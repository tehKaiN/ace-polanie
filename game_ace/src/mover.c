#include "mover.h"
#include <ace/macros.h>
#include <mini_std/stdio.h>
#include "bitmap_pair.h"
#include "world.h"
#include "castle.h"
#include "picture.h"
#include "misc.h"
#include "battle.h"

typedef struct tMixedBitmaps {
	tBitmapPair sPairNarrow;
	tBitmapPair sPairWide;
} tMixedBitmaps;

typedef struct tMoverStats {
	UWORD s_range;
	UWORD a_range;
	UWORD damage;
	UWORD armour;
	UWORD hp;
	UWORD maxdelay;
} tMoverStats;

static const tUbCoordYX pWideSizes[] = {
	{.ubX = 24, .ubY = 21}, // x0y0
	{.ubX = 24, .ubY = 14}, // x0y1
	{.ubX = 24, .ubY = 21}, // x0y2

	{.ubX = 16, .ubY = 21}, // x1y0
	{.ubX = 16, .ubY = 14}, // x1y1
	{.ubX = 16, .ubY = 21}, // x1y2

	{.ubX = 24, .ubY = 21}, // x2y0
	{.ubX = 24, .ubY = 14}, // x2y1
	{.ubX = 24, .ubY = 21}, // x2y2
};

static const tMoverStats Udata[MOVER_KIND_COUNT] = {
	{2, 0, 0, 0, 100, 12},
	{3, 1, 10, 0, 100, 10},
	{4, 3, 5, 0, 100, 8},
	{4, 3, 35, 0, 70, 14},
	{5, 5, 50, 0, 80, 16},
	{3, 1, 20, 3, 120, 10},
	{5, 4, 15, 3, 120, 10},
	{4, 1, 30, 5, 150, 10},
	{4, 1, 25, 3, 300, 16},
	{4, 1, 20, 3, 120, 6},
	{3, 1, 0, 0, 40, 12},
	{6, 6, 10, 0, 50, 12},
	{6, 5, 25, 5, 130, 8}
};

static const int ddamage[15] = {1, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 6, 7, 8, 9};

static const int darmour[15] = {0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 6};

static const int dmagic[15] = {
	60,  80,  85,  90,  120, 140, 150, 160,
  170, 180, 190, 200, 220, 240, 280
};

static const UBYTE shiftX[MOVER_KIND_COUNT][17] = {
    {0, 1, 2, 3, 5, 6, 8, 9, 11, 12, 13, 14, 16, 15, 15, 15, 15},
    {0, 1, 2, 3, 4, 6, 8, 10, 12, 14, 16, 25, 15, 15, 15, 15, 15},
    {0, 2, 4, 6, 8, 10, 12, 14, 16, 15, 15, 15, 15, 15, 15, 15, 15},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 16, 15, 15},
    {0, 1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 10, 11, 12, 13, 14, 15},
    {0, 1, 3, 5, 6, 8, 9, 11, 12, 14, 16, 15, 15, 15, 15, 15, 15},
    {0, 1, 3, 5, 6, 8, 9, 11, 12, 14, 16, 15, 15, 15, 15, 15, 15},
    {0, 1, 3, 5, 6, 8, 9, 11, 12, 14, 15, 15, 15, 15, 15, 15, 15},
    {0, 1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 10, 11, 12, 13, 14, 15},
    {0, 3, 5, 7, 9, 12, 14, 15, 15, 8, 9, 10, 11, 12, 13, 14, 15},
    {0, 1, 2, 3, 5, 6, 8, 9, 11, 12, 13, 14, 16, 15, 15, 15, 15},
    {0, 1, 2, 3, 5, 6, 8, 9, 11, 12, 13, 14, 16, 15, 15, 15, 15},
    {0, 2, 4, 6, 8, 10, 12, 14, 16, 15, 15, 15, 15, 15, 15, 15, 15}
};

static const UBYTE shiftY[MOVER_KIND_COUNT][17] = {
    {0, 1, 2, 3, 5, 6, 8, 9, 11, 12, 13, 14, 15, 15, 15, 15, 15},
    {0, 1, 2, 5, 6, 7, 8, 10, 11, 12, 14, 25, 15, 15, 15, 15, 15},
    {0, 1, 3, 5, 7, 9, 11, 13, 14, 15, 15, 15, 15, 15, 15, 15, 15},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15},
    {0, 1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 10, 11, 12, 13, 14, 14},
    {0, 1, 2, 5, 6, 7, 8, 10, 11, 12, 14, 25, 15, 15, 15, 15, 15},
    {0, 1, 2, 5, 6, 7, 8, 10, 11, 12, 14, 25, 15, 15, 15, 15, 15},
    {0, 1, 2, 5, 6, 7, 8, 10, 11, 12, 14, 25, 15, 15, 15, 15, 15},
    {0, 1, 2, 3, 4, 5, 6, 7, 7, 8, 9, 10, 11, 12, 13, 14, 14},
    {0, 3, 5, 7, 9, 12, 14, 14, 14, 8, 9, 10, 11, 12, 13, 14, 14},
    {0, 1, 2, 3, 5, 6, 8, 9, 11, 12, 13, 14, 15, 15, 15, 15, 15},
    {0, 1, 2, 3, 5, 6, 8, 9, 11, 12, 13, 14, 15, 15, 15, 15, 15},
    {0, 1, 3, 5, 7, 9, 11, 13, 14, 15, 15, 15, 15, 15, 15, 15, 15}
};

static const UBYTE Phase[MOVER_KIND_COUNT][19] = {
    {0, 0, 0, 1, 1, 1, 0, 0, 0, 2, 2, 2, 0, 6, 1, 1, 0, 8, 4},
    {0, 0, 1, 1, 1, 0, 0, 2, 2, 2, 0, 6, 0, 0, 0, 0, 0, 6, 3},
    {0, 0, 2, 2, 0, 0, 1, 1, 1, 6, 0, 0, 0, 0, 0, 0, 0, 4, 2},
    {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 2, 2, 0, 6, 0, 11, 8},
    {0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 13, 9},
    {0, 0, 2, 2, 2, 0, 0, 0, 1, 1, 1, 6, 0, 0, 0, 0, 0, 6, 3},
    {0, 0, 2, 2, 2, 0, 0, 0, 1, 1, 1, 6, 0, 0, 0, 0, 0, 6, 3},
    {0, 0, 2, 2, 2, 0, 0, 1, 1, 1, 1, 6, 0, 0, 1, 1, 0, 5, 2},
    {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 8, 2},
    {0, 1, 1, 0, 2, 2, 0, 6, 0, 0, 0, 2, 2, 2, 2, 0, 0, 4, 2},
    {0, 0, 0, 1, 1, 1, 0, 0, 0, 2, 2, 2, 0, 6, 1, 1, 0, 8, 4},
    {0, 0, 0, 1, 1, 1, 0, 0, 0, 2, 2, 2, 0, 6, 1, 1, 0, 8, 4},
    {0, 0, 2, 2, 0, 0, 1, 1, 1, 6, 0, 0, 0, 0, 0, 0, 0, 4, 2}
};

static UBYTE floodfillQueue[2000];
static int Place[WORLD_SIZE_X][WORLD_SIZE_Y];

static tMixedBitmaps s_sMixedAxe;
static tMixedBitmaps s_sMixedBear;
static tMixedBitmaps s_sMixedBeast;
static tMixedBitmaps s_sMixedKnight;
static tMixedBitmaps s_sMixedSword;

static tBitmapPair s_sNarrowCow;
static tBitmapPair s_sNarrowFarmer;
static tBitmapPair s_sNarrowHunter;
static tBitmapPair s_sNarrowMage;
static tBitmapPair s_sNarrowPike;
static tBitmapPair s_sNarrowPriest;
static tBitmapPair s_sNarrowPriestess;
static tBitmapPair s_sNarrowXbow;

static void moverNarrowCreate(tBitmapPair *pBmPair, const char *szDataPath, tMoverKind eKind) {
	bitmapPairCreate(pBmPair, szDataPath);
	UWORD uwOffsY = 0;
	UBYTE ubFrameIndex = 0;
	for(UBYTE ubPhase = 0; ubPhase < MOVER_PHASE_COUNT; ++ubPhase) {
		for(UBYTE ubX = 0; ubX < 3; ++ubX) {
			for(UBYTE ubY = 0; ubY < 3; ++ubY) {
				g_pMoverFrames[eKind][ubPhase][ubX][ubY].pBitmap = pBmPair->pFrames;
				g_pMoverFrames[eKind][ubPhase][ubX][ubY].pMask = pBmPair->pMasks;
				g_pMoverFrames[eKind][ubPhase][ubX][ubY].uwWidth = 16;
				g_pMoverFrames[eKind][ubPhase][ubX][ubY].uwHeight = 14;
				g_pMoverFrames[eKind][ubPhase][ubX][ubY].uwOffsY = uwOffsY;
				uwOffsY += 14;
				++ubFrameIndex;
			}
		}
	}
}

static void moverNarrowDestroy(tBitmapPair *pNarrow) {
	bitmapPairDestroy(pNarrow);
}

static void moverMixedCreate(tMixedBitmaps *pMixed, const char *szName, tMoverKind eKind) {
	char szPath[40];

	sprintf(szPath, "movers/%s16", szName);
	bitmapPairCreate(&pMixed->sPairNarrow, szPath);
	sprintf(szPath, "movers/%s32", szName);
	bitmapPairCreate(&pMixed->sPairWide, szPath);

	UWORD uwOffsY = 0;
	UBYTE ubFrameIndex = 0;
	for(UBYTE ubPhase = 0; ubPhase < MOVER_PHASE_ACTION1; ++ubPhase) {
		for(UBYTE ubX = 0; ubX < 3; ++ubX) {
			for(UBYTE ubY = 0; ubY < 3; ++ubY) {
				g_pMoverFrames[eKind][ubPhase][ubX][ubY].pBitmap = pMixed->sPairNarrow.pFrames;
				g_pMoverFrames[eKind][ubPhase][ubX][ubY].pMask = pMixed->sPairNarrow.pMasks;
				g_pMoverFrames[eKind][ubPhase][ubX][ubY].uwWidth = 16;
				g_pMoverFrames[eKind][ubPhase][ubX][ubY].uwHeight = 14;
				g_pMoverFrames[eKind][ubPhase][ubX][ubY].uwOffsY = uwOffsY;
				uwOffsY += 14;
				++ubFrameIndex;
			}
		}
	}

	uwOffsY = 0;
	for(UBYTE ubPhase = MOVER_PHASE_ACTION1; ubPhase < MOVER_PHASE_COUNT; ++ubPhase) {
		ubFrameIndex = 0;
		for(UBYTE ubX = 0; ubX < 3; ++ubX) {
			for(UBYTE ubY = 0; ubY < 3; ++ubY) {
				g_pMoverFrames[eKind][ubPhase][ubX][ubY].pBitmap = pMixed->sPairWide.pFrames;
				g_pMoverFrames[eKind][ubPhase][ubX][ubY].pMask = pMixed->sPairWide.pMasks;
				g_pMoverFrames[eKind][ubPhase][ubX][ubY].uwWidth = pWideSizes[ubFrameIndex].ubX;
				g_pMoverFrames[eKind][ubPhase][ubX][ubY].uwHeight = pWideSizes[ubFrameIndex].ubY;
				g_pMoverFrames[eKind][ubPhase][ubX][ubY].uwOffsY = uwOffsY;
				uwOffsY += pWideSizes[ubFrameIndex].ubY;
				++ubFrameIndex;
			}
		}
	}
}

