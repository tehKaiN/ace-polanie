#pragma once

#include "gfx.h"

typedef enum tMissileKind {
	MISSILE_KIND_ARROW,
	MISSILE_KIND_LIGHTNING,
	MISSILE_KIND_FIREBALL,
	MISSILE_KIND_PIKE,
	MISSILE_KIND_PHANTOM,
	MISSILE_KIND_XBOW,
	MISSILE_KIND_COUNT
} tMissileKind;

typedef struct tMissile {
  int x, y, xt, yt, target;
  int dx, dy;
  char type;
  tImage *view;
  char visible;
  char exist;
  char damage;
} tMissile;

void missileImageCreate(void);

void missileImageDestroy(void);

void missileInit(tMissile *pMissile, int x1, int y1, int x2, int y2, int d, int t);

void missileMove(tMissile *pMissile);

void missileShow(tMissile *pMissile, int xe, int ye);

extern tImage missiles[MISSILE_KIND_COUNT][3][3];
