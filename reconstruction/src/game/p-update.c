/*
 * p-update.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x080b0fe0-0x080b8455, 43 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"

extern int nokoflag_0 __asm__("D_08288040"); /* file-static 0x08288040 */

/* PlayerReset @ 0x080b0fe0, 1512 bytes
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 2 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
void PlayerReset(int *param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  
  piVar6 = g;
  if (*param_1 == 0) {
    return;
  }
  piVar2 = param_1;
  if (param_1[3] == 1) {
    piVar2 = (int *)g[0x73da];
  }
  if (param_1[3] == 2) {
    piVar2 = (int *)g[0x73db];
  }
  iVar3 = *(int *)param_1[0x87];
  param_1[0x57] = 0;
  iVar1 = piVar6[0x799f];
  param_1[0x62] = GHIDRA_F2I(int, ((float10)param_1[0x16] * ((float)0.01f)));
  param_1[0x60] = 0;
  param_1[0x5e] = 0;
  param_1[100] = 1;
  param_1[0x65] = 0;
  param_1[0x66] = 1;
  param_1[0x6f] = 0;
  param_1[0x6e] = 0;
  param_1[0x6d] = 0;
  param_1[0x71] = 0;
  param_1[0x70] = 0;
  param_1[0x72] = 0;
  param_1[0x73] = 0;
  param_1[0x74] = 0;
  iVar1 = (iVar1 * param_1[0x14]) / 100;
  param_1[0x5f] = param_1[0x15];
  param_1[0x5d] = (int)(piVar2 + 0x5f);
  param_1[0x59] = iVar1;
  param_1[0x5b] = iVar1;
  param_1[0x5a] = iVar1;
  param_1[0x58] = iVar1;
  param_1[0x5c] = (int)(piVar2 + 0x5e);
  param_1[99] = GHIDRA_F2I(int, (100.0 / (float10)param_1[0x1c]));
  param_1[0x77] = 0;
  param_1[0x78] = 0;
  param_1[0x79] = 1;
  param_1[0x80] = 0;
  param_1[0x7f] = 0;
  param_1[0x7e] = 0;
  param_1[0x7d] = 0;
  param_1[0x81] = 0;
  param_1[0x82] = 0;
  *(undefined1 *)(param_1 + 0x83) = 0;
  param_1[0x85] = 0;
  param_1[0x86] = 0;
  param_1[0x84] = 0;
  iVar1 = ArrayScanFirst(iVar3);
  while (iVar1 != 0) {
    ProjArrayDelete((int *)param_1[0x87],*(int *)(iVar3 + 0x1c));
    iVar1 = ArrayScanNext(iVar3);
  }
  ArrayClear(param_1[0x88]);
  piVar6 = param_1 + 0x89;
  for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar6 = 0;
    piVar6 = piVar6 + 1;
  }
  param_1[0x8c] = 0x3f800000;
  param_1[0x8b] = 0x3f800000;
  memset(param_1 + 0x92,0,0xbc);
  memset(param_1 + 0xc1,0,0x65c);
  param_1[0x259] = *param_1 + 0x11b4;
  param_1[0x90] = 0;
  param_1[0x8f] = 0;
  param_1[0x91] = 0;
  KBClearCommandValidTimes(param_1 + 0x25a);
  KBClearCommandLastTimes((int)(param_1 + 0x25a));
  KBISetFlip((int)(param_1 + 0x92),0);
  param_1[0x2fb] = 0;
  param_1[0x2fc] = -1;
  param_1[0x2fd] = 0;
  param_1[0x2fe] = 0;
  memset(param_1 + 0x2ff,0,0x200);
  iVar3 = 0;
  param_1[0x37f] = 0;
  param_1[0x380] = 1;
  param_1[0x381] = 0;
  param_1[0x382] = 1;
  param_1[899] = 1;
  param_1[900] = 0;
  param_1[0x385] = 0;
  param_1[0x387] = 0;
  param_1[0x386] = 0;
  param_1[0x388] = 0;
  param_1[0x389] = 1;
  param_1[0x38a] = 0;
  param_1[0x38b] = 0;
  param_1[0x38c] = 0;
  param_1[0x38d] = 0;
  param_1[0x38f] = 1;
  piVar6 = param_1 + 0x390;
  for (uVar4 = param_1[0x54] & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
    *piVar6 = 0;
    piVar6 = piVar6 + 1;
  }
  piVar6 = param_1 + 0x3cc;
  for (uVar4 = param_1[0x55] & 0x3fffffff; uVar4 != 0; uVar4 = uVar4 - 1) {
    *piVar6 = 0;
    piVar6 = piVar6 + 1;
  }
  iVar1 = param_1[0x452];
  param_1[0x3f4] = 0;
  param_1[0x3f5] = 0;
  param_1[0x3f6] = 0;
  param_1[0x3f7] = 0;
  param_1[0x3f8] = 0;
  param_1[0x3f9] = 0;
  param_1[0x3fa] = 0;
  param_1[0x3fb] = 0;
  param_1[0x3fc] = 0;
  param_1[0x3fd] = 0;
  piVar6 = param_1 + 0x3fe;
  for (iVar5 = 0x57; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar6 = 0;
    piVar6 = piVar6 + 1;
  }
  param_1[0x452] = iVar1;
  param_1[0x400] = 0xfff;
  param_1[0x411] = param_1[0x1e];
  piVar6 = g;
  param_1[0x3ff] = 0xfff;
  param_1[0x418] = 0x3eb33333;
  param_1[0x41e] = -0x39001000;
  param_1[0x41f] = -0x3f700000;
  piVar2 = piVar6;
  if ((uint)piVar6[0x7395] < 0x80000000) {
    do {
      *(undefined4 *)(iVar1 + iVar3 * 4) = 0xffffffff;
      iVar3 = iVar3 + 1;
      piVar2 = g;
    } while (iVar3 <= piVar6[0x7395]);
  }
  memset((void *)param_1[0x455],0,piVar2[0x7395] * 4 + 4);
  memset(param_1 + 0x456,0,0x1ec);
  memset(param_1 + 0x4d2,0,0x4c);
  param_1[0x4d4] = 0x3f800000;
  param_1[0x4d3] = 0x3f800000;
  iVar3 = param_1[0x4e5];
  param_1[0x4d7] = -32000;
  param_1[0x4e2] = -1;
  param_1[0x4e3] = 0x100;
  param_1[0x4e4] = 0;
  if (iVar3 != 0) {
    *(undefined4 *)(iVar3 + 0x18) = 0;
    *(undefined4 *)(iVar3 + 8) = 0;
    param_1[0x4e5] = 0;
  }
  param_1[0x4e6] = 0;
  param_1[0x4e7] = 0;
  param_1[0x4e8] = 0;
  param_1[0x4e9] = 0;
  param_1[0x4ea] = 0;
  param_1[0x4f0] = 0;
  PlayerSelfAnim(param_1,0);
  AnimResetAction((int *)param_1[0x4ef]);
  PalFXReset(param_1 + 0x977);
  PlayerResetAI((int)param_1);
  piVar6 = param_1 + 0xd0c;
  for (iVar3 = 10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar6 = 0;
    piVar6 = piVar6 + 1;
  }
  param_1[0xd0a] = 0;
  param_1[0xd09] = 0;
  param_1[0xd16] = 0;
  ClipboardClear((undefined4 *)param_1[0xd17]);
  return;
}

/* PlayerEnableSet @ 0x080b15d0, 348 bytes */
int PlayerEnableSet(int param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = g;
  iVar2 = g[param_1 + 0x73d9];
  if (*(int *)(iVar2 + 0x158) != param_2) {
    if (param_2 == 0) {
      if (g[0x7398] == 1) {
        g[0x7459] = 0;
        piVar3[0x745a] = -1;
      }
      else if (param_1 == g[0x7459]) {
        g[0x7459] = param_1 + 1;
        while( true ) {
          if ((piVar3[piVar3[0x7459] + 0x73d9] == 0) ||
             (bVar1 = true, *(int *)(piVar3[piVar3[0x7459] + 0x73d9] + 0x158) == 0)) {
            bVar1 = false;
          }
          if (bVar1) break;
          piVar3[0x7459] = piVar3[0x7459] + 1;
        }
      }
      else if (param_1 == g[0x745a]) {
        g[0x745a] = param_1 + -1;
        while( true ) {
          if ((piVar3[piVar3[0x745a] + 0x73d9] == 0) ||
             (bVar1 = true, *(int *)(piVar3[piVar3[0x745a] + 0x73d9] + 0x158) == 0)) {
            bVar1 = false;
          }
          if (bVar1) break;
          piVar3[0x745a] = piVar3[0x745a] + -1;
        }
      }
    }
    else if (g[0x7398] == 0) {
      g[0x745a] = param_1;
      piVar3[0x7459] = param_1;
    }
    else {
      if (param_1 < g[0x7459]) {
        g[0x7459] = param_1;
      }
      if (piVar3[0x745a] < param_1) {
        piVar3[0x745a] = param_1;
        piVar3 = g;
      }
    }
    *(int *)(piVar3[param_1 + 0x73d9] + 0x158) = param_2;
    if (param_2 == 0) {
      iVar2 = piVar3[0x7398] + -1;
    }
    else {
      iVar2 = piVar3[0x7398] + 1;
    }
    piVar3[0x7398] = iVar2;
  }
  return iVar2;
}

/* PlayerChangeState @ 0x080b1730, 152 bytes */
byte PlayerChangeState(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  
  bVar3 = true;
  if (param_2 != 0) {
    if (*(int **)(param_1 + 0xbec) == (int *)0x0) {
      iVar2 = ArrayAccessGrpItem(**(int **)(param_1 + 0xbe8),param_2,0);
      if (iVar2 == 0) {
        bVar3 = false;
      }
    }
    else {
      iVar2 = ArrayAccessGrpItem(**(int **)(param_1 + 0xbec),param_2,0);
      bVar3 = iVar2 != 0;
    }
  }
  uVar1 = *(undefined4 *)(param_1 + 0xbf4);
  *(int *)(param_1 + 0xbf4) = param_2;
  *(undefined4 *)(param_1 + 0xbf8) = uVar1;
  *(undefined4 *)(param_1 + 0xdfc) = 0;
  if (!bVar3) {
    VWarn(param_1,"changed to invalid state %i (from state %i)\n",*(undefined4 *)(param_1 + 0xbf4),
          uVar1);
  }
  return bVar3;
}

/* PlayerLifeSet @ 0x080b17d0, 242 bytes */
int * PlayerLifeSet(int param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int *extraout_EAX;
  int *extraout_EAX_00;
  int *piVar3;
  
  if (((g[0x7511] != 3) || (*(int *)(param_1 + 0xe24) == 0)) ||
     (piVar3 = (int *)g[0x508d], g[0x7514] < g[0x508d])) {
    uVar2 = 0xffffffffU - ((int)param_2 >> 0x1f) & param_2;
    *(uint *)(param_1 + 0x160) = uVar2;
    uVar1 = *(uint *)(param_1 + 0x164);
    if ((int)uVar1 < (int)uVar2) {
      *(uint *)(param_1 + 0x160) = uVar1;
      uVar2 = uVar1;
    }
    piVar3 = (int *)g[0x730b];
    if ((piVar3 != (int *)0x0) && (uVar2 == 0)) {
      *(undefined4 *)(param_1 + 0x160) = 1;
      uVar2 = 1;
    }
    if ((((int)uVar2 < 1) && (*(int *)(param_1 + 0x1c) == 1)) && (*(int *)(param_1 + 0x2628) != 1))
    {
      *(undefined4 *)(param_1 + 0x160) = 1;
      uVar2 = 1;
    }
    if ((((int)uVar2 < 1) && (*(int *)(param_1 + 0x1c) == 0)) && (piVar3 = g, g[0x7511] == 2)) {
      if (*(int *)(param_1 + 0x1014) == 0) {
        WinIconCheck((*(int *)(param_1 + 0xc) == 1) + 1,0,6);
        piVar3 = extraout_EAX_00;
      }
      else {
        WinIconCheckTeam(*(int *)(param_1 + 0xc),*(int *)(*(int *)(param_1 + 0x1014) + 0xc),
                         *(uint *)(param_1 + 0x1048));
        piVar3 = extraout_EAX;
      }
    }
  }
  return piVar3;
}

/* PlayerLifeSetNoIcon @ 0x080b18d0, 115 bytes */
void PlayerLifeSetNoIcon(int param_1,uint param_2)

{
  uint uVar1;
  
  if (((g[0x7511] != 3) || (*(int *)(param_1 + 0xe24) == 0)) || (g[0x7514] < g[0x508d])) {
    uVar1 = 0xffffffffU - ((int)param_2 >> 0x1f) & param_2;
    *(uint *)(param_1 + 0x160) = uVar1;
    if (*(int *)(param_1 + 0x164) < (int)uVar1) {
      *(int *)(param_1 + 0x160) = *(int *)(param_1 + 0x164);
    }
    if ((g[0x730b] != 0) && (*(int *)(param_1 + 0x160) == 0)) {
      *(undefined4 *)(param_1 + 0x160) = 1;
    }
  }
  return;
}

/* PlayerPowerSet @ 0x080b1950, 60 bytes */
void PlayerPowerSet(int param_1,uint param_2)

{
  uint *puVar1;
  uint *puVar2;
  uint uVar3;
  
  if (1 < g[0x7511] - 3U) {
    puVar1 = *(uint **)(param_1 + 0x170);
    uVar3 = 0xffffffffU - ((int)param_2 >> 0x1f) & param_2;
    puVar2 = *(uint **)(param_1 + 0x174);
    *puVar1 = uVar3;
    if ((int)*puVar2 < (int)uVar3) {
      *puVar1 = *puVar2;
    }
  }
  return;
}

/* PlayerChangeAnim @ 0x080b1990, 115 bytes */
void PlayerChangeAnim(int *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  if (param_1[0x4f0] == 0) {
    *(undefined4 *)param_1[0x4ef] = *(undefined4 *)(*param_1 + 0x11cc);
  }
  iVar1 = AnimChangeAction((int *)param_1[0x4ef],0,param_2);
  uVar2 = (uint)(iVar1 == 0);
  param_1[0xd16] = uVar2;
  if (uVar2 == 0) {
    AnimResetAction((int *)param_1[0x4ef]);
    return;
  }
  VWarn((int)param_1,"Changed to invalid action %i",param_2,uVar2);
  return;
}

/* PlayerChangeAnimElem @ 0x080b1a10, 164 bytes */
void PlayerChangeAnimElem(int *param_1,int param_2,int param_3)

{
  int iVar1;
  
  if (param_1[0x4f0] == 0) {
    *(undefined4 *)param_1[0x4ef] = *(undefined4 *)(*param_1 + 0x11cc);
  }
  iVar1 = AnimChangeActionElem((int *)param_1[0x4ef],0,param_2,param_3 + -1);
  param_1[0xd16] = (uint)(iVar1 == 0);
  if ((iVar1 == 0) != 0) {
    iVar1 = AnimChangeAction((int *)param_1[0x4ef],0,param_2);
    param_1[0xd16] = (uint)(iVar1 == 0);
    if ((iVar1 == 0) != 0) {
      VWarn((int)param_1,"Changed to invalid action %i");
      return;
    }
    VWarn((int)param_1,"Changed to invalid animelem %i within action %i",param_3,param_2);
  }
  return;
}

/* PlayerSelfAnim @ 0x080b1ac0, 27 bytes
 * FIXUP: return type set to void: only unaffected-register values were returned */
void PlayerSelfAnim(int *param_1,int param_2)

{
  undefined4 extraout_EAX;
  
  *(undefined4 *)param_1[0x4ef] = *(undefined4 *)(*param_1 + 0x11cc);
  PlayerChangeAnim(param_1,param_2);
  return;
}

/* PlayerSelfAnimElem @ 0x080b1ae0, 29 bytes */
void PlayerSelfAnimElem(int *param_1,int param_2,int param_3)

{
  *(undefined4 *)param_1[0x4ef] = *(undefined4 *)(*param_1 + 0x11cc);
  PlayerChangeAnimElem(param_1,param_2,param_3);
  return;
}

/* PlayerAutoTurn @ 0x080b1b00, 187 bytes
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
undefined4 PlayerAutoTurn(int param_1,int param_2,int param_3)

{
  float10 fVar1;
  int *piVar2;
  undefined4 uVar3;
  
  piVar2 = *(int **)(param_1 + 0xe0c);
  if ((*(int **)(param_1 + 0xe0c) != (int *)0x0) || (piVar2 = g, 2 < g[0x7511])) {
    fVar1 = (*(float *)(param_1 + 0x19c) - *(float *)(param_2 + 0x19c)) *
            (float10)*(int *)(param_1 + 400);
    piVar2 = (int *)CONCAT22((short)((uint)piVar2 >> 0x10),
                             (ushort)(fVar1 < 0.0) << 8 | (ushort)GHIDRA_ISNAN(fVar1) << 10 |
                             (ushort)(fVar1 == 0.0) << 0xe);
    if ((fVar1 >= 0.0 && (fVar1 == 0.0) == 0) && (*(char *)(param_1 + 0x207) == '\0')) {
      PlayerTurnAround(param_1);
      piVar2 = *(int **)(param_1 + 0xe00);
      if (piVar2 == (int *)0x1) {
        uVar3 = AnimChangeAction(*(int **)(param_1 + 0x13bc),0,5);
        return uVar3;
      }
      if (piVar2 == (int *)0x2) {
        uVar3 = AnimChangeAction(*(int **)(param_1 + 0x13bc),0,6);
        return uVar3;
      }
    }
  }
  return piVar2;
}

/* PlayerTurnAround @ 0x080b1bc0, 44 bytes
 * FIXUP: return type set to void: only unaffected-register values were returned */
void PlayerTurnAround(int param_1)

{
  int iVar1;
  undefined4 extraout_EAX;
  
  iVar1 = *(int *)(param_1 + 400);
  *(int *)(param_1 + 400) = -iVar1;
  KBISetFlip(param_1 + 0x248,(uint)(-iVar1 == -1));
  return;
}

