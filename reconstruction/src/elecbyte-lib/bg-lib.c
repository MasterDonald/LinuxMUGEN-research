/*
 * bg-lib.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0804b0f0-0x0804e431, 29 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"

extern undefined1 GlobalTemp[16] __asm__("D_082a6298"); /* file-static 0x082a6298 */

/* BGArrayReadFile @ 0x0804b0f0, 26 bytes */
void BGArrayReadFile(char *param_1,char *param_2)

{
  BGArrayReadFileSA(param_1,param_2,0,0);
  return;
}

/* BGArrayReadFileSA @ 0x0804b110, 180 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x1010-byte frame (a local's address escapes, see apply_frame_emulation) */
char * BGArrayReadFileSA(char *param_1,char *param_2,int param_3,int param_4)

{
  char *pcVar1;
  char *pcVar2;
  unsigned char ghidra_frame[0x1010] __attribute__((aligned(16)));
#define local_100c (*(char (*)[4096])(ghidra_frame + 0x4))
  
  pcVar1 = TPReadFile(param_1);
  if (pcVar1 == (char *)0x0) {
    strcat((char *)ErrorMessage,"\nTXTPARSE error opening ");
    strcat((char *)ErrorMessage,param_1);
    pcVar2 = (char *)0x0;
  }
  else {
    splitdirfile(param_1,local_100c,(char *)0x0);
    pcVar2 = BGArrayReadTP(pcVar1,local_100c,param_2,param_3,param_4);
    if (pcVar2 == (char *)0x0) {
      strcat((char *)ErrorMessage,"\nBG error reading ");
      strcat((char *)ErrorMessage,param_1);
    }
    TPFree((undefined4 *)pcVar1);
  }
  return pcVar2;
}
#undef local_100c

