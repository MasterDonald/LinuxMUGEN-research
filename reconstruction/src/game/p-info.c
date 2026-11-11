/*
 * p-info.c -- player queries
 * Relations between players (partners, enemies, targets, nearest enemy),
 * distances, widths, guard distance and existence checks used by triggers.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/p-info.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* PlayerNearestEnemy @ 0x080ab1c0, 488 bytes
 *
 * Returns the closest active, not-dead enemy of a player (by body distance),
 * preferring current targets. Stored as the player's "p2" each frame.
 *
 * Parameters:
 *   player       int
 *
 * Player fields read: targets, movetype, active, ishelper
 * Globals read: slot_first, slot_last
 * Calls: ArrayScanFirst, PlayerLyingDead, PlayerAreEnemies,
 *        PlayerBodyDistX, ArrayScanNext
 * Called by: GameUpdate, HelperMake
 *
 * Elecbyte file: src/mugen/p-info.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 */
int PlayerNearestEnemy(int player)

{
  bool b1;
  int *item;
  int player2;
  int i4;
  int saved_ESI;
  int player3;
  int stk_1c;
  int player4;
  int stk_14;
  
  stk_14 = 0;
  player4 = player;
  if (*(int *)(player + 0x2624) != 0) {
    player4 = *(int *)(player + 0x2624);
  }
  item = (int *)ArrayScanFirst(*(int *)(player + PLB_TARGETS));
  while ((item != (int *)0x0 && (*(int *)(player + PLB_MOVETYPE) == 1))) {
    player3 = *item;
    if ((player3 == 0) || (b1 = true, *(int *)(player3 + PLB_ACTIVE) == 0)) {
      b1 = false;
    }
    if ((((b1) && (player3 != player)) && (player2 = PlayerLyingDead(player3), player2 == 0)) &&
       ((player2 = PlayerAreEnemies(player4,player3), player2 != 0 &&
        ((*(int *)(player3 + PLB_ISHELPER) == 0 || (*(int *)(player3 + 0x2628) == 1)))))) {
      if (stk_14 == 0) {
        saved_ESI = PlayerBodyDistX(player,player3);
        stk_14 = player3;
        if (saved_ESI < 0) {
          saved_ESI = -saved_ESI;
        }
      }
      else {
        player2 = PlayerBodyDistX(player,player3);
        if (player2 < 0) {
          player2 = -player2;
        }
        if (player2 < saved_ESI) {
          stk_14 = player3;
        }
      }
    }
    item = (int *)ArrayScanNext(*(int *)(player + PLB_TARGETS));
  }
  if ((stk_14 == 0) && (player3 = g[G_SLOT_FIRST], player3 <= g[G_SLOT_LAST])) {
    stk_1c = player3 * 4 + 0x1cf60;
    item = g;
    do {
      player2 = *(int *)(stk_1c + 4 + (int)item);
      if ((player2 == 0) || (b1 = true, *(int *)(player2 + PLB_ACTIVE) == 0)) {
        b1 = false;
      }
      if (((((b1) && (player2 != player)) &&
           (i4 = PlayerLyingDead(player2), item = g, i4 == 0)) &&
          (i4 = PlayerAreEnemies(player4,player2), item = g, i4 != 0)) &&
         ((*(int *)(player2 + PLB_ISHELPER) == 0 || (*(int *)(player2 + 0x2628) == 1)))) {
        if (stk_14 == 0) {
          saved_ESI = PlayerBodyDistX(player,player2);
          item = g;
          stk_14 = player2;
          if (saved_ESI < 0) {
            saved_ESI = -saved_ESI;
          }
        }
        else {
          i4 = PlayerBodyDistX(player,player2);
          if (i4 < 0) {
            i4 = -i4;
          }
          item = g;
          if (i4 < saved_ESI) {
            stk_14 = player2;
          }
        }
      }
      player3 = player3 + 1;
      stk_1c = stk_1c + 4;
    } while (player3 <= item[0x745a]);
  }
  return stk_14;
}

