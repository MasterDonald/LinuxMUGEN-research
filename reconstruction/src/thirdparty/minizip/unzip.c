/*
 * unzip.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x080802e0-0x08081579, 23 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* unzlocal_getByte @ 0x080802e0, 74 bytes
 * REVIEW: pid-unaff_
 * FIXUP: hand-written override (see overrides/) */
/* OVERRIDE: written by hand from the assembly at 0x080802e0-0x0808032a.
 * Reason: the one-byte buffer lives in a prologue "push %ebx" slot
 * (0x7(%esp) after the pushes); Ghidra rendered it as &stack0xfffffffb and
 * read the byte back as "unaff_EBX >> 0x18".
 * The function matches the public minizip 0.15 unzlocal_getByte (Gilles
 * Vollant, zlib licence): read one byte with fread; on success store it and
 * return UNZ_OK (0); otherwise return UNZ_ERRNO (-1) if ferror() is set,
 * else UNZ_EOF (0). VERIFIED: "sete %al; dec %eax" at 0x8080322 computes
 * (ferror == 0) - 1. */
int unzlocal_getByte(_IO_FILE *param_1, uint *param_2)
{
  unsigned char c;

  if (fread(&c, 1, 1, param_1) == 1) {                    /* 0x80802f1 */
    *param_2 = (uint)c;                                   /* movzbl-style: xor edx; mov dl */
    return 0;
  }
  return (ferror(param_1) == 0) - 1;
}

/* unzlocal_getShort @ 0x08080330, 84 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x10-byte frame (a local's address escapes, see apply_frame_emulation) */
int unzlocal_getShort(_IO_FILE *param_1,uint *param_2)

{
  uint uVar1;
  int iVar2;
  unsigned char ghidra_frame[0x10] __attribute__((aligned(16)));
#define local_10 (*(uint *)(ghidra_frame + 0x0))
  
  iVar2 = unzlocal_getByte(param_1,&local_10);
  uVar1 = local_10;
  if (iVar2 == 0) {
    iVar2 = unzlocal_getByte(param_1,&local_10);
  }
  *param_2 = uVar1 + local_10 * 0x100 & (iVar2 != 0) - 1;
  return iVar2;
}
#undef local_10

/* unzlocal_getLong @ 0x08080390, 142 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x10-byte frame (a local's address escapes, see apply_frame_emulation) */
int unzlocal_getLong(_IO_FILE *param_1,uint *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  unsigned char ghidra_frame[0x10] __attribute__((aligned(16)));
#define local_10 (*(uint *)(ghidra_frame + 0x0))
  
  iVar2 = unzlocal_getByte(param_1,&local_10);
  uVar1 = local_10;
  if (iVar2 == 0) {
    iVar2 = unzlocal_getByte(param_1,&local_10);
  }
  iVar3 = local_10 * 0x100;
  if (iVar2 == 0) {
    iVar2 = unzlocal_getByte(param_1,&local_10);
  }
  iVar4 = local_10 * 0x10000;
  if (iVar2 == 0) {
    iVar2 = unzlocal_getByte(param_1,&local_10);
  }
  *param_2 = uVar1 + iVar3 + iVar4 + local_10 * 0x1000000 & (iVar2 != 0) - 1;
  return iVar2;
}
#undef local_10

/* strcmpcasenosensitive_internal @ 0x08080420, 92 bytes */
int strcmpcasenosensitive_internal(char *param_1,char *param_2)

{
  char cVar1;
  char cVar2;
  
  while( true ) {
    cVar1 = *param_1;
    param_1 = param_1 + 1;
    cVar2 = *param_2;
    param_2 = param_2 + 1;
    if ((byte)(cVar1 + 0x9fU) < 0x1a) {
      cVar1 = cVar1 + -0x20;
    }
    if ((byte)(cVar2 + 0x9fU) < 0x1a) {
      cVar2 = cVar2 + -0x20;
    }
    if (cVar1 == '\0') {
      return (cVar2 == '\0') - 1;
    }
    if (cVar2 == '\0') {
      return 1;
    }
    if (cVar1 < cVar2) break;
    if (cVar2 < cVar1) {
      return 1;
    }
  }
  return -1;
}

/* unzStringFileNameCompare @ 0x08080480, 56 bytes */
int unzStringFileNameCompare(char *param_1,char *param_2,int param_3)

{
  int iVar1;
  
  if (param_3 == 0) {
    param_3 = 1;
  }
  if (param_3 == 1) {
    iVar1 = strcmp(param_1,param_2);
    return iVar1;
  }
  iVar1 = strcmpcasenosensitive_internal(param_1,param_2);
  return iVar1;
}

