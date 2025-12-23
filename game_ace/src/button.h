#pragma once

#include "gfx.h"

typedef enum tButtonBgKind {
	// 0 and 1 were bigger tile bitmaps with diferent size
	BUTTON_BG_KIND_PRESSED = 0, // was 2
	BUTTON_BG_KIND_UNPRESSED = 1, // was 3
	BUTTON_BG_KIND_COUNT = 2, // was 4
} tButtonBgKind;

typedef enum tButtonKind {
	BUTTON_KIND_SHIELD = 0,
	BUTTON_KIND_MENU = 7,
	BUTTON_KIND_REPAIR = 8,
	BUTTON_KIND_SHED= 9,
	BUTTON_KIND_HUT = 10,
	BUTTON_KIND_MAGE_HUT = 11,
	BUTTON_KIND_WARRIOR_HUT = 12,
	BUTTON_KIND_KNIGHT_HUT = 13,
	BUTTON_KIND_WALL = 14,
	BUTTON_KIND_PEEK = 15,
	BUTTON_KIND_COUNT = 16,
} tButtonKind;

void buttonCreate(void);
void buttonDestroy(void);

extern tImage buttons[BUTTON_KIND_COUNT];
extern tImage Buttons[BUTTON_BG_KIND_COUNT]; // moze byc [8] bo save i smenu to te same przyciski
