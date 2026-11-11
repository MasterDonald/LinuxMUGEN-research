/*
 * explod.c -- explods
 * Explods (stand-alone effects created by characters) and system explods
 * (fight screen and motif elements): creation, update, binding and drawing.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/explod.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"

extern int id_0 __asm__("D_08287a6c"); /* file-static 0x08287a6c */

/* ExplodArrayNew @ 0x0808dc30, 127 bytes
 *
 * Creates an explod array with room for `capacity` explods, each with its
 * own animation instance.
 *
 * Parameters:
 *   arg1         size_t
 *   arg2         uint32_t
 *
 * Calls: ecalloc, AnimNew
 * Called by: GameLoadFightData
 *
 * Elecbyte file: src/mugen/explod.c
 */
int * ExplodArrayNew(size_t arg1,uint32_t arg2)

{
  int *mem;
  int mem2;
  uint32_t *anim;
  int i4;
  
  mem = (int *)ecalloc(1,0xc);
  if (mem != (int *)0x0) {
    mem[1] = arg1;
    mem2 = ecalloc(arg1,0xe4);
    *mem = mem2;
    if (mem2 != 0) {
      mem2 = 0;
      if ((int)arg1 < 1) {
        return mem;
      }
      i4 = 0;
      while( true ) {
        anim = AnimNew(0,0);
        *(uint32_t **)(*mem + 0x80 + i4) = anim;
        if (anim == (uint32_t *)0x0) break;
        mem2 = mem2 + 1;
        i4 = i4 + 0xe4;
        anim[0xc] = arg2;
        if ((int)arg1 <= mem2) {
          return mem;
        }
      }
    }
  }
  return (int *)0x0;
}

/* ExplodArrayFree @ 0x0808dcb0, 101 bytes
 *
 * Frees an explod array and the animation instances.
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: AnimFree
 * C library: free
 * Called by: GameFreeFightData
 *
 * Elecbyte file: src/mugen/explod.c
 */
void ExplodArrayFree(int *arg1)

{
  int i1;
  int i2;
  
  if (arg1 == (int *)0x0) {
    return;
  }
  i1 = *arg1;
  if (i1 != 0) {
    i2 = 0;
    if (0 < arg1[1]) {
      while( true ) {
        AnimFree(*(void **)(i1 + 0x80 + i2 * 0xe4));
        if (arg1[1] <= i2 + 1) break;
        i1 = *arg1;
        i2 = i2 + 1;
      }
    }
    free((void *)*arg1);
  }
  free(arg1);
  return;
}

/* ExplodArrayUpdate @ 0x0808dd20, 38 bytes
 *
 * Advances every live explod by one tick (ExplodUpdate).
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: ExplodUpdate
 * Called by: CharacterSelectScreen, GameLoop, GameUpdate
 *
 * Elecbyte file: src/mugen/explod.c
 */
void ExplodArrayUpdate(int *arg1)

{
  int i1;
  int i2;
  
  i1 = 0;
  if (0 < arg1[1]) {
    do {
      i2 = i1 + 1;
      ExplodUpdate(arg1,i1);
      i1 = i2;
    } while (i2 < arg1[1]);
  }
  return;
}

/* ExplodUpdate @ 0x0808dd50, 374 bytes
 *
 * Advances one explod. It follows its bound player while the bind time lasts
 * (unless that player is in a hit pause and the explod does not ignore it),
 * moves it by velocity and acceleration, and advances its animation. It
 * removes the explod when its remove time runs out (-1 = when the animation
 * ends).
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *
 * Player fields read: hitpausetime
 * Calls: PlayerAccessID, AnimUpdate
 * Called by: ExplodArrayUpdate, SysExplodCreateDrawPal
 *
 * Elecbyte file: src/mugen/explod.c
 * Note: 4 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
int * ExplodUpdate(int *arg1,int arg2)

{
  int *pi1;
  int *pi2;
  int *pi3;
  int player;
  
  pi3 = (int *)*arg1;
  pi1 = pi3 + arg2 * 0x39;
  if ((*pi1 != 0) &&
     (((g[0x74f3] == -1 || (pi1[0xf] <= pi1[g[0x74f3] + 0xd])) ||
      (pi3 = (int *)(pi1[g[0x74f3] + 0xd] + 1), pi3 == (int *)0x0)))) {
    if ((((pi1[3] != 0) && (pi1[0x1f] == 0)) &&
        (player = PlayerAccessID(pi1[3]), player != 0)) && (0 < *(int *)(player + PLB_HITPAUSETIME))) {
      return (int *)*(int *)(player + PLB_HITPAUSETIME);
    }
    pi3 = (int *)pi1[0xf];
    if (((int)pi3 < pi1[0x10]) || (pi1[0x10] == -1)) {
      if (pi1[1] == 1) {
        AnimUpdate((uint32_t *)pi1[0x20]);
        pi3 = (int *)pi1[0xf];
      }
      if (0 < (int)pi3) {
        pi1[5] = BITS_F2I(int, (BITS_I2F(pi1[5]) + BITS_I2F(pi1[7])));
        pi1[7] = BITS_F2I(int, (BITS_I2F(pi1[7]) + BITS_I2F(pi1[9])));
        pi1[6] = BITS_F2I(int, (BITS_I2F(pi1[6]) + BITS_I2F(pi1[8])));
        pi1[8] = BITS_F2I(int, (BITS_I2F(pi1[8]) + BITS_I2F(pi1[10])));
      }
      pi3 = (int *)0x0;
      if (pi1[0x18] != 0) {
        if ((float *)pi1[0x13] != (float *)0x0) {
          pi1[5] = BITS_F2I(int, ((float80)pi1[0xb] + *(float *)pi1[0x13]));
        }
        if ((float *)pi1[0x14] != (float *)0x0) {
          pi1[6] = BITS_F2I(int, ((float80)pi1[0xc] + *(float *)pi1[0x14]));
        }
        if ((int *)pi1[0x15] != (int *)0x0) {
          pi1[5] = BITS_F2I(int, (float)(pi1[0xb] + *(int *)pi1[0x15]));
        }
        if ((int *)pi1[0x16] != (int *)0x0) {
          pi1[6] = BITS_F2I(int, (float)(pi1[0xc] + *(int *)pi1[0x16]));
        }
        pi3 = (int *)pi1[0x18];
        if (0 < (int)pi3) {
          pi3 = (int *)((int)pi3 + -1);
          pi1[0x18] = (int)pi3;
          pi2 = g;
          if ((pi3 == (int *)0x0) &&
             (pi3 = (int *)pi1[0x1b], (int *)pi1[0x1b] == (int *)0x0)) {
            pi1[0x1b] = 1;
            pi1[5] = BITS_F2I(int, ((float80)pi2[0x7311] + BITS_I2F(pi1[5])));
            pi1[6] = BITS_F2I(int, ((float80)pi2[0x7312] + BITS_I2F(pi1[6])));
            pi3 = pi2;
          }
        }
      }
      pi1[0xf] = pi1[0xf] + 1;
    }
    else {
      *pi1 = 0;
      arg1[2] = arg1[2] + -1;
    }
  }
  return pi3;
}

/* ExplodArrayDraw @ 0x0808ded0, 103 bytes
 *
 * Draws the live explods of layer `layer` (-1 = every layer) that are not
 * hidden.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *
 * Calls: ExplodDraw
 * Called by: GameLoop, GameRoundDraw
 *
 * Elecbyte file: src/mugen/explod.c
 */
void ExplodArrayDraw(int *arg1,int arg2)

{
  int *pi1;
  int i2;
  int i3;
  int i4;
  int i5;
  
  i3 = 0;
  i4 = 0;
  i2 = arg1[1];
  if ((0 < i2) && (pi1 = (int *)*arg1, (uint32_t)arg1[2] < 0x80000000)) {
    i5 = 0;
    do {
      if (*pi1 != 0) {
        i4 = i4 + 1;
        if (((pi1[0x19] == arg2) || (arg2 == -1)) && (pi1[2] == 0)) {
          ExplodDraw((int)pi1);
          i2 = arg1[1];
        }
      }
      i3 = i3 + 1;
      i5 = i5 + 0xe4;
    } while ((i3 < i2) && (pi1 = (int *)(i5 + *arg1), i4 <= arg1[2]));
  }
  return;
}

