/*
 * p-input.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x080abd40-0x080ac658, 1 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* PlayerKBUpdate @ 0x080abd40, 2328 bytes
 * FIXUP: 2 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void PlayerKBUpdate(int *param_1)

{
  float10 dVar1;
  bool bVar2;
  bool bVar3;
  undefined3 extraout_var;
  int iVar4;
  undefined3 extraout_var_00;
  int iVar5;
  int *piVar6;
  int iVar7;
  int *piVar8;
  uint local_28;
  int local_24;
  uint local_1c;
  int local_18;
  
  bVar2 = false;
  piVar6 = param_1 + 0x92;
  local_28 = KBIGetch((int)piVar6);
  if (param_1[0x98b] == 0) {
    bVar3 = GameModeInPassiveFightScreen();
    piVar8 = g;
    if ((GHIDRA_ZEXT8(bVar3) == 0) &&
       ((((g[0x7511] == 1 || ((g[0x7511] == 0 && (2 < g[0x7514])))) && (local_28 - 5 < 6)) &&
        ((g[0x750e] <= g[0x4fa4] + 2 && (g[0x7517] == 0)))))) {
      iVar4 = ((g[0x7559] == 4) - 1 & 0xfffffff6) + 0x14;
      g[0x7517] = 1;
      piVar8[0x730c] = 1;
      piVar8[0x730d] = 0;
      piVar8[0x730e] = iVar4;
      if (1 < piVar8[0x7506]) {
        piVar8[0x730e] = iVar4 * 2;
      }
    }
    if (((piVar8[0x33b7] - 5U < 2) && (piVar8[0x7541] == 1)) && (local_28 - 5 < 6)) {
      piVar8[0x7541] = 2;
      piVar8[0x7542] = 0;
    }
    bVar3 = GameModeInPassiveFightScreen();
    if (((GHIDRA_ZEXT8(bVar3) == 0) && (g[0x7511] == 4)) &&
       ((g[0x508e] < g[0x7514] && ((g[0x7514] < g[0x7510] + -0x11 && (local_28 - 5 < 6)))))) {
      g[0x7511] = 4;
      MasterPalMul(0x100,0x100,0x100);
      piVar8 = g;
      g[0x7514] = g[0x7510] + -0x11;
      piVar8[0x7518] = 1;
    }
  }
  if (param_1[0x57] != 0) {
    return;
  }
  if (param_1[0x989] == 0) {
    iVar4 = param_1[0x8f];
  }
  else {
    if (param_1[0x8f] != 0) {
      return;
    }
    iVar4 = 0;
  }
  if (iVar4 == 0) {
    if (param_1[0x90] != 0) {
      KBIRefreshKeyflags((int)piVar6,param_1[600]);
      param_1[0x90] = 0;
    }
  }
  else {
    local_28 = 0;
    KBIClearKeyflags((int)piVar6);
    param_1[0x90] = 1;
  }
  if (g[0x74df] == 0) {
    return;
  }
  local_1c = 0xffffffff;
  if (0 < param_1[0x386]) {
    param_1[0x254] = 1;
  }
  if (param_1[0x8f] == 0) {
    KBUpdateHold((int)(param_1 + 0xc1),(int)piVar6);
  }
  else {
    param_1[0x255] = 0;
  }
  local_24 = 0;
  iVar4 = g[0x74f3];
  if (((iVar4 != -1) && (param_1[iVar4 + 0x77] == 0)) &&
     (g[iVar4 * 9 + 0x74fa] < g[iVar4 * 9 + 0x74fc])) {
    local_24 = 2;
  }
  if (param_1[0x254] == 0) {
    KBCountdownCommandValidTimes((int)(param_1 + 0x25a),'\x01',local_24);
  }
  iVar4 = param_1[0x989];
  if ((iVar4 == 0) || (*(int *)(iVar4 + 0x262c) == 0)) {
    KBFillBuffer((int)piVar6,(int)(param_1 + 0xc1),local_28,g[0x7304]);
  }
  else {
    iVar7 = param_1[0x254];
    piVar6 = (int *)(iVar4 + 0x304);
    piVar8 = param_1 + 0xc1;
    for (iVar5 = 0x197; iVar5 != 0; iVar5 = iVar5 + -1) {
      *piVar8 = *piVar6;
      piVar6 = piVar6 + 1;
      piVar8 = piVar8 + 1;
    }
    param_1[0x254] = iVar7;
  }
  iVar4 = param_1[0x243];
  KBGetCommandSpecial((int)(param_1 + 0x25a),(int *)param_1[0x259],(int)(param_1 + 0xc1),g[0x7304],1
                     );
  piVar6 = g;
  param_1[0x243] = iVar4;
  KBGetCommandSpecial((int)(param_1 + 0x25a),(int *)(*param_1 + 0x11b4),(int)(param_1 + 0xc1),
                      piVar6[0x7304],2);
  PlayerAIProcessCommands((int)param_1);
  if (((param_1[0x386] == 0) && (g[param_1[2] + 0x749e] != 0)) && (param_1[0x254] == 1)) {
    param_1[0x254] = 0;
  }
  piVar6 = g;
  iVar4 = param_1[0x380];
  if (iVar4 == 1) {
    iVar7 = param_1[0xb2];
    if (iVar7 == 0) {
      iVar5 = param_1[0xb4];
    }
    else {
      iVar5 = param_1[0xb4];
      if (iVar5 == 0) {
        local_1c = 1;
      }
    }
    if ((iVar5 != 0) && (iVar7 == 0)) {
      local_1c = 1;
    }
    if (param_1[0xb3] != 0) {
      local_1c = 0xb;
    }
    if ((param_1[0xb1] != 0) && (local_1c = 7, iVar7 != 0)) {
      local_1c = 7;
    }
    if ((param_1[0xb1] != 0) && (iVar5 != 0)) {
      local_1c = 7;
    }
  }
  if ((iVar4 == 2) && (param_1[0xb3] != 0)) {
    bVar2 = true;
  }
  if ((iVar4 == 3) && (local_28 == 1)) {
    local_1c = 10;
  }
  param_1[900] = 0;
  if ((piVar6[0x731d] == 0) && (param_1[0xb4] != 0)) {
    if (param_1[0x381] == 0) {
      if ((param_1[899] == 0) && (iVar4 = param_1[0x2fd], iVar4 != 0x34)) goto LAB_080ac226;
    }
    else {
      iVar4 = param_1[0x2fd];
LAB_080ac226:
      if ((iVar4 != 0x97) && ((iVar4 != 0x99 && (iVar4 != 0x9b)))) goto LAB_080ac33a;
    }
    iVar4 = param_1[0x380];
    if (((iVar4 != 1) || ((char)param_1[0x81] == '\0')) &&
       ((((iVar4 != 2 || (*(char *)((int)param_1 + 0x205) == '\0')) &&
         ((iVar4 != 3 || (*(char *)((int)param_1 + 0x206) == '\0')))) &&
        ((param_1[0xb1] == 0 && (local_24 = piVar6[0x7459], local_24 <= piVar6[0x745a])))))) {
      iVar4 = local_24 * 4 + 0x1cf60;
      iVar7 = iVar4;
      do {
        piVar8 = *(int **)(iVar7 + 4 + (int)piVar6);
        if (param_1 != piVar8) {
          if ((piVar8 == (int *)0x0) || (bVar3 = true, piVar8[0x56] == 0)) {
            bVar3 = false;
          }
          if (bVar3) {
            iVar5 = *(int *)(iVar4 + 4 + (int)piVar6);
            if (((*(int *)(iVar5 + 0xc) != param_1[3]) && (*(int *)(iVar5 + 0xc) != 0)) &&
               ((*(int *)(iVar5 + 0xe04) == 1 || (0 < *(int *)(**(int **)(iVar5 + 0x21c) + 8))))) {
              param_1[900] = 1;
              iVar5 = PlayerInGuardDist((int)param_1,iVar5);
              piVar6 = g;
              if (iVar5 != 0) {
                local_1c = 0x28;
              }
            }
          }
        }
        local_24 = local_24 + 1;
        iVar4 = iVar4 + 4;
        iVar7 = iVar7 + 4;
      } while (local_24 <= piVar6[0x745a]);
    }
  }
LAB_080ac33a:
  if (param_1[0xb2] != 0) {
    local_1c = local_1c | (param_1[0xb4] == 0) - 1;
  }
  if (param_1[0x91] != 0) {
    local_1c = 0xffffffff;
    KBClearCommandValidTimes(param_1 + 0x25a);
    bVar2 = false;
  }
  if (local_1c == 10) {
    if (((param_1[899] != 0) && (0 < param_1[0x74])) &&
       ((float10)param_1[0x45] < -GHIDRA_I2F(param_1[0x68]))) {
      PlayerChangeState((int)param_1,0x2d);
      param_1[0x74] = param_1[0x74] + -1;
    }
    goto LAB_080ac5ce;
  }
  if ((int)local_1c < 0xb) {
    if (local_1c == 1) {
      if (((param_1[899] == 0) || (*(char *)((int)param_1 + 0x20a) != '\0')) ||
         (param_1[0x2fd] == 0x14)) goto LAB_080ac5ce;
      iVar4 = 0x14;
    }
    else {
      if (local_1c != 7) goto LAB_080ac590;
      if ((param_1[899] == 0) || (g[0x7511] == 3)) goto LAB_080ac5ce;
      iVar4 = 0x28;
    }
  }
  else {
    if (local_1c == 0x28) {
      if ((param_1[0x381] == 0) && (param_1[899] != 0)) {
        iVar4 = param_1[0x2fd];
        if ((2 < iVar4 - 0x82U) && ((iVar4 != 0x78 && (iVar4 != 0x8c)))) {
          if ((param_1[0x380] != 3) && (param_1[0x6f] = 0, param_1[0x2fd] != 100)) {
            param_1[0x6d] = 0;
          }
          PlayerChangeState((int)param_1,0x78);
        }
        param_1[900] = 1;
      }
      goto LAB_080ac5ce;
    }
    if ((int)local_1c < 0x29) {
      if (local_1c == 0xb) {
        if (param_1[899] == 0) goto LAB_080ac5ce;
        if (param_1[0x2fd] != 100) {
          param_1[0x6d] = 0;
        }
        param_1[0x6f] = 0;
        if (param_1[0x2fd] - 10U < 2) goto LAB_080ac5ce;
        iVar4 = 10;
        goto LAB_080ac5c5;
      }
    }
    else if (local_1c == 900) {
      PlayerTurnAround((int)param_1);
      iVar4 = AnimCurIDno((undefined4 *)param_1[0x4ef]);
      if (iVar4 != 5) {
        PlayerSelfAnim(param_1,5);
      }
      goto LAB_080ac5ce;
    }
LAB_080ac590:
    if (param_1[0x2fd] == 0x14) {
      PlayerChangeState((int)param_1,0);
    }
    if (((param_1[0x380] != 2) || (param_1[899] == 0)) || (bVar2)) goto LAB_080ac5ce;
    iVar4 = 0xc;
  }
LAB_080ac5c5:
  PlayerChangeState((int)param_1,iVar4);
LAB_080ac5ce:
  if ((local_28 != 0) && (param_1[0x381] == 2)) {
    if (param_1[0x380] == 4) {
      dVar1 = (double)param_1[0x411] * 0.75;
    }
    else {
      if (param_1[0x40c] < 1) {
        return;
      }
      dVar1 = (double)param_1[0x411] * ((double)0.9);
    }
    local_18 = (int)GHIDRA_FIST32(dVar1);
    param_1[0x411] = local_18;
  }
  return;
}

