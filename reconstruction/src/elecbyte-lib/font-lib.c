/*
 * font-lib.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08051990-0x08052a4c, 20 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* V_FontDrawLine @ 0x08051990, 618 bytes */
void V_FontDrawLine(char *param_1,int *param_2,int param_3,int param_4,uint param_5)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char cVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint local_48;
  uint local_38;
  int local_20;
  
  iVar5 = W_y1;
  iVar4 = W_x2;
  iVar3 = W_x1;
  iVar2 = W_y2;
  local_20 = 0;
  if (param_2 != (int *)0x0) {
    uVar10 = param_3 + *param_2;
    uVar1 = ((param_4 - param_2[1]) - param_2[3]) + 1;
    if (((int)uVar10 <= W_x2) && ((int)uVar1 <= W_y2)) {
      iVar7 = MasterPalConvertCol16(param_5);
      cVar6 = *param_1;
      uVar12 = uVar10;
      do {
        if ((cVar6 == '\0') || (cVar6 == '\n')) {
          W_Define(iVar3,iVar5,iVar4,iVar2);
          return;
        }
        if (cVar6 != '\r') {
          if (cVar6 < '\x0e') {
            if (cVar6 == '\t') {
              uVar12 = (int)(uVar12 - uVar10) / (param_2[5] + param_2[2]);
              if ((int)uVar12 < 0) {
                uVar12 = uVar12 + 3;
              }
              uVar12 = uVar10 + ((uVar12 & 0xfffffffc) + 4) * (param_2[5] + param_2[2]);
              goto LAB_08051ba6;
            }
LAB_08051a97:
            uVar11 = (uVar12 + param_2[cVar6 + 0x107]) - 1;
            uVar8 = (uVar1 + param_2[3]) - 1;
            if ((((iVar3 <= (int)uVar11) && (iVar5 <= (int)uVar8)) && ((int)uVar12 <= iVar4)) &&
               ((int)uVar1 <= iVar2)) {
              local_38 = uVar12;
              if ((int)uVar12 < iVar3) {
                local_38 = iVar3;
              }
              local_48 = uVar1;
              if ((int)uVar1 < iVar5) {
                local_48 = iVar5;
              }
              if (iVar4 < (int)uVar11) {
                uVar11 = iVar4;
              }
              if (iVar2 < (int)uVar8) {
                uVar8 = iVar2;
              }
              W_Define(local_38,local_48,uVar11,uVar8);
              if (param_2[cVar6 + 0x107] != 0) {
                if (iVar7 == -1) {
                  W_PutSprite((int *)param_2[0x206],0,uVar12 - param_2[cVar6 + 8],uVar1);
                }
                else {
                  W_PutSpriteShadow((int *)param_2[0x206],0,uVar12 - param_2[cVar6 + 8],uVar1,
                                    (short)iVar7);
                }
              }
            }
            iVar9 = param_2[5] + param_2[cVar6 + 0x107];
          }
          else {
            if (cVar6 != ' ') goto LAB_08051a97;
            iVar9 = param_2[5] + param_2[2];
          }
          uVar12 = uVar12 + iVar9;
        }
LAB_08051ba6:
        local_20 = local_20 + 1;
        cVar6 = param_1[local_20];
      } while( true );
    }
  }
  return;
}

/* V_FontDrawLineBank @ 0x08051c00, 968 bytes */
void V_FontDrawLineBank(char *param_1,int *param_2,int param_3,int param_4,int param_5)

