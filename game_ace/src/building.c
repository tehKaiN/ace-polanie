#include "building.h"
#include <ace/managers/log.h>
#include "castle.h"
#include "world.h"
#include "picture.h"
#include "battle.h"

void buildingInit(tBuilding *pBuilding, int x0, int y0, tBuildingKind eKind, tMapObjectTeam eTeam, UBYTE isFullyBuilt) {
	if(eKind > BUILDING_KIND_COUNT) {
		logWrite("ERR: building kind out of range: %d", eKind);
	}

	pBuilding->exist = 4;
	if (eKind > 10) {
		eKind -= 10;
		// Nr += 300; // wtf?
	}
	pBuilding->type = eKind;
	switch (pBuilding->type) {
		case BUILDING_KIND_UNK:
			pBuilding->maxfood = 0;
			pBuilding->maxhp = 400;
			break;
		case BUILDING_KIND_KNIGHT_HUT:
			pBuilding->maxfood = 1;
			pBuilding->maxhp = 400;
			break;
		case BUILDING_KIND_SHED:
		case BUILDING_KIND_MAGE_HUT:
			pBuilding->maxfood = 3;
			pBuilding->maxhp = 350;
			break;
		case BUILDING_KIND_HUT:
			pBuilding->maxfood = 6;
			pBuilding->maxhp = 350;
			break;
		case BUILDING_KIND_WARRIOR_HUT:
			pBuilding->maxfood = 4;
			pBuilding->maxhp = 350;
			break;
		case BUILDING_KIND_COUNT:
			break;
	}
	pBuilding->x = x0 - 2;
	pBuilding->y = y0 - 2;

	pBuilding->armour = 10;
	if (eTeam == MAP_OBJECT_TEAM_PLAYER) {
		pBuilding->maxhp = pBuilding->maxhp >> 1;
	}

	pBuilding->hp = 30;
	pBuilding->sMapObject.eTeam = eTeam;

	tPictureKind ePicTopLeft = PICTURE_KIND_CONSTRUCTION_0;
	if (isFullyBuilt) {
		pBuilding->exist = 1;
		pBuilding->hp = pBuilding->maxhp;
		ePicTopLeft = PICTURE_KIND_BUILDING_0_FULL_0 + (pBuilding->type - 1) * 20;
	}

	pBuilding->faza = 0;
	for (UBYTE i = 0; i < 6; i++) {
		pBuilding->m[i].exist = 0;
		pBuilding->m[i].missile.exist = 0;
	}
	for (UBYTE j = 0; j < 3; j++) {
		for (UBYTE i = 0; i < 3; i++) {
			placeG[pBuilding->x + i][pBuilding->y + j] = ePicTopLeft + i + j * 3;
		}
	}

	if (pBuilding->sMapObject.eTeam == MAP_OBJECT_TEAM_PLAYER) {
		for (UBYTE j = -2; j < 5; j++)
			for (UBYTE i = -2; i < 5; i++) {
				if (pBuilding->x + i > 0 && pBuilding->y + j > 0 && pBuilding->x + i < WORLD_SIZE_X && pBuilding->y + j < WORLD_SIZE_Y)
					if (!placeN[pBuilding->x + i][pBuilding->y + j])
						placeN[pBuilding->x + i][pBuilding->y + j] = 1;
			}
	}

	place[pBuilding->x][pBuilding->y] = &pBuilding->sMapObject;
	place[pBuilding->x + 1][pBuilding->y] = &pBuilding->sMapObject;
	place[pBuilding->x + 2][pBuilding->y] = &pBuilding->sMapObject;

	place[pBuilding->x + 2][pBuilding->y + 1] = &pBuilding->sMapObject;
	place[pBuilding->x][pBuilding->y + 1] = &pBuilding->sMapObject;
	place[pBuilding->x + 1][pBuilding->y + 1] = &pBuilding->sMapObject;

	if (pBuilding->type != BUILDING_KIND_KNIGHT_HUT) {
		place[pBuilding->x + 1][pBuilding->y + 2] = &pBuilding->sMapObject;
	}

	place[pBuilding->x + 2][pBuilding->y + 2] = &pBuilding->sMapObject;

	place[pBuilding->x][pBuilding->y + 2] = 0; // miejsce gdzie rodza sie krowy
}

////////////////////////////////////////////////////////////////////////////

