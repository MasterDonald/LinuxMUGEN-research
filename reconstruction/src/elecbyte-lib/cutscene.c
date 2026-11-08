/*
 * cutscene.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0804f9e0-0x08050cc8, 14 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* SceneReadFile @ 0x0804f9e0, 180 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x1010-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 * SceneReadFile(char *param_1,char *param_2,int param_3,int param_4)

{
  char *pcVar1;
  undefined4 *puVar2;
  unsigned char ghidra_frame[0x1010] __attribute__((aligned(16)));
#define local_100c (*(char (*)[4096])(ghidra_frame + 0x4))
  
  pcVar1 = TPReadFile(param_1);
  if (pcVar1 == (char *)0x0) {
    strcat((char *)ErrorMessage,"\nTXTPARSE error opening ");
    strcat((char *)ErrorMessage,param_1);
    puVar2 = (undefined4 *)0x0;
  }
  else {
    splitdirfile(param_1,local_100c,(char *)0x0);
    puVar2 = SceneReadTP(pcVar1,local_100c,param_2,param_3,param_4);
    if (puVar2 == (undefined4 *)0x0) {
      strcat((char *)ErrorMessage,"\nCutscene error reading ");
      strcat((char *)ErrorMessage,param_1);
    }
    TPFree((undefined4 *)pcVar1);
  }
  return puVar2;
}
#undef local_100c

/* SceneReadTP @ 0x0804faa0, 169 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x60-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 * SceneReadTP(char *param_1,char *param_2,char *param_3,int param_4,int param_5)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  unsigned char ghidra_frame[0x60] __attribute__((aligned(16)));
#define local_5c (*(char (*)[80])(ghidra_frame + 0x4))
  
  strcpy(local_5c,param_3);
  strcat(local_5c,"def");
  iVar1 = TPGroupSeek((int)param_1,local_5c);
  if (iVar1 == -1) {
    sprintf((char *)ErrorMessage,"Can\'t access group %s",local_5c,param_3);
  }
  else {
    puVar2 = (undefined4 *)ecalloc(1,8);
    if (puVar2 == (undefined4 *)0x0) {
      return (undefined4 *)0x0;
    }
    *puVar2 = 0;
    piVar3 = SiSceneReadTP(param_1,param_2,param_3,param_4,param_5);
    puVar2[1] = piVar3;
    if (piVar3 != (int *)0x0) {
      return puVar2;
    }
    SceneFree(puVar2);
  }
  return (undefined4 *)0x0;
}
#undef local_5c

/* SiSceneReadTP @ 0x0804fb50, 2140 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 38 stack locals placed at their original offsets in a 0x1370-byte frame (a local's address escapes, see apply_frame_emulation) */
int * SiSceneReadTP(char *param_1,char *param_2,char *param_3,int param_4,int param_5)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  char *pcVar4;
  int *piVar5;
  size_t sVar6;
  int iVar7;
  undefined4 *puVar8;
  char *pcVar9;
  char *pcVar10;
  undefined3 extraout_var;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar11;
  undefined4 extraout_ECX_01;
  char *extraout_EDX;
  char *extraout_EDX_00;
  size_t sVar12;
  int iVar13;
  char *pcVar14;
  unsigned char ghidra_frame[0x1370] __attribute__((aligned(16)));
