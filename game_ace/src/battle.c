#include "battle.h"
#include <ace/utils/palette.h>
#include <ace/utils/disk_file.h>
#include <ace/utils/endian.h>
#include <ace/managers/key.h>
#include <ace/managers/mouse.h>
#include <ace/managers/system.h>
#include "button.h"
#include "gfx.h"
#include "mover.h"
#include "picture.h"
#include "missile.h"
#include "polanie.h"
#include "track.h"
#include "world.h"
#include "misc.h"
#include "menu.h"
#include "castle.h"

#define MaxX WORLD_SIZE_X
#define MaxY WORLD_SIZE_Y
#define MaxUnitsInCastle CASTLE_UNITS_MAX

// 1-single start   0-rs   2-loaded
typedef enum tBattleStartKind {
	START_KIND_MULTIPLAYER_RS232 = 0,
	START_KIND_SINGLEPLAYER = 1,
	START_KIND_SAVED_GAME = 2,
} tBattleStartKind;

typedef enum tEndLevelResult { // endL
	END_RESULT_VICTORY = 1,
	END_RESULT_DEFEAT = 2,
} tEndLevelResult;

typedef struct Plansza {
	char decisionType; // 0-miasto 1-bitwa dyn 2-stat 3,4-nic
	char gen;          // 0-nic 1-generator
	char endType;      // 0-zabij 1-uratuj 2-zabij jedn
	char typ;   // typ uratowanego /nr domu do zostawienia 20-nic nie zostawiaj
	int xw, yw; // xwyjscia,ywwyjscia -do uratowania
	int x0, y0; // miejsce faceta do uwolnienia;
	int xp, yp, tp; // miejsce przemiany,typ przemiany;
	int gTimer;
	int maxmilk;
	char name[20];
	char haslo;
	char nrh;
	char nrp; // nr planszy jezeli rowny 7 14 24 to haslo
	char ide;
	char next;
} Plansza;

typedef struct EditStr {
  int mode; // 0-tereny(skaly,woda,droga,sucha ziemia,palisada),
            // 1-gadgety,2-drzewa, 3-postacie, 4-budynki, 5-rodzaje decyzji i
            // konca
  int panel;
  int obj;
  int color;        // 0-niebieski 1-szary 2-zolty 3-zielony
  int xp, yp;       // pastwisko wrogow
  int xz, yz;       // zbiorka wrogow
  int xo, yo;       // postac do odnalezienia
  int xk, yk;       // krag
  int xprz, yprz;   // miejsce przemiany
  int warunekKonca; // 0-zabij wszystkich 1-uratuj 2-zabij jednego
  int typPlanszy;   // 0-wioska 1-bitwa dyn 2-stat 3-nic
  int postac;
  int generator;
  int maxmilk;
  int milk;
  int X, Y;
  char pName[20];
  char name[40];
} EditStr;

tEndLevelResult endL;
tBattleStartKind eStartKind;
tBitMap *s_pBattleUi;
Plansza pl;
EditStr E;

static int ScreenX = 3;
static int ScreenY = 1;
static UBYTE showAll;

static tEndLevelResult EndLevel(void);

static void battlePlayMsgSound(void) {
	// if (Msg.dzwiek) {
	// 	if (Msg.dzwiek < 0)
	// 		Msg.dzwiek = 0;
	// 	if (!SND.jest_odtwarzany) // 1996.06.29
	// 	{
	// 		if (Msg.X < ScreenX + 22 && Msg.Y < ScreenY + 18 &&
	// 				Msg.X > ScreenX - 5 && Msg.Y > ScreenY - 4)
	// 			if (dzwiek && Msg.dzwiek < 26)
	// 				SND(Msg.dzwiek - 1);
	// 		if (mowa && Msg.dzwiek > 25)
	// 			SND(Msg.dzwiek - 1);
	// 		Msg.dzwiek = 0;
	// 		Msg.ddzwiek++;
	// 		if (Msg.ddzwiek > 2)
	// 			Msg.ddzwiek = 0;
	// 	}
	// }
}

static void battleShowBackground(void) {
	blitCopyAligned(s_pBattleUi, 0, 0, g_pVpManager->pBack, 0, 0, 320, 200);

	//Patch the palette bar from the background
	blitCopy(g_pVpManager->pBack, 110, 0, g_pVpManager->pBack, 0, 0, 110, 1, MINTERM_COOKIE);

	// Remove stuff from the game window
	blitRect(g_pVpManager->pBack, 11, 8, 267 - 11, 190 - 8, 0);
}

#define ACTION_PANEL_BUTTON_COUNT 6

// Co:
typedef enum tWhat {
	WHAT_HQ = 20, // Budynek glowny
	WHAT_SHED = 21, // Obora
	WHAT_HUT = 22, // Chata mieszkalna
	WHAT_MAGE_HUT = 23, // Dwór Mocy
	WHAT_WARRIOR_HUT = 24, // Chata Wojów
	WHAT_KNIGHT_HUT = 25, // Dwór rycerza
} tWhat;

// static tImage *tlo;
// static tImage *Mysz[13];
// static tImage *ramka[4];

UWORD g_uwLevel;

#define PANEL_BUTTON_X 274
#define PANEL_BUTTON_Y1 18
#define PANEL_BUTTON_DY 20
#define PANEL_BUTTON_Y(y) (PANEL_BUTTON_Y1 + (y) * PANEL_BUTTON_DY)

// kto 0-oni 1-myb 2-mypost
static void battleShowPanel(int iff, int co, UWORD uwMax, UWORD uwFood, int ubPressedButton)
{
	for (UBYTE i = 0; i < ACTION_PANEL_BUTTON_COUNT; i++) {
		gfxDrawImageNoMask(
			PANEL_BUTTON_X, PANEL_BUTTON_Y(i),
			&Buttons[BUTTON_BG_KIND_UNPRESSED]
		);
	}

	if (ubPressedButton){
		gfxDrawImageNoMask(
			PANEL_BUTTON_X, PANEL_BUTTON_Y(ubPressedButton - 1),
			&Buttons[BUTTON_BG_KIND_PRESSED]
		);
	}

	if (iff + co + uwMax == 0) {
		return;
	}

	switch (co) {
		case WHAT_HQ:
			if (uwMax >= 1050)
				gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(1) + 1, &buttons[BUTTON_KIND_MAGE_HUT]); // swiatynia
			if (uwMax >= 850)
				gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(2) + 1, &buttons[BUTTON_KIND_HUT]); // koszary1
			if (uwMax >= 650)
				gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(3) + 1, &buttons[BUTTON_KIND_SHED]); // stajnia
			if (uwMax >= 250)
				gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(5) + 1, &picture[PICTURE_KIND_ROAD_15]); // droga
			break;
		case WHAT_SHED:
			// odbudowa +krowa
			if (uwMax >= 450 && uwFood)
				gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(4) + 1, &movers[0][MOVER_KIND_COW][1][1]);
			if (uwMax >= 1250 && uwFood && g_uwLevel > PASTUCH_LEV)
				gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(0) + 1, &movers[0][MOVER_KIND_FARMER][1][1]);
			break;
		case WHAT_HUT:
			// odbudowa +procarz+dzida+koszary2
			if (uwMax >= 1050)
				gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(1) + 1, &buttons[BUTTON_KIND_WARRIOR_HUT]); // koszary2
			if (uwMax >= 650 && uwFood)
				gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(3) + 1, &movers[0][MOVER_KIND_HUNTER][1][1]);
			if (uwMax >= 450 && uwFood)
				gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(4) + 1, &movers[0][MOVER_KIND_AXE][1][1]);
			break;
		case WHAT_MAGE_HUT:
			// odbudowa +babcia+kaplan
			if (uwMax >= 1250 && uwFood && g_uwLevel > MAG_LEV)
				gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(0) + 1, &movers[0][MOVER_KIND_MAGE][1][1]); // mag
			if (uwMax >= 1050 && uwFood)
				gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(1) + 1, &movers[0][MOVER_KIND_PRIEST][1][1]); // kaplan
			if (uwMax >= 650 && uwFood)
				gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(3) + 1, &movers[0][MOVER_KIND_PRIESTESS][1][1]); // druidka
			break;
		case WHAT_WARRIOR_HUT:
			// odbudowa +miecz+luk+akademia
			if (uwMax >= 1050)
				gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(1) + 1, &buttons[BUTTON_KIND_KNIGHT_HUT]); // dom bohatera
			if (uwMax >= 850 && uwFood)
				gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(2) + 1, &movers[0][MOVER_KIND_PIKE][1][1]); // luk
			if (uwMax >= 650 && uwFood)
				gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(3) + 1, &movers[0][MOVER_KIND_SWORD][1][1]); // miecz
			if (uwMax >= 250)
				gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(5) + 1, &buttons[BUTTON_KIND_WALL]); // palisada
			break;
		case WHAT_KNIGHT_HUT:
			// odbudowa +wodz
			if (uwMax >= 1250 && uwFood && g_uwLevel > KUSZNIK_LEV)
				gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(0) + 1, &movers[0][MOVER_KIND_XBOW][1][1]);
			if (uwMax >= 1050 && uwFood)
				gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(1) + 1, &movers[0][MOVER_KIND_KNIGHT][1][1]);
			break;
	}

	if (co && co < 20) {
		gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(0) + 1, &buttons[BUTTON_KIND_SHIELD]);

		if (co == 4 && uwFood > 79) {
			gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(2) + 3, &missiles[2][1][2]);
			gfxDrawImageMaskedClipped(PANEL_BUTTON_X - 3, PANEL_BUTTON_Y(2) + 1, &missiles[2][1][2]); // deszcz
			gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 5, PANEL_BUTTON_Y(2) + 1, &missiles[2][1][2]);
		}
		if (co == 4 && uwFood > 25)
			gfxDrawImageNoMask(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(3) + 1, &buttons[BUTTON_KIND_PEEK]);
		if (co == 3 && uwFood > 79) {
			gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(2) + 2, &missiles[1][1][2]); // deszcz
			gfxDrawImageMaskedClipped(PANEL_BUTTON_X - 3, PANEL_BUTTON_Y(2) + 1, &missiles[1][1][2]); // deszcz
			gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 5, PANEL_BUTTON_Y(2) + 1, &missiles[1][1][2]); // deszcz
		}
		if (co == 3 && uwFood > 49) {
			gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(3) + 1, &picture[PICTURE_KIND_SHIELD_0]);
		}
		if (co == 1 && ubPressedButton == 3) {
			gfxDrawImageMaskedClipped(PANEL_BUTTON_X + 1, PANEL_BUTTON_Y(2) + 1, &buttons[BUTTON_KIND_REPAIR]);
		}
	}
}

