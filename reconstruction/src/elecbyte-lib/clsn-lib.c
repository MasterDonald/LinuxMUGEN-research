/*
 * clsn-lib.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0804e660-0x0804f136, 16 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* ClsnArrayNew @ 0x0804e660, 89 bytes */
undefined4 ClsnArrayNew(size_t param_1)

{
  undefined4 *puVar1;
  int iVar2;
  
  if ((0 < (int)param_1) && (puVar1 = (undefined4 *)ecalloc(1,0x14), puVar1 != (undefined4 *)0x0)) {
    *puVar1 = 1;
    puVar1[1] = param_1;
    puVar1[4] = 1;
    iVar2 = ecalloc(param_1,0x14);
    puVar1[2] = iVar2;
    if (iVar2 != 0) {
      return puVar1;
    }
    ClsnArrayFree(puVar1);
  }
  return 0;
}

/* ClsnArrayFree @ 0x0804e6c0, 57 bytes */
undefined4 ClsnArrayFree(void *param_1)

{
  undefined4 in_EAX;
  int iVar1;
  undefined4 extraout_EAX;
  
  if ((param_1 != (void *)0x0) &&
     (iVar1 = *(int *)((int)param_1 + 0x10) + -1, *(int *)((int)param_1 + 0x10) = iVar1, iVar1 < 1))
  {
    if (*(void **)((int)param_1 + 8) != (void *)0x0) {
      free(*(void **)((int)param_1 + 8));
    }
    free(param_1);
    return extraout_EAX;
  }
  return in_EAX;
}

/* ClsnArrayCopy @ 0x0804e700, 75 bytes */
undefined4 * ClsnArrayCopy(undefined4 *param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  puVar1 = (undefined4 *)ClsnArrayNew(param_1[1]);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1[1] = param_1[1];
    puVar1[3] = param_1[3];
    *puVar1 = *param_1;
    puVar3 = (undefined4 *)param_1[2];
    puVar4 = (undefined4 *)puVar1[2];
    for (uVar2 = param_1[1] * 5 & 0x3fffffff; uVar2 != 0; uVar2 = uVar2 - 1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar4 = puVar4 + 1;
    }
  }
  return puVar1;
}

/* ClsnArrayInstance @ 0x0804e750, 12 bytes */
int ClsnArrayInstance(int param_1)

{
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
  return param_1;
}

/* ClsnArrayAdd @ 0x0804e760, 79 bytes */
bool ClsnArrayAdd(int param_1,undefined4 *param_2)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0xc);
  bVar2 = iVar3 < *(int *)(param_1 + 4);
  if (bVar2) {
    iVar1 = *(int *)(param_1 + 8);
    iVar3 = iVar3 * 0x14;
    *(undefined4 *)(iVar1 + iVar3) = *param_2;
    *(undefined4 *)(iVar1 + 4 + iVar3) = param_2[1];
    *(undefined4 *)(iVar1 + 8 + iVar3) = param_2[2];
    *(undefined4 *)(iVar1 + 0xc + iVar3) = param_2[3];
    *(undefined4 *)(iVar1 + 0x10 + iVar3) = param_2[4];
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
  }
  return bVar2;
}

/* ClsnArrayAddRect @ 0x0804e7b0, 67 bytes
 * FIXUP: frame emulation: 5 stack locals placed at their original offsets in a 0x30-byte frame (a local's address escapes, see apply_frame_emulation) */
void ClsnArrayAddRect(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                     undefined4 param_5)

{

  unsigned char ghidra_frame[0x30] __attribute__((aligned(16)));
#define local_2c (*(undefined4 *)(ghidra_frame + 0x4))
#define local_28 (*(undefined4 *)(ghidra_frame + 0x8))
#define local_24 (*(undefined4 *)(ghidra_frame + 0xc))
#define local_20 (*(undefined4 *)(ghidra_frame + 0x10))
#define local_1c (*(undefined4 *)(ghidra_frame + 0x14))
  
  local_1c = param_5;
  local_2c = 0;
  local_28 = param_2;
  local_24 = param_3;
  local_20 = param_4;
  ClsnArrayAdd(param_1,&local_2c);
  return;
}
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c

