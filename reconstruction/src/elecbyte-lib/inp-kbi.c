/*
 * inp-kbi.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08053970-0x08053d22, 12 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* KBIClearKeyflags @ 0x08053970, 29 bytes */
void KBIClearKeyflags(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 0xb;
  puVar1 = (undefined4 *)(param_1 + 0x7c);
  do {
    *puVar1 = 0;
    puVar1 = puVar1 + 1;
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  return;
}

/* KBIRefreshKeyflags @ 0x08053990, 117 bytes */
void KBIRefreshKeyflags(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = 1;
  do {
    uVar2 = KBIFlippedKey(param_1,uVar4);
    uVar3 = KBToUInp(*(uint *)(param_2 + uVar4 * 4));
    iVar1 = *(int *)(param_1 + 0x78 + uVar2 * 4);
    if ((iVar1 != 0) != (uinpflag[uVar3] != 0)) {
      KBIStuffBuf(param_1,((iVar1 != 0) - 1 & 0xfffffff0) + 0x10 | uVar4 | 0x20);
    }
    uVar4 = uVar4 + 1;
  } while ((int)uVar4 < 0xd);
  return;
}

/* KBISetFlip @ 0x08053a10, 150 bytes */
void KBISetFlip(int param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 == *(int *)(param_1 + 0xb8)) {
    return;
  }
  if ((*(int *)(param_1 + 0xb4) == 0) &&
     ((*(int *)(param_1 + 0x88) == 0 || (*(int *)(param_1 + 0x80) == 0)))) {
    uVar1 = KBIFlippedKey(param_1,4);
    if (*(int *)(param_1 + 0x78 + uVar1 * 4) == 0) {
      uVar1 = KBIFlippedKey(param_1,2);
      if (*(int *)(param_1 + 0x78 + uVar1 * 4) == 0) goto LAB_08053a9c;
      KBIStuffBuf(param_1,0x32);
      uVar1 = 0x24;
    }
    else {
      KBIStuffBuf(param_1,0x34);
      uVar1 = 0x22;
    }
    KBIStuffBuf(param_1,uVar1);
  }
LAB_08053a9c:
  *(int *)(param_1 + 0xb8) = param_2;
  return;
}

/* KBIUpdate @ 0x08053ab0, 55 bytes
 * REVIEW: pid-unaff_ */
undefined4 KBIUpdate(int param_1,int param_2,uint param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 unaff_EBX;
  
  if (param_3 != 0) {
    uVar1 = KBIKeyMap(param_1,param_3);
    if (uVar1 != 0) {
      uVar2 = KBIStuffBuf(param_2,uVar1);
      return uVar2;
    }
  }
  return unaff_EBX;
}

/* KBIStuffBuf @ 0x08053af0, 36 bytes */
undefined4 KBIStuffBuf(int param_1,uint param_2)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = KBIFlippedKey(param_1,param_2);
  uVar2 = KBIStuffBufNoFlip(param_1,uVar1);
  return uVar2;
}

/* KBIStuffBufNoFlip @ 0x08053b20, 104 bytes */
uint KBIStuffBufNoFlip(int param_1,uint param_2)

{
  uint in_EAX;
  uint uVar1;
  
  if (((param_2 & 0xf) != 0) && (*(int *)(param_1 + 0xb4) == 0)) {
    *(uint *)(param_1 + *(int *)(param_1 + 0xb0) * 4) = param_2;
    uVar1 = *(int *)(param_1 + 0xb0) + 1;
    in_EAX = (0x1d < (int)uVar1) - 1 & uVar1;
    *(uint *)(param_1 + 0xb0) = in_EAX;
    if (in_EAX == *(uint *)(param_1 + 0xac)) {
      uVar1 = in_EAX + 1;
      in_EAX = (0x1d < (int)uVar1) - 1;
      *(uint *)(param_1 + 0xac) = uVar1 & in_EAX;
    }
    *(uint *)(param_1 + 0x78 + (param_2 & 0xf) * 4) = (param_2 >> 4 ^ 1) & 1;
  }
  return in_EAX;
}

/* KBIGetch @ 0x08053b90, 48 bytes */
undefined4 KBIGetch(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_1 + 0xac);
  if (iVar1 == *(int *)(param_1 + 0xb0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)(param_1 + iVar1 * 4);
    *(uint *)(param_1 + 0xac) = iVar1 + 1U & (0x1d < (int)(iVar1 + 1U)) - 1;
  }
  return uVar2;
}

/* KBIClearAll @ 0x08053bc0, 57 bytes */
undefined4 KBIClearAll(int param_1)

{
  int *piVar1;
  uint uVar2;
  
  uVar2 = 1;
  piVar1 = (int *)(param_1 + 0x7c);
  do {
    if (*piVar1 != 0) {
      KBIStuffBuf(param_1,uVar2 | 0x10);
    }
    uVar2 = uVar2 + 1;
    piVar1 = piVar1 + 1;
  } while ((int)uVar2 < 0xd);
  return 1;
}

/* KBIIs6Button @ 0x08053c00, 60 bytes */
undefined4 KBIIs6Button(uint param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 5;
  do {
    uVar1 = KBToUInp(*(uint *)(param_2 + iVar2 * 4));
    if (param_1 == uVar1) {
      return 1;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xb);
  return 0;
}

/* KBIIs6ButtonOrStart @ 0x08053c40, 62 bytes */
bool KBIIs6ButtonOrStart(uint param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  
  iVar1 = KBIIs6Button(param_1,param_2);
  if (iVar1 == 0) {
    uVar2 = KBToUInp(*(uint *)(param_2 + 0x2c));
    bVar3 = param_1 == uVar2;
  }
  else {
    bVar3 = true;
  }
  return bVar3;
}

/* KBIKeyMap @ 0x08053c80, 99 bytes */
uint KBIKeyMap(int param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = 0;
  if ((param_2 & 0x1000) != 0) {
    uVar4 = 0x10;
  }
  uVar2 = 1;
  while ((uVar3 = 0, (int)uVar2 < 0xd &&
         (uVar1 = KBToUInp(*(uint *)(param_1 + uVar2 * 4)), uVar3 = uVar2,
         (param_2 & 0xffffefff) != uVar1))) {
    uVar2 = uVar2 + 1;
  }
  if (uVar3 == 0) {
    uVar4 = 0;
  }
  else {
    uVar4 = uVar4 | uVar3;
  }
  return uVar4;
}

/* KBIFlippedKey @ 0x08053cf0, 50 bytes */
uint KBIFlippedKey(int param_1,uint param_2)

{
  if (*(int *)(param_1 + 0xb8) != 0) {
    if ((param_2 & 0xf) == 4) {
      param_2 = param_2 & 0xfffffff0 | 2;
    }
    else if ((param_2 & 0xf) == 2) {
      param_2 = param_2 & 0xfffffff0 | 4;
    }
  }
  return param_2;
}