{
  char cVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  byte *pbVar17;
  int iVar18;
  undefined2 *puVar19;
  int iVar20;
  int iVar21;
  int *piVar22;
  int *piVar23;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  int local_38;
  int local_34;
  
  iVar8 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_38 = 0;
  bVar3 = false;
  if (param_2 != (int *)0x0) {
    piVar22 = (int *)param_2[0x206];
    iVar9 = SpriteArrayAccess(piVar22,0);
    iVar20 = param_3 + *param_2;
    iVar10 = ((param_4 - param_2[1]) - param_2[3]) + 1;
    if ((((iVar20 <= W_x2) && (iVar10 <= W_y2)) && (-1 < param_5)) &&
       (iVar11 = SpriteArrayNumPals((int)piVar22), param_5 < iVar11)) {
      piVar12 = SpriteArrayPalUpdateAndAccess((int)piVar22,param_5);
      iVar11 = SpriteDecompGetAndLockData(piVar22,0);
      if (iVar11 != 0) {
        iVar13 = SpriteDecompGetData(V_Current,V_CurrentIdx);
        iVar7 = W_y1;
        iVar6 = W_x2;
        iVar5 = W_x1;
        iVar4 = W_y2;
        cVar1 = *param_1;
        iVar21 = iVar20;
        do {
          if ((cVar1 == '\0') || (cVar1 == '\n')) {
            SpriteDecompUnlockData();
            return;
          }
          if (!bVar3) {
            local_4c = 0;
            local_48 = iVar10;
            if (iVar10 < iVar7) {
              local_48 = iVar7;
              local_4c = iVar7 - iVar10;
            }
            local_50 = iVar10 + param_2[3] + -1;
            if (iVar4 < local_50) {
              local_50 = iVar4;
            }
            bVar3 = true;
          }
          if (cVar1 != '\r') {
            if (cVar1 < '\x0e') {
              if (cVar1 == '\t') {
                uVar14 = (iVar21 - iVar20) / (param_2[5] + param_2[2]);
                if ((int)uVar14 < 0) {
                  uVar14 = uVar14 + 3;
                }
                iVar21 = iVar20 + ((uVar14 & 0xfffffffc) + 4) * (param_2[5] + param_2[2]);
                goto LAB_08051f80;
              }
LAB_08051e50:
              local_58 = 0;
              local_54 = iVar21;
              if (iVar21 < iVar5) {
                local_54 = iVar5;
                local_58 = iVar5 - iVar21;
              }
              iVar15 = iVar21 + param_2[cVar1 + 0x107] + -1;
              if (iVar6 < iVar15) {
                iVar15 = iVar6;
              }
              iVar16 = (local_50 - local_48) + 1;
              local_34 = 0;
              if (0 < iVar16) {
                iVar2 = param_2[cVar1 + 8];
                piVar23 = (int *)(local_48 * 4 + *(int *)(iVar8 + 0x2c));
                piVar22 = (int *)(local_4c * 4 + *(int *)(iVar9 + 0x2c));
                do {
                  pbVar17 = (byte *)(iVar2 + iVar11 + *piVar22 + local_58);
                  puVar19 = (undefined2 *)(iVar13 + *piVar23 + local_54 * 2);
                  for (iVar18 = (iVar15 - local_54) + 1; 0 < iVar18; iVar18 = iVar18 + -1) {
                    if (*pbVar17 != 0) {
                      *puVar19 = *(undefined2 *)((int)piVar12 + (uint)*pbVar17 * 2 + 0x5c);
                    }
                    puVar19 = puVar19 + 1;
                    pbVar17 = pbVar17 + 1;
                  }
                  piVar23 = piVar23 + 1;
                  local_34 = local_34 + 1;
                  piVar22 = piVar22 + 1;
                } while (local_34 < iVar16);
              }
              iVar15 = param_2[5] + param_2[cVar1 + 0x107];
            }
            else {
              if (cVar1 != ' ') goto LAB_08051e50;
              iVar15 = param_2[5] + param_2[2];
            }
            iVar21 = iVar21 + iVar15;
          }
LAB_08051f80:
          local_38 = local_38 + 1;
          cVar1 = param_1[local_38];
        } while( true );
      }
    }
  }
  return;
}

/* V_FontDraw @ 0x08051fd0, 39 bytes */
void V_FontDraw(char *param_1,int *param_2,int param_3,int param_4,uint param_5)

