/*
 * explod.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0808dc30-0x0808fdbf, 32 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"

extern int id_0 __asm__("D_08287a6c"); /* file-static 0x08287a6c */

/* ExplodArrayNew @ 0x0808dc30, 127 bytes */
int * ExplodArrayNew(size_t param_1,undefined4 param_2)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  
  piVar1 = (int *)ecalloc(1,0xc);
  if (piVar1 != (int *)0x0) {
    piVar1[1] = param_1;
    iVar2 = ecalloc(param_1,0xe4);
    *piVar1 = iVar2;
    if (iVar2 != 0) {
      iVar2 = 0;
      if ((int)param_1 < 1) {
        return piVar1;
      }
      iVar4 = 0;
      while( true ) {
        puVar3 = AnimNew(0,0);
        *(undefined4 **)(*piVar1 + 0x80 + iVar4) = puVar3;
        if (puVar3 == (undefined4 *)0x0) break;
        iVar2 = iVar2 + 1;
        iVar4 = iVar4 + 0xe4;
        puVar3[0xc] = param_2;
        if ((int)param_1 <= iVar2) {
          return piVar1;
        }
      }
    }
  }
  return (int *)0x0;
}

/* ExplodArrayFree @ 0x0808dcb0, 101 bytes */
void ExplodArrayFree(int *param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 == (int *)0x0) {
    return;
  }
  iVar1 = *param_1;
  if (iVar1 != 0) {
    iVar2 = 0;
    if (0 < param_1[1]) {
      while( true ) {
        AnimFree(*(void **)(iVar1 + 0x80 + iVar2 * 0xe4));
        if (param_1[1] <= iVar2 + 1) break;
        iVar1 = *param_1;
        iVar2 = iVar2 + 1;
      }
    }
    free((void *)*param_1);
  }
  free(param_1);
  return;
}

/* ExplodArrayUpdate @ 0x0808dd20, 38 bytes */
void ExplodArrayUpdate(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  if (0 < param_1[1]) {
    do {
      iVar2 = iVar1 + 1;
      ExplodUpdate(param_1,iVar1);
      iVar1 = iVar2;
    } while (iVar2 < param_1[1]);
  }
  return;
}

/* ExplodUpdate @ 0x0808dd50, 374 bytes
 * FIXUP: 4 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
int * ExplodUpdate(int *param_1,int param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  
  piVar3 = (int *)*param_1;
  piVar1 = piVar3 + param_2 * 0x39;
  if ((*piVar1 != 0) &&
     (((g[0x74f3] == -1 || (piVar1[0xf] <= piVar1[g[0x74f3] + 0xd])) ||
      (piVar3 = (int *)(piVar1[g[0x74f3] + 0xd] + 1), piVar3 == (int *)0x0)))) {
    if ((((piVar1[3] != 0) && (piVar1[0x1f] == 0)) &&
        (iVar4 = PlayerAccessID(piVar1[3]), iVar4 != 0)) && (0 < *(int *)(iVar4 + 0xe18))) {
      return (int *)*(int *)(iVar4 + 0xe18);
    }
    piVar3 = (int *)piVar1[0xf];
    if (((int)piVar3 < piVar1[0x10]) || (piVar1[0x10] == -1)) {
      if (piVar1[1] == 1) {
        AnimUpdate((undefined4 *)piVar1[0x20]);
        piVar3 = (int *)piVar1[0xf];
      }
      if (0 < (int)piVar3) {
        piVar1[5] = GHIDRA_F2I(int, (GHIDRA_I2F(piVar1[5]) + GHIDRA_I2F(piVar1[7])));
        piVar1[7] = GHIDRA_F2I(int, (GHIDRA_I2F(piVar1[7]) + GHIDRA_I2F(piVar1[9])));
        piVar1[6] = GHIDRA_F2I(int, (GHIDRA_I2F(piVar1[6]) + GHIDRA_I2F(piVar1[8])));
        piVar1[8] = GHIDRA_F2I(int, (GHIDRA_I2F(piVar1[8]) + GHIDRA_I2F(piVar1[10])));
      }
      piVar3 = (int *)0x0;
      if (piVar1[0x18] != 0) {
        if ((float *)piVar1[0x13] != (float *)0x0) {
          piVar1[5] = GHIDRA_F2I(int, ((float10)piVar1[0xb] + *(float *)piVar1[0x13]));
        }
        if ((float *)piVar1[0x14] != (float *)0x0) {
          piVar1[6] = GHIDRA_F2I(int, ((float10)piVar1[0xc] + *(float *)piVar1[0x14]));
        }
        if ((int *)piVar1[0x15] != (int *)0x0) {
          piVar1[5] = GHIDRA_F2I(int, (float)(piVar1[0xb] + *(int *)piVar1[0x15]));
        }
        if ((int *)piVar1[0x16] != (int *)0x0) {
          piVar1[6] = GHIDRA_F2I(int, (float)(piVar1[0xc] + *(int *)piVar1[0x16]));
        }
        piVar3 = (int *)piVar1[0x18];
        if (0 < (int)piVar3) {
          piVar3 = (int *)((int)piVar3 + -1);
          piVar1[0x18] = (int)piVar3;
          piVar2 = g;
          if ((piVar3 == (int *)0x0) &&
             (piVar3 = (int *)piVar1[0x1b], (int *)piVar1[0x1b] == (int *)0x0)) {
            piVar1[0x1b] = 1;
            piVar1[5] = GHIDRA_F2I(int, ((float10)piVar2[0x7311] + GHIDRA_I2F(piVar1[5])));
            piVar1[6] = GHIDRA_F2I(int, ((float10)piVar2[0x7312] + GHIDRA_I2F(piVar1[6])));
            piVar3 = piVar2;
          }
        }
      }
      piVar1[0xf] = piVar1[0xf] + 1;
    }
    else {
      *piVar1 = 0;
      param_1[2] = param_1[2] + -1;
    }
  }
  return piVar3;
}

/* ExplodArrayDraw @ 0x0808ded0, 103 bytes */
void ExplodArrayDraw(int *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = 0;
  iVar4 = 0;
  iVar2 = param_1[1];
  if ((0 < iVar2) && (piVar1 = (int *)*param_1, (uint)param_1[2] < 0x80000000)) {
    iVar5 = 0;
    do {
      if (*piVar1 != 0) {
        iVar4 = iVar4 + 1;
        if (((piVar1[0x19] == param_2) || (param_2 == -1)) && (piVar1[2] == 0)) {
          ExplodDraw((int)piVar1);
          iVar2 = param_1[1];
        }
      }
      iVar3 = iVar3 + 1;
      iVar5 = iVar5 + 0xe4;
    } while ((iVar3 < iVar2) && (piVar1 = (int *)(iVar5 + *param_1), iVar4 <= param_1[2]));
  }
  return;
}