/* BGArrayReadTP @ 0x0804b1d0, 2838 bytes
 * FIXUP: removed 2 x87 control-word save statements
 * FIXUP: 3 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: untyped (undefined4) <-> float moves kept as bit copies: 0 assignments, 3 calls, 0 returns
 * FIXUP: frame emulation: 31 stack locals placed at their original offsets in a 0x10f0-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 2 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
char * BGArrayReadTP(char *param_1,char *param_2,char *param_3,int param_4,int param_5)

{
  float10 fVar1;
  bool bVar2;
  size_t sVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  int *piVar7;
  undefined3 extraout_var;
  char *pcVar8;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  int iVar9;
  uint uVar10;
  undefined4 *puVar11;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar12;
  size_t sVar13;
  float10 fVar14;
  undefined4 uVar15;
  undefined2 in_FPUControlWord;
  int iVar16;
  char *pcVar17;
  char *pcVar18;
  char *pcVar19;
  uint *puVar20;
  undefined4 *puVar21;
  unsigned char ghidra_frame[0x10f0] __attribute__((aligned(16)));
#define local_10f0 (*(int *)(ghidra_frame + 0x0))
#define local_10ec (*(int *)(ghidra_frame + 0x4))
#define local_10e8 (*(char **)(ghidra_frame + 0x8))
#define local_10dc (*(float *)(ghidra_frame + 0x14))
#define local_10d8 (*(float *)(ghidra_frame + 0x18))
#define local_10d4 (*(float *)(ghidra_frame + 0x1c))
#define local_10d0 (*(int *)(ghidra_frame + 0x20))
#define local_10cc (*(int *)(ghidra_frame + 0x24))
#define local_10c8 (*(float *)(ghidra_frame + 0x28))
#define local_10c4 (*(uint *)(ghidra_frame + 0x2c))
#define local_10c0 (*(int *)(ghidra_frame + 0x30))
#define local_10bc (*(uint *)(ghidra_frame + 0x34))
#define local_10b8 (*(undefined4 *)(ghidra_frame + 0x38))
#define local_10b4 (*(undefined4 *)(ghidra_frame + 0x3c))
#define local_10b0 (*(uint *)(ghidra_frame + 0x40))
#define local_10ac (*(int *)(ghidra_frame + 0x44))
#define local_10a8 (*(int *)(ghidra_frame + 0x48))
#define local_10a4 (*(float *)(ghidra_frame + 0x4c))
#define local_10a0 (*(float *)(ghidra_frame + 0x50))
#define local_109c (*(undefined4 *)(ghidra_frame + 0x54))
#define local_1098 (*(float *)(ghidra_frame + 0x58))
#define local_1094 (*(uint *)(ghidra_frame + 0x5c))
#define local_1090 (*(undefined4 *)(ghidra_frame + 0x60))
#define local_108c (*(undefined4 *)(ghidra_frame + 0x64))
#define local_1088 (*(uint *)(ghidra_frame + 0x68))
#define local_1084 (*(int *)(ghidra_frame + 0x6c))
#define local_1080 (*(undefined2 *)(ghidra_frame + 0x70))
#define uStack_107e (*(undefined2 *)(ghidra_frame + 0x72))
#define local_107c (*(char (*)[48])(ghidra_frame + 0x74))
#define local_104c (*(char (*)[48])(ghidra_frame + 0xa4))
#define local_101c (*(char (*)[4108])(ghidra_frame + 0xd4))
  
  sVar3 = strlen(param_3);
  sprintf(local_104c,"%s ",param_3);
  sprintf(local_107c,"%s]",param_3);
  iVar4 = TPGroupMatchCount((int)param_1,local_104c);
  iVar5 = TPGroupMatchCount((int)param_1,local_107c);
  sVar13 = iVar4 + iVar5;
  if (sVar13 == 0) {
    sprintf((char *)ErrorMessage,"Need at least one [%s] type bg",param_3,0);
    return (char *)0x0;
  }
  pcVar6 = (char *)BGArrayNew(sVar13,0);
  if (pcVar6 == (char *)0x0) {
    return (char *)0x0;
  }
  pcVar19 = local_101c;
  strcpy(pcVar19,param_3);
  strcat(pcVar19,"def");
  iVar4 = TPGroupSeek((int)param_1,pcVar19);
  if (iVar4 == -1) {
    sprintf((char *)ErrorMessage,"Can\'t access group %s",pcVar19,param_1);
  }
  else {
    local_10e8 = TPGetValue((int)param_1,"spr");
    if (local_10e8 == (char *)0x0) {
      if (param_4 == 0) {
        memcpy(ErrorMessage,"Error: sff file must be specified",0x22);
        goto LAB_0804bccb;
      }
      *(int *)(pcVar6 + 0x28) = param_4;
      pcVar6[0x2c] = '\0';
      pcVar6[0x2d] = '\0';
      pcVar6[0x2e] = '\0';
      pcVar6[0x2f] = '\0';
    }
    else {
      joindirfile(pcVar19,param_2,local_10e8);
      piVar7 = SpriteReadFile(pcVar19);
      *(int **)(pcVar6 + 0x28) = piVar7;
      if (piVar7 == (int *)0x0) {
        pcVar17 = "Error reading sprite %s";
LAB_0804bcbb:
        sprintf((char *)ErrorMessage,pcVar17,local_10e8,pcVar19);
        goto LAB_0804bccb;
      }
      pcVar6[0x2c] = '\x01';
      pcVar6[0x2d] = '\0';
      pcVar6[0x2e] = '\0';
      pcVar6[0x2f] = '\0';
    }
    bVar2 = TPGetValueInt((int)param_1,"debugbg",&local_1088);
    if (GHIDRA_ZEXT8(bVar2) == 0) {
      TPScanf((int)param_1,"bgclearcolor","%i,%i,%i",pcVar6 + 0x3c,pcVar6 + 0x40,pcVar6 + 0x44,
              extraout_ECX,extraout_ECX);
    }
    else if (local_1088 != 0) {
      pcVar6[0x44] = -1;
      pcVar6[0x45] = '\0';
      pcVar6[0x46] = '\0';
      pcVar6[0x47] = '\0';
      pcVar6[0x3c] = -1;
      pcVar6[0x3d] = '\0';
      pcVar6[0x3e] = '\0';
      pcVar6[0x3f] = '\0';
      pcVar6[0x40] = '\0';
      pcVar6[0x41] = '\0';
      pcVar6[0x42] = '\0';
      pcVar6[0x43] = '\0';
    }
    if (param_5 == 0) {
      iVar4 = TPGroupScanFirst((int)param_1);
      do {
        iVar5 = strimatch((char *)(iVar4 + 1),"begin action ");
        if (iVar5 != 0) break;
        iVar4 = TPGroupScanNext((int)param_1);
      } while (iVar4 != 0);
      if (iVar4 != 0) {
        piVar7 = AnimRCReadFileTP((int)param_1);
        *(int **)(pcVar6 + 0x20) = piVar7;
        if (piVar7 == (int *)0x0) {
          strcat((char *)ErrorMessage,"\nError loading anim.");
          goto LAB_0804bccb;
        }
        pcVar6[0x24] = '\x01';
        pcVar6[0x25] = '\0';
        pcVar6[0x26] = '\0';
        pcVar6[0x27] = '\0';
      }
    }
    else {
      *(int *)(pcVar6 + 0x20) = param_5;
      pcVar6[0x24] = '\0';
      pcVar6[0x25] = '\0';
      pcVar6[0x26] = '\0';
      pcVar6[0x27] = '\0';
    }
    local_10e8 = (char *)TPGroupScanFirst((int)param_1);
    local_1088 = 0;
    if (0 < (int)sVar13) {
      do {
        while ((*(int *)(param_1 + 0x18) != *(int *)(param_1 + 0x2c) &&
               ((iVar4 = strimatch(local_10e8 + 1,param_3), iVar4 == 0 ||
                (((*(byte *)(__ctype_b + 1 + local_10e8[sVar3 + 1] * 2) & 0x20) == 0 &&
                 (local_10e8[sVar3 + 1] != ']'))))))) {
          local_10e8 = (char *)TPGroupScanNext((int)param_1);
        }
        local_10a8 = -1;
        local_10ac = -1;
        local_10b0 = 0xffffffff;
        local_1098 = 0.0;
        local_109c = 0;
        local_10a0 = 1.0;
        local_10a4 = 1.0;
        local_108c = 0;
        local_1090 = 0;
        local_10f0 = 0;
        local_10bc = 0;
        local_10c0 = 0;
        local_10c4 = 0;
        local_10b8 = 0x100;
        local_10b4 = 0;
        local_1094 = 0;
        puVar20 = &local_1094;
        pcVar17 = pcVar19;
        TPGetValueInt((int)param_1,"layerno",&local_1094);
        pcVar18 = "type";
        pcVar8 = TPGetValue((int)param_1,"type");
        if (pcVar8 == (char *)0x0) {
          sprintf((char *)ErrorMessage,"Missing type in %s",local_10e8,extraout_ECX_00);
          goto LAB_0804bccb;
        }
        switch(*(undefined4 *)(__ctype_tolower + *pcVar8 * 4)) {
        case 0x61:
          local_10ec = 3;
          break;
        default:
          sprintf((char *)ErrorMessage,"Invalid type: %s\n\tin %s",pcVar8,local_10e8);
          goto LAB_0804bccb;
        case 100:
          local_10ec = 10;
          break;
        case 0x68:
          local_10ec = 2;
          break;
        case 0x6e:
          local_10ec = 0;
          break;
        case 0x70:
          local_10ec = 1;
        }
        TPScanf((int)param_1,"start","%i,%i",&local_109c,&local_1098,pcVar18,puVar20,pcVar17);
        TPScanf((int)param_1,"delta","%f,%f",&local_10a4,&local_10a0);
        local_10a4 = local_10a4 * -1.0;
        local_10a0 = local_10a0 * -1.0;
        TPScanf((int)param_1,"velocity","%f,%f",&local_1090,&local_108c);
        if ((local_10ec == 3) || (local_10ec == 10)) {
          if ((local_10ec == 3) &&
             (bVar2 = TPGetValueInt((int)param_1,"actionno",&local_10b0),
             GHIDRA_ZEXT8(bVar2) == 0)) {
            pcVar17 = "Missing actionno in %s";
            goto LAB_0804bcbb;
          }
        }
        else {
          iVar4 = TPScanf((int)param_1,"spriteno","%i,%i",&local_10ac,&local_10a8);
          if (iVar4 != 2) {
            sprintf((char *)ErrorMessage,"Invalid or missing spriteno: %i,%i\n\tin %s",local_10ac,
                    local_10a8,local_10e8);
            goto LAB_0804bccb;
          }
        }
        pcVar17 = TPGetValue((int)param_1,"trans");
        if (pcVar17 != (char *)0x0) {
          puVar11 = &local_10b8;
          puVar21 = &local_10b4;
          local_10f0 = GetDrawType(pcVar17,&local_10b8,&local_10b4);
          if (local_10f0 == -2) {
            sprintf((char *)ErrorMessage,"Invalid argument: trans = %s\nin %s",pcVar17,local_10e8);
            goto LAB_0804bccb;
          }
          TPScanf((int)param_1,"alpha","%i,%i",&local_10b8,&local_10b4,puVar11,puVar21,pcVar19);
        }
        bVar2 = TPGetValueInt((int)param_1,"mask",&local_10bc);
        fVar1 = local_1098;
        fVar14 = local_10a0;
        if (GHIDRA_ZEXT8(bVar2) != 0) {
          if (local_10bc == 0) {
            local_10bc = 0;
          }
          else if (local_10bc == 1) {
            local_10bc = 1;
          }
        }
        if (local_10ec == 3) {
          iVar4 = BGArrayAddAnim((int)pcVar6,local_1088,local_109c,GHIDRA_F2I(undefined4, local_1098),GHIDRA_F2I(undefined4, local_10a4),GHIDRA_F2I(undefined4, local_10a0),local_10b0);
          if (iVar4 == -1) {
            strcat((char *)ErrorMessage,"Error adding anim for ");
            strcat((char *)ErrorMessage,local_10e8);
            goto LAB_0804bccb;
          }
        }
        else {
          iVar4 = BGArrayAdd((int)pcVar6,local_1088,local_10ec,local_109c,GHIDRA_F2I(undefined4, local_1098),GHIDRA_F2I(undefined4, local_10a4),GHIDRA_F2I(undefined4, local_10a0),local_10f0,local_10b8,local_10b4,local_10bc,local_10ac,local_10a8);
          fVar14 = fVar1;
          if (iVar4 == -1) {
            strcat((char *)ErrorMessage,"\nError in ");
            strcat((char *)ErrorMessage,local_10e8);
            goto LAB_0804bccb;
          }
        }
        iVar4 = BGAccess((int)pcVar6,local_1088);
        *(uint *)(iVar4 + 0x80) = local_1094;
        *(undefined4 *)(iVar4 + 0x24) = local_1090;
        *(undefined4 *)(iVar4 + 0x28) = local_108c;
        puVar20 = (uint *)(iVar4 + 0xb4);
        pcVar19 = "id";
        TPGetValueInt((int)param_1,"id",puVar20);
        TPScanf((int)param_1,"tile","%i,%i",&local_10c4,&local_10c0,pcVar19,puVar20,fVar14);
        *(uint *)(iVar4 + 0x2c) = local_10c4;
        *(int *)(iVar4 + 0x30) = local_10c0;
        TPScanf((int)param_1,"tilespacing","%i,%i",iVar4 + 0x34,iVar4 + 0x38);
        if (local_10ec == 3) {
          if (*(int *)(iVar4 + 0x34) < 1) {
            *(undefined4 *)(iVar4 + 0x34) = 1;
          }
          if (*(int *)(iVar4 + 0x38) < 1) {
            *(undefined4 *)(iVar4 + 0x38) = 1;
          }
        }
        *(undefined4 *)(iVar4 + 0x4c) = 0;
        iVar5 = iVar4 + 0x5c;
        iVar16 = iVar4 + 0x54;
        uVar15 = extraout_ECX_01;
        iVar9 = TPScanf((int)param_1,"window","%i,%i,%i,%i",iVar4 + 0x50,iVar4 + 0x58,iVar16,iVar5,
                        extraout_ECX_01);
        uVar12 = extraout_EDX;
        if (3 < iVar9) {
          *(undefined4 *)(iVar4 + 0x4c) = 1;
          TPScanf((int)param_1,"windowdelta","%f,%f",iVar4 + 0x60,iVar4 + 100,iVar16,iVar5,uVar15);
          uVar12 = extraout_EDX_00;
        }
        puVar20 = (uint *)(iVar4 + 0xd0);
        pcVar19 = param_1;
        TPGetValueInt((int)param_1,"positionlink",puVar20);
        TPScanf((int)param_1,"sin.x","%f, %f, %f",iVar4 + 0xd4,iVar4 + 0xdc,iVar4 + 0xe4,puVar20,
                uVar12);
        iVar5 = iVar4 + 0xe8;
        TPScanf((int)param_1,"sin.y","%f, %f, %f",iVar4 + 0xd8,iVar4 + 0xe0,iVar5);
        if (local_10ec == 1) {
          uVar15 = 0;
          local_10dc = 100.0;
          local_10c8 = 0.0;
          iVar4 = TPScanf((int)param_1,"width","%i,%i",&local_10d0,&local_10cc,iVar5,puVar20,uVar12)
          ;
          if (iVar4 == 2) {
            uVar15 = 1;
          }
          else {
            iVar4 = TPScanf((int)param_1,"xscale","%f,%f",&local_10d8,&local_10d4,iVar5,puVar20,
                            uVar12);
            if (iVar4 != 2) {
              sprintf((char *)ErrorMessage,"Missing or invalid width or xscale for parallax in %s.",
                      local_10e8,extraout_ECX_02);
              goto LAB_0804bccb;
            }
            piVar7 = (int *)SpriteArrayAccessGrpItem(*(int **)(pcVar6 + 0x28),local_10ac,local_10a8)
            ;
            local_10d0 = (int)GHIDRA_FIST32((float)*piVar7 * local_10d8);
            local_10cc = (int)GHIDRA_FIST32((float)*piVar7 * local_10d4);
            local_1084 = local_10cc;
          }
          TPGetValueFloat((int)param_1,"yscalestart",&local_10dc);
          TPGetValueFloat((int)param_1,"yscaledelta",&local_10c8);
          uVar10 = local_10c0 * 2 | local_10c4;
          fVar14 = local_10c8 * 10.0;
          iVar4 = (int)GHIDRA_FIST32(local_10dc * 10.0);
          iVar5 = local_10d0;
          iVar16 = local_10cc;
          local_1084 = iVar4;
          puVar11 = (undefined4 *)BGAccess((int)pcVar6,local_1088);
          iVar4 = BGParalSetup((int)pcVar6,puVar11,iVar5,iVar16,iVar4,GHIDRA_F2I(undefined4, fVar14),uVar10,uVar15);
          pcVar19 = pcVar6;
          if (iVar4 == 0) {
            pcVar17 = "Can\'t init parallax in %s.";
            goto LAB_0804bcbb;
          }
        }
        local_10e8 = (char *)TPGroupScanNext((int)param_1);
        local_1088 = local_1088 + 1;
      } while ((int)local_1088 < (int)sVar13);
    }
    iVar4 = BGArrayReadCtrlTP((int)pcVar6,(int)param_1,param_3);
    if (iVar4 != 0) {
      return pcVar6;
    }
    strcat((char *)ErrorMessage,"\nError reading bg control data");
  }
LAB_0804bccb:
  BGArrayFree((int)pcVar6);
  return (char *)0x0;
}
#undef local_10f0
#undef local_10ec
#undef local_10e8
#undef local_10dc
#undef local_10d8
#undef local_10d4
#undef local_10d0
#undef local_10cc
#undef local_10c8
#undef local_10c4
#undef local_10c0
#undef local_10bc
#undef local_10b8
#undef local_10b4
#undef local_10b0
#undef local_10ac
#undef local_10a8
#undef local_10a4
#undef local_10a0
#undef local_109c
#undef local_1098
#undef local_1094
#undef local_1090
#undef local_108c
#undef local_1088
#undef local_1084
#undef local_1080
#undef uStack_107e
#undef local_107c
#undef local_104c
#undef local_101c

/* BGArrayReadCtrlTP @ 0x0804bcf0, 1620 bytes
 * FIXUP: 2 data addresses written as literals replaced by data-image references
 * FIXUP: frame emulation: 16 stack locals placed at their original offsets in a 0xf0-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 BGArrayReadCtrlTP(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  float *pfVar4;
  float *pfVar5;
  float *extraout_ECX;
  uint uVar6;
  uint uVar7;
  size_t sVar8;
  int *piVar9;
  float *pfVar10;
  int *piVar11;
  int *piVar12;
  uint *puVar13;
  char *pcVar14;
  float *pfVar15;
  undefined4 uVar16;
  unsigned char ghidra_frame[0xf0] __attribute__((aligned(16)));
#define local_e8 (*(int *)(ghidra_frame + 0x8))
#define local_e4 (*(uint **)(ghidra_frame + 0xc))
#define local_dc (*(char (*)[48])(ghidra_frame + 0x14))
#define local_ac (*(uint (*)[12])(ghidra_frame + 0x44))
#define local_7c (*(int *)(ghidra_frame + 0x74))
#define local_78 (*(undefined1 (*)[4])(ghidra_frame + 0x78))
#define local_74 (*(undefined1 (*)[4])(ghidra_frame + 0x7c))
#define local_70 (*(undefined1 (*)[4])(ghidra_frame + 0x80))
#define local_6c (*(undefined1 (*)[4])(ghidra_frame + 0x84))
#define local_68 (*(undefined1 (*)[4])(ghidra_frame + 0x88))
#define local_64 (*(undefined1 (*)[4])(ghidra_frame + 0x8c))
#define local_60 (*(undefined1 (*)[4])(ghidra_frame + 0x90))
#define local_5c (*(undefined1 (*)[4])(ghidra_frame + 0x94))
#define local_58 (*(undefined1 (*)[8])(ghidra_frame + 0x98))
#define local_50 (*(uint (*)[4])(ghidra_frame + 0xa0))
#define local_40 (*(uint (*)[12])(ghidra_frame + 0xb0))
  
  sprintf((char *)local_ac,"%sctrl",param_3);
  sprintf(local_dc,"%sctrldef",param_3);
  puVar13 = local_ac;
  do {
    local_e4 = puVar13;
    uVar6 = *local_e4 + 0xfefefeff & (*local_e4 ^ 0xffffffff);
    uVar7 = uVar6 & 0x80808080;
    puVar13 = local_e4 + 1;
  } while (uVar7 == 0);
  if ((uVar6 & 0x8080) == 0) {
    uVar7 = uVar7 >> 0x10;
    puVar13 = (uint *)((int)local_e4 + 6);
  }
  local_e4 = puVar13;
  pfVar10 = (float *)((int)local_e4 + ((-3 - (uint)CARRY1((byte)uVar7,(byte)uVar7)) - (int)local_ac)
                     );
  iVar1 = TPGroupMatchCount(param_2,(char *)local_ac);
  iVar2 = TPGroupMatchCount(param_2,local_dc);
  sVar8 = iVar1 - iVar2;
  if (sVar8 != 0) {
    *(size_t *)(param_1 + 0x38) = sVar8;
    puVar13 = (uint *)0x54;
    pfVar4 = pfVar10;
    pfVar15 = pfVar10;
    iVar1 = ecalloc(sVar8,0x54);
    *(int *)(param_1 + 0x34) = iVar1;
    if (iVar1 == 0) {
      return 0;
    }
    piVar11 = &local_7c;
    for (iVar1 = 0x15; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar11 = 0;
      piVar11 = piVar11 + 1;
    }
    local_50[1] = 0;
    local_40[0] = 0xffffffff;
    local_7c = -1;
    local_50[0] = 0xffffffff;
    pfVar3 = (float *)TPGroupScanFirst(param_2);
    local_e8 = 0;
    if (0 < (int)sVar8) {
      do {
        if (*(int *)(param_2 + 0x18) != *(int *)(param_2 + 0x2c)) {
          do {
            iVar1 = strimatchlen((int)pfVar3 + 1,(int)local_dc,(int)pfVar10 + 3);
            pfVar4 = (float *)0x0;
            if ((iVar1 != 0) &&
               (((*(byte *)((int)__ctype_b + *(char *)((int)(pfVar10 + 1) + (int)pfVar3) * 2 + 1) &
                 0x20) != 0 ||
                (pfVar4 = __ctype_b, *(char *)((int)(pfVar10 + 1) + (int)pfVar3) == ']')))) {
              piVar11 = &local_7c;
              for (iVar1 = 0x15; iVar1 != 0; iVar1 = iVar1 + -1) {
                *piVar11 = 0;
                piVar11 = piVar11 + 1;
              }
              local_50[1] = 0;
              local_40[0] = 0xffffffff;
              local_7c = -1;
              local_50[0] = 0xffffffff;
              uVar16 = 0;
              TPGetValueInt(param_2,"looptime",local_40);
              puVar13 = local_50;
              pcVar14 = "eventID";
              TPGetValueInt(param_2,"eventID",puVar13);
              pfVar4 = (float *)TPScanf(param_2,"ctrlid","%i,%i,%i,%i,%i,%i,%i,%i,%i,%i",&local_7c,
                                        local_78,local_74,local_70,local_6c,local_68,local_64,
                                        local_60,local_5c,local_58,pcVar14,puVar13,uVar16);
              (&local_7c)[(int)pfVar4] = -1;
            }
            puVar13 = local_ac;
            pfVar15 = pfVar4;
            iVar1 = strimatch((char *)((int)pfVar3 + 1),(char *)puVar13);
          } while (((iVar1 == 0) ||
                   (((*(byte *)((int)__ctype_b + *(char *)((int)pfVar10 + 1 + (int)pfVar3) * 2 + 1)
                     & 0x20) == 0 && (*(char *)((int)pfVar10 + 1 + (int)pfVar3) != ']')))) &&
                  (pfVar3 = (float *)TPGroupScanNext(param_2),
                  *(int *)(param_2 + 0x18) != *(int *)(param_2 + 0x2c)));
        }
        piVar11 = (int *)(*(int *)(param_1 + 0x34) + local_e8 * 0x54);
        piVar9 = &local_7c;
        piVar12 = piVar11;
        for (iVar1 = 0x15; iVar1 != 0; iVar1 = iVar1 + -1) {
          *piVar12 = *piVar9;
          piVar9 = piVar9 + 1;
          piVar12 = piVar12 + 1;
        }
        iVar1 = TPScanf(param_2,"ctrlid","%i,%i,%i,%i,%i,%i,%i,%i,%i,%i",piVar11,piVar11 + 1,
                        piVar11 + 2,piVar11 + 3,piVar11 + 4,piVar11 + 5,piVar11 + 6,piVar11 + 7,
                        piVar11 + 8,piVar11 + 9,puVar13,pfVar4,pfVar15);
        piVar11[iVar1] = -1;
        if (*piVar11 == -1) {
          piVar9 = &local_7c;
          piVar12 = piVar11;
          for (iVar1 = 0xb; iVar1 != 0; iVar1 = iVar1 + -1) {
            *piVar12 = *piVar9;
            piVar9 = piVar9 + 1;
            piVar12 = piVar12 + 1;
          }
        }
        pcVar14 = "type";
        piVar12 = piVar9;
        pfVar5 = (float *)TPGetValue(param_2,"type");
        if (pfVar5 == (float *)0x0) {
          sprintf((char *)ErrorMessage,"\n%i/%i %s: Missing \"type\" parameter.",local_e8,sVar8,
                  pfVar3,pcVar14,piVar9,piVar12);
          return 0;
        }
        iVar1 = _alemu_stricmp((char *)pfVar5,"visible");
        if (iVar1 == 0) {
          piVar11[0xc] = 1;
        }
        else {
          iVar1 = _alemu_stricmp((char *)pfVar5,"enable");
          if (iVar1 == 0) {
            piVar11[0xc] = 2;
          }
          else {
            iVar1 = _alemu_stricmp((char *)pfVar5,"velset");
            if (iVar1 == 0) {
              piVar11[0xc] = 4;
            }
            else {
              iVar1 = _alemu_stricmp((char *)pfVar5,"veladd");
              if (iVar1 == 0) {
                piVar11[0xc] = 6;
              }
              else {
                iVar1 = _alemu_stricmp((char *)pfVar5,"posset");
                if (iVar1 == 0) {
                  piVar11[0xc] = 3;
                }
                else {
                  iVar1 = _alemu_stricmp((char *)pfVar5,"posadd");
                  if (iVar1 == 0) {
                    piVar11[0xc] = 5;
                  }
                  else {
                    iVar1 = _alemu_stricmp((char *)pfVar5,"anim");
                    if (iVar1 == 0) {
                      piVar11[0xc] = 8;
                    }
                    else {
                      iVar1 = _alemu_stricmp((char *)pfVar5,"sinx");
                      if (iVar1 == 0) {
                        piVar11[0xc] = 0xb;
                      }
                      else {
                        iVar1 = _alemu_stricmp((char *)pfVar5,"siny");
                        if (iVar1 == 0) {
                          piVar11[0xc] = 0xc;
                        }
                        else {
                          iVar1 = _alemu_stricmp((char *)pfVar5,"null");
                          if (iVar1 == 0) {
                            piVar11[0xc] = 0;
                          }
                          else {
                            iVar1 = _alemu_stricmp((char *)pfVar5,"dummy");
                            if (iVar1 != 0) {
                              sprintf((char *)ErrorMessage,"\n%s: Invalid type: ",pfVar5,iVar1);
                              return 0;
                            }
                            piVar11[0xc] = 0x14;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
        puVar13 = (uint *)(piVar11 + 0xf);
        pfVar4 = pfVar3;
        pfVar15 = pfVar3;
        iVar1 = TPScanf(param_2,"time","%i,%i,%i",piVar11 + 0xd,piVar11 + 0xe);
        if (iVar1 < 2) {
          piVar11[0xe] = piVar11[0xd];
        }
        switch(piVar11[0xc]) {
        case 1:
        case 2:
          pfVar15 = pfVar5;
          goto LAB_0804c2d2;
        case 3:
        case 4:
        case 5:
        case 6:
          piVar11[0x12] = -0x39001000;
          piVar11[0x11] = -0x39001000;
          pfVar15 = extraout_ECX;
          TPGetValueFloat(param_2,"x",(float *)(piVar11 + 0x11));
          pfVar4 = (float *)(piVar11 + 0x12);
          puVar13 = (uint *)(int)&DAT_0827fd99;
          TPGetValueFloat(param_2,"y",pfVar4);
          break;
        case 8:
          pfVar15 = pfVar3;
LAB_0804c2d2:
          pfVar4 = (float *)(piVar11 + 0x10);
          puVar13 = (uint *)(int)&DAT_0827b8f2;
          TPGetValueInt(param_2,"value",(uint *)pfVar4);
          break;
        case 0xb:
        case 0xc:
          puVar13 = (uint *)(piVar11 + 0x13);
          pfVar15 = pfVar5;
          TPScanf(param_2,"value","%f,%f,%f",piVar11 + 0x11,piVar11 + 0x12);
          pfVar4 = pfVar5;
        }
        pfVar3 = (float *)TPGroupScanNext(param_2);
        local_e8 = local_e8 + 1;
      } while (local_e8 < (int)sVar8);
    }
  }
  return 1;
}
#undef local_e8
#undef local_e4
#undef local_dc
#undef local_ac
#undef local_7c
#undef local_78
#undef local_74
#undef local_70
#undef local_6c
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_58
#undef local_50
#undef local_40

/* BGArrayNew @ 0x0804c350, 107 bytes */
int BGArrayNew(size_t param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = ecalloc(1,0x54);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    puVar2 = ArrayNew(param_1,0x100,0);
    *(undefined4 **)(iVar1 + 0x30) = puVar2;
    if (puVar2 == (undefined4 *)0x0) {
      BGArrayFree(iVar1);
      iVar1 = 0;
    }
    else {
      *(undefined4 *)(iVar1 + 0x28) = param_2;
      *(undefined4 *)(iVar1 + 0x48) = 0xffffffff;
      *(undefined4 *)(iVar1 + 0x3c) = 0xffffffff;
    }
  }
  return iVar1;
}

