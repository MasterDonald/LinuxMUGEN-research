/*
 * p-update.c -- player update and hits
 * Per-frame player update (states, physics, bounds), the collision pass
 * (pushes, hits, reversals, projectiles), damage and get-hit reactions,
 * sparks and dust, and player drawing.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/p-update.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"

extern int nokoflag_0 __asm__("D_08288040"); /* file-static 0x08288040 */

/* PlayerReset @ 0x080b0fe0, 1512 bytes
 *
 * Resets a player for a new round: removes projectiles and targets, clears
 * command timers and key flags, variables (unless persistent), hit
 * definition, position, velocity, facing, state flags, PalFX, and returns it
 * to its stand animation.
 *
 * Parameters:
 *   player       int *
 *
 * Player fields read: teamside, projectiles, targets, var, fvar, hitdef,
 *                     anim
 * Player fields written: attackmul, facing, vel_z, vel_y, vel_x, offset_y,
 *                        offset_x, sprpriority, lifemax, life, defencemul,
 *                        width, stateno, prevstateno, statetime,
 *                        statetype, movetype, ctrl, hitpausetime, alive
 * Calls: ArrayScanFirst, ProjArrayDelete, ArrayScanNext, ArrayClear,
 *        KBClearCommandValidTimes, KBClearCommandLastTimes, KBISetFlip,
 *        PlayerSelfAnim, AnimResetAction, PalFXReset, PlayerResetAI,
 *        ClipboardClear
 * C library: memset
 * Called by: ArcadeWinScreen, ContinueScreenLoop, GameRoundReset,
 *            HelperMake, PlayerNew, SurvivalResultsScreen
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 2 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
void PlayerReset(int *player)

{
  int item;
  int *pi2;
  int array;
  uint32_t u4;
  int i5;
  int *pi6;
  
  pi6 = g;
  if (*player == 0) {
    return;
  }
  pi2 = player;
  if (player[PL_TEAMSIDE] == 1) {
    pi2 = (int *)g[0x73da];
  }
  if (player[PL_TEAMSIDE] == 2) {
    pi2 = (int *)g[0x73db];
  }
  array = *(int *)player[PL_PROJECTILES];
  player[0x57] = 0;
  item = pi6[0x799f];
  player[PL_ATTACKMUL] = BITS_F2I(int, ((float80)player[0x16] * ((float)0.01f)));
  player[0x60] = 0;
  player[0x5e] = 0;
  player[PL_FACING] = 1;
  player[0x65] = 0;
  player[0x66] = 1;
  player[PL_VEL_Z] = 0;
  player[PL_VEL_Y] = 0;
  player[PL_VEL_X] = 0;
  player[PL_OFFSET_Y] = 0;
  player[PL_OFFSET_X] = 0;
  player[0x72] = 0;
  player[PL_SPRPRIORITY] = 0;
  player[0x74] = 0;
  item = (item * player[0x14]) / 100;
  player[0x5f] = player[0x15];
  player[0x5d] = (int)(pi2 + 0x5f);
  player[PL_LIFEMAX] = item;
  player[0x5b] = item;
  player[0x5a] = item;
  player[PL_LIFE] = item;
  player[0x5c] = (int)(pi2 + 0x5e);
  player[PL_DEFENCEMUL] = BITS_F2I(int, (100.0 / (float80)player[0x1c]));
  player[0x77] = 0;
  player[0x78] = 0;
  player[0x79] = 1;
  player[0x80] = 0;
  player[0x7f] = 0;
  player[0x7e] = 0;
  player[PL_WIDTH] = 0;
  player[0x81] = 0;
  player[0x82] = 0;
  *(uint8_t *)(player + 0x83) = 0;
  player[0x85] = 0;
  player[0x86] = 0;
  player[0x84] = 0;
  item = ArrayScanFirst(array);
  while (item != 0) {
    ProjArrayDelete((int *)player[PL_PROJECTILES],*(int *)(array + 0x1c));
    item = ArrayScanNext(array);
  }
  ArrayClear(player[PL_TARGETS]);
  pi6 = player + 0x89;
  for (array = 6; array != 0; array = array + -1) {
    *pi6 = 0;
    pi6 = pi6 + 1;
  }
  player[0x8c] = 0x3f800000;
  player[0x8b] = 0x3f800000;
  memset(player + 0x92,0,0xbc);
  memset(player + 0xc1,0,0x65c);
  player[0x259] = *player + 0x11b4;
  player[0x90] = 0;
  player[0x8f] = 0;
  player[0x91] = 0;
  KBClearCommandValidTimes(player + 0x25a);
  KBClearCommandLastTimes((int)(player + 0x25a));
  KBISetFlip((int)(player + 0x92),0);
  player[0x2fb] = 0;
  player[0x2fc] = -1;
  player[PL_STATENO] = 0;
  player[PL_PREVSTATENO] = 0;
  memset(player + 0x2ff,0,0x200);
  array = 0;
  player[PL_STATETIME] = 0;
  player[PL_STATETYPE] = 1;
  player[PL_MOVETYPE] = 0;
  player[0x382] = 1;
  player[PL_CTRL] = 1;
  player[900] = 0;
  player[0x385] = 0;
  player[0x387] = 0;
  player[PL_HITPAUSETIME] = 0;
  player[0x388] = 0;
  player[PL_ALIVE] = 1;
  player[0x38a] = 0;
  player[0x38b] = 0;
  player[PL_MOVECONTACT] = 0;
  player[PL_MOVEREVERSED] = 0;
  player[0x38f] = 1;
  pi6 = player + PL_VAR;
  for (u4 = player[0x54] & 0x3fffffff; u4 != 0; u4 = u4 - 1) {
    *pi6 = 0;
    pi6 = pi6 + 1;
  }
  pi6 = player + PL_FVAR;
  for (u4 = player[0x55] & 0x3fffffff; u4 != 0; u4 = u4 - 1) {
    *pi6 = 0;
    pi6 = pi6 + 1;
  }
  item = player[0x452];
  player[PL_SYSVAR] = 0;
  player[0x3f5] = 0;
  player[0x3f6] = 0;
  player[0x3f7] = 0;
  player[0x3f8] = 0;
  player[0x3f9] = 0;
  player[0x3fa] = 0;
  player[0x3fb] = 0;
  player[0x3fc] = 0;
  player[0x3fd] = 0;
  pi6 = player + 0x3fe;
  for (i5 = 0x57; i5 != 0; i5 = i5 + -1) {
    *pi6 = 0;
    pi6 = pi6 + 1;
  }
  player[0x452] = item;
  player[0x400] = 0xfff;
  player[0x411] = player[0x1e];
  pi6 = g;
  player[0x3ff] = 0xfff;
  player[0x418] = 0x3eb33333;
  player[0x41e] = -0x39001000;
  player[0x41f] = -0x3f700000;
  pi2 = pi6;
  if ((uint32_t)pi6[0x7395] < 0x80000000) {
    do {
      *(uint32_t *)(item + array * 4) = 0xffffffff;
      array = array + 1;
      pi2 = g;
    } while (array <= pi6[0x7395]);
  }
  memset((void *)player[0x455],0,pi2[0x7395] * 4 + 4);
  memset(player + PL_HITDEF,0,0x1ec);
  memset(player + 0x4d2,0,0x4c);
  player[0x4d4] = 0x3f800000;
  player[0x4d3] = 0x3f800000;
  array = player[0x4e5];
  player[0x4d7] = -32000;
  player[0x4e2] = -1;
  player[0x4e3] = 0x100;
  player[0x4e4] = 0;
  if (array != 0) {
    *(uint32_t *)(array + ARRAY_INDEX) = 0;
    *(uint32_t *)(array + 8) = 0;
    player[0x4e5] = 0;
  }
  player[0x4e6] = 0;
  player[PL_HITCOUNT] = 0;
  player[PL_UNIQHITCOUNT] = 0;
  player[0x4e9] = 0;
  player[0x4ea] = 0;
  player[0x4f0] = 0;
  PlayerSelfAnim(player,0);
  AnimResetAction((int *)player[PL_ANIM]);
  PalFXReset(player + 0x977);
  PlayerResetAI((int)player);
  pi6 = player + 0xd0c;
  for (array = 10; array != 0; array = array + -1) {
    *pi6 = 0;
    pi6 = pi6 + 1;
  }
  player[0xd0a] = 0;
  player[0xd09] = 0;
  player[0xd16] = 0;
  ClipboardClear((uint32_t *)player[0xd17]);
  return;
}

/* PlayerEnableSet @ 0x080b15d0, 348 bytes
 *
 * Enables or disables a player slot: active players are kept in the slot
 * range (first/last) that the update loops scan.
 *
 * Parameters:
 *   player       int
 *   enable       int
 *
 * Globals read: players
 * Globals written: slot_first, slot_last
 * Called by: ArcadeWinScreen, GameFreeChars, GameInputUpdate,
 *            GameLoadAndCreateChars, GameRoundReset, GameUnloadStage,
 *            HelperDestroy, HelperMake, SurvivalResultsScreen
 *
 * Elecbyte file: src/mugen/p-update.c
 */
int PlayerEnableSet(int player,int enable)

{
  bool b1;
  int i2;
  int *pi3;
  
  pi3 = g;
  i2 = g[player + G_PLAYERS];
  if (*(int *)(i2 + 0x158) != enable) {
    if (enable == 0) {
      if (g[0x7398] == 1) {
        g[G_SLOT_FIRST] = 0;
        pi3[0x745a] = -1;
      }
      else if (player == g[G_SLOT_FIRST]) {
        g[G_SLOT_FIRST] = player + 1;
        while( true ) {
          if ((pi3[pi3[0x7459] + 0x73d9] == 0) ||
             (b1 = true, *(int *)(pi3[pi3[0x7459] + 0x73d9] + 0x158) == 0)) {
            b1 = false;
          }
          if (b1) break;
          pi3[0x7459] = pi3[0x7459] + 1;
        }
      }
      else if (player == g[G_SLOT_LAST]) {
        g[G_SLOT_LAST] = player + -1;
        while( true ) {
          if ((pi3[pi3[0x745a] + 0x73d9] == 0) ||
             (b1 = true, *(int *)(pi3[pi3[0x745a] + 0x73d9] + 0x158) == 0)) {
            b1 = false;
          }
          if (b1) break;
          pi3[0x745a] = pi3[0x745a] + -1;
        }
      }
    }
    else if (g[0x7398] == 0) {
      g[G_SLOT_LAST] = player;
      pi3[0x7459] = player;
    }
    else {
      if (player < g[G_SLOT_FIRST]) {
        g[G_SLOT_FIRST] = player;
      }
      if (pi3[0x745a] < player) {
        pi3[0x745a] = player;
        pi3 = g;
      }
    }
    *(int *)(pi3[player + 0x73d9] + 0x158) = enable;
    if (enable == 0) {
      i2 = pi3[0x7398] + -1;
    }
    else {
      i2 = pi3[0x7398] + 1;
    }
    pi3[0x7398] = i2;
  }
  return i2;
}

/* PlayerChangeState @ 0x080b1730, 152 bytes
 *
 * Puts the player into state `stateno` of the state table it is using:
 * records the previous state, resets the state time and marks the statedef
 * to be applied. "changed to invalid state %i (from state %i)" if the state
 * does not exist.
 *
 * Parameters:
 *   player       int
 *   stateno      int
 *
 * Player fields written: stateno, prevstateno, statetime
 * Calls: ArrayAccessGrpItem, VWarn
 * Called by: ArcadeWinScreen, ContinueScreenLoop, GameInputUpdate,
 *            GameRoundReset, GameRoundUpdate, HelperMake, Player1HitP2,
 *            Player1ReverseP2, PlayerCheckProjHit, PlayerDropBoundTargets,
 *            PlayerKBUpdate, PlayerSCtrlApplyElem, PlayerUpdate,
 *            SurvivalResultsScreen
 * Messages:
 *   "changed to invalid state %i (from state %i)\n"
 *
 * Elecbyte file: src/mugen/p-update.c
 */
uint8_t PlayerChangeState(int player,int stateno)

{
  uint32_t u1;
  int item;
  bool b3;
  
  b3 = true;
  if (stateno != 0) {
    if (*(int **)(player + 0xbec) == (int *)0x0) {
      item = ArrayAccessGrpItem(**(int **)(player + 0xbe8),stateno,0);
      if (item == 0) {
        b3 = false;
      }
    }
    else {
      item = ArrayAccessGrpItem(**(int **)(player + 0xbec),stateno,0);
      b3 = item != 0;
    }
  }
  u1 = *(uint32_t *)(player + PLB_STATENO);
  *(int *)(player + PLB_STATENO) = stateno;
  *(uint32_t *)(player + PLB_PREVSTATENO) = u1;
  *(uint32_t *)(player + PLB_STATETIME) = 0;
  if (!b3) {
    VWarn(player,"changed to invalid state %i (from state %i)\n",*(uint32_t *)(player + PLB_STATENO),
          u1);
  }
  return b3;
}

/* PlayerLifeSet @ 0x080b17d0, 242 bytes
 *
 * Sets a player's life, clamped to 0..lifemax (unchanged once the round is
 * over and the KO time has passed). Life is kept at 1 while a "no KO" mode
 * is on, and for helpers that are not allowed to die. When a non-helper
 * player's life reaches 0 during the round, the KO is recorded for the win
 * icons.
 *
 * Parameters:
 *   player       int
 *   life         uint32_t
 *
 * Player fields read: alive, lifemax, ishelper, teamside
 * Player fields written: life
 * Globals read: round_over_hittime
 * Calls: WinIconCheck, WinIconCheckTeam
 * Called by: GameInputUpdate, GameRoundUpdate, PlayerSCtrlApplyElem,
 *            PlayerTakeDamage
 *
 * Elecbyte file: src/mugen/p-update.c
 */
int * PlayerLifeSet(int player,uint32_t life)

{
  uint32_t u1;
  uint32_t u2;
  int *stale_EAX;
  int *stale_EAX_00;
  int *pi3;
  
  if (((g[0x7511] != 3) || (*(int *)(player + PLB_ALIVE) == 0)) ||
     (pi3 = (int *)g[G_ROUND_OVER_HITTIME], g[0x7514] < g[G_ROUND_OVER_HITTIME])) {
    u2 = 0xffffffffU - ((int)life >> 0x1f) & life;
    *(uint32_t *)(player + PLB_LIFE) = u2;
    u1 = *(uint32_t *)(player + PLB_LIFEMAX);
    if ((int)u1 < (int)u2) {
      *(uint32_t *)(player + PLB_LIFE) = u1;
      u2 = u1;
    }
    pi3 = (int *)g[0x730b];
    if ((pi3 != (int *)0x0) && (u2 == 0)) {
      *(uint32_t *)(player + PLB_LIFE) = 1;
      u2 = 1;
    }
    if ((((int)u2 < 1) && (*(int *)(player + PLB_ISHELPER) == 1)) && (*(int *)(player + 0x2628) != 1))
    {
      *(uint32_t *)(player + PLB_LIFE) = 1;
      u2 = 1;
    }
    if ((((int)u2 < 1) && (*(int *)(player + PLB_ISHELPER) == 0)) && (pi3 = g, g[0x7511] == 2)) {
      if (*(int *)(player + 0x1014) == 0) {
        WinIconCheck((*(int *)(player + PLB_TEAMSIDE) == 1) + 1,0,6);
        pi3 = stale_EAX_00;
      }
      else {
        WinIconCheckTeam(*(int *)(player + PLB_TEAMSIDE),*(int *)(*(int *)(player + 0x1014) + 0xc),
                         *(uint32_t *)(player + 0x1048));
        pi3 = stale_EAX;
      }
    }
  }
  return pi3;
}

/* PlayerLifeSetNoIcon @ 0x080b18d0, 115 bytes
 *
 * Sets a player's life clamped to 0..lifemax without the KO bookkeeping.
 *
 * Parameters:
 *   player       int
 *   life         uint32_t
 *
 * Player fields read: alive, lifemax
 * Player fields written: life
 * Globals read: round_over_hittime
 * Called by: PlayerUpdate
 *
 * Elecbyte file: src/mugen/p-update.c
 */
void PlayerLifeSetNoIcon(int player,uint32_t life)

{
  uint32_t u1;
  
  if (((g[0x7511] != 3) || (*(int *)(player + PLB_ALIVE) == 0)) || (g[0x7514] < g[G_ROUND_OVER_HITTIME])) {
    u1 = 0xffffffffU - ((int)life >> 0x1f) & life;
    *(uint32_t *)(player + PLB_LIFE) = u1;
    if (*(int *)(player + PLB_LIFEMAX) < (int)u1) {
      *(int *)(player + PLB_LIFE) = *(int *)(player + PLB_LIFEMAX);
    }
    if ((g[0x730b] != 0) && (*(int *)(player + PLB_LIFE) == 0)) {
      *(uint32_t *)(player + PLB_LIFE) = 1;
    }
  }
  return;
}

/* PlayerPowerSet @ 0x080b1950, 60 bytes
 *
 * Sets a player's power, clamped to 0..powermax.
 *
 * Parameters:
 *   player       int
 *   power        uint32_t
 *
 * Called by: Player1HitP2, Player1ReverseP2, PlayerCheckProjHit,
 *            PlayerGetHit, PlayerGetHitG, PlayerSCtrlApplyElem,
 *            PlayerSCtrlUpdate
 *
 * Elecbyte file: src/mugen/p-update.c
 */
void PlayerPowerSet(int player,uint32_t power)

{
  uint32_t *pu1;
  uint32_t *pu2;
  uint32_t u3;
  
  if (1 < g[0x7511] - 3U) {
    pu1 = *(uint32_t **)(player + 0x170);
    u3 = 0xffffffffU - ((int)power >> 0x1f) & power;
    pu2 = *(uint32_t **)(player + 0x174);
    *pu1 = u3;
    if ((int)*pu2 < (int)u3) {
      *pu1 = *pu2;
    }
  }
  return;
}

/* PlayerChangeAnim @ 0x080b1990, 115 bytes
 *
 * Changes the player's animation to action `action` of the animations it is
 * using. "Changed to invalid action %i" if it does not exist.
 *
 * Parameters:
 *   player       int *
 *   action       int
 *
 * Player fields written: anim
 * Calls: AnimChangeAction, AnimResetAction, VWarn
 * Called by: PlayerSCtrlApplyElem, PlayerSelfAnim
 * Messages:
 *   "Changed to invalid action %i"
 *
 * Elecbyte file: src/mugen/p-update.c
 */
void PlayerChangeAnim(int *player,int action)

{
  int i1;
  uint32_t u2;
  
  if (player[0x4f0] == 0) {
    *(uint32_t *)player[PL_ANIM] = *(uint32_t *)(*player + 0x11cc);
  }
  i1 = AnimChangeAction((int *)player[PL_ANIM],0,action);
  u2 = (uint32_t)(i1 == 0);
  player[0xd16] = u2;
  if (u2 == 0) {
    AnimResetAction((int *)player[PL_ANIM]);
    return;
  }
  VWarn((int)player,"Changed to invalid action %i",action,u2);
  return;
}

/* PlayerChangeAnimElem @ 0x080b1a10, 164 bytes
 *
 * Changes the player's animation and jumps to element `elem`. Warnings for
 * an invalid action or element.
 *
 * Parameters:
 *   player       int *
 *   action       int
 *   elem         int
 *
 * Player fields written: anim
 * Calls: AnimChangeActionElem, AnimChangeAction, VWarn
 * Called by: PlayerSCtrlApplyElem, PlayerSelfAnimElem
 * Messages:
 *   "Changed to invalid action %i"
 *   "Changed to invalid animelem %i within action %i"
 *
 * Elecbyte file: src/mugen/p-update.c
 */
void PlayerChangeAnimElem(int *player,int action,int elem)

{
  int i1;
  
  if (player[0x4f0] == 0) {
    *(uint32_t *)player[PL_ANIM] = *(uint32_t *)(*player + 0x11cc);
  }
  i1 = AnimChangeActionElem((int *)player[PL_ANIM],0,action,elem + -1);
  player[0xd16] = (uint32_t)(i1 == 0);
  if ((i1 == 0) != 0) {
    i1 = AnimChangeAction((int *)player[PL_ANIM],0,action);
    player[0xd16] = (uint32_t)(i1 == 0);
    if ((i1 == 0) != 0) {
      VWarn((int)player,"Changed to invalid action %i");
      return;
    }
    VWarn((int)player,"Changed to invalid animelem %i within action %i",elem,action);
  }
  return;
}

/* PlayerSelfAnim @ 0x080b1ac0, 27 bytes
 *
 * Changes the player's animation to an action of its own character (not the
 * one whose states it is in).
 *
 * Parameters:
 *   player       int *
 *   action       int
 *
 * Player fields written: anim
 * Calls: PlayerChangeAnim
 * Called by: PlayerKBUpdate, PlayerReset, PlayerSCtrlApplyElem,
 *            PlayerSCtrlUpdate
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: Returns nothing (the original left only stale register values).
 */
void PlayerSelfAnim(int *player,int action)

{
  uint32_t stale_EAX;
  
  *(uint32_t *)player[PL_ANIM] = *(uint32_t *)(*player + 0x11cc);
  PlayerChangeAnim(player,action);
  return;
}

/* PlayerSelfAnimElem @ 0x080b1ae0, 29 bytes
 *
 * PlayerSelfAnim with a start element.
 *
 * Parameters:
 *   player       int *
 *   action       int
 *   elem         int
 *
 * Player fields written: anim
 * Calls: PlayerChangeAnimElem
 * Called by: PlayerSCtrlApplyElem
 *
 * Elecbyte file: src/mugen/p-update.c
 */
void PlayerSelfAnimElem(int *player,int action,int elem)

{
  *(uint32_t *)player[PL_ANIM] = *(uint32_t *)(*player + 0x11cc);
  PlayerChangeAnimElem(player,action,elem);
  return;
}

/* PlayerAutoTurn @ 0x080b1b00, 187 bytes
 *
 * Turns a player to face `opponent` when it has control (or the round is
 * over), the opponent is behind it and auto-turning is not disabled. It
 * plays turning animation 5 when standing and 6 when crouching.
 *
 * Parameters:
 *   player       int
 *   opponent     int
 *   arg3         int
 *
 * Player fields read: ctrl, pos_x, statetype, anim
 * Calls: PlayerTurnAround, AnimChangeAction
 * Called by: GameUpdate, PlayerSCtrlApplyElem
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t PlayerAutoTurn(int player,int opponent,int arg3)

{
  float80 f1;
  int *pi2;
  uint32_t u3;
  
  pi2 = *(int **)(player + PLB_CTRL);
  if ((*(int **)(player + PLB_CTRL) != (int *)0x0) || (pi2 = g, 2 < g[0x7511])) {
    f1 = (*(float *)(player + PLB_POS_X) - *(float *)(opponent + 0x19c)) *
            (float80)*(int *)(player + 400);
    pi2 = (int *)CONCAT22((short)((uint32_t)pi2 >> 0x10),
                             (uint16_t)(f1 < 0.0) << 8 | (uint16_t)IS_NAN(f1) << 10 |
                             (uint16_t)(f1 == 0.0) << 0xe);
    if ((f1 >= 0.0 && (f1 == 0.0) == 0) && (*(char *)(player + 0x207) == '\0')) {
      PlayerTurnAround(player);
      pi2 = *(int **)(player + PLB_STATETYPE);
      if (pi2 == (int *)0x1) {
        u3 = AnimChangeAction(*(int **)(player + PLB_ANIM),0,5);
        return u3;
      }
      if (pi2 == (int *)0x2) {
        u3 = AnimChangeAction(*(int **)(player + PLB_ANIM),0,6);
        return u3;
      }
    }
  }
  return pi2;
}

/* PlayerTurnAround @ 0x080b1bc0, 44 bytes
 *
 * Flips the player's facing and tells the key buffer (KBISetFlip) so forward
 * and back swap.
 *
 * Parameters:
 *   player       int
 *
 * Calls: KBISetFlip
 * Called by: GameRoundResetPlayerPos, PlayerAutoTurn, PlayerKBUpdate,
 *            PlayerSCtrlApplyElem, PlayerSCtrlUpdate, PlayerUpdate
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: Returns nothing (the original left only stale register values).
 */
