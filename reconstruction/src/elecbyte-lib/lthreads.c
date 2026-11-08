/*
 * lthreads.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08081ff0-0x08082065, 5 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* EBT_ThreadCreate @ 0x08081ff0, 40 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x10-byte frame (a local's address escapes, see apply_frame_emulation) */
int EBT_ThreadCreate(pthread_t *param_1,undefined4 param_2,__start_routine *param_3,void *param_4)

{
  int iVar1;
  pthread_t in_ECX;
  unsigned char ghidra_frame[0x10] __attribute__((aligned(16)));
#define local_8 (*(pthread_t *)(ghidra_frame + 0x8))
  
  local_8 = in_ECX;
  iVar1 = pthread_create(&local_8,(pthread_attr_t *)0x0,param_3,param_4);
  *param_1 = local_8;
  return iVar1;
}
#undef local_8

/* EBT_MutexInit @ 0x08082020, 19 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x30-byte frame (a local's address escapes, see apply_frame_emulation) */
int EBT_MutexInit(void)

{
  int iVar1;
  unsigned char ghidra_frame[0x30] __attribute__((aligned(16)));
#define local_2c (*(pthread_mutex_t *)(ghidra_frame + 0x4))
  
  iVar1 = pthread_mutex_init(&local_2c,(pthread_mutexattr_t *)0x0);
  return iVar1;
}
#undef local_2c

/* EBT_MutexDestroy @ 0x08082040, 5 bytes */
int EBT_MutexDestroy(pthread_mutex_t *__mutex)

{
  int iVar1;
  
  iVar1 = pthread_mutex_destroy(__mutex);
  return iVar1;
}

/* EBT_MutexLock @ 0x08082050, 5 bytes
 * REVIEW: calls-missing-in-pid:__pthread_alt_lock,__pthread_find_self,__pthread_lock */
int EBT_MutexLock(pthread_mutex_t *m)

{
  int iVar1;
  
  iVar1 = pthread_mutex_lock(m);
  return iVar1;
}

/* EBT_MutexUnlock @ 0x08082060, 5 bytes
 * REVIEW: calls-missing-in-pid:__pthread_alt_unlock,__pthread_find_self,__pthread_unlock */
int EBT_MutexUnlock(pthread_mutex_t *m)

{
  int iVar1;
  
  iVar1 = pthread_mutex_unlock(m);
  return iVar1;
}

