/*
 * pal-lib.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x080553c0-0x0805675f, 41 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* EBPalInit @ 0x080553c0, 160 bytes */
undefined4 EBPalInit(int *param_1,int param_2,void *param_3,int param_4)

{
  void *__dest;
  int iVar1;
  int *piVar2;
  
  piVar2 = param_1;
  for (iVar1 = 0x97; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar2 = 0;
    piVar2 = piVar2 + 1;
  }
  EBPalSettingsReset(param_1 + 3);
  EBPalSettingsReset(param_1 + 0xc);
  *param_1 = param_2;
  param_1[0x15] = param_1[0x15] | 4;
  if (param_4 == 0) {
    param_1[2] = (int)param_3;
  }
  else {
    __dest = calloc(1,param_2 * 4);
    param_1[2] = (int)__dest;
    if (__dest == (void *)0x0) {
      return 0;
    }
    memcpy(__dest,param_3,param_2 * 4);
    param_1[1] = 1;
  }
  EBPalGenerateFPal(param_1);
  return 1;
}

/* EBPalDeInit @ 0x08055460, 51 bytes */
void EBPalDeInit(int param_1)

{
  if ((*(int *)(param_1 + 4) != 0) && (*(void **)(param_1 + 8) != (void *)0x0)) {
    free(*(void **)(param_1 + 8));
  }
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  return;
}

/* EBPalReset @ 0x080554a0, 41 bytes */
uint EBPalReset(int param_1)

{
  uint in_EAX;
  
  if ((*(byte *)(param_1 + 0x54) & 4) == 0) {
    EBPalSettingsReset((undefined4 *)(param_1 + 0xc));
    in_EAX = *(uint *)(param_1 + 0x54) | 5;
    *(uint *)(param_1 + 0x54) = in_EAX;
  }
  return in_EAX;
}

/* EBPalCopy @ 0x080554d0, 108 bytes */
undefined4 EBPalCopy(int *param_1,int *param_2,int param_3)

{
  void *__dest;
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  piVar2 = param_2;
  piVar3 = param_1;
  for (iVar1 = 0x97; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar3 = *piVar2;
    piVar2 = piVar2 + 1;
    piVar3 = piVar3 + 1;
  }
  param_1[1] = 0;
  if (param_3 != 0) {
    iVar1 = *param_2;
    __dest = calloc(1,iVar1 * 4);
    param_1[2] = (int)__dest;
    if (__dest == (void *)0x0) {
      return 0;
    }
    memcpy(__dest,(void *)param_2[2],iVar1 * 4);
  }
  return 1;
}

/* EBPalGenerateFPal @ 0x08055540, 40 bytes */
void EBPalGenerateFPal(int *param_1)

{
  Pal4ToFpal(param_1[2],(int)(param_1 + 0x17),0,*param_1 + -1);
  param_1[0x15] = param_1[0x15] & 0xfffffffe;
  return;
}

/* EBPalUpdate @ 0x08055570, 229 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x40-byte frame (a local's address escapes, see apply_frame_emulation) */
void EBPalUpdate(int *param_1)

{
  bool bVar1;
  bool bVar2;
  uint uVar3;
  undefined3 extraout_var;
  int *piVar4;
  unsigned char ghidra_frame[0x40] __attribute__((aligned(16)));
#define local_3c (*(int (*)[12])(ghidra_frame + 0x4))
  
  piVar4 = local_3c;
  bVar1 = false;
  if ((G_RenderMode == 0) && (param_1[0x16] != MasterPal[0x13])) {
    bVar1 = true;
  }
  uVar3 = param_1[0x15] & 2;
  if (((!bVar1) && ((param_1[0x15] & 1U) == 0)) && (uVar3 == 0)) {
    return;
  }
  if (((bVar1) || (uVar3 != 0)) ||
     (bVar2 = EBPalSettingsAreSame((byte *)(param_1 + 3),(byte *)(param_1 + 0xc)),
     GHIDRA_ZEXT8(bVar2) == 0)) {
    if (bVar1) {
      EBPalSettingsMix(local_3c,MasterPal,param_1 + 3);
    }
    else {
      piVar4 = param_1 + 3;
    }
    Pal4SettingsToFpal(param_1[2],piVar4,(int)(param_1 + 0x17),0,*param_1 + -1);
    EBPalSettingsCopy(param_1 + 0xc,param_1 + 3);
    palupdatecount = palupdatecount + 1;
  }
  piVar4 = MasterPal;
  param_1[0x15] = param_1[0x15] & 0xfffffffc;
  param_1[0x16] = piVar4[0x13];
  return;
}
#undef local_3c