static void moverMixedDestroy(tMixedBitmaps *pMixed) {
	bitmapPairDestroy(&pMixed->sPairNarrow);
	bitmapPairDestroy(&pMixed->sPairWide);
}

void moverGraphicsCreate(void) {
	moverMixedCreate(&s_sMixedAxe, "axe", MOVER_KIND_AXE);
	moverMixedCreate(&s_sMixedBear, "bear", MOVER_KIND_BEAR);
	moverMixedCreate(&s_sMixedBeast, "beast", MOVER_KIND_BEAST);
	moverMixedCreate(&s_sMixedKnight, "knight", MOVER_KIND_KNIGHT);
	moverMixedCreate(&s_sMixedSword, "sword", MOVER_KIND_SWORD);

	moverNarrowCreate(&s_sNarrowCow, "movers/cow", MOVER_KIND_COW);
	moverNarrowCreate(&s_sNarrowFarmer, "movers/farmer", MOVER_KIND_FARMER);
	moverNarrowCreate(&s_sNarrowHunter, "movers/hunter", MOVER_KIND_HUNTER);
	moverNarrowCreate(&s_sNarrowMage, "movers/mage", MOVER_KIND_MAGE);
	moverNarrowCreate(&s_sNarrowPike, "movers/pike", MOVER_KIND_PIKE);
	moverNarrowCreate(&s_sNarrowPriest, "movers/priest", MOVER_KIND_PRIEST);
	moverNarrowCreate(&s_sNarrowPriestess, "movers/priestess", MOVER_KIND_PRIESTESS);
	moverNarrowCreate(&s_sNarrowXbow, "movers/xbow", MOVER_KIND_XBOW);
}

void moverGraphicsDestroy(void) {
	moverMixedDestroy(&s_sMixedAxe);
	moverMixedDestroy(&s_sMixedBear);
	moverMixedDestroy(&s_sMixedBeast);
	moverMixedDestroy(&s_sMixedKnight);
	moverMixedDestroy(&s_sMixedSword);

	moverNarrowDestroy(&s_sNarrowCow);
	moverNarrowDestroy(&s_sNarrowFarmer);
	moverNarrowDestroy(&s_sNarrowHunter);
	moverNarrowDestroy(&s_sNarrowMage);
	moverNarrowDestroy(&s_sNarrowPike);
	moverNarrowDestroy(&s_sNarrowPriest);
	moverNarrowDestroy(&s_sNarrowPriestess);
	moverNarrowDestroy(&s_sNarrowXbow);
}

static int Who(int nr) // 0 nikt 1-nasz wojownik 2-nasz budynek 3-ich wojownik 4-ich budynek
{
  int aa = nr & 0x00ff;
  int bb = nr >> 8;
  if (bb < 1 || 2 < bb)
    return 0;
  bb--;
  int nrb = aa / 10;       // nr budynku
  int nrp = aa - nrb * 10; // nr postaci

  if (nrp > 3 || nrb > 19) // jeden z zolnierzy
  {
    if (bb)
      return 3; // ich zolnierz
    else
      return 1; // nasz zolnierz
  }
  if (bb)
    return 4; // ich budynek
  else
    return 2; // nasz budynek
}

static int Type(int nr) // building.type / mover.type
{
  int aa = nr & 0x00ff;
  int bb = nr >> 8;
  if (bb < 1 || 2 < bb)
    return 0;
  bb--;
  int nrb = aa / 10;       // nr budynku
  int nrp = aa - nrb * 10; // nr postaci

  if (nrp > 3 || nrb > 19) // jeden z zolnierzy
  {
    if (nrb < 20)
      return castle[bb].b[nrb].m[nrp - 4].type;
    else
      return castle[bb].m[(nr & 0xff) - 200].type;
  }
  return castle[bb].b[nrb].type + 20;
}

tMover *moverGetByNum(int nr) {
  int aa = nr & 0x00ff;
  int bb = nr >> 8;
  if (bb < 1 || 2 < bb)
    return NULL;
  bb--;
  int nrb = aa / 10;       // nr budynku
  int nrp = aa - nrb * 10; // nr postaci

  if (nrp > 3 || nrb > 19) // jeden z zolnierzy
  {
    if (nrb < 20) {
      // char ss[20];
      // sprintf(ss,"Pointer c:%d, b:%d, p:%d,
      // u:%d",bb,nrb,nrp-4,castle[bb].b[nrb-1].m[nrp-4].udder);
      // strcpy(Msg.msg,ss);
      // Msg.licznik=20;
      return &castle[bb].b[nrb].m[nrp - 4];
    } else
      return &castle[bb].m[(nr & 0xff) - 200];
  }
  return NULL;
}

static void NewCow(tMover *oldcow) {
  if (oldcow == NULL)
    return;
  // oldcow->wybrany=1;
  int side = (oldcow->sMapObject.eTeam == MAP_OBJECT_TEAM_CPU) ? 0 : 1;

  for (int i = 2; i < 38; i++) {
    if (!(castle[side].m[i].exist)) {
      place[oldcow->sMapObject.ubX][oldcow->sMapObject.ubY] = 0;
      oldcow->exist = MOVER_EXIST_NONE;
      moverInit(&castle[side].m[i], oldcow->type, oldcow->sMapObject.ubX, oldcow->sMapObject.ubY, 1, 10);
      moverSetIFF(&castle[side].m[i], side + 1);
      castle[side].m[i].hp = oldcow->hp;
      castle[side].m[i].maxhp = oldcow->maxhp;
      castle[side].m[i].udder = oldcow->udder;
      castle[side].m[i].xm = castle[side].m[i].sMapObject.ubX + 3;
      castle[side].m[i].ym = castle[side].m[i].sMapObject.ubY + 3;
      castle[side].m[i].xp = castle[side].m[i].sMapObject.ubX;
      castle[side].m[i].yp = castle[side].m[i].sMapObject.ubY;
      castle[side].m[i].xe = castle[side].m[i].sMapObject.ubX;
      castle[side].m[i].ye = castle[side].m[i].sMapObject.ubY;
      castle[side].m[i].dx = castle[side].m[i].dx;
      castle[side].m[i].dy = castle[side].m[i].dy;
      moverShow(&castle[side].m[i]);
      if (side) {
        castle[side].m[i].xp = xpastw;
        castle[side].m[i].yp = ypastw;
        castle[side].m[i].xe = xpastw;
        castle[side].m[i].ye = ypastw;
      }
      return;
    }
  }

  for (UBYTE bi = 0; bi < CASTLE_BUILIDNGS_MAX; bi++)
    for (UBYTE bmi = 0; bmi < BUILDING_MOVERS_MAX; bmi++) {
      if (castle[side].b[bi].type == 2 && castle[side].b[bi].exist == 1)
        if (!(castle[side].b[bi].m[bmi].exist)) {
          // strcpy(Msg.msg,"Przepisuje krowe do obory");
          // Msg.licznik=200;

          place[oldcow->sMapObject.ubX][oldcow->sMapObject.ubY] = 0;
          oldcow->exist = MOVER_EXIST_NONE;
          moverInit(&castle[side].b[bi].m[bmi], oldcow->type, oldcow->sMapObject.ubX, oldcow->sMapObject.ubY, 1, 10);
          moverSetIFF(&castle[side].b[bi].m[bmi], side + 1);
          castle[side].b[bi].m[bmi].hp = oldcow->hp;
          castle[side].b[bi].m[bmi].maxhp = oldcow->maxhp;
          castle[side].b[bi].m[bmi].udder = oldcow->udder;
          castle[side].b[bi].m[bmi].xm = castle[side].m[bi].sMapObject.ubX + 3;
          castle[side].b[bi].m[bmi].ym = castle[side].m[bi].sMapObject.ubY + 3;
          castle[side].b[bi].m[bmi].xp = castle[side].m[bi].sMapObject.ubX;
          castle[side].b[bi].m[bmi].yp = castle[side].m[bi].sMapObject.ubY;
          castle[side].b[bi].m[bmi].xe = castle[side].m[bi].sMapObject.ubX;
          castle[side].b[bi].m[bmi].ye = castle[side].m[bi].sMapObject.ubY;
          castle[side].b[bi].m[bmi].dx = castle[side].m[bi].dx;
          castle[side].b[bi].m[bmi].dy = castle[side].m[bi].dy;
          moverShow(&castle[side].b[bi].m[bmi]);
          if (side) {
            castle[side].b[bi].m[bmi].xp = xpastw;
            castle[side].b[bi].m[bmi].yp = ypastw;
            castle[side].b[bi].m[bmi].xe = xpastw;
            castle[side].b[bi].m[bmi].ye = ypastw;
          }
          return;
        }
    }
}

static void FindCow(int x, int y, int *xe, int *ye) {
  int i, j, startk, stopk;
  int ii, jj;
  for (j = 0; j < WORLD_SIZE_Y; j++)
    for (i = 0; i < WORLD_SIZE_X; i++) {
      Place[i][j] = 1;
      if ((i > 0) && (j > 0) && (i < WORLD_SIZE_X - 1) && (j < WORLD_SIZE_Y - 1)) {
        if (!place[i][j])
          Place[i][j] = 1000;
        if (place[i][j] && place[i][j]->eTeam == MAP_OBJECT_TEAM_PLAYER) {
          if (place[i][j]->eKind == MAP_OBJECT_KIND_MOVER) // nasz wojownik
          {
            tMover *pPlayerMover = (tMover*)place[i][j];
            if (pPlayerMover->type == 0) {
              Place[i][j] = 1001;
            }
          }
        }
      }
    }
  startk = 0;
  stopk = 0;
  i = x;
  j = y;
  Place[i][j] = 1000;
  do {
    /////////////////pozar prerii///////////////////////////
    if (stopk != startk) {
      i = floodfillQueue[stopk];
      j = floodfillQueue[stopk + 1];
      if (stopk < 1950)
        stopk += 2;
      else
        stopk = 0;
    }

    for (jj = j - 1; jj < j + 2; jj++)
      for (ii = i - 1; ii < i + 2; ii++) {
        if (Place[ii][jj] == 1001) {
          *xe = ii;
          *ye = jj;
          return;
        }
        if (Place[ii][jj] == 1000)
          if (ii > 0 && ii < WORLD_SIZE_X - 1 && jj > 0 && jj < WORLD_SIZE_Y - 1) {
            Place[ii][jj] = 1;
            floodfillQueue[startk] = ii;
            floodfillQueue[startk + 1] = jj;
            if (startk < 1950)
              startk += 2;
            else
              startk = 0;
          }
      }

  } while (stopk != startk);
  //-------------------
  *xe = x;
  *ye = y;
}

