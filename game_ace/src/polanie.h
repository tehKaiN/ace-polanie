#pragma once

#include <ace/managers/viewport/simplebuffer.h>
#include <ace/managers/state.h>
#include <ace/managers/sprite.h>
#include <ace/utils/font.h>

extern tVPort *g_pVp;
extern tSimpleBufferManager *g_pVpManager;

extern tStateManager *g_pStateMachineGame;
extern tSprite *g_pMouseSprite;
extern tFont *g_pFont;
extern tTextBitMap *g_pTextBitmap;
