#include "picture.h"
#include "bitmap_pair.h"

static tBitmapPair s_sPairDryEarth;
static tBitmapPair s_sPairPicture;
static tBitmapPair s_sPairTree;

void pictureCreate(void) {
	bitmapPairCreate(&s_sPairDryEarth, "picture/dry_earth");
	bitmapPairCreate(&s_sPairPicture, "picture/picture");
	bitmapPairCreate(&s_sPairTree, "picture/tree");

	UWORD uwOffsY = 0;
	for(tPictureKind ePic = 0; ePic < PICTURE_KIND_COUNT; ++ePic) {
		picture[ePic].pBitmap = s_sPairPicture.pFrames;
		picture[ePic].pMask = s_sPairPicture.pMasks;
		picture[ePic].uwWidth = 16;
		picture[ePic].uwHeight = 14;
		picture[ePic].uwOffsY = uwOffsY;
		uwOffsY += 14;
	}

	uwOffsY = 0;
	for(tPictureKind ePic = PICTURE_KIND_DRY_EARTH_0; ePic <= PICTURE_KIND_DRY_EARTH_2; ++ePic) {
		picture[ePic].pBitmap = s_sPairDryEarth.pFrames;
		picture[ePic].pMask = s_sPairDryEarth.pMasks;
		picture[ePic].uwWidth = 22;
		picture[ePic].uwHeight = 18;
		picture[ePic].uwOffsY = uwOffsY;
		uwOffsY += 18;
	}

	uwOffsY = 0;
	for(tPictureKind ePic = PICTURE_KIND_TREE_0_BOTTOM; ePic < PICTURE_KIND_TREE_6_TOP; ++ePic) {
		picture[ePic].pBitmap = s_sPairTree.pFrames;
		picture[ePic].pMask = s_sPairTree.pMasks;
		picture[ePic].uwWidth = 32;
		picture[ePic].uwHeight = 14;
		picture[ePic].uwOffsY = uwOffsY;
		uwOffsY += 14;
	}
}

void pictureDestroy(void) {
	bitmapPairDestroy(&s_sPairDryEarth);
	bitmapPairDestroy(&s_sPairPicture);
	bitmapPairDestroy(&s_sPairTree);
}

tImage picture[PICTURE_KIND_COUNT];
