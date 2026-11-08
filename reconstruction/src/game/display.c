/*
 * display.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0808d940-0x0808dc25, 4 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"

extern int framesskipped_0 __asm__("D_08287a64"); /* file-static 0x08287a64 */
extern int snapcount_1 __asm__("D_08287a68"); /* file-static 0x08287a68 */

/* FrameSkipReset @ 0x0808d940, 30 bytes */
void FrameSkipReset(void)

{
  int *piVar1;
  
  piVar1 = g;
  g[0x7306] = 0;
  piVar1[0x7307] = 0;
  TimerSyncReset();
  return;
}

/* FrameSkipUpdate @ 0x0808d960, 186 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
void FrameSkipUpdate(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  bool bVar4;
  undefined3 extraout_var;
  
  piVar3 = g;
  iVar1 = g[0x7305];
  g[0x7307] = 0;
  if (iVar1 == -1) {
    piVar3[0x7306] = 0;
    bVar4 = TimerGetSync();
    if (((GHIDRA_ZEXT8(bVar4) == 0) || (g[0x82d2] != 0)) || (3 < framesskipped_0)) {
      if (framesskipped_0 == 4) {
        TimerSyncReset();
      }
      framesskipped_0 = 0;
    }
    else {
      g[0x7306] = 1;
      framesskipped_0 = framesskipped_0 + 1;
      TimerSkipSync();
    }
  }
  else {
    iVar2 = piVar3[0x7306];
    piVar3[0x7306] = iVar2 + 1;
    if (iVar1 < iVar2 + 1) {
      piVar3[0x7306] = 0;
    }
  }
  if (g[0x7306] != 0) {
    g[0x7307] = 1;
  }
  return;
}

/* DrawToScreen @ 0x0808da20, 391 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
void DrawToScreen(void)

{
  uint *puVar1;
  bool bVar2;
  int iVar3;
  int *piVar4;
  undefined3 extraout_var;
  
  if (g[0x7307] == 0) {
    if (g[0x7559] == 0) {
      if (g[0x7558] == 0) {
        V_BufToScreenXY((int *)g[0x4139],0,S_Width - V_Width >> 1,S_Height - V_Height >> 1);
        return;
      }
      piVar4 = (int *)g[0x4139];
    }
    else {
      iVar3 = SpriteArrayAccess((int *)g[0x4136],0);
      puVar1 = *(uint **)(iVar3 + 0x24);
      piVar4 = (int *)SpriteArrayAccess((int *)g[0x4138],0);
      iVar3 = piVar4[9];
      if (g[0x7559] == 1) {
        V_DoubleResDiag((int *)puVar1,iVar3);
      }
      if (g[0x7559] == 2) {
        V_DoubleResBlur((int *)puVar1,iVar3);
      }
      if (g[0x7559] == 3) {
        V_DoubleResLines(puVar1,iVar3);
      }
      if ((g[0x7559] == 4) && (bVar2 = GameModeInFightScreen(), GHIDRA_ZEXT8(bVar2) == 0))
      {
        V_DoubleRes(puVar1,iVar3);
      }
      if ((g[0x7558] == 0) || ((V_Width == S_Width && (V_Height == S_Height)))) {
        V_BufToScreenXY((int *)g[0x4138],0,S_Width - *piVar4 >> 1,S_Height - piVar4[1] >> 1);
        return;
      }
      piVar4 = (int *)g[0x4138];
    }
    V_BufToScreenStretch(piVar4,0);
  }
  return;
}

/* ScreenSnap @ 0x0808dbb0, 117 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x20-byte frame (a local's address escapes, see apply_frame_emulation) */
void ScreenSnap(void)

{
  int iVar1;
  undefined4 in_ECX;
  undefined4 extraout_ECX;
  int *piVar2;
  unsigned char ghidra_frame[0x20] __attribute__((aligned(16)));
#define local_1c (*(byte (*)[20])(ghidra_frame + 0x4))
  
  piVar2 = (int *)g[0x4136];
  do {
    sprintf((char *)local_1c,"mugen%i.pcx",snapcount_1,in_ECX);
    snapcount_1 = snapcount_1 + 1;
    iVar1 = access((char *)local_1c,0);
    in_ECX = extraout_ECX;
  } while (iVar1 == 0);
  if ((int *)g[0x4138] != (int *)0x0) {
    piVar2 = (int *)g[0x4138];
  }
  iVar1 = SpriteArrayAccess(piVar2,0);
  save_pcx(local_1c,*(uint **)(iVar1 + 0x24),(undefined1 *)0x0);
  return;
}
#undef local_1c

