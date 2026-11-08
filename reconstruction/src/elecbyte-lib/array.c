/*
 * array.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0804a930-0x0804b0e4, 21 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* ArrayNew @ 0x0804a930, 139 bytes */
undefined4 * ArrayNew(size_t param_1,size_t param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  void *pvVar2;
  
  puVar1 = calloc(1,0x2c);
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = param_3;
    puVar1[1] = param_2;
    puVar1[3] = param_1;
    puVar1[2] = 0;
    puVar1[4] = 0;
    pvVar2 = calloc(param_1,param_2);
    puVar1[5] = pvVar2;
    if (pvVar2 != (void *)0x0) {
      pvVar2 = calloc(param_1 + 1,0x10);
      puVar1[6] = pvVar2;
      if (pvVar2 != (void *)0x0) {
        puVar1[10] = 0;
        puVar1[9] = 0;
        return puVar1;
      }
    }
    ArrayFree(puVar1);
  }
  return (undefined4 *)0x0;
}

/* ArrayCopy @ 0x0804a9c0, 183 bytes */
undefined4 * ArrayCopy(undefined4 *param_1)

{
  size_t __size;
  size_t __nmemb;
  undefined4 *puVar1;
  void *pvVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  puVar1 = calloc(1,0x2c);
  if (puVar1 != (undefined4 *)0x0) {
    puVar4 = param_1;
    puVar5 = puVar1;
    for (iVar3 = 0xb; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    __size = param_1[1];
    __nmemb = param_1[3];
    puVar1[6] = 0;
    puVar1[5] = 0;
    pvVar2 = calloc(__nmemb,__size);
    puVar1[5] = pvVar2;
    if (pvVar2 != (void *)0x0) {
      pvVar2 = calloc(param_1[3] + 1,0x10);
      puVar1[6] = pvVar2;
      if (pvVar2 != (void *)0x0) {
        memcpy((void *)puVar1[5],(void *)param_1[5],param_1[1] * param_1[3]);
        puVar4 = (undefined4 *)param_1[6];
        puVar5 = (undefined4 *)puVar1[6];
        for (iVar3 = (param_1[3] & 0xfffffff) << 2; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar5 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar5 = puVar5 + 1;
        }
        return puVar1;
      }
    }
    ArrayFree(puVar1);
  }
  return (undefined4 *)0x0;
}

/* ArrayCopyOnto @ 0x0804aa80, 124 bytes */
undefined4 * ArrayCopyOnto(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  void *__dest;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  if (((int)param_1[3] < (int)param_2[3]) &&
     (iVar3 = ArrayResize((int)param_1,param_2[3]), iVar3 == 0)) {
    param_1 = (undefined4 *)0x0;
  }
  else {
    uVar1 = param_1[6];
    __dest = (void *)param_1[5];
    puVar4 = param_2;
    puVar5 = param_1;
    for (iVar3 = 0xb; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    iVar3 = param_2[3];
    param_1[6] = uVar1;
    iVar2 = param_2[1];
    param_1[5] = __dest;
    memcpy(__dest,(void *)param_2[5],iVar2 * iVar3);
    puVar4 = (undefined4 *)param_2[6];
    puVar5 = (undefined4 *)param_1[6];
    for (iVar3 = (param_2[3] & 0xfffffff) << 2; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
  }
  return param_1;
}

/* ArrayFree @ 0x0804ab00, 68 bytes */
undefined4 ArrayFree(void *param_1)

{
  undefined4 in_EAX;
  undefined4 extraout_EAX;
  
  if (param_1 != (void *)0x0) {
    if (*(void **)((int)param_1 + 0x14) != (void *)0x0) {
      free(*(void **)((int)param_1 + 0x14));
    }
    if (*(void **)((int)param_1 + 0x18) != (void *)0x0) {
      free(*(void **)((int)param_1 + 0x18));
    }
    free(param_1);
    return extraout_EAX;
  }
  return in_EAX;
}

/* ArrayHasSpace @ 0x0804ab50, 16 bytes */
bool ArrayHasSpace(int param_1)

{
  return *(int *)(param_1 + 8) < *(int *)(param_1 + 0xc);
}

/* ArrayAdd @ 0x0804ab60, 129 bytes */
int ArrayAdd(int param_1,void *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  void *__dest;
  int iVar3;
  
  iVar2 = ArrayFindEmpty(param_1);
  if (iVar2 != -1) {
    __dest = (void *)ArrayAccessUnsafe(param_1,iVar2);
    memcpy(__dest,param_2,*(size_t *)(param_1 + 4));
    iVar1 = *(int *)(param_1 + 0x18);
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
    iVar3 = iVar2 * 0x10;
    *(undefined4 *)(iVar1 + iVar3) = 1;
    *(undefined4 *)(iVar1 + 4 + iVar3) = *(undefined4 *)(param_1 + 0x10);
    *(undefined4 *)(iVar1 + 8 + iVar3) = param_3;
    *(undefined4 *)(iVar1 + 0xc + iVar3) = param_4;
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
    if (iVar2 < *(int *)(param_1 + 0x24)) {
      *(int *)(param_1 + 0x24) = iVar2;
    }
    if (*(int *)(param_1 + 0x28) < iVar2) {
      *(int *)(param_1 + 0x28) = iVar2;
    }
  }
  return iVar2;
}

/* ArrayAddUnique @ 0x0804abf0, 94 bytes */
uint ArrayAddUnique(int param_1,void *param_2,int param_3,int param_4)

{
  uint uVar1;
  void *__dest;
  
  uVar1 = ArrayFind(param_1,param_3,param_4);
  if (uVar1 == 0xffffffff) {
    uVar1 = ArrayAdd(param_1,param_2,param_3,param_4);
  }
  else {
    __dest = (void *)ArrayAccessUnsafe(param_1,uVar1);
    memcpy(__dest,param_2,*(size_t *)(param_1 + 4));
  }
  return uVar1;
}

/* ArrayAddResize @ 0x0804ac50, 95 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
int ArrayAddResize(int param_1,void *param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  
  bVar1 = ArrayHasSpace(param_1);
  if (GHIDRA_ZEXT8(bVar1) == 0) {
    iVar2 = ArrayResize(param_1,*(int *)(param_1 + 0xc) + 1);
    if (iVar2 == 0) {
      return -1;
    }
  }
  iVar2 = ArrayAdd(param_1,param_2,param_3,param_4);
  return iVar2;
}

/* ArrayAddUniqueResize @ 0x0804acb0, 95 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
uint ArrayAddUniqueResize(int param_1,void *param_2,int param_3,int param_4)

{
  bool bVar1;
  undefined3 extraout_var;
  int iVar2;
  uint uVar3;
  
  bVar1 = ArrayHasSpace(param_1);
  if (GHIDRA_ZEXT8(bVar1) == 0) {
    iVar2 = ArrayResize(param_1,*(int *)(param_1 + 0xc) + 1);
    if (iVar2 == 0) {
      return 0xffffffff;
    }
  }
  uVar3 = ArrayAddUnique(param_1,param_2,param_3,param_4);
  return uVar3;
}

/* ArrayDelete @ 0x0804ad10, 139 bytes */
void ArrayDelete(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0x18);
  *(undefined4 *)(iVar1 + param_2 * 0x10) = 0;
  iVar2 = *(int *)(param_1 + 8) + -1;
  *(int *)(param_1 + 8) = iVar2;
  if (iVar2 == 0) {
    *(undefined4 *)(param_1 + 0x28) = 0;
    *(undefined4 *)(param_1 + 0x24) = 0;
  }
  else {
    iVar2 = *(int *)(param_1 + 0x24);
    if (param_2 == iVar2) {
      iVar1 = *(int *)(iVar1 + param_2 * 0x10);
      while (iVar1 == 0) {
        iVar2 = iVar2 + 1;
        *(int *)(param_1 + 0x24) = iVar2;
        iVar1 = *(int *)(*(int *)(param_1 + 0x18) + iVar2 * 0x10);
      }
    }
    else {
      iVar1 = *(int *)(param_1 + 0x28);
      if (param_2 == iVar1) {
        iVar2 = *(int *)(*(int *)(param_1 + 0x18) + iVar1 * 0x10);
        while (iVar2 == 0) {
          iVar1 = iVar1 + -1;
          *(int *)(param_1 + 0x28) = iVar1;
          iVar2 = *(int *)(*(int *)(param_1 + 0x18) + iVar1 * 0x10);
        }
      }
    }
  }
  return;
}

/* ArrayClear @ 0x0804ada0, 66 bytes */
void ArrayClear(int param_1)

{
  memset(*(void **)(param_1 + 0x18),0,*(int *)(param_1 + 0xc) << 4);
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  return;
}

/* ArrayResize @ 0x0804adf0, 172 bytes */
undefined4 ArrayResize(int param_1,int param_2)

{
  int iVar1;
  void *pvVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  iVar1 = *(int *)(param_1 + 0xc);
  if (iVar1 <= param_2) {
    if (param_2 == iVar1) {
      return 1;
    }
    pvVar2 = realloc(*(void **)(param_1 + 0x14),param_2 * *(int *)(param_1 + 4));
    if (pvVar2 != (void *)0x0) {
      *(void **)(param_1 + 0x14) = pvVar2;
      pvVar2 = realloc(*(void **)(param_1 + 0x18),param_2 * 0x10 + 0x10);
      if (pvVar2 != (void *)0x0) {
        *(void **)(param_1 + 0x18) = pvVar2;
        memset((void *)(iVar1 * *(int *)(param_1 + 4) + *(int *)(param_1 + 0x14)),0,
               (param_2 - iVar1) * *(int *)(param_1 + 4));
        puVar4 = (undefined4 *)(iVar1 * 0x10 + *(int *)(param_1 + 0x18));
        for (uVar3 = (param_2 - iVar1) * 0x10 + 0x10U >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
          *puVar4 = 0;
          puVar4 = puVar4 + 1;
        }
        *(int *)(param_1 + 0xc) = param_2;
        return 1;
      }
    }
  }
  return 0;
}

/* ArrayFindEmpty @ 0x0804aea0, 119 bytes */
int ArrayFindEmpty(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_1 + 8);
  if (iVar1 < *(int *)(param_1 + 0xc)) {
    if (iVar1 == 0) {
      return 0;
    }
    iVar2 = *(int *)(param_1 + 0x28);
    iVar3 = *(int *)(param_1 + 0x24);
    if (iVar1 < (iVar2 - iVar3) + 1) {
      iVar3 = iVar3 + 1;
      iVar1 = *(int *)(*(int *)(param_1 + 0x18) + iVar3 * 0x10);
      while (iVar1 != 0) {
        iVar3 = iVar3 + 1;
        iVar1 = *(int *)(*(int *)(param_1 + 0x18) + iVar3 * 0x10);
      }
      return iVar3;
    }
    if (0 < iVar3) {
      return iVar3 + -1;
    }
    if (iVar2 < *(int *)(param_1 + 0xc) + -1) {
      return iVar2 + 1;
    }
  }
  return -1;
}

/* ArrayAccessSafe @ 0x0804af20, 32 bytes */
int ArrayAccessSafe(int param_1,int param_2)

{
  if ((-1 < param_2) && (param_2 < *(int *)(param_1 + 8))) {
    return param_2 * *(int *)(param_1 + 4) + *(int *)(param_1 + 0x14);
  }
  return 0;
}

/* ArrayFind @ 0x0804af40, 153 bytes */
uint ArrayFind(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  
  iVar1 = *(int *)(param_1 + 0x28);
  if (*(int *)(param_1 + 8) == 0) {
    uVar3 = 0xffffffff;
  }
  else {
    iVar2 = *(int *)(param_1 + 0x24);
    if ((iVar1 - iVar2) + 1 == *(int *)(param_1 + 8)) {
      uVar3 = iVar2 - 1;
      iVar4 = *(int *)(param_1 + 0x18);
      iVar2 = iVar4 + 0x10 + iVar1 * 0x10;
      *(int *)(iVar2 + 8) = param_2;
      *(int *)(iVar2 + 0xc) = param_3;
      iVar2 = uVar3 * 0x10 + iVar4;
      do {
        do {
          iVar4 = iVar2;
          uVar3 = uVar3 + 1;
          iVar2 = iVar4 + 0x10;
        } while (*(int *)(iVar4 + 0x18) != param_2);
      } while (*(int *)(iVar4 + 0x1c) != param_3);
    }
    else {
      uVar3 = iVar2 - 1;
      iVar4 = *(int *)(param_1 + 0x18);
      iVar2 = iVar4 + 0x10 + iVar1 * 0x10;
      *(int *)(iVar2 + 8) = param_2;
      *(int *)(iVar2 + 0xc) = param_3;
      piVar5 = (int *)(uVar3 * 0x10 + iVar4);
      do {
        do {
          piVar6 = piVar5;
          piVar5 = piVar6 + 4;
          uVar3 = uVar3 + 1;
        } while (piVar6[6] != param_2);
      } while ((piVar6[7] != param_3) || (*piVar5 == 0));
    }
    uVar3 = uVar3 | ((int)uVar3 <= iVar1) - 1;
  }
  return uVar3;
}

/* ArrayAccessGrpItem @ 0x0804afe0, 54 bytes */
int ArrayAccessGrpItem(int param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = ArrayFind(param_1,param_2,param_3);
  if (uVar1 == 0xffffffff) {
    iVar2 = 0;
  }
  else {
    iVar2 = uVar1 * *(int *)(param_1 + 4) + *(int *)(param_1 + 0x14);
  }
  return iVar2;
}

/* ArrayIdxToGrp @ 0x0804b020, 19 bytes */
undefined4 ArrayIdxToGrp(int param_1,int param_2)

{
  return *(undefined4 *)(*(int *)(param_1 + 0x18) + 8 + param_2 * 0x10);
}

/* ArrayIdxToItem @ 0x0804b040, 19 bytes */
undefined4 ArrayIdxToItem(int param_1,int param_2)

{
  return *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xc + param_2 * 0x10);
}

/* ArrayScanFirst @ 0x0804b060, 41 bytes */
int ArrayScanFirst(int param_1)

{
  if (*(int *)(param_1 + 8) == 0) {
    return 0;
  }
  *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x20) = 1;
  return *(int *)(param_1 + 0x24) * *(int *)(param_1 + 4) + *(int *)(param_1 + 0x14);
}

/* ArrayScanNext @ 0x0804b090, 58 bytes */
int ArrayScanNext(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x1c);
  if (iVar1 < *(int *)(param_1 + 0x28)) {
    do {
      iVar1 = iVar1 + 1;
    } while (*(int *)(*(int *)(param_1 + 0x18) + iVar1 * 0x10) == 0);
    *(int *)(param_1 + 0x1c) = iVar1;
    *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + 1;
    iVar1 = iVar1 * *(int *)(param_1 + 4) + *(int *)(param_1 + 0x14);
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

/* ArrayAccessUnsafe @ 0x0804b0d0, 20 bytes */
int ArrayAccessUnsafe(int param_1,int param_2)

{
  return *(int *)(param_1 + 4) * param_2 + *(int *)(param_1 + 0x14);
}

