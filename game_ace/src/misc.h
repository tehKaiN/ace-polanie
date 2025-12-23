#pragma once

#include "gfx.h"

#define MISC_FIRE_FRAME_COUNT 14
#define MISC_TREE_FRAME_COUNT 14

void miscCreate(void);

void miscDestroy(void);

extern tImage fire[MISC_FIRE_FRAME_COUNT];
extern tImage tree[MISC_TREE_FRAME_COUNT];
extern tImage shadow;
