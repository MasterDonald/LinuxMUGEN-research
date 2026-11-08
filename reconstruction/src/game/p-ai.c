/*
 * p-ai.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x080a5d70-0x080ab1bf, 60 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* PlayerAIInit @ 0x080a5d70, 86 bytes */
undefined4 PlayerAIInit(int param_1,int param_2)

{
  int iVar1;
  
  if (param_2 != 0) {
    *(undefined4 *)(param_1 + 0x2dac) = 1;
    iVar1 = AIStateSetInit(param_1 + 0x2db0);
    if (iVar1 == 0) {
      return 0;
    }
  }
  *(undefined4 *)(param_1 + 0x33e4) = 0xffffffff;
  PlayerAISetLevel(param_1,4);
  return 1;
}

/* PlayerAIDeInit @ 0x080a5dd0, 40 bytes */
void PlayerAIDeInit(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  AIStateSetDeInit((undefined4 *)(param_1 + 0x2db0));
  puVar2 = (undefined4 *)(param_1 + 0x262c);
  for (iVar1 = 0x37e; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  return;
}

/* AILearnDataLoad @ 0x080a5e00, 640 bytes
 * FIXUP: rewrote 4 Ghidra partial-variable accesses (x._O_S_)
 * FIXUP: frame emulation: 6 stack locals placed at their original offsets in a 0x520-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 AILearnDataLoad(char *param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  FILE *stream;
  size_t sVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  byte *pbVar7;
  bool bVar8;
  bool bVar9;
  char *__format;
  unsigned char ghidra_frame[0x520] __attribute__((aligned(16)));
#define local_520 (*(int *)(ghidra_frame + 0x0))
#define local_51c (*(undefined1 (*)[516])(ghidra_frame + 0x4))
#define local_318 (*(undefined4 *)(ghidra_frame + 0x208))
#define local_5c (*(byte (*)[12])(ghidra_frame + 0x4c4))
#define local_50 (*(int *)(ghidra_frame + 0x4d0))
#define local_4c (*(undefined4 *)(ghidra_frame + 0x4d4))
  
  AIStateSetDeInit(param_2);
  iVar2 = AIStateSetInit((int)param_2);
  if ((iVar2 != 0) && (stream = fopen(param_1,"rb"), stream != (FILE *)0x0)) {
    sVar3 = fread(local_5c,0x40,1,stream);
    bVar8 = false;
    bVar9 = sVar3 == 0;
    if (bVar9) {
      __format = "Error reading file header";
LAB_080a6041:
      sprintf((char *)(g + 0x81d2),__format);
    }
    else {
      iVar2 = 0xc;
      pbVar5 = local_5c;
      pbVar7 = (byte *)"ElecbyteAIB";
      do {
        if (iVar2 == 0) break;
        iVar2 = iVar2 + -1;
        bVar8 = *pbVar5 < *pbVar7;
        bVar9 = *pbVar5 == *pbVar7;
        pbVar5 = pbVar5 + 1;
        pbVar7 = pbVar7 + 1;
      } while (bVar9);
      if ((!bVar8 && !bVar9) == bVar8) {
        if (local_50 == 0x100) {
          if ((((local_4c & 0xffff) == MUGENDATE_Y) && ((uint)(*(uchar *)((char *)&local_4c + 2)) == MUGENDATE_M)) &&
             (iVar2 = 0, (uint)(*(uchar *)((char *)&local_4c + 3)) == MUGENDATE_D)) {
            for (; iVar2 < 2; iVar2 = iVar2 + 1) {
              iVar1 = param_2[iVar2];
              sVar3 = fread(&local_520,4,1,stream);
              if (sVar3 == 0) goto LAB_080a604d;
              iVar6 = 0;
              if (0 < local_520) {
                do {
                  sVar3 = fread(local_51c,0x4b4,1,stream);
                  if (sVar3 == 0) goto LAB_080a604d;
                  iVar4 = ArrayAdd(iVar1,local_51c,0,local_318);
                  if (iVar4 == -1) {
                    __format = "Out of AI learning space";
                    goto LAB_080a6041;
                  }
                  iVar6 = iVar6 + 1;
                } while (iVar6 < local_520);
              }
            }
            sVar3 = fread(param_2 + 2,0x100,1,stream);
            if (sVar3 != 0) {
              fclose(stream);
              return 1;
            }
          }
          else {
            sprintf((char *)(g + 0x81d2),"Incorrect MUGEN version for AI: %i.%02i.%02i",
                    local_4c & 0xffff,(uint)(*(uchar *)((char *)&local_4c + 2)),(uint)(*(uchar *)((char *)&local_4c + 3)));
          }
        }
        else {
          sprintf((char *)(g + 0x81d2),"Incorrect AI version",stream,stream);
        }
      }
      else {
        sprintf((char *)(g + 0x81d2),"Not an AI file",iVar2,iVar2);
      }
    }
LAB_080a604d:
    fclose(stream);
  }
  return 0;
}
#undef local_520
#undef local_51c
#undef local_318
#undef local_5c
#undef local_50
#undef local_4c

/* AILearnDataSave @ 0x080a6080, 329 bytes
 * FIXUP: frame emulation: 5 stack locals placed at their original offsets in a 0x60-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 AILearnDataSave(char *param_1,int param_2)

{
  int iVar1;
  FILE *stream;
  size_t sVar2;
  void *ptr;
  int iVar3;
  undefined4 *puVar4;
  unsigned char ghidra_frame[0x60] __attribute__((aligned(16)));
#define local_60 (*(undefined4 *)(ghidra_frame + 0x0))
#define local_5c (*(undefined4 (*)[4])(ghidra_frame + 0x4))
#define local_4c (*(undefined2 *)(ghidra_frame + 0x14))
#define local_4a (*(undefined1 *)(ghidra_frame + 0x16))
#define local_49 (*(undefined1 *)(ghidra_frame + 0x17))
  
  iVar3 = 0;
  do {
    if (*(int *)(param_2 + iVar3 * 4) == 0) {
      return 0;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 2);
  stream = fopen(param_1,"wb");
  if (stream != (FILE *)0x0) {
    puVar4 = local_5c;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    memcpy(local_5c,"ElecbyteAIB",0xc);
    local_4c = (undefined2)MUGENDATE_Y;
    local_4a = (undefined1)MUGENDATE_M;
    local_5c[3] = 0x100;
    local_49 = (undefined1)MUGENDATE_D;
    sVar2 = fwrite(local_5c,0x40,1,stream);
    if (sVar2 != 0) {
      iVar3 = 0;
      do {
        iVar1 = *(int *)(param_2 + iVar3 * 4);
        local_60 = *(undefined4 *)(iVar1 + 8);
        sVar2 = fwrite(&local_60,4,1,stream);
        if (sVar2 == 0) goto LAB_080a6199;
        ptr = (void *)ArrayScanFirst(iVar1);
        while (ptr != (void *)0x0) {
          sVar2 = fwrite(ptr,*(size_t *)(iVar1 + 4),1,stream);
          if (sVar2 == 0) goto LAB_080a6199;
          ptr = (void *)ArrayScanNext(iVar1);
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < 2);
      sVar2 = fwrite((void *)(param_2 + 8),0x100,1,stream);
      if (sVar2 != 0) {
        fclose(stream);
        return 1;
      }
    }
LAB_080a6199:
    fclose(stream);
  }
  return 0;
}
#undef local_60
#undef local_5c
#undef local_4c
#undef local_4a
#undef local_49

/* AIStateSetInit @ 0x080a61d0, 91 bytes */
undefined4 AIStateSetInit(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = 0;
  do {
    puVar1 = ArrayNew(*(size_t *)((int)&AIMaxStateInfo + iVar3),0x4b4,0);
    *(undefined4 **)(param_1 + iVar3) = puVar1;
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + 4;
  } while (iVar2 < 2);
  iVar2 = 3;
  puVar1 = (undefined4 *)(param_1 + 200);
  do {
    *puVar1 = 0xc6fff000;
    puVar1 = puVar1 + -0x10;
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  return 1;
}

/* AIStateSetDeInit @ 0x080a6230, 57 bytes */
void AIStateSetDeInit(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if ((void *)param_1[iVar1] != (void *)0x0) {
      ArrayFree((void *)param_1[iVar1]);
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 2);
  for (iVar1 = 0x42; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = 0;
    param_1 = param_1 + 1;
  }
  return;
}

/* AIStateSetClear @ 0x080a6270, 45 bytes */
void AIStateSetClear(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    iVar1 = *(int *)(param_1 + iVar2 * 4);
    if (iVar1 != 0) {
      ArrayClear(iVar1);
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 2);
  return;
}

/* AIStateSetMerge @ 0x080a62a0, 222 bytes */
undefined4 AIStateSetMerge(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  void *pvVar4;
  uint uVar5;
  int iVar6;
  int local_14;
  
  iVar6 = 0;
  local_14 = 0;
  do {
    iVar1 = *(int *)(param_2 + iVar6);
    if (iVar1 != 0) {
      if (*(int *)(param_1 + iVar6) == 0) {
        puVar3 = ArrayNew(*(size_t *)((int)&AIMaxStateInfo + iVar6),0x4b4,0);
        *(undefined4 **)(param_1 + iVar6) = puVar3;
        if (puVar3 == (undefined4 *)0x0) {
          return 0;
        }
      }
      iVar2 = *(int *)(param_1 + iVar6);
      pvVar4 = (void *)ArrayScanFirst(iVar1);
      while (pvVar4 != (void *)0x0) {
        uVar5 = ArrayFind(iVar2,0,*(int *)((int)pvVar4 + 0x204));
        if (uVar5 == 0xffffffff) {
          ArrayAdd(iVar2,pvVar4,0,*(undefined4 *)((int)pvVar4 + 0x204));
        }
        else {
          AIMergeLearnData((int *)(uVar5 * *(int *)(iVar2 + 4) + *(int *)(iVar2 + 0x14)),(int)pvVar4
                           ,-1);
        }
        pvVar4 = (void *)ArrayScanNext(iVar1);
      }
    }
    iVar6 = iVar6 + 4;
    local_14 = local_14 + 1;
  } while (local_14 < 2);
  return 1;
}

/* AIStateSetCopy @ 0x080a6380, 37 bytes */
void AIStateSetCopy(int param_1,int param_2)

{
  AIStateSetClear(param_1);
  AIStateSetMerge(param_1,param_2);
  return;
}

/* PlayerAISetLevel @ 0x080a63b0, 15 bytes */
void PlayerAISetLevel(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x33f8) = param_2;
  return;
}

/* PlayerResetAI @ 0x080a63c0, 114 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x670-byte frame (a local's address escapes, see apply_frame_emulation) */
void PlayerResetAI(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  unsigned char ghidra_frame[0x670] __attribute__((aligned(16)));
#define local_66c (*(undefined4 (*)[407])(ghidra_frame + 0x4))
  
  puVar3 = (undefined4 *)(param_1 + 0x2dac);
  puVar4 = local_66c;
  for (iVar2 = 0x193; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  uVar1 = *(undefined4 *)(param_1 + 0x33f8);
  puVar3 = (undefined4 *)(param_1 + 0x262c);
  for (iVar2 = 0x37e; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  AIClearCommands((undefined4 *)(param_1 + 0x33fc));
  PlayerAIClearMsg(param_1);
  puVar3 = local_66c;
  puVar4 = (undefined4 *)(param_1 + 0x2dac);
  for (iVar2 = 0x193; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  *(undefined4 *)(param_1 + 0x33f8) = uVar1;
  return;
}
#undef local_66c

/* PlayerAI @ 0x080a6440, 303 bytes */
void PlayerAI(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  iVar2 = *(int *)(param_1 + 0x3424);
  iVar1 = param_1 + 0x248;
  if (((*(int *)(param_1 + 0x262c) != 0) && (iVar2 != 0)) && (*(int *)(iVar2 + 0x158) != 0)) {
    AIClearCommands((undefined4 *)(param_1 + 0x33fc));
    if (g[0x7511] != 2) {
      AIKBReleaseAll(param_1);
      return;
    }
    if ((*(int *)(param_1 + 0x2c8) != 0) && (*(int *)(param_1 + 0x2d0) != 0)) {
      if (*(int *)(param_1 + 0xe10) == 0) {
        uVar4 = 0x14;
      }
      else {
        uVar4 = 0x12;
      }
      KBIStuffBufNoFlip(iVar1,uVar4);
    }
    if ((*(int *)(param_1 + 0x2c4) != 0) && (*(int *)(param_1 + 0x2cc) != 0)) {
      KBIStuffBufNoFlip(iVar1,0x11);
    }
    uVar4 = KBIGetch(param_1 + 0x2cec);
    if (uVar4 == 0) {
      uVar3 = AICheckForAttacks(param_1);
      *(undefined4 *)(param_1 + 0x2da8) = uVar3;
      if ((g[0x33ae] == 3) && (*(int *)(param_1 + 0x2cd0) == 0)) {
        AIForTrainingMode(param_1,iVar2);
      }
      else {
        AIForNormal(param_1,*(int *)(param_1 + 0x33f8));
      }
    }
    else {
      KBIStuffBufNoFlip(iVar1,uVar4);
    }
  }
  return;
}

/* PlayerAIProcessCommands @ 0x080a6570, 76 bytes */
void PlayerAIProcessCommands(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = param_1;
  if (*(int *)(param_1 + 0x2624) != 0) {
    iVar2 = *(int *)(param_1 + 0x2624);
  }
  if (*(int *)(iVar2 + 0x262c) != 0) {
    iVar3 = 0x33f0;
    if (*(int *)(iVar2 + 0x33fc) != -1) {
      iVar4 = 0x33f0;
      do {
        piVar1 = (int *)(iVar4 + iVar2 + 0xc);
        iVar4 = iVar4 + 4;
        iVar3 = iVar3 + 4;
        *(undefined1 *)(*piVar1 + param_1 + 0x968) = 1;
      } while (*(int *)(iVar3 + iVar2 + 0xc) != -1);
    }
  }
  return;
}

/* AIInsertCommand @ 0x080a65c0, 52 bytes */
undefined4 AIInsertCommand(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = *param_1;
  while (iVar1 != -1) {
    iVar2 = iVar2 + 1;
    iVar1 = param_1[iVar2];
  }
  if (iVar2 < 9) {
    param_1[iVar2] = param_2;
    param_1[iVar2 + 1] = -1;
    return 1;
  }
  return 0;
}

/* AICopyCommands @ 0x080a6600, 39 bytes */
void AICopyCommands(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = *param_2;
  while (iVar1 != -1) {
    *(int *)(param_1 + iVar2 * 4) = iVar1;
    iVar2 = iVar2 + 1;
    iVar1 = param_2[iVar2];
  }
  *(undefined4 *)(param_1 + iVar2 * 4) = 0xffffffff;
  return;
}

/* AIClearCommands @ 0x080a6630, 11 bytes */
void AIClearCommands(undefined4 *param_1)

{
  *param_1 = 0xffffffff;
  return;
}

/* AICountCommands @ 0x080a6640, 24 bytes */
int AICountCommands(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = *param_1;
  while (iVar1 != -1) {
    iVar2 = iVar2 + 1;
    iVar1 = param_1[iVar2];
  }
  return iVar2;
}

/* PlayerAILearnMoveStart @ 0x080a6660, 392 bytes */
undefined4 PlayerAILearnMoveStart(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  iVar1 = AIFetchLearnDataArray(param_1 + 0x2dac,*(int *)(param_1 + 0xe00));
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 0x267c) = 0;
  }
  else {
    uVar2 = ArrayAccessGrpItem(iVar1,0,*(int *)(param_1 + 0xbf4));
    *(undefined4 *)(param_1 + 0x267c) = uVar2;
  }
  if (*(int *)(param_1 + 0x2dac) == 0) {
    uVar2 = 0;
  }
  else {
    if (*(int *)(param_1 + 0x2eb8) != 0) {
      PlayerAILearnMoveEnd(param_1,0);
    }
    puVar3 = (undefined4 *)(param_1 + 0x2eb8);
    for (iVar1 = 0x136; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = 0;
      puVar3 = puVar3 + 1;
    }
    *(undefined4 *)(param_1 + 0x2eb8) = 1;
    *(undefined4 *)(param_1 + 0x2ec0) = *(undefined4 *)(param_1 + 0xe00);
    *(undefined4 *)(param_1 + 0x2ecc) = *(undefined4 *)(param_1 + 400);
    *(int *)(param_1 + 0x2ec4) = (int)GHIDRA_FIST32(*(float *)(param_1 + 0x19c));
    *(int *)(param_1 + 0x2ec8) = (int)GHIDRA_FIST32(*(float *)(param_1 + 0x1a0));
    *(undefined4 *)(param_1 + 0x2ed8) = 0;
    *(undefined4 *)(param_1 + 0x30e0) = *(undefined4 *)(param_1 + 0xbf4);
    *(undefined4 *)(param_1 + 0x30e4) = *(undefined4 *)(param_1 + 0xe00);
    *(undefined4 *)(param_1 + 0x2edc) = *(undefined4 *)(param_1 + 0x33e8);
    *(undefined4 *)(param_1 + 12000) = *(undefined4 *)(param_1 + 0x33ec);
    *(undefined4 *)(param_1 + 0x2ee4) = *(undefined4 *)(param_1 + 0x33f0);
    *(undefined4 *)(param_1 + 0x2ee8) = *(undefined4 *)(param_1 + 0x33f4);
    *(undefined4 *)(param_1 + 0x30dc) = 1;
    AICopyCommands(param_1 + 0x30e8,(int *)(param_1 + 0x3390));
    *(undefined4 *)(param_1 + 0x3210) = 0xc6fff000;
    *(undefined4 *)(param_1 + 0x31d0) = 0xc6fff000;
    uVar2 = 1;
  }
  return uVar2;
}

/* PlayerAILearnMoveUpdate @ 0x080a67f0, 2550 bytes
 * FIXUP: removed 5 x87 control-word save statements
 * FIXUP: 12 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 52 stack locals placed at their original offsets in a 0x100-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void PlayerAILearnMoveUpdate(int param_1,int param_2)

{
  float10 fVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined2 in_FPUControlWord;
  unsigned char ghidra_frame[0x100] __attribute__((aligned(16)));
#define local_f4 (*(uint *)(ghidra_frame + 0xc))
#define local_ec (*(float *)(ghidra_frame + 0x14))
#define local_e8 (*(undefined4 *)(ghidra_frame + 0x18))
#define uStack_e4 (*(undefined4 *)(ghidra_frame + 0x1c))
#define local_e0 (*(undefined4 *)(ghidra_frame + 0x20))
#define local_dc (*(float *)(ghidra_frame + 0x24))
#define local_d8 (*(undefined4 *)(ghidra_frame + 0x28))
#define local_d4 (*(undefined4 *)(ghidra_frame + 0x2c))
#define local_d0 (*(undefined4 *)(ghidra_frame + 0x30))
#define fStack_cc (*(float *)(ghidra_frame + 0x34))
#define local_c8 (*(undefined4 *)(ghidra_frame + 0x38))
#define local_c4 (*(undefined4 *)(ghidra_frame + 0x3c))
#define local_c0 (*(undefined4 *)(ghidra_frame + 0x40))
#define local_bc (*(float *)(ghidra_frame + 0x44))
#define uStack_b8 (*(undefined4 *)(ghidra_frame + 0x48))
#define local_b4 (*(undefined4 *)(ghidra_frame + 0x4c))
#define local_b0 (*(undefined4 *)(ghidra_frame + 0x50))
#define local_ac (*(float *)(ghidra_frame + 0x54))
#define local_a8 (*(undefined4 *)(ghidra_frame + 0x58))
#define local_a4 (*(undefined4 *)(ghidra_frame + 0x5c))
#define local_a0 (*(undefined4 *)(ghidra_frame + 0x60))
#define local_9c (*(float *)(ghidra_frame + 0x64))
#define local_98 (*(undefined4 *)(ghidra_frame + 0x68))
#define local_94 (*(undefined4 *)(ghidra_frame + 0x6c))
#define local_90 (*(undefined4 *)(ghidra_frame + 0x70))
#define local_8c (*(float *)(ghidra_frame + 0x74))
#define local_88 (*(undefined4 *)(ghidra_frame + 0x78))
#define local_84 (*(undefined4 *)(ghidra_frame + 0x7c))
#define uStack_80 (*(undefined4 *)(ghidra_frame + 0x80))
#define local_7c (*(float *)(ghidra_frame + 0x84))
#define local_78 (*(undefined4 *)(ghidra_frame + 0x88))
#define local_74 (*(undefined4 *)(ghidra_frame + 0x8c))
#define local_70 (*(undefined4 *)(ghidra_frame + 0x90))
#define fStack_6c (*(float *)(ghidra_frame + 0x94))
#define local_68 (*(undefined4 *)(ghidra_frame + 0x98))
#define local_64 (*(undefined4 *)(ghidra_frame + 0x9c))
#define local_60 (*(undefined4 *)(ghidra_frame + 0xa0))
#define local_5c (*(float *)(ghidra_frame + 0xa4))
#define local_58 (*(undefined4 *)(ghidra_frame + 0xa8))
#define local_54 (*(undefined4 *)(ghidra_frame + 0xac))
#define local_50 (*(undefined4 *)(ghidra_frame + 0xb0))
#define local_44 (*(float *)(ghidra_frame + 0xbc))
#define local_40 (*(undefined2 *)(ghidra_frame + 0xc0))
#define uStack_3e (*(undefined2 *)(ghidra_frame + 0xc2))
#define local_3c (*(float *)(ghidra_frame + 0xc4))
#define local_38 (*(undefined4 *)(ghidra_frame + 0xc8))
#define uStack_34 (*(undefined4 *)(ghidra_frame + 0xcc))
#define local_30 (*(undefined4 *)(ghidra_frame + 0xd0))
#define local_2c (*(float *)(ghidra_frame + 0xd4))
#define local_28 (*(undefined4 *)(ghidra_frame + 0xd8))
#define local_24 (*(undefined4 *)(ghidra_frame + 0xdc))
#define uStack_20 (*(undefined4 *)(ghidra_frame + 0xe0))
  
  bVar3 = true;
  bVar2 = false;
  iVar6 = param_1 + 0x2edc;
  fVar1 = *(float *)(param_1 + 0x2ebc);
  local_f4 = 0;
  if (((*(int *)(*(int *)(param_1 + 0x13bc) + 0x10) == 0) || (*(int *)(param_1 + 0x2dac) == 0)) ||
     (*(int *)(param_1 + 0x2eb8) == 0)) {
    bVar3 = false;
  }
  if ((*(int *)(param_1 + 0xe04) == 0) && (*(int *)(param_1 + 0xe0c) != 0)) {
    if (bVar3) {
      local_f4 = (uint)(1 < *(int *)(param_1 + 0x2eb8));
    }
    bVar2 = true;
  }
  if ((*(int *)(param_1 + 0xbec) != 0) || (*(int *)(param_1 + 0xe04) == 2)) {
    bVar2 = true;
  }
  if (bVar2) {
    *(undefined4 *)(param_1 + 0x267c) = 0;
  }
  if (*(int *)(param_1 + 0x2dac) != 0) {
    AILearnIdleClsnUpdate(param_1);
  }
  if (bVar3) {
    if (bVar2) {
      PlayerAILearnMoveEnd(param_1,local_f4);
    }
    else {
      iVar4 = PlayerAIGetAIPLHS(param_1);
      iVar5 = *(int *)(param_1 + 0x2ed8);
      if (iVar5 == 0) {
        *(int *)(param_1 + 0x2ed8) = iVar4;
        iVar5 = iVar4;
      }
      if (((param_2 != 0) && (*(int *)(param_1 + 0xe18) == 0)) && (g[0x74f3] == -1)) {
        AILearnClsnUpdate(param_1,iVar6);
      }
      if (*(int *)(param_1 + 0x2eb8) == 1) {
        if ((*(int *)(param_1 + 0x1158) != 0) &&
           (*(int *)(*(int *)(*(int *)(param_1 + 0x13bc) + 0x10) + 0x28) != 0)) {
          iVar4 = iVar5 * 0x30;
          AIValMake(&local_2c,fVar1);
          *(float *)(param_1 + 0x3110) = local_2c;
          *(undefined4 *)(param_1 + 0x3114) = local_28;
          *(undefined4 *)(param_1 + 0x3118) = local_24;
          *(undefined4 *)(param_1 + 0x311c) = uStack_20;
          *(float *)(iVar4 + 0x264 + iVar6) = local_2c;
          *(undefined4 *)(iVar4 + 0x268 + iVar6) = *(undefined4 *)(param_1 + 0x3114);
          *(undefined4 *)(iVar4 + 0x26c + iVar6) = *(undefined4 *)(param_1 + 0x3118);
          *(undefined4 *)(iVar4 + 0x270 + iVar6) = *(undefined4 *)(param_1 + 0x311c);
          local_44 = GHIDRA_I2F((int)GHIDRA_FIST32((*(float *)(param_1 + 0x19c) -
                                       (float10)*(int *)(param_1 + 0x2ec4)) *
                                       (float10)*(int *)(param_1 + 0x2ecc)));
          AIValMake(&local_3c,local_44);
          *(float *)(param_1 + 0x3120) = local_3c;
          *(undefined4 *)(param_1 + 0x3124) = local_38;
          *(undefined4 *)(param_1 + 0x3128) = uStack_34;
          *(undefined4 *)(param_1 + 0x312c) = local_30;
          *(float *)(iVar4 + 0x274 + iVar6) = local_3c;
          *(undefined4 *)(iVar4 + 0x278 + iVar6) = *(undefined4 *)(param_1 + 0x3124);
          *(undefined4 *)(iVar4 + 0x27c + iVar6) = *(undefined4 *)(param_1 + 0x3128);
          *(undefined4 *)(iVar4 + 0x280 + iVar6) = *(undefined4 *)(param_1 + 0x312c);
          local_44 = GHIDRA_I2F((int)GHIDRA_FIST32(*(float *)(param_1 + 0x1a0) -
                                       (float10)*(int *)(param_1 + 0x2ec8)));
          AIValMake(&local_5c,local_44);
          *(float *)(param_1 + 0x3130) = local_5c;
          *(undefined4 *)(param_1 + 0x3134) = local_58;
          *(undefined4 *)(param_1 + 0x3138) = local_54;
          *(undefined4 *)(param_1 + 0x313c) = local_50;
          *(float *)(iVar4 + 0x284 + iVar6) = local_5c;
          *(undefined4 *)(iVar4 + 0x288 + iVar6) = *(undefined4 *)(param_1 + 0x3134);
          *(undefined4 *)(iVar4 + 0x28c + iVar6) = *(undefined4 *)(param_1 + 0x3138);
          *(undefined4 *)(iVar4 + 0x290 + iVar6) = *(undefined4 *)(param_1 + 0x313c);
          *(undefined4 *)(param_1 + 0x3250) = *(undefined4 *)(param_1 + 0x11d0);
          *(undefined4 *)(param_1 + 0x3254) = *(undefined4 *)(param_1 + 0x11cc);
          *(undefined4 *)(param_1 + 0x3258) = *(undefined4 *)(param_1 + 0x1164);
          *(undefined4 *)(param_1 + 0x325c) = *(undefined4 *)(param_1 + 0x1204);
          *(undefined4 *)(param_1 + 0x2eb8) = 2;
        }
        if (*(int *)(param_1 + 0x33e4) != -1) {
          iVar5 = iVar5 * 0x30;
          AIValMake(&fStack_6c,fVar1);
          *(float *)(param_1 + 0x3110) = fStack_6c;
          *(undefined4 *)(param_1 + 0x3114) = local_68;
          *(undefined4 *)(param_1 + 0x3118) = local_64;
          *(undefined4 *)(param_1 + 0x311c) = local_60;
          *(float *)(iVar5 + 0x264 + iVar6) = fStack_6c;
          *(undefined4 *)(iVar5 + 0x268 + iVar6) = *(undefined4 *)(param_1 + 0x3114);
          *(undefined4 *)(iVar5 + 0x26c + iVar6) = *(undefined4 *)(param_1 + 0x3118);
          *(undefined4 *)(iVar5 + 0x270 + iVar6) = *(undefined4 *)(param_1 + 0x311c);
          local_44 = GHIDRA_I2F((int)GHIDRA_FIST32((*(float *)(param_1 + 0x19c) -
                                       (float10)*(int *)(param_1 + 0x2ec4)) *
                                       (float10)*(int *)(param_1 + 0x2ecc)));
          AIValMake(&local_7c,local_44);
          *(float *)(param_1 + 0x3120) = local_7c;
          *(undefined4 *)(param_1 + 0x3124) = local_78;
          *(undefined4 *)(param_1 + 0x3128) = local_74;
          *(undefined4 *)(param_1 + 0x312c) = local_70;
          *(float *)(iVar5 + 0x274 + iVar6) = local_7c;
          *(undefined4 *)(iVar5 + 0x278 + iVar6) = *(undefined4 *)(param_1 + 0x3124);
          *(undefined4 *)(iVar5 + 0x27c + iVar6) = *(undefined4 *)(param_1 + 0x3128);
          *(undefined4 *)(iVar5 + 0x280 + iVar6) = *(undefined4 *)(param_1 + 0x312c);
          local_44 = GHIDRA_I2F((int)GHIDRA_FIST32(*(float *)(param_1 + 0x1a0) -
                                       (float10)*(int *)(param_1 + 0x2ec8)));
          AIValMake(&local_8c,local_44);
          *(float *)(param_1 + 0x3130) = local_8c;
          *(undefined4 *)(param_1 + 0x3134) = local_88;
          *(undefined4 *)(param_1 + 0x3138) = local_84;
          *(undefined4 *)(param_1 + 0x313c) = uStack_80;
          *(float *)(iVar5 + 0x284 + iVar6) = local_8c;
          *(undefined4 *)(iVar5 + 0x288 + iVar6) = *(undefined4 *)(param_1 + 0x3134);
          *(undefined4 *)(iVar5 + 0x28c + iVar6) = *(undefined4 *)(param_1 + 0x3138);
          *(undefined4 *)(iVar5 + 0x290 + iVar6) = *(undefined4 *)(param_1 + 0x313c);
          *(undefined4 *)(param_1 + 0x2ed4) = *(undefined4 *)(param_1 + 0x33e4);
          *(undefined4 *)(param_1 + 0x33e4) = 0xffffffff;
          *(undefined4 *)(param_1 + 0x2eb8) = 2;
        }
      }
      else if (*(int *)(param_1 + 0x2eb8) == 2) {
        if (((*(int *)(param_1 + 0x1158) != 0) &&
            (*(int *)(*(int *)(*(int *)(param_1 + 0x13bc) + 0x10) + 0x28) != 0)) ||
           (iVar4 = ProjArrayCountActiveID(*(int **)(param_1 + 0x21c),*(int *)(param_1 + 0x2ed4)),
           iVar4 != 0)) {
          iVar4 = iVar5 * 0x30;
          AIValMake(&local_9c,fVar1);
          *(float *)(iVar4 + 0x264 + iVar6) = local_9c;
          *(undefined4 *)(iVar4 + 0x268 + iVar6) = local_98;
          *(undefined4 *)(iVar4 + 0x26c + iVar6) = local_94;
          *(undefined4 *)(iVar4 + 0x270 + iVar6) = local_90;
          local_44 = GHIDRA_I2F((int)GHIDRA_FIST32((*(float *)(param_1 + 0x19c) -
                                       (float10)*(int *)(param_1 + 0x2ec4)) *
                                       (float10)*(int *)(param_1 + 0x2ecc)));
          AIValMake(&local_ac,local_44);
          *(float *)(iVar4 + 0x274 + iVar6) = local_ac;
          *(undefined4 *)(iVar4 + 0x278 + iVar6) = local_a8;
          *(undefined4 *)(iVar4 + 0x27c + iVar6) = local_a4;
          *(undefined4 *)(iVar4 + 0x280 + iVar6) = local_a0;
          local_44 = GHIDRA_I2F((int)GHIDRA_FIST32(*(float *)(param_1 + 0x1a0) -
                                       (float10)*(int *)(param_1 + 0x2ec8)));
          AIValMake(&local_bc,local_44);
          *(float *)(iVar4 + 0x284 + iVar6) = local_bc;
          *(undefined4 *)(iVar4 + 0x288 + iVar6) = uStack_b8;
          *(undefined4 *)(iVar4 + 0x28c + iVar6) = local_b4;
          *(undefined4 *)(iVar4 + 0x290 + iVar6) = local_b0;
          if (*(int *)(param_1 + 0x1168) != *(int *)(param_1 + 0x2ed0)) {
            local_44 = GHIDRA_I2F((int)GHIDRA_FIST32(*(float *)(param_1 + 0x3260)));
            AIValMake(&fStack_cc,GHIDRA_I2F((GHIDRA_F2I(int, local_44) + *(int *)(param_1 + 0x1190))));
            *(float *)(param_1 + 0x3260) = fStack_cc;
            *(undefined4 *)(param_1 + 0x3264) = local_c8;
            *(undefined4 *)(param_1 + 0x3268) = local_c4;
            *(undefined4 *)(param_1 + 0x326c) = local_c0;
            *(undefined4 *)(param_1 + 0x2ed0) = *(undefined4 *)(param_1 + 0x1168);
          }
        }
        iVar5 = iVar5 * 0x30;
        if ((*(float *)(iVar5 + 0x394 + iVar6) == 0.0) && (*(int *)(param_1 + 0xe0c) != 0)) {
          AIValMake(&fStack_cc,fVar1);
          *(float *)(iVar5 + 0x394 + iVar6) = fStack_cc;
          *(undefined4 *)(iVar5 + 0x398 + iVar6) = local_c8;
          *(undefined4 *)(iVar5 + 0x39c + iVar6) = local_c4;
          *(undefined4 *)(iVar5 + 0x3a0 + iVar6) = local_c0;
          local_44 = GHIDRA_I2F((int)GHIDRA_FIST32((*(float *)(param_1 + 0x19c) -
                                       (float10)*(int *)(param_1 + 0x2ec4)) *
                                       (float10)*(int *)(param_1 + 0x2ecc)));
          AIValMake(&local_dc,local_44);
          *(float *)(iVar5 + 0x3a4 + iVar6) = local_dc;
          *(undefined4 *)(iVar5 + 0x3a8 + iVar6) = local_d8;
          *(undefined4 *)(iVar5 + 0x3ac + iVar6) = local_d4;
          *(undefined4 *)(iVar5 + 0x3b0 + iVar6) = local_d0;
          local_44 = GHIDRA_I2F((int)GHIDRA_FIST32(*(float *)(param_1 + 0x1a0) -
                                       (float10)*(int *)(param_1 + 0x2ec8)));
          AIValMake(&local_ec,local_44);
          *(float *)(iVar5 + 0x3b4 + iVar6) = local_ec;
          *(undefined4 *)(iVar5 + 0x3b8 + iVar6) = local_e8;
          *(undefined4 *)(iVar5 + 0x3bc + iVar6) = uStack_e4;
          *(undefined4 *)(iVar5 + 0x3c0 + iVar6) = local_e0;
        }
      }
      if (((param_2 != 0) && (*(int *)(param_1 + 0xe18) == 0)) && (g[0x74f3] == -1)) {
        *(int *)(param_1 + 0x2ebc) = *(int *)(param_1 + 0x2ebc) + 1;
      }
    }
  }
  return;
}
#undef local_f4
#undef local_ec
#undef local_e8
#undef uStack_e4
#undef local_e0
#undef local_dc
#undef local_d8
#undef local_d4
#undef local_d0
#undef fStack_cc
#undef local_c8
#undef local_c4
#undef local_c0
#undef local_bc
#undef uStack_b8
#undef local_b4
#undef local_b0
#undef local_ac
#undef local_a8
#undef local_a4
#undef local_a0
#undef local_9c
#undef local_98
#undef local_94
#undef local_90
#undef local_8c
#undef local_88
#undef local_84
#undef uStack_80
#undef local_7c
#undef local_78
#undef local_74
#undef local_70
#undef fStack_6c
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef local_44
#undef local_40
#undef uStack_3e
#undef local_3c
#undef local_38
#undef uStack_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef uStack_20

/* AILearnClsnUpdate @ 0x080a71f0, 609 bytes
 * FIXUP: 8 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
int AILearnClsnUpdate(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  int local_2c;
  int local_20;
  int local_1c;
  
  pfVar8 = (float *)(param_2 + 0x2f4);
  iVar1 = (int)GHIDRA_FIST32((*(float *)(param_1 + 0x19c) - (float10)*(int *)(param_1 + 0x2ec4)) *
                     (float10)*(int *)(param_1 + 0x2ecc));
  local_1c = 0;
  iVar2 = (int)GHIDRA_FIST32(*(float *)(param_1 + 0x1a0) - (float10)*(int *)(param_1 + 0x2ec8));
  do {
    iVar7 = 0;
    iVar4 = *(int *)(*(int *)(param_1 + 0x13bc) + 0x10);
    if (iVar4 != 0) {
      if (local_1c == 0) {
        iVar7 = *(int *)(iVar4 + 0x28);
      }
      else {
        iVar7 = *(int *)(iVar4 + 0x2c);
      }
    }
    if (iVar7 != 0) {
      fVar3 = *pfVar8;
      iVar4 = CONCAT22((short)((uint)iVar4 >> 0x10),
                       (ushort)(fVar3 < -32760.0) << 8 | (ushort)GHIDRA_ISNAN(fVar3) << 10 |
                       (ushort)(fVar3 == -32760.0) << 0xe);
      if ((fVar3 == -32760.0) != 0) {
        iVar4 = *(int *)(iVar7 + 8);
        iVar5 = *(int *)(iVar4 + 8);
        *pfVar8 = (float)(iVar1 + *(int *)(iVar4 + 4));
        iVar6 = *(int *)(iVar4 + 0xc);
        pfVar8[4] = (float)(iVar2 + iVar5);
        iVar4 = *(int *)(iVar4 + 0x10);
        pfVar8[8] = (float)(iVar1 + iVar6);
        iVar4 = iVar2 + iVar4;
        pfVar8[0xc] = (float10)iVar4;
      }
      local_20 = 0;
      if (0 < *(int *)(iVar7 + 4)) {
        local_2c = 0;
        do {
          iVar6 = local_2c + *(int *)(iVar7 + 8);
          iVar5 = IntMin((int)GHIDRA_FIST32(*pfVar8),iVar1 + *(int *)(iVar6 + 4));
          iVar4 = *(int *)(iVar6 + 8);
          *pfVar8 = (float10)iVar5;
          iVar5 = IntMin((int)GHIDRA_FIST32(pfVar8[4]),iVar2 + iVar4);
          iVar4 = *(int *)(iVar6 + 0xc);
          pfVar8[4] = (float10)iVar5;
          iVar5 = IntMax((int)GHIDRA_FIST32(pfVar8[8]),iVar1 + iVar4);
          iVar4 = *(int *)(iVar6 + 0x10);
          pfVar8[8] = (float10)iVar5;
          iVar4 = IntMax((int)GHIDRA_FIST32(pfVar8[0xc]),iVar2 + iVar4);
          pfVar8[0xc] = (float10)iVar4;
          local_20 = local_20 + 1;
          local_2c = local_2c + 0x14;
        } while (local_20 < *(int *)(iVar7 + 4));
      }
    }
    pfVar8 = pfVar8 + 0x10;
    local_1c = local_1c + 1;
  } while (local_1c < 2);
  return iVar4;
}

/* AILearnIdleClsnUpdate @ 0x080a7460, 436 bytes
 * FIXUP: 8 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
void AILearnIdleClsnUpdate(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 local_1c;
  
  if (*(int *)(*(int *)(param_1 + 0x13bc) + 0x10) != 0) {
    iVar2 = AIIdleClsnMatchState(*(int *)(param_1 + 0xbf4));
    if ((iVar2 != -1) &&
       (iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x13bc) + 0x10) + 0x2c), iVar1 != 0)) {
      iVar2 = iVar2 * 0x40 + param_1 + 0x262c;
      if (*(float *)(iVar2 + 0x78c) == -32760.0) {
        iVar6 = *(int *)(iVar1 + 8);
        *(float *)(iVar2 + 0x78c) = (float10)*(int *)(iVar6 + 4);
        *(float *)(iVar2 + 0x79c) = (float10)*(int *)(iVar6 + 8);
        *(float *)(iVar2 + 0x7ac) = (float10)*(int *)(iVar6 + 0xc);
        *(float *)(iVar2 + 0x7bc) = (float10)*(int *)(iVar6 + 0x10);
      }
      iVar6 = 0;
      if (0 < *(int *)(iVar1 + 4)) {
        local_1c = 0;
        do {
          iVar5 = local_1c + *(int *)(iVar1 + 8);
          iVar6 = iVar6 + 1;
          iVar3 = IntMin((int)GHIDRA_FIST32(*(float *)(iVar2 + 0x78c)),*(int *)(iVar5 + 4));
          iVar4 = *(int *)(iVar5 + 8);
          *(float *)(iVar2 + 0x78c) = (float10)iVar3;
          iVar3 = IntMin((int)GHIDRA_FIST32(*(float *)(iVar2 + 0x79c)),iVar4);
          iVar4 = *(int *)(iVar5 + 0xc);
          *(float *)(iVar2 + 0x79c) = (float10)iVar3;
          iVar3 = IntMax((int)GHIDRA_FIST32(*(float *)(iVar2 + 0x7ac)),iVar4);
          iVar4 = *(int *)(iVar5 + 0x10);
          *(float *)(iVar2 + 0x7ac) = (float10)iVar3;
          iVar4 = IntMax((int)GHIDRA_FIST32(*(float *)(iVar2 + 0x7bc)),iVar4);
          *(float *)(iVar2 + 0x7bc) = (float10)iVar4;
          local_1c = local_1c + 0x14;
        } while (iVar6 < *(int *)(iVar1 + 4));
      }
    }
  }
  return;
}

/* AIIdleClsnMatchState @ 0x080a7620, 66 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x20-byte frame (a local's address escapes, see apply_frame_emulation) */
int AIIdleClsnMatchState(int param_1)

{
  int iVar1;
  unsigned char ghidra_frame[0x20] __attribute__((aligned(16)));
#define local_1c (*(int (*)[7])(ghidra_frame + 0x4))
  
  iVar1 = 0;
  local_1c[0] = 0;
  local_1c[1] = 0x14;
  local_1c[2] = 0xb;
  local_1c[3] = 0x32;
  do {
    if (param_1 == local_1c[iVar1]) {
      return iVar1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 4);
  return -1;
}
#undef local_1c

/* PlayerAILearnMoveEnd @ 0x080a7670, 857 bytes
 * FIXUP: removed 2 x87 control-word save statements
 * FIXUP: 6 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 27 stack locals placed at their original offsets in a 0x90-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 PlayerAILearnMoveEnd(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  void *pvVar3;
  int iVar4;
  int iVar5;
  undefined2 in_FPUControlWord;
  unsigned char ghidra_frame[0x90] __attribute__((aligned(16)));
#define local_8c (*(float *)(ghidra_frame + 0x4))
#define local_88 (*(undefined4 *)(ghidra_frame + 0x8))
#define local_84 (*(undefined4 *)(ghidra_frame + 0xc))
#define uStack_80 (*(undefined4 *)(ghidra_frame + 0x10))
#define local_7c (*(float *)(ghidra_frame + 0x14))
#define local_78 (*(undefined4 *)(ghidra_frame + 0x18))
#define local_74 (*(undefined4 *)(ghidra_frame + 0x1c))
#define local_70 (*(undefined4 *)(ghidra_frame + 0x20))
#define fStack_6c (*(float *)(ghidra_frame + 0x24))
#define local_68 (*(undefined4 *)(ghidra_frame + 0x28))
#define local_64 (*(undefined4 *)(ghidra_frame + 0x2c))
#define local_60 (*(undefined4 *)(ghidra_frame + 0x30))
#define local_5c (*(float *)(ghidra_frame + 0x34))
#define local_58 (*(undefined4 *)(ghidra_frame + 0x38))
#define local_54 (*(undefined4 *)(ghidra_frame + 0x3c))
#define local_50 (*(undefined4 *)(ghidra_frame + 0x40))
#define local_44 (*(float *)(ghidra_frame + 0x4c))
#define local_40 (*(undefined2 *)(ghidra_frame + 0x50))
#define uStack_3e (*(undefined2 *)(ghidra_frame + 0x52))
#define local_3c (*(float *)(ghidra_frame + 0x54))
#define local_38 (*(undefined4 *)(ghidra_frame + 0x58))
#define uStack_34 (*(undefined4 *)(ghidra_frame + 0x5c))
#define local_30 (*(undefined4 *)(ghidra_frame + 0x60))
#define local_2c (*(float *)(ghidra_frame + 0x64))
#define local_28 (*(undefined4 *)(ghidra_frame + 0x68))
#define local_24 (*(undefined4 *)(ghidra_frame + 0x6c))
#define uStack_20 (*(undefined4 *)(ghidra_frame + 0x70))
  
  iVar5 = param_1 + 0x2dac;
  pvVar3 = (void *)(param_1 + 0x2edc);
  if (*(int *)(param_1 + 0x2dac) == 0) {
    return 0;
  }
  if (param_2 != 0) {
    iVar2 = *(int *)(param_1 + 0x2ed8);
    AIValMake(&local_2c,*(float *)(param_1 + 0x2ebc));
    iVar4 = iVar2 * 0x30;
    *(float *)(iVar4 + 0x424 + (int)pvVar3) = local_2c;
    *(undefined4 *)(iVar4 + 0x428 + (int)pvVar3) = local_28;
    *(undefined4 *)(iVar4 + 0x42c + (int)pvVar3) = local_24;
    *(undefined4 *)(iVar4 + 0x430 + (int)pvVar3) = uStack_20;
    local_44 = GHIDRA_I2F((int)GHIDRA_FIST32((*(float *)(param_1 + 0x19c) - (float10)*(int *)(param_1 + 0x2ec4)) *
                                 (float10)*(int *)(param_1 + 0x2ecc)));
    AIValMake(&local_3c,local_44);
    *(float *)(iVar4 + 0x434 + (int)pvVar3) = local_3c;
    *(undefined4 *)(iVar4 + 0x438 + (int)pvVar3) = local_38;
    *(undefined4 *)(iVar4 + 0x43c + (int)pvVar3) = uStack_34;
    *(undefined4 *)(iVar4 + 0x440 + (int)pvVar3) = local_30;
    local_44 = GHIDRA_I2F((int)GHIDRA_FIST32(*(float *)(param_1 + 0x1a0) - (float10)*(int *)(param_1 + 0x2ec8)));
    AIValMake(&local_5c,local_44);
    *(float *)(iVar4 + 0x444 + (int)pvVar3) = local_5c;
    *(undefined4 *)(iVar4 + 0x448 + (int)pvVar3) = local_58;
    *(undefined4 *)(iVar4 + 0x44c + (int)pvVar3) = local_54;
    *(undefined4 *)(iVar4 + 0x450 + (int)pvVar3) = local_50;
    if ((*(float *)(iVar4 + 0x394 + (int)pvVar3) == 0.0) && (*(int *)(param_1 + 0xe0c) != 0)) {
      AIValMake(&fStack_6c,*(float *)(param_1 + 0x2ebc));
      *(float *)(iVar4 + 0x394 + (int)pvVar3) = fStack_6c;
      *(undefined4 *)(iVar4 + 0x398 + (int)pvVar3) = local_68;
      *(undefined4 *)(iVar4 + 0x39c + (int)pvVar3) = local_64;
      *(undefined4 *)(iVar4 + 0x3a0 + (int)pvVar3) = local_60;
      local_44 = GHIDRA_I2F((int)GHIDRA_FIST32((*(float *)(param_1 + 0x19c) - (float10)*(int *)(param_1 + 0x2ec4))
                                   * (float10)*(int *)(param_1 + 0x2ecc)));
      AIValMake(&local_7c,local_44);
      *(float *)(iVar4 + 0x3a4 + (int)pvVar3) = local_7c;
      *(undefined4 *)(iVar4 + 0x3a8 + (int)pvVar3) = local_78;
      *(undefined4 *)(iVar4 + 0x3ac + (int)pvVar3) = local_74;
      *(undefined4 *)(iVar4 + 0x3b0 + (int)pvVar3) = local_70;
      local_44 = GHIDRA_I2F((int)GHIDRA_FIST32(*(float *)(param_1 + 0x1a0) - (float10)*(int *)(param_1 + 0x2ec8)));
      AIValMake(&local_8c,local_44);
      *(float *)(iVar4 + 0x3b4 + (int)pvVar3) = local_8c;
      *(undefined4 *)(iVar4 + 0x3b8 + (int)pvVar3) = local_88;
      *(undefined4 *)(iVar4 + 0x3bc + (int)pvVar3) = local_84;
      *(undefined4 *)(iVar4 + 0x3c0 + (int)pvVar3) = uStack_80;
    }
    iVar4 = AIFetchLearnDataArray(iVar5,*(int *)(param_1 + 0x2ec0));
    if (iVar4 != 0) {
      uVar1 = ArrayFind(iVar4,0,*(int *)(param_1 + 0x30e0));
      if (uVar1 == 0xffffffff) {
        iVar2 = ArrayAdd(iVar4,pvVar3,0,*(undefined4 *)(param_1 + 0x30e0));
        if (iVar2 == -1) goto LAB_080a7970;
        ArrayAccessGrpItem(iVar4,0,*(int *)(param_1 + 0x30e0));
      }
      else {
        AIMergeLearnData((int *)(uVar1 * *(int *)(iVar4 + 4) + *(int *)(iVar4 + 0x14)),(int)pvVar3,
                         iVar2);
      }
      AILearnStopRecord(iVar5);
      return 1;
    }
  }
LAB_080a7970:
  AILearnStopRecord(iVar5);
  return 0;
}
#undef local_8c
#undef local_88
#undef local_84
#undef uStack_80
#undef local_7c
#undef local_78
#undef local_74
#undef local_70
#undef fStack_6c
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef local_44
#undef local_40
#undef uStack_3e
#undef local_3c
#undef local_38
#undef uStack_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef uStack_20

/* PlayerAIGetAIPLHS @ 0x080a79d0, 67 bytes */
undefined4 PlayerAIGetAIPLHS(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xe30);
  if (iVar1 == 1) {
    return 1;
  }
  if (iVar1 < 2) {
    if (iVar1 == 0) {
      return 0;
    }
  }
  else if (iVar1 == 2) {
    return 2;
  }
  return 0;
}

/* AIFetchLearnDataArray @ 0x080a7a20, 43 bytes */
undefined4 AIFetchLearnDataArray(int param_1,int param_2)

{
  if (0 < param_2) {
    if (param_2 < 3) {
      return *(undefined4 *)(param_1 + 4);
    }
    if (param_2 == 3) {
      return *(undefined4 *)(param_1 + 8);
    }
  }
  return 0;
}

/* PlayerAIMsgAttack @ 0x080a7a50, 124 bytes */
void PlayerAIMsgAttack(int param_1)

{
  int iVar1;
  undefined4 local_14;
  
  local_14 = 0;
  iVar1 = AIFetchLearnDataArray(param_1 + 0x2dac,*(int *)(param_1 + 0xe00));
  if (iVar1 != 0) {
    local_14 = *(undefined4 *)(param_1 + 0xbf4);
  }
  *(undefined4 *)(param_1 + 0x2ccc) = 1;
  PlayerAIBroadcastMsg(param_1,0,0,local_14,iVar1);
  return;
}

/* PlayerAIMsgAttackEnd @ 0x080a7ad0, 76 bytes */
void PlayerAIMsgAttackEnd(int param_1)

{
  *(undefined4 *)(param_1 + 0x2ccc) = 0;
  PlayerAIBroadcastMsg(param_1,0,1,0xffffffff,0);
  return;
}

/* PlayerAIBroadcastMsg @ 0x080a7b20, 200 bytes */
int PlayerAIBroadcastMsg
              (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
              undefined4 param_5)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  piVar4 = g;
  iVar8 = 0;
  iVar7 = g[0x7459];
  if (iVar7 <= g[0x745a]) {
    iVar6 = iVar7 * 4 + 0x1cf60;
    do {
      iVar1 = *(int *)(iVar6 + 4 + (int)piVar4);
      if ((iVar1 == 0) || (bVar3 = true, *(int *)(iVar1 + 0x158) == 0)) {
        bVar3 = false;
      }
      if (((bVar3) && (iVar1 != param_1)) && (*(int *)(iVar1 + 0x262c) != 0)) {
        iVar2 = *(int *)(iVar1 + 0x2cc8);
        if (iVar2 < 10) {
          iVar5 = iVar2 * 0x10;
          *(int *)(iVar1 + 0x2c28 + iVar5) = param_1;
          *(undefined4 *)(iVar1 + 0x2c2c + iVar5) = param_3;
          *(undefined4 *)(iVar1 + 0x2c30 + iVar5) = param_4;
          *(undefined4 *)(iVar1 + 0x2c34 + iVar5) = param_5;
          *(int *)(iVar1 + 0x2cc8) = iVar2 + 1;
          iVar8 = iVar8 + 1;
        }
      }
      iVar7 = iVar7 + 1;
      iVar6 = iVar6 + 4;
    } while (iVar7 <= piVar4[0x745a]);
  }
  return iVar8;
}

/* PlayerAIFindMsg @ 0x080a7bf0, 65 bytes */
int PlayerAIFindMsg(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  if (0 < *(int *)(param_1 + 0x2cc8)) {
    iVar2 = 0;
    do {
      if (*(int *)(param_1 + 0x2c2c + iVar2) == param_3) {
        if (param_2 == 0) {
          return iVar1;
        }
        if (param_2 == *(int *)(param_1 + 0x2c28 + iVar2)) {
          return iVar1;
        }
      }
      iVar1 = iVar1 + 1;
      iVar2 = iVar2 + 0x10;
    } while (iVar1 < *(int *)(param_1 + 0x2cc8));
  }
  return -1;
}

/* PlayerAIGetMsg @ 0x080a7c40, 145 bytes */
undefined4 * PlayerAIGetMsg(undefined4 *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  iVar1 = PlayerAIFindMsg(param_2,param_3,param_4);
  local_1c = 0;
  local_14 = 0;
  local_10 = 0;
  local_18 = 0xffffffff;
  if (iVar1 != -1) {
    iVar1 = iVar1 * 0x10;
    local_1c = *(undefined4 *)(iVar1 + 0x2c28 + param_2);
    local_18 = *(undefined4 *)(iVar1 + 0x2c2c + param_2);
    local_14 = *(undefined4 *)(iVar1 + 0x2c30 + param_2);
    local_10 = *(undefined4 *)(iVar1 + 0x2c34 + param_2);
  }
  *param_1 = local_1c;
  param_1[1] = local_18;
  param_1[2] = local_14;
  param_1[3] = local_10;
  return param_1;
}

/* PlayerAIGetAndRemoveMsg @ 0x080a7ce0, 153 bytes */
undefined4 * PlayerAIGetAndRemoveMsg(undefined4 *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  iVar1 = PlayerAIFindMsg(param_2,param_3,param_4);
  local_1c = 0;
  local_14 = 0;
  local_10 = 0;
  local_18 = 0xffffffff;
  if (iVar1 != -1) {
    iVar1 = iVar1 * 0x10;
    local_1c = *(undefined4 *)(iVar1 + 0x2c28 + param_2);
    local_18 = *(undefined4 *)(iVar1 + 0x2c2c + param_2);
    local_14 = *(undefined4 *)(iVar1 + 0x2c30 + param_2);
    local_10 = *(undefined4 *)(iVar1 + 0x2c34 + param_2);
    *(undefined4 *)(iVar1 + 0x2c2c + param_2) = 2;
  }
  *param_1 = local_1c;
  param_1[1] = local_18;
  param_1[2] = local_14;
  param_1[3] = local_10;
  return param_1;
}

/* PlayerAIClearMsg @ 0x080a7d80, 15 bytes */
void PlayerAIClearMsg(int param_1)

{
  *(undefined4 *)(param_1 + 0x2cc8) = 0;
  return;
}

/* PlayerAIMsgStateUpdate @ 0x080a7d90, 68 bytes */
void PlayerAIMsgStateUpdate(int param_1)

{
  if ((*(int *)(param_1 + 0x2ccc) == 1) &&
     ((((*(int *)(param_1 + 0xe04) == 0 && (*(int *)(param_1 + 0xe0c) != 0)) ||
       (*(int *)(param_1 + 0xbec) != 0)) || (*(int *)(param_1 + 0xe04) == 2)))) {
    PlayerAIMsgAttackEnd(param_1);
    return;
  }
  return;
}

/* PlayerAISctrlProjectile @ 0x080a7de0, 17 bytes */
void PlayerAISctrlProjectile(int param_1,undefined4 *param_2)

{
  *(undefined4 *)(param_1 + 0x33e4) = *param_2;
  return;
}

/* AIForNormal @ 0x080a7e00, 293 bytes */
void AIForNormal(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int local_14;
  
  local_14 = 100;
  do {
    iVar1 = AIForNormalDecisions(param_1,param_2);
    iVar2 = 0;
    switch(*(undefined4 *)(param_1 + 0x2630)) {
    case 0:
      iVar2 = AIForNormalIdle(param_1);
      break;
    case 1:
      iVar2 = AIForNormalMove(param_1);
      break;
    case 2:
      iVar2 = AIForNormalAttack(param_1,param_2);
      break;
    case 3:
      iVar2 = AIForNormalGuard(param_1,param_2);
      break;
    case 4:
      iVar2 = AIForNormalRandom(param_1,*(int *)(param_1 + 0x3424),param_2);
    }
  } while (((iVar1 != 0) || (iVar2 != 0)) && (local_14 = local_14 + -1, local_14 != 0));
  *(int *)(param_1 + 0x2638) = *(int *)(param_1 + 0x2638) + 1;
  if (0 < *(int *)(param_1 + 0x2b54)) {
    *(int *)(param_1 + 0x2b54) = *(int *)(param_1 + 0x2b54) + -1;
  }
  if (*(int *)(param_1 + 0x2b44) == 0) {
    if ((*(int *)(param_1 + 0x268c) == 0) || (*(int *)(*(int *)(param_1 + 0x268c) + 0xe04) != 1)) {
      *(int *)(param_1 + 0x2b4c) = *(int *)(param_1 + 0x2b4c) + 1;
      return;
    }
  }
  else if (((*(int *)(param_1 + 0x268c) != 0) && (*(int *)(*(int *)(param_1 + 0x268c) + 0xe18) == 0)
           ) && (g[0x74f3] == -1)) {
    *(int *)(param_1 + 0x2b48) = *(int *)(param_1 + 0x2b48) + 1;
  }
  *(undefined4 *)(param_1 + 0x2b4c) = 0;
  return;
}

/* AIForNormalDecisions @ 0x080a7f30, 1946 bytes
 * FIXUP: 4 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 8 stack locals placed at their original offsets in a 0x50-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
/* WARNING: Removing unreachable block (ram,0x080a8383) */

undefined4 AIForNormalDecisions(int param_1,int param_2)

{
  float10 fVar1;
  bool bVar2;
  int iVar3;
  long lVar4;
  int iVar5;
  uint uVar6;
  undefined4 *puVar7;
  undefined4 uVar8;
  unsigned char ghidra_frame[0x50] __attribute__((aligned(16)));
#define local_50 (*(float *)(ghidra_frame + 0x0))
#define local_4c (*(int *)(ghidra_frame + 0x4))
#define local_40 (*(int *)(ghidra_frame + 0x10))
#define local_38 (*(undefined4 **)(ghidra_frame + 0x18))
#define local_34 (*(uint *)(ghidra_frame + 0x1c))
#define local_2c (*(undefined4 *)(ghidra_frame + 0x24))
#define local_28 (*(int *)(ghidra_frame + 0x28))
#define iStack_20 (*(int *)(ghidra_frame + 0x30))
  
  local_38 = (undefined4 *)0x0;
  iVar5 = *(int *)(param_1 + 0x268c);
  local_40 = (int)GHIDRA_FIST32(*(float *)(param_1 + 0x19c) - *(float *)(*(int *)(param_1 + 0x3424) + 0x19c)
                       );
  if (local_40 < 0) {
    local_40 = -local_40;
  }
  iVar3 = *(int *)(param_1 + 0x3424);
  if (iVar3 == 0) {
    return 0;
  }
  if ((*(int *)(param_1 + 0x2630) == 0) && (*(int *)(iVar3 + 0x2ec) != 0)) {
    AIMovePlanRoute(param_1,param_2,
                    (int)GHIDRA_FIST32(*(float *)(*(int *)(param_1 + 0x3424) + 0x19c) -
                               (float)(*(int *)(param_1 + 400) * 0x28)),
                    (int)GHIDRA_FIST32(*(float *)(iVar3 + 0x1a0)));
    uVar8 = 1;
    goto LAB_080a86b4;
  }
  if ((*(int *)(param_1 + 0x2630) == 1) && (iVar3 = AIMoveReachedDest(param_1), iVar3 != 0)) {
    AIKBReleaseDir(param_1);
  }
  else {
    PlayerAIGetMsg(&local_2c,param_1,*(int *)(param_1 + 0x3424),1);
    if (((local_28 != -1) || (iVar3 = *(int *)(*(int *)(param_1 + 0x3424) + 0xe04), iVar3 == 0)) ||
       (iVar3 == 2)) {
      *(undefined4 *)(param_1 + 0x2b44) = 0;
      *(undefined4 *)(param_1 + 0x2b48) = 0;
    }
    if ((*(int *)(param_1 + 0x2630) == 0) && (param_2 != 9)) {
      lVar4 = random();
      iVar3 = lVar4 % 0x3c;
      if (0x96 < *(int *)(param_1 + 0x2638)) {
        iVar3 = iVar3 / 2;
      }
      if (local_40 < 100) {
        iVar3 = iVar3 / 2;
      }
      if (local_40 < 0x32) {
        iVar3 = iVar3 / 2;
      }
      if ((*(int *)(param_1 + 0xe04) == 2) && (2 < *(int *)(param_1 + 0x102c))) {
        iVar3 = iVar3 / 2;
      }
      if ((*(int *)(param_1 + 0xe04) == 2) && (*(int *)(param_1 + 0xe00) == 4)) {
        iVar3 = iVar3 / 2;
      }
      if ((iVar3 == 0) || ((0 < *(int *)(param_1 + 0x2638) && (*(int *)(param_1 + 0x139c) != 0)))) {
        uVar8 = 4;
        goto LAB_080a86b4;
      }
    }
    PlayerAIGetAndRemoveMsg(&local_2c,param_1,*(int *)(param_1 + 0x3424),0);
    if ((local_28 != -1) && (lVar4 = random(), lVar4 % 0xc < param_2 + 3)) {
      if (iStack_20 != 0) {
        local_38 = *(undefined4 **)(*(int *)(param_1 + 0x3424) + 0x267c);
      }
      if (local_38 != (undefined4 *)0x0) {
        puVar7 = (undefined4 *)(param_1 + 0x2690);
        for (iVar3 = 0x12d; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar7 = *local_38;
          local_38 = local_38 + 1;
          puVar7 = puVar7 + 1;
        }
        *(undefined4 *)(param_1 + 0x2b44) = 1;
        *(undefined4 *)(param_1 + 0x2b48) = 0;
        *(undefined4 *)(param_1 + 0x268c) = *(undefined4 *)(param_1 + 0x3424);
      }
    }
    uVar6 = *(uint *)(param_1 + 0x2630);
    if ((((uVar6 < 2) || (uVar6 == 4)) && (*(int *)(param_1 + 0x2b44) != 0)) &&
       (((*(int *)(param_1 + 0x2b54) == 0 && (uVar6 != 3)) &&
        ((uVar6 != 2 || (2 < *(int *)(param_1 + 0x2638))))))) {
      if ((*(int *)(param_1 + 0xe0c) != 0) &&
         (((float10)*(int *)(param_1 + 0x2b48) < *(float *)(param_1 + 0x28f4) ||
          (*(float *)(param_1 + 0x28f4) == 0.0)))) {
        iVar3 = AIAttackInRange(param_1,param_2,*(int *)(param_1 + 0x3424),param_1 + 0x2690);
        if (0 < iVar3) {
          *(undefined4 *)(param_1 + 0x2b54) = 5;
          if (param_2 - 1U < 3) {
            lVar4 = random();
            *(int *)(param_1 + 0x2b54) = *(int *)(param_1 + 0x2b54) + lVar4 % (4 - param_2);
          }
          lVar4 = random();
          if (lVar4 % 0x14 <= param_2 + 0xb) {
            uVar8 = 3;
            goto LAB_080a86b4;
          }
        }
        uVar6 = *(uint *)(param_1 + 0x2630);
      }
    }
    if (uVar6 != 3) {
      return 0;
    }
    if (*(int *)(param_1 + 0x2b44) != 0) {
      if ((iVar5 == 0) || (bVar2 = true, *(int *)(iVar5 + 0x158) == 0)) {
        bVar2 = false;
      }
      if ((bVar2) && (*(int *)(param_1 + 0x2b44) != 0)) {
        iVar3 = *(int *)(param_1 + 0x2b48);
        if (param_1 + 0x2690 == 0) {
          return 0;
        }
        local_4c = *(int *)(iVar5 + 0x2ed8);
        if ((local_4c == 0) && ((int)GHIDRA_FIST32(*(float *)(param_1 + 0x28f4)) == 0)) {
          local_4c = 1;
        }
        if ((local_4c == 1) && ((int)GHIDRA_FIST32(*(float *)(param_1 + 0x2924)) == 0)) {
          local_4c = 2;
        }
        PlayerAIGetMsg(&local_2c,param_1,*(int *)(param_1 + 0x3424),0);
        if (local_28 == -1) {
          if ((iVar3 < 1) || ((int)GHIDRA_FIST32(*(float *)(param_1 + 0x28c4)) <= iVar3)) {
LAB_080a8558:
            local_50 = (float10)iVar3;
            if ((*(int *)(param_1 + 0x2638) == 0) &&
               (uVar6 = *(uint *)(param_1 + 0x2a08), uVar6 != 0xffffffff)) {
              if ((uVar6 & 0xc) == 0xc) {
                *(uint *)(param_1 + 0x2b58) = (uint)(*(int *)(param_1 + 0xe00) == 2);
              }
              else {
                *(uint *)(param_1 + 0x2b58) = uVar6 >> 3 & 1;
              }
            }
            fVar1 = *(float *)(local_4c * 0x30 + 0x264 + param_1 + 0x2690);
            PlayerAIGetAndRemoveMsg(&local_2c,param_1,*(int *)(param_1 + 0x3424),1);
            if ((local_28 == -1 && local_50 < fVar1) || (*(int *)(param_1 + 0xe0c) == 0)) {
              return 0;
            }
            iVar5 = param_2 * 5;
            if (200 < local_40) {
              iVar5 = iVar5 / 2;
            }
            if (0x96 < local_40) {
              iVar5 = iVar5 / 2;
            }
            if (local_40 < 100) {
              iVar5 = iVar5 + 10;
            }
            if (local_40 < 0x4b) {
              iVar5 = iVar5 + 10;
            }
            if (local_40 < 0x32) {
              iVar5 = iVar5 + 10;
            }
            lVar4 = random();
            if (((iVar5 <= lVar4 % 100) && (param_2 != 9)) ||
               (iVar5 = AIBuildCounterAttackList(param_1,param_2), iVar5 < 1)) goto LAB_080a86b2;
          }
          else {
            iVar5 = iVar3;
            if (iVar3 < 0) {
              iVar5 = iVar3 + 3;
            }
            if (iVar3 < 3) {
              iVar5 = (iVar5 >> 2) + 5;
            }
            else {
              iVar5 = (iVar5 >> 2) + 2;
            }
            local_34 = (uint)GHIDRA_FIST32((float10)iVar5 -
                                   6.0 / (*(float *)(param_1 + 0x28c4) - (float10)iVar3));
            lVar4 = random();
            if (((int)(local_34 & (param_2 == 9) - 1) <= lVar4 % 100) ||
               (iVar5 = AIBuildCounterAttackList(param_1,param_2), iVar5 < 1)) goto LAB_080a8558;
          }
          lVar4 = random();
          AIAttackSetupAttack(param_1,param_2,
                              *(undefined4 *)
                               (param_1 + 0x2b5c + (lVar4 % *(int *)(param_1 + 0x2c24)) * 4));
          uVar8 = 2;
          goto LAB_080a86b4;
        }
      }
    }
  }
LAB_080a86b2:
  uVar8 = 0;
LAB_080a86b4:
  uVar8 = AIChangeState(param_1 + 0x262c,uVar8);
  return uVar8;
}
#undef local_50
#undef local_4c
#undef local_40
#undef local_38
#undef local_34
#undef local_2c
#undef local_28
#undef iStack_20

/* AIMovePlanRoute @ 0x080a86d0, 504 bytes
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
undefined4 AIMovePlanRoute(int param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  float10 fVar2;
  int iVar3;
  undefined4 local_20;
  
  iVar3 = (int)GHIDRA_FIST32((float10)*(int *)(param_1 + 400) * ((float)param_3 - *(float *)(param_1 + 0x19c))
                    );
  *(undefined4 *)(param_1 + 0x2660) = 0;
  *(undefined4 *)(param_1 + 0x266c) = 0;
  if (param_4 == 0) {
    *(int *)(param_1 + 0x2658) = param_3;
    *(undefined4 *)(param_1 + 0x265c) = 0;
    *(undefined4 *)(param_1 + 0x2654) = 1;
  }
  else {
    if (iVar3 < 0) {
      fVar2 = (*(float *)(param_1 + 0xf0) * -2.0 * *(float *)(param_1 + 0xe4)) /
              *(float *)(param_1 + 0x130);
    }
    else {
      fVar2 = (*(float *)(param_1 + 0xec) * -2.0 * *(float *)(param_1 + 0xe4)) /
              *(float *)(param_1 + 0x130);
    }
    local_20 = (int)GHIDRA_FIST32(fVar2);
    iVar1 = (int)GHIDRA_FIST32((-*(float *)(param_1 + 0xe4) * *(float *)(param_1 + 0xe4)) /
                       (*(float *)(param_1 + 0x130) + *(float *)(param_1 + 0x130)));
    if (((iVar3 < 0) || (local_20 <= iVar3)) && ((-1 < iVar3 || (iVar3 <= local_20)))) {
      if (iVar1 < param_4) {
        iVar3 = param_3 - ((local_20 * param_4) / iVar1) * *(int *)(param_1 + 400);
      }
      else {
        iVar3 = (int)GHIDRA_FIST32((double)param_3 -
                           (double)*(int *)(param_1 + 400) * (double)local_20 * 0.5);
      }
      *(int *)(param_1 + 0x2658) = iVar3;
      *(undefined4 *)(param_1 + 0x265c) = 0;
      *(undefined4 *)(param_1 + 0x2654) = 1;
      *(int *)(param_1 + 0x2664) = param_3;
      *(int *)(param_1 + 0x2668) = param_4;
      *(undefined4 *)(param_1 + 0x2660) = 2;
    }
    else {
      *(int *)(param_1 + 0x2658) = param_3;
      *(int *)(param_1 + 0x265c) = param_4;
      *(undefined4 *)(param_1 + 0x2654) = 2;
    }
  }
  return 1;
}

/* AIMoveReachedDest @ 0x080a88d0, 54 bytes */
undefined4 AIMoveReachedDest(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(param_1 + 0x266c);
  if ((iVar1 < 1) && (*(int *)(param_1 + 0x2660 + iVar1 * 0xc) != 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = AIMoveReachedDestIdx(param_1,iVar1);
  }
  return uVar2;
}

/* AIMoveReachedDestIdx @ 0x080a8910, 246 bytes
 * FIXUP: 2 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
undefined4 AIMoveReachedDestIdx(int param_1,int param_2)

{
  float10 fVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = *(int *)(param_2 * 0xc + 0x2c + param_1 + 0x262c);
  iVar3 = *(int *)(param_2 * 0xc + 0x30 + param_1 + 0x262c);
  if (((*(int *)(param_1 + 0x264c) <= iVar2) && ((float)(iVar2 + -1) <= *(float *)(param_1 + 0x19c))
      ) || ((iVar2 <= *(int *)(param_1 + 0x264c) &&
            (*(float *)(param_1 + 0x19c) <= (float)(iVar2 + 1))))) {
    fVar1 = *(float *)(param_1 + 0x1b4);
    if (fVar1 != 0.0) {
      return 1;
    }
    if (*(int *)(param_1 + 0x2644) != 2) {
      return 1;
    }
  }
  else {
    fVar1 = *(float *)(param_1 + 0x1b4);
  }
  if ((fVar1 == 0.0) &&
     (((*(float *)(param_1 + 0x1b8) < 0.0 && (*(float *)(param_1 + 0x1a0) < (float10)iVar3)) ||
      ((fVar1 == 0.0 &&
       ((0.0 < *(float *)(param_1 + 0x1b8) && ((float10)iVar3 <= *(float *)(param_1 + 0x1a0))))))))) {
    return 1;
  }
  return 0;
}

/* AIForNormalIdle @ 0x080a8a10, 189 bytes */
undefined4 AIForNormalIdle(int param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if (*(int *)(param_1 + 0x3424) != 0) {
    if (*(int *)(param_1 + 0x263c) == 1) {
      uVar1 = 3;
    }
    if ((*(int *)(param_1 + 0x2638) == 0) &&
       (*(undefined4 *)(param_1 + 0x2640) = 0, *(int *)(param_1 + 0x2634) == 4)) {
      AIKBReleaseAllExcept(param_1,uVar1);
    }
    if ((*(int *)(param_1 + 0x263c) == 1) && (*(int *)(param_1 + 0x2cc) == 0)) {
      KBIStuffBufNoFlip(param_1 + 0x248,3);
    }
    if (((0 < *(int *)(param_1 + 0x2638)) && (*(int *)(param_1 + 0x2634) - 2U < 2)) &&
       (*(int *)(param_1 + 0x2da8) == 0)) {
      AIKBReleaseDirExcept(param_1,uVar1);
    }
    *(int *)(param_1 + 0x2640) = *(int *)(param_1 + 0x2640) + 1;
  }
  return 0;
}

/* AISetIdleAction @ 0x080a8ad0, 15 bytes */
void AISetIdleAction(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x263c) = param_2;
  return;
}

/* AIForNormalMove @ 0x080a8ae0, 737 bytes
 * REVIEW: calls-missing-in-pid:NAN
 * FIXUP: 7 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
undefined4 AIForNormalMove(int param_1)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint local_20;
  
  local_20 = 0xffffffff;
  iVar1 = param_1 + 0x248;
  if (*(int *)(param_1 + 0x3424) == 0) {
    return 0;
  }
  if (*(int *)(param_1 + 0x2638) == 0) {
    *(undefined4 *)(param_1 + 0x2648) = 0;
  }
  do {
    bVar3 = false;
    iVar5 = *(int *)(param_1 + 0x266c);
    iVar4 = iVar5 * 0xc;
    iVar7 = (int)GHIDRA_FIST32(((float10)*(int *)(iVar4 + 0x2c + param_1 + 0x262c) -
                       *(float *)(param_1 + 0x19c)) * (float10)*(int *)(param_1 + 400));
    iVar2 = (int)GHIDRA_FIST32((float10)*(int *)(iVar4 + 0x30 + param_1 + 0x262c) -
                       *(float *)(param_1 + 0x1a0));
    if (*(int *)(param_1 + 0x2648) == 0) {
      *(int *)(param_1 + 0x264c) = (int)GHIDRA_FIST32(*(float *)(param_1 + 0x19c));
      *(int *)(param_1 + 0x2650) = (int)GHIDRA_FIST32(*(float *)(param_1 + 0x1a0));
      *(undefined4 *)(param_1 + 0x2644) = *(undefined4 *)(iVar4 + param_1 + 0x2654);
    }
    else if (((iVar5 < 1) && (*(int *)(param_1 + 0x2660 + iVar4) != 0)) &&
            (iVar5 = AIMoveReachedDestIdx(param_1,iVar5), iVar5 != 0)) {
      *(int *)(param_1 + 0x266c) = *(int *)(param_1 + 0x266c) + 1;
      *(undefined4 *)(param_1 + 0x2648) = 0;
      bVar3 = true;
    }
  } while (bVar3);
  if (*(int *)(param_1 + 0x2644) == 1) {
    if (iVar7 < 1) {
      if (iVar7 < 0) {
        local_20 = 4;
      }
    }
    else {
      local_20 = 2;
    }
    uVar6 = 1;
    iVar7 = 0x74;
    do {
      if ((*(int *)(iVar7 + param_1 + 0x250) != 0) && (uVar6 != local_20)) {
        KBIStuffBufNoFlip(iVar1,uVar6 | 0x10);
      }
      uVar6 = uVar6 + 1;
      iVar7 = iVar7 + 4;
    } while ((int)uVar6 < 5);
    if ((local_20 == 0xffffffff) || (*(int *)(param_1 + 0x2c0 + local_20 * 4) != 0))
    goto LAB_080a8db0;
  }
  else {
    if ((*(int *)(param_1 + 0x2644) != 2) || (*(int *)(param_1 + 0xe00) == 3)) goto LAB_080a8db0;
    if (iVar7 < 1) {
      if ((iVar7 < 0) &&
         ((float10)iVar2 * *(float *)(param_1 + 0xf0) < (float10)iVar7 * *(float *)(param_1 + 0xe4))) {
        local_20 = 4;
      }
    }
    else if ((float10)iVar7 * *(float *)(param_1 + 0xe4) < (float10)iVar2 * *(float *)(param_1 + 0xec))
    {
      local_20 = 2;
    }
    uVar6 = 1;
    iVar7 = 0x74;
    do {
      if (((*(int *)(iVar7 + 8 + iVar1) != 0) && (uVar6 != local_20)) && (uVar6 != 1)) {
        KBIStuffBufNoFlip(iVar1,uVar6 | 0x10);
      }
      uVar6 = uVar6 + 1;
      iVar7 = iVar7 + 4;
    } while ((int)uVar6 < 5);
    if ((local_20 != 0xffffffff) && (*(int *)(param_1 + 0x2c0 + local_20 * 4) == 0)) {
      KBIStuffBufNoFlip(iVar1,local_20);
    }
    if (*(int *)(param_1 + 0x2c4) != 0) goto LAB_080a8db0;
    local_20 = 1;
  }
  KBIStuffBufNoFlip(iVar1,local_20);
LAB_080a8db0:
  *(int *)(param_1 + 0x2648) = *(int *)(param_1 + 0x2648) + 1;
  return 0;
}

/* AIForNormalAttack @ 0x080a8dd0, 474 bytes */
undefined4 AIForNormalAttack(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 local_18;
  
  iVar2 = *(int *)(param_1 + 0x2670);
  iVar1 = param_1 + 0x248;
  if (iVar2 == 0) {
    uVar3 = AIChangeState(param_1 + 0x262c,0);
    return uVar3;
  }
  if (*(int *)(param_1 + 0x2638) == 0) {
    *(undefined4 *)(param_1 + 0x2674) = 0;
    iVar5 = 0;
    local_18 = *(int *)(iVar2 + 0x200);
    if (0 < local_18) {
      iVar4 = *(int *)(iVar2 + 4);
      if (iVar4 == *(int *)(param_1 + 0xe00)) {
        *(int *)(param_1 + 0x2674) = iVar4;
      }
      else {
        do {
          if (*(int *)(param_1 + 0x2674) == 0) {
            *(int *)(param_1 + 0x2674) = iVar4;
            local_18 = *(int *)(iVar2 + 0x200);
          }
          iVar5 = iVar5 + 1;
          if (local_18 <= iVar5) goto LAB_080a8e87;
          iVar4 = *(int *)(iVar5 * 0x10 + 4 + iVar2);
        } while (iVar4 != *(int *)(param_1 + 0xe00));
        *(int *)(param_1 + 0x2674) = iVar4;
      }
    }
  }
LAB_080a8e87:
  if (*(int *)(param_1 + 0x2678) != 0) goto LAB_080a8f6e;
  iVar5 = *(int *)(param_1 + 0x2674);
  if (iVar5 == 0) {
LAB_080a8f3b:
    iVar4 = *(int *)(param_1 + 0xe00);
  }
  else {
    iVar4 = *(int *)(param_1 + 0xe00);
    if (iVar4 != iVar5) {
      if (iVar5 == 2) {
        if (*(int *)(param_1 + 0x2c4) != 0) {
          KBIStuffBufNoFlip(iVar1,0x11);
        }
        if (*(int *)(param_1 + 0x2cc) == 0) {
          KBIStuffBufNoFlip(iVar1,3);
        }
      }
      if (iVar5 == 1) {
        if (*(int *)(param_1 + 0x2c4) != 0) {
          KBIStuffBufNoFlip(iVar1,0x11);
        }
        if (*(int *)(param_1 + 0x2cc) != 0) {
          KBIStuffBufNoFlip(iVar1,0x13);
        }
      }
      if (iVar5 == 3) {
        if (*(int *)(param_1 + 0x2cc) != 0) {
          KBIStuffBufNoFlip(iVar1,0x13);
        }
        if (*(int *)(param_1 + 0x2c4) == 0) {
          KBIStuffBufNoFlip(iVar1,1);
        }
      }
      goto LAB_080a8f3b;
    }
  }
  if ((iVar4 == iVar5) || (4 < *(int *)(param_1 + 0x2638))) {
    AIInsertCommand((int *)(param_1 + 0x33fc),*(int *)(iVar2 + 0x20c));
    *(undefined4 *)(param_1 + 0x2678) = 1;
  }
LAB_080a8f6e:
  if (((*(int *)(param_1 + 0xe04) == 0) && (*(int *)(param_1 + 0x2678) != 0)) &&
     (0 < *(int *)(param_1 + 0x2638))) {
    uVar3 = AIChangeState(param_1 + 0x262c,0);
    return uVar3;
  }
  return 0;
}

/* AIAttackSetupAttack @ 0x080a8fb0, 40 bytes */
undefined4 AIAttackSetupAttack(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0x2670) = param_3;
  *(undefined4 *)(param_1 + 0x2674) = 0;
  *(undefined4 *)(param_1 + 0x2678) = 0;
  return 1;
}

