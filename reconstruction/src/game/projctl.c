/*
 * projctl.c -- projectiles
 * Projectile arrays: creation, movement, removal, drawing, shadows and
 * collision box display.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/projctl.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* ProjArrayNew @ 0x080b9170, 100 bytes
 *
 * Creates a player's projectile array with room for `capacity` projectiles.
 *
 * Parameters:
 *   arg1         size_t
 *   arg2         uint32_t
 *   arg3         uint32_t
 *
 * Calls: ArrayNew, ProjArrayFree
 * C library: calloc
 * Called by: PlayerNew
 *
 * Elecbyte file: src/mugen/projctl.c
 */
uint32_t * ProjArrayNew(size_t arg1,uint32_t arg2,uint32_t arg3)

{
  uint32_t *pu1;
  uint32_t *array;
  
  pu1 = calloc(1,0xc);
  if (pu1 == (uint32_t *)0x0) {
    pu1 = (uint32_t *)0x0;
  }
  else {
    array = ArrayNew(arg1,0x2dc,0);
    *pu1 = array;
    if (array == (uint32_t *)0x0) {
      ProjArrayFree(pu1);
      pu1 = (uint32_t *)0x0;
    }
    else {
      pu1[1] = arg2;
      pu1[2] = arg3;
    }
  }
  return pu1;
}

/* ProjArrayFree @ 0x080b91e0, 39 bytes
 *
 * Frees a projectile array.
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * Calls: ArrayFree
 * C library: free
 * Called by: PlayerFree, ProjArrayNew
 *
 * Elecbyte file: src/mugen/projctl.c
 */
void ProjArrayFree(uint32_t *arg1)

{
  if (arg1 != (uint32_t *)0x0) {
    ArrayFree((void *)*arg1);
    free(arg1);
    return;
  }
  return;
}

/* ProjArrayAdd @ 0x080b9210, 147 bytes
 *
 * Adds a projectile: copies the projectile parameters into a free slot,
 * gives it a copy of the owner's animation instance and starts its
 * projectile animation. Returns the slot or -1.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int *
 *   arg3         void *
 *   arg4         int
 *
 * Calls: ArrayFindEmpty, ArrayAdd, AnimCopy, AnimChangeAction,
 *        AnimResetAction
 * Called by: SCtrlInitProjectile
 *
 * Elecbyte file: src/mugen/projctl.c
 */
int ProjArrayAdd(int *arg1,int *arg2,void *arg3,int arg4)

{
  int *anim;
  int array;
  uint32_t *pu3;
  int index;
  int i5;
  
  array = *arg2;
  pu3 = (uint32_t *)arg1[0x4ef];
  index = ArrayFindEmpty(array);
  if (index != -1) {
    i5 = index * *(int *)(array + 4) + *(int *)(array + ARRAY_DATA);
    index = ArrayAdd(array,arg3,0,0);
    if (index != -1) {
      anim = (int *)(i5 + 0x284);
      AnimCopy(anim,pu3);
      *(uint32_t *)(i5 + 0x284) = *(uint32_t *)(*arg1 + 0x11cc);
      AnimChangeAction(anim,0,arg4);
      AnimResetAction(anim);
    }
  }
  return index;
}

/* ProjArrayDelete @ 0x080b92b0, 84 bytes
 *
 * Removes projectile `idx` from the array.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *
 * Calls: ArrayDelete
 * Called by: GameRoundUpdate, PlayerReset, ProjArrayUpdate
 *
 * Elecbyte file: src/mugen/projctl.c
 */
void ProjArrayDelete(int *arg1,int arg2)

{
  int i1;
  int i2;
  
  i2 = arg2 * *(int *)(*arg1 + 4) + *(int *)(*arg1 + 0x14);
  if (i2 != 0) {
    i1 = *(int *)(i2 + 0x2d8);
    if (i1 != 0) {
      *(uint32_t *)(i1 + 0x18) = 0;
      *(uint32_t *)(i1 + 8) = 0;
      *(uint32_t *)(i2 + 0x2d8) = 0;
    }
    ArrayDelete(*arg1,arg2);
    return;
  }
  return;
}