/* ExplodDraw @ 0x0808df40, 716 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: 2 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void ExplodDraw(int param_1)

{
  float10 fVar1;
  float10 fVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  bool bVar11;
  undefined3 extraout_var;
  float local_3c;
  float local_38;
  
  iVar10 = W_y1;
  iVar9 = W_x2;
  iVar8 = W_x1;
  iVar7 = W_y2;
  local_38 = *(float *)(param_1 + 0x44);
  local_3c = *(float *)(param_1 + 0x48);
  if (*(int *)(param_1 + 0x6c) == 0) {
    fVar1 = *(float *)(param_1 + 0x14);
    fVar2 = *(float *)(param_1 + 0x18);
  }
  else {
    fVar1 = *(float *)(param_1 + 0x14) - (float)g[0x7311];
    fVar2 = *(float *)(param_1 + 0x18) - (float)g[0x7312];
  }
  if (*(int *)(param_1 + 0x70) != 0) {
    fVar1 = fVar1 - (float)g[0x7315];
    fVar2 = fVar2 - (float)g[0x7316];
  }
  if (((g[0x7559] == 4) && (bVar11 = GameModeInFightScreen(), GHIDRA_ZEXT8(bVar11) != 0))
     && ((*(int *)(param_1 + 4) != 1 || (*(int *)(*(int *)(param_1 + 0x80) + 0x30) == 0)))) {
    fVar1 = fVar1 + fVar1;
    local_38 = local_38 + local_38;
    fVar2 = fVar2 + fVar2;
    local_3c = local_3c + local_3c;
  }
  if (*(uint *)(param_1 + 0xe0) != 0xffffffff) {
    W_Define(*(uint *)(param_1 + 0xd4),*(uint *)(param_1 + 0xdc),*(uint *)(param_1 + 0xd8),
             *(uint *)(param_1 + 0xe0));
  }
  iVar3 = *(int *)(param_1 + 0x80);
  uVar4 = *(undefined4 *)(iVar3 + 0x20);
  *(undefined4 *)(iVar3 + 0x20) = *(undefined4 *)(param_1 + 0x84);
  uVar5 = *(undefined4 *)(iVar3 + 0x24);
  *(undefined4 *)(iVar3 + 0x24) = *(undefined4 *)(param_1 + 0x88);
  uVar6 = *(undefined4 *)(iVar3 + 0x28);
  *(undefined4 *)(iVar3 + 0x28) = *(undefined4 *)(param_1 + 0x8c);
  iVar3 = *(int *)(param_1 + 4);
  if (iVar3 == 2) {
    if ((*(uint *)(param_1 + 0x68) & 1) != 0) {
      local_38 = local_38 * -1.0;
    }
    if ((*(uint *)(param_1 + 0x68) & 2) != 0) {
      local_3c = local_3c * -1.0;
    }
    W_ScaleSprite_S(*(int **)(param_1 + 0x90),*(int *)(param_1 + 0x94),fVar1,fVar2,local_38,local_3c
                   );
  }
  else if (iVar3 < 3) {
    if (iVar3 == 1) {
      AnimDrawScaleFlip(*(undefined4 **)(param_1 + 0x80),(int)GHIDRA_FIST32(fVar1),(int)GHIDRA_FIST32(fVar2),
                        local_38,local_3c,*(uint *)(param_1 + 0x68));
    }
  }
  else if (iVar3 == 3) {
    V_FontDrawAlignBank((char *)(param_1 + 0xa4),*(int **)(param_1 + 0x98),(int)GHIDRA_FIST32(fVar1),
                        (int)GHIDRA_FIST32(fVar2),*(int *)(param_1 + 0xa0),*(int *)(param_1 + 0x9c));
  }
  iVar3 = *(int *)(param_1 + 0x80);
  *(undefined4 *)(iVar3 + 0x20) = uVar4;
  *(undefined4 *)(iVar3 + 0x24) = uVar5;
  *(undefined4 *)(iVar3 + 0x28) = uVar6;
  if (*(int *)(param_1 + 0xe0) != -1) {
    W_Define(iVar8,iVar10,iVar9,iVar7);
  }
  return;
}

/* ExplodArrayDrawShadow @ 0x0808e210, 145 bytes */
void ExplodArrayDrawShadow(int *param_1)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int local_14;
  
  iVar5 = 0;
  local_14 = 0;
  iVar2 = param_1[1];
  if ((0 < iVar2) && (piVar3 = (int *)*param_1, (uint)param_1[2] < 0x80000000)) {
    iVar4 = 0;
    do {
      if (*piVar3 != 0) {
        uVar1 = piVar3[0x1d];
        iVar5 = iVar5 + 1;
        if (uVar1 != 0) {
          if (uVar1 == 0xffffffff) {
            uVar1 = g[0x10a5];
          }
          ExplodDrawShadow((int)piVar3,g + 0x10a4,uVar1,g + 0x10a9);
          iVar2 = param_1[1];
        }
      }
      iVar4 = iVar4 + 0xe4;
      local_14 = local_14 + 1;
    } while ((local_14 < iVar2) && (piVar3 = (int *)(iVar4 + *param_1), iVar5 <= param_1[2]));
  }
  return;
}