/* BGArrayFree @ 0x0804c3c0, 442 bytes
 * FIXUP: hand-written override (see overrides/) */
/* OVERRIDE: written by hand from the assembly at 0x0804c3c0-0x0804c57a.
 * Reason: the loop is entered by a jump into its middle (0x804c3e7 ->
 * 0x804c507); Ghidra lost the stack depth there, inverted the entry test
 * and left "&stack0xffffffd4" (the scan loop never ran).
 * Layout (VERIFIED, each offset is in the listing):
 *   bga+0x20 anim RC, freed if bga+0x24      bga+0x28 sprites, if bga+0x2c
 *   bga+0x30 element Array                   bga+0x34 malloc'd block
 *   element: [0] type (1 = parallax/tiled), [0x10] count (0x40),
 *            [0x27] 0x9c block, [0x28]/[0x29] 0xa0 table + "owns entries" flag,
 *            [0x2a]/[0x2b] 0xa8 table + flag, [0x2c] 0xb0 table (always owns),
 *            [0x3b] 0xec animation.
 * The function ends with a tail call to free(bga); the value left in EAX is
 * not used by either caller (0x804c... BGRead error path, BGFree). */
undefined4 BGArrayFree(int param_1)
{
  int arr, i;
  int *e;

  if (param_1 == 0)
    return 0;
  arr = *(int *)(param_1 + 0x30);
  e = arr ? (int *)ArrayScanFirst(arr) : (int *)0;          /* 0x804c3e2 */
  while (e != 0) {
    if (e[0] == 1) {
      if (e[0x27] != 0)
        free((void *)e[0x27]);
      if (e[0x28] != 0) {
        if (e[0x29] != 0)
          for (i = 0; i < e[0x10]; i++)
            if (((int *)e[0x28])[i] != 0)
              free((void *)((int *)e[0x28])[i]);
        free((void *)e[0x28]);
      }
      if (e[0x2a] != 0) {
        if (e[0x2b] != 0)
          for (i = 0; i < e[0x10]; i++)
            if (((int *)e[0x2a])[i] != 0)
              free((void *)((int *)e[0x2a])[i]);
        free((void *)e[0x2a]);
      }
      if (e[0x2c] != 0) {
        for (i = 0; i < e[0x10]; i++)
          if (((int *)e[0x2c])[i] != 0)
            free((void *)((int *)e[0x2c])[i]);
        free((void *)e[0x2c]);
      }
    }
    AnimFree((void *)e[0x3b]);                                /* 0x804c4f7 */
    e = (int *)ArrayScanNext(arr);                            /* 0x804c502 */
  }
  ArrayFree(*(void **)(param_1 + 0x30));
  if (*(int *)(param_1 + 0x24) != 0)
    AnimRCFree(*(int **)(param_1 + 0x20));
  if (*(int *)(param_1 + 0x2c) != 0)
    SpriteArrayFree(*(int **)(param_1 + 0x28));
  if (*(int *)(param_1 + 0x34) != 0)
    free(*(void **)(param_1 + 0x34));
  free((void *)param_1);                                      /* tail call 0x804c56d */
  return 0;
}

