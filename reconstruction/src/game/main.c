/*
 * main.c -- main program and match sequence
 * Program entry (main), Quick VS setup, the top-level loop over title,
 * select and fight, the match sequence of a game mode (GamePlay), the arcade
 * win and survival result screens, demo fight setup, and the game-state
 * queries.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/main.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* _mangled_main @ 0x0809c470, 636 bytes
 *
 * Program entry (main). It parses the command line and initialises the
 * engine (GameInit), sets up the back buffer, timer and frame rate, and
 * shows the logo storyboard. It finds the characters and stages ("Error
 * finding characters/stages in ...") and loads the select data ("Cannot load
 * char select data in ..."). It applies Quick VS options, starts the debug
 * GUI and runs MainLoop. At exit it shuts everything down (GameDeInit).
 *
 * Parameters:
 *   argc         int
 *   argv         char **
 *
 * Calls: ParseCmdLine, GameInit, V_SetBuf, W_Cls, W_Define,
 *        TimerSetFPSDelay, TimerSetTicks, TimerSetSyncFPS, PlayCutscene,
 *        EB_GUIInit, EB_GUINewWindow, EB_GUISetWinAttr, ClipboardFree,
 *        CharInfoInit, ErrorExit, InitSelectScreenMatrix, FindCharacters,
 *        QuickVSSetup, MainLoop, EB_GUIDeInit, GameDeInit
 * C library: install_mouse, strcat
 * Messages:
 *   "\nCannot load char select data in "
 *   "\nError finding characters/stages in "
 *
 * Elecbyte file: src/mugen/main.c
 * Note: decompiler flag: blocks removed as unreachable
 * Note: decompiler flag: unusual stack variable
 * Note: decompiler flag: the second decompiler pass lost the call(s) to
 *       FindCharacters,InitSelectScreenMatrix,strcat
 * Note: Written by hand from the assembly (reconstruction/overrides/).
 * Note: written by hand from the assembly at 0x0809c470-0x0809c6ec. Reason: the
 *       by-value copy of the 0x32c-byte options block (rep movsl) breaks
 *       Ghidra's stack tracking; the decompiler dropped GameInit's arguments and
 *       removed the "mode == 1" branch as unreachable. Stack layout (D0 = esp
 *       after "sub $0x344"): mode at D0+0x10 (zeroed before ParseCmdLine), opts
 *       at D0+0x14. After GameInit, esp = D0+4 (GCC 2.96 alignment rebalance),
 *       so 0xc(%esp) is mode and 0x300(%esp) is opts+0x2ec. Verified: argument
 *       order of every call, string addresses 0x8276f0b "scene", 0x8279230
 *       "Debug", 0x8279280, 0x82792c0.
 */
int _mangled_main(int argc, char **argv)
{
  int mode;
  MugenCmdLine opts;
  int *win;

  mode = 0;
  ParseCmdLine(&opts, argc, argv);
  GameInit(opts, &mode);                       /* 0x809c4b2 */
  if (g[0x104e0 / 4] != 0) {
    V_SetBuf((int *)g[0x104e0 / 4], 0);
    W_Cls(0);
  }
  V_SetBuf((int *)g[0x104d8 / 4], 0);
  W_Cls(0);
  W_Define(0, 0, V_Width - 1, V_Height - 1);
  TimerSetFPSDelay(0x1e);
  TimerSetTicks(0);
  TimerSetSyncFPS(0x3c);
  if (((char *)&opts)[0x2ec] != '\0') {        /* storyboard given on the command line */
    PlayCutscene((char *)&opts + 0x2ec, "scene");
  }
  else {
    install_mouse();
    EB_GUIInit(g[0x104d8 / 4]);
    win = EB_GUINewWindow("Debug", 10, 0x32, 300, (int *)0x3c);
    g[0x20b5c / 4] = (int)win;
    EB_GUISetWinAttr(g[0x20b5c / 4], 1);
    *(uint32_t *)(g[0x20b5c / 4] + 0x20) = 0;
    ClipboardFree(*(uint32_t **)(g[0x20b5c / 4] + 0x30));
    *(int *)(g[0x20b5c / 4] + 0x30) = g[0x20744 / 4];
    PlayCutscene((char *)g + 0x6d44, "scene");  /* logo/intro storyboard */
    if (CharInfoInit() == 0) {
      ErrorExit();
    }
    if (mode == 1) {                           /* 0x809c615: normal start, select screen */
      if (InitSelectScreenMatrix((char *)g + 0x5380) == 0) {
        strcat((char *)g + 0x20748, "\nCannot load char select data in ");
        strcat((char *)g + 0x20748, (char *)g + 0x5380);
        ErrorExit();
      }
      if (FindCharacters() == 0) {
        strcat((char *)g + 0x20748, "\nError finding characters/stages in ");
        strcat((char *)g + 0x20748, (char *)g + 0x5380);
        ErrorExit();
      }
    }
    else {
      QuickVSSetup(&opts);                     /* quick versus from the command line */
    }
    MainLoop(mode);
  }
  EB_GUIDeInit();
  GameDeInit(mode);
  return 0;
}

