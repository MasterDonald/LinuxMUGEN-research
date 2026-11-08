/*
 * projctl.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x080b9170-0x080b9fc5, 14 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* ProjArrayNew @ 0x080b9170, 100 bytes */
undefined4 * ProjArrayNew(size_t param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = calloc(1,0xc);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar2 = ArrayNew(param_1,0x2dc,0);
    *puVar1 = puVar2;
    if (puVar2 == (undefined4 *)0x0) {
      ProjArrayFree(puVar1);
      puVar1 = (undefined4 *)0x0;
    }
    else {
      puVar1[1] = param_2;
      puVar1[2] = param_3;
    }
  }
  return puVar1;
}

/* ProjArrayFree @ 0x080b91e0, 39 bytes */
void ProjArrayFree(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    ArrayFree((void *)*param_1);
    free(param_1);
    return;
  }
  return;
}

/* ProjArrayAdd @ 0x080b9210, 147 bytes */
int ProjArrayAdd(int *param_1,int *param_2,void *param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  
  iVar2 = *param_2;
  puVar3 = (undefined4 *)param_1[0x4ef];
  iVar4 = ArrayFindEmpty(iVar2);
  if (iVar4 != -1) {
    iVar5 = iVar4 * *(int *)(iVar2 + 4) + *(int *)(iVar2 + 0x14);
    iVar4 = ArrayAdd(iVar2,param_3,0,0);
    if (iVar4 != -1) {
      piVar1 = (int *)(iVar5 + 0x284);
      AnimCopy(piVar1,puVar3);
      *(undefined4 *)(iVar5 + 0x284) = *(undefined4 *)(*param_1 + 0x11cc);
      AnimChangeAction(piVar1,0,param_4);
      AnimResetAction(piVar1);
    }
  }
  return iVar4;
}

/* ProjArrayDelete @ 0x080b92b0, 84 bytes */
void ProjArrayDelete(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_2 * *(int *)(*param_1 + 4) + *(int *)(*param_1 + 0x14);
  if (iVar2 != 0) {
    iVar1 = *(int *)(iVar2 + 0x2d8);
    if (iVar1 != 0) {
      *(undefined4 *)(iVar1 + 0x18) = 0;
      *(undefined4 *)(iVar1 + 8) = 0;
      *(undefined4 *)(iVar2 + 0x2d8) = 0;
    }
    ArrayDelete(*param_1,param_2);
    return;
  }
  return;
}