/* unzlocal_SearchCentralDir @ 0x080804c0, 280 bytes */
int unzlocal_SearchCentralDir(FILE *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  void *ptr;
  size_t sVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  size_t size;
  int local_1c;
  uint local_18;
  
  local_18 = 0xffff;
  local_1c = 0;
  iVar2 = fseek(param_1,0,2);
  if (iVar2 == 0) {
    uVar3 = ftell(param_1);
    if (uVar3 < 0xffff) {
      local_18 = uVar3;
    }
    uVar7 = 4;
    ptr = malloc(0x404);
    if (ptr != (void *)0x0) {
      while (uVar7 < local_18) {
        uVar1 = uVar7 + 0x400;
        uVar7 = local_18;
        if (uVar1 <= local_18) {
          uVar7 = uVar1;
        }
        iVar2 = uVar3 - uVar7;
        size = uVar3 - iVar2;
        if (0x404 < size) {
          size = 0x404;
        }
        iVar5 = fseek(param_1,iVar2,0);
        if ((iVar5 != 0) || (sVar4 = fread(ptr,size,1,param_1), sVar4 != 1)) break;
        iVar5 = size - 3;
        do {
          iVar6 = iVar5;
          iVar5 = iVar6 + -1;
          if (iVar6 < 1) goto LAB_0808056e;
        } while ((((*(char *)(iVar5 + (int)ptr) != 'P') || (*(char *)(iVar6 + (int)ptr) != 'K')) ||
                 (*(char *)(iVar6 + 1 + (int)ptr) != '\x05')) ||
                (*(char *)(iVar6 + 2 + (int)ptr) != '\x06'));
        local_1c = iVar2 + iVar5;
LAB_0808056e:
        if (local_1c != 0) break;
      }
      if (ptr == (void *)0x0) {
        return local_1c;
      }
      free(ptr);
      return local_1c;
    }
  }
  return 0;
}

/* unzOpen @ 0x080805e0, 444 bytes
 * FIXUP: frame emulation: 12 stack locals placed at their original offsets in a 0xa0-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 * unzOpen(char *param_1)

{
  FILE *__stream;
  undefined4 *puVar1;
  uint __off;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  FILE **ppFVar9;
  undefined4 *puVar10;
  unsigned char ghidra_frame[0xa0] __attribute__((aligned(16)));
#define local_9c (*(uint *)(ghidra_frame + 0x4))
#define local_98 (*(uint *)(ghidra_frame + 0x8))
#define local_94 (*(uint *)(ghidra_frame + 0xc))
#define local_90 (*(uint *)(ghidra_frame + 0x10))
#define local_8c (*(FILE **)(ghidra_frame + 0x14))
#define local_88 (*(uint *)(ghidra_frame + 0x18))
#define local_84 (*(uint *)(ghidra_frame + 0x1c))
#define local_80 (*(int *)(ghidra_frame + 0x20))
#define local_70 (*(uint *)(ghidra_frame + 0x30))
#define local_6c (*(uint *)(ghidra_frame + 0x34))
#define local_68 (*(uint (*)[22])(ghidra_frame + 0x38))
#define local_10 (*(undefined4 *)(ghidra_frame + 0x90))
  
  __stream = fopen(param_1,"rb");
  if (__stream == (FILE *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    __off = unzlocal_SearchCentralDir(__stream);
    iVar2 = fseek(__stream,__off,0);
    iVar3 = unzlocal_getLong(__stream,&local_90);
    iVar4 = unzlocal_getShort(__stream,&local_94);
    iVar5 = unzlocal_getShort(__stream,&local_98);
    iVar6 = unzlocal_getShort(__stream,&local_88);
    iVar7 = unzlocal_getShort(__stream,&local_9c);
    uVar8 = (__off != 0) - 1 | (iVar2 == 0) - 1 | (iVar3 == 0) - 1 | (iVar4 == 0) - 1 |
            (iVar5 == 0) - 1 | (iVar6 == 0) - 1 | (iVar7 == 0) - 1;
    if (((local_9c != local_88) || (local_98 != 0)) || (local_94 != 0)) {
      uVar8 = 0xffffff99;
    }
    iVar2 = unzlocal_getLong(__stream,&local_6c);
    iVar3 = unzlocal_getLong(__stream,local_68);
    iVar4 = unzlocal_getShort(__stream,&local_84);
    uVar8 = uVar8 | (iVar2 == 0) - 1 | (iVar3 == 0) - 1 | (iVar4 == 0) - 1;
    if ((__off < local_6c + local_68[0]) && (uVar8 == 0)) {
      uVar8 = 0xffffff99;
    }
    if (uVar8 == 0) {
      local_80 = (__off - local_68[0]) - local_6c;
      local_10 = 0;
      local_8c = __stream;
      local_70 = __off;
      puVar1 = malloc(0x80);
      ppFVar9 = &local_8c;
      puVar10 = puVar1;
      for (iVar2 = 0x20; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar10 = *ppFVar9;
        ppFVar9 = ppFVar9 + 1;
        puVar10 = puVar10 + 1;
      }
      unzGoToFirstFile(puVar1);
    }
    else {
      fclose(__stream);
      puVar1 = (undefined4 *)0x0;
    }
  }
  return puVar1;
}
#undef local_9c
#undef local_98
#undef local_94
#undef local_90
#undef local_8c
#undef local_88
#undef local_84
#undef local_80
#undef local_70
#undef local_6c
#undef local_68
#undef local_10

/* unzClose @ 0x080807a0, 63 bytes */
undefined4 unzClose(void *param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0xffffff9a;
  if (param_1 != (void *)0x0) {
    if (*(int *)((int)param_1 + 0x7c) != 0) {
      unzCloseCurrentFile((int)param_1);
    }
    fclose(*(FILE **)param_1);
    free(param_1);
    uVar1 = 0;
  }
  return uVar1;
}

