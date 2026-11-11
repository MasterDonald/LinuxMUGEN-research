/*
 * gameloop.c -- fight loop
 * The fight loop: per-frame update and drawing order, rounds, camera, input
 * and debug keys, fight screen bars and combo counters, afterimage hooks,
 * continue screen and debug display.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/gameloop.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"

extern uint8_t framestep_0 __asm__("D_08287a70"); /* file-static 0x08287a70 */

/* GameLoop @ 0x0808fdc0, 4927 bytes
 *
 * Runs the fight until the match ends or the player quits. Each frame it:
 * - handles input and pause (GameInputUpdate);
 * - updates the game (GameUpdate), explods, PalFX and the camera;
 * - draws the stage background, shadows, players, projectiles, explods,
 * afterimages and foreground in priority order, then the fight screen (bars,
 * round texts, combo), the debug display and collision boxes (when enabled)
 * and the training menu;
 * - copies the frame to the screen with frame skipping (DrawToScreen);
 * - waits for the frame timer.
 *
 * It also handles reloading the stage between arcade matches, the precache
 * thread, music pause and resume, and the speed test.
 *
 * Parameters:
 *   arg1         int
 *
 * Globals read: speedtest, video_linux_doubleres, backbuffer, slot_last,
 *               slot_first, demo_mode, demo_mode_fight_bars_display,
 *               stresstest
 * Globals written: frameskip
 * Calls: V_SetBuf, W_Cls, W_Define, FrameSkipReset, PrecacheIsRunning,
 *        PrecacheRequestCancel, PrecacheFinish, MasterPalReset,
 *        GameRoundReset, GameReloadStage, GameModeInPassiveFightScreen,
 *        BGMPause, BGMResume, BGMPoll, BGArraySetViewScale,
 *        PRSprArrayClear, GameInputUpdate, PalGrpResetPalette,
 *        PalGrpMakeFlag, PalGrpSetMul, PalFXUpdate, PalGrpFlagIsNonZero,
 *        GameUpdate, ExplodArrayUpdate, ...
 * C library: sprintf
 * Called by: ArcadeWinScreen, GamePlay, SurvivalResultsScreen
 *
 * Elecbyte file: src/mugen/gameloop.c
 * Note: decompiler flag: stack slots read outside the declared parameters
 *       (entry_stack variables)
 * Note: rewrote 1 PalGrpFlag by-value loads
 * Note: 3 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: PalGrpMakeFlag result written into the argument area: given explicit
 *       temporaries pgf_fffffb88
 * Note: Locals live in `frame`, laid out as on the original stack (0x440 bytes,
 *       2 variables), because their address is taken.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t GameLoop(int arg1)

{
  PalGrpFlag pgf_fffffb88;
  int *pi1;
  int i2;
  int i3;
  PalGrpFlag f;
  PalGrpFlag f_00;
  uint32_t u4;
  bool b5;
  uint32_t stale_var;
  int i6;
  uint32_t stale_var_00;
  uint32_t *pu7;
  float80 f8;
  uint32_t stale_var_01;
  int i9;
  uint8_t b10;
  uint8_t b11;
  bool b12;
  int *pi13;
  int i14;
  int i4;
  int i16;
  uint32_t entry_stack_fffffb88;
  uint32_t entry_stack_fffffb8c;
  uint32_t u17;
  int *text;
  int *font;
  int i20;
  unsigned char frame[0x440] __attribute__((aligned(16)));
#define buf_43c (*(int (*)[256])(frame + 0x4))
#define stk_3c (*(PalGrpFlag (*)[2])(frame + 0x404))
  
  u4 = _rgb_r_shift_16;
  text = g;
  g[0x33b7] = arg1;
  text[0x4135] = 0;
  b10 = (uint8_t)_rgb_g_shift_16;
  b11 = (uint8_t)_rgb_b_shift_16;
  text[0x7316] = 0;
  text[0x7315] = 0;
  if (text[0x7559] == 4) {
    text = (int *)text[0x4138];
  }
  else {
    text = (int *)text[0x4136];
  }
  V_SetBuf(text,0);
  W_Cls(0);
  font = (int *)0x0;
  text = (int *)0x0;
  u17 = 0x808fe84;
  W_Define(0,0,V_Width - 1,V_Height - 1);
  FrameSkipReset();
  pi13 = g;
  if (g[G_SPEEDTEST] == 0) goto L_0808fec1;
  g[G_FRAMESKIP] = 2000;
  pi13[0x82d2] = 1;
  i9 = pi13[0x7304];
  do {
    if (9999 < i9) {
L_080910a2:
      i9 = PrecacheIsRunning();
      if ((i9 != 0) && ((g[0x4135] != 0 || (g[0x33b3] == 0)))) {
        PrecacheRequestCancel();
        PrecacheFinish();
      }
      g[0x33b7] = 0;
      FrameSkipReset();
      MasterPalReset();
      return 1;
    }
L_0808fee6:
    if (pi13[0x82d4] != 0) {
      PrecacheRequestCancel();
      PrecacheFinish();
      GameRoundReset();
      pi13 = g;
      g[0x82d4] = 0;
    }
    if (pi13[0x82d5] != 0) {
      PrecacheRequestCancel();
      PrecacheFinish();
      i9 = GameReloadStage();
      if (i9 == 0) {
        return 0;
      }
      g[0x82d5] = 0;
    }
    b5 = GameModeInPassiveFightScreen();
    if (ZEXT8(b5) == 0) {
      if ((g[0x10ae] == 0) && (*(char *)((int)g + 0x1d391) != '\0')) {
        BGMPause(g + 0x10aa);
      }
      if ((g[0x10ae] != 0) && (*(char *)((int)g + 0x1d391) == '\0')) {
        BGMResume(g + 0x10aa);
      }
    }
    BGMPoll(g + 0x10aa);
    if (g[G_VIDEO_LINUX_DOUBLERES] == 4) {
      V_SetBuf((int *)g[G_BACKBUFFER],0);
      BGArraySetViewScale(g[0x6ed4],1);
    }
    PRSprArrayClear((int *)g[0x413d]);
    pi13 = g;
    i9 = g[0x7315];
    i14 = g[0x7311];
    i16 = g[0x7316];
    i2 = g[0x7312];
    if (g[0x7309] == 0) {
      pi1 = g + 0x7503;
      i4 = 1;
      g[0x74f3] = -1;
      if (*pi1 < 1) {
        do {
          i4 = i4 + -1;
          if (i4 < 0) goto L_0809008d;
        } while (g[i4 * 9 + 0x74fa] < 1);
        g[0x74f3] = i4;
      }
      else {
        pi13[0x74f3] = 1;
      }
    }
L_0809008d:
    GameInputUpdate();
    pi13 = g;
    i4 = g[0x750c];
    if ((0 < i4) && (g[0x7309] == 0)) {
      if (0 < g[0x750d]) {
        i4 = -100;
      }
      g[0x750d] = g[0x750d] + i4;
    }
    if (pi13[0x7309] == 0) {
      PalGrpResetPalette();
      pi13 = g;
    }
    pi1 = g;
    if (((pi13[0x7309] == 0) && (i4 = pi13[0x74f3], i4 != -1)) &&
       (0 < pi13[i4 * 9 + 0x74fa])) {
      if (pi13[0x750d] == 0) {
        pi13[i4 * 9 + 0x74fa] = pi13[i4 * 9 + 0x74fa] + -1;
        pi13 = pi1;
      }
      if ((pi13[i4 * 9 + 0x74fa] != 0) && (pi13[i4 * 9 + 0x74f9] != 0)) {
        PalGrpMakeFlag(stk_3c,0xb00,0);
        f.w[1] = stk_3c[0].w[1];
        f.w[0] = stk_3c[0].w[0];
        f.w[2] = stk_3c[0].w[2];
        f.w[3] = stk_3c[0].w[3];
        f.w[4] = stk_3c[0].w[4];
        entry_stack_fffffb88 = stk_3c[0].w[1];
        entry_stack_fffffb8c = stk_3c[0].w[2];
        PalGrpSetMul(f,0x50,0x50,0x80);
        font = (int *)g[i4 * 9 + 0x74f5];
        text = (int *)g[i4 * 9 + 0x74f4];
        u17 = 0x80901cd;
        f_00.w[1] = (uint32_t)font;
        f_00.w[0] = (uint32_t)text;
        f_00.w[2] = g[i4 * 9 + 0x74f6];
        f_00.w[3] = g[i4 * 9 + 0x74f7];
        f_00.w[4] = g[i4 * 9 + 0x74f8];
        PalGrpSetMul(f_00,0x80,0x80,0xc0);
      }
    }
    i20 = 1;
    i4 = 0;
    PalGrpMakeFlag(&pgf_fffffb88,0x100,0);
    PalFXUpdate(g + 0x6ed5,pgf_fffffb88.w[0],pgf_fffffb88.w[1],pgf_fffffb88.w[2],pgf_fffffb88.w[3],pgf_fffffb88.w[4],i4,i20);
    i4 = g[G_SLOT_LAST];
    text = g;
    if (g[G_SLOT_FIRST] <= i4) {
      i20 = i4 * 4 + 0x1cf60;
      do {
        i6 = *(int *)(i20 + 4 + (int)text);
        if ((i6 == 0) || (b5 = true, *(int *)(i6 + 0x158) == 0)) {
          b5 = false;
        }
        if ((b5) &&
           (i6 = PalGrpFlagIsNonZero(*(PalGrpFlag *)(*(int *)(i20 + 4 + (int)text) + 0x25c8)),
           text = g, i6 != 0)) {
          i6 = 0;
          if ((g[0x74f3] == -1) ||
             (*(int *)(*(int *)(i20 + 4 + (int)g) + 0x1dc + g[0x74f3] * 4) != 0)) {
            i6 = 1;
          }
          i3 = *(int *)((int)g + i20 + 4);
          PalFXUpdate((int *)(*(int *)((int)g + i20 + 4) + 0x25dc),*(int *)(i3 + 0x25c8),
                      *(int *)(i3 + 0x25cc),*(int *)(i3 + 0x25d0),*(int *)(i3 + 0x25d4),
                      *(int *)(i3 + 0x25d8),0,i6);
          text = g;
        }
        i4 = i4 + -1;
        i20 = i20 + -4;
      } while (text[0x7459] <= i4);
    }
    text = text + 0x6ee4;
    u17 = 0x8090340;
    font = (int *)stk_3c[0].w[0];
    PalFXUpdate(text,stk_3c[0].w[0],stk_3c[0].w[1],stk_3c[0].w[2],stk_3c[0].w[3],
                stk_3c[0].w[4],1,1);
    i4 = GameUpdate();
    if (i4 == 0) {
      if (g[0x7309] == 0) {
        ExplodArrayUpdate((int *)g[0x52bf]);
      }
      b5 = GameModeInPassiveFightScreen();
      if ((((ZEXT8(b5) == 0) || ((g[0x7541] == 0 && (g[0x7542] == 1)))) &&
          ((g[0x74f3] == -1 || (g[g[0x74f3] * 9 + 0x74fb] == 0)))) &&
         ((g[0x7309] == 0 && (g[0x750d] == 0)))) {
        BGArrayUpdate(g[0x6ed4]);
      }
      if (((g[0x7309] == 0) && (g[0x750d] == 0)) && (0 < g[0x4146])) {
        g[0x4146] = g[0x4146] + -1;
      }
      b5 = false;
      if ((g[0x52bd] != 0) && ((char)g[0x74e5] == '\0')) {
        b5 = true;
      }
      if (g[G_DEMO_MODE] != 0) {
        b5 = (bool)(b5 & g[G_DEMO_MODE_FIGHT_BARS_DISPLAY] != 0);
      }
      if (g[0x7307] == 0) {
        MasterPalProcessChanges();
        if (g[0x4146] == 0) {
          if (*(char *)((int)g + 0x1d395) == '\0') {
            GameBGDraw();
          }
          else {
            W_Cls(0);
          }
          if (g[G_VIDEO_LINUX_DOUBLERES] == 4) {
            i4 = V_BufGetSurface((int *)g[0x4138],0);
            font = (int *)0x0;
            text = (int *)g[G_BACKBUFFER];
            u17 = 0x80904b7;
            pu7 = (uint32_t *)V_BufGetSurface(text,0);
            V_DoubleRes(pu7,i4);
          }
        }
        if (g[G_VIDEO_LINUX_DOUBLERES] == 4) {
          BGArraySetViewScale(g[0x6ed4],2);
          V_SetBuf((int *)g[0x4138],0);
        }
      }
      if (b5) {
        GameBarsDraw(0);
      }
      GameBarsUpdate();
      if ((g[0x7307] == 0) && (g[0x4146] == 0)) {
        if (*(char *)((int)g + 0x1d392) == '\0') {
          i4 = g[G_SLOT_LAST];
          text = g;
          if (g[G_SLOT_FIRST] <= i4) {
            i20 = i4 * 4 + 0x1cf60;
            do {
              i6 = *(int *)(i20 + 4 + (int)text);
              if ((i6 == 0) || (b12 = true, *(int *)(i6 + 0x158) == 0)) {
                b12 = false;
              }
              if (((b12) &&
                  (i6 = *(int *)((int)text + i20 + 4), *(char *)(i6 + 0x208) == '\0'))
                 && (*(int *)(i6 + 0x198) != 0)) {
                PlayerDrawShadow(*(int *)((int)text + i20 + 4),text + 0x10a4,
                                 text + 0x10a9);
                text = g;
              }
              i4 = i4 + -1;
              i20 = i20 + -4;
            } while (text[0x7459] <= i4);
          }
          i4 = text[0x745a];
          if (text[0x7459] <= i4) {
            i20 = i4 * 4 + 0x1cf60;
            i6 = i20;
            do {
              i3 = *(int *)(i6 + 4 + (int)text);
              if ((i3 == 0) || (b12 = true, *(int *)(i3 + 0x158) == 0)) {
                b12 = false;
              }
              if (b12) {
                ProjArrayDrawShadow(*(int **)(*(int *)(i20 + 4 + (int)text) + 0x21c));
                text = g;
              }
              i4 = i4 + -1;
              i20 = i20 + -4;
              i6 = i6 + -4;
            } while (text[0x7459] <= i4);
          }
          ExplodArrayDrawShadow((int *)text[0x52be]);
        }
        if (g[G_VIDEO_LINUX_DOUBLERES] == 4) {
          f8 = 2.0;
        }
        else {
          f8 = 1.0;
        }
        font = (int *)0x2;
        text = (int *)g[0x413c];
        u17 = 0x8090672;
        AnimPerArrayDrawScaleGrp(text,2,-(i9 + i14),-(i16 + i2),f8);
      }
      if (g[0x7307] == 0) {
        if ((0 < g[0x4146]) && (g[0x4144] != 0)) {
          W_Cls(g[0x4145]);
        }
        i4 = g[G_SLOT_FIRST];
        pi13 = g;
        if (i4 <= g[G_SLOT_LAST]) {
          i20 = i4 * 4 + 0x1cf60;
          do {
            i6 = *(int *)(i20 + 4 + (int)pi13);
            if ((i6 == 0) || (b12 = true, *(int *)(i6 + 0x158) == 0)) {
              b12 = false;
            }
            if ((b12) && (*(int *)(*(int *)((int)pi13 + i20 + 4) + 0x198) != 0)) {
              PlayerDrawAnim(*(int *)((int)pi13 + i20 + 4),1.0);
              pi13 = g;
            }
            i4 = i4 + 1;
            i20 = i20 + 4;
          } while (i4 <= pi13[0x745a]);
        }
        i4 = pi13[0x745a];
        if (pi13[0x7459] <= i4) {
          i20 = i4 * 4 + 0x1cf60;
          i6 = i20;
          do {
            i3 = *(int *)(i6 + 4 + (int)pi13);
            if ((i3 == 0) || (b12 = true, *(int *)(i3 + 0x158) == 0)) {
              b12 = false;
            }
            if (b12) {
              ProjArrayDraw(*(int **)(*(int *)(i20 + 4 + (int)pi13) + 0x21c));
              pi13 = g;
            }
            i4 = i4 + -1;
            i20 = i20 + -4;
            i6 = i6 + -4;
          } while (pi13[0x7459] <= i4);
        }
        ExplodArrayDraw((int *)pi13[0x52be],0);
        i4 = g[G_SLOT_LAST];
        pi13 = g;
        if (g[G_SLOT_FIRST] <= i4) {
          i20 = i4 * 4 + 0x1cf60;
          do {
            i6 = *(int *)(i20 + 4 + (int)pi13);
            if ((i6 == 0) || (b12 = true, *(int *)(i6 + 0x158) == 0)) {
              b12 = false;
            }
            if (b12) {
              PlayerAftImgDraw(*(int *)(i20 + 4 + (int)pi13));
              ProjArrayAftImgDraw(*(int **)(*(int *)((int)g + i20 + 4) + 0x21c));
              pi13 = g;
            }
            i4 = i4 + -1;
            i20 = i20 + -4;
          } while (pi13[0x7459] <= i4);
        }
        if (pi13[0x7559] == 4) {
          PRSprArrayScale((int *)pi13[0x413d],2.0);
          pi13 = g;
        }
        PRSprArrayDraw((int *)pi13[0x413d]);
        ExplodArrayDraw((int *)g[0x52be],1);
      }
      if (b5) {
        GameBarsDraw(1);
      }
      if ((g[0x7307] == 0) && (*(char *)((int)g + 0x1d396) == '\0')) {
        GameFGDraw();
      }
      GameRoundDraw();
      if (g[0x7307] == 0) {
        if ((0 < g[0x4146]) && (g[0x4144] == 0)) {
          W_Cls(g[0x4145]);
        }
        if (g[G_VIDEO_LINUX_DOUBLERES] == 4) {
          f8 = 2.0;
        }
        else {
          f8 = 1.0;
        }
        font = (int *)0x1;
        text = (int *)g[0x413c];
        u17 = 0x809090d;
        AnimPerArrayDrawScaleGrp(text,1,-(i9 + i14),-(i16 + i2),f8);
        ExplodArrayDraw((int *)g[0x52be],2);
      }
      if (b5) {
        GameBarsDraw(2);
      }
      pi13 = g;
      if (g[0x7307] == 0) {
        if (g[0x81d0] != 0) {
          i9 = g[G_SLOT_LAST];
          if (g[G_SLOT_FIRST] <= i9) {
            i14 = i9 * 4 + 0x1cf60;
            i16 = i14;
            do {
              i2 = *(int *)(i16 + 4 + (int)pi13);
              if ((i2 == 0) || (b5 = true, *(int *)(i2 + 0x158) == 0)) {
                b5 = false;
              }
              if (b5) {
                if (pi13[0x7559] == 4) {
                  f8 = 2.0;
                }
                else {
                  f8 = 1.0;
                }
                PlayerDrawClsn(*(int *)(i14 + 4 + (int)pi13),f8);
                pi13 = g;
              }
              i9 = i9 + -1;
              i14 = i14 + -4;
              i16 = i16 + -4;
            } while (pi13[0x7459] <= i9);
          }
          i9 = pi13[0x745a];
          if (pi13[0x7459] <= i9) {
            i14 = i9 * 4 + 0x1cf60;
            i16 = i14;
            do {
              i2 = *(int *)(i16 + 4 + (int)pi13);
              if ((i2 == 0) || (b5 = true, *(int *)(i2 + 0x158) == 0)) {
                b5 = false;
              }
              if (b5) {
                if (pi13[0x7559] == 4) {
                  f8 = 2.0;
                }
                else {
                  f8 = 1.0;
                }
                ProjArrayClsnDraw(*(int **)(*(int *)(i14 + 4 + (int)pi13) + 0x21c),f8);
                pi13 = g;
              }
              i9 = i9 + -1;
              i14 = i14 + -4;
              i16 = i16 + -4;
            } while (pi13[0x7459] <= i9);
          }
        }
        if (pi13[0x52bd] != 0) {
          ComboDisplay(1);
          ComboDisplay(2);
          pi13 = g;
        }
        if (pi13[0x730c] != 0) {
          W_BoxFill(0,0,V_Width,pi13[0x730d],0);
          W_BoxFillTransSub16(0,g[0x730d],V_Width,g[0x730d] + 4,
                              0x10 << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                              0x20 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                              0x10 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
          W_BoxFillTransSub16(0,g[0x730d] + 5,V_Width,g[0x730d] + 9,
                              0xc << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                              0x18 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                              0xc << ((uint8_t)_rgb_b_shift_16 & 0x1f));
          W_BoxFillTransSub16(0,g[0x730d] + 10,V_Width,g[0x730d] + 0xe,
                              8 << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                              0x10 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                              8 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
          W_BoxFillTransSub16(0,g[0x730d] + 0xf,V_Width,g[0x730d] + 0x13,
                              4 << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                              8 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                              4 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
          W_BoxFill(0,(V_Height - g[0x730d]) + -1,V_Width,V_Height + -1,0);
          W_BoxFillTransSub16(0,(V_Height - g[0x730d]) + -1,V_Width,(V_Height - g[0x730d]) + -5,
                              0x10 << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                              0x20 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                              0x10 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
          W_BoxFillTransSub16(0,(V_Height - g[0x730d]) + -6,V_Width,(V_Height - g[0x730d]) + -10,
                              0xc << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                              0x18 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                              0xc << ((uint8_t)_rgb_b_shift_16 & 0x1f));
          W_BoxFillTransSub16(0,(V_Height - g[0x730d]) + -0xb,V_Width,(V_Height - g[0x730d]) + -0xf,
                              8 << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                              0x10 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                              8 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
          font = (int *)((V_Height - g[0x730d]) + -0x10);
          text = (int *)0x0;
          u17 = 0x8090d72;
          W_BoxFillTransSub16(0,(int)font,V_Width,(V_Height - g[0x730d]) + -0x14,
                              4 << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                              8 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                              4 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
          pi13 = g;
        }
        if ((pi13[0x81cd] != 0) && ((pi13[0x74e8] == 0 || (pi13[0x74f0] != 0)))) {
          ShowDebugInfo(pi13[0x81cb]);
          pi13 = g;
        }
      }
      if ((pi13[0x730c] != 0) && (pi13[0x7309] == 0)) {
        i9 = pi13[0x730e];
        i14 = i9 + pi13[0x730d];
        pi13[0x730d] = i14;
        pi13 = g;
        if (((i9 < 0) && (i14 < 0)) || ((0 < i9 && (V_Height / 2 < i14)))) {
          g[0x730c] = 0;
        }
      }
      if ((pi13[0x7309] == 0) && (pi13[0x750d] == 0)) {
        ComboDisplayUpdate(1);
        ComboDisplayUpdate(2);
        pi13 = g;
      }
      if ((pi13[0x7309] != 0) && (pi13[0x74e2] == 0)) {
        if (pi13[0x7dba] == 0) {
          text = buf_43c;
          sprintf((char *)text,"PAUSED");
          W_Box(0x85,8,0xb9,0x1b,
                10 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x14 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                0x10 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
          W_Box(0x86,9,0xb8,0x1a,
                0x18 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x30 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                0x1e << ((uint8_t)_rgb_b_shift_16 & 0x1f));
          W_BoxFillTransAdd16_B50(0x87,10,0xb7,0x19,3 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
          font = (int *)g[0x413b];
          u17 = 0x8090f4c;
          V_FontDraw((char *)text,font,0x8e,0x14,
                     0x1f << ((uint8_t)u4 & 0x1f) | 0x3f << (b10 & 0x1f) |
                     0x1f << (b11 & 0x1f));
          pi13 = g;
        }
        else {
          TrainingMenuDraw();
          pi13 = g;
        }
      }
      if (pi13[0x4137] != 0) {
        V_SetBuf((int *)pi13[0x4137],0);
        if (keypauseflag == 0) {
          font = (int *)0x0;
          text = (int *)g[G_BACKBUFFER];
          u17 = 0x8090fab;
          W_PutSpriteTransAdd_B(text,0,0,0,0x80,0x80);
        }
        V_SetBuf((int *)g[G_BACKBUFFER],0);
        pi13 = g;
      }
      if (pi13[0x82d2] == 0) {
        TimerWaitSync();
        pi13 = g;
      }
      if ((pi13[0x7307] == 0) && (pi13[0x4143] != 0)) {
        VRetrace();
      }
      DrawToScreen();
      if (g[0x7307] == 0) {
        MasterPalFinishedDraw();
      }
      FrameSkipUpdate();
      pi1 = g;
      pi13 = g + 0x7309;
      g[0x7308] = 0;
      if (*pi13 == 0) {
        pi1[0x7304] = pi1[0x7304] + 1;
      }
    }
    b5 = GameModeInPassiveFightScreen();
    pi13 = g;
    if (((ZEXT8(b5) == 0) && (g[0x7546] != 0)) || (g[0x4135] != 0))
    goto L_080910a2;
    if (g[G_SPEEDTEST] == 0) {
L_0808fec1:
      pi13 = g;
      i9 = g[G_STRESSTEST];
      if ((i9 != 0) && (i9 != -1)) {
        g[G_FRAMESKIP] = i9;
        pi13[0x82d2] = 1;
        pi13 = g;
      }
      goto L_0808fee6;
    }
    g[G_FRAMESKIP] = 2000;
    pi13[0x82d2] = 1;
    i9 = pi13[0x7304];
    pi13 = g;
  } while( true );
}
#undef buf_43c
#undef stk_3c

/* GameUpdate @ 0x08091100, 3369 bytes
 *
 * One game tick: feeds queued input to the players (KBIUpdate), runs the AI
 * and updates every player (PlayerUpdate), their afterimages and
 * projectiles. It moves the camera, runs the collision pass
 * (GameClsnUpdate), finds each player's nearest enemy, updates combos, the
 * round state (GameRoundUpdate) and the win, survival and demo screens.
 *
 * Player fields read: active, pos_x, ishelper, movetype, hitpausetime,
 *                     anim
 * Globals read: slot_first, slot_last
 * Calls: PlayerNearestEnemy, IntCircBufGet, KBIUpdate,
 *        PlayerAIMsgStateUpdate, PlayerAI, PlayerAIClearMsg,
 *        GameWinScreenUpdate, GameRoundUpdate, GameDemoUpdate,
 *        GameSurvivalResultsUpdate, GameModeInPassiveFightScreen,
 *        AnimGetLooptime, PlayerAutoTurn, PlayerKBUpdate, PlayerUpdate,
 *        PlayerUpdateBindTo, AnimUpdate, ProjArrayUpdate,
 *        ProjArrayCalcDraw, PlayerAftImgUpdate, ProjArrayAftImgUpdate,
 *        GameClsnUpdate, PlayerMakeDust, PlayerAILearnMoveUpdate, ...
 * C library: fsin
 * Called by: GameLoop
 *
 * Elecbyte file: src/mugen/gameloop.c
 * Note: 1 float-field accesses rewritten as bit reinterpretations (asm: x87
 *       single loads/stores at offsets 0x1cc70)
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 * Note: Locals live in `frame`, laid out as on the original stack (0x120 bytes,
 *       1 variables), because their address is taken.
 */
