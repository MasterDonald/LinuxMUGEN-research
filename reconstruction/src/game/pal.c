/*
 * pal.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x080b8460-0x080b9161, 20 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* PalGrpAdd @ 0x080b8460, 428 bytes
 * REVIEW: pid-in_stack_
 * FIXUP: rewrote 1 PalGrpFlag by-value loads
 * FIXUP: PalGrpMakeFlag result written into the argument area: given explicit temporaries pgf_ffffffc8 */
undefined4 PalGrpAdd(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  PalGrpFlag pgf_ffffffc8;
  int *piVar1;
  undefined4 *puVar2;
  PalGrpFlag a;
  PalGrpFlag a_00;
  PalGrpFlag b;
  int iVar3;
  void *pvVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  uint in_stack_ffffffc8;
  uint in_stack_ffffffcc;
  uint in_stack_ffffffd0;
  void *in_stack_ffffffd4;
  uint in_stack_ffffffd8;
  
  puVar2 = (undefined4 *)g[0x413e];
  iVar6 = puVar2[2];
  if (param_1 == 0) {
LAB_080b8531:
    uVar5 = 0;
  }
  else {
    iVar8 = 0;
    iVar3 = iVar6;
    if (iVar6 < 1) {
      pvVar4 = (void *)*puVar2;
    }
    else {
      pvVar4 = (void *)*puVar2;
      iVar7 = 0;
      do {
        piVar1 = (int *)(iVar7 + (int)pvVar4);
        if (param_1 == *piVar1) {
          in_stack_ffffffd8 = piVar1[5];
          in_stack_ffffffd4 = (void *)piVar1[4];
          in_stack_ffffffd0 = piVar1[3];
          in_stack_ffffffcc = piVar1[2];
          in_stack_ffffffc8 = (*(uint (*) [5])(piVar1 + 1))[0];
          a.w[1] = param_3;
          a.w[0] = param_2;
          a.w[2] = param_4;
          a.w[3] = param_5;
          a.w[4] = param_6;
          iVar3 = PalGrpFlagEqual(a,*(PalGrpFlag *)(piVar1 + 1));
          if (iVar3 != 0) goto LAB_080b85ff;
          iVar3 = puVar2[2];
          pvVar4 = (void *)*puVar2;
        }
        iVar8 = iVar8 + 1;
        iVar7 = iVar7 + 0x18;
      } while (iVar8 < iVar3);
    }
    iVar8 = puVar2[1];
    if (iVar8 <= iVar3) {
      if (pvVar4 == (void *)0x0) {
        pvVar4 = (void *)ecalloc(1,iVar8 * 0x18 + 0x180);
      }
      else {
        pvVar4 = realloc((void *)*puVar2,iVar8 * 0x18 + 0x180);
      }
      if (pvVar4 == (void *)0x0) goto LAB_080b8531;
      in_stack_ffffffd8 = 0;
      in_stack_ffffffd4 = (void *)((int)pvVar4 + puVar2[1] * 0x18);
      in_stack_ffffffd0 = 0x80b854f;
      memset(in_stack_ffffffd4,0,0x180);
      *puVar2 = pvVar4;
      puVar2[1] = puVar2[1] + 0x10;
    }
    piVar1 = (int *)((int)pvVar4 + iVar6 * 0x18);
    piVar9 = piVar1;
    for (iVar6 = 6; iVar6 != 0; iVar6 = iVar6 + -1) {
      *piVar9 = 0;
      piVar9 = piVar9 + 1;
    }
    *piVar1 = param_1;
    piVar1[1] = param_2;
    piVar1[2] = param_3;
    piVar1[3] = param_4;
    piVar1[4] = param_5;
    piVar1[5] = param_6;
    puVar2[2] = puVar2[2] + 1;
    PalGrpMakeFlag(&pgf_ffffffc8,0x100,0);
    a_00.w[1] = param_3;
    a_00.w[0] = param_2;
    a_00.w[2] = param_4;
    a_00.w[3] = param_5;
    a_00.w[4] = param_6;
    b.w[1] = pgf_ffffffc8.w[1];
    b.w[0] = pgf_ffffffc8.w[0];
    b.w[2] = pgf_ffffffc8.w[2];
    b.w[3] = (uint)pgf_ffffffc8.w[3];
    b.w[4] = pgf_ffffffc8.w[4];
    iVar6 = PalGrpFlagEqual(a_00,b);
    if (iVar6 != 0) {
      g[0x81ca] = g[0x81ca] + 1;
    }
LAB_080b85ff:
    uVar5 = 1;
  }
  return uVar5;
}