/* QuickVSSetup @ 0x0809c6f0, 1134 bytes
 *
 * Sets up a Quick VS match from the command line (-p1/-p2/-s...). It
 * resolves each character's .def file in chars/ (Cannot find character: %s),
 * reads its "[Info]" pal.defaults for the colour, fills the team selections,
 * the stage and the round count, and starts versus mode directly.
 *
 * Parameters:
 *   opts         MugenCmdLine *
 *
 * Text keys read: [Info], "pal.defaults"
 * Globals read: charinfo, errmsg
 * Globals written: num_chars, round_match_wins
 * Calls: splitdirfile, strmatchlen, TPReadFile, ErrorExit, TPGroupSeek,
 *        TPScanf, TPFree
 * C library: strcmp, sprintf, strcpy
 * Called by: _mangled_main
 * Messages:
 *   "Cannot find character: %s"
 *
 * Elecbyte file: src/mugen/main.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: 1 data addresses refer to the data image (data/mugen_data.S).
 * Note: Locals live in `frame`, laid out as on the original stack (0x3030 bytes,
 *       5 variables), because their address is taken.
 */
void QuickVSSetup(MugenCmdLine *opts)

{
  int *pi1;
  int i2;
  int i3;
  uint32_t u4;
  uint32_t *tp;
  int i6;
  int i7;
  uint32_t stale_ECX;
  int i8;
  int *pi9;
  MugenCmdLine *s2;
  int *pi10;
  int saved_EBP;
  int i4;
  unsigned char frame[0x3030] __attribute__((aligned(16)));
#define path (*(MugenCmdLine **)(frame + 0x0))
#define stk_302c (*(uint32_t *)(frame + 0x4))
#define dirname (*(char (*)[4096])(frame + 0x14))
#define filename (*(char (*)[4096])(frame + 0x1014))
#define filename2 (*(char (*)[4108])(frame + 0x2014))
  
  pi9 = g;
  g[0x3a60] = 1;
  pi9[0x33b9] = 1;
  pi9[0x3a64] = 0;
  pi9[0x33bd] = 0;
  pi9[0x3a62] = 0;
  pi9[0x33bb] = 0;
  stk_302c = 0;
  path = opts;
  do {
    i2 = (int)stk_302c / 2;
    i7 = (int)stk_302c % 2;
    pi10 = pi9;
    if ((char)path->mode != '\0') {
      i4 = 0;
      pi9[i7 * 0x6a7 + i2 * 5 + 0x33be] = stk_302c + 1;
      pi9[i7 * 0x6a7 + i2 * 5 + 0x33c1] = i7;
      saved_EBP = 0;
      s2 = opts;
      if (0 < (int)stk_302c) {
        do {
          i3 = strcmp((char *)path,(char *)s2);
          if (i3 == 0) {
            saved_EBP = 1;
            pi9[i7 * 0x6a7 + i2 * 5 + 0x33bf] =
                 g[(i4 / 2) * 5 + (i4 % 2) * 0x6a7 + 0x33bf];
            break;
          }
          i4 = i4 + 1;
          s2 = (MugenCmdLine *)(s2->rest + 0x3c);
        } while (i4 < (int)stk_302c);
      }
      if (saved_EBP == 0) {
        i4 = g[G_NUM_CHARS];
        i3 = g[G_CHARINFO] + i4 * 0x702c;
        pi9[i7 * 0x6a7 + i2 * 5 + 0x33bf] = i4;
        u4 = splitdirfile((char *)path,dirname,filename);
        if (dirname[0] == '\0') {
          sprintf(dirname,"chars/%s/",path,u4);
          sprintf(filename,"%s.def",path);
        }
        else {
          i6 = strmatchlen((int)dirname,(int)&str_chars_9236,5);
          if (i6 == 0) {
            sprintf(filename2,"chars/%s",dirname,filename);
            strcpy(dirname,filename2);
          }
        }
        sprintf(filename2,"%s%s",dirname,filename);
        tp = TPReadFile(filename2);
        if (tp == (uint32_t *)0x0) {
          sprintf((char *)(g + G_ERRMSG),"Cannot find character: %s",filename2,0);
          ErrorExit();
        }
        TPGroupSeek((int)tp,"Info");
        i8 = 3;
        i6 = 4;
        do {
          *(int *)(i3 + 0x5010 + i6 * 4) = i6;
          i6 = i6 + -1;
          i8 = i8 + -1;
        } while (-1 < i8);
        TPScanf((int)tp,"pal.defaults","%i,%i,%i,%i",i3 + 0x5014,i3 + 0x5018,
                i3 + 0x501c,i3 + 0x5020,stale_ECX);
        TPFree(tp);
        sprintf((char *)(i4 * 0x702c + g[G_CHARINFO] + 0x200a),dirname);
        sprintf((char *)(i4 * 0x702c + g[G_CHARINFO] + 0x100b),filename);
        saved_EBP = g[G_NUM_CHARS] + 1;
        g[G_NUM_CHARS] = saved_EBP;
      }
      pi10 = g;
      pi9[i7 * 0x6a7 + i2 * 5 + 0x33c0] =
           *(int *)(stk_302c * 4 + 0x5014 + i4 * 0x702c + g[G_CHARINFO]) + -1;
      if (pi10[stk_302c + 0x7991] != -1) {
        pi9[i7 * 0x6a7 + i2 * 5 + 0x33c0] = pi10[stk_302c + 0x7991];
      }
      i2 = pi9[i7 * 0x6a7 + 0x33bd];
      pi9[i7 * 0x6a7 + 0x33bd] = i2 + 1;
      pi10 = g;
      if (1 < i2 + 1) {
        pi9[i7 * 0x6a7 + 0x33bb] = 1;
        pi9[i7 * 0x6a7 + 0x33bc] = 1;
        pi10[0x33ae] = 0;
      }
      pi10 = g;
      pi9[i7 * 0x6a7 + 0x33ba] = pi9[i7 * 0x6a7 + 0x33ba] + 1;
      pi10[stk_302c + 0x33af] = stk_302c & 1;
      pi10[stk_302c + 0x741a] = 1;
    }
    stk_302c = stk_302c + 1;
    path = (MugenCmdLine *)(path->rest + 0x3c);
    pi9 = pi10;
    if (3 < (int)stk_302c) {
      pi9 = pi10 + 0x33bb;
      pi10 = pi10 + 0x4106;
      for (i2 = 0x17; i2 != 0; i2 = i2 + -1) {
        *pi10 = *pi9;
        pi9 = pi9 + 1;
        pi10 = pi10 + 1;
      }
      pi9 = g + 0x3a62;
      pi10 = g + 0x411d;
      for (i2 = 0x17; pi1 = g, i2 != 0; i2 = i2 + -1) {
        *pi10 = *pi9;
        pi9 = pi9 + 1;
        pi10 = pi10 + 1;
      }
      g[G_ROUND_MATCH_WINS] = *(int *)(opts->rest + 0x290);
      if (opts->rest[0xfc] != 0) {
        sprintf((char *)(pi1 + 0x805),"stages/%s.def",opts->rest + 0xfc,saved_EBP);
      }
      return;
    }
  } while( true );
}
#undef path
#undef stk_302c
#undef dirname
#undef filename
#undef filename2

