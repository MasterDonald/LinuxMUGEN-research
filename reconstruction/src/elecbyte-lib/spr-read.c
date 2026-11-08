/*
 * spr-read.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0805bf20-0x0805cd6f, 12 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"

extern int ReadMode __asm__("D_08287a0c"); /* file-static 0x08287a0c */
extern int BufferedReadMode __asm__("D_08287a10"); /* file-static 0x08287a10 */

/* SpriteSetReadMode @ 0x0805bf20, 10 bytes */
void SpriteSetReadMode(int param_1)

{
  ReadMode = param_1;
  return;
}

/* SpriteSetBufReadMode @ 0x0805bf30, 10 bytes */
void SpriteSetBufReadMode(int param_1)

{
  BufferedReadMode = param_1;
  return;
}

/* SpriteReadFile @ 0x0805bf40, 317 bytes */
int * SpriteReadFile(char *param_1)

{
  FILE *stream;
  size_t __size;
  void *ptr;
  size_t sVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  
  if (BufferedReadMode == 0) {
    piVar2 = (int *)MFfopenFile(param_1,"rb");
    if (piVar2 == (int *)0x0) {
      return (int *)0x0;
    }
  }
  else {
    stream = fopen(param_1,"rb");
    if (stream == (FILE *)0x0) {
      return (int *)0x0;
    }
    __size = ffilelength(stream);
    ptr = malloc(__size);
    if (ptr == (void *)0x0) {
      fclose(stream);
      return (int *)0x0;
    }
    sVar1 = fread(ptr,__size,1,stream);
    if (sVar1 == 0) {
      fclose(stream);
      free(ptr);
      return (int *)0x0;
    }
    fclose(stream);
    piVar2 = MFfopenMem((int)ptr,__size);
    if (piVar2 == (int *)0x0) {
      free(ptr);
      return (int *)0x0;
    }
    piVar2[6] = 1;
  }
  MFfseek(piVar2,0,0);
  iVar3 = CheckExtension(param_1);
  if (iVar3 == 1) {
    piVar4 = SpriteReadPCXPtr(piVar2,0,0);
  }
  else {
    if (iVar3 != 2) {
      return (int *)0x0;
    }
    piVar4 = SpriteReadSFFPtr(piVar2);
  }
  if (piVar4 == (int *)0x0) {
    MFfclose(piVar2);
    return (int *)0x0;
  }
  MFfclose(piVar2);
  return piVar4;
}

/* SpriteReadSFFPtr @ 0x0805c080, 180 bytes
 * FIXUP: 1 data addresses written as literals replaced by data-image references
 * FIXUP: frame emulation: 2 stack locals placed at their original offsets in a 0x220-byte frame (a local's address escapes, see apply_frame_emulation) */
int * SpriteReadSFFPtr(int *param_1)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  int *piVar4;
  byte *pbVar5;
  byte *pbVar6;
  bool bVar7;
  bool bVar8;
  unsigned char ghidra_frame[0x220] __attribute__((aligned(16)));
#define local_21c (*(byte (*)[12])(ghidra_frame + 0x4))
#define local_210 (*(int *)(ghidra_frame + 0x10))
  
  piVar4 = (int *)0x0;
  iVar1 = MFftell(param_1);
  sVar2 = MFfread(local_21c,0x200,1,param_1);
  bVar7 = false;
  bVar8 = sVar2 == 0;
  if (!bVar8) {
    iVar3 = 0xc;
    pbVar5 = local_21c;
    pbVar6 = (byte *)(int)&DAT_082772cc;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar7 = *pbVar5 < *pbVar6;
      bVar8 = *pbVar5 == *pbVar6;
      pbVar5 = pbVar5 + 1;
      pbVar6 = pbVar6 + 1;
    } while (bVar8);
    if ((!bVar7 && !bVar8) == bVar7) {
      if (local_210 == 0x1000100) {
        piVar4 = SpriteReadSFFPtr_1_01(param_1,(int)local_21c);
      }
      else {
        piVar4 = (int *)SpriteReadSFFPtr_2_00();
      }
      if (piVar4 != (int *)0x0) {
        piVar4[6] = local_210;
      }
    }
  }
  MFfseek(param_1,iVar1,0);
  return piVar4;
}
#undef local_21c
#undef local_210