/* ExplodDraw @ 0x0808df40, 716 bytes
 *
 * Draws one explod: its animation with scale, facing and blend, positioned
 * in screen or stage space. Text explods (system explods with text) are
 * drawn with their font.
 *
 * Parameters:
 *   arg1         int
 *
 * Globals read: video_linux_doubleres
 * Calls: GameModeInFightScreen, W_Define, W_ScaleSprite_S,
 *        AnimDrawScaleFlip, V_FontDrawAlignBank
 * Called by: ExplodArrayDraw, SysExplodCreateDrawPal
 *
 * Elecbyte file: src/mugen/explod.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: 2 temporaries are float80, as the original kept them in x87 registers.
 */
void ExplodDraw(int arg1)

{
  float80 f1;
  float80 f2;
  int i3;
  uint32_t u4;
  uint32_t u5;
  uint32_t u6;
  int i7;
  int i8;
  int i9;
  int i10;
  bool b11;
  uint32_t stale_var;
  float stk_3c;
  float stk_38;
  
  i10 = W_y1;
  i9 = W_x2;
  i8 = W_x1;
  i7 = W_y2;
  stk_38 = *(float *)(arg1 + 0x44);
  stk_3c = *(float *)(arg1 + 0x48);
  if (*(int *)(arg1 + 0x6c) == 0) {
    f1 = *(float *)(arg1 + 0x14);
    f2 = *(float *)(arg1 + 0x18);
  }
  else {
    f1 = *(float *)(arg1 + 0x14) - (float)g[0x7311];
    f2 = *(float *)(arg1 + 0x18) - (float)g[0x7312];
  }
  if (*(int *)(arg1 + 0x70) != 0) {
    f1 = f1 - (float)g[0x7315];
    f2 = f2 - (float)g[0x7316];
  }
  if (((g[G_VIDEO_LINUX_DOUBLERES] == 4) && (b11 = GameModeInFightScreen(), ZEXT8(b11) != 0))
     && ((*(int *)(arg1 + 4) != 1 || (*(int *)(*(int *)(arg1 + 0x80) + 0x30) == 0)))) {
    f1 = f1 + f1;
    stk_38 = stk_38 + stk_38;
    f2 = f2 + f2;
    stk_3c = stk_3c + stk_3c;
  }
  if (*(uint32_t *)(arg1 + 0xe0) != 0xffffffff) {
    W_Define(*(uint32_t *)(arg1 + 0xd4),*(uint32_t *)(arg1 + 0xdc),*(uint32_t *)(arg1 + 0xd8),
             *(uint32_t *)(arg1 + 0xe0));
  }
  i3 = *(int *)(arg1 + 0x80);
  u4 = *(uint32_t *)(i3 + 0x20);
  *(uint32_t *)(i3 + 0x20) = *(uint32_t *)(arg1 + 0x84);
  u5 = *(uint32_t *)(i3 + 0x24);
  *(uint32_t *)(i3 + 0x24) = *(uint32_t *)(arg1 + 0x88);
  u6 = *(uint32_t *)(i3 + 0x28);
  *(uint32_t *)(i3 + 0x28) = *(uint32_t *)(arg1 + 0x8c);
  i3 = *(int *)(arg1 + 4);
  if (i3 == 2) {
    if ((*(uint32_t *)(arg1 + 0x68) & 1) != 0) {
      stk_38 = stk_38 * -1.0;
    }
    if ((*(uint32_t *)(arg1 + 0x68) & 2) != 0) {
      stk_3c = stk_3c * -1.0;
    }
    W_ScaleSprite_S(*(int **)(arg1 + 0x90),*(int *)(arg1 + 0x94),f1,f2,stk_38,stk_3c
                   );
  }
  else if (i3 < 3) {
    if (i3 == 1) {
      AnimDrawScaleFlip(*(uint32_t **)(arg1 + 0x80),(int)X87_FIST32(f1),(int)X87_FIST32(f2),
                        stk_38,stk_3c,*(uint32_t *)(arg1 + 0x68));
    }
  }
  else if (i3 == 3) {
    V_FontDrawAlignBank((char *)(arg1 + 0xa4),*(int **)(arg1 + 0x98),(int)X87_FIST32(f1),
                        (int)X87_FIST32(f2),*(int *)(arg1 + 0xa0),*(int *)(arg1 + 0x9c));
  }
  i3 = *(int *)(arg1 + 0x80);
  *(uint32_t *)(i3 + 0x20) = u4;
  *(uint32_t *)(i3 + 0x24) = u5;
  *(uint32_t *)(i3 + 0x28) = u6;
  if (*(int *)(arg1 + 0xe0) != -1) {
    W_Define(i8,i10,i9,i7);
  }
  return;
}

/* ExplodArrayDrawShadow @ 0x0808e210, 145 bytes
 *
 * Draws the shadows and reflections of every explod that has a shadow.
 *
 * Parameters:
 *   arg1         int *
 *
 * Globals read: shadow_intensity, reflection_intensity
 * Calls: ExplodDrawShadow
 * Called by: GameLoop
 *
 * Elecbyte file: src/mugen/explod.c
 */
void ExplodArrayDrawShadow(int *arg1)

{
  uint32_t u1;
  int i2;
  int *pi3;
  int i4;
  int i5;
  int stk_14;
  
  i5 = 0;
  stk_14 = 0;
  i2 = arg1[1];
  if ((0 < i2) && (pi3 = (int *)*arg1, (uint32_t)arg1[2] < 0x80000000)) {
    i4 = 0;
    do {
      if (*pi3 != 0) {
        u1 = pi3[0x1d];
        i5 = i5 + 1;
        if (u1 != 0) {
          if (u1 == 0xffffffff) {
            u1 = g[0x10a5];
          }
          ExplodDrawShadow((int)pi3,g + G_SHADOW_INTENSITY,u1,g + G_REFLECTION_INTENSITY);
          i2 = arg1[1];
        }
      }
      i4 = i4 + 0xe4;
      stk_14 = stk_14 + 1;
    } while ((stk_14 < i2) && (pi3 = (int *)(i4 + *arg1), i5 <= arg1[2]));
  }
  return;
}

/* ExplodDrawShadow @ 0x0808e2b0, 1422 bytes
 *
 * Draws one explod's shadow and/or reflection (like the player shadows).
 *
 * Parameters:
 *   arg1         int
 *   arg2         int *
 *   arg3         uint32_t
 *   arg4         int *
 *
 * Globals read: config_drawshadows, video_linux_doubleres,
 *               stageinfo_zoffset
 * Calls: AnimCurSpriteIdx, W_RotateSpriteTransAdd_B,
 *        W_RotateShadowTransSub_P, W_RotateSpriteTransAdd_B_P
 * Called by: ExplodArrayDrawShadow
 *
 * Elecbyte file: src/mugen/explod.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to NAN
 * Note: 14 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: 4 temporaries are float80, as the original kept them in x87 registers.
 */
void ExplodDrawShadow(int arg1,int *arg2,uint32_t arg3,int *arg4)