/* PlayerUpdate @ 0x080b1bf0, 4338 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: stack-depth join lost: auStack_1c widened to frame_1c (0x40 bytes of headroom for pseudo-pushes)
 * FIXUP: 1 exact-text site patches
 * FIXUP: 7 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 2 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void PlayerUpdate(int *player)

{
  undefined2 uVar1;
  float10 fVar2;
  float10 fVar3;
  byte bVar4;
  int iVar5;
  int *piVar6;
  undefined3 extraout_var;
  int iVar7;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar8;
  int extraout_ECX_01;
  int extraout_ECX_02;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 uVar9;
  undefined1 *puVar10;
  int iVar12;
  undefined2 in_FPUControlWord;
  undefined1 frame_1c [0x40 + 20];
  undefined1 *puVar11;
  
  if (player[0x57] != 0) {
    return;
  }
  if (0 < player[0x40d]) {
    player[0x386] = 0;
    player[0x387] = 0;
  }
  if (0 < player[0x387]) {
    player[0x386] = player[0x387];
    player[0x387] = 0;
  }
  if (0 < player[0x386]) {
    player[0x386] = player[0x386] + -1;
  }
  iVar7 = 0x10a0;
  iVar12 = 7;
  do {
    if (((*(int *)((int)player + iVar7 + 8) != 0) &&
        (iVar5 = *(int *)((int)player + iVar7 + 0x14), iVar5 != -1)) &&
       (iVar5 = iVar5 + -1, *(int *)((int)player + iVar7 + 0x14) = iVar5, iVar5 < 1)) {
      *(undefined4 *)((int)player + iVar7 + 8) = 0;
    }
    iVar7 = iVar7 + 0x14;
    iVar12 = iVar12 + -1;
  } while (-1 < iVar12);
  iVar7 = player[0x41b];
  if ((iVar7 != 0) &&
     (((*(int *)(iVar7 + 0x158) == 0 || (*(int *)(iVar7 + 0xe2c) != g[0x7304])) ||
      ((piVar6 = PlayerFindTarget(*(int *)(iVar7 + 0x220),(int)player), piVar6 == (int *)0x0 ||
       (piVar6[7] == 0)))))) {
    player[0x41b] = 0;
  }
  if (player[0x386] == 0) {
    player[0x79] = 1;
    player[0x7a] = 1;
    player[0x7b] = 1;
    player[0x7c] = 1;
    player[0x4d4] = 0x3f800000;
    player[0x4d3] = 0x3f800000;
    player[0x4e0] = 0;
    player[0x4e2] = -1;
    player[0x4e3] = 0x100;
    player[0x4e4] = 0;
    player[0x7e] = 0;
    player[0x7d] = 0;
    player[0x80] = 0;
    player[0x7f] = 0;
    player[0x71] = 0;
    player[0x70] = 0;
    player[0x66] = 1;
    if ((player[7] == 1) && (player[0x98a] != 1)) {
      player[0x79] = 0;
      player[0x7b] = 0;
      player[0x7a] = 0;
      player[0x7c] = 0;
    }
    player[0x6a] = player[0x67];
    player[0x6b] = player[0x68];
    player[0x6c] = player[0x69];
  }
  if ((player[7] == 0) || ((player[7] == 1 && (player[0x98a] == 1)))) {
    PlayerSCtrlUpdateSpec(player,-3,3);
    PlayerSCtrlUpdateSpec(player,-2,7);
  }
  puVar10 = (frame_1c + 0x40);
  if (player[0x8f] != 0) goto LAB_080b1e2d;
  puVar11 = frame_1c + 0x40 - 0x10;  /* frame offset -0x2c */
  PlayerSCtrlUpdateSpec(player,-1,3);
  do {
    puVar10 = puVar11 + 0x10;
LAB_080b1e2d:
    iVar7 = 0;
    do {
      *(int **)(puVar10 + -0x10) = player;
      *(undefined4 *)(puVar10 + -0x14) = 0x80b1e39;
      iVar5 = PlayerSCtrlUpdate(*(int **)(puVar10 + -0x10));
      iVar12 = iVar7;
      if (iVar5 == 0) break;
      iVar12 = iVar7 + 1;
      if (0x9c4 < iVar7) {
        *(int *)(puVar10 + -0x10) = *player;
        *(int *)(puVar10 + -0x14) = player[0x2fd];
        *(undefined4 *)(puVar10 + -0x18) = 0x9c4;
        *(char **)(puVar10 + -0x1c) =
             "State machine stuck in loop (stopped after %i loops): %i for %s\nCheck your states for infinite ChangeState loops."
        ;
        *(int **)(puVar10 + -0x20) = g + 0x81d2;
        *(undefined4 *)(puVar10 + -0x24) = 0x80b1e71;
        sprintf(*(char **)(puVar10 + -0x20),*(char **)(puVar10 + -0x1c),*(int *)(puVar10 + -0x18),*(int *)(puVar10 + -0x14),*(char **)(puVar10 + -0x10));
        *(undefined4 *)(puVar10 + -4) = 0x80b1e79;
        ErrorExit();
      }
      iVar7 = iVar12;
    } while (keyflag[1] == 0);
    iVar7 = player[0x386];
    if (0 < iVar7) goto LAB_080b2b83;
    if (player[0x381] == 2) {
      fVar2 = GHIDRA_I2F(player[0x413]);
      if (fVar2 != 0.0) {
        player[0x413] = 0;
        player[0x67] = GHIDRA_F2I(int, (GHIDRA_I2F(player[0x67]) + fVar2));
      }
      fVar2 = GHIDRA_I2F(player[0x414]);
      if (fVar2 != 0.0) {
        player[0x414] = 0;
        player[0x68] = GHIDRA_F2I(int, (GHIDRA_I2F(player[0x68]) + fVar2));
      }
      fVar2 = GHIDRA_I2F(player[0x415]);
      if (fVar2 != 0.0) {
        player[0x415] = 0;
        player[0x69] = GHIDRA_F2I(int, (GHIDRA_I2F(player[0x69]) + fVar2));
      }
      player[0x40d] = player[0x40d] - 1U & 0xffffffffU - ((int)(player[0x40d] - 1U) >> 0x1f);
      if (player[0x40a] != 0) {
        *(int **)(puVar10 + -0x10) = player;
        *(undefined4 *)(puVar10 + -0x14) = 0x80b1f50;
        iVar7 = PlayerGetDamagedLife(*(int *)(puVar10 + -0x10));
        iVar12 = *(int *)(puVar10 + -0xc);
        *(int *)(puVar10 + -0xc) = iVar7;
        *(int **)(puVar10 + -0x10) = player;
        *(undefined4 *)(puVar10 + -0x14) = 0x80b1f59;
        PlayerLifeSetNoIcon(*(int *)(puVar10 + -0x10),*(uint *)(puVar10 + -0xc));
        player[0x40a] = 0;
      }
    }
    else {
      player[0x40a] = 0;
      player[0x419] = 0;
      player[0x405] = 0;
      player[0x412] = 0;
      player[0x41c] = 0;
      player[0x411] = player[0x1e];
      player[0x40c] = 0;
      player[0x40d] = 0;
      player[0x425] = 0;
      player[0x423] = 1;
      player[99] = GHIDRA_F2I(int, (100.0 / (float10)player[0x1c]));
    }
    if (player[0x65] != 0) {
      if (player[100] != player[0x65]) {
        *(int **)(puVar10 + -0x10) = player;
        *(undefined4 *)(puVar10 + -0x14) = 0x80b1ff5;
        PlayerTurnAround(*(int *)(puVar10 + -0x10));
      }
      player[0x65] = 0;
    }
    if ((char)player[0x83] != '\0') {
      player[0x66] = 0;
    }
    iVar7 = player[0x2fd];
    if (iVar7 == 0x98) {
LAB_080b234b:
      player[900] = 1;
LAB_080b2355:
      if (player[0x388] < 1) {
        player[0x67] = GHIDRA_F2I(int, (GHIDRA_I2F(player[0x67]) + GHIDRA_I2F(player[0x6d])));
        player[0x68] = GHIDRA_F2I(int, (GHIDRA_I2F(player[0x68]) + GHIDRA_I2F(player[0x6e])));
        player[0x69] = GHIDRA_F2I(int, (GHIDRA_I2F(player[0x69]) + GHIDRA_I2F(player[0x6f])));
      }
      else {
        player[0x388] = player[0x388] + -1;
      }
      if ((player[0x8e] != 0) && (g[0x74f3] != 1)) {
        fVar2 = GHIDRA_I2F(player[0x89]) * GHIDRA_I2F(player[0x8b]);
        player[0x67] = GHIDRA_F2I(int, (GHIDRA_I2F(player[0x67]) + GHIDRA_I2F(player[0x89])));
        player[0x89] = GHIDRA_F2I(int, fVar2);
        player[0x68] = GHIDRA_F2I(int, (GHIDRA_I2F(player[0x68]) + GHIDRA_I2F(player[0x8a])));
        player[0x8a] = GHIDRA_F2I(int, (GHIDRA_I2F(player[0x8a]) * GHIDRA_I2F(player[0x8c])));
        if (fVar2 < 0.0) {
          fVar2 = fVar2 * -1.0;
        }
        if (fVar2 < GHIDRA_I2F(player[0x8d])) {
          player[0x8e] = 0;
        }
        iVar7 = player[0x8e];
        if (0 < iVar7) {
          iVar7 = iVar7 + -1;
          player[0x8e] = iVar7;
        }
        if (iVar7 == 0) {
          player[0x8a] = 0;
          player[0x89] = 0;
        }
      }
      iVar7 = player[0x382];
      if (iVar7 == 1) {
        fVar2 = GHIDRA_I2F(player[0x6d]);
        fVar3 = GHIDRA_I2F(player[0x4d]);
        player[0x6d] = GHIDRA_F2I(int, (fVar2 * fVar3));
        *(undefined2 *)(puVar10 + 0x10) = in_FPUControlWord;
        puVar10[0x11] = 0xc;
        *(undefined4 *)(puVar10 + 0x10) = *(undefined4 *)(puVar10 + 0x10);
        *(int *)(puVar10 + 0xc) = (int)GHIDRA_FIST32(fVar2 * fVar3);
        uVar1 = *(undefined2 *)(puVar10 + 0x10);
        if (*(int *)(puVar10 + 0xc) == 0) {
          player[0x6d] = 0;
        }
        fVar2 = GHIDRA_I2F(player[0x6f]);
        fVar3 = GHIDRA_I2F(player[0x4d]);
        player[0x6f] = GHIDRA_F2I(int, (fVar2 * fVar3));
        *(undefined2 *)(puVar10 + 0x10) = uVar1;
        puVar10[0x11] = 0xc;
        *(undefined4 *)(puVar10 + 0x10) = *(undefined4 *)(puVar10 + 0x10);
        *(int *)(puVar10 + 0xc) = (int)GHIDRA_FIST32(fVar2 * fVar3);
        in_FPUControlWord = *(undefined2 *)(puVar10 + 0x10);
        if (*(int *)(puVar10 + 0xc) == 0) {
          player[0x6f] = 0;
        }
        iVar7 = player[0x382];
      }
      if (iVar7 == 2) {
        iVar7 = player[0x382];
        player[0x6d] = GHIDRA_F2I(int, (GHIDRA_I2F(player[0x6d]) * GHIDRA_I2F(player[0x4e])));
      }
      if (iVar7 == 3) {
        fVar2 = GHIDRA_I2F(player[0x6e]);
        player[0x6e] = GHIDRA_F2I(int, (fVar2 + GHIDRA_I2F(player[0x4c])));
        if (((player[0x2fd] != 0x69) && (0.0 < fVar2 + GHIDRA_I2F(player[0x4c]))) &&
           (0.0 <= GHIDRA_I2F(player[0x68]))) {
          *(int *)(puVar10 + -4) = iVar12;
          *(int *)(puVar10 + -8) = iVar12;
          *(undefined4 *)(puVar10 + -0xc) = 0x34;
          *(int **)(puVar10 + -0x10) = player;
          *(undefined4 *)(puVar10 + -0x14) = 0x80b2568;
          PlayerChangeState(*(int *)(puVar10 + -0x10),*(int *)(puVar10 + -0xc));
          player[0x70] = 0;
          goto LAB_080b1e2d;
        }
      }
      iVar7 = player[0x58];
      if (iVar7 < 1) {
        iVar12 = 0;
        if (player[0x389] != 0) {
          if (nokoflag_0 != 0) {
            nokoflag_0 = (int)*(char *)((int)g + 0x1d38e);
          }
          piVar6 = g;
          if ((*(char *)((int)g + 0x1d38f) == '\0') && (nokoflag_0 == 0)) {
            *(undefined4 *)(puVar10 + -0x1c) = 0;
            *(int **)(puVar10 + -0x20) = player;
            *(undefined4 *)(puVar10 + -0x24) = 0x80b25d6;
            iVar7 = PlayerSndID(*(int *)(puVar10 + -0x20),*(int *)(puVar10 + -0x1c));
            *(int *)(puVar10 + -0x10) = iVar7;
            *(undefined4 *)(puVar10 + -0x14) = 0x80b25df;
            SndIDStop(*(int *)(puVar10 + -0x10));
            *(undefined4 *)(puVar10 + -0xc) = *(undefined4 *)(*player + 0x11d0);
            *(undefined4 *)(puVar10 + -0x10) = 0;
            *(undefined4 *)(puVar10 + -0x14) = 0xb;
            *(undefined4 *)(puVar10 + -0x18) = *(undefined4 *)(*player + 0x11d4);
            fVar2 = GHIDRA_I2F(player[0x4d5]);
            *(undefined2 *)(puVar10 + 0x10) = in_FPUControlWord;
            puVar10[0x11] = 0xc;
            *(undefined4 *)(puVar10 + 0x10) = *(undefined4 *)(puVar10 + 0x10);
            *(int *)(puVar10 + 0xc) = (int)GHIDRA_FIST32(fVar2);
            in_FPUControlWord = *(undefined2 *)(puVar10 + 0x10);
            *(undefined4 *)(puVar10 + -0x1c) = *(undefined4 *)(puVar10 + 0xc);
            *(undefined4 *)(puVar10 + -0x20) = 0xffffffff;
            *(undefined4 *)(puVar10 + -0x24) = 0x80b2626;
            piVar6 = (int *)GameSndPlayIDPos(*(int *)(puVar10 + -0x20),*(int *)(puVar10 + -0x1c),
                                             *(int **)(puVar10 + -0x18),*(int *)(puVar10 + -0x14),
                                             *(int *)(puVar10 + -0x10),*(int *)(puVar10 + -0xc));
            iVar7 = extraout_ECX_01;
          }
          if (nokoflag_0 == 0) {
            nokoflag_0 = 1;
            player[0x389] = 0;
            player[0x38a] = 0;
            player[899] = 0;
            if (player[0x381] != 2) {
              *(undefined4 *)(puVar10 + -4) = 0;
              *(undefined4 *)(puVar10 + -8) = 0;
              *(undefined4 *)(puVar10 + -0xc) = 0x13a6;
              *(int **)(puVar10 + -0x10) = player;
              *(undefined4 *)(puVar10 + -0x14) = 0x80b2675;
              bVar4 = PlayerChangeState(*(int *)(puVar10 + -0x10),*(int *)(puVar10 + -0xc));
              piVar6 = (int *)GHIDRA_ZEXT8(bVar4);
              player[0x416] = -0x3fcccccd;
              player[0x417] = -0x3fa00000;
              player[0x41c] = 1;
            }
            *(int **)(puVar10 + -4) = piVar6;
            *(int **)(puVar10 + -8) = piVar6;
            *(undefined4 *)(puVar10 + -0xc) = 0;
            *(int **)(puVar10 + -0x10) = player;
            *(undefined4 *)(puVar10 + -0x14) = 0x80b26a0;
            PlayerDropBoundTargets(*(int *)(puVar10 + -0x10),*(int **)(puVar10 + -0xc));
            *(int *)(puVar10 + -0xc) = player[1];
            *(int *)(puVar10 + -0x10) = g[0x52be];
            *(undefined4 *)(puVar10 + -0x14) = 0x80b26b7;
            ExplodRemoveGetHit(*(undefined4 **)(puVar10 + -0x10),*(int *)(puVar10 + -0xc));
            iVar7 = extraout_ECX_02;
          }
          goto LAB_080b26ba;
        }
      }
      else {
LAB_080b26ba:
        iVar12 = player[0x389];
      }
      if (iVar12 == 0) {
        iVar12 = player[0x38a] + 1;
        player[0x38a] = iVar12;
        if (player[0x51] != 0) {
          if ((iVar12 == 0x14) && (*(char *)((int)g + 0x1d38f) == '\0')) {
            *(int *)(puVar10 + -4) = iVar7;
            *(int *)(puVar10 + -8) = iVar7;
            *(int *)(puVar10 + -0xc) = *(int *)(*player + 0x11d0) + -0x3c;
            *(undefined4 *)(puVar10 + -0x10) = 0;
            *(undefined4 *)(puVar10 + -0x14) = 0xb;
            *(undefined4 *)(puVar10 + -0x18) = *(undefined4 *)(*player + 0x11d4);
            fVar2 = GHIDRA_I2F(player[0x4d5]);
            *(undefined2 *)(puVar10 + 0x10) = in_FPUControlWord;
            puVar10[0x11] = 0xc;
            *(undefined4 *)(puVar10 + 0x10) = *(undefined4 *)(puVar10 + 0x10);
            *(int *)(puVar10 + 0xc) = (int)GHIDRA_FIST32(fVar2);
            in_FPUControlWord = *(undefined2 *)(puVar10 + 0x10);
            *(undefined4 *)(puVar10 + -0x1c) = *(undefined4 *)(puVar10 + 0xc);
            *(undefined4 *)(puVar10 + -0x20) = 0xffffffff;
            *(undefined4 *)(puVar10 + -0x24) = 0x80b2741;
            iVar12 = GameSndPlayIDPos(*(int *)(puVar10 + -0x20),*(int *)(puVar10 + -0x1c),
                                      *(int **)(puVar10 + -0x18),*(int *)(puVar10 + -0x14),
                                      *(int *)(puVar10 + -0x10),*(int *)(puVar10 + -0xc));
          }
          if ((player[0x38a] == 0x32) && (*(char *)((int)g + 0x1d38f) == '\0')) {
            *(int *)(puVar10 + -4) = iVar12;
            *(int *)(puVar10 + -8) = iVar12;
            *(int *)(puVar10 + -0xc) = *(int *)(*player + 0x11d0) + -0x78;
            *(undefined4 *)(puVar10 + -0x10) = 0;
            *(undefined4 *)(puVar10 + -0x14) = 0xb;
            *(undefined4 *)(puVar10 + -0x18) = *(undefined4 *)(*player + 0x11d4);
            fVar2 = GHIDRA_I2F(player[0x4d5]);
            *(undefined2 *)(puVar10 + 0x10) = in_FPUControlWord;
            puVar10[0x11] = 0xc;
            *(undefined4 *)(puVar10 + 0x10) = *(undefined4 *)(puVar10 + 0x10);
            *(int *)(puVar10 + 0xc) = (int)GHIDRA_FIST32(fVar2);
            *(undefined4 *)(puVar10 + -0x1c) = *(undefined4 *)(puVar10 + 0xc);
            *(undefined4 *)(puVar10 + -0x20) = 0xffffffff;
            *(undefined4 *)(puVar10 + -0x24) = 0x80b27a6;
            GameSndPlayIDPos(*(int *)(puVar10 + -0x20),*(int *)(puVar10 + -0x1c),
                             *(int **)(puVar10 + -0x18),*(int *)(puVar10 + -0x14),
                             *(int *)(puVar10 + -0x10),*(int *)(puVar10 + -0xc));
          }
        }
        if (player == (int *)g[0x73da]) {
          if (g[0x73dc] == 0) {
            piVar6 = (int *)0x0;
            goto LAB_080b27cb;
          }
LAB_080b27fe:
          player[0x7c] = 0;
        }
        else {
          piVar6 = (int *)g[0x73dc];
LAB_080b27cb:
          if ((player == piVar6) && ((int *)g[0x73da] != (int *)0x0)) goto LAB_080b27fe;
          if (player == (int *)g[0x73db]) {
            if (g[0x73dd] != 0) goto LAB_080b27fe;
            piVar6 = (int *)0x0;
          }
          else {
            piVar6 = (int *)g[0x73dd];
          }
          if ((player == piVar6) && ((int *)g[0x73db] != (int *)0x0)) goto LAB_080b27fe;
        }
        *(int **)(puVar10 + -0x10) = player;
        *(undefined4 *)(puVar10 + -0x14) = 0x80b2811;
        iVar7 = PlayerLyingDead(*(int *)(puVar10 + -0x10));
        if (9 < iVar7) {
          if (player == (int *)g[0x73da]) {
            if (g[0x73dc] == 0) {
              piVar6 = (int *)0x0;
              goto LAB_080b283b;
            }
          }
          else {
            piVar6 = (int *)g[0x73dc];
LAB_080b283b:
            if ((player != piVar6) || ((int *)g[0x73da] == (int *)0x0)) {
              if (player == (int *)g[0x73db]) {
                if (g[0x73dd] != 0) goto LAB_080b286e;
                piVar6 = (int *)0x0;
              }
              else {
                piVar6 = (int *)g[0x73dd];
              }
              if ((player != piVar6) || ((int *)g[0x73db] == (int *)0x0)) goto LAB_080b288c;
            }
          }
LAB_080b286e:
          player[0x79] = 0;
          player[0x7b] = 0;
          player[0x7a] = 0;
        }
      }
LAB_080b288c:
      if (player[0x401] == 0) {
        player[0x3ff] = 0xfff;
      }
      if (player[0x402] == 0) {
        player[0x400] = 0xfff;
      }
      if (0 < player[0x401]) {
        player[0x401] = player[0x401] + -1;
      }
      if (0 < player[0x402]) {
        player[0x402] = player[0x402] + -1;
      }
      if (g[0x731d] == 1) {
        *(int **)(puVar10 + -0x10) = player;
        *(undefined4 *)(puVar10 + -0x14) = 0x80b28f1;
        iVar7 = PlayerLyingDead(*(int *)(puVar10 + -0x10));
        if (0x3b < iVar7) {
          *(int **)(puVar10 + -0x10) = player;
          *(undefined4 *)(puVar10 + -0x14) = 0x80b2902;
          iVar7 = PlayerLyingDead(*(int *)(puVar10 + -0x10));
          if (iVar7 < 0x5a) {
            player[0x66] = player[0x37f] >> 2 & 1;
          }
        }
        *(int **)(puVar10 + -0x10) = player;
        *(undefined4 *)(puVar10 + -0x14) = 0x80b2925;
        iVar7 = PlayerLyingDead(*(int *)(puVar10 + -0x10));
        if (0x59 < iVar7) {
          *(int **)(puVar10 + -0x10) = player;
          *(undefined4 *)(puVar10 + -0x14) = 0x80b2936;
          iVar7 = PlayerLyingDead(*(int *)(puVar10 + -0x10));
          if (iVar7 < 0x78) {
            player[0x66] = player[0x37f] >> 1 & 1;
          }
        }
        *(int **)(puVar10 + -0x10) = player;
        *(undefined4 *)(puVar10 + -0x14) = 0x80b2958;
        iVar7 = PlayerLyingDead(*(int *)(puVar10 + -0x10));
        if (0x77 < iVar7) {
          *(int **)(puVar10 + -0x10) = player;
          *(undefined4 *)(puVar10 + -0x14) = 0x80b2969;
          iVar7 = PlayerLyingDead(*(int *)(puVar10 + -0x10));
          if (iVar7 < 0x96) {
            player[0x66] = (uint)((player[0x37f] & 3U) == 1);
          }
        }
        *(int **)(puVar10 + -0x10) = player;
        *(undefined4 *)(puVar10 + -0x14) = 0x80b2991;
        iVar7 = PlayerLyingDead(*(int *)(puVar10 + -0x10));
        if (0x95 < iVar7) {
          *(int **)(puVar10 + -0x10) = player;
          *(undefined4 *)(puVar10 + -0x14) = 0x80b29a4;
          iVar7 = PlayerLyingDead(*(int *)(puVar10 + -0x10));
          if (iVar7 < 0xb4) {
            player[0x66] = (uint)((player[0x37f] & 7U) == 1);
          }
        }
        *(int **)(puVar10 + -0x10) = player;
        *(undefined4 *)(puVar10 + -0x14) = 0x80b29cc;
        iVar7 = PlayerLyingDead(*(int *)(puVar10 + -0x10));
        if (0xb3 < iVar7) {
          player[0x66] = 0;
        }
      }
      if (player[0x381] == 0) {
        player[0x385] = player[0x385] + 1;
      }
      else {
        player[0x385] = 0;
      }
      if (g[0x33ae] == 3) {
        *(int **)(puVar10 + -0x10) = player;
        *(undefined4 *)(puVar10 + -0x14) = 0x80b2a25;
        iVar7 = PlayerLyingDead(*(int *)(puVar10 + -0x10));
        if (0x59 < iVar7) {
          player[0x2fd] = 0x1400;
          player[0x37f] = -1;
          player[0x58] = player[0x59];
          player[0x389] = 1;
          player[0x404] = 0;
          player[0x403] = 0;
        }
        iVar7 = player[0x385];
        if (0x1e < iVar7) {
          if (*(int *)player[0x5c] < *(int *)player[0x5d]) {
            *(int *)player[0x5c] = *(int *)player[0x5d];
            iVar7 = player[0x385];
          }
        }
        if ((0x3c < iVar7) && (player[0x58] < player[0x59])) {
          player[0x58] = player[0x59];
        }
      }
      player[0x37f] = player[0x37f] + 1;
      if (player[0x38c] != 0) {
        player[0x38d] = player[0x38d] + 1;
      }
      if ((-1 < player[0x40e]) && (player[0x40d] == 0)) {
        player[0x40e] = player[0x40e] + -1;
      }
      if (player[0x41c] == 0) {
        iVar7 = player[0x381];
      }
      else {
        iVar7 = player[0x381];
        if (iVar7 == 2) {
          player[0x421] = player[0x421] + 1;
        }
      }
      if (iVar7 == 2) {
        player[0x454] = 0;
      }
      else {
        player[0x454] = player[0x454] + 1;
      }
      iVar7 = g[0x74f3];
      if (iVar7 == -1) {
        if (player[0x381] == 2) {
          player[0x78] = 0;
          player[0x77] = 0;
        }
      }
      else if (0 < player[iVar7 + 0x77]) {
        player[iVar7 + 0x77] = player[iVar7 + 0x77] + -1;
      }
      iVar7 = player[0x386];
LAB_080b2b83:
      if (iVar7 == 0) {
        player[0x70] = player[0x70] + player[100] * player[0x52];
        player[0x71] = player[0x71] + player[0x53];
      }
      *(int **)(puVar10 + -0x10) = player;
      *(undefined4 *)(puVar10 + -0x14) = 0x80b2bc1;
      StageBound(*(int *)(puVar10 + -0x10));
      *(undefined4 *)(puVar10 + -0x14) = 0x80b2bc6;
      CameraMoveP();
      *(int **)(puVar10 + -0x10) = player;
      *(undefined4 *)(puVar10 + -0x14) = 0x80b2bce;
      PlayerCalcDraw(*(int *)(puVar10 + -0x10));
      player[0x86] = player[0x86] + 1;
      *(int *)(puVar10 + -0x10) = player[0x88];
      *(undefined4 *)(puVar10 + -0x14) = 0x80b2be8;
      piVar6 = (int *)ArrayScanFirst(*(int *)(puVar10 + -0x10));
      while (piVar6 != (int *)0x0) {
        iVar7 = *piVar6;
        piVar6[7] = piVar6[6];
        if ((*(int *)(iVar7 + 0xe04) == 2) && (piVar6[6] != 0)) {
          *(int *)(puVar10 + -4) = player[100] * piVar6[3];
          iVar12 = *(int *)(puVar10 + -4);
          *(int **)(iVar7 + 0x106c) = player;
          *(float *)(iVar7 + 0x19c) = (float10)iVar12 + GHIDRA_I2F(player[0x67]);
          *(float *)(iVar7 + 0x1a0) = (float10)piVar6[4] + GHIDRA_I2F(player[0x68]);
          *(float *)(iVar7 + 0x1a4) = (float10)piVar6[5] + GHIDRA_I2F(player[0x69]);
          *(int *)(iVar7 + 0x1b4) = player[0x6d];
          *(int *)(iVar7 + 0x1b8) = player[0x6e];
          *(int *)(iVar7 + 0x1bc) = player[0x6f];
          *(undefined4 *)(iVar7 + 0x1054) = 0;
          *(undefined4 *)(iVar7 + 0x1050) = 0;
          *(undefined4 *)(iVar7 + 0x104c) = 0;
          if (*(int *)(iVar7 + 0xe20) < 1) {
            *(undefined4 *)(iVar7 + 0xe20) = 1;
          }
          if (0 < piVar6[6]) {
            piVar6[6] = piVar6[6] + -1;
          }
        }
        *(int *)(puVar10 + -0x10) = player[0x88];
        *(undefined4 *)(puVar10 + -0x14) = 0x80b2cbe;
        piVar6 = (int *)ArrayScanNext(*(int *)(puVar10 + -0x10));
      }
      player[0x38b] = g[0x7304];
      return;
    }
    if (iVar7 < 0x99) {
      if (iVar7 == 0x83) {
LAB_080b2150:
        iVar7 = player[0x1c];
        player[900] = 1;
LAB_080b233d:
        player[99] = GHIDRA_F2I(int, (100.0 / (float10)iVar7));
        goto LAB_080b2355;
      }
      if (iVar7 < 0x84) {
        if (iVar7 == 0x78) goto LAB_080b234b;
        if (iVar7 < 0x79) {
          if ((iVar7 == 0x28) && (player[0x37f] == 0)) {
            player[0x74] = player[0x44];
          }
        }
        else if (iVar7 == 0x82) goto LAB_080b2150;
        goto LAB_080b2355;
      }
      if (iVar7 != 0x8c) {
        if (iVar7 < 0x8d) {
          if (iVar7 == 0x84) goto LAB_080b2150;
        }
        else if ((iVar7 == 0x96) || (iVar7 == 0x97)) goto LAB_080b234b;
        goto LAB_080b2355;
      }
      player[900] = 1;
      player[99] = GHIDRA_F2I(int, (100.0 / (float10)player[0x1c]));
      *(int *)(puVar10 + -0x10) = player[0x4ef];
      *(undefined4 *)(puVar10 + -0x14) = 0x80b218a;
      iVar7 = AnimGetLooptime(*(undefined4 **)(puVar10 + -0x10));
      if (player[0x37f] < iVar7) goto LAB_080b2355;
      iVar7 = player[0x380];
      uVar8 = extraout_ECX;
      uVar9 = extraout_EDX;
      if (iVar7 == 1) {
        *(int *)(puVar10 + -4) = iVar12;
        *(int *)(puVar10 + -8) = iVar12;
        *(undefined4 *)(puVar10 + -0xc) = 0;
        *(int **)(puVar10 + -0x10) = player;
        *(undefined4 *)(puVar10 + -0x14) = 0x80b21ae;
        PlayerChangeState(*(int *)(puVar10 + -0x10),*(int *)(puVar10 + -0xc));
        iVar7 = player[0x380];
        uVar8 = extraout_ECX_00;
        uVar9 = extraout_EDX_00;
      }
      if (iVar7 == 2) {
        *(undefined4 *)(puVar10 + -4) = uVar8;
        *(undefined4 *)(puVar10 + -8) = uVar8;
        *(undefined4 *)(puVar10 + -0xc) = 0xb;
        *(int **)(puVar10 + -0x10) = player;
        *(undefined4 *)(puVar10 + -0x14) = 0x80b21c6;
        PlayerChangeState(*(int *)(puVar10 + -0x10),*(int *)(puVar10 + -0xc));
        iVar7 = player[0x380];
        uVar9 = extraout_EDX_01;
      }
      if (iVar7 == 3) {
        *(undefined4 *)(puVar10 + -4) = uVar9;
        *(undefined4 *)(puVar10 + -8) = uVar9;
        *(undefined4 *)(puVar10 + -0xc) = 0x33;
        *(int **)(puVar10 + -0x10) = player;
        *(undefined4 *)(puVar10 + -0x14) = 0x80b21de;
        PlayerChangeState(*(int *)(puVar10 + -0x10),*(int *)(puVar10 + -0xc));
      }
      player[0x419] = 0;
      player[0x405] = 0;
      player[0x412] = 0;
      goto LAB_080b1e2d;
    }
    if (iVar7 == 0x13ec) {
      if (player[0x37f] == 0) {
        if (0 < player[0x40c]) {
          player[0x411] = player[0x411] >> 1;
        }
        iVar12 = player[0x40c] + 1;
        player[0x40c] = iVar12;
        player[99] = GHIDRA_F2I(int, (GHIDRA_I2F(player[99]) * GHIDRA_I2F(player[0x1d])));
      }
      if (player[0x411] < 0xb) {
        player[0x3ff] = 0;
        player[0x401] = -1;
      }
      goto LAB_080b2355;
    }
    if (iVar7 < 0x13ed) {
      if (((iVar7 == 0x9a) || (iVar7 < 0x9a)) || (iVar7 == 0x9b)) goto LAB_080b234b;
      if ((iVar7 == 0x13ce) && (player[0x37f] == 0)) {
        iVar12 = player[0x40c] + 1;
        player[0x40c] = iVar12;
        player[99] = GHIDRA_F2I(int, (GHIDRA_I2F(player[99]) * GHIDRA_I2F(player[0x1d])));
      }
      goto LAB_080b2355;
    }
    if (iVar7 == 0x1400) {
      iVar12 = player[0x37f];
      if (iVar12 == 0) {
        player[99] = GHIDRA_F2I(int, (100.0 / (float10)player[0x1c]));
      }
      player[0x419] = 0;
      player[0x405] = 0;
      player[0x412] = 0;
      goto LAB_080b2355;
    }
    if (0x1400 < iVar7) {
      if (iVar7 == 0x1450) {
        iVar7 = player[0x37f];
      }
      else {
        if (iVar7 != 0x145a) goto LAB_080b2355;
        iVar7 = player[0x37f];
      }
      if (iVar7 == 0) {
        iVar7 = player[0x1c];
        goto LAB_080b233d;
      }
      goto LAB_080b2355;
    }
    if (iVar7 != 0x13f6) goto LAB_080b2355;
    iVar7 = player[0x411];
    if (((0 < iVar7) || (player[0x389] == 0)) || (player[0x37f] < 1)) {
      if (0 < iVar7) {
        player[0x411] = iVar7 + -1;
      }
      goto LAB_080b2355;
    }
    iVar7 = player[0x1e];
    player[0x411] = iVar7;
    *(int *)(puVar10 + -4) = iVar7;
    *(int *)(puVar10 + -8) = iVar7;
    *(undefined4 *)(puVar10 + -0xc) = 0x1400;
    puVar11 = puVar10 + -0x10;
    *(int **)(puVar10 + -0x10) = player;
    *(undefined4 *)(puVar10 + -0x14) = 0x80b22cb;
    PlayerChangeState(*(int *)(puVar10 + -0x10),*(int *)(puVar10 + -0xc));
  } while( true );
}