static void battleDrawSelection(void) {
	// if (select.IFF < 2) {
	//   int color22 = LightGray;
	//   if (select.IFF)
	//     color22 = LightRed;
	//   if (select.co) // zolnierz
	//   {
	//     if (selectM->exist != 1) // jezeli nie zyje
	//     {
	//       SetClippingArea13h(0, 0, 319, 199);
	//       int p = 0;
	//       int b = 0;
	//       if (selectM->IFF == 1) {
	//         b = 20;
	//         int kkk = 0;
	//         for (int i = 1; i < CASTLE_MOVERS_MAX; i++) {
	//           if (castle[0].m[i].wybrany && castle[0].m[i].exist == 1) {
	//             p = i;
	//             kkk++;
	//           }
	//         }
	//         if (p) {
	//           selectM = &castle[0].m[p];
	//           if (kkk == 1)
	//             grupa = 0; // skasowac grupe
	//         } else {       // szukaj w budynkach
	//           b = 20;
	//           b = 4;
	//           int kkk = 0;
	//           for (int j = 0; j < 20; j++)
	//             for (i = 0; i < 20; i++)
	//               if (castle[0].b[j].m[i].wybrany &&
	//                   castle[0].b[j].m[i].exist == 1) {
	//                 p = i;
	//                 b = j;
	//                 kkk++;
	//               }
	//           if (b < 20) {
	//             selectM = &castle[0].b[j].m[i];
	//             if (kkk == 1)
	//               grupa = 0;
	//           } else {
	//             b = 0;
	//             p = 0;
	//           }
	//         }
	//       }
	//       if (!p && !b) {
	//         select.IFF = 2;
	//         ShowPanel(0, 0, 0, 0, 0);
	//         mouseMode = 0; //  to odznacz
	//       }
	//     }
	//   } else // budynek
	//   {
	//     if (selectB->exist == 1 || selectB->exist > 2) {
	//       int xr, yr; // zaznaczenie budynku
	//       xr = (selectB->x - ScreenX) * 16 + 11 - 3;
	//       yr = (selectB->y - ScreenY) * 14 + 8;
	//       int color = LightGreen;
	//       if (selectB->hp < (selectB->maxhp >> 1))
	//         color = Yellow;
	//       if (selectB->hp < (selectB->maxhp >> 2))
	//         color = LightRed;

	//       Bar13h(xr + 1, yr - 1, xr + 1 + (selectB->hp * 52 / selectB->maxhp),
	//              yr + 1, color);
	//       if (selectB->type > 1 &&
	//           !select.IFF) // wypisz ilosc jedzenia w naszej chacie
	//       {
	//         color = (selectB->maxfood - selectB->food);
	//         for (i = 0; i < selectB->maxfood; i++) {
	//           if (i < color)
	//             Bar13h(xr + 3 + i * 5, yr + 41, xr + 6 + i * 5, yr + 43,
	//                    DarkYellow);
	//           else
	//             Bar13h(xr + 3 + i * 5, yr + 41, xr + 6 + i * 5, yr + 43,
	//                    DarkBrown);
	//         }
	//       }
	//       PutImageChange13h(xr + 1, yr - 3, buttons[1], 1, color1, color22);
	//       PutImageChange13h(xr + 53 - 16, yr - 3, buttons[2], 1, color1,
	//                         color22);
	//       PutImageChange13h(xr + 1, yr + 45 - 14, buttons[3], 1, color1,
	//                         color22);
	//       PutImageChange13h(xr + 53 - 16, yr + 45 - 14, buttons[4], 1, color1,
	//                         color22);
	//     } else {
	//       select.IFF = 2;
	//       SetClippingArea13h(0, 0, 319, 199);
	//       ShowPanel(0, 0, 0, 0, 0);
	//       mouseMode = 0; // jezeli nie to odznacz
	//     }
	//   }
	// }
}

static void battleDrawMilk(void) {
	// PutImage13h(299, 9, drewno[2], 0); //???
	// i = castle[master].milk;
	// if (i > 1410)
	// 	i = 1410;
	// i = i / 10;
	// if (i)
	// 	Bar13h(299, 150 - i, 314, 150, 255);
	// i = castle[master].maxmilk;
	// if (i > 1260)
	// 	i = 0;
	// i = i / 10;
	// if (i)
	// 	Bar13h(299, 150 - i, 314, 151 - i, LightRed);
}

static void battleDrawMsg(void) {
	// if (Msg.licznik && !mowa) {
	// 	OutText13h(29, 171, Msg.msg, 1);
	// 	OutText13h(30, 170, Msg.msg, MsgFontColor);
	// }
}

static void battleUpdateTooltip(void) {
	// if (mouseCommand > 1) {
	// 	switch (mouseCommand) {
	// 	case 2:
	// 		OutText13h(80, 23, "Budowa drogi", White);
	// 		break;
	// 	case 3:
	// 		OutText13h(80, 23, "Budowa palisady", White);
	// 		break;
	// 	case 4:
	// 		OutText13h(80, 23, "Budowa obory", White);
	// 		break;
	// 	case 5:
	// 		OutText13h(80, 23, "Budowa chaty drwali i my*liwych", White);
	// 		break;
	// 	case 6:
	// 		OutText13h(80, 23, "Budowa chaty kap`an%w", White);
	// 		break;
	// 	case 7:
	// 		OutText13h(80, 23, "Budowa chaty woj%w", White);
	// 		break;
	// 	case 8:
	// 		OutText13h(80, 23, "Budowa chaty rycerza", White);
	// 		break;
	// 		/*  case 2:OutText13h(49,24,"Weg bauen",1);OutText13h(50,23,"Weg
	// 			bauen",White);break; case 3:OutText13h(49,24,"Zaun
	// 			bauen",1);OutText13h(50,23,"Zaun bauen",White);break; case
	// 			4:OutText13h(49,24,"Scheune bauen",1);OutText13h(50,23,"Scheune
	// 			bauen",White);break; case 5:OutText13h(49,24,"Haus der J[ger
	// 			bauen",1);OutText13h(50,23,"Haus der J[ger bauen",White);break; case
	// 			6:OutText13h(49,24,"Haus der Priester
	// 			bauen",1);OutText13h(50,23,"Haus der Priester bauen",White);break;
	// 			case 7:OutText13h(49,24,"Haus der K[mpfer
	// 			bauen",1);OutText13h(50,23,"Haus der K[mpfer bauen",White);break;
	// 			case 8:OutText13h(49,24,"Haus der Ritter
	// 			bauen",1);OutText13h(50,23,"Haus der Ritter bauen",White);break;
	// 		*/
	// 	}
	// }
	// if (!select.co && !select.IFF && !mowa) {
	// 	switch (selectB->type) {
	// 	case 1:
	// 		OutText13h(81, 12, "Budynek glowny", 1);
	// 		OutText13h(80, 12, "Budynek glowny", LightGray);
	// 		break;
	// 	case 2:
	// 		OutText13h(81, 12, "  Obora", 1);
	// 		OutText13h(80, 12, "  Obora", LightGray);
	// 		break;
	// 	case 3:
	// 		OutText13h(81, 12, "Chata drwali i mysliwych", 1);
	// 		OutText13h(80, 12, "Chata drwali i mysliwych", LightGray);
	// 		break;
	// 	case 4:
	// 		OutText13h(81, 12, "Chata kaplanow", 1);
	// 		OutText13h(80, 12, "Chata kaplanow", LightGray);
	// 		break;
	// 	case 5:
	// 		OutText13h(81, 12, "Chata wojow", 1);
	// 		OutText13h(80, 12, "Chata wojow", LightGray);
	// 		break;
	// 	case 6:
	// 		OutText13h(81, 12, "Chata rycerza", 1);
	// 		OutText13h(80, 12, "Chata rycerza", LightGray);
	// 		break;

	// 		/* case
	// 			1:OutText13h(49,13,"Hauptgeb[ude",1);OutText13h(50,12,"Hauptgeb[ude",FontColor);break;
	// 			case 2:OutText13h(49,13," Scheune",1);OutText13h(50,12,"
	// 			Scheune",FontColor);break; case 3:OutText13h(49,13,"Haus der
	// 			J[ger",1);OutText13h(50,12,"Haus der J[ger",FontColor);break; case
	// 			4:OutText13h(49,13,"Haus der Priester",1);OutText13h(50,12,"Haus der
	// 			Priester",FontColor);break; case 5:OutText13h(49,13,"Haus der
	// 			K[mpfer",1);OutText13h(50,12,"Haus der K[mpfer",FontColor);break;
	// 			case 6:OutText13h(49,13,"Haus der Ritter",1);OutText13h(50,12,"Haus
	// 			der Ritter",FontColor);break;
	// 		*/
	// 	}
	// }
	// if (select.co == 1) {
	// 	if (pl.endType == 1 && !select.IFF && select.nrm == 1 &&
	// 			select.nrb == 20) {
	// 		OutText13h(100, 30, pl.name, 1);
	// 		OutText13h(101, 30, pl.name, FontColor);
	// 	}
	// 	if (pl.endType == 4 && select.IFF == 1 && select.nrm == 1 &&
	// 			select.nrb == 20) {
	// 		OutText13h(100, 30, pl.name, 1);
	// 		OutText13h(101, 30, pl.name, LightRed);
	// 	}
	// }
	// if (showcel) {
	// 	OutText13h(19, 76, cel1, 1);
	// 	OutText13h(20, 75, cel1, FontColor);
	// 	OutText13h(19, 86, cel2, 1);
	// 	OutText13h(20, 85, cel2, FontColor);
	// }
}