static void FindShed(int k, int *xm, int *ym) {
  int i;
  for (i = 0; i < CASTLE_BUILIDNGS_MAX; i++) {
    if (castle[k].b[i].type == 2 && castle[k].b[i].exist == 1) {
      *xm = castle[k].b[i].sMapObject.ubX;
      *ym = castle[k].b[i].sMapObject.ubY + 2;
    }
  }
  for (i = 0; i < CASTLE_BUILIDNGS_MAX; i++) {
    if (!place[castle[k].b[i].sMapObject.ubX][castle[k].b[i].sMapObject.ubY + 1] &&
        castle[k].b[i].type == 2 && castle[k].b[i].exist == 1) {
      *xm = castle[k].b[i].sMapObject.ubX;
      *ym = castle[k].b[i].sMapObject.ubY + 2;
    }
  }
}

static void FindEnemy(int x, int y, int *xe, int *ye, int distance) {
  int i, j, startk, stopk;
  int ii, jj;
  for (j = 0; j < WORLD_SIZE_Y; j++) {
    for (i = 0; i < WORLD_SIZE_X; i++) {
      Place[i][j] = 1;
      if (!place[i][j])
        Place[i][j] = 1000;
      else if (place[i][j]->eTeam == MAP_OBJECT_TEAM_PLAYER && !(distance))
        Place[i][j] = 1001;
      else if (place[i][j]->eTeam == MAP_OBJECT_TEAM_CPU && distance == 1)
        Place[i][j] = 1001;
      else if ((place[i][j]->eTeam == MAP_OBJECT_TEAM_TREE) && distance == 2)
        Place[i][j] = 1001;
    }
  }

  startk = 0;
  stopk = 0;
  i = x;
  j = y;
  Place[i][j] = 1000;
  do {
    /////////////////pozar prerii///////////////////////////
    if (stopk != startk) {
      i = floodfillQueue[stopk];
      j = floodfillQueue[stopk + 1];
      if (stopk < 1950)
        stopk += 2;
      else
        stopk = 0;
    }

    for (jj = j - 1; jj < j + 2; jj++)
      for (ii = i - 1; ii < i + 2; ii++) {
        if (Place[ii][jj] == 1001) {
          *xe = ii;
          *ye = jj;
          return;
        }
        if (Place[ii][jj] == 1000)
          if (ii > 0 && ii < WORLD_SIZE_X - 1 && jj > 0 && jj < WORLD_SIZE_Y - 1) {
            Place[ii][jj] = 1;
            floodfillQueue[startk] = ii;
            floodfillQueue[startk + 1] = jj;
            if (startk < 1950)
              startk += 2;
            else
              startk = 0;
          }
      }

  } while (stopk != startk);
  //-------------------
  *xe = 32;
  *ye = 32;
}

static void FindHolyPlace(int *xe, int *ye) {
  int i, j, startk, stopk;
  int ii, jj;
  if (placeG[*xe][*ye] == 256)
    return;
  int x = *xe;
  int y = *ye;
  for (j = 0; j < WORLD_SIZE_Y; j++)
    for (i = 0; i < WORLD_SIZE_X; i++) {
      Place[i][j] = 1; // zajete
      if ((i > 0) && (j > 0) && (i < WORLD_SIZE_X - 1) && (j < WORLD_SIZE_Y - 1)) {
        if (!(place[i][j]))
          Place[i][j] = 1000; // wolne
        if (placeG[i][j] == 256)
          Place[i][j] = 1234;
      }
    }

  startk = 0;
  stopk = 0;
  i = x;
  j = y;
  Place[i][j] = 1000;
  do {
    /////////////////pozar prerii///////////////////////////
    if (stopk != startk) {
      i = floodfillQueue[stopk];
      j = floodfillQueue[stopk + 1];
      if (stopk < 1950)
        stopk += 2;
      else
        stopk = 0;
    }

    for (jj = j - 1; jj < j + 2; jj++)
      for (ii = i - 1; ii < i + 2; ii++) {
        if (Place[ii][jj] == 1234) {
          *xe = ii;
          *ye = jj;
          return;
        }
        if (Place[ii][jj] == 1000) {
          if (ii > 0 && ii < WORLD_SIZE_X - 1 && jj > 0 && jj < WORLD_SIZE_Y - 1) {
            Place[ii][jj] = 1;
            floodfillQueue[startk] = ii;
            floodfillQueue[startk + 1] = jj;
            if (startk < 1950)
              startk += 2;
            else
              startk = 0;
          }
        }
      }

  } while (stopk != startk);
  //-------------------
  *xe = x;
  *ye = y;
}

#pragma region methods

void moverSetStart(tMover *pMover, int x0, int y0) {
  pMover->sMapObject.ubX = x0;
  pMover->sMapObject.ubY = y0;
}

void moverDisable(tMover *pMover) {
  pMover->exist = MOVER_EXIST_NONE;
  pMover->missile.exist = 0;
  pMover->wybrany = 0;
  pMover->ispath = 0;
}

void moverInit(tMover *pMover, int eMoverKind, int x1, int y1, int c, int d) {
  pMover->sMapObject.eKind = MAP_OBJECT_KIND_MOVER;
  pMover->magic = 0;
  if (eMoverKind == 3 || eMoverKind == 4 || eMoverKind == 11)
    pMover->magic = dmagic[0] / 2;
  pMover->wybrany = 0;
  pMover->exp = 0;
  pMover->type = eMoverKind;
  pMover->pFrameset = &g_pMoverFrames[eMoverKind]; // TODO: team color bitmaps

  pMover->s_range = Udata[eMoverKind].s_range;
  pMover->a_range = Udata[eMoverKind].a_range;
  pMover->damage = Udata[eMoverKind].damage;
  pMover->armour = Udata[eMoverKind].armour;
  pMover->hp = Udata[eMoverKind].hp;
  pMover->maxdelay = Udata[eMoverKind].maxdelay;

  pMover->commandN = c;
  pMover->command = c;
  moverSetStart(pMover, x1, y1);
  pMover->xm = x1;
  pMover->ym = y1;
  pMover->maxhp = pMover->hp;
  pMover->exist = MOVER_EXIST_ALIVE;
  pMover->dx = 0;
  pMover->dy = 0;
  pMover->phase = 0;
  pMover->udder = 0;
  pMover->target = 0;
  pMover->visible = 0;
  pMover->inmove = 0;
  pMover->delay = d;
  pMover->marmour = 0;
}

void moverConstruct(tMover *pMover) {
  pMover->ispath = 0;
  pMover->dx = 0;
  pMover->dy = 0;
  pMover->exist = MOVER_EXIST_NONE;
  pMover->wybrany = 0;
  pMover->missile.exist = 0;
  pMover->maxdelay = 5;
}

// Probably not needed since everything is allocated upfront
void moverDestruct(tMover *pMover) {
  pMover->exist = MOVER_EXIST_NONE;
  pMover->missile.exist = 0;
  pMover->wybrany = 0;
}

void moverSetTarget(tMover *pMover, const tMapObject *pTarget) {
  pMover->target = pTarget;
  pMover->mainTarget = 1;

  if (pMover->type == 11) {
    if (pMover->target && pMover->target->eKind != MAP_OBJECT_KIND_MOVER) {
      pMover->target = 0;
      pMover->mainTarget = 0;
    }
  }
}

void moverSetIFF(tMover *pMover, tMapObjectTeam eTeam) {
  pMover->sMapObject.eTeam = eTeam;
  if (eTeam == MAP_OBJECT_TEAM_CPU && g_eDifficulty > DIFFICULTY_MEDIUM) {
    pMover->hp += 15;
    pMover->maxhp += 15;
  }
  else if (eTeam == MAP_OBJECT_TEAM_CPU && g_eDifficulty == DIFFICULTY_EASY) {
    pMover->hp -= 25;
    pMover->maxhp -= 25;
  }
}

void moverSetCommand(tMover *pMover, int Nr) {
  if (pMover->type != 1 && (Nr == 8 || Nr == 11))
    return;
  if (Nr == 8) {
    pMover->xm = pMover->xe;
    pMover->ym = pMover->ye;
  } // budowa
  if (Nr == 2)
    pMover->ispath = 0;
  if (Nr == 5)
    pMover->mainTarget = 0;
  if (pMover->type && Nr == 123 && (pMover->sMapObject.ubX & 1))
    return;
  pMover->commandN = Nr;
}