{
  V_FontDrawAlign(param_1,param_2,param_3,param_4,1,param_5);
  return;
}

/* V_FontDrawRight @ 0x08052000, 39 bytes
 * FIXUP: return type set to void: only unaffected-register values were returned */
void V_FontDrawRight(char *param_1,int *param_2,int param_3,int param_4,uint param_5)

{
  undefined4 extraout_EAX;
  
  V_FontDrawAlign(param_1,param_2,param_3,param_4,-1,param_5);
  return;
}

/* V_FontDrawCenter @ 0x08052030, 39 bytes
 * FIXUP: return type set to void: only unaffected-register values were returned */
void V_FontDrawCenter(char *param_1,int *param_2,int param_3,int param_4,uint param_5)

{
  undefined4 extraout_EAX;
  
  V_FontDrawAlign(param_1,param_2,param_3,param_4,0,param_5);
  return;
}

/* V_FontDrawBank @ 0x08052060, 39 bytes */
void V_FontDrawBank(char *param_1,int *param_2,int param_3,int param_4,int param_5)

{
  V_FontDrawAlignBank(param_1,param_2,param_3,param_4,1,param_5);
  return;
}

/* V_FontDrawRightBank @ 0x08052090, 39 bytes */
undefined4 V_FontDrawRightBank(char *param_1,int *param_2,int param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  
  uVar1 = V_FontDrawAlignBank(param_1,param_2,param_3,param_4,-1,param_5);
  return uVar1;
}

/* V_FontDrawCenterBank @ 0x080520c0, 39 bytes */
void V_FontDrawCenterBank(char *param_1,int *param_2,int param_3,int param_4,int param_5)

{
  V_FontDrawAlignBank(param_1,param_2,param_3,param_4,0,param_5);
  return;
}

/* V_FontWrite @ 0x080520f0, 88 bytes
 * FIXUP: varargs: replaced 1 &stack0x.. with a va_list started after param_5
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x1020-byte frame (a local's address escapes, see apply_frame_emulation) */
void V_FontWrite(int *param_1,int param_2,int param_3,uint param_4,char *param_5,...)

{
  va_list ghidra_va;
  va_start(ghidra_va, param_5);
  unsigned char ghidra_frame[0x1020] __attribute__((aligned(16)));
#define local_101c (*(char (*)[4108])(ghidra_frame + 0x4))
  
  vsprintf(local_101c,param_5,ghidra_va);
  V_FontDraw(local_101c,param_1,param_2,param_3,param_4);
  return;
}
#undef local_101c

/* V_FontWriteRight @ 0x08052150, 88 bytes
 * FIXUP: varargs: replaced 1 &stack0x.. with a va_list started after param_5
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x1020-byte frame (a local's address escapes, see apply_frame_emulation) */
void V_FontWriteRight(int *param_1,int param_2,int param_3,uint param_4,char *param_5,...)

{
  va_list ghidra_va;
  va_start(ghidra_va, param_5);
  unsigned char ghidra_frame[0x1020] __attribute__((aligned(16)));
#define local_101c (*(char (*)[4108])(ghidra_frame + 0x4))
  
  vsprintf(local_101c,param_5,ghidra_va);
  V_FontDrawRight(local_101c,param_1,param_2,param_3,param_4);
  return;
}
#undef local_101c

/* V_FontWriteBank @ 0x080521b0, 88 bytes
 * FIXUP: varargs: replaced 1 &stack0x.. with a va_list started after param_5
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x1020-byte frame (a local's address escapes, see apply_frame_emulation) */
void V_FontWriteBank(int *param_1,int param_2,int param_3,int param_4,char *param_5,...)

{
  va_list ghidra_va;
  va_start(ghidra_va, param_5);
  unsigned char ghidra_frame[0x1020] __attribute__((aligned(16)));
#define local_101c (*(char (*)[4108])(ghidra_frame + 0x4))
  
  vsprintf(local_101c,param_5,ghidra_va);
  V_FontDrawBank(local_101c,param_1,param_2,param_3,param_4);
  return;
}
#undef local_101c