static void battleProcessMouse(void) {
	// int M;
	// int x, y;

	// x = (int)((uwMouseX - 11) >> 4) + ScreenX;
	// y = (int)(uwMouseY - 8) / 14 + ScreenY;
	// M = 1;
	// if (select.IFF < 2) // jezeli zaznaczony
	// {
	//   if (!select.IFF && select.co) // nasz zolnierz
	//   {
	//     M = 12;
	//     if (!place[x][y]) {
	//       M = 2;
	//     } // jezeli wolne to idz

	//     if (selectM->type && place[x][y] > 255) {
	//       M = 5;
	//     } // zaznacz??????
	//     if (selectM->type && place[x][y] > 511) {
	//       M = 3;
	//     } // atakuj
	//     if (selectM->type == 10 && M == 3) {
	//       Mover1 *mm = Pointer(place[x][y]);
	//       if (mm == NULL ||
	//           (mm->type != 0 && mm->type != 8)) // krowa i niedzwiedz
	//       {
	//         M = 12;
	//       } // nie atakuj nikogo oprocz krowy
	//     }
	//     if ((selectM->type != 4 && selectM->type != 1) && place[x][y] > 768) {
	//       M = 12;
	//     } // nie drzewo
	//     if ((selectM->type == 1) && place[x][y] > 768 && placeG[x][y] < 119 &&
	//         placeG[x][y] > 112) {
	//       M = 12;
	//     } // nie drzewo

	//     if (!selectM->type && place[x][y] < 512 && placeG[x][y] > 157 &&
	//         placeG[x][y] < 166)
	//       M = 2; // krowa idz do naszej obory
	//     if (!placeN[x][y])
	//       M = 2; // idz
	//     if (!mouseMode)
	//       M = 1; // strzalka
	//     if (!mouseMode && place[x][y] > 255 && place[x][y] < 768 &&
	//         placeN[x][y]) {
	//       M = 5;
	//     } // nasz
	//     if ((selectM->type == 1) && (select.co == 1) &&
	//         (place[x][y] == 2 || placeG[x][y] == 277 ||
	//          (place[x][y] > 255 && place[x][y] < 511 && placeG[x][y] > 126 &&
	//           placeG[x][y] < 256)))
	//       M = 13; // robota
	//     if ((selectM->type == 3) && mouseCommand == 13)
	//       M = 16;
	//     if ((selectM->type == 4) && mouseCommand == 13)
	//       M = 17;

	//   } else // nie nasz
	//   {
	//     if (place[x][y] > 255 && place[x][y] < 768)
	//       M = 5;
	//   }
	// }
	// // jezeli nikt nie zaznaczony

	// if (select.IFF >= 2)
	//   if (place[x][y] > 255 && place[x][y] < 768)
	//     M = 5; // zaznacz

	// int k = mouse.Button;
	// mouse.Button = 1;
	// if (mouse.MWindow(11, 8, 76, 74) && Map && mouseCommand < 2) // na mapie
	// {
	//   x = uwMouseX - 12;
	//   y = uwMouseY - 9;
	//   M = 15;
	//   if (mouseMode)
	//     M = 4;
	// }
	// mouse.Button = k;
	// if (mouseCommand > 1 && mouseCommand < 8 && !select.co)
	//   M = 1;
	// if (uwMouseX > 261)
	//   M = 1; // panel
	// if (uwMouseY > 192) {
	//   uwMouseY = 192;
	//   M = 9;
	//   if (ScreenY == WORLD_SIZE_Y - 14)
	//     M = 12;
	// }
	// if (uwMouseY > 192 - 7 && M == 1) {
	//   uwMouseY = 192;
	//   M = 9;
	//   if (ScreenY == WORLD_SIZE_Y - 14)
	//     M = 12;
	// }
	// if (uwMouseY < 8) {
	//   uwMouseY = 7;
	//   M = 8;
	//   if (ScreenY == 1)
	//     M = 12;
	// }
	// if (uwMouseX < 11) {
	//   uwMouseX = 8;
	//   M = 10;
	//   if (ScreenX == 1)
	//     M = 12;
	// }
	// if (uwMouseX > 306) {
	//   uwMouseX = 311;
	//   M = 11;
	//   if (ScreenX == WORLD_SIZE_X - 17)
	//     M = 12;
	// }

	// if (zaznaczanie) {
	//   if (uwMouseX > 261)
	//     uwMouseX = 261;
	//   if (uwMouseY > 192 - 7)
	//     uwMouseY = 192 - 7;
	//   if (uwMouseY < 10)
	//     uwMouseY = 10;
	//   if (uwMouseX < 12)
	//     uwMouseX = 12;
	//   Rectangle13h(rx1, ry1, rx2, ry2, LightGray);
	//   M = 1;
	// }

	// if (mouseCommand > 1 && mouseCommand < 10 && !select.co) // budynek
	// {
	//   int i, j, siz = 3, kol = 255, dr = 0;
	//   if (mouseCommand < 4)
	//     siz = 1;
	//   /////  tu sprawdzic
	//   showAll = 1;
	//   for (i = -1; i <= siz; i++)
	//     for (j = 0; j < siz; j++) {
	//       if (placeG[x + i][y + j] > 30 && placeG[x + i][y + j] < 54)
	//         dr = 1;
	//     }
	//   for (i = 0; i < siz; i++)
	//     for (j = -1; j <= siz; j++) {
	//       if (placeG[x + i][y + j] > 30 && placeG[x + i][y + j] < 54)
	//         dr = 1;
	//     }
	//   if (y > 62 || x > 62)
	//     dr = 0;
	//   int c = 0;
	//   if (mouseCommand == 3) {
	//     dr = 1;
	//   } // palisada
	//   if (mouseCommand == 2) {
	//     c = 1;
	//   } // droga

	//   if (dr == 1) {
	//     for (i = 0; i < siz; i++)
	//       for (j = 0; j < siz; j++) {
	//         if (place[x + i][y + j] > c)
	//           kol = LightRed;
	//         if (!placeN[x + i][y + j])
	//           kol = LightRed;
	//         if ((placeG[x + i][y + j] > 45 && placeG[x + i][y + j] < 54) ||
	//             (placeG[x + i][y + j] > 126 && placeG[x + i][y + j] < 257))
	//           kol = LightRed;
	//       }
	//   } else {
	//     kol = LightRed;
	//   }
	//   siz--;
	//   if (x >= ScreenX && x < ScreenX + 16 && y >= ScreenY && y < ScreenY + 13) {
	//     PutImageChange13h(11 + (x - ScreenX) * 16, 8 + (y - ScreenY) * 14,
	//                       buttons[1], 1, color1, kol);
	//   }
	//   if (x + siz >= ScreenX && x + siz < ScreenX + 16 && y >= ScreenY &&
	//       y < ScreenY + 13) {
	//     PutImageChange13h(11 + (x + siz - ScreenX) * 16, 8 + (y - ScreenY) * 14,
	//                       buttons[2], 1, color1, kol);
	//   }
	//   if (x >= ScreenX && x < ScreenX + 16 && y + siz >= ScreenY &&
	//       y + siz < ScreenY + 13) {
	//     PutImageChange13h(11 + (x - ScreenX) * 16, 8 + (y + siz - ScreenY) * 14,
	//                       buttons[3], 1, color1, kol);
	//   }
	//   if (x + siz >= ScreenX && x + siz < ScreenX + 16 && y + siz >= ScreenY &&
	//       y + siz < ScreenY + 13) {
	//     PutImageChange13h(11 + (x + siz - ScreenX) * 16,
	//                       8 + (y + siz - ScreenY) * 14, buttons[4], 1, color1,
	//                       kol);
	//   }
	// }
	// int colorM = White; // LightGreen;
	// if (mouseP > 1) {
	//   colorM = LightGray;
	//   if (M == 2)
	//     M = 7;
	//   if (M == 3)
	//     M = 6;
	// }
	// int a = 8, b = 7;
	// if (M == 15) {
	//   GetImage13h(uwMouseX - 8, uwMouseY - 7, uwMouseX + 8, uwMouseY + 7, Mysz[0]);
	//   PutImageChange13h(uwMouseX - 8, uwMouseY - 7, buttons[5], 1, Color1, colorM);
	// } else {
	//   if (M == 13) {
	//     GetImage13h(uwMouseX - 8, uwMouseY - 7, uwMouseX + 8, uwMouseY + 7, Mysz[0]);
	//     PutImage13h(uwMouseX - 8, uwMouseY - 7, buttons[8], 1);
	//   } else {
	//     if (M == 16) {
	//       GetImage13h(uwMouseX - 8, uwMouseY - 7, uwMouseX + 8, uwMouseY + 7,
	//                   Mysz[0]);
	//       PutImage13h(uwMouseX - 8, uwMouseY - 6, &missiles[1][1][2], 1);
	//       PutImage13h(uwMouseX - 5, uwMouseY - 7, &missiles[1][1][2], 1);
	//       PutImage13h(uwMouseX - 11, uwMouseY - 7, &missiles[1][1][2], 1);
	//     } else {
	//       if (M == 17) {
	//         GetImage13h(uwMouseX - 8, uwMouseY - 7, uwMouseX + 8, uwMouseY + 7,
	//                     Mysz[0]);
	//         PutImage13h(uwMouseX - 8, uwMouseY - 6, &missiles[2][1][2], 1);
	//         PutImage13h(uwMouseX - 5, uwMouseY - 7, &missiles[2][1][2], 1);
	//         PutImage13h(uwMouseX - 11, uwMouseY - 7, &missiles[2][1][2], 1);
	//       } else {
	//         if (M == 1) {
	//           a = 2;
	//           b = 2;
	//         }
	//         GetImage13h(uwMouseX - a, uwMouseY - b, uwMouseX - a + 16,
	//                     uwMouseY - b + 14, Mysz[0]);
	//         mouse.Button = 1;
	//         if (mouseCommand > 1 && mouse.MWindow(11, 8, 267, 190)) {
	//         } else {
	//           PutImageChange13h(uwMouseX - a, uwMouseY - b, Mysz[M], 1, Color1,
	//                             colorM);
	//         }
	//         mouse.Button = 0;
	//       }
	//     }
	//   }
	// }
	// ShowVirtualScreen();
	// PutImage13h(uwMouseX - a, uwMouseY - b, Mysz[0], 0);
}

