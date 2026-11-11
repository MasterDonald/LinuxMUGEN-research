/*
 * p-input.c -- player input
 * Per-frame key and command processing for each player.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/p-input.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* PlayerKBUpdate @ 0x080abd40, 2328 bytes
 *
 * Per-frame input processing for one player. It reads the player's key
 * buffer (KBIGetch), refreshes key states, ages the command timers, records
 * hold states, and runs command detection (KBFillBuffer,
 * KBGetCommandSpecial) on new key events. It also handles the debug keys
 * that act on players. AI-controlled players get their keys from PlayerAI
 * instead. Nothing happens during passive fight screens.
 *
 * Parameters:
 *   player       int *
 *
 * Player fields read: hitpausetime, statetype, movetype, ctrl, stateno,
 *                     teamside, teamside, movetype, projectiles, pos_y,
 *                     anim
 * Player fields written: vel_z, vel_x
 * Globals read: round_round_time, video_linux_doubleres,
 *               round_over_wintime, frame_count
 * Calls: KBIGetch, GameModeInPassiveFightScreen, MasterPalMul,
 *        KBIRefreshKeyflags, KBIClearKeyflags, KBUpdateHold,
 *        KBCountdownCommandValidTimes, KBFillBuffer, KBGetCommandSpecial,
 *        PlayerAIProcessCommands, PlayerInGuardDist,
 *        KBClearCommandValidTimes, PlayerChangeState, PlayerTurnAround,
 *        AnimCurIDno, PlayerSelfAnim
 * Called by: GameUpdate
 *
 * Elecbyte file: src/mugen/p-input.c
 * Note: 2 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void PlayerKBUpdate(int *player)

{
  float80 d1;
  bool b2;
  bool b3;
  uint32_t stale_var;
  int i4;
  uint32_t stale_var_00;
  int player2;
  int *pi6;
  int i7;
  int *pi8;
  uint32_t stk_28;
  int stk_24;
  uint32_t stk_1c;
  int stk_18;
  
  b2 = false;
  pi6 = player + 0x92;
  stk_28 = KBIGetch((int)pi6);
  if (player[0x98b] == 0) {
    b3 = GameModeInPassiveFightScreen();
    pi8 = g;
    if ((ZEXT8(b3) == 0) &&
       ((((g[0x7511] == 1 || ((g[0x7511] == 0 && (2 < g[0x7514])))) && (stk_28 - 5 < 6)) &&
        ((g[0x750e] <= g[G_ROUND_ROUND_TIME] + 2 && (g[0x7517] == 0)))))) {
      i4 = ((g[G_VIDEO_LINUX_DOUBLERES] == 4) - 1 & 0xfffffff6) + 0x14;
      g[0x7517] = 1;
      pi8[0x730c] = 1;
      pi8[0x730d] = 0;
      pi8[0x730e] = i4;
      if (1 < pi8[0x7506]) {
        pi8[0x730e] = i4 * 2;
      }
    }
    if (((pi8[0x33b7] - 5U < 2) && (pi8[0x7541] == 1)) && (stk_28 - 5 < 6)) {
      pi8[0x7541] = 2;
      pi8[0x7542] = 0;
    }
    b3 = GameModeInPassiveFightScreen();
    if (((ZEXT8(b3) == 0) && (g[0x7511] == 4)) &&
       ((g[G_ROUND_OVER_WINTIME] < g[0x7514] && ((g[0x7514] < g[0x7510] + -0x11 && (stk_28 - 5 < 6)))))) {
      g[0x7511] = 4;
      MasterPalMul(0x100,0x100,0x100);
      pi8 = g;
      g[0x7514] = g[0x7510] + -0x11;
      pi8[0x7518] = 1;
    }
  }
  if (player[0x57] != 0) {
    return;
  }
  if (player[0x989] == 0) {
    i4 = player[0x8f];
  }
  else {
    if (player[0x8f] != 0) {
      return;
    }
    i4 = 0;
  }
  if (i4 == 0) {
    if (player[0x90] != 0) {
      KBIRefreshKeyflags((int)pi6,player[600]);
      player[0x90] = 0;
    }
  }
  else {
    stk_28 = 0;
    KBIClearKeyflags((int)pi6);
    player[0x90] = 1;
  }
  if (g[0x74df] == 0) {
    return;
  }
  stk_1c = 0xffffffff;
  if (0 < player[PL_HITPAUSETIME]) {
    player[0x254] = 1;
  }
  if (player[0x8f] == 0) {
    KBUpdateHold((int)(player + 0xc1),(int)pi6);
  }
  else {
    player[0x255] = 0;
  }
  stk_24 = 0;
  i4 = g[0x74f3];
  if (((i4 != -1) && (player[i4 + 0x77] == 0)) &&
     (g[i4 * 9 + 0x74fa] < g[i4 * 9 + 0x74fc])) {
    stk_24 = 2;
  }
  if (player[0x254] == 0) {
    KBCountdownCommandValidTimes((int)(player + 0x25a),'\x01',stk_24);
  }
  i4 = player[0x989];
  if ((i4 == 0) || (*(int *)(i4 + 0x262c) == 0)) {
    KBFillBuffer((int)pi6,(int)(player + 0xc1),stk_28,g[G_FRAME_COUNT]);
  }
  else {
    i7 = player[0x254];
    pi6 = (int *)(i4 + 0x304);
    pi8 = player + 0xc1;
    for (player2 = 0x197; player2 != 0; player2 = player2 + -1) {
      *pi8 = *pi6;
      pi6 = pi6 + 1;
      pi8 = pi8 + 1;
    }
    player[0x254] = i7;
  }
  i4 = player[0x243];
  KBGetCommandSpecial((int)(player + 0x25a),(int *)player[0x259],(int)(player + 0xc1),g[G_FRAME_COUNT],1
                     );
  pi6 = g;
  player[0x243] = i4;
  KBGetCommandSpecial((int)(player + 0x25a),(int *)(*player + 0x11b4),(int)(player + 0xc1),
                      pi6[0x7304],2);
  PlayerAIProcessCommands((int)player);
  if (((player[PL_HITPAUSETIME] == 0) && (g[player[2] + 0x749e] != 0)) && (player[0x254] == 1)) {
    player[0x254] = 0;
  }
  pi6 = g;
  i4 = player[PL_STATETYPE];
  if (i4 == 1) {
    i7 = player[0xb2];
    if (i7 == 0) {
      player2 = player[0xb4];
    }
    else {
      player2 = player[0xb4];
      if (player2 == 0) {
        stk_1c = 1;
      }
    }
    if ((player2 != 0) && (i7 == 0)) {
      stk_1c = 1;
    }
    if (player[0xb3] != 0) {
      stk_1c = 0xb;
    }
    if ((player[0xb1] != 0) && (stk_1c = 7, i7 != 0)) {
      stk_1c = 7;
    }
    if ((player[0xb1] != 0) && (player2 != 0)) {
      stk_1c = 7;
    }
  }
  if ((i4 == 2) && (player[0xb3] != 0)) {
    b2 = true;
  }
  if ((i4 == 3) && (stk_28 == 1)) {
    stk_1c = 10;
  }
  player[900] = 0;
  if ((pi6[0x731d] == 0) && (player[0xb4] != 0)) {
    if (player[PL_MOVETYPE] == 0) {
      if ((player[PL_CTRL] == 0) && (i4 = player[PL_STATENO], i4 != 0x34)) goto L_080ac226;
    }
    else {
      i4 = player[PL_STATENO];
L_080ac226:
      if ((i4 != 0x97) && ((i4 != 0x99 && (i4 != 0x9b)))) goto L_080ac33a;
    }
    i4 = player[PL_STATETYPE];
    if (((i4 != 1) || ((char)player[0x81] == '\0')) &&
       ((((i4 != 2 || (*(char *)((int)player + 0x205) == '\0')) &&
         ((i4 != 3 || (*(char *)((int)player + 0x206) == '\0')))) &&
        ((player[0xb1] == 0 && (stk_24 = pi6[0x7459], stk_24 <= pi6[0x745a])))))) {
      i4 = stk_24 * 4 + 0x1cf60;
      i7 = i4;
      do {
        pi8 = *(int **)(i7 + 4 + (int)pi6);
        if (player != pi8) {
          if ((pi8 == (int *)0x0) || (b3 = true, pi8[0x56] == 0)) {
            b3 = false;
          }
          if (b3) {
            player2 = *(int *)(i4 + 4 + (int)pi6);
            if (((*(int *)(player2 + PLB_TEAMSIDE) != player[PL_TEAMSIDE]) && (*(int *)(player2 + PLB_TEAMSIDE) != 0)) &&
               ((*(int *)(player2 + PLB_MOVETYPE) == 1 || (0 < *(int *)(**(int **)(player2 + PLB_PROJECTILES) + 8))))) {
              player[900] = 1;
              player2 = PlayerInGuardDist((int)player,player2);
              pi6 = g;
              if (player2 != 0) {
                stk_1c = 0x28;
              }
            }
          }
        }
        stk_24 = stk_24 + 1;
        i4 = i4 + 4;
        i7 = i7 + 4;
      } while (stk_24 <= pi6[0x745a]);
    }
  }
L_080ac33a:
  if (player[0xb2] != 0) {
    stk_1c = stk_1c | (player[0xb4] == 0) - 1;
  }
  if (player[0x91] != 0) {
    stk_1c = 0xffffffff;
    KBClearCommandValidTimes(player + 0x25a);
    b2 = false;
  }
  if (stk_1c == 10) {
    if (((player[PL_CTRL] != 0) && (0 < player[0x74])) &&
       ((float80)player[0x45] < -BITS_I2F(player[PL_POS_Y]))) {
      PlayerChangeState((int)player,0x2d);
      player[0x74] = player[0x74] + -1;
    }
    goto L_080ac5ce;
  }
  if ((int)stk_1c < 0xb) {
    if (stk_1c == 1) {
      if (((player[PL_CTRL] == 0) || (*(char *)((int)player + 0x20a) != '\0')) ||
         (player[PL_STATENO] == 0x14)) goto L_080ac5ce;
      i4 = 0x14;
    }
    else {
      if (stk_1c != 7) goto L_080ac590;
      if ((player[PL_CTRL] == 0) || (g[0x7511] == 3)) goto L_080ac5ce;
      i4 = 0x28;
    }
  }
  else {
    if (stk_1c == 0x28) {
      if ((player[PL_MOVETYPE] == 0) && (player[PL_CTRL] != 0)) {
        i4 = player[PL_STATENO];
        if ((2 < i4 - 0x82U) && ((i4 != 0x78 && (i4 != 0x8c)))) {
          if ((player[PL_STATETYPE] != 3) && (player[PL_VEL_Z] = 0, player[PL_STATENO] != 100)) {
            player[PL_VEL_X] = 0;
          }
          PlayerChangeState((int)player,0x78);
        }
        player[900] = 1;
      }
      goto L_080ac5ce;
    }
    if ((int)stk_1c < 0x29) {
      if (stk_1c == 0xb) {
        if (player[PL_CTRL] == 0) goto L_080ac5ce;
        if (player[PL_STATENO] != 100) {
          player[PL_VEL_X] = 0;
        }
        player[PL_VEL_Z] = 0;
        if (player[PL_STATENO] - 10U < 2) goto L_080ac5ce;
        i4 = 10;
        goto L_080ac5c5;
      }
    }
    else if (stk_1c == 900) {
      PlayerTurnAround((int)player);
      i4 = AnimCurIDno((uint32_t *)player[PL_ANIM]);
      if (i4 != 5) {
        PlayerSelfAnim(player,5);
      }
      goto L_080ac5ce;
    }
L_080ac590:
    if (player[PL_STATENO] == 0x14) {
      PlayerChangeState((int)player,0);
    }
    if (((player[PL_STATETYPE] != 2) || (player[PL_CTRL] == 0)) || (b2)) goto L_080ac5ce;
    i4 = 0xc;
  }
L_080ac5c5:
  PlayerChangeState((int)player,i4);
L_080ac5ce:
  if ((stk_28 != 0) && (player[PL_MOVETYPE] == 2)) {
    if (player[PL_STATETYPE] == 4) {
      d1 = (double)player[0x411] * 0.75;
    }
    else {
      if (player[0x40c] < 1) {
        return;
      }
      d1 = (double)player[0x411] * ((double)0.9);
    }
    stk_18 = (int)X87_FIST32(d1);
    player[0x411] = stk_18;
  }
  return;
}