uint32_t GameUpdate(void)

{
  uint32_t *anim;
  int i2;
  int *pi3;
  bool b4;
  int *player;
  uint32_t u6;
  uint32_t stale_var;
  uint32_t u7;
  int *pi8;
  int player2;
  int looptime;
  int i11;
  int player3;
  float80 l13;
  unsigned char frame[0x120] __attribute__((aligned(16)));
#define buf_11c (*(int (*)[67])(frame + 0x4))
  
  pi3 = g;
  player = g + 0x33ae;
  g[0x730b] = 0;
  if ((*player == 3) || (pi3[0x74e8] != 0)) {
    pi3[0x730b] = 1;
  }
  player = g;
  i11 = g[G_SLOT_FIRST];
  if (i11 <= g[G_SLOT_LAST]) {
    looptime = i11 * 4 + 0x1cf60;
    do {
      player3 = *(int *)(looptime + 4 + (int)player);
      if ((player3 == 0) || (player2 = 1, *(int *)(player3 + PLB_ACTIVE) == 0)) {
        player2 = 0;
      }
      looptime = looptime + 4;
      pi3[i11 + 0x749e] = player2;
      i11 = i11 + 1;
    } while (i11 <= player[0x745a]);
  }
  i11 = 1;
  if (0 < player[0x7395]) {
    looptime = 0x1cf64;
    do {
      player3 = *(int *)(looptime + 4 + (int)player);
      if (player3 == 0) {
L_080911f5:
        b4 = false;
      }
      else {
        buf_11c[i11] = (int)X87_FIST32(*(float *)(player3 + PLB_POS_X));
        b4 = true;
        if (*(int *)(player3 + PLB_ACTIVE) == 0) goto L_080911f5;
      }
      if (b4) {
        player2 = *(int *)(player3 + 0x3424);
        if (((player2 == 0) || (*(int *)(player2 + PLB_ACTIVE) == 0)) ||
           (b4 = true, *(int *)(player2 + PLB_ISHELPER) != 0)) {
          b4 = false;
        }
        if (b4) {
          *(int *)(player3 + 0x3428) = player2;
        }
        player2 = PlayerNearestEnemy(player3);
        *(int *)(player3 + 0x3424) = player2;
      }
      i11 = i11 + 1;
      looptime = looptime + 4;
      player = g;
    } while (i11 <= g[0x7395]);
  }
  pi8 = g;
  if ((player[0x74f3] != -1) && (i11 = player[0x7459], i11 <= player[0x745a])) {
    looptime = i11 * 4 + 0x1cf60;
    player3 = looptime;
    do {
      player2 = *(int *)(player3 + 4 + (int)player);
      if ((player2 == 0) || (b4 = true, *(int *)(player2 + PLB_ACTIVE) == 0)) {
        b4 = false;
      }
      if ((b4) &&
         (*(int *)(*(int *)(looptime + 4 + (int)player) + 0x1dc + player[0x74f3] * 4) == 0)) {
        pi3[i11 + 0x749e] = 0;
        player = pi8;
      }
      i11 = i11 + 1;
      looptime = looptime + 4;
      player3 = player3 + 4;
    } while (i11 <= player[0x745a]);
  }
  while (u6 = IntCircBufGet(player + 0x7391), u6 != 0) {
    player = g;
    if (((g[0x7309] == 0) || ((u6 & 0x1000) != 0)) && (i11 = g[G_SLOT_FIRST], i11 <= g[G_SLOT_LAST]))
    {
      looptime = i11 * 4 + 0x1cf60;
      do {
        player3 = *(int *)(looptime + 4 + (int)player);
        if ((player3 == 0) || (b4 = true, *(int *)(player3 + PLB_ACTIVE) == 0)) {
          b4 = false;
        }
        if ((b4) && (player3 = *(int *)((int)player + looptime + 4), *(int *)(player3 + 0x262c) == 0)
           ) {
          KBIUpdate(*(int *)(*(int *)((int)player + looptime + 4) + 0x960),player3 + 0x248,u6);
          player = g;
        }
        i11 = i11 + 1;
        looptime = looptime + 4;
      } while (i11 <= player[0x745a]);
    }
  }
  if ((g[0x7309] == 0) && (g[0x750d] < 1)) {
    i11 = g[G_SLOT_FIRST];
    player = g;
    if (i11 <= g[G_SLOT_LAST]) {
      looptime = i11 * 4 + 0x1cf60;
      player3 = looptime;
      do {
        player2 = *(int *)(player3 + 4 + (int)player);
        if ((player2 == 0) || (b4 = true, *(int *)(player2 + PLB_ACTIVE) == 0)) {
          b4 = false;
        }
        if (b4) {
          PlayerAIMsgStateUpdate(*(int *)(looptime + 4 + (int)player));
          player = g;
        }
        i11 = i11 + 1;
        looptime = looptime + 4;
        player3 = player3 + 4;
      } while (i11 <= player[0x745a]);
    }
    i11 = player[0x7459];
    if (i11 <= player[0x745a]) {
      looptime = i11 * 4 + 0x1cf60;
      player3 = looptime;
      do {
        player2 = *(int *)(player3 + 4 + (int)player);
        if ((player2 == 0) || (b4 = true, *(int *)(player2 + PLB_ACTIVE) == 0)) {
          b4 = false;
        }
        if (b4) {
          PlayerAI(*(int *)(looptime + 4 + (int)player));
          player = g;
        }
        i11 = i11 + 1;
        looptime = looptime + 4;
        player3 = player3 + 4;
      } while (i11 <= player[0x745a]);
    }
    i11 = player[0x7459];
    if (i11 <= player[0x745a]) {
      looptime = i11 * 4 + 0x1cf60;
      player3 = looptime;
      do {
        player2 = *(int *)(player3 + 4 + (int)player);
        if ((player2 == 0) || (b4 = true, *(int *)(player2 + PLB_ACTIVE) == 0)) {
          b4 = false;
        }
        if (b4) {
          PlayerAIClearMsg(*(int *)(looptime + 4 + (int)player));
          player = g;
        }
        i11 = i11 + 1;
        looptime = looptime + 4;
        player3 = player3 + 4;
      } while (i11 <= player[0x745a]);
    }
    i11 = player[0x33b7];
    if (i11 == 5) {
      GameWinScreenUpdate();
      player = g;
    }
    else if (i11 < 6) {
      if ((i11 == 4) &&
         (((player[0x7309] == 0 && (i11 = GameRoundUpdate(), player = g, i11 != 0)) ||
          ((player[0x7309] == 0 &&
           ((player[0x74e8] != 0 && (i11 = GameDemoUpdate(), player = g, i11 != 0)))))))) {
        return 1;
      }
    }
    else if (i11 == 6) {
      GameSurvivalResultsUpdate();
      player = g;
    }
    pi8 = g;
    i11 = player[0x7459];
    if (i11 <= player[0x745a]) {
      looptime = i11 * 4 + 0x1cf60;
      player3 = looptime;
      do {
        player2 = *(int *)(player3 + 4 + (int)player);
        if ((player2 == 0) || (b4 = true, *(int *)(player2 + PLB_ACTIVE) == 0)) {
          b4 = false;
        }
        if ((b4) && (*(int *)(*(int *)(looptime + 4 + (int)player) + 0x15c) != 0)) {
          pi3[i11 + 0x749e] = 0;
          player = pi8;
        }
        i11 = i11 + 1;
        looptime = looptime + 4;
        player3 = player3 + 4;
      } while (i11 <= player[0x745a]);
    }
    if (((player[0x109d] != 0) &&
        (b4 = GameModeInPassiveFightScreen(), player = g, ZEXT8(b4) == 0)) &&
       (i11 = g[G_SLOT_FIRST], i11 <= g[G_SLOT_LAST])) {
      do {
        looptime = player[i11 + 0x73d9];
        if (((looptime == 0) || (*(int *)(looptime + 0x158) == 0)) ||
           (b4 = true, *(int *)(looptime + 0x1c) != 0)) {
          b4 = false;
        }
        if ((b4) && (pi3[i11 + 0x749e] != 0)) {
          u6 = *(uint32_t *)(player[i11 + 0x73d9] + 0x3424);
          if ((u6 == 0) || (u7 = 1, *(int *)(u6 + 0x158) == 0)) {
            u7 = 0;
          }
          u6 = u6 & (u7 ^ 1) - 1;
          if ((u6 == 0) && (2 < player[0x7511])) {
            if ((*(int *)(player[i11 + 0x73d9] + 0x3428) == 0) ||
               (b4 = true, *(int *)(*(int *)(player[i11 + 0x73d9] + 0x3428) + 0x158) == 0)) {
              b4 = false;
            }
            if (b4) {
              u6 = *(uint32_t *)(player[i11 + 0x73d9] + 0x3428);
            }
          }
          if (u6 != 0) {
            looptime = *(int *)(player[i11 + 0x73d9] + 0xbf4);
            if (((((looptime == 0) || (looptime == 0xb)) || (looptime == 0x14)) || (looptime == 0x28)) ||
               ((looptime == 0x34 &&
                (anim = *(uint32_t **)(player[i11 + 0x73d9] + 0x13bc),
                looptime = AnimGetLooptime(anim), player = g, looptime + -1 <= (int)anim[7])))) {
              PlayerAutoTurn(player[i11 + 0x73d9],u6,1);
              player = g;
            }
          }
        }
        i11 = i11 + 1;
      } while (i11 <= player[0x745a]);
    }
    i11 = player[0x7459];
    if (i11 <= player[0x745a]) {
      looptime = i11 * 4 + 0x1cf60;
      player3 = looptime;
      do {
        player2 = *(int *)(player3 + 4 + (int)player);
        if ((player2 == 0) || (b4 = true, *(int *)(player2 + PLB_ACTIVE) == 0)) {
          b4 = false;
        }
        if (b4) {
          PlayerKBUpdate(*(int **)(looptime + 4 + (int)player));
          player = g;
        }
        i11 = i11 + 1;
        looptime = looptime + 4;
        player3 = player3 + 4;
      } while (i11 <= player[0x745a]);
    }
    *(uint8_t *)((int)player + 0x1d396) = 0;
    player[0x74e3] = 0;
    player[0x74e4] = 0;
    *(uint16_t *)(player + 0x74e5) = 0;
    i11 = g[G_SLOT_FIRST];
    player = g;
    if (i11 <= g[G_SLOT_LAST]) {
      looptime = i11 * 4 + 0x1cf60;
      player3 = looptime;
      do {
        player2 = *(int *)(player3 + 4 + (int)player);
        if ((player2 == 0) || (b4 = true, *(int *)(player2 + PLB_ACTIVE) == 0)) {
          b4 = false;
        }
        if ((b4) && (pi3[i11 + 0x749e] != 0)) {
          player2 = *(int *)(looptime + 4 + (int)player);
          *(uint8_t *)(player2 + 0x20c) = 0;
          *(uint32_t *)(player2 + 0x204) = 0;
          *(uint32_t *)(player2 + 0x208) = 0;
          player = g;
        }
        i11 = i11 + 1;
        looptime = looptime + 4;
        player3 = player3 + 4;
      } while (i11 <= player[0x745a]);
    }
    i11 = player[0x7459];
    player[0x74de] = 0;
    pi8 = g;
    if (i11 <= player[0x745a]) {
      looptime = i11 * 4 + 0x1cf60;
      player3 = looptime;
      do {
        player2 = *(int *)(player3 + 4 + (int)pi8);
        if ((player2 == 0) || (b4 = true, *(int *)(player2 + PLB_ACTIVE) == 0)) {
          b4 = false;
        }
        if (((b4) && (pi3[i11 + 0x749e] != 0)) &&
           (player = *(int **)(looptime + 4 + (int)pi8), player[PL_MOVETYPE] == 1)) {
          PlayerUpdate(player);
          pi8 = g;
        }
        i11 = i11 + 1;
        looptime = looptime + 4;
        player3 = player3 + 4;
      } while (i11 <= pi8[0x745a]);
    }
    i11 = pi8[0x7459];
    if (i11 <= pi8[0x745a]) {
      looptime = i11 * 4 + 0x1cf60;
      player3 = looptime;
      do {
        player2 = *(int *)(player3 + 4 + (int)pi8);
        if ((player2 == 0) || (b4 = true, *(int *)(player2 + PLB_ACTIVE) == 0)) {
          b4 = false;
        }
        if (((b4) && (pi3[i11 + 0x749e] != 0)) &&
           (player = *(int **)(looptime + 4 + (int)pi8), player[0x38b] != pi8[0x7304])) {
          PlayerUpdate(player);
          pi8 = g;
        }
        i11 = i11 + 1;
        looptime = looptime + 4;
        player3 = player3 + 4;
      } while (i11 <= pi8[0x745a]);
    }
    while (pi8[0x74de] != 0) {
      i11 = pi8[0x7459];
      pi8[0x74de] = 0;
      player = pi8 + 0x745a;
      pi8 = g;
      if (i11 <= *player) {
        looptime = i11 * 4 + 0x1cf60;
        player3 = looptime;
        do {
          player2 = *(int *)(player3 + 4 + (int)pi8);
          if ((player2 == 0) || (b4 = true, *(int *)(player2 + PLB_ACTIVE) == 0)) {
            b4 = false;
          }
          if (((b4) && (pi3[i11 + 0x749e] != 0)) &&
             (player = *(int **)(looptime + 4 + (int)pi8), player[0x38b] != pi8[0x7304])) {
            PlayerUpdate(player);
            pi8 = g;
          }
          i11 = i11 + 1;
          looptime = looptime + 4;
          player3 = player3 + 4;
        } while (i11 <= pi8[0x745a]);
      }
    }
    i11 = pi8[0x7459];
    if (i11 <= pi8[0x745a]) {
      looptime = i11 * 4 + 0x1cf60;
      player3 = looptime;
      do {
        player2 = *(int *)(player3 + 4 + (int)pi8);
        if ((player2 == 0) || (b4 = true, *(int *)(player2 + PLB_ACTIVE) == 0)) {
          b4 = false;
        }
        if ((b4) && (pi3[i11 + 0x749e] != 0)) {
          PlayerUpdateBindTo(*(int *)(looptime + 4 + (int)pi8));
          pi8 = g;
        }
        i11 = i11 + 1;
        looptime = looptime + 4;
        player3 = player3 + 4;
      } while (i11 <= pi8[0x745a]);
    }
    player = pi8;
    if (((0 < pi8[0x7318]) && (pi8[0x7309] == 0)) && (pi8[0x750d] == 0)) {
      l13 = (float80)
               fsin(((float80)pi8[0x7317] * (float80)BITS_I2F(pi8[0x731a]) +
                    (float80)(*(float *)&pi8[0x731c])) * (float80)((double)3.14159) *
                    (float80)((double)0.005555555555555556));
      pi8[0x7316] = (int)X87_FIST32(l13 * (float80)BITS_I2F(pi8[0x731b]));
      i11 = pi8[0x7317];
      pi8[0x7317] = i11 + 1;
      player = g;
      if (i11 + 1 == pi8[0x7318]) {
        pi8[0x7318] = 0;
        pi8[0x7316] = 0;
        pi8[0x7315] = 0;
        player = g;
      }
    }
    i11 = player[0x7459];
    if (i11 <= player[0x745a]) {
      looptime = i11 * 4 + 0x1cf60;
      player3 = looptime;
      do {
        player2 = *(int *)(player3 + 4 + (int)player);
        if ((player2 == 0) || (b4 = true, *(int *)(player2 + PLB_ACTIVE) == 0)) {
          b4 = false;
        }
        if (((b4) && (pi3[i11 + 0x749e] != 0)) &&
           (player2 = *(int *)(looptime + 4 + (int)player), *(int *)(player2 + PLB_HITPAUSETIME) == 0)) {
          AnimUpdate(*(uint32_t **)(player2 + PLB_ANIM));
          player = g;
        }
        i11 = i11 + 1;
        looptime = looptime + 4;
        player3 = player3 + 4;
      } while (i11 <= player[0x745a]);
    }
    i11 = player[0x745a];
    if (player[0x7459] <= i11) {
      looptime = i11 * 4 + 0x1cf60;
      player3 = looptime;
      player2 = looptime;
      do {
        i2 = *(int *)(player3 + 4 + (int)player);
        if ((i2 == 0) || (b4 = true, *(int *)(i2 + 0x158) == 0)) {
          b4 = false;
        }
        if (b4) {
          if (pi3[i11 + 0x749e] != 0) {
            ProjArrayUpdate(*(int **)(*(int *)(looptime + 4 + (int)player) + 0x21c));
            player = g;
          }
          ProjArrayCalcDraw(*(int **)(*(int *)(player2 + 4 + (int)player) + 0x21c));
          player = g;
        }
        i11 = i11 + -1;
        player2 = player2 + -4;
        looptime = looptime + -4;
        player3 = player3 + -4;
      } while (player[0x7459] <= i11);
    }
    i11 = player[0x745a];
    if (player[0x7459] <= i11) {
      looptime = i11 * 4 + 0x1cf60;
      do {
        player3 = *(int *)(looptime + 4 + (int)player);
        if ((player3 == 0) || (b4 = true, *(int *)(player3 + PLB_ACTIVE) == 0)) {
          b4 = false;
        }
        if ((b4) && (*(int *)((int)pi3 + looptime + 0x318) != 0)) {
          PlayerAftImgUpdate(*(int *)(looptime + 4 + (int)player));
          ProjArrayAftImgUpdate(*(int **)(*(int *)((int)g + looptime + 4) + 0x21c));
          player = g;
        }
        i11 = i11 + -1;
        looptime = looptime + -4;
      } while (player[0x7459] <= i11);
    }
    if (player[0x74e0] != 0) {
      GameClsnUpdate();
      player = g;
    }
    if ((player[0x74f3] == -1) && (i11 = player[0x745a], player[0x7459] <= i11)) {
      player3 = i11 * 4;
      looptime = player3 + 0x1cf60;
      pi8 = player;
      do {
        player2 = *(int *)(looptime + 4 + (int)pi8);
        if ((player2 == 0) || (b4 = true, *(int *)(player2 + PLB_ACTIVE) == 0)) {
          b4 = false;
        }
        player = pi8;
        if ((b4) &&
           (player = g,
           (int)X87_FIST32(*(float *)(*(int *)((int)pi8 + looptime + 4) + 0x19c)) !=
           *(int *)((int)buf_11c + player3))) {
          PlayerMakeDust(*(int *)((int)pi8 + looptime + 4));
          player = g;
        }
        i11 = i11 + -1;
        looptime = looptime + -4;
        player3 = player3 + -4;
        pi8 = player;
      } while (player[0x7459] <= i11);
    }
    i11 = player[0x745a];
    if (player[0x7459] <= i11) {
      looptime = i11 * 4 + 0x1cf60;
      do {
        player3 = *(int *)(looptime + 4 + (int)player);
        if ((player3 == 0) || (b4 = true, *(int *)(player3 + PLB_ACTIVE) == 0)) {
          b4 = false;
        }
        if ((b4) && (*(int *)(*(int *)((int)player + looptime + 4) + 0x15c) == 0)) {
          PlayerAILearnMoveUpdate
                    (*(int *)((int)player + looptime + 4),*(int *)((int)pi3 + looptime + 0x318));
          player = g;
        }
        i11 = i11 + -1;
        looptime = looptime + -4;
      } while (player[0x7459] <= i11);
    }
    CameraMoveP();
    AnimPerArrayUpdate((int *)g[0x413c]);
    i11 = g[G_SLOT_FIRST];
    player = g;
    if (i11 <= g[G_SLOT_LAST]) {
      looptime = i11 * 4 + 0x1cf60;
      player3 = looptime;
      do {
        player2 = *(int *)(player3 + 4 + (int)player);
        if ((player2 == 0) || (b4 = true, *(int *)(player2 + PLB_ACTIVE) == 0)) {
          b4 = false;
        }
        if (b4) {
          PlayerComboCountCheck(*(int *)(looptime + 4 + (int)player));
          player = g;
        }
        i11 = i11 + 1;
        looptime = looptime + 4;
        player3 = player3 + 4;
      } while (i11 <= player[0x745a]);
    }
    ExplodArrayUpdate((int *)player[0x52be]);
  }
  return 0;
}
#undef buf_11c