#define local_1368 (*(int *)(ghidra_frame + 0x8))
#define local_1364 (*(int *)(ghidra_frame + 0xc))
#define local_135c (*(char (*)[48])(ghidra_frame + 0x14))
#define local_132c (*(char (*)[48])(ghidra_frame + 0x44))
#define local_12fc (*(char (*)[4096])(ghidra_frame + 0x74))
#define local_2fc (*(undefined4 (*)[38])(ghidra_frame + 0x1074))
#define local_264 (*(undefined4 *)(ghidra_frame + 0x110c))
#define local_260 (*(undefined4 *)(ghidra_frame + 0x1110))
#define local_25c (*(undefined4 *)(ghidra_frame + 0x1114))
#define local_258 (*(undefined4 *)(ghidra_frame + 0x1118))
#define local_254 (*(int *)(ghidra_frame + 0x111c))
#define local_250 (*(undefined4 *)(ghidra_frame + 0x1120))
#define local_24c (*(int *)(ghidra_frame + 0x1124))
#define local_248 (*(undefined4 *)(ghidra_frame + 0x1128))
#define local_1a0 (*(undefined4 *)(ghidra_frame + 0x11d0))
#define local_19c (*(undefined4 *)(ghidra_frame + 0x11d4))
#define local_18c (*(char (*)[128])(ghidra_frame + 0x11e4))
#define local_10c (*(uint (*)[3])(ghidra_frame + 0x1264))
#define local_100 (*(uint *)(ghidra_frame + 0x1270))
#define local_fc (*(uint *)(ghidra_frame + 0x1274))
#define local_f8 (*(uint *)(ghidra_frame + 0x1278))
#define local_f4 (*(undefined4 *)(ghidra_frame + 0x127c))
#define local_f0 (*(undefined4 *)(ghidra_frame + 0x1280))
#define local_ec (*(undefined4 *)(ghidra_frame + 0x1284))
#define local_e8 (*(undefined4 *)(ghidra_frame + 0x1288))
#define local_e4 (*(int *)(ghidra_frame + 0x128c))
#define local_e0 (*(undefined4 *)(ghidra_frame + 0x1290))
#define local_dc (*(int *)(ghidra_frame + 0x1294))
#define local_d8 (*(undefined4 *)(ghidra_frame + 0x1298))
#define local_d4 (*(char **)(ghidra_frame + 0x129c))
#define uStack_d0 (*(uint *)(ghidra_frame + 0x12a0))
#define auStack_cc (*(undefined1 (*)[4])(ghidra_frame + 0x12a4))
#define auStack_c8 (*(undefined1 (*)[4])(ghidra_frame + 0x12a8))
#define auStack_c4 (*(uint (*)[33])(ghidra_frame + 0x12ac))
#define local_40 (*(undefined4 (*)[4])(ghidra_frame + 0x1330))
#define local_30 (*(undefined4 *)(ghidra_frame + 0x1340))
#define local_2c (*(undefined4 *)(ghidra_frame + 0x1344))
#define local_28 (*(uint (*)[6])(ghidra_frame + 0x1348))
  
  pcVar9 = local_12fc;
  strcpy(pcVar9,param_3);
  strcat(pcVar9,"def");
  iVar2 = TPGroupSeek((int)param_1,pcVar9);
  if (iVar2 == -1) {
    sprintf((char *)ErrorMessage,"Can\'t access group %s",pcVar9,extraout_ECX);
    return (int *)0x0;
  }
  piVar3 = (int *)ecalloc(1,0x10e8);
  if (piVar3 == (int *)0x0) {
    return (int *)0x0;
  }
  strcpy((char *)(piVar3 + 6),param_2);
  iVar2 = TPGroupSeek((int)param_1,pcVar9);
  if (iVar2 == -1) {
    sprintf((char *)ErrorMessage,"Can\'t access group %s",pcVar9,param_4);
  }
  else {
    pcVar4 = TPGetValue((int)param_1,"spr");
    if (pcVar4 == (char *)0x0) {
      if (param_4 == 0) {
        memcpy(ErrorMessage,"Error: sff file must be specified",0x22);
        goto LAB_0804fe88;
      }
      piVar3[2] = param_4;
      piVar3[3] = 0;
    }
    else {
      joindirfile(pcVar9,param_2,pcVar4);
      piVar5 = SpriteReadFile(pcVar9);
      piVar3[2] = (int)piVar5;
      if (piVar5 == (int *)0x0) {
        sprintf((char *)ErrorMessage,"Error reading sprite %s",pcVar4,pcVar9);
        goto LAB_0804fe88;
      }
      piVar3[3] = 1;
    }
    TPGetValueInt((int)param_1,"startscene",(uint *)(piVar3 + 0x439));
    if (param_5 == 0) {
      iVar2 = TPGroupScanFirst((int)param_1);
      pcVar4 = extraout_EDX;
      do {
        iVar7 = strimatch((char *)(iVar2 + 1),"begin action ");
        pcVar9 = pcVar4;
        if (iVar7 != 0) break;
        iVar2 = TPGroupScanNext((int)param_1);
        pcVar4 = extraout_EDX_00;
      } while (iVar2 != 0);
      if (iVar2 != 0) {
        piVar5 = AnimRCReadFileTP((int)param_1);
        piVar3[4] = (int)piVar5;
        if (piVar5 == (int *)0x0) {
          strcat((char *)ErrorMessage,"\nError loading anim.");
          goto LAB_0804fe88;
        }
        piVar3[5] = 1;
      }
    }
    else {
      piVar3[4] = param_5;
      piVar3[5] = 0;
    }
    sVar6 = strlen(param_3);
    sprintf(local_132c,"%s ",param_3,pcVar9);
    pcVar9 = local_135c;
    sprintf(local_135c,"%s]",param_3);
    iVar2 = TPGroupMatchCount((int)param_1,local_132c);
    iVar7 = TPGroupMatchCount((int)param_1,local_135c);
    sVar12 = iVar2 + iVar7;
    if (sVar12 == 0) {
      sprintf((char *)ErrorMessage,"Need at least one [%s] type act",param_3,pcVar9);
    }
    else {
      piVar3[1] = sVar12;
      puVar8 = ArrayNew(sVar12,0x168,0);
      *piVar3 = (int)puVar8;
      if (puVar8 != (undefined4 *)0x0) {
        local_1364 = TPGroupScanFirst((int)param_1);
        local_1368 = 0;
        if (0 < (int)sVar12) {
          do {
            while ((*(int *)(param_1 + 0x18) != *(int *)(param_1 + 0x2c) &&
                   ((iVar2 = strimatch((char *)(local_1364 + 1),param_3), iVar2 == 0 ||
                    (((*(byte *)(__ctype_b + 1 + *(char *)(sVar6 + 1 + local_1364) * 2) & 0x20) == 0
                     && (*(char *)(sVar6 + 1 + local_1364) != ']'))))))) {
              local_1364 = TPGroupScanNext((int)param_1);
            }
            if (0 < local_1368) {
              pcVar9 = local_18c;
              puVar8 = local_2fc;
              for (iVar2 = 0x5a; iVar2 != 0; iVar2 = iVar2 + -1) {
                *puVar8 = *(undefined4 *)pcVar9;
                pcVar9 = pcVar9 + 4;
                puVar8 = puVar8 + 1;
              }
            }
            pcVar9 = local_18c;
            for (iVar2 = 0x5a; iVar2 != 0; iVar2 = iVar2 + -1) {
              pcVar9[0] = '\0';
              pcVar9[1] = '\0';
              pcVar9[2] = '\0';
              pcVar9[3] = '\0';
              pcVar9 = pcVar9 + 4;
            }
            iVar2 = 9;
            puVar8 = local_40;
            do {
              *puVar8 = 0xffffffff;
              puVar8 = puVar8 + -4;
              iVar2 = iVar2 + -1;
            } while (-1 < iVar2);
            local_10c[0] = 1;
            if (local_1368 == 0) {
              local_f4 = 0xffffffff;
            }
            else {
              local_f4 = local_264;
              local_f0 = local_260;
              local_ec = local_25c;
              local_e4 = local_254;
              local_e0 = local_250;
              local_dc = local_24c;
              local_d8 = local_248;
              local_e8 = local_258;
              local_30 = local_1a0;
              local_2c = local_19c;
            }
            pcVar9 = TPGetValue((int)param_1,"bgm");
            if (pcVar9 != (char *)0x0) {
              local_10c[1] = 1;
              strncpy(local_18c,pcVar9,0x7f);
            }
            TPGetValueInt((int)param_1,"bgm.loop",local_10c);
            TPGetValueInt((int)param_1,"fadein.time",local_10c + 2);
            TPGetValueInt((int)param_1,"fadein.col",&local_100);
            TPGetValueInt((int)param_1,"fadeout.time",&local_fc);
            TPGetValueInt((int)param_1,"fadeout.col",&local_f8);
            TPScanf((int)param_1,"clearcolor","%i,%i,%i",&local_f4,&local_f0,&local_ec);
            iVar2 = TPScanf((int)param_1,"window","%i,%i,%i,%i",&local_e4,&local_e0,&local_dc,
                            &local_d8);
            if (iVar2 == 4) {
              local_e8 = 1;
            }
            if ((local_e4 == -1) || (local_dc < local_e4)) {
              local_e8 = 0;
            }
            pcVar9 = "bg.name";
            pcVar4 = param_1;
            pcVar14 = param_1;
            pcVar10 = TPGetValue((int)param_1,"bg.name");
            if ((pcVar10 != (char *)0x0) && (*pcVar10 != '\0')) {
              pcVar9 = *(char **)(param_1 + 0x18);
              local_d4 = BGArrayReadTP(param_1,param_2,pcVar10,piVar3[2],piVar3[4]);
              if (local_d4 == (char *)0x0) goto LAB_0804fe88;
              pcVar4 = param_1;
              pcVar14 = param_1;
              TPGroupSeekIdx((int)param_1,(int)pcVar9);
            }
            TPScanf((int)param_1,"layerall.pos","%i,%i",&local_30,&local_2c,pcVar9,pcVar4,pcVar14);
            uVar11 = extraout_ECX_00;
            iVar2 = 0;
            do {
              sprintf(local_12fc,"layer%i.anim",iVar2,uVar11);
              TPGetValueInt((int)param_1,local_12fc,&uStack_d0 + iVar2 * 4);
              sprintf(local_12fc,"layer%i.offset",iVar2);
              TPScanf((int)param_1,local_12fc,"%i,%i",auStack_cc + iVar2 * 0x10,
                      auStack_c8 + iVar2 * 0x10);
              iVar7 = iVar2 + 1;
              sprintf(local_12fc,"layer%i.starttime",iVar2);
              TPGetValueInt((int)param_1,local_12fc,auStack_c4 + iVar2 * 4);
              uVar11 = extraout_ECX_01;
              iVar2 = iVar7;
            } while (iVar7 < 10);
            bVar1 = TPGetValueInt((int)param_1,"end.time",local_28);
            if (GHIDRA_ZEXT8(bVar1) == 0) {
              sprintf((char *)ErrorMessage,"\nIn %s: end.time not specified.",local_1364,local_18c);
              goto LAB_0804fe88;
            }
            ArrayAdd(*piVar3,local_18c,0,local_1368);
            local_1364 = TPGroupScanNext((int)param_1);
            local_1368 = local_1368 + 1;
          } while (local_1368 < (int)sVar12);
        }
        iVar2 = 0;
        local_1368 = 0;
        do {
          iVar13 = 0;
          iVar7 = iVar2 + 0x1010;
          do {
            puVar8 = AnimNew(piVar3[4],piVar3[2]);
            *(undefined4 **)((int)piVar3 + iVar7 + 0xc) = puVar8;
            if (puVar8 == (undefined4 *)0x0) goto LAB_0804fe88;
            iVar13 = iVar13 + 1;
            iVar7 = iVar7 + 4;
          } while (iVar13 < 10);
          iVar2 = iVar2 + 0x60;
          local_1368 = local_1368 + 1;
          if (1 < local_1368) {
            SiSceneReset((int)piVar3);
            return piVar3;
          }
        } while( true );
      }
    }
  }