/* EBPalSetDataptr @ 0x08055660, 71 bytes */
undefined4 EBPalSetDataptr(int *param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if (param_1[1] == 0) {
    if (-1 < param_2) {
      *param_1 = param_2;
    }
    if ((param_3 != 0) && (param_3 != param_1[2])) {
      param_1[2] = param_3;
      EBPalMarkDataChanged((int)param_1);
    }
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* EBPalGetDataptr @ 0x080556b0, 8 bytes */
undefined4 EBPalGetDataptr(int param_1)

{
  return *(undefined4 *)(param_1 + 8);
}

/* EBPalGetNumcols @ 0x080556c0, 7 bytes */
undefined4 EBPalGetNumcols(undefined4 *param_1)

{
  return *param_1;
}

/* EBPalMarkDataChanged @ 0x080556d0, 14 bytes */
void EBPalMarkDataChanged(int param_1)

{
  *(uint *)(param_1 + 0x54) = *(uint *)(param_1 + 0x54) | 2;
  return;
}

/* EBPalSettingsReset @ 0x080556e0, 48 bytes */
void EBPalSettingsReset(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1;
  for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  param_1[6] = 0x100;
  param_1[5] = 0x100;
  param_1[4] = 0x100;
  *param_1 = 0x100;
  return;
}

/* EBPalSettingsCopy @ 0x08055710, 21 bytes */
void EBPalSettingsCopy(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  
  for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *param_2;
    param_2 = param_2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}

/* EBPalSettingsMix @ 0x08055730, 115 bytes */
void EBPalSettingsMix(int *param_1,int *param_2,int *param_3)

{
  int iVar1;
  
  *param_1 = *param_3 * *param_2 >> 8;
  param_1[1] = param_3[1] + param_2[1];
  param_1[2] = param_3[2] + param_2[1];
  param_1[3] = param_3[3] + param_2[1];
  param_1[4] = param_3[4] * param_2[4] >> 8;
  param_1[5] = param_3[5] * param_2[5] >> 8;
  param_1[6] = param_3[6] * param_2[6] >> 8;
  iVar1 = 0;
  if ((param_2[8] != 0) || (param_3[8] != 0)) {
    iVar1 = 1;
  }
  param_1[8] = iVar1;
  return;
}

/* EBPalSettingsAreSame @ 0x080557b0, 34 bytes */
bool EBPalSettingsAreSame(byte *param_1,byte *param_2)

{
  int iVar1;
  undefined1 in_CF;
  undefined1 in_ZF;
  
  iVar1 = 0x24;
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    in_CF = *param_1 < *param_2;
    in_ZF = *param_1 == *param_2;
    param_1 = param_1 + 1;
    param_2 = param_2 + 1;
  } while ((bool)in_ZF);
  return (!(bool)in_CF && !(bool)in_ZF) == (bool)in_CF;
}

/* EBPalAdd @ 0x080557e0, 67 bytes */
uint EBPalAdd(int param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  
  uVar1 = param_1 + 0xc;
  if (((param_2 != 0) || (param_3 != 0)) || (param_4 != 0)) {
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + param_2;
    *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + param_3;
    *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + param_4;
    uVar1 = *(uint *)(param_1 + 0x54) & 0xfffffffb | 1;
    *(uint *)(param_1 + 0x54) = uVar1;
  }
  return uVar1;
}

/* EBPalMul @ 0x08055830, 93 bytes */
void EBPalMul(int param_1,int param_2,int param_3,int param_4)

{
  if (((param_2 != 0x100) || (param_3 != 0x100)) || (param_4 != 0x100)) {
    *(int *)(param_1 + 0x1c) = param_2 * *(int *)(param_1 + 0x1c) >> 8;
    *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) * param_3 >> 8;
    *(int *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) * param_4 >> 8;
    *(uint *)(param_1 + 0x54) = *(uint *)(param_1 + 0x54) & 0xfffffffb | 1;
  }
  return;
}

