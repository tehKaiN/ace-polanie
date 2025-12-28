#include "missile.h"
#include <ace/macros.h>
#include "world.h"
#include "mover.h"
#include "battle.h"
#include "bitmap_pair.h"

static tBitmapPair s_sMissilesPair;

void missileImageCreate(void) {
	bitmapPairCreate(&s_sMissilesPair, "missiles");

	UWORD uwOffsY = 0;
	for(tMissileKind eMissileKind = 0; eMissileKind < MISSILE_KIND_COUNT; ++eMissileKind) {
		for(UBYTE ubDx = 0; ubDx < 2; ++ubDx) {
			for(UBYTE ubDy = 0; ubDy < 3; ++ubDy) {
				missiles[eMissileKind][ubDx][ubDy].pBitmap = s_sMissilesPair.pFrames;
				missiles[eMissileKind][ubDx][ubDy].pMask = s_sMissilesPair.pMasks;
				missiles[eMissileKind][ubDx][ubDy].uwWidth = 16;
				missiles[eMissileKind][ubDx][ubDy].uwHeight = 14;
				missiles[eMissileKind][ubDx][ubDy].uwOffsY = uwOffsY;
				uwOffsY += 14;
			}
		}
	}
}

void missileImageDestroy(void) {
	bitmapPairDestroy(&s_sMissilesPair);
}

void missileInit(tMissile *pMissile, int x1, int y1, int x2, int y2, int d, int t) {
  int max;
  if (pMissile->exist)
    return;

  pMissile->damage = d;
  pMissile->xt = x2;
  pMissile->yt = y2;
  pMissile->target = place[pMissile->xt][pMissile->yt];
  pMissile->dx = x2 - x1;
  pMissile->dy = y2 - y1;
  if (ABS(pMissile->dx) - ABS(pMissile->dy) > 1)
    pMissile->dy = 0;
  if (ABS(pMissile->dy) - ABS(pMissile->dx) > 1)
    pMissile->dx = 0;
  if (pMissile->dx > 0)
    pMissile->dx = -1;
  if (pMissile->dx < 0)
    pMissile->dx = -1;
  if (pMissile->dy > 0)
    pMissile->dy = 1;
  if (pMissile->dy < 0)
    pMissile->dy = -1;
  pMissile->exist = 6;
  pMissile->type = (char)t;
  switch (t) {
  case 9: // strzyga
  case 8: // niedzwiedz
  case 7: // miecz -bohater
  case 5: // miecz
  case 1:
    pMissile->view = NULL;
    break; // topor

  case 2:
    pMissile->exist++;
    pMissile->view = &missiles[0][pMissile->dx + 1][pMissile->dy + 1];
    break; // luk
  case 12:
    pMissile->exist++;
    pMissile->view = &missiles[5][pMissile->dx + 1][pMissile->dy + 1];
    break; // kusznik
  case 3:
    pMissile->exist += 3;
    pMissile->view = &missiles[1][pMissile->dx + 1][pMissile->dy + 1];
    break; // grom
  case 13:
    pMissile->exist += 3;
    pMissile->view = &missiles[1][pMissile->dx + 1][pMissile->dy + 1];
    break; // grom
  case 11:
    pMissile->exist += 3;
    pMissile->view = &missiles[4][pMissile->dx + 1][pMissile->dy + 1];
    break; // magowy
  case 4:
    pMissile->exist += 3;
    pMissile->view = &missiles[2][pMissile->dx + 1][pMissile->dy + 1];
    break; // duzy ogien
  case 14:
    pMissile->exist += 3;
    pMissile->view = &missiles[2][pMissile->dx + 1][pMissile->dy + 1];
    break; // duzy ogien
  case 6:
    pMissile->exist += 2;
    pMissile->view = &missiles[3][pMissile->dx + 1][pMissile->dy + 1];
    break; // wlocznia
  }
  //------------obliczenie przyrostow na ekranie
  max = 2;
  if (pMissile->view != NULL) {
    pMissile->dx = x2 - x1;
    pMissile->dy = y2 - y1;
    max = ABS(pMissile->dx);
    if (max < ABS(pMissile->dy))
      max = ABS(pMissile->dy);
    max = max << 1;
    if (max < 1)
      max = 2;
    pMissile->dx = (int)(pMissile->dx << 4) / max;
    pMissile->dy = (int)pMissile->dy * 14 / max;
    pMissile->x = x1 << 4;
    pMissile->y = y1 * 14;
    if (pMissile->type == 12) {
      pMissile->dx *= 2;
      pMissile->dy *= 2;
      max /= 2;
    }
    pMissile->x += pMissile->dx;
    pMissile->y += pMissile->dy;
  }
  //-------------------------
  pMissile->visible = max;
  pMissile->visible--;
  missileMove(pMissile);
}

