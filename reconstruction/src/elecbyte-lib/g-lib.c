/*
 * g-lib.c -- graphics mode
 * Video mode setup through Allegro, page flipping, the sine table, blend
 * mode names and the DoubleRes output filters.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/g-lib.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* G_Init @ 0x08052a50, 69 bytes
 *
 * Initialises the graphics library: allocates a 4 KB scratch block, builds
 * the sine table (Trig_Init) and creates the master palette. On failure sets
 * error 3 ("Can't init graphics"). Returns true on success.
 *
 * Calls: Trig_Init, MasterPalInit, ErrorSet
 * C library: malloc
 * Called by: GameInit
 *
 * Elecbyte file: src/lib/g-lib.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
bool G_Init(void)

{
  bool b1;
  int i2;
  uint32_t stale_var;
  
  TempStore = (int)malloc(0x1000);
  if (((void *)TempStore != (void *)0x0) && (i2 = Trig_Init(), i2 != 0)) {
    b1 = MasterPalInit();
    return ZEXT8(b1) != 0;
  }
  ErrorSet(3);
  return false;
}

/* G_DeInit @ 0x08052aa0, 95 bytes
 *
 * Frees the page-flipping bitmaps, the master palette, the scratch block and
 * the sine table.
 *
 * Calls: MasterPalDeInit, Trig_DeInit
 * C library: destroy_bitmap, free
 * Called by: GameDeInit
 *
 * Elecbyte file: src/lib/g-lib.c
 */
uint32_t G_DeInit(void)

{
  if (G_ScreenPage[0] != 0) {
    destroy_bitmap((int *)G_ScreenPage[0]);
  }
  if (G_ScreenPage[1] != 0) {
    destroy_bitmap((int *)G_ScreenPage[1]);
  }
  MasterPalDeInit();
  if (TempStore != 0) {
    free((void *)TempStore);
  }
  TempStore = 0;
  Trig_DeInit();
  return 1;
}

/* G_SetRenderMode @ 0x08052b00, 29 bytes
 *
 * Sets the render mode (0-2); other values are ignored. Mode 0 makes
 * palettes follow the master palette.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: GameInit
 *
 * Elecbyte file: src/lib/g-lib.c
 */
uint32_t G_SetRenderMode(int arg1)

{
  if ((arg1 < 3) && (-1 < arg1)) {
    G_RenderMode = arg1;
    return 1;
  }
  return 0;
}

/* G_SetMode @ 0x08052b20, 405 bytes
 *
 * Sets the video mode: Allegro set_gfx_mode(driver, width, height) at colour
 * depth `depth` (driver -1 = text mode, depth 8). It destroys old page-flip
 * bitmaps, resets the blit mode, records the driver capabilities and sets
 * the screen globals (S_Width, S_Height, G_ColDepth, bytes per pixel,
 * V_ColDepth). Red/blue swapping is turned off. On failure sets error 4
 * ("Can't change video mode"). Returns 1 on success, 0 on failure.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Calls: ErrorSet
 * C library: destroy_bitmap, set_color_depth, set_gfx_mode
 * Called by: DebugErrorExit, ErrorExit, GameDeInit, GameInit, GfxResize
 *
 * Elecbyte file: src/lib/g-lib.c
 */
uint32_t G_SetMode(uint32_t arg1,int arg2,int arg3,int arg4)

