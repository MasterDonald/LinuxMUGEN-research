/*
 * spr16sub.c -- 16-bit subtractive blitters
 * Pixel loops that draw 8-bit sprites and shadows onto 16-bit buffers with
 * subtractive blending, unscaled, scaled and rotated.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/spr16sub.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* W_PutSpriteTransSub8to16 @ 0x08072060, 665 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended subtractively (colour 0 transparent). Clipped to the window set by
 * W_Define. This is the pixel loop: it reads the 8-bit sprite rows through
 * the sprite's palette converted to 16-bit colours and writes 16-bit pixels.
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
 * Called by: W_PutSpriteTransSub, W_ScaleSpriteTransSub8to16
 *
 * Elecbyte file: src/lib/spr16sub.c
 */
void W_PutSpriteTransSub8to16(int *sprites,int index,int x,int y)

{
  int *sprite;
  int sprite2;
  int i3;
  int i4;
  int *sprite3;
  uint8_t *pb6;
  int i7;
  uint32_t u8;
  int i9;
  int i10;
  int i11;
  int i12;
  int i13;
  uint32_t u14;
  uint16_t *pu15;
  int stk_48;
  int stk_44;
  int stk_40;
  int stk_3c;
  int stk_30;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_40 = 0;
  i10 = y - sprite[3];
  stk_48 = 0;
  i12 = x - sprite[2];
  if ((((i10 <= W_y2) && (W_y1 < sprite[1] + i10)) && (i12 <= W_x2)) &&
     (W_x1 < *sprite + i12)) {
    stk_3c = i10;
    if (i10 < W_y1) {
      stk_3c = W_y1;
      stk_40 = W_y1 - i10;
    }
    i10 = sprite[1] + i10 + -1;
    if (W_y2 < i10) {
      i10 = W_y2;
    }
    stk_44 = i12;
    if (i12 < W_x1) {
      stk_44 = W_x1;
      stk_48 = W_x1 - i12;
    }
    i12 = *sprite + i12 + -1;
    if (W_x2 < i12) {
      i12 = W_x2;
    }
    i12 = (i12 - stk_44) + 1;
    i10 = (i10 - stk_3c) + 1;
    if (((0 < i12) && (0 < i10)) &&
       (i3 = SpriteDecompGetAndLockData(sprites,index), i3 != 0)) {
      i4 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      sprite3 = (int *)sprites[5];
      if (sprite3 == (int *)0x0) {
        sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
      }
      else {
        EBPalUpdate(sprite3);
      }
      stk_30 = 0;
      if (0 < i10) {
        do {
          pb6 = (uint8_t *)(i3 + *(int *)(sprite[0xb] + (stk_40 + stk_30) * 4) + stk_48);
          pu15 = (uint16_t *)
                    (i4 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_3c + stk_30) * 4) +
                    stk_44 * 2);
          for (i13 = i12; i13 != 0; i13 = i13 + -1) {
            if (*pb6 != 0) {
              u14 = (uint32_t)*(short *)((int)sprite3 + (uint32_t)*pb6 * 2 + 0x5c);
              u8 = (uint32_t)*pu15;
              i7 = (u8 & 0xf800) - (u14 & 0xf800);
              i11 = (u8 & 0x7e0) - (u14 & 0x7e0);
              i9 = (u8 & 0x1f) - (u14 & 0x1f);
              *pu15 = (uint16_t)i7 & -(short)(i7 >> 0x1f) - 1U |
                         (uint16_t)i11 & -(short)(i11 >> 0x1f) - 1U |
                         (uint16_t)i9 & 0xffffU - (short)(i9 >> 0x1f);
            }
            pu15 = pu15 + 1;
            pb6 = pb6 + 1;
          }
          stk_30 = stk_30 + 1;
        } while (stk_30 < i10);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteTransSubMirH8to16 @ 0x08072300, 685 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended subtractively (colour 0 transparent), mirrored horizontally.
 * Clipped to the window set by W_Define. This is the pixel loop: it reads
 * the 8-bit sprite rows through the sprite's palette converted to 16-bit
 * colours and writes 16-bit pixels.
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
 * Called by: W_PutSpriteTransSubMirH, W_ScaleSpriteTransSubMirH8to16
 *
 * Elecbyte file: src/lib/spr16sub.c
 */
void W_PutSpriteTransSubMirH8to16(int *sprites,int index,int x,int y)

{
  int i1;
  int *sprite;
  int sprite2;
  int i4;
  int i5;
  int i6;
  int *sprite3;
  int i8;
  uint32_t u9;
  int i10;
  int i11;
  int i12;
  int i13;
  uint32_t u14;
  uint16_t *pu15;
  int stk_48;
  int stk_44;
  int stk_40;
  int stk_3c;
  int stk_30;
  uint8_t *stk_2c;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  i1 = *sprite;
  stk_40 = 0;
  i4 = (sprite[2] - i1) + 1 + x;
  i11 = y - sprite[3];
  stk_48 = 0;
  if ((((i11 <= W_y2) && (W_y1 < sprite[1] + i11)) && (i4 <= W_x2)) &&
     (W_x1 < i1 + i4)) {
    stk_3c = i11;
    if (i11 < W_y1) {
      stk_3c = W_y1;
      stk_40 = W_y1 - i11;
    }
    i11 = sprite[1] + i11 + -1;
    if (W_y2 < i11) {
      i11 = W_y2;
    }
    stk_44 = i4;
    if (i4 < W_x1) {
      stk_44 = W_x1;
      stk_48 = W_x1 - i4;
    }
    i4 = i1 + i4 + -1;
    if (W_x2 < i4) {
      i4 = W_x2;
    }
    i4 = (i4 - stk_44) + 1;
    i11 = (i11 - stk_3c) + 1;
    if (((0 < i4) && (0 < i11)) &&
       (i5 = SpriteDecompGetAndLockData(sprites,index), i5 != 0)) {
      i6 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      sprite3 = (int *)sprites[5];
      if (sprite3 == (int *)0x0) {
        sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
      }
      else {
        EBPalUpdate(sprite3);
      }
      stk_30 = 0;
      if (0 < i11) {
        do {
          stk_2c = (uint8_t *)((i5 + *(int *)(sprite[0xb] + (stk_40 + stk_30) * 4) + i1) -
                             stk_48);
          pu15 = (uint16_t *)
                    (i6 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_3c + stk_30) * 4) +
                    stk_44 * 2);
          for (i13 = i4; i13 != 0; i13 = i13 + -1) {
            stk_2c = stk_2c + -1;
            if (*stk_2c != 0) {
              u9 = (uint32_t)*pu15;
              u14 = (uint32_t)*(short *)((int)sprite3 + (uint32_t)*stk_2c * 2 + 0x5c);
              i8 = (u9 & 0xf800) - (u14 & 0xf800);
              i12 = (u9 & 0x7e0) - (u14 & 0x7e0);
              i10 = (u9 & 0x1f) - (u14 & 0x1f);
              *pu15 = (uint16_t)i8 & -(short)(i8 >> 0x1f) - 1U |
                         (uint16_t)i12 & -(short)(i12 >> 0x1f) - 1U |
                         (uint16_t)i10 & -(short)(i10 >> 0x1f) - 1U;
            }
            pu15 = pu15 + 1;
          }
          stk_30 = stk_30 + 1;
        } while (stk_30 < i11);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteTransSubMirV8to16 @ 0x080725b0, 685 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended subtractively (colour 0 transparent), mirrored vertically. Clipped
 * to the window set by W_Define. This is the pixel loop: it reads the 8-bit
 * sprite rows through the sprite's palette converted to 16-bit colours and
 * writes 16-bit pixels.
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
 * Called by: W_PutSpriteTransSubMirV, W_ScaleSpriteTransSubMirV8to16
 *
 * Elecbyte file: src/lib/spr16sub.c
 */
void W_PutSpriteTransSubMirV8to16(int *sprites,int index,int x,int y)

{
  int i1;
  int *sprite;
  int sprite2;
  int i4;
  int i5;
  int *sprite3;
  uint8_t *pb7;
  int i8;
  int i9;
  uint32_t u10;
  int i11;
  int i12;
  int i13;
  int i14;
  uint32_t u15;
  uint16_t *pu16;
  int stk_48;
  int stk_44;
  int stk_40;
  int stk_3c;
  int stk_30;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_40 = 0;
  i1 = sprite[1];
  i13 = x - sprite[2];
  i9 = (sprite[3] - i1) + 1 + y;
  stk_48 = 0;
  if ((((i9 <= W_y2) && (W_y1 < i1 + i9)) && (i13 <= W_x2)) && (W_x1 < *sprite + i13)
     ) {
    stk_3c = i9;
    if (i9 < W_y1) {
      stk_3c = W_y1;
      stk_40 = W_y1 - i9;
    }
    i9 = i1 + i9 + -1;
    if (W_y2 < i9) {
      i9 = W_y2;
    }
    stk_44 = i13;
    if (i13 < W_x1) {
      stk_44 = W_x1;
      stk_48 = W_x1 - i13;
    }
    i13 = *sprite + i13 + -1;
    if (W_x2 < i13) {
      i13 = W_x2;
    }
    i13 = (i13 - stk_44) + 1;
    i9 = (i9 - stk_3c) + 1;
    if (((0 < i13) && (0 < i9)) &&
       (i4 = SpriteDecompGetAndLockData(sprites,index), i4 != 0)) {
      i5 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      sprite3 = (int *)sprites[5];
      if (sprite3 == (int *)0x0) {
        sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
      }
      else {
        EBPalUpdate(sprite3);
      }
      stk_30 = 0;
      if (0 < i9) {
        do {
          pb7 = (uint8_t *)(i4 + *(int *)(sprite[0xb] + -4 + ((i1 - stk_40) - stk_30) * 4)
                           + stk_48);
          pu16 = (uint16_t *)
                    (i5 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_3c + stk_30) * 4) +
                    stk_44 * 2);
          for (i14 = i13; i14 != 0; i14 = i14 + -1) {
            if (*pb7 != 0) {
              u15 = (uint32_t)*(short *)((int)sprite3 + (uint32_t)*pb7 * 2 + 0x5c);
              u10 = (uint32_t)*pu16;
              i8 = (u10 & 0xf800) - (u15 & 0xf800);
              i12 = (u10 & 0x7e0) - (u15 & 0x7e0);
              i11 = (u10 & 0x1f) - (u15 & 0x1f);
              *pu16 = (uint16_t)i8 & -(short)(i8 >> 0x1f) - 1U |
                         (uint16_t)i12 & -(short)(i12 >> 0x1f) - 1U |
                         (uint16_t)i11 & -(short)(i11 >> 0x1f) - 1U;
            }
            pu16 = pu16 + 1;
            pb7 = pb7 + 1;
          }
          stk_30 = stk_30 + 1;
        } while (stk_30 < i9);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteTransSubMirHV8to16 @ 0x08072860, 713 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended subtractively (colour 0 transparent), mirrored horizontally and
 * vertically. Clipped to the window set by W_Define. This is the pixel loop:
 * it reads the 8-bit sprite rows through the sprite's palette converted to
 * 16-bit colours and writes 16-bit pixels.
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
 * Called by: W_PutSpriteTransSubMirHV, W_ScaleSpriteTransSubMirHV8to16
 *
 * Elecbyte file: src/lib/spr16sub.c
 */
void W_PutSpriteTransSubMirHV8to16(int *sprites,int index,int x,int y)

{
  int i1;
  int i2;
  int *sprite;
  int sprite2;
  int i5;
  int i6;
  int i7;
  int *sprite3;
  int i9;
  int i10;
  uint32_t u11;
  int i12;
  int i13;
  int i14;
  uint32_t u15;
  uint16_t *pu16;
  int stk_48;
  int stk_44;
  int stk_40;
  int stk_3c;
  int stk_30;
  uint8_t *stk_2c;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  i1 = *sprite;
  i2 = sprite[1];
  stk_40 = 0;
  i5 = (sprite[2] - i1) + 1 + x;
  stk_48 = 0;
  i10 = (sprite[3] - i2) + 1 + y;
  if ((((i10 <= W_y2) && (W_y1 < i2 + i10)) && (i5 <= W_x2)) && (W_x1 < i1 + i5))
  {
    stk_3c = i10;
    if (i10 < W_y1) {
      stk_3c = W_y1;
      stk_40 = W_y1 - i10;
    }
    i10 = i2 + i10 + -1;
    if (W_y2 < i10) {
      i10 = W_y2;
    }
    stk_44 = i5;
    if (i5 < W_x1) {
      stk_44 = W_x1;
      stk_48 = W_x1 - i5;
    }
    i5 = i1 + i5 + -1;
    if (W_x2 < i5) {
      i5 = W_x2;
    }
    i5 = (i5 - stk_44) + 1;
    i10 = (i10 - stk_3c) + 1;
    if (((0 < i5) && (0 < i10)) &&
       (i6 = SpriteDecompGetAndLockData(sprites,index), i6 != 0)) {
      i7 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      sprite3 = (int *)sprites[5];
      if (sprite3 == (int *)0x0) {
        sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
      }
      else {
        EBPalUpdate(sprite3);
      }
      stk_30 = 0;
      if (0 < i10) {
        do {
          stk_2c = (uint8_t *)((i6 + *(int *)(sprite[0xb] + -4 +
                                               ((i2 - stk_40) - stk_30) * 4) + i1) -
                             stk_48);
          pu16 = (uint16_t *)
                    (i7 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_3c + stk_30) * 4) +
                    stk_44 * 2);
          for (i14 = i5; i14 != 0; i14 = i14 + -1) {
            stk_2c = stk_2c + -1;
            if (*stk_2c != 0) {
              u15 = (uint32_t)*(short *)((int)sprite3 + (uint32_t)*stk_2c * 2 + 0x5c);
              u11 = (uint32_t)*pu16;
              i9 = (u11 & 0xf800) - (u15 & 0xf800);
              i13 = (u11 & 0x7e0) - (u15 & 0x7e0);
              i12 = (u11 & 0x1f) - (u15 & 0x1f);
              *pu16 = (uint16_t)i9 & -(short)(i9 >> 0x1f) - 1U |
                         (uint16_t)i13 & -(short)(i13 >> 0x1f) - 1U |
                         (uint16_t)i12 & -(short)(i12 >> 0x1f) - 1U;
            }
            pu16 = pu16 + 1;
          }
          stk_30 = stk_30 + 1;
        } while (stk_30 < i10);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_ScaleSpriteTransSub8to16 @ 0x08072b30, 2421 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended subtractively (colour 0 transparent). Clipped to the
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
 *        SpriteDecompUnlockData, W_PutSpriteTransSub8to16
 * Called by: W_ScaleSpriteTransSub
 *
 * Elecbyte file: src/lib/spr16sub.c
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 8 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleSpriteTransSub8to16
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
  int i11;
  int *sprite3;
  uint8_t *pb13;
  int i14;
  int i15;
  int i16;
  uint32_t *pu17;
  uint32_t u18;
  uint32_t u19;
  uint32_t u20;
  int stk_144;
  int stk_100;
  int stk_fc;
  int stk_f8;
  int stk_f4;
  uint32_t stk_f0;
  uint32_t stk_ec;
  int stk_d8;
  uint32_t stk_54;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_f8 = 0;
  stk_100 = 0;
  if ((0.0 < arg5) && (0.0 < arg6)) {
    i2 = *sprite;
    i10 = sprite[1];
    if ((((double)0.001) <= ABS((float80)i2 - arg5)) || (((double)0.001) <= ABS((float80)i10 - arg6))) {
      f3 = x - ((float80)sprite[2] * arg5) / (float80)i2;
      f4 = y - ((float80)sprite[3] * arg6) / (float80)i10;
      if ((((f4 <= (float)W_y2) && ((float)W_y1 < (f4 + arg6) - 0.5)) &&
          (f3 <= (float)W_x2)) && ((float)W_x1 < (f3 + arg5) - 0.5)) {
        stk_f4 = (int)X87_FIST32(X87_FLOOR(f4));
        f5 = (float)stk_f4;
        if (f4 <= f5) {
          stk_ec = 0;
        }
        else {
          if ((float)stk_f4 < f4 - 0.5) {
            stk_f4 = stk_f4 + 1;
            f5 = (float)stk_f4;
          }
          stk_54 = (uint32_t)(int64_t)X87_FIST64((((float80)i10 * (f5 - f4)) / arg6) * 65536.0);
          stk_ec = stk_54;
        }
        if (stk_f4 < W_y1) {
          i8 = W_y1 - stk_f4;
          stk_f4 = W_y1;
          stk_54 = (uint32_t)(int64_t)X87_FIST64(((float)(i8 * i10) / arg6) * 65536.0);
          stk_ec = stk_ec + stk_54;
        }
        i8 = (int)X87_FIST32(X87_FLOOR((f4 + arg6) - 0.5));
        if (W_y2 < i8) {
          i8 = W_y2;
        }
        if (i8 - stk_f4 != -1 && -1 < (i8 - stk_f4) + 1) {
          stk_fc = (int)X87_FIST32(X87_FLOOR(f3));
          f4 = (float)stk_fc;
          if (f3 <= f4) {
            stk_f0 = 0;
          }
          else {
            if ((float)stk_fc < f3 - 0.5) {
              stk_fc = stk_fc + 1;
              f4 = (float)stk_fc;
            }
            stk_54 = (uint32_t)(int64_t)X87_FIST64((((f4 - f3) * (float80)i2) / arg5) * 65536.0)
            ;
            stk_f0 = stk_54;
          }
          if (f3 < (float)W_x1) {
            i9 = W_x1 - stk_fc;
            stk_fc = W_x1;
            stk_144 = (int)(int64_t)X87_FIST64(((float)(i9 * i2) / arg5) * 65536.0);
            stk_f0 = stk_f0 + stk_144;
          }
          i9 = (int)X87_FIST32(X87_FLOOR((f3 + arg5) - 0.5));
          if (W_x2 < i9) {
            i9 = W_x2;
          }
          stk_54 = (uint32_t)(int64_t)X87_FIST64((float)(i2 << 0x10) / arg5);
          i2 = (int)X87_FIST32((float)(i10 << 0x10) / arg6);
          for (; ((int)stk_f0 < 0 && (stk_fc <= i9)); stk_fc = stk_fc + 1) {
            stk_f0 = stk_f0 + stk_54;
          }
          i10 = (int)stk_f0 >> 0x10;
          if (i10 != 0) {
            stk_f0 = stk_f0 & 0xffff;
            stk_100 = i10;
          }
          for (; ((int)stk_ec < 0 && (stk_f4 <= i8)); stk_f4 = stk_f4 + 1) {
            stk_ec = stk_ec + i2;
          }
          i10 = (int)stk_ec >> 0x10;
          if (i10 != 0) {
            stk_ec = stk_ec & 0xffff;
            stk_f8 = i10;
          }
          i10 = (i9 - stk_fc) + 1;
          i8 = (i8 - stk_f4) + 1;
          if ((0 < i10) && (0 < i8)) {
            i9 = SpriteDecompGetAndLockData(sprites,index);
            if (i9 != 0) {
              i11 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              sprite3 = (int *)sprites[5];
              if (sprite3 == (int *)0x0) {
                sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
              }
              else {
                EBPalUpdate(sprite3);
              }
              stk_d8 = 0;
              if (0 < i8) {
                do {
                  pb13 = (uint8_t *)(i9 + *(int *)(sprite[0xb] +
                                                     (((int)stk_ec >> 0x10) + stk_f8) * 4) +
                                    stk_100);
                  pu17 = (uint32_t *)(stk_fc * 2 +
                                    i11 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                     (stk_f4 + stk_d8) * 4));
                  u20 = stk_f0;
                  for (i1 = i10; i1 != 0; i1 = i1 + -1) {
                    if (*pb13 != 0) {
                      u18 = (uint32_t)*(short *)((int)sprite3 + (uint32_t)*pb13 * 2 + 0x5c);
                      u19 = *pu17;
                      i14 = (u19 & 0xf800) - (u18 & 0xf800);
                      i16 = (u19 & 0x7e0) - (u18 & 0x7e0);
                      i15 = (u19 & 0x1f) - (u18 & 0x1f);
                      *(uint16_t *)pu17 =
                           (uint16_t)i14 & -(short)(i14 >> 0x1f) - 1U |
                           (uint16_t)i16 & -(short)(i16 >> 0x1f) - 1U |
                           (uint16_t)i15 & -(short)(i15 >> 0x1f) - 1U;
                    }
                    u19 = u20 + stk_54;
                    pu17 = (uint32_t *)((int)pu17 + 2);
                    u20 = u19 & 0xffff;
                    pb13 = pb13 + (u19 >> 0x10);
                  }
                  stk_d8 = stk_d8 + 1;
                  stk_ec = stk_ec + i2;
                } while (stk_d8 < i8);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteTransSub8to16(sprites,index,(int)X87_FIST32(x),(int)X87_FIST32(y));
    }
  }
  return;
}

/* W_ScaleSpriteTransSubMirH8to16 @ 0x080734b0, 2429 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended subtractively (colour 0 transparent), mirrored
 * horizontally. Clipped to the window set by W_Define. This is the pixel
 * loop: it reads the 8-bit sprite rows through the sprite's palette
 * converted to 16-bit colours and writes 16-bit pixels.
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
 *        SpriteDecompUnlockData, W_PutSpriteTransSubMirH8to16
 * Called by: W_ScaleSpriteTransSubMirH
 *
 * Elecbyte file: src/lib/spr16sub.c
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 7 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleSpriteTransSubMirH8to16
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
  int i12;
  int *sprite3;
  uint8_t *pb14;
  int i15;
  int i16;
  int i17;
  uint32_t *pu18;
  uint32_t u19;
  uint32_t u20;
  uint32_t u21;
  int stk_144;
  int stk_100;
  int stk_fc;
  int stk_f8;
  int stk_f4;
  uint32_t stk_f0;
  uint32_t stk_ec;
  int stk_d8;
  uint32_t stk_54;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_f8 = 0;
  stk_100 = 0;
  if ((0.0 < arg5) && (0.0 < arg6)) {
    i2 = *sprite;
    i3 = sprite[1];
    if ((((double)0.001) <= ABS((float80)i2 - arg5)) || (((double)0.001) <= ABS((float80)i3 - arg6))) {
      f4 = x - ((float)((i2 - sprite[2]) + -1) * arg5) / (float80)i2;
      f5 = y - ((float80)sprite[3] * arg6) / (float80)i3;
      if ((((f5 <= (float)W_y2) && ((float)W_y1 < (f5 + arg6) - 0.5)) &&
          (f4 <= (float)W_x2)) && ((float)W_x1 < (f4 + arg5) - 0.5)) {
        stk_f4 = (int)X87_FIST32(X87_FLOOR(f5));
        f6 = (float)stk_f4;
        if (f5 <= f6) {
          stk_ec = 0;
        }
        else {
          if ((float)stk_f4 < f5 - 0.5) {
            stk_f4 = stk_f4 + 1;
            f6 = (float)stk_f4;
          }
          stk_54 = (uint32_t)(int64_t)X87_FIST64((((float80)i3 * (f6 - f5)) / arg6) * 65536.0);
          stk_ec = stk_54;
        }
        if (stk_f4 < W_y1) {
          i9 = W_y1 - stk_f4;
          stk_f4 = W_y1;
          stk_54 = (uint32_t)(int64_t)X87_FIST64(((float)(i9 * i3) / arg6) * 65536.0);
          stk_ec = stk_ec + stk_54;
        }
        i9 = (int)X87_FIST32(X87_FLOOR((f5 + arg6) - 0.5));
        if (W_y2 < i9) {
          i9 = W_y2;
        }
        if (i9 - stk_f4 != -1 && -1 < (i9 - stk_f4) + 1) {
          stk_fc = (int)X87_FIST32(X87_FLOOR(f4));
          f5 = (float)stk_fc;
          if (f4 <= f5) {
            stk_f0 = 0;
          }
          else {
            if ((float)stk_fc < f4 - 0.5) {
              stk_fc = stk_fc + 1;
              f5 = (float)stk_fc;
            }
            stk_54 = (uint32_t)(int64_t)X87_FIST64((((f5 - f4) * (float80)i2) / arg5) * 65536.0)
            ;
            stk_f0 = stk_54;
          }
          if (f4 < (float)W_x1) {
            i10 = W_x1 - stk_fc;
            stk_fc = W_x1;
            stk_144 = (int)(int64_t)X87_FIST64(((float)(i10 * i2) / arg5) * 65536.0);
            stk_f0 = stk_f0 + stk_144;
          }
          i10 = (int)X87_FIST32(X87_FLOOR((f4 + arg5) - 0.5));
          if (W_x2 < i10) {
            i10 = W_x2;
          }
          stk_144 = (int)(int64_t)X87_FIST64((float)(i2 << 0x10) / arg5);
          i3 = (int)X87_FIST32((float)(i3 << 0x10) / arg6);
          for (; ((int)stk_f0 < 0 && (stk_fc <= i10)); stk_fc = stk_fc + 1) {
            stk_f0 = stk_f0 + stk_144;
          }
          i11 = (int)stk_f0 >> 0x10;
          if (i11 != 0) {
            stk_f0 = stk_f0 & 0xffff;
            stk_100 = i11;
          }
          for (; ((int)stk_ec < 0 && (stk_f4 <= i9)); stk_f4 = stk_f4 + 1) {
            stk_ec = stk_ec + i3;
          }
          i11 = (int)stk_ec >> 0x10;
          if (i11 != 0) {
            stk_ec = stk_ec & 0xffff;
            stk_f8 = i11;
          }
          i10 = (i10 - stk_fc) + 1;
          i9 = (i9 - stk_f4) + 1;
          if ((0 < i10) && (0 < i9)) {
            i11 = SpriteDecompGetAndLockData(sprites,index);
            if (i11 != 0) {
              i12 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              sprite3 = (int *)sprites[5];
              if (sprite3 == (int *)0x0) {
                sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
              }
              else {
                EBPalUpdate(sprite3);
              }
              stk_d8 = 0;
              if (0 < i9) {
                do {
                  pb14 = (uint8_t *)(((i11 + *(int *)(sprite[0xb] +
                                                        (((int)stk_ec >> 0x10) + stk_f8) * 4) +
                                      i2) - stk_100) + -1);
                  pu18 = (uint32_t *)(stk_fc * 2 +
                                    i12 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                     (stk_f4 + stk_d8) * 4));
                  u21 = stk_f0;
                  for (i1 = i10; i1 != 0; i1 = i1 + -1) {
                    if (*pb14 != 0) {
                      u19 = (uint32_t)*(short *)((int)sprite3 + (uint32_t)*pb14 * 2 + 0x5c);
                      u20 = *pu18;
                      i15 = (u20 & 0xf800) - (u19 & 0xf800);
                      i17 = (u20 & 0x7e0) - (u19 & 0x7e0);
                      i16 = (u20 & 0x1f) - (u19 & 0x1f);
                      *(uint16_t *)pu18 =
                           (uint16_t)i15 & -(short)(i15 >> 0x1f) - 1U |
                           (uint16_t)i17 & -(short)(i17 >> 0x1f) - 1U |
                           (uint16_t)i16 & -(short)(i16 >> 0x1f) - 1U;
                    }
                    u20 = u21 + stk_144;
                    pu18 = (uint32_t *)((int)pu18 + 2);
                    u21 = u20 & 0xffff;
                    pb14 = pb14 + -(u20 >> 0x10);
                  }
                  stk_d8 = stk_d8 + 1;
                  stk_ec = stk_ec + i3;
                } while (stk_d8 < i9);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteTransSubMirH8to16(sprites,index,(int)X87_FIST32(x),(int)X87_FIST32(y));
    }
  }
  return;
}

/* W_ScaleSpriteTransSubMirV8to16 @ 0x08073e30, 2445 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended subtractively (colour 0 transparent), mirrored vertically.
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
 *        SpriteDecompUnlockData, W_PutSpriteTransSubMirV8to16
 * Called by: W_ScaleSpriteTransSubMirV
 *
 * Elecbyte file: src/lib/spr16sub.c
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 7 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleSpriteTransSubMirV8to16
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
  int i12;
  int *sprite3;
  uint8_t *pb14;
  int i15;
  int i16;
  int i17;
  uint32_t *pu18;
  uint32_t u19;
  uint32_t u20;
  uint32_t u21;
  int stk_144;
  int stk_100;
  int stk_fc;
  int stk_f8;
  int stk_f4;
  uint32_t stk_f0;
  uint32_t stk_ec;
  int stk_d8;
  uint32_t stk_54;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_f8 = 0;
  stk_100 = 0;
  if ((0.0 < arg5) && (0.0 < arg6)) {
    i2 = *sprite;
    i3 = sprite[1];
    if ((((double)0.001) <= ABS((float80)i2 - arg5)) || (((double)0.001) <= ABS((float80)i3 - arg6))) {
      f4 = x - ((float80)sprite[2] * arg5) / (float80)i2;
      f5 = y - ((float)((i3 - sprite[3]) + -1) * arg6) / (float80)i3;
      if ((((f5 <= (float)W_y2) && ((float)W_y1 < (f5 + arg6) - 0.5)) &&
          (f4 <= (float)W_x2)) && ((float)W_x1 < (f4 + arg5) - 0.5)) {
        stk_f4 = (int)X87_FIST32(X87_FLOOR(f5));
        f6 = (float)stk_f4;
        if (f5 <= f6) {
          stk_ec = 0;
        }
        else {
          if ((float)stk_f4 < f5 - 0.5) {
            stk_f4 = stk_f4 + 1;
            f6 = (float)stk_f4;
          }
          stk_54 = (uint32_t)(int64_t)X87_FIST64((((float80)i3 * (f6 - f5)) / arg6) * 65536.0);
          stk_ec = stk_54;
        }
        if (stk_f4 < W_y1) {
          i9 = W_y1 - stk_f4;
          stk_f4 = W_y1;
          stk_54 = (uint32_t)(int64_t)X87_FIST64(((float)(i9 * i3) / arg6) * 65536.0);
          stk_ec = stk_ec + stk_54;
        }
        i9 = (int)X87_FIST32(X87_FLOOR((f5 + arg6) - 0.5));
        if (W_y2 < i9) {
          i9 = W_y2;
        }
        if (i9 - stk_f4 != -1 && -1 < (i9 - stk_f4) + 1) {
          stk_fc = (int)X87_FIST32(X87_FLOOR(f4));
          f5 = (float)stk_fc;
          if (f4 <= f5) {
            stk_f0 = 0;
          }
          else {
            if ((float)stk_fc < f4 - 0.5) {
              stk_fc = stk_fc + 1;
              f5 = (float)stk_fc;
            }
            stk_54 = (uint32_t)(int64_t)X87_FIST64((((f5 - f4) * (float80)i2) / arg5) * 65536.0)
            ;
            stk_f0 = stk_54;
          }
          if (f4 < (float)W_x1) {
            i10 = W_x1 - stk_fc;
            stk_fc = W_x1;
            stk_144 = (int)(int64_t)X87_FIST64(((float)(i10 * i2) / arg5) * 65536.0);
            stk_f0 = stk_f0 + stk_144;
          }
          i10 = (int)X87_FIST32(X87_FLOOR((f4 + arg5) - 0.5));
          if (W_x2 < i10) {
            i10 = W_x2;
          }
          stk_54 = (uint32_t)(int64_t)X87_FIST64((float)(i2 << 0x10) / arg5);
          i2 = (int)X87_FIST32((float)(i3 << 0x10) / arg6);
          for (; ((int)stk_f0 < 0 && (stk_fc <= i10)); stk_fc = stk_fc + 1) {
            stk_f0 = stk_f0 + stk_54;
          }
          i11 = (int)stk_f0 >> 0x10;
          if (i11 != 0) {
            stk_f0 = stk_f0 & 0xffff;
            stk_100 = i11;
          }
          for (; ((int)stk_ec < 0 && (stk_f4 <= i9)); stk_f4 = stk_f4 + 1) {
            stk_ec = stk_ec + i2;
          }
          i11 = (int)stk_ec >> 0x10;
          if (i11 != 0) {
            stk_ec = stk_ec & 0xffff;
            stk_f8 = i11;
          }
          i10 = (i10 - stk_fc) + 1;
          i9 = (i9 - stk_f4) + 1;
          if ((0 < i10) && (0 < i9)) {
            i11 = SpriteDecompGetAndLockData(sprites,index);
            if (i11 != 0) {
              i12 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              sprite3 = (int *)sprites[5];
              if (sprite3 == (int *)0x0) {
                sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
              }
              else {
                EBPalUpdate(sprite3);
              }
              stk_d8 = 0;
              if (0 < i9) {
                do {
                  pb14 = (uint8_t *)(i11 + *(int *)(sprite[0xb] + -4 +
                                                      ((i3 - stk_f8) - ((int)stk_ec >> 0x10))
                                                      * 4) + stk_100);
                  pu18 = (uint32_t *)(stk_fc * 2 +
                                    i12 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                     (stk_f4 + stk_d8) * 4));
                  u21 = stk_f0;
                  for (i1 = i10; i1 != 0; i1 = i1 + -1) {
                    if (*pb14 != 0) {
                      u20 = *pu18;
                      u19 = (uint32_t)*(short *)((int)sprite3 + (uint32_t)*pb14 * 2 + 0x5c);
                      i15 = (u20 & 0xf800) - (u19 & 0xf800);
                      i17 = (u20 & 0x7e0) - (u19 & 0x7e0);
                      i16 = (u20 & 0x1f) - (u19 & 0x1f);
                      *(uint16_t *)pu18 =
                           (uint16_t)i15 & -(short)(i15 >> 0x1f) - 1U |
                           (uint16_t)i17 & -(short)(i17 >> 0x1f) - 1U |
                           (uint16_t)i16 & -(short)(i16 >> 0x1f) - 1U;
                    }
                    u20 = u21 + stk_54;
                    pu18 = (uint32_t *)((int)pu18 + 2);
                    u21 = u20 & 0xffff;
                    pb14 = pb14 + (u20 >> 0x10);
                  }
                  stk_d8 = stk_d8 + 1;
                  stk_ec = stk_ec + i2;
                } while (stk_d8 < i9);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteTransSubMirV8to16(sprites,index,(int)X87_FIST32(x),(int)X87_FIST32(y));
    }
  }
  return;
}

/* W_ScaleSpriteTransSubMirHV8to16 @ 0x080747c0, 2436 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended subtractively (colour 0 transparent), mirrored
 * horizontally and vertically. Clipped to the window set by W_Define. This
 * is the pixel loop: it reads the 8-bit sprite rows through the sprite's
 * palette converted to 16-bit colours and writes 16-bit pixels.
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
 *        SpriteDecompUnlockData, W_PutSpriteTransSubMirHV8to16
 * Called by: W_ScaleSpriteTransSubMirHV
 *
 * Elecbyte file: src/lib/spr16sub.c
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 6 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleSpriteTransSubMirHV8to16
               (int *sprites,int index,float x,float y,float arg5,float arg6)

{
  int i1;
  int i2;
  int i3;
  int i4;
  float80 f5;
  float80 f6;
  float80 f7;
  int *sprite;
  int sprite2;
  int i10;
  int i11;
  int i12;
  int i13;
  int *sprite3;
  uint8_t *pb15;
  int i16;
  int i17;
  int i18;
  uint32_t *pu19;
  uint32_t u20;
  uint32_t u21;
  uint32_t u22;
  int stk_144;
  int stk_100;
  int stk_fc;
  int stk_f8;
  int stk_f4;
  uint32_t stk_f0;
  uint32_t stk_ec;
  int stk_d8;
  uint32_t stk_54;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_f8 = 0;
  stk_100 = 0;
  if ((0.0 < arg5) && (0.0 < arg6)) {
    i3 = *sprite;
    i4 = sprite[1];
    if ((((double)0.001) <= ABS((float80)i3 - arg5)) || (((double)0.001) <= ABS((float80)i4 - arg6))) {
      f5 = x - ((float)((i3 - sprite[2]) + -1) * arg5) / (float80)i3;
      f6 = y - ((float)((i4 - sprite[3]) + -1) * arg6) / (float80)i4;
      if ((((f6 <= (float)W_y2) && ((float)W_y1 < (f6 + arg6) - 0.5)) &&
          (f5 <= (float)W_x2)) && ((float)W_x1 < (f5 + arg5) - 0.5)) {
        stk_f4 = (int)X87_FIST32(X87_FLOOR(f6));
        f7 = (float)stk_f4;
        if (f6 <= f7) {
          stk_ec = 0;
        }
        else {
          if ((float)stk_f4 < f6 - 0.5) {
            stk_f4 = stk_f4 + 1;
            f7 = (float)stk_f4;
          }
          stk_54 = (uint32_t)(int64_t)X87_FIST64((((float80)i4 * (f7 - f6)) / arg6) * 65536.0);
          stk_ec = stk_54;
        }
        if (stk_f4 < W_y1) {
          i10 = W_y1 - stk_f4;
          stk_f4 = W_y1;
          stk_54 = (uint32_t)(int64_t)X87_FIST64(((float)(i10 * i4) / arg6) * 65536.0);
          stk_ec = stk_ec + stk_54;
        }
        i10 = (int)X87_FIST32(X87_FLOOR((f6 + arg6) - 0.5));
        if (W_y2 < i10) {
          i10 = W_y2;
        }
        if (i10 - stk_f4 != -1 && -1 < (i10 - stk_f4) + 1) {
          stk_fc = (int)X87_FIST32(X87_FLOOR(f5));
          f6 = (float)stk_fc;
          if (f5 <= f6) {
            stk_f0 = 0;
          }
          else {
            if ((float)stk_fc < f5 - 0.5) {
              stk_fc = stk_fc + 1;
              f6 = (float)stk_fc;
            }
            stk_54 = (uint32_t)(int64_t)X87_FIST64((((f6 - f5) * (float80)i3) / arg5) * 65536.0)
            ;
            stk_f0 = stk_54;
          }
          if (f5 < (float)W_x1) {
            i11 = W_x1 - stk_fc;
            stk_fc = W_x1;
            stk_144 = (int)(int64_t)X87_FIST64(((float)(i11 * i3) / arg5) * 65536.0);
            stk_f0 = stk_f0 + stk_144;
          }
          i11 = (int)X87_FIST32(X87_FLOOR((f5 + arg5) - 0.5));
          if (W_x2 < i11) {
            i11 = W_x2;
          }
          stk_144 = (int)(int64_t)X87_FIST64((float)(i3 << 0x10) / arg5);
          i1 = (int)X87_FIST32((float)(i4 << 0x10) / arg6);
          for (; ((int)stk_f0 < 0 && (stk_fc <= i11)); stk_fc = stk_fc + 1) {
            stk_f0 = stk_f0 + stk_144;
          }
          i12 = (int)stk_f0 >> 0x10;
          if (i12 != 0) {
            stk_f0 = stk_f0 & 0xffff;
            stk_100 = i12;
          }
          for (; ((int)stk_ec < 0 && (stk_f4 <= i10)); stk_f4 = stk_f4 + 1) {
            stk_ec = stk_ec + i1;
          }
          i12 = (int)stk_ec >> 0x10;
          if (i12 != 0) {
            stk_ec = stk_ec & 0xffff;
            stk_f8 = i12;
          }
          i11 = (i11 - stk_fc) + 1;
          i10 = (i10 - stk_f4) + 1;
          if ((0 < i11) && (0 < i10)) {
            i12 = SpriteDecompGetAndLockData(sprites,index);
            if (i12 != 0) {
              i13 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              sprite3 = (int *)sprites[5];
              if (sprite3 == (int *)0x0) {
                sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
              }
              else {
                EBPalUpdate(sprite3);
              }
              stk_d8 = 0;
              if (0 < i10) {
                do {
                  pb15 = (uint8_t *)(((i12 + *(int *)(sprite[0xb] + -4 +
                                                        ((i4 - stk_f8) -
                                                        ((int)stk_ec >> 0x10)) * 4) + i3) -
                                     stk_100) + -1);
                  pu19 = (uint32_t *)(stk_fc * 2 +
                                    i13 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                     (stk_f4 + stk_d8) * 4));
                  u22 = stk_f0;
                  for (i2 = i11; i2 != 0; i2 = i2 + -1) {
                    if (*pb15 != 0) {
                      u20 = (uint32_t)*(short *)((int)sprite3 + (uint32_t)*pb15 * 2 + 0x5c);
                      u21 = *pu19;
                      i16 = (u21 & 0xf800) - (u20 & 0xf800);
                      i18 = (u21 & 0x7e0) - (u20 & 0x7e0);
                      i17 = (u21 & 0x1f) - (u20 & 0x1f);
                      *(uint16_t *)pu19 =
                           (uint16_t)i16 & -(short)(i16 >> 0x1f) - 1U |
                           (uint16_t)i18 & -(short)(i18 >> 0x1f) - 1U |
                           (uint16_t)i17 & -(short)(i17 >> 0x1f) - 1U;
                    }
                    u21 = u22 + stk_144;
                    pu19 = (uint32_t *)((int)pu19 + 2);
                    u22 = u21 & 0xffff;
                    pb15 = pb15 + -(u21 >> 0x10);
                  }
                  stk_d8 = stk_d8 + 1;
                  stk_ec = stk_ec + i1;
                } while (stk_d8 < i10);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteTransSubMirHV8to16(sprites,index,(int)X87_FIST32(x),(int)X87_FIST32(y));
    }
  }
  return;
}

/* W_RotateSpriteTransSub8to16_P @ 0x08075150, 3824 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, blended subtractively (colour 0 transparent).
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
 * Calls: SpriteArrayAccess, roundfloat, W_ScaleSpriteTransSub_S,
 *        SpriteDecompGetAndLockData, SpriteDecompGetData,
 *        SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * Called by: W_RotateSpriteTransSub_P
 *
 * Elecbyte file: src/lib/spr16sub.c
 * Note: 1 accesses to parts of a variable are written as sized accesses.
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 15 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x90 bytes,
 *       13 variables), because their address is taken.
 * Note: 8 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t W_RotateSpriteTransSub8to16_P
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
  uint64_t u9;
  float80 f10;
  float80 f11;
  float80 f12;
  float80 f13;
  float80 f14;
  float80 f15;
  float80 f16;
  float80 f17;
  int *sprite;
  int sprite2;
  int i20;
  int i21;
  uint32_t u22;
  int i23;
  int i24;
  int i25;
  int *sprite3;
  int i27;
  int i28;
  int i29;
  int i30;
  int i31;
  int i32;
  int i33;
  int i34;
  uint32_t u35;
  int i36;
  int i37;
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
  i20 = roundfloat(x2);
  i21 = roundfloat(y);
  i33 = (int)X87_FIST32(arg6 * 1024.0);
  if (i33 < 0) {
    i33 = -i33;
    arg5 = arg5 + 180.0;
  }
  stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
  i36 = (int)X87_FIST32(arg7 * 1024.0);
  if (i36 < 0) {
    i36 = -i36;
    arg5 = arg5 + 180.0;
  }
  if (i33 == 0) {
    return stk_20;
  }
  if (i36 == 0) {
    return stk_20;
  }
  if (arg5 < 0.0) {
    arg5 = (float)((int)X87_FIST32(-arg5 * ((float)0.0027777778f)) * 0x168 + 0x168) + arg5;
  }
  u9 = (int64_t)(int)X87_FIST32(arg5 * 8.0) % 0xb40;
  i29 = (int)u9;
  if (i29 == 0) {
L_08075442:
    u22 = W_ScaleSpriteTransSub_S
                       (sprites,index,x2,y,arg6 * arg8,arg7 * arg9);
    return u22;
  }
  if (i29 == 0x5a0) {
    arg7 = -arg7;
    arg6 = -arg6;
    goto L_08075442;
  }
  i5 = *sprite;
  i6 = sprite[1];
  i7 = sprite[2];
  i8 = sprite[3];
  f10 = (float)SinTable[(i29 + 0x2d0) % 0xb40];
  f11 = f10 * 0.0009765625;
  f13 = (float)SinTable[(int)((int64_t)
                                 ((uint64_t)(uint32_t)(i29 >> 0x1f) << 0x20 | u9 & 0xffffffff) %
                                0xb40)];
  f12 = f13 * 0.0009765625;
  i1 = (int)X87_FIST32((float)((SinTable[(i29 + 0x2d0) % 0xb40] << 0x10) / i33) / arg8);
  u22 = (SinTable[(int)((int64_t)
                           ((uint64_t)(uint32_t)(i29 >> 0x1f) << 0x20 | u9 & 0xffffffff) % 0xb40)
                    ] << 0x10) / i36;
  i2 = (int)X87_FIST32((float80)(int)u22 / arg8);
  if (i29 < 0x2d0) {
    i29 = -i7;
    i23 = -i8;
    i24 = (i5 - i7) + -1;
    i25 = (i6 - i8) + -1;
L_0807568f:
    f14 = (float80)i29;
    f15 = (float80)i24;
    stk_84 = (float80)i23;
    stk_8c = (float80)i25;
    stk_88 = stk_8c;
    f17 = f14;
  }
  else {
    if (i29 < 0x5a0) {
      i24 = (i5 - i7) + -1;
      i23 = -i8;
      i29 = (i6 - i8) + -1;
      i25 = -i7;
    }
    else {
      if (i29 < 0x870) {
        i29 = (i5 - i7) + -1;
        i23 = (i6 - i8) + -1;
        i24 = -i7;
        i25 = -i8;
        goto L_0807568f;
      }
      if (0xb3f < i29) {
        return u22;
      }
      i24 = -i7;
      i23 = (i6 - i8) + -1;
      i29 = -i8;
      i25 = (i5 - i7) + -1;
    }
    f14 = (float80)i24;
    stk_88 = (float80)i29;
    f15 = (float80)i25;
    stk_8c = (float80)i23;
    stk_84 = stk_88;
    f17 = f15;
  }
  stk_80 = (float80)i24;
  stk_88 = stk_88 * arg7;
  f14 = f14 * arg6;
  f16 = (float80)i23 * arg7;
  f15 = f15 * arg6;
  i29 = roundfloat((-f14 * f12 + f16 * f11) * arg9);
  i23 = roundfloat((-f15 * f12 + stk_88 * f11) * arg9);
  stk_50 = roundfloat((-(stk_80 * arg6) * f12 + stk_84 * arg7 * f11) * arg9);
  stk_90 = roundfloat((-(f17 * arg6) * f12 + stk_8c * arg7 * f11) * arg9);
  if ((stk_50 == i29) || (stk_50 == i23)) {
    stk_74 = 0;
    stk_70 = 0;
    stk_60 = (int)X87_FIST32((f14 * f11 + f16 * f12) * 65536.0 * arg8);
    stk_64 = (int)X87_FIST32((f15 * f11 + stk_88 * f12) * 65536.0 * arg8);
  }
  else {
    f17 = f11 * stk_80 * arg6 + stk_84 * arg7 * f12;
    stk_70 = (int)X87_FIST32(((f17 - (f14 * f11 + f16 * f12)) * 65536.0 * arg8) /
                          (float)(stk_50 - i29));
    if (stk_70 < 0) {
      stk_70 = -stk_70;
    }
    stk_74 = (int)X87_FIST32((((stk_88 * f12 + f15 * f11) - f17) * 65536.0 * arg8) /
                          (float)(stk_50 - i23));
    if (stk_74 < 0) {
      stk_74 = -stk_74;
    }
    stk_64 = (int)X87_FIST32(f17 * 65536.0 * arg8);
    stk_60 = stk_64;
  }
  for (; stk_50 < W_y1 - i21; stk_50 = stk_50 + 1) {
    i24 = stk_74;
    if (stk_50 < i29) {
      i24 = -stk_70;
    }
    stk_60 = stk_60 + i24;
    i24 = stk_74;
    if (i23 <= stk_50) {
      i24 = -stk_70;
    }
    stk_64 = stk_64 + i24;
  }
  if (W_y2 - i21 < stk_90) {
    stk_90 = W_y2 - i21;
  }
  i24 = SpriteDecompGetAndLockData(sprites,index);
  if (i24 == 0) {
    return 0;
  }
  i25 = SpriteDecompGetData(V_Current,V_CurrentIdx);
  sprite3 = (int *)sprites[5];
  if (sprite3 == (int *)0x0) {
    sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
  }
  else {
    EBPalUpdate(sprite3);
  }
  if (stk_50 <= stk_90) {
    i27 = W_x1 - i20;
    do {
      i37 = stk_60 >> 0x10;
      if (stk_60 >> 0x10 < i27) {
        i37 = i27;
      }
      i28 = stk_64 >> 0x10;
      if (W_x2 - i20 < stk_64 >> 0x10) {
        i28 = W_x2 - i20;
      }
      stk_5c = (int)X87_FIST32(((((float80)i37 / arg8) * f10 -
                             ((float)stk_50 / arg9) * f13) * 65536.0) / (float80)i33) +
                 i7 * 0x10000;
      i34 = i8 * 0x10000 +
               (int)X87_FIST32(((((float80)i37 / arg8) * f13 +
                           ((float)stk_50 / arg9) * f10) * 65536.0) / (float80)i36);
      stk_38 = (uint16_t *)
                 (i25 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_50 + i21) * 4) +
                 (i20 + i37) * 2);
      i30 = (i28 - i37) + 1;
      i32 = i28 - i37;
      i31 = i2 * i30 + i34;
      for (i30 = stk_5c + i1 * i30;
          (SBORROW4(i28,i37) == i32 < 0 &&
          ((((i6 <= i31 >> 0x10 || (i5 <= i30 >> 0x10)) || (i31 >> 0x10 < 0)) ||
           (i30 >> 0x10 < 0)))); i30 = i30 - i1) {
        i28 = i28 + -1;
        i31 = i31 - i2;
        i32 = i28 - i37;
      }
      for (; (i37 <= i28 &&
             (((i6 <= i34 >> 0x10 || (i5 <= stk_5c >> 0x10)) ||
              ((i34 >> 0x10 < 0 || (stk_5c >> 0x10 < 0)))))); stk_5c = stk_5c + i1) {
        stk_38 = stk_38 + 1;
        i37 = i37 + 1;
        i34 = i34 + i2;
      }
      i37 = (i28 - i37) + 1;
      if (0 < i37) {
        do {
          b3 = *(uint8_t *)((stk_5c >> 0x10) + i24 + *(int *)(i4 + (i34 >> 0x10) * 4));
          if (b3 != 0) {
            u35 = (uint32_t)*(uint16_t *)((int)sprite3 + (uint32_t)b3 * 2 + 0x5c);
            u22 = (uint32_t)*stk_38;
            i28 = (u22 & 0xf800) - (u35 & 0xf800);
            i32 = (u22 & 0x7e0) - (u35 & 0x7e0);
            i31 = (u22 & 0x1f) - (u35 & 0x1f);
            *stk_38 = (uint16_t)i28 & -(short)(i28 >> 0x1f) - 1U |
                        (uint16_t)i32 & -(short)(i32 >> 0x1f) - 1U |
                        (uint16_t)i31 & -(short)(i31 >> 0x1f) - 1U;
          }
          stk_5c = stk_5c + i1;
          stk_38 = stk_38 + 1;
          i34 = i34 + i2;
          i37 = i37 + -1;
        } while (i37 != 0);
      }
      i37 = stk_74;
      if (stk_50 < i29) {
        i37 = -stk_70;
      }
      stk_60 = stk_60 + i37;
      i37 = stk_74;
      if (i23 <= stk_50) {
        i37 = -stk_70;
      }
      stk_64 = stk_64 + i37;
      stk_50 = stk_50 + 1;
    } while (stk_50 <= stk_90);
  }
  u22 = SpriteDecompUnlockData();
  return u22;
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

/* W_RotateSpriteTransSubMirH8to16_P @ 0x08076040, 3760 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, blended subtractively (colour 0 transparent),
 * mirrored horizontally. Clipped to the window set by W_Define. This is the
 * pixel loop: it reads the 8-bit sprite rows through the sprite's palette
 * converted to 16-bit colours and writes 16-bit pixels. Scaling without
 * rotation is handed to the scaled blitter.
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
 * Calls: SpriteArrayAccess, roundfloat, W_ScaleSpriteTransSub_S,
 *        SpriteDecompGetAndLockData, SpriteDecompGetData,
 *        SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * Called by: W_RotateSpriteTransSub_P
 *
 * Elecbyte file: src/lib/spr16sub.c
 * Note: 1 accesses to parts of a variable are written as sized accesses.
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 15 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x90 bytes,
 *       13 variables), because their address is taken.
 * Note: 8 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t W_RotateSpriteTransSubMirH8to16_P
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
  uint64_t u9;
  float80 f10;
  float80 f11;
  float80 f12;
  float80 f13;
  float80 f14;
  float80 f15;
  float80 f16;
  float80 f17;
  int *sprite;
  int sprite2;
  int i20;
  int i21;
  uint32_t u22;
  int i23;
  int i24;
  int i25;
  int *sprite3;
  int i27;
  int i28;
  int i29;
  int i30;
  int i31;
  int i32;
  int i33;
  uint32_t u34;
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
  i20 = roundfloat(x2);
  i21 = roundfloat(y);
  i31 = (int)X87_FIST32(arg6 * 1024.0);
  if (i31 < 0) {
    i31 = -i31;
    arg5 = arg5 + 180.0;
  }
  stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
  i35 = (int)X87_FIST32(arg7 * 1024.0);
  if (i35 < 0) {
    i35 = -i35;
    arg5 = arg5 + 180.0;
  }
  if (i31 == 0) {
    return stk_20;
  }
  if (i35 == 0) {
    return stk_20;
  }
  if (arg5 < 0.0) {
    arg5 = (float)((int)X87_FIST32(-arg5 * ((float)0.0027777778f)) * 0x168 + 0x168) + arg5;
  }
  u9 = (int64_t)(int)X87_FIST32(arg5 * 8.0) % 0xb40;
  i27 = (int)u9;
  if (i27 == 0) {
    arg6 = -arg6;
L_0807632d:
    u22 = W_ScaleSpriteTransSub_S
                       (sprites,index,x2,y,arg6 * arg8,arg7 * arg9);
    return u22;
  }
  if (i27 == 0x5a0) {
    arg7 = -arg7;
    goto L_0807632d;
  }
  i5 = *sprite;
  i6 = sprite[1];
  i7 = sprite[2];
  i8 = sprite[3];
  f10 = (float)SinTable[(i27 + 0x2d0) % 0xb40];
  f11 = f10 * 0.0009765625;
  f13 = (float)SinTable[(int)((int64_t)
                                 ((uint64_t)(uint32_t)(i27 >> 0x1f) << 0x20 | u9 & 0xffffffff) %
                                0xb40)];
  f12 = f13 * 0.0009765625;
  i1 = (int)X87_FIST32((float)((SinTable[(i27 + 0x2d0) % 0xb40] << 0x10) / i31) / arg8);
  u22 = (SinTable[(int)((int64_t)
                           ((uint64_t)(uint32_t)(i27 >> 0x1f) << 0x20 | u9 & 0xffffffff) % 0xb40)
                    ] << 0x10) / i35;
  i2 = (int)X87_FIST32((float80)(int)u22 / arg8);
  if (i27 < 0x2d0) {
    i27 = -i7;
    i23 = -i8;
    i24 = (i5 - i7) + -1;
    i25 = (i6 - i8) + -1;
L_0807657f:
    f14 = (float80)i27;
    f15 = (float80)i24;
    stk_84 = (float80)i23;
    stk_8c = (float80)i25;
    stk_88 = stk_8c;
    f17 = f14;
  }
  else {
    if (i27 < 0x5a0) {
      i24 = (i5 - i7) + -1;
      i23 = -i8;
      i27 = (i6 - i8) + -1;
      i25 = -i7;
    }
    else {
      if (i27 < 0x870) {
        i27 = (i5 - i7) + -1;
        i23 = (i6 - i8) + -1;
        i24 = -i7;
        i25 = -i8;
        goto L_0807657f;
      }
      if (0xb3f < i27) {
        return u22;
      }
      i24 = -i7;
      i23 = (i6 - i8) + -1;
      i27 = -i8;
      i25 = (i5 - i7) + -1;
    }
    f14 = (float80)i24;
    stk_88 = (float80)i27;
    f15 = (float80)i25;
    stk_8c = (float80)i23;
    stk_84 = stk_88;
    f17 = f15;
  }
  stk_80 = (float80)i24;
  stk_88 = stk_88 * arg7;
  f14 = f14 * arg6;
  f16 = (float80)i23 * arg7;
  f15 = f15 * arg6;
  i27 = roundfloat((-f14 * f12 + f16 * f11) * arg9);
  i24 = roundfloat((-f15 * f12 + stk_88 * f11) * arg9);
  stk_50 = roundfloat((-(stk_80 * arg6) * f12 + stk_84 * arg7 * f11) * arg9);
  stk_90 = roundfloat((-(f17 * arg6) * f12 + stk_8c * arg7 * f11) * arg9);
  if ((stk_50 == i27) || (stk_50 == i24)) {
    stk_74 = 0;
    stk_70 = 0;
    stk_60 = (int)X87_FIST32((f14 * f11 + f16 * f12) * 65536.0 * arg8);
    stk_64 = (int)X87_FIST32((f15 * f11 + stk_88 * f12) * 65536.0 * arg8);
  }
  else {
    f17 = f11 * stk_80 * arg6 + stk_84 * arg7 * f12;
    stk_70 = (int)X87_FIST32(((f17 - (f14 * f11 + f16 * f12)) * 65536.0 * arg8) /
                          (float)(stk_50 - i27));
    if (stk_70 < 0) {
      stk_70 = -stk_70;
    }
    stk_74 = (int)X87_FIST32((((stk_88 * f12 + f15 * f11) - f17) * 65536.0 * arg8) /
                          (float)(stk_50 - i24));
    if (stk_74 < 0) {
      stk_74 = -stk_74;
    }
    stk_64 = (int)X87_FIST32(f17 * 65536.0 * arg8);
    stk_60 = stk_64;
  }
  for (; stk_50 < W_y1 - i21; stk_50 = stk_50 + 1) {
    i23 = stk_74;
    if (stk_50 < i27) {
      i23 = -stk_70;
    }
    stk_60 = stk_60 + i23;
    i23 = stk_74;
    if (i24 <= stk_50) {
      i23 = -stk_70;
    }
    stk_64 = stk_64 + i23;
  }
  if (W_y2 - i21 < stk_90) {
    stk_90 = W_y2 - i21;
  }
  i23 = SpriteDecompGetAndLockData(sprites,index);
  if (i23 == 0) {
    return 0;
  }
  i25 = SpriteDecompGetData(V_Current,V_CurrentIdx);
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
      i36 = stk_64 >> 0x10;
      if (W_x2 < i20 - i33) {
        i33 = i20 - W_x2;
      }
      if (i20 - i36 < W_x1) {
        i36 = i20 - W_x1;
      }
      stk_5c = (int)X87_FIST32(((((float80)i33 / arg8) * f10 -
                             ((float)stk_50 / arg9) * f13) * 65536.0) / (float80)i31) +
                 i7 * 0x10000;
      i32 = i8 * 0x10000 +
               (int)X87_FIST32(((((float80)i33 / arg8) * f13 +
                           ((float)stk_50 / arg9) * f10) * 65536.0) / (float80)i35);
      stk_38 = (uint16_t *)
                 (i25 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_50 + i21) * 4) +
                 (i20 - i33) * 2);
      i28 = (i36 - i33) + 1;
      i30 = i36 - i33;
      i29 = i2 * i28 + i32;
      for (i28 = stk_5c + i1 * i28;
          (SBORROW4(i36,i33) == i30 < 0 &&
          ((((i6 <= i29 >> 0x10 || (i5 <= i28 >> 0x10)) || (i29 >> 0x10 < 0)) ||
           (i28 >> 0x10 < 0)))); i28 = i28 - i1) {
        i36 = i36 + -1;
        i29 = i29 - i2;
        i30 = i36 - i33;
      }
      for (; (i33 <= i36 &&
             (((i6 <= i32 >> 0x10 || (i5 <= stk_5c >> 0x10)) ||
              ((i32 >> 0x10 < 0 || (stk_5c >> 0x10 < 0)))))); stk_5c = stk_5c + i1) {
        stk_38 = stk_38 + -1;
        i33 = i33 + 1;
        i32 = i32 + i2;
      }
      i33 = (i36 - i33) + 1;
      if (0 < i33) {
        do {
          b3 = *(uint8_t *)((stk_5c >> 0x10) + i23 + *(int *)(i4 + (i32 >> 0x10) * 4));
          if (b3 != 0) {
            u34 = (uint32_t)*(uint16_t *)((int)sprite3 + (uint32_t)b3 * 2 + 0x5c);
            u22 = (uint32_t)*stk_38;
            i36 = (u22 & 0xf800) - (u34 & 0xf800);
            i30 = (u22 & 0x7e0) - (u34 & 0x7e0);
            i29 = (u22 & 0x1f) - (u34 & 0x1f);
            *stk_38 = (uint16_t)i36 & -(short)(i36 >> 0x1f) - 1U |
                        (uint16_t)i30 & -(short)(i30 >> 0x1f) - 1U |
                        (uint16_t)i29 & -(short)(i29 >> 0x1f) - 1U;
          }
          stk_5c = stk_5c + i1;
          stk_38 = stk_38 + -1;
          i32 = i32 + i2;
          i33 = i33 + -1;
        } while (i33 != 0);
      }
      i33 = stk_74;
      if (stk_50 < i27) {
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
  u22 = SpriteDecompUnlockData();
  return u22;
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

/* W_ScaleShadowTransSub8to16 @ 0x08076ef0, 2197 bytes
 *
 * Draws the shape of sprite `index` (a shadow) of a sprite array, scaled,
 * into the current drawing buffer, in a solid colour subtracted from the
 * screen. Clipped to the window set by W_Define. This is the pixel loop: it
 * reads the 8-bit sprite rows through the sprite's palette converted to
 * 16-bit colours and writes 16-bit pixels.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         uint32_t
 *
 * Calls: SpriteArrayAccess, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * Called by: W_ScaleShadowTransSub
 *
 * Elecbyte file: src/lib/spr16sub.c
 * Note: 6 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleShadowTransSub8to16
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               uint32_t arg7)

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
  char *pc11;
  int i12;
  int i13;
  int i14;
  int i15;
  uint32_t u16;
  uint32_t u17;
  uint16_t *pu18;
  int stk_134;
  int stk_100;
  int stk_fc;
  int stk_f8;
  int stk_f4;
  uint32_t stk_f0;
  uint32_t stk_ec;
  int stk_d8;
  uint32_t stk_4c;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_f8 = 0;
  stk_100 = 0;
  if (((0.0 < arg5) && (0.0 < arg6)) && (arg7 != 0)) {
    i1 = *sprite;
    i9 = sprite[1];
    f4 = x - ((float80)sprite[2] * arg5) / (float80)i1;
    f2 = y - ((float80)sprite[3] * arg6) / (float80)i9;
    if (((f2 <= (float)W_y2) && ((float)W_y1 < (f2 + arg6) - 0.5)) &&
       ((f4 <= (float)W_x2 && ((float)W_x1 < (f4 + arg5) - 0.5)))) {
      stk_f4 = (int)X87_FIST32(X87_FLOOR(f2));
      f3 = (float)stk_f4;
      if (f2 <= f3) {
        stk_ec = 0;
      }
      else {
        if ((float)stk_f4 < f2 - 0.5) {
          stk_f4 = stk_f4 + 1;
          f3 = (float)stk_f4;
        }
        stk_4c = (uint32_t)(int64_t)X87_FIST64((((f3 - f2) * (float80)i9) / arg6) * 65536.0);
        stk_ec = stk_4c;
      }
      if (stk_f4 < W_y1) {
        i7 = W_y1 - stk_f4;
        stk_f4 = W_y1;
        stk_4c = (uint32_t)(int64_t)X87_FIST64(((float)(i7 * i9) / arg6) * 65536.0);
        stk_ec = stk_ec + stk_4c;
      }
      i7 = (int)X87_FIST32(X87_FLOOR((f2 + arg6) - 0.5));
      if (W_y2 < i7) {
        i7 = W_y2;
      }
      if (i7 - stk_f4 != -1 && -1 < (i7 - stk_f4) + 1) {
        stk_fc = (int)X87_FIST32(X87_FLOOR(f4));
        f2 = (float)stk_fc;
        if (f4 <= f2) {
          stk_f0 = 0;
        }
        else {
          if ((float)stk_fc < f4 - 0.5) {
            stk_fc = stk_fc + 1;
            f2 = (float)stk_fc;
          }
          stk_4c = (uint32_t)(int64_t)X87_FIST64((((f2 - f4) * (float80)i1) / arg5) * 65536.0);
          stk_f0 = stk_4c;
        }
        if (f4 < (float)W_x1) {
          i8 = W_x1 - stk_fc;
          stk_fc = W_x1;
          stk_134 = (int)(int64_t)X87_FIST64(((float)(i8 * i1) / arg5) * 65536.0);
          stk_f0 = stk_f0 + stk_134;
        }
        i8 = (int)X87_FIST32(X87_FLOOR((f4 + arg5) - 0.5));
        if (W_x2 < i8) {
          i8 = W_x2;
        }
        stk_4c = (uint32_t)(int64_t)X87_FIST64((float)(i1 << 0x10) / arg5);
        i1 = (int)X87_FIST32((float)(i9 << 0x10) / arg6);
        for (; ((int)stk_f0 < 0 && (stk_fc <= i8)); stk_fc = stk_fc + 1) {
          stk_f0 = stk_f0 + stk_4c;
        }
        i9 = (int)stk_f0 >> 0x10;
        if (i9 != 0) {
          stk_f0 = stk_f0 & 0xffff;
          stk_100 = i9;
        }
        for (; ((int)stk_ec < 0 && (stk_f4 <= i7)); stk_f4 = stk_f4 + 1) {
          stk_ec = stk_ec + i1;
        }
        i9 = (int)stk_ec >> 0x10;
        if (i9 != 0) {
          stk_ec = stk_ec & 0xffff;
          stk_f8 = i9;
        }
        i9 = (i8 - stk_fc) + 1;
        i7 = (i7 - stk_f4) + 1;
        if ((0 < i9) && (0 < i7)) {
          i8 = SpriteDecompGetAndLockData(sprites,index);
          if (i8 != 0) {
            i10 = SpriteDecompGetData(V_Current,V_CurrentIdx);
            if ((int *)sprites[5] == (int *)0x0) {
              SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
            }
            else {
              EBPalUpdate((int *)sprites[5]);
            }
            for (stk_d8 = 0; stk_d8 < i7; stk_d8 = stk_d8 + 1) {
              pc11 = (char *)(i8 + *(int *)(sprite[0xb] +
                                                 (((int)stk_ec >> 0x10) + stk_f8) * 4) +
                                stk_100);
              pu18 = (uint16_t *)
                        (stk_fc * 2 +
                        i10 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_f4 + stk_d8) * 4));
              u17 = stk_f0;
              for (i15 = i9; i15 != 0; i15 = i15 + -1) {
                if (*pc11 != '\0') {
                  u16 = (uint32_t)*pu18;
                  i12 = (u16 & 0xf800) - (arg7 & 0xf800);
                  i14 = (u16 & 0x7e0) - (arg7 & 0x7e0);
                  i13 = (u16 & 0x1f) - (arg7 & 0x1f);
                  *pu18 = (uint16_t)i12 & -(short)(i12 >> 0x1f) - 1U |
                             (uint16_t)i14 & -(short)(i14 >> 0x1f) - 1U |
                             (uint16_t)i13 & -(short)(i13 >> 0x1f) - 1U;
                }
                u16 = u17 + stk_4c;
                pu18 = pu18 + 1;
                u17 = u16 & 0xffff;
                pc11 = pc11 + (u16 >> 0x10);
              }
              stk_ec = stk_ec + i1;
            }
            SpriteDecompUnlockData();
          }
        }
      }
    }
  }
  return;
}

/* W_ScaleShadowTransSubMirH8to16 @ 0x08077790, 2209 bytes
 *
 * Draws the shape of sprite `index` (a shadow) of a sprite array, scaled,
 * into the current drawing buffer, in a solid colour subtracted from the
 * screen, mirrored horizontally. Clipped to the window set by W_Define. This
 * is the pixel loop: it reads the 8-bit sprite rows through the sprite's
 * palette converted to 16-bit colours and writes 16-bit pixels.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         uint32_t
 *
 * Calls: SpriteArrayAccess, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * Called by: W_ScaleShadowTransSubMirH
 *
 * Elecbyte file: src/lib/spr16sub.c
 * Note: 5 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleShadowTransSubMirH8to16
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               uint32_t arg7)

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
  int i11;
  char *pc12;
  int i13;
  int i14;
  int i15;
  int i16;
  uint32_t u17;
  uint32_t u18;
  uint16_t *pu19;
  int stk_134;
  int stk_100;
  int stk_fc;
  int stk_f8;
  int stk_f4;
  uint32_t stk_f0;
  uint32_t stk_ec;
  int stk_d8;
  uint32_t stk_4c;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_f8 = 0;
  stk_100 = 0;
  if (((0.0 < arg5) && (0.0 < arg6)) && (arg7 != 0)) {
    i1 = *sprite;
    i2 = sprite[1];
    f5 = x - ((float)((i1 - sprite[2]) + -1) * arg5) / (float80)i1;
    f3 = y - ((float80)sprite[3] * arg6) / (float80)i2;
    if (((f3 <= (float)W_y2) && ((float)W_y1 < (f3 + arg6) - 0.5)) &&
       ((f5 <= (float)W_x2 && ((float)W_x1 < (f5 + arg5) - 0.5)))) {
      stk_f4 = (int)X87_FIST32(X87_FLOOR(f3));
      f4 = (float)stk_f4;
      if (f3 <= f4) {
        stk_ec = 0;
      }
      else {
        if ((float)stk_f4 < f3 - 0.5) {
          stk_f4 = stk_f4 + 1;
          f4 = (float)stk_f4;
        }
        stk_4c = (uint32_t)(int64_t)X87_FIST64((((f4 - f3) * (float80)i2) / arg6) * 65536.0);
        stk_ec = stk_4c;
      }
      if (stk_f4 < W_y1) {
        i8 = W_y1 - stk_f4;
        stk_f4 = W_y1;
        stk_4c = (uint32_t)(int64_t)X87_FIST64(((float)(i8 * i2) / arg6) * 65536.0);
        stk_ec = stk_ec + stk_4c;
      }
      i8 = (int)X87_FIST32(X87_FLOOR((f3 + arg6) - 0.5));
      if (W_y2 < i8) {
        i8 = W_y2;
      }
      if (i8 - stk_f4 != -1 && -1 < (i8 - stk_f4) + 1) {
        stk_fc = (int)X87_FIST32(X87_FLOOR(f5));
        f3 = (float)stk_fc;
        if (f5 <= f3) {
          stk_f0 = 0;
        }
        else {
          if ((float)stk_fc < f5 - 0.5) {
            stk_fc = stk_fc + 1;
            f3 = (float)stk_fc;
          }
          stk_4c = (uint32_t)(int64_t)X87_FIST64((((f3 - f5) * (float80)i1) / arg5) * 65536.0);
          stk_f0 = stk_4c;
        }
        if (f5 < (float)W_x1) {
          i9 = W_x1 - stk_fc;
          stk_fc = W_x1;
          stk_134 = (int)(int64_t)X87_FIST64(((float)(i9 * i1) / arg5) * 65536.0);
          stk_f0 = stk_f0 + stk_134;
        }
        i9 = (int)X87_FIST32(X87_FLOOR((f5 + arg5) - 0.5));
        if (W_x2 < i9) {
          i9 = W_x2;
        }
        stk_134 = (int)(int64_t)X87_FIST64((float)(i1 << 0x10) / arg5);
        i2 = (int)X87_FIST32((float)(i2 << 0x10) / arg6);
        for (; ((int)stk_f0 < 0 && (stk_fc <= i9)); stk_fc = stk_fc + 1) {
          stk_f0 = stk_f0 + stk_134;
        }
        i10 = (int)stk_f0 >> 0x10;
        if (i10 != 0) {
          stk_f0 = stk_f0 & 0xffff;
          stk_100 = i10;
        }
        for (; ((int)stk_ec < 0 && (stk_f4 <= i8)); stk_f4 = stk_f4 + 1) {
          stk_ec = stk_ec + i2;
        }
        i10 = (int)stk_ec >> 0x10;
        if (i10 != 0) {
          stk_ec = stk_ec & 0xffff;
          stk_f8 = i10;
        }
        i9 = (i9 - stk_fc) + 1;
        i8 = (i8 - stk_f4) + 1;
        if ((0 < i9) && (0 < i8)) {
          i10 = SpriteDecompGetAndLockData(sprites,index);
          if (i10 != 0) {
            i11 = SpriteDecompGetData(V_Current,V_CurrentIdx);
            if ((int *)sprites[5] == (int *)0x0) {
              SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
            }
            else {
              EBPalUpdate((int *)sprites[5]);
            }
            stk_d8 = 0;
            if (0 < i8) {
              do {
                pc12 = (char *)(((i10 + *(int *)(sprite[0xb] +
                                                      (((int)stk_ec >> 0x10) + stk_f8) * 4) +
                                    i1) - stk_100) + -1);
                pu19 = (uint16_t *)
                          (stk_fc * 2 +
                          i11 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_f4 + stk_d8) * 4));
                u18 = stk_f0;
                for (i16 = i9; i16 != 0; i16 = i16 + -1) {
                  if (*pc12 != '\0') {
                    u17 = (uint32_t)*pu19;
                    i13 = (u17 & 0xf800) - (arg7 & 0xf800);
                    i15 = (u17 & 0x7e0) - (arg7 & 0x7e0);
                    i14 = (u17 & 0x1f) - (arg7 & 0x1f);
                    *pu19 = (uint16_t)i13 & -(short)(i13 >> 0x1f) - 1U |
                               (uint16_t)i15 & -(short)(i15 >> 0x1f) - 1U |
                               (uint16_t)i14 & -(short)(i14 >> 0x1f) - 1U;
                  }
                  u17 = u18 + stk_134;
                  pu19 = pu19 + 1;
                  u18 = u17 & 0xffff;
                  pc12 = pc12 + -(u17 >> 0x10);
                }
                stk_d8 = stk_d8 + 1;
                stk_ec = stk_ec + i2;
              } while (stk_d8 < i8);
            }
            SpriteDecompUnlockData();
          }
        }
      }
    }
  }
  return;
}

/* W_ScaleShadowTransSubMirV8to16 @ 0x08078040, 2241 bytes
 *
 * Draws the shape of sprite `index` (a shadow) of a sprite array, scaled,
 * into the current drawing buffer, in a solid colour subtracted from the
 * screen, mirrored vertically. Clipped to the window set by W_Define. This
 * is the pixel loop: it reads the 8-bit sprite rows through the sprite's
 * palette converted to 16-bit colours and writes 16-bit pixels.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         uint32_t
 *
 * Calls: SpriteArrayAccess, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * Called by: W_ScaleShadowTransSubMirV
 *
 * Elecbyte file: src/lib/spr16sub.c
 * Note: 5 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleShadowTransSubMirV8to16
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               uint32_t arg7)

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
  int i11;
  char *pc12;
  int i13;
  int i14;
  int i15;
  int i16;
  uint32_t u17;
  uint32_t u18;
  uint16_t *pu19;
  int stk_134;
  int stk_100;
  int stk_fc;
  int stk_f8;
  int stk_f4;
  uint32_t stk_f0;
  uint32_t stk_ec;
  int stk_d8;
  uint32_t stk_4c;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_f8 = 0;
  stk_100 = 0;
  if (((0.0 < arg5) && (0.0 < arg6)) && (arg7 != 0)) {
    i1 = *sprite;
    i2 = sprite[1];
    f5 = x - ((float80)sprite[2] * arg5) / (float80)i1;
    f3 = y - ((float)((i2 - sprite[3]) + -1) * arg6) / (float80)i2;
    if (((f3 <= (float)W_y2) && ((float)W_y1 < (f3 + arg6) - 0.5)) &&
       ((f5 <= (float)W_x2 && ((float)W_x1 < (f5 + arg5) - 0.5)))) {
      stk_f4 = (int)X87_FIST32(X87_FLOOR(f3));
      f4 = (float)stk_f4;
      if (f3 <= f4) {
        stk_ec = 0;
      }
      else {
        if ((float)stk_f4 < f3 - 0.5) {
          stk_f4 = stk_f4 + 1;
          f4 = (float)stk_f4;
        }
        stk_4c = (uint32_t)(int64_t)X87_FIST64((((f4 - f3) * (float80)i2) / arg6) * 65536.0);
        stk_ec = stk_4c;
      }
      if (stk_f4 < W_y1) {
        i8 = W_y1 - stk_f4;
        stk_f4 = W_y1;
        stk_4c = (uint32_t)(int64_t)X87_FIST64(((float)(i8 * i2) / arg6) * 65536.0);
        stk_ec = stk_ec + stk_4c;
      }
      i8 = (int)X87_FIST32(X87_FLOOR((f3 + arg6) - 0.5));
      if (W_y2 < i8) {
        i8 = W_y2;
      }
      if (i8 - stk_f4 != -1 && -1 < (i8 - stk_f4) + 1) {
        stk_fc = (int)X87_FIST32(X87_FLOOR(f5));
        f3 = (float)stk_fc;
        if (f5 <= f3) {
          stk_f0 = 0;
        }
        else {
          if ((float)stk_fc < f5 - 0.5) {
            stk_fc = stk_fc + 1;
            f3 = (float)stk_fc;
          }
          stk_4c = (uint32_t)(int64_t)X87_FIST64((((f3 - f5) * (float80)i1) / arg5) * 65536.0);
          stk_f0 = stk_4c;
        }
        if (f5 < (float)W_x1) {
          i9 = W_x1 - stk_fc;
          stk_fc = W_x1;
          stk_134 = (int)(int64_t)X87_FIST64(((float)(i9 * i1) / arg5) * 65536.0);
          stk_f0 = stk_f0 + stk_134;
        }
        i9 = (int)X87_FIST32(X87_FLOOR((f5 + arg5) - 0.5));
        if (W_x2 < i9) {
          i9 = W_x2;
        }
        stk_4c = (uint32_t)(int64_t)X87_FIST64((float)(i1 << 0x10) / arg5);
        i1 = (int)X87_FIST32((float)(i2 << 0x10) / arg6);
        for (; ((int)stk_f0 < 0 && (stk_fc <= i9)); stk_fc = stk_fc + 1) {
          stk_f0 = stk_f0 + stk_4c;
        }
        i10 = (int)stk_f0 >> 0x10;
        if (i10 != 0) {
          stk_f0 = stk_f0 & 0xffff;
          stk_100 = i10;
        }
        for (; ((int)stk_ec < 0 && (stk_f4 <= i8)); stk_f4 = stk_f4 + 1) {
          stk_ec = stk_ec + i1;
        }
        i10 = (int)stk_ec >> 0x10;
        if (i10 != 0) {
          stk_ec = stk_ec & 0xffff;
          stk_f8 = i10;
        }
        i9 = (i9 - stk_fc) + 1;
        i8 = (i8 - stk_f4) + 1;
        if ((0 < i9) && (0 < i8)) {
          i10 = SpriteDecompGetAndLockData(sprites,index);
          if (i10 != 0) {
            i11 = SpriteDecompGetData(V_Current,V_CurrentIdx);
            if ((int *)sprites[5] == (int *)0x0) {
              SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
            }
            else {
              EBPalUpdate((int *)sprites[5]);
            }
            stk_d8 = 0;
            if (0 < i8) {
              do {
                pc12 = (char *)(i10 + *(int *)(sprite[0xb] + -4 +
                                                    ((i2 - stk_f8) - ((int)stk_ec >> 0x10)) *
                                                    4) + stk_100);
                pu19 = (uint16_t *)
                          (stk_fc * 2 +
                          i11 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_f4 + stk_d8) * 4));
                u18 = stk_f0;
                for (i16 = i9; i16 != 0; i16 = i16 + -1) {
                  if (*pc12 != '\0') {
                    u17 = (uint32_t)*pu19;
                    i13 = (u17 & 0xf800) - (arg7 & 0xf800);
                    i15 = (u17 & 0x7e0) - (arg7 & 0x7e0);
                    i14 = (u17 & 0x1f) - (arg7 & 0x1f);
                    *pu19 = (uint16_t)i13 & -(short)(i13 >> 0x1f) - 1U |
                               (uint16_t)i15 & -(short)(i15 >> 0x1f) - 1U |
                               (uint16_t)i14 & -(short)(i14 >> 0x1f) - 1U;
                  }
                  u17 = u18 + stk_4c;
                  pu19 = pu19 + 1;
                  u18 = u17 & 0xffff;
                  pc12 = pc12 + (u17 >> 0x10);
                }
                stk_d8 = stk_d8 + 1;
                stk_ec = stk_ec + i1;
              } while (stk_d8 < i8);
            }
            SpriteDecompUnlockData();
          }
        }
      }
    }
  }
  return;
}

/* W_ScaleShadowTransSubMirHV8to16 @ 0x08078910, 2241 bytes
 *
 * Draws the shape of sprite `index` (a shadow) of a sprite array, scaled,
 * into the current drawing buffer, in a solid colour subtracted from the
 * screen, mirrored horizontally and vertically. Clipped to the window set by
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
 *   arg7         uint32_t
 *
 * Calls: SpriteArrayAccess, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * Called by: W_ScaleShadowTransSubMirHV
 *
 * Elecbyte file: src/lib/spr16sub.c
 * Note: 4 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleShadowTransSubMirHV8to16
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               uint32_t arg7)

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
  int i12;
  char *pc13;
  int i14;
  int i15;
  int i16;
  int i17;
  uint32_t u18;
  uint32_t u19;
  uint16_t *pu20;
  int stk_134;
  int stk_100;
  int stk_fc;
  int stk_f8;
  int stk_f4;
  uint32_t stk_f0;
  uint32_t stk_ec;
  int stk_d8;
  uint32_t stk_4c;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_f8 = 0;
  stk_100 = 0;
  if (((0.0 < arg5) && (0.0 < arg6)) && (arg7 != 0)) {
    i2 = *sprite;
    i3 = sprite[1];
    f6 = x - ((float)((i2 - sprite[2]) + -1) * arg5) / (float80)i2;
    f4 = y - ((float)((i3 - sprite[3]) + -1) * arg6) / (float80)i3;
    if (((f4 <= (float)W_y2) && ((float)W_y1 < (f4 + arg6) - 0.5)) &&
       ((f6 <= (float)W_x2 && ((float)W_x1 < (f6 + arg5) - 0.5)))) {
      stk_f4 = (int)X87_FIST32(X87_FLOOR(f4));
      f5 = (float)stk_f4;
      if (f4 <= f5) {
        stk_ec = 0;
      }
      else {
        if ((float)stk_f4 < f4 - 0.5) {
          stk_f4 = stk_f4 + 1;
          f5 = (float)stk_f4;
        }
        stk_4c = (uint32_t)(int64_t)X87_FIST64((((f5 - f4) * (float80)i3) / arg6) * 65536.0);
        stk_ec = stk_4c;
      }
      if (stk_f4 < W_y1) {
        i9 = W_y1 - stk_f4;
        stk_f4 = W_y1;
        stk_4c = (uint32_t)(int64_t)X87_FIST64(((float)(i9 * i3) / arg6) * 65536.0);
        stk_ec = stk_ec + stk_4c;
      }
      i9 = (int)X87_FIST32(X87_FLOOR((f4 + arg6) - 0.5));
      if (W_y2 < i9) {
        i9 = W_y2;
      }
      if (i9 - stk_f4 != -1 && -1 < (i9 - stk_f4) + 1) {
        stk_fc = (int)X87_FIST32(X87_FLOOR(f6));
        f4 = (float)stk_fc;
        if (f6 <= f4) {
          stk_f0 = 0;
        }
        else {
          if ((float)stk_fc < f6 - 0.5) {
            stk_fc = stk_fc + 1;
            f4 = (float)stk_fc;
          }
          stk_4c = (uint32_t)(int64_t)X87_FIST64((((f4 - f6) * (float80)i2) / arg5) * 65536.0);
          stk_f0 = stk_4c;
        }
        if (f6 < (float)W_x1) {
          i10 = W_x1 - stk_fc;
          stk_fc = W_x1;
          stk_134 = (int)(int64_t)X87_FIST64(((float)(i10 * i2) / arg5) * 65536.0);
          stk_f0 = stk_f0 + stk_134;
        }
        i10 = (int)X87_FIST32(X87_FLOOR((f6 + arg5) - 0.5));
        if (W_x2 < i10) {
          i10 = W_x2;
        }
        stk_134 = (int)(int64_t)X87_FIST64((float)(i2 << 0x10) / arg5);
        i1 = (int)X87_FIST32((float)(i3 << 0x10) / arg6);
        for (; ((int)stk_f0 < 0 && (stk_fc <= i10)); stk_fc = stk_fc + 1) {
          stk_f0 = stk_f0 + stk_134;
        }
        i11 = (int)stk_f0 >> 0x10;
        if (i11 != 0) {
          stk_f0 = stk_f0 & 0xffff;
          stk_100 = i11;
        }
        for (; ((int)stk_ec < 0 && (stk_f4 <= i9)); stk_f4 = stk_f4 + 1) {
          stk_ec = stk_ec + i1;
        }
        i11 = (int)stk_ec >> 0x10;
        if (i11 != 0) {
          stk_ec = stk_ec & 0xffff;
          stk_f8 = i11;
        }
        i10 = (i10 - stk_fc) + 1;
        i9 = (i9 - stk_f4) + 1;
        if ((0 < i10) && (0 < i9)) {
          i11 = SpriteDecompGetAndLockData(sprites,index);
          if (i11 != 0) {
            i12 = SpriteDecompGetData(V_Current,V_CurrentIdx);
            if ((int *)sprites[5] == (int *)0x0) {
              SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
            }
            else {
              EBPalUpdate((int *)sprites[5]);
            }
            stk_d8 = 0;
            if (0 < i9) {
              do {
                pc13 = (char *)(((i11 + *(int *)(sprite[0xb] + -4 +
                                                      ((i3 - stk_f8) - ((int)stk_ec >> 0x10))
                                                      * 4) + i2) - stk_100) + -1);
                pu20 = (uint16_t *)
                          (stk_fc * 2 +
                          i12 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_f4 + stk_d8) * 4));
                u19 = stk_f0;
                for (i17 = i10; i17 != 0; i17 = i17 + -1) {
                  if (*pc13 != '\0') {
                    u18 = (uint32_t)*pu20;
                    i14 = (u18 & 0xf800) - (arg7 & 0xf800);
                    i16 = (u18 & 0x7e0) - (arg7 & 0x7e0);
                    i15 = (u18 & 0x1f) - (arg7 & 0x1f);
                    *pu20 = (uint16_t)i14 & -(short)(i14 >> 0x1f) - 1U |
                               (uint16_t)i16 & -(short)(i16 >> 0x1f) - 1U |
                               (uint16_t)i15 & -(short)(i15 >> 0x1f) - 1U;
                  }
                  u18 = u19 + stk_134;
                  pu20 = pu20 + 1;
                  u19 = u18 & 0xffff;
                  pc13 = pc13 + -(u18 >> 0x10);
                }
                stk_d8 = stk_d8 + 1;
                stk_ec = stk_ec + i1;
              } while (stk_d8 < i9);
            }
            SpriteDecompUnlockData();
          }
        }
      }
    }
  }
  return;
}

/* W_RotateShadowTransSub8to16_P @ 0x080791e0, 3748 bytes
 *
 * Draws the shape of sprite `index` (a shadow) of a sprite array, rotated
 * and scaled, into the current drawing buffer, in a solid colour subtracted
 * from the screen. Clipped to the window set by W_Define. This is the pixel
 * loop: it reads the 8-bit sprite rows through the sprite's palette
 * converted to 16-bit colours and writes 16-bit pixels. Scaling without
 * rotation is handed to the scaled blitter.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         float
 *   arg9         float
 *   arg10        uint32_t
 *
 * Calls: SpriteArrayAccess, roundfloat, W_ScaleShadowTransSub_S,
 *        SpriteDecompGetAndLockData, SpriteDecompGetData,
 *        SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * Called by: W_RotateShadowTransSub_P
 *
 * Elecbyte file: src/lib/spr16sub.c
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 14 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: 8 temporaries are float80, as the original kept them in x87 registers.
 */
int W_RotateShadowTransSub8to16_P
              (int *sprites,int index,float x,float y,float arg5,float arg6,
              float arg7,float arg8,float arg9,uint32_t arg10)

{
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  uint64_t u7;
  float80 f8;
  float80 f9;
  float80 f10;
  float80 f11;
  float80 f12;
  float80 f13;
  float80 f14;
  float80 f15;
  int *sprite;
  int sprite2;
  int i18;
  int i19;
  int i20;
  int i21;
  int i22;
  int i23;
  int i24;
  int i25;
  int i26;
  int i27;
  uint32_t u28;
  int i29;
  int i30;
  int i31;
  int i32;
  int i33;
  int stk_94;
  float stk_90;
  float stk_8c;
  float stk_88;
  float stk_84;
  int stk_78;
  int stk_74;
  int stk_68;
  int stk_64;
  int stk_60;
  int stk_54;
  int stk_50;
  uint16_t *stk_38;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  i20 = sprite[0xb];
  i18 = roundfloat(x);
  i19 = roundfloat(y);
  stk_54 = (int)X87_FIST32(arg6 * 1024.0);
  if (stk_54 < 0) {
    stk_54 = -stk_54;
    arg5 = arg5 + 180.0;
  }
  i31 = (int)X87_FIST32(arg7 * 1024.0);
  if (i31 < 0) {
    i31 = -i31;
    arg5 = arg5 + 180.0;
  }
  if (stk_54 == 0) {
    return 0;
  }
  if (i31 == 0) {
    return stk_54;
  }
  if (arg5 < 0.0) {
    arg5 = (float)((int)X87_FIST32(-arg5 * ((float)0.0027777778f)) * 0x168 + 0x168) + arg5;
  }
  u7 = (int64_t)(int)X87_FIST32(arg5 * 8.0) % 0xb40;
  i26 = (int)u7;
  if (i26 == 0) {
L_08079510:
    i20 = W_ScaleShadowTransSub_S
                       (sprites,index,x,y,arg6 * arg8,arg7 * arg9,arg10
                       );
    return i20;
  }
  if (i26 == 0x5a0) {
    arg7 = -arg7;
    arg6 = -arg6;
    goto L_08079510;
  }
  i3 = *sprite;
  i4 = sprite[1];
  i5 = sprite[2];
  i6 = sprite[3];
  f8 = (float)SinTable[(i26 + 0x2d0) % 0xb40];
  f9 = f8 * 0.0009765625;
  f11 = (float)SinTable[(int)((int64_t)
                                 ((uint64_t)(uint32_t)(i26 >> 0x1f) << 0x20 | u7 & 0xffffffff) %
                                0xb40)];
  f10 = f11 * 0.0009765625;
  i1 = (int)X87_FIST32((float)((SinTable[(i26 + 0x2d0) % 0xb40] << 0x10) / stk_54) / arg8);
  i21 = (SinTable[(int)((int64_t)
                           ((uint64_t)(uint32_t)(i26 >> 0x1f) << 0x20 | u7 & 0xffffffff) % 0xb40)
                    ] << 0x10) / i31;
  i2 = (int)X87_FIST32((float80)i21 / arg8);
  if (i26 < 0x2d0) {
    i26 = -i5;
    i22 = -i6;
    i21 = (i3 - i5) + -1;
    i23 = (i4 - i6) + -1;
L_0807974f:
    f12 = (float80)i26;
    f13 = (float80)i21;
    stk_88 = (float80)i22;
    stk_90 = (float80)i23;
    stk_8c = stk_90;
    f15 = f12;
  }
  else {
    if (i26 < 0x5a0) {
      i21 = (i3 - i5) + -1;
      i22 = -i6;
      i26 = (i4 - i6) + -1;
      i23 = -i5;
    }
    else {
      if (i26 < 0x870) {
        i26 = (i3 - i5) + -1;
        i22 = (i4 - i6) + -1;
        i21 = -i5;
        i23 = -i6;
        goto L_0807974f;
      }
      if (0xb3f < i26) {
        return i21;
      }
      i21 = -i5;
      i22 = (i4 - i6) + -1;
      i26 = -i6;
      i23 = (i3 - i5) + -1;
    }
    f12 = (float80)i21;
    stk_8c = (float80)i26;
    f13 = (float80)i23;
    stk_90 = (float80)i22;
    stk_88 = stk_8c;
    f15 = f13;
  }
  stk_84 = (float80)i21;
  stk_8c = stk_8c * arg7;
  f12 = f12 * arg6;
  f14 = (float80)i22 * arg7;
  f13 = f13 * arg6;
  i26 = roundfloat((-f12 * f10 + f14 * f9) * arg9);
  i21 = roundfloat((-f13 * f10 + stk_8c * f9) * arg9);
  stk_50 = roundfloat((-(stk_84 * arg6) * f10 + stk_88 * arg7 * f9) * arg9);
  stk_94 = roundfloat((-(f15 * arg6) * f10 + stk_90 * arg7 * f9) * arg9);
  if ((stk_50 == i26) || (stk_50 == i21)) {
    stk_78 = 0;
    stk_74 = 0;
    stk_64 = (int)X87_FIST32((f12 * f9 + f14 * f10) * 65536.0 * arg8);
    stk_68 = (int)X87_FIST32((f13 * f9 + stk_8c * f10) * 65536.0 * arg8);
  }
  else {
    f15 = f9 * stk_84 * arg6 + stk_88 * arg7 * f10;
    stk_74 = (int)X87_FIST32(((f15 - (f12 * f9 + f14 * f10)) * 65536.0 * arg8) /
                          (float)(stk_50 - i26));
    if (stk_74 < 0) {
      stk_74 = -stk_74;
    }
    stk_78 = (int)X87_FIST32((((stk_8c * f10 + f13 * f9) - f15) * 65536.0 * arg8) /
                          (float)(stk_50 - i21));
    if (stk_78 < 0) {
      stk_78 = -stk_78;
    }
    stk_68 = (int)X87_FIST32(f15 * 65536.0 * arg8);
    stk_64 = stk_68;
  }
  for (; stk_50 < W_y1 - i19; stk_50 = stk_50 + 1) {
    i22 = stk_78;
    if (stk_50 < i26) {
      i22 = -stk_74;
    }
    stk_64 = stk_64 + i22;
    i22 = stk_78;
    if (i21 <= stk_50) {
      i22 = -stk_74;
    }
    stk_68 = stk_68 + i22;
  }
  if (W_y2 - i19 < stk_94) {
    stk_94 = W_y2 - i19;
  }
  i22 = SpriteDecompGetAndLockData(sprites,index);
  if (i22 == 0) {
    return 0;
  }
  i23 = SpriteDecompGetData(V_Current,V_CurrentIdx);
  if ((int *)sprites[5] == (int *)0x0) {
    SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
  }
  else {
    EBPalUpdate((int *)sprites[5]);
  }
  if (stk_50 <= stk_94) {
    i24 = W_x1 - i18;
    do {
      i33 = stk_64 >> 0x10;
      if (stk_64 >> 0x10 < i24) {
        i33 = i24;
      }
      i25 = stk_68 >> 0x10;
      if (W_x2 - i18 < stk_68 >> 0x10) {
        i25 = W_x2 - i18;
      }
      stk_60 = (int)X87_FIST32(((((float80)i33 / arg8) * f8 -
                             ((float)stk_50 / arg9) * f11) * 65536.0) / (float)stk_54) +
                 i5 * 0x10000;
      i32 = i6 * 0x10000 +
               (int)X87_FIST32(((((float80)i33 / arg8) * f11 + ((float)stk_50 / arg9) * f8
                           ) * 65536.0) / (float80)i31);
      stk_38 = (uint16_t *)
                 (i23 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_50 + i19) * 4) +
                 (i18 + i33) * 2);
      i27 = (i25 - i33) + 1;
      i30 = i25 - i33;
      i29 = i2 * i27 + i32;
      for (i27 = stk_60 + i1 * i27;
          (SBORROW4(i25,i33) == i30 < 0 &&
          ((((i4 <= i29 >> 0x10 || (i3 <= i27 >> 0x10)) || (i29 >> 0x10 < 0)) ||
           (i27 >> 0x10 < 0)))); i27 = i27 - i1) {
        i25 = i25 + -1;
        i29 = i29 - i2;
        i30 = i25 - i33;
      }
      for (; (i33 <= i25 &&
             (((i4 <= i32 >> 0x10 || (i3 <= stk_60 >> 0x10)) ||
              ((i32 >> 0x10 < 0 || (stk_60 >> 0x10 < 0)))))); stk_60 = stk_60 + i1) {
        stk_38 = stk_38 + 1;
        i33 = i33 + 1;
        i32 = i32 + i2;
      }
      i33 = (i25 - i33) + 1;
      if (0 < i33) {
        do {
          if (*(char *)((stk_60 >> 0x10) + i22 + *(int *)(i20 + (i32 >> 0x10) * 4)) !=
              '\0') {
            u28 = (uint32_t)*stk_38;
            i25 = (u28 & 0xf800) - (arg10 & 0xf800);
            i29 = (u28 & 0x1f) - (arg10 & 0x1f);
            i30 = (u28 & 0x7e0) - (arg10 & 0x7e0);
            *stk_38 = (uint16_t)i25 & -(short)(i25 >> 0x1f) - 1U |
                        (uint16_t)i30 & -(short)(i30 >> 0x1f) - 1U |
                        (uint16_t)i29 & -(short)(i29 >> 0x1f) - 1U;
          }
          stk_60 = stk_60 + i1;
          stk_38 = stk_38 + 1;
          i32 = i32 + i2;
          i33 = i33 + -1;
        } while (i33 != 0);
      }
      i33 = stk_78;
      if (stk_50 < i26) {
        i33 = -stk_74;
      }
      stk_64 = stk_64 + i33;
      i33 = stk_78;
      if (i21 <= stk_50) {
        i33 = -stk_74;
      }
      stk_68 = stk_68 + i33;
      stk_50 = stk_50 + 1;
    } while (stk_50 <= stk_94);
  }
  i20 = SpriteDecompUnlockData();
  return i20;
}

/* W_RotateShadowTransSubMirH8to16_P @ 0x0807a090, 3748 bytes
 *
 * Draws the shape of sprite `index` (a shadow) of a sprite array, rotated
 * and scaled, into the current drawing buffer, in a solid colour subtracted
 * from the screen, mirrored horizontally. Clipped to the window set by
 * W_Define. This is the pixel loop: it reads the 8-bit sprite rows through
 * the sprite's palette converted to 16-bit colours and writes 16-bit pixels.
 * Scaling without rotation is handed to the scaled blitter.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         float
 *   arg9         float
 *   arg10        uint32_t
 *
 * Calls: SpriteArrayAccess, roundfloat, W_ScaleShadowTransSub_S,
 *        SpriteDecompGetAndLockData, SpriteDecompGetData,
 *        SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * Called by: W_RotateShadowTransSub_P
 *
 * Elecbyte file: src/lib/spr16sub.c
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 14 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: 8 temporaries are float80, as the original kept them in x87 registers.
 */
int W_RotateShadowTransSubMirH8to16_P
              (int *sprites,int index,float x,float y,float arg5,float arg6,
              float arg7,float arg8,float arg9,uint32_t arg10)

{
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  uint64_t u7;
  float80 f8;
  float80 f9;
  float80 f10;
  float80 f11;
  float80 f12;
  float80 f13;
  float80 f14;
  float80 f15;
  int *sprite;
  int sprite2;
  int i18;
  int i19;
  int i20;
  int i21;
  int i22;
  int i23;
  int i24;
  int i25;
  uint32_t u26;
  int i27;
  int i28;
  int i29;
  int i30;
  int i31;
  int i32;
  int stk_94;
  float stk_90;
  float stk_8c;
  float stk_88;
  float stk_84;
  int stk_78;
  int stk_74;
  int stk_68;
  int stk_64;
  int stk_60;
  int stk_54;
  int stk_50;
  uint16_t *stk_38;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  i20 = sprite[0xb];
  i18 = roundfloat(x);
  i19 = roundfloat(y);
  stk_54 = (int)X87_FIST32(arg6 * 1024.0);
  if (stk_54 < 0) {
    stk_54 = -stk_54;
    arg5 = arg5 + 180.0;
  }
  i29 = (int)X87_FIST32(arg7 * 1024.0);
  if (i29 < 0) {
    i29 = -i29;
    arg5 = arg5 + 180.0;
  }
  if (stk_54 == 0) {
    return 0;
  }
  if (i29 == 0) {
    return stk_54;
  }
  if (arg5 < 0.0) {
    arg5 = (float)((int)X87_FIST32(-arg5 * ((float)0.0027777778f)) * 0x168 + 0x168) + arg5;
  }
  u7 = (int64_t)(int)X87_FIST32(arg5 * 8.0) % 0xb40;
  i24 = (int)u7;
  if (i24 == 0) {
    arg6 = -arg6;
L_0807a3bd:
    i20 = W_ScaleShadowTransSub_S
                       (sprites,index,x,y,arg6 * arg8,arg7 * arg9,arg10
                       );
    return i20;
  }
  if (i24 == 0x5a0) {
    arg7 = -arg7;
    goto L_0807a3bd;
  }
  i3 = *sprite;
  i4 = sprite[1];
  i5 = sprite[2];
  i6 = sprite[3];
  f8 = (float)SinTable[(i24 + 0x2d0) % 0xb40];
  f9 = f8 * 0.0009765625;
  f11 = (float)SinTable[(int)((int64_t)
                                 ((uint64_t)(uint32_t)(i24 >> 0x1f) << 0x20 | u7 & 0xffffffff) %
                                0xb40)];
  f10 = f11 * 0.0009765625;
  i1 = (int)X87_FIST32((float)((SinTable[(i24 + 0x2d0) % 0xb40] << 0x10) / stk_54) / arg8);
  i21 = (SinTable[(int)((int64_t)
                           ((uint64_t)(uint32_t)(i24 >> 0x1f) << 0x20 | u7 & 0xffffffff) % 0xb40)
                    ] << 0x10) / i29;
  i2 = (int)X87_FIST32((float80)i21 / arg8);
  if (i24 < 0x2d0) {
    i24 = -i5;
    i21 = -i6;
    i22 = (i3 - i5) + -1;
    i23 = (i4 - i6) + -1;
L_0807a5ff:
    f12 = (float80)i24;
    f13 = (float80)i22;
    stk_88 = (float80)i21;
    stk_90 = (float80)i23;
    stk_8c = stk_90;
    f15 = f12;
  }
  else {
    if (i24 < 0x5a0) {
      i22 = (i3 - i5) + -1;
      i21 = -i6;
      i24 = (i4 - i6) + -1;
      i23 = -i5;
    }
    else {
      if (i24 < 0x870) {
        i24 = (i3 - i5) + -1;
        i21 = (i4 - i6) + -1;
        i22 = -i5;
        i23 = -i6;
        goto L_0807a5ff;
      }
      if (0xb3f < i24) {
        return i21;
      }
      i22 = -i5;
      i21 = (i4 - i6) + -1;
      i24 = -i6;
      i23 = (i3 - i5) + -1;
    }
    f12 = (float80)i22;
    stk_8c = (float80)i24;
    f13 = (float80)i23;
    stk_90 = (float80)i21;
    stk_88 = stk_8c;
    f15 = f13;
  }
  stk_84 = (float80)i22;
  stk_8c = stk_8c * arg7;
  f12 = f12 * arg6;
  f14 = (float80)i21 * arg7;
  f13 = f13 * arg6;
  i24 = roundfloat((-f12 * f10 + f14 * f9) * arg9);
  i21 = roundfloat((-f13 * f10 + stk_8c * f9) * arg9);
  stk_50 = roundfloat((-(stk_84 * arg6) * f10 + stk_88 * arg7 * f9) * arg9);
  stk_94 = roundfloat((-(f15 * arg6) * f10 + stk_90 * arg7 * f9) * arg9);
  if ((stk_50 == i24) || (stk_50 == i21)) {
    stk_78 = 0;
    stk_74 = 0;
    stk_64 = (int)X87_FIST32((f12 * f9 + f14 * f10) * 65536.0 * arg8);
    stk_68 = (int)X87_FIST32((f13 * f9 + stk_8c * f10) * 65536.0 * arg8);
  }
  else {
    f15 = f9 * stk_84 * arg6 + stk_88 * arg7 * f10;
    stk_74 = (int)X87_FIST32(((f15 - (f12 * f9 + f14 * f10)) * 65536.0 * arg8) /
                          (float)(stk_50 - i24));
    if (stk_74 < 0) {
      stk_74 = -stk_74;
    }
    stk_78 = (int)X87_FIST32((((stk_8c * f10 + f13 * f9) - f15) * 65536.0 * arg8) /
                          (float)(stk_50 - i21));
    if (stk_78 < 0) {
      stk_78 = -stk_78;
    }
    stk_68 = (int)X87_FIST32(f15 * 65536.0 * arg8);
    stk_64 = stk_68;
  }
  for (; stk_50 < W_y1 - i19; stk_50 = stk_50 + 1) {
    i22 = stk_78;
    if (stk_50 < i24) {
      i22 = -stk_74;
    }
    stk_64 = stk_64 + i22;
    i22 = stk_78;
    if (i21 <= stk_50) {
      i22 = -stk_74;
    }
    stk_68 = stk_68 + i22;
  }
  if (W_y2 - i19 < stk_94) {
    stk_94 = W_y2 - i19;
  }
  i22 = SpriteDecompGetAndLockData(sprites,index);
  if (i22 == 0) {
    return 0;
  }
  i23 = SpriteDecompGetData(V_Current,V_CurrentIdx);
  if ((int *)sprites[5] == (int *)0x0) {
    SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
  }
  else {
    EBPalUpdate((int *)sprites[5]);
  }
  if (stk_50 <= stk_94) {
    do {
      i31 = stk_64 >> 0x10;
      i32 = stk_68 >> 0x10;
      if (W_x2 < i18 - i31) {
        i31 = i18 - W_x2;
      }
      if (i18 - i32 < W_x1) {
        i32 = i18 - W_x1;
      }
      stk_60 = (int)X87_FIST32(((((float80)i31 / arg8) * f8 -
                             ((float)stk_50 / arg9) * f11) * 65536.0) / (float)stk_54) +
                 i5 * 0x10000;
      i30 = i6 * 0x10000 +
               (int)X87_FIST32(((((float80)i31 / arg8) * f11 + ((float)stk_50 / arg9) * f8
                           ) * 65536.0) / (float80)i29);
      stk_38 = (uint16_t *)
                 (i23 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_50 + i19) * 4) +
                 (i18 - i31) * 2);
      i25 = (i32 - i31) + 1;
      i28 = i32 - i31;
      i27 = i2 * i25 + i30;
      for (i25 = stk_60 + i1 * i25;
          (SBORROW4(i32,i31) == i28 < 0 &&
          ((((i4 <= i27 >> 0x10 || (i3 <= i25 >> 0x10)) || (i27 >> 0x10 < 0)) ||
           (i25 >> 0x10 < 0)))); i25 = i25 - i1) {
        i32 = i32 + -1;
        i27 = i27 - i2;
        i28 = i32 - i31;
      }
      for (; (i31 <= i32 &&
             (((i4 <= i30 >> 0x10 || (i3 <= stk_60 >> 0x10)) ||
              ((i30 >> 0x10 < 0 || (stk_60 >> 0x10 < 0)))))); stk_60 = stk_60 + i1) {
        stk_38 = stk_38 + -1;
        i31 = i31 + 1;
        i30 = i30 + i2;
      }
      i31 = (i32 - i31) + 1;
      if (0 < i31) {
        do {
          if (*(char *)((stk_60 >> 0x10) + i22 + *(int *)(i20 + (i30 >> 0x10) * 4)) !=
              '\0') {
            u26 = (uint32_t)*stk_38;
            i32 = (u26 & 0xf800) - (arg10 & 0xf800);
            i27 = (u26 & 0x1f) - (arg10 & 0x1f);
            i28 = (u26 & 0x7e0) - (arg10 & 0x7e0);
            *stk_38 = (uint16_t)i32 & -(short)(i32 >> 0x1f) - 1U |
                        (uint16_t)i28 & -(short)(i28 >> 0x1f) - 1U |
                        (uint16_t)i27 & -(short)(i27 >> 0x1f) - 1U;
          }
          stk_60 = stk_60 + i1;
          stk_38 = stk_38 + -1;
          i30 = i30 + i2;
          i31 = i31 + -1;
        } while (i31 != 0);
      }
      i31 = stk_78;
      if (stk_50 < i24) {
        i31 = -stk_74;
      }
      stk_64 = stk_64 + i31;
      i31 = stk_78;
      if (i21 <= stk_50) {
        i31 = -stk_74;
      }
      stk_68 = stk_68 + i31;
      stk_50 = stk_50 + 1;
    } while (stk_50 <= stk_94);
  }
  i20 = SpriteDecompUnlockData();
  return i20;
}

