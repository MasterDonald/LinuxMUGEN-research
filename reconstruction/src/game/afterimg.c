/*
 * afterimg.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08082070-0x08082875, 7 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* AftImgNew @ 0x08082070, 74 bytes */
int * AftImgNew(int param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)ecalloc(1,0x7c);
  if (piVar1 == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    iVar2 = AftImgInit(piVar1,param_1);
    if (iVar2 == 0) {
      AftImgFree(piVar1);
      piVar1 = (int *)0x0;
    }
  }
  return piVar1;
}

/* AftImgInit @ 0x080820c0, 140 bytes */
undefined4 AftImgInit(int *param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  piVar5 = param_1;
  for (iVar3 = 0x1f; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar5 = 0;
    piVar5 = piVar5 + 1;
  }
  iVar3 = ecalloc(1,param_2 * 0x67c);
  *param_1 = iVar3;
  if (iVar3 == 0) {
LAB_080820fc:
    uVar1 = 0;
  }
  else {
    iVar3 = 0;
    param_1[1] = param_2;
    if (0 < param_2) {
      iVar4 = 0;
      do {
        iVar2 = EBPalInit((int *)(iVar4 + *param_1 + 0x20),0x100,(void *)(iVar4 + *param_1 + 0x27c),
                          0);
        if (iVar2 == 0) goto LAB_080820fc;
        iVar3 = iVar3 + 1;
        iVar4 = iVar4 + 0x67c;
      } while (iVar3 < param_2);
    }
    uVar1 = 1;
  }
  return uVar1;
}

/* AftImgFree @ 0x08082150, 37 bytes */
undefined4 AftImgFree(int *param_1)

{
  undefined4 extraout_EAX;
  undefined4 in_EDX;
  
  if (param_1 != (int *)0x0) {
    AftImgDeInit(param_1);
    free(param_1);
    return extraout_EAX;
  }
  return in_EDX;
}

/* AftImgDeInit @ 0x08082180, 97 bytes */
void AftImgDeInit(int *param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != (int *)0x0) {
    iVar1 = *param_1;
    if (iVar1 != 0) {
      iVar2 = 0;
      if (0 < param_1[1]) {
        while( true ) {
          EBPalDeInit(iVar1 + 0x20 + iVar2 * 0x67c);
          if (param_1[1] <= iVar2 + 1) break;
          iVar1 = *param_1;
          iVar2 = iVar2 + 1;
        }
      }
      free((void *)*param_1);
    }
    for (iVar1 = 0x1f; iVar1 != 0; iVar1 = iVar1 + -1) {
      *param_1 = 0;
      param_1 = param_1 + 1;
    }
  }
  return;
}

/* AftImgSetup @ 0x080821f0, 59 bytes */
void AftImgSetup(int param_1,undefined4 *param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  
  *(undefined4 *)(param_1 + 0x18) = 1;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0xc) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 8) = param_3;
  puVar2 = (undefined4 *)(param_1 + 0x1c);
  for (iVar1 = 0x18; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = *param_2;
    param_2 = param_2 + 1;
    puVar2 = puVar2 + 1;
  }
  return;
}

