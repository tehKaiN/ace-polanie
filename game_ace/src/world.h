#pragma once

#include <ace/types.h>

#define WORLD_SIZE_X 66
#define WORLD_SIZE_Y 66
#define WORLD_WINDOW_SIZE_X 16
#define WORLD_WINDOW_SIZE_Y 13

void worldShowPlace(UWORD uwX, UWORD uwY);

void worldShowTrees(UWORD uwX, UWORD uwY);

void worldPlaceRoad(UWORD x, UWORD y, ULONG typ);

void worldPlaceWater(UWORD x, UWORD y, ULONG t);

void worldDump(UBYTE ubStartX, UBYTE ubStartY, UBYTE ubSizeX, UBYTE ubSizeY);

void worldRevealAll(void);

extern int drzewa;
extern int drzewa0;
extern UWORD place[WORLD_SIZE_X][WORLD_SIZE_Y];
extern UBYTE placeN[WORLD_SIZE_X][WORLD_SIZE_Y];
extern UWORD attack[WORLD_SIZE_X][WORLD_SIZE_Y];
extern UWORD placeG[WORLD_SIZE_X][WORLD_SIZE_Y];
extern UBYTE xleczenie;
extern UBYTE yleczenie;
extern UWORD xpastw;
extern UWORD ypastw;