void buildingRun(tBuilding *pBuilding) {
	int i, j, dd = 0;
	if (!pBuilding->exist)
		return;
	// odbudowa
	if (pBuilding->hp < pBuilding->maxhp)
		for (i = pBuilding->x; i < pBuilding->x + 3; i++)
			for (j = pBuilding->y; j < pBuilding->y + 3; j++) {
				if (placeN[i][j] > 219) {
					dd += (placeN[i][j] - 219) * 2;
					if (pBuilding->sMapObject.eTeam == MAP_OBJECT_TEAM_CPU)
						dd += 3;
					placeN[i][j] = 1;
				}
			}

	if (dd) {
		pBuilding->hp += dd;
		if (pBuilding->hp >= pBuilding->maxhp)
			pBuilding->hp = pBuilding->maxhp;
	}

	if (pBuilding->exist == 4 && pBuilding->hp > (pBuilding->maxhp / 2)) // polowa budowy
	{
		for (j = 0; j < 3; j++)
			for (i = 0; i < 3; i++) {
				placeG[pBuilding->x + i][pBuilding->y + j] = 147 + (pBuilding->type - 1) * 20 + i + j * 3;
			}
		pBuilding->exist = 3;
	}

	if (pBuilding->exist == 3 && pBuilding->hp >= pBuilding->maxhp) // koniec budowy
	{
		pBuilding->exist = 1;
		for (j = 0; j < 3; j++)
			for (i = 0; i < 3; i++) {
				placeG[pBuilding->x + i][pBuilding->y + j] = 137 + (pBuilding->type - 1) * 20 + i + j * 3;
			}
		place[pBuilding->x + 1][pBuilding->y + 1] = &pBuilding->sMapObject;
		// if (Msg.dzwiek < 18) {
		// 	Msg.dzwiek = 18;
		// 	Msg.X = pBuilding->x;
		// 	Msg.Y = pBuilding->y;
		// }
	}

	pBuilding->food = 0;
	for (i = 0; i < BUILDING_MOVERS_MAX; i++) {
		moverRun(&pBuilding->m[i]); // uruchom podlegle postacie
		if (pBuilding->m[i].exist) {
			pBuilding->food++;
		}
	}

	if (pBuilding->exist == 2 && !pBuilding->food) {
		pBuilding->exist = 0;
		return;
	} // jezeli zburzony i brak postaci to zniknij
	if (pBuilding->exist != 1)
		pBuilding->food = pBuilding->maxfood;
	//--- sprawdzenie atakow
	dd = 0;
	if (pBuilding->exist == 1 || pBuilding->exist > 2) {
		attack[pBuilding->x + 1][pBuilding->y + 1] = 0;
		for (i = pBuilding->x; i < pBuilding->x + 3; i++)
			for (j = pBuilding->y; j < pBuilding->y + 3; j++)
				if ((i != pBuilding->x) || j < 2 + pBuilding->y) {
					dd += attack[i][j];
					attack[i][j] = 0;
				}

		if (dd > pBuilding->armour)
			dd -= pBuilding->armour;
		else
			dd = 0;
	}
	if (pBuilding->exist == 2)
		dd = 0; // zabitego nie rabac
	if (dd) {
		if (pBuilding->sMapObject.eTeam == MAP_OBJECT_TEAM_PLAYER) {
			// strcpy(Msg.msg, "Wr%g w wiosce !!!");
			// Msg.licznik = 20;
		}
		else if (pBuilding->sMapObject.eTeam == MAP_OBJECT_TEAM_CPU) {
			for (int post = 4; post < CASTLE_MOVERS_MAX; post++) {
				if (castle[1].m[post].type && castle[1].m[post].type < 10)
					castle[1].m[post].drange = 7;
			}
			for (int build = 0; build < CASTLE_BUILIDNGS_MAX; build++) {
				for (UBYTE post = 0; post < BUILDING_MOVERS_MAX; post++) {
					if (castle[1].b[build].m[post].type)
						castle[1].b[build].m[post].drange = 7;
				}
			}
		}
		pBuilding->hp -= dd;
		if (pBuilding->hp <= 0) {
			pBuilding->hp = 0;
			j = 0;
			do {
				for (i = 0; i < 3; i++) {
					placeG[pBuilding->x + i][pBuilding->y + j] = 257 + i + j * 3; // ruina
					if (pBuilding->type != 6 || i != 1 || j != 2)
						if (i || j != 2)
							place[pBuilding->x + i][pBuilding->y + j] = 0;
					placeN[pBuilding->x + i][pBuilding->y + j] = 88;
				}
				j++;
			} while (j < 3);
			placeN[pBuilding->x + 2][pBuilding->y + 2] = 100;
			placeN[pBuilding->x][pBuilding->y] = 81;
			placeN[pBuilding->x][pBuilding->y + 1] = 95;
			placeN[pBuilding->x + 2][pBuilding->y + 2] = 83;
			placeN[pBuilding->x + 2][pBuilding->y] = 81;
			placeN[pBuilding->x][pBuilding->y + 2] = 79;
			pBuilding->exist = 2;
			// if (Msg.dzwiek < 17) {
			// 	Msg.dzwiek = 17;
			// 	Msg.X = pBuilding->x;
			// 	Msg.Y = pBuilding->y;
			// }
		}
	}

	if (pBuilding->exist != 1)
		return;
	if (pBuilding->hp < pBuilding->maxhp)
		placeN[pBuilding->x + 1][pBuilding->y + 1] = 1;
	if (pBuilding->hp < pBuilding->maxhp / 2)
		placeN[pBuilding->x + 1][pBuilding->y + 1] = 74;
	if (pBuilding->hp < pBuilding->maxhp / 4)
		placeN[pBuilding->x + 1][pBuilding->y + 1] = 78;
	if (pBuilding->hp < pBuilding->maxhp / 8)
		placeN[pBuilding->x + 1][pBuilding->y + 1] = 100;

	if (++pBuilding->faza > 4)
		pBuilding->faza = 0;

	// Animate buildings
	// TODO: create table with dx/dy/tile1/tile3 per building type
	if (pBuilding->exist == 1 && pBuilding->faza == 1)
		switch (pBuilding->type) {
			case BUILDING_KIND_UNK:
				placeG[pBuilding->x + 1][pBuilding->y] = 137 + 9;
				break;
			case BUILDING_KIND_SHED:
				placeG[pBuilding->x + 2][pBuilding->y + 1] = 157 + 9;
				break;
			case BUILDING_KIND_HUT:
				placeG[pBuilding->x + 2][pBuilding->y] = 177 + 9;
				break;
			case BUILDING_KIND_MAGE_HUT:
				placeG[pBuilding->x + 1][pBuilding->y + 1] = 197 + 9;
				break;
			case BUILDING_KIND_WARRIOR_HUT:
				placeG[pBuilding->x + 1][pBuilding->y + 1] = 217 + 9;
				break;
			case BUILDING_KIND_KNIGHT_HUT:
				placeG[pBuilding->x + 2][pBuilding->y] = 237 + 9;
				break;
			case BUILDING_KIND_COUNT:
				break;
		}
	if (pBuilding->exist == 1 && pBuilding->faza == 3)
		switch (pBuilding->type) {
			case BUILDING_KIND_UNK:
				placeG[pBuilding->x + 1][pBuilding->y] = 137 + 1;
				break;
			case BUILDING_KIND_SHED:
				placeG[pBuilding->x + 2][pBuilding->y + 1] = 157 + 5;
				break;
			case BUILDING_KIND_HUT:
				placeG[pBuilding->x + 2][pBuilding->y] = 177 + 2;
				break;
			case BUILDING_KIND_MAGE_HUT:
				placeG[pBuilding->x + 1][pBuilding->y + 1] = 197 + 4;
				break;
			case BUILDING_KIND_WARRIOR_HUT:
				placeG[pBuilding->x + 1][pBuilding->y + 1] = 217 + 4;
				break;
			case BUILDING_KIND_KNIGHT_HUT:
				placeG[pBuilding->x + 2][pBuilding->y] = 237 + 2;
				break;
			case BUILDING_KIND_COUNT:
				break;
		}
}