/* GameWinScreenUpdate @ 0x08091e30, 391 bytes
 *
 * Runs the win screen after a match: fades the stage and shows the win text
 * explod.
 *
 * Calls: MasterPalMul, PalGrpMakeFlag, PalGrpSetMul, SysExplodCreate_Sys
 * Called by: GameUpdate
 *
 * Elecbyte file: src/mugen/gameloop.c
 * Note: decompiler flag: stack slots read outside the declared parameters
 *       (entry_stack variables)
 * Note: PalGrpMakeFlag result written into the argument area: given explicit
 *       temporaries pgf_ffffffb4
 */
void GameWinScreenUpdate(void)

{
  PalGrpFlag pgf_ffffffb4;
  bool b1;
  int *pi2;
  int *pi3;
  PalGrpFlag entry_stack_ffffffb4;
  int i4;
  int i5;
  int i6;
  
  pi2 = g;
  do {
    pi3 = g;
    i4 = g[0x7541];
    b1 = false;
    i5 = g[0x7542];
    if (i4 == 1) {
      if (i5 == pi2[0x2b70]) {
        g[0x7541] = 2;
        pi3[0x7542] = 0;
        b1 = true;
      }
    }
    else if (i4 < 2) {
      if (i4 == 0) {
        i4 = pi2[0x2b71];
        if (i5 < i4) {
          i6 = (i5 << 8) / i4;
          MasterPalMul(i6,i6,i6);
        }
        if (i5 == i4) {
          b1 = true;
          MasterPalMul(0x100,0x100,0x100);
          pi3 = g;
          g[0x7541] = 1;
          pi3[0x7542] = 0;
        }
      }
    }
    else if (i4 == 2) {
      i4 = pi2[0x2b72];
      if (i5 < i4) {
        i6 = 0x100 - (i5 << 8) / i4;
        MasterPalMul(i6,i6,i6);
      }
      if (i5 == i4) {
        MasterPalMul(0,0,0);
        g[0x4135] = 1;
      }
    }
  } while (b1);
  i6 = 0x80;
  i5 = 0x80;
  i4 = 0x80;
  PalGrpMakeFlag(&pgf_ffffffb4,0xffffffff,0);
  PalGrpSetMul(pgf_ffffffb4,i4,i5,i6);
  SysExplodCreate_Sys(pi2 + 0x2b55,0,0);
  g[0x7542] = g[0x7542] + 1;
  return;
}

/* GameSurvivalResultsUpdate @ 0x08091fc0, 439 bytes
 *
 * Runs the survival results screen: fades and shows the number of rounds
 * won.
 *
 * Globals read: round_no
 * Calls: MasterPalMul, PalGrpMakeFlag, PalGrpSetMul, SysExplodCreate_Sys
 * C library: strcpy, sprintf
 * Called by: GameUpdate
 *
 * Elecbyte file: src/mugen/gameloop.c
 * Note: decompiler flag: stack slots read outside the declared parameters
 *       (entry_stack variables)
 * Note: PalGrpMakeFlag result written into the argument area: given explicit
 *       temporaries pgf_fffffeb4
 * Note: 1 exact-text site patches (see SITE_PATCHES in
 *       tools/build_source_tree.py)
 * Note: Locals live in `frame`, laid out as on the original stack (0x120 bytes,
 *       1 variables), because their address is taken.
 */
void GameSurvivalResultsUpdate(void)

{
  PalGrpFlag pgf_fffffeb4;
  int *pi1;
  bool b2;
  int *pi3;
  PalGrpFlag entry_stack_fffffeb4;
  int i4;
  int i5;
  int i6;
  unsigned char frame[0x120] __attribute__((aligned(16)));
#define buf_11c (*(char (*)[268])(frame + 0x4))
  
  pi3 = g;
  do {
    pi1 = g;
    i4 = g[0x7541];
    b2 = false;
    i5 = g[0x7542];
    if (i4 == 1) {
      if (i5 == pi3[0x2b8f]) {
        g[0x7541] = 2;
        pi1[0x7542] = 0;
        b2 = true;
      }
    }
    else if (i4 < 2) {
      if (i4 == 0) {
        i4 = pi3[0x2b90];
        if (i5 < i4) {
          i6 = (i5 << 8) / i4;
          MasterPalMul(i6,i6,i6);
        }
        if (i5 == i4) {
          b2 = true;
          MasterPalMul(0x100,0x100,0x100);
          pi1 = g;
          g[0x7541] = 1;
          pi1[0x7542] = 0;
        }
      }
    }
    else if (i4 == 2) {
      i4 = pi3[0x2b91];
      if (i5 < i4) {
        i6 = 0x100 - (i5 << 8) / i4;
        MasterPalMul(i6,i6,i6);
      }
      if (i5 == i4) {
        MasterPalMul(0,0,0);
        g[0x4135] = 1;
      }
    }
  } while (b2);
  pi1 = pi3 + 0x2b83;
  i6 = 0x80;
  i5 = 0x80;
  i4 = 0x80;
  PalGrpMakeFlag(&pgf_fffffeb4,0xffffffff,0);
  PalGrpSetMul(pgf_fffffeb4,i4,i5,i6);
  strcpy(buf_11c,(char *)pi1);
  sprintf((char *)pi1,buf_11c,g[G_ROUND_NO + g[0x33b4]]);
  SysExplodCreate_Sys(pi3 + 0x2b74,0,0);
  strcpy((char *)pi1,buf_11c);
  g[0x7542] = g[0x7542] + 1;
  return;
}
#undef buf_11c

/* GameDemoUpdate @ 0x08092180, 200 bytes
 *
 * Ends a demo fight after its configured time (with a fade out).
 *
 * Globals read: demo_mode, demo_mode_fight_endtime
 * Calls: MasterPalMul
 * Called by: GameUpdate
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
uint32_t GameDemoUpdate(void)

{
  int i1;
  int *pi2;
  uint32_t u3;
  
  u3 = 0;
  if (g[0x7511] == 2) {
    if (g[G_DEMO_MODE] != 0) {
      if (g[G_DEMO_MODE_FIGHT_ENDTIME] + -0x78 <= g[0x74f1]) {
        i1 = ((g[G_DEMO_MODE_FIGHT_ENDTIME] - g[0x74f1]) * 0x100) / 0x78;
        MasterPalMul(i1,i1,i1);
      }
      pi2 = g;
      if (g[G_DEMO_MODE_FIGHT_ENDTIME] <= g[0x74f1]) {
        i1 = g[0x74f2];
        u3 = 1;
        g[0x4135] = 1;
        pi2[0x74f2] = i1 + 1;
        if (pi2[0x74e9] <= i1) {
          pi2[0x74f2] = 0;
          pi2[0x2351] = 0;
        }
      }
    }
    g[0x74f1] = g[0x74f1] + 1;
  }
  return u3;
}

/* GameRoundUpdate @ 0x08092250, 4836 bytes
 *
 * The round state machine: intro (players in their intro states), "Round n"
 * / "Fight" announcements, fight with the timer counting down, KO or time
 * over detection, slow motion on KO, round over, win poses, and the move to
 * the next round or match (GameNextRound). Also turns-mode member changes,
 * life recovery between members (TeamLifeBack) and match logging. Starts
 * precaching the next team ("start pre-caching team %i next %i").
 *
 * Player fields read: active, ishelper, stateno, teamside, alive
 * Player fields written: ctrl
 * Globals read: players, options_team_loseonko, slot_first, slot_last,
 *               round_ctrl_time, round_slow_time, clipboard,
 *               sound_linux_masterwavvolume, sound_linux_midivolume
 * Calls: WinIconCheck, GameRoundResetPlayerPos, MasterPalMul,
 *        PlayerChangeState, ArrayScanFirst, ProjArrayDelete,
 *        ArrayScanNext, HelperDestroy, ExplodArrayReset, GameSndPlay,
 *        GameRoundWinner, ClipboardAppend, PrecacheRequestTeam,
 *        GameMatchWinner, PrecacheRequestNextArcadeTeam, PrecacheStart,
 *        PlayerLyingDead, TeamLifeBack, PlayerLifeSet, GameSetVol,
 *        LogMatch, PrecacheFinish, W_Cls, DrawToScreen, ...
 * Called by: GameUpdate
 * Messages:
 *   "start pre-caching team %i next %i\n"
 *
 * Elecbyte file: src/mugen/gameloop.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x80 bytes,
 *       10 variables), because their address is taken.
 */
uint32_t GameRoundUpdate(void)

{
  int *pi1;
  bool b2;
  bool b3;
  uint8_t b4;
  int item;
  int *sounds;
  int *pi7;
  int *pi8;
  int player;
  int group;
  int i2;
  uint32_t u12;
  int i13;
  unsigned char frame[0x80] __attribute__((aligned(16)));
#define stk_78 (*(int *)(frame + 0x8))
#define stk_74 (*(int *)(frame + 0xc))
#define stk_6c (*(int *)(frame + 0x14))
#define stk_68 (*(int *)(frame + 0x18))
#define stk_64 (*(int *)(frame + 0x1c))
#define stk_60 (*(int *)(frame + 0x20))
#define stk_5c (*(int *)(frame + 0x24))
#define stk_4c (*(uint32_t *)(frame + 0x34))
#define stk_48 (*(int *)(frame + 0x38))
#define stk_3c (*(int (*)[11])(frame + 0x44))
  
  pi8 = g;
  pi7 = g + 0x4109;
  stk_3c[4] = 0xffffffff;
  stk_3c[5] = -1;
  stk_3c[6] = -1;
  stk_3c[0] = 0;
  stk_3c[1] = 0;
  stk_3c[2] = 0;
  stk_4c = 0;
  stk_78 = 4;
  sounds = g + 0x4106;
  stk_48 = 1;
  do {
    group = 0;
    i2 = sounds[2];
    if (0 < i2) {
      do {
        i2 = g[pi7[group * 5] + G_PLAYERS];
        group = group + 1;
        *(uint32_t *)((int)stk_3c + stk_78) =
             (*(int *)(i2 + 0x160) * 1000) / *(int *)(i2 + 0x164) +
             *(int *)((int)stk_3c + stk_78) + (uint32_t)(*(int *)(i2 + 0xe24) != 0);
        i2 = sounds[2];
      } while (group < i2);
    }
    pi7 = pi7 + 0x17;
    sounds = sounds + 0x17;
    *(int *)((int)stk_3c + stk_78) = *(int *)((int)stk_3c + stk_78) / i2;
    stk_78 = stk_78 + 4;
    stk_48 = stk_48 + -1;
  } while (-1 < stk_48);
  stk_74 = 0;
  stk_48 = 1;
  do {
    i2 = 0;
    sounds = (int *)((int)g + stk_74 + 0x10418);
    if (0 < *(int *)((int)g + stk_74 + 0x10420)) {
      stk_64 = -4;
      stk_68 = 0x10;
      stk_6c = 0;
      do {
        group = g[*(int *)(stk_6c + 0xc + (int)sounds) + G_PLAYERS];
        if (((group == 0) || (*(int *)(group + 0x158) == 0)) ||
           (b2 = true, *(int *)(group + 0x1c) != 0)) {
          b2 = false;
        }
        if (b2) {
          if (stk_3c[*(int *)(group + 0xc) + 4] == -1) {
            stk_3c[*(int *)(group + 0xc) + 4] = 1;
          }
          if ((((*sounds != 1) || (i2 < 1)) ||
              ((g[G_OPTIONS_TEAM_LOSEONKO] != 0 ||
               ((*(int *)((int)g + stk_68 + stk_74 + 0x10424) == 0 ||
                (*(int *)((int)g + stk_64 + stk_74 + 0x10424) != 0)))))) &&
             (*(int *)(group + 0xe24) != 0)) {
            stk_3c[*(int *)(group + 0xc) + 4] = 0;
          }
        }
        stk_64 = stk_64 + 0x14;
        stk_68 = stk_68 + 0x14;
        stk_6c = stk_6c + 0x14;
        i2 = i2 + 1;
      } while (i2 < *(int *)((int)g + stk_74 + 0x10420));
    }
    stk_74 = stk_74 + 0x5c;
    stk_48 = stk_48 + -1;
  } while (-1 < stk_48);
  sounds = g;
  if ((stk_3c[5] != -1) && (stk_3c[6] != -1)) {
    if ((stk_3c[5] == 0) || (stk_3c[6] == 0)) {
      if (stk_3c[5] == 0) {
        if (stk_3c[6] == 0) {
          if (g[0x7515] == 0) {
            g[0x7513] = 3;
            if (stk_3c[2] < stk_3c[1]) {
              pi8[0x7512] = 1;
              i2 = 1;
            }
            else {
              if (stk_3c[2] <= stk_3c[1]) {
                WinIconCheck(1,0,4);
                WinIconCheck(2,0,4);
                sounds = g;
                g[0x7512] = 0;
                goto L_080925c2;
              }
              pi8[0x7512] = 2;
              if ((pi8[0x7511] != 3) && (pi8[0x7508] < 10)) {
                pi8[pi8[0x7508] + 0x7523] = 4;
              }
              i2 = 2;
            }
            WinIconCheck(i2,0,4);
            sounds = g;
          }
        }
        else {
          g[0x7513] = 1;
          pi8[0x7512] = 1;
          sounds = g;
        }
      }
      else {
        g[0x7513] = 1;
        pi8[0x7512] = 2;
        sounds = g;
      }
    }
    else {
      g[0x7513] = 2;
      pi8[0x7512] = 0;
      sounds = g;
    }
  }
L_080925c2:
  if (sounds[0x730b] != 0) {
    sounds[0x7513] = 0;
    sounds = g;
  }
  if (1 < (uint32_t)sounds[0x7511]) {
    sounds[0x7517] = 0;
    sounds = g;
  }
  if ((sounds[0x7517] != 0) && (sounds[0x730c] == 0)) {
    sounds[0x7517] = 0;
    sounds[0x7511] = 2;
    GameRoundResetPlayerPos();
    MasterPalMul(0x100,0x100,0x100);
    i2 = V_Height;
    sounds = g;
    g[0x7514] = -1;
    sounds[0x730c] = 1;
    if (sounds[0x7559] != 4) {
      i2 = i2 / 2;
    }
    group = sounds[0x7459];
    sounds[0x730d] = i2;
    sounds[0x730e] = -sounds[0x730e];
    if (group <= sounds[0x745a]) {
      i2 = group * 4 + 0x1cf60;
      player = i2;
      do {
        item = *(int *)(i2 + 4 + (int)sounds);
        if (((item == 0) || (*(int *)(item + 0x158) == 0)) ||
           (b2 = true, *(int *)(item + 0x1c) != 0)) {
          b2 = false;
        }
        if (b2) {
          PlayerChangeState(*(int *)(player + 4 + (int)sounds),0);
          sounds = g;
        }
        group = group + 1;
        player = player + 4;
        i2 = i2 + 4;
      } while (group <= sounds[0x745a]);
    }
    i2 = sounds[0x7459];
    if (i2 <= sounds[0x745a]) {
      group = i2 * 4 + 0x1cf60;
      do {
        player = *(int *)(group + 4 + (int)sounds);
        if (player != 0) {
          *(uint32_t *)(player + 0x15c) = 0;
          sounds = g;
        }
        player = *(int *)(group + 4 + (int)sounds);
        if (((player == 0) || (*(int *)(player + PLB_ACTIVE) == 0)) ||
           (b2 = true, *(int *)(player + PLB_ISHELPER) != 0)) {
          b2 = false;
        }
        if (b2) {
          player = **(int **)(*(int *)(group + 4 + (int)sounds) + 0x21c);
          item = ArrayScanFirst(player);
          while (sounds = g, item != 0) {
            ProjArrayDelete(*(int **)(*(int *)((int)g + group + 4) + 0x21c),*(int *)(player + PLB_ISHELPER))
            ;
            item = ArrayScanNext(player);
          }
        }
        else {
          player = *(int *)(group + 4 + (int)sounds);
          if ((player == 0) || (b2 = true, *(int *)(player + PLB_ACTIVE) == 0)) {
            b2 = false;
          }
          if ((b2) && (player = *(int *)(group + 4 + (int)sounds), *(int *)(player + PLB_ISHELPER) == 1))
          {
            HelperDestroy(player);
            sounds = g;
          }
        }
        i2 = i2 + 1;
        group = group + 4;
      } while (i2 <= sounds[0x745a]);
    }
    ExplodArrayReset((uint32_t *)sounds[0x52be]);
    ExplodArrayReset((uint32_t *)g[0x52bf]);
    sounds = g;
  }
  do {
    sounds[0x74e0] = 1;
    pi7 = g;
    switch(sounds[0x7511]) {
    case 0:
      sounds = g + 0x7514;
      g[0x74e0] = 0;
      u12 = *sounds - 2U & 0xffffffffU - ((int)(*sounds - 2U) >> 0x1f);
      if ((int)u12 < 0x10) {
        i2 = u12 << 4;
      }
      else {
        i2 = 0x100;
      }
      MasterPalMul(i2,i2,i2);
      pi7 = g;
      if (g[0x7514] < pi8[0x4e77]) goto L_default_0809282e;
      MasterPalMul(0x100,0x100,0x100);
      sounds = g;
      g[0x7511] = 1;
      sounds[0x7514] = 0;
      break;
    case 1:
      i2 = g[G_SLOT_FIRST];
      sounds = g;
      if (i2 <= g[G_SLOT_LAST]) {
        group = i2 * 4 + 0x1cf60;
        player = group;
        do {
          pi7 = g;
          item = *(int *)(player + 4 + (int)sounds);
          if (((item == 0) || (*(int *)(item + 0x158) == 0)) ||
             (b2 = true, *(int *)(item + 0x1c) != 0)) {
            b2 = false;
          }
          if ((b2) && (sounds[0x7506] == 1)) {
            if (sounds[0x7514] < 0) {
              *(uint8_t *)(sounds + 0x74e3) = 1;
              sounds = g;
            }
            else {
              *(uint32_t *)(*(int *)(group + 4 + (int)sounds) + 0x15c) = 0;
              sounds = pi7;
            }
          }
          i2 = i2 + 1;
          group = group + 4;
          player = player + 4;
        } while (i2 <= sounds[0x745a]);
      }
      if ((char)sounds[0x74e3] != '\0') {
        sounds[0x750e] = 0;
        sounds = g;
      }
      if (((sounds[0x750e] == pi8[0x4fa5] + 1) && (sounds[0x7506] < 10)) && (sounds[0x74e8] == 0)
         ) {
        GameSndPlay((int *)sounds[0x4155],pi8[sounds[0x7506] + 0x4fa6],
                    pi8[sounds[0x7506] + 0x4fb0],0);
        sounds = g;
      }
      if (sounds[0x750e] < pi8[0x4e78]) {
        sounds[0x750e] = sounds[0x750e] + 1;
        pi7 = g;
        goto L_default_0809282e;
      }
      sounds[0x7511] = 2;
      sounds[0x7514] = 0;
      GameRoundResetPlayerPos();
      sounds = g;
      break;
    case 2:
      if ((g[0x74f3] == -1) && (g[0x750d] == 0)) {
        sounds = g + 0x7514;
        pi1 = g + G_ROUND_CTRL_TIME;
        if (((*pi1 <= *sounds) && ((0 < g[0x7515] && (*(char *)((int)g + 0x1d393) == '\0')))) &&
           ((i2 = g[0x7515] + -1, g[0x7515] = i2, i2 == 0 && (*pi1 < *sounds)))) {
          pi7[0x7511] = 3;
          pi7[0x7514] = 0;
          sounds = pi7;
          break;
        }
      }
      if ((pi7[0x7514] == pi8[0x4fd6]) && (pi7[0x74e8] == 0)) {
        GameSndPlay((int *)pi7[0x4155],pi8[0x4fd7],pi8[0x4fd8],0);
        pi7 = g;
      }
      if ((pi7[0x7514] == pi8[0x508a]) && (i2 = pi7[0x7459], i2 <= pi7[0x745a]))
      {
        group = i2 * 4 + 0x1cf60;
        sounds = pi7;
        do {
          player = *(int *)(group + 4 + (int)sounds);
          if (((player == 0) || (*(int *)(player + PLB_ACTIVE) == 0)) ||
             (b2 = true, *(int *)(player + PLB_ISHELPER) != 0)) {
            b2 = false;
          }
          pi7 = sounds;
          if ((b2) &&
             (player = *(int *)((int)sounds + group + 4), *(uint32_t *)(player + PLB_CTRL) = 1,
             pi7 = g, *(int *)(player + PLB_STATENO) != 0)) {
            PlayerChangeState(*(int *)((int)sounds + group + 4),0);
            pi7 = g;
          }
          i2 = i2 + 1;
          group = group + 4;
          sounds = pi7;
        } while (i2 <= pi7[0x745a]);
      }
      if (((pi7[0x7513] == 0) || (*(char *)((int)pi7 + 0x1d38e) != '\0')) ||
         (pi7[0x7514] <= pi7[0x508a])) {
        pi7[0x7516] = pi7[0x7516] + 1;
        pi7 = g;
        goto L_default_0809282e;
      }
      pi7[0x7511] = 3;
      pi7[0x7514] = 0;
      sounds = g;
      if ((pi7[0x7513] != 3) && ((char)pi7[0x74e4] == '\0')) {
        pi7[0x750b] = pi8[0x508b];
        pi7[0x750c] = 500;
        pi7[0x750d] = 500;
        sounds = g;
      }
      break;
    case 3:
      sounds = g + 0x7514;
      g[0x750f] = *sounds;
      if (*sounds == pi8[0x502b]) {
        i2 = pi7[0x7513];
        if (i2 == 3) {
          i2 = pi8[0x5031];
          group = pi8[0x5030];
          sounds = (int *)pi7[0x4155];
        }
        else if (i2 == 2) {
          i2 = pi8[0x502f];
          group = pi8[0x502e];
          sounds = (int *)pi7[0x4155];
        }
        else {
          if (i2 != 1) goto L_08092c58;
          i2 = pi8[0x502d];
          group = pi8[0x502c];
          sounds = (int *)pi7[0x4155];
        }
        GameSndPlay(sounds,group,i2,0);
      }
L_08092c58:
      pi7 = g;
      if (g[0x7513] != 3) {
        if ((g[0x7514] < g[G_ROUND_SLOW_TIME] / 2) && (g[0x7514] == 5)) {
          g[0x750c] = 200;
          pi7[0x750d] = 200;
        }
        if (pi7[0x7514] == pi7[0x508b] / 2) {
          pi7[0x750c] = 100;
          pi7[0x750d] = 100;
          pi7 = g;
        }
        if (pi7[0x7514] == (pi7[0x508b] * 7) / 10) {
          pi7[0x750c] = 0x32;
          pi7[0x750d] = 0x32;
          pi7 = g;
        }
        if (pi7[0x7514] == (pi7[0x508b] * 9) / 10) {
          pi7[0x750c] = 0x19;
          pi7[0x750d] = 0x19;
          pi7 = g;
        }
      }
      sounds = g;
      if (((pi7[0x7514] == pi8[0x508c]) || ((pi7[0x7514] == 0 && (pi7[0x7515] == 0))))
         && (i2 = pi7[0x7459], i2 <= pi7[0x745a])) {
        group = i2 * 4 + 0x1cf60;
        player = group;
        do {
          item = *(int *)(player + 4 + (int)pi7);
          if ((item == 0) || (b2 = true, *(int *)(item + 0x158) == 0)) {
            b2 = false;
          }
          if (b2) {
            *(uint32_t *)(*(int *)(group + 4 + (int)pi7) + 0x244) = 1;
            pi7 = sounds;
          }
          i2 = i2 + 1;
          group = group + 4;
          player = player + 4;
        } while (i2 <= pi7[0x745a]);
      }
      if ((pi7[0x14d0] != 0) && (pi7[0x7514] == pi7[0x508d])) {
        stk_48 = 0;
        stk_60 = 0;
        i2 = 1;
        do {
          group = GameRoundWinner();
          sounds = g;
          if (group != i2) {
            group = *(int *)((int)g + stk_60 + 0xcee0) + 1;
            if (group < *(int *)((int)g + stk_60 + 0xcee4)) {
              ClipboardAppend((int *)g[G_CLIPBOARD],"start pre-caching team %i next %i\n",i2,group);
              group = *(int *)((int)sounds + stk_60 + 0xcee0) * 0x5c + stk_60 + 0xcf48;
L_08092eb2:
              PrecacheRequestTeam((int)sounds + group);
            }
            else if ((2 - g[0x33b3] == stk_48) &&
                    (group = GameMatchWinner(), group == 2 - stk_48)) {
              PrecacheRequestNextArcadeTeam();
            }
            else if ((g[0x33b3] == stk_48) && (group = GameMatchWinner(), group == i2)) {
              group = stk_60 + 0xceec;
              goto L_08092eb2;
            }
          }
          stk_48 = stk_48 + 1;
          stk_60 = stk_60 + 0x1a9c;
          i2 = i2 + 1;
        } while (stk_48 < 2);
        PrecacheStart();
        pi7 = g;
      }
      if (pi8[0x508c] + 0xb4 <= pi7[0x7514]) {
        pi7[0x74e0] = 0;
        pi7 = g;
      }
      b2 = true;
      i2 = pi7[0x7459];
      if (i2 <= pi7[0x745a]) {
        group = i2 * 4 + 0x1cf60;
        player = group;
        stk_5c = group;
        do {
          item = *(int *)(stk_5c + 4 + (int)pi7);
          if (((item == 0) || (*(int *)(item + 0x158) == 0)) ||
             (b3 = true, *(int *)(item + 0x1c) != 0)) {
            b3 = false;
          }
          if (b3) {
            b4 = 0;
            item = *(int *)(player + 4 + (int)pi7);
            if ((((*(int *)(item + 0xe0c) != 0) && (*(int *)(item + 0xe00) == 1)) &&
                (*(int *)(item + 0xe04) == 0)) ||
               (item = PlayerLyingDead(*(int *)(group + 4 + (int)pi7)), pi7 = g, 0 < item))
            {
              b4 = 1;
            }
            b2 = (bool)(b2 & b4);
          }
          i2 = i2 + 1;
          stk_5c = stk_5c + 4;
          group = group + 4;
          player = player + 4;
        } while (i2 <= pi7[0x745a]);
      }
      sounds = g;
      if (899 < pi7[0x7514]) {
        b2 = true;
      }
      if ((!b2) || (pi7[0x7514] < pi8[0x508c])) goto L_default_0809282e;
      i2 = pi7[0x7459];
      if (i2 <= pi7[0x745a]) {
        group = i2 * 4 + 0x1cf60;
        player = group;
        do {
          item = *(int *)(player + 4 + (int)pi7);
          if (((item == 0) || (*(int *)(item + 0x158) == 0)) ||
             (b2 = true, *(int *)(item + 0x1c) != 0)) {
            b2 = false;
          }
          if (b2) {
            *(uint32_t *)(*(int *)(group + 4 + (int)pi7) + 0xe0c) = 0;
            pi7 = sounds;
          }
          i2 = i2 + 1;
          group = group + 4;
          player = player + 4;
        } while (i2 <= pi7[0x745a]);
      }
      pi7[0x7511] = 4;
      pi7[0x7514] = 0;
      pi7[0x750b] = 0;
      sounds = g;
      break;
    case 4:
      goto L_case_0809282e_4;
    default:
      goto L_default_0809282e;
    }
  } while( true );
L_case_0809282e_4:
  g[0x74e0] = 0;
  if (pi8[0x508c] + pi7[0x7514] == pi8[0x502b]) {
    i2 = pi7[0x7513];
    if (i2 == 3) {
      i2 = pi8[0x5031];
      group = pi8[0x5030];
      sounds = (int *)pi7[0x4155];
    }
    else if (i2 == 2) {
      i2 = pi8[0x502f];
      group = pi8[0x502e];
      sounds = (int *)pi7[0x4155];
    }
    else {
      if (i2 != 1) goto L_0809312e;
      i2 = pi8[0x502d];
      group = pi8[0x502c];
      sounds = (int *)pi7[0x4155];
    }
    GameSndPlay(sounds,group,i2,0);
  }
L_0809312e:
  if (g[0x7514] == pi8[0x508e]) {
    i2 = g[G_SLOT_FIRST];
    pi8 = g;
    if (i2 <= g[G_SLOT_LAST]) {
      group = i2 * 4 + 0x1cf60;
      sounds = g;
      do {
        player = *(int *)(group + 4 + (int)sounds);
        if (((player == 0) || (*(int *)(player + PLB_ACTIVE) == 0)) ||
           (b2 = true, *(int *)(player + PLB_ISHELPER) != 0)) {
          b2 = false;
        }
        pi8 = sounds;
        if (b2) {
          player = *(int *)((int)sounds + group + 4);
          if (sounds[0x7512] == *(int *)(player + PLB_TEAMSIDE)) {
            *(uint32_t *)(player + 0x244) = 0;
            pi8 = g;
            if (*(int *)(player + PLB_ALIVE) != 0) {
              item = 0xb4;
L_080931b5:
              player = *(int *)((int)sounds + group + 4);
L_080931ec:
              PlayerChangeState(player,item);
              pi8 = g;
            }
          }
          else if (sounds[0x7512] == 0) {
            if (*(int *)(player + PLB_ALIVE) != 0) {
              item = 0xaf;
              player = *(int *)((int)sounds + group + 4);
              goto L_080931ec;
            }
          }
          else if (*(int *)(player + PLB_ALIVE) != 0) {
            item = 0xaa;
            goto L_080931b5;
          }
        }
        i2 = i2 + 1;
        group = group + 4;
        sounds = pi8;
      } while (i2 <= pi8[0x745a]);
    }
    i2 = pi8[0x7512];
    if (i2 == 0) {
      group = 0x1d410;
      i2 = 0xe970;
      pi8[0x750a] = pi8[0x750a] + 1;
      pi8 = g;
      stk_48 = 1;
      do {
        if (*(int *)(i2 + 4 + (int)pi8) < pi8[0x750a]) {
          *(int *)(group + 0xc + (int)pi8) = *(int *)(group + 0xc + (int)pi8) + 1;
        }
        group = group + 4;
        i2 = i2 + 0x1a9c;
        stk_48 = stk_48 + -1;
      } while (-1 < stk_48);
      pi8[0x7509] = 1;
    }
    else {
      pi8[0x7509] = 1;
      pi8[i2 + 0x7506] = pi8[i2 + 0x7506] + 1;
      i2 = GameMatchWinner();
      pi8 = g;
      if (i2 == 0) {
        player = g[0x7512] + -1;
        i2 = g[player * 0x6a7 + 0x33b8];
        group = 0;
        if (0 < g[i2 * 0x17 + player * 0x6a7 + 0x33bd]) {
          do {
            i13 = group + 1;
            group = g[pi8[i2 * 0x17 + player * 0x6a7 + group * 5 + 0x33be] + G_PLAYERS];
            item = TeamLifeBack(player);
            PlayerLifeSet(group,(item * *(int *)(group + 0x164)) / 1000 +
                                 *(int *)(group + 0x160));
            group = i13;
          } while (i13 < pi8[i2 * 0x17 + player * 0x6a7 + 0x33bd]);
        }
      }
    }
  }
  if ((*(char *)((int)g + 0x1d38d) != '\0') && (g[0x7518] == 0)) {
    g[0x7510] = g[0x7514] + 0x13;
  }
  i2 = g[0x7510] - g[0x7514];
  if (i2 < 0x10) {
    group = GameMatchWinner();
    if (group != 0) {
      GameSetVol(g[G_SOUND_LINUX_MASTERWAVVOLUME] + (0x10 - i2) * -2,g[G_SOUND_LINUX_MIDIVOLUME] + (0x10 - i2) * -2);
    }
    i2 = i2 * 0x10;
    MasterPalMul(i2,i2,i2);
  }
  pi7 = g;
  if (g[0x7510] <= g[0x7514]) {
    i2 = GameMatchWinner();
    pi8 = g;
    if (i2 != 0) {
      g[0x7546] = 1;
      pi8[0x7545] = i2;
    }
    if (g[0x7546] == 0) {
      LogMatch();
      pi8 = g;
      i2 = g[G_SLOT_FIRST];
      if (i2 <= g[G_SLOT_LAST]) {
        group = i2 * 4 + 0x1cf60;
        player = group;
        do {
          item = *(int *)(player + 4 + (int)pi8);
          if (((item == 0) || (*(int *)(item + 0x158) == 0)) ||
             (b2 = true, *(int *)(item + 0x1c) != 0)) {
            b2 = false;
          }
          if (b2) {
            item = *(int *)(group + 4 + (int)pi8);
            *(int *)(item + 0x342c) = *(int *)(item + 0x342c) + 1;
          }
          i2 = i2 + 1;
          group = group + 4;
          player = player + 4;
        } while (i2 <= pi8[0x745a]);
      }
      PrecacheFinish();
      W_Cls(0);
      g[0x7307] = 0;
      DrawToScreen();
      DrawToScreen();
      GameNextRound();
    }
    stk_4c = 1;
    pi7 = g;
  }
L_default_0809282e:
  if (0 < pi7[0x750b]) {
    pi7[0x750b] = pi7[0x750b] + -1;
    pi7 = g;
  }
  if ((pi7[0x750b] == 0) && (pi7[0x750c] != 0)) {
    pi7[0x750c] = 0;
    pi7[0x750d] = 0;
    pi7 = g;
  }
  pi7[0x7514] = pi7[0x7514] + 1;
  return stk_4c;
}
#undef stk_78
#undef stk_74
#undef stk_6c
#undef stk_68
#undef stk_64
#undef stk_60
#undef stk_5c
#undef stk_4c
#undef stk_48
#undef stk_3c