/* BGArrayAdd @ 0x0804c580, 323 bytes
 * FIXUP: frame emulation: 13 stack locals placed at their original offsets in a 0x120-byte frame (a local's address escapes, see apply_frame_emulation) */
int BGArrayAdd(int param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5,
              undefined4 param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9,
              undefined4 param_10,undefined4 param_11,int param_12,int param_13)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  unsigned char ghidra_frame[0x120] __attribute__((aligned(16)));
#define local_11c (*(int (*)[7])(ghidra_frame + 0x4))
#define local_100 (*(undefined4 *)(ghidra_frame + 0x20))
#define local_fc (*(undefined4 *)(ghidra_frame + 0x24))
#define local_e0 (*(undefined4 *)(ghidra_frame + 0x40))
#define local_dc (*(undefined4 *)(ghidra_frame + 0x44))
#define local_ac (*(undefined4 *)(ghidra_frame + 0x74))
#define local_a8 (*(undefined4 *)(ghidra_frame + 0x78))
#define local_a4 (*(undefined4 *)(ghidra_frame + 0x7c))
#define local_a0 (*(undefined4 *)(ghidra_frame + 0x80))
#define local_98 (*(undefined4 *)(ghidra_frame + 0x88))
#define local_64 (*(undefined4 *)(ghidra_frame + 0xbc))
#define local_60 (*(undefined4 *)(ghidra_frame + 0xc0))
#define local_28 (*(int *)(ghidra_frame + 0xf8))
  
  if (param_3 == 3) {
    iVar1 = -1;
  }
  else {
    piVar3 = local_11c;
    for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar3 = 0;
      piVar3 = piVar3 + 1;
    }
    local_11c[0] = param_3;
    local_11c[1] = param_4;
    local_11c[2] = param_5;
    local_100 = param_6;
    local_fc = param_7;
    local_ac = param_8;
    local_a8 = param_9;
    local_a4 = param_10;
    local_a0 = param_11;
    local_98 = 1;
    if (param_3 != 10) {
      iVar1 = SpriteArrayGetNum(*(int **)(param_1 + 0x28),param_12,param_13);
      if (iVar1 == -1) {
        sprintf((char *)ErrorMessage,"Sprite doesn\'t exist: %i,%i",param_12,param_13);
        return -1;
      }
      local_28 = iVar1;
      puVar2 = (undefined4 *)SpriteArrayAccess(*(int **)(param_1 + 0x28),iVar1);
      local_e0 = *puVar2;
      iVar1 = SpriteArrayAccess(*(int **)(param_1 + 0x28),iVar1);
      local_dc = *(undefined4 *)(iVar1 + 4);
    }
    local_64 = 1;
    local_60 = 1;
    iVar1 = ArrayAdd(*(int *)(param_1 + 0x30),local_11c,0,param_2);
  }
  return iVar1;
}
#undef local_11c
#undef local_100
#undef local_fc
#undef local_e0
#undef local_dc
#undef local_ac
#undef local_a8
#undef local_a4
#undef local_a0
#undef local_98
#undef local_64
#undef local_60
#undef local_28

/* BGArrayAddAnim @ 0x0804c6d0, 223 bytes
 * FIXUP: frame emulation: 8 stack locals placed at their original offsets in a 0x120-byte frame (a local's address escapes, see apply_frame_emulation) */
int BGArrayAddAnim(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                  undefined4 param_5,undefined4 param_6,int param_7)

{
  int iVar1;
  undefined4 *puVar2;
  unsigned char ghidra_frame[0x120] __attribute__((aligned(16)));
#define local_11c (*(undefined4 (*)[7])(ghidra_frame + 0x4))
#define local_100 (*(undefined4 *)(ghidra_frame + 0x20))
#define local_fc (*(undefined4 *)(ghidra_frame + 0x24))
#define local_98 (*(undefined4 *)(ghidra_frame + 0x88))
#define local_64 (*(undefined4 *)(ghidra_frame + 0xbc))
#define local_60 (*(undefined4 *)(ghidra_frame + 0xc0))
#define local_30 (*(int **)(ghidra_frame + 0xf0))
#define local_2c (*(int *)(ghidra_frame + 0xf4))
  
  puVar2 = local_11c;
  for (iVar1 = 0x40; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  local_11c[1] = param_3;
  local_11c[0] = 3;
  local_11c[2] = param_4;
  local_100 = param_5;
  local_fc = param_6;
  local_98 = 1;
  local_30 = AnimNew(*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x28));
  if ((local_30 != (int *)0x0) && (iVar1 = AnimChangeAction(local_30,0,param_7), iVar1 != 0)) {
    local_2c = param_7;
    local_64 = 1;
    local_60 = 1;
    iVar1 = ArrayAdd(*(int *)(param_1 + 0x30),local_11c,0,param_2);
    return iVar1;
  }
  return -1;
}
#undef local_11c
#undef local_100
#undef local_fc
#undef local_98
#undef local_64
#undef local_60
#undef local_30
#undef local_2c