/* ExplodDrawShadow @ 0x0808e2b0, 1422 bytes
 * REVIEW: calls-missing-in-pid:NAN
 * FIXUP: 14 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 4 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void ExplodDrawShadow(int param_1,int *param_2,uint param_3,int *param_4)

{
  float10 fVar1;
  float10 fVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  float10 fVar6;
  int iVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  float10 fVar14;
  int local_3c;
  
  piVar3 = *(int **)(param_1 + 0x90);
  iVar4 = *(int *)(*(int *)(param_1 + 0x80) + 0x10);
  uVar13 = *(uint *)(param_1 + 0x68);
  bVar8 = (byte)_rgb_r_shift_16;
  bVar9 = (byte)_rgb_g_shift_16;
  bVar10 = (byte)_rgb_b_shift_16;
  local_3c = *param_2;
  if ((g[0x7570] != 0) && (iVar7 = AnimCurSpriteIdx(*(int *)(param_1 + 0x80)), iVar7 != -1)) {
    fVar1 = *(float *)(param_1 + 0x44);
    fVar2 = *(float *)(param_1 + 0x48);
    fVar6 = (float10)*(int *)(iVar4 + 0x14);
    if (*(int *)(param_1 + 0x6c) == 0) {
      fVar14 = *(float *)(param_1 + 0x14);
    }
    else {
      fVar14 = *(float *)(param_1 + 0x14) - (float)g[0x7311];
    }
    fVar14 = (fVar14 - (float)g[0x7315]) +
             (float10)(int)((uint)((uVar13 & 1) == 0) * 2 + -1) *
             (float10)*(int *)(iVar4 + 0x10) * fVar1;
    uVar13 = uVar13 ^ *(uint *)(iVar4 + 0x18) & 3;
    if ((uVar13 & 1) != 0) {
      fVar1 = fVar1 * -1.0;
    }
    if ((uVar13 & 2) == 0) {
      fVar2 = fVar2 * -1.0;
    }
    if (g[0x7559] == 4) {
      fVar14 = fVar14 + fVar14;
      fVar1 = fVar1 + fVar1;
    }
    iVar4 = (int)GHIDRA_FIST32(fVar14);
    if (0 < *param_4) {
      if (*(int *)(param_1 + 0x6c) == 0) {
        iVar11 = g[0x7316];
        fVar14 = (float)g[0x4140] - ((*(float *)(param_1 + 0x18) - (float)g[0x4140]) + fVar6);
      }
      else {
        fVar14 = ((float)g[0x4140] - ((*(float *)(param_1 + 0x18) - (float)g[0x4140]) + fVar6)) -
                 (float)g[0x7312];
        iVar11 = g[0x7316];
      }
      fVar14 = fVar14 - (float10)iVar11;
      if (g[0x7559] == 4) {
        fVar14 = fVar14 + fVar14;
      }
      iVar11 = *param_4;
      iVar12 = 0x100 - iVar11;
      if (*(int *)(param_1 + 0x84) == 3) {
        iVar11 = iVar11 * *(int *)(param_1 + 0x88) >> 8;
        iVar12 = iVar12 + ((0x100 - iVar12) * *(int *)(param_1 + 0x8c) >> 8);
      }
      W_RotateSpriteTransAdd_B
                (piVar3,iVar7,(float10)iVar4,(float10)(int)GHIDRA_FIST32(fVar14),0.0,fVar1,fVar2,iVar11,iVar12);
    }
    fVar2 = *(float *)(param_1 + 0x48);
    if (*(int *)(param_1 + 0x6c) == 0) {
      fVar6 = (((float)g[0x4140] -
               (((*(float *)(param_1 + 0x18) + (float)g[0x7312]) - (float)g[0x4140]) + fVar6) *
               fVar2 * GHIDRA_I2F(param_2[2])) - (float)g[0x7316]) - (float)g[0x7312];
    }
    else {
      fVar6 = (((float)g[0x4140] -
               ((*(float *)(param_1 + 0x18) - (float)g[0x4140]) + fVar6) * fVar2 * GHIDRA_I2F(param_2[2])
               ) - (float)g[0x7312]) - (float)g[0x7316];
    }
    if ((uVar13 & 2) == 0) {
      fVar2 = fVar2 * -1.0;
    }
    if (g[0x7559] == 4) {
      fVar6 = fVar6 + fVar6;
      fVar2 = fVar2 + fVar2;
    }
    iVar11 = 0x100;
    if (*(int *)(param_1 + 0x84) == 3) {
      iVar11 = 0x100 - *(int *)(param_1 + 0x8c);
    }
    iVar12 = param_2[3];
    iVar5 = param_2[4];
    if (iVar12 < iVar5) {
      if ((float10)iVar12 < *(float *)(param_1 + 0x18) - (float)g[0x4140]) {
        fVar14 = *(float *)(param_1 + 0x18) - (float)g[0x4140];
        if (fVar14 < (float10)iVar5) {
          iVar11 = (int)GHIDRA_FIST32(((float10)iVar11 * (fVar14 - (float10)iVar12)) / (float)(iVar5 - iVar12));
        }
      }
      else {
        iVar11 = 0;
      }
    }
    if (iVar11 < 0x100) {
      param_3 = ((int)((param_3 & 0x1f) * iVar11) >> 8 & 0x1fU) +
                ((int)((param_3 & 0xf800) * iVar11) >> 8 & 0xf800U) +
                ((int)((param_3 & 0x7e0) * iVar11) >> 8 & 0x7e0U);
      local_3c = iVar11 * local_3c >> 8;
    }
    if ((param_3 == (0x1f << (bVar8 & 0x1f) | 0x3f << (bVar9 & 0x1f) | 0x1f << (bVar10 & 0x1f))) ||
       (local_3c == 0x100)) {
      local_3c = 0;
      fVar14 = GHIDRA_I2F(param_2[2]);
    }
    else {
      if (param_3 != 0) {
        W_RotateShadowTransSub_P
                  (piVar3,iVar7,(float10)iVar4,(float10)(int)GHIDRA_FIST32(fVar6),0.0,fVar1,fVar2,1.0,
                   GHIDRA_I2F(param_2[2]),param_3);
      }
      if (local_3c < 1) {
        return;
      }
      local_3c = 0x100 - local_3c;
      fVar14 = GHIDRA_I2F(param_2[2]);
    }
    W_RotateSpriteTransAdd_B_P
              (piVar3,iVar7,(float10)iVar4,(float10)(int)GHIDRA_FIST32(fVar6),0.0,fVar1,fVar2,1.0,fVar14,0,
               local_3c);
  }
  return;
}

/* ExplodArrayReset @ 0x0808e840, 41 bytes */
void ExplodArrayReset(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < (int)param_1[1]) {
    puVar1 = (undefined4 *)*param_1;
    do {
      *puVar1 = 0;
      puVar1 = puVar1 + 0x39;
      iVar2 = iVar2 + 1;
    } while (iVar2 < (int)param_1[1]);
  }
  param_1[2] = 0;
  return;
}