/* ProjArrayUpdate @ 0x080b9310, 864 bytes
 * FIXUP: 5 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void ProjArrayUpdate(int *param_1)

{
  float10 fVar1;
  int iVar2;
  bool bVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  
  iVar2 = *param_1;
  iVar5 = ArrayScanFirst(iVar2);
  do {
    piVar4 = g;
    if (iVar5 == 0) {
      return;
    }
    bVar3 = false;
    *(undefined4 *)(iVar5 + 0x2c0) = 0;
    if (((piVar4[0x74f3] != -1) &&
        (iVar6 = *(int *)(iVar5 + 0x2d0 + piVar4[0x74f3] * 4), iVar6 < *(int *)(iVar5 + 0x20))) &&
       (iVar6 != -1)) {
      bVar3 = true;
    }
    if (bVar3) {
      *(undefined4 *)(iVar5 + 0x2c0) = 1;
    }
    if ((*(int *)(iVar5 + 0x28) == 0) && (!bVar3)) {
      while (iVar6 = *(int *)(iVar5 + 4), iVar6 == 1) {
        *(float *)(iVar5 + 0x44) = *(float *)(iVar5 + 0x44) + *(float *)(iVar5 + 100);
        fVar1 = *(float *)(iVar5 + 100) * *(float *)(iVar5 + 0x74) + *(float *)(iVar5 + 0x7c);
        *(float *)(iVar5 + 100) = fVar1;
        *(float *)(iVar5 + 0x48) = *(float *)(iVar5 + 0x48) + *(float *)(iVar5 + 0x68);
        *(float *)(iVar5 + 0x68) =
             *(float *)(iVar5 + 0x68) * *(float *)(iVar5 + 0x78) + *(float *)(iVar5 + 0x80);
        if (fVar1 <= 0.0) {
          if (*(float *)(iVar5 + 100) < 0.0) {
            *(undefined4 *)(iVar5 + 0x34) = 0xffffffff;
          }
        }
        else {
          *(undefined4 *)(iVar5 + 0x34) = 1;
        }
        fVar1 = *(float *)(iVar5 + 0x44);
        if ((((((float10)*(int *)(iVar5 + 0x88) <= fVar1) || (0.0 <= *(float *)(iVar5 + 100))) &&
             (((float10)*(int *)(iVar5 + 0x8c) <= *(float *)(iVar5 + 0x48) ||
              (0.0 <= *(float *)(iVar5 + 0x68))))) &&
            ((fVar1 <= (float10)*(int *)(iVar5 + 0x90) || (*(float *)(iVar5 + 100) <= 0.0)))) &&
           ((*(float *)(iVar5 + 0x48) <= (float10)*(int *)(iVar5 + 0x94) ||
            (*(float *)(iVar5 + 0x68) <= 0.0)))) {
          if (((float)(g[0x7311] - *(int *)(iVar5 + 0x84)) <= fVar1) &&
             (fVar1 <= (float)(*(int *)(iVar5 + 0x84) + 0x140 + g[0x7311]))) {
            if (0 < *(int *)(iVar5 + 0x2c)) {
              *(int *)(iVar5 + 0x2c) = *(int *)(iVar5 + 0x2c) + -1;
            }
            if ((*(int *)(iVar5 + 0x24) < *(int *)(iVar5 + 0x3c)) || (*(int *)(iVar5 + 0x3c) == -1))
            goto LAB_080b95e7;
          }
        }
        *(undefined4 *)(iVar5 + 4) = 2;
        *(undefined4 *)(iVar5 + 0x24) = 0;
      }
      if ((iVar6 < 1) || (4 < iVar6)) {
        iVar6 = *(int *)(iVar2 + 0x1c);
      }
      else {
        iVar6 = *(int *)(iVar5 + 4);
        *(float *)(iVar5 + 0x44) = *(float *)(iVar5 + 0x44) + *(float *)(iVar5 + 100);
        *(float *)(iVar5 + 0x48) = *(float *)(iVar5 + 0x48) + *(float *)(iVar5 + 0x68);
        if ((((iVar6 == 2) && (*(int *)(iVar5 + 0x14) == -1)) ||
            ((iVar6 == 3 && (*(int *)(iVar5 + 0x18) == -1)))) ||
           ((iVar6 == 4 && (*(int *)(iVar5 + 0x10) == -1)))) {
LAB_080b95ae:
          iVar6 = *(int *)(iVar2 + 0x1c);
        }
        else {
          if (*(int *)(iVar5 + 0x24) == 0) {
            *(undefined4 *)(iVar5 + 100) = *(undefined4 *)(iVar5 + 0x6c);
            *(undefined4 *)(iVar5 + 0x68) = *(undefined4 *)(iVar5 + 0x70);
            if (*(int *)(iVar5 + 4) == 2) {
              iVar6 = *(int *)(iVar5 + 0x14);
            }
            else if (*(int *)(iVar5 + 4) == 4) {
              iVar6 = *(int *)(iVar5 + 0x10);
            }
            else {
              iVar6 = *(int *)(iVar5 + 0x18);
            }
            AnimChangeAction((int *)(iVar5 + 0x284),0,iVar6);
            iVar6 = AnimGetLooptime((undefined4 *)(iVar5 + 0x284));
            if (iVar6 < 1) goto LAB_080b95ae;
          }
          iVar6 = AnimGetLooptime((undefined4 *)(iVar5 + 0x284));
          if (*(int *)(iVar5 + 0x2a0) != iVar6) goto LAB_080b95e7;
          iVar6 = *(int *)(iVar2 + 0x1c);
        }
      }
      ProjArrayDelete(param_1,iVar6);
    }
LAB_080b95e7:
    if (!bVar3) {
      *(int *)(iVar5 + 0x2b8) =
           (int)GHIDRA_FIST32(*(float *)(iVar5 + 0x4c) * 10.0 + (float10)*(int *)(iVar5 + 700));
      AnimUpdate((undefined4 *)(iVar5 + 0x284));
      if (*(int *)(iVar5 + 0x28) < 1) {
        *(int *)(iVar5 + 0x20) = *(int *)(iVar5 + 0x20) + 1;
        *(int *)(iVar5 + 0x24) = *(int *)(iVar5 + 0x24) + 1;
      }
      else {
        *(int *)(iVar5 + 0x28) = *(int *)(iVar5 + 0x28) + -1;
      }
    }
    iVar5 = ArrayScanNext(iVar2);
  } while( true );
}

/* ProjArrayCalcDraw @ 0x080b9670, 302 bytes
 * FIXUP: 1 float-field accesses rewritten as bit reinterpretations (asm: x87 single loads/stores at offsets 0x4280)
 * FIXUP: 4 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
void ProjArrayCalcDraw(int *param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar1 = *param_1;
  iVar4 = ArrayScanFirst(iVar1);
  while (iVar4 != 0) {
    if ((*(int *)(iVar4 + 4) < 5) && (0 < *(int *)(iVar4 + 4))) {
      iVar2 = g[0x109e];
      if (g[0x109f] == iVar2) {
        *(undefined4 *)(iVar4 + 0x50) = 0x3f800000;
      }
      else {
        *(float *)(iVar4 + 0x50) =
             (GHIDRA_I2F(g[0x10a1]) - GHIDRA_I2F(g[0x10a0])) *
             ((*(float *)(iVar4 + 0x4c) - (float10)iVar2) / (float)(g[0x109f] - iVar2)) +
             (*(float *)&g[0x10a0]);
      }
      piVar3 = g;
      *(int *)(iVar4 + 0x5c) =
           (int)GHIDRA_FIST32((((*(float *)(iVar4 + 0x44) - (float)g[0x7311]) - (float)g[0x7315]) - 160.0) *
                      *(float *)(iVar4 + 0x50) + 160.0);
      *(int *)(iVar4 + 0x60) =
           (int)GHIDRA_FIST32(((*(float *)(iVar4 + 0x48) * *(float *)(iVar4 + 0x50) - (float10)piVar3[0x7312])
                      - (float10)piVar3[0x7316]) + *(float *)(iVar4 + 0x4c) + (float10)piVar3[0x4140]);
    }
    iVar4 = ArrayScanNext(iVar1);
  }
  return;
}

/* ProjArrayCountActive @ 0x080b97a0, 50 bytes */
int ProjArrayCountActive(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar1 = *param_1;
  iVar2 = ArrayScanFirst(iVar1);
  while (iVar2 != 0) {
    if (*(int *)(iVar2 + 4) == 1) {
      iVar3 = iVar3 + 1;
    }
    iVar2 = ArrayScanNext(iVar1);
  }
  return iVar3;
}