/* unzGetGlobalInfo @ 0x080807e0, 34 bytes */
undefined4 unzGetGlobalInfo(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    return 0xffffff9a;
  }
  uVar1 = *(undefined4 *)(param_1 + 8);
  *param_2 = *(undefined4 *)(param_1 + 4);
  param_2[1] = uVar1;
  return 0;
}

/* unzlocal_DosDateToTmuDate @ 0x08080810, 83 bytes */
void unzlocal_DosDateToTmuDate(uint param_1,int *param_2)

{
  param_2[3] = param_1 >> 0x10 & 0x1f;
  param_2[5] = (param_1 >> 0x19) + 0x7bc;
  param_2[4] = ((param_1 >> 0x10 & 0x1e0) >> 5) - 1;
  param_2[2] = (param_1 & 0xf800) >> 0xb;
  param_2[1] = (param_1 & 0x7e0) >> 5;
  *param_2 = (param_1 & 0x1f) * 2;
  return;
}

/* unzlocal_GetCurrentFileInfoInternal @ 0x08080870, 955 bytes
 * FIXUP: frame emulation: 14 stack locals placed at their original offsets in a 0x80-byte frame (a local's address escapes, see apply_frame_emulation) */
uint unzlocal_GetCurrentFileInfoInternal
               (undefined4 *param_1,uint *param_2,uint *param_3,size_t param_4,uint param_5,
               size_t param_6,void *param_7,size_t param_8,void *param_9)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  size_t sVar17;
  uint uVar18;
  void *pvVar19;
  uint *puVar20;
  unsigned char ghidra_frame[0x80] __attribute__((aligned(16)));
