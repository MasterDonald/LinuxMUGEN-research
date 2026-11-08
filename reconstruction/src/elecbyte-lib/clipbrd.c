/*
 * clipbrd.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0804e440-0x0804e654, 5 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* ClipboardNew @ 0x0804e440, 153 bytes */
int * ClipboardNew(int param_1,size_t param_2)

{
  int iVar1;
  int *piVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  
  if ((0 < (int)param_2) && (piVar2 = calloc(1,0x18), piVar2 != (int *)0x0)) {
    piVar2[2] = param_1;
    piVar2[3] = param_2;
    pvVar3 = calloc(param_2,4);
    *piVar2 = (int)pvVar3;
    if (pvVar3 != (void *)0x0) {
      pvVar3 = calloc(param_1 * param_2,1);
      piVar2[1] = (int)pvVar3;
      if (pvVar3 != (void *)0x0) {
        iVar5 = 0;
        if ((int)param_2 < 1) {
          return piVar2;
        }
        iVar1 = *piVar2;
        iVar4 = 0;
        do {
          *(int *)(iVar1 + iVar5 * 4) = iVar4 + piVar2[1];
          iVar5 = iVar5 + 1;
          iVar4 = iVar4 + param_1;
        } while (iVar5 < (int)param_2);
        return piVar2;
      }
    }
    ClipboardFree(piVar2);
  }
  return (int *)0x0;
}

/* ClipboardFree @ 0x0804e4e0, 68 bytes
 * REVIEW: pid-unaff_
 * FIXUP: return type set to void: only unaffected-register values were returned */
void ClipboardFree(undefined4 *param_1)

{
  undefined4 extraout_EAX;
  undefined4 unaff_EBX;
  
  if (param_1 != (undefined4 *)0x0) {
    if ((void *)*param_1 != (void *)0x0) {
      free((void *)*param_1);
    }
    if ((void *)param_1[1] != (void *)0x0) {
      free((void *)param_1[1]);
    }
    free(param_1);
    return;
  }
  return;
}

/* ClipboardClear @ 0x0804e530, 26 bytes */
void ClipboardClear(undefined4 *param_1)

{
  param_1[5] = 0;
  param_1[4] = 0;
  **(undefined1 **)*param_1 = 0;
  return;
}

/* ClipboardPrint @ 0x0804e550, 68 bytes
 * FIXUP: varargs: replaced 1 &stack0x.. with a va_list started after param_2
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x410-byte frame (a local's address escapes, see apply_frame_emulation) */
void ClipboardPrint(int *param_1,char *param_2,...)

{
  va_list ghidra_va;
  va_start(ghidra_va, param_2);
  unsigned char ghidra_frame[0x410] __attribute__((aligned(16)));
#define local_40c (*(char (*)[1028])(ghidra_frame + 0x4))
  
  ClipboardClear(param_1);
  vsprintf(local_40c,param_2,ghidra_va);
  ClipboardAppend(param_1,local_40c);
  return;
}
#undef local_40c

/* ClipboardAppend @ 0x0804e5a0, 180 bytes
 * FIXUP: varargs: replaced 1 &stack0x.. with a va_list started after param_2
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x420-byte frame (a local's address escapes, see apply_frame_emulation) */
size_t ClipboardAppend(int *param_1,char *param_2,...)

{
  va_list ghidra_va;
  va_start(ghidra_va, param_2);
  int iVar1;
  int iVar2;
  size_t sVar3;
  uint uVar4;
  size_t sVar5;
  char *__s;
  char *__s_00;
  unsigned char ghidra_frame[0x420] __attribute__((aligned(16)));
#define local_41c (*(char (*)[1036])(ghidra_frame + 0x4))
  
  __s_00 = *(char **)(*param_1 + param_1[5] * 4);
  iVar1 = param_1[2];
  iVar2 = param_1[3];
  __s = local_41c;
  vsprintf(__s,param_2,ghidra_va);
  sVar3 = strlen(__s_00);
  sVar5 = sVar3;
  while (local_41c[0] != '\0') {
    if ((iVar1 + -1 <= (int)sVar5) ||
       (sVar3 = CONCAT31((int3)((uint)(iVar1 + -1) >> 8),*__s), *__s == '\n')) {
      __s_00[sVar5] = '\0';
      uVar4 = (iVar2 <= (int)(param_1[5] + 1U)) - 1 & param_1[5] + 1U;
      param_1[5] = uVar4;
      if (uVar4 == param_1[4]) {
        param_1[4] = uVar4 + 1 & (iVar2 <= (int)(uVar4 + 1)) - 1;
      }
      sVar5 = 0;
      __s_00 = *(char **)(*param_1 + uVar4 * 4);
      sVar3 = CONCAT31((int3)((uint)*param_1 >> 8),*__s);
    }
    if ((char)sVar3 != '\n') {
      __s_00[sVar5] = (char)sVar3;
      sVar5 = sVar5 + 1;
    }
    __s = __s + 1;
    local_41c[0] = *__s;
  }
  __s_00[sVar5] = '\0';
  return sVar3;
}
#undef local_41c