/* ProjArrayCountActiveID @ 0x080b97e0, 65 bytes */
int ProjArrayCountActiveID(int *param_1,int param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar1 = *param_1;
  piVar2 = (int *)ArrayScanFirst(iVar1);
  while (piVar2 != (int *)0x0) {
    if ((piVar2[1] == 1) && (*piVar2 == param_2)) {
      iVar3 = iVar3 + 1;
    }
    piVar2 = (int *)ArrayScanNext(iVar1);
  }
  return iVar3;
}

/* ProjClsnDetect @ 0x080b9830, 209 bytes */
undefined4 ProjClsnDetect(int *param_1,int *param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *param_1;
  iVar2 = ArrayScanFirst(iVar1);
  while( true ) {
    if (iVar2 == 0) {
      return 0;
    }
    if ((*(int *)(iVar2 + 4) == 1) &&
       (iVar2 = ClsnArrayDetectRectFlip
                          (*(int **)(*(int *)(iVar2 + 0x294) + 0x28),param_2,
                           (int)GHIDRA_FIST32((float)param_3 - *(float *)(iVar2 + 0x44)),
                           (int)GHIDRA_FIST32((float)param_4 - *(float *)(iVar2 + 0x48)),
                           (uint)(*(int *)(iVar2 + 0x34) != 1),param_5), iVar2 != 0)) break;
    iVar2 = ArrayScanNext(iVar1);
  }
  return 1;
}

