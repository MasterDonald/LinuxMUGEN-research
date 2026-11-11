/*
 * helper.c -- helpers
 * Creation, removal and lookup of helper players.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/helper.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* HelperMake @ 0x080980d0, 2140 bytes
 *
 * Creates a helper for `player` from a Helper state controller. It takes a
 * free player slot, makes a player record sharing the owner's character
 * data, gives it its own sprite palette instance and copies the controller's
 * parameters: name ("%s's helper" by default), id, position relative to the
 * owner or a target, facing, state number, key control, own palette, size
 * and screen-bound overrides. Then it enables the helper and puts it in its
 * start state. Errors: "illegal helper stateno", "negative helper ID".
 * Returns the helper or NULL.
 *
 * Parameters:
 *   player       int *
 *   arg2         char *
 *   arg3         int *
 *
 * Player fields read: active, anim, projectiles, var, fvar
 * Player fields written: id, pos_x, pos_y, teamside, facing, pos_z
 * Globals read: next_player_id
 * Calls: PlayerEnableSet, EvalExpressionI, SpriteArrayNewInstanceOnto,
 *        PalGrpFlagIsNonZero, PalGrpRemove, PalGrpAddSpr, EvalExpressionF,
 *        PlayerReset, Warn, PlayerChangeState, KBISetFlip,
 *        PlayerNearestEnemy
 * C library: sprintf, strcpy
 * Called by: PlayerSCtrlApplyElem
 * Messages:
 *   "%s\'s helper"
 *   "illegal helper stateno"
 *   "negative helper ID"
 *   "illegal helper pausemovetime"
 *   "illegal helper supermovetime"
 *
 * Elecbyte file: src/mugen/helper.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: rewrote 2 PalGrpFlag by-value loads
 * Note: 4 data addresses refer to the data image (data/mugen_data.S).
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
int * HelperMake(int *player,char *arg2,int *arg3)

{
  uint32_t *pu1;
  int i2;
  int *player2;
  int value2;
  int *pi5;
  int value3;
  int *pi7;
  int saved_EDI;
  int *pi8;
  float80 value4;
  int stk_20;
  
  pi7 = (int *)*arg3;
  player2 = (int *)0x0;
  if (4 < g[0x7395]) {
    player2 = (int *)g[0x73de];
    value2 = player2[PL_ACTIVE];
    value3 = 5;
    while ((value2 != 0 && (player2 = (int *)0x0, value3 + 1 <= g[0x7395]))) {
      player2 = (int *)g[value3 + 0x73da];
      value2 = player2[PL_ACTIVE];
      value3 = value3 + 1;
    }
  }
  if (player2 == (int *)0x0) {
    return (int *)0x0;
  }
  value2 = *player;
  *player2 = value2;
  player2[0x259] = value2 + 0x11b4;
  player2[0x2fa] = player[0x2fa];
  PlayerEnableSet(player2[2],1);
  value2 = EvalExpressionI((int)player,arg2 + 0x80,0);
  if (value2 == 0) {
    value3 = player[0x4eb];
  }
  else {
    pi5 = SpriteArrayNewInstanceOnto((int *)player2[0x4ec],(int *)player[0x4ed]);
    if (pi5 == (int *)0x0) {
      return (int *)0x0;
    }
    value3 = player2[0x4ec];
  }
  player2[0x4eb] = value3;
  pu1 = (uint32_t *)player2[PL_ANIM];
  value3 = *player2;
  player2[0x4ed] = player[0x4ed];
  *pu1 = *(uint32_t *)(value3 + 0x11cc);
  pu1[1] = player2[0x4eb];
  i2 = player2[PL_PROJECTILES];
  *(uint32_t *)(i2 + 4) = *(uint32_t *)(value3 + 0x11cc);
  *(int *)(i2 + 8) = player2[0x4ed];
  if (value2 != 0) {
    saved_EDI = player2[0x976];
    value2 = PalGrpFlagIsNonZero(*(PalGrpFlag *)(player2 + 0x972));
    if (value2 != 0) {
      PalGrpRemove(*(PalGrpFlag *)(player2 + 0x972));
      saved_EDI = player2[0x974];
      PalGrpAddSpr(player2[0x4eb],player2[0x972],player2[0x973],saved_EDI,player2[0x975],player2[0x976]);
    }
  }
  if (*arg2 == '\0') {
    sprintf((char *)(player2 + 8),"%s\'s helper",player + 8,saved_EDI);
  }
  else {
    strcpy((char *)(player2 + 8),arg2);
  }
  pi5 = g;
  player2[PL_ID] = g[G_NEXT_PLAYER_ID];
  pi5[0x749d] = pi5[0x749d] + 1;
  pi5 = player + 0x14;
  pi8 = player2 + 0x14;
  for (value2 = 0x42; value2 != 0; value2 = value2 + -1) {
    *pi8 = *pi5;
    pi5 = pi5 + 1;
    pi8 = pi8 + 1;
  }
  value4 = EvalExpressionF(player,(int *)(arg2 + 0xa4));
  if (value4 != -32760.0) {
    player2[0x1f] = BITS_F2I(int, value4);
  }
  value4 = EvalExpressionF(player,(int *)(arg2 + 0xb0));
  if (value4 != -32760.0) {
    player2[0x20] = BITS_F2I(int, value4);
  }
  value2 = EvalExpressionI((int)player,arg2 + 0xbc,1);
  if (value2 != -0x7fef) {
    player2[0x21] = value2;
  }
  value2 = EvalExpressionI((int)player,arg2 + 200,1);
  if (value2 != -0x7fef) {
    player2[0x22] = value2;
  }
  value2 = EvalExpressionI((int)player,arg2 + 0xd4,1);
  if (value2 != -0x7fef) {
    player2[0x23] = value2;
  }
  value2 = EvalExpressionI((int)player,arg2 + 0xe0,1);
  if (value2 != -0x7fef) {
    player2[0x24] = value2;
  }
  value2 = EvalExpressionI((int)player,arg2 + 0xec,1);
  if (value2 != -0x7fef) {
    player2[0x26] = value2;
  }
  value2 = EvalExpressionI((int)player,arg2 + 0xf8,1);
  if (value2 != -0x7fef) {
    player2[0x27] = value2;
  }
  value2 = EvalExpressionI((int)player,arg2 + 0x104,1);
  if (value2 != -0x7fef) {
    player2[0x28] = value2;
  }
  value2 = EvalExpressionI((int)player,arg2 + 0x110,1);
  if (value2 != -0x7fef) {
    player2[0x29] = value2;
  }
  value2 = EvalExpressionI((int)player,arg2 + 0x11c,1);
  if (value2 != -0x7fef) {
    player2[0x2a] = value2;
  }
  value2 = EvalExpressionI((int)player,arg2 + 0x128,1);
  if (value2 != -0x7fef) {
    player2[0x2b] = value2;
  }
  value2 = EvalExpressionI((int)player,arg2 + 0x134,1);
  if (value2 != -0x7fef) {
    player2[0x2c] = value2;
  }
  PlayerReset(player2);
  pi5 = player2 + PL_VAR;
  for (value2 = 0x3c; value2 != 0; value2 = value2 + -1) {
    *pi5 = 0;
    pi5 = pi5 + 1;
  }
  pi5 = player2 + PL_FVAR;
  for (value2 = 0x28; value2 != 0; value2 = value2 + -1) {
    *pi5 = 0;
    pi5 = pi5 + 1;
  }
  value2 = EvalExpressionI((int)player,arg2 + 0x68,1);
  if (value2 < 0) {
    value2 = 0;
    Warn((int)player,(int)&str_illegal_helper_stateno_8834);
  }
  PlayerChangeState((int)player2,value2);
  player2[PL_POS_X] = player[PL_POS_X];
  player2[PL_POS_Y] = player[PL_POS_Y];
  player2[PL_TEAMSIDE] = player[PL_TEAMSIDE];
  player2[600] = player[600];
  value2 = EvalExpressionI((int)player,arg2 + 0x74,0);
  player2[0x8f] = (uint32_t)(value2 == 0);
  value2 = EvalExpressionI((int)player,arg2 + 0x74,0);
  if (value2 != 0) {
    pi5 = player + 0x92;
    pi8 = player2 + 0x92;
    for (value2 = 0x2f; value2 != 0; value2 = value2 + -1) {
      *pi8 = *pi5;
      pi5 = pi5 + 1;
      pi8 = pi8 + 1;
    }
    pi5 = player + 0xc1;
    pi8 = player2 + 0xc1;
    for (value2 = 0x197; value2 != 0; value2 = value2 + -1) {
      *pi8 = *pi5;
      pi5 = pi5 + 1;
      pi8 = pi8 + 1;
    }
  }
  value2 = EvalExpressionI((int)player,arg2 + 0x30,1);
  if (value2 < 0) {
    value2 = 0;
    Warn((int)player,(int)&str_negative_helper_id_884b);
  }
  player2[0x986] = value2;
  player2[0x988] = (int)player;
  player2[0x987] = player[PL_ID];
  pi5 = (int *)player[0x989];
  if ((int *)player[0x989] == (int *)0x0) {
    pi5 = player;
  }
  player2[0x989] = (int)pi5;
  player2[0x98a] = *(int *)(arg2 + 0x3c);
  player2[PL_FACING] = 1;
  value3 = *(int *)(arg2 + 0x58);
  switch(value3) {
  case 0:
L_case_080986a1_0:
    pi7 = player;
    break;
  case 1:
  case 2:
    player2[PL_FACING] = player[PL_FACING];
    value3 = *(int *)(arg2 + 0x58);
  case 3:
  case 4:
    if ((((value3 == 2) && (player[PL_FACING] == 1)) || ((value3 == 1 && (player[PL_FACING] == -1)))) ||
       (value3 == 3)) {
      value2 = g[0x7311];
    }
    else {
      value2 = g[0x7311] + 0x140;
    }
    stk_20 = 0;
    goto L_default_080986a1;
  case 5:
    if (pi7 == (int *)0x0) goto L_case_080986a1_0;
    break;
  default:
    goto L_default_080986a1;
  }
  value2 = (int)X87_FIST32(BITS_I2F(pi7[0x67]));
  stk_20 = (int)X87_FIST32(BITS_I2F(pi7[0x68]));
  player2[PL_FACING] = pi7[100];
L_default_080986a1:
  value3 = EvalExpressionI((int)player,arg2 + 0x40,1);
  player2[PL_POS_X] = BITS_F2I(int, (float)(value3 * player2[PL_FACING] + value2));
  value2 = EvalExpressionI((int)player,arg2 + 0x4c,1);
  player2[PL_POS_Y] = BITS_F2I(int, (float)(value2 + stk_20));
  player2[PL_POS_Z] = player[PL_POS_Z];
  value2 = EvalExpressionI((int)player,arg2 + 0x5c,1);
  if (value2 == -1) {
    player2[PL_FACING] = -player2[PL_FACING];
  }
  KBISetFlip((int)(player2 + 0x92),(uint32_t)(player2[PL_FACING] == -1));
  if (player2[0x98a] != 1) {
    player2[0x79] = 0;
    player2[0x7b] = 0;
    player2[0x7a] = 0;
    player2[0x7c] = 0;
  }
  value2 = EvalExpressionI((int)player,arg2 + 0x98,1);
  if (value2 < 0) {
    value2 = 0;
    Warn((int)player,(int)&str_illegal_helper_pausemovetime_885e);
  }
  player2[0x77] = value2;
  value2 = EvalExpressionI((int)player,arg2 + 0x8c,1);
  if (value2 < 0) {
    value2 = 0;
    Warn((int)player,(int)&str_illegal_helper_supermovetime_887b);
  }
  player2[0x78] = value2;
  player2[0x3ff] = 0;
  player2[0x401] = 1;
  value2 = PlayerNearestEnemy((int)player2);
  *(uint8_t *)(player2 + 0x83) = 0;
  pi7 = g;
  player2[0xd09] = value2;
  player2[0x81] = 0;
  player2[0x82] = 0;
  pi7[player2[2] + 0x749e] = 1;
  pi7[0x74de] = 1;
  return player2;
}

/* HelperDestroy @ 0x08098930, 411 bytes
 *
 * Removes a helper (DestroySelf, or the owner leaving): drops its bindings
 * and targets, releases its palette group and slot, and disables it.
 *
 * Parameters:
 *   arg1         int
 *
 * Globals read: slot_first, slot_last
 * Calls: PlayerDropBoundTargets, PalGrpFlagIsNonZero, PalGrpRemove,
 *        PlayerEnableSet
 * Called by: GameFreePlayerDependencies, GameRoundUpdate,
 *            PlayerSCtrlApplyElem
 *
 * Elecbyte file: src/mugen/helper.c
 * Note: rewrote 4 PalGrpFlag by-value loads
 */