LAB_0804fe88:
  SiSceneFree(piVar3);
  return (int *)0x0;
}
#undef local_1368
#undef local_1364
#undef local_135c
#undef local_132c
#undef local_12fc
#undef local_2fc
#undef local_264
#undef local_260
#undef local_25c
#undef local_258
#undef local_254
#undef local_250
#undef local_24c
#undef local_248
#undef local_1a0
#undef local_19c
#undef local_18c
#undef local_10c
#undef local_100
#undef local_fc
#undef local_f8
#undef local_f4
#undef local_f0
#undef local_ec
#undef local_e8
#undef local_e4
#undef local_e0
#undef local_dc
#undef local_d8
#undef local_d4
#undef uStack_d0
#undef auStack_cc
#undef auStack_c8
#undef auStack_c4
#undef local_40
#undef local_30
#undef local_2c
#undef local_28

/* SceneRegisterBGMFn @ 0x080503b0, 34 bytes */
void SceneRegisterBGMFn(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  if (*param_1 == 0) {
    iVar1 = param_1[1];
    *(undefined4 *)(iVar1 + 0x10d8) = param_2;
    *(undefined4 *)(iVar1 + 0x10dc) = param_3;
  }
  return;
}

/* SceneReset @ 0x080503e0, 36 bytes */
void SceneReset(int *param_1)