/* MainLoop @ 0x0809cb60, 1469 bytes
 *
 * The top-level game loop. Shows the intro storyboard once, then repeats:
 * - mode select (or demo mode when idle);
 * - character select;
 * - building the arcade order and starting the precache loader;
 * - GamePlay;
 * - the ending, game over and credits storyboards as the result requires.
 *
 * With `interactive` = 0 (Quick VS), it runs one match and returns.
 *
 * Parameters:
 *   arg1         int
 *
 * Globals read: files_intro_storyboard, demo_mode, slct_coop_side,
 *               charinfo, num_chars, demo_mode_vsscreen_enabled
 * Calls: IntroScreen, GameResetPersistVars, ModeSelect, BGMFree,
 *        DemoFightSetup, CharacterSelectScreen, ArcadeListBuild,
 *        PrecacheRequestCurArcadeTeam, PrecacheStart,
 *        SurvivalBuildRandomTeam, TrainingMenuReset, ArcadeListGetCurrent,
 *        TimerSetSyncFPS, fileexist, PlayCutscene, VersusScreen, GamePlay,
 *        ErrorExit, ArcadeListGetCurSize, ArcadeListEnemiesLeft,
 *        PrecacheIsRunning, PrecacheRequestCancel, PrecacheFinish,
 *        CharStopUsingPalAll
 * C library: random, strcpy, _alemu_stricmp, sprintf
 * Called by: _mangled_main
 *
 * Elecbyte file: src/mugen/main.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x1020 bytes,
 *       1 variables), because their address is taken.
 */
void MainLoop(int arg1)

