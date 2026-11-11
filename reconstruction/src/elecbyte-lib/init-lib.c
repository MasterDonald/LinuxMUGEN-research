/*
 * init-lib.c -- library start-up
 * Starts and stops the Allegro-based Elecbyte library.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/init-lib.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* ElecInit @ 0x08053910, 73 bytes
 *
 * Starts the Elecbyte library: install_allegro (with atexit and errno) and,
 * on success, clears the error code and the error/debug message buffers.
 * Returns nonzero on failure.
 *
 * Calls: ErrorSet
 * C library: __errno_location, install_allegro
 * Called by: GameInit
 *
 * Elecbyte file: src/lib/init-lib.c
 */
bool ElecInit(void)

{
  int *pi1;
  int i2;
  generic_fn *pc3;
  
  pc3 = atexit;
  pi1 = __errno_location();
  i2 = install_allegro(0,pi1,pc3);
  if (i2 == 0) {
    ErrorSet(0);
    DebugTmpStr[0] = 0;
    ErrorMessage[0] = 0;
  }
  return i2 != 0;
}

/* ElecDeInit @ 0x08053960, 5 bytes
 *
 * Library shutdown hook; empty in this build.
 *
 * C library: allegro_exit
 * Called by: ErrorExit, GameDeInit
 *
 * Elecbyte file: src/lib/init-lib.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to free
 */
uint32_t ElecDeInit(void)

{
  uint32_t u1;
  
  u1 = allegro_exit();
  return u1;
}

