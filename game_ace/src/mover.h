#pragma once

#include "gfx.h"
#include "missile.h"
#include "map_object.h"

typedef enum tMoverExist {
  MOVER_EXIST_NONE = 0,
  MOVER_EXIST_ALIVE = 1,
  MOVER_EXIST_ROT = 2,
} tMoverExist;

typedef enum tMoverPhase {
	MOVER_PHASE_STAND,
	MOVER_PHASE_WALK1,
	MOVER_PHASE_WALK2,
	MOVER_PHASE_ACTION1,
	MOVER_PHASE_ACTION2,
	MOVER_PHASE_COUNT
} tMoverPhase;

typedef enum tMoverKind {
	MOVER_KIND_COW = 0,
	MOVER_KIND_AXE = 1,
	MOVER_KIND_HUNTER = 2,
	MOVER_KIND_PRIESTESS = 3,
	MOVER_KIND_PRIEST = 4,
	MOVER_KIND_SWORD = 5,
	MOVER_KIND_PIKE = 6,
	MOVER_KIND_KNIGHT = 7,
	MOVER_KIND_BEAR = 8,
	MOVER_KIND_BEAST = 9,
	MOVER_KIND_FARMER = 10,
	MOVER_KIND_MAGE = 11,
	MOVER_KIND_XBOW = 12,
	MOVER_KIND_COUNT = 13
} tMoverKind;

typedef tImage tMoverFrameset[MOVER_PHASE_COUNT][3][3]; // phase, dx, dy

typedef struct tMover {
  tMapObject sMapObject;
  int xr, yr;
  char wybrany;
  int hp, maxhp;
  int mainTarget; // bool
  int visible;
  int command, commandN; // 0-nic 1-go 2-fight
  tMoverKind type;              // 0-krowa 1-miecz 2-luk 3-mag
  tMissile missile;
  tMoverExist exist;

  int exp;
  int xe, ye; // enemy x/y
  int dx, dy;
  int phase; // 0-faza ruch  1-faza ruch 2-atak
  int faza;
  int magic; // 100
  int xp, yp, xm, ym;
  int armour, marmour;
  int inmove;
  int inattack;
  int drange;
  int damage;
  int udder;
  int base;
  int s_range;
  int a_range;
  const tMapObject *target;
  const tMoverFrameset *pFrameset;
  int ShowHit;
  int delay, maxdelay;
  int ispath;
  int path[6][2];
} tMover;

void moverGraphicsCreate(void);

void moverGraphicsDestroy(void);

tMover *moverGetByNum(int nr);
tMover *moverTryGetAt(UBYTE ubX, UBYTE ubY);

void moverConstruct(tMover *pMover);
void moverDestruct(tMover *pMover);
void moverMove(tMover *pMover);
void moverShow(tMover *pMover);
void moverHide(tMover *pMover);
void moverSetEnd(tMover *pMover, int, int);
void moverSetStart(tMover *pMover, int, int);
void moverPrepare(tMover *pMover, int, int, int);
void moverShowS(tMover *pMover);
void moverDisable(tMover *pMover);
void moverRepare(tMover *pMover);
void moverSetIFF(tMover *pMover, tMapObjectTeam eTeam);
void moverInit(tMover *pMover, int eMoverKind, int x1, int y1, int c, int d);
void moverSetCommand(tMover *pMover, int);
void moverSetTarget(tMover *pMover, const tMapObject *pTarget);
void moverRun(tMover *pMover);
int moverMilk(tMover *pMover);
int moverOK(const tMover *pMover);

void moverFindGrass(tMover *pMover);
void moverLabeling(tMover *pMover);
int moverLookAround(tMover *pMover);
int moverLokateTarget(tMover *pMover);
void moverGraze(tMover *pMover); // pasienie sie
void moverAttack(tMover *pMover);
int moverDistance(tMover *pMover);

extern tMoverFrameset g_pMoverFrames[MOVER_KIND_COUNT];
extern int PlaceUsed;