/* V_FontDrawAlign_I @ 0x08052210, 498 bytes
 * REVIEW: pid-unaff_ */
void V_FontDrawAlign_I(char *param_1,int *param_2,int param_3,int param_4,int param_5,uint param_6,
                      int param_7)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  char cVar5;
  int iVar6;
  int unaff_ESI;
  int local_20;
  int local_18;
  
  if (param_2 != (int *)0x0) {
    local_18 = param_4;
    iVar6 = 0;
    if (*param_1 != '\0') {
      local_20 = param_2[3];
      iVar2 = param_4 - local_20;
      while (iVar2 + 1 <= W_y2) {
        iVar2 = iVar6;
        if (param_5 == 1) {
          cVar5 = param_1[iVar6];
          while ((cVar5 != '\0' && (cVar5 != '\n'))) {
            iVar2 = iVar2 + 1;
            cVar5 = param_1[iVar2];
          }
        }
        else {
          iVar4 = param_2[5];
          unaff_ESI = -iVar4;
          cVar5 = param_1[iVar6];
          while ((cVar5 != '\0' && (cVar5 != '\n'))) {
            if (cVar5 != '\r') {
              if (cVar5 < '\x0e') {
                if (cVar5 == '\t') {
                  uVar3 = unaff_ESI / (iVar4 + param_2[2]);
                  if ((int)uVar3 < 0) {
                    uVar3 = uVar3 + 3;
                  }
                  unaff_ESI = ((uVar3 & 0xfffffffc) + 4) * (iVar4 + param_2[2]);
                  goto LAB_08052304;
                }
LAB_080522f0:
                iVar1 = param_2[cVar5 + 0x107];
              }
              else {
                if (cVar5 != ' ') goto LAB_080522f0;
                iVar1 = param_2[2];
              }
              unaff_ESI = unaff_ESI + iVar4 + iVar1;
            }
LAB_08052304:
            iVar2 = iVar2 + 1;
            cVar5 = param_1[iVar2];
          }
          if (unaff_ESI < 0) {
            unaff_ESI = 0;
          }
        }
        if (iVar6 < iVar2) {
          if (param_5 == 0) {
            iVar4 = param_3 - (unaff_ESI >> 1);
          }
          else {
            iVar4 = param_3;
            if (param_5 == -1) {
              iVar4 = (param_3 - unaff_ESI) + 1;
            }
          }
          if (param_7 == -1) {
            V_FontDrawLine(param_1 + iVar6,param_2,iVar4,local_18,param_6);
          }
          else {
            V_FontDrawLineBank(param_1 + iVar6,param_2,iVar4,local_18,param_7);
          }
          local_20 = param_2[3];
        }
        iVar6 = iVar2 + 1;
        local_18 = local_18 + local_20 + param_2[6];
        if (cVar5 == '\0') {
          return;
        }
        iVar2 = local_18 - local_20;
      }
    }
  }
  return;
}

/* V_FontDrawAlign @ 0x08052410, 44 bytes */
void V_FontDrawAlign(char *param_1,int *param_2,int param_3,int param_4,int param_5,uint param_6)

{
  V_FontDrawAlign_I(param_1,param_2,param_3,param_4,param_5,param_6,-1);
  return;
}

/* V_FontDrawAlignBank @ 0x08052440, 44 bytes
 * FIXUP: return type set to void: only unaffected-register values were returned */
undefined4
V_FontDrawAlignBank(char *param_1,int *param_2,int param_3,int param_4,int param_5,int param_6)

{
  undefined4 extraout_EAX;
  
  V_FontDrawAlign_I(param_1,param_2,param_3,param_4,param_5,0,param_6);
  return;
}

/* FontReadFile @ 0x08052470, 61 bytes */
undefined4 FontReadFile(char *param_1)