/* AIForNormalGuard @ 0x080a8fe0, 211 bytes */
undefined4 AIForNormalGuard(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  iVar1 = param_1 + 0x248;
  if (*(int *)(param_1 + 0x3424) == 0) {
    uVar2 = AIChangeState(param_1 + 0x262c,0);
    return uVar2;
  }
  if (((*(int *)(param_1 + 0x2da8) != 0) && (*(int *)(param_1 + 0xe04) == 0)) &&
     (*(int *)(param_1 + 0xe0c) != 0)) {
    if (*(int *)(param_1 + 0x2c4) != 0) {
      KBIStuffBufNoFlip(iVar1,0x11);
    }
    if (*(int *)(param_1 + 0x2c8) != 0) {
      KBIStuffBufNoFlip(iVar1,0x12);
    }
    if (*(int *)(param_1 + 0x2d0) == 0) {
      KBIStuffBufNoFlip(iVar1,4);
    }
    if (*(int *)(param_1 + 0x2b58) == 0) {
      if (*(int *)(param_1 + 0x2cc) == 0) {
        return 0;
      }
      uVar3 = 0x13;
    }
    else {
      if (*(int *)(param_1 + 0x2cc) != 0) {
        return 0;
      }
      uVar3 = 3;
    }
    KBIStuffBufNoFlip(iVar1,uVar3);
  }
  return 0;
}

