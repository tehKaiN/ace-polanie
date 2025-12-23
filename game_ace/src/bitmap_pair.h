#pragma once

#include <ace/utils/bitmap.h>

typedef struct tBitmapPair {
	tBitMap *pFrames;
	tBitMap *pMasks;
} tBitmapPair;

void bitmapPairCreate(tBitmapPair *pBmPair, const char *szDataPath);

void bitmapPairDestroy(tBitmapPair *pBmPair);
