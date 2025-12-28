#include "castle.h"
#include "world.h"

void castleInit(tCastle *pCastle, int iff, int mlk) {
  pCastle->IFF = iff;
  pCastle->milk = mlk;
  pCastle->maxmilk = mlk;
  for (UBYTE ubMover = 0; ubMover < CASTLE_MOVERS_MAX; ubMover++) {
    moverDisable(&pCastle->m[ubMover]);
	}
  for (UBYTE ubBuilding = 0; ubBuilding < CASTLE_BUILIDNGS_MAX; ubBuilding++) {
    pCastle->b[ubBuilding].exist = 0;
    for (UBYTE ubMover = 0; ubMover < BUILDING_MOVERS_MAX; ubMover++) {
      moverDisable(&pCastle->b[ubBuilding].m[ubMover]);
		}
  }
}

void castleShowS(tCastle *pCastle, int Xs, int Ys, int what) {
  //////////// pokaz budynki i ich rycerzy
  for (UBYTE i = 0; i < CASTLE_BUILIDNGS_MAX; i++) {
    buildingShowS(&pCastle->b[i], Xs, Ys, what);
	}

  if (what == 1) //////////// pokaz obiekty  martwe
  {
    for (UBYTE i = 1; i < CASTLE_MOVERS_MAX; i++) {
      if (pCastle->m[i].exist == 2)
        moverShowS(&pCastle->m[i]);
    }
  }
  if (what == 2) //////////// pokaz obiekty  zywe
  {
    for (UBYTE i = 1; i < CASTLE_MOVERS_MAX; i++) {
      if (pCastle->m[i].exist == 1)
        moverShowS(&pCastle->m[i]);
    }
  }

  if (what == 3) /////////// pokaz pociski
  {
    for (UBYTE i = 1; i < CASTLE_MOVERS_MAX; i++)
      missileShow(&pCastle->m[i].missile, Xs, Ys);
  }
}

void castlePrepare(tCastle *pCastle, int X, int Y, int typ) {
  // przygotuj budynki i ich rycerzy
  for (UBYTE i = 0; i < CASTLE_BUILIDNGS_MAX; i++) {
    buildingPrepare(&pCastle->b[i], X, Y, typ);
  }

  // przygotuj obiekty
  for (UBYTE i = 1; i < CASTLE_MOVERS_MAX; i++) {
    moverPrepare(&pCastle->m[i], X, Y, typ);
  }
}

void castleGetCmd(tCastle *pCastle, tCommand *pCmd) {
  pCmd->nrm = pCastle->command.nrm;
  pCmd->nrb = pCastle->command.nrb;
  pCmd->command = pCastle->command.command;
  pCmd->x = pCastle->command.x;
  pCmd->y = pCastle->command.y;
  pCmd->co = pCastle->command.co;
}

void castleSetCmd(tCastle *pCastle, tCommand *pCmd) {
  pCastle->command.nrb = pCmd->nrb;
  pCastle->command.nrm = pCmd->nrm;
  pCastle->command.command = pCmd->command;
  pCastle->command.x = pCmd->x;
  pCastle->command.y = pCmd->y;
  pCastle->command.co = pCmd->co;
}

