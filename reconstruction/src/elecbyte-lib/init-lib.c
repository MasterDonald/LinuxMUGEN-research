/*
 * init-lib.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08053910-0x08053965, 2 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* ElecInit @ 0x08053910, 73 bytes */
bool ElecInit(void)

{
  int *piVar1;
  int iVar2;
  code *pcVar3;
  
  pcVar3 = atexit;
  piVar1 = __errno_location();
  iVar2 = install_allegro(0,piVar1,pcVar3);
  if (iVar2 == 0) {
    ErrorSet(0);
    DebugTmpStr[0] = 0;
    ErrorMessage[0] = 0;
  }
  return iVar2 != 0;
}

/* ElecDeInit @ 0x08053960, 5 bytes
 * REVIEW: calls-missing-in-pid:free */
undefined4 ElecDeInit(void)

{
  undefined4 uVar1;
  
  uVar1 = allegro_exit();
  return uVar1;
}