#define local_74 (*(uint *)(ghidra_frame + 0xc))
#define local_70 (*(uint *)(ghidra_frame + 0x10))
#define local_6c (*(uint (*)[4])(ghidra_frame + 0x14))
#define local_5c (*(uint *)(ghidra_frame + 0x24))
#define local_58 (*(uint *)(ghidra_frame + 0x28))
#define local_54 (*(uint *)(ghidra_frame + 0x2c))
#define local_50 (*(uint *)(ghidra_frame + 0x30))
#define local_4c (*(uint *)(ghidra_frame + 0x34))
#define local_48 (*(void **)(ghidra_frame + 0x38))
#define local_44 (*(void **)(ghidra_frame + 0x3c))
#define local_40 (*(uint *)(ghidra_frame + 0x40))
#define local_3c (*(uint *)(ghidra_frame + 0x44))
#define local_38 (*(uint *)(ghidra_frame + 0x48))
#define local_34 (*(int (*)[9])(ghidra_frame + 0x4c))
  
  uVar1 = 0xffffff9a;
  if (param_1 != (undefined4 *)0x0) {
    iVar2 = fseek((FILE *)*param_1,param_1[3] + param_1[5],0);
    uVar1 = (iVar2 == 0) - 1;
    if (uVar1 == 0) {
      iVar2 = unzlocal_getLong((_IO_FILE *)*param_1,&local_70);
      if (iVar2 == 0) {
        if (local_70 != 0x2014b50) {
          uVar1 = 0xffffff99;
        }
      }
      else {
        uVar1 = 0xffffffff;
      }
    }
    iVar2 = unzlocal_getShort((_IO_FILE *)*param_1,local_6c);
    iVar3 = unzlocal_getShort((_IO_FILE *)*param_1,local_6c + 1);
    iVar4 = unzlocal_getShort((_IO_FILE *)*param_1,local_6c + 2);
    iVar5 = unzlocal_getShort((_IO_FILE *)*param_1,local_6c + 3);
    iVar6 = unzlocal_getLong((_IO_FILE *)*param_1,&local_5c);
    unzlocal_DosDateToTmuDate(local_5c,local_34);
    iVar7 = unzlocal_getLong((_IO_FILE *)*param_1,&local_58);
    iVar8 = unzlocal_getLong((_IO_FILE *)*param_1,&local_54);
    iVar9 = unzlocal_getLong((_IO_FILE *)*param_1,&local_50);
    iVar10 = unzlocal_getShort((_IO_FILE *)*param_1,&local_4c);
    iVar11 = unzlocal_getShort((_IO_FILE *)*param_1,(uint *)&local_48);
    iVar12 = unzlocal_getShort((_IO_FILE *)*param_1,(uint *)&local_44);
    iVar13 = unzlocal_getShort((_IO_FILE *)*param_1,&local_40);
    iVar14 = unzlocal_getShort((_IO_FILE *)*param_1,&local_3c);
    iVar15 = unzlocal_getLong((_IO_FILE *)*param_1,&local_38);
    iVar16 = unzlocal_getLong((_IO_FILE *)*param_1,&local_74);
    uVar1 = uVar1 | (iVar2 == 0) - 1 | (iVar3 == 0) - 1 | (iVar4 == 0) - 1 | (iVar5 == 0) - 1 |
            (iVar6 == 0) - 1 | (iVar7 == 0) - 1 | (iVar8 == 0) - 1 | (iVar9 == 0) - 1 |
            (iVar10 == 0) - 1 | (iVar11 == 0) - 1 | (iVar12 == 0) - 1 | (iVar13 == 0) - 1 |
            (iVar14 == 0) - 1 | (iVar15 == 0) - 1 | (iVar16 == 0) - 1;
    uVar18 = local_4c;
    if ((uVar1 == 0) && (param_4 != 0)) {
      uVar18 = param_5;
      if (local_4c < param_5) {
        *(undefined1 *)(local_4c + param_4) = 0;
        uVar18 = local_4c;
      }
      if ((local_4c != 0) && (param_5 != 0)) {
        sVar17 = fread((void *)param_4,uVar18,1,(FILE *)*param_1);
        uVar1 = (sVar17 == 1) - 1;
      }
      uVar18 = local_4c - uVar18;
    }
    if ((uVar1 == 0) && (param_6 != 0)) {
      pvVar19 = local_48;
      if (param_7 <= local_48) {
        pvVar19 = param_7;
      }
      if (uVar18 != 0) {
        iVar2 = fseek((FILE *)*param_1,uVar18,1);
        if (iVar2 == 0) {
          uVar18 = 0;
        }
        else {
          uVar1 = 0xffffffff;
        }
      }
      if ((local_48 != (void *)0x0) && (param_7 != (void *)0x0)) {
        sVar17 = fread((void *)param_6,(size_t)pvVar19,1,(FILE *)*param_1);
        uVar1 = uVar1 | (sVar17 == 1) - 1;
      }
      local_48 = (void *)((int)local_48 - (int)pvVar19);
    }
    if ((uVar1 == 0) && (param_8 != 0)) {
      pvVar19 = param_9;
      if (local_44 < param_9) {
        *(undefined1 *)((int)local_44 + param_8) = 0;
        pvVar19 = local_44;
      }
      if ((uVar18 + (int)local_48 != 0) &&
         (iVar2 = fseek((FILE *)*param_1,uVar18 + (int)local_48,1), iVar2 != 0)) {
        uVar1 = 0xffffffff;
      }
      if ((local_44 != (void *)0x0) && (param_9 != (void *)0x0)) {
        sVar17 = fread((void *)param_8,(size_t)pvVar19,1,(FILE *)*param_1);
        uVar1 = uVar1 | (sVar17 == 1) - 1;
      }
    }
    if ((uVar1 == 0) && (param_2 != (uint *)0x0)) {
      puVar20 = local_6c;
      for (iVar2 = 0x14; iVar2 != 0; iVar2 = iVar2 + -1) {
        *param_2 = *puVar20;
        puVar20 = puVar20 + 1;
        param_2 = param_2 + 1;
      }
    }
    if ((uVar1 == 0) && (param_3 != (uint *)0x0)) {
      *param_3 = local_74;
    }
  }
  return uVar1;
}
#undef local_74
#undef local_70
#undef local_6c
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef local_34