/* GameRoundDraw @ 0x08093540, 956 bytes
 *
 * Draws the round announcements (round number, "Fight", KO, time over, draw,
 * win texts) as fight explods at their times.
 *
 * Globals read: round_fight_time, demo_mode, round_fight, round_pos_0,
 *               round_pos_1, round_round_time, round_no, round_win_time
 * Calls: SysExplodCreate_Fight, GameRoundWinner, ExplodArrayDraw
 * C library: strcpy, sprintf
 * Called by: GameLoop
 *
 * Elecbyte file: src/mugen/gameloop.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x60 bytes, 1
 *       variables), because their address is taken.
 */
void GameRoundDraw(void)

{
  int *pi1;
  int *pi2;
  int *pi3;
  int *pi4;
  int *pi5;
  uint32_t entry_EDX;
  uint32_t stale_EDX;
  int i6;
  int *src;
  int i7;
  unsigned char frame[0x60] __attribute__((aligned(16)));
#define stk_5c (*(char (*)[76])(frame + 0x4))
  
  pi4 = g;
  pi5 = (int *)g[0x73da];
  pi1 = (int *)g[0x73db];
  pi2 = (int *)g[0x73dc];
  pi3 = (int *)g[0x73dd];
  i6 = g[0x7511];
  if (i6 == 2) {
    if ((g[0x7514] == g[G_ROUND_FIGHT_TIME] + 1) && (g[G_DEMO_MODE] == 0)) {
      SysExplodCreate_Fight(g + G_ROUND_FIGHT,g[G_ROUND_POS_0],g[G_ROUND_POS_1]);
    }
  }
  else if (i6 < 3) {
    if (((i6 == 1) && (g[0x750e] == g[G_ROUND_ROUND_TIME] + 2)) && (g[G_DEMO_MODE] == 0)) {
      if (g[G_ROUND_NO] < 10) {
        SysExplodCreate_Fight(g + g[G_ROUND_NO] * 0x1b + 0x4e96,g[G_ROUND_POS_0],g[G_ROUND_POS_1]);
        entry_EDX = stale_EDX;
      }
      src = pi4 + 0x4e8a;
      strcpy(stk_5c,(char *)src);
      sprintf((char *)src,stk_5c,g[G_ROUND_NO],entry_EDX);
      i6 = pi4[0x4e7a];
      pi5 = pi4 + 0x4e7b;
      i7 = pi4[0x4e79];
L_08093848:
      SysExplodCreate_Fight(pi5,i7,i6);
      strcpy((char *)src,stk_5c);
    }
  }
  else if ((i6 == 4) && (g[0x7514] == g[G_ROUND_WIN_TIME] + 1)) {
    i6 = GameRoundWinner();
    if (i6 == 1) {
      if (pi2 == (int *)0x0) {
        src = pi4 + 0x5041;
        strcpy(stk_5c,(char *)src);
        sprintf((char *)src,stk_5c,*pi5 + 0x30);
        i6 = pi4[0x4e7a];
        pi5 = pi4 + 0x5032;
        i7 = pi4[0x4e79];
      }
      else {
        src = pi4 + 0x505c;
        strcpy(stk_5c,(char *)src);
        sprintf((char *)src,stk_5c,*pi5 + 0x30,*pi2 + 0x30);
        i6 = pi4[0x4e7a];
        pi5 = pi4 + 0x504d;
        i7 = pi4[0x4e79];
      }
    }
    else {
      i6 = GameRoundWinner();
      if (i6 == 2) {
        if (pi3 == (int *)0x0) {
          src = pi4 + 0x5041;
          strcpy(stk_5c,(char *)src);
          sprintf((char *)src,stk_5c,*pi1 + 0x30);
          i6 = pi4[0x4e7a];
          pi5 = pi4 + 0x5032;
          i7 = pi4[0x4e79];
        }
        else {
          src = pi4 + 0x505c;
          strcpy(stk_5c,(char *)src);
          sprintf((char *)src,stk_5c,*pi1 + 0x30,*pi3 + 0x30);
          i6 = pi4[0x4e7a];
          pi5 = pi4 + 0x504d;
          i7 = pi4[0x4e79];
        }
      }
      else {
        if (g[0x7513] != 3) goto L_08093860;
        src = pi4 + 0x5077;
        strcpy(stk_5c,(char *)src);
        sprintf((char *)src,stk_5c,*pi1 + 0x30);
        i6 = pi4[0x4e7a];
        i7 = pi4[0x4e79];
        pi5 = pi4 + 0x5068;
      }
    }
    goto L_08093848;
  }
L_08093860:
  if (1 < g[0x7511] - 3U) goto L_080938d7;
  i6 = g[0x7514];
  if (g[0x7511] == 4) {
    i6 = i6 + g[0x750f];
  }
  if (i6 != pi4[0x502a] + 1) goto L_080938d7;
  i6 = g[0x7513];
  if (i6 == 3) {
    pi5 = pi4 + 0x500f;
L_080938bf:
    i6 = pi4[0x4e7a];
    i7 = pi4[0x4e79];
  }
  else {
    if (i6 != 2) {
      if (i6 != 1) goto L_080938d7;
      pi5 = pi4 + 0x4fd9;
      goto L_080938bf;
    }
    pi5 = pi4 + 0x4ff4;
    i6 = pi4[0x4e7a];
    i7 = pi4[0x4e79];
  }
  SysExplodCreate_Fight(pi5,i7,i6);
L_080938d7:
  if (g[0x7307] == 0) {
    ExplodArrayDraw((int *)g[0x52bf],-1);
  }
  return;
}
#undef stk_5c

/* GameInputUpdate @ 0x08093900, 2629 bytes
 *
 * Per-frame input: polls keyboard and joysticks and passes the events to the
 * players or the training menu. Handles pause and frame advance, and, when
 * debug keys are allowed, the debug keys. The code tests these raw keys:
 * Space, F1, F2, F3, F4, F5, F8, F12, Scroll Lock, and the letters C, D, F,
 * I, L, S, T, V, alone or with Ctrl, Shift or Alt. The effects include debug
 * display, collision boxes, life refill and KO of either side (Shift / Ctrl
 * + F1 set life to 1), speed and pause controls, and screenshots.
 *
 * Player fields read: active, ishelper, stateno, lifemax
 * Player fields written: life, alive, ctrl, vel_y, vel_x
 * Globals read: debug_allowdebugkeys, demo_mode, slot_first, slot_last,
 *               clipboard, debug_allowdebugmode
 * Globals written: vretrace, speed_flag, frameskip
 * Calls: PadPoll, KBPoll, KBkbhit, KBgetchraw, PadHit, PadGet,
 *        GlobalInputUpdate, IntCircBufClear, TrainingMenuUpdate, UInpHit,
 *        UInpGet, IntCircBufStuff, PlayerChangeState, PlayerLifeSet,
 *        ClipboardClear, PlayerEnableSet, TimerSyncReset,
 *        TrainingMenuReset, ScreenSnap
 * Called by: GameLoop
 *
 * Elecbyte file: src/mugen/gameloop.c
 * Note: 3 byte results widened with ZEXT8 (upper bytes are zero).
 */
uint32_t GameInputUpdate(void)

