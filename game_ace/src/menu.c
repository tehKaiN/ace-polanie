#include "menu.h"
#include <ace/utils/extview.h>
#include <ace/managers/system.h>
#include <ace/managers/mouse.h>
#include <ace/managers/game.h>
#include <ace/managers/key.h>
#include <ace/managers/blit.h>
#include <ace/utils/disk_file.h>
#include <ace/utils/string.h>
#include "polanie.h"
#include "battle.h"
#include "track.h"
#include "gfx.h"

#define MENU_SAVE_SLOT_COUNT 4

static tStateManager *s_pStateMachineMenu;

static tState s_sStateMain;
static tState s_sStateLoad;
static tState s_sStateCampaign;
// static tState s_sStateSave;
// static tState s_sStateOptions;

static void menuDrawButton(tUwRect sRect, const char *szText) {
	blitRect(g_pVpManager->pBack, sRect.uwX, sRect.uwY, sRect.uwWidth, sRect.uwHeight, 1);
	if(!stringIsEmpty(szText)) {
		fontDrawStr(
			g_pFont, g_pVpManager->pBack,
			sRect.uwX + sRect.uwWidth / 2, sRect.uwY + sRect.uwHeight / 2, szText, 16,
			FONT_CENTER | FONT_COOKIE | FONT_SHADOW, g_pTextBitmap
		);
	}
}

static void menuGsCreate(void) {
  // PlayTrack(TRACK_MENU);

	g_pVp->pPalette[0] = 0x000;
	g_pVp->pPalette[1] = 0xF00;
	g_pVp->pPalette[16] = 0xFFF;
	g_pVp->pPalette[17] = 0xFFF;
	g_pVp->pPalette[18] = 0xFFF;
	g_pVp->pPalette[19] = 0xFFF;

	s_pStateMachineMenu = stateManagerCreate();
	statePush(s_pStateMachineMenu, &s_sStateMain);

	viewLoad(g_pVp->pView);
	systemSetDmaBit(DMAB_SPRITE, 1);
	systemUnuse();
}

static void menuGsLoop(void) {
	stateProcess(s_pStateMachineMenu);

	UWORD uwX = mouseGetX(MOUSE_PORT_1);
	UWORD uwY = mouseGetY(MOUSE_PORT_1);
	g_pMouseSprite->wX = (WORD)uwX - 1;
	g_pMouseSprite->wY = (WORD)uwY - 1;
	spriteRequestMetadataUpdate(g_pMouseSprite);
	spriteProcess(g_pMouseSprite);

	vPortProcessManagers(g_pVp);
	copProcessBlocks();
	systemIdleBegin();
	vPortWaitForEnd(g_pVp);
	systemIdleEnd();
}

static void menuGsDestroy(void) {
	systemUse();
	viewLoad(0);
	systemSetDmaBit(DMAB_SPRITE, 0);

	stateManagerDestroy(s_pStateMachineMenu);
}

#pragma region Main menu

static const tUwRect s_sRectMainNewGame = {
	.uwX = 20, .uwY = 45,
	.uwWidth = 130 - 20, .uwHeight = 70 - 45
};
static const tUwRect s_sRectMainLoadGame = {
	.uwX = 20, .uwY = 90, .uwWidth = 130 - 20, .uwHeight = 115 - 90
};
static const tUwRect s_sRectMainExit = {
	.uwX = 20, .uwY = 130,
	.uwWidth = 130 - 20, .uwHeight = 151 - 130
};

static void menuMainCreate(void) {
	blitRect(g_pVpManager->pBack, 0, 0, 320, 200, 0);
	menuDrawButton(s_sRectMainNewGame, "Nowa gra");
	menuDrawButton(s_sRectMainLoadGame, "Wczytaj gre");
	menuDrawButton(s_sRectMainExit, "Koniec");

	gfxCopyBackToFront();
}

static void menuMainLoop(void) {
	UWORD uwX = mouseGetX(MOUSE_PORT_1);
	UWORD uwY = mouseGetY(MOUSE_PORT_1);
	UBYTE isLmbPressed = mouseUse(MOUSE_PORT_1, MOUSE_LMB);

  if (
		keyUse(KEY_K) || keyUse(KEY_Q) ||
		(isLmbPressed && inRect(uwX, uwY, s_sRectMainExit))
	) {
		gameExit();
  }
	else if (
		keyUse(KEY_N) ||
		(isLmbPressed && inRect(uwX, uwY, s_sRectMainNewGame))
	) {
		stateChange(s_pStateMachineMenu, &s_sStateCampaign);
    // show = 1;
  }
	else if (
		keyUse(KEY_W) || keyUse(KEY_L) ||
		(isLmbPressed && inRect(uwX, uwY, s_sRectMainLoadGame))
	) {
		stateChange(s_pStateMachineMenu, &s_sStateLoad);
    return;
  }
}
#pragma endregion