/* PlayerUpdateBindTo @ 0x080b2cf0, 185 bytes
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
undefined4 PlayerUpdateBindTo(int param_1)

{
  undefined4 uVar1;
  undefined4 in_ECX;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 400);
  if (*(int *)(param_1 + 0x3430) != 0) {
    if (*(int **)(param_1 + 0x3440) != (int *)0x0) {
      iVar2 = **(int **)(param_1 + 0x3440);
      if (*(int *)(param_1 + 0x3444) != 0) {
        *(int *)(param_1 + 400) = iVar2 * *(int *)(param_1 + 0x3444);
      }
    }
    if (*(float **)(param_1 + 0x3434) != (float *)0x0) {
      *(float *)(param_1 + 0x19c) =
           (float10)iVar2 * *(float *)(param_1 + 0x3448) + **(float **)(param_1 + 0x3434);
    }
    if (*(float **)(param_1 + 0x3438) != (float *)0x0) {
      *(float *)(param_1 + 0x1a0) = **(float **)(param_1 + 0x3438) + *(float *)(param_1 + 0x344c);
    }
    if (*(float **)(param_1 + 0x343c) != (float *)0x0) {
      *(float *)(param_1 + 0x1a4) = **(float **)(param_1 + 0x343c) + *(float *)(param_1 + 0x3450);
    }
    if (0 < *(int *)(param_1 + 0x3430)) {
      *(int *)(param_1 + 0x3430) = *(int *)(param_1 + 0x3430) + -1;
    }
    StageBound(param_1);
    CameraMoveP();
    uVar1 = PlayerCalcDraw(param_1);
    return uVar1;
  }
  return in_ECX;
}

/* ScreenBound @ 0x080b2db0, 328 bytes
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void ScreenBound(int param_1)

{
  int iVar1;
  float10 fVar2;
  int iVar3;
  int iVar4;
  
  if ((g[0x731d] != 1) || (*(int *)(param_1 + 0xe24) != 0)) {
    iVar3 = PlayerGetWidth(param_1,3,4);
    iVar4 = PlayerGetWidth(param_1,4,4);
    if (*(int *)(param_1 + 0xe00) == 3) {
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 1;
    }
    if (*(int *)(param_1 + 0xe00) == 4) {
      iVar4 = iVar4 + 2;
      iVar3 = iVar3 + 2;
    }
    iVar1 = (int)GHIDRA_FIST32((float)(g[0x10a3] + -0xa0) / *(float *)(param_1 + 0x1348) + (float)g[0x7311]
                       + 160.0);
    *(int *)(param_1 + 0x1d4) = iVar1;
    fVar2 = (float)(iVar1 + iVar3);
    if (*(float *)(param_1 + 0x19c) < fVar2) {
      *(float *)(param_1 + 0x19c) = fVar2;
    }
    iVar3 = (int)GHIDRA_FIST32((float)(0xa0 - g[0x10a2]) / *(float *)(param_1 + 0x1348) + (float)g[0x7311] +
                       160.0);
    *(int *)(param_1 + 0x1d8) = iVar3;
    fVar2 = (float)(iVar3 - iVar4);
    if (fVar2 < *(float *)(param_1 + 0x19c)) {
      *(float *)(param_1 + 0x19c) = fVar2;
    }
  }
  return;
}

/* StageBound @ 0x080b2f00, 157 bytes
 * FIXUP: 5 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 2 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void StageBound(int param_1)

{
  float10 fVar1;
  float10 fVar2;
  int *piVar3;
  
  piVar3 = g;
  if ((g[0x731d] != 1) || (*(int *)(param_1 + 0xe24) != 0)) {
    fVar2 = (float)g[0x1099];
    fVar1 = *(float *)(param_1 + 0x19c);
    if (fVar1 < fVar2) {
      *(float *)(param_1 + 0x19c) = fVar2;
      fVar1 = fVar2;
    }
    if ((float10)piVar3[0x109a] < fVar1) {
      *(float *)(param_1 + 0x19c) = (float10)piVar3[0x109a];
      piVar3 = g;
    }
    fVar2 = (float10)piVar3[0x109b];
    fVar1 = *(float *)(param_1 + 0x1a4);
    if (fVar1 < fVar2) {
      *(float *)(param_1 + 0x1a4) = fVar2;
      piVar3 = g;
      fVar1 = fVar2;
    }
    if ((float10)piVar3[0x109c] < fVar1) {
      *(float *)(param_1 + 0x1a4) = (float10)piVar3[0x109c];
      return;
    }
  }
  return;
}

/* GameClsnUpdate @ 0x080b2fa0, 1167 bytes */
void GameClsnUpdate(void)

{
  int iVar1;
  int *piVar2;
  bool bVar3;
  undefined4 uVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  int *piVar11;
  int *piVar12;
  
  piVar9 = g;
  iVar8 = 0;
  iVar5 = g[0x7459];
  if (iVar5 <= g[0x745a]) {
    iVar7 = iVar5 * 4 + 0x1cf60;
    iVar10 = 0x1d160;
    do {
      iVar1 = *(int *)(iVar7 + 4 + (int)piVar9);
      if ((iVar1 == 0) || (bVar3 = true, *(int *)(iVar1 + 0x158) == 0)) {
        bVar3 = false;
      }
      if ((bVar3) && (*(int *)(*(int *)(iVar1 + 0x13bc) + 0x10) != 0)) {
        *(int *)(iVar10 + 0xc + (int)piVar9) = iVar1;
        iVar10 = iVar10 + 4;
        iVar8 = iVar8 + 1;
      }
      iVar5 = iVar5 + 1;
      iVar7 = iVar7 + 4;
    } while (iVar5 <= piVar9[0x745a]);
  }
  piVar9[iVar8 + 0x745b] = 0;
  iVar5 = piVar9[0x745b];
  piVar9[0x749c] = iVar8;
  piVar9 = piVar9 + 0x745b;
  while (iVar5 != 0) {
    if (0 < *(int *)(iVar5 + 0xff8)) {
      *(int *)(iVar5 + 0xff8) = *(int *)(iVar5 + 0xff8) + -1;
    }
    piVar9 = piVar9 + 1;
    *(undefined4 *)(iVar5 + 0x1344) = 0;
    iVar5 = *piVar9;
  }
  piVar9 = g + 0x745b;
  iVar5 = g[0x745b];
  while (iVar5 != 0) {
    piVar6 = piVar9 + 1;
    iVar8 = piVar9[1];
    while (iVar8 != 0) {
      iVar7 = PlayerAreEnemies(iVar5,iVar8);
      if (iVar7 != 0) {
        PlayerPushCheck(iVar5,iVar8,0);
      }
      piVar6 = piVar6 + 1;
      iVar8 = *piVar6;
    }
    piVar9 = piVar9 + 1;
    iVar5 = *piVar9;
  }
  piVar9 = g + 0x745b;
  piVar6 = (int *)g[0x745b];
  while (piVar6 != (int *)0x0) {
    piVar11 = piVar9 + 1;
    piVar12 = (int *)piVar9[1];
    while (piVar12 != (int *)0x0) {
      iVar5 = PlayerAreEnemies((int)piVar6,(int)piVar12);
      if (iVar5 != 0) {
        iVar5 = PlayerCheckReversal((int)piVar6,(int)piVar12);
        if (iVar5 != 0) {
          Player1ReverseP2(piVar6,piVar12);
        }
        iVar5 = PlayerCheckReversal((int)piVar12,(int)piVar6);
        if (iVar5 != 0) {
          Player1ReverseP2(piVar12,piVar6);
        }
      }
      piVar11 = piVar11 + 1;
      piVar12 = (int *)*piVar11;
    }
    piVar9 = piVar9 + 1;
    piVar6 = (int *)*piVar9;
  }
  piVar9 = g + 0x745b;
  iVar5 = g[0x745b];
  piVar6 = g;
  while (g = piVar6, iVar5 != 0) {
    iVar8 = piVar9[1];
    piVar6 = piVar9 + 1;
    while (iVar8 != 0) {
      piVar6 = piVar6 + 1;
      uVar4 = PlayerCheckP1HitP2(iVar5,iVar8);
      *(undefined4 *)(*(int *)(iVar8 + 0x1154) + *(int *)(iVar5 + 8) * 4) = uVar4;
      uVar4 = PlayerCheckP1HitP2(iVar8,iVar5);
      piVar11 = (int *)(iVar8 + 8);
      iVar8 = *piVar6;
      *(undefined4 *)(*(int *)(iVar5 + 0x1154) + *piVar11 * 4) = uVar4;
    }
    piVar9 = piVar9 + 1;
    piVar6 = g;
    iVar5 = *piVar9;
  }
  if ((*(byte *)(piVar6 + 0x7304) & 1) == 0) {
    piVar9 = piVar6 + piVar6[0x749c] + 0x745a;
    if (piVar6 + 0x745b <= piVar9) {
      do {
        piVar2 = (int *)*piVar9;
        piVar11 = piVar6 + 0x745b;
        piVar12 = (int *)piVar6[0x745b];
        while (piVar12 != (int *)0x0) {
          if (*(int *)(piVar2[0x455] + piVar12[2] * 4) != 0) {
            Player1HitP2(piVar12,piVar2);
            *(undefined4 *)(piVar2[0x455] + piVar12[2] * 4) = 0;
          }
          piVar11 = piVar11 + 1;
          piVar6 = g;
          piVar12 = (int *)*piVar11;
        }
        piVar9 = piVar9 + -1;
      } while (piVar6 + 0x745b <= piVar9);
    }
  }
  else {
    piVar9 = piVar6 + 0x745b;
    piVar11 = (int *)piVar6[0x745b];
    while (piVar11 != (int *)0x0) {
      piVar12 = piVar6 + 0x745b;
      piVar2 = (int *)piVar6[0x745b];
      while (piVar2 != (int *)0x0) {
        if (*(int *)(piVar11[0x455] + piVar2[2] * 4) != 0) {
          Player1HitP2(piVar2,piVar11);
          *(undefined4 *)(piVar11[0x455] + piVar2[2] * 4) = 0;
        }
        piVar12 = piVar12 + 1;
        piVar6 = g;
        piVar2 = (int *)*piVar12;
      }
      piVar9 = piVar9 + 1;
      piVar11 = (int *)*piVar9;
    }
  }
  piVar9 = piVar6 + 0x745b;
  piVar11 = (int *)piVar6[0x745b];
  while (piVar11 != (int *)0x0) {
    piVar6 = piVar9 + 1;
    piVar12 = (int *)piVar9[1];
    while (piVar12 != (int *)0x0) {
      piVar6 = piVar6 + 1;
      PlayerCheckHitProj((int)piVar11,piVar12);
      PlayerCheckHitProj((int)piVar12,piVar11);
      piVar12 = (int *)*piVar6;
    }
    piVar9 = piVar9 + 1;
    piVar6 = g;
    piVar11 = (int *)*piVar9;
  }
  piVar9 = piVar6 + 0x745b;
  piVar11 = (int *)piVar6[0x745b];
  while (piVar11 != (int *)0x0) {
    piVar6 = piVar9 + 1;
    piVar12 = (int *)piVar9[1];
    while (piVar12 != (int *)0x0) {
      if ((piVar12[0x3ff] & piVar12[0x400]) != 0) {
        PlayerCheckProjHit(piVar11,piVar12);
      }
      if ((piVar11[0x3ff] & piVar11[0x400]) != 0) {
        PlayerCheckProjHit(piVar12,piVar11);
      }
      piVar6 = piVar6 + 1;
      piVar12 = (int *)*piVar6;
    }
    piVar9 = piVar9 + 1;
    piVar6 = g;
    piVar11 = (int *)*piVar9;
  }
  piVar9 = piVar6 + 0x745b;
  iVar5 = piVar6[0x745b];
  while (iVar5 != 0) {
    piVar9 = piVar9 + 1;
    PlayerProjDoHit(iVar5);
    piVar6 = g;
    iVar5 = *piVar9;
  }
  piVar9 = piVar6 + 0x745b;
  iVar5 = piVar6[0x745b];
  while (iVar5 != 0) {
    piVar6 = piVar9 + 1;
    iVar8 = piVar9[1];
    while (iVar8 != 0) {
      piVar6 = piVar6 + 1;
      CheckProjHitProj(iVar5,iVar8);
      iVar8 = *piVar6;
    }
    piVar9 = piVar9 + 1;
    piVar6 = g;
    iVar5 = *piVar9;
  }
  piVar9 = piVar6 + 0x745b;
  iVar5 = piVar6[0x745b];
  while (iVar5 != 0) {
    piVar6 = piVar9 + 1;
    iVar8 = piVar9[1];
    while (iVar8 != 0) {
      iVar7 = PlayerAreEnemies(iVar5,iVar8);
      if (iVar7 != 0) {
        PlayerPushCheck(iVar5,iVar8,0);
      }
      piVar6 = piVar6 + 1;
      iVar8 = *piVar6;
    }
    piVar9 = piVar9 + 1;
    iVar5 = *piVar9;
  }
  return;
}