void buildingPrepare(tBuilding *pBuilding, int X, int Y, int typ) {
	int i;
	for (i = 0; i < BUILDING_MOVERS_MAX; i++) {
		moverPrepare(&pBuilding->m[i], X, Y, typ);
	}
}

void buildingShowS(tBuilding *pBuilding, int Xs, int Ys, int what) {
	// TODO: split to separate fns
	switch(what) {
		case 1:
			// pokaz obiekty martwe
			for (UBYTE i = 0; i < BUILDING_MOVERS_MAX; i++) {
				if (pBuilding->m[i].exist == 2)
					moverShowS(&pBuilding->m[i]);
			}
			break;
		case 2:
			// pokaz obiekty zywe
			for (UBYTE i = 0; i < BUILDING_MOVERS_MAX; i++) {
				if (pBuilding->m[i].exist == 1)
					moverShowS(&pBuilding->m[i]);
			}
			break;
		case 3:
			// pokaz pociski
			for (UBYTE i = 0; i < BUILDING_MOVERS_MAX; i++) {
				missileShow(&pBuilding->m[i].missile, Xs, Ys);
			}
			break;
	}
}

////////////////////////////////////////////////////////////////////////

void buildingRebuild(tBuilding *pBuilding) {
	(void)pBuilding;

	// Commented out in the original
	// if(pBuilding->hp < pBuilding->maxhp) {
	// 	pBuilding->hp += 30;
	// }

	// if(pBuilding->hp > pBuilding->maxhp) {
	// 	pBuilding->hp = pBuilding->maxhp;
	// }
}

////////////////////////////////////////////////////////////////////////

