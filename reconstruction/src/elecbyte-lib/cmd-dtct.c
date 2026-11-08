/*
 * cmd-dtct.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0804f140-0x0804f9d2, 14 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* KBUpdateHold @ 0x0804f140, 29 bytes */
void KBUpdateHold(int param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = KBGetHoldFlag(param_2);
  *(uint *)(param_1 + 0x650) = uVar1;
  return;
}

/* KBFillBuffer @ 0x0804f160, 571 bytes */
undefined4 KBFillBuffer(int param_1,int param_2,uint param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 local_18;
  int local_14;
  
  local_14 = 0;
  local_18 = 0;
  uVar2 = KBKeyMap(param_1,param_3);
  if ((uVar2 == 0) && (param_3 != 0)) {
    return 0;
  }
  uVar5 = uVar2 >> 0x14;
  uVar6 = uVar2 >> 0x10 & 1;
  iVar3 = KBKeyIndex(uVar2);
  if ((iVar3 != -1) && (uVar6 == 0)) {
    *(int *)(param_2 + 0x60c + iVar3 * 4) = param_4;
  }
  if ((iVar3 != -1) && (uVar6 != 0)) {
    local_14 = param_4 - *(int *)(param_2 + 0x60c + iVar3 * 4);
  }
  if (uVar2 == 0) goto LAB_0804f318;
  uVar4 = uVar2 & 0xffff;
  if (uVar4 != 0x2000) {
    if (uVar4 < 0x2001) {
      if (uVar4 != 0x1000) goto LAB_0804f318;
    }
    else if ((uVar4 != 0x4000) && (uVar4 != 0x8000)) goto LAB_0804f318;
  }
  uVar4 = ((*(int *)(param_1 + 0x7c) != 0) - 1 & 0xfffff000) + 0x1000;
  if (*(int *)(param_1 + 0x80) != 0) {
    uVar4 = uVar4 | 0x2000;
  }
  if (*(int *)(param_1 + 0x88) != 0) {
    uVar4 = uVar4 | 0x8000;
  }
  if (*(int *)(param_1 + 0x84) != 0) {
    uVar4 = uVar4 | 0x4000;
  }
  uVar1 = *(uint *)(param_2 + 0x654);
  if (uVar4 != uVar1) {
    uVar2 = uVar4;
    if (uVar6 == 0) {
      if ((uVar1 != 0) && (uVar1 != uVar4)) {
        KBTimeStuffBuf(param_2,uVar1 | 0x10000,param_4,local_14);
        local_18 = 1;
      }
      *(uint *)(param_2 + 0x654) = uVar4;
    }
    else {
      if ((uVar1 != 0) && (uVar1 != uVar4)) {
        KBTimeStuffBuf(param_2,uVar1 | 0x10000,param_4,local_14);
        local_18 = 1;
      }
      if ((uVar5 & 1) != 0) {
        uVar2 = uVar4 | 0x100000;
      }
      *(uint *)(param_2 + 0x654) = uVar4;
    }
  }
LAB_0804f318:
  if ((uVar2 & 0x9f000) == 0) {
    if (uVar2 == 0) {
      uVar5 = *(uint *)(param_2 + 0x658);
      if (uVar5 != 0) {
        *(undefined4 *)(param_2 + 0x658) = 0;
        uVar2 = uVar5;
      }
    }
    else if (*(uint *)(param_2 + 0x658) == 0) {
      *(uint *)(param_2 + 0x658) = uVar2;
      uVar2 = 0;
    }
    else {
      *(uint *)(param_2 + 0x658) = *(uint *)(param_2 + 0x658) | uVar2;
      uVar2 = 0;
    }
  }
  if ((short)uVar2 != 0) {
    KBTimeStuffBuf(param_2,uVar2,param_4,local_14);
    local_18 = 1;
  }
  return local_18;
}

/* KBClearCommandValidTimes @ 0x0804f3a0, 17 bytes */
void KBClearCommandValidTimes(undefined4 *param_1)