void battleRefreshScreen(void) {
	showAll = 2;
}

static void battleShowSelected(void) {
	if (showAll) {
		--showAll;
		gfxSetClippingArea(11, 8, 267, 190); // 262,192
		worldShowPlace(ScreenX, ScreenY);

		castleShowS(&castle[0], ScreenX, ScreenY, 1);
		castleShowS(&castle[1], ScreenX, ScreenY, 1);
		castleShowS(&castle[1], ScreenX, ScreenY, 2);
		castleShowS(&castle[0], ScreenX, ScreenY, 2);
		int xee = (ScreenX << 4) - 11;
		int yee = ScreenY * 14 - 8;
		castleShowS(&castle[0], xee, yee, 3);
		castleShowS(&castle[1], xee, yee, 3);

		worldShowTrees(ScreenX, ScreenY);
		battleDrawSelection();
		gfxSetClippingArea(0, 0, 319, 199);

		battleDrawMilk();

		// if (mouseCommand < 2) {
		//   ShowBattleMap(ScreenX, ScreenY);
		// }

		battleDrawMsg();
		battleUpdateTooltip();
	}

	battleProcessMouse();
}

static void battleInitOldLevel(UWORD uwLevel) {
	tFile *pFileMaps = diskFileOpen("data/levels/level.dat", DISK_FILE_MODE_READ, 0);
	UBYTE z;
	int k = 0, p0 = 1, p1 = 1;
	int chatki = 1, chaTki = 1;

	logWrite("Skipping level load until %hu\n", uwLevel);
	do {
		fileRead(pFileMaps, &z, sizeof(z));
		if (z == '$')
			k++;
		if (z == '@') {
			logWrite("ERR: unexpected char @ while loading map\n");
			return;
		}
	} while (k != uwLevel);

	// Maps are encoded with windows codepage 1250
	for (UBYTE j = 0; j < WORLD_SIZE_Y; j++) {
		do {
			fileRead(pFileMaps, &z, sizeof(z));
			if (z == '@') {
				logWrite("ERR: unexpected char @ while loading map\n");
				return;
			}
			if (z == 'D') {
				fileRead(pFileMaps, &z, sizeof(z));
				pl.decisionType = (char)(z - 48);
			}
			if (z == 'E') {
				fileRead(pFileMaps, &z, sizeof(z));
				pl.endType = (char)(z - 48);
			}
			if (z == 'G')
				pl.gen = 1;
			if (z == 'P') {
				fileRead(pFileMaps, &z, sizeof(z));
				pl.tp = (char)(z - 48);
			}
			if (z == 'T') {
				fileRead(pFileMaps, &z, sizeof(z));
				char i = (char)(z - 48);
				fileRead(pFileMaps, &z, sizeof(z));
				pl.typ = (char)(z - 48) + i * 10;
			}
			if (z == 'M') {
				fileRead(pFileMaps, &z, sizeof(z));
				pl.maxmilk = (int)(z - 48) * 200 + 50;
				if (pl.maxmilk == 50)
					pl.maxmilk = 0;
			}
			if (z == 'N') {
				fileRead(pFileMaps, &z, sizeof(z));
				char i = (char)(z - 48);
				fileRead(pFileMaps, &z, sizeof(z));
				pl.next = (char)(z - 48) + i * 10;
			}
			if (z == '*') {
				UBYTE cc = 0;
				do {
					fileRead(pFileMaps, &z, sizeof(z));
					pl.name[cc] = z;
					cc++;
				} while (pl.name[cc - 1] != '*');
				pl.name[cc - 1] = 0;
			} //   'imie'

		} while (z != '!');
		if (pl.endType == 4 && !p1)
			p1 = 1;

		for (UBYTE i = 0; i < WORLD_SIZE_X; i++) {
			if(p0 > CASTLE_MOVERS_MAX - 5) {
				p0 = CASTLE_MOVERS_MAX - 5;
			}
			if(p1 > CASTLE_MOVERS_MAX - 5) {
				p1 = CASTLE_MOVERS_MAX - 5;
			}
			fileRead(pFileMaps, &z, sizeof(z));
			if (z == '@') {
				logWrite("ERR: unexpected char @ while loading map\n");
				return;
			}
			place[i][j] = 0;
			if (i == 0 || i == WORLD_SIZE_X - 1 || j == 0 || j == WORLD_SIZE_Y - 1)
				place[i][j] = 10;
			placeG[i][j] = 8;
			if (z == '*') {
				if (pl.endType == 1) {
					place[i][j] = 10;
					pl.x0 = i;
					pl.y0 = j;
				}
				if (pl.endType == 4) {
					if (!p1) {
						p1++;
					}

					moverInit(&castle[1].m[1], pl.typ, i, j, 0, 5);
					moverSetNr(&castle[1].m[1], 512 + 201);
					moverSetIFF(&castle[1].m[1], 2);
					moverShow(&castle[1].m[1]);
				}
			}
			if (z == '^') {
				pl.xw = i;
				pl.yw = j;
				placeG[i][j] = 301;
			}
			if (z == '.')
				placeG[i][j] = 256;
			if (z == '+') {
				placeN[i][j] = 1;
				placeN[i + 1][j] = 1;
				placeN[i + 1][j + 1] = 1;
				placeN[i][j + 1] = 1;
			}

			if (z == 'a')
				placeG[i][j] = 54; // zejscie ze skal
			if (z == 'b')
				placeG[i][j] = 55;
			if (z == 'c')
				placeG[i][j] = 56;
			if (z == 'd')
				placeG[i][j] = 57;
			if (z == 'e') {
				placeG[i][j] = 58;
				place[i][j] = 10;
			}
			if (z == 'f') {
				placeG[i][j] = 59;
				place[i][j] = 0;
			}
			if (z == 'g') {
				placeG[i][j] = 60;
				place[i][j] = 10;
			}
			if (z == 'h') {
				placeG[i][j] = 61;
				place[i][j] = 10;
			}
			if (z == 'i') {
				placeG[i][j] = 62;
				place[i][j] = 10;
			}
			if (z == 'j') {
				placeG[i][j] = 63;
				place[i][j] = 10;
			}
			if (z == 'k') {
				placeG[i][j] = 64;
				place[i][j] = 10;
			}
			if (z == 'l') {
				placeG[i][j] = 65;
				place[i][j] = 10;
			}
			if (z == 'm') {
				placeG[i][j] = 66;
				place[i][j] = 10;
			}
			if (z == 'n')
				placeG[i][j] = 67;
			if (z == 'o') {
				placeG[i][j] = 68;
				place[i][j] = 10;
			}
			if (z == 'p') {
				placeG[i][j] = 69;
				place[i][j] = 10;
			}
			// skaly
			if (z == 211) { // 'Ó'
				placeG[i][j] = 9;
				place[i][j] = 10;
			}
			if (z == 201) { // 'É'
				placeG[i][j] = 10;
				place[i][j] = 10;
			}
			if (z == 186) { // 'ş'
				placeG[i][j] = 11;
				place[i][j] = 10;
			}
			if (z == 217) { // 'Ů'
				placeG[i][j] = 12;
				place[i][j] = 10;
			}
			if (z == 196) { // 'Ä'
				placeG[i][j] = 13;
				place[i][j] = 10;
			}
			if (z == 130) { // '¸'
				placeG[i][j] = 14;
				place[i][j] = 10;
			}
			if (z == 179) { // 'ł'
				placeG[i][j] = 15;
				place[i][j] = 10;
			}
			if (z == 205) { // 'Í'
				placeG[i][j] = 16;
				place[i][j] = 10;
			}
			if (z == 's') {
				placeG[i][j] = 17;
				place[i][j] = 0;
			} // wejscie
			if (z == 188) { // 'Ľ'
				placeG[i][j] = 18;
				place[i][j] = 10;
			}
			if (z == 212) { // 'Ô'
				placeG[i][j] = 19;
				place[i][j] = 10;
			}
			if (z == 218) { // 'Ú'
				placeG[i][j] = 20;
				place[i][j] = 10;
			}
			if (z == 183) { // '·'
				placeG[i][j] = 21;
				place[i][j] = 10;
			}

			if (z == 'u') {
				placeG[i][j] = 256;
				xleczenie = i;
				yleczenie = j;
			}
			if (z == '/') {
				placeG[i][j] = 300;
				pl.xp = i;
				pl.yp = j;
			}
			if (z == 'q')
				placeG[i][j] = 22;
			if (z == 't')
				placeG[i][j] = 35;
			if (z == 'w') {
				placeG[i][j] = 74;
				place[i][j] = 1;
			}
			if (z == 'r') {
				placeG[i][j] = 266;
				place[i][j] = 256 + 512 + drzewa;
				drzewa++;
			} //??
			//--------most-------------------
			if (z == '1')
				placeG[i][j] = 46;
			if (z == '2')
				placeG[i][j] = 47;
			if (z == '3')
				placeG[i][j] = 48;
			if (z == '4')
				placeG[i][j] = 49;
			if (z == '5')
				placeG[i][j] = 50;
			if (z == '6')
				placeG[i][j] = 51;
			if (z == '7')
				placeG[i][j] = 52;
			if (z == '8')
				placeG[i][j] = 53;
			// ---------drzewa ---------------
			if (z == 'A' && drzewa < 2000) {
				placeG[i][j] = 113;
				place[i][j] = 256 + 512 + drzewa;
				drzewa++;
			}
			if (z == 'B' && drzewa < 2000) {
				placeG[i][j] = 114;
				place[i][j] = 256 + 512 + drzewa;
				drzewa++;
			}
			if (z == 'C' && drzewa < 2000) {
				placeG[i][j] = 115;
				place[i][j] = 256 + 512 + drzewa;
				drzewa++;
			}
			if (z == 'D' && drzewa < 2000) {
				placeG[i][j] = 116;
				place[i][j] = 256 + 512 + drzewa;
				drzewa++;
			}
			if (z == 'E' && drzewa < 2000) {
				placeG[i][j] = 117;
				place[i][j] = 256 + 512 + drzewa;
				drzewa++;
			}
			if (z == 'F' && drzewa < 2000) {
				placeG[i][j] = 118;
				place[i][j] = 256 + 512 + drzewa;
				drzewa++;
			}
			if (z == 'G' && drzewa < 2000) {
				placeG[i][j] = 119;
				place[i][j] = 256 + 512 + drzewa;
				drzewa++;
			}
			//---- PASTWISKO I MIEJSCE ZBIORKI
			if (z == '?') {
				// mem.xz = i;
				// mem.yz = j;
			}
			if (z == '-') {
				// mem.xp = i;
				// mem.yp = j;
				xpastw = i;
				ypastw = j;
			}
			//---start
			if (z == '=') {
				ScreenX = i;
				ScreenY = j;
			}
			//----- zamki -----------
			if (z == 'H') {
				if (chatki < 19) {
					buildingInit(&castle[0].b[chatki], i, j, 11, 1, chatki);
					castle[0].b[chatki].exist = 1;
					castle[0].b[chatki].hp = castle[0].b[chatki].maxhp;
					chatki++;
				}
			}
			if (z == 'I') {
				if (chatki < 19) {
					buildingInit(&castle[0].b[chatki], i, j, 12, 1, chatki);
					chatki++;
				}
			}
			if (z == 'J') // koszary
			{
				if (chatki < 19) {
					buildingInit(&castle[0].b[chatki], i, j, 13, 1, chatki);
					chatki++;
				}
			}
			if (z == 'K') // swiatynia
			{
				if (chatki < 19) {
					buildingInit(&castle[0].b[chatki], i, j, 14, 1, chatki);
					chatki++;
				}
			}
			if (z == 'L') // KOSZAARY 2
			{
				if (chatki < 19) {
					buildingInit(&castle[0].b[chatki], i, j, 15, 1, chatki);
					chatki++;
				}
			}
			if (z == 'M') // DOM BOH
			{
				if (chatki < 19) {
					buildingInit(&castle[0].b[chatki], i, j, 16, 1, chatki);
					chatki++;
				}
			}
			// KROWA NASZA
			if (z == 'x' && p0 < 39) {
				p0++;
				moverInit(&castle[0].m[p0], 0, i, j, 0, 5);
				moverSetNr(&castle[0].m[p0], 256 + p0 + 200);
				moverSetIFF(&castle[0].m[p0], 1);
				moverShow(&castle[0].m[p0]);
			}
			if (z == 'y' && p0 < 39) {
				p0++;
				moverInit(&castle[0].m[p0], 1, i, j, 0, 5);
				moverSetNr(&castle[0].m[p0], 256 + p0 + 200);
				moverSetIFF(&castle[0].m[p0], 1);
				moverShow(&castle[0].m[p0]);
			}
			if (z == 'z' && p0 < 39) {
				p0++;
				moverInit(&castle[0].m[p0], 2, i, j, 0, 5);
				moverSetNr(&castle[0].m[p0], 256 + p0 + 200);
				moverSetIFF(&castle[0].m[p0], 1);
				moverShow(&castle[0].m[p0]);
			}
			if (z == '9' && p0 < 39) {
				p0++;
				moverInit(&castle[0].m[p0], 3, i, j, 0, 5);
				moverSetNr(&castle[0].m[p0], 256 + p0 + 200);
				moverSetIFF(&castle[0].m[p0], 1);
				moverShow(&castle[0].m[p0]);
			}
			if (z == '0' && p0 < 39) {
				p0++;
				moverInit(&castle[0].m[p0], 4, i, j, 0, 5);
				moverSetNr(&castle[0].m[p0], 256 + p0 + 200);
				moverSetIFF(&castle[0].m[p0], 1);
				moverShow(&castle[0].m[p0]);
			}
			if (z == ':' && p0 < 39) {
				p0++;
				moverInit(&castle[0].m[p0], 5, i, j, 0, 5);
				moverSetNr(&castle[0].m[p0], 256 + p0 + 200);
				moverSetIFF(&castle[0].m[p0], 1);
				moverShow(&castle[0].m[p0]);
			}
			if (z == ';' && p0 < 39) {
				p0++;
				moverInit(&castle[0].m[p0], 6, i, j, 0, 5);
				moverSetNr(&castle[0].m[p0], 256 + p0 + 200);
				moverSetIFF(&castle[0].m[p0], 1);
				moverShow(&castle[0].m[p0]);
			}
			if (z == '<' && p0 < 39) {
				p0++;
				moverInit(&castle[0].m[p0], 7, i, j, 0, 5);
				moverSetNr(&castle[0].m[p0], 256 + p0 + 200);
				moverSetIFF(&castle[0].m[p0], 1);
				moverShow(&castle[0].m[p0]);
			}
			if (z == '>' && p0 < 39) {
				p0++;
				moverInit(&castle[0].m[p0], 8, i, j, 0, 5);
				moverSetNr(&castle[0].m[p0], 256 + p0 + 200);
				moverSetIFF(&castle[0].m[p0], 1);
				moverShow(&castle[0].m[p0]);
			}
			if (z == ',' && p0 < 39) {
				p0++;
				moverInit(&castle[0].m[p0], 9, i, j, 0, 5);
				moverSetNr(&castle[0].m[p0], 256 + p0 + 200);
				moverSetIFF(&castle[0].m[p0], 1);
				moverShow(&castle[0].m[p0]);
			}
			if (z == 176 && p0 < 39) // 176  nasz Pastuch
			{
				p0++;
				moverInit(&castle[0].m[p0], 10, i, j, 0, 5);
				moverSetNr(&castle[0].m[p0], 256 + p0 + 200);
				moverSetIFF(&castle[0].m[p0], 1);
				moverShow(&castle[0].m[p0]);
			}
			if (z == 177 && p0 < 39) // 177 nasz Mag
			{
				p0++;
				moverInit(&castle[0].m[p0], 11, i, j, 0, 5);
				moverSetNr(&castle[0].m[p0], 256 + p0 + 200);
				moverSetIFF(&castle[0].m[p0], 1);
				moverShow(&castle[0].m[p0]);
			}
			if (z == 178 && p0 < 39) //  178  nasz Kusznik
			{
				p0++;
				moverInit(&castle[0].m[p0], 12, i, j, 0, 5);
				moverSetNr(&castle[0].m[p0], 256 + p0 + 200);
				moverSetIFF(&castle[0].m[p0], 1);
				moverShow(&castle[0].m[p0]);
			}
			//-----------------------------------------------------------------
			if (z == 'N') {
				if (chaTki < 19) {
					buildingInit(&castle[1].b[chaTki], i, j, 11, 2, chaTki);
					chaTki++;
				}
			}
			if (z == 'O') {
				if (chaTki < 19) {
					buildingInit(&castle[1].b[chaTki], i, j, 12, 2, chaTki);
					chaTki++;
				}
			}
			if (z == 'P') {
				if (chaTki < 19) {
					buildingInit(&castle[1].b[chaTki], i, j, 13, 2, chaTki);
					chaTki++;
				}
			}
			if (z == 'Q') // swiatynia
			{
				if (chaTki < 19) {
					buildingInit(&castle[1].b[chaTki], i, j, 14, 2, chaTki);
					chaTki++;
				}
			}
			if (z == 'R') // koszary2
			{
				if (chaTki < 19) {
					buildingInit(&castle[1].b[chaTki], i, j, 15, 2, chaTki);
					chaTki++;
				}
			}
			if (z == 'S') // akademia
			{
				if (chaTki < 19) {
					buildingInit(&castle[1].b[chaTki], i, j, 16, 2, chaTki);
					chaTki++;
				}
			}
			//-----------------------------------------------------
			if (z == 'T' && p1 < 39) {
				p1++;
				moverInit(&castle[1].m[p1], 0, i, j, 0, 5);
				moverSetNr(&castle[1].m[p1], 512 + p1 + 200);
				moverSetIFF(&castle[1].m[p1], 2);
				moverShow(&castle[1].m[p1]);
			}
			if (z == 'U' && p1 < 39) {
				p1++;
				moverInit(&castle[1].m[p1], 1, i, j, 0, 5);
				moverSetNr(&castle[1].m[p1], 512 + p1 + 200);
				moverSetIFF(&castle[1].m[p1], 2);
				moverShow(&castle[1].m[p1]);
			}
			if (z == 'W' && p1 < 39) {
				p1++;
				moverInit(&castle[1].m[p1], 2, i, j, 0, 5);
				moverSetNr(&castle[1].m[p1], 512 + p1 + 200);
				moverSetIFF(&castle[1].m[p1], 2);
				moverShow(&castle[1].m[p1]);
			}
			if (z == 'X' && p1 < 39) {
				p1++;
				moverInit(&castle[1].m[p1], 3, i, j, 0, 5);
				moverSetNr(&castle[1].m[p1], 512 + p1 + 200);
				moverSetIFF(&castle[1].m[p1], 2);
				moverShow(&castle[1].m[p1]);
			}
			if (z == 'Y' && p1 < 39) {
				p1++;
				moverInit(&castle[1].m[p1], 4, i, j, 0, 5);
				moverSetNr(&castle[1].m[p1], 512 + p1 + 200);
				moverSetIFF(&castle[1].m[p1], 2);
				moverShow(&castle[1].m[p1]);
			}
			if (z == 'Z' && p1 < 39) {
				p1++;
				moverInit(&castle[1].m[p1], 5, i, j, 0, 5);
				moverSetNr(&castle[1].m[p1], 512 + p1 + 200);
				moverSetIFF(&castle[1].m[p1], 2);
				moverShow(&castle[1].m[p1]);
			}
			if (z == '#' && p1 < 39) {
				p1++;
				moverInit(&castle[1].m[p1], 6, i, j, 0, 5);
				moverSetNr(&castle[1].m[p1], 512 + p1 + 200);
				moverSetIFF(&castle[1].m[p1], 2);
				moverShow(&castle[1].m[p1]);
			}
			if (z == '"' && p1 < 39) {
				p1++;
				moverInit(&castle[1].m[p1], 7, i, j, 0, 5);
				moverSetNr(&castle[1].m[p1], 512 + p1 + 200);
				moverSetIFF(&castle[1].m[p1], 2);
				moverShow(&castle[1].m[p1]);
			}
			if (z == '%' && p1 < 39) {
				p1++;
				moverInit(&castle[1].m[p1], 8, i, j, 0, 5);
				moverSetNr(&castle[1].m[p1], 512 + p1 + 200);
				moverSetIFF(&castle[1].m[p1], 2);
				moverShow(&castle[1].m[p1]);
			}
			if (z == '&' && p1 < 39) {
				p1++;
				moverInit(&castle[1].m[p1], 9, i, j, 0, 5);
				moverSetNr(&castle[1].m[p1], 512 + p1 + 200);
				moverSetIFF(&castle[1].m[p1], 2);
				moverShow(&castle[1].m[p1]);
			}
			if (z == 173 && p1 < 39) // 173          pastuch
			{
				p1++;
				moverInit(&castle[1].m[p1], 10, i, j, 0, 5);
				moverSetNr(&castle[1].m[p1], 512 + p1 + 200);
				moverSetIFF(&castle[1].m[p1], 2);
				moverShow(&castle[1].m[p1]);
			}
			if (z == 174 && p1 < 39) // 174    Mag
			{
				p1++;
				moverInit(&castle[1].m[p1], 11, i, j, 0, 5);
				moverSetNr(&castle[1].m[p1], 512 + p1 + 200);
				moverSetIFF(&castle[1].m[p1], 2);
				moverShow(&castle[1].m[p1]);
			}
			if (z == 175 && p1 < 39) // 175            kusznik
			{
				p1++;
				moverInit(&castle[1].m[p1], 12, i, j, 0, 5);
				moverSetNr(&castle[1].m[p1], 512 + p1 + 200);
				moverSetIFF(&castle[1].m[p1], 2);
				moverShow(&castle[1].m[p1]);
			}
		}
	}

	fileClose(pFileMaps);
	// mem.faza = 0;
	castle[0].maxmilk = pl.maxmilk;
	castle[0].milk = pl.maxmilk;
	castle[1].maxmilk = 1800;
	castle[1].milk = 1800;
	drzewa0 = drzewa + 256 + 512;
}