{
  int player;
  int player2;
  int i3;
  uint32_t *clipboard;
  bool b5;
  uint32_t stale_var;
  uint32_t stale_var_00;
  int player3;
  uint32_t stale_var_01;
  bool b7;
  int *pi8;
  int *pi9;
  int player4;
  int i11;
  int player5;
  int player6;
  uint32_t u14;
  uint32_t stk_18;
  uint32_t stk_14;
  
  stk_18 = 0;
  player4 = g[0x73da];
  player5 = g[0x73db];
  player = g[0x73dc];
  player2 = g[0x73dd];
  b7 = false;
  stk_14 = 0;
  if ((g[0x81cb] != 0) || (g[G_DEBUG_ALLOWDEBUGKEYS] != 0)) {
    b7 = true;
  }
  g[0x7309] = (int)(char)keypauseflag;
  PadPoll();
  KBPoll();
  b5 = KBkbhit();
  if (ZEXT8(b5) != 0) {
    stk_18 = KBgetchraw();
  }
  b5 = PadHit();
  if (ZEXT8(b5) != 0) {
    stk_14 = PadGet();
  }
  GlobalInputUpdate();
  IntCircBufClear((int)(g + 0x7391));
  u14 = 0;
  while( true ) {
    player3 = TrainingMenuUpdate(u14);
    if (player3 != 0) {
      keypauseflag = 0;
    }
    b5 = UInpHit();
    if (ZEXT8(b5) == 0) break;
    u14 = UInpGet();
    IntCircBufStuff(g + 0x7391,u14);
  }
  if (stk_18 == 1) {
    g[0x4135] = 1;
  }
  pi8 = g;
  if ((g[G_DEMO_MODE] != 0) &&
     ((((stk_18 != 0 && ((stk_18 & 0x100) == 0)) && (stk_18 != 0x46)) ||
      ((stk_14 != 0 && ((stk_14 & 0x100) == 0)))))) {
    g[0x4135] = 1;
    pi8[0x82d2] = 0;
  }
  if (b7) {
    if ((stk_18 == 0x39) || (keyflag[0x39] != 0)) {
      player3 = g[G_SLOT_FIRST];
      pi8 = g;
      if (player3 <= g[G_SLOT_LAST]) {
        i11 = player3 * 4 + 0x1cf60;
        do {
          player6 = *(int *)(i11 + 4 + (int)pi8);
          if (((player6 == 0) || (*(int *)(player6 + PLB_ACTIVE) == 0)) ||
             (b5 = true, *(int *)(player6 + PLB_ISHELPER) != 0)) {
            b5 = false;
          }
          if (b5) {
            player6 = *(int *)((int)pi8 + i11 + 4);
            if (*(int *)(player6 + PLB_STATENO) == 0x141e) {
              PlayerChangeState(player6,0x1400);
              pi8 = g;
            }
            player6 = *(int *)(i11 + 4 + (int)pi8);
            *(uint32_t *)(player6 + PLB_LIFE) = *(uint32_t *)(player6 + PLB_LIFEMAX);
            *(uint32_t *)(player6 + PLB_ALIVE) = 1;
            *(uint32_t *)(player6 + 0x198) = 1;
            *(uint32_t *)(player6 + 0x1010) = 0;
            *(uint32_t *)(player6 + 0x100c) = 0;
            **(uint32_t **)(player6 + 0x170) = **(uint32_t **)(player6 + 0x174);
            pi8 = g;
          }
          player3 = player3 + 1;
          i11 = i11 + 4;
        } while (player3 <= pi8[0x745a]);
      }
      if ((pi8[0x33ae] != 3) && (pi8[0x74e8] == 0)) {
        pi8[0x7515] = (pi8[0x79a0] + 1) * pi8[0x4e61] + -1;
      }
    }
    if (stk_18 == 0x3b) {
      if ((keyflag[0x9d] == 0) && (keyflag[0x1d] == 0)) {
        PlayerLifeSet(player5,0);
        player3 = player2;
      }
      else {
        PlayerLifeSet(player4,0);
        player3 = player;
      }
      if (player3 != 0) {
        PlayerLifeSet(player3,0);
      }
    }
    if (stk_18 == 0x3c) {
      if (((keyflag[0x36] == 0) && (keyflag[0x2a] == 0)) && (PlayerLifeSet(player4,1), player != 0)) {
        PlayerLifeSet(player,1);
      }
      if (((keyflag[0x9d] == 0) && (keyflag[0x1d] == 0)) && (PlayerLifeSet(player5,1), player2 != 0)) {
        PlayerLifeSet(player2,1);
      }
    }
    if ((keyflag[0x3d] != 0) || (stk_18 == 0x3d)) {
      **(uint32_t **)(player4 + 0x170) = **(uint32_t **)(player4 + 0x174);
      **(uint32_t **)(player5 + 0x170) = **(uint32_t **)(player5 + 0x174);
    }
    pi8 = g;
    if (stk_18 == 0x3e) {
      player3 = g[G_SLOT_FIRST];
      if (player3 <= g[G_SLOT_LAST]) {
        i11 = player3 * 4 + 0x1cf60;
        player6 = i11;
        do {
          i3 = *(int *)(player6 + 4 + (int)pi8);
          if (((i3 == 0) || (*(int *)(i3 + 0x158) == 0)) ||
             (b5 = true, *(int *)(i3 + 0x1c) != 0)) {
            b5 = false;
          }
          if (b5) {
            i3 = *(int *)(i11 + 4 + (int)pi8);
            *(uint32_t *)(i3 + 0x160) = *(uint32_t *)(i3 + 0x164);
          }
          player3 = player3 + 1;
          i11 = i11 + 4;
          player6 = player6 + 4;
        } while (player3 <= pi8[0x745a]);
      }
      if ((keyflag[0x36] == 0) && (keyflag[0x2a] == 0)) {
        pi8[0x82d4] = 1;
      }
      else {
        pi8[0x82d5] = 1;
      }
    }
    if (stk_18 == 0x3f) {
      g[0x7515] = 1;
    }
    if (stk_18 == 0x42) {
      ClipboardClear((uint32_t *)g[G_CLIPBOARD]);
      player3 = g[G_SLOT_FIRST];
      if (player3 <= g[G_SLOT_LAST]) {
        i11 = player3 * 4 + 0x1cf60;
        pi8 = g;
        player6 = i11;
        do {
          i3 = *(int *)(player6 + 4 + (int)pi8);
          if ((i3 == 0) || (b5 = true, *(int *)(i3 + 0x158) == 0)) {
            b5 = false;
          }
          if ((b5) &&
             (clipboard = *(uint32_t **)(*(int *)(i11 + 4 + (int)pi8) + 0x345c),
             clipboard != (uint32_t *)0x0)) {
            ClipboardClear(clipboard);
            pi8 = g;
          }
          player3 = player3 + 1;
          i11 = i11 + 4;
          player6 = player6 + 4;
        } while (player3 <= pi8[0x745a]);
      }
    }
  }
  if ((keyflag[0x1d] != 0) || (keyflag[0x9d] != 0)) {
    if (b7) {
      if ((keyflag[0x38] == 0) && (keyflag[0xb8] == 0)) {
        if (stk_18 == 2) {
          *(uint32_t *)(player4 + 0x262c) = *(uint32_t *)(player4 + 0x262c) ^ 1;
        }
        if (stk_18 == 3) {
          *(uint32_t *)(player5 + 0x262c) = *(uint32_t *)(player5 + 0x262c) ^ 1;
        }
        if ((stk_18 == 4) && (player != 0)) {
          *(uint32_t *)(player + 0x262c) = *(uint32_t *)(player + 0x262c) ^ 1;
        }
        if ((stk_18 == 5) && (player2 != 0)) {
          *(uint32_t *)(player2 + 0x262c) = *(uint32_t *)(player2 + 0x262c) ^ 1;
        }
      }
      else {
        if (stk_18 == 2) {
          PlayerEnableSet(*(int *)(player4 + 8),(uint32_t)(*(int *)(player4 + PLB_ACTIVE) == 0));
        }
        if (stk_18 == 3) {
          PlayerEnableSet(*(int *)(player5 + 8),(uint32_t)(*(int *)(player5 + PLB_ACTIVE) == 0));
        }
        if ((stk_18 == 4) && (player != 0)) {
          PlayerEnableSet(*(int *)(player + 8),(uint32_t)(*(int *)(player + PLB_ACTIVE) == 0));
        }
        if ((stk_18 == 5) && (player2 != 0)) {
          PlayerEnableSet(*(int *)(player2 + 8),(uint32_t)(*(int *)(player2 + PLB_ACTIVE) == 0));
        }
      }
      if (stk_18 == 0x2f) {
        if (g[G_VRETRACE] == 0) {
          g[G_VRETRACE] = 1;
        }
        else {
          g[G_VRETRACE] = 0;
        }
      }
      if (stk_18 == 0x1f) {
        if (g[G_SPEED_FLAG] == 0) {
          g[G_SPEED_FLAG] = 1;
        }
        else {
          g[G_SPEED_FLAG] = 0;
          TimerSyncReset();
        }
      }
      pi8 = g;
      if (stk_18 == 0x21) {
        player4 = g[G_FRAMESKIP];
        g[G_FRAMESKIP] = player4 + 1;
        if (player4 + 1 == 3) {
          pi8[0x7305] = 2000;
          pi8[0x6ef3] = 0;
        }
        pi8 = g;
        if (2000 < g[G_FRAMESKIP]) {
          g[G_FRAMESKIP] = -1;
          pi8[0x6ef3] = 1;
        }
      }
      if ((1999 < pi8[0x7305]) && (pi8[0x82d2] == 0)) {
        pi8[0x7305] = -1;
        pi8[0x6ef3] = 1;
        pi8 = g;
      }
      if (stk_18 == 0x26) {
        pi8[0x52bd] = (uint32_t)(pi8[0x52bd] == 0);
        pi8 = g;
      }
      pi9 = pi8;
      if ((stk_18 == 0x2e) &&
         (player4 = pi8[0x81d0], pi8[0x81d0] = player4 + 1, pi9 = g, 2 < player4 + 1)) {
        pi8[0x81d0] = 0;
        pi9 = g;
      }
      if ((stk_18 == 0x17) && (player4 = pi9[0x7459], player4 <= pi9[0x745a])) {
        player5 = player4 * 4 + 0x1cf60;
        do {
          player = *(int *)(player5 + 4 + (int)pi9);
          if (((player == 0) || (*(int *)(player + PLB_ACTIVE) == 0)) ||
             (b7 = true, *(int *)(player + PLB_ISHELPER) != 0)) {
            b7 = false;
          }
          if (b7) {
            PlayerChangeState(*(int *)(player5 + 4 + (int)pi9),0);
            pi9 = g;
            player = *(int *)(player5 + 4 + (int)g);
            *(uint32_t *)(player + PLB_CTRL) = 1;
            *(uint32_t *)(player + PLB_VEL_Y) = 0;
            *(uint32_t *)(player + PLB_VEL_X) = 0;
          }
          player4 = player4 + 1;
          player5 = player5 + 4;
        } while (player4 <= pi9[0x745a]);
      }
      if ((pi9[0x81cc] != 0) && (stk_18 == 0x14)) {
        pi9[0x33b6] = 0;
        if ((pi9[0x73db] == 0) || (b7 = true, *(int *)(pi9[0x73db] + 0x158) == 0)) {
          b7 = false;
        }
        if (b7) {
          *(uint32_t *)(g[0x73db] + 0x262c) = 0;
        }
        pi9 = g;
        pi8 = g + 0x33ae;
        g[0x7515] = -1;
        pi9[0x33ae] = (uint32_t)(*pi8 != 3) * 3;
        TrainingMenuReset();
      }
    }
    pi8 = g;
    if ((stk_18 == 0x20) && (g[G_DEBUG_ALLOWDEBUGMODE] != 0)) {
      do {
        pi8[0x81cd] = 1;
        *(uint32_t *)(pi8[0x82d7] + 0x20) = 1;
        player4 = pi8[0x81cb];
        pi8[0x81cb] = player4 + 1;
        if ((pi8[player4 + 0x73da] == 0) ||
           (b7 = true, *(int *)(pi8[player4 + 0x73da] + 0x158) == 0)) {
          b7 = false;
        }
        pi9 = g;
      } while ((!b7) && (pi9 = pi8, pi8[0x81cb] < pi8[0x745a]));
      if (pi9[0x745a] < pi9[0x81cb]) {
        pi9[0x81cd] = 0;
        *(uint32_t *)(pi9[0x82d7] + 0x20) = 0;
        pi9[0x81cb] = 0;
      }
    }
  }
  if (framestep_0 != 0) {
    framestep_0 = 0;
    keypauseflag = 1;
  }
  if ((((g[0x7309] != 0) && (stk_18 != 0)) && (framestep_0 == 0)) &&
     (((stk_18 & 0x100) == 0 && (stk_18 != 0x58)))) {
    if ((g[0x33ae] != 3) || (stk_18 == 0x46)) {
      keypauseflag = 0;
    }
    if (stk_18 == 0x46) {
      framestep_0 = 1;
    }
  }
  if (g[0x74e2] == 1) {
    ScreenSnap();
    g[0x74e2] = 0;
  }
  if (stk_18 == 0x58) {
    if (g[0x7309] == 0) {
      ScreenSnap();
    }
    else {
      g[0x74e2] = 1;
    }
  }
  return 0;
}

/* CameraMoveAbs @ 0x08094350, 119 bytes
 *
 * Moves the camera to an absolute position (round start, win screens).
 *
 * Parameters:
 *   arg1         float
 *   arg2         float
 *
 * Called by: ArcadeWinScreen, GamePlay, GameRoundReset,
 *            SurvivalResultsScreen
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
int CameraMoveAbs(float arg1,float arg2)

{
  int *pi1;
  
  pi1 = g;
  g[0x730f] = BITS_F2I(int, arg1);
  pi1[0x7313] = BITS_F2I(int, arg1);
  pi1[0x7310] = BITS_F2I(int, arg2);
  pi1[0x7314] = BITS_F2I(int, arg2);
  pi1[0x7311] = (int)X87_FIST32(arg1);
  pi1[0x7312] = (int)X87_FIST32(arg2);
  return (int)X87_FIST32(arg2);
}

/* CameraMoveP @ 0x080943d0, 2350 bytes
 *
 * Moves the camera to follow the players: horizontally keeps them inside the
 * screen with the stage tension and bounds, vertically follows jumps with
 * floortension and verticalfollow. Inactive during passive screens.
 *
 * Player fields read: pos_x, statetype, vel_x
 * Globals read: camera_tension, camera_floortension,
 *               camera_verticalfollow, slot_first, slot_last,
 *               camera_boundleft
 * Calls: GameModeInPassiveFightScreen, PlayerCalcDraw, PlayerGetWidth
 * Called by: GameUpdate, PlayerUpdate, PlayerUpdateBindTo
 *
 * Elecbyte file: src/mugen/gameloop.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: 4 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 16 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: 4 temporaries are float80, as the original kept them in x87 registers.
 */
void CameraMoveP(void)

{
  float80 f1;
  float80 f2;
  float80 f3;
  float80 f4;
  bool b5;
  uint32_t stale_var;
  int width;
  int width2;
  int *pi8;
  int *pi9;
  int i10;
  int i11;
  int i12;
  int player;
  int width3;
  int i15;
  float stk_38;
  int stk_24;
  int player2;
  
  player = 0;
  player2 = 0;
  stk_24 = 0;
  i10 = g[G_CAMERA_TENSION];
  i12 = g[G_CAMERA_FLOORTENSION];
  f1 = BITS_I2F(g[G_CAMERA_VERTICALFOLLOW]);
  stk_38 = 1.0;
  f2 = BITS_I2F(g[0x7313]);
  f3 = BITS_I2F(g[0x7314]);
  b5 = GameModeInPassiveFightScreen();
  if (ZEXT8(b5) != 0) {
    return;
  }
  i15 = g[G_SLOT_FIRST];
  pi9 = g;
  if (i15 <= g[G_SLOT_LAST]) {
    i11 = i15 * 4 + 0x1cf60;
    width3 = i11;
    do {
      width2 = *(int *)(width3 + 4 + (int)pi9);
      if ((width2 == 0) || (b5 = true, *(int *)(width2 + 0x158) == 0)) {
        b5 = false;
      }
      if (b5) {
        PlayerCalcDraw(*(int *)(i11 + 4 + (int)pi9));
        pi9 = g;
      }
      i15 = i15 + 1;
      i11 = i11 + 4;
      width3 = width3 + 4;
    } while (i15 <= pi9[0x745a]);
  }
  i15 = pi9[0x7459];
  if (i15 <= pi9[0x745a]) {
    i11 = i15 * 4 + 0x1cf60;
    do {
      width3 = *(int *)(i11 + 4 + (int)pi9);
      if ((width3 == 0) || (b5 = true, *(int *)(width3 + 0x158) == 0)) {
        b5 = false;
      }
      if (b5) {
        width3 = *(int *)((int)pi9 + i11 + 4);
        if (*(int *)(width3 + 0x1e8) != 0) {
          if (player != 0) {
            width2 = PlayerGetWidth(*(int *)((int)pi9 + i11 + 4),3,4);
            f4 = *(float *)(*(int *)((int)g + i11 + 4) + 0x19c);
            width = PlayerGetWidth(player,3,4);
            pi9 = g;
            width3 = player;
            if ((int)X87_FIST32(f4) - width2 < (int)X87_FIST32(*(float *)(player + PLB_POS_X)) - width) {
              width3 = *(int *)(i11 + 4 + (int)g);
            }
          }
          player = width3;
          if (player2 != 0) {
            width3 = PlayerGetWidth(*(int *)(i11 + 4 + (int)pi9),4,4);
            f4 = *(float *)(*(int *)((int)g + i11 + 4) + 0x19c);
            width2 = PlayerGetWidth(player2,4,4);
            pi9 = g;
            if ((int)X87_FIST32(f4) + width3 <= (int)X87_FIST32(*(float *)(player2 + PLB_POS_X)) + width2)
            goto L_08094646;
          }
          player2 = *(int *)(i11 + 4 + (int)pi9);
        }
L_08094646:
        width3 = *(int *)(i11 + 4 + (int)pi9);
        if ((*(int *)(width3 + 0x1ec) != 0) &&
           ((stk_24 == 0 || (*(float *)(width3 + 0x1a0) < *(float *)(stk_24 + 0x1a0))))) {
          stk_24 = width3;
        }
      }
      i15 = i15 + 1;
      i11 = i11 + 4;
    } while (i15 <= pi9[0x745a]);
  }
  if (((stk_24 != 0) && (player != 0)) && (player2 != 0)) {
    width2 = PlayerGetWidth(player,3,4);
    width3 = PlayerGetWidth(player2,4,4);
    i15 = (int)X87_FIST32((((float80)(int)X87_FIST32(*(float *)(player + PLB_POS_X)) - BITS_I2F(g[0x730f])) -
                        (float80)i10) - (float80)width2);
    i11 = (int)X87_FIST32(((float)(0x13f - i10) -
                        ((float80)(int)X87_FIST32(*(float *)(player2 + PLB_POS_X)) - BITS_I2F(g[0x730f]))) -
                        (float80)width3);
    width2 = (int)X87_FIST32(*(float *)(player + PLB_POS_X)) - width2;
    i10 = width3 + -0xa0 + (int)X87_FIST32(*(float *)(player2 + PLB_POS_X));
    width3 = width2 + -0xa0;
    if (*(int *)(player + PLB_STATETYPE) == 3) {
      i15 = i15 + -1;
      width3 = width2 + -0xa1;
    }
    if (*(int *)(player + PLB_STATETYPE) == 4) {
      width3 = width3 + -2;
      i15 = i15 + -2;
    }
    if (*(int *)(player2 + PLB_STATETYPE) == 3) {
      i10 = i10 + 1;
      i11 = i11 + -1;
    }
    if (*(int *)(player2 + PLB_STATETYPE) == 4) {
      i10 = i10 + 2;
      i11 = i11 + -2;
    }
    if (((i15 < 0) && (i11 < 0)) ||
       (((i15 < -1 || (i11 < -1)) && (i15 + i11 < 0)))) {
      g[0x7313] = BITS_F2I(int, (float)((i10 + width3) / 2));
    }
    else {
      if (i15 < -1) {
        f4 = (float80)i15 + BITS_I2F(g[0x730f]);
      }
      else {
        if (-2 < i11) goto L_080948b2;
        f4 = BITS_I2F(g[0x730f]) - (float80)i11;
      }
      g[0x7313] = BITS_F2I(int, f4);
    }
L_080948b2:
    pi9 = g;
    if (((*(float *)(player + PLB_VEL_X) < -1.0) && (i15 < 0)) && (0 < i11)) {
      stk_38 = ABS(*(float *)(player + PLB_VEL_X));
    }
    if (((stk_38 < *(float *)(player2 + PLB_VEL_X)) && (i11 < 0)) && (0 < i15)) {
      stk_38 = ABS(*(float *)(player2 + PLB_VEL_X));
    }
    g[0x7314] = BITS_F2I(int, ((float80)(int)X87_FIST32((float80)i12 + *(float *)(stk_24 + 0x1a0)) * f1));
  }
  if (pi9[0x7511] != 0) {
    pi9[0x7313] = BITS_F2I(int, (float)((int)X87_FIST32(f2 + BITS_I2F(pi9[0x7313])) / 2));
    pi9[0x7314] = BITS_F2I(int, (BITS_I2F(pi9[0x7314]) * ((double)0.15) + f3 * ((double)0.85)));
  }
  pi8 = g;
  if (g[0x7309] != 0) goto L_08094b58;
  if (pi9[0x7511] == 0) {
    g[0x730f] = g[0x7313];
  }
  if (BITS_I2F(pi8[0x730f]) < BITS_I2F(pi8[0x7313])) {
    pi8[0x730f] = BITS_F2I(int, (BITS_I2F(pi8[0x730f]) + stk_38));
    pi8 = g;
  }
  if (BITS_I2F(pi8[0x7313]) < BITS_I2F(pi8[0x730f])) {
    pi8[0x730f] = BITS_F2I(int, (BITS_I2F(pi8[0x730f]) - stk_38));
    pi8 = g;
  }
  if (BITS_I2F(pi8[0x7314]) <= BITS_I2F(pi8[0x7310])) {
    if (BITS_I2F(pi8[0x7310]) <= BITS_I2F(pi8[0x7314])) goto L_08094b58;
    f2 = BITS_I2F(pi8[0x7310]) - 0.5;
    pi8[0x7310] = BITS_F2I(int, f2);
    if (BITS_I2F(pi8[0x7314]) + 5.0 < f2) {
      pi8[0x7310] = BITS_F2I(int, (f2 - (f2 - BITS_I2F(pi8[0x7314])) * f1 * ((float)0.1f)));
    }
    f1 = BITS_I2F(g[0x7314]);
    pi8 = g;
    if (f1 + 0.5 < BITS_I2F(g[0x7310])) goto L_08094b58;
  }
  else {
    f2 = BITS_I2F(pi8[0x7310]) + 0.5;
    pi8[0x7310] = BITS_F2I(int, f2);
    if (f2 < BITS_I2F(pi8[0x7314]) - 5.0) {
      pi8[0x7310] = BITS_F2I(int, ((BITS_I2F(pi8[0x7314]) - f2) * f1 * ((float)0.1f) + f2));
    }
    f1 = BITS_I2F(g[0x7314]);
    pi8 = g;
    if (BITS_I2F(g[0x7310]) < f1 - 0.5) goto L_08094b58;
  }
  pi8 = g;
  g[0x7310] = BITS_F2I(int, f1);
L_08094b58:
  i10 = (int)X87_FIST32(BITS_I2F(pi8[0x730f]) - BITS_I2F(pi8[0x7313]));
  if (i10 < 0) {
    i10 = -i10;
  }
  if ((float80)i10 <= stk_38 + stk_38) {
    pi8[0x730f] = pi8[0x7313];
  }
  pi9 = g;
  if (BITS_I2F(g[0x730f]) < (float)g[G_CAMERA_BOUNDLEFT]) {
    g[0x730f] = BITS_F2I(int, (float)g[G_CAMERA_BOUNDLEFT]);
  }
  if ((float80)pi9[0x1083] < BITS_I2F(pi9[0x730f])) {
    pi9[0x730f] = BITS_F2I(int, (float80)pi9[0x1083]);
    pi9 = g;
  }
  if ((float80)pi9[0x1085] < BITS_I2F(pi9[0x7310])) {
    pi9[0x7310] = BITS_F2I(int, (float80)pi9[0x1085]);
    pi9 = g;
  }
  if (BITS_I2F(pi9[0x7310]) < (float80)pi9[0x1084]) {
    pi9[0x7310] = BITS_F2I(int, (float80)pi9[0x1084]);
    pi9 = g;
  }
  pi9[0x7311] = (int)X87_FIST32(BITS_I2F(pi9[0x730f]));
  i10 = pi9[0x7459];
  pi9[0x7312] = (int)X87_FIST32(BITS_I2F(pi9[0x7310]));
  if (i10 <= pi9[0x745a]) {
    i12 = i10 * 4 + 0x1cf60;
    pi9 = g;
    player = i12;
    do {
      i15 = *(int *)(player + 4 + (int)pi9);
      if ((i15 == 0) || (b5 = true, *(int *)(i15 + 0x158) == 0)) {
        b5 = false;
      }
      if (b5) {
        PlayerCalcDraw(*(int *)(i12 + 4 + (int)pi9));
        pi9 = g;
      }
      i10 = i10 + 1;
      i12 = i12 + 4;
      player = player + 4;
    } while (i10 <= pi9[0x745a]);
  }
  return;
}

/* ComboAdd @ 0x08094d00, 112 bytes
 *
 * Adds hits to a side's combo counter and restarts its display time.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Called by: Player1HitP2, Player1ReverseP2, PlayerCheckProjHit,
 *            PlayerSCtrlApplyElem
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
void ComboAdd(int arg1,int arg2)

{
  int *pi1;
  int i2;
  int i3;
  int *pi4;
  
  pi4 = g;
  if (arg1 - 1U < 2) {
    i2 = g[arg1 * 6 + 0x7542];
    pi1 = g + arg1 * 6 + 0x7541;
    g[arg1 * 6 + 0x7542] = arg2 + i2;
    if ((pi4[arg1 * 6 + 0x7541] == 0) && (1 < arg2 + i2)) {
      pi4[arg1 * 6 + 0x7545] = pi4[0x4e64];
    }
    i2 = pi4[arg1 * 6 + 0x7542];
    if (1 < i2) {
      i3 = pi4[0x4e65];
      pi4[arg1 * 6 + 0x7544] = i2;
      *pi1 = i3;
      if (999 < i2) {
        pi4[arg1 * 6 + 0x7544] = 999;
      }
    }
  }
  return;
}

/* ComboClear @ 0x08094d70, 32 bytes
 *
 * Resets a side's combo counter. Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
void ComboClear(int arg1)

{
  if (arg1 - 1U < 2) {
    g[arg1 * 6 + 0x7542] = 0;
  }
  return;
}

/* ComboDisplay @ 0x08094d90, 696 bytes
 *
 * Draws a side's combo counter (count and text with the combo fonts) while
 * it is displayed, sliding in from the screen edge.
 *
 * Parameters:
 *   arg1         int
 *
 * Globals read: combo_pos_1, video_linux_doubleres
 * Calls: V_FontDrawBank, V_FontWriteBank, V_FontDrawRightBank,
 *        FontGetWidth
 * C library: sprintf
 * Called by: GameLoop
 *
 * Elecbyte file: src/mugen/gameloop.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x70 bytes, 2
 *       variables), because their address is taken.
 */
void ComboDisplay(int arg1)