/* ClsnParseLine @ 0x0804e800, 1016 bytes
 * FIXUP: 1 data addresses written as literals replaced by data-image references
 * FIXUP: 4 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
void * ClsnParseLine(int param_1,int param_2)

{
  byte bVar1;
  uint uVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  char cVar7;
  uint local_2c;
  uint local_28;
  uint local_24;
  int local_20;
  
  cVar7 = '\0';
  local_20 = 5;
  if (*(char *)(param_1 + 5) != '\0') {
    if (*(char *)(param_1 + 5) == ':') {
      cVar7 = ':';
    }
    else {
      do {
        local_20 = local_20 + 1;
        cVar7 = *(char *)(local_20 + param_1);
        if (cVar7 == '\0') break;
      } while (cVar7 != ':');
    }
  }
  if (cVar7 != '\0') {
    do {
      local_20 = local_20 + 1;
    } while ((*(byte *)(__ctype_b + 1 + *(char *)(local_20 + param_1) * 2) & 0x20) != 0);
    if ((*(byte *)(__ctype_b + 1 + *(char *)(local_20 + param_1) * 2) & 8) != 0) {
      uVar2 = __strtol_internal((byte *)(param_1 + local_20),(undefined4 *)0x0,10,0);
      pvVar3 = (void *)ClsnArrayNew(uVar2);
      if (pvVar3 != (void *)0x0) {
        local_20 = 0;
        if (*(int *)((int)pvVar3 + 4) < 1) {
          return pvVar3;
        }
LAB_0804e930:
        iVar4 = TPAccessNextLine(param_2);
        if (iVar4 == 0) {
LAB_0804e908:
          ClsnArrayFree(pvVar3);
        }
        else {
          iVar5 = strimatchlen(iVar4,(int)&DAT_08276ee8,4);
          if (iVar5 != 0) {
            cVar7 = *(char *)(iVar4 + 5);
            iVar5 = 5;
            if (cVar7 != '=') {
              iVar5 = 5;
              do {
                if (cVar7 == '\0') goto LAB_0804e908;
                iVar5 = iVar5 + 1;
                cVar7 = *(char *)(iVar5 + iVar4);
              } while (cVar7 != '=');
            }
            while( true ) {
              iVar5 = iVar5 + 1;
              cVar7 = *(char *)(iVar5 + iVar4);
              if (((byte)(cVar7 - 0x30U) < 10) || (cVar7 == '-')) break;
              if (cVar7 == '\0') goto LAB_0804e908;
            }
            local_24 = __strtol_internal((byte *)(iVar5 + iVar4),(undefined4 *)0x0,10,0);
            cVar7 = ',';
            bVar1 = *(byte *)(iVar5 + iVar4);
            if (bVar1 != 0x2c) {
              if (bVar1 == 0) {
                cVar7 = '\0';
              }
              else {
                do {
                  iVar5 = iVar5 + 1;
                  cVar7 = *(char *)(iVar5 + iVar4);
                  if (cVar7 == ',') break;
                } while (cVar7 != '\0');
              }
            }
            do {
              if (((byte)(cVar7 - 0x30U) < 10) || (cVar7 == '-')) goto LAB_0804e9ec;
              if (cVar7 == '\0') goto LAB_0804e908;
              iVar5 = iVar5 + 1;
              cVar7 = *(char *)(iVar5 + iVar4);
            } while( true );
          }
        }
      }
    }
  }
  return (void *)0x0;
LAB_0804e9ec:
  local_28 = __strtol_internal((byte *)(iVar5 + iVar4),(undefined4 *)0x0,10,0);
  cVar7 = ',';
  bVar1 = *(byte *)(iVar5 + iVar4);
  if (bVar1 != 0x2c) {
    if (bVar1 == 0) {
      cVar7 = '\0';
    }
    else {
      do {
        iVar5 = iVar5 + 1;
        cVar7 = *(char *)(iVar5 + iVar4);
        if (cVar7 == ',') break;
      } while (cVar7 != '\0');
    }
  }
  do {
    if (((byte)(cVar7 - 0x30U) < 10) || (cVar7 == '-')) break;
    if (cVar7 == '\0') goto LAB_0804e908;
    iVar5 = iVar5 + 1;
    cVar7 = *(char *)(iVar5 + iVar4);
  } while( true );
  uVar2 = __strtol_internal((byte *)(iVar5 + iVar4),(undefined4 *)0x0,10,0);
  cVar7 = ',';
  bVar1 = *(byte *)(iVar5 + iVar4);
  if (bVar1 != 0x2c) {
    if (bVar1 == 0) {
      cVar7 = '\0';
    }
    else {
      do {
        iVar5 = iVar5 + 1;
        cVar7 = *(char *)(iVar5 + iVar4);
        if (cVar7 == ',') break;
      } while (cVar7 != '\0');
    }
  }
  do {
    if (((byte)(cVar7 - 0x30U) < 10) || (cVar7 == '-')) break;
    if (cVar7 == '\0') goto LAB_0804e908;
    iVar5 = iVar5 + 1;
    cVar7 = *(char *)(iVar5 + iVar4);
  } while( true );
  uVar6 = __strtol_internal((byte *)(iVar5 + iVar4),(undefined4 *)0x0,10,0);
  local_2c = uVar2;
  if ((int)uVar2 < (int)local_24) {
    local_2c = local_24;
    local_24 = uVar2;
  }
  uVar2 = uVar6;
  if ((int)uVar6 < (int)local_28) {
    uVar2 = local_28;
    local_28 = uVar6;
  }
  if ((GHIDRA_I2F(clsnxscale) != 1.0) || (GHIDRA_I2F(clsnyscale) != 1.0)) {
    uVar2 = (uint)GHIDRA_FIST32((float10)(int)uVar2 * GHIDRA_I2F(clsnyscale));
    local_2c = (uint)GHIDRA_FIST32((float10)(int)local_2c * GHIDRA_I2F(clsnxscale));
    local_28 = (uint)GHIDRA_FIST32((float10)(int)local_28 * GHIDRA_I2F(clsnyscale));
    local_24 = (uint)GHIDRA_FIST32((float10)(int)local_24 * GHIDRA_I2F(clsnxscale));
  }
  ClsnArrayAddRect((int)pvVar3,local_24,local_28,local_2c,uVar2);
  local_20 = local_20 + 1;
  if (*(int *)((int)pvVar3 + 4) <= local_20) {
    return pvVar3;
  }
  goto LAB_0804e930;
}

/* ClsnMixDetectRectIndiv @ 0x0804ec00, 124 bytes */
undefined4 ClsnMixDetectRectIndiv(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  if (0 < *(int *)(param_2 + 4)) {
    iVar4 = 0;
    do {
      bVar2 = false;
      iVar1 = *(int *)(param_2 + 8) + iVar4;
      if ((((*(int *)(param_1 + 4) <= param_3 + *(int *)(iVar1 + 0xc)) &&
           (param_3 + *(int *)(iVar1 + 4) <= *(int *)(param_1 + 0xc))) &&
          (*(int *)(param_1 + 8) <= param_4 + *(int *)(iVar1 + 0x10))) &&
         (param_4 + *(int *)(iVar1 + 8) <= *(int *)(param_1 + 0x10))) {
        bVar2 = true;
      }
      if (bVar2) {
        return iVar3;
      }
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + 0x14;
    } while (iVar3 < *(int *)(param_2 + 4));
  }
  return 0xffffffff;
}