{
  char *src;
  bool b1;
  int *pi2;
  bool b3;
  int i4;
  long l5;
  uint32_t stale_var;
  uint32_t u6;
  int *pi7;
  unsigned char frame[0x1020] __attribute__((aligned(16)));
#define path (*(char (*)[4108])(frame + 0x4))
  
L_0809d0ad:
  if (((arg1 != 0) && ((char)g[G_FILES_INTRO_STORYBOARD] != '\0')) && (g[0x2351] == 0)) {
    IntroScreen();
    g[0x2351] = 1;
  }
L_0809d0dd:
  GameResetPersistVars();
  if (arg1 == 0) {
    g[0x33b5] = 1;
  }
  else {
    ModeSelect();
    if (g[0x33b5] == 10) {
      BGMFree(g + 0x6efa);
      return;
    }
  }
L_0809cb85:
  GameResetPersistVars();
  pi7 = g;
  g[0x7543] = 0;
  if ((arg1 == 0) || ((pi7[0x74e8] != 0 && (pi7[0x74eb] == 0)))) {
    if (g[G_DEMO_MODE] != 0) {
      DemoFightSetup();
      BGMFree(g + 0x6efa);
    }
  }
  else {
    i4 = CharacterSelectScreen(pi7[0x33b5],pi7[0x33b6]);
    if (i4 == 0) goto L_0809d0dd;
    if ((g[0x33b3] != 0) && (ArcadeListBuild(), g[0x14d0] != 0)) {
      PrecacheRequestCurArcadeTeam();
      PrecacheStart();
    }
    if (g[G_SLCT_COOP_SIDE] != 0) {
      SurvivalBuildRandomTeam(g + (2 - g[G_SLCT_COOP_SIDE]) * 0x6a7 + 0x33b8,2 - g[G_SLCT_COOP_SIDE],1);
    }
  }
  if (arg1 == 0) {
    if ((char)g[0x805] != '\0') goto L_0809cd09;
    pi7 = g + 0x7dc4;
  }
  else {
    if ((char)g[0x805] != '\0') goto L_0809cd09;
    l5 = random();
    pi7 = (int *)(g[G_CHARINFO] + 0x3009 + (l5 % g[G_NUM_CHARS]) * 0x702c);
  }
  strcpy((char *)(g + 0x805),(char *)pi7);
L_0809cd09:
  TrainingMenuReset();
  do {
    pi2 = g;
    pi7 = g + 0x7543;
    i4 = g[0x7544];
    *(uint8_t *)((int)g + 0x3013) = 0;
    pi2[0x7543] = *pi7 + 1;
    pi2[0x7544] = i4 + 1;
    b1 = false;
    if ((g[0x33b3] != 0) && (i4 = ArcadeListGetCurrent(), i4 != -1)) {
      i4 = g[G_CHARINFO] + i4 * 0x702c;
      strcpy((char *)(g + 0x805),(char *)(i4 + 0x3009));
      strcpy((char *)((int)g + 0x3013),(char *)(i4 + 0x4008));
    }
    if (((char)g[0x805] == '\0') ||
       (i4 = _alemu_stricmp((char *)(g + 0x805),"random"), i4 == 0)) {
      if (g[0x33ad] < 1) {
        pi7 = g + 0x7dc4;
      }
      else {
        l5 = random();
        pi7 = (int *)(g[0x33ac] + (l5 % g[0x33ad]) * 0x1054);
      }
      strcpy((char *)(g + 0x805),(char *)pi7);
    }
    if ((g[0x33b3] != 0) && (g[0x7543] == 1)) {
      TimerSetSyncFPS(0x3c);
      if (g[g[0x33b3] * 0x6a7 + 0x2d18] != -1) {
        i4 = g[g[0x33b3] * 0x6a7 + 0x2d18] * 0x702c;
        src = (char *)(i4 + g[G_CHARINFO] + 0x5028);
        sprintf(path,"%s/%s",i4 + g[G_CHARINFO] + 0x200a,src);
        b3 = fileexist(path);
        if (ZEXT8(b3) == 0) {
          strcpy(path,src);
        }
        PlayCutscene(path,"scene");
      }
    }
    while( true ) {
      if ((arg1 != 0) &&
         (((g[G_DEMO_MODE] == 0 || (g[G_DEMO_MODE_VSSCREEN_ENABLED] != 0)) && (u6 = VersusScreen(), u6 == 0))))
      goto L_0809d066;
      i4 = GamePlay();
      if (i4 == 0) {
        ErrorExit();
      }
      if (g[0x4134] == 0) break;
      GameResetPersistVars();
      i4 = CharacterSelectScreen(g[0x33b5],g[0x33b6]);
      if (i4 == 0) {
        g[0x4134] = 0;
        goto L_0809d0dd;
      }
      g[0x4134] = 0;
      i4 = ArcadeListGetCurrent();
      if (i4 != -1) {
        i4 = g[G_CHARINFO] + i4 * 0x702c;
        strcpy((char *)(g + 0x805),(char *)(i4 + 0x3009));
        strcpy((char *)((int)g + 0x3013),(char *)(i4 + 0x4008));
      }
      g[0x7544] = g[0x7544] + 1;
    }
    if (g[0x33b3] != 0) {
      g[0x14bb] = g[0x14bb] + 1;
      i4 = ArcadeListGetCurSize();
      g[0x14ba] = g[0x14ba] + i4;
      i4 = ArcadeListEnemiesLeft();
      if (i4 == 0) break;
      b1 = true;
    }
    if ((!b1) || (g[0x4135] != 0)) break;
  } while( true );
L_0809d066:
  i4 = PrecacheIsRunning();
  if (i4 != 0) {
    PrecacheRequestCancel();
    PrecacheFinish();
  }
  if (arg1 == 0) {
    return;
  }
  CharStopUsingPalAll();
  if (((g[0x33b3] != 0) || (g[G_DEMO_MODE] != 0)) || (g[G_SLCT_COOP_SIDE] != 0)) goto L_0809d0ad;
  goto L_0809cb85;
}
#undef path