void HelperDestroy(int arg1)

{
  int i1;
  bool b2;
  int *pi3;
  int i4;
  int i5;
  
  if (*(int *)(arg1 + 0x1c) == 1) {
    PlayerDropBoundTargets(arg1,(int *)0x0);
    pi3 = g;
    i4 = g[G_SLOT_FIRST];
    if (i4 <= g[G_SLOT_LAST]) {
      i5 = i4 * 4 + 0x1cf60;
      do {
        i1 = *(int *)(i5 + 4 + (int)pi3);
        if ((i1 == 0) || (b2 = true, *(int *)(i1 + 0x158) == 0)) {
          b2 = false;
        }
        if (((b2) && (*(int *)(i1 + 0x3454) == arg1)) && (*(int *)(i1 + 0x3430) != 0)) {
          *(uint32_t *)(i1 + 0x3430) = 0;
          *(uint32_t *)(i1 + 0x3454) = 0;
        }
        i4 = i4 + 1;
        i5 = i5 + 4;
      } while (i4 <= pi3[0x745a]);
    }
    i4 = *(int *)(arg1 + 0x1394);
    if (i4 != 0) {
      *(uint32_t *)(i4 + 0x18) = 0;
      *(uint32_t *)(i4 + 8) = 0;
      *(uint32_t *)(arg1 + 0x1394) = 0;
    }
    i4 = PalGrpFlagIsNonZero(*(PalGrpFlag *)(arg1 + 0x25c8));
    if (i4 != 0) {
      PalGrpRemove(*(PalGrpFlag *)(arg1 + 0x25c8));
      PalGrpRemove(*(PalGrpFlag *)(arg1 + 0x25c8));
      PalGrpRemove(*(PalGrpFlag *)(arg1 + 0x25c8));
    }
    *(uint32_t *)(arg1 + 0x13b4) = 0;
    *(uint32_t *)(arg1 + 0x13ac) = 0;
    PlayerEnableSet(*(int *)(arg1 + 8),0);
  }
  return;
}