/* ProjArrayDraw @ 0x080b9910, 105 bytes */
undefined4 ProjArrayDraw(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uStack_8;
  
  iVar1 = *param_1;
  iVar2 = ArrayScanFirst(iVar1);
  while (iVar2 != 0) {
    if ((*(int *)(iVar2 + 4) < 5) && (0 < *(int *)(iVar2 + 4))) {
      AnimDrawScaleFlip((undefined4 *)(iVar2 + 0x284),*(int *)(iVar2 + 0x5c),*(int *)(iVar2 + 0x60),
                        *(float *)(iVar2 + 0x50) * *(float *)(iVar2 + 0x54),
                        *(float *)(iVar2 + 0x50) * *(float *)(iVar2 + 0x58),
                        (uint)(*(int *)(iVar2 + 0x34) != 1));
    }
    iVar2 = ArrayScanNext(iVar1);
  }
  return uStack_8;
}

/* ProjArrayDrawShadow @ 0x080b9980, 116 bytes */
void ProjArrayDrawShadow(int *param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = *param_1;
  iVar2 = ArrayScanFirst(iVar1);
  while (iVar2 != 0) {
    if (((*(int *)(iVar2 + 4) < 5) && (0 < *(int *)(iVar2 + 4))) &&
       (uVar3 = *(uint *)(iVar2 + 0x40), uVar3 != 0)) {
      if (uVar3 == 0xffffffff) {
        uVar3 = g[0x10a5];
      }
      ProjDrawShadow(iVar2,g + 0x10a4,uVar3,g + 0x10a9);
    }
    iVar2 = ArrayScanNext(iVar1);
  }
  return;
}

