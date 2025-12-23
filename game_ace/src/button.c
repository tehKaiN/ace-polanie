#include "button.h"

static tBitMap *s_pButtonsBitmap;
static tBitMap *s_pButtonsBgBitmap;

void buttonCreate(void) {
	s_pButtonsBitmap = bitmapCreateFromPath("data/button.bm", 0);
	s_pButtonsBgBitmap = bitmapCreateFromPath("data/button_bg.bm", 0);

	for(UBYTE i = 0; i < BUTTON_KIND_COUNT; ++i) {
		buttons[i].pBitmap = s_pButtonsBitmap;
		buttons[i].pMask = 0;
		buttons[i].uwWidth = 16;
		buttons[i].uwHeight = 14;
		buttons[i].uwOffsY = 14 * i;
	}

	for(UBYTE i = 0; i < BUTTON_KIND_COUNT; ++i) {
		Buttons[i].pBitmap = s_pButtonsBgBitmap;
		Buttons[i].pMask = 0;
		Buttons[i].uwWidth = 32;
		Buttons[i].uwHeight = 16;
		Buttons[i].uwOffsY = 16 * i;
	}
}

void buttonDestroy(void) {
	bitmapDestroy(s_pButtonsBitmap);
	bitmapDestroy(s_pButtonsBgBitmap);
}

tImage buttons[BUTTON_KIND_COUNT];
tImage Buttons[BUTTON_BG_KIND_COUNT]; // moze byc [8] bo save i smenu to te same przyciski
