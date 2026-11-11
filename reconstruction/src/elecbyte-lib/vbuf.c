/*
 * vbuf.c -- drawing buffers and primitives
 * Off-screen drawing buffers, the clipping window, copying buffers to the
 * screen, and pixels, lines and boxes in plain and blended forms.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/vbuf.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* V_Alloc @ 0x0807ce40, 29 bytes
 *
 * Allocates a drawing buffer of width x height in the current colour depth
 * (V_AllocDepth).
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Calls: V_AllocDepth
 * Called by: EB_GUINewWindow
 *
 * Elecbyte file: src/lib/vbuf.c
 */
uint32_t V_Alloc(int arg1,int arg2)

{
  uint32_t u1;
  
  u1 = V_AllocDepth(arg1,arg2,G_ColDepth);
  return u1;
}

/* V_AllocDepth @ 0x0807ce60, 29 bytes
 *
 * Allocates one drawing buffer of the given size and depth (V_AllocDepthAry
 * with one page).
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *
 * Calls: V_AllocDepthAry
 * Called by: GameVarInit, V_Alloc
 *
 * Elecbyte file: src/lib/vbuf.c
 */
int * V_AllocDepth(int arg1,int arg2,int arg3)

{
  int *pi1;
  
  pi1 = V_AllocDepthAry(arg1,arg2,arg3,1);
  return pi1;
}

/* V_AllocDepthAry @ 0x0807ce80, 215 bytes
 *
 * Allocates a sprite array of `pages` Allegro bitmaps (create_bitmap_ex) of
 * the given size and depth, usable as drawing buffers. Returns NULL on
 * failure.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         size_t
 *
 * Calls: SpriteArrayNewSize, SpriteArrayFree, SpriteInit,
 *        SpriteArrayAddSprite
 * C library: create_bitmap_ex, set_clip, set_color_depth
 * Called by: V_AllocDepth
 *
 * Elecbyte file: src/lib/vbuf.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x60 bytes, 2
 *       variables), because their address is taken.
 */
int * V_AllocDepthAry(int arg1,int arg2,int arg3,size_t arg4)

{
  int *sprites;
  uint32_t *pu2;
  int i3;
  int i4;
  unsigned char frame[0x60] __attribute__((aligned(16)));
#define buf_5c (*(int (*)[6])(frame + 0x4))
#define stk_44 (*(uint32_t *)(frame + 0x1c))
  
  sprites = SpriteArrayNewSize(arg4,1);
  if (sprites == (int *)0x0) {
    sprites = (int *)0x0;
  }
  else {
    i3 = 0;
    if (0 < (int)arg4) {
      do {
        pu2 = (uint32_t *)create_bitmap_ex(arg3,arg1,arg2);
        if (pu2 == (uint32_t *)0x0) {
          SpriteArrayFree(sprites);
          return (int *)0x0;
        }
        set_clip(pu2,0,0,arg1 - 1,arg2 - 1);
        set_color_depth(arg3);
        SpriteInit(buf_5c,1,pu2,0x40,0,arg1,arg2,arg3,0,0);
        stk_44 = 1;
        i4 = i3 + 1;
        SpriteArrayAddSprite(sprites,buf_5c,0,i3);
        i3 = i4;
      } while (i4 < (int)arg4);
    }
  }
  return sprites;
}
#undef buf_5c
#undef stk_44

/* V_DeAlloc @ 0x0807cf60, 60 bytes
 *
 * Frees a drawing buffer (its bitmaps and the sprite array).
 *
 * Parameters:
 *   sprites      int
 *
 * Calls: SpriteArrayFree
 * Called by: EB_GUICloseWindow, GameVarDeInit
 *
 * Elecbyte file: src/lib/vbuf.c
 */
uint32_t V_DeAlloc(int sprites)

{
  if (sprites != 0) {
    if (V_Current == (int *)sprites) {
      V_Current = (int *)0x0;
      V_CurrentIdx = 0;
    }
    SpriteArrayFree((int *)sprites);
  }
  return 1;
}

/* V_SetBuf @ 0x0807cfa0, 144 bytes
 *
 * Makes page `index` of a drawing buffer the current drawing target: it sets
 * V_Current, V_Width, V_Height, V_ColDepth, the bytes per pixel and the
 * clipping window (whole buffer). Returns 0 if the page is not a raw or
 * bitmap sprite.
 *
 * Parameters:
 *   buffer       int *
 *   index        int
 *
 * Calls: SpriteArrayAccess, W_Define
 * C library: set_color_depth
 * Called by: CharacterSelectScreen, ContinueScreenLoop, EB_GUIClearWindow,
 *            EB_GUIDrawWindow, EB_GUINewWindow, EB_GUIPutSprite, GameLoop,
 *            GameVarInit, GfxResize, KeyConfigScreen, ModeSelect,
 *            OptionsScreen, PlayCutscene, VersusScreen, _mangled_main
 *
 * Elecbyte file: src/lib/vbuf.c
 */
uint32_t V_SetBuf(int *buffer,int index)

{
  int *sprite;
  uint32_t u2;
  
  sprite = (int *)SpriteArrayAccess(buffer,index);
  if ((sprite == (int *)0x0) || (1 < (uint32_t)sprite[7])) {
    u2 = 0;
  }
  else {
    V_Current = buffer;
    V_Width = *sprite;
    V_Height = sprite[1];
    V_ColDepth = sprite[4];
    V_Size = V_Width * V_Height;
    V_BytesPerPixel = V_ColDepth + 7 >> 3;
    V_CurrentIdx = index;
    W_Skip = 0;
    W_Define(0,0,V_Width - 1,V_Height - 1);
    set_color_depth(V_ColDepth);
    u2 = 1;
  }
  return u2;
}

/* V_BufGetSurface @ 0x0807d030, 42 bytes
 *
 * Returns the Allegro bitmap of page `index` of a drawing buffer, or NULL.
 *
 * Parameters:
 *   buffer       int *
 *   index        int
 *
 * Calls: SpriteArrayAccess
 * Called by: GameLoop, V_BufLock, V_BufUnlock
 *
 * Elecbyte file: src/lib/vbuf.c
 */
uint32_t V_BufGetSurface(int *buffer,int index)

{
  int sprite;
  uint32_t u2;
  
  sprite = SpriteArrayAccess(buffer,index);
  if ((sprite == 0) || (*(int *)(sprite + 0x1c) != 1)) {
    u2 = 0;
  }
  else {
    u2 = *(uint32_t *)(sprite + 0x24);
  }
  return u2;
}

/* V_BufLock @ 0x0807d060, 59 bytes
 *
 * Acquires the page's bitmap (its vtable acquire method) before direct pixel
 * access.
 *
 * Parameters:
 *   buffer       int *
 *   index        int
 *
 * Calls: V_BufGetSurface
 * Called by: V_BufLockCurrent
 *
 * Elecbyte file: src/lib/vbuf.c
 */
uint32_t V_BufLock(int *buffer,int index)

{
  generic_fn *pc1;
  int i2;
  uint32_t u3;
  
  i2 = V_BufGetSurface(buffer,index);
  if (i2 == 0) {
    u3 = 0;
  }
  else {
    pc1 = *(generic_fn **)(*(int *)(i2 + 0x1c) + 0x10);
    if (pc1 != (generic_fn *)0x0) {
      (*pc1)(i2);
    }
    u3 = 1;
  }
  return u3;
}

/* V_BufUnlock @ 0x0807d0a0, 50 bytes
 *
 * Releases the page's bitmap after direct pixel access.
 *
 * Parameters:
 *   buffer       int *
 *   index        int
 *
 * Calls: V_BufGetSurface
 * Called by: V_BufUnlockCurrent
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void V_BufUnlock(int *buffer,int index)

{
  generic_fn *pc1;
  int i2;
  
  i2 = V_BufGetSurface(buffer,index);
  if ((i2 != 0) && (pc1 = *(generic_fn **)(*(int *)(i2 + 0x1c) + 0x14), pc1 != (generic_fn *)0x0)) {
    (*pc1)(i2);
  }
  return;
}

/* V_BufLockCurrent @ 0x0807d0e0, 25 bytes
 *
 * V_BufLock on the current drawing buffer. Not called in this build.
 *
 * Calls: V_BufLock
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void V_BufLockCurrent(void)

{
  V_BufLock(V_Current,V_CurrentIdx);
  return;
}

/* V_BufUnlockCurrent @ 0x0807d100, 26 bytes
 *
 * V_BufUnlock on the current drawing buffer. Not called in this build.
 *
 * Calls: V_BufUnlock
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void V_BufUnlockCurrent(void)

{
  V_BufUnlock(V_Current,V_CurrentIdx);
  return;
}

/* V_BufToScreen @ 0x0807d120, 211 bytes
 *
 * Copies a full drawing buffer to the screen (blit), then flips pages
 * (G_PageFlip). When a 16-bit buffer goes to a 32-bit screen with RGB/BGR
 * swapping enabled, it uses blit_32to16_RGBtoBGR.
 *
 * Parameters:
 *   buffer       int *
 *   index        int
 *
 * Calls: SpriteArrayAccess, blit_32to16_RGBtoBGR, G_PageFlip
 * C library: blit
 * Called by: V_BufToScreenStretch
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void V_BufToScreen(int *buffer,int index)

{
  int *pi1;
  generic_fn *pc2;
  uint32_t *sprite;
  
  sprite = (uint32_t *)SpriteArrayAccess(buffer,index);
  if ((sprite != (uint32_t *)0x0) && (sprite[7] == 1)) {
    pi1 = (int *)sprite[9];
    pc2 = *(generic_fn **)(*(int *)(screen + 0x1c) + 0x10);
    if (pc2 != (generic_fn *)0x0) {
      (*pc2)(screen);
    }
    if (((sprite[4] == 0x10) && (*(int *)G_Screenptr[7] == 0x20)) && (scrRGB16toBGR32 != 0)) {
      blit_32to16_RGBtoBGR(pi1,(int)G_Screenptr,0,0,0,0,*sprite,sprite[1]);
    }
    else {
      blit(pi1,G_Screenptr,0,0,0,0,*sprite,sprite[1]);
    }
    pc2 = *(generic_fn **)(*(int *)(screen + 0x1c) + 0x14);
    if (pc2 != (generic_fn *)0x0) {
      (*pc2)(screen);
    }
    if ((G_BlitMode == 1) && (G_BlitModeAuto != 0)) {
      G_PageFlip();
    }
  }
  return;
}

/* V_BufToScreenXY @ 0x0807d200, 325 bytes
 *
 * Copies a drawing buffer to the screen at (x, y), clearing the screen first
 * when the buffer does not cover it, then flips pages.
 *
 * Parameters:
 *   buffer       int *
 *   index        int
 *   x            int
 *   y            int
 *
 * Calls: SpriteArrayAccess, blit_32to16_RGBtoBGR, G_PageFlip
 * C library: set_clip, blit
 * Called by: DrawToScreen
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void V_BufToScreenXY(int *buffer,int index,int x,int y)

{
  int *pi1;
  generic_fn *pc2;
  uint32_t *sprite;
  uint32_t u4;
  uint32_t u5;
  
  sprite = (uint32_t *)SpriteArrayAccess(buffer,index);
  if ((sprite != (uint32_t *)0x0) && (sprite[7] == 1)) {
    pi1 = (int *)sprite[9];
    if ((x < 0) ||
       (((y < 0 || (S_Width < (int)(x + *sprite))) ||
        (S_Height < (int)(y + sprite[1]))))) {
      u5 = S_Height - 1;
      u4 = S_Width - 1;
    }
    else {
      u5 = 0;
      u4 = 0;
    }
    set_clip((uint32_t *)G_Screenptr,0,0,u4,u5);
    pc2 = *(generic_fn **)(*(int *)(screen + 0x1c) + 0x10);
    if (pc2 != (generic_fn *)0x0) {
      (*pc2)(screen);
    }
    if (((sprite[4] == 0x10) && (*(int *)G_Screenptr[7] == 0x20)) && (scrRGB16toBGR32 != 0)) {
      blit_32to16_RGBtoBGR(pi1,(int)G_Screenptr,0,0,x,y,*sprite,sprite[1]);
    }
    else {
      blit(pi1,G_Screenptr,0,0,x,y,*sprite,sprite[1]);
    }
    pc2 = *(generic_fn **)(*(int *)(screen + 0x1c) + 0x14);
    if (pc2 != (generic_fn *)0x0) {
      (*pc2)(screen);
    }
    if ((G_BlitMode == 1) && (G_BlitModeAuto != 0)) {
      G_PageFlip();
    }
  }
  return;
}

/* V_BufToScreenStretch @ 0x0807d350, 283 bytes
 *
 * Copies a drawing buffer stretched to the screen size (stretch_blit, or the
 * RGB/BGR-swapping variant); uses V_BufToScreen when the sizes match.
 *
 * Parameters:
 *   buffer       int *
 *   index        int
 *
 * Calls: SpriteArrayAccess, V_BufToScreen, stretch_blit_32to16_RGBtoBGR,
 *        G_PageFlip
 * C library: stretch_blit
 * Called by: DrawToScreen
 *
 * Elecbyte file: src/lib/vbuf.c
 * Note: 4 word-indexed accesses to Allegro screen cast to int *
 */