{
  FILE *pFVar1;
  undefined4 uVar2;
  
  pFVar1 = (FILE *)MFfopenFile(param_1,"rb");
  if (pFVar1 == (FILE *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FontReadFilePtr(pFVar1);
    MFfclose((int *)pFVar1);
  }
  return uVar2;
}

/* FontReadFilePtr @ 0x080524b0, 119 bytes
 * FIXUP: 2 dead flag initialisations of inlined repz cmpsb loops set to constants
 * FIXUP: frame emulation: 2 stack locals placed at their original offsets in a 0x60-byte frame (a local's address escapes, see apply_frame_emulation) */
void * FontReadFilePtr(FILE *param_1)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  bool bVar6;
  bool bVar7;
  unsigned char ghidra_frame[0x60] __attribute__((aligned(16)));
#define local_5c (*(byte (*)[12])(ghidra_frame + 0x4))
#define local_50 (*(int *)(ghidra_frame + 0x10))
  
  iVar1 = MFftell(&param_1->_flags);
  MFfread(local_5c,0x40,1,&param_1->_flags);
  iVar3 = 0xc;
  bVar6 = 0;  /* dead flag (repz cmpsb, count 0xc) */
  bVar7 = 0;  /* dead flag (repz cmpsb, count 0xc) */
  pbVar4 = local_5c;
  pbVar5 = (byte *)"ElecbyteFnt";
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar6 = *pbVar4 < *pbVar5;
    bVar7 = *pbVar4 == *pbVar5;
    pbVar4 = pbVar4 + 1;
    pbVar5 = pbVar5 + 1;
  } while (bVar7);
  if (((!bVar6 && !bVar7) == bVar6) && (local_50 == 0x100)) {
    pvVar2 = FontReadFilePtr_0_01(param_1,(int)local_5c);
    MFfseek(&param_1->_flags,iVar1,0);
  }
  else {
    pvVar2 = (void *)0x0;
  }
  return pvVar2;
}
#undef local_5c
#undef local_50

/* FontReadFilePtr_0_01 @ 0x08052530, 1086 bytes
 * FIXUP: frame emulation: 6 stack locals placed at their original offsets in a 0x4f0-byte frame (a local's address escapes, see apply_frame_emulation) */