void PlayerTurnAround(int player)

{
  int i1;
  uint32_t stale_EAX;
  
  i1 = *(int *)(player + 400);
  *(int *)(player + 400) = -i1;
  KBISetFlip(player + 0x248,(uint32_t)(-i1 == -1));
  return;
}

/* PlayerUpdate @ 0x080b1bf0, 4338 bytes
 *
 * Per-frame update of one player. It runs the special states (-3, -2, -1)
 * and the current state (repeating while controllers change the state,
 * stopped after a limit: "State machine stuck in loop (stopped after %i
 * loops): %i for %s ... Check your states for infinite ChangeState loops.").
 * Then it applies physics (gravity, friction, velocity), the stage bounds,
 * pending damage, hit and guard timers, binding, and advances the animation.
 *
 * Parameters:
 *   player       int *
 *
 * Player fields read: active, targets, ishelper, movetype, facing, id,
 *                     lifemax, movecontact, targets, movetype, anim,
 *                     statetype
 * Player fields written: hitpausetime, width, offset_y, offset_x, pos_x,
 *                        pos_y, pos_z, hitshakeover, hitfall, defencemul,
 *                        vel_x, vel_z, vel_y, alive, ctrl, hitvel,
 *                        stateno, statetime, life, movereversed
 * Globals read: frame_count, errmsg
 * Calls: PlayerFindTarget, PlayerSCtrlUpdateSpec, PlayerSCtrlUpdate,
 *        ErrorExit, PlayerGetDamagedLife, PlayerLifeSetNoIcon,
 *        PlayerTurnAround, PlayerChangeState, PlayerSndID, SndIDStop,
 *        GameSndPlayIDPos, PlayerDropBoundTargets, ExplodRemoveGetHit,
 *        PlayerLyingDead, StageBound, CameraMoveP, PlayerCalcDraw,
 *        ArrayScanFirst, ArrayScanNext, AnimGetLooptime
 * C library: sprintf
 * Called by: ContinueScreenLoop, GameUpdate
 * Messages:
 *   "State machine stuck in loop (stopped after %i loops): %i for
 *     %s\nCheck your states for infinite ChangeState loops."
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: stack-depth join lost: auStack_1c widened to frame_1c (0x40 bytes of
 *       headroom for pseudo-pushes)
 * Note: 1 exact-text site patches (see SITE_PATCHES in
 *       tools/build_source_tree.py)
 * Note: 7 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 2 temporaries are float80, as the original kept them in x87 registers.
 */
void PlayerUpdate(int *player)

{
  uint16_t u1;
  float80 f2;
  float80 f3;
  uint8_t b4;
  int i5;
  int *item;
  uint32_t stale_var;
  int player2;
  uint32_t stale_ECX;
  uint32_t stale_ECX_00;
  uint32_t u8;
  int stale_ECX_01;
  int stale_ECX_02;
  uint32_t stale_EDX;
  uint32_t stale_EDX_00;
  uint32_t stale_EDX_01;
  uint32_t u9;
  uint8_t *pu10;
  int i12;
  uint16_t entry_FPUControlWord;
  uint8_t frame_1c [0x40 + 20];
  uint8_t *pu11;
  
  if (player[0x57] != 0) {
    return;
  }
  if (0 < player[PL_HITSHAKEOVER]) {
    player[PL_HITPAUSETIME] = 0;
    player[0x387] = 0;
  }
  if (0 < player[0x387]) {
    player[PL_HITPAUSETIME] = player[0x387];
    player[0x387] = 0;
  }
  if (0 < player[PL_HITPAUSETIME]) {
    player[PL_HITPAUSETIME] = player[PL_HITPAUSETIME] + -1;
  }
  player2 = 0x10a0;
  i12 = 7;
  do {
    if (((*(int *)((int)player + player2 + 8) != 0) &&
        (i5 = *(int *)((int)player + player2 + 0x14), i5 != -1)) &&
       (i5 = i5 + -1, *(int *)((int)player + player2 + 0x14) = i5, i5 < 1)) {
      *(uint32_t *)((int)player + player2 + 8) = 0;
    }
    player2 = player2 + 0x14;
    i12 = i12 + -1;
  } while (-1 < i12);
  player2 = player[0x41b];
  if ((player2 != 0) &&
     (((*(int *)(player2 + PLB_ACTIVE) == 0 || (*(int *)(player2 + 0xe2c) != g[G_FRAME_COUNT])) ||
      ((item = PlayerFindTarget(*(int *)(player2 + PLB_TARGETS),(int)player), item == (int *)0x0 ||
       (item[7] == 0)))))) {
    player[0x41b] = 0;
  }
  if (player[PL_HITPAUSETIME] == 0) {
    player[0x79] = 1;
    player[0x7a] = 1;
    player[0x7b] = 1;
    player[0x7c] = 1;
    player[0x4d4] = 0x3f800000;
    player[0x4d3] = 0x3f800000;
    player[0x4e0] = 0;
    player[0x4e2] = -1;
    player[0x4e3] = 0x100;
    player[0x4e4] = 0;
    player[0x7e] = 0;
    player[PL_WIDTH] = 0;
    player[0x80] = 0;
    player[0x7f] = 0;
    player[PL_OFFSET_Y] = 0;
    player[PL_OFFSET_X] = 0;
    player[0x66] = 1;
    if ((player[PL_ISHELPER] == 1) && (player[0x98a] != 1)) {
      player[0x79] = 0;
      player[0x7b] = 0;
      player[0x7a] = 0;
      player[0x7c] = 0;
    }
    player[0x6a] = player[PL_POS_X];
    player[0x6b] = player[PL_POS_Y];
    player[0x6c] = player[PL_POS_Z];
  }
  if ((player[PL_ISHELPER] == 0) || ((player[PL_ISHELPER] == 1 && (player[0x98a] == 1)))) {
    PlayerSCtrlUpdateSpec(player,-3,3);
    PlayerSCtrlUpdateSpec(player,-2,7);
  }
  pu10 = (frame_1c + 0x40);
  if (player[0x8f] != 0) goto L_080b1e2d;
  pu11 = frame_1c + 0x40 - 0x10;  /* frame offset -0x2c */
  PlayerSCtrlUpdateSpec(player,-1,3);
  do {
    pu10 = pu11 + 0x10;
L_080b1e2d:
    player2 = 0;
    do {
      *(int **)(pu10 + -0x10) = player;
      *(uint32_t *)(pu10 + -0x14) = 0x80b1e39;
      i5 = PlayerSCtrlUpdate(*(int **)(pu10 + -0x10));
      i12 = player2;
      if (i5 == 0) break;
      i12 = player2 + 1;
      if (0x9c4 < player2) {
        *(int *)(pu10 + -0x10) = *player;
        *(int *)(pu10 + -0x14) = player[PL_STATENO];
        *(uint32_t *)(pu10 + -0x18) = 0x9c4;
        *(char **)(pu10 + -0x1c) =
             "State machine stuck in loop (stopped after %i loops): %i for %s\nCheck your states for infinite ChangeState loops."
        ;
        *(int **)(pu10 + -0x20) = g + G_ERRMSG;
        *(uint32_t *)(pu10 + -0x24) = 0x80b1e71;
        sprintf(*(char **)(pu10 + -0x20),*(char **)(pu10 + -0x1c),*(int *)(pu10 + -0x18),*(int *)(pu10 + -0x14),*(char **)(pu10 + -0x10));
        *(uint32_t *)(pu10 + -4) = 0x80b1e79;
        ErrorExit();
      }
      player2 = i12;
    } while (keyflag[1] == 0);
    player2 = player[PL_HITPAUSETIME];
    if (0 < player2) goto L_080b2b83;
    if (player[PL_MOVETYPE] == 2) {
      f2 = BITS_I2F(player[0x413]);
      if (f2 != 0.0) {
        player[0x413] = 0;
        player[PL_POS_X] = BITS_F2I(int, (BITS_I2F(player[PL_POS_X]) + f2));
      }
      f2 = BITS_I2F(player[0x414]);
      if (f2 != 0.0) {
        player[0x414] = 0;
        player[PL_POS_Y] = BITS_F2I(int, (BITS_I2F(player[PL_POS_Y]) + f2));
      }
      f2 = BITS_I2F(player[0x415]);
      if (f2 != 0.0) {
        player[0x415] = 0;
        player[PL_POS_Z] = BITS_F2I(int, (BITS_I2F(player[PL_POS_Z]) + f2));
      }
      player[PL_HITSHAKEOVER] = player[PL_HITSHAKEOVER] - 1U & 0xffffffffU - ((int)(player[PL_HITSHAKEOVER] - 1U) >> 0x1f);
      if (player[0x40a] != 0) {
        *(int **)(pu10 + -0x10) = player;
        *(uint32_t *)(pu10 + -0x14) = 0x80b1f50;
        player2 = PlayerGetDamagedLife(*(int *)(pu10 + -0x10));
        i12 = *(int *)(pu10 + -0xc);
        *(int *)(pu10 + -0xc) = player2;
        *(int **)(pu10 + -0x10) = player;
        *(uint32_t *)(pu10 + -0x14) = 0x80b1f59;
        PlayerLifeSetNoIcon(*(int *)(pu10 + -0x10),*(uint32_t *)(pu10 + -0xc));
        player[0x40a] = 0;
      }
    }
    else {
      player[0x40a] = 0;
      player[0x419] = 0;
      player[0x405] = 0;
      player[0x412] = 0;
      player[PL_HITFALL] = 0;
      player[0x411] = player[0x1e];
      player[0x40c] = 0;
      player[PL_HITSHAKEOVER] = 0;
      player[0x425] = 0;
      player[0x423] = 1;
      player[PL_DEFENCEMUL] = BITS_F2I(int, (100.0 / (float80)player[0x1c]));
    }
    if (player[0x65] != 0) {
      if (player[PL_FACING] != player[0x65]) {
        *(int **)(pu10 + -0x10) = player;
        *(uint32_t *)(pu10 + -0x14) = 0x80b1ff5;
        PlayerTurnAround(*(int *)(pu10 + -0x10));
      }
      player[0x65] = 0;
    }
    if ((char)player[0x83] != '\0') {
      player[0x66] = 0;
    }
    player2 = player[PL_STATENO];
    if (player2 == 0x98) {
L_080b234b:
      player[900] = 1;
L_080b2355:
      if (player[0x388] < 1) {
        player[PL_POS_X] = BITS_F2I(int, (BITS_I2F(player[PL_POS_X]) + BITS_I2F(player[PL_VEL_X])));
        player[PL_POS_Y] = BITS_F2I(int, (BITS_I2F(player[PL_POS_Y]) + BITS_I2F(player[PL_VEL_Y])));
        player[PL_POS_Z] = BITS_F2I(int, (BITS_I2F(player[PL_POS_Z]) + BITS_I2F(player[PL_VEL_Z])));
      }
      else {
        player[0x388] = player[0x388] + -1;
      }
      if ((player[0x8e] != 0) && (g[0x74f3] != 1)) {
        f2 = BITS_I2F(player[0x89]) * BITS_I2F(player[0x8b]);
        player[PL_POS_X] = BITS_F2I(int, (BITS_I2F(player[PL_POS_X]) + BITS_I2F(player[0x89])));
        player[0x89] = BITS_F2I(int, f2);
        player[PL_POS_Y] = BITS_F2I(int, (BITS_I2F(player[PL_POS_Y]) + BITS_I2F(player[0x8a])));
        player[0x8a] = BITS_F2I(int, (BITS_I2F(player[0x8a]) * BITS_I2F(player[0x8c])));
        if (f2 < 0.0) {
          f2 = f2 * -1.0;
        }
        if (f2 < BITS_I2F(player[0x8d])) {
          player[0x8e] = 0;
        }
        player2 = player[0x8e];
        if (0 < player2) {
          player2 = player2 + -1;
          player[0x8e] = player2;
        }
        if (player2 == 0) {
          player[0x8a] = 0;
          player[0x89] = 0;
        }
      }
      player2 = player[0x382];
      if (player2 == 1) {
        f2 = BITS_I2F(player[PL_VEL_X]);
        f3 = BITS_I2F(player[0x4d]);
        player[PL_VEL_X] = BITS_F2I(int, (f2 * f3));
        *(uint16_t *)(pu10 + 0x10) = entry_FPUControlWord;
        pu10[0x11] = 0xc;
        *(uint32_t *)(pu10 + 0x10) = *(uint32_t *)(pu10 + 0x10);
        *(int *)(pu10 + 0xc) = (int)X87_FIST32(f2 * f3);
        u1 = *(uint16_t *)(pu10 + 0x10);
        if (*(int *)(pu10 + 0xc) == 0) {
          player[PL_VEL_X] = 0;
        }
        f2 = BITS_I2F(player[PL_VEL_Z]);
        f3 = BITS_I2F(player[0x4d]);
        player[PL_VEL_Z] = BITS_F2I(int, (f2 * f3));
        *(uint16_t *)(pu10 + 0x10) = u1;
        pu10[0x11] = 0xc;
        *(uint32_t *)(pu10 + 0x10) = *(uint32_t *)(pu10 + 0x10);
        *(int *)(pu10 + 0xc) = (int)X87_FIST32(f2 * f3);
        entry_FPUControlWord = *(uint16_t *)(pu10 + 0x10);
        if (*(int *)(pu10 + 0xc) == 0) {
          player[PL_VEL_Z] = 0;
        }
        player2 = player[0x382];
      }
      if (player2 == 2) {
        player2 = player[0x382];
        player[PL_VEL_X] = BITS_F2I(int, (BITS_I2F(player[PL_VEL_X]) * BITS_I2F(player[0x4e])));
      }
      if (player2 == 3) {
        f2 = BITS_I2F(player[PL_VEL_Y]);
        player[PL_VEL_Y] = BITS_F2I(int, (f2 + BITS_I2F(player[0x4c])));
        if (((player[PL_STATENO] != 0x69) && (0.0 < f2 + BITS_I2F(player[0x4c]))) &&
           (0.0 <= BITS_I2F(player[PL_POS_Y]))) {
          *(int *)(pu10 + -4) = i12;
          *(int *)(pu10 + -8) = i12;
          *(uint32_t *)(pu10 + -0xc) = 0x34;
          *(int **)(pu10 + -0x10) = player;
          *(uint32_t *)(pu10 + -0x14) = 0x80b2568;
          PlayerChangeState(*(int *)(pu10 + -0x10),*(int *)(pu10 + -0xc));
          player[PL_OFFSET_X] = 0;
          goto L_080b1e2d;
        }
      }
      player2 = player[PL_LIFE];
      if (player2 < 1) {
        i12 = 0;
        if (player[PL_ALIVE] != 0) {
          if (nokoflag_0 != 0) {
            nokoflag_0 = (int)*(char *)((int)g + 0x1d38e);
          }
          item = g;
          if ((*(char *)((int)g + 0x1d38f) == '\0') && (nokoflag_0 == 0)) {
            *(uint32_t *)(pu10 + -0x1c) = 0;
            *(int **)(pu10 + -0x20) = player;
            *(uint32_t *)(pu10 + -0x24) = 0x80b25d6;
            player2 = PlayerSndID(*(int *)(pu10 + -0x20),*(int *)(pu10 + -0x1c));
            *(int *)(pu10 + -0x10) = player2;
            *(uint32_t *)(pu10 + -0x14) = 0x80b25df;
            SndIDStop(*(int *)(pu10 + -0x10));
            *(uint32_t *)(pu10 + -0xc) = *(uint32_t *)(*player + 0x11d0);
            *(uint32_t *)(pu10 + -0x10) = 0;
            *(uint32_t *)(pu10 + -0x14) = 0xb;
            *(uint32_t *)(pu10 + -0x18) = *(uint32_t *)(*player + 0x11d4);
            f2 = BITS_I2F(player[0x4d5]);
            *(uint16_t *)(pu10 + 0x10) = entry_FPUControlWord;
            pu10[0x11] = 0xc;
            *(uint32_t *)(pu10 + 0x10) = *(uint32_t *)(pu10 + 0x10);
            *(int *)(pu10 + 0xc) = (int)X87_FIST32(f2);
            entry_FPUControlWord = *(uint16_t *)(pu10 + 0x10);
            *(uint32_t *)(pu10 + -0x1c) = *(uint32_t *)(pu10 + 0xc);
            *(uint32_t *)(pu10 + -0x20) = 0xffffffff;
            *(uint32_t *)(pu10 + -0x24) = 0x80b2626;
            item = (int *)GameSndPlayIDPos(*(int *)(pu10 + -0x20),*(int *)(pu10 + -0x1c),
                                             *(int **)(pu10 + -0x18),*(int *)(pu10 + -0x14),
                                             *(int *)(pu10 + -0x10),*(int *)(pu10 + -0xc));
            player2 = stale_ECX_01;
          }
          if (nokoflag_0 == 0) {
            nokoflag_0 = 1;
            player[PL_ALIVE] = 0;
            player[0x38a] = 0;
            player[PL_CTRL] = 0;
            if (player[PL_MOVETYPE] != 2) {
              *(uint32_t *)(pu10 + -4) = 0;
              *(uint32_t *)(pu10 + -8) = 0;
              *(uint32_t *)(pu10 + -0xc) = 0x13a6;
              *(int **)(pu10 + -0x10) = player;
              *(uint32_t *)(pu10 + -0x14) = 0x80b2675;
              b4 = PlayerChangeState(*(int *)(pu10 + -0x10),*(int *)(pu10 + -0xc));
              item = (int *)ZEXT8(b4);
              player[PL_HITVEL] = -0x3fcccccd;
              player[0x417] = -0x3fa00000;
              player[PL_HITFALL] = 1;
            }
            *(int **)(pu10 + -4) = item;
            *(int **)(pu10 + -8) = item;
            *(uint32_t *)(pu10 + -0xc) = 0;
            *(int **)(pu10 + -0x10) = player;
            *(uint32_t *)(pu10 + -0x14) = 0x80b26a0;
            PlayerDropBoundTargets(*(int *)(pu10 + -0x10),*(int **)(pu10 + -0xc));
            *(int *)(pu10 + -0xc) = player[PL_ID];
            *(int *)(pu10 + -0x10) = g[0x52be];
            *(uint32_t *)(pu10 + -0x14) = 0x80b26b7;
            ExplodRemoveGetHit(*(uint32_t **)(pu10 + -0x10),*(int *)(pu10 + -0xc));
            player2 = stale_ECX_02;
          }
          goto L_080b26ba;
        }
      }
      else {
L_080b26ba:
        i12 = player[PL_ALIVE];
      }
      if (i12 == 0) {
        i12 = player[0x38a] + 1;
        player[0x38a] = i12;
        if (player[0x51] != 0) {
          if ((i12 == 0x14) && (*(char *)((int)g + 0x1d38f) == '\0')) {
            *(int *)(pu10 + -4) = player2;
            *(int *)(pu10 + -8) = player2;
            *(int *)(pu10 + -0xc) = *(int *)(*player + 0x11d0) + -0x3c;
            *(uint32_t *)(pu10 + -0x10) = 0;
            *(uint32_t *)(pu10 + -0x14) = 0xb;
            *(uint32_t *)(pu10 + -0x18) = *(uint32_t *)(*player + 0x11d4);
            f2 = BITS_I2F(player[0x4d5]);
            *(uint16_t *)(pu10 + 0x10) = entry_FPUControlWord;
            pu10[0x11] = 0xc;
            *(uint32_t *)(pu10 + 0x10) = *(uint32_t *)(pu10 + 0x10);
            *(int *)(pu10 + 0xc) = (int)X87_FIST32(f2);
            entry_FPUControlWord = *(uint16_t *)(pu10 + 0x10);
            *(uint32_t *)(pu10 + -0x1c) = *(uint32_t *)(pu10 + 0xc);
            *(uint32_t *)(pu10 + -0x20) = 0xffffffff;
            *(uint32_t *)(pu10 + -0x24) = 0x80b2741;
            i12 = GameSndPlayIDPos(*(int *)(pu10 + -0x20),*(int *)(pu10 + -0x1c),
                                      *(int **)(pu10 + -0x18),*(int *)(pu10 + -0x14),
                                      *(int *)(pu10 + -0x10),*(int *)(pu10 + -0xc));
          }
          if ((player[0x38a] == 0x32) && (*(char *)((int)g + 0x1d38f) == '\0')) {
            *(int *)(pu10 + -4) = i12;
            *(int *)(pu10 + -8) = i12;
            *(int *)(pu10 + -0xc) = *(int *)(*player + 0x11d0) + -0x78;
            *(uint32_t *)(pu10 + -0x10) = 0;
            *(uint32_t *)(pu10 + -0x14) = 0xb;
            *(uint32_t *)(pu10 + -0x18) = *(uint32_t *)(*player + 0x11d4);
            f2 = BITS_I2F(player[0x4d5]);
            *(uint16_t *)(pu10 + 0x10) = entry_FPUControlWord;
            pu10[0x11] = 0xc;
            *(uint32_t *)(pu10 + 0x10) = *(uint32_t *)(pu10 + 0x10);
            *(int *)(pu10 + 0xc) = (int)X87_FIST32(f2);
            *(uint32_t *)(pu10 + -0x1c) = *(uint32_t *)(pu10 + 0xc);
            *(uint32_t *)(pu10 + -0x20) = 0xffffffff;
            *(uint32_t *)(pu10 + -0x24) = 0x80b27a6;
            GameSndPlayIDPos(*(int *)(pu10 + -0x20),*(int *)(pu10 + -0x1c),
                             *(int **)(pu10 + -0x18),*(int *)(pu10 + -0x14),
                             *(int *)(pu10 + -0x10),*(int *)(pu10 + -0xc));
          }
        }
        if (player == (int *)g[0x73da]) {
          if (g[0x73dc] == 0) {
            item = (int *)0x0;
            goto L_080b27cb;
          }
L_080b27fe:
          player[0x7c] = 0;
        }
        else {
          item = (int *)g[0x73dc];
L_080b27cb:
          if ((player == item) && ((int *)g[0x73da] != (int *)0x0)) goto L_080b27fe;
          if (player == (int *)g[0x73db]) {
            if (g[0x73dd] != 0) goto L_080b27fe;
            item = (int *)0x0;
          }
          else {
            item = (int *)g[0x73dd];
          }
          if ((player == item) && ((int *)g[0x73db] != (int *)0x0)) goto L_080b27fe;
        }
        *(int **)(pu10 + -0x10) = player;
        *(uint32_t *)(pu10 + -0x14) = 0x80b2811;
        player2 = PlayerLyingDead(*(int *)(pu10 + -0x10));
        if (9 < player2) {
          if (player == (int *)g[0x73da]) {
            if (g[0x73dc] == 0) {
              item = (int *)0x0;
              goto L_080b283b;
            }
          }
          else {
            item = (int *)g[0x73dc];
L_080b283b:
            if ((player != item) || ((int *)g[0x73da] == (int *)0x0)) {
              if (player == (int *)g[0x73db]) {
                if (g[0x73dd] != 0) goto L_080b286e;
                item = (int *)0x0;
              }
              else {
                item = (int *)g[0x73dd];
              }
              if ((player != item) || ((int *)g[0x73db] == (int *)0x0)) goto L_080b288c;
            }
          }
L_080b286e:
          player[0x79] = 0;
          player[0x7b] = 0;
          player[0x7a] = 0;
        }
      }
L_080b288c:
      if (player[0x401] == 0) {
        player[0x3ff] = 0xfff;
      }
      if (player[0x402] == 0) {
        player[0x400] = 0xfff;
      }
      if (0 < player[0x401]) {
        player[0x401] = player[0x401] + -1;
      }
      if (0 < player[0x402]) {
        player[0x402] = player[0x402] + -1;
      }
      if (g[0x731d] == 1) {
        *(int **)(pu10 + -0x10) = player;
        *(uint32_t *)(pu10 + -0x14) = 0x80b28f1;
        player2 = PlayerLyingDead(*(int *)(pu10 + -0x10));
        if (0x3b < player2) {
          *(int **)(pu10 + -0x10) = player;
          *(uint32_t *)(pu10 + -0x14) = 0x80b2902;
          player2 = PlayerLyingDead(*(int *)(pu10 + -0x10));
          if (player2 < 0x5a) {
            player[0x66] = player[PL_STATETIME] >> 2 & 1;
          }
        }
        *(int **)(pu10 + -0x10) = player;
        *(uint32_t *)(pu10 + -0x14) = 0x80b2925;
        player2 = PlayerLyingDead(*(int *)(pu10 + -0x10));
        if (0x59 < player2) {
          *(int **)(pu10 + -0x10) = player;
          *(uint32_t *)(pu10 + -0x14) = 0x80b2936;
          player2 = PlayerLyingDead(*(int *)(pu10 + -0x10));
          if (player2 < 0x78) {
            player[0x66] = player[PL_STATETIME] >> 1 & 1;
          }
        }
        *(int **)(pu10 + -0x10) = player;
        *(uint32_t *)(pu10 + -0x14) = 0x80b2958;
        player2 = PlayerLyingDead(*(int *)(pu10 + -0x10));
        if (0x77 < player2) {
          *(int **)(pu10 + -0x10) = player;
          *(uint32_t *)(pu10 + -0x14) = 0x80b2969;
          player2 = PlayerLyingDead(*(int *)(pu10 + -0x10));
          if (player2 < 0x96) {
            player[0x66] = (uint32_t)((player[PL_STATETIME] & 3U) == 1);
          }
        }
        *(int **)(pu10 + -0x10) = player;
        *(uint32_t *)(pu10 + -0x14) = 0x80b2991;
        player2 = PlayerLyingDead(*(int *)(pu10 + -0x10));
        if (0x95 < player2) {
          *(int **)(pu10 + -0x10) = player;
          *(uint32_t *)(pu10 + -0x14) = 0x80b29a4;
          player2 = PlayerLyingDead(*(int *)(pu10 + -0x10));
          if (player2 < 0xb4) {
            player[0x66] = (uint32_t)((player[PL_STATETIME] & 7U) == 1);
          }
        }
        *(int **)(pu10 + -0x10) = player;
        *(uint32_t *)(pu10 + -0x14) = 0x80b29cc;
        player2 = PlayerLyingDead(*(int *)(pu10 + -0x10));
        if (0xb3 < player2) {
          player[0x66] = 0;
        }
      }
      if (player[PL_MOVETYPE] == 0) {
        player[0x385] = player[0x385] + 1;
      }
      else {
        player[0x385] = 0;
      }
      if (g[0x33ae] == 3) {
        *(int **)(pu10 + -0x10) = player;
        *(uint32_t *)(pu10 + -0x14) = 0x80b2a25;
        player2 = PlayerLyingDead(*(int *)(pu10 + -0x10));
        if (0x59 < player2) {
          player[PL_STATENO] = 0x1400;
          player[PL_STATETIME] = -1;
          player[PL_LIFE] = player[PL_LIFEMAX];
          player[PL_ALIVE] = 1;
          player[0x404] = 0;
          player[0x403] = 0;
        }
        player2 = player[0x385];
        if (0x1e < player2) {
          if (*(int *)player[0x5c] < *(int *)player[0x5d]) {
            *(int *)player[0x5c] = *(int *)player[0x5d];
            player2 = player[0x385];
          }
        }
        if ((0x3c < player2) && (player[PL_LIFE] < player[PL_LIFEMAX])) {
          player[PL_LIFE] = player[PL_LIFEMAX];
        }
      }
      player[PL_STATETIME] = player[PL_STATETIME] + 1;
      if (player[PL_MOVECONTACT] != 0) {
        player[PL_MOVEREVERSED] = player[PL_MOVEREVERSED] + 1;
      }
      if ((-1 < player[PL_HITOVER]) && (player[PL_HITSHAKEOVER] == 0)) {
        player[PL_HITOVER] = player[PL_HITOVER] + -1;
      }
      if (player[PL_HITFALL] == 0) {
        player2 = player[PL_MOVETYPE];
      }
      else {
        player2 = player[PL_MOVETYPE];
        if (player2 == 2) {
          player[0x421] = player[0x421] + 1;
        }
      }
      if (player2 == 2) {
        player[0x454] = 0;
      }
      else {
        player[0x454] = player[0x454] + 1;
      }
      player2 = g[0x74f3];
      if (player2 == -1) {
        if (player[PL_MOVETYPE] == 2) {
          player[0x78] = 0;
          player[0x77] = 0;
        }
      }
      else if (0 < player[player2 + 0x77]) {
        player[player2 + 0x77] = player[player2 + 0x77] + -1;
      }
      player2 = player[PL_HITPAUSETIME];
L_080b2b83:
      if (player2 == 0) {
        player[PL_OFFSET_X] = player[PL_OFFSET_X] + player[PL_FACING] * player[0x52];
        player[PL_OFFSET_Y] = player[PL_OFFSET_Y] + player[0x53];
      }
      *(int **)(pu10 + -0x10) = player;
      *(uint32_t *)(pu10 + -0x14) = 0x80b2bc1;
      StageBound(*(int *)(pu10 + -0x10));
      *(uint32_t *)(pu10 + -0x14) = 0x80b2bc6;
      CameraMoveP();
      *(int **)(pu10 + -0x10) = player;
      *(uint32_t *)(pu10 + -0x14) = 0x80b2bce;
      PlayerCalcDraw(*(int *)(pu10 + -0x10));
      player[0x86] = player[0x86] + 1;
      *(int *)(pu10 + -0x10) = player[PL_TARGETS];
      *(uint32_t *)(pu10 + -0x14) = 0x80b2be8;
      item = (int *)ArrayScanFirst(*(int *)(pu10 + -0x10));
      while (item != (int *)0x0) {
        player2 = *item;
        item[7] = item[6];
        if ((*(int *)(player2 + PLB_MOVETYPE) == 2) && (item[6] != 0)) {
          *(int *)(pu10 + -4) = player[PL_FACING] * item[3];
          i12 = *(int *)(pu10 + -4);
          *(int **)(player2 + 0x106c) = player;
          *(float *)(player2 + PLB_POS_X) = (float80)i12 + BITS_I2F(player[PL_POS_X]);
          *(float *)(player2 + PLB_POS_Y) = (float80)item[4] + BITS_I2F(player[PL_POS_Y]);
          *(float *)(player2 + PLB_POS_Z) = (float80)item[5] + BITS_I2F(player[PL_POS_Z]);
          *(int *)(player2 + PLB_VEL_X) = player[PL_VEL_X];
          *(int *)(player2 + PLB_VEL_Y) = player[PL_VEL_Y];
          *(int *)(player2 + PLB_VEL_Z) = player[PL_VEL_Z];
          *(uint32_t *)(player2 + 0x1054) = 0;
          *(uint32_t *)(player2 + 0x1050) = 0;
          *(uint32_t *)(player2 + 0x104c) = 0;
          if (*(int *)(player2 + 0xe20) < 1) {
            *(uint32_t *)(player2 + 0xe20) = 1;
          }
          if (0 < item[6]) {
            item[6] = item[6] + -1;
          }
        }
        *(int *)(pu10 + -0x10) = player[PL_TARGETS];
        *(uint32_t *)(pu10 + -0x14) = 0x80b2cbe;
        item = (int *)ArrayScanNext(*(int *)(pu10 + -0x10));
      }
      player[0x38b] = g[G_FRAME_COUNT];
      return;
    }
    if (player2 < 0x99) {
      if (player2 == 0x83) {
L_080b2150:
        player2 = player[0x1c];
        player[900] = 1;
L_080b233d:
        player[PL_DEFENCEMUL] = BITS_F2I(int, (100.0 / (float80)player2));
        goto L_080b2355;
      }
      if (player2 < 0x84) {
        if (player2 == 0x78) goto L_080b234b;
        if (player2 < 0x79) {
          if ((player2 == 0x28) && (player[PL_STATETIME] == 0)) {
            player[0x74] = player[0x44];
          }
        }
        else if (player2 == 0x82) goto L_080b2150;
        goto L_080b2355;
      }
      if (player2 != 0x8c) {
        if (player2 < 0x8d) {
          if (player2 == 0x84) goto L_080b2150;
        }
        else if ((player2 == 0x96) || (player2 == 0x97)) goto L_080b234b;
        goto L_080b2355;
      }
      player[900] = 1;
      player[PL_DEFENCEMUL] = BITS_F2I(int, (100.0 / (float80)player[0x1c]));
      *(int *)(pu10 + -0x10) = player[PL_ANIM];
      *(uint32_t *)(pu10 + -0x14) = 0x80b218a;
      player2 = AnimGetLooptime(*(uint32_t **)(pu10 + -0x10));
      if (player[PL_STATETIME] < player2) goto L_080b2355;
      player2 = player[PL_STATETYPE];
      u8 = stale_ECX;
      u9 = stale_EDX;
      if (player2 == 1) {
        *(int *)(pu10 + -4) = i12;
        *(int *)(pu10 + -8) = i12;
        *(uint32_t *)(pu10 + -0xc) = 0;
        *(int **)(pu10 + -0x10) = player;
        *(uint32_t *)(pu10 + -0x14) = 0x80b21ae;
        PlayerChangeState(*(int *)(pu10 + -0x10),*(int *)(pu10 + -0xc));
        player2 = player[PL_STATETYPE];
        u8 = stale_ECX_00;
        u9 = stale_EDX_00;
      }
      if (player2 == 2) {
        *(uint32_t *)(pu10 + -4) = u8;
        *(uint32_t *)(pu10 + -8) = u8;
        *(uint32_t *)(pu10 + -0xc) = 0xb;
        *(int **)(pu10 + -0x10) = player;
        *(uint32_t *)(pu10 + -0x14) = 0x80b21c6;
        PlayerChangeState(*(int *)(pu10 + -0x10),*(int *)(pu10 + -0xc));
        player2 = player[PL_STATETYPE];
        u9 = stale_EDX_01;
      }
      if (player2 == 3) {
        *(uint32_t *)(pu10 + -4) = u9;
        *(uint32_t *)(pu10 + -8) = u9;
        *(uint32_t *)(pu10 + -0xc) = 0x33;
        *(int **)(pu10 + -0x10) = player;
        *(uint32_t *)(pu10 + -0x14) = 0x80b21de;
        PlayerChangeState(*(int *)(pu10 + -0x10),*(int *)(pu10 + -0xc));
      }
      player[0x419] = 0;
      player[0x405] = 0;
      player[0x412] = 0;
      goto L_080b1e2d;
    }
    if (player2 == 0x13ec) {
      if (player[PL_STATETIME] == 0) {
        if (0 < player[0x40c]) {
          player[0x411] = player[0x411] >> 1;
        }
        i12 = player[0x40c] + 1;
        player[0x40c] = i12;
        player[PL_DEFENCEMUL] = BITS_F2I(int, (BITS_I2F(player[PL_DEFENCEMUL]) * BITS_I2F(player[0x1d])));
      }
      if (player[0x411] < 0xb) {
        player[0x3ff] = 0;
        player[0x401] = -1;
      }
      goto L_080b2355;
    }
    if (player2 < 0x13ed) {
      if (((player2 == 0x9a) || (player2 < 0x9a)) || (player2 == 0x9b)) goto L_080b234b;
      if ((player2 == 0x13ce) && (player[PL_STATETIME] == 0)) {
        i12 = player[0x40c] + 1;
        player[0x40c] = i12;
        player[PL_DEFENCEMUL] = BITS_F2I(int, (BITS_I2F(player[PL_DEFENCEMUL]) * BITS_I2F(player[0x1d])));
      }
      goto L_080b2355;
    }
    if (player2 == 0x1400) {
      i12 = player[PL_STATETIME];
      if (i12 == 0) {
        player[PL_DEFENCEMUL] = BITS_F2I(int, (100.0 / (float80)player[0x1c]));
      }
      player[0x419] = 0;
      player[0x405] = 0;
      player[0x412] = 0;
      goto L_080b2355;
    }
    if (0x1400 < player2) {
      if (player2 == 0x1450) {
        player2 = player[PL_STATETIME];
      }
      else {
        if (player2 != 0x145a) goto L_080b2355;
        player2 = player[PL_STATETIME];
      }
      if (player2 == 0) {
        player2 = player[0x1c];
        goto L_080b233d;
      }
      goto L_080b2355;
    }
    if (player2 != 0x13f6) goto L_080b2355;
    player2 = player[0x411];
    if (((0 < player2) || (player[PL_ALIVE] == 0)) || (player[PL_STATETIME] < 1)) {
      if (0 < player2) {
        player[0x411] = player2 + -1;
      }
      goto L_080b2355;
    }
    player2 = player[0x1e];
    player[0x411] = player2;
    *(int *)(pu10 + -4) = player2;
    *(int *)(pu10 + -8) = player2;
    *(uint32_t *)(pu10 + -0xc) = 0x1400;
    pu11 = pu10 + -0x10;
    *(int **)(pu10 + -0x10) = player;
    *(uint32_t *)(pu10 + -0x14) = 0x80b22cb;
    PlayerChangeState(*(int *)(pu10 + -0x10),*(int *)(pu10 + -0xc));
  } while( true );
}