{
  int *pi1;
  int i2;
  int i3;
  int *pi4;
  int i5;
  int *pi6;
  int i7;
  uint32_t u8;
  unsigned char frame[0x70] __attribute__((aligned(16)));
#define stk_68 (*(int *)(frame + 0x8))
#define stk_5c (*(char (*)[76])(frame + 0x14))
  
  pi4 = g;
  if (arg1 - 1U < 2) {
    pi1 = g + arg1 * 6 + 0x7541;
    i5 = g[arg1 * 6 + 0x7544];
    if (1 < i5) {
      stk_68 = g[G_COMBO_POS_1];
      if (g[G_VIDEO_LINUX_DOUBLERES] == 4) {
        stk_68 = stk_68 * 2;
      }
      if (arg1 + -1 == 0) {
        i2 = g[arg1 * 6 + 0x7545];
        i7 = 0;
        sprintf(stk_5c,(char *)(g + 0x4e6d),i5);
        if (pi4[0x4e66] != -1) {
          u8 = (uint32_t)(9 < pi4[arg1 * 6 + 0x7544]);
          if (pi4[arg1 * 6 + 0x7544] < 100) {
            i7 = u8 + 1;
          }
          else {
            i7 = u8 + 2;
          }
          i7 = *(int *)(g[pi4[0x4e66] + 0x414b] + 8) * i7;
        }
        pi6 = (int *)pi4[0x4e6a];
        u8 = 0;
        V_FontDrawBank(stk_5c,(int *)g[pi4[0x4e69] + 0x414b],i2 + i7 + pi4[0x4e6b],
                       stk_68 + pi4[0x4e6c],(int)pi6);
        if (pi4[0x4e68] != 0) {
          i5 = pi4[0x4e65];
          i7 = *pi1;
          u8 = (uint32_t)(i7 == i5 + -1);
          if (i7 == i5 + -2) {
            u8 = 2;
          }
          if (i7 == i5 + -3) {
            u8 = 1;
          }
          if (i7 == i5 + -5) {
            u8 = 1;
          }
          pi6 = pi1;
          if (i7 == i5 + -7) {
            u8 = 1;
          }
        }
        if (pi4[0x4e66] != -1) {
          V_FontWriteBank((int *)g[pi4[0x4e66] + 0x414b],i2 + u8,stk_68,pi4[0x4e67],
                          "%i",pi4[arg1 * 6 + 0x7544],pi6,pi6);
        }
      }
      else {
        i7 = (V_Width - g[arg1 * 6 + 0x7545]) + -1;
        sprintf(stk_5c,(char *)(g + 0x4e6d),i5,arg1 + -1);
        V_FontDrawRightBank(stk_5c,(int *)g[pi4[0x4e69] + 0x414b],i7,
                            stk_68 + pi4[0x4e6c],pi4[0x4e6a]);
        if (pi4[0x4e66] != -1) {
          i5 = FontGetWidth(g[pi4[0x4e69] + 0x414b],stk_5c);
          i5 = i5 + pi4[0x4e6b];
          if (pi4[0x4e68] != 0) {
            i2 = pi4[0x4e65];
            i3 = pi4[arg1 * 6 + 0x7541];
            if (i3 == i2 + -1) {
              i5 = i5 + 1;
            }
            if (i3 == i2 + -2) {
              i5 = i5 + 2;
            }
            if (i3 == i2 + -3) {
              i5 = i5 + 1;
            }
            if (i3 == i2 + -5) {
              i5 = i5 + 1;
            }
            if (i3 == i2 + -7) {
              i5 = i5 + 1;
            }
          }
          sprintf(stk_5c,"%i",pi4[arg1 * 6 + 0x7544],pi4);
          V_FontDrawRightBank(stk_5c,(int *)g[pi4[0x4e66] + 0x414b],i7 - i5,stk_68,
                              pi4[0x4e67]);
        }
      }
    }
  }
  return;
}
#undef stk_68
#undef stk_5c

/* ComboDisplayUpdate @ 0x08095050, 189 bytes
 *
 * Advances a side's combo display timer and slide.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: GameLoop
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
void ComboDisplayUpdate(int arg1)

{
  int *pi1;
  int *pi2;
  int i3;
  int i4;
  
  pi2 = g;
  if (arg1 - 1U < 2) {
    pi1 = g + arg1 * 6 + 0x7541;
    if (g[arg1 * 6 + 0x7546] == 0) {
      g[arg1 * 6 + 0x7542] = 0;
    }
    pi2[arg1 * 6 + 0x7546] = 0;
    if (0 < pi2[arg1 * 6 + 0x7541]) {
      i4 = pi2[arg1 * 6 + 0x7545];
      if (i4 < pi2[0x4e62]) {
        i3 = pi2[0x4e62] - i4;
        if (i3 < 0) {
          i3 = i3 + 7;
        }
        i4 = (i3 >> 3) + 1 + i4;
        pi2[arg1 * 6 + 0x7545] = i4;
        if (pi2[0x4e62] < i4) {
          pi2[arg1 * 6 + 0x7545] = pi2[0x4e62];
        }
      }
      *pi1 = *pi1 + -1;
    }
    if ((pi2[arg1 * 6 + 0x7542] < 2) && (*pi1 == 0)) {
      i4 = pi2[arg1 * 6 + 0x7545];
      i3 = pi2[0x4e64];
      if (i3 < i4) {
        i4 = i4 + -3;
        pi2[arg1 * 6 + 0x7545] = i4;
        i3 = pi2[0x4e64];
      }
      if (i4 < i3) {
        pi2[arg1 * 6 + 0x7545] = i3;
        pi2[arg1 * 6 + 0x7544] = 0;
      }
    }
  }
  return;
}

/* PlayerComboCountCheck @ 0x08095110, 155 bytes
 *
 * Ends a side's combo when its targets have recovered or are lying dead
 * (removes such targets).
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: ArrayScanFirst, PlayerLyingDead, ArrayDelete, ArrayScanNext
 * Called by: GameUpdate
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
void PlayerComboCountCheck(int arg1)

{
  int *item;
  int i2;
  
  item = (int *)ArrayScanFirst(*(int *)(arg1 + 0x220));
  while( true ) {
    if (item == (int *)0x0) {
      *(uint32_t *)(arg1 + 0x1398) = 0;
      return;
    }
    if (((*(int *)(*item + 0xe04) == 2) && (i2 = PlayerLyingDead(*item), i2 == 0)) ||
       ((*(int *)(arg1 + 0x1158) != 0 && (*(int *)(arg1 + 0x1204) != 0)))) break;
    ArrayDelete(*(int *)(arg1 + 0x220),*(int *)(*(int *)(arg1 + 0x220) + 0x1c));
    item = (int *)ArrayScanNext(*(int *)(arg1 + 0x220));
  }
  g[*(int *)(arg1 + 0xc) * 6 + 0x7546] = 1;
  return;
}

/* GameBGDraw @ 0x080951b0, 309 bytes
 *
 * Draws the stage background layer at the current camera position (with
 * zoffset), or a solid box when the background is disabled.
 *
 * Globals written: stageinfo_zoffset
 * Calls: BGArrayMoveOffset, BGArrayDrawLayer, BGAccessID, W_BoxFill
 * Called by: ContinueScreenLoop, GameLoop
 *
 * Elecbyte file: src/mugen/gameloop.c
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
void GameBGDraw(void)

{
  int *pi1;
  int i2;
  
  BGArrayMoveOffset((int *)g[0x6ed4],(float)g[0x7311],(float)g[0x7312],-g[0x7315],-g[0x7316]);
  BGArrayDrawLayer(g[0x6ed4],0);
  pi1 = g;
  g[G_STAGEINFO_ZOFFSET] = g[0x4141];
  i2 = pi1[0x4142];
  if (i2 != -1) {
    i2 = BGAccessID(pi1[0x6ed4],i2);
    if (i2 != 0) {
      g[G_STAGEINFO_ZOFFSET] = (int)X87_FIST32((float)g[G_STAGEINFO_ZOFFSET] +
                             ((float80)*(int *)(i2 + 0x10) -
                             (float)g[0x7312] * *(float *)(i2 + 0x20)) + ((double)0.999999));
    }
  }
  if (0 < g[0x7316]) {
    W_BoxFill(0,V_Height + -1,V_Width + -1,V_Height - g[0x7316],0);
  }
  if (g[0x7316] < 0) {
    W_BoxFill(0,0,V_Width + -1,g[0x7316] ^ 0xffffffff,0);
  }
  return;
}

/* GameFGDraw @ 0x080952f0, 26 bytes
 *
 * Draws the stage foreground layer.
 *
 * Calls: BGArrayDrawLayer
 * Called by: ContinueScreenLoop, GameLoop
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
void GameFGDraw(void)

{
  BGArrayDrawLayer(g[0x6ed4],1);
  return;
}

/* GameBarsDraw @ 0x08095310, 4327 bytes
 *
 * Draws the fight screen: life bars (single, simul, turns), power bars,
 * faces, names, the round timer, win icons, using the fight.def system
 * explods.
 *
 * Parameters:
 *   arg1         int
 *
 * Globals read: time_bg
 * Calls: SysExplodCreateDraw_Fight, GameLifeBarDraw, GamePowerBarDraw,
 *        SysExplodCreateDraw
 * C library: sprintf, strncpy
 * Called by: GameLoop
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
void GameBarsDraw(int arg1)

{
  int *pi1;
  int *pi2;
  int *sysexplod;
  uint32_t stale_EDX;
  uint32_t u4;
  uint32_t stale_EDX_00;
  int *pi5;
  int i2;
  int *sysexplod2;
  int *pi8;
  int *sysexplod3;
  int j;
  int *sysexplod4;
  int i12;
  int k;
  char *format;
  int stk_c4;
  int stk_c0;
  int stk_bc;
  int stk_b8;
  int stk_b4;
  int stk_b0;
  int stk_ac;
  int stk_a8;
  int stk_a4;
  int *sysexplod5;
  int stk_9c;
  int stk_98;
  int stk_94;
  int *stk_90;
  int stk_8c;
  int *stk_88;
  int *sysexplod6;
  int stk_80;
  int stk_7c;
  int stk_78;
  int *stk_74;
  int stk_70;
  int stk_6c;
  int stk_68;
  int *stk_64;
  int stk_60;
  int *sysexplod7;
  int *stk_58;
  int stk_54;
  int *stk_50;
  int stk_34;
  int stk_30;
  int stk_2c;
  
  pi2 = g;
  stk_50 = g;
  sysexplod4 = g + 0x46cf;
  sysexplod = g + G_TIME_BG;
  pi8 = g + 0x4157;
  pi5 = g + 0x5090;
  stk_30 = 0;
  stk_c4 = 0;
  do {
    stk_2c = 0;
    stk_ac = 0;
    stk_b8 = 0;
    stk_bc = 0;
    stk_c0 = 0x1cf6c;
    do {
      if (*(int *)(stk_c0 + 4 + (int)stk_50) == 0) {
        stk_34 = 1;
        sysexplod2 = pi8;
        if (1 < *(int *)((int)stk_50 + stk_ac + 0xcee4)) {
          sysexplod2 = pi2 + 0x449f;
        }
      }
      else {
        stk_34 = 3;
        sysexplod2 = pi2 + 0x426f;
      }
      if (stk_2c < stk_34 + stk_2c) {
        sysexplod3 = (int *)((int)sysexplod2 + stk_bc + stk_c4 + 0x14);
        i2 = stk_b8;
        i12 = stk_2c;
        do {
          i12 = i12 + 2;
          j = i2 + 4;
          pi1 = (int *)((int)sysexplod2 + i2);
          i2 = i2 + 0x460;
          SysExplodCreateDraw_Fight(sysexplod3,*pi1,*(int *)((int)sysexplod2 + j),arg1);
          sysexplod3 = sysexplod3 + 0x118;
        } while (i12 < stk_34 + stk_2c);
        stk_50 = g;
      }
      stk_2c = stk_2c + 1;
      stk_ac = stk_ac + 0x1a9c;
      stk_b8 = stk_b8 + 0x230;
      stk_bc = stk_bc + 0x230;
      stk_c0 = stk_c0 + 4;
    } while (stk_2c < 2);
    stk_30 = stk_30 + 1;
    stk_c4 = stk_c4 + 0x6c;
  } while (stk_30 < 3);
  stk_2c = 0;
  while( true ) {
    if (stk_50[stk_2c + 0x73dc] == 0) {
      stk_34 = 1;
      sysexplod2 = pi8;
      if (1 < stk_50[stk_2c * 0x6a7 + 0x33b9]) {
        sysexplod2 = pi2 + 0x449f;
      }
    }
    else {
      stk_34 = 3;
      sysexplod2 = pi2 + 0x426f;
    }
    i2 = stk_2c;
    if (stk_2c < stk_34 + stk_2c) {
      while( true ) {
        GameLifeBarDraw(i2 + 1,stk_50[i2 + 0x73da],sysexplod2 + i2 * 0x8c,arg1);
        if (stk_34 + stk_2c <= i2 + 2) break;
        stk_50 = g;
        i2 = i2 + 2;
      }
    }
    stk_2c = stk_2c + 1;
    if (1 < stk_2c) break;
    stk_50 = g;
  }
  stk_30 = 0;
  pi8 = sysexplod4;
  do {
    sysexplod2 = pi8 + 5;
    i12 = 1;
    i2 = 0;
    do {
      j = i2 + 4;
      sysexplod3 = (int *)((int)sysexplod4 + i2);
      i2 = i2 + 0x230;
      SysExplodCreateDraw_Fight(sysexplod2,*sysexplod3,*(int *)(j + (int)sysexplod4),arg1);
      sysexplod2 = sysexplod2 + 0x8c;
      i12 = i12 + -1;
    } while (-1 < i12);
    pi8 = pi8 + 0x1b;
    stk_30 = stk_30 + 1;
  } while (stk_30 < 3);
  i2 = 0;
  do {
    i12 = i2 + 1;
    GamePowerBarDraw(i12,g[i2 + 0x73da],pi2[i2 * 0x8c + 0x46d1] + sysexplod4[i2 * 0x8c],
                     sysexplod4[i2 * 0x8c + 1],pi2[i2 * 0x8c + 0x46d2] + sysexplod4[i2 * 0x8c]
                     ,arg1);
    i2 = i12;
  } while (i12 < 2);
  sysexplod2 = pi2 + 0x47e7;
  i2 = 0;
  pi8 = pi2 + 0x47f6;
  i12 = 1;
  stk_a8 = 0x1cf64;
  u4 = stale_EDX;
  do {
    sprintf((char *)pi8,"%i",*(int *)(*(int *)((int)g + stk_a8 + 4) + 0x180) / 1000,u4);
    pi8 = pi8 + 0x1b;
    j = i2 + 4;
    sysexplod3 = (int *)((int)sysexplod4 + i2);
    i2 = i2 + 0x230;
    SysExplodCreateDraw_Fight(sysexplod2,*sysexplod3,*(int *)(j + (int)sysexplod4),arg1);
    sysexplod2 = sysexplod2 + 0x1b;
    stk_a8 = stk_a8 + 4;
    i12 = i12 + -1;
    u4 = stale_EDX_00;
  } while (-1 < i12);
  sysexplod5 = pi2 + 0x4add;
  stk_50 = g;
  stk_2c = 0;
  stk_a4 = 0;
  do {
    if (stk_50[0x33b4] != 2 - stk_2c) {
      i2 = *(int *)((int)stk_50 + stk_a4 + 0xcee4);
      if (1 < i2) {
        k = 0;
        i12 = sysexplod5[0x51];
        j = sysexplod5[0x52];
        if (0 < i2 + -1) {
          do {
            k = k + 1;
            SysExplodCreateDraw_Fight(sysexplod5,i12,j,arg1);
            j = j + sysexplod5[0x55];
            i12 = i12 + sysexplod5[0x54];
          } while (k < *(int *)((int)stk_50 + stk_a4 + 0xcee4) + -1);
          stk_50 = g;
        }
      }
    }
    stk_2c = stk_2c + 1;
    sysexplod5 = sysexplod5 + 0x56;
    stk_a4 = stk_a4 + 0x1a9c;
  } while (stk_2c < 2);
  stk_2c = 0;
  stk_98 = 0x1cf6c;
  stk_9c = 0;
  stk_b4 = 0;
  do {
    if (*(int *)(stk_98 + 4 + (int)stk_50) == 0) {
      stk_34 = 1;
      pi8 = pi2 + 0x4831;
      if (1 < *(int *)((int)stk_50 + stk_9c + 0xcee4)) {
        pi8 = pi2 + 0x49f9;
      }
    }
    else {
      stk_34 = 3;
      pi8 = pi2 + 0x4915;
    }
    if (stk_2c < stk_34 + stk_2c) {
      i2 = stk_2c * 4;
      sysexplod4 = (int *)(stk_b4 + (int)pi8);
      i12 = stk_2c;
      do {
        i12 = i12 + 2;
        j = i2 + 0x370;
        k = i2 + 0x360;
        i2 = i2 + 8;
        SysExplodCreateDraw_Fight
                  (sysexplod4,*(int *)((int)pi8 + k),*(int *)((int)pi8 + j),arg1);
        sysexplod4 = sysexplod4 + 0x6c;
      } while (i12 < stk_34 + stk_2c);
      stk_50 = g;
    }
    stk_2c = stk_2c + 1;
    stk_98 = stk_98 + 4;
    stk_9c = stk_9c + 0x1a9c;
    stk_b4 = stk_b4 + 0xd8;
  } while (stk_2c < 2);
  stk_2c = 0;
  i2 = 0;
  i12 = 0x1cf6c;
  do {
    if (*(int *)(i12 + 4 + (int)stk_50) == 0) {
      stk_34 = 1;
      pi8 = pi2 + 0x4831;
      if (1 < *(int *)((int)stk_50 + i2 + 0xcee4)) {
        pi8 = pi2 + 0x49f9;
      }
    }
    else {
      stk_34 = 3;
      pi8 = pi2 + 0x4915;
    }
    stk_34 = stk_2c + -1 + stk_34;
    if (-1 < stk_34) {
      while( true ) {
        SysExplodCreateDraw((int *)stk_50[0x52bf],pi8 + stk_34 * 0x36 + 0x1b,
                            *(int **)(stk_50[stk_34 + 0x73da] + 0x13ac),
                            *(int **)(*(int *)stk_50[stk_34 + 0x73da] + 0x11cc),
                            (int)(stk_50 + 0x414b),pi8[stk_34 + 0xd8],pi8[stk_34 + 0xdc]
                            ,arg1);
        stk_34 = stk_34 + -2;
        if (stk_34 < 0) break;
        stk_50 = g;
      }
      stk_50 = g;
    }
    i12 = i12 + 4;
    stk_2c = stk_2c + 1;
    i2 = i2 + 0x1a9c;
  } while (stk_2c < 2);
  stk_90 = pi2 + 0x4add;
  stk_2c = 0;
  stk_94 = 0;
  do {
    pi8 = stk_50;
    if (stk_50[0x33b4] != 2 - stk_2c) {
      sysexplod4 = (int *)((int)stk_50 + stk_94 + 0xcee0);
      i2 = *(int *)((int)stk_50 + stk_94 + 0xcee4);
      if (1 < i2) {
        k = 0;
        i12 = stk_90[0x51];
        j = stk_90[0x52];
        if (0 < i2) {
          do {
            if (k != *sysexplod4) {
              i2 = k + stk_2c * 4;
              if (pi2[i2 + 0x52b5] != 0) {
                SysExplodCreateDraw((int *)stk_50[0x52bf],stk_90 + 0x1b,
                                    (int *)pi2[i2 + 0x52b5],(int *)pi2[0x414a],
                                    (int)(stk_50 + 0x414b),i12,j,arg1);
                stk_50 = g;
              }
              i12 = i12 + stk_90[0x54];
              j = j + stk_90[0x55];
            }
            k = k + 1;
          } while (k < *(int *)((int)pi8 + stk_94 + 0xcee4));
        }
      }
    }
    stk_2c = stk_2c + 1;
    stk_90 = stk_90 + 0x56;
    stk_94 = stk_94 + 0x1a9c;
  } while (stk_2c < 2);
  sysexplod6 = pi2 + 0x4b13;
  stk_88 = pi2 + 0x4add;
  stk_8c = 0;
  stk_2c = 1;
  do {
    if (1 < *(int *)((int)stk_50 + stk_8c + 0xcee4)) {
      j = 0;
      i2 = stk_88[0x51];
      i12 = stk_88[0x52];
      if (0 < *(int *)((int)stk_50 + stk_8c + 0xcee0)) {
        do {
          j = j + 1;
          SysExplodCreateDraw_Fight(sysexplod6,i2,i12,arg1);
          i2 = i2 + stk_88[0x54];
          i12 = i12 + stk_88[0x55];
        } while (j < *(int *)((int)stk_50 + stk_8c + 0xcee0));
        stk_50 = g;
      }
    }
    sysexplod6 = sysexplod6 + 0x56;
    stk_88 = stk_88 + 0x56;
    stk_8c = stk_8c + 0x1a9c;
    stk_2c = stk_2c + -1;
  } while (-1 < stk_2c);
  stk_2c = 0;
  stk_7c = 0x1cf6c;
  stk_80 = 0;
  stk_b0 = 0;
  do {
    if (*(int *)(stk_7c + 4 + (int)stk_50) == 0) {
      stk_34 = 1;
      pi8 = pi2 + 0x4b89;
      if (1 < *(int *)((int)stk_50 + stk_80 + 0xcee4)) {
        pi8 = pi2 + 0x4d49;
      }
    }
    else {
      stk_34 = 3;
      pi8 = pi2 + 0x4c69;
    }
    if (stk_2c < stk_34 + stk_2c) {
      i2 = stk_2c * 4;
      sysexplod4 = (int *)(stk_b0 + (int)pi8);
      i12 = stk_2c;
      do {
        i12 = i12 + 2;
        j = i2 + 0x370;
        k = i2 + 0x360;
        i2 = i2 + 8;
        SysExplodCreateDraw_Fight
                  (sysexplod4,*(int *)((int)pi8 + k),*(int *)((int)pi8 + j),arg1);
        sysexplod4 = sysexplod4 + 0x36;
      } while (i12 < stk_34 + stk_2c);
      stk_50 = g;
    }
    i2 = stk_2c + 1;
    stk_7c = stk_7c + 4;
    stk_80 = stk_80 + 0x1a9c;
    stk_b0 = stk_b0 + 0x6c;
    stk_2c = i2;
  } while (i2 < 2);
  stk_2c = 0;
  while( true ) {
    if (stk_50[stk_2c + 0x73dc] == 0) {
      stk_34 = 1;
      pi8 = pi2 + 0x4b89;
      if (1 < stk_50[stk_2c * 0x6a7 + 0x33b9]) {
        pi8 = pi2 + 0x4d49;
      }
    }
    else {
      stk_34 = 3;
      pi8 = pi2 + 0x4c69;
    }
    i12 = stk_2c;
    j = stk_2c;
    if (stk_2c < stk_34 + stk_2c) {
      while( true ) {
        i12 = j + 2;
        strncpy((char *)(pi8 + j * 0x1b + 0x7b),
                (char *)(*(int *)stk_50[j + 0x73da] + 0x30),0x2f);
        i2 = pi8[j + 0xd8];
        SysExplodCreateDraw_Fight(pi8 + j * 0x1b + 0x6c,i2,pi8[j + 0xdc],arg1)
        ;
        if (stk_34 + stk_2c <= i12) break;
        stk_50 = g;
        j = i12;
      }
    }
    stk_2c = stk_2c + 1;
    if (1 < stk_2c) break;
    stk_50 = g;
  }
  SysExplodCreateDraw_Fight(sysexplod,pi2[0x4e5f],pi2[0x4e60],arg1);
  if (g[0x7515] == -1) {
    j = 0x6f;
    format = "%c";
  }
  else {
    j = g[0x7515] / pi2[0x4e61];
    format = "%i";
    i2 = i12;
  }
  sprintf((char *)(pi2 + 0x4e53),format,j,i2);
  i2 = 0;
  SysExplodCreateDraw_Fight(pi2 + 0x4e44,pi2[0x4e5f],pi2[0x4e60],arg1);
  stk_58 = pi2 + 0x509f;
  stk_54 = 0x870;
  stk_60 = 0;
  stk_68 = 0;
  stk_6c = 0x1d410;
  stk_70 = 0x880;
  stk_78 = 0;
  stk_74 = pi5;
  stk_64 = pi5;
  sysexplod7 = pi5;
  do {
    stk_50 = g;
    i12 = *(int *)(stk_60 + 0x1d41c + (int)g);
    if (pi2[0x52b4] < i12) {
      sprintf((char *)stk_58,"%i",*(uint32_t *)(stk_60 + 0x1d41c + (int)g),i12);
      SysExplodCreateDraw_Fight
                (sysexplod7,*(int *)((int)pi2 + stk_60 + 0x14ab0),
                 *(int *)(stk_54 + 8 + (int)pi5),arg1);
    }
    else {
      stk_30 = 0;
      if (0 < i12) {
        i12 = stk_78 * 4 + 0x1d450;
        j = stk_60;
        do {
          k = *(int *)(i12 + 0x14 + (int)stk_50);
          if (k != -1) {
            SysExplodCreateDraw_Fight
                      (stk_74 + k * 0x1b + 0x36,
                       stk_30 * *(int *)(j + 0x880 + (int)pi5) +
                       *(int *)(j + 0x870 + (int)pi5),
                       stk_30 * *(int *)((int)pi2 + j + 0x14ac8) +
                       *(int *)((int)pi2 + j + 0x14ab8),arg1);
            stk_50 = g;
          }
          stk_30 = stk_30 + 1;
          i12 = i12 + 4;
          k = j + 0x1d41c;
          j = i2 * 4;
        } while (stk_30 < *(int *)(k + (int)stk_50));
      }
      stk_30 = 0;
      if (0 < *(int *)(stk_60 + 0x1d41c + (int)stk_50)) {
        i12 = stk_68 * 4 + 0x1d4a0;
        do {
          j = *(int *)(i12 + 0x14 + (int)stk_50);
          if (j != -1) {
            SysExplodCreateDraw_Fight
                      (stk_64 + j * 0x1b + 0x36,
                       stk_30 * *(int *)(stk_70 + (int)pi5) +
                       *(int *)(stk_54 + (int)pi5),
                       stk_30 * *(int *)((int)pi2 + stk_70 + 0x14248) +
                       *(int *)((int)pi2 + stk_54 + 0x14248),arg1);
            stk_50 = g;
          }
          stk_30 = stk_30 + 1;
          i12 = i12 + 4;
        } while (stk_30 < *(int *)(stk_6c + 0xc + (int)stk_50));
      }
    }
    stk_54 = stk_54 + 4;
    stk_58 = stk_58 + 0x1b;
    sysexplod7 = sysexplod7 + 0x1b;
    stk_60 = stk_60 + 4;
    stk_64 = stk_64 + 0xf3;
    stk_68 = stk_68 + 10;
    stk_6c = stk_6c + 4;
    stk_70 = stk_70 + 4;
    stk_74 = stk_74 + 0xf3;
    stk_78 = stk_78 + 10;
    i2 = i2 + 1;
  } while (i2 < 2);
  return;
}

/* GameLifeBarDraw @ 0x08096400, 1210 bytes
 *
 * Draws one life bar: background, the red damage part that shrinks after a
 * hit, the current life, and the front, clipped to the bar's range.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         int
 *   arg3         int *
 *   arg4         int
 *
 * Globals read: video_linux_doubleres, debug_display
 * Calls: W_Define, SysExplodCreateDraw_Fight, V_FontDraw, V_FontDrawRight
 * C library: sprintf, makecol
 * Called by: GameBarsDraw
 *
 * Elecbyte file: src/mugen/gameloop.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x140 bytes,
 *       3 variables), because their address is taken.
 */