/* ExplodDefault @ 0x0808e870, 287 bytes */
void ExplodDefault(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar1 = (undefined4 *)param_1[0x20];
  puVar3 = param_1;
  for (iVar2 = 0x39; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  *puVar1 = 0;
  param_1[0x25] = 0xffffffff;
  *param_1 = 1;
  param_1[0x20] = puVar1;
  param_1[0xe] = 0;
  param_1[0xd] = 0;
  param_1[0xf] = 0;
  param_1[0x10] = 0;
  param_1[0xc] = 0;
  param_1[0xb] = 0;
  param_1[0x1a] = 0;
  param_1[0x18] = 0;
  param_1[10] = 0;
  param_1[9] = 0;
  param_1[8] = 0;
  param_1[7] = 0;
  param_1[6] = 0;
  param_1[5] = 0;
  param_1[0x12] = 0x3f800000;
  param_1[0x11] = 0x3f800000;
  param_1[0x14] = 0;
  param_1[0x13] = 0;
  param_1[0x16] = 0;
  param_1[0x15] = 0;
  puVar1[0xc] = 0;
  puVar1[0xd] = 0;
  puVar1[1] = 0;
  param_1[0x21] = 0xffffffff;
  param_1[0x22] = 0x100;
  param_1[0x23] = 0;
  param_1[0x38] = 0xffffffff;
  param_1[0x36] = 0xffffffff;
  param_1[0x37] = 0xffffffff;
  param_1[0x35] = 0xffffffff;
  return;
}

/* ExplodMakeFromInfo @ 0x0808e990, 215 bytes
 * FIXUP: 1 data addresses written as literals replaced by data-image references */
void ExplodMakeFromInfo(int *param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int *piVar4;
  
  iVar1 = EvalExpressionI((int)param_1,param_2 + 0xc,1);
  if (iVar1 < 0) {
    iVar1 = 0;
    Warn((int)param_1,(int)&DAT_0827851f);
  }
  if (*(int *)(param_2 + 0x18) == 0) {
    iVar2 = EvalExpressionI((int)param_1,param_2 + 0x128,1);
    if (iVar2 == 0) {
      iVar2 = param_1[0x4eb];
    }
    else {
      iVar2 = param_1[0x4ed];
    }
    piVar4 = *(int **)(*param_1 + 0x11cc);
    puVar3 = (undefined4 *)g[0x52be];
  }
  else {
    iVar2 = g[0x4147];
    piVar4 = (int *)g[0x4148];
    puVar3 = (undefined4 *)g[0x52be];
  }
  iVar1 = ExplodAdd(puVar3,iVar1,piVar4,iVar2);
  if (iVar1 != -1) {
    ExplodSetParams(param_1,*(int *)g[0x52be] + iVar1 * 0xe4,param_2,param_3,0);
  }
  return;
}

/* ExplodModifyFromInfo @ 0x0808ea70, 146 bytes */
void ExplodModifyFromInfo(int *param_1,int param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  piVar1 = (int *)g[0x52be];
  iVar3 = EvalExpressionI((int)param_1,param_2,1);
  iVar6 = 0;
  iVar5 = piVar1[1];
  iVar2 = param_1[1];
  if (0 < iVar5) {
    iVar7 = 0;
    do {
      piVar4 = (int *)(iVar7 + *piVar1);
      if ((*piVar4 != 0) && (((piVar4[4] == iVar3 || (iVar3 == -1)) && (piVar4[3] == iVar2)))) {
        ExplodSetParams(param_1,(int)piVar4,param_2,param_3,1);
        iVar5 = piVar1[1];
      }
      iVar6 = iVar6 + 1;
      iVar7 = iVar7 + 0xe4;
    } while (iVar6 < iVar5);
  }
  return;
}

/* ExplodSetParams @ 0x0808eb10, 2020 bytes
 * REVIEW: pid-unaff_; calls-missing-in-pid:NAN
 * FIXUP: 8 data addresses written as literals replaced by data-image references
 * FIXUP: 2 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void ExplodSetParams(int *param_1,int param_2,int param_3,int *param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  long lVar4;
  int iVar5;
  int unaff_EDI;
  float10 fVar6;
  int local_20;
  uint local_1c;
  
  piVar3 = (int *)*param_4;
  if (param_5 == 0) {
    iVar2 = EvalExpressionI((int)param_1,param_3,1);
    *(int *)(param_2 + 0x10) = iVar2;
    if (iVar2 < 0) {
      *(undefined4 *)(param_2 + 0x10) = 0;
      Warn((int)param_1,(int)&DAT_08278535);
    }
    *(int *)(param_2 + 0xc) = param_1[1];
  }
  if (*(int *)(param_3 + 0xc4) == -0x7fef) goto LAB_0808ef0b;
  *(undefined4 *)(param_2 + 0x6c) = 1;
  *(undefined4 *)(param_2 + 0x70) = 1;
  iVar2 = *(int *)(param_3 + 0xc4);
  if (iVar2 < 5) {
    if (iVar2 < 1) {
      if (iVar2 != 0) goto LAB_0808ed24;
      local_20 = 0;
      local_1c = 0;
      *(int **)(param_2 + 0x4c) = param_1 + 0x4d5;
      unaff_EDI = param_1[100];
      *(int **)(param_2 + 0x50) = param_1 + 0x4d6;
      *(undefined4 *)(param_2 + 0x6c) = 0;
      iVar2 = *(int *)(param_3 + 0xc4);
    }
    else if ((((iVar2 == 2) && (param_1[100] == 1)) || ((iVar2 == 1 && (param_1[100] == -1)))) ||
            (iVar2 == 3)) {
      unaff_EDI = 1;
      piVar3 = g + 0x7312;
      *(int **)(param_2 + 0x54) = g + 0x7311;
      *(int **)(param_2 + 0x58) = piVar3;
      local_20 = 0;
      local_1c = 0;
      iVar2 = *(int *)(param_3 + 0xc4);
    }
    else {
      piVar3 = g + 0x7311;
      *(int **)(param_2 + 0x58) = g + 0x7312;
      *(int **)(param_2 + 0x54) = piVar3;
      local_1c = 0x140;
      local_20 = 0;
      unaff_EDI = (uint)(iVar2 != 2) * 2 + -1;
    }
  }
  else if (iVar2 == 5) {
    if (piVar3 == (int *)0x0) {
      local_1c = (uint)GHIDRA_FIST32(GHIDRA_I2F(param_1[0x4d5]));
      local_20 = (int)GHIDRA_FIST32(GHIDRA_I2F(param_1[0x4d6]));
      *(int **)(param_2 + 0x4c) = param_1 + 0x4d5;
      unaff_EDI = param_1[100];
      piVar3 = param_1;
    }
    else {
      local_20 = 0;
      local_1c = 0;
      *(int **)(param_2 + 0x4c) = piVar3 + 0x4d5;
      unaff_EDI = piVar3[100];
    }
    *(int **)(param_2 + 0x50) = piVar3 + 0x4d6;
    *(undefined4 *)(param_2 + 0x6c) = 0;
    iVar2 = *(int *)(param_3 + 0xc4);
  }
  else {
LAB_0808ed24:
    local_20 = 0;
    local_1c = 0;
  }
  *(int *)(param_2 + 0x5c) = iVar2;
  iVar2 = EvalExpressionI((int)param_1,param_3 + 0xec,1);
  if ((iVar2 != 1) && (iVar2 != -1)) {
    iVar2 = 1;
    Warn((int)param_1,(int)&DAT_08278600);
  }
  if (iVar2 * unaff_EDI == -1) {
    *(uint *)(param_2 + 0x68) = *(uint *)(param_2 + 0x68) | 1;
  }
  iVar2 = EvalExpressionI((int)param_1,param_3 + 0xf8,1);
  if ((iVar2 != 1) && (iVar2 != -1)) {
    iVar2 = 1;
    Warn((int)param_1,(int)&DAT_08278640);
  }
  if (iVar2 == -1) {
    *(uint *)(param_2 + 0x68) = *(uint *)(param_2 + 0x68) | 2;
  }
  iVar2 = EvalExpressionI((int)param_1,param_3 + 0x1c,1);
  *(uint *)(param_2 + 0x2c) = iVar2 * unaff_EDI + local_1c;
  iVar2 = EvalExpressionI((int)param_1,param_3 + 0x28,1);
  *(int *)(param_2 + 0x30) = iVar2 + local_20;
  iVar2 = EvalExpressionI((int)param_1,param_3 + 100,1);
  if (iVar2 < 0) {
    iVar2 = 0;
    Warn((int)param_1,(int)&DAT_08278548);
  }
  lVar4 = random();
  *(int *)(param_2 + 0x2c) = *(int *)(param_2 + 0x2c) + (lVar4 % (iVar2 + 1) - (iVar2 + 1 >> 1));
  iVar2 = EvalExpressionI((int)param_1,param_3 + 0x70,1);
  if (iVar2 < 0) {
    iVar2 = 0;
    Warn((int)param_1,(int)&DAT_08278548);
  }
  lVar4 = random();
  *(float *)(param_2 + 0x14) = (float10)*(int *)(param_2 + 0x2c);
  iVar2 = (lVar4 % (iVar2 + 1) - (iVar2 + 1 >> 1)) + *(int *)(param_2 + 0x30);
  *(int *)(param_2 + 0x30) = iVar2;
  *(float *)(param_2 + 0x18) = (float10)iVar2;
  fVar6 = EvalExpressionF(param_1,(int *)(param_3 + 0x34));
  *(float *)(param_2 + 0x1c) = fVar6 * (float)unaff_EDI;
  fVar6 = EvalExpressionF(param_1,(int *)(param_3 + 0x40));
  *(float *)(param_2 + 0x20) = fVar6;
  fVar6 = EvalExpressionF(param_1,(int *)(param_3 + 0x4c));
  *(float *)(param_2 + 0x24) = fVar6 * (float)unaff_EDI;
  fVar6 = EvalExpressionF(param_1,(int *)(param_3 + 0x58));
  *(float *)(param_2 + 0x28) = fVar6;
  if ((param_5 != 0) && (*(int *)(param_2 + 0x60) == 0)) {
    *(undefined4 *)(param_2 + 0x60) = 1;
  }
LAB_0808ef0b:
  fVar6 = EvalExpressionF(param_1,(int *)(param_3 + 0xac));
  if (fVar6 != -32760.0) {
    *(float *)(param_2 + 0x44) = fVar6;
  }
  fVar6 = EvalExpressionF(param_1,(int *)(param_3 + 0xb8));
  if (fVar6 != -32760.0) {
    *(float *)(param_2 + 0x48) = fVar6;
  }
  iVar2 = EvalExpressionI((int)param_1,param_3 + 200,1);
  if (iVar2 != -0x7fef) {
    if (iVar2 < -1) {
      iVar2 = -1;
      Warn((int)param_1,(int)&DAT_08278680);
    }
    *(int *)(param_2 + 0x60) = iVar2;
  }
  iVar2 = EvalExpressionI((int)param_1,param_3 + 0xe0,1);
  if (iVar2 != -0x7fef) {
    *(uint *)(param_2 + 100) = (uint)(iVar2 != 0) * 2;
  }
  iVar2 = EvalExpressionI((int)param_1,param_3 + 0xa0,1);
  if (iVar2 != -0x7fef) {
    if (iVar2 < -2) {
      iVar2 = -2;
      Warn((int)param_1,(int)&DAT_08278565);
    }
    if (iVar2 == -2) {
      iVar2 = AnimGetLooptime(*(undefined4 **)(param_2 + 0x80));
      *(int *)(param_2 + 0x40) = iVar2 - *(int *)(param_2 + 0x3c);
    }
    else {
      *(int *)(param_2 + 0x40) = iVar2;
    }
  }
  iVar2 = EvalExpressionI((int)param_1,param_3 + 0x88,1);
  if ((((iVar2 == 0) || (iVar2 == -0x7fef)) &&
      (iVar5 = EvalExpressionI((int)param_1,param_3 + 0x7c,1), iVar5 != -0x7fef)) && (iVar5 != 0)) {
    iVar2 = -2;
  }
  if (iVar2 != -0x7fef) {
    if (iVar2 == -2) {
      iVar2 = *(int *)(param_2 + 0x40);
    }
    *(int *)(param_2 + 0x38) = iVar2;
  }
  iVar2 = EvalExpressionI((int)param_1,param_3 + 0x94,1);
  if (iVar2 != -0x7fef) {
    if (iVar2 == -2) {
      iVar2 = *(int *)(param_2 + 0x40);
    }
    *(int *)(param_2 + 0x34) = iVar2;
  }
  if (*(int *)(param_2 + 100) == 0) {
    iVar2 = EvalExpressionI((int)param_1,param_3 + 0xd4,1);
    if (iVar2 != -0x7fef) {
      iVar5 = *(int *)(param_2 + 0x80);
      iVar1 = g[0x413d];
      *(int *)(iVar5 + 0x34) = iVar2;
      *(int *)(iVar5 + 0x30) = iVar1;
    }
  }
  else {
    *(undefined4 *)(*(int *)(param_2 + 0x80) + 0x30) = 0;
  }
  local_1c = EvalExpressionI((int)param_1,param_3 + 0x104,1);
  if (local_1c != 0xffff8011) {
    iVar2 = EvalExpressionI((int)param_1,param_3 + 0x110,1);
    iVar5 = EvalExpressionI((int)param_1,param_3 + 0x11c,1);
    if (((((int)local_1c < -1) || (iVar2 < -1)) ||
        ((iVar5 < -1 || ((0xff < (int)local_1c || (0xff < iVar2)))))) || (0xff < iVar5)) {
      local_1c = 0xffffffff;
      Warn((int)param_1,(int)&DAT_08278583);
    }
    if (local_1c != 0xffffffff) {
      local_1c = ((int)local_1c >> 3) << ((byte)_rgb_r_shift_16 & 0x1f) |
                 (iVar2 >> 2) << ((byte)_rgb_g_shift_16 & 0x1f) |
                 (iVar5 >> 3) << ((byte)_rgb_b_shift_16 & 0x1f);
    }
    *(uint *)(param_2 + 0x74) = local_1c;
  }
  iVar2 = EvalExpressionI((int)param_1,param_3 + 0x134,1);
  if (iVar2 != -0x7fef) {
    *(int *)(param_2 + 0x78) = iVar2;
  }
  iVar2 = EvalExpressionI((int)param_1,param_3 + 0x140,1);
  if (iVar2 != -0x7fef) {
    *(int *)(param_2 + 0x7c) = iVar2;
  }
  if (*(int *)(param_3 + 0x14c) != -0x7fef) {
    *(int *)(param_2 + 0x84) = *(int *)(param_3 + 0x14c);
  }
  iVar2 = EvalExpressionI((int)param_1,param_3 + 0x150,1);
  if (iVar2 != -0x7fef) {
    *(int *)(param_2 + 0x88) = iVar2;
  }
  iVar2 = *(int *)(param_2 + 0x88);
  if (iVar2 < 0) {
    *(undefined4 *)(param_2 + 0x88) = 0;
    iVar2 = 0;
  }
  if (0x100 < iVar2) {
    *(undefined4 *)(param_2 + 0x88) = 0x100;
  }
  iVar2 = EvalExpressionI((int)param_1,param_3 + 0x15c,1);
  if (iVar2 != -0x7fef) {
    *(int *)(param_2 + 0x8c) = iVar2;
  }
  iVar2 = *(int *)(param_2 + 0x8c);
  if (iVar2 < 0) {
    *(undefined4 *)(param_2 + 0x8c) = 0;
    iVar2 = 0;
  }
  if (0x100 < iVar2) {
    *(undefined4 *)(param_2 + 0x8c) = 0x100;
  }
  return;
}

/* ExplodAdd @ 0x0808f300, 182 bytes */
int ExplodAdd(undefined4 *param_1,int param_2,int *param_3,int param_4)

{
  undefined4 *puVar1;
  uint uVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  
  uVar2 = ArrayFind(*param_3,0,param_2);
  if (uVar2 != 0xffffffff) {
    iVar5 = 0;
    if (0 < (int)param_1[1]) {
      piVar3 = (int *)*param_1;
      piVar4 = piVar3;
      do {
        if (*piVar3 == 0) {
          ExplodDefault(piVar4);
          puVar1 = (undefined4 *)piVar4[0x20];
          piVar4[1] = 1;
          puVar1[1] = param_4;
          *puVar1 = param_3;
          piVar4[0x24] = param_4;
          AnimChangeAction((int *)piVar4[0x20],0,param_2);
          AnimResetAction((int *)piVar4[0x20]);
          param_1[2] = param_1[2] + 1;
          return iVar5;
        }
        iVar5 = iVar5 + 1;
        piVar3 = piVar3 + 0x39;
        piVar4 = piVar4 + 0x39;
      } while (iVar5 < (int)param_1[1]);
    }
  }
  return -1;
}

/* ExplodAddSprite @ 0x0808f3c0, 145 bytes */
int ExplodAddSprite(undefined4 *param_1,int param_2,int param_3,int *param_4)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  
  iVar1 = SpriteArrayGetNum(param_4,param_2,param_3);
  if (iVar1 != -1) {
    iVar4 = 0;
    if (0 < (int)param_1[1]) {
      piVar2 = (int *)*param_1;
      piVar3 = piVar2;
      do {
        if (*piVar2 == 0) {
          ExplodDefault(piVar3);
          piVar3[1] = 2;
          piVar3[0x25] = iVar1;
          piVar3[0x24] = (int)param_4;
          param_1[2] = param_1[2] + 1;
          return iVar4;
        }
        iVar4 = iVar4 + 1;
        piVar2 = piVar2 + 0x39;
        piVar3 = piVar3 + 0x39;
      } while (iVar4 < (int)param_1[1]);
    }
  }
  return -1;
}

