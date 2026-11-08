/*
 * pad-lib.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08054e80-0x080553bb, 11 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"

extern int numpads __asm__("D_082879c4"); /* file-static 0x082879c4 */
extern int *PadHitHook __asm__("D_082879c8"); /* file-static 0x082879c8 */
extern int PadType __asm__("D_082a66e0"); /* file-static 0x082a66e0 */
extern int PadID __asm__("D_082a66e4"); /* file-static 0x082a66e4 */
extern byte padbuf[1032] __asm__("D_082a6700"); /* file-static 0x082a6700 */
extern int padbitflag[4] __asm__("D_082a6b08"); /* file-static 0x082a6b08 */
extern int padoldbitflag[4] __asm__("D_082a6b18"); /* file-static 0x082a6b18 */

/* PadInit @ 0x08054e80, 153 bytes
 * FIXUP: rewrote 1 Ghidra partial-variable accesses (x._O_S_) */
int PadInit(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  if (PadInstalled == 0) {
    memset(padflag,0,0x81);
    PadType = 0;
    iVar1 = 0;
    switch(param_1) {
    case 1:
    case 4:
    case 6:
    case 8:
    case 0x14:
    case 0x15:
    case 0x17:
      iVar2 = install_joystick(-1);
      if (iVar2 == 0) {
        PadReset();
        numpads = num_joysticks;
        iVar1 = (*(uint *)((char *)&joy + 8));
      }
    }
    PadType = param_1;
    if (iVar1 != 0) {
      PadID = param_2;
    }
    PadInstalled = (int)(iVar1 != 0);
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

/* DeviceInit @ 0x08054f20, 6 bytes */
undefined4 DeviceInit(void)

{
  return 1;
}

/* PadReset @ 0x08054f30, 74 bytes */
undefined4 PadReset(void)

{
  int iVar1;
  int iVar2;
  
  memset(padflag,0,0x81);
  if (0 < numpads) {
    iVar2 = 0;
    iVar1 = numpads;
    do {
      *(undefined4 *)((int)padbitflag + iVar2) = 0;
      *(undefined4 *)((int)padoldbitflag + iVar2) = 0;
      iVar2 = iVar2 + 4;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  PadBufClear();
  return 1;
}

/* PadDeInit @ 0x08054f80, 87 bytes */
void PadDeInit(void)

{
  if (PadInstalled != 0) {
    PadRemoveHitHook();
    PadReset();
    switch(PadType) {
    case 1:
    case 4:
    case 6:
    case 8:
    case 0x14:
    case 0x15:
    case 0x17:
      remove_joystick();
    }
    PadInstalled = 0;
    PadType = 0;
    numpads = 0;
  }
  return;
}

/* PadPoll @ 0x08054fe0, 671 bytes */
int PadPoll(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int local_2c;
  int local_28;
  int local_24;
  int local_1c;
  int local_18;
  int local_14;
  
  local_18 = 0;
  if (PadInstalled == 0) {
    iVar4 = 0;
  }
  else {
    if (0 < numpads) {
      iVar2 = 0;
      iVar4 = numpads;
      do {
        *(undefined4 *)((int)padoldbitflag + iVar2) = *(undefined4 *)((int)padbitflag + iVar2);
        *(undefined4 *)((int)padbitflag + iVar2) = 0;
        iVar2 = iVar2 + 4;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    switch(PadType) {
    case 1:
    case 4:
    case 6:
    case 8:
    case 0x14:
    case 0x15:
    case 0x17:
      poll_joystick();
      iVar2 = numpads;
      local_14 = 0;
      if (0 < numpads) {
        local_24 = 0;
        local_28 = 0;
        local_2c = 0x10;
        iVar4 = 0;
        do {
          if (*(int *)(joy + local_24 + 0x18) != 0) {
            *(uint *)((int)padbitflag + iVar4) = *(uint *)((int)padbitflag + iVar4) | 8;
          }
          if (*(int *)(joy + local_24 + 0x1c) != 0) {
            *(uint *)((int)padbitflag + iVar4) = *(uint *)((int)padbitflag + iVar4) | 0x10;
          }
          if (*(int *)(joy + local_24 + 0x28) != 0) {
            *(uint *)((int)padbitflag + iVar4) = *(uint *)((int)padbitflag + iVar4) | 2;
          }
          if (*(int *)(joy + local_2c + 0x1c) != 0) {
            *(uint *)((int)padbitflag + iVar4) = *(uint *)((int)padbitflag + iVar4) | 4;
          }
          iVar5 = 0;
          iVar1 = *(int *)(joy + local_24 + 8);
          if (0 < iVar1) {
            iVar3 = local_28 * 4 + 0xf0;
            do {
              if (*(int *)(joy + iVar3 + 0xc) != 0) {
                *(uint *)((int)padbitflag + iVar4) =
                     *(uint *)((int)padbitflag + iVar4) | 0x20 << ((byte)iVar5 & 0x1f);
              }
              iVar5 = iVar5 + 1;
              iVar3 = iVar3 + 8;
            } while (iVar5 < iVar1);
          }
          local_14 = local_14 + 1;
          local_24 = local_24 + 0x17c;
          local_28 = local_28 + 0x5f;
          local_2c = local_2c + 0x17c;
          iVar4 = iVar4 + 4;
        } while (local_14 < iVar2);
      }
      break;
    default:
      iVar2 = numpads;
    }
    local_14 = 0;
    iVar4 = local_18;
    if (0 < iVar2) {
      local_1c = 0;
      do {
        uVar7 = *(uint *)((int)padbitflag + local_1c) ^ *(uint *)((int)padoldbitflag + local_1c);
        iVar4 = 0;
        if ((local_18 != 0) || (uVar7 != 0)) {
          iVar4 = 1;
        }
        if (uVar7 != 0) {
          uVar6 = 0;
          do {
            if ((uVar7 & 1) != 0) {
              iVar2 = uVar6 + local_14 * 0x20;
              padflag[iVar2] =
                   (byte)(*(int *)((int)padbitflag + local_1c) >> ((byte)uVar6 & 0x1f)) & 1;
              uVar8 = uVar6;
              if ((char)padflag[iVar2] == 0) {
                uVar8 = uVar6 | 0x100;
              }
              if (PadHitHook != (int *)0x0) {
                (*(code *)PadHitHook)(iVar2,(int)(char)padflag[iVar2],uVar6 & 0xff,uVar6 & 0xff);
              }
              PadStuff(uVar8 + local_14 * 0x20);
            }
            uVar7 = (int)uVar7 >> 1;
            uVar6 = uVar6 + 1;
            iVar2 = numpads;
          } while ((int)uVar6 < 0x20);
        }
        local_14 = local_14 + 1;
        local_1c = local_1c + 4;
        local_18 = iVar4;
      } while (local_14 < iVar2);
    }
  }
  return iVar4;
}

/* PadStuff @ 0x08055280, 84 bytes
 * FIXUP: rewrote 9 Ghidra partial-variable accesses (x._O_S_) */
void PadStuff(undefined4 param_1)

{
  if (PadInstalled != 0) {
    *(undefined4 *)(padbuf + (*(uint *)((char *)&padbuf + 1028)) * 4) = param_1;
    (*(uint *)((char *)&padbuf + 1028)) = (0xff < (int)((*(uint *)((char *)&padbuf + 1028)) + 1)) - 1 & (*(uint *)((char *)&padbuf + 1028)) + 1;
    if ((*(uint *)((char *)&padbuf + 1028)) == (*(uint *)((char *)&padbuf + 1024))) {
      (*(uint *)((char *)&padbuf + 1024)) = (*(uint *)((char *)&padbuf + 1028)) + 1 & (0xff < (int)((*(uint *)((char *)&padbuf + 1028)) + 1)) - 1;
    }
  }
  return;
}

/* PadGet @ 0x080552e0, 85 bytes
 * FIXUP: rewrote 8 Ghidra partial-variable accesses (x._O_S_) */
undefined4 PadGet(void)

{
  undefined4 uVar1;
  
  if (PadInstalled == 0) {
    uVar1 = 0;
  }
  else {
    if ((*(uint *)((char *)&padbuf + 1024)) == (*(uint *)((char *)&padbuf + 1028))) {
      do {
        PadPoll();
      } while ((*(uint *)((char *)&padbuf + 1024)) == (*(uint *)((char *)&padbuf + 1028)));
    }
    uVar1 = *(undefined4 *)(padbuf + (*(uint *)((char *)&padbuf + 1024)) * 4);
    (*(uint *)((char *)&padbuf + 1024)) = (*(uint *)((char *)&padbuf + 1024)) + 1 & (0xff < (int)((*(uint *)((char *)&padbuf + 1024)) + 1)) - 1;
  }
  return uVar1;
}

/* PadHit @ 0x08055340, 34 bytes
 * FIXUP: rewrote 2 Ghidra partial-variable accesses (x._O_S_) */
bool PadHit(void)

{
  if (PadInstalled == 0) {
    return false;
  }
  return (*(uint *)((char *)&padbuf + 1024)) != (*(uint *)((char *)&padbuf + 1028));
}

/* PadBufClear @ 0x08055370, 21 bytes */
void PadBufClear(void)

{
  padbuf[0x404] = 0;
  padbuf[0x405] = 0;
  padbuf[0x406] = 0;
  padbuf[0x407] = 0;
  padbuf[0x400] = 0;
  padbuf[0x401] = 0;
  padbuf[0x402] = 0;
  padbuf[0x403] = 0;
  return;
}

/* PadInstallHitHook @ 0x08055390, 31 bytes */
undefined4 PadInstallHitHook(int *param_1)

{
  if (PadHitHook != (int *)0x0) {
    return 0;
  }
  PadHitHook = param_1;
  return 1;
}

/* PadRemoveHitHook @ 0x080553b0, 11 bytes */
void PadRemoveHitHook(void)

{
  PadHitHook = (int *)0x0;
  return;
}