void GameLifeBarDraw(uint32_t arg1,int arg2,int *arg3,int arg4)

{
  int i1;
  int i2;
  int i3;
  int i4;
  uint32_t u5;
  int i6;
  int i7;
  int i8;
  uint32_t u9;
  uint32_t u10;
  int *font;
  unsigned char frame[0x140] __attribute__((aligned(16)));
#define stk_134 (*(int *)(frame + 0xc))
#define stk_120 (*(uint32_t *)(frame + 0x20))
#define text (*(char (*)[268])(frame + 0x24))
  
  i4 = W_y1;
  i3 = W_x2;
  i2 = W_x1;
  i1 = W_y2;
  stk_134 = -1;
  i7 = (g[G_VIDEO_LINUX_DOUBLERES] == 4) + 1;
  i8 = arg3[1] * i7;
  u9 = (*arg3 + arg3[2]) * i7;
  u10 = (*arg3 + arg3[3]) * i7;
  u5 = u9;
  if (u9 - u10 != 0 && (int)u10 <= (int)u9) {
    stk_134 = 1;
    u5 = u10;
    u10 = u9;
  }
  u9 = (int)(*(int *)(arg2 + 0x16c) * (u10 - u5)) / *(int *)(arg2 + 0x164);
  i7 = (int)(*(int *)(arg2 + 0x168) * (u10 - u5)) / *(int *)(arg2 + 0x164);
  stk_120 = i7 + 1U & (*(int *)(arg2 + 0x168) == 0) - 1;
  if ((int)u9 < (int)stk_120) {
    stk_120 = u9;
  }
  W_Define(u5,W_y1,u10,W_y2);
  if (stk_134 == 1) {
    i6 = *(int *)(arg2 + 0x168);
    if (i6 < *(int *)(arg2 + 0x16c)) {
      W_Define(u10 - stk_120,i4,u10 - u9,i1);
      SysExplodCreateDraw_Fight(arg3 + 0x56,*arg3,arg3[1],arg4);
      i6 = *(int *)(arg2 + 0x168);
    }
    if (0 < i6) {
      W_Define(u10 - i7,i4,u10,i1);
      SysExplodCreateDraw_Fight(arg3 + 0x71,*arg3,arg3[1],arg4);
    }
    if ((g[G_DEBUG_DISPLAY] == 0) || (arg3[0x79] != arg4)) goto L_08096896;
    W_Define(u5,0,u10,V_Height - 1);
    sprintf(text,"%i",*(uint32_t *)(arg2 + 0x160));
    u5 = makecol(0x80,0x80,0);
    V_FontDraw(text,(int *)g[0x413a],(u10 - i7) + 1,i8 + 5,u5);
    sprintf(text,"%3i",*(int *)(arg2 + 0x16c) - *(int *)(arg2 + 0x160));
    if (*(int *)(arg2 + 0x16c) == *(int *)(arg2 + 0x160) ||
        *(int *)(arg2 + 0x16c) - *(int *)(arg2 + 0x160) < 0) goto L_08096896;
    u9 = makecol(0x80,0,0);
    i7 = (u10 - stk_120) + -0xb;
    font = (int *)g[0x413a];
  }
  else {
    i6 = *(int *)(arg2 + 0x168);
    if (i6 < *(int *)(arg2 + 0x16c)) {
      W_Define(u5 + stk_120,i4,u5 + u9,i1);
      SysExplodCreateDraw_Fight(arg3 + 0x56,*arg3,arg3[1],arg4);
      i6 = *(int *)(arg2 + 0x168);
    }
    if (0 < i6) {
      W_Define(u5 + i7,i4,u5,i1);
      SysExplodCreateDraw_Fight(arg3 + 0x71,*arg3,arg3[1],arg4);
    }
    if ((g[G_DEBUG_DISPLAY] == 0) || (arg3[0x79] != arg4)) goto L_08096896;
    W_Define(u5,0,u10,V_Height - 1);
    sprintf(text,"%i",*(uint32_t *)(arg2 + 0x160));
    u10 = makecol(0x80,0x80,0);
    V_FontDrawRight(text,(int *)g[0x413a],i7 + -1 + u5,i8 + 5,u10);
    sprintf(text,"%i",*(int *)(arg2 + 0x16c) - *(int *)(arg2 + 0x160));
    if (*(int *)(arg2 + 0x16c) == *(int *)(arg2 + 0x160) ||
        *(int *)(arg2 + 0x16c) - *(int *)(arg2 + 0x160) < 0) goto L_08096896;
    u9 = makecol(0x80,0,0);
    i7 = stk_120 + 1 + u5;
    font = (int *)g[0x413a];
  }
  V_FontDraw(text,font,i7,i8 + 5,u9);
L_08096896:
  W_Define(i2,i4,i3,i1);
  return;
}
#undef stk_134
#undef stk_120
#undef text

/* GameBarsUpdate @ 0x080968c0, 110 bytes
 *
 * Updates the life and power bars of both sides.
 *
 * Calls: GameLifeBarUpdate, GamePowerBarUpdate
 * Called by: GameLoop
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
void GameBarsUpdate(void)

{
  int player;
  int player2;
  int player3;
  int player4;
  
  player = g[0x73da];
  player2 = g[0x73db];
  player3 = g[0x73dc];
  player4 = g[0x73dd];
  GameLifeBarUpdate(player);
  GameLifeBarUpdate(player2);
  if (player3 != 0) {
    GameLifeBarUpdate(player3);
  }
  if (player4 != 0) {
    GameLifeBarUpdate(player4);
  }
  GamePowerBarUpdate(player);
  GamePowerBarUpdate(player2);
  return;
}

/* GameLifeBarUpdate @ 0x08096930, 372 bytes
 *
 * Moves a life bar's displayed damage toward the real life after the hit.
 *
 * Parameters:
 *   player       int
 *
 * Player fields read: lifemax, life, movetype
 * Calls: PlayerLyingDead
 * Called by: GameBarsUpdate
 *
 * Elecbyte file: src/mugen/gameloop.c
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 */
void GameLifeBarUpdate(int player)

{
  int i1;
  int i2;
  int i3;
  int i4;
  
  i2 = (*(int *)(player + PLB_LIFEMAX) * 9) / 1000;
  i4 = *(int *)(player + PLB_LIFEMAX) / 0x19;
  if (i2 == 0) {
    i2 = 1;
  }
  if (i4 == 0) {
    i4 = 1;
  }
  if ((g[0x7309] == 0) && (g[0x750d] == 0)) {
    i1 = *(int *)(player + 0x168);
    i3 = *(int *)(player + PLB_LIFE);
    if (i3 < i1) {
      i1 = (int)X87_FIST32((double)i1 - ((double)(i1 - i3) * ((double)0.1) + (double)i2));
      i3 = *(int *)(player + PLB_LIFE);
      *(int *)(player + 0x168) = i1;
      if (i1 < i3) {
        *(int *)(player + 0x168) = i3;
        i1 = i3;
      }
    }
    if (i1 < i3) {
      if (i3 - i1 < i4) {
        i4 = i3 - i1;
      }
      *(int *)(player + 0x168) = i4 + i1;
    }
    if (((*(int *)(player + PLB_MOVETYPE) != 2) || (i2 = PlayerLyingDead(player), 0x3c < i2)) &&
       (i2 = *(int *)(player + 0x168), i2 == *(int *)(player + PLB_LIFE))) {
      i4 = *(int *)(player + 0x16c);
      if (i2 < i4) {
        i4 = (int)X87_FIST32((double)i4 - (double)(i4 - i2) * ((double)0.1));
        i2 = *(int *)(player + 0x168);
        *(int *)(player + 0x16c) = i4;
      }
      if (i4 < i2) {
        *(int *)(player + 0x16c) = i2;
      }
    }
  }
  return;
}

/* GamePowerBarDraw @ 0x08096ab0, 338 bytes
 *
 * Draws one power bar and its level counter.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         uint32_t
 *   arg5         int
 *   arg6         int
 *
 * Globals read: video_linux_doubleres
 * Calls: W_Define, SysExplodCreateDraw_Fight
 * Called by: GameBarsDraw
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
uint32_t
GamePowerBarDraw(int arg1,int arg2,int arg3,uint32_t arg4,int arg5,int arg6)

{
  int *pi1;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  uint32_t u7;
  uint32_t u8;
  uint32_t u9;
  uint32_t u10;
  int i11;
  int stk_28;
  
  i5 = W_y1;
  i4 = W_x2;
  i3 = W_x1;
  i2 = W_y2;
  pi1 = g;
  stk_28 = -1;
  i6 = (g[G_VIDEO_LINUX_DOUBLERES] == 4) + 1;
  u10 = arg3 * i6;
  u8 = arg5 * i6;
  u9 = u8;
  if (u10 - u8 != 0 && (int)u8 <= (int)u10) {
    stk_28 = 1;
    u9 = u10;
    u10 = u8;
  }
  i6 = (int)(((u9 - u10) + 1) * *(int *)(arg2 + 0x180)) / **(int **)(arg2 + 0x174);
  if (stk_28 == 1) {
    if (i6 < 1) goto L_08096bd6;
    W_Define((u9 - i6) + 1,0,u9,V_Height - 1);
    i6 = pi1[arg1 * 0x8c + 0x4644];
    i11 = pi1[arg1 * 0x8c + 0x4643];
  }
  else {
    if (i6 < 1) goto L_08096bd6;
    W_Define(i6 + -1 + u10,0,u10,V_Height - 1);
    i6 = pi1[arg1 * 0x8c + 0x4644];
    i11 = pi1[arg1 * 0x8c + 0x4643];
  }
  SysExplodCreateDraw_Fight(pi1 + arg1 * 0x8c + 0x46b4,i11,i6,arg6);
L_08096bd6:
  u7 = W_Define(i3,i5,i4,i2);
  return u7;
}

/* GamePowerBarUpdate @ 0x08096c10, 225 bytes
 *
 * Updates a power bar and plays the level sound when a new power level is
 * reached.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: GameSndPlay
 * Called by: GameBarsUpdate
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
int GamePowerBarUpdate(int arg1)

{
  int i1;
  int i2;
  int i3;
  
  if ((g[0x7309] == 0) && (g[0x750d] == 0)) {
    i2 = *(int *)(arg1 + 0x180);
    i3 = *(int *)(arg1 + 0x178);
    if (i2 < i3) {
      i2 = (i3 - i2) / 0x14 + 0xf + i2;
      *(int *)(arg1 + 0x180) = i2;
    }
    if (i2 <= i3) goto L_08096c71;
    *(int *)(arg1 + 0x180) = i3;
  }
  i3 = *(int *)(arg1 + 0x178);
L_08096c71:
  i1 = i3 / 1000;
  i2 = *(int *)(arg1 + 0x184);
  if (i2 != i1) {
    if ((i2 < i1) && (i1 < 10)) {
      GameSndPlay((int *)g[0x4155],g[*(int *)(arg1 + 0x178) / 1000 + 0x481d],g[i1 + 0x4827],0)
      ;
      i3 = *(int *)(arg1 + 0x178);
    }
    i2 = i3 * 0x10624dd3;
    *(int *)(arg1 + 0x184) = i3 / 1000;
  }
  return i2;
}

/* RequestNewAftImg @ 0x08096d00, 48 bytes
 *
 * Returns the afterimage record of a player slot for a new effect.
 *
 * Parameters:
 *   array        int
 *
 * Calls: ArrayAccessGrpItem
 * Called by: PlayerSCtrlApplyElem, SCtrlInitProjectile
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
int RequestNewAftImg(int array)

{
  int item;
  int i2;
  
  i2 = 0;
  if (0 < *(int *)(array + ARRAY_CAPACITY)) {
    do {
      item = ArrayAccessGrpItem(array,0,i2);
      if (*(int *)(item + 8) == 0) {
        return item;
      }
      i2 = i2 + 1;
    } while (i2 < *(int *)(array + ARRAY_CAPACITY));
  }
  return 0;
}

/* GameAftImgReset @ 0x08096d30, 53 bytes
 *
 * Stops the afterimage of a player slot.
 *
 * Parameters:
 *   array        int
 *
 * Calls: ArrayAccessGrpItem
 * Called by: GameRoundReset
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
void GameAftImgReset(int array)

{
  int item;
  int i2;
  
  item = 0;
  if (0 < *(int *)(array + ARRAY_CAPACITY)) {
    do {
      i2 = item + 1;
      item = ArrayAccessGrpItem(array,0,item);
      *(uint32_t *)(item + 0x18) = 0;
      *(uint32_t *)(item + 8) = 0;
      item = i2;
    } while (i2 < *(int *)(array + ARRAY_CAPACITY));
  }
  return;
}

/* GameAftImgCount @ 0x08096d70, 49 bytes
 *
 * Returns the number of afterimage records. Not called in this build.
 *
 * Parameters:
 *   array        int
 *
 * Calls: ArrayAccessGrpItem
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
int GameAftImgCount(int array)

{
  int item;
  int i2;
  int i3;
  
  i3 = 0;
  i2 = 0;
  if (0 < *(int *)(array + ARRAY_CAPACITY)) {
    do {
      item = ArrayAccessGrpItem(array,0,i2);
      if (*(int *)(item + 8) != 0) {
        i3 = i3 + 1;
      }
      i2 = i2 + 1;
    } while (i2 < *(int *)(array + ARRAY_CAPACITY));
  }
  return i3;
}

/* PlayerAftImgUpdate @ 0x08096db0, 200 bytes
 *
 * Records a player's current frame into its afterimage trail.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: AftImgUpdate
 * Called by: GameUpdate
 *
 * Elecbyte file: src/mugen/gameloop.c
 * Note: untyped (undefined4) <-> float moves kept as bit copies: 0 assignments,
 *       1 calls, 0 returns
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void PlayerAftImgUpdate(int arg1)

{
  int *pi1;
  float80 f2;
  int i3;
  
  pi1 = *(int **)(arg1 + 0x1394);
  if ((*(int *)(arg1 + 0x15c) == 0) && (pi1 != (int *)0x0)) {
    if (*(int *)(arg1 + 0x1380) == 0) {
      f2 = 0.0;
    }
    else {
      f2 = *(float *)(arg1 + 0x137c);
    }
    i3 = AftImgUpdate(pi1,(float)g[0x7311] + *(float *)(arg1 + 0x1354),(float)g[0x7312] + *(float *)(arg1 + 0x1358),*(float *)(arg1 + 0x7c) * *(float *)(arg1 + 0x1348) *
                         *(float *)(arg1 + 0x134c),BITS_F2I(uint32_t, *(float *)(arg1 + 0x80) * *(float *)(arg1 + 0x1348) *
                         *(float *)(arg1 + 0x1350)),f2,(uint32_t)(*(int *)(arg1 + 400) != 1),(uint32_t)(*(int *)(arg1 + 0xe18) == 0));
    if (i3 == 0) {
      pi1[2] = 0;
      *(uint32_t *)(arg1 + 0x1394) = 0;
    }
  }
  return;
}

/* PlayerAftImgDraw @ 0x08096e80, 72 bytes
 *
 * Draws a player's afterimage trail.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: AftImgDraw
 * Called by: GameLoop
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
void PlayerAftImgDraw(int arg1)

{
  if (*(int **)(arg1 + 0x1394) != (int *)0x0) {
    AftImgDraw(*(int **)(arg1 + 0x1394),-g[0x7315] - g[0x7311],-g[0x7316] - g[0x7312],
               *(int *)(arg1 + 0x1cc));
  }
  return;
}

/* ProjArrayAftImgUpdate @ 0x08096ed0, 46 bytes
 *
 * Records the current frame of every projectile with an afterimage.
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: ArrayScanFirst, ProjAftImgUpdate, ArrayScanNext
 * Called by: GameUpdate
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
void ProjArrayAftImgUpdate(int *arg1)

{
  int array;
  int item;
  
  array = *arg1;
  item = ArrayScanFirst(array);
  while (item != 0) {
    ProjAftImgUpdate(item);
    item = ArrayScanNext(array);
  }
  return;
}

/* ProjAftImgUpdate @ 0x08096f00, 156 bytes
 *
 * Records one projectile's current frame into its afterimage trail.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: AftImgUpdate
 * Called by: ProjArrayAftImgUpdate
 *
 * Elecbyte file: src/mugen/gameloop.c
 * Note: untyped (undefined4) <-> float moves kept as bit copies: 0 assignments,
 *       1 calls, 0 returns
 */
void ProjAftImgUpdate(int arg1)

{
  int *pi1;
  int i2;
  
  pi1 = *(int **)(arg1 + 0x2d8);
  if ((*(int *)(arg1 + 0x2c0) == 0) && (pi1 != (int *)0x0)) {
    i2 = AftImgUpdate(pi1,(float)(g[0x7311] + *(int *)(arg1 + 0x5c)),(float)(g[0x7312] + *(int *)(arg1 + 0x60)),*(float *)(arg1 + 0x54) * *(float *)(arg1 + 0x50),BITS_F2I(uint32_t, *(float *)(arg1 + 0x58) * *(float *)(arg1 + 0x50)),0.0,(uint32_t)(*(int *)(arg1 + 0x34) != 1),(uint32_t)(*(int *)(arg1 + 0x28) == 0));
    if (i2 == 0) {
      pi1[2] = 0;
      *(uint32_t *)(arg1 + 0x2d8) = 0;
    }
  }
  return;
}