/* GamePlay @ 0x0809d120, 1282 bytes
 *
 * Plays a whole match sequence for the selected mode. It loads the stage and
 * fight data and starts the stage music, then loops rounds (GameLoop) until
 * the match ends. It handles continues, arcade progression and the
 * arcade/survival result screens, and unloads everything at the end. Returns
 * when the player quits or the sequence ends.
 *
 * Globals read: misc_unloadsystem, gamespeed, camera_startx,
 *               camera_starty, continue_screen_enabled, charinfo,
 *               win_screen_enabled, default_ending_enabled,
 *               default_ending_storyboard, end_credits_enabled,
 *               end_credits_storyboard, survival_results_screen_enabled,
 *               sound_linux_masterwavvolume, sound_linux_midivolume
 * Calls: GameUnloadSystemSprSnd, LogPreMatch, GameLoadStage,
 *        GameStgInitFightData, GameSetVol, BGMStart, KBBufferClear,
 *        PadPoll, PadBufClear, UInpRefreshFlags, UInpBufClear,
 *        GameMatchReset, TimerSetSyncFPS, CameraMoveAbs, GameLoop,
 *        PalGrpResetPalette, SndIDStop, LogMatch, BGMPause,
 *        ContinueScreen, BGMResume, ArcadeListEnemiesLeft,
 *        ArcadeListGetCurSize, BGMFree, ...
 * C library: memset, strcpy
 * Called by: MainLoop
 *
 * Elecbyte file: src/mugen/main.c
 * Note: 2 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x4030 bytes,
 *       6 variables), because their address is taken.
 */
uint32_t GamePlay(void)

{
  int *pi1;
  int i2;
  int i3;
  uint8_t b4;
  bool b5;
  int i6;
  int *filename;
  uint32_t u8;
  uint32_t stale_var;
  uint32_t stale_var_00;
  int i9;
  int i10;
  uint32_t *pu11;
  uint32_t *pu12;
  unsigned char frame[0x4030] __attribute__((aligned(16)));
#define stk_4024 (*(int *)(frame + 0xc))
#define stk_4020 (*(int *)(frame + 0x10))
#define path (*(char (*)[4096])(frame + 0x14))
#define path2 (*(char (*)[4096])(frame + 0x1014))
#define path3 (*(char (*)[4096])(frame + 0x2014))
#define stk_101c (*(int (*)[1027])(frame + 0x3014))
  
  memset(path3,0,0xfff);
  memset(path2,0,0xfff);
  memset(path,0,0xfff);
  filename = g + G_MISC_UNLOADSYSTEM;
  g[0x52bd] = 1;
  if (*filename != 0) {
    GameUnloadSystemSprSnd();
  }
  LogPreMatch();
  g[0x81c9] = Ticks;
  i6 = GameLoadStage();
  if ((i6 == 0) || (i6 = GameStgInitFightData(), filename = g, i6 == 0)) {
L_0809d30d:
    u8 = 0;
  }
  else {
    g[0x81c9] = Ticks - g[0x81c9];
    GameSetVol(filename[0x6ef5],filename[0x6ef7]);
    BGMStart(g + 0x10aa);
    while( true ) {
      i6 = 1;
      KBBufferClear();
      PadPoll();
      PadBufClear();
      UInpRefreshFlags();
      UInpBufClear();
      filename = g + 0x33b8;
      do {
        *filename = 0;
        filename = filename + 0x6a7;
        i6 = i6 + -1;
      } while (-1 < i6);
      stk_4020 = 0xcee0;
      stk_4024 = 0;
      i10 = 0x10410;
      i6 = 1;
      do {
        i2 = i10 + 8;
        i10 = i10 + 0x5c;
        i3 = stk_4024 + *(int *)(stk_4020 + (int)g) * 0x5c;
        stk_4024 = stk_4024 + 0x1a9c;
        pu11 = (uint32_t *)(i3 + 0xceec + (int)g);
        pu12 = (uint32_t *)(i2 + (int)g);
        for (i9 = 0x17; i9 != 0; i9 = i9 + -1) {
          *pu12 = *pu11;
          pu11 = pu11 + 1;
          pu12 = pu12 + 1;
        }
        stk_4020 = stk_4020 + 0x1a9c;
        i6 = i6 + -1;
      } while (-1 < i6);
      GameMatchReset();
      i6 = g[G_GAMESPEED] * 5 + g[0x756f];
      if (i6 < 10) {
        i6 = 10;
      }
      TimerSetSyncFPS(i6);
      CameraMoveAbs((float)g[G_CAMERA_STARTX],(float)g[G_CAMERA_STARTY]);
      filename = g;
      g[0x74e0] = 1;
      filename[0x74df] = 1;
      i6 = GameLoop(4);
      if (i6 == 0) goto L_0809d30d;
      PalGrpResetPalette();
      SndIDStop(-1);
      LogMatch();
      filename = g;
      if (((g[0x7546] == 0) || (g[0x4135] != 0)) || (g[0x33b3] == 0)) goto L_0809d55a;
      if (g[0x7545] == g[0x33b3]) break;
      GameSetVol(0,0);
      BGMPause(g + 0x10aa);
      filename = g;
      pi1 = g + G_CONTINUE_SCREEN_ENABLED;
      g[0x4135] = 1;
      if (*pi1 == 0) {
        if (filename[0x2f94] != 0) {
          strcpy(path,(char *)(filename + 0x2f95));
          filename = g;
          g[0x2351] = 0;
        }
        goto L_0809d55a;
      }
      b4 = ContinueScreen();
      filename = g;
      if ((ZEXT8(b4) == 0) || (pi1 = g + 0x4134, g[0x4135] = 0, *pi1 != 0))
      goto L_0809d55a;
      GameSetVol(filename[0x6ef5],filename[0x6ef7]);
      BGMResume(g + 0x10aa);
    }
    i6 = ArcadeListEnemiesLeft();
    i10 = ArcadeListGetCurSize();
    filename = g;
    if (i6 <= i10) {
      BGMFree(g + 0x10aa);
      i6 = g[G_CHARINFO] + g[g[0x33b3] * 0x6a7 + 0x2d18] * 0x702c;
      filename = (int *)(i6 + 0x6027);
      if (*(char *)(i6 + 0x6027) == '\0') {
        if (g[G_WIN_SCREEN_ENABLED] != 0) {
          ArcadeWinScreen();
        }
        if (g[G_DEFAULT_ENDING_ENABLED] != 0) {
          filename = g + G_DEFAULT_ENDING_STORYBOARD;
          goto L_0809d500;
        }
      }
      else {
        joindirfile((char *)stk_101c,(char *)(i6 + 0x200a),(char *)filename);
        b5 = fileexist((char *)stk_101c);
        if (ZEXT8(b5) != 0) {
          filename = stk_101c;
        }
L_0809d500:
        strcpy(path3,(char *)filename);
      }
      if (g[G_END_CREDITS_ENABLED] != 0) {
        strcpy(path2,(char *)(g + G_END_CREDITS_STORYBOARD));
      }
      g[0x2351] = 0;
      filename = g;
    }
L_0809d55a:
    if (((filename[0x7546] != 0) && (filename[0x4135] == 0)) &&
       ((filename[0x33b4] != 0 && (BGMFree(filename + 0x10aa), g[G_SURVIVAL_RESULTS_SCREEN_ENABLED] != 0)))) {
      SurvivalResultsScreen();
    }
    PalGrpClear();
    GameStgDeInitFightData();
    GameUnloadStage();
    TimerSetSyncFPS(0x3c);
    PlayCutscene(path3,"scene");
    PlayCutscene(path2,"scene");
    PlayCutscene(path,"scene");
    GameReloadSystemSprSnd();
    GameSetVol(g[G_SOUND_LINUX_MASTERWAVVOLUME],g[G_SOUND_LINUX_MIDIVOLUME]);
    u8 = 1;
  }
  return u8;
}
#undef stk_4024
#undef stk_4020
#undef path
#undef path2
#undef path3
#undef stk_101c