/* PlayerUpdateBindTo @ 0x080b2cf0, 185 bytes
 *
 * Applies a player's binding (BindToTarget, TargetBind...): moves it to the
 * bound player's position plus the offset, then re-applies the bounds and
 * camera.
 *
 * Parameters:
 *   player       int
 *
 * Player fields written: pos_x, pos_y, pos_z
 * Calls: StageBound, CameraMoveP, PlayerCalcDraw
 * Called by: GameUpdate
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
uint32_t PlayerUpdateBindTo(int player)

{
  uint32_t u1;
  uint32_t entry_ECX;
  int i2;
  
  i2 = *(int *)(player + 400);
  if (*(int *)(player + 0x3430) != 0) {
    if (*(int **)(player + 0x3440) != (int *)0x0) {
      i2 = **(int **)(player + 0x3440);
      if (*(int *)(player + 0x3444) != 0) {
        *(int *)(player + 400) = i2 * *(int *)(player + 0x3444);
      }
    }
    if (*(float **)(player + 0x3434) != (float *)0x0) {
      *(float *)(player + PLB_POS_X) =
           (float80)i2 * *(float *)(player + 0x3448) + **(float **)(player + 0x3434);
    }
    if (*(float **)(player + 0x3438) != (float *)0x0) {
      *(float *)(player + PLB_POS_Y) = **(float **)(player + 0x3438) + *(float *)(player + 0x344c);
    }
    if (*(float **)(player + 0x343c) != (float *)0x0) {
      *(float *)(player + PLB_POS_Z) = **(float **)(player + 0x343c) + *(float *)(player + 0x3450);
    }
    if (0 < *(int *)(player + 0x3430)) {
      *(int *)(player + 0x3430) = *(int *)(player + 0x3430) + -1;
    }
    StageBound(player);
    CameraMoveP();
    u1 = PlayerCalcDraw(player);
    return u1;
  }
  return entry_ECX;
}

/* ScreenBound @ 0x080b2db0, 328 bytes
 *
 * Keeps a player inside the visible screen (unless ScreenBound is off for
 * it), using its widths.
 *
 * Parameters:
 *   player       int
 *
 * Player fields read: alive, statetype
 * Player fields written: pos_x
 * Globals read: bound_screenleft, bound_screenright
 * Calls: PlayerGetWidth
 * Called by: PlayerCalcDraw, PlayerPushCheck
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void ScreenBound(int player)

{
  int i1;
  float80 f2;
  int width;
  int width2;
  
  if ((g[0x731d] != 1) || (*(int *)(player + PLB_ALIVE) != 0)) {
    width = PlayerGetWidth(player,3,4);
    width2 = PlayerGetWidth(player,4,4);
    if (*(int *)(player + PLB_STATETYPE) == 3) {
      width2 = width2 + 1;
      width = width + 1;
    }
    if (*(int *)(player + PLB_STATETYPE) == 4) {
      width2 = width2 + 2;
      width = width + 2;
    }
    i1 = (int)X87_FIST32((float)(g[G_BOUND_SCREENLEFT] + -0xa0) / *(float *)(player + 0x1348) + (float)g[0x7311]
                       + 160.0);
    *(int *)(player + 0x1d4) = i1;
    f2 = (float)(i1 + width);
    if (*(float *)(player + PLB_POS_X) < f2) {
      *(float *)(player + PLB_POS_X) = f2;
    }
    width = (int)X87_FIST32((float)(0xa0 - g[G_BOUND_SCREENRIGHT]) / *(float *)(player + 0x1348) + (float)g[0x7311] +
                       160.0);
    *(int *)(player + 0x1d8) = width;
    f2 = (float)(width - width2);
    if (f2 < *(float *)(player + PLB_POS_X)) {
      *(float *)(player + PLB_POS_X) = f2;
    }
  }
  return;
}

/* StageBound @ 0x080b2f00, 157 bytes
 *
 * Keeps a player inside the stage's left and right bounds.
 *
 * Parameters:
 *   player       int
 *
 * Player fields read: alive
 * Player fields written: pos_x, pos_z
 * Globals read: playerinfo_leftbound
 * Called by: PlayerPushCheck, PlayerUpdate, PlayerUpdateBindTo
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 5 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 2 temporaries are float80, as the original kept them in x87 registers.
 */
void StageBound(int player)

{
  float80 f1;
  float80 f2;
  int *pi3;
  
  pi3 = g;
  if ((g[0x731d] != 1) || (*(int *)(player + PLB_ALIVE) != 0)) {
    f2 = (float)g[G_PLAYERINFO_LEFTBOUND];
    f1 = *(float *)(player + PLB_POS_X);
    if (f1 < f2) {
      *(float *)(player + PLB_POS_X) = f2;
      f1 = f2;
    }
    if ((float80)pi3[0x109a] < f1) {
      *(float *)(player + PLB_POS_X) = (float80)pi3[0x109a];
      pi3 = g;
    }
    f2 = (float80)pi3[0x109b];
    f1 = *(float *)(player + PLB_POS_Z);
    if (f1 < f2) {
      *(float *)(player + PLB_POS_Z) = f2;
      pi3 = g;
      f1 = f2;
    }
    if ((float80)pi3[0x109c] < f1) {
      *(float *)(player + PLB_POS_Z) = (float80)pi3[0x109c];
      return;
    }
  }
  return;
}

/* GameClsnUpdate @ 0x080b2fa0, 1167 bytes
 *
 * The collision pass for one frame. For every pair of active players it
 * checks pushing, reversals and hits (both directions). Then it checks
 * projectiles against players and against each other, and applies the hits
 * found (Player1HitP2, PlayerGetHit...).
 *
 * Globals read: slot_first, slot_last, clsn_list
 * Calls: PlayerAreEnemies, PlayerPushCheck, PlayerCheckReversal,
 *        Player1ReverseP2, PlayerCheckP1HitP2, Player1HitP2,
 *        PlayerCheckHitProj, PlayerCheckProjHit, PlayerProjDoHit,
 *        CheckProjHitProj
 * Called by: GameUpdate
 *
 * Elecbyte file: src/mugen/p-update.c
 */
void GameClsnUpdate(void)

{
  int i1;
  int *player;
  bool b3;
  uint32_t u4;
  int player2;
  int *player3;
  int i7;
  int player4;
  int *pi9;
  int i10;
  int *player5;
  int *player6;
  
  pi9 = g;
  player4 = 0;
  player2 = g[G_SLOT_FIRST];
  if (player2 <= g[G_SLOT_LAST]) {
    i7 = player2 * 4 + 0x1cf60;
    i10 = 0x1d160;
    do {
      i1 = *(int *)(i7 + 4 + (int)pi9);
      if ((i1 == 0) || (b3 = true, *(int *)(i1 + 0x158) == 0)) {
        b3 = false;
      }
      if ((b3) && (*(int *)(*(int *)(i1 + 0x13bc) + 0x10) != 0)) {
        *(int *)(i10 + 0xc + (int)pi9) = i1;
        i10 = i10 + 4;
        player4 = player4 + 1;
      }
      player2 = player2 + 1;
      i7 = i7 + 4;
    } while (player2 <= pi9[0x745a]);
  }
  pi9[player4 + 0x745b] = 0;
  player2 = pi9[0x745b];
  pi9[0x749c] = player4;
  pi9 = pi9 + 0x745b;
  while (player2 != 0) {
    if (0 < *(int *)(player2 + 0xff8)) {
      *(int *)(player2 + 0xff8) = *(int *)(player2 + 0xff8) + -1;
    }
    pi9 = pi9 + 1;
    *(uint32_t *)(player2 + 0x1344) = 0;
    player2 = *pi9;
  }
  pi9 = g + G_CLSN_LIST;
  player2 = g[G_CLSN_LIST];
  while (player2 != 0) {
    player3 = pi9 + 1;
    player4 = pi9[1];
    while (player4 != 0) {
      i7 = PlayerAreEnemies(player2,player4);
      if (i7 != 0) {
        PlayerPushCheck(player2,player4,0);
      }
      player3 = player3 + 1;
      player4 = *player3;
    }
    pi9 = pi9 + 1;
    player2 = *pi9;
  }
  pi9 = g + G_CLSN_LIST;
  player3 = (int *)g[G_CLSN_LIST];
  while (player3 != (int *)0x0) {
    player5 = pi9 + 1;
    player6 = (int *)pi9[1];
    while (player6 != (int *)0x0) {
      player2 = PlayerAreEnemies((int)player3,(int)player6);
      if (player2 != 0) {
        player2 = PlayerCheckReversal((int)player3,(int)player6);
        if (player2 != 0) {
          Player1ReverseP2(player3,player6);
        }
        player2 = PlayerCheckReversal((int)player6,(int)player3);
        if (player2 != 0) {
          Player1ReverseP2(player6,player3);
        }
      }
      player5 = player5 + 1;
      player6 = (int *)*player5;
    }
    pi9 = pi9 + 1;
    player3 = (int *)*pi9;
  }
  pi9 = g + G_CLSN_LIST;
  player2 = g[G_CLSN_LIST];
  player3 = g;
  while (g = player3, player2 != 0) {
    player4 = pi9[1];
    player3 = pi9 + 1;
    while (player4 != 0) {
      player3 = player3 + 1;
      u4 = PlayerCheckP1HitP2(player2,player4);
      *(uint32_t *)(*(int *)(player4 + 0x1154) + *(int *)(player2 + 8) * 4) = u4;
      u4 = PlayerCheckP1HitP2(player4,player2);
      player5 = (int *)(player4 + 8);
      player4 = *player3;
      *(uint32_t *)(*(int *)(player2 + 0x1154) + *player5 * 4) = u4;
    }
    pi9 = pi9 + 1;
    player3 = g;
    player2 = *pi9;
  }
  if ((*(uint8_t *)(player3 + 0x7304) & 1) == 0) {
    pi9 = player3 + player3[0x749c] + 0x745a;
    if (player3 + 0x745b <= pi9) {
      do {
        player = (int *)*pi9;
        player5 = player3 + 0x745b;
        player6 = (int *)player3[0x745b];
        while (player6 != (int *)0x0) {
          if (*(int *)(player[0x455] + player6[2] * 4) != 0) {
            Player1HitP2(player6,player);
            *(uint32_t *)(player[0x455] + player6[2] * 4) = 0;
          }
          player5 = player5 + 1;
          player3 = g;
          player6 = (int *)*player5;
        }
        pi9 = pi9 + -1;
      } while (player3 + 0x745b <= pi9);
    }
  }
  else {
    pi9 = player3 + 0x745b;
    player5 = (int *)player3[0x745b];
    while (player5 != (int *)0x0) {
      player6 = player3 + 0x745b;
      player = (int *)player3[0x745b];
      while (player != (int *)0x0) {
        if (*(int *)(player5[0x455] + player[2] * 4) != 0) {
          Player1HitP2(player,player5);
          *(uint32_t *)(player5[0x455] + player[2] * 4) = 0;
        }
        player6 = player6 + 1;
        player3 = g;
        player = (int *)*player6;
      }
      pi9 = pi9 + 1;
      player5 = (int *)*pi9;
    }
  }
  pi9 = player3 + 0x745b;
  player5 = (int *)player3[0x745b];
  while (player5 != (int *)0x0) {
    player3 = pi9 + 1;
    player6 = (int *)pi9[1];
    while (player6 != (int *)0x0) {
      player3 = player3 + 1;
      PlayerCheckHitProj((int)player5,player6);
      PlayerCheckHitProj((int)player6,player5);
      player6 = (int *)*player3;
    }
    pi9 = pi9 + 1;
    player3 = g;
    player5 = (int *)*pi9;
  }
  pi9 = player3 + 0x745b;
  player5 = (int *)player3[0x745b];
  while (player5 != (int *)0x0) {
    player3 = pi9 + 1;
    player6 = (int *)pi9[1];
    while (player6 != (int *)0x0) {
      if ((player6[0x3ff] & player6[0x400]) != 0) {
        PlayerCheckProjHit(player5,player6);
      }
      if ((player5[0x3ff] & player5[0x400]) != 0) {
        PlayerCheckProjHit(player6,player5);
      }
      player3 = player3 + 1;
      player6 = (int *)*player3;
    }
    pi9 = pi9 + 1;
    player3 = g;
    player5 = (int *)*pi9;
  }
  pi9 = player3 + 0x745b;
  player2 = player3[0x745b];
  while (player2 != 0) {
    pi9 = pi9 + 1;
    PlayerProjDoHit(player2);
    player3 = g;
    player2 = *pi9;
  }
  pi9 = player3 + 0x745b;
  player2 = player3[0x745b];
  while (player2 != 0) {
    player3 = pi9 + 1;
    player4 = pi9[1];
    while (player4 != 0) {
      player3 = player3 + 1;
      CheckProjHitProj(player2,player4);
      player4 = *player3;
    }
    pi9 = pi9 + 1;
    player3 = g;
    player2 = *pi9;
  }
  pi9 = player3 + 0x745b;
  player2 = player3[0x745b];
  while (player2 != 0) {
    player3 = pi9 + 1;
    player4 = pi9[1];
    while (player4 != 0) {
      i7 = PlayerAreEnemies(player2,player4);
      if (i7 != 0) {
        PlayerPushCheck(player2,player4,0);
      }
      player3 = player3 + 1;
      player4 = *player3;
    }
    pi9 = pi9 + 1;
    player2 = *pi9;
  }
  return;
}