/* PartnerAccess @ 0x080ab3b0, 123 bytes
 *
 * Returns the n-th teammate of a player, or NULL. Partner redirection.
 *
 * Parameters:
 *   player       int
 *   n            int
 *
 * Player fields read: teamside
 * Globals read: slot_first, slot_last
 * Called by: SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/p-info.c
 */
int PartnerAccess(int player,int n)

{
  int i1;
  bool b2;
  int i3;
  int i4;
  int i5;
  
  i5 = 0;
  i3 = g[G_SLOT_FIRST];
  if (i3 <= g[G_SLOT_LAST]) {
    i4 = i3 * 4 + 0x1cf60;
    do {
      i1 = *(int *)(i4 + 4 + (int)g);
      if (((i1 == 0) || (*(int *)(i1 + 0x158) == 0)) ||
         (b2 = true, *(int *)(i1 + 0x1c) != 0)) {
        b2 = false;
      }
      if (((b2) && (*(int *)(i1 + 0xc) == *(int *)(player + PLB_TEAMSIDE))) &&
         ((i1 != player && (i1 != *(int *)(player + 0x2624))))) {
        if (i5 == n) {
          return i1;
        }
        i5 = i5 + 1;
      }
      i3 = i3 + 1;
      i4 = i4 + 4;
    } while (i3 <= g[G_SLOT_LAST]);
  }
  return 0;
}

/* PartnerCount @ 0x080ab430, 115 bytes
 *
 * Returns the number of a player's teammates. NumPartner trigger.
 *
 * Parameters:
 *   player       int
 *
 * Player fields read: teamside
 * Globals read: slot_first, slot_last
 * Called by: SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/p-info.c
 */
int PartnerCount(int player)

{
  int i1;
  bool b2;
  int i3;
  int i4;
  int i5;
  
  i5 = 0;
  i3 = g[G_SLOT_FIRST];
  if (i3 <= g[G_SLOT_LAST]) {
    i4 = i3 * 4 + 0x1cf60;
    do {
      i1 = *(int *)(i4 + 4 + (int)g);
      if (((i1 == 0) || (*(int *)(i1 + 0x158) == 0)) ||
         (b2 = true, *(int *)(i1 + 0x1c) != 0)) {
        b2 = false;
      }
      if (((b2) && (*(int *)(i1 + 0xc) == *(int *)(player + PLB_TEAMSIDE))) &&
         ((i1 != player && (i1 != *(int *)(player + 0x2624))))) {
        i5 = i5 + 1;
      }
      i3 = i3 + 1;
      i4 = i4 + 4;
    } while (i3 <= g[G_SLOT_LAST]);
  }
  return i5;
}

/* EnemyAccess @ 0x080ab4b0, 133 bytes
 *
 * Returns the n-th enemy player, or NULL. Enemy redirection.
 *
 * Parameters:
 *   player       int
 *   n            int
 *
 * Globals read: slot_first, slot_last
 * Calls: PlayerAreEnemies
 * Called by: SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/p-info.c
 */
int EnemyAccess(int player,int n)

{
  int i1;
  bool b2;
  int i3;
  int *pi4;
  int i5;
  int i6;
  int i7;
  
  i5 = 0;
  i6 = g[G_SLOT_FIRST];
  if (i6 <= g[G_SLOT_LAST]) {
    i7 = i6 * 4 + 0x1cf60;
    pi4 = g;
    do {
      i1 = *(int *)(i7 + 4 + (int)pi4);
      if (((i1 == 0) || (*(int *)(i1 + 0x158) == 0)) ||
         (b2 = true, *(int *)(i1 + 0x1c) != 0)) {
        b2 = false;
      }
      if ((b2) && (i3 = PlayerAreEnemies(player,i1), pi4 = g, i3 != 0)) {
        if (i5 == n) {
          return i1;
        }
        i5 = i5 + 1;
      }
      i6 = i6 + 1;
      i7 = i7 + 4;
    } while (i6 <= pi4[0x745a]);
  }
  return 0;
}