/* ArcadeWinScreen @ 0x0809d630, 505 bytes
 *
 * Shows the arcade "win" screen after a match: resets the round with the
 * winner in its win pose and runs the screen for its time.
 *
 * Player fields written: pos_x, facing
 * Globals read: camera_startx, camera_starty, slot_first, slot_last
 * Calls: TimerSetSyncFPS, GameRoundReset, CameraMoveAbs, PlayerEnableSet,
 *        PlayerReset, PlayerChangeState, GameLoop, PalGrpResetPalette,
 *        SndIDStop
 * Called by: GamePlay
 *
 * Elecbyte file: src/mugen/main.c
 * Note: Returns nothing (the original left only stale register values).
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void ArcadeWinScreen(void)

{
  float80 f1;
  bool b2;
  uint32_t stale_EAX;
  int *player;
  int i4;
  int player2;
  int *player3;
  int i7;
  
  g[0x52bd] = 0;
  TimerSetSyncFPS(0x3c);
  GameRoundReset();
  CameraMoveAbs((float)g[G_CAMERA_STARTX],(float)g[G_CAMERA_STARTY]);
  player2 = g[G_SLOT_FIRST];
  player = g;
  if (player2 <= g[G_SLOT_LAST]) {
    i7 = player2 * 4 + 0x1cf60;
    do {
      i4 = *(int *)(i7 + 4 + (int)player);
      if ((i4 == 0) || (b2 = true, *(int *)(i4 + 0x158) == 0)) {
        b2 = false;
      }
      if (b2) {
        PlayerEnableSet(player2,0);
        player = g;
      }
      player2 = player2 + 1;
      i7 = i7 + 4;
    } while (player2 <= player[0x745a]);
  }
  if (player[0x33b3] == 2) {
    player3 = (int *)player[0x73db];
    player = (int *)player[0x73dd];
  }
  else {
    player3 = (int *)player[0x73da];
    player = (int *)player[0x73dc];
  }
  if (player3 != (int *)0x0) {
    PlayerEnableSet(player3[2],1);
    PlayerReset(player3);
    PlayerChangeState((int)player3,0xb4);
    f1 = (float)(V_Width / 2 + g[0x7311]);
    player3[PL_POS_X] = BITS_F2I(int, f1);
    if (player != (int *)0x0) {
      player3[PL_POS_X] = BITS_F2I(int, (f1 - (float)(player3[PL_FACING] * 0x28)));
    }
    player3[0x8f] = 1;
  }
  if (player != (int *)0x0) {
    PlayerEnableSet(player[2],1);
    PlayerReset(player);
    PlayerChangeState((int)player,0xb4);
    player2 = g[0x7311];
    i4 = V_Width / 2;
    i7 = player3[PL_FACING];
    player[PL_FACING] = -i7;
    player[0x8f] = 1;
    player[PL_POS_X] = BITS_F2I(int, (float)(i4 + player2 + i7 * 0x28));
  }
  player = g;
  g[0x7541] = 0;
  player[0x7542] = 0;
  player[0x74e0] = 0;
  player[0x74df] = 1;
  GameLoop(5);
  PalGrpResetPalette();
  SndIDStop(-1);
  return;
}

/* SurvivalResultsScreen @ 0x0809d830, 552 bytes
 *
 * Shows the survival mode results (number of rounds won) with the players in
 * their poses.
 *
 * Player fields written: pos_x, facing
 * Globals read: round_no, camera_startx, camera_starty, slot_first,
 *               slot_last
 * Calls: TimerSetSyncFPS, GameRoundReset, CameraMoveAbs, PlayerEnableSet,
 *        PlayerReset, PlayerChangeState, GameLoop, PalGrpResetPalette,
 *        SndIDStop
 * Called by: GamePlay
 *
 * Elecbyte file: src/mugen/main.c
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void SurvivalResultsScreen(void)

{
  int i1;
  float80 f2;
  bool b3;
  int *pi4;
  int *player;
  int player2;
  int *player3;
  int i8;
  int i9;
  
  pi4 = g;
  i9 = g[g[0x33b4] + G_ROUND_NO];
  g[0x52bd] = 0;
  TimerSetSyncFPS(0x3c);
  GameRoundReset();
  CameraMoveAbs((float)g[G_CAMERA_STARTX],(float)g[G_CAMERA_STARTY]);
  player2 = g[G_SLOT_FIRST];
  player = g;
  if (player2 <= g[G_SLOT_LAST]) {
    i8 = player2 * 4 + 0x1cf60;
    do {
      i1 = *(int *)(i8 + 4 + (int)player);
      if ((i1 == 0) || (b3 = true, *(int *)(i1 + 0x158) == 0)) {
        b3 = false;
      }
      if (b3) {
        PlayerEnableSet(player2,0);
        player = g;
      }
      player2 = player2 + 1;
      i8 = i8 + 4;
    } while (player2 <= player[0x745a]);
  }
  if (player[0x33b4] == 2) {
    player3 = (int *)player[0x73db];
    player = (int *)player[0x73dd];
  }
  else {
    player3 = (int *)player[0x73da];
    player = (int *)player[0x73dc];
  }
  i9 = ((pi4[0x2b92] <= i9) - 1 & 0xfffffff6) + 0xb4;
  if (player3 != (int *)0x0) {
    PlayerEnableSet(player3[2],1);
    PlayerReset(player3);
    PlayerChangeState((int)player3,i9);
    f2 = (float)(V_Width / 2 + g[0x7311]);
    player3[PL_POS_X] = BITS_F2I(int, f2);
    if (player != (int *)0x0) {
      player3[PL_POS_X] = BITS_F2I(int, (f2 - (float)(player3[PL_FACING] * 0x28)));
    }
    player3[0x8f] = 1;
  }
  if (player != (int *)0x0) {
    PlayerEnableSet(player[2],1);
    PlayerReset(player);
    PlayerChangeState((int)player,i9);
    i9 = g[0x7311];
    player2 = player3[PL_FACING];
    i8 = V_Width / 2;
    player[PL_FACING] = -player2;
    player[0x8f] = 1;
    player[PL_POS_X] = BITS_F2I(int, (float)(i8 + i9 + player2 * 0x28));
  }
  pi4 = g;
  g[0x7541] = 0;
  pi4[0x7542] = 0;
  pi4[0x74e0] = 0;
  pi4[0x74df] = 1;
  GameLoop(6);
  PalGrpResetPalette();
  SndIDStop(-1);
  return;
}

/* DemoFightSetup @ 0x0809da60, 410 bytes
 *
 * Picks random characters and colours for a demo (attract mode) fight
 * between two AI players.
 *
 * Globals read: num_chars
 * Calls: CharReservePal
 * C library: random
 * Called by: MainLoop
 *
 * Elecbyte file: src/mugen/main.c
 */