{
  int i1;
  uint32_t u2;
  
  if (G_ScreenPage[0] != 0) {
    destroy_bitmap((int *)G_ScreenPage[0]);
  }
  if (G_ScreenPage[1] != 0) {
    destroy_bitmap((int *)G_ScreenPage[1]);
  }
  G_ScreenPage[1] = 0;
  G_ScreenPage[0] = 0;
  G_Screenptr = (int *)0x0;
  G_BlitMode = 0;
  G_BlitModeAuto = 0;
  set_color_depth(8);
  if (arg1 != 0xffffffff) {
    set_color_depth(arg4);
  }
  i1 = set_gfx_mode(arg1,arg2,arg3,0,0);
  if (i1 < 0) {
    ErrorSet(4);
    u2 = 0;
  }
  else {
    G_Capabilities = (int)((gfx_capabilities & 1) != 0);
    if ((gfx_capabilities & 2) != 0) {
      G_Capabilities = G_Capabilities | 2;
    }
    S_Width = arg2;
    S_Size = arg2 * arg3;
    S_Height = arg3;
    G_ColDepth = arg4;
    switch(arg4) {
    case 8:
      G_BytesPerPixel = 1;
      break;
    default:
      G_BytesPerPixel = 2;
      break;
    case 0x18:
      G_BytesPerPixel = 3;
      break;
    case 0x20:
      G_BytesPerPixel = 4;
    }
    G_CurMode = arg1;
    V_ColDepth = arg4;
    V_BytesPerPixel = G_BytesPerPixel;
    G_Screenptr = screen;
    u2 = 1;
    scrRGB16toBGR32 = 0;
  }
  return u2;
}

/* G_MakeColor @ 0x08052cc0, 5 bytes
 *
 * Returns the screen colour for (r, g, b) (Allegro makecol).
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         int
 *   arg3         int
 *
 * C library: makecol
 * Called by: EB_GUIDrawWindow, EB_GUINewWindow
 *
 * Elecbyte file: src/lib/g-lib.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to
 *       makecol_depth
 */
uint32_t G_MakeColor(uint32_t arg1,int arg2,int arg3)

{
  uint32_t u1;
  
  u1 = makecol(arg1,arg2,arg3);
  return u1;
}

/* G_SetRGBtoBGR @ 0x08052cd0, 56 bytes
 *
 * Turns red/blue swapping for 16-to-32-bit output on or off by exchanging
 * Allegro's 16-bit red and blue shifts.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: GameInit
 *
 * Elecbyte file: src/lib/g-lib.c
 */
void G_SetRGBtoBGR(int arg1)

{
  uint32_t u1;
  
  u1 = _rgb_r_shift_16;
  if ((scrRGB16toBGR32 == 0) != (arg1 == 0)) {
    scrRGB16toBGR32 = arg1;
    _rgb_r_shift_16 = _rgb_b_shift_16;
    _rgb_b_shift_16 = u1;
  }
  return;
}

/* G_SetBlitMode @ 0x08052d10, 310 bytes
 *
 * Chooses how frames reach the screen: 0 direct to `screen`, 1 page flipping
 * with two video bitmaps. When video bitmaps cannot be created it falls back
 * to mode 0.
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t
 *
 * C library: destroy_bitmap, create_video_bitmap
 * Called by: GameInit, GfxResize
 *
 * Elecbyte file: src/lib/g-lib.c
 */
uint32_t G_SetBlitMode(int arg1,uint32_t arg2)

{
  int *pi1;
  int *pi2;
  
  if (arg1 != G_BlitMode) {
    if (G_ScreenPage[0] != 0) {
      destroy_bitmap((int *)G_ScreenPage[0]);
    }
    if (G_ScreenPage[1] != 0) {
      destroy_bitmap((int *)G_ScreenPage[1]);
    }
    G_Screenptr = screen;
    G_ScreenPage[1] = 0;
    G_ScreenPage[0] = 0;
    if (arg1 != 0) {
      if ((arg1 != 1) || (pi1 = create_video_bitmap(S_Width,S_Height), pi1 == (int *)0x0))
      {
        return 0;
      }
      pi2 = create_video_bitmap(S_Width,S_Height);
      if (pi2 == (int *)0x0) {
        destroy_bitmap(pi1);
        return 0;
      }
      G_Screenptr = pi2;
      G_ScreenPage[0] = (int)pi1;
      G_ScreenPage[1] = (int)pi2;
      (**(generic_fn **)(pi1[7] + 0x94))(pi1,0,pi2,pi2);
      (**(generic_fn **)(pi2[7] + 0x94))(pi2,0);
    }
    G_BlitMode = arg1;
    G_BlitModeAuto = arg2 & (arg1 == 0) - 1;
  }
  return 1;
}