void V_BufToScreenStretch(int *buffer,int index)

{
  int i1;
  int *sprite;
  int *stale_ECX;
  int *stale_ECX_00;
  int *pi3;
  int *stale_EDX;
  int *pi4;
  int i5;
  int *pi6;
  
  sprite = (int *)SpriteArrayAccess(buffer,index);
  if ((sprite != (int *)0x0) && (sprite[7] == 1)) {
    i1 = sprite[9];
    if ((*sprite == S_Width) && (sprite[1] == S_Height)) {
      V_BufToScreen(buffer,index);
      return;
    }
    pi3 = stale_ECX;
    pi4 = screen;
    if (*(generic_fn **)(((int *)screen)[7] + 0x10) != (generic_fn *)0x0) {
      (**(generic_fn **)(((int *)screen)[7] + 0x10))(screen);
      pi3 = stale_ECX_00;
      pi4 = stale_EDX;
    }
    i5 = S_Height;
    if (((sprite[4] == 0x10) && (pi4 = G_Screenptr, *(int *)G_Screenptr[7] == 0x20)) &&
       (scrRGB16toBGR32 != 0)) {
      pi6 = pi3;
      stretch_blit_32to16_RGBtoBGR
                (i1,(int)G_Screenptr,0,0,*sprite,sprite[1],0,0,S_Width,S_Height);
      pi4 = pi3;
    }
    else {
      pi6 = pi4;
      stretch_blit(i1,(int)G_Screenptr,0,0,*sprite,sprite[1],0,0,S_Width,S_Height);
    }
    if (*(generic_fn **)(((int *)screen)[7] + 0x14) != (generic_fn *)0x0) {
      (**(generic_fn **)(((int *)screen)[7] + 0x14))(screen,i5,pi4,pi6);
    }
    if ((G_BlitMode == 1) && (G_BlitModeAuto != 0)) {
      G_PageFlip();
    }
  }
  return;
}

/* blit_32to16_RGBtoBGR @ 0x0807d470, 544 bytes
 *
 * Copies a rectangle from a 16-bit bitmap to a 32-bit bitmap, converting
 * each pixel from 5-6-5 RGB to 8-8-8 with red and blue swapped.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *   arg6         int
 *   arg7         int
 *   arg8         int
 *
 * Called by: V_BufToScreen, V_BufToScreenXY
 *
 * Elecbyte file: src/lib/vbuf.c
 * Note: 4 exact-text site patches (see SITE_PATCHES in
 *       tools/build_source_tree.py)
 */
void blit_32to16_RGBtoBGR
               (int *arg1,int arg2,int arg3,int arg4,int arg5,int arg6,int arg7
               ,int arg8)

{
  uint16_t u1;
  int i2;
  int i3;
  int i4;
  int i5;
  uint32_t *pu6;
  uint16_t *pu7;
  
  i5 = *arg1;
  if ((((arg3 < i5) && (i4 = arg1[1], arg4 < i4)) &&
      (i2 = *(int *)(arg2 + 0x10), arg5 < i2)) &&
     (i3 = *(int *)(arg2 + 0x18), arg6 < i3)) {
    if (arg3 < 0) {
      arg7 = arg7 + arg3;
      arg5 = arg5 - arg3;
      arg3 = 0;
    }
    if (arg4 < 0) {
      arg8 = arg8 + arg4;
      arg6 = arg6 - arg4;
      arg4 = 0;
    }
    if (i5 < arg3 + arg7) {
      arg7 = i5 - arg3;
    }
    if (i4 < arg4 + arg8) {
      arg8 = i4 - arg4;
    }
    i5 = *(int *)(arg2 + 0xc);
    if (arg5 < i5) {
      arg7 = arg7 + (arg5 - i5);
      arg3 = arg3 - (arg5 - i5);
      arg5 = i5;
    }
    i5 = *(int *)(arg2 + 0x14);
    if (arg6 < i5) {
      arg8 = arg8 + (arg6 - i5);
      arg6 = i5;
    }
    if (i2 < arg5 + arg7) {
      arg7 = i2 - arg5;
    }
    if (i3 < arg6 + arg8) {
      arg8 = i3 - arg6;
    }
    if ((0 < arg7) && (0 < arg8)) {
      i5 = 0;
      if (0 < arg8) {
        do {
          i4 = ALG_bmp_read_line(arg1, arg4 + i5);
          pu7 = (uint16_t *)(i4 + arg3 * 2);
          i4 = ALG_bmp_write_line((void *)arg2, arg6 + i5);
          pu6 = (uint32_t *)(i4 + arg5 * 4);
          i4 = arg7;
          if (0 < arg7) {
            do {
              u1 = *pu7;
              pu7 = pu7 + 1;
              *pu6 = (u1 & 0x1f) << 3 | (u1 & 0x7e0) << 5 | (uint32_t)(u1 >> 0xb) << 0x13;
              pu6 = pu6 + 1;
              i4 = i4 + -1;
            } while (i4 != 0);
          }
          i5 = i5 + 1;
        } while (i5 < arg8);
      }
      ALG_bmp_unwrite_line(arg1);
      ALG_bmp_unwrite_line((void *)arg2);
    }
  }
  return;
}

/* stretch_blit_32to16_RGBtoBGR @ 0x0807d690, 978 bytes
 *
 * blit_32to16_RGBtoBGR with stretching (nearest-neighbour sampling).
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *   arg6         int
 *   arg7         int
 *   arg8         int
 *   arg9         int
 *   arg10        int
 *
 * Called by: V_BufToScreenStretch
 *
 * Elecbyte file: src/lib/vbuf.c
 * Note: 2 exact-text site patches (see SITE_PATCHES in
 *       tools/build_source_tree.py)
 */
void stretch_blit_32to16_RGBtoBGR
               (int arg1,int arg2,int arg3,int arg4,int arg5,int arg6,int arg7,
               int arg8,int arg9,int arg10)

{
  uint16_t u1;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  int i7;
  uint32_t *pu8;
  int i9;
  uint32_t *pu10;
  int i11;
  int i12;
  int i13;
  uint16_t *pu14;
  int stk_94;
  int stk_90;
  int stk_60;
  int stk_54;
  int stk_50;
  int stk_4c;
  int stk_40;
  
  if (arg5 < 1) {
    return;
  }
  if (arg6 < 1) {
    return;
  }
  if (arg9 < 1) {
    return;
  }
  if (0 < arg10) {
    if (*(int *)(arg2 + 8) == 0) {
      stk_50 = arg8;
      stk_94 = arg9 + arg7;
      stk_54 = arg8 + arg10;
      i9 = arg7;
    }
    else {
      stk_50 = *(int *)(arg2 + 0x14);
      if (stk_50 < arg8) {
        stk_50 = arg8;
      }
      stk_54 = *(int *)(arg2 + 0x18);
      if (arg8 + arg10 < *(int *)(arg2 + 0x18)) {
        stk_54 = arg8 + arg10;
      }
      if (stk_54 <= stk_50) {
        return;
      }
      i9 = *(int *)(arg2 + 0xc);
      if (*(int *)(arg2 + 0xc) < arg7) {
        i9 = arg7;
      }
      stk_94 = *(int *)(arg2 + 0x10);
      if (arg9 + arg7 < *(int *)(arg2 + 0x10)) {
        stk_94 = arg9 + arg7;
      }
      if (stk_94 <= i9) {
        return;
      }
    }
    arg6 = arg6 + -1;
    i4 = arg10 + -1;
    i13 = arg5 + -1;
    i5 = arg9 + -1;
    if (i5 == 0) {
      stk_90 = 0;
    }
    else {
      stk_90 = i13 / i5;
      i13 = i13 % i5;
    }
    stk_4c = 0;
    if (i4 != 0) {
      stk_4c = arg6 / i4;
      arg6 = arg6 % i4;
    }
    i13 = i13 * 2;
    i11 = i13 - i5;
    stk_40 = arg3;
    i5 = i11 - i5;
    if (arg7 < i9) {
      i6 = i9 - arg7;
      do {
        i2 = i13;
        if (-1 < i11) {
          stk_40 = stk_40 + 1;
          i2 = i5;
        }
        i11 = i11 + i2;
        stk_40 = stk_40 + stk_90;
        i6 = i6 + -1;
        arg7 = i9;
      } while (i6 != 0);
    }
    i6 = arg6 * 2;
    i2 = stk_40 * 2;
    i12 = i6 - i4;
    i4 = i12 - i4;
    stk_40 = arg4;
    if (arg8 < stk_50) {
      i7 = stk_50 - arg8;
      do {
        i3 = i6;
        if (-1 < i12) {
          stk_40 = stk_40 + 1;
          i3 = i4;
        }
        i12 = i12 + i3;
        stk_40 = stk_40 + stk_4c;
        i7 = i7 + -1;
        arg8 = stk_50;
      } while (i7 != 0);
    }
    for (; arg8 < stk_54; arg8 = arg8 + 1) {
      pu14 = (uint16_t *)(i2 + *(int *)(arg1 + 0x40 + stk_40 * 4));
      i7 = ALG_bmp_write_line((void *)arg2, arg8);
      pu10 = (uint32_t *)(arg7 * 4 + i7);
      pu8 = pu10 + (stk_94 - i9);
      stk_60 = i11;
      for (; pu10 < pu8; pu10 = pu10 + 1) {
        u1 = *pu14;
        *pu10 = (u1 & 0x1f) << 3 | (u1 & 0x7e0) << 5 | (uint32_t)(u1 >> 0xb) << 0x13;
        i7 = i13;
        if (-1 < stk_60) {
          pu14 = pu14 + 1;
          i7 = i5;
        }
        stk_60 = stk_60 + i7;
        pu14 = pu14 + stk_90;
      }
      i7 = i6;
      if (-1 < i12) {
        stk_40 = stk_40 + 1;
        i7 = i4;
      }
      i12 = i12 + i7;
      stk_40 = stk_40 + stk_4c;
    }
    ALG_bmp_unwrite_line((void *)arg2);
    return;
  }
  return;
}

