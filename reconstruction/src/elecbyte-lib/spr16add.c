/*
 * spr16add.c -- 16-bit additive blitters
 * Pixel loops that draw 8-bit sprites onto 16-bit buffers with additive
 * blending (plain and with alpha), unscaled, scaled and rotated, in all
 * mirror forms.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/spr16add.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* W_PutSpriteTransAdd8to16 @ 0x08062440, 712 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended additively (colour 0 transparent). Clipped to the window set by
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
 * Called by: W_PutSpriteTransAdd, W_PutSpriteTransAdd8to16_B,
 *            W_ScaleSpriteTransAdd8to16
 *
 * Elecbyte file: src/lib/spr16add.c
 */
void W_PutSpriteTransAdd8to16(int *sprites,int index,int x,int y)

{
  uint32_t u1;
  int i2;
  int *sprite;
  int sprite2;
  int i5;
  int i6;
  int *sprite3;
  uint8_t *pb8;
  uint32_t u9;
  uint16_t u10;
  uint16_t u11;
  int i13;
  int i14;
  uint32_t *pu15;
  uint32_t u16;
  int stk_4c;
  int stk_48;
  int stk_44;
  int stk_40;
  int stk_34;
  uint32_t u12;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_44 = 0;
  i13 = y - sprite[3];
  stk_4c = 0;
  i14 = x - sprite[2];
  if ((((i13 <= W_y2) && (W_y1 < sprite[1] + i13)) && (i14 <= W_x2)) &&
     (W_x1 < *sprite + i14)) {
    stk_40 = i13;
    if (i13 < W_y1) {
      stk_40 = W_y1;
      stk_44 = W_y1 - i13;
    }
    i13 = sprite[1] + i13 + -1;
    if (W_y2 < i13) {
      i13 = W_y2;
    }
    stk_48 = i14;
    if (i14 < W_x1) {
      stk_48 = W_x1;
      stk_4c = W_x1 - i14;
    }
    i14 = *sprite + i14 + -1;
    if (W_x2 < i14) {
      i14 = W_x2;
    }
    i14 = (i14 - stk_48) + 1;
    i13 = (i13 - stk_40) + 1;
    if (((0 < i14) && (0 < i13)) &&
       (i5 = SpriteDecompGetAndLockData(sprites,index), i5 != 0)) {
      i6 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      sprite3 = (int *)sprites[5];
      if (sprite3 == (int *)0x0) {
        sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
      }
      else {
        EBPalUpdate(sprite3);
      }
      stk_34 = 0;
      if (0 < i13) {
        do {
          pb8 = (uint8_t *)(i5 + *(int *)(sprite[0xb] + (stk_44 + stk_34) * 4) + stk_4c);
          pu15 = (uint32_t *)(i6 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_40 + stk_34) * 4) +
                            stk_48 * 2);
          for (i2 = i14; i2 != 0; i2 = i2 + -1) {
            if (*pb8 != 0) {
              u9 = (uint32_t)*(uint16_t *)((int)sprite3 + (uint32_t)*pb8 * 2 + 0x5c);
              u12 = *pu15;
              u16 = (u12 & 0xf800) + (u9 & 0xf800);
              if (0xf800 < u16) {
                u16 = 0xf800;
              }
              u1 = (u12 & 0x7e0) + (u9 & 0x7e0);
              u10 = (uint16_t)u1;
              if (0x7e0 < u1) {
                u10 = 0x7e0;
              }
              u12 = (u9 & 0x1f) + (u12 & 0x1f);
              u11 = (uint16_t)u12;
              if (0x1f < u12) {
                u11 = 0x1f;
              }
              *(uint16_t *)pu15 = (uint16_t)u16 | u10 | u11;
            }
            pu15 = (uint32_t *)((int)pu15 + 2);
            pb8 = pb8 + 1;
          }
          stk_34 = stk_34 + 1;
        } while (stk_34 < i13);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteTransAddMirH8to16 @ 0x08062710, 735 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended additively (colour 0 transparent), mirrored horizontally. Clipped
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
 * Called by: W_PutSpriteTransAddMirH, W_PutSpriteTransAddMirH8to16_B,
 *            W_ScaleSpriteTransAddMirH8to16
 *
 * Elecbyte file: src/lib/spr16add.c
 */
void W_PutSpriteTransAddMirH8to16(int *sprites,int index,int x,int y)

{
  uint32_t u1;
  int i2;
  int i3;
  int *sprite;
  int sprite2;
  int i6;
  int i7;
  int i8;
  int *sprite3;
  uint32_t u10;
  uint16_t u11;
  uint16_t u12;
  int i14;
  uint32_t *pu15;
  uint32_t u16;
  int stk_4c;
  int stk_48;
  int stk_44;
  int stk_40;
  int stk_34;
  uint8_t *stk_2c;
  uint32_t u13;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  i3 = *sprite;
  stk_44 = 0;
  i6 = (sprite[2] - i3) + 1 + x;
  i14 = y - sprite[3];
  stk_4c = 0;
  if ((((i14 <= W_y2) && (W_y1 < sprite[1] + i14)) && (i6 <= W_x2)) &&
     (W_x1 < i3 + i6)) {
    stk_40 = i14;
    if (i14 < W_y1) {
      stk_40 = W_y1;
      stk_44 = W_y1 - i14;
    }
    i14 = sprite[1] + i14 + -1;
    if (W_y2 < i14) {
      i14 = W_y2;
    }
    stk_48 = i6;
    if (i6 < W_x1) {
      stk_48 = W_x1;
      stk_4c = W_x1 - i6;
    }
    i6 = i3 + i6 + -1;
    if (W_x2 < i6) {
      i6 = W_x2;
    }
    i6 = (i6 - stk_48) + 1;
    i14 = (i14 - stk_40) + 1;
    if (((0 < i6) && (0 < i14)) &&
       (i7 = SpriteDecompGetAndLockData(sprites,index), i7 != 0)) {
      i8 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      sprite3 = (int *)sprites[5];
      if (sprite3 == (int *)0x0) {
        sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
      }
      else {
        EBPalUpdate(sprite3);
      }
      stk_34 = 0;
      if (0 < i14) {
        do {
          stk_2c = (uint8_t *)((i7 + *(int *)(sprite[0xb] + (stk_44 + stk_34) * 4) + i3) -
                             stk_4c);
          pu15 = (uint32_t *)(i8 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_40 + stk_34) * 4) +
                            stk_48 * 2);
          for (i2 = i6; i2 != 0; i2 = i2 + -1) {
            stk_2c = stk_2c + -1;
            if (*stk_2c != 0) {
              u10 = (uint32_t)*(uint16_t *)((int)sprite3 + (uint32_t)*stk_2c * 2 + 0x5c);
              u13 = *pu15;
              u16 = (u13 & 0xf800) + (u10 & 0xf800);
              if (0xf800 < u16) {
                u16 = 0xf800;
              }
              u1 = (u13 & 0x7e0) + (u10 & 0x7e0);
              u11 = (uint16_t)u1;
              if (0x7e0 < u1) {
                u11 = 0x7e0;
              }
              u13 = (u10 & 0x1f) + (u13 & 0x1f);
              u12 = (uint16_t)u13;
              if (0x1f < u13) {
                u12 = 0x1f;
              }
              *(uint16_t *)pu15 = (uint16_t)u16 | u11 | u12;
            }
            pu15 = (uint32_t *)((int)pu15 + 2);
          }
          stk_34 = stk_34 + 1;
        } while (stk_34 < i14);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteTransAddMirV8to16 @ 0x080629f0, 744 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended additively (colour 0 transparent), mirrored vertically. Clipped to
 * the window set by W_Define. This is the pixel loop: it reads the 8-bit
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
 * Called by: W_PutSpriteTransAddMirV, W_PutSpriteTransAddMirV8to16_B,
 *            W_ScaleSpriteTransAddMirV8to16
 *
 * Elecbyte file: src/lib/spr16add.c
 */
void W_PutSpriteTransAddMirV8to16(int *sprites,int index,int x,int y)

{
  uint32_t u1;
  int i2;
  int i3;
  int *sprite;
  int sprite2;
  int i6;
  int i7;
  int *sprite3;
  uint8_t *pb9;
  uint32_t u10;
  uint16_t u11;
  uint16_t u12;
  int i13;
  int i15;
  uint32_t *pu16;
  uint32_t u17;
  int stk_4c;
  int stk_48;
  int stk_44;
  int stk_40;
  int stk_34;
  uint32_t u14;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_44 = 0;
  i3 = sprite[1];
  i15 = x - sprite[2];
  i13 = (sprite[3] - i3) + 1 + y;
  stk_4c = 0;
  if ((((i13 <= W_y2) && (W_y1 < i3 + i13)) && (i15 <= W_x2)) &&
     (W_x1 < *sprite + i15)) {
    stk_40 = i13;
    if (i13 < W_y1) {
      stk_40 = W_y1;
      stk_44 = W_y1 - i13;
    }
    i13 = i3 + i13 + -1;
    if (W_y2 < i13) {
      i13 = W_y2;
    }
    stk_48 = i15;
    if (i15 < W_x1) {
      stk_48 = W_x1;
      stk_4c = W_x1 - i15;
    }
    i15 = *sprite + i15 + -1;
    if (W_x2 < i15) {
      i15 = W_x2;
    }
    i15 = (i15 - stk_48) + 1;
    i13 = (i13 - stk_40) + 1;
    if (((0 < i15) && (0 < i13)) &&
       (i6 = SpriteDecompGetAndLockData(sprites,index), i6 != 0)) {
      i7 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      sprite3 = (int *)sprites[5];
      if (sprite3 == (int *)0x0) {
        sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
      }
      else {
        EBPalUpdate(sprite3);
      }
      stk_34 = 0;
      if (0 < i13) {
        do {
          pb9 = (uint8_t *)(i6 + *(int *)(sprite[0xb] + -4 + ((i3 - stk_44) - stk_34) * 4)
                           + stk_4c);
          pu16 = (uint32_t *)(i7 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_40 + stk_34) * 4) +
                            stk_48 * 2);
          for (i2 = i15; i2 != 0; i2 = i2 + -1) {
            if (*pb9 != 0) {
              u10 = (uint32_t)*(uint16_t *)((int)sprite3 + (uint32_t)*pb9 * 2 + 0x5c);
              u14 = *pu16;
              u17 = (u14 & 0xf800) + (u10 & 0xf800);
              if (0xf800 < u17) {
                u17 = 0xf800;
              }
              u1 = (u14 & 0x7e0) + (u10 & 0x7e0);
              u11 = (uint16_t)u1;
              if (0x7e0 < u1) {
                u11 = 0x7e0;
              }
              u14 = (u10 & 0x1f) + (u14 & 0x1f);
              u12 = (uint16_t)u14;
              if (0x1f < u14) {
                u12 = 0x1f;
              }
              *(uint16_t *)pu16 = (uint16_t)u17 | u11 | u12;
            }
            pu16 = (uint32_t *)((int)pu16 + 2);
            pb9 = pb9 + 1;
          }
          stk_34 = stk_34 + 1;
        } while (stk_34 < i13);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteTransAddMirHV8to16 @ 0x08062ce0, 760 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended additively (colour 0 transparent), mirrored horizontally and
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
 * Called by: W_PutSpriteTransAddMirHV, W_PutSpriteTransAddMirHV8to16_B,
 *            W_ScaleSpriteTransAddMirHV8to16
 *
 * Elecbyte file: src/lib/spr16add.c
 */
void W_PutSpriteTransAddMirHV8to16(int *sprites,int index,int x,int y)

{
  uint32_t u1;
  int i2;
  int i3;
  int i4;
  int *sprite;
  int sprite2;
  int i7;
  int i8;
  int i9;
  int *sprite3;
  uint32_t u11;
  uint16_t u12;
  uint16_t u13;
  int i14;
  uint32_t *pu16;
  uint32_t u17;
  int stk_4c;
  int stk_48;
  int stk_44;
  int stk_40;
  int stk_34;
  uint8_t *stk_2c;
  uint32_t u15;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  i3 = *sprite;
  i4 = sprite[1];
  stk_44 = 0;
  i7 = (sprite[2] - i3) + 1 + x;
  stk_4c = 0;
  i14 = (sprite[3] - i4) + 1 + y;
  if ((((i14 <= W_y2) && (W_y1 < i4 + i14)) && (i7 <= W_x2)) && (W_x1 < i3 + i7))
  {
    stk_40 = i14;
    if (i14 < W_y1) {
      stk_40 = W_y1;
      stk_44 = W_y1 - i14;
    }
    i14 = i4 + i14 + -1;
    if (W_y2 < i14) {
      i14 = W_y2;
    }
    stk_48 = i7;
    if (i7 < W_x1) {
      stk_48 = W_x1;
      stk_4c = W_x1 - i7;
    }
    i7 = i3 + i7 + -1;
    if (W_x2 < i7) {
      i7 = W_x2;
    }
    i7 = (i7 - stk_48) + 1;
    i14 = (i14 - stk_40) + 1;
    if (((0 < i7) && (0 < i14)) &&
       (i8 = SpriteDecompGetAndLockData(sprites,index), i8 != 0)) {
      i9 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      sprite3 = (int *)sprites[5];
      if (sprite3 == (int *)0x0) {
        sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
      }
      else {
        EBPalUpdate(sprite3);
      }
      stk_34 = 0;
      if (0 < i14) {
        do {
          stk_2c = (uint8_t *)((i8 + *(int *)(sprite[0xb] + -4 +
                                               ((i4 - stk_44) - stk_34) * 4) + i3) -
                             stk_4c);
          pu16 = (uint32_t *)(i9 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_40 + stk_34) * 4) +
                            stk_48 * 2);
          for (i2 = i7; i2 != 0; i2 = i2 + -1) {
            stk_2c = stk_2c + -1;
            if (*stk_2c != 0) {
              u11 = (uint32_t)*(uint16_t *)((int)sprite3 + (uint32_t)*stk_2c * 2 + 0x5c);
              u15 = *pu16;
              u17 = (u15 & 0xf800) + (u11 & 0xf800);
              if (0xf800 < u17) {
                u17 = 0xf800;
              }
              u1 = (u15 & 0x7e0) + (u11 & 0x7e0);
              u12 = (uint16_t)u1;
              if (0x7e0 < u1) {
                u12 = 0x7e0;
              }
              u15 = (u11 & 0x1f) + (u15 & 0x1f);
              u13 = (uint16_t)u15;
              if (0x1f < u15) {
                u13 = 0x1f;
              }
              *(uint16_t *)pu16 = (uint16_t)u17 | u12 | u13;
            }
            pu16 = (uint32_t *)((int)pu16 + 2);
          }
          stk_34 = stk_34 + 1;
        } while (stk_34 < i14);
      }
      SpriteDecompUnlockData();
      return;
    }
  }
  return;
}

/* W_PutSpriteTransAdd8to16_B @ 0x08062fe0, 2267 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended additively (colour 0 transparent), with explicit source and
 * destination alpha (256 = full). Clipped to the window set by W_Define.
 * This is the pixel loop: it reads the 8-bit sprite rows through the
 * sprite's palette converted to 16-bit colours and writes 16-bit pixels.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *   arg5         int
 *   arg6         int
 *
 * Calls: SpriteArrayAccess, W_PutSprite8to16, W_PutSpriteTransAdd8to16,
 *        SpriteDecompGetAndLockData, SpriteDecompGetData,
 *        SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * C library: memset
 * Called by: W_PutSpriteTransAdd_B, W_ScaleSpriteTransAdd8to16_B
 *
 * Elecbyte file: src/lib/spr16add.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x250 bytes,
 *       8 variables), because their address is taken.
 */
void W_PutSpriteTransAdd8to16_B
               (int *sprites,int index,int x,int y,int arg5,int arg6)

{
  uint32_t u1;
  int i2;
  uint16_t u3;
  uint16_t u4;
  int *sprite;
  int sprite2;
  int i7;
  int i8;
  int *sprite3;
  uint32_t u10;
  uint32_t u11;
  int i12;
  uint8_t *pb13;
  int i14;
  uint32_t u15;
  uint16_t *pu16;
  unsigned char frame[0x250] __attribute__((aligned(16)));
#define stk_250 (*(uint16_t **)(frame + 0x0))
#define stk_24c (*(int *)(frame + 0x4))
#define stk_248 (*(int *)(frame + 0x8))
#define stk_244 (*(int *)(frame + 0xc))
#define stk_240 (*(int *)(frame + 0x10))
#define stk_234 (*(int *)(frame + 0x1c))
#define stk_230 (*(int *)(frame + 0x20))
#define stk_21c (*(uint16_t (*)[262])(frame + 0x34))
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_244 = 0;
  stk_24c = 0;
  if ((arg5 == 0x100) && (arg6 == 0)) {
    W_PutSprite8to16(sprites,index,x,y);
  }
  else if ((arg5 == 0x100) && (arg6 == 0x100)) {
    W_PutSpriteTransAdd8to16(sprites,index,x,y);
  }
  else if ((arg5 != 0) || (arg6 != 0x100)) {
    i12 = y - sprite[3];
    i14 = x - sprite[2];
    if ((i12 <= W_y2) &&
       (((W_y1 < sprite[1] + i12 && (i14 <= W_x2)) && (W_x1 < *sprite + i14)))) {
      stk_240 = i12;
      if (i12 < W_y1) {
        stk_240 = W_y1;
        stk_244 = W_y1 - i12;
      }
      i12 = sprite[1] + i12 + -1;
      if (W_y2 < i12) {
        i12 = W_y2;
      }
      stk_248 = i14;
      if (i14 < W_x1) {
        stk_248 = W_x1;
        stk_24c = W_x1 - i14;
      }
      i14 = *sprite + i14 + -1;
      if (W_x2 < i14) {
        i14 = W_x2;
      }
      i14 = (i14 - stk_248) + 1;
      i12 = (i12 - stk_240) + 1;
      if (((0 < i14) && (0 < i12)) &&
         (i7 = SpriteDecompGetAndLockData(sprites,index), i7 != 0)) {
        i8 = SpriteDecompGetData(V_Current,V_CurrentIdx);
        sprite3 = (int *)sprites[5];
        if (sprite3 == (int *)0x0) {
          sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
        }
        else {
          EBPalUpdate(sprite3);
        }
        pu16 = (uint16_t *)(sprite3 + 0x17);
        stk_250 = pu16;
        if (arg5 != 0x100) {
          stk_250 = stk_21c;
          if (arg5 == 0) {
            memset(stk_21c,0,sprite[5] * 2);
          }
          else if (arg5 == 0x80) {
            stk_230 = 1;
            i2 = sprite[5];
            if (1 < i2) {
              do {
                stk_21c[stk_230] = pu16[stk_230] >> 1 & 0xfbef;
                stk_230 = stk_230 + 1;
              } while (stk_230 < i2);
            }
          }
          else {
            stk_230 = 1;
            i2 = sprite[5];
            if (1 < i2) {
              do {
                u15 = (uint32_t)pu16[stk_230];
                stk_21c[stk_230] =
                     (uint16_t)((u15 & 0xf800) * arg5 >> 8) & 0xf800 |
                     (uint16_t)((u15 & 0x7e0) * arg5 >> 8) & 0x7e0 |
                     (uint16_t)((u15 & 0x1f) * arg5 >> 8) & 0x1f;
                stk_230 = stk_230 + 1;
              } while (stk_230 < i2);
            }
          }
        }
        if (arg6 == 0) {
          stk_234 = 0;
          if (0 < i12) {
            sprite3 = (int *)(stk_240 * 4 + *(int *)(sprite2 + 0x2c));
            sprite = (int *)(stk_244 * 4 + sprite[0xb]);
            do {
              pb13 = (uint8_t *)(stk_24c + i7 + *sprite);
              pu16 = (uint16_t *)(stk_248 * 2 + i8 + *sprite3);
              for (sprite2 = i14; sprite2 != 0; sprite2 = sprite2 + -1) {
                if (*pb13 != 0) {
                  *pu16 = stk_250[*pb13];
                }
                pu16 = pu16 + 1;
                pb13 = pb13 + 1;
              }
              stk_234 = stk_234 + 1;
              sprite3 = sprite3 + 1;
              sprite = sprite + 1;
            } while (stk_234 < i12);
          }
        }
        else if ((arg5 + arg6 < 0x101) && (arg6 == 0x80)) {
          stk_234 = 0;
          if (0 < i12) {
            do {
              pb13 = (uint8_t *)(stk_24c +
                                i7 + *(int *)(sprite[0xb] + (stk_244 + stk_234) * 4));
              pu16 = (uint16_t *)
                        (i8 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_240 + stk_234) * 4) +
                        stk_248 * 2);
              for (i2 = i14; i2 != 0; i2 = i2 + -1) {
                if (*pb13 != 0) {
                  u4 = stk_250[*pb13];
                  u3 = *pu16 >> 1;
                  *pu16 = (u3 & 0x3e0) + (u4 & 0x7e0) | (u3 & 0x7800) + (u4 & 0xf800)
                             | (u3 & 0xf) + (u4 & 0x1f);
                }
                pu16 = pu16 + 1;
                pb13 = pb13 + 1;
              }
              stk_234 = stk_234 + 1;
            } while (stk_234 < i12);
          }
        }
        else if (arg5 + arg6 < 0x101) {
          stk_234 = 0;
          if (0 < i12) {
            do {
              pb13 = (uint8_t *)(stk_24c +
                                i7 + *(int *)(sprite[0xb] + (stk_244 + stk_234) * 4));
              pu16 = (uint16_t *)
                        (i8 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_240 + stk_234) * 4) +
                        stk_248 * 2);
              for (i2 = i14; i2 != 0; i2 = i2 + -1) {
                if (*pb13 != 0) {
                  u4 = stk_250[*pb13];
                  u15 = (uint32_t)*pu16;
                  *pu16 = ((uint16_t)((u15 & 0x7e0) * arg6 >> 8) & 0x7e0) + (u4 & 0x7e0) |
                             ((uint16_t)((u15 & 0xf800) * arg6 >> 8) & 0xf800) +
                             (u4 & 0xf800) |
                             ((uint16_t)((u15 & 0x1f) * arg6 >> 8) & 0x1f) + (u4 & 0x1f);
                }
                pu16 = pu16 + 1;
                pb13 = pb13 + 1;
              }
              stk_234 = stk_234 + 1;
            } while (stk_234 < i12);
          }
        }
        else if (arg6 == 0x80) {
          stk_234 = 0;
          if (0 < i12) {
            do {
              pb13 = (uint8_t *)(stk_24c +
                                i7 + *(int *)(sprite[0xb] + (stk_244 + stk_234) * 4));
              pu16 = (uint16_t *)
                        (i8 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_240 + stk_234) * 4) +
                        stk_248 * 2);
              for (i2 = i14; i2 != 0; i2 = i2 + -1) {
                if (*pb13 != 0) {
                  u10 = (uint32_t)stk_250[*pb13];
                  u11 = (uint32_t)(*pu16 >> 1);
                  u15 = (u11 & 0x7800) + (u10 & 0xf800);
                  if (0xf800 < u15) {
                    u15 = 0xf800;
                  }
                  u1 = (u11 & 0x3e0) + (u10 & 0x7e0);
                  u4 = (uint16_t)u1;
                  if (0x7e0 < u1) {
                    u4 = 0x7e0;
                  }
                  u10 = (u11 & 0xf) + (u10 & 0x1f);
                  u3 = (uint16_t)u10;
                  if (0x1f < u10) {
                    u3 = 0x1f;
                  }
                  *pu16 = u4 | (uint16_t)u15 | u3;
                }
                pu16 = pu16 + 1;
                pb13 = pb13 + 1;
              }
              stk_234 = stk_234 + 1;
            } while (stk_234 < i12);
          }
        }
        else {
          stk_234 = 0;
          if (0 < i12) {
            do {
              pb13 = (uint8_t *)(stk_24c +
                                i7 + *(int *)(sprite[0xb] + (stk_244 + stk_234) * 4));
              pu16 = (uint16_t *)
                        (i8 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_240 + stk_234) * 4) +
                        stk_248 * 2);
              for (i2 = i14; i2 != 0; i2 = i2 + -1) {
                if (*pb13 != 0) {
                  u10 = (uint32_t)stk_250[*pb13];
                  u11 = (uint32_t)*pu16;
                  u15 = ((u11 & 0xf800) * arg6 >> 8 & 0xf800) + (u10 & 0xf800);
                  if (0xf800 < u15) {
                    u15 = 0xf800;
                  }
                  u1 = ((u11 & 0x7e0) * arg6 >> 8 & 0x7e0) + (u10 & 0x7e0);
                  u4 = (uint16_t)u1;
                  if (0x7e0 < u1) {
                    u4 = 0x7e0;
                  }
                  u10 = ((u11 & 0x1f) * arg6 >> 8 & 0x1f) + (u10 & 0x1f);
                  u3 = (uint16_t)u10;
                  if (0x1f < u10) {
                    u3 = 0x1f;
                  }
                  *pu16 = u4 | (uint16_t)u15 | u3;
                }
                pu16 = pu16 + 1;
                pb13 = pb13 + 1;
              }
              stk_234 = stk_234 + 1;
            } while (stk_234 < i12);
          }
        }
        SpriteDecompUnlockData();
      }
    }
  }
  return;
}
#undef stk_250
#undef stk_24c
#undef stk_248
#undef stk_244
#undef stk_240
#undef stk_234
#undef stk_230
#undef stk_21c

/* W_PutSpriteTransAddMirH8to16_B @ 0x080638c0, 2323 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended additively (colour 0 transparent), mirrored horizontally, with
 * explicit source and destination alpha (256 = full). Clipped to the window
 * set by W_Define. This is the pixel loop: it reads the 8-bit sprite rows
 * through the sprite's palette converted to 16-bit colours and writes 16-bit
 * pixels.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *   arg5         int
 *   arg6         int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteMirH8to16,
 *        W_PutSpriteTransAddMirH8to16, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * C library: memset
 * Called by: W_PutSpriteTransAddMirH_B, W_ScaleSpriteTransAddMirH8to16_B
 *
 * Elecbyte file: src/lib/spr16add.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x260 bytes,
 *       8 variables), because their address is taken.
 */
void W_PutSpriteTransAddMirH8to16_B
               (int *sprites,int index,int x,int y,int arg5,int arg6)

