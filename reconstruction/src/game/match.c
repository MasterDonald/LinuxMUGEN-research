/*
 * match.c -- stages and rounds
 * Stage loading, match and round reset and winners, the next-round logic and
 * match logging.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/match.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* GameLoadStage @ 0x0809dc50, 2522 bytes
 *
 * Loads the selected stage .def. Groups and keys:
 * - "[Camera]": startx, starty, boundleft, boundright, boundhigh, boundlow,
 * tension, floortension, verticalfollow;
 * - "[PlayerInfo]": p1/p2 startx, starty, startz, facing, and leftbound,
 * rightbound, topbound, botbound;
 * - "[Bound]": screenleft, screenright;
 * - "[StageInfo]": zoffset, zoffsetlink, autoturn, resetbg;
 * - "[Shadow]": intensity, color, yscale, fade.range;
 * - "[Reflection]": intensity;
 * - "[Scaling]": topz, botz, topscale, botscale;
 * - "[Music]": bgmusic, bgvolume.
 *
 * It then loads the stage music (BGMLoad) and the background (GameBGLoad)
 * and creates the player records. Errors: "Can't open stage: %s", "Missing
 * camera info: %s", "Missing player info", "Missing bound info", "Missing
 * stage info", "Missing scaling info", "Can't create helper characters".
 *
 * Text keys read: [Camera], "boundleft", "boundright", "startx", "starty",
 *                 "tension", "floortension", "boundhigh", "boundlow",
 *                 "verticalfollow", [PlayerInfo], "p1startx", "p1starty",
 *                 "p1startz", "p1facing", "p2startx", "p2starty",
 *                 "p2startz", "p2facing", "leftbound", "rightbound",
 *                 "topbound", "botbound", [Scaling], ...
 * Globals read: errmsg, stageinfo_zoffsetlink, demo_mode,
 *               demo_mode_fight_playbgm, debug_display
 * Globals written: stageinfo_zoffset
 * Calls: TPReadFile, TPGroupSeek, TPGetValueInt, TPGetValueFloat, TPScanf,
 *        TPGetValue, BGMLoad, TPFree, GameBGLoad, PlayerNew,
 *        PalGrpMakeFlag
 * C library: strcpy, sprintf, strcat
 * Called by: GamePlay, GameReloadStage
 * Messages:
 *   "Can\'t open stage: %s"
 *   "Missing camera info: %s"
 *   "Missing player info: %s"
 *   "Missing scaling info: %s"
 *   "Missing bound info: %s"
 *   "Missing stage info: %s"
 *
 * Elecbyte file: src/mugen/match.c
 * Note: 20 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x130 bytes,
 *       6 variables), because their address is taken.
 */
uint32_t GameLoadStage(void)

