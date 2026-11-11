/*
 * precache.c -- background loading
 * A worker thread that loads upcoming characters into the cache while menus
 * and fights run.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/precache.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* PrecacheInit @ 0x080d5700, 97 bytes
 *
 * Initialises the background loader: stores the enable flag, creates its
 * mutex and empties its request queue. Returns true on success.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: EBT_MutexInit
 * Called by: CharInfoInit
 *
 * Elecbyte file: src/mugen/precache.c
 */
uint32_t PrecacheInit(int arg1)

{
  int *pi1;
  int i2;
  
  pi1 = g;
  g[0x14d0] = arg1;
  i2 = EBT_MutexInit();
  if (i2 == 0) {
    pi1[0x14d8] = 0;
    pi1[0x14d9] = 0;
    pi1[0x14da] = 0;
    pi1[0x14db] = -1;
  }
  return (uint32_t)(i2 == 0);
}

/* PrecacheRequestTeam @ 0x080d5770, 124 bytes
 *
 * Queues every member of a team for background loading (under the mutex).
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: EBT_MutexLock, PrecacheRequestChar, EBT_MutexUnlock
 * Called by: GameRoundUpdate, VersusScreen
 *
 * Elecbyte file: src/mugen/precache.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
uint32_t PrecacheRequestTeam(int arg1)

{
  int i1;
  bool b2;
  uint32_t stale_var;
  int i3;
  int i4;
  uint32_t u5;
  
  u5 = 1;
  if (g[0x14d0] == 0) {
    u5 = 0;
  }
  else {
    EBT_MutexLock((pthread_mutex_t *)(g + 0x14d1));
    i3 = *(int *)(arg1 + 8);
    for (i4 = 0; i4 < i3; i4 = i4 + 1) {
      i1 = *(int *)(arg1 + 0x10 + i4 * 0x14);
      if (i1 != -1) {
        b2 = PrecacheRequestChar(i1);
        if (ZEXT8(b2) == 0) {
          u5 = 0;
          break;
        }
        i3 = *(int *)(arg1 + 8);
      }
    }
    EBT_MutexUnlock((pthread_mutex_t *)(g + 0x14d1));
  }
  return u5;
}

/* PrecacheRequestCurArcadeTeam @ 0x080d57f0, 14 bytes
 *
 * Queues the current arcade opponent team for background loading.
 *
 * Calls: PrecacheRequestArcadeTeam
 * Called by: MainLoop
 *
 * Elecbyte file: src/mugen/precache.c
 */
void PrecacheRequestCurArcadeTeam(void)

{
  PrecacheRequestArcadeTeam(0);
  return;
}

/* PrecacheRequestNextArcadeTeam @ 0x080d5800, 14 bytes
 *
 * Queues the next arcade opponent team for background loading.
 *
 * Calls: PrecacheRequestArcadeTeam
 * Called by: GameRoundUpdate
 *
 * Elecbyte file: src/mugen/precache.c
 */
void PrecacheRequestNextArcadeTeam(void)

{
  PrecacheRequestArcadeTeam(1);
  return;
}

/* PrecacheRequestArcadeTeam @ 0x080d5810, 136 bytes
 *
 * Queues the arcade team at position `offset` of the arcade order.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: ArcadeListPeek, PrecacheRequestChar
 * Called by: PrecacheRequestCurArcadeTeam, PrecacheRequestNextArcadeTeam
 *
 * Elecbyte file: src/mugen/precache.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x40 bytes, 1
 *       variables), because their address is taken.
 */
uint32_t PrecacheRequestArcadeTeam(int arg1)

{
  bool b1;
  int i2;
  uint32_t stale_var;
  int i3;
  unsigned char frame[0x40] __attribute__((aligned(16)));
#define stk_3c (*(int (*)[12])(frame + 0x4))
  
  i3 = g[0x33b3];
  if (i3 != 0) {
    i2 = ArcadeListPeek((int)stk_3c,arg1);
    if (g[(2 - i3) * 0x6a7 + 0x33bd] < i2) {
      i2 = g[(2 - i3) * 0x6a7 + 0x33bd];
    }
    i3 = 0;
    if (0 < i2) {
      do {
        b1 = PrecacheRequestChar(stk_3c[i3]);
        if (ZEXT8(b1) == 0) {
          return 0;
        }
        i3 = i3 + 1;
      } while (i3 < i2);
    }
  }
  return 1;
}
#undef stk_3c