/* PlayerPushCheck @ 0x080b3430, 617 bytes
 * FIXUP: 8 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 3 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void PlayerPushCheck(int param_1,int param_2,int param_3)

{
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  int iVar4;
  uint local_1c;
  
  local_1c = (uint)(*(int *)(param_1 + 400) != 1);
  if (param_3 == 0) {
    fVar1 = ((float10)*(int *)(param_2 + 0x1c0) + *(float *)(param_2 + 0x19c)) -
            ((float10)*(int *)(param_1 + 0x1c0) + *(float *)(param_1 + 0x19c));
    fVar2 = ((float10)*(int *)(param_2 + 0x1c4) + *(float *)(param_2 + 0x1a0)) -
            ((float10)*(int *)(param_1 + 0x1c4) + *(float *)(param_1 + 0x1a0));
    fVar3 = *(float *)(param_1 + 0x1a4) - *(float *)(param_2 + 0x1a4);
  }
  else {
    fVar1 = ((float10)*(int *)(param_2 + 0x1c0) + *(float *)(param_2 + 0x1a8)) -
            ((float10)*(int *)(param_1 + 0x1c0) + *(float *)(param_1 + 0x1a8));
    fVar2 = ((float10)*(int *)(param_2 + 0x1c4) + *(float *)(param_2 + 0x1ac)) -
            ((float10)*(int *)(param_1 + 0x1c4) + *(float *)(param_1 + 0x1ac));
    fVar3 = *(float *)(param_1 + 0x1b0) - *(float *)(param_2 + 0x1b0);
  }
  iVar4 = (int)GHIDRA_FIST32(fVar3);
  if ((*(int *)(param_1 + 0x1f0) != 0) && (*(int *)(param_2 + 0x1f0) != 0)) {
    if (iVar4 < 0) {
      iVar4 = -iVar4;
    }
    if (iVar4 < *(int *)(param_2 + 0x94) + *(int *)(param_1 + 0x94)) {
      iVar4 = ClsnArrayDetectRectFlip
                        (*(int **)(*(int *)(*(int *)(param_1 + 0x13bc) + 0x10) + 0x2c),
                         *(int **)(*(int *)(*(int *)(param_2 + 0x13bc) + 0x10) + 0x2c),
                         (int)GHIDRA_FIST32(fVar1),(int)GHIDRA_FIST32(fVar2),local_1c,
                         (uint)(*(int *)(param_2 + 400) != 1));
      if (iVar4 != 0) {
        if (((*(int *)(param_1 + 0xe24) != 0) && (*(int *)(param_2 + 0xe24) != 0)) ||
           (g[0x731d] != 1)) {
          PlayerCheckOverlap(param_1,param_2);
        }
        StageBound(param_1);
        StageBound(param_2);
        if (*(int *)(param_1 + 0x1e4) != 0) {
          ScreenBound(param_1);
        }
        if (*(int *)(param_2 + 0x1e4) != 0) {
          ScreenBound(param_2);
        }
      }
    }
  }
  return;
}

/* PlayerCheckOverlap @ 0x080b36a0, 291 bytes
 * FIXUP: 2 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 2 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void PlayerCheckOverlap(int param_1,int param_2)

{
  float10 fVar1;
  float10 fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (((*(int *)(param_1 + 0xe00) != 1) ||
      (*(float *)(param_1 + 0x1a0) - *(float *)(param_2 + 0x1a0) <= (float10)*(int *)(param_1 + 0x98))
      ) && ((*(int *)(param_2 + 0xe00) != 1 ||
            (*(float *)(param_2 + 0x1a0) - *(float *)(param_1 + 0x1a0) <=
             (float10)*(int *)(param_2 + 0x98))))) {
    iVar5 = param_1;
    if (*(float *)(param_2 + 0x19c) < *(float *)(param_1 + 0x19c)) {
      iVar5 = param_2;
      param_2 = param_1;
    }
    iVar3 = PlayerGetWidth(iVar5,4,1);
    iVar4 = PlayerGetWidth(param_2,3,1);
    fVar2 = *(float *)(param_2 + 0x19c) - *(float *)(iVar5 + 0x19c);
    if (fVar2 < 10.0) {
      fVar1 = (*(float *)(iVar5 + 0x19c) + *(float *)(param_2 + 0x19c)) * 0.5;
      *(float *)(iVar5 + 0x19c) = fVar1 - 5.0;
      *(float *)(param_2 + 0x19c) = fVar1 + 5.0;
    }
    if (fVar2 < (float)(iVar4 + iVar3)) {
      fVar2 = ((float)(iVar4 + iVar3) - fVar2) * 0.5;
      *(float *)(iVar5 + 0x19c) = *(float *)(iVar5 + 0x19c) - fVar2;
      *(float *)(param_2 + 0x19c) = *(float *)(param_2 + 0x19c) + fVar2;
    }
  }
  return;
}

/* PlayerCheckP1HitP2 @ 0x080b37d0, 95 bytes
 * FIXUP: 2 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
undefined4 PlayerCheckP1HitP2(int param_1,int param_2)

{
  bool bVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined4 uVar2;
  
  uVar2 = 0;
  bVar1 = PlayerCheckHit(param_1,param_2);
  if (GHIDRA_ZEXT8(bVar1) != 0) {
    bVar1 = PlayerCheckHit(param_2,param_1);
    if (GHIDRA_ZEXT8(bVar1) != 0) {
      if (*(int *)(param_1 + 0x11d4) <= *(int *)(param_2 + 0x11d4)) {
        if (*(int *)(param_1 + 0x11d4) != *(int *)(param_2 + 0x11d4)) {
          return 0;
        }
        if (*(int *)(param_1 + 0x11d8) != 0) {
          return 0;
        }
        if (*(int *)(param_2 + 0x11d8) == 2) {
          return 0;
        }
      }
    }
    uVar2 = 1;
  }
  return uVar2;
}

/* PlayerCheckHit @ 0x080b3830, 778 bytes
 * REVIEW: calls-missing-in-pid:NAN
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: 4 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 2 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
bool PlayerCheckHit(int param_1,int param_2)

{
  float10 fVar1;
  float10 fVar2;
  int *piVar3;
  int *piVar4;
  bool bVar5;
  undefined3 extraout_var;
  int *piVar6;
  int iVar7;
  int iVar8;
  int local_30;
  uint local_28;
  uint local_24;
  
  local_24 = (uint)(*(int *)(param_1 + 400) != 1);
  local_28 = (uint)(*(int *)(param_2 + 400) != 1);
  piVar3 = *(int **)(*(int *)(*(int *)(param_1 + 0x13bc) + 0x10) + 0x28);
  piVar4 = *(int **)(*(int *)(*(int *)(param_2 + 0x13bc) + 0x10) + 0x2c);
  if (*(int *)(param_1 + 0xe04) == 0) {
    return false;
  }
  if (*(int *)(param_1 + 0x1204) != 0) {
    return false;
  }
  if (0 < *(int *)(param_2 + 0xff8)) {
    return false;
  }
  if ((*(uint *)(param_2 + 0xffc) & *(uint *)(param_2 + 0x1000)) == 0) {
    return false;
  }
  if (*(int *)(param_1 + 0x1158) == 0) {
    return false;
  }
  bVar5 = HitdefAffectTeam(param_1 + 0x1158,*(int *)(param_1 + 0xc),*(uint *)(param_2 + 0xc));
  if (GHIDRA_ZEXT8(bVar5) == 0) {
    return false;
  }
  if (*(int *)(param_1 + 0x1170) != -1) {
    if (*(int *)(param_2 + 0x1064) != *(int *)(param_1 + 0x1170)) {
      return false;
    }
    if (*(int *)(param_2 + 0x1014) != param_1) {
      return false;
    }
  }
  if ((*(int *)(param_1 + 0x1174) != -1) && (*(int *)(param_2 + 0x1014) == param_1)) {
    if (*(int *)(param_2 + 0x1064) == *(int *)(param_1 + 0x1174)) {
      return false;
    }
    if ((*(int *)(param_1 + 0x1178) != -1) &&
       (*(int *)(param_2 + 0x1064) == *(int *)(param_1 + 0x1178))) {
      return false;
    }
  }
  piVar6 = PlayerFindTarget(*(int *)(param_1 + 0x220),param_2);
  if (piVar6 == (int *)0x0) {
    iVar7 = *(int *)(param_1 + 0x1168);
  }
  else {
    iVar7 = *(int *)(param_1 + 0x1168);
    if (piVar6[2] == iVar7) {
      return false;
    }
  }
  if (*(int *)(*(int *)(param_2 + 0x1148) + *(int *)(param_1 + 8) * 4) == iVar7) {
    return false;
  }
  local_30 = *(int *)(param_1 + 0x11dc);
  iVar7 = *(int *)(param_1 + 0x11e0);
  if (local_30 == -1) {
    local_30 = *(int *)(param_1 + 0x5c);
  }
  if (iVar7 == -1) {
    iVar7 = *(int *)(param_1 + 0x60);
  }
  fVar1 = *(float *)(param_1 + 0x1a4);
  fVar2 = *(float *)(param_2 + 0x1a4);
  if (fVar1 < fVar2) {
    iVar8 = *(int *)(param_2 + 0x94);
  }
  else {
    iVar8 = *(int *)(param_2 + 0x94);
    if (fVar1 - fVar2 <= (float)(local_30 + iVar8)) goto LAB_080b3a95;
    if (fVar2 < fVar1) {
      return false;
    }
  }
  if ((float)(iVar8 + iVar7) < fVar2 - fVar1) {
    return false;
  }
LAB_080b3a95:
  iVar7 = ClsnArrayDetectRectFlip
                    (piVar3,piVar4,
                     (int)GHIDRA_FIST32(((float10)*(int *)(param_2 + 0x1c0) + *(float *)(param_2 + 0x19c)) -
                                ((float10)*(int *)(param_1 + 0x1c0) + *(float *)(param_1 + 0x19c))),
                     (int)GHIDRA_FIST32(((float10)*(int *)(param_2 + 0x1c4) + *(float *)(param_2 + 0x1a0)) -
                                ((float10)*(int *)(param_1 + 0x1c4) + *(float *)(param_1 + 0x1a0))),
                     local_24,local_28);
  if (iVar7 != 0) {
    if (*(char *)(param_1 + 0x209) == '\0') {
      if (piVar6 == (int *)0x0) {
        iVar7 = *(int *)(param_1 + 0x118c);
      }
      else {
        iVar7 = *(int *)(param_1 + 0x118c);
        if ((iVar7 != -1) && (piVar6[1] - iVar7 < 0)) {
          return false;
        }
      }
      *(int *)(param_1 + 0x1344) = iVar7;
    }
    iVar7 = PlayerCheckFlagHit(param_2,*(uint *)(param_1 + 0x11d0));
    if (iVar7 != 0) {
      PlayerAttrStateSet(param_1);
      iVar7 = PlayerCheckAttrHit(param_2,*(uint *)(param_1 + 0x1164));
      return iVar7 != 0;
    }
  }
  return false;
}

/* Player1HitP2 @ 0x080b3b40, 2237 bytes
 * FIXUP: 1 float-field accesses rewritten as bit reinterpretations (asm: x87 single loads/stores at offsets 0x1354)
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 8 stack locals placed at their original offsets in a 0x70-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void Player1HitP2(int *param_1,int *param_2)

{
  float10 fVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  undefined3 extraout_var;
  int *piVar7;
  int iVar8;
  int *piVar9;
  int **ppiVar10;
  int *piVar11;
  unsigned char ghidra_frame[0x70] __attribute__((aligned(16)));
#define local_68 (*(uint *)(ghidra_frame + 0x8))
#define local_60 (*(int *)(ghidra_frame + 0x10))
#define local_58 (*(int *)(ghidra_frame + 0x18))
#define local_54 (*(uint *)(ghidra_frame + 0x1c))
#define local_4c (*(int **)(ghidra_frame + 0x24))
#define local_48 (*(int **)(ghidra_frame + 0x28))
#define local_3c (*(int **)(ghidra_frame + 0x34))
#define local_38 (*(int *)(ghidra_frame + 0x38))
  
  local_48 = (int *)0x0;
  local_58 = param_1[100];
  piVar7 = param_1 + 0x456;
  local_54 = (uint)(local_58 != 1);
  iVar8 = g[param_1[3] + 0x7506];
  if (param_1[0x462] != 0) {
    if (param_1[0x456] == 0) {
      return;
    }
    if (0 < param_2[0x3fe]) {
      return;
    }
    PlayerDropBoundTargets((int)param_1,param_2);
  }
  local_68 = 0;
  bVar3 = false;
  iVar5 = PlayerCheckFlagHit((int)param_2,param_1[0x473]);
  if (((iVar5 == 0) || (param_2[900] == 0)) || (*(char *)((int)param_1 + 0x20b) != '\0')) {
    iVar8 = PlayerGetDamagedLife((int)param_2);
    iVar5 = PlayerGetCorrectedDamage(param_1[0x464],param_1[0x45f],(int)param_2);
    if (iVar8 - iVar5 < 1) {
      WinIconCheckTeam(param_2[3],param_1[3],param_1[0x459]);
LAB_080b3d04:
      local_68 = 1;
    }
  }
  else {
    iVar5 = PlayerGetDamagedLife((int)param_2);
    iVar6 = PlayerGetCorrectedDamage(param_1[0x465],param_1[0x460],(int)param_2);
    if (iVar5 - iVar6 < 1) {
      if (((g[0x79a9] != 0) && (local_68 = 1, g[0x7511] != 3)) && (iVar8 < 10)) {
        WinIconCheck(param_1[3],0,3);
        goto LAB_080b3d04;
      }
    }
    else {
      bVar3 = true;
    }
  }
  bVar2 = false;
  local_68 = local_68 & (g[0x730b] != 0) - 1;
  piVar9 = param_2 + 0x42a;
  for (iVar8 = 0; iVar8 < 8; iVar8 = iVar8 + 1) {
    local_4c = piVar9;
    if ((*piVar9 != 0) &&
       (bVar4 = AttrMatch(piVar9[1],param_1[0x459]), GHIDRA_ZEXT8(bVar4) != 0)) {
      bVar2 = true;
      break;
    }
    piVar9 = piVar9 + 5;
  }
  if (bVar2) {
    bVar3 = false;
    local_68 = 0;
    if (param_1[0x47b] != 0) {
      return;
    }
    if (param_1[0x479] != -1) {
      return;
    }
  }
  else {
    local_4c = (int *)0x0;
    local_48 = PlayerFindTarget(param_1[0x88],(int)param_2);
    if (local_48 == (int *)0x0) {
      ppiVar10 = &local_3c;
      for (iVar8 = 8; iVar8 != 0; iVar8 = iVar8 + -1) {
        *ppiVar10 = (int *)0x0;
        ppiVar10 = ppiVar10 + 1;
      }
      local_3c = param_2;
      local_38 = param_1[0x19];
      iVar8 = ArrayAdd(param_1[0x88],&local_3c,0,0);
      if (iVar8 == -1) {
        return;
      }
      local_48 = (int *)(iVar8 * *(int *)(param_1[0x88] + 4) + *(int *)(param_1[0x88] + 0x14));
    }
    local_48[6] = 0;
    local_48[5] = 0;
    local_48[4] = 0;
    local_48[3] = 0;
    local_48[2] = param_1[0x45a];
  }
  param_1[0x73] = param_1[0x47d];
  param_2[0x73] = param_1[0x47e];
  if (param_2[100] == local_58) {
    iVar8 = PlayerGetWidth((int)param_2,2,0);
    iVar8 = -iVar8 - param_1[0x492];
  }
  else {
    iVar8 = PlayerGetWidth((int)param_2,1,0);
    iVar8 = iVar8 + param_1[0x492];
  }
  iVar8 = (int)GHIDRA_FIST32((float)g[0x7311] +
                     (float)((iVar8 - param_2[0x70]) * param_2[100]) * GHIDRA_I2F(param_2[0x4d2]) +
                     (*(float *)&param_2[0x4d5]));
  iVar5 = (int)GHIDRA_FIST32((float)(param_1[0x493] - param_1[0x71]) * GHIDRA_I2F(param_1[0x4d2]) +
                     GHIDRA_I2F(param_1[0x4d6]) + (float)g[0x7312]);
  if (bVar3) {
    param_1[0x387] = param_1[0x4b5];
    param_1[0x38c] = 1;
    param_1[0x38d] = 0;
    local_60 = PlayerGetHitG(param_1,param_2,(int)piVar7,local_58);
    PlayerPowerSet((int)param_1,param_1[0x467] + *(int *)param_1[0x5c]);
    PlayerSparkCreate(param_1,param_1[0x490],iVar8,iVar5,param_1[0x491],local_54,1);
    goto LAB_080b4371;
  }
  if (!bVar2) {
    if (((param_2[0x41c] != 0) || ((param_1[0x474] & 1U) != 0)) ||
       ((param_1[0x4a6] != 0 && (param_2[0x380] == 3)))) {
      local_48[1] = local_48[1] - param_1[0x4d1];
      param_1[0x463] = 0;
    }
    if (param_1[0x494] != 0) {
      local_58 = -param_1[100];
      param_1[0x65] = local_58;
    }
    if (param_1[0x495] != 0) {
      if (param_1[0x495] == 1) {
        if (local_58 != param_2[100]) {
LAB_080b4020:
          local_58 = -param_1[100];
          param_1[0x65] = local_58;
        }
      }
      else if (local_58 == param_2[100]) goto LAB_080b4020;
    }
  }
  local_60 = PlayerGetHit(param_1,param_2,(int)piVar7,GHIDRA_I2F(param_1[0x67]),GHIDRA_I2F(param_1[0x68]),
                          GHIDRA_I2F(param_1[0x69]),local_58,local_68,(int)local_4c);
  if ((local_60 != 0) || (bVar2)) {
    param_1[0x387] = param_1[0x46b];
    PlayerPowerSet((int)param_1,param_1[0x466] + *(int *)param_1[0x5c]);
    piVar9 = g;
    param_1[0x4e6] = param_1[0x4e6] + param_1[0x46c];
    if (param_1[0x38e] < piVar9[0x7304]) {
      param_1[0x4e7] = param_1[0x4e7] + param_1[0x46c];
    }
    param_1[0x4e8] = param_1[0x4e8] + param_1[0x46c];
    param_1[0x38c] = 2;
    param_1[0x38d] = 0;
    ComboAdd(param_1[3],param_1[0x46c]);
    if (!bVar2) {
      if ((0 < param_1[0x4bd]) || (param_1[0x4bd] == -1)) {
        piVar9 = param_1 + 0x4bc;
        piVar11 = param_2 + 0x977;
        for (iVar6 = 0xf; iVar6 != 0; iVar6 = iVar6 + -1) {
          *piVar11 = *piVar9;
          piVar9 = piVar9 + 1;
          piVar11 = piVar11 + 1;
        }
      }
      if ((param_1[0x459] & 0x1c0U) != 0) {
        param_2[0x3fe] = param_1[0x46b] + 1;
        param_1[0x3fe] = param_1[0x46b] + 1;
      }
    }
  }
  PlayerSparkCreate(param_1,param_1[0x48e],iVar8,iVar5,param_1[0x48f],local_54,0);
  if (bVar2) {
    if (local_4c[2] != -1) {
      PlayerChangeState((int)param_2,local_4c[2]);
    }
  }
  else {
    if (param_1[0x479] != -1) {
      PlayerChangeState((int)param_1,param_1[0x479]);
    }
    if (param_1[0x47b] != 0) {
      param_2[0x2fb] = param_1[0x2fa];
      param_2[0x2fc] = param_1[2];
      param_2[0x259] = param_1[0x259];
      KBClearCommandValidTimes(param_2 + 0x25a);
      if (param_1[0x2fb] != 0) {
        param_2[0x2fb] = param_1[0x2fb];
        param_2[0x2fc] = param_1[0x2fc];
      }
      if (param_1[0x4f0] == 0) {
        param_2[0x4f0] = *(int *)param_1[0x4ef];
      }
      else {
        param_2[0x4f0] = param_1[0x4f0];
      }
    }
    if (param_1[0x47a] != -1) {
      PlayerChangeState((int)param_2,param_1[0x47a]);
      param_2[899] = 0;
    }
    local_48[6] = param_1[0x47c];
    local_48[3] = param_1[0x499];
    local_48[4] = param_1[0x49a];
    local_48[5] = param_1[0x49b];
  }
LAB_080b4371:
  if ((local_60 != 0) && (iVar8 = PlayerInCorner((int)param_2), iVar8 != 0)) {
    param_1[0x8e] = -1;
    fVar1 = GHIDRA_I2F(param_2[0x453]);
    param_1[0x8a] = 0;
    param_1[0x8b] = 0x3f333333;
    param_1[0x8d] = 0x3f800000;
    param_1[0x89] = GHIDRA_F2I(int, ((float10)param_1[100] * fVar1));
  }
  param_1[0x38e] = g[0x7304];
  if (param_1[0x462] != 0) {
    *piVar7 = 0;
  }
  return;
}
#undef local_68
#undef local_60
#undef local_58
#undef local_54
#undef local_4c
#undef local_48
#undef local_3c
#undef local_38

/* PlayerGetHit @ 0x080b4400, 2824 bytes
 * FIXUP: 2 float-field accesses rewritten as bit reinterpretations (asm: x87 single loads/stores at offsets 0x104c)
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 9 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
undefined4
PlayerGetHit(int *param_1,int *param_2,int param_3,float param_4,float param_5,float param_6,
            int param_7,int param_8,int param_9)

{
  float10 fVar1;
  bool bVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int local_20;
  
  bVar2 = true;
  iVar4 = -param_7;
  local_20 = 1;
  param_2[0x453] = 0;
  if ((param_9 != 0) && (*(int *)(param_9 + 0x10) != 0)) {
    param_2[0x380] = 3;
  }
  if (*(int *)(param_3 + 100) == 0) {
    iVar5 = *(int *)(*param_1 + 0x11d0);
    iVar9 = *(int *)(param_3 + 0x60);
    iVar8 = *(int *)(param_3 + 0x5c);
    piVar6 = *(int **)(*param_1 + 0x11d4);
  }
  else {
    iVar5 = 0;
    iVar9 = *(int *)(param_3 + 0x60);
    iVar8 = *(int *)(param_3 + 0x5c);
    piVar6 = (int *)g[0x4156];
  }
  GameSndPlayIDPos(-1,(int)GHIDRA_FIST32(GHIDRA_I2F(param_2[0x4d5])),piVar6,iVar8,iVar9,iVar5);
  if (*(int *)(param_3 + 0x118) == -param_2[100] * iVar4) {
    param_2[0x65] = -param_2[100];
  }
  param_2[0x412] = *(int *)(param_3 + 0xc);
  param_2[0x405] = (int)param_1;
  iVar5 = param_1[2];
  uVar3 = *(undefined4 *)(param_3 + 0x10);
  param_2[0x417] = 0;
  *(undefined4 *)(param_2[0x452] + iVar5 * 4) = uVar3;
  param_2[0x419] = *(int *)(param_3 + 0x14);
  param_2[0x41a] = 0;
  param_2[0x409] = *(int *)(param_3 + 0x11c);
  param_2[0x408] = *(int *)(param_3 + 0x134);
  param_2[0x416] = 0;
  if (((*(uint *)(param_3 + 0x78) & 1) != 0) || (param_8 != 0)) {
    param_2[0x41c] = 1;
  }
  if (param_2[0x41c] == 0) {
    iVar5 = *(int *)(param_3 + 0xa4);
  }
  else {
    iVar5 = *(int *)(param_3 + 0xb4);
  }
  param_2[0x407] = iVar5;
  if (1 < param_2[0x380] - 1U) {
    if ((param_2[0x380] == 4) && (GHIDRA_I2F(param_2[0x68]) == 0.0)) {
      if ((*(int *)(param_3 + 0x11c) != 0) && (*(int *)(param_3 + 0xac) == 0)) {
        fVar1 = *(float *)(param_3 + 0x158);
        bVar2 = false;
        param_2[0x2fe] = param_2[0x2fd];
        if (fVar1 == -32760.0) {
          param_2[0x416] = param_2[0x6d];
        }
        else {
          param_2[0x416] = GHIDRA_F2I(int, ((float10)iVar4 * fVar1));
        }
        if (*(float *)(param_3 + 0x158) == -32760.0) {
          iVar5 = param_2[0x6e];
        }
        else {
          iVar5 = *(int *)(param_3 + 0x15c);
        }
        param_2[0x417] = iVar5;
        param_2[0x453] = *(int *)(param_3 + 0x160);
        if (GHIDRA_I2F(param_2[0x417]) == 0.0) {
          param_2[0x2fd] = 0x13d8;
          param_2[0x40e] = *(int *)(param_3 + 0x154);
        }
        else {
          param_2[0x2fd] = 0x13d8;
          local_20 = *(int *)(param_3 + 0x150);
          param_2[0x414] = GHIDRA_F2I(int, (GHIDRA_I2F(param_2[0x414]) + 15.0));
        }
      }
    }
    else if ((*(int *)(param_3 + 0x134) != 0) && (*(int *)(param_3 + 0xac) == 0)) {
      bVar2 = false;
      param_2[0x2fe] = param_2[0x2fd];
      param_2[0x2fd] = 0x139c;
      fVar1 = *(float *)(param_3 + 0x144);
      param_2[0x2fd] = ((*(int *)(param_3 + 0x134) == 3) - 1 & 0xffffffce) + 0x13ce;
      if (fVar1 == -32760.0) {
        param_2[0x416] = param_2[0x6d];
      }
      else {
        param_2[0x416] = GHIDRA_F2I(int, ((float10)iVar4 * fVar1));
      }
      if (*(float *)(param_3 + 0x148) == -32760.0) {
        param_2[0x417] = param_2[0x6e];
      }
      else {
        param_2[0x417] = GHIDRA_F2I(int, *(float *)(param_3 + 0x148));
      }
      param_2[0x453] = *(int *)(param_3 + 0x14c);
      param_2[0x40e] = *(int *)(param_3 + 0x13c);
      if (*(int *)(param_3 + 0x140) != 0) {
        param_2[0x41c] = 1;
      }
      if (param_2[0x41c] == 0) {
        iVar5 = *(int *)(param_3 + 0x138);
      }
      else {
        iVar5 = *(int *)(param_3 + 0xb4);
      }
      param_2[0x407] = iVar5;
      if (param_8 != 0) {
        if (GHIDRA_I2F(param_2[0x416]) < 0.0) {
          param_2[0x416] = GHIDRA_F2I(int, (GHIDRA_I2F(param_2[0x416]) - 2.0));
        }
        if (GHIDRA_I2F(param_2[0x417]) <= 0.0) {
          fVar1 = GHIDRA_I2F(param_2[0x417]) - 2.0;
          param_2[0x417] = GHIDRA_F2I(int, fVar1);
          if ((fVar1 <= 0.0) && (-3.0 < fVar1)) {
            param_2[0x417] = -0x3fc00000;
          }
        }
      }
    }
    goto LAB_080b49d0;
  }
  if ((*(int *)(param_3 + 0x11c) == 0) || (*(int *)(param_3 + 0xac) != 0)) goto LAB_080b49d0;
  bVar2 = false;
  param_2[0x2fe] = param_2[0x2fd];
  if ((*(int *)(param_3 + 0xa8) != 0) || (param_8 != 0)) {
    param_2[0x380] = 1;
  }
  param_2[0x2fd] = ((param_2[0x380] != 1) - 1 & 0xfffffff6) + 0x1392;
  if (*(int *)(param_3 + 0x11c) == 3) {
    param_2[0x2fd] = 0x13ce;
  }
  if (*(float *)(param_3 + 0x128) == -32760.0) {
    param_2[0x416] = param_2[0x6d];
  }
  else {
    param_2[0x416] = GHIDRA_F2I(int, ((float10)iVar4 * *(float *)(param_3 + 0x128)));
  }
  if (*(float *)(param_3 + 300) == -32760.0) {
    param_2[0x417] = param_2[0x6e];
  }
  else {
    param_2[0x417] = GHIDRA_F2I(int, *(float *)(param_3 + 300));
  }
  param_2[0x453] = *(int *)(param_3 + 0x130);
  if (param_8 == 0) {
LAB_080b46ec:
    fVar1 = GHIDRA_I2F(param_2[0x417]);
  }
  else {
    if (*(float *)(param_3 + 300) == 0.0) {
      param_2[0x416] = GHIDRA_F2I(int, (GHIDRA_I2F(param_2[0x416]) * ((double)0.66)));
    }
    if (GHIDRA_I2F(param_2[0x416]) < 0.0) {
      param_2[0x416] = GHIDRA_F2I(int, (GHIDRA_I2F(param_2[0x416]) - 2.5));
    }
    fVar1 = GHIDRA_I2F(param_2[0x417]);
    if (fVar1 <= 0.0) {
      fVar1 = fVar1 - 2.0;
      param_2[0x417] = GHIDRA_F2I(int, fVar1);
      if ((fVar1 <= 0.0) && (-6.0 < fVar1)) {
        param_2[0x417] = -0x3f400000;
      }
      goto LAB_080b46ec;
    }
  }
  if (param_2[0x41c] == 0) {
LAB_080b4715:
    if (fVar1 == 0.0) {
      param_2[0x40e] = *(int *)(param_3 + 0x120);
      param_2[0x40f] = *(int *)(param_3 + 0x124);
      if (param_2[0x407] == 3) {
        param_2[0x407] = 2;
      }
      goto LAB_080b49d0;
    }
  }
  else if (fVar1 == 0.0) {
    param_2[0x417] = -0x457ced91;
    fVar1 = GHIDRA_I2F(param_2[0x417]);
    goto LAB_080b4715;
  }
  param_2[0x40e] = *(int *)(param_3 + 0x13c);
LAB_080b49d0:
  iVar5 = param_2[0x65];
  if (iVar5 == 0) {
    iVar5 = param_2[100];
  }
  iVar9 = iVar4;
  if (*(int *)(param_3 + 0x118) == -1) {
    iVar9 = param_7;
  }
  if ((iVar5 != iVar9) && ((uint)param_2[0x407] < 3)) {
    if (param_2[0x409] == 1) {
      param_2[0x409] = 2;
    }
    else if (param_2[0x409] == 2) {
      param_2[0x409] = 1;
    }
    if (param_2[0x408] == 1) {
      param_2[0x408] = 2;
    }
    else if (param_2[0x408] == 2) {
      param_2[0x408] = 1;
    }
  }
  if ((bVar2) && (*(int *)(param_3 + 0xac) == 0)) {
    uVar3 = 0;
  }
  else {
    if (*(float *)(param_3 + 0x194) == -32760.0) {
      param_2[0x418] = 0x3eb33333;
    }
    else {
      param_2[0x418] = GHIDRA_F2I(int, *(float *)(param_3 + 0x194));
    }
    if (*(int *)(param_3 + 0x1d8) != 0) {
      piVar6 = (int *)(param_3 + 0x1d4);
      piVar7 = g + 0x7317;
      for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
        *piVar7 = *piVar6;
        piVar6 = piVar6 + 1;
        piVar7 = piVar7 + 1;
      }
    }
    param_2[0x41e] = *(int *)(param_3 + 0xb8);
    param_2[0x41f] = *(int *)(param_3 + 0xbc);
    param_2[0x420] = *(int *)(param_3 + 0xc0);
    param_2[0x421] = 0;
    param_2[0x422] = *(int *)(param_3 + 0xc4);
    param_2[0x423] = *(int *)(param_3 + 0x2c);
    piVar6 = (int *)(param_3 + 200);
    piVar7 = param_2 + 0x424;
    for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar7 = *piVar6;
      piVar6 = piVar6 + 1;
      piVar7 = piVar7 + 1;
    }
    if (local_20 == 0) {
      param_2[0x41e] = -0x39001000;
      param_2[0x41f] = 0;
    }
    param_2[0x41d] = *(int *)(param_3 + 0xb0);
    if (*(int *)(param_3 + 0xac) == 0) {
      iVar5 = PlayerSndID((int)param_2,0);
      SndIDStop(iVar5);
      param_2[0x259] = *param_2 + 0x11b4;
      param_2[0x2fb] = 0;
      param_2[0x2fc] = -1;
      KBClearCommandValidTimes(param_2 + 0x25a);
      param_2[0x4f0] = 0;
      if ((param_2[0x381] != 2) && (1 < param_2[0x454])) {
        param_2[0x5b] = param_2[0x58];
        param_2[0x5a] = param_2[0x58];
        param_2[0x40b] = 0;
      }
      piVar6 = g;
      param_2[0x40b] = param_2[0x40b] + 1;
      param_2[900] = 0;
      param_2[0x381] = 2;
      param_2[0x74] = 0;
      param_2[0x37f] = 0;
      param_2[899] = 0;
      iVar5 = *(int *)(param_3 + 0x50);
      param_2[0x40d] = iVar5;
      iVar9 = piVar6[0x74f3];
      if ((iVar9 != -1) && (param_2[iVar9 + 0x77] < iVar5)) {
        param_2[iVar9 + 0x77] = iVar5;
      }
      param_2[0x387] = 0;
      param_2[0x386] = 0;
      iVar5 = (int)GHIDRA_FIST32((float10)(int)GHIDRA_FIST32(GHIDRA_I2F(param_2[0x67])) - param_4);
      if (iVar5 < 0) {
        iVar5 = -iVar5;
      }
      iVar9 = *(int *)(param_3 + 0x100);
      if ((iVar5 < iVar9) && (iVar9 != -0x401)) {
        param_2[0x413] =
             (int)(((param_4 - (float)(iVar9 * iVar4)) - GHIDRA_I2F(param_2[0x67])) +
                  (*(float *)&param_2[0x413]));
      }
      fVar1 = (float10)*(int *)(param_3 + 0x104);
      if ((GHIDRA_I2F(param_2[0x68]) - param_5 < fVar1) && (*(int *)(param_3 + 0x104) != -0x401)) {
        param_2[0x414] = GHIDRA_F2I(int, (((fVar1 + param_5) - GHIDRA_I2F(param_2[0x68])) + GHIDRA_I2F(param_2[0x414])));
      }
      fVar1 = (float10)*(int *)(param_3 + 0x108);
      if ((param_6 - GHIDRA_I2F(param_2[0x69]) < fVar1) && (*(int *)(param_3 + 0x108) != -0x401)) {
        param_2[0x415] = GHIDRA_F2I(int, (((fVar1 + param_6) - GHIDRA_I2F(param_2[0x69])) + GHIDRA_I2F(param_2[0x415])));
      }
      iVar5 = (int)GHIDRA_FIST32(param_4 - (float10)(int)GHIDRA_FIST32(GHIDRA_I2F(param_2[0x67])));
      if (iVar5 < 0) {
        iVar5 = -iVar5;
      }
      iVar9 = *(int *)(param_3 + 0x10c);
      if ((iVar9 < iVar5) && (iVar9 != -0x401)) {
        param_2[0x413] =
             (int)(((param_4 - (float)(iVar9 * iVar4)) - GHIDRA_I2F(param_2[0x67])) +
                  (*(float *)&param_2[0x413]));
      }
      fVar1 = (float10)*(int *)(param_3 + 0x110);
      if ((fVar1 < GHIDRA_I2F(param_2[0x68]) - param_5) && (*(int *)(param_3 + 0x110) != -0x401)) {
        param_2[0x414] = GHIDRA_F2I(int, (((fVar1 + param_5) - GHIDRA_I2F(param_2[0x68])) + GHIDRA_I2F(param_2[0x414])));
      }
      fVar1 = (float10)*(int *)(param_3 + 0x114);
      if ((fVar1 < param_6 - GHIDRA_I2F(param_2[0x69])) && (*(int *)(param_3 + 0x114) != -0x401)) {
        param_2[0x415] = GHIDRA_F2I(int, (((fVar1 + param_6) - GHIDRA_I2F(param_2[0x69])) + GHIDRA_I2F(param_2[0x415])));
      }
      PlayerDropBoundTargets((int)param_2,(int *)0x0);
      ExplodRemoveGetHit((undefined4 *)g[0x52be],param_2[1]);
      iVar4 = PlayerGetCorrectedDamage
                        (*(int *)(param_3 + 0x38),*(int *)(param_3 + 0x24),(int)param_2);
      param_2[0x40a] = param_2[0x40a] + iVar4;
      if (param_8 != 0) {
        param_2[0x40a] = param_2[0x58];
      }
      if ((param_2[7] != 1) || (param_2[0x98a] == 1)) {
        PlayerPowerSet((int)param_2,*(int *)(param_3 + 0x48) + *(int *)param_2[0x5c]);
      }
    }
    uVar3 = 1;
  }
  return uVar3;
}

/* PlayerTakeDamage @ 0x080b4f10, 131 bytes
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
void PlayerTakeDamage(int param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = -param_2;
  uVar2 = uVar1;
  if (param_4 == 0) {
    if ((int)uVar1 < 0) {
      uVar2 = (uint)GHIDRA_FIST32((float10)(int)uVar1 * *(float *)(param_1 + 0x18c) - 0.5);
    }
    if (0x7fffffff < uVar1) {
      uVar2 = uVar2 | (uVar2 != 0) - 1;
    }
  }
  uVar2 = uVar2 + *(int *)(param_1 + 0x160);
  if (((int)uVar2 < 1) && (param_3 == 0)) {
    uVar2 = 1;
  }
  PlayerLifeSet(param_1,uVar2);
  return;
}

/* PlayerGetCorrectedDamage @ 0x080b4fa0, 153 bytes */
int PlayerGetCorrectedDamage(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_3 + 0x1028) +
          (int)GHIDRA_FIST32((float)param_1 * *(float *)(param_3 + 0x18c) + 0.5);
  if ((0 < param_1) && (iVar2 == 0)) {
    iVar2 = 1;
  }
  if (param_2 == 0) {
    iVar1 = PlayerGetDamagedLife(param_3);
    if ((iVar1 == iVar2 || iVar1 - iVar2 < 0) && (*(int *)(param_3 + 0xe24) != 0)) {
      iVar2 = PlayerGetDamagedLife(param_3);
      iVar2 = iVar2 + -1;
    }
  }
  return iVar2 - *(int *)(param_3 + 0x1028);
}