int buildingWynik(tBuilding *pBuilding, int r) {
	if (pBuilding->type == 1) {
		if (r > 2)
			return r + 1; // obora,koszary 1,swiatynia
		if (r == 1)
			return 2; // droga
		return 1;
	}
	if (pBuilding->type == 2 && r == 2) // krowa
		return 0;
	if (pBuilding->type == 2 && (r == 6 && g_uwLevel > PASTUCH_LEV))
		return 0; // pastuch
	if (pBuilding->type == 3) {
		if (r == 5)
			return 7; // koszary 2
		if (r == 2 || r == 3)
			return 0; // topor,luk
		return 1;   // palisada
	}
	if (pBuilding->type == 4) {
		if (r == 5 || r == 3 || r == 6)
			return 0; // druidka,druid,mag
	}
	if (pBuilding->type == 5) {
		if (r == 5)
			return 8; // dom wodza
		if (r == 4 || r == 3)
			return 0; // miecz,wlocznia
		if (r == 1)
			return 3; // palisada
		return 1;   // odbudowa
	}
	if (pBuilding->type == 6 && (r == 5 || r == 6))
		return 0;
	return 1;
}

int buildingMilk(tBuilding *pBuilding) {
	if (pBuilding->type != 2)
		return 0;
	int i = (
		moverMilk(&pBuilding->m[0]) + moverMilk(&pBuilding->m[1]) + moverMilk(&pBuilding->m[2]) +
		moverMilk(&pBuilding->m[3]) + moverMilk(&pBuilding->m[4]) +	moverMilk(&pBuilding->m[5])
	);
	return i;
}

int buildingNewMan(tBuilding *pBuilding, int Nr) {
	int i, j, p;
	if (pBuilding->exist != 1)
		return 0;
	j = 20;
	if (pBuilding->food >= pBuilding->maxfood)
		return 0;
	for (i = 5; i >= 0; i--)
		if (!pBuilding->m[i].exist)
			j = i; // znajdz wolny
	// if(place[x][y+2]!=0)return 0;  // nie mozna utorzyc goscia
	i = 20;
	if (pBuilding->type == 2 && Nr == 2) {
		i = 0;
		p = 450;
	} // krowa
	if (pBuilding->type == 2 && Nr == 6 && g_uwLevel > PASTUCH_LEV) {
		i = 10;
		p = 1250;
	} // pastuch
	if (pBuilding->type == 3 && Nr == 2) {
		i = 1;
		p = 450;
	} // topor
	if (pBuilding->type == 3 && Nr == 3) {
		i = 2;
		p = 650;
	} // luk
	if (pBuilding->type == 4 && Nr == 3) {
		i = 3;
		p = 650;
	} // druidka   //i=typ
	if (pBuilding->type == 4 && Nr == 5) {
		i = 4;
		p = 1050;
	} // kaplan
	if (pBuilding->type == 4 && Nr == 6 && g_uwLevel > MAG_LEV) {
		i = 11;
		p = 1250;
	} // mag
	if (pBuilding->type == 5 && Nr == 3) {
		i = 5;
		p = 650;
	} // miecz
	if (pBuilding->type == 5 && Nr == 4) {
		i = 6;
		p = 850;
	} // wlocznia
	if (pBuilding->type == 6 && Nr == 5) {
		i = 7;
		p = 1050;
	} // dowodca
	if (pBuilding->type == 6 && Nr == 6 && g_uwLevel > KUSZNIK_LEV) {
		i = 12;
		p = 1250;
	} // kusznik
	if (i == 20)
		return 0; // zla kolejnosc nie mozna zbudowac takiego goscia w tym budynku
	int xx = 0, yy = 0;
	if (place[pBuilding->x][pBuilding->y + 2]) {
		for (int i1 = pBuilding->x - 1; i1 < pBuilding->x + 4; i1++)
			for (int j1 = pBuilding->y - 1; j1 < pBuilding->y + 4; j1++)
				if (!place[i1][j1]) {
					xx = i1;
					yy = j1;
				}
	} else {
		xx = pBuilding->x;
		yy = pBuilding->y + 2;
	}
	if (!xx || !yy)
		return 0;
	moverInit(&pBuilding->m[j], i, xx, yy, 0, 0);
	moverSetIFF(&pBuilding->m[j], pBuilding->sMapObject.eTeam);

	if (!i) {
		pBuilding->m[j].xm = pBuilding->x;
		pBuilding->m[j].ym = pBuilding->y + 2;

	} // stajnia dla krowy
	if (pBuilding->sMapObject.eTeam == MAP_OBJECT_TEAM_PLAYER) {
		moverSetCommand(&pBuilding->m[j], 1);
		moverSetEnd(&pBuilding->m[j], pBuilding->x - 2, pBuilding->y + 4);
	}
	else {
		pBuilding->m[j].exp = g_eDifficulty * 30;
	}
	moverShow(&pBuilding->m[j]);
	pBuilding->food--;
	return p;
}

