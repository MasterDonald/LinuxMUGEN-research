/*
 * afterimg.c -- afterimages
 * Afterimage trails: a ring of recent frames of a player or projectile,
 * drawn with progressive palette effects.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/afterimg.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* AftImgNew @ 0x08082070, 74 bytes
 *
 * Allocates and initialises an afterimage record for `length` frames. Not
 * called in this build.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: ecalloc, AftImgInit, AftImgFree
 *
 * Elecbyte file: src/mugen/afterimg.c
 */
int * AftImgNew(int arg1)

{
  int *mem;
  int i2;
  
  mem = (int *)ecalloc(1,0x7c);
  if (mem == (int *)0x0) {
    mem = (int *)0x0;
  }
  else {
    i2 = AftImgInit(mem,arg1);
    if (i2 == 0) {
      AftImgFree(mem);
      mem = (int *)0x0;
    }
  }
  return mem;
}

/* AftImgInit @ 0x080820c0, 140 bytes
 *
 * Initialises an afterimage record: a ring of `length` frame snapshots and a
 * private palette used to tint them.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *
 * Calls: ecalloc, EBPalInit
 * Called by: AftImgNew, GameAftImgArrayNew
 *
 * Elecbyte file: src/mugen/afterimg.c
 */
uint32_t AftImgInit(int *arg1,int arg2)

{
  uint32_t u1;
  int i2;
  int mem;
  int i4;
  int *pi5;
  
  pi5 = arg1;
  for (mem = 0x1f; mem != 0; mem = mem + -1) {
    *pi5 = 0;
    pi5 = pi5 + 1;
  }
  mem = ecalloc(1,arg2 * 0x67c);
  *arg1 = mem;
  if (mem == 0) {
L_080820fc:
    u1 = 0;
  }
  else {
    mem = 0;
    arg1[1] = arg2;
    if (0 < arg2) {
      i4 = 0;
      do {
        i2 = EBPalInit((int *)(i4 + *arg1 + 0x20),0x100,(void *)(i4 + *arg1 + 0x27c),
                          0);
        if (i2 == 0) goto L_080820fc;
        mem = mem + 1;
        i4 = i4 + 0x67c;
      } while (mem < arg2);
    }
    u1 = 1;
  }
  return u1;
}

/* AftImgFree @ 0x08082150, 37 bytes
 *
 * Deinitialises and frees an afterimage record.
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: AftImgDeInit
 * C library: free
 * Called by: AftImgNew
 *
 * Elecbyte file: src/mugen/afterimg.c
 */
uint32_t AftImgFree(int *arg1)

{
  uint32_t stale_EAX;
  uint32_t entry_EDX;
  
  if (arg1 != (int *)0x0) {
    AftImgDeInit(arg1);
    free(arg1);
    return stale_EAX;
  }
  return entry_EDX;
}

/* AftImgDeInit @ 0x08082180, 97 bytes
 *
 * Frees an afterimage record's snapshot ring and palette.
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: EBPalDeInit
 * C library: free
 * Called by: AftImgFree, GameAftImgArrayFree
 *
 * Elecbyte file: src/mugen/afterimg.c
 */
void AftImgDeInit(int *arg1)

{
  int i1;
  int i2;
  
  if (arg1 != (int *)0x0) {
    i1 = *arg1;
    if (i1 != 0) {
      i2 = 0;
      if (0 < arg1[1]) {
        while( true ) {
          EBPalDeInit(i1 + 0x20 + i2 * 0x67c);
          if (arg1[1] <= i2 + 1) break;
          i1 = *arg1;
          i2 = i2 + 1;
        }
      }
      free((void *)*arg1);
    }
    for (i1 = 0x1f; i1 != 0; i1 = i1 + -1) {
      *arg1 = 0;
      arg1 = arg1 + 1;
    }
  }
  return;
}