/* BGArraySetViewScale @ 0x0804c7b0, 50 bytes */
void BGArraySetViewScale(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0x30);
  iVar2 = ArrayScanFirst(iVar1);
  while (iVar2 != 0) {
    *(undefined4 *)(iVar2 + 0x84) = param_2;
    iVar2 = ArrayScanNext(iVar1);
  }
  return;
}

/* BGArrayMove @ 0x0804c7f0, 31 bytes
 * FIXUP: return type set to void: only unaffected-register values were returned */
void BGArrayMove(int *param_1,float param_2,float param_3)

{
  undefined4 extraout_EAX;
  
  BGArrayMoveOffset(param_1,param_2,param_3,0,0);
  return;
}

/* BGArrayMoveOffset @ 0x0804c810, 489 bytes
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
void BGArrayMoveOffset(int *param_1,float param_2,float param_3,int param_4,int param_5)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  longdouble lVar4;
  longdouble lVar5;
  float local_20;
  float local_1c;
  
  iVar1 = param_1[0xc];
  local_20 = 0.0;
  local_1c = 0.0;
  *param_1 = GHIDRA_F2I(int, param_2);
  param_1[1] = GHIDRA_F2I(int, param_3);
  piVar2 = (int *)ArrayScanFirst(iVar1);
  if (piVar2 != (int *)0x0) {
    do {
      lVar5 = (longdouble)0;
      lVar4 = lVar5;
      if ((longdouble)GHIDRA_I2F(piVar2[0x37]) != lVar5) {
        lVar4 = ((longdouble)GHIDRA_I2F(piVar2[0x39]) / (longdouble)GHIDRA_I2F(piVar2[0x37])) *
                (longdouble)((double)3.14159);
        lVar4 = (longdouble)fsin(lVar4 + lVar4);
        lVar4 = (longdouble)(float)(lVar4 * (longdouble)GHIDRA_I2F(piVar2[0x35]));
      }
      if ((longdouble)GHIDRA_I2F(piVar2[0x38]) != lVar5) {
        lVar5 = ((longdouble)GHIDRA_I2F(piVar2[0x3a]) / (longdouble)GHIDRA_I2F(piVar2[0x38])) *
                (longdouble)((double)3.14159);
        lVar5 = (longdouble)fsin(lVar5 + lVar5);
        lVar5 = (longdouble)(float)(lVar5 * (longdouble)GHIDRA_I2F(piVar2[0x36]));
      }
      if (piVar2[0x34] == 0) {
        iVar3 = param_1[7];
        lVar4 = (longdouble)GHIDRA_I2F(piVar2[9]) * (longdouble)iVar3 +
                (longdouble)piVar2[1] + (longdouble)GHIDRA_I2F(piVar2[7]) * (longdouble)param_2 + lVar4;
        piVar2[5] = GHIDRA_F2I(int, (float)lVar4);
        local_1c = (float)lVar4;
        lVar5 = (longdouble)GHIDRA_I2F(piVar2[8]) * (longdouble)param_3 + (longdouble)piVar2[2] +
                (longdouble)GHIDRA_I2F(piVar2[10]) * (longdouble)iVar3 + lVar5;
        piVar2[6] = GHIDRA_F2I(int, (float)lVar5);
        local_20 = (float)lVar5;
      }
      else {
        piVar2[5] = GHIDRA_F2I(int, (float)((longdouble)piVar2[1] + lVar4 + (longdouble)local_1c));
        piVar2[6] = GHIDRA_F2I(int, (float)((longdouble)piVar2[2] + lVar5 + (longdouble)local_20));
      }
      piVar2[5] = GHIDRA_F2I(int, (GHIDRA_I2F(piVar2[0x30]) + (float)param_4 + GHIDRA_I2F(piVar2[5])));
      piVar2[6] = GHIDRA_F2I(int, (GHIDRA_I2F(piVar2[0x31]) + (float)param_5 + GHIDRA_I2F(piVar2[6])));
      if (piVar2[0x13] != 0) {
        iVar3 = roundfloat(GHIDRA_I2F(piVar2[0x18]) * param_2);
        piVar2[0x1a] = iVar3;
        iVar3 = roundfloat(GHIDRA_I2F(piVar2[0x19]) * param_3);
        piVar2[0x1b] = iVar3;
      }
      if (*piVar2 == 1) {
        piVar2[0x24] = (int)GHIDRA_FIST32(GHIDRA_I2F(piVar2[0x25]) * param_3 + (float10)piVar2[0x23]);
      }
      iVar3 = roundfloat(GHIDRA_I2F(piVar2[5]));
      piVar2[3] = iVar3;
      iVar3 = roundfloat(GHIDRA_I2F(piVar2[6]));
      piVar2[4] = iVar3;
      piVar2 = (int *)ArrayScanNext(iVar1);
    } while (piVar2 != (int *)0x0);
  }
  return;
}

/* BGArrayDraw @ 0x0804ca00, 92 bytes */
void BGArrayDraw(int param_1)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  
  iVar1 = *(int *)(param_1 + 0x30);
  if (*(int *)(param_1 + 0x48) != -1) {
    uVar2 = makecol(*(undefined4 *)(param_1 + 0x48),*(int *)(param_1 + 0x4c),
                    *(int *)(param_1 + 0x50));
    W_Cls(uVar2);
  }
  piVar3 = (int *)ArrayScanFirst(iVar1);
  while (piVar3 != (int *)0x0) {
    BGDraw(param_1,piVar3);
    piVar3 = (int *)ArrayScanNext(iVar1);
  }
  return;
}

/* BGArrayDrawLayer @ 0x0804ca60, 107 bytes */
void BGArrayDrawLayer(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  
  iVar1 = *(int *)(param_1 + 0x30);
  if ((*(int *)(param_1 + 0x48) != -1) && (param_2 == 0)) {
    uVar2 = makecol(*(undefined4 *)(param_1 + 0x48),*(int *)(param_1 + 0x4c),
                    *(int *)(param_1 + 0x50));
    W_Cls(uVar2);
  }
  piVar3 = (int *)ArrayScanFirst(iVar1);
  while (piVar3 != (int *)0x0) {
    if (piVar3[0x20] == param_2) {
      BGDraw(param_1,piVar3);
    }
    piVar3 = (int *)ArrayScanNext(iVar1);
  }
  return;
}

/* BGArrayUpdate @ 0x0804cad0, 222 bytes */
void BGArrayUpdate(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *(int *)(param_1 + 0x30);
  *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(param_1 + 0x40);
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_1 + 0x44);
  BGArrayCtrlUpdate(param_1);
  piVar2 = (int *)ArrayScanFirst(iVar1);
  while (piVar2 != (int *)0x0) {
    if (piVar2[0x2e] != 0) {
      if (*piVar2 == 3) {
        AnimUpdate((undefined4 *)piVar2[0x3b]);
      }
      if (GHIDRA_I2F(piVar2[0x37]) != 0.0) {
        piVar2[0x39] = GHIDRA_F2I(int, (GHIDRA_I2F(piVar2[0x39]) + 1.0));
      }
      if (GHIDRA_I2F(piVar2[0x38]) != 0.0) {
        piVar2[0x3a] = GHIDRA_F2I(int, (GHIDRA_I2F(piVar2[0x3a]) + 1.0));
      }
    }
    piVar2[0x30] = GHIDRA_F2I(int, (GHIDRA_I2F(piVar2[0x30]) + GHIDRA_I2F(piVar2[0x32])));
    piVar2[0x31] = GHIDRA_F2I(int, (GHIDRA_I2F(piVar2[0x31]) + GHIDRA_I2F(piVar2[0x33])));
    piVar2 = (int *)ArrayScanNext(iVar1);
  }
  *(int *)(param_1 + 0x1c) = *(int *)(param_1 + 0x1c) + 1;
  return;
}

/* BGArrayCtrlUpdate @ 0x0804cbb0, 707 bytes */
void BGArrayCtrlUpdate(int param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  
  iVar2 = *(int *)(param_1 + 0x30);
  iVar5 = *(int *)(param_1 + 0x34);
  if ((iVar5 != 0) && (iVar6 = 0, 0 < *(int *)(param_1 + 0x38))) {
    while( true ) {
      piVar1 = (int *)(iVar5 + iVar6 * 0x54);
      iVar5 = piVar1[0x14];
      if ((((piVar1[0xd] <= iVar5) && (iVar5 <= piVar1[0xe])) ||
          ((piVar1[0xd] == -1 && (*(int *)(param_1 + 0x1c) == 0)))) && (piVar1[0xc] < 100)) {
        piVar3 = (int *)ArrayScanFirst(iVar2);
        while (piVar3 != (int *)0x0) {
          bVar7 = *piVar1 == -1;
          if (!bVar7) {
            piVar4 = piVar1;
            do {
              if (piVar3[0x2d] == *piVar4) {
                bVar7 = true;
              }
              piVar4 = piVar4 + 1;
            } while (*piVar4 != -1);
          }
          if (bVar7) {
            switch(piVar1[0xc]) {
            case 1:
              piVar3[0x2f] = piVar1[0x10];
              break;
            case 2:
              piVar3[0x2e] = piVar1[0x10];
              break;
            case 3:
              if (GHIDRA_I2F(piVar1[0x11]) != -32760.0) {
                piVar3[0x30] = piVar1[0x11];
              }
              if (GHIDRA_I2F(piVar1[0x12]) != -32760.0) {
                piVar3[0x31] = piVar1[0x12];
              }
              break;
            case 4:
              if (GHIDRA_I2F(piVar1[0x11]) != -32760.0) {
                piVar3[0x32] = piVar1[0x11];
              }
              if (GHIDRA_I2F(piVar1[0x12]) != -32760.0) {
                piVar3[0x33] = piVar1[0x12];
              }
              break;
            case 5:
              if (GHIDRA_I2F(piVar1[0x11]) != -32760.0) {
                piVar3[0x30] = GHIDRA_F2I(int, (GHIDRA_I2F(piVar3[0x30]) + GHIDRA_I2F(piVar1[0x11])));
              }
              if (GHIDRA_I2F(piVar1[0x12]) != -32760.0) {
                piVar3[0x31] = GHIDRA_F2I(int, (GHIDRA_I2F(piVar3[0x31]) + GHIDRA_I2F(piVar1[0x12])));
              }
              break;
            case 6:
              if (GHIDRA_I2F(piVar1[0x11]) != -32760.0) {
                piVar3[0x32] = GHIDRA_F2I(int, (GHIDRA_I2F(piVar3[0x32]) + GHIDRA_I2F(piVar1[0x11])));
              }
              if (GHIDRA_I2F(piVar1[0x12]) != -32760.0) {
                piVar3[0x33] = GHIDRA_F2I(int, (GHIDRA_I2F(piVar3[0x33]) + GHIDRA_I2F(piVar1[0x12])));
              }
              break;
            case 8:
              if ((*piVar3 == 3) && (piVar3[0x3b] != 0)) {
                AnimChangeAction((int *)piVar3[0x3b],0,piVar1[0x10]);
                AnimResetAction((int *)piVar3[0x3b]);
              }
              break;
            case 0xb:
              piVar3[0x35] = piVar1[0x11];
              piVar3[0x37] = piVar1[0x12];
              piVar3[0x39] = piVar1[0x13];
              break;
            case 0xc:
              piVar3[0x36] = piVar1[0x11];
              piVar3[0x38] = piVar1[0x12];
              piVar3[0x3a] = piVar1[0x13];
            }
          }
          piVar3 = (int *)ArrayScanNext(iVar2);
        }
        iVar5 = piVar1[0x14];
      }
      piVar1[0x14] = iVar5 + 1;
      if ((piVar1[0xf] <= iVar5 + 1) && (piVar1[0xf] != -1)) {
        piVar1[0x14] = 0;
      }
      iVar6 = iVar6 + 1;
      if (*(int *)(param_1 + 0x38) <= iVar6) break;
      iVar5 = *(int *)(param_1 + 0x34);
    }
  }
  return;
}

