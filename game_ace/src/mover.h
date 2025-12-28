#pragma once

#include "gfx.h"
#include "missile.h"

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

typedef struct tMover {
  int xr, yr;
  char wybrany;
  int nr; // nr bity 0-7 nr bity 8-9 IFF bity 10-15 typ
  int hp, maxhp;
  int mainTarget;
  int visible;
  int command, commandN; // 0-nic 1-go 2-fight
  tMoverKind type;              // 0-krowa 1-miecz 2-luk 3-mag
  tMissile missile;

  int exist;

  int IFF; // zawsze 1 lub 2
  int exp;
  int x, y;
  int xe, ye;
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
  int target;
  int ShowHit;
  int delay, maxdelay;
  int ispath;
  int path[6][2];
} tMover;

void moverGraphicsCreate(void);

void moverGraphicsDestroy(void);

tMover *moverGetByNum(int nr);

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
void moverSetNr(tMover *pMover, int);
void moverSetIFF(tMover *pMover, int);
void moverInit(tMover *pMover, int, int, int, int, int);
void moverSetCommand(tMover *pMover, int);
void moverSetTarget(tMover *pMover, int);
void moverRun(tMover *pMover);
int moverMilk(tMover *pMover);
int moverOK(const tMover *pMover);

void moverFindGrass(tMover *pMover);
void moverLabeling(tMover *pMover);
void moverRun1(tMover *pMover);
void moverRun2(tMover *pMover);
int moverLookAround(tMover *pMover);
int moverLokateTarget(tMover *pMover);
void moverGraze(tMover *pMover); // pasienie sie
void moverAttack(tMover *pMover);
int moverDistance(tMover *pMover);

extern tImage movers[MOVER_PHASE_COUNT][MOVER_KIND_COUNT][3][3]; // faza:typ:dx:dy
extern int PlaceUsed;
