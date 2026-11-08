/*
 * spr-lib.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08058610-0x0805bf12, 106 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* SpriteInit @ 0x08058610, 203 bytes */
bool SpriteInit(int *param_1,int param_2,void *param_3,size_t param_4,int param_5,int param_6,
               int param_7,int param_8,int param_9,int param_10)

{
  void *__dest;
  int iVar1;
  int *piVar2;
  
  piVar2 = param_1;
  for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar2 = 0;
    piVar2 = piVar2 + 1;
  }
  param_1[0xc] = -1;
  param_1[7] = param_2;
  if (param_5 == 0) {
    param_1[9] = (int)param_3;
  }
  else {
    __dest = calloc(1,param_4);
    param_1[9] = (int)__dest;
    if (__dest == (void *)0x0) {
      return false;
    }
    param_1[6] = 1;
    memcpy(__dest,param_3,param_4);
  }
  param_1[8] = param_4;
  *param_1 = param_6;
  param_1[4] = param_8;
  param_1[1] = param_7;
  if (param_8 < 9) {
    param_1[5] = 1 << ((byte)param_8 & 0x1f);
  }
  param_1[2] = param_9;
  param_1[3] = param_10;
  iVar1 = SpriteInitLine(param_1,(void *)0x0);
  return iVar1 != 0;
}

/* SpriteDeInit @ 0x080586e0, 90 bytes */
void SpriteDeInit(int param_1)

{
  int *__ptr;
  
  if (param_1 != 0) {
    if ((*(int *)(param_1 + 0x18) != 0) && (__ptr = *(int **)(param_1 + 0x24), __ptr != (int *)0x0))
    {
      if (*(int *)(param_1 + 0x1c) == 1) {
        destroy_bitmap(__ptr);
      }
      else {
        free(__ptr);
      }
    }
    if ((*(int *)(param_1 + 0x28) != 0) && (*(void **)(param_1 + 0x2c) != (void *)0x0)) {
      free(*(void **)(param_1 + 0x2c));
      return;
    }
  }
  return;
}

/* SpriteCopy @ 0x08058740, 195 bytes */
undefined4 SpriteCopy(undefined4 *param_1,undefined4 *param_2,int param_3)

{
  void *__dest;
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  puVar1 = param_2;
  puVar4 = param_1;
  for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar4 = puVar4 + 1;
  }
  param_1[10] = 0;
  param_1[6] = 0;
  if (param_3 != 0) {
    __dest = calloc(1,param_2[8]);
    param_1[9] = __dest;
    if (__dest == (void *)0x0) {
      return 0;
    }
    memcpy(__dest,(void *)param_2[9],param_2[8]);
    param_1[6] = 1;
    if (param_1[0xb] != 0) {
      puVar1 = calloc(4,param_2[1]);
      param_1[0xb] = puVar1;
      if (puVar1 == (undefined4 *)0x0) {
        SpriteDeInit((int)param_1);
        return 0;
      }
      puVar4 = (undefined4 *)param_2[0xb];
      for (uVar3 = param_2[1] & 0x3fffffff; uVar3 != 0; uVar3 = uVar3 - 1) {
        *puVar1 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar1 = puVar1 + 1;
      }
      param_1[10] = 1;
    }
  }
  return 1;
}

/* SpriteInitLine @ 0x08058810, 105 bytes */
int SpriteInitLine(int *param_1,void *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  if (param_1[0xb] == 0) {
    if (param_2 == (void *)0x0) {
      param_2 = calloc(4,param_1[1]);
      if (param_2 == (void *)0x0) goto LAB_0805883e;
      param_1[10] = 1;
    }
    iVar2 = ColDepthToBytesPerPixel(param_1[4]);
    iVar1 = *param_1;
    iVar3 = 0;
    if (0 < param_1[1]) {
      do {
        *(int *)((int)param_2 + iVar3 * 4) = iVar4;
        iVar3 = iVar3 + 1;
        iVar4 = iVar4 + iVar2 * iVar1;
      } while (iVar3 < param_1[1]);
    }
    param_1[0xb] = (int)param_2;
    iVar4 = param_1[1];
  }
  else {
LAB_0805883e:
    iVar4 = 0;
  }
  return iVar4;
}

/* SpriteUsePal @ 0x08058880, 80 bytes */
undefined4 SpriteUsePal(int param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = ArrayFind(*(int *)(param_2 + 8),param_3,param_4);
  if ((uVar1 == 0xffffffff) ||
     (*(int *)(uVar1 * *(int *)(*(int *)(param_2 + 8) + 4) + *(int *)(*(int *)(param_2 + 8) + 0x14))
      != *(int *)(param_1 + 0x14))) {
    uVar2 = 0;
  }
  else {
    *(uint *)(param_1 + 0x30) = uVar1;
    uVar2 = 1;
  }
  return uVar2;
}

/* SpriteSetAxis @ 0x080588d0, 19 bytes */
void SpriteSetAxis(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0xc) = param_3;
  *(undefined4 *)(param_1 + 8) = param_2;
  return;
}

/* SpriteArrayNew @ 0x080588f0, 16 bytes */
void SpriteArrayNew(void)

{
  SpriteArrayNewSize(0,0);
  return;
}

/* SpriteArrayNewSize @ 0x08058900, 93 bytes */
undefined4 * SpriteArrayNewSize(size_t param_1,size_t param_2)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = (undefined4 *)ecalloc(1,0x1c);
  if (puVar1 != (undefined4 *)0x0) {
    if (0 < (int)param_1) {
      puVar2 = ArrayNew(param_1,0x34,0);
      *puVar1 = puVar2;
      if (puVar2 == (undefined4 *)0x0) {
        return (undefined4 *)0x0;
      }
    }
    if ((int)param_2 < 1) {
      return puVar1;
    }
    puVar2 = ArrayNew(param_2,0x25c,0);
    puVar1[2] = puVar2;
    if (puVar2 != (undefined4 *)0x0) {
      return puVar1;
    }
  }
  return (undefined4 *)0x0;
}

/* SpriteArrayNewInstance @ 0x08058960, 191 bytes */
int * SpriteArrayNewInstance(int *param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  int *local_14;
  
  piVar2 = (int *)ecalloc(1,0x1c);
  if (piVar2 == (int *)0x0) {
    piVar2 = (int *)0x0;
  }
  else {
    local_14 = (int *)param_1[3];
    if (local_14 == (int *)0x0) {
      local_14 = param_1;
    }
    piVar5 = param_1;
    piVar6 = piVar2;
    for (iVar4 = 7; iVar4 != 0; iVar4 = iVar4 + -1) {
      *piVar6 = *piVar5;
      piVar5 = piVar5 + 1;
      piVar6 = piVar6 + 1;
    }
    piVar2[2] = 0;
    piVar2[3] = (int)local_14;
    puVar3 = (undefined4 *)param_1[2];
    piVar2[4] = 0;
    if (puVar3 != (undefined4 *)0x0) {
      puVar3 = ArrayCopy(puVar3);
      piVar2[2] = (int)puVar3;
      if (puVar3 == (undefined4 *)0x0) {
        SpriteArrayFree(piVar2);
        return (int *)0x0;
      }
      iVar4 = ArrayScanFirst((int)puVar3);
      while (iVar4 != 0) {
        iVar1 = piVar2[2];
        *(undefined4 *)(iVar4 + 4) = 0;
        iVar4 = ArrayScanNext(iVar1);
      }
    }
    local_14[4] = local_14[4] + 1;
  }
  return piVar2;
}