/* ClsnMixDetectRect @ 0x0804ec80, 126 bytes */
undefined4 ClsnMixDetectRect(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  if (0 < *(int *)(param_2 + 4)) {
    iVar4 = 0;
    do {
      bVar2 = false;
      iVar1 = *(int *)(param_2 + 8) + iVar4;
      if ((((*(int *)(param_1 + 4) <= param_3 + *(int *)(iVar1 + 0xc)) &&
           (param_3 + *(int *)(iVar1 + 4) <= *(int *)(param_1 + 0xc))) &&
          (*(int *)(param_1 + 8) <= param_4 + *(int *)(iVar1 + 0x10))) &&
         (param_4 + *(int *)(iVar1 + 8) <= *(int *)(param_1 + 0x10))) {
        bVar2 = true;
      }
      if (bVar2) {
        return 1;
      }
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + 0x14;
    } while (iVar3 < *(int *)(param_2 + 4));
  }
  return 0;
}

/* ClsnMixDetectRectHFlip1 @ 0x0804ed00, 158 bytes */
undefined4 ClsnMixDetectRectHFlip1(int param_1,int param_2,int param_3,int param_4)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int local_1c;
  
  iVar3 = 0;
  if (0 < *(int *)(param_2 + 4)) {
    local_1c = 0;
    do {
      iVar2 = local_1c + *(int *)(param_2 + 8);
      bVar1 = false;
      if ((((-*(int *)(param_1 + 0xc) <= param_3 + *(int *)(iVar2 + 0xc)) &&
           (param_3 + *(int *)(iVar2 + 4) <= -*(int *)(param_1 + 4))) &&
          (*(int *)(param_1 + 8) <= param_4 + *(int *)(iVar2 + 0x10))) &&
         (param_4 + *(int *)(iVar2 + 8) <= *(int *)(param_1 + 0x10))) {
        bVar1 = true;
      }
      if (bVar1) {
        return 1;
      }
      iVar3 = iVar3 + 1;
      local_1c = local_1c + 0x14;
    } while (iVar3 < *(int *)(param_2 + 4));
  }
  return 0;
}