void moverLabeling(tMover *pMover) {
  int min, startk, stopk;
  pMover->delay = pMover->maxdelay;
  if (PlaceUsed > 5 && pMover->type)
    return;
  PlaceUsed++;

  for (UBYTE j = 0; j < WORLD_SIZE_Y; j++) {
    for (UBYTE i = 0; i < WORLD_SIZE_X; i++) {
      if (place[i][j] == 0) {
        Place[i][j] = 1000;
        if (10 < placeN[i][j] && placeN[i][j] < 100)
          Place[i][j] = 9999;
      }
      else {
        Place[i][j] = 9999;
      }
    }
  }

  startk = 0;
  stopk = 0;
  UBYTE i = pMover->xe;
  UBYTE j = pMover->ye;
  Place[i][j] = 0;
  do {
    /////////////////pozar prerii///////////////////////////
    if (stopk != startk) {
      i = floodfillQueue[stopk];
      j = floodfillQueue[stopk + 1];
      if (stopk < 1950)
        stopk += 2;
      else
        stopk = 0;
    }

    min = Place[i][j];
    UBYTE ubStartX = MAX(0, i - 1);
    UBYTE ubEndX = MIN(WORLD_SIZE_X - 1, i + 1);
    UBYTE ubStartY = MAX(0, j - 1);
    UBYTE ubEndY = MIN(WORLD_SIZE_Y - 1, j + 1);
    for (UBYTE jj = ubStartY; jj <= ubEndY; jj++) {
      for (UBYTE ii = ubStartX; ii <= ubEndX; ii++) {
        if (min + 1 < Place[ii][jj] && Place[ii][jj] <= 1000) {
          Place[ii][jj] = min + 1;
          floodfillQueue[startk] = ii;
          floodfillQueue[startk + 1] = jj;
          if (startk < 1950)
            startk += 2;
          else
            startk = 0;
        }
      }
    }
  } while ((Place[pMover->sMapObject.ubX][pMover->sMapObject.ubY] == 1000) && (stopk != startk));

  if (Place[pMover->sMapObject.ubX][pMover->sMapObject.ubY] == 1000) // 1 ruch w kierunku
  {
    if (!pMover->type)
      return;
    int ddx, ddy;
    ddx = pMover->sMapObject.ubX - pMover->xe;
    if (ddx < 0)
      ddx = -1;
    if (ddx > 0)
      ddx = 1;
    ddy = pMover->sMapObject.ubY - pMover->ye;
    if (ddy < 0)
      ddy = -1;
    if (ddy > 0)
      ddy = 1;
    pMover->path[0][0] = ddx;
    pMover->path[0][1] = ddy;
    pMover->ispath = 1;
    pMover->xe += ddx; // przesun punkt docelowy
    pMover->ye += ddy;
    // if(!type&&udder<100){xp=xe;yp=ye;}
    // if(!type){xp=x;yp=y;}
    return;
  }

  i = pMover->sMapObject.ubX;
  j = pMover->sMapObject.ubY;
  Place[i][j] = 1000;
  min = 1000;
  BYTE mini, minj;
  if (Place[i - 1][j] < min) {
    min = Place[i - 1][j];
    mini = i - 1;
    minj = j;
  }
  if (Place[i + 1][j] < min) {
    min = Place[i + 1][j];
    mini = i + 1;
    minj = j;
  }
  if (Place[i][j - 1] < min) {
    min = Place[i][j - 1];
    mini = i;
    minj = j - 1;
  }
  if (Place[i][j + 1] < min) {
    min = Place[i][j + 1];
    mini = i;
    minj = j + 1;
  }
  if (Place[i - 1][j - 1] < min) {
    min = Place[i - 1][j - 1];
    mini = i - 1;
    minj = j - 1;
  }
  if (Place[i - 1][j + 1] < min) {
    min = Place[i - 1][j + 1];
    mini = i - 1;
    minj = j + 1;
  }
  if (Place[i + 1][j - 1] < min) {
    min = Place[i + 1][j - 1];
    mini = i + 1;
    minj = j - 1;
  }
  if (Place[i + 1][j + 1] < min) {
    min = Place[i + 1][j + 1];
    mini = i + 1;
    minj = j + 1;
  }

  if (min >= 1000)
    return;

  int Path[6][2];
  Path[0][0] = i - mini;
  Path[0][1] = j - minj;
  pMover->ispath = 1;
  if (min == 0) {
    pMover->path[0][0] = Path[0][0];
    pMover->path[0][1] = Path[0][1];
    return;
  }
  do {
    i = mini;
    j = minj;
    min = 1000;
    Place[i][j] = 1000;
    if (Place[i - 1][j] < min) {
      min = Place[i - 1][j];
      mini = i - 1;
      minj = j;
    }
    if (Place[i + 1][j] < min) {
      min = Place[i + 1][j];
      mini = i + 1;
      minj = j;
    }
    if (Place[i][j - 1] < min) {
      min = Place[i][j - 1];
      mini = i;
      minj = j - 1;
    }
    if (Place[i][j + 1] < min) {
      min = Place[i][j + 1];
      mini = i;
      minj = j + 1;
    }
    if (Place[i - 1][j - 1] < min) {
      min = Place[i - 1][j - 1];
      mini = i - 1;
      minj = j - 1;
    }
    if (Place[i - 1][j + 1] < min) {
      min = Place[i - 1][j + 1];
      mini = i - 1;
      minj = j + 1;
    }
    if (Place[i + 1][j - 1] < min) {
      min = Place[i + 1][j - 1];
      mini = i + 1;
      minj = j - 1;
    }
    if (Place[i + 1][j + 1] < min) {
      min = Place[i + 1][j + 1];
      mini = i + 1;
      minj = j + 1;
    }

    if (min >= 1000) {
      for (i = 0; i < pMover->ispath; i++) {
        pMover->path[i][0] = Path[pMover->ispath - i - 1][0];
        pMover->path[i][1] = Path[pMover->ispath - i - 1][1];
      }
      return;
    }
    Path[pMover->ispath][0] = i - mini;
    Path[pMover->ispath][1] = j - minj;
    pMover->ispath++;
  } while ((min != 0) && (pMover->ispath < 6));
  for (i = 0; i < pMover->ispath; i++) {
    pMover->path[i][0] = Path[pMover->ispath - i - 1][0];
    pMover->path[i][1] = Path[pMover->ispath - i - 1][1];
  }
}

tMover *moverTryGetAt(UBYTE ubX, UBYTE ubY) {
  if(place[ubX][ubY] && place[ubX][ubY]->eKind == MAP_OBJECT_KIND_MOVER) {
    return (tMover*)place[ubX][ubY];
  }
  return 0;
}

void moverMove(tMover *pMover) {
  pMover->inmove = 0;
  if (pMover->xe < 1)
    pMover->xe = 1;
  if (pMover->xe >= WORLD_SIZE_X)
    pMover->xe = WORLD_SIZE_X - 1;
  if (pMover->ye < 1)
    pMover->ye = 1;
  if (pMover->ye >= WORLD_SIZE_Y)
    pMover->ye = WORLD_SIZE_Y - 1;
  if ((pMover->sMapObject.ubX == pMover->xe) && (pMover->sMapObject.ubY == pMover->ye)) {
    pMover->commandN = 0;
    if (!pMover->type && pMover->command == 3) {
      pMover->command = 1;
      pMover->commandN = 1;
      pMover->delay = 0;
    }
    return;
  }
  if (pMover->type == 11 && pMover->magic > 10 && moverDistance(pMover) > 6) {
    pMover->commandN = 10;
    return;
  }
  place[pMover->sMapObject.ubX][pMover->sMapObject.ubY] = 0;
  if (!pMover->ispath)
    moverLabeling(pMover);

  place[pMover->sMapObject.ubX][pMover->sMapObject.ubY] = &pMover->sMapObject;
  if (!pMover->ispath) {
    if (!pMover->type) {
      tMover *mov;
      if (place[pMover->sMapObject.ubX - 1][pMover->sMapObject.ubY - 1]) {
        mov = moverTryGetAt(pMover->sMapObject.ubX - 1, pMover->sMapObject.ubY - 1);
        if (mov != NULL) {
          moverSetEnd(mov, pMover->sMapObject.ubX - 5, pMover->sMapObject.ubY - 5);
          moverSetCommand(mov, 1);
          // strcpy(Msg.msg,"Posun sie z -1 -1 !!!");
          /// Msg.licznik=20;
        }
      }
      if (place[pMover->sMapObject.ubX + 1][pMover->sMapObject.ubY + 1]) {
        mov = moverTryGetAt(pMover->sMapObject.ubX + 1, pMover->sMapObject.ubY + 1);
        if (mov != NULL) {
          moverSetEnd(mov, pMover->sMapObject.ubX + 5, pMover->sMapObject.ubY + 5);
          moverSetCommand(mov, 1);
          // strcpy(Msg.msg,"Posun sie z 1 1 !!!");
          // Msg.licznik=20;
        }
      }
      if (place[pMover->sMapObject.ubX - 1][pMover->sMapObject.ubY + 1]) {
        mov = moverTryGetAt(pMover->sMapObject.ubX - 1, pMover->sMapObject.ubY + 1);
        if (mov != NULL) {
          moverSetEnd(mov, pMover->sMapObject.ubX - 5, pMover->sMapObject.ubY + 5);
          moverSetCommand(mov, 1);
          // strcpy(Msg.msg,"Posun sie z -1 1 !!!");
          // Msg.licznik=20;
        }
      }
      pMover->drange++;
      if (pMover->drange > 14) {
        if (placeG[pMover->sMapObject.ubX][pMover->sMapObject.ubY] != 163) {
          pMover->xe = pMover->sMapObject.ubX;
          pMover->ye = pMover->sMapObject.ubY;
          if (pMover->udder < 100) {
            pMover->xp = pMover->sMapObject.ubX;
            pMover->yp = pMover->sMapObject.ubY;
          }
        }
        pMover->drange = 0;
      }
      pMover->delay = pMover->maxdelay;
      return;
    } else {
      pMover->delay = pMover->maxdelay;
      return;
    }
  }

  pMover->dx = pMover->path[pMover->ispath - 1][0];
  pMover->dy = pMover->path[pMover->ispath - 1][1];

  if (place[pMover->sMapObject.ubX - pMover->dx][pMover->sMapObject.ubY - pMover->dy] != 0) {
    if ((pMover->type) && (pMover->sMapObject.ubX - pMover->xe < 2) && (pMover->sMapObject.ubX - pMover->xe > -2) && (pMover->sMapObject.ubY - pMover->ye < 2) &&
        (pMover->sMapObject.ubY - pMover->ye > -2)) {
      pMover->commandN = 0;
    }
    if (!pMover->type) {
      // if(Msg.dzwiek<8){Msg.dzwiek=8;Msg.X=x;Msg.Y=y;}
      if (placeG[pMover->sMapObject.ubX][pMover->sMapObject.ubY] != 163) {
        pMover->xe = pMover->sMapObject.ubX;
        pMover->ye = pMover->sMapObject.ubY;
        if (pMover->udder < 100) {
          pMover->xp = pMover->sMapObject.ubX;
          pMover->yp = pMover->sMapObject.ubY;
        }
      }
      pMover->ispath = 0;
      return;
    }
    if (pMover->udder > 3) {
      pMover->udder = 0;
      pMover->ispath = 0;
      return;
    }
    pMover->udder++;
    pMover->delay = pMover->maxdelay;
    return;
  }
  pMover->ispath--;

  moverHide(pMover);
  pMover->sMapObject.ubX -= pMover->dx;
  pMover->sMapObject.ubY -= pMover->dy;
  moverShow(pMover);

  pMover->delay = pMover->maxdelay;
  // if(placeG[pMover->sMapObject.ubX][pMover->sMapObject.ubY]>34&&placeG[pMover->sMapObject.ubX][pMover->sMapObject.ubY]<46)delay-=2; //przyspieszenie na drodze
  pMover->inmove = 1;
  if (pMover->sMapObject.ubX == pMover->xe && pMover->sMapObject.ubY == pMover->ye) {
    pMover->ispath = 0;
  }
}