{
  float80 f1;
  float80 f2;
  int *sprites;
  int i4;
  int i5;
  float80 f6;
  int i7;
  uint8_t b8;
  uint8_t b9;
  uint8_t b10;
  int i11;
  int i12;
  uint32_t u13;
  float80 f14;
  int stk_3c;
  
  sprites = *(int **)(arg1 + 0x90);
  i4 = *(int *)(*(int *)(arg1 + 0x80) + 0x10);
  u13 = *(uint32_t *)(arg1 + 0x68);
  b8 = (uint8_t)_rgb_r_shift_16;
  b9 = (uint8_t)_rgb_g_shift_16;
  b10 = (uint8_t)_rgb_b_shift_16;
  stk_3c = *arg2;
  if ((g[G_CONFIG_DRAWSHADOWS] != 0) && (i7 = AnimCurSpriteIdx(*(int *)(arg1 + 0x80)), i7 != -1)) {
    f1 = *(float *)(arg1 + 0x44);
    f2 = *(float *)(arg1 + 0x48);
    f6 = (float80)*(int *)(i4 + 0x14);
    if (*(int *)(arg1 + 0x6c) == 0) {
      f14 = *(float *)(arg1 + 0x14);
    }
    else {
      f14 = *(float *)(arg1 + 0x14) - (float)g[0x7311];
    }
    f14 = (f14 - (float)g[0x7315]) +
             (float80)(int)((uint32_t)((u13 & 1) == 0) * 2 + -1) *
             (float80)*(int *)(i4 + 0x10) * f1;
    u13 = u13 ^ *(uint32_t *)(i4 + 0x18) & 3;
    if ((u13 & 1) != 0) {
      f1 = f1 * -1.0;
    }
    if ((u13 & 2) == 0) {
      f2 = f2 * -1.0;
    }
    if (g[G_VIDEO_LINUX_DOUBLERES] == 4) {
      f14 = f14 + f14;
      f1 = f1 + f1;
    }
    i4 = (int)X87_FIST32(f14);
    if (0 < *arg4) {
      if (*(int *)(arg1 + 0x6c) == 0) {
        i11 = g[0x7316];
        f14 = (float)g[G_STAGEINFO_ZOFFSET] - ((*(float *)(arg1 + 0x18) - (float)g[G_STAGEINFO_ZOFFSET]) + f6);
      }
      else {
        f14 = ((float)g[G_STAGEINFO_ZOFFSET] - ((*(float *)(arg1 + 0x18) - (float)g[G_STAGEINFO_ZOFFSET]) + f6)) -
                 (float)g[0x7312];
        i11 = g[0x7316];
      }
      f14 = f14 - (float80)i11;
      if (g[G_VIDEO_LINUX_DOUBLERES] == 4) {
        f14 = f14 + f14;
      }
      i11 = *arg4;
      i12 = 0x100 - i11;
      if (*(int *)(arg1 + 0x84) == 3) {
        i11 = i11 * *(int *)(arg1 + 0x88) >> 8;
        i12 = i12 + ((0x100 - i12) * *(int *)(arg1 + 0x8c) >> 8);
      }
      W_RotateSpriteTransAdd_B
                (sprites,i7,(float80)i4,(float80)(int)X87_FIST32(f14),0.0,f1,f2,i11,i12);
    }
    f2 = *(float *)(arg1 + 0x48);
    if (*(int *)(arg1 + 0x6c) == 0) {
      f6 = (((float)g[G_STAGEINFO_ZOFFSET] -
               (((*(float *)(arg1 + 0x18) + (float)g[0x7312]) - (float)g[G_STAGEINFO_ZOFFSET]) + f6) *
               f2 * BITS_I2F(arg2[2])) - (float)g[0x7316]) - (float)g[0x7312];
    }
    else {
      f6 = (((float)g[G_STAGEINFO_ZOFFSET] -
               ((*(float *)(arg1 + 0x18) - (float)g[G_STAGEINFO_ZOFFSET]) + f6) * f2 * BITS_I2F(arg2[2])
               ) - (float)g[0x7312]) - (float)g[0x7316];
    }
    if ((u13 & 2) == 0) {
      f2 = f2 * -1.0;
    }
    if (g[G_VIDEO_LINUX_DOUBLERES] == 4) {
      f6 = f6 + f6;
      f2 = f2 + f2;
    }
    i11 = 0x100;
    if (*(int *)(arg1 + 0x84) == 3) {
      i11 = 0x100 - *(int *)(arg1 + 0x8c);
    }
    i12 = arg2[3];
    i5 = arg2[4];
    if (i12 < i5) {
      if ((float80)i12 < *(float *)(arg1 + 0x18) - (float)g[G_STAGEINFO_ZOFFSET]) {
        f14 = *(float *)(arg1 + 0x18) - (float)g[G_STAGEINFO_ZOFFSET];
        if (f14 < (float80)i5) {
          i11 = (int)X87_FIST32(((float80)i11 * (f14 - (float80)i12)) / (float)(i5 - i12));
        }
      }
      else {
        i11 = 0;
      }
    }
    if (i11 < 0x100) {
      arg3 = ((int)((arg3 & 0x1f) * i11) >> 8 & 0x1fU) +
                ((int)((arg3 & 0xf800) * i11) >> 8 & 0xf800U) +
                ((int)((arg3 & 0x7e0) * i11) >> 8 & 0x7e0U);
      stk_3c = i11 * stk_3c >> 8;
    }
    if ((arg3 == (0x1f << (b8 & 0x1f) | 0x3f << (b9 & 0x1f) | 0x1f << (b10 & 0x1f))) ||
       (stk_3c == 0x100)) {
      stk_3c = 0;
      f14 = BITS_I2F(arg2[2]);
    }
    else {
      if (arg3 != 0) {
        W_RotateShadowTransSub_P
                  (sprites,i7,(float80)i4,(float80)(int)X87_FIST32(f6),0.0,f1,f2,1.0,
                   BITS_I2F(arg2[2]),arg3);
      }
      if (stk_3c < 1) {
        return;
      }
      stk_3c = 0x100 - stk_3c;
      f14 = BITS_I2F(arg2[2]);
    }
    W_RotateSpriteTransAdd_B_P
              (sprites,i7,(float80)i4,(float80)(int)X87_FIST32(f6),0.0,f1,f2,1.0,f14,0,
               stk_3c);
  }
  return;
}

/* ExplodArrayReset @ 0x0808e840, 41 bytes
 *
 * Removes every explod (round reset).
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * Called by: GameRoundReset, GameRoundUpdate
 *
 * Elecbyte file: src/mugen/explod.c
 */
void ExplodArrayReset(uint32_t *arg1)

{
  uint32_t *pu1;
  int i2;
  
  i2 = 0;
  if (0 < (int)arg1[1]) {
    pu1 = (uint32_t *)*arg1;
    do {
      *pu1 = 0;
      pu1 = pu1 + 0x39;
      i2 = i2 + 1;
    } while (i2 < (int)arg1[1]);
  }
  arg1[2] = 0;
  return;
}

/* ExplodDefault @ 0x0808e870, 287 bytes
 *
 * Fills an explod record with its default values: in use, all positions and
 * velocities 0, scale 1.0, no binding (-1), blend override -1, alpha 256.
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * Called by: ExplodAdd, ExplodAddSprite, ExplodAddText
 *
 * Elecbyte file: src/mugen/explod.c
 */
void ExplodDefault(uint32_t *arg1)

{
  uint32_t *pu1;
  int i2;
  uint32_t *pu3;
  
  pu1 = (uint32_t *)arg1[0x20];
  pu3 = arg1;
  for (i2 = 0x39; i2 != 0; i2 = i2 + -1) {
    *pu3 = 0;
    pu3 = pu3 + 1;
  }
  *pu1 = 0;
  arg1[0x25] = 0xffffffff;
  *arg1 = 1;
  arg1[0x20] = pu1;
  arg1[0xe] = 0;
  arg1[0xd] = 0;
  arg1[0xf] = 0;
  arg1[0x10] = 0;
  arg1[0xc] = 0;
  arg1[0xb] = 0;
  arg1[0x1a] = 0;
  arg1[0x18] = 0;
  arg1[10] = 0;
  arg1[9] = 0;
  arg1[8] = 0;
  arg1[7] = 0;
  arg1[6] = 0;
  arg1[5] = 0;
  arg1[0x12] = 0x3f800000;
  arg1[0x11] = 0x3f800000;
  arg1[0x14] = 0;
  arg1[0x13] = 0;
  arg1[0x16] = 0;
  arg1[0x15] = 0;
  pu1[0xc] = 0;
  pu1[0xd] = 0;
  pu1[1] = 0;
  arg1[0x21] = 0xffffffff;
  arg1[0x22] = 0x100;
  arg1[0x23] = 0;
  arg1[0x38] = 0xffffffff;
  arg1[0x36] = 0xffffffff;
  arg1[0x37] = 0xffffffff;
  arg1[0x35] = 0xffffffff;
  return;
}

