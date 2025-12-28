#pragma once

#include "gfx.h"

#define MISC_FIRE_FRAME_COUNT 14
#define MISC_TREE_FRAME_COUNT 14
#define MISC_DEAD_FRAME_COUNT 4
#define MISC_HIT_FRAME_COUNT 2

void miscCreate(void);

void miscDestroy(void);

extern tImage dead[MISC_DEAD_FRAME_COUNT];
extern tImage Hit[MISC_HIT_FRAME_COUNT];
extern tImage fire[MISC_FIRE_FRAME_COUNT];
extern tImage tree[MISC_TREE_FRAME_COUNT];
extern tImage shadow;