/* ProjArrayUpdate @ 0x080b9310, 864 bytes
 *
 * Advances every projectile by one tick. It moves it (velocity,
 * acceleration, velocity multiplier), advances its animation, and switches
 * it to its hit, remove or cancel animation when it hits, is cancelled or
 * times out. It removes it when the removal animation ends, when it leaves
 * the stage edge or the screen bound, or when its remove time runs out.
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: ArrayScanFirst, AnimChangeAction, AnimGetLooptime,
 *        ProjArrayDelete, AnimUpdate, ArrayScanNext
 * Called by: GameUpdate
 *
 * Elecbyte file: src/mugen/projctl.c
 * Note: 5 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void ProjArrayUpdate(int *arg1)

{
  float80 f1;
  int array;
  bool b3;
  int *pi4;
  int item;
  int looptime;
  
  array = *arg1;
  item = ArrayScanFirst(array);
  do {
    pi4 = g;
    if (item == 0) {
      return;
    }
    b3 = false;
    *(uint32_t *)(item + 0x2c0) = 0;
    if (((pi4[0x74f3] != -1) &&
        (looptime = *(int *)(item + 0x2d0 + pi4[0x74f3] * 4), looptime < *(int *)(item + 0x20))) &&
       (looptime != -1)) {
      b3 = true;
    }
    if (b3) {
      *(uint32_t *)(item + 0x2c0) = 1;
    }
    if ((*(int *)(item + 0x28) == 0) && (!b3)) {
      while (looptime = *(int *)(item + 4), looptime == 1) {
        *(float *)(item + 0x44) = *(float *)(item + 0x44) + *(float *)(item + 100);
        f1 = *(float *)(item + 100) * *(float *)(item + 0x74) + *(float *)(item + 0x7c);
        *(float *)(item + 100) = f1;
        *(float *)(item + 0x48) = *(float *)(item + 0x48) + *(float *)(item + 0x68);
        *(float *)(item + 0x68) =
             *(float *)(item + 0x68) * *(float *)(item + 0x78) + *(float *)(item + 0x80);
        if (f1 <= 0.0) {
          if (*(float *)(item + 100) < 0.0) {
            *(uint32_t *)(item + 0x34) = 0xffffffff;
          }
        }
        else {
          *(uint32_t *)(item + 0x34) = 1;
        }
        f1 = *(float *)(item + 0x44);
        if ((((((float80)*(int *)(item + 0x88) <= f1) || (0.0 <= *(float *)(item + 100))) &&
             (((float80)*(int *)(item + 0x8c) <= *(float *)(item + 0x48) ||
              (0.0 <= *(float *)(item + 0x68))))) &&
            ((f1 <= (float80)*(int *)(item + 0x90) || (*(float *)(item + 100) <= 0.0)))) &&
           ((*(float *)(item + 0x48) <= (float80)*(int *)(item + 0x94) ||
            (*(float *)(item + 0x68) <= 0.0)))) {
          if (((float)(g[0x7311] - *(int *)(item + 0x84)) <= f1) &&
             (f1 <= (float)(*(int *)(item + 0x84) + 0x140 + g[0x7311]))) {
            if (0 < *(int *)(item + 0x2c)) {
              *(int *)(item + 0x2c) = *(int *)(item + 0x2c) + -1;
            }
            if ((*(int *)(item + 0x24) < *(int *)(item + 0x3c)) || (*(int *)(item + 0x3c) == -1))
            goto L_080b95e7;
          }
        }
        *(uint32_t *)(item + 4) = 2;
        *(uint32_t *)(item + 0x24) = 0;
      }
      if ((looptime < 1) || (4 < looptime)) {
        looptime = *(int *)(array + 0x1c);
      }
      else {
        looptime = *(int *)(item + 4);
        *(float *)(item + 0x44) = *(float *)(item + 0x44) + *(float *)(item + 100);
        *(float *)(item + 0x48) = *(float *)(item + 0x48) + *(float *)(item + 0x68);
        if ((((looptime == 2) && (*(int *)(item + 0x14) == -1)) ||
            ((looptime == 3 && (*(int *)(item + 0x18) == -1)))) ||
           ((looptime == 4 && (*(int *)(item + 0x10) == -1)))) {
L_080b95ae:
          looptime = *(int *)(array + 0x1c);
        }
        else {
          if (*(int *)(item + 0x24) == 0) {
            *(uint32_t *)(item + 100) = *(uint32_t *)(item + 0x6c);
            *(uint32_t *)(item + 0x68) = *(uint32_t *)(item + 0x70);
            if (*(int *)(item + 4) == 2) {
              looptime = *(int *)(item + 0x14);
            }
            else if (*(int *)(item + 4) == 4) {
              looptime = *(int *)(item + 0x10);
            }
            else {
              looptime = *(int *)(item + 0x18);
            }
            AnimChangeAction((int *)(item + 0x284),0,looptime);
            looptime = AnimGetLooptime((uint32_t *)(item + 0x284));
            if (looptime < 1) goto L_080b95ae;
          }
          looptime = AnimGetLooptime((uint32_t *)(item + 0x284));
          if (*(int *)(item + 0x2a0) != looptime) goto L_080b95e7;
          looptime = *(int *)(array + 0x1c);
        }
      }
      ProjArrayDelete(arg1,looptime);
    }
L_080b95e7:
    if (!b3) {
      *(int *)(item + 0x2b8) =
           (int)X87_FIST32(*(float *)(item + 0x4c) * 10.0 + (float80)*(int *)(item + 700));
      AnimUpdate((uint32_t *)(item + 0x284));
      if (*(int *)(item + 0x28) < 1) {
        *(int *)(item + 0x20) = *(int *)(item + 0x20) + 1;
        *(int *)(item + 0x24) = *(int *)(item + 0x24) + 1;
      }
      else {
        *(int *)(item + 0x28) = *(int *)(item + 0x28) + -1;
      }
    }
    item = ArrayScanNext(array);
  } while( true );
}

/* ProjArrayCalcDraw @ 0x080b9670, 302 bytes
 *
 * Computes each live projectile's draw scale from its z position (stage
 * "[Scaling]" topz/botz and topscale/botscale) and its screen position.
 *
 * Parameters:
 *   arg1         int *
 *
 * Globals read: scaling_topz, scaling_botz, scaling_botscale,
 *               scaling_topscale
 * Calls: ArrayScanFirst, ArrayScanNext
 * Called by: GameUpdate
 *
 * Elecbyte file: src/mugen/projctl.c
 * Note: 1 float-field accesses rewritten as bit reinterpretations (asm: x87
 *       single loads/stores at offsets 0x4280)
 * Note: 4 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
void ProjArrayCalcDraw(int *arg1)

{
  int array;
  int i2;
  int *pi3;
  int item;
  
  array = *arg1;
  item = ArrayScanFirst(array);
  while (item != 0) {
    if ((*(int *)(item + 4) < 5) && (0 < *(int *)(item + 4))) {
      i2 = g[G_SCALING_TOPZ];
      if (g[G_SCALING_BOTZ] == i2) {
        *(uint32_t *)(item + 0x50) = 0x3f800000;
      }
      else {
        *(float *)(item + 0x50) =
             (BITS_I2F(g[G_SCALING_BOTSCALE]) - BITS_I2F(g[G_SCALING_TOPSCALE])) *
             ((*(float *)(item + 0x4c) - (float80)i2) / (float)(g[G_SCALING_BOTZ] - i2)) +
             (*(float *)&g[G_SCALING_TOPSCALE]);
      }
      pi3 = g;
      *(int *)(item + 0x5c) =
           (int)X87_FIST32((((*(float *)(item + 0x44) - (float)g[0x7311]) - (float)g[0x7315]) - 160.0) *
                      *(float *)(item + 0x50) + 160.0);
      *(int *)(item + 0x60) =
           (int)X87_FIST32(((*(float *)(item + 0x48) * *(float *)(item + 0x50) - (float80)pi3[0x7312])
                      - (float80)pi3[0x7316]) + *(float *)(item + 0x4c) + (float80)pi3[0x4140]);
    }
    item = ArrayScanNext(array);
  }
  return;
}

/* ProjArrayCountActive @ 0x080b97a0, 50 bytes
 *
 * Counts the live projectiles of an array. The NumProj trigger.
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: ArrayScanFirst, ArrayScanNext
 * Called by: AICheckForAttacks, SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/projctl.c
 */