static void battleInitNewLevel(UWORD uwLevel) {
	char name[40];
	int p0 = 1, p1 = 1;
	int chatki = 1, chaTki = 1;

	sprintf(name, "data/levels/level.%d", uwLevel);
	logWrite("Otwieram plik: %s\n", name);

	tFile *pFileMaps = diskFileOpen(name, DISK_FILE_MODE_READ, 0);
	if (pFileMaps == NULL) {
		logWrite("ERR: Sorry bracie ale nie znalazlem pliku %s.", name);
		return;
	}

	// OutText13h(50,15,"Czytam nagl%wek",255);
	fileSeek(pFileMaps, WORLD_SIZE_X * WORLD_SIZE_Y * 4, SEEK_SET);
	// FIXME: this probably won't work due to struct alignment differences.
	// Change to reading field by field + endian convert.
	fileRead(pFileMaps, &E, sizeof(E));

	// sprintf(name,"x:%d,y:%d,tp:%d,wk:%d,",E.X,E.Y,E.typPlanszy,E.warunekKonca);
	// OutText13h(50,25,name,255);
	// getch();
	ScreenX = E.X;
	ScreenY = E.Y;
	pl.decisionType = E.typPlanszy;
	pl.endType = E.warunekKonca;
	pl.xp = 0;
	pl.yp = 0;
	// color2 = E.color;
	// switch (E.color) {
	// case 0:
	//   color2 = DarkBlue;
	//   break;
	// case 1:
	//   color2 = DarkYellow;
	//   break;
	// case 2:
	//   color2 = DarkGreen;
	//   break; //
	// case 3:
	//   color2 = LightGray;
	//   break;
	// }
	pl.typ = E.postac;
	pl.gen = E.generator;
	pl.maxmilk = E.maxmilk;
	strcpy(pl.name, E.pName);
	if (pl.endType == 4 && !p1)
		p1 = 1;

	/// OutText13h(50,170,"Ustawiam na zero",255);
	int typ = fileSeek(pFileMaps, 0, SEEK_SET);
	// if(typ)OutText13h(50,120,"Blad",255);
	// OutText13h(50,180,"Czytam dane",255);

	for (UBYTE j = 0; j < WORLD_SIZE_Y; j++)
		for (UBYTE i = 0; i < WORLD_SIZE_X; i++) {
			ULONG ulReadG;
			typ = fileRead(pFileMaps, &ulReadG, sizeof(ulReadG));
			ulReadG = endianLittle32(ulReadG);
			placeG[i][j] = ulReadG;

			if (placeG[i][j] < 8)
				placeG[i][j] = 8;
			if (placeG[i][j] == 329) // postac do uratowania
			{
				if (pl.endType == 1) {
					place[i][j] = 10;
					pl.x0 = i;
					pl.y0 = j;
				}
				if (pl.endType == 4) {
					if (!p1)
						p1++;
					moverInit(&castle[1].m[1], pl.typ, i, j, 0, 5);
					moverSetNr(&castle[1].m[1], 512 + 201);
					moverSetIFF(&castle[1].m[1], 2);
					moverShow(&castle[1].m[1]);
				}
			}
			if (placeG[i][j] == 301) // krag mocy
			{
				pl.xw = i;
				pl.yw = j;
				placeG[i][j] = 301;
			}
			if (placeG[i][j] == 328) // rozjasnienie
			{
				placeN[i][j] = 1;
				placeN[i + 1][j] = 1;
				placeN[i + 1][j + 1] = 1;
				placeN[i][j + 1] = 1;
				placeG[i][j] = 8;
			}

			if (placeG[i][j] == 58)
				place[i][j] = 10;
			if (placeG[i][j] > 59 && placeG[i][j] < 67)
				place[i][j] = 10;
			if (placeG[i][j] == 68)
				place[i][j] = 10;
			if (placeG[i][j] == 69)
				place[i][j] = 10;
			// skaly
			if (placeG[i][j] > 8 && placeG[i][j] < 17)
				place[i][j] = 10;
			if (placeG[i][j] > 17 && placeG[i][j] < 22)
				place[i][j] = 10;

			if (placeG[i][j] == 331) {
				placeG[i][j] = 256;
				xleczenie = i;
				yleczenie = j;
			}
			if (placeG[i][j] == 300) {
				pl.xp = i;
				pl.yp = j;
				placeG[i][j] = 300;
			}

			if (placeG[i][j] > 73 && placeG[i][j] < 87) // woda
			{
				place[i][j] = 1;
			}
			if (placeG[i][j] > 265 && placeG[i][j] < 278) // palisada
			{
				place[i][j] = 256 + 512 + drzewa;
				drzewa++;
			}
			// ---------drzewa ---------------
			if ((placeG[i][j] > 112 && placeG[i][j] < 120) ||
					placeG[i][j] == 71 || placeG[i][j] == 73) {
				place[i][j] = 256 + 512 + drzewa;
				drzewa++;
			}

			//---- PASTWISKO I MIEJSCE ZBIORKI
			if (placeG[i][j] == 333) // zbiorka
			{
				// mem.xz = i;
				// mem.yz = j;
				placeG[i][j] = 8;
			}
			if (placeG[i][j] == 330) // pastwisko
			{
				// mem.xp = i;
				// mem.yp = j;
				xpastw = i;
				ypastw = j;
				placeG[i][j] = 8;
			}
			//----- zamki I POSTACIE -----------

			switch (placeG[i][j]) {
			case 145: // nasz budynek glowny
			case 165: // nasza obora
			case 185:
			case 205:
			case 225:
			case 245:
				typ = 1 + (placeG[i][j] - 145) / 20;
				if (chatki < 19 && typ > 0 && typ < 7) {
					buildingInit(&castle[0].b[chatki], i, j, 10 + typ, 1, chatki);
					castle[0].b[chatki].exist = 1;
					castle[0].b[chatki].hp = castle[0].b[chatki].maxhp;
					chatki++;
				} else {
					for (int xx = -2; xx < 1; xx++)
						for (int yy = -2; yy < 1; yy++)
							placeG[i + xx][j + yy] = 8;
				}
				break;

			case 302: // KROWA NASZA
			case 303:
			case 304:
			case 305:
			case 306:
			case 307:
			case 308:
			case 309:
			case 310:
			case 311:
			case 312:
			case 313:
			case 314: // kusznik
				if (p0 < 39) {
					p0++;
					moverInit(&castle[0].m[p0], placeG[i][j] - 302, i, j, 0, 5);
					moverSetNr(&castle[0].m[p0], 256 + p0 + 200);
					moverSetIFF(&castle[0].m[p0], 1);
					moverShow(&castle[0].m[p0]);
				}
				placeG[i][j] = 8;
				break;

			case 155: // ich budynek glowny
			case 175: // ich obora
			case 195:
			case 215:
			case 235:
			case 255:
				typ = 1 + (placeG[i][j] - 155) / 20;
				if (chaTki < 19) {
					buildingInit(&castle[1].b[chaTki], i, j, 10 + typ, 2, chaTki);
					chaTki++;
				}
				else {
					for (int xx = -2; xx < 1; xx++) {
						for (int yy = -2; yy < 1; yy++) {
							placeG[i + xx][j + yy] = 8;
						}
					}
				}
				break;
			case 315: // ich krowa
			case 316:
			case 317:
			case 318:
			case 319:
			case 320:
			case 321:
			case 322:
			case 323:
			case 324:
			case 325:
			case 326:
			case 327:
				if (p1 < 39) {
					p1++;
					moverInit(&castle[1].m[p1], placeG[i][j] - 315, i, j, 0, 5);
					moverSetNr(&castle[1].m[p1], 512 + p1 + 200);
					moverSetIFF(&castle[1].m[p1], 2);
					moverShow(&castle[1].m[p1]);
				}
				placeG[i][j] = 8;
				break;
			}

			if (placeG[i][j] > 301)
				placeG[i][j] = 8;
		}

	fileClose(pFileMaps);
	// mem.faza = 0;
	castle[0].maxmilk = E.maxmilk;
	castle[0].milk = E.milk;
	castle[1].maxmilk = 1800;
	castle[1].milk = 1800;
}