/* G_PageFlip @ 0x08052e50, 76 bytes
 *
 * In page-flipping mode, shows the page just drawn (show_video_bitmap) and
 * switches drawing to the other page.
 *
 * C library: show_video_bitmap
 * Called by: V_BufToScreen, V_BufToScreenStretch, V_BufToScreenXY
 *
 * Elecbyte file: src/lib/g-lib.c
 */
void G_PageFlip(void)

{
  bool b1;
  
  if (G_BlitMode == 1) {
    if ((G_Screenptr == (int *)G_ScreenPage[0]) || (G_Screenptr == (int *)G_ScreenPage[1])) {
      show_video_bitmap(G_Screenptr);
    }
    b1 = G_Screenptr == (int *)G_ScreenPage[0];
    G_Screenptr = (int *)G_ScreenPage[0];
    if (b1) {
      G_Screenptr = (int *)G_ScreenPage[1];
    }
  }
  return;
}

/* VGA_Cls @ 0x08052ea0, 24 bytes
 *
 * Clears the screen to colour 0.
 *
 * Elecbyte file: src/lib/g-lib.c
 */
void VGA_Cls(void)

{
  (**(generic_fn **)(*(int *)(screen + 0x1c) + 0x94))(screen,0);
  return;
}

/* VRetrace @ 0x08052ec0, 5 bytes
 *
 * Waits for the vertical retrace (Allegro vsync). Used when the VRetrace
 * option is on.
 *
 * C library: vsync
 * Called by: CharacterSelectScreenDraw, ContinueScreenLoop, GameLoop,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, PlayCutscene,
 *            VersusScreen
 *
 * Elecbyte file: src/lib/g-lib.c
 */
uint32_t VRetrace(void)

{
  uint32_t u1;
  
  u1 = vsync();
  return u1;
}

/* sgn @ 0x08052ed0, 24 bytes
 *
 * Returns the sign of an int: -1, 0 or 1.
 *
 * Parameters:
 *   arg1         uint32_t
 *
 * Elecbyte file: src/lib/g-lib.c
 */
int sgn(uint32_t arg1)

{
  if (0 < (int)arg1) {
    return 1;
  }
  return -1 - ((int)(arg1 ^ 0xffffffff) >> 0x1f);
}

/* GetDrawType @ 0x08052ef0, 205 bytes
 *
 * Parses a blend mode name into the engine's blend code: "none" 0, "add" 1,
 * "sub" 2, "addalpha" 3 (alpha left to the caller), "add1" 3 with alpha
 * 256/128. An empty string or "default" gives -1, anything else -2. Used for
 * the trans parameters of backgrounds, explods and afterimages.
 *
 * Parameters:
 *   arg1         char *
 *   arg2         uint32_t *
 *   arg3         uint32_t *
 *
 * C library: _alemu_stricmp
 * Called by: BGArrayReadTP, SCtrlParseAftImgParams, SCtrlParseExplod
 *
 * Elecbyte file: src/lib/g-lib.c
 */
uint32_t GetDrawType(char *arg1,uint32_t *arg2,uint32_t *arg3)

{
  int i1;
  uint32_t u2;
  
  i1 = _alemu_stricmp(arg1,"none");
  u2 = 0;
  if (i1 != 0) {
    i1 = _alemu_stricmp(arg1,"add");
    u2 = 1;
    if (i1 != 0) {
      i1 = _alemu_stricmp(arg1,"addalpha");
      u2 = 3;
      if (i1 != 0) {
        i1 = _alemu_stricmp(arg1,"add1");
        if (i1 == 0) {
          u2 = 3;
          *arg2 = 0x100;
          *arg3 = 0x80;
        }
        else {
          i1 = _alemu_stricmp(arg1,"sub");
          u2 = 2;
          if (i1 != 0) {
            if ((*arg1 == '\0') || (i1 = _alemu_stricmp(arg1,"default"), i1 == 0)) {
              u2 = 0xffffffff;
            }
            else {
              u2 = 0xfffffffe;
            }
          }
        }
      }
    }
  }
  return u2;
}

