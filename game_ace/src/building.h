#pragma once

#include "mover.h"
#include "map_object.h"

#define BUILDING_MOVERS_MAX 6

typedef enum tBuildingKind {
	BUILDING_KIND_UNK = 1,
	BUILDING_KIND_SHED = 2,
	BUILDING_KIND_HUT = 3,
	BUILDING_KIND_MAGE_HUT = 4,
	BUILDING_KIND_WARRIOR_HUT = 5,
	BUILDING_KIND_KNIGHT_HUT = 6,
	BUILDING_KIND_COUNT,
} tBuildingKind;

typedef struct tBuilding {
  tMapObject sMapObject;
  int exist;
  int faza;
  tBuildingKind type;
  int hp;
  int armour;
  int maxhp;
  int food, maxfood;
  tMover m[BUILDING_MOVERS_MAX];
} tBuilding;

void buildingPrepare(tBuilding *pBuilding, int, int, int);
void buildingShowS(tBuilding *pBuilding, int, int, int);
void buildingRun(tBuilding *pBuilding);
int buildingWynik(tBuilding *pBuilding, int);
int buildingNewMan(tBuilding *pBuilding, int);
int buildingMilk(tBuilding *pBuilding);
void buildingRebuild(tBuilding *pBuilding);
void buildingInit(tBuilding *pBuilding, int x0, int y0, tBuildingKind eKind, tMapObjectTeam eTeam, UBYTE isFullyBuilt);