void missileMove(tMissile *pMissile) {
  if (!pMissile->exist)
    return;
  if (pMissile->exist == 100) {
    pMissile->exist = 0;
    return;
  }
  if (pMissile->exist == 2) // dzwiek wystrzalu
  {
    // int kk = 0;
    // switch (pMissile->type) {
		// 	case 2:
		// 	case 6:
		// 		kk = 3;
		// 		break;
		// 	case 13:
		// 	case 3:
		// 		kk = 4;
		// 		break;
		// 	case 4:
		// 	case 14:
		// 		kk = 5;
		// 		break;
		// 	case 11:
		// 		kk = 6;
		// 		break; // duch
		// 	case 12:
		// 		kk = 7;
		// 		break; // kusza
    // }
    // if (Msg.dzwiek < kk) {
    //   Msg.dzwiek = kk;
    //   Msg.X = pMissile->xt;
    //   Msg.Y = pMissile->yt;
    // }
  }
  if (pMissile->exist > 1) {
    pMissile->exist--;
    return;
  }

  if (pMissile->visible)
    pMissile->visible--;
  if (pMissile->visible == 100) {
    pMissile->exist = 0;
    return;
  }
  if (pMissile->visible > 100) {
    attack[pMissile->xt][pMissile->yt] += pMissile->damage;
    return;
  }
  if (pMissile->visible > 0) {
    pMissile->x += pMissile->dx;
    pMissile->y += pMissile->dy;
  } else {
    pMissile->exist = 120; // opoznienie przed nastepnym strzalem
    if (pMissile->type == 4 || pMissile->type == 11 || pMissile->type == 12) {
      pMissile->exist = 130;
    }
    attack[pMissile->xt][pMissile->yt] += pMissile->damage;
    // gromobicie
    if (pMissile->type == 13) {
      attack[pMissile->xt + 1][pMissile->yt] += pMissile->damage;
      attack[pMissile->xt - 1][pMissile->yt] += pMissile->damage;
      pMissile->exist = 103;
    }
    // deszcz ognia
    if (pMissile->type == 14) {
      pMissile->exist = 103;
      attack[pMissile->xt + 1][pMissile->yt] += pMissile->damage;
      attack[pMissile->xt - 1][pMissile->yt] += pMissile->damage;
      if ((placeN[pMissile->xt][pMissile->yt] < 50 || placeG[pMissile->xt][pMissile->yt] < 112) &&
          (placeG[pMissile->xt][pMissile->yt] < 74 || placeG[pMissile->xt][pMissile->yt] > 86)) {
        placeN[pMissile->xt][pMissile->yt] = 100;
      }
      if ((placeN[pMissile->xt + 1][pMissile->yt] < 50 || placeG[pMissile->xt + 1][pMissile->yt] < 112) &&
          (placeG[pMissile->xt + 1][pMissile->yt] < 74 || placeG[pMissile->xt + 1][pMissile->yt] > 86)) {
        placeN[pMissile->xt + 1][pMissile->yt] = 100;
      }
      if ((placeN[pMissile->xt - 1][pMissile->yt] < 50 || placeG[pMissile->xt - 1][pMissile->yt] < 112) &&
          (placeG[pMissile->xt - 1][pMissile->yt] < 74 || placeG[pMissile->xt - 1][pMissile->yt] > 86)) {
        placeN[pMissile->xt - 1][pMissile->yt] = 100;
      }
    }
    /////kaplan i ognie
    if (pMissile->type == 4 && (placeN[pMissile->xt][pMissile->yt] < 50 || placeG[pMissile->xt][pMissile->yt] < 112) &&
        (placeG[pMissile->xt][pMissile->yt] < 74 || placeG[pMissile->xt][pMissile->yt] > 86)) {
      placeN[pMissile->xt][pMissile->yt] = 100;
    }
    if (pMissile->type == 4) { // rozrzut ognia po strzale
      if (pMissile->dx > -3 && pMissile->dx < 3)
        pMissile->dx = 0;
      if (pMissile->dx > 2)
        pMissile->dx = 1;
      if (pMissile->dx < -2)
        pMissile->dx = -1;
      if (pMissile->dy > -3 && pMissile->dy < 3)
        pMissile->dy = 0;
      if (pMissile->dy > 2)
        pMissile->dy = 1;
      if (pMissile->dy < -2)
        pMissile->dy = -1;
      pMissile->xt += pMissile->dx;
      pMissile->yt += pMissile->dy;
      if (placeG[pMissile->xt][pMissile->yt] < 74 || placeG[pMissile->xt][pMissile->yt] > 86) {
        placeN[pMissile->xt][pMissile->yt] = 90;
        attack[pMissile->xt][pMissile->yt] += (pMissile->damage - 10);
      }
      pMissile->xt += pMissile->dx;
      pMissile->yt += pMissile->dy;
      if (placeG[pMissile->xt][pMissile->yt] < 74 || placeG[pMissile->xt][pMissile->yt] > 86) {
        placeN[pMissile->xt][pMissile->yt] = 80;
        attack[pMissile->xt][pMissile->yt] += (pMissile->damage - 20);
      }
    }
    if ((pMissile->type != 4) && (pMissile->type != 11) && (pMissile->type < 13)) {
      if (!place[pMissile->xt][pMissile->yt]) {
        tMover *tar = moverGetByNum(pMissile->target);
        if (tar != NULL) {
          if (ABS(pMissile->xt - tar->x) < 2 && ABS(pMissile->yt - tar->y) < 2) {
            pMissile->xt = tar->x;
            pMissile->yt = tar->y;
            if (g_eDifficulty)
              attack[pMissile->xt][pMissile->yt] += (pMissile->damage >> 1);
            else
              attack[pMissile->xt][pMissile->yt] += (pMissile->damage >> 2);
          }
        }
      }
    }
    // dzwieki uderzen
    // if (pMissile->type == 8 && Msg.dzwiek < 8) {
    //   Msg.dzwiek = 8;
    //   Msg.X = pMissile->xt;
    //   Msg.Y = pMissile->yt;
    // }
    // if (pMissile->type == 9 && Msg.dzwiek < 9) {
    //   Msg.dzwiek = 9;
    //   Msg.X = pMissile->xt;
    //   Msg.Y = pMissile->yt;
    // }
    if (pMissile->type == 7 || pMissile->type == 5 || pMissile->type == 1) {
      if (place[pMissile->xt][pMissile->yt] > 768)
        pMissile->dx = 1;
      else
        pMissile->dx = 2;
      // if (Msg.dzwiek < pMissile->dx) {
      //   Msg.dzwiek = pMissile->dx;
      //   Msg.X = pMissile->xt;
      //   Msg.Y = pMissile->yt;
      // }
    }
    // duch
    if (pMissile->type == 11) {
      pMissile->visible = 140;
      pMissile->exist = 1;
      pMissile->x = pMissile->xt * 16;
      pMissile->y = pMissile->yt * 14;
    } else {
      pMissile->view = NULL;
      pMissile->dx = 0;
      pMissile->dy = 0;
    }
  }
}