int ProjArrayCountActive(int *arg1)

{
  int array;
  int item;
  int i3;
  
  i3 = 0;
  array = *arg1;
  item = ArrayScanFirst(array);
  while (item != 0) {
    if (*(int *)(item + 4) == 1) {
      i3 = i3 + 1;
    }
    item = ArrayScanNext(array);
  }
  return i3;
}

/* ProjArrayCountActiveID @ 0x080b97e0, 65 bytes
 *
 * Counts the live projectiles with projectile id `id`. The NumProjID
 * trigger.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *
 * Calls: ArrayScanFirst, ArrayScanNext
 * Called by: PlayerAILearnMoveUpdate, SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/projctl.c
 */
int ProjArrayCountActiveID(int *arg1,int arg2)

{
  int array;
  int *item;
  int i3;
  
  i3 = 0;
  array = *arg1;
  item = (int *)ArrayScanFirst(array);
  while (item != (int *)0x0) {
    if ((item[1] == 1) && (*item == arg2)) {
      i3 = i3 + 1;
    }
    item = (int *)ArrayScanNext(array);
  }
  return i3;
}

/* ProjClsnDetect @ 0x080b9830, 209 bytes
 *
 * Tests whether any live projectile's collision boxes overlap the given box
 * array at offset (x, y) with facing. Returns the first such projectile, or
 * NULL. Not called in this build.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int *
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *
 * Calls: ArrayScanFirst, ClsnArrayDetectRectFlip, ArrayScanNext
 *
 * Elecbyte file: src/mugen/projctl.c
 */