/* Trig_Init @ 0x08052fc0, 183 bytes
 *
 * Builds the sine lookup table: 3600 entries in steps of 1/8 degree (0 to
 * 450 degrees, so cosines can be read at an offset of 90 degrees), used by
 * the rotating blitters. Returns 0 if allocation fails.
 *
 * C library: malloc, fsin
 * Called by: G_Init
 *
 * Elecbyte file: src/lib/g-lib.c
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 */
uint32_t Trig_Init(void)

{
  int *pi1;
  uint32_t u2;
  int i2;
  float80 l4;
  
  if (SinTable == (int *)0x0) {
    SinTable = malloc(0x3840);
  }
  i2 = 0;
  if (SinTable == (int *)0x0) {
    u2 = 0;
  }
  else {
    do {
      l4 = (float80)
              fsin((float80)i2 * (float80)((double)0.01745329238474369) * (float80)0.125);
      SinTable[i2] = (int)X87_FIST32(l4 * (float80)1024.0);
      pi1 = SinTable;
      i2 = i2 + 1;
    } while (i2 < 0xe10);
    *SinTable = 0;
    pi1[0x2d0] = 0x400;
    pi1[0x5a0] = 0;
    pi1[0x870] = -0x400;
    pi1[0xb40] = 0;
    u2 = 1;
  }
  return u2;
}

/* Trig_DeInit @ 0x08053080, 33 bytes
 *
 * Frees the sine lookup table.
 *
 * C library: free
 * Called by: G_DeInit
 *
 * Elecbyte file: src/lib/g-lib.c
 */
uint32_t Trig_DeInit(void)

{
  if (SinTable != (int *)0x0) {
    free(SinTable);
  }
  return 1;
}

/* V_DoubleRes @ 0x080530b0, 154 bytes
 *
 * Doubles a 15/16-bit image into a buffer twice its size by pixel repetition
 * (each pixel becomes a 2x2 block). Used for "DoubleRes" output modes.
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         int
 *
 * Called by: DrawToScreen, GameLoop
 *
 * Elecbyte file: src/lib/g-lib.c
 */
void V_DoubleRes(uint32_t *arg1,int arg2)

{
  uint16_t u1;
  uint16_t u2;
  int i3;
  int i4;
  uint32_t u5;
  uint32_t u6;
  uint32_t u7;
  uint16_t *pu8;
  uint16_t *pu9;
  uint32_t *pu10;
  uint32_t *pu11;
  
  u5 = arg1[1];
  i4 = *(int *)arg1[7];
  if ((((i4 == 0xf) || (i4 == 0x10)) &&
      ((i3 = **(int **)(arg2 + 0x1c), i3 == 0xf || (i3 == 0x10)))) &&
     ((i4 == i3 && ((*arg1 & 3) == 0)))) {
    pu11 = *(uint32_t **)(arg2 + 0x28);
    u6 = *arg1 >> 2;
    pu8 = (uint16_t *)arg1[10];
    u7 = u6;
    do {
      do {
        u1 = *pu8;
        u2 = pu8[1];
        pu9 = pu8 + 4;
        *(uint16_t *)pu11 = u1;
        *(uint16_t *)((int)pu11 + 2) = u1;
        u1 = pu8[2];
        *(uint16_t *)(pu11 + 1) = u2;
        *(uint16_t *)((int)pu11 + 6) = u2;
        u2 = pu8[3];
        *(uint16_t *)(pu11 + 2) = u1;
        *(uint16_t *)((int)pu11 + 10) = u1;
        *(uint16_t *)(pu11 + 3) = u2;
        *(uint16_t *)((int)pu11 + 0xe) = u2;
        pu11 = pu11 + 4;
        u6 = u6 - 1;
        pu8 = pu9;
      } while (u6 != 0);
      pu10 = pu11 + u7 * -4;
      for (i4 = u7 * 4; i4 != 0; i4 = i4 + -1) {
        *pu11 = *pu10;
        pu10 = pu10 + 1;
        pu11 = pu11 + 1;
      }
      u6 = u7 & 0xfffffff;
      u5 = u5 - 1;
      u7 = u6;
    } while (u5 != 0);
  }
  return;
}

