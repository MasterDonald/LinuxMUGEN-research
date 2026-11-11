/*
 * menus.c -- menus and storyboards
 * Storyboard playback (intro and others), the title screen, the options and
 * key configuration screens, the training mode menu and the information text
 * box.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/menus.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"

extern int ShowInfoNow_0 __asm__("D_08287a94"); /* file-static 0x08287a94 */

/* IntroScreen @ 0x0809fd70, 28 bytes
 *
 * Plays the motif's intro storyboard, if one is configured.
 *
 * Globals read: files_intro_storyboard
 * Calls: PlayCutscene
 * Called by: MainLoop
 *
 * Elecbyte file: src/mugen/menus.c
 */
void IntroScreen(void)

{
  PlayCutscene((char *)(g + G_FILES_INTRO_STORYBOARD),"scene");
  return;
}

/* PlayCutscene @ 0x0809fd90, 1054 bytes
 *
 * Plays a storyboard file. It loads it (relative to the motif directory),
 * registers the music callbacks and runs it at 60 frames per second until it
 * ends or a key is pressed (if skippable). It updates, draws and fades each
 * frame, then frees it. Message: "Error loading storyboard: <file>".
 *
 * Parameters:
 *   path         char *
 *   arg2         char *
 *
 * Globals read: errmsg, backbuffer, debug_display,
 *               sound_linux_pausebgmondefocus, speed_flag, vretrace
 * Calls: FindFileDir, SceneReadFile, SceneRegisterBGMFn, V_SetBuf, W_Cls,
 *        TimerSetSyncFPS, KBBufferClear, PadPoll, PadBufClear,
 *        UInpRefreshFlags, UInpBufClear, BGMResume, BGMPause,
 *        BGMPollIgnoreDefocus, KBPoll, KBkbhit, KBgetchraw, PadHit,
 *        PadGet, GlobalInputUpdate, UInpHit, UInpGet, KBIMenuGetKey,
 *        PRSprArrayClear, ...
 * C library: strcat
 * Called by: GamePlay, IntroScreen, MainLoop, _mangled_main
 * Messages:
 *   "\nError loading storyboard: "
 *
 * Elecbyte file: src/mugen/menus.c
 * Note: 3 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x2040 bytes,
 *       8 variables), because their address is taken.
 */
void PlayCutscene(char *path,char *arg2)