/* PalGrpRemove @ 0x080b8610, 177 bytes
 * FIXUP: rewrote 1 PalGrpFlag by-value loads */
void PalGrpRemove(PalGrpFlag f)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  piVar1 = (int *)g[0x413e];
  if (0 < piVar1[2]) {
    iVar3 = 0;
    do {
      iVar2 = PalGrpFlagEqual(f,*(PalGrpFlag *)(iVar3 + *piVar1 + 4));
      if (iVar2 == 0) {
        iVar3 = iVar3 + 0x18;
        iVar4 = iVar4 + 1;
      }
      else {
        iVar2 = piVar1[2];
        if (0 < (iVar2 - iVar4) + -1) {
          memmove((void *)(iVar3 + *piVar1),(void *)(iVar3 + *piVar1 + 0x18),
                  (iVar2 - iVar4) * 0x18 - 0x18);
          iVar2 = piVar1[2];
        }
        piVar1[2] = iVar2 + -1;
      }
    } while (iVar4 < piVar1[2]);
  }
  return;
}

/* PalGrpAddSpr @ 0x080b86d0, 88 bytes */
undefined4 PalGrpAddSpr(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  undefined4 in_ECX;
  
  if ((param_1 != 0) && (*(int *)(param_1 + 8) != 0)) {
    iVar1 = ArrayScanFirst(*(int *)(param_1 + 8));
    while (iVar1 != 0) {
      PalGrpAdd(iVar1,param_2,param_3,param_4,param_5,param_6);
      iVar1 = ArrayScanNext(*(int *)(param_1 + 8));
    }
  }
  return in_ECX;
}

/* PalGrpBuildFight @ 0x080b8730, 546 bytes
 * REVIEW: pid-in_stack_
 * FIXUP: rewrote 1 PalGrpFlag by-value loads
 * FIXUP: PalGrpMakeFlag result written into the argument area: given explicit temporaries pgf_ffffffc8 */
void PalGrpBuildFight(void)