/* PlayerGetHitG @ 0x080b5040, 714 bytes
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
undefined4 PlayerGetHitG(int *param_1,int *param_2,int param_3,int param_4)

{
  float10 fVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  
  iVar3 = *(int *)(param_3 + 0x70);
  param_2[0x453] = 0;
  if (iVar3 == 0) {
    iVar3 = *(int *)(*param_1 + 0x11d0);
    iVar6 = *(int *)(param_3 + 0x6c);
    iVar5 = *(int *)(param_3 + 0x68);
    piVar4 = *(int **)(*param_1 + 0x11d4);
  }
  else {
    iVar3 = 0;
    iVar6 = *(int *)(param_3 + 0x6c);
    iVar5 = *(int *)(param_3 + 0x68);
    piVar4 = (int *)g[0x4156];
  }
  GameSndPlayIDPos(-1,(int)GHIDRA_FIST32(GHIDRA_I2F(param_2[0x4d5])),piVar4,iVar5,iVar6,iVar3);
  param_2[0x412] = *(int *)(param_3 + 0xc);
  iVar3 = param_1[2];
  uVar2 = *(undefined4 *)(param_3 + 0x10);
  param_2[0x405] = (int)param_1;
  *(undefined4 *)(param_2[0x452] + iVar3 * 4) = uVar2;
  param_2[0x419] = *(int *)(param_3 + 0x14);
  param_2[0x259] = *param_2 + 0x11b4;
  param_2[0x41a] = 1;
  param_2[0x417] = 0;
  param_2[0x416] = 0;
  param_2[0x2fb] = 0;
  param_2[0x2fc] = -1;
  KBClearCommandValidTimes(param_2 + 0x25a);
  iVar3 = param_2[0x380];
  param_2[0x4f0] = 0;
  if (iVar3 == 2) {
    param_2[0x2fd] = 0x98;
  }
  else {
    if (iVar3 < 3) {
      if (iVar3 == 1) {
        param_2[0x2fd] = 0x96;
        goto LAB_080b51bf;
      }
    }
    else if (iVar3 == 3) {
      param_2[0x2fd] = 0x9a;
      goto LAB_080b51bf;
    }
    sprintf((char *)(g + 0x81d2),"Guard state error: wrong move type",param_1,param_1);
    ErrorExit();
  }
LAB_080b51bf:
  param_2[0x40d] = *(int *)(param_3 + 0x178);
  if (param_2[0x381] != 2) {
    param_2[0x5b] = param_2[0x58];
    param_2[0x5a] = param_2[0x58];
  }
  param_2[900] = 1;
  param_2[0x381] = 2;
  param_2[0x74] = 0;
  param_2[0x37f] = 0;
  param_2[899] = 0;
  param_2[0x387] = 0;
  param_2[0x386] = 0;
  if (param_2[0x380] - 1U < 2) {
    param_2[0x40e] = *(int *)(param_3 + 0x168);
    param_2[0x40f] = *(int *)(param_3 + 0x16c);
    fVar1 = *(float *)(param_3 + 0x164);
    param_2[0x410] = *(int *)(param_3 + 0x170);
    param_2[0x416] = GHIDRA_F2I(int, ((float)-param_4 * fVar1));
    param_2[0x453] = *(int *)(param_3 + 0x180);
  }
  if (param_2[0x380] == 3) {
    param_2[0x416] = GHIDRA_F2I(int, ((float)-param_4 * *(float *)(param_3 + 0x184)));
    param_2[0x417] = *(int *)(param_3 + 0x188);
    param_2[0x410] = *(int *)(param_3 + 0x18c);
    param_2[0x453] = *(int *)(param_3 + 400);
  }
  iVar3 = PlayerGetCorrectedDamage(*(int *)(param_3 + 0x3c),*(int *)(param_3 + 0x28),(int)param_2);
  param_2[0x40a] = param_2[0x40a] + iVar3;
  if ((param_2[7] != 1) || (param_2[0x98a] == 1)) {
    PlayerPowerSet((int)param_2,*(int *)(param_3 + 0x4c) + *(int *)param_2[0x5c]);
  }
  return 1;
}

/* PlayerCheckReversal @ 0x080b5310, 507 bytes
 * FIXUP: 4 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 2 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
undefined4 PlayerCheckReversal(int param_1,int param_2)

{
  float10 fVar1;
  float10 fVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int local_2c;
  uint local_24;
  
  local_24 = (uint)(*(int *)(param_1 + 400) != 1);
  if (*(int *)(param_1 + 0x1158) == 0) {
    return 0;
  }
  if (*(int *)(param_2 + 0x1158) == 0) {
    return 0;
  }
  if (*(int *)(param_1 + 0x1204) == 0) {
    return 0;
  }
  if (*(int *)(*(int *)(param_2 + 0x1148) + *(int *)(param_1 + 8) * 4) == *(int *)(param_1 + 0x1168)
     ) {
    return 0;
  }
  if (*(int *)(*(int *)(param_1 + 0x1148) + *(int *)(param_2 + 8) * 4) == *(int *)(param_2 + 0x1168)
     ) {
    return 0;
  }
  local_2c = *(int *)(param_1 + 0x11dc);
  iVar3 = *(int *)(param_1 + 0x11e0);
  if (local_2c == -1) {
    local_2c = *(int *)(param_1 + 0x5c);
  }
  if (iVar3 == -1) {
    iVar3 = *(int *)(param_1 + 0x60);
  }
  fVar1 = *(float *)(param_1 + 0x1a4);
  fVar2 = *(float *)(param_2 + 0x1a4);
  if (fVar1 < fVar2) {
    iVar4 = *(int *)(param_2 + 0x94);
  }
  else {
    iVar4 = *(int *)(param_2 + 0x94);
    if (fVar1 - fVar2 <= (float)(local_2c + iVar4)) goto LAB_080b54b9;
    if (fVar2 < fVar1) {
      return 0;
    }
  }
  if ((float)(iVar4 + iVar3) < fVar2 - fVar1) {
    return 0;
  }
LAB_080b54b9:
  iVar3 = ClsnArrayDetectRectFlip
                    (*(int **)(*(int *)(*(int *)(param_1 + 0x13bc) + 0x10) + 0x28),
                     *(int **)(*(int *)(*(int *)(param_2 + 0x13bc) + 0x10) + 0x28),
                     (int)GHIDRA_FIST32(((float10)*(int *)(param_2 + 0x1c0) + *(float *)(param_2 + 0x19c)) -
                                ((float10)*(int *)(param_1 + 0x1c0) + *(float *)(param_1 + 0x19c))),
                     (int)GHIDRA_FIST32(((float10)*(int *)(param_2 + 0x1c4) + *(float *)(param_2 + 0x1a0)) -
                                ((float10)*(int *)(param_1 + 0x1c4) + *(float *)(param_1 + 0x1a0))),
                     local_24,(uint)(*(int *)(param_2 + 400) != 1));
  if ((iVar3 != 0) &&
     (uVar5 = *(uint *)(param_2 + 0x1164) & *(uint *)(param_1 + 0x1204), (uVar5 & 7) != 0)) {
    return (uint)((uVar5 & 0xfffffff8) != 0);
  }
  return 0;
}

/* Player1ReverseP2 @ 0x080b5510, 1408 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: 2 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 4 stack locals placed at their original offsets in a 0x50-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 4 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void Player1ReverseP2(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  float10 fVar4;
  float10 fVar5;
  float10 fVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  byte bVar12;
  bool bVar13;
  undefined3 extraout_var;
  int iVar14;
  int *piVar15;
  int iVar16;
  int **ppiVar17;
  int *piVar18;
  unsigned char ghidra_frame[0x50] __attribute__((aligned(16)));
#define local_4c (*(uint *)(ghidra_frame + 0x4))
#define local_48 (*(int **)(ghidra_frame + 0x8))
#define local_3c (*(int **)(ghidra_frame + 0x14))
#define local_38 (*(int *)(ghidra_frame + 0x18))
  
  local_4c = (uint)(param_2[100] != 1);
  iVar14 = param_1[100];
  if (param_1[0x462] != 0) {
    if (param_1[0x457] != 0) {
      return;
    }
    PlayerDropBoundTargets((int)param_1,param_2);
    param_1[0x457] = 1;
  }
  iVar16 = 0;
  bVar12 = 0;
  piVar15 = param_2;
  do {
    if (7 < iVar16) {
LAB_080b55b7:
      bVar13 = (bool)(bVar12 & param_1[0x47a] != -1);
      if (!bVar13) {
        local_48 = PlayerFindTarget(param_1[0x88],(int)param_2);
        if (local_48 == (int *)0x0) {
          ppiVar17 = &local_3c;
          for (iVar16 = 8; iVar16 != 0; iVar16 = iVar16 + -1) {
            *ppiVar17 = (int *)0x0;
            ppiVar17 = ppiVar17 + 1;
          }
          local_38 = param_1[0x19];
          local_3c = param_2;
          iVar16 = ArrayAdd(param_1[0x88],&local_3c,0,0);
          if (iVar16 == -1) {
            return;
          }
          local_48 = (int *)(iVar16 * *(int *)(param_1[0x88] + 4) + *(int *)(param_1[0x88] + 0x14));
        }
        local_48[6] = 0;
        local_48[5] = 0;
        local_48[4] = 0;
        local_48[3] = 0;
        local_48[2] = param_1[0x45a];
      }
      param_1[0x73] = param_1[0x47d];
      param_2[0x73] = param_1[0x47e];
      if (param_2[100] == iVar14) {
        iVar16 = PlayerGetWidth((int)param_1,2,0);
        iVar16 = (-param_1[0x492] - param_2[0x492]) - iVar16;
      }
      else {
        iVar16 = PlayerGetWidth((int)param_1,1,0);
        iVar16 = param_1[0x492] + param_2[0x492] + iVar16;
      }
      iVar7 = param_1[0x70];
      iVar8 = param_1[100];
      iVar1 = g[0x7311];
      fVar3 = GHIDRA_I2F(param_1[0x4d2]);
      fVar4 = GHIDRA_I2F(param_1[0x4d5]);
      iVar9 = param_1[0x493];
      iVar10 = param_2[0x493];
      iVar11 = param_2[0x71];
      iVar2 = g[0x7312];
      fVar5 = GHIDRA_I2F(param_2[0x4d2]);
      fVar6 = GHIDRA_I2F(param_2[0x4d6]);
      if (!bVar13) {
        PlayerGetHit(param_1,param_2,(int)(param_1 + 0x456),GHIDRA_I2F(param_1[0x67]),
                     GHIDRA_I2F(param_1[0x68]),GHIDRA_I2F(param_1[0x69]),iVar14,0,0);
        if ((param_2[0x41c] != 0) || ((*(byte *)(param_1 + 0x474) & 1) != 0)) {
          local_48[1] = local_48[1] - param_1[0x463];
          param_1[0x463] = 0;
        }
        if (param_1[0x494] != 0) {
          param_1[0x65] = -param_1[100];
        }
      }
      param_1[0x387] = param_1[0x46b];
      param_2[0x387] = param_1[0x46a];
      PlayerPowerSet((int)param_1,param_1[0x466] + *(int *)param_1[0x5c]);
      param_2[0x38c] = 4;
      param_2[0x38d] = 0;
      param_2[0x400] = 0xfff;
      param_2[0x3ff] = 0xfff;
      param_2[0x401] = 0;
      param_2[0x402] = 0;
      param_2[0x3fe] = param_1[0x46b];
      if ((param_1[0x459] & 0x1c0U) != 0) {
        param_1[0x3fe] = param_1[0x46b];
      }
      param_1[0x4e6] = param_1[0x4e6] + param_1[0x46c];
      param_1[0x4e7] = param_1[0x4e7] + param_1[0x46c];
      param_1[0x4e8] = param_1[0x4e8] + param_1[0x46c];
      param_1[0x38c] = 2;
      param_1[0x38d] = 0;
      ComboAdd(param_1[3],param_1[0x46c]);
      if ((!bVar13) && ((0 < param_1[0x4bd] || (param_1[0x4bd] == -1)))) {
        piVar15 = param_1 + 0x4bc;
        piVar18 = param_2 + 0x977;
        for (iVar14 = 0xf; iVar14 != 0; iVar14 = iVar14 + -1) {
          *piVar18 = *piVar15;
          piVar15 = piVar15 + 1;
          piVar18 = piVar18 + 1;
        }
      }
      PlayerSparkCreate(param_1,param_1[0x48e],
                        (int)GHIDRA_FIST32((float)((iVar16 - iVar7) * iVar8) * fVar3 + fVar4 + (float10)iVar1)
                        ,(int)GHIDRA_FIST32((float)((iVar9 + iVar10) - iVar11) * fVar5 + fVar6 +
                                    (float10)iVar2),param_1[0x48f],local_4c,0);
      if (!bVar13) {
        if (param_1[0x479] != -1) {
          param_1[0x2fd] = param_1[0x479];
          param_1[0x37f] = 0;
        }
        if (param_1[0x47b] != 0) {
          param_2[0x2fb] = param_1[0x2fa];
          param_2[0x2fc] = param_1[2];
          param_2[0x259] = param_1[0x259];
          KBClearCommandValidTimes(param_2 + 0x25a);
          if (param_1[0x2fb] != 0) {
            param_2[0x2fb] = param_1[0x2fb];
            param_2[0x2fc] = param_1[0x2fc];
          }
          if (param_1[0x4f0] == 0) {
            param_2[0x4f0] = *(int *)param_1[0x4ef];
          }
          else {
            param_2[0x4f0] = param_1[0x4f0];
          }
        }
        if (param_1[0x47a] != -1) {
          PlayerDropBoundTargets((int)param_2,(int *)0x0);
          ExplodRemoveGetHit((undefined4 *)g[0x52be],param_2[1]);
          PlayerChangeState((int)param_2,param_1[0x47a]);
          param_2[899] = 0;
        }
        local_48[6] = param_1[0x47c];
        local_48[3] = param_1[0x499];
        local_48[4] = param_1[0x49a];
        local_48[5] = param_1[0x49b];
      }
      param_2[0x456] = 0;
      if (param_1[0x462] != 0) {
        param_1[0x457] = 1;
      }
      return;
    }
    if ((piVar15[0x42a] != 0) &&
       (bVar13 = AttrMatch(piVar15[0x42b],param_1[0x459]), GHIDRA_ZEXT8(bVar13) != 0)) {
      bVar12 = 1;
      goto LAB_080b55b7;
    }
    piVar15 = piVar15 + 5;
    iVar16 = iVar16 + 1;
  } while( true );
}
#undef local_4c
#undef local_48
#undef local_3c
#undef local_38

/* PlayerCheckHitProj @ 0x080b5a90, 797 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: 6 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 4 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void PlayerCheckHitProj(int param_1,int *param_2)

{
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  bool bVar10;
  int iVar11;
  undefined3 extraout_var;
  int iVar12;
  int iVar13;
  int *piVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  uint local_28;
  
  iVar5 = *(int *)param_2[0x87];
  local_28 = (uint)(*(int *)(param_1 + 400) != 1);
  piVar6 = *(int **)(*(int *)(*(int *)(param_1 + 0x13bc) + 0x10) + 0x28);
  if (((*(char *)(param_1 + 0x11d0) < '\0') && (*(int *)(param_1 + 0xe04) != 0)) &&
     (*(int *)(param_1 + 0x1158) != 0)) {
    iVar11 = ArrayScanFirst(iVar5);
    while (iVar11 != 0) {
      iVar13 = *(int *)(iVar11 + 0x34);
      if (*(int *)(iVar11 + 4) == 1) {
        bVar10 = HitdefAffectTeam(param_1 + 0x1158,*(int *)(param_1 + 0xc),*(uint *)(iVar11 + 8));
        if ((GHIDRA_ZEXT8(bVar10) != 0) && (*(int *)(iVar11 + 0x28) < 1)) {
          iVar12 = (int)GHIDRA_FIST32((float10)(int)GHIDRA_FIST32(*(float *)(param_1 + 0x1a4)) -
                              *(float *)(iVar11 + 0x4c));
          if (iVar12 < 0) {
            iVar12 = -iVar12;
          }
          if ((iVar12 < 9) && (*(int *)(iVar11 + 0x2c) < 1)) {
            iVar13 = ClsnArrayDetectRectFlip
                               (*(int **)(*(int *)(iVar11 + 0x294) + 0x2c),piVar6,
                                (int)GHIDRA_FIST32(((float10)*(int *)(param_1 + 0x1c0) +
                                           *(float *)(param_1 + 0x19c)) - *(float *)(iVar11 + 0x44))
                                ,(int)GHIDRA_FIST32(((float10)*(int *)(param_1 + 0x1c4) +
                                            *(float *)(param_1 + 0x1a0)) - *(float *)(iVar11 + 0x48)
                                           ),(uint)(iVar13 != 1),local_28);
            piVar14 = g;
            if ((iVar13 != 0) && (0 < *(int *)(iVar11 + 0x1c))) {
              iVar12 = g[0x109e];
              iVar7 = g[0x109f];
              fVar1 = *(float *)(iVar11 + 0x4c);
              iVar8 = *(int *)(iVar11 + 0x188);
              iVar9 = *(int *)(iVar11 + 0x34);
              fVar2 = GHIDRA_I2F(g[0x10a0]);
              fVar3 = GHIDRA_I2F(g[0x10a1]);
              iVar13 = g[0x7311];
              fVar4 = *(float *)(iVar11 + 0x44);
              *(undefined4 *)(param_1 + 0x1158) = 0;
              if (*(int *)(iVar11 + 0x108) == 0) {
                iVar17 = *(int *)(*param_2 + 0x11d0);
                iVar16 = *(int *)(iVar11 + 0x104);
                iVar15 = *(int *)(iVar11 + 0x100);
                piVar14 = *(int **)(*param_2 + 0x11d4);
              }
              else {
                iVar17 = 0;
                iVar16 = *(int *)(iVar11 + 0x104);
                iVar15 = *(int *)(iVar11 + 0x100);
                piVar14 = (int *)piVar14[0x4156];
              }
              GameSndPlayIDPos(-1,(int)GHIDRA_FIST32((((fVar4 - (float10)iVar13) - 160.0) +
                                             (float)(iVar9 * iVar8)) *
                                             (((fVar1 - (float10)iVar12) / (float)(iVar7 - iVar12)) *
                                              (fVar3 - fVar2) + fVar2) + (float10)iVar13 + 160.0),
                               piVar14,iVar15,iVar16,iVar17);
              if (*(int *)(param_1 + 0x11e4) != -1) {
                *(int *)(param_1 + 0xbf4) = *(int *)(param_1 + 0x11e4);
                *(undefined4 *)(param_1 + 0xdfc) = 0;
              }
              iVar13 = *(int *)(iVar11 + 0x1c) + -1;
              *(int *)(iVar11 + 0x1c) = iVar13;
              if ((iVar13 < 1) && (*(int *)(iVar11 + 0x38) != 0)) {
                *(undefined4 *)(iVar11 + 4) = 2;
                *(undefined4 *)(iVar11 + 0x24) = 0;
              }
              else {
                *(undefined4 *)(iVar11 + 0x28) = *(undefined4 *)(iVar11 + 0xec);
              }
            }
          }
        }
      }
      iVar11 = ArrayScanNext(iVar5);
    }
  }
  return;
}

/* PlayerCheckProjHit @ 0x080b5db0, 2475 bytes
 * FIXUP: 2 float-field accesses rewritten as bit reinterpretations (asm: x87 single loads/stores at offsets 0x44, 0x48)
 * FIXUP: 2 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: 4 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 7 stack locals placed at their original offsets in a 0x80-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void PlayerCheckProjHit(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  float10 fVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  int *piVar8;
  int iVar9;
  undefined3 extraout_var;
  int iVar10;
  undefined3 extraout_var_00;
  int iVar11;
  int *piVar12;
  int **ppiVar13;
  int *piVar14;
  unsigned char ghidra_frame[0x80] __attribute__((aligned(16)));
#define local_74 (*(uint *)(ghidra_frame + 0xc))
#define local_68 (*(uint *)(ghidra_frame + 0x18))
#define local_5c (*(uint *)(ghidra_frame + 0x24))
#define local_54 (*(int **)(ghidra_frame + 0x2c))
#define local_50 (*(int **)(ghidra_frame + 0x30))
#define local_3c (*(int **)(ghidra_frame + 0x44))
#define local_38 (*(int *)(ghidra_frame + 0x48))
  
  iVar1 = *(int *)param_1[0x87];
  local_5c = (uint)(param_2[100] != 1);
  iVar2 = g[param_1[3] + 0x7506];
  piVar3 = *(int **)(*(int *)(param_2[0x4ef] + 0x10) + 0x2c);
  if (param_2[0x3fe] < 1) {
    piVar8 = (int *)ArrayScanFirst(iVar1);
    while (piVar8 != (int *)0x0) {
      piVar12 = piVar8 + 0x26;
      local_74 = (uint)(piVar8[0xd] != 1);
      if (((piVar8[1] < 3) && (0 < piVar8[1])) && (piVar8[10] < 1)) {
        iVar9 = (int)GHIDRA_FIST32((float10)(int)GHIDRA_FIST32(GHIDRA_I2F(param_2[0x69])) - GHIDRA_I2F(piVar8[0x13]));
        if (iVar9 < 0) {
          iVar9 = -iVar9;
        }
        if (((((iVar9 < 9) &&
              (bVar6 = HitdefAffectTeam((int)piVar12,piVar8[2],param_2[3]),
              GHIDRA_ZEXT8(bVar6) != 0)) &&
             ((iVar9 = PlayerCheckAttrHit((int)param_2,piVar8[0x29]), iVar9 != 0 &&
              ((piVar8[0xb] < 1 &&
               (iVar9 = ClsnArrayDetectRectFlip
                                  (*(int **)(piVar8[0xa5] + 0x28),piVar3,
                                   (int)GHIDRA_FIST32(((float10)param_2[0x70] + GHIDRA_I2F(param_2[0x67])) -
                                              (*(float *)&piVar8[0x11])),
                                   (int)GHIDRA_FIST32(((float10)param_2[0x71] + GHIDRA_I2F(param_2[0x68])) -
                                              (*(float *)&piVar8[0x12])),local_74,local_5c), iVar9 != 0)))
              ))) && (iVar9 = PlayerCheckFlagHit((int)param_2,piVar8[0x44]), iVar9 != 0)) &&
           (0 < piVar8[7])) {
          bVar6 = false;
          local_68 = 0;
          iVar9 = PlayerCheckFlagHit((int)param_2,piVar8[0x43]);
          if (((iVar9 == 0) || (param_2[900] == 0)) || (*(char *)((int)param_1 + 0x20b) != '\0')) {
            iVar9 = PlayerGetDamagedLife((int)param_2);
            iVar10 = PlayerGetCorrectedDamage(piVar8[0x34],piVar8[0x2f],(int)param_2);
            if (iVar9 == iVar10 || iVar9 - iVar10 < 0) {
              WinIconCheckTeam(param_2[3],param_1[3],piVar8[0x29]);
LAB_080b6114:
              local_68 = 1;
            }
          }
          else {
            iVar9 = PlayerGetDamagedLife((int)param_2);
            iVar10 = PlayerGetCorrectedDamage(piVar8[0x35],piVar8[0x30],(int)param_2);
            if (iVar9 == iVar10 || iVar9 - iVar10 < 0) {
              local_68 = 1;
              if ((g[0x7511] != 3) && (iVar2 < 10)) {
                WinIconCheck(param_1[3],0,3);
                goto LAB_080b6114;
              }
            }
            else {
              bVar6 = true;
            }
          }
          local_68 = local_68 & (g[0x730b] != 0) - 1;
          bVar5 = false;
          piVar14 = param_2 + 0x42a;
          for (iVar9 = 0; iVar9 < 8; iVar9 = iVar9 + 1) {
            local_54 = piVar14;
            if ((*piVar14 != 0) &&
               (bVar7 = AttrMatch(piVar14[1],piVar8[0x29]), GHIDRA_ZEXT8(bVar7) != 0)) {
              bVar5 = true;
              break;
            }
            piVar14 = piVar14 + 5;
          }
          if (bVar5) {
            bVar6 = false;
            local_68 = 0;
          }
          else {
            local_54 = (int *)0x0;
            param_2[0x73] = piVar8[0x4e];
            local_50 = PlayerFindTarget(param_1[0x88],(int)param_2);
            if (local_50 == (int *)0x0) {
              ppiVar13 = &local_3c;
              for (iVar9 = 8; iVar9 != 0; iVar9 = iVar9 + -1) {
                *ppiVar13 = (int *)0x0;
                ppiVar13 = ppiVar13 + 1;
              }
              local_3c = param_2;
              local_38 = param_1[0x19];
              iVar9 = ArrayAdd(param_1[0x88],&local_3c,0,0);
              if (iVar9 == -1) goto LAB_080b6739;
              local_50 = (int *)(iVar9 * *(int *)(param_1[0x88] + 4) +
                                *(int *)(param_1[0x88] + 0x14));
            }
            local_50[6] = 0;
            local_50[5] = 0;
            local_50[4] = 0;
            local_50[3] = 0;
            if ((*(char *)((int)param_1 + 0x209) == '\0') && (local_50[1] - piVar8[0x33] < 0))
            goto LAB_080b6739;
          }
          fVar4 = ((GHIDRA_I2F(piVar8[0x13]) - (float)g[0x109e]) / (float)(g[0x109f] - g[0x109e])) *
                  (GHIDRA_I2F(g[0x10a1]) - GHIDRA_I2F(g[0x10a0])) + GHIDRA_I2F(g[0x10a0]);
          iVar9 = (int)GHIDRA_FIST32((((GHIDRA_I2F(piVar8[0x11]) - (float)g[0x7311]) - 160.0) +
                             (float)(piVar8[0xd] * piVar8[0x62])) * fVar4 + (float)g[0x7311] + 160.0
                            );
          iVar10 = (int)GHIDRA_FIST32(((float10)piVar8[99] + GHIDRA_I2F(piVar8[0x12])) * fVar4 +
                              GHIDRA_I2F(piVar8[0x13]) + (float)g[0x4140]);
          if (bVar6) {
            PlayerGetHitG(param_1,param_2,(int)piVar12,piVar8[0xd]);
            PlayerPowerSet((int)param_1,piVar8[0x37] + *(int *)param_1[0x5c]);
            PlayerSparkCreate(param_1,piVar8[0x60],iVar9,iVar10,piVar8[0x61],local_74,1);
            param_1[0x84] = *piVar8;
            param_1[0x85] = 1;
            param_1[0x86] = 0;
          }
          else {
            PlayerGetHit(param_1,param_2,(int)piVar12,GHIDRA_I2F(piVar8[0x11]),GHIDRA_I2F(piVar8[0x12]),
                         GHIDRA_I2F(piVar8[0x13]),piVar8[0xd],local_68,(int)local_54);
            PlayerPowerSet((int)param_1,piVar8[0x36] + *(int *)param_1[0x5c]);
            if ((((!bVar5) && (*(char *)((int)param_1 + 0x209) == '\0')) && (param_2[0x41c] != 0))
               && (piVar8[0x33] != -1)) {
              local_50[1] = local_50[1] - piVar8[0x33];
              piVar8[0x33] = 0;
            }
            param_1[0x4e6] = param_1[0x4e6] + piVar8[0x3c];
            ComboAdd(param_1[3],piVar8[0x3c]);
            param_1[0x84] = *piVar8;
            param_1[0x85] = 2;
            param_1[0x86] = 0;
            param_2[0x400] = 0x1ff;
            param_2[0x402] = 0;
            if ((!bVar5) && ((0 < piVar8[0x8d] || (piVar8[0x8d] == -1)))) {
              piVar12 = piVar8 + 0x8c;
              piVar14 = param_2 + 0x977;
              for (iVar11 = 0xf; iVar11 != 0; iVar11 = iVar11 + -1) {
                *piVar14 = *piVar12;
                piVar12 = piVar12 + 1;
                piVar14 = piVar14 + 1;
              }
            }
            PlayerSparkCreate(param_1,piVar8[0x5e],iVar9,iVar10,piVar8[0x5f],local_74,0);
            if (bVar5) {
              if (local_54[2] != -1) {
                PlayerChangeState((int)param_2,local_54[2]);
              }
            }
            else {
              if (piVar8[0x49] != -1) {
                param_1[0x2fd] = piVar8[0x49];
                param_1[0x37f] = 0;
              }
              if (piVar8[0x4b] != 0) {
                param_2[0x2fb] = param_1[0x2fa];
                param_2[0x2fc] = param_1[2];
                param_2[0x259] = param_1[0x259];
                KBClearCommandValidTimes(param_2 + 0x25a);
                if (param_1[0x2fb] != 0) {
                  param_2[0x2fb] = param_1[0x2fb];
                  param_2[0x2fc] = param_1[0x2fc];
                }
                if (param_1[0x4f0] == 0) {
                  param_2[0x4f0] = *(int *)param_1[0x4ef];
                }
                else {
                  param_2[0x4f0] = param_1[0x4f0];
                }
              }
              if (piVar8[0x4a] != -1) {
                PlayerChangeState((int)param_2,piVar8[0x4a]);
                param_2[899] = 0;
              }
              local_50[6] = piVar8[0x4c];
              local_50[3] = piVar8[0x69];
              local_50[4] = piVar8[0x6a];
              local_50[5] = piVar8[0x6b];
            }
          }
          piVar8[0xb1] = 1;
          if ((piVar8[7] == 1 || piVar8[7] + -1 < 0) && (piVar8[0xe] != 0)) {
            piVar8[0xb2] = 0;
            piVar8[0xb3] = 0;
          }
          else {
            piVar8[0xb2] = piVar8[0x3b];
            piVar8[0xb3] = piVar8[0xc];
          }
        }
      }
LAB_080b6739:
      piVar8 = (int *)ArrayScanNext(iVar1);
    }
  }
  return;
}
#undef local_74
#undef local_68
#undef local_5c
#undef local_54
#undef local_50
#undef local_3c
#undef local_38

/* PlayerProjDoHit @ 0x080b6760, 116 bytes */
undefined4 PlayerProjDoHit(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uStack_c;
  
  iVar1 = **(int **)(param_1 + 0x21c);
  iVar2 = ArrayScanFirst(iVar1);
  while (iVar2 != 0) {
    if (*(int *)(iVar2 + 0x2c4) != 0) {
      *(undefined4 *)(iVar2 + 0x2c) = *(undefined4 *)(iVar2 + 0x2cc);
      *(undefined4 *)(iVar2 + 0x28) = *(undefined4 *)(iVar2 + 0x2c8);
      iVar3 = *(int *)(iVar2 + 0x1c) + -1;
      *(undefined4 *)(iVar2 + 0x2c4) = 0;
      *(int *)(iVar2 + 0x1c) = iVar3;
      if ((iVar3 < 1) && (*(int *)(iVar2 + 0x38) != 0)) {
        *(undefined4 *)(iVar2 + 4) = 4;
        *(undefined4 *)(iVar2 + 0x24) = 0;
      }
    }
    iVar2 = ArrayScanNext(iVar1);
  }
  return uStack_c;
}

