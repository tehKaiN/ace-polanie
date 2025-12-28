#pragma once

#include <ace/managers/state.h>

#define KUSZNIK_LEV 32
#define PASTUCH_LEV 26
#define MAG_LEV 40

typedef enum tDifficulty {
	DIFFICULTY_EASY,
	DIFFICULTY_MEDIUM,
	DIFFICULTY_HARD,
} tDifficulty;

extern tState g_sStateBattle;

void battleStartNewLevel(UWORD uwLevelIndex, tDifficulty eDifficulty);

void battleLoadFromSlot(UBYTE ubSlotIndex);

extern UWORD g_uwLevel; // used for unit unlocks
extern tDifficulty g_eDifficulty;
