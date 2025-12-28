#include "world.h"
#include <ace/managers/log.h>
#include "picture.h"
#include "misc.h"

static const UBYTE maskaT[16] = {
	PICTURE_KIND_GRASS_2, PICTURE_KIND_GRASS_3,
	PICTURE_KIND_GRASS_4, PICTURE_KIND_GRASS_6,
	PICTURE_KIND_GRASS_7, PICTURE_KIND_GRASS_5,
	PICTURE_KIND_GRASS_8, PICTURE_KIND_GRASS_4,
	PICTURE_KIND_GRASS_3, PICTURE_KIND_GRASS_4,
	PICTURE_KIND_GRASS_8, PICTURE_KIND_GRASS_4,
	PICTURE_KIND_GRASS_2, PICTURE_KIND_GRASS_3,
	PICTURE_KIND_GRASS_3, PICTURE_KIND_GRASS_5
};

// static int grassCounter;
static int waterCounter;
static int fireCounter;

void worldShowPlace(UWORD uwLeftX, UWORD uwTopY) {
	// kol[0] = LightYellow;
	// kol[1] = Yellow;
	// kol[2] = DarkYellow;
	// kol[3] = LightYellow;
	for (UBYTE ubY = uwTopY; ubY < uwTopY + WORLD_WINDOW_SIZE_Y; ubY++) {
		for (UBYTE ubX = uwLeftX; ubX < uwLeftX + WORLD_WINDOW_SIZE_X; ubX++) {
			if (placeN[ubX][ubY]) {
				UWORD uwScreenX = Xe[ubX - uwLeftX];
				UWORD uwScreenY = Ye[ubY - uwTopY];

				if (placeG[ubX][ubY] <= PICTURE_KIND_GRASS_8) {
					UBYTE k = (ubX + ubY * 5) & 0x0f;
					gfxDrawImageNoMask(uwScreenX, uwScreenY, &picture[maskaT[k]]); // trawa
					if (placeG[ubX][ubY] < 6)
						gfxDrawImageMaskedClipped(uwScreenX, uwScreenY, &picture[PICTURE_KIND_GRASS_1]); // wyjedzona
					if (placeG[ubX][ubY] < 3)
						gfxDrawImageMaskedClipped(uwScreenX, uwScreenY, &picture[PICTURE_KIND_GRASS_0]); // wyjedzona bardzo
				}
				else if (placeG[ubX][ubY] <= PICTURE_KIND_ROCK_12) {
					gfxDrawImageNoMask(uwScreenX, uwScreenY, &picture[placeG[ubX][ubY]]); // obrazki
				}
				else if (placeG[ubX][ubY] <= PICTURE_KIND_DRY_EARTH_2) {
					// Missing dry earth: 22, 23, 24, drawn later
				}
				else if (placeG[ubX][ubY] <= PICTURE_KIND_ROAD_20)
					gfxDrawImageNoMask(uwScreenX, uwScreenY, &picture[placeG[ubX][ubY]]); // obrazki
				else if (placeG[ubX][ubY] <= PICTURE_KIND_BRIDGE_7) {
					gfxDrawImageNoMask(uwScreenX, uwScreenY, &picture[PICTURE_KIND_WATER_8 + (waterCounter * 13)]); // woda
					gfxDrawImageMaskedClipped(uwScreenX, uwScreenY, &picture[placeG[ubX][ubY]]); // most
				}
				else if (placeG[ubX][ubY] < 68)
					gfxDrawImageNoMask(uwScreenX, uwScreenY, &picture[placeG[ubX][ubY]]); // obrazki
				else if (placeG[ubX][ubY] == PICTURE_KIND_FIREPLACE_SMALL) {
					gfxDrawImageNoMask(uwScreenX, uwScreenY, &picture[PICTURE_KIND_FIREPLACE_SMALL]);
					gfxDrawImageMaskedClipped(uwScreenX, uwScreenY, &fire[8 + ((fireCounter + ubX + ubY) & 3)]);
				} // male ognisko
				else if (placeG[ubX][ubY] == PICTURE_KIND_FIRE_RING) {
					gfxDrawImageNoMask(uwScreenX, uwScreenY, &picture[PICTURE_KIND_FIREPLACE_SMALL]);
					gfxDrawImageMaskedClipped(uwScreenX, uwScreenY, &fire[4 + ((fireCounter + ubX + ubY) & 3)]);
				} // duze ognisko
				else if (placeG[ubX][ubY] <= PICTURE_KIND_GADGET_BURNT_TREE_4)
					gfxDrawImageNoMask(uwScreenX, uwScreenY, &picture[2]); // podstawa pod rzewa wypalone
				else if (placeG[ubX][ubY] <= PICTURE_KIND_WATER_12)
					gfxDrawImageNoMask(uwScreenX, uwScreenY, &picture[placeG[ubX][ubY] + (waterCounter * 13)]); // woda
				else if (PICTURE_KIND_WALL_0 <= placeG[ubX][ubY] && placeG[ubX][ubY] <= PICTURE_KIND_WALL_11)
					gfxDrawImageNoMask(uwScreenX, uwScreenY, &picture[placeG[ubX][ubY]]); // palisada
				else if (PICTURE_KIND_TREE_0_BOTTOM <= placeG[ubX][ubY] && placeG[ubX][ubY] <= PICTURE_KIND_TREE_6_BOTTOM)
					gfxDrawImageNoMask(uwScreenX, uwScreenY, &picture[2]); // trawa pod drzewem
				else if (PICTURE_KIND_CONSTRUCTION_0 <= placeG[ubX][ubY] && placeG[ubX][ubY] <= PICTURE_KIND_RUIN_8) {
					if(place[ubX][ubY] < 512) {
						gfxDrawImageNoMask(uwScreenX, uwScreenY, &picture[placeG[ubX][ubY]]); // zamek i ruina nasz
					}
					else {
						PutImageChange13h(uwScreenX, uwScreenY, &picture[placeG[ubX][ubY]], 0, color1, color2); // zamek i ruina ich
					}
				}
				if (place[ubX][ubY] == 2)
					gfxDrawImageMaskedClipped(uwScreenX, uwScreenY, &picture[156]); // pale
				if (placeG[ubX][ubY] == 256)
					gfxDrawImageNoMask(uwScreenX, uwScreenY, &picture[PICTURE_KIND_GRASS_2]); // swiete miejsce
				if (placeG[ubX][ubY] == 301) {
					PutImageChange13h(uwScreenX, uwScreenY, &picture[PICTURE_KIND_FIRE_RING], 1, Red, kol[(fireCounter & 3)]);
				}
				if (placeG[ubX][ubY] == 300) {
					gfxDrawImageNoMask(uwScreenX, uwScreenY, &picture[PICTURE_KIND_GRASS_2]); // swiete miejsce - przemiana
					PutImageChange13h(uwScreenX, uwScreenY, &picture[PICTURE_KIND_HEAL_0 + (waterCounter & 1)], 1, Red, LightRed);
				}
				if (placeN[ubX][ubY] == 3)
					gfxDrawImageMaskedClipped(uwScreenX, uwScreenY, &fire[12]); // popiul duzy
				if (placeN[ubX][ubY] == 2)
					gfxDrawImageMaskedClipped(uwScreenX, uwScreenY, &fire[13]); // popiul maly
				if (placeG[ubX][ubY] == 70)
					gfxDrawImageMaskedClipped(uwScreenX, uwScreenY, &tree[1]); // lezy drzewo brazowe
				if (placeG[ubX][ubY] == 72)
					gfxDrawImageMaskedClipped(uwScreenX, uwScreenY, &tree[8]); // lezy drzewo spalone
				if (placeG[ubX + 1][ubY] == 70)
					gfxDrawImageMaskedClipped(uwScreenX, uwScreenY, &tree[0]); // lezy drzewo brazowe
				if (placeG[ubX + 1][ubY] == 72)
					gfxDrawImageMaskedClipped(uwScreenX, uwScreenY, &tree[7]); // lezy drzewo spalone
			}
		}
	}

	// Draw dry earth
	for (UBYTE ubY = uwTopY; ubY < uwTopY + WORLD_WINDOW_SIZE_Y; ubY++) {
		for (UBYTE ubX = uwLeftX; ubX < uwLeftX + WORLD_WINDOW_SIZE_X; ubX++) {
			if (PICTURE_KIND_DRY_EARTH_0 <= placeG[ubX][ubY] && placeG[ubX][ubY] <= PICTURE_KIND_DRY_EARTH_2)
				if (placeN[ubX][ubY]) {
					gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX] - 3, Ye[ubY - uwTopY] - 2, &picture[placeG[ubX][ubY]]);
				}
		}
	}

	// Fog of war
	for (UBYTE ubY = uwTopY; ubY < uwTopY + WORLD_WINDOW_SIZE_Y; ubY++) {
		for (UBYTE ubX = uwLeftX; ubX < uwLeftX + WORLD_WINDOW_SIZE_X; ubX++) {
			if (!(placeN[ubX][ubY])) {
				gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX] - 9, Ye[ubY - uwTopY] - 7, &shadow);
			}
		}
	}

	// if (Msg.x >= uwLeftX && Msg.y >= uwTopX && Msg.x < uwLeftX + WORLD_WINDOW_SIZE_X && Msg.y < uwTopX + 13 && Msg.count) {
	//   if (Msg.count == 4)
	//     Rectangle13h(Xe[Msg.x - uwLeftX] - 7, Ye[Msg.y - uwTopX] - 2, Xe[Msg.x - uwLeftX] + 14,
	//                  Ye[Msg.y - uwTopX] + 15, White);
	//   if (Msg.count == 3)
	//     Rectangle13h(Xe[Msg.x - uwLeftX] - 4, Ye[Msg.y - uwTopX], Xe[Msg.x - uwLeftX] + 11,
	//                  Ye[Msg.y - uwTopX] + 13, LightGray);
	//   if (Msg.count == 2)
	//     Rectangle13h(Xe[Msg.x - uwLeftX] - 1, Ye[Msg.y - uwTopX] + 2, Xe[Msg.x - uwLeftX] + 8,
	//                  Ye[Msg.y - uwTopX] + 11, Gray);
	//   if (Msg.count == 1)
	//     Rectangle13h(Xe[Msg.x - uwLeftX] + 1, Ye[Msg.y - uwTopX] + 4, Xe[Msg.x - uwLeftX] + 6,
	//                  Ye[Msg.y - uwTopX] + 9, Gray);
	//   if (Msg.count == 10)
	//     Rectangle13h(Xe[Msg.x - uwLeftX] - 7, Ye[Msg.y - uwTopX] - 2, Xe[Msg.x - uwLeftX] + 14,
	//                  Ye[Msg.y - uwTopX] + 15, Yellow);
	//   if (Msg.count == 9)
	//     Rectangle13h(Xe[Msg.x - uwLeftX] - 4, Ye[Msg.y - uwTopX], Xe[Msg.x - uwLeftX] + 11,
	//                  Ye[Msg.y - uwTopX] + 13, LightRed);
	//   if (Msg.count == 8)
	//     Rectangle13h(Xe[Msg.x - uwLeftX] - 1, Ye[Msg.y - uwTopX] + 2, Xe[Msg.x - uwLeftX] + 8,
	//                  Ye[Msg.y - uwTopX] + 11, Red);
	//   if (Msg.count == 7)
	//     Rectangle13h(Xe[Msg.x - uwLeftX] + 1, Ye[Msg.y - uwTopX] + 4, Xe[Msg.x - uwLeftX] + 6,
	//                  Ye[Msg.y - uwTopX] + 9, Red);
	// }
}

