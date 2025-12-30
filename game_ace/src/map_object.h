#pragma once

#include <ace/types.h>

#define MAP_OBJECT_TREES_MAX 2000

typedef enum tMapObjectKind: UBYTE {
	MAP_OBJECT_KIND_UNKNOWN,
	MAP_OBJECT_KIND_MOVER,
	MAP_OBJECT_KIND_BUILDING,
	MAP_OBJECT_KIND_TREE,
} tMapObjectKind;

typedef enum tMapObjectTeam: UBYTE {
	MAP_OBJECT_TEAM_NONE,
	MAP_OBJECT_TEAM_PLAYER,
	MAP_OBJECT_TEAM_CPU,
	MAP_OBJECT_TEAM_TREE,
} tMapObjectTeam;

typedef struct tMapObject {
	tMapObjectKind eKind;
	tMapObjectTeam eTeam;
	UBYTE ubX;
	UBYTE ubY;
} tMapObject;

tMapObject *mapObjectInitTree(UWORD uwIndex, UBYTE ubTileX, UBYTE ubTileY);

extern tMapObject g_sMapObjTrees[MAP_OBJECT_TREES_MAX]; // nr 768+
extern const tMapObject g_sMapObjObstacle; // nr 10
extern const tMapObject g_sMapObjWater; // nr 1
extern const tMapObject g_sMapObjBridge; // nr 2