/* AIAttackInRange @ 0x080a90c0, 723 bytes
 * FIXUP: frame emulation: 7 stack locals placed at their original offsets in a 0xa0-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 6 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
int AIAttackInRange(int param_1,undefined4 param_2,int param_3,int param_4)

{
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  float10 fVar5;
  float10 fVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  float *pfVar12;
  unsigned char ghidra_frame[0xa0] __attribute__((aligned(16)));
#define local_a0 (*(int **)(ghidra_frame + 0x0))
#define local_94 (*(uint *)(ghidra_frame + 0xc))
#define local_90 (*(uint *)(ghidra_frame + 0x10))
#define local_8c (*(int **)(ghidra_frame + 0x14))
#define local_88 (*(int **)(ghidra_frame + 0x18))
#define local_7c (*(int (*)[12])(ghidra_frame + 0x24))
#define local_4c (*(int (*)[15])(ghidra_frame + 0x54))
  
  local_90 = (uint)(*(int *)(param_1 + 400) != 1);
  local_94 = (uint)(*(int *)(param_3 + 400) != 1);
  fVar1 = *(float *)(param_1 + 0x19c);
  fVar2 = *(float *)(param_3 + 0x19c);
  fVar3 = *(float *)(param_1 + 0x1a0);
  fVar4 = *(float *)(param_3 + 0x1a0);
  iVar8 = *(int *)(*(int *)(param_1 + 0x13bc) + 0x10);
  if ((iVar8 != 0) && (iVar10 = *(int *)(*(int *)(param_3 + 0x13bc) + 0x10), iVar10 != 0)) {
    local_88 = *(int **)(iVar8 + 0x2c);
    local_8c = *(int **)(iVar10 + 0x28);
    iVar10 = 0;
    local_a0 = local_7c;
    piVar11 = local_4c;
    for (iVar8 = 10; iVar8 != 0; iVar8 = iVar8 + -1) {
      *piVar11 = 0;
      piVar11 = piVar11 + 1;
    }
    iVar8 = 0;
    do {
      if (iVar10 == 0) {
        iVar7 = *(int *)(param_1 + 0x267c);
        iVar9 = param_1;
      }
      else {
        iVar7 = *(int *)(param_3 + 0x267c);
        iVar9 = param_3;
        if (param_4 != 0) {
          iVar7 = param_4;
        }
      }
      pfVar12 = (float *)(iVar7 + 0x2f4U & (iVar7 == 0) - 1);
      if ((iVar10 == 0) && (iVar7 = AIIdleClsnMatchState(*(int *)(iVar9 + 0xbf4)), iVar7 != -1)) {
        pfVar12 = (float *)(iVar7 * 0x40 + 0x2db8 + iVar9);
      }
      piVar11 = local_88;
      if ((pfVar12 != (float *)0x0) && (fVar5 = *pfVar12, fVar5 != -32760.0)) {
        *(undefined4 *)((int)local_7c + iVar8) = 0;
        fVar6 = pfVar12[4];
        *(int *)((int)local_7c + iVar8 + 4) = (int)GHIDRA_FIST32(fVar5);
        fVar5 = pfVar12[8];
        *(int *)((int)local_7c + iVar8 + 8) = (int)GHIDRA_FIST32(fVar6);
        fVar6 = pfVar12[0xc];
        *(int *)((int)local_7c + iVar8 + 0xc) = (int)GHIDRA_FIST32(fVar5);
        *(int *)((int)local_7c + iVar8 + 0x10) = (int)GHIDRA_FIST32(fVar6);
        *(undefined4 *)(iVar8 + (int)local_4c) = 1;
        *(undefined4 *)((int)local_4c + iVar8 + 4) = 1;
        *(int **)((int)local_4c + iVar8 + 8) = local_a0;
        piVar11 = local_4c;
        if (iVar10 != 0) {
          local_8c = (int *)((int)local_4c + iVar8);
          piVar11 = local_88;
        }
      }
      local_88 = piVar11;
      iVar10 = iVar10 + 1;
      local_a0 = local_a0 + 5;
      iVar8 = iVar8 + 0x14;
    } while (iVar10 < 2);
    if ((((local_88 != (int *)0x0) && (local_8c != (int *)0x0)) && (*local_88 != 0)) &&
       (*local_8c != 0)) {
      iVar8 = ClsnArrayDetectRectFlip
                        (local_88,local_8c,(int)GHIDRA_FIST32(fVar2 - fVar1),(int)GHIDRA_FIST32(fVar4 - fVar3),
                         local_90,local_94);
      return ((iVar8 != 0) - 1 & 0xffffff9c) + 100;
    }
  }
  return 0;
}
#undef local_a0
#undef local_94
#undef local_90
#undef local_8c
#undef local_88
#undef local_7c
#undef local_4c

/* AIBuildCounterAttackList @ 0x080a93a0, 661 bytes
 * FIXUP: 3 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
int AIBuildCounterAttackList(int param_1,undefined4 param_2)

{
  int iVar1;
  float10 fVar2;
  int iVar3;
  bool bVar4;
  bool bVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  
  iVar3 = *(int *)(param_1 + 0x268c);
  bVar5 = false;
  *(undefined4 *)(param_1 + 0x2c24) = 0;
  if (*(int *)(param_1 + 0x2b44) != 0) {
    iVar6 = AIFetchLearnDataArray(param_1 + 0x2dac,*(int *)(param_1 + 0xe00));
    if (iVar6 != 0) {
      if ((iVar3 == 0) || (bVar4 = true, *(int *)(iVar3 + 0x158) == 0)) {
        bVar4 = false;
      }
      if (bVar4) {
        uVar10 = *(uint *)(iVar3 + 0x2ed8);
        if (2 < uVar10) {
                    /* WARNING: Subroutine does not return */
          __assert_fail("e_hitstateidx >= 0 && e_hitstateidx < AIPLHS_NUM","src/mugen/p-ai.c",0x783,
                        "AIBuildCounterAttackList");
        }
        fVar2 = *(float *)(param_1 + 0x28c4);
        if (fVar2 <= (float10)*(int *)(param_1 + 0x2b48)) {
          if (*(float *)(uVar10 * 0x30 + 0x394 + param_1 + 0x2690) == 0.0) {
            return 0;
          }
          fVar2 = *(float *)(uVar10 * 0x30 + 0x394 + param_1 + 0x2690);
        }
        else {
          bVar5 = true;
        }
        iVar1 = (int)GHIDRA_FIST32(fVar2 - (float10)*(int *)(param_1 + 0x2b48));
        iVar11 = 0;
        iVar7 = ArrayScanFirst(iVar6);
        if (iVar7 != 0) {
          do {
            uVar10 = ((float10)iVar1 <= *(float *)(iVar7 + 0x234)) - 1 & 100;
            iVar8 = AIAttackInRange(iVar3,param_2,param_1,iVar7);
            if (iVar8 == 0) {
              uVar10 = uVar10 - 100;
            }
            if (*(int *)(iVar7 + 0x380) != 0) {
              if (bVar5) {
                if ((int)GHIDRA_FIST32(*(float *)(iVar7 + 0x264)) < iVar1) {
                  uVar10 = uVar10 - 100;
                }
                uVar9 = *(uint *)(param_1 + 0x2a0c) & *(uint *)(iVar7 + 0x380);
                if (((uVar9 & 7) != 0) && ((uVar9 & 0xfffffff8) != 0)) goto LAB_080a95ac;
              }
              uVar10 = uVar10 - 100;
            }
LAB_080a95ac:
            if ((((*(uint *)(param_1 + 0x2a10) != 0) &&
                 (uVar9 = *(uint *)(param_1 + 0x2a10) & *(uint *)(iVar7 + 0x37c), bVar5)) &&
                ((uVar9 & 7) != 0)) && ((uVar9 & 0xfffffff8) != 0)) {
              uVar10 = uVar10 - 100;
            }
            if (*(int *)(param_1 + 0xe0c) == 0) {
              uVar10 = uVar10 - 100;
            }
            if (0 < (int)uVar10) {
              *(int *)(param_1 + 0x2b5c + iVar11 * 4) = iVar7;
              iVar11 = iVar11 + 1;
            }
            iVar7 = ArrayScanNext(iVar6);
          } while ((iVar7 != 0) && (iVar11 < 0x31));
        }
        *(undefined4 *)(param_1 + 0x2b5c + iVar11 * 4) = 0;
        *(int *)(param_1 + 0x2c24) = iVar11;
        return iVar11;
      }
    }
  }
  return 0;
}

