/*
 * helper.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x080980d0-0x08098c47, 6 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* HelperMake @ 0x080980d0, 2140 bytes
 * REVIEW: pid-unaff_
 * FIXUP: rewrote 2 PalGrpFlag by-value loads
 * FIXUP: 4 data addresses written as literals replaced by data-image references
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
int * HelperMake(int *param_1,char *param_2,int *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int *piVar7;
  int unaff_EDI;
  int *piVar8;
  float10 fVar9;
  int local_20;
  
  piVar7 = (int *)*param_3;
  piVar3 = (int *)0x0;
  if (4 < g[0x7395]) {
    piVar3 = (int *)g[0x73de];
    iVar4 = piVar3[0x56];
    iVar6 = 5;
    while ((iVar4 != 0 && (piVar3 = (int *)0x0, iVar6 + 1 <= g[0x7395]))) {
      piVar3 = (int *)g[iVar6 + 0x73da];
      iVar4 = piVar3[0x56];
      iVar6 = iVar6 + 1;
    }
  }
  if (piVar3 == (int *)0x0) {
    return (int *)0x0;
  }
  iVar4 = *param_1;
  *piVar3 = iVar4;
  piVar3[0x259] = iVar4 + 0x11b4;
  piVar3[0x2fa] = param_1[0x2fa];
  PlayerEnableSet(piVar3[2],1);
  iVar4 = EvalExpressionI((int)param_1,param_2 + 0x80,0);
  if (iVar4 == 0) {
    iVar6 = param_1[0x4eb];
  }
  else {
    piVar5 = SpriteArrayNewInstanceOnto((int *)piVar3[0x4ec],(int *)param_1[0x4ed]);
    if (piVar5 == (int *)0x0) {
      return (int *)0x0;
    }
    iVar6 = piVar3[0x4ec];
  }
  piVar3[0x4eb] = iVar6;
  puVar1 = (undefined4 *)piVar3[0x4ef];
  iVar6 = *piVar3;
  piVar3[0x4ed] = param_1[0x4ed];
  *puVar1 = *(undefined4 *)(iVar6 + 0x11cc);
  puVar1[1] = piVar3[0x4eb];
  iVar2 = piVar3[0x87];
  *(undefined4 *)(iVar2 + 4) = *(undefined4 *)(iVar6 + 0x11cc);
  *(int *)(iVar2 + 8) = piVar3[0x4ed];
  if (iVar4 != 0) {
    unaff_EDI = piVar3[0x976];
    iVar4 = PalGrpFlagIsNonZero(*(PalGrpFlag *)(piVar3 + 0x972));
    if (iVar4 != 0) {
      PalGrpRemove(*(PalGrpFlag *)(piVar3 + 0x972));
      unaff_EDI = piVar3[0x974];
      PalGrpAddSpr(piVar3[0x4eb],piVar3[0x972],piVar3[0x973],unaff_EDI,piVar3[0x975],piVar3[0x976]);
    }
  }
  if (*param_2 == '\0') {
    sprintf((char *)(piVar3 + 8),"%s\'s helper",param_1 + 8,unaff_EDI);
  }
  else {
    strcpy((char *)(piVar3 + 8),param_2);
  }
  piVar5 = g;
  piVar3[1] = g[0x749d];
  piVar5[0x749d] = piVar5[0x749d] + 1;
  piVar5 = param_1 + 0x14;
  piVar8 = piVar3 + 0x14;
  for (iVar4 = 0x42; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar8 = *piVar5;
    piVar5 = piVar5 + 1;
    piVar8 = piVar8 + 1;
  }
  fVar9 = EvalExpressionF(param_1,(int *)(param_2 + 0xa4));
  if (fVar9 != -32760.0) {
    piVar3[0x1f] = GHIDRA_F2I(int, fVar9);
  }
  fVar9 = EvalExpressionF(param_1,(int *)(param_2 + 0xb0));
  if (fVar9 != -32760.0) {
    piVar3[0x20] = GHIDRA_F2I(int, fVar9);
  }
  iVar4 = EvalExpressionI((int)param_1,param_2 + 0xbc,1);
  if (iVar4 != -0x7fef) {
    piVar3[0x21] = iVar4;
  }
  iVar4 = EvalExpressionI((int)param_1,param_2 + 200,1);
  if (iVar4 != -0x7fef) {
    piVar3[0x22] = iVar4;
  }
  iVar4 = EvalExpressionI((int)param_1,param_2 + 0xd4,1);
  if (iVar4 != -0x7fef) {
    piVar3[0x23] = iVar4;
  }
  iVar4 = EvalExpressionI((int)param_1,param_2 + 0xe0,1);
  if (iVar4 != -0x7fef) {
    piVar3[0x24] = iVar4;
  }
  iVar4 = EvalExpressionI((int)param_1,param_2 + 0xec,1);
  if (iVar4 != -0x7fef) {
    piVar3[0x26] = iVar4;
  }
  iVar4 = EvalExpressionI((int)param_1,param_2 + 0xf8,1);
  if (iVar4 != -0x7fef) {
    piVar3[0x27] = iVar4;
  }
  iVar4 = EvalExpressionI((int)param_1,param_2 + 0x104,1);
  if (iVar4 != -0x7fef) {
    piVar3[0x28] = iVar4;
  }
  iVar4 = EvalExpressionI((int)param_1,param_2 + 0x110,1);
  if (iVar4 != -0x7fef) {
    piVar3[0x29] = iVar4;
  }
  iVar4 = EvalExpressionI((int)param_1,param_2 + 0x11c,1);
  if (iVar4 != -0x7fef) {
    piVar3[0x2a] = iVar4;
  }
  iVar4 = EvalExpressionI((int)param_1,param_2 + 0x128,1);
  if (iVar4 != -0x7fef) {
    piVar3[0x2b] = iVar4;
  }
  iVar4 = EvalExpressionI((int)param_1,param_2 + 0x134,1);
  if (iVar4 != -0x7fef) {
    piVar3[0x2c] = iVar4;
  }
  PlayerReset(piVar3);
  piVar5 = piVar3 + 0x390;
  for (iVar4 = 0x3c; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar5 = 0;
    piVar5 = piVar5 + 1;
  }
  piVar5 = piVar3 + 0x3cc;
  for (iVar4 = 0x28; iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar5 = 0;
    piVar5 = piVar5 + 1;
  }
  iVar4 = EvalExpressionI((int)param_1,param_2 + 0x68,1);
  if (iVar4 < 0) {
    iVar4 = 0;
    Warn((int)param_1,(int)&DAT_08278834);
  }
  PlayerChangeState((int)piVar3,iVar4);
  piVar3[0x67] = param_1[0x67];
  piVar3[0x68] = param_1[0x68];
  piVar3[3] = param_1[3];
  piVar3[600] = param_1[600];
  iVar4 = EvalExpressionI((int)param_1,param_2 + 0x74,0);
  piVar3[0x8f] = (uint)(iVar4 == 0);
  iVar4 = EvalExpressionI((int)param_1,param_2 + 0x74,0);
  if (iVar4 != 0) {
    piVar5 = param_1 + 0x92;
    piVar8 = piVar3 + 0x92;
    for (iVar4 = 0x2f; iVar4 != 0; iVar4 = iVar4 + -1) {
      *piVar8 = *piVar5;
      piVar5 = piVar5 + 1;
      piVar8 = piVar8 + 1;
    }
    piVar5 = param_1 + 0xc1;
    piVar8 = piVar3 + 0xc1;
    for (iVar4 = 0x197; iVar4 != 0; iVar4 = iVar4 + -1) {
      *piVar8 = *piVar5;
      piVar5 = piVar5 + 1;
      piVar8 = piVar8 + 1;
    }
  }
  iVar4 = EvalExpressionI((int)param_1,param_2 + 0x30,1);
  if (iVar4 < 0) {
    iVar4 = 0;
    Warn((int)param_1,(int)&DAT_0827884b);
  }
  piVar3[0x986] = iVar4;
  piVar3[0x988] = (int)param_1;
  piVar3[0x987] = param_1[1];
  piVar5 = (int *)param_1[0x989];
  if ((int *)param_1[0x989] == (int *)0x0) {
    piVar5 = param_1;
  }
  piVar3[0x989] = (int)piVar5;
  piVar3[0x98a] = *(int *)(param_2 + 0x3c);
  piVar3[100] = 1;
  iVar6 = *(int *)(param_2 + 0x58);
  switch(iVar6) {
  case 0:
switchD_080986a1_caseD_0:
    piVar7 = param_1;
    break;
  case 1:
  case 2:
    piVar3[100] = param_1[100];
    iVar6 = *(int *)(param_2 + 0x58);
  case 3:
  case 4:
    if ((((iVar6 == 2) && (param_1[100] == 1)) || ((iVar6 == 1 && (param_1[100] == -1)))) ||
       (iVar6 == 3)) {
      iVar4 = g[0x7311];
    }
    else {
      iVar4 = g[0x7311] + 0x140;
    }
    local_20 = 0;
    goto switchD_080986a1_default;
  case 5:
    if (piVar7 == (int *)0x0) goto switchD_080986a1_caseD_0;
    break;
  default:
    goto switchD_080986a1_default;
  }
  iVar4 = (int)GHIDRA_FIST32(GHIDRA_I2F(piVar7[0x67]));
  local_20 = (int)GHIDRA_FIST32(GHIDRA_I2F(piVar7[0x68]));
  piVar3[100] = piVar7[100];
switchD_080986a1_default:
  iVar6 = EvalExpressionI((int)param_1,param_2 + 0x40,1);
  piVar3[0x67] = GHIDRA_F2I(int, (float)(iVar6 * piVar3[100] + iVar4));
  iVar4 = EvalExpressionI((int)param_1,param_2 + 0x4c,1);
  piVar3[0x68] = GHIDRA_F2I(int, (float)(iVar4 + local_20));
  piVar3[0x69] = param_1[0x69];
  iVar4 = EvalExpressionI((int)param_1,param_2 + 0x5c,1);
  if (iVar4 == -1) {
    piVar3[100] = -piVar3[100];
  }
  KBISetFlip((int)(piVar3 + 0x92),(uint)(piVar3[100] == -1));
  if (piVar3[0x98a] != 1) {
    piVar3[0x79] = 0;
    piVar3[0x7b] = 0;
    piVar3[0x7a] = 0;
    piVar3[0x7c] = 0;
  }
  iVar4 = EvalExpressionI((int)param_1,param_2 + 0x98,1);
  if (iVar4 < 0) {
    iVar4 = 0;
    Warn((int)param_1,(int)&DAT_0827885e);
  }
  piVar3[0x77] = iVar4;
  iVar4 = EvalExpressionI((int)param_1,param_2 + 0x8c,1);
  if (iVar4 < 0) {
    iVar4 = 0;
    Warn((int)param_1,(int)&DAT_0827887b);
  }
  piVar3[0x78] = iVar4;
  piVar3[0x3ff] = 0;
  piVar3[0x401] = 1;
  iVar4 = PlayerNearestEnemy((int)piVar3);
  *(undefined1 *)(piVar3 + 0x83) = 0;
  piVar7 = g;
  piVar3[0xd09] = iVar4;
  piVar3[0x81] = 0;
  piVar3[0x82] = 0;
  piVar7[piVar3[2] + 0x749e] = 1;
  piVar7[0x74de] = 1;
  return piVar3;
}

/* HelperDestroy @ 0x08098930, 411 bytes
 * FIXUP: rewrote 4 PalGrpFlag by-value loads */