/* V_DoubleResDiag @ 0x08053150, 698 bytes
 *
 * Doubles a 15/16-bit image with diagonal interpolation: the extra pixels
 * are averages of neighbours, which smooths edges. The rebuild patches one
 * call site so this mode does not overrun the buffer (see reconstruction
 * notes, problem #33).
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *
 * Called by: DrawToScreen
 *
 * Elecbyte file: src/lib/g-lib.c
 * Note: 2 exact-text site patches (see SITE_PATCHES in
 *       tools/build_source_tree.py)
 */
void V_DoubleResDiag(int *arg1,int arg2)

{
  uint16_t u1;
  short s2;
  uint16_t *pu3;
  short *ps4;
  short *pu5;
  short *ps6;
  int i7;
  int i8;
  
  i7 = *(int *)arg1[7];
  if ((((i7 == 0xf) || (i7 == 0x10)) &&
      ((i8 = **(int **)(arg2 + 0x1c), i8 == 0xf || (i8 == 0x10)))) && (i7 == i8))
  {
    pu5 = (short *)arg1[10];
    pu3 = *(uint16_t **)(arg2 + 0x28);
    u1 = *pu5;
    *pu3 = u1;
    pu3[1] = u1;
    pu3[0x280] = u1;
    pu3[0x281] = u1;
    if (pu5[1] == pu5[0x140]) {
      pu3[0x281] = pu5[1];
    }
    pu5 = pu5 + 1;
    pu3 = pu3 + 2;
    if (1 < *arg1 + -1) {
      i7 = *arg1 + -2;
      do {
        u1 = *pu5;
        *pu3 = u1;
        pu3[1] = u1;
        pu3[0x280] = u1;
        pu3[0x281] = u1;
        s2 = pu5[0x140];
        if (pu5[-1] == s2) {
          pu3[0x280] = pu5[-1];
          s2 = pu5[0x140];
        }
        if (pu5[1] == s2) {
          pu3[0x281] = pu5[1];
        }
        pu5 = pu5 + 1;
        pu3 = pu3 + 2;
        i7 = i7 + -1;
      } while (i7 != 0);
    }
    u1 = *pu5;
    *pu3 = u1;
    pu3[1] = u1;
    pu3[0x280] = u1;
    pu3[0x281] = u1;
    if (pu5[-1] == pu5[0x140]) {
      pu3[0x280] = pu5[-1];
    }
    ps6 = pu5 + 1;
    ps4 = pu3 + 0x282;
    if (1 < arg1[1] + -1) {
      i7 = arg1[1] + -2;
      do {
        s2 = *ps6;
        *ps4 = s2;
        ps4[1] = s2;
        ps4[0x280] = s2;
        ps4[0x281] = s2;
        s2 = ps6[1];
        if (s2 == ps6[-0x140]) {
          ps4[1] = s2;
        }
        if (s2 == ps6[0x140]) {
          ps4[0x281] = s2;
        }
        ps6 = ps6 + 1;
        ps4 = ps4 + 2;
        if (1 < *arg1 + -1) {
          i8 = *arg1 + -2;
          do {
            s2 = *ps6;
            *ps4 = s2;
            ps4[1] = s2;
            ps4[0x280] = s2;
            ps4[0x281] = s2;
            s2 = ps6[-1];
            if (s2 == ps6[-0x140]) {
              *ps4 = s2;
            }
            if (s2 == ps6[0x140]) {
              ps4[0x280] = s2;
            }
            s2 = ps6[1];
            if (s2 == ps6[-0x140]) {
              ps4[1] = s2;
            }
            if (s2 == ps6[0x140]) {
              ps4[0x281] = s2;
            }
            ps6 = ps6 + 1;
            ps4 = ps4 + 2;
            i8 = i8 + -1;
          } while (i8 != 0);
        }
        s2 = *ps6;
        *ps4 = s2;
        ps4[1] = s2;
        ps4[0x280] = s2;
        ps4[0x281] = s2;
        s2 = ps6[-1];
        if (s2 == ps6[-0x140]) {
          *ps4 = s2;
        }
        if (s2 == ps6[0x140]) {
          ps4[0x280] = s2;
        }
        ps6 = ps6 + 1;
        ps4 = ps4 + 0x282;
        i7 = i7 + -1;
      } while (i7 != 0);
    }
    s2 = *ps6;
    *ps4 = s2;
    ps4[1] = s2;
    ps4[0x280] = s2;
    ps4[0x281] = s2;
    if (ps6[1] == ps6[-0x140]) {
      ps4[1] = ps6[1];
    }
    ps6 = ps6 + 1;
    ps4 = ps4 + 2;
    if (1 < *arg1 + -1) {
      i7 = *arg1 + -2;
      do {
        s2 = *ps6;
        *ps4 = s2;
        ps4[1] = s2;
        ps4[0x280] = s2;
        ps4[0x281] = s2;
        s2 = ps6[-0x140];
        if (ps6[-1] == s2) {
          *ps4 = ps6[-1];
          s2 = ps6[-0x140];
        }
        if (ps6[1] == s2) {
          ps4[1] = ps6[1];
        }
        ps6 = ps6 + 1;
        ps4 = ps4 + 2;
        i7 = i7 + -1;
      } while (i7 != 0);
    }
    s2 = *ps6;
    *ps4 = s2;
    ps4[1] = s2;
    ps4[0x280] = s2;
    ps4[0x281] = s2;
    if (ps6[-1] == ps6[-0x140]) {
      *ps4 = ps6[-1];
    }
  }
  return;
}