/* AIForNormalRandom @ 0x080a9640, 2057 bytes
 * FIXUP: frame emulation: 4 stack locals placed at their original offsets in a 0x50-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 AIForNormalRandom(int param_1,int param_2,int param_3)

{
  long lVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  int iVar8;
  unsigned char ghidra_frame[0x50] __attribute__((aligned(16)));
#define local_44 (*(uint *)(ghidra_frame + 0xc))
#define local_40 (*(int *)(ghidra_frame + 0x10))
#define local_2c (*(undefined4 *)(ghidra_frame + 0x24))
#define iStack_28 (*(int *)(ghidra_frame + 0x28))
  
  iVar4 = param_1 + 0x2cec;
  iVar5 = param_1 + 0x248;
  local_40 = (int)GHIDRA_FIST32(*(float *)(param_1 + 0x19c) - *(float *)(param_2 + 0x19c));
  if (local_40 < 0) {
    local_40 = -local_40;
  }
  lVar1 = random();
  uVar6 = lVar1 % 6 + 5;
  lVar1 = random();
  local_44 = lVar1 % 6 + 5;
  if (((param_3 == 9) && (PlayerAIGetAndRemoveMsg(&local_2c,param_1,param_2,1), iStack_28 != -1)) ||
     (PlayerAIGetMsg(&local_2c,param_1,param_2,0), iStack_28 != -1)) {
    uVar2 = AIChangeState(param_1 + 0x262c,0);
    return uVar2;
  }
  lVar1 = random();
  if (lVar1 % 100 == 0) {
    uVar6 = 0xb;
  }
  if ((local_44 == uVar6) || (uVar6 = random(), (uVar6 & 7) != 0)) {
    local_44 = 0;
  }
  iVar8 = *(int *)(param_1 + 0x2da8);
  if (iVar8 != 0) {
    iVar3 = *(int *)(param_1 + 0xe04);
    if ((iVar3 != 0) || (*(int *)(param_1 + 0xe0c) == 0)) goto LAB_080a97a0;
LAB_080a97a9:
    iVar8 = 10;
    iVar3 = *(int *)(param_1 + 0xdfc);
    if (iVar3 < 2) {
      iVar8 = param_3 / 2 + 0x1a;
    }
    if (iVar3 < 5) {
      iVar8 = iVar8 + 5;
    }
    if (10 < iVar3) {
      iVar8 = iVar8 + -5;
    }
    if ((local_40 < 0x1e) && (iVar8 = param_3 / 2 + 6 + iVar8, iVar3 < 2)) {
      iVar8 = iVar8 + 10;
    }
    if (0xa0 < local_40) {
      iVar8 = iVar8 / 2;
    }
    iVar3 = PlayerInGuardDist(param_1,param_2);
    if (iVar3 == 0) {
      iVar8 = iVar8 / 5;
    }
    lVar1 = random();
    if (((param_3 + 6) * iVar8) / 0xe <= lVar1 % 100) {
      iVar8 = *(int *)(param_1 + 0x2da8);
      goto LAB_080a999a;
    }
    if (*(int *)(param_1 + 0xe10) == 0) {
      iVar4 = *(int *)(param_2 + 0xe00);
      if (*(int *)(param_1 + 0x2c4) != 0) {
        KBIStuffBufNoFlip(iVar5,0x11);
      }
      if (*(int *)(param_1 + 0x2c8) != 0) {
        KBIStuffBufNoFlip(iVar5,0x12);
      }
      if (*(int *)(param_1 + 0x2d0) == 0) {
        KBIStuffBufNoFlip(iVar5,4);
      }
      lVar1 = random();
      if ((int)(((iVar4 == 2) - 1 & 0xffffffce) + 0x4b) <= lVar1 % 100) {
        iVar4 = *(int *)(param_1 + 0x2cc);
        goto joined_r0x080a9980;
      }
      if (*(int *)(param_1 + 0x2cc) != 0) {
        return 0;
      }
      uVar6 = 3;
    }
    else {
      lVar1 = random();
      if (0x1d < lVar1 % 100) {
        return 0;
      }
      uVar6 = *(uint *)(param_2 + 0x11cc);
      if (((uVar6 & 0xc) == 8) && (*(int *)(param_1 + 0x2cc) == 0)) {
        KBIStuffBufNoFlip(iVar5,3);
        uVar6 = *(uint *)(param_2 + 0x11cc);
      }
      if ((uVar6 & 0xc) != 4) {
        return 0;
      }
      iVar4 = *(int *)(param_1 + 0x2cc);
joined_r0x080a9980:
      if (iVar4 == 0) {
        return 0;
      }
      uVar6 = 0x13;
    }
    goto LAB_080a9e37;
  }
  iVar3 = *(int *)(param_1 + 0xe04);
LAB_080a97a0:
  if (iVar3 == 2) goto LAB_080a97a9;
LAB_080a999a:
  if ((iVar8 == 0) && (*(int *)(param_1 + 0x2d0) != 0)) {
    KBIStuffBufNoFlip(iVar5,0x14);
  }
  lVar1 = random();
  if (0x39 < lVar1 % 100) goto LAB_080a9d75;
  lVar1 = random();
  if (((lVar1 % 1000 < 0x3e) && (0x7d < local_40)) && (*(int *)(param_1 + 0x2c8) == 0)) {
    uVar6 = 1;
    piVar7 = (int *)(param_1 + 0x2c4);
    do {
      if (*piVar7 != 0) {
        KBIStuffBufNoFlip(iVar5,uVar6 | 0x10);
      }
      uVar6 = uVar6 + 1;
      piVar7 = piVar7 + 1;
    } while ((int)uVar6 < 5);
    lVar1 = random();
    if (lVar1 % 1000 < 0x96) {
      KBIStuffBufNoFlip(iVar5,1);
    }
    lVar1 = random();
    if (lVar1 % 1000 < 0x2ee) {
      KBIStuffBufNoFlip(iVar5,2);
    }
  }
  lVar1 = random();
  if (0x3d < lVar1 % 1000) goto switchD_080a9ada_default;
  uVar6 = 1;
  piVar7 = (int *)(param_1 + 0x2c4);
  do {
    if (*piVar7 != 0) {
      KBIStuffBufNoFlip(iVar5,uVar6 | 0x10);
    }
    uVar6 = uVar6 + 1;
    piVar7 = piVar7 + 1;
  } while ((int)uVar6 < 5);
  lVar1 = random();
  switch(lVar1 % 0x13) {
  case 0:
    KBIStuffBufNoFlip(iVar5,1);
    uVar6 = 4;
    break;
  case 1:
    uVar6 = 1;
    break;
  case 2:
  case 3:
  case 4:
    KBIStuffBufNoFlip(iVar5,1);
    goto LAB_080a9b3c;
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
    goto LAB_080a9b3c;
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
    uVar6 = 4;
    break;
  case 0xf:
    KBIStuffBufNoFlip(iVar5,3);
    uVar6 = 4;
    break;
  case 0x10:
  case 0x11:
    uVar6 = 3;
    break;
  case 0x12:
    KBIStuffBufNoFlip(iVar5,3);
LAB_080a9b3c:
    uVar6 = 2;
    break;
  default:
    goto switchD_080a9ada_default;
  }
  KBIStuffBufNoFlip(iVar5,uVar6);
switchD_080a9ada_default:
  iVar8 = 100;
  if ((*(int *)(param_1 + 0xe04) == 1) && (iVar8 = 0x96, *(int *)(param_1 + 0xe30) == 2)) {
    iVar8 = (param_3 * 0x15e + 0x1068) / 0x14 + 0x96;
  }
  if (local_40 < 0x96) {
    iVar8 = iVar8 + 0x32;
  }
  if (local_40 < 100) {
    iVar8 = iVar8 + 0x4b;
  }
  if (local_40 < 0x3c) {
    iVar8 = param_3 * 5 + 0x69 + iVar8;
  }
  if (local_40 < 0x2d) {
    iVar8 = param_3 * 3 + 0x78 + iVar8;
  }
  if (local_40 < 0x1e) {
    iVar8 = param_3 * 3 + 0x78 + iVar8;
  }
  iVar8 = ((param_3 + 6) * iVar8) / 0xe;
  if (*(int *)(param_1 + 0xe04) == 2) {
    iVar8 = iVar8 / 10;
  }
  lVar1 = random();
  if (lVar1 % 1000 < iVar8) {
    iVar8 = 500;
    if (*(int *)(param_1 + 0xe30) == 2) {
      if ((*(uint *)(param_1 + 0x1164) & 0x6d8) != 0) {
        iVar8 = 0xfa;
      }
    }
    else {
      iVar8 = 0x2ee;
    }
    lVar1 = random();
    if (lVar1 % 1000 < iVar8) {
      lVar1 = random();
      local_44 = lVar1 % 6 + 5;
      if (*(int *)(param_1 + 0x2c0 + local_44 * 4) != 0) {
        local_44 = local_44 | 0x10;
      }
    }
    else {
      uVar6 = 1;
      piVar7 = (int *)(param_1 + 0x2c4);
      do {
        if (*piVar7 != 0) {
          KBIStuffBufNoFlip(iVar5,uVar6 | 0x10);
        }
        uVar6 = uVar6 + 1;
        piVar7 = piVar7 + 1;
      } while ((int)uVar6 < 5);
      lVar1 = random();
      if ((lVar1 % 1000 < param_3 * 0x1e + 0x226) && (g[0x757f] != 0)) {
        lVar1 = random();
        AIInsertCommand((int *)(param_1 + 0x33fc),lVar1 % *(int *)(*(int *)(param_1 + 0x964) + 0xc))
        ;
      }
      KBIStuffBufNoFlip(iVar4,local_44);
      local_44 = local_44 | 0x10;
      iVar5 = iVar4;
    }
    KBIStuffBufNoFlip(iVar5,local_44);
  }
LAB_080a9d75:
  if ((*(int *)(param_1 + 0xe04) == 2) && (*(int *)(param_1 + 0x1070) != 0)) {
    iVar5 = 2;
    if (-20.0 < *(float *)(param_1 + 0x1a0)) {
      iVar5 = 0x14;
    }
    if ((-1.0 < *(float *)(param_1 + 0x1b8)) && (*(float *)(param_1 + 0x1b8) < 3.0)) {
      iVar5 = iVar5 + 8;
    }
    lVar1 = random();
    if (lVar1 % 100 < iVar5) {
      lVar1 = random();
      if (lVar1 % 100 < 0x32) {
        KBIStuffBufNoFlip(iVar4,5);
        uVar6 = 6;
        iVar5 = iVar4;
      }
      else {
        KBIStuffBufNoFlip(iVar4,8);
        uVar6 = 9;
        iVar5 = iVar4;
      }
LAB_080a9e37:
      KBIStuffBufNoFlip(iVar5,uVar6);
    }
  }
  return 0;
}
#undef local_44
#undef local_40
#undef local_2c
#undef iStack_28

/* AIForTrainingMode @ 0x080a9e50, 1796 bytes */
void AIForTrainingMode(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = *(int *)(param_1 + 0x2ce8);
  iVar1 = param_1 + 0x248;
  if (iVar2 != 0) goto LAB_080aa545;
  if (((*(int *)(param_1 + 0x2da8) == 0) || (*(int *)(param_1 + 0xe04) != 0)) ||
     (*(int *)(param_1 + 0xe0c) == 0)) {
LAB_080a9f6f:
    iVar2 = *(int *)(param_1 + 0xe10);
  }
  else {
    if (*(int *)(param_1 + 0x2cd8) == 0) {
      if (*(int *)(param_1 + 0x2d0) != 0) {
        KBIStuffBufNoFlip(iVar1,0x14);
      }
      goto LAB_080a9f6f;
    }
    iVar2 = *(int *)(param_1 + 0xe10);
    if (iVar2 == 0) {
      if (*(int *)(param_1 + 0x2c4) != 0) {
        KBIStuffBufNoFlip(iVar1,0x11);
      }
      if (*(int *)(param_1 + 0x2c8) != 0) {
        KBIStuffBufNoFlip(iVar1,0x12);
      }
      uVar3 = *(uint *)(param_2 + 0x11cc);
      if (((uVar3 & 0xc) == 8) && (*(int *)(param_1 + 0x2cc) == 0)) {
        KBIStuffBufNoFlip(iVar1,3);
        uVar3 = *(uint *)(param_2 + 0x11cc);
      }
      if (((uVar3 & 0xc) == 4) && (*(int *)(param_1 + 0x2cc) != 0)) {
        KBIStuffBufNoFlip(iVar1,0x13);
      }
      if (*(int *)(param_1 + 0x2d0) != 0) {
        return;
      }
      uVar3 = 4;
      goto LAB_080aa514;
    }
  }
  if (iVar2 != 0) {
    if (*(int *)(param_1 + 0x2da8) != 0) {
      return;
    }
    if (*(int *)(param_1 + 0x2d0) == 0) {
      return;
    }
    uVar3 = 0x14;
    goto LAB_080aa514;
  }
  if (*(int *)(param_1 + 0x2cdc) != 0) {
    iVar2 = (int)GHIDRA_FIST32(*(float *)(param_1 + 0x19c) - *(float *)(param_2 + 0x19c));
    if (iVar2 < 0) {
      iVar2 = -iVar2;
    }
    if (*(int *)(param_1 + 0x2cdc) < iVar2) {
      if (*(int *)(param_1 + 0x2cd4) == 1) {
        if (((*(int *)(param_1 + 0x2c4) != 0) || (*(int *)(param_1 + 0x2cc) != 0)) ||
           (iVar2 = 0, *(int *)(param_1 + 0x2d0) != 0)) {
          *(undefined4 *)(param_1 + 0x2ce8) = 5;
          goto LAB_080aa01b;
        }
      }
      else {
LAB_080aa01b:
        iVar2 = *(int *)(param_1 + 0x2c4);
      }
      if (iVar2 != 0) {
        KBIStuffBufNoFlip(iVar1,0x11);
      }
      if (*(int *)(param_1 + 0x2cc) != 0) {
        KBIStuffBufNoFlip(iVar1,0x13);
      }
      if (*(int *)(param_1 + 0x2d0) != 0) {
        KBIStuffBufNoFlip(iVar1,0x14);
      }
      if (*(int *)(param_1 + 0x2ce8) != 0) {
        return;
      }
      if (*(int *)(param_1 + 0x2c8) != 0) {
        return;
      }
      uVar3 = 2;
      goto LAB_080aa514;
    }
    iVar2 = (int)GHIDRA_FIST32(*(float *)(param_1 + 0x19c) - *(float *)(param_2 + 0x19c));
    if (iVar2 < 0) {
      iVar2 = -iVar2;
    }
    if (((float)(*(int *)(param_1 + 0x2cdc) - iVar2) <
         (float)(*(int *)(param_2 + 400) * -0x14) * *(float *)(param_2 + 0x1b4)) &&
       ((*(float *)(param_1 + 0x19c) - *(float *)(param_2 + 0x19c)) * *(float *)(param_1 + 0x1b4) <=
        0.0)) {
      return;
    }
    if (*(int *)(param_1 + 0x2c8) != 0) {
      uVar3 = 0x12;
      goto LAB_080aa514;
    }
  }
  if ((*(int *)(param_1 + 0x2ce0) != 0) && (iVar2 = PlayerInCorner(param_1), iVar2 == 0)) {
    iVar2 = (int)GHIDRA_FIST32(*(float *)(param_1 + 0x19c) - *(float *)(param_2 + 0x19c));
    if (iVar2 < 0) {
      iVar2 = -iVar2;
    }
    if (iVar2 < *(int *)(param_1 + 0x2ce0)) {
      if (*(int *)(param_1 + 0x2cd4) == 1) {
        if (((*(int *)(param_1 + 0x2c4) != 0) || (*(int *)(param_1 + 0x2cc) != 0)) ||
           (iVar2 = 0, *(int *)(param_1 + 0x2c8) != 0)) {
          *(undefined4 *)(param_1 + 0x2ce8) = 5;
          goto LAB_080aa1af;
        }
      }
      else {
LAB_080aa1af:
        iVar2 = *(int *)(param_1 + 0x2c4);
      }
      if (iVar2 != 0) {
        KBIStuffBufNoFlip(iVar1,0x11);
      }
      if (*(int *)(param_1 + 0x2cc) != 0) {
        KBIStuffBufNoFlip(iVar1,0x13);
      }
      if (*(int *)(param_1 + 0x2c8) != 0) {
        KBIStuffBufNoFlip(iVar1,0x12);
      }
      if (*(int *)(param_1 + 0x2ce8) != 0) {
        return;
      }
      if (*(int *)(param_1 + 0x2d0) != 0) {
        return;
      }
      uVar3 = 4;
      goto LAB_080aa514;
    }
    iVar2 = (int)GHIDRA_FIST32(*(float *)(param_1 + 0x19c) - *(float *)(param_2 + 0x19c));
    if (iVar2 < 0) {
      iVar2 = -iVar2;
    }
    if (((float)(iVar2 - *(int *)(param_1 + 0x2ce0)) <
         (float)(*(int *)(param_2 + 400) * 0x14) * *(float *)(param_2 + 0x1b4)) &&
       (0.0 <= (*(float *)(param_1 + 0x19c) - *(float *)(param_2 + 0x19c)) *
               *(float *)(param_1 + 0x1b4))) {
      return;
    }
    if (*(int *)(param_1 + 0x2d0) != 0) {
      uVar3 = 0x14;
      goto LAB_080aa514;
    }
  }
  iVar2 = *(int *)(param_1 + 0x2cd4);
  if (iVar2 == 1) {
    if (*(int *)(param_1 + 0x2c4) != 0) {
      KBIStuffBufNoFlip(iVar1,0x11);
    }
    if (*(int *)(param_1 + 0x2cc) == 0) {
      KBIStuffBufNoFlip(iVar1,3);
    }
    if (*(int *)(param_1 + 0x2d0) != 0) {
      KBIStuffBufNoFlip(iVar1,0x14);
    }
    if (*(int *)(param_1 + 0x2c8) != 0) {
      uVar3 = 0x12;
LAB_080aa497:
      KBIStuffBufNoFlip(iVar1,uVar3);
    }
  }
  else if (iVar2 < 2) {
    if (iVar2 == 0) {
      if (*(int *)(param_1 + 0x2c4) != 0) {
        KBIStuffBufNoFlip(iVar1,0x11);
      }
      if (*(int *)(param_1 + 0x2cc) != 0) {
        KBIStuffBufNoFlip(iVar1,0x13);
      }
      if (*(int *)(param_1 + 0x2d0) != 0) {
        KBIStuffBufNoFlip(iVar1,0x14);
      }
      if (*(int *)(param_1 + 0x2c8) != 0) {
        uVar3 = 0x12;
        goto LAB_080aa497;
      }
    }
  }
  else if (iVar2 == 2) {
    if (*(int *)(param_1 + 0x2cc) != 0) {
      KBIStuffBufNoFlip(iVar1,0x13);
    }
    if (*(int *)(param_1 + 0x2d0) != 0) {
      KBIStuffBufNoFlip(iVar1,0x14);
    }
    if (*(int *)(param_1 + 0x2c8) != 0) {
      KBIStuffBufNoFlip(iVar1,0x12);
    }
    if (*(float *)(param_1 + 0x1a0) == 0.0) {
LAB_080aa46a:
      if (*(int *)(param_1 + 0x2c4) == 0) {
        uVar3 = 1;
        goto LAB_080aa497;
      }
    }
    else if (*(int *)(param_1 + 0x2c4) != 0) {
LAB_080aa495:
      uVar3 = 0x11;
      goto LAB_080aa497;
    }
  }
  else if (iVar2 == 3) {
    if (*(int *)(param_1 + 0x2cc) != 0) {
      KBIStuffBufNoFlip(iVar1,0x13);
    }
    if (*(int *)(param_1 + 0x2d0) != 0) {
      KBIStuffBufNoFlip(iVar1,0x14);
    }
    if (*(int *)(param_1 + 0x2c8) != 0) {
      KBIStuffBufNoFlip(iVar1,0x12);
    }
    if (*(float *)(param_1 + 0x1a0) == 0.0) goto LAB_080aa46a;
    if (*(float *)(param_1 + 0x1b8) <= 0.0) goto LAB_080aa495;
    if (*(int *)(param_1 + 0x2c4) == 0) {
      uVar3 = 1;
      goto LAB_080aa497;
    }
  }
  uVar3 = *(uint *)(param_1 + 0x2ce4);
  if (uVar3 == 0) {
    return;
  }
  switch(uVar3) {
  case 1:
    uVar3 = 5;
    break;
  case 2:
    uVar3 = 6;
    break;
  case 3:
    uVar3 = 7;
    break;
  case 4:
    uVar3 = 8;
    break;
  case 5:
    uVar3 = 9;
    break;
  case 6:
    uVar3 = 10;
    break;
  case 7:
    uVar3 = 0xb;
  }
  if (*(int *)(param_1 + 0x2c0 + uVar3 * 4) == 0) {
    iVar2 = *(int *)(param_1 + 0x2ce8);
    if (iVar2 == 0) {
      *(undefined4 *)(param_1 + 0x2ce8) = 5;
LAB_080aa514:
      KBIStuffBufNoFlip(iVar1,uVar3);
      return;
    }
  }
  else {
    iVar2 = *(int *)(param_1 + 0x2ce8);
    if (iVar2 == 0) {
      KBIStuffBufNoFlip(iVar1,uVar3 | 0x10);
      *(undefined4 *)(param_1 + 0x2ce8) = 5;
      return;
    }
  }
LAB_080aa545:
  *(int *)(param_1 + 0x2ce8) = iVar2 + -1;
  return;
}