/* SpriteReadSFFPtr_1_01 @ 0x0805c140, 606 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 18 stack locals placed at their original offsets in a 0x300-byte frame (a local's address escapes, see apply_frame_emulation) */
int * SpriteReadSFFPtr_1_01(int *param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  size_t sVar4;
  void *pvVar5;
  int iVar6;
  undefined3 extraout_var;
  undefined4 *puVar7;
  int *piVar8;
  void *pvVar9;
  unsigned char ghidra_frame[0x300] __attribute__((aligned(16)));
#define local_300 (*(int *)(ghidra_frame + 0x0))
#define local_2fc (*(int *)(ghidra_frame + 0x4))
#define local_2f8 (*(int *)(ghidra_frame + 0x8))
#define local_2ec (*(int *)(ghidra_frame + 0x14))
#define local_2e8 (*(int *)(ghidra_frame + 0x18))
#define local_2e4 (*(int *)(ghidra_frame + 0x1c))
#define local_2e0 (*(size_t *)(ghidra_frame + 0x20))
#define local_2dc (*(int *)(ghidra_frame + 0x24))
#define local_2d8 (*(int *)(ghidra_frame + 0x28))
#define local_2d4 (*(short *)(ghidra_frame + 0x2c))
#define local_2d2 (*(short *)(ghidra_frame + 0x2e))
#define local_2d0 (*(short *)(ghidra_frame + 0x30))
#define local_2ce (*(short *)(ghidra_frame + 0x32))
#define local_2cc (*(short *)(ghidra_frame + 0x34))
#define local_2ca (*(char *)(ghidra_frame + 0x36))
#define local_2bc (*(int (*)[152])(ghidra_frame + 0x44))
#define local_5c (*(int (*)[6])(ghidra_frame + 0x2a4))
#define local_44 (*(undefined4 *)(ghidra_frame + 0x2bc))
  
  local_2fc = 0;
  local_300 = -1;
  iVar2 = MFftell(param_1);
  piVar3 = SpriteArrayNewSize(*(size_t *)(param_2 + 0x14),1);
  if (piVar3 == (int *)0x0) {
    piVar3 = (int *)0x0;
  }
  else {
    local_2f8 = 0;
    if (0 < *(int *)(param_2 + 0x14)) {
      iVar6 = *(int *)(param_2 + 0x18);
      do {
        MFfseek(param_1,iVar6 + iVar2 + -0x200,0);
        sVar4 = MFfread(&local_2dc,0x20,1,param_1);
        if (sVar4 == 0) goto LAB_0805c198;
        if (local_2d8 < 1) {
          puVar7 = (undefined4 *)SpriteArrayAccess(piVar3,(int)local_2cc);
          SpriteCopy(local_5c,puVar7,0);
          SpriteSetAxis((int)local_5c,(int)local_2d4,(int)local_2d2);
        }
        else {
          piVar8 = (int *)0x0;
          if ((ReadMode != 0x10) && ((local_300 == -1 || (local_2ca == '\0')))) {
            piVar8 = local_2bc;
          }
          pvVar5 = SpriteReadPCXRawPtr(param_1,&local_2ec,&local_2e8,&local_2e4,&local_2e0,piVar8);
          if ((pvVar5 == (void *)0x0) ||
             ((pvVar9 = (void *)((uint)piVar8 & (8 < local_2e4) - 1), pvVar9 != (void *)0x0 &&
              (iVar6 = SpriteArrayAddPal((int)piVar3,pvVar9,0,local_2fc), iVar6 == 0)))) {
LAB_0805c198:
            SpriteArrayFree(piVar3);
            return (int *)0x0;
          }
          bVar1 = SpriteInit(local_5c,0,pvVar5,local_2e0,0,local_2ec,local_2e8,local_2e4,
                             (int)local_2d4,(int)local_2d2);
          if (GHIDRA_ZEXT8(bVar1) == 0) goto LAB_0805c198;
          local_44 = 1;
          if (pvVar9 == (void *)0x0) {
            if (local_2ca != '\0') {
              SpriteUsePal((int)local_5c,(int)piVar3,0,local_300);
            }
          }
          else {
            SpriteUsePal((int)local_5c,(int)piVar3,0,local_2fc);
            local_300 = local_2fc;
            local_2fc = local_2fc + 1;
          }
        }
        SpriteArrayAddSprite(piVar3,local_5c,(int)local_2d0,(int)local_2ce);
        local_2f8 = local_2f8 + 1;
        iVar6 = local_2dc;
      } while (local_2f8 < *(int *)(param_2 + 0x14));
    }
    MFfseek(param_1,iVar2,0);
  }
  return piVar3;
}
#undef local_300
#undef local_2fc
#undef local_2f8
#undef local_2ec
#undef local_2e8
#undef local_2e4
#undef local_2e0
#undef local_2dc
#undef local_2d8
#undef local_2d4
#undef local_2d2
#undef local_2d0
#undef local_2ce
#undef local_2cc
#undef local_2ca
#undef local_2bc
#undef local_5c
#undef local_44

