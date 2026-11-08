/*
 * input-lb.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08053ee0-0x08054563, 22 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"

extern int *uinpkeymap __asm__("D_08287134"); /* file-static 0x08287134 */
extern volatile byte uinpbuf[16] __asm__("D_08287138"); /* file-static 0x08287138 */
extern volatile void *uinpbufptr __asm__("D_08287148"); /* file-static 0x08287148 */

/* UInpKBHook @ 0x08053ee0, 116 bytes */
undefined4 UInpKBHook(uint param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  undefined4 in_EAX;
  undefined4 uVar3;
  
  if (uinpkeymap != (int *)0x0) {
    param_1 = uinpkeymap[param_1];
  }
  bVar1 = uinpflag[param_1];
  if (param_2 == 0) {
    bVar2 = uinpflag[param_1] & 0xfe;
  }
  else {
    bVar2 = uinpflag[param_1] | 1;
  }
  uinpflag[param_1] = bVar2;
  if ((bVar1 == 0) != (uinpflag[param_1] == 0)) {
    if (uinpflag[param_1] == 0) {
      param_1 = param_1 | 0x1000;
    }
    uVar3 = UInpStuff(param_1);
    return uVar3;
  }
  return in_EAX;
}

/* UInpPadHook @ 0x08053f60, 118 bytes */
void UInpPadHook(int param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  
  uVar3 = param_1 + 0x100;
  if (uinpkeymap != (int *)0x0) {
    uVar3 = uinpkeymap[uVar3];
  }
  bVar1 = uinpflag[uVar3];
  if (param_2 == 0) {
    bVar2 = uinpflag[uVar3] & 0xfd;
  }
  else {
    bVar2 = uinpflag[uVar3] | 2;
  }
  uinpflag[uVar3] = bVar2;
  if ((bVar1 == 0) != (uinpflag[uVar3] == 0)) {
    if (uinpflag[uVar3] == 0) {
      uVar3 = uVar3 | 0x1000;
    }
    UInpStuff(uVar3);
    return;
  }
  return;
}

/* UInpInit @ 0x08053fe0, 136 bytes
 * FIXUP: 2 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
undefined4 UInpInit(void)

{
  bool bVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar2;
  
  bVar1 = IntCircBufIsValid(uinpbufptr);
  if ((((GHIDRA_ZEXT8(bVar1) != 0) ||
       (bVar1 = IntCircBufInit(uinpbufptr,0x100), GHIDRA_ZEXT8(bVar1) != 0)) &&
      (iVar2 = KBInstallHitHook(UInpKBHook), iVar2 != 0)) &&
     (iVar2 = PadInstallHitHook(UInpPadHook), iVar2 != 0)) {
    memset(uinpflag,0,0x181);
    UInpBufClear();
    UInpRefreshFlags();
    return 1;
  }
  return 0;
}

/* UInpReInit @ 0x08054070, 21 bytes */
undefined4 UInpReInit(void)

{
  undefined4 uVar1;
  
  KBRemoveHitHook();
  PadRemoveHitHook();
  uVar1 = UInpInit();
  return uVar1;
}

/* UInpDeInit @ 0x08054090, 36 bytes */
void UInpDeInit(void)

{
  KBRemoveHitHook();
  PadRemoveHitHook();
  UInpResetKeyMap();
  IntCircBufDeInit(uinpbufptr);
  return;
}

/* UInpRefreshFlags @ 0x080540c0, 217 bytes */
void UInpRefreshFlags(void)