uint32_t ProjClsnDetect(int *arg1,int *arg2,int arg3,int arg4,int arg5)

{
  int array;
  int item;
  
  array = *arg1;
  item = ArrayScanFirst(array);
  while( true ) {
    if (item == 0) {
      return 0;
    }
    if ((*(int *)(item + 4) == 1) &&
       (item = ClsnArrayDetectRectFlip
                          (*(int **)(*(int *)(item + 0x294) + 0x28),arg2,
                           (int)X87_FIST32((float)arg3 - *(float *)(item + 0x44)),
                           (int)X87_FIST32((float)arg4 - *(float *)(item + 0x48)),
                           (uint32_t)(*(int *)(item + 0x34) != 1),arg5), item != 0)) break;
    item = ArrayScanNext(array);
  }
  return 1;
}

/* ProjArrayDraw @ 0x080b9910, 105 bytes
 *
 * Draws every live projectile with its scale and facing.
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: ArrayScanFirst, AnimDrawScaleFlip, ArrayScanNext
 * Called by: GameLoop
 *
 * Elecbyte file: src/mugen/projctl.c
 */
uint32_t ProjArrayDraw(int *arg1)

{
  int array;
  int item;
  uint32_t stk_8;
  
  array = *arg1;
  item = ArrayScanFirst(array);
  while (item != 0) {
    if ((*(int *)(item + 4) < 5) && (0 < *(int *)(item + 4))) {
      AnimDrawScaleFlip((uint32_t *)(item + 0x284),*(int *)(item + 0x5c),*(int *)(item + 0x60),
                        *(float *)(item + 0x50) * *(float *)(item + 0x54),
                        *(float *)(item + 0x50) * *(float *)(item + 0x58),
                        (uint32_t)(*(int *)(item + 0x34) != 1));
    }
    item = ArrayScanNext(array);
  }
  return stk_8;
}

/* ProjArrayDrawShadow @ 0x080b9980, 116 bytes
 *
 * Draws the shadows and reflections of every live projectile
 * (ProjDrawShadow) with the stage's shadow and reflection intensity.
 *
 * Parameters:
 *   arg1         int *
 *
 * Globals read: shadow_intensity, reflection_intensity
 * Calls: ArrayScanFirst, ProjDrawShadow, ArrayScanNext
 * Called by: GameLoop
 *
 * Elecbyte file: src/mugen/projctl.c
 */
void ProjArrayDrawShadow(int *arg1)