/* PrecacheRequestChar @ 0x080d58a0, 93 bytes
 *
 * Queues one character for background loading unless it is already cached
 * (in that case its cache priority is raised).
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: PlayerIsCached, IntQueueAddUnique, PlayerCacheChangePriority
 * Called by: CharacterSelectScreen, PrecacheRequestArcadeTeam,
 *            PrecacheRequestTeam
 *
 * Elecbyte file: src/mugen/precache.c
 * Note: 2 byte results widened with ZEXT8 (upper bytes are zero).
 */
bool PrecacheRequestChar(int arg1)

{
  int *pi1;
  bool b2;
  uint32_t stale_var;
  uint32_t stale_var_00;
  int i3;
  
  pi1 = g + 0x14db;
  if (g[0x14d0] == 0) {
    b2 = false;
  }
  else {
    b2 = PlayerIsCached(arg1);
    if (ZEXT8(b2) == 0) {
      b2 = IntQueueAddUnique(pi1,arg1,4);
      i3 = ZEXT8(b2);
    }
    else {
      i3 = 2;
      PlayerCacheChangePriority(arg1,4);
    }
    b2 = i3 != 0;
  }
  return b2;
}

/* PrecacheStart @ 0x080d5900, 230 bytes
 *
 * Starts the loader thread (EBT_ThreadCreate on PrecacheWorkerThread) if
 * requests are waiting and it is not running.
 *
 * Calls: EBT_MutexLock, IntQueueIsEmpty, EBT_ThreadCreate, EBT_MutexUnlock
 * C library: pthread_yield
 * Called by: CharacterSelectScreen, GameRoundUpdate, MainLoop,
 *            VersusScreen
 *
 * Elecbyte file: src/mugen/precache.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x10 bytes, 1
 *       variables), because their address is taken.
 */
uint32_t PrecacheStart(void)

{
  pthread_mutex_t *m;
  int *pi1;
  bool b2;
  uint32_t u3;
  uint32_t stale_var;
  int i4;
  unsigned char frame[0x10] __attribute__((aligned(16)));
#define stk_10 (*(pthread_t *)(frame + 0x0))
  
  pi1 = g;
  if (g[0x14d0] == 0) {
    u3 = 0;
  }
  else {
    u3 = 1;
    if ((uint32_t)g[0x14d8] < 2) {
      m = (pthread_mutex_t *)(g + 0x14d1);
      EBT_MutexLock(m);
      b2 = IntQueueIsEmpty(pi1 + 0x14db);
      if ((ZEXT8(b2) == 0) &&
         ((pi1[0x14d8] != 0 ||
          (i4 = EBT_ThreadCreate(&stk_10,0,PrecacheWorkerThread,(void *)0x0), i4 == 0)))) {
        pi1[0x14d7] = 1;
        pi1[0x14d9] = 0;
        pi1[0x14da] = 0;
        EBT_MutexUnlock((pthread_mutex_t *)(pi1 + 0x14d1));
        i4 = pi1[0x14d8];
        while (i4 != 1) {
          pthread_yield();
          i4 = pi1[0x14d8];
        }
        EBT_MutexLock((pthread_mutex_t *)(pi1 + 0x14d1));
        pi1[0x14d8] = 2;
        EBT_MutexUnlock((pthread_mutex_t *)(pi1 + 0x14d1));
        u3 = 1;
      }
      else {
        EBT_MutexUnlock(m);
        u3 = 0;
      }
    }
  }
  return u3;
}
#undef stk_10

/* PrecacheRequestCancel @ 0x080d59f0, 61 bytes
 *
 * Empties the request queue so the loader stops after the current character.
 *
 * Calls: EBT_MutexLock, EBT_MutexUnlock
 * Called by: GameLoop, MainLoop, VersusScreen
 *
 * Elecbyte file: src/mugen/precache.c
 */
void PrecacheRequestCancel(void)

{
  pthread_mutex_t *m;
  int *pi1;
  
  pi1 = g;
  m = (pthread_mutex_t *)(g + 0x14d1);
  EBT_MutexLock(m);
  if (pi1[0x14d7] != 0) {
    pi1[0x14da] = 1;
  }
  EBT_MutexUnlock(m);
  return;
}

/* PrecacheIsRunning @ 0x080d5a30, 62 bytes
 *
 * Returns true while the loader thread is working.
 *
 * Calls: EBT_MutexLock, EBT_MutexUnlock
 * Called by: GameLoop, MainLoop
 *
 * Elecbyte file: src/mugen/precache.c
 */
int PrecacheIsRunning(void)

{
  pthread_mutex_t *m;
  int *pi1;
  int i2;
  
  pi1 = g;
  i2 = 0;
  if (g[0x14d0] != 0) {
    m = (pthread_mutex_t *)(g + 0x14d1);
    EBT_MutexLock(m);
    i2 = pi1[0x14d7];
    EBT_MutexUnlock(m);
  }
  return i2;
}