#pragma region Load menu

static const tUwRect s_pSaveButtonRects[] = {
	{.uwX = 100, .uwY = 30, .uwWidth = 220 - 100, .uwHeight = 47 - 30},
	{.uwX = 100, .uwY = 57, .uwWidth = 220 - 100, .uwHeight = 74 - 57},
	{.uwX = 100, .uwY = 87, .uwWidth = 220 - 100, .uwHeight = 104 - 87},
	{.uwX = 100, .uwY = 114, .uwWidth = 220 - 100, .uwHeight = 131 - 114},
	{.uwX = 100, .uwY = 142, .uwWidth = 220 - 100, .uwHeight = 159 - 142},
};

static void menuLoadCreate(void) {
	// DownPalette(2);
  // LoadExtendedPalette(1);
	blitRect(g_pVpManager->pBack, 0, 0, 320, 200, 0);
  // ShowPicture(1, 0);
  // ShowPicture(16, 100);
  // PressButton(1, 1);
  // PressButton(2, 1);
  // PressButton(3, 1);
  // PressButton(4, 1);
  // PressButton(5, 1);

	systemUse();
	char szSaveName[12]; // at first save file name, then display name
  for (UBYTE i = 0; i < MENU_SAVE_SLOT_COUNT; i++) {
		sprintf(szSaveName, "save.%03hhu", i);
    if (diskFileExists(szSaveName)) {
			tFile *pSaveFile = diskFileOpen(szSaveName, DISK_FILE_MODE_READ, 1);
			fileRead(pSaveFile, szSaveName, sizeof(szSaveName));
      fileClose(pSaveFile);
    }
		else {
			stringCopy("Pusty", szSaveName);
		}

		menuDrawButton(s_pSaveButtonRects[i], szSaveName);
  }
	systemUnuse();

	menuDrawButton(s_pSaveButtonRects[4], "Koniec");
	gfxCopyBackToFront();
}

static void menuLoadLoop(void) {
	UWORD uwX = mouseGetX(MOUSE_PORT_1);
	UWORD uwY = mouseGetY(MOUSE_PORT_1);
	UBYTE isLmbPressed = mouseUse(MOUSE_PORT_1, MOUSE_LMB);

	for(UBYTE i = 0; i < MENU_SAVE_SLOT_COUNT; ++i) {
		if (keyUse(KEY_1 + i) + (isLmbPressed && inRect(uwX, uwY, s_pSaveButtonRects[i]))) {
			// PressButton(1, 0);
			// delay(300);
			battleLoadFromSlot(i);
			// endGame = 0;
			// show = 1;
			// PlayTrack(TRACK_MENU);
			return;
		}
	}
	if (keyUse(KEY_C) || (isLmbPressed && inRect(uwX, uwY, s_pSaveButtonRects[4]))) {
		// cancel
		// PressButton(5, 0); // unpressed
		// delay(300);
		// PressButton(5, 1); // pressed
		stateChange(s_pStateMachineMenu, &s_sStateMain);
	}
}

#pragma endregion

#pragma region Campaign menu

#define MENU_CAMPAIGN_COUNT 6

static tUwRect s_sCampaignRects[MENU_CAMPAIGN_COUNT] = {
	{.uwX = 44, .uwY = 10, .uwWidth = 210 - 44, .uwHeight = 32 - 10},
	{.uwX = 44, .uwY = 40, .uwWidth = 210 - 44, .uwHeight = 62 - 40},
	{.uwX = 44, .uwY = 70, .uwWidth = 210 - 44, .uwHeight = 92 - 70},
	{.uwX = 44, .uwY = 100, .uwWidth = 210 - 44, .uwHeight = 122 - 100},
	{.uwX = 44, .uwY = 130, .uwWidth = 210 - 44, .uwHeight = 152 - 130},
	{.uwX = 44, .uwY = 160, .uwWidth = 210 - 44, .uwHeight = 182 - 160},
};

