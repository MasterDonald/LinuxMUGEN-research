/*
 * p-info.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x080ab1c0-0x080abd3e, 22 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* PlayerNearestEnemy @ 0x080ab1c0, 488 bytes
 * REVIEW: pid-unaff_ */
int PlayerNearestEnemy(int param_1)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int unaff_ESI;
  int iVar5;
  int local_1c;
  int local_18;
  int local_14;
  
  local_14 = 0;
  local_18 = param_1;
  if (*(int *)(param_1 + 0x2624) != 0) {
    local_18 = *(int *)(param_1 + 0x2624);
  }
  piVar2 = (int *)ArrayScanFirst(*(int *)(param_1 + 0x220));
  while ((piVar2 != (int *)0x0 && (*(int *)(param_1 + 0xe04) == 1))) {
    iVar5 = *piVar2;
    if ((iVar5 == 0) || (bVar1 = true, *(int *)(iVar5 + 0x158) == 0)) {
      bVar1 = false;
    }
    if ((((bVar1) && (iVar5 != param_1)) && (iVar3 = PlayerLyingDead(iVar5), iVar3 == 0)) &&
       ((iVar3 = PlayerAreEnemies(local_18,iVar5), iVar3 != 0 &&
        ((*(int *)(iVar5 + 0x1c) == 0 || (*(int *)(iVar5 + 0x2628) == 1)))))) {
      if (local_14 == 0) {
        unaff_ESI = PlayerBodyDistX(param_1,iVar5);
        local_14 = iVar5;
        if (unaff_ESI < 0) {
          unaff_ESI = -unaff_ESI;
        }
      }
      else {
        iVar3 = PlayerBodyDistX(param_1,iVar5);
        if (iVar3 < 0) {
          iVar3 = -iVar3;
        }
        if (iVar3 < unaff_ESI) {
          local_14 = iVar5;
        }
      }
    }
    piVar2 = (int *)ArrayScanNext(*(int *)(param_1 + 0x220));
  }
  if ((local_14 == 0) && (iVar5 = g[0x7459], iVar5 <= g[0x745a])) {
    local_1c = iVar5 * 4 + 0x1cf60;
    piVar2 = g;
    do {
      iVar3 = *(int *)(local_1c + 4 + (int)piVar2);
      if ((iVar3 == 0) || (bVar1 = true, *(int *)(iVar3 + 0x158) == 0)) {
        bVar1 = false;
      }
      if (((((bVar1) && (iVar3 != param_1)) &&
           (iVar4 = PlayerLyingDead(iVar3), piVar2 = g, iVar4 == 0)) &&
          (iVar4 = PlayerAreEnemies(local_18,iVar3), piVar2 = g, iVar4 != 0)) &&
         ((*(int *)(iVar3 + 0x1c) == 0 || (*(int *)(iVar3 + 0x2628) == 1)))) {
        if (local_14 == 0) {
          unaff_ESI = PlayerBodyDistX(param_1,iVar3);
          piVar2 = g;
          local_14 = iVar3;
          if (unaff_ESI < 0) {
            unaff_ESI = -unaff_ESI;
          }
        }
        else {
          iVar4 = PlayerBodyDistX(param_1,iVar3);
          if (iVar4 < 0) {
            iVar4 = -iVar4;
          }
          piVar2 = g;
          if (iVar4 < unaff_ESI) {
            local_14 = iVar3;
          }
        }
      }
      iVar5 = iVar5 + 1;
      local_1c = local_1c + 4;
    } while (iVar5 <= piVar2[0x745a]);
  }
  return local_14;
}

