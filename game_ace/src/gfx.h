#pragma once

#include <ace/utils/bitmap.h>

// FIXME: `how` controls whether mask is used or not, but clipping is enabled at all times
#define PutImageChange13h(x, y, p, how, c1, c2) gfxDrawImageMaskedClipped(x, y, p)

#define Color1 16

#define LightRed 16
#define Red 16
#define DarkRed 16

#define LightYellow 16
#define Yellow 16
#define DarkYellow 16

#define LightGreen 16
#define Green 16
#define DarkGreen 16

#define LightBlue 16
#define Blue 16
#define DarkBlue 16

#define LightGray 16
#define Gray 16
#define DarkGray 16

#define LightBrown 16
#define Brown 16
#define DarkBrown 16

#define Black 0
#define White 16
#define FontColor 16
#define MsgFontColor 16

typedef struct tImage {
	tBitMap *pBitmap;
	tBitMap *pMask;
	UWORD uwOffsY;
	UWORD uwWidth;
	UWORD uwHeight;
} tImage;

extern UWORD g_gfxClipX1;
extern UWORD g_gfxClipY1;
extern UWORD g_gfxClipX2;
extern UWORD g_gfxClipY2;

void Bar13h(UWORD uwX1, UWORD uwY1, UWORD uwX2, UWORD uwY2, UBYTE ubColor);

void Rectangle13h(UWORD uwX1, UWORD uwY1, UWORD uwX2, UWORD uwY2, UBYTE ubColor);

void gfxCopyBackToFront(void);

void gfxDrawImageNoMask(WORD wX, WORD wY, tImage *pImage);

void gfxDrawImageMaskedClipped(WORD wX, WORD wY, tImage *pImage);

void gfxSetClippingArea(UWORD uwX1, UWORD uwY1, UWORD uwX2, UWORD uwY2);

// static inline void ShowPicture(UBYTE ubImageIndex, UWORD uwDestY);

// void PutImage13h(int x, int y, char *picture, int how) {
// 	if(how == 0) {
// 		gfxDrawImageNoMask();
// 	}
// 	else {
// 		gfxDrawImageMaskClipped();
// 	}
// }