/* EnemyCount @ 0x080ab540, 130 bytes
 *
 * Returns the number of enemy players. NumEnemy trigger.
 *
 * Parameters:
 *   player       int
 *
 * Globals read: slot_first, slot_last
 * Calls: PlayerAreEnemies
 * Called by: SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/p-info.c
 */
int EnemyCount(int player)

{
  bool b1;
  int i2;
  int *pi3;
  int i4;
  int i5;
  int i6;
  
  i6 = 0;
  i4 = g[G_SLOT_FIRST];
  if (i4 <= g[G_SLOT_LAST]) {
    i5 = i4 * 4 + 0x1cf60;
    pi3 = g;
    do {
      i2 = *(int *)(i5 + 4 + (int)pi3);
      if (((i2 == 0) || (*(int *)(i2 + 0x158) == 0)) ||
         (b1 = true, *(int *)(i2 + 0x1c) != 0)) {
        b1 = false;
      }
      if ((b1) && (i2 = PlayerAreEnemies(player,i2), pi3 = g, i2 != 0)) {
        i6 = i6 + 1;
      }
      i4 = i4 + 1;
      i5 = i5 + 4;
    } while (i4 <= pi3[0x745a]);
  }
  return i6;
}

/* EnemyAccessNear @ 0x080ab5d0, 250 bytes
 *
 * Returns the n-th nearest enemy, or NULL. EnemyNear redirection.
 *
 * Parameters:
 *   player       int
 *   n            int
 *
 * Player fields read: teamside
 * Calls: PlayerDistX
 * Called by: SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/p-info.c
 */
uint32_t EnemyAccessNear(int player,int n)

{
  bool b1;
  bool b2;
  int i3;
  int i4;
  int i5;
  int i6;
  
  i6 = 0;
  i5 = 0;
  if (n < 2) {
    if (*(int *)(player + PLB_TEAMSIDE) == 1) {
      i6 = g[0x73db];
      i5 = g[0x73dd];
    }
    else if (*(int *)(player + PLB_TEAMSIDE) == 2) {
      i6 = g[0x73da];
      i5 = g[0x73dc];
    }
    if ((i6 == 0) || (b1 = true, *(int *)(i6 + 0x158) == 0)) {
      b1 = false;
    }
    if ((i5 == 0) || (b2 = true, *(int *)(i5 + 0x158) == 0)) {
      b2 = false;
    }
    if ((b1) || (b2)) {
      if ((n == 0) && ((b1 && (!b2)))) {
        return i6;
      }
      if (((n == 0) && (!b1)) && (b2)) {
        return i5;
      }
      if ((b1) && (b2)) {
        i3 = PlayerDistX(player,i6);
        if (i3 < 0) {
          i3 = -i3;
        }
        i4 = PlayerDistX(player,i5);
        if (i4 < 0) {
          i4 = -i4;
        }
        if (i3 < i4) {
          if (n == 0) {
            return i6;
          }
          return i5;
        }
        if (n == 0) {
          return i5;
        }
        return i6;
      }
    }
  }
  return 0;
}

/* PlayerAccessID @ 0x080ab6d0, 112 bytes
 *
 * Returns the active player with id `id`, or NULL. PlayerID redirection,
 * explod binding.
 *
 * Parameters:
 *   id           int
 *
 * Globals read: slot_first, slot_last
 * Called by: ExplodUpdate, SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/p-info.c
 */
int PlayerAccessID(int id)