void DemoFightSetup(void)

{
  uint32_t u1;
  long l2;
  uint32_t u3;
  int i4;
  int pal;
  int i6;
  uint32_t u7;
  int *pi8;
  int *pi9;
  
  pi8 = g;
  g[0x33ae] = 0;
  pi8[0x33b3] = 0;
  pi8[0x3a60] = 1;
  pi8[0x33b9] = 1;
  pi8[0x3a64] = 0;
  pi8[0x33bd] = 0;
  pi8[0x3a62] = 0;
  pi8[0x33bb] = 0;
  u7 = 0;
  do {
    pi8 = g;
    i6 = (int)u7 / 2;
    i4 = (int)u7 % 2;
    u1 = u7 + 1;
    g[i4 * 0x6a7 + i6 * 5 + 0x33c1] = i4;
    pi8[i4 * 0x6a7 + i6 * 5 + 0x33be] = u1;
    l2 = random();
    pal = l2 % g[G_NUM_CHARS];
    pi8[i4 * 0x6a7 + i6 * 5 + 0x33bf] = pal;
    l2 = random();
    u3 = CharReservePal(l2 % 0xc,pal);
    pi8[i4 * 0x6a7 + i6 * 5 + 0x33c0] = u3;
    pal = pi8[i4 * 0x6a7 + 0x33bd];
    pi8[i4 * 0x6a7 + 0x33bd] = pal + 1;
    pi9 = g;
    if (1 < pal + 1) {
      pi8[i4 * 0x6a7 + 0x33bb] = 1;
      pi8[i4 * 0x6a7 + 0x33bc] = 1;
      pi9[0x33ae] = 0;
    }
    pi8[i4 * 0x6a7 + 0x33ba] = pi8[i4 * 0x6a7 + 0x33ba] + 1;
    pi8 = g;
    g[u7 + 0x33af] = u7 & 1;
    pi8[u7 + 0x741a] = 1;
    u7 = u1;
  } while ((int)u1 < 2);
  *(uint8_t *)(pi8 + 0x805) = 0;
  pi8 = g + 0x33bb;
  pi9 = g + 0x4106;
  for (pal = 0x17; pal != 0; pal = pal + -1) {
    *pi9 = *pi8;
    pi8 = pi8 + 1;
    pi9 = pi9 + 1;
  }
  pi8 = g + 0x3a62;
  pi9 = g + 0x411d;
  for (pal = 0x17; pal != 0; pal = pal + -1) {
    *pi9 = *pi8;
    pi8 = pi8 + 1;
    pi9 = pi9 + 1;
  }
  return;
}