static void battleInitLevel(UWORD uwLevel, UBYTE isLoadGame) {
	endL = 0;
	// if (!isLoadGame) {
	//   if (uwLevel < 26) {
	//     switch (prowintion[uwLevel - 1]) {
	//     case 1:
	//     case 4:
	//       color2 = DarkBlue;
	//       break;
	//     case 3:
	//       color2 = DarkYellow;
	//       break;
	//     case 2:
	//       color2 = DarkGreen;
	//       break; //
	//     case 5:
	//       color2 = LightGray;
	//       break;
	//     }
	//   }
	//   if (uwLevel > 25)
	//     color2 = Yellow;
	// }

	// if (uwLevel == 15) {
	//   prowintionA[18] = 1;
	//   prowintionA[10] = 1; // 11,14,16,19
	//   prowintionA[13] = 1;
	//   prowintionA[15] = 1;
	// }

	// for (int d1 = 0; d1 < 10; d1++)
	//   for (int d2 = 0; d2 < 10; d2++) {
	//     posTT[d1][d2][0] = 0;
	//     posTT[d1][d2][1] = 20;
	//   }
	// for (i = 0; i < 10; i++)
	//   posT[i].IFF = 2;

	for(UBYTE c = 0; c < 2; ++c) {
		for(UBYTE m = 0; m < CASTLE_MOVERS_MAX; ++m) {
			moverConstruct(&castle[c].m[m]);
		}
		for(UBYTE b = 0; b < CASTLE_BUILIDNGS_MAX; ++b) {
			for(UBYTE m = 0; m < BUILDING_MOVERS_MAX; ++m) {
				moverConstruct(&castle[c].b[b].m[m]);
			}
		}
	}

	if (!isLoadGame) {
		drzewa = 1;
		pl.nrp = 0;
		pl.haslo = 132;
		pl.next = 0;
		pl.tp = 0;
		pl.x0 = 0;
		pl.xp = 0;
		pl.yp = 0;
		pl.gen = 0;
		for (UBYTE i = 0; i < WORLD_SIZE_X; i++)
			for (UBYTE j = 0; j < WORLD_SIZE_Y; j++) {
				placeN[i][j] = 0;
				placeG[i][j] = 8;
				place[i][j] = 0;
			}

		castleInit(&castle[0], 1, 2000);
		castleInit(&castle[1], 2, 2000);
		ScreenX = 10;
		ScreenY = 10;

		if (uwLevel < 26) {
			battleInitOldLevel(uwLevel);
		}
		else {
			battleInitNewLevel(uwLevel);
		}
	}
	if (ScreenX < 1)
		ScreenX = 1;
	if (ScreenY < 1)
		ScreenY = 1;
	if (ScreenX > WORLD_SIZE_X - 16)
		ScreenX = WORLD_SIZE_X - 16;
	if (ScreenY > WORLD_SIZE_Y - 14)
		ScreenY = WORLD_SIZE_Y - 14;
	if (uwLevel < 26) {
		for (UBYTE i = 1; i < WORLD_SIZE_X - 1; i++)
			for (UBYTE j = 1; j < WORLD_SIZE_Y - 1; j++) {
				if (PICTURE_KIND_ROAD_5 < placeG[i][j] && placeG[i][j] <= PICTURE_KIND_ROAD_20)
					worldPlaceRoad(i, j, PICTURE_KIND_ROAD_10); // droga
				if (PICTURE_KIND_WALL_0 <= placeG[i][j] && placeG[i][j] < PICTURE_KIND_WALL_11)
					worldPlaceRoad(i, j, PICTURE_KIND_WALL_0); // palisada
				if (PICTURE_KIND_WATER_0 <= placeG[i][j] && placeG[i][j] < PICTURE_KIND_WATER_13)
					worldPlaceWater(i, j, PICTURE_KIND_WATER_0);
				if (placeG[i][j] == PICTURE_KIND_DRY_EARTH_0)
					placeG[i][j] = PICTURE_KIND_DRY_EARTH_0 + (i & 1) + (j & 1); // sucha ziemia
			}
	}
	drzewa0 = drzewa + 256 + 512;
	placeG[xleczenie][yleczenie] = 256;
	// strcpy(Msg.msg, "Zaczynajmy !");
	// Msg.licznik = 50;
	// Msg.dzwiek = 0;
}