/* EBPalInvertAll @ 0x08055890, 40 bytes */
void EBPalInvertAll(int param_1,int param_2)

{
  if (param_2 != 0) {
    *(uint *)(param_1 + 0x2c) = (uint)(*(int *)(param_1 + 0x2c) == 0);
    *(uint *)(param_1 + 0x54) = *(uint *)(param_1 + 0x54) & 0xfffffffb | 1;
  }
  return;
}

/* EBPalColorBal @ 0x080558c0, 40 bytes */
int EBPalColorBal(int param_1,int param_2)

{
  if (param_2 != 0x100) {
    *(int *)(param_1 + 0xc) = param_2 * *(int *)(param_1 + 0xc) >> 8;
    param_2 = *(uint *)(param_1 + 0x54) & 0xfffffffb | 1;
    *(int *)(param_1 + 0x54) = param_2;
  }
  return param_2;
}

/* MasterPalInit @ 0x080558f0, 91 bytes */
bool MasterPalInit(void)

{
  int *piVar1;
  
  if (MasterPal == (int *)0x0) {
    MasterPal = calloc(1,0x54);
  }
  piVar1 = MasterPal;
  if (MasterPal != (int *)0x0) {
    EBPalSettingsReset(MasterPal);
    EBPalSettingsReset(MasterPal + 9);
    piVar1 = MasterPal;
    MasterPal[0x14] = 1;
  }
  return piVar1 != (int *)0x0;
}

/* MasterPalDeInit @ 0x08055950, 38 bytes */
void MasterPalDeInit(void)

{
  if (MasterPal != (int *)0x0) {
    free(MasterPal);
    MasterPal = (int *)0x0;
  }
  return;
}

/* MasterPalProcessChanges @ 0x08055980, 65 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
void MasterPalProcessChanges(void)

{
  bool bVar1;
  undefined3 extraout_var;
  
  if (MasterPal[0x12] != 0) {
    bVar1 = EBPalSettingsAreSame((byte *)MasterPal,(byte *)(MasterPal + 9));
    if (GHIDRA_ZEXT8(bVar1) == 0) {
      MasterPal[0x13] = MasterPal[0x13] + 1;
    }
    else {
      MasterPal[0x12] = 0;
    }
  }
  return;
}

/* MasterPalFinishedDraw @ 0x080559d0, 46 bytes */
void MasterPalFinishedDraw(void)

{
  if (MasterPal[0x12] != 0) {
    EBPalSettingsCopy(MasterPal + 9,MasterPal);
    MasterPal[0x12] = 0;
  }
  return;
}

/* MasterPalReset @ 0x08055a00, 37 bytes */
void MasterPalReset(void)

{
  int *piVar1;
  
  EBPalSettingsReset(MasterPal);
  piVar1 = MasterPal;
  MasterPal[0x12] = 1;
  piVar1[0x14] = 1;
  return;
}

/* MasterPalAdd @ 0x08055a30, 63 bytes */
int * MasterPalAdd(int param_1,int param_2,int param_3)

{
  int *piVar1;
  
  piVar1 = MasterPal;
  if (((MasterPal[1] != param_1) || (MasterPal[2] != param_2)) || (MasterPal[3] != param_3)) {
    MasterPal[1] = param_1;
    piVar1[2] = param_2;
    piVar1[3] = param_3;
    piVar1 = MasterPal;
    MasterPal[0x12] = 1;
    piVar1[0x14] = 0;
  }
  return piVar1;
}

/* MasterPalMul @ 0x08055a70, 63 bytes */
int * MasterPalMul(int param_1,int param_2,int param_3)

{
  int *piVar1;
  
  piVar1 = MasterPal;
  if (((MasterPal[4] != param_1) || (MasterPal[5] != param_2)) || (MasterPal[6] != param_3)) {
    MasterPal[4] = param_1;
    piVar1[5] = param_2;
    piVar1[6] = param_3;
    piVar1 = MasterPal;
    MasterPal[0x12] = 1;
    piVar1[0x14] = 0;
  }
  return piVar1;
}

/* MasterPalInvertAll @ 0x08055ab0, 32 bytes */
void MasterPalInvertAll(int param_1)

{
  int *piVar1;
  
  piVar1 = MasterPal;
  if (MasterPal[8] != param_1) {
    MasterPal[8] = param_1;
    piVar1[0x12] = 1;
    piVar1[0x14] = 0;
  }
  return;
}