/* ClsnMixDetectRectHFlipAll @ 0x0804eda0, 158 bytes */
undefined4 ClsnMixDetectRectHFlipAll(int param_1,int param_2,int param_3,int param_4)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int local_1c;
  
  iVar3 = 0;
  if (0 < *(int *)(param_2 + 4)) {
    local_1c = 0;
    do {
      iVar2 = local_1c + *(int *)(param_2 + 8);
      bVar1 = false;
      if ((((-*(int *)(param_1 + 0xc) <= param_3 - *(int *)(iVar2 + 4)) &&
           (param_3 - *(int *)(iVar2 + 0xc) <= -*(int *)(param_1 + 4))) &&
          (*(int *)(param_1 + 8) <= param_4 + *(int *)(iVar2 + 0x10))) &&
         (param_4 + *(int *)(iVar2 + 8) <= *(int *)(param_1 + 0x10))) {
        bVar1 = true;
      }
      if (bVar1) {
        return 1;
      }
      iVar3 = iVar3 + 1;
      local_1c = local_1c + 0x14;
    } while (iVar3 < *(int *)(param_2 + 4));
  }
  return 0;
}

/* ClsnArrayDetectRect @ 0x0804ee40, 114 bytes */
undefined4 ClsnArrayDetectRect(int *param_1,int *param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if ((((param_1 != (int *)0x0) && (param_2 != (int *)0x0)) && (*param_1 != 0)) &&
     ((*param_2 != 0 && (iVar2 = 0, 0 < param_1[1])))) {
    iVar3 = 0;
    do {
      iVar1 = ClsnMixDetectRect(iVar3 + param_1[2],(int)param_2,param_3,param_4);
      if (iVar1 != 0) {
        return 1;
      }
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 0x14;
    } while (iVar2 < param_1[1]);
  }
  return 0;
}