/* W_Define @ 0x0807da70, 200 bytes
 *
 * Sets the clipping window of the current drawing buffer to (x1, y1)-(x2,
 * y2), ordering the corners and clamping them to the buffer. All W_ drawing
 * functions clip to this window.
 *
 * Parameters:
 *   x1           uint32_t
 *   y1           uint32_t
 *   x2           uint32_t
 *   y2           uint32_t
 *
 * Calls: SpriteArrayAccess
 * C library: set_clip
 * Called by: BGDraw, EB_GUIDrawWindow, ExplodDraw, GameLifeBarDraw,
 *            GameLoop, GamePowerBarDraw, ModeSelect, SiSceneDraw,
 *            V_FontDrawLine, V_SetBuf, W_DefineV, _mangled_main
 *
 * Elecbyte file: src/lib/vbuf.c
 */
int W_Define(uint32_t x1,uint32_t y1,uint32_t x2,uint32_t y2)

{
  int sprite;
  uint32_t u2;
  
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  W_x2 = x2;
  if ((int)x2 < (int)x1) {
    W_x2 = x1;
    x1 = x2;
  }
  u2 = y1;
  if ((int)y2 < (int)y1) {
    u2 = y2;
    y2 = y1;
  }
  W_x1 = x1 & 0xffffffffU - ((int)x1 >> 0x1f);
  W_y1 = u2 & 0xffffffffU - ((int)u2 >> 0x1f);
  if (V_Width <= W_x2) {
    W_x2 = V_Width - 1;
  }
  if (V_Height <= (int)y2) {
    y2 = V_Height - 1;
  }
  W_Height = (y2 - W_y1) + 1;
  W_Width = (W_x2 - W_x1) + 1;
  W_Skip = V_Width - W_Width;
  W_y2 = y2;
  if (*(int *)(sprite + 0x1c) == 1) {
    sprite = set_clip(*(uint32_t **)(sprite + 0x24),W_x1,W_y1,W_x2,y2);
  }
  return sprite;
}

/* W_DefineV @ 0x0807db40, 31 bytes
 *
 * W_Define with the four coordinates passed in an array.
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * Calls: W_Define
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_DefineV(uint32_t *arg1)

{
  W_Define(*arg1,arg1[1],arg1[2],arg1[3]);
  return;
}

/* W_GetV @ 0x0807db60, 36 bytes
 *
 * Stores the current clipping window into a 4-int array. Not called in this
 * build.
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_GetV(uint32_t *arg1)

{
  *arg1 = W_x1;
  arg1[1] = W_y1;
  arg1[2] = W_x2;
  arg1[3] = W_y2;
  return;
}

/* W_Cls @ 0x0807db90, 175 bytes
 *
 * Fills the whole current drawing buffer with colour `col` (converted
 * through the master palette for 16-bit buffers).
 *
 * Parameters:
 *   col          uint32_t
 *
 * Calls: SpriteArrayAccess, MasterPalConvertCol16, ColDepthToBytesPerPixel
 * C library: memset
 * Called by: BGArrayDraw, BGArrayDrawLayer, CharacterSelectScreen,
 *            EB_GUIClearWindow, EB_GUINewWindow, GameLoop, GameNextRound,
 *            GameReloadStage, GameRoundUpdate, GameVarInit, ModeSelect,
 *            PlayCutscene, SiSceneDraw, VersusScreen, _mangled_main
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_Cls(uint32_t col)

{
  int i1;
  int *sprite;
  uint32_t u3;
  int i4;
  
  sprite = (int *)SpriteArrayAccess(V_Current,V_CurrentIdx);
  u3 = MasterPalConvertCol16(col);
  if (sprite[7] == 1) {
    (**(generic_fn **)(*(int *)(sprite[9] + 0x1c) + 0x94))(sprite[9],u3,sprite,sprite);
  }
  else {
    i4 = ColDepthToBytesPerPixel(sprite[4]);
    if (i4 == 1) {
      memset((void *)sprite[9],u3 & 0xff,sprite[8]);
    }
    else if (i4 == 2) {
      i4 = *sprite * sprite[1];
      if (i4 != 0) {
        i1 = sprite[9];
        do {
          *(short *)(i1 + i4 * 2) = (short)u3;
          i4 = i4 + -1;
        } while (i4 != 0);
      }
    }
    else if ((i4 == 4) && (i4 = *sprite * sprite[1], i4 != 0)) {
      i1 = sprite[9];
      do {
        *(uint32_t *)(i1 + i4 * 4) = u3;
        i4 = i4 + -1;
      } while (i4 != 0);
    }
  }
  return;
}

/* W_PutPixel @ 0x0807dc40, 233 bytes
 *
 * Sets one pixel of the current drawing buffer, if it is inside the window.
 *
 * Parameters:
 *   x            int
 *   y            int
 *   col          uint32_t
 *
 * Calls: SpriteArrayAccess, MasterPalConvertCol16, ColDepthToBytesPerPixel
 * Called by: ModeSelect
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_PutPixel(int x,int y,uint32_t col)

{
  int sprite;
  uint32_t u2;
  int i3;
  int i4;
  
  i4 = 0;
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  u2 = MasterPalConvertCol16(col);
  if (*(int *)(sprite + 0x1c) == 1) {
    (**(generic_fn **)(*(int *)(*(int *)(sprite + 0x24) + 0x1c) + 0x24))
              (*(int *)(sprite + 0x24),x,y,u2);
  }
  else {
    i4 = *(int *)(sprite + 0x24);
  }
  if ((((i4 != 0) && (W_x1 <= x)) && (x <= W_x2)) &&
     ((W_y1 <= y && (y <= W_y2)))) {
    i3 = ColDepthToBytesPerPixel(*(int *)(sprite + 0x10));
    if (i3 == 2) {
      *(short *)(i4 + *(int *)(*(int *)(sprite + 0x2c) + y * 4) + x * 2) =
           (short)u2;
    }
    else if (i3 < 3) {
      if (i3 == 1) {
        *(char *)(x + i4 + *(int *)(*(int *)(sprite + 0x2c) + y * 4)) = (char)u2;
      }
    }
    else if (i3 == 4) {
      *(uint32_t *)(i4 + *(int *)(*(int *)(sprite + 0x2c) + y * 4) + x * 4) = u2;
    }
  }
  return;
}

/* W_PutPixelTransAdd16 @ 0x0807dd30, 240 bytes
 *
 * Adds colour `col` to one pixel of a 16-bit drawing buffer (per channel,
 * saturating). Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         uint32_t
 *
 * Calls: SpriteArrayAccess, MasterPalConvertCol16
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_PutPixelTransAdd16(int arg1,int arg2,uint32_t arg3)

{
  uint32_t *pu1;
  uint32_t u2;
  uint32_t u3;
  int sprite;
  uint32_t u5;
  uint16_t u6;
  uint16_t u7;
  int i8;
  uint32_t u9;
  
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  u5 = MasterPalConvertCol16(arg3);
  if (*(int *)(sprite + 0x1c) == 1) {
    i8 = *(int *)(*(int *)(sprite + 0x24) + 0x28);
  }
  else {
    i8 = *(int *)(sprite + 0x24);
  }
  if ((((i8 != 0) && (W_x1 <= arg1)) && (arg1 <= W_x2)) &&
     ((W_y1 <= arg2 && (arg2 <= W_y2)))) {
    pu1 = (uint32_t *)(i8 + *(int *)(*(int *)(sprite + 0x2c) + arg2 * 4) + arg1 * 2);
    u3 = *pu1;
    u9 = (u3 & 0xf800) + (u5 & 0xf800);
    if (0xf800 < u9) {
      u9 = 0xf800;
    }
    u2 = (u3 & 0x7e0) + (u5 & 0x7e0);
    u6 = (uint16_t)u2;
    if (0x7e0 < u2) {
      u6 = 0x7e0;
    }
    u5 = (u3 & 0x1f) + (u5 & 0x1f);
    u7 = (uint16_t)u5;
    if (0x1f < u5) {
      u7 = 0x1f;
    }
    *(uint16_t *)pu1 = (uint16_t)u9 | u6 | u7;
  }
  return;
}

/* W_PutPixelXor16 @ 0x0807de20, 106 bytes
 *
 * Inverts one pixel of a 16-bit drawing buffer (XOR 0xffff), if it is inside
 * the window. Used to draw collision box outlines in debug mode.
 *
 * Parameters:
 *   x            int
 *   y            int
 *
 * Calls: SpriteArrayAccess
 * Called by: PlayerDrawClsn
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_PutPixelXor16(int x,int y)

{
  uint16_t *pu1;
  int sprite;
  int i3;
  
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  if (*(int *)(sprite + 0x1c) == 1) {
    i3 = *(int *)(*(int *)(sprite + 0x24) + 0x28);
  }
  else {
    i3 = *(int *)(sprite + 0x24);
  }
  if ((((i3 != 0) && (W_x1 <= x)) && (x <= W_x2)) &&
     ((W_y1 <= y && (y <= W_y2)))) {
    pu1 = (uint16_t *)(i3 + *(int *)(*(int *)(sprite + 0x2c) + y * 4) + x * 2);
    *pu1 = *pu1 ^ 0xffff;
  }
  return;
}

/* W_Line @ 0x0807de90, 386 bytes
 *
 * Draws a line in colour `col`. Horizontal and vertical lines use
 * W_HLine/W_VLine; other lines are clipped against the window
 * (DoDrawClippedLine).
 *
 * Parameters:
 *   x1           float
 *   y1           float
 *   x2           float
 *   y2           float
 *   col          uint32_t
 *
 * Calls: SpriteArrayAccess, W_HLine, W_VLine, MasterPalConvertCol16,
 *        DoDrawClippedLine
 * Called by: ModeSelect, OptionsScreen, W_Box
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_Line(float x1,float y1,float x2,float y2,uint32_t col)

{
  uint32_t u1;
  int sprite;
  uint32_t u3;
  int i4;
  
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  u1 = (uint32_t)X87_FIST32(y1);
  if (u1 == (int)X87_FIST32(y2)) {
    W_HLine((int)X87_FIST32(x1),(int)X87_FIST32(x2),u1,col);
  }
  else if ((int)X87_FIST32(x1) == (int)X87_FIST32(x2)) {
    W_VLine((int)X87_FIST32(x1),u1,(int)X87_FIST32(y2),col);
  }
  else {
    u3 = MasterPalConvertCol16(col);
    if (*(int *)(sprite + 0x1c) == 1) {
      i4 = *(int *)(*(int *)(sprite + 0x24) + 0x28);
    }
    else {
      i4 = *(int *)(sprite + 0x24);
    }
    if (i4 != 0) {
      DoDrawClippedLine(i4,*(int *)(sprite + 0x2c),x1,y1,x2,y2,(short)u3);
    }
  }
  return;
}

/* DoDrawLine @ 0x0807e020, 1598 bytes
 *
 * Draws an already clipped line with Bresenham's algorithm into the current
 * buffer (8 or 16 bits per pixel).
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         float
 *   arg4         float
 *   arg5         float
 *   arg6         float
 *   arg7         uint16_t
 *
 * Called by: DoDrawClippedLine
 *
 * Elecbyte file: src/lib/vbuf.c
 * Note: 16 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: 5 temporaries are float80, as the original kept them in x87 registers.
 */