/* AftImgSetup @ 0x080821f0, 59 bytes
 *
 * Starts an afterimage effect: copies the 24 effect parameters (time,
 * length, colour adds and multipliers, timegap, framegap, blend) and resets
 * the ring.
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t *
 *   arg3         uint32_t
 *
 * Called by: SCtrlInitAftImgParams
 *
 * Elecbyte file: src/mugen/afterimg.c
 */
void AftImgSetup(int arg1,uint32_t *arg2,uint32_t arg3)

{
  int i1;
  uint32_t *pu2;
  
  *(uint32_t *)(arg1 + 0x18) = 1;
  *(uint32_t *)(arg1 + 0x10) = 0;
  *(uint32_t *)(arg1 + 0xc) = 0;
  *(uint32_t *)(arg1 + 0x14) = 0;
  *(uint32_t *)(arg1 + 8) = arg3;
  pu2 = (uint32_t *)(arg1 + 0x1c);
  for (i1 = 0x18; i1 != 0; i1 = i1 + -1) {
    *pu2 = *arg2;
    arg2 = arg2 + 1;
    pu2 = pu2 + 1;
  }
  return;
}

/* AftImgUpdate @ 0x08082230, 448 bytes
 *
 * Records the owner's current frame (sprite, position, scale, angle, facing)
 * into the afterimage ring every `timegap` ticks while the effect is active,
 * and counts down its remaining time. Returns 0 when inactive.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         float
 *   arg3         float
 *   arg4         float
 *   arg5         uint32_t
 *   arg6         float
 *   arg7         uint32_t
 *   arg8         int
 *
 * Calls: FlipFlagMix, HFlipToSgn
 * Called by: PlayerAftImgUpdate, ProjAftImgUpdate
 *
 * Elecbyte file: src/mugen/afterimg.c
 * Note: 3 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: untyped (undefined4) <-> float moves kept as bit copies: 4 assignments,
 *       0 calls, 0 returns
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t
AftImgUpdate(int *arg1,float arg2,float arg3,float arg4,uint32_t arg5,float arg6
            ,uint32_t arg7,int arg8)

{
  uint32_t *pu1;
  int i2;
  float80 f3;
  uint32_t u4;
  uint32_t u5;
  int i6;
  int i7;
  
  if ((arg1[6] == 0) || (i2 = arg1[2], i2 == 0)) {
L_08082291:
    u4 = 0;
  }
  else {
    if (arg1[7] == -1) {
      i7 = arg1[5];
      i6 = arg1[9];
    }
    else {
      i7 = arg1[5];
      i6 = arg1[9];
      if (arg1[8] * i6 + arg1[7] <= i7 + 1) {
        arg1[6] = 0;
        goto L_08082291;
      }
    }
    if (i7 % i6 == 0) {
      pu1 = (uint32_t *)(*arg1 + arg1[4] * 0x67c);
      *pu1 = *(uint32_t *)(i2 + 0x2c);
      u5 = FlipFlagMix(arg7,*(uint32_t *)(*(int *)(i2 + 0x10) + 0x18) & 3);
      pu1[5] = u5;
      pu1[3] = BITS_F2I(uint32_t, arg4);
      pu1[4] = arg5;
      f3 = (float80)*(int *)(*(int *)(arg1[2] + 0x10) + 0x10) * arg4;
      if ((arg7 & 1) != 0) {
        f3 = f3 * -1.0;
      }
      pu1[1] = BITS_F2I(uint32_t, f3 + arg2);
      f3 = (float80)*(int *)(*(int *)(arg1[2] + 0x10) + 0x14) * BITS_I2F(pu1[4]);
      if ((arg7 & 2) != 0) {
        f3 = f3 * -1.0;
      }
      pu1[2] = BITS_F2I(uint32_t, f3 + arg3);
      pu1[6] = *(uint32_t *)(arg1[2] + 0x34);
      i6 = HFlipToSgn(arg7);
      i2 = arg1[5];
      i7 = arg1[7];
      pu1[7] = BITS_F2I(uint32_t, (float80)i6 * arg6);
      if ((i7 <= i2 + 1) && (i7 != -1)) {
        *pu1 = 0xffffffff;
      }
      u5 = arg1[4] + 1;
      arg1[4] = u5;
      u5 = u5 & (arg1[8] <= (int)u5) - 1;
      arg1[4] = u5;
      if (u5 == arg1[3]) {
        u5 = u5 + 1;
        arg1[3] = u5;
        arg1[3] = u5 & (arg1[8] <= (int)u5) - 1;
      }
    }
    if (arg8 != 0) {
      arg1[5] = arg1[5] + 1;
    }
    u4 = 1;
  }
  return u4;
}

/* AftImgDraw @ 0x080823f0, 1157 bytes
 *
 * Draws the afterimage trail: every `framegap`-th snapshot, oldest first,
 * with the palette progressively processed by the effect parameters: colour,
 * invert, brightness add, multiply and per-step add/multiply (Pal4ColorBal,
 * Pal4InvertAll, Pal4BrightnessRGB, Pal4ContrastRGB). The configured blend
 * mode is applied.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Calls: EBPalGetDataptr, SpriteArrayAccess, EBPalSetDataptr, EBPalReset,
 *        SpriteArrayPalAccess, Pal4ColorBal, Pal4InvertAll,
 *        Pal4BrightnessRGB, Pal4ContrastRGB, EBPalMarkDataChanged,
 *        EBPalAdd, EBPalMul, PRSprAdd
 * Called by: PlayerAftImgDraw, ProjAftImgDraw
 *
 * Elecbyte file: src/mugen/afterimg.c
 * Note: Locals live in `frame`, laid out as on the original stack (0xa0 bytes,
 *       20 variables), because their address is taken.
 */