/* V_DoubleResBlur @ 0x08053410, 1131 bytes
 *
 * Doubles a 15/16-bit image with a blur: every output pixel is an average of
 * the neighbouring source pixels.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *
 * Called by: DrawToScreen
 *
 * Elecbyte file: src/lib/g-lib.c
 */
void V_DoubleResBlur(int *arg1,int arg2)

{
  short s1;
  short s2;
  int i3;
  int i4;
  short s5;
  short s6;
  short s7;
  short *ps8;
  short *ps9;
  short *stk_1c;
  int stk_18;
  int stk_14;
  
  i3 = *(int *)arg1[7];
  if ((((i3 == 0xf) || (i3 == 0x10)) &&
      ((i4 = **(int **)(arg2 + 0x1c), i4 == 0xf || (i4 == 0x10)))) && (i3 == i4))
  {
    stk_1c = *(short **)(arg2 + 0x28);
    ps9 = (short *)arg1[10];
    s1 = ps9[1];
    s2 = ps9[0x140];
    ps8 = ps9 + 1;
    s5 = (short)((int)((int)*ps9 & 0xf7deU) >> 1);
    *stk_1c = s5 * 2;
    s1 = (short)((int)((int)s1 & 0xe79cU) >> 2);
    stk_1c[1] = s5 + s1 * 2;
    s2 = (short)((int)((int)s2 & 0xe79cU) >> 2);
    stk_1c[0x280] = s5 + s2 * 2;
    stk_1c[0x281] = s1 + s5 + s2;
    stk_1c = stk_1c + 2;
    if (1 < *arg1 + -1) {
      stk_14 = *arg1 + -2;
      do {
        s1 = ps8[1];
        s2 = ps8[0x140];
        s6 = (short)((int)((int)ps8[-1] & 0xe79cU) >> 2);
        s5 = (short)((int)((int)*ps8 & 0xf7deU) >> 1);
        *stk_1c = s5 + s6 * 2;
        s7 = (short)((int)((int)s1 & 0xe79cU) >> 2);
        stk_1c[1] = s5 + s7 * 2;
        ps8 = ps8 + 1;
        s1 = (short)((int)((int)s2 & 0xe79cU) >> 2);
        stk_1c[0x280] = s6 + s5 + s1;
        stk_1c[0x281] = s7 + s5 + s1;
        stk_1c = stk_1c + 2;
        stk_14 = stk_14 + -1;
      } while (stk_14 != 0);
    }
    s1 = ps8[-1];
    s2 = ps8[0x140];
    s5 = (short)((int)((int)*ps8 & 0xf7deU) >> 1);
    *stk_1c = s5 * 2;
    s1 = (short)((int)((int)s1 & 0xe79cU) >> 2);
    stk_1c[1] = s5 + s1 * 2;
    s2 = (short)((int)((int)s2 & 0xe79cU) >> 2);
    stk_1c[0x280] = s5 + s2 * 2;
    ps8 = ps8 + 1;
    stk_1c[0x281] = s1 + s5 + s2;
    stk_1c = stk_1c + 0x282;
    if (1 < arg1[1] + -1) {
      stk_18 = arg1[1] + -2;
      i3 = *arg1;
      do {
        s1 = ps8[1];
        s2 = ps8[0x140];
        s6 = (short)((int)((int)ps8[-0x140] & 0xe79cU) >> 2);
        s5 = (short)((int)((int)*ps8 & 0xf7deU) >> 1);
        *stk_1c = s5 + s6 * 2;
        s1 = (short)((int)((int)s1 & 0xe79cU) >> 2);
        ps8 = ps8 + 1;
        stk_1c[1] = s1 + s5 + s6;
        s2 = (short)((int)((int)s2 & 0xe79cU) >> 2);
        stk_1c[0x280] = s5 + s2 * 2;
        stk_1c[0x281] = s2 + s5 + s1;
        stk_1c = stk_1c + 2;
        if (1 < i3 + -1) {
          stk_14 = i3 + -2;
          do {
            s1 = ps8[0x140];
            s2 = ps8[1];
            ps9 = ps8 + -0x140;
            s6 = (short)((int)((int)ps8[-1] & 0xe79cU) >> 2);
            s7 = (short)((int)((int)*ps8 & 0xf7deU) >> 1);
            ps8 = ps8 + 1;
            s5 = (short)((int)((int)*ps9 & 0xe79cU) >> 2);
            *stk_1c = s6 + s7 + s5;
            s2 = (short)((int)((int)s2 & 0xe79cU) >> 2);
            stk_1c[1] = s2 + s7 + s5;
            s7 = (short)((int)((int)s1 & 0xe79cU) >> 2) + s7;
            stk_1c[0x280] = s6 + s7;
            stk_1c[0x281] = s7 + s2;
            stk_1c = stk_1c + 2;
            stk_14 = stk_14 + -1;
          } while (stk_14 != 0);
        }
        s1 = ps8[0x140];
        s5 = (short)((int)((int)ps8[-1] & 0xe79cU) >> 2);
        s6 = (short)((int)((int)*ps8 & 0xf7deU) >> 1);
        s2 = (short)((int)((int)ps8[-0x140] & 0xe79cU) >> 2);
        ps8 = ps8 + 1;
        *stk_1c = s5 + s6 + s2;
        stk_1c[1] = s6 + s2 * 2;
        s1 = (short)((int)((int)s1 & 0xe79cU) >> 2);
        stk_1c[0x280] = s1 + s6 + s5;
        stk_1c[0x281] = s6 + s1 * 2;
        stk_1c = stk_1c + 0x282;
        stk_18 = stk_18 + -1;
      } while (stk_18 != 0);
    }
    s1 = ps8[1];
    ps9 = ps8 + 1;
    s5 = (short)((int)((int)ps8[-0x140] & 0xe79cU) >> 2);
    s2 = (short)((int)((int)*ps8 & 0xf7deU) >> 1);
    *stk_1c = s2 + s5 * 2;
    s1 = (short)((int)((int)s1 & 0xe79cU) >> 2);
    stk_1c[1] = s1 + s2 + s5;
    stk_1c[0x280] = s2 * 2;
    stk_1c[0x281] = s2 + s1 * 2;
    stk_1c = stk_1c + 2;
    if (1 < *arg1 + -1) {
      stk_14 = *arg1 + -2;
      do {
        s1 = ps9[1];
        s5 = (short)((int)((int)ps9[-1] & 0xe79cU) >> 2);
        s6 = (short)((int)((int)*ps9 & 0xf7deU) >> 1);
        s2 = (short)((int)((int)ps9[-0x140] & 0xe79cU) >> 2);
        ps9 = ps9 + 1;
        *stk_1c = s5 + s6 + s2;
        s1 = (short)((int)((int)s1 & 0xe79cU) >> 2);
        stk_1c[1] = s1 + s6 + s2;
        stk_1c[0x280] = s6 + s5 * 2;
        stk_1c[0x281] = s6 + s1 * 2;
        stk_1c = stk_1c + 2;
        stk_14 = stk_14 + -1;
      } while (stk_14 != 0);
    }
    s2 = (short)((int)((int)ps9[-1] & 0xe79cU) >> 2);
    s5 = (short)((int)((int)*ps9 & 0xf7deU) >> 1);
    s1 = (short)((int)((int)ps9[-0x140] & 0xe79cU) >> 2);
    *stk_1c = s2 + s5 + s1;
    stk_1c[1] = s5 + s1 * 2;
    stk_1c[0x280] = s5 + s2 * 2;
    stk_1c[0x281] = s5 * 2;
  }
  return;
}