/* AftImgUpdate @ 0x08082230, 448 bytes
 * FIXUP: 3 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: untyped (undefined4) <-> float moves kept as bit copies: 4 assignments, 0 calls, 0 returns
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
undefined4
AftImgUpdate(int *param_1,float param_2,float param_3,float param_4,undefined4 param_5,float param_6
            ,uint param_7,int param_8)

{
  undefined4 *puVar1;
  int iVar2;
  float10 fVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  
  if ((param_1[6] == 0) || (iVar2 = param_1[2], iVar2 == 0)) {
LAB_08082291:
    uVar4 = 0;
  }
  else {
    if (param_1[7] == -1) {
      iVar7 = param_1[5];
      iVar6 = param_1[9];
    }
    else {
      iVar7 = param_1[5];
      iVar6 = param_1[9];
      if (param_1[8] * iVar6 + param_1[7] <= iVar7 + 1) {
        param_1[6] = 0;
        goto LAB_08082291;
      }
    }
    if (iVar7 % iVar6 == 0) {
      puVar1 = (undefined4 *)(*param_1 + param_1[4] * 0x67c);
      *puVar1 = *(undefined4 *)(iVar2 + 0x2c);
      uVar5 = FlipFlagMix(param_7,*(uint *)(*(int *)(iVar2 + 0x10) + 0x18) & 3);
      puVar1[5] = uVar5;
      puVar1[3] = GHIDRA_F2I(undefined4, param_4);
      puVar1[4] = param_5;
      fVar3 = (float10)*(int *)(*(int *)(param_1[2] + 0x10) + 0x10) * param_4;
      if ((param_7 & 1) != 0) {
        fVar3 = fVar3 * -1.0;
      }
      puVar1[1] = GHIDRA_F2I(undefined4, fVar3 + param_2);
      fVar3 = (float10)*(int *)(*(int *)(param_1[2] + 0x10) + 0x14) * GHIDRA_I2F(puVar1[4]);
      if ((param_7 & 2) != 0) {
        fVar3 = fVar3 * -1.0;
      }
      puVar1[2] = GHIDRA_F2I(undefined4, fVar3 + param_3);
      puVar1[6] = *(undefined4 *)(param_1[2] + 0x34);
      iVar6 = HFlipToSgn(param_7);
      iVar2 = param_1[5];
      iVar7 = param_1[7];
      puVar1[7] = GHIDRA_F2I(undefined4, (float10)iVar6 * param_6);
      if ((iVar7 <= iVar2 + 1) && (iVar7 != -1)) {
        *puVar1 = 0xffffffff;
      }
      uVar5 = param_1[4] + 1;
      param_1[4] = uVar5;
      uVar5 = uVar5 & (param_1[8] <= (int)uVar5) - 1;
      param_1[4] = uVar5;
      if (uVar5 == param_1[3]) {
        uVar5 = uVar5 + 1;
        param_1[3] = uVar5;
        param_1[3] = uVar5 & (param_1[8] <= (int)uVar5) - 1;
      }
    }
    if (param_8 != 0) {
      param_1[5] = param_1[5] + 1;
    }
    uVar4 = 1;
  }
  return uVar4;
}

/* AftImgDraw @ 0x080823f0, 1157 bytes
 * FIXUP: frame emulation: 20 stack locals placed at their original offsets in a 0xa0-byte frame (a local's address escapes, see apply_frame_emulation) */