{
  if (*param_1 == 0) {
    SiSceneReset(param_1[1]);
    return;
  }
  return;
}

/* SiSceneReset @ 0x08050410, 149 bytes */
void SiSceneReset(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar4 = 0;
  iVar6 = 0x1010;
  iVar3 = 0x1060;
  iVar5 = param_1;
  do {
    iVar2 = 9;
    puVar1 = (undefined4 *)(iVar5 + 0x1068);
    do {
      *puVar1 = 0;
      puVar1 = puVar1 + -1;
      iVar2 = iVar2 + -1;
    } while (-1 < iVar2);
    *(undefined4 *)(iVar3 + 0x10 + param_1) = 0;
    *(undefined4 *)(param_1 + 0xc + iVar3) = 0;
    iVar4 = iVar4 + 1;
    *(undefined4 *)(param_1 + 0x14 + iVar3) = *(undefined4 *)(param_1 + 0x10e4);
    iVar3 = iVar3 + 0x60;
    *(undefined4 *)(iVar6 + 8 + param_1) = 0;
    iVar5 = iVar5 + 0x60;
    iVar6 = iVar6 + 0x60;
  } while (iVar4 < 2);
  *(undefined4 *)(param_1 + 0x1018) = 1;
  if ((*(code **)(param_1 + 0x10dc) != (code *)0x0) && (*(int *)(param_1 + 0x10e0) != 0)) {
    (**(code **)(param_1 + 0x10dc))();
  }
  return;
}