void HelperDestroy(int param_1)

{
  int iVar1;
  bool bVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  if (*(int *)(param_1 + 0x1c) == 1) {
    PlayerDropBoundTargets(param_1,(int *)0x0);
    piVar3 = g;
    iVar4 = g[0x7459];
    if (iVar4 <= g[0x745a]) {
      iVar5 = iVar4 * 4 + 0x1cf60;
      do {
        iVar1 = *(int *)(iVar5 + 4 + (int)piVar3);
        if ((iVar1 == 0) || (bVar2 = true, *(int *)(iVar1 + 0x158) == 0)) {
          bVar2 = false;
        }
        if (((bVar2) && (*(int *)(iVar1 + 0x3454) == param_1)) && (*(int *)(iVar1 + 0x3430) != 0)) {
          *(undefined4 *)(iVar1 + 0x3430) = 0;
          *(undefined4 *)(iVar1 + 0x3454) = 0;
        }
        iVar4 = iVar4 + 1;
        iVar5 = iVar5 + 4;
      } while (iVar4 <= piVar3[0x745a]);
    }
    iVar4 = *(int *)(param_1 + 0x1394);
    if (iVar4 != 0) {
      *(undefined4 *)(iVar4 + 0x18) = 0;
      *(undefined4 *)(iVar4 + 8) = 0;
      *(undefined4 *)(param_1 + 0x1394) = 0;
    }
    iVar4 = PalGrpFlagIsNonZero(*(PalGrpFlag *)(param_1 + 0x25c8));
    if (iVar4 != 0) {
      PalGrpRemove(*(PalGrpFlag *)(param_1 + 0x25c8));
      PalGrpRemove(*(PalGrpFlag *)(param_1 + 0x25c8));
      PalGrpRemove(*(PalGrpFlag *)(param_1 + 0x25c8));
    }
    *(undefined4 *)(param_1 + 0x13b4) = 0;
    *(undefined4 *)(param_1 + 0x13ac) = 0;
    PlayerEnableSet(*(int *)(param_1 + 8),0);
  }
  return;
}