/* SpriteArrayNewInstanceOnto @ 0x08058a20, 207 bytes */
int * SpriteArrayNewInstanceOnto(int *param_1,int *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int *local_14;
  
  if (param_1[4] < 1) {
    local_14 = (int *)param_2[3];
    if (local_14 == (int *)0x0) {
      local_14 = param_2;
    }
    iVar1 = SpriteArrayClear(param_1);
    if (iVar1 != 0) {
      if ((void *)*param_1 != (void *)0x0) {
        ArrayFree((void *)*param_1);
        *param_1 = 0;
      }
      iVar1 = param_1[2];
      piVar4 = param_2;
      piVar5 = param_1;
      for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
        *piVar5 = *piVar4;
        piVar4 = piVar4 + 1;
        piVar5 = piVar5 + 1;
      }
      param_1[2] = iVar1;
      puVar2 = (undefined4 *)param_2[2];
      param_1[3] = (int)local_14;
      param_1[4] = 0;
      if (puVar2 != (undefined4 *)0x0) {
        puVar2 = ArrayCopyOnto((undefined4 *)param_1[2],puVar2);
        if (puVar2 == (undefined4 *)0x0) {
          return (int *)0x0;
        }
        iVar1 = ArrayScanFirst(param_1[2]);
        while (iVar1 != 0) {
          iVar3 = param_1[2];
          *(undefined4 *)(iVar1 + 4) = 0;
          iVar1 = ArrayScanNext(iVar3);
        }
      }
      local_14[4] = local_14[4] + 1;
      return param_1;
    }
  }
  return (int *)0x0;
}

/* SpriteArrayAddSprite @ 0x08058af0, 76 bytes */
uint SpriteArrayAddSprite(int *param_1,void *param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  int iVar2;
  
  if (*param_1 == 0) {
    puVar1 = ArrayNew(1,0x34,0);
    *param_1 = (int)puVar1;
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
  }
  iVar2 = ArrayAddResize(*param_1,param_2,param_3,param_4);
  return (uint)(iVar2 != -1);
}

/* SpriteArrayAddPal @ 0x08058b40, 87 bytes */
uint SpriteArrayAddPal(int param_1,void *param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 8) == 0) {
    puVar1 = ArrayNew(1,0x25c,0);
    *(undefined4 **)(param_1 + 8) = puVar1;
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
  }
  iVar2 = ArrayAddResize(*(int *)(param_1 + 8),param_2,param_3,param_4);
  return (uint)(iVar2 != -1);
}

/* SpriteArrayNumImages @ 0x08058ba0, 10 bytes */
undefined4 SpriteArrayNumImages(int *param_1)

{
  return *(undefined4 *)(*param_1 + 8);
}

/* SpriteArrayNumPals @ 0x08058bb0, 11 bytes */
undefined4 SpriteArrayNumPals(int param_1)

{
  return *(undefined4 *)(*(int *)(param_1 + 8) + 8);
}

/* SpriteArrayFree @ 0x08058bc0, 208 bytes */
undefined4 SpriteArrayFree(int *param_1)

{
  int iVar1;
  
  if (param_1 != (int *)0x0) {
    if (0 < param_1[4]) {
      return 0;
    }
    if (param_1[2] != 0) {
      iVar1 = ArrayScanFirst(param_1[2]);
      while (iVar1 != 0) {
        EBPalDeInit(iVar1);
        iVar1 = ArrayScanNext(param_1[2]);
      }
      ArrayFree((void *)param_1[2]);
    }
    iVar1 = param_1[3];
    if (iVar1 == 0) {
      if (*param_1 != 0) {
        iVar1 = ArrayScanFirst(*param_1);
        while (iVar1 != 0) {
          SpriteDeInit(iVar1);
          iVar1 = ArrayScanNext(*param_1);
        }
        ArrayFree((void *)*param_1);
      }
      if ((void *)param_1[1] != (void *)0x0) {
        free((void *)param_1[1]);
      }
      iVar1 = param_1[3];
    }
    if (iVar1 != 0) {
      *(int *)(iVar1 + 0x10) = *(int *)(iVar1 + 0x10) + -1;
    }
    free(param_1);
  }
  return 1;
}

/* SpriteArrayClear @ 0x08058c90, 219 bytes */
undefined4 SpriteArrayClear(int *param_1)

{
  int iVar1;
  
  if (param_1 == (int *)0x0) {
    return 1;
  }
  if (0 < param_1[4]) {
    return 0;
  }
  if (param_1[2] != 0) {
    iVar1 = ArrayScanFirst(param_1[2]);
    while (iVar1 != 0) {
      EBPalDeInit(iVar1);
      iVar1 = ArrayScanNext(param_1[2]);
    }
    ArrayClear(param_1[2]);
  }
  if (param_1[3] == 0) {
    if (*param_1 != 0) {
      iVar1 = ArrayScanFirst(*param_1);
      while (iVar1 != 0) {
        SpriteDeInit(iVar1);
        iVar1 = ArrayScanNext(*param_1);
      }
      ArrayClear(*param_1);
    }
    if ((void *)param_1[1] == (void *)0x0) goto LAB_08058d4d;
    free((void *)param_1[1]);
  }
  else {
    *param_1 = 0;
  }
  param_1[1] = 0;
LAB_08058d4d:
  iVar1 = param_1[3];
  if (iVar1 != 0) {
    *(int *)(iVar1 + 0x10) = *(int *)(iVar1 + 0x10) + -1;
  }
  param_1[3] = 0;
  return 1;
}

/* SpriteArrayGetNum @ 0x08058d70, 15 bytes */
uint SpriteArrayGetNum(int *param_1,int param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = ArrayFind(*param_1,param_2,param_3);
  return uVar1;
}

/* SpriteArrayPalGetNum @ 0x08058d80, 16 bytes */
uint SpriteArrayPalGetNum(int param_1,int param_2,int param_3)

{
  uint uVar1;
  
  uVar1 = ArrayFind(*(int *)(param_1 + 8),param_2,param_3);
  return uVar1;
}

/* SpriteArrayAccess @ 0x08058d90, 22 bytes */
int SpriteArrayAccess(int *param_1,int param_2)

{
  return *(int *)(*param_1 + 4) * param_2 + *(int *)(*param_1 + 0x14);
}

/* SpriteArrayAccessGrpItem @ 0x08058db0, 15 bytes */
undefined4 SpriteArrayAccessGrpItem(int *param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  
  uVar1 = ArrayAccessGrpItem(*param_1,param_2,param_3);
  return uVar1;
}

/* SpriteArrayPalAccess @ 0x08058dc0, 23 bytes */
int SpriteArrayPalAccess(int param_1,int param_2)

{
  return *(int *)(*(int *)(param_1 + 8) + 4) * param_2 + *(int *)(*(int *)(param_1 + 8) + 0x14);
}

/* SpriteArrayPalAccessGrpItem @ 0x08058de0, 16 bytes */
void SpriteArrayPalAccessGrpItem(int param_1,int param_2,int param_3)

{
  ArrayAccessGrpItem(*(int *)(param_1 + 8),param_2,param_3);
  return;
}

/* SpriteArrayPalUpdateAndAccess @ 0x08058df0, 39 bytes */
int * SpriteArrayPalUpdateAndAccess(int param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = (int *)(param_2 * *(int *)(*(int *)(param_1 + 8) + 4) +
                  *(int *)(*(int *)(param_1 + 8) + 0x14));
  EBPalUpdate(piVar1);
  return piVar1;
}

/* SpriteArrayPalRemapFromRoot @ 0x08058e20, 73 bytes */
bool SpriteArrayPalRemapFromRoot(int param_1,int param_2,int param_3)

{
  int *piVar1;
  int *piVar2;
  bool bVar3;
  
  bVar3 = *(int *)(param_1 + 0xc) != 0;
  if (bVar3) {
    piVar1 = (int *)SpriteArrayPalAccess(*(int *)(param_1 + 0xc),param_3);
    piVar2 = (int *)SpriteArrayPalAccess(param_1,param_2);
    EBPalCopy(piVar2,piVar1,0);
  }
  return bVar3;
}