/* ExplodAddText @ 0x0808f460, 142 bytes */
int ExplodAddText(int *param_1,char *param_2,int param_3,int param_4,int param_5)

{
  int *piVar1;
  int *__dest;
  int iVar2;
  
  iVar2 = 0;
  if (0 < param_1[1]) {
    piVar1 = (int *)*param_1;
    __dest = piVar1 + 0x29;
    do {
      if (*piVar1 == 0) {
        ExplodDefault(piVar1);
        piVar1[1] = 3;
        piVar1[0x26] = param_3;
        piVar1[0x27] = param_4;
        piVar1[0x28] = param_5;
        strncpy((char *)__dest,param_2,0x2f);
        param_1[2] = param_1[2] + 1;
        return iVar2;
      }
      iVar2 = iVar2 + 1;
      __dest = __dest + 0x39;
      piVar1 = piVar1 + 0x39;
    } while (iVar2 < param_1[1]);
  }
  return -1;
}

/* ExplodRemove @ 0x0808f4f0, 45 bytes */
void ExplodRemove(int *param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = (int *)(*param_1 + param_2 * 0xe4);
  if (*piVar1 != 0) {
    *piVar1 = 0;
    param_1[2] = param_1[2] + -1;
  }
  return;
}

/* ExplodRemoveID @ 0x0808f520, 82 bytes */
void ExplodRemoveID(undefined4 *param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar2 = param_1[1];
  if (0 < iVar2) {
    piVar1 = (int *)*param_1;
    do {
      if ((*piVar1 != 0) && (((piVar1[4] == param_3 || (param_3 == -1)) && (piVar1[3] == param_2))))
      {
        *piVar1 = 0;
        param_1[2] = param_1[2] + -1;
        iVar2 = param_1[1];
      }
      iVar3 = iVar3 + 1;
      piVar1 = piVar1 + 0x39;
    } while (iVar3 < iVar2);
  }
  return;
}