static void battleGsCreate(void) {
	s_pBattleUi = bitmapCreateFromPath("data/battle_ui.bm", 0);
	buttonCreate();
	moverGraphicsCreate();
	pictureCreate();
	missileImageCreate();
	miscCreate();
	paletteLoadFromPath("data/battle.plt", g_pVp->pPalette, 32);

#ifdef SHAREWARE
	for (int i = 0; i < 52; i++)
		Track[i] = 2 + (i & 1);
#endif
	pl.nrh = 0;
	// color1 = Red;

	// licznik2 = 0;
	// if (type < START_KIND_SAVED_GAME) {
	// 	PlayTrack(TRACK_TXT);
	// 	ShowText(level, 0);
	// } else
	// 	DownPalette(2);

	// StopPlaying();
	// kody = 0;
	if (eStartKind != START_KIND_SAVED_GAME) {
		battleInitLevel(g_uwLevel, 0);
	} else {
		battleInitLevel(g_uwLevel, 1);
		eStartKind = START_KIND_SINGLEPLAYER;
	}
	// chat = 100;
	// if (type > START_KIND_SINGLEPLAYER)
	// 	type = START_KIND_SINGLEPLAYER;

	// SetScreen(1);
	battleShowBackground();
	battleShowPanel(0, 0, 0, 0, 0);
	// if (Map)
	// 	PressButton(16, 2);
	// else
	// 	PressButton(16, 3);
	gfxDrawImageNoMask(275, 139, &buttons[BUTTON_KIND_MAP]);
	gfxCopyBackToFront();

	// PlayTrack(Track[level - 1]);
	// quitLevel = 0; //   screen=1
	// selectM = &castle[master].m[1];
	// select.co = 1;
	// select.nrb = 1;
	// select.nrm = 1;
	// select.IFF = 2;
	// mouseCommand = 1;

	worldRevealAll();

	castleRun(&castle[0]);
	castleRun(&castle[1]);
	castlePrepare(&castle[0], ScreenX, ScreenY, 1);
	castlePrepare(&castle[1], ScreenX, ScreenY, 1);
	battleRefreshScreen();
	battleShowSelected();
	// LoadExtendedPalette(3);
	// RisePalette(1);

	// mem.faza = 0;
	// mouseMode = 0;
	// Msg.ddzwiek = 0;

	systemUnuse();
	viewLoad(g_pVp->pView);
	systemSetDmaBit(DMAB_SPRITE, 1);
}