/* SpriteArrayPalRemapFromRootGrpItem @ 0x08058e70, 106 bytes */
bool SpriteArrayPalRemapFromRootGrpItem
               (int *param_1,int param_2,int param_3,int param_4,int param_5)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  
  if (param_1[3] != 0) {
    iVar2 = SpriteArrayGetNum(param_1,param_2,param_3);
    iVar3 = SpriteArrayGetNum(param_1,param_4,param_5);
    if ((iVar2 != -1) && (iVar3 != -1)) {
      bVar1 = SpriteArrayPalRemapFromRoot((int)param_1,iVar2,iVar3);
      return bVar1;
    }
  }
  return false;
}

/* ColDepthToBytesPerPixel @ 0x08058ee0, 11 bytes */
int ColDepthToBytesPerPixel(int param_1)

{
  return param_1 + 7 >> 3;
}

/* SpriteDecompGetData @ 0x08058ef0, 60 bytes */
undefined4 SpriteDecompGetData(int *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  uVar2 = 0;
  if (iVar1 != 0) {
    if (*(int *)(iVar1 + 0x1c) == 0) {
      uVar2 = *(undefined4 *)(iVar1 + 0x24);
    }
    else if (*(int *)(iVar1 + 0x1c) == 1) {
      uVar2 = *(undefined4 *)(*(int *)(iVar1 + 0x24) + 0x28);
    }
  }
  return uVar2;
}

/* SpriteDecompGetAndLockData @ 0x08058f30, 5 bytes
 * REVIEW: calls-missing-in-pid:SpriteArrayAccess */
undefined4 SpriteDecompGetAndLockData(int *param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = SpriteDecompGetData(param_1,param_2);
  return uVar1;
}

/* SpriteDecompUnlockData @ 0x08058f40, 1 bytes */
undefined4 SpriteDecompUnlockData(void)

{
  undefined4 in_EAX;
  
  return in_EAX;
}

/* W_PutSurface @ 0x08058f50, 1 bytes */
void W_PutSurface(void)

{
  return;
}

/* W_PutSprite @ 0x08058f60, 136 bytes */
undefined4 W_PutSprite(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 extraout_EAX;
  undefined4 extraout_EAX_00;
  
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) && (0xe < V_ColDepth)) {
    iVar1 = SpriteArrayAccess(param_1,param_2);
    if (*(int *)(iVar1 + 0x10) == 8) {
      W_PutSprite8to16(param_1,param_2,param_3,param_4);
      return extraout_EAX;
    }
    W_PutSurface();
    return extraout_EAX_00;
  }
  return V_ColDepth;
}

/* W_PutSpriteA @ 0x08058ff0, 76 bytes */
void W_PutSpriteA(int *param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  
  if ((-1 < param_2) && (-1 < param_3)) {
    iVar1 = SpriteArrayGetNum(param_1,param_2,param_3);
    if (iVar1 != -1) {
      W_PutSprite(param_1,iVar1,param_4,param_5);
      return;
    }
  }
  return;
}

/* W_PutSpriteAMirH @ 0x08059040, 76 bytes */
void W_PutSpriteAMirH(int *param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  
  if ((-1 < param_2) && (-1 < param_3)) {
    iVar1 = SpriteArrayGetNum(param_1,param_2,param_3);
    if (iVar1 != -1) {
      W_PutSpriteMirH(param_1,iVar1,param_4,param_5);
      return;
    }
  }
  return;
}

/* W_PutSpriteAPal @ 0x08059090, 98 bytes */
void W_PutSpriteAPal(int *param_1,int param_2,int param_3,undefined4 param_4,int param_5,int param_6
                    )

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if ((-1 < param_2) && (-1 < param_3)) {
    iVar2 = SpriteArrayGetNum(param_1,param_2,param_3);
    if (iVar2 != -1) {
      iVar3 = SpriteArrayAccess(param_1,iVar2);
      uVar1 = *(undefined4 *)(iVar3 + 0x30);
      *(undefined4 *)(iVar3 + 0x30) = param_4;
      W_PutSprite(param_1,iVar2,param_5,param_6);
      *(undefined4 *)(iVar3 + 0x30) = uVar1;
    }
  }
  return;
}

/* W_PutSpriteAMirHPal @ 0x08059100, 98 bytes */
void W_PutSpriteAMirHPal(int *param_1,int param_2,int param_3,undefined4 param_4,int param_5,
                        int param_6)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if ((-1 < param_2) && (-1 < param_3)) {
    iVar2 = SpriteArrayGetNum(param_1,param_2,param_3);
    if (iVar2 != -1) {
      iVar3 = SpriteArrayAccess(param_1,iVar2);
      uVar1 = *(undefined4 *)(iVar3 + 0x30);
      *(undefined4 *)(iVar3 + 0x30) = param_4;
      W_PutSpriteMirH(param_1,iVar2,param_5,param_6);
      *(undefined4 *)(iVar3 + 0x30) = uVar1;
    }
  }
  return;
}

/* W_PutSpriteFlat @ 0x08059170, 92 bytes */
void W_PutSpriteFlat(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  if ((V_ColDepth < 0x11) && (0xe < V_ColDepth)) {
    iVar1 = SpriteArrayAccess(param_1,param_2);
    if (*(int *)(iVar1 + 0x10) == 8) {
      W_PutSpriteFlat8to16(param_1,param_2,param_3,param_4);
      return;
    }
  }
  return;
}

/* W_PutSpriteMirH @ 0x080591d0, 92 bytes */
undefined4 W_PutSpriteMirH(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 extraout_EAX;
  
  iVar1 = V_ColDepth;
  if ((V_ColDepth < 0x11) && (0xe < V_ColDepth)) {
    iVar1 = SpriteArrayAccess(param_1,param_2);
    if (*(int *)(iVar1 + 0x10) == 8) {
      W_PutSpriteMirH8to16(param_1,param_2,param_3,param_4);
      return extraout_EAX;
    }
  }
  return iVar1;
}

/* W_PutSpriteMirV @ 0x08059230, 92 bytes */
undefined4 W_PutSpriteMirV(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 extraout_EAX;
  
  iVar1 = V_ColDepth;
  if ((V_ColDepth < 0x11) && (0xe < V_ColDepth)) {
    iVar1 = SpriteArrayAccess(param_1,param_2);
    if (*(int *)(iVar1 + 0x10) == 8) {
      W_PutSpriteMirV8to16(param_1,param_2,param_3,param_4);
      return extraout_EAX;
    }
  }
  return iVar1;
}

/* W_PutSpriteMirHV @ 0x08059290, 92 bytes */
undefined4 W_PutSpriteMirHV(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 extraout_EAX;
  
  iVar1 = V_ColDepth;
  if ((V_ColDepth < 0x11) && (0xe < V_ColDepth)) {
    iVar1 = SpriteArrayAccess(param_1,param_2);
    if (*(int *)(iVar1 + 0x10) == 8) {
      W_PutSpriteMirHV8to16(param_1,param_2,param_3,param_4);
      return extraout_EAX;
    }
  }
  return iVar1;
}

/* W_PutSpriteShadow @ 0x080592f0, 152 bytes */
void W_PutSpriteShadow(int *param_1,int param_2,int param_3,int param_4,undefined2 param_5)

{
  int iVar1;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((V_ColDepth < 0x11) && (0xe < V_ColDepth)) {
    if (*(int *)(iVar1 + 0x10) == 8) {
      W_PutSpriteShadow8to16(param_1,param_2,param_3,param_4,param_5);
      return;
    }
    if (*(int *)(iVar1 + 0x10) == 0x10) {
      W_PutSpriteShadow16();
      return;
    }
  }
  return;
}

