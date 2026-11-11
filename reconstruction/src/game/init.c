/*
 * init.c -- start-up and shutdown
 * Engine initialisation and shutdown, input setup, fight screen data
 * loading, game buffers, music records and window switch callbacks.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/init.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* CloseAllFunc @ 0x08098c50, 16 bytes
 *
 * Empty close-button handler.
 *
 * Elecbyte file: src/mugen/init.c
 */
void CloseAllFunc(void)

{
  g[0x4135] = 1;
  return;
}

/* GameInit @ 0x08098c60, 1764 bytes
 *
 * Starts the engine. Steps, with the console messages they print:
 * - initialise the library (ElecInit) and allocate the game variables
 * ("Can't allocate game variables.");
 * - read data/mugen.cfg ("Error reading data/mugen.cfg");
 * - start the timer;
 * - start the keyboard with repeat and LEDs, the default keys and the
 * unified input ("Initializing keyboard.", "Can't init input");
 * - start sound ("Initializing sound...", "ok", "no wave device found.", "no
 * midi device found.", "sound is disabled") and MP3;
 * - start graphics ("Initializing graphics.") with the configured width,
 * height and depth. If that mode fails, the console asks "Switch to
 * 640x480x16bits? (y/n)" and retries with that mode; otherwise it stops
 * ("Unable to initialize graphics for M.U.G.E.N").
 * - set up the game buffers and fonts and load the motif (GameLoadSystem).
 *
 * Parameters:
 *   opts         MugenCmdLine
 *   mode         int *
 *
 * Globals read: errmsg, sound_linux_wavchannels, sound_linux_playmp3,
 *               video_linux_width, video_linux_height, video_linux_depth,
 *               sound_linux_masterwavvolume
 * Globals written: speedtest, difficulty, gamespeed
 * Calls: ElecInit, ecalloc, GameConfigRead, ErrorExit, TimerInit, KBInit,
 *        KBBufferChange, KBRepeatSet, KBLEDLockSet, KBLEDSet,
 *        GameDefKeyInit, UInpInit, ErrorExitM, SndSetMode, SndInit,
 *        ErrorSet, MP3Init, G_Init, G_SetRenderMode, G_SetMode,
 *        KBBufferClear, KBgetchraw, G_SetRGBtoBGR, G_SetBlitMode, ...
 * C library: printf, exit, strcat, strcpy, fopen, fclose, fflush, strlen,
 *            _alemu_stricmp
 * Called by: _mangled_main
 * Messages:
 *   "Can\'t allocate game variables.\n\n"
 *   "\nError reading data/mugen.cfg"
 *   "Initializing keyboard.\n"
 *   "Can\'t init input"
 *   "Initializing sound..."
 *   "sound is disabled\n"
 *
 * Elecbyte file: src/mugen/init.c
 * Note: decompiler flag: stack slots read outside the declared parameters
 *       (entry_stack variables)
 * Note: decompiler flag: the second decompiler pass lost the call(s) to
 *       builtin_strncpy
 * Note: Structures passed by value: opts, mode.
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: 2 exact-text site patches (see SITE_PATCHES in
 *       tools/build_source_tree.py)
 */