static void battleScroll(void) {
  // if (scrollTimer + (5 - skroller) > licznik)
  //   return;

  // scrollTimer = licznik;
  // if(skroller1>skroller){return;}

	UWORD uwMouseX = mouseGetX(MOUSE_PORT_1);
	UWORD uwMouseY = mouseGetY(MOUSE_PORT_1);

  if (uwMouseX < 10) {
    ScreenX--;
    if (ScreenX < 1) {
      ScreenX = 1;
      return;
    }
    castlePrepare(&castle[0], ScreenX, ScreenY, 0);
    castlePrepare(&castle[1], ScreenX, ScreenY, 0);
    // skroller1++;
    battleRefreshScreen();
  }
  if (uwMouseX > 310) {
    ScreenX++;
    if (ScreenX > WORLD_SIZE_X - 17) {
      ScreenX = WORLD_SIZE_X - 17;
      return;
    }
    castlePrepare(&castle[0], ScreenX, ScreenY, 0);
    castlePrepare(&castle[1], ScreenX, ScreenY, 0);
    // skroller1++;
    battleRefreshScreen();
  }
  if (uwMouseY < 8) {
    ScreenY--;
    if (ScreenY < 1) {
      ScreenY = 1;
      return;
    }
    castlePrepare(&castle[0], ScreenX, ScreenY, 0);
    castlePrepare(&castle[1], ScreenX, ScreenY, 0);
    // skroller1++;
    battleRefreshScreen();
    return;
  }
  if (uwMouseY > 192 - 7) {
    ScreenY++;
    if (ScreenY > WORLD_SIZE_Y - 14) {
      ScreenY = WORLD_SIZE_X - 14;
      return;
    }
    castlePrepare(&castle[0], ScreenX, ScreenY, 0);
    castlePrepare(&castle[1], ScreenX, ScreenY, 0);
    // skroller1++;
    battleRefreshScreen();
    return;
  }
}

static void battleGsLoop(void) {
	if(keyUse(KEY_ESCAPE)) {
		stateChange(g_pStateMachineGame, &g_sStateMenu);
		return;
	}
	else if(keyUse(KEY_F1)) {
		worldDump(0, 0, WORLD_SIZE_X, WORLD_SIZE_Y);
	}
	else if(keyUse(KEY_F2)) {
		worldDump(ScreenX, ScreenY, WORLD_WINDOW_SIZE_X, WORLD_WINDOW_SIZE_Y);
	}

// 	do {
// 		decisionFaza++;
// 		if (decisionFaza == 6) {
// 			switch (pl.decisionType) {
// 			case 0:
// 				Decision();
// 				break;
// 			case 1:
// 				DecisionB();
// 				break;
// 			case 2:
// 				DecisionS();
// 				break;
// 			}
// 			if (pl.gen)
// 				Generator();
// 			decisionFaza = 0;
// 			CheckCD();
// 		}
// 		if (grupa == 1 && Cmd[0].co == 1)
// 			Cmd[0].co = 3;
// 		castle[0].SetCmd(&Cmd[0]);
// 		castle[1].SetCmd(&Cmd[1]);

		castleRun(&castle[0]);
		castleRun(&castle[1]);
		castlePrepare(&castle[0], ScreenX, ScreenY, 1);
		castlePrepare(&castle[1], ScreenX, ScreenY, 1);

// 		// clear commmand
// 		Cmd[1].co = 5;
// 		Cmd[0].co = 5;
// 		ClearAttack();
// 		if (pl.endType == 1 && placeN[pl.x0][pl.y0] && pl.x0) {
// 			castle[0].m[1].Init(pl.typ, pl.x0, pl.y0, 0, 0);
// 			castle[0].m[1].SetIFF(1);
// 			castle[0].m[1].SetNr(1 + 456);
// 			castle[0].m[1].Show();
// 			pl.x0 = 0;
// 			placeN[pl.x0][pl.y0] = 1;
// 		}
// 		if (placeG[pl.xp][pl.yp] == 300 && place[pl.xp][pl.yp] > 256 &&
// 				place[pl.xp][pl.yp] < 768) // przemiana
// 		{
// 			Mover1 *mm = Pointer(place[pl.xp][pl.yp]);
// 			if (mm != NULL) {
// 				mm->type = 8;
// 				mm->s_range = Udata[8][0];
// 				mm->a_range = Udata[8][1];
// 				mm->damage = Udata[8][2];
// 				mm->armour = Udata[8][3];
// 				mm->maxhp = Udata[8][4];
// 				mm->maxdelay = Udata[8][5];
// 				mm->magic = 0;
// 				if (mm->hp > mm->maxhp)
// 					mm->hp = mm->maxhp;
// 			}
// 		}
// 		if (mouseP > 3)
// 			mouseP = 0;
// 		else
// 			mouseP++;
// 		if (Msg.count == 6)
// 			Msg.count = 0;
// 		if (Msg.count)
// 			Msg.count--;

// 		if (mouseCounter > 0)
// 			mouseCounter--;
// 		if (mouseCounter == 1 ||
// 				(!mouseCounter && mouseCommand == 1)) // wypisz panel
// 			if (select.IFF < 1) {
// 				int comm = 0;
// 				if (select.co == 1) {
// 					int comm = 0;
// 					if (selectM->type && selectM->command == 5)
// 						comm = 1;
// 					if (selectM->type == 1 && selectM->command == 8)
// 						comm = 3;
// 					if ((selectM->type == 3 || selectM->type == 4) &&
// 							selectM->command == 7)
// 						comm = 3;
// 					battleShowPanel(select.IFF, selectM->type, 1, selectM->magic, comm);
// 				}
// 				if (select.co == 0) {
// 					if (selectB->exist == 1)
// 						comm = castle[0].milk;
// 					battleShowPanel(select.IFF, selectB->type + PANEL_BUTTON_Y(0) + 1, comm,
// 										selectB->maxfood - selectB->food, 0);
// 				}
// 			} else {
// 				battleShowPanel(0, 0, 0, 0, 0);
// 			}

// 		battlePlayMsgSound();

// 		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 		do {
// 			if (Map && MapY < 64)
// 				MapY++;
// 			if (Map && MapY < 64)
// 				MapY++;
// 			if (!Map && MapY)
// 				MapY--;
// 			if (!Map && MapY)
// 				MapY--;
// 			if (!zaznaczanie)
				battleScroll();
			battleShowSelected();
// 			i = mouse.GetMsg13h();
// 			ile0 = mouse.Ile(0);
// 			ile1 = mouse.Ile(1);
// 			if (i || ile0 || ile1)
// 				DispatchEvent();
// 			if (zaznaczanie && !mouse.Button) {
// 				zaznaczanie = 0;
// 				ZaznaczObiekt(rx1, ry1, rx2, ry2, 0);
// 				rx2 = rx1;
// 				ry2 = ry1;
// 			}
// #ifdef bez_zegara
// 			licznik++;
// #endif

// 		} while (licznik - licznik2 < speed);
// 		showAll = 1;
// 		//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// 		if (licznik > 10000) {
// 			licznik = 0;
// 			scrollTimer = licznik;
// 		}
// 		licznik2 = licznik;

// 		if (pl.ide)
// 			pl.ide--;
// 		if (Msg.licznik)
// 			Msg.licznik--;
// 		if (decisionFaza == 2 && !quitLevel)
// 			endL = EndLevel();
// 	} while (!quitLevel && !endL);

	UWORD uwX = mouseGetX(MOUSE_PORT_1);
	UWORD uwY = mouseGetY(MOUSE_PORT_1);
	g_pMouseSprite->wX = (WORD)uwX - 1;
	g_pMouseSprite->wY = (WORD)uwY - 1;
	spriteRequestMetadataUpdate(g_pMouseSprite);
	spriteProcess(g_pMouseSprite);

	vPortProcessManagers(g_pVp);
	copProcessBlocks();
	systemIdleBegin();
	vPortWaitForEnd(g_pVp);
	systemIdleEnd();
}

static void battleGsDestroy(void) {
	castleFreeUnits(&castle[0]);
	castleFreeUnits(&castle[1]);
// 	SetScreen(0);
// 	if (endL == 1) {
// 		PlayTrack(TRACK_VICTORY);
// 		ShowText(level, 1);
// 		if (level < 26) {
// #ifdef SHAREWARE
// 			quitLevel = 1; // koniec scenariusza
// #else
// 			prowintion[level - 1] = 1;
// 			prowintionA[level - 1] = 0;
// 			if (pl.next)
// 				prowintionA[pl.next - 1] = 1;
// 			j = 0;
// 			for (i = 0; i < 25; i++)
// 				j += prowintion[i];
// 			if (j == 25)
// 				quitLevel = 2;
// 			else
// 				NextConquest();
// #endif
// 		} else {
// #ifdef SHAREWARE
// 			quitLevel = 1; // koniec scenariusza
// #else
// 			if (level == 30 || level == 35 || level == 41 || level == 46 ||
// 					level == 52)
// 				quitLevel = 1; // koniec scenariusza
// 			else
// 				level++;
// #endif
// 		}
// 	}

// 	if (endL == 2) {
// 		PlayTrack(TRACK_DEFEAT);
// 		ShowText(level, 2);
// 		if (level == 15 || level > 25) {
// 		} else
// 			NextConquest();
// 	}
// 	if (quitLevel == 2) {
// 		PlayTrack(TRACK_VICTORY);
// 		ShowText(2, 3);
// 		ShowText(3, 3);
// 		ShowText(4, 3);
// 		ShowText(5, 3);
// 		quitLevel = 1;
// 	} // zakonczenie gry

	systemSetDmaBit(DMAB_SPRITE, 0);
	viewLoad(0);
	systemUse();
	moverGraphicsDestroy();
	pictureDestroy();
	missileImageDestroy();
	miscDestroy();
	buttonDestroy();
	bitmapDestroy(s_pBattleUi);
}

void battleStartNewLevel(UWORD uwLevelIndex, tDifficulty eDifficulty) {
	g_uwLevel = uwLevelIndex;
	g_eDifficulty = eDifficulty;
	stateChange(g_pStateMachineGame, &g_sStateBattle);
}

void battleLoadFromSlot(UBYTE ubSlotIndex) {
	(void)ubSlotIndex;
	statePush(g_pStateMachineGame, &g_sStateBattle);
}

tDifficulty g_eDifficulty;

tState g_sStateBattle = {
	.cbCreate = battleGsCreate,
	.cbLoop = battleGsLoop,
	.cbDestroy = battleGsDestroy
};