/* W_ScaleSprite @ 0x08059390, 239 bytes
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
void W_ScaleSprite(int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  int iVar1;
  int *piVar2;
  
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (iVar1 = SpriteArrayAccess(param_1,param_2), *(int *)(iVar1 + 0x10) == 8)
      ))) {
    W_ScaleSprite8to16(param_1,param_2,param_3,param_4,param_5,param_6);
    return;
  }
  piVar2 = (int *)SpriteArrayAccess(param_1,param_2);
  if (((float)*piVar2 == param_5) &&
     (iVar1 = SpriteArrayAccess(param_1,param_2), (float10)*(int *)(iVar1 + 4) == param_6)) {
    W_PutSprite(param_1,param_2,(int)GHIDRA_FIST32(param_3),(int)GHIDRA_FIST32(param_4));
  }
  return;
}

/* W_ScaleSpriteFlat @ 0x08059480, 124 bytes */
void W_ScaleSpriteFlat(int *param_1,int param_2,float param_3,float param_4,float param_5,
                      float param_6)

{
  int iVar1;
  
  if ((V_ColDepth < 0x11) && (0xe < V_ColDepth)) {
    iVar1 = SpriteArrayAccess(param_1,param_2);
    if (*(int *)(iVar1 + 0x10) == 8) {
      W_ScaleSpriteFlat8to16(param_1,param_2,param_3,param_4,param_5,param_6);
      return;
    }
  }
  return;
}

/* W_ScaleSpriteMirH @ 0x08059500, 136 bytes */
void W_ScaleSpriteMirH(int *param_1,int param_2,float param_3,float param_4,float param_5,
                      float param_6)

{
  int iVar1;
  
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) && (0xe < V_ColDepth)) {
    iVar1 = SpriteArrayAccess(param_1,param_2);
    if (*(int *)(iVar1 + 0x10) == 8) {
      W_ScaleSpriteMirH8to16(param_1,param_2,param_3,param_4,param_5,param_6);
      return;
    }
  }
  return;
}

/* W_ScaleSpriteMirV @ 0x08059590, 136 bytes */
void W_ScaleSpriteMirV(int *param_1,int param_2,float param_3,float param_4,float param_5,
                      float param_6)

{
  int iVar1;
  
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) && (0xe < V_ColDepth)) {
    iVar1 = SpriteArrayAccess(param_1,param_2);
    if (*(int *)(iVar1 + 0x10) == 8) {
      W_ScaleSpriteMirV8to16(param_1,param_2,param_3,param_4,param_5,param_6);
      return;
    }
  }
  return;
}

/* W_ScaleSpriteMirHV @ 0x08059620, 136 bytes */
void W_ScaleSpriteMirHV(int *param_1,int param_2,float param_3,float param_4,float param_5,
                       float param_6)

{
  int iVar1;
  
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) && (0xe < V_ColDepth)) {
    iVar1 = SpriteArrayAccess(param_1,param_2);
    if (*(int *)(iVar1 + 0x10) == 8) {
      W_ScaleSpriteMirHV8to16(param_1,param_2,param_3,param_4,param_5,param_6);
      return;
    }
  }
  return;
}

/* W_ScaleSprite_S @ 0x080596b0, 328 bytes
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
undefined4
W_ScaleSprite_S(int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  int *piVar1;
  int iVar2;
  undefined2 uVar4;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined4 uVar3;
  undefined2 extraout_var_01;
  undefined4 extraout_EAX;
  float local_2c;
  float local_28;
  
  piVar1 = (int *)SpriteArrayAccess(param_1,param_2);
  local_28 = (float)*piVar1 * param_5;
  iVar2 = SpriteArrayAccess(param_1,param_2);
  local_2c = (float10)*(int *)(iVar2 + 4) * param_6;
  uVar4 = (undefined2)((uint)iVar2 >> 0x10);
  if (0.0 < param_6) {
    if (0.0 < param_5) {
      W_ScaleSprite(param_1,param_2,param_3,param_4,local_28,local_2c);
      uVar4 = extraout_var;
    }
    if (param_5 < 0.0) {
      W_ScaleSpriteMirH(param_1,param_2,param_3,param_4,-local_28,local_2c);
      uVar4 = extraout_var_00;
    }
  }
  uVar3 = CONCAT22(uVar4,(ushort)(param_6 < 0.0) << 8 | (ushort)GHIDRA_ISNAN(param_6) << 10 |
                         (ushort)(param_6 == 0.0) << 0xe);
  if (param_6 < 0.0) {
    if (0.0 < param_5) {
      W_ScaleSpriteMirV(param_1,param_2,param_3,param_4,local_28,-local_2c);
      uVar4 = extraout_var_01;
    }
    uVar3 = CONCAT22(uVar4,(ushort)(param_5 < 0.0) << 8 | (ushort)GHIDRA_ISNAN(param_5) << 10 |
                           (ushort)(param_5 == 0.0) << 0xe);
    if (param_5 < 0.0) {
      local_2c = -local_2c;
      local_28 = -local_28;
      W_ScaleSpriteMirHV(param_1,param_2,param_3,param_4,local_28,local_2c);
      return extraout_EAX;
    }
  }
  return uVar3;
}

/* W_ScaleSpriteFlat_S @ 0x08059800, 168 bytes
 * FIXUP: 2 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
void W_ScaleSpriteFlat_S(int *param_1,int param_2,int param_3,int param_4,float param_5,
                        float param_6)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = (int *)SpriteArrayAccess(param_1,param_2);
  iVar1 = *piVar2;
  iVar3 = SpriteArrayAccess(param_1,param_2);
  if ((0.0 < param_6) && (0.0 < param_5)) {
    W_ScaleSpriteFlat(param_1,param_2,(float)param_3,(float)param_4,(float10)iVar1 * param_5,
                      (float10)*(int *)(iVar3 + 4) * param_6);
    return;
  }
  return;
}

/* W_ScaleSpriteMirH_S @ 0x080598b0, 50 bytes */
void W_ScaleSpriteMirH_S(int *param_1,int param_2,int param_3,int param_4,float param_5,
                        float param_6)

{
  W_ScaleSprite_S(param_1,param_2,(float)param_3,(float)param_4,-param_5,param_6);
  return;
}

/* W_ScaleSpriteMirV_S @ 0x080598f0, 42 bytes */
void W_ScaleSpriteMirV_S(int *param_1,int param_2,int param_3,int param_4,float param_5,
                        float param_6)

{
  param_6 = -param_6;
  W_ScaleSprite_S(param_1,param_2,(float)param_3,(float)param_4,param_5,param_6);
  return;
}

/* W_ScaleSpriteMirHV_S @ 0x08059920, 55 bytes */
void W_ScaleSpriteMirHV_S
               (int *param_1,int param_2,int param_3,int param_4,float param_5,float param_6)

{
  param_6 = -param_6;
  W_ScaleSprite_S(param_1,param_2,(float)param_3,(float)param_4,-param_5,param_6);
  return;
}

/* W_RotateSprite @ 0x08059960, 57 bytes */
void W_RotateSprite(int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6
                   ,float param_7)

{
  W_RotateSprite_P(param_1,param_2,param_3,param_4,param_5,param_6,param_7,1.0,1.0);
  return;
}

/* W_RotateSpriteMirH @ 0x080599a0, 57 bytes */
void W_RotateSpriteMirH(int *param_1,int param_2,float param_3,float param_4,float param_5,
                       float param_6,float param_7)

{
  W_RotateSpriteMirH_P(param_1,param_2,param_3,param_4,param_5,param_6,param_7,1.0,1.0);
  return;
}