void * FontReadFilePtr_0_01(FILE *param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  void *pvVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  char cVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  char *pcVar11;
  int *piVar12;
  unsigned char ghidra_frame[0x4f0] __attribute__((aligned(16)));
#define local_4f0 (*(int *)(ghidra_frame + 0x0))
#define local_4ec (*(int *)(ghidra_frame + 0x4))
#define local_4e0 (*(int *)(ghidra_frame + 0x10))
#define local_4dc (*(int (*)[152])(ghidra_frame + 0x14))
#define local_27c (*(int (*)[2])(ghidra_frame + 0x274))
#define local_274 (*(int *)(ghidra_frame + 0x27c))
  
  local_4ec = 0;
  iVar2 = MFftell(&param_1->_flags);
  pvVar3 = calloc(1,0x81c);
  if (pvVar3 == (void *)0x0) {
    return (void *)0x0;
  }
  MFfseek(&param_1->_flags,iVar2 + -0x40 + *(int *)(param_2 + 0x10),0);
  piVar4 = SpriteReadPCXPtr(&param_1->_flags,0,0);
  *(int **)((int)pvVar3 + 0x818) = piVar4;
  if (piVar4 != (int *)0x0) {
    *(undefined4 *)((int)pvVar3 + 0x10) = 1;
    MFfseek(&param_1->_flags,iVar2 + -0x40 + *(int *)(param_2 + 0x18),0);
    piVar4 = TPReadFilePtr((FILE *)param_1->_IO_read_ptr,0);
    if (piVar4 != (int *)0x0) {
      pcVar11 = "def";
      piVar10 = piVar4;
      piVar12 = piVar4;
      iVar5 = TPGroupSeek((int)piVar4,"def");
      if (iVar5 != -1) {
        TPScanf((int)piVar4,"size","%i,%i",(int)pvVar3 + 8,(int)pvVar3 + 0xc,pcVar11,piVar10,piVar12
               );
        TPScanf((int)piVar4,"spacing","%i,%i",(int)pvVar3 + 0x14,(int)pvVar3 + 0x18);
        TPGetValueInt((int)piVar4,"colors",(uint *)((int)pvVar3 + 0x1c));
        TPScanf((int)piVar4,"offset","%i,%i",pvVar3,(int)pvVar3 + 4);
        pcVar11 = TPGetValue((int)piVar4,"type");
        if ((pcVar11 != (char *)0x0) && ((*pcVar11 == 'f' || (*pcVar11 == 'F')))) {
          *(undefined4 *)((int)pvVar3 + 0x10) = 0;
        }
        iVar5 = TPGroupSeek((int)piVar4,"map");
        if (iVar5 != -1) {
          pcVar11 = (char *)TPAccessFirstLine((int)piVar4);
          uVar1 = extraout_ECX;
          while (pcVar11 != (char *)0x0) {
            local_4e0 = (int)*pcVar11;
            iVar9 = 0;
            iVar5 = 2;
            if (pcVar11[1] != '\0') {
              if ((*pcVar11 == '0') && (pcVar11[1] == 'x')) {
                sscanf(pcVar11 + 2,"%x",&local_4e0,uVar1);
                cVar7 = '\0';
                if (pcVar11[2] != '\0') {
                  if (pcVar11[2] == ' ') {
                    cVar7 = ' ';
                  }
                  else {
                    do {
                      iVar5 = iVar5 + 1;
                      cVar7 = pcVar11[iVar5];
                      if (cVar7 == '\0') break;
                    } while (cVar7 != ' ');
                  }
                }
                while (cVar7 == ' ') {
                  iVar5 = iVar5 + 1;
                  cVar7 = pcVar11[iVar5];
                }
              }
              iVar9 = sscanf(pcVar11 + iVar5,"%i %i",(int)pvVar3 + local_4e0 * 4 + 0x20,
                             (int)pvVar3 + local_4e0 * 4 + 0x41c);
            }
            if (iVar9 < 1) {
              *(int *)((int)pvVar3 + local_4e0 * 4 + 0x20) = local_4ec;
            }
            if (iVar9 < 2) {
              *(undefined4 *)((int)pvVar3 + local_4e0 * 4 + 0x41c) =
                   *(undefined4 *)((int)pvVar3 + 8);
            }
            local_4ec = local_4ec + *(int *)((int)pvVar3 + local_4e0 * 4 + 0x41c);
            pcVar11 = (char *)TPAccessNextLine((int)piVar4);
            uVar1 = extraout_ECX_00;
          }
          *(int *)((int)pvVar3 + 0x49c) = *(int *)((int)pvVar3 + 8);
          if (((*(int *)((int)pvVar3 + 8) != 0) && (*(int *)((int)pvVar3 + 0xc) != 0)) &&
             (*(int *)((int)pvVar3 + 0x1c) != 0)) {
            TPFree(piVar4);
            if (1 < *(int *)((int)pvVar3 + 0x1c)) {
              iVar5 = *(int *)((int)pvVar3 + 0x1c) * 2 + -2;
              iVar9 = 0x1f;
              if (iVar5 < 0) {
                iVar5 = -0x80000000;
              }
              else {
                do {
                  iVar9 = iVar9 + -1;
                  if (iVar9 == 0) goto LAB_08052838;
                } while (iVar5 >> ((byte)iVar9 & 0x1f) == 0);
                iVar5 = 1 << ((byte)iVar9 & 0x1f);
              }
LAB_08052838:
              piVar4 = (int *)SpriteArrayPalAccess(*(int *)((int)pvVar3 + 0x818),0);
              piVar10 = local_4dc;
              for (iVar9 = 0x97; iVar9 != 0; iVar9 = iVar9 + -1) {
                *piVar10 = *piVar4;
                piVar4 = piVar4 + 1;
                piVar10 = piVar10 + 1;
              }
              ArrayDelete(*(int *)(*(int *)((int)pvVar3 + 0x818) + 8),0);
              local_4f0 = 0;
              iVar9 = 0x100 - iVar5;
              if (-1 < iVar9) {
                do {
                  EBPalCopy(local_27c,local_4dc,0);
                  local_274 = local_274 + iVar9 * 4;
                  local_27c[0] = iVar5;
                  EBPalGenerateFPal(local_27c);
                  iVar8 = local_4f0 + 1;
                  iVar6 = SpriteArrayAddPal(*(int *)((int)pvVar3 + 0x818),local_27c,0,local_4f0);
                  if (iVar6 == 0) goto LAB_08052901;
                  iVar9 = iVar9 - iVar5;
                  local_4f0 = iVar8;
                } while (-1 < iVar9);
              }
              iVar9 = SpriteArrayAddPal(*(int *)((int)pvVar3 + 0x818),local_4dc,0,local_4f0);
              if (iVar9 == 0) goto LAB_08052901;
              iVar6 = SpriteArrayAccess(*(int **)((int)pvVar3 + 0x818),0);
              iVar8 = 0;
              iVar9 = *(int *)(iVar6 + 0x20);
              *(int *)(iVar6 + 0x14) = iVar5;
              if (0 < iVar9) {
                do {
                  cVar7 = *(char *)(iVar8 + *(int *)(iVar6 + 0x24));
                  if (cVar7 != '\0') {
                    *(char *)(iVar8 + *(int *)(iVar6 + 0x24)) = cVar7 + (char)iVar5;
                    iVar9 = *(int *)(iVar6 + 0x20);
                  }
                  iVar8 = iVar8 + 1;
                } while (iVar8 < iVar9);
              }
            }
            MFfseek(&param_1->_flags,iVar2,0);
            return pvVar3;
          }
        }
      }
    }
  }
LAB_08052901:
  FontFree(pvVar3);
  return (void *)0x0;
}
#undef local_4f0
#undef local_4ec
#undef local_4e0
#undef local_4dc
#undef local_27c
#undef local_274