/* AICheckForAttacks @ 0x080aa560, 158 bytes */
undefined4 AICheckForAttacks(int param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = g[0x7459];
  if (iVar5 <= g[0x745a]) {
    iVar6 = iVar5 * 4 + 0x1cf60;
    piVar4 = g;
    do {
      iVar3 = *(int *)(iVar6 + 4 + (int)piVar4);
      if ((iVar3 == 0) || (bVar1 = true, *(int *)(iVar3 + 0x158) == 0)) {
        bVar1 = false;
      }
      if ((bVar1) &&
         (((*(int *)(iVar3 + 0xe04) == 1 ||
           (iVar2 = ProjArrayCountActive(*(int **)(iVar3 + 0x21c)), piVar4 = g, 0 < iVar2)) &&
          (iVar3 = PlayerInGuardDist(param_1,iVar3), piVar4 = g, iVar3 != 0)))) {
        return 1;
      }
      iVar5 = iVar5 + 1;
      iVar6 = iVar6 + 4;
    } while (iVar5 <= piVar4[0x745a]);
  }
  return 0;
}

/* AIValMake @ 0x080aa600, 67 bytes
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
void AIValMake(float *param_1,float param_2)

{
  *param_1 = (float10)GHIDRA_F2I(int, param_2);
  param_1[1] = param_2;
  param_1[2] = param_2;
  param_1[3] = 0.0;
  return;
}

/* AIValMerge @ 0x080aa650, 200 bytes
 * FIXUP: 4 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
float * AIValMerge(float *param_1,float param_2,float param_3,float param_4,float param_5,
                  float param_6,float param_7,float param_8)

{
  int iVar1;
  
  if (GHIDRA_F2I(int, param_7) < GHIDRA_F2I(int, param_3)) {
    param_3 = param_7;
  }
  if (GHIDRA_F2I(int, param_4) < GHIDRA_F2I(int, param_8)) {
    param_4 = param_8;
  }
  iVar1 = (int)GHIDRA_FIST32(param_6 - param_2);
  if (iVar1 < 0) {
    iVar1 = -iVar1;
  }
  *param_1 = param_6 * ((double)0.05) + param_2 * ((double)0.95);
  param_1[1] = param_3;
  param_1[2] = param_4;
  param_1[3] = param_5 * ((double)0.95) + (float10)iVar1 * ((double)0.05);
  return param_1;
}

/* AIValMergeR @ 0x080aa720, 86 bytes
 * FIXUP: frame emulation: 4 stack locals placed at their original offsets in a 0x20-byte frame (a local's address escapes, see apply_frame_emulation) */