{
  uint32_t u1;
  int i2;
  int i3;
  uint16_t u4;
  uint16_t u5;
  int *sprite;
  int sprite2;
  int i8;
  int i9;
  int i10;
  int *sprite3;
  uint8_t *pb12;
  uint32_t u13;
  uint32_t u14;
  int i15;
  uint32_t u16;
  uint16_t *pu17;
  unsigned char frame[0x260] __attribute__((aligned(16)));
#define stk_254 (*(uint16_t **)(frame + 0xc))
#define stk_24c (*(int *)(frame + 0x14))
#define stk_248 (*(int *)(frame + 0x18))
#define stk_244 (*(int *)(frame + 0x1c))
#define stk_240 (*(int *)(frame + 0x20))
#define stk_234 (*(int *)(frame + 0x2c))
#define stk_230 (*(int *)(frame + 0x30))
#define stk_21c (*(uint16_t (*)[262])(frame + 0x44))
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_244 = 0;
  stk_24c = 0;
  if ((arg5 == 0x100) && (arg6 == 0)) {
    W_PutSpriteMirH8to16(sprites,index,x,y);
  }
  else if ((arg5 == 0x100) && (arg6 == 0x100)) {
    W_PutSpriteTransAddMirH8to16(sprites,index,x,y);
  }
  else if ((arg5 != 0) || (arg6 != 0x100)) {
    i3 = *sprite;
    i8 = (sprite[2] - i3) + 1 + x;
    i15 = y - sprite[3];
    if ((i15 <= W_y2) &&
       (((W_y1 < sprite[1] + i15 && (i8 <= W_x2)) && (W_x1 < i3 + i8)))) {
      stk_240 = i15;
      if (i15 < W_y1) {
        stk_240 = W_y1;
        stk_244 = W_y1 - i15;
      }
      i15 = sprite[1] + i15 + -1;
      if (W_y2 < i15) {
        i15 = W_y2;
      }
      stk_248 = i8;
      if (i8 < W_x1) {
        stk_248 = W_x1;
        stk_24c = W_x1 - i8;
      }
      i8 = i3 + i8 + -1;
      if (W_x2 < i8) {
        i8 = W_x2;
      }
      i8 = (i8 - stk_248) + 1;
      i15 = (i15 - stk_240) + 1;
      if (((0 < i8) && (0 < i15)) &&
         (i9 = SpriteDecompGetAndLockData(sprites,index), i9 != 0)) {
        i10 = SpriteDecompGetData(V_Current,V_CurrentIdx);
        sprite3 = (int *)sprites[5];
        if (sprite3 == (int *)0x0) {
          sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
        }
        else {
          EBPalUpdate(sprite3);
        }
        pu17 = (uint16_t *)(sprite3 + 0x17);
        stk_254 = pu17;
        if (arg5 != 0x100) {
          stk_254 = stk_21c;
          if (arg5 == 0) {
            memset(stk_21c,0,sprite[5] * 2);
          }
          else if (arg5 == 0x80) {
            stk_230 = 1;
            i2 = sprite[5];
            if (1 < i2) {
              do {
                stk_21c[stk_230] = pu17[stk_230] >> 1 & 0xfbef;
                stk_230 = stk_230 + 1;
              } while (stk_230 < i2);
            }
          }
          else {
            stk_230 = 1;
            i2 = sprite[5];
            if (1 < i2) {
              do {
                u16 = (uint32_t)pu17[stk_230];
                stk_21c[stk_230] =
                     (uint16_t)((u16 & 0xf800) * arg5 >> 8) & 0xf800 |
                     (uint16_t)((u16 & 0x7e0) * arg5 >> 8) & 0x7e0 |
                     (uint16_t)((u16 & 0x1f) * arg5 >> 8) & 0x1f;
                stk_230 = stk_230 + 1;
              } while (stk_230 < i2);
            }
          }
        }
        if (arg6 == 0) {
          stk_234 = 0;
          if (0 < i15) {
            sprite = (int *)(stk_244 * 4 + sprite[0xb]);
            sprite3 = (int *)(stk_240 * 4 + *(int *)(sprite2 + 0x2c));
            do {
              pb12 = (uint8_t *)((i9 + *sprite + i3) - stk_24c);
              pu17 = (uint16_t *)(i10 + *sprite3 + stk_248 * 2);
              for (sprite2 = i8; sprite2 != 0; sprite2 = sprite2 + -1) {
                pb12 = pb12 + -1;
                if (*pb12 != 0) {
                  *pu17 = stk_254[*pb12];
                }
                pu17 = pu17 + 1;
              }
              stk_234 = stk_234 + 1;
              sprite = sprite + 1;
              sprite3 = sprite3 + 1;
            } while (stk_234 < i15);
          }
        }
        else if ((arg5 + arg6 < 0x101) && (arg6 == 0x80)) {
          stk_234 = 0;
          if (0 < i15) {
            do {
              pb12 = (uint8_t *)((i9 + *(int *)(sprite[0xb] + (stk_244 + stk_234) * 4) +
                                 i3) - stk_24c);
              pu17 = (uint16_t *)
                        (i10 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_240 + stk_234) * 4) +
                        stk_248 * 2);
              for (i2 = i8; i2 != 0; i2 = i2 + -1) {
                pb12 = pb12 + -1;
                if (*pb12 != 0) {
                  u5 = stk_254[*pb12];
                  u4 = *pu17 >> 1;
                  *pu17 = (u4 & 0x3e0) + (u5 & 0x7e0) | (u4 & 0x7800) + (u5 & 0xf800)
                             | (u4 & 0xf) + (u5 & 0x1f);
                }
                pu17 = pu17 + 1;
              }
              stk_234 = stk_234 + 1;
            } while (stk_234 < i15);
          }
        }
        else if (arg5 + arg6 < 0x101) {
          stk_234 = 0;
          if (0 < i15) {
            do {
              pb12 = (uint8_t *)((i9 + *(int *)(sprite[0xb] + (stk_244 + stk_234) * 4) +
                                 i3) - stk_24c);
              pu17 = (uint16_t *)
                        (i10 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_240 + stk_234) * 4) +
                        stk_248 * 2);
              for (i2 = i8; i2 != 0; i2 = i2 + -1) {
                pb12 = pb12 + -1;
                if (*pb12 != 0) {
                  u5 = stk_254[*pb12];
                  u16 = (uint32_t)*pu17;
                  *pu17 = ((uint16_t)((u16 & 0x7e0) * arg6 >> 8) & 0x7e0) + (u5 & 0x7e0) |
                             ((uint16_t)((u16 & 0xf800) * arg6 >> 8) & 0xf800) +
                             (u5 & 0xf800) |
                             ((uint16_t)((u16 & 0x1f) * arg6 >> 8) & 0x1f) + (u5 & 0x1f);
                }
                pu17 = pu17 + 1;
              }
              stk_234 = stk_234 + 1;
            } while (stk_234 < i15);
          }
        }
        else if (arg6 == 0x80) {
          stk_234 = 0;
          if (0 < i15) {
            do {
              pb12 = (uint8_t *)((i9 + *(int *)(sprite[0xb] + (stk_244 + stk_234) * 4) +
                                 i3) - stk_24c);
              pu17 = (uint16_t *)
                        (i10 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_240 + stk_234) * 4) +
                        stk_248 * 2);
              for (i2 = i8; i2 != 0; i2 = i2 + -1) {
                pb12 = pb12 + -1;
                if (*pb12 != 0) {
                  u13 = (uint32_t)stk_254[*pb12];
                  u14 = (uint32_t)(*pu17 >> 1);
                  u16 = (u14 & 0x7800) + (u13 & 0xf800);
                  if (0xf800 < u16) {
                    u16 = 0xf800;
                  }
                  u1 = (u14 & 0x3e0) + (u13 & 0x7e0);
                  u5 = (uint16_t)u1;
                  if (0x7e0 < u1) {
                    u5 = 0x7e0;
                  }
                  u13 = (u14 & 0xf) + (u13 & 0x1f);
                  u4 = (uint16_t)u13;
                  if (0x1f < u13) {
                    u4 = 0x1f;
                  }
                  *pu17 = u5 | (uint16_t)u16 | u4;
                }
                pu17 = pu17 + 1;
              }
              stk_234 = stk_234 + 1;
            } while (stk_234 < i15);
          }
        }
        else {
          stk_234 = 0;
          if (0 < i15) {
            do {
              pb12 = (uint8_t *)((i9 + *(int *)(sprite[0xb] + (stk_244 + stk_234) * 4) +
                                 i3) - stk_24c);
              pu17 = (uint16_t *)
                        (i10 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_240 + stk_234) * 4) +
                        stk_248 * 2);
              for (i2 = i8; i2 != 0; i2 = i2 + -1) {
                pb12 = pb12 + -1;
                if (*pb12 != 0) {
                  u13 = (uint32_t)stk_254[*pb12];
                  u14 = (uint32_t)*pu17;
                  u16 = ((u14 & 0xf800) * arg6 >> 8 & 0xf800) + (u13 & 0xf800);
                  if (0xf800 < u16) {
                    u16 = 0xf800;
                  }
                  u1 = ((u14 & 0x7e0) * arg6 >> 8 & 0x7e0) + (u13 & 0x7e0);
                  u5 = (uint16_t)u1;
                  if (0x7e0 < u1) {
                    u5 = 0x7e0;
                  }
                  u13 = ((u14 & 0x1f) * arg6 >> 8 & 0x1f) + (u13 & 0x1f);
                  u4 = (uint16_t)u13;
                  if (0x1f < u13) {
                    u4 = 0x1f;
                  }
                  *pu17 = u5 | (uint16_t)u16 | u4;
                }
                pu17 = pu17 + 1;
              }
              stk_234 = stk_234 + 1;
            } while (stk_234 < i15);
          }
        }
        SpriteDecompUnlockData();
      }
    }
  }
  return;
}
#undef stk_254
#undef stk_24c
#undef stk_248
#undef stk_244
#undef stk_240
#undef stk_234
#undef stk_230
#undef stk_21c

/* W_PutSpriteTransAddMirV8to16_B @ 0x080641e0, 2323 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended additively (colour 0 transparent), mirrored vertically, with
 * explicit source and destination alpha (256 = full). Clipped to the window
 * set by W_Define. This is the pixel loop: it reads the 8-bit sprite rows
 * through the sprite's palette converted to 16-bit colours and writes 16-bit
 * pixels.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *   arg5         int
 *   arg6         int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteMirV8to16,
 *        W_PutSpriteTransAddMirV8to16, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * C library: memset
 * Called by: W_PutSpriteTransAddMirV_B, W_ScaleSpriteTransAddMirV8to16_B
 *
 * Elecbyte file: src/lib/spr16add.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x260 bytes,
 *       8 variables), because their address is taken.
 */
void W_PutSpriteTransAddMirV8to16_B
               (int *sprites,int index,int x,int y,int arg5,int arg6)

{
  uint32_t u1;
  int i2;
  int i3;
  uint16_t u4;
  uint16_t u5;
  int *sprite;
  int sprite2;
  int i8;
  int i9;
  int *sprite3;
  uint32_t u11;
  uint32_t u12;
  int i13;
  uint8_t *pb14;
  int i15;
  uint32_t u16;
  uint16_t *pu17;
  unsigned char frame[0x260] __attribute__((aligned(16)));
#define stk_254 (*(uint16_t **)(frame + 0xc))
#define stk_24c (*(int *)(frame + 0x14))
#define stk_248 (*(int *)(frame + 0x18))
#define stk_244 (*(int *)(frame + 0x1c))
#define stk_240 (*(int *)(frame + 0x20))
#define stk_234 (*(int *)(frame + 0x2c))
#define stk_230 (*(int *)(frame + 0x30))
#define stk_21c (*(uint16_t (*)[262])(frame + 0x44))
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_244 = 0;
  stk_24c = 0;
  if ((arg5 == 0x100) && (arg6 == 0)) {
    W_PutSpriteMirV8to16(sprites,index,x,y);
  }
  else if ((arg5 == 0x100) && (arg6 == 0x100)) {
    W_PutSpriteTransAddMirV8to16(sprites,index,x,y);
  }
  else if ((arg5 != 0) || (arg6 != 0x100)) {
    i2 = sprite[1];
    i15 = x - sprite[2];
    i13 = (sprite[3] - i2) + 1 + y;
    if ((i13 <= W_y2) &&
       (((W_y1 < i2 + i13 && (i15 <= W_x2)) && (W_x1 < *sprite + i15)))) {
      stk_240 = i13;
      if (i13 < W_y1) {
        stk_240 = W_y1;
        stk_244 = W_y1 - i13;
      }
      i13 = i2 + i13 + -1;
      if (W_y2 < i13) {
        i13 = W_y2;
      }
      stk_248 = i15;
      if (i15 < W_x1) {
        stk_248 = W_x1;
        stk_24c = W_x1 - i15;
      }
      i15 = *sprite + i15 + -1;
      if (W_x2 < i15) {
        i15 = W_x2;
      }
      i15 = (i15 - stk_248) + 1;
      i13 = (i13 - stk_240) + 1;
      if (((0 < i15) && (0 < i13)) &&
         (i8 = SpriteDecompGetAndLockData(sprites,index), i8 != 0)) {
        i9 = SpriteDecompGetData(V_Current,V_CurrentIdx);
        sprite3 = (int *)sprites[5];
        if (sprite3 == (int *)0x0) {
          sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
        }
        else {
          EBPalUpdate(sprite3);
        }
        pu17 = (uint16_t *)(sprite3 + 0x17);
        stk_254 = pu17;
        if (arg5 != 0x100) {
          stk_254 = stk_21c;
          if (arg5 == 0) {
            memset(stk_21c,0,sprite[5] * 2);
          }
          else if (arg5 == 0x80) {
            stk_230 = 1;
            i3 = sprite[5];
            if (1 < i3) {
              do {
                stk_21c[stk_230] = pu17[stk_230] >> 1 & 0xfbef;
                stk_230 = stk_230 + 1;
              } while (stk_230 < i3);
            }
          }
          else {
            stk_230 = 1;
            i3 = sprite[5];
            if (1 < i3) {
              do {
                u16 = (uint32_t)pu17[stk_230];
                stk_21c[stk_230] =
                     (uint16_t)((u16 & 0xf800) * arg5 >> 8) & 0xf800 |
                     (uint16_t)((u16 & 0x7e0) * arg5 >> 8) & 0x7e0 |
                     (uint16_t)((u16 & 0x1f) * arg5 >> 8) & 0x1f;
                stk_230 = stk_230 + 1;
              } while (stk_230 < i3);
            }
          }
        }
        if (arg6 == 0) {
          stk_234 = 0;
          if (0 < i13) {
            i3 = sprite[0xb];
            sprite = (int *)(stk_240 * 4 + *(int *)(sprite2 + 0x2c));
            do {
              pb14 = (uint8_t *)(stk_24c +
                                i8 + *(int *)(i3 + -4 + ((i2 - stk_244) - stk_234) * 4)
                                );
              pu17 = (uint16_t *)(i9 + *sprite + stk_248 * 2);
              for (sprite2 = i15; sprite2 != 0; sprite2 = sprite2 + -1) {
                if (*pb14 != 0) {
                  *pu17 = stk_254[*pb14];
                }
                pu17 = pu17 + 1;
                pb14 = pb14 + 1;
              }
              stk_234 = stk_234 + 1;
              sprite = sprite + 1;
            } while (stk_234 < i13);
          }
        }
        else if ((arg5 + arg6 < 0x101) && (arg6 == 0x80)) {
          stk_234 = 0;
          if (0 < i13) {
            do {
              pb14 = (uint8_t *)(stk_24c +
                                i8 + *(int *)(sprite[0xb] + -4 +
                                                ((i2 - stk_244) - stk_234) * 4));
              pu17 = (uint16_t *)
                        (i9 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_240 + stk_234) * 4) +
                        stk_248 * 2);
              for (i3 = i15; i3 != 0; i3 = i3 + -1) {
                if (*pb14 != 0) {
                  u5 = stk_254[*pb14];
                  u4 = *pu17 >> 1;
                  *pu17 = (u4 & 0x3e0) + (u5 & 0x7e0) | (u4 & 0x7800) + (u5 & 0xf800)
                             | (u4 & 0xf) + (u5 & 0x1f);
                }
                pu17 = pu17 + 1;
                pb14 = pb14 + 1;
              }
              stk_234 = stk_234 + 1;
            } while (stk_234 < i13);
          }
        }
        else if (arg5 + arg6 < 0x101) {
          stk_234 = 0;
          if (0 < i13) {
            do {
              pb14 = (uint8_t *)(stk_24c +
                                i8 + *(int *)(sprite[0xb] + -4 +
                                                ((i2 - stk_244) - stk_234) * 4));
              pu17 = (uint16_t *)
                        (i9 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_240 + stk_234) * 4) +
                        stk_248 * 2);
              for (i3 = i15; i3 != 0; i3 = i3 + -1) {
                if (*pb14 != 0) {
                  u5 = stk_254[*pb14];
                  u16 = (uint32_t)*pu17;
                  *pu17 = ((uint16_t)((u16 & 0x7e0) * arg6 >> 8) & 0x7e0) + (u5 & 0x7e0) |
                             ((uint16_t)((u16 & 0xf800) * arg6 >> 8) & 0xf800) +
                             (u5 & 0xf800) |
                             ((uint16_t)((u16 & 0x1f) * arg6 >> 8) & 0x1f) + (u5 & 0x1f);
                }
                pu17 = pu17 + 1;
                pb14 = pb14 + 1;
              }
              stk_234 = stk_234 + 1;
            } while (stk_234 < i13);
          }
        }
        else if (arg6 == 0x80) {
          stk_234 = 0;
          if (0 < i13) {
            do {
              pb14 = (uint8_t *)(stk_24c +
                                i8 + *(int *)(sprite[0xb] + -4 +
                                                ((i2 - stk_244) - stk_234) * 4));
              pu17 = (uint16_t *)
                        (i9 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_240 + stk_234) * 4) +
                        stk_248 * 2);
              for (i3 = i15; i3 != 0; i3 = i3 + -1) {
                if (*pb14 != 0) {
                  u11 = (uint32_t)stk_254[*pb14];
                  u12 = (uint32_t)(*pu17 >> 1);
                  u16 = (u12 & 0x7800) + (u11 & 0xf800);
                  if (0xf800 < u16) {
                    u16 = 0xf800;
                  }
                  u1 = (u12 & 0x3e0) + (u11 & 0x7e0);
                  u5 = (uint16_t)u1;
                  if (0x7e0 < u1) {
                    u5 = 0x7e0;
                  }
                  u11 = (u12 & 0xf) + (u11 & 0x1f);
                  u4 = (uint16_t)u11;
                  if (0x1f < u11) {
                    u4 = 0x1f;
                  }
                  *pu17 = u5 | (uint16_t)u16 | u4;
                }
                pu17 = pu17 + 1;
                pb14 = pb14 + 1;
              }
              stk_234 = stk_234 + 1;
            } while (stk_234 < i13);
          }
        }
        else {
          stk_234 = 0;
          if (0 < i13) {
            do {
              pb14 = (uint8_t *)(stk_24c +
                                i8 + *(int *)(sprite[0xb] + -4 +
                                                ((i2 - stk_244) - stk_234) * 4));
              pu17 = (uint16_t *)
                        (i9 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_240 + stk_234) * 4) +
                        stk_248 * 2);
              for (i3 = i15; i3 != 0; i3 = i3 + -1) {
                if (*pb14 != 0) {
                  u11 = (uint32_t)stk_254[*pb14];
                  u12 = (uint32_t)*pu17;
                  u16 = ((u12 & 0xf800) * arg6 >> 8 & 0xf800) + (u11 & 0xf800);
                  if (0xf800 < u16) {
                    u16 = 0xf800;
                  }
                  u1 = ((u12 & 0x7e0) * arg6 >> 8 & 0x7e0) + (u11 & 0x7e0);
                  u5 = (uint16_t)u1;
                  if (0x7e0 < u1) {
                    u5 = 0x7e0;
                  }
                  u11 = ((u12 & 0x1f) * arg6 >> 8 & 0x1f) + (u11 & 0x1f);
                  u4 = (uint16_t)u11;
                  if (0x1f < u11) {
                    u4 = 0x1f;
                  }
                  *pu17 = u5 | (uint16_t)u16 | u4;
                }
                pu17 = pu17 + 1;
                pb14 = pb14 + 1;
              }
              stk_234 = stk_234 + 1;
            } while (stk_234 < i13);
          }
        }
        SpriteDecompUnlockData();
      }
    }
  }
  return;
}
#undef stk_254
#undef stk_24c
#undef stk_248
#undef stk_244
#undef stk_240
#undef stk_234
#undef stk_230
#undef stk_21c

/* W_PutSpriteTransAddMirHV8to16_B @ 0x08064b00, 2355 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended additively (colour 0 transparent), mirrored horizontally and
 * vertically, with explicit source and destination alpha (256 = full).
 * Clipped to the window set by W_Define. This is the pixel loop: it reads
 * the 8-bit sprite rows through the sprite's palette converted to 16-bit
 * colours and writes 16-bit pixels.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *   arg5         int
 *   arg6         int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteMirHV8to16,
 *        W_PutSpriteTransAddMirHV8to16, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * C library: memset
 * Called by: W_PutSpriteTransAddMirHV_B, W_ScaleSpriteTransAddMirHV8to16_B
 *
 * Elecbyte file: src/lib/spr16add.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x260 bytes,
 *       8 variables), because their address is taken.
 */
void W_PutSpriteTransAddMirHV8to16_B
               (int *sprites,int index,int x,int y,int arg5,int arg6)

{
  uint32_t u1;
  int i2;
  int i3;
  int i4;
  int i5;
  uint16_t u6;
  uint16_t u7;
  int *sprite;
  int sprite2;
  int i10;
  int i11;
  int i12;
  int *sprite3;
  uint8_t *pb14;
  uint32_t u15;
  uint32_t u16;
  int i17;
  uint32_t u18;
  uint16_t *pu19;
  unsigned char frame[0x260] __attribute__((aligned(16)));
#define stk_258 (*(uint16_t **)(frame + 0x8))
#define stk_24c (*(int *)(frame + 0x14))
#define stk_248 (*(int *)(frame + 0x18))
#define stk_244 (*(int *)(frame + 0x1c))
#define stk_240 (*(int *)(frame + 0x20))
#define stk_234 (*(int *)(frame + 0x2c))
#define stk_230 (*(int *)(frame + 0x30))
#define stk_21c (*(uint16_t (*)[262])(frame + 0x44))
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_244 = 0;
  stk_24c = 0;
  if ((arg5 == 0x100) && (arg6 == 0)) {
    W_PutSpriteMirHV8to16(sprites,index,x,y);
  }
  else if ((arg5 == 0x100) && (arg6 == 0x100)) {
    W_PutSpriteTransAddMirHV8to16(sprites,index,x,y);
  }
  else if ((arg5 != 0) || (arg6 != 0x100)) {
    i3 = *sprite;
    i4 = sprite[1];
    i10 = (sprite[2] - i3) + 1 + x;
    i17 = (sprite[3] - i4) + 1 + y;
    if ((i17 <= W_y2) &&
       (((W_y1 < i4 + i17 && (i10 <= W_x2)) && (W_x1 < i3 + i10)))) {
      stk_240 = i17;
      if (i17 < W_y1) {
        stk_240 = W_y1;
        stk_244 = W_y1 - i17;
      }
      i17 = i4 + i17 + -1;
      if (W_y2 < i17) {
        i17 = W_y2;
      }
      stk_248 = i10;
      if (i10 < W_x1) {
        stk_248 = W_x1;
        stk_24c = W_x1 - i10;
      }
      i10 = i3 + i10 + -1;
      if (W_x2 < i10) {
        i10 = W_x2;
      }
      i10 = (i10 - stk_248) + 1;
      i17 = (i17 - stk_240) + 1;
      if (((0 < i10) && (0 < i17)) &&
         (i11 = SpriteDecompGetAndLockData(sprites,index), i11 != 0)) {
        i12 = SpriteDecompGetData(V_Current,V_CurrentIdx);
        sprite3 = (int *)sprites[5];
        if (sprite3 == (int *)0x0) {
          sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
        }
        else {
          EBPalUpdate(sprite3);
        }
        pu19 = (uint16_t *)(sprite3 + 0x17);
        stk_258 = pu19;
        if (arg5 != 0x100) {
          stk_258 = stk_21c;
          if (arg5 == 0) {
            memset(stk_21c,0,sprite[5] * 2);
          }
          else if (arg5 == 0x80) {
            stk_230 = 1;
            i5 = sprite[5];
            if (1 < i5) {
              do {
                stk_21c[stk_230] = pu19[stk_230] >> 1 & 0xfbef;
                stk_230 = stk_230 + 1;
              } while (stk_230 < i5);
            }
          }
          else {
            stk_230 = 1;
            i5 = sprite[5];
            if (1 < i5) {
              do {
                u18 = (uint32_t)pu19[stk_230];
                stk_21c[stk_230] =
                     (uint16_t)((u18 & 0xf800) * arg5 >> 8) & 0xf800 |
                     (uint16_t)((u18 & 0x7e0) * arg5 >> 8) & 0x7e0 |
                     (uint16_t)((u18 & 0x1f) * arg5 >> 8) & 0x1f;
                stk_230 = stk_230 + 1;
              } while (stk_230 < i5);
            }
          }
        }
        if (arg6 == 0) {
          stk_234 = 0;
          if (0 < i17) {
            i5 = sprite[0xb];
            do {
              pb14 = (uint8_t *)((i11 + *(int *)(i5 + -4 +
                                                   ((i4 - stk_244) - stk_234) * 4) + i3) -
                                stk_24c);
              pu19 = (uint16_t *)
                        (i12 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_240 + stk_234) * 4) +
                        stk_248 * 2);
              for (i2 = i10; i2 != 0; i2 = i2 + -1) {
                pb14 = pb14 + -1;
                if (*pb14 != 0) {
                  *pu19 = stk_258[*pb14];
                }
                pu19 = pu19 + 1;
              }
              stk_234 = stk_234 + 1;
            } while (stk_234 < i17);
          }
        }
        else if ((arg5 + arg6 < 0x101) && (arg6 == 0x80)) {
          stk_234 = 0;
          if (0 < i17) {
            do {
              pb14 = (uint8_t *)((i11 + *(int *)(sprite[0xb] + -4 +
                                                   ((i4 - stk_244) - stk_234) * 4) + i3) -
                                stk_24c);
              pu19 = (uint16_t *)
                        (i12 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_240 + stk_234) * 4) +
                        stk_248 * 2);
              for (i5 = i10; i5 != 0; i5 = i5 + -1) {
                pb14 = pb14 + -1;
                if (*pb14 != 0) {
                  u7 = stk_258[*pb14];
                  u6 = *pu19 >> 1;
                  *pu19 = (u6 & 0x3e0) + (u7 & 0x7e0) | (u6 & 0x7800) + (u7 & 0xf800)
                             | (u6 & 0xf) + (u7 & 0x1f);
                }
                pu19 = pu19 + 1;
              }
              stk_234 = stk_234 + 1;
            } while (stk_234 < i17);
          }
        }
        else if (arg5 + arg6 < 0x101) {
          stk_234 = 0;
          if (0 < i17) {
            do {
              pb14 = (uint8_t *)((i11 + *(int *)(sprite[0xb] + -4 +
                                                   ((i4 - stk_244) - stk_234) * 4) + i3) -
                                stk_24c);
              pu19 = (uint16_t *)
                        (i12 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_240 + stk_234) * 4) +
                        stk_248 * 2);
              for (i5 = i10; i5 != 0; i5 = i5 + -1) {
                pb14 = pb14 + -1;
                if (*pb14 != 0) {
                  u7 = stk_258[*pb14];
                  u18 = (uint32_t)*pu19;
                  *pu19 = ((uint16_t)((u18 & 0x7e0) * arg6 >> 8) & 0x7e0) + (u7 & 0x7e0) |
                             ((uint16_t)((u18 & 0xf800) * arg6 >> 8) & 0xf800) +
                             (u7 & 0xf800) |
                             ((uint16_t)((u18 & 0x1f) * arg6 >> 8) & 0x1f) + (u7 & 0x1f);
                }
                pu19 = pu19 + 1;
              }
              stk_234 = stk_234 + 1;
            } while (stk_234 < i17);
          }
        }
        else if (arg6 == 0x80) {
          stk_234 = 0;
          if (0 < i17) {
            do {
              pb14 = (uint8_t *)((i11 + *(int *)(sprite[0xb] + -4 +
                                                   ((i4 - stk_244) - stk_234) * 4) + i3) -
                                stk_24c);
              pu19 = (uint16_t *)
                        (i12 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_240 + stk_234) * 4) +
                        stk_248 * 2);
              for (i5 = i10; i5 != 0; i5 = i5 + -1) {
                pb14 = pb14 + -1;
                if (*pb14 != 0) {
                  u15 = (uint32_t)stk_258[*pb14];
                  u16 = (uint32_t)(*pu19 >> 1);
                  u18 = (u16 & 0x7800) + (u15 & 0xf800);
                  if (0xf800 < u18) {
                    u18 = 0xf800;
                  }
                  u1 = (u16 & 0x3e0) + (u15 & 0x7e0);
                  u7 = (uint16_t)u1;
                  if (0x7e0 < u1) {
                    u7 = 0x7e0;
                  }
                  u15 = (u16 & 0xf) + (u15 & 0x1f);
                  u6 = (uint16_t)u15;
                  if (0x1f < u15) {
                    u6 = 0x1f;
                  }
                  *pu19 = u7 | (uint16_t)u18 | u6;
                }
                pu19 = pu19 + 1;
              }
              stk_234 = stk_234 + 1;
            } while (stk_234 < i17);
          }
        }
        else {
          stk_234 = 0;
          if (0 < i17) {
            do {
              pb14 = (uint8_t *)((i11 + *(int *)(sprite[0xb] + -4 +
                                                   ((i4 - stk_244) - stk_234) * 4) + i3) -
                                stk_24c);
              pu19 = (uint16_t *)
                        (i12 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_240 + stk_234) * 4) +
                        stk_248 * 2);
              for (i5 = i10; i5 != 0; i5 = i5 + -1) {
                pb14 = pb14 + -1;
                if (*pb14 != 0) {
                  u15 = (uint32_t)stk_258[*pb14];
                  u16 = (uint32_t)*pu19;
                  u18 = ((u16 & 0xf800) * arg6 >> 8 & 0xf800) + (u15 & 0xf800);
                  if (0xf800 < u18) {
                    u18 = 0xf800;
                  }
                  u1 = ((u16 & 0x7e0) * arg6 >> 8 & 0x7e0) + (u15 & 0x7e0);
                  u7 = (uint16_t)u1;
                  if (0x7e0 < u1) {
                    u7 = 0x7e0;
                  }
                  u15 = ((u16 & 0x1f) * arg6 >> 8 & 0x1f) + (u15 & 0x1f);
                  u6 = (uint16_t)u15;
                  if (0x1f < u15) {
                    u6 = 0x1f;
                  }
                  *pu19 = u7 | (uint16_t)u18 | u6;
                }
                pu19 = pu19 + 1;
              }
              stk_234 = stk_234 + 1;
            } while (stk_234 < i17);
          }
        }
        SpriteDecompUnlockData();
      }
    }
  }
  return;
}
#undef stk_258
#undef stk_24c
#undef stk_248
#undef stk_244
#undef stk_240
#undef stk_234
#undef stk_230
#undef stk_21c