/* MasterPalColorBal @ 0x08055ad0, 30 bytes */
void MasterPalColorBal(int param_1)

{
  int *piVar1;
  
  piVar1 = MasterPal;
  if (*MasterPal != param_1) {
    *MasterPal = param_1;
    piVar1[0x12] = 1;
    piVar1[0x14] = 0;
  }
  return;
}

/* MasterPalConvertCol16 @ 0x08055af0, 129 bytes
 * FIXUP: frame emulation: 2 stack locals placed at their original offsets in a 0x10-byte frame (a local's address escapes, see apply_frame_emulation) */
uint MasterPalConvertCol16(uint param_1)

{
  undefined4 in_EDX;
  unsigned char ghidra_frame[0x10] __attribute__((aligned(16)));
#define local_a (*(ushort *)(ghidra_frame + 0x6))
#define local_8 (*(uint *)(ghidra_frame + 0x8))
  
  local_a = (ushort)((uint)in_EDX >> 0x10);
  if (MasterPal[0x14] == 0) {
    local_8 = (uint)(CONCAT11((char)((param_1 & 0x7e0) >> 3),(char)(param_1 >> 8)) & 0xfff8);
    local_8 = local_8 | (param_1 & 0x1f) << 0x13;
    Pal4SettingsToFpal((int)&local_8,MasterPal,(int)&local_a,0,0);
  }
  else {
    local_a = (ushort)param_1;
  }
  return (uint)local_a;
}
#undef local_a
#undef local_8

/* Pal3toPal4 @ 0x08055b80, 92 bytes */
void Pal3toPal4(undefined1 *param_1,undefined1 *param_2,int param_3,int param_4)