void missileShow(tMissile *pMissile, int xe, int ye) {
  if (pMissile->exist != 1)
    return;

  if (pMissile->view != NULL) {
    int a, b;
    a = pMissile->x - xe;
    b = pMissile->y - ye;
    if (a > 10 && a <= 259 && b > 7 && b < 185) {
      if (pMissile->visible > 100) // duszacy duszek
      {
        if (pMissile->visible & 0x04) // duszacy duszek
        {
          gfxDrawImageMaskedClipped(a, b, &missiles[4][1][1]);
        } else {
          if (pMissile->dx > 0)
            PutImageChangeInverse13h(a, b, pMissile->view, 1, 1, 1);
          else
            gfxDrawImageMaskedClipped(a, b, pMissile->view);
        }
      } else {
        if (pMissile->dx > 0)
          PutImageChangeInverse13h(a, b, pMissile->view, 1, 1, 1);
        else
          gfxDrawImageMaskedClipped(a, b, pMissile->view);
        if (pMissile->type == 13 || pMissile->type == 14) {
          int k = (6 + (pMissile->y / 14) - pMissile->yt) * 2;
          gfxDrawImageMaskedClipped(a - k, b - 5, pMissile->view);
          gfxDrawImageMaskedClipped(a + k, b - 5, pMissile->view);
        }
      }
    }
  }
}

tImage missiles[MISSILE_KIND_COUNT][3][3];