/* ProjArrayAftImgDraw @ 0x08096fa0, 46 bytes
 *
 * Draws the afterimage trails of every projectile.
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: ArrayScanFirst, ProjAftImgDraw, ArrayScanNext
 * Called by: GameLoop
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
void ProjArrayAftImgDraw(int *arg1)

{
  int array;
  int item;
  
  array = *arg1;
  item = ArrayScanFirst(array);
  while (item != 0) {
    ProjAftImgDraw(item);
    item = ArrayScanNext(array);
  }
  return;
}

/* ProjAftImgDraw @ 0x08096fd0, 72 bytes
 *
 * Draws one projectile's afterimage trail.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: AftImgDraw
 * Called by: ProjArrayAftImgDraw
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
void ProjAftImgDraw(int arg1)

{
  if (*(int **)(arg1 + 0x2d8) != (int *)0x0) {
    AftImgDraw(*(int **)(arg1 + 0x2d8),-g[0x7315] - g[0x7311],-g[0x7316] - g[0x7312],
               *(int *)(arg1 + 700));
  }
  return;
}

/* GameClsnDraw @ 0x08097020, 486 bytes
 *
 * Draws a box array at a screen position for the collision display (Clsn1
 * subtracted, Clsn2 added, filled boxes for some).
 *
 * Parameters:
 *   arg1         int
 *   arg2         float
 *   arg3         float
 *   arg4         float
 *   arg5         float
 *   arg6         uint32_t
 *   arg7         uint32_t
 *   arg8         int
 *
 * Calls: W_BoxTransSub16, W_BoxTransAdd16, W_BoxFillTransAdd16
 * Called by: PlayerDrawClsn, ProjClsnDraw
 *
 * Elecbyte file: src/mugen/gameloop.c
 * Note: 5 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void GameClsnDraw(int arg1,float arg2,float arg3,float arg4,float arg5,uint32_t arg6,
                 uint32_t arg7,int arg8)

{
  uint32_t u1;
  uint32_t u2;
  uint32_t u3;
  uint32_t u4;
  float80 f5;
  int *pi6;
  int i7;
  int stk_24;
  int stk_1c;
  
  if (((arg1 != 0) && (arg4 != 0.0)) && (arg5 != 0.0)) {
    stk_1c = 0;
    i7 = *(int *)(arg1 + 4);
    if (0 < i7) {
      stk_24 = 0;
      do {
        pi6 = (int *)(stk_24 + *(int *)(arg1 + 8));
        if (*pi6 == 0) {
          f5 = (float80)(int)((uint32_t)((arg7 & 1) == 0) * 2 + -1);
          u1 = (uint32_t)X87_FIST32((float80)pi6[1] * arg4 * f5 + arg2);
          u2 = (uint32_t)X87_FIST32((float80)pi6[2] * arg5 + arg3);
          u3 = (uint32_t)X87_FIST32((float80)pi6[3] * arg4 * f5 + arg2);
          u4 = (uint32_t)X87_FIST32((float80)pi6[4] * arg5 + arg3);
          W_BoxTransSub16(u1,u2,u3,u4,
                          4 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 8 << ((uint8_t)_rgb_g_shift_16 & 0x1f)
                          | 4 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
          if (arg8 == 0) {
            W_BoxTransAdd16(u1,u2,u3,u4,arg6);
            i7 = *(int *)(arg1 + 4);
          }
          else {
            W_BoxFillTransAdd16(u1,u2,u3,u4,arg6);
            i7 = *(int *)(arg1 + 4);
          }
        }
        stk_1c = stk_1c + 1;
        stk_24 = stk_24 + 0x14;
      } while (stk_1c < i7);
    }
  }
  return;
}

/* TeamLifeBack @ 0x08097210, 194 bytes
 *
 * Gives the next turns-mode member back part of its life between rounds.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: GameRoundUpdate
 *
 * Elecbyte file: src/mugen/gameloop.c
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
int TeamLifeBack(int arg1)

{
  float80 f1;
  
  f1 = (100.0 - (float)g[0x7516] / (float)g[0x4e61]) * ((float)0.01f);
  if (f1 < 0.0) {
    f1 = 0.0;
  }
  return (int)X87_FIST32((float)g[arg1 * 0x6a7 + 0x3a57] +
                    ((1.0 - BITS_I2F(g[arg1 * 0x6a7 + 0x3a59])) +
                    BITS_I2F(g[(1 - arg1) * 0x6a7 + 0x3a5e]) * BITS_I2F(g[arg1 * 0x6a7 + 0x3a59])) *
                    BITS_I2F(g[arg1 * 0x6a7 + 0x3a58]) * f1);
}

/* WinIconCheckTeam @ 0x080972e0, 122 bytes
 *
 * Records the win icon for a team when the last member is KOed.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         uint32_t
 *
 * Calls: WinIconCheck
 * Called by: Player1HitP2, PlayerCheckProjHit, PlayerLifeSet
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
void WinIconCheckTeam(int arg1,int arg2,uint32_t arg3)

{
  if ((arg1 != arg2) && (arg1 != 0)) {
    WinIconCheck(arg2,arg3,-1);
    return;
  }
  if (arg1 == arg2) {
    WinIconCheck((arg1 == 1) + 1,0,7);
    return;
  }
  WinIconCheck((arg1 == 1) + 1,0,0);
  return;
}

/* WinIconCheck @ 0x08097360, 188 bytes
 *
 * Records the win type of the round for a side's win icon; a team with full
 * life adds the "perfect" mark (TeamHasFullLife).
 *
 * Parameters:
 *   side         int
 *   arg2         uint32_t
 *   icon         int
 *
 * Globals read: round_no
 * Calls: TeamHasFullLife
 * Called by: GameRoundUpdate, Player1HitP2, PlayerCheckProjHit,
 *            PlayerLifeSet, WinIconCheckTeam
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
void WinIconCheck(int side,uint32_t arg2,int icon)

{
  int *pi1;
  int *pi2;
  int i3;
  
  pi2 = g;
  i3 = g[side + G_ROUND_NO];
  if ((i3 < 10) && (g[0x7511] != 3)) {
    pi1 = g + side * 10 + i3 + 0x7523;
    if (icon == -1) {
      g[side * 10 + i3 + 0x750f] = 0;
      if ((arg2 & 0x1c0) != 0) {
        pi2[side * 10 + i3 + 0x750f] = 5;
      }
      if ((arg2 & 0x490) == 0) {
        if ((arg2 & 0x920) != 0) {
          pi2[side * 10 + i3 + 0x750f] = 2;
        }
      }
      else {
        pi2[side * 10 + i3 + 0x750f] = 1;
      }
    }
    else {
      g[side * 10 + i3 + 0x750f] = icon;
    }
    i3 = TeamHasFullLife(side);
    *pi1 = (uint32_t)(i3 != 0) * 9 + -1;
  }
  return;
}

/* TeamHasFullLife @ 0x08097420, 139 bytes
 *
 * Returns true if every member of a team has full life (perfect).
 *
 * Parameters:
 *   arg1         int
 *
 * Globals read: slot_first, slot_last
 * Called by: SCtrlTrigEval, WinIconCheck
 *
 * Elecbyte file: src/mugen/gameloop.c
 */
uint32_t TeamHasFullLife(int arg1)

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
      if (((i1 == 0) || (*(int *)(i1 + 0x158) == 0)) ||
         (b2 = true, *(int *)(i1 + 0x1c) != 0)) {
        b2 = false;
      }
      if (((b2) && (i1 = *pi5, *(int *)(i1 + 0xc) == arg1)) &&
         (*(int *)(i1 + 0x160) != *(int *)(i1 + 0x164))) {
        return 0;
      }
      i3 = i3 + 1;
      pi5 = pi5 + 1;
      i4 = i4 + 4;
    } while (i3 <= g[G_SLOT_LAST]);
  }
  return 1;
}

/* ShowDebugInfo @ 0x080974b0, 1160 bytes
 *
 * The debug display (Ctrl+D): frame count and FPS ("Frames: %i (%.1f FPS)"),
 * VRetrace, speed, frame skip, each player's state, animation, control,
 * types and the debug clipboard text, plus the debug GUI windows.
 *
 * Parameters:
 *   arg1         int
 *
 * Player fields read: active, anim, stateno, ctrl, statetype, movetype,
 *                     statetime
 * Globals read: players, frame_count, vretrace, speed_flag, frameskip
 * Calls: TimerGetFPS, V_FontDraw, AnimGetLooptime, AnimCurIDno,
 *        EB_GUIUpdate, FontDrawClipboard
 * C library: sprintf, strcat
 * Called by: GameLoop
 * Messages:
 *   "Frames: %i (%.1f FPS)"
 *   "VRet: %i, Speed: %i, Skip: %c"
 *   "%s %i"
 *   "%s %i (%i)"
 *   " (in %s %i\'s state rc)"
 *   "ActionID: %i; Spr: %i,%i; Elemno: %i/%i; Time: %i/%i"
 *
 * Elecbyte file: src/mugen/gameloop.c
 * Note: 2 exact-text site patches (see SITE_PATCHES in
 *       tools/build_source_tree.py)
 * Note: Locals live in `frame`, laid out as on the original stack (0x160 bytes,
 *       2 variables), because their address is taken.
 */
void ShowDebugInfo(int arg1)

{
  int player;
  int i2;
  uint32_t *pu3;
  bool b4;
  int i5;
  uint32_t looptime;
  int i7;
  uint32_t u8;
  uint32_t u9;
  uint32_t u10;
  uint32_t stale_EDX;
  uint32_t u11;
  uint32_t u12;
  float80 l13;
  int *font;
  uint64_t u15;
  unsigned char frame[0x160] __attribute__((aligned(16)));
#define stk_15c (*(char (*)[64])(frame + 0x4))
#define text2 (*(char (*)[268])(frame + 0x44))
  
  i5 = V_Height;
  player = g[arg1 + G_PLAYERS];
  u12 = 0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
           0x1f << ((uint8_t)_rgb_b_shift_16 & 0x1f);
  if (arg1 != 0) {
    l13 = TimerGetFPS();
    if (l13 < (float80)0) {
      l13 = (float80)0;
    }
    sprintf(text2,"Frames: %i (%.1f FPS)",g[G_FRAME_COUNT],(double)l13);
    V_FontDraw(text2,(int *)g[0x413a],10,i5 + -0x27,u12);
    sprintf(text2,"VRet: %i, Speed: %i, Skip: %c",g[G_VRETRACE],g[G_SPEED_FLAG],(g[G_FRAMESKIP] == -1) ? 0x61 : g[G_FRAMESKIP] + 0x30);
    V_FontDraw(text2,(int *)g[0x413a],0x6e,i5 + -0x27,u12);
    if ((player == 0) || (b4 = true, *(int *)(player + PLB_ACTIVE) == 0)) {
      b4 = false;
    }
    if (b4) {
      if (*(int *)(player + 4) == arg1 + -1) {
        sprintf(text2,"%s %i",player + 0x20,arg1 + -1);
      }
      else {
        sprintf(text2,"%s %i (%i)",player + 0x20,*(uint32_t *)(player + 4),arg1 + -1);
      }
      if ((*(int *)(player + 0xbec) != 0) && (i2 = *(int *)(player + 0xbf0), i2 != -1)) {
        sprintf(stk_15c," (in %s %i\'s state rc)",g[i2 + G_PLAYERS] + 0x20,
                *(uint32_t *)(g[i2 + G_PLAYERS] + 4));
        strcat(text2,stk_15c);
      }
      V_FontDraw(text2,(int *)g[0x413a],10,i5 + -0x1f,
                 0x19 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x32 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                 0x1b << ((uint8_t)_rgb_b_shift_16 & 0x1f));
      looptime = AnimGetLooptime(*(uint32_t **)(player + PLB_ANIM));
      pu3 = *(uint32_t **)(player + PLB_ANIM);
      u15 = CONCAT44(looptime,pu3[7]);
      u9 = 0xffffffff;
      looptime = *(uint32_t *)
               (*(int *)(*(int *)*pu3 + 4) * pu3[3] + *(int *)(*(int *)*pu3 + 0x14) + 4);
      i7 = *(int *)(*(int *)(player + PLB_ANIM) + 0x14) + 1;
      i2 = *(int *)(*(int *)(player + PLB_ANIM) + 0x10);
      if (i2 != 0) {
        u9 = *(uint32_t *)(i2 + 0xc);
      }
      i2 = *(int *)(*(int *)(player + PLB_ANIM) + 0x10);
      u10 = 0xffffffff;
      if (i2 != 0) {
        u10 = *(uint32_t *)(i2 + 8);
      }
      u8 = AnimCurIDno(*(uint32_t **)(player + PLB_ANIM));
      sprintf(text2,"ActionID: %i; Spr: %i,%i; Elemno: %i/%i; Time: %i/%i",u8,u10,u9,
              i7,looptime,u15);
      if (*(int *)(player + 0x3458) != 0) {
        strcat(text2," (invalid)");
      }
      if (*(int *)(player + 0x13c0) == 0) {
        font = (int *)g[0x413a];
        u11 = u12;
      }
      else {
        u11 = 0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                 0xf << ((uint8_t)_rgb_b_shift_16 & 0x1f);
        font = (int *)g[0x413a];
      }
      V_FontDraw(text2,font,10,i5 + -0x18,u11);
      sprintf(text2,"State no: %i; Ctrl: %i; Type: %i; Movetype %i; Time: %i",
              *(uint32_t *)(player + PLB_STATENO),*(uint32_t *)(player + PLB_CTRL),
              *(uint32_t *)(player + PLB_STATETYPE),*(uint32_t *)(player + PLB_MOVETYPE),
              *(int *)(player + PLB_STATETIME) + -1,stale_EDX);
      if ((*(int *)(player + 0xe3c) == 0) && (199 < *(int *)(player + PLB_STATENO))) {
        strcat(text2," (invalid)");
      }
      if (*(int *)(player + 0xbec) == 0) {
        font = (int *)g[0x413a];
        u11 = u12;
      }
      else {
        u11 = 0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                 0xf << ((uint8_t)_rgb_b_shift_16 & 0x1f);
        font = (int *)g[0x413a];
      }
      V_FontDraw(text2,font,10,i5 + -0x11,u11);
      EB_GUIUpdate();
      FontDrawClipboard(*(int **)(player + 0x345c),(int *)g[0x413a],10,V_Height + -10,u12);
    }
    else {
      sprintf(text2,"Player %i Disabled",arg1 + -1,text2);
      V_FontDraw(text2,(int *)g[0x413a],10,i5 + -0x1f,
                 0x19 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x32 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                 0x1b << ((uint8_t)_rgb_b_shift_16 & 0x1f));
    }
  }
  return;
}
#undef stk_15c
#undef text2

/* ContinueScreenLoop @ 0x08097940, 1934 bytes
 *
 * The continue screen: the loser in its continue pose, the countdown, and
 * yes/no selection; resets the round if the player continues.
 *
 * Player fields read: anim
 * Player fields written: pos_x, facing
 * Globals read: backbuffer, shadow_intensity, reflection_intensity,
 *               speed_flag, vretrace
 * Calls: V_SetBuf, TimerSetSyncFPS, KBBufferClear, PadPoll, PadBufClear,
 *        UInpRefreshFlags, UInpBufClear, GameRoundReset, BGArrayUpdate,
 *        FrameSkipReset, PlayerReset, PlayerChangeState, KBPoll, KBkbhit,
 *        KBgetchraw, PadHit, PadGet, GlobalInputUpdate, UInpHit, UInpGet,
 *        KBIMenuGetKey, PRSprArrayClear, MasterPalMul, BGMPoll, ...
 * Called by: ContinueScreen
 *
 * Elecbyte file: src/mugen/gameloop.c
 * Note: decompiler flag: stack slots read outside the declared parameters
 *       (entry_stack variables)
 * Note: 3 accesses to parts of a variable are written as sized accesses.
 * Note: 3 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: PalGrpMakeFlag result written into the argument area: given explicit
 *       temporaries pgf_ffffff74
 * Note: Locals live in `frame`, laid out as on the original stack (0x40 bytes, 8
 *       variables), because their address is taken.
 */
uint8_t ContinueScreenLoop(void)

{
  PalGrpFlag pgf_ffffff74;
  uint8_t b1;
  PalGrpFlag f;
  bool b2;
  bool b3;
  bool b4;
  bool b5;
  int *player;
  uint32_t stale_var;
  uint32_t stale_var_00;
  uint32_t stale_var_01;
  uint8_t b6;
  uint8_t b7;
  int i8;
  int i9;
  uint32_t u10;
  uint32_t u11;
  uint8_t entry_stack_ffffff74 [12];
  uint32_t entry_stack_ffffff80;
  uint8_t *entry_stack_ffffff84;
  int i12;
  int *player2;
  unsigned char frame[0x40] __attribute__((aligned(16)));
#define stk_40 (*(int *)(frame + 0x0))
#define stk_38 (*(int *)(frame + 0x8))
#define stk_2c (*(uint32_t *)(frame + 0x14))
#define stk_28 (*(int *)(frame + 0x18))
#define stk_24 (*(int *)(frame + 0x1c))
#define stk_20 (*(uint32_t *)(frame + 0x20))
#define stk_1c (*(int **)(frame + 0x24))
#define stk_18 (*(int **)(frame + 0x28))
  
  stk_1c = g + 0x733b;
  stk_18 = g + 0x7348;
  b2 = false;
  b3 = true;
  stk_38 = 0;
  b4 = false;
  stk_40 = 0;
  V_SetBuf((int *)g[G_BACKBUFFER],0);
  TimerSetSyncFPS(0x3c);
  KBBufferClear();
  PadPoll();
  PadBufClear();
  UInpRefreshFlags();
  UInpBufClear();
  GameRoundReset();
  BGArrayUpdate(g[0x6ed4]);
  FrameSkipReset();
  if (g[0x33b3] == 2) {
    player2 = (int *)g[0x73db];
    player = (int *)g[0x73dd];
  }
  else {
    player2 = (int *)g[0x73da];
    player = (int *)g[0x73dc];
  }
  PlayerReset(player2);
  PlayerChangeState((int)player2,0x157c);
  player2[PL_POS_X] = BITS_F2I(int, (float)(V_Width / 2 + g[0x7311]));
  if (player != (int *)0x0) {
    PlayerReset(player);
    PlayerChangeState((int)player,0x157c);
    i9 = g[0x7311];
    i8 = V_Width / 2;
    i12 = player2[PL_FACING];
    player[PL_FACING] = -i12;
    player[PL_POS_X] = BITS_F2I(int, (float)(i8 + i9 + i12 * 0x28));
    player2[PL_POS_X] = BITS_F2I(int, (BITS_I2F(player2[PL_POS_X]) - (float)(player2[PL_FACING] * 0x28)));
  }
  do {
    stk_24 = 0;
    stk_20 = 0;
    i9 = 0;
    PadPoll();
    KBPoll();
    b5 = KBkbhit();
    if (ZEXT8(b5) != 0) {
      stk_24 = KBgetchraw();
    }
    b5 = PadHit();
    if (ZEXT8(b5) != 0) {
      stk_20 = PadGet();
    }
    GlobalInputUpdate();
    b5 = UInpHit();
    if (ZEXT8(b5) != 0) {
      i9 = UInpGet();
    }
    KBIMenuGetKey(&stk_2c,i9,(int)&stk_1c,2);
    i9 = stk_28;
    u10 = stk_2c;
    PRSprArrayClear((int *)g[0x413d]);
    if ((i9 + 1 == g[0x33b3]) || (g[0x33af] == g[0x33b0])) {
      if ((u10 & 8) != 0) {
        b3 = true;
      }
      b3 = (bool)(b3 & (u10 & 2) == 0);
      if ((u10 & 0xff0) != 0) {
        b2 = true;
      }
    }
    if (stk_24 == 1) {
      b3 = false;
      b2 = true;
    }
    if (b2) {
      if (stk_40 < 8) {
        i9 = stk_40 * -0x20 + 0x100;
        MasterPalMul(i9,i9,i9);
      }
      if (stk_40 == 8) {
        MasterPalMul(0,0,0);
      }
      stk_40 = stk_40 + 1;
      if (stk_40 == 8) {
        b4 = true;
      }
    }
    BGMPoll(g + 0x6efa);
    if (g[0x7309] == 0) {
      PalGrpResetPalette();
    }
    PlayerUpdate(player2);
    if (player != (int *)0x0) {
      PlayerUpdate(player);
    }
    AnimUpdate((uint32_t *)player2[PL_ANIM]);
    if (player != (int *)0x0) {
      AnimUpdate((uint32_t *)player[PL_ANIM]);
    }
    AnimPerArrayUpdate((int *)g[0x413c]);
    if (0 < stk_38) {
      i8 = 0x80;
      i12 = 0x80;
      i9 = 0x80;
      PalGrpMakeFlag(&pgf_ffffff74,0xffffffff,0);
      f.w[3] = pgf_ffffff74.w[3];
      f.w[0] = pgf_ffffff74.w[0];
      f.w[1] = pgf_ffffff74.w[1];
      f.w[2] = pgf_ffffff74.w[2];
      f.w[4] = (uint32_t)pgf_ffffff74.w[4];
      PalGrpSetMul(f,i9,i12,i8);
    }
    if (stk_38 < 8) {
      i9 = stk_38 << 5;
      MasterPalMul(i9,i9,i9);
    }
    if (stk_38 == 8) {
      MasterPalMul(0x100,0x100,0x100);
    }
    if (g[0x7307] == 0) {
      MasterPalProcessChanges();
      GameBGDraw();
      PlayerDrawShadow((int)player2,g + G_SHADOW_INTENSITY,g + G_REFLECTION_INTENSITY);
      if (player != (int *)0x0) {
        PlayerDrawShadow((int)player,g + G_SHADOW_INTENSITY,g + G_REFLECTION_INTENSITY);
      }
      AnimPerArrayDrawGrp((int *)g[0x413c],2,-g[0x7311],-g[0x7312]);
      PlayerDrawAnim((int)player2,1.0);
      if (player != (int *)0x0) {
        PlayerDrawAnim((int)player,1.0);
      }
      PRSprArrayDraw((int *)g[0x413d]);
      GameFGDraw();
      AnimPerArrayDrawGrp((int *)g[0x413c],1,-g[0x7311],-g[0x7312]);
      b7 = (uint8_t)_rgb_b_shift_16;
      b1 = (uint8_t)_rgb_r_shift_16;
      b6 = (uint8_t)_rgb_g_shift_16;
      if (b3) {
        u11 = 0x1f << (b1 & 0x1f) | 0x3f << (b6 & 0x1f) | 0x1f << (b7 & 0x1f);
        u10 = 0x10 << (b1 & 0x1f) | 0x20 << (b6 & 0x1f);
        i9 = 0x10;
      }
      else {
        u11 = 0x10 << (b1 & 0x1f) | 0x20 << (b6 & 0x1f) | 0x10 << (b7 & 0x1f);
        u10 = 0x1f << (b1 & 0x1f) | 0x3f << (b6 & 0x1f);
        i9 = 0x1f;
      }
      V_FontDrawCenter("Continue?",(int *)g[0x413b],0xa0,0x29,0);
      V_FontDrawCenter("Continue?",(int *)g[0x413b],0x9f,0x28,
                       0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                       0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                       0x1f << ((uint8_t)_rgb_b_shift_16 & 0x1f));
      V_FontDrawRight("Yes",(int *)g[0x413b],0x96,0x3d,0);
      V_FontDrawRight("Yes",(int *)g[0x413b],0x95,0x3c,u11);
      V_FontDraw("No",(int *)g[0x413b],0xaa,0x3d,0);
      entry_stack_ffffff84 = &str_no;
      entry_stack_ffffff80 = 0x8098037;
      V_FontDraw("No",(int *)g[0x413b],0xa9,0x3c,u10 | i9 << (b7 & 0x1f));
    }
    if (g[G_SPEED_FLAG] == 0) {
      TimerWaitSync();
    }
    if ((g[0x7307] == 0) && (g[G_VRETRACE] != 0)) {
      VRetrace();
    }
    DrawToScreen();
    if (g[0x7307] == 0) {
      MasterPalFinishedDraw();
    }
    FrameSkipUpdate();
    stk_38 = stk_38 + 1;
  } while (!b4);
  FrameSkipReset();
  GameResetPersistVars();
  if (b3) {
    g[0x4134] = 1;
  }
  return b3;
}
#undef stk_40
#undef stk_38
#undef stk_2c
#undef stk_28
#undef stk_24
#undef stk_20
#undef stk_1c
#undef stk_18