void DoDrawLine(int arg1,int arg2,float arg3,float arg4,float arg5,float arg6,
               uint16_t arg7)

{
  float80 f1;
  float80 f2;
  float80 f3;
  float80 f4;
  float80 f5;
  int i2;
  int i7;
  int i8;
  int i9;
  
  f1 = arg3;
  f5 = arg4;
  if (arg5 < arg3) {
    f1 = arg5;
    f5 = arg6;
    arg6 = arg4;
    arg5 = arg3;
  }
  i8 = (int)X87_FIST32(f1);
  i2 = (int)X87_FIST32(arg5);
  i7 = (int)X87_FIST32(f5);
  i9 = (int)X87_FIST32(arg6);
  f2 = arg5 - f1;
  f4 = arg6 - f5;
  if (i8 == i2) {
    if (i7 <= i9) {
      do {
        i2 = i7 * 4;
        i7 = i7 + 1;
        *(uint16_t *)(i8 * 2 + arg1 + *(int *)(arg2 + i2)) = arg7;
      } while (i7 <= i9);
    }
  }
  else if (i7 == i9) {
    if (i8 <= i2) {
      i7 = *(int *)(arg2 + i7 * 4);
      do {
        *(uint16_t *)(arg1 + i7 + i8 * 2) = arg7;
        i8 = i8 + 1;
      } while (i8 <= i2);
    }
  }
  else {
    *(uint16_t *)(arg1 + *(int *)(arg2 + i7 * 4) + i8 * 2) = arg7;
    if (0.0 < f2) {
      if ((f4 <= 0.0) || (f2 < f4)) {
        if (0.0 < f2) {
          if ((f4 <= 0.0) || (f4 <= f2)) {
            if (0.0 < f2) {
              if ((0.0 <= f4) || (f2 < -f4)) {
                if (((0.0 < f2) && (f4 < 0.0)) && (f2 < -f4)) {
                  f4 = f4 * -1.0;
                  f3 = f2 + f2;
                  f1 = (f1 - (float80)i8) * f4 + f2 * (f5 - (float80)i7);
                  f1 = f1 + f1 + (f3 - f4);
                  i2 = (int)X87_FIST32(f4);
                  if (-1 < i2 + -1) {
                    do {
                      i9 = (int)X87_FIST32(f1);
                      i7 = i7 + -1;
                      if (i9 < 0) {
                        f1 = (float80)i9 + f3;
                      }
                      else {
                        i8 = i8 + 1;
                        f1 = ((f3 - f4) - f4) + (float80)i9;
                      }
                      i2 = i2 + -1;
                      *(uint16_t *)(arg1 + *(int *)(arg2 + i7 * 4) + i8 * 2) = arg7
                      ;
                    } while (i2 != 0);
                  }
                }
              }
              else {
                f4 = f4 * -1.0;
                f3 = f4 + f4;
                f1 = -f4 * (f1 - (float80)i8) - (f5 - (float80)i7) * f2;
                f1 = f1 + f1 + (f3 - f2);
                i2 = 0;
                if ((int)X87_FIST32(f2) - 1U < 0x80000000) {
                  do {
                    i9 = (int)X87_FIST32(f1);
                    i8 = i8 + 1;
                    if (i9 < 0) {
                      f1 = (float80)i9 + f3;
                    }
                    else {
                      i7 = i7 + -1;
                      f1 = ((f3 - f2) - f2) + (float80)i9;
                    }
                    i2 = i2 + 1;
                    *(uint16_t *)(arg1 + *(int *)(arg2 + i7 * 4) + i8 * 2) = arg7;
                  } while (i2 <= (int)((int)X87_FIST32(f2) - 1U));
                }
              }
            }
          }
          else {
            f3 = f2 + f2;
            f1 = (f1 - (float80)i8) * f4 - f2 * (f5 - (float80)i7);
            f1 = f1 + f1 + (f3 - f4);
            i2 = 0;
            if ((int)X87_FIST32(f4) - 1U < 0x80000000) {
              do {
                i9 = (int)X87_FIST32(f1);
                i7 = i7 + 1;
                if (i9 < 0) {
                  f1 = (float80)i9 + f3;
                }
                else {
                  i8 = i8 + 1;
                  f1 = ((f3 - f4) - f4) + (float80)i9;
                }
                i2 = i2 + 1;
                *(uint16_t *)(arg1 + *(int *)(arg2 + i7 * 4) + i8 * 2) = arg7;
              } while (i2 <= (int)((int)X87_FIST32(f4) - 1U));
            }
          }
        }
      }
      else {
        f3 = f4 + f4;
        f1 = -f4 * (f1 - (float80)i8) + (f5 - (float80)i7) * f2;
        f1 = f1 + f1 + (f3 - f2);
        i2 = 0;
        if ((int)X87_FIST32(f2) - 1U < 0x80000000) {
          do {
            i9 = (int)X87_FIST32(f1);
            i8 = i8 + 1;
            if (i9 < 0) {
              f1 = (float80)i9 + f3;
            }
            else {
              i7 = i7 + 1;
              f1 = ((f3 - f2) - f2) + (float80)i9;
            }
            i2 = i2 + 1;
            *(uint16_t *)(arg1 + *(int *)(arg2 + i7 * 4) + i8 * 2) = arg7;
          } while (i2 <= (int)((int)X87_FIST32(f2) - 1U));
        }
      }
    }
  }
  return;
}

/* CyrusT @ 0x0807e660, 59 bytes
 *
 * Cyrus-Beck line clipping helper: returns the parameter t where the line
 * (p0 + t * d) crosses the clipping edge with the given normal and point.
 *
 * Parameters:
 *   arg1         float
 *   arg2         float
 *   arg3         float
 *   arg4         float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         float
 *
 * Called by: DoDrawClippedLine
 *
 * Elecbyte file: src/lib/vbuf.c
 */
float80
CyrusT(float arg1,float arg2,float arg3,float arg4,float arg5,float arg6,
      float arg7,float arg8)

{
  return (((float80)arg1 - (float80)arg7) * (float80)arg5 +
         ((float80)arg2 - (float80)arg8) * (float80)arg6) /
         -((float80)arg6 * (float80)arg4 + (float80)arg5 * (float80)arg3);
}

/* TrivialTestPoint @ 0x0807e6a0, 76 bytes
 *
 * Returns the Cohen-Sutherland outcode of a point against the window: 1
 * left, 2 right, 4 above, 8 below.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Called by: DoDrawClippedLine
 *
 * Elecbyte file: src/lib/vbuf.c
 */
uint32_t TrivialTestPoint(int arg1,int arg2)

{
  uint32_t u1;
  
  u1 = 0;
  if (arg1 < W_x1) {
    u1 = 1;
  }
  else if (W_x2 < arg1) {
    u1 = 2;
  }
  if (arg2 < W_y1) {
    return u1 | 4;
  }
  if (W_y2 < arg2) {
    u1 = u1 | 8;
  }
  return u1;
}