/* CheckProjHitProj @ 0x080b67e0, 626 bytes
 * FIXUP: 2 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
undefined4 CheckProjHitProj(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  bool bVar5;
  int iVar6;
  int iVar7;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar8;
  
  iVar1 = **(int **)(param_1 + 0x21c);
  iVar2 = **(int **)(param_2 + 0x21c);
  iVar6 = ArrayScanFirst(iVar1);
  do {
    if (iVar6 == 0) {
      return 0;
    }
    iVar3 = *(int *)(iVar6 + 0x34);
    piVar4 = *(int **)(*(int *)(iVar6 + 0x294) + 0x2c);
    if ((piVar4 != (int *)0x0) && (*(int *)(iVar6 + 4) == 1)) {
      iVar7 = ArrayScanFirst(iVar2);
      while (iVar7 != 0) {
        if ((((int)GHIDRA_FIST32(*(float *)(iVar7 + 0x4c)) - (int)GHIDRA_FIST32(*(float *)(iVar6 + 0x4c))) + 8U <
             0x11) && (*(int *)(iVar7 + 4) == 1)) {
          bVar5 = HitdefAffectTeam(iVar6 + 0x98,*(int *)(iVar6 + 8),*(uint *)(iVar7 + 8));
          if (GHIDRA_ZEXT8(bVar5) == 0) {
            bVar5 = HitdefAffectTeam(iVar7 + 0x98,*(int *)(iVar7 + 8),*(uint *)(iVar6 + 8));
            if (GHIDRA_ZEXT8(bVar5) == 0) goto LAB_080b6a16;
          }
          iVar8 = ClsnArrayDetectRectFlip
                            (piVar4,*(int **)(*(int *)(iVar7 + 0x294) + 0x2c),
                             (int)GHIDRA_FIST32(*(float *)(iVar7 + 0x44) - *(float *)(iVar6 + 0x44)),
                             (int)GHIDRA_FIST32(*(float *)(iVar7 + 0x48) - *(float *)(iVar6 + 0x48)),
                             (uint)(iVar3 != 1),(uint)(*(int *)(iVar7 + 0x34) != 1));
          if (iVar8 != 0) {
            iVar3 = *(int *)(iVar7 + 0xc);
            iVar8 = *(int *)(iVar6 + 0xc);
            if (iVar8 <= iVar3) {
              *(int *)(iVar6 + 0x1c) = *(int *)(iVar6 + 0x1c) + -1;
            }
            if (*(int *)(iVar6 + 0x1c) < 1) {
              *(undefined4 *)(iVar6 + 4) = 3;
              *(undefined4 *)(iVar6 + 0x24) = 0;
              *(undefined4 *)(param_1 + 0x214) = 3;
              *(undefined4 *)(param_1 + 0x218) = 0;
            }
            else {
              *(undefined4 *)(iVar6 + 0x28) = *(undefined4 *)(iVar6 + 0xec);
            }
            if (*(int *)(iVar7 + 0xc) <= *(int *)(iVar6 + 0xc)) {
              *(int *)(iVar6 + 0xc) = *(int *)(iVar6 + 0xc) + -1;
              *(int *)(iVar7 + 0x1c) = *(int *)(iVar7 + 0x1c) + -1;
            }
            if (*(int *)(iVar7 + 0x1c) < 1) {
              *(undefined4 *)(iVar7 + 4) = 3;
              *(undefined4 *)(iVar7 + 0x24) = 0;
              *(undefined4 *)(param_2 + 0x214) = 3;
              *(undefined4 *)(param_2 + 0x218) = 0;
            }
            else {
              *(undefined4 *)(iVar7 + 0x28) = *(undefined4 *)(iVar7 + 0xec);
            }
            if (iVar8 <= iVar3) {
              *(int *)(iVar7 + 0xc) = *(int *)(iVar7 + 0xc) + -1;
            }
            break;
          }
        }
LAB_080b6a16:
        iVar7 = ArrayScanNext(iVar2);
      }
    }
    iVar6 = ArrayScanNext(iVar1);
  } while( true );
}

/* PlayerCheckFlagHit @ 0x080b6a60, 149 bytes */
undefined4 PlayerCheckFlagHit(int param_1,uint param_2)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = *(int *)(param_1 + 0xe00);
  if ((((iVar1 != 4) || ((param_2 & 0x40) != 0)) &&
      ((*(int *)(param_1 + 0xe04) != 2 || ((param_2 & 2) != 0)))) &&
     ((((*(int *)(param_1 + 0xe04) == 2 && (*(int *)(param_1 + 0xe10) == 0)) ||
       ((param_2 & 0x100) == 0)) && ((*(int *)(param_1 + 0x1070) == 0 || ((param_2 & 0x20) != 0)))))
     ) {
    if (iVar1 == 2) {
      bVar2 = (param_2 & 8) == 0;
    }
    else if (iVar1 < 3) {
      if (iVar1 != 1) {
        return 0;
      }
      bVar2 = (param_2 & 4) == 0;
    }
    else if (iVar1 == 3) {
      bVar2 = (param_2 & 0x10) == 0;
    }
    else {
      if (iVar1 != 4) {
        return 0;
      }
      bVar2 = (param_2 & 0x40) == 0;
    }
    if (!bVar2) {
      return 1;
    }
  }
  return 0;
}

