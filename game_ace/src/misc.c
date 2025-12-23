#include "misc.h"
#include "bitmap_pair.h"

static tBitmapPair s_sFirePair;
static tBitmapPair s_sTreePair;
static tBitmapPair s_sShadowPair;

void miscCreate(void) {
	bitmapPairCreate(&s_sFirePair, "fire");
	bitmapPairCreate(&s_sTreePair, "tree");
	bitmapPairCreate(&s_sShadowPair, "movers/shadow");

	UWORD uwOffsY = 0;
	for(UBYTE i = 0; i < MISC_FIRE_FRAME_COUNT; ++i) {
		fire[i].pBitmap = s_sFirePair.pFrames;
		fire[i].pMask = s_sFirePair.pMasks;
		fire[i].uwWidth = 16;
		fire[i].uwHeight = 14;
		fire[i].uwOffsY = uwOffsY;
		uwOffsY += 14;
	}

	uwOffsY = 0;
	for(UBYTE i = 0; i < MISC_FIRE_FRAME_COUNT; ++i) {
		tree[i].pBitmap = s_sTreePair.pFrames;
		tree[i].pMask = s_sTreePair.pMasks;
		tree[i].uwWidth = 16;
		tree[i].uwHeight = 14;
		tree[i].uwOffsY = uwOffsY;
		uwOffsY += 14;
	}

	shadow.pBitmap = s_sShadowPair.pFrames;
	shadow.pMask = s_sShadowPair.pMasks;
	shadow.uwWidth = 32;
	shadow.uwHeight = 28;
	shadow.uwOffsY = 0;
}

void miscDestroy(void) {
	bitmapPairDestroy(&s_sFirePair);
	bitmapPairDestroy(&s_sTreePair);
	bitmapPairDestroy(&s_sShadowPair);
}

tImage fire[MISC_FIRE_FRAME_COUNT];
tImage tree[MISC_TREE_FRAME_COUNT];
tImage shadow;