void AftImgDraw(int *param_1,int param_2,int param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  int *piVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  unsigned char ghidra_frame[0xa0] __attribute__((aligned(16)));
#define local_94 (*(float *)(ghidra_frame + 0xc))
#define local_90 (*(float *)(ghidra_frame + 0x10))
#define local_8c (*(float *)(ghidra_frame + 0x14))
#define local_88 (*(int *)(ghidra_frame + 0x18))
#define local_74 (*(int *)(ghidra_frame + 0x2c))
#define local_70 (*(int *)(ghidra_frame + 0x30))
#define local_5c (*(int *)(ghidra_frame + 0x44))
#define local_58 (*(int **)(ghidra_frame + 0x48))
#define local_54 (*(int *)(ghidra_frame + 0x4c))
#define local_50 (*(int **)(ghidra_frame + 0x50))
#define local_4c (*(int *)(ghidra_frame + 0x54))
#define local_48 (*(int *)(ghidra_frame + 0x58))
#define local_44 (*(undefined4 *)(ghidra_frame + 0x5c))
#define local_40 (*(int *)(ghidra_frame + 0x60))
#define local_3c (*(int *)(ghidra_frame + 0x64))
#define local_38 (*(int *)(ghidra_frame + 0x68))
#define local_34 (*(float *)(ghidra_frame + 0x6c))
#define local_30 (*(float *)(ghidra_frame + 0x70))
#define local_2c (*(int *)(ghidra_frame + 0x74))
#define local_28 (*(int *)(ghidra_frame + 0x78))
  
  local_74 = 0;
  local_88 = 0;
  if (param_1[6] != 0) {
    iVar5 = param_1[3];
    iVar10 = param_1[4];
    if (iVar5 != iVar10) {
      bVar4 = iVar5 <= iVar10;
      local_70 = -1;
      if (iVar10 < 0) {
        bVar4 = true;
        iVar10 = iVar10 + param_1[8];
      }
      do {
        iVar6 = param_1[10];
        while( true ) {
          while( true ) {
            do {
              iVar10 = iVar10 - iVar6;
              if ((iVar10 < 0) && (!bVar4)) {
                bVar4 = true;
                iVar10 = iVar10 + param_1[8];
              }
              if ((iVar10 < iVar5) && (bVar4)) {
                return;
              }
              piVar1 = (int *)(*param_1 + iVar10 * 0x67c);
              iVar2 = *piVar1;
            } while (iVar2 == -1);
            piVar9 = piVar1 + 8;
            iVar5 = EBPalGetDataptr((int)piVar9);
            piVar3 = *(int **)(param_1[2] + 4);
            iVar6 = SpriteArrayAccess(piVar3,iVar2);
            iVar7 = *(int *)(iVar6 + 0x14) + -1;
            if (0 < iVar7) break;
            iVar6 = param_1[10];
            iVar5 = param_1[3];
          }
          if (*(int *)(iVar6 + 0x30) != -1) break;
          iVar6 = param_1[10];
          iVar5 = param_1[3];
        }
        EBPalSetDataptr(piVar9,*(int *)(iVar6 + 0x14),0);
        EBPalReset((int)piVar9);
        if (local_74 == 0) {
          iVar8 = SpriteArrayPalAccess((int)piVar3,*(int *)(iVar6 + 0x30));
          iVar13 = 1;
          iVar6 = param_1[0xb];
          iVar12 = iVar5;
          iVar14 = iVar7;
          iVar8 = EBPalGetDataptr(iVar8);
          Pal4ColorBal(iVar8,iVar12,iVar6,iVar13,iVar14);
          if (param_1[0xc] != 0) {
            Pal4InvertAll(iVar5,iVar5,1,iVar7);
          }
          Pal4BrightnessRGB(iVar5,iVar5,param_1[0xd],param_1[0xe],param_1[0xf],1,iVar7);
          Pal4ContrastRGB(iVar5,iVar5,param_1[0x10],param_1[0x11],param_1[0x12],1,iVar7);
          Pal4BrightnessRGB(iVar5,iVar5,param_1[0x13],param_1[0x14],param_1[0x15],1,iVar7);
          local_90 = 256.0;
          local_94 = 256.0;
          local_8c = 256.0;
          EBPalMarkDataChanged((int)piVar9);
          local_88 = iVar5;
        }
        else {
          local_8c = local_8c * GHIDRA_I2F(param_1[0x19]);
          local_90 = local_90 * GHIDRA_I2F(param_1[0x1a]);
          local_94 = local_94 * GHIDRA_I2F(param_1[0x1b]);
          EBPalSetDataptr(piVar9,-1,local_88);
          EBPalAdd((int)piVar9,param_1[0x16] * local_74,param_1[0x17] * local_74,
                   param_1[0x18] * local_74);
          EBPalMul((int)piVar9,(int)GHIDRA_FIST32(local_8c),(int)GHIDRA_FIST32(local_90),(int)GHIDRA_FIST32(local_94));
        }
        local_74 = local_74 + 1;
        piVar11 = &local_5c;
        for (iVar5 = 0xe; iVar5 != 0; iVar5 = iVar5 + -1) {
          *piVar11 = 0;
          piVar11 = piVar11 + 1;
        }
        local_5c = piVar1[6];
        if (param_4 < piVar1[6]) {
          local_5c = param_4;
        }
        local_5c = local_5c + local_70;
        local_4c = (int)GHIDRA_FIST32((float)param_2 + GHIDRA_I2F(piVar1[1]));
        local_48 = (int)GHIDRA_FIST32((float)param_3 + GHIDRA_I2F(piVar1[2]));
        local_40 = param_1[0x1c];
        local_3c = param_1[0x1d];
        local_38 = param_1[0x1e];
        local_34 = GHIDRA_I2F(piVar1[3]);
        local_28 = piVar1[5];
        local_30 = GHIDRA_I2F(piVar1[4]);
        if (GHIDRA_I2F(piVar1[7]) == 0.0) {
          local_44 = 2;
          if ((local_34 == 1.0) && (local_30 == 1.0)) {
            local_44 = 1;
          }
        }
        else {
          local_44 = 3;
          local_2c = piVar1[7];
        }
        local_58 = piVar3;
        local_54 = iVar2;
        local_50 = piVar9;
        PRSprAdd(*(int **)(param_1[2] + 0x30),&local_5c);
        iVar5 = param_1[3];
        local_70 = local_70 + -1;
      } while( true );
    }
  }
  return;
}
#undef local_94
#undef local_90
#undef local_8c
#undef local_88
#undef local_74
#undef local_70
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_28

