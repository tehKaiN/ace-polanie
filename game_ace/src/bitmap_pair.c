#include "bitmap_pair.h"
#include <ace/managers/memory.h>

void bitmapPairCreate(tBitmapPair *pBmPair, const char *szDataPath) {
	char szFullPath[40];
	sprintf(szFullPath, "data/%s.bm", szDataPath);
	pBmPair->pFrames = bitmapCreateFromPath(szFullPath, 0);
	sprintf(szFullPath, "data/%s_mask.bm", szDataPath);
	pBmPair->pMasks = bitmapCreateFromPath(szFullPath, 0);
}

void bitmapPairDestroy(tBitmapPair *pBmPair) {
	bitmapDestroy(pBmPair->pFrames);
	bitmapDestroy(pBmPair->pMasks);
}