/* PartnerAccess @ 0x080ab3b0, 123 bytes */
int PartnerAccess(int param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  iVar3 = g[0x7459];
  if (iVar3 <= g[0x745a]) {
    iVar4 = iVar3 * 4 + 0x1cf60;
    do {
      iVar1 = *(int *)(iVar4 + 4 + (int)g);
      if (((iVar1 == 0) || (*(int *)(iVar1 + 0x158) == 0)) ||
         (bVar2 = true, *(int *)(iVar1 + 0x1c) != 0)) {
        bVar2 = false;
      }
      if (((bVar2) && (*(int *)(iVar1 + 0xc) == *(int *)(param_1 + 0xc))) &&
         ((iVar1 != param_1 && (iVar1 != *(int *)(param_1 + 0x2624))))) {
        if (iVar5 == param_2) {
          return iVar1;
        }
        iVar5 = iVar5 + 1;
      }
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + 4;
    } while (iVar3 <= g[0x745a]);
  }
  return 0;
}

/* PartnerCount @ 0x080ab430, 115 bytes */
int PartnerCount(int param_1)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  iVar3 = g[0x7459];
  if (iVar3 <= g[0x745a]) {
    iVar4 = iVar3 * 4 + 0x1cf60;
    do {
      iVar1 = *(int *)(iVar4 + 4 + (int)g);
      if (((iVar1 == 0) || (*(int *)(iVar1 + 0x158) == 0)) ||
         (bVar2 = true, *(int *)(iVar1 + 0x1c) != 0)) {
        bVar2 = false;
      }
      if (((bVar2) && (*(int *)(iVar1 + 0xc) == *(int *)(param_1 + 0xc))) &&
         ((iVar1 != param_1 && (iVar1 != *(int *)(param_1 + 0x2624))))) {
        iVar5 = iVar5 + 1;
      }
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + 4;
    } while (iVar3 <= g[0x745a]);
  }
  return iVar5;
}

/* EnemyAccess @ 0x080ab4b0, 133 bytes */
int EnemyAccess(int param_1,int param_2)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar5 = 0;
  iVar6 = g[0x7459];
  if (iVar6 <= g[0x745a]) {
    iVar7 = iVar6 * 4 + 0x1cf60;
    piVar4 = g;
    do {
      iVar1 = *(int *)(iVar7 + 4 + (int)piVar4);
      if (((iVar1 == 0) || (*(int *)(iVar1 + 0x158) == 0)) ||
         (bVar2 = true, *(int *)(iVar1 + 0x1c) != 0)) {
        bVar2 = false;
      }
      if ((bVar2) && (iVar3 = PlayerAreEnemies(param_1,iVar1), piVar4 = g, iVar3 != 0)) {
        if (iVar5 == param_2) {
          return iVar1;
        }
        iVar5 = iVar5 + 1;
      }
      iVar6 = iVar6 + 1;
      iVar7 = iVar7 + 4;
    } while (iVar6 <= piVar4[0x745a]);
  }
  return 0;
}

/* EnemyCount @ 0x080ab540, 130 bytes */
int EnemyCount(int param_1)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = 0;
  iVar4 = g[0x7459];
  if (iVar4 <= g[0x745a]) {
    iVar5 = iVar4 * 4 + 0x1cf60;
    piVar3 = g;
    do {
      iVar2 = *(int *)(iVar5 + 4 + (int)piVar3);
      if (((iVar2 == 0) || (*(int *)(iVar2 + 0x158) == 0)) ||
         (bVar1 = true, *(int *)(iVar2 + 0x1c) != 0)) {
        bVar1 = false;
      }
      if ((bVar1) && (iVar2 = PlayerAreEnemies(param_1,iVar2), piVar3 = g, iVar2 != 0)) {
        iVar6 = iVar6 + 1;
      }
      iVar4 = iVar4 + 1;
      iVar5 = iVar5 + 4;
    } while (iVar4 <= piVar3[0x745a]);
  }
  return iVar6;
}