int moverLookAround(tMover *pMover) {
  if (!pMover->type) {
    pMover->command = 2;
    return 1;
  }

  int i, j, k = 1;
  int NoOfEnemies = 0;
  int NoOfOurs = 0;

  if (pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_CPU && pMover->type == MOVER_KIND_FARMER)
  {
    FindCow(pMover->sMapObject.ubX, pMover->sMapObject.ubY, &pMover->xe, &pMover->ye);
    if (pMover->xe != pMover->sMapObject.ubX || pMover->sMapObject.ubY != pMover->ye) {
      pMover->target = place[pMover->xe][pMover->ye];
      pMover->commandN = 2;
      return 1;
    }

    if (pMover->sMapObject.ubX != pMover->xm || pMover->sMapObject.ubY != pMover->ym) {
      pMover->xe = pMover->xm;
      pMover->ye = pMover->ym;
      pMover->commandN = 1;
    }
    return 0;
  }

  pMover->ispath = 0;
  pMover->target = 0;

  if (pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_CPU && pMover->hp > (pMover->maxhp - 20))
  {
    k = pMover->s_range + pMover->drange;
    for (i = pMover->sMapObject.ubX - k; i <= pMover->sMapObject.ubX + k && i < WORLD_SIZE_X - 1; i++) {
      for (j = pMover->sMapObject.ubY - k + 1; j <= pMover->sMapObject.ubY + k - 1 && j < WORLD_SIZE_Y - 1; j++) {
        if(place[i][j] && place[i][j]->eKind == MAP_OBJECT_KIND_MOVER) {
          if(place[i][j]->eTeam == MAP_OBJECT_TEAM_PLAYER) {
            NoOfEnemies++;
          }
          else {
            NoOfOurs++;
          }
        }
      }
    }

    if (NoOfEnemies > 2 && NoOfOurs == 1) {
      FindEnemy(pMover->sMapObject.ubX, pMover->sMapObject.ubY, &pMover->xe, &pMover->ye, 1);
      pMover->commandN = 1; // move
      return 0;
    }
  }

  const tMapObject *pOther = 0;
  tMapObjectTeam eEnemyTeam = pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_PLAYER ? MAP_OBJECT_TEAM_CPU : MAP_OBJECT_TEAM_PLAYER;
  for (k = 1; k <= pMover->s_range + pMover->drange; k++) {
    UBYTE ubStartX = MAX(0, pMover->sMapObject.ubX - k);
    UBYTE ubEndX = MIN(WORLD_SIZE_X - 1, pMover->sMapObject.ubX + k);
    UBYTE ubStartY = MAX(0, pMover->sMapObject.ubY - k);
    UBYTE ubEndY = MIN(WORLD_SIZE_Y - 1, pMover->sMapObject.ubY + k);
    for (i = ubStartX; i <= ubEndX; i++)
      for (j = ubStartY; j <= ubEndY; j++) {
        if (place[i][j] && place[i][j] != &pMover->sMapObject) {
          pOther = place[i][j];
          if (pOther->eTeam == eEnemyTeam && pOther->eKind == MAP_OBJECT_KIND_MOVER) {
            tMover *pOtherMover = (tMover*)pOther;
            pMover->target = pOther;

            if (pMover->type != 10) {
              return 1;
            }

            if ((!pOtherMover->type) || (pOtherMover->type == 9)) {
              return 1;
            }
          }
        }
      }
  }

  if (!pOther || pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_PLAYER || pMover->type == MOVER_KIND_MAGE) {
    // No attackable map objects in vincity
    // Player units don't auto-attack buildings
    // Mages don't auto-attack buildings
    return 0;
  }

  for (k = 1; k <= pMover->s_range + pMover->drange; k++) {
    UBYTE ubStartX = MAX(0, pMover->sMapObject.ubX - k);
    UBYTE ubEndX = MIN(WORLD_SIZE_X - 1, pMover->sMapObject.ubX + k);
    UBYTE ubStartY = MAX(0, pMover->sMapObject.ubY - k);
    UBYTE ubEndY = MIN(WORLD_SIZE_Y - 1, pMover->sMapObject.ubY + k);
    for (i = ubStartX; i <= ubEndX; i++) {
      for (j = ubStartY; j <= ubEndY; j++) {
        if (place[i][j] && place[i][j] != &pMover->sMapObject) {
          pOther = place[i][j];
          if (pOther->eTeam == eEnemyTeam) {
            pMover->target = pOther;
            return 1;
          }
        }
      }
    }
  }

  return 0;
}

int moverLokateTarget(tMover *pMover) {
  if (place[pMover->xe][pMover->ye] == pMover->target) {
    return 1;
  }

  // Check if target is still valid
  UBYTE xe = pMover->target->ubX;
  UBYTE ye = pMover->target->ubY;
  if (place[xe][ye] == pMover->target) {
    pMover->xe = xe;
    pMover->ye = ye;
    return 1;
  }

  return 0;
}

int moverDistance(tMover *pMover) {
  int maxx, maxy;
  maxx = pMover->sMapObject.ubX - pMover->xe;
  maxy = pMover->sMapObject.ubY - pMover->ye;
  if (maxx < 0)
    maxx = -maxx;
  if (maxy < 0)
    maxy = -maxy;
  if (maxy < maxx)
    return maxx;
  else
    return maxy;
}

void moverAttack(tMover *pMover) {
  pMover->inmove = 0;
  if (!pMover->target) {
    pMover->phase = 0;
    pMover->delay = pMover->maxdelay;
    return;
  }

  // wooden wall is internally a tree
  if (pMover->target->eTeam != MAP_OBJECT_TEAM_TREE) {
    pMover->ispath = 0;
  }
  else if (pMover->type != MOVER_KIND_AXE && pMover->type != MOVER_KIND_MAGE) {
    pMover->target = 0;
    pMover->mainTarget = 0;
  }

  if (!moverLokateTarget(pMover)) {
    pMover->target = 0;
    pMover->mainTarget = 0;
    pMover->phase = 0;
    if (pMover->command == 2) {
      pMover->commandN = 0;
    } else {
      if (pMover->command != 11)
        pMover->commandN = 5;
      else
        pMover->commandN = 11;
    }
    pMover->delay = pMover->maxdelay;
    return;
  }

  if (moverDistance(pMover) <= pMover->a_range) {
    if (pMover->type == 10) {
      pMover->ispath = 0;
      /// wstaznik na krowe

      pMover->inattack = 1;
      tMover *oldcow = (tMover*)pMover->target;
      if (oldcow != NULL) {
        moverSetCommand(oldcow, 123); // zmiana
      }

      pMover->dx = pMover->sMapObject.ubX - pMover->xe;
      pMover->dy = pMover->sMapObject.ubY - pMover->ye;
      if (pMover->dx > 1)
        pMover->dx = 1;
      if (pMover->dx < 0)
        pMover->dx = -1;
      if (pMover->dy > 1)
        pMover->dy = 1;
      if (pMover->dy < 0)
        pMover->dy = -1;
      pMover->delay = 10;
      pMover->target = 0;
      pMover->commandN = 0;
      return;
    }

    pMover->ispath = 0;
    if (pMover->missile.exist) {
      pMover->delay = pMover->maxdelay;
      return;
    }
    pMover->dx = pMover->sMapObject.ubX - pMover->xe;
    pMover->dy = pMover->sMapObject.ubY - pMover->ye;
    if (pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_CPU && pMover->type == MOVER_KIND_PRIESTESS && pMover->magic < 11) {
      moverSetEnd(pMover, pMover->sMapObject.ubX + (pMover->dx * 3), pMover->sMapObject.ubY + (pMover->dy * 3));
      moverMove(pMover);
      return;
    }
    if (pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_CPU && pMover->type == MOVER_KIND_MAGE && pMover->magic < 11) {
      moverSetEnd(pMover, pMover->sMapObject.ubX + (pMover->dx * 3), pMover->sMapObject.ubY + (pMover->dy * 3));
      moverMove(pMover);
      return;
    }
    if (pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_CPU && pMover->type == MOVER_KIND_PRIEST && pMover->magic < 21) {
      moverSetEnd(pMover, pMover->sMapObject.ubX + (pMover->dx * 3), pMover->sMapObject.ubY + (pMover->dy * 3));
      moverMove(pMover);
      return;
    } // ucieczka
    pMover->delay = pMover->maxdelay;

    if (pMover->type == MOVER_KIND_PRIESTESS && pMover->magic < 11) {
      pMover->phase = 0;
      pMover->dx = 0;
      pMover->dy = 0;
      return;
    }
    if (pMover->type == MOVER_KIND_PRIEST && pMover->magic < 21) {
      pMover->phase = 0;
      pMover->dx = 0;
      pMover->dy = 0;
      return;
    }
    if (pMover->type == MOVER_KIND_MAGE && pMover->magic < 21) {
      pMover->phase = 0;
      pMover->dx = 0;
      pMover->dy = 0;
      return;
    }
    if (pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_CPU && (pMover->type == MOVER_KIND_PRIEST || pMover->type == MOVER_KIND_PRIESTESS) && pMover->magic > 80) {
      pMover->phase = 0;
      pMover->dx = 0;
      pMover->dy = 0;
      pMover->commandN = 7;
      pMover->delay = 0;
      return;
    }

    if (pMover->type == MOVER_KIND_PRIESTESS)
      pMover->magic -= 10;
    if (pMover->type == MOVER_KIND_PRIEST)
      pMover->magic -= 20;
    if (pMover->type == MOVER_KIND_MAGE)
      pMover->magic -= 20;

    int baseDamage = pMover->damage;
    if (pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_CPU && place[pMover->xe][pMover->ye] && place[pMover->xe][pMover->ye]->eKind == MAP_OBJECT_KIND_TREE) // was comparing to 800, doesn't make sense
      baseDamage += 20;
    missileInit(&pMover->missile, pMover->sMapObject.ubX, pMover->sMapObject.ubY, pMover->xe, pMover->ye, baseDamage + ddamage[pMover->exp >> 4], pMover->type);

    if ((pMover->type == 4 || pMover->type == 11) && pMover->target->eTeam == MAP_OBJECT_TEAM_TREE) {
      pMover->mainTarget = 0;
    }
    if (pMover->target && pMover->target->eTeam != MAP_OBJECT_TEAM_TREE && pMover->exp < (15 * 16) - 5) {
      if (pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_CPU) {
        // NOTE: comment says "if not a building", but condition allowed them anyway
        pMover->exp++;
        if (pMover->type == MOVER_KIND_PRIESTESS || pMover->type == MOVER_KIND_PRIEST || pMover->type == MOVER_KIND_MAGE)
          pMover->exp += 3;
      }
    }
    pMover->inattack = 1;
    if (pMover->dx > 1)
      pMover->dx = 1;
    if (pMover->dx < 0)
      pMover->dx = -1;
    if (pMover->dy > 1)
      pMover->dy = 1;
    if (pMover->dy < 0)
      pMover->dy = -1;
    if (!placeN[pMover->sMapObject.ubX][pMover->sMapObject.ubY])
      placeN[pMover->sMapObject.ubX][pMover->sMapObject.ubY] = 1;
    if (!placeN[pMover->xe][pMover->ye])
      placeN[pMover->xe][pMover->ye] = 1;

    if (!pMover->mainTarget) {
      pMover->target = 0;
      if (pMover->command == 2)
        pMover->commandN = 0;
      else
        pMover->commandN = 5;
    }
    return;
  }
  if (pMover->command == 2 || pMover->command == 11) {
    moverMove(pMover);
  } else {
    pMover->target = 0;
    pMover->commandN = 5;
    pMover->delay = pMover->maxdelay;
  }
}