void AIValMergeR(float *param_1,float param_2,float param_3,float param_4,int param_5)

{

  unsigned char ghidra_frame[0x20] __attribute__((aligned(16)));
#define local_1c (*(float *)(ghidra_frame + 0x4))
#define local_18 (*(float *)(ghidra_frame + 0x8))
#define local_14 (*(float *)(ghidra_frame + 0xc))
#define fStack_10 (*(float *)(ghidra_frame + 0x10))
  
  AIValMerge(&local_1c,*param_1,param_1[1],param_1[2],param_1[3],param_2,param_3,param_4);
  *param_1 = local_1c;
  param_1[1] = local_18;
  param_1[2] = local_14;
  param_1[3] = fStack_10;
  return;
}
#undef local_1c
#undef local_18
#undef local_14
#undef fStack_10

/* AILearnStopRecord @ 0x080aa780, 33 bytes */
undefined4 AILearnStopRecord(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(param_1 + 0x10c);
  for (iVar1 = 0x136; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined4 *)(param_1 + 0x10c) = 0;
  return 0;
}

/* AIMergeLearnData @ 0x080aa7b0, 2255 bytes */
void AIMergeLearnData(int *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  int *piVar4;
  float *pfVar5;
  int *piVar6;
  int local_68;
  float *local_64;
  float *local_60;
  float *local_5c;
  int local_58;
  int local_54;
  float *local_50;
  float *local_4c;
  float *local_48;
  int *local_44;
  int *local_40;
  float *local_3c;
  float *local_38;
  float *local_34;
  int local_30;
  int *local_2c;
  int *local_28;
  int local_24;
  int local_20;
  int local_1c;
  
  local_20 = 0;
  local_24 = *(int *)(param_2 + 0x200);
  if (0 < local_24) {
    iVar2 = 0;
    do {
      local_1c = 0;
      iVar1 = param_1[0x80];
      if ((0 < iVar1) && (*param_1 != *(int *)(param_2 + iVar2))) {
        do {
          local_1c = local_1c + 1;
          if (iVar1 <= local_1c) break;
        } while (param_1[local_1c * 4] != *(int *)(iVar2 + param_2));
      }
      if ((local_1c == iVar1) && (local_1c < 0x20)) {
        param_1[local_1c * 4] = *(int *)(param_2 + iVar2);
        param_1[local_1c * 4 + 1] = *(int *)(param_2 + 4 + iVar2);
        param_1[local_1c * 4 + 2] = *(int *)(param_2 + 8 + iVar2);
        param_1[local_1c * 4 + 3] = *(int *)(param_2 + 0xc + iVar2);
        param_1[0x80] = param_1[0x80] + 1;
        local_24 = *(int *)(param_2 + 0x200);
      }
      iVar2 = iVar2 + 0x10;
      local_20 = local_20 + 1;
    } while (local_20 < local_24);
  }
  param_1[0x83] = *(int *)(param_2 + 0x20c);
  param_1[0x84] = -1;
  AIValMergeR((float *)(param_1 + 0x8d),*(float *)(param_2 + 0x234),*(float *)(param_2 + 0x238),
              *(float *)(param_2 + 0x23c),*(int *)(param_2 + 0x240));
  AIValMergeR((float *)(param_1 + 0x91),*(float *)(param_2 + 0x244),*(float *)(param_2 + 0x248),
              *(float *)(param_2 + 0x24c),*(int *)(param_2 + 0x250));
  iVar2 = 0x280;
  AIValMergeR((float *)(param_1 + 0x95),*(float *)(param_2 + 0x254),*(float *)(param_2 + 600),
              *(float *)(param_2 + 0x25c),*(int *)(param_2 + 0x260));
  local_1c = 0;
  local_64 = (float *)(param_1 + 0xa1);
  pfVar3 = (float *)(param_1 + 0x9d);
  pfVar5 = (float *)(param_1 + 0x99);
  local_68 = 0x260;
  do {
    if (((int)GHIDRA_FIST32(*(float *)(local_68 + 4 + param_2)) != 0) &&
       ((param_3 == -1 || (param_3 == local_1c)))) {
      if ((int)GHIDRA_FIST32(*(float *)(local_68 + 4 + (int)param_1)) == 0) {
        *(undefined4 *)((int)param_1 + iVar2 + -0x1c) = *(undefined4 *)(param_2 + -0x1c + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + -0x18) = *(undefined4 *)(param_2 + -0x18 + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + -0x14) = *(undefined4 *)(param_2 + -0x14 + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + -0x10) = *(undefined4 *)(param_2 + -0x10 + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + -0xc) = *(undefined4 *)(param_2 + -0xc + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + -8) = *(undefined4 *)(param_2 + -8 + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + -4) = *(undefined4 *)(param_2 + -4 + iVar2);
        *(undefined4 *)((int)param_1 + iVar2) = *(undefined4 *)(param_2 + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + 4) = *(undefined4 *)(param_2 + 4 + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + 8) = *(undefined4 *)(param_2 + 8 + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + 0xc) = *(undefined4 *)(param_2 + 0xc + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + 0x10) = *(undefined4 *)(param_2 + 0x10 + iVar2);
      }
      else {
        AIValMergeR(pfVar5,*(float *)(param_2 + -0x1c + iVar2),*(float *)(param_2 + -0x18 + iVar2),
                    *(float *)(param_2 + -0x14 + iVar2),*(int *)(param_2 + -0x10 + iVar2));
        AIValMergeR(pfVar3,*(float *)(param_2 + -0xc + iVar2),*(float *)(param_2 + -8 + iVar2),
                    *(float *)(param_2 + -4 + iVar2),*(int *)(param_2 + iVar2));
        AIValMergeR(local_64,*(float *)(param_2 + 4 + iVar2),*(float *)(param_2 + 8 + iVar2),
                    *(float *)(param_2 + 0xc + iVar2),*(int *)(param_2 + 0x10 + iVar2));
      }
    }
    local_1c = local_1c + 1;
    local_64 = local_64 + 0xc;
    local_68 = local_68 + 0x30;
    iVar2 = iVar2 + 0x30;
    pfVar3 = pfVar3 + 0xc;
    pfVar5 = pfVar5 + 0xc;
  } while (local_1c < 3);
  local_5c = (float *)(param_1 + 0xc9);
  local_60 = (float *)(param_1 + 0xc1);
  iVar2 = 800;
  local_58 = 0x2f0;
  pfVar3 = (float *)(param_1 + 0xc5);
  pfVar5 = (float *)(param_1 + 0xbd);
  local_1c = 1;
  do {
    if (*(float *)(local_58 + 4 + param_2) != -32760.0) {
      if (*(float *)(local_58 + 4 + (int)param_1) == -32760.0) {
        *(undefined4 *)((int)param_1 + iVar2 + -0x2c) = *(undefined4 *)(param_2 + -0x2c + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + -0x28) = *(undefined4 *)(param_2 + -0x28 + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + -0x24) = *(undefined4 *)(param_2 + -0x24 + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + -0x20) = *(undefined4 *)(param_2 + -0x20 + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + -0xc) = *(undefined4 *)(param_2 + -0xc + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + -8) = *(undefined4 *)(param_2 + -8 + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + -4) = *(undefined4 *)(param_2 + -4 + iVar2);
        *(undefined4 *)((int)param_1 + iVar2) = *(undefined4 *)(param_2 + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + -0x1c) = *(undefined4 *)(param_2 + -0x1c + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + -0x18) = *(undefined4 *)(param_2 + -0x18 + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + -0x14) = *(undefined4 *)(param_2 + -0x14 + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + -0x10) = *(undefined4 *)(param_2 + -0x10 + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + 4) = *(undefined4 *)(param_2 + 4 + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + 8) = *(undefined4 *)(param_2 + 8 + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + 0xc) = *(undefined4 *)(param_2 + 0xc + iVar2);
        *(undefined4 *)((int)param_1 + iVar2 + 0x10) = *(undefined4 *)(param_2 + 0x10 + iVar2);
      }
      else {
        AIValMergeR(pfVar5,*(float *)(param_2 + -0x2c + iVar2),*(float *)(param_2 + -0x28 + iVar2),
                    *(float *)(param_2 + -0x24 + iVar2),*(int *)(param_2 + -0x20 + iVar2));
        AIValMergeR(pfVar3,*(float *)(param_2 + -0xc + iVar2),*(float *)(param_2 + -8 + iVar2),
                    *(float *)(param_2 + -4 + iVar2),*(int *)(param_2 + iVar2));
        AIValMergeR(local_60,*(float *)(param_2 + -0x1c + iVar2),*(float *)(param_2 + -0x18 + iVar2)
                    ,*(float *)(param_2 + -0x14 + iVar2),*(int *)(param_2 + -0x10 + iVar2));
        AIValMergeR(local_5c,*(float *)(param_2 + 4 + iVar2),*(float *)(param_2 + 8 + iVar2),
                    *(float *)(param_2 + 0xc + iVar2),*(int *)(param_2 + 0x10 + iVar2));
      }
    }
    local_58 = local_58 + 0x40;
    local_5c = local_5c + 0x10;
    local_60 = local_60 + 0x10;
    iVar2 = iVar2 + 0x40;
    pfVar3 = pfVar3 + 0x10;
    pfVar5 = pfVar5 + 0x10;
    local_1c = local_1c + -1;
  } while (-1 < local_1c);
  if (param_1[0xdd] != *(int *)(param_2 + 0x374)) {
    param_1[0xdd] = -1;
  }
  if (param_1[0xde] != *(int *)(param_2 + 0x378)) {
    param_1[0xde] = -1;
  }
  if (((param_1[0xdf] != *(int *)(param_2 + 0x37c)) && (param_1[0xdf] != 0)) &&
     (*(int *)(param_2 + 0x37c) != 0)) {
    param_1[0xdf] = -1;
  }
  if (((param_1[0xe0] != *(int *)(param_2 + 0x380)) && (param_1[0xe0] != 0)) &&
     (*(int *)(param_2 + 0x380) != 0)) {
    param_1[0xe0] = -1;
  }
  iVar2 = 0;
  AIValMergeR((float *)(param_1 + 0xe1),*(float *)(param_2 + 900),*(float *)(param_2 + 0x388),
              *(float *)(param_2 + 0x38c),*(int *)(param_2 + 0x390));
  local_28 = (int *)(param_2 + 0x420);
  local_1c = 0;
  local_2c = param_1 + 0x108;
  local_34 = (float *)(param_1 + 0x111);
  local_38 = (float *)(param_1 + 0x10d);
  local_3c = (float *)(param_1 + 0x109);
  local_40 = (int *)(param_2 + 0x390);
  local_48 = (float *)(param_1 + 0xed);
  local_44 = param_1 + 0xe4;
  local_4c = (float *)(param_1 + 0xe9);
  local_50 = (float *)(param_1 + 0xe5);
  local_30 = 0x420;
  local_54 = 0x390;
  do {
    if (((int)GHIDRA_FIST32(*(float *)(local_54 + 4 + param_2)) != 0) &&
       ((param_3 == -1 || (param_3 == local_1c)))) {
      if ((int)GHIDRA_FIST32(*(float *)(local_54 + 4 + (int)param_1)) == 0) {
        iVar1 = 0xc;
        piVar4 = local_40;
        piVar6 = local_44;
        while( true ) {
          piVar6 = piVar6 + 1;
          piVar4 = piVar4 + 1;
          if (iVar1 == 0) break;
          iVar1 = iVar1 + -1;
          *piVar6 = *piVar4;
        }
      }
      else {
        AIValMergeR(local_50,*(float *)(param_2 + 0x394 + iVar2),*(float *)(param_2 + 0x398 + iVar2)
                    ,*(float *)(param_2 + 0x39c + iVar2),*(int *)(param_2 + 0x3a0 + iVar2));
        AIValMergeR(local_4c,*(float *)(param_2 + 0x3a4 + iVar2),*(float *)(param_2 + 0x3a8 + iVar2)
                    ,*(float *)(param_2 + 0x3ac + iVar2),*(int *)(param_2 + 0x3b0 + iVar2));
        AIValMergeR(local_48,*(float *)(param_2 + 0x3b4 + iVar2),*(float *)(param_2 + 0x3b8 + iVar2)
                    ,*(float *)(param_2 + 0x3bc + iVar2),*(int *)(param_2 + 0x3c0 + iVar2));
      }
    }
    if (*(float *)(local_30 + 4 + param_2) != 0.0) {
      if (*(float *)(local_30 + 4 + (int)param_1) == 0.0) {
        iVar1 = 0xc;
        piVar4 = local_28;
        piVar6 = local_2c;
        while( true ) {
          piVar6 = piVar6 + 1;
          piVar4 = piVar4 + 1;
          if (iVar1 == 0) break;
          iVar1 = iVar1 + -1;
          *piVar6 = *piVar4;
        }
      }
      else {
        AIValMergeR(local_3c,*(float *)(param_2 + 0x424 + iVar2),*(float *)(param_2 + 0x428 + iVar2)
                    ,*(float *)(param_2 + 0x42c + iVar2),*(int *)(param_2 + 0x430 + iVar2));
        AIValMergeR(local_38,*(float *)(param_2 + 0x434 + iVar2),*(float *)(param_2 + 0x438 + iVar2)
                    ,*(float *)(param_2 + 0x43c + iVar2),*(int *)(param_2 + 0x440 + iVar2));
        AIValMergeR(local_34,*(float *)(param_2 + 0x444 + iVar2),*(float *)(param_2 + 0x448 + iVar2)
                    ,*(float *)(param_2 + 0x44c + iVar2),*(int *)(param_2 + 0x450 + iVar2));
      }
    }
    local_30 = local_30 + 0x30;
    local_28 = local_28 + 0xc;
    local_2c = local_2c + 0xc;
    local_44 = local_44 + 0xc;
    local_34 = local_34 + 0xc;
    local_38 = local_38 + 0xc;
    local_3c = local_3c + 0xc;
    local_40 = local_40 + 0xc;
    local_1c = local_1c + 1;
    local_48 = local_48 + 0xc;
    local_4c = local_4c + 0xc;
    local_50 = local_50 + 0xc;
    local_54 = local_54 + 0x30;
    iVar2 = iVar2 + 0x30;
  } while (local_1c < 3);
  return;
}