/* SceneUpdate @ 0x080504b0, 41 bytes */
undefined4 SceneUpdate(int *param_1)

{
  undefined4 uVar1;
  
  if (*param_1 == 0) {
    uVar1 = SiSceneUpdate((int *)param_1[1]);
    return uVar1;
  }
  return 1;
}

/* SiSceneUpdate @ 0x080504e0, 838 bytes
 * FIXUP: frame emulation: 7 stack locals placed at their original offsets in a 0x1040-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 SiSceneUpdate(int *param_1)

{
  char *pcVar1;
  int *piVar2;
  undefined4 uVar3;
  int iVar4;
  int extraout_ECX;
  int extraout_ECX_00;
  int *piVar5;
  int iVar6;
  char *pcVar7;
  unsigned char ghidra_frame[0x1040] __attribute__((aligned(16)));
#define local_1038 (*(int **)(ghidra_frame + 0x8))
#define local_1034 (*(int **)(ghidra_frame + 0xc))
#define local_1030 (*(int **)(ghidra_frame + 0x10))
#define local_102c (*(int *)(ghidra_frame + 0x14))
#define local_1028 (*(int *)(ghidra_frame + 0x18))
#define local_1024 (*(int (*)[2])(ghidra_frame + 0x1c))
#define local_101c (*(char (*)[4108])(ghidra_frame + 0x24))
  
  local_1024[0] = 0;
  local_1024[1] = 0;
  do {
    if (((param_1[0x406] == 0) || (local_1024[0] != 0)) &&
       ((param_1[0x41e] == 0 || (local_1024[1] != 0)))) {
      iVar4 = 0x1060;
      local_1028 = 1;
      do {
        *(int *)((int)param_1 + iVar4 + 0x10) = *(int *)((int)param_1 + iVar4 + 0x10) + 1;
        iVar4 = iVar4 + 0x60;
        local_1028 = local_1028 + -1;
      } while (-1 < local_1028);
      return 0;
    }
    local_1034 = param_1 + 0x407;
    local_1038 = param_1 + 0x406;
    local_1028 = 0;
    piVar5 = param_1 + 0x409;
    local_1030 = local_1034;
    do {
      if (piVar5[-3] != 0) {
        pcVar1 = (char *)ArrayAccessGrpItem(*param_1,0,piVar5[0x14]);
        if ((*(int *)(pcVar1 + 0x164) <= piVar5[0x12]) && (*(int *)(pcVar1 + 0x164) != -1)) {
          iVar4 = piVar5[0x14] + 1;
          piVar5[0x14] = iVar4;
          if (param_1[1] <= iVar4) {
            return 1;
          }
          pcVar1 = (char *)ArrayAccessGrpItem(*param_1,0,iVar4);
          piVar5[0x12] = 0;
        }
        if (piVar5[0x12] == 0) {
          iVar4 = param_1[4];
          if (iVar4 != 0) {
            iVar6 = 9;
            piVar2 = local_1038 + 0x14;
            do {
              *piVar2 = 0;
              piVar2 = piVar2 + -1;
              iVar6 = iVar6 + -1;
            } while (-1 < iVar6);
          }
          if (*(int *)(pcVar1 + 0xb8) != 0) {
            BGArrayReset(*(int *)(pcVar1 + 0xb8));
            iVar4 = extraout_ECX;
          }
          if ((((code *)param_1[0x437] != (code *)0x0) && (param_1[0x438] != 0)) &&
             (*(int *)(pcVar1 + 0x84) != 0)) {
            (*(code *)param_1[0x437])();
            param_1[0x438] = 0;
            iVar4 = extraout_ECX_00;
          }
          if ((param_1[0x436] != 0) && (*pcVar1 != '\0')) {
            pcVar7 = pcVar1;
            joindirfile(local_101c,(char *)(param_1 + 6),pcVar1);
            (*(code *)param_1[0x436])(local_101c,*(undefined4 *)(pcVar1 + 0x80),pcVar7,iVar4);
            param_1[0x438] = 1;
          }
        }
        iVar4 = 0;
        if (param_1[4] != 0) {
          iVar4 = 0xb0;
          local_102c = 0x20;
          iVar6 = 0;
          do {
            if ((-1 < *(int *)(pcVar1 + iVar4 + 0xc)) &&
               (*(int *)(pcVar1 + iVar4 + 0x18) == piVar5[0x12])) {
              uVar3 = AnimChangeAction((int *)local_1034[iVar6],0,*(int *)(pcVar1 + iVar4 + 0xc));
              *(undefined4 *)(local_102c + (int)piVar5) = uVar3;
            }
            iVar6 = iVar6 + 1;
            local_102c = local_102c + 4;
            iVar4 = iVar4 + 0x10;
          } while (iVar6 < 10);
          iVar4 = param_1[4];
        }
        if (iVar4 != 0) {
          iVar4 = 0;
          iVar6 = 9;
          do {
            if (*(int *)((int)local_1038 + iVar4 + 0x2c) != 0) {
              AnimUpdate(*(undefined4 **)(iVar4 + (int)local_1030));
            }
            iVar4 = iVar4 + 4;
            iVar6 = iVar6 + -1;
          } while (-1 < iVar6);
        }
        if (*(int *)(pcVar1 + 0xb8) != 0) {
          BGArrayUpdate(*(int *)(pcVar1 + 0xb8));
          BGArrayMove(*(int **)(pcVar1 + 0xb8),0.0,0.0);
        }
        iVar4 = piVar5[0x12];
        piVar5[0x12] = iVar4 + 1;
        if (((*(int *)(pcVar1 + 0x164) <= iVar4 + 1) && (*(int *)(pcVar1 + 0x164) != -1)) &&
           (param_1[1] <= piVar5[0x14] + 1)) {
          return 1;
        }
        local_1024[local_1028] = 1;
      }
      local_1028 = local_1028 + 1;
      local_1030 = local_1030 + 0x18;
      local_1034 = local_1034 + 0x18;
      local_1038 = local_1038 + 0x18;
      piVar5 = piVar5 + 0x18;
    } while (local_1028 < 2);
  } while( true );
}
#undef local_1038
#undef local_1034
#undef local_1030
#undef local_102c
#undef local_1028
#undef local_1024
#undef local_101c

/* SceneUpdatePal @ 0x08050830, 36 bytes */
void SceneUpdatePal(int *param_1)