/* PlayerPushCheck @ 0x080b3430, 617 bytes
 *
 * Pushes two overlapping players apart (if both have push enabled) and
 * re-applies the stage and screen bounds.
 *
 * Parameters:
 *   player       int
 *   player2      int  (player)
 *   arg3         int
 *
 * Player fields read: offset_x, pos_x, offset_y, pos_y, pos_z, anim, alive
 * Calls: ClsnArrayDetectRectFlip, PlayerCheckOverlap, StageBound,
 *        ScreenBound
 * Called by: GameClsnUpdate
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 8 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void PlayerPushCheck(int player,int player2,int arg3)

{
  float80 f1;
  float80 f2;
  float80 f3;
  int i4;
  uint32_t stk_1c;
  
  stk_1c = (uint32_t)(*(int *)(player + 400) != 1);
  if (arg3 == 0) {
    f1 = ((float80)*(int *)(player2 + PLB_OFFSET_X) + *(float *)(player2 + PLB_POS_X)) -
            ((float80)*(int *)(player + PLB_OFFSET_X) + *(float *)(player + PLB_POS_X));
    f2 = ((float80)*(int *)(player2 + PLB_OFFSET_Y) + *(float *)(player2 + PLB_POS_Y)) -
            ((float80)*(int *)(player + PLB_OFFSET_Y) + *(float *)(player + PLB_POS_Y));
    f3 = *(float *)(player + PLB_POS_Z) - *(float *)(player2 + PLB_POS_Z);
  }
  else {
    f1 = ((float80)*(int *)(player2 + PLB_OFFSET_X) + *(float *)(player2 + 0x1a8)) -
            ((float80)*(int *)(player + PLB_OFFSET_X) + *(float *)(player + 0x1a8));
    f2 = ((float80)*(int *)(player2 + PLB_OFFSET_Y) + *(float *)(player2 + 0x1ac)) -
            ((float80)*(int *)(player + PLB_OFFSET_Y) + *(float *)(player + 0x1ac));
    f3 = *(float *)(player + 0x1b0) - *(float *)(player2 + 0x1b0);
  }
  i4 = (int)X87_FIST32(f3);
  if ((*(int *)(player + 0x1f0) != 0) && (*(int *)(player2 + 0x1f0) != 0)) {
    if (i4 < 0) {
      i4 = -i4;
    }
    if (i4 < *(int *)(player2 + 0x94) + *(int *)(player + 0x94)) {
      i4 = ClsnArrayDetectRectFlip
                        (*(int **)(*(int *)(*(int *)(player + PLB_ANIM) + 0x10) + 0x2c),
                         *(int **)(*(int *)(*(int *)(player2 + PLB_ANIM) + 0x10) + 0x2c),
                         (int)X87_FIST32(f1),(int)X87_FIST32(f2),stk_1c,
                         (uint32_t)(*(int *)(player2 + 400) != 1));
      if (i4 != 0) {
        if (((*(int *)(player + PLB_ALIVE) != 0) && (*(int *)(player2 + PLB_ALIVE) != 0)) ||
           (g[0x731d] != 1)) {
          PlayerCheckOverlap(player,player2);
        }
        StageBound(player);
        StageBound(player2);
        if (*(int *)(player + 0x1e4) != 0) {
          ScreenBound(player);
        }
        if (*(int *)(player2 + 0x1e4) != 0) {
          ScreenBound(player2);
        }
      }
    }
  }
  return;
}

/* PlayerCheckOverlap @ 0x080b36a0, 291 bytes
 *
 * Returns how much two players' bodies overlap horizontally (by their
 * widths), or 0.
 *
 * Parameters:
 *   player       int
 *   player2      int  (player)
 *
 * Player fields read: statetype, pos_y
 * Player fields written: pos_x
 * Calls: PlayerGetWidth
 * Called by: PlayerPushCheck
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 2 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 2 temporaries are float80, as the original kept them in x87 registers.
 */
void PlayerCheckOverlap(int player,int player2)

{
  float80 f1;
  float80 f2;
  int width;
  int width2;
  int player3;
  
  if (((*(int *)(player + PLB_STATETYPE) != 1) ||
      (*(float *)(player + PLB_POS_Y) - *(float *)(player2 + PLB_POS_Y) <= (float80)*(int *)(player + 0x98))
      ) && ((*(int *)(player2 + PLB_STATETYPE) != 1 ||
            (*(float *)(player2 + PLB_POS_Y) - *(float *)(player + PLB_POS_Y) <=
             (float80)*(int *)(player2 + 0x98))))) {
    player3 = player;
    if (*(float *)(player2 + PLB_POS_X) < *(float *)(player + PLB_POS_X)) {
      player3 = player2;
      player2 = player;
    }
    width = PlayerGetWidth(player3,4,1);
    width2 = PlayerGetWidth(player2,3,1);
    f2 = *(float *)(player2 + PLB_POS_X) - *(float *)(player3 + PLB_POS_X);
    if (f2 < 10.0) {
      f1 = (*(float *)(player3 + PLB_POS_X) + *(float *)(player2 + PLB_POS_X)) * 0.5;
      *(float *)(player3 + PLB_POS_X) = f1 - 5.0;
      *(float *)(player2 + PLB_POS_X) = f1 + 5.0;
    }
    if (f2 < (float)(width2 + width)) {
      f2 = ((float)(width2 + width) - f2) * 0.5;
      *(float *)(player3 + PLB_POS_X) = *(float *)(player3 + PLB_POS_X) - f2;
      *(float *)(player2 + PLB_POS_X) = *(float *)(player2 + PLB_POS_X) + f2;
    }
  }
  return;
}

/* PlayerCheckP1HitP2 @ 0x080b37d0, 95 bytes
 *
 * Returns whether player 1's active HitDef can hit player 2 this frame
 * (PlayerCheckHit).
 *
 * Parameters:
 *   player       int
 *   player2      int  (player)
 *
 * Calls: PlayerCheckHit
 * Called by: GameClsnUpdate
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 2 byte results widened with ZEXT8 (upper bytes are zero).
 */
uint32_t PlayerCheckP1HitP2(int player,int player2)

{
  bool b1;
  uint32_t stale_var;
  uint32_t stale_var_00;
  uint32_t u2;
  
  u2 = 0;
  b1 = PlayerCheckHit(player,player2);
  if (ZEXT8(b1) != 0) {
    b1 = PlayerCheckHit(player2,player);
    if (ZEXT8(b1) != 0) {
      if (*(int *)(player + 0x11d4) <= *(int *)(player2 + 0x11d4)) {
        if (*(int *)(player + 0x11d4) != *(int *)(player2 + 0x11d4)) {
          return 0;
        }
        if (*(int *)(player + 0x11d8) != 0) {
          return 0;
        }
        if (*(int *)(player2 + 0x11d8) == 2) {
          return 0;
        }
      }
    }
    u2 = 1;
  }
  return u2;
}

/* PlayerCheckHit @ 0x080b3830, 778 bytes
 *
 * Tests an attack: player 1 must have an active HitDef that affects player
 * 2's team and has not already hit it (unless allowed). The flags must match
 * player 2's state (PlayerCheckFlagHit), and the attack boxes (Clsn1) must
 * overlap player 2's body boxes (Clsn2).
 *
 * Parameters:
 *   player       int
 *   player2      int  (player)
 *
 * Player fields read: anim, movetype, hitdef, teamside, targets, pos_z,
 *                     offset_x, pos_x, offset_y, pos_y
 * Calls: HitdefAffectTeam, PlayerFindTarget, ClsnArrayDetectRectFlip,
 *        PlayerCheckFlagHit, PlayerAttrStateSet, PlayerCheckAttrHit
 * Called by: PlayerCheckP1HitP2
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to NAN
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: 4 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 2 temporaries are float80, as the original kept them in x87 registers.
 */
bool PlayerCheckHit(int player,int player2)

{
  float80 f1;
  float80 f2;
  int *pi3;
  int *pi4;
  bool b5;
  uint32_t stale_var;
  int *pi6;
  int i7;
  int i8;
  int stk_30;
  uint32_t stk_28;
  uint32_t stk_24;
  
  stk_24 = (uint32_t)(*(int *)(player + 400) != 1);
  stk_28 = (uint32_t)(*(int *)(player2 + 400) != 1);
  pi3 = *(int **)(*(int *)(*(int *)(player + PLB_ANIM) + 0x10) + 0x28);
  pi4 = *(int **)(*(int *)(*(int *)(player2 + PLB_ANIM) + 0x10) + 0x2c);
  if (*(int *)(player + PLB_MOVETYPE) == 0) {
    return false;
  }
  if (*(int *)(player + 0x1204) != 0) {
    return false;
  }
  if (0 < *(int *)(player2 + 0xff8)) {
    return false;
  }
  if ((*(uint32_t *)(player2 + 0xffc) & *(uint32_t *)(player2 + 0x1000)) == 0) {
    return false;
  }
  if (*(int *)(player + PLB_HITDEF) == 0) {
    return false;
  }
  b5 = HitdefAffectTeam(player + 0x1158,*(int *)(player + PLB_TEAMSIDE),*(uint32_t *)(player2 + PLB_TEAMSIDE));
  if (ZEXT8(b5) == 0) {
    return false;
  }
  if (*(int *)(player + 0x1170) != -1) {
    if (*(int *)(player2 + 0x1064) != *(int *)(player + 0x1170)) {
      return false;
    }
    if (*(int *)(player2 + 0x1014) != player) {
      return false;
    }
  }
  if ((*(int *)(player + 0x1174) != -1) && (*(int *)(player2 + 0x1014) == player)) {
    if (*(int *)(player2 + 0x1064) == *(int *)(player + 0x1174)) {
      return false;
    }
    if ((*(int *)(player + 0x1178) != -1) &&
       (*(int *)(player2 + 0x1064) == *(int *)(player + 0x1178))) {
      return false;
    }
  }
  pi6 = PlayerFindTarget(*(int *)(player + PLB_TARGETS),player2);
  if (pi6 == (int *)0x0) {
    i7 = *(int *)(player + 0x1168);
  }
  else {
    i7 = *(int *)(player + 0x1168);
    if (pi6[2] == i7) {
      return false;
    }
  }
  if (*(int *)(*(int *)(player2 + 0x1148) + *(int *)(player + 8) * 4) == i7) {
    return false;
  }
  stk_30 = *(int *)(player + 0x11dc);
  i7 = *(int *)(player + 0x11e0);
  if (stk_30 == -1) {
    stk_30 = *(int *)(player + 0x5c);
  }
  if (i7 == -1) {
    i7 = *(int *)(player + 0x60);
  }
  f1 = *(float *)(player + PLB_POS_Z);
  f2 = *(float *)(player2 + PLB_POS_Z);
  if (f1 < f2) {
    i8 = *(int *)(player2 + 0x94);
  }
  else {
    i8 = *(int *)(player2 + 0x94);
    if (f1 - f2 <= (float)(stk_30 + i8)) goto L_080b3a95;
    if (f2 < f1) {
      return false;
    }
  }
  if ((float)(i8 + i7) < f2 - f1) {
    return false;
  }
L_080b3a95:
  i7 = ClsnArrayDetectRectFlip
                    (pi3,pi4,
                     (int)X87_FIST32(((float80)*(int *)(player2 + PLB_OFFSET_X) + *(float *)(player2 + PLB_POS_X)) -
                                ((float80)*(int *)(player + PLB_OFFSET_X) + *(float *)(player + PLB_POS_X))),
                     (int)X87_FIST32(((float80)*(int *)(player2 + PLB_OFFSET_Y) + *(float *)(player2 + PLB_POS_Y)) -
                                ((float80)*(int *)(player + PLB_OFFSET_Y) + *(float *)(player + PLB_POS_Y))),
                     stk_24,stk_28);
  if (i7 != 0) {
    if (*(char *)(player + 0x209) == '\0') {
      if (pi6 == (int *)0x0) {
        i7 = *(int *)(player + 0x118c);
      }
      else {
        i7 = *(int *)(player + 0x118c);
        if ((i7 != -1) && (pi6[1] - i7 < 0)) {
          return false;
        }
      }
      *(int *)(player + 0x1344) = i7;
    }
    i7 = PlayerCheckFlagHit(player2,*(uint32_t *)(player + 0x11d0));
    if (i7 != 0) {
      PlayerAttrStateSet(player);
      i7 = PlayerCheckAttrHit(player2,*(uint32_t *)(player + 0x1164));
      return i7 != 0;
    }
  }
  return false;
}