/* ExplodMakeFromInfo @ 0x0808e990, 215 bytes
 *
 * Creates an explod from an Explod controller's parameter block for a
 * player. Warning: "illegal explod animno". Returns the explod or NULL.
 *
 * Parameters:
 *   player       int *
 *   expr         int
 *   arg3         int *
 *
 * Calls: EvalExpressionI, Warn, ExplodAdd, ExplodSetParams
 * Called by: PlayerSCtrlApplyElem
 * Messages:
 *   "illegal explod animno"
 *
 * Elecbyte file: src/mugen/explod.c
 * Note: 1 data addresses refer to the data image (data/mugen_data.S).
 */
void ExplodMakeFromInfo(int *player,int expr,int *arg3)

{
  int value;
  int value2;
  uint32_t *pu3;
  int *pi4;
  
  value = EvalExpressionI((int)player,expr + 0xc,1);
  if (value < 0) {
    value = 0;
    Warn((int)player,(int)&str_illegal_explod_animno_851f);
  }
  if (*(int *)(expr + 0x18) == 0) {
    value2 = EvalExpressionI((int)player,expr + 0x128,1);
    if (value2 == 0) {
      value2 = player[0x4eb];
    }
    else {
      value2 = player[0x4ed];
    }
    pi4 = *(int **)(*player + 0x11cc);
    pu3 = (uint32_t *)g[0x52be];
  }
  else {
    value2 = g[0x4147];
    pi4 = (int *)g[0x4148];
    pu3 = (uint32_t *)g[0x52be];
  }
  value = ExplodAdd(pu3,value,pi4,value2);
  if (value != -1) {
    ExplodSetParams(player,*(int *)g[0x52be] + value * 0xe4,expr,arg3,0);
  }
  return;
}

/* ExplodModifyFromInfo @ 0x0808ea70, 146 bytes
 *
 * Applies a ModifyExplod controller: re-evaluates the given parameters for
 * every explod of the player with the given id.
 *
 * Parameters:
 *   player       int *
 *   expr         int
 *   arg3         int *
 *
 * Player fields read: id
 * Calls: EvalExpressionI, ExplodSetParams
 * Called by: PlayerSCtrlApplyElem
 *
 * Elecbyte file: src/mugen/explod.c
 */
void ExplodModifyFromInfo(int *player,int expr,int *arg3)

{
  int *pi1;
  int i2;
  int value;
  int *pi4;
  int i5;
  int i3;
  int i7;
  
  pi1 = (int *)g[0x52be];
  value = EvalExpressionI((int)player,expr,1);
  i3 = 0;
  i5 = pi1[1];
  i2 = player[PL_ID];
  if (0 < i5) {
    i7 = 0;
    do {
      pi4 = (int *)(i7 + *pi1);
      if ((*pi4 != 0) && (((pi4[4] == value || (value == -1)) && (pi4[3] == i2)))) {
        ExplodSetParams(player,(int)pi4,expr,arg3,1);
        i5 = pi1[1];
      }
      i3 = i3 + 1;
      i7 = i7 + 0xe4;
    } while (i3 < i5);
  }
  return;
}