/* FontFree @ 0x08052970, 54 bytes */
undefined4 FontFree(void *param_1)

{
  if (param_1 != (void *)0x0) {
    if (*(int **)((int)param_1 + 0x818) != (int *)0x0) {
      SpriteArrayFree(*(int **)((int)param_1 + 0x818));
    }
    free(param_1);
  }
  return 1;
}

/* FontGetWidth @ 0x080529b0, 85 bytes */
int FontGetWidth(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = 0;
  for (; *param_2 != '\0'; param_2 = param_2 + 1) {
    if (*param_2 == '\n') {
      if (iVar1 < iVar2) {
        iVar1 = iVar2;
      }
      iVar2 = 0;
    }
    else {
      iVar2 = iVar2 + *(int *)(param_1 + 0x14) + *(int *)(param_1 + 0x41c + *param_2 * 4);
    }
  }
  if (iVar1 < iVar2) {
    iVar1 = iVar2;
  }
  if (0 < iVar1) {
    iVar1 = iVar1 - *(int *)(param_1 + 0x14);
  }
  return iVar1;
}

/* FontGetWidthQuick @ 0x08052a10, 60 bytes */
int FontGetWidthQuick(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  
  iVar2 = 0;
  cVar1 = *param_2;
  while (cVar1 != '\0') {
    cVar1 = *param_2;
    param_2 = param_2 + 1;
    iVar2 = iVar2 + *(int *)(param_1 + 0x14) + *(int *)(param_1 + 0x41c + cVar1 * 4);
    cVar1 = *param_2;
  }
  if (0 < iVar2) {
    iVar2 = iVar2 - *(int *)(param_1 + 0x14);
  }
  return iVar2;
}