/* HelperParent @ 0x08098ad0, 40 bytes */
uint HelperParent(int param_1)

{
  if (*(int *)(param_1 + 0x1c) != 1) {
    return 0;
  }
  return *(uint *)(param_1 + 0x2620) &
         (*(int *)(*(uint *)(param_1 + 0x2620) + 4) != *(int *)(param_1 + 0x261c)) - 1;
}

/* HelperRoot @ 0x08098b00, 11 bytes */
undefined4 HelperRoot(int param_1)

{
  return *(undefined4 *)(param_1 + 0x2624);
}

/* HelperCount @ 0x08098b10, 153 bytes */
int HelperCount(int param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  iVar6 = 0;
  iVar4 = g[0x7459];
  if (iVar4 <= g[0x745a]) {
    piVar5 = g + iVar4 + 0x73d9;
    iVar3 = iVar4 * 4 + 0x1cf60;
    do {
      iVar1 = *(int *)(iVar3 + 4 + (int)g);
      if ((iVar1 == 0) || (bVar2 = true, *(int *)(iVar1 + 0x158) == 0)) {
        bVar2 = false;
      }
      if (bVar2) {
        iVar1 = *piVar5;
        if ((((*(int *)(iVar1 + 0x2624) == param_1) ||
             (*(int *)(iVar1 + 0x2624) == *(int *)(param_1 + 0x2624))) &&
            (*(int *)(iVar1 + 0x1c) == 1)) &&
           ((*(int *)(iVar1 + 0x2618) == param_2 || (param_2 == 0)))) {
          iVar6 = iVar6 + 1;
        }
      }
      iVar4 = iVar4 + 1;
      piVar5 = piVar5 + 1;
      iVar3 = iVar3 + 4;
    } while (iVar4 <= g[0x745a]);
  }
  return iVar6;
}

/* HelperAccessID @ 0x08098bb0, 151 bytes */
undefined4 HelperAccessID(int param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  iVar3 = g[0x7459];
  if (iVar3 <= g[0x745a]) {
    piVar5 = g + iVar3 + 0x73d9;
    iVar4 = iVar3 * 4 + 0x1cf60;
    do {
      iVar1 = *(int *)(iVar4 + 4 + (int)g);
      if ((iVar1 == 0) || (bVar2 = true, *(int *)(iVar1 + 0x158) == 0)) {
        bVar2 = false;
      }
      if (bVar2) {
        iVar1 = *piVar5;
        if (((*(int *)(iVar1 + 0x2624) == param_1) ||
            (*(int *)(iVar1 + 0x2624) == *(int *)(param_1 + 0x2624))) &&
           (*(int *)(iVar1 + 0x1c) == 1)) {
          if (*(int *)(iVar1 + 0x2618) == param_2) {
            return iVar1;
          }
          if (param_2 == 0) {
            return iVar1;
          }
        }
      }
      iVar3 = iVar3 + 1;
      piVar5 = piVar5 + 1;
      iVar4 = iVar4 + 4;
    } while (iVar3 <= g[0x745a]);
  }
  return 0;
}