/* BGArrayReset @ 0x0804ce80, 236 bytes */
void BGArrayReset(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar1 = *(int *)(param_1 + 0x30);
  *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(param_1 + 0x40);
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_1 + 0x44);
  if (0 < *(int *)(param_1 + 0x38)) {
    puVar2 = (undefined4 *)(*(int *)(param_1 + 0x34) + 0x50);
    do {
      *puVar2 = 0;
      puVar2 = puVar2 + 0x15;
      iVar4 = iVar4 + 1;
    } while (iVar4 < *(int *)(param_1 + 0x38));
  }
  piVar3 = (int *)ArrayScanFirst(iVar1);
  while (piVar3 != (int *)0x0) {
    if (*piVar3 == 3) {
      AnimChangeAction((int *)piVar3[0x3b],0,piVar3[0x3c]);
      AnimResetAction((int *)piVar3[0x3b]);
    }
    piVar3[0x2f] = 1;
    piVar3[0x2e] = 1;
    piVar3[0x33] = 0;
    piVar3[0x32] = 0;
    piVar3[0x31] = 0;
    piVar3[0x30] = 0;
    piVar3[0x3a] = 0;
    piVar3[0x39] = 0;
    piVar3 = (int *)ArrayScanNext(iVar1);
  }
  *(undefined4 *)(param_1 + 0x1c) = 0;
  return;
}

/* BGAccess @ 0x0804cf70, 27 bytes */
undefined4 BGAccess(int param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = ArrayAccessGrpItem(*(int *)(param_1 + 0x30),0,param_2);
  return uVar1;
}

/* BGAccessID @ 0x0804cf90, 57 bytes */
int BGAccessID(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = ArrayScanFirst(*(int *)(param_1 + 0x30));
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if (*(int *)(iVar1 + 0xb4) == param_2) break;
    iVar1 = ArrayScanNext(*(int *)(param_1 + 0x30));
  }
  return iVar1;
}

/* BGParalSetup @ 0x0804cfd0, 530 bytes
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: untyped (undefined4) <-> float moves kept as bit copies: 1 assignments, 0 calls, 0 returns */
undefined4
BGParalSetup(int param_1,undefined4 *param_2,int param_3,int param_4,undefined4 param_5,
            undefined4 param_6,uint param_7,undefined4 param_8)

{
  size_t sVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int local_30;
  int local_2c;
  
  piVar2 = (int *)SpriteArrayAccess(*(int **)(param_1 + 0x28),param_2[0x3d]);
  sVar1 = piVar2[4];
  if (piVar2[7] == 0) {
    *param_2 = 1;
    param_2[0xf] = param_3;
    param_2[0x23] = param_5;
    param_2[0xb] = param_7 & 1;
    param_2[0xc] = 0;
    param_2[0x25] = param_6;
    param_2[0x22] = param_8;
    param_2[0x26] = GHIDRA_F2I(undefined4, (float)param_4 / (float)param_3);
    iVar3 = ecalloc(param_2[0x10],4);
    param_2[0x27] = iVar3;
    if (iVar3 != 0) {
      iVar3 = ecalloc(param_2[0x10],4);
      param_2[0x28] = iVar3;
      if (iVar3 != 0) {
        iVar6 = 0;
        iVar3 = piVar2[9];
        iVar4 = param_2[0x10];
        if (0 < iVar4) {
          do {
            if (param_2[0x22] == 0) {
              iVar5 = param_2[0x27];
              iVar4 = *piVar2;
            }
            else {
              iVar5 = param_2[0x27];
              iVar4 = (int)GHIDRA_FIST32(((float)(param_4 - param_3) * (float10)iVar6) / (float)(iVar4 + -1) +
                                 (float)param_3);
            }
            *(int *)(iVar5 + iVar6 * 4) = iVar4;
            if (param_2[0x22] == 0) {
              *(int *)(param_2[0x28] + iVar6 * 4) = iVar3 + *(int *)(piVar2[0xb] + iVar6 * 4);
              param_2[0x29] = 0;
            }
            else {
              iVar4 = ecalloc(*(int *)(param_2[0x27] + iVar6 * 4) + 4,sVar1);
              *(int *)(param_2[0x28] + iVar6 * 4) = iVar4;
              if (iVar4 == 0) {
                return 0;
              }
              local_2c = param_2[0x27];
              iVar4 = 0;
              if (0 < *(int *)(local_2c + iVar6 * 4)) {
                do {
                  local_30 = local_2c;
                  if (sVar1 == 8) {
                    *(undefined1 *)(iVar4 + *(int *)(param_2[0x28] + iVar6 * 4)) =
                         *(undefined1 *)
                          ((*piVar2 * iVar4) / *(int *)(local_2c + iVar6 * 4) +
                           *(int *)(piVar2[0xb] + iVar6 * 4) + iVar3);
                    local_30 = param_2[0x27];
                  }
                  iVar4 = iVar4 + 1;
                  local_2c = local_30;
                } while (iVar4 < *(int *)(local_30 + iVar6 * 4));
              }
              param_2[0x29] = 1;
            }
            iVar6 = iVar6 + 1;
            iVar4 = param_2[0x10];
          } while (iVar6 < iVar4);
        }
        return 1;
      }
    }
  }
  return 0;
}