{
  PalGrpFlag pgf_ffffffc8;
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  uint in_stack_ffffffc8;
  uint in_stack_ffffffcc;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  PalGrpClear();
  g[0x81ca] = 0;
  uVar8 = 0x18;
  uVar7 = 0x40;
  uVar6 = 0x80b8756;
  iVar2 = ecalloc(0x40,0x18);
  piVar4 = g;
  piVar1 = (int *)g[0x413e];
  *piVar1 = iVar2;
  if (iVar2 != 0) {
    piVar1[1] = 0x40;
    iVar2 = 1;
    if (0 < piVar4[0x7395]) {
      iVar5 = 0x1cf64;
      do {
        iVar3 = *(int *)(iVar5 + 4 + (int)piVar4);
        if (iVar3 != 0) {
          uVar7 = *(uint *)(iVar3 + 0x25d8);
          uVar6 = *(uint *)(iVar3 + 0x25d4);
          in_stack_ffffffcc = *(uint *)(iVar3 + 0x25d0);
          in_stack_ffffffc8 = *(uint *)(iVar3 + 0x25cc);
          iVar3 = PalGrpFlagIsNonZero(*(PalGrpFlag *)(iVar3 + 0x25c8));
          piVar4 = g;
          if (iVar3 != 0) {
            iVar3 = *(int *)((int)g + iVar5 + 4);
            uVar8 = *(uint *)(iVar3 + 0x25d8);
            uVar7 = *(uint *)(iVar3 + 0x25d4);
            uVar6 = *(uint *)(iVar3 + 0x25d0);
            in_stack_ffffffcc = *(uint *)(iVar3 + 0x25cc);
            in_stack_ffffffc8 = *(uint *)(iVar3 + 0x25c8);
            PalGrpAddSpr(*(int *)(*(int *)((int)g + iVar5 + 4) + 0x13ac),in_stack_ffffffc8,
                         in_stack_ffffffcc,uVar6,uVar7,uVar8);
            piVar4 = g;
          }
        }
        iVar2 = iVar2 + 1;
        iVar5 = iVar5 + 4;
      } while (iVar2 <= piVar4[0x7395]);
    }
    iVar2 = 0;
    PalGrpMakeFlag(&pgf_ffffffc8,0x100,0);
    PalGrpAddSpr(*(int *)(g[0x6ed4] + 0x28),pgf_ffffffc8.w[0],pgf_ffffffc8.w[1],pgf_ffffffc8.w[2],pgf_ffffffc8.w[3],pgf_ffffffc8.w[4]);
    PalGrpMakeFlag(&pgf_ffffffc8,0x200,0);
    PalGrpAddSpr(g[0x4149],pgf_ffffffc8.w[0],pgf_ffffffc8.w[1],pgf_ffffffc8.w[2],pgf_ffffffc8.w[3],pgf_ffffffc8.w[4]);
    PalGrpMakeFlag(&pgf_ffffffc8,0x400,0);
    PalGrpAddSpr(g[0x4147],pgf_ffffffc8.w[0],pgf_ffffffc8.w[1],pgf_ffffffc8.w[2],pgf_ffffffc8.w[3],pgf_ffffffc8.w[4]);
    do {
      iVar5 = 0;
      do {
        iVar3 = iVar5 + iVar2 * 4;
        iVar5 = iVar5 + 1;
        iVar3 = g[iVar3 + 0x52b5];
        PalGrpMakeFlag(&pgf_ffffffc8,0x200,0);
        PalGrpAddSpr(iVar3,pgf_ffffffc8.w[0],pgf_ffffffc8.w[1],pgf_ffffffc8.w[2],pgf_ffffffc8.w[3],pgf_ffffffc8.w[4]);
      } while (iVar5 < 4);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 2);
    iVar5 = 9;
    iVar2 = 0x10520;
    do {
      if (*(int *)((int)g + iVar2 + 0xc) != 0) {
        PalGrpMakeFlag(&pgf_ffffffc8,0x800,0);
        PalGrpAddSpr(*(int *)(*(int *)((int)g + iVar2 + 0xc) + 0x818),pgf_ffffffc8.w[0],pgf_ffffffc8.w[1],pgf_ffffffc8.w[2],pgf_ffffffc8.w[3],pgf_ffffffc8.w[4]);
      }
      iVar2 = iVar2 + 4;
      iVar5 = iVar5 + -1;
    } while (-1 < iVar5);
  }
  return;
}

/* PalGrpClear @ 0x080b8960, 113 bytes */
undefined4 * PalGrpClear(void)

{
  undefined4 *puVar1;
  int *piVar2;
  
  piVar2 = g;
  if (*(int *)g[0x413e] != 0) {
    PalGrpResetPalette();
    free(*(void **)g[0x413e]);
    piVar2 = g;
    puVar1 = (undefined4 *)g[0x413e];
    *puVar1 = 0;
    puVar1[2] = 0;
    puVar1[1] = 0;
  }
  puVar1 = (undefined4 *)piVar2[0x413e];
  *puVar1 = 0;
  puVar1[1] = 0;
  puVar1[2] = 0;
  return puVar1;
}

/* PalGrpResetPalette @ 0x080b89e0, 53 bytes */
void PalGrpResetPalette(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  piVar2 = (int *)g[0x413e];
  if (0 < piVar2[2]) {
    iVar4 = 0;
    do {
      iVar3 = iVar3 + 1;
      piVar1 = (int *)(*piVar2 + iVar4);
      iVar4 = iVar4 + 0x18;
      EBPalReset(*piVar1);
    } while (iVar3 < piVar2[2]);
  }
  return;
}

/* PalGrpSetAdd @ 0x080b8a20, 159 bytes
 * FIXUP: rewrote 1 PalGrpFlag by-value loads
 * FIXUP: renamed locals shadowing globals: g */
