/*
 * precache.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x080d5700-0x080d5e6b, 17 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* PrecacheInit @ 0x080d5700, 97 bytes */
uint PrecacheInit(int param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = g;
  g[0x14d0] = param_1;
  iVar2 = EBT_MutexInit();
  if (iVar2 == 0) {
    piVar1[0x14d8] = 0;
    piVar1[0x14d9] = 0;
    piVar1[0x14da] = 0;
    piVar1[0x14db] = -1;
  }
  return (uint)(iVar2 == 0);
}

/* PrecacheRequestTeam @ 0x080d5770, 124 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
undefined4 PrecacheRequestTeam(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined3 extraout_var;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  uVar5 = 1;
  if (g[0x14d0] == 0) {
    uVar5 = 0;
  }
  else {
    EBT_MutexLock((pthread_mutex_t *)(g + 0x14d1));
    iVar3 = *(int *)(param_1 + 8);
    for (iVar4 = 0; iVar4 < iVar3; iVar4 = iVar4 + 1) {
      iVar1 = *(int *)(param_1 + 0x10 + iVar4 * 0x14);
      if (iVar1 != -1) {
        bVar2 = PrecacheRequestChar(iVar1);
        if (GHIDRA_ZEXT8(bVar2) == 0) {
          uVar5 = 0;
          break;
        }
        iVar3 = *(int *)(param_1 + 8);
      }
    }
    EBT_MutexUnlock((pthread_mutex_t *)(g + 0x14d1));
  }
  return uVar5;
}

/* PrecacheRequestCurArcadeTeam @ 0x080d57f0, 14 bytes */
void PrecacheRequestCurArcadeTeam(void)

{
  PrecacheRequestArcadeTeam(0);
  return;
}

/* PrecacheRequestNextArcadeTeam @ 0x080d5800, 14 bytes */
void PrecacheRequestNextArcadeTeam(void)

{
  PrecacheRequestArcadeTeam(1);
  return;
}

/* PrecacheRequestArcadeTeam @ 0x080d5810, 136 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x40-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 PrecacheRequestArcadeTeam(int param_1)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  int iVar3;
  unsigned char ghidra_frame[0x40] __attribute__((aligned(16)));
#define local_3c (*(int (*)[12])(ghidra_frame + 0x4))
  
  iVar3 = g[0x33b3];
  if (iVar3 != 0) {
    iVar2 = ArcadeListPeek((int)local_3c,param_1);
    if (g[(2 - iVar3) * 0x6a7 + 0x33bd] < iVar2) {
      iVar2 = g[(2 - iVar3) * 0x6a7 + 0x33bd];
    }
    iVar3 = 0;
    if (0 < iVar2) {
      do {
        bVar1 = PrecacheRequestChar(local_3c[iVar3]);
        if (GHIDRA_ZEXT8(bVar1) == 0) {
          return 0;
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < iVar2);
    }
  }
  return 1;
}
#undef local_3c

/* PrecacheRequestChar @ 0x080d58a0, 93 bytes
 * FIXUP: 2 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
bool PrecacheRequestChar(int param_1)

{
  int *piVar1;
  bool bVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar3;
  
  piVar1 = g + 0x14db;
  if (g[0x14d0] == 0) {
    bVar2 = false;
  }
  else {
    bVar2 = PlayerIsCached(param_1);
    if (GHIDRA_ZEXT8(bVar2) == 0) {
      bVar2 = IntQueueAddUnique(piVar1,param_1,4);
      iVar3 = GHIDRA_ZEXT8(bVar2);
    }
    else {
      iVar3 = 2;
      PlayerCacheChangePriority(param_1,4);
    }
    bVar2 = iVar3 != 0;
  }
  return bVar2;
}

/* PrecacheStart @ 0x080d5900, 230 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x10-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 PrecacheStart(void)

{
  pthread_mutex_t *m;
  int *piVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined3 extraout_var;
  int iVar4;
  unsigned char ghidra_frame[0x10] __attribute__((aligned(16)));
#define local_10 (*(pthread_t *)(ghidra_frame + 0x0))
  
  piVar1 = g;
  if (g[0x14d0] == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = 1;
    if ((uint)g[0x14d8] < 2) {
      m = (pthread_mutex_t *)(g + 0x14d1);
      EBT_MutexLock(m);
      bVar2 = IntQueueIsEmpty(piVar1 + 0x14db);
      if ((GHIDRA_ZEXT8(bVar2) == 0) &&
         ((piVar1[0x14d8] != 0 ||
          (iVar4 = EBT_ThreadCreate(&local_10,0,PrecacheWorkerThread,(void *)0x0), iVar4 == 0)))) {
        piVar1[0x14d7] = 1;
        piVar1[0x14d9] = 0;
        piVar1[0x14da] = 0;
        EBT_MutexUnlock((pthread_mutex_t *)(piVar1 + 0x14d1));
        iVar4 = piVar1[0x14d8];
        while (iVar4 != 1) {
          pthread_yield();
          iVar4 = piVar1[0x14d8];
        }
        EBT_MutexLock((pthread_mutex_t *)(piVar1 + 0x14d1));
        piVar1[0x14d8] = 2;
        EBT_MutexUnlock((pthread_mutex_t *)(piVar1 + 0x14d1));
        uVar3 = 1;
      }
      else {
        EBT_MutexUnlock(m);
        uVar3 = 0;
      }
    }
  }
  return uVar3;
}
#undef local_10

/* PrecacheRequestCancel @ 0x080d59f0, 61 bytes */
void PrecacheRequestCancel(void)