{
  if (*param_1 == 0) {
    SiSceneUpdatePal((int *)param_1[1]);
    return;
  }
  return;
}

/* SiSceneUpdatePal @ 0x08050860, 271 bytes
 * REVIEW: pid-unaff_ */
void SiSceneUpdatePal(int *param_1)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int unaff_EBX;
  int *piVar5;
  int local_14;
  
  local_14 = 1;
  piVar5 = param_1;
  do {
    if (piVar5[0x406] != 0) {
      bVar2 = false;
      iVar3 = ArrayAccessGrpItem(*param_1,0,piVar5[0x41d]);
      iVar1 = *(int *)(iVar3 + 0x88);
      if (piVar5[0x41b] + -1 <= iVar1) {
        if (iVar1 < 1) {
          unaff_EBX = 0x100;
        }
        else {
          unaff_EBX = ((piVar5[0x41b] + -1) * 0x100) / iVar1;
          if (0x7f < *(int *)(iVar3 + 0x8c)) {
            unaff_EBX = 0x200 - unaff_EBX;
          }
        }
        bVar2 = true;
      }
      iVar1 = *(int *)(iVar3 + 0x90);
      iVar4 = *(int *)(iVar3 + 0x164) - piVar5[0x41b];
      if ((iVar4 < iVar1) && (0 < iVar1)) {
        unaff_EBX = (iVar4 * 0x100) / iVar1;
        if (0x7f < *(int *)(iVar3 + 0x94)) {
          unaff_EBX = 0x200 - unaff_EBX;
        }
        bVar2 = true;
      }
      if (bVar2) {
        if (unaff_EBX < 0x101) {
          MasterPalMul(unaff_EBX,unaff_EBX,unaff_EBX);
        }
        else {
          iVar1 = unaff_EBX + -0x100;
          MasterPalAdd(iVar1,iVar1,iVar1);
        }
      }
    }
    piVar5 = piVar5 + 0x18;
    local_14 = local_14 + -1;
  } while (-1 < local_14);
  return;
}