void worldShowTrees(UWORD uwLeftX, UWORD uwTopY) {
  for (UBYTE ubY = uwTopY; ubY < uwTopY + WORLD_WINDOW_SIZE_Y + 1; ubY++) {
    for (UBYTE ubX = uwLeftX; ubX < uwLeftX + WORLD_WINDOW_SIZE_X; ubX++) {
      if (placeN[ubX][ubY]) {
        if (placeG[ubX][ubY] > 112 && placeG[ubX][ubY] < 120) // drzewo zywe
        {
          if (placeN[ubX][ubY] < 190) {
            if (ubY < uwTopY + WORLD_WINDOW_SIZE_Y)
              gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX] - 8, Ye[ubY - uwTopY], &picture[placeG[ubX][ubY]]); // drzewo dol
            if (ubY > uwTopY)
              gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX] - 8, Ye[ubY - 1 - uwTopY], &picture[placeG[ubX][ubY] + 7]); //
            // fire gora
            if (ubY > uwTopY && placeN[ubX][ubY] > 74 && placeN[ubX][ubY] < 91)
              gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX], Ye[ubY - 1 - uwTopY] + 8, &fire[(fireCounter + ubX + ubY + 1) & 3]); // fire big
            if (ubY > uwTopY && placeN[ubX][ubY] > 70 && placeN[ubX][ubY] < 75)
              gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX], Ye[ubY - 1 - uwTopY] - 7, &fire[8 + ((fireCounter + ubX + ubY) & 3)]); // fire small
            if (ubY > uwTopY && placeN[ubX][ubY] > 70 && placeN[ubX][ubY] < 75)
              gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX], Ye[ubY - 1 - uwTopY] + 4, &fire[(fireCounter + ubX + ubY) & 3]); // fire big
          }
          if (placeN[ubX][ubY] > 194 && placeN[ubX][ubY] < 201) { // drzewo brazowe
            if (ubY > uwTopY) {
              gfxDrawImageMaskedClipped(Xe[ubX - 1 - uwLeftX], Ye[ubY - 1 - uwTopY], &tree[4]); //
              if (ubX > uwLeftX)
                gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX], Ye[ubY - 1 - uwTopY], &tree[5]); //
            }
            if (ubY < uwTopY + WORLD_WINDOW_SIZE_Y)
              gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX], Ye[ubY - uwTopY], &tree[6]); //
          }                                                  // 1 faza przewrotu
          if (placeN[ubX][ubY] > 190 && placeN[ubX][ubY] < 195) {
            if (ubX > uwLeftX)
              gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX], Ye[ubY - uwTopY], &tree[3]); //
            if (ubY < uwTopY + WORLD_WINDOW_SIZE_Y)
              gfxDrawImageMaskedClipped(Xe[ubX - 1 - uwLeftX], Ye[ubY - uwTopY], &tree[2]); //
          } // 2 faza przewrotu
        }

        if (placeG[ubX][ubY] == 71 || placeG[ubX][ubY] == 73) // drzewo spalone
        {
          if (placeN[ubX][ubY] < 190) {
            if (ubY < uwTopY + WORLD_WINDOW_SIZE_Y)
              gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX], Ye[ubY - uwTopY], &picture[placeG[ubX][ubY]]); // drzewo dol
            if (ubY > uwTopY)
              gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX], Ye[ubY - 1 - uwTopY], &picture[placeG[ubX][ubY] - 1]); //
          }
          if (placeN[ubX][ubY] > 194 && placeN[ubX][ubY] < 201) { // drzewo brazowe
            if (ubY > uwTopY) {
              gfxDrawImageMaskedClipped(Xe[ubX - 1 - uwLeftX], Ye[ubY - 1 - uwTopY], &tree[11]); //
              if (ubX > uwLeftX)
                gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX], Ye[ubY - 1 - uwTopY], &tree[12]); //
            }
            if (ubY < uwTopY + WORLD_WINDOW_SIZE_Y)
              gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX], Ye[ubY - uwTopY], &tree[13]); //
          } // 1 faza przewrotu
          if (placeN[ubX][ubY] > 190 && placeN[ubX][ubY] < 195) {
            if (ubX > uwLeftX)
              gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX], Ye[ubY - uwTopY], &tree[10]); //
            if (ubY < uwTopY + WORLD_WINDOW_SIZE_Y)
              gfxDrawImageMaskedClipped(Xe[ubX - 1 - uwLeftX], Ye[ubY - uwTopY], &tree[9]); //
          } // 2 faza przewrotu
        }

        ///////////// fire /////////////
        if (ubY < uwTopY + WORLD_WINDOW_SIZE_Y && placeN[ubX][ubY] > 90 && placeN[ubX][ubY] < 101) // fire big
        {
          gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX], Ye[ubY - uwTopY], &fire[((fireCounter + ubX + ubY) & 3)]);
        }
        if (ubY < uwTopY + WORLD_WINDOW_SIZE_Y && placeN[ubX][ubY] > 72 && placeN[ubX][ubY] < 91) // fire med
        {
          if (placeG[ubX][ubY] < 113 || placeG[ubX][ubY] > 119)
            gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX], Ye[ubY - uwTopY], &fire[12]);
          gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX], Ye[ubY - uwTopY], &fire[4 + ((fireCounter + ubX + ubY) & 3)]);
        }
        if (ubY < uwTopY + WORLD_WINDOW_SIZE_Y && placeN[ubX][ubY] >= 70 && placeN[ubX][ubY] < 73) // fire small
        {
          if (placeG[ubX][ubY] < 113 || placeG[ubX][ubY] > 119)
            gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX], Ye[ubY - uwTopY], &fire[12]);
          gfxDrawImageMaskedClipped(Xe[ubX - uwLeftX], Ye[ubY - uwTopY], &fire[8 + ((fireCounter + ubX + ubY) & 3)]);
        }
      }
    }
  }
}