/* SpriteReadSFFPtr_2_00 @ 0x0805c3a0, 3 bytes */
undefined4 SpriteReadSFFPtr_2_00(void)

{
  return 0;
}

/* SpriteReadSFFList @ 0x0805c3b0, 89 bytes */
int * SpriteReadSFFList(char *param_1,int *param_2)

{
  int *piVar1;
  int *piVar2;
  
  piVar1 = (int *)MFfopenFile(param_1,"rb");
  if (piVar1 == (int *)0x0) {
    piVar2 = (int *)0x0;
  }
  else {
    piVar2 = SpriteReadSFFListPtr(piVar1,param_2);
    if (piVar2 == (int *)0x0) {
      MFfclose(piVar1);
      piVar2 = (int *)0x0;
    }
    else {
      MFfclose(piVar1);
    }
  }
  return piVar2;
}

/* SpriteReadSFFListPtr @ 0x0805c410, 165 bytes
 * FIXUP: 1 data addresses written as literals replaced by data-image references
 * FIXUP: frame emulation: 3 stack locals placed at their original offsets in a 0x220-byte frame (a local's address escapes, see apply_frame_emulation) */
int * SpriteReadSFFListPtr(int *param_1,int *param_2)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  bool bVar6;
  bool bVar7;
  unsigned char ghidra_frame[0x220] __attribute__((aligned(16)));
#define local_220 (*(int **)(ghidra_frame + 0x0))
#define local_21c (*(byte (*)[12])(ghidra_frame + 0x4))
#define local_210 (*(int *)(ghidra_frame + 0x10))
  
  local_220 = (int *)0x0;
  iVar1 = MFftell(param_1);
  sVar2 = MFfread(local_21c,0x200,1,param_1);
  bVar6 = false;
  bVar7 = sVar2 == 0;
  if (!bVar7) {
    iVar3 = 0xc;
    pbVar4 = local_21c;
    pbVar5 = (byte *)(int)&DAT_082772cc;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar6 = *pbVar4 < *pbVar5;
      bVar7 = *pbVar4 == *pbVar5;
      pbVar4 = pbVar4 + 1;
      pbVar5 = pbVar5 + 1;
    } while (bVar7);
    if ((!bVar6 && !bVar7) == bVar6) {
      if (local_210 == 0x1000100) {
        local_220 = SpriteReadSFFListPtr_1_01(param_1,(int)local_21c,param_2);
      }
      else {
        local_220 = (int *)SpriteReadSFFListPtr_2_00();
      }
    }
  }
  MFfseek(param_1,iVar1,0);
  return local_220;
}
#undef local_220
#undef local_21c
#undef local_210