void castleRun(tCastle *pCastle) {
  int i;
  if (pCastle->command.co == 2) // komendy ogolne
  {
    if (pCastle->command.command == 2 && pCastle->milk >= 45 &&
        !place[pCastle->command.x][pCastle->command.y]) // droga
    {
      placeG[pCastle->command.x][pCastle->command.y] = 35;
      worldPlaceRoad(pCastle->command.x, pCastle->command.y, 35);
      worldPlaceRoad(pCastle->command.x - 1, pCastle->command.y, 35);
      worldPlaceRoad(pCastle->command.x + 1, pCastle->command.y, 35);
      worldPlaceRoad(pCastle->command.x, pCastle->command.y - 1, 35);
      worldPlaceRoad(pCastle->command.x, pCastle->command.y + 1, 35);
      pCastle->milk -= 45;
      // if (Msg.dzwiek < 20) {
      //   Msg.dzwiek = 20;
      //   Msg.X = pCastle->command.x;
      //   Msg.Y = pCastle->command.y;
      // }
    }
    if (pCastle->command.command == 2 && pCastle->milk >= 45 &&
        place[pCastle->command.x][pCastle->command.y] == 1) // most
    {
      place[pCastle->command.x][pCastle->command.y] = 2;
      pCastle->milk -= 80;
      // if (Msg.dzwiek < 20) {
      //   Msg.dzwiek = 20;
      //   Msg.X = pCastle->command.x;
      //   Msg.Y = pCastle->command.y;
      // }
    }
    if (pCastle->command.command == 3 && pCastle->milk >= 50) // palisada
    {
      placeG[pCastle->command.x][pCastle->command.y] = 277;
      pCastle->milk -= 60;
      worldPlaceRoad(pCastle->command.x - 1, pCastle->command.y, 35);
      worldPlaceRoad(pCastle->command.x + 1, pCastle->command.y, 35);
      worldPlaceRoad(pCastle->command.x, pCastle->command.y - 1, 35);
      worldPlaceRoad(pCastle->command.x, pCastle->command.y + 1, 35);
      // if (Msg.dzwiek < 20) {
      //   Msg.dzwiek = 20;
      //   Msg.X = pCastle->command.x;
      //   Msg.Y = pCastle->command.y;
      // }
    }
    if (pCastle->command.command > 3) // budowa budynku
    {
      int w = 20;
      for (i = 0; i < 20; i++)
        if (!pCastle->b[i].exist)
          w = i;
      i = pCastle->command.command - 1;
      if (i > 5)
        i = 5;
      if (pCastle->milk < i * 200 + 50)
        return;
      if (w < 20) {
        buildingInit(&pCastle->b[w], pCastle->command.x, pCastle->command.y, pCastle->command.command - 2, pCastle->IFF, w);
        pCastle->milk -= i * 200 + 50;
        // if (Msg.dzwiek < 20) {
        //   Msg.dzwiek = 20;
        //   Msg.X = pCastle->command.x;
        //   Msg.Y = pCastle->command.y;
        // }
        pCastle->command.y -= 2;
        pCastle->command.x -= 2;
        for (int ii = -1; ii <= 3; ii++)
          for (int jj = -1; jj <= 3; jj++)
            worldPlaceRoad(pCastle->command.x + ii, pCastle->command.y + jj, 35);
      }
    }
  }
  if (pCastle->command.co == 0) // komendy dla budynkow (odbudowa)
  {
    if (pCastle->command.command == 1 && pCastle->milk >= 250) {
      if (pCastle->b[pCastle->command.nrb].hp < pCastle->b[pCastle->command.nrb].maxhp)
        pCastle->milk -= 250;
      buildingRebuild(&pCastle->b[pCastle->command.nrb]);
    };
    if (pCastle->command.command > 1) // budowa postaci
    {
      i = pCastle->command.command;
      if (pCastle->milk >= i * 200 + 50) {
        pCastle->milk -= buildingNewMan(&pCastle->b[pCastle->command.nrb], i);
      }
    }
  }
  if (pCastle->command.co == 1) // komendy dla modulow
  {
    tMover *mm;
    if (pCastle->command.nrb < CASTLE_BUILIDNGS_MAX)
      mm = &pCastle->b[pCastle->command.nrb].m[pCastle->command.nrm];
    else
      mm = &pCastle->m[pCastle->command.nrm];

    moverSetCommand(mm, pCastle->command.command);
    if (pCastle->command.command == 1 || pCastle->command.command == 7 || pCastle->command.command == 8)
      moverSetEnd(mm, pCastle->command.x, pCastle->command.y);
    if (pCastle->command.command == 2)
      moverSetTarget(mm, place[pCastle->command.x][pCastle->command.y]);
  }

	tMover *mm;
  if (pCastle->command.co == 3) // komendy dla modulow wszystkich
  {
    int post, bud;
    for (post = 1; post < CASTLE_MOVERS_MAX; post++) {
      mm = &pCastle->m[post];
      if (mm->wybrany) {
        moverSetCommand(mm, pCastle->command.command);
        if (pCastle->command.command == 8 || pCastle->command.command == 7 ||
            pCastle->command.command == 1)
          moverSetEnd(mm, pCastle->command.x, pCastle->command.y);
        if (pCastle->command.command == 2)
          moverSetTarget(mm, place[pCastle->command.x][pCastle->command.y]);
      }
    }
    for (bud = 0; bud < CASTLE_BUILIDNGS_MAX; bud++) {
      for (post = 0; post < BUILDING_MOVERS_MAX; post++) {
        mm = &pCastle->b[bud].m[post];
        if (mm->wybrany) {
          moverSetCommand(mm, pCastle->command.command);
          if (pCastle->command.command == 8 || pCastle->command.command == 7 ||
              pCastle->command.command == 1)
            moverSetEnd(mm, pCastle->command.x, pCastle->command.y);
          if (pCastle->command.command == 2)
            moverSetTarget(mm, place[pCastle->command.x][pCastle->command.y]);
        }
      }
		}
  }

  // disable command
  pCastle->command.co = 5;
  pCastle->command.command = 0;
  // zbierz mleczko
  if (pCastle->milk < pCastle->maxmilk) {
    for (i = 0; i < CASTLE_BUILIDNGS_MAX; i++) {
      pCastle->milk += buildingMilk(&pCastle->b[i]);
		}
    for (i = 1; i < CASTLE_MOVERS_MAX; i++) {
      if (!pCastle->m[i].type) {
        pCastle->milk += moverMilk(&pCastle->m[i]);
			}
		}
  }
	else {
    pCastle->milk = pCastle->maxmilk;
  }

  // run units
	pCastle->faza = !pCastle->faza;
  if (pCastle->faza) {
		// zolnierzy
    for (i = 1; i < CASTLE_MOVERS_MAX / 2; i++)
      moverRun(&pCastle->m[i]);
    for (i = 0; i < 10; i++)
      buildingRun(&pCastle->b[i]);
  }
	else { //  lub budynki
    for (i = CASTLE_MOVERS_MAX / 2; i < CASTLE_MOVERS_MAX; i++) {
      moverRun(&pCastle->m[i]);
		}
    for (i = 10; i < CASTLE_BUILIDNGS_MAX; i++) {
      buildingRun(&pCastle->b[i]);
		}
  }
  PlaceUsed = 0;
}

void castleDisableUnits(tCastle *pCastle) {
  for (UBYTE post = 1; post < CASTLE_MOVERS_MAX; post++) {
    pCastle->m[post].wybrany = 0;
  }

  for (UBYTE bud = 0; bud < CASTLE_BUILIDNGS_MAX; bud++) {
    for (UBYTE post = 0; post < BUILDING_MOVERS_MAX; post++) {
      pCastle->b[bud].m[post].wybrany = 0;
    }
	}
}

void castleFreeUnits(tCastle *pCastle) {
  for (UBYTE post = 1; post < CASTLE_MOVERS_MAX; post++) {
    moverDisable(&pCastle->m[post]);
  }
  for (UBYTE bud = 0; bud < CASTLE_BUILIDNGS_MAX; bud++) {
    for (UBYTE post = 0; post < BUILDING_MOVERS_MAX; post++) {
      moverDisable(&pCastle->b[bud].m[post]);
    }
	}
}

tCastle castle[2];