void moverRepare(tMover *pMover) {
  pMover->inmove = 0;
  pMover->inattack = 0;
  if (placeN[pMover->xe][pMover->ye] > 226 || placeG[pMover->xe][pMover->ye] == 47 ||
      (placeG[pMover->xe][pMover->ye] > 265 && placeG[pMover->xe][pMover->ye] < 277)) {
    pMover->commandN = 0;
    placeN[pMover->xe][pMover->ye] = 1;
    pMover->delay = pMover->maxdelay;
    return;
  }
  if (moverDistance(pMover) == 1) {
    pMover->ispath = 0;
    if (placeG[pMover->xe][pMover->ye] == 277 && place[pMover->xe][pMover->ye]) {
      pMover->delay = pMover->maxdelay;
      return;
    }
    pMover->dx = pMover->sMapObject.ubX - pMover->xe;
    pMover->dy = pMover->sMapObject.ubY - pMover->ye;
    pMover->delay = pMover->maxdelay;
    pMover->inattack = 1;
    if (pMover->dx > 1)
      pMover->dx = 1;
    if (pMover->dx < 0)
      pMover->dx = -1;
    if (pMover->dy > 1)
      pMover->dy = 1;
    if (pMover->dy < 0)
      pMover->dy = -1;
    if (placeN[pMover->xe][pMover->ye] < 220)
      placeN[pMover->xe][pMover->ye] = 220;
    else
      placeN[pMover->xe][pMover->ye]++;
    // if (Msg.dzwiek < 2) {
    //   Msg.dzwiek = 1;
    //   Msg.X = pMover->sMapObject.ubX;
    //   Msg.Y = pMover->sMapObject.ubY;
    // }
    return;
  }
  pMover->xe = pMover->xm;
  pMover->ye = pMover->ym;
  moverMove(pMover);
}

static void moverRunNonCow(tMover *pMover) {
  if (attack[pMover->sMapObject.ubX][pMover->sMapObject.ubY]) {
    int dem;
    if (pMover->marmour)
      attack[pMover->sMapObject.ubX][pMover->sMapObject.ubY] = 0;
    if (attack[pMover->sMapObject.ubX][pMover->sMapObject.ubY] > 0) {
      dem = (int)attack[pMover->sMapObject.ubX][pMover->sMapObject.ubY] - pMover->armour - darmour[pMover->exp >> 4];
      attack[pMover->sMapObject.ubX][pMover->sMapObject.ubY] = 0;
      if (dem <= 0)
        dem = 1;
      if (!pMover->mainTarget)
        if (pMover->command == 2)
          pMover->commandN = 0;
      if ((pMover->command == 1 || pMover->command == 8) && pMover->type != 10 &&
          placeG[pMover->xe][pMover->ye] != 256 && (pMover->hp > (pMover->maxhp >> 1)))
        pMover->commandN = 0;        // zatrzymaj idacych!
      if (placeN[pMover->sMapObject.ubX][pMover->sMapObject.ubY] > 60) // uciekaj z ognia
      {
        for (int ii = pMover->sMapObject.ubX - 1; ii <= pMover->sMapObject.ubX + 1; ii++) {
          for (int jj = pMover->sMapObject.ubY - 1; jj <= pMover->sMapObject.ubY + 1; jj++) {
            if (ii > 0 && jj > 0 && ii < WORLD_SIZE_X - 1 && jj < WORLD_SIZE_Y - 1) {
              if (!(place[ii][jj]) && (placeN[ii][jj] < 2)) {
                pMover->xe = ii;
                pMover->ye = jj;
                moverSetCommand(pMover, 1);
              }
            }
          }
        }
      }
      if (pMover->type == 3 && pMover->magic > 49) {
        pMover->commandN = 9; // magiczna tarcza
        if (pMover->exp < 100)
          pMover->exp += 4;
      }
      if (pMover->hp > dem) {
        pMover->hp -= dem;
        pMover->ShowHit = 5;
        if (pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_CPU)
          pMover->drange = 6;
      }
      else {
        pMover->exist = MOVER_EXIST_ROT;
        pMover->hp = 0;
        pMover->dx = 0;
        pMover->dy = 0;
        pMover->ispath = 0;
        pMover->delay = 400;
        moverHide(pMover);
        pMover->inmove = 0;
        // int kk = 35 + pMover->type * 11;
        // if (Msg.dzwiek < kk) {
        //   Msg.dzwiek = kk;
        //   Msg.X = pMover->sMapObject.ubX;
        //   Msg.Y = pMover->sMapObject.ubY;
        // }
        return;
      }
      if (pMover->hp < ((UBYTE)g_eDifficulty >> 4) && pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_CPU && pMover->command != 1) //&&diff
      { // jezeli chory to udaj sie do swiatyni na leczenie
        int xl = pMover->sMapObject.ubX, yl = pMover->sMapObject.ubY;
        FindHolyPlace(&xl, &yl);
        if (xl != pMover->sMapObject.ubX || yl != pMover->sMapObject.ubY) {
          moverSetEnd(pMover, xl, yl);
          moverSetCommand(pMover, 1);
        }
      }
    }
  }

  if (pMover->marmour)
    pMover->marmour--;

  if (pMover->delay)
    return; // wyjdz jezeli nie koniec ruchu

  if (pMover->drange)
    pMover->drange--;

  if (pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_CPU && !pMover->command && placeG[pMover->sMapObject.ubX][pMover->sMapObject.ubY] == 163) //??? nie blokuj obory
  {
    moverSetEnd(pMover, pMover->sMapObject.ubX + 2, pMover->sMapObject.ubY - 3);
    moverSetCommand(pMover, 1);
  }
  /*   if(hp<5+(diff>>4)&&IFF==2&&!drange&&command!=1)//&&diff
     {// jezeli chory to udaj sie do swiatyni na leczenie
         int xl=x,yl=y;
         if(placeG[pMover->xe][pMover->ye]!=256)
         {
             FindHolyPlace(&xl,&yl);
             if(xl!=x||yl!=y)
             {
                 SetEnd(xl,yl);
                 SetCommand(1);
             }
         }
         else
         {
             SetCommand(1);
         }
     }*/
  if (pMover->hp == pMover->maxhp && pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_CPU && !pMover->command &&
      placeG[pMover->sMapObject.ubX][pMover->sMapObject.ubY] == 256) { // wyleczony odsun sie z miejsca leczenia
    moverSetEnd(pMover, pMover->sMapObject.ubX + 5, pMover->sMapObject.ubY + 5);
    moverSetCommand(pMover, 1);
  }
  pMover->inattack = 0;
  pMover->phase = 0;
  if (placeG[pMover->sMapObject.ubX][pMover->sMapObject.ubY] == 256 && pMover->hp < pMover->maxhp) {
    pMover->hp += 4; // leczenie w swietym miejscu
    if (pMover->hp > pMover->maxhp)
      pMover->hp = pMover->maxhp;
    if (pMover->type == 3 || pMover->type == 4 || pMover->type == 9 || pMover->type == 11)
      pMover->magic += 5;
  }
  if (pMover->type == 3 || pMover->type == 4 || pMover->type == 9 || pMover->type == 11) {
    pMover->magic++;
    if (pMover->type == 11)
      pMover->magic++;
    if (pMover->magic > dmagic[pMover->exp >> 4])
      pMover->magic = dmagic[pMover->exp >> 4];
    if (pMover->type == 9 && pMover->magic > 9 && pMover->hp < pMover->maxhp) { // autoleczenie strzygi
      pMover->hp += 10;
      pMover->magic -= 10;
    }
  }

  if (pMover->command == 8 && pMover->commandN != 8) {
    placeN[pMover->xe][pMover->ye] = 1; // jezeli konczysz robote to wyczysc po sobie
  }
  if (pMover->command == 10) // teleport
  {
    pMover->commandN = 0;

    moverHide(pMover);
    if (place[pMover->xe][pMover->ye] || pMover->xe < 1 || pMover->ye < 1 || pMover->xe > WORLD_SIZE_X - 2 || pMover->ye > WORLD_SIZE_X - 2)
      pMover->xe += 3; //=0
    if (place[pMover->xe][pMover->ye] || pMover->xe < 1 || pMover->ye < 1 || pMover->xe > WORLD_SIZE_X - 2 || pMover->ye > WORLD_SIZE_X - 2)
      pMover->ye += 3; // 1
    if (place[pMover->xe][pMover->ye] || pMover->xe < 1 || pMover->ye < 1 || pMover->xe > WORLD_SIZE_X - 2 || pMover->ye > WORLD_SIZE_X - 2)
      pMover->xe -= 3; // 2
    if (place[pMover->xe][pMover->ye] || pMover->xe < 1 || pMover->ye < 1 || pMover->xe > WORLD_SIZE_X - 2 || pMover->ye > WORLD_SIZE_X - 2)
      pMover->xe -= 3; // 3
    if (place[pMover->xe][pMover->ye] || pMover->xe < 1 || pMover->ye < 1 || pMover->xe > WORLD_SIZE_X - 2 || pMover->ye > WORLD_SIZE_X - 2)
      pMover->ye -= 3; // 4
    if (place[pMover->xe][pMover->ye] || pMover->xe < 1 || pMover->ye < 1 || pMover->xe > WORLD_SIZE_X - 2 || pMover->ye > WORLD_SIZE_X - 2)
      pMover->ye -= 3; // 5
    if (place[pMover->xe][pMover->ye] || pMover->xe < 1 || pMover->ye < 1 || pMover->xe > WORLD_SIZE_X - 2 || pMover->ye > WORLD_SIZE_X - 2)
      pMover->xe += 3; // 6
    if (place[pMover->xe][pMover->ye] || pMover->xe < 1 || pMover->ye < 1 || pMover->xe > WORLD_SIZE_X - 2 || pMover->ye > WORLD_SIZE_X - 2)
      pMover->xe += 3; // 7
    if (place[pMover->xe][pMover->ye] || pMover->xe < 1 || pMover->ye < 1 || pMover->xe > WORLD_SIZE_X - 2 || pMover->ye > WORLD_SIZE_X - 2) {
      pMover->xe = pMover->sMapObject.ubX;
      pMover->ye = pMover->sMapObject.ubY;
    }
    pMover->sMapObject.ubX = pMover->xe;
    pMover->sMapObject.ubY = pMover->ye;
    moverShow(pMover);

    pMover->inattack = 1;
    pMover->delay = pMover->maxdelay;
    pMover->command = pMover->commandN;
    return;
  }
  pMover->command = pMover->commandN;

  switch (pMover->command) {
  case 123:
    NewCow(pMover);
    return;
  case 0:
    if (moverLookAround(pMover)) {
      pMover->commandN = 2;
      return;
    } // jezeli nic nie robi to rozejzec sie
    break;
  case 1:
    if (pMover->sMapObject.ubX == pMover->xe && pMover->sMapObject.ubY == pMover->ye) {
      pMover->commandN = 0;
      pMover->inmove = 0;
      return;
    } else {
      moverMove(pMover);
      return;
    } // jezeli idzie to idz

  case 2:
  case 6:
    moverAttack(pMover);
    return; // jezeli atak to atakuj
  case 5:
    if (moverLookAround(pMover)) {
      pMover->commandN = 6;
      return;
    } // jezeli nic nie robi to rozejzec sie
    break;
  case 7:
    if (pMover->magic >= 80) {
      pMover->inattack = moverDistance(pMover);
      if (pMover->inattack > 9) {
        pMover->inattack = 0;
        moverMove(pMover);
        return;
      }
      if (pMover->missile.exist)
        return;
      pMover->inmove = 0;
      pMover->inattack = 1;
      pMover->dx = 0;
      pMover->dy = 0;
      int Mtype = 14;
      if (pMover->type == 3)
        Mtype = 13;
      int xxe = pMover->xe + ((pMover->magic & 2) >> 1) - ((pMover->magic & 4) >> 2);
      int yye = pMover->ye + ((pMover->magic & 2) >> 1) - ((pMover->magic & 4) >> 2);
      missileInit(&pMover->missile, xxe + 1, yye - 4, xxe, yye, pMover->damage - (pMover->type - 3) * 20, Mtype);
      pMover->magic -= 5;
      pMover->delay = pMover->maxdelay;
      if (!place[pMover->xe][pMover->ye])
        pMover->commandN = 0;
    } else
      pMover->commandN = 0;
    break;
  case 8:
    moverRepare(pMover);
    return;
  case 9:
    pMover->commandN = 0;
    if (pMover->magic > 49 && pMover->type == 3) {
      pMover->inattack = 1;
      pMover->magic -= 50;
      pMover->marmour = 100;
      if (pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_PLAYER)
        pMover->marmour = 200;
      // if (Msg.dzwiek < 16) {
      //   Msg.dzwiek = 10;
      //   Msg.X = pMover->sMapObject.ubX;
      //   Msg.Y = pMover->sMapObject.ubY;
      // }
    }
    if (pMover->magic > 24 && pMover->type == 4) { // widzenie
      pMover->inattack = 1;
      pMover->magic -= 25;
      pMover->marmour = 5;
      // if (Msg.dzwiek < 12) {
      //   Msg.dzwiek = 11;
      //   Msg.X = pMover->sMapObject.ubX;
      //   Msg.Y = pMover->sMapObject.ubY;
      // }
      int xx, yy, i, j;
      for (i = 1; i < WORLD_SIZE_X; i++)
        for (j = 1; j < WORLD_SIZE_Y; j++) {
          xx = ABS(pMover->sMapObject.ubX - i);
          yy = ABS(pMover->sMapObject.ubY - j);
          if (xx + yy < 18 && yy < 14 && xx < 14 && !placeN[i][j])
            placeN[i][j] = 1;
        }
    }
    break;
  case 10: // teleportacja
    if (pMover->magic > 10) {
      pMover->inmove = 0;
      pMover->inattack = 0;
      pMover->inattack = 1;
      pMover->dx = 0;
      pMover->dy = 0;
      pMover->magic -= 10;
      pMover->delay = pMover->maxdelay;
    }
    pMover->commandN = 0;
    break;
  case 11: // rabanie palisady
    if (pMover->type != 1 && pMover->type != 4) {
      pMover->command = 0;
      pMover->commandN = 0;
      return;
    }
    FindEnemy(pMover->sMapObject.ubX, pMover->sMapObject.ubY, &pMover->xe, &pMover->ye, 2);
    pMover->target = place[pMover->xe][pMover->ye];
    if (pMover->xe == 32 && pMover->ye == 32)
      pMover->target = 0;
    if (pMover->target == &pMover->sMapObject)
      pMover->target = 0;
    if (!pMover->target) {
      moverLookAround(pMover);
    }
    if (pMover->target) {
      moverAttack(pMover);
    }
    pMover->commandN = 11;
    pMover->target = 0;
    return;
  }
  pMover->inmove = 0;
  pMover->delay = pMover->maxdelay;
}