/* Player1HitP2 @ 0x080b3b40, 2237 bytes
 *
 * Applies a successful hit from player 1 to player 2. It adds player 2 as a
 * target, computes damage with attack and defence multipliers, and gives
 * power to both. It plays the hit spark and sound and sets the hit pause,
 * move contact and combo counters. Then it puts player 2 into its get-hit
 * (or guard) state (PlayerGetHit / PlayerGetHitG), with p1stateno/p2stateno.
 *
 * Parameters:
 *   player       int *
 *   player2      int *  (player)
 *
 * Player fields read: facing, hitdef, teamside, hitdef_damage, targets,
 *                     offset_x, offset_y, hitfall, statetype, pos_x,
 *                     pos_y, pos_z, anim
 * Player fields written: sprpriority, movecontact, movereversed, hitcount,
 *                        uniqhitcount, ctrl
 * Globals read: round_no, frame_count
 * Calls: PlayerDropBoundTargets, PlayerCheckFlagHit, PlayerGetDamagedLife,
 *        PlayerGetCorrectedDamage, WinIconCheckTeam, WinIconCheck,
 *        AttrMatch, PlayerFindTarget, ArrayAdd, PlayerGetWidth,
 *        PlayerGetHitG, PlayerPowerSet, PlayerSparkCreate, PlayerGetHit,
 *        ComboAdd, PlayerChangeState, KBClearCommandValidTimes,
 *        PlayerInCorner
 * Called by: GameClsnUpdate
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 1 float-field accesses rewritten as bit reinterpretations (asm: x87
 *       single loads/stores at offsets 0x1354)
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x70 bytes, 8
 *       variables), because their address is taken.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void Player1HitP2(int *player,int *player2)

{
  float80 f1;
  bool b2;
  bool b3;
  bool b4;
  int i5;
  int i6;
  uint32_t stale_var;
  int *pi7;
  int width;
  int *pi9;
  int **ppi10;
  int *pi11;
  unsigned char frame[0x70] __attribute__((aligned(16)));
#define stk_68 (*(uint32_t *)(frame + 0x8))
#define stk_60 (*(int *)(frame + 0x10))
#define stk_58 (*(int *)(frame + 0x18))
#define stk_54 (*(uint32_t *)(frame + 0x1c))
#define stk_4c (*(int **)(frame + 0x24))
#define stk_48 (*(int **)(frame + 0x28))
#define stk_3c (*(int **)(frame + 0x34))
#define stk_38 (*(int *)(frame + 0x38))
  
  stk_48 = (int *)0x0;
  stk_58 = player[PL_FACING];
  pi7 = player + PL_HITDEF;
  stk_54 = (uint32_t)(stk_58 != 1);
  width = g[player[PL_TEAMSIDE] + G_ROUND_NO];
  if (player[0x462] != 0) {
    if (player[PL_HITDEF] == 0) {
      return;
    }
    if (0 < player2[0x3fe]) {
      return;
    }
    PlayerDropBoundTargets((int)player,player2);
  }
  stk_68 = 0;
  b3 = false;
  i5 = PlayerCheckFlagHit((int)player2,player[0x473]);
  if (((i5 == 0) || (player2[900] == 0)) || (*(char *)((int)player + 0x20b) != '\0')) {
    width = PlayerGetDamagedLife((int)player2);
    i5 = PlayerGetCorrectedDamage(player[PL_HITDEF_DAMAGE],player[0x45f],(int)player2);
    if (width - i5 < 1) {
      WinIconCheckTeam(player2[PL_TEAMSIDE],player[PL_TEAMSIDE],player[0x459]);
L_080b3d04:
      stk_68 = 1;
    }
  }
  else {
    i5 = PlayerGetDamagedLife((int)player2);
    i6 = PlayerGetCorrectedDamage(player[0x465],player[0x460],(int)player2);
    if (i5 - i6 < 1) {
      if (((g[0x79a9] != 0) && (stk_68 = 1, g[0x7511] != 3)) && (width < 10)) {
        WinIconCheck(player[PL_TEAMSIDE],0,3);
        goto L_080b3d04;
      }
    }
    else {
      b3 = true;
    }
  }
  b2 = false;
  stk_68 = stk_68 & (g[0x730b] != 0) - 1;
  pi9 = player2 + 0x42a;
  for (width = 0; width < 8; width = width + 1) {
    stk_4c = pi9;
    if ((*pi9 != 0) &&
       (b4 = AttrMatch(pi9[1],player[0x459]), ZEXT8(b4) != 0)) {
      b2 = true;
      break;
    }
    pi9 = pi9 + 5;
  }
  if (b2) {
    b3 = false;
    stk_68 = 0;
    if (player[0x47b] != 0) {
      return;
    }
    if (player[0x479] != -1) {
      return;
    }
  }
  else {
    stk_4c = (int *)0x0;
    stk_48 = PlayerFindTarget(player[PL_TARGETS],(int)player2);
    if (stk_48 == (int *)0x0) {
      ppi10 = &stk_3c;
      for (width = 8; width != 0; width = width + -1) {
        *ppi10 = (int *)0x0;
        ppi10 = ppi10 + 1;
      }
      stk_3c = player2;
      stk_38 = player[0x19];
      width = ArrayAdd(player[PL_TARGETS],&stk_3c,0,0);
      if (width == -1) {
        return;
      }
      stk_48 = (int *)(width * *(int *)(player[PL_TARGETS] + 4) + *(int *)(player[PL_TARGETS] + 0x14));
    }
    stk_48[6] = 0;
    stk_48[5] = 0;
    stk_48[4] = 0;
    stk_48[3] = 0;
    stk_48[2] = player[0x45a];
  }
  player[PL_SPRPRIORITY] = player[0x47d];
  player2[PL_SPRPRIORITY] = player[0x47e];
  if (player2[PL_FACING] == stk_58) {
    width = PlayerGetWidth((int)player2,2,0);
    width = -width - player[0x492];
  }
  else {
    width = PlayerGetWidth((int)player2,1,0);
    width = width + player[0x492];
  }
  width = (int)X87_FIST32((float)g[0x7311] +
                     (float)((width - player2[PL_OFFSET_X]) * player2[PL_FACING]) * BITS_I2F(player2[0x4d2]) +
                     (*(float *)&player2[0x4d5]));
  i5 = (int)X87_FIST32((float)(player[0x493] - player[PL_OFFSET_Y]) * BITS_I2F(player[0x4d2]) +
                     BITS_I2F(player[0x4d6]) + (float)g[0x7312]);
  if (b3) {
    player[0x387] = player[0x4b5];
    player[PL_MOVECONTACT] = 1;
    player[PL_MOVEREVERSED] = 0;
    stk_60 = PlayerGetHitG(player,player2,(int)pi7,stk_58);
    PlayerPowerSet((int)player,player[0x467] + *(int *)player[0x5c]);
    PlayerSparkCreate(player,player[0x490],width,i5,player[0x491],stk_54,1);
    goto L_080b4371;
  }
  if (!b2) {
    if (((player2[PL_HITFALL] != 0) || ((player[0x474] & 1U) != 0)) ||
       ((player[0x4a6] != 0 && (player2[PL_STATETYPE] == 3)))) {
      stk_48[1] = stk_48[1] - player[0x4d1];
      player[0x463] = 0;
    }
    if (player[0x494] != 0) {
      stk_58 = -player[PL_FACING];
      player[0x65] = stk_58;
    }
    if (player[0x495] != 0) {
      if (player[0x495] == 1) {
        if (stk_58 != player2[PL_FACING]) {
L_080b4020:
          stk_58 = -player[PL_FACING];
          player[0x65] = stk_58;
        }
      }
      else if (stk_58 == player2[PL_FACING]) goto L_080b4020;
    }
  }
  stk_60 = PlayerGetHit(player,player2,(int)pi7,BITS_I2F(player[PL_POS_X]),BITS_I2F(player[PL_POS_Y]),
                          BITS_I2F(player[PL_POS_Z]),stk_58,stk_68,(int)stk_4c);
  if ((stk_60 != 0) || (b2)) {
    player[0x387] = player[0x46b];
    PlayerPowerSet((int)player,player[0x466] + *(int *)player[0x5c]);
    pi9 = g;
    player[0x4e6] = player[0x4e6] + player[0x46c];
    if (player[0x38e] < pi9[0x7304]) {
      player[PL_HITCOUNT] = player[PL_HITCOUNT] + player[0x46c];
    }
    player[PL_UNIQHITCOUNT] = player[PL_UNIQHITCOUNT] + player[0x46c];
    player[PL_MOVECONTACT] = 2;
    player[PL_MOVEREVERSED] = 0;
    ComboAdd(player[PL_TEAMSIDE],player[0x46c]);
    if (!b2) {
      if ((0 < player[0x4bd]) || (player[0x4bd] == -1)) {
        pi9 = player + 0x4bc;
        pi11 = player2 + 0x977;
        for (i6 = 0xf; i6 != 0; i6 = i6 + -1) {
          *pi11 = *pi9;
          pi9 = pi9 + 1;
          pi11 = pi11 + 1;
        }
      }
      if ((player[0x459] & 0x1c0U) != 0) {
        player2[0x3fe] = player[0x46b] + 1;
        player[0x3fe] = player[0x46b] + 1;
      }
    }
  }
  PlayerSparkCreate(player,player[0x48e],width,i5,player[0x48f],stk_54,0);
  if (b2) {
    if (stk_4c[2] != -1) {
      PlayerChangeState((int)player2,stk_4c[2]);
    }
  }
  else {
    if (player[0x479] != -1) {
      PlayerChangeState((int)player,player[0x479]);
    }
    if (player[0x47b] != 0) {
      player2[0x2fb] = player[0x2fa];
      player2[0x2fc] = player[2];
      player2[0x259] = player[0x259];
      KBClearCommandValidTimes(player2 + 0x25a);
      if (player[0x2fb] != 0) {
        player2[0x2fb] = player[0x2fb];
        player2[0x2fc] = player[0x2fc];
      }
      if (player[0x4f0] == 0) {
        player2[0x4f0] = *(int *)player[PL_ANIM];
      }
      else {
        player2[0x4f0] = player[0x4f0];
      }
    }
    if (player[0x47a] != -1) {
      PlayerChangeState((int)player2,player[0x47a]);
      player2[PL_CTRL] = 0;
    }
    stk_48[6] = player[0x47c];
    stk_48[3] = player[0x499];
    stk_48[4] = player[0x49a];
    stk_48[5] = player[0x49b];
  }
L_080b4371:
  if ((stk_60 != 0) && (width = PlayerInCorner((int)player2), width != 0)) {
    player[0x8e] = -1;
    f1 = BITS_I2F(player2[0x453]);
    player[0x8a] = 0;
    player[0x8b] = 0x3f333333;
    player[0x8d] = 0x3f800000;
    player[0x89] = BITS_F2I(int, ((float80)player[PL_FACING] * f1));
  }
  player[0x38e] = g[G_FRAME_COUNT];
  if (player[0x462] != 0) {
    *pi7 = 0;
  }
  return;
}
#undef stk_68
#undef stk_60
#undef stk_58
#undef stk_54
#undef stk_4c
#undef stk_48
#undef stk_3c
#undef stk_38

/* PlayerGetHit @ 0x080b4400, 2824 bytes
 *
 * Puts a player into the get-hit reaction for a hit. It sets the hit
 * variables (GetHitVar: velocities, hit time, slide time, fall, damage...),
 * plays the hit sound, stops command buffering, releases its bindings and
 * removes its "removeongethit" explods. Then it changes to the appropriate
 * get-hit state (or the attacker's p2stateno).
 *
 * Parameters:
 *   arg1         int *
 *   player       int *
 *   arg3         int
 *   arg4         float
 *   arg5         float
 *   arg6         float
 *   arg7         int
 *   arg8         int
 *   arg9         int
 *
 * Player fields read: facing, pos_y, vel_x, vel_y, life, pos_x, pos_z, id,
 *                     ishelper
 * Player fields written: statetype, hitvel, hitfall, prevstateno, stateno,
 *                        hitover, canrecover, movetype, statetime, ctrl,
 *                        hitshakeover, hitpausetime
 * Calls: GameSndPlayIDPos, PlayerSndID, SndIDStop,
 *        KBClearCommandValidTimes, PlayerDropBoundTargets,
 *        ExplodRemoveGetHit, PlayerGetCorrectedDamage, PlayerPowerSet
 * Called by: Player1HitP2, Player1ReverseP2, PlayerCheckProjHit
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 2 float-field accesses rewritten as bit reinterpretations (asm: x87
 *       single loads/stores at offsets 0x104c)
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 9 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t
PlayerGetHit(int *arg1,int *player,int arg3,float arg4,float arg5,float arg6,
            int arg7,int arg8,int arg9)

{
  float80 f1;
  bool b2;
  uint32_t u3;
  int i4;
  int i5;
  int *sounds;
  int *pi7;
  int i8;
  int i9;
  int stk_20;
  
  b2 = true;
  i4 = -arg7;
  stk_20 = 1;
  player[0x453] = 0;
  if ((arg9 != 0) && (*(int *)(arg9 + 0x10) != 0)) {
    player[PL_STATETYPE] = 3;
  }
  if (*(int *)(arg3 + 100) == 0) {
    i5 = *(int *)(*arg1 + 0x11d0);
    i9 = *(int *)(arg3 + 0x60);
    i8 = *(int *)(arg3 + 0x5c);
    sounds = *(int **)(*arg1 + 0x11d4);
  }
  else {
    i5 = 0;
    i9 = *(int *)(arg3 + 0x60);
    i8 = *(int *)(arg3 + 0x5c);
    sounds = (int *)g[0x4156];
  }
  GameSndPlayIDPos(-1,(int)X87_FIST32(BITS_I2F(player[0x4d5])),sounds,i8,i9,i5);
  if (*(int *)(arg3 + 0x118) == -player[PL_FACING] * i4) {
    player[0x65] = -player[PL_FACING];
  }
  player[0x412] = *(int *)(arg3 + 0xc);
  player[0x405] = (int)arg1;
  i5 = arg1[2];
  u3 = *(uint32_t *)(arg3 + 0x10);
  player[0x417] = 0;
  *(uint32_t *)(player[0x452] + i5 * 4) = u3;
  player[0x419] = *(int *)(arg3 + 0x14);
  player[0x41a] = 0;
  player[0x409] = *(int *)(arg3 + 0x11c);
  player[0x408] = *(int *)(arg3 + 0x134);
  player[PL_HITVEL] = 0;
  if (((*(uint32_t *)(arg3 + 0x78) & 1) != 0) || (arg8 != 0)) {
    player[PL_HITFALL] = 1;
  }
  if (player[PL_HITFALL] == 0) {
    i5 = *(int *)(arg3 + 0xa4);
  }
  else {
    i5 = *(int *)(arg3 + 0xb4);
  }
  player[0x407] = i5;
  if (1 < player[PL_STATETYPE] - 1U) {
    if ((player[PL_STATETYPE] == 4) && (BITS_I2F(player[PL_POS_Y]) == 0.0)) {
      if ((*(int *)(arg3 + 0x11c) != 0) && (*(int *)(arg3 + 0xac) == 0)) {
        f1 = *(float *)(arg3 + 0x158);
        b2 = false;
        player[PL_PREVSTATENO] = player[PL_STATENO];
        if (f1 == -32760.0) {
          player[PL_HITVEL] = player[PL_VEL_X];
        }
        else {
          player[PL_HITVEL] = BITS_F2I(int, ((float80)i4 * f1));
        }
        if (*(float *)(arg3 + 0x158) == -32760.0) {
          i5 = player[PL_VEL_Y];
        }
        else {
          i5 = *(int *)(arg3 + 0x15c);
        }
        player[0x417] = i5;
        player[0x453] = *(int *)(arg3 + 0x160);
        if (BITS_I2F(player[0x417]) == 0.0) {
          player[PL_STATENO] = 0x13d8;
          player[PL_HITOVER] = *(int *)(arg3 + 0x154);
        }
        else {
          player[PL_STATENO] = 0x13d8;
          stk_20 = *(int *)(arg3 + 0x150);
          player[0x414] = BITS_F2I(int, (BITS_I2F(player[0x414]) + 15.0));
        }
      }
    }
    else if ((*(int *)(arg3 + 0x134) != 0) && (*(int *)(arg3 + 0xac) == 0)) {
      b2 = false;
      player[PL_PREVSTATENO] = player[PL_STATENO];
      player[PL_STATENO] = 0x139c;
      f1 = *(float *)(arg3 + 0x144);
      player[PL_STATENO] = ((*(int *)(arg3 + 0x134) == 3) - 1 & 0xffffffce) + 0x13ce;
      if (f1 == -32760.0) {
        player[PL_HITVEL] = player[PL_VEL_X];
      }
      else {
        player[PL_HITVEL] = BITS_F2I(int, ((float80)i4 * f1));
      }
      if (*(float *)(arg3 + 0x148) == -32760.0) {
        player[0x417] = player[PL_VEL_Y];
      }
      else {
        player[0x417] = BITS_F2I(int, *(float *)(arg3 + 0x148));
      }
      player[0x453] = *(int *)(arg3 + 0x14c);
      player[PL_HITOVER] = *(int *)(arg3 + 0x13c);
      if (*(int *)(arg3 + 0x140) != 0) {
        player[PL_HITFALL] = 1;
      }
      if (player[PL_HITFALL] == 0) {
        i5 = *(int *)(arg3 + 0x138);
      }
      else {
        i5 = *(int *)(arg3 + 0xb4);
      }
      player[0x407] = i5;
      if (arg8 != 0) {
        if (BITS_I2F(player[PL_HITVEL]) < 0.0) {
          player[PL_HITVEL] = BITS_F2I(int, (BITS_I2F(player[PL_HITVEL]) - 2.0));
        }
        if (BITS_I2F(player[0x417]) <= 0.0) {
          f1 = BITS_I2F(player[0x417]) - 2.0;
          player[0x417] = BITS_F2I(int, f1);
          if ((f1 <= 0.0) && (-3.0 < f1)) {
            player[0x417] = -0x3fc00000;
          }
        }
      }
    }
    goto L_080b49d0;
  }
  if ((*(int *)(arg3 + 0x11c) == 0) || (*(int *)(arg3 + 0xac) != 0)) goto L_080b49d0;
  b2 = false;
  player[PL_PREVSTATENO] = player[PL_STATENO];
  if ((*(int *)(arg3 + 0xa8) != 0) || (arg8 != 0)) {
    player[PL_STATETYPE] = 1;
  }
  player[PL_STATENO] = ((player[PL_STATETYPE] != 1) - 1 & 0xfffffff6) + 0x1392;
  if (*(int *)(arg3 + 0x11c) == 3) {
    player[PL_STATENO] = 0x13ce;
  }
  if (*(float *)(arg3 + 0x128) == -32760.0) {
    player[PL_HITVEL] = player[PL_VEL_X];
  }
  else {
    player[PL_HITVEL] = BITS_F2I(int, ((float80)i4 * *(float *)(arg3 + 0x128)));
  }
  if (*(float *)(arg3 + 300) == -32760.0) {
    player[0x417] = player[PL_VEL_Y];
  }
  else {
    player[0x417] = BITS_F2I(int, *(float *)(arg3 + 300));
  }
  player[0x453] = *(int *)(arg3 + 0x130);
  if (arg8 == 0) {
L_080b46ec:
    f1 = BITS_I2F(player[0x417]);
  }
  else {
    if (*(float *)(arg3 + 300) == 0.0) {
      player[PL_HITVEL] = BITS_F2I(int, (BITS_I2F(player[PL_HITVEL]) * ((double)0.66)));
    }
    if (BITS_I2F(player[PL_HITVEL]) < 0.0) {
      player[PL_HITVEL] = BITS_F2I(int, (BITS_I2F(player[PL_HITVEL]) - 2.5));
    }
    f1 = BITS_I2F(player[0x417]);
    if (f1 <= 0.0) {
      f1 = f1 - 2.0;
      player[0x417] = BITS_F2I(int, f1);
      if ((f1 <= 0.0) && (-6.0 < f1)) {
        player[0x417] = -0x3f400000;
      }
      goto L_080b46ec;
    }
  }
  if (player[PL_HITFALL] == 0) {
L_080b4715:
    if (f1 == 0.0) {
      player[PL_HITOVER] = *(int *)(arg3 + 0x120);
      player[0x40f] = *(int *)(arg3 + 0x124);
      if (player[0x407] == 3) {
        player[0x407] = 2;
      }
      goto L_080b49d0;
    }
  }
  else if (f1 == 0.0) {
    player[0x417] = -0x457ced91;
    f1 = BITS_I2F(player[0x417]);
    goto L_080b4715;
  }
  player[PL_HITOVER] = *(int *)(arg3 + 0x13c);
L_080b49d0:
  i5 = player[0x65];
  if (i5 == 0) {
    i5 = player[PL_FACING];
  }
  i9 = i4;
  if (*(int *)(arg3 + 0x118) == -1) {
    i9 = arg7;
  }
  if ((i5 != i9) && ((uint32_t)player[0x407] < 3)) {
    if (player[0x409] == 1) {
      player[0x409] = 2;
    }
    else if (player[0x409] == 2) {
      player[0x409] = 1;
    }
    if (player[0x408] == 1) {
      player[0x408] = 2;
    }
    else if (player[0x408] == 2) {
      player[0x408] = 1;
    }
  }
  if ((b2) && (*(int *)(arg3 + 0xac) == 0)) {
    u3 = 0;
  }
  else {
    if (*(float *)(arg3 + 0x194) == -32760.0) {
      player[0x418] = 0x3eb33333;
    }
    else {
      player[0x418] = BITS_F2I(int, *(float *)(arg3 + 0x194));
    }
    if (*(int *)(arg3 + 0x1d8) != 0) {
      sounds = (int *)(arg3 + 0x1d4);
      pi7 = g + 0x7317;
      for (i5 = 6; i5 != 0; i5 = i5 + -1) {
        *pi7 = *sounds;
        sounds = sounds + 1;
        pi7 = pi7 + 1;
      }
    }
    player[0x41e] = *(int *)(arg3 + 0xb8);
    player[0x41f] = *(int *)(arg3 + 0xbc);
    player[PL_CANRECOVER] = *(int *)(arg3 + 0xc0);
    player[0x421] = 0;
    player[0x422] = *(int *)(arg3 + 0xc4);
    player[0x423] = *(int *)(arg3 + 0x2c);
    sounds = (int *)(arg3 + 200);
    pi7 = player + 0x424;
    for (i5 = 6; i5 != 0; i5 = i5 + -1) {
      *pi7 = *sounds;
      sounds = sounds + 1;
      pi7 = pi7 + 1;
    }
    if (stk_20 == 0) {
      player[0x41e] = -0x39001000;
      player[0x41f] = 0;
    }
    player[0x41d] = *(int *)(arg3 + 0xb0);
    if (*(int *)(arg3 + 0xac) == 0) {
      i5 = PlayerSndID((int)player,0);
      SndIDStop(i5);
      player[0x259] = *player + 0x11b4;
      player[0x2fb] = 0;
      player[0x2fc] = -1;
      KBClearCommandValidTimes(player + 0x25a);
      player[0x4f0] = 0;
      if ((player[PL_MOVETYPE] != 2) && (1 < player[0x454])) {
        player[0x5b] = player[PL_LIFE];
        player[0x5a] = player[PL_LIFE];
        player[0x40b] = 0;
      }
      sounds = g;
      player[0x40b] = player[0x40b] + 1;
      player[900] = 0;
      player[PL_MOVETYPE] = 2;
      player[0x74] = 0;
      player[PL_STATETIME] = 0;
      player[PL_CTRL] = 0;
      i5 = *(int *)(arg3 + 0x50);
      player[PL_HITSHAKEOVER] = i5;
      i9 = sounds[0x74f3];
      if ((i9 != -1) && (player[i9 + 0x77] < i5)) {
        player[i9 + 0x77] = i5;
      }
      player[0x387] = 0;
      player[PL_HITPAUSETIME] = 0;
      i5 = (int)X87_FIST32((float80)(int)X87_FIST32(BITS_I2F(player[PL_POS_X])) - arg4);
      if (i5 < 0) {
        i5 = -i5;
      }
      i9 = *(int *)(arg3 + 0x100);
      if ((i5 < i9) && (i9 != -0x401)) {
        player[0x413] =
             (int)(((arg4 - (float)(i9 * i4)) - BITS_I2F(player[PL_POS_X])) +
                  (*(float *)&player[0x413]));
      }
      f1 = (float80)*(int *)(arg3 + 0x104);
      if ((BITS_I2F(player[PL_POS_Y]) - arg5 < f1) && (*(int *)(arg3 + 0x104) != -0x401)) {
        player[0x414] = BITS_F2I(int, (((f1 + arg5) - BITS_I2F(player[PL_POS_Y])) + BITS_I2F(player[0x414])));
      }
      f1 = (float80)*(int *)(arg3 + 0x108);
      if ((arg6 - BITS_I2F(player[PL_POS_Z]) < f1) && (*(int *)(arg3 + 0x108) != -0x401)) {
        player[0x415] = BITS_F2I(int, (((f1 + arg6) - BITS_I2F(player[PL_POS_Z])) + BITS_I2F(player[0x415])));
      }
      i5 = (int)X87_FIST32(arg4 - (float80)(int)X87_FIST32(BITS_I2F(player[PL_POS_X])));
      if (i5 < 0) {
        i5 = -i5;
      }
      i9 = *(int *)(arg3 + 0x10c);
      if ((i9 < i5) && (i9 != -0x401)) {
        player[0x413] =
             (int)(((arg4 - (float)(i9 * i4)) - BITS_I2F(player[PL_POS_X])) +
                  (*(float *)&player[0x413]));
      }
      f1 = (float80)*(int *)(arg3 + 0x110);
      if ((f1 < BITS_I2F(player[PL_POS_Y]) - arg5) && (*(int *)(arg3 + 0x110) != -0x401)) {
        player[0x414] = BITS_F2I(int, (((f1 + arg5) - BITS_I2F(player[PL_POS_Y])) + BITS_I2F(player[0x414])));
      }
      f1 = (float80)*(int *)(arg3 + 0x114);
      if ((f1 < arg6 - BITS_I2F(player[PL_POS_Z])) && (*(int *)(arg3 + 0x114) != -0x401)) {
        player[0x415] = BITS_F2I(int, (((f1 + arg6) - BITS_I2F(player[PL_POS_Z])) + BITS_I2F(player[0x415])));
      }
      PlayerDropBoundTargets((int)player,(int *)0x0);
      ExplodRemoveGetHit((uint32_t *)g[0x52be],player[PL_ID]);
      i4 = PlayerGetCorrectedDamage
                        (*(int *)(arg3 + 0x38),*(int *)(arg3 + 0x24),(int)player);
      player[0x40a] = player[0x40a] + i4;
      if (arg8 != 0) {
        player[0x40a] = player[PL_LIFE];
      }
      if ((player[PL_ISHELPER] != 1) || (player[0x98a] == 1)) {
        PlayerPowerSet((int)player,*(int *)(arg3 + 0x48) + *(int *)player[0x5c]);
      }
    }
    u3 = 1;
  }
  return u3;
}

/* PlayerTakeDamage @ 0x080b4f10, 131 bytes
 *
 * Applies damage to a player (LifeAdd-style), scaled by its defence
 * multiplier unless absolute.
 *
 * Parameters:
 *   player       int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Player fields read: defencemul, life
 * Calls: PlayerLifeSet
 * Called by: PlayerSCtrlApplyElem
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
void PlayerTakeDamage(int player,int arg2,int arg3,int arg4)

{
  uint32_t u1;
  uint32_t u2;
  
  u1 = -arg2;
  u2 = u1;
  if (arg4 == 0) {
    if ((int)u1 < 0) {
      u2 = (uint32_t)X87_FIST32((float80)(int)u1 * *(float *)(player + PLB_DEFENCEMUL) - 0.5);
    }
    if (0x7fffffff < u1) {
      u2 = u2 | (u2 != 0) - 1;
    }
  }
  u2 = u2 + *(int *)(player + PLB_LIFE);
  if (((int)u2 < 1) && (arg3 == 0)) {
    u2 = 1;
  }
  PlayerLifeSet(player,u2);
  return;
}

/* PlayerGetCorrectedDamage @ 0x080b4fa0, 153 bytes
 *
 * Returns the damage a hit really does: `damage` scaled by the player's
 * defence factor and rounded, at least 1 for a positive damage. For a
 * non-killing hit ("kill = 0") it is limited so the player keeps at least 1
 * life.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   player       int
 *
 * Player fields read: defencemul, alive
 * Calls: PlayerGetDamagedLife
 * Called by: Player1HitP2, PlayerCheckProjHit, PlayerGetHit, PlayerGetHitG
 *
 * Elecbyte file: src/mugen/p-update.c
 */
int PlayerGetCorrectedDamage(int arg1,int arg2,int player)

{
  int i1;
  int i2;
  
  i2 = *(int *)(player + 0x1028) +
          (int)X87_FIST32((float)arg1 * *(float *)(player + PLB_DEFENCEMUL) + 0.5);
  if ((0 < arg1) && (i2 == 0)) {
    i2 = 1;
  }
  if (arg2 == 0) {
    i1 = PlayerGetDamagedLife(player);
    if ((i1 == i2 || i1 - i2 < 0) && (*(int *)(player + PLB_ALIVE) != 0)) {
      i2 = PlayerGetDamagedLife(player);
      i2 = i2 + -1;
    }
  }
  return i2 - *(int *)(player + 0x1028);
}