/* AIChangeState @ 0x080ab080, 30 bytes */
undefined4 AIChangeState(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(param_1 + 4);
  *(undefined4 *)(param_1 + 4) = param_2;
  *(undefined4 *)(param_1 + 8) = uVar1;
  *(undefined4 *)(param_1 + 0xc) = 0;
  return 1;
}

/* AIKBReleaseDir @ 0x080ab0a0, 57 bytes */
void AIKBReleaseDir(int param_1)

{
  int *piVar1;
  uint uVar2;
  
  uVar2 = 1;
  piVar1 = (int *)(param_1 + 0x2c4);
  do {
    if (*piVar1 != 0) {
      KBIStuffBufNoFlip(param_1 + 0x248,uVar2 | 0x10);
    }
    uVar2 = uVar2 + 1;
    piVar1 = piVar1 + 1;
  } while ((int)uVar2 < 5);
  return;
}

/* AIKBReleaseDirExcept @ 0x080ab0e0, 79 bytes */
void AIKBReleaseDirExcept(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 0x74;
  uVar1 = 1;
  do {
    if ((uVar1 != param_2) && (*(int *)(iVar2 + param_1 + 0x250) != 0)) {
      KBIStuffBufNoFlip(param_1 + 0x248,uVar1 | 0x10);
    }
    uVar1 = uVar1 + 1;
    iVar2 = iVar2 + 4;
  } while ((int)uVar1 < 5);
  return;
}

/* AIKBReleaseAll @ 0x080ab130, 57 bytes */
void AIKBReleaseAll(int param_1)

{
  int *piVar1;
  uint uVar2;
  
  uVar2 = 1;
  piVar1 = (int *)(param_1 + 0x2c4);
  do {
    if (*piVar1 != 0) {
      KBIStuffBufNoFlip(param_1 + 0x248,uVar2 | 0x10);
    }
    uVar2 = uVar2 + 1;
    piVar1 = piVar1 + 1;
  } while ((int)uVar2 < 0xe);
  return;
}

/* AIKBReleaseAllExcept @ 0x080ab170, 79 bytes */
void AIKBReleaseAllExcept(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 0x74;
  uVar1 = 1;
  do {
    if ((uVar1 != param_2) && (*(int *)(iVar2 + param_1 + 0x250) != 0)) {
      KBIStuffBufNoFlip(param_1 + 0x248,uVar1 | 0x10);
    }
    uVar1 = uVar1 + 1;
    iVar2 = iVar2 + 4;
  } while ((int)uVar1 < 0xe);
  return;
}