{
  int i1;
  bool b2;
  int i3;
  int i4;
  int *pi5;
  
  i3 = g[G_SLOT_FIRST];
  if (i3 <= g[G_SLOT_LAST]) {
    pi5 = g + i3 + 0x73d9;
    i4 = i3 * 4 + 0x1cf60;
    do {
      i1 = *(int *)(i4 + 4 + (int)g);
      if ((i1 == 0) || (b2 = true, *(int *)(i1 + 0x158) == 0)) {
        b2 = false;
      }
      if ((b2) && (*(int *)(*pi5 + 4) == id)) {
        return *pi5;
      }
      i3 = i3 + 1;
      pi5 = pi5 + 1;
      i4 = i4 + 4;
    } while (i3 <= g[G_SLOT_LAST]);
  }
  return 0;
}

/* PlayerGetDamagedLife @ 0x080ab740, 19 bytes
 *
 * Returns the player's life minus its pending damage (the damage of the hit
 * being received).
 *
 * Parameters:
 *   player       int
 *
 * Player fields read: life
 * Called by: Player1HitP2, PlayerCheckProjHit, PlayerGetCorrectedDamage,
 *            PlayerUpdate
 *
 * Elecbyte file: src/mugen/p-info.c
 */
int PlayerGetDamagedLife(int player)

{
  return *(int *)(player + PLB_LIFE) - *(int *)(player + 0x1028);
}

/* PlayerInCorner @ 0x080ab760, 126 bytes
 *
 * Returns true if the player is against a screen or stage edge.
 *
 * Parameters:
 *   player       int
 *
 * Player fields read: pos_x
 * Called by: AIForTrainingMode, Player1HitP2
 *
 * Elecbyte file: src/mugen/p-info.c
 */
uint32_t PlayerInCorner(int player)

{
  if ((8 < ((int)X87_FIST32(*(float *)(player + PLB_POS_X)) - *(int *)(player + 0x1d4)) + 4U) &&
     (8 < ((int)X87_FIST32(*(float *)(player + PLB_POS_X)) - *(int *)(player + 0x1d8)) + 4U)) {
    return 0;
  }
  return 1;
}

/* PlayerDistX @ 0x080ab7e0, 65 bytes
 *
 * Returns the horizontal distance from the first player to the second,
 * multiplied by the first player's facing (positive = in front of it),
 * truncated to an int.
 *
 * Parameters:
 *   player       int
 *   player2      int
 *
 * Player fields read: pos_x
 * Called by: EnemyAccessNear, PlayerBodyDistX, PlayerInGuardDist,
 *            PlayerSCtrlUpdate, SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/p-info.c
 */
int PlayerDistX(int player,int player2)

{
  return (int)X87_FIST32(*(float *)(player2 + 0x19c) - *(float *)(player + PLB_POS_X)) *
         *(int *)(player + 400);
}

/* PlayerBodyDistX @ 0x080ab830, 252 bytes
 *
 * Returns the horizontal distance between the front edges of two players'
 * bodies (PlayerDistX minus both widths). P2BodyDist trigger.
 *
 * Parameters:
 *   player       int
 *   player2      int  (player)
 *
 * Player fields read: statetype, pos_x
 * Calls: PlayerDistX
 * Called by: PlayerNearestEnemy, SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/p-info.c
 * Note: 3 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 2 temporaries are float80, as the original kept them in x87 registers.
 */
int PlayerBodyDistX(int player,int player2)

{
  float80 f1;
  float80 f2;
  int i3;
  int i4;
  
  if (*(int *)(player + PLB_STATETYPE) == 3) {
    i3 = *(int *)(player + 400) * *(int *)(player + 0x90);
  }
  else {
    i3 = *(int *)(player + 400) * *(int *)(player + 0x88);
  }
  f1 = *(float *)(player + PLB_POS_X);
  i4 = PlayerDistX(player2,player);
  if (i4 < 1) {
    if (*(int *)(player2 + PLB_STATETYPE) == 3) {
      i4 = *(int *)(player2 + 400) * *(int *)(player2 + 0x8c);
    }
    else {
      i4 = *(int *)(player2 + 400) * *(int *)(player2 + 0x84);
    }
    f2 = *(float *)(player2 + PLB_POS_X) - (float80)i4;
  }
  else {
    if (*(int *)(player2 + PLB_STATETYPE) == 3) {
      i4 = *(int *)(player2 + 400) * *(int *)(player2 + 0x90);
    }
    else {
      i4 = *(int *)(player2 + 400) * *(int *)(player2 + 0x88);
    }
    f2 = (float80)i4 + *(float *)(player2 + PLB_POS_X);
  }
  return (int)X87_FIST32(f2 - ((float80)i3 + f1)) * *(int *)(player + 400);
}