/* PrecacheIsDone @ 0x080d5a70, 95 bytes
 *
 * Returns true when the loader has finished all requests. Not called in this
 * build.
 *
 * Calls: EBT_MutexLock, EBT_MutexUnlock
 *
 * Elecbyte file: src/mugen/precache.c
 */
uint32_t PrecacheIsDone(void)

{
  int *pi1;
  uint32_t u2;
  
  pi1 = g;
  if (g[0x14d0] == 0) {
    u2 = 1;
  }
  else {
    u2 = 0;
    EBT_MutexLock((pthread_mutex_t *)(g + 0x14d1));
    if ((pi1[0x14d9] != 0) || (pi1[0x14d7] == 0)) {
      u2 = 1;
    }
    EBT_MutexUnlock((pthread_mutex_t *)(pi1 + 0x14d1));
  }
  return u2;
}

/* PrecacheFinish @ 0x080d5ad0, 143 bytes
 *
 * Waits, sleeping 5 ms at a time, until the loader thread reports it has
 * finished, then resets the loader state. Called before the engine needs the
 * characters itself.
 *
 * Calls: EBT_MutexLock, EBT_MutexUnlock, TimerDelay
 * Called by: CharacterSelectScreen, GameLoop, GameRoundUpdate, MainLoop,
 *            VersusScreen
 *
 * Elecbyte file: src/mugen/precache.c
 */
void PrecacheFinish(void)

{
  pthread_mutex_t *m;
  int i1;
  int *pi2;
  
  pi2 = g;
  if (g[0x14d0] != 0) {
    m = (pthread_mutex_t *)(g + 0x14d1);
    EBT_MutexLock(m);
    if (pi2[0x14d7] != 0) {
      i1 = pi2[0x14d9];
      while (i1 == 0) {
        EBT_MutexUnlock(m);
        TimerDelay(5);
        EBT_MutexLock(m);
        i1 = pi2[0x14d9];
      }
      pi2[0x14d7] = 0;
      pi2[0x14d9] = 0;
      pi2[0x14da] = 0;
    }
    EBT_MutexUnlock((pthread_mutex_t *)(pi2 + 0x14d1));
  }
  return;
}

/* PrecacheWorkerThread @ 0x080d5b60, 546 bytes
 *
 * The loader thread. It takes queued characters one by one and loads each
 * into the player cache (PlayerCacheLoad) when a cache slot is free,
 * yielding between steps. It stops when the queue is empty or cancelled.
 * Errors are reported as "Error while precaching".
 *
 * Globals read: errmsg
 * Calls: EBT_MutexLock, IntQueueClear, EBT_MutexUnlock, IntQueueIsEmpty,
 *        IntQueuePeekTop, PlayerCacheHasUnused, PlayerCacheLoad,
 *        IntQueueDequeue, PlayerCacheFreePriority, IntQueueAddUnique
 * C library: pthread_yield, sprintf
 * Messages:
 *   "\nError while precaching"
 *
 * Elecbyte file: src/mugen/precache.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x40 bytes, 2
 *       variables), because their address is taken.
 */
void PrecacheWorkerThread(void)

{
  int *pi1;
  pthread_mutex_t *pp2;
  int *pi3;
  bool b4;
  uint32_t stale_var;
  int chardef;
  uint32_t *pu6;
  uint32_t *pu7;
  uint32_t stale_EDX;
  uint32_t u8;
  uint32_t u9;
  unsigned char frame[0x40] __attribute__((aligned(16)));
#define stk_40 (*(int *)(frame + 0x0))
#define stk_3c (*(int (*)[11])(frame + 0x4))
  
  pi3 = g;
  pi1 = g + 0x14db;
  pp2 = (pthread_mutex_t *)(g + 0x14d1);
  EBT_MutexLock(pp2);
  IntQueueClear(stk_3c);
  pi3[0x14d8] = 1;
  EBT_MutexUnlock(pp2);
  while (pi3[0x14d8] == 1) {
    pthread_yield();
  }
  pp2 = (pthread_mutex_t *)(pi3 + 0x14d1);
  EBT_MutexLock(pp2);
  pi3[0x14d8] = 3;
  do {
    b4 = IntQueueIsEmpty(pi1);
    if (ZEXT8(b4) != 0) goto L_080d5ce5;
    IntQueuePeekTop(pi1,&stk_40);
    EBT_MutexUnlock(pp2);
    chardef = PlayerCacheHasUnused();
    if (chardef != 0) {
      chardef = PlayerCacheLoad(stk_40);
      if (chardef == 0) {
        pu7 = (uint32_t *)(g + G_ERRMSG);
        do {
          pu6 = pu7;
          pu7 = pu6 + 1;
          u8 = *pu6 + 0xfefefeff & (*pu6 ^ 0xffffffff);
          u9 = u8 & 0x80808080;
        } while (u9 == 0);
        if ((u8 & 0x8080) == 0) {
          u9 = u9 >> 0x10;
          pu7 = (uint32_t *)((int)pu6 + 6);
        }
        sprintf((char *)((int)pu7 +
                         (-(int)(g + G_ERRMSG) - (uint32_t)CARRY1((uint8_t)u9,(uint8_t)u9)) + 0x20745 +
                        (int)g),"\nError while precaching",stale_EDX,stale_EDX);
        EBT_MutexLock(pp2);
        pi3[0x14d9] = 1;
        IntQueueClear(pi1);
        EBT_MutexUnlock(pp2);
L_080d5ce5:
        while (chardef = IntQueueDequeue(stk_3c,&stk_40), chardef != 0) {
          PlayerCacheFreePriority(stk_40,4);
        }
        pi3[0x14d9] = 1;
        pi3[0x14da] = 0;
        pi3[0x14d8] = 0;
        EBT_MutexUnlock((pthread_mutex_t *)(pi3 + 0x14d1));
        return;
      }
      IntQueueAddUnique(stk_3c,stk_40,4);
    }
    EBT_MutexLock(pp2);
    if (pi3[0x14da] != 0) {
      IntQueueClear(pi1);
      goto L_080d5ce5;
    }
    IntQueueDequeue(pi1,(int *)0x0);
  } while( true );
}
#undef stk_40
#undef stk_3c