void worldPlaceRoad(UWORD x, UWORD y, ULONG typ) {
	// typ=35-droga  266-palisada
	if (placeG[x][y] > typ + 10 || placeG[x][y] < typ - 4)
		return;
	if (typ > 200 && placeG[x][y] < typ - 1)
		return;

	int k = 0; // wprowadzic duzo zmian
	if (placeG[x][y - 1] < typ + 11 && placeG[x][y - 1] > typ - 5)
		k = 1;
	if (placeG[x + 1][y] < typ + 11 && placeG[x + 1][y] > typ - 5)
		k += 2;
	if (placeG[x][y + 1] < typ + 11 && placeG[x][y + 1] > typ - 5)
		k += 4;
	if (placeG[x - 1][y] < typ + 11 && placeG[x - 1][y] > typ - 5)
		k += 8;

	if (!k && typ < 200) {
		placeG[x][y] = 0;
		return;
	}
	if (k == 1 && typ < 200) {
		placeG[x][y] = 34;
		return;
	}
	if (k == 2 && typ < 200) {
		placeG[x][y] = 31;
		return;
	}
	if (k == 4 && typ < 200) {
		placeG[x][y] = 33;
		return;
	}
	if (k == 8 && typ < 200) {
		placeG[x][y] = 32;
		return;
	}

	if (k == 1 || k == 4) {
		placeG[x][y] = typ + 1;
		return;
	}
	if (k == 2 || k == 8) {
		placeG[x][y] = typ + 5;
		return;
	}
	//////??????????????????????????????
	if (k > 7)
		k--;
	if (k > 3)
		k--;
	if (k > 2)
		k--;
	if (k > 1)
		k--;
	if (!k)
		k = 2;
	placeG[x][y] = typ - 1 + k;
}