{
  bool b1;
  bool b2;
  bool b3;
  bool b4;
  bool b5;
  bool b6;
  bool b7;
  bool b8;
  bool b9;
  bool b10;
  bool b11;
  bool b12;
  uint32_t *pu13;
  uint32_t *tp;
  uint32_t stale_var;
  uint32_t stale_var_00;
  uint32_t stale_var_01;
  uint32_t stale_var_02;
  uint32_t stale_var_03;
  uint32_t stale_var_04;
  uint32_t stale_var_05;
  uint32_t stale_var_06;
  uint32_t stale_var_07;
  uint32_t stale_var_08;
  uint32_t stale_var_09;
  uint32_t stale_var_10;
  uint32_t stale_var_11;
  uint32_t stale_var_12;
  uint32_t stale_var_13;
  uint32_t stale_var_14;
  uint32_t stale_var_15;
  uint32_t stale_var_16;
  uint8_t *value;
  uint32_t stale_var_17;
  int *pi16;
  int *player;
  uint32_t u18;
  int i19;
  uint32_t stale_ECX;
  uint32_t stale_ECX_00;
  uint32_t stale_ECX_01;
  uint32_t stale_ECX_02;
  int i20;
  int i21;
  uint32_t *pu22;
  int i2;
  unsigned char frame[0x130] __attribute__((aligned(16)));
#define stk_128 (*(int *)(frame + 0x8))
#define stk_124 (*(int *)(frame + 0xc))
#define stk_120 (*(int *)(frame + 0x10))
#define stk_11c (*(PalGrpFlag *)(frame + 0x14))
#define stk_fc (*(PalGrpFlag *)(frame + 0x34))
#define filename (*(char (*)[204])(frame + 0x54))
  
  pi16 = g;
  pu13 = (uint32_t *)(g + 0x107f);
  stk_128 = 0;
  stk_124 = 0;
  stk_120 = 0;
  pu22 = pu13;
  for (i19 = 0x435; i19 != 0; i19 = i19 + -1) {
    *pu22 = 0;
    pu22 = pu22 + 1;
  }
  strcpy(filename,(char *)(g + 0x805));
  tp = TPReadFile(filename);
  if (tp == (uint32_t *)0x0) {
    sprintf((char *)(g + G_ERRMSG),"Can\'t open stage: %s",filename);
  }
  else {
    i19 = TPGroupSeek((int)tp,"Camera");
    if (i19 == -1) {
      sprintf((char *)(g + G_ERRMSG),"Missing camera info: %s",filename,0);
    }
    else {
      pi16[0x1088] = 0;
      pi16[0x1087] = 0x32;
      pi16[0x1084] = -0x19;
      pi16[0x1085] = 0;
      pi16[0x1081] = 0;
      pi16[0x1080] = 0;
      pi16[0x1082] = -0x4b;
      pi16[0x1083] = 0x4b;
      pi16[0x1086] = 0x3e4ccccd;
      TPGetValueInt((int)tp,"boundleft",(uint32_t *)(pi16 + 0x1082));
      TPGetValueInt((int)tp,"boundright",(uint32_t *)(pi16 + 0x1083));
      TPGetValueInt((int)tp,"startx",(uint32_t *)(pi16 + 0x1080));
      TPGetValueInt((int)tp,"starty",(uint32_t *)(pi16 + 0x1081));
      TPGetValueInt((int)tp,"tension",(uint32_t *)(pi16 + 0x1087));
      TPGetValueInt((int)tp,"floortension",(uint32_t *)(pi16 + 0x1088));
      TPGetValueInt((int)tp,"boundhigh",(uint32_t *)(pi16 + 0x1084));
      TPGetValueInt((int)tp,"boundlow",(uint32_t *)(pi16 + 0x1085));
      TPGetValueFloat((int)tp,"verticalfollow",(float *)(pi16 + 0x1086));
      i19 = TPGroupSeek((int)tp,"PlayerInfo");
      if (i19 == -1) {
        sprintf((char *)(g + G_ERRMSG),"Missing player info: %s",filename,stale_ECX);
      }
      else {
        b1 = TPGetValueInt((int)tp,"p1startx",(uint32_t *)(pi16 + 0x1089));
        b2 = TPGetValueInt((int)tp,"p1starty",(uint32_t *)(pi16 + 0x108d));
        b3 = TPGetValueInt((int)tp,"p1startz",(uint32_t *)(pi16 + 0x1091));
        b4 = TPGetValueInt((int)tp,"p1facing",(uint32_t *)(pi16 + 0x1095));
        b5 = TPGetValueInt((int)tp,"p2startx",(uint32_t *)(pi16 + 0x108a));
        b6 = TPGetValueInt((int)tp,"p2starty",(uint32_t *)(pi16 + 0x108e));
        b7 = TPGetValueInt((int)tp,"p2startz",(uint32_t *)(pi16 + 0x1092));
        b8 = TPGetValueInt((int)tp,"p2facing",(uint32_t *)(pi16 + 0x1096));
        b9 = TPGetValueInt((int)tp,"leftbound",(uint32_t *)(pi16 + 0x1099));
        b10 = TPGetValueInt((int)tp,"rightbound",(uint32_t *)(pi16 + 0x109a));
        b11 = TPGetValueInt((int)tp,"topbound",(uint32_t *)(pi16 + 0x109b));
        b12 = TPGetValueInt((int)tp,"botbound",(uint32_t *)(pi16 + 0x109c));
        if ((ZEXT8(b1) & ZEXT8(b2) &
             ZEXT8(b3) & ZEXT8(b4) &
             ZEXT8(b5) & ZEXT8(b6) &
             ZEXT8(b7) & ZEXT8(b8) &
             ZEXT8(b9) & ZEXT8(b10) &
             ZEXT8(b11) & ZEXT8(b12)) == 1) {
          pi16[0x108b] = pi16[0x1089] + -0x19;
          pi16[0x108f] = pi16[0x108d];
          pi16[0x1093] = pi16[0x1091];
          pi16[0x1097] = pi16[0x1095];
          pi16[0x108c] = pi16[0x108a] + 0x19;
          pi16[0x1090] = pi16[0x108e];
          pi16[0x1094] = pi16[0x1092];
          pi16[0x1098] = pi16[0x1096];
          i19 = TPGroupSeek((int)tp,"Scaling");
          if (i19 == -1) {
            sprintf((char *)(g + G_ERRMSG),"Missing scaling info: %s",filename,stale_ECX_00);
          }
          else {
            b1 = TPGetValueInt((int)tp,"topz",(uint32_t *)(pi16 + 0x109e));
            b2 = TPGetValueInt((int)tp,"botz",(uint32_t *)(pi16 + 0x109f));
            b3 = TPGetValueFloat((int)tp,"topscale",(float *)(pi16 + 0x10a0));
            b4 = TPGetValueFloat((int)tp,"botscale",(float *)(pi16 + 0x10a1));
            if ((ZEXT8(b1) & ZEXT8(b2) &
                 ZEXT8(b3) & ZEXT8(b4)) == 1) {
              if (pi16[0x109e] == pi16[0x109f]) {
                pi16[0x10a1] = BITS_F2I(int, (BITS_I2F(pi16[0x10a1]) + 1.0));
              }
              i19 = TPGroupSeek((int)tp,"Bound");
              if (i19 == -1) {
                sprintf((char *)(g + G_ERRMSG),"Missing bound info: %s",filename,tp);
              }
              else {
                b1 = TPGetValueInt((int)tp,"screenleft",(uint32_t *)(pi16 + 0x10a3));
                b2 = TPGetValueInt((int)tp,"screenright",(uint32_t *)(pi16 + 0x10a2));
                i19 = (ZEXT8(b1) & ZEXT8(b2)) - 1;
                if (i19 == 0) {
                  i19 = TPGroupSeek((int)tp,"StageInfo");
                  player = g;
                  if (i19 == -1) {
                    sprintf((char *)(g + G_ERRMSG),"Missing stage info: %s",filename,0);
                  }
                  else {
                    g[G_STAGEINFO_ZOFFSET] = 0xbe;
                    player[0x4142] = -1;
                    TPGetValueInt((int)tp,"zoffset",(uint32_t *)(player + 0x4140));
                    TPGetValueInt((int)tp,"zoffsetlink",(uint32_t *)(g + G_STAGEINFO_ZOFFSETLINK));
                    g[0x4141] = g[G_STAGEINFO_ZOFFSET];
                    pi16[0x109d] = 0;
                    TPGetValueInt((int)tp,"autoturn",(uint32_t *)(pi16 + 0x109d));
                    *pu13 = 1;
                    TPGetValueInt((int)tp,"resetbg",pu13);
                    pi16[0x10a6] = 0x3ecccccd;
                    pi16[0x10a4] = 0x80;
                    i19 = TPGroupSeek((int)tp,"Shadow");
                    if (i19 != -1) {
                      TPScanf((int)tp,"color","%i,%i,%i",&stk_128,&stk_124,&stk_120,
                              stale_ECX_02,stale_ECX_02);
                      TPGetValueInt((int)tp,"intensity",(uint32_t *)(pi16 + 0x10a4));
                      TPGetValueFloat((int)tp,"yscale",(float *)(pi16 + 0x10a6));
                      TPScanf((int)tp,"fade.range","%i,%i",pi16 + 0x10a7,pi16 + 0x10a8);
                    }
                    pi16[0x10a5] =
                         (stk_128 >> 3) << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                         (stk_124 >> 2) << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                         (stk_120 >> 3) << ((uint8_t)_rgb_b_shift_16 & 0x1f);
                    i19 = TPGroupSeek((int)tp,"Reflection");
                    if (i19 != -1) {
                      TPGetValueInt((int)tp,"intensity",(uint32_t *)(pi16 + 0x10a9));
                    }
                    i19 = TPGroupSeek((int)tp,"Music");
                    if ((i19 != -1) && (g[0x6ef3] != 0)) {
                      value = (uint8_t *)TPGetValue((int)tp,"bgmusic");
                      if (*(char *)((int)g + 0x3013) == '\0') {
                        if (value != (uint8_t *)0x0) {
                          TPGetValueInt((int)tp,"bgvolume",(uint32_t *)(pi16 + 0x10b0));
                        }
                      }
                      else {
                        value = (uint8_t *)((int)g + 0x3013);
                      }
                      if ((value != (uint8_t *)0x0) &&
                         (((g[G_DEMO_MODE] == 0 || (g[G_DEMO_MODE_FIGHT_PLAYBGM] != 0)) &&
                          (i19 = BGMLoad(pi16 + 0x10aa,value,1), i19 == 0)))) {
                        return 0;
                      }
                    }
                    TPFree(tp);
                    g[0x81c4] = Ticks;
                    b1 = GameBGLoad();
                    pi16 = g;
                    if (ZEXT8(b1) != 0) {
                      player = g + 0x7397;
                      g[0x81c4] = Ticks - g[0x81c4];
                      pi16[0x7395] = pi16[0x7396] + *player;
                      i19 = 1;
                      pi16[0x749d] = 0;
                      pi16 = pi16 + 0x33b8;
                      do {
                        *pi16 = 0;
                        pi16 = pi16 + 0x6a7;
                        i19 = i19 + -1;
                      } while (-1 < i19);
                      i2 = 0;
                      i19 = 5;
                      if (0 < g[0x7396]) {
                        i21 = 0x1cf74;
                        do {
                          player = PlayerNew(0);
                          pi16 = g;
                          *(int **)(i21 + 4 + (int)g) = player;
                          if (player == (int *)0x0) {
                            strcat((char *)(pi16 + 0x81d2),"\nCan\'t create helper characters");
                            return 0;
                          }
                          player[2] = i19;
                          if (i19 + -1 < 0x20) {
                            PalGrpMakeFlag(&stk_fc,1 << ((uint8_t)(i19 + -1) & 0x1f),1);
                            i20 = *(int *)((int)g + i21 + 4);
                            *(uint32_t *)(i20 + 0x25c8) = stk_fc.w[0];
                            *(uint32_t *)(i20 + 0x25cc) = stk_fc.w[1];
                            *(uint32_t *)(i20 + 0x25d0) = stk_fc.w[2];
                            *(uint32_t *)(i20 + 0x25d4) = stk_fc.w[3];
                            u18 = stk_fc.w[4];
                          }
                          else {
                            PalGrpMakeFlag(&stk_11c,1 << ((char)i19 - 0x21U & 0x1f),2);
                            i20 = *(int *)((int)g + i21 + 4);
                            *(uint32_t *)(i20 + 0x25c8) = stk_11c.w[0];
                            *(uint32_t *)(i20 + 0x25cc) = stk_11c.w[1];
                            *(uint32_t *)(i20 + 0x25d0) = stk_11c.w[2];
                            *(uint32_t *)(i20 + 0x25d4) = stk_11c.w[3];
                            u18 = stk_11c.w[4];
                          }
                          *(uint32_t *)(i20 + 0x25d8) = u18;
                          i2 = i2 + 1;
                          i21 = i21 + 4;
                          i19 = i19 + 1;
                        } while (i2 < g[0x7396]);
                      }
                      if (g[G_DEBUG_DISPLAY] == 0) {
                        g[0x81cb] = 0;
                      }
                      else {
                        g[0x81cb] = 1;
                      }
                      return 1;
                    }
                  }
                }
                else {
                  sprintf((char *)(g + G_ERRMSG),"Can\'t read bound info: %s",filename,i19);
                }
              }
            }
            else {
              sprintf((char *)(g + G_ERRMSG),"Can\'t read scaling info: %s",filename,stale_ECX_01);
            }
          }
        }
        else {
          sprintf((char *)(g + G_ERRMSG),"Can\'t read player info: %s",filename,
                  ZEXT8(b8));
        }
      }
    }
  }
  return 0;
}
#undef stk_128
#undef stk_124
#undef stk_120
#undef stk_11c
#undef stk_fc
#undef filename