/* ExplodSetParams @ 0x0808eb10, 2020 bytes
 *
 * Evaluates an Explod parameter block into an explod record: position from
 * pos and postype, facing, velocities, removal, priorities, blend, scale,
 * binding. Warnings: "negative explod ID", "explod facing param must be 1 or
 * -1", "explod vfacing param must be 1 or -1", ...
 *
 * Parameters:
 *   player       int *
 *   arg2         int
 *   expr         int
 *   arg4         int *
 *   arg5         int
 *
 * Player fields read: id, facing
 * Calls: EvalExpressionI, Warn, EvalExpressionF, AnimGetLooptime
 * C library: random
 * Called by: ExplodMakeFromInfo, ExplodModifyFromInfo
 * Messages:
 *   "negative explod ID"
 *   "explod facing param must be 1 or -1"
 *   "explod vfacing param must be 1 or -1"
 *   "negative explod random param"
 *   "Illegal posbindtime for explod"
 *   "Illegal removetime for explod"
 *
 * Elecbyte file: src/mugen/explod.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: decompiler flag: the second decompiler pass lost the call(s) to NAN
 * Note: 8 data addresses refer to the data image (data/mugen_data.S).
 * Note: 2 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void ExplodSetParams(int *player,int arg2,int expr,int *arg4,int arg5)

{
  int i1;
  int value;
  int *pi3;
  long l4;
  int value2;
  int saved_EDI;
  float80 value3;
  int stk_20;
  uint32_t value4;
  
  pi3 = (int *)*arg4;
  if (arg5 == 0) {
    value = EvalExpressionI((int)player,expr,1);
    *(int *)(arg2 + 0x10) = value;
    if (value < 0) {
      *(uint32_t *)(arg2 + 0x10) = 0;
      Warn((int)player,(int)&str_negative_explod_id_8535);
    }
    *(int *)(arg2 + 0xc) = player[PL_ID];
  }
  if (*(int *)(expr + 0xc4) == -0x7fef) goto L_0808ef0b;
  *(uint32_t *)(arg2 + 0x6c) = 1;
  *(uint32_t *)(arg2 + 0x70) = 1;
  value = *(int *)(expr + 0xc4);
  if (value < 5) {
    if (value < 1) {
      if (value != 0) goto L_0808ed24;
      stk_20 = 0;
      value4 = 0;
      *(int **)(arg2 + 0x4c) = player + 0x4d5;
      saved_EDI = player[PL_FACING];
      *(int **)(arg2 + 0x50) = player + 0x4d6;
      *(uint32_t *)(arg2 + 0x6c) = 0;
      value = *(int *)(expr + 0xc4);
    }
    else if ((((value == 2) && (player[PL_FACING] == 1)) || ((value == 1 && (player[PL_FACING] == -1)))) ||
            (value == 3)) {
      saved_EDI = 1;
      pi3 = g + 0x7312;
      *(int **)(arg2 + 0x54) = g + 0x7311;
      *(int **)(arg2 + 0x58) = pi3;
      stk_20 = 0;
      value4 = 0;
      value = *(int *)(expr + 0xc4);
    }
    else {
      pi3 = g + 0x7311;
      *(int **)(arg2 + 0x58) = g + 0x7312;
      *(int **)(arg2 + 0x54) = pi3;
      value4 = 0x140;
      stk_20 = 0;
      saved_EDI = (uint32_t)(value != 2) * 2 + -1;
    }
  }
  else if (value == 5) {
    if (pi3 == (int *)0x0) {
      value4 = (uint32_t)X87_FIST32(BITS_I2F(player[0x4d5]));
      stk_20 = (int)X87_FIST32(BITS_I2F(player[0x4d6]));
      *(int **)(arg2 + 0x4c) = player + 0x4d5;
      saved_EDI = player[PL_FACING];
      pi3 = player;
    }
    else {
      stk_20 = 0;
      value4 = 0;
      *(int **)(arg2 + 0x4c) = pi3 + 0x4d5;
      saved_EDI = pi3[100];
    }
    *(int **)(arg2 + 0x50) = pi3 + 0x4d6;
    *(uint32_t *)(arg2 + 0x6c) = 0;
    value = *(int *)(expr + 0xc4);
  }
  else {
L_0808ed24:
    stk_20 = 0;
    value4 = 0;
  }
  *(int *)(arg2 + 0x5c) = value;
  value = EvalExpressionI((int)player,expr + 0xec,1);
  if ((value != 1) && (value != -1)) {
    value = 1;
    Warn((int)player,(int)&str_explod_facing_param_must_be_8600);
  }
  if (value * saved_EDI == -1) {
    *(uint32_t *)(arg2 + 0x68) = *(uint32_t *)(arg2 + 0x68) | 1;
  }
  value = EvalExpressionI((int)player,expr + 0xf8,1);
  if ((value != 1) && (value != -1)) {
    value = 1;
    Warn((int)player,(int)&str_explod_vfacing_param_must_be_8640);
  }
  if (value == -1) {
    *(uint32_t *)(arg2 + 0x68) = *(uint32_t *)(arg2 + 0x68) | 2;
  }
  value = EvalExpressionI((int)player,expr + 0x1c,1);
  *(uint32_t *)(arg2 + 0x2c) = value * saved_EDI + value4;
  value = EvalExpressionI((int)player,expr + 0x28,1);
  *(int *)(arg2 + 0x30) = value + stk_20;
  value = EvalExpressionI((int)player,expr + 100,1);
  if (value < 0) {
    value = 0;
    Warn((int)player,(int)&str_negative_explod_random_param_8548);
  }
  l4 = random();
  *(int *)(arg2 + 0x2c) = *(int *)(arg2 + 0x2c) + (l4 % (value + 1) - (value + 1 >> 1));
  value = EvalExpressionI((int)player,expr + 0x70,1);
  if (value < 0) {
    value = 0;
    Warn((int)player,(int)&str_negative_explod_random_param_8548);
  }
  l4 = random();
  *(float *)(arg2 + 0x14) = (float80)*(int *)(arg2 + 0x2c);
  value = (l4 % (value + 1) - (value + 1 >> 1)) + *(int *)(arg2 + 0x30);
  *(int *)(arg2 + 0x30) = value;
  *(float *)(arg2 + 0x18) = (float80)value;
  value3 = EvalExpressionF(player,(int *)(expr + 0x34));
  *(float *)(arg2 + 0x1c) = value3 * (float)saved_EDI;
  value3 = EvalExpressionF(player,(int *)(expr + 0x40));
  *(float *)(arg2 + 0x20) = value3;
  value3 = EvalExpressionF(player,(int *)(expr + 0x4c));
  *(float *)(arg2 + 0x24) = value3 * (float)saved_EDI;
  value3 = EvalExpressionF(player,(int *)(expr + 0x58));
  *(float *)(arg2 + 0x28) = value3;
  if ((arg5 != 0) && (*(int *)(arg2 + 0x60) == 0)) {
    *(uint32_t *)(arg2 + 0x60) = 1;
  }
L_0808ef0b:
  value3 = EvalExpressionF(player,(int *)(expr + 0xac));
  if (value3 != -32760.0) {
    *(float *)(arg2 + 0x44) = value3;
  }
  value3 = EvalExpressionF(player,(int *)(expr + 0xb8));
  if (value3 != -32760.0) {
    *(float *)(arg2 + 0x48) = value3;
  }
  value = EvalExpressionI((int)player,expr + 200,1);
  if (value != -0x7fef) {
    if (value < -1) {
      value = -1;
      Warn((int)player,(int)&str_illegal_posbindtime_for_expl_8680);
    }
    *(int *)(arg2 + 0x60) = value;
  }
  value = EvalExpressionI((int)player,expr + 0xe0,1);
  if (value != -0x7fef) {
    *(uint32_t *)(arg2 + 100) = (uint32_t)(value != 0) * 2;
  }
  value = EvalExpressionI((int)player,expr + 0xa0,1);
  if (value != -0x7fef) {
    if (value < -2) {
      value = -2;
      Warn((int)player,(int)&str_illegal_removetime_for_explo_8565);
    }
    if (value == -2) {
      value = AnimGetLooptime(*(uint32_t **)(arg2 + 0x80));
      *(int *)(arg2 + 0x40) = value - *(int *)(arg2 + 0x3c);
    }
    else {
      *(int *)(arg2 + 0x40) = value;
    }
  }
  value = EvalExpressionI((int)player,expr + 0x88,1);
  if ((((value == 0) || (value == -0x7fef)) &&
      (value2 = EvalExpressionI((int)player,expr + 0x7c,1), value2 != -0x7fef)) && (value2 != 0)) {
    value = -2;
  }
  if (value != -0x7fef) {
    if (value == -2) {
      value = *(int *)(arg2 + 0x40);
    }
    *(int *)(arg2 + 0x38) = value;
  }
  value = EvalExpressionI((int)player,expr + 0x94,1);
  if (value != -0x7fef) {
    if (value == -2) {
      value = *(int *)(arg2 + 0x40);
    }
    *(int *)(arg2 + 0x34) = value;
  }
  if (*(int *)(arg2 + 100) == 0) {
    value = EvalExpressionI((int)player,expr + 0xd4,1);
    if (value != -0x7fef) {
      value2 = *(int *)(arg2 + 0x80);
      i1 = g[0x413d];
      *(int *)(value2 + 0x34) = value;
      *(int *)(value2 + 0x30) = i1;
    }
  }
  else {
    *(uint32_t *)(*(int *)(arg2 + 0x80) + 0x30) = 0;
  }
  value4 = EvalExpressionI((int)player,expr + 0x104,1);
  if (value4 != 0xffff8011) {
    value = EvalExpressionI((int)player,expr + 0x110,1);
    value2 = EvalExpressionI((int)player,expr + 0x11c,1);
    if (((((int)value4 < -1) || (value < -1)) ||
        ((value2 < -1 || ((0xff < (int)value4 || (0xff < value)))))) || (0xff < value2)) {
      value4 = 0xffffffff;
      Warn((int)player,(int)&str_illegal_shadow_color_8583);
    }
    if (value4 != 0xffffffff) {
      value4 = ((int)value4 >> 3) << ((uint8_t)_rgb_r_shift_16 & 0x1f) |
                 (value >> 2) << ((uint8_t)_rgb_g_shift_16 & 0x1f) |
                 (value2 >> 3) << ((uint8_t)_rgb_b_shift_16 & 0x1f);
    }
    *(uint32_t *)(arg2 + 0x74) = value4;
  }
  value = EvalExpressionI((int)player,expr + 0x134,1);
  if (value != -0x7fef) {
    *(int *)(arg2 + 0x78) = value;
  }
  value = EvalExpressionI((int)player,expr + 0x140,1);
  if (value != -0x7fef) {
    *(int *)(arg2 + 0x7c) = value;
  }
  if (*(int *)(expr + 0x14c) != -0x7fef) {
    *(int *)(arg2 + 0x84) = *(int *)(expr + 0x14c);
  }
  value = EvalExpressionI((int)player,expr + 0x150,1);
  if (value != -0x7fef) {
    *(int *)(arg2 + 0x88) = value;
  }
  value = *(int *)(arg2 + 0x88);
  if (value < 0) {
    *(uint32_t *)(arg2 + 0x88) = 0;
    value = 0;
  }
  if (0x100 < value) {
    *(uint32_t *)(arg2 + 0x88) = 0x100;
  }
  value = EvalExpressionI((int)player,expr + 0x15c,1);
  if (value != -0x7fef) {
    *(int *)(arg2 + 0x8c) = value;
  }
  value = *(int *)(arg2 + 0x8c);
  if (value < 0) {
    *(uint32_t *)(arg2 + 0x8c) = 0;
    value = 0;
  }
  if (0x100 < value) {
    *(uint32_t *)(arg2 + 0x8c) = 0x100;
  }
  return;
}

/* ExplodAdd @ 0x0808f300, 182 bytes
 *
 * Adds an animation explod to the array (ExplodDefault, then its animation
 * started on `action`). Returns the explod or NULL.
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         int
 *   arg3         int *
 *   arg4         int
 *
 * Calls: ArrayFind, ExplodDefault, AnimChangeAction, AnimResetAction
 * Called by: ExplodMakeFromInfo, PlayerMakeDust, PlayerSCtrlApplyElem,
 *            PlayerSparkCreate, SysExplodCreate
 *
 * Elecbyte file: src/mugen/explod.c
 */
int ExplodAdd(uint32_t *arg1,int arg2,int *arg3,int arg4)

