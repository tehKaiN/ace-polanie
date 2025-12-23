#pragma once

#include <ace/managers/state.h>

extern tState g_sStateBattle;

void battleStartNewLevel(UBYTE ubLevelIndex);

void battleLoadFromSlot(UBYTE ubSlotIndex);