void GameInit(MugenCmdLine opts, int *mode)
{
  int *pi1;
  bool b2;
  int *mem;
  int i4;
  FILE *stream;
  uint32_t stale_var;
  uint32_t u5;
  size_t s6;
  uint32_t *pu7;
  uint32_t *pu8;
  uint32_t u9;
  int *pi10;
  char *pc11;
  
  ElecInit();
  if (*(generic_fn **)(system_driver + 0x20) != (generic_fn *)0x0) {
    (**(generic_fn **)(system_driver + 0x20))("M.U.G.E.N");
  }
  mem = (int *)ecalloc(1,0x20b60);
  if (mem == (int *)0x0) {
    printf("Can\'t allocate game variables.\n\n");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  g = mem;
  i4 = GameConfigRead("data/mugen.cfg");
  if (i4 == 0) {
    strcat((char *)(g + G_ERRMSG),"\nError reading data/mugen.cfg");
    ErrorExit();
  }
  mem = g;
  if ((*(int *)((char *)&opts + 0x28c)) != 0) {
    g[0x755f] = 1;
    mem[0x7563] = 0;
    mem[0x7561] = 0;
    mem[0x7560] = 0;
    mem[0x7562] = 0;
  }
  mem = g;
  if ((*(int *)((char *)&opts + 0x184)) != 0) {
    g[0x758c] = 1;
    strcpy((char *)(mem + 0x758d),((char *)&opts + 0x188));
    stream = fopen((char *)(g + 0x758d),"wt");
    if (stream != (FILE *)0x0) {
      fclose(stream);
    }
  }
  mem = (int *)((char *)&opts + 0x298);
  pi10 = g + 0x798d;
  for (i4 = 0x11; pi1 = g, i4 != 0; i4 = i4 + -1) {
    *pi10 = *mem;
    mem = mem + 1;
    pi10 = pi10 + 1;
  }
  g[G_SPEEDTEST] = (*(int *)((char *)&opts + 0x2e4));
  pi1[0x82d6] = (*(int *)((char *)&opts + 0x2e8));
  pi1[0x799d] = (*(int *)((char *)&opts + 0x290));
  if ((*(char *)((char *)&opts + 0x40)) == '\0') {
    *mode = 1;
  }
  else {
    pi1[0x81cc] = 1;
  }
  TimerInit(0xb4);
  printf("Initializing keyboard.\n");
  KBInit();
  KBBufferChange(2);
  KBRepeatSet(0,0);
  KBFilterRelease = 0;
  KBLEDLockSet(1);
  KBLEDSet(0);
  GameDefKeyInit();
  i4 = UInpInit();
  if (i4 == 0) {
    ErrorExitM("Can\'t init input");
  }
  printf("Initializing sound...");
  if ((*(int *)((char *)&opts + 0x288)) != 0) {
    g[0x6ef3] = 0;
    SndSetMode(0);
    printf("sound is disabled\n");
  }
  if (g[0x6ef3] != 0) {
    i4 = SndInit(g[0x755b],g[0x755c],g[G_SOUND_LINUX_WAVCHANNELS]);
    if (i4 == 0) {
      i4 = SndInit(g[0x755b],0,g[G_SOUND_LINUX_WAVCHANNELS]);
      if (i4 == 0) {
        i4 = SndInit(0,g[0x755c],g[G_SOUND_LINUX_WAVCHANNELS]);
        if (i4 == 0) {
          g[0x6ef3] = 0;
          SndSetMode(0);
          pc11 = "failed to init hardware.\n";
        }
        else {
          pc11 = "no wave device found.\n";
        }
      }
      else {
        pc11 = "no midi device found.\n";
      }
    }
    else {
      SndSetMode(1);
      pc11 = "ok\n";
    }
    printf(pc11);
    ErrorSet(0);
    if (g[G_SOUND_LINUX_PLAYMP3] != 0) {
      MP3Init();
    }
  }
  printf("Initializing graphics.\n");
  b2 = G_Init();
  if (ZEXT8(b2) == 0) {
    ErrorExit();
  }
  u5 = g[0x7556];
  i4 = G_SetRenderMode(0);
  if (i4 == 0) {
    ErrorExit();
  }
  i4 = G_SetMode(u5,g[G_VIDEO_LINUX_WIDTH],g[G_VIDEO_LINUX_HEIGHT],g[G_VIDEO_LINUX_DEPTH]);
  if (i4 == 0) {
    if (((g[G_VIDEO_LINUX_WIDTH] == 0x280) && (g[G_VIDEO_LINUX_HEIGHT] == 0x1e0)) && (g[G_VIDEO_LINUX_DEPTH] == 0x10)) {
      ErrorExit();
    }
    else {
      printf("\nError: Can\'t change video mode to %ix%ix%ibits\n",g[G_VIDEO_LINUX_WIDTH],g[G_VIDEO_LINUX_HEIGHT],g[G_VIDEO_LINUX_DEPTH]);
      printf("Switch to 640x480x16bits? (y/n)\n\n");
      fflush((FILE *)stdout);
      KBBufferClear();
      do {
        u5 = KBgetchraw();
      } while ((u5 & 0x100) != 0);
      if (u5 != 0x15) {
        ErrorExit();
      }
      i4 = G_SetMode(0,0x280,0x1e0,0x10);
      if (i4 == 0) {
        ErrorExitM("Unable to initialize graphics for M.U.G.E.N");
      }
    }
  }
  if (g[G_VIDEO_LINUX_DEPTH] == 0x20) {
    G_SetRGBtoBGR(1);
  }
  if (g[0x7557] != 0) {
    G_SetBlitMode(g[0x7557],1);
  }
  g[0x74e7] = 1;
  SwitchCallbacksInit();
  i4 = GameVarInit();
  if (i4 == 0) {
    ErrorExit();
  }
  strcpy((char *)((int)g + 0xfff),(char *)g);
  mem = g;
  pc11 = (char *)((int)g + 0xfff);
  s6 = strlen(pc11);
  if (*(char *)((int)mem + s6 + 0xffe) == '\\') {
    s6 = strlen(pc11);
    *(uint8_t *)((int)mem + s6 + 0xffe) = 0;
    mem = g;
  }
  s6 = strlen((char *)((int)mem + 0xfff));
  if (*(char *)(s6 + 0xffe + (int)mem) != '/') {
    strcat((char *)((int)mem + 0xfff),"/");
  }
  i4 = GameVarLoadFonts();
  if (i4 == 0) {
    ErrorExit();
  }
  GameResetOptions();
  GameLoadOptions();
  if (0 < (*(int *)((char *)&opts + 0x2dc))) {
    g[G_DIFFICULTY] = (*(int *)((char *)&opts + 0x2dc));
  }
  if ((*(int *)((char *)&opts + 0x2e0)) + 9U < 0x13) {
    g[G_GAMESPEED] = (*(int *)((char *)&opts + 0x2e0));
  }
  mem = g;
  if ((*(char *)((char *)&opts + 0x140)) == '\0') goto L_080992ce;
  *(uint32_t *)((int)g + 0x15aff) = 0x61746164;
  *(uint16_t *)((int)mem + 0x15b03) = 0x2f;
  pu7 = (uint32_t *)((char *)&opts + 0x140);
  do {
    pu8 = pu7;
    pu7 = pu8 + 1;
    u5 = *pu8 + 0xfefefeff & (*pu8 ^ 0xffffffff);
    u9 = u5 & 0x80808080;
  } while (u9 == 0);
  if ((u5 & 0x8080) == 0) {
    u9 = u9 >> 0x10;
    pu7 = (uint32_t *)((int)pu8 + 6);
  }
  pu8 = (uint32_t *)((char *)&opts + 0x140);
  if ((int)pu7 + ((-3 - (uint32_t)CARRY1((uint8_t)u9,(uint8_t)u9)) - (int)((char *)&opts + 0x140)) < 4) {
L_08099294:
    strcat(((char *)&opts + 0x140),"/system.def");
  }
  else {
    do {
      pu7 = pu8;
      pu8 = pu7 + 1;
      u5 = *pu7 + 0xfefefeff & (*pu7 ^ 0xffffffff);
      u9 = u5 & 0x80808080;
    } while (u9 == 0);
    if ((u5 & 0x8080) == 0) {
      u9 = u9 >> 0x10;
      pu8 = (uint32_t *)((int)pu7 + 6);
    }
    i4 = _alemu_stricmp((char *)((int)pu8 +
                                   (int)(((char *)&opts + 0x139) +
                                        (-(int)((char *)&opts + 0x140) -
                                        (uint32_t)CARRY1((uint8_t)u9,(uint8_t)u9)))),".def");
    if (i4 != 0) goto L_08099294;
  }
  splitdirfile(((char *)&opts + 0x140),(char *)(g + 0x56c1),(char *)(g + 0x52c0));
L_080992ce:
  i4 = GameLoadSystem();
  if (i4 == 0) {
    strcat((char *)(g + G_ERRMSG),"\nError loading system data: ");
    strcat((char *)(g + G_ERRMSG),(char *)((int)g + 0x15aff));
    strcat((char *)(g + G_ERRMSG),(char *)(g + 0x52c0));
    ErrorExit();
  }
  GameSetVol(g[G_SOUND_LINUX_MASTERWAVVOLUME],0xffffffff);
  return;
}

/* GameDeInit @ 0x08099350, 319 bytes
 *
 * Shuts the engine down in reverse order: back to text mode, frees the
 * character cache, character list, select screen, fight data, motif and game
 * variables, stops sound, CD, MP3, input and timer. It prints the version
 * banner and, with debug output enabled, load-time statistics ("BG load
 * time: %.1f ms", "Player load time", "Total load time", "Pal groups in
 * background").
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: G_SetMode, PlayerCacheClear, CharInfoFree,
 *        FreeSelectScreenMatrix, GameFreeFightData, GameUnloadSystem,
 *        GameVarDeInit, UInpDeInit, PadDeInit, KBDeInit,
 *        SwitchCallbacksDeInit, TimerDeInit, G_DeInit, CDADeInit,
 *        MP3DeInit, SndDeInit, ElecDeInit
 * C library: printf, chdir
 * Called by: _mangled_main
 * Messages:
 *   "M.U.G.E.N test ver %i.%02i.%02i\t\t\t\t\t(c)%i Elecbyte\n\n"
 *   "BG load time: %.1f ms\nPlayer load time: %.1f ms, %.1f ms\n"
 *   "Total load time: %.1f ms\n"
 *   "Pal groups in background: %i\n"
 *
 * Elecbyte file: src/mugen/init.c
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void GameDeInit(int arg1)

{
  float80 f1;
  
  G_SetMode(0xffffffff,0x50,0x19,8);
  printf("M.U.G.E.N test ver %i.%02i.%02i\t\t\t\t\t(c)%i Elecbyte\n\n",MUGENDATE_Y,MUGENDATE_M,
         MUGENDATE_D,MUGENDATE_Y);
  f1 = (float)TicksPerSecond;
  printf("BG load time: %.1f ms\nPlayer load time: %.1f ms, %.1f ms\n",
         (double)(((float)g[0x81c4] / f1) * 1000.0),(double)(((float)g[0x81c5] / f1) * 1000.0)
         ,(double)(((float)g[0x81c6] / f1) * 1000.0));
  printf("Total load time: %.1f ms\n",(double)(((float)g[0x81c9] / (float)TicksPerSecond) * 1000.0))
  ;
  printf("Pal groups in background: %i\n",g[0x81ca]);
  printf("\n");
  PlayerCacheClear();
  CharInfoFree();
  if (arg1 != 0) {
    FreeSelectScreenMatrix();
  }
  GameFreeFightData();
  GameUnloadSystem();
  chdir((char *)g);
  GameVarDeInit();
  UInpDeInit();
  PadDeInit();
  KBDeInit();
  SwitchCallbacksDeInit();
  TimerDeInit();
  G_DeInit();
  CDADeInit();
  MP3DeInit();
  SndDeInit();
  ElecDeInit();
  return;
}

/* GameInitPads @ 0x08099490, 344 bytes
 *
 * Reinstalls the joysticks according to the configured joystick types of
 * both players, then reinstalls the unified input layer.
 *
 * Globals read: input_p2_joystick_type_1ce38, input_p1_joystick_type_1ce34
 * Calls: PlayerKeysRemoveZero, PadDeInit, DeviceInit, PadInit, UInpReInit,
 *        ErrorExitM
 * Called by: GameLoadOptions
 * Messages:
 *   "Can\'t init input"
 *
 * Elecbyte file: src/mugen/init.c
 */
void GameInitPads(void)

{
  int i1;
  int i2;
  int *pi3;
  int *pi4;
  
  pi3 = g + 0x736f;
  pi4 = g + 0x7355;
  for (i1 = 0xd; i1 != 0; i1 = i1 + -1) {
    *pi4 = *pi3;
    pi3 = pi3 + 1;
    pi4 = pi4 + 1;
  }
  pi3 = g + 0x737c;
  pi4 = g + 0x7362;
  for (i1 = 0xd; i1 != 0; i1 = i1 + -1) {
    *pi4 = *pi3;
    pi3 = pi3 + 1;
    pi4 = pi4 + 1;
  }
  if (g[0x738b] == 0) {
    pi3 = g + 0x7355;
    for (i1 = 0xd; i1 != 0; i1 = i1 + -1) {
      *pi3 = 0;
      pi3 = pi3 + 1;
    }
    PlayerKeysRemoveZero((int)(g + 0x7355),0x80);
  }
  if (g[0x738c] == 0) {
    pi3 = g + 0x7362;
    for (i1 = 0xd; i1 != 0; i1 = i1 + -1) {
      *pi3 = 0;
      pi3 = pi3 + 1;
    }
    PlayerKeysRemoveZero((int)(g + 0x7362),0x80);
  }
  if (PadInstalled != 0) {
    PadDeInit();
  }
  i1 = g[0x738b];
  if (((i1 != 0) || (g[0x738c] != 0)) && (g[0x799d] == 0)) {
    if (i1 == 0) {
      i2 = g[G_INPUT_P2_JOYSTICK_TYPE_1CE38];
    }
    else {
      i2 = g[G_INPUT_P1_JOYSTICK_TYPE_1CE34];
    }
    if (i2 == 0x16) {
      DeviceInit();
    }
    i1 = PadInit(i2,(uint32_t)(i1 == 0));
    pi3 = g;
    if (i1 == 0) {
      g[0x738c] = 0;
      pi3[0x738b] = 0;
    }
  }
  i1 = UInpReInit();
  if (i1 == 0) {
    ErrorExitM("Can\'t init input");
  }
  return;
}

/* GameDefKeyInit @ 0x080995f0, 70 bytes
 *
 * Fills both players' key configurations with the built-in defaults
 * (DefaultKeyCfg, mapped into KBI key order by KeyCfgToKBIMap).
 *
 * Called by: GameInit
 *
 * Elecbyte file: src/mugen/init.c
 */
void GameDefKeyInit(void)

{
  int *pi1;
  int i2;
  int *pi3;
  int i3;
  int j;
  int *pi6;
  int i7;
  
  j = 0;
  i7 = 0;
  pi6 = g + 0x733b;
  do {
    i3 = 0;
    pi3 = (int *)((int)&DefaultKeyCfg + i7);
    do {
      pi1 = &KeyCfgToKBIMap + i3;
      i3 = i3 + 1;
      i2 = *pi3;
      pi3 = pi3 + 1;
      pi6[*pi1] = i2;
    } while (i3 < 0xb);
    j = j + 1;
    pi6 = pi6 + 0xd;
    i7 = i7 + 0x2c;
  } while (j < 2);
  return;
}

/* GameInputSetup @ 0x08099640, 377 bytes
 *
 * Builds the unified input key map from both players' key and joystick
 * configurations (KBToUInp for each entry) and reinstalls the input layer.
 * Asserts that every converted code is in range.
 *
 * Calls: KBToUInp, UInpSetKeyMap, UInpReInit
 * C library: __assert_fail
 * Called by: GameLoadOptions, KeyConfigScreen, OptionsScreen
 * Messages:
 *   "KeyConvFunc(key_pad->sc[KeyCfgToKBIMap[i]]) < ((0x20*4)+256)+1"
 *
 * Elecbyte file: src/mugen/init.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x650 bytes,
 *       8 variables), because their address is taken.
 */
bool GameInputSetup(void)

{
  uint32_t *pu1;
  int *pi2;
  int i3;
  int i4;
  uint32_t uinp;
  int i6;
  int i2;
  bool b8;
  unsigned char frame[0x650] __attribute__((aligned(16)));
#define stk_644 (*(int *)(frame + 0xc))
#define stk_640 (*(int *)(frame + 0x10))
#define stk_63c (*(uint32_t **)(frame + 0x14))
#define stk_638 (*(generic_fn **)(frame + 0x18))
#define stk_634 (*(int *)(frame + 0x1c))
#define stk_630 (*(int *)(frame + 0x20))
#define stk_62c (*(uint32_t (*)[383])(frame + 0x24))
#define stk_30 (*(int (*)[8])(frame + 0x620))
  
  i6 = 0x17f;
  pi2 = stk_30;
  do {
    *pi2 = i6;
    pi2 = pi2 + -1;
    i6 = i6 + -1;
  } while (-1 < i6);
  stk_634 = 0;
  do {
    stk_638 = KBToUInp;
    if (stk_634 != 0) {
      stk_638 = PadToUInp;
    }
    stk_630 = 0;
    stk_63c = &DefaultKeyCfg;
    stk_640 = 0;
    stk_644 = 0;
    do {
      pi2 = g;
      if (stk_634 == 0) {
        i6 = stk_644 + 0x1cc84;
      }
      else {
        i6 = stk_640 + 0x1cd54;
      }
      i2 = 0;
      do {
        i4 = (&KeyCfgToKBIMap)[i2];
        i3 = (*stk_638)(*(uint32_t *)((int)pi2 + i4 * 4 + i6));
        if (0x180 < i3) {
                    /* WARNING: Subroutine does not return */
          __assert_fail("KeyConvFunc(key_pad->sc[KeyCfgToKBIMap[i]]) < ((0x20*4)+256)+1",
                        "src/mugen/init.c",0x254,"GameInputSetup");
        }
        i4 = (*stk_638)(*(uint32_t *)((int)pi2 + i4 * 4 + i6));
        pu1 = stk_63c + i2;
        i2 = i2 + 1;
        uinp = KBToUInp(*pu1);
        stk_62c[i4] = uinp;
      } while (i2 < 0xb);
      stk_630 = stk_630 + 1;
      stk_63c = stk_63c + 0xb;
      stk_640 = stk_640 + 0x34;
      stk_644 = stk_644 + 0x34;
    } while (stk_630 < 2);
    stk_634 = stk_634 + 1;
  } while (stk_634 < 2);
  i6 = UInpSetKeyMap(stk_62c);
  if (i6 == 0) {
    b8 = false;
  }
  else {
    i6 = UInpReInit();
    b8 = i6 != 0;
  }
  return b8;
}
#undef stk_644
#undef stk_640
#undef stk_63c
#undef stk_638
#undef stk_634
#undef stk_630
#undef stk_62c
#undef stk_30

/* GfxResize @ 0x080997c0, 184 bytes
 *
 * Changes the video mode to a new size and depth and resets the blit mode.
 * Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         uint32_t
 *   arg4         int
 *
 * Globals read: video_linux_width, video_linux_height, video_linux_depth
 * Calls: G_SetMode, G_SetBlitMode, V_SetBuf
 *
 * Elecbyte file: src/mugen/init.c
 */
bool GfxResize(int arg1,int arg2,uint32_t arg3,int arg4)

{
  uint32_t u1;
  uint32_t u2;
  int i3;
  
  u1 = g[0x7556];
  if ((arg4 == 0) || (u1 != 1)) {
    u2 = u1;
    if ((arg4 == 0) && (u1 != 1)) {
      u2 = 1;
    }
  }
  else {
    u2 = 2;
  }
  i3 = G_SetMode(u2,arg1,arg2,arg3);
  if (i3 == 0) {
    G_SetMode(u1,g[G_VIDEO_LINUX_WIDTH],g[G_VIDEO_LINUX_HEIGHT],g[G_VIDEO_LINUX_DEPTH]);
  }
  if (g[0x7557] != 0) {
    G_SetBlitMode(g[0x7557],1);
  }
  V_SetBuf(V_Current,0);
  return i3 != 0;
}

/* GameLoadFightData @ 0x08099880, 9120 bytes
 *
 * Loads the fight screen definition (fight.def) and the fight effects.
 * "[Files]" gives sff, snd, fightfx.sff, fightfx.air, common.snd and the
 * fonts. The life bar, power bar, face, name, time, combo, round and win
 * icon groups (normal, simul and turns variants) give the positions,
 * sprites, animations, fonts and sounds of every fight screen element,
 * including KO, DKO, TO, draw, win and lose sounds. It also allocates the
 * explod and system explod arrays. Missing groups or files are fatal
 * ("Missing lifebar info", "Can't read Files|fightfx.sff", "Can't allocate
 * explods", ...).
 *
 * Parameters:
 *   value        FILE *
 *
 * Text keys read: [Files], "sff", "snd", "fightfx.sff", "fightfx.air",
 *                 "common.snd", [Lifebar], [Turns Lifebar], [Simul
 *                 Lifebar], [Powerbar], [face], [simul face], [turns
 *                 face], [name], [simul name], [turns name], [time],
 *                 "pos", "framespercount", [combo], "text.text",
 *                 "start.x", "counter.font", "counter.shake", ...
 * Globals read: errmsg, config_explodmax
 * Calls: TPReadFile, splitdirfile, TPGroupSeek, TPGetValue, FindFileDirEx,
 *        SpriteReadFile, SndReadFile, AnimRCReadFile, FontReadFile,
 *        TPGroupScanFirst, strimatch, TPGroupScanNext, AnimRCReadFileTP,
 *        TPScanf, SysExplodParse, TPGetValueInt, StripDoublePercent,
 *        TPFree, ExplodArrayNew
 * C library: sprintf, strcat, strncpy
 * Called by: GameLoadSystem
 * Messages:
 *   "Can\'t open %s"
 *   "Missing files info"
 *   "Can\'t read Files|sff"
 *   "Can\'t read %s"
 *   "Can\'t read Files|snd"
 *   "Can\'t read Files|fightfx.sff"
 *
 * Elecbyte file: src/mugen/init.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x2250 bytes,
 *       71 variables), because their address is taken.
 */
uint32_t GameLoadFightData(FILE *value)

{
  int *pi1;
  int *pi2;
  bool b3;
  int *pi4;
  FILE *tp;
  int i2;
  int *sysexplod;
  int *sprites;
  int i9;
  char *value2;
  FILE *stale_ECX;
  FILE *stale_ECX_00;
  FILE *stale_ECX_01;
  FILE *stale_ECX_02;
  FILE *stale_ECX_03;
  uint32_t stale_ECX_04;
  FILE *stale_ECX_05;
  uint32_t stale_ECX_06;
  FILE *stale_ECX_07;
  uint32_t stale_ECX_08;
  FILE *stale_ECX_09;
  char *stale_ECX_10;
  FILE *stale_ECX_11;
  FILE *stale_ECX_12;
  FILE *stale_EDX;
  FILE *stale_EDX_00;
  FILE *stale_EDX_01;
  FILE *stale_EDX_02;
  int *stale_EDX_03;
  FILE *stale_EDX_04;
  FILE *filename;
  char *pc11;
  int *pi12;
  uint32_t *pu13;
  unsigned char frame[0x2250] __attribute__((aligned(16)));
#define stk_2248 (*(int *)(frame + 0x8))
#define stk_2244 (*(int **)(frame + 0xc))
#define stk_2240 (*(int **)(frame + 0x10))
#define stk_223c (*(int **)(frame + 0x14))
#define stk_2238 (*(int **)(frame + 0x18))
#define stk_2234 (*(int *)(frame + 0x1c))
#define sysexplod2 (*(int **)(frame + 0x20))
#define sysexplod3 (*(int **)(frame + 0x24))
#define stk_2228 (*(int **)(frame + 0x28))
#define stk_2224 (*(int **)(frame + 0x2c))
#define stk_2220 (*(int **)(frame + 0x30))
#define stk_221c (*(int **)(frame + 0x34))
#define stk_2218 (*(int *)(frame + 0x38))
#define sysexplod4 (*(int **)(frame + 0x3c))
#define sysexplod5 (*(int **)(frame + 0x40))
#define stk_220c (*(int **)(frame + 0x44))
#define stk_2208 (*(int **)(frame + 0x48))
#define stk_2204 (*(int **)(frame + 0x4c))
#define stk_2200 (*(int **)(frame + 0x50))
#define stk_21fc (*(int *)(frame + 0x54))
#define sysexplod6 (*(int **)(frame + 0x58))
#define sysexplod7 (*(int **)(frame + 0x5c))
#define stk_21f0 (*(int **)(frame + 0x60))
#define stk_21ec (*(int **)(frame + 0x64))
#define stk_21e8 (*(int **)(frame + 0x68))
#define stk_21e4 (*(int **)(frame + 0x6c))
#define stk_21e0 (*(int *)(frame + 0x70))
#define stk_21dc (*(int **)(frame + 0x74))
#define sysexplod8 (*(int **)(frame + 0x78))
#define sysexplod9 (*(int **)(frame + 0x7c))
#define sysexplod10 (*(int **)(frame + 0x80))
#define stk_21cc (*(int **)(frame + 0x84))
#define sysexplod11 (*(int **)(frame + 0x88))
#define stk_21c0 (*(uint32_t **)(frame + 0x90))
#define stk_21bc (*(int **)(frame + 0x94))
#define sysexplod12 (*(int **)(frame + 0x98))
#define stk_21b0 (*(uint32_t **)(frame + 0xa0))
#define sysexplod13 (*(int **)(frame + 0xa4))
#define sysexplod14 (*(int **)(frame + 0xa8))
#define stk_21a0 (*(uint32_t **)(frame + 0xb0))
#define stk_219c (*(int **)(frame + 0xb4))
#define stk_2198 (*(int **)(frame + 0xb8))
#define stk_2194 (*(int **)(frame + 0xbc))
#define stk_2190 (*(int **)(frame + 0xc0))
#define sysexplod15 (*(int **)(frame + 0xc4))
#define sysexplod16 (*(int **)(frame + 0xc8))
#define sysexplod17 (*(int **)(frame + 0xd0))
#define sysexplod18 (*(int **)(frame + 0xd4))
#define sysexplod19 (*(int **)(frame + 0xdc))
#define sysexplod20 (*(int **)(frame + 0xe0))
#define stk_216c (*(int **)(frame + 0xe4))
#define sysexplod21 (*(int **)(frame + 0xe8))
#define sysexplod22 (*(int **)(frame + 0xec))
#define stk_2160 (*(int *)(frame + 0xf0))
#define stk_215c (*(int **)(frame + 0xf4))
#define stk_2158 (*(int **)(frame + 0xf8))
#define sysexplod23 (*(int **)(frame + 0xfc))
#define sysexplod24 (*(int **)(frame + 0x100))
#define sysexplod25 (*(int **)(frame + 0x104))
#define sysexplod26 (*(int **)(frame + 0x108))
#define sysexplod27 (*(int **)(frame + 0x10c))
#define sysexplod28 (*(int **)(frame + 0x110))
#define sysexplod29 (*(int **)(frame + 0x114))
#define sysexplod30 (*(int **)(frame + 0x118))
#define sysexplod31 (*(int **)(frame + 0x11c))
#define sysexplod32 (*(int **)(frame + 0x120))
#define sysexplod33 (*(int **)(frame + 0x124))
#define dirname (*(char (*)[4096])(frame + 0x154))
#define filename2 (*(FILE (*)[27])(frame + 0x1154))
#define keyname (*(char (*)[32])(frame + 0x2154))
#define keyname2 (*(char (*)[204])(frame + 0x2174))
  
  pi4 = g;
  pi12 = g + 0x4149;
  stk_2244 = g + 0x4157;
  tp = TPReadFile((char *)value);
  if (tp == (FILE *)0x0) {
    sysexplod = g + G_ERRMSG;
    pc11 = "Can\'t open %s";
    filename = stale_ECX;
  }
  else {
    splitdirfile((char *)value,dirname,(char *)0x0);
    i2 = TPGroupSeek((int)tp,"Files");
    if (i2 == -1) {
      sysexplod = g + G_ERRMSG;
      pc11 = "Missing files info";
      filename = value;
    }
    else {
      value = (FILE *)TPGetValue((int)tp,"sff");
      if (value == (FILE *)0x0) {
        sysexplod = g + G_ERRMSG;
        pc11 = "Can\'t read Files|sff";
        value = stale_EDX;
        filename = stale_EDX;
      }
      else {
        i2 = FindFileDirEx((char *)value,(char *)filename2,(char *)0x0,
                              (uint32_t *)dirname);
        if (i2 == 0) {
          return 0;
        }
        sysexplod = SpriteReadFile((char *)filename2);
        pi4[0x4149] = (int)sysexplod;
        if (sysexplod == (int *)0x0) {
          sysexplod = g + G_ERRMSG;
          pc11 = "Can\'t read %s";
          filename = tp;
        }
        else {
          value = (FILE *)TPGetValue((int)tp,"snd");
          if (value == (FILE *)0x0) {
            sysexplod = g + G_ERRMSG;
            pc11 = "Can\'t read Files|snd";
            value = filename2;
            filename = filename2;
          }
          else {
            i2 = FindFileDirEx((char *)value,(char *)filename2,(char *)0x0,
                                  (uint32_t *)dirname);
            if (i2 == 0) {
              return 0;
            }
            sysexplod = SndReadFile((char *)filename2);
            pi4[0x4155] = (int)sysexplod;
            if (sysexplod == (int *)0x0) {
              sysexplod = g + G_ERRMSG;
              pc11 = "Can\'t read %s";
              filename = stale_EDX_00;
            }
            else {
              value = (FILE *)TPGetValue((int)tp,"fightfx.sff");
              if (value == (FILE *)0x0) {
                sysexplod = g + G_ERRMSG;
                pc11 = "Can\'t read Files|fightfx.sff";
                filename = (FILE *)0x0;
              }
              else {
                i2 = FindFileDirEx((char *)value,(char *)filename2,(char *)0x0,
                                      (uint32_t *)dirname);
                if (i2 == 0) {
                  return 0;
                }
                sprites = SpriteReadFile((char *)filename2);
                sysexplod = g;
                g[0x4147] = (int)sprites;
                if (sprites == (int *)0x0) {
                  sysexplod = sysexplod + 0x81d2;
                  pc11 = "Can\'t load %s";
                  filename = stale_ECX_00;
                }
                else {
                  value = (FILE *)TPGetValue((int)tp,"fightfx.air");
                  if (value == (FILE *)0x0) {
                    sysexplod = g + G_ERRMSG;
                    pc11 = "Can\'t read Files|fightfx.air";
                    filename = (FILE *)0x0;
                  }
                  else {
                    i2 = FindFileDirEx((char *)value,(char *)filename2,(char *)0x0,
                                          (uint32_t *)dirname);
                    if (i2 == 0) {
                      return 0;
                    }
                    sprites = AnimRCReadFile((char *)filename2);
                    sysexplod = g;
                    g[0x4148] = (int)sprites;
                    if (sprites == (int *)0x0) {
                      sysexplod = sysexplod + 0x81d2;
                      pc11 = "Can\'t load %s";
                      filename = stale_ECX_01;
                    }
                    else {
                      value = (FILE *)TPGetValue((int)tp,"common.snd");
                      if (value == (FILE *)0x0) {
                        sysexplod = g + G_ERRMSG;
                        pc11 = "Can\'t read Files|common.snd";
                        filename = (FILE *)0x0;
                      }
                      else {
                        i2 = FindFileDirEx((char *)value,(char *)filename2,(char *)0x0,
                                              (uint32_t *)dirname);
                        if (i2 == 0) {
                          return 0;
                        }
                        sprites = SndReadFile((char *)filename2);
                        sysexplod = g;
                        g[0x4156] = (int)sprites;
                        if (sprites == (int *)0x0) {
                          sysexplod = sysexplod + 0x81d2;
                          pc11 = "Can\'t load %s";
                          filename = stale_ECX_02;
                        }
                        else {
                          i2 = 0;
                          stk_2248 = 0;
                          do {
                            *(int *)((int)pi4 + stk_2248 + 0x1052c) = g[0x413a];
                            sprintf(keyname,"font%i",i2,stk_2248);
                            value = (FILE *)TPGetValue((int)tp,keyname);
                            if (value != (FILE *)0x0) {
                              filename = filename2;
                              i9 = FindFileDirEx((char *)value,(char *)filename,(char *)0x0,
                                                    (uint32_t *)dirname);
                              if (i9 == 0) {
                                return 0;
                              }
                              i9 = FontReadFile((char *)filename);
                              *(int *)((int)pi4 + stk_2248 + 0x1052c) = i9;
                              if (i9 == 0) {
                                sysexplod = g + G_ERRMSG;
                                pc11 = "Can\'t read font %s";
                                goto L_0809bc03;
                              }
                            }
                            i2 = i2 + 1;
                            stk_2248 = stk_2248 + 4;
                          } while (i2 < 10);
                          i2 = TPGroupScanFirst((int)tp);
                          do {
                            i9 = strimatch((char *)(i2 + 1),"begin action ");
                            if (i9 != 0) break;
                            i2 = TPGroupScanNext((int)tp);
                          } while (i2 != 0);
                          if (i2 != 0) {
                            sysexplod = AnimRCReadFileTP((int)tp);
                            pi4[0x414a] = (int)sysexplod;
                            if (sysexplod == (int *)0x0) {
                              strcat((char *)(g + G_ERRMSG),"\nError loading anim in Files");
                              return 0;
                            }
                          }
                          i2 = TPGroupSeek((int)tp,"Lifebar");
                          if (i2 == -1) {
                            sysexplod = g + G_ERRMSG;
                            pc11 = "Missing lifebar info";
                            value = stale_ECX_03;
                            filename = stale_ECX_03;
                          }
                          else {
                            sysexplod3 = pi4 + 0x41c8;
                            sysexplod2 = pi4 + 0x41ad;
                            stk_223c = pi4 + 0x4158;
                            sysexplod = pi4 + 0x4159;
                            stk_2234 = 1;
                            stk_2240 = sysexplod;
                            stk_2238 = pi4 + 0x415a;
                            do {
                              i2 = 4;
                              sprites = stk_2244 + 0x76;
                              do {
                                *sprites = 1;
                                sprites = sprites + -0x1b;
                                i2 = i2 + -1;
                              } while (-1 < i2);
                              sprintf(keyname2,"p%i.pos",stk_2234,sysexplod);
                              TPScanf((int)tp,keyname2,"%i,%i",stk_2244,stk_223c);
                              sprintf(keyname2,"p%i.range.x",stk_2234);
                              TPScanf((int)tp,keyname2,"%i,%i",stk_2240,stk_2238);
                              i2 = 0;
                              sysexplod = stk_2244 + 5;
                              do {
                                i9 = i2 + 1;
                                sprintf(keyname2,"p%i.bg%i",stk_2234,i2);
                                SysExplodParse((int)tp,sysexplod,keyname2);
                                i2 = i9;
                                sysexplod = sysexplod + 0x1b;
                              } while (i9 < 3);
                              sprintf(keyname2,"p%i.mid",stk_2234,stale_ECX_04);
                              SysExplodParse((int)tp,sysexplod2,keyname2);
                              sprintf(keyname2,"p%i.front",stk_2234);
                              SysExplodParse((int)tp,sysexplod3,keyname2);
                              sysexplod3 = sysexplod3 + 0x8c;
                              sysexplod2 = sysexplod2 + 0x8c;
                              sysexplod = stk_2238 + 0x8c;
                              stk_223c = stk_223c + 0x8c;
                              stk_2240 = stk_2240 + 0x8c;
                              stk_2244 = stk_2244 + 0x8c;
                              b3 = stk_2234 < 2;
                              stk_2238 = sysexplod;
                              stk_2234 = stk_2234 + 1;
                            } while (b3);
                            i2 = TPGroupSeek((int)tp,"Turns Lifebar");
                            if (i2 == -1) {
                              sysexplod = g + G_ERRMSG;
                              pc11 = "Missing turns lifebar info";
                              value = stale_ECX_05;
                              filename = stale_ECX_05;
                            }
                            else {
                              sysexplod5 = pi4 + 0x4510;
                              sysexplod4 = pi4 + 0x44f5;
                              sysexplod = pi4 + 0x44a0;
                              stk_2224 = pi4 + 0x44a1;
                              stk_2228 = pi4 + 0x449f;
                              stk_2218 = 1;
                              stk_2220 = sysexplod;
                              stk_221c = pi4 + 0x44a2;
                              do {
                                i2 = 4;
                                sprites = stk_2228 + 0x76;
                                do {
                                  *sprites = 1;
                                  sprites = sprites + -0x1b;
                                  i2 = i2 + -1;
                                } while (-1 < i2);
                                sprintf(keyname2,"p%i.pos",stk_2218,sysexplod);
                                TPScanf((int)tp,keyname2,"%i,%i",stk_2228,stk_2220);
                                sprintf(keyname2,"p%i.range.x",stk_2218);
                                TPScanf((int)tp,keyname2,"%i,%i",stk_2224,stk_221c);
                                i2 = 0;
                                sysexplod = stk_2228 + 5;
                                do {
                                  i9 = i2 + 1;
                                  sprintf(keyname2,"p%i.bg%i",stk_2218,i2);
                                  SysExplodParse((int)tp,sysexplod,keyname2);
                                  i2 = i9;
                                  sysexplod = sysexplod + 0x1b;
                                } while (i9 < 3);
                                sprintf(keyname2,"p%i.mid",stk_2218,stale_ECX_06);
                                SysExplodParse((int)tp,sysexplod4,keyname2);
                                sprintf(keyname2,"p%i.front",stk_2218);
                                SysExplodParse((int)tp,sysexplod5,keyname2);
                                sysexplod5 = sysexplod5 + 0x8c;
                                sysexplod4 = sysexplod4 + 0x8c;
                                sysexplod = stk_221c + 0x8c;
                                stk_2220 = stk_2220 + 0x8c;
                                stk_2224 = stk_2224 + 0x8c;
                                stk_2228 = stk_2228 + 0x8c;
                                b3 = stk_2218 < 2;
                                stk_221c = sysexplod;
                                stk_2218 = stk_2218 + 1;
                              } while (b3);
                              i2 = TPGroupSeek((int)tp,"Simul Lifebar");
                              if (i2 == -1) {
                                sysexplod = g + G_ERRMSG;
                                pc11 = "Missing simul lifebar info";
                                value = stale_ECX_07;
                                filename = stale_ECX_07;
                              }
                              else {
                                sysexplod7 = pi4 + 0x42e0;
                                sysexplod6 = pi4 + 0x42c5;
                                stk_2204 = pi4 + 0x4270;
                                stk_2208 = pi4 + 0x4271;
                                sysexplod = pi4 + 0x426f;
                                stk_21fc = 1;
                                stk_220c = sysexplod;
                                stk_2200 = pi4 + 0x4272;
                                do {
                                  i2 = 4;
                                  sprites = stk_220c + 0x76;
                                  do {
                                    *sprites = 1;
                                    sprites = sprites + -0x1b;
                                    i2 = i2 + -1;
                                  } while (-1 < i2);
                                  sprintf(keyname2,"p%i.pos",stk_21fc,sysexplod);
                                  TPScanf((int)tp,keyname2,"%i,%i",stk_220c,stk_2204);
                                  sprintf(keyname2,"p%i.range.x",stk_21fc);
                                  TPScanf((int)tp,keyname2,"%i,%i",stk_2208,stk_2200);
                                  i2 = 0;
                                  sysexplod = stk_220c + 5;
                                  do {
                                    i9 = i2 + 1;
                                    sprintf(keyname2,"p%i.bg%i",stk_21fc,i2);
                                    SysExplodParse((int)tp,sysexplod,keyname2);
                                    i2 = i9;
                                    sysexplod = sysexplod + 0x1b;
                                  } while (i9 < 3);
                                  sprintf(keyname2,"p%i.mid",stk_21fc,stale_ECX_08);
                                  SysExplodParse((int)tp,sysexplod6,keyname2);
                                  sprintf(keyname2,"p%i.front",stk_21fc);
                                  SysExplodParse((int)tp,sysexplod7,keyname2);
                                  sysexplod7 = sysexplod7 + 0x8c;
                                  sysexplod6 = sysexplod6 + 0x8c;
                                  sysexplod = stk_2200 + 0x8c;
                                  stk_2204 = stk_2204 + 0x8c;
                                  stk_2208 = stk_2208 + 0x8c;
                                  stk_220c = stk_220c + 0x8c;
                                  b3 = stk_21fc < 4;
                                  stk_2200 = sysexplod;
                                  stk_21fc = stk_21fc + 1;
                                } while (b3);
                                i2 = TPGroupSeek((int)tp,"Powerbar");
                                if (i2 == -1) {
                                  sysexplod = g + G_ERRMSG;
                                  pc11 = "Missing Powerbar info";
                                  value = stale_ECX_09;
                                  filename = stale_ECX_09;
                                }
                                else {
                                  stk_21dc = pi4 + 0x46cf;
                                  i2 = 9;
                                  sysexplod = pi4 + 0x4826;
                                  do {
                                    *sysexplod = -1;
                                    sysexplod = sysexplod + -1;
                                    i2 = i2 + -1;
                                  } while (-1 < i2);
                                  sysexplod10 = pi4 + 0x47e7;
                                  sysexplod9 = pi4 + 0x4740;
                                  sysexplod8 = pi4 + 0x4725;
                                  sysexplod = pi4 + 0x46d0;
                                  stk_21e8 = pi4 + 0x46d1;
                                  stk_21ec = pi4 + 0x46d2;
                                  stk_21e0 = 1;
                                  stk_21e4 = (int *)0x0;
                                  stk_21f0 = sysexplod;
                                  do {
                                    i2 = 4;
                                    sprites = pi4 + (int)stk_21e4 * 4 + 0x4745;
                                    do {
                                      *sprites = 1;
                                      sprites = sprites + -0x1b;
                                      i2 = i2 + -1;
                                    } while (-1 < i2);
                                    sprintf(keyname2,"p%i.pos",stk_21e0,sysexplod);
                                    TPScanf((int)tp,keyname2,"%i,%i",stk_21dc,stk_21f0);
                                    sprintf(keyname2,"p%i.range.x",stk_21e0);
                                    TPScanf((int)tp,keyname2,"%i,%i",stk_21e8,stk_21ec);
                                    i2 = 0;
                                    sysexplod = pi4 + (int)stk_21e4 * 4 + 0x46d4;
                                    do {
                                      i9 = i2 + 1;
                                      sprintf(keyname2,"p%i.bg%i",stk_21e0,i2);
                                      SysExplodParse((int)tp,sysexplod,keyname2);
                                      i2 = i9;
                                      sysexplod = sysexplod + 0x1b;
                                    } while (i9 < 3);
                                    sprintf(keyname2,"p%i.mid",stk_21e0,i9);
                                    SysExplodParse((int)tp,sysexplod8,keyname2);
                                    sprintf(keyname2,"p%i.front",stk_21e0);
                                    SysExplodParse((int)tp,sysexplod9,keyname2);
                                    sprintf(keyname2,"p%i.counter",stk_21e0);
                                    SysExplodParse((int)tp,sysexplod10,keyname2);
                                    sysexplod10 = sysexplod10 + 0x1b;
                                    sysexplod9 = sysexplod9 + 0x8c;
                                    sysexplod8 = sysexplod8 + 0x8c;
                                    stk_21dc = stk_21dc + 0x8c;
                                    sysexplod = (int *)((int)stk_21e4 + 0x23);
                                    stk_21e8 = stk_21e8 + 0x8c;
                                    stk_21ec = stk_21ec + 0x8c;
                                    stk_21f0 = stk_21f0 + 0x8c;
                                    b3 = stk_21e0 < 2;
                                    stk_21e4 = sysexplod;
                                    stk_21e0 = stk_21e0 + 1;
                                  } while (b3);
                                  pc11 = keyname;
                                  filename = (FILE *)0x0;
                                  sysexplod = pi4 + 0x4827;
                                  sprites = pi4 + 0x481d;
                                  do {
                                    value = (FILE *)((int)&filename->_flags + 1);
                                    sprintf(keyname,"level%i.snd",filename,pc11);
                                    TPScanf((int)tp,keyname,"%i,%i",sprites,sysexplod);
                                    pc11 = stale_ECX_10;
                                    filename = value;
                                    sysexplod = sysexplod + 1;
                                    sprites = sprites + 1;
                                  } while ((int)value < 10);
                                  i2 = TPGroupSeek((int)tp,"face");
                                  if (i2 == -1) {
                                    sysexplod = g + G_ERRMSG;
                                    pc11 = "Missing face info";
                                  }
                                  else {
                                    value = (FILE *)0x0;
                                    sysexplod11 = pi4 + 0x4831;
                                    pi4[0x4911] = 1;
                                    pi4[0x4912] = -1;
                                    sysexplod = pi4 + 0x484c;
                                    stk_21c0 = (uint32_t *)(pi4 + 0x4911);
                                    stk_21cc = pi4 + 0x4909;
                                    sprites = pi4 + 0x490d;
                                    do {
                                      value = (FILE *)((int)&value->_flags + 1);
                                      sprintf(keyname2,"p%i.pos",value,sysexplod);
                                      TPScanf((int)tp,keyname2,"%i,%i",stk_21cc,sprites);
                                      sprintf(keyname2,"p%i.bg",value);
                                      SysExplodParse((int)tp,sysexplod11,keyname2);
                                      sprintf(keyname2,"p%i.face",value);
                                      SysExplodParse((int)tp,sysexplod,keyname2);
                                      sprintf(keyname2,"p%i.facing",value);
                                      TPGetValueInt((int)tp,keyname2,stk_21c0);
                                      stk_21c0 = stk_21c0 + 1;
                                      sysexplod = sysexplod + 0x36;
                                      sysexplod11 = sysexplod11 + 0x36;
                                      stk_21cc = stk_21cc + 1;
                                      sprites = sprites + 1;
                                    } while ((int)value < 2);
                                    i2 = TPGroupSeek((int)tp,"simul face");
                                    if (i2 == -1) {
                                      sysexplod = g + G_ERRMSG;
                                      pc11 = "Missing simul face info";
                                      filename = value;
                                    }
                                    else {
                                      value = (FILE *)0x0;
                                      sysexplod12 = pi4 + 0x4915;
                                      pi4[0x49f7] = 1;
                                      pi4[0x49f5] = 1;
                                      pi4[0x49f8] = -1;
                                      pi4[0x49f6] = -1;
                                      sysexplod = pi4 + 0x4930;
                                      stk_21b0 = (uint32_t *)(pi4 + 0x49f5);
                                      stk_21bc = pi4 + 0x49ed;
                                      sprites = pi4 + 0x49f1;
                                      do {
                                        value = (FILE *)((int)&value->_flags + 1);
                                        sprintf(keyname2,"p%i.pos",value,sysexplod);
                                        TPScanf((int)tp,keyname2,"%i,%i",stk_21bc,sprites);
                                        sprintf(keyname2,"p%i.bg",value);
                                        SysExplodParse((int)tp,sysexplod12,keyname2);
                                        sprintf(keyname2,"p%i.face",value);
                                        SysExplodParse((int)tp,sysexplod,keyname2);
                                        sprintf(keyname2,"p%i.facing",value);
                                        TPGetValueInt((int)tp,keyname2,stk_21b0);
                                        stk_21b0 = stk_21b0 + 1;
                                        sysexplod = sysexplod + 0x36;
                                        sysexplod12 = sysexplod12 + 0x36;
                                        stk_21bc = stk_21bc + 1;
                                        sprites = sprites + 1;
                                      } while ((int)value < 4);
                                      i2 = TPGroupSeek((int)tp,"turns face");
                                      if (i2 == -1) {
                                        sysexplod = g + G_ERRMSG;
                                        pc11 = "Missing turns face info";
                                        filename = value;
                                      }
                                      else {
                                        i2 = 0;
                                        sprites = pi4 + 0x49f9;
                                        pi4[0x4ad9] = 1;
                                        pi4[0x4ada] = -1;
                                        sysexplod16 = pi4 + 0x4b13;
                                        sysexplod15 = pi4 + 0x4af8;
                                        stk_2190 = pi4 + 0x4b31;
                                        stk_2194 = pi4 + 0x4b32;
                                        stk_2198 = pi4 + 0x4b2e;
                                        stk_219c = pi4 + 0x4b2f;
                                        sysexplod = pi4 + 0x4a14;
                                        stk_21a0 = (uint32_t *)(pi4 + 0x4ad9);
                                        sysexplod13 = pi4 + 0x4add;
                                        sysexplod14 = sprites;
                                        do {
                                          i2 = i2 + 1;
                                          sprintf(keyname2,"p%i.pos",i2,sysexplod);
                                          pi1 = sprites + 0xdc;
                                          pi2 = sprites + 0xd8;
                                          sprites = sprites + 1;
                                          TPScanf((int)tp,keyname2,"%i,%i",pi2,pi1);
                                          sprintf(keyname2,"p%i.bg",i2);
                                          SysExplodParse((int)tp,sysexplod14,keyname2);
                                          sprintf(keyname2,"p%i.face",i2);
                                          SysExplodParse((int)tp,sysexplod,keyname2);
                                          sprintf(keyname2,"p%i.facing",i2);
                                          TPGetValueInt((int)tp,keyname2,stk_21a0);
                                          sprintf(keyname2,"p%i.teammate.pos",i2);
                                          TPScanf((int)tp,keyname2,"%i,%i",stk_2198,stk_219c
                                                 );
                                          sprintf(keyname2,"p%i.teammate.spacing",i2);
                                          TPScanf((int)tp,keyname2,"%i,%i",stk_2190,stk_2194
                                                 );
                                          sprintf(keyname2,"p%i.teammate.bg",i2);
                                          SysExplodParse((int)tp,sysexplod13,keyname2);
                                          sprintf(keyname2,"p%i.teammate.face",i2);
                                          SysExplodParse((int)tp,sysexplod15,keyname2);
                                          sprintf(keyname2,"p%i.teammate.ko",i2);
                                          SysExplodParse((int)tp,sysexplod16,keyname2);
                                          sprintf(keyname2,"p%i.teammate.facing",i2);
                                          TPGetValueInt((int)tp,keyname2,stk_21a0);
                                          sysexplod16 = sysexplod16 + 0x56;
                                          sysexplod15 = sysexplod15 + 0x56;
                                          stk_2190 = stk_2190 + 0x56;
                                          stk_2194 = stk_2194 + 0x56;
                                          stk_2198 = stk_2198 + 0x56;
                                          stk_219c = stk_219c + 0x56;
                                          stk_21a0 = stk_21a0 + 1;
                                          sysexplod = sysexplod + 0x36;
                                          sysexplod14 = sysexplod14 + 0x36;
                                          sysexplod13 = sysexplod13 + 0x56;
                                        } while (i2 < 2);
                                        i2 = TPGroupSeek((int)tp,"name");
                                        if (i2 == -1) {
                                          sysexplod = g + G_ERRMSG;
                                          pc11 = "Missing name info";
                                          value = stale_EDX_01;
                                          filename = stale_EDX_01;
                                        }
                                        else {
                                          sysexplod18 = pi4 + 0x4bf5;
                                          sysexplod17 = pi4 + 0x4b89;
                                          sprites = pi4 + 0x4c61;
                                          i2 = 0;
                                          sysexplod = pi4 + 0x4c65;
                                          do {
                                            i2 = i2 + 1;
                                            sprintf(keyname2,"p%i.pos",i2,sprites);
                                            TPScanf((int)tp,keyname2,"%i,%i",sprites,sysexplod);
                                            sprintf(keyname2,"p%i.bg",i2);
                                            SysExplodParse((int)tp,sysexplod17,keyname2);
                                            sprintf(keyname2,"p%i.name",i2);
                                            SysExplodParse((int)tp,sysexplod18,keyname2);
                                            sysexplod18 = sysexplod18 + 0x1b;
                                            sysexplod17 = sysexplod17 + 0x1b;
                                            sprites = sprites + 1;
                                            sysexplod = sysexplod + 1;
                                          } while (i2 < 2);
                                          i2 = TPGroupSeek((int)tp,"simul name");
                                          if (i2 == -1) {
                                            sysexplod = g + G_ERRMSG;
                                            pc11 = "Missing simul name info";
                                            value = stale_EDX_02;
                                            filename = stale_EDX_02;
                                          }
                                          else {
                                            sysexplod20 = pi4 + 0x4cd5;
                                            sysexplod19 = pi4 + 0x4c69;
                                            sprites = pi4 + 0x4d41;
                                            i2 = 0;
                                            sysexplod = pi4 + 0x4d45;
                                            do {
                                              i2 = i2 + 1;
                                              sprintf(keyname2,"p%i.pos",i2,sprites);
                                              TPScanf((int)tp,keyname2,"%i,%i",sprites,sysexplod);
                                              sprintf(keyname2,"p%i.bg",i2);
                                              SysExplodParse((int)tp,sysexplod19,keyname2);
                                              sprintf(keyname2,"p%i.name",i2);
                                              SysExplodParse((int)tp,sysexplod20,keyname2);
                                              sysexplod20 = sysexplod20 + 0x1b;
                                              sysexplod19 = sysexplod19 + 0x1b;
                                              sprites = sprites + 1;
                                              sysexplod = sysexplod + 1;
                                            } while (i2 < 4);
                                            i2 = TPGroupSeek((int)tp,"turns name");
                                            if (i2 == -1) {
                                              sysexplod = g + G_ERRMSG;
                                              pc11 = "Missing turns name info";
                                              value = stale_ECX_11;
                                              filename = stale_ECX_11;
                                            }
                                            else {
                                              sprites = pi4 + 0x4db5;
                                              sysexplod21 = pi4 + 0x4d49;
                                              i2 = 0;
                                              sysexplod = pi4 + 0x4e25;
                                              stk_216c = pi4 + 0x4e21;
                                              sysexplod22 = sprites;
                                              do {
                                                i2 = i2 + 1;
                                                sprintf(keyname2,"p%i.pos",i2,sprites);
                                                TPScanf((int)tp,keyname2,"%i,%i",stk_216c,
                                                        sysexplod);
                                                sprintf(keyname2,"p%i.bg",i2);
                                                SysExplodParse((int)tp,sysexplod21,keyname2);
                                                sprintf(keyname2,"p%i.name",i2);
                                                SysExplodParse((int)tp,sysexplod22,keyname2);
                                                sysexplod22 = sysexplod22 + 0x1b;
                                                sysexplod21 = sysexplod21 + 0x1b;
                                                sprites = stk_216c + 1;
                                                sysexplod = sysexplod + 1;
                                                stk_216c = sprites;
                                              } while (i2 < 4);
                                              pc11 = "time";
                                              sysexplod = sysexplod22;
                                              i2 = TPGroupSeek((int)tp,"time");
                                              if (i2 == -1) {
                                                sysexplod = g + G_ERRMSG;
                                                pc11 = "Missing time info";
                                                value = tp;
                                                filename = tp;
                                              }
                                              else {
                                                pi4[0x4e61] = 0x3c;
                                                TPScanf((int)tp,"pos","%i,%i",pi4 + 0x4e5f,
                                                        pi4 + 0x4e60,pc11,sysexplod22,sysexplod);
                                                SysExplodParse((int)tp,pi4 + 0x4e29,"bg");
                                                value = (FILE *)(pi4 + 0x4e61);
                                                SysExplodParse((int)tp,pi4 + 0x4e44,"counter"
                                                              );
                                                TPGetValueInt((int)tp,"framespercount",
                                                              (uint32_t *)value);
                                                i2 = TPGroupSeek((int)tp,"combo");
                                                if (i2 == -1) {
                                                  sysexplod = g + G_ERRMSG;
                                                  pc11 = "Missing combo info";
                                                  filename = value;
                                                }
                                                else {
                                                  sprites = pi4 + 0x4e62;
                                                  pi4[0x4e62] = 10;
                                                  pi4[0x4e63] = 0x50;
                                                  pi4[0x4e64] = -0x28;
                                                  pi4[0x4e65] = 0x5a;
                                                  pi4[0x4e66] = -1;
                                                  pi4[0x4e6d] = 0x48206925;
                                                  pi4[0x4e6e] = 0x217469;
                                                  value = (FILE *)(pi4 + 0x4e6d);
                                                  pc11 = "text.text";
                                                  sysexplod = pi12;
                                                  value2 = TPGetValue((int)tp,"text.text");
                                                  if (value2 != (char *)0x0) {
                                                    pi12 = (int *)0x1f;
                                                    sysexplod = stale_EDX_03;
                                                    strncpy((char *)value,value2,0x1f);
                                                    pc11 = value2;
                                                  }
                                                  TPScanf((int)tp,"pos","%i,%i",sprites,
                                                          pi4 + 0x4e63,pc11,pi12,sysexplod);
                                                  TPGetValueInt((int)tp,"start.x",
                                                                (uint32_t *)(pi4 + 0x4e64));
                                                  TPScanf((int)tp,"counter.font","%i,%i",
                                                          pi4 + 0x4e66,pi4 + 0x4e67);
                                                  TPGetValueInt((int)tp,"counter.shake",
                                                                (uint32_t *)(pi4 + 0x4e68));
                                                  TPScanf((int)tp,"text.font","%i,%i",
                                                          pi4 + 0x4e69,pi4 + 0x4e6a);
                                                  TPScanf((int)tp,"text.offset","%i,%i",
                                                          pi4 + 0x4e6b,pi4 + 0x4e6c);
                                                  TPGetValueInt((int)tp,"displaytime",
                                                                (uint32_t *)(pi4 + 0x4e65));
                                                  i2 = TPGroupSeek((int)tp,"round");
                                                  if (i2 == -1) {
                                                    sysexplod = g + G_ERRMSG;
                                                    pc11 = "Missing round info";
                                                    filename = value;
                                                  }
                                                  else {
                                                    pi4[0x4e77] = 0x1e;
                                                    pi4[0x4e78] = 0x46;
                                                    pi4[0x5038] = 0xa0;
                                                    pi4[0x4fdf] = 0xa0;
                                                    pi4[0x4fc0] = 0xa0;
                                                    pi4[0x5039] = 0x78;
                                                    pi4[0x4fe0] = 0x78;
                                                    pi4[0x4fc1] = 0x78;
                                                    pi4[0x4fc9] = 0x68676946;
                                                    *(uint16_t *)(pi4 + 0x4fca) = 0x2174;
                                                    *(uint8_t *)((int)pi4 + 0x13f2a) = 0;
                                                    pi4[0x4fe8] = 0x4f2e4b;
                                                    pi4[0x4fa4] = 0;
                                                    pi4[0x4fd5] = 0;
                                                    pi4[0x502a] = 0;
                                                    pi4[0x5089] = 0x3c;
                                                    pi4[0x508b] = 0x3c;
                                                    pi4[0x508c] = 0;
                                                    pi4[0x508d] = 10;
                                                    pi4[0x508e] = 0x2d;
                                                    pi4[0x508f] = 0x96;
                                                    pi4[0x4e75] = 2;
                                                    pi4[0x4e76] = 1;
                                                    TPGetValueInt((int)tp,"match.wins",
                                                                  (uint32_t *)(pi4 + 0x4e75));
                                                    TPGetValueInt((int)tp,"match.maxdrawgames",
                                                                  (uint32_t *)(pi4 + 0x4e76));
                                                    TPGetValueInt((int)tp,"start.waittime",
                                                                  (uint32_t *)(pi4 + 0x4e77));
                                                    pu13 = (uint32_t *)(pi4 + 0x4e78);
                                                    pc11 = "intro.time";
                                                    TPGetValueInt((int)tp,"intro.time",pu13);
                                                    TPScanf((int)tp,"pos","%i,%i",
                                                            pi4 + 0x4e79,pi4 + 0x4e7a,pc11,
                                                            pu13,sprites);
                                                    SysExplodParse((int)tp,pi4 + 0x4e7b,
                                                                   "round.default");
                                                    StripDoublePercent((char *)(pi4 + 0x4e8a));
                                                    TPGetValueInt((int)tp,"round.time",
                                                                  (uint32_t *)(pi4 + 0x4fa4));
                                                    pi4[0x4fa5] = pi4[0x4fa4];
                                                    TPGetValueInt((int)tp,"round.sndtime",
                                                                  (uint32_t *)(pi4 + 0x4fa5));
                                                    sysexplod23 = pi4 + 0x4eb1;
                                                    stk_2158 = pi4 + 0x4fa7;
                                                    stk_215c = pi4 + 0x4fb1;
                                                    stk_2160 = 0x4c4;
                                                    i2 = 1;
                                                    do {
                                                      *(uint32_t *)
                                                       (stk_2160 + 4 + (int)(pi4 + 0x4e75)) =
                                                           0xffffffff;
                                                      sprintf(keyname2,"round%i.snd",i2,
                                                              stk_2160);
                                                      TPScanf((int)tp,keyname2,"%i,%i",
                                                              stk_2158,stk_215c);
                                                      i9 = i2 + 1;
                                                      sprintf(keyname2,"round%i",i2);
                                                      SysExplodParse((int)tp,sysexplod23,keyname2
                                                                    );
                                                      sysexplod23 = sysexplod23 + 0x1b;
                                                      stk_2158 = stk_2158 + 1;
                                                      stk_215c = stk_215c + 1;
                                                      stk_2160 = stk_2160 + 4;
                                                      i2 = i9;
                                                    } while (i9 < 10);
                                                    pi4[0x4fd7] = -1;
                                                    SysExplodParse((int)tp,pi4 + 0x4fba,
                                                                   "fight");
                                                    TPGetValueInt((int)tp,"fight.time",
                                                                  (uint32_t *)(pi4 + 0x4fd5));
                                                    pi4[0x4fd6] = pi4[0x4fd5];
                                                    pu13 = (uint32_t *)(pi4 + 0x4fd6);
                                                    pc11 = "fight.sndtime";
                                                    TPGetValueInt((int)tp,"fight.sndtime",
                                                                  pu13);
                                                    TPScanf((int)tp,"fight.snd","%i,%i",
                                                            pi4 + 0x4fd7,pi4 + 0x4fd8,pc11,
                                                            pu13,stk_2158);
                                                    TPGetValueInt((int)tp,"ctrl.time",
                                                                  (uint32_t *)(pi4 + 0x508a));
                                                    pi4[0x5030] = -1;
                                                    pi4[0x502e] = -1;
                                                    pi4[0x502c] = -1;
                                                    SysExplodParse((int)tp,pi4 + 0x4fd9,"KO")
                                                    ;
                                                    SysExplodParse((int)tp,pi4 + 0x4ff4,
                                                                   &str_dko);
                                                    SysExplodParse((int)tp,pi4 + 0x500f,
                                                                   &str_to);
                                                    TPGetValueInt((int)tp,"KO.time",
                                                                  (uint32_t *)(pi4 + 0x502a));
                                                    pi4[0x502b] = pi4[0x502a];
                                                    TPGetValueInt((int)tp,"KO.sndtime",
                                                                  (uint32_t *)(pi4 + 0x502b));
                                                    TPScanf((int)tp,"KO.snd","%i,%i",
                                                            pi4 + 0x502c,pi4 + 0x502d);
                                                    TPScanf((int)tp,"DKO.snd","%i,%i",
                                                            pi4 + 0x502e,pi4 + 0x502f);
                                                    TPScanf((int)tp,"TO.snd","%i,%i",
                                                            pi4 + 0x5030,pi4 + 0x5031);
                                                    pi4[0x502a] = pi4[0x502a] + pi4[0x508d]
                                                    ;
                                                    pi4[0x502b] = pi4[0x502b] + pi4[0x508d]
                                                    ;
                                                    TPGetValueInt((int)tp,"win.time",
                                                                  (uint32_t *)(pi4 + 0x5089));
                                                    SysExplodParse((int)tp,pi4 + 0x5032,"win"
                                                                  );
                                                    SysExplodParse((int)tp,pi4 + 0x504d,
                                                                   &str_win2);
                                                    SysExplodParse((int)tp,pi4 + 0x5068,
                                                                   "draw");
                                                    pi4[0x5087] = -1;
                                                    pi4[0x5085] = -1;
                                                    pi4[0x5083] = -1;
                                                    TPScanf((int)tp,"win.snd","%i,%i",
                                                            pi4 + 0x5083,pi4 + 0x5084);
                                                    TPScanf((int)tp,"lose.snd","%i,%i",
                                                            pi4 + 0x5085,pi4 + 0x5086);
                                                    TPScanf((int)tp,"draw.snd","%i,%i",
                                                            pi4 + 0x5087,pi4 + 0x5088);
                                                    TPGetValueInt((int)tp,"slow.time",
                                                                  (uint32_t *)(pi4 + 0x508b));
                                                    TPGetValueInt((int)tp,"over.waittime",
                                                                  (uint32_t *)(pi4 + 0x508c));
                                                    TPGetValueInt((int)tp,"over.hittime",
                                                                  (uint32_t *)(pi4 + 0x508d));
                                                    TPGetValueInt((int)tp,"over.wintime",
                                                                  (uint32_t *)(pi4 + 0x508e));
                                                    TPGetValueInt((int)tp,"over.time",
                                                                  (uint32_t *)(pi4 + 0x508f));
                                                    i2 = TPGroupSeek((int)tp,"winicon");
                                                    if (i2 == -1) {
                                                      sysexplod = g + G_ERRMSG;
                                                      pc11 = "Missing winicon info";
                                                      value = stale_EDX_04;
                                                      filename = stale_EDX_04;
                                                    }
                                                    else {
                                                      pi12 = pi4 + 0x5090;
                                                      sysexplod33 = pi4 + 0x519e;
                                                      sysexplod31 = pi4 + 0x5168;
                                                      sysexplod32 = pi4 + 0x5183;
                                                      sysexplod30 = pi4 + 0x5117;
                                                      sysexplod29 = pi4 + 0x5132;
                                                      sysexplod28 = pi4 + 0x514d;
                                                      sysexplod27 = pi4 + 0x50fc;
                                                      sysexplod = pi4 + 0x50c6;
                                                      i2 = 0;
                                                      sysexplod24 = pi12;
                                                      sysexplod25 = sysexplod;
                                                      sysexplod26 = pi4 + 0x50e1;
                                                      do {
                                                        i2 = i2 + 1;
                                                        sprintf(keyname2,"p%i.pos",i2,sysexplod);
                                                        TPScanf((int)tp,keyname2,"%i,%i",
                                                                pi12 + 0x21c,pi12 + 0x21e);
                                                        sprintf(keyname2,"p%i.iconoffset",i2);
                                                        sysexplod = pi12 + 0x222;
                                                        sprites = pi12 + 0x220;
                                                        pi12 = pi12 + 1;
                                                        TPScanf((int)tp,keyname2,"%i,%i",sprites,
                                                                sysexplod);
                                                        sprintf(keyname2,"p%i.counter",i2);
                                                        SysExplodParse((int)tp,sysexplod24,
                                                                       keyname2);
                                                        sprintf(keyname2,"p%i.n",i2);
                                                        SysExplodParse((int)tp,sysexplod25,
                                                                       keyname2);
                                                        sprintf(keyname2,"p%i.s",i2);
                                                        SysExplodParse((int)tp,sysexplod26,
                                                                       keyname2);
                                                        sprintf(keyname2,"p%i.h",i2);
                                                        SysExplodParse((int)tp,sysexplod27,
                                                                       keyname2);
                                                        sprintf(keyname2,"p%i.throw",i2);
                                                        SysExplodParse((int)tp,sysexplod28,
                                                                       keyname2);
                                                        sprintf(keyname2,"p%i.t",i2);
                                                        SysExplodParse((int)tp,sysexplod29,
                                                                       keyname2);
                                                        sprintf(keyname2,"p%i.c",i2);
                                                        SysExplodParse((int)tp,sysexplod30,
                                                                       keyname2);
                                                        sprintf(keyname2,"p%i.suicide",i2);
                                                        SysExplodParse((int)tp,sysexplod31,
                                                                       keyname2);
                                                        sprintf(keyname2,"p%i.teammate",i2);
                                                        SysExplodParse((int)tp,sysexplod32,
                                                                       keyname2);
                                                        sprintf(keyname2,"p%i.perfect",i2);
                                                        SysExplodParse((int)tp,sysexplod33,
                                                                       keyname2);
                                                        sysexplod33 = sysexplod33 + 0xf3;
                                                        sysexplod32 = sysexplod32 + 0xf3;
                                                        sysexplod31 = sysexplod31 + 0xf3;
                                                        sysexplod30 = sysexplod30 + 0xf3;
                                                        sysexplod29 = sysexplod29 + 0xf3;
                                                        sysexplod28 = sysexplod28 + 0xf3;
                                                        sysexplod27 = sysexplod27 + 0xf3;
                                                        sysexplod = sysexplod26 + 0xf3;
                                                        sysexplod25 = sysexplod25 + 0xf3;
                                                        sysexplod24 = sysexplod24 + 0x1b;
                                                        sysexplod26 = sysexplod;
                                                      } while (i2 < 2);
                                                      TPGetValueInt((int)tp,"useiconupto",
                                                                    (uint32_t *)(pi4 + 0x52b4));
                                                      if (9 < pi4[0x52b4]) {
                                                        pi4[0x52b4] = 9;
                                                      }
                                                      TPFree(&tp->_flags);
                                                      pi12 = ExplodArrayNew(g[G_CONFIG_EXPLODMAX],g[0x413d]);
                                                      sysexplod = g;
                                                      g[0x52be] = (int)pi12;
                                                      if (pi12 == (int *)0x0) {
                                                        sysexplod = sysexplod + 0x81d2;
                                                        pc11 = "Can\'t allocate explods";
                                                        value = stale_ECX_12;
                                                        filename = stale_ECX_12;
                                                      }
                                                      else {
                                                        pi12 = ExplodArrayNew(sysexplod[0x7574],0);
                                                        sysexplod = g;
                                                        g[0x52bf] = (int)pi12;
                                                        if (pi12 != (int *)0x0) {
                                                          return 1;
                                                        }
                                                        sysexplod = sysexplod + 0x81d2;
                                                        pc11 = "Can\'t allocate sysexplods";
                                                        value = tp;
                                                        filename = tp;
                                                      }
                                                    }
                                                  }
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
L_0809bc03:
  sprintf((char *)sysexplod,pc11,value,filename);
  return 0;
}
#undef stk_2248
#undef stk_2244
#undef stk_2240
#undef stk_223c
#undef stk_2238
#undef stk_2234
#undef sysexplod2
#undef sysexplod3
#undef stk_2228
#undef stk_2224
#undef stk_2220
#undef stk_221c
#undef stk_2218
#undef sysexplod4
#undef sysexplod5
#undef stk_220c
#undef stk_2208
#undef stk_2204
#undef stk_2200
#undef stk_21fc
#undef sysexplod6
#undef sysexplod7
#undef stk_21f0
#undef stk_21ec
#undef stk_21e8
#undef stk_21e4
#undef stk_21e0
#undef stk_21dc
#undef sysexplod8
#undef sysexplod9
#undef sysexplod10
#undef stk_21cc
#undef sysexplod11
#undef stk_21c0
#undef stk_21bc
#undef sysexplod12
#undef stk_21b0
#undef sysexplod13
#undef sysexplod14
#undef stk_21a0
#undef stk_219c
#undef stk_2198
#undef stk_2194
#undef stk_2190
#undef sysexplod15
#undef sysexplod16
#undef sysexplod17
#undef sysexplod18
#undef sysexplod19
#undef sysexplod20
#undef stk_216c
#undef sysexplod21
#undef sysexplod22
#undef stk_2160
#undef stk_215c
#undef stk_2158
#undef sysexplod23
#undef sysexplod24
#undef sysexplod25
#undef sysexplod26
#undef sysexplod27
#undef sysexplod28
#undef sysexplod29
#undef sysexplod30
#undef sysexplod31
#undef sysexplod32
#undef sysexplod33
#undef dirname
#undef filename2
#undef keyname
#undef keyname2

/* GameFreeFightData @ 0x0809bc20, 202 bytes
 *
 * Frees the fight screen data: fonts, animations, sprites, sounds and the
 * explod array.
 *
 * Calls: FontFree, AnimRCFree, SpriteArrayFree, SndArrayFree,
 *        ExplodArrayFree
 * Called by: GameDeInit
 *
 * Elecbyte file: src/mugen/init.c
 */
void GameFreeFightData(void)

{
  void *pv1;
  int *pi2;
  int i3;
  int i4;
  
  i4 = 0x10520;
  i3 = 9;
  pi2 = g;
  do {
    pv1 = *(void **)(i4 + 0xc + (int)pi2);
    if (pv1 != (void *)pi2[0x413a]) {
      FontFree(pv1);
      pi2 = g;
    }
    i4 = i4 + 4;
    i3 = i3 + -1;
  } while (-1 < i3);
  AnimRCFree((int *)pi2[0x414a]);
  SpriteArrayFree((int *)g[0x4149]);
  SndArrayFree((uint32_t *)g[0x4156]);
  SndArrayFree((uint32_t *)g[0x4155]);
  SpriteArrayFree((int *)g[0x4147]);
  AnimRCFree((int *)g[0x4148]);
  ExplodArrayFree((int *)g[0x52bf]);
  ExplodArrayFree((int *)g[0x52be]);
  return;
}

/* GameVarInit @ 0x0809bcf0, 1132 bytes
 *
 * Allocates the game buffers. It creates the back buffer (320x240, or
 * 640x480 for DoubleRes), the priority sprite lists, persistent animations,
 * afterimages, the debug clipboard and the input ring, and checks the
 * version date. Each failure gives a message ("Can't create screen buffer.",
 * "Can't create priority sprites layer 1.", ...).
 *
 * Globals read: errmsg, video_linux_doubleres, config_layeredspritemax,
 *               video_linux_vretrace, config_helpermax
 * Globals written: backbuffer, vretrace, clipboard
 * Calls: GameVarDeInit, MDYDateCmp, V_AllocDepth, V_SetBuf, W_Cls,
 *        PRSprArrayNew, AnimPerArrayNew, GameAftImgArrayNew, ecalloc,
 *        IntCircBufInit, ClipboardNew
 * C library: getcwd, fopen, fclose, remove, time, gmtime, memcpy, srandom,
 *            sprintf
 * Called by: GameInit
 * Messages:
 *   "Can\'t create screen buffer."
 *   "Can\'t create priority sprites layer 1."
 *   "Can\'t create persistent animation array."
 *   "Can\'t init afterimages."
 *   "Can\'t create palgroup array."
 *   "Can\'t create clipboard."
 *
 * Elecbyte file: src/mugen/init.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x30 bytes, 7
 *       variables), because their address is taken.
 */
uint32_t GameVarInit(void)

{
  int *pi1;
  bool b2;
  char *pc3;
  FILE *stream;
  tm *pt4;
  int mem;
  uint32_t *pu6;
  uint32_t stale_var;
  uint32_t seed;
  int *s2;
  int *pi7;
  int *clipboard;
  unsigned char frame[0x30] __attribute__((aligned(16)));
#define stk_30 (*(time_t *)(frame + 0x0))
#define stk_2c (*(int *)(frame + 0x4))
#define stk_28 (*(int *)(frame + 0x8))
#define stk_24 (*(int *)(frame + 0xc))
#define stk_1c (*(int **)(frame + 0x14))
#define stk_18 (*(int *)(frame + 0x18))
#define stk_14 (*(int **)(frame + 0x1c))
  
  pc3 = getcwd((char *)g,0xfff);
  pi7 = g;
  if (pc3 == (char *)0x0) {
L_0809bfc7:
    GameVarDeInit();
  }
  else {
    g[0x804] = MUGENDATE_Y;
    pi7[0x802] = MUGENDATE_M;
    pi7[0x803] = MUGENDATE_D;
    pi7[0x33ae] = 0;
    stream = fopen("_mugen__.tmp","wb");
    if (stream != (FILE *)0x0) {
      g[0x801] = 1;
      fclose(stream);
      remove("_mugen__.tmp");
    }
    time(&stk_30);
    pt4 = gmtime(&stk_30);
    pi7 = (int *)(pt4->tm_year + 0x76c);
    clipboard = (int *)(pt4->tm_mon + 1);
    stk_18 = pt4->tm_mday;
    stk_24 = MUGENEXPDATE_Y;
    stk_2c = MUGENEXPDATE_M;
    stk_28 = MUGENEXPDATE_D;
    stk_1c = clipboard;
    stk_14 = pi7;
    mem = MDYDateCmp((int)clipboard,stk_18,(int)pi7,MUGENEXPDATE_M,MUGENEXPDATE_D,MUGENEXPDATE_Y
                      );
    if (0 < mem) {
      g[0x74e6] = 1;
    }
    mem = V_AllocDepth(0x140,0xf0,0x10);
    pi1 = g;
    g[G_BACKBUFFER] = mem;
    if (mem == 0) {
      GameVarDeInit();
      s2 = g + G_ERRMSG;
      pc3 = "Can\'t create screen buffer.";
      pi7 = clipboard;
    }
    else {
      pi1 = (int *)pi1[0x4136];
      V_SetBuf(pi1,0);
      W_Cls(0);
      clipboard = g + G_VIDEO_LINUX_DOUBLERES;
      g[0x4139] = g[G_BACKBUFFER];
      if (*clipboard != 0) {
        mem = V_AllocDepth(0x280,0x1e0,0x10);
        clipboard = g;
        g[0x4138] = mem;
        if (mem == 0) {
          pi7 = (int *)GameVarDeInit();
          pc3 = "Can\'t create screen buffer.";
          s2 = g + G_ERRMSG;
          goto L_0809c142;
        }
        clipboard[0x4139] = mem;
      }
      pu6 = PRSprArrayNew(g[G_CONFIG_LAYEREDSPRITEMAX]);
      g[0x413d] = (int)pu6;
      if (pu6 == (uint32_t *)0x0) {
        GameVarDeInit();
        s2 = g + G_ERRMSG;
        pc3 = "Can\'t create priority sprites layer 1.";
      }
      else {
        mem = AnimPerArrayNew(0x20);
        clipboard = g;
        g[0x413c] = mem;
        if (mem == 0) {
          GameVarDeInit();
          s2 = g + G_ERRMSG;
          pc3 = "Can\'t create persistent animation array.";
          pi7 = pi1;
        }
        else {
          pu6 = GameAftImgArrayNew(clipboard[0x7571],0x3c);
          g[0x413f] = (int)pu6;
          if (pu6 == (uint32_t *)0x0) {
            pi7 = (int *)GameVarDeInit();
            pc3 = "Can\'t init afterimages.";
            s2 = g + G_ERRMSG;
          }
          else {
            mem = ecalloc(1,0xc);
            clipboard = g;
            g[0x413e] = mem;
            if (mem == 0) {
              GameVarDeInit();
              s2 = g + G_ERRMSG;
              pc3 = "Can\'t create palgroup array.";
            }
            else {
              b2 = IntCircBufInit(clipboard + 0x7391,0x20);
              clipboard = g;
              if (ZEXT8(b2) == 0) goto L_0809bfc7;
              g[G_VRETRACE] = g[G_VIDEO_LINUX_VRETRACE];
              clipboard[0x52bd] = 1;
              memcpy(clipboard + 0x52c0,"system.def",0xb);
              pi1 = g;
              clipboard = g + G_CONFIG_HELPERMAX;
              g[0x7396] = *clipboard;
              pi1[0x7395] = *clipboard + 4;
              *(uint32_t *)((int)pi1 + 0x15aff) = 0x61746164;
              *(uint16_t *)((int)pi1 + 0x15b03) = 0x2f;
              pi1[0x7304] = 0;
              pi1[0x7305] = -1;
              pi1[0x7307] = 0;
              pi1[0x7306] = 0;
              pi1[0x7310] = 0;
              pi1[0x730f] = 0;
              pi1[0x7312] = 0;
              pi1[0x7311] = 0;
              pi1[0x7316] = 0;
              pi1[0x7315] = 0;
              pi1[0x4135] = 0;
              pi1[0x741a] = 1;
              pi1[0x741b] = 1;
              pi1[0x741c] = 0;
              pi1[0x741d] = 0;
              pi1[0x745a] = -1;
              pi1[0x7397] = 4;
              pi1[0x33af] = 1;
              pi1[0x33b0] = 2;
              seed = time((time_t *)0x0);
              g[0x730a] = seed;
              srandom(seed);
              clipboard = ClipboardNew(0x4d,8);
              g[G_CLIPBOARD] = (int)clipboard;
              if (clipboard != (int *)0x0) {
                return 1;
              }
              GameVarDeInit();
              s2 = g + G_ERRMSG;
              pc3 = "Can\'t create clipboard.";
            }
          }
        }
      }
    }
L_0809c142:
    sprintf((char *)s2,pc3,pi7,pi7);
  }
  return 0;
}
#undef stk_30
#undef stk_2c
#undef stk_28
#undef stk_24
#undef stk_1c
#undef stk_18
#undef stk_14

/* GameVarLoadFonts @ 0x0809c160, 153 bytes
 *
 * Loads the built-in debug fonts; on failure sets error 1 ("Can't load
 * fonts").
 *
 * Globals read: errmsg
 * Calls: FontReadFile, ErrorSet, GameVarDeInit
 * C library: memcpy
 * Called by: GameInit
 *
 * Elecbyte file: src/mugen/init.c
 */
uint32_t GameVarLoadFonts(void)

{
  int i1;
  char *src;
  
  i1 = FontReadFile("font/f-4x6.fnt");
  g[0x413a] = i1;
  if (i1 == 0) {
    ErrorSet(1);
    src = "f-4x6.fnt";
  }
  else {
    i1 = FontReadFile("font/f-6x9.fnt");
    g[0x413b] = i1;
    if (i1 != 0) {
      return 1;
    }
    ErrorSet(1);
    src = "f-6x9.fnt";
  }
  memcpy(g + G_ERRMSG,src,10);
  GameVarDeInit();
  return 0;
}

/* GameVarDeInit @ 0x0809c200, 273 bytes
 *
 * Frees the game buffers allocated by GameVarInit.
 *
 * Globals read: backbuffer, clipboard
 * Calls: FontFree, IntCircBufDeInit, PRSprArrayFree, GameAftImgArrayFree,
 *        AnimPerArrayFree, V_DeAlloc, ClipboardFree
 * C library: free
 * Called by: GameDeInit, GameVarInit, GameVarLoadFonts
 *
 * Elecbyte file: src/mugen/init.c
 */
uint32_t GameVarDeInit(void)

{
  uint32_t stale_EAX;
  uint32_t u1;
  
  u1 = 0;
  if (g != (int *)0x0) {
    FontFree((void *)g[0x413a]);
    FontFree((void *)g[0x413b]);
    IntCircBufDeInit(g + 0x7391);
    free((void *)g[0x413e]);
    PRSprArrayFree((uint32_t *)g[0x413d]);
    GameAftImgArrayFree((void *)g[0x413f]);
    AnimPerArrayFree((uint32_t *)g[0x413c]);
    V_DeAlloc(g[G_BACKBUFFER]);
    if (g[0x4137] != 0) {
      V_DeAlloc(g[0x4137]);
    }
    if (g[0x4138] != 0) {
      V_DeAlloc(g[0x4138]);
    }
    if ((uint32_t *)g[G_CLIPBOARD] != (uint32_t *)0x0) {
      ClipboardFree((uint32_t *)g[G_CLIPBOARD]);
    }
    free(g);
    g = (int *)0x0;
    u1 = stale_EAX;
  }
  return u1;
}

/* GameAftImgArrayNew @ 0x0809c320, 140 bytes
 *
 * Creates the global array of afterimage records (one per player slot), each
 * initialised for `length` frames.
 *
 * Parameters:
 *   arg1         size_t
 *   arg2         int
 *
 * Calls: ArrayNew, AftImgInit, GameAftImgArrayFree, ArrayAdd
 * Called by: GameVarInit
 *
 * Elecbyte file: src/mugen/init.c
 * Note: Locals live in `frame`, laid out as on the original stack (0xa0 bytes, 1
 *       variables), because their address is taken.
 */
uint32_t * GameAftImgArrayNew(size_t arg1,int arg2)

{
  uint32_t *array;
  int i2;
  int i3;
  int *pi4;
  unsigned char frame[0xa0] __attribute__((aligned(16)));
#define buf_9c (*(int (*)[35])(frame + 0x4))
  
  array = ArrayNew(arg1,0x7c,0);
  if (array == (uint32_t *)0x0) {
    array = (uint32_t *)0x0;
  }
  else {
    i3 = 0;
    if (0 < (int)arg1) {
      do {
        pi4 = buf_9c;
        for (i2 = 0x1f; i2 != 0; i2 = i2 + -1) {
          *pi4 = 0;
          pi4 = pi4 + 1;
        }
        i2 = AftImgInit(buf_9c,arg2);
        if (i2 == 0) {
          GameAftImgArrayFree(array);
          return (uint32_t *)0x0;
        }
        i2 = i3 + 1;
        ArrayAdd((int)array,buf_9c,0,i3);
        i3 = i2;
      } while (i2 < (int)arg1);
    }
  }
  return array;
}
#undef buf_9c

/* GameAftImgArrayFree @ 0x0809c3b0, 68 bytes
 *
 * Frees the afterimage array and its records.
 *
 * Parameters:
 *   array        void *
 *
 * Calls: ArrayAccessGrpItem, AftImgDeInit, ArrayFree
 * Called by: GameAftImgArrayNew, GameVarDeInit
 *
 * Elecbyte file: src/mugen/init.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 */
uint32_t GameAftImgArrayFree(void *array)

{
  int *item;
  uint32_t u2;
  uint32_t saved_EBX;
  int i3;
  int i4;
  
  if (array != (void *)0x0) {
    i3 = 0;
    if (0 < *(int *)((int)array + 0xc)) {
      do {
        i4 = i3 + 1;
        item = (int *)ArrayAccessGrpItem((int)array,0,i3);
        AftImgDeInit(item);
        i3 = i4;
      } while (i4 < *(int *)((int)array + 0xc));
    }
    u2 = ArrayFree(array);
    return u2;
  }
  return saved_EBX;
}

/* SwitchCallbacksInit @ 0x0809c400, 1 bytes
 *
 * Empty: window switch callbacks are not installed in this build.
 *
 * Called by: GameInit
 *
 * Elecbyte file: src/mugen/init.c
 */
void SwitchCallbacksInit(void)

{
  return;
}

/* SwitchCallbacksDeInit @ 0x0809c410, 1 bytes
 *
 * Empty counterpart of SwitchCallbacksInit.
 *
 * Called by: GameDeInit
 *
 * Elecbyte file: src/mugen/init.c
 */
void SwitchCallbacksDeInit(void)

{
  return;
}

/* SwitchAwayCallback @ 0x0809c420, 20 bytes
 *
 * Called when the window loses focus: suspends keyboard input.
 *
 * Calls: KBSuspend
 *
 * Elecbyte file: src/mugen/init.c
 */
void SwitchAwayCallback(void)

{
  g[0x74e7] = 0;
  KBSuspend();
  return;
}

/* SwitchBackCallback @ 0x0809c440, 36 bytes
 *
 * Called when the window regains focus: resumes keyboard input and
 * resynchronises the key and input flags.
 *
 * Calls: KBResume, KBRefreshflags, UInpRefreshFlags
 *
 * Elecbyte file: src/mugen/init.c
 */
void SwitchBackCallback(void)

{
  g[0x74e7] = 1;
  KBResume();
  KBRefreshflags();
  UInpRefreshFlags();
  return;
}

