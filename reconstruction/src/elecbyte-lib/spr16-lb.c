/*
 * spr16-lb.c -- 16-bit blitters
 * Pixel loops that draw 8-bit sprites onto 16-bit buffers: plain and opaque,
 * unscaled, scaled and rotated, mirror forms, and shadows.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/spr16-lb.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"

extern uint8_t GlobalTemp[32] __asm__("D_082a6b80"); /* file-static 0x082a6b80 */

/* W_PutSprite8to16 @ 0x0805cd70, 552 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * with colour 0 transparent. Clipped to the window set by W_Define. This is
 * the pixel loop: it reads the 8-bit sprite rows through the sprite's
 * palette converted to 16-bit colours and writes 16-bit pixels.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *
 * Calls: SpriteArrayAccess, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * Called by: EB_GUIPutSprite, W_PutSprite, W_PutSpriteTransAdd8to16_B,
 *            W_ScaleSprite8to16
 *
 * Elecbyte file: src/lib/spr16-lb.c
 */
void W_PutSprite8to16(int *sprites,int index,int x,int y)

{
  int *sprite;
  int sprite2;
  int i3;
  int *sprite3;
  uint8_t *pb5;
  int i6;
  uint16_t *pu7;
  int i8;
  int i9;
  int *pi10;
  int stk_4c;
  int stk_3c;
  int stk_38;
  int stk_34;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_38 = 0;
  i6 = y - sprite[3];
  stk_3c = 0;
  i8 = x - sprite[2];
  if ((((i6 <= W_y2) && (W_y1 < sprite[1] + i6)) && (i8 <= W_x2)) &&
     (W_x1 < *sprite + i8)) {
    stk_34 = i6;
    if (i6 < W_y1) {
      stk_34 = W_y1;
      stk_38 = W_y1 - i6;
    }
    i6 = sprite[1] + i6 + -1;
    if (W_y2 < i6) {
      i6 = W_y2;
    }
    i9 = i8;
    if (i8 < W_x1) {
      stk_3c = W_x1 - i8;
      i9 = W_x1;
    }
    i8 = *sprite + i8 + -1;
    if (W_x2 < i8) {
      i8 = W_x2;
    }
    i8 = (i8 - i9) + 1;
    stk_4c = (i6 - stk_34) + 1;
    if (((0 < i8) && (0 < stk_4c)) &&
       (i6 = SpriteDecompGetAndLockData(sprites,index), i6 != 0)) {
      i3 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      sprite3 = (int *)sprites[5];
      if (sprite3 == (int *)0x0) {
        sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
      }
      else {
        EBPalUpdate(sprite3);
      }
      if (0 < stk_4c) {
        pi10 = (int *)(stk_34 * 4 + *(int *)(sprite2 + 0x2c));
        sprite = (int *)(stk_38 * 4 + sprite[0xb]);
        do {
          pb5 = (uint8_t *)(stk_3c + i6 + *sprite);
          pu7 = (uint16_t *)(i9 * 2 + i3 + *pi10);
          for (sprite2 = i8; sprite2 != 0; sprite2 = sprite2 + -1) {
            if (*pb5 != 0) {
              *pu7 = *(uint16_t *)((int)sprite3 + (uint32_t)*pb5 * 2 + 0x5c);
            }
            pu7 = pu7 + 1;
            pb5 = pb5 + 1;
          }
          pi10 = pi10 + 1;
          sprite = sprite + 1;
          stk_4c = stk_4c + -1;
        } while (stk_4c != 0);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteFlat8to16 @ 0x0805cfa0, 536 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * opaque (colour 0 is drawn too). Clipped to the window set by W_Define.
 * This is the pixel loop: it reads the 8-bit sprite rows through the
 * sprite's palette converted to 16-bit colours and writes 16-bit pixels.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *
 * Calls: SpriteArrayAccess, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * Called by: W_PutSpriteFlat, W_ScaleSpriteFlat8to16
 *
 * Elecbyte file: src/lib/spr16-lb.c
 */
void W_PutSpriteFlat8to16(int *sprites,int index,int x,int y)

{
  uint8_t b1;
  int *sprite;
  int sprite2;
  int i4;
  int *sprite3;
  uint16_t *pu6;
  int i7;
  uint8_t *pb8;
  int i9;
  int i10;
  int *pi11;
  int stk_48;
  int stk_38;
  int stk_34;
  int stk_30;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_34 = 0;
  i7 = y - sprite[3];
  stk_38 = 0;
  i9 = x - sprite[2];
  if ((((i7 <= W_y2) && (W_y1 < sprite[1] + i7)) && (i9 <= W_x2)) &&
     (W_x1 < *sprite + i9)) {
    stk_30 = i7;
    if (i7 < W_y1) {
      stk_30 = W_y1;
      stk_34 = W_y1 - i7;
    }
    i7 = sprite[1] + i7 + -1;
    if (W_y2 < i7) {
      i7 = W_y2;
    }
    i10 = i9;
    if (i9 < W_x1) {
      stk_38 = W_x1 - i9;
      i10 = W_x1;
    }
    i9 = *sprite + i9 + -1;
    if (W_x2 < i9) {
      i9 = W_x2;
    }
    i9 = (i9 - i10) + 1;
    stk_48 = (i7 - stk_30) + 1;
    if (((0 < i9) && (0 < stk_48)) &&
       (i7 = SpriteDecompGetAndLockData(sprites,index), i7 != 0)) {
      i4 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      sprite3 = (int *)sprites[5];
      if (sprite3 == (int *)0x0) {
        sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
      }
      else {
        EBPalUpdate(sprite3);
      }
      if (0 < stk_48) {
        pi11 = (int *)(stk_30 * 4 + *(int *)(sprite2 + 0x2c));
        sprite = (int *)(stk_34 * 4 + sprite[0xb]);
        do {
          pb8 = (uint8_t *)(stk_38 + i7 + *sprite);
          pu6 = (uint16_t *)(i10 * 2 + i4 + *pi11);
          for (sprite2 = i9; sprite2 != 0; sprite2 = sprite2 + -1) {
            b1 = *pb8;
            pb8 = pb8 + 1;
            *pu6 = *(uint16_t *)((int)sprite3 + (uint32_t)b1 * 2 + 0x5c);
            pu6 = pu6 + 1;
          }
          pi11 = pi11 + 1;
          sprite = sprite + 1;
          stk_48 = stk_48 + -1;
        } while (stk_48 != 0);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteMirH8to16 @ 0x0805d1c0, 600 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * with colour 0 transparent, mirrored horizontally. Clipped to the window
 * set by W_Define. This is the pixel loop: it reads the 8-bit sprite rows
 * through the sprite's palette converted to 16-bit colours and writes 16-bit
 * pixels.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *
 * Calls: SpriteArrayAccess, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * Called by: W_PutSpriteMirH, W_PutSpriteTransAddMirH8to16_B,
 *            W_ScaleSpriteMirH8to16
 *
 * Elecbyte file: src/lib/spr16-lb.c
 */
void W_PutSpriteMirH8to16(int *sprites,int index,int x,int y)

{
  int i1;
  int *sprite;
  int sprite2;
  int i4;
  int i5;
  int i6;
  int *sprite3;
  uint8_t *pb8;
  int i9;
  uint16_t *pu10;
  int i11;
  int *pi12;
  int stk_50;
  int stk_3c;
  int stk_38;
  int stk_34;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  i1 = *sprite;
  stk_38 = 0;
  i4 = (sprite[2] - i1) + 1 + x;
  i9 = y - sprite[3];
  stk_3c = 0;
  if ((((i9 <= W_y2) && (W_y1 < sprite[1] + i9)) && (i4 <= W_x2)) && (W_x1 < i1 + i4)
     ) {
    stk_34 = i9;
    if (i9 < W_y1) {
      stk_34 = W_y1;
      stk_38 = W_y1 - i9;
    }
    i9 = sprite[1] + i9 + -1;
    if (W_y2 < i9) {
      i9 = W_y2;
    }
    i11 = i4;
    if (i4 < W_x1) {
      stk_3c = W_x1 - i4;
      i11 = W_x1;
    }
    i4 = i1 + i4 + -1;
    if (W_x2 < i4) {
      i4 = W_x2;
    }
    i4 = (i4 - i11) + 1;
    i9 = (i9 - stk_34) + 1;
    if (((0 < i4) && (0 < i9)) &&
       (i5 = SpriteDecompGetAndLockData(sprites,index), i5 != 0)) {
      i6 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      sprite3 = (int *)sprites[5];
      if (sprite3 == (int *)0x0) {
        sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
      }
      else {
        EBPalUpdate(sprite3);
      }
      stk_50 = 0;
      if (0 < i9) {
        pi12 = (int *)(stk_38 * 4 + sprite[0xb]);
        sprite = (int *)(stk_34 * 4 + *(int *)(sprite2 + 0x2c));
        do {
          pb8 = (uint8_t *)((i5 + *pi12 + i1) - stk_3c);
          pu10 = (uint16_t *)(i11 * 2 + i6 + *sprite);
          for (sprite2 = i4; sprite2 != 0; sprite2 = sprite2 + -1) {
            pb8 = pb8 + -1;
            if (*pb8 != 0) {
              *pu10 = *(uint16_t *)((int)sprite3 + (uint32_t)*pb8 * 2 + 0x5c);
            }
            pu10 = pu10 + 1;
          }
          stk_50 = stk_50 + 1;
          pi12 = pi12 + 1;
          sprite = sprite + 1;
        } while (stk_50 < i9);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteMirV8to16 @ 0x0805d420, 568 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * with colour 0 transparent, mirrored vertically. Clipped to the window set
 * by W_Define. This is the pixel loop: it reads the 8-bit sprite rows
 * through the sprite's palette converted to 16-bit colours and writes 16-bit
 * pixels.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *
 * Calls: SpriteArrayAccess, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * Called by: W_PutSpriteMirV, W_PutSpriteTransAddMirV8to16_B,
 *            W_ScaleSpriteMirV8to16
 *
 * Elecbyte file: src/lib/spr16-lb.c
 */
void W_PutSpriteMirV8to16(int *sprites,int index,int x,int y)

{
  int i1;
  int i2;
  int *sprite;
  int sprite2;
  int i5;
  int i6;
  int *sprite3;
  int i8;
  uint8_t *pb9;
  uint16_t *pu10;
  int i11;
  int i12;
  int i3;
  int stk_3c;
  int stk_38;
  int stk_34;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_38 = 0;
  i1 = sprite[1];
  i11 = x - sprite[2];
  i8 = (sprite[3] - i1) + 1 + y;
  stk_3c = 0;
  if ((((i8 <= W_y2) && (W_y1 < i1 + i8)) && (i11 <= W_x2)) && (W_x1 < *sprite + i11)
     ) {
    stk_34 = i8;
    if (i8 < W_y1) {
      stk_34 = W_y1;
      stk_38 = W_y1 - i8;
    }
    i8 = i1 + i8 + -1;
    if (W_y2 < i8) {
      i8 = W_y2;
    }
    i12 = i11;
    if (i11 < W_x1) {
      stk_3c = W_x1 - i11;
      i12 = W_x1;
    }
    i11 = *sprite + i11 + -1;
    if (W_x2 < i11) {
      i11 = W_x2;
    }
    i11 = (i11 - i12) + 1;
    i8 = (i8 - stk_34) + 1;
    if (((0 < i11) && (0 < i8)) &&
       (i5 = SpriteDecompGetAndLockData(sprites,index), i5 != 0)) {
      i6 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      sprite3 = (int *)sprites[5];
      if (sprite3 == (int *)0x0) {
        sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
      }
      else {
        EBPalUpdate(sprite3);
      }
      i3 = 0;
      if (0 < i8) {
        i2 = sprite[0xb];
        sprite = (int *)(stk_34 * 4 + *(int *)(sprite2 + 0x2c));
        do {
          pb9 = (uint8_t *)(i5 + *(int *)(i2 + -4 + ((i1 - stk_38) - i3) * 4) +
                           stk_3c);
          pu10 = (uint16_t *)(i12 * 2 + i6 + *sprite);
          for (sprite2 = i11; sprite2 != 0; sprite2 = sprite2 + -1) {
            if (*pb9 != 0) {
              *pu10 = *(uint16_t *)((int)sprite3 + (uint32_t)*pb9 * 2 + 0x5c);
            }
            pu10 = pu10 + 1;
            pb9 = pb9 + 1;
          }
          i3 = i3 + 1;
          sprite = sprite + 1;
        } while (i3 < i8);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteMirHV8to16 @ 0x0805d660, 584 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * with colour 0 transparent, mirrored horizontally and vertically. Clipped
 * to the window set by W_Define. This is the pixel loop: it reads the 8-bit
 * sprite rows through the sprite's palette converted to 16-bit colours and
 * writes 16-bit pixels.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x2           int  (x)
 *   y            int
 *
 * Calls: SpriteArrayAccess, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * Called by: W_PutSpriteMirHV, W_PutSpriteTransAddMirHV8to16_B,
 *            W_ScaleSpriteMirHV8to16
 *
 * Elecbyte file: src/lib/spr16-lb.c
 * Note: 1 accesses to parts of a variable are written as sized accesses.
 */
void W_PutSpriteMirHV8to16(int *sprites,int index,int x2,int y)

{
  int i1;
  int i2;
  int i3;
  int *sprite;
  int sprite2;
  int i6;
  int i7;
  int i8;
  int *sprite3;
  uint8_t *pb10;
  uint16_t *pu11;
  int i12;
  int i13;
  int i14;
  int i4;
  int stk_3c;
  int stk_38;
  int stk_34;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  i1 = *sprite;
  i2 = sprite[1];
  stk_38 = 0;
  i6 = (sprite[2] - i1) + 1 + x2;
  stk_3c = 0;
  i12 = (sprite[3] - i2) + 1 + y;
  if ((((i12 <= W_y2) && (W_y1 < i2 + i12)) && (i6 <= W_x2)) && (W_x1 < i1 + i6))
  {
    stk_34 = i12;
    if (i12 < W_y1) {
      stk_34 = W_y1;
      stk_38 = W_y1 - i12;
    }
    i12 = i2 + i12 + -1;
    if (W_y2 < i12) {
      i12 = W_y2;
    }
    i14 = i6;
    if (i6 < W_x1) {
      stk_3c = W_x1 - i6;
      i14 = W_x1;
    }
    i6 = i1 + i6 + -1;
    if (W_x2 < i6) {
      i6 = W_x2;
    }
    i6 = (i6 - i14) + 1;
    i12 = (i12 - stk_34) + 1;
    if (((0 < i6) && (0 < i12)) &&
       (i7 = SpriteDecompGetAndLockData(sprites,index), i7 != 0)) {
      i8 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      sprite3 = (int *)sprites[5];
      if (sprite3 == (int *)0x0) {
        sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
      }
      else {
        EBPalUpdate(sprite3);
      }
      if (0 < i12) {
        i3 = sprite[0xb];
        i4 = 0;
        do {
          pb10 = (uint8_t *)((i7 + *(int *)(i3 + -4 + ((i2 - stk_38) - i4) * 4) +
                             i1) - stk_3c);
          pu11 = (uint16_t *)
                    (i8 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_34 + i4) * 4) + i14 * 2
                    );
          (*(uint32_t *)((char *)&GlobalTemp + 0)) = sprite3 + 0x17;
          for (i13 = i6; i13 != 0; i13 = i13 + -1) {
            pb10 = pb10 + -1;
            if (*pb10 != 0) {
              *pu11 = *(uint16_t *)((int)(sprite3 + 0x17) + (uint32_t)*pb10 * 2);
            }
            pu11 = pu11 + 1;
          }
          i4 = i4 + 1;
        } while (i4 < i12);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_ScaleSprite8to16 @ 0x0805d8b0, 2262 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, with colour 0 transparent. Clipped to the window set by W_Define.
 * This is the pixel loop: it reads the 8-bit sprite rows through the
 * sprite's palette converted to 16-bit colours and writes 16-bit pixels.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData, W_PutSprite8to16
 * Called by: W_ScaleSprite, W_ScaleSpriteTransAdd8to16_B
 *
 * Elecbyte file: src/lib/spr16-lb.c
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 11 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleSprite8to16(int *sprites,int index,float x,float y,float arg5,
                       float arg6)

{
  int i1;
  float80 f2;
  float80 f3;
  float80 f4;
  int *sprite;
  int sprite2;
  int i7;
  int i8;
  int i9;
  int i10;
  int *sprite3;
  uint16_t *pu12;
  int i13;
  uint32_t u14;
  uint32_t u15;
  uint8_t *pb16;
  uint32_t u17;
  int i18;
  int stk_13c;
  int stk_e8;
  int stk_e4;
  int stk_e0;
  uint32_t stk_dc;
  int stk_d0;
  uint32_t stk_54;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_e4 = 0;
  stk_e8 = 0;
  if ((0.0 < arg5) && (0.0 < arg6)) {
    i1 = *sprite;
    i8 = sprite[1];
    if ((((double)0.001) <= ABS((float80)i1 - arg5)) || (((double)0.001) <= ABS((float80)i8 - arg6))) {
      f2 = x - ((float80)sprite[2] * arg5) / (float80)i1;
      f3 = y - ((float80)sprite[3] * arg6) / (float80)i8;
      if ((((f3 <= (float)W_y2) && ((float)W_y1 < (f3 + arg6) - 0.5)) &&
          (f2 <= (float)W_x2)) && ((float)W_x1 < (f2 + arg5) - 0.5)) {
        stk_e0 = (int)X87_FIST32(X87_FLOOR(f3));
        f4 = (float)stk_e0;
        if (f3 <= f4) {
          stk_dc = 0;
        }
        else {
          if ((float)stk_e0 < f3 - 0.5) {
            stk_e0 = stk_e0 + 1;
            f4 = (float)stk_e0;
          }
          stk_54 = (uint32_t)(int64_t)X87_FIST64((((float80)i8 * (f4 - f3)) / arg6) * 65536.0);
          stk_dc = stk_54;
        }
        if (stk_e0 < W_y1) {
          i7 = W_y1 - stk_e0;
          stk_e0 = W_y1;
          stk_54 = (uint32_t)(int64_t)X87_FIST64(((float)(i7 * i8) / arg6) * 65536.0);
          stk_dc = stk_dc + stk_54;
        }
        i7 = (int)X87_FIST32(X87_FLOOR((f3 + arg6) - 0.5));
        if (W_y2 < i7) {
          i7 = W_y2;
        }
        if (i7 - stk_e0 != -1 && -1 < (i7 - stk_e0) + 1) {
          i18 = (int)X87_FIST32(X87_FLOOR(f2));
          f3 = (float80)i18;
          if (f2 <= f3) {
            u17 = 0;
          }
          else {
            if ((float80)i18 < f2 - 0.5) {
              i18 = i18 + 1;
              f3 = (float80)i18;
            }
            stk_54 = (uint32_t)(int64_t)X87_FIST64((((f3 - f2) * (float80)i1) / arg5) * 65536.0)
            ;
            u17 = stk_54;
          }
          if (f2 < (float)W_x1) {
            stk_54 = (uint32_t)(int64_t)X87_FIST64(((float)((W_x1 - i18) * i1) / arg5) * 65536.0)
            ;
            u17 = u17 + stk_54;
            i18 = W_x1;
          }
          i9 = (int)X87_FIST32(X87_FLOOR((f2 + arg5) - 0.5));
          if (W_x2 < i9) {
            i9 = W_x2;
          }
          stk_13c = (int)(int64_t)X87_FIST64((float)(i1 << 0x10) / arg5);
          i1 = (int)X87_FIST32((float)(i8 << 0x10) / arg6);
          for (; ((int)u17 < 0 && (i18 <= i9)); i18 = i18 + 1) {
            u17 = u17 + stk_13c;
          }
          i8 = (int)u17 >> 0x10;
          if (i8 != 0) {
            u17 = u17 & 0xffff;
            stk_e8 = i8;
          }
          for (; ((int)stk_dc < 0 && (stk_e0 <= i7)); stk_e0 = stk_e0 + 1) {
            stk_dc = stk_dc + i1;
          }
          i8 = (int)stk_dc >> 0x10;
          if (i8 != 0) {
            stk_dc = stk_dc & 0xffff;
            stk_e4 = i8;
          }
          i8 = (i9 - i18) + 1;
          i7 = (i7 - stk_e0) + 1;
          if ((0 < i8) && (0 < i7)) {
            i9 = SpriteDecompGetAndLockData(sprites,index);
            if (i9 != 0) {
              i10 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              sprite3 = (int *)sprites[5];
              if (sprite3 == (int *)0x0) {
                sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
              }
              else {
                EBPalUpdate(sprite3);
              }
              stk_d0 = 0;
              if (0 < i7) {
                do {
                  pb16 = (uint8_t *)(stk_e8 +
                                    i9 + *(int *)(sprite[0xb] +
                                                    (((int)stk_dc >> 0x10) + stk_e4) * 4));
                  pu12 = (uint16_t *)
                            (i10 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_e0 + stk_d0) * 4) +
                            i18 * 2);
                  u15 = u17;
                  for (i13 = i8; i13 != 0; i13 = i13 + -1) {
                    if (*pb16 != 0) {
                      *pu12 = *(uint16_t *)((int)sprite3 + (uint32_t)*pb16 * 2 + 0x5c);
                    }
                    pu12 = pu12 + 1;
                    u14 = u15 + stk_13c;
                    u15 = u14 & 0xffff;
                    pb16 = pb16 + (u14 >> 0x10);
                  }
                  stk_dc = stk_dc + i1;
                  stk_d0 = stk_d0 + 1;
                } while (stk_d0 < i7);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSprite8to16(sprites,index,(int)X87_FIST32(x),(int)X87_FIST32(y));
    }
  }
  return;
}

/* W_ScaleSpriteFlat8to16 @ 0x0805e190, 2288 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, opaque (colour 0 is drawn too). Clipped to the window set by
 * W_Define. This is the pixel loop: it reads the 8-bit sprite rows through
 * the sprite's palette converted to 16-bit colours and writes 16-bit pixels.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData, W_PutSpriteFlat8to16
 * Called by: W_ScaleSpriteFlat
 *
 * Elecbyte file: src/lib/spr16-lb.c
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 14 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleSpriteFlat8to16
               (int *sprites,int index,float x,float y,float arg5,float arg6)

{
  int i1;
  int i2;
  float80 f3;
  float80 f4;
  float80 f5;
  int *sprite;
  int sprite2;
  int i8;
  int i9;
  int i10;
  int *sprite3;
  uint32_t u12;
  uint32_t u13;
  uint16_t *pu14;
  int i15;
  int i16;
  uint8_t *pb17;
  int i18;
  int *stk_138;
  int stk_134;
  int stk_e8;
  int stk_e4;
  uint32_t stk_e0;
  uint32_t stk_dc;
  int stk_d0;
  uint32_t stk_54;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_e4 = 0;
  stk_e8 = 0;
  if ((0.0 < arg5) && (0.0 < arg6)) {
    i1 = *sprite;
    i8 = sprite[1];
    if ((((double)0.001) <= ABS((float80)i1 - arg5)) || (((double)0.001) <= ABS((float80)i8 - arg6))) {
      f3 = x - ((float80)sprite[2] * arg5) / (float80)i1;
      f4 = y - ((float80)sprite[3] * arg6) / (float80)i8;
      if ((((f4 <= (float)W_y2) && ((float)W_y1 < (f4 + arg6) - 0.5)) &&
          (f3 <= (float)W_x2)) && ((float)W_x1 < (f3 + arg5) - 0.5)) {
        i16 = (int)X87_FIST32(X87_FLOOR(f4));
        f5 = (float80)i16;
        if (f4 <= f5) {
          stk_dc = 0;
        }
        else {
          if ((float80)i16 < f4 - 0.5) {
            i16 = i16 + 1;
            f5 = (float80)i16;
          }
          stk_54 = (uint32_t)(int64_t)X87_FIST64((((float80)i8 * (f5 - f4)) / arg6) * 65536.0);
          stk_dc = stk_54;
        }
        if (i16 < W_y1) {
          stk_54 = (uint32_t)(int64_t)X87_FIST64(((float)((W_y1 - i16) * i8) / arg6) * 65536.0);
          stk_dc = stk_dc + stk_54;
          i16 = W_y1;
        }
        i18 = (int)X87_FIST32(X87_FLOOR((f4 + arg6) - 0.5));
        if (W_y2 < i18) {
          i18 = W_y2;
        }
        if (i18 - i16 != -1 && -1 < (i18 - i16) + 1) {
          i15 = (int)X87_FIST32(X87_FLOOR(f3));
          f4 = (float80)i15;
          if (f3 <= f4) {
            stk_e0 = 0;
          }
          else {
            if ((float80)i15 < f3 - 0.5) {
              i15 = i15 + 1;
              f4 = (float80)i15;
            }
            stk_54 = (uint32_t)(int64_t)X87_FIST64((((f4 - f3) * (float80)i1) / arg5) * 65536.0)
            ;
            stk_e0 = stk_54;
          }
          if (f3 < (float)W_x1) {
            stk_54 = (uint32_t)(int64_t)X87_FIST64(((float)((W_x1 - i15) * i1) / arg5) * 65536.0)
            ;
            stk_e0 = stk_e0 + stk_54;
            i15 = W_x1;
          }
          i9 = (int)X87_FIST32(X87_FLOOR((f3 + arg5) - 0.5));
          if (W_x2 < i9) {
            i9 = W_x2;
          }
          stk_134 = (int)(int64_t)X87_FIST64((float)(i1 << 0x10) / arg5);
          i1 = (int)X87_FIST32((float)(i8 << 0x10) / arg6);
          for (; ((int)stk_e0 < 0 && (i15 <= i9)); i15 = i15 + 1) {
            stk_e0 = stk_e0 + stk_134;
          }
          i8 = (int)stk_e0 >> 0x10;
          if (i8 != 0) {
            stk_e0 = stk_e0 & 0xffff;
            stk_e8 = i8;
          }
          for (; ((int)stk_dc < 0 && (i16 <= i18)); i16 = i16 + 1) {
            stk_dc = stk_dc + i1;
          }
          i8 = (int)stk_dc >> 0x10;
          if (i8 != 0) {
            stk_dc = stk_dc & 0xffff;
            stk_e4 = i8;
          }
          i8 = (i9 - i15) + 1;
          i18 = (i18 - i16) + 1;
          if ((0 < i8) && (0 < i18)) {
            i9 = SpriteDecompGetAndLockData(sprites,index);
            if (i9 != 0) {
              i10 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              sprite3 = (int *)sprites[5];
              if (sprite3 == (int *)0x0) {
                sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
              }
              else {
                EBPalUpdate(sprite3);
              }
              stk_d0 = 0;
              if (0 < i18) {
                i2 = sprite[0xb];
                stk_138 = (int *)(i16 * 4 + *(int *)(sprite2 + 0x2c));
                do {
                  pb17 = (uint8_t *)(stk_e8 +
                                    i9 + *(int *)(i2 + (((int)stk_dc >> 0x10) + stk_e4) *
                                                             4));
                  pu14 = (uint16_t *)(i15 * 2 + i10 + *stk_138);
                  u13 = stk_e0;
                  for (sprite2 = i8; sprite2 != 0; sprite2 = sprite2 + -1) {
                    *pu14 = *(uint16_t *)((int)sprite3 + (uint32_t)*pb17 * 2 + 0x5c);
                    pu14 = pu14 + 1;
                    u12 = u13 + stk_134;
                    u13 = u12 & 0xffff;
                    pb17 = pb17 + (u12 >> 0x10);
                  }
                  stk_d0 = stk_d0 + 1;
                  stk_138 = stk_138 + 1;
                  stk_dc = stk_dc + i1;
                } while (stk_d0 < i18);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteFlat8to16(sprites,index,(int)X87_FIST32(x),(int)X87_FIST32(y));
    }
  }
  return;
}

/* W_ScaleSpriteMirH8to16 @ 0x0805ea80, 2284 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, with colour 0 transparent, mirrored horizontally. Clipped to the
 * window set by W_Define. This is the pixel loop: it reads the 8-bit sprite
 * rows through the sprite's palette converted to 16-bit colours and writes
 * 16-bit pixels.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData, W_PutSpriteMirH8to16
 * Called by: W_ScaleSpriteMirH, W_ScaleSpriteTransAddMirH8to16_B
 *
 * Elecbyte file: src/lib/spr16-lb.c
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 10 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleSpriteMirH8to16
               (int *sprites,int index,float x,float y,float arg5,float arg6)

{
  int i1;
  int i2;
  float80 f3;
  float80 f4;
  float80 f5;
  int *sprite;
  int sprite2;
  int i8;
  int i9;
  int i10;
  int *sprite3;
  uint16_t *pu12;
  int i13;
  int i14;
  uint32_t u15;
  uint32_t u16;
  uint8_t *pb17;
  uint32_t u18;
  int i19;
  int stk_13c;
  int stk_e8;
  int stk_e4;
  int stk_e0;
  uint32_t stk_dc;
  int stk_d0;
  uint32_t stk_54;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_e4 = 0;
  stk_e8 = 0;
  if ((0.0 < arg5) && (0.0 < arg6)) {
    i1 = *sprite;
    i2 = sprite[1];
    if ((((double)0.001) <= ABS((float80)i1 - arg5)) || (((double)0.001) <= ABS((float80)i2 - arg6))) {
      f3 = x - ((float)((i1 - sprite[2]) + -1) * arg5) / (float80)i1;
      f4 = y - ((float80)sprite[3] * arg6) / (float80)i2;
      if ((((f4 <= (float)W_y2) && ((float)W_y1 < (f4 + arg6) - 0.5)) &&
          (f3 <= (float)W_x2)) && ((float)W_x1 < (f3 + arg5) - 0.5)) {
        stk_e0 = (int)X87_FIST32(X87_FLOOR(f4));
        f5 = (float)stk_e0;
        if (f4 <= f5) {
          stk_dc = 0;
        }
        else {
          if ((float)stk_e0 < f4 - 0.5) {
            stk_e0 = stk_e0 + 1;
            f5 = (float)stk_e0;
          }
          stk_54 = (uint32_t)(int64_t)X87_FIST64((((float80)i2 * (f5 - f4)) / arg6) * 65536.0);
          stk_dc = stk_54;
        }
        if (stk_e0 < W_y1) {
          i8 = W_y1 - stk_e0;
          stk_e0 = W_y1;
          stk_54 = (uint32_t)(int64_t)X87_FIST64(((float)(i8 * i2) / arg6) * 65536.0);
          stk_dc = stk_dc + stk_54;
        }
        i8 = (int)X87_FIST32(X87_FLOOR((f4 + arg6) - 0.5));
        if (W_y2 < i8) {
          i8 = W_y2;
        }
        if (i8 - stk_e0 != -1 && -1 < (i8 - stk_e0) + 1) {
          i19 = (int)X87_FIST32(X87_FLOOR(f3));
          f4 = (float80)i19;
          if (f3 <= f4) {
            u18 = 0;
          }
          else {
            if ((float80)i19 < f3 - 0.5) {
              i19 = i19 + 1;
              f4 = (float80)i19;
            }
            stk_54 = (uint32_t)(int64_t)X87_FIST64((((f4 - f3) * (float80)i1) / arg5) * 65536.0)
            ;
            u18 = stk_54;
          }
          if (f3 < (float)W_x1) {
            stk_54 = (uint32_t)(int64_t)X87_FIST64(((float)((W_x1 - i19) * i1) / arg5) * 65536.0)
            ;
            u18 = u18 + stk_54;
            i19 = W_x1;
          }
          i13 = (int)X87_FIST32(X87_FLOOR((f3 + arg5) - 0.5));
          if (W_x2 < i13) {
            i13 = W_x2;
          }
          stk_13c = (int)(int64_t)X87_FIST64((float)(i1 << 0x10) / arg5);
          i2 = (int)X87_FIST32((float)(i2 << 0x10) / arg6);
          for (; ((int)u18 < 0 && (i19 <= i13)); i19 = i19 + 1) {
            u18 = u18 + stk_13c;
          }
          i9 = (int)u18 >> 0x10;
          if (i9 != 0) {
            u18 = u18 & 0xffff;
            stk_e8 = i9;
          }
          for (; ((int)stk_dc < 0 && (stk_e0 <= i8)); stk_e0 = stk_e0 + 1) {
            stk_dc = stk_dc + i2;
          }
          i9 = (int)stk_dc >> 0x10;
          if (i9 != 0) {
            stk_dc = stk_dc & 0xffff;
            stk_e4 = i9;
          }
          i13 = (i13 - i19) + 1;
          i8 = (i8 - stk_e0) + 1;
          if ((0 < i13) && (0 < i8)) {
            i9 = SpriteDecompGetAndLockData(sprites,index);
            if (i9 != 0) {
              i10 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              sprite3 = (int *)sprites[5];
              if (sprite3 == (int *)0x0) {
                sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
              }
              else {
                EBPalUpdate(sprite3);
              }
              stk_d0 = 0;
              if (0 < i8) {
                do {
                  pb17 = (uint8_t *)(((i9 + *(int *)(sprite[0xb] +
                                                       (((int)stk_dc >> 0x10) + stk_e4) * 4) +
                                      i1) - stk_e8) + -1);
                  pu12 = (uint16_t *)
                            (i10 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_e0 + stk_d0) * 4) +
                            i19 * 2);
                  u16 = u18;
                  for (i14 = i13; i14 != 0; i14 = i14 + -1) {
                    if (*pb17 != 0) {
                      *pu12 = *(uint16_t *)((int)sprite3 + (uint32_t)*pb17 * 2 + 0x5c);
                    }
                    pu12 = pu12 + 1;
                    u15 = u16 + stk_13c;
                    u16 = u15 & 0xffff;
                    pb17 = pb17 + -(u15 >> 0x10);
                  }
                  stk_d0 = stk_d0 + 1;
                  stk_dc = stk_dc + i2;
                } while (stk_d0 < i8);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteMirH8to16(sprites,index,(int)X87_FIST32(x),(int)X87_FIST32(y));
    }
  }
  return;
}

/* W_ScaleSpriteMirV8to16 @ 0x0805f370, 2294 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, with colour 0 transparent, mirrored vertically. Clipped to the
 * window set by W_Define. This is the pixel loop: it reads the 8-bit sprite
 * rows through the sprite's palette converted to 16-bit colours and writes
 * 16-bit pixels.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData, W_PutSpriteMirV8to16
 * Called by: W_ScaleSpriteMirV, W_ScaleSpriteTransAddMirV8to16_B
 *
 * Elecbyte file: src/lib/spr16-lb.c
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 10 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleSpriteMirV8to16
               (int *sprites,int index,float x,float y,float arg5,float arg6)

{
  int i1;
  int i2;
  float80 f3;
  float80 f4;
  float80 f5;
  int *sprite;
  int sprite2;
  int i8;
  int i9;
  int i10;
  int *sprite3;
  uint16_t *pu12;
  int i13;
  int i14;
  uint32_t u15;
  uint32_t u16;
  uint8_t *pb17;
  uint32_t u18;
  int i19;
  int stk_13c;
  int stk_e8;
  int stk_e4;
  int stk_e0;
  uint32_t stk_dc;
  int stk_d0;
  uint32_t stk_54;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_e4 = 0;
  stk_e8 = 0;
  if ((0.0 < arg5) && (0.0 < arg6)) {
    i1 = *sprite;
    i2 = sprite[1];
    if ((((double)0.001) <= ABS((float80)i1 - arg5)) || (((double)0.001) <= ABS((float80)i2 - arg6))) {
      f3 = x - ((float80)sprite[2] * arg5) / (float80)i1;
      f4 = y - ((float)((i2 - sprite[3]) + -1) * arg6) / (float80)i2;
      if ((((f4 <= (float)W_y2) && ((float)W_y1 < (f4 + arg6) - 0.5)) &&
          (f3 <= (float)W_x2)) && ((float)W_x1 < (f3 + arg5) - 0.5)) {
        stk_e0 = (int)X87_FIST32(X87_FLOOR(f4));
        f5 = (float)stk_e0;
        if (f4 <= f5) {
          stk_dc = 0;
        }
        else {
          if ((float)stk_e0 < f4 - 0.5) {
            stk_e0 = stk_e0 + 1;
            f5 = (float)stk_e0;
          }
          stk_54 = (uint32_t)(int64_t)X87_FIST64((((float80)i2 * (f5 - f4)) / arg6) * 65536.0);
          stk_dc = stk_54;
        }
        if (stk_e0 < W_y1) {
          i8 = W_y1 - stk_e0;
          stk_e0 = W_y1;
          stk_54 = (uint32_t)(int64_t)X87_FIST64(((float)(i8 * i2) / arg6) * 65536.0);
          stk_dc = stk_dc + stk_54;
        }
        i8 = (int)X87_FIST32(X87_FLOOR((f4 + arg6) - 0.5));
        if (W_y2 < i8) {
          i8 = W_y2;
        }
        if (i8 - stk_e0 != -1 && -1 < (i8 - stk_e0) + 1) {
          i19 = (int)X87_FIST32(X87_FLOOR(f3));
          f4 = (float80)i19;
          if (f3 <= f4) {
            u18 = 0;
          }
          else {
            if ((float80)i19 < f3 - 0.5) {
              i19 = i19 + 1;
              f4 = (float80)i19;
            }
            stk_54 = (uint32_t)(int64_t)X87_FIST64((((f4 - f3) * (float80)i1) / arg5) * 65536.0)
            ;
            u18 = stk_54;
          }
          if (f3 < (float)W_x1) {
            stk_54 = (uint32_t)(int64_t)X87_FIST64(((float)((W_x1 - i19) * i1) / arg5) * 65536.0)
            ;
            u18 = u18 + stk_54;
            i19 = W_x1;
          }
          i13 = (int)X87_FIST32(X87_FLOOR((f3 + arg5) - 0.5));
          if (W_x2 < i13) {
            i13 = W_x2;
          }
          stk_13c = (int)(int64_t)X87_FIST64((float)(i1 << 0x10) / arg5);
          i1 = (int)X87_FIST32((float)(i2 << 0x10) / arg6);
          for (; ((int)u18 < 0 && (i19 <= i13)); i19 = i19 + 1) {
            u18 = u18 + stk_13c;
          }
          i9 = (int)u18 >> 0x10;
          if (i9 != 0) {
            u18 = u18 & 0xffff;
            stk_e8 = i9;
          }
          for (; ((int)stk_dc < 0 && (stk_e0 <= i8)); stk_e0 = stk_e0 + 1) {
            stk_dc = stk_dc + i1;
          }
          i9 = (int)stk_dc >> 0x10;
          if (i9 != 0) {
            stk_dc = stk_dc & 0xffff;
            stk_e4 = i9;
          }
          i13 = (i13 - i19) + 1;
          i8 = (i8 - stk_e0) + 1;
          if ((0 < i13) && (0 < i8)) {
            i9 = SpriteDecompGetAndLockData(sprites,index);
            if (i9 != 0) {
              i10 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              sprite3 = (int *)sprites[5];
              if (sprite3 == (int *)0x0) {
                sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
              }
              else {
                EBPalUpdate(sprite3);
              }
              stk_d0 = 0;
              if (0 < i8) {
                do {
                  pb17 = (uint8_t *)(stk_e8 +
                                    i9 + *(int *)(sprite[0xb] + -4 +
                                                    ((i2 - stk_e4) - ((int)stk_dc >> 0x10)) *
                                                    4));
                  pu12 = (uint16_t *)
                            (i10 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_e0 + stk_d0) * 4) +
                            i19 * 2);
                  u16 = u18;
                  for (i14 = i13; i14 != 0; i14 = i14 + -1) {
                    if (*pb17 != 0) {
                      *pu12 = *(uint16_t *)((int)sprite3 + (uint32_t)*pb17 * 2 + 0x5c);
                    }
                    pu12 = pu12 + 1;
                    u15 = u16 + stk_13c;
                    u16 = u15 & 0xffff;
                    pb17 = pb17 + (u15 >> 0x10);
                  }
                  stk_d0 = stk_d0 + 1;
                  stk_dc = stk_dc + i1;
                } while (stk_d0 < i8);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteMirV8to16(sprites,index,(int)X87_FIST32(x),(int)X87_FIST32(y));
    }
  }
  return;
}

/* W_ScaleSpriteMirHV8to16 @ 0x0805fc70, 2301 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, with colour 0 transparent, mirrored horizontally and vertically.
 * Clipped to the window set by W_Define. This is the pixel loop: it reads
 * the 8-bit sprite rows through the sprite's palette converted to 16-bit
 * colours and writes 16-bit pixels.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData, W_PutSpriteMirHV8to16
 * Called by: W_ScaleSpriteMirHV, W_ScaleSpriteTransAddMirHV8to16_B
 *
 * Elecbyte file: src/lib/spr16-lb.c
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 9 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleSpriteMirHV8to16
               (int *sprites,int index,float x,float y,float arg5,float arg6)

{
  int i1;
  int i2;
  int i3;
  float80 f4;
  float80 f5;
  float80 f6;
  int *sprite;
  int sprite2;
  int i9;
  int i10;
  int i11;
  int *sprite3;
  uint16_t *pu13;
  int i14;
  int i15;
  uint32_t u16;
  uint32_t u17;
  uint8_t *pb18;
  uint32_t u19;
  int i20;
  int stk_13c;
  int stk_e8;
  int stk_e4;
  int stk_e0;
  uint32_t stk_dc;
  int stk_d0;
  uint32_t stk_54;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_e4 = 0;
  stk_e8 = 0;
  if ((0.0 < arg5) && (0.0 < arg6)) {
    i2 = *sprite;
    i3 = sprite[1];
    if ((((double)0.001) <= ABS((float80)i2 - arg5)) || (((double)0.001) <= ABS((float80)i3 - arg6))) {
      f4 = x - ((float)((i2 - sprite[2]) + -1) * arg5) / (float80)i2;
      f5 = y - ((float)((i3 - sprite[3]) + -1) * arg6) / (float80)i3;
      if ((((f5 <= (float)W_y2) && ((float)W_y1 < (f5 + arg6) - 0.5)) &&
          (f4 <= (float)W_x2)) && ((float)W_x1 < (f4 + arg5) - 0.5)) {
        stk_e0 = (int)X87_FIST32(X87_FLOOR(f5));
        f6 = (float)stk_e0;
        if (f5 <= f6) {
          stk_dc = 0;
        }
        else {
          if ((float)stk_e0 < f5 - 0.5) {
            stk_e0 = stk_e0 + 1;
            f6 = (float)stk_e0;
          }
          stk_54 = (uint32_t)(int64_t)X87_FIST64((((float80)i3 * (f6 - f5)) / arg6) * 65536.0);
          stk_dc = stk_54;
        }
        if (stk_e0 < W_y1) {
          i9 = W_y1 - stk_e0;
          stk_e0 = W_y1;
          stk_54 = (uint32_t)(int64_t)X87_FIST64(((float)(i9 * i3) / arg6) * 65536.0);
          stk_dc = stk_dc + stk_54;
        }
        i9 = (int)X87_FIST32(X87_FLOOR((f5 + arg6) - 0.5));
        if (W_y2 < i9) {
          i9 = W_y2;
        }
        if (i9 - stk_e0 != -1 && -1 < (i9 - stk_e0) + 1) {
          i20 = (int)X87_FIST32(X87_FLOOR(f4));
          f5 = (float80)i20;
          if (f4 <= f5) {
            u19 = 0;
          }
          else {
            if ((float80)i20 < f4 - 0.5) {
              i20 = i20 + 1;
              f5 = (float80)i20;
            }
            stk_54 = (uint32_t)(int64_t)X87_FIST64((((f5 - f4) * (float80)i2) / arg5) * 65536.0)
            ;
            u19 = stk_54;
          }
          if (f4 < (float)W_x1) {
            stk_54 = (uint32_t)(int64_t)X87_FIST64(((float)((W_x1 - i20) * i2) / arg5) * 65536.0)
            ;
            u19 = u19 + stk_54;
            i20 = W_x1;
          }
          i14 = (int)X87_FIST32(X87_FLOOR((f4 + arg5) - 0.5));
          if (W_x2 < i14) {
            i14 = W_x2;
          }
          stk_13c = (int)(int64_t)X87_FIST64((float)(i2 << 0x10) / arg5);
          i1 = (int)X87_FIST32((float)(i3 << 0x10) / arg6);
          for (; ((int)u19 < 0 && (i20 <= i14)); i20 = i20 + 1) {
            u19 = u19 + stk_13c;
          }
          i10 = (int)u19 >> 0x10;
          if (i10 != 0) {
            u19 = u19 & 0xffff;
            stk_e8 = i10;
          }
          for (; ((int)stk_dc < 0 && (stk_e0 <= i9)); stk_e0 = stk_e0 + 1) {
            stk_dc = stk_dc + i1;
          }
          i10 = (int)stk_dc >> 0x10;
          if (i10 != 0) {
            stk_dc = stk_dc & 0xffff;
            stk_e4 = i10;
          }
          i14 = (i14 - i20) + 1;
          i9 = (i9 - stk_e0) + 1;
          if ((0 < i14) && (0 < i9)) {
            i10 = SpriteDecompGetAndLockData(sprites,index);
            if (i10 != 0) {
              i11 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              sprite3 = (int *)sprites[5];
              if (sprite3 == (int *)0x0) {
                sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
              }
              else {
                EBPalUpdate(sprite3);
              }
              stk_d0 = 0;
              if (0 < i9) {
                do {
                  pb18 = (uint8_t *)(((i10 + *(int *)(sprite[0xb] + -4 +
                                                        ((i3 - stk_e4) -
                                                        ((int)stk_dc >> 0x10)) * 4) + i2) -
                                     stk_e8) + -1);
                  pu13 = (uint16_t *)
                            (i11 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_e0 + stk_d0) * 4) +
                            i20 * 2);
                  u17 = u19;
                  for (i15 = i14; i15 != 0; i15 = i15 + -1) {
                    if (*pb18 != 0) {
                      *pu13 = *(uint16_t *)((int)sprite3 + (uint32_t)*pb18 * 2 + 0x5c);
                    }
                    pu13 = pu13 + 1;
                    u16 = u17 + stk_13c;
                    u17 = u16 & 0xffff;
                    pb18 = pb18 + -(u16 >> 0x10);
                  }
                  stk_d0 = stk_d0 + 1;
                  stk_dc = stk_dc + i1;
                } while (stk_d0 < i9);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteMirHV8to16(sprites,index,(int)X87_FIST32(x),(int)X87_FIST32(y));
    }
  }
  return;
}

/* W_RotateSprite8to16_P @ 0x08060570, 3728 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, with colour 0 transparent. Clipped to the window
 * set by W_Define. This is the pixel loop: it reads the 8-bit sprite rows
 * through the sprite's palette converted to 16-bit colours and writes 16-bit
 * pixels. Scaling without rotation is handed to the scaled blitter.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x2           float  (x)
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         float
 *   arg9         float
 *
 * Calls: SpriteArrayAccess, roundfloat, W_ScaleSprite_S,
 *        SpriteDecompGetAndLockData, SpriteDecompGetData,
 *        SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * Called by: W_RotateSpriteTransAdd8to16_B_P, W_RotateSprite_P
 *
 * Elecbyte file: src/lib/spr16-lb.c
 * Note: 2 accesses to parts of a variable are written as sized accesses.
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 14 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: untyped (undefined4) <-> float moves kept as bit copies: 0 assignments,
 *       0 calls, 5 returns
 * Note: Locals live in `frame`, laid out as on the original stack (0x90 bytes,
 *       13 variables), because their address is taken.
 * Note: 8 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t
W_RotateSprite8to16_P
          (int *sprites,int index,float x2,float y,float arg5,float arg6,
          float arg7,float arg8,float arg9)

{
  int i1;
  int i2;
  uint8_t b3;
  int i4;
  int i5;
  int i6;
  int i7;
  int i8;
  int i9;
  uint64_t u10;
  float80 f11;
  float80 f12;
  float80 f13;
  float80 f14;
  float80 f15;
  float80 f16;
  float80 f17;
  float80 f18;
  int *sprite;
  int sprite2;
  int i21;
  int i22;
  uint32_t u23;
  int i24;
  int i25;
  int i26;
  int *sprite3;
  int i28;
  int i29;
  int i30;
  int i31;
  int i32;
  int i33;
  int i34;
  int i35;
  int i36;
  uint16_t entry_FPUControlWord;
  unsigned char frame[0x90] __attribute__((aligned(16)));
#define stk_90 (*(int *)(frame + 0x0))
#define stk_8c (*(float *)(frame + 0x4))
#define stk_88 (*(float *)(frame + 0x8))
#define stk_84 (*(float *)(frame + 0xc))
#define stk_80 (*(float *)(frame + 0x10))
#define stk_74 (*(int *)(frame + 0x1c))
#define stk_70 (*(int *)(frame + 0x20))
#define stk_64 (*(int *)(frame + 0x2c))
#define stk_60 (*(int *)(frame + 0x30))
#define stk_5c (*(int *)(frame + 0x34))
#define stk_50 (*(int *)(frame + 0x40))
#define stk_38 (*(uint16_t **)(frame + 0x58))
#define stk_20 (*(uint32_t *)(frame + 0x70))
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  i4 = sprite[0xb];
  i21 = roundfloat(x2);
  i22 = roundfloat(y);
  i33 = (int)X87_FIST32(arg6 * 1024.0);
  if (i33 < 0) {
    i33 = -i33;
    arg5 = arg5 + 180.0;
  }
  stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
  i35 = (int)X87_FIST32(arg7 * 1024.0);
  if (i35 < 0) {
    i35 = -i35;
    arg5 = arg5 + 180.0;
  }
  if (i33 == 0) {
    return BITS_I2F(stk_20);
  }
  if (i35 == 0) {
    return BITS_I2F(stk_20);
  }
  if (arg5 < 0.0) {
    arg5 = (float)((int)X87_FIST32(-arg5 * ((float)0.0027777778f)) * 0x168 + 0x168) + arg5;
  }
  u10 = (int64_t)(int)X87_FIST32(arg5 * 8.0) % 0xb40;
  i30 = (int)u10;
  if (i30 == 0) {
L_08060862:
    u23 = W_ScaleSprite_S(sprites,index,x2,y,arg6 * arg8,arg7 * arg9);
    return BITS_I2F(u23);
  }
  if (i30 == 0x5a0) {
    arg7 = -arg7;
    arg6 = -arg6;
    goto L_08060862;
  }
  i5 = *sprite;
  i6 = sprite[1];
  i7 = sprite[2];
  i8 = sprite[3];
  f11 = (float)SinTable[(i30 + 0x2d0) % 0xb40];
  f12 = f11 * 0.0009765625;
  f14 = (float)SinTable[(int)((int64_t)
                                 ((uint64_t)(uint32_t)(i30 >> 0x1f) << 0x20 | u10 & 0xffffffff) %
                                0xb40)];
  f13 = f14 * 0.0009765625;
  i1 = (int)X87_FIST32((float)((SinTable[(i30 + 0x2d0) % 0xb40] << 0x10) / i33) / arg8);
  stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
  i2 = (int)X87_FIST32((float)((SinTable[(int)((int64_t)
                                             ((uint64_t)(uint32_t)(i30 >> 0x1f) << 0x20 |
                                             u10 & 0xffffffff) % 0xb40)] << 0x10) / i35) /
                     arg8);
  if (i30 < 0x2d0) {
    i30 = -i7;
    i24 = -i8;
    i25 = (i5 - i7) + -1;
    i26 = (i6 - i8) + -1;
L_08060aaf:
    f15 = (float80)i30;
    f16 = (float80)i25;
    stk_84 = (float80)i24;
    stk_8c = (float80)i26;
    stk_88 = stk_8c;
    f18 = f15;
  }
  else {
    if (i30 < 0x5a0) {
      i25 = (i5 - i7) + -1;
      i24 = -i8;
      i30 = (i6 - i8) + -1;
      i26 = -i7;
    }
    else {
      if (i30 < 0x870) {
        i30 = (i5 - i7) + -1;
        i24 = (i6 - i8) + -1;
        i25 = -i7;
        i26 = -i8;
        goto L_08060aaf;
      }
      if (0xb3f < i30) {
        return BITS_I2F(stk_20);
      }
      i25 = -i7;
      i24 = (i6 - i8) + -1;
      i30 = -i8;
      i26 = (i5 - i7) + -1;
    }
    f15 = (float80)i25;
    stk_88 = (float80)i30;
    f16 = (float80)i26;
    stk_8c = (float80)i24;
    stk_84 = stk_88;
    f18 = f16;
  }
  stk_80 = (float80)i25;
  stk_88 = stk_88 * arg7;
  f15 = f15 * arg6;
  f17 = (float80)i24 * arg7;
  f16 = f16 * arg6;
  i30 = roundfloat((-f15 * f13 + f17 * f12) * arg9);
  i25 = roundfloat((-f16 * f13 + stk_88 * f12) * arg9);
  stk_50 = roundfloat((-(stk_80 * arg6) * f13 + stk_84 * arg7 * f12) * arg9);
  stk_90 = roundfloat((-(f18 * arg6) * f13 + stk_8c * arg7 * f12) * arg9);
  if ((stk_50 == i30) || (stk_50 == i25)) {
    stk_74 = 0;
    stk_70 = 0;
    stk_60 = (int)X87_FIST32((f15 * f12 + f17 * f13) * 65536.0 * arg8);
    stk_64 = (int)X87_FIST32((f16 * f12 + stk_88 * f13) * 65536.0 * arg8);
  }
  else {
    f18 = f12 * stk_80 * arg6 + stk_84 * arg7 * f13;
    stk_70 = (int)X87_FIST32(((f18 - (f15 * f12 + f17 * f13)) * 65536.0 * arg8) /
                          (float)(stk_50 - i30));
    if (stk_70 < 0) {
      stk_70 = -stk_70;
    }
    stk_74 = (int)X87_FIST32((((stk_88 * f13 + f16 * f12) - f18) * 65536.0 * arg8) /
                          (float)(stk_50 - i25));
    if (stk_74 < 0) {
      stk_74 = -stk_74;
    }
    stk_64 = (int)X87_FIST32(f18 * 65536.0 * arg8);
    stk_60 = stk_64;
  }
  for (; stk_50 < W_y1 - i22; stk_50 = stk_50 + 1) {
    i24 = stk_74;
    if (stk_50 < i30) {
      i24 = -stk_70;
    }
    stk_60 = stk_60 + i24;
    i24 = stk_74;
    if (i25 <= stk_50) {
      i24 = -stk_70;
    }
    stk_64 = stk_64 + i24;
  }
  if (W_y2 - i22 < stk_90) {
    stk_90 = W_y2 - i22;
  }
  i24 = SpriteDecompGetAndLockData(sprites,index);
  if (i24 == 0) {
    return 0;
  }
  i26 = SpriteDecompGetData(V_Current,V_CurrentIdx);
  sprite3 = (int *)sprites[5];
  if (sprite3 == (int *)0x0) {
    sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
  }
  else {
    EBPalUpdate(sprite3);
  }
  if (stk_50 <= stk_90) {
    i28 = W_x1 - i21;
    do {
      i32 = stk_60 >> 0x10;
      if (stk_60 >> 0x10 < i28) {
        i32 = i28;
      }
      i36 = stk_64 >> 0x10;
      if (W_x2 - i21 < stk_64 >> 0x10) {
        i36 = W_x2 - i21;
      }
      stk_5c = (int)X87_FIST32(((((float80)i32 / arg8) * f11 -
                             ((float)stk_50 / arg9) * f14) * 65536.0) / (float80)i33) +
                 i7 * 0x10000;
      i34 = i8 * 0x10000 +
               (int)X87_FIST32(((((float80)i32 / arg8) * f14 +
                           ((float)stk_50 / arg9) * f11) * 65536.0) / (float80)i35);
      stk_38 = (uint16_t *)
                 (i26 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_50 + i22) * 4) +
                 (i21 + i32) * 2);
      i31 = (i36 - i32) + 1;
      i9 = i36 - i32;
      i29 = i2 * i31 + i34;
      for (i31 = stk_5c + i1 * i31;
          (SBORROW4(i36,i32) == i9 < 0 &&
          ((((i6 <= i29 >> 0x10 || (i5 <= i31 >> 0x10)) || (i29 >> 0x10 < 0)) ||
           (i31 >> 0x10 < 0)))); i31 = i31 - i1) {
        i36 = i36 + -1;
        i29 = i29 - i2;
        i9 = i36 - i32;
      }
      for (; (i32 <= i36 &&
             (((i6 <= i34 >> 0x10 || (i5 <= stk_5c >> 0x10)) ||
              ((i34 >> 0x10 < 0 || (stk_5c >> 0x10 < 0)))))); stk_5c = stk_5c + i1) {
        stk_38 = stk_38 + 1;
        i32 = i32 + 1;
        i34 = i34 + i2;
      }
      i32 = (i36 - i32) + 1;
      if (0 < i32) {
        do {
          b3 = *(uint8_t *)((stk_5c >> 0x10) + i24 + *(int *)(i4 + (i34 >> 0x10) * 4));
          if (b3 != 0) {
            *stk_38 = *(uint16_t *)((int)sprite3 + (uint32_t)b3 * 2 + 0x5c);
          }
          stk_5c = stk_5c + i1;
          stk_38 = stk_38 + 1;
          i34 = i34 + i2;
          i32 = i32 + -1;
        } while (i32 != 0);
      }
      i32 = stk_74;
      if (stk_50 < i30) {
        i32 = -stk_70;
      }
      stk_60 = stk_60 + i32;
      i32 = stk_74;
      if (i25 <= stk_50) {
        i32 = -stk_70;
      }
      stk_64 = stk_64 + i32;
      stk_50 = stk_50 + 1;
    } while (stk_50 <= stk_90);
  }
  u23 = SpriteDecompUnlockData();
  return BITS_I2F(u23);
}
#undef stk_90
#undef stk_8c
#undef stk_88
#undef stk_84
#undef stk_80
#undef stk_74
#undef stk_70
#undef stk_64
#undef stk_60
#undef stk_5c
#undef stk_50
#undef stk_38
#undef stk_20

/* W_RotateSpriteMirH8to16_P @ 0x08061400, 3664 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, with colour 0 transparent, mirrored horizontally.
 * Clipped to the window set by W_Define. This is the pixel loop: it reads
 * the 8-bit sprite rows through the sprite's palette converted to 16-bit
 * colours and writes 16-bit pixels. Scaling without rotation is handed to
 * the scaled blitter.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x2           float  (x)
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         float
 *   arg9         float
 *
 * Calls: SpriteArrayAccess, roundfloat, W_ScaleSprite_S,
 *        SpriteDecompGetAndLockData, SpriteDecompGetData,
 *        SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * Called by: W_RotateSpriteTransAddMirH8to16_B_P, W_RotateSprite_P
 *
 * Elecbyte file: src/lib/spr16-lb.c
 * Note: 2 accesses to parts of a variable are written as sized accesses.
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 14 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: untyped (undefined4) <-> float moves kept as bit copies: 0 assignments,
 *       0 calls, 5 returns
 * Note: Locals live in `frame`, laid out as on the original stack (0x90 bytes,
 *       13 variables), because their address is taken.
 * Note: 8 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t
W_RotateSpriteMirH8to16_P
          (int *sprites,int index,float x2,float y,float arg5,float arg6,
          float arg7,float arg8,float arg9)

{
  int i1;
  int i2;
  uint8_t b3;
  int i4;
  int i5;
  int i6;
  int i7;
  int i8;
  int i9;
  uint64_t u10;
  float80 f11;
  float80 f12;
  float80 f13;
  float80 f14;
  float80 f15;
  float80 f16;
  float80 f17;
  float80 f18;
  int *sprite;
  int sprite2;
  int i21;
  int i22;
  uint32_t u23;
  int i24;
  int i25;
  int i26;
  int *sprite3;
  int i28;
  int i29;
  int i30;
  int i31;
  int i32;
  int i33;
  int i34;
  int i35;
  uint16_t entry_FPUControlWord;
  unsigned char frame[0x90] __attribute__((aligned(16)));
#define stk_90 (*(int *)(frame + 0x0))
#define stk_8c (*(float *)(frame + 0x4))
#define stk_88 (*(float *)(frame + 0x8))
#define stk_84 (*(float *)(frame + 0xc))
#define stk_80 (*(float *)(frame + 0x10))
#define stk_74 (*(int *)(frame + 0x1c))
#define stk_70 (*(int *)(frame + 0x20))
#define stk_64 (*(int *)(frame + 0x2c))
#define stk_60 (*(int *)(frame + 0x30))
#define stk_5c (*(int *)(frame + 0x34))
#define stk_50 (*(int *)(frame + 0x40))
#define stk_38 (*(uint16_t **)(frame + 0x58))
#define stk_20 (*(uint32_t *)(frame + 0x70))
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  i4 = sprite[0xb];
  i21 = roundfloat(x2);
  i22 = roundfloat(y);
  i31 = (int)X87_FIST32(arg6 * 1024.0);
  if (i31 < 0) {
    i31 = -i31;
    arg5 = arg5 + 180.0;
  }
  stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
  i34 = (int)X87_FIST32(arg7 * 1024.0);
  if (i34 < 0) {
    i34 = -i34;
    arg5 = arg5 + 180.0;
  }
  if (i31 == 0) {
    return BITS_I2F(stk_20);
  }
  if (i34 == 0) {
    return BITS_I2F(stk_20);
  }
  if (arg5 < 0.0) {
    arg5 = (float)((int)X87_FIST32(-arg5 * ((float)0.0027777778f)) * 0x168 + 0x168) + arg5;
  }
  u10 = (int64_t)(int)X87_FIST32(arg5 * 8.0) % 0xb40;
  i29 = (int)u10;
  if (i29 == 0) {
    arg6 = -arg6;
L_080616ed:
    u23 = W_ScaleSprite_S(sprites,index,x2,y,arg6 * arg8,arg7 * arg9);
    return BITS_I2F(u23);
  }
  if (i29 == 0x5a0) {
    arg7 = -arg7;
    goto L_080616ed;
  }
  i5 = *sprite;
  i6 = sprite[1];
  i7 = sprite[2];
  i8 = sprite[3];
  f11 = (float)SinTable[(i29 + 0x2d0) % 0xb40];
  f12 = f11 * 0.0009765625;
  f14 = (float)SinTable[(int)((int64_t)
                                 ((uint64_t)(uint32_t)(i29 >> 0x1f) << 0x20 | u10 & 0xffffffff) %
                                0xb40)];
  f13 = f14 * 0.0009765625;
  i1 = (int)X87_FIST32((float)((SinTable[(i29 + 0x2d0) % 0xb40] << 0x10) / i31) / arg8);
  stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
  i2 = (int)X87_FIST32((float)((SinTable[(int)((int64_t)
                                             ((uint64_t)(uint32_t)(i29 >> 0x1f) << 0x20 |
                                             u10 & 0xffffffff) % 0xb40)] << 0x10) / i34) /
                     arg8);
  if (i29 < 0x2d0) {
    i29 = -i7;
    i24 = -i8;
    i25 = (i5 - i7) + -1;
    i26 = (i6 - i8) + -1;
L_0806193f:
    f15 = (float80)i29;
    f16 = (float80)i25;
    stk_84 = (float80)i24;
    stk_8c = (float80)i26;
    stk_88 = stk_8c;
    f18 = f15;
  }
  else {
    if (i29 < 0x5a0) {
      i25 = (i5 - i7) + -1;
      i24 = -i8;
      i29 = (i6 - i8) + -1;
      i26 = -i7;
    }
    else {
      if (i29 < 0x870) {
        i29 = (i5 - i7) + -1;
        i24 = (i6 - i8) + -1;
        i25 = -i7;
        i26 = -i8;
        goto L_0806193f;
      }
      if (0xb3f < i29) {
        return BITS_I2F(stk_20);
      }
      i25 = -i7;
      i24 = (i6 - i8) + -1;
      i29 = -i8;
      i26 = (i5 - i7) + -1;
    }
    f15 = (float80)i25;
    stk_88 = (float80)i29;
    f16 = (float80)i26;
    stk_8c = (float80)i24;
    stk_84 = stk_88;
    f18 = f16;
  }
  stk_80 = (float80)i25;
  stk_88 = stk_88 * arg7;
  f15 = f15 * arg6;
  f17 = (float80)i24 * arg7;
  f16 = f16 * arg6;
  i29 = roundfloat((-f15 * f13 + f17 * f12) * arg9);
  i24 = roundfloat((-f16 * f13 + stk_88 * f12) * arg9);
  stk_50 = roundfloat((-(stk_80 * arg6) * f13 + stk_84 * arg7 * f12) * arg9);
  stk_90 = roundfloat((-(f18 * arg6) * f13 + stk_8c * arg7 * f12) * arg9);
  if ((stk_50 == i29) || (stk_50 == i24)) {
    stk_74 = 0;
    stk_70 = 0;
    stk_60 = (int)X87_FIST32((f15 * f12 + f17 * f13) * 65536.0 * arg8);
    stk_64 = (int)X87_FIST32((f16 * f12 + stk_88 * f13) * 65536.0 * arg8);
  }
  else {
    f18 = f12 * stk_80 * arg6 + stk_84 * arg7 * f13;
    stk_70 = (int)X87_FIST32(((f18 - (f15 * f12 + f17 * f13)) * 65536.0 * arg8) /
                          (float)(stk_50 - i29));
    if (stk_70 < 0) {
      stk_70 = -stk_70;
    }
    stk_74 = (int)X87_FIST32((((stk_88 * f13 + f16 * f12) - f18) * 65536.0 * arg8) /
                          (float)(stk_50 - i24));
    if (stk_74 < 0) {
      stk_74 = -stk_74;
    }
    stk_64 = (int)X87_FIST32(f18 * 65536.0 * arg8);
    stk_60 = stk_64;
  }
  for (; stk_50 < W_y1 - i22; stk_50 = stk_50 + 1) {
    i25 = stk_74;
    if (stk_50 < i29) {
      i25 = -stk_70;
    }
    stk_60 = stk_60 + i25;
    i25 = stk_74;
    if (i24 <= stk_50) {
      i25 = -stk_70;
    }
    stk_64 = stk_64 + i25;
  }
  if (W_y2 - i22 < stk_90) {
    stk_90 = W_y2 - i22;
  }
  i25 = SpriteDecompGetAndLockData(sprites,index);
  if (i25 == 0) {
    return 0;
  }
  i26 = SpriteDecompGetData(V_Current,V_CurrentIdx);
  sprite3 = (int *)sprites[5];
  if (sprite3 == (int *)0x0) {
    sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
  }
  else {
    EBPalUpdate(sprite3);
  }
  if (stk_50 <= stk_90) {
    do {
      i33 = stk_60 >> 0x10;
      i35 = stk_64 >> 0x10;
      if (W_x2 < i21 - i33) {
        i33 = i21 - W_x2;
      }
      if (i21 - i35 < W_x1) {
        i35 = i21 - W_x1;
      }
      stk_5c = (int)X87_FIST32(((((float80)i33 / arg8) * f11 -
                             ((float)stk_50 / arg9) * f14) * 65536.0) / (float80)i31) +
                 i7 * 0x10000;
      i32 = i8 * 0x10000 +
               (int)X87_FIST32(((((float80)i33 / arg8) * f14 +
                           ((float)stk_50 / arg9) * f11) * 65536.0) / (float80)i34);
      stk_38 = (uint16_t *)
                 (i26 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_50 + i22) * 4) +
                 (i21 - i33) * 2);
      i30 = (i35 - i33) + 1;
      i9 = i35 - i33;
      i28 = i2 * i30 + i32;
      for (i30 = stk_5c + i1 * i30;
          (SBORROW4(i35,i33) == i9 < 0 &&
          ((((i6 <= i28 >> 0x10 || (i5 <= i30 >> 0x10)) || (i28 >> 0x10 < 0)) ||
           (i30 >> 0x10 < 0)))); i30 = i30 - i1) {
        i35 = i35 + -1;
        i28 = i28 - i2;
        i9 = i35 - i33;
      }
      for (; (i33 <= i35 &&
             (((i6 <= i32 >> 0x10 || (i5 <= stk_5c >> 0x10)) ||
              ((i32 >> 0x10 < 0 || (stk_5c >> 0x10 < 0)))))); stk_5c = stk_5c + i1) {
        stk_38 = stk_38 + -1;
        i33 = i33 + 1;
        i32 = i32 + i2;
      }
      i33 = (i35 - i33) + 1;
      if (0 < i33) {
        do {
          b3 = *(uint8_t *)((stk_5c >> 0x10) + i25 + *(int *)(i4 + (i32 >> 0x10) * 4));
          if (b3 != 0) {
            *stk_38 = *(uint16_t *)((int)sprite3 + (uint32_t)b3 * 2 + 0x5c);
          }
          stk_5c = stk_5c + i1;
          stk_38 = stk_38 + -1;
          i32 = i32 + i2;
          i33 = i33 + -1;
        } while (i33 != 0);
      }
      i33 = stk_74;
      if (stk_50 < i29) {
        i33 = -stk_70;
      }
      stk_60 = stk_60 + i33;
      i33 = stk_74;
      if (i24 <= stk_50) {
        i33 = -stk_70;
      }
      stk_64 = stk_64 + i33;
      stk_50 = stk_50 + 1;
    } while (stk_50 <= stk_90);
  }
  u23 = SpriteDecompUnlockData();
  return BITS_I2F(u23);
}
#undef stk_90
#undef stk_8c
#undef stk_88
#undef stk_84
#undef stk_80
#undef stk_74
#undef stk_70
#undef stk_64
#undef stk_60
#undef stk_5c
#undef stk_50
#undef stk_38
#undef stk_20

/* W_PutSpriteShadow8to16 @ 0x08062250, 477 bytes
 *
 * Draws the shape of sprite `index` (a shadow) of a sprite array into the
 * current drawing buffer, in a solid colour. Clipped to the window set by
 * W_Define. This is the pixel loop: it reads the 8-bit sprite rows through
 * the sprite's palette converted to 16-bit colours and writes 16-bit pixels.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *   arg5         uint16_t
 *
 * Calls: SpriteArrayAccess, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteDecompUnlockData
 * Called by: W_PutSpriteShadow
 *
 * Elecbyte file: src/lib/spr16-lb.c
 */
void W_PutSpriteShadow8to16(int *sprites,int index,int x,int y,uint16_t arg5)

{
  int *sprite;
  int sprite2;
  int i3;
  int i4;
  uint16_t *pu5;
  char *pc6;
  int i7;
  int i8;
  int i9;
  int *pi10;
  int stk_38;
  int stk_34;
  int stk_30;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_34 = 0;
  i7 = y - sprite[3];
  stk_38 = 0;
  i9 = x - sprite[2];
  if ((((i7 <= W_y2) && (W_y1 < sprite[1] + i7)) && (i9 <= W_x2)) &&
     (W_x1 < *sprite + i9)) {
    stk_30 = i7;
    if (i7 < W_y1) {
      stk_30 = W_y1;
      stk_34 = W_y1 - i7;
    }
    i7 = sprite[1] + i7 + -1;
    if (W_y2 < i7) {
      i7 = W_y2;
    }
    i8 = i9;
    if (i9 < W_x1) {
      stk_38 = W_x1 - i9;
      i8 = W_x1;
    }
    i9 = *sprite + i9 + -1;
    if (W_x2 < i9) {
      i9 = W_x2;
    }
    i9 = (i9 - i8) + 1;
    i7 = (i7 - stk_30) + 1;
    if (((0 < i9) && (0 < i7)) &&
       (i3 = SpriteDecompGetAndLockData(sprites,index), i3 != 0)) {
      i4 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      if (0 < i7) {
        pi10 = (int *)(stk_30 * 4 + *(int *)(sprite2 + 0x2c));
        sprite = (int *)(stk_34 * 4 + sprite[0xb]);
        do {
          pc6 = (char *)(stk_38 + i3 + *sprite);
          pu5 = (uint16_t *)(i4 + *pi10 + i8 * 2);
          for (sprite2 = i9; sprite2 != 0; sprite2 = sprite2 + -1) {
            if (*pc6 != '\0') {
              *pu5 = arg5;
            }
            pu5 = pu5 + 1;
            pc6 = pc6 + 1;
          }
          pi10 = pi10 + 1;
          sprite = sprite + 1;
          i7 = i7 + -1;
        } while (i7 != 0);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteShadow16 @ 0x08062430, 1 bytes
 *
 * Draws the shape of sprite `index` (a shadow) of a sprite array into the
 * current drawing buffer, in a solid colour. Clipped to the window set by
 * W_Define. Variant for 16-bit sprites; empty in this build (only 8-bit
 * sprites exist).
 *
 * Called by: W_PutSpriteShadow
 *
 * Elecbyte file: src/lib/spr16-lb.c
 */
void W_PutSpriteShadow16(void)

{
  return;
}