void AftImgDraw(int *arg1,int arg2,int arg3,int arg4)

{
  int *pi1;
  int i2;
  int *sprites;
  bool b4;
  int i5;
  int sprite;
  int i7;
  int i8;
  int *pi9;
  int i10;
  int *pi11;
  int i12;
  int i13;
  int i14;
  unsigned char frame[0xa0] __attribute__((aligned(16)));
#define stk_94 (*(float *)(frame + 0xc))
#define stk_90 (*(float *)(frame + 0x10))
#define stk_8c (*(float *)(frame + 0x14))
#define stk_88 (*(int *)(frame + 0x18))
#define stk_74 (*(int *)(frame + 0x2c))
#define stk_70 (*(int *)(frame + 0x30))
#define stk_5c (*(int *)(frame + 0x44))
#define stk_58 (*(int **)(frame + 0x48))
#define stk_54 (*(int *)(frame + 0x4c))
#define stk_50 (*(int **)(frame + 0x50))
#define stk_4c (*(int *)(frame + 0x54))
#define stk_48 (*(int *)(frame + 0x58))
#define stk_44 (*(uint32_t *)(frame + 0x5c))
#define stk_40 (*(int *)(frame + 0x60))
#define stk_3c (*(int *)(frame + 0x64))
#define stk_38 (*(int *)(frame + 0x68))
#define stk_34 (*(float *)(frame + 0x6c))
#define stk_30 (*(float *)(frame + 0x70))
#define stk_2c (*(int *)(frame + 0x74))
#define stk_28 (*(int *)(frame + 0x78))
  
  stk_74 = 0;
  stk_88 = 0;
  if (arg1[6] != 0) {
    i5 = arg1[3];
    i10 = arg1[4];
    if (i5 != i10) {
      b4 = i5 <= i10;
      stk_70 = -1;
      if (i10 < 0) {
        b4 = true;
        i10 = i10 + arg1[8];
      }
      do {
        sprite = arg1[10];
        while( true ) {
          while( true ) {
            do {
              i10 = i10 - sprite;
              if ((i10 < 0) && (!b4)) {
                b4 = true;
                i10 = i10 + arg1[8];
              }
              if ((i10 < i5) && (b4)) {
                return;
              }
              pi1 = (int *)(*arg1 + i10 * 0x67c);
              i2 = *pi1;
            } while (i2 == -1);
            pi9 = pi1 + 8;
            i5 = EBPalGetDataptr((int)pi9);
            sprites = *(int **)(arg1[2] + 4);
            sprite = SpriteArrayAccess(sprites,i2);
            i7 = *(int *)(sprite + 0x14) + -1;
            if (0 < i7) break;
            sprite = arg1[10];
            i5 = arg1[3];
          }
          if (*(int *)(sprite + 0x30) != -1) break;
          sprite = arg1[10];
          i5 = arg1[3];
        }
        EBPalSetDataptr(pi9,*(int *)(sprite + 0x14),0);
        EBPalReset((int)pi9);
        if (stk_74 == 0) {
          i8 = SpriteArrayPalAccess((int)sprites,*(int *)(sprite + 0x30));
          i13 = 1;
          sprite = arg1[0xb];
          i12 = i5;
          i14 = i7;
          i8 = EBPalGetDataptr(i8);
          Pal4ColorBal(i8,i12,sprite,i13,i14);
          if (arg1[0xc] != 0) {
            Pal4InvertAll(i5,i5,1,i7);
          }
          Pal4BrightnessRGB(i5,i5,arg1[0xd],arg1[0xe],arg1[0xf],1,i7);
          Pal4ContrastRGB(i5,i5,arg1[0x10],arg1[0x11],arg1[0x12],1,i7);
          Pal4BrightnessRGB(i5,i5,arg1[0x13],arg1[0x14],arg1[0x15],1,i7);
          stk_90 = 256.0;
          stk_94 = 256.0;
          stk_8c = 256.0;
          EBPalMarkDataChanged((int)pi9);
          stk_88 = i5;
        }
        else {
          stk_8c = stk_8c * BITS_I2F(arg1[0x19]);
          stk_90 = stk_90 * BITS_I2F(arg1[0x1a]);
          stk_94 = stk_94 * BITS_I2F(arg1[0x1b]);
          EBPalSetDataptr(pi9,-1,stk_88);
          EBPalAdd((int)pi9,arg1[0x16] * stk_74,arg1[0x17] * stk_74,
                   arg1[0x18] * stk_74);
          EBPalMul((int)pi9,(int)X87_FIST32(stk_8c),(int)X87_FIST32(stk_90),(int)X87_FIST32(stk_94));
        }
        stk_74 = stk_74 + 1;
        pi11 = &stk_5c;
        for (i5 = 0xe; i5 != 0; i5 = i5 + -1) {
          *pi11 = 0;
          pi11 = pi11 + 1;
        }
        stk_5c = pi1[6];
        if (arg4 < pi1[6]) {
          stk_5c = arg4;
        }
        stk_5c = stk_5c + stk_70;
        stk_4c = (int)X87_FIST32((float)arg2 + BITS_I2F(pi1[1]));
        stk_48 = (int)X87_FIST32((float)arg3 + BITS_I2F(pi1[2]));
        stk_40 = arg1[0x1c];
        stk_3c = arg1[0x1d];
        stk_38 = arg1[0x1e];
        stk_34 = BITS_I2F(pi1[3]);
        stk_28 = pi1[5];
        stk_30 = BITS_I2F(pi1[4]);
        if (BITS_I2F(pi1[7]) == 0.0) {
          stk_44 = 2;
          if ((stk_34 == 1.0) && (stk_30 == 1.0)) {
            stk_44 = 1;
          }
        }
        else {
          stk_44 = 3;
          stk_2c = pi1[7];
        }
        stk_58 = sprites;
        stk_54 = i2;
        stk_50 = pi9;
        PRSprAdd(*(int **)(arg1[2] + 0x30),&stk_5c);
        i5 = arg1[3];
        stk_70 = stk_70 + -1;
      } while( true );
    }
  }
  return;
}
#undef stk_94
#undef stk_90
#undef stk_8c
#undef stk_88
#undef stk_74
#undef stk_70
#undef stk_5c
#undef stk_58
#undef stk_54
#undef stk_50
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