{
  byte *pbVar1;
  int *piVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  
  memset(uinpflag,0,0x181);
  if (uinpkeymap == (int *)0x0) {
    iVar4 = 0;
    do {
      uinpflag[iVar4] = uinpflag[iVar4] | keyflag[iVar4] != 0;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x100);
    iVar5 = 0;
    iVar4 = 0x100;
    do {
      bVar3 = uinpflag[iVar4];
      if (keyflag[iVar4 + 0x20] != 0) {
        bVar3 = bVar3 | 2;
      }
      iVar5 = iVar5 + 1;
      uinpflag[iVar4] = bVar3;
      iVar4 = iVar4 + 1;
    } while (iVar5 < 0x80);
  }
  else {
    iVar4 = 0;
    do {
      piVar2 = uinpkeymap + iVar4;
      pbVar1 = keyflag + iVar4;
      iVar4 = iVar4 + 1;
      uinpflag[*piVar2] = uinpflag[*piVar2] | *pbVar1 != 0;
      piVar2 = uinpkeymap;
    } while (iVar4 < 0x100);
    iVar4 = 0;
    do {
      iVar5 = iVar4 + 0x100;
      bVar3 = uinpflag[piVar2[iVar5]];
      if (padflag[iVar4] != 0) {
        bVar3 = bVar3 | 2;
      }
      iVar4 = iVar4 + 1;
      uinpflag[piVar2[iVar5]] = bVar3;
    } while (iVar4 < 0x80);
  }
  return;
}

/* UInpSetKeyMap @ 0x080541a0, 68 bytes */
undefined4 UInpSetKeyMap(undefined4 *param_1)

{
  int iVar1;
  int *piVar2;
  
  if ((uinpkeymap == (int *)0x0) && (uinpkeymap = calloc(4,0x181), uinpkeymap == (int *)0x0)) {
    return 0;
  }
  piVar2 = uinpkeymap;
  for (iVar1 = 0x180; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar2 = *param_1;
    param_1 = param_1 + 1;
    piVar2 = piVar2 + 1;
  }
  return 1;
}

/* UInpGetKeyMap @ 0x080541f0, 61 bytes */
undefined4 UInpGetKeyMap(undefined4 *param_1)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  
  if (uinpkeymap == (int *)0x0) {
    iVar3 = 0x17f;
    piVar2 = param_1 + 0x17f;
    do {
      *piVar2 = iVar3;
      piVar2 = piVar2 + -1;
      iVar3 = iVar3 + -1;
    } while (-1 < iVar3);
    uVar1 = 0;
  }
  else {
    piVar2 = uinpkeymap;
    for (iVar3 = 0x180; iVar3 != 0; iVar3 = iVar3 + -1) {
      *param_1 = *piVar2;
      piVar2 = piVar2 + 1;
      param_1 = param_1 + 1;
    }
    uVar1 = 1;
  }
  return uVar1;
}

/* UInpResetKeyMap @ 0x08054230, 38 bytes */
void UInpResetKeyMap(void)

{
  int *__ptr;
  
  __ptr = uinpkeymap;
  if (uinpkeymap != (int *)0x0) {
    uinpkeymap = (int *)0x0;
    free(__ptr);
  }
  return;
}

/* UInpStuff @ 0x08054260, 49 bytes */
undefined4 UInpStuff(undefined4 param_1)

{
  undefined4 in_EAX;
  undefined4 extraout_EAX;
  
  if ((PadInstalled != 0) || (KBInstalled != 0)) {
    IntCircBufStuff(uinpbufptr,param_1);
    in_EAX = extraout_EAX;
  }
  return in_EAX;
}

/* UInpGet @ 0x080542a0, 90 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
undefined4 UInpGet(void)

{
  bool bVar1;
  undefined4 uVar2;
  undefined3 extraout_var;
  
  if ((PadInstalled == 0) && (KBInstalled == 0)) {
    uVar2 = 0;
  }
  else {
    while( true ) {
      bVar1 = IntCircBufIsEmpty((int)uinpbufptr);
      if (GHIDRA_ZEXT8(bVar1) == 0) break;
      if (PadInstalled != 0) {
        PadPoll();
      }
    }
    uVar2 = IntCircBufGet(uinpbufptr);
  }
  return uVar2;
}

/* UInpHit @ 0x08054300, 63 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
bool UInpHit(void)

{
  bool bVar1;
  undefined3 extraout_var;
  
  if ((PadInstalled == 0) && (KBInstalled == 0)) {
    bVar1 = false;
  }
  else {
    bVar1 = IntCircBufIsEmpty((int)uinpbufptr);
    bVar1 = GHIDRA_ZEXT8(bVar1) == 0;
  }
  return bVar1;
}

/* UInpBufClear @ 0x08054340, 19 bytes */
void UInpBufClear(void)