/* PlayerInAnyGuardDist @ 0x080ab930, 177 bytes
 *
 * Returns true if any enemy attack (an active HitDef or projectile) is
 * within guard distance of the player. InGuardDist trigger.
 *
 * Parameters:
 *   arg1         int
 *
 * Player fields read: active, teamside, movetype, projectiles
 * Globals read: slot_first, slot_last
 * Calls: PlayerInGuardDist
 * Called by: SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/p-info.c
 */
uint32_t PlayerInAnyGuardDist(int arg1)

{
  bool b1;
  int player;
  int *pi3;
  int i4;
  int i5;
  int i6;
  
  i4 = g[G_SLOT_FIRST];
  if (i4 <= g[G_SLOT_LAST]) {
    i5 = i4 * 4 + 0x1cf60;
    pi3 = g;
    i6 = i5;
    do {
      player = *(int *)(i6 + 4 + (int)pi3);
      if (arg1 != player) {
        if ((player == 0) || (b1 = true, *(int *)(player + PLB_ACTIVE) == 0)) {
          b1 = false;
        }
        if (b1) {
          player = *(int *)(i5 + 4 + (int)pi3);
          if ((((*(int *)(player + PLB_TEAMSIDE) != *(int *)(arg1 + 0xc)) && (*(int *)(player + PLB_TEAMSIDE) != 0))
              && ((*(int *)(player + PLB_MOVETYPE) == 1 || (0 < *(int *)(**(int **)(player + PLB_PROJECTILES) + 8)))))
             && (player = PlayerInGuardDist(arg1,player), pi3 = g, player != 0)) {
            return 1;
          }
        }
      }
      i4 = i4 + 1;
      i5 = i5 + 4;
      i6 = i6 + 4;
    } while (i4 <= pi3[0x745a]);
  }
  return 0;
}

/* PlayerInGuardDist @ 0x080ab9f0, 177 bytes
 *
 * Returns true if player `attacker`'s attack or one of its projectiles is
 * within guard distance of `player`.
 *
 * Parameters:
 *   arg1         int
 *   player       int
 *
 * Player fields read: projectiles
 * Calls: PlayerDistX, ArrayScanFirst, ArrayScanNext
 * Called by: AICheckForAttacks, AIForNormalRandom, PlayerInAnyGuardDist,
 *            PlayerKBUpdate
 *
 * Elecbyte file: src/mugen/p-info.c
 */
uint32_t PlayerInGuardDist(int arg1,int player)

{
  int array;
  int item;
  uint32_t u3;
  int i4;
  
  array = **(int **)(player + PLB_PROJECTILES);
  item = PlayerDistX(player,arg1);
  if (((item < *(int *)(player + 0x12cc)) && (-1 < item)) && (*(int *)(array + 8) == 0)) {
L_080aba23:
    u3 = 1;
  }
  else {
    item = ArrayScanFirst(array);
    while (item != 0) {
      if (*(int *)(item + 0x98) != 0) {
        i4 = (int)X87_FIST32(*(float *)(arg1 + 0x19c) - *(float *)(item + 0x44)) *
                *(int *)(item + 0x34);
        if ((i4 < *(int *)(item + 0x20c)) && (-1 < i4)) goto L_080aba23;
      }
      item = ArrayScanNext(array);
    }
    u3 = 0;
  }
  return u3;
}