/* EnemyAccessNear @ 0x080ab5d0, 250 bytes */
undefined4 EnemyAccessNear(int param_1,int param_2)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = 0;
  iVar5 = 0;
  if (param_2 < 2) {
    if (*(int *)(param_1 + 0xc) == 1) {
      iVar6 = g[0x73db];
      iVar5 = g[0x73dd];
    }
    else if (*(int *)(param_1 + 0xc) == 2) {
      iVar6 = g[0x73da];
      iVar5 = g[0x73dc];
    }
    if ((iVar6 == 0) || (bVar1 = true, *(int *)(iVar6 + 0x158) == 0)) {
      bVar1 = false;
    }
    if ((iVar5 == 0) || (bVar2 = true, *(int *)(iVar5 + 0x158) == 0)) {
      bVar2 = false;
    }
    if ((bVar1) || (bVar2)) {
      if ((param_2 == 0) && ((bVar1 && (!bVar2)))) {
        return iVar6;
      }
      if (((param_2 == 0) && (!bVar1)) && (bVar2)) {
        return iVar5;
      }
      if ((bVar1) && (bVar2)) {
        iVar3 = PlayerDistX(param_1,iVar6);
        if (iVar3 < 0) {
          iVar3 = -iVar3;
        }
        iVar4 = PlayerDistX(param_1,iVar5);
        if (iVar4 < 0) {
          iVar4 = -iVar4;
        }
        if (iVar3 < iVar4) {
          if (param_2 == 0) {
            return iVar6;
          }
          return iVar5;
        }
        if (param_2 == 0) {
          return iVar5;
        }
        return iVar6;
      }
    }
  }
  return 0;
}

/* PlayerAccessID @ 0x080ab6d0, 112 bytes */
int PlayerAccessID(int param_1)

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
      if ((bVar2) && (*(int *)(*piVar5 + 4) == param_1)) {
        return *piVar5;
      }
      iVar3 = iVar3 + 1;
      piVar5 = piVar5 + 1;
      iVar4 = iVar4 + 4;
    } while (iVar3 <= g[0x745a]);
  }
  return 0;
}

/* PlayerGetDamagedLife @ 0x080ab740, 19 bytes */
int PlayerGetDamagedLife(int param_1)

{
  return *(int *)(param_1 + 0x160) - *(int *)(param_1 + 0x1028);
}

/* PlayerInCorner @ 0x080ab760, 126 bytes */
undefined4 PlayerInCorner(int param_1)

{
  if ((8 < ((int)GHIDRA_FIST32(*(float *)(param_1 + 0x19c)) - *(int *)(param_1 + 0x1d4)) + 4U) &&
     (8 < ((int)GHIDRA_FIST32(*(float *)(param_1 + 0x19c)) - *(int *)(param_1 + 0x1d8)) + 4U)) {
    return 0;
  }
  return 1;
}

/* PlayerDistX @ 0x080ab7e0, 65 bytes */
int PlayerDistX(int param_1,int param_2)

{
  return (int)GHIDRA_FIST32(*(float *)(param_2 + 0x19c) - *(float *)(param_1 + 0x19c)) *
         *(int *)(param_1 + 400);
}