/* BGDraw @ 0x0804d1f0, 798 bytes
 * FIXUP: 15 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
void BGDraw(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  iVar5 = W_y1;
  iVar4 = W_x2;
  iVar3 = W_x1;
  iVar2 = W_y2;
  iVar8 = V_Width / 2;
  iVar6 = roundfloat((float10)param_2[0x21] * GHIDRA_I2F(param_2[5]));
  iVar7 = roundfloat((float10)param_2[0x21] * GHIDRA_I2F(param_2[6]));
  if (param_2[0x2e] == 0) {
    return;
  }
  if (param_2[0x2f] == 0) {
    return;
  }
  if (param_2[0x13] != 0) {
    W_Define((param_2[0x14] - param_2[0x1a]) * param_2[0x21],
             (param_2[0x16] - param_2[0x1b]) * param_2[0x21],
             (param_2[0x15] - param_2[0x1a]) * param_2[0x21],
             (param_2[0x17] - param_2[0x1b]) * param_2[0x21]);
  }
  iVar1 = *param_2;
  if (iVar1 == 1) {
    BGParalDrawScale(param_1,(int)param_2,param_2[0x24]);
  }
  else if (iVar1 < 2) {
    if (iVar1 == 0) {
      if ((param_2[0xb] == 0) && (param_2[0xc] == 0)) {
        iVar1 = param_2[0x1c];
        if (iVar1 == 2) {
          W_PutSpriteTransSub(*(int **)(param_1 + 0x28),param_2[0x3d],iVar8 + iVar6,iVar7);
        }
        else {
          if (iVar1 < 3) {
            if (iVar1 == 1) {
              W_ScaleSpriteTransAdd_S
                        (*(int **)(param_1 + 0x28),param_2[0x3d],(float)(iVar8 + iVar6),(float10)iVar7
                         ,(float10)param_2[0x21],(float10)param_2[0x21]);
              goto LAB_0804d4ea;
            }
          }
          else if (iVar1 == 3) {
            W_ScaleSpriteTransAdd_B_S
                      (*(int **)(param_1 + 0x28),param_2[0x3d],(float)(iVar8 + iVar6),(float10)iVar7,
                       (float10)param_2[0x21],(float10)param_2[0x21],param_2[0x1d],param_2[0x1e]);
            goto LAB_0804d4ea;
          }
          if (param_2[0x1f] == 1) {
            W_ScaleSprite_S(*(int **)(param_1 + 0x28),param_2[0x3d],(float)(iVar8 + iVar6),
                            (float10)iVar7,(float10)param_2[0x21],(float10)param_2[0x21]);
          }
          else {
            W_ScaleSpriteFlat_S(*(int **)(param_1 + 0x28),param_2[0x3d],iVar8 + iVar6,iVar7,
                                (float10)param_2[0x21],(float10)param_2[0x21]);
          }
        }
      }
      else {
        BGNormalDrawTile(param_1,(int)param_2);
      }
    }
  }
  else if (iVar1 == 3) {
    if ((param_2[0xb] == 0) && (param_2[0xc] == 0)) {
      AnimDrawScale((undefined4 *)param_2[0x3b],iVar8 + iVar6,iVar7,(float10)param_2[0x21],
                    (float10)param_2[0x21]);
    }
    else {
      BGAnimDrawTile(param_1,(int)param_2);
    }
  }
LAB_0804d4ea:
  W_Define(iVar3,iVar5,iVar4,iVar2);
  return;
}

/* BGNormalDrawTile @ 0x0804d510, 890 bytes
 * FIXUP: 14 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
void BGNormalDrawTile(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  
  iVar1 = SpriteArrayAccess(*(int **)(param_1 + 0x28),*(int *)(param_2 + 0xf4));
  iVar3 = *(int *)(param_2 + 0x84);
  local_30 = 0;
  local_34 = 0;
  iVar5 = V_Width / 2 + *(int *)(param_2 + 0xc) * iVar3;
  iVar4 = (*(int *)(param_2 + 0x34) + *(int *)(param_2 + 0x3c)) * iVar3;
  iVar2 = (*(int *)(param_2 + 0x34) + *(int *)(param_2 + 0x40)) * iVar3;
  iVar8 = *(int *)(param_2 + 0x10) * iVar3;
  if (iVar1 != 0) {
    local_30 = *(int *)(iVar1 + 8) * iVar3;
    local_34 = iVar3 * *(int *)(iVar1 + 0xc);
  }
  local_28 = *(int *)(param_2 + 0x2c);
  local_2c = *(int *)(param_2 + 0x30);
  iVar3 = local_2c;
  if (local_28 == 1) {
    *(int *)(param_2 + 0xc) = *(int *)(param_2 + 0xc) - local_30;
    if ((iVar5 < -iVar4) || (0 < iVar5)) {
      iVar5 = iVar5 % iVar4;
    }
    if (0 < iVar5) {
      iVar5 = iVar5 - iVar4;
    }
    *(int *)(param_2 + 0xc) = *(int *)(param_2 + 0xc) + local_30;
    local_28 = -1;
    iVar3 = *(int *)(param_2 + 0x30);
  }
  if (local_28 == 0) {
    local_28 = 1;
  }
  if (local_2c == 0) {
    local_2c = 1;
  }
  if (iVar3 == 1) {
    iVar8 = iVar8 - local_34;
    if ((iVar8 < -iVar2) || (0 < iVar8)) {
      iVar8 = iVar8 % iVar2;
    }
    if (0 < iVar8) {
      iVar8 = iVar8 - iVar2;
    }
    iVar8 = iVar8 + local_34;
    local_2c = -1;
  }
  iVar3 = V_Height;
  iVar1 = V_Width;
  if (iVar8 - local_34 < V_Height) {
    do {
      if (local_2c == 0) {
        return;
      }
      iVar6 = iVar5;
      iVar7 = local_28;
      if (iVar5 - local_30 < iVar1) {
        do {
          if (iVar7 == 0) break;
          iVar3 = *(int *)(param_2 + 0x70);
          if (iVar3 == 2) {
            W_PutSpriteTransSub(*(int **)(param_1 + 0x28),*(int *)(param_2 + 0xf4),iVar6,iVar8);
          }
          else if (iVar3 < 3) {
            if (iVar3 == 1) {
              W_ScaleSpriteTransAdd_S
                        (*(int **)(param_1 + 0x28),*(int *)(param_2 + 0xf4),(float10)iVar6,
                         (float10)iVar8,(float10)*(int *)(param_2 + 0x84),
                         (float10)*(int *)(param_2 + 0x84));
            }
            else {
LAB_0804d7b0:
              if (*(int *)(param_2 + 0x7c) == 1) {
                W_ScaleSprite_S(*(int **)(param_1 + 0x28),*(int *)(param_2 + 0xf4),(float10)iVar6,
                                (float10)iVar8,(float10)*(int *)(param_2 + 0x84),
                                (float10)*(int *)(param_2 + 0x84));
              }
              else {
                W_ScaleSpriteFlat_S(*(int **)(param_1 + 0x28),*(int *)(param_2 + 0xf4),iVar6,iVar8,
                                    (float10)*(int *)(param_2 + 0x84),(float10)*(int *)(param_2 + 0x84))
                ;
              }
            }
          }
          else {
            if (iVar3 != 3) goto LAB_0804d7b0;
            W_ScaleSpriteTransAdd_B_S
                      (*(int **)(param_1 + 0x28),*(int *)(param_2 + 0xf4),(float10)iVar6,(float10)iVar8,
                       (float10)*(int *)(param_2 + 0x84),(float10)*(int *)(param_2 + 0x84),
                       *(int *)(param_2 + 0x74),*(int *)(param_2 + 0x78));
          }
          iVar6 = iVar6 + iVar4;
          if (0 < iVar7) {
            iVar7 = iVar7 + -1;
          }
          iVar1 = V_Width;
          iVar3 = V_Height;
        } while (iVar6 - local_30 < V_Width);
      }
      iVar8 = iVar8 + iVar2;
      if (0 < local_2c) {
        local_2c = local_2c + -1;
      }
    } while (iVar8 - local_34 < iVar3);
  }
  return;
}

/* BGAnimDrawTile @ 0x0804d890, 361 bytes
 * FIXUP: 2 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
void BGAnimDrawTile(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int local_24;
  int local_20;
  int local_18;
  
  iVar5 = *(int *)(param_2 + 0x84);
  local_24 = V_Width;
  iVar2 = V_Width / 2 + *(int *)(param_2 + 0xc) * iVar5;
  local_18 = *(int *)(param_2 + 0x34) * iVar5;
  iVar6 = *(int *)(param_2 + 0x10) * iVar5;
  if (local_18 == 0) {
    local_18 = iVar5;
  }
  local_20 = *(int *)(param_2 + 0x2c);
  iVar5 = *(int *)(param_2 + 0x30);
  if (local_20 == 1) {
    if ((iVar2 < -local_18) || (0 < iVar2)) {
      iVar2 = iVar2 % local_18;
    }
    if (0 < iVar2) {
      iVar2 = iVar2 - local_18;
    }
    local_20 = -1;
  }
  if (local_20 == 0) {
    local_20 = 1;
  }
  iVar4 = iVar5;
  if (iVar5 == 0) {
    iVar4 = 1;
  }
  iVar1 = V_Height;
  if (iVar5 == 1) {
    if ((iVar6 < -local_18) || (0 < iVar6)) {
      iVar6 = iVar6 % local_18;
    }
    if (0 < iVar6) {
      iVar6 = iVar6 - local_18;
    }
    iVar4 = -1;
  }
  do {
    if ((iVar1 <= iVar6) || (iVar4 == 0)) {
      return;
    }
    iVar5 = iVar2;
    iVar3 = local_20;
    if (iVar2 < local_24) {
      do {
        if (iVar3 == 0) break;
        AnimDrawScale(*(undefined4 **)(param_2 + 0xec),iVar5,iVar6,(float10)*(int *)(param_2 + 0x84),
                      (float10)*(int *)(param_2 + 0x84));
        iVar5 = iVar5 + local_18;
        if (0 < iVar3) {
          iVar3 = iVar3 + -1;
        }
        local_24 = V_Width;
        iVar1 = V_Height;
      } while (iVar5 < V_Width);
    }
    iVar6 = iVar6 + local_18;
    if (0 < iVar4) {
      iVar4 = iVar4 + -1;
    }
  } while( true );
}

/* BGParalDraw @ 0x0804da00, 27 bytes */
void BGParalDraw(int param_1,int param_2)

{
  BGParalDrawScale(param_1,param_2,1000);
  return;
}

/* BGParalDrawScale @ 0x0804da20, 144 bytes */
void BGParalDrawScale(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = SpriteArrayAccess(*(int **)(param_1 + 0x28),*(int *)(param_2 + 0xf4));
  if (V_ColDepth - 0xfU < 2) {
    if (*(int *)(iVar1 + 0x10) == 8) {
      if (*(int *)(param_2 + 0x7c) == 1) {
        if (*(int *)(param_2 + 0x84) == 2) {
          BGParalDraw8to16_2X();
        }
        else {
          BGParalDraw8to16(param_1,param_2,param_3);
        }
      }
      else if (*(int *)(param_2 + 0x84) == 2) {
        BGParalDraw8to16Flat2X();
      }
      else {
        BGParalDraw8to16Flat(param_1,param_2,param_3);
      }
    }
    else {
      BGParalDraw16();
    }
  }
  return;
}