{
  IntCircBufClear((int)uinpbufptr);
  return;
}

/* KBToUInp @ 0x08054360, 83 bytes */
uint KBToUInp(uint param_1)

{
  uint uVar1;
  
  uVar1 = param_1 & 0xfffffeff;
  if (0x100 < (int)uVar1) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("uinp_ch <= 256","src/lib/input-lb.c",0x130,"KBToUInp");
  }
  if ((uVar1 == 0x100) || (uVar1 == 0)) {
    uVar1 = 0x180;
  }
  else if ((param_1 & 0x100) != 0) {
    uVar1 = uVar1 | 0x1000;
  }
  return uVar1;
}

/* PadToUInp @ 0x080543c0, 90 bytes */
uint PadToUInp(uint param_1)

{
  uint uVar1;
  
  uVar1 = param_1 & 0xfffffeff;
  if (0x80 < (int)uVar1) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("uinp_ch <= (0x20*4)","src/lib/input-lb.c",0x140,"PadToUInp");
  }
  if (uVar1 == 0x80) {
    uVar1 = 0x180;
  }
  else if ((uVar1 != 0) && (uVar1 = uVar1 + 0x100, (param_1 & 0x100) != 0)) {
    uVar1 = uVar1 | 0x1000;
  }
  return uVar1;
}

/* IntCircBufInit @ 0x08054420, 80 bytes */
bool IntCircBufInit(undefined4 *param_1,int param_2)

{
  void *pvVar1;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  pvVar1 = calloc(1,param_2 * 4);
  *param_1 = pvVar1;
  if (pvVar1 != (void *)0x0) {
    param_1[3] = param_2;
  }
  return pvVar1 != (void *)0x0;
}

/* IntCircBufDeInit @ 0x08054470, 56 bytes */
undefined4 IntCircBufDeInit(undefined4 *param_1)

{
  undefined4 in_ECX;
  
  if ((void *)*param_1 != (void *)0x0) {
    free((void *)*param_1);
  }
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  return in_ECX;
}

/* IntCircBufIsValid @ 0x080544b0, 14 bytes */
bool IntCircBufIsValid(int *param_1)

{
  return *param_1 != 0;
}

/* IntCircBufStuff @ 0x080544c0, 60 bytes */
void IntCircBufStuff(int *param_1,undefined4 param_2)

{
  uint uVar1;
  
  *(undefined4 *)(*param_1 + param_1[2] * 4) = param_2;
  uVar1 = param_1[2] + 1U & (param_1[3] <= (int)(param_1[2] + 1U)) - 1;
  param_1[2] = uVar1;
  if (uVar1 == param_1[1]) {
    param_1[1] = uVar1 + 1 & (param_1[3] <= (int)(uVar1 + 1)) - 1;
  }
  return;
}

/* IntCircBufGet @ 0x08054500, 61 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
undefined4 IntCircBufGet(int *param_1)

{
  bool bVar1;
  undefined3 extraout_var;
  undefined4 uVar2;
  uint uVar3;
  
  bVar1 = IntCircBufIsEmpty((int)param_1);
  if (GHIDRA_ZEXT8(bVar1) == 0) {
    uVar2 = *(undefined4 *)(*param_1 + param_1[1] * 4);
    uVar3 = param_1[1] + 1;
    param_1[1] = uVar3 & (param_1[3] <= (int)uVar3) - 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* IntCircBufIsEmpty @ 0x08054540, 16 bytes */
bool IntCircBufIsEmpty(int param_1)

{
  return *(int *)(param_1 + 4) == *(int *)(param_1 + 8);
}

/* IntCircBufClear @ 0x08054550, 19 bytes */
void IntCircBufClear(int param_1)

{
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  return;
}