int moverMilk(tMover *pMover) {
  if (pMover->command != 4)
    return 0;
  if (pMover->exist != 1)
    return 0;
  if (placeG[pMover->sMapObject.ubX][pMover->sMapObject.ubY - 1] != 160)
    return 0;

  pMover->udder--;
  if (!pMover->udder) {
    pMover->xe = pMover->xp;
    pMover->ye = pMover->yp;
    pMover->commandN = 1;
    return 0;
  }
  return 1; // wymie
}

void moverFindGrass(tMover *pMover) {
  int max = 0, maxx = 0, maxy = 0;

  for (int range = 1; range < 5; range++) {
    max = 0;
    if (pMover->sMapObject.ubX & 1) {
      for (int i = pMover->sMapObject.ubX - range; i <= pMover->sMapObject.ubX + range; i++)
        for (int j = pMover->sMapObject.ubY - range; j <= pMover->sMapObject.ubY + range; j++)
          if (i > 0 && j > 0 && i < WORLD_SIZE_X - 1 && j < WORLD_SIZE_Y - 1)
            if (place[i][j] == 0 && placeG[i][j] > max && placeG[i][j] < 9) {
              max = placeG[i][j];
              maxx = i;
              maxy = j;
            }
    } else {
      for (int i = pMover->sMapObject.ubX + range; i >= pMover->sMapObject.ubX - range; i--)
        for (int j = pMover->sMapObject.ubY + range; j >= pMover->sMapObject.ubY - range; j--)
          if (i > 0 && j > 0 && i < WORLD_SIZE_X - 1 && j < WORLD_SIZE_Y - 1)
            if (place[i][j] == 0 && placeG[i][j] > max && placeG[i][j] < 9) {
              max = placeG[i][j];
              maxx = i;
              maxy = j;
            }
    }

    if (max) {
      pMover->commandN = 1;
      moverSetEnd(pMover, maxx, maxy);
      return;
    }
  }
}

void moverGraze(tMover *pMover) {
  int grass = placeG[pMover->sMapObject.ubX][pMover->sMapObject.ubY];
  pMover->inmove = 0;

  if (!grass || grass > 8) {
    moverFindGrass(pMover);
    pMover->delay = pMover->maxdelay;
    return;
  }
  pMover->inattack = 1;
  pMover->udder += grass;
  if (pMover->udder > 100)
    pMover->udder = 100;
  placeG[pMover->sMapObject.ubX][pMover->sMapObject.ubY]--;
  if (pMover->udder >= 100) {
    int k = 0;
    if (pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_CPU)
      k = 1;

    if (placeG[pMover->xm][pMover->ym - 1] != 160) {
      FindShed(k, &pMover->xm, &pMover->ym);
    }
    pMover->xe = pMover->xm;
    pMover->ye = pMover->ym;
    pMover->commandN = 3;
  } // wracaj
  pMover->delay = pMover->maxdelay;
}

static void moverRunCow(tMover *pMover) // krowy
{
  // command
  // 1-idz na pastwisko
  // 2-harwestuj
  // 3-wracaj
  // 4- oddaj mleko
  // 5-uciekaj

  if (attack[pMover->sMapObject.ubX][pMover->sMapObject.ubY]) {
    int dem;
    pMover->commandN = 5; // ucieczka
    dem = attack[pMover->sMapObject.ubX][pMover->sMapObject.ubY] - pMover->armour;
    attack[pMover->sMapObject.ubX][pMover->sMapObject.ubY] = 0;
    if (dem > 0)
      pMover->hp -= dem;
    if (dem > 4)
      pMover->ShowHit = 4;
    else
      pMover->ShowHit = 3;
    if (pMover->hp <= 0) {
      pMover->exist = MOVER_EXIST_NONE;
      pMover->dx = 0;
      pMover->dy = 0;
      pMover->delay = 200;
      pMover->ispath = 0;
      moverHide(pMover);
      pMover->inmove = 0;
      // if (Msg.dzwiek < 8) {
      //   Msg.dzwiek = 8;
      //   Msg.X = pMover->sMapObject.ubX;
      //   Msg.Y = pMover->sMapObject.ubY;
      // }
      return;
    }
  }

  if (pMover->delay) {
    return; // wyjdz jezeli nie koniec ruchu
  }

  pMover->inattack = 0;
  pMover->phase = 0;
  if (placeG[pMover->sMapObject.ubX][pMover->sMapObject.ubY] == 256 && pMover->hp < pMover->maxhp)
    pMover->hp++; // leczenie w swietym miejscu
  pMover->command = pMover->commandN;
  if (pMover->command == 1 && pMover->sMapObject.ubX == pMover->xe && pMover->sMapObject.ubY == pMover->ye) {
    if (pMover->sMapObject.ubX == pMover->xm && pMover->sMapObject.ubY == pMover->ym) {
      pMover->commandN = 4; // daj sie doic
      pMover->inmove = 0;
      return;
    } else {
      if (pMover->udder < 100) {
        pMover->commandN = 2;
        pMover->inmove = 0;
        return;
      } else {
        if (placeG[pMover->xm][pMover->ym - 1] != 160) {
          int k = 0;
          if (pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_CPU)
            k = 1;
          FindShed(k, &pMover->xm, &pMover->ym);
        }
        pMover->xe = pMover->xm;
        pMover->ye = pMover->ym;
        pMover->commandN = 1;
        pMover->inmove = 0;
        return;
      }
    } // doszedles to graze
  }

  if (pMover->command == 123) {
    NewCow(pMover);
    return;
  }
  if (pMover->command == 1) {
    moverMove(pMover);
    return;
  }
  if (pMover->command == 2) {
    moverGraze(pMover);
    return;
  } // jezeli nic nie robi to rozejzec sie
  if (pMover->command == 3 && pMover->sMapObject.ubX == pMover->xm && pMover->sMapObject.ubY == pMover->ym) {
    pMover->commandN = 4;
    pMover->inmove = 0;
    return;
  } // oddawaj
  if (pMover->command == 3) {
    moverMove(pMover);
    return;
  } // wracaj
  if (pMover->command == 4)
    return;
  if (pMover->command == 5) {
    // ucieczka do obory
    int k = 0;
    if (pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_CPU)
      k = 1;

    if (placeG[pMover->xm][pMover->ym - 1] != 160) {
      for (int i = 0; i < 20; i++) {
        if (castle[k].b[i].type == 2 && castle[k].b[i].exist == 1) {
          pMover->xm = castle[k].b[i].sMapObject.ubX;
          pMover->ym = castle[k].b[i].sMapObject.ubY + 2;
        }
      }
    }
    pMover->xe = pMover->xm;
    pMover->ye = pMover->ym;
    pMover->commandN = 1;
    if (pMover->sMapObject.ubX == pMover->xm && pMover->sMapObject.ubY == pMover->ym) {
      pMover->xe = pMover->xp;
      pMover->ye = pMover->yp;
    }
    return;
  } // uciekaj
  pMover->inmove = 0;
  pMover->commandN = 2;
  pMover->delay = pMover->maxdelay;
}

void moverRun(tMover *pMover) {
  switch(pMover->exist) {
    case MOVER_EXIST_NONE:
      return;
    case MOVER_EXIST_ROT:
      if(pMover->delay < 1) {
        pMover->exist = MOVER_EXIST_NONE;
      }
      else {
        pMover->delay--;
      }
      break;
    case MOVER_EXIST_ALIVE:
      if (pMover->type) {
        moverRunNonCow(pMover);
      }
      else {
        moverRunCow(pMover);
      }
      break;
  }
}