void PalGrpSetAdd(PalGrpFlag f,int r,int g_local,int b)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  piVar1 = (int *)g[0x413e];
  if ((((r != 0) || (g_local != 0)) || (b != 0)) && (iVar5 = 0, 0 < piVar1[2])) {
    iVar4 = 0;
    do {
      iVar2 = *piVar1;
      iVar3 = PalGrpAndFlagZero(*(PalGrpFlag *)((int *)(iVar4 + iVar2) + 1),f);
      if (iVar3 != 0) {
        EBPalAdd(*(int *)(iVar4 + iVar2),r,g_local,b);
      }
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 0x18;
    } while (iVar5 < piVar1[2]);
  }
  return;
}

/* PalGrpSetMul @ 0x080b8ac0, 172 bytes
 * FIXUP: rewrote 1 PalGrpFlag by-value loads
 * FIXUP: renamed locals shadowing globals: g */
void PalGrpSetMul(PalGrpFlag f,int r,int g_local,int b)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  piVar1 = (int *)g[0x413e];
  if ((((r != 0x100) || (g_local != 0x100)) || (b != 0x100)) && (0 < piVar1[2])) {
    iVar4 = 0;
    iVar5 = 0;
    do {
      iVar2 = *piVar1;
      iVar3 = PalGrpAndFlagZero(*(PalGrpFlag *)((int *)(iVar4 + iVar2) + 1),f);
      if (iVar3 != 0) {
        EBPalMul(*(int *)(iVar4 + iVar2),r,g_local,b);
      }
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 0x18;
    } while (iVar5 < piVar1[2]);
  }
  return;
}

/* PalGrpSetInvertAll @ 0x080b8b70, 135 bytes
 * FIXUP: rewrote 1 PalGrpFlag by-value loads */
void PalGrpSetInvertAll(PalGrpFlag f,int invert)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  piVar1 = (int *)g[0x413e];
  if ((invert != 0) && (iVar5 = 0, 0 < piVar1[2])) {
    iVar4 = 0;
    do {
      iVar2 = *piVar1;
      iVar3 = PalGrpAndFlagZero(*(PalGrpFlag *)((int *)(iVar4 + iVar2) + 1),f);
      if (iVar3 != 0) {
        EBPalInvertAll(*(int *)(iVar4 + iVar2),invert);
      }
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 0x18;
    } while (iVar5 < piVar1[2]);
  }
  return;
}

/* PalGrpSetColorBal @ 0x080b8c00, 137 bytes
 * FIXUP: rewrote 1 PalGrpFlag by-value loads */
void PalGrpSetColorBal(PalGrpFlag f,int colorbal)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  piVar1 = (int *)g[0x413e];
  if ((colorbal != 0x100) && (iVar5 = 0, 0 < piVar1[2])) {
    iVar4 = 0;
    do {
      iVar2 = *piVar1;
      iVar3 = PalGrpAndFlagZero(*(PalGrpFlag *)((int *)(iVar4 + iVar2) + 1),f);
      if (iVar3 != 0) {
        EBPalColorBal(*(int *)(iVar4 + iVar2),colorbal);
      }
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 0x18;
    } while (iVar5 < piVar1[2]);
  }
  return;
}

/* PalGrpSetClear @ 0x080b8c90, 128 bytes
 * FIXUP: rewrote 1 PalGrpFlag by-value loads */
void PalGrpSetClear(PalGrpFlag f)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  piVar1 = (int *)g[0x413e];
  if (0 < piVar1[2]) {
    iVar4 = 0;
    do {
      iVar2 = *piVar1;
      iVar3 = PalGrpAndFlagZero(*(PalGrpFlag *)((int *)(iVar4 + iVar2) + 1),f);
      if (iVar3 != 0) {
        EBPalReset(*(int *)(iVar4 + iVar2));
      }
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 0x18;
    } while (iVar5 < piVar1[2]);
  }
  return;
}

/* PalGrpMakeFlag @ 0x080b8d10, 100 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x30-byte frame (a local's address escapes, see apply_frame_emulation) */
PalGrpFlag * PalGrpMakeFlag(PalGrpFlag *__return_storage_ptr__,uint group,int unused)