/* PlayerCheckAttrHit @ 0x080b6b00, 24 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
undefined4 PlayerCheckAttrHit(int param_1,uint param_2)

{
  bool bVar1;
  undefined3 extraout_var;
  
  bVar1 = AttrMatch(*(uint *)(param_1 + 0x1000) & *(uint *)(param_1 + 0xffc),param_2);
  return GHIDRA_ZEXT8(bVar1);
}

/* AttrMatch @ 0x080b6b20, 30 bytes */
bool AttrMatch(uint param_1,uint param_2)

{
  if ((param_2 & param_1 & 7) == 0) {
    return false;
  }
  return (param_2 & param_1 & 0xfffffff8) != 0;
}

/* PlayerAttrStateSet @ 0x080b6b40, 90 bytes */
void PlayerAttrStateSet(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(param_1 + 0xe00);
  uVar2 = *(uint *)(param_1 + 0x1164) & 0xfffffff8;
  *(uint *)(param_1 + 0x1164) = uVar2;
  if (iVar1 == 2) {
    *(uint *)(param_1 + 0x1164) = uVar2 | 2;
    return;
  }
  if (iVar1 < 3) {
    if (iVar1 != 1) {
      return;
    }
    *(uint *)(param_1 + 0x1164) = uVar2 | 1;
    return;
  }
  if (iVar1 != 3) {
    return;
  }
  *(uint *)(param_1 + 0x1164) = uVar2 | 4;
  return;
}

/* PlayerDropBoundTargets @ 0x080b6ba0, 183 bytes */
void PlayerDropBoundTargets(int param_1,int *param_2)

{
  int *piVar1;
  int *piVar2;
  
  piVar2 = (int *)ArrayScanFirst(*(int *)(param_1 + 0x220));
  while (piVar2 != (int *)0x0) {
    piVar1 = (int *)*piVar2;
    if (piVar1 != param_2) {
      if ((piVar2[7] != 0) && (piVar1[7] == 0)) {
        piVar1[0x259] = *piVar1 + 0x11b4;
        piVar1[0x2fb] = 0;
        piVar1[0x2fc] = -1;
        KBClearCommandValidTimes(piVar1 + 0x25a);
        piVar1[0x4f0] = 0;
        PlayerChangeState((int)piVar1,0x13ba);
      }
      ArrayDelete(*(int *)(param_1 + 0x220),*(int *)(*(int *)(param_1 + 0x220) + 0x1c));
    }
    piVar2 = (int *)ArrayScanNext(*(int *)(param_1 + 0x220));
  }
  return;
}

/* PlayerSparkCreate @ 0x080b6c60, 310 bytes */
int PlayerSparkCreate(int *param_1,int param_2,int param_3,int param_4,int param_5,
                     undefined4 param_6,int param_7)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int *piVar5;
  
  if (param_2 == -2) {
    if (param_7 == 0) {
      param_2 = param_1[0x4f];
    }
    else {
      param_2 = param_1[0x50];
    }
  }
  if (param_2 == -1) {
    iVar2 = -1;
  }
  else {
    if (param_5 == 0) {
      iVar2 = g[0x4147];
      piVar5 = (int *)g[0x4148];
      puVar4 = (undefined4 *)g[0x52be];
    }
    else {
      iVar2 = param_1[0x4ed];
      piVar5 = *(int **)(*param_1 + 0x11cc);
      puVar4 = (undefined4 *)g[0x52be];
    }
    iVar2 = ExplodAdd(puVar4,param_2,piVar5,iVar2);
    if (iVar2 != -1) {
      iVar1 = *(int *)g[0x52be] + iVar2 * 0xe4;
      *(undefined4 *)(iVar1 + 0x10) = 0;
      *(undefined4 *)(iVar1 + 0xc) = 0;
      *(undefined4 *)(iVar1 + 0x6c) = 1;
      *(undefined4 *)(iVar1 + 0x70) = 1;
      *(undefined4 *)(iVar1 + 0x5c) = 3;
      *(int *)(iVar1 + 0x2c) = param_3;
      *(undefined4 *)(iVar1 + 0x68) = param_6;
      *(int *)(iVar1 + 0x30) = param_4;
      *(float *)(iVar1 + 0x14) = (float)param_3;
      *(float *)(iVar1 + 0x18) = (float)param_4;
      *(undefined4 *)(iVar1 + 100) = 2;
      uVar3 = AnimGetLooptime(*(undefined4 **)(iVar1 + 0x80));
      *(undefined4 *)(iVar1 + 0x40) = uVar3;
      *(undefined4 *)(iVar1 + 0x38) = uVar3;
      *(undefined4 *)(iVar1 + 0x34) = uVar3;
      *(undefined4 *)(*(int *)(iVar1 + 0x80) + 0x30) = 0;
    }
  }
  return iVar2;
}