/* GameBGLoad @ 0x0809e630, 254 bytes
 *
 * Loads the stage background: the "[BGdef]" group ("spr") and its elements
 * (BGArrayReadTP) from the stage .def. Errors: "Error opening %s", "BG error
 * reading %s".
 *
 * Text keys read: [BGdef], "spr"
 * Globals read: errmsg
 * Calls: TPReadFile, TPGroupSeek, TPGetValue, strmatchlen, splitdirfile,
 *        BGArrayReadTP, TPFree
 * C library: sprintf
 * Called by: GameLoadStage
 * Messages:
 *   "\nError opening %s"
 *   "\nBG error reading %s"
 *
 * Elecbyte file: src/mugen/match.c
 * Note: 1 data addresses refer to the data image (data/mugen_data.S).
 * Note: Locals live in `frame`, laid out as on the original stack (0x1010 bytes,
 *       1 variables), because their address is taken.
 */
bool GameBGLoad(void)

{
  int *pi1;
  char *tp;
  int i3;
  char *value;
  uint32_t stale_ECX;
  unsigned char frame[0x1010] __attribute__((aligned(16)));
#define dirname (*(char (*)[4104])(frame + 0x4))
  
  tp = TPReadFile((char *)(g + 0x805));
  if (tp == (char *)0x0) {
    sprintf((char *)(g + G_ERRMSG),"\nError opening %s",g + 0x805,stale_ECX);
  }
  dirname[0] = '\0';
  i3 = TPGroupSeek((int)tp,"BGdef");
  if (i3 != -1) {
    value = TPGetValue((int)tp,"spr");
    if (value != (char *)0x0) {
      i3 = strmatchlen((int)value,(int)&str_stages_953b,7);
      if (i3 == 0) {
        splitdirfile((char *)(g + 0x805),dirname,(char *)0x0);
      }
    }
  }
  value = BGArrayReadTP(tp,dirname,"BG",0,0);
  pi1 = g;
  g[0x6ed4] = (int)value;
  if (value != (char *)0x0) {
    TPFree((uint32_t *)tp);
  }
  else {
    sprintf((char *)(pi1 + 0x81d2),"\nBG error reading %s",pi1 + 0x805,0);
  }
  return value != (char *)0x0;
}
#undef dirname

/* GameUnloadStage @ 0x0809e730, 407 bytes
 *
 * Unloads the stage: frees the music, saves persistent player variables,
 * frees the players (keeping cached characters by priority) and the
 * background.
 *
 * Calls: BGMFree, PlayerEnableSet, PlayerSavePersistVars, PlayerFree,
 *        PlayerCacheFreePriority, BGArrayFree
 * Called by: GamePlay, GameReloadStage
 *
 * Elecbyte file: src/mugen/match.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 */
void GameUnloadStage(void)

{
  int *pi1;
  int *pi2;
  int i3;
  int saved_EBP;
  int i4;
  int stk_18;
  int player;
  
  BGMFree(g + 0x10aa);
  player = 1;
  pi2 = g;
  if (0 < g[0x7395]) {
    i4 = 0x1cf64;
    stk_18 = 4;
    do {
      i3 = *(int *)(i4 + 4 + (int)pi2);
      if (i3 != 0) {
        if (*(int *)(i3 + 0x158) != 0) {
          PlayerEnableSet(player,0);
          pi2 = g;
        }
        i3 = *(int *)((int)pi2 + i4 + 4);
        if (*(int *)(i3 + 0x10) != -1) {
          PlayerSavePersistVars
                    (*(int *)((int)pi2 + i4 + 4),
                     pi2 + *(int *)(i3 + 0x10) * 0x6a7 +
                              *(int *)(i3 + 0x14) * 400 + *(int *)(i3 + 0x18) * 100 + 0x3417);
          pi2 = g;
        }
        pi1 = *(int **)(i4 + 4 + (int)pi2);
        i3 = -1;
        if ((*pi1 != 0) && (pi1[0x989] == 0)) {
          i3 = *(int *)(*pi1 + 0x10a8);
          if (pi1[3] == pi2[0x33b3]) {
            saved_EBP = pi2[0x3a61] + pi2[0x33ba];
          }
          else {
            saved_EBP = 0;
          }
        }
        PlayerFree(*(int **)(i4 + 4 + (int)pi2));
        if (i3 != -1) {
          PlayerCacheFreePriority(i3,saved_EBP);
        }
        pi2 = g;
        *(uint32_t *)((int)g + stk_18 + 0x1ce64) = 0;
        *(uint32_t *)((int)pi2 + i4 + 4) = 0;
      }
      player = player + 1;
      stk_18 = stk_18 + 4;
      i4 = i4 + 4;
    } while (player <= pi2[0x7395]);
  }
  BGArrayFree(pi2[0x6ed4]);
  g[0x6ed4] = 0;
  return;
}