void moverSetEnd(tMover *pMover, int x0, int y0) {
  if (x0 == 0)
    x0 = 1;
  if (y0 == 0)
    y0 = 1;
  if (y0 > WORLD_SIZE_Y - 2)
    y0 = WORLD_SIZE_Y - 2;
  if (x0 > WORLD_SIZE_X - 2)
    x0 = WORLD_SIZE_X - 2;

  if (pMover->type == MOVER_KIND_COW) {
    if (
      (placeG[x0][y0] == PICTURE_KIND_BUILDING_1_FULL_6 && place[x0][y0 - 1]->eTeam == MAP_OBJECT_TEAM_PLAYER) ||
      (PICTURE_KIND_BUILDING_1_FULL_0 < placeG[x0][y0] && placeG[x0][y0] < PICTURE_KIND_BUILDING_1_FULL_9 && place[x0][y0]->eTeam == MAP_OBJECT_TEAM_PLAYER)
    ) {
      for (int i = x0 - 3; i < x0 + 1; i++)
        for (int j = y0; j < y0 + 3; j++) {
          if (placeG[i][j] == 163) {
            pMover->xm = i;
            pMover->ym = j;
            pMover->ispath = 0;
            // strcpy(Msg.msg, "Muuu!!!");
            // Msg.licznik = 20;
            return;
          }
        }
      return;
    }
    else {
      pMover->xp = x0;
      pMover->yp = y0;
    }
  }
  pMover->xe = x0;
  pMover->ye = y0;
  if (pMover->commandN == 8 || pMover->command == 8) {
    pMover->xm = x0;
    pMover->ym = y0;
  }
  pMover->ispath = 0;
}

void moverPrepare(tMover *pMover, int x0, int y0, int typ) {
  missileMove(&pMover->missile);
  if (!pMover->dx && !pMover->dy)
    pMover->dy = 1;
  if (pMover->phase > 2 && !pMover->inattack)
    pMover->phase = 0;
  if (pMover->inmove) {
    pMover->phase = Phase[pMover->type][pMover->delay];
  }
  else if (pMover->inattack) {
    if (pMover->delay > pMover->maxdelay - 2) {
      pMover->phase = 3;
    }
    if (pMover->delay == Phase[pMover->type][17]) {
      pMover->phase = 4;
    }
    if (pMover->delay == Phase[pMover->type][18]) {
      pMover->phase = 1;
      if (!pMover->type)
        pMover->phase = 0;
    }
  }

  if (!pMover->command)
    pMover->inmove = 0;
  if ((pMover->delay == 3) && (!pMover->command || pMover->command == 5)) // obracanie
  {
    if (pMover->faza < 4) {
      pMover->faza++;
    }
    else {
      pMover->faza = 0;
      pMover->dx++;
      if (pMover->dx > 1) {
        pMover->dx = -1;
        pMover->dy--;
      }
      if (pMover->dy < -1)
        pMover->dy = 1;
    }
  }
  if (pMover->sMapObject.ubX < (x0 - 1) || pMover->sMapObject.ubY < (y0 - 1) || pMover->sMapObject.ubX > (x0 + 17) || pMover->sMapObject.ubY > (y0 + 14))
    pMover->visible = 0; // ze wzgledu na LookUpTable
  else
    pMover->visible = 1;
  if (pMover->visible) {
    if (pMover->inmove == 1) {
      if (pMover->dx > 0)
        pMover->xr = Xe[pMover->sMapObject.ubX - x0 + 1] + (int)shiftX[pMover->type][pMover->delay] - 16;
      if (pMover->dx < 0)
        pMover->xr = Xe[pMover->sMapObject.ubX - x0 + 1] - (int)shiftX[pMover->type][pMover->delay] - 16;
      if (!pMover->dx)
        pMover->xr = Xe[pMover->sMapObject.ubX - x0 + 1] - 16;
      if (pMover->dy > 0)
        pMover->yr = Ye[pMover->sMapObject.ubY - y0 + 1] + (int)shiftY[pMover->type][pMover->delay] - 14;
      if (pMover->dy < 0)
        pMover->yr = Ye[pMover->sMapObject.ubY - y0 + 1] - (int)shiftY[pMover->type][pMover->delay] - 14;
      if (!pMover->dy)
        pMover->yr = Ye[pMover->sMapObject.ubY - y0 + 1] - 14;
    } else {
      pMover->xr = Xe[pMover->sMapObject.ubX - x0 + 1] - 16;
      pMover->yr = Ye[pMover->sMapObject.ubY - y0 + 1] - 14;
    }
    if (pMover->inattack && pMover->phase > 2 &&
        (pMover->type == 1 || pMover->type == 5 || (pMover->type > 6 && pMover->type < 10))) {
      if (pMover->dy > 0)
        pMover->yr -= 7;
      if (pMover->dx > 0)
        pMover->xr -= 8;
    }
    if (pMover->xr > 0 && pMover->xr < 282 && pMover->yr > 0 && pMover->yr < 194) {
    } else
      pMover->visible = 0;
  }
  if (typ) {
    if (pMover->ShowHit)
      pMover->ShowHit--;
    if (pMover->delay)
      pMover->delay--;
  }
}

static void moverShowRot(tMover *pMover) {
  UBYTE ubStage;
  if (pMover->delay < 70)
    ubStage = 0;
  else if (pMover->delay < 200)
    ubStage = 1;
  else
    ubStage = 2;

  if (ubStage) {
    // 1st phase - use mover-specific frames
    gfxDrawImageMaskedClipped(pMover->xr, pMover->yr, &(*pMover->pFrameset)[5 - ubStage][1][1]);
  }
  else {
    // 2nd phasae - use generic dead frames
    if (pMover->type == MOVER_KIND_BEAR)
      ubStage = 2;
    else if (pMover->type == MOVER_KIND_COW)
      ubStage = 1;
    else
      ubStage = 0;

    if (pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_PLAYER) {
      gfxDrawImageMaskedClipped(pMover->xr, pMover->yr, &dead[ubStage]);
    }
    else {
      PutImageChange13h(pMover->xr, pMover->yr, &dead[ubStage], 1, color1, color2);
    }
  }
}

static void moverShowSelection(tMover *pMover) {
  int a = 0, b = 0;
  if (pMover->inattack && pMover->phase > 2 &&
      (pMover->type == 1 || pMover->type == 5 || pMover->type == 7 || pMover->type == 8 || pMover->type == 9)) {
    if (pMover->dy > 0)
      b = 7;
    if (pMover->dx > 0)
      a = 8;
  }

  int color = LightGreen;
  if (pMover->hp < (pMover->maxhp >> 1))
    color = Yellow;
  if (pMover->hp < (pMover->maxhp >> 2))
    color = LightRed;
  Bar13h(pMover->xr + a + 1, pMover->yr + b - 2, pMover->xr + a + 15, pMover->yr + b, Black);
  int hh = (pMover->hp * 14 / pMover->maxhp);
  if (!hh)
    hh = 1;
  Bar13h(pMover->xr + a + 1, pMover->yr + b - 2, pMover->xr + a + 1 + hh, pMover->yr + b, color);
  if (pMover->magic && pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_PLAYER) {
    hh = (pMover->magic * 14 / dmagic[pMover->exp >> 4]);
    Bar13h(pMover->xr + a + 16, pMover->yr + b + 14 - hh, pMover->xr + a + 17, pMover->yr + b + 14, LightBlue);
  }
  if (!pMover->type && pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_PLAYER) {
    hh = ((pMover->udder * 14) / 100);
    if (pMover->udder < 4)
      hh = 0;

    if (hh)
      Bar13h(pMover->xr + a + 16, pMover->yr + b + 14 - hh, pMover->xr + a + 17, pMover->yr + b + 14, White);
  }
}

void moverShowS(tMover *pMover) {
  if (!pMover->exist || !pMover->visible || !placeN[pMover->sMapObject.ubX][pMover->sMapObject.ubY]) {
    return;
  }

  if (pMover->exist == MOVER_EXIST_ROT) {
    moverShowRot(pMover);
    return;
  }

  if (!pMover->dx && !pMover->dy) {
    pMover->dy = 1;
  }

  if (pMover->wybrany) {
    moverShowSelection(pMover);
  }

  // There was a flipped draw of mover image here, it's gone now.
  // Beware: mover dx and dy are in reverse orientation as frames!
  if ((*pMover->pFrameset)[pMover->phase][1 - pMover->dx][1 - pMover->dy].pBitmap) {
    gfxDrawImageMaskedClipped(pMover->xr, pMover->yr, &(*pMover->pFrameset)[pMover->phase][1 - pMover->dx][1 - pMover->dy]);
  }

  if (pMover->marmour) {
    gfxDrawImageMaskedClipped(pMover->xr, pMover->yr, &picture[278 + (pMover->marmour & 3)]);
  }

  if (placeG[pMover->sMapObject.ubX][pMover->sMapObject.ubY] == 256 && pMover->hp < pMover->maxhp) {
    PutImageChange13h(pMover->xr, pMover->yr, &picture[282 + (pMover->delay & 1)], 1, Red, LightBlue);
  }

  if (pMover->ShowHit > 2) {
    gfxDrawImageMaskedClipped(pMover->xr, pMover->yr, &Hit[1]);
  }
  else if (pMover->ShowHit > 0) {
    gfxDrawImageMaskedClipped(pMover->xr, pMover->yr, &Hit[0]);
  }
}

void moverShow(tMover *pMover) {
  int i, j;
  place[pMover->sMapObject.ubX][pMover->sMapObject.ubY] = &pMover->sMapObject;
  if (pMover->sMapObject.eTeam == MAP_OBJECT_TEAM_PLAYER) {
    for (i = -pMover->s_range; i <= pMover->s_range; i++) {
      if (pMover->sMapObject.ubX + i > 0 && pMover->sMapObject.ubX + i < WORLD_SIZE_X)
        for (j = -pMover->s_range; j <= pMover->s_range; j++) {
          if (pMover->sMapObject.ubY + j > 0 && pMover->sMapObject.ubY + j < WORLD_SIZE_Y && !(placeN[pMover->sMapObject.ubX + i][pMover->sMapObject.ubY + j])) {
            if ((i != -pMover->s_range || j != -pMover->s_range) &&
                (i != -pMover->s_range || j != pMover->s_range) &&
                (i != pMover->s_range || j != -pMover->s_range) &&
                (i != pMover->s_range || j != pMover->s_range)) // bez rogow
            {
              placeN[pMover->sMapObject.ubX + i][pMover->sMapObject.ubY + j] |= 1;
            }
          }
        }
    }
  }
}

void moverHide(tMover *pMover) {
	place[pMover->sMapObject.ubX][pMover->sMapObject.ubY] = 0;
}

int moverOK(const tMover *pMover) {
	return pMover->exist;
}

#pragma endregion

tMoverFrameset g_pMoverFrames[MOVER_KIND_COUNT];
int PlaceUsed;