/* PlayerGetHitG @ 0x080b5040, 714 bytes
 *
 * Puts a player into its guard reaction for a guarded hit: guard damage,
 * guard pause, slide and control times, guard sound. "Guard state error:
 * wrong move type" if the player was not able to guard.
 *
 * Parameters:
 *   arg1         int *
 *   player       int *
 *   arg3         int
 *   arg4         int
 *
 * Player fields read: statetype, life, ishelper
 * Player fields written: hitvel, stateno, hitshakeover, movetype,
 *                        statetime, ctrl, hitpausetime, hitover
 * Globals read: errmsg
 * Calls: GameSndPlayIDPos, KBClearCommandValidTimes, ErrorExit,
 *        PlayerGetCorrectedDamage, PlayerPowerSet
 * C library: sprintf
 * Called by: Player1HitP2, PlayerCheckProjHit
 * Messages:
 *   "Guard state error: wrong move type"
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t PlayerGetHitG(int *arg1,int *player,int arg3,int arg4)

{
  float80 f1;
  uint32_t u2;
  int i3;
  int *sounds;
  int i5;
  int i6;
  
  i3 = *(int *)(arg3 + 0x70);
  player[0x453] = 0;
  if (i3 == 0) {
    i3 = *(int *)(*arg1 + 0x11d0);
    i6 = *(int *)(arg3 + 0x6c);
    i5 = *(int *)(arg3 + 0x68);
    sounds = *(int **)(*arg1 + 0x11d4);
  }
  else {
    i3 = 0;
    i6 = *(int *)(arg3 + 0x6c);
    i5 = *(int *)(arg3 + 0x68);
    sounds = (int *)g[0x4156];
  }
  GameSndPlayIDPos(-1,(int)X87_FIST32(BITS_I2F(player[0x4d5])),sounds,i5,i6,i3);
  player[0x412] = *(int *)(arg3 + 0xc);
  i3 = arg1[2];
  u2 = *(uint32_t *)(arg3 + 0x10);
  player[0x405] = (int)arg1;
  *(uint32_t *)(player[0x452] + i3 * 4) = u2;
  player[0x419] = *(int *)(arg3 + 0x14);
  player[0x259] = *player + 0x11b4;
  player[0x41a] = 1;
  player[0x417] = 0;
  player[PL_HITVEL] = 0;
  player[0x2fb] = 0;
  player[0x2fc] = -1;
  KBClearCommandValidTimes(player + 0x25a);
  i3 = player[PL_STATETYPE];
  player[0x4f0] = 0;
  if (i3 == 2) {
    player[PL_STATENO] = 0x98;
  }
  else {
    if (i3 < 3) {
      if (i3 == 1) {
        player[PL_STATENO] = 0x96;
        goto L_080b51bf;
      }
    }
    else if (i3 == 3) {
      player[PL_STATENO] = 0x9a;
      goto L_080b51bf;
    }
    sprintf((char *)(g + G_ERRMSG),"Guard state error: wrong move type",arg1,arg1);
    ErrorExit();
  }
L_080b51bf:
  player[PL_HITSHAKEOVER] = *(int *)(arg3 + 0x178);
  if (player[PL_MOVETYPE] != 2) {
    player[0x5b] = player[PL_LIFE];
    player[0x5a] = player[PL_LIFE];
  }
  player[900] = 1;
  player[PL_MOVETYPE] = 2;
  player[0x74] = 0;
  player[PL_STATETIME] = 0;
  player[PL_CTRL] = 0;
  player[0x387] = 0;
  player[PL_HITPAUSETIME] = 0;
  if (player[PL_STATETYPE] - 1U < 2) {
    player[PL_HITOVER] = *(int *)(arg3 + 0x168);
    player[0x40f] = *(int *)(arg3 + 0x16c);
    f1 = *(float *)(arg3 + 0x164);
    player[0x410] = *(int *)(arg3 + 0x170);
    player[PL_HITVEL] = BITS_F2I(int, ((float)-arg4 * f1));
    player[0x453] = *(int *)(arg3 + 0x180);
  }
  if (player[PL_STATETYPE] == 3) {
    player[PL_HITVEL] = BITS_F2I(int, ((float)-arg4 * *(float *)(arg3 + 0x184)));
    player[0x417] = *(int *)(arg3 + 0x188);
    player[0x410] = *(int *)(arg3 + 0x18c);
    player[0x453] = *(int *)(arg3 + 400);
  }
  i3 = PlayerGetCorrectedDamage(*(int *)(arg3 + 0x3c),*(int *)(arg3 + 0x28),(int)player);
  player[0x40a] = player[0x40a] + i3;
  if ((player[PL_ISHELPER] != 1) || (player[0x98a] == 1)) {
    PlayerPowerSet((int)player,*(int *)(arg3 + 0x4c) + *(int *)player[0x5c]);
  }
  return 1;
}

/* PlayerCheckReversal @ 0x080b5310, 507 bytes
 *
 * Tests whether player 1's active ReversalDef catches player 2's attack
 * (attributes and Clsn1 overlap).
 *
 * Parameters:
 *   player       int
 *   player2      int  (player)
 *
 * Player fields read: hitdef, pos_z, anim, offset_x, pos_x, offset_y,
 *                     pos_y
 * Calls: ClsnArrayDetectRectFlip
 * Called by: GameClsnUpdate
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 4 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 2 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t PlayerCheckReversal(int player,int player2)

{
  float80 f1;
  float80 f2;
  int i3;
  int i4;
  uint32_t u5;
  int stk_2c;
  uint32_t stk_24;
  
  stk_24 = (uint32_t)(*(int *)(player + 400) != 1);
  if (*(int *)(player + PLB_HITDEF) == 0) {
    return 0;
  }
  if (*(int *)(player2 + PLB_HITDEF) == 0) {
    return 0;
  }
  if (*(int *)(player + 0x1204) == 0) {
    return 0;
  }
  if (*(int *)(*(int *)(player2 + 0x1148) + *(int *)(player + 8) * 4) == *(int *)(player + 0x1168)
     ) {
    return 0;
  }
  if (*(int *)(*(int *)(player + 0x1148) + *(int *)(player2 + 8) * 4) == *(int *)(player2 + 0x1168)
     ) {
    return 0;
  }
  stk_2c = *(int *)(player + 0x11dc);
  i3 = *(int *)(player + 0x11e0);
  if (stk_2c == -1) {
    stk_2c = *(int *)(player + 0x5c);
  }
  if (i3 == -1) {
    i3 = *(int *)(player + 0x60);
  }
  f1 = *(float *)(player + PLB_POS_Z);
  f2 = *(float *)(player2 + PLB_POS_Z);
  if (f1 < f2) {
    i4 = *(int *)(player2 + 0x94);
  }
  else {
    i4 = *(int *)(player2 + 0x94);
    if (f1 - f2 <= (float)(stk_2c + i4)) goto L_080b54b9;
    if (f2 < f1) {
      return 0;
    }
  }
  if ((float)(i4 + i3) < f2 - f1) {
    return 0;
  }
L_080b54b9:
  i3 = ClsnArrayDetectRectFlip
                    (*(int **)(*(int *)(*(int *)(player + PLB_ANIM) + 0x10) + 0x28),
                     *(int **)(*(int *)(*(int *)(player2 + PLB_ANIM) + 0x10) + 0x28),
                     (int)X87_FIST32(((float80)*(int *)(player2 + PLB_OFFSET_X) + *(float *)(player2 + PLB_POS_X)) -
                                ((float80)*(int *)(player + PLB_OFFSET_X) + *(float *)(player + PLB_POS_X))),
                     (int)X87_FIST32(((float80)*(int *)(player2 + PLB_OFFSET_Y) + *(float *)(player2 + PLB_POS_Y)) -
                                ((float80)*(int *)(player + PLB_OFFSET_Y) + *(float *)(player + PLB_POS_Y))),
                     stk_24,(uint32_t)(*(int *)(player2 + 400) != 1));
  if ((i3 != 0) &&
     (u5 = *(uint32_t *)(player2 + 0x1164) & *(uint32_t *)(player + 0x1204), (u5 & 7) != 0)) {
    return (uint32_t)((u5 & 0xfffffff8) != 0);
  }
  return 0;
}

/* Player1ReverseP2 @ 0x080b5510, 1408 bytes
 *
 * Applies a reversal: player 1 takes player 2 as a target, both get power,
 * spark and sound play, and player 2 goes into the reversal's p2stateno.
 *
 * Parameters:
 *   player       int *
 *   player2      int *  (player)
 *
 * Player fields read: facing, targets, offset_x, offset_y, pos_x, pos_y,
 *                     pos_z, hitfall, teamside, anim, id
 * Player fields written: sprpriority, movecontact, movereversed, hitcount,
 *                        uniqhitcount, stateno, statetime, ctrl, hitdef
 * Calls: PlayerDropBoundTargets, PlayerFindTarget, ArrayAdd,
 *        PlayerGetWidth, PlayerGetHit, PlayerPowerSet, ComboAdd,
 *        PlayerSparkCreate, KBClearCommandValidTimes, ExplodRemoveGetHit,
 *        PlayerChangeState, AttrMatch
 * Called by: GameClsnUpdate
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: 2 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x50 bytes, 4
 *       variables), because their address is taken.
 * Note: 4 temporaries are float80, as the original kept them in x87 registers.
 */
void Player1ReverseP2(int *player,int *player2)

{
  int i1;
  int i2;
  float80 f3;
  float80 f4;
  float80 f5;
  float80 f6;
  int i7;
  int i8;
  int i9;
  int i10;
  int i11;
  uint8_t b12;
  bool b13;
  uint32_t stale_var;
  int i14;
  int *pi15;
  int width;
  int **ppi17;
  int *pi18;
  unsigned char frame[0x50] __attribute__((aligned(16)));
#define stk_4c (*(uint32_t *)(frame + 0x4))
#define stk_48 (*(int **)(frame + 0x8))
#define stk_3c (*(int **)(frame + 0x14))
#define stk_38 (*(int *)(frame + 0x18))
  
  stk_4c = (uint32_t)(player2[PL_FACING] != 1);
  i14 = player[PL_FACING];
  if (player[0x462] != 0) {
    if (player[0x457] != 0) {
      return;
    }
    PlayerDropBoundTargets((int)player,player2);
    player[0x457] = 1;
  }
  width = 0;
  b12 = 0;
  pi15 = player2;
  do {
    if (7 < width) {
L_080b55b7:
      b13 = (bool)(b12 & player[0x47a] != -1);
      if (!b13) {
        stk_48 = PlayerFindTarget(player[PL_TARGETS],(int)player2);
        if (stk_48 == (int *)0x0) {
          ppi17 = &stk_3c;
          for (width = 8; width != 0; width = width + -1) {
            *ppi17 = (int *)0x0;
            ppi17 = ppi17 + 1;
          }
          stk_38 = player[0x19];
          stk_3c = player2;
          width = ArrayAdd(player[PL_TARGETS],&stk_3c,0,0);
          if (width == -1) {
            return;
          }
          stk_48 = (int *)(width * *(int *)(player[PL_TARGETS] + 4) + *(int *)(player[PL_TARGETS] + 0x14));
        }
        stk_48[6] = 0;
        stk_48[5] = 0;
        stk_48[4] = 0;
        stk_48[3] = 0;
        stk_48[2] = player[0x45a];
      }
      player[PL_SPRPRIORITY] = player[0x47d];
      player2[PL_SPRPRIORITY] = player[0x47e];
      if (player2[PL_FACING] == i14) {
        width = PlayerGetWidth((int)player,2,0);
        width = (-player[0x492] - player2[0x492]) - width;
      }
      else {
        width = PlayerGetWidth((int)player,1,0);
        width = player[0x492] + player2[0x492] + width;
      }
      i7 = player[PL_OFFSET_X];
      i8 = player[PL_FACING];
      i1 = g[0x7311];
      f3 = BITS_I2F(player[0x4d2]);
      f4 = BITS_I2F(player[0x4d5]);
      i9 = player[0x493];
      i10 = player2[0x493];
      i11 = player2[PL_OFFSET_Y];
      i2 = g[0x7312];
      f5 = BITS_I2F(player2[0x4d2]);
      f6 = BITS_I2F(player2[0x4d6]);
      if (!b13) {
        PlayerGetHit(player,player2,(int)(player + PL_HITDEF),BITS_I2F(player[PL_POS_X]),
                     BITS_I2F(player[PL_POS_Y]),BITS_I2F(player[PL_POS_Z]),i14,0,0);
        if ((player2[PL_HITFALL] != 0) || ((*(uint8_t *)(player + 0x474) & 1) != 0)) {
          stk_48[1] = stk_48[1] - player[0x463];
          player[0x463] = 0;
        }
        if (player[0x494] != 0) {
          player[0x65] = -player[PL_FACING];
        }
      }
      player[0x387] = player[0x46b];
      player2[0x387] = player[0x46a];
      PlayerPowerSet((int)player,player[0x466] + *(int *)player[0x5c]);
      player2[PL_MOVECONTACT] = 4;
      player2[PL_MOVEREVERSED] = 0;
      player2[0x400] = 0xfff;
      player2[0x3ff] = 0xfff;
      player2[0x401] = 0;
      player2[0x402] = 0;
      player2[0x3fe] = player[0x46b];
      if ((player[0x459] & 0x1c0U) != 0) {
        player[0x3fe] = player[0x46b];
      }
      player[0x4e6] = player[0x4e6] + player[0x46c];
      player[PL_HITCOUNT] = player[PL_HITCOUNT] + player[0x46c];
      player[PL_UNIQHITCOUNT] = player[PL_UNIQHITCOUNT] + player[0x46c];
      player[PL_MOVECONTACT] = 2;
      player[PL_MOVEREVERSED] = 0;
      ComboAdd(player[PL_TEAMSIDE],player[0x46c]);
      if ((!b13) && ((0 < player[0x4bd] || (player[0x4bd] == -1)))) {
        pi15 = player + 0x4bc;
        pi18 = player2 + 0x977;
        for (i14 = 0xf; i14 != 0; i14 = i14 + -1) {
          *pi18 = *pi15;
          pi15 = pi15 + 1;
          pi18 = pi18 + 1;
        }
      }
      PlayerSparkCreate(player,player[0x48e],
                        (int)X87_FIST32((float)((width - i7) * i8) * f3 + f4 + (float80)i1)
                        ,(int)X87_FIST32((float)((i9 + i10) - i11) * f5 + f6 +
                                    (float80)i2),player[0x48f],stk_4c,0);
      if (!b13) {
        if (player[0x479] != -1) {
          player[PL_STATENO] = player[0x479];
          player[PL_STATETIME] = 0;
        }
        if (player[0x47b] != 0) {
          player2[0x2fb] = player[0x2fa];
          player2[0x2fc] = player[2];
          player2[0x259] = player[0x259];
          KBClearCommandValidTimes(player2 + 0x25a);
          if (player[0x2fb] != 0) {
            player2[0x2fb] = player[0x2fb];
            player2[0x2fc] = player[0x2fc];
          }
          if (player[0x4f0] == 0) {
            player2[0x4f0] = *(int *)player[PL_ANIM];
          }
          else {
            player2[0x4f0] = player[0x4f0];
          }
        }
        if (player[0x47a] != -1) {
          PlayerDropBoundTargets((int)player2,(int *)0x0);
          ExplodRemoveGetHit((uint32_t *)g[0x52be],player2[PL_ID]);
          PlayerChangeState((int)player2,player[0x47a]);
          player2[PL_CTRL] = 0;
        }
        stk_48[6] = player[0x47c];
        stk_48[3] = player[0x499];
        stk_48[4] = player[0x49a];
        stk_48[5] = player[0x49b];
      }
      player2[PL_HITDEF] = 0;
      if (player[0x462] != 0) {
        player[0x457] = 1;
      }
      return;
    }
    if ((pi15[0x42a] != 0) &&
       (b13 = AttrMatch(pi15[0x42b],player[0x459]), ZEXT8(b13) != 0)) {
      b12 = 1;
      goto L_080b55b7;
    }
    pi15 = pi15 + 5;
    width = width + 1;
  } while( true );
}
#undef stk_4c
#undef stk_48
#undef stk_3c
#undef stk_38

/* PlayerCheckHitProj @ 0x080b5a90, 797 bytes
 *
 * Tests a player's attack against enemy projectiles (projectile cancelling
 * by hits).
 *
 * Parameters:
 *   player       int
 *   arg2         int *
 *
 * Player fields read: anim, movetype, teamside, pos_z, offset_x, pos_x,
 *                     offset_y, pos_y
 * Player fields written: hitdef, stateno, statetime
 * Globals read: scaling_topz, scaling_botz, scaling_topscale,
 *               scaling_botscale
 * Calls: ArrayScanFirst, HitdefAffectTeam, ClsnArrayDetectRectFlip,
 *        GameSndPlayIDPos, ArrayScanNext
 * Called by: GameClsnUpdate
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: 6 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 4 temporaries are float80, as the original kept them in x87 registers.
 */
void PlayerCheckHitProj(int player,int *arg2)

{
  float80 f1;
  float80 f2;
  float80 f3;
  float80 f4;
  int array;
  int *pi6;
  int i7;
  int i8;
  int i9;
  bool b10;
  int item;
  uint32_t stale_var;
  int i12;
  int i13;
  int *sounds;
  int i15;
  int i16;
  int i17;
  uint32_t stk_28;
  
  array = *(int *)arg2[0x87];
  stk_28 = (uint32_t)(*(int *)(player + 400) != 1);
  pi6 = *(int **)(*(int *)(*(int *)(player + PLB_ANIM) + 0x10) + 0x28);
  if (((*(char *)(player + 0x11d0) < '\0') && (*(int *)(player + PLB_MOVETYPE) != 0)) &&
     (*(int *)(player + PLB_HITDEF) != 0)) {
    item = ArrayScanFirst(array);
    while (item != 0) {
      i13 = *(int *)(item + 0x34);
      if (*(int *)(item + 4) == 1) {
        b10 = HitdefAffectTeam(player + 0x1158,*(int *)(player + PLB_TEAMSIDE),*(uint32_t *)(item + 8));
        if ((ZEXT8(b10) != 0) && (*(int *)(item + 0x28) < 1)) {
          i12 = (int)X87_FIST32((float80)(int)X87_FIST32(*(float *)(player + PLB_POS_Z)) -
                              *(float *)(item + 0x4c));
          if (i12 < 0) {
            i12 = -i12;
          }
          if ((i12 < 9) && (*(int *)(item + 0x2c) < 1)) {
            i13 = ClsnArrayDetectRectFlip
                               (*(int **)(*(int *)(item + 0x294) + 0x2c),pi6,
                                (int)X87_FIST32(((float80)*(int *)(player + PLB_OFFSET_X) +
                                           *(float *)(player + PLB_POS_X)) - *(float *)(item + 0x44))
                                ,(int)X87_FIST32(((float80)*(int *)(player + PLB_OFFSET_Y) +
                                            *(float *)(player + PLB_POS_Y)) - *(float *)(item + 0x48)
                                           ),(uint32_t)(i13 != 1),stk_28);
            sounds = g;
            if ((i13 != 0) && (0 < *(int *)(item + 0x1c))) {
              i12 = g[G_SCALING_TOPZ];
              i7 = g[G_SCALING_BOTZ];
              f1 = *(float *)(item + 0x4c);
              i8 = *(int *)(item + 0x188);
              i9 = *(int *)(item + 0x34);
              f2 = BITS_I2F(g[G_SCALING_TOPSCALE]);
              f3 = BITS_I2F(g[G_SCALING_BOTSCALE]);
              i13 = g[0x7311];
              f4 = *(float *)(item + 0x44);
              *(uint32_t *)(player + PLB_HITDEF) = 0;
              if (*(int *)(item + 0x108) == 0) {
                i17 = *(int *)(*arg2 + 0x11d0);
                i16 = *(int *)(item + 0x104);
                i15 = *(int *)(item + 0x100);
                sounds = *(int **)(*arg2 + 0x11d4);
              }
              else {
                i17 = 0;
                i16 = *(int *)(item + 0x104);
                i15 = *(int *)(item + 0x100);
                sounds = (int *)sounds[0x4156];
              }
              GameSndPlayIDPos(-1,(int)X87_FIST32((((f4 - (float80)i13) - 160.0) +
                                             (float)(i9 * i8)) *
                                             (((f1 - (float80)i12) / (float)(i7 - i12)) *
                                              (f3 - f2) + f2) + (float80)i13 + 160.0),
                               sounds,i15,i16,i17);
              if (*(int *)(player + 0x11e4) != -1) {
                *(int *)(player + PLB_STATENO) = *(int *)(player + 0x11e4);
                *(uint32_t *)(player + PLB_STATETIME) = 0;
              }
              i13 = *(int *)(item + 0x1c) + -1;
              *(int *)(item + 0x1c) = i13;
              if ((i13 < 1) && (*(int *)(item + 0x38) != 0)) {
                *(uint32_t *)(item + 4) = 2;
                *(uint32_t *)(item + 0x24) = 0;
              }
              else {
                *(uint32_t *)(item + 0x28) = *(uint32_t *)(item + 0xec);
              }
            }
          }
        }
      }
      item = ArrayScanNext(array);
    }
  }
  return;
}