/* ClsnArrayDetectRectFlip @ 0x0804eec0, 365 bytes */
undefined4
ClsnArrayDetectRectFlip(int *param_1,int *param_2,int param_3,int param_4,int param_5,int param_6)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if ((((param_1 != (int *)0x0) && (param_2 != (int *)0x0)) && (*param_1 != 0)) && (*param_2 != 0))
  {
    if ((param_5 == 0) && (param_6 == 0)) {
      uVar1 = ClsnArrayDetectRect(param_1,param_2,param_3,param_4);
      return uVar1;
    }
    if (((param_5 == 1) && (param_6 == 0)) && (iVar3 = 0, 0 < param_1[1])) {
      iVar4 = 0;
      do {
        iVar2 = ClsnMixDetectRectHFlip1(iVar4 + param_1[2],(int)param_2,param_3,param_4);
        if (iVar2 != 0) {
          return 1;
        }
        iVar3 = iVar3 + 1;
        iVar4 = iVar4 + 0x14;
      } while (iVar3 < param_1[1]);
    }
    if (((param_5 == 0) && (param_6 == 1)) && (iVar3 = 0, 0 < param_2[1])) {
      iVar4 = 0;
      do {
        iVar2 = ClsnMixDetectRectHFlip1(iVar4 + param_2[2],(int)param_1,-param_3,-param_4);
        if (iVar2 != 0) {
          return 1;
        }
        iVar3 = iVar3 + 1;
        iVar4 = iVar4 + 0x14;
      } while (iVar3 < param_2[1]);
    }
    if (((param_5 == 1) && (param_6 == 1)) && (iVar3 = 0, 0 < param_1[1])) {
      iVar4 = 0;
      do {
        iVar2 = ClsnMixDetectRectHFlipAll(iVar4 + param_1[2],(int)param_2,param_3,param_4);
        if (iVar2 != 0) {
          return 1;
        }
        iVar3 = iVar3 + 1;
        iVar4 = iVar4 + 0x14;
      } while (iVar3 < param_1[1]);
    }
  }
  return 0;
}

/* ClsnDetectRect @ 0x0804f030, 74 bytes */
undefined4 ClsnDetectRect(int param_1,int param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((((*(int *)(param_1 + 4) <= param_3 + *(int *)(param_2 + 0xc)) &&
       (param_3 + *(int *)(param_2 + 4) <= *(int *)(param_1 + 0xc))) &&
      (*(int *)(param_1 + 8) <= param_4 + *(int *)(param_2 + 0x10))) &&
     (param_4 + *(int *)(param_2 + 8) <= *(int *)(param_1 + 0x10))) {
    uVar1 = 1;
  }
  return uVar1;
}

/* ClsnDetectRectHFlip1 @ 0x0804f080, 86 bytes */
undefined4 ClsnDetectRectHFlip1(int param_1,int param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((((-*(int *)(param_1 + 0xc) <= param_3 + *(int *)(param_2 + 0xc)) &&
       (param_3 + *(int *)(param_2 + 4) <= -*(int *)(param_1 + 4))) &&
      (*(int *)(param_1 + 8) <= param_4 + *(int *)(param_2 + 0x10))) &&
     (param_4 + *(int *)(param_2 + 8) <= *(int *)(param_1 + 0x10))) {
    uVar1 = 1;
  }
  return uVar1;
}

/* ClsnDetectRectHFlipAll @ 0x0804f0e0, 86 bytes */
undefined4 ClsnDetectRectHFlipAll(int param_1,int param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if ((((-*(int *)(param_1 + 0xc) <= param_3 - *(int *)(param_2 + 4)) &&
       (param_3 - *(int *)(param_2 + 0xc) <= -*(int *)(param_1 + 4))) &&
      (*(int *)(param_1 + 8) <= param_4 + *(int *)(param_2 + 0x10))) &&
     (param_4 + *(int *)(param_2 + 8) <= *(int *)(param_1 + 0x10))) {
    uVar1 = 1;
  }
  return uVar1;
}