/* W_RotateSprite_P @ 0x080599e0, 541 bytes
 * FIXUP: untyped (undefined4) <-> float moves kept as bit copies: 0 assignments, 0 calls, 2 returns
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
undefined4
W_RotateSprite_P(int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
                float param_7,float param_8,float param_9)

{
  bool bVar1;
  float10 fVar2;
  int iVar3;
  undefined4 uVar4;
  
  bVar1 = param_6 < 0.0;
  if (bVar1) {
    param_6 = param_6 * -1.0;
    param_5 = 360.0 - param_5;
  }
  if (param_7 < 0.0) {
    fVar2 = param_5 + 180.0;
    bVar1 = !bVar1;
    param_7 = param_7 * -1.0;
    if (360.0 <= fVar2) {
      fVar2 = fVar2 - 360.0;
    }
    param_5 = 360.0 - fVar2;
  }
  if (param_8 < 0.0) {
    param_8 = param_8 * -1.0;
    bVar1 = !bVar1;
  }
  if (param_9 < 0.0) {
    param_5 = param_5 + 180.0;
    bVar1 = !bVar1;
    param_9 = param_9 * -1.0;
    if (360.0 <= param_5) {
      param_5 = param_5 - 360.0;
    }
  }
  iVar3 = V_ColDepth;
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (iVar3 = SpriteArrayAccess(param_1,param_2), *(int *)(iVar3 + 0x10) == 8)
      ))) {
    if (bVar1) {
      uVar4 = W_RotateSpriteMirH8to16_P
                        (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
      return GHIDRA_I2F(uVar4);
    }
    uVar4 = W_RotateSprite8to16_P
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    return GHIDRA_I2F(uVar4);
  }
  return iVar3;
}

/* W_RotateSpriteMirH_P @ 0x08059c00, 41 bytes */
void W_RotateSpriteMirH_P
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7,float param_8,float param_9)

{
  W_RotateSprite_P(param_1,param_2,param_3,param_4,360.0 - param_5,-param_6,param_7,param_8,param_9)
  ;
  return;
}

/* W_PutSpriteTransAdd @ 0x08059c30, 104 bytes */
undefined4 W_PutSpriteTransAdd(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 extraout_EAX;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_PutSpriteTransAdd8to16(param_1,param_2,param_3,param_4);
    return extraout_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransAddMirH @ 0x08059ca0, 104 bytes */
undefined4 W_PutSpriteTransAddMirH(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 extraout_EAX;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_PutSpriteTransAddMirH8to16(param_1,param_2,param_3,param_4);
    return extraout_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransAddMirV @ 0x08059d10, 104 bytes */
undefined4 W_PutSpriteTransAddMirV(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 extraout_EAX;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_PutSpriteTransAddMirV8to16(param_1,param_2,param_3,param_4);
    return extraout_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransAddMirHV @ 0x08059d80, 104 bytes */
undefined4 W_PutSpriteTransAddMirHV(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 extraout_EAX;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_PutSpriteTransAddMirHV8to16(param_1,param_2,param_3,param_4);
    return extraout_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransAddFlip @ 0x08059df0, 156 bytes */
void W_PutSpriteTransAddFlip(int *param_1,int param_2,int param_3,int param_4,int param_5)

{
  if (param_5 == 1) {
    W_PutSpriteTransAddMirH(param_1,param_2,param_3,param_4);
    return;
  }
  if (param_5 < 2) {
    if (param_5 == 0) {
      W_PutSpriteTransAdd(param_1,param_2,param_3,param_4);
      return;
    }
  }
  else {
    if (param_5 == 2) {
      W_PutSpriteTransAddMirV(param_1,param_2,param_3,param_4);
      return;
    }
    if (param_5 == 3) {
      W_PutSpriteTransAddMirHV(param_1,param_2,param_3,param_4);
      return;
    }
  }
  return;
}

/* W_PutSpriteTransAdd_B @ 0x08059e90, 136 bytes */
undefined4
W_PutSpriteTransAdd_B(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  undefined4 extraout_EAX;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_PutSpriteTransAdd8to16_B(param_1,param_2,param_3,param_4,param_5,param_6);
    return extraout_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransAddMirH_B @ 0x08059f20, 136 bytes */
undefined4
W_PutSpriteTransAddMirH_B(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  undefined4 extraout_EAX;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_PutSpriteTransAddMirH8to16_B(param_1,param_2,param_3,param_4,param_5,param_6);
    return extraout_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransAddMirV_B @ 0x08059fb0, 136 bytes */
undefined4
W_PutSpriteTransAddMirV_B(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  undefined4 extraout_EAX;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_PutSpriteTransAddMirV8to16_B(param_1,param_2,param_3,param_4,param_5,param_6);
    return extraout_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransAddMirHV_B @ 0x0805a040, 136 bytes */
undefined4
W_PutSpriteTransAddMirHV_B(int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  undefined4 extraout_EAX;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_PutSpriteTransAddMirHV8to16_B(param_1,param_2,param_3,param_4,param_5,param_6);
    return extraout_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransAddFlip_B @ 0x0805a0d0, 232 bytes */
void W_PutSpriteTransAddFlip_B
               (int *param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7
               )

{
  if (param_5 == 1) {
    W_PutSpriteTransAddMirH_B(param_1,param_2,param_3,param_4,param_6,param_7);
    return;
  }
  if (param_5 < 2) {
    if (param_5 == 0) {
      W_PutSpriteTransAdd_B(param_1,param_2,param_3,param_4,param_6,param_7);
      return;
    }
  }
  else {
    if (param_5 == 2) {
      W_PutSpriteTransAddMirV_B(param_1,param_2,param_3,param_4,param_6,param_7);
      return;
    }
    if (param_5 == 3) {
      W_PutSpriteTransAddMirHV_B(param_1,param_2,param_3,param_4,param_6,param_7);
      return;
    }
  }
  return;
}

/* W_ScaleSpriteTransAdd @ 0x0805a1c0, 136 bytes */
undefined4
W_ScaleSpriteTransAdd
          (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  int iVar1;
  undefined4 extraout_EAX;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_ScaleSpriteTransAdd8to16(param_1,param_2,param_3,param_4,param_5,param_6);
    return extraout_EAX;
  }
  return V_ColDepth;
}

/* W_ScaleSpriteTransAdd_S @ 0x0805a250, 328 bytes
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
undefined4
W_ScaleSpriteTransAdd_S
          (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  int *piVar1;
  undefined2 uVar3;
  undefined4 uVar2;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined4 extraout_EAX;
  float local_2c;
  float local_28;
  
  piVar1 = (int *)SpriteArrayAccess(param_1,param_2);
  local_28 = (float)*piVar1 * param_5;
  local_2c = (float10)piVar1[1] * param_6;
  uVar3 = (undefined2)((uint)piVar1 >> 0x10);
  if (0.0 < param_6) {
    if (0.0 < param_5) {
      uVar2 = W_ScaleSpriteTransAdd(param_1,param_2,param_3,param_4,local_28,local_2c);
      uVar3 = (undefined2)((uint)uVar2 >> 0x10);
    }
    if (param_5 < 0.0) {
      W_ScaleSpriteTransAddMirH(param_1,param_2,param_3,param_4,-local_28,local_2c);
      uVar3 = extraout_var;
    }
  }
  uVar2 = CONCAT22(uVar3,(ushort)(param_6 < 0.0) << 8 | (ushort)GHIDRA_ISNAN(param_6) << 10 |
                         (ushort)(param_6 == 0.0) << 0xe);
  if (param_6 < 0.0) {
    if (0.0 < param_5) {
      W_ScaleSpriteTransAddMirV(param_1,param_2,param_3,param_4,local_28,-local_2c);
      uVar3 = extraout_var_00;
    }
    uVar2 = CONCAT22(uVar3,(ushort)(param_5 < 0.0) << 8 | (ushort)GHIDRA_ISNAN(param_5) << 10 |
                           (ushort)(param_5 == 0.0) << 0xe);
    if (param_5 < 0.0) {
      local_2c = -local_2c;
      local_28 = -local_28;
      W_ScaleSpriteTransAddMirHV(param_1,param_2,param_3,param_4,local_28,local_2c);
      return extraout_EAX;
    }
  }
  return uVar2;
}

/* W_ScaleSpriteTransAddMirH @ 0x0805a3a0, 136 bytes */
void W_ScaleSpriteTransAddMirH
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  int iVar1;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_ScaleSpriteTransAddMirH8to16(param_1,param_2,param_3,param_4,param_5,param_6);
    return;
  }
  return;
}

/* W_ScaleSpriteTransAddMirV @ 0x0805a430, 136 bytes */
void W_ScaleSpriteTransAddMirV
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  int iVar1;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_ScaleSpriteTransAddMirV8to16(param_1,param_2,param_3,param_4,param_5,param_6);
    return;
  }
  return;
}

/* W_ScaleSpriteTransAddMirHV @ 0x0805a4c0, 136 bytes */
void W_ScaleSpriteTransAddMirHV
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  int iVar1;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_ScaleSpriteTransAddMirHV8to16(param_1,param_2,param_3,param_4,param_5,param_6);
    return;
  }
  return;
}

/* W_ScaleSpriteTransAdd_B @ 0x0805a550, 168 bytes */
void W_ScaleSpriteTransAdd_B
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               int param_7,int param_8)