/* ExplodRemoveGetHit @ 0x0808f580, 66 bytes */
void ExplodRemoveGetHit(undefined4 *param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar2 = param_1[1];
  if (0 < iVar2) {
    piVar1 = (int *)*param_1;
    do {
      if (((*piVar1 != 0) && (piVar1[3] == param_2)) && (piVar1[0x1e] != 0)) {
        *piVar1 = 0;
        param_1[2] = param_1[2] + -1;
        iVar2 = param_1[1];
      }
      iVar3 = iVar3 + 1;
      piVar1 = piVar1 + 0x39;
    } while (iVar3 < iVar2);
  }
  return;
}

/* ExplodAccessID @ 0x0808f5d0, 71 bytes */
int ExplodAccessID(undefined4 *param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  if (0 < (int)param_1[1]) {
    piVar2 = (int *)*param_1;
    do {
      if ((*piVar2 != 0) && (((piVar2[4] == param_3 || (param_3 == -1)) && (piVar2[3] == param_2))))
      {
        return iVar1;
      }
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 0x39;
    } while (iVar1 < (int)param_1[1]);
  }
  return -1;
}

/* ExplodGetUniqID @ 0x0808f620, 15 bytes */
int ExplodGetUniqID(void)

{
  int iVar1;
  
  iVar1 = id_0;
  id_0 = id_0 + 1;
  return iVar1;
}

