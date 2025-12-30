#include "map_object.h"
#include <ace/managers/log.h>

tMapObject *mapObjectInitTree(UWORD uwIndex, UBYTE ubTileX, UBYTE ubTileY) {
	if(uwIndex > MAP_OBJECT_TREES_MAX) {
		logWrite("ERR: Too many trees!\n");
	}

	tMapObject *pTree = &g_sMapObjTrees[uwIndex];
	pTree->eKind = MAP_OBJECT_KIND_TREE;
	pTree->eTeam = MAP_OBJECT_TEAM_TREE;
	pTree->ubX = ubTileX;
	pTree->ubY = ubTileY;

	return pTree;
}

tMapObject g_sMapObjTrees[MAP_OBJECT_TREES_MAX];

const tMapObject g_sMapObjObstacle = {
	.eKind = MAP_OBJECT_KIND_UNKNOWN,
	.eTeam = MAP_OBJECT_TEAM_NONE,
};

const tMapObject g_sMapObjWater = {
	.eKind = MAP_OBJECT_KIND_UNKNOWN,
	.eTeam = MAP_OBJECT_TEAM_NONE,
};

const tMapObject g_sMapObjBridge = {
	.eKind = MAP_OBJECT_KIND_UNKNOWN,
	.eTeam = MAP_OBJECT_TEAM_NONE,
};