{
  int iVar1;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_ScaleSpriteTransAdd8to16_B(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    return;
  }
  return;
}

/* W_ScaleSpriteTransAdd_B_S @ 0x0805a600, 392 bytes
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
undefined4
W_ScaleSpriteTransAdd_B_S
          (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
          int param_7,int param_8)

{
  int *piVar1;
  undefined2 uVar3;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined4 uVar2;
  undefined2 extraout_var_01;
  undefined4 extraout_EAX;
  float local_34;
  float local_30;
  
  piVar1 = (int *)SpriteArrayAccess(param_1,param_2);
  local_30 = (float)*piVar1 * param_5;
  local_34 = (float10)piVar1[1] * param_6;
  uVar3 = (undefined2)((uint)piVar1 >> 0x10);
  if (0.0 < param_6) {
    if (0.0 < param_5) {
      W_ScaleSpriteTransAdd_B(param_1,param_2,param_3,param_4,local_30,local_34,param_7,param_8);
      uVar3 = extraout_var;
    }
    if (param_5 < 0.0) {
      W_ScaleSpriteTransAddMirH_B
                (param_1,param_2,param_3,param_4,-local_30,local_34,param_7,param_8);
      uVar3 = extraout_var_00;
    }
  }
  uVar2 = CONCAT22(uVar3,(ushort)(param_6 < 0.0) << 8 | (ushort)GHIDRA_ISNAN(param_6) << 10 |
                         (ushort)(param_6 == 0.0) << 0xe);
  if (param_6 < 0.0) {
    if (0.0 < param_5) {
      W_ScaleSpriteTransAddMirV_B
                (param_1,param_2,param_3,param_4,local_30,-local_34,param_7,param_8);
      uVar3 = extraout_var_01;
    }
    uVar2 = CONCAT22(uVar3,(ushort)(param_5 < 0.0) << 8 | (ushort)GHIDRA_ISNAN(param_5) << 10 |
                           (ushort)(param_5 == 0.0) << 0xe);
    if (param_5 < 0.0) {
      local_34 = -local_34;
      local_30 = -local_30;
      W_ScaleSpriteTransAddMirHV_B
                (param_1,param_2,param_3,param_4,local_30,local_34,param_7,param_8);
      return extraout_EAX;
    }
  }
  return uVar2;
}

/* W_ScaleSpriteTransAddMirH_B @ 0x0805a790, 168 bytes */
void W_ScaleSpriteTransAddMirH_B
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               int param_7,int param_8)

{
  int iVar1;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_ScaleSpriteTransAddMirH8to16_B
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    return;
  }
  return;
}

/* W_ScaleSpriteTransAddMirV_B @ 0x0805a840, 168 bytes */
void W_ScaleSpriteTransAddMirV_B
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               int param_7,int param_8)

{
  int iVar1;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_ScaleSpriteTransAddMirV8to16_B
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    return;
  }
  return;
}

/* W_ScaleSpriteTransAddMirHV_B @ 0x0805a8f0, 168 bytes */
void W_ScaleSpriteTransAddMirHV_B
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               int param_7,int param_8)

{
  int iVar1;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_ScaleSpriteTransAddMirHV8to16_B
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    return;
  }
  return;
}

/* W_RotateSpriteTransAdd @ 0x0805a9a0, 57 bytes */
void W_RotateSpriteTransAdd
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7)

{
  W_RotateSpriteTransAdd_P(param_1,param_2,param_3,param_4,param_5,param_6,param_7,1.0,1.0);
  return;
}

/* W_RotateSpriteTransAddMirH @ 0x0805a9e0, 57 bytes */
void W_RotateSpriteTransAddMirH
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7)

{
  W_RotateSpriteTransAddMirH_P(param_1,param_2,param_3,param_4,param_5,param_6,param_7,1.0,1.0);
  return;
}

/* W_RotateSpriteTransAdd_P @ 0x0805aa20, 541 bytes
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
uint W_RotateSpriteTransAdd_P
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7,float param_8,float param_9)

{
  bool bVar1;
  float10 fVar2;
  int iVar3;
  uint uVar4;
  
  bVar1 = param_6 < 0.0;
  if (bVar1) {
    param_6 = param_6 * -1.0;
    param_5 = 360.0 - param_5;
  }
  if (param_7 < 0.0) {
    fVar2 = param_5 + 180.0;
    bVar1 = !bVar1;
    param_7 = param_7 * -1.0;
    if (360.0 <= fVar2) {
      fVar2 = fVar2 - 360.0;
    }
    param_5 = 360.0 - fVar2;
  }
  if (param_8 < 0.0) {
    param_8 = param_8 * -1.0;
    bVar1 = !bVar1;
  }
  if (param_9 < 0.0) {
    param_5 = param_5 + 180.0;
    bVar1 = !bVar1;
    param_9 = param_9 * -1.0;
    if (360.0 <= param_5) {
      param_5 = param_5 - 360.0;
    }
  }
  iVar3 = V_ColDepth;
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (iVar3 = SpriteArrayAccess(param_1,param_2), *(int *)(iVar3 + 0x10) == 8)
      ))) {
    if (bVar1) {
      uVar4 = W_RotateSpriteTransAddMirH8to16_P
                        (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
      return uVar4;
    }
    uVar4 = W_RotateSpriteTransAdd8to16_P
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    return uVar4;
  }
  return iVar3;
}

/* W_RotateSpriteTransAddMirH_P @ 0x0805ac40, 41 bytes */
void W_RotateSpriteTransAddMirH_P
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7,float param_8,float param_9)

{
  W_RotateSpriteTransAdd_P
            (param_1,param_2,param_3,param_4,360.0 - param_5,-param_6,param_7,param_8,param_9);
  return;
}

/* W_RotateSpriteTransAdd_B @ 0x0805ac70, 67 bytes */
void W_RotateSpriteTransAdd_B
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7,int param_8,int param_9)

{
  W_RotateSpriteTransAdd_B_P
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,1.0,1.0,param_8,param_9);
  return;
}

/* W_RotateSpriteTransAddMirH_B @ 0x0805acc0, 67 bytes */
void W_RotateSpriteTransAddMirH_B
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7,int param_8,int param_9)

{
  W_RotateSpriteTransAddMirH_B_P
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,1.0,1.0,param_8,param_9);
  return;
}