{
  uint32_t *pu1;
  uint32_t index;
  int *pi3;
  int *pi4;
  int i2;
  
  index = ArrayFind(*arg3,0,arg2);
  if (index != 0xffffffff) {
    i2 = 0;
    if (0 < (int)arg1[1]) {
      pi3 = (int *)*arg1;
      pi4 = pi3;
      do {
        if (*pi3 == 0) {
          ExplodDefault(pi4);
          pu1 = (uint32_t *)pi4[0x20];
          pi4[1] = 1;
          pu1[1] = arg4;
          *pu1 = arg3;
          pi4[0x24] = arg4;
          AnimChangeAction((int *)pi4[0x20],0,arg2);
          AnimResetAction((int *)pi4[0x20]);
          arg1[2] = arg1[2] + 1;
          return i2;
        }
        i2 = i2 + 1;
        pi3 = pi3 + 0x39;
        pi4 = pi4 + 0x39;
      } while (i2 < (int)arg1[1]);
    }
  }
  return -1;
}

/* ExplodAddSprite @ 0x0808f3c0, 145 bytes
 *
 * Adds a single-sprite explod (sprite key group, image of a sprite array).
 * Used by system explods.
 *
 * Parameters:
 *   arg1         uint32_t *
 *   group        int
 *   arg3         int
 *   sprites      int *
 *
 * Calls: SpriteArrayGetNum, ExplodDefault
 * Called by: SysExplodCreate
 *
 * Elecbyte file: src/mugen/explod.c
 */
int ExplodAddSprite(uint32_t *arg1,int group,int arg3,int *sprites)

{
  int index;
  int *pi2;
  int *pi3;
  int i2;
  
  index = SpriteArrayGetNum(sprites,group,arg3);
  if (index != -1) {
    i2 = 0;
    if (0 < (int)arg1[1]) {
      pi2 = (int *)*arg1;
      pi3 = pi2;
      do {
        if (*pi2 == 0) {
          ExplodDefault(pi3);
          pi3[1] = 2;
          pi3[0x25] = index;
          pi3[0x24] = (int)sprites;
          arg1[2] = arg1[2] + 1;
          return i2;
        }
        i2 = i2 + 1;
        pi2 = pi2 + 0x39;
        pi3 = pi3 + 0x39;
      } while (i2 < (int)arg1[1]);
    }
  }
  return -1;
}

/* ExplodAddText @ 0x0808f460, 142 bytes
 *
 * Adds a text explod (a text drawn with a font). Used by system explods.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         char *
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *
 * Calls: ExplodDefault
 * C library: strncpy
 * Called by: SysExplodCreate
 *
 * Elecbyte file: src/mugen/explod.c
 */
int ExplodAddText(int *arg1,char *arg2,int arg3,int arg4,int arg5)

{
  int *pi1;
  int *dest;
  int i2;
  
  i2 = 0;
  if (0 < arg1[1]) {
    pi1 = (int *)*arg1;
    dest = pi1 + 0x29;
    do {
      if (*pi1 == 0) {
        ExplodDefault(pi1);
        pi1[1] = 3;
        pi1[0x26] = arg3;
        pi1[0x27] = arg4;
        pi1[0x28] = arg5;
        strncpy((char *)dest,arg2,0x2f);
        arg1[2] = arg1[2] + 1;
        return i2;
      }
      i2 = i2 + 1;
      dest = dest + 0x39;
      pi1 = pi1 + 0x39;
    } while (i2 < arg1[1]);
  }
  return -1;
}

/* ExplodRemove @ 0x0808f4f0, 45 bytes
 *
 * Removes explod `index`.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *
 * Called by: SysExplodCreateDrawPal
 *
 * Elecbyte file: src/mugen/explod.c
 */
void ExplodRemove(int *arg1,int arg2)

{
  int *pi1;
  
  pi1 = (int *)(*arg1 + arg2 * 0xe4);
  if (*pi1 != 0) {
    *pi1 = 0;
    arg1[2] = arg1[2] + -1;
  }
  return;
}

/* ExplodRemoveID @ 0x0808f520, 82 bytes
 *
 * Removes the explods of player `owner` with id `id` (-1 = all of them).
 * RemoveExplod controller.
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         int
 *   arg3         int
 *
 * Called by: GameFreePlayerDependencies, PlayerSCtrlApplyElem
 *
 * Elecbyte file: src/mugen/explod.c
 */
void ExplodRemoveID(uint32_t *arg1,int arg2,int arg3)

{
  int *pi1;
  int i2;
  int i3;
  
  i3 = 0;
  i2 = arg1[1];
  if (0 < i2) {
    pi1 = (int *)*arg1;
    do {
      if ((*pi1 != 0) && (((pi1[4] == arg3 || (arg3 == -1)) && (pi1[3] == arg2))))
      {
        *pi1 = 0;
        arg1[2] = arg1[2] + -1;
        i2 = arg1[1];
      }
      i3 = i3 + 1;
      pi1 = pi1 + 0x39;
    } while (i3 < i2);
  }
  return;
}

/* ExplodRemoveGetHit @ 0x0808f580, 66 bytes
 *
 * Removes the explods of a player marked "removeongethit" (when the player
 * gets hit).
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         int
 *
 * Called by: Player1ReverseP2, PlayerGetHit, PlayerUpdate
 *
 * Elecbyte file: src/mugen/explod.c
 */
void ExplodRemoveGetHit(uint32_t *arg1,int arg2)

{
  int *pi1;
  int i2;
  int i3;
  
  i3 = 0;
  i2 = arg1[1];
  if (0 < i2) {
    pi1 = (int *)*arg1;
    do {
      if (((*pi1 != 0) && (pi1[3] == arg2)) && (pi1[0x1e] != 0)) {
        *pi1 = 0;
        arg1[2] = arg1[2] + -1;
        i2 = arg1[1];
      }
      i3 = i3 + 1;
      pi1 = pi1 + 0x39;
    } while (i3 < i2);
  }
  return;
}

/* ExplodAccessID @ 0x0808f5d0, 71 bytes
 *
 * Returns the explod of owner `owner` with id `id`, or NULL.
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         int
 *   arg3         int
 *
 * Called by: SysExplodCreate
 *
 * Elecbyte file: src/mugen/explod.c
 */
int ExplodAccessID(uint32_t *arg1,int arg2,int arg3)

{
  int i2;
  int *pi2;
  
  i2 = 0;
  if (0 < (int)arg1[1]) {
    pi2 = (int *)*arg1;
    do {
      if ((*pi2 != 0) && (((pi2[4] == arg3 || (arg3 == -1)) && (pi2[3] == arg2))))
      {
        return i2;
      }
      i2 = i2 + 1;
      pi2 = pi2 + 0x39;
    } while (i2 < (int)arg1[1]);
  }
  return -1;
}

/* ExplodGetUniqID @ 0x0808f620, 15 bytes
 *
 * Returns a new unique explod id for system explods.
 *
 * Called by: SysExplodParse
 *
 * Elecbyte file: src/mugen/explod.c
 */
int ExplodGetUniqID(void)

{
  int i1;
  
  i1 = id_0;
  id_0 = id_0 + 1;
  return i1;
}

/* ExplodBindChange @ 0x0808f630, 73 bytes
 *
 * Changes the bind time of the explods of a player with a given id
 * (ExplodBindTime controller).
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Called by: PlayerSCtrlApplyElem
 *
 * Elecbyte file: src/mugen/explod.c
 */
void ExplodBindChange(uint32_t *arg1,int arg2,int arg3,int arg4)

{
  int *pi1;
  int i2;
  int i3;
  
  i2 = 0;
  i3 = arg1[1];
  if (0 < i3) {
    pi1 = (int *)*arg1;
    do {
      if ((*pi1 != 0) && (((pi1[4] == arg3 || (arg3 == -1)) && (pi1[3] == arg2))))
      {
        pi1[0x18] = arg4;
        i3 = arg1[1];
      }
      i2 = i2 + 1;
      pi1 = pi1 + 0x39;
    } while (i2 < i3);
  }
  return;
}

/* ExplodCount @ 0x0808f680, 72 bytes
 *
 * Counts the explods of a player with id `id` (-1 = all). NumExplod trigger.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *
 * Called by: SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/explod.c
 */
int ExplodCount(int *arg1,int arg2,int arg3)