/////////////////////////////////////////////////////
void worldPlaceWater(UWORD x, UWORD y, ULONG t) // woda t=74-86
{
	if (placeG[x][y] > t + 12 || placeG[x][y] < t)
		return;

	int k = 0;
	if (placeG[x][y - 1] < t + 13 && placeG[x][y - 1] >= t)
		k += 1;
	if (placeG[x + 1][y] < t + 13 && placeG[x + 1][y] >= t)
		k += 2;
	if (placeG[x][y + 1] < t + 13 && placeG[x][y + 1] >= t)
		k += 4;
	if (placeG[x - 1][y] < t + 13 && placeG[x - 1][y] >= t)
		k += 8;
	// mosty
	if (!(k & 1) && placeG[x][y - 1] < 54 && placeG[x][y - 1] > 45)
		k += 1;
	if (!(k & 2) && placeG[x + 1][y] < 54 && placeG[x + 1][y] > 45)
		k += 2;
	if (!(k & 4) && placeG[x][y + 1] < 54 && placeG[x][y + 1] > 45)
		k += 4;
	if (!(k & 8) && placeG[x - 1][y] < 54 && placeG[x - 1][y] > 45)
		k += 8;
	placeG[x][y] = 8;
	switch (k) {
	case 0:
		placeG[x][y] = 60;
		break;
	case 3:
		placeG[x][y] = t;
		break;
	case 6:
		placeG[x][y] = t + 1;
		break;
	case 7:
		placeG[x][y] = t + 2;
		break;
	case 9:
		placeG[x][y] = t + 3;
		break;
	case 11:
		placeG[x][y] = t + 4;
		break;
	case 12:
		placeG[x][y] = t + 5;
		break;
	case 13:
		placeG[x][y] = t + 6;
		break;
	case 14:
		placeG[x][y] = t + 7;
		break;
	case 15:
		placeG[x][y] = t + 8;
		int xx;
		xx = placeG[x - 1][y - 1];
		if ((xx < 46) || (xx > 53 && xx < 74) || (xx > 86))
			placeG[x][y] = t + 9;
		xx = placeG[x + 1][y - 1];
		if ((xx < 46) || (xx > 53 && xx < 74) || (xx > 86))
			placeG[x][y] = t + 10;
		xx = placeG[x + 1][y + 1];
		if ((xx < 46) || (xx > 53 && xx < 74) || (xx > 86))
			placeG[x][y] = t + 11;
		xx = placeG[x - 1][y + 1];
		if ((xx < 46) || (xx > 53 && xx < 74) || (xx > 86))
			placeG[x][y] = t + 12;
		break;
	}
}