{
  int array;
  int item;
  uint32_t u3;
  
  array = *arg1;
  item = ArrayScanFirst(array);
  while (item != 0) {
    if (((*(int *)(item + 4) < 5) && (0 < *(int *)(item + 4))) &&
       (u3 = *(uint32_t *)(item + 0x40), u3 != 0)) {
      if (u3 == 0xffffffff) {
        u3 = g[0x10a5];
      }
      ProjDrawShadow(item,g + G_SHADOW_INTENSITY,u3,g + G_REFLECTION_INTENSITY);
    }
    item = ArrayScanNext(array);
  }
  return;
}

/* ProjDrawShadow @ 0x080b9a00, 1174 bytes
 *
 * Draws one projectile's shadow (a darkened, vertically squashed copy under
 * it) and/or its reflection, depending on the stage settings and the
 * DrawShadows option.
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
 * Called by: ProjArrayDrawShadow
 *
 * Elecbyte file: src/mugen/projctl.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to NAN
 * Note: 14 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: 4 temporaries are float80, as the original kept them in x87 registers.
 */
void ProjDrawShadow(int arg1,int *arg2,uint32_t arg3,int *arg4)

{
  int i1;
  int *sprites;
  int i3;
  int i4;
  float80 f5;
  float80 f6;
  float80 f7;
  int i8;
  uint8_t b9;
  uint8_t b10;
  uint8_t b11;
  int i12;
  uint32_t u13;
  float80 f14;
  int stk_3c;
  
  sprites = *(int **)(arg1 + 0x288);
  i3 = *(int *)(arg1 + 0x294);
  i12 = *(int *)(arg1 + 0x34);
  b9 = (uint8_t)_rgb_r_shift_16;
  b10 = (uint8_t)_rgb_g_shift_16;
  stk_3c = *arg2;
  b11 = (uint8_t)_rgb_b_shift_16;
  if ((g[G_CONFIG_DRAWSHADOWS] != 0) && (i8 = AnimCurSpriteIdx(arg1 + 0x284), i8 != -1)) {
    i1 = *(int *)(i3 + 0x14);
    f7 = *(float *)(arg1 + 0x50) * *(float *)(arg1 + 0x54);
    f6 = *(float *)(arg1 + 0x50) * *(float *)(arg1 + 0x58);
    u13 = (uint32_t)(i12 != 1) ^ *(uint32_t *)(i3 + 0x18) & 3;
    f5 = ((float80)*(int *)(i3 + 0x10) * f7 * (float80)i12 + (float80)*(int *)(arg1 + 0x5c)
            ) - (float)g[0x7315];
    if ((u13 & 1) != 0) {
      f7 = f7 * -1.0;
    }
    if ((u13 & 2) == 0) {
      f6 = f6 * -1.0;
    }
    if (g[G_VIDEO_LINUX_DOUBLERES] == 4) {
      f5 = f5 + f5;
      f7 = f7 + f7;
    }
    i3 = (int)X87_FIST32(f5);
    if (0 < *arg4) {
      f5 = ((((float)g[G_STAGEINFO_ZOFFSET] - (*(float *)(arg1 + 0x48) + (float80)i1)) - (float)g[0x7312])
              + *(float *)(arg1 + 0x4c)) - (float)g[0x7316];
      if (g[G_VIDEO_LINUX_DOUBLERES] == 4) {
        f5 = f5 + f5;
      }
      W_RotateSpriteTransAdd_B
                (sprites,i8,(float80)i3,(float80)(int)X87_FIST32(f5),0.0,f7,f6,*arg4,
                 0x100 - *arg4);
    }
    f5 = *(float *)(arg1 + 0x50) * *(float *)(arg1 + 0x58);
    f6 = ((((float)g[G_STAGEINFO_ZOFFSET] -
              (*(float *)(arg1 + 0x48) + (float80)i1) * f5 * BITS_I2F(arg2[2])) -
             (float)g[0x7312]) + *(float *)(arg1 + 0x4c)) - (float)g[0x7316];
    if ((u13 & 2) == 0) {
      f5 = f5 * -1.0;
    }
    if (g[G_VIDEO_LINUX_DOUBLERES] == 4) {
      f6 = f6 + f6;
      f5 = f5 + f5;
    }
    i12 = 0x100;
    i1 = arg2[3];
    i4 = arg2[4];
    if (i1 < i4) {
      f14 = *(float *)(arg1 + 0x48);
      if ((float80)i1 < f14) {
        if (f14 < (float80)i4) {
          i12 = (int)X87_FIST32(((f14 - (float80)i1) * 256.0) / (float)(i4 - i1));
        }
      }
      else {
        i12 = 0;
      }
    }
    if (i12 < 0x100) {
      stk_3c = i12 * stk_3c >> 8;
      arg3 = ((int)((arg3 & 0x1f) * i12) >> 8 & 0x1fU) +
                ((int)((arg3 & 0xf800) * i12) >> 8 & 0xf800U) +
                ((int)((arg3 & 0x7e0) * i12) >> 8 & 0x7e0U);
    }
    if ((arg3 == (0x1f << (b9 & 0x1f) | 0x3f << (b10 & 0x1f) | 0x1f << (b11 & 0x1f))) ||
       (stk_3c == 0x100)) {
      stk_3c = 0;
      f14 = BITS_I2F(arg2[2]);
    }
    else {
      if (arg3 != 0) {
        W_RotateShadowTransSub_P
                  (sprites,i8,(float80)i3,(float80)(int)X87_FIST32(f6),0.0,f7,f5,1.0,
                   BITS_I2F(arg2[2]),arg3);
      }
      if (stk_3c < 1) {
        return;
      }
      stk_3c = 0x100 - stk_3c;
      f14 = BITS_I2F(arg2[2]);
    }
    W_RotateSpriteTransAdd_B_P
              (sprites,i8,(float80)i3,(float80)(int)X87_FIST32(f6),0.0,f7,f5,1.0,f14,0,
               stk_3c);
  }
  return;
}