/* unzGetCurrentFileInfo @ 0x08080c30, 54 bytes */
uint unzGetCurrentFileInfo
               (undefined4 *param_1,uint *param_2,size_t param_3,uint param_4,size_t param_5,
               void *param_6,size_t param_7,void *param_8)

{
  uint uVar1;
  
  uVar1 = unzlocal_GetCurrentFileInfoInternal
                    (param_1,param_2,(uint *)0x0,param_3,param_4,param_5,param_6,param_7,param_8);
  return uVar1;
}

/* unzGoToFirstFile @ 0x08080c70, 75 bytes */
uint unzGoToFirstFile(undefined4 *param_1)

{
  uint uVar1;
  
  uVar1 = 0xffffff9a;
  if (param_1 != (undefined4 *)0x0) {
    param_1[5] = param_1[9];
    param_1[4] = 0;
    uVar1 = unzlocal_GetCurrentFileInfoInternal
                      (param_1,param_1 + 10,param_1 + 0x1e,0,0,0,(void *)0x0,0,(void *)0x0);
    param_1[6] = (uint)(uVar1 == 0);
  }
  return uVar1;
}

/* unzGoToNextFile @ 0x08080cc0, 119 bytes */
uint unzGoToNextFile(undefined4 *param_1)

{
  uint uVar1;
  
  uVar1 = 0xffffff9a;
  if (param_1 != (undefined4 *)0x0) {
    if (param_1[6] == 0) {
      uVar1 = 0xffffff9c;
    }
    else {
      uVar1 = 0xffffff9c;
      if (param_1[4] + 1 != param_1[1]) {
        param_1[4] = param_1[4] + 1;
        param_1[5] = param_1[0x13] + param_1[0x12] + param_1[0x14] + param_1[5] + 0x2e;
        uVar1 = unzlocal_GetCurrentFileInfoInternal
                          (param_1,param_1 + 10,param_1 + 0x1e,0,0,0,(void *)0x0,0,(void *)0x0);
        param_1[6] = (uint)(uVar1 == 0);
      }
    }
  }
  return uVar1;
}

/* unzLocateFile @ 0x08080d40, 198 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x130-byte frame (a local's address escapes, see apply_frame_emulation) */
uint unzLocateFile(undefined4 *param_1,char *param_2,int param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  size_t sVar4;
  int iVar5;
  unsigned char ghidra_frame[0x130] __attribute__((aligned(16)));
#define local_12c (*(char (*)[284])(ghidra_frame + 0x4))
  
  uVar3 = 0xffffff9a;
  if (param_1 != (undefined4 *)0x0) {
    sVar4 = strlen(param_2);
    if (sVar4 < 0x100) {
      if (param_1[6] == 0) {
        uVar3 = 0xffffff9c;
      }
      else {
        uVar1 = param_1[5];
        uVar2 = param_1[4];
        uVar3 = unzGoToFirstFile(param_1);
        if (uVar3 == 0) {
          do {
            unzGetCurrentFileInfo
                      (param_1,(uint *)0x0,(size_t)local_12c,0x100,0,(void *)0x0,0,(void *)0x0);
            iVar5 = unzStringFileNameCompare(local_12c,param_2,param_3);
            if (iVar5 == 0) {
              return 0;
            }
            uVar3 = unzGoToNextFile(param_1);
          } while (uVar3 == 0);
        }
        param_1[4] = uVar2;
        param_1[5] = uVar1;
      }
    }
    else {
      uVar3 = 0xffffff9a;
    }
  }
  return uVar3;
}
#undef local_12c

/* unzlocal_CheckCurrentFileCoherencyHeader @ 0x08080e10, 554 bytes
 * FIXUP: frame emulation: 5 stack locals placed at their original offsets in a 0x30-byte frame (a local's address escapes, see apply_frame_emulation) */