/* SceneDraw @ 0x08050970, 36 bytes */
void SceneDraw(int *param_1)

{
  if (*param_1 == 0) {
    SiSceneDraw((int *)param_1[1]);
    return;
  }
  return;
}

/* SiSceneDraw @ 0x080509a0, 480 bytes */
void SiSceneDraw(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *local_30;
  int *local_2c;
  int *local_28;
  int local_24;
  
  iVar4 = W_y1;
  iVar3 = W_x2;
  iVar2 = W_x1;
  iVar1 = W_y2;
  local_28 = param_1 + 0x407;
  local_2c = param_1 + 0x409;
  local_30 = param_1 + 0x406;
  local_24 = 1;
  do {
    if (*local_30 != 0) {
      iVar5 = ArrayAccessGrpItem(*param_1,0,local_30[0x17]);
      if (*(int *)(iVar5 + 0x98) != -1) {
        uVar6 = makecol(*(undefined4 *)(iVar5 + 0x98),*(int *)(iVar5 + 0x9c),*(int *)(iVar5 + 0xa0))
        ;
        W_Cls(uVar6);
      }
      if (*(int *)(iVar5 + 0xa4) != 0) {
        W_Define(*(uint *)(iVar5 + 0xa8),*(uint *)(iVar5 + 0xac),*(uint *)(iVar5 + 0xb0),
                 *(uint *)(iVar5 + 0xb4));
      }
      if (*(int *)(iVar5 + 0xb8) != 0) {
        BGArrayDrawLayer(*(int *)(iVar5 + 0xb8),0);
      }
      if (param_1[4] != 0) {
        iVar9 = 0;
        iVar7 = 0x20;
        iVar8 = 0xb0;
        do {
          if (*(int *)(iVar7 + (int)local_2c) != 0) {
            AnimDraw((undefined4 *)local_28[iVar9],
                     *(int *)(iVar5 + 0x10 + iVar8) + *(int *)(iVar5 + 0x15c),
                     *(int *)(iVar5 + 0x14 + iVar8) + *(int *)(iVar5 + 0x160));
          }
          iVar9 = iVar9 + 1;
          iVar8 = iVar8 + 0x10;
          iVar7 = iVar7 + 4;
        } while (iVar9 < 10);
      }
      if (*(int *)(iVar5 + 0xb8) != 0) {
        BGArrayDrawLayer(*(int *)(iVar5 + 0xb8),1);
      }
      if (*(int *)(iVar5 + 0xa4) != 0) {
        W_Define(iVar2,iVar4,iVar3,iVar1);
      }
    }
    local_28 = local_28 + 0x18;
    local_2c = local_2c + 0x18;
    local_30 = local_30 + 0x18;
    local_24 = local_24 + -1;
  } while (-1 < local_24);
  return;
}