/* SpriteReadSFFListPtr_1_01 @ 0x0805c4c0, 747 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 18 stack locals placed at their original offsets in a 0x310-byte frame (a local's address escapes, see apply_frame_emulation) */
int * SpriteReadSFFListPtr_1_01(int *param_1,int param_2,int *param_3)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  size_t sVar4;
  void *__ptr;
  undefined3 extraout_var;
  int iVar5;
  int iVar6;
  int *piVar7;
  void *pvVar8;
  bool bVar9;
  unsigned char ghidra_frame[0x310] __attribute__((aligned(16)));
#define local_308 (*(size_t *)(ghidra_frame + 0x8))
#define local_304 (*(int *)(ghidra_frame + 0xc))
#define local_300 (*(int *)(ghidra_frame + 0x10))
#define local_2fc (*(int *)(ghidra_frame + 0x14))
#define local_2f8 (*(int *)(ghidra_frame + 0x18))
#define local_2ec (*(int *)(ghidra_frame + 0x24))
#define local_2e8 (*(int *)(ghidra_frame + 0x28))
#define local_2e4 (*(int *)(ghidra_frame + 0x2c))
#define local_2e0 (*(size_t *)(ghidra_frame + 0x30))
#define local_2dc (*(int *)(ghidra_frame + 0x34))
#define local_2d8 (*(int *)(ghidra_frame + 0x38))
#define local_2d4 (*(short *)(ghidra_frame + 0x3c))
#define local_2d2 (*(short *)(ghidra_frame + 0x3e))
#define local_2d0 (*(short *)(ghidra_frame + 0x40))
#define local_2ce (*(short *)(ghidra_frame + 0x42))
#define local_2ca (*(char *)(ghidra_frame + 0x46))
#define local_2bc (*(int (*)[152])(ghidra_frame + 0x54))
#define local_5c (*(int (*)[19])(ghidra_frame + 0x2b4))
  
  local_2fc = 0;
  local_300 = -1;
  local_304 = 0;
  local_308 = 0;
  local_2f8 = 0;
  iVar2 = *param_3;
  while (iVar2 != -1) {
    local_2f8 = local_2f8 + 2;
    local_308 = local_308 + 1;
    iVar2 = param_3[local_2f8];
  }
  iVar2 = MFftell(param_1);
  piVar3 = SpriteArrayNewSize(local_308,1);
  if (piVar3 == (int *)0x0) {
    piVar3 = (int *)0x0;
  }
  else {
    local_2f8 = 0;
    iVar5 = *(int *)(param_2 + 0x18);
    if (0 < *(int *)(param_2 + 0x14)) {
      do {
        MFfseek(param_1,iVar5 + iVar2 + -0x200,0);
        sVar4 = MFfread(&local_2dc,0x20,1,param_1);
        if (sVar4 == 0) goto LAB_0805c560;
        bVar1 = false;
        iVar5 = 0;
        if (*param_3 != -1) {
          if ((int)local_2d0 != *param_3) goto LAB_0805c5f5;
          bVar9 = (int)local_2ce == param_3[1];
          while (!bVar9) {
LAB_0805c5f5:
            do {
              iVar6 = iVar5;
              iVar5 = iVar6 + 2;
              if (param_3[iVar5] == -1) goto LAB_0805c61d;
            } while ((int)local_2d0 != param_3[iVar5]);
            bVar9 = (int)local_2ce == param_3[iVar6 + 3];
          }
          bVar1 = true;
        }
LAB_0805c61d:
        if (0 < local_2d8) {
          piVar7 = (int *)0x0;
          if ((ReadMode != 0x10) && ((local_300 == -1 || (local_2ca == '\0')))) {
            piVar7 = local_2bc;
          }
          if (bVar1) {
            __ptr = SpriteReadPCXRawPtr(param_1,&local_2ec,&local_2e8,&local_2e4,&local_2e0,piVar7);
            if ((__ptr == (void *)0x0) ||
               ((pvVar8 = (void *)((uint)piVar7 & (8 < local_2e4) - 1), pvVar8 != (void *)0x0 &&
                (iVar5 = SpriteArrayAddPal((int)piVar3,pvVar8,0,local_2fc), iVar5 == 0)))) {
LAB_0805c560:
              SpriteArrayFree(piVar3);
              return (int *)0x0;
            }
            bVar9 = SpriteInit(local_5c,0,__ptr,local_2e0,1,local_2ec,local_2e8,local_2e4,
                               (int)local_2d4,(int)local_2d2);
            if (GHIDRA_ZEXT8(bVar9) == 0) goto LAB_0805c560;
            free(__ptr);
            if (pvVar8 == (void *)0x0) {
              if (local_2ca != '\0') {
                SpriteUsePal((int)local_5c,(int)piVar3,0,local_300);
              }
            }
            else {
              SpriteUsePal((int)local_5c,(int)piVar3,0,local_2fc);
              local_300 = local_2fc;
              local_2fc = local_2fc + 1;
            }
          }
        }
        if (bVar1) {
          SpriteArrayAddSprite(piVar3,local_5c,(int)local_2d0,(int)local_2ce);
          local_304 = local_304 + 1;
        }
      } while ((local_304 < (int)local_308) &&
              (local_2f8 = local_2f8 + 1, iVar5 = local_2dc, local_2f8 < *(int *)(param_2 + 0x14)));
    }
    MFfseek(param_1,iVar2,0);
  }
  return piVar3;
}
#undef local_308
#undef local_304
#undef local_300
#undef local_2fc
#undef local_2f8
#undef local_2ec
#undef local_2e8
#undef local_2e4
#undef local_2e0
#undef local_2dc
#undef local_2d8
#undef local_2d4
#undef local_2d2
#undef local_2d0
#undef local_2ce
#undef local_2ca
#undef local_2bc
#undef local_5c