/* W_RotateSpriteTransAdd_B_P @ 0x0805ad10, 639 bytes
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
uint W_RotateSpriteTransAdd_B_P
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7,float param_8,float param_9,int param_10,int param_11)

{
  bool bVar1;
  float10 fVar2;
  int iVar3;
  uint uVar4;
  
  bVar1 = param_6 < 0.0;
  if (bVar1) {
    param_6 = param_6 * -1.0;
    param_5 = 360.0 - param_5;
  }
  if (param_7 < 0.0) {
    fVar2 = param_5 + 180.0;
    bVar1 = !bVar1;
    param_7 = param_7 * -1.0;
    if (360.0 <= fVar2) {
      fVar2 = fVar2 - 360.0;
    }
    param_5 = 360.0 - fVar2;
  }
  if (param_8 < 0.0) {
    param_8 = param_8 * -1.0;
    bVar1 = !bVar1;
  }
  if (param_9 < 0.0) {
    param_5 = param_5 + 180.0;
    bVar1 = !bVar1;
    param_9 = param_9 * -1.0;
    if (360.0 <= param_5) {
      param_5 = param_5 - 360.0;
    }
  }
  iVar3 = V_ColDepth;
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (iVar3 = SpriteArrayAccess(param_1,param_2), *(int *)(iVar3 + 0x10) == 8)
      ))) {
    if (bVar1) {
      uVar4 = W_RotateSpriteTransAddMirH8to16_B_P
                        (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         param_10,param_11);
      return uVar4;
    }
    uVar4 = W_RotateSpriteTransAdd8to16_B_P
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                       param_10,param_11);
    return uVar4;
  }
  return iVar3;
}

/* W_RotateSpriteTransAddMirH_B_P @ 0x0805af90, 41 bytes */
void W_RotateSpriteTransAddMirH_B_P
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7,float param_8,float param_9,int param_10,int param_11)

{
  W_RotateSpriteTransAdd_B_P
            (param_1,param_2,param_3,param_4,360.0 - param_5,-param_6,param_7,param_8,param_9,
             param_10,param_11);
  return;
}

/* W_PutSpriteTransSub @ 0x0805afc0, 104 bytes */
undefined4 W_PutSpriteTransSub(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 extraout_EAX;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_PutSpriteTransSub8to16(param_1,param_2,param_3,param_4);
    return extraout_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransSubMirH @ 0x0805b030, 104 bytes */
undefined4 W_PutSpriteTransSubMirH(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 extraout_EAX;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_PutSpriteTransSubMirH8to16(param_1,param_2,param_3,param_4);
    return extraout_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransSubMirV @ 0x0805b0a0, 104 bytes */
void W_PutSpriteTransSubMirV(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_PutSpriteTransSubMirV8to16(param_1,param_2,param_3,param_4);
    return;
  }
  return;
}

/* W_PutSpriteTransSubMirHV @ 0x0805b110, 104 bytes */
undefined4 W_PutSpriteTransSubMirHV(int *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 extraout_EAX;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_PutSpriteTransSubMirHV8to16(param_1,param_2,param_3,param_4);
    return extraout_EAX;
  }
  return V_ColDepth;
}

/* W_ScaleSpriteTransSub @ 0x0805b180, 136 bytes */
undefined4
W_ScaleSpriteTransSub
          (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  int iVar1;
  undefined4 extraout_EAX;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_ScaleSpriteTransSub8to16(param_1,param_2,param_3,param_4,param_5,param_6);
    return extraout_EAX;
  }
  return V_ColDepth;
}

/* W_ScaleSpriteTransSub_S @ 0x0805b210, 328 bytes
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
undefined4
W_ScaleSpriteTransSub_S
          (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  int *piVar1;
  undefined2 uVar3;
  undefined4 uVar2;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined4 extraout_EAX;
  float local_2c;
  float local_28;
  
  piVar1 = (int *)SpriteArrayAccess(param_1,param_2);
  local_28 = (float)*piVar1 * param_5;
  local_2c = (float10)piVar1[1] * param_6;
  uVar3 = (undefined2)((uint)piVar1 >> 0x10);
  if (0.0 < param_6) {
    if (0.0 < param_5) {
      uVar2 = W_ScaleSpriteTransSub(param_1,param_2,param_3,param_4,local_28,local_2c);
      uVar3 = (undefined2)((uint)uVar2 >> 0x10);
    }
    if (param_5 < 0.0) {
      W_ScaleSpriteTransSubMirH(param_1,param_2,param_3,param_4,-local_28,local_2c);
      uVar3 = extraout_var;
    }
  }
  uVar2 = CONCAT22(uVar3,(ushort)(param_6 < 0.0) << 8 | (ushort)GHIDRA_ISNAN(param_6) << 10 |
                         (ushort)(param_6 == 0.0) << 0xe);
  if (param_6 < 0.0) {
    if (0.0 < param_5) {
      W_ScaleSpriteTransSubMirV(param_1,param_2,param_3,param_4,local_28,-local_2c);
      uVar3 = extraout_var_00;
    }
    uVar2 = CONCAT22(uVar3,(ushort)(param_5 < 0.0) << 8 | (ushort)GHIDRA_ISNAN(param_5) << 10 |
                           (ushort)(param_5 == 0.0) << 0xe);
    if (param_5 < 0.0) {
      local_2c = -local_2c;
      local_28 = -local_28;
      W_ScaleSpriteTransSubMirHV(param_1,param_2,param_3,param_4,local_28,local_2c);
      return extraout_EAX;
    }
  }
  return uVar2;
}

/* W_ScaleSpriteTransSubMirH @ 0x0805b360, 136 bytes */
void W_ScaleSpriteTransSubMirH
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  int iVar1;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_ScaleSpriteTransSubMirH8to16(param_1,param_2,param_3,param_4,param_5,param_6);
    return;
  }
  return;
}

/* W_ScaleSpriteTransSubMirV @ 0x0805b3f0, 136 bytes */
void W_ScaleSpriteTransSubMirV
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  int iVar1;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_ScaleSpriteTransSubMirV8to16(param_1,param_2,param_3,param_4,param_5,param_6);
    return;
  }
  return;
}

/* W_ScaleSpriteTransSubMirHV @ 0x0805b480, 136 bytes */
void W_ScaleSpriteTransSubMirHV
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6)

{
  int iVar1;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_ScaleSpriteTransSubMirHV8to16(param_1,param_2,param_3,param_4,param_5,param_6);
    return;
  }
  return;
}

/* W_RotateSpriteTransSub @ 0x0805b510, 57 bytes */
void W_RotateSpriteTransSub
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7)

{
  W_RotateSpriteTransSub_P(param_1,param_2,param_3,param_4,param_5,param_6,param_7,1.0,1.0);
  return;
}

/* W_RotateSpriteTransSubMirH @ 0x0805b550, 57 bytes */
void W_RotateSpriteTransSubMirH
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7)

{
  W_RotateSpriteTransSubMirH_P(param_1,param_2,param_3,param_4,param_5,param_6,param_7,1.0,1.0);
  return;
}