/* SceneFree @ 0x08050b80, 71 bytes
 * REVIEW: pid-unaff_
 * FIXUP: return type set to void: only unaffected-register values were returned */
void SceneFree(void *param_1)

{
  int iVar1;
  undefined4 extraout_EAX;
  undefined4 unaff_EBX;
  
  if (param_1 != (void *)0x0) {
    iVar1 = *(int *)((int)param_1 + 4);
    if (iVar1 != 0) {
      if ((*(code **)(iVar1 + 0x10dc) != (code *)0x0) && (*(int *)(iVar1 + 0x10e0) != 0)) {
        (**(code **)(iVar1 + 0x10dc))();
      }
      SiSceneFree(*(int **)((int)param_1 + 4));
    }
    free(param_1);
    return;
  }
  return;
}

/* SiSceneFree @ 0x08050bd0, 248 bytes
 * FIXUP: hand-written override (see overrides/) */
/* OVERRIDE: written by hand from the assembly at 0x08050bd0-0x08050cc8.
 * Reason: same loop shape as BGArrayFree (entry jump into the middle of the
 * scan loop at 0x8050bf2 -> 0x8050c17); Ghidra lost the stack depth.
 * Layout (VERIFIED in the listing):
 *   s[0] (0x00) Array of scenes; each scene has a BG array at +0xb8
 *   0x08 sprites, freed if 0x0c != 0;  0x10 anim RC, freed if 0x14 != 0
 *   0x101c + i*0x60 + k*4 (i = 0..1, k = 0..9) animations
 *   (address = s + 0xc + 0x1010 + i*0x60 + k*4; the loop counts k down from 9)
 * Ends with a tail call to free(s). */
undefined4 SiSceneFree(int *param_1)
{
  int arr, i, k, scene;

  if (param_1 == 0)
    return 0;
  arr = param_1[0];
  scene = arr ? ArrayScanFirst(arr) : 0;                       /* 0x8050bed */
  while (scene != 0) {
    if (*(int *)(scene + 0xb8) != 0)
      BGArrayFree(*(int *)(scene + 0xb8));                     /* 0x8050c06 */
    scene = ArrayScanNext(arr);                                /* 0x8050c12 */
  }
  ArrayFree((void *)param_1[0]);
  for (i = 0; i <= 1; i++)
    for (k = 0; k < 10; k++) {
      void *a = *(void **)((char *)param_1 + 0x101c + i * 0x60 + k * 4);
      if (a != 0)
        AnimFree(a);
    }
  if (param_1[5] != 0)                                         /* 0x14 */
    AnimRCFree((int *)param_1[4]);                             /* 0x10 */
  if (param_1[3] != 0)                                         /* 0x0c */
    SpriteArrayFree((int *)param_1[2]);                        /* 0x08 */
  free(param_1);                                               /* tail call 0x8050cbb */
  return 0;
}