/* GameStgInitFightData @ 0x0809e8d0, 557 bytes
 *
 * Loads the per-match fight data that depends on the selected characters:
 * the "[Files]" "sprite" of the fight screen (the face sprites listed for
 * each character, read with SpriteReadSFFList).
 *
 * Text keys read: [Files], "sprite"
 * Globals read: slct_coop_side, charinfo
 * Calls: SysExplodParseGetSprGrpImgNo, joindirfile, TPReadFile,
 *        TPGroupSeek, TPGetValue, TPFree, SpriteSetBufReadMode,
 *        SpriteReadSFFList
 * Called by: GamePlay, GameReloadStage
 *
 * Elecbyte file: src/mugen/match.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x1050 bytes,
 *       8 variables), because their address is taken.
 */
uint32_t GameStgInitFightData(void)

{
  int *pi1;
  int *pi2;
  int i3;
  uint32_t *tp;
  int i5;
  char *value;
  int i2;
  unsigned char frame[0x1050] __attribute__((aligned(16)));
#define stk_1048 (*(int **)(frame + 0x8))
#define stk_1044 (*(int *)(frame + 0xc))
#define stk_1034 (*(int *)(frame + 0x1c))
#define stk_1030 (*(int *)(frame + 0x20))
#define filename (*(char (*)[4096])(frame + 0x24))
#define stk_2c (*(int *)(frame + 0x1024))
#define stk_28 (*(int *)(frame + 0x1028))
#define stk_24 (*(uint32_t *)(frame + 0x102c))
  
  pi1 = g;
  i2 = 0;
  do {
    pi2 = g;
    if (((1 < g[i2 * 0x6a7 + 0x33b9]) && (g[G_SLCT_COOP_SIDE] != 2 - i2)) &&
       (i3 = SysExplodParseGetSprGrpImgNo(pi1 + i2 * 0x56 + 0x4af8,&stk_1034,&stk_1030)
       , i3 != 0)) {
      stk_2c = stk_1034;
      stk_28 = stk_1030;
      stk_24 = 0xffffffff;
      stk_1044 = 0;
      if (0 < pi2[i2 * 0x6a7 + 0x33b9]) {
        stk_1048 = pi2 + i2 * 0x6a7 + 0x33bf;
        do {
          i3 = *stk_1048 * 0x702c;
          joindirfile(filename,(char *)(i3 + g[G_CHARINFO] + 0x200a),
                      (char *)(i3 + g[G_CHARINFO] + 0x100b));
          tp = TPReadFile(filename);
          if (tp != (uint32_t *)0x0) {
            filename[0] = '\0';
            i5 = TPGroupSeek((int)tp,"Files");
            if ((i5 != -1) && (value = TPGetValue((int)tp,"sprite"), value != (char *)0x0))
            {
              joindirfile(filename,(char *)(i3 + g[G_CHARINFO] + 0x200a),value);
            }
            TPFree(tp);
            if (filename[0] != '\0') {
              SpriteSetBufReadMode(0);
              i3 = SpriteReadSFFList(filename,&stk_2c);
              pi1[i2 * 4 + stk_1044 + 0x52b5] = i3;
              SpriteSetBufReadMode(g[0x757b]);
            }
          }
          stk_1044 = stk_1044 + 1;
          stk_1048 = stk_1048 + 0x17;
        } while (stk_1044 < pi2[i2 * 0x6a7 + 0x33b9]);
      }
    }
    i2 = i2 + 1;
  } while (i2 < 2);
  return 1;
}
#undef stk_1048
#undef stk_1044
#undef stk_1034
#undef stk_1030
#undef filename
#undef stk_2c
#undef stk_28
#undef stk_24

/* GameStgDeInitFightData @ 0x0809eb00, 85 bytes
 *
 * Frees the per-match fight sprites.
 *
 * Calls: SpriteArrayFree
 * Called by: GamePlay, GameReloadStage
 *
 * Elecbyte file: src/mugen/match.c
 */
void GameStgDeInitFightData(void)

{
  int *sprites;
  int *pi2;
  int i3;
  int i2;
  int i5;
  
  pi2 = g;
  i2 = 0;
  do {
    i5 = 3;
    i3 = i2 * 0x10 + 0x45b0;
    do {
      sprites = *(int **)((int)pi2 + i3 + 0x10524);
      if (sprites != (int *)0x0) {
        SpriteArrayFree(sprites);
        *(uint32_t *)((int)pi2 + i3 + 0x10524) = 0;
      }
      i3 = i3 + 4;
      i5 = i5 + -1;
    } while (-1 < i5);
    i2 = i2 + 1;
  } while (i2 < 2);
  return;
}

/* GameNextRound @ 0x0809eb60, 380 bytes
 *
 * Moves to the next round or match. It finds the round winner, shows a
 * loading frame, reorders teams, loads and activates the next team members
 * (turns mode) or builds the next survival opponent, and resets the round.
 *
 * Globals read: players, slct_coop_side
 * Globals written: round_no
 * Calls: GameRoundWinner, W_Cls, FrameSkipReset, DrawToScreen,
 *        TeamReorderAll, GameLoadAndActivateTeam, SurvivalBuildRandomTeam,
 *        GameRoundReset
 * Called by: GameRoundUpdate
 *
 * Elecbyte file: src/mugen/match.c
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
void GameNextRound(void)

{
  int i1;
  int *pi2;
  int i3;
  int i4;
  int i5;
  int i2;
  int stk_1c;
  
  i2 = 0;
  g[G_ROUND_NO] = g[G_ROUND_NO] + 1;
  stk_1c = 0;
  do {
    i3 = GameRoundWinner();
    pi2 = g;
    if (i3 != i2 + 1) {
      if (*(int *)((int)g + stk_1c + 0xcee0) + 1 < *(int *)((int)g + stk_1c + 0xcee4)) {
        W_Cls(0);
        FrameSkipReset();
        DrawToScreen();
        *(int *)((int)pi2 + stk_1c + 0xcee0) = *(int *)((int)pi2 + stk_1c + 0xcee0) + 1;
        TeamReorderAll(i2);
        GameLoadAndActivateTeam(i2);
      }
      pi2 = g;
      i3 = *(int *)((int)g + stk_1c + 0xcee0) * 0x5c + stk_1c + 0xceec;
      i4 = 0;
      if (0 < *(int *)((int)g + i3 + 8)) {
        do {
          i5 = i4 + 1;
          i1 = g[*(int *)((int)pi2 + i4 * 0x14 + i3 + 0xc) + G_PLAYERS];
          i4 = (int)X87_FIST32((float80)*(int *)(i1 + 0x50) *
                             *(float *)((int)pi2 + stk_1c + 0xe96c));
          *(int *)(i1 + 0x164) = i4;
          *(int *)(i1 + 0x16c) = i4;
          *(int *)(i1 + 0x168) = i4;
          *(int *)(i1 + 0x160) = i4;
          i4 = i5;
        } while (i5 < *(int *)((int)pi2 + i3 + 8));
      }
    }
    i2 = i2 + 1;
    stk_1c = stk_1c + 0x1a9c;
  } while (i2 < 2);
  if (g[G_SLCT_COOP_SIDE] != 0) {
    SurvivalBuildRandomTeam(g + (2 - g[G_SLCT_COOP_SIDE]) * 0x6a7 + 0x33b8,2 - g[G_SLCT_COOP_SIDE],0);
  }
  GameRoundReset();
  FrameSkipReset();
  return;
}

/* GameReloadStage @ 0x0809ece0, 262 bytes
 *
 * Reloads the stage between arcade matches (new opponent, new stage): shows
 * "Loading...", clears palette groups, reloads the fight data and stage, and
 * resets the match.
 *
 * Calls: W_Cls, V_FontDrawRight, FrameSkipReset, DrawToScreen,
 *        PalGrpClear, GameStgDeInitFightData, GameUnloadStage,
 *        GameResetPersistVars, PlayerCacheClear, GameLoadStage,
 *        GameStgInitFightData, GameSetVol, BGMStart, GameMatchReset
 * Called by: GameLoop
 *
 * Elecbyte file: src/mugen/match.c
 */