{
  int i1;
  int i2;
  int i3;
  int i4;
  
  i4 = 0;
  i2 = arg1[1];
  if (0 < i2) {
    i1 = *arg1;
    i3 = 0;
    do {
      if ((*(int *)(i1 + i3) != 0) &&
         (((*(int *)(i1 + 0x10 + i3) == arg3 || (arg3 == -1)) &&
          (*(int *)(i1 + 0xc + i3) == arg2)))) {
        i4 = i4 + 1;
      }
      i3 = i3 + 0xe4;
      i2 = i2 + -1;
    } while (i2 != 0);
  }
  return i4;
}

/* SysExplodParse @ 0x0808f6d0, 549 bytes
 *
 * Reads a "system explod" from a motif or fight.def group under key prefix
 * `prefix`. The element is a sprite ("<prefix>.spr = group, image"), an
 * animation ("<prefix>.anim") or a text ("<prefix>.font" and
 * "<prefix>.text"), with "<prefix>.offset", ".facing", ".vfacing", ".scale",
 * ".layerno" and ".displaytime". Every fight screen and motif element is
 * built this way.
 *
 * Parameters:
 *   tp           int
 *   sysexplod    int *
 *   prefix       uint32_t
 *
 * Calls: TPScanf, TPGetValueInt, TPGetValue, ExplodGetUniqID
 * C library: sprintf, strncpy
 * Called by: CharselReadConfig, GameLoadFightData, GameLoadSystem
 *
 * Elecbyte file: src/mugen/explod.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x60 bytes, 1
 *       variables), because their address is taken.
 */
uint32_t SysExplodParse(int tp,int *sysexplod,uint32_t prefix)

{
  bool b1;
  int i2;
  uint32_t stale_var;
  char *value;
  uint32_t stale_EDX;
  uint32_t stale_EDX_00;
  uint32_t u3;
  uint32_t stale_EDX_01;
  uint32_t stale_EDX_02;
  unsigned char frame[0x60] __attribute__((aligned(16)));
#define keyname (*(char (*)[76])(frame + 0x4))
  
  *sysexplod = 0;
  sprintf(keyname,"%s.spr",prefix);
  i2 = TPScanf(tp,keyname,"%i,%i",sysexplod + 1,sysexplod + 2);
  if (i2 == 2) {
    *sysexplod = 2;
  }
  i2 = *sysexplod;
  u3 = stale_EDX;
  if (i2 == 0) {
    sprintf(keyname,"%s.anim",prefix,0);
    b1 = TPGetValueInt(tp,keyname,(uint32_t *)(sysexplod + 1));
    u3 = stale_EDX_00;
    if (ZEXT8(b1) == 0) {
      i2 = *sysexplod;
    }
    else {
      *sysexplod = 1;
      i2 = 1;
    }
  }
  if (i2 == 0) {
    sprintf(keyname,"%s.font",prefix,u3);
    i2 = TPScanf(tp,keyname,"%i,%i,%i",sysexplod + 1,sysexplod + 2,sysexplod + 3);
    if (1 < i2) {
      *sysexplod = 3;
      sprintf(keyname,"%s.text",prefix,stale_EDX_01);
      value = TPGetValue(tp,keyname);
      if (value == (char *)0x0) {
        *(uint8_t *)(sysexplod + 0xf) = 0;
      }
      else {
        strncpy((char *)(sysexplod + 0xf),value,0x2f);
      }
    }
  }
  sysexplod[9] = 0;
  i2 = ExplodGetUniqID();
  sysexplod[10] = i2;
  if (*sysexplod != 0) {
    sysexplod[5] = -2;
    sprintf(keyname,"%s.displaytime",prefix,keyname);
    TPGetValueInt(tp,keyname,(uint32_t *)(sysexplod + 5));
    if ((*sysexplod != 1) && (sysexplod[5] == -2)) {
      sysexplod[5] = 1;
    }
    sprintf(keyname,"%s.offset",prefix,stale_EDX_02);
    TPScanf(tp,keyname,"%i,%i",sysexplod + 6,sysexplod + 7);
    sprintf(keyname,"%s.facing",prefix);
    TPGetValueInt(tp,keyname,(uint32_t *)(sysexplod + 0xb));
    sprintf(keyname,"%s.vfacing",prefix);
    TPGetValueInt(tp,keyname,(uint32_t *)(sysexplod + 0xc));
    sprintf(keyname,"%s.layerno",prefix);
    TPGetValueInt(tp,keyname,(uint32_t *)(sysexplod + 8));
    sysexplod[0xe] = 0x3f800000;
    sysexplod[0xd] = 0x3f800000;
    sprintf(keyname,"%s.scale",prefix);
    TPScanf(tp,keyname,"%f,%f",sysexplod + 0xd,sysexplod + 0xe);
  }
  return 1;
}
#undef keyname

/* SysExplodParseGetSprGrpImgNo @ 0x0808f900, 40 bytes
 *
 * Returns the sprite key (group, image) of a sprite system explod.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int *
 *   arg3         int *
 *
 * Called by: GameStgInitFightData
 *
 * Elecbyte file: src/mugen/explod.c
 */
uint32_t SysExplodParseGetSprGrpImgNo(int *arg1,int *arg2,int *arg3)

{
  if (*arg1 != 2) {
    return 0;
  }
  *arg2 = arg1[1];
  *arg3 = arg1[2];
  return 1;
}

/* SysExplodCreateDraw @ 0x0808f930, 13 bytes
 *
 * SysExplodCreateDrawPal with the default palette.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int *
 *   sprites      int *
 *   arg4         int *
 *   arg5         int
 *   arg6         int
 *   arg7         int
 *   arg8         int
 *
 * Calls: SysExplodCreateDrawPal
 * Called by: GameBarsDraw, SysExplodCreateDraw_Fight,
 *            SysExplodCreateDraw_Sys
 *
 * Elecbyte file: src/mugen/explod.c
 */
void SysExplodCreateDraw(int *arg1,int *arg2,int *sprites,int *arg4,int arg5,int arg6
                        ,int arg7,int arg8)

{
  SysExplodCreateDrawPal(arg1,arg2,sprites,arg4,arg5,arg6,arg7,arg8);
  return;
}

/* SysExplodCreateDrawPal @ 0x0808f940, 217 bytes
 *
 * Creates a temporary explod from a system explod definition at (x, y),
 * draws it immediately and removes it. Used for fight screen elements drawn
 * every frame (bars, faces, names).
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int *
 *   sprites      int *
 *   arg4         int *
 *   arg5         int
 *   arg6         int
 *   arg7         int
 *   arg8         int
 *
 * Calls: SysExplodCreate, ExplodUpdate, ExplodDraw, ExplodRemove
 * Called by: SysExplodCreateDraw
 *
 * Elecbyte file: src/mugen/explod.c
 * Note: 1 call results that the caller reads as stale_EAX assigned explicitly
 */
int SysExplodCreateDrawPal
              (int *arg1,int *arg2,int *sprites,int *arg4,int arg5,int arg6,
              int arg7,int arg8)

{
  int i1;
  int stale_EAX;
  int i2;
  
  if ((arg2[8] == arg8) || (arg8 == -1)) {
    stale_EAX = SysExplodCreate(arg1,arg2,sprites,arg4,arg5,arg6,arg7);
    i1 = stale_EAX;
    if (stale_EAX != -1) {
      i2 = *arg1;
      if ((*(int *)(i2 + 0x3c + stale_EAX * 0xe4) == 0) &&
         (*(int *)(i2 + 4 + stale_EAX * 0xe4) == 1)) {
        ExplodUpdate(arg1,stale_EAX);
        i2 = *arg1;
      }
      if (g[0x7306] == 0) {
        ExplodDraw(i2 + stale_EAX * 0xe4);
        i2 = *arg1;
      }
      *(uint32_t *)(i2 + 8 + stale_EAX * 0xe4) = 1;
      if (*(int *)(i2 + 0x40 + stale_EAX * 0xe4) == 1) {
        ExplodRemove(arg1,stale_EAX);
      }
    }
  }
  else {
    i1 = -1;
  }
  return i1;
}

