#include "gfx.h"
#include <ace/managers/blit.h>
#include "polanie.h"

__attribute__((deprecated))
void Bar13h(
	UWORD uwX1, UWORD uwY1, UWORD uwX2, UWORD uwY2, UBYTE ubColor
) {
	UWORD uwWidth = uwX2 - uwX1;
	UWORD uwHeight = uwY2 - uwY1;
	blitRect(g_pVpManager->pBack, uwX1, uwY1, uwWidth, uwHeight, ubColor);
}

void Rectangle13h(
	UWORD uwX1, UWORD uwY1, UWORD uwX2, UWORD uwY2, UBYTE ubColor
) {
	blitRect(g_pVpManager->pBack, uwX1, uwY1, uwX2 - uwX1, 1, ubColor);
	blitRect(g_pVpManager->pBack, uwX1, uwY2, uwX2 - uwX1, 1, ubColor);

	blitRect(g_pVpManager->pBack, uwX1, uwY1, 1, uwY2 - uwY1, ubColor);
	blitRect(g_pVpManager->pBack, uwX2, uwY1, 1, uwY2 - uwY1, ubColor);
}

void gfxCopyBackToFront(void) {
	blitCopyAligned(g_pVpManager->pBack, 0, 0, g_pVpManager->pFront, 0, 0, 320, 100);
	blitCopyAligned(g_pVpManager->pBack, 0, 100, g_pVpManager->pFront, 0, 100, 320, 100);
}

void gfxDrawImageNoMask(WORD wX, WORD wY, tImage *pImage) {
  if (wX < 0 || wY < 0) {
    logWrite("ERR: gfxDrawImageNoMask() has negative coords");
	}

  UWORD uwWidth = pImage->uwWidth;
  UWORD uwHeight = pImage->uwHeight;
  if (wX + uwWidth < g_gfxClipX1 || wY + uwHeight < g_gfxClipY1 || wX >= g_gfxClipX2 || wY >= g_gfxClipY2) {
    logWrite("ERR: gfxDrawImageNoMask() deep out of clip bounds");
	}

	if (wY + uwHeight > 199) {
    logWrite("ERR: gfxDrawImageNoMask() out of screen bound Y");
	}

	if(!pImage->pBitmap) {
		logWrite("ERR: pSrc is null\n");
	}

	tBitMap *pDest = g_pVpManager->pBack;
	blitCopy(pImage->pBitmap, 0, pImage->uwOffsY, pDest, wX, wY, uwWidth, uwHeight, MINTERM_COOKIE);
}

void gfxDrawImageMaskedClipped(WORD wX, WORD wY, tImage *pImage) {
  if (wX < 0 || wY < 0) {
    return;
	}

  UWORD uwWidth = pImage->uwWidth;
  UWORD uwHeight = pImage->uwHeight;
  if (wX + uwWidth < g_gfxClipX1 || wY + uwHeight < g_gfxClipY1 || wX >= g_gfxClipX2 || wY >= g_gfxClipY2) {
    return;
	}

	UWORD uwSrcX = 0;
	UWORD uwSrcY = pImage->uwOffsY;
	if (uwHeight > g_gfxClipY2 - wY) {
		uwHeight = g_gfxClipY2 - wY;
	}
	if (wY < g_gfxClipY1) {
		uwSrcY += g_gfxClipY1 - wY;
		uwHeight -= g_gfxClipY1 - wY;
		wY = g_gfxClipY1;
	}

	if (uwWidth > g_gfxClipX2 - wX) {
		uwWidth = g_gfxClipX2 - wX;
	}
	if (wX < g_gfxClipX1) {
		uwSrcX = g_gfxClipX1 - wX;
		uwWidth -= uwSrcX;
		wX = g_gfxClipX1;
	}

	tBitMap *pDest = g_pVpManager->pBack;
	if(!pImage->pBitmap) {
		logWrite("ERR: pSrc is null\n");
	}
	if(!pImage->pMask) {
		logWrite("ERR: pMask is null\n");
	}
	if(uwWidth == 0 || uwHeight == 0) {
		logWrite("ERR: zero dimensions\n");
	}
	blitCopyMask(pImage->pBitmap, uwSrcX, uwSrcY, pDest, wX, wY, uwWidth, uwHeight, pImage->pMask->Planes[0]);
}

void gfxSetClippingArea(UWORD uwX1, UWORD uwY1, UWORD uwX2, UWORD uwY2) {
	g_gfxClipX1 = uwX1;
	g_gfxClipY1 = uwY1;
	g_gfxClipX2 = uwX2;
	g_gfxClipY2 = uwY2;
}

UWORD g_gfxClipX1;
UWORD g_gfxClipY1;
UWORD g_gfxClipX2;
UWORD g_gfxClipY2;