/* PlayerBodyDistX @ 0x080ab830, 252 bytes
 * FIXUP: 3 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 2 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
int PlayerBodyDistX(int param_1,int param_2)

{
  float10 fVar1;
  float10 fVar2;
  int iVar3;
  int iVar4;
  
  if (*(int *)(param_1 + 0xe00) == 3) {
    iVar3 = *(int *)(param_1 + 400) * *(int *)(param_1 + 0x90);
  }
  else {
    iVar3 = *(int *)(param_1 + 400) * *(int *)(param_1 + 0x88);
  }
  fVar1 = *(float *)(param_1 + 0x19c);
  iVar4 = PlayerDistX(param_2,param_1);
  if (iVar4 < 1) {
    if (*(int *)(param_2 + 0xe00) == 3) {
      iVar4 = *(int *)(param_2 + 400) * *(int *)(param_2 + 0x8c);
    }
    else {
      iVar4 = *(int *)(param_2 + 400) * *(int *)(param_2 + 0x84);
    }
    fVar2 = *(float *)(param_2 + 0x19c) - (float10)iVar4;
  }
  else {
    if (*(int *)(param_2 + 0xe00) == 3) {
      iVar4 = *(int *)(param_2 + 400) * *(int *)(param_2 + 0x90);
    }
    else {
      iVar4 = *(int *)(param_2 + 400) * *(int *)(param_2 + 0x88);
    }
    fVar2 = (float10)iVar4 + *(float *)(param_2 + 0x19c);
  }
  return (int)GHIDRA_FIST32(fVar2 - ((float10)iVar3 + fVar1)) * *(int *)(param_1 + 400);
}

/* PlayerInAnyGuardDist @ 0x080ab930, 177 bytes */
undefined4 PlayerInAnyGuardDist(int param_1)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar4 = g[0x7459];
  if (iVar4 <= g[0x745a]) {
    iVar5 = iVar4 * 4 + 0x1cf60;
    piVar3 = g;
    iVar6 = iVar5;
    do {
      iVar2 = *(int *)(iVar6 + 4 + (int)piVar3);
      if (param_1 != iVar2) {
        if ((iVar2 == 0) || (bVar1 = true, *(int *)(iVar2 + 0x158) == 0)) {
          bVar1 = false;
        }
        if (bVar1) {
          iVar2 = *(int *)(iVar5 + 4 + (int)piVar3);
          if ((((*(int *)(iVar2 + 0xc) != *(int *)(param_1 + 0xc)) && (*(int *)(iVar2 + 0xc) != 0))
              && ((*(int *)(iVar2 + 0xe04) == 1 || (0 < *(int *)(**(int **)(iVar2 + 0x21c) + 8)))))
             && (iVar2 = PlayerInGuardDist(param_1,iVar2), piVar3 = g, iVar2 != 0)) {
            return 1;
          }
        }
      }
      iVar4 = iVar4 + 1;
      iVar5 = iVar5 + 4;
      iVar6 = iVar6 + 4;
    } while (iVar4 <= piVar3[0x745a]);
  }
  return 0;
}

/* PlayerInGuardDist @ 0x080ab9f0, 177 bytes */
undefined4 PlayerInGuardDist(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar1 = **(int **)(param_2 + 0x21c);
  iVar2 = PlayerDistX(param_2,param_1);
  if (((iVar2 < *(int *)(param_2 + 0x12cc)) && (-1 < iVar2)) && (*(int *)(iVar1 + 8) == 0)) {
LAB_080aba23:
    uVar3 = 1;
  }
  else {
    iVar2 = ArrayScanFirst(iVar1);
    while (iVar2 != 0) {
      if (*(int *)(iVar2 + 0x98) != 0) {
        iVar4 = (int)GHIDRA_FIST32(*(float *)(param_1 + 0x19c) - *(float *)(iVar2 + 0x44)) *
                *(int *)(iVar2 + 0x34);
        if ((iVar4 < *(int *)(iVar2 + 0x20c)) && (-1 < iVar4)) goto LAB_080aba23;
      }
      iVar2 = ArrayScanNext(iVar1);
    }
    uVar3 = 0;
  }
  return uVar3;
}

/* HitdefAffectTeam @ 0x080abab0, 47 bytes */
bool HitdefAffectTeam(int param_1,int param_2,uint param_3)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_1 + 8);
  if (param_2 == 2) {
    uVar1 = uVar1 & 0xfffffffc | (uVar1 & 1) * 2 | uVar1 >> 1 & 1;
  }
  return (param_3 & uVar1) != 0;
}

/* PlayerAreEnemies @ 0x080abae0, 36 bytes */
undefined4 PlayerAreEnemies(int param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (((*(int *)(param_1 + 0xc) != *(int *)(param_2 + 0xc)) && (*(int *)(param_1 + 0xc) != 0)) &&
     (*(int *)(param_2 + 0xc) != 0)) {
    uVar1 = 1;
  }
  return uVar1;
}