/* HelperParent @ 0x08098ad0, 40 bytes
 *
 * Returns the helper's parent player, or NULL when the parent no longer
 * exists (its id changed). Non-helpers return NULL. Used by the parent
 * redirection.
 *
 * Parameters:
 *   player       int
 *
 * Player fields read: ishelper
 * Called by: PlayerGetRedirInfo, SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/helper.c
 */
uint32_t HelperParent(int player)

{
  if (*(int *)(player + PLB_ISHELPER) != 1) {
    return 0;
  }
  return *(uint32_t *)(player + 0x2620) &
         (*(int *)(*(uint32_t *)(player + 0x2620) + 4) != *(int *)(player + 0x261c)) - 1;
}

/* HelperRoot @ 0x08098b00, 11 bytes
 *
 * Returns the root player (the original character) of a helper.
 *
 * Parameters:
 *   player       int
 *
 * Called by: PlayerGetRedirInfo, SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/helper.c
 */
uint32_t HelperRoot(int player)

{
  return *(uint32_t *)(player + 0x2624);
}

/* HelperCount @ 0x08098b10, 153 bytes
 *
 * Counts the active helpers of the same root as `player` with id `helper_id`
 * (any id when -1). The NumHelper trigger.
 *
 * Parameters:
 *   player       int
 *   helper_id    int
 *
 * Globals read: slot_first, slot_last
 * Called by: SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/helper.c
 */