{
  pthread_mutex_t *m;
  int *piVar1;
  
  piVar1 = g;
  m = (pthread_mutex_t *)(g + 0x14d1);
  EBT_MutexLock(m);
  if (piVar1[0x14d7] != 0) {
    piVar1[0x14da] = 1;
  }
  EBT_MutexUnlock(m);
  return;
}

/* PrecacheIsRunning @ 0x080d5a30, 62 bytes */
int PrecacheIsRunning(void)

{
  pthread_mutex_t *m;
  int *piVar1;
  int iVar2;
  
  piVar1 = g;
  iVar2 = 0;
  if (g[0x14d0] != 0) {
    m = (pthread_mutex_t *)(g + 0x14d1);
    EBT_MutexLock(m);
    iVar2 = piVar1[0x14d7];
    EBT_MutexUnlock(m);
  }
  return iVar2;
}

/* PrecacheIsDone @ 0x080d5a70, 95 bytes */
undefined4 PrecacheIsDone(void)

{
  int *piVar1;
  undefined4 uVar2;
  
  piVar1 = g;
  if (g[0x14d0] == 0) {
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
    EBT_MutexLock((pthread_mutex_t *)(g + 0x14d1));
    if ((piVar1[0x14d9] != 0) || (piVar1[0x14d7] == 0)) {
      uVar2 = 1;
    }
    EBT_MutexUnlock((pthread_mutex_t *)(piVar1 + 0x14d1));
  }
  return uVar2;
}

/* PrecacheFinish @ 0x080d5ad0, 143 bytes */
void PrecacheFinish(void)

{
  pthread_mutex_t *m;
  int iVar1;
  int *piVar2;
  
  piVar2 = g;
  if (g[0x14d0] != 0) {
    m = (pthread_mutex_t *)(g + 0x14d1);
    EBT_MutexLock(m);
    if (piVar2[0x14d7] != 0) {
      iVar1 = piVar2[0x14d9];
      while (iVar1 == 0) {
        EBT_MutexUnlock(m);
        TimerDelay(5);
        EBT_MutexLock(m);
        iVar1 = piVar2[0x14d9];
      }
      piVar2[0x14d7] = 0;
      piVar2[0x14d9] = 0;
      piVar2[0x14da] = 0;
    }
    EBT_MutexUnlock((pthread_mutex_t *)(piVar2 + 0x14d1));
  }
  return;
}

/* PrecacheWorkerThread @ 0x080d5b60, 546 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 2 stack locals placed at their original offsets in a 0x40-byte frame (a local's address escapes, see apply_frame_emulation) */
/* WARNING: Removing unreachable block (ram,0x080d5d25) */
/* WARNING: Removing unreachable block (ram,0x080d5d2c) */

void PrecacheWorkerThread(void)