/* IntQueueAddUnique @ 0x080d5d90, 90 bytes
 *
 * Appends a value to a -1-terminated int queue of capacity `size` unless it
 * is already there. Returns false if it was present or the queue is full.
 *
 * Parameters:
 *   queue        int *
 *   value        int
 *   size         int
 *
 * Called by: PrecacheRequestChar, PrecacheWorkerThread
 *
 * Elecbyte file: src/mugen/precache.c
 */
bool IntQueueAddUnique(int *queue,int value,int size)

{
  int i1;
  int i2;
  
  i2 = 0;
  if (0 < size) {
    i1 = *queue;
    while (i1 != -1) {
      if (i1 == value) {
        return true;
      }
      i2 = i2 + 1;
      if (size <= i2) break;
      i1 = queue[i2];
    }
  }
  if (i2 != size) {
    queue[i2] = value;
    queue[i2 + 1] = -1;
  }
  return i2 != size;
}

/* IntQueueIsEmpty @ 0x080d5df0, 13 bytes
 *
 * Returns true if the queue's first entry is -1.
 *
 * Parameters:
 *   queue        int *
 *
 * Called by: PrecacheStart, PrecacheWorkerThread
 *
 * Elecbyte file: src/mugen/precache.c
 */
bool IntQueueIsEmpty(int *queue)

{
  return *queue == -1;
}

/* IntQueuePeekTop @ 0x080d5e00, 28 bytes
 *
 * Returns the first value of the queue.
 *
 * Parameters:
 *   queue        int *
 *   out          int *
 *
 * Called by: PrecacheWorkerThread
 *
 * Elecbyte file: src/mugen/precache.c
 */
uint32_t IntQueuePeekTop(int *queue,int *out)

{
  if (*queue == -1) {
    return 0;
  }
  *out = *queue;
  return 1;
}

/* IntQueueDequeue @ 0x080d5e20, 57 bytes
 *
 * Removes the first value of the queue (shifting the rest, at most 4
 * entries) and returns it through `out`.
 *
 * Parameters:
 *   queue        int *
 *   out          int *
 *
 * Called by: PrecacheWorkerThread
 *
 * Elecbyte file: src/mugen/precache.c
 */
uint32_t IntQueueDequeue(int *queue,int *out)

{
  int i1;
  int i2;
  
  i1 = *queue;
  if (i1 == -1) {
    return 0;
  }
  if (out != (int *)0x0) {
    *out = i1;
    i1 = *queue;
  }
  i2 = 0;
  while( true ) {
    if (i1 == -1) {
      return 1;
    }
    queue[i2] = queue[i2 + 1];
    i2 = i2 + 1;
    if (3 < i2) break;
    i1 = queue[i2];
  }
  return 1;
}

/* IntQueueClear @ 0x080d5e60, 11 bytes
 *
 * Empties the queue.
 *
 * Parameters:
 *   queue        uint32_t *
 *
 * Called by: PrecacheWorkerThread
 *
 * Elecbyte file: src/mugen/precache.c
 */
uint32_t * IntQueueClear(uint32_t *queue)

{
  *queue = 0xffffffff;
  return queue;
}