/* ContinueScreen @ 0x0809dc00, 5 bytes
 *
 * Shows the continue screen (ContinueScreenLoop).
 *
 * Calls: ContinueScreenLoop
 * Called by: GamePlay
 *
 * Elecbyte file: src/mugen/main.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to AnimPerA
 *       rrayDrawGrp,AnimPerArrayUpdate,AnimUpdate,BGArrayUpdate,BGMPoll,DrawToSc
 *       reen,FrameSkipReset,FrameSkipUpdate,GameBGDraw,GameFGDraw,GameResetPersi
 *       stVars,GameRoundReset,GlobalInputUpdate,KBBufferClear,KBIMenuGetKey,KBPo
 *       ll,KBgetchraw,KBkbhit,MasterPalFinishedDraw,MasterPalMul,MasterPalProces
 *       sChanges,PRSprArrayClear,PRSprArrayDraw,PadBufClear,PadGet,PadHit,PadPol
 *       l,PalGrpMakeFlag,PalGrpResetPalette,PalGrpSetMul,PlayerChangeState,Playe
 *       rDrawAnim,PlayerDrawShadow,PlayerReset,PlayerUpdate,TimerSetSyncFPS,Time
 *       rWaitSync,UInpBufClear,UInpGet,UInpHit,UInpRefreshFlags,VRetrace,V_FontD
 *       raw,V_FontDrawCenter,V_FontDrawRight,V_SetBuf
 */
uint8_t ContinueScreen(void)

{
  uint8_t b1;
  
  b1 = ContinueScreenLoop();
  return b1;
}

/* GameModeInFightScreen @ 0x0809dc10, 23 bytes
 *
 * Returns true while the game state is one of the fight screens (states
 * 4-7).
 *
 * Called by: DrawToScreen, ExplodDraw
 *
 * Elecbyte file: src/mugen/main.c
 */
bool GameModeInFightScreen(void)

{
  return g[0x33b7] - 4U < 4;
}

/* GameModeInPassiveFightScreen @ 0x0809dc30, 23 bytes
 *
 * Returns true in the fight screens where players have no control (states
 * 5-7: intro, round over, win).
 *
 * Called by: CameraMoveP, GameLoop, GameUpdate, PlayerKBUpdate,
 *            PlayerSCtrlApplyElem
 *
 * Elecbyte file: src/mugen/main.c
 */
bool GameModeInPassiveFightScreen(void)

{
  return g[0x33b7] - 5U < 3;
}

