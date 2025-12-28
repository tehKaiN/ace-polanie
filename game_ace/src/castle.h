#pragma once

#include "command.h"
#include "building.h"

#define CASTLE_MOVERS_MAX 40
#define CASTLE_BUILIDNGS_MAX 20

typedef struct tCastle {
  int IFF;
  int faza;
  int milk, maxmilk;
  tMover m[CASTLE_MOVERS_MAX];
  tBuilding b[CASTLE_BUILIDNGS_MAX];
  tCommand command;
} tCastle;

void castleInit(tCastle *pCastle, int iff, int mlk);

void castleGetCmd(tCastle *pCastle, tCommand *pCmd);

void castleSetCmd(tCastle *pCastle, tCommand *pCmd);

void castlePrepare(tCastle *pCastle, int X, int Y, int typ);

void castleShowS(tCastle *pCastle, int Xs, int Ys, int what);

void castleRun(tCastle *pCastle);

void castleDisableUnits(tCastle *pCastle);

void castleFreeUnits(tCastle *pCastle);

extern tCastle castle[2];