/* SpriteReadSFFListPtr_2_00 @ 0x0805c7b0, 3 bytes */
undefined4 SpriteReadSFFListPtr_2_00(void)

{
  return 0;
}

/* SpriteReadPCXRawPtr @ 0x0805c7c0, 1210 bytes
 * FIXUP: frame emulation: 4 stack locals placed at their original offsets in a 0x450-byte frame (a local's address escapes, see apply_frame_emulation) */
void * SpriteReadPCXRawPtr(int *param_1,int *param_2,int *param_3,int *param_4,size_t *param_5,
                          int *param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  void *pvVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  undefined4 *puVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  unsigned char ghidra_frame[0x450] __attribute__((aligned(16)));
#define local_450 (*(int *)(ghidra_frame + 0x0))
#define local_444 (*(int *)(ghidra_frame + 0xc))
#define local_440 (*(int *)(ghidra_frame + 0x10))
#define local_41c (*(undefined4 *)(ghidra_frame + 0x34))
  
  puVar15 = &local_41c;
  for (iVar12 = 0x100; iVar12 != 0; iVar12 = iVar12 + -1) {
    *puVar15 = 0;
    puVar15 = puVar15 + 1;
  }
  iVar12 = MFftell(param_1);
  MFgetc(param_1);
  MFgetc(param_1);
  MFgetc(param_1);
  uVar5 = MFgetc(param_1);
  if (uVar5 != 8) {
    return (void *)0x0;
  }
  uVar5 = MFigetw(param_1);
  uVar6 = MFigetw(param_1);
  uVar7 = MFigetw(param_1);
  iVar1 = (uVar7 + 1) - uVar5;
  uVar5 = MFigetw(param_1);
  iVar16 = 0xf;
  iVar2 = (uVar5 + 1) - uVar6;
  iVar14 = 0;
  MFigetl(param_1);
  do {
    uVar5 = MFgetc(param_1);
    *(char *)((int)&local_41c + iVar14) = (char)uVar5;
    uVar5 = MFgetc(param_1);
    *(char *)((int)&local_41c + iVar14 + 1) = (char)uVar5;
    uVar5 = MFgetc(param_1);
    *(char *)((int)&local_41c + iVar14 + 2) = (char)uVar5;
    *(undefined1 *)((int)&local_41c + iVar14 + 3) = 0xff;
    iVar14 = iVar14 + 4;
    iVar16 = iVar16 + -1;
  } while (-1 < iVar16);
  MFgetc(param_1);
  uVar5 = MFgetc(param_1);
  iVar14 = uVar5 * 8;
  if ((iVar14 != 8) && (iVar14 != 0x18)) {
    return (void *)0x0;
  }
  iVar16 = iVar14 + -1;
  if (iVar16 < 0) {
    iVar16 = iVar14 + 6;
  }
  iVar17 = 0x3b;
  iVar16 = (iVar16 >> 3) + 1;
  uVar5 = MFigetw(param_1);
  *param_5 = iVar16 * iVar1 * iVar2;
  do {
    MFgetc(param_1);
    iVar17 = iVar17 + -1;
  } while (-1 < iVar17);
  pvVar8 = calloc(1,*param_5);
  if (pvVar8 == (void *)0x0) {
    ElecOutOfMem = 1;
    return (void *)0x0;
  }
  local_444 = 0;
  if (0 < iVar2) {
    local_450 = 0;
    do {
      uVar6 = 0;
      local_440 = 0;
      iVar17 = _rgb_r_shift_24;
      if (_rgb_r_shift_24 < 0) {
        iVar17 = _rgb_r_shift_24 + 7;
      }
      iVar17 = iVar17 >> 3;
      while( true ) {
        iVar11 = uVar5 * iVar14;
        if (iVar11 < 0) {
          iVar11 = iVar11 + 7;
        }
        if (iVar11 >> 3 <= (int)uVar6) break;
        uVar7 = MFgetc(param_1);
        uVar4 = (undefined1)uVar7;
        if ((uVar7 & 0xc0) == 0xc0) {
          uVar7 = uVar7 & 0x3f;
          uVar9 = MFgetc(param_1);
          uVar4 = (undefined1)uVar9;
        }
        else {
          uVar7 = 1;
        }
        iVar3 = _rgb_b_shift_24;
        iVar11 = _rgb_g_shift_24;
        if (iVar14 == 8) {
          while (uVar7 = uVar7 - 1, uVar7 != 0xffffffff) {
            if ((int)uVar6 < iVar1) {
              *(undefined1 *)((int)pvVar8 + uVar6 + local_450 * iVar1) = uVar4;
            }
            uVar6 = uVar6 + 1;
          }
        }
        else {
          iVar18 = uVar7 - 1;
          if (iVar18 != -1) {
            iVar13 = local_440 * 3;
            do {
              if (local_440 < iVar1) {
                *(undefined1 *)((int)pvVar8 + iVar17 + iVar13 + local_450 * iVar1) = uVar4;
              }
              uVar6 = uVar6 + 1;
              iVar10 = iVar11;
              if ((uVar6 == uVar5) || (iVar10 = iVar3, uVar6 == uVar5 * 2)) {
                iVar13 = 0;
                local_440 = 0;
                if (iVar10 < 0) {
                  iVar10 = iVar10 + 7;
                }
                iVar17 = iVar10 >> 3;
              }
              else {
                iVar13 = iVar13 + 3;
                local_440 = local_440 + 1;
              }
              iVar18 = iVar18 + -1;
            } while (iVar18 != -1);
          }
        }
      }
      local_444 = local_444 + 1;
      local_450 = local_450 + iVar16;
    } while (local_444 < iVar2);
  }
  if ((iVar14 == 8) && (param_6 != (int *)0x0)) {
    do {
      iVar16 = MFfeof(param_1);
      if (iVar16 != 0) goto LAB_0805cbeb;
      uVar5 = MFgetc(param_1);
    } while (uVar5 != 0xc);
    iVar17 = 0;
    iVar16 = 0;
    do {
      iVar17 = iVar17 + 1;
      uVar5 = MFgetc(param_1);
      *(char *)((int)&local_41c + iVar16) = (char)uVar5;
      uVar5 = MFgetc(param_1);
      *(char *)((int)&local_41c + iVar16 + 1) = (char)uVar5;
      uVar5 = MFgetc(param_1);
      *(char *)((int)&local_41c + iVar16 + 2) = (char)uVar5;
      *(undefined1 *)((int)&local_41c + iVar16 + 3) = 0xff;
      iVar16 = iVar16 + 4;
    } while (iVar17 < 0x100);
LAB_0805cbeb:
    iVar16 = 0x100;
  }
  else {
    if ((iVar14 != 4) || (param_6 == (int *)0x0)) goto LAB_0805cc2c;
    iVar16 = 0x10;
  }
  EBPalInit(param_6,iVar16,&local_41c,1);
LAB_0805cc2c:
  *param_4 = iVar14;
  *param_2 = iVar1;
  *param_3 = iVar2;
  MFfseek(param_1,iVar12,0);
  return pvVar8;
}
#undef local_450
#undef local_444
#undef local_440
#undef local_41c