/* HitdefAffectTeam @ 0x080abab0, 47 bytes
 *
 * Returns true if a HitDef's affectteam (enemy, friend, both) allows it to
 * hit `target`.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         uint32_t
 *
 * Called by: CheckProjHitProj, PlayerCheckHit, PlayerCheckHitProj,
 *            PlayerCheckProjHit
 *
 * Elecbyte file: src/mugen/p-info.c
 */
bool HitdefAffectTeam(int arg1,int arg2,uint32_t arg3)

{
  uint32_t u1;
  
  u1 = *(uint32_t *)(arg1 + 8);
  if (arg2 == 2) {
    u1 = u1 & 0xfffffffc | (u1 & 1) * 2 | u1 >> 1 & 1;
  }
  return (arg3 & u1) != 0;
}

/* PlayerAreEnemies @ 0x080abae0, 36 bytes
 *
 * Returns true if two players are on different teams.
 *
 * Parameters:
 *   player       int
 *   player2      int
 *
 * Player fields read: teamside
 * Called by: EnemyAccess, EnemyCount, GameClsnUpdate, PlayerNearestEnemy
 *
 * Elecbyte file: src/mugen/p-info.c
 */
uint32_t PlayerAreEnemies(int player,int player2)

{
  uint32_t u1;
  
  u1 = 0;
  if (((*(int *)(player + PLB_TEAMSIDE) != *(int *)(player2 + 0xc)) && (*(int *)(player + PLB_TEAMSIDE) != 0)) &&
     (*(int *)(player2 + 0xc) != 0)) {
    u1 = 1;
  }
  return u1;
}

/* PlayerGetWidth @ 0x080abb10, 219 bytes
 *
 * Returns a player's front and back widths for its state type (ground or air
 * sizes, plus the Width controller values).
 *
 * Parameters:
 *   player       int
 *   arg2         int
 *   arg3         uint32_t
 *
 * Player fields read: statetype
 * Called by: CameraMoveP, Player1HitP2, Player1ReverseP2,
 *            PlayerCheckOverlap, ScreenBound
 *
 * Elecbyte file: src/mugen/p-info.c
 */
int PlayerGetWidth(int player,int arg2,uint32_t arg3)

{
  int i1;
  int i2;
  
  i1 = 0;
  i2 = 0;
  if (arg2 == 2) {
    i2 = -*(int *)(player + 400);
  }
  else if (arg2 < 3) {
    if (arg2 == 1) {
      i2 = *(int *)(player + 400);
    }
  }
  else if (arg2 == 3) {
    i2 = -1;
  }
  else if (arg2 == 4) {
    i2 = 1;
  }
  if (arg3 < 3) {
    if (*(int *)(player + PLB_STATETYPE) == 3) {
      if (*(int *)(player + 400) == i2) {
        i1 = *(int *)(player + 0x90);
      }
      else {
        i1 = *(int *)(player + 0x8c);
      }
    }
    else if (*(int *)(player + 400) == i2) {
      i1 = *(int *)(player + 0x88);
    }
    else {
      i1 = *(int *)(player + 0x84);
    }
  }
  if ((arg3 == 1) || (arg3 == 3)) {
    if (*(int *)(player + 400) != i2) {
      return i1 + *(int *)(player + 0x200);
    }
    i2 = *(int *)(player + 0x1fc);
  }
  else {
    if ((arg3 != 2) && (arg3 != 4)) {
      return i1;
    }
    if (*(int *)(player + 400) == i2) {
      return i1 + *(int *)(player + 500);
    }
    i2 = *(int *)(player + 0x1f8);
  }
  return i1 + i2;
}

/* PlayerAnimExist @ 0x080abbf0, 38 bytes
 *
 * Returns true if animation `action` exists in the animations the player is
 * currently using. AnimExist trigger.
 *
 * Parameters:
 *   player       int
 *   action       int
 *
 * Player fields read: anim
 * Calls: AnimGrpNoToIdx
 * Called by: SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/p-info.c
 */
bool PlayerAnimExist(int player,int action)

{
  int index;
  
  index = AnimGrpNoToIdx(*(uint32_t **)(player + PLB_ANIM),0,action);
  return index != -1;
}