/* V_DoubleResLines @ 0x08053880, 133 bytes
 *
 * Doubles a 15/16-bit image as scanlines: each pixel is doubled horizontally
 * and every second output line is left untouched (dark scanlines).
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         int
 *
 * Called by: DrawToScreen
 *
 * Elecbyte file: src/lib/g-lib.c
 */
void V_DoubleResLines(uint32_t *arg1,int arg2)

{
  uint16_t u1;
  uint16_t u2;
  int i3;
  int i4;
  uint32_t u5;
  uint32_t u6;
  uint32_t u7;
  uint16_t *pu8;
  uint16_t *pu9;
  uint16_t *pu10;
  
  i3 = *(int *)arg1[7];
  if ((((i3 == 0xf) || (i3 == 0x10)) &&
      ((i4 = **(int **)(arg2 + 0x1c), i4 == 0xf || (i4 == 0x10)))) && (i3 == i4))
  {
    u5 = *arg1;
    u7 = arg1[1];
    u6 = u5 >> 2;
    pu8 = (uint16_t *)arg1[10];
    pu9 = *(uint16_t **)(arg2 + 0x28);
    do {
      do {
        pu10 = pu9;
        u1 = *pu8;
        u2 = pu8[1];
        pu9 = pu8 + 4;
        *pu10 = u1;
        pu10[1] = u1;
        u1 = pu8[2];
        pu10[2] = u2;
        pu10[3] = u2;
        u2 = pu8[3];
        pu10[4] = u1;
        pu10[5] = u1;
        pu10[6] = u2;
        pu10[7] = u2;
        u6 = u6 - 1;
        pu8 = pu9;
        pu9 = pu10 + 8;
      } while (u6 != 0);
      u7 = u7 - 1;
      u6 = u5 >> 2;
      pu9 = pu10 + 0x288;
    } while (u7 != 0);
  }
  return;
}