/* W_RotateSpriteTransSub_P @ 0x0805b590, 541 bytes
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
uint W_RotateSpriteTransSub_P
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7,float param_8,float param_9)

{
  bool bVar1;
  float10 fVar2;
  int iVar3;
  uint uVar4;
  
  bVar1 = param_6 < 0.0;
  if (bVar1) {
    param_6 = param_6 * -1.0;
    param_5 = 360.0 - param_5;
  }
  if (param_7 < 0.0) {
    fVar2 = param_5 + 180.0;
    bVar1 = !bVar1;
    param_7 = param_7 * -1.0;
    if (360.0 <= fVar2) {
      fVar2 = fVar2 - 360.0;
    }
    param_5 = 360.0 - fVar2;
  }
  if (param_8 < 0.0) {
    param_8 = param_8 * -1.0;
    bVar1 = !bVar1;
  }
  if (param_9 < 0.0) {
    param_5 = param_5 + 180.0;
    bVar1 = !bVar1;
    param_9 = param_9 * -1.0;
    if (360.0 <= param_5) {
      param_5 = param_5 - 360.0;
    }
  }
  iVar3 = V_ColDepth;
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (iVar3 = SpriteArrayAccess(param_1,param_2), *(int *)(iVar3 + 0x10) == 8)
      ))) {
    if (bVar1) {
      uVar4 = W_RotateSpriteTransSubMirH8to16_P
                        (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
      return uVar4;
    }
    uVar4 = W_RotateSpriteTransSub8to16_P
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    return uVar4;
  }
  return iVar3;
}

/* W_RotateSpriteTransSubMirH_P @ 0x0805b7b0, 41 bytes */
void W_RotateSpriteTransSubMirH_P
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7,float param_8,float param_9)

{
  W_RotateSpriteTransSub_P
            (param_1,param_2,param_3,param_4,360.0 - param_5,-param_6,param_7,param_8,param_9);
  return;
}

/* W_ScaleShadowTransSub @ 0x0805b7e0, 152 bytes */
void W_ScaleShadowTransSub
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               uint param_7)

{
  int iVar1;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_ScaleShadowTransSub8to16(param_1,param_2,param_3,param_4,param_5,param_6,param_7);
    return;
  }
  return;
}

/* W_ScaleShadowTransSub_S @ 0x0805b880, 360 bytes
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
undefined4
W_ScaleShadowTransSub_S
          (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
          uint param_7)

{
  int *piVar1;
  undefined2 uVar3;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined4 uVar2;
  undefined2 extraout_var_01;
  undefined4 extraout_EAX;
  float local_30;
  float local_2c;
  
  piVar1 = (int *)SpriteArrayAccess(param_1,param_2);
  local_2c = (float)*piVar1 * param_5;
  local_30 = (float10)piVar1[1] * param_6;
  uVar3 = (undefined2)((uint)piVar1 >> 0x10);
  if (0.0 < param_6) {
    if (0.0 < param_5) {
      W_ScaleShadowTransSub(param_1,param_2,param_3,param_4,local_2c,local_30,param_7);
      uVar3 = extraout_var;
    }
    if (param_5 < 0.0) {
      W_ScaleShadowTransSubMirH(param_1,param_2,param_3,param_4,-local_2c,local_30,param_7);
      uVar3 = extraout_var_00;
    }
  }
  uVar2 = CONCAT22(uVar3,(ushort)(param_6 < 0.0) << 8 | (ushort)GHIDRA_ISNAN(param_6) << 10 |
                         (ushort)(param_6 == 0.0) << 0xe);
  if (param_6 < 0.0) {
    if (0.0 < param_5) {
      W_ScaleShadowTransSubMirV(param_1,param_2,param_3,param_4,local_2c,-local_30,param_7);
      uVar3 = extraout_var_01;
    }
    uVar2 = CONCAT22(uVar3,(ushort)(param_5 < 0.0) << 8 | (ushort)GHIDRA_ISNAN(param_5) << 10 |
                           (ushort)(param_5 == 0.0) << 0xe);
    if (param_5 < 0.0) {
      local_30 = -local_30;
      local_2c = -local_2c;
      W_ScaleShadowTransSubMirHV(param_1,param_2,param_3,param_4,local_2c,local_30,param_7);
      return extraout_EAX;
    }
  }
  return uVar2;
}

/* W_ScaleShadowTransSubMirH @ 0x0805b9f0, 152 bytes */
void W_ScaleShadowTransSubMirH
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               uint param_7)

{
  int iVar1;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_ScaleShadowTransSubMirH8to16(param_1,param_2,param_3,param_4,param_5,param_6,param_7);
    return;
  }
  return;
}

/* W_ScaleShadowTransSubMirV @ 0x0805ba90, 152 bytes */
void W_ScaleShadowTransSubMirV
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               uint param_7)

{
  int iVar1;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_ScaleShadowTransSubMirV8to16(param_1,param_2,param_3,param_4,param_5,param_6,param_7);
    return;
  }
  return;
}

/* W_ScaleShadowTransSubMirHV @ 0x0805bb30, 152 bytes */
void W_ScaleShadowTransSubMirHV
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               uint param_7)

{
  int iVar1;
  
  iVar1 = SpriteArrayAccess(param_1,param_2);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(iVar1 + 0x10) == 8)))) {
    W_ScaleShadowTransSubMirHV8to16(param_1,param_2,param_3,param_4,param_5,param_6,param_7);
    return;
  }
  return;
}

/* W_RotateShadowTransSub @ 0x0805bbd0, 62 bytes */
void W_RotateShadowTransSub
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7,uint param_8)

{
  W_RotateShadowTransSub_P(param_1,param_2,param_3,param_4,param_5,param_6,param_7,1.0,1.0,param_8);
  return;
}

/* W_RotateShadowTransSubMirH @ 0x0805bc10, 62 bytes */
void W_RotateShadowTransSubMirH
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7,uint param_8)

{
  W_RotateShadowTransSubMirH_P
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,1.0,1.0,param_8);
  return;
}

/* W_RotateShadowTransSub_P @ 0x0805bc50, 601 bytes
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
int W_RotateShadowTransSub_P
              (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
              float param_7,float param_8,float param_9,uint param_10)

{
  bool bVar1;
  float10 fVar2;
  int iVar3;
  
  bVar1 = param_6 < 0.0;
  if (bVar1) {
    param_6 = param_6 * -1.0;
    param_5 = 360.0 - param_5;
  }
  if (param_7 < 0.0) {
    fVar2 = param_5 + 180.0;
    bVar1 = !bVar1;
    param_7 = param_7 * -1.0;
    if (360.0 <= fVar2) {
      fVar2 = fVar2 - 360.0;
    }
    param_5 = 360.0 - fVar2;
  }
  if (param_8 < 0.0) {
    param_8 = param_8 * -1.0;
    bVar1 = !bVar1;
  }
  if (param_9 < 0.0) {
    param_5 = param_5 + 180.0;
    bVar1 = !bVar1;
    param_9 = param_9 * -1.0;
    if (360.0 <= param_5) {
      param_5 = param_5 - 360.0;
    }
  }
  iVar3 = V_ColDepth;
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (iVar3 = SpriteArrayAccess(param_1,param_2), *(int *)(iVar3 + 0x10) == 8)
      ))) {
    if (bVar1) {
      iVar3 = W_RotateShadowTransSubMirH8to16_P
                        (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         param_10);
      return iVar3;
    }
    iVar3 = W_RotateShadowTransSub8to16_P
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                       param_10);
    return iVar3;
  }
  return iVar3;
}

/* W_RotateShadowTransSubMirH_P @ 0x0805beb0, 41 bytes */
void W_RotateShadowTransSubMirH_P
               (int *param_1,int param_2,float param_3,float param_4,float param_5,float param_6,
               float param_7,float param_8,float param_9,uint param_10)

{
  W_RotateShadowTransSub_P
            (param_1,param_2,param_3,param_4,360.0 - param_5,-param_6,param_7,param_8,param_9,
             param_10);
  return;
}

/* HFlipToSgn @ 0x0805bee0, 18 bytes */
int HFlipToSgn(uint param_1)

{
  return (uint)((param_1 & 1) == 0) * 2 + -1;
}

/* VFlipToSgn @ 0x0805bf00, 18 bytes */
int VFlipToSgn(uint param_1)

{
  return (uint)((param_1 & 2) == 0) * 2 + -1;
}