/* PlayerCheckProjHit @ 0x080b5db0, 2475 bytes
 *
 * Tests player 2's projectiles against player 1 and applies the hits:
 * damage, power, spark, sound, hit counters, get-hit or guard state, and the
 * projectile's own hit handling (hit count, hit animation).
 *
 * Parameters:
 *   player       int *
 *   player2      int *  (player)
 *
 * Player fields read: projectiles, facing, teamside, anim, pos_z,
 *                     offset_x, pos_x, offset_y, pos_y, targets, hitfall
 * Player fields written: sprpriority, stateno, statetime, ctrl
 * Globals read: round_no, scaling_topz, scaling_botz, scaling_botscale,
 *               scaling_topscale, stageinfo_zoffset
 * Calls: ArrayScanFirst, HitdefAffectTeam, PlayerCheckAttrHit,
 *        ClsnArrayDetectRectFlip, PlayerCheckFlagHit,
 *        PlayerGetDamagedLife, PlayerGetCorrectedDamage, WinIconCheckTeam,
 *        WinIconCheck, AttrMatch, PlayerFindTarget, ArrayAdd,
 *        PlayerGetHitG, PlayerPowerSet, PlayerSparkCreate, PlayerGetHit,
 *        ComboAdd, PlayerChangeState, KBClearCommandValidTimes,
 *        ArrayScanNext
 * Called by: GameClsnUpdate
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 2 float-field accesses rewritten as bit reinterpretations (asm: x87
 *       single loads/stores at offsets 0x44, 0x48)
 * Note: 2 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: 4 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x80 bytes, 7
 *       variables), because their address is taken.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void PlayerCheckProjHit(int *player,int *player2)

{
  int array;
  int i2;
  int *pi3;
  float80 f4;
  bool b5;
  bool b6;
  bool b7;
  int *item;
  int index;
  uint32_t stale_var;
  int i10;
  uint32_t stale_var_00;
  int i11;
  int *pi12;
  int **ppi13;
  int *pi14;
  unsigned char frame[0x80] __attribute__((aligned(16)));
#define stk_74 (*(uint32_t *)(frame + 0xc))
#define stk_68 (*(uint32_t *)(frame + 0x18))
#define stk_5c (*(uint32_t *)(frame + 0x24))
#define stk_54 (*(int **)(frame + 0x2c))
#define stk_50 (*(int **)(frame + 0x30))
#define stk_3c (*(int **)(frame + 0x44))
#define stk_38 (*(int *)(frame + 0x48))
  
  array = *(int *)player[PL_PROJECTILES];
  stk_5c = (uint32_t)(player2[PL_FACING] != 1);
  i2 = g[player[PL_TEAMSIDE] + G_ROUND_NO];
  pi3 = *(int **)(*(int *)(player2[PL_ANIM] + 0x10) + 0x2c);
  if (player2[0x3fe] < 1) {
    item = (int *)ArrayScanFirst(array);
    while (item != (int *)0x0) {
      pi12 = item + 0x26;
      stk_74 = (uint32_t)(item[0xd] != 1);
      if (((item[1] < 3) && (0 < item[1])) && (item[10] < 1)) {
        index = (int)X87_FIST32((float80)(int)X87_FIST32(BITS_I2F(player2[PL_POS_Z])) - BITS_I2F(item[0x13]));
        if (index < 0) {
          index = -index;
        }
        if (((((index < 9) &&
              (b6 = HitdefAffectTeam((int)pi12,item[2],player2[PL_TEAMSIDE]),
              ZEXT8(b6) != 0)) &&
             ((index = PlayerCheckAttrHit((int)player2,item[0x29]), index != 0 &&
              ((item[0xb] < 1 &&
               (index = ClsnArrayDetectRectFlip
                                  (*(int **)(item[0xa5] + 0x28),pi3,
                                   (int)X87_FIST32(((float80)player2[PL_OFFSET_X] + BITS_I2F(player2[PL_POS_X])) -
                                              (*(float *)&item[0x11])),
                                   (int)X87_FIST32(((float80)player2[PL_OFFSET_Y] + BITS_I2F(player2[PL_POS_Y])) -
                                              (*(float *)&item[0x12])),stk_74,stk_5c), index != 0)))
              ))) && (index = PlayerCheckFlagHit((int)player2,item[0x44]), index != 0)) &&
           (0 < item[7])) {
          b6 = false;
          stk_68 = 0;
          index = PlayerCheckFlagHit((int)player2,item[0x43]);
          if (((index == 0) || (player2[900] == 0)) || (*(char *)((int)player + 0x20b) != '\0')) {
            index = PlayerGetDamagedLife((int)player2);
            i10 = PlayerGetCorrectedDamage(item[0x34],item[0x2f],(int)player2);
            if (index == i10 || index - i10 < 0) {
              WinIconCheckTeam(player2[PL_TEAMSIDE],player[PL_TEAMSIDE],item[0x29]);
L_080b6114:
              stk_68 = 1;
            }
          }
          else {
            index = PlayerGetDamagedLife((int)player2);
            i10 = PlayerGetCorrectedDamage(item[0x35],item[0x30],(int)player2);
            if (index == i10 || index - i10 < 0) {
              stk_68 = 1;
              if ((g[0x7511] != 3) && (i2 < 10)) {
                WinIconCheck(player[PL_TEAMSIDE],0,3);
                goto L_080b6114;
              }
            }
            else {
              b6 = true;
            }
          }
          stk_68 = stk_68 & (g[0x730b] != 0) - 1;
          b5 = false;
          pi14 = player2 + 0x42a;
          for (index = 0; index < 8; index = index + 1) {
            stk_54 = pi14;
            if ((*pi14 != 0) &&
               (b7 = AttrMatch(pi14[1],item[0x29]), ZEXT8(b7) != 0)) {
              b5 = true;
              break;
            }
            pi14 = pi14 + 5;
          }
          if (b5) {
            b6 = false;
            stk_68 = 0;
          }
          else {
            stk_54 = (int *)0x0;
            player2[PL_SPRPRIORITY] = item[0x4e];
            stk_50 = PlayerFindTarget(player[PL_TARGETS],(int)player2);
            if (stk_50 == (int *)0x0) {
              ppi13 = &stk_3c;
              for (index = 8; index != 0; index = index + -1) {
                *ppi13 = (int *)0x0;
                ppi13 = ppi13 + 1;
              }
              stk_3c = player2;
              stk_38 = player[0x19];
              index = ArrayAdd(player[PL_TARGETS],&stk_3c,0,0);
              if (index == -1) goto L_080b6739;
              stk_50 = (int *)(index * *(int *)(player[PL_TARGETS] + 4) +
                                *(int *)(player[PL_TARGETS] + 0x14));
            }
            stk_50[6] = 0;
            stk_50[5] = 0;
            stk_50[4] = 0;
            stk_50[3] = 0;
            if ((*(char *)((int)player + 0x209) == '\0') && (stk_50[1] - item[0x33] < 0))
            goto L_080b6739;
          }
          f4 = ((BITS_I2F(item[0x13]) - (float)g[G_SCALING_TOPZ]) / (float)(g[G_SCALING_BOTZ] - g[G_SCALING_TOPZ])) *
                  (BITS_I2F(g[G_SCALING_BOTSCALE]) - BITS_I2F(g[G_SCALING_TOPSCALE])) + BITS_I2F(g[G_SCALING_TOPSCALE]);
          index = (int)X87_FIST32((((BITS_I2F(item[0x11]) - (float)g[0x7311]) - 160.0) +
                             (float)(item[0xd] * item[0x62])) * f4 + (float)g[0x7311] + 160.0
                            );
          i10 = (int)X87_FIST32(((float80)item[99] + BITS_I2F(item[0x12])) * f4 +
                              BITS_I2F(item[0x13]) + (float)g[G_STAGEINFO_ZOFFSET]);
          if (b6) {
            PlayerGetHitG(player,player2,(int)pi12,item[0xd]);
            PlayerPowerSet((int)player,item[0x37] + *(int *)player[0x5c]);
            PlayerSparkCreate(player,item[0x60],index,i10,item[0x61],stk_74,1);
            player[0x84] = *item;
            player[0x85] = 1;
            player[0x86] = 0;
          }
          else {
            PlayerGetHit(player,player2,(int)pi12,BITS_I2F(item[0x11]),BITS_I2F(item[0x12]),
                         BITS_I2F(item[0x13]),item[0xd],stk_68,(int)stk_54);
            PlayerPowerSet((int)player,item[0x36] + *(int *)player[0x5c]);
            if ((((!b5) && (*(char *)((int)player + 0x209) == '\0')) && (player2[PL_HITFALL] != 0))
               && (item[0x33] != -1)) {
              stk_50[1] = stk_50[1] - item[0x33];
              item[0x33] = 0;
            }
            player[0x4e6] = player[0x4e6] + item[0x3c];
            ComboAdd(player[PL_TEAMSIDE],item[0x3c]);
            player[0x84] = *item;
            player[0x85] = 2;
            player[0x86] = 0;
            player2[0x400] = 0x1ff;
            player2[0x402] = 0;
            if ((!b5) && ((0 < item[0x8d] || (item[0x8d] == -1)))) {
              pi12 = item + 0x8c;
              pi14 = player2 + 0x977;
              for (i11 = 0xf; i11 != 0; i11 = i11 + -1) {
                *pi14 = *pi12;
                pi12 = pi12 + 1;
                pi14 = pi14 + 1;
              }
            }
            PlayerSparkCreate(player,item[0x5e],index,i10,item[0x5f],stk_74,0);
            if (b5) {
              if (stk_54[2] != -1) {
                PlayerChangeState((int)player2,stk_54[2]);
              }
            }
            else {
              if (item[0x49] != -1) {
                player[PL_STATENO] = item[0x49];
                player[PL_STATETIME] = 0;
              }
              if (item[0x4b] != 0) {
                player2[0x2fb] = player[0x2fa];
                player2[0x2fc] = player[2];
                player2[0x259] = player[0x259];
                KBClearCommandValidTimes(player2 + 0x25a);
                if (player[0x2fb] != 0) {
                  player2[0x2fb] = player[0x2fb];
                  player2[0x2fc] = player[0x2fc];
                }
                if (player[0x4f0] == 0) {
                  player2[0x4f0] = *(int *)player[PL_ANIM];
                }
                else {
                  player2[0x4f0] = player[0x4f0];
                }
              }
              if (item[0x4a] != -1) {
                PlayerChangeState((int)player2,item[0x4a]);
                player2[PL_CTRL] = 0;
              }
              stk_50[6] = item[0x4c];
              stk_50[3] = item[0x69];
              stk_50[4] = item[0x6a];
              stk_50[5] = item[0x6b];
            }
          }
          item[0xb1] = 1;
          if ((item[7] == 1 || item[7] + -1 < 0) && (item[0xe] != 0)) {
            item[0xb2] = 0;
            item[0xb3] = 0;
          }
          else {
            item[0xb2] = item[0x3b];
            item[0xb3] = item[0xc];
          }
        }
      }
L_080b6739:
      item = (int *)ArrayScanNext(array);
    }
  }
  return;
}
#undef stk_74
#undef stk_68
#undef stk_5c
#undef stk_54
#undef stk_50
#undef stk_3c
#undef stk_38

/* PlayerProjDoHit @ 0x080b6760, 116 bytes
 *
 * Applies the deferred "has hit" updates to a player's projectiles after the
 * collision pass.
 *
 * Parameters:
 *   player       int
 *
 * Player fields read: projectiles
 * Calls: ArrayScanFirst, ArrayScanNext
 * Called by: GameClsnUpdate
 *
 * Elecbyte file: src/mugen/p-update.c
 */
uint32_t PlayerProjDoHit(int player)

{
  int array;
  int item;
  int i3;
  uint32_t stk_c;
  
  array = **(int **)(player + PLB_PROJECTILES);
  item = ArrayScanFirst(array);
  while (item != 0) {
    if (*(int *)(item + 0x2c4) != 0) {
      *(uint32_t *)(item + 0x2c) = *(uint32_t *)(item + 0x2cc);
      *(uint32_t *)(item + 0x28) = *(uint32_t *)(item + 0x2c8);
      i3 = *(int *)(item + 0x1c) + -1;
      *(uint32_t *)(item + 0x2c4) = 0;
      *(int *)(item + 0x1c) = i3;
      if ((i3 < 1) && (*(int *)(item + 0x38) != 0)) {
        *(uint32_t *)(item + 4) = 4;
        *(uint32_t *)(item + 0x24) = 0;
      }
    }
    item = ArrayScanNext(array);
  }
  return stk_c;
}

/* CheckProjHitProj @ 0x080b67e0, 626 bytes
 *
 * Tests the projectiles of two players against each other and cancels the
 * ones that collide, according to their projpriority.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Calls: ArrayScanFirst, HitdefAffectTeam, ClsnArrayDetectRectFlip,
 *        ArrayScanNext
 * Called by: GameClsnUpdate
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 2 byte results widened with ZEXT8 (upper bytes are zero).
 */
uint32_t CheckProjHitProj(int arg1,int arg2)

{
  int array;
  int array2;
  int i3;
  int *pi4;
  bool b5;
  int item;
  int item2;
  uint32_t stale_var;
  uint32_t stale_var_00;
  int i8;
  
  array = **(int **)(arg1 + 0x21c);
  array2 = **(int **)(arg2 + 0x21c);
  item = ArrayScanFirst(array);
  do {
    if (item == 0) {
      return 0;
    }
    i3 = *(int *)(item + 0x34);
    pi4 = *(int **)(*(int *)(item + 0x294) + 0x2c);
    if ((pi4 != (int *)0x0) && (*(int *)(item + 4) == 1)) {
      item2 = ArrayScanFirst(array2);
      while (item2 != 0) {
        if ((((int)X87_FIST32(*(float *)(item2 + 0x4c)) - (int)X87_FIST32(*(float *)(item + 0x4c))) + 8U <
             0x11) && (*(int *)(item2 + 4) == 1)) {
          b5 = HitdefAffectTeam(item + 0x98,*(int *)(item + 8),*(uint32_t *)(item2 + 8));
          if (ZEXT8(b5) == 0) {
            b5 = HitdefAffectTeam(item2 + 0x98,*(int *)(item2 + 8),*(uint32_t *)(item + 8));
            if (ZEXT8(b5) == 0) goto L_080b6a16;
          }
          i8 = ClsnArrayDetectRectFlip
                            (pi4,*(int **)(*(int *)(item2 + 0x294) + 0x2c),
                             (int)X87_FIST32(*(float *)(item2 + 0x44) - *(float *)(item + 0x44)),
                             (int)X87_FIST32(*(float *)(item2 + 0x48) - *(float *)(item + 0x48)),
                             (uint32_t)(i3 != 1),(uint32_t)(*(int *)(item2 + 0x34) != 1));
          if (i8 != 0) {
            i3 = *(int *)(item2 + 0xc);
            i8 = *(int *)(item + 0xc);
            if (i8 <= i3) {
              *(int *)(item + 0x1c) = *(int *)(item + 0x1c) + -1;
            }
            if (*(int *)(item + 0x1c) < 1) {
              *(uint32_t *)(item + 4) = 3;
              *(uint32_t *)(item + 0x24) = 0;
              *(uint32_t *)(arg1 + 0x214) = 3;
              *(uint32_t *)(arg1 + 0x218) = 0;
            }
            else {
              *(uint32_t *)(item + 0x28) = *(uint32_t *)(item + 0xec);
            }
            if (*(int *)(item2 + 0xc) <= *(int *)(item + 0xc)) {
              *(int *)(item + 0xc) = *(int *)(item + 0xc) + -1;
              *(int *)(item2 + 0x1c) = *(int *)(item2 + 0x1c) + -1;
            }
            if (*(int *)(item2 + 0x1c) < 1) {
              *(uint32_t *)(item2 + 4) = 3;
              *(uint32_t *)(item2 + 0x24) = 0;
              *(uint32_t *)(arg2 + 0x214) = 3;
              *(uint32_t *)(arg2 + 0x218) = 0;
            }
            else {
              *(uint32_t *)(item2 + 0x28) = *(uint32_t *)(item2 + 0xec);
            }
            if (i8 <= i3) {
              *(int *)(item2 + 0xc) = *(int *)(item2 + 0xc) + -1;
            }
            break;
          }
        }
L_080b6a16:
        item2 = ArrayScanNext(array2);
      }
    }
    item = ArrayScanNext(array);
  } while( true );
}

/* PlayerCheckFlagHit @ 0x080b6a60, 149 bytes
 *
 * Returns true if a HitDef's hitflag/guardflag allows hitting a player in
 * its current state type, move type and fall state.
 *
 * Parameters:
 *   player       int
 *   arg2         uint32_t
 *
 * Player fields read: statetype, movetype, hitfall
 * Called by: Player1HitP2, PlayerCheckHit, PlayerCheckProjHit
 *
 * Elecbyte file: src/mugen/p-update.c
 */
uint32_t PlayerCheckFlagHit(int player,uint32_t arg2)

{
  int i1;
  bool b2;
  
  i1 = *(int *)(player + PLB_STATETYPE);
  if ((((i1 != 4) || ((arg2 & 0x40) != 0)) &&
      ((*(int *)(player + PLB_MOVETYPE) != 2 || ((arg2 & 2) != 0)))) &&
     ((((*(int *)(player + PLB_MOVETYPE) == 2 && (*(int *)(player + 0xe10) == 0)) ||
       ((arg2 & 0x100) == 0)) && ((*(int *)(player + PLB_HITFALL) == 0 || ((arg2 & 0x20) != 0)))))
     ) {
    if (i1 == 2) {
      b2 = (arg2 & 8) == 0;
    }
    else if (i1 < 3) {
      if (i1 != 1) {
        return 0;
      }
      b2 = (arg2 & 4) == 0;
    }
    else if (i1 == 3) {
      b2 = (arg2 & 0x10) == 0;
    }
    else {
      if (i1 != 4) {
        return 0;
      }
      b2 = (arg2 & 0x40) == 0;
    }
    if (!b2) {
      return 1;
    }
  }
  return 0;
}

/* PlayerCheckAttrHit @ 0x080b6b00, 24 bytes
 *
 * Returns true if an attack's attributes pass the player's HitBy/NotHitBy
 * restrictions (AttrMatch).
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t
 *
 * Calls: AttrMatch
 * Called by: PlayerCheckHit, PlayerCheckProjHit
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
uint32_t PlayerCheckAttrHit(int arg1,uint32_t arg2)

{
  bool b1;
  uint32_t stale_var;
  
  b1 = AttrMatch(*(uint32_t *)(arg1 + 0x1000) & *(uint32_t *)(arg1 + 0xffc),arg2);
  return ZEXT8(b1);
}

/* AttrMatch @ 0x080b6b20, 30 bytes
 *
 * Returns true if two hit attribute sets intersect in both state type and
 * attack type.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         uint32_t
 *
 * Called by: Player1HitP2, Player1ReverseP2, PlayerCheckAttrHit,
 *            PlayerCheckProjHit
 *
 * Elecbyte file: src/mugen/p-update.c
 */
bool AttrMatch(uint32_t arg1,uint32_t arg2)

{
  if ((arg2 & arg1 & 7) == 0) {
    return false;
  }
  return (arg2 & arg1 & 0xfffffff8) != 0;
}

/* PlayerAttrStateSet @ 0x080b6b40, 90 bytes
 *
 * Updates the player's HitBy/NotHitBy timers for this frame.
 *
 * Parameters:
 *   player       int
 *
 * Player fields read: statetype
 * Called by: PlayerCheckHit
 *
 * Elecbyte file: src/mugen/p-update.c
 */
void PlayerAttrStateSet(int player)

{
  int i1;
  uint32_t u2;
  
  i1 = *(int *)(player + PLB_STATETYPE);
  u2 = *(uint32_t *)(player + 0x1164) & 0xfffffff8;
  *(uint32_t *)(player + 0x1164) = u2;
  if (i1 == 2) {
    *(uint32_t *)(player + 0x1164) = u2 | 2;
    return;
  }
  if (i1 < 3) {
    if (i1 != 1) {
      return;
    }
    *(uint32_t *)(player + 0x1164) = u2 | 1;
    return;
  }
  if (i1 != 3) {
    return;
  }
  *(uint32_t *)(player + 0x1164) = u2 | 4;
  return;
}

/* PlayerDropBoundTargets @ 0x080b6ba0, 183 bytes
 *
 * Releases the targets of a player that are bound to it (TargetBind) or the
 * player that binds it, and returns bound targets to their own states when
 * needed.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int *
 *
 * Player fields read: ishelper
 * Calls: ArrayScanFirst, KBClearCommandValidTimes, PlayerChangeState,
 *        ArrayDelete, ArrayScanNext
 * Called by: GameFreePlayerDependencies, HelperDestroy, Player1HitP2,
 *            Player1ReverseP2, PlayerGetHit, PlayerUpdate
 *
 * Elecbyte file: src/mugen/p-update.c
 */
void PlayerDropBoundTargets(int arg1,int *arg2)

{
  int *player;
  int *item;
  
  item = (int *)ArrayScanFirst(*(int *)(arg1 + 0x220));
  while (item != (int *)0x0) {
    player = (int *)*item;
    if (player != arg2) {
      if ((item[7] != 0) && (player[PL_ISHELPER] == 0)) {
        player[0x259] = *player + 0x11b4;
        player[0x2fb] = 0;
        player[0x2fc] = -1;
        KBClearCommandValidTimes(player + 0x25a);
        player[0x4f0] = 0;
        PlayerChangeState((int)player,0x13ba);
      }
      ArrayDelete(*(int *)(arg1 + 0x220),*(int *)(*(int *)(arg1 + 0x220) + 0x1c));
    }
    item = (int *)ArrayScanNext(*(int *)(arg1 + 0x220));
  }
  return;
}

/* PlayerSparkCreate @ 0x080b6c60, 310 bytes
 *
 * Creates a hit or guard spark explod at the hit position (from fightfx or
 * the player's own animations, the "S" prefix).
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *   arg6         uint32_t
 *   arg7         int
 *
 * Calls: ExplodAdd, AnimGetLooptime
 * Called by: Player1HitP2, Player1ReverseP2, PlayerCheckProjHit,
 *            PlayerSCtrlApplyElem
 *
 * Elecbyte file: src/mugen/p-update.c
 */
int PlayerSparkCreate(int *arg1,int arg2,int arg3,int arg4,int arg5,
                     uint32_t arg6,int arg7)

{
  int i1;
  int i2;
  uint32_t looptime;
  uint32_t *pu4;
  int *pi5;
  
  if (arg2 == -2) {
    if (arg7 == 0) {
      arg2 = arg1[0x4f];
    }
    else {
      arg2 = arg1[0x50];
    }
  }
  if (arg2 == -1) {
    i2 = -1;
  }
  else {
    if (arg5 == 0) {
      i2 = g[0x4147];
      pi5 = (int *)g[0x4148];
      pu4 = (uint32_t *)g[0x52be];
    }
    else {
      i2 = arg1[0x4ed];
      pi5 = *(int **)(*arg1 + 0x11cc);
      pu4 = (uint32_t *)g[0x52be];
    }
    i2 = ExplodAdd(pu4,arg2,pi5,i2);
    if (i2 != -1) {
      i1 = *(int *)g[0x52be] + i2 * 0xe4;
      *(uint32_t *)(i1 + 0x10) = 0;
      *(uint32_t *)(i1 + 0xc) = 0;
      *(uint32_t *)(i1 + 0x6c) = 1;
      *(uint32_t *)(i1 + 0x70) = 1;
      *(uint32_t *)(i1 + 0x5c) = 3;
      *(int *)(i1 + 0x2c) = arg3;
      *(uint32_t *)(i1 + 0x68) = arg6;
      *(int *)(i1 + 0x30) = arg4;
      *(float *)(i1 + 0x14) = (float)arg3;
      *(float *)(i1 + 0x18) = (float)arg4;
      *(uint32_t *)(i1 + 100) = 2;
      looptime = AnimGetLooptime(*(uint32_t **)(i1 + 0x80));
      *(uint32_t *)(i1 + 0x40) = looptime;
      *(uint32_t *)(i1 + 0x38) = looptime;
      *(uint32_t *)(i1 + 0x34) = looptime;
      *(uint32_t *)(*(int *)(i1 + 0x80) + 0x30) = 0;
    }
  }
  return i2;
}

/* PlayerMakeDust @ 0x080b6da0, 415 bytes
 *
 * Creates the dust explods behind a running or landing player (MakeDust
 * controller and automatic dust).
 *
 * Parameters:
 *   player       int
 *
 * Player fields read: pos_y, statetype, movetype, stateno
 * Calls: ExplodAdd, AnimGetLooptime
 * C library: random
 * Called by: GameUpdate
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 4 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 2 temporaries are float80, as the original kept them in x87 registers.
 */
int PlayerMakeDust(int player)

{
  int i1;
  int i2;
  float80 f3;
  float80 f4;
  int64_t l5;
  bool b6;
  int *pi7;
  int i8;
  long l9;
  long l10;
  uint32_t looptime;
  
  b6 = false;
  l5 = (int64_t)g[0x7514] / 3;
  i8 = (int)l5;
  if (g[0x7514] % 3 == 0) {
    f3 = *(float *)(player + PLB_POS_Y);
    i8 = CONCAT22((short)((uint64_t)l5 >> 0x10),
                     (uint16_t)(f3 < 0.0) << 8 | (uint16_t)IS_NAN(f3) << 10 |
                     (uint16_t)(f3 == 0.0) << 0xe);
    if (((((f3 == 0.0) != 0) && (i8 = *(int *)(player + PLB_STATETYPE), i8 != 3)) && (i8 != 4))
       && ((i8 = *(int *)(player + PLB_MOVETYPE), i8 != 0 && (i8 = i8 + -1, i8 != 0)))) {
      b6 = true;
    }
    if (*(int *)(player + PLB_STATENO) == 0x34) {
      b6 = true;
    }
  }
  if (b6) {
    l9 = random();
    i1 = g[0x7311];
    f3 = *(float *)(player + 0x1354);
    l10 = random();
    i2 = g[0x7312];
    f4 = *(float *)(player + 0x1358);
    i8 = ExplodAdd((uint32_t *)g[0x52be],0x78,(int *)g[0x4148],g[0x4147]);
    if (i8 != -1) {
      i8 = *(int *)g[0x52be] + i8 * 0xe4;
      *(float *)(i8 + 0x14) =
           (float80)(int)X87_FIST32(((float)(l9 % 3) + (float80)i1 + f3) - 1.0);
      *(float *)(i8 + 0x18) =
           (float80)(int)X87_FIST32(((float)(l10 % 3) + (float80)i2 + f4) - 1.0);
      *(uint32_t *)(i8 + 0x6c) = 1;
      looptime = AnimGetLooptime(*(uint32_t **)(i8 + 0x80));
      i1 = *(int *)(i8 + 0x80);
      *(uint32_t *)(i8 + 0x40) = looptime;
      pi7 = g;
      *(uint32_t *)(i1 + 0x34) = 10;
      i8 = pi7[0x413d];
      *(int *)(i1 + 0x30) = i8;
    }
  }
  return i8;
}

/* PlayerCalcDraw @ 0x080b6f40, 629 bytes
 *
 * Computes a player's screen position and draw scale from its stage
 * position, z position (stage scaling) and offsets, and applies the screen
 * bound.
 *
 * Parameters:
 *   player       int
 *
 * Player fields read: pos_z, pos_y, pos_x, offset_x, offset_y
 * Globals read: stageinfo_zoffset, scaling_botscale, scaling_topscale,
 *               scaling_topz, scaling_botz
 * Calls: ScreenBound
 * Called by: CameraMoveP, PlayerSCtrlApplyElem, PlayerUpdate,
 *            PlayerUpdateBindTo
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 1 float-field accesses rewritten as bit reinterpretations (asm: x87
 *       single loads/stores at offsets 0x4280)
 * Note: 3 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
int PlayerCalcDraw(int player)

{
  int i1;
  int *pi2;
  int stk_c;
  
  if ((((((int)X87_FIST32(*(float *)(player + PLB_POS_Z)) == *(int *)(player + 0x1364)) &&
        ((int)X87_FIST32(*(float *)(player + PLB_POS_Y)) == *(int *)(player + 0x1360))) &&
       (stk_c = (int)X87_FIST32(*(float *)(player + PLB_POS_X)), stk_c == *(int *)(player + 0x135c)))
      && ((g[0x7311] == *(int *)(player + 0x1368) && (g[0x7312] == *(int *)(player + 0x136c)))))
     && ((g[G_STAGEINFO_ZOFFSET] == *(int *)(player + 0x1370) &&
         ((*(int *)(player + PLB_OFFSET_X) == *(int *)(player + 0x1374) &&
          (*(int *)(player + PLB_OFFSET_Y) == *(int *)(player + 0x1378))))))) {
    if (*(int *)(player + 0x1e4) != 0) {
      ScreenBound(player);
    }
  }
  else {
    *(float *)(player + 0x1348) =
         (BITS_I2F(g[G_SCALING_BOTSCALE]) - BITS_I2F(g[G_SCALING_TOPSCALE])) *
         ((*(float *)(player + PLB_POS_Z) - (float)g[G_SCALING_TOPZ]) / (float)((g[G_SCALING_BOTZ] - g[G_SCALING_TOPZ]) + 1)) +
         (*(float *)&g[G_SCALING_TOPSCALE]);
    if (*(int *)(player + 0x1e4) != 0) {
      ScreenBound(player);
    }
    pi2 = g;
    i1 = g[G_STAGEINFO_ZOFFSET];
    *(float *)(player + 0x1354) =
         ((((float80)*(int *)(player + PLB_OFFSET_X) + *(float *)(player + PLB_POS_X)) - BITS_I2F(g[0x730f])) -
         160.0) * *(float *)(player + 0x1348) + 160.0;
    *(float *)(player + 0x1358) =
         (((float80)*(int *)(player + PLB_OFFSET_Y) + *(float *)(player + PLB_POS_Y)) *
          *(float *)(player + 0x1348) - BITS_I2F(pi2[0x7310])) + *(float *)(player + PLB_POS_Z) +
         (float80)i1;
    *(int *)(player + 0x135c) = (int)X87_FIST32(*(float *)(player + PLB_POS_X));
    *(int *)(player + 0x1360) = (int)X87_FIST32(*(float *)(player + PLB_POS_Y));
    stk_c = (int)X87_FIST32(*(float *)(player + PLB_POS_Z));
    *(int *)(player + 0x1364) = stk_c;
    *(int *)(player + 0x1368) = pi2[0x7311];
    *(int *)(player + 0x136c) = pi2[0x7312];
    *(int *)(player + 0x1370) = pi2[0x4140];
    *(uint32_t *)(player + 0x1374) = *(uint32_t *)(player + PLB_OFFSET_X);
    *(uint32_t *)(player + 0x1378) = *(uint32_t *)(player + PLB_OFFSET_Y);
  }
  return stk_c;
}

/* PlayerDrawAnim @ 0x080b71c0, 499 bytes
 *
 * Draws a player's current animation at its screen position: scaled,
 * flipped, with its blend and palette, rotated when AngleDraw is active, and
 * shaking during a hit shake.
 *
 * Parameters:
 *   player       int
 *   arg2         float
 *
 * Player fields read: movetype, hitshakeover, statetime, anim, pos_z,
 *                     sprpriority
 * Calls: AnimDrawScaleFlip, AnimDrawRotateFlip
 * Called by: ContinueScreenLoop, GameLoop
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 2 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 4 temporaries are float80, as the original kept them in x87 registers.
 */