void worldDump(UBYTE ubStartX, UBYTE ubStartY, UBYTE ubSizeX, UBYTE ubSizeY) {
	logBlockBegin("worldDump(ubStartX: %hhu, ubStartY: %hhu, ubSizeX: %hhu, ubSizeY: %hhu))", ubStartX, ubStartY, ubSizeX, ubSizeY);
	static char szBfr[4 * WORLD_SIZE_X + 36];

	logWrite("placeG:");
	for(UBYTE y = ubStartY; y < ubStartY + ubSizeY; ++y) {
		char *pEnd = szBfr + sprintf(szBfr, "%2hhu: ", y);
		for(UBYTE x = ubStartX; x < ubStartX + ubSizeX; ++x) {
			pEnd += sprintf(pEnd, "%03X ", (UWORD)placeG[x][y]);
		}
		logWrite(szBfr);
	}

	logWrite("\nplaceN:");
	for(UBYTE y = ubStartY; y < ubStartY + ubSizeY; ++y) {
		char *pEnd = szBfr + sprintf(szBfr, "%2hhu: ", y);
		for(UBYTE x = ubStartX; x < ubStartX + ubSizeX; ++x) {
			pEnd += sprintf(pEnd, "%03X ", placeN[x][y]);
		}
		logWrite(szBfr);
	}
	logWrite("\nplace:");
	for(UBYTE y = ubStartY; y < ubStartY + ubSizeY; ++y) {
		char *pEnd = szBfr + sprintf(szBfr, "%2hhu: ", y);
		for(UBYTE x = ubStartX; x < ubStartX + ubSizeX; ++x) {
			pEnd += sprintf(pEnd, "%03X ", place[x][y]);
		}
		logWrite(szBfr);
	}
	logBlockEnd("worldDump()");
}

void worldRevealAll(void) {
	for(UBYTE ubX=0 ; ubX < WORLD_SIZE_X; ubX++) {
    for(UBYTE ubY=0; ubY < WORLD_SIZE_Y; ubY++) {
			placeN[ubX][ubY] = 1;
		}
	}
}

const UWORD Xe[20] = {
	11,  27,  43,  59,  75,  91,  107, 123, 139, 155,
	171, 187, 203, 219, 235, 251, 267, 283, 299, 315
};
const UWORD Ye[16] = {
	8,   22,  36,  50,  64,  78,  92,  106,
	120, 134, 148, 162, 176, 190, 204, 218
};

int drzewa;
int drzewa0;
UWORD place[WORLD_SIZE_X][WORLD_SIZE_Y];
UBYTE placeN[WORLD_SIZE_X][WORLD_SIZE_Y]; // 0 means behind fog of war
UWORD attack[WORLD_SIZE_X][WORLD_SIZE_Y];
UWORD placeG[WORLD_SIZE_X][WORLD_SIZE_Y];
UBYTE xleczenie;
UBYTE yleczenie;
UWORD xpastw;
UWORD ypastw;