uint unzlocal_CheckCurrentFileCoherencyHeader
               (undefined4 *param_1,int *param_2,int *param_3,uint *param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  unsigned char ghidra_frame[0x30] __attribute__((aligned(16)));
#define local_24 (*(uint *)(ghidra_frame + 0xc))
#define local_20 (*(uint *)(ghidra_frame + 0x10))
#define local_1c (*(uint *)(ghidra_frame + 0x14))
#define local_18 (*(uint *)(ghidra_frame + 0x18))
#define local_14 (*(uint *)(ghidra_frame + 0x1c))
  
  uVar3 = 0;
  *param_2 = 0;
  *param_3 = 0;
  *param_4 = 0;
  iVar1 = fseek((FILE *)*param_1,param_1[3] + param_1[0x1e],0);
  if (iVar1 == 0) {
    iVar1 = unzlocal_getLong((_IO_FILE *)*param_1,&local_14);
    if (iVar1 == 0) {
      if (local_14 != 0x4034b50) {
        uVar3 = 0xffffff99;
      }
    }
    else {
      uVar3 = 0xffffffff;
    }
    iVar1 = unzlocal_getShort((_IO_FILE *)*param_1,&local_18);
    iVar2 = unzlocal_getShort((_IO_FILE *)*param_1,&local_1c);
    uVar3 = uVar3 | (iVar1 == 0) - 1 | (iVar2 == 0) - 1;
    iVar1 = unzlocal_getShort((_IO_FILE *)*param_1,&local_18);
    if (iVar1 == 0) {
      if ((uVar3 == 0) && (local_18 != param_1[0xd])) {
        uVar3 = 0xffffff99;
      }
    }
    else {
      uVar3 = 0xffffffff;
    }
    if (((uVar3 == 0) && (param_1[0xd] != 0)) && (param_1[0xd] != 8)) {
      uVar3 = 0xffffff99;
    }
    iVar1 = unzlocal_getLong((_IO_FILE *)*param_1,&local_18);
    uVar3 = uVar3 | (iVar1 == 0) - 1;
    iVar1 = unzlocal_getLong((_IO_FILE *)*param_1,&local_18);
    if (iVar1 == 0) {
      if (((uVar3 == 0) && (local_18 != param_1[0xf])) && ((local_1c & 8) == 0)) {
        uVar3 = 0xffffff99;
      }
    }
    else {
      uVar3 = 0xffffffff;
    }
    iVar1 = unzlocal_getLong((_IO_FILE *)*param_1,&local_18);
    if (iVar1 == 0) {
      if (((uVar3 == 0) && (local_18 != param_1[0x10])) && ((local_1c & 8) == 0)) {
        uVar3 = 0xffffff99;
      }
    }
    else {
      uVar3 = 0xffffffff;
    }
    iVar1 = unzlocal_getLong((_IO_FILE *)*param_1,&local_18);
    if (iVar1 == 0) {
      if (((uVar3 == 0) && (local_18 != param_1[0x11])) && ((local_1c & 8) == 0)) {
        uVar3 = 0xffffff99;
      }
    }
    else {
      uVar3 = 0xffffffff;
    }
    iVar1 = unzlocal_getShort((_IO_FILE *)*param_1,&local_20);
    if (iVar1 == 0) {
      if ((uVar3 == 0) && (local_20 != param_1[0x12])) {
        uVar3 = 0xffffff99;
      }
    }
    else {
      uVar3 = 0xffffffff;
    }
    *param_2 = *param_2 + local_20;
    iVar1 = unzlocal_getShort((_IO_FILE *)*param_1,&local_24);
    uVar3 = uVar3 | (iVar1 == 0) - 1;
    *param_3 = local_20 + param_1[0x1e] + 0x1e;
    *param_4 = local_24;
    *param_2 = *param_2 + local_24;
  }
  else {
    uVar3 = 0xffffffff;
  }
  return uVar3;
}
#undef local_24
#undef local_20
#undef local_1c
#undef local_18
#undef local_14