/* SpriteReadPCXPtr @ 0x0805cc80, 239 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 6 stack locals placed at their original offsets in a 0x2c0-byte frame (a local's address escapes, see apply_frame_emulation) */
int * SpriteReadPCXPtr(int *param_1,int param_2,int param_3)

{
  bool bVar1;
  int *piVar2;
  void *pvVar3;
  undefined3 extraout_var;
  unsigned char ghidra_frame[0x2c0] __attribute__((aligned(16)));
#define local_2bc (*(int *)(ghidra_frame + 0x4))
#define local_2b8 (*(int *)(ghidra_frame + 0x8))
#define local_2b4 (*(int *)(ghidra_frame + 0xc))
#define local_2b0 (*(size_t *)(ghidra_frame + 0x10))
#define local_2ac (*(int (*)[152])(ghidra_frame + 0x14))
#define local_4c (*(int (*)[16])(ghidra_frame + 0x274))
  
  piVar2 = SpriteArrayNewSize(1,1);
  if (piVar2 != (int *)0x0) {
    pvVar3 = SpriteReadPCXRawPtr(param_1,&local_2bc,&local_2b8,&local_2b4,&local_2b0,local_2ac);
    if (pvVar3 != (void *)0x0) {
      if (local_2b4 < 9) {
        SpriteArrayAddPal((int)piVar2,local_2ac,0,0);
      }
      piVar2[1] = (int)pvVar3;
      bVar1 = SpriteInit(local_4c,0,pvVar3,local_2b0,0,local_2bc,local_2b8,local_2b4,param_2,param_3
                        );
      if (GHIDRA_ZEXT8(bVar1) != 0) {
        if (local_2b4 < 9) {
          SpriteUsePal((int)local_4c,(int)piVar2,0,0);
        }
        SpriteArrayAddSprite(piVar2,local_4c,0,0);
        return piVar2;
      }
    }
    SpriteArrayFree(piVar2);
  }
  return (int *)0x0;
}
#undef local_2bc
#undef local_2b8
#undef local_2b4
#undef local_2b0
#undef local_2ac
#undef local_4c