/* W_ScaleSpriteTransAdd8to16 @ 0x08065440, 2478 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended additively (colour 0 transparent). Clipped to the window
 * set by W_Define. This is the pixel loop: it reads the 8-bit sprite rows
 * through the sprite's palette converted to 16-bit colours and writes 16-bit
 * pixels.
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
 *        SpriteDecompUnlockData, W_PutSpriteTransAdd8to16
 * Called by: W_ScaleSpriteTransAdd, W_ScaleSpriteTransAdd8to16_B
 *
 * Elecbyte file: src/lib/spr16add.c
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 8 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleSpriteTransAdd8to16
               (int *sprites,int index,float x,float y,float arg5,float arg6)

{
  uint32_t u1;
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
  uint16_t *pu15;
  uint32_t u16;
  uint16_t u17;
  uint16_t u18;
  uint32_t u20;
  uint32_t u21;
  int stk_144;
  int stk_104;
  int stk_100;
  int stk_fc;
  int stk_f8;
  uint32_t stk_f4;
  uint32_t stk_f0;
  int stk_dc;
  uint32_t stk_54;
  uint32_t u19;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_fc = 0;
  stk_104 = 0;
  if ((0.0 < arg5) && (0.0 < arg6)) {
    i3 = *sprite;
    i11 = sprite[1];
    if ((((double)0.001) <= ABS((float80)i3 - arg5)) || (((double)0.001) <= ABS((float80)i11 - arg6))) {
      f4 = x - ((float80)sprite[2] * arg5) / (float80)i3;
      f5 = y - ((float80)sprite[3] * arg6) / (float80)i11;
      if ((((f5 <= (float)W_y2) && ((float)W_y1 < (f5 + arg6) - 0.5)) &&
          (f4 <= (float)W_x2)) && ((float)W_x1 < (f4 + arg5) - 0.5)) {
        stk_f8 = (int)X87_FIST32(X87_FLOOR(f5));
        f6 = (float)stk_f8;
        if (f5 <= f6) {
          stk_f0 = 0;
        }
        else {
          if ((float)stk_f8 < f5 - 0.5) {
            stk_f8 = stk_f8 + 1;
            f6 = (float)stk_f8;
          }
          stk_54 = (uint32_t)(int64_t)X87_FIST64((((float80)i11 * (f6 - f5)) / arg6) * 65536.0);
          stk_f0 = stk_54;
        }
        if (stk_f8 < W_y1) {
          i9 = W_y1 - stk_f8;
          stk_f8 = W_y1;
          stk_54 = (uint32_t)(int64_t)X87_FIST64(((float)(i9 * i11) / arg6) * 65536.0);
          stk_f0 = stk_f0 + stk_54;
        }
        i9 = (int)X87_FIST32(X87_FLOOR((f5 + arg6) - 0.5));
        if (W_y2 < i9) {
          i9 = W_y2;
        }
        if (i9 - stk_f8 != -1 && -1 < (i9 - stk_f8) + 1) {
          stk_100 = (int)X87_FIST32(X87_FLOOR(f4));
          f5 = (float)stk_100;
          if (f4 <= f5) {
            stk_f4 = 0;
          }
          else {
            if ((float)stk_100 < f4 - 0.5) {
              stk_100 = stk_100 + 1;
              f5 = (float)stk_100;
            }
            stk_54 = (uint32_t)(int64_t)X87_FIST64((((f5 - f4) * (float80)i3) / arg5) * 65536.0)
            ;
            stk_f4 = stk_54;
          }
          if (f4 < (float)W_x1) {
            i10 = W_x1 - stk_100;
            stk_100 = W_x1;
            stk_144 = (int)(int64_t)X87_FIST64(((float)(i10 * i3) / arg5) * 65536.0);
            stk_f4 = stk_f4 + stk_144;
          }
          i10 = (int)X87_FIST32(X87_FLOOR((f4 + arg5) - 0.5));
          if (W_x2 < i10) {
            i10 = W_x2;
          }
          stk_54 = (uint32_t)(int64_t)X87_FIST64((float)(i3 << 0x10) / arg5);
          i3 = (int)X87_FIST32((float)(i11 << 0x10) / arg6);
          for (; ((int)stk_f4 < 0 && (stk_100 <= i10)); stk_100 = stk_100 + 1) {
            stk_f4 = stk_f4 + stk_54;
          }
          i11 = (int)stk_f4 >> 0x10;
          if (i11 != 0) {
            stk_f4 = stk_f4 & 0xffff;
            stk_104 = i11;
          }
          for (; ((int)stk_f0 < 0 && (stk_f8 <= i9)); stk_f8 = stk_f8 + 1) {
            stk_f0 = stk_f0 + i3;
          }
          i11 = (int)stk_f0 >> 0x10;
          if (i11 != 0) {
            stk_f0 = stk_f0 & 0xffff;
            stk_fc = i11;
          }
          i11 = (i10 - stk_100) + 1;
          i9 = (i9 - stk_f8) + 1;
          if ((0 < i11) && (0 < i9)) {
            i10 = SpriteDecompGetAndLockData(sprites,index);
            if (i10 != 0) {
              i12 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              sprite3 = (int *)sprites[5];
              if (sprite3 == (int *)0x0) {
                sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
              }
              else {
                EBPalUpdate(sprite3);
              }
              stk_dc = 0;
              if (0 < i9) {
                do {
                  pb14 = (uint8_t *)(i10 + *(int *)(sprite[0xb] +
                                                      (((int)stk_f0 >> 0x10) + stk_fc) * 4) +
                                    stk_104);
                  pu15 = (uint16_t *)
                            (i12 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_f8 + stk_dc) * 4) +
                            stk_100 * 2);
                  u20 = stk_f4;
                  for (i2 = i11; i2 != 0; i2 = i2 + -1) {
                    if (*pb14 != 0) {
                      u19 = (uint32_t)*(uint16_t *)((int)sprite3 + (uint32_t)*pb14 * 2 + 0x5c);
                      u16 = (uint32_t)*pu15;
                      u21 = (u16 & 0xf800) + (u19 & 0xf800);
                      if (0xf800 < u21) {
                        u21 = 0xf800;
                      }
                      u1 = (u16 & 0x7e0) + (u19 & 0x7e0);
                      u17 = (uint16_t)u1;
                      if (0x7e0 < u1) {
                        u17 = 0x7e0;
                      }
                      u19 = (u19 & 0x1f) + (u16 & 0x1f);
                      u18 = (uint16_t)u19;
                      if (0x1f < u19) {
                        u18 = 0x1f;
                      }
                      *pu15 = (uint16_t)u21 | u17 | u18;
                    }
                    pu15 = pu15 + 1;
                    pb14 = pb14 + (u20 + stk_54 >> 0x10);
                    u20 = u20 + stk_54 & 0xffff;
                  }
                  stk_dc = stk_dc + 1;
                  stk_f0 = stk_f0 + i3;
                } while (stk_dc < i9);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteTransAdd8to16(sprites,index,(int)X87_FIST32(x),(int)X87_FIST32(y));
    }
  }
  return;
}

/* W_ScaleSpriteTransAddMirH8to16 @ 0x08065df0, 2480 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended additively (colour 0 transparent), mirrored horizontally.
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
 *        SpriteDecompUnlockData, W_PutSpriteTransAddMirH8to16
 * Called by: W_ScaleSpriteTransAddMirH, W_ScaleSpriteTransAddMirH8to16_B
 *
 * Elecbyte file: src/lib/spr16add.c
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 7 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleSpriteTransAddMirH8to16
               (int *sprites,int index,float x,float y,float arg5,float arg6)

{
  uint32_t u1;
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
  uint16_t *pu16;
  uint32_t u17;
  uint16_t u18;
  uint16_t u19;
  uint32_t u21;
  uint32_t u22;
  int stk_144;
  int stk_104;
  int stk_100;
  int stk_fc;
  int stk_f8;
  uint32_t stk_f4;
  uint32_t stk_f0;
  int stk_dc;
  uint32_t stk_54;
  uint32_t u20;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_fc = 0;
  stk_104 = 0;
  if ((0.0 < arg5) && (0.0 < arg6)) {
    i3 = *sprite;
    i4 = sprite[1];
    if ((((double)0.001) <= ABS((float80)i3 - arg5)) || (((double)0.001) <= ABS((float80)i4 - arg6))) {
      f5 = x - ((float)((i3 - sprite[2]) + -1) * arg5) / (float80)i3;
      f6 = y - ((float80)sprite[3] * arg6) / (float80)i4;
      if ((((f6 <= (float)W_y2) && ((float)W_y1 < (f6 + arg6) - 0.5)) &&
          (f5 <= (float)W_x2)) && ((float)W_x1 < (f5 + arg5) - 0.5)) {
        stk_f8 = (int)X87_FIST32(X87_FLOOR(f6));
        f7 = (float)stk_f8;
        if (f6 <= f7) {
          stk_f0 = 0;
        }
        else {
          if ((float)stk_f8 < f6 - 0.5) {
            stk_f8 = stk_f8 + 1;
            f7 = (float)stk_f8;
          }
          stk_54 = (uint32_t)(int64_t)X87_FIST64((((float80)i4 * (f7 - f6)) / arg6) * 65536.0);
          stk_f0 = stk_54;
        }
        if (stk_f8 < W_y1) {
          i10 = W_y1 - stk_f8;
          stk_f8 = W_y1;
          stk_54 = (uint32_t)(int64_t)X87_FIST64(((float)(i10 * i4) / arg6) * 65536.0);
          stk_f0 = stk_f0 + stk_54;
        }
        i10 = (int)X87_FIST32(X87_FLOOR((f6 + arg6) - 0.5));
        if (W_y2 < i10) {
          i10 = W_y2;
        }
        if (i10 - stk_f8 != -1 && -1 < (i10 - stk_f8) + 1) {
          stk_100 = (int)X87_FIST32(X87_FLOOR(f5));
          f6 = (float)stk_100;
          if (f5 <= f6) {
            stk_f4 = 0;
          }
          else {
            if ((float)stk_100 < f5 - 0.5) {
              stk_100 = stk_100 + 1;
              f6 = (float)stk_100;
            }
            stk_54 = (uint32_t)(int64_t)X87_FIST64((((f6 - f5) * (float80)i3) / arg5) * 65536.0)
            ;
            stk_f4 = stk_54;
          }
          if (f5 < (float)W_x1) {
            i11 = W_x1 - stk_100;
            stk_100 = W_x1;
            stk_144 = (int)(int64_t)X87_FIST64(((float)(i11 * i3) / arg5) * 65536.0);
            stk_f4 = stk_f4 + stk_144;
          }
          i11 = (int)X87_FIST32(X87_FLOOR((f5 + arg5) - 0.5));
          if (W_x2 < i11) {
            i11 = W_x2;
          }
          stk_144 = (int)(int64_t)X87_FIST64((float)(i3 << 0x10) / arg5);
          i4 = (int)X87_FIST32((float)(i4 << 0x10) / arg6);
          for (; ((int)stk_f4 < 0 && (stk_100 <= i11)); stk_100 = stk_100 + 1) {
            stk_f4 = stk_f4 + stk_144;
          }
          i12 = (int)stk_f4 >> 0x10;
          if (i12 != 0) {
            stk_f4 = stk_f4 & 0xffff;
            stk_104 = i12;
          }
          for (; ((int)stk_f0 < 0 && (stk_f8 <= i10)); stk_f8 = stk_f8 + 1) {
            stk_f0 = stk_f0 + i4;
          }
          i12 = (int)stk_f0 >> 0x10;
          if (i12 != 0) {
            stk_f0 = stk_f0 & 0xffff;
            stk_fc = i12;
          }
          i11 = (i11 - stk_100) + 1;
          i10 = (i10 - stk_f8) + 1;
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
              stk_dc = 0;
              if (0 < i10) {
                do {
                  pb15 = (uint8_t *)(((i12 + *(int *)(sprite[0xb] +
                                                        (((int)stk_f0 >> 0x10) + stk_fc) * 4) +
                                      i3) - stk_104) + -1);
                  pu16 = (uint16_t *)
                            (i13 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_f8 + stk_dc) * 4) +
                            stk_100 * 2);
                  u21 = stk_f4;
                  for (i2 = i11; i2 != 0; i2 = i2 + -1) {
                    if (*pb15 != 0) {
                      u20 = (uint32_t)*(uint16_t *)((int)sprite3 + (uint32_t)*pb15 * 2 + 0x5c);
                      u17 = (uint32_t)*pu16;
                      u22 = (u17 & 0xf800) + (u20 & 0xf800);
                      if (0xf800 < u22) {
                        u22 = 0xf800;
                      }
                      u1 = (u17 & 0x7e0) + (u20 & 0x7e0);
                      u18 = (uint16_t)u1;
                      if (0x7e0 < u1) {
                        u18 = 0x7e0;
                      }
                      u20 = (u20 & 0x1f) + (u17 & 0x1f);
                      u19 = (uint16_t)u20;
                      if (0x1f < u20) {
                        u19 = 0x1f;
                      }
                      *pu16 = (uint16_t)u22 | u18 | u19;
                    }
                    u22 = u21 + stk_144;
                    u21 = u22 & 0xffff;
                    pu16 = pu16 + 1;
                    pb15 = pb15 + -(u22 >> 0x10);
                  }
                  stk_dc = stk_dc + 1;
                  stk_f0 = stk_f0 + i4;
                } while (stk_dc < i10);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteTransAddMirH8to16(sprites,index,(int)X87_FIST32(x),(int)X87_FIST32(y));
    }
  }
  return;
}

/* W_ScaleSpriteTransAddMirV8to16 @ 0x080667a0, 2497 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended additively (colour 0 transparent), mirrored vertically.
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
 *        SpriteDecompUnlockData, W_PutSpriteTransAddMirV8to16
 * Called by: W_ScaleSpriteTransAddMirV, W_ScaleSpriteTransAddMirV8to16_B
 *
 * Elecbyte file: src/lib/spr16add.c
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 7 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleSpriteTransAddMirV8to16
               (int *sprites,int index,float x,float y,float arg5,float arg6)

{
  uint32_t u1;
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
  uint16_t *pu16;
  uint32_t u17;
  uint16_t u18;
  uint16_t u19;
  uint32_t u21;
  uint32_t u22;
  int stk_144;
  int stk_104;
  int stk_100;
  int stk_fc;
  int stk_f8;
  uint32_t stk_f4;
  uint32_t stk_f0;
  int stk_dc;
  uint32_t stk_54;
  uint32_t u20;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_fc = 0;
  stk_104 = 0;
  if ((0.0 < arg5) && (0.0 < arg6)) {
    i3 = *sprite;
    i4 = sprite[1];
    if ((((double)0.001) <= ABS((float80)i3 - arg5)) || (((double)0.001) <= ABS((float80)i4 - arg6))) {
      f5 = x - ((float80)sprite[2] * arg5) / (float80)i3;
      f6 = y - ((float)((i4 - sprite[3]) + -1) * arg6) / (float80)i4;
      if ((((f6 <= (float)W_y2) && ((float)W_y1 < (f6 + arg6) - 0.5)) &&
          (f5 <= (float)W_x2)) && ((float)W_x1 < (f5 + arg5) - 0.5)) {
        stk_f8 = (int)X87_FIST32(X87_FLOOR(f6));
        f7 = (float)stk_f8;
        if (f6 <= f7) {
          stk_f0 = 0;
        }
        else {
          if ((float)stk_f8 < f6 - 0.5) {
            stk_f8 = stk_f8 + 1;
            f7 = (float)stk_f8;
          }
          stk_54 = (uint32_t)(int64_t)X87_FIST64((((float80)i4 * (f7 - f6)) / arg6) * 65536.0);
          stk_f0 = stk_54;
        }
        if (stk_f8 < W_y1) {
          i10 = W_y1 - stk_f8;
          stk_f8 = W_y1;
          stk_54 = (uint32_t)(int64_t)X87_FIST64(((float)(i10 * i4) / arg6) * 65536.0);
          stk_f0 = stk_f0 + stk_54;
        }
        i10 = (int)X87_FIST32(X87_FLOOR((f6 + arg6) - 0.5));
        if (W_y2 < i10) {
          i10 = W_y2;
        }
        if (i10 - stk_f8 != -1 && -1 < (i10 - stk_f8) + 1) {
          stk_100 = (int)X87_FIST32(X87_FLOOR(f5));
          f6 = (float)stk_100;
          if (f5 <= f6) {
            stk_f4 = 0;
          }
          else {
            if ((float)stk_100 < f5 - 0.5) {
              stk_100 = stk_100 + 1;
              f6 = (float)stk_100;
            }
            stk_54 = (uint32_t)(int64_t)X87_FIST64((((f6 - f5) * (float80)i3) / arg5) * 65536.0)
            ;
            stk_f4 = stk_54;
          }
          if (f5 < (float)W_x1) {
            i11 = W_x1 - stk_100;
            stk_100 = W_x1;
            stk_144 = (int)(int64_t)X87_FIST64(((float)(i11 * i3) / arg5) * 65536.0);
            stk_f4 = stk_f4 + stk_144;
          }
          i11 = (int)X87_FIST32(X87_FLOOR((f5 + arg5) - 0.5));
          if (W_x2 < i11) {
            i11 = W_x2;
          }
          stk_54 = (uint32_t)(int64_t)X87_FIST64((float)(i3 << 0x10) / arg5);
          i3 = (int)X87_FIST32((float)(i4 << 0x10) / arg6);
          for (; ((int)stk_f4 < 0 && (stk_100 <= i11)); stk_100 = stk_100 + 1) {
            stk_f4 = stk_f4 + stk_54;
          }
          i12 = (int)stk_f4 >> 0x10;
          if (i12 != 0) {
            stk_f4 = stk_f4 & 0xffff;
            stk_104 = i12;
          }
          for (; ((int)stk_f0 < 0 && (stk_f8 <= i10)); stk_f8 = stk_f8 + 1) {
            stk_f0 = stk_f0 + i3;
          }
          i12 = (int)stk_f0 >> 0x10;
          if (i12 != 0) {
            stk_f0 = stk_f0 & 0xffff;
            stk_fc = i12;
          }
          i11 = (i11 - stk_100) + 1;
          i10 = (i10 - stk_f8) + 1;
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
              stk_dc = 0;
              if (0 < i10) {
                do {
                  pb15 = (uint8_t *)(i12 + *(int *)(sprite[0xb] + -4 +
                                                      ((i4 - stk_fc) - ((int)stk_f0 >> 0x10))
                                                      * 4) + stk_104);
                  pu16 = (uint16_t *)
                            (i13 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_f8 + stk_dc) * 4) +
                            stk_100 * 2);
                  u21 = stk_f4;
                  for (i2 = i11; i2 != 0; i2 = i2 + -1) {
                    if (*pb15 != 0) {
                      u20 = (uint32_t)*(uint16_t *)((int)sprite3 + (uint32_t)*pb15 * 2 + 0x5c);
                      u17 = (uint32_t)*pu16;
                      u22 = (u17 & 0xf800) + (u20 & 0xf800);
                      if (0xf800 < u22) {
                        u22 = 0xf800;
                      }
                      u1 = (u17 & 0x7e0) + (u20 & 0x7e0);
                      u18 = (uint16_t)u1;
                      if (0x7e0 < u1) {
                        u18 = 0x7e0;
                      }
                      u20 = (u20 & 0x1f) + (u17 & 0x1f);
                      u19 = (uint16_t)u20;
                      if (0x1f < u20) {
                        u19 = 0x1f;
                      }
                      *pu16 = (uint16_t)u22 | u18 | u19;
                    }
                    u22 = u21 + stk_54;
                    u21 = u22 & 0xffff;
                    pu16 = pu16 + 1;
                    pb15 = pb15 + (u22 >> 0x10);
                  }
                  stk_dc = stk_dc + 1;
                  stk_f0 = stk_f0 + i3;
                } while (stk_dc < i10);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteTransAddMirV8to16(sprites,index,(int)X87_FIST32(x),(int)X87_FIST32(y));
    }
  }
  return;
}

/* W_ScaleSpriteTransAddMirHV8to16 @ 0x08067170, 2494 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended additively (colour 0 transparent), mirrored horizontally
 * and vertically. Clipped to the window set by W_Define. This is the pixel
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
 *        SpriteDecompUnlockData, W_PutSpriteTransAddMirHV8to16
 * Called by: W_ScaleSpriteTransAddMirHV, W_ScaleSpriteTransAddMirHV8to16_B
 *
 * Elecbyte file: src/lib/spr16add.c
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 6 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleSpriteTransAddMirHV8to16
               (int *sprites,int index,float x,float y,float arg5,float arg6)

{
  uint32_t u1;
  int i2;
  int i3;
  int i4;
  int i5;
  float80 f6;
  float80 f7;
  float80 f8;
  int *sprite;
  int sprite2;
  int i11;
  int i12;
  int i13;
  int i14;
  int *sprite3;
  uint8_t *pb16;
  uint16_t *pu17;
  uint32_t u18;
  uint16_t u19;
  uint16_t u20;
  uint32_t u22;
  uint32_t u23;
  int stk_144;
  int stk_104;
  int stk_100;
  int stk_fc;
  int stk_f8;
  uint32_t stk_f4;
  uint32_t stk_f0;
  int stk_dc;
  uint32_t stk_54;
  uint32_t u21;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_fc = 0;
  stk_104 = 0;
  if ((0.0 < arg5) && (0.0 < arg6)) {
    i4 = *sprite;
    i5 = sprite[1];
    if ((((double)0.001) <= ABS((float80)i4 - arg5)) || (((double)0.001) <= ABS((float80)i5 - arg6))) {
      f6 = x - ((float)((i4 - sprite[2]) + -1) * arg5) / (float80)i4;
      f7 = y - ((float)((i5 - sprite[3]) + -1) * arg6) / (float80)i5;
      if ((((f7 <= (float)W_y2) && ((float)W_y1 < (f7 + arg6) - 0.5)) &&
          (f6 <= (float)W_x2)) && ((float)W_x1 < (f6 + arg5) - 0.5)) {
        stk_f8 = (int)X87_FIST32(X87_FLOOR(f7));
        f8 = (float)stk_f8;
        if (f7 <= f8) {
          stk_f0 = 0;
        }
        else {
          if ((float)stk_f8 < f7 - 0.5) {
            stk_f8 = stk_f8 + 1;
            f8 = (float)stk_f8;
          }
          stk_54 = (uint32_t)(int64_t)X87_FIST64((((float80)i5 * (f8 - f7)) / arg6) * 65536.0);
          stk_f0 = stk_54;
        }
        if (stk_f8 < W_y1) {
          i11 = W_y1 - stk_f8;
          stk_f8 = W_y1;
          stk_54 = (uint32_t)(int64_t)X87_FIST64(((float)(i11 * i5) / arg6) * 65536.0);
          stk_f0 = stk_f0 + stk_54;
        }
        i11 = (int)X87_FIST32(X87_FLOOR((f7 + arg6) - 0.5));
        if (W_y2 < i11) {
          i11 = W_y2;
        }
        if (i11 - stk_f8 != -1 && -1 < (i11 - stk_f8) + 1) {
          stk_100 = (int)X87_FIST32(X87_FLOOR(f6));
          f7 = (float)stk_100;
          if (f6 <= f7) {
            stk_f4 = 0;
          }
          else {
            if ((float)stk_100 < f6 - 0.5) {
              stk_100 = stk_100 + 1;
              f7 = (float)stk_100;
            }
            stk_54 = (uint32_t)(int64_t)X87_FIST64((((f7 - f6) * (float80)i4) / arg5) * 65536.0)
            ;
            stk_f4 = stk_54;
          }
          if (f6 < (float)W_x1) {
            i12 = W_x1 - stk_100;
            stk_100 = W_x1;
            stk_144 = (int)(int64_t)X87_FIST64(((float)(i12 * i4) / arg5) * 65536.0);
            stk_f4 = stk_f4 + stk_144;
          }
          i12 = (int)X87_FIST32(X87_FLOOR((f6 + arg5) - 0.5));
          if (W_x2 < i12) {
            i12 = W_x2;
          }
          stk_144 = (int)(int64_t)X87_FIST64((float)(i4 << 0x10) / arg5);
          i2 = (int)X87_FIST32((float)(i5 << 0x10) / arg6);
          for (; ((int)stk_f4 < 0 && (stk_100 <= i12)); stk_100 = stk_100 + 1) {
            stk_f4 = stk_f4 + stk_144;
          }
          i13 = (int)stk_f4 >> 0x10;
          if (i13 != 0) {
            stk_f4 = stk_f4 & 0xffff;
            stk_104 = i13;
          }
          for (; ((int)stk_f0 < 0 && (stk_f8 <= i11)); stk_f8 = stk_f8 + 1) {
            stk_f0 = stk_f0 + i2;
          }
          i13 = (int)stk_f0 >> 0x10;
          if (i13 != 0) {
            stk_f0 = stk_f0 & 0xffff;
            stk_fc = i13;
          }
          i12 = (i12 - stk_100) + 1;
          i11 = (i11 - stk_f8) + 1;
          if ((0 < i12) && (0 < i11)) {
            i13 = SpriteDecompGetAndLockData(sprites,index);
            if (i13 != 0) {
              i14 = SpriteDecompGetData(V_Current,V_CurrentIdx);
              sprite3 = (int *)sprites[5];
              if (sprite3 == (int *)0x0) {
                sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
              }
              else {
                EBPalUpdate(sprite3);
              }
              stk_dc = 0;
              if (0 < i11) {
                do {
                  pb16 = (uint8_t *)(((i13 + *(int *)(sprite[0xb] + -4 +
                                                        ((i5 - stk_fc) -
                                                        ((int)stk_f0 >> 0x10)) * 4) + i4) -
                                     stk_104) + -1);
                  pu17 = (uint16_t *)
                            (i14 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_f8 + stk_dc) * 4)
                            + stk_100 * 2);
                  u22 = stk_f4;
                  for (i3 = i12; i3 != 0; i3 = i3 + -1) {
                    if (*pb16 != 0) {
                      u21 = (uint32_t)*(uint16_t *)((int)sprite3 + (uint32_t)*pb16 * 2 + 0x5c);
                      u18 = (uint32_t)*pu17;
                      u23 = (u18 & 0xf800) + (u21 & 0xf800);
                      if (0xf800 < u23) {
                        u23 = 0xf800;
                      }
                      u1 = (u18 & 0x7e0) + (u21 & 0x7e0);
                      u19 = (uint16_t)u1;
                      if (0x7e0 < u1) {
                        u19 = 0x7e0;
                      }
                      u21 = (u21 & 0x1f) + (u18 & 0x1f);
                      u20 = (uint16_t)u21;
                      if (0x1f < u21) {
                        u20 = 0x1f;
                      }
                      *pu17 = (uint16_t)u23 | u19 | u20;
                    }
                    u23 = u22 + stk_144;
                    u22 = u23 & 0xffff;
                    pu17 = pu17 + 1;
                    pb16 = pb16 + -(u23 >> 0x10);
                  }
                  stk_f0 = stk_f0 + i2;
                  stk_dc = stk_dc + 1;
                } while (stk_dc < i11);
              }
              SpriteDecompUnlockData();
            }
          }
        }
      }
    }
    else {
      W_PutSpriteTransAddMirHV8to16(sprites,index,(int)X87_FIST32(x),(int)X87_FIST32(y));
    }
  }
  return;
}

/* W_ScaleSpriteTransAdd8to16_B @ 0x08067b30, 4291 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended additively (colour 0 transparent), with explicit source
 * and destination alpha (256 = full). Clipped to the window set by W_Define.
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
 *   arg7         int
 *   arg8         int
 *
 * Calls: SpriteArrayAccess, W_ScaleSprite8to16,
 *        W_ScaleSpriteTransAdd8to16, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData, W_PutSpriteTransAdd8to16_B
 * C library: memset
 * Called by: W_ScaleSpriteTransAdd_B
 *
 * Elecbyte file: src/lib/spr16add.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to NAN
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 8 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x350 bytes,
 *       12 variables), because their address is taken.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleSpriteTransAdd8to16_B
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               int arg7,int arg8)

{
  uint32_t u1;
  int i2;
  int i3;
  uint32_t u4;
  float80 f5;
  float80 f6;
  float80 f7;
  uint16_t u8;
  uint16_t u9;
  int *sprite;
  int sprite2;
  int i12;
  int i13;
  int i14;
  int i15;
  int *sprite3;
  uint8_t *pb17;
  uint32_t u18;
  uint16_t *pu19;
  uint32_t *pu20;
  uint32_t u21;
  uint32_t u22;
  unsigned char frame[0x350] __attribute__((aligned(16)));
#define stk_344 (*(int *)(frame + 0xc))
#define stk_308 (*(uint16_t **)(frame + 0x48))
#define stk_300 (*(int *)(frame + 0x50))
#define stk_2fc (*(int *)(frame + 0x54))
#define stk_2f8 (*(int *)(frame + 0x58))
#define stk_2f4 (*(int *)(frame + 0x5c))
#define stk_2f0 (*(uint32_t *)(frame + 0x60))
#define stk_2ec (*(uint32_t *)(frame + 0x64))
#define stk_2d8 (*(int *)(frame + 0x78))
#define stk_2d4 (*(int *)(frame + 0x7c))
#define stk_254 (*(uint32_t *)(frame + 0xfc))
#define stk_21c (*(uint16_t (*)[262])(frame + 0x134))
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_2f8 = 0;
  stk_300 = 0;
  if ((0.0 < arg5) && (0.0 < arg6)) {
    if ((arg7 == 0x100) && (arg8 == 0)) {
      W_ScaleSprite8to16(sprites,index,x,y,arg5,arg6);
    }
    else if ((arg7 == 0x100) && (arg8 == 0x100)) {
      W_ScaleSpriteTransAdd8to16(sprites,index,x,y,arg5,arg6);
    }
    else if ((arg7 != 0) || (arg8 != 0x100)) {
      i3 = *sprite;
      i14 = sprite[1];
      if ((((double)0.001) <= ABS((float80)i3 - arg5)) || (((double)0.001) <= ABS((float80)i14 - arg6))) {
        f5 = x - ((float80)sprite[2] * arg5) / (float80)i3;
        f6 = y - ((float80)sprite[3] * arg6) / (float80)i14;
        if ((f6 <= (float)W_y2) &&
           ((((float)W_y1 < (f6 + arg6) - 0.5 && (f5 <= (float)W_x2)) &&
            ((float)W_x1 < (f5 + arg5) - 0.5)))) {
          stk_2f4 = (int)X87_FIST32(X87_FLOOR(f6));
          f7 = (float)stk_2f4;
          if (f6 <= f7) {
            stk_2ec = 0;
          }
          else {
            if ((float)stk_2f4 < f6 - 0.5) {
              stk_2f4 = stk_2f4 + 1;
              f7 = (float)stk_2f4;
            }
            stk_254 = (uint32_t)(int64_t)
                              X87_FIST64((((float80)i14 * (f7 - f6)) / arg6) * 65536.0);
            stk_2ec = stk_254;
          }
          if (stk_2f4 < W_y1) {
            i12 = W_y1 - stk_2f4;
            stk_2f4 = W_y1;
            stk_254 = (uint32_t)(int64_t)X87_FIST64(((float)(i12 * i14) / arg6) * 65536.0);
            stk_2ec = stk_2ec + stk_254;
          }
          i12 = (int)X87_FIST32(X87_FLOOR((f6 + arg6) - 0.5));
          if (W_y2 < i12) {
            i12 = W_y2;
          }
          if (i12 - stk_2f4 != -1 && -1 < (i12 - stk_2f4) + 1) {
            stk_2fc = (int)X87_FIST32(X87_FLOOR(f5));
            f6 = (float)stk_2fc;
            if (f5 <= f6) {
              stk_2f0 = 0;
            }
            else {
              if ((float)stk_2fc < f5 - 0.5) {
                stk_2fc = stk_2fc + 1;
                f6 = (float)stk_2fc;
              }
              stk_254 = (uint32_t)(int64_t)
                                X87_FIST64((((f6 - f5) * (float80)i3) / arg5) * 65536.0);
              stk_2f0 = stk_254;
            }
            if (f5 < (float)W_x1) {
              i13 = W_x1 - stk_2fc;
              stk_2fc = W_x1;
              stk_344 = (int)(int64_t)X87_FIST64(((float)(i13 * i3) / arg5) * 65536.0);
              stk_2f0 = stk_2f0 + stk_344;
            }
            i13 = (int)X87_FIST32(X87_FLOOR((f5 + arg5) - 0.5));
            if (W_x2 < i13) {
              i13 = W_x2;
            }
            stk_344 = (int)(int64_t)X87_FIST64((float)(i3 << 0x10) / arg5);
            i3 = (int)X87_FIST32((float)(i14 << 0x10) / arg6);
            for (; ((int)stk_2f0 < 0 && (stk_2fc <= i13)); stk_2fc = stk_2fc + 1) {
              stk_2f0 = stk_2f0 + stk_344;
            }
            i14 = (int)stk_2f0 >> 0x10;
            if (i14 != 0) {
              stk_2f0 = stk_2f0 & 0xffff;
              stk_300 = i14;
            }
            for (; ((int)stk_2ec < 0 && (stk_2f4 <= i12)); stk_2f4 = stk_2f4 + 1) {
              stk_2ec = stk_2ec + i3;
            }
            i14 = (int)stk_2ec >> 0x10;
            if (i14 != 0) {
              stk_2ec = stk_2ec & 0xffff;
              stk_2f8 = i14;
            }
            i14 = (i13 - stk_2fc) + 1;
            i12 = (i12 - stk_2f4) + 1;
            if ((0 < i14) && (0 < i12)) {
              stk_2fc = stk_2fc * 2;
              i13 = SpriteDecompGetAndLockData(sprites,index);
              if (i13 != 0) {
                i15 = SpriteDecompGetData(V_Current,V_CurrentIdx);
                sprite3 = (int *)sprites[5];
                if (sprite3 == (int *)0x0) {
                  sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
                }
                else {
                  EBPalUpdate(sprite3);
                }
                pu19 = (uint16_t *)(sprite3 + 0x17);
                stk_308 = pu19;
                if (arg7 != 0x100) {
                  stk_308 = stk_21c;
                  if (arg7 == 0) {
                    memset(stk_21c,0,sprite[5] * 2);
                  }
                  else if (arg7 == 0x80) {
                    stk_2d4 = 1;
                    i2 = sprite[5];
                    if (1 < i2) {
                      do {
                        stk_21c[stk_2d4] = pu19[stk_2d4] >> 1 & 0xfbef;
                        stk_2d4 = stk_2d4 + 1;
                      } while (stk_2d4 < i2);
                    }
                  }
                  else {
                    stk_2d4 = 1;
                    i2 = sprite[5];
                    if (1 < i2) {
                      do {
                        u22 = (uint32_t)pu19[stk_2d4];
                        stk_21c[stk_2d4] =
                             (uint16_t)((u22 & 0xf800) * arg7 >> 8) & 0xf800 |
                             (uint16_t)((u22 & 0x7e0) * arg7 >> 8) & 0x7e0 |
                             (uint16_t)((u22 & 0x1f) * arg7 >> 8) & 0x1f;
                        stk_2d4 = stk_2d4 + 1;
                      } while (stk_2d4 < i2);
                    }
                  }
                }
                if (arg8 == 0) {
                  stk_2d8 = 0;
                  if (0 < i12) {
                    do {
                      pb17 = (uint8_t *)(i13 + *(int *)(sprite[0xb] +
                                                          (((int)stk_2ec >> 0x10) + stk_2f8) * 4
                                                          ) + stk_300);
                      pu19 = (uint16_t *)
                                (stk_2fc +
                                i15 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                 (stk_2f4 + stk_2d8) * 4));
                      u22 = stk_2f0;
                      for (i2 = i14; i2 != 0; i2 = i2 + -1) {
                        if (*pb17 != 0) {
                          *pu19 = stk_308[*pb17];
                        }
                        u21 = u22 + stk_344;
                        pu19 = pu19 + 1;
                        u22 = u21 & 0xffff;
                        pb17 = pb17 + (u21 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i3;
                    } while (stk_2d8 < i12);
                  }
                }
                else if ((arg8 + arg7 < 0x101) && (arg8 == 0x80)) {
                  stk_2d8 = 0;
                  if (0 < i12) {
                    do {
                      pb17 = (uint8_t *)(i13 + *(int *)(sprite[0xb] +
                                                          (((int)stk_2ec >> 0x10) + stk_2f8) * 4
                                                          ) + stk_300);
                      pu19 = (uint16_t *)
                                (stk_2fc +
                                i15 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                 (stk_2f4 + stk_2d8) * 4));
                      u22 = stk_2f0;
                      for (i2 = i14; i2 != 0; i2 = i2 + -1) {
                        if (*pb17 != 0) {
                          u9 = stk_308[*pb17];
                          u8 = (uint16_t)*(uint32_t *)pu19 >> 1;
                          *pu19 = (u8 & 0x3e0) + (u9 & 0x7e0) |
                                     (u8 & 0x7800) + (u9 & 0xf800) |
                                     (u8 & 0xf) + (u9 & 0x1f);
                        }
                        u21 = u22 + stk_344;
                        pu19 = pu19 + 1;
                        u22 = u21 & 0xffff;
                        pb17 = pb17 + (u21 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i3;
                    } while (stk_2d8 < i12);
                  }
                }
                else if (arg8 + arg7 < 0x101) {
                  stk_2d8 = 0;
                  if (0 < i12) {
                    do {
                      pb17 = (uint8_t *)(i13 + *(int *)(sprite[0xb] +
                                                          (((int)stk_2ec >> 0x10) + stk_2f8) * 4
                                                          ) + stk_300);
                      pu20 = (uint32_t *)(stk_2fc +
                                        i15 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                         (stk_2f4 + stk_2d8) * 4));
                      u22 = stk_2f0;
                      for (i2 = i14; i2 != 0; i2 = i2 + -1) {
                        if (*pb17 != 0) {
                          u9 = stk_308[*pb17];
                          u21 = *pu20;
                          *(uint16_t *)pu20 =
                               ((uint16_t)((u21 & 0x7e0) * arg8 >> 8) & 0x7e0) + (u9 & 0x7e0)
                               | ((uint16_t)((u21 & 0xf800) * arg8 >> 8) & 0xf800) +
                                 (u9 & 0xf800) |
                               ((uint16_t)((u21 & 0x1f) * arg8 >> 8) & 0x1f) + (u9 & 0x1f);
                        }
                        u21 = u22 + stk_344;
                        pu20 = (uint32_t *)((int)pu20 + 2);
                        u22 = u21 & 0xffff;
                        pb17 = pb17 + (u21 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i3;
                    } while (stk_2d8 < i12);
                  }
                }
                else if (arg8 == 0x80) {
                  stk_2d8 = 0;
                  if (0 < i12) {
                    do {
                      pb17 = (uint8_t *)(i13 + *(int *)(sprite[0xb] +
                                                          (((int)stk_2ec >> 0x10) + stk_2f8) * 4
                                                          ) + stk_300);
                      pu20 = (uint32_t *)(stk_2fc +
                                        i15 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                         (stk_2f4 + stk_2d8) * 4));
                      u22 = stk_2f0;
                      for (i2 = i14; i2 != 0; i2 = i2 + -1) {
                        if (*pb17 != 0) {
                          u18 = (uint32_t)stk_308[*pb17];
                          u4 = *pu20 >> 1;
                          u21 = (u4 & 0x7800) + (u18 & 0xf800);
                          if (0xf800 < u21) {
                            u21 = 0xf800;
                          }
                          u1 = (u4 & 0x3e0) + (u18 & 0x7e0);
                          u9 = (uint16_t)u1;
                          if (0x7e0 < u1) {
                            u9 = 0x7e0;
                          }
                          u4 = (u4 & 0xf) + (u18 & 0x1f);
                          u8 = (uint16_t)u4;
                          if (0x1f < u4) {
                            u8 = 0x1f;
                          }
                          *(uint16_t *)pu20 = u9 | (uint16_t)u21 | u8;
                        }
                        u21 = u22 + stk_344;
                        pu20 = (uint32_t *)((int)pu20 + 2);
                        u22 = u21 & 0xffff;
                        pb17 = pb17 + (u21 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i3;
                    } while (stk_2d8 < i12);
                  }
                }
                else {
                  stk_2d8 = 0;
                  if (0 < i12) {
                    do {
                      pb17 = (uint8_t *)(i13 + *(int *)(sprite[0xb] +
                                                          (((int)stk_2ec >> 0x10) + stk_2f8) * 4
                                                          ) + stk_300);
                      pu20 = (uint32_t *)(stk_2fc +
                                        i15 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                         (stk_2f4 + stk_2d8) * 4));
                      u22 = stk_2f0;
                      for (i2 = i14; i2 != 0; i2 = i2 + -1) {
                        if (*pb17 != 0) {
                          u18 = (uint32_t)stk_308[*pb17];
                          u4 = *pu20;
                          u21 = ((u4 & 0xf800) * arg8 >> 8 & 0xf800) + (u18 & 0xf800);
                          if (0xf800 < u21) {
                            u21 = 0xf800;
                          }
                          u1 = ((u4 & 0x7e0) * arg8 >> 8 & 0x7e0) + (u18 & 0x7e0);
                          u9 = (uint16_t)u1;
                          if (0x7e0 < u1) {
                            u9 = 0x7e0;
                          }
                          u4 = ((u4 & 0x1f) * arg8 >> 8 & 0x1f) + (u18 & 0x1f);
                          u8 = (uint16_t)u4;
                          if (0x1f < u4) {
                            u8 = 0x1f;
                          }
                          *(uint16_t *)pu20 = u9 | (uint16_t)u21 | u8;
                        }
                        u21 = u22 + stk_344;
                        pu20 = (uint32_t *)((int)pu20 + 2);
                        u22 = u21 & 0xffff;
                        pb17 = pb17 + (u21 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i3;
                    } while (stk_2d8 < i12);
                  }
                }
                SpriteDecompUnlockData();
              }
            }
          }
        }
      }
      else {
        W_PutSpriteTransAdd8to16_B
                  (sprites,index,(int)X87_FIST32(x),(int)X87_FIST32(y),arg7,arg8);
      }
    }
  }
  return;
}
#undef stk_344
#undef stk_308
#undef stk_300
#undef stk_2fc
#undef stk_2f8
#undef stk_2f4
#undef stk_2f0
#undef stk_2ec
#undef stk_2d8
#undef stk_2d4
#undef stk_254
#undef stk_21c

/* W_ScaleSpriteTransAddMirH8to16_B @ 0x08068c00, 4331 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended additively (colour 0 transparent), mirrored horizontally,
 * with explicit source and destination alpha (256 = full). Clipped to the
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
 *   arg7         int
 *   arg8         int
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteMirH8to16,
 *        W_ScaleSpriteTransAddMirH8to16, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData, W_PutSpriteTransAddMirH8to16_B
 * C library: memset
 * Called by: W_ScaleSpriteTransAddMirH_B
 *
 * Elecbyte file: src/lib/spr16add.c
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 7 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x350 bytes,
 *       12 variables), because their address is taken.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleSpriteTransAddMirH8to16_B
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               int arg7,int arg8)

{
  uint32_t u1;
  int i2;
  int i3;
  int i4;
  uint32_t u5;
  float80 f6;
  float80 f7;
  float80 f8;
  uint16_t u9;
  uint16_t u10;
  int *sprite;
  int sprite2;
  int i13;
  int i14;
  int i15;
  int i16;
  int *sprite3;
  uint8_t *pb18;
  uint32_t u19;
  uint16_t *pu20;
  uint32_t *pu21;
  uint32_t u22;
  uint32_t u23;
  unsigned char frame[0x350] __attribute__((aligned(16)));
#define stk_344 (*(int *)(frame + 0xc))
#define stk_308 (*(uint16_t **)(frame + 0x48))
#define stk_300 (*(int *)(frame + 0x50))
#define stk_2fc (*(int *)(frame + 0x54))
#define stk_2f8 (*(int *)(frame + 0x58))
#define stk_2f4 (*(int *)(frame + 0x5c))
#define stk_2f0 (*(uint32_t *)(frame + 0x60))
#define stk_2ec (*(uint32_t *)(frame + 0x64))
#define stk_2d8 (*(int *)(frame + 0x78))
#define stk_2d4 (*(int *)(frame + 0x7c))
#define stk_254 (*(uint32_t *)(frame + 0xfc))
#define stk_21c (*(uint16_t (*)[262])(frame + 0x134))
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_2f8 = 0;
  stk_300 = 0;
  if ((0.0 < arg5) && (0.0 < arg6)) {
    if ((arg7 == 0x100) && (arg8 == 0)) {
      W_ScaleSpriteMirH8to16(sprites,index,x,y,arg5,arg6);
    }
    else if ((arg7 == 0x100) && (arg8 == 0x100)) {
      W_ScaleSpriteTransAddMirH8to16(sprites,index,x,y,arg5,arg6);
    }
    else if ((arg7 != 0) || (arg8 != 0x100)) {
      i3 = *sprite;
      i4 = sprite[1];
      if ((((double)0.001) <= ABS((float80)i3 - arg5)) || (((double)0.001) <= ABS((float80)i4 - arg6))) {
        f6 = x - ((float)((i3 - sprite[2]) + -1) * arg5) / (float80)i3;
        f7 = y - ((float80)sprite[3] * arg6) / (float80)i4;
        if ((f7 <= (float)W_y2) &&
           ((((float)W_y1 < (f7 + arg6) - 0.5 && (f6 <= (float)W_x2)) &&
            ((float)W_x1 < (f6 + arg5) - 0.5)))) {
          stk_2f4 = (int)X87_FIST32(X87_FLOOR(f7));
          f8 = (float)stk_2f4;
          if (f7 <= f8) {
            stk_2ec = 0;
          }
          else {
            if ((float)stk_2f4 < f7 - 0.5) {
              stk_2f4 = stk_2f4 + 1;
              f8 = (float)stk_2f4;
            }
            stk_254 = (uint32_t)(int64_t)
                              X87_FIST64((((float80)i4 * (f8 - f7)) / arg6) * 65536.0);
            stk_2ec = stk_254;
          }
          if (stk_2f4 < W_y1) {
            i13 = W_y1 - stk_2f4;
            stk_2f4 = W_y1;
            stk_254 = (uint32_t)(int64_t)X87_FIST64(((float)(i13 * i4) / arg6) * 65536.0);
            stk_2ec = stk_2ec + stk_254;
          }
          i13 = (int)X87_FIST32(X87_FLOOR((f7 + arg6) - 0.5));
          if (W_y2 < i13) {
            i13 = W_y2;
          }
          if (i13 - stk_2f4 != -1 && -1 < (i13 - stk_2f4) + 1) {
            stk_2fc = (int)X87_FIST32(X87_FLOOR(f6));
            f7 = (float)stk_2fc;
            if (f6 <= f7) {
              stk_2f0 = 0;
            }
            else {
              if ((float)stk_2fc < f6 - 0.5) {
                stk_2fc = stk_2fc + 1;
                f7 = (float)stk_2fc;
              }
              stk_254 = (uint32_t)(int64_t)
                                X87_FIST64((((f7 - f6) * (float80)i3) / arg5) * 65536.0);
              stk_2f0 = stk_254;
            }
            if (f6 < (float)W_x1) {
              i14 = W_x1 - stk_2fc;
              stk_2fc = W_x1;
              stk_344 = (int)(int64_t)X87_FIST64(((float)(i14 * i3) / arg5) * 65536.0);
              stk_2f0 = stk_2f0 + stk_344;
            }
            i14 = (int)X87_FIST32(X87_FLOOR((f6 + arg5) - 0.5));
            if (W_x2 < i14) {
              i14 = W_x2;
            }
            stk_344 = (int)(int64_t)X87_FIST64((float)(i3 << 0x10) / arg5);
            i4 = (int)X87_FIST32((float)(i4 << 0x10) / arg6);
            for (; ((int)stk_2f0 < 0 && (stk_2fc <= i14)); stk_2fc = stk_2fc + 1) {
              stk_2f0 = stk_2f0 + stk_344;
            }
            i15 = (int)stk_2f0 >> 0x10;
            if (i15 != 0) {
              stk_2f0 = stk_2f0 & 0xffff;
              stk_300 = i15;
            }
            for (; ((int)stk_2ec < 0 && (stk_2f4 <= i13)); stk_2f4 = stk_2f4 + 1) {
              stk_2ec = stk_2ec + i4;
            }
            i15 = (int)stk_2ec >> 0x10;
            if (i15 != 0) {
              stk_2ec = stk_2ec & 0xffff;
              stk_2f8 = i15;
            }
            i14 = (i14 - stk_2fc) + 1;
            i13 = (i13 - stk_2f4) + 1;
            if ((0 < i14) && (0 < i13)) {
              stk_2fc = stk_2fc * 2;
              i15 = SpriteDecompGetAndLockData(sprites,index);
              if (i15 != 0) {
                i16 = SpriteDecompGetData(V_Current,V_CurrentIdx);
                sprite3 = (int *)sprites[5];
                if (sprite3 == (int *)0x0) {
                  sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
                }
                else {
                  EBPalUpdate(sprite3);
                }
                pu20 = (uint16_t *)(sprite3 + 0x17);
                stk_308 = pu20;
                if (arg7 != 0x100) {
                  stk_308 = stk_21c;
                  if (arg7 == 0) {
                    memset(stk_21c,0,sprite[5] * 2);
                  }
                  else if (arg7 == 0x80) {
                    stk_2d4 = 1;
                    i2 = sprite[5];
                    if (1 < i2) {
                      do {
                        stk_21c[stk_2d4] = pu20[stk_2d4] >> 1 & 0xfbef;
                        stk_2d4 = stk_2d4 + 1;
                      } while (stk_2d4 < i2);
                    }
                  }
                  else {
                    stk_2d4 = 1;
                    i2 = sprite[5];
                    if (1 < i2) {
                      do {
                        u23 = (uint32_t)pu20[stk_2d4];
                        stk_21c[stk_2d4] =
                             (uint16_t)((u23 & 0xf800) * arg7 >> 8) & 0xf800 |
                             (uint16_t)((u23 & 0x7e0) * arg7 >> 8) & 0x7e0 |
                             (uint16_t)((u23 & 0x1f) * arg7 >> 8) & 0x1f;
                        stk_2d4 = stk_2d4 + 1;
                      } while (stk_2d4 < i2);
                    }
                  }
                }
                if (arg8 == 0) {
                  stk_2d8 = 0;
                  if (0 < i13) {
                    do {
                      pb18 = (uint8_t *)(((i15 + *(int *)(sprite[0xb] +
                                                            (((int)stk_2ec >> 0x10) + stk_2f8) *
                                                            4) + i3) - stk_300) + -1);
                      pu20 = (uint16_t *)
                                (stk_2fc +
                                i16 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                 (stk_2f4 + stk_2d8) * 4));
                      u23 = stk_2f0;
                      for (i2 = i14; i2 != 0; i2 = i2 + -1) {
                        if (*pb18 != 0) {
                          *pu20 = stk_308[*pb18];
                        }
                        u22 = u23 + stk_344;
                        pu20 = pu20 + 1;
                        u23 = u22 & 0xffff;
                        pb18 = pb18 + -(u22 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i4;
                    } while (stk_2d8 < i13);
                  }
                }
                else if ((arg8 + arg7 < 0x101) && (arg8 == 0x80)) {
                  stk_2d8 = 0;
                  if (0 < i13) {
                    do {
                      pb18 = (uint8_t *)(((i15 + *(int *)(sprite[0xb] +
                                                            (((int)stk_2ec >> 0x10) + stk_2f8) *
                                                            4) + i3) - stk_300) + -1);
                      pu20 = (uint16_t *)
                                (stk_2fc +
                                i16 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                 (stk_2f4 + stk_2d8) * 4));
                      u23 = stk_2f0;
                      for (i2 = i14; i2 != 0; i2 = i2 + -1) {
                        if (*pb18 != 0) {
                          u10 = stk_308[*pb18];
                          u9 = (uint16_t)*(uint32_t *)pu20 >> 1;
                          *pu20 = (u9 & 0x3e0) + (u10 & 0x7e0) |
                                     (u9 & 0x7800) + (u10 & 0xf800) |
                                     (u9 & 0xf) + (u10 & 0x1f);
                        }
                        u22 = u23 + stk_344;
                        pu20 = pu20 + 1;
                        u23 = u22 & 0xffff;
                        pb18 = pb18 + -(u22 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i4;
                    } while (stk_2d8 < i13);
                  }
                }
                else if (arg8 + arg7 < 0x101) {
                  stk_2d8 = 0;
                  if (0 < i13) {
                    do {
                      pb18 = (uint8_t *)(((i15 + *(int *)(sprite[0xb] +
                                                            (((int)stk_2ec >> 0x10) + stk_2f8) *
                                                            4) + i3) - stk_300) + -1);
                      pu21 = (uint32_t *)(stk_2fc +
                                        i16 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                         (stk_2f4 + stk_2d8) * 4));
                      u23 = stk_2f0;
                      for (i2 = i14; i2 != 0; i2 = i2 + -1) {
                        if (*pb18 != 0) {
                          u10 = stk_308[*pb18];
                          u22 = *pu21;
                          *(uint16_t *)pu21 =
                               ((uint16_t)((u22 & 0x7e0) * arg8 >> 8) & 0x7e0) +
                               (u10 & 0x7e0) |
                               ((uint16_t)((u22 & 0xf800) * arg8 >> 8) & 0xf800) +
                               (u10 & 0xf800) |
                               ((uint16_t)((u22 & 0x1f) * arg8 >> 8) & 0x1f) + (u10 & 0x1f);
                        }
                        u22 = u23 + stk_344;
                        pu21 = (uint32_t *)((int)pu21 + 2);
                        u23 = u22 & 0xffff;
                        pb18 = pb18 + -(u22 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i4;
                    } while (stk_2d8 < i13);
                  }
                }
                else if (arg8 == 0x80) {
                  stk_2d8 = 0;
                  if (0 < i13) {
                    do {
                      pb18 = (uint8_t *)(((i15 + *(int *)(sprite[0xb] +
                                                            (((int)stk_2ec >> 0x10) + stk_2f8) *
                                                            4) + i3) - stk_300) + -1);
                      pu21 = (uint32_t *)(stk_2fc +
                                        i16 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                         (stk_2f4 + stk_2d8) * 4));
                      u23 = stk_2f0;
                      for (i2 = i14; i2 != 0; i2 = i2 + -1) {
                        if (*pb18 != 0) {
                          u19 = (uint32_t)stk_308[*pb18];
                          u5 = *pu21 >> 1;
                          u22 = (u5 & 0x7800) + (u19 & 0xf800);
                          if (0xf800 < u22) {
                            u22 = 0xf800;
                          }
                          u1 = (u5 & 0x3e0) + (u19 & 0x7e0);
                          u10 = (uint16_t)u1;
                          if (0x7e0 < u1) {
                            u10 = 0x7e0;
                          }
                          u5 = (u5 & 0xf) + (u19 & 0x1f);
                          u9 = (uint16_t)u5;
                          if (0x1f < u5) {
                            u9 = 0x1f;
                          }
                          *(uint16_t *)pu21 = u10 | (uint16_t)u22 | u9;
                        }
                        u22 = u23 + stk_344;
                        pu21 = (uint32_t *)((int)pu21 + 2);
                        u23 = u22 & 0xffff;
                        pb18 = pb18 + -(u22 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i4;
                    } while (stk_2d8 < i13);
                  }
                }
                else {
                  stk_2d8 = 0;
                  if (0 < i13) {
                    do {
                      pb18 = (uint8_t *)(((i15 + *(int *)(sprite[0xb] +
                                                            (((int)stk_2ec >> 0x10) + stk_2f8) *
                                                            4) + i3) - stk_300) + -1);
                      pu21 = (uint32_t *)(stk_2fc +
                                        i16 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                         (stk_2f4 + stk_2d8) * 4));
                      u23 = stk_2f0;
                      for (i2 = i14; i2 != 0; i2 = i2 + -1) {
                        if (*pb18 != 0) {
                          u19 = (uint32_t)stk_308[*pb18];
                          u5 = *pu21;
                          u22 = ((u5 & 0xf800) * arg8 >> 8 & 0xf800) + (u19 & 0xf800);
                          if (0xf800 < u22) {
                            u22 = 0xf800;
                          }
                          u1 = ((u5 & 0x7e0) * arg8 >> 8 & 0x7e0) + (u19 & 0x7e0);
                          u10 = (uint16_t)u1;
                          if (0x7e0 < u1) {
                            u10 = 0x7e0;
                          }
                          u5 = ((u5 & 0x1f) * arg8 >> 8 & 0x1f) + (u19 & 0x1f);
                          u9 = (uint16_t)u5;
                          if (0x1f < u5) {
                            u9 = 0x1f;
                          }
                          *(uint16_t *)pu21 = u10 | (uint16_t)u22 | u9;
                        }
                        u22 = u23 + stk_344;
                        pu21 = (uint32_t *)((int)pu21 + 2);
                        u23 = u22 & 0xffff;
                        pb18 = pb18 + -(u22 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i4;
                    } while (stk_2d8 < i13);
                  }
                }
                SpriteDecompUnlockData();
              }
            }
          }
        }
      }
      else {
        W_PutSpriteTransAddMirH8to16_B
                  (sprites,index,(int)X87_FIST32(x),(int)X87_FIST32(y),arg7,arg8);
      }
    }
  }
  return;
}
#undef stk_344
#undef stk_308
#undef stk_300
#undef stk_2fc
#undef stk_2f8
#undef stk_2f4
#undef stk_2f0
#undef stk_2ec
#undef stk_2d8
#undef stk_2d4
#undef stk_254
#undef stk_21c

/* W_ScaleSpriteTransAddMirV8to16_B @ 0x08069cf0, 4592 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended additively (colour 0 transparent), mirrored vertically,
 * with explicit source and destination alpha (256 = full). Clipped to the
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
 *   arg7         int
 *   arg8         int
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteMirV8to16,
 *        W_ScaleSpriteTransAddMirV8to16, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData, W_PutSpriteTransAddMirV8to16_B
 * C library: memset
 * Called by: W_ScaleSpriteTransAddMirV_B
 *
 * Elecbyte file: src/lib/spr16add.c
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 7 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x360 bytes,
 *       12 variables), because their address is taken.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleSpriteTransAddMirV8to16_B
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               int arg7,int arg8)

{
  uint32_t u1;
  int i2;
  int i3;
  int i4;
  uint32_t u5;
  float80 f6;
  float80 f7;
  float80 f8;
  uint16_t u9;
  uint16_t u10;
  int *sprite;
  int sprite2;
  int i13;
  int i14;
  int i15;
  int i16;
  int *sprite3;
  uint8_t *pb18;
  uint32_t u19;
  uint16_t *pu20;
  uint32_t *pu21;
  uint32_t u22;
  uint32_t u23;
  unsigned char frame[0x360] __attribute__((aligned(16)));
#define stk_354 (*(int *)(frame + 0xc))
#define stk_308 (*(uint16_t **)(frame + 0x58))
#define stk_300 (*(int *)(frame + 0x60))
#define stk_2fc (*(int *)(frame + 0x64))
#define stk_2f8 (*(int *)(frame + 0x68))
#define stk_2f4 (*(int *)(frame + 0x6c))
#define stk_2f0 (*(uint32_t *)(frame + 0x70))
#define stk_2ec (*(uint32_t *)(frame + 0x74))
#define stk_2d8 (*(int *)(frame + 0x88))
#define stk_2d4 (*(int *)(frame + 0x8c))
#define stk_254 (*(uint32_t *)(frame + 0x10c))
#define stk_21c (*(uint16_t (*)[262])(frame + 0x144))
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_2f8 = 0;
  stk_300 = 0;
  if ((0.0 < arg5) && (0.0 < arg6)) {
    if ((arg7 == 0x100) && (arg8 == 0)) {
      W_ScaleSpriteMirV8to16(sprites,index,x,y,arg5,arg6);
    }
    else if ((arg7 == 0x100) && (arg8 == 0x100)) {
      W_ScaleSpriteTransAddMirV8to16(sprites,index,x,y,arg5,arg6);
    }
    else if ((arg7 != 0) || (arg8 != 0x100)) {
      i3 = *sprite;
      i4 = sprite[1];
      if ((((double)0.001) <= ABS((float80)i3 - arg5)) || (((double)0.001) <= ABS((float80)i4 - arg6))) {
        f6 = x - ((float80)sprite[2] * arg5) / (float80)i3;
        f7 = y - ((float)((i4 - sprite[3]) + -1) * arg6) / (float80)i4;
        if ((f7 <= (float)W_y2) &&
           ((((float)W_y1 < (f7 + arg6) - 0.5 && (f6 <= (float)W_x2)) &&
            ((float)W_x1 < (f6 + arg5) - 0.5)))) {
          stk_2f4 = (int)X87_FIST32(X87_FLOOR(f7));
          f8 = (float)stk_2f4;
          if (f7 <= f8) {
            stk_2ec = 0;
          }
          else {
            if ((float)stk_2f4 < f7 - 0.5) {
              stk_2f4 = stk_2f4 + 1;
              f8 = (float)stk_2f4;
            }
            stk_254 = (uint32_t)(int64_t)
                              X87_FIST64((((float80)i4 * (f8 - f7)) / arg6) * 65536.0);
            stk_2ec = stk_254;
          }
          if (stk_2f4 < W_y1) {
            i13 = W_y1 - stk_2f4;
            stk_2f4 = W_y1;
            stk_254 = (uint32_t)(int64_t)X87_FIST64(((float)(i13 * i4) / arg6) * 65536.0);
            stk_2ec = stk_2ec + stk_254;
          }
          i13 = (int)X87_FIST32(X87_FLOOR((f7 + arg6) - 0.5));
          if (W_y2 < i13) {
            i13 = W_y2;
          }
          if (i13 - stk_2f4 != -1 && -1 < (i13 - stk_2f4) + 1) {
            stk_2fc = (int)X87_FIST32(X87_FLOOR(f6));
            f7 = (float)stk_2fc;
            if (f6 <= f7) {
              stk_2f0 = 0;
            }
            else {
              if ((float)stk_2fc < f6 - 0.5) {
                stk_2fc = stk_2fc + 1;
                f7 = (float)stk_2fc;
              }
              stk_254 = (uint32_t)(int64_t)
                                X87_FIST64((((f7 - f6) * (float80)i3) / arg5) * 65536.0);
              stk_2f0 = stk_254;
            }
            if (f6 < (float)W_x1) {
              i14 = W_x1 - stk_2fc;
              stk_2fc = W_x1;
              stk_354 = (int)(int64_t)X87_FIST64(((float)(i14 * i3) / arg5) * 65536.0);
              stk_2f0 = stk_2f0 + stk_354;
            }
            i14 = (int)X87_FIST32(X87_FLOOR((f6 + arg5) - 0.5));
            if (W_x2 < i14) {
              i14 = W_x2;
            }
            stk_254 = (uint32_t)(int64_t)X87_FIST64((float)(i3 << 0x10) / arg5);
            i3 = (int)X87_FIST32((float)(i4 << 0x10) / arg6);
            for (; ((int)stk_2f0 < 0 && (stk_2fc <= i14)); stk_2fc = stk_2fc + 1) {
              stk_2f0 = stk_2f0 + stk_254;
            }
            i15 = (int)stk_2f0 >> 0x10;
            if (i15 != 0) {
              stk_2f0 = stk_2f0 & 0xffff;
              stk_300 = i15;
            }
            for (; ((int)stk_2ec < 0 && (stk_2f4 <= i13)); stk_2f4 = stk_2f4 + 1) {
              stk_2ec = stk_2ec + i3;
            }
            i15 = (int)stk_2ec >> 0x10;
            if (i15 != 0) {
              stk_2ec = stk_2ec & 0xffff;
              stk_2f8 = i15;
            }
            i14 = (i14 - stk_2fc) + 1;
            i13 = (i13 - stk_2f4) + 1;
            if ((0 < i14) && (0 < i13)) {
              stk_2fc = stk_2fc * 2;
              i15 = SpriteDecompGetAndLockData(sprites,index);
              if (i15 != 0) {
                i16 = SpriteDecompGetData(V_Current,V_CurrentIdx);
                sprite3 = (int *)sprites[5];
                if (sprite3 == (int *)0x0) {
                  sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
                }
                else {
                  EBPalUpdate(sprite3);
                }
                pu20 = (uint16_t *)(sprite3 + 0x17);
                stk_308 = pu20;
                if (arg7 != 0x100) {
                  stk_308 = stk_21c;
                  if (arg7 == 0) {
                    memset(stk_21c,0,sprite[5] * 2);
                  }
                  else if (arg7 == 0x80) {
                    stk_2d4 = 1;
                    i2 = sprite[5];
                    if (1 < i2) {
                      do {
                        stk_21c[stk_2d4] = pu20[stk_2d4] >> 1 & 0xfbef;
                        stk_2d4 = stk_2d4 + 1;
                      } while (stk_2d4 < i2);
                    }
                  }
                  else {
                    stk_2d4 = 1;
                    i2 = sprite[5];
                    if (1 < i2) {
                      do {
                        u23 = (uint32_t)pu20[stk_2d4];
                        stk_21c[stk_2d4] =
                             (uint16_t)((u23 & 0xf800) * arg7 >> 8) & 0xf800 |
                             (uint16_t)((u23 & 0x7e0) * arg7 >> 8) & 0x7e0 |
                             (uint16_t)((u23 & 0x1f) * arg7 >> 8) & 0x1f;
                        stk_2d4 = stk_2d4 + 1;
                      } while (stk_2d4 < i2);
                    }
                  }
                }
                if (arg8 == 0) {
                  stk_2d8 = 0;
                  if (0 < i13) {
                    do {
                      pb18 = (uint8_t *)(i15 + *(int *)(sprite[0xb] + -4 +
                                                          ((i4 - stk_2f8) -
                                                          ((int)stk_2ec >> 0x10)) * 4) + stk_300
                                        );
                      pu20 = (uint16_t *)
                                (stk_2fc +
                                i16 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                 (stk_2f4 + stk_2d8) * 4));
                      u23 = stk_2f0;
                      for (i2 = i14; i2 != 0; i2 = i2 + -1) {
                        if (*pb18 != 0) {
                          *pu20 = stk_308[*pb18];
                        }
                        u22 = u23 + stk_254;
                        pu20 = pu20 + 1;
                        u23 = u22 & 0xffff;
                        pb18 = pb18 + (u22 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i3;
                    } while (stk_2d8 < i13);
                  }
                }
                else if ((arg8 + arg7 < 0x101) && (arg8 == 0x80)) {
                  stk_2d8 = 0;
                  if (0 < i13) {
                    do {
                      pb18 = (uint8_t *)(i15 + *(int *)(sprite[0xb] + -4 +
                                                          ((i4 - stk_2f8) -
                                                          ((int)stk_2ec >> 0x10)) * 4) + stk_300
                                        );
                      pu20 = (uint16_t *)
                                (stk_2fc +
                                i16 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                 (stk_2f4 + stk_2d8) * 4));
                      u23 = stk_2f0;
                      for (i2 = i14; i2 != 0; i2 = i2 + -1) {
                        if (*pb18 != 0) {
                          u10 = stk_308[*pb18];
                          u9 = (uint16_t)*(uint32_t *)pu20 >> 1;
                          *pu20 = (u9 & 0x3e0) + (u10 & 0x7e0) |
                                     (u9 & 0x7800) + (u10 & 0xf800) |
                                     (u9 & 0xf) + (u10 & 0x1f);
                        }
                        u22 = u23 + stk_254;
                        pu20 = pu20 + 1;
                        u23 = u22 & 0xffff;
                        pb18 = pb18 + (u22 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i3;
                    } while (stk_2d8 < i13);
                  }
                }
                else if (arg8 + arg7 < 0x101) {
                  stk_2d8 = 0;
                  if (0 < i13) {
                    do {
                      pb18 = (uint8_t *)(i15 + *(int *)(sprite[0xb] + -4 +
                                                          ((i4 - stk_2f8) -
                                                          ((int)stk_2ec >> 0x10)) * 4) + stk_300
                                        );
                      pu21 = (uint32_t *)(stk_2fc +
                                        i16 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                         (stk_2f4 + stk_2d8) * 4));
                      u23 = stk_2f0;
                      for (i2 = i14; i2 != 0; i2 = i2 + -1) {
                        if (*pb18 != 0) {
                          u10 = stk_308[*pb18];
                          u22 = *pu21;
                          *(uint16_t *)pu21 =
                               ((uint16_t)((u22 & 0x7e0) * arg8 >> 8) & 0x7e0) +
                               (u10 & 0x7e0) |
                               ((uint16_t)((u22 & 0xf800) * arg8 >> 8) & 0xf800) +
                               (u10 & 0xf800) |
                               ((uint16_t)((u22 & 0x1f) * arg8 >> 8) & 0x1f) + (u10 & 0x1f);
                        }
                        u22 = u23 + stk_254;
                        pu21 = (uint32_t *)((int)pu21 + 2);
                        u23 = u22 & 0xffff;
                        pb18 = pb18 + (u22 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i3;
                    } while (stk_2d8 < i13);
                  }
                }
                else if (arg8 == 0x80) {
                  stk_2d8 = 0;
                  if (0 < i13) {
                    do {
                      pb18 = (uint8_t *)(i15 + *(int *)(sprite[0xb] + -4 +
                                                          ((i4 - stk_2f8) -
                                                          ((int)stk_2ec >> 0x10)) * 4) + stk_300
                                        );
                      pu21 = (uint32_t *)(stk_2fc +
                                        i16 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                         (stk_2f4 + stk_2d8) * 4));
                      u23 = stk_2f0;
                      for (i2 = i14; i2 != 0; i2 = i2 + -1) {
                        if (*pb18 != 0) {
                          u19 = (uint32_t)stk_308[*pb18];
                          u5 = *pu21 >> 1;
                          u22 = (u5 & 0x7800) + (u19 & 0xf800);
                          if (0xf800 < u22) {
                            u22 = 0xf800;
                          }
                          u1 = (u5 & 0x3e0) + (u19 & 0x7e0);
                          u10 = (uint16_t)u1;
                          if (0x7e0 < u1) {
                            u10 = 0x7e0;
                          }
                          u5 = (u5 & 0xf) + (u19 & 0x1f);
                          u9 = (uint16_t)u5;
                          if (0x1f < u5) {
                            u9 = 0x1f;
                          }
                          *(uint16_t *)pu21 = u10 | (uint16_t)u22 | u9;
                        }
                        u22 = u23 + stk_254;
                        pu21 = (uint32_t *)((int)pu21 + 2);
                        u23 = u22 & 0xffff;
                        pb18 = pb18 + (u22 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i3;
                    } while (stk_2d8 < i13);
                  }
                }
                else {
                  stk_2d8 = 0;
                  if (0 < i13) {
                    do {
                      pb18 = (uint8_t *)(i15 + *(int *)(sprite[0xb] + -4 +
                                                          ((i4 - stk_2f8) -
                                                          ((int)stk_2ec >> 0x10)) * 4) + stk_300
                                        );
                      pu21 = (uint32_t *)(stk_2fc +
                                        i16 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                         (stk_2f4 + stk_2d8) * 4));
                      u23 = stk_2f0;
                      for (i2 = i14; i2 != 0; i2 = i2 + -1) {
                        if (*pb18 != 0) {
                          u19 = (uint32_t)stk_308[*pb18];
                          u5 = *pu21;
                          u22 = ((u5 & 0xf800) * arg8 >> 8 & 0xf800) + (u19 & 0xf800);
                          if (0xf800 < u22) {
                            u22 = 0xf800;
                          }
                          u1 = ((u5 & 0x7e0) * arg8 >> 8 & 0x7e0) + (u19 & 0x7e0);
                          u10 = (uint16_t)u1;
                          if (0x7e0 < u1) {
                            u10 = 0x7e0;
                          }
                          u5 = ((u5 & 0x1f) * arg8 >> 8 & 0x1f) + (u19 & 0x1f);
                          u9 = (uint16_t)u5;
                          if (0x1f < u5) {
                            u9 = 0x1f;
                          }
                          *(uint16_t *)pu21 = u10 | (uint16_t)u22 | u9;
                        }
                        u22 = u23 + stk_254;
                        pu21 = (uint32_t *)((int)pu21 + 2);
                        u23 = u22 & 0xffff;
                        pb18 = pb18 + (u22 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i3;
                    } while (stk_2d8 < i13);
                  }
                }
                SpriteDecompUnlockData();
              }
            }
          }
        }
      }
      else {
        W_PutSpriteTransAddMirV8to16_B
                  (sprites,index,(int)X87_FIST32(x),(int)X87_FIST32(y),arg7,arg8);
      }
    }
  }
  return;
}
#undef stk_354
#undef stk_308
#undef stk_300
#undef stk_2fc
#undef stk_2f8
#undef stk_2f4
#undef stk_2f0
#undef stk_2ec
#undef stk_2d8
#undef stk_2d4
#undef stk_254
#undef stk_21c

/* W_ScaleSpriteTransAddMirHV8to16_B @ 0x0806aee0, 4626 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended additively (colour 0 transparent), mirrored horizontally
 * and vertically, with explicit source and destination alpha (256 = full).
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
 *   arg7         int
 *   arg8         int
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteMirHV8to16,
 *        W_ScaleSpriteTransAddMirHV8to16, SpriteDecompGetAndLockData,
 *        SpriteDecompGetData, SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData, W_PutSpriteTransAddMirHV8to16_B
 * C library: memset
 * Called by: W_ScaleSpriteTransAddMirHV_B
 *
 * Elecbyte file: src/lib/spr16add.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to NAN
 * Note: 2 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 6 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x360 bytes,
 *       12 variables), because their address is taken.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void W_ScaleSpriteTransAddMirHV8to16_B
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               int arg7,int arg8)

{
  uint32_t u1;
  int i2;
  int i3;
  int i4;
  int i5;
  uint32_t u6;
  float80 f7;
  float80 f8;
  float80 f9;
  uint16_t u10;
  uint16_t u11;
  int *sprite;
  int sprite2;
  int i14;
  int i15;
  int i16;
  int i17;
  int *sprite3;
  uint8_t *pb19;
  uint32_t u20;
  uint16_t *pu21;
  uint32_t *pu22;
  uint32_t u23;
  uint32_t u24;
  unsigned char frame[0x360] __attribute__((aligned(16)));
#define stk_354 (*(int *)(frame + 0xc))
#define stk_30c (*(uint16_t **)(frame + 0x54))
#define stk_300 (*(int *)(frame + 0x60))
#define stk_2fc (*(int *)(frame + 0x64))
#define stk_2f8 (*(int *)(frame + 0x68))
#define stk_2f4 (*(int *)(frame + 0x6c))
#define stk_2f0 (*(uint32_t *)(frame + 0x70))
#define stk_2ec (*(uint32_t *)(frame + 0x74))
#define stk_2d8 (*(int *)(frame + 0x88))
#define stk_2d4 (*(int *)(frame + 0x8c))
#define stk_254 (*(uint32_t *)(frame + 0x10c))
#define stk_21c (*(uint16_t (*)[262])(frame + 0x144))
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  stk_2f8 = 0;
  stk_300 = 0;
  if ((0.0 < arg5) && (0.0 < arg6)) {
    if ((arg7 == 0x100) && (arg8 == 0)) {
      W_ScaleSpriteMirHV8to16(sprites,index,x,y,arg5,arg6);
    }
    else if ((arg7 == 0x100) && (arg8 == 0x100)) {
      W_ScaleSpriteTransAddMirHV8to16(sprites,index,x,y,arg5,arg6);
    }
    else if ((arg7 != 0) || (arg8 != 0x100)) {
      i4 = *sprite;
      i5 = sprite[1];
      if ((((double)0.001) <= ABS((float80)i4 - arg5)) || (((double)0.001) <= ABS((float80)i5 - arg6))) {
        f7 = x - ((float)((i4 - sprite[2]) + -1) * arg5) / (float80)i4;
        f8 = y - ((float)((i5 - sprite[3]) + -1) * arg6) / (float80)i5;
        if ((f8 <= (float)W_y2) &&
           ((((float)W_y1 < (f8 + arg6) - 0.5 && (f7 <= (float)W_x2)) &&
            ((float)W_x1 < (f7 + arg5) - 0.5)))) {
          stk_2f4 = (int)X87_FIST32(X87_FLOOR(f8));
          f9 = (float)stk_2f4;
          if (f8 <= f9) {
            stk_2ec = 0;
          }
          else {
            if ((float)stk_2f4 < f8 - 0.5) {
              stk_2f4 = stk_2f4 + 1;
              f9 = (float)stk_2f4;
            }
            stk_254 = (uint32_t)(int64_t)
                              X87_FIST64((((float80)i5 * (f9 - f8)) / arg6) * 65536.0);
            stk_2ec = stk_254;
          }
          if (stk_2f4 < W_y1) {
            i14 = W_y1 - stk_2f4;
            stk_2f4 = W_y1;
            stk_254 = (uint32_t)(int64_t)X87_FIST64(((float)(i14 * i5) / arg6) * 65536.0);
            stk_2ec = stk_2ec + stk_254;
          }
          i14 = (int)X87_FIST32(X87_FLOOR((f8 + arg6) - 0.5));
          if (W_y2 < i14) {
            i14 = W_y2;
          }
          if (i14 - stk_2f4 != -1 && -1 < (i14 - stk_2f4) + 1) {
            stk_2fc = (int)X87_FIST32(X87_FLOOR(f7));
            f8 = (float)stk_2fc;
            if (f7 <= f8) {
              stk_2f0 = 0;
            }
            else {
              if ((float)stk_2fc < f7 - 0.5) {
                stk_2fc = stk_2fc + 1;
                f8 = (float)stk_2fc;
              }
              stk_254 = (uint32_t)(int64_t)
                                X87_FIST64((((f8 - f7) * (float80)i4) / arg5) * 65536.0);
              stk_2f0 = stk_254;
            }
            if (f7 < (float)W_x1) {
              i15 = W_x1 - stk_2fc;
              stk_2fc = W_x1;
              stk_354 = (int)(int64_t)X87_FIST64(((float)(i15 * i4) / arg5) * 65536.0);
              stk_2f0 = stk_2f0 + stk_354;
            }
            i15 = (int)X87_FIST32(X87_FLOOR((f7 + arg5) - 0.5));
            if (W_x2 < i15) {
              i15 = W_x2;
            }
            stk_354 = (int)(int64_t)X87_FIST64((float)(i4 << 0x10) / arg5);
            i2 = (int)X87_FIST32((float)(i5 << 0x10) / arg6);
            for (; ((int)stk_2f0 < 0 && (stk_2fc <= i15)); stk_2fc = stk_2fc + 1) {
              stk_2f0 = stk_2f0 + stk_354;
            }
            i16 = (int)stk_2f0 >> 0x10;
            if (i16 != 0) {
              stk_2f0 = stk_2f0 & 0xffff;
              stk_300 = i16;
            }
            for (; ((int)stk_2ec < 0 && (stk_2f4 <= i14)); stk_2f4 = stk_2f4 + 1) {
              stk_2ec = stk_2ec + i2;
            }
            i16 = (int)stk_2ec >> 0x10;
            if (i16 != 0) {
              stk_2ec = stk_2ec & 0xffff;
              stk_2f8 = i16;
            }
            i15 = (i15 - stk_2fc) + 1;
            i14 = (i14 - stk_2f4) + 1;
            if ((0 < i15) && (0 < i14)) {
              stk_2fc = stk_2fc * 2;
              i16 = SpriteDecompGetAndLockData(sprites,index);
              if (i16 != 0) {
                i17 = SpriteDecompGetData(V_Current,V_CurrentIdx);
                sprite3 = (int *)sprites[5];
                if (sprite3 == (int *)0x0) {
                  sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
                }
                else {
                  EBPalUpdate(sprite3);
                }
                pu21 = (uint16_t *)(sprite3 + 0x17);
                stk_30c = pu21;
                if (arg7 != 0x100) {
                  stk_30c = stk_21c;
                  if (arg7 == 0) {
                    memset(stk_21c,0,sprite[5] * 2);
                  }
                  else if (arg7 == 0x80) {
                    stk_2d4 = 1;
                    i3 = sprite[5];
                    if (1 < i3) {
                      do {
                        stk_21c[stk_2d4] = pu21[stk_2d4] >> 1 & 0xfbef;
                        stk_2d4 = stk_2d4 + 1;
                      } while (stk_2d4 < i3);
                    }
                  }
                  else {
                    stk_2d4 = 1;
                    i3 = sprite[5];
                    if (1 < i3) {
                      do {
                        u24 = (uint32_t)pu21[stk_2d4];
                        stk_21c[stk_2d4] =
                             (uint16_t)((u24 & 0xf800) * arg7 >> 8) & 0xf800 |
                             (uint16_t)((u24 & 0x7e0) * arg7 >> 8) & 0x7e0 |
                             (uint16_t)((u24 & 0x1f) * arg7 >> 8) & 0x1f;
                        stk_2d4 = stk_2d4 + 1;
                      } while (stk_2d4 < i3);
                    }
                  }
                }
                if (arg8 == 0) {
                  stk_2d8 = 0;
                  if (0 < i14) {
                    do {
                      pb19 = (uint8_t *)(((i16 + *(int *)(sprite[0xb] + -4 +
                                                            ((i5 - stk_2f8) -
                                                            ((int)stk_2ec >> 0x10)) * 4) + i4)
                                         - stk_300) + -1);
                      pu21 = (uint16_t *)
                                (stk_2fc +
                                i17 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                 (stk_2f4 + stk_2d8) * 4));
                      u24 = stk_2f0;
                      for (i3 = i15; i3 != 0; i3 = i3 + -1) {
                        if (*pb19 != 0) {
                          *pu21 = stk_30c[*pb19];
                        }
                        u23 = u24 + stk_354;
                        pu21 = pu21 + 1;
                        u24 = u23 & 0xffff;
                        pb19 = pb19 + -(u23 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i2;
                    } while (stk_2d8 < i14);
                  }
                }
                else if ((arg8 + arg7 < 0x101) && (arg8 == 0x80)) {
                  stk_2d8 = 0;
                  if (0 < i14) {
                    do {
                      pb19 = (uint8_t *)(((i16 + *(int *)(sprite[0xb] + -4 +
                                                            ((i5 - stk_2f8) -
                                                            ((int)stk_2ec >> 0x10)) * 4) + i4)
                                         - stk_300) + -1);
                      pu21 = (uint16_t *)
                                (stk_2fc +
                                i17 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                 (stk_2f4 + stk_2d8) * 4));
                      u24 = stk_2f0;
                      for (i3 = i15; i3 != 0; i3 = i3 + -1) {
                        if (*pb19 != 0) {
                          u11 = stk_30c[*pb19];
                          u10 = (uint16_t)*(uint32_t *)pu21 >> 1;
                          *pu21 = (u10 & 0x3e0) + (u11 & 0x7e0) |
                                     (u10 & 0x7800) + (u11 & 0xf800) |
                                     (u10 & 0xf) + (u11 & 0x1f);
                        }
                        u23 = u24 + stk_354;
                        pu21 = pu21 + 1;
                        u24 = u23 & 0xffff;
                        pb19 = pb19 + -(u23 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i2;
                    } while (stk_2d8 < i14);
                  }
                }
                else if (arg8 + arg7 < 0x101) {
                  stk_2d8 = 0;
                  if (0 < i14) {
                    do {
                      pb19 = (uint8_t *)(((i16 + *(int *)(sprite[0xb] + -4 +
                                                            ((i5 - stk_2f8) -
                                                            ((int)stk_2ec >> 0x10)) * 4) + i4)
                                         - stk_300) + -1);
                      pu22 = (uint32_t *)(stk_2fc +
                                        i17 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                         (stk_2f4 + stk_2d8) * 4));
                      u24 = stk_2f0;
                      for (i3 = i15; i3 != 0; i3 = i3 + -1) {
                        if (*pb19 != 0) {
                          u11 = stk_30c[*pb19];
                          u23 = *pu22;
                          *(uint16_t *)pu22 =
                               ((uint16_t)((u23 & 0x7e0) * arg8 >> 8) & 0x7e0) +
                               (u11 & 0x7e0) |
                               ((uint16_t)((u23 & 0xf800) * arg8 >> 8) & 0xf800) +
                               (u11 & 0xf800) |
                               ((uint16_t)((u23 & 0x1f) * arg8 >> 8) & 0x1f) + (u11 & 0x1f);
                        }
                        u23 = u24 + stk_354;
                        pu22 = (uint32_t *)((int)pu22 + 2);
                        u24 = u23 & 0xffff;
                        pb19 = pb19 + -(u23 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i2;
                    } while (stk_2d8 < i14);
                  }
                }
                else if (arg8 == 0x80) {
                  stk_2d8 = 0;
                  if (0 < i14) {
                    do {
                      pb19 = (uint8_t *)(((i16 + *(int *)(sprite[0xb] + -4 +
                                                            ((i5 - stk_2f8) -
                                                            ((int)stk_2ec >> 0x10)) * 4) + i4)
                                         - stk_300) + -1);
                      pu22 = (uint32_t *)(stk_2fc +
                                        i17 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                         (stk_2f4 + stk_2d8) * 4));
                      u24 = stk_2f0;
                      for (i3 = i15; i3 != 0; i3 = i3 + -1) {
                        if (*pb19 != 0) {
                          u20 = (uint32_t)stk_30c[*pb19];
                          u6 = *pu22 >> 1;
                          u23 = (u6 & 0x7800) + (u20 & 0xf800);
                          if (0xf800 < u23) {
                            u23 = 0xf800;
                          }
                          u1 = (u6 & 0x3e0) + (u20 & 0x7e0);
                          u11 = (uint16_t)u1;
                          if (0x7e0 < u1) {
                            u11 = 0x7e0;
                          }
                          u6 = (u6 & 0xf) + (u20 & 0x1f);
                          u10 = (uint16_t)u6;
                          if (0x1f < u6) {
                            u10 = 0x1f;
                          }
                          *(uint16_t *)pu22 = u11 | (uint16_t)u23 | u10;
                        }
                        u23 = u24 + stk_354;
                        pu22 = (uint32_t *)((int)pu22 + 2);
                        u24 = u23 & 0xffff;
                        pb19 = pb19 + -(u23 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i2;
                    } while (stk_2d8 < i14);
                  }
                }
                else {
                  stk_2d8 = 0;
                  if (0 < i14) {
                    do {
                      pb19 = (uint8_t *)(((i16 + *(int *)(sprite[0xb] + -4 +
                                                            ((i5 - stk_2f8) -
                                                            ((int)stk_2ec >> 0x10)) * 4) + i4)
                                         - stk_300) + -1);
                      pu22 = (uint32_t *)(stk_2fc +
                                        i17 + *(int *)(*(int *)(sprite2 + 0x2c) +
                                                         (stk_2f4 + stk_2d8) * 4));
                      u24 = stk_2f0;
                      for (i3 = i15; i3 != 0; i3 = i3 + -1) {
                        if (*pb19 != 0) {
                          u20 = (uint32_t)stk_30c[*pb19];
                          u6 = *pu22;
                          u23 = ((u6 & 0xf800) * arg8 >> 8 & 0xf800) + (u20 & 0xf800);
                          if (0xf800 < u23) {
                            u23 = 0xf800;
                          }
                          u1 = ((u6 & 0x7e0) * arg8 >> 8 & 0x7e0) + (u20 & 0x7e0);
                          u11 = (uint16_t)u1;
                          if (0x7e0 < u1) {
                            u11 = 0x7e0;
                          }
                          u6 = ((u6 & 0x1f) * arg8 >> 8 & 0x1f) + (u20 & 0x1f);
                          u10 = (uint16_t)u6;
                          if (0x1f < u6) {
                            u10 = 0x1f;
                          }
                          *(uint16_t *)pu22 = u11 | (uint16_t)u23 | u10;
                        }
                        u23 = u24 + stk_354;
                        pu22 = (uint32_t *)((int)pu22 + 2);
                        u24 = u23 & 0xffff;
                        pb19 = pb19 + -(u23 >> 0x10);
                      }
                      stk_2d8 = stk_2d8 + 1;
                      stk_2ec = stk_2ec + i2;
                    } while (stk_2d8 < i14);
                  }
                }
                SpriteDecompUnlockData();
              }
            }
          }
        }
      }
      else {
        W_PutSpriteTransAddMirHV8to16_B
                  (sprites,index,(int)X87_FIST32(x),(int)X87_FIST32(y),arg7,arg8);
      }
    }
  }
  return;
}
#undef stk_354
#undef stk_30c
#undef stk_300
#undef stk_2fc
#undef stk_2f8
#undef stk_2f4
#undef stk_2f0
#undef stk_2ec
#undef stk_2d8
#undef stk_2d4
#undef stk_254
#undef stk_21c

/* W_RotateSpriteTransAdd8to16_P @ 0x0806c100, 3861 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, blended additively (colour 0 transparent). Clipped
 * to the window set by W_Define. This is the pixel loop: it reads the 8-bit
 * sprite rows through the sprite's palette converted to 16-bit colours and
 * writes 16-bit pixels. Scaling without rotation is handed to the scaled
 * blitter.
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
 * Calls: SpriteArrayAccess, roundfloat, W_ScaleSpriteTransAdd_S,
 *        SpriteDecompGetAndLockData, SpriteDecompGetData,
 *        SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * Called by: W_RotateSpriteTransAdd8to16_B_P, W_RotateSpriteTransAdd_P
 *
 * Elecbyte file: src/lib/spr16add.c
 * Note: 1 accesses to parts of a variable are written as sized accesses.
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 15 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0xa0 bytes,
 *       14 variables), because their address is taken.
 * Note: 8 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t W_RotateSpriteTransAdd8to16_P
               (int *sprites,int index,float x2,float y,float arg5,float arg6,
               float arg7,float arg8,float arg9)

{
  uint32_t u1;
  int i2;
  int i3;
  uint8_t b4;
  int i5;
  int i6;
  int i7;
  int i8;
  int i9;
  int i10;
  uint64_t u11;
  float80 f12;
  float80 f13;
  float80 f14;
  float80 f15;
  float80 f16;
  float80 f17;
  float80 f18;
  float80 f19;
  int *sprite;
  int sprite2;
  int i22;
  int i23;
  uint32_t u24;
  int i25;
  int i26;
  int i27;
  int *sprite3;
  int i29;
  uint32_t u30;
  uint16_t u31;
  int i32;
  uint16_t u33;
  int i34;
  int i35;
  int i37;
  int i38;
  int i39;
  int i40;
  int i41;
  uint16_t entry_FPUControlWord;
  uint32_t u36;
  unsigned char frame[0xa0] __attribute__((aligned(16)));
#define stk_94 (*(int *)(frame + 0xc))
#define stk_90 (*(float *)(frame + 0x10))
#define stk_8c (*(float *)(frame + 0x14))
#define stk_88 (*(float *)(frame + 0x18))
#define stk_84 (*(float *)(frame + 0x1c))
#define stk_78 (*(int *)(frame + 0x28))
#define stk_74 (*(int *)(frame + 0x2c))
#define stk_68 (*(int *)(frame + 0x38))
#define stk_64 (*(int *)(frame + 0x3c))
#define stk_60 (*(int *)(frame + 0x40))
#define stk_54 (*(int *)(frame + 0x4c))
#define stk_50 (*(int *)(frame + 0x50))
#define stk_38 (*(uint16_t **)(frame + 0x68))
#define stk_20 (*(uint32_t *)(frame + 0x80))
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  i5 = sprite[0xb];
  i22 = roundfloat(x2);
  i23 = roundfloat(y);
  i37 = (int)X87_FIST32(arg6 * 1024.0);
  if (i37 < 0) {
    i37 = -i37;
    arg5 = arg5 + 180.0;
  }
  stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
  i40 = (int)X87_FIST32(arg7 * 1024.0);
  if (i40 < 0) {
    i40 = -i40;
    arg5 = arg5 + 180.0;
  }
  if (i37 == 0) {
    return stk_20;
  }
  if (i40 == 0) {
    return stk_20;
  }
  if (arg5 < 0.0) {
    arg5 = (float)((int)X87_FIST32(-arg5 * ((float)0.0027777778f)) * 0x168 + 0x168) + arg5;
  }
  u11 = (int64_t)(int)X87_FIST32(arg5 * 8.0) % 0xb40;
  i34 = (int)u11;
  if (i34 == 0) {
L_0806c3f2:
    u24 = W_ScaleSpriteTransAdd_S
                       (sprites,index,x2,y,arg6 * arg8,arg7 * arg9);
    return u24;
  }
  if (i34 == 0x5a0) {
    arg7 = -arg7;
    arg6 = -arg6;
    goto L_0806c3f2;
  }
  i6 = *sprite;
  i7 = sprite[1];
  i8 = sprite[2];
  i9 = sprite[3];
  f12 = (float)SinTable[(i34 + 0x2d0) % 0xb40];
  f13 = f12 * 0.0009765625;
  f15 = (float)SinTable[(int)((int64_t)
                                 ((uint64_t)(uint32_t)(i34 >> 0x1f) << 0x20 | u11 & 0xffffffff) %
                                0xb40)];
  f14 = f15 * 0.0009765625;
  i2 = (int)X87_FIST32((float)((SinTable[(i34 + 0x2d0) % 0xb40] << 0x10) / i37) / arg8);
  u24 = (SinTable[(int)((int64_t)
                           ((uint64_t)(uint32_t)(i34 >> 0x1f) << 0x20 | u11 & 0xffffffff) % 0xb40
                          )] << 0x10) / i40;
  i3 = (int)X87_FIST32((float80)(int)u24 / arg8);
  if (i34 < 0x2d0) {
    i34 = -i8;
    i25 = -i9;
    i26 = (i6 - i8) + -1;
    i27 = (i7 - i9) + -1;
L_0806c63f:
    f16 = (float80)i34;
    f17 = (float80)i26;
    stk_88 = (float80)i25;
    stk_90 = (float80)i27;
    stk_8c = stk_90;
    f19 = f16;
  }
  else {
    if (i34 < 0x5a0) {
      i26 = (i6 - i8) + -1;
      i25 = -i9;
      i34 = (i7 - i9) + -1;
      i27 = -i8;
    }
    else {
      if (i34 < 0x870) {
        i34 = (i6 - i8) + -1;
        i25 = (i7 - i9) + -1;
        i26 = -i8;
        i27 = -i9;
        goto L_0806c63f;
      }
      if (0xb3f < i34) {
        return u24;
      }
      i26 = -i8;
      i25 = (i7 - i9) + -1;
      i34 = -i9;
      i27 = (i6 - i8) + -1;
    }
    f16 = (float80)i26;
    stk_8c = (float80)i34;
    f17 = (float80)i27;
    stk_90 = (float80)i25;
    stk_88 = stk_8c;
    f19 = f17;
  }
  stk_84 = (float80)i26;
  stk_8c = stk_8c * arg7;
  f16 = f16 * arg6;
  f18 = (float80)i25 * arg7;
  f17 = f17 * arg6;
  i34 = roundfloat((-f16 * f14 + f18 * f13) * arg9);
  i26 = roundfloat((-f17 * f14 + stk_8c * f13) * arg9);
  stk_54 = roundfloat((-(stk_84 * arg6) * f14 + stk_88 * arg7 * f13) * arg9);
  stk_94 = roundfloat((-(f19 * arg6) * f14 + stk_90 * arg7 * f13) * arg9);
  if ((stk_54 == i34) || (stk_54 == i26)) {
    stk_78 = 0;
    stk_74 = 0;
    stk_64 = (int)X87_FIST32((f16 * f13 + f18 * f14) * 65536.0 * arg8);
    stk_68 = (int)X87_FIST32((f17 * f13 + stk_8c * f14) * 65536.0 * arg8);
  }
  else {
    f19 = f13 * stk_84 * arg6 + stk_88 * arg7 * f14;
    stk_74 = (int)X87_FIST32(((f19 - (f16 * f13 + f18 * f14)) * 65536.0 * arg8) /
                          (float)(stk_54 - i34));
    if (stk_74 < 0) {
      stk_74 = -stk_74;
    }
    stk_78 = (int)X87_FIST32((((stk_8c * f14 + f17 * f13) - f19) * 65536.0 * arg8) /
                          (float)(stk_54 - i26));
    if (stk_78 < 0) {
      stk_78 = -stk_78;
    }
    stk_68 = (int)X87_FIST32(f19 * 65536.0 * arg8);
    stk_64 = stk_68;
  }
  for (; stk_54 < W_y1 - i23; stk_54 = stk_54 + 1) {
    i25 = stk_78;
    if (stk_54 < i34) {
      i25 = -stk_74;
    }
    stk_64 = stk_64 + i25;
    i25 = stk_78;
    if (i26 <= stk_54) {
      i25 = -stk_74;
    }
    stk_68 = stk_68 + i25;
  }
  if (W_y2 - i23 < stk_94) {
    stk_94 = W_y2 - i23;
  }
  i25 = SpriteDecompGetAndLockData(sprites,index);
  if (i25 == 0) {
    return 0;
  }
  i27 = SpriteDecompGetData(V_Current,V_CurrentIdx);
  sprite3 = (int *)sprites[5];
  if (sprite3 == (int *)0x0) {
    sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
  }
  else {
    EBPalUpdate(sprite3);
  }
  if (stk_54 <= stk_94) {
    i29 = W_x1 - i22;
    do {
      i39 = stk_64 >> 0x10;
      if (stk_64 >> 0x10 < i29) {
        i39 = i29;
      }
      i41 = stk_68 >> 0x10;
      if (W_x2 - i22 < stk_68 >> 0x10) {
        i41 = W_x2 - i22;
      }
      stk_60 = (int)X87_FIST32(((((float80)i39 / arg8) * f12 -
                             ((float)stk_54 / arg9) * f15) * 65536.0) / (float80)i37) +
                 i8 * 0x10000;
      i38 = i9 * 0x10000 +
               (int)X87_FIST32(((((float80)i39 / arg8) * f15 +
                           ((float)stk_54 / arg9) * f12) * 65536.0) / (float80)i40);
      stk_38 = (uint16_t *)
                 (i27 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_54 + i23) * 4) +
                 (i22 + i39) * 2);
      i35 = (i41 - i39) + 1;
      i10 = i41 - i39;
      i32 = i3 * i35 + i38;
      for (i35 = stk_60 + i2 * i35;
          (SBORROW4(i41,i39) == i10 < 0 &&
          ((((i7 <= i32 >> 0x10 || (i6 <= i35 >> 0x10)) || (i32 >> 0x10 < 0)) ||
           (i35 >> 0x10 < 0)))); i35 = i35 - i2) {
        i41 = i41 + -1;
        i32 = i32 - i3;
        i10 = i41 - i39;
      }
      for (; (i39 <= i41 &&
             (((i7 <= i38 >> 0x10 || (i6 <= stk_60 >> 0x10)) ||
              ((i38 >> 0x10 < 0 || (stk_60 >> 0x10 < 0)))))); stk_60 = stk_60 + i2) {
        stk_38 = stk_38 + 1;
        i39 = i39 + 1;
        i38 = i38 + i3;
      }
      stk_50 = (i41 - i39) + 1;
      if (0 < stk_50) {
        do {
          b4 = *(uint8_t *)((stk_60 >> 0x10) + i25 + *(int *)(i5 + (i38 >> 0x10) * 4));
          if (b4 != 0) {
            u36 = (uint32_t)*(uint16_t *)((int)sprite3 + (uint32_t)b4 * 2 + 0x5c);
            u30 = (uint32_t)*stk_38;
            u24 = (u30 & 0xf800) + (u36 & 0xf800);
            if (0xf800 < u24) {
              u24 = 0xf800;
            }
            u1 = (u30 & 0x7e0) + (u36 & 0x7e0);
            u31 = (uint16_t)u1;
            if (0x7e0 < u1) {
              u31 = 0x7e0;
            }
            u36 = (u36 & 0x1f) + (u30 & 0x1f);
            u33 = (uint16_t)u36;
            if (0x1f < u36) {
              u33 = 0x1f;
            }
            *stk_38 = (uint16_t)u24 | u31 | u33;
          }
          stk_60 = stk_60 + i2;
          stk_38 = stk_38 + 1;
          i38 = i38 + i3;
          stk_50 = stk_50 + -1;
        } while (stk_50 != 0);
      }
      i39 = stk_78;
      if (stk_54 < i34) {
        i39 = -stk_74;
      }
      stk_64 = stk_64 + i39;
      i39 = stk_78;
      if (i26 <= stk_54) {
        i39 = -stk_74;
      }
      stk_68 = stk_68 + i39;
      stk_54 = stk_54 + 1;
    } while (stk_54 <= stk_94);
  }
  u24 = SpriteDecompUnlockData();
  return u24;
}
#undef stk_94
#undef stk_90
#undef stk_8c
#undef stk_88
#undef stk_84
#undef stk_78
#undef stk_74
#undef stk_68
#undef stk_64
#undef stk_60
#undef stk_54
#undef stk_50
#undef stk_38
#undef stk_20

/* W_RotateSpriteTransAddMirH8to16_P @ 0x0806d020, 3861 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, blended additively (colour 0 transparent),
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
 * Calls: SpriteArrayAccess, roundfloat, W_ScaleSpriteTransAdd_S,
 *        SpriteDecompGetAndLockData, SpriteDecompGetData,
 *        SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * Called by: W_RotateSpriteTransAddMirH8to16_B_P, W_RotateSpriteTransAdd_P
 *
 * Elecbyte file: src/lib/spr16add.c
 * Note: 1 accesses to parts of a variable are written as sized accesses.
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 15 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0xa0 bytes,
 *       14 variables), because their address is taken.
 * Note: 8 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t W_RotateSpriteTransAddMirH8to16_P
               (int *sprites,int index,float x2,float y,float arg5,float arg6,
               float arg7,float arg8,float arg9)

{
  uint32_t u1;
  int i2;
  int i3;
  uint8_t b4;
  int i5;
  int i6;
  int i7;
  int i8;
  int i9;
  int i10;
  uint64_t u11;
  float80 f12;
  float80 f13;
  float80 f14;
  float80 f15;
  float80 f16;
  float80 f17;
  float80 f18;
  float80 f19;
  int *sprite;
  int sprite2;
  int i22;
  int i23;
  uint32_t u24;
  int i25;
  int i26;
  int i27;
  int *sprite3;
  uint32_t u29;
  uint16_t u30;
  int i31;
  uint16_t u32;
  int i33;
  int i34;
  int i36;
  int i37;
  int i38;
  int i39;
  int i40;
  uint16_t entry_FPUControlWord;
  uint32_t u35;
  unsigned char frame[0xa0] __attribute__((aligned(16)));
#define stk_94 (*(int *)(frame + 0xc))
#define stk_90 (*(float *)(frame + 0x10))
#define stk_8c (*(float *)(frame + 0x14))
#define stk_88 (*(float *)(frame + 0x18))
#define stk_84 (*(float *)(frame + 0x1c))
#define stk_78 (*(int *)(frame + 0x28))
#define stk_74 (*(int *)(frame + 0x2c))
#define stk_68 (*(int *)(frame + 0x38))
#define stk_64 (*(int *)(frame + 0x3c))
#define stk_60 (*(int *)(frame + 0x40))
#define stk_54 (*(int *)(frame + 0x4c))
#define stk_50 (*(int *)(frame + 0x50))
#define stk_38 (*(uint16_t **)(frame + 0x68))
#define stk_20 (*(uint32_t *)(frame + 0x80))
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  i5 = sprite[0xb];
  i22 = roundfloat(x2);
  i23 = roundfloat(y);
  i36 = (int)X87_FIST32(arg6 * 1024.0);
  if (i36 < 0) {
    i36 = -i36;
    arg5 = arg5 + 180.0;
  }
  stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
  i39 = (int)X87_FIST32(arg7 * 1024.0);
  if (i39 < 0) {
    i39 = -i39;
    arg5 = arg5 + 180.0;
  }
  if (i36 == 0) {
    return stk_20;
  }
  if (i39 == 0) {
    return stk_20;
  }
  if (arg5 < 0.0) {
    arg5 = (float)((int)X87_FIST32(-arg5 * ((float)0.0027777778f)) * 0x168 + 0x168) + arg5;
  }
  u11 = (int64_t)(int)X87_FIST32(arg5 * 8.0) % 0xb40;
  i33 = (int)u11;
  if (i33 == 0) {
    arg6 = -arg6;
L_0806d313:
    u24 = W_ScaleSpriteTransAdd_S
                       (sprites,index,x2,y,arg6 * arg8,arg7 * arg9);
    return u24;
  }
  if (i33 == 0x5a0) {
    arg7 = -arg7;
    goto L_0806d313;
  }
  i6 = *sprite;
  i7 = sprite[1];
  i8 = sprite[2];
  i9 = sprite[3];
  f12 = (float)SinTable[(i33 + 0x2d0) % 0xb40];
  f13 = f12 * 0.0009765625;
  f15 = (float)SinTable[(int)((int64_t)
                                 ((uint64_t)(uint32_t)(i33 >> 0x1f) << 0x20 | u11 & 0xffffffff) %
                                0xb40)];
  f14 = f15 * 0.0009765625;
  i2 = (int)X87_FIST32((float)((SinTable[(i33 + 0x2d0) % 0xb40] << 0x10) / i36) / arg8);
  u24 = (SinTable[(int)((int64_t)
                           ((uint64_t)(uint32_t)(i33 >> 0x1f) << 0x20 | u11 & 0xffffffff) % 0xb40
                          )] << 0x10) / i39;
  i3 = (int)X87_FIST32((float80)(int)u24 / arg8);
  if (i33 < 0x2d0) {
    i33 = -i8;
    i25 = -i9;
    i26 = (i6 - i8) + -1;
    i27 = (i7 - i9) + -1;
L_0806d55f:
    f16 = (float80)i33;
    f17 = (float80)i26;
    stk_88 = (float80)i25;
    stk_90 = (float80)i27;
    stk_8c = stk_90;
    f19 = f16;
  }
  else {
    if (i33 < 0x5a0) {
      i26 = (i6 - i8) + -1;
      i25 = -i9;
      i33 = (i7 - i9) + -1;
      i27 = -i8;
    }
    else {
      if (i33 < 0x870) {
        i33 = (i6 - i8) + -1;
        i25 = (i7 - i9) + -1;
        i26 = -i8;
        i27 = -i9;
        goto L_0806d55f;
      }
      if (0xb3f < i33) {
        return u24;
      }
      i26 = -i8;
      i25 = (i7 - i9) + -1;
      i33 = -i9;
      i27 = (i6 - i8) + -1;
    }
    f16 = (float80)i26;
    stk_8c = (float80)i33;
    f17 = (float80)i27;
    stk_90 = (float80)i25;
    stk_88 = stk_8c;
    f19 = f17;
  }
  stk_84 = (float80)i26;
  stk_8c = stk_8c * arg7;
  f16 = f16 * arg6;
  f18 = (float80)i25 * arg7;
  f17 = f17 * arg6;
  i33 = roundfloat((-f16 * f14 + f18 * f13) * arg9);
  i26 = roundfloat((-f17 * f14 + stk_8c * f13) * arg9);
  stk_54 = roundfloat((-(stk_84 * arg6) * f14 + stk_88 * arg7 * f13) * arg9);
  stk_94 = roundfloat((-(f19 * arg6) * f14 + stk_90 * arg7 * f13) * arg9);
  if ((stk_54 == i33) || (stk_54 == i26)) {
    stk_78 = 0;
    stk_74 = 0;
    stk_64 = (int)X87_FIST32((f16 * f13 + f18 * f14) * 65536.0 * arg8);
    stk_68 = (int)X87_FIST32((f17 * f13 + stk_8c * f14) * 65536.0 * arg8);
  }
  else {
    f19 = f13 * stk_84 * arg6 + stk_88 * arg7 * f14;
    stk_74 = (int)X87_FIST32(((f19 - (f16 * f13 + f18 * f14)) * 65536.0 * arg8) /
                          (float)(stk_54 - i33));
    if (stk_74 < 0) {
      stk_74 = -stk_74;
    }
    stk_78 = (int)X87_FIST32((((stk_8c * f14 + f17 * f13) - f19) * 65536.0 * arg8) /
                          (float)(stk_54 - i26));
    if (stk_78 < 0) {
      stk_78 = -stk_78;
    }
    stk_68 = (int)X87_FIST32(f19 * 65536.0 * arg8);
    stk_64 = stk_68;
  }
  for (; stk_54 < W_y1 - i23; stk_54 = stk_54 + 1) {
    i25 = stk_78;
    if (stk_54 < i33) {
      i25 = -stk_74;
    }
    stk_64 = stk_64 + i25;
    i25 = stk_78;
    if (i26 <= stk_54) {
      i25 = -stk_74;
    }
    stk_68 = stk_68 + i25;
  }
  if (W_y2 - i23 < stk_94) {
    stk_94 = W_y2 - i23;
  }
  i25 = SpriteDecompGetAndLockData(sprites,index);
  if (i25 == 0) {
    return 0;
  }
  i27 = SpriteDecompGetData(V_Current,V_CurrentIdx);
  sprite3 = (int *)sprites[5];
  if (sprite3 == (int *)0x0) {
    sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
  }
  else {
    EBPalUpdate(sprite3);
  }
  if (stk_54 <= stk_94) {
    do {
      i38 = stk_64 >> 0x10;
      i40 = stk_68 >> 0x10;
      if (W_x2 < i22 - i38) {
        i38 = i22 - W_x2;
      }
      if (i22 - i40 < W_x1) {
        i40 = i22 - W_x1;
      }
      stk_60 = (int)X87_FIST32(((((float80)i38 / arg8) * f12 -
                             ((float)stk_54 / arg9) * f15) * 65536.0) / (float80)i36) +
                 i8 * 0x10000;
      i37 = i9 * 0x10000 +
               (int)X87_FIST32(((((float80)i38 / arg8) * f15 +
                           ((float)stk_54 / arg9) * f12) * 65536.0) / (float80)i39);
      stk_38 = (uint16_t *)
                 (i27 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_54 + i23) * 4) +
                 (i22 - i38) * 2);
      i34 = (i40 - i38) + 1;
      i10 = i40 - i38;
      i31 = i3 * i34 + i37;
      for (i34 = stk_60 + i2 * i34;
          (SBORROW4(i40,i38) == i10 < 0 &&
          ((((i7 <= i31 >> 0x10 || (i6 <= i34 >> 0x10)) || (i31 >> 0x10 < 0)) ||
           (i34 >> 0x10 < 0)))); i34 = i34 - i2) {
        i40 = i40 + -1;
        i31 = i31 - i3;
        i10 = i40 - i38;
      }
      for (; (i38 <= i40 &&
             (((i7 <= i37 >> 0x10 || (i6 <= stk_60 >> 0x10)) ||
              ((i37 >> 0x10 < 0 || (stk_60 >> 0x10 < 0)))))); stk_60 = stk_60 + i2) {
        stk_38 = stk_38 + -1;
        i38 = i38 + 1;
        i37 = i37 + i3;
      }
      stk_50 = (i40 - i38) + 1;
      if (0 < stk_50) {
        do {
          b4 = *(uint8_t *)((stk_60 >> 0x10) + i25 + *(int *)(i5 + (i37 >> 0x10) * 4));
          if (b4 != 0) {
            u35 = (uint32_t)*(uint16_t *)((int)sprite3 + (uint32_t)b4 * 2 + 0x5c);
            u29 = (uint32_t)*stk_38;
            u24 = (u29 & 0xf800) + (u35 & 0xf800);
            if (0xf800 < u24) {
              u24 = 0xf800;
            }
            u1 = (u29 & 0x7e0) + (u35 & 0x7e0);
            u30 = (uint16_t)u1;
            if (0x7e0 < u1) {
              u30 = 0x7e0;
            }
            u35 = (u35 & 0x1f) + (u29 & 0x1f);
            u32 = (uint16_t)u35;
            if (0x1f < u35) {
              u32 = 0x1f;
            }
            *stk_38 = (uint16_t)u24 | u30 | u32;
          }
          stk_60 = stk_60 + i2;
          stk_38 = stk_38 + -1;
          i37 = i37 + i3;
          stk_50 = stk_50 + -1;
        } while (stk_50 != 0);
      }
      i38 = stk_78;
      if (stk_54 < i33) {
        i38 = -stk_74;
      }
      stk_64 = stk_64 + i38;
      i38 = stk_78;
      if (i26 <= stk_54) {
        i38 = -stk_74;
      }
      stk_68 = stk_68 + i38;
      stk_54 = stk_54 + 1;
    } while (stk_54 <= stk_94);
  }
  u24 = SpriteDecompUnlockData();
  return u24;
}
#undef stk_94
#undef stk_90
#undef stk_8c
#undef stk_88
#undef stk_84
#undef stk_78
#undef stk_74
#undef stk_68
#undef stk_64
#undef stk_60
#undef stk_54
#undef stk_50
#undef stk_38
#undef stk_20

/* W_RotateSpriteTransAdd8to16_B_P @ 0x0806df40, 8365 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, blended additively (colour 0 transparent), with
 * explicit source and destination alpha (256 = full). Clipped to the window
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
 *   arg10        int
 *   arg11        int
 *
 * Calls: SpriteArrayAccess, roundfloat, W_RotateSprite8to16_P,
 *        W_RotateSpriteTransAdd8to16_P, W_ScaleSpriteTransAdd_B_S,
 *        SpriteDecompGetAndLockData, SpriteDecompGetData,
 *        SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * C library: memset
 * Called by: W_RotateSpriteTransAdd_B_P
 *
 * Elecbyte file: src/lib/spr16add.c
 * Note: 1 accesses to parts of a variable are written as sized accesses.
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 21 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x2b0 bytes,
 *       17 variables), because their address is taken.
 * Note: 8 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t W_RotateSpriteTransAdd8to16_B_P
               (int *sprites,int index,float x2,float y,float arg5,float arg6,
               float arg7,float arg8,float arg9,int arg10,int arg11)

{
  uint16_t *pu1;
  uint32_t u2;
  int i3;
  int i4;
  uint8_t b5;
  int i6;
  int i7;
  int i8;
  int i9;
  int i10;
  int i11;
  uint64_t u12;
  float80 f13;
  float80 f14;
  float80 f15;
  float80 f16;
  float80 f17;
  float80 f18;
  float80 f19;
  float80 f20;
  uint16_t u21;
  uint16_t u22;
  int *sprite;
  int sprite2;
  int i25;
  int i26;
  uint32_t u27;
  int i28;
  int i29;
  int i30;
  int *sprite3;
  int i32;
  uint32_t u33;
  uint32_t u34;
  int i35;
  int i36;
  int i37;
  int i38;
  int i39;
  int i40;
  uint16_t entry_FPUControlWord;
  unsigned char frame[0x2b0] __attribute__((aligned(16)));
#define stk_2a4 (*(uint16_t **)(frame + 0xc))
#define stk_298 (*(int *)(frame + 0x18))
#define stk_294 (*(float *)(frame + 0x1c))
#define stk_290 (*(float *)(frame + 0x20))
#define stk_28c (*(float *)(frame + 0x24))
#define stk_288 (*(float *)(frame + 0x28))
#define stk_27c (*(int *)(frame + 0x34))
#define stk_278 (*(int *)(frame + 0x38))
#define stk_26c (*(int *)(frame + 0x44))
#define stk_268 (*(int *)(frame + 0x48))
#define stk_264 (*(int *)(frame + 0x4c))
#define stk_258 (*(int *)(frame + 0x58))
#define stk_254 (*(int *)(frame + 0x5c))
#define stk_250 (*(int *)(frame + 0x60))
#define stk_238 (*(uint16_t **)(frame + 0x78))
#define stk_220 (*(uint32_t *)(frame + 0x90))
#define stk_21c (*(uint16_t (*)[262])(frame + 0x94))
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  i6 = sprite[0xb];
  i25 = roundfloat(x2);
  i26 = roundfloat(y);
  if ((arg10 == 0x100) && (arg11 == 0)) {
    u27 = W_RotateSprite8to16_P
                       (sprites,index,x2,y,arg5,arg6,arg7,arg8,arg9);
    return u27;
  }
  if ((arg10 == 0x100) && (arg11 == 0x100)) {
    u27 = W_RotateSpriteTransAdd8to16_P
                       (sprites,index,x2,y,arg5,arg6,arg7,arg8,arg9);
    return u27;
  }
  if ((arg10 == 0) && (arg11 == 0x100)) {
    return 0;
  }
  stk_254 = (int)X87_FIST32(arg6 * 1024.0);
  if (stk_254 < 0) {
    stk_254 = -stk_254;
    arg5 = arg5 + 180.0;
  }
  stk_220 = CONCAT22((*(uint16_t *)((char *)&stk_220 + 2)),entry_FPUControlWord);
  stk_258 = (int)X87_FIST32(arg7 * 1024.0);
  if (stk_258 < 0) {
    stk_258 = -stk_258;
    arg5 = arg5 + 180.0;
  }
  if (stk_254 == 0) {
    return stk_220;
  }
  if (stk_258 == 0) {
    return stk_220;
  }
  if (arg5 < 0.0) {
    arg5 = (float)((int)X87_FIST32(-arg5 * ((float)0.0027777778f)) * 0x168 + 0x168) + arg5;
  }
  u12 = (int64_t)(int)X87_FIST32(arg5 * 8.0) % 0xb40;
  i36 = (int)u12;
  if (i36 == 0) {
L_0806e335:
    u27 = W_ScaleSpriteTransAdd_B_S
                       (sprites,index,x2,y,arg6 * arg8,arg7 * arg9,arg10
                        ,arg11);
    return u27;
  }
  if (i36 == 0x5a0) {
    arg7 = -arg7;
    arg6 = -arg6;
    goto L_0806e335;
  }
  i7 = *sprite;
  i8 = sprite[1];
  i9 = sprite[2];
  i10 = sprite[3];
  f13 = (float)SinTable[(i36 + 0x2d0) % 0xb40];
  f14 = f13 * 0.0009765625;
  f16 = (float)SinTable[(int)((int64_t)
                                 ((uint64_t)(uint32_t)(i36 >> 0x1f) << 0x20 | u12 & 0xffffffff) %
                                0xb40)];
  f15 = f16 * 0.0009765625;
  i3 = (int)X87_FIST32((float)((SinTable[(i36 + 0x2d0) % 0xb40] << 0x10) / stk_254) / arg8);
  u27 = (SinTable[(int)((int64_t)
                           ((uint64_t)(uint32_t)(i36 >> 0x1f) << 0x20 | u12 & 0xffffffff) % 0xb40
                          )] << 0x10) / stk_258;
  i4 = (int)X87_FIST32((float80)(int)u27 / arg8);
  if (i36 < 0x2d0) {
    i36 = -i9;
    i28 = -i10;
    i29 = (i7 - i9) + -1;
    i30 = (i8 - i10) + -1;
L_0806e57f:
    f17 = (float80)i36;
    f18 = (float80)i29;
    stk_28c = (float80)i28;
    stk_294 = (float80)i30;
    stk_290 = stk_294;
    f20 = f17;
  }
  else {
    if (i36 < 0x5a0) {
      i29 = (i7 - i9) + -1;
      i28 = -i10;
      i36 = (i8 - i10) + -1;
      i30 = -i9;
    }
    else {
      if (i36 < 0x870) {
        i36 = (i7 - i9) + -1;
        i28 = (i8 - i10) + -1;
        i29 = -i9;
        i30 = -i10;
        goto L_0806e57f;
      }
      if (0xb3f < i36) {
        return u27;
      }
      i29 = -i9;
      i28 = (i8 - i10) + -1;
      i36 = -i10;
      i30 = (i7 - i9) + -1;
    }
    f17 = (float80)i29;
    stk_290 = (float80)i36;
    f18 = (float80)i30;
    stk_294 = (float80)i28;
    stk_28c = stk_290;
    f20 = f18;
  }
  stk_288 = (float80)i29;
  stk_290 = stk_290 * arg7;
  f17 = f17 * arg6;
  f19 = (float80)i28 * arg7;
  f18 = f18 * arg6;
  i36 = roundfloat((-f17 * f15 + f19 * f14) * arg9);
  i28 = roundfloat((-f18 * f15 + stk_290 * f14) * arg9);
  stk_250 = roundfloat((-(stk_288 * arg6) * f15 + stk_28c * arg7 * f14) * arg9)
  ;
  stk_298 = roundfloat((-(f20 * arg6) * f15 + stk_294 * arg7 * f14) * arg9);
  if ((stk_250 == i36) || (stk_250 == i28)) {
    stk_27c = 0;
    stk_278 = 0;
    stk_268 = (int)X87_FIST32((f17 * f14 + f19 * f15) * 65536.0 * arg8);
    stk_26c = (int)X87_FIST32((f18 * f14 + stk_290 * f15) * 65536.0 * arg8);
  }
  else {
    f20 = f14 * stk_288 * arg6 + stk_28c * arg7 * f15;
    stk_278 = (int)X87_FIST32(((f20 - (f17 * f14 + f19 * f15)) * 65536.0 * arg8) /
                           (float)(stk_250 - i36));
    if (stk_278 < 0) {
      stk_278 = -stk_278;
    }
    stk_27c = (int)X87_FIST32((((stk_290 * f15 + f18 * f14) - f20) * 65536.0 * arg8) /
                           (float)(stk_250 - i28));
    if (stk_27c < 0) {
      stk_27c = -stk_27c;
    }
    stk_26c = (int)X87_FIST32(f20 * 65536.0 * arg8);
    stk_268 = stk_26c;
  }
  for (; stk_250 < W_y1 - i26; stk_250 = stk_250 + 1) {
    i29 = stk_27c;
    if (stk_250 < i36) {
      i29 = -stk_278;
    }
    stk_268 = stk_268 + i29;
    i29 = stk_27c;
    if (i28 <= stk_250) {
      i29 = -stk_278;
    }
    stk_26c = stk_26c + i29;
  }
  if (W_y2 - i26 < stk_298) {
    stk_298 = W_y2 - i26;
  }
  i29 = SpriteDecompGetAndLockData(sprites,index);
  if (i29 == 0) {
    return 0;
  }
  i30 = SpriteDecompGetData(V_Current,V_CurrentIdx);
  sprite3 = (int *)sprites[5];
  if (sprite3 == (int *)0x0) {
    sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
  }
  else {
    EBPalUpdate(sprite3);
  }
  pu1 = (uint16_t *)(sprite3 + 0x17);
  stk_2a4 = pu1;
  if (arg10 != 0x100) {
    stk_2a4 = stk_21c;
    if (arg10 == 0) {
      memset(stk_21c,0,sprite[5] * 2);
    }
    else if (arg10 == 0x80) {
      i40 = 1;
      i32 = sprite[5];
      if (1 < i32) {
        do {
          stk_21c[i40] = pu1[i40] >> 1 & 0xfbef;
          i40 = i40 + 1;
        } while (i40 < i32);
      }
    }
    else {
      i40 = 1;
      i32 = sprite[5];
      if (1 < i32) {
        do {
          u27 = (uint32_t)pu1[i40];
          stk_21c[i40] =
               (uint16_t)((u27 & 0xf800) * arg10 >> 8) & 0xf800 |
               (uint16_t)((u27 & 0x7e0) * arg10 >> 8) & 0x7e0 |
               (uint16_t)((u27 & 0x1f) * arg10 >> 8) & 0x1f;
          i40 = i40 + 1;
        } while (i40 < i32);
      }
    }
  }
  if (arg11 == 0) {
    if (stk_250 <= stk_298) {
      i32 = W_x1 - i25;
      do {
        i40 = stk_268 >> 0x10;
        if (stk_268 >> 0x10 < i32) {
          i40 = i32;
        }
        i39 = stk_26c >> 0x10;
        if (W_x2 - i25 < stk_26c >> 0x10) {
          i39 = W_x2 - i25;
        }
        stk_264 = (int)X87_FIST32(((((float80)i40 / arg8) * f13 -
                                ((float)stk_250 / arg9) * f16) * 65536.0) / (float)stk_254
                              ) + i9 * 0x10000;
        i38 = i10 * 0x10000 +
                 (int)X87_FIST32(((((float80)i40 / arg8) * f16 +
                             ((float)stk_250 / arg9) * f13) * 65536.0) / (float)stk_258);
        stk_238 = (uint16_t *)
                    (i30 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_250 + i26) * 4) +
                    (i25 + i40) * 2);
        i37 = (i39 - i40) + 1;
        i11 = i39 - i40;
        i35 = i4 * i37 + i38;
        for (i37 = stk_264 + i3 * i37;
            (SBORROW4(i39,i40) == i11 < 0 &&
            (((i8 <= i35 >> 0x10 || (i7 <= i37 >> 0x10)) ||
             ((i35 >> 0x10 < 0 || (i37 >> 0x10 < 0)))))); i37 = i37 - i3) {
          i39 = i39 + -1;
          i35 = i35 - i4;
          i11 = i39 - i40;
        }
        for (; (i40 <= i39 &&
               ((((i8 <= i38 >> 0x10 || (i7 <= stk_264 >> 0x10)) || (i38 >> 0x10 < 0))
                || (stk_264 >> 0x10 < 0)))); stk_264 = stk_264 + i3) {
          stk_238 = stk_238 + 1;
          i40 = i40 + 1;
          i38 = i38 + i4;
        }
        i40 = (i39 - i40) + 1;
        if (0 < i40) {
          do {
            b5 = *(uint8_t *)((stk_264 >> 0x10) + i29 + *(int *)(i6 + (i38 >> 0x10) * 4))
            ;
            if (b5 != 0) {
              *stk_238 = stk_2a4[b5];
            }
            stk_264 = stk_264 + i3;
            stk_238 = stk_238 + 1;
            i38 = i38 + i4;
            i40 = i40 + -1;
          } while (i40 != 0);
        }
        i40 = stk_27c;
        if (stk_250 < i36) {
          i40 = -stk_278;
        }
        stk_268 = stk_268 + i40;
        i40 = stk_27c;
        if (i28 <= stk_250) {
          i40 = -stk_278;
        }
        stk_26c = stk_26c + i40;
        stk_250 = stk_250 + 1;
      } while (stk_250 <= stk_298);
    }
  }
  else if ((arg10 + arg11 < 0x101) && (arg11 == 0x80)) {
    if (stk_250 <= stk_298) {
      i32 = W_x1 - i25;
      do {
        i40 = stk_268 >> 0x10;
        if (stk_268 >> 0x10 < i32) {
          i40 = i32;
        }
        i39 = stk_26c >> 0x10;
        if (W_x2 - i25 < stk_26c >> 0x10) {
          i39 = W_x2 - i25;
        }
        stk_264 = (int)X87_FIST32(((((float80)i40 / arg8) * f13 -
                                ((float)stk_250 / arg9) * f16) * 65536.0) / (float)stk_254
                              ) + i9 * 0x10000;
        i38 = i10 * 0x10000 +
                 (int)X87_FIST32(((((float80)i40 / arg8) * f16 +
                             ((float)stk_250 / arg9) * f13) * 65536.0) / (float)stk_258);
        stk_238 = (uint16_t *)
                    (i30 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_250 + i26) * 4) +
                    (i25 + i40) * 2);
        i37 = (i39 - i40) + 1;
        i11 = i39 - i40;
        i35 = i4 * i37 + i38;
        for (i37 = stk_264 + i3 * i37;
            (SBORROW4(i39,i40) == i11 < 0 &&
            ((((i8 <= i35 >> 0x10 || (i7 <= i37 >> 0x10)) || (i35 >> 0x10 < 0)) ||
             (i37 >> 0x10 < 0)))); i37 = i37 - i3) {
          i39 = i39 + -1;
          i35 = i35 - i4;
          i11 = i39 - i40;
        }
        for (; (i40 <= i39 &&
               (((i8 <= i38 >> 0x10 || (i7 <= stk_264 >> 0x10)) ||
                ((i38 >> 0x10 < 0 || (stk_264 >> 0x10 < 0)))))); stk_264 = stk_264 + i3)
        {
          stk_238 = stk_238 + 1;
          i40 = i40 + 1;
          i38 = i38 + i4;
        }
        i40 = (i39 - i40) + 1;
        if (0 < i40) {
          do {
            b5 = *(uint8_t *)((stk_264 >> 0x10) + i29 + *(int *)(i6 + (i38 >> 0x10) * 4))
            ;
            if (b5 != 0) {
              u22 = stk_2a4[b5];
              u21 = *stk_238 >> 1;
              *stk_238 = (u21 & 0x3e0) + (u22 & 0x7e0) |
                           (u21 & 0x7800) + (u22 & 0xf800) | (u21 & 0xf) + (u22 & 0x1f);
            }
            stk_264 = stk_264 + i3;
            stk_238 = stk_238 + 1;
            i38 = i38 + i4;
            i40 = i40 + -1;
          } while (i40 != 0);
        }
        i40 = stk_27c;
        if (stk_250 < i36) {
          i40 = -stk_278;
        }
        stk_268 = stk_268 + i40;
        i40 = stk_27c;
        if (i28 <= stk_250) {
          i40 = -stk_278;
        }
        stk_26c = stk_26c + i40;
        stk_250 = stk_250 + 1;
      } while (stk_250 <= stk_298);
    }
  }
  else if (arg10 + arg11 < 0x101) {
    if (stk_250 <= stk_298) {
      i32 = W_x1 - i25;
      do {
        i40 = stk_268 >> 0x10;
        if (stk_268 >> 0x10 < i32) {
          i40 = i32;
        }
        i39 = stk_26c >> 0x10;
        if (W_x2 - i25 < stk_26c >> 0x10) {
          i39 = W_x2 - i25;
        }
        stk_264 = (int)X87_FIST32(((((float80)i40 / arg8) * f13 -
                                ((float)stk_250 / arg9) * f16) * 65536.0) / (float)stk_254
                              ) + i9 * 0x10000;
        i38 = i10 * 0x10000 +
                 (int)X87_FIST32(((((float80)i40 / arg8) * f16 +
                             ((float)stk_250 / arg9) * f13) * 65536.0) / (float)stk_258);
        stk_238 = (uint16_t *)
                    (i30 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_250 + i26) * 4) +
                    (i25 + i40) * 2);
        i37 = (i39 - i40) + 1;
        i11 = i39 - i40;
        i35 = i4 * i37 + i38;
        for (i37 = stk_264 + i3 * i37;
            (SBORROW4(i39,i40) == i11 < 0 &&
            (((i8 <= i35 >> 0x10 || (i7 <= i37 >> 0x10)) ||
             ((i35 >> 0x10 < 0 || (i37 >> 0x10 < 0)))))); i37 = i37 - i3) {
          i39 = i39 + -1;
          i35 = i35 - i4;
          i11 = i39 - i40;
        }
        for (; (i40 <= i39 &&
               (((i8 <= i38 >> 0x10 || (i7 <= stk_264 >> 0x10)) ||
                ((i38 >> 0x10 < 0 || (stk_264 >> 0x10 < 0)))))); stk_264 = stk_264 + i3)
        {
          stk_238 = stk_238 + 1;
          i40 = i40 + 1;
          i38 = i38 + i4;
        }
        i40 = (i39 - i40) + 1;
        if (0 < i40) {
          do {
            b5 = *(uint8_t *)((stk_264 >> 0x10) + i29 + *(int *)(i6 + (i38 >> 0x10) * 4))
            ;
            if (b5 != 0) {
              u22 = stk_2a4[b5];
              u27 = (uint32_t)*stk_238;
              *stk_238 = ((uint16_t)((u27 & 0x7e0) * arg11 >> 8) & 0x7e0) + (u22 & 0x7e0) |
                           ((uint16_t)((u27 & 0xf800) * arg11 >> 8) & 0xf800) +
                           (u22 & 0xf800) |
                           ((uint16_t)((u27 & 0x1f) * arg11 >> 8) & 0x1f) + (u22 & 0x1f);
            }
            stk_264 = stk_264 + i3;
            stk_238 = stk_238 + 1;
            i38 = i38 + i4;
            i40 = i40 + -1;
          } while (i40 != 0);
        }
        i40 = stk_27c;
        if (stk_250 < i36) {
          i40 = -stk_278;
        }
        stk_268 = stk_268 + i40;
        i40 = stk_27c;
        if (i28 <= stk_250) {
          i40 = -stk_278;
        }
        stk_26c = stk_26c + i40;
        stk_250 = stk_250 + 1;
      } while (stk_250 <= stk_298);
    }
  }
  else if (arg11 == 0x80) {
    if (stk_250 <= stk_298) {
      i32 = W_x1 - i25;
      do {
        i40 = stk_268 >> 0x10;
        if (stk_268 >> 0x10 < i32) {
          i40 = i32;
        }
        i39 = stk_26c >> 0x10;
        if (W_x2 - i25 < stk_26c >> 0x10) {
          i39 = W_x2 - i25;
        }
        stk_264 = (int)X87_FIST32(((((float80)i40 / arg8) * f13 -
                                ((float)stk_250 / arg9) * f16) * 65536.0) / (float)stk_254
                              ) + i9 * 0x10000;
        i38 = i10 * 0x10000 +
                 (int)X87_FIST32(((((float80)i40 / arg8) * f16 +
                             ((float)stk_250 / arg9) * f13) * 65536.0) / (float)stk_258);
        stk_238 = (uint16_t *)
                    (i30 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_250 + i26) * 4) +
                    (i25 + i40) * 2);
        i37 = (i39 - i40) + 1;
        i11 = i39 - i40;
        i35 = i4 * i37 + i38;
        for (i37 = stk_264 + i3 * i37;
            (SBORROW4(i39,i40) == i11 < 0 &&
            (((i8 <= i35 >> 0x10 || (i7 <= i37 >> 0x10)) ||
             ((i35 >> 0x10 < 0 || (i37 >> 0x10 < 0)))))); i37 = i37 - i3) {
          i39 = i39 + -1;
          i35 = i35 - i4;
          i11 = i39 - i40;
        }
        for (; (i40 <= i39 &&
               ((((i8 <= i38 >> 0x10 || (i7 <= stk_264 >> 0x10)) || (i38 >> 0x10 < 0))
                || (stk_264 >> 0x10 < 0)))); stk_264 = stk_264 + i3) {
          stk_238 = stk_238 + 1;
          i40 = i40 + 1;
          i38 = i38 + i4;
        }
        i40 = (i39 - i40) + 1;
        if (0 < i40) {
          do {
            b5 = *(uint8_t *)((stk_264 >> 0x10) + i29 + *(int *)(i6 + (i38 >> 0x10) * 4))
            ;
            if (b5 != 0) {
              u33 = (uint32_t)stk_2a4[b5];
              u34 = (uint32_t)(*stk_238 >> 1);
              u27 = (u34 & 0x7800) + (u33 & 0xf800);
              if (0xf800 < u27) {
                u27 = 0xf800;
              }
              u2 = (u34 & 0x3e0) + (u33 & 0x7e0);
              u22 = (uint16_t)u2;
              if (0x7e0 < u2) {
                u22 = 0x7e0;
              }
              u33 = (u34 & 0xf) + (u33 & 0x1f);
              u21 = (uint16_t)u33;
              if (0x1f < u33) {
                u21 = 0x1f;
              }
              *stk_238 = u22 | (uint16_t)u27 | u21;
            }
            stk_264 = stk_264 + i3;
            stk_238 = stk_238 + 1;
            i38 = i38 + i4;
            i40 = i40 + -1;
          } while (i40 != 0);
        }
        i40 = stk_27c;
        if (stk_250 < i36) {
          i40 = -stk_278;
        }
        stk_268 = stk_268 + i40;
        i40 = stk_27c;
        if (i28 <= stk_250) {
          i40 = -stk_278;
        }
        stk_26c = stk_26c + i40;
        stk_250 = stk_250 + 1;
      } while (stk_250 <= stk_298);
    }
  }
  else if (stk_250 <= stk_298) {
    i32 = W_x1 - i25;
    do {
      i40 = stk_268 >> 0x10;
      if (stk_268 >> 0x10 < i32) {
        i40 = i32;
      }
      i39 = stk_26c >> 0x10;
      if (W_x2 - i25 < stk_26c >> 0x10) {
        i39 = W_x2 - i25;
      }
      stk_264 = (int)X87_FIST32(((((float80)i40 / arg8) * f13 -
                              ((float)stk_250 / arg9) * f16) * 65536.0) / (float)stk_254)
                  + i9 * 0x10000;
      i38 = i10 * 0x10000 +
               (int)X87_FIST32(((((float80)i40 / arg8) * f16 +
                           ((float)stk_250 / arg9) * f13) * 65536.0) / (float)stk_258);
      stk_238 = (uint16_t *)
                  (i30 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_250 + i26) * 4) +
                  (i25 + i40) * 2);
      i37 = (i39 - i40) + 1;
      i11 = i39 - i40;
      i35 = i4 * i37 + i38;
      for (i37 = stk_264 + i3 * i37;
          (SBORROW4(i39,i40) == i11 < 0 &&
          ((((i8 <= i35 >> 0x10 || (i7 <= i37 >> 0x10)) || (i35 >> 0x10 < 0)) ||
           (i37 >> 0x10 < 0)))); i37 = i37 - i3) {
        i39 = i39 + -1;
        i35 = i35 - i4;
        i11 = i39 - i40;
      }
      for (; (i40 <= i39 &&
             (((i8 <= i38 >> 0x10 || (i7 <= stk_264 >> 0x10)) ||
              ((i38 >> 0x10 < 0 || (stk_264 >> 0x10 < 0)))))); stk_264 = stk_264 + i3) {
        stk_238 = stk_238 + 1;
        i40 = i40 + 1;
        i38 = i38 + i4;
      }
      i40 = (i39 - i40) + 1;
      if (0 < i40) {
        do {
          b5 = *(uint8_t *)((stk_264 >> 0x10) + i29 + *(int *)(i6 + (i38 >> 0x10) * 4));
          if (b5 != 0) {
            u33 = (uint32_t)stk_2a4[b5];
            u34 = (uint32_t)*stk_238;
            u27 = ((u34 & 0xf800) * arg11 >> 8 & 0xf800) + (u33 & 0xf800);
            if (0xf800 < u27) {
              u27 = 0xf800;
            }
            u2 = ((u34 & 0x7e0) * arg11 >> 8 & 0x7e0) + (u33 & 0x7e0);
            u22 = (uint16_t)u2;
            if (0x7e0 < u2) {
              u22 = 0x7e0;
            }
            u33 = ((u34 & 0x1f) * arg11 >> 8 & 0x1f) + (u33 & 0x1f);
            u21 = (uint16_t)u33;
            if (0x1f < u33) {
              u21 = 0x1f;
            }
            *stk_238 = u22 | (uint16_t)u27 | u21;
          }
          stk_264 = stk_264 + i3;
          stk_238 = stk_238 + 1;
          i38 = i38 + i4;
          i40 = i40 + -1;
        } while (i40 != 0);
      }
      i40 = stk_27c;
      if (stk_250 < i36) {
        i40 = -stk_278;
      }
      stk_268 = stk_268 + i40;
      i40 = stk_27c;
      if (i28 <= stk_250) {
        i40 = -stk_278;
      }
      stk_26c = stk_26c + i40;
      stk_250 = stk_250 + 1;
    } while (stk_250 <= stk_298);
  }
  u27 = SpriteDecompUnlockData();
  return u27;
}
#undef stk_2a4
#undef stk_298
#undef stk_294
#undef stk_290
#undef stk_28c
#undef stk_288
#undef stk_27c
#undef stk_278
#undef stk_26c
#undef stk_268
#undef stk_264
#undef stk_258
#undef stk_254
#undef stk_250
#undef stk_238
#undef stk_220
#undef stk_21c

/* W_RotateSpriteTransAddMirH8to16_B_P @ 0x0806fff0, 8301 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, blended additively (colour 0 transparent),
 * mirrored horizontally, with explicit source and destination alpha (256 =
 * full). Clipped to the window set by W_Define. This is the pixel loop: it
 * reads the 8-bit sprite rows through the sprite's palette converted to
 * 16-bit colours and writes 16-bit pixels. Scaling without rotation is
 * handed to the scaled blitter.
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
 *   arg10        int
 *   arg11        int
 *
 * Calls: SpriteArrayAccess, roundfloat, W_RotateSpriteMirH8to16_P,
 *        W_RotateSpriteTransAddMirH8to16_P, W_ScaleSpriteTransAdd_B_S,
 *        SpriteDecompGetAndLockData, SpriteDecompGetData,
 *        SpriteArrayPalUpdateAndAccess, EBPalUpdate,
 *        SpriteDecompUnlockData
 * C library: memset
 * Called by: W_RotateSpriteTransAdd_B_P
 *
 * Elecbyte file: src/lib/spr16add.c
 * Note: 1 accesses to parts of a variable are written as sized accesses.
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 21 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x2b0 bytes,
 *       17 variables), because their address is taken.
 * Note: 8 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t W_RotateSpriteTransAddMirH8to16_B_P
               (int *sprites,int index,float x2,float y,float arg5,float arg6,
               float arg7,float arg8,float arg9,int arg10,int arg11)

{
  uint16_t *pu1;
  uint32_t u2;
  int i3;
  int i4;
  uint8_t b5;
  int i6;
  int i7;
  int i8;
  int i9;
  int i10;
  int i11;
  uint64_t u12;
  float80 f13;
  float80 f14;
  float80 f15;
  float80 f16;
  float80 f17;
  float80 f18;
  float80 f19;
  float80 f20;
  uint16_t u21;
  uint16_t u22;
  int *sprite;
  int sprite2;
  int i25;
  int i26;
  uint32_t u27;
  int i28;
  int i29;
  int i30;
  int *sprite3;
  uint32_t u32;
  uint32_t u33;
  int i34;
  int i35;
  int i36;
  int i37;
  int i38;
  int i39;
  uint16_t entry_FPUControlWord;
  unsigned char frame[0x2b0] __attribute__((aligned(16)));
#define stk_2a4 (*(uint16_t **)(frame + 0xc))
#define stk_298 (*(int *)(frame + 0x18))
#define stk_294 (*(float *)(frame + 0x1c))
#define stk_290 (*(float *)(frame + 0x20))
#define stk_28c (*(float *)(frame + 0x24))
#define stk_288 (*(float *)(frame + 0x28))
#define stk_27c (*(int *)(frame + 0x34))
#define stk_278 (*(int *)(frame + 0x38))
#define stk_26c (*(int *)(frame + 0x44))
#define stk_268 (*(int *)(frame + 0x48))
#define stk_264 (*(int *)(frame + 0x4c))
#define stk_258 (*(int *)(frame + 0x58))
#define stk_254 (*(int *)(frame + 0x5c))
#define stk_250 (*(int *)(frame + 0x60))
#define stk_238 (*(uint16_t **)(frame + 0x78))
#define stk_220 (*(uint32_t *)(frame + 0x90))
#define stk_21c (*(uint16_t (*)[262])(frame + 0x94))
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  sprite2 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  i6 = sprite[0xb];
  i25 = roundfloat(x2);
  i26 = roundfloat(y);
  if ((arg10 == 0x100) && (arg11 == 0)) {
    u27 = W_RotateSpriteMirH8to16_P
                       (sprites,index,x2,y,arg5,arg6,arg7,arg8,arg9);
    return u27;
  }
  if ((arg10 == 0x100) && (arg11 == 0x100)) {
    u27 = W_RotateSpriteTransAddMirH8to16_P
                       (sprites,index,x2,y,arg5,arg6,arg7,arg8,arg9);
    return u27;
  }
  if ((arg10 == 0) && (arg11 == 0x100)) {
    return 0;
  }
  stk_254 = (int)X87_FIST32(arg6 * 1024.0);
  if (stk_254 < 0) {
    stk_254 = -stk_254;
    arg5 = arg5 + 180.0;
  }
  stk_220 = CONCAT22((*(uint16_t *)((char *)&stk_220 + 2)),entry_FPUControlWord);
  stk_258 = (int)X87_FIST32(arg7 * 1024.0);
  if (stk_258 < 0) {
    stk_258 = -stk_258;
    arg5 = arg5 + 180.0;
  }
  if (stk_254 == 0) {
    return stk_220;
  }
  if (stk_258 == 0) {
    return stk_220;
  }
  if (arg5 < 0.0) {
    arg5 = (float)((int)X87_FIST32(-arg5 * ((float)0.0027777778f)) * 0x168 + 0x168) + arg5;
  }
  u12 = (int64_t)(int)X87_FIST32(arg5 * 8.0) % 0xb40;
  i35 = (int)u12;
  if (i35 == 0) {
    arg6 = -arg6;
L_080703e8:
    u27 = W_ScaleSpriteTransAdd_B_S
                       (sprites,index,x2,y,arg6 * arg8,arg7 * arg9,arg10
                        ,arg11);
    return u27;
  }
  if (i35 == 0x5a0) {
    arg7 = -arg7;
    goto L_080703e8;
  }
  i7 = *sprite;
  i8 = sprite[1];
  i9 = sprite[2];
  i10 = sprite[3];
  f13 = (float)SinTable[(i35 + 0x2d0) % 0xb40];
  f14 = f13 * 0.0009765625;
  f16 = (float)SinTable[(int)((int64_t)
                                 ((uint64_t)(uint32_t)(i35 >> 0x1f) << 0x20 | u12 & 0xffffffff) %
                                0xb40)];
  f15 = f16 * 0.0009765625;
  i3 = (int)X87_FIST32((float)((SinTable[(i35 + 0x2d0) % 0xb40] << 0x10) / stk_254) / arg8);
  u27 = (SinTable[(int)((int64_t)
                           ((uint64_t)(uint32_t)(i35 >> 0x1f) << 0x20 | u12 & 0xffffffff) % 0xb40
                          )] << 0x10) / stk_258;
  i4 = (int)X87_FIST32((float80)(int)u27 / arg8);
  if (i35 < 0x2d0) {
    i35 = -i9;
    i28 = -i10;
    i29 = (i7 - i9) + -1;
    i30 = (i8 - i10) + -1;
L_08070625:
    f17 = (float80)i35;
    f18 = (float80)i29;
    stk_28c = (float80)i28;
    stk_294 = (float80)i30;
    stk_290 = stk_294;
    f20 = f17;
  }
  else {
    if (i35 < 0x5a0) {
      i29 = (i7 - i9) + -1;
      i28 = -i10;
      i35 = (i8 - i10) + -1;
      i30 = -i9;
    }
    else {
      if (i35 < 0x870) {
        i35 = (i7 - i9) + -1;
        i28 = (i8 - i10) + -1;
        i29 = -i9;
        i30 = -i10;
        goto L_08070625;
      }
      if (0xb3f < i35) {
        return u27;
      }
      i29 = -i9;
      i28 = (i8 - i10) + -1;
      i35 = -i10;
      i30 = (i7 - i9) + -1;
    }
    f17 = (float80)i29;
    stk_290 = (float80)i35;
    f18 = (float80)i30;
    stk_294 = (float80)i28;
    stk_28c = stk_290;
    f20 = f18;
  }
  stk_288 = (float80)i29;
  stk_290 = stk_290 * arg7;
  f17 = f17 * arg6;
  f19 = (float80)i28 * arg7;
  f18 = f18 * arg6;
  i35 = roundfloat((-f17 * f15 + f19 * f14) * arg9);
  i29 = roundfloat((-f18 * f15 + stk_290 * f14) * arg9);
  stk_250 = roundfloat((-(stk_288 * arg6) * f15 + stk_28c * arg7 * f14) * arg9)
  ;
  stk_298 = roundfloat((-(f20 * arg6) * f15 + stk_294 * arg7 * f14) * arg9);
  if ((stk_250 == i35) || (stk_250 == i29)) {
    stk_27c = 0;
    stk_278 = 0;
    stk_268 = (int)X87_FIST32((f17 * f14 + f19 * f15) * 65536.0 * arg8);
    stk_26c = (int)X87_FIST32((f18 * f14 + stk_290 * f15) * 65536.0 * arg8);
  }
  else {
    f20 = f14 * stk_288 * arg6 + stk_28c * arg7 * f15;
    stk_278 = (int)X87_FIST32(((f20 - (f17 * f14 + f19 * f15)) * 65536.0 * arg8) /
                           (float)(stk_250 - i35));
    if (stk_278 < 0) {
      stk_278 = -stk_278;
    }
    stk_27c = (int)X87_FIST32((((stk_290 * f15 + f18 * f14) - f20) * 65536.0 * arg8) /
                           (float)(stk_250 - i29));
    if (stk_27c < 0) {
      stk_27c = -stk_27c;
    }
    stk_26c = (int)X87_FIST32(f20 * 65536.0 * arg8);
    stk_268 = stk_26c;
  }
  for (; stk_250 < W_y1 - i26; stk_250 = stk_250 + 1) {
    i28 = stk_27c;
    if (stk_250 < i35) {
      i28 = -stk_278;
    }
    stk_268 = stk_268 + i28;
    i28 = stk_27c;
    if (i29 <= stk_250) {
      i28 = -stk_278;
    }
    stk_26c = stk_26c + i28;
  }
  if (W_y2 - i26 < stk_298) {
    stk_298 = W_y2 - i26;
  }
  i28 = SpriteDecompGetAndLockData(sprites,index);
  if (i28 == 0) {
    return 0;
  }
  i30 = SpriteDecompGetData(V_Current,V_CurrentIdx);
  sprite3 = (int *)sprites[5];
  if (sprite3 == (int *)0x0) {
    sprite3 = SpriteArrayPalUpdateAndAccess((int)sprites,sprite[0xc]);
  }
  else {
    EBPalUpdate(sprite3);
  }
  pu1 = (uint16_t *)(sprite3 + 0x17);
  stk_2a4 = pu1;
  if (arg10 != 0x100) {
    stk_2a4 = stk_21c;
    if (arg10 == 0) {
      memset(stk_21c,0,sprite[5] * 2);
    }
    else if (arg10 == 0x80) {
      i39 = 1;
      i38 = sprite[5];
      if (1 < i38) {
        do {
          stk_21c[i39] = pu1[i39] >> 1 & 0xfbef;
          i39 = i39 + 1;
        } while (i39 < i38);
      }
    }
    else {
      i39 = 1;
      i38 = sprite[5];
      if (1 < i38) {
        do {
          u27 = (uint32_t)pu1[i39];
          stk_21c[i39] =
               (uint16_t)((u27 & 0xf800) * arg10 >> 8) & 0xf800 |
               (uint16_t)((u27 & 0x7e0) * arg10 >> 8) & 0x7e0 |
               (uint16_t)((u27 & 0x1f) * arg10 >> 8) & 0x1f;
          i39 = i39 + 1;
        } while (i39 < i38);
      }
    }
  }
  if (arg11 == 0) {
    if (stk_250 <= stk_298) {
      do {
        i38 = stk_268 >> 0x10;
        i39 = stk_26c >> 0x10;
        if (W_x2 < i25 - i38) {
          i38 = i25 - W_x2;
        }
        if (i25 - i39 < W_x1) {
          i39 = i25 - W_x1;
        }
        stk_264 = (int)X87_FIST32(((((float80)i38 / arg8) * f13 -
                                ((float)stk_250 / arg9) * f16) * 65536.0) / (float)stk_254
                              ) + i9 * 0x10000;
        i37 = i10 * 0x10000 +
                 (int)X87_FIST32(((((float80)i38 / arg8) * f16 +
                             ((float)stk_250 / arg9) * f13) * 65536.0) / (float)stk_258);
        stk_238 = (uint16_t *)
                    (i30 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_250 + i26) * 4) +
                    (i25 - i38) * 2);
        i36 = (i39 - i38) + 1;
        i11 = i39 - i38;
        i34 = i4 * i36 + i37;
        for (i36 = stk_264 + i3 * i36;
            (SBORROW4(i39,i38) == i11 < 0 &&
            (((i8 <= i34 >> 0x10 || (i7 <= i36 >> 0x10)) ||
             ((i34 >> 0x10 < 0 || (i36 >> 0x10 < 0)))))); i36 = i36 - i3) {
          i39 = i39 + -1;
          i34 = i34 - i4;
          i11 = i39 - i38;
        }
        for (; (i38 <= i39 &&
               ((((i8 <= i37 >> 0x10 || (i7 <= stk_264 >> 0x10)) || (i37 >> 0x10 < 0))
                || (stk_264 >> 0x10 < 0)))); stk_264 = stk_264 + i3) {
          stk_238 = stk_238 + -1;
          i38 = i38 + 1;
          i37 = i37 + i4;
        }
        i38 = (i39 - i38) + 1;
        if (0 < i38) {
          do {
            b5 = *(uint8_t *)((stk_264 >> 0x10) + i28 + *(int *)(i6 + (i37 >> 0x10) * 4))
            ;
            if (b5 != 0) {
              *stk_238 = stk_2a4[b5];
            }
            stk_264 = stk_264 + i3;
            stk_238 = stk_238 + -1;
            i37 = i37 + i4;
            i38 = i38 + -1;
          } while (i38 != 0);
        }
        i38 = stk_27c;
        if (stk_250 < i35) {
          i38 = -stk_278;
        }
        stk_268 = stk_268 + i38;
        i38 = stk_27c;
        if (i29 <= stk_250) {
          i38 = -stk_278;
        }
        stk_26c = stk_26c + i38;
        stk_250 = stk_250 + 1;
      } while (stk_250 <= stk_298);
    }
  }
  else if ((arg10 + arg11 < 0x101) && (arg11 == 0x80)) {
    if (stk_250 <= stk_298) {
      do {
        i38 = stk_268 >> 0x10;
        i39 = stk_26c >> 0x10;
        if (W_x2 < i25 - i38) {
          i38 = i25 - W_x2;
        }
        if (i25 - i39 < W_x1) {
          i39 = i25 - W_x1;
        }
        stk_264 = (int)X87_FIST32(((((float80)i38 / arg8) * f13 -
                                ((float)stk_250 / arg9) * f16) * 65536.0) / (float)stk_254
                              ) + i9 * 0x10000;
        i37 = i10 * 0x10000 +
                 (int)X87_FIST32(((((float80)i38 / arg8) * f16 +
                             ((float)stk_250 / arg9) * f13) * 65536.0) / (float)stk_258);
        stk_238 = (uint16_t *)
                    (i30 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_250 + i26) * 4) +
                    (i25 - i38) * 2);
        i36 = (i39 - i38) + 1;
        i11 = i39 - i38;
        i34 = i4 * i36 + i37;
        for (i36 = stk_264 + i3 * i36;
            (SBORROW4(i39,i38) == i11 < 0 &&
            ((((i8 <= i34 >> 0x10 || (i7 <= i36 >> 0x10)) || (i34 >> 0x10 < 0)) ||
             (i36 >> 0x10 < 0)))); i36 = i36 - i3) {
          i39 = i39 + -1;
          i34 = i34 - i4;
          i11 = i39 - i38;
        }
        for (; (i38 <= i39 &&
               (((i8 <= i37 >> 0x10 || (i7 <= stk_264 >> 0x10)) ||
                ((i37 >> 0x10 < 0 || (stk_264 >> 0x10 < 0)))))); stk_264 = stk_264 + i3)
        {
          stk_238 = stk_238 + -1;
          i38 = i38 + 1;
          i37 = i37 + i4;
        }
        i38 = (i39 - i38) + 1;
        if (0 < i38) {
          do {
            b5 = *(uint8_t *)((stk_264 >> 0x10) + i28 + *(int *)(i6 + (i37 >> 0x10) * 4))
            ;
            if (b5 != 0) {
              u22 = stk_2a4[b5];
              u21 = *stk_238 >> 1;
              *stk_238 = (u21 & 0x3e0) + (u22 & 0x7e0) |
                           (u21 & 0x7800) + (u22 & 0xf800) | (u21 & 0xf) + (u22 & 0x1f);
            }
            stk_264 = stk_264 + i3;
            stk_238 = stk_238 + -1;
            i37 = i37 + i4;
            i38 = i38 + -1;
          } while (i38 != 0);
        }
        i38 = stk_27c;
        if (stk_250 < i35) {
          i38 = -stk_278;
        }
        stk_268 = stk_268 + i38;
        i38 = stk_27c;
        if (i29 <= stk_250) {
          i38 = -stk_278;
        }
        stk_26c = stk_26c + i38;
        stk_250 = stk_250 + 1;
      } while (stk_250 <= stk_298);
    }
  }
  else if (arg10 + arg11 < 0x101) {
    if (stk_250 <= stk_298) {
      do {
        i38 = stk_268 >> 0x10;
        i39 = stk_26c >> 0x10;
        if (W_x2 < i25 - i38) {
          i38 = i25 - W_x2;
        }
        if (i25 - i39 < W_x1) {
          i39 = i25 - W_x1;
        }
        stk_264 = (int)X87_FIST32(((((float80)i38 / arg8) * f13 -
                                ((float)stk_250 / arg9) * f16) * 65536.0) / (float)stk_254
                              ) + i9 * 0x10000;
        i37 = i10 * 0x10000 +
                 (int)X87_FIST32(((((float80)i38 / arg8) * f16 +
                             ((float)stk_250 / arg9) * f13) * 65536.0) / (float)stk_258);
        stk_238 = (uint16_t *)
                    (i30 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_250 + i26) * 4) +
                    (i25 - i38) * 2);
        i36 = (i39 - i38) + 1;
        i11 = i39 - i38;
        i34 = i4 * i36 + i37;
        for (i36 = stk_264 + i3 * i36;
            (SBORROW4(i39,i38) == i11 < 0 &&
            (((i8 <= i34 >> 0x10 || (i7 <= i36 >> 0x10)) ||
             ((i34 >> 0x10 < 0 || (i36 >> 0x10 < 0)))))); i36 = i36 - i3) {
          i39 = i39 + -1;
          i34 = i34 - i4;
          i11 = i39 - i38;
        }
        for (; (i38 <= i39 &&
               (((i8 <= i37 >> 0x10 || (i7 <= stk_264 >> 0x10)) ||
                ((i37 >> 0x10 < 0 || (stk_264 >> 0x10 < 0)))))); stk_264 = stk_264 + i3)
        {
          stk_238 = stk_238 + -1;
          i38 = i38 + 1;
          i37 = i37 + i4;
        }
        i38 = (i39 - i38) + 1;
        if (0 < i38) {
          do {
            b5 = *(uint8_t *)((stk_264 >> 0x10) + i28 + *(int *)(i6 + (i37 >> 0x10) * 4))
            ;
            if (b5 != 0) {
              u22 = stk_2a4[b5];
              u27 = (uint32_t)*stk_238;
              *stk_238 = ((uint16_t)((u27 & 0x7e0) * arg11 >> 8) & 0x7e0) + (u22 & 0x7e0) |
                           ((uint16_t)((u27 & 0xf800) * arg11 >> 8) & 0xf800) +
                           (u22 & 0xf800) |
                           ((uint16_t)((u27 & 0x1f) * arg11 >> 8) & 0x1f) + (u22 & 0x1f);
            }
            stk_264 = stk_264 + i3;
            stk_238 = stk_238 + -1;
            i37 = i37 + i4;
            i38 = i38 + -1;
          } while (i38 != 0);
        }
        i38 = stk_27c;
        if (stk_250 < i35) {
          i38 = -stk_278;
        }
        stk_268 = stk_268 + i38;
        i38 = stk_27c;
        if (i29 <= stk_250) {
          i38 = -stk_278;
        }
        stk_26c = stk_26c + i38;
        stk_250 = stk_250 + 1;
      } while (stk_250 <= stk_298);
    }
  }
  else if (arg11 == 0x80) {
    if (stk_250 <= stk_298) {
      do {
        i38 = stk_268 >> 0x10;
        i39 = stk_26c >> 0x10;
        if (W_x2 < i25 - i38) {
          i38 = i25 - W_x2;
        }
        if (i25 - i39 < W_x1) {
          i39 = i25 - W_x1;
        }
        stk_264 = (int)X87_FIST32(((((float80)i38 / arg8) * f13 -
                                ((float)stk_250 / arg9) * f16) * 65536.0) / (float)stk_254
                              ) + i9 * 0x10000;
        i37 = i10 * 0x10000 +
                 (int)X87_FIST32(((((float80)i38 / arg8) * f16 +
                             ((float)stk_250 / arg9) * f13) * 65536.0) / (float)stk_258);
        stk_238 = (uint16_t *)
                    (i30 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_250 + i26) * 4) +
                    (i25 - i38) * 2);
        i36 = (i39 - i38) + 1;
        i11 = i39 - i38;
        i34 = i4 * i36 + i37;
        for (i36 = stk_264 + i3 * i36;
            (SBORROW4(i39,i38) == i11 < 0 &&
            (((i8 <= i34 >> 0x10 || (i7 <= i36 >> 0x10)) ||
             ((i34 >> 0x10 < 0 || (i36 >> 0x10 < 0)))))); i36 = i36 - i3) {
          i39 = i39 + -1;
          i34 = i34 - i4;
          i11 = i39 - i38;
        }
        for (; (i38 <= i39 &&
               ((((i8 <= i37 >> 0x10 || (i7 <= stk_264 >> 0x10)) || (i37 >> 0x10 < 0))
                || (stk_264 >> 0x10 < 0)))); stk_264 = stk_264 + i3) {
          stk_238 = stk_238 + -1;
          i38 = i38 + 1;
          i37 = i37 + i4;
        }
        i38 = (i39 - i38) + 1;
        if (0 < i38) {
          do {
            b5 = *(uint8_t *)((stk_264 >> 0x10) + i28 + *(int *)(i6 + (i37 >> 0x10) * 4))
            ;
            if (b5 != 0) {
              u32 = (uint32_t)stk_2a4[b5];
              u33 = (uint32_t)(*stk_238 >> 1);
              u27 = (u33 & 0x7800) + (u32 & 0xf800);
              if (0xf800 < u27) {
                u27 = 0xf800;
              }
              u2 = (u33 & 0x3e0) + (u32 & 0x7e0);
              u22 = (uint16_t)u2;
              if (0x7e0 < u2) {
                u22 = 0x7e0;
              }
              u32 = (u33 & 0xf) + (u32 & 0x1f);
              u21 = (uint16_t)u32;
              if (0x1f < u32) {
                u21 = 0x1f;
              }
              *stk_238 = u22 | (uint16_t)u27 | u21;
            }
            stk_264 = stk_264 + i3;
            stk_238 = stk_238 + -1;
            i37 = i37 + i4;
            i38 = i38 + -1;
          } while (i38 != 0);
        }
        i38 = stk_27c;
        if (stk_250 < i35) {
          i38 = -stk_278;
        }
        stk_268 = stk_268 + i38;
        i38 = stk_27c;
        if (i29 <= stk_250) {
          i38 = -stk_278;
        }
        stk_26c = stk_26c + i38;
        stk_250 = stk_250 + 1;
      } while (stk_250 <= stk_298);
    }
  }
  else if (stk_250 <= stk_298) {
    do {
      i38 = stk_268 >> 0x10;
      i39 = stk_26c >> 0x10;
      if (W_x2 < i25 - i38) {
        i38 = i25 - W_x2;
      }
      if (i25 - i39 < W_x1) {
        i39 = i25 - W_x1;
      }
      stk_264 = (int)X87_FIST32(((((float80)i38 / arg8) * f13 -
                              ((float)stk_250 / arg9) * f16) * 65536.0) / (float)stk_254)
                  + i9 * 0x10000;
      i37 = i10 * 0x10000 +
               (int)X87_FIST32(((((float80)i38 / arg8) * f16 +
                           ((float)stk_250 / arg9) * f13) * 65536.0) / (float)stk_258);
      stk_238 = (uint16_t *)
                  (i30 + *(int *)(*(int *)(sprite2 + 0x2c) + (stk_250 + i26) * 4) +
                  (i25 - i38) * 2);
      i36 = (i39 - i38) + 1;
      i11 = i39 - i38;
      i34 = i4 * i36 + i37;
      for (i36 = stk_264 + i3 * i36;
          (SBORROW4(i39,i38) == i11 < 0 &&
          ((((i8 <= i34 >> 0x10 || (i7 <= i36 >> 0x10)) || (i34 >> 0x10 < 0)) ||
           (i36 >> 0x10 < 0)))); i36 = i36 - i3) {
        i39 = i39 + -1;
        i34 = i34 - i4;
        i11 = i39 - i38;
      }
      for (; (i38 <= i39 &&
             (((i8 <= i37 >> 0x10 || (i7 <= stk_264 >> 0x10)) ||
              ((i37 >> 0x10 < 0 || (stk_264 >> 0x10 < 0)))))); stk_264 = stk_264 + i3) {
        stk_238 = stk_238 + -1;
        i38 = i38 + 1;
        i37 = i37 + i4;
      }
      i38 = (i39 - i38) + 1;
      if (0 < i38) {
        do {
          b5 = *(uint8_t *)((stk_264 >> 0x10) + i28 + *(int *)(i6 + (i37 >> 0x10) * 4));
          if (b5 != 0) {
            u32 = (uint32_t)stk_2a4[b5];
            u33 = (uint32_t)*stk_238;
            u27 = ((u33 & 0xf800) * arg11 >> 8 & 0xf800) + (u32 & 0xf800);
            if (0xf800 < u27) {
              u27 = 0xf800;
            }
            u2 = ((u33 & 0x7e0) * arg11 >> 8 & 0x7e0) + (u32 & 0x7e0);
            u22 = (uint16_t)u2;
            if (0x7e0 < u2) {
              u22 = 0x7e0;
            }
            u32 = ((u33 & 0x1f) * arg11 >> 8 & 0x1f) + (u32 & 0x1f);
            u21 = (uint16_t)u32;
            if (0x1f < u32) {
              u21 = 0x1f;
            }
            *stk_238 = u22 | (uint16_t)u27 | u21;
          }
          stk_264 = stk_264 + i3;
          stk_238 = stk_238 + -1;
          i37 = i37 + i4;
          i38 = i38 + -1;
        } while (i38 != 0);
      }
      i38 = stk_27c;
      if (stk_250 < i35) {
        i38 = -stk_278;
      }
      stk_268 = stk_268 + i38;
      i38 = stk_27c;
      if (i29 <= stk_250) {
        i38 = -stk_278;
      }
      stk_26c = stk_26c + i38;
      stk_250 = stk_250 + 1;
    } while (stk_250 <= stk_298);
  }
  u27 = SpriteDecompUnlockData();
  return u27;
}
#undef stk_2a4
#undef stk_298
#undef stk_294
#undef stk_290
#undef stk_28c
#undef stk_288
#undef stk_27c
#undef stk_278
#undef stk_26c
#undef stk_268
#undef stk_264
#undef stk_258
#undef stk_254
#undef stk_250
#undef stk_238
#undef stk_220
#undef stk_21c