/* unzOpenCurrentFile @ 0x08081040, 340 bytes
 * FIXUP: frame emulation: 3 stack locals placed at their original offsets in a 0x20-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 unzOpenCurrentFile(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 *__ptr;
  void *pvVar4;
  undefined8 uVar5;
  unsigned char ghidra_frame[0x20] __attribute__((aligned(16)));
#define local_14 (*(int *)(ghidra_frame + 0xc))
#define local_10 (*(int *)(ghidra_frame + 0x10))
#define local_c (*(uint *)(ghidra_frame + 0x14))
  
  uVar2 = 0xffffff9a;
  if (param_1 != (undefined4 *)0x0) {
    if (param_1[6] == 0) {
      uVar2 = 0xffffff9a;
    }
    else {
      if (param_1[0x1f] != 0) {
        unzCloseCurrentFile((int)param_1);
      }
      uVar3 = unzlocal_CheckCurrentFileCoherencyHeader(param_1,&local_14,&local_10,&local_c);
      if (uVar3 == 0) {
        __ptr = malloc(0x6c);
        uVar2 = 0xffffff98;
        if (__ptr != (undefined4 *)0x0) {
          pvVar4 = malloc(0x4000);
          *__ptr = pvVar4;
          __ptr[0x11] = local_10;
          __ptr[0x12] = local_c;
          __ptr[0x13] = 0;
          if (pvVar4 == (void *)0x0) {
            free(__ptr);
            uVar2 = 0xffffff98;
          }
          else {
            __ptr[0x10] = 0;
            iVar1 = param_1[0xd];
            uVar2 = param_1[0xf];
            __ptr[0x19] = iVar1;
            __ptr[0x15] = uVar2;
            uVar2 = *param_1;
            __ptr[0x14] = 0;
            __ptr[0x18] = uVar2;
            __ptr[0x1a] = param_1[3];
            __ptr[6] = 0;
            if (iVar1 != 0) {
              __ptr[9] = 0;
              __ptr[10] = 0;
              __ptr[0xb] = 0;
              uVar5 = inflateInit2_((int)(__ptr + 1),-0xf,"1.1.3",0x38);
              if ((int)uVar5 == 0) {
                __ptr[0x10] = 1;
              }
            }
            param_1[0x1f] = __ptr;
            __ptr[0x16] = param_1[0x10];
            __ptr[0x17] = param_1[0x11];
            __ptr[0xf] = local_14 + param_1[0x1e] + 0x1e;
            uVar2 = 0;
            __ptr[2] = 0;
          }
        }
      }
      else {
        uVar2 = 0xffffff99;
      }
    }
  }
  return uVar2;
}
#undef local_14
#undef local_10
#undef local_c

/* unzReadCurrentFile @ 0x080811a0, 497 bytes */
uint unzReadCurrentFile(int param_1,int param_2,uint param_3)

{
  int *piVar1;
  byte *pbVar2;
  int iVar3;
  size_t sVar4;
  uint uVar5;
  uint uVar6;
  size_t size;
  uint local_18;
  uint local_14;
  
  local_14 = 0;
  local_18 = 0;
  if (param_1 == 0) {
    uVar5 = 0xffffff9a;
  }
  else {
    piVar1 = *(int **)(param_1 + 0x7c);
    uVar5 = 0xffffff9a;
    if (piVar1 != (int *)0x0) {
      if (*piVar1 == 0) {
        uVar5 = 0xffffff9c;
      }
      else if (param_3 == 0) {
LAB_080811f5:
        uVar5 = 0;
      }
      else {
        piVar1[5] = param_3;
        piVar1[4] = param_2;
        if ((uint)piVar1[0x17] < param_3) {
          piVar1[5] = piVar1[0x17];
        }
        iVar3 = piVar1[5];
        while (iVar3 != 0) {
          if ((piVar1[2] == 0) && (uVar5 = piVar1[0x16], uVar5 != 0)) {
            size = 0x4000;
            if (uVar5 < 0x4000) {
              size = uVar5;
            }
            if (size == 0) goto LAB_080811f5;
            iVar3 = fseek((FILE *)piVar1[0x18],piVar1[0x1a] + piVar1[0xf],0);
            if ((iVar3 != 0) ||
               (sVar4 = fread((void *)*piVar1,size,1,(FILE *)piVar1[0x18]), sVar4 != 1)) {
              return 0xffffffff;
            }
            piVar1[0xf] = piVar1[0xf] + size;
            piVar1[0x16] = piVar1[0x16] - size;
            piVar1[1] = *piVar1;
            piVar1[2] = size;
          }
          if (piVar1[0x19] == 0) {
            uVar5 = piVar1[5];
            if ((uint)piVar1[2] <= (uint)piVar1[5]) {
              uVar5 = piVar1[2];
            }
            uVar6 = 0;
            if (uVar5 != 0) {
              do {
                *(undefined1 *)(uVar6 + piVar1[4]) = *(undefined1 *)(uVar6 + piVar1[1]);
                uVar6 = uVar6 + 1;
              } while (uVar6 < uVar5);
            }
            uVar6 = crc32(piVar1[0x14],(byte *)piVar1[4],uVar5);
            piVar1[0x14] = uVar6;
            piVar1[0x17] = piVar1[0x17] - uVar5;
            piVar1[2] = piVar1[2] - uVar5;
            local_18 = local_18 + uVar5;
            piVar1[5] = piVar1[5] - uVar5;
            piVar1[4] = piVar1[4] + uVar5;
            piVar1[1] = piVar1[1] + uVar5;
            piVar1[6] = piVar1[6] + uVar5;
          }
          else {
            iVar3 = piVar1[6];
            pbVar2 = (byte *)piVar1[4];
            local_14 = inflate(piVar1 + 1,2);
            uVar6 = piVar1[6] - iVar3;
            uVar5 = crc32(piVar1[0x14],pbVar2,uVar6);
            local_18 = local_18 + uVar6;
            piVar1[0x14] = uVar5;
            piVar1[0x17] = piVar1[0x17] - uVar6;
            if (local_14 == 1) goto LAB_08081376;
            if (local_14 != 0) break;
          }
          iVar3 = piVar1[5];
        }
        uVar5 = local_14;
        if (local_14 == 0) {
LAB_08081376:
          uVar5 = local_18;
        }
      }
    }
  }
  return uVar5;
}