{
  int iVar1;
  
  for (iVar1 = 0x20; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = 0;
    param_1 = param_1 + 1;
  }
  return;
}

/* KBClearCommandLastTimes @ 0x0804f3c0, 20 bytes */
void KBClearCommandLastTimes(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(param_1 + 0x80);
  for (iVar1 = 0x80; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return;
}

/* KBCountdownCommandValidTimes @ 0x0804f3e0, 50 bytes */
void KBCountdownCommandValidTimes(int param_1,char param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    if ((*(char *)(iVar2 + param_1) != '\0') &&
       (bVar1 = *(char *)(iVar2 + param_1) - param_2, *(byte *)(iVar2 + param_1) = bVar1,
       (int)(uint)bVar1 < param_3)) {
      *(char *)(iVar2 + param_1) = (char)param_3;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x80);
  return;
}

/* KBCommandIsValid @ 0x0804f420, 18 bytes */
bool KBCommandIsValid(int param_1,int param_2)

{
  return *(char *)(param_2 + param_1) != '\0';
}

/* KBGetCommand @ 0x0804f440, 34 bytes */
void KBGetCommand(int param_1,int *param_2,int param_3,undefined4 param_4)

{
  KBGetCommandSpecial(param_1,param_2,param_3,param_4,0xf);
  return;
}

/* KBGetCommandSpecial @ 0x0804f470, 309 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x20-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 KBGetCommandSpecial(int param_1,int *param_2,int param_3,undefined4 param_4,uint param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  unsigned char ghidra_frame[0x20] __attribute__((aligned(16)));
#define local_14 (*(int *)(ghidra_frame + 0xc))
  
  iVar4 = *(int *)(param_3 + 0x608);
  if (iVar4 == *(int *)(param_3 + 0x604)) {
    iVar2 = param_2[2];
  }
  else {
    do {
      iVar3 = 0;
      *(uint *)(param_3 + 0x608) = iVar4 + 1U & (0x7f < (int)(iVar4 + 1U)) - 1;
      iVar2 = param_2[2];
      if (0 < iVar2) {
        iVar4 = 0;
        do {
          if ((*(uint *)(*param_2 + 0x14 + iVar4) & param_5) != 0) {
            iVar2 = PatternMatch(param_3,(int *)(iVar4 + *param_2),&local_14);
            if (iVar2 != 0) {
              iVar1 = *(int *)(*param_2 + 0x10 + iVar4);
              iVar2 = iVar1 * 4 + 0x80;
              if (*(int *)(iVar2 + param_1) < local_14) {
                *(undefined1 *)(iVar1 + param_1) = *(undefined1 *)(*param_2 + 0xc + iVar4);
                *(undefined4 *)(iVar2 + param_1) = param_4;
              }
            }
            iVar2 = param_2[2];
          }
          iVar3 = iVar3 + 1;
          iVar4 = iVar4 + 0x18;
        } while (iVar3 < iVar2);
      }
      iVar4 = *(int *)(param_3 + 0x608);
    } while (iVar4 != *(int *)(param_3 + 0x604));
  }
  iVar4 = 0;
  if (0 < iVar2) {
    iVar3 = 0;
    do {
      iVar1 = *param_2;
      if ((((*(uint *)(iVar1 + 0x14 + iVar3) & param_5) != 0) &&
          ((*(byte *)(*(int *)(iVar1 + iVar3) + 2) & 2) != 0)) && (*(int *)(iVar1 + 4 + iVar3) == 1)
         ) {
        iVar2 = PatternMatch(param_3,(int *)(iVar3 + iVar1),&local_14);
        if (iVar2 != 0) {
          iVar2 = *(int *)(*param_2 + 0x10 + iVar3);
          *(undefined1 *)(iVar2 + param_1) = 1;
          *(undefined4 *)(param_1 + 0x80 + iVar2 * 4) = param_4;
        }
        iVar2 = param_2[2];
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0x18;
    } while (iVar4 < iVar2);
  }
  return 0;
}
#undef local_14

/* KBGetHoldFlag @ 0x0804f5b0, 170 bytes */
uint KBGetHoldFlag(int param_1)

{
  uint uVar1;
  
  uVar1 = ((*(int *)(param_1 + 0x7c) != 0) - 1 & 0xfffff000) + 0x1000;
  if (*(int *)(param_1 + 0x80) != 0) {
    uVar1 = uVar1 | 0x2000;
  }
  if (*(int *)(param_1 + 0x84) != 0) {
    uVar1 = uVar1 | 0x4000;
  }
  if (*(int *)(param_1 + 0x88) != 0) {
    uVar1 = uVar1 | 0x8000;
  }
  if (*(int *)(param_1 + 0x8c) != 0) {
    uVar1 = uVar1 | 0x10;
  }
  if (*(int *)(param_1 + 0x90) != 0) {
    uVar1 = uVar1 | 0x20;
  }
  if (*(int *)(param_1 + 0x94) != 0) {
    uVar1 = uVar1 | 0x40;
  }
  if (*(int *)(param_1 + 0x98) != 0) {
    uVar1 = uVar1 | 0x80;
  }
  if (*(int *)(param_1 + 0x9c) != 0) {
    uVar1 = uVar1 | 0x100;
  }
  if (*(int *)(param_1 + 0xa0) != 0) {
    uVar1 = uVar1 | 0x200;
  }
  if (*(int *)(param_1 + 0xa4) != 0) {
    uVar1 = uVar1 | 0x400;
  }
  return uVar1;
}

/* KBKeyMap @ 0x0804f660, 152 bytes */
uint KBKeyMap(undefined4 param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = 0;
  uVar2 = 0;
  if (param_2 != 0) {
    if ((param_2 & 0x10) != 0) {
      uVar2 = 0x10000;
    }
    if ((param_2 & 0x20) != 0) {
      uVar2 = uVar2 | 0x100000;
    }
    switch(param_2 & 0xf) {
    case 1:
      uVar1 = 0x1000;
      break;
    case 2:
      uVar1 = 0x2000;
      break;
    case 3:
      uVar1 = 0x4000;
      break;
    case 4:
      uVar1 = 0x8000;
      break;
    case 5:
      uVar1 = 0x10;
      break;
    case 6:
      uVar1 = 0x20;
      break;
    case 7:
      uVar1 = 0x40;
      break;
    case 8:
      uVar1 = 0x80;
      break;
    case 9:
      uVar1 = 0x100;
      break;
    case 10:
      uVar1 = 0x200;
      break;
    case 0xb:
      uVar1 = 0x400;
    }
    uVar1 = uVar1 | uVar2;
  }
  return uVar1;
}

/* KBKeyIndex @ 0x0804f700, 28 bytes */
int KBKeyIndex(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if ((param_1 >> ((byte)iVar1 & 0x1f) & 1U) != 0) {
      return iVar1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x10);
  return -1;
}

/* CharMatch @ 0x0804f720, 270 bytes */
undefined4 CharMatch(int param_1,int param_2,uint param_3)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  bool bVar4;
  
  if ((param_3 & 0x20000) == 0) {
    uVar3 = *(uint *)(param_2 * 4 + param_1);
    if ((((int)param_3 >> 0x16) * 4 <= *(int *)(param_1 + 0x400 + param_2 * 4)) &&
       ((uVar3 & 0x110000) != 0x100000)) {
      if ((param_3 & 0x8f000) == 0) {
        if ((((param_3 & 0xfff) != 0) && ((param_3 & 0x10000) == (uVar3 & 0x10000))) &&
           ((uVar3 & param_3 & 0xffff) == (param_3 & 0xffff))) {
          return 1;
        }
      }
      else {
        uVar1 = param_3 & 0x1ffff;
        if ((param_3 & 0x40000) == 0) {
          bVar4 = uVar3 == uVar1;
        }
        else {
          if ((uVar3 & uVar1) != uVar1) goto LAB_0804f829;
          bVar4 = (uVar3 & 0x10000) == (param_3 & 0x10000);
        }
LAB_0804f7fb:
        if (bVar4) goto LAB_0804f791;
      }
    }
LAB_0804f829:
    uVar2 = 0;
  }
  else {
    uVar3 = param_3 & 0x8f000;
    if (uVar3 == 0) {
      if (((param_3 & 0xfff) == 0) || ((param_3 & 0xfff & *(uint *)(param_1 + 0x650) & 0xfff) == 0))
      goto LAB_0804f829;
    }
    else {
      uVar1 = *(uint *)(param_1 + 0x650) & 0x8f000;
      if (((param_3 & 0x80000) == 0) || (uVar1 != 0)) {
        if ((param_3 & 0x40000) == 0) {
          bVar4 = uVar1 == uVar3;
        }
        else {
          bVar4 = (uVar1 & uVar3) == uVar3;
        }
        goto LAB_0804f7fb;
      }
    }
LAB_0804f791:
    uVar2 = 1;
  }
  return uVar2;
}