/* DoDrawClippedLine @ 0x0807e6f0, 1363 bytes
 *
 * Clips a line to the window (outcodes for trivial accept/reject, Cyrus-Beck
 * intersections otherwise) and draws the visible part with DoDrawLine.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         float
 *   arg4         float
 *   arg5         float
 *   arg6         float
 *   arg7         uint16_t
 *
 * Calls: TrivialTestPoint, CyrusT, DoDrawLine
 * Called by: W_Line
 *
 * Elecbyte file: src/lib/vbuf.c
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void DoDrawClippedLine(int arg1,int arg2,float arg3,float arg4,float arg5,
                      float arg6,uint16_t arg7)

{
  float80 f1;
  float80 f2;
  float80 f3;
  uint32_t u4;
  uint32_t u5;
  int i6;
  int i7;
  int i8;
  int i9;
  float80 l10;
  float80 l11;
  float80 l12;
  float80 l13;
  float80 l14;
  
  f2 = arg5 - arg3;
  f3 = arg6 - arg4;
  u4 = TrivialTestPoint((int)X87_FIST32(arg3),(int)X87_FIST32(arg4));
  u5 = TrivialTestPoint((int)X87_FIST32(arg5),(int)X87_FIST32(arg6));
  if ((u5 & u4) == 0) {
    l10 = CyrusT(arg3,arg4,f2,f3,-1.0,0.0,(float)W_x1,(float)W_y2);
    f1 = (float)l10;
    if ((l10 < (float80)0.0) || (1.0 < f1)) {
      i9 = 0;
    }
    else {
      i9 = (uint32_t)(f2 * -1.0 < 0.0) * 2 + -1;
    }
    l10 = CyrusT(arg3,arg4,f2,f3,1.0,0.0,(float)W_x2,(float)W_y1);
    if ((l10 < (float80)0.0) || ((float80)1.0 < l10)) {
      i8 = 0;
    }
    else {
      i8 = (uint32_t)(f2 < 0.0) * 2 + -1;
    }
    l11 = CyrusT(arg3,arg4,f2,f3,0.0,-1.0,(float)W_x1,(float)W_y1);
    if ((l11 < (float80)0.0) || ((float80)1 < l11)) {
      i7 = 0;
    }
    else {
      i7 = (uint32_t)(f3 * -1.0 < 0.0) * 2 + -1;
    }
    l12 = CyrusT(arg3,arg4,f2,f3,0.0,1.0,(float)W_x2,(float)W_y2);
    if ((l12 < (float80)0.0) || ((float80)1.0 < l12)) {
      i6 = 0;
    }
    else {
      i6 = (uint32_t)(f3 < 0.0) * 2 + -1;
    }
    l14 = (float80)1;
    if ((i9 == -1) && ((float80)f1 < l14)) {
      l14 = (float80)f1;
    }
    if ((i8 == -1) && (l13 = (float80)(float)l10, l13 < l14)) {
      l14 = l13;
    }
    if ((i7 == -1) && (l11 < l14)) {
      l14 = l11;
    }
    if ((i6 == -1) && (l12 < l14)) {
      l14 = l12;
    }
    l13 = (float80)0;
    if ((i9 == 1) && (l13 < (float80)f1)) {
      l13 = (float80)f1;
    }
    if ((i8 == 1) && (l10 = (float80)(float)l10, l13 < l10)) {
      l13 = l10;
    }
    l10 = l13;
    if ((i7 == 1) && (l10 = l11, l11 <= l13)) {
      l10 = l13;
    }
    if ((i6 == 1) && (l10 < l12)) {
      l10 = l12;
    }
    if (l10 <= l14) {
      l12 = l10 * (float80)f2 + (float80)arg3;
      l11 = l14 * (float80)f2 + (float80)arg3;
      l14 = l14 * (float80)f3 + (float80)arg4;
      l10 = (float80)f3 * l10 + (float80)arg4;
      if (l12 < (float80)W_x1) {
        l12 = (float80)W_x1;
      }
      if ((float80)W_x2 < l12) {
        l12 = (float80)W_x2;
      }
      if (l11 < (float80)W_x1) {
        l11 = (float80)W_x1;
      }
      if ((float80)W_x2 < l11) {
        l11 = (float80)W_x2;
      }
      if (l10 < (float80)W_y1) {
        l10 = (float80)W_y1;
      }
      if ((float80)W_y2 < l10) {
        l10 = (float80)W_y2;
      }
      if (l14 < (float80)W_y1) {
        l14 = (float80)W_y1;
      }
      if ((float80)W_y2 < l14) {
        l14 = (float80)W_y2;
      }
      DoDrawLine(arg1,arg2,(float)l12,(float)l10,(float)l11,(float)l14,arg7);
    }
  }
  return;
}

/* W_HLine @ 0x0807ec50, 177 bytes
 *
 * Draws a horizontal line in colour `col` into the current drawing buffer,
 * clipped to the window.
 *
 * Parameters:
 *   x1           uint32_t
 *   x2           uint32_t
 *   y            int
 *   col          uint32_t
 *
 * Calls: SpriteArrayAccess, MasterPalConvertCol16
 * Called by: W_Line
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_HLine(uint32_t x1,uint32_t x2,int y,uint32_t col)

{
  int sprite;
  uint32_t u2;
  int i3;
  uint16_t *pu4;
  uint32_t u5;
  
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  u5 = x2;
  if ((int)x2 < (int)x1) {
    u5 = x1;
    x1 = x2;
  }
  if ((((W_y1 <= y) && (y <= W_y2)) && (W_x1 <= (int)u5)) && ((int)x1 <= W_x2))
  {
    if ((int)x1 < W_x1) {
      x1 = W_x1;
    }
    if (W_x2 < (int)u5) {
      u5 = W_x2;
    }
    u2 = MasterPalConvertCol16(col);
    if (*(int *)(sprite + 0x1c) == 1) {
      i3 = *(int *)(*(int *)(sprite + 0x24) + 0x28);
    }
    else {
      i3 = *(int *)(sprite + 0x24);
    }
    if (i3 != 0) {
      pu4 = (uint16_t *)(i3 + *(int *)(*(int *)(sprite + 0x2c) + y * 4) + x1 * 2);
      for (sprite = (u5 - x1) + 1; sprite != 0; sprite = sprite + -1) {
        *pu4 = (short)u2;
        pu4 = pu4 + 1;
      }
    }
  }
  return;
}

/* W_VLine @ 0x0807ed10, 196 bytes
 *
 * Draws a vertical line in colour `col` into the current drawing buffer,
 * clipped to the window.
 *
 * Parameters:
 *   x            int
 *   y1           uint32_t
 *   y2           uint32_t
 *   col          uint32_t
 *
 * Calls: SpriteArrayAccess, MasterPalConvertCol16
 * Called by: W_Line
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_VLine(int x,uint32_t y1,uint32_t y2,uint32_t col)

{
  int i1;
  int sprite;
  uint32_t u3;
  int i4;
  uint16_t *pu5;
  uint32_t u6;
  
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  i1 = V_Width;
  u6 = y2;
  if ((int)y2 < (int)y1) {
    u6 = y1;
    y1 = y2;
  }
  if ((((W_x1 <= x) && (x <= W_x2)) && (W_y1 <= (int)u6)) && ((int)y1 <= W_y2))
  {
    if ((int)y1 < W_y1) {
      y1 = W_y1;
    }
    if (W_y2 < (int)u6) {
      u6 = W_y2;
    }
    u3 = MasterPalConvertCol16(col);
    if (*(int *)(sprite + 0x1c) == 1) {
      i4 = *(int *)(*(int *)(sprite + 0x24) + 0x28);
    }
    else {
      i4 = *(int *)(sprite + 0x24);
    }
    if (i4 != 0) {
      pu5 = (uint16_t *)(i4 + *(int *)(*(int *)(sprite + 0x2c) + y1 * 4) + x * 2);
      for (sprite = (u6 - y1) + 1; sprite != 0; sprite = sprite + -1) {
        *pu5 = (short)u3;
        pu5 = pu5 + i1;
      }
    }
  }
  return;
}

/* W_HLineTransAdd16 @ 0x0807ede0, 312 bytes
 *
 * Draws a horizontal line in colour `col`, added to the screen colours into
 * the current drawing buffer, clipped to the window. 16-bit buffers only.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         uint32_t
 *   arg3         uint32_t
 *   arg4         uint32_t
 *
 * Calls: SpriteArrayAccess, MasterPalConvertCol16
 * Called by: PlayerDrawClsn, W_BoxTransAdd16
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_HLineTransAdd16(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4)

{
  int sprite;
  uint32_t u2;
  uint16_t u3;
  uint16_t u5;
  int i6;
  uint32_t u7;
  uint16_t *pu8;
  uint32_t u4;
  
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  u2 = arg2;
  if ((int)arg2 < (int)arg1) {
    u2 = arg1;
    arg1 = arg2;
  }
  if ((((W_y1 <= (int)arg3) && ((int)arg3 <= W_y2)) && (W_x1 <= (int)u2)) &&
     ((int)arg1 <= W_x2)) {
    if ((int)arg1 < W_x1) {
      arg1 = W_x1;
    }
    if (W_x2 < (int)u2) {
      u2 = W_x2;
    }
    MasterPalConvertCol16(arg4);
    if (*(int *)(sprite + 0x1c) == 1) {
      i6 = *(int *)(*(int *)(sprite + 0x24) + 0x28);
    }
    else {
      i6 = *(int *)(sprite + 0x24);
    }
    if (i6 != 0) {
      pu8 = (uint16_t *)(i6 + *(int *)(*(int *)(sprite + 0x2c) + arg3 * 4) + arg1 * 2);
      for (sprite = (u2 - arg1) + 1; sprite != 0; sprite = sprite + -1) {
        u2 = (uint32_t)*pu8;
        u7 = (arg4 & 0xf800) + (u2 & 0xf800);
        if (0xf800 < u7) {
          u7 = 0xf800;
        }
        u4 = (arg4 & 0x7e0) + (u2 & 0x7e0);
        u3 = (uint16_t)u4;
        if (0x7e0 < u4) {
          u3 = 0x7e0;
        }
        u2 = (u2 & 0x1f) + (arg4 & 0x1f);
        u5 = (uint16_t)u2;
        if (0x1f < u2) {
          u5 = 0x1f;
        }
        *pu8 = (uint16_t)u7 | u3 | u5;
        pu8 = pu8 + 1;
      }
    }
  }
  return;
}

/* W_HLineTransAdd16_B50 @ 0x0807ef20, 310 bytes
 *
 * Draws a horizontal line in colour `col`, added to the screen colours at
 * half intensity (50% blend) into the current drawing buffer, clipped to the
 * window. 16-bit buffers only.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         uint32_t
 *   arg3         uint32_t
 *   arg4         uint32_t
 *
 * Calls: SpriteArrayAccess, MasterPalConvertCol16
 * Called by: W_BoxTransAdd16_B50
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_HLineTransAdd16_B50(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4)

{
  uint16_t u1;
  int sprite;
  uint32_t u3;
  uint32_t u5;
  uint16_t u6;
  int i7;
  uint16_t *pu8;
  uint32_t u4;
  
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  u3 = arg2;
  if ((int)arg2 < (int)arg1) {
    u3 = arg1;
    arg1 = arg2;
  }
  if ((((W_y1 <= (int)arg3) && ((int)arg3 <= W_y2)) && (W_x1 <= (int)u3)) &&
     ((int)arg1 <= W_x2)) {
    if ((int)arg1 < W_x1) {
      arg1 = W_x1;
    }
    if (W_x2 < (int)u3) {
      u3 = W_x2;
    }
    MasterPalConvertCol16(arg4);
    if (*(int *)(sprite + 0x1c) == 1) {
      i7 = *(int *)(*(int *)(sprite + 0x24) + 0x28);
    }
    else {
      i7 = *(int *)(sprite + 0x24);
    }
    if (i7 != 0) {
      pu8 = (uint16_t *)(i7 + *(int *)(*(int *)(sprite + 0x2c) + arg3 * 4) + arg1 * 2);
      for (sprite = (u3 - arg1) + 1; sprite != 0; sprite = sprite + -1) {
        u3 = (uint32_t)(*pu8 >> 1);
        u5 = (arg4 & 0xf800) + (u3 & 0x7800);
        if (0xf800 < u5) {
          u5 = 0xf800;
        }
        u4 = (u3 & 0x3e0) + (arg4 & 0x7e0);
        u1 = (uint16_t)u4;
        if (0x7e0 < u4) {
          u1 = 0x7e0;
        }
        u3 = (u3 & 0xf) + (arg4 & 0x1f);
        u6 = (uint16_t)u3;
        if (0x1f < u3) {
          u6 = 0x1f;
        }
        *pu8 = u1 | (uint16_t)u5 | u6;
        pu8 = pu8 + 1;
      }
    }
  }
  return;
}

/* W_VLineTransAdd16 @ 0x0807f060, 330 bytes
 *
 * Draws a vertical line in colour `col`, added to the screen colours into
 * the current drawing buffer, clipped to the window. 16-bit buffers only.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         uint32_t
 *   arg3         uint32_t
 *   arg4         uint32_t
 *
 * Calls: SpriteArrayAccess, MasterPalConvertCol16
 * Called by: PlayerDrawClsn, W_BoxTransAdd16
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_VLineTransAdd16(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4)

{
  int i1;
  int sprite;
  uint32_t u3;
  uint16_t u4;
  uint16_t u6;
  int i7;
  uint32_t u8;
  uint16_t *pu9;
  uint32_t u5;
  
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  i1 = V_Width;
  u3 = arg3;
  if ((int)arg3 < (int)arg2) {
    u3 = arg2;
    arg2 = arg3;
  }
  if ((((W_x1 <= (int)arg1) && ((int)arg1 <= W_x2)) && (W_y1 <= (int)u3)) &&
     ((int)arg2 <= W_y2)) {
    if ((int)arg2 < W_y1) {
      arg2 = W_y1;
    }
    if (W_y2 < (int)u3) {
      u3 = W_y2;
    }
    MasterPalConvertCol16(arg4);
    if (*(int *)(sprite + 0x1c) == 1) {
      i7 = *(int *)(*(int *)(sprite + 0x24) + 0x28);
    }
    else {
      i7 = *(int *)(sprite + 0x24);
    }
    if (i7 != 0) {
      pu9 = (uint16_t *)(i7 + *(int *)(*(int *)(sprite + 0x2c) + arg2 * 4) + arg1 * 2);
      for (sprite = (u3 - arg2) + 1; sprite != 0; sprite = sprite + -1) {
        u3 = (uint32_t)*pu9;
        u8 = (arg4 & 0xf800) + (u3 & 0xf800);
        if (0xf800 < u8) {
          u8 = 0xf800;
        }
        u5 = (arg4 & 0x7e0) + (u3 & 0x7e0);
        u4 = (uint16_t)u5;
        if (0x7e0 < u5) {
          u4 = 0x7e0;
        }
        u3 = (u3 & 0x1f) + (arg4 & 0x1f);
        u6 = (uint16_t)u3;
        if (0x1f < u3) {
          u6 = 0x1f;
        }
        *pu9 = (uint16_t)u8 | u4 | u6;
        pu9 = pu9 + i1;
      }
    }
  }
  return;
}

/* W_VLineTransAdd16_B50 @ 0x0807f1b0, 328 bytes
 *
 * Draws a vertical line in colour `col`, added to the screen colours at half
 * intensity (50% blend) into the current drawing buffer, clipped to the
 * window. 16-bit buffers only.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         uint32_t
 *   arg3         uint32_t
 *   arg4         uint32_t
 *
 * Calls: SpriteArrayAccess, MasterPalConvertCol16
 * Called by: W_BoxTransAdd16_B50
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_VLineTransAdd16_B50(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4)

{
  int i1;
  uint16_t u2;
  int sprite;
  uint32_t u4;
  uint32_t u6;
  uint16_t u7;
  int i8;
  uint16_t *pu9;
  uint32_t u5;
  
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  i1 = V_Width;
  u4 = arg3;
  if ((int)arg3 < (int)arg2) {
    u4 = arg2;
    arg2 = arg3;
  }
  if ((((W_x1 <= (int)arg1) && ((int)arg1 <= W_x2)) && (W_y1 <= (int)u4)) &&
     ((int)arg2 <= W_y2)) {
    if ((int)arg2 < W_y1) {
      arg2 = W_y1;
    }
    if (W_y2 < (int)u4) {
      u4 = W_y2;
    }
    MasterPalConvertCol16(arg4);
    if (*(int *)(sprite + 0x1c) == 1) {
      i8 = *(int *)(*(int *)(sprite + 0x24) + 0x28);
    }
    else {
      i8 = *(int *)(sprite + 0x24);
    }
    if (i8 != 0) {
      pu9 = (uint16_t *)(i8 + *(int *)(*(int *)(sprite + 0x2c) + arg2 * 4) + arg1 * 2);
      for (sprite = (u4 - arg2) + 1; sprite != 0; sprite = sprite + -1) {
        u4 = (uint32_t)(*pu9 >> 1);
        u6 = (arg4 & 0xf800) + (u4 & 0x7800);
        if (0xf800 < u6) {
          u6 = 0xf800;
        }
        u5 = (u4 & 0x3e0) + (arg4 & 0x7e0);
        u2 = (uint16_t)u5;
        if (0x7e0 < u5) {
          u2 = 0x7e0;
        }
        u4 = (u4 & 0xf) + (arg4 & 0x1f);
        u7 = (uint16_t)u4;
        if (0x1f < u4) {
          u7 = 0x1f;
        }
        *pu9 = u2 | (uint16_t)u6 | u7;
        pu9 = pu9 + i1;
      }
    }
  }
  return;
}

/* W_HLineTransSub16 @ 0x0807f300, 299 bytes
 *
 * Draws a horizontal line in colour `col`, subtracted from the screen
 * colours into the current drawing buffer, clipped to the window. 16-bit
 * buffers only.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         uint32_t
 *   arg3         uint32_t
 *   arg4         uint32_t
 *
 * Calls: SpriteArrayAccess, MasterPalConvertCol16
 * Called by: W_BoxTransSub16
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_HLineTransSub16(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4)

{
  int sprite;
  uint32_t u2;
  int i3;
  int i4;
  int i5;
  uint16_t *pu6;
  
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  u2 = arg2;
  if ((int)arg2 < (int)arg1) {
    u2 = arg1;
    arg1 = arg2;
  }
  if ((((W_y1 <= (int)arg3) && ((int)arg3 <= W_y2)) && (W_x1 <= (int)u2)) &&
     ((int)arg1 <= W_x2)) {
    if ((int)arg1 < W_x1) {
      arg1 = W_x1;
    }
    if (W_x2 < (int)u2) {
      u2 = W_x2;
    }
    MasterPalConvertCol16(arg4);
    if (*(int *)(sprite + 0x1c) == 1) {
      i3 = *(int *)(*(int *)(sprite + 0x24) + 0x28);
    }
    else {
      i3 = *(int *)(sprite + 0x24);
    }
    if (i3 != 0) {
      pu6 = (uint16_t *)(i3 + *(int *)(*(int *)(sprite + 0x2c) + arg3 * 4) + arg1 * 2);
      for (sprite = (u2 - arg1) + 1; sprite != 0; sprite = sprite + -1) {
        u2 = (uint32_t)*pu6;
        i5 = (u2 & 0xf800) - (arg4 & 0xf800);
        i4 = (u2 & 0x7e0) - (arg4 & 0x7e0);
        i3 = (u2 & 0x1f) - (arg4 & 0x1f);
        *pu6 = (uint16_t)i5 & -(short)(i5 >> 0x1f) - 1U |
                  (uint16_t)i4 & -(short)(i4 >> 0x1f) - 1U |
                  (uint16_t)i3 & -(short)(i3 >> 0x1f) - 1U;
        pu6 = pu6 + 1;
      }
    }
  }
  return;
}

/* W_HLineTransSub16_B50 @ 0x0807f430, 302 bytes
 *
 * Draws a horizontal line in colour `col`, subtracted from the screen
 * colours at half intensity (50% blend) into the current drawing buffer,
 * clipped to the window. 16-bit buffers only.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         uint32_t
 *   arg3         uint32_t
 *   arg4         uint32_t
 *
 * Calls: SpriteArrayAccess, MasterPalConvertCol16
 * Called by: W_BoxTransSub16_B50
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_HLineTransSub16_B50(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4)

{
  int sprite;
  uint32_t u2;
  int i3;
  int i4;
  int i5;
  uint16_t *pu6;
  
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  u2 = arg2;
  if ((int)arg2 < (int)arg1) {
    u2 = arg1;
    arg1 = arg2;
  }
  if ((((W_y1 <= (int)arg3) && ((int)arg3 <= W_y2)) && (W_x1 <= (int)u2)) &&
     ((int)arg1 <= W_x2)) {
    if ((int)arg1 < W_x1) {
      arg1 = W_x1;
    }
    if (W_x2 < (int)u2) {
      u2 = W_x2;
    }
    MasterPalConvertCol16(arg4);
    if (*(int *)(sprite + 0x1c) == 1) {
      i3 = *(int *)(*(int *)(sprite + 0x24) + 0x28);
    }
    else {
      i3 = *(int *)(sprite + 0x24);
    }
    if (i3 != 0) {
      pu6 = (uint16_t *)(i3 + *(int *)(*(int *)(sprite + 0x2c) + arg3 * 4) + arg1 * 2);
      for (sprite = (u2 - arg1) + 1; sprite != 0; sprite = sprite + -1) {
        u2 = (uint32_t)(*pu6 >> 1);
        i5 = (u2 & 0x7800) - (arg4 & 0xf800);
        i4 = (u2 & 0x3e0) - (arg4 & 0x7e0);
        i3 = (u2 & 0xf) - (arg4 & 0x1f);
        *pu6 = (uint16_t)i5 & -(short)(i5 >> 0x1f) - 1U |
                  (uint16_t)i4 & -(short)(i4 >> 0x1f) - 1U |
                  (uint16_t)i3 & -(short)(i3 >> 0x1f) - 1U;
        pu6 = pu6 + 1;
      }
    }
  }
  return;
}

/* W_VLineTransSub16 @ 0x0807f560, 314 bytes
 *
 * Draws a vertical line in colour `col`, subtracted from the screen colours
 * into the current drawing buffer, clipped to the window. 16-bit buffers
 * only.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         uint32_t
 *   arg3         uint32_t
 *   arg4         uint32_t
 *
 * Calls: SpriteArrayAccess, MasterPalConvertCol16
 * Called by: W_BoxTransSub16
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_VLineTransSub16(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4)

{
  int i1;
  int sprite;
  uint32_t u3;
  int i4;
  int i5;
  int i6;
  uint16_t *pu7;
  
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  i1 = V_Width;
  u3 = arg3;
  if ((int)arg3 < (int)arg2) {
    u3 = arg2;
    arg2 = arg3;
  }
  if ((((W_x1 <= (int)arg1) && ((int)arg1 <= W_x2)) && (W_y1 <= (int)u3)) &&
     ((int)arg2 <= W_y2)) {
    if ((int)arg2 < W_y1) {
      arg2 = W_y1;
    }
    if (W_y2 < (int)u3) {
      u3 = W_y2;
    }
    MasterPalConvertCol16(arg4);
    if (*(int *)(sprite + 0x1c) == 1) {
      i4 = *(int *)(*(int *)(sprite + 0x24) + 0x28);
    }
    else {
      i4 = *(int *)(sprite + 0x24);
    }
    if (i4 != 0) {
      pu7 = (uint16_t *)(i4 + *(int *)(*(int *)(sprite + 0x2c) + arg2 * 4) + arg1 * 2);
      for (sprite = (u3 - arg2) + 1; sprite != 0; sprite = sprite + -1) {
        u3 = (uint32_t)*pu7;
        i6 = (u3 & 0xf800) - (arg4 & 0xf800);
        i5 = (u3 & 0x7e0) - (arg4 & 0x7e0);
        i4 = (u3 & 0x1f) - (arg4 & 0x1f);
        *pu7 = (uint16_t)i6 & -(short)(i6 >> 0x1f) - 1U |
                  (uint16_t)i5 & -(short)(i5 >> 0x1f) - 1U |
                  (uint16_t)i4 & -(short)(i4 >> 0x1f) - 1U;
        pu7 = pu7 + i1;
      }
    }
  }
  return;
}

/* W_VLineTransSub16_B50 @ 0x0807f6a0, 317 bytes
 *
 * Draws a vertical line in colour `col`, subtracted from the screen colours
 * at half intensity (50% blend) into the current drawing buffer, clipped to
 * the window. 16-bit buffers only.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         uint32_t
 *   arg3         uint32_t
 *   arg4         uint32_t
 *
 * Calls: SpriteArrayAccess, MasterPalConvertCol16
 * Called by: W_BoxTransSub16_B50
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_VLineTransSub16_B50(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4)

{
  int i1;
  int sprite;
  uint32_t u3;
  int i4;
  int i5;
  int i6;
  uint16_t *pu7;
  
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  i1 = V_Width;
  u3 = arg3;
  if ((int)arg3 < (int)arg2) {
    u3 = arg2;
    arg2 = arg3;
  }
  if ((((W_x1 <= (int)arg1) && ((int)arg1 <= W_x2)) && (W_y1 <= (int)u3)) &&
     ((int)arg2 <= W_y2)) {
    if ((int)arg2 < W_y1) {
      arg2 = W_y1;
    }
    if (W_y2 < (int)u3) {
      u3 = W_y2;
    }
    MasterPalConvertCol16(arg4);
    if (*(int *)(sprite + 0x1c) == 1) {
      i4 = *(int *)(*(int *)(sprite + 0x24) + 0x28);
    }
    else {
      i4 = *(int *)(sprite + 0x24);
    }
    if (i4 != 0) {
      pu7 = (uint16_t *)(i4 + *(int *)(*(int *)(sprite + 0x2c) + arg2 * 4) + arg1 * 2);
      for (sprite = (u3 - arg2) + 1; sprite != 0; sprite = sprite + -1) {
        u3 = (uint32_t)(*pu7 >> 1);
        i6 = (u3 & 0x7800) - (arg4 & 0xf800);
        i5 = (u3 & 0x3e0) - (arg4 & 0x7e0);
        i4 = (u3 & 0xf) - (arg4 & 0x1f);
        *pu7 = (uint16_t)i6 & -(short)(i6 >> 0x1f) - 1U |
                  (uint16_t)i5 & -(short)(i5 >> 0x1f) - 1U |
                  (uint16_t)i4 & -(short)(i4 >> 0x1f) - 1U;
        pu7 = pu7 + i1;
      }
    }
  }
  return;
}

/* W_Box @ 0x0807f7e0, 280 bytes
 *
 * Draws a rectangle outline in colour `col` into the current drawing buffer,
 * clipped to the window.
 *
 * Parameters:
 *   x1           int
 *   y1           int
 *   x2           int
 *   y2           int
 *   col          uint32_t
 *
 * Calls: SpriteArrayAccess, MasterPalConvertCol16, W_Line
 * C library: rect
 * Called by: GameLoop, ModeSelect, TrainingMenuDraw
 *
 * Elecbyte file: src/lib/vbuf.c
 * Note: 4 temporaries are float80, as the original kept them in x87 registers.
 */