/* PlayerGetWidth @ 0x080abb10, 219 bytes */
int PlayerGetWidth(int param_1,int param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = 0;
  if (param_2 == 2) {
    iVar2 = -*(int *)(param_1 + 400);
  }
  else if (param_2 < 3) {
    if (param_2 == 1) {
      iVar2 = *(int *)(param_1 + 400);
    }
  }
  else if (param_2 == 3) {
    iVar2 = -1;
  }
  else if (param_2 == 4) {
    iVar2 = 1;
  }
  if (param_3 < 3) {
    if (*(int *)(param_1 + 0xe00) == 3) {
      if (*(int *)(param_1 + 400) == iVar2) {
        iVar1 = *(int *)(param_1 + 0x90);
      }
      else {
        iVar1 = *(int *)(param_1 + 0x8c);
      }
    }
    else if (*(int *)(param_1 + 400) == iVar2) {
      iVar1 = *(int *)(param_1 + 0x88);
    }
    else {
      iVar1 = *(int *)(param_1 + 0x84);
    }
  }
  if ((param_3 == 1) || (param_3 == 3)) {
    if (*(int *)(param_1 + 400) != iVar2) {
      return iVar1 + *(int *)(param_1 + 0x200);
    }
    iVar2 = *(int *)(param_1 + 0x1fc);
  }
  else {
    if ((param_3 != 2) && (param_3 != 4)) {
      return iVar1;
    }
    if (*(int *)(param_1 + 400) == iVar2) {
      return iVar1 + *(int *)(param_1 + 500);
    }
    iVar2 = *(int *)(param_1 + 0x1f8);
  }
  return iVar1 + iVar2;
}

/* PlayerAnimExist @ 0x080abbf0, 38 bytes */
bool PlayerAnimExist(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = AnimGrpNoToIdx(*(undefined4 **)(param_1 + 0x13bc),0,param_2);
  return iVar1 != -1;
}

/* PlayerSelfAnimExist @ 0x080abc20, 67 bytes */
bool PlayerSelfAnimExist(int *param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = *(undefined4 *)param_1[0x4ef];
  *(undefined4 *)param_1[0x4ef] = *(undefined4 *)(*param_1 + 0x11cc);
  iVar2 = AnimGrpNoToIdx((undefined4 *)param_1[0x4ef],0,param_2);
  *(undefined4 *)param_1[0x4ef] = uVar1;
  return iVar2 != -1;
}

/* PlayerLyingDead @ 0x080abc70, 26 bytes */
undefined4 PlayerLyingDead(int param_1)

{
  if (*(int *)(param_1 + 0xbf4) == 0x141e) {
    return *(undefined4 *)(param_1 + 0xdfc);
  }
  return 0;
}

/* PlayerFindTarget @ 0x080abc90, 47 bytes */
int * PlayerFindTarget(int param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = (int *)ArrayScanFirst(param_1);
  while( true ) {
    if (piVar1 == (int *)0x0) {
      return (int *)0x0;
    }
    if (*piVar1 == param_2) break;
    piVar1 = (int *)ArrayScanNext(param_1);
  }
  return piVar1;
}

/* TargetAccessID @ 0x080abcc0, 64 bytes */
undefined4 TargetAccessID(int param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = (int *)ArrayScanFirst(param_1);
  while( true ) {
    if (piVar1 == (int *)0x0) {
      return 0;
    }
    if (*(int *)(*piVar1 + 0x1064) == param_2) break;
    if (param_2 == -1) {
      return piVar1;
    }
    piVar1 = (int *)ArrayScanNext(param_1);
  }
  return piVar1;
}

/* TargetCount @ 0x080abd00, 62 bytes */
int TargetCount(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = (int *)ArrayScanFirst(param_1);
  while (piVar1 != (int *)0x0) {
    if ((*(int *)(*piVar1 + 0x1064) == param_2) || (param_2 == -1)) {
      iVar2 = iVar2 + 1;
    }
    piVar1 = (int *)ArrayScanNext(param_1);
  }
  return iVar2;
}

