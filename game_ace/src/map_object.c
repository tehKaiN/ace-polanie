#include "map_object.h"

const tMapObject g_sMapObjTree = {
	.eKind = MAP_OBJECT_KIND_TREE,
	.eTeam = MAP_OBJECT_TEAM_TREE,
};

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