void W_Box(int x1,int y1,int x2,int y2,uint32_t col)

{
  float80 f1;
  float80 f2;
  float80 f3;
  float80 f4;
  int sprite;
  uint32_t u6;
  uint32_t stk_1c;
  
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_1c = 0;
  u6 = MasterPalConvertCol16(col);
  if (*(int *)(sprite + 0x1c) == 1) {
    rect(*(int *)(sprite + 0x24),x1,y1,x2,y2,u6);
  }
  else {
    stk_1c = *(int *)(sprite + 0x24);
  }
  if (stk_1c != 0) {
    f1 = (float)y2;
    f2 = (float)x1;
    f3 = (float)y1;
    W_Line(f2,f3,f2,f1,u6);
    f4 = (float)x2;
    W_Line(f2,f1,f4,f1,u6);
    W_Line(f4,f1,f4,f3,u6);
    W_Line(f4,f3,f2,f3,u6);
    return;
  }
  return;
}

/* W_BoxTransAdd16 @ 0x0807f900, 100 bytes
 *
 * Draws a rectangle outline in colour `col`, added to the screen colours
 * into the current drawing buffer, clipped to the window. 16-bit buffers
 * only.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         uint32_t
 *   arg3         uint32_t
 *   arg4         uint32_t
 *   arg5         uint32_t
 *
 * Calls: W_HLineTransAdd16, W_VLineTransAdd16
 * Called by: EB_GUIDrawWindow, GameClsnDraw, PlayerDrawClsn
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_BoxTransAdd16(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4,uint32_t arg5)

{
  W_HLineTransAdd16(arg1,arg3,arg2,arg5);
  W_HLineTransAdd16(arg1,arg3,arg4,arg5);
  W_VLineTransAdd16(arg1,arg2,arg4,arg5);
  W_VLineTransAdd16(arg3,arg2,arg4,arg5);
  return;
}

/* W_BoxTransAdd16_B50 @ 0x0807f970, 100 bytes
 *
 * Draws a rectangle outline in colour `col`, added to the screen colours at
 * half intensity (50% blend) into the current drawing buffer, clipped to the
 * window. 16-bit buffers only.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         uint32_t
 *   arg3         uint32_t
 *   arg4         uint32_t
 *   arg5         uint32_t
 *
 * Calls: W_HLineTransAdd16_B50, W_VLineTransAdd16_B50
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_BoxTransAdd16_B50(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4,uint32_t arg5)

{
  W_HLineTransAdd16_B50(arg1,arg3,arg2,arg5);
  W_HLineTransAdd16_B50(arg1,arg3,arg4,arg5);
  W_VLineTransAdd16_B50(arg1,arg2,arg4,arg5);
  W_VLineTransAdd16_B50(arg3,arg2,arg4,arg5);
  return;
}

/* W_BoxTransSub16 @ 0x0807f9e0, 100 bytes
 *
 * Draws a rectangle outline in colour `col`, subtracted from the screen
 * colours into the current drawing buffer, clipped to the window. 16-bit
 * buffers only.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         uint32_t
 *   arg3         uint32_t
 *   arg4         uint32_t
 *   arg5         uint32_t
 *
 * Calls: W_HLineTransSub16, W_VLineTransSub16
 * Called by: GameClsnDraw, PlayerDrawClsn
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_BoxTransSub16(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4,uint32_t arg5)

{
  W_HLineTransSub16(arg1,arg3,arg2,arg5);
  W_HLineTransSub16(arg1,arg3,arg4,arg5);
  W_VLineTransSub16(arg1,arg2,arg4,arg5);
  W_VLineTransSub16(arg3,arg2,arg4,arg5);
  return;
}

/* W_BoxTransSub16_B50 @ 0x0807fa50, 100 bytes
 *
 * Draws a rectangle outline in colour `col`, subtracted from the screen
 * colours at half intensity (50% blend) into the current drawing buffer,
 * clipped to the window. 16-bit buffers only.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         uint32_t
 *   arg3         uint32_t
 *   arg4         uint32_t
 *   arg5         uint32_t
 *
 * Calls: W_HLineTransSub16_B50, W_VLineTransSub16_B50
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_BoxTransSub16_B50(uint32_t arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4,uint32_t arg5)

{
  W_HLineTransSub16_B50(arg1,arg3,arg2,arg5);
  W_HLineTransSub16_B50(arg1,arg3,arg4,arg5);
  W_VLineTransSub16_B50(arg1,arg2,arg4,arg5);
  W_VLineTransSub16_B50(arg3,arg2,arg4,arg5);
  return;
}

/* W_BoxFill @ 0x0807fac0, 301 bytes
 *
 * Draws a filled rectangle in colour `col` into the current drawing buffer,
 * clipped to the window.
 *
 * Parameters:
 *   x1           int
 *   y1           int
 *   x2           int
 *   y2           int
 *   col          uint32_t
 *
 * Calls: SpriteArrayAccess, MasterPalConvertCol16
 * Called by: EB_GUIDrawWindow, GameBGDraw, GameLoop, OptionsScreen
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_BoxFill(int x1,int y1,int x2,int y2,uint32_t col)

{
  int sprite;
  uint32_t u2;
  uint16_t *pu3;
  uint32_t stale_EDX;
  int i4;
  int i5;
  int stk_18;
  
  i5 = x2;
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_18 = 0;
  u2 = MasterPalConvertCol16(col);
  if (*(int *)(sprite + 0x1c) == 1) {
    (**(generic_fn **)(*(int *)(*(int *)(sprite + 0x24) + 0x1c) + 0x34))
              (*(int *)(sprite + 0x24),x1,y1,x2,y2,u2,stale_EDX,
               stale_EDX);
  }
  else {
    stk_18 = *(int *)(sprite + 0x24);
  }
  if (stk_18 != 0) {
    if (x2 < x1) {
      x2 = x1;
      x1 = i5;
    }
    i5 = y2;
    if (y2 < y1) {
      i5 = y1;
      y1 = y2;
    }
    if ((((W_x1 <= x2) && (x1 <= W_x2)) && (W_y1 <= i5)) && (y1 <= W_y2)) {
      if (x1 < W_x1) {
        x1 = W_x1;
      }
      if (W_x2 < x2) {
        x2 = W_x2;
      }
      if (y1 < W_y1) {
        y1 = W_y1;
      }
      if (W_y2 < i5) {
        i5 = W_y2;
      }
      if (y1 <= i5) {
        sprite = *(int *)(sprite + 0x2c);
        do {
          pu3 = (uint16_t *)(stk_18 + *(int *)(sprite + y1 * 4) + x1 * 2);
          for (i4 = (x2 - x1) + 1; i4 != 0; i4 = i4 + -1) {
            *pu3 = (short)u2;
            pu3 = pu3 + 1;
          }
          y1 = y1 + 1;
        } while (y1 <= i5);
      }
    }
  }
  return;
}

/* W_BoxFillTransAdd16 @ 0x0807fbf0, 443 bytes
 *
 * Draws a filled rectangle in colour `col`, added to the screen colours into
 * the current drawing buffer, clipped to the window. 16-bit buffers only.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         int
 *   arg3         uint32_t
 *   arg4         int
 *   arg5         uint32_t
 *
 * Calls: SpriteArrayAccess, MasterPalConvertCol16
 * Called by: CharacterSelectScreenDraw, GameClsnDraw, KeyConfigScreen,
 *            ModeSelect, OptionsScreen, PlayerDrawClsn
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_BoxFillTransAdd16(uint32_t arg1,int arg2,uint32_t arg3,int arg4,uint32_t arg5)

{
  int sprite;
  int i2;
  uint16_t u3;
  uint16_t u5;
  uint32_t u7;
  uint16_t *pu8;
  int i9;
  uint32_t u4;
  uint32_t u6;
  
  i2 = arg4;
  u6 = arg1;
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  if ((int)arg3 < (int)arg1) {
    arg1 = arg3;
    arg3 = u6;
  }
  if (arg4 < arg2) {
    arg4 = arg2;
    arg2 = i2;
  }
  if ((((W_x1 <= (int)arg3) && ((int)arg1 <= W_x2)) && (W_y1 <= arg4)) && (arg2 <= W_y2)
     ) {
    if ((int)arg1 < W_x1) {
      arg1 = W_x1;
    }
    if (W_x2 < (int)arg3) {
      arg3 = W_x2;
    }
    if (arg2 < W_y1) {
      arg2 = W_y1;
    }
    if (W_y2 < arg4) {
      arg4 = W_y2;
    }
    MasterPalConvertCol16(arg5);
    if (*(int *)(sprite + 0x1c) == 1) {
      i2 = *(int *)(*(int *)(sprite + 0x24) + 0x28);
    }
    else {
      i2 = *(int *)(sprite + 0x24);
    }
    if (i2 != 0) {
      for (; arg2 <= arg4; arg2 = arg2 + 1) {
        pu8 = (uint16_t *)(i2 + *(int *)(*(int *)(sprite + 0x2c) + arg2 * 4) + arg1 * 2);
        for (i9 = (arg3 - arg1) + 1; i9 != 0; i9 = i9 + -1) {
          u6 = (uint32_t)*pu8;
          u7 = (arg5 & 0xf800) + (u6 & 0xf800);
          if (0xf800 < u7) {
            u7 = 0xf800;
          }
          u4 = (arg5 & 0x7e0) + (u6 & 0x7e0);
          u3 = (uint16_t)u4;
          if (0x7e0 < u4) {
            u3 = 0x7e0;
          }
          u6 = (arg5 & 0x1f) + (u6 & 0x1f);
          u5 = (uint16_t)u6;
          if (0x1f < u6) {
            u5 = 0x1f;
          }
          *pu8 = (uint16_t)u7 | u3 | u5;
          pu8 = pu8 + 1;
        }
      }
    }
  }
  return;
}

/* W_BoxFillTransAdd16_B50 @ 0x0807fdb0, 432 bytes
 *
 * Draws a filled rectangle in colour `col`, added to the screen colours at
 * half intensity (50% blend) into the current drawing buffer, clipped to the
 * window. 16-bit buffers only.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         int
 *   arg3         uint32_t
 *   arg4         int
 *   arg5         uint32_t
 *
 * Calls: SpriteArrayAccess, MasterPalConvertCol16
 * Called by: EB_GUIDrawWindow, GameLoop, ModeSelect, TrainingMenuDraw
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_BoxFillTransAdd16_B50(uint32_t arg1,int arg2,uint32_t arg3,int arg4,uint32_t arg5)

{
  uint16_t u1;
  int sprite;
  int i3;
  uint32_t u5;
  uint16_t u6;
  uint16_t *pu8;
  int i9;
  uint32_t u4;
  uint32_t u7;
  
  i3 = arg4;
  u7 = arg3;
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  if ((int)arg3 < (int)arg1) {
    arg3 = arg1;
    arg1 = u7;
  }
  if (arg4 < arg2) {
    arg4 = arg2;
    arg2 = i3;
  }
  if ((((W_x1 <= (int)arg3) && ((int)arg1 <= W_x2)) && (W_y1 <= arg4)) && (arg2 <= W_y2)
     ) {
    if ((int)arg1 < W_x1) {
      arg1 = W_x1;
    }
    if (W_x2 < (int)arg3) {
      arg3 = W_x2;
    }
    if (arg2 < W_y1) {
      arg2 = W_y1;
    }
    if (W_y2 < arg4) {
      arg4 = W_y2;
    }
    MasterPalConvertCol16(arg5);
    if (*(int *)(sprite + 0x1c) == 1) {
      i3 = *(int *)(*(int *)(sprite + 0x24) + 0x28);
    }
    else {
      i3 = *(int *)(sprite + 0x24);
    }
    if (i3 != 0) {
      for (; arg2 <= arg4; arg2 = arg2 + 1) {
        pu8 = (uint16_t *)(i3 + *(int *)(*(int *)(sprite + 0x2c) + arg2 * 4) + arg1 * 2);
        for (i9 = (arg3 - arg1) + 1; i9 != 0; i9 = i9 + -1) {
          u7 = (uint32_t)(*pu8 >> 1);
          u5 = (arg5 & 0xf800) + (u7 & 0x7800);
          if (0xf800 < u5) {
            u5 = 0xf800;
          }
          u4 = (u7 & 0x3e0) + (arg5 & 0x7e0);
          u1 = (uint16_t)u4;
          if (0x7e0 < u4) {
            u1 = 0x7e0;
          }
          u7 = (u7 & 0xf) + (arg5 & 0x1f);
          u6 = (uint16_t)u7;
          if (0x1f < u7) {
            u6 = 0x1f;
          }
          *pu8 = u1 | (uint16_t)u5 | u6;
          pu8 = pu8 + 1;
        }
      }
    }
  }
  return;
}

/* W_BoxFillTransSub16 @ 0x0807ff60, 439 bytes
 *
 * Draws a filled rectangle in colour `col`, subtracted from the screen
 * colours into the current drawing buffer, clipped to the window. 16-bit
 * buffers only.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         int
 *   arg3         uint32_t
 *   arg4         int
 *   arg5         uint32_t
 *
 * Calls: SpriteArrayAccess, MasterPalConvertCol16
 * Called by: GameLoop, KeyConfigScreen, OptionsScreen
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_BoxFillTransSub16(uint32_t arg1,int arg2,uint32_t arg3,int arg4,uint32_t arg5)

{
  int sprite;
  int i2;
  int i3;
  uint32_t u4;
  int i5;
  int i6;
  uint16_t *pu7;
  int i8;
  
  i2 = arg4;
  u4 = arg1;
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  if ((int)arg3 < (int)arg1) {
    arg1 = arg3;
    arg3 = u4;
  }
  if (arg4 < arg2) {
    arg4 = arg2;
    arg2 = i2;
  }
  if ((((W_x1 <= (int)arg3) && ((int)arg1 <= W_x2)) && (W_y1 <= arg4)) && (arg2 <= W_y2)
     ) {
    if ((int)arg1 < W_x1) {
      arg1 = W_x1;
    }
    if (W_x2 < (int)arg3) {
      arg3 = W_x2;
    }
    if (arg2 < W_y1) {
      arg2 = W_y1;
    }
    if (W_y2 < arg4) {
      arg4 = W_y2;
    }
    MasterPalConvertCol16(arg5);
    if (*(int *)(sprite + 0x1c) == 1) {
      i2 = *(int *)(*(int *)(sprite + 0x24) + 0x28);
    }
    else {
      i2 = *(int *)(sprite + 0x24);
    }
    if (i2 != 0) {
      for (; arg2 <= arg4; arg2 = arg2 + 1) {
        pu7 = (uint16_t *)(i2 + *(int *)(*(int *)(sprite + 0x2c) + arg2 * 4) + arg1 * 2);
        for (i8 = (arg3 - arg1) + 1; i8 != 0; i8 = i8 + -1) {
          u4 = (uint32_t)*pu7;
          i3 = (u4 & 0xf800) - (arg5 & 0xf800);
          i6 = (u4 & 0x7e0) - (arg5 & 0x7e0);
          i5 = (u4 & 0x1f) - (arg5 & 0x1f);
          *pu7 = (uint16_t)i3 & -(short)(i3 >> 0x1f) - 1U |
                    (uint16_t)i6 & -(short)(i6 >> 0x1f) - 1U |
                    (uint16_t)i5 & -(short)(i5 >> 0x1f) - 1U;
          pu7 = pu7 + 1;
        }
      }
    }
  }
  return;
}

/* W_BoxFillTransSub16_B50 @ 0x08080120, 442 bytes
 *
 * Draws a filled rectangle in colour `col`, subtracted from the screen
 * colours at half intensity (50% blend) into the current drawing buffer,
 * clipped to the window. 16-bit buffers only.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         int
 *   arg3         uint32_t
 *   arg4         int
 *   arg5         uint32_t
 *
 * Calls: SpriteArrayAccess, MasterPalConvertCol16
 *
 * Elecbyte file: src/lib/vbuf.c
 */