{

  unsigned char ghidra_frame[0x30] __attribute__((aligned(16)));
#define local_2c (*(uint (*)[10])(ghidra_frame + 0x4))
  
  local_2c[0] = 0;
  local_2c[1] = 0;
  local_2c[2] = 0;
  local_2c[3] = 0;
  local_2c[4] = 0;
  local_2c[unused] = local_2c[unused] | group;
  __return_storage_ptr__->w[0] = local_2c[0];
  __return_storage_ptr__->w[1] = local_2c[1];
  __return_storage_ptr__->w[2] = local_2c[2];
  __return_storage_ptr__->w[3] = local_2c[3];
  __return_storage_ptr__->w[4] = local_2c[4];
  return __return_storage_ptr__;
}
#undef local_2c

/* PalGrpMakeFlagALL @ 0x080b8d80, 69 bytes
 * FIXUP: frame emulation: 5 stack locals placed at their original offsets in a 0x30-byte frame (a local's address escapes, see apply_frame_emulation) */
PalGrpFlag * PalGrpMakeFlagALL(PalGrpFlag *__return_storage_ptr__)

{
  uint *puVar1;
  int iVar2;
  unsigned char ghidra_frame[0x30] __attribute__((aligned(16)));
#define local_2c (*(uint *)(ghidra_frame + 0x4))
#define local_28 (*(uint *)(ghidra_frame + 0x8))
#define local_24 (*(uint *)(ghidra_frame + 0xc))
#define local_20 (*(uint *)(ghidra_frame + 0x10))
#define local_1c (*(uint (*)[7])(ghidra_frame + 0x14))
  
  iVar2 = 4;
  puVar1 = local_1c;
  do {
    *puVar1 = 0xffffffff;
    puVar1 = puVar1 + -1;
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  __return_storage_ptr__->w[0] = local_2c;
  __return_storage_ptr__->w[1] = local_28;
  __return_storage_ptr__->w[2] = local_24;
  __return_storage_ptr__->w[3] = local_20;
  __return_storage_ptr__->w[4] = local_1c[0];
  return __return_storage_ptr__;
}
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c

/* PalGrpOrFlag @ 0x080b8dd0, 70 bytes */
PalGrpFlag * PalGrpOrFlag(PalGrpFlag *__return_storage_ptr__,PalGrpFlag a,PalGrpFlag b)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar2 = 4;
  do {
    puVar1 = (uint *)((int)a.w + iVar3);
    *puVar1 = *puVar1 | *(uint *)((int)b.w + iVar3);
    iVar3 = iVar3 + 4;
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  __return_storage_ptr__->w[0] = a.w[0];
  __return_storage_ptr__->w[1] = a.w[1];
  __return_storage_ptr__->w[2] = a.w[2];
  __return_storage_ptr__->w[3] = a.w[3];
  __return_storage_ptr__->w[4] = a.w[4];
  return __return_storage_ptr__;
}

/* PalGrpXorFlag @ 0x080b8e20, 70 bytes */
PalGrpFlag * PalGrpXorFlag(PalGrpFlag *__return_storage_ptr__,PalGrpFlag a,PalGrpFlag b)

{
  uint *puVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar2 = 4;
  do {
    puVar1 = (uint *)((int)a.w + iVar3);
    *puVar1 = *puVar1 ^ *(uint *)((int)b.w + iVar3);
    iVar3 = iVar3 + 4;
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  __return_storage_ptr__->w[0] = a.w[0];
  __return_storage_ptr__->w[1] = a.w[1];
  __return_storage_ptr__->w[2] = a.w[2];
  __return_storage_ptr__->w[3] = a.w[3];
  __return_storage_ptr__->w[4] = a.w[4];
  return __return_storage_ptr__;
}

/* PalGrpAndFlagZero @ 0x080b8e70, 32 bytes */
int PalGrpAndFlagZero(PalGrpFlag a,PalGrpFlag b)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = 0;
  do {
    if ((*(uint *)((int)a.w + iVar2) & *(uint *)((int)b.w + iVar2)) != 0) {
      return 1;
    }
    iVar1 = iVar1 + 1;
    iVar2 = iVar2 + 4;
  } while (iVar1 < 5);
  return 0;
}

/* PalGrpFlagEqual @ 0x080b8e90, 32 bytes */
int PalGrpFlagEqual(PalGrpFlag a,PalGrpFlag b)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = 0;
  do {
    if (*(int *)((int)a.w + iVar2) != *(int *)((int)b.w + iVar2)) {
      return 0;
    }
    iVar1 = iVar1 + 1;
    iVar2 = iVar2 + 4;
  } while (iVar1 < 5);
  return 1;
}