/* ProjArrayClsnDraw @ 0x080b9ea0, 51 bytes
 *
 * Draws the collision boxes of every live projectile (debug display).
 *
 * Parameters:
 *   arg1         int *
 *   arg2         float
 *
 * Calls: ArrayScanFirst, ProjClsnDraw, ArrayScanNext
 * Called by: GameLoop
 *
 * Elecbyte file: src/mugen/projctl.c
 */
void ProjArrayClsnDraw(int *arg1,float arg2)

{
  int array;
  int item;
  
  array = *arg1;
  item = ArrayScanFirst(array);
  while (item != 0) {
    ProjClsnDraw(item,arg2);
    item = ArrayScanNext(array);
  }
  return;
}

/* ProjClsnDraw @ 0x080b9ee0, 229 bytes
 *
 * Draws one projectile's collision boxes at its screen position
 * (GameClsnDraw).
 *
 * Parameters:
 *   arg1         int
 *   arg2         float
 *
 * Globals read: stageinfo_zoffset
 * Calls: GameClsnDraw
 * C library: makecol
 * Called by: ProjArrayClsnDraw
 *
 * Elecbyte file: src/mugen/projctl.c
 * Note: 5 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 3 temporaries are float80, as the original kept them in x87 registers.
 */
void ProjClsnDraw(int arg1,float arg2)

{
  int i1;
  int i2;
  int i3;
  float80 f4;
  float80 f5;
  float80 f6;
  uint32_t u7;
  uint32_t u8;
  uint32_t u9;
  
  i1 = g[0x7311];
  f4 = *(float *)(arg1 + 0x44);
  u9 = (uint32_t)(*(int *)(arg1 + 0x34) != 1);
  i2 = g[0x7312];
  i3 = g[G_STAGEINFO_ZOFFSET];
  f5 = *(float *)(arg1 + 0x48);
  f6 = *(float *)(arg1 + 0x4c);
  u7 = (uint32_t)(g[0x81d0] == 2);
  u8 = makecol(0xff,0,0);
  GameClsnDraw(*(int *)(*(int *)(arg1 + 0x294) + 0x28),
               (float80)(int)X87_FIST32(f4 - (float80)i1) * arg2,
               (float80)(int)X87_FIST32((f5 - (float80)i2) + f6 + (float80)i3) * arg2,arg2,
               arg2,u8,u9,u7);
  return;
}