void W_BoxFillTransSub16_B50(uint32_t arg1,int arg2,uint32_t arg3,int arg4,uint32_t arg5)

{
  int sprite;
  int i2;
  int i3;
  uint32_t u4;
  int i5;
  int i6;
  uint16_t *pu7;
  int i8;
  
  i2 = arg4;
  u4 = arg1;
  sprite = SpriteArrayAccess(V_Current,V_CurrentIdx);
  if ((int)arg3 < (int)arg1) {
    arg1 = arg3;
    arg3 = u4;
  }
  if (arg4 < arg2) {
    arg4 = arg2;
    arg2 = i2;
  }
  if ((((W_x1 <= (int)arg3) && ((int)arg1 <= W_x2)) && (W_y1 <= arg4)) && (arg2 <= W_y2)
     ) {
    if ((int)arg1 < W_x1) {
      arg1 = W_x1;
    }
    if (W_x2 < (int)arg3) {
      arg3 = W_x2;
    }
    if (arg2 < W_y1) {
      arg2 = W_y1;
    }
    if (W_y2 < arg4) {
      arg4 = W_y2;
    }
    MasterPalConvertCol16(arg5);
    if (*(int *)(sprite + 0x1c) == 1) {
      i2 = *(int *)(*(int *)(sprite + 0x24) + 0x28);
    }
    else {
      i2 = *(int *)(sprite + 0x24);
    }
    if (i2 != 0) {
      for (; arg2 <= arg4; arg2 = arg2 + 1) {
        pu7 = (uint16_t *)(i2 + *(int *)(*(int *)(sprite + 0x2c) + arg2 * 4) + arg1 * 2);
        for (i8 = (arg3 - arg1) + 1; i8 != 0; i8 = i8 + -1) {
          u4 = (uint32_t)(*pu7 >> 1);
          i3 = (u4 & 0x7800) - (arg5 & 0xf800);
          i6 = (u4 & 0x3e0) - (arg5 & 0x7e0);
          i5 = (u4 & 0xf) - (arg5 & 0x1f);
          *pu7 = (uint16_t)i3 & -(short)(i3 >> 0x1f) - 1U |
                    (uint16_t)i6 & -(short)(i6 >> 0x1f) - 1U |
                    (uint16_t)i5 & -(short)(i5 >> 0x1f) - 1U;
          pu7 = pu7 + 1;
        }
      }
    }
  }
  return;
}