{
  undefined1 *puVar1;
  int iVar2;
  undefined1 uVar3;
  
  uVar3 = 0xff;
  if (param_4 != 0) {
    uVar3 = 0;
  }
  if (0 < param_3) {
    *param_1 = *param_2;
    puVar1 = param_2 + 2;
    param_1[1] = param_2[1];
    param_2 = param_2 + 3;
    param_1[2] = *puVar1;
    param_1[3] = uVar3;
    param_1 = param_1 + 4;
  }
  if (1 < param_3) {
    iVar2 = param_3 + -1;
    do {
      *param_1 = *param_2;
      puVar1 = param_2 + 2;
      param_1[1] = param_2[1];
      param_2 = param_2 + 3;
      param_1[2] = *puVar1;
      param_1[3] = 0xff;
      param_1 = param_1 + 4;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return;
}

/* Pal4Copy @ 0x08055be0, 69 bytes */
void Pal4Copy(int param_1,int param_2,int param_3,int param_4)

{
  if (param_1 != param_2) {
    memcpy((void *)(param_3 * 4 + param_2),(void *)(param_3 * 4 + param_1),
           (param_4 - param_3) * 4 + 4);
    return;
  }
  return;
}

/* Pal4SetSingle @ 0x08055c30, 41 bytes */
void Pal4SetSingle(int param_1,int param_2,undefined1 param_3,undefined1 param_4,undefined1 param_5)

{
  int iVar1;
  
  iVar1 = param_2 * 4;
  *(undefined1 *)(iVar1 + param_1) = param_3;
  *(undefined1 *)(iVar1 + 1 + param_1) = param_4;
  *(undefined1 *)(iVar1 + 2 + param_1) = param_5;
  return;
}

/* Pal4Contrast @ 0x08055c60, 155 bytes */
void Pal4Contrast(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  
  if (param_3 == 0x100) {
    Pal4Copy(param_1,param_2,param_4,param_5);
    return;
  }
  for (iVar2 = param_4 * 4; iVar2 < param_5 * 4 + 4; iVar2 = iVar2 + 4) {
    iVar1 = (int)((uint)*(byte *)(iVar2 + param_1) * param_3) >> 8;
    if (0xff < iVar1) {
      iVar1 = 0xff;
    }
    *(char *)(iVar2 + param_2) = (char)iVar1;
    iVar1 = (int)((uint)*(byte *)(iVar2 + 1 + param_1) * param_3) >> 8;
    if (0xff < iVar1) {
      iVar1 = 0xff;
    }
    *(char *)(iVar2 + 1 + param_2) = (char)iVar1;
    iVar1 = (int)((uint)*(byte *)(iVar2 + 2 + param_1) * param_3) >> 8;
    if (0xff < iVar1) {
      iVar1 = 0xff;
    }
    *(char *)(iVar2 + 2 + param_2) = (char)iVar1;
  }
  return;
}

/* Pal4ContrastRGB @ 0x08055d00, 200 bytes */
void Pal4ContrastRGB(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                    int param_7)

{
  int iVar1;
  int iVar2;
  
  if (((param_3 == 0x100) && (param_4 == 0x100)) && (param_5 == 0x100)) {
    Pal4Copy(param_1,param_2,param_6,param_7);
    return;
  }
  for (iVar2 = param_6 * 4; iVar2 < param_7 * 4 + 4; iVar2 = iVar2 + 4) {
    iVar1 = (int)((uint)*(byte *)(iVar2 + param_1) * param_3) >> 8;
    if (0xff < iVar1) {
      iVar1 = 0xff;
    }
    *(char *)(iVar2 + param_2) = (char)iVar1;
    iVar1 = (int)((uint)*(byte *)(iVar2 + 1 + param_1) * param_4) >> 8;
    if (0xff < iVar1) {
      iVar1 = 0xff;
    }
    *(char *)(iVar2 + 1 + param_2) = (char)iVar1;
    iVar1 = (int)((uint)*(byte *)(iVar2 + 2 + param_1) * param_5) >> 8;
    if (0xff < iVar1) {
      iVar1 = 0xff;
    }
    *(char *)(iVar2 + 2 + param_2) = (char)iVar1;
  }
  return;
}

/* Pal4Brightness @ 0x08055dd0, 193 bytes */
void Pal4Brightness(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  
  if (param_3 == 0) {
    Pal4Copy(param_1,param_2,param_4,param_5);
    return;
  }
  for (iVar1 = param_4 * 4; iVar1 < param_5 * 4 + 4; iVar1 = iVar1 + 4) {
    iVar2 = (uint)*(byte *)(iVar1 + param_1) + param_3;
    if (0xff < iVar2) {
      iVar2 = 0xff;
    }
    *(byte *)(iVar1 + param_2) = (byte)iVar2 & -(char)(iVar2 >> 0x1f) - 1U;
    iVar2 = (uint)*(byte *)(iVar1 + 1 + param_1) + param_3;
    if (0xff < iVar2) {
      iVar2 = 0xff;
    }
    *(byte *)(iVar1 + 1 + param_2) = (byte)iVar2 & -(char)(iVar2 >> 0x1f) - 1U;
    iVar2 = (uint)*(byte *)(iVar1 + 2 + param_1) + param_3;
    if (0xff < iVar2) {
      iVar2 = 0xff;
    }
    *(byte *)(iVar1 + 2 + param_2) = (byte)iVar2 & -(char)(iVar2 >> 0x1f) - 1U;
  }
  return;
}

/* Pal4BrightnessRGB @ 0x08055ea0, 231 bytes */
void Pal4BrightnessRGB(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                      int param_7)

{
  int iVar1;
  int iVar2;
  
  if (((param_3 == 0) && (param_4 == 0)) && (param_5 == 0)) {
    Pal4Copy(param_1,param_2,param_6,param_7);
    return;
  }
  for (iVar1 = param_6 * 4; iVar1 < param_7 * 4 + 4; iVar1 = iVar1 + 4) {
    iVar2 = param_3 + (uint)*(byte *)(iVar1 + param_1);
    if (0xff < iVar2) {
      iVar2 = 0xff;
    }
    *(byte *)(iVar1 + param_2) = (byte)iVar2 & -(char)(iVar2 >> 0x1f) - 1U;
    iVar2 = param_4 + (uint)*(byte *)(iVar1 + 1 + param_1);
    if (0xff < iVar2) {
      iVar2 = 0xff;
    }
    *(byte *)(iVar1 + 1 + param_2) = (byte)iVar2 & -(char)(iVar2 >> 0x1f) - 1U;
    iVar2 = (uint)*(byte *)(iVar1 + 2 + param_1) + param_5;
    if (0xff < iVar2) {
      iVar2 = 0xff;
    }
    *(byte *)(iVar1 + 2 + param_2) = (byte)iVar2 & -(char)(iVar2 >> 0x1f) - 1U;
  }
  return;
}

/* Pal4ColorBal @ 0x08055f90, 312 bytes */
void Pal4ColorBal(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  byte *pbVar1;
  byte *pbVar2;
  int iVar3;
  byte bVar4;
  undefined1 uVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  
  iVar3 = param_5 * 4 + 4;
  if (param_3 == 0) {
    iVar7 = param_4 * 4;
    pbVar8 = (byte *)(iVar7 + param_1);
    for (; iVar7 < iVar3; iVar7 = iVar7 + 4) {
      bVar4 = *pbVar8;
      pbVar1 = pbVar8 + 1;
      pbVar2 = pbVar8 + 2;
      pbVar8 = pbVar8 + 4;
      uVar5 = (undefined1)((int)((uint)bVar4 * 5 + (uint)*pbVar1 * 7 + (uint)*pbVar2 * 4) >> 4);
      *(undefined1 *)(iVar7 + 2 + param_2) = uVar5;
      *(undefined1 *)(iVar7 + 1 + param_2) = uVar5;
      *(undefined1 *)(iVar7 + param_2) = uVar5;
    }
  }
  else {
    if (0xfe < param_3 - 1U) {
      Pal4Copy(param_1,param_2,param_4,param_5);
      return;
    }
    iVar7 = param_4 * 4;
    pbVar8 = (byte *)(iVar7 + param_1);
    for (; iVar7 < iVar3; iVar7 = iVar7 + 4) {
      iVar6 = ((int)((uint)*pbVar8 * 5 + (uint)pbVar8[1] * 7 + (uint)pbVar8[2] * 4) >> 4) *
              (0x100 - param_3);
      *(char *)(iVar7 + param_2) = (char)((uint)*pbVar8 * param_3 + iVar6 >> 8);
      *(char *)(iVar7 + 1 + param_2) = (char)((uint)pbVar8[1] * param_3 + iVar6 >> 8);
      pbVar1 = pbVar8 + 2;
      pbVar8 = pbVar8 + 4;
      *(char *)(iVar7 + 2 + param_2) = (char)((uint)*pbVar1 * param_3 + iVar6 >> 8);
    }
  }
  return;
}

/* Pal4InvertAll @ 0x080560d0, 72 bytes */
void Pal4InvertAll(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  for (iVar1 = param_3 * 4; iVar1 < (param_4 + 1) * 4; iVar1 = iVar1 + 4) {
    *(byte *)(iVar1 + param_2) = *(byte *)(iVar1 + param_1) ^ 0xff;
    *(byte *)(iVar1 + 1 + param_2) = *(byte *)(iVar1 + 1 + param_1) ^ 0xff;
    *(byte *)(iVar1 + 2 + param_2) = *(byte *)(iVar1 + 2 + param_1) ^ 0xff;
  }
  return;
}

/* Pal4Read3File @ 0x08056120, 159 bytes */
undefined4 Pal4Read3File(int param_1,char *param_2)

{
  FILE *__fp;
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  __fp = fopen(param_2,"rb");
  if (__fp == (FILE *)0x0) {
    uVar1 = 0;
  }
  else {
    do {
      iVar3 = (0xff - iVar4) * 4;
      iVar2 = fgetc(__fp);
      *(char *)(iVar3 + param_1) = (char)iVar2;
      iVar2 = fgetc(__fp);
      *(char *)(iVar3 + 1 + param_1) = (char)iVar2;
      iVar2 = fgetc(__fp);
      *(char *)(iVar3 + 2 + param_1) = (char)iVar2;
      iVar2 = feof(__fp);
      if (iVar2 != 0) {
        fclose(__fp);
        return 0;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x100);
    fclose(__fp);
    uVar1 = 1;
  }
  return uVar1;
}

/* Pal4Read3FilePtr @ 0x080561c0, 151 bytes */
undefined4 Pal4Read3FilePtr(int param_1,int *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  while( true ) {
    iVar2 = (0xff - iVar3) * 4;
    uVar1 = MFgetc(param_2);
    *(char *)(iVar2 + param_1) = (char)uVar1;
    uVar1 = MFgetc(param_2);
    *(char *)(iVar2 + 1 + param_1) = (char)uVar1;
    uVar1 = MFgetc(param_2);
    *(char *)(iVar2 + 2 + param_1) = (char)uVar1;
    iVar2 = MFfeof(param_2);
    if ((iVar2 != 0) && (iVar3 != 0xff)) break;
    iVar3 = iVar3 + 1;
    if (0xff < iVar3) {
      if (*param_2 != 3) {
        MFfclose(param_2);
      }
      return 1;
    }
  }
  if (*param_2 != 3) {
    MFfclose(param_2);
  }
  return 0;
}

/* Pal4ToFpal @ 0x08056260, 93 bytes */
void Pal4ToFpal(int param_1,int param_2,int param_3,int param_4)

{
  byte *pbVar1;
  byte *pbVar2;
  byte bVar3;
  byte *pbVar4;
  ushort *puVar5;
  int iVar6;
  
  pbVar4 = (byte *)(param_3 * 4 + param_1);
  puVar5 = (ushort *)(param_3 * 2 + param_2);
  for (iVar6 = (param_4 - param_3) + 1; iVar6 != 0; iVar6 = iVar6 + -1) {
    bVar3 = *pbVar4;
    pbVar1 = pbVar4 + 1;
    pbVar2 = pbVar4 + 2;
    pbVar4 = pbVar4 + 4;
    *puVar5 = (ushort)(bVar3 >> 3) << 0xb | (ushort)(*pbVar1 >> 2) << 5 | (ushort)(*pbVar2 >> 3);
    puVar5 = puVar5 + 1;
  }
  return;
}

/* Pal4SettingsToFpal @ 0x080562c0, 1183 bytes */
void Pal4SettingsToFpal(int param_1,int *param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  int local_18;
  
  iVar1 = (param_5 - param_4) * 4 + 4;
  iVar9 = param_4 * 2 + param_3;
  uVar8 = ((param_2[8] != 0) - 1 & 0xffffff01) + 0xff;
  iVar16 = param_4 * 4 + param_1;
  iVar17 = *param_2;
  iVar2 = param_2[1];
  iVar3 = param_2[2];
  iVar4 = param_2[3];
  iVar5 = param_2[4];
  iVar6 = param_2[5];
  iVar7 = param_2[6];
  if ((((iVar5 == 0x100) && (iVar6 == 0x100)) && (iVar7 == 0x100)) && (iVar17 == 0x100)) {
    local_18 = 0;
    if (0 < iVar1) {
      iVar17 = 0;
      do {
        uVar12 = iVar2 + (*(byte *)(iVar17 + iVar16) ^ uVar8);
        uVar12 = uVar12 & 0xffffffffU - ((int)uVar12 >> 0x1f);
        if (0xff < (int)uVar12) {
          uVar12 = 0xff;
        }
        uVar15 = iVar3 + (*(byte *)(iVar17 + 1 + iVar16) ^ uVar8);
        uVar15 = uVar15 & 0xffffffffU - ((int)uVar15 >> 0x1f);
        if (0xff < (int)uVar15) {
          uVar15 = 0xff;
        }
        uVar10 = iVar4 + (*(byte *)(iVar17 + 2 + iVar16) ^ uVar8);
        uVar10 = uVar10 & 0xffffffffU - ((int)uVar10 >> 0x1f);
        if (0xff < (int)uVar10) {
          uVar10 = 0xff;
        }
        iVar17 = iVar17 + 4;
        *(ushort *)(iVar9 + local_18 * 2) =
             (ushort)(((int)uVar12 >> 3) << 0xb) | (ushort)(((int)uVar15 >> 2) << 5) |
             (ushort)((int)uVar10 >> 3);
        local_18 = local_18 + 1;
      } while (iVar17 < iVar1);
    }
  }
  else if (iVar17 == 0) {
    iVar17 = 0;
    local_18 = 0;
    if (0 < iVar1) {
      do {
        uVar12 = (int)((uint)*(byte *)(iVar17 + iVar16) * 5 +
                       (uint)*(byte *)(iVar17 + 1 + iVar16) * 7 +
                      (uint)*(byte *)(iVar17 + 2 + iVar16) * 4) >> 4 ^ uVar8;
        iVar13 = (iVar2 + uVar12) * iVar5;
        uVar15 = iVar13 >> 8 & 0xffffffffU - (iVar13 >> 0x1f);
        if (0xff < (int)uVar15) {
          uVar15 = 0xff;
        }
        iVar13 = (iVar3 + uVar12) * iVar6;
        uVar10 = iVar13 >> 8 & 0xffffffffU - (iVar13 >> 0x1f);
        if (0xff < (int)uVar10) {
          uVar10 = 0xff;
        }
        iVar13 = (uVar12 + iVar4) * iVar7;
        uVar12 = iVar13 >> 8 & 0xffffffffU - (iVar13 >> 0x1f);
        if (0xff < (int)uVar12) {
          uVar12 = 0xff;
        }
        iVar17 = iVar17 + 4;
        *(ushort *)(iVar9 + local_18 * 2) =
             (ushort)(((int)uVar15 >> 3) << 0xb) | (ushort)(((int)uVar10 >> 2) << 5) |
             (ushort)((int)uVar12 >> 3);
        local_18 = local_18 + 1;
      } while (iVar17 < iVar1);
    }
  }
  else if (iVar17 < 0x100) {
    iVar13 = 0;
    local_18 = 0;
    if (0 < iVar1) {
      do {
        uVar10 = (uint)*(byte *)(iVar13 + 1 + iVar16);
        uVar12 = (uint)*(byte *)(iVar13 + 2 + iVar16);
        iVar11 = ((int)((uint)*(byte *)(iVar13 + iVar16) * 5 + uVar10 * 7 + uVar12 * 4) >> 4) *
                 (0x100 - iVar17);
        iVar14 = (((int)((uint)*(byte *)(iVar13 + iVar16) * iVar17 + iVar11) >> 8 ^ uVar8) + iVar2)
                 * iVar5;
        uVar15 = iVar14 >> 8 & 0xffffffffU - (iVar14 >> 0x1f);
        if (0xff < (int)uVar15) {
          uVar15 = 0xff;
        }
        iVar14 = (iVar3 + ((int)(iVar11 + uVar10 * iVar17) >> 8 ^ uVar8)) * iVar6;
        uVar10 = iVar14 >> 8 & 0xffffffffU - (iVar14 >> 0x1f);
        if (0xff < (int)uVar10) {
          uVar10 = 0xff;
        }
        iVar11 = (iVar4 + ((int)(uVar12 * iVar17 + iVar11) >> 8 ^ uVar8)) * iVar7;
        uVar12 = iVar11 >> 8 & 0xffffffffU - (iVar11 >> 0x1f);
        if (0xff < (int)uVar12) {
          uVar12 = 0xff;
        }
        iVar13 = iVar13 + 4;
        *(ushort *)(iVar9 + local_18 * 2) =
             (ushort)(((int)uVar15 >> 3) << 0xb) | (ushort)(((int)uVar10 >> 2) << 5) |
             (ushort)((int)uVar12 >> 3);
        local_18 = local_18 + 1;
      } while (iVar13 < iVar1);
    }
  }
  else {
    local_18 = 0;
    if (0 < iVar1) {
      iVar17 = 0;
      do {
        iVar13 = (iVar2 + (*(byte *)(iVar17 + iVar16) ^ uVar8)) * iVar5;
        uVar12 = iVar13 >> 8 & 0xffffffffU - (iVar13 >> 0x1f);
        if (0xff < (int)uVar12) {
          uVar12 = 0xff;
        }
        iVar13 = (iVar3 + (*(byte *)(iVar17 + 1 + iVar16) ^ uVar8)) * iVar6;
        uVar15 = iVar13 >> 8 & 0xffffffffU - (iVar13 >> 0x1f);
        if (0xff < (int)uVar15) {
          uVar15 = 0xff;
        }
        iVar13 = (iVar4 + (*(byte *)(iVar17 + 2 + iVar16) ^ uVar8)) * iVar7;
        uVar10 = iVar13 >> 8 & 0xffffffffU - (iVar13 >> 0x1f);
        if (0xff < (int)uVar10) {
          uVar10 = 0xff;
        }
        iVar17 = iVar17 + 4;
        *(ushort *)(iVar9 + local_18 * 2) =
             (ushort)(((int)uVar12 >> 3) << 0xb) | (ushort)(((int)uVar15 >> 2) << 5) |
             (ushort)((int)uVar10 >> 3);
        local_18 = local_18 + 1;
      } while (iVar17 < iVar1);
    }
  }
  return;
}