{
  bool b1;
  bool b2;
  bool b3;
  bool b4;
  bool b5;
  int i6;
  int *pi7;
  uint32_t stale_var;
  uint32_t stale_var_00;
  uint32_t stale_var_01;
  int *pi8;
  uint32_t u9;
  unsigned char frame[0x2040] __attribute__((aligned(16)));
#define stk_2040 (*(uint32_t *)(frame + 0x0))
#define stk_2034 (*(uint32_t (*)[2])(frame + 0xc))
#define stk_202c (*(uint32_t *)(frame + 0x14))
#define stk_2028 (*(uint32_t *)(frame + 0x18))
#define stk_2024 (*(int **)(frame + 0x1c))
#define stk_2020 (*(int **)(frame + 0x20))
#define stk_201c (*(char (*)[4096])(frame + 0x24))
#define filename (*(char (*)[4108])(frame + 0x1024))
  
  b1 = false;
  b4 = false;
  b3 = false;
  b2 = false;
  if ((path != (char *)0x0) && (*path != '\0')) {
    i6 = FindFileDir(path,filename,stk_201c);
    if (i6 != 0) {
      pi7 = SceneReadFile(filename,arg2,0,0);
      if (pi7 == (int *)0x0) {
        strcat((char *)(g + G_ERRMSG),"\nError loading storyboard: ");
        strcat((char *)(g + G_ERRMSG),path);
      }
      else {
        SceneRegisterBGMFn(pi7,BGMPlayForScene,BGMStopForScene);
        stk_2024 = g + 0x733b;
        stk_2020 = g + 0x7348;
        V_SetBuf((int *)g[G_BACKBUFFER],0);
        W_Cls(0);
        TimerSetSyncFPS(0x3c);
        KBBufferClear();
        PadPoll();
        PadBufClear();
        UInpRefreshFlags();
        UInpBufClear();
        do {
          pi8 = g;
          if (g[G_DEBUG_DISPLAY] == 0) {
            keypauseflag = 0;
            g[0x7309] = 0;
          }
          if ((pi8[0x7309] == 0) || (b1)) {
            if ((pi8[0x7309] == 0) && (b1)) {
              b1 = false;
              BGMResume(pi8 + 0x6efa);
              pi8 = g;
            }
          }
          else {
            b1 = true;
            BGMPause(pi8 + 0x6efa);
            pi8 = g;
          }
          i6 = 0;
          BGMPollIgnoreDefocus(pi8 + 0x6efa);
          stk_202c = 0;
          stk_2028 = 0;
          PadPoll();
          KBPoll();
          b5 = KBkbhit();
          if (ZEXT8(b5) != 0) {
            stk_202c = KBgetchraw();
          }
          b5 = PadHit();
          if (ZEXT8(b5) != 0) {
            stk_2028 = PadGet();
          }
          GlobalInputUpdate();
          b5 = UInpHit();
          if (ZEXT8(b5) != 0) {
            i6 = UInpGet();
          }
          KBIMenuGetKey(stk_2034,i6,(int)&stk_2024,2);
          if ((stk_2034[0] & 0xff0) != 0) {
            b4 = true;
          }
          if (stk_202c == 1) {
            b4 = true;
          }
          PRSprArrayClear((int *)g[0x413d]);
          if (g[G_SOUND_LINUX_PAUSEBGMONDEFOCUS] != 0) {
            if ((b2) || (g[0x74e7] != 0)) {
              if ((!b2) || (g[0x74e7] == 0)) goto L_080a0075;
              b2 = false;
              u9 = stk_2040;
            }
            else {
              b2 = true;
              stk_2040 = BGMGetVolume(g + 0x6efa);
              u9 = 0;
            }
            BGMSetVolume(g + 0x6efa,u9);
          }
L_080a0075:
          if ((g[0x7309] == 0) && (i6 = SceneUpdate(pi7), i6 != 0)) {
            b4 = true;
          }
          i6 = (int)(char)keypauseflag;
          g[0x7309] = i6;
          if (b3) {
            b3 = false;
            keypauseflag = 1;
          }
          if (((((i6 != 0) && (stk_202c != 0)) && (!b3)) &&
              (((stk_202c & 0x100) == 0 && (stk_202c != 0x58)))) && (stk_202c == 0x46)) {
            keypauseflag = 0;
            b3 = true;
          }
          if (stk_202c == 0x58) {
            ScreenSnap();
          }
          if (g[0x7307] == 0) {
            MasterPalReset();
            SceneUpdatePal(pi7);
            MasterPalProcessChanges();
            SceneDraw(pi7);
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
        } while (!b4);
        FrameSkipReset();
        SceneFree(pi7);
      }
    }
  }
  return;
}
#undef stk_2040
#undef stk_2034
#undef stk_202c
#undef stk_2028
#undef stk_2024
#undef stk_2020
#undef stk_201c
#undef filename

/* ModeSelect @ 0x080a01b0, 5751 bytes
 *
 * The title screen. Shows the motif's title background and menu and handles
 * cursor movement, sounds, and the idle timer that starts demo mode
 * ("Loading demo"). F1 opens the information box ("Press F1 for info"):
 * version "Beta %i.%02i.%02i", "(c) Elecbyte 2002" and a summary of the
 * terms of use. The beta licence date is also checked here: after it, the
 * screen shows "The beta period for this version of M.U.G.E.N has ended".
 * The chosen mode is stored in the game mode globals.
 *
 * Globals read: title_info_fadein_time, backbuffer, config_firstrun,
 *               sound_linux_masterwavvolume, sound_linux_midivolume,
 *               num_chars, input_p1_joystick_type_1ce34,
 *               input_p2_joystick_type_1ce38, sys_sounds,
 *               demo_mode_title_waittime, speed_flag, vretrace
 * Globals written: demo_mode
 * Calls: V_SetBuf, W_Cls, TimerSetSyncFPS, KBBufferClear, PadPoll,
 *        PadBufClear, UInpRefreshFlags, UInpBufClear, CharselResetCursor,
 *        CharselResetMenuPos, GameSetVol, BGArrayReset, datenotostr,
 *        BGMLoadAndStart, ErrorExit, FrameSkipReset, BGMPoll, KBPoll,
 *        KBkbhit, KBgetchraw, PadHit, PadGet, GlobalInputUpdate, UInpHit,
 *        ...
 * C library: memcpy, strcpy, sprintf, strcat
 * Called by: MainLoop
 * Messages:
 *   "[big]M.U.G.E.N Information\n[small][col=192,192,192]\n. Thanks for
 *     using MUGEN! MUGEN betas are available from\n[big]
 *     www.elecbyte.com.\n\n[small]. Please refer to readme.txt before using
 *     MUGEN.\n\n. Answers to commonly-asked questions can be found in\n
 *     mugenfaq.txt.\n\n[big][col=255,255,255]\nSummary of Terms of
 *     Use\n[small][col=192,192,192]\n. This version of MUGEN is to be used
 *     AT YOUR OWN RISK.\n\n. You may use MUGEN beta "
 *   "\n  after which you MUST obtain a new license.\n\n. The full
 *     description of the license is in readme.txt. Please\n  read it
 *     carefully.\n[small][col=192,192,128]\n\n\n\nPress F1 to continue."
 *   "%i.%02i.%02i "
 *   "until "
 *   "Loading demo"
 *   "Beta %i.%02i.%02i"
 *
 * Elecbyte file: src/mugen/menus.c
 * Note: removed 2 x87 control-word save statements
 * Note: 3 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: 19 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x13a0 bytes,
 *       38 variables), because their address is taken.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void ModeSelect(void)

{
  int *pi1;
  float80 f2;
  bool b3;
  bool b4;
  int *pi5;
  bool b6;
  int i2;
  uint32_t stale_var;
  uint32_t stale_var_00;
  uint32_t stale_var_01;
  uint32_t u8;
  int i9;
  uint32_t *pu10;
  uint32_t *pu11;
  uint32_t u12;
  uint32_t u13;
  int *pi14;
  uint32_t u15;
  uint32_t u16;
  int i17;
  int i18;
  int i19;
  int i20;
  uint32_t u21;
  int *sounds;
  int i23;
  int i24;
  uint16_t entry_FPUControlWord;
  char *pc25;
  unsigned char frame[0x13a0] __attribute__((aligned(16)));
#define stk_1398 (*(int **)(frame + 0x8))
#define stk_1350 (*(int *)(frame + 0x50))
#define stk_134c (*(int *)(frame + 0x54))
#define stk_1348 (*(int *)(frame + 0x58))
#define stk_1344 (*(int *)(frame + 0x5c))
#define stk_1340 (*(int *)(frame + 0x60))
#define stk_133c (*(int *)(frame + 0x64))
#define stk_1334 (*(int *)(frame + 0x6c))
#define stk_1330 (*(int *)(frame + 0x70))
#define stk_132c (*(int *)(frame + 0x74))
#define stk_1328 (*(uint32_t *)(frame + 0x78))
#define stk_1324 (*(int *)(frame + 0x7c))
#define stk_131c (*(int **)(frame + 0x84))
#define stk_1318 (*(int *)(frame + 0x88))
#define stk_1314 (*(int *)(frame + 0x8c))
#define stk_1310 (*(int *)(frame + 0x90))
#define stk_130c (*(int **)(frame + 0x94))
#define stk_1308 (*(int **)(frame + 0x98))
#define stk_1304 (*(int *)(frame + 0x9c))
#define stk_1300 (*(uint16_t *)(frame + 0xa0))
#define stk_12fe (*(uint16_t *)(frame + 0xa2))
#define stk_12fc (*(int (*)[2])(frame + 0xa4))
#define stk_12f4 (*(uint32_t **)(frame + 0xac))
#define stk_12f0 (*(uint32_t *)(frame + 0xb0))
#define stk_12ec (*(uint32_t *)(frame + 0xb4))
#define stk_12e8 (*(uint32_t *)(frame + 0xb8))
#define stk_12e4 (*(uint32_t *)(frame + 0xbc))
#define stk_12e0 (*(uint32_t *)(frame + 0xc0))
#define stk_12dc (*(uint32_t *)(frame + 0xc4))
#define stk_12d8 (*(int *)(frame + 0xc8))
#define stk_12d4 (*(int *)(frame + 0xcc))
#define stk_12d0 (*(float *)(frame + 0xd0))
#define stk_12cc (*(uint32_t *)(frame + 0xd4))
#define stk_12c8 (*(uint32_t *)(frame + 0xd8))
#define stk_12bc (*(uint32_t (*)[1024])(frame + 0xe4))
#define stk_2bc (*(char (*)[192])(frame + 0x10e4))
#define stk_1fc (*(char (*)[432])(frame + 0x11a4))
#define stk_4c (*(int (*)[15])(frame + 0x1354))
  
  pi5 = g;
  pi1 = g + G_TITLE_INFO_FADEIN_TIME;
  stk_1328 = g[0x33b5];
  stk_134c = -1;
  stk_1330 = 0;
  stk_1334 = 0;
  b3 = false;
  stk_133c = 1;
  stk_1340 = 0;
  stk_1344 = 0;
  stk_1348 = 0;
  stk_1350 = -1;
  b4 = false;
  memcpy(stk_1fc,
         "[big]M.U.G.E.N Information\n[small][col=192,192,192]\n. Thanks for using MUGEN! MUGEN betas are available from\n[big]  www.elecbyte.com.\n\n[small]. Please refer to readme.txt before using MUGEN.\n\n. Answers to commonly-asked questions can be found in\n  mugenfaq.txt.\n\n[big][col=255,255,255]\nSummary of Terms of Use\n[small][col=192,192,192]\n. This version of MUGEN is to be used AT YOUR OWN RISK.\n\n. You may use MUGEN beta "
         ,0x1a2);
  memcpy(stk_2bc,
         "\n  after which you MUST obtain a new license.\n\n. The full description of the license is in readme.txt. Please\n  read it carefully.\n[small][col=192,192,128]\n\n\n\nPress F1 to continue."
         ,0xb5);
  stk_130c = g + 0x733b;
  stk_1308 = g + 0x7348;
  V_SetBuf((int *)g[G_BACKBUFFER],0);
  W_Cls(0);
  TimerSetSyncFPS(0x3c);
  KBBufferClear();
  PadPoll();
  PadBufClear();
  UInpRefreshFlags();
  UInpBufClear();
  if (ShowInfoNow_0 == -1) {
    ShowInfoNow_0 = 0;
    if ((g[G_CONFIG_FIRSTRUN] != 0) || (g[0x801] == 0)) {
      ShowInfoNow_0 = 1;
    }
    if (g[0x74e6] != 0) {
      ShowInfoNow_0 = 1;
    }
  }
  stk_1328 = stk_1328 & (g[G_DEMO_MODE] != 0) - 1;
  g[G_DEMO_MODE] = 0;
  CharselResetCursor();
  CharselResetMenuPos();
  GameSetVol(g[G_SOUND_LINUX_MASTERWAVVOLUME],g[G_SOUND_LINUX_MIDIVOLUME]);
  sounds = g;
  i18 = 10;
  i9 = 0;
  i2 = 0;
  pi14 = pi5 + 0x1017;
  do {
    *(int **)((int)stk_4c + i2) = pi14;
    if ((char)pi5[i2 * 2 + 0x1017] == '\0') {
      *(uint32_t *)((int)stk_4c + i2) = 0;
    }
    else {
      i9 = i9 + 1;
    }
    pi14 = pi14 + 8;
    i2 = i2 + 4;
    i18 = i18 + -1;
  } while (-1 < i18);
  if (i9 == 0) {
    if ((g[G_NUM_CHARS] < 1) || (keyflag[1] != 0)) {
      stk_1328 = 10;
    }
    else {
      g[G_DEMO_MODE] = 1;
      sounds[0x74f1] = 0;
      stk_1328 = 1;
      stk_133c = 1;
    }
  }
  else {
    i2 = stk_4c[stk_1328];
    while (i2 == 0) {
      stk_1328 = stk_1328 + 1 & (10 < (int)(stk_1328 + 1)) - 1;
      i2 = stk_4c[stk_1328];
    }
    BGArrayReset(g[0x62ce]);
    sounds = stk_12fc;
    for (i2 = 0xe; i2 != 0; i2 = i2 + -1) {
      *sounds = 0;
      sounds = sounds + 1;
    }
    strcpy((char *)stk_12bc,stk_1fc);
    pu10 = stk_12bc;
    do {
      pu11 = pu10;
      pu10 = pu11 + 1;
      u15 = *pu11 + 0xfefefeff & (*pu11 ^ 0xffffffff);
      u16 = u15 & 0x80808080;
    } while (u16 == 0);
    if ((u15 & 0x8080) == 0) {
      u16 = u16 >> 0x10;
      pu10 = (uint32_t *)((int)pu11 + 6);
    }
    sprintf((char *)((int)pu10 + (-3 - (uint32_t)CARRY1((uint8_t)u16,(uint8_t)u16))),"%i.%02i.%02i ",
            MUGENDATE_Y,MUGENDATE_M,MUGENDATE_D);
    strcat((char *)stk_12bc,"until ");
    pu10 = stk_12bc;
    do {
      pu11 = pu10;
      pu10 = pu11 + 1;
      u15 = *pu11 + 0xfefefeff & (*pu11 ^ 0xffffffff);
      u16 = u15 & 0x80808080;
    } while (u16 == 0);
    if ((u15 & 0x8080) == 0) {
      u16 = u16 >> 0x10;
      pu10 = (uint32_t *)((int)pu11 + 6);
    }
    datenotostr(MUGENEXPDATE_Y,MUGENEXPDATE_M,(uint8_t **)MUGENEXPDATE_D,
                (char *)((int)pu10 + (-3 - (uint32_t)CARRY1((uint8_t)u16,(uint8_t)u16))));
    strcat((char *)stk_12bc,stk_2bc);
    stk_12f0 = (V_Width + -0x118) / 2;
    stk_12ec = 0xffffff33;
    stk_12c8 = 0xffffff33;
    stk_12e4 = 0xffffff33;
    stk_12dc = (V_Height + -200) / 2;
    stk_12fc[0] = 0x118;
    stk_12fc[1] = 200;
    stk_12f4 = stk_12bc;
    stk_12e8 = stk_12f0;
    stk_12e0 = stk_12f0;
    i2 = BGMLoadAndStart(g + 0x6efa,(uint8_t *)(g + 0x62d1),g[0x66d1],0);
    if (i2 == 0) {
      ErrorExit();
    }
    FrameSkipReset();
    stk_1314 = 0;
    do {
      i2 = 0;
      BGMPoll(g + 0x6efa);
      stk_1314 = 0;
      stk_1310 = 0;
      PadPoll();
      KBPoll();
      b6 = KBkbhit();
      if (ZEXT8(b6) != 0) {
        stk_1314 = KBgetchraw();
      }
      b6 = PadHit();
      if (ZEXT8(b6) != 0) {
        stk_1310 = PadGet();
      }
      GlobalInputUpdate();
      b6 = UInpHit();
      if (ZEXT8(b6) != 0) {
        i2 = UInpGet();
      }
      KBIMenuGetKey((uint32_t *)&stk_131c,i2,(int)&stk_130c,2);
      i2 = stk_1318;
      sounds = stk_131c;
      PRSprArrayClear((int *)g[0x413d]);
      if (((g[G_INPUT_P1_JOYSTICK_TYPE_1CE34] == 0x16) || (g[G_INPUT_P2_JOYSTICK_TYPE_1CE38] == 0x16)) && (stk_1310 == 0xb)) {
        stk_1314 = 1;
        stk_1310 = 0;
      }
      if ((stk_12cc == 0) && (stk_1348 == 1)) {
        if (((uint32_t)sounds & 1) != 0) {
          do {
            stk_1328 = stk_1328 - 1;
            if ((int)stk_1328 < 0) {
              stk_1328 = 10;
            }
          } while (stk_4c[stk_1328] == 0);
          GameSndPlay((int *)g[G_SYS_SOUNDS],pi5[0x1007],pi5[0x1008],0);
        }
        if (((uint32_t)sounds & 4) != 0) {
          do {
            stk_1328 = stk_1328 + 1 & (10 < (int)(stk_1328 + 1)) - 1;
          } while (stk_4c[stk_1328] == 0);
          GameSndPlay((int *)g[G_SYS_SOUNDS],pi5[0x1007],pi5[0x1008],0);
        }
        if (((uint32_t)sounds & 0xff0) != 0) {
          stk_133c = i2 + 1;
          b3 = true;
        }
      }
      pi14 = g;
      if ((sounds != (int *)0x0) || (stk_12d8 != 0)) {
        stk_1340 = 0;
      }
      stk_1340 = stk_1340 + 1;
      if (((g[G_DEMO_MODE_TITLE_WAITTIME] < stk_1340) && (g[G_DEMO_MODE_TITLE_WAITTIME] != -1)) && (0 < g[G_NUM_CHARS])) {
        g[G_DEMO_MODE] = 1;
        pi14[0x74f1] = 0;
        stk_1328 = 1;
        b3 = true;
        stk_133c = 1;
      }
      if ((stk_1314 == 0x3b) || (sounds = (int *)ShowInfoNow_0, ShowInfoNow_0 != 0)) {
        stk_12cc = (uint32_t)(stk_12cc == 0);
        stk_12d8 = 1;
        u15 = stk_12dc;
        if ((stk_12cc == 1) || (u15 = stk_12e4, stk_12cc == 0)) {
          stk_12c8 = u15;
        }
        ShowInfoNow_0 = 0;
      }
      if ((b3) && (stk_1350 == -1)) {
        if (g[G_DEMO_MODE] == 0) {
          sounds = (int *)g[G_SYS_SOUNDS];
          GameSndPlay(sounds,pi5[0x1009],pi5[0x100a],0);
        }
        if (stk_1328 == 9) {
          OptionsScreen();
          W_Cls(0);
          BGArrayReset(g[0x62ce]);
          stk_1348 = 0;
          stk_134c = stk_1350;
          stk_1344 = 0;
          b3 = false;
          b4 = false;
        }
      }
      if (stk_1314 == 1) {
        stk_1328 = 10;
        b3 = true;
      }
      if (stk_1314 == 0x58) {
        ScreenSnap();
      }
      i2 = 0;
      stk_1324 = 0;
      if (stk_1328 < 0x80000000) {
        do {
          if (stk_4c[i2] != 0) {
            stk_1324 = stk_1324 + 1;
          }
          i2 = i2 + 1;
        } while (i2 <= (int)stk_1328);
      }
      if (keyflag[0x10] != 0) {
        ErrorExitM("%i",stk_1324,sounds,sounds);
      }
      i2 = pi5[0x1016];
      i9 = 1;
      do {
        i18 = (stk_1324 + -1) * i2 - stk_1334;
        if ((pi5[0x1071] + -1) * i2 < i18) {
          stk_1334 = stk_1334 + i2;
        }
        if (i18 < 0) {
          stk_1334 = stk_1334 - i2;
        }
        i9 = i9 + -1;
      } while (-1 < i9);
      if (stk_1330 < stk_1334) {
        i2 = (stk_1334 - stk_1330) / 5 + 1;
L_080a0b06:
        stk_1330 = i2 + stk_1330;
      }
      else if (stk_1334 < stk_1330) {
        i2 = (stk_1334 - stk_1330) / 5 + -1;
        goto L_080a0b06;
      }
      if ((ABS((double)(stk_1334 - stk_1330)) <= 2.0) || (stk_1344 == 0)) {
        stk_1330 = stk_1334;
      }
      if (stk_12d8 != 0) {
        if (stk_12ec != stk_12c8) {
          stk_12d4 = (uint32_t)((int)stk_12ec < (int)stk_12c8) * 2 + -1;
          stk_12ec = (int)(stk_12c8 - stk_12ec) / 0xc + stk_12d4 * 5 + stk_12ec;
          if (((int)(stk_12d4 * (stk_12c8 - stk_12ec)) < 1) &&
             (stk_12ec = stk_12c8, stk_12cc == 0)) {
            stk_12d8 = 0;
          }
        }
        stk_12d0 = (float80)(int)(stk_12ec - stk_12e4) / (float80)(int)(stk_12dc - stk_12e4);
      }
      BGArrayMove((int *)g[0x62ce],0.0,0.0);
      BGArrayUpdate(g[0x62ce]);
      i2 = *pi1;
      if ((0 < i2) && (stk_1348 == 0)) {
        i2 = (stk_1344 << 8) / i2;
        MasterPalMul(i2,i2,i2);
        i2 = *pi1;
      }
      if (stk_1344 == i2) {
        stk_1348 = 1;
      }
      if ((0 < pi5[0x1006]) && (stk_1348 == 2)) {
        u15 = 0x100 - ((stk_1344 - stk_134c) * 0x100) / pi5[0x1006];
        u15 = u15 & 0xffffffffU - ((int)u15 >> 0x1f);
        MasterPalMul(u15,u15,u15);
      }
      if (g[0x7307] == 0) {
        MasterPalProcessChanges();
        BGArrayDrawLayer(g[0x62ce],0);
        u15 = 0;
        W_Define(0,pi5[0x100e] - pi5[0x106f],V_Width - 1,
                 pi5[0x1070] + pi5[0x100e] + (pi5[0x1071] + -1) * pi5[0x1016]);
        stk_1324 = 0;
        stk_1398 = stk_4c;
        do {
          if (*stk_1398 != 0) {
            i2 = pi5[0x100d];
            if ((u15 & 1) == 0) {
              i9 = -0x5b - i2;
            }
            else {
              i9 = 0x199 - i2;
            }
            stk_132c = (int)X87_FIST32((float80)i2 + (float80)i9 * stk_12d0);
            i2 = (stk_1324 * pi5[0x1016] + pi5[0x100e]) - stk_1330;
            if ((u15 == stk_1328) && (g[G_DEMO_MODE] == 0)) {
              i9 = stk_1344 * 2;
              if (i9 % 0x40 < 0x20) {
                i9 = i9 % 0x20 + 0x10;
              }
              else {
                i9 = 0x2f - i9 % 0x20;
              }
              if ((pi5[0x1072] != 0) && (stk_1348 == 1)) {
                W_BoxFillTransAdd16(stk_132c + pi5[0x1073],i2 + pi5[0x1074],
                                    stk_132c + pi5[0x1075],i2 + pi5[0x1076],
                                    (i9 - (i9 >> 0x1f) >> 4) << ((uint8_t)_rgb_r_shift_16 & 0x1f)
                                    | (i9 >> 2) << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                                    (i9 >> 3) << ((uint8_t)_rgb_b_shift_16 & 0x1f));
              }
              if (pi5[0x1012] == -1) {
                V_FontDrawCenter((char *)*stk_1398,(int *)g[0x413b],stk_132c,i2,
                                 0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                                 0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                                 0x1f << ((uint8_t)_rgb_b_shift_16 & 0x1f));
              }
              else {
                i9 = pi5[0x1014];
                i18 = pi5[0x1013];
                sounds = (int *)g[pi5[0x1012] + 0x62c3];
                pc25 = (char *)*stk_1398;
L_080a1019:
                V_FontDrawAlignBank(pc25,sounds,stk_132c,i2,i18,i9);
              }
            }
            else {
              if (pi5[0x100f] != -1) {
                i9 = pi5[0x1011];
                i18 = pi5[0x1010];
                sounds = (int *)g[pi5[0x100f] + 0x62c3];
                pc25 = (char *)*stk_1398;
                goto L_080a1019;
              }
              V_FontDrawCenter((char *)*stk_1398,(int *)g[0x413b],stk_132c,i2,
                               0x10 << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                               0x20 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                               0x10 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
            }
            stk_1324 = stk_1324 + 1;
          }
          u15 = u15 + 1;
          stk_1398 = stk_1398 + 1;
        } while ((int)u15 < 0xb);
        W_Define(0,0,V_Width - 1,V_Height - 1);
        u16 = stk_12ec;
        u15 = stk_12f0;
        if (stk_12d8 != 0) {
          i23 = stk_12f0 + stk_12fc[0];
          i20 = stk_12ec + stk_12fc[1];
          u12 = 10 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x1d << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                   0x15 << ((uint8_t)_rgb_b_shift_16 & 0x1f);
          u21 = 8 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x18 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                   0x12 << ((uint8_t)_rgb_b_shift_16 & 0x1f);
          W_Define(stk_12f0,stk_12ec,i23 - 1U,i20 - 1U);
          i9 = i20 + -3;
          u8 = i23 - 3;
          i2 = u16 + 2;
          u13 = u15 + 2;
          W_BoxFillTransAdd16_B50(u13,i2,u8,i9,8 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
          i18 = i20 + -2;
          i19 = i23 + -2;
          i17 = u16 + 1;
          i24 = u15 + 1;
          W_Box(i24,i17,i19,i18,u12);
          W_Box(u13,i2,u8,i9,u21);
          W_Line((float80)i24,(float80)(int)u16,(float80)i19,(float80)(int)u16,u21);
          f2 = (float80)(int)(i20 - 1U);
          W_Line((float80)i24,f2,(float80)i19,f2,u21);
          W_Line((float80)(int)u15,(float80)i17,(float80)(int)u15,(float80)i18,u21);
          f2 = (float80)(int)(i23 - 1U);
          W_Line(f2,(float80)i17,f2,(float80)i18,u21);
          W_PutPixel(i24,i17,u21);
          W_PutPixel(i19,i17,u21);
          W_PutPixel(i24,i18,u21);
          W_PutPixel(i19,i18,u21);
          W_PutPixel(u13,i2,u12);
          W_PutPixel(u8,i2,u12);
          W_PutPixel(u13,i9,u12);
          W_PutPixel(u8,i9,u12);
          W_PutPixel(u15 + 3,u16 + 3,u21);
          W_PutPixel(i23 + -4,u16 + 3,u21);
          W_PutPixel(u15 + 3,i20 + -4,u21);
          W_PutPixel(i23 + -4,i20 + -4,u21);
          InfoTextDraw((char *)stk_12f4,stk_12f0 + 10,stk_12ec + 8);
          W_Define(0,0,V_Width - 1,V_Height - 1);
        }
        i2 = V_Height + -2;
        if ((stk_1348 == 0) && (i9 = *pi1, 0 < i9)) {
          i18 = i9 - stk_1344;
L_080a13ee:
          i2 = i2 + (i18 * 10) / i9;
        }
        else if ((stk_1348 == 2) && (stk_134c < stk_1350)) {
          i18 = stk_1344 - stk_134c;
          i9 = stk_1350 - stk_134c;
          goto L_080a13ee;
        }
        W_BoxFillTransAdd16_B50
                  (0,i2 + -5,V_Width - 1,i2 + 1,8 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
        if ((b3) && (g[G_DEMO_MODE] != 0)) {
          V_FontDrawRight("Loading demo",(int *)g[0x413a],V_Width + -4,i2,
                          0x18 << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                          0x30 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                          0x18 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
        }
        else {
          V_FontWrite((int *)g[0x413a],2,i2,
                      0x18 << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                      0x30 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                      0x18 << ((uint8_t)_rgb_b_shift_16 & 0x1f),"Beta %i.%02i.%02i",MUGENDATE_Y,
                      MUGENDATE_M,MUGENDATE_D);
          V_FontDrawRight("(c) Elecbyte 2002",(int *)g[0x413a],V_Width + -3,i2,
                          0x18 << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                          0x30 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                          0x18 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
          stk_1304 = (int)X87_FIST32(stk_12d0 * 18.0 + (float80)i2);
          V_FontDrawCenter("Press F1 for info",(int *)g[0x413a],V_Width / 2 + -1,stk_1304,
                           0x18 << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                           0x30 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                           0x18 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
          stk_1304 = (int)X87_FIST32((float)(i2 + 0x12) - stk_12d0 * 18.0);
          V_FontDrawCenter("Press F1 to continue",(int *)g[0x413a],V_Width / 2 + -1,stk_1304,
                           0x18 << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                           0x30 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                           0x18 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
        }
        if (g[0x74e6] != 0) {
          W_BoxFillTransAdd16_B50(0,0,V_Width - 1,6,0x18 << ((uint8_t)_rgb_r_shift_16 & 0x1f));
          V_FontDrawCenter("The beta period for this version of M.U.G.E.N has ended",
                           (int *)g[0x413a],V_Width / 2,5,
                           0x18 << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                           0x30 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                           0x18 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
        }
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
      if (((b3) && (stk_1350 == -1)) && (stk_1348 == 1)) {
        stk_134c = stk_1344;
        stk_1348 = 2;
        stk_1350 = stk_1344 + pi5[0x1006];
      }
      stk_1344 = stk_1344 + 1;
      if (b4) break;
      if ((stk_1350 != -1) && (stk_1350 < stk_1344)) {
        b4 = true;
      }
    } while (stk_1314 != 1);
  }
  FrameSkipReset();
  PalGrpClear();
  pi1 = g;
  g[0x33b5] = stk_1328;
  pi1[0x33b6] = stk_133c + -1;
  return;
}
#undef stk_1398
#undef stk_1350
#undef stk_134c
#undef stk_1348
#undef stk_1344
#undef stk_1340
#undef stk_133c
#undef stk_1334
#undef stk_1330
#undef stk_132c
#undef stk_1328
#undef stk_1324
#undef stk_131c
#undef stk_1318
#undef stk_1314
#undef stk_1310
#undef stk_130c
#undef stk_1308
#undef stk_1304
#undef stk_1300
#undef stk_12fe
#undef stk_12fc
#undef stk_12f4
#undef stk_12f0
#undef stk_12ec
#undef stk_12e8
#undef stk_12e4
#undef stk_12e0
#undef stk_12dc
#undef stk_12d8
#undef stk_12d4
#undef stk_12d0
#undef stk_12cc
#undef stk_12c8
#undef stk_12bc
#undef stk_2bc
#undef stk_1fc
#undef stk_4c

/* OptionsScreen @ 0x080a1830, 8811 bytes
 *
 * The options menu ("OPTIONS"): Difficulty, Time Limit, Game Speed
 * (Slow/Fast n), Wav Volume, Midi Volume, Input Config (Key Config, Joystick
 * Config, Joystick Type), Team Mode Config (1P VS Team Advantage, what
 * happens "If player KOed": team loses or AI keeps fighting), Default
 * Values, Load/Save ("Options Loaded", "Options Saved") and Return to Main
 * Menu. Saving writes mugen.cfg (GameSaveOptions).
 *
 * Globals read: backbuffer, input_p1_joystick_type_1ce34,
 *               input_p2_joystick_type_1ce38, sys_sounds, speed_flag,
 *               vretrace
 * Globals written: options_team_1vs2life
 * Calls: V_SetBuf, TimerSetSyncFPS, KBBufferClear, PadPoll, PadBufClear,
 *        UInpRefreshFlags, UInpBufClear, BGArrayReset, FrameSkipReset,
 *        BGMPoll, KBPoll, KBkbhit, KBgetchraw, PadHit, PadGet,
 *        GlobalInputUpdate, UInpHit, UInpGet, KBIMenuGetKey,
 *        PRSprArrayClear, GameSndPlay, GameResetOptions, GameLoadOptions,
 *        GameSaveOptions, ...
 * C library: memcpy, sprintf
 * Called by: ModeSelect
 * Messages:
 *   "Time Limit"
 *   "Game Speed"
 *   "Wav Volume"
 *   "Midi Volume"
 *   "Input Config"
 *   "Team Mode Config"
 *
 * Elecbyte file: src/mugen/menus.c
 * Note: 2 accesses to parts of a variable are written as sized accesses.
 * Note: removed pointer casts from 7 case labels; switch operand cast to int
 * Note: 3 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x200 bytes,
 *       50 variables), because their address is taken.
 */
void OptionsScreen(void)

{
  uint8_t b1;
  bool b2;
  bool b3;
  bool b4;
  bool b5;
  int *pi6;
  uint32_t u7;
  bool b8;
  uint32_t stale_var;
  uint32_t stale_var_00;
  uint32_t stale_var_01;
  int *font;
  int *font2;
  uint8_t b11;
  uint8_t b12;
  uint8_t b13;
  int *stale_ECX;
  uint32_t *pu16;
  uint32_t *pu17;
  uint32_t u18;
  uint32_t u19;
  int *stale_EDX;
  int *stale_EDX_00;
  int *pi20;
  int i21;
  int *pi22;
  uint32_t *pu23;
  uint32_t *pu24;
  uint32_t u25;
  bool b26;
  bool b27;
  bool b28;
  char *text;
  uint32_t u30;
  uint32_t u31;
  int i32;
  size_t n;
  uint8_t b14;
  uint8_t b15;
  unsigned char frame[0x200] __attribute__((aligned(16)));
#define stk_1f4 (*(uint8_t *)(frame + 0xc))
#define stk_1e8 (*(int *)(frame + 0x18))
#define stk_1e4 (*(int *)(frame + 0x1c))
#define stk_1e0 (*(int *)(frame + 0x20))
#define stk_1dc (*(int *)(frame + 0x24))
#define stk_1b0 (*(int *)(frame + 0x50))
#define stk_1ac (*(int *)(frame + 0x54))
#define stk_1a8 (*(uint32_t *)(frame + 0x58))
#define stk_194 (*(uint32_t *)(frame + 0x6c))
#define stk_188 (*(int *)(frame + 0x78))
#define stk_184 (*(int *)(frame + 0x7c))
#define stk_17c (*(uint32_t *)(frame + 0x84))
#define stk_178 (*(int *)(frame + 0x88))
#define stk_164 (*(int *)(frame + 0x9c))
#define stk_160 (*(int *)(frame + 0xa0))
#define stk_15c (*(int *)(frame + 0xa4))
#define stk_158 (*(int *)(frame + 0xa8))
#define stk_154 (*(int *)(frame + 0xac))
#define stk_150 (*(int **)(frame + 0xb0))
#define stk_14c (*(uint32_t (*)[4])(frame + 0xb4))
#define stk_13c (*(int *)(frame + 0xc4))
#define stk_138 (*(int *)(frame + 0xc8))
#define stk_134 (*(int **)(frame + 0xcc))
#define stk_130 (*(int **)(frame + 0xd0))
#define stk_12c (*(uint32_t *)(frame + 0xd4))
#define stk_120 (*(int *)(frame + 0xe0))
#define stk_10c (*(char **(*)[4])(frame + 0xf4))
#define stk_fc (*(uint32_t *)(frame + 0x104))
#define stk_f8 (*(int *)(frame + 0x108))
#define stk_f7 (*(uint32_t *)(frame + 0x109))
#define stk_7c (*(char **)(frame + 0x184))
#define stk_78 (*(char **)(frame + 0x188))
#define stk_74 (*(char **)(frame + 0x18c))
#define stk_70 (*(char **)(frame + 0x190))
#define stk_6c (*(char **)(frame + 0x194))
#define stk_68 (*(char **)(frame + 0x198))
#define stk_64 (*(char **)(frame + 0x19c))
#define stk_60 (*(char **)(frame + 0x1a0))
#define stk_5c (*(char **)(frame + 0x1a4))
#define stk_4c (*(char **)(frame + 0x1b4))
#define stk_48 (*(uint8_t **)(frame + 0x1b8))
#define stk_44 (*(char **)(frame + 0x1bc))
#define stk_40 (*(char **)(frame + 0x1c0))
#define stk_3c (*(char **)(frame + 0x1c4))
#define stk_38 (*(char **)(frame + 0x1c8))
#define stk_34 (*(char **)(frame + 0x1cc))
#define stk_30 (*(char **)(frame + 0x1d0))
#define stk_2c (*(char **)(frame + 0x1d4))
#define stk_28 (*(char **)(frame + 0x1d8))
#define stk_24 (*(char **)(frame + 0x1dc))
  
  pi6 = g;
  b11 = (uint8_t)_rgb_r_shift_16;
  b1 = (uint8_t)_rgb_g_shift_16;
  b12 = (uint8_t)_rgb_b_shift_16;
  u18 = 8 << (b11 & 0x1f) | 0xc << (b1 & 0x1f) | 4 << (b12 & 0x1f);
  stk_14c[0] = 0;
  stk_134 = g + 0x733b;
  stk_14c[1] = 0;
  stk_178 = 0;
  b3 = false;
  b5 = false;
  b4 = false;
  stk_1a8 = 0;
  stk_1b0 = 1;
  b2 = false;
  stk_130 = g + 0x7348;
  V_SetBuf((int *)g[G_BACKBUFFER],0);
  TimerSetSyncFPS(0x3c);
  KBBufferClear();
  KBRepeat = 1;
  PadPoll();
  PadBufClear();
  UInpRefreshFlags();
  UInpBufClear();
  BGArrayReset(g[0x62d0]);
  stk_4c = "Difficulty";
  g[0x79a6] = 0;
  stk_10c[0] = &stk_4c;
  stk_10c[2] = &stk_6c;
  stk_10c[1] = &stk_7c;
  stk_48 = &str_life_d876;
  stk_44 = "Time Limit";
  stk_40 = "Game Speed";
  stk_3c = "Wav Volume";
  stk_38 = "Midi Volume";
  stk_34 = "Input Config";
  stk_30 = "Team Mode Config";
  stk_28 = "Default Values";
  stk_2c = "Load/Save";
  stk_24 = "Return to Main Menu";
  stk_6c = "Key Config";
  stk_68 = "Joystick Type";
  stk_64 = "Joystick Config";
  stk_60 = "Default Values";
  stk_5c = "Return to Options";
  stk_7c = "1P VS Team Advantage";
  stk_78 = "If player KOed";
  stk_74 = "Default Values";
  stk_70 = "Return to Options";
  FrameSkipReset();
L_080a1af0:
  i21 = 0;
  BGMPoll(g + 0x6efa);
  stk_13c = 0;
  stk_138 = 0;
  PadPoll();
  KBPoll();
  b8 = KBkbhit();
  if (ZEXT8(b8) != 0) {
    stk_13c = KBgetchraw();
  }
  b8 = PadHit();
  if (ZEXT8(b8) != 0) {
    stk_138 = PadGet();
  }
  GlobalInputUpdate();
  b8 = UInpHit();
  if (ZEXT8(b8) != 0) {
    i21 = UInpGet();
  }
  if (b2) {
    i21 = 0;
    stk_13c = 0;
    stk_138 = 0;
    b2 = false;
  }
  KBIMenuGetKey(stk_14c + 2,i21,(int)&stk_134,2);
  u25 = stk_14c[3];
  u19 = stk_14c[2];
  PRSprArrayClear((int *)g[0x413d]);
  if (((g[G_INPUT_P1_JOYSTICK_TYPE_1CE34] == 0x16) || (g[G_INPUT_P2_JOYSTICK_TYPE_1CE38] == 0x16)) && (stk_138 == 0xb)) {
    stk_13c = 1;
    stk_138 = 0;
  }
  if (stk_1a8 == 1) {
    stk_1ac = 4;
    stk_158 = 0x31;
    stk_15c = 0xdc;
    stk_160 = 0x50;
    stk_164 = 0xdc;
L_080a1cf8:
    stk_1b0 = 1;
  }
  else if (stk_1a8 < 2) {
    if (stk_1a8 == 0) {
      stk_1ac = 0xb;
      stk_158 = 0x45;
      stk_15c = 0xb4;
      stk_160 = 0xa9;
      stk_164 = 0xb4;
      goto L_080a1cf8;
    }
  }
  else if (stk_1a8 == 2) {
    stk_1ac = 5;
    stk_158 = 0x1d;
    stk_15c = 0x104;
    stk_160 = 0x69;
    stk_164 = 0x82;
    stk_1b0 = 2;
  }
  if ((!b3) || ((stk_14c[u25] == 8 && (stk_1a8 == 0)))) {
    if ((u19 & 1) != 0) {
      u30 = stk_14c[u25];
      stk_14c[u25] = u30 - 1;
      if ((int)(u30 - 1) < 0) {
        stk_14c[u25] = stk_1ac - 1;
      }
      b4 = false;
      b3 = false;
      GameSndPlay((int *)g[G_SYS_SOUNDS],pi6[0x1079],pi6[0x107a],0);
    }
    if ((u19 & 4) != 0) {
      stk_14c[u25] = stk_14c[u25] + 1 & (stk_1ac <= (int)(stk_14c[u25] + 1)) - 1;
      b4 = false;
      b3 = false;
      GameSndPlay((int *)g[G_SYS_SOUNDS],pi6[0x1079],pi6[0x107a],0);
    }
  }
  if (stk_1b0 == 1) {
    stk_14c[1 - u25] = stk_14c[u25];
  }
  b26 = (u19 & 0xff0) != 0;
  stk_194 = (uint32_t)((u19 & 8) != 0);
  b8 = (u19 & 2) != 0;
  if (b3) {
    if ((stk_194 != 0) || (stk_13c == 1)) {
      b5 = false;
    }
    if (b8) {
      b5 = true;
    }
    if ((b26) || (stk_13c == 1)) {
      b4 = true;
    }
    b8 = false;
    stk_194 = 0;
    b26 = false;
    if (stk_13c == 1) {
      stk_13c = 0;
    }
  }
  if (stk_1a8 == 0) {
    u19 = g[stk_14c[u25] + 0x799e];
    switch(stk_14c[u25]) {
    case 0:
      if ((stk_194 != 0) && (1 < (int)u19)) {
        u19 = u19 - 1;
      }
      if (b8) {
        b28 = SBORROW4(u19,7);
        b27 = (int)(u19 - 7) < 0;
        b8 = u19 == 7;
L_080a2018:
        if (b8 || b28 != b27) {
          u19 = u19 + 1;
        }
      }
      break;
    case 1:
      if ((stk_194 != 0) && (0x1e < (int)u19)) {
        u19 = u19 - 10;
      }
      if ((b8) && ((int)u19 < 300)) {
        u19 = u19 + 10;
      }
      break;
    case 2:
      if (((stk_194 == 0) || ((int)u19 < 0x15)) || (u19 == 99)) {
        if ((stk_194 == 0) || (u19 != 99)) {
          if ((stk_194 != 0) && (u19 == 0xffffffff)) {
            u19 = 99;
          }
        }
        else {
          u19 = 0x50;
        }
      }
      else {
        u19 = u19 - 0x14;
      }
      if (((b8) && ((int)u19 < 0x50)) && (u19 != 0xffffffff)) {
        u19 = u19 + 0x14;
      }
      else if ((b8) && (u19 == 0x50)) {
        u19 = 99;
      }
      else if ((b8) && (u19 == 99)) {
        u19 = 0xffffffff;
      }
      break;
    case 3:
      if ((stk_194 != 0) && (-9 < (int)u19)) {
        u19 = u19 - 1;
      }
      if (b8) {
        b28 = SBORROW4(u19,8);
        b27 = (int)(u19 - 8) < 0;
        b8 = u19 == 8;
        goto L_080a2018;
      }
      break;
    case 4:
    case 5:
      if ((stk_194 != 0) && (0 < (int)u19)) {
        u19 = u19 - 1;
      }
      if (b8) {
        b28 = SBORROW4(u19,99);
        b27 = (int)(u19 - 99) < 0;
        b8 = u19 == 99;
        goto L_080a2018;
      }
      break;
    case 8:
      u19 = u19 & stk_194 - 1;
      if (b8) {
        u19 = 1;
      }
      if ((b3) && (b4)) {
L_080a2066:
        b4 = false;
        b3 = false;
      }
      break;
    case 9:
      if ((b3) && (b4)) {
        if (b5) {
          GameResetOptions();
        }
        goto L_080a2066;
      }
    }
    g[stk_14c[u25] + 0x799e] = u19;
    if (!b3) {
      i21 = stk_13c;
      if (stk_13c == 1) {
        stk_14c[u25] = 10;
        i21 = 1;
        b26 = true;
      }
      if (i21 == 0x3b) {
        stk_14c[u25] = 6;
        b26 = true;
        i21 = stk_13c;
      }
      if (i21 == 0x3c) {
        stk_14c[u25] = 7;
        b26 = true;
      }
    }
    if (!b26) goto L_case_080a210f_a;
    switch(stk_14c[u25]) {
    case 6:
      GameSndPlay((int *)g[G_SYS_SOUNDS],pi6[0x107b],pi6[0x107c],0);
      stk_12c = stk_14c[0];
      stk_120 = stk_14c[1];
      stk_1a8 = 2;
      goto L_080a2196;
    case 7:
      GameSndPlay((int *)g[G_SYS_SOUNDS],pi6[0x107b],pi6[0x107c],0);
      stk_12c = stk_14c[0];
      stk_120 = stk_14c[1];
      stk_1a8 = 1;
L_080a2196:
      stk_14c[1] = 0;
      stk_14c[0] = 0;
      goto L_080a1af0;
    case 8:
      GameSndPlay((int *)g[G_SYS_SOUNDS],pi6[0x107b],pi6[0x107c],0);
      if (g[stk_14c[u25] + 0x799e] == 0) {
        GameLoadOptions();
      }
      else {
        GameSaveOptions();
      }
      b3 = true;
      b2 = true;
    default:
      b26 = false;
      break;
    case 9:
      GameSndPlay((int *)g[G_SYS_SOUNDS],pi6[0x107b],pi6[0x107c],0);
      b3 = true;
      b5 = false;
      b26 = false;
      font = g;
      goto L_080a286d;
    case 10:
      break;
    }
  }
  else if (stk_1a8 == 2) {
    u19 = g[u25 * 5 + stk_14c[u25] + 0x79aa];
    u30 = u19;
    font = g;
    if (stk_14c[u25] == 1) {
      if (stk_194 != 0) {
        u30 = u19 & (u19 != 0) - 1;
      }
      if ((b8) && (u30 == 0)) {
        u30 = 1;
      }
      if (u30 != u19) {
        i21 = 0;
        g[u25 * 5 + stk_14c[u25] + 0x79aa] = u30;
        stk_1dc = 0x1ce30;
        stk_1e0 = 0x1ce30;
        stk_1e4 = 0x1e6a4;
        stk_1e8 = 0x1ce20;
        stk_150 = (int *)0x1;
        do {
          font = g;
          u19 = (uint32_t)(*(int *)(stk_1e4 + 8 + (int)g) != 0);
          *(uint32_t *)(stk_1e8 + 0xc + (int)g) = u19;
          if (u19 == 0) {
            pu23 = (uint32_t *)((int)font + i21 + 0x1cd54);
            for (i32 = 0xd; font = g, i32 != 0; i32 = i32 + -1) {
              *pu23 = 0;
              pu23 = pu23 + 1;
            }
            *(uint32_t *)(stk_1dc + 4 + (int)g) = 0;
            PlayerKeysRemoveZero(i21 + 0x1cd54 + (int)font,0x80);
          }
          else {
            pu23 = (uint32_t *)((int)font + i21 + 0x1cdbc);
            pu24 = (uint32_t *)((int)font + i21 + 0x1cd54);
            for (i32 = 0xd; i32 != 0; i32 = i32 + -1) {
              *pu24 = *pu23;
              pu23 = pu23 + 1;
              pu24 = pu24 + 1;
            }
            *(uint32_t *)((int)g + stk_1e0 + 4) = u30;
          }
          stk_1dc = stk_1dc + 4;
          stk_1e0 = stk_1e0 + 4;
          stk_1e4 = stk_1e4 + 0x14;
          stk_1e8 = stk_1e8 + 4;
          i21 = i21 + 0x34;
          stk_150 = (int *)((int)stk_150 + -1);
        } while (-1 < (int)stk_150);
        if (((g[0x738b] == 0) && (g[0x738c] == 0)) && (PadInstalled != 0)) {
          PadDeInit();
          font = g;
        }
        else {
          font = g;
          if ((g[0x799d] == 0) && (PadInstalled == 0)) {
            i21 = PadInit(g[(g[0x738c] != 0) + 0x738d],(uint32_t)(g[0x738c] != 0));
            font = g;
            if (i21 == 0) {
              g[0x738c] = 0;
              font[0x738b] = 0;
            }
            else {
              GameInputSetup();
              font = g;
            }
          }
        }
      }
    }
    font[u25 * 5 + stk_14c[u25] + 0x79aa] = u30;
    i21 = stk_13c;
    if (stk_13c == 1) {
      stk_14c[1] = 4;
      stk_14c[0] = 4;
      b26 = true;
      i21 = 1;
    }
    if (i21 == 0x3b) {
      stk_14c[1] = 0;
      stk_14c[0] = 0;
      b26 = true;
      i21 = stk_13c;
    }
    if (i21 == 0x3c) {
      stk_14c[1] = 2;
      stk_14c[0] = 2;
      b26 = true;
    }
    if (!b26) goto L_case_080a210f_a;
    u19 = stk_14c[u25];
    if (u19 == 2) {
      if ((g[0x738b] != 0) || (g[0x738c] != 0)) {
        GameSndPlay((int *)g[G_SYS_SOUNDS],pi6[0x107b],pi6[0x107c],0);
        stk_178 = KeyConfigScreen(1,stk_178);
        GameSndPlay((int *)g[G_SYS_SOUNDS],pi6[0x107d],pi6[0x107e],0);
      }
      b26 = false;
      font = g;
      goto L_080a286d;
    }
    if ((int)u19 < 3) {
      if (u19 == 0) {
        GameSndPlay((int *)g[G_SYS_SOUNDS],pi6[0x107b],pi6[0x107c],0);
        stk_178 = KeyConfigScreen(0,stk_178);
        GameSndPlay((int *)g[G_SYS_SOUNDS],pi6[0x107d],pi6[0x107e],0);
        b26 = false;
        font = g;
        goto L_080a286d;
      }
    }
    else {
      if (u19 == 3) {
        GameSndPlay((int *)g[G_SYS_SOUNDS],pi6[0x107b],pi6[0x107c],0);
        font = g;
        g[u25 * 5 + 0x79ab] = 0;
        goto L_080a2813;
      }
      if (u19 == 4) {
        GameSndPlay((int *)g[G_SYS_SOUNDS],pi6[0x107d],pi6[0x107e],0);
        stk_14c[0] = stk_12c;
        stk_14c[1] = stk_120;
        stk_1a8 = 0;
        goto L_080a1af0;
      }
    }
  }
  else if (stk_1a8 == 1) {
    u19 = stk_14c[u25];
    i21 = g[u19 + 0x79b4];
    if (u19 == 0) {
      if ((stk_194 != 0) && (100 < i21)) {
        i21 = i21 + -10;
      }
      if ((b8) && (i21 < 300)) {
        i21 = i21 + 10;
      }
    }
    else if (u19 == 1) {
      if ((stk_194 != 0) && (0 < i21)) {
        i21 = i21 + -1;
      }
      if ((b8) && (i21 < 1)) {
        i21 = i21 + 1;
      }
    }
    g[stk_14c[u25] + 0x79b4] = i21;
    if (stk_13c == 1) {
      stk_14c[u25] = 3;
      b26 = true;
    }
    if (b26) {
      if (stk_14c[u25] == 2) {
        GameSndPlay((int *)g[G_SYS_SOUNDS],pi6[0x107b],pi6[0x107c],0);
        font = g;
        g[G_OPTIONS_TEAM_1VS2LIFE] = 200;
        font[0x79b5] = 0;
L_080a2813:
        b26 = false;
        goto L_080a286d;
      }
      if (stk_14c[u25] == 3) {
        GameSndPlay((int *)g[G_SYS_SOUNDS],pi6[0x107d],pi6[0x107e],0);
        stk_14c[0] = stk_12c;
        stk_1a8 = 0;
        stk_14c[1] = stk_120;
        goto L_080a1af0;
      }
    }
  }
L_case_080a210f_a:
  font = g;
L_080a286d:
  BGArrayMove((int *)font[0x62d0],0.0,0.0);
  BGArrayUpdate(g[0x62d0]);
  if (g[0x7307] == 0) {
    MasterPalProcessChanges();
    BGArrayDrawLayer(g[0x62d0],0);
    i21 = stk_158 + stk_15c;
    W_BoxFillTransSub16(stk_158 - 0xf,0x24,i21 + 0xe,stk_160 + 0x31,
                        0x10 << (b11 & 0x1f) | 0x18 << (b1 & 0x1f) | 8 << (b12 & 0x1f));
    W_BoxFillTransSub16(stk_158 - 0x10U,0x25,stk_158 - 0x10U,stk_160 + 0x30,u18);
    W_BoxFillTransSub16(i21 + 0xfU,0x25,i21 + 0xfU,stk_160 + 0x30,u18);
    W_BoxFillTransSub16(stk_158 - 0xeU,0x23,i21 + 0xdU,0x23,u18);
    W_BoxFillTransSub16(stk_158 - 0xeU,stk_160 + 0x32,i21 + 0xdU,stk_160 + 0x32,u18);
    b13 = (uint8_t)_rgb_r_shift_16;
    b14 = (uint8_t)_rgb_g_shift_16;
    b15 = (uint8_t)_rgb_b_shift_16;
    if (stk_1a8 == 0) {
      u19 = 0x1f << (b13 & 0x1f) | 0x3f << (b14 & 0x1f) | 0x1f << (b15 & 0x1f);
      i32 = 0x14;
      i21 = V_Width / 2;
      font = (int *)g[0x413b];
      text = "OPTIONS";
L_080a2b57:
      V_FontDrawCenter(text,font,i21,i32,u19);
    }
    else {
      if (stk_1a8 == 2) {
        V_FontDrawCenter("INPUT CONFIG",(int *)g[0x413b],V_Width / 2,0x14,
                         0x1f << (b13 & 0x1f) | 0x3f << (b14 & 0x1f) | 0x1f << (b15 & 0x1f)
                        );
        i21 = stk_15c;
        if (stk_15c < 0) {
          i21 = stk_15c + 3;
        }
        V_FontDrawCenter("PLAYER 1",(int *)g[0x413b],(i21 >> 2) + stk_158,0x2f,
                         0x10 << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                         0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                         0x1f << ((uint8_t)_rgb_b_shift_16 & 0x1f));
        u19 = 0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x20 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                 0x10 << ((uint8_t)_rgb_b_shift_16 & 0x1f);
        i32 = 0x2f;
        i21 = stk_15c * 3;
        if (i21 < 0) {
          i21 = i21 + 3;
        }
        i21 = (i21 >> 2) + stk_158;
        font = (int *)g[0x413b];
        text = "PLAYER 2";
        goto L_080a2b57;
      }
      if (stk_1a8 == 1) {
        u19 = 0x1f << (b13 & 0x1f) | 0x3f << (b14 & 0x1f) | 0x1f << (b15 & 0x1f);
        i32 = 0x14;
        i21 = V_Width / 2;
        font = (int *)g[0x413b];
        text = "TEAM MODE CONFIG";
        goto L_080a2b57;
      }
    }
    stk_154 = 0;
    do {
      stk_150 = (int *)0x0;
      stk_184 = 0;
      if (0 < stk_1ac) {
        do {
          stk_188 = stk_158 + (stk_154 * stk_15c) / 2;
          if (stk_1b0 == 2) {
            if (stk_154 == 0) {
              stk_188 = stk_188 + -7;
            }
            else {
              stk_188 = stk_188 + 7;
            }
          }
          stk_1f4 = (uint8_t)_rgb_b_shift_16;
          u19 = 0x18 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x30 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                   0x18 << (stk_1f4 & 0x1f);
          if (stk_1a8 == 0) {
            if ((stk_150 == (int *)0xa) || (stk_150 == (int *)0x8)) {
              stk_184 = stk_184 + 1;
            }
          }
          else if (stk_1a8 == 2) {
            if (((stk_150 == (int *)0x0) || (stk_150 == (int *)0x3)) ||
               (stk_150 == (int *)0x1)) {
              stk_184 = stk_184 + 1;
            }
          }
          else if ((stk_1a8 == 1) && (stk_150 == (int *)0x3)) {
            stk_184 = stk_184 + 1;
          }
          i21 = ((int)stk_150 + stk_184) * 0xd;
          font = (int *)(i21 + 0x32);
          if (stk_150 == (int *)stk_14c[stk_154]) {
            i32 = stk_178 * 4;
            if (i32 % 0x80 < 0x40) {
              i32 = i32 % 0x40 + 0x20;
            }
            else {
              i32 = 0x5f - i32 % 0x40;
            }
            stk_17c = (i32 >> 3) << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                        (i32 >> 2) << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                        (i32 >> 3) << (stk_1f4 & 0x1f);
            W_BoxFillTransAdd16(stk_188 - 5,i21 + 0x28,
                                stk_15c / (int)((stk_1b0 != 1) + 1) + 4 + stk_188,
                                i21 + 0x35,stk_17c);
            stk_1f4 = (uint8_t)_rgb_b_shift_16;
            u19 = 0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f)
                     | 0x1f << (stk_1f4 & 0x1f);
          }
          if (((stk_1a8 == 2) && (stk_150 == (int *)0x2)) &&
             ((g[0x738b] == 0 && (g[0x738c] == 0)))) {
            stk_1f4 = (uint8_t)_rgb_b_shift_16;
            u19 = 0x12 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x20 << ((uint8_t)_rgb_g_shift_16 & 0x1f)
                     | 0x10 << (stk_1f4 & 0x1f);
          }
          V_FontDraw(stk_10c[stk_1a8][(int)stk_150],(int *)g[0x413b],stk_188,(int)font,
                     u19);
          stk_fc = stk_fc & 0xffffff00;
          u7 = stk_f7;
          font2 = g;
          if (stk_1a8 != 0) {
            if (stk_1a8 == 2) {
              i21 = g[(int)stk_150 + stk_154 * 5 + 0x79aa];
              if (stk_150 == (int *)0x1) {
                if (i21 == 0) {
                  n = 9;
                  text = "Disabled";
L_080a3134:
                  memcpy(&stk_fc,text,n);
                }
                else if (i21 == 1) {
                  stk_fc = 0x6f747541;
                  stk_f8 = (uint32_t)stk_f7 << 8;
                }
                else if (i21 - 4U < 5) {
                  sprintf((char *)&stk_fc,"%i button",i21,stale_ECX);
                }
                else {
                  if (i21 == 0x14) {
                    n = 0xb;
                    text = "Sidewinder";
                    goto L_080a3134;
                  }
                  if (i21 == 0x15) {
                    stk_fc = 0x53454e53;
                    stk_f8 = 0x79654b;
                  }
                  else {
                    if (i21 == 0x16) {
                      stk_fc = 0x20585350;
                    }
                    else {
                      if (i21 != 0x17) goto L_080a318f;
                      stk_fc = 0x2034364e;
                    }
                    stk_f8 = 0x646150;
                  }
                }
              }
L_080a318f:
              if ((g[stk_154 + 0x738b] == 0) && (i21 != 0)) {
                u19 = 0x12 << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                         0x20 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                         0x10 << ((uint8_t)_rgb_b_shift_16 & 0x1f);
              }
            }
            else if (stk_1a8 == 1) {
              pi22 = (int *)g[(int)(stk_150 + 0x1e6d)];
              if (stk_150 == (int *)0x0) {
                text = "%i%%";
                pu17 = &stk_fc;
                goto L_080a2f6f;
              }
              if (stk_150 == (int *)0x1) {
                font2 = (int *)0x0;
                pi20 = stale_EDX;
                if (pi22 == (int *)0x0) {
                  font2 = (int *)sprintf((char *)&stk_fc,"Team loses",stale_ECX,stale_ECX)
                  ;
                  pi20 = stale_EDX_00;
                }
                if (pi22 == (int *)0x1) {
                  font2 = (int *)sprintf((char *)&stk_fc,"AI keeps fighting",pi20,pi20);
                }
                if (pi22 == (int *)0x2) {
                  text = "Control AI";
                  pu17 = &stk_fc;
                  pi22 = font2;
                  goto L_080a2f6f;
                }
              }
            }
            goto L_case_080a2ecf_6;
          }
          pi22 = (int *)g[(int)stk_150 + 0x799e];
          switch((int)stk_150) {
          case 0x0:
            if ((int)pi22 < 3) {
              stk_fc = 0x79736145;
              stk_f8 = (uint32_t)u7 << 8;
            }
            else if ((int)pi22 < 6) {
              stk_fc = 0x6964654d;
              stk_f8 = CONCAT13((*(uint8_t *)((char *)&stk_f7 + 2)),0x6d75);
            }
            else {
              stk_fc = 0x64726148;
              stk_f8 = (uint32_t)u7 << 8;
            }
            text = " %i";
            pu17 = &stk_fc;
            do {
              pu16 = pu17;
              pu17 = pu16 + 1;
              u30 = *pu16 + 0xfefefeff & (*pu16 ^ 0xffffffff);
              u31 = u30 & 0x80808080;
            } while (u31 == 0);
            if ((u30 & 0x8080) == 0) {
              u31 = u31 >> 0x10;
              pu17 = (uint32_t *)((int)pu16 + 6);
            }
            pu17 = (uint32_t *)((int)pu17 + (-3 - (uint32_t)CARRY1((uint8_t)u31,(uint8_t)u31)));
            font2 = stk_150;
            goto L_080a2f6f;
          case 0x1:
            text = "%i%%";
            pu17 = &stk_fc;
            font2 = font;
L_080a2f6f:
            sprintf((char *)pu17,text,pi22,font2);
            break;
          case 0x2:
            if (pi22 != (int *)0xffffffff) {
              text = "%i";
              pu17 = &stk_fc;
              goto L_080a2f6f;
            }
            stk_fc = 0x656e6f4e;
            stk_f8 = (uint32_t)u7 << 8;
            break;
          case 0x3:
            if (pi22 != (int *)0x0) {
              if ((int)pi22 < 1) {
                pi22 = (int *)-(int)pi22;
                text = "Slow %i";
                pu17 = &stk_fc;
                font2 = stale_EDX;
              }
              else {
                text = "Fast %i";
                pu17 = &stk_fc;
                font2 = stale_ECX;
              }
              goto L_080a2f6f;
            }
            stk_fc = 0x6d726f4e;
            stk_f8 = CONCAT13((*(uint8_t *)((char *)&stk_f7 + 2)),0x6c61);
            break;
          case 0x4:
          case 0x5:
            if (pi22 == (int *)0x0) {
              stk_fc = 0x66664f;
            }
            else {
              if (pi22 != (int *)0x64) {
                text = "%i";
                pu17 = &stk_fc;
                font2 = stk_150;
                goto L_080a2f6f;
              }
              stk_fc = 0x78614d;
            }
            break;
          case 0x8:
            if (pi22 == (int *)0x0) {
              stk_fc = 0x64616f4c;
              stk_f8 = (uint32_t)u7 << 8;
            }
            else {
              stk_fc = 0x65766153;
              stk_f8 = (uint32_t)u7 << 8;
            }
          }
L_case_080a2ecf_6:
          i21 = stk_188 + stk_164;
          V_FontDrawRight((char *)&stk_fc,(int *)g[0x413b],i21,(int)font,u19);
          b13 = (uint8_t)_rgb_r_shift_16;
          b14 = (uint8_t)_rgb_g_shift_16;
          b15 = (uint8_t)_rgb_b_shift_16;
          if (stk_1a8 == 0) {
            if (stk_150 == (int *)0x6) {
              V_FontDrawRight("(F1)",(int *)g[0x413b],i21,(int)font,
                              0x1f << (b13 & 0x1f) | 0x3f << (b14 & 0x1f) |
                              0x10 << (b15 & 0x1f));
            }
            if (stk_150 == (int *)0x7) {
              V_FontDrawRight("(F2)",(int *)g[0x413b],i21,(int)font,
                              0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                              0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                              0x10 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
            }
            if (stk_150 == (int *)0xa) {
              u19 = 0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                       0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                       0x10 << ((uint8_t)_rgb_b_shift_16 & 0x1f);
              font2 = (int *)g[0x413b];
              goto L_080a3549;
            }
          }
          else if ((stk_1a8 == 2) && (stk_154 == 1)) {
            if (stk_150 == (int *)0x0) {
              V_FontDrawRight("(F1)",(int *)g[0x413b],i21,(int)font,
                              0x1f << (b13 & 0x1f) | 0x3f << (b14 & 0x1f) |
                              0x10 << (b15 & 0x1f));
            }
            if (stk_150 == (int *)0x2) {
              V_FontDrawRight("(F2)",(int *)g[0x413b],i21,(int)font,
                              0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                              0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                              0x10 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
            }
            if (stk_150 == (int *)0x4) {
              u19 = 0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                       0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                       0x10 << ((uint8_t)_rgb_b_shift_16 & 0x1f);
              font2 = (int *)g[0x413b];
L_080a3549:
              V_FontDrawRight("(Esc)",font2,stk_188 + stk_164,(int)font,u19);
            }
          }
          else if ((stk_1a8 == 1) && (stk_150 == (int *)0x3)) {
            u19 = 0x1f << (b13 & 0x1f) | 0x3f << (b14 & 0x1f) | 0x10 << (b15 & 0x1f);
            font2 = (int *)g[0x413b];
            goto L_080a3549;
          }
          stk_150 = (int *)((int)stk_150 + 1);
        } while ((int)stk_150 < stk_1ac);
      }
    } while ((stk_1b0 != 1) && (stk_154 = stk_154 + 1, stk_154 < 2));
    if (b3) {
      W_Line(100.0,99.0,(float)(V_Width + -100),99.0,
             7 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0xe << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
             0xc << ((uint8_t)_rgb_b_shift_16 & 0x1f));
      W_Line(100.0,131.0,(float)(V_Width + -100),131.0,
             7 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0xe << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
             0xc << ((uint8_t)_rgb_b_shift_16 & 0x1f));
      W_Line(99.0,100.0,99.0,130.0,
             7 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0xe << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
             0xc << ((uint8_t)_rgb_b_shift_16 & 0x1f));
      W_Line((float)(V_Width + -99),100.0,(float)(V_Width + -99),130.0,
             7 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0xe << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
             0xc << ((uint8_t)_rgb_b_shift_16 & 0x1f));
      W_BoxFill(100,100,V_Width + -100,0x82,
                10 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x15 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                0x11 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
      b14 = (uint8_t)_rgb_r_shift_16;
      b15 = (uint8_t)_rgb_g_shift_16;
      b13 = (uint8_t)_rgb_b_shift_16;
      if (stk_14c[u25] == 9) {
        if (b5) {
          stk_150 = (int *)(0x18 << (b14 & 0x1f) | 0x30 << (b15 & 0x1f) |
                             0x18 << (b13 & 0x1f));
          u31 = 0xb4;
          u25 = 0x1f << (b14 & 0x1f) | 0x3f << (b15 & 0x1f);
          u30 = 0xa2;
          u19 = 0x1f << (b13 & 0x1f);
        }
        else {
          stk_150 = (int *)(0x1f << (b14 & 0x1f) | 0x3f << (b15 & 0x1f) |
                             0x1f << (b13 & 0x1f));
          u25 = 0x18 << (b14 & 0x1f) | 0x30 << (b15 & 0x1f);
          u31 = 0x9d;
          u19 = 0x18 << (b13 & 0x1f);
          u30 = 0x8e;
        }
        W_BoxFillTransAdd16(u30,0x73,u31,0x7f,stk_17c);
        V_FontDrawCenter("Confirm",(int *)g[0x413b],0x9f,0x70,
                         0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                         0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                         0x1f << ((uint8_t)_rgb_b_shift_16 & 0x1f));
        V_FontDrawRight("No",(int *)g[0x413b],0x9a,0x7d,(uint32_t)stk_150);
        V_FontDraw("Yes",(int *)g[0x413b],0xa4,0x7d,u25 | u19);
      }
      else if (stk_14c[u25] == 8) {
        if (g[0x79a6] == 0) {
          u19 = 0x1f << (b14 & 0x1f) | 0x3f << (b15 & 0x1f) | 0x1f << (b13 & 0x1f);
          font = (int *)g[0x413b];
          text = "Options Loaded";
        }
        else {
          u19 = 0x1f << (b14 & 0x1f) | 0x3f << (b15 & 0x1f) | 0x1f << (b13 & 0x1f);
          font = (int *)g[0x413b];
          text = "Options Saved";
        }
        V_FontDrawCenter(text,font,0x9f,0x76,u19);
      }
    }
    BGArrayDrawLayer(g[0x62d0],1);
  }
  if (stk_13c == 0x58) {
    ScreenSnap();
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
  stk_178 = stk_178 + 1;
  if ((b26) && (((stk_14c[0] == 10 || (stk_14c[1] == 10)) && (stk_1a8 == 0)))) {
    FrameSkipReset();
    GameSndPlay((int *)g[G_SYS_SOUNDS],pi6[0x107d],pi6[0x107e],0);
    KBRepeat = 0;
    return;
  }
  goto L_080a1af0;
}
#undef stk_1f4
#undef stk_1e8
#undef stk_1e4
#undef stk_1e0
#undef stk_1dc
#undef stk_1b0
#undef stk_1ac
#undef stk_1a8
#undef stk_194
#undef stk_188
#undef stk_184
#undef stk_17c
#undef stk_178
#undef stk_164
#undef stk_160
#undef stk_15c
#undef stk_158
#undef stk_154
#undef stk_150
#undef stk_14c
#undef stk_13c
#undef stk_138
#undef stk_134
#undef stk_130
#undef stk_12c
#undef stk_120
#undef stk_10c
#undef stk_fc
#undef stk_f8
#undef stk_f7
#undef stk_7c
#undef stk_78
#undef stk_74
#undef stk_70
#undef stk_6c
#undef stk_68
#undef stk_64
#undef stk_60
#undef stk_5c
#undef stk_4c
#undef stk_48
#undef stk_44
#undef stk_40
#undef stk_3c
#undef stk_38
#undef stk_34
#undef stk_30
#undef stk_2c
#undef stk_28
#undef stk_24

/* KeyConfigScreen @ 0x080a3aa0, 5453 bytes
 *
 * The key and joystick configuration screen ("KEY CONFIG" / "JOYSTICK
 * CONFIG") for players 1 and 2. Each entry (directions, six buttons, Start)
 * is assigned by pressing a key ("Press a key to assign to entry"); space
 * disables it ("Not used"), Esc cancels; "Config all" walks through every
 * entry; "Default" restores the defaults.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Globals read: backbuffer, speed_flag, vretrace
 * Calls: V_SetBuf, TimerSetSyncFPS, KBBufferClear, PadPoll, PadBufClear,
 *        UInpRefreshFlags, UInpBufClear, FrameSkipReset, BGMPoll, KBPoll,
 *        KBkbhit, KBgetchraw, PadHit, PadGet, GlobalInputUpdate, UInpHit,
 *        UInpGet, BGArrayMove, BGArrayUpdate, MasterPalProcessChanges,
 *        BGArrayDrawLayer, W_BoxFillTransSub16, V_FontDrawCenter,
 *        V_FontDraw, ...
 * C library: memcpy, sprintf
 * Called by: OptionsScreen
 * Messages:
 *   "Config all"
 *   "JOYSTICK CONFIG"
 *   "KEY CONFIG"
 *   "PLAYER 1"
 *   "PLAYER 2"
 *   "Press a key to assign to entry"
 *
 * Elecbyte file: src/mugen/menus.c
 * Note: 3 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x270 bytes,
 *       51 variables), because their address is taken.
 */
int KeyConfigScreen(int arg1,int arg2)

{
  uint8_t b1;
  bool b2;
  bool b3;
  bool b4;
  bool b5;
  int i6;
  int i7;
  int i8;
  bool b9;
  uint32_t u10;
  uint32_t stale_var;
  uint32_t stale_var_00;
  uint32_t stale_var_01;
  uint32_t u11;
  uint32_t u12;
  char *text;
  uint32_t *pu14;
  int i15;
  uint32_t u16;
  uint32_t stale_ECX;
  int i17;
  int i18;
  char *pc19;
  int i2;
  uint32_t *pu21;
  int *font;
  uint32_t u23;
  unsigned char frame[0x270] __attribute__((aligned(16)));
#define stk_270 (*(uint32_t *)(frame + 0x0))
#define stk_26c (*(int *)(frame + 0x4))
#define stk_268 (*(int *)(frame + 0x8))
#define stk_264 (*(int *)(frame + 0xc))
#define stk_254 (*(uint32_t *)(frame + 0x1c))
#define stk_248 (*(uint8_t *)(frame + 0x28))
#define stk_244 (*(uint8_t *)(frame + 0x2c))
#define stk_240 (*(int *)(frame + 0x30))
#define stk_23c (*(int *)(frame + 0x34))
#define stk_22c (*(int *)(frame + 0x44))
#define stk_224 (*(uint32_t *)(frame + 0x4c))
#define stk_220 (*(int *)(frame + 0x50))
#define stk_21c (*(uint32_t *)(frame + 0x54))
#define stk_218 (*(uint32_t *)(frame + 0x58))
#define stk_214 (*(int *(*)[15])(frame + 0x5c))
#define buf_1d8 (*(uint32_t (*)[10])(frame + 0x98))
#define buf_1b0 (*(uint32_t (*)[25])(frame + 0xc0))
#define stk_14c (*(char *(*)[4])(frame + 0x124))
#define stk_13c (*(char **)(frame + 0x134))
#define stk_138 (*(char **)(frame + 0x138))
#define stk_134 (*(char **)(frame + 0x13c))
#define stk_130 (*(char **)(frame + 0x140))
#define stk_12c (*(char **)(frame + 0x144))
#define stk_128 (*(char **)(frame + 0x148))
#define stk_124 (*(uint8_t **)(frame + 0x14c))
#define stk_120 (*(char **)(frame + 0x150))
#define stk_11c (*(char **)(frame + 0x154))
#define stk_118 (*(uint8_t **)(frame + 0x158))
#define text2 (*(char (*)[2])(frame + 0x164))
#define buf_10a (*(char (*)[126])(frame + 0x166))
#define stk_8c (*(uint32_t *)(frame + 0x1e4))
#define stk_88 (*(int *)(frame + 0x1e8))
#define stk_84 (*(int *)(frame + 0x1ec))
#define stk_7c (*(int *)(frame + 0x1f4))
#define stk_78 (*(int *)(frame + 0x1f8))
#define stk_74 (*(int *)(frame + 0x1fc))
#define stk_70 (*(int *)(frame + 0x200))
#define stk_6c (*(int *)(frame + 0x204))
#define stk_60 (*(int *)(frame + 0x210))
#define stk_5c (*(int *)(frame + 0x214))
#define stk_58 (*(uint32_t *)(frame + 0x218))
#define stk_54 (*(uint32_t *)(frame + 0x21c))
#define stk_50 (*(int *)(frame + 0x220))
#define stk_4c (*(uint32_t *)(frame + 0x224))
#define stk_48 (*(uint32_t *)(frame + 0x228))
#define stk_44 (*(uint32_t *)(frame + 0x22c))
#define stk_40 (*(uint32_t *)(frame + 0x230))
#define stk_34 (*(uint32_t *)(frame + 0x23c))
#define stk_30 (*(uint32_t *)(frame + 0x240))
#define stk_2c (*(uint32_t *)(frame + 0x244))
#define stk_28 (*(uint32_t *)(frame + 0x248))
  
  i8 = TimerFPS;
  i7 = KBRepeat;
  stk_254 = (uint32_t)(arg1 == 0);
  u10 = (stk_254 - 1 & 0xffffff80) + 0x100;
  stk_58 = 0x10 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x18 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
             8 << ((uint8_t)_rgb_b_shift_16 & 0x1f);
  stk_54 = 8 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0xc << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
             4 << ((uint8_t)_rgb_b_shift_16 & 0x1f);
  stk_23c = 0;
  stk_8c = 0;
  stk_88 = 0;
  stk_84 = 0;
  stk_7c = 0x31;
  stk_78 = 0x1e;
  stk_74 = 0xdc;
  stk_70 = 0xcd;
  stk_6c = 0xd;
  stk_60 = 0x50;
  stk_5c = 0xf;
  stk_50 = V_Width + 0x31;
  stk_4c = 0x1e;
  stk_48 = 0xdc;
  stk_44 = 0xcd;
  stk_40 = 0xd;
  stk_34 = 0x50;
  stk_30 = 0xf;
  if (arg1 == 0) {
    stk_214[0] = g + 0x7321;
    stk_214[1] = g + 0x732e;
  }
  else {
    stk_214[0] = g + 0x736f;
    stk_214[1] = g + 0x737c;
  }
  stk_14c[0] = "Config all";
  stk_14c[1] = "Up";
  stk_14c[2] = "Down";
  stk_14c[3] = "Left";
  stk_13c = "Right";
  stk_138 = "A";
  stk_134 = "B";
  stk_130 = "C";
  stk_12c = "X";
  stk_128 = "Y";
  stk_124 = &str_z;
  stk_120 = "Start";
  stk_11c = "Default";
  stk_118 = &str_exit;
  stk_220 = 0;
  i15 = 0;
  stk_2c = stk_58;
  stk_28 = stk_54;
  do {
    font = stk_214[stk_220];
    *(int *)((int)buf_1b0 + i15 + 4) = font[1];
    *(int *)((int)buf_1b0 + i15 + 8) = font[3];
    *(int *)((int)buf_1b0 + i15 + 0xc) = font[4];
    *(int *)((int)buf_1b0 + i15 + 0x10) = font[2];
    *(int *)((int)buf_1b0 + i15 + 0x14) = font[5];
    *(int *)((int)buf_1b0 + i15 + 0x18) = font[6];
    *(int *)((int)buf_1b0 + i15 + 0x1c) = font[7];
    *(int *)((int)buf_1b0 + i15 + 0x20) = font[8];
    *(int *)((int)buf_1b0 + i15 + 0x24) = font[9];
    *(int *)((int)buf_1b0 + i15 + 0x28) = font[10];
    *(int *)((int)buf_1b0 + i15 + 0x2c) = font[0xb];
    i15 = i15 + 0x2c;
    stk_220 = stk_220 + 1;
  } while (stk_220 < 2);
  V_SetBuf((int *)g[G_BACKBUFFER],0);
  TimerSetSyncFPS(0x3c);
  KBBufferClear();
  PadPoll();
  PadBufClear();
  UInpRefreshFlags();
  UInpBufClear();
  KBRepeat = 1;
  FrameSkipReset();
  stk_26c = arg2 << 2;
  do {
    b3 = false;
    BGMPoll(g + 0x6efa);
    b2 = false;
    b4 = false;
    stk_21c = 0;
    stk_218 = 0;
    b5 = false;
    stk_84 = 0;
    PadPoll();
    KBPoll();
    b9 = KBkbhit();
    if (ZEXT8(b9) != 0) {
      stk_21c = KBgetchraw();
    }
    b9 = PadHit();
    if (ZEXT8(b9) != 0) {
      stk_218 = PadGet();
    }
    GlobalInputUpdate();
    b9 = UInpHit();
    if (ZEXT8(b9) != 0) {
      UInpGet();
    }
    u16 = stk_218 & 0xffffff9f;
    if ((stk_21c == 0x1c) || (u16 - 5 < 0x1b)) {
      stk_84 = 1;
    }
    if ((stk_21c == 200) || (u16 == 1)) {
      b2 = true;
    }
    if ((stk_21c == 0xd0) || (u16 == 2)) {
      b3 = true;
    }
    if ((stk_21c == 0xcb) || (u16 == 3)) {
      b4 = true;
    }
    if ((stk_21c == 0xcd) || (u16 == 4)) {
      b5 = true;
    }
    if (stk_23c != 0) {
      b3 = false;
      b2 = false;
      b4 = false;
      b5 = false;
      stk_84 = 0;
    }
    if (stk_21c - 0x3b < 2) {
      stk_8c = (uint32_t)(stk_21c != 0x3b);
      stk_88 = 0;
      stk_84 = 1;
    }
    if (stk_21c - 0x3d < 2) {
      stk_8c = (uint32_t)(stk_21c != 0x3d);
      stk_88 = 0xc;
      stk_84 = 1;
    }
    if ((stk_21c == 1) && (stk_23c == 0)) {
      stk_88 = 0xd;
      stk_84 = 1;
    }
    if ((stk_21c == 1) && (stk_23c != 0)) {
      stk_88 = 0;
      stk_84 = 0;
      stk_23c = 0;
      stk_220 = 0;
      do {
        i15 = stk_8c * 0xb + stk_220;
        buf_1b0[i15 + 1] = (uint32_t)stk_214[i15 + 2];
        stk_220 = stk_220 + 1;
      } while (stk_220 < 0xb);
    }
    if (b2) {
      if (stk_88 < 1) {
        stk_88 = 0xd;
      }
      else {
        stk_88 = stk_88 + -1;
      }
      if (stk_88 - 1U < 0xb) {
        stk_88 = 0;
      }
    }
    if (b3) {
      if (stk_88 < 0xd) {
        stk_88 = stk_88 + 1;
      }
      else {
        stk_88 = 0;
      }
      if (stk_88 - 1U < 0xb) {
        stk_88 = 0xc;
      }
    }
    if (b4) {
      stk_8c = 0;
    }
    if (b5) {
      stk_8c = 1;
    }
    if ((stk_84 != 0) && (stk_88 == 0)) {
      stk_220 = 0;
      do {
        i15 = stk_8c * 0xb + stk_220;
        stk_214[i15 + 2] = (int *)buf_1b0[i15 + 1];
        stk_220 = stk_220 + 1;
      } while (stk_220 < 0xb);
      stk_23c = stk_8c + 1;
      stk_240 = 0;
      KBRepeat = 0;
      stk_21c = 0;
      stk_218 = 0;
    }
    if ((stk_88 == 0xc) && (stk_84 != 0)) {
      stk_220 = 0;
      do {
        if (arg1 == 0) {
          i18 = stk_8c * 0xb + stk_220;
          i15 = i18 * 4;
          u11 = (&DefaultKeyCfg)[i18];
        }
        else {
          i15 = (stk_8c * 0xb + stk_220) * 4;
          u11 = *(uint32_t *)(DefaultJoyCfg + i15);
        }
        *(uint32_t *)((int)buf_1b0 + i15 + 4) = u11;
        stk_220 = stk_220 + 1;
      } while (stk_220 < 0xb);
    }
    if (((stk_23c != 0) && (stk_21c != 1)) &&
       ((((arg1 == 0 && ((stk_21c != 0 && ((stk_21c & 0x100) == 0)))) ||
         ((arg1 == 1 && ((stk_218 != 0 && ((stk_218 & 0x100) == 0)))))) ||
        (stk_21c == 0x39)))) {
      if (stk_21c == 0x39) {
        buf_1d8[stk_23c * 0xb + stk_240] = u10;
      }
      else if (stk_23c != 0) {
        if (arg1 != 0) {
          stk_21c = stk_218;
        }
        buf_1d8[stk_23c * 0xb + stk_240] = stk_21c;
      }
      stk_240 = stk_240 + 1;
      if (10 < stk_240) {
        stk_23c = 0;
        KBRepeat = 1;
      }
    }
    BGArrayMove((int *)g[0x62d0],0.0,0.0);
    BGArrayUpdate(g[0x62d0]);
    if (g[0x7307] == 0) {
      MasterPalProcessChanges();
      u16 = stale_ECX;
      BGArrayDrawLayer(g[0x62d0],0);
      W_BoxFillTransSub16(stk_7c - stk_5c,stk_78 + -0xe,stk_5c + -1 + stk_7c + stk_74,
                          stk_78 + stk_70 + -1,stk_58);
      u12 = (stk_7c - stk_5c) - 1;
      W_BoxFillTransSub16(u12,stk_78 + -0xd,u12,stk_78 + stk_70 + -2,stk_54);
      u12 = stk_74 + stk_7c + stk_5c;
      W_BoxFillTransSub16(u12,stk_78 + -0xd,u12,stk_78 + stk_70 + -2,stk_54);
      W_BoxFillTransSub16((stk_7c - stk_5c) + 1,stk_78 + -0xf,
                          stk_5c + -2 + stk_7c + stk_74,stk_78 + -0xf,stk_54);
      W_BoxFillTransSub16((stk_7c - stk_5c) + 1,stk_70 + stk_78,
                          stk_5c + -2 + stk_7c + stk_74,stk_70 + stk_78,stk_54);
      text = "JOYSTICK CONFIG";
      if (arg1 == 0) {
        text = "KEY CONFIG";
      }
      V_FontDrawCenter(text,(int *)g[0x413b],V_Width / 2,10,
                       0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                       0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                       0x1f << ((uint8_t)_rgb_b_shift_16 & 0x1f));
      V_FontDrawCenter("PLAYER 1",(int *)g[0x413b],0x5a,stk_78 + -3,
                       0x10 << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                       0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                       0x1f << ((uint8_t)_rgb_b_shift_16 & 0x1f));
      V_FontDrawCenter("PLAYER 2",(int *)g[0x413b],0xe5,stk_78 + -3,
                       0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                       0x20 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                       0x10 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
      u12 = arg2 % 0x1c2;
      if ((int)u12 < 0x96) {
        text = "Press a key to assign to entry";
        pc19 = text2;
        for (i15 = 7; i15 != 0; i15 = i15 + -1) {
          *(uint32_t *)pc19 = *(uint32_t *)text;
          text = text + 4;
          pc19 = pc19 + 4;
        }
        pc19[0] = 'r';
        pc19[1] = 'y';
        pc19[2] = '\0';
      }
      else if ((int)u12 < 300) {
        text = "Press spacebar to disable entry";
        pc19 = text2;
        for (i15 = 8; i15 != 0; i15 = i15 + -1) {
          *(uint32_t *)pc19 = *(uint32_t *)text;
          text = text + 4;
          pc19 = pc19 + 4;
        }
      }
      else {
        memcpy(text2,"Press esc to cancel",0x14);
        u16 = u12;
      }
      if (stk_23c == 1) {
        V_FontDraw(text2,(int *)g[0x413a],stk_7c,stk_6c * 0xd + stk_78 + 10,
                   0x18 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x30 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                   0x18 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
      }
      else if (stk_23c == 2) {
        V_FontDrawRight(text2,(int *)g[0x413a],stk_74 + stk_7c,
                        stk_6c * 0xd + stk_78 + 10,
                        0x18 << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                        0x30 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                        0x18 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
      }
      stk_22c = 0;
      stk_220 = 0;
      stk_268 = 0;
      do {
        b1 = (uint8_t)_rgb_r_shift_16;
        stk_244 = (uint8_t)_rgb_g_shift_16;
        stk_248 = (uint8_t)_rgb_b_shift_16;
        u12 = 0x18 << (b1 & 0x1f) | 0x30 << (stk_244 & 0x1f) | 0x18 << (stk_248 & 0x1f);
        if (((stk_220 == 0xe) || (stk_220 == 0xc)) || (stk_220 == 0)) {
          stk_22c = stk_22c + 1;
        }
        i15 = (stk_220 + stk_22c) * stk_6c + stk_78;
        stk_224 = u12;
        if (stk_220 == stk_88) {
          if (stk_26c % 0x80 < 0x40) {
            i18 = stk_26c % 0x40 + 0x20;
          }
          else {
            i18 = 0x5f - stk_26c % 0x40;
          }
          if (stk_23c == 0) {
            stk_270 = (i18 >> 3) << (b1 & 0x1f) | (i18 >> 2) << (stk_244 & 0x1f) |
                        (i18 >> 3) << (stk_248 & 0x1f);
          }
          else {
            stk_270 = 0xc << (b1 & 0x1f) | 0x18 << (stk_244 & 0x1f) |
                        0xc << (stk_248 & 0x1f);
          }
          i18 = stk_7c;
          if (stk_220 < 0xd) {
            i18 = stk_8c * 0x8c + stk_7c;
          }
          W_BoxFillTransAdd16(i18 - 5,i15 + -10,i18 + 0x56,i15 + 3,stk_270);
          if ((stk_8c == 0) || (stk_88 == 0xd)) {
            u12 = 0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f)
                     | 0x1f << ((uint8_t)_rgb_b_shift_16 & 0x1f);
          }
          else {
            stk_224 = 0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                        0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                        0x1f << ((uint8_t)_rgb_b_shift_16 & 0x1f);
          }
        }
        if ((0xb < stk_220) && (stk_23c != 0)) break;
        V_FontDraw(*(char **)((int)stk_14c + stk_268),(int *)g[0x413b],stk_7c,i15,u12);
        if (stk_220 < 0xd) {
          V_FontDraw(*(char **)((int)stk_14c + stk_268),(int *)g[0x413b],stk_7c + 0x8c,i15,
                     stk_224);
        }
        if (stk_220 == 0) {
          V_FontDrawRight("(F1)",(int *)g[0x413b],stk_60 + stk_7c,i15,
                          0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                          0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                          0x10 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
          V_FontDrawRight("(F2)",(int *)g[0x413b],stk_7c + 0x8c + stk_60,i15,
                          0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                          0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                          0x10 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
        }
        if (stk_220 == 0xc) {
          V_FontDrawRight("(F3)",(int *)g[0x413b],stk_60 + stk_7c,i15,
                          0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                          0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                          0x10 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
          V_FontDrawRight("(F4)",(int *)g[0x413b],stk_7c + 0x8c + stk_60,i15,
                          0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                          0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                          0x10 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
        }
        if (stk_220 == 0xd) {
          V_FontDrawRight("(Esc)",(int *)g[0x413b],stk_60 + stk_7c,i15,
                          0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                          0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                          0x10 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
        }
        if (stk_220 - 1U < 0xb) {
          if (arg1 == 0) {
            u23 = *(uint32_t *)((int)buf_1b0 + stk_268);
            if (u23 == 0x100) {
              memcpy(text2,"Not used",9);
              u16 = u23;
            }
            else {
              pu14 = KBRawToName((uint8_t)u23);
              sprintf(text2,"%s",pu14);
            }
            V_FontDrawRight(text2,(int *)g[0x413b],stk_60 + stk_7c,i15,u12);
            u12 = *(uint32_t *)((int)buf_1b0 + stk_268 + 0x2c);
            if (u12 == 0x100) {
              memcpy(text2,"Not used",9);
              u16 = u12;
            }
            else {
              pu14 = KBRawToName((uint8_t)u12);
              sprintf(text2,"%s",pu14,u16);
            }
            i18 = stk_7c + 0x8c + stk_60;
            font = (int *)g[0x413b];
          }
          else {
            u16 = *(uint32_t *)((int)buf_1b0 + stk_268);
            if (u16 == u10) {
              memcpy(text2,"Not used",9);
            }
            else {
              sprintf(text2,"%c-%02i",((int)u16 >> 5 & 0x11U) + 0x41,u16 & 0xffffff9f);
            }
            V_FontDrawRight(text2,(int *)g[0x413b],stk_60 + stk_7c,i15,u12);
            u23 = *(uint32_t *)((int)buf_1b0 + stk_268 + 0x2c);
            if (u23 == u10) {
              memcpy(text2,"Not used",9);
              u16 = u12;
            }
            else {
              u16 = u23 & 0xffffff9f;
              sprintf(text2,"%c-%02i",((int)u23 >> 5 & 0x11U) + 0x41,u16);
            }
            i18 = stk_7c + 0x8c + stk_60;
            font = (int *)g[0x413b];
          }
          V_FontDrawRight(text2,font,i18,i15,stk_224);
        }
        stk_220 = stk_220 + 1;
        stk_268 = stk_268 + 4;
      } while (stk_220 < 0xe);
      if (stk_23c != 0) {
        i15 = (stk_240 + 2) * stk_6c + stk_78;
        if (stk_26c % 0x80 < 0x40) {
          i18 = stk_26c % 0x40 + 0x20;
        }
        else {
          i18 = 0x5f - stk_26c % 0x40;
        }
        if (stk_23c == 1) {
          u16 = stk_7c + 0x56;
          i17 = stk_7c;
        }
        else {
          u16 = stk_7c + 0xe2;
          i17 = stk_7c + 0x8c;
        }
        W_BoxFillTransAdd16(i17 - 5,i15 + -9,u16,i15 + 2,
                            (i18 >> 3) << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                            (0x60 - i18 >> 2) << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                            (0x60 - i18 / 2 >> 3) << ((uint8_t)_rgb_b_shift_16 & 0x1f));
      }
      BGArrayDrawLayer(g[0x62d0],1);
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
    stk_26c = stk_26c + 4;
    arg2 = arg2 + 1;
    if ((stk_84 != 0) && (stk_88 == 0xd)) {
      i15 = 0;
      FrameSkipReset();
      stk_220 = 0;
      stk_264 = 0;
      do {
        i2 = 0;
        i18 = *(int *)((int)stk_214 + stk_264);
        i17 = i15;
        do {
          font = &KeyCfgToKBIMap + i2;
          i2 = i2 + 1;
          i6 = i17 + 4;
          i17 = i17 + 4;
          *(uint32_t *)(i18 + *font * 4) = *(uint32_t *)((int)buf_1b0 + i6);
        } while (i2 < 0xb);
        stk_220 = stk_220 + 1;
        stk_264 = stk_264 + 4;
        i15 = i15 + 0x2c;
      } while (stk_220 < 2);
      if (arg1 == 1) {
        i18 = 0;
        i15 = 0x1ce20;
        stk_220 = 1;
        do {
          if (*(int *)(i15 + 0xc + (int)g) != 0) {
            pu14 = (uint32_t *)((int)g + i18 + 0x1cdbc);
            pu21 = (uint32_t *)((int)g + i18 + 0x1cd54);
            for (i17 = 0xd; i17 != 0; i17 = i17 + -1) {
              *pu21 = *pu14;
              pu14 = pu14 + 1;
              pu21 = pu21 + 1;
            }
          }
          i18 = i18 + 0x34;
          i15 = i15 + 4;
          stk_220 = stk_220 + -1;
        } while (-1 < stk_220);
      }
      GameInputSetup();
      KBRepeat = i7;
      TimerSetSyncFPS(i8);
      return arg2;
    }
  } while( true );
}
#undef stk_270
#undef stk_26c
#undef stk_268
#undef stk_264
#undef stk_254
#undef stk_248
#undef stk_244
#undef stk_240
#undef stk_23c
#undef stk_22c
#undef stk_224
#undef stk_220
#undef stk_21c
#undef stk_218
#undef stk_214
#undef buf_1d8
#undef buf_1b0
#undef stk_14c
#undef stk_13c
#undef stk_138
#undef stk_134
#undef stk_130
#undef stk_12c
#undef stk_128
#undef stk_124
#undef stk_120
#undef stk_11c
#undef stk_118
#undef text2
#undef buf_10a
#undef stk_8c
#undef stk_88
#undef stk_84
#undef stk_7c
#undef stk_78
#undef stk_74
#undef stk_70
#undef stk_6c
#undef stk_60
#undef stk_5c
#undef stk_58
#undef stk_54
#undef stk_50
#undef stk_4c
#undef stk_48
#undef stk_44
#undef stk_40
#undef stk_34
#undef stk_30
#undef stk_2c
#undef stk_28

/* TrainingMenuUpdate @ 0x080a4ff0, 1167 bytes
 *
 * Handles the training mode menu: Start opens and closes it, directions move
 * through and change the settings (see TrainingMenuDraw), and the other keys
 * are passed on to the player.
 *
 * Parameters:
 *   arg1         uint32_t
 *
 * Calls: KBToUInp, KBIIs6ButtonOrStart, KBIStuffBuf
 * Called by: GameInputUpdate
 *
 * Elecbyte file: src/mugen/menus.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x90 bytes,
 *       15 variables), because their address is taken.
 */
uint32_t TrainingMenuUpdate(uint32_t arg1)

{
  int i1;
  int i2;
  uint32_t *pu3;
  bool b4;
  int *pi5;
  bool b6;
  uint32_t uinp;
  uint32_t stale_var;
  int *pi8;
  int *pi9;
  int i10;
  unsigned char frame[0x90] __attribute__((aligned(16)));
#define stk_8c (*(uint32_t *)(frame + 0x4))
#define stk_88 (*(uint32_t *)(frame + 0x8))
#define stk_84 (*(uint32_t *)(frame + 0xc))
#define stk_80 (*(uint32_t *)(frame + 0x10))
#define stk_7c (*(int *(*)[4])(frame + 0x14))
#define stk_6c (*(int (*)[4])(frame + 0x24))
#define stk_5c (*(uint32_t **)(frame + 0x34))
#define stk_58 (*(uint32_t **)(frame + 0x38))
#define stk_54 (*(uint32_t **)(frame + 0x3c))
#define stk_4c (*(uint32_t *(*)[4])(frame + 0x44))
#define stk_3c (*(uint32_t *)(frame + 0x54))
#define stk_38 (*(uint32_t *)(frame + 0x58))
#define stk_34 (*(uint32_t *)(frame + 0x5c))
#define stk_30 (*(uint32_t *)(frame + 0x60))
#define stk_2c (*(uint32_t *)(frame + 0x64))
  
  stk_5c = &stk_3c;
  stk_4c[0] = &stk_3c;
  stk_54 = &stk_88;
  stk_4c[2] = &stk_88;
  stk_58 = &stk_84;
  stk_7c[0] = g + 0x7dbc;
  b4 = false;
  stk_3c = 3;
  stk_38 = 2;
  stk_34 = 4;
  stk_30 = 4;
  stk_2c = 8;
  stk_84 = 3;
  stk_80 = 8;
  stk_88 = 3;
  stk_4c[1] = &stk_84;
  stk_7c[1] = g + 0x7dc1;
  stk_6c[0] = 5;
  stk_6c[1] = 2;
  stk_6c[2] = 1;
  i1 = g[0x7dbb];
  stk_7c[2] = g + 0x7dc3;
  pi9 = stk_7c[i1];
  if (g[0x7309] == 0) {
    return 0;
  }
  if (g[0x33b6] == 1) {
    pi8 = g + 0x7348;
    i10 = g[0x73da];
  }
  else {
    pi8 = g + 0x733b;
    i10 = g[0x73db];
  }
  uinp = KBToUInp(pi8[10]);
  if ((arg1 == uinp) && (g[0x33ae] == 3)) {
    g[0x7dba] = (uint32_t)(g[0x7dba] == 0);
    return 0;
  }
  if (g[0x7dba] == 0) {
    return 0;
  }
  *pi9 = i1;
  if (i1 == 1) {
    pi9[1] = *(int *)(i10 + 0x33f8) + -1;
  }
  else if ((i1 < 2) && (i1 == 0)) {
    pi9[1] = *(int *)(i10 + 0x2cd8);
    pi9[2] = *(int *)(i10 + 0x2cd4);
    pi9[4] = *(int *)(i10 + 0x2ce4);
    i2 = *(int *)(i10 + 0x2cdc);
    if ((i2 == 0) && (*(int *)(i10 + 0x2ce0) == 0)) {
      pi9[3] = 0;
    }
    else if (i2 == 0x32) {
      pi9[3] = 1;
    }
    else {
      pi9[3] = (i2 != 0x96) + 2;
    }
  }
  stk_8c = 0;
  uinp = KBToUInp(pi8[4]);
  pi5 = g;
  if (arg1 == uinp) {
    i2 = g[0x7db9];
    g[0x7db9] = i2 + -1;
    if (i2 + -1 < 0) {
      pi5[0x7db9] = stk_4c[i1][pi5[0x7db8]] + -1;
    }
  }
  else {
    uinp = KBToUInp(pi8[2]);
    pi5 = g;
    if (arg1 != uinp) {
      uinp = KBToUInp(pi8[1]);
      pi5 = g;
      if (arg1 == uinp) {
        i2 = g[0x7db8];
        g[0x7db8] = i2 + -1;
        if (i2 + -1 < 0) {
          pi5[0x7db8] = stk_6c[i1] + -1;
        }
      }
      else {
        uinp = KBToUInp(pi8[3]);
        pi5 = g;
        if (arg1 != uinp) {
          b6 = KBIIs6ButtonOrStart(arg1,(int)pi8);
          if ((ZEXT8(b6) != 0) || (uinp = KBToUInp(1), arg1 == uinp)) {
            stk_8c = 1;
          }
          goto L_080a532d;
        }
        i2 = g[0x7db8];
        g[0x7db8] = i2 + 1;
        if (stk_6c[i1] <= i2 + 1) {
          pi5[0x7db8] = 0;
        }
      }
      g[0x7db9] = pi9[g[0x7db8]];
      goto L_080a532d;
    }
    i2 = g[0x7db9];
    pi8 = g + 0x7db8;
    pu3 = stk_4c[i1];
    g[0x7db9] = i2 + 1;
    if (i2 + 1 == pu3[*pi8]) {
      pi5[0x7db9] = 0;
    }
  }
  b4 = true;
L_080a532d:
  pi9[g[0x7db8]] = g[0x7db9];
  if (i1 == 2) {
    *(uint32_t *)(i10 + 0x262c) = 0;
  }
  else {
    *(uint32_t *)(i10 + 0x262c) = 1;
    *(int *)(i10 + 0x2cd0) = i1;
  }
  if (i1 == 1) {
    *(int *)(i10 + 0x33f8) = pi9[1] + 1;
  }
  else if ((i1 < 2) && (i1 == 0)) {
    *(int *)(i10 + 0x2cd8) = pi9[1];
    *(int *)(i10 + 0x2cd4) = pi9[2];
    *(int *)(i10 + 0x2ce4) = pi9[4];
    i1 = pi9[3];
    if (i1 == 1) {
      *(uint32_t *)(i10 + 0x2cdc) = 0x32;
      *(uint32_t *)(i10 + 0x2ce0) = 0;
    }
    else if (i1 < 2) {
      if (i1 == 0) {
        *(uint32_t *)(i10 + 0x2ce0) = 0;
        *(uint32_t *)(i10 + 0x2cdc) = 0;
      }
    }
    else if (i1 == 2) {
      *(uint32_t *)(i10 + 0x2cdc) = 0x96;
      *(uint32_t *)(i10 + 0x2ce0) = 100;
    }
    else if (i1 == 3) {
      *(uint32_t *)(i10 + 0x2cdc) = 0;
      *(uint32_t *)(i10 + 0x2ce0) = 0x118;
    }
  }
  g[0x7dbb] = *pi9;
  if (b4) {
    pi9 = (int *)(i10 + 0x2c4);
    uinp = 1;
    do {
      if (*pi9 != 0) {
        KBIStuffBuf(i10 + 0x248,uinp | 0x10);
      }
      uinp = uinp + 1;
      pi9 = pi9 + 1;
    } while ((int)uinp < 0xc);
    return stk_8c;
  }
  return stk_8c;
}
#undef stk_8c
#undef stk_88
#undef stk_84
#undef stk_80
#undef stk_7c
#undef stk_6c
#undef stk_5c
#undef stk_58
#undef stk_54
#undef stk_4c
#undef stk_3c
#undef stk_38
#undef stk_34
#undef stk_30
#undef stk_2c

/* TrainingMenuReset @ 0x080a5480, 45 bytes
 *
 * Closes the training menu and sets the dummy defaults for training mode.
 *
 * Called by: GameInputUpdate, MainLoop
 *
 * Elecbyte file: src/mugen/menus.c
 */
uint32_t TrainingMenuReset(void)

{
  int i1;
  int *pi2;
  
  pi2 = g;
  i1 = g[0x33ae];
  g[0x7db9] = 0;
  pi2[0x7db8] = 0;
  pi2[0x7dba] = (uint32_t)(i1 == 3);
  return (uint32_t)(i1 == 3);
}

/* TrainingMenuDraw @ 0x080a54b0, 1716 bytes
 *
 * Draws the "Training Menu" box with its settings: Dummy control
 * (Cooperative, AI with "AI Level", Manual), Dummy mode (Stand, Crouch,
 * Jump...), Guard mode, Distance, Button jam, and Close.
 *
 * Calls: W_Box, W_BoxFillTransAdd16_B50, V_FontDrawCenter, V_FontDraw
 * Called by: GameLoop
 * Messages:
 *   "Dummy control"
 *   "Guard mode"
 *   "Dummy mode"
 *   "Button jam"
 *   "AI Level"
 *   "Training Menu"
 *
 * Elecbyte file: src/mugen/menus.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x1f0 bytes,
 *       63 variables), because their address is taken.
 */
void TrainingMenuDraw(void)

{
  int *pi1;
  uint8_t b2;
  uint8_t b3;
  int i4;
  uint32_t u5;
  void **ppv6;
  int i2;
  uint32_t *pu8;
  char *text;
  int *font;
  int i11;
  int i12;
  uint32_t u13;
  unsigned char frame[0x1f0] __attribute__((aligned(16)));
#define stk_1f0 (*(uint8_t *)(frame + 0x0))
#define stk_1e0 (*(int *)(frame + 0x10))
#define stk_1dc (*(int *)(frame + 0x14))
#define stk_1b8 (*(char **)(frame + 0x38))
#define stk_1b4 (*(uint32_t *)(frame + 0x3c))
#define stk_1b0 (*(char ***)(frame + 0x40))
#define stk_1ac (*(char **)(frame + 0x44))
#define stk_1a8 (*(char **)(frame + 0x48))
#define stk_1a4 (*(uint32_t *)(frame + 0x4c))
#define stk_1a0 (*(uint32_t *)(frame + 0x50))
#define stk_19c (*(char ***)(frame + 0x54))
#define stk_198 (*(uint32_t **)(frame + 0x58))
#define stk_194 (*(uint8_t **)(frame + 0x5c))
#define stk_190 (*(uint8_t **)(frame + 0x60))
#define stk_18c (*(int *(*)[4])(frame + 0x64))
#define stk_17c (*(int (*)[4])(frame + 0x74))
#define stk_16c (*(char ***)(frame + 0x84))
#define stk_168 (*(char ***)(frame + 0x88))
#define stk_164 (*(char ***)(frame + 0x8c))
#define stk_15c (*(char **(*)[4])(frame + 0x94))
#define stk_14c (*(uint32_t **)(frame + 0xa4))
#define stk_148 (*(uint32_t **)(frame + 0xa8))
#define stk_144 (*(uint32_t **)(frame + 0xac))
#define stk_13c (*(uint32_t **)(frame + 0xb4))
#define stk_138 (*(uint32_t **)(frame + 0xb8))
#define stk_134 (*(uint32_t **)(frame + 0xbc))
#define stk_12c (*(char ****)(frame + 0xc4))
#define stk_128 (*(char ****)(frame + 0xc8))
#define stk_124 (*(char ****)(frame + 0xcc))
#define stk_11c (*(char ***(*)[4])(frame + 0xd4))
#define stk_10c (*(uint32_t (*)[8])(frame + 0xe4))
#define stk_ec (*(char **)(frame + 0x104))
#define stk_e8 (*(char **)(frame + 0x108))
#define stk_e4 (*(char **)(frame + 0x10c))
#define stk_e0 (*(char **)(frame + 0x110))
#define stk_dc (*(char **)(frame + 0x114))
#define stk_cc (*(uint32_t *)(frame + 0x124))
#define stk_c8 (*(uint32_t *)(frame + 0x128))
#define stk_c4 (*(uint32_t *)(frame + 0x12c))
#define stk_c0 (*(uint32_t *)(frame + 0x130))
#define stk_bc (*(uint32_t *)(frame + 0x134))
#define stk_ac (*(char ***)(frame + 0x144))
#define stk_a8 (*(uint8_t ***)(frame + 0x148))
#define stk_a4 (*(char ***)(frame + 0x14c))
#define stk_a0 (*(uint8_t ***)(frame + 0x150))
#define stk_9c (*(uint32_t **)(frame + 0x154))
#define stk_8c (*(char ***)(frame + 0x164))
#define stk_88 (*(uint8_t ***)(frame + 0x168))
#define stk_84 (*(char ***)(frame + 0x16c))
#define stk_80 (*(uint8_t ***)(frame + 0x170))
#define stk_7c (*(uint32_t **)(frame + 0x174))
#define stk_6c (*(uint32_t (*)[8])(frame + 0x184))
#define stk_4c (*(uint8_t **)(frame + 0x1a4))
#define stk_48 (*(char **)(frame + 0x1a8))
#define stk_44 (*(char **)(frame + 0x1ac))
#define stk_40 (*(uint8_t **)(frame + 0x1b0))
#define stk_3c (*(char **)(frame + 0x1b4))
#define stk_38 (*(char **)(frame + 0x1b8))
#define stk_34 (*(uint8_t **)(frame + 0x1bc))
#define stk_30 (*(uint8_t **)(frame + 0x1c0))
#define stk_2c (*(char **)(frame + 0x1c4))
#define stk_28 (*(char **)(frame + 0x1c8))
#define stk_24 (*(char **)(frame + 0x1cc))
  
  stk_2c = "Cooperative";
  stk_28 = "AI";
  stk_24 = "Manual";
  stk_194 = &str_none_9809;
  stk_190 = &str_auto_982e;
  stk_3c = "Stand";
  stk_38 = "Crouch";
  stk_34 = &str_jump;
  stk_30 = &str_w_jump;
  stk_4c = &str_any;
  stk_48 = "Close";
  stk_44 = "Medium";
  stk_40 = &str_far;
  stk_1b0 = &stk_2c;
  ppv6 = &d_08287a98;
  pu8 = stk_6c;
  for (i4 = 8; i4 != 0; i4 = i4 + -1) {
    *pu8 = *ppv6;
    ppv6 = ppv6 + 1;
    pu8 = pu8 + 1;
  }
  stk_ac = stk_1b0;
  stk_a8 = &stk_194;
  stk_a4 = &stk_3c;
  stk_a0 = &stk_4c;
  stk_9c = stk_6c;
  stk_8c = stk_1b0;
  stk_88 = &stk_194;
  stk_84 = &stk_3c;
  stk_80 = &stk_4c;
  stk_7c = stk_6c;
  stk_198 = stk_10c;
  stk_cc = 3;
  stk_c8 = 2;
  stk_c4 = 4;
  stk_c0 = 4;
  stk_bc = 8;
  stk_ec = "Dummy control";
  stk_e8 = "Guard mode";
  stk_e4 = "Dummy mode";
  stk_e0 = "Distance";
  stk_dc = "Button jam";
  ppv6 = &d_08287ab8;
  pu8 = stk_10c;
  for (i4 = 8; i4 != 0; i4 = i4 + -1) {
    *pu8 = *ppv6;
    ppv6 = ppv6 + 1;
    pu8 = pu8 + 1;
  }
  stk_1b8 = "Dummy control";
  stk_1ac = "Dummy control";
  stk_12c = &stk_8c;
  stk_124 = &stk_1b0;
  stk_11c[0] = &stk_8c;
  stk_11c[2] = &stk_1b0;
  stk_128 = &stk_19c;
  stk_11c[1] = &stk_19c;
  stk_14c = &stk_cc;
  stk_148 = &stk_1a4;
  stk_144 = &stk_1b4;
  stk_13c = &stk_cc;
  stk_1a4 = 3;
  stk_1a0 = 8;
  stk_1a8 = "AI Level";
  stk_1b4 = 3;
  stk_138 = &stk_1a4;
  stk_134 = &stk_1b4;
  stk_16c = &stk_ec;
  stk_168 = &stk_1ac;
  stk_15c[0] = &stk_ec;
  stk_15c[1] = &stk_1ac;
  stk_164 = &stk_1b8;
  stk_15c[2] = &stk_1b8;
  stk_17c[0] = 5;
  stk_17c[1] = 2;
  stk_17c[2] = 1;
  i4 = g[0x7dbb];
  stk_18c[0] = g + 0x7dbc;
  stk_18c[1] = g + 0x7dc1;
  stk_18c[2] = g + 0x7dc3;
  pi1 = stk_18c[i4];
  stk_19c = stk_1b0;
  W_Box(0x4f,0x1d,0xf1,0x97,
        10 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x14 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
        0x10 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
  W_Box(0x50,0x1e,0xf0,0x96,
        0x18 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x30 << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
        0x1e << ((uint8_t)_rgb_b_shift_16 & 0x1f));
  W_BoxFillTransAdd16_B50(0x50,0x1e,0xf0,0x96,3 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
  b2 = (uint8_t)_rgb_r_shift_16;
  b3 = (uint8_t)_rgb_g_shift_16;
  u5 = 0x1f << (b2 & 0x1f) | 0x3f << (b3 & 0x1f);
  stk_1f0 = (uint8_t)_rgb_b_shift_16;
  i2 = 0;
  V_FontDrawCenter("Training Menu",(int *)g[0x413b],0xa0,0x29,0);
  V_FontDrawCenter("Training Menu",(int *)g[0x413b],0x9f,0x28,
                   0x1f << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x3f << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                   0x1f << ((uint8_t)_rgb_b_shift_16 & 0x1f));
  *pi1 = i4;
  if (0 < stk_17c[i4]) {
    stk_1dc = 0x3c;
    stk_1e0 = 0x3d;
    do {
      V_FontDraw(stk_15c[i4][i2],(int *)g[0x413b],0x5b,stk_1e0,0);
      if (pi1[i2] == -1) {
        i11 = 0x5a;
        font = (int *)g[0x413b];
        text = stk_15c[i4][i2];
        i12 = stk_1e0;
        u13 = 0xc << (b2 & 0x1f) | 0x19 << (b3 & 0x1f) | 0xc << (stk_1f0 & 0x1f);
      }
      else {
        V_FontDraw(stk_11c[i4][i2][pi1[i2]],(int *)g[0x413b],0xb5,stk_1e0,0);
        i12 = stk_1dc;
        if (g[0x7db8] == i2) {
          V_FontDraw(stk_15c[i4][i2],(int *)g[0x413b],0x5a,stk_1dc,
                     0x1f << (stk_1f0 & 0x1f) | u5);
          i11 = 0xb4;
          font = (int *)g[0x413b];
          text = stk_11c[i4][i2][pi1[i2]];
          u13 = 0x19 << (stk_1f0 & 0x1f) | u5;
        }
        else {
          V_FontDraw(stk_15c[i4][i2],(int *)g[0x413b],0x5a,stk_1dc,
                     0x10 << ((uint8_t)_rgb_r_shift_16 & 0x1f) | 0x20 << ((uint8_t)_rgb_g_shift_16 & 0x1f)
                     | 0x10 << ((uint8_t)_rgb_b_shift_16 & 0x1f));
          i11 = 0xb4;
          font = (int *)g[0x413b];
          text = stk_11c[i4][i2][pi1[i2]];
          u13 = u5;
        }
      }
      V_FontDraw(text,font,i11,i12,u13);
      stk_1dc = stk_1dc + 0x14;
      stk_1e0 = stk_1e0 + 0x14;
      i2 = i2 + 1;
    } while (i2 < stk_17c[i4]);
  }
  return;
}
#undef stk_1f0
#undef stk_1e0
#undef stk_1dc
#undef stk_1b8
#undef stk_1b4
#undef stk_1b0
#undef stk_1ac
#undef stk_1a8
#undef stk_1a4
#undef stk_1a0
#undef stk_19c
#undef stk_198
#undef stk_194
#undef stk_190
#undef stk_18c
#undef stk_17c
#undef stk_16c
#undef stk_168
#undef stk_164
#undef stk_15c
#undef stk_14c
#undef stk_148
#undef stk_144
#undef stk_13c
#undef stk_138
#undef stk_134
#undef stk_12c
#undef stk_128
#undef stk_124
#undef stk_11c
#undef stk_10c
#undef stk_ec
#undef stk_e8
#undef stk_e4
#undef stk_e0
#undef stk_dc
#undef stk_cc
#undef stk_c8
#undef stk_c4
#undef stk_c0
#undef stk_bc
#undef stk_ac
#undef stk_a8
#undef stk_a4
#undef stk_a0
#undef stk_9c
#undef stk_8c
#undef stk_88
#undef stk_84
#undef stk_80
#undef stk_7c
#undef stk_6c
#undef stk_4c
#undef stk_48
#undef stk_44
#undef stk_40
#undef stk_3c
#undef stk_38
#undef stk_34
#undef stk_30
#undef stk_2c
#undef stk_28
#undef stk_24

/* InfoTextDraw @ 0x080a5b70, 507 bytes
 *
 * Draws formatted information text with inline markup ("[big]", "[small]",
 * "[col=r,g,b]") line by line. Used by the mode select information box.
 *
 * Parameters:
 *   arg1         char *
 *   arg2         int
 *   arg3         int
 *
 * Calls: strmatchlen, V_FontDraw
 * C library: makecol, sscanf
 * Called by: ModeSelect
 *
 * Elecbyte file: src/mugen/menus.c
 * Note: 3 data addresses refer to the data image (data/mugen_data.S).
 * Note: Locals live in `frame`, laid out as on the original stack (0x240 bytes,
 *       6 variables), because their address is taken.
 */
void InfoTextDraw(char *arg1,int arg2,int arg3)

{
  char *pc1;
  int *pi2;
  int *pi3;
  char c4;
  char c5;
  int i6;
  int i7;
  int i8;
  int i9;
  uint8_t *pu10;
  uint32_t u11;
  unsigned char frame[0x240] __attribute__((aligned(16)));
#define stk_238 (*(uint32_t *)(frame + 0x8))
#define font (*(int **)(frame + 0x14))
#define stk_228 (*(uint32_t *)(frame + 0x18))
#define stk_224 (*(int *)(frame + 0x1c))
#define stk_220 (*(int *)(frame + 0x20))
#define text (*(char (*)[524])(frame + 0x24))
  
  i9 = 0;
  pi2 = (int *)g[0x413b];
  pi3 = (int *)g[0x413a];
  stk_238 = makecol(0xff,0xff,0xff);
  c4 = *arg1;
  font = pi2;
  do {
    if (c4 == '\0') {
      return;
    }
    i8 = 0;
    while (c4 == '[') {
      pc1 = arg1 + i9 + 1;
      i6 = strmatchlen((int)pc1,(int)&str_big,4);
      if (i6 == 0) {
        i6 = strmatchlen((int)pc1,(int)&str_small_99a2,6);
        if (i6 == 0) {
          u11 = 3;
          pu10 = &str_col;
          i7 = strmatchlen((int)pc1,(int)&str_col,3);
          if (i7 == 0) {
            c4 = *pc1;
            i9 = i9 + 1;
          }
          else {
            i9 = i9 + 5;
            sscanf(arg1 + i9,"%i,%i,%i",&stk_228,&stk_224,&stk_220,pu10,u11,i6)
            ;
            stk_238 = makecol(stk_228,stk_224,stk_220);
            c4 = arg1[i9];
            c5 = '\0';
            if (c4 != '\0') {
              if (c4 == ']') {
                c5 = ']';
              }
              else {
                do {
                  i9 = i9 + 1;
                  c5 = arg1[i9];
                  if (c5 == '\0') break;
                } while (c5 != ']');
              }
            }
            c4 = '\0';
            if (c5 != '\0') {
              c4 = arg1[i9 + 1];
              i9 = i9 + 1;
            }
          }
        }
        else {
          c4 = arg1[i9 + 7];
          i9 = i9 + 7;
          font = pi3;
        }
      }
      else {
        c4 = arg1[i9 + 5];
        i9 = i9 + 5;
        font = pi2;
      }
    }
    if ((c4 != '\0') && (c4 != '\n')) {
      while( true ) {
        i9 = i9 + 1;
        text[i8] = c4;
        i8 = i8 + 1;
        c4 = arg1[i9];
        if (c4 == '\0') break;
        if ((c4 == '\n') || (0x1fd < i8)) break;
      }
    }
    text[i8] = '\0';
    if (arg1[i9] == '\n') {
      arg3 = arg3 + font[3];
    }
    V_FontDraw(text,font,arg2,arg3,stk_238);
    c4 = arg1[i9];
    if (c4 == '\n') {
      i9 = i9 + 1;
      arg3 = arg3 + 1;
      c4 = arg1[i9];
    }
  } while( true );
}
#undef stk_238
#undef font
#undef stk_228
#undef stk_224
#undef stk_220
#undef text