/* SysExplodCreate @ 0x0808fa20, 615 bytes
 *
 * Creates a persistent explod from a system explod definition (animation,
 * sprite or text) at (x, y), reusing the existing explod with the same id.
 * Returns the explod.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int *
 *   sprites      int *
 *   arg4         int *
 *   arg5         int
 *   arg6         int
 *   arg7         int
 *
 * Calls: ExplodAccessID, ExplodAdd, AnimChangeAction, AnimResetAction,
 *        ExplodAddSprite, ExplodAddText, AnimGetLooptime
 * Called by: SysExplodCreateDrawPal, SysExplodCreate_Fight,
 *            SysExplodCreate_Sys
 *
 * Elecbyte file: src/mugen/explod.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: Written by hand from the assembly (reconstruction/overrides/).
 * Note: Ghidra output of 0x0808fa20-0x0808fc87 with the return value restored.
 *       Reason: the function returns the explod index kept in %ebx (VERIFIED:
 *       "mov %eax,%ebx" after ExplodAccessID / ExplodAdd / ExplodAddSprite /
 *       ExplodAddText, epilogue "mov %ebx,%eax; ret"), but Ghidra reused the
 *       index variable as a temporary after L_0808fbad and printed "return
 *       unaff_EBX" everywhere, so callers lost it (SysExplodCreateDrawPal,
 *       SysExplodCreate_Fight use it as an index). On the three early exits the
 *       original returns the caller's %ebx unchanged; that value cannot be
 *       reproduced in C, -1 ("no explod") is returned instead (documented in
 *       COMPLETENESS-REPORT.md). pu5[5], pu5[6] are float fields stored with
 *       fstps (bit copies).
 */
int SysExplodCreate(int *arg1,int *arg2,int *sprites,int *arg4,int arg5,int arg6,
                   int arg7)
{
  uint32_t u1;
  bool b2;
  int looptime;
  int i4;
  int idx;
  uint32_t *pu5;

  pu5 = (uint32_t *)0x0;
  b2 = true;
  if (*arg2 == 0) {
    return -1;
  }
  looptime = ExplodAccessID(arg1,arg2[9],arg2[10]);
  if (looptime == -1) {
    i4 = *arg2;
    if (i4 == 1) {
      if (((arg4 != (int *)0x0) && (sprites != (int *)0x0)) &&
         (looptime = ExplodAdd(arg1,arg2[1],arg4,(int)sprites), looptime != -1)) {
        pu5 = (uint32_t *)(*arg1 + looptime * 0xe4);
        i4 = AnimChangeAction((int *)pu5[0x20],0,arg2[1]);
        if (i4 == 0) {
          *pu5 = 0;
          arg1[2] = arg1[2] + -1;
        }
        else {
          AnimResetAction((int *)pu5[0x20]);
        }
      }
    }
    else {
      if (i4 < 2) {
        return -1;
      }
      if (i4 == 2) {
        if (sprites == (int *)0x0) goto L_0808fbad;
        looptime = ExplodAddSprite(arg1,arg2[1],arg2[2],sprites);
      }
      else {
        if (i4 != 3) {
          return -1;
        }
        u1 = arg2[1];
        if (((9 < u1) || ((char)arg2[0xf] == '\0')) || (g[u1 + 0x414b] == 0))
        goto L_0808fbad;
        looptime = ExplodAddText(arg1,(char *)(arg2 + 0xf),*(int *)(arg5 + u1 * 4),
                              arg2[2],arg2[3]);
      }
      if (looptime != -1) {
        pu5 = (uint32_t *)(*arg1 + looptime * 0xe4);
      }
    }
  }
  else {
    b2 = false;
  }
L_0808fbad:
  idx = looptime;                                     /* %ebx from here to the epilogue */
  if (looptime != -1) {
    pu5 = (uint32_t *)(*arg1 + looptime * 0xe4);
  }
  if (pu5 != (uint32_t *)0x0) {
    pu5[3] = arg2[9];
    pu5[0x1f] = 1;
    pu5[4] = arg2[10];
    pu5[0x1b] = 0;
    pu5[0x17] = 3;
    if (arg2[0xb] == -1) {
      pu5[0x1a] = pu5[0x1a] | 1;
    }
    if (arg2[0xc] == -1) {
      pu5[0x1a] = pu5[0x1a] | 2;
    }
    looptime = arg2[6];
    pu5[0xb] = arg6 + looptime;
    i4 = arg2[7];
    pu5[0xc] = arg7 + i4;
    pu5[5] = BITS_F2I(uint32_t, (float)(arg6 + looptime));
    pu5[6] = BITS_F2I(uint32_t, (float)(arg7 + i4));
    pu5[0x11] = arg2[0xd];
    pu5[0x12] = arg2[0xe];
    pu5[0x19] = arg2[8];
    if (b2) {
      looptime = arg2[5];
      if ((looptime == -2) && (pu5[1] == 1)) {
        looptime = AnimGetLooptime((uint32_t *)pu5[0x20]);
      }
      pu5[0x10] = looptime;
      pu5[0xe] = pu5[0x10];
      pu5[0xd] = pu5[0x10];
    }
  }
  return idx;
}

/* SysExplodCreate_Fight @ 0x0808fc90, 60 bytes
 *
 * SysExplodCreate with the fight screen sprites and animations (round
 * announcements, KO).
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *
 * Calls: SysExplodCreate
 * Called by: GameRoundDraw
 *
 * Elecbyte file: src/mugen/explod.c
 * Note: Returns nothing (the original left only stale register values).
 */
void SysExplodCreate_Fight(int *arg1,int arg2,int arg3)

{
  uint32_t stale_EAX;
  
  SysExplodCreate((int *)g[0x52bf],arg1,(int *)g[0x4149],(int *)g[0x414a],(int)(g + 0x414b),
                  arg2,arg3);
  return;
}

/* SysExplodCreate_Sys @ 0x0808fcd0, 70 bytes
 *
 * SysExplodCreate with the motif sprites (reloading them if they were
 * unloaded). Used on the win and survival result screens.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *
 * Calls: GameReloadSystemSprSnd, SysExplodCreate
 * Called by: GameSurvivalResultsUpdate, GameWinScreenUpdate
 *
 * Elecbyte file: src/mugen/explod.c
 */
void SysExplodCreate_Sys(int *arg1,int arg2,int arg3)

{
  GameReloadSystemSprSnd();
  SysExplodCreate((int *)g[0x52bf],arg1,(int *)g[0x5ac0],(int *)g[0x62c2],(int)(g + 0x62c3),
                  arg2,arg3);
  return;
}

/* SysExplodCreateDraw_Fight @ 0x0808fd20, 65 bytes
 *
 * SysExplodCreateDraw with the fight screen sprites.
 *
 * Parameters:
 *   sysexplod    int *
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Calls: SysExplodCreateDraw
 * Called by: GameBarsDraw, GameLifeBarDraw, GamePowerBarDraw
 *
 * Elecbyte file: src/mugen/explod.c
 * Note: Returns nothing (the original left only stale register values).
 */
void SysExplodCreateDraw_Fight(int *sysexplod,int arg2,int arg3,int arg4)

{
  uint32_t stale_EAX;
  
  SysExplodCreateDraw((int *)g[0x52bf],sysexplod,(int *)g[0x4149],(int *)g[0x414a],(int)(g + 0x414b),
                      arg2,arg3,arg4);
  return;
}

/* SysExplodCreateDraw_Sys @ 0x0808fd70, 79 bytes
 *
 * SysExplodCreateDraw with the motif sprites (reloading them if needed).
 * Used by the select screen.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Calls: GameReloadSystemSprSnd, SysExplodCreateDraw
 * Called by: CharacterSelectScreenDraw
 *
 * Elecbyte file: src/mugen/explod.c
 * Note: Returns nothing (the original left only stale register values).
 */
void SysExplodCreateDraw_Sys(int *arg1,int arg2,int arg3,int arg4)

{
  uint32_t stale_EAX;
  
  GameReloadSystemSprSnd();
  SysExplodCreateDraw((int *)g[0x52bf],arg1,(int *)g[0x5ac0],(int *)g[0x62c2],(int)(g + 0x62c3),
                      arg2,arg3,arg4);
  return;
}

