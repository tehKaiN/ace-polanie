#include <ace/generic/main.h>
#include <ace/managers/state.h>
#include <ace/managers/key.h>
#include <ace/managers/mouse.h>
#include <ace/managers/viewport/simplebuffer.h>
#include "polanie.h"
#include "menu.h"

static tView *s_pView;
tVPort *g_pVp;
tSimpleBufferManager *g_pVpManager;

tStateManager *g_pStateMachineGame;
tFont *g_pFont;
tTextBitMap *g_pTextBitmap;
tSprite *g_pMouseSprite;

static tBitMap *s_pSpriteBitmap;

void genericCreate(void) {
	keyCreate();
	mouseCreate(MOUSE_PORT_1);
	g_pFont = fontCreateFromPath("data/uni54.fnt");
	g_pTextBitmap = fontCreateTextBitMap(320, g_pFont->uwHeight);

	s_pView = viewCreate(0,
		TAG_VIEW_WINDOW_HEIGHT, 200,
	TAG_END);

	g_pVp = vPortCreate(0,
		TAG_VPORT_BPP, 5,
		TAG_VPORT_VIEW, s_pView,
	TAG_END);

	g_pVpManager = simpleBufferCreate(0,
		TAG_SIMPLEBUFFER_BITMAP_FLAGS, BMF_INTERLEAVED|BMF_CLEAR,
		TAG_SIMPLEBUFFER_IS_DBLBUF, 1,
		TAG_SIMPLEBUFFER_USE_X_SCROLLING, 0,
		TAG_SIMPLEBUFFER_VPORT, g_pVp,
	TAG_END);

	s_pSpriteBitmap = bitmapCreate(16, 5, 2, BMF_INTERLEAVED | BMF_CLEAR);
	blitRect(s_pSpriteBitmap, 0, 1, 3, 3, 1);

	spriteManagerCreate(s_pView, 0, 0);
	g_pMouseSprite = spriteAdd(0, s_pSpriteBitmap);
	spriteProcessChannel(0);

	g_pStateMachineGame = stateManagerCreate();
	statePush(g_pStateMachineGame, &g_sStateMenu);
}

void genericProcess(void) {
	keyProcess();
	mouseProcess();
	stateProcess(g_pStateMachineGame);
}

void genericDestroy(void) {
	viewLoad(0);
	spriteManagerDestroy();
	bitmapDestroy(s_pSpriteBitmap);

	fontDestroy(g_pFont);
	fontDestroyTextBitMap(g_pTextBitmap);
	keyDestroy();
	mouseDestroy();
	viewDestroy(s_pView);

	stateManagerDestroy(g_pStateMachineGame);
}