/* PalGrpFlagIsNonZero @ 0x080b8eb0, 25 bytes */
int PalGrpFlagIsNonZero(PalGrpFlag a)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (a.w[iVar1] != 0) {
      return 1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 5);
  return 0;
}

/* PalFXReset @ 0x080b8ed0, 56 bytes */
void PalFXReset(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = 0xf; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_1[8] = 0x100;
  param_1[7] = 0x100;
  param_1[6] = 0x100;
  param_1[2] = 0x100;
  param_1[0xe] = 1;
  return;
}

/* PalFXUpdate @ 0x080b8f10, 593 bytes
 * FIXUP: renamed locals shadowing globals: g
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 4 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void PalFXUpdate(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                int param_7,int param_8)

{
  float10 fVar1;
  int iVar2;
  PalGrpFlag f;
  PalGrpFlag f_00;
  PalGrpFlag f_01;
  PalGrpFlag f_02;
  PalGrpFlag f_03;
  int g_local;
  int b;
  int iVar3;
  longdouble lVar4;
  
  if (param_1[0xe] != 0) {
    if (param_7 == 0) {
      f.w[1] = param_3;
      f.w[0] = param_2;
      f.w[2] = param_4;
      f.w[3] = param_5;
      f.w[4] = param_6;
      PalGrpSetClear(f);
    }
    else {
      MasterPalReset();
    }
    param_1[0xe] = 0;
  }
  iVar3 = param_1[1];
  if ((iVar3 != 0) && (iVar2 = g[0x750d], g[0x7309] == 0)) {
    if ((*param_1 < iVar3) || (iVar3 == -1)) {
      if (iVar3 != 0) {
        iVar3 = param_1[3];
        g_local = param_1[4];
        b = param_1[5];
        if (param_1[0xd] != 0) {
          lVar4 = (longdouble)((double)3.14159) * ((longdouble)*param_1 / (longdouble)param_1[0xd]);
          lVar4 = (longdouble)fsin(lVar4 + lVar4);
          fVar1 = (float)lVar4;
          iVar3 = (int)GHIDRA_FIST32((float10)param_1[9] * fVar1 + (float10)iVar3);
          g_local = (int)GHIDRA_FIST32((float10)param_1[10] * fVar1 + (float)g_local);
          b = (int)GHIDRA_FIST32((float)b + (float10)param_1[0xb] * fVar1);
        }
        if (param_7 == 0) {
          f_00.w[1] = param_3;
          f_00.w[0] = param_2;
          f_00.w[2] = param_4;
          f_00.w[3] = param_5;
          f_00.w[4] = param_6;
          PalGrpSetAdd(f_00,iVar3,g_local,b);
          f_01.w[1] = param_3;
          f_01.w[0] = param_2;
          f_01.w[2] = param_4;
          f_01.w[3] = param_5;
          f_01.w[4] = param_6;
          PalGrpSetMul(f_01,param_1[6],param_1[7],param_1[8]);
          f_02.w[1] = param_3;
          f_02.w[0] = param_2;
          f_02.w[2] = param_4;
          f_02.w[3] = param_5;
          f_02.w[4] = param_6;
          PalGrpSetInvertAll(f_02,param_1[0xc]);
          f_03.w[1] = param_3;
          f_03.w[0] = param_2;
          f_03.w[2] = param_4;
          f_03.w[3] = param_5;
          f_03.w[4] = param_6;
          PalGrpSetColorBal(f_03,param_1[2]);
        }
        else {
          MasterPalAdd(iVar3,g_local,b);
          MasterPalMul(param_1[6],param_1[7],param_1[8]);
          MasterPalInvertAll(param_1[0xc]);
          MasterPalColorBal(param_1[2]);
        }
        if ((param_8 & (iVar2 != 0) - 1) != 0) {
          *param_1 = *param_1 + 1;
        }
      }
    }
    else {
      PalFXReset(param_1);
    }
  }
  return;
}