/* BGParalDraw8to16 @ 0x0804dab0, 1276 bytes
 * FIXUP: 5 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void BGParalDraw8to16(int param_1,int param_2,int param_3)

{
  float10 fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  byte *pbVar14;
  undefined2 *puVar15;
  int local_60;
  int local_5c;
  int local_58;
  int local_44;
  int local_40;
  float local_38;
  int local_34;
  int local_30;
  int local_18;
  
  iVar5 = SpriteArrayAccess(*(int **)(param_1 + 0x28),*(int *)(param_2 + 0xf4));
  iVar6 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  local_38 = *(float *)(param_2 + 0x14);
  local_40 = 500;
  local_44 = 0;
  if ((iVar5 != 0) && (0 < param_3)) {
    if ((*(int *)(param_2 + 0x2c) != 0) &&
       ((local_38 < (float)-*(int *)(param_2 + 0x3c) || (0.0 < local_38)))) {
      local_38 = (local_38 - (float10)(int)GHIDRA_FIST32(local_38)) +
                 (float)((int)GHIDRA_FIST32(local_38) % *(int *)(param_2 + 0x3c));
      if (0.0 < local_38) {
        local_38 = local_38 - (float10)*(int *)(param_2 + 0x3c);
      }
    }
    iVar7 = roundfloat(*(float *)(param_2 + 0x18) -
                       (float)((*(int *)(iVar5 + 0xc) * 1000) / param_3));
    iVar8 = SpriteDecompGetAndLockData(*(int **)(param_1 + 0x28),*(int *)(param_2 + 0xf4));
    if (iVar8 != 0) {
      iVar9 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      piVar10 = SpriteArrayPalUpdateAndAccess(*(int *)(param_1 + 0x28),*(int *)(iVar5 + 0x30));
      iVar4 = W_y1;
      iVar3 = W_x2;
      iVar2 = W_x1;
      iVar8 = W_y2;
      local_30 = 0;
      if ((iVar7 <= W_y2) && (iVar11 = *(int *)(param_2 + 0x40), 0 < iVar11)) {
        iVar12 = V_Width / 2;
        do {
          if (iVar4 <= iVar7 + local_30) {
            if (*(int *)(param_2 + 0x88) == 0) {
              fVar1 = (((*(float *)(param_2 + 0x98) - 1.0) * (float)(local_44 + 1)) / (float10)iVar11
                      + 1.0) * local_38 + (float)(iVar12 - *(int *)(iVar5 + 8));
            }
            else {
              iVar11 = **(int **)(param_2 + 0x9c);
              fVar1 = ((float)(*(int **)(param_2 + 0x9c))[local_44] *
                      (local_38 - (float)(iVar11 / 2))) / (float10)iVar11 + (float10)iVar12;
            }
            local_18 = (int)GHIDRA_FIST32(fVar1);
            if (*(int *)(param_2 + 0x2c) == 0) {
              local_58 = *(int *)(param_2 + 0x9c);
            }
            else {
              local_58 = *(int *)(param_2 + 0x9c);
              iVar11 = *(int *)(local_58 + local_44 * 4);
              if ((local_18 < -iVar11) || (0 < local_18)) {
                local_18 = local_18 % iVar11;
              }
              if (0 < local_18) {
                local_18 = local_18 - *(int *)(local_58 + local_44 * 4);
              }
            }
            iVar13 = 0;
            iVar11 = local_18 + *(int *)(local_58 + local_44 * 4) + -1;
            if (local_18 < iVar2) {
              iVar13 = iVar2 - local_18;
              local_18 = iVar2;
            }
            if (iVar3 < iVar11) {
              iVar11 = iVar3;
            }
            local_5c = *(int *)(iVar6 + 0x2c);
            local_60 = *(int *)(param_2 + 0xa0);
            puVar15 = (undefined2 *)
                      (iVar9 + *(int *)(local_5c + (iVar7 + local_30) * 4) + local_18 * 2);
            pbVar14 = (byte *)(iVar13 + *(int *)(local_60 + local_44 * 4));
            iVar13 = (iVar11 - local_18) + 1;
            local_34 = iVar3;
            if (*(int *)(param_2 + 0x2c) == 0) {
              local_34 = iVar11;
            }
            if (local_18 <= local_34) {
              do {
                if (-1 < iVar13) {
                  local_18 = local_18 + iVar13;
                  if (iVar3 + 1 < local_18) {
                    iVar13 = (iVar3 - local_18) + 1 + iVar13;
                  }
                  if (iVar13 != 0) {
                    do {
                      if (*pbVar14 != 0) {
                        *puVar15 = *(undefined2 *)((int)piVar10 + (uint)*pbVar14 * 2 + 0x5c);
                      }
                      puVar15 = puVar15 + 1;
                      pbVar14 = pbVar14 + 1;
                      iVar13 = iVar13 + -1;
                    } while (iVar13 != 0);
                    local_58 = *(int *)(param_2 + 0x9c);
                    local_5c = *(int *)(iVar6 + 0x2c);
                    local_60 = *(int *)(param_2 + 0xa0);
                  }
                }
                pbVar14 = *(byte **)(local_60 + local_44 * 4);
                iVar13 = *(int *)(local_58 + local_44 * 4);
                puVar15 = (undefined2 *)
                          (iVar9 + *(int *)(local_5c + (iVar7 + local_30) * 4) + local_18 * 2);
              } while (local_18 <= local_34);
            }
          }
          for (local_40 = local_40 + param_3; 999 < local_40; local_40 = local_40 + -1000) {
            local_44 = local_44 + 1;
          }
          local_30 = local_30 + 1;
        } while ((iVar7 + local_30 <= iVar8) &&
                (iVar11 = *(int *)(param_2 + 0x40), local_44 < iVar11));
      }
      SpriteDecompUnlockData();
    }
  }
  return;
}

/* BGParalDraw8to16_2X @ 0x0804dfb0, 1 bytes */
void BGParalDraw8to16_2X(void)

{
  return;
}

/* BGParalDraw8to16Flat @ 0x0804dfc0, 1117 bytes
 * FIXUP: rewrote 1 Ghidra partial-variable accesses (x._O_S_)
 * FIXUP: 3 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 2 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void BGParalDraw8to16Flat(int param_1,int param_2,int param_3)

{
  float10 fVar1;
  float10 fVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int *piVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  undefined2 *puVar16;
  byte *pbVar17;
  int local_64;
  int local_60;
  int local_4c;
  int local_48;
  int local_38;
  int local_34;
  int local_30;
  int local_18;
  
  iVar7 = SpriteArrayAccess(*(int **)(param_1 + 0x28),*(int *)(param_2 + 0xf4));
  iVar8 = SpriteArrayAccess(V_Current,V_CurrentIdx);
  fVar1 = *(float *)(param_2 + 0x14);
  local_48 = 500;
  fVar2 = *(float *)(param_2 + 0x18);
  local_4c = 0;
  if ((iVar7 != 0) && (0 < param_3)) {
    iVar4 = *(int *)(iVar7 + 0xc);
    iVar9 = SpriteDecompGetAndLockData(*(int **)(param_1 + 0x28),*(int *)(param_2 + 0xf4));
    if (iVar9 != 0) {
      iVar10 = SpriteDecompGetData(V_Current,V_CurrentIdx);
      piVar11 = SpriteArrayPalUpdateAndAccess(*(int *)(param_1 + 0x28),*(int *)(iVar7 + 0x30));
      piVar11 = piVar11 + 0x17;
      iVar12 = roundfloat(fVar2 - (float)((iVar4 * 1000) / param_3));
      iVar6 = W_y1;
      iVar5 = W_x2;
      iVar9 = W_x1;
      iVar4 = W_y2;
      local_30 = 0;
      if ((iVar12 <= W_y2) && (iVar14 = *(int *)(param_2 + 0x40), 0 < iVar14)) {
        iVar13 = V_Width / 2;
        do {
          if (iVar6 <= iVar12 + local_30) {
            if (*(int *)(param_2 + 0x88) == 0) {
              fVar2 = (((*(float *)(param_2 + 0x98) - 1.0) * (float)(local_4c + 1)) / (float10)iVar14
                      + 1.0) * fVar1 + (float)(iVar13 - *(int *)(iVar7 + 8));
            }
            else {
              iVar14 = **(int **)(param_2 + 0x9c);
              fVar2 = ((float)(*(int **)(param_2 + 0x9c))[local_4c] * (fVar1 - (float)(iVar14 / 2)))
                      / (float10)iVar14 + (float10)iVar13;
            }
            local_18 = (int)GHIDRA_FIST32(fVar2);
            if (*(int *)(param_2 + 0x2c) == 0) {
              local_60 = *(int *)(param_2 + 0x9c);
            }
            else {
              local_60 = *(int *)(param_2 + 0x9c);
              iVar14 = *(int *)(local_60 + local_4c * 4);
              if ((local_18 < -iVar14) || (0 < local_18)) {
                local_18 = local_18 % iVar14;
              }
              if (0 < local_18) {
                local_18 = local_18 - *(int *)(local_60 + local_4c * 4);
              }
            }
            iVar14 = 0;
            local_34 = local_18 + *(int *)(local_60 + local_4c * 4) + -1;
            if (local_18 < iVar9) {
              iVar14 = iVar9 - local_18;
              local_18 = iVar9;
            }
            if (iVar5 < local_34) {
              local_34 = iVar5;
            }
            local_64 = *(int *)(iVar8 + 0x2c);
            puVar16 = (undefined2 *)
                      (iVar10 + *(int *)(local_64 + (iVar12 + local_30) * 4) + local_18 * 2);
            iVar15 = *(int *)(param_2 + 0xa0);
            pbVar17 = (byte *)(*(int *)(iVar15 + local_4c * 4) + iVar14);
            iVar14 = (local_34 - local_18) + 1;
            local_38 = iVar5;
            if (*(int *)(param_2 + 0x2c) == 0) {
              local_38 = local_34;
            }
            if (local_18 <= local_38) {
              do {
                if (-1 < iVar14) {
                  local_18 = local_18 + iVar14;
                  (*(uint *)((char *)&GlobalTemp + 0)) = piVar11;
                  if (iVar5 + 1 < local_18) {
                    iVar14 = (iVar5 - local_18) + 1 + iVar14;
                  }
                  for (; iVar14 != 0; iVar14 = iVar14 + -1) {
                    bVar3 = *pbVar17;
                    pbVar17 = pbVar17 + 1;
                    *puVar16 = *(undefined2 *)((int)piVar11 + (uint)bVar3 * 2);
                    puVar16 = puVar16 + 1;
                  }
                  local_60 = *(int *)(param_2 + 0x9c);
                  local_64 = *(int *)(iVar8 + 0x2c);
                  iVar15 = *(int *)(param_2 + 0xa0);
                }
                iVar14 = *(int *)(local_60 + local_4c * 4);
                pbVar17 = *(byte **)(iVar15 + local_4c * 4);
                puVar16 = (undefined2 *)
                          (iVar10 + *(int *)(local_64 + (iVar12 + local_30) * 4) + local_18 * 2);
              } while (local_18 <= local_38);
            }
          }
          for (local_48 = local_48 + param_3; 999 < local_48; local_48 = local_48 + -1000) {
            local_4c = local_4c + 1;
          }
          local_30 = local_30 + 1;
        } while ((iVar12 + local_30 <= iVar4) &&
                (iVar14 = *(int *)(param_2 + 0x40), local_4c < iVar14));
      }
      SpriteDecompUnlockData();
    }
  }
  return;
}

/* BGParalDraw8to16Flat2X @ 0x0804e420, 1 bytes */
void BGParalDraw8to16Flat2X(void)

{
  return;
}

/* BGParalDraw16 @ 0x0804e430, 1 bytes */
void BGParalDraw16(void)

{
  return;
}