void PlayerDrawAnim(int player,float arg2)

{
  int i1;
  uint32_t u2;
  uint32_t u3;
  uint32_t u4;
  float80 f5;
  float80 f6;
  float80 f7;
  float80 f8;
  uint32_t u9;
  
  f7 = *(float *)(player + 0x1354) - (float)g[0x7315];
  f5 = *(float *)(player + 0x7c) * *(float *)(player + 0x1348) * *(float *)(player + 0x134c) *
          arg2;
  u9 = (uint32_t)(*(int *)(player + 400) != 1);
  f6 = *(float *)(player + 0x80) * *(float *)(player + 0x1348) * *(float *)(player + 0x1350) *
          arg2;
  f8 = *(float *)(player + 0x1358) - (float)g[0x7316];
  if ((*(int *)(player + PLB_MOVETYPE) == 2) && (0 < *(int *)(player + PLB_HITSHAKEOVER))) {
    f7 = (float80)(int)((*(uint32_t *)(player + PLB_STATETIME) & 1) * *(int *)(player + 400)) + f7;
  }
  *(int *)(*(int *)(player + PLB_ANIM) + 0x34) =
       (int)X87_FIST32(*(float *)(player + PLB_POS_Z) * 10.0 + (float80)*(int *)(player + PLB_SPRPRIORITY));
  i1 = *(int *)(player + PLB_ANIM);
  u2 = *(uint32_t *)(i1 + 0x20);
  *(uint32_t *)(i1 + 0x20) = *(uint32_t *)(player + 5000);
  u3 = *(uint32_t *)(i1 + 0x24);
  *(uint32_t *)(i1 + 0x24) = *(uint32_t *)(player + 0x138c);
  u4 = *(uint32_t *)(i1 + 0x28);
  *(uint32_t *)(i1 + 0x28) = *(uint32_t *)(player + 0x1390);
  if (*(int *)(player + 0x1380) == 0) {
    AnimDrawScaleFlip(*(uint32_t **)(player + PLB_ANIM),(int)X87_FIST32(f7),(int)X87_FIST32(f8),f5,
                      f6,u9);
  }
  else {
    AnimDrawRotateFlip(*(uint32_t **)(player + PLB_ANIM),(int)X87_FIST32(f7),(int)X87_FIST32(f8),
                       *(float *)(player + 0x137c),f5,f6,u9);
  }
  i1 = *(int *)(player + PLB_ANIM);
  *(uint32_t *)(i1 + 0x20) = u2;
  *(uint32_t *)(i1 + 0x24) = u3;
  *(uint32_t *)(i1 + 0x28) = u4;
  return;
}

/* PlayerDrawShadow @ 0x080b73c0, 1507 bytes
 *
 * Draws a player's shadow (darkened, squashed sprite below it) and/or
 * reflection, per the stage settings and the DrawShadows option.
 *
 * Parameters:
 *   player       int
 *   arg2         int *
 *   arg3         int *
 *
 * Player fields read: anim, offset_y, hitshakeover, statetime, pos_y,
 *                     pos_z
 * Globals read: config_drawshadows, video_linux_doubleres,
 *               stageinfo_zoffset
 * Calls: AnimCurSpriteIdx, W_RotateSpriteTransAdd_B,
 *        W_RotateShadowTransSub_P, W_RotateSpriteTransAdd_B_P
 * Called by: ContinueScreenLoop, GameLoop
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to NAN
 * Note: 16 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: 4 temporaries are float80, as the original kept them in x87 registers.
 */
void PlayerDrawShadow(int player,int *arg2,int *arg3)

{
  int i1;
  int *sprites;
  float80 f3;
  float80 f4;
  float80 f5;
  int i6;
  int i7;
  uint8_t b8;
  uint8_t b9;
  uint8_t b10;
  uint32_t u11;
  int i12;
  int i13;
  uint32_t u14;
  float80 f15;
  int stk_44;
  int stk_40;
  
  i1 = *(int *)(*(int *)(player + PLB_ANIM) + 0x10);
  sprites = *(int **)(*(int *)(player + PLB_ANIM) + 4);
  i12 = *(int *)(player + 400);
  b8 = (uint8_t)_rgb_r_shift_16;
  b9 = (uint8_t)_rgb_g_shift_16;
  b10 = (uint8_t)_rgb_b_shift_16;
  if (*(int *)(player + 0x1380) == 0) {
    stk_40 = 0;
  }
  else {
    stk_40 = (int)X87_FIST32((float)-i12 * *(float *)(player + 0x137c));
  }
  stk_44 = *arg2;
  u14 = arg2[1];
  if ((g[G_CONFIG_DRAWSHADOWS] != 0) && (i6 = AnimCurSpriteIdx(*(int *)(player + PLB_ANIM)), i6 != -1)) {
    i7 = *(int *)(i1 + 0x14) + *(int *)(player + PLB_OFFSET_Y);
    f5 = *(float *)(player + 0x7c) * *(float *)(player + 0x1348) * *(float *)(player + 0x134c)
    ;
    f4 = *(float *)(player + 0x80) * *(float *)(player + 0x1348) * *(float *)(player + 0x1350)
    ;
    f3 = ((float80)i12 * (float80)*(int *)(i1 + 0x10) * f5 + *(float *)(player + 0x1354)) -
            (float)g[0x7315];
    if (0 < *(int *)(player + PLB_HITSHAKEOVER)) {
      f3 = (float80)(int)((*(uint32_t *)(player + PLB_STATETIME) & 1) * i12) + f3;
    }
    u11 = (uint32_t)(i12 != 1) ^ *(uint32_t *)(i1 + 0x18) & 3;
    if ((u11 & 1) != 0) {
      f5 = f5 * -1.0;
    }
    if ((u11 & 2) == 0) {
      f4 = f4 * -1.0;
    }
    if (g[G_VIDEO_LINUX_DOUBLERES] == 4) {
      f3 = f3 + f3;
      f5 = f5 + f5;
    }
    i1 = (int)X87_FIST32(f3);
    if (0 < *arg3) {
      f3 = (float)(*(int *)(player + 0xb0) * 2) +
              (((((float)g[G_STAGEINFO_ZOFFSET] -
                 (*(float *)(player + PLB_POS_Y) + (float80)i7) * *(float *)(player + 0x80) *
                 *(float *)(player + 0x1348)) - BITS_I2F(g[0x7310])) + *(float *)(player + PLB_POS_Z)) -
              (float)g[0x7316]);
      if (g[G_VIDEO_LINUX_DOUBLERES] == 4) {
        f3 = f3 + f3;
        f4 = f4 + f4;
      }
      i12 = *arg3;
      i13 = 0x100 - i12;
      if (*(int *)(player + 5000) == 3) {
        i12 = i12 * *(int *)(player + 0x138c) >> 8;
        i13 = i13 + ((0x100 - i13) * *(int *)(player + 0x1390) >> 8);
      }
      W_RotateSpriteTransAdd_B
                (sprites,i6,(float80)i1,(float80)(int)X87_FIST32(f3),(float)stk_40,f5,f4,
                 i12,i13);
    }
    f3 = *(float *)(player + 0x80) * *(float *)(player + 0x1348) * *(float *)(player + 0x1350)
    ;
    f4 = ((((f3 + 1.0) * (float80)*(int *)(player + 0xb0) + *(float *)(player + PLB_POS_Z) +
              (float)g[G_STAGEINFO_ZOFFSET]) -
             (*(float *)(player + PLB_POS_Y) + (float80)i7) * f3 * BITS_I2F(arg2[2])) -
            (float)g[0x7316]) - (float)g[0x7312];
    if ((u11 & 2) == 0) {
      f3 = f3 * -1.0;
    }
    if (g[G_VIDEO_LINUX_DOUBLERES] == 4) {
      f4 = f4 + f4;
      f3 = f3 + f3;
    }
    i12 = 0x100;
    if (*(int *)(player + 5000) == 3) {
      i12 = 0x100 - *(int *)(player + 0x1390);
    }
    i7 = arg2[3];
    i13 = arg2[4];
    if (i7 < i13) {
      f15 = *(float *)(player + PLB_POS_Y);
      if ((float80)i7 < f15) {
        if (f15 < (float80)i13) {
          i12 = (int)X87_FIST32(((float80)i12 * (f15 - (float80)i7)) / (float)(i13 - i7));
        }
      }
      else {
        i12 = 0;
      }
    }
    if (i12 < 0x100) {
      u14 = ((int)((u14 & 0x1f) * i12) >> 8 & 0x1fU) +
               ((int)((u14 & 0xf800) * i12) >> 8 & 0xf800U) +
               ((int)((u14 & 0x7e0) * i12) >> 8 & 0x7e0U);
      stk_44 = i12 * stk_44 >> 8;
    }
    if ((u14 == (0x1f << (b8 & 0x1f) | 0x3f << (b9 & 0x1f) | 0x1f << (b10 & 0x1f))) ||
       (stk_44 == 0x100)) {
      stk_44 = 0;
      f15 = BITS_I2F(arg2[2]);
    }
    else {
      if (u14 != 0) {
        W_RotateShadowTransSub_P
                  (sprites,i6,(float80)i1,(float80)(int)X87_FIST32(f4),(float)stk_40,f5,f3,
                   1.0,BITS_I2F(arg2[2]),u14);
      }
      if (stk_44 < 1) {
        return;
      }
      stk_44 = 0x100 - stk_44;
      f15 = BITS_I2F(arg2[2]);
    }
    W_RotateSpriteTransAdd_B_P
              (sprites,i6,(float80)i1,(float80)(int)X87_FIST32(f4),(float)stk_40,f5,f3,1.0,
               f15,0,stk_44);
  }
  return;
}

/* PlayerDrawClsn @ 0x080b79b0, 2725 bytes
 *
 * Debug display: draws a player's collision boxes (attack and body boxes in
 * different blends, and the push width), its axis, and its name and state
 * number ("%s, %i").
 *
 * Parameters:
 *   player       int
 *   arg2         float
 *
 * Player fields read: anim, pos_x, pos_y, statetype, hitdef, targets
 * Calls: V_FontDraw, GameClsnDraw, W_BoxTransSub16, W_BoxFillTransAdd16,
 *        W_BoxTransAdd16, W_PutPixelXor16, W_HLineTransAdd16,
 *        W_VLineTransAdd16, ArrayScanFirst, ArrayScanNext
 * C library: sprintf, builtin_strncpy, makecol, strcat
 * Called by: GameLoop
 * Messages:
 *   "%s, %i"
 *
 * Elecbyte file: src/mugen/p-update.c
 * Note: 1 accesses to parts of a variable are written as sized accesses.
 * Note: 10 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x190 bytes,
 *       5 variables), because their address is taken.
 * Note: 2 temporaries are float80, as the original kept them in x87 registers.
 */
void PlayerDrawClsn(int player,float arg2)

{
  int i1;
  char *pc2;
  uint32_t u3;
  uint32_t u4;
  float80 f5;
  float80 f6;
  bool b7;
  int i8;
  uint32_t u9;
  int *item;
  char *pc11;
  uint32_t u12;
  char *pc13;
  uint32_t u14;
  char *pc15;
  char *dest;
  int i16;
  int i17;
  unsigned char frame[0x190] __attribute__((aligned(16)));
#define stk_188 (*(int *)(frame + 0x8))
#define stk_174 (*(int *)(frame + 0x1c))
#define stk_15c (*(char (*)[64])(frame + 0x34))
#define text (*(char (*)[4])(frame + 0x74))
#define stk_118 (*(uint32_t *)(frame + 0x78))
  
  i16 = *(int *)(*(int *)(player + PLB_ANIM) + 0x10);
  u9 = (uint32_t)(*(int *)(player + 400) != 1);
  b7 = false;
  i1 = (int)X87_FIST32((*(float *)(player + 0x1354) - (float)g[0x7315]) * arg2);
  pc2 = (char *)(int)X87_FIST32((*(float *)(player + 0x1358) - (float)g[0x7316]) * arg2);
  u14 = *(uint32_t *)(player + 0x1000) & *(uint32_t *)(player + 0xffc);
  if (i16 == 0) {
    return;
  }
  i17 = *(int *)(i16 + 0x28);
  i16 = *(int *)(i16 + 0x2c);
  sprintf(text,"%c%c%c|%c%c%c|%c%c%c|%c%c%c",(((u14 & 1) == 0) - 1 & 0xffffffcd) + 0x53,
          (((u14 & 2) == 0) - 1 & 0xffffffdd) + 0x43,
          (((u14 & 4) == 0) - 1 & 0xffffffdf) + 0x41,
          (((u14 & 8) == 0) - 1 & 0xffffffd2) + 0x4e,
          (((u14 & 0x10) == 0) - 1 & 0xffffffcd) + 0x53,
          (((u14 & 0x20) == 0) - 1 & 0xffffffd8) + 0x48,
          (((u14 & 0x40) == 0) - 1 & 0xffffffd2) + 0x4e,
          ((-1 < (char)u14) - 1 & 0xffffffcd) + 0x53,
          (((u14 & 0x100) == 0) - 1 & 0xffffffd8) + 0x48,
          (((u14 & 0x200) == 0) - 1 & 0xffffffd2) + 0x4e,
          (((u14 & 0x400) == 0) - 1 & 0xffffffcd) + 0x53,
          (((u14 & 0x800) == 0) - 1 & 0xffffffd8) + 0x48,i17,i17);
  if ((((u14 & 7) == 0) || (0 < *(int *)(player + 0xff8))) || ((u14 & 0xff8) == 0)) {
    builtin_strncpy(text,"MUTE",4);
    stk_118 = CONCAT13((*(uint8_t *)((char *)&stk_118 + 3)),0x494b);
    b7 = true;
  }
  if (u14 != 0xfff) {
    b7 = true;
  }
  if (b7) {
    u14 = makecol(0xff,0xff,0xd4);
    V_FontDraw(text,(int *)g[0x413a],i1 + -0x1c,(int)(pc2 + -2),u14);
    u14 = 0x1f << ((uint8_t)_rgb_g_shift_16 & 0x1f);
    i8 = 0xf;
  }
  else {
    if (*(int *)(player + 0xe10) == 0) {
      u14 = 0x1f << ((uint8_t)_rgb_b_shift_16 & 0x1f);
      goto L_080b7c5d;
    }
    u14 = 8 << ((uint8_t)_rgb_r_shift_16 & 0x1f);
    i8 = 0x18;
  }
  u14 = u14 | i8 << ((uint8_t)_rgb_b_shift_16 & 0x1f);
L_080b7c5d:
  f5 = (float80)(int)pc2;
  f6 = (float80)i1;
  GameClsnDraw(i16,f6,f5,*(float *)(player + 0x1348) * arg2,
               *(float *)(player + 0x1348) * arg2,u14,u9,(uint32_t)(g[0x81d0] == 2));
  GameClsnDraw(i17,f6,f5,*(float *)(player + 0x1348) * arg2,
               *(float *)(player + 0x1348) * arg2,0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f),u9,
               (uint32_t)(g[0x81d0] == 2));
  stk_188 = 0;
  i16 = player;
  do {
    if (*(float *)(i16 + 0x31d0) != -32760.0) {
      u9 = (uint32_t)X87_FIST32(((float80)*(int *)(player + 400) * *(float *)(i16 + 0x31d0) + f6 +
                          (float80)*(int *)(player + 0x2ec4)) - *(float *)(player + PLB_POS_X));
      u14 = (uint32_t)X87_FIST32(((float80)*(int *)(player + 0x2ec8) + f5 + *(float *)(i16 + 0x31e0))
                           - *(float *)(player + PLB_POS_Y));
      u3 = (uint32_t)X87_FIST32(((float80)*(int *)(player + 400) * *(float *)(i16 + 0x31f0) + f6 +
                          (float80)*(int *)(player + 0x2ec4)) - *(float *)(player + PLB_POS_X));
      u4 = (uint32_t)X87_FIST32((f5 + *(float *)(i16 + 0x3200) + (float80)*(int *)(player + 0x2ec8))
                          - *(float *)(player + PLB_POS_Y));
      W_BoxTransSub16(u9,u14,u3,u4,
                      4 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 8 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                      4 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
      if (g[0x81d0] == 2) {
        if (stk_188 == 0) {
          u12 = 8 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 8 << ((uint8_t)_rgb_b_shift_16 & 0x1f);
        }
        else {
          u12 = 0x10 << ((uint8_t)_rgb_g_shift_16 & 0x1f);
        }
        W_BoxFillTransAdd16(u9,u14,u3,u4,u12);
      }
      else {
        if (stk_188 == 0) {
          u12 = 8 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 8 << ((uint8_t)_rgb_b_shift_16 & 0x1f);
        }
        else {
          u12 = 0x10 << ((uint8_t)_rgb_g_shift_16 & 0x1f);
        }
        W_BoxTransAdd16(u9,u14,u3,u4,u12);
      }
    }
    i16 = i16 + 0x40;
    stk_188 = stk_188 + 1;
  } while (stk_188 < 2);
  W_PutPixelXor16(i1,(int)pc2);
  W_PutPixelXor16(i1 + -1,(int)pc2);
  W_PutPixelXor16(i1 + 1,(int)pc2);
  W_PutPixelXor16(i1,(int)(pc2 + -1));
  W_PutPixelXor16(i1,(int)(pc2 + 1));
  if (*(int *)(player + 400) == 1) {
    if (*(int *)(player + PLB_STATETYPE) == 3) {
      i16 = *(int *)(player + 0x8c);
      i17 = *(int *)(player + 0x90);
    }
    else {
      i16 = *(int *)(player + 0x84);
      i17 = *(int *)(player + 0x88);
    }
    pc15 = (char *)(i16 + *(int *)(player + 0x1f8));
    stk_174 = i17 + *(int *)(player + 500);
    i16 = i16 + *(int *)(player + 0x200);
    i17 = i17 + *(int *)(player + 0x1fc);
  }
  else {
    if (*(int *)(player + PLB_STATETYPE) == 3) {
      i17 = *(int *)(player + 0x8c);
      i16 = *(int *)(player + 0x90);
    }
    else {
      i17 = *(int *)(player + 0x84);
      i16 = *(int *)(player + 0x88);
    }
    stk_174 = i17 + *(int *)(player + 0x1f8);
    pc15 = (char *)(i16 + *(int *)(player + 500));
    i16 = i16 + *(int *)(player + 0x1fc);
    i17 = i17 + *(int *)(player + 0x200);
  }
  dest = (char *)(int)X87_FIST32((float80)i16 * arg2);
  i16 = (int)X87_FIST32((float80)i17 * arg2);
  u14 = i1 + i16;
  u9 = i1 - (int)dest;
  W_HLineTransAdd16(u9,u14,(uint32_t)pc2,
                    8 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x1f << ((uint8_t)_rgb_g_shift_16 & 0x1f));
  pc13 = pc2 + 1;
  pc11 = pc2 + -1;
  W_VLineTransAdd16(u9,(uint32_t)pc11,(uint32_t)pc13,
                    8 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x1f << ((uint8_t)_rgb_g_shift_16 & 0x1f));
  W_VLineTransAdd16(u14,(uint32_t)pc11,(uint32_t)pc13,
                    8 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x1f << ((uint8_t)_rgb_g_shift_16 & 0x1f));
  if (pc15 != dest) {
    W_VLineTransAdd16(i1 - (int)pc15,(uint32_t)pc11,(uint32_t)pc13,
                      0xf << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x10 << ((uint8_t)_rgb_g_shift_16 & 0x1f)
                     );
  }
  if (stk_174 != i16) {
    W_VLineTransAdd16(i1 + stk_174,(uint32_t)pc11,(uint32_t)pc13,
                      0xf << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x10 << ((uint8_t)_rgb_g_shift_16 & 0x1f)
                     );
  }
  if ((int)dest < (int)pc15) {
    W_HLineTransAdd16(u9,i1 - (int)pc15,(uint32_t)pc2,
                      0xf << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x10 << ((uint8_t)_rgb_g_shift_16 & 0x1f)
                     );
    dest = pc2;
  }
  if (i16 < stk_174) {
    W_HLineTransAdd16(u14,i1 + stk_174,(uint32_t)pc2,
                      0xf << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x10 << ((uint8_t)_rgb_g_shift_16 & 0x1f)
                     );
  }
  i16 = *(int *)(player + 4);
  sprintf(text,"%s, %i",player + 0x20,i16);
  if (*(int *)(player + PLB_HITDEF) != 0) {
    strcat(text," H");
  }
  V_FontDraw(text,(int *)g[0x413a],i1 + -0x14,(int)(pc2 + 6),
             0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
             0x1f << ((uint8_t)_rgb_b_shift_16 & 0x1f));
  if (0 < *(int *)(*(int *)(player + PLB_TARGETS) + 8)) {
    builtin_strncpy(text,"Targ",4);
    stk_118 = 0x207465;
    item = (int *)ArrayScanFirst(*(int *)(player + PLB_TARGETS));
    if (item != (int *)0x0) {
      do {
        i17 = *item;
        if (i17 == 0) {
L_080b8385:
          b7 = false;
        }
        else {
          i16 = *(int *)(i17 + 0x158);
          b7 = true;
          if (i16 == 0) goto L_080b8385;
        }
        if (b7) {
          sprintf(stk_15c,"%i",*(uint32_t *)(i17 + 4),dest);
          strcat(text,stk_15c);
        }
        sprintf(stk_15c," %i",item[1],i16);
        dest = text;
        strcat(dest,stk_15c);
        item = (int *)ArrayScanNext(*(int *)(player + PLB_TARGETS));
        if (item == (int *)0x0) break;
        strcat(dest,", ");
      } while( true );
    }
    u9 = makecol(0xff,0xc0,0xff);
    V_FontDraw(text,(int *)g[0x413a],i1 + -0x14,(int)(pc2 + 0xc),u9);
  }
  return;
}
#undef stk_188
#undef stk_174
#undef stk_15c
#undef text
#undef stk_118