/* ProjDrawShadow @ 0x080b9a00, 1174 bytes
 * REVIEW: calls-missing-in-pid:NAN
 * FIXUP: 14 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 4 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void ProjDrawShadow(int param_1,int *param_2,uint param_3,int *param_4)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  int iVar8;
  byte bVar9;
  byte bVar10;
  byte bVar11;
  int iVar12;
  uint uVar13;
  float10 fVar14;
  int local_3c;
  
  piVar2 = *(int **)(param_1 + 0x288);
  iVar3 = *(int *)(param_1 + 0x294);
  iVar12 = *(int *)(param_1 + 0x34);
  bVar9 = (byte)_rgb_r_shift_16;
  bVar10 = (byte)_rgb_g_shift_16;
  local_3c = *param_2;
  bVar11 = (byte)_rgb_b_shift_16;
  if ((g[0x7570] != 0) && (iVar8 = AnimCurSpriteIdx(param_1 + 0x284), iVar8 != -1)) {
    iVar1 = *(int *)(iVar3 + 0x14);
    fVar7 = *(float *)(param_1 + 0x50) * *(float *)(param_1 + 0x54);
    fVar6 = *(float *)(param_1 + 0x50) * *(float *)(param_1 + 0x58);
    uVar13 = (uint)(iVar12 != 1) ^ *(uint *)(iVar3 + 0x18) & 3;
    fVar5 = ((float10)*(int *)(iVar3 + 0x10) * fVar7 * (float10)iVar12 + (float10)*(int *)(param_1 + 0x5c)
            ) - (float)g[0x7315];
    if ((uVar13 & 1) != 0) {
      fVar7 = fVar7 * -1.0;
    }
    if ((uVar13 & 2) == 0) {
      fVar6 = fVar6 * -1.0;
    }
    if (g[0x7559] == 4) {
      fVar5 = fVar5 + fVar5;
      fVar7 = fVar7 + fVar7;
    }
    iVar3 = (int)GHIDRA_FIST32(fVar5);
    if (0 < *param_4) {
      fVar5 = ((((float)g[0x4140] - (*(float *)(param_1 + 0x48) + (float10)iVar1)) - (float)g[0x7312])
              + *(float *)(param_1 + 0x4c)) - (float)g[0x7316];
      if (g[0x7559] == 4) {
        fVar5 = fVar5 + fVar5;
      }
      W_RotateSpriteTransAdd_B
                (piVar2,iVar8,(float10)iVar3,(float10)(int)GHIDRA_FIST32(fVar5),0.0,fVar7,fVar6,*param_4,
                 0x100 - *param_4);
    }
    fVar5 = *(float *)(param_1 + 0x50) * *(float *)(param_1 + 0x58);
    fVar6 = ((((float)g[0x4140] -
              (*(float *)(param_1 + 0x48) + (float10)iVar1) * fVar5 * GHIDRA_I2F(param_2[2])) -
             (float)g[0x7312]) + *(float *)(param_1 + 0x4c)) - (float)g[0x7316];
    if ((uVar13 & 2) == 0) {
      fVar5 = fVar5 * -1.0;
    }
    if (g[0x7559] == 4) {
      fVar6 = fVar6 + fVar6;
      fVar5 = fVar5 + fVar5;
    }
    iVar12 = 0x100;
    iVar1 = param_2[3];
    iVar4 = param_2[4];
    if (iVar1 < iVar4) {
      fVar14 = *(float *)(param_1 + 0x48);
      if ((float10)iVar1 < fVar14) {
        if (fVar14 < (float10)iVar4) {
          iVar12 = (int)GHIDRA_FIST32(((fVar14 - (float10)iVar1) * 256.0) / (float)(iVar4 - iVar1));
        }
      }
      else {
        iVar12 = 0;
      }
    }
    if (iVar12 < 0x100) {
      local_3c = iVar12 * local_3c >> 8;
      param_3 = ((int)((param_3 & 0x1f) * iVar12) >> 8 & 0x1fU) +
                ((int)((param_3 & 0xf800) * iVar12) >> 8 & 0xf800U) +
                ((int)((param_3 & 0x7e0) * iVar12) >> 8 & 0x7e0U);
    }
    if ((param_3 == (0x1f << (bVar9 & 0x1f) | 0x3f << (bVar10 & 0x1f) | 0x1f << (bVar11 & 0x1f))) ||
       (local_3c == 0x100)) {
      local_3c = 0;
      fVar14 = GHIDRA_I2F(param_2[2]);
    }
    else {
      if (param_3 != 0) {
        W_RotateShadowTransSub_P
                  (piVar2,iVar8,(float10)iVar3,(float10)(int)GHIDRA_FIST32(fVar6),0.0,fVar7,fVar5,1.0,
                   GHIDRA_I2F(param_2[2]),param_3);
      }
      if (local_3c < 1) {
        return;
      }
      local_3c = 0x100 - local_3c;
      fVar14 = GHIDRA_I2F(param_2[2]);
    }
    W_RotateSpriteTransAdd_B_P
              (piVar2,iVar8,(float10)iVar3,(float10)(int)GHIDRA_FIST32(fVar6),0.0,fVar7,fVar5,1.0,fVar14,0,
               local_3c);
  }
  return;
}

/* ProjArrayClsnDraw @ 0x080b9ea0, 51 bytes */
void ProjArrayClsnDraw(int *param_1,float param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *param_1;
  iVar2 = ArrayScanFirst(iVar1);
  while (iVar2 != 0) {
    ProjClsnDraw(iVar2,param_2);
    iVar2 = ArrayScanNext(iVar1);
  }
  return;
}

/* ProjClsnDraw @ 0x080b9ee0, 229 bytes
 * FIXUP: 5 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void ProjClsnDraw(int param_1,float param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float10 fVar4;
  float10 fVar5;
  float10 fVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  iVar1 = g[0x7311];
  fVar4 = *(float *)(param_1 + 0x44);
  uVar9 = (uint)(*(int *)(param_1 + 0x34) != 1);
  iVar2 = g[0x7312];
  iVar3 = g[0x4140];
  fVar5 = *(float *)(param_1 + 0x48);
  fVar6 = *(float *)(param_1 + 0x4c);
  uVar7 = (uint)(g[0x81d0] == 2);
  uVar8 = makecol(0xff,0,0);
  GameClsnDraw(*(int *)(*(int *)(param_1 + 0x294) + 0x28),
               (float10)(int)GHIDRA_FIST32(fVar4 - (float10)iVar1) * param_2,
               (float10)(int)GHIDRA_FIST32((fVar5 - (float10)iVar2) + fVar6 + (float10)iVar3) * param_2,param_2,
               param_2,uVar8,uVar9,uVar7);
  return;
}