int HelperCount(int player,int helper_id)

{
  int i1;
  bool b2;
  int i3;
  int i4;
  int *pi5;
  int i6;
  
  i6 = 0;
  i4 = g[G_SLOT_FIRST];
  if (i4 <= g[G_SLOT_LAST]) {
    pi5 = g + i4 + 0x73d9;
    i3 = i4 * 4 + 0x1cf60;
    do {
      i1 = *(int *)(i3 + 4 + (int)g);
      if ((i1 == 0) || (b2 = true, *(int *)(i1 + 0x158) == 0)) {
        b2 = false;
      }
      if (b2) {
        i1 = *pi5;
        if ((((*(int *)(i1 + 0x2624) == player) ||
             (*(int *)(i1 + 0x2624) == *(int *)(player + 0x2624))) &&
            (*(int *)(i1 + 0x1c) == 1)) &&
           ((*(int *)(i1 + 0x2618) == helper_id || (helper_id == 0)))) {
          i6 = i6 + 1;
        }
      }
      i4 = i4 + 1;
      pi5 = pi5 + 1;
      i3 = i3 + 4;
    } while (i4 <= g[G_SLOT_LAST]);
  }
  return i6;
}

/* HelperAccessID @ 0x08098bb0, 151 bytes
 *
 * Returns the first active helper of the same root as `player` whose id is
 * `id`, or NULL. Used by the helper(id) redirection.
 *
 * Parameters:
 *   player       int
 *   id           int
 *
 * Globals read: slot_first, slot_last
 * Called by: SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/helper.c
 */
uint32_t HelperAccessID(int player,int id)

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
      if (b2) {
        i1 = *pi5;
        if (((*(int *)(i1 + 0x2624) == player) ||
            (*(int *)(i1 + 0x2624) == *(int *)(player + 0x2624))) &&
           (*(int *)(i1 + 0x1c) == 1)) {
          if (*(int *)(i1 + 0x2618) == id) {
            return i1;
          }
          if (id == 0) {
            return i1;
          }
        }
      }
      i3 = i3 + 1;
      pi5 = pi5 + 1;
      i4 = i4 + 4;
    } while (i3 <= g[G_SLOT_LAST]);
  }
  return 0;
}