/* PlayerMakeDust @ 0x080b6da0, 415 bytes
 * FIXUP: 4 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 2 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
int PlayerMakeDust(int param_1)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  float10 fVar4;
  longlong lVar5;
  bool bVar6;
  int *piVar7;
  int iVar8;
  long lVar9;
  long lVar10;
  undefined4 uVar11;
  
  bVar6 = false;
  lVar5 = (longlong)g[0x7514] / 3;
  iVar8 = (int)lVar5;
  if (g[0x7514] % 3 == 0) {
    fVar3 = *(float *)(param_1 + 0x1a0);
    iVar8 = CONCAT22((short)((ulonglong)lVar5 >> 0x10),
                     (ushort)(fVar3 < 0.0) << 8 | (ushort)GHIDRA_ISNAN(fVar3) << 10 |
                     (ushort)(fVar3 == 0.0) << 0xe);
    if (((((fVar3 == 0.0) != 0) && (iVar8 = *(int *)(param_1 + 0xe00), iVar8 != 3)) && (iVar8 != 4))
       && ((iVar8 = *(int *)(param_1 + 0xe04), iVar8 != 0 && (iVar8 = iVar8 + -1, iVar8 != 0)))) {
      bVar6 = true;
    }
    if (*(int *)(param_1 + 0xbf4) == 0x34) {
      bVar6 = true;
    }
  }
  if (bVar6) {
    lVar9 = random();
    iVar1 = g[0x7311];
    fVar3 = *(float *)(param_1 + 0x1354);
    lVar10 = random();
    iVar2 = g[0x7312];
    fVar4 = *(float *)(param_1 + 0x1358);
    iVar8 = ExplodAdd((undefined4 *)g[0x52be],0x78,(int *)g[0x4148],g[0x4147]);
    if (iVar8 != -1) {
      iVar8 = *(int *)g[0x52be] + iVar8 * 0xe4;
      *(float *)(iVar8 + 0x14) =
           (float10)(int)GHIDRA_FIST32(((float)(lVar9 % 3) + (float10)iVar1 + fVar3) - 1.0);
      *(float *)(iVar8 + 0x18) =
           (float10)(int)GHIDRA_FIST32(((float)(lVar10 % 3) + (float10)iVar2 + fVar4) - 1.0);
      *(undefined4 *)(iVar8 + 0x6c) = 1;
      uVar11 = AnimGetLooptime(*(undefined4 **)(iVar8 + 0x80));
      iVar1 = *(int *)(iVar8 + 0x80);
      *(undefined4 *)(iVar8 + 0x40) = uVar11;
      piVar7 = g;
      *(undefined4 *)(iVar1 + 0x34) = 10;
      iVar8 = piVar7[0x413d];
      *(int *)(iVar1 + 0x30) = iVar8;
    }
  }
  return iVar8;
}

/* PlayerCalcDraw @ 0x080b6f40, 629 bytes
 * FIXUP: 1 float-field accesses rewritten as bit reinterpretations (asm: x87 single loads/stores at offsets 0x4280)
 * FIXUP: 3 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
int PlayerCalcDraw(int param_1)

{
  int iVar1;
  int *piVar2;
  int local_c;
  
  if ((((((int)GHIDRA_FIST32(*(float *)(param_1 + 0x1a4)) == *(int *)(param_1 + 0x1364)) &&
        ((int)GHIDRA_FIST32(*(float *)(param_1 + 0x1a0)) == *(int *)(param_1 + 0x1360))) &&
       (local_c = (int)GHIDRA_FIST32(*(float *)(param_1 + 0x19c)), local_c == *(int *)(param_1 + 0x135c)))
      && ((g[0x7311] == *(int *)(param_1 + 0x1368) && (g[0x7312] == *(int *)(param_1 + 0x136c)))))
     && ((g[0x4140] == *(int *)(param_1 + 0x1370) &&
         ((*(int *)(param_1 + 0x1c0) == *(int *)(param_1 + 0x1374) &&
          (*(int *)(param_1 + 0x1c4) == *(int *)(param_1 + 0x1378))))))) {
    if (*(int *)(param_1 + 0x1e4) != 0) {
      ScreenBound(param_1);
    }
  }
  else {
    *(float *)(param_1 + 0x1348) =
         (GHIDRA_I2F(g[0x10a1]) - GHIDRA_I2F(g[0x10a0])) *
         ((*(float *)(param_1 + 0x1a4) - (float)g[0x109e]) / (float)((g[0x109f] - g[0x109e]) + 1)) +
         (*(float *)&g[0x10a0]);
    if (*(int *)(param_1 + 0x1e4) != 0) {
      ScreenBound(param_1);
    }
    piVar2 = g;
    iVar1 = g[0x4140];
    *(float *)(param_1 + 0x1354) =
         ((((float10)*(int *)(param_1 + 0x1c0) + *(float *)(param_1 + 0x19c)) - GHIDRA_I2F(g[0x730f])) -
         160.0) * *(float *)(param_1 + 0x1348) + 160.0;
    *(float *)(param_1 + 0x1358) =
         (((float10)*(int *)(param_1 + 0x1c4) + *(float *)(param_1 + 0x1a0)) *
          *(float *)(param_1 + 0x1348) - GHIDRA_I2F(piVar2[0x7310])) + *(float *)(param_1 + 0x1a4) +
         (float10)iVar1;
    *(int *)(param_1 + 0x135c) = (int)GHIDRA_FIST32(*(float *)(param_1 + 0x19c));
    *(int *)(param_1 + 0x1360) = (int)GHIDRA_FIST32(*(float *)(param_1 + 0x1a0));
    local_c = (int)GHIDRA_FIST32(*(float *)(param_1 + 0x1a4));
    *(int *)(param_1 + 0x1364) = local_c;
    *(int *)(param_1 + 0x1368) = piVar2[0x7311];
    *(int *)(param_1 + 0x136c) = piVar2[0x7312];
    *(int *)(param_1 + 0x1370) = piVar2[0x4140];
    *(undefined4 *)(param_1 + 0x1374) = *(undefined4 *)(param_1 + 0x1c0);
    *(undefined4 *)(param_1 + 0x1378) = *(undefined4 *)(param_1 + 0x1c4);
  }
  return local_c;
}

/* PlayerDrawAnim @ 0x080b71c0, 499 bytes
 * FIXUP: 2 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 4 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void PlayerDrawAnim(int param_1,float param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  float10 fVar5;
  float10 fVar6;
  float10 fVar7;
  float10 fVar8;
  uint uVar9;
  
  fVar7 = *(float *)(param_1 + 0x1354) - (float)g[0x7315];
  fVar5 = *(float *)(param_1 + 0x7c) * *(float *)(param_1 + 0x1348) * *(float *)(param_1 + 0x134c) *
          param_2;
  uVar9 = (uint)(*(int *)(param_1 + 400) != 1);
  fVar6 = *(float *)(param_1 + 0x80) * *(float *)(param_1 + 0x1348) * *(float *)(param_1 + 0x1350) *
          param_2;
  fVar8 = *(float *)(param_1 + 0x1358) - (float)g[0x7316];
  if ((*(int *)(param_1 + 0xe04) == 2) && (0 < *(int *)(param_1 + 0x1034))) {
    fVar7 = (float10)(int)((*(uint *)(param_1 + 0xdfc) & 1) * *(int *)(param_1 + 400)) + fVar7;
  }
  *(int *)(*(int *)(param_1 + 0x13bc) + 0x34) =
       (int)GHIDRA_FIST32(*(float *)(param_1 + 0x1a4) * 10.0 + (float10)*(int *)(param_1 + 0x1cc));
  iVar1 = *(int *)(param_1 + 0x13bc);
  uVar2 = *(undefined4 *)(iVar1 + 0x20);
  *(undefined4 *)(iVar1 + 0x20) = *(undefined4 *)(param_1 + 5000);
  uVar3 = *(undefined4 *)(iVar1 + 0x24);
  *(undefined4 *)(iVar1 + 0x24) = *(undefined4 *)(param_1 + 0x138c);
  uVar4 = *(undefined4 *)(iVar1 + 0x28);
  *(undefined4 *)(iVar1 + 0x28) = *(undefined4 *)(param_1 + 0x1390);
  if (*(int *)(param_1 + 0x1380) == 0) {
    AnimDrawScaleFlip(*(undefined4 **)(param_1 + 0x13bc),(int)GHIDRA_FIST32(fVar7),(int)GHIDRA_FIST32(fVar8),fVar5,
                      fVar6,uVar9);
  }
  else {
    AnimDrawRotateFlip(*(undefined4 **)(param_1 + 0x13bc),(int)GHIDRA_FIST32(fVar7),(int)GHIDRA_FIST32(fVar8),
                       *(float *)(param_1 + 0x137c),fVar5,fVar6,uVar9);
  }
  iVar1 = *(int *)(param_1 + 0x13bc);
  *(undefined4 *)(iVar1 + 0x20) = uVar2;
  *(undefined4 *)(iVar1 + 0x24) = uVar3;
  *(undefined4 *)(iVar1 + 0x28) = uVar4;
  return;
}

/* PlayerDrawShadow @ 0x080b73c0, 1507 bytes
 * REVIEW: calls-missing-in-pid:NAN
 * FIXUP: 16 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 4 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void PlayerDrawShadow(int param_1,int *param_2,int *param_3)

{
  int iVar1;
  int *piVar2;
  float10 fVar3;
  float10 fVar4;
  float10 fVar5;
  int iVar6;
  int iVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  float10 fVar15;
  int local_44;
  int local_40;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x13bc) + 0x10);
  piVar2 = *(int **)(*(int *)(param_1 + 0x13bc) + 4);
  iVar12 = *(int *)(param_1 + 400);
  bVar8 = (byte)_rgb_r_shift_16;
  bVar9 = (byte)_rgb_g_shift_16;
  bVar10 = (byte)_rgb_b_shift_16;
  if (*(int *)(param_1 + 0x1380) == 0) {
    local_40 = 0;
  }
  else {
    local_40 = (int)GHIDRA_FIST32((float)-iVar12 * *(float *)(param_1 + 0x137c));
  }
  local_44 = *param_2;
  uVar14 = param_2[1];
  if ((g[0x7570] != 0) && (iVar6 = AnimCurSpriteIdx(*(int *)(param_1 + 0x13bc)), iVar6 != -1)) {
    iVar7 = *(int *)(iVar1 + 0x14) + *(int *)(param_1 + 0x1c4);
    fVar5 = *(float *)(param_1 + 0x7c) * *(float *)(param_1 + 0x1348) * *(float *)(param_1 + 0x134c)
    ;
    fVar4 = *(float *)(param_1 + 0x80) * *(float *)(param_1 + 0x1348) * *(float *)(param_1 + 0x1350)
    ;
    fVar3 = ((float10)iVar12 * (float10)*(int *)(iVar1 + 0x10) * fVar5 + *(float *)(param_1 + 0x1354)) -
            (float)g[0x7315];
    if (0 < *(int *)(param_1 + 0x1034)) {
      fVar3 = (float10)(int)((*(uint *)(param_1 + 0xdfc) & 1) * iVar12) + fVar3;
    }
    uVar11 = (uint)(iVar12 != 1) ^ *(uint *)(iVar1 + 0x18) & 3;
    if ((uVar11 & 1) != 0) {
      fVar5 = fVar5 * -1.0;
    }
    if ((uVar11 & 2) == 0) {
      fVar4 = fVar4 * -1.0;
    }
    if (g[0x7559] == 4) {
      fVar3 = fVar3 + fVar3;
      fVar5 = fVar5 + fVar5;
    }
    iVar1 = (int)GHIDRA_FIST32(fVar3);
    if (0 < *param_3) {
      fVar3 = (float)(*(int *)(param_1 + 0xb0) * 2) +
              (((((float)g[0x4140] -
                 (*(float *)(param_1 + 0x1a0) + (float10)iVar7) * *(float *)(param_1 + 0x80) *
                 *(float *)(param_1 + 0x1348)) - GHIDRA_I2F(g[0x7310])) + *(float *)(param_1 + 0x1a4)) -
              (float)g[0x7316]);
      if (g[0x7559] == 4) {
        fVar3 = fVar3 + fVar3;
        fVar4 = fVar4 + fVar4;
      }
      iVar12 = *param_3;
      iVar13 = 0x100 - iVar12;
      if (*(int *)(param_1 + 5000) == 3) {
        iVar12 = iVar12 * *(int *)(param_1 + 0x138c) >> 8;
        iVar13 = iVar13 + ((0x100 - iVar13) * *(int *)(param_1 + 0x1390) >> 8);
      }
      W_RotateSpriteTransAdd_B
                (piVar2,iVar6,(float10)iVar1,(float10)(int)GHIDRA_FIST32(fVar3),(float)local_40,fVar5,fVar4,
                 iVar12,iVar13);
    }
    fVar3 = *(float *)(param_1 + 0x80) * *(float *)(param_1 + 0x1348) * *(float *)(param_1 + 0x1350)
    ;
    fVar4 = ((((fVar3 + 1.0) * (float10)*(int *)(param_1 + 0xb0) + *(float *)(param_1 + 0x1a4) +
              (float)g[0x4140]) -
             (*(float *)(param_1 + 0x1a0) + (float10)iVar7) * fVar3 * GHIDRA_I2F(param_2[2])) -
            (float)g[0x7316]) - (float)g[0x7312];
    if ((uVar11 & 2) == 0) {
      fVar3 = fVar3 * -1.0;
    }
    if (g[0x7559] == 4) {
      fVar4 = fVar4 + fVar4;
      fVar3 = fVar3 + fVar3;
    }
    iVar12 = 0x100;
    if (*(int *)(param_1 + 5000) == 3) {
      iVar12 = 0x100 - *(int *)(param_1 + 0x1390);
    }
    iVar7 = param_2[3];
    iVar13 = param_2[4];
    if (iVar7 < iVar13) {
      fVar15 = *(float *)(param_1 + 0x1a0);
      if ((float10)iVar7 < fVar15) {
        if (fVar15 < (float10)iVar13) {
          iVar12 = (int)GHIDRA_FIST32(((float10)iVar12 * (fVar15 - (float10)iVar7)) / (float)(iVar13 - iVar7));
        }
      }
      else {
        iVar12 = 0;
      }
    }
    if (iVar12 < 0x100) {
      uVar14 = ((int)((uVar14 & 0x1f) * iVar12) >> 8 & 0x1fU) +
               ((int)((uVar14 & 0xf800) * iVar12) >> 8 & 0xf800U) +
               ((int)((uVar14 & 0x7e0) * iVar12) >> 8 & 0x7e0U);
      local_44 = iVar12 * local_44 >> 8;
    }
    if ((uVar14 == (0x1f << (bVar8 & 0x1f) | 0x3f << (bVar9 & 0x1f) | 0x1f << (bVar10 & 0x1f))) ||
       (local_44 == 0x100)) {
      local_44 = 0;
      fVar15 = GHIDRA_I2F(param_2[2]);
    }
    else {
      if (uVar14 != 0) {
        W_RotateShadowTransSub_P
                  (piVar2,iVar6,(float10)iVar1,(float10)(int)GHIDRA_FIST32(fVar4),(float)local_40,fVar5,fVar3,
                   1.0,GHIDRA_I2F(param_2[2]),uVar14);
      }
      if (local_44 < 1) {
        return;
      }
      local_44 = 0x100 - local_44;
      fVar15 = GHIDRA_I2F(param_2[2]);
    }
    W_RotateSpriteTransAdd_B_P
              (piVar2,iVar6,(float10)iVar1,(float10)(int)GHIDRA_FIST32(fVar4),(float)local_40,fVar5,fVar3,1.0,
               fVar15,0,local_44);
  }
  return;
}

/* PlayerDrawClsn @ 0x080b79b0, 2725 bytes
 * FIXUP: rewrote 1 Ghidra partial-variable accesses (x._O_S_)
 * FIXUP: 10 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 5 stack locals placed at their original offsets in a 0x190-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 2 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void PlayerDrawClsn(int param_1,float param_2)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  uint uVar4;
  float10 fVar5;
  float10 fVar6;
  bool bVar7;
  int iVar8;
  uint uVar9;
  int *piVar10;
  char *pcVar11;
  uint uVar12;
  char *pcVar13;
  uint uVar14;
  char *pcVar15;
  char *__dest;
  int iVar16;
  int iVar17;
  unsigned char ghidra_frame[0x190] __attribute__((aligned(16)));
#define local_188 (*(int *)(ghidra_frame + 0x8))
#define local_174 (*(int *)(ghidra_frame + 0x1c))
#define local_15c (*(char (*)[64])(ghidra_frame + 0x34))
#define local_11c (*(char (*)[4])(ghidra_frame + 0x74))
#define local_118 (*(undefined4 *)(ghidra_frame + 0x78))
  
  iVar16 = *(int *)(*(int *)(param_1 + 0x13bc) + 0x10);
  uVar9 = (uint)(*(int *)(param_1 + 400) != 1);
  bVar7 = false;
  iVar1 = (int)GHIDRA_FIST32((*(float *)(param_1 + 0x1354) - (float)g[0x7315]) * param_2);
  pcVar2 = (char *)(int)GHIDRA_FIST32((*(float *)(param_1 + 0x1358) - (float)g[0x7316]) * param_2);
  uVar14 = *(uint *)(param_1 + 0x1000) & *(uint *)(param_1 + 0xffc);
  if (iVar16 == 0) {
    return;
  }
  iVar17 = *(int *)(iVar16 + 0x28);
  iVar16 = *(int *)(iVar16 + 0x2c);
  sprintf(local_11c,"%c%c%c|%c%c%c|%c%c%c|%c%c%c",(((uVar14 & 1) == 0) - 1 & 0xffffffcd) + 0x53,
          (((uVar14 & 2) == 0) - 1 & 0xffffffdd) + 0x43,
          (((uVar14 & 4) == 0) - 1 & 0xffffffdf) + 0x41,
          (((uVar14 & 8) == 0) - 1 & 0xffffffd2) + 0x4e,
          (((uVar14 & 0x10) == 0) - 1 & 0xffffffcd) + 0x53,
          (((uVar14 & 0x20) == 0) - 1 & 0xffffffd8) + 0x48,
          (((uVar14 & 0x40) == 0) - 1 & 0xffffffd2) + 0x4e,
          ((-1 < (char)uVar14) - 1 & 0xffffffcd) + 0x53,
          (((uVar14 & 0x100) == 0) - 1 & 0xffffffd8) + 0x48,
          (((uVar14 & 0x200) == 0) - 1 & 0xffffffd2) + 0x4e,
          (((uVar14 & 0x400) == 0) - 1 & 0xffffffcd) + 0x53,
          (((uVar14 & 0x800) == 0) - 1 & 0xffffffd8) + 0x48,iVar17,iVar17);
  if ((((uVar14 & 7) == 0) || (0 < *(int *)(param_1 + 0xff8))) || ((uVar14 & 0xff8) == 0)) {
    builtin_strncpy(local_11c,"MUTE",4);
    local_118 = CONCAT13((*(uchar *)((char *)&local_118 + 3)),0x494b);
    bVar7 = true;
  }
  if (uVar14 != 0xfff) {
    bVar7 = true;
  }
  if (bVar7) {
    uVar14 = makecol(0xff,0xff,0xd4);
    V_FontDraw(local_11c,(int *)g[0x413a],iVar1 + -0x1c,(int)(pcVar2 + -2),uVar14);
    uVar14 = 0x1f << ((byte)_rgb_g_shift_16 & 0x1f);
    iVar8 = 0xf;
  }
  else {
    if (*(int *)(param_1 + 0xe10) == 0) {
      uVar14 = 0x1f << ((byte)_rgb_b_shift_16 & 0x1f);
      goto LAB_080b7c5d;
    }
    uVar14 = 8 << ((byte)_rgb_r_shift_16 & 0x1f);
    iVar8 = 0x18;
  }
  uVar14 = uVar14 | iVar8 << ((byte)_rgb_b_shift_16 & 0x1f);
LAB_080b7c5d:
  fVar5 = (float10)(int)pcVar2;
  fVar6 = (float10)iVar1;
  GameClsnDraw(iVar16,fVar6,fVar5,*(float *)(param_1 + 0x1348) * param_2,
               *(float *)(param_1 + 0x1348) * param_2,uVar14,uVar9,(uint)(g[0x81d0] == 2));
  GameClsnDraw(iVar17,fVar6,fVar5,*(float *)(param_1 + 0x1348) * param_2,
               *(float *)(param_1 + 0x1348) * param_2,0x1f << ((byte)_rgb_r_shift_16 & 0x1f),uVar9,
               (uint)(g[0x81d0] == 2));
  local_188 = 0;
  iVar16 = param_1;
  do {
    if (*(float *)(iVar16 + 0x31d0) != -32760.0) {
      uVar9 = (uint)GHIDRA_FIST32(((float10)*(int *)(param_1 + 400) * *(float *)(iVar16 + 0x31d0) + fVar6 +
                          (float10)*(int *)(param_1 + 0x2ec4)) - *(float *)(param_1 + 0x19c));
      uVar14 = (uint)GHIDRA_FIST32(((float10)*(int *)(param_1 + 0x2ec8) + fVar5 + *(float *)(iVar16 + 0x31e0))
                           - *(float *)(param_1 + 0x1a0));
      uVar3 = (uint)GHIDRA_FIST32(((float10)*(int *)(param_1 + 400) * *(float *)(iVar16 + 0x31f0) + fVar6 +
                          (float10)*(int *)(param_1 + 0x2ec4)) - *(float *)(param_1 + 0x19c));
      uVar4 = (uint)GHIDRA_FIST32((fVar5 + *(float *)(iVar16 + 0x3200) + (float10)*(int *)(param_1 + 0x2ec8))
                          - *(float *)(param_1 + 0x1a0));
      W_BoxTransSub16(uVar9,uVar14,uVar3,uVar4,
                      4 << ((byte)_rgb_r_shift_16 & 0x1f) | 8 << ((byte)_rgb_g_shift_16 & 0x1f) |
                      4 << ((byte)_rgb_b_shift_16 & 0x1f));
      if (g[0x81d0] == 2) {
        if (local_188 == 0) {
          uVar12 = 8 << ((byte)_rgb_r_shift_16 & 0x1f) | 8 << ((byte)_rgb_b_shift_16 & 0x1f);
        }
        else {
          uVar12 = 0x10 << ((byte)_rgb_g_shift_16 & 0x1f);
        }
        W_BoxFillTransAdd16(uVar9,uVar14,uVar3,uVar4,uVar12);
      }
      else {
        if (local_188 == 0) {
          uVar12 = 8 << ((byte)_rgb_r_shift_16 & 0x1f) | 8 << ((byte)_rgb_b_shift_16 & 0x1f);
        }
        else {
          uVar12 = 0x10 << ((byte)_rgb_g_shift_16 & 0x1f);
        }
        W_BoxTransAdd16(uVar9,uVar14,uVar3,uVar4,uVar12);
      }
    }
    iVar16 = iVar16 + 0x40;
    local_188 = local_188 + 1;
  } while (local_188 < 2);
  W_PutPixelXor16(iVar1,(int)pcVar2);
  W_PutPixelXor16(iVar1 + -1,(int)pcVar2);
  W_PutPixelXor16(iVar1 + 1,(int)pcVar2);
  W_PutPixelXor16(iVar1,(int)(pcVar2 + -1));
  W_PutPixelXor16(iVar1,(int)(pcVar2 + 1));
  if (*(int *)(param_1 + 400) == 1) {
    if (*(int *)(param_1 + 0xe00) == 3) {
      iVar16 = *(int *)(param_1 + 0x8c);
      iVar17 = *(int *)(param_1 + 0x90);
    }
    else {
      iVar16 = *(int *)(param_1 + 0x84);
      iVar17 = *(int *)(param_1 + 0x88);
    }
    pcVar15 = (char *)(iVar16 + *(int *)(param_1 + 0x1f8));
    local_174 = iVar17 + *(int *)(param_1 + 500);
    iVar16 = iVar16 + *(int *)(param_1 + 0x200);
    iVar17 = iVar17 + *(int *)(param_1 + 0x1fc);
  }
  else {
    if (*(int *)(param_1 + 0xe00) == 3) {
      iVar17 = *(int *)(param_1 + 0x8c);
      iVar16 = *(int *)(param_1 + 0x90);
    }
    else {
      iVar17 = *(int *)(param_1 + 0x84);
      iVar16 = *(int *)(param_1 + 0x88);
    }
    local_174 = iVar17 + *(int *)(param_1 + 0x1f8);
    pcVar15 = (char *)(iVar16 + *(int *)(param_1 + 500));
    iVar16 = iVar16 + *(int *)(param_1 + 0x1fc);
    iVar17 = iVar17 + *(int *)(param_1 + 0x200);
  }
  __dest = (char *)(int)GHIDRA_FIST32((float10)iVar16 * param_2);
  iVar16 = (int)GHIDRA_FIST32((float10)iVar17 * param_2);
  uVar14 = iVar1 + iVar16;
  uVar9 = iVar1 - (int)__dest;
  W_HLineTransAdd16(uVar9,uVar14,(uint)pcVar2,
                    8 << ((byte)_rgb_r_shift_16 & 0x1f) | 0x1f << ((byte)_rgb_g_shift_16 & 0x1f));
  pcVar13 = pcVar2 + 1;
  pcVar11 = pcVar2 + -1;
  W_VLineTransAdd16(uVar9,(uint)pcVar11,(uint)pcVar13,
                    8 << ((byte)_rgb_r_shift_16 & 0x1f) | 0x1f << ((byte)_rgb_g_shift_16 & 0x1f));
  W_VLineTransAdd16(uVar14,(uint)pcVar11,(uint)pcVar13,
                    8 << ((byte)_rgb_r_shift_16 & 0x1f) | 0x1f << ((byte)_rgb_g_shift_16 & 0x1f));
  if (pcVar15 != __dest) {
    W_VLineTransAdd16(iVar1 - (int)pcVar15,(uint)pcVar11,(uint)pcVar13,
                      0xf << ((byte)_rgb_r_shift_16 & 0x1f) | 0x10 << ((byte)_rgb_g_shift_16 & 0x1f)
                     );
  }
  if (local_174 != iVar16) {
    W_VLineTransAdd16(iVar1 + local_174,(uint)pcVar11,(uint)pcVar13,
                      0xf << ((byte)_rgb_r_shift_16 & 0x1f) | 0x10 << ((byte)_rgb_g_shift_16 & 0x1f)
                     );
  }
  if ((int)__dest < (int)pcVar15) {
    W_HLineTransAdd16(uVar9,iVar1 - (int)pcVar15,(uint)pcVar2,
                      0xf << ((byte)_rgb_r_shift_16 & 0x1f) | 0x10 << ((byte)_rgb_g_shift_16 & 0x1f)
                     );
    __dest = pcVar2;
  }
  if (iVar16 < local_174) {
    W_HLineTransAdd16(uVar14,iVar1 + local_174,(uint)pcVar2,
                      0xf << ((byte)_rgb_r_shift_16 & 0x1f) | 0x10 << ((byte)_rgb_g_shift_16 & 0x1f)
                     );
  }
  iVar16 = *(int *)(param_1 + 4);
  sprintf(local_11c,"%s, %i",param_1 + 0x20,iVar16);
  if (*(int *)(param_1 + 0x1158) != 0) {
    strcat(local_11c," H");
  }
  V_FontDraw(local_11c,(int *)g[0x413a],iVar1 + -0x14,(int)(pcVar2 + 6),
             0x1f << ((byte)_rgb_r_shift_16 & 0x1f) | 0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
             0x1f << ((byte)_rgb_b_shift_16 & 0x1f));
  if (0 < *(int *)(*(int *)(param_1 + 0x220) + 8)) {
    builtin_strncpy(local_11c,"Targ",4);
    local_118 = 0x207465;
    piVar10 = (int *)ArrayScanFirst(*(int *)(param_1 + 0x220));
    if (piVar10 != (int *)0x0) {
      do {
        iVar17 = *piVar10;
        if (iVar17 == 0) {
LAB_080b8385:
          bVar7 = false;
        }
        else {
          iVar16 = *(int *)(iVar17 + 0x158);
          bVar7 = true;
          if (iVar16 == 0) goto LAB_080b8385;
        }
        if (bVar7) {
          sprintf(local_15c,"%i",*(undefined4 *)(iVar17 + 4),__dest);
          strcat(local_11c,local_15c);
        }
        sprintf(local_15c," %i",piVar10[1],iVar16);
        __dest = local_11c;
        strcat(__dest,local_15c);
        piVar10 = (int *)ArrayScanNext(*(int *)(param_1 + 0x220));
        if (piVar10 == (int *)0x0) break;
        strcat(__dest,", ");
      } while( true );
    }
    uVar9 = makecol(0xff,0xc0,0xff);
    V_FontDraw(local_11c,(int *)g[0x413a],iVar1 + -0x14,(int)(pcVar2 + 0xc),uVar9);
  }
  return;
}
#undef local_188
#undef local_174
#undef local_15c
#undef local_11c
#undef local_118