/* PatternMatch @ 0x0804f830, 300 bytes */
undefined4 PatternMatch(int param_1,int *param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint local_1c;
  int local_14;
  
  iVar1 = *param_2;
  iVar2 = param_2[2];
  local_1c = 0;
  iVar6 = param_2[1] + -1;
  iVar5 = *(int *)(param_1 + 0x608);
  if (iVar5 < 1) {
    local_14 = *(int *)(param_1 + 0x3fc);
    uVar7 = *(uint *)(iVar1 + iVar6 * 8);
    iVar3 = 0x7f;
  }
  else {
    local_14 = *(int *)(param_1 + 0x1fc + iVar5 * 4);
    uVar7 = *(uint *)(iVar1 + iVar6 * 8);
    iVar3 = iVar5 + -1;
  }
  iVar3 = CharMatch(param_1,iVar3,uVar7);
  if (iVar3 != 0) {
    iVar3 = iVar5 * 4 + 0x200;
    do {
      if (iVar5 == *(int *)(param_1 + 0x600)) {
        return 0;
      }
      iVar3 = iVar3 + -4;
      iVar5 = iVar5 + -1;
      if (iVar5 < 0) {
        iVar3 = 0x3fc;
        iVar5 = 0x7f;
      }
      if ((iVar2 < local_14 - *(int *)(param_1 + iVar3)) &&
         ((*(byte *)(iVar1 + 2 + iVar6 * 8) & 2) == 0)) {
        return 0;
      }
      iVar4 = CharMatch(param_1,iVar5,*(uint *)(iVar1 + iVar6 * 8));
      if (iVar4 == 0) {
        if ((local_1c & 1) != 0) {
          return 0;
        }
        local_1c = 0;
      }
      else {
        local_1c = *(uint *)(iVar1 + 4 + iVar6 * 8);
        iVar6 = iVar6 + -1;
        if (iVar6 < 0) {
          if (param_3 != (undefined4 *)0x0) {
            *param_3 = *(undefined4 *)(iVar3 + param_1);
          }
          return 1;
        }
      }
    } while ((local_14 - *(int *)(param_1 + iVar3) <= iVar2) ||
            ((*(byte *)(iVar1 + 2 + iVar6 * 8) & 2) == 0));
  }
  return 0;
}

/* KBTimeStuffBuf @ 0x0804f960, 114 bytes */
void KBTimeStuffBuf(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  
  *(undefined4 *)(param_1 + *(int *)(param_1 + 0x604) * 4) = param_2;
  *(undefined4 *)(param_1 + 0x200 + *(int *)(param_1 + 0x604) * 4) = param_3;
  *(undefined4 *)(param_1 + 0x400 + *(int *)(param_1 + 0x604) * 4) = param_4;
  uVar1 = *(int *)(param_1 + 0x604) + 1;
  uVar1 = (0x7f < (int)uVar1) - 1 & uVar1;
  *(uint *)(param_1 + 0x604) = uVar1;
  if (uVar1 == *(uint *)(param_1 + 0x600)) {
    *(uint *)(param_1 + 0x600) = uVar1 + 1 & (0x7f < (int)(uVar1 + 1)) - 1;
  }
  return;
}