/* ExplodBindChange @ 0x0808f630, 73 bytes */
void ExplodBindChange(undefined4 *param_1,int param_2,int param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = param_1[1];
  if (0 < iVar3) {
    piVar1 = (int *)*param_1;
    do {
      if ((*piVar1 != 0) && (((piVar1[4] == param_3 || (param_3 == -1)) && (piVar1[3] == param_2))))
      {
        piVar1[0x18] = param_4;
        iVar3 = param_1[1];
      }
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + 0x39;
    } while (iVar2 < iVar3);
  }
  return;
}

/* ExplodCount @ 0x0808f680, 72 bytes */
int ExplodCount(int *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar2 = param_1[1];
  if (0 < iVar2) {
    iVar1 = *param_1;
    iVar3 = 0;
    do {
      if ((*(int *)(iVar1 + iVar3) != 0) &&
         (((*(int *)(iVar1 + 0x10 + iVar3) == param_3 || (param_3 == -1)) &&
          (*(int *)(iVar1 + 0xc + iVar3) == param_2)))) {
        iVar4 = iVar4 + 1;
      }
      iVar3 = iVar3 + 0xe4;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return iVar4;
}

/* SysExplodParse @ 0x0808f6d0, 549 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x60-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 SysExplodParse(int param_1,int *param_2,undefined4 param_3)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  char *__src;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar3;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  unsigned char ghidra_frame[0x60] __attribute__((aligned(16)));
#define local_5c (*(char (*)[76])(ghidra_frame + 0x4))
  
  *param_2 = 0;
  sprintf(local_5c,"%s.spr",param_3);
  iVar2 = TPScanf(param_1,local_5c,"%i,%i",param_2 + 1,param_2 + 2);
  if (iVar2 == 2) {
    *param_2 = 2;
  }
  iVar2 = *param_2;
  uVar3 = extraout_EDX;
  if (iVar2 == 0) {
    sprintf(local_5c,"%s.anim",param_3,0);
    bVar1 = TPGetValueInt(param_1,local_5c,(uint *)(param_2 + 1));
    uVar3 = extraout_EDX_00;
    if (GHIDRA_ZEXT8(bVar1) == 0) {
      iVar2 = *param_2;
    }
    else {
      *param_2 = 1;
      iVar2 = 1;
    }
  }
  if (iVar2 == 0) {
    sprintf(local_5c,"%s.font",param_3,uVar3);
    iVar2 = TPScanf(param_1,local_5c,"%i,%i,%i",param_2 + 1,param_2 + 2,param_2 + 3);
    if (1 < iVar2) {
      *param_2 = 3;
      sprintf(local_5c,"%s.text",param_3,extraout_EDX_01);
      __src = TPGetValue(param_1,local_5c);
      if (__src == (char *)0x0) {
        *(undefined1 *)(param_2 + 0xf) = 0;
      }
      else {
        strncpy((char *)(param_2 + 0xf),__src,0x2f);
      }
    }
  }
  param_2[9] = 0;
  iVar2 = ExplodGetUniqID();
  param_2[10] = iVar2;
  if (*param_2 != 0) {
    param_2[5] = -2;
    sprintf(local_5c,"%s.displaytime",param_3,local_5c);
    TPGetValueInt(param_1,local_5c,(uint *)(param_2 + 5));
    if ((*param_2 != 1) && (param_2[5] == -2)) {
      param_2[5] = 1;
    }
    sprintf(local_5c,"%s.offset",param_3,extraout_EDX_02);
    TPScanf(param_1,local_5c,"%i,%i",param_2 + 6,param_2 + 7);
    sprintf(local_5c,"%s.facing",param_3);
    TPGetValueInt(param_1,local_5c,(uint *)(param_2 + 0xb));
    sprintf(local_5c,"%s.vfacing",param_3);
    TPGetValueInt(param_1,local_5c,(uint *)(param_2 + 0xc));
    sprintf(local_5c,"%s.layerno",param_3);
    TPGetValueInt(param_1,local_5c,(uint *)(param_2 + 8));
    param_2[0xe] = 0x3f800000;
    param_2[0xd] = 0x3f800000;
    sprintf(local_5c,"%s.scale",param_3);
    TPScanf(param_1,local_5c,"%f,%f",param_2 + 0xd,param_2 + 0xe);
  }
  return 1;
}
#undef local_5c

/* SysExplodParseGetSprGrpImgNo @ 0x0808f900, 40 bytes */
undefined4 SysExplodParseGetSprGrpImgNo(int *param_1,int *param_2,int *param_3)

{
  if (*param_1 != 2) {
    return 0;
  }
  *param_2 = param_1[1];
  *param_3 = param_1[2];
  return 1;
}

/* SysExplodCreateDraw @ 0x0808f930, 13 bytes */
void SysExplodCreateDraw(int *param_1,int *param_2,int *param_3,int *param_4,int param_5,int param_6
                        ,int param_7,int param_8)

{
  SysExplodCreateDrawPal(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}

/* SysExplodCreateDrawPal @ 0x0808f940, 217 bytes
 * FIXUP: 1 call results that the caller reads as extraout_EAX assigned explicitly */
int SysExplodCreateDrawPal
              (int *param_1,int *param_2,int *param_3,int *param_4,int param_5,int param_6,
              int param_7,int param_8)

{
  int iVar1;
  int extraout_EAX;
  int iVar2;
  
  if ((param_2[8] == param_8) || (param_8 == -1)) {
    extraout_EAX = SysExplodCreate(param_1,param_2,param_3,param_4,param_5,param_6,param_7);
    iVar1 = extraout_EAX;
    if (extraout_EAX != -1) {
      iVar2 = *param_1;
      if ((*(int *)(iVar2 + 0x3c + extraout_EAX * 0xe4) == 0) &&
         (*(int *)(iVar2 + 4 + extraout_EAX * 0xe4) == 1)) {
        ExplodUpdate(param_1,extraout_EAX);
        iVar2 = *param_1;
      }
      if (g[0x7306] == 0) {
        ExplodDraw(iVar2 + extraout_EAX * 0xe4);
        iVar2 = *param_1;
      }
      *(undefined4 *)(iVar2 + 8 + extraout_EAX * 0xe4) = 1;
      if (*(int *)(iVar2 + 0x40 + extraout_EAX * 0xe4) == 1) {
        ExplodRemove(param_1,extraout_EAX);
      }
    }
  }
  else {
    iVar1 = -1;
  }
  return iVar1;
}

/* SysExplodCreate @ 0x0808fa20, 615 bytes
 * REVIEW: pid-unaff_
 * FIXUP: hand-written override (see overrides/) */
/* OVERRIDE: Ghidra output of 0x0808fa20-0x0808fc87 with the return value
 * restored. Reason: the function returns the explod index kept in %ebx
 * (VERIFIED: "mov %eax,%ebx" after ExplodAccessID / ExplodAdd /
 * ExplodAddSprite / ExplodAddText, epilogue "mov %ebx,%eax; ret"), but
 * Ghidra reused the index variable as a temporary after LAB_0808fbad and
 * printed "return unaff_EBX" everywhere, so callers lost it
 * (SysExplodCreateDrawPal, SysExplodCreate_Fight use it as an index).
 * On the three early exits the original returns the caller's %ebx
 * unchanged; that value cannot be reproduced in C, -1 ("no explod") is
 * returned instead (documented in COMPLETENESS-REPORT.md).
 * puVar5[5], puVar5[6] are float fields stored with fstps (bit copies). */
int SysExplodCreate(int *param_1,int *param_2,int *param_3,int *param_4,int param_5,int param_6,
                   int param_7)
{
  uint uVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int idx;
  undefined4 *puVar5;

  puVar5 = (undefined4 *)0x0;
  bVar2 = true;
  if (*param_2 == 0) {
    return -1;
  }
  iVar3 = ExplodAccessID(param_1,param_2[9],param_2[10]);
  if (iVar3 == -1) {
    iVar4 = *param_2;
    if (iVar4 == 1) {
      if (((param_4 != (int *)0x0) && (param_3 != (int *)0x0)) &&
         (iVar3 = ExplodAdd(param_1,param_2[1],param_4,(int)param_3), iVar3 != -1)) {
        puVar5 = (undefined4 *)(*param_1 + iVar3 * 0xe4);
        iVar4 = AnimChangeAction((int *)puVar5[0x20],0,param_2[1]);
        if (iVar4 == 0) {
          *puVar5 = 0;
          param_1[2] = param_1[2] + -1;
        }
        else {
          AnimResetAction((int *)puVar5[0x20]);
        }
      }
    }
    else {
      if (iVar4 < 2) {
        return -1;
      }
      if (iVar4 == 2) {
        if (param_3 == (int *)0x0) goto LAB_0808fbad;
        iVar3 = ExplodAddSprite(param_1,param_2[1],param_2[2],param_3);
      }
      else {
        if (iVar4 != 3) {
          return -1;
        }
        uVar1 = param_2[1];
        if (((9 < uVar1) || ((char)param_2[0xf] == '\0')) || (g[uVar1 + 0x414b] == 0))
        goto LAB_0808fbad;
        iVar3 = ExplodAddText(param_1,(char *)(param_2 + 0xf),*(int *)(param_5 + uVar1 * 4),
                              param_2[2],param_2[3]);
      }
      if (iVar3 != -1) {
        puVar5 = (undefined4 *)(*param_1 + iVar3 * 0xe4);
      }
    }
  }
  else {
    bVar2 = false;
  }
LAB_0808fbad:
  idx = iVar3;                                     /* %ebx from here to the epilogue */
  if (iVar3 != -1) {
    puVar5 = (undefined4 *)(*param_1 + iVar3 * 0xe4);
  }
  if (puVar5 != (undefined4 *)0x0) {
    puVar5[3] = param_2[9];
    puVar5[0x1f] = 1;
    puVar5[4] = param_2[10];
    puVar5[0x1b] = 0;
    puVar5[0x17] = 3;
    if (param_2[0xb] == -1) {
      puVar5[0x1a] = puVar5[0x1a] | 1;
    }
    if (param_2[0xc] == -1) {
      puVar5[0x1a] = puVar5[0x1a] | 2;
    }
    iVar3 = param_2[6];
    puVar5[0xb] = param_6 + iVar3;
    iVar4 = param_2[7];
    puVar5[0xc] = param_7 + iVar4;
    puVar5[5] = GHIDRA_F2I(undefined4, (float)(param_6 + iVar3));
    puVar5[6] = GHIDRA_F2I(undefined4, (float)(param_7 + iVar4));
    puVar5[0x11] = param_2[0xd];
    puVar5[0x12] = param_2[0xe];
    puVar5[0x19] = param_2[8];
    if (bVar2) {
      iVar3 = param_2[5];
      if ((iVar3 == -2) && (puVar5[1] == 1)) {
        iVar3 = AnimGetLooptime((undefined4 *)puVar5[0x20]);
      }
      puVar5[0x10] = iVar3;
      puVar5[0xe] = puVar5[0x10];
      puVar5[0xd] = puVar5[0x10];
    }
  }
  return idx;
}

/* SysExplodCreate_Fight @ 0x0808fc90, 60 bytes
 * FIXUP: return type set to void: only unaffected-register values were returned */
void SysExplodCreate_Fight(int *param_1,int param_2,int param_3)

{
  undefined4 extraout_EAX;
  
  SysExplodCreate((int *)g[0x52bf],param_1,(int *)g[0x4149],(int *)g[0x414a],(int)(g + 0x414b),
                  param_2,param_3);
  return;
}

/* SysExplodCreate_Sys @ 0x0808fcd0, 70 bytes */
void SysExplodCreate_Sys(int *param_1,int param_2,int param_3)

{
  GameReloadSystemSprSnd();
  SysExplodCreate((int *)g[0x52bf],param_1,(int *)g[0x5ac0],(int *)g[0x62c2],(int)(g + 0x62c3),
                  param_2,param_3);
  return;
}

/* SysExplodCreateDraw_Fight @ 0x0808fd20, 65 bytes
 * FIXUP: return type set to void: only unaffected-register values were returned */
void SysExplodCreateDraw_Fight(int *param_1,int param_2,int param_3,int param_4)

{
  undefined4 extraout_EAX;
  
  SysExplodCreateDraw((int *)g[0x52bf],param_1,(int *)g[0x4149],(int *)g[0x414a],(int)(g + 0x414b),
                      param_2,param_3,param_4);
  return;
}

/* SysExplodCreateDraw_Sys @ 0x0808fd70, 79 bytes
 * FIXUP: return type set to void: only unaffected-register values were returned */
void SysExplodCreateDraw_Sys(int *param_1,int param_2,int param_3,int param_4)

{
  undefined4 extraout_EAX;
  
  GameReloadSystemSprSnd();
  SysExplodCreateDraw((int *)g[0x52bf],param_1,(int *)g[0x5ac0],(int *)g[0x62c2],(int)(g + 0x62c3),
                      param_2,param_3,param_4);
  return;
}

