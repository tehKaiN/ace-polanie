#include "mover.h"
#include <mini_std/stdio.h>
#include "bitmap_pair.h"

typedef struct tMixedBitmaps {
	tBitmapPair sPairNarrow;
	tBitmapPair sPairWide;
} tMixedBitmaps;

static const tUbCoordYX pWideSizes[] = {
	{.ubX = 24, .ubY = 21},
	{.ubX = 24, .ubY = 14},
	{.ubX = 24, .ubY = 21},
	{.ubX = 16, .ubY = 21},
	{.ubX = 16, .ubY = 14},
	{.ubX = 16, .ubY = 21},
};

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
		for(UBYTE ubX = 0; ubX < 2; ++ubX) {
			for(UBYTE ubY = 0; ubY < 2; ++ubY) {
				movers[ubPhase][eKind][ubX][ubY].pBitmap = pBmPair->pFrames;
				movers[ubPhase][eKind][ubX][ubY].pMask = pBmPair->pMasks;
				movers[ubPhase][eKind][ubX][ubY].uwWidth = 16;
				movers[ubPhase][eKind][ubX][ubY].uwHeight = 14;
				movers[ubPhase][eKind][ubX][ubY].uwOffsY = uwOffsY;
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
		for(UBYTE ubX = 0; ubX < 2; ++ubX) {
			for(UBYTE ubY = 0; ubY < 2; ++ubY) {
				movers[ubPhase][eKind][ubX][ubY].pBitmap = pMixed->sPairNarrow.pFrames;
				movers[ubPhase][eKind][ubX][ubY].pMask = pMixed->sPairNarrow.pMasks;
				movers[ubPhase][eKind][ubX][ubY].uwWidth = 16;
				movers[ubPhase][eKind][ubX][ubY].uwHeight = 14;
				movers[ubPhase][eKind][ubX][ubY].uwOffsY = uwOffsY;
				uwOffsY += 14;
				++ubFrameIndex;
			}
		}
	}

	uwOffsY = 0;
	for(UBYTE ubPhase = MOVER_PHASE_ACTION1; ubPhase < MOVER_PHASE_COUNT; ++ubPhase) {
		ubFrameIndex = 0;
		for(UBYTE ubX = 0; ubX < 2; ++ubX) {
			for(UBYTE ubY = 0; ubY < 2; ++ubY) {
				movers[ubPhase][eKind][ubX][ubY].pBitmap = pMixed->sPairWide.pFrames;
				movers[ubPhase][eKind][ubX][ubY].pMask = pMixed->sPairWide.pMasks;
				movers[ubPhase][eKind][ubX][ubY].uwWidth = pWideSizes[ubFrameIndex].ubX;
				movers[ubPhase][eKind][ubX][ubY].uwHeight = pWideSizes[ubFrameIndex].ubY;
				movers[ubPhase][eKind][ubX][ubY].uwOffsY = uwOffsY;
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

void moverCreate(void) {
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

void moverDestroy(void) {
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

tImage movers[MOVER_PHASE_COUNT][MOVER_KIND_COUNT][3][3]; // faza:typ:dx:dy

// TODO: misc
// static tBitMap *s_pShadowBitmap;
// static tBitMap *s_pShadowMask;