tUwRect s_sCampaignBackRect = {.uwX = 235, .uwY = 160, .uwWidth = 304 - 235, .uwHeight = 182 - 160};

// base coords used for iterating for extra buttons
tUwRect s_sCampaignFirstFaceRect = {.uwX = 250, .uwY = 24, .uwWidth = 20, .uwHeight = 30};

static void menuCampaignCreate(void) {
  // DownPalette(1);
	blitRect(g_pVpManager->pBack, 0, 0, 320, 200, 0);
  // ShowPicture(10, 0);
  // ShowPicture(24, 100);
  // LoadExtendedPalette(10);
  // PokazOczy();
  // RisePalette(1);

	static const char *pTitles[MENU_CAMPAIGN_COUNT] = {
		"Powrot Mirka",
		"Przyjaciele",
		"Porwanie",
		"Wojna Magow",
		"Wschodnia pozoga",
		"Poludnie w ogniu",
	};

	for(UBYTE i = 0; i < MENU_CAMPAIGN_COUNT; ++i) {
		menuDrawButton(s_sCampaignRects[i], pTitles[i]);
	}

	menuDrawButton(s_sCampaignBackRect, "Powrot");
	for(UBYTE i = 0; i < 3; ++i) {
		tUwRect sFaceRect = s_sCampaignFirstFaceRect;
		sFaceRect.uwY += i * 43;
		menuDrawButton(sFaceRect, "");
	}

	gfxCopyBackToFront();
}

static void menuCampaignLoop(void) {
	UBYTE isLmbPressed = mouseUse(MOUSE_PORT_1, MOUSE_LMB);
	if(!isLmbPressed) {
		return;
	}

	UWORD uwX = mouseGetX(MOUSE_PORT_1);
	UWORD uwY = mouseGetY(MOUSE_PORT_1);

	static const UBYTE s_ubStartLevels[] = {15, 26, 31, 36, 42, 47};

	for(UBYTE i = 0; i < MENU_CAMPAIGN_COUNT; ++i) {
		if (inRect(uwX, uwY, s_sCampaignRects[i])) {
			if(i == 0) {
				// StopPlaying();
				// // play("data\\s002.dat");
				// char ss[50];
				// sprintf(ss, "%sdata\\i003.dat", drive);
				// if (IsFile(ss))
				// 	SND.PlayWav(ss);
				// sprintf(ss, "%sdata\\s003.dat", drive);
				// if (IsFile(ss))
				// 	play(ss); // odtwarza flica Intro Daniel
				// SND.EndPlayWav();

				// PlayTrack(TRACK_TXT);
				// ShowText(1, 3); // show start
				// for (i = 0; i < 25; i++) {
				// 	prowintion[i] = prowintionInit[i];
				// }
			}
			else {
				// Other campaigns seemed to have played following, but it was commented out:
				// s003.dat, s004.dat, s005.dat, s006.dat, s007.dat,
			}

			// UBYTE ubCampaignIndex = i + 1;
			UBYTE ubLevelIndex = s_ubStartLevels[i];
			// TODO: click on head to select difficulty
			battleStartNewLevel(ubLevelIndex, DIFFICULTY_EASY); // Battle(1);
			// endGame = 0;
			// PlayTrack(TRACK_MENU);
			return;
		}
	}

	if (inRect(uwX, uwY, s_sCampaignBackRect)) {
		stateChange(s_pStateMachineMenu, &s_sStateMain);
		return;
	}

	for (UBYTE i = 0; i < 3; i++) {
		tUwRect sFaceRect = s_sCampaignFirstFaceRect;
		sFaceRect.uwY += i * 43;

		if (inRect(uwX, uwY, sFaceRect)) {
			// diff = i;
			// PokazOczy();
		}
	}
}

#pragma endregion

static tState s_sStateMain = {.cbCreate = menuMainCreate, .cbLoop = menuMainLoop};
static tState s_sStateLoad = {.cbCreate = menuLoadCreate, .cbLoop = menuLoadLoop};
static tState s_sStateCampaign = {.cbCreate = menuCampaignCreate, .cbLoop = menuCampaignLoop};
// static tState s_sStateSave = {.cbCreate = 0, .cbLoop = 0};
// static tState s_sStateOptions = {.cbCreate = 0, .cbLoop = 0};

tState g_sStateMenu = {
	.cbCreate = menuGsCreate,
	.cbLoop = menuGsLoop,
	.cbDestroy = menuGsDestroy
};