{
  int *piVar1;
  pthread_mutex_t *ppVar2;
  int *piVar3;
  bool bVar4;
  undefined3 extraout_var;
  int iVar5;
  uint *puVar6;
  uint *puVar7;
  undefined4 extraout_EDX;
  uint uVar8;
  uint uVar9;
  unsigned char ghidra_frame[0x40] __attribute__((aligned(16)));
#define local_40 (*(int *)(ghidra_frame + 0x0))
#define local_3c (*(int (*)[11])(ghidra_frame + 0x4))
  
  piVar3 = g;
  piVar1 = g + 0x14db;
  ppVar2 = (pthread_mutex_t *)(g + 0x14d1);
  EBT_MutexLock(ppVar2);
  IntQueueClear(local_3c);
  piVar3[0x14d8] = 1;
  EBT_MutexUnlock(ppVar2);
  while (piVar3[0x14d8] == 1) {
    pthread_yield();
  }
  ppVar2 = (pthread_mutex_t *)(piVar3 + 0x14d1);
  EBT_MutexLock(ppVar2);
  piVar3[0x14d8] = 3;
  do {
    bVar4 = IntQueueIsEmpty(piVar1);
    if (GHIDRA_ZEXT8(bVar4) != 0) goto LAB_080d5ce5;
    IntQueuePeekTop(piVar1,&local_40);
    EBT_MutexUnlock(ppVar2);
    iVar5 = PlayerCacheHasUnused();
    if (iVar5 != 0) {
      iVar5 = PlayerCacheLoad(local_40);
      if (iVar5 == 0) {
        puVar7 = (uint *)(g + 0x81d2);
        do {
          puVar6 = puVar7;
          puVar7 = puVar6 + 1;
          uVar8 = *puVar6 + 0xfefefeff & (*puVar6 ^ 0xffffffff);
          uVar9 = uVar8 & 0x80808080;
        } while (uVar9 == 0);
        if ((uVar8 & 0x8080) == 0) {
          uVar9 = uVar9 >> 0x10;
          puVar7 = (uint *)((int)puVar6 + 6);
        }
        sprintf((char *)((int)puVar7 +
                         (-(int)(g + 0x81d2) - (uint)CARRY1((byte)uVar9,(byte)uVar9)) + 0x20745 +
                        (int)g),"\nError while precaching",extraout_EDX,extraout_EDX);
        EBT_MutexLock(ppVar2);
        piVar3[0x14d9] = 1;
        IntQueueClear(piVar1);
        EBT_MutexUnlock(ppVar2);
LAB_080d5ce5:
        while (iVar5 = IntQueueDequeue(local_3c,&local_40), iVar5 != 0) {
          PlayerCacheFreePriority(local_40,4);
        }
        piVar3[0x14d9] = 1;
        piVar3[0x14da] = 0;
        piVar3[0x14d8] = 0;
        EBT_MutexUnlock((pthread_mutex_t *)(piVar3 + 0x14d1));
        return;
      }
      IntQueueAddUnique(local_3c,local_40,4);
    }
    EBT_MutexLock(ppVar2);
    if (piVar3[0x14da] != 0) {
      IntQueueClear(piVar1);
      goto LAB_080d5ce5;
    }
    IntQueueDequeue(piVar1,(int *)0x0);
  } while( true );
}
#undef local_40
#undef local_3c

/* IntQueueAddUnique @ 0x080d5d90, 90 bytes */
bool IntQueueAddUnique(int *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < param_3) {
    iVar1 = *param_1;
    while (iVar1 != -1) {
      if (iVar1 == param_2) {
        return true;
      }
      iVar2 = iVar2 + 1;
      if (param_3 <= iVar2) break;
      iVar1 = param_1[iVar2];
    }
  }
  if (iVar2 != param_3) {
    param_1[iVar2] = param_2;
    param_1[iVar2 + 1] = -1;
  }
  return iVar2 != param_3;
}

/* IntQueueIsEmpty @ 0x080d5df0, 13 bytes */
bool IntQueueIsEmpty(int *param_1)

{
  return *param_1 == -1;
}

/* IntQueuePeekTop @ 0x080d5e00, 28 bytes */
undefined4 IntQueuePeekTop(int *param_1,int *param_2)

{
  if (*param_1 == -1) {
    return 0;
  }
  *param_2 = *param_1;
  return 1;
}

/* IntQueueDequeue @ 0x080d5e20, 57 bytes */
undefined4 IntQueueDequeue(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *param_1;
  if (iVar1 == -1) {
    return 0;
  }
  if (param_2 != (int *)0x0) {
    *param_2 = iVar1;
    iVar1 = *param_1;
  }
  iVar2 = 0;
  while( true ) {
    if (iVar1 == -1) {
      return 1;
    }
    param_1[iVar2] = param_1[iVar2 + 1];
    iVar2 = iVar2 + 1;
    if (3 < iVar2) break;
    iVar1 = param_1[iVar2];
  }
  return 1;
}

/* IntQueueClear @ 0x080d5e60, 11 bytes */
undefined4 * IntQueueClear(undefined4 *param_1)

{
  *param_1 = 0xffffffff;
  return param_1;
}