/* PlayerSelfAnimExist @ 0x080abc20, 67 bytes
 *
 * Returns true if animation `action` exists in the player's own animations.
 * SelfAnimExist trigger.
 *
 * Parameters:
 *   player       int *
 *   action       int
 *
 * Player fields written: anim
 * Calls: AnimGrpNoToIdx
 * Called by: SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/p-info.c
 */
bool PlayerSelfAnimExist(int *player,int action)

{
  uint32_t u1;
  int index;
  
  u1 = *(uint32_t *)player[PL_ANIM];
  *(uint32_t *)player[PL_ANIM] = *(uint32_t *)(*player + 0x11cc);
  index = AnimGrpNoToIdx((uint32_t *)player[PL_ANIM],0,action);
  *(uint32_t *)player[PL_ANIM] = u1;
  return index != -1;
}

/* PlayerLyingDead @ 0x080abc70, 26 bytes
 *
 * Returns true if the player is KOed and lying down (in the lie-dead state
 * long enough).
 *
 * Parameters:
 *   player       int
 *
 * Player fields read: stateno, statetime
 * Called by: GameLifeBarUpdate, GameRoundUpdate, PlayerComboCountCheck,
 *            PlayerNearestEnemy, PlayerUpdate
 *
 * Elecbyte file: src/mugen/p-info.c
 */
uint32_t PlayerLyingDead(int player)

{
  if (*(int *)(player + PLB_STATENO) == 0x141e) {
    return *(uint32_t *)(player + PLB_STATETIME);
  }
  return 0;
}

/* PlayerFindTarget @ 0x080abc90, 47 bytes
 *
 * Returns the entry for player `p` in a target array, or NULL.
 *
 * Parameters:
 *   array        int
 *   arg2         int
 *
 * Calls: ArrayScanFirst, ArrayScanNext
 * Called by: Player1HitP2, Player1ReverseP2, PlayerCheckHit,
 *            PlayerCheckProjHit, PlayerUpdate
 *
 * Elecbyte file: src/mugen/p-info.c
 */
int * PlayerFindTarget(int array,int arg2)

{
  int *item;
  
  item = (int *)ArrayScanFirst(array);
  while( true ) {
    if (item == (int *)0x0) {
      return (int *)0x0;
    }
    if (*item == arg2) break;
    item = (int *)ArrayScanNext(array);
  }
  return item;
}

/* TargetAccessID @ 0x080abcc0, 64 bytes
 *
 * Returns the first target with HitDef id `id` (-1 = any), or NULL. Target
 * redirection.
 *
 * Parameters:
 *   array        int
 *   arg2         int
 *
 * Calls: ArrayScanFirst, ArrayScanNext
 * Called by: SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/p-info.c
 */
uint32_t TargetAccessID(int array,int arg2)

{
  int *item;
  
  item = (int *)ArrayScanFirst(array);
  while( true ) {
    if (item == (int *)0x0) {
      return 0;
    }
    if (*(int *)(*item + 0x1064) == arg2) break;
    if (arg2 == -1) {
      return item;
    }
    item = (int *)ArrayScanNext(array);
  }
  return item;
}

/* TargetCount @ 0x080abd00, 62 bytes
 *
 * Counts the targets with HitDef id `id` (-1 = all). NumTarget trigger.
 *
 * Parameters:
 *   array        int
 *   arg2         int
 *
 * Calls: ArrayScanFirst, ArrayScanNext
 * Called by: SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/p-info.c
 */
int TargetCount(int array,int arg2)

{
  int *item;
  int i2;
  
  i2 = 0;
  item = (int *)ArrayScanFirst(array);
  while (item != (int *)0x0) {
    if ((*(int *)(*item + 0x1064) == arg2) || (arg2 == -1)) {
      i2 = i2 + 1;
    }
    item = (int *)ArrayScanNext(array);
  }
  return i2;
}

