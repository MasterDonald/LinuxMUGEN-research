/*
 * lthreads.c -- threads
 * Thin pthread wrappers used by the background character loader.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/lthreads.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* EBT_ThreadCreate @ 0x08081ff0, 40 bytes
 *
 * Starts a thread with default attributes (pthread_create wrapper) and
 * stores its id in the first argument. Returns pthread_create's result. The
 * precache loader (PrecacheStart) uses it to load characters in the
 * background.
 *
 * Parameters:
 *   arg1         pthread_t *
 *   arg2         uint32_t
 *   arg3         __start_routine *
 *   arg4         void *
 *
 * C library: pthread_create
 * Called by: PrecacheStart
 *
 * Elecbyte file: src/lib/lthreads.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x10 bytes, 1
 *       variables), because their address is taken.
 */
int EBT_ThreadCreate(pthread_t *arg1,uint32_t arg2,__start_routine *arg3,void *arg4)

{
  int i1;
  pthread_t entry_ECX;
  unsigned char frame[0x10] __attribute__((aligned(16)));
#define stk_8 (*(pthread_t *)(frame + 0x8))
  
  stk_8 = entry_ECX;
  i1 = pthread_create(&stk_8,(pthread_attr_t *)0x0,arg3,arg4);
  *arg1 = stk_8;
  return i1;
}
#undef stk_8

/* EBT_MutexInit @ 0x08082020, 19 bytes
 *
 * Initialises a pthread mutex and returns pthread_mutex_init's result (0 =
 * success).
 *
 * The mutex it initialises is a local variable of this function (as in the
 * original machine code), so the mutex is lost when it returns. The precache
 * module then locks a different, global mutex in the global block that was
 * never initialised. That works only because a zero-filled pthread_mutex_t
 * is a valid unlocked mutex in glibc. Original Elecbyte defect; keep this in
 * mind when porting.
 *
 * C library: pthread_mutex_init
 * Called by: PrecacheInit
 *
 * Elecbyte file: src/lib/lthreads.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x30 bytes, 1
 *       variables), because their address is taken.
 */
int EBT_MutexInit(void)

{
  int i1;
  unsigned char frame[0x30] __attribute__((aligned(16)));
#define stk_2c (*(pthread_mutex_t *)(frame + 0x4))
  
  i1 = pthread_mutex_init(&stk_2c,(pthread_mutexattr_t *)0x0);
  return i1;
}
#undef stk_2c

/* EBT_MutexDestroy @ 0x08082040, 5 bytes
 *
 * Destroys a mutex (pthread_mutex_destroy).
 *
 * Parameters:
 *   mutex        pthread_mutex_t *
 *
 * C library: pthread_mutex_destroy
 *
 * Elecbyte file: src/lib/lthreads.c
 */
int EBT_MutexDestroy(pthread_mutex_t *mutex)

{
  int i1;
  
  i1 = pthread_mutex_destroy(mutex);
  return i1;
}

/* EBT_MutexLock @ 0x08082050, 5 bytes
 *
 * Locks a mutex (pthread_mutex_lock).
 *
 * Parameters:
 *   m            pthread_mutex_t *
 *
 * C library: pthread_mutex_lock
 * Called by: PrecacheFinish, PrecacheIsDone, PrecacheIsRunning,
 *            PrecacheRequestCancel, PrecacheRequestTeam, PrecacheStart,
 *            PrecacheWorkerThread
 *
 * Elecbyte file: src/lib/lthreads.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to
 *       __pthread_alt_lock,__pthread_find_self,__pthread_lock
 */
int EBT_MutexLock(pthread_mutex_t *m)

{
  int i1;
  
  i1 = pthread_mutex_lock(m);
  return i1;
}

/* EBT_MutexUnlock @ 0x08082060, 5 bytes
 *
 * Unlocks a mutex (pthread_mutex_unlock).
 *
 * Parameters:
 *   m            pthread_mutex_t *
 *
 * C library: pthread_mutex_unlock
 * Called by: PrecacheFinish, PrecacheIsDone, PrecacheIsRunning,
 *            PrecacheRequestCancel, PrecacheRequestTeam, PrecacheStart,
 *            PrecacheWorkerThread
 *
 * Elecbyte file: src/lib/lthreads.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to
 *       __pthread_alt_unlock,__pthread_find_self,__pthread_unlock
 */
int EBT_MutexUnlock(pthread_mutex_t *m)

{
  int i1;
  
  i1 = pthread_mutex_unlock(m);
  return i1;
}

