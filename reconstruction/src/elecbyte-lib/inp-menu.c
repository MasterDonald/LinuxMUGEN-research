/*
 * inp-menu.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08053d30-0x08053ed2, 1 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* KBIMenuGetKey @ 0x08053d30, 418 bytes
 * FIXUP: frame emulation: 12 stack locals placed at their original offsets in a 0x70-byte frame (a local's address escapes, see apply_frame_emulation) */
uint * KBIMenuGetKey(uint *param_1,int param_2,int param_3,int param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  uint *puVar5;
  int iVar6;
  unsigned char ghidra_frame[0x70] __attribute__((aligned(16)));
#define local_64 (*(uint *)(ghidra_frame + 0xc))
#define local_60 (*(uint *)(ghidra_frame + 0x10))
#define local_5c (*(uint (*)[4])(ghidra_frame + 0x14))
#define local_4c (*(int *)(ghidra_frame + 0x24))
#define local_48 (*(int *)(ghidra_frame + 0x28))
#define local_44 (*(int *)(ghidra_frame + 0x2c))
#define local_40 (*(int *)(ghidra_frame + 0x30))
#define local_3c (*(int *)(ghidra_frame + 0x34))
#define local_38 (*(int *)(ghidra_frame + 0x38))
#define local_34 (*(int *)(ghidra_frame + 0x3c))
#define local_30 (*(int *)(ghidra_frame + 0x40))
#define local_2c (*(int *)(ghidra_frame + 0x44))
  
  uVar3 = 0;
  local_64 = 0;
  local_60 = 0;
  uVar1 = local_60;
  if (0 < param_4) {
    do {
      puVar4 = *(uint **)(param_3 + uVar3 * 4);
      puVar5 = local_5c;
      for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      iVar2 = 0;
      iVar6 = 0xc;
      do {
        uVar1 = KBToUInp(*(uint *)((int)local_5c + iVar2));
        *(uint *)((int)local_5c + iVar2) = uVar1;
        iVar2 = iVar2 + 4;
        iVar6 = iVar6 + -1;
      } while (-1 < iVar6);
      if (param_2 == local_5c[1]) {
        local_64 = local_64 | 1;
      }
      else if (param_2 == local_5c[2]) {
        local_64 = local_64 | 2;
      }
      else if (param_2 == local_5c[3]) {
        local_64 = local_64 | 4;
      }
      else if (param_2 == local_4c) {
        local_64 = local_64 | 8;
      }
      else if (param_2 == local_48) {
        local_64 = local_64 | 0x10;
      }
      else if (param_2 == local_44) {
        local_64 = local_64 | 0x20;
      }
      else if (param_2 == local_40) {
        local_64 = local_64 | 0x40;
      }
      else if (param_2 == local_3c) {
        local_64 = local_64 | 0x80;
      }
      else if (param_2 == local_38) {
        local_64 = local_64 | 0x100;
      }
      else if (param_2 == local_34) {
        local_64 = local_64 | 0x200;
      }
      else if (param_2 == local_30) {
        local_64 = local_64 | 0x400;
      }
      else if (param_2 == local_2c) {
        local_64 = local_64 | 0x800;
      }
      uVar1 = uVar3;
    } while ((local_64 == 0) && (uVar3 = uVar3 + 1, uVar1 = local_60, (int)uVar3 < param_4));
  }
  local_60 = uVar1;
  param_1[1] = local_60;
  *param_1 = local_64;
  return param_1;
}
#undef local_64
#undef local_60
#undef local_5c
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c