/* unztell @ 0x080813a0, 25 bytes */
undefined4 unztell(int param_1)

{
  if ((param_1 != 0) && (*(int *)(param_1 + 0x7c) != 0)) {
    return *(undefined4 *)(*(int *)(param_1 + 0x7c) + 0x18);
  }
  return 0xffffff9a;
}

/* unzeof @ 0x080813c0, 32 bytes */
uint unzeof(int param_1)

{
  if ((param_1 != 0) && (*(int *)(param_1 + 0x7c) != 0)) {
    return (uint)(*(int *)(*(int *)(param_1 + 0x7c) + 0x5c) == 0);
  }
  return 0xffffff9a;
}

/* unzGetLocalExtrafield @ 0x080813e0, 147 bytes */
uint unzGetLocalExtrafield(int param_1,size_t param_2,uint param_3)

{
  int iVar1;
  uint size;
  int iVar2;
  size_t sVar3;
  uint uVar4;
  
  if (param_1 == 0) {
    size = 0xffffff9a;
  }
  else {
    iVar1 = *(int *)(param_1 + 0x7c);
    size = 0xffffff9a;
    if (iVar1 != 0) {
      size = *(int *)(iVar1 + 0x48) - *(int *)(iVar1 + 0x4c);
      if (param_2 != 0) {
        uVar4 = size;
        if (param_3 <= size) {
          uVar4 = param_3;
        }
        if (uVar4 == 0) {
          size = 0;
        }
        else {
          iVar2 = fseek(*(FILE **)(iVar1 + 0x60),*(int *)(iVar1 + 0x4c) + *(int *)(iVar1 + 0x44),0);
          if (iVar2 == 0) {
            sVar3 = fread((void *)param_2,size,1,*(FILE **)(iVar1 + 0x60));
            size = (sVar3 == 1) - 1 | uVar4;
          }
          else {
            size = 0xffffffff;
          }
        }
      }
    }
  }
  return size;
}

/* unzCloseCurrentFile @ 0x08081480, 123 bytes */
undefined4 unzCloseCurrentFile(int param_1)

{
  undefined4 *__ptr;
  undefined4 uVar1;
  
  uVar1 = 0xffffff9a;
  if ((param_1 != 0) && (__ptr = *(undefined4 **)(param_1 + 0x7c), __ptr != (undefined4 *)0x0)) {
    uVar1 = 0;
    if ((__ptr[0x17] == 0) && (__ptr[0x14] != __ptr[0x15])) {
      uVar1 = 0xffffff97;
    }
    if ((void *)*__ptr != (void *)0x0) {
      free((void *)*__ptr);
    }
    *__ptr = 0;
    if (__ptr[0x10] != 0) {
      inflateEnd((int)(__ptr + 1));
    }
    __ptr[0x10] = 0;
    free(__ptr);
    *(undefined4 *)(param_1 + 0x7c) = 0;
  }
  return uVar1;
}

/* unzGetGlobalComment @ 0x08081500, 121 bytes */
uint unzGetGlobalComment(undefined4 *param_1,undefined1 *param_2,uint param_3)

{
  int iVar1;
  size_t sVar2;
  uint size;
  
  if (param_1 == (undefined4 *)0x0) {
    return 0xffffff9a;
  }
  size = param_3;
  if ((uint)param_1[2] < param_3) {
    size = param_1[2];
  }
  iVar1 = fseek((FILE *)*param_1,param_1[7] + 0x16,0);
  if (iVar1 == 0) {
    if (size != 0) {
      *param_2 = 0;
      sVar2 = fread(param_2,size,1,(FILE *)*param_1);
      if (sVar2 != 1) goto LAB_08081559;
    }
    if ((param_2 != (undefined1 *)0x0) && ((uint)param_1[2] < param_3)) {
      param_2[param_1[2]] = 0;
    }
  }
  else {
LAB_08081559:
    size = 0xffffffff;
  }
  return size;
}