uint32_t GameReloadStage(void)

{
  int *pi1;
  int i2;
  
  W_Cls(0);
  V_FontDrawRight("Loading",(int *)g[0x413a],V_Width + -4,V_Height + -2,
                  0x18 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x30 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                  0x18 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
  FrameSkipReset();
  DrawToScreen();
  PalGrpClear();
  GameStgDeInitFightData();
  GameUnloadStage();
  GameResetPersistVars();
  PlayerCacheClear();
  g[0x81c9] = Ticks;
  i2 = GameLoadStage();
  if ((i2 != 0) && (i2 = GameStgInitFightData(), pi1 = g, i2 != 0)) {
    g[0x81c9] = Ticks - g[0x81c9];
    GameSetVol(pi1[0x6ef5],pi1[0x6ef7]);
    BGMStart(g + 0x10aa);
    GameMatchReset();
    FrameSkipReset();
    return 1;
  }
  return 0;
}

/* GameMatchReset @ 0x0809edf0, 1043 bytes
 *
 * Resets everything for a new match: persistent variables, team order,
 * active team members, round counters and timers, then the first round
 * (GameRoundReset) and the stage background.
 *
 * Calls: GameResetPersistVars, TeamResetPersistVars, TeamReorderAll,
 *        GameLoadAndActivateTeam, GameRoundReset, BGArrayReset
 * Called by: GamePlay, GameReloadStage
 *
 * Elecbyte file: src/mugen/match.c
 * Note: removed 1 x87 control-word save statements
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 6 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x30 bytes, 3
 *       variables), because their address is taken.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void GameMatchReset(void)

{
  float80 f1;
  int *pi2;
  int *pi3;
  int i2;
  int i5;
  int i6;
  uint32_t u7;
  uint16_t entry_FPUControlWord;
  unsigned char frame[0x30] __attribute__((aligned(16)));
#define stk_2c (*(float (*)[4])(frame + 0x4))
#define stk_1c (*(uint16_t *)(frame + 0x14))
#define stk_1a (*(uint16_t *)(frame + 0x16))
  
  if (g[0x33b3] == 0) {
    GameResetPersistVars();
  }
  else {
    TeamResetPersistVars(2 - g[0x33b3]);
  }
  i5 = 0xe950;
  i2 = 0xe960;
  i6 = 1;
  TeamReorderAll(0);
  TeamReorderAll(1);
  GameLoadAndActivateTeam(0);
  GameLoadAndActivateTeam(1);
  pi2 = g;
  pi3 = g;
  do {
    *(uint32_t *)((int)pi2 + i2 + 0xc) = 0x3f800000;
    i2 = i2 + 0x1a9c;
    pi3[0x3a57] = 0;
    pi3[0x3a58] = 0;
    pi3[0x3a59] = 0;
    *(uint32_t *)((int)pi2 + i5 + 0x18) = 1;
    i5 = i5 + 0x1a9c;
    pi3[0x3a5c] = pi2[0x4e75];
    pi3[0x3a5d] = pi2[0x4e76];
    pi3 = pi3 + 0x6a7;
    i6 = i6 + -1;
  } while (-1 < i6);
  pi2 = g;
  if ((1 < g[0x33b9]) || (1 < g[0x3a60])) {
    i2 = 0;
    do {
      pi2[i2 * 0x6a7 + 0x3a57] = 0x7d;
      pi2[i2 * 0x6a7 + 0x3a5a] = 0;
      pi2[i2 * 0x6a7 + 0x3a58] = 0x43898000;
      pi2[i2 * 0x6a7 + 0x3a59] = 0x3f19999a;
      if (1 < pi2[(1 - i2) * 0x6a7 + 0x33b9]) {
        pi2[i2 * 0x6a7 + 0x3a5c] = pi2[(1 - i2) * 0x6a7 + 0x33b9];
      }
      pi2 = g;
      i5 = i2 + 1;
      g[i2 * 0x6a7 + 0x3a5d] = 0;
      i2 = i5;
    } while (i5 < 2);
  }
  pi3 = g;
  i2 = 0;
  do {
    stk_2c[i2] = (float80)pi2[i2 * 0x6a7 + 0x33bd] / (float80)pi2[i2 * 0x6a7 + 0x3a5c];
    i2 = i2 + 1;
    pi2 = g;
  } while (i2 < 2);
  stk_2c[0] = stk_2c[0] / stk_2c[1];
  f1 = stk_2c[0];
  if (stk_2c[0] < 1.0) {
    f1 = 1.0 / stk_2c[0];
  }
  u7 = (uint32_t)(stk_2c[0] < 1.0);
  g[u7 * 0x6a7 + 0x3a5b] = BITS_F2I(int, (1.0 / f1));
  if (pi3[0x33b4] != 0) {
    u7 = pi3[0x33b4] - 1;
    pi3[u7 * 0x6a7 + 0x3a5c] = 999999;
    if (pi3[u7 * 0x6a7 + 0x33b9] < 2) {
      pi3[(1 - u7) * 0x6a7 + 0x3a5c] = 1;
    }
    else {
      pi3[u7 * 0x6a7 + 0x3a5b] =
           (int)(1.0 - (float)(pi3[u7 * 0x6a7 + 0x33b9] + -1) * ((double)0.1));
      pi3[u7 * 0x6a7 + 0x3a57] =
           (int)X87_FIST32((float80)pi3[u7 * 0x6a7 + 0x3a57] *
                      (1.0 / (float80)pi3[u7 * 0x6a7 + 0x33b9]));
      pi3[u7 * 0x6a7 + 0x3a58] =
           (int)((1.0 / ((float80)pi3[u7 * 0x6a7 + 0x33b9] - 0.5)) *
                (float80)pi3[u7 * 0x6a7 + 0x3a58]);
    }
  }
  pi2 = g;
  if (g[0x81cc] != 0) {
    g[u7 * 0x6a7 + 0x3a5b] = 0x3f800000;
  }
  pi3 = g;
  i2 = 1;
  if (0 < pi2[0x7395]) {
    i5 = 0x1cf64;
    do {
      i6 = *(int *)(i5 + 4 + (int)pi2);
      if (i6 != 0) {
        *(uint32_t *)(i6 + 0x180) = 0;
        *(uint32_t *)(i6 + 0x178) = 0;
        *(uint32_t *)(i6 + 0x342c) = 0;
        pi2 = pi3;
      }
      i2 = i2 + 1;
      i5 = i5 + 4;
    } while (i2 <= pi2[0x7395]);
  }
  i5 = 9;
  GameRoundReset();
  pi2 = g;
  i2 = 0;
  g[0x7546] = 0;
  pi2[0x7517] = 0;
  pi2[0x7506] = 1;
  pi2[0x7508] = 0;
  pi2[0x7507] = 0;
  pi2[0x750a] = 0;
  do {
    *(uint32_t *)((int)pi2 + i2 + 0x1d48c) = 0xffffffff;
    *(uint32_t *)((int)pi2 + i2 + 0x1d464) = 0xffffffff;
    *(uint32_t *)((int)pi2 + i2 + 0x1d4dc) = 0xffffffff;
    *(uint32_t *)((int)pi2 + i2 + 0x1d4b4) = 0xffffffff;
    i2 = i2 + 4;
    i5 = i5 + -1;
  } while (-1 < i5);
  pi2 = g + 0x7317;
  for (i2 = 6; pi3 = g, i2 != 0; i2 = i2 + -1) {
    *pi2 = 0;
    pi2 = pi2 + 1;
  }
  g[0x74e1] = 0;
  BGArrayReset(pi3[0x6ed4]);
  return;
}
#undef stk_2c
#undef stk_1c
#undef stk_1a

/* GameRoundReset @ 0x0809f210, 1639 bytes
 *
 * Resets everything for a new round: stops player sounds, resets each player
 * (life, power per the rules, position, state), refreshes inputs, clears
 * explods, projectiles and persistent animations, moves the camera to its
 * start, resets the round timer and the fight screen elements.
 *
 * Player fields read: ishelper, teammode, active
 * Player fields written: life, ctrl, life, lifemax
 * Globals read: round_over_time
 * Calls: SndIDStop, PlayerReset, PlayerChangeState, KBIRefreshKeyflags,
 *        PlayerEnableSet, GameRoundResetPlayerPos, CameraMoveAbs,
 *        AnimPerArrayClear, MasterPalAdd, MasterPalMul, BGArrayReset,
 *        PalFXReset, PalGrpResetPalette, GameAftImgReset, ExplodArrayReset
 * Called by: ArcadeWinScreen, ContinueScreenLoop, GameLoop,
 *            GameMatchReset, GameNextRound, SurvivalResultsScreen
 *
 * Elecbyte file: src/mugen/match.c
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 7 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
void GameRoundReset(void)

{
  int i1;
  int i2;
  int *player;
  int *pi4;
  int i3;
  int player2;
  int i7;
  int *pi8;
  int stk_48;
  int stk_44;
  int stk_40;
  int stk_3c;
  int stk_30;
  int stk_2c;
  int stk_28;
  
  pi8 = g;
  SndIDStop(-1);
  pi4 = g;
  i3 = g[0x4e61];
  g[0x7510] = g[G_ROUND_OVER_TIME];
  pi4[0x7509] = 0;
  pi4[0x7518] = 0;
  pi4[0x750b] = 0;
  pi4[0x750d] = 0;
  pi4[0x750c] = 0;
  pi4[0x750e] = 0;
  pi4[0x750f] = 0;
  pi4[0x7511] = 0;
  pi4[0x7512] = 0;
  pi4[0x7513] = 0;
  pi4[0x7514] = 0;
  pi4[0x7515] = (pi4[0x79a0] + 1) * i3 + -1;
  pi4[0x7516] = 0;
  if (((pi4[0x33ae] == 3) || (pi4[0x74e8] != 0)) || (pi4[0x33b4] != 0)) {
    g[0x7515] = -1;
  }
  i3 = 1;
  pi4 = g;
  if (0 < g[0x7395]) {
    stk_48 = 0x1cf64;
    do {
      player = *(int **)(stk_48 + 4 + (int)pi4);
      if (player != (int *)0x0) {
        if (player[PL_ISHELPER] == 0) {
          i7 = player[PL_LIFE];
          player2 = player[0x98b];
          i1 = player[0x5e];
          PlayerReset(player);
          PlayerChangeState((int)player,0x170c);
          KBIRefreshKeyflags((int)(player + 0x92),player[600]);
          pi4 = g;
          player[0x98b] = player2;
          player[0x60] = i1;
          player[0x5e] = i1;
          if (pi4[0x74e8] != 0) {
            player2 = *(int *)player[0x5d];
            player[0x60] = player2;
            player[0x61] = player2;
            player[0x5e] = player2;
          }
          if (pi4[player[PL_TEAMMODE] * 0x6a7 + 0x3a5a] == 0) {
            player[PL_LIFE] = i7;
          }
          pi4 = g;
          player[0x5b] = player[PL_LIFE];
          player[0x5a] = player[PL_LIFE];
        }
        else if (player[PL_ACTIVE] != 0) {
          PlayerEnableSet(player[2],0);
          pi4 = g;
        }
      }
      i3 = i3 + 1;
      stk_48 = stk_48 + 4;
    } while (i3 <= pi4[0x7395]);
  }
  i3 = 0;
  do {
    player2 = 0;
    i7 = pi4[i3 * 0x6a7 + 0x33b8];
    player = pi4;
    if (0 < pi4[i3 * 0x6a7 + i7 * 0x17 + 0x33bd]) {
      do {
        i2 = player[pi4[i3 * 0x6a7 + i7 * 0x17 + player2 * 5 + 0x33be] + 0x73d9];
        i1 = (int)X87_FIST32((float80)*(int *)(i2 + 0x50) * BITS_I2F(pi4[i3 * 0x6a7 + 0x3a5b]) *
                           (float80)player[0x799f] * ((float)0.01f) + 0.5);
        *(int *)(i2 + 0x164) = i1;
        if (i1 < *(int *)(i2 + 0x160)) {
          *(int *)(i2 + 0x16c) = i1;
          *(int *)(i2 + 0x168) = i1;
          *(int *)(i2 + 0x160) = i1;
        }
        player2 = player2 + 1;
        player = g;
      } while (player2 < pi4[i3 * 0x6a7 + i7 * 0x17 + 0x33bd]);
    }
    i3 = i3 + 1;
    pi4 = g;
  } while (i3 < 2);
  i3 = 0;
  GameRoundResetPlayerPos();
  pi4 = g;
  stk_3c = 0xe970;
  stk_40 = 0;
  stk_44 = 0;
  do {
    *(uint32_t *)(stk_3c + 8 + (int)pi4) = 0;
    i7 = *(int *)((int)pi8 + stk_40 + 0x10420);
    if (0 < i7) {
      player = pi8 + stk_44 + 0x4109;
      do {
        player2 = pi4[*player + 0x73d9];
        if (player2 != 0) {
          *(float *)((int)pi4 + stk_3c + 8) =
               (float80)*(int *)(player2 + PLB_LIFE) / (float80)*(int *)(player2 + PLB_LIFEMAX) +
               *(float *)((int)pi4 + stk_3c + 8);
        }
        player = player + 5;
        i7 = i7 + -1;
      } while (i7 != 0);
    }
    i7 = *(int *)((int)pi8 + stk_40 + 0x10420);
    if (0 < i7) {
      *(float *)((int)pi4 + stk_3c + 8) = *(float *)((int)pi4 + stk_3c + 8) / (float80)i7
      ;
    }
    player = g;
    stk_3c = stk_3c + 0x1a9c;
    stk_40 = stk_40 + 0x5c;
    stk_44 = stk_44 + 0x17;
    i3 = i3 + 1;
  } while (i3 < 2);
  i3 = 1;
  if (0 < pi4[0x7395]) {
    i7 = 0x1cf64;
    do {
      player2 = *(int *)(i7 + 4 + (int)pi4);
      if (player2 != 0) {
        *(uint32_t *)(player2 + PLB_CTRL) = 0;
        pi4 = player;
      }
      i3 = i3 + 1;
      i7 = i7 + 4;
    } while (i3 <= pi4[0x7395]);
  }
  pi8 = g;
  i3 = 0x1cf64;
  stk_28 = 0x1e650;
  stk_2c = 0x1e640;
  stk_30 = 0x1e620;
  i7 = 3;
  do {
    player2 = *(int *)(i3 + 4 + (int)pi4);
    if (player2 != 0) {
      i1 = *(int *)(stk_30 + 0x14 + (int)pi4);
      if (i1 != -1) {
        *(int *)(player2 + 0x262c) = i1;
        pi4 = pi8;
      }
      i1 = *(int *)(stk_2c + 0x14 + (int)pi4);
      if (i1 != -1) {
        *(int *)(player2 + 0x16c) = i1;
        *(int *)(player2 + 0x168) = i1;
        *(int *)(player2 + PLB_LIFE) = i1;
        *(int *)(player2 + PLB_LIFEMAX) = i1;
        pi4 = pi8;
      }
      i1 = *(int *)(stk_28 + 0x14 + (int)pi4);
      if (i1 != -1) {
        **(int **)(player2 + 0x170) = i1;
        *(int *)(player2 + 0x180) = i1;
        *(int *)(player2 + 0x184) = i1;
        pi4 = pi8;
      }
    }
    stk_28 = stk_28 + 4;
    stk_2c = stk_2c + 4;
    stk_30 = stk_30 + 4;
    i3 = i3 + 4;
    i7 = i7 + -1;
  } while (-1 < i7);
  CameraMoveAbs((float80)pi4[0x1080],(float80)pi4[0x1081]);
  pi8 = g;
  g[0x7316] = 0;
  pi8[0x7315] = 0;
  AnimPerArrayClear((int *)pi8[0x413c]);
  MasterPalAdd(0,0,0);
  MasterPalMul(0,0,0);
  pi8 = g;
  *(uint8_t *)((int)g + 0x1d396) = 0;
  pi4 = g;
  pi8[0x74e3] = 0;
  pi8[0x74e4] = 0;
  *(uint16_t *)(pi8 + 0x74e5) = 0;
  if (pi4[0x107f] != 0) {
    BGArrayReset(pi4[0x6ed4]);
    pi4 = g;
  }
  PalFXReset(pi4 + 0x6ed5);
  PalFXReset(g + 0x6ee4);
  PalGrpResetPalette();
  GameAftImgReset(g[0x413f]);
  ExplodArrayReset((uint32_t *)g[0x52be]);
  ExplodArrayReset((uint32_t *)g[0x52bf]);
  pi8 = g;
  g[0x74f3] = -1;
  pi8[0x7503] = 0;
  pi8[0x74fa] = 0;
  pi8 = pi8 + 0x7317;
  for (i3 = 6; i3 != 0; i3 = i3 + -1) {
    *pi8 = 0;
    pi8 = pi8 + 1;
  }
  pi8 = g + 0x7547;
  for (i3 = 6; i3 != 0; i3 = i3 + -1) {
    *pi8 = 0;
    pi8 = pi8 + 1;
  }
  pi8 = g + 0x754d;
  for (i3 = 6; i3 != 0; i3 = i3 + -1) {
    *pi8 = 0;
    pi8 = pi8 + 1;
  }
  keypauseflag = 0;
  g[0x7309] = 0;
  return;
}

/* GameRoundResetPlayerPos @ 0x0809f880, 221 bytes
 *
 * Puts the active players at their stage start positions and facings
 * (velocities cleared).
 *
 * Player fields written: pos_x, pos_y, pos_z
 * Calls: PlayerTurnAround
 * Called by: GameRoundReset, GameRoundUpdate
 *
 * Elecbyte file: src/mugen/match.c
 * Note: 6 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
int GameRoundResetPlayerPos(void)

{
  int i1;
  int i2;
  int i3;
  int *pi4;
  int player;
  
  pi4 = g;
  player = 3;
  i3 = 0x1cf64;
  do {
    i2 = *(int *)(i3 + 4 + (int)pi4);
    if (i2 != 0) {
      *(uint32_t *)(i2 + 0x1bc) = 0;
      *(uint32_t *)(i2 + 0x1b8) = 0;
      *(uint32_t *)(i2 + 0x1b4) = 0;
    }
    i3 = i3 + 4;
    player = player + -1;
  } while (-1 < player);
  i3 = 1;
  do {
    player = pi4[i3 + 0x73d9];
    if (player != 0) {
      if (pi4[i3 + 0x1094] != *(int *)(player + 400)) {
        PlayerTurnAround(player);
        pi4 = g;
      }
      i2 = pi4[i3 + 0x1088] + 0xa0;
      *(float *)(player + PLB_POS_X) = (float80)i2;
      *(float *)(player + 0x1a8) = (float80)i2;
      i1 = pi4[i3 + 0x108c];
      *(float *)(player + PLB_POS_Y) = (float80)i1;
      *(float *)(player + 0x1ac) = (float80)i1;
      i1 = pi4[i3 + 0x1090];
      *(float *)(player + PLB_POS_Z) = (float80)i1;
      *(float *)(player + 0x1b0) = (float80)i1;
    }
    i3 = i3 + 1;
    pi4 = g;
  } while (i3 < 5);
  return i2;
}

/* GameRoundWinner @ 0x0809f960, 12 bytes
 *
 * Returns the winner of the last round (1 or 2, 0 for a draw).
 *
 * Called by: GameNextRound, GameRoundDraw, GameRoundUpdate, LogMatch
 *
 * Elecbyte file: src/mugen/match.c
 */
int GameRoundWinner(void)

{
  return g[0x7512];
}

/* GameMatchWinner @ 0x0809f970, 200 bytes
 *
 * Returns the team that has won the match (enough rounds won, or the last
 * member of a turns team KOed), or 0 if the match goes on. Used by the
 * MatchOver trigger and the round logic.
 *
 * Globals read: round_over_hittime
 * Called by: GameRoundUpdate, SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/match.c
 */
int GameMatchWinner(void)

{
  int i1;
  int i2;
  int i3;
  
  i3 = 0;
  if (((g[0x7511] == 3) && (g[0x7514] < g[G_ROUND_OVER_HITTIME])) || (i1 = 0, g[0x7511] < 3)) {
    i3 = 0;
  }
  else {
    for (; i1 < 2; i1 = i1 + 1) {
      i2 = g[i1 + 0x7507];
      if ((g[0x7509] == 0) &&
         ((g[0x7512] == i1 + 1 ||
          ((g[0x7512] == 0 && (g[i1 * 0x6a7 + 0x3a5d] < g[0x750a] + 1)))))) {
        i2 = i2 + 1;
      }
      if (g[i1 * 0x6a7 + 0x3a5c] <= i2) {
        if (i3 == 0) {
          i3 = i1 + 1;
        }
        else if (g[0x33b3] == 0) {
          i3 = 1;
        }
        else {
          i3 = 3 - g[0x33b3];
        }
      }
    }
  }
  return i3;
}

/* LogPreMatch @ 0x0809fa40, 508 bytes
 *
 * Writes the "[Match n]" header with the team members to the match log
 * (-log).
 *
 * Globals read: charinfo
 * C library: fopen, fprintf, fclose
 * Called by: GamePlay
 * Messages:
 *   "[Match %i]\n"
 *   "totalmatches = %i\n"
 *   "team%i.%i = "
 *   "stage = %s\n"
 *
 * Elecbyte file: src/mugen/match.c
 */
void LogPreMatch(void)

{
  FILE *stream;
  uint32_t stale_ECX;
  uint32_t stale_ECX_00;
  uint32_t u1;
  int *pi2;
  uint32_t stale_EDX;
  uint32_t u3;
  uint32_t stale_EDX_00;
  int *pi4;
  int i5;
  int i2;
  int stk_28;
  int stk_24;
  int stk_20;
  int stk_1c;
  int stk_18;
  
  if ((g[0x758c] != 0) && (stream = fopen((char *)(g + 0x758d),"at"), stream != (FILE *)0x0)) {
    stk_20 = g[0x7543];
    fprintf(stream,"[Match %i]\n",stk_20);
    fprintf(stream,"totalmatches = %i\n",g[0x7544]);
    stk_1c = 0;
    stk_28 = 0;
    pi2 = g;
    do {
      stk_18 = 0;
      pi4 = pi2;
      if (0 < *(int *)((int)pi2 + stk_28 + 0xcee4)) {
        stk_24 = (int)pi2 + stk_28 + 0xcef8;
        i5 = (int)pi2 + stk_28 + 0xceec;
        do {
          fprintf(stream,"team%i.%i = ",stk_1c + 1,stk_18 + 1);
          u1 = stale_ECX;
          if (0 < *(int *)(i5 + 8)) {
            stk_20 = 0;
            i2 = 0;
            u3 = stale_EDX;
            do {
              if (0 < i2) {
                fprintf(stream,", ",u3,u3);
              }
              i2 = i2 + 1;
              fprintf(stream,(char *)(g[0x1b50] + 4 +
                                       *(int *)(g[G_CHARINFO] + 0x500c +
                                               *(int *)(stk_20 + stk_24) * 0x702c) * 0x2038),
                      stk_20,stk_20);
              stk_20 = stk_20 + 0x14;
              u1 = stale_ECX_00;
              u3 = stale_EDX_00;
            } while (i2 < *(int *)(i5 + 8));
          }
          i5 = i5 + 0x5c;
          fprintf(stream,"\n",u1,u1);
          stk_24 = stk_24 + 0x5c;
          stk_18 = stk_18 + 1;
          pi4 = g;
        } while (stk_18 < *(int *)((int)pi2 + stk_28 + 0xcee4));
      }
      stk_1c = stk_1c + 1;
      stk_28 = stk_28 + 0x1a9c;
      pi2 = pi4;
    } while (stk_1c < 2);
    fprintf(stream,"stage = %s\n",pi4 + 0x805,stk_20);
    fprintf(stream,"\n");
    fclose(stream);
  }
  return;
}

/* LogMatch @ 0x0809fc40, 299 bytes
 *
 * Writes "[Match n Round m]" with the winning team and the time left to the
 * match log.
 *
 * Globals read: round_no
 * Calls: GameRoundWinner
 * C library: fopen, fprintf, fclose
 * Called by: GamePlay, GameRoundUpdate
 * Messages:
 *   "[Match %i Round %i]\n"
 *   "winningteam = %i\n"
 *   "timeleft = %.2f\n"
 *   "p%i.name = %s\n"
 *   "p%i.life = %i\n"
 *   "p%i.power = %i\n"
 *
 * Elecbyte file: src/mugen/match.c
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void LogMatch(void)

{
  int i1;
  float80 d2;
  FILE *stream;
  int i3;
  int *pi4;
  int i5;
  
  if (g[0x758c] != 0) {
    stream = fopen((char *)(g + 0x758d),"at");
    if (stream != (FILE *)0x0) {
      fprintf(stream,"[Match %i Round %i]\n",g[0x7543],g[G_ROUND_NO]);
      i3 = GameRoundWinner();
      fprintf(stream,"winningteam = %i\n",i3);
      if (g[0x7515] == -1) {
        d2 = -1.0;
      }
      else {
        d2 = (double)g[0x7515] / (double)g[0x4e61];
      }
      i5 = 1;
      i3 = 0x1cf64;
      fprintf(stream,"timeleft = %.2f\n",d2);
      do {
        pi4 = g + 1;
        i1 = *(int *)(i3 + (int)pi4);
        if (i1 != 0) {
          fprintf(stream,"p%i.name = %s\n",i5,i1 + 0x20);
          fprintf(stream,"p%i.life = %i\n",i5,*(uint32_t *)(i1 + 0x160));
          pi4 = (int *)fprintf(stream,"p%i.power = %i\n",i5,**(uint32_t **)(i1 + 0x170)
                                 );
        }
        i5 = i5 + 1;
        i3 = i3 + 4;
      } while (i5 < 5);
      fprintf(stream,"\n",pi4,pi4);
      fclose(stream);
    }
  }
  return;
}

