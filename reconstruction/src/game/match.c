/*
 * match.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0809dc50-0x0809fd6b, 14 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* GameLoadStage @ 0x0809dc50, 2522 bytes
 * FIXUP: 20 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 6 stack locals placed at their original offsets in a 0x130-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 GameLoadStage(void)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  bool bVar10;
  bool bVar11;
  bool bVar12;
  uint *puVar13;
  undefined4 *puVar14;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  undefined3 extraout_var_07;
  undefined3 extraout_var_08;
  undefined3 extraout_var_09;
  undefined3 extraout_var_10;
  undefined3 extraout_var_11;
  undefined3 extraout_var_12;
  undefined3 extraout_var_13;
  undefined3 extraout_var_14;
  undefined3 extraout_var_15;
  undefined3 extraout_var_16;
  byte *pbVar15;
  undefined3 extraout_var_17;
  int *piVar16;
  int *piVar17;
  uint uVar18;
  int iVar19;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_ECX_02;
  int iVar20;
  int iVar21;
  uint *puVar22;
  int iVar23;
  unsigned char ghidra_frame[0x130] __attribute__((aligned(16)));
#define local_128 (*(int *)(ghidra_frame + 0x8))
#define local_124 (*(int *)(ghidra_frame + 0xc))
#define local_120 (*(int *)(ghidra_frame + 0x10))
#define local_11c (*(PalGrpFlag *)(ghidra_frame + 0x14))
#define local_fc (*(PalGrpFlag *)(ghidra_frame + 0x34))
#define local_dc (*(char (*)[204])(ghidra_frame + 0x54))
  
  piVar16 = g;
  puVar13 = (uint *)(g + 0x107f);
  local_128 = 0;
  local_124 = 0;
  local_120 = 0;
  puVar22 = puVar13;
  for (iVar19 = 0x435; iVar19 != 0; iVar19 = iVar19 + -1) {
    *puVar22 = 0;
    puVar22 = puVar22 + 1;
  }
  strcpy(local_dc,(char *)(g + 0x805));
  puVar14 = TPReadFile(local_dc);
  if (puVar14 == (undefined4 *)0x0) {
    sprintf((char *)(g + 0x81d2),"Can\'t open stage: %s",local_dc);
  }
  else {
    iVar19 = TPGroupSeek((int)puVar14,"Camera");
    if (iVar19 == -1) {
      sprintf((char *)(g + 0x81d2),"Missing camera info: %s",local_dc,0);
    }
    else {
      piVar16[0x1088] = 0;
      piVar16[0x1087] = 0x32;
      piVar16[0x1084] = -0x19;
      piVar16[0x1085] = 0;
      piVar16[0x1081] = 0;
      piVar16[0x1080] = 0;
      piVar16[0x1082] = -0x4b;
      piVar16[0x1083] = 0x4b;
      piVar16[0x1086] = 0x3e4ccccd;
      TPGetValueInt((int)puVar14,"boundleft",(uint *)(piVar16 + 0x1082));
      TPGetValueInt((int)puVar14,"boundright",(uint *)(piVar16 + 0x1083));
      TPGetValueInt((int)puVar14,"startx",(uint *)(piVar16 + 0x1080));
      TPGetValueInt((int)puVar14,"starty",(uint *)(piVar16 + 0x1081));
      TPGetValueInt((int)puVar14,"tension",(uint *)(piVar16 + 0x1087));
      TPGetValueInt((int)puVar14,"floortension",(uint *)(piVar16 + 0x1088));
      TPGetValueInt((int)puVar14,"boundhigh",(uint *)(piVar16 + 0x1084));
      TPGetValueInt((int)puVar14,"boundlow",(uint *)(piVar16 + 0x1085));
      TPGetValueFloat((int)puVar14,"verticalfollow",(float *)(piVar16 + 0x1086));
      iVar19 = TPGroupSeek((int)puVar14,"PlayerInfo");
      if (iVar19 == -1) {
        sprintf((char *)(g + 0x81d2),"Missing player info: %s",local_dc,extraout_ECX);
      }
      else {
        bVar1 = TPGetValueInt((int)puVar14,"p1startx",(uint *)(piVar16 + 0x1089));
        bVar2 = TPGetValueInt((int)puVar14,"p1starty",(uint *)(piVar16 + 0x108d));
        bVar3 = TPGetValueInt((int)puVar14,"p1startz",(uint *)(piVar16 + 0x1091));
        bVar4 = TPGetValueInt((int)puVar14,"p1facing",(uint *)(piVar16 + 0x1095));
        bVar5 = TPGetValueInt((int)puVar14,"p2startx",(uint *)(piVar16 + 0x108a));
        bVar6 = TPGetValueInt((int)puVar14,"p2starty",(uint *)(piVar16 + 0x108e));
        bVar7 = TPGetValueInt((int)puVar14,"p2startz",(uint *)(piVar16 + 0x1092));
        bVar8 = TPGetValueInt((int)puVar14,"p2facing",(uint *)(piVar16 + 0x1096));
        bVar9 = TPGetValueInt((int)puVar14,"leftbound",(uint *)(piVar16 + 0x1099));
        bVar10 = TPGetValueInt((int)puVar14,"rightbound",(uint *)(piVar16 + 0x109a));
        bVar11 = TPGetValueInt((int)puVar14,"topbound",(uint *)(piVar16 + 0x109b));
        bVar12 = TPGetValueInt((int)puVar14,"botbound",(uint *)(piVar16 + 0x109c));
        if ((GHIDRA_ZEXT8(bVar1) & GHIDRA_ZEXT8(bVar2) &
             GHIDRA_ZEXT8(bVar3) & GHIDRA_ZEXT8(bVar4) &
             GHIDRA_ZEXT8(bVar5) & GHIDRA_ZEXT8(bVar6) &
             GHIDRA_ZEXT8(bVar7) & GHIDRA_ZEXT8(bVar8) &
             GHIDRA_ZEXT8(bVar9) & GHIDRA_ZEXT8(bVar10) &
             GHIDRA_ZEXT8(bVar11) & GHIDRA_ZEXT8(bVar12)) == 1) {
          piVar16[0x108b] = piVar16[0x1089] + -0x19;
          piVar16[0x108f] = piVar16[0x108d];
          piVar16[0x1093] = piVar16[0x1091];
          piVar16[0x1097] = piVar16[0x1095];
          piVar16[0x108c] = piVar16[0x108a] + 0x19;
          piVar16[0x1090] = piVar16[0x108e];
          piVar16[0x1094] = piVar16[0x1092];
          piVar16[0x1098] = piVar16[0x1096];
          iVar19 = TPGroupSeek((int)puVar14,"Scaling");
          if (iVar19 == -1) {
            sprintf((char *)(g + 0x81d2),"Missing scaling info: %s",local_dc,extraout_ECX_00);
          }
          else {
            bVar1 = TPGetValueInt((int)puVar14,"topz",(uint *)(piVar16 + 0x109e));
            bVar2 = TPGetValueInt((int)puVar14,"botz",(uint *)(piVar16 + 0x109f));
            bVar3 = TPGetValueFloat((int)puVar14,"topscale",(float *)(piVar16 + 0x10a0));
            bVar4 = TPGetValueFloat((int)puVar14,"botscale",(float *)(piVar16 + 0x10a1));
            if ((GHIDRA_ZEXT8(bVar1) & GHIDRA_ZEXT8(bVar2) &
                 GHIDRA_ZEXT8(bVar3) & GHIDRA_ZEXT8(bVar4)) == 1) {
              if (piVar16[0x109e] == piVar16[0x109f]) {
                piVar16[0x10a1] = GHIDRA_F2I(int, (GHIDRA_I2F(piVar16[0x10a1]) + 1.0));
              }
              iVar19 = TPGroupSeek((int)puVar14,"Bound");
              if (iVar19 == -1) {
                sprintf((char *)(g + 0x81d2),"Missing bound info: %s",local_dc,puVar14);
              }
              else {
                bVar1 = TPGetValueInt((int)puVar14,"screenleft",(uint *)(piVar16 + 0x10a3));
                bVar2 = TPGetValueInt((int)puVar14,"screenright",(uint *)(piVar16 + 0x10a2));
                iVar19 = (GHIDRA_ZEXT8(bVar1) & GHIDRA_ZEXT8(bVar2)) - 1;
                if (iVar19 == 0) {
                  iVar19 = TPGroupSeek((int)puVar14,"StageInfo");
                  piVar17 = g;
                  if (iVar19 == -1) {
                    sprintf((char *)(g + 0x81d2),"Missing stage info: %s",local_dc,0);
                  }
                  else {
                    g[0x4140] = 0xbe;
                    piVar17[0x4142] = -1;
                    TPGetValueInt((int)puVar14,"zoffset",(uint *)(piVar17 + 0x4140));
                    TPGetValueInt((int)puVar14,"zoffsetlink",(uint *)(g + 0x4142));
                    g[0x4141] = g[0x4140];
                    piVar16[0x109d] = 0;
                    TPGetValueInt((int)puVar14,"autoturn",(uint *)(piVar16 + 0x109d));
                    *puVar13 = 1;
                    TPGetValueInt((int)puVar14,"resetbg",puVar13);
                    piVar16[0x10a6] = 0x3ecccccd;
                    piVar16[0x10a4] = 0x80;
                    iVar19 = TPGroupSeek((int)puVar14,"Shadow");
                    if (iVar19 != -1) {
                      TPScanf((int)puVar14,"color","%i,%i,%i",&local_128,&local_124,&local_120,
                              extraout_ECX_02,extraout_ECX_02);
                      TPGetValueInt((int)puVar14,"intensity",(uint *)(piVar16 + 0x10a4));
                      TPGetValueFloat((int)puVar14,"yscale",(float *)(piVar16 + 0x10a6));
                      TPScanf((int)puVar14,"fade.range","%i,%i",piVar16 + 0x10a7,piVar16 + 0x10a8);
                    }
                    piVar16[0x10a5] =
                         (local_128 >> 3) << ((byte)_rgb_r_shift_16 & 0x1f) |
                         (local_124 >> 2) << ((byte)_rgb_g_shift_16 & 0x1f) |
                         (local_120 >> 3) << ((byte)_rgb_b_shift_16 & 0x1f);
                    iVar19 = TPGroupSeek((int)puVar14,"Reflection");
                    if (iVar19 != -1) {
                      TPGetValueInt((int)puVar14,"intensity",(uint *)(piVar16 + 0x10a9));
                    }
                    iVar19 = TPGroupSeek((int)puVar14,"Music");
                    if ((iVar19 != -1) && (g[0x6ef3] != 0)) {
                      pbVar15 = (byte *)TPGetValue((int)puVar14,"bgmusic");
                      if (*(char *)((int)g + 0x3013) == '\0') {
                        if (pbVar15 != (byte *)0x0) {
                          TPGetValueInt((int)puVar14,"bgvolume",(uint *)(piVar16 + 0x10b0));
                        }
                      }
                      else {
                        pbVar15 = (byte *)((int)g + 0x3013);
                      }
                      if ((pbVar15 != (byte *)0x0) &&
                         (((g[0x74e8] == 0 || (g[0x74ee] != 0)) &&
                          (iVar19 = BGMLoad(piVar16 + 0x10aa,pbVar15,1), iVar19 == 0)))) {
                        return 0;
                      }
                    }
                    TPFree(puVar14);
                    g[0x81c4] = Ticks;
                    bVar1 = GameBGLoad();
                    piVar16 = g;
                    if (GHIDRA_ZEXT8(bVar1) != 0) {
                      piVar17 = g + 0x7397;
                      g[0x81c4] = Ticks - g[0x81c4];
                      piVar16[0x7395] = piVar16[0x7396] + *piVar17;
                      iVar19 = 1;
                      piVar16[0x749d] = 0;
                      piVar16 = piVar16 + 0x33b8;
                      do {
                        *piVar16 = 0;
                        piVar16 = piVar16 + 0x6a7;
                        iVar19 = iVar19 + -1;
                      } while (-1 < iVar19);
                      iVar23 = 0;
                      iVar19 = 5;
                      if (0 < g[0x7396]) {
                        iVar21 = 0x1cf74;
                        do {
                          piVar17 = PlayerNew(0);
                          piVar16 = g;
                          *(int **)(iVar21 + 4 + (int)g) = piVar17;
                          if (piVar17 == (int *)0x0) {
                            strcat((char *)(piVar16 + 0x81d2),"\nCan\'t create helper characters");
                            return 0;
                          }
                          piVar17[2] = iVar19;
                          if (iVar19 + -1 < 0x20) {
                            PalGrpMakeFlag(&local_fc,1 << ((byte)(iVar19 + -1) & 0x1f),1);
                            iVar20 = *(int *)((int)g + iVar21 + 4);
                            *(uint *)(iVar20 + 0x25c8) = local_fc.w[0];
                            *(uint *)(iVar20 + 0x25cc) = local_fc.w[1];
                            *(uint *)(iVar20 + 0x25d0) = local_fc.w[2];
                            *(uint *)(iVar20 + 0x25d4) = local_fc.w[3];
                            uVar18 = local_fc.w[4];
                          }
                          else {
                            PalGrpMakeFlag(&local_11c,1 << ((char)iVar19 - 0x21U & 0x1f),2);
                            iVar20 = *(int *)((int)g + iVar21 + 4);
                            *(uint *)(iVar20 + 0x25c8) = local_11c.w[0];
                            *(uint *)(iVar20 + 0x25cc) = local_11c.w[1];
                            *(uint *)(iVar20 + 0x25d0) = local_11c.w[2];
                            *(uint *)(iVar20 + 0x25d4) = local_11c.w[3];
                            uVar18 = local_11c.w[4];
                          }
                          *(uint *)(iVar20 + 0x25d8) = uVar18;
                          iVar23 = iVar23 + 1;
                          iVar21 = iVar21 + 4;
                          iVar19 = iVar19 + 1;
                        } while (iVar23 < g[0x7396]);
                      }
                      if (g[0x81cd] == 0) {
                        g[0x81cb] = 0;
                      }
                      else {
                        g[0x81cb] = 1;
                      }
                      return 1;
                    }
                  }
                }
                else {
                  sprintf((char *)(g + 0x81d2),"Can\'t read bound info: %s",local_dc,iVar19);
                }
              }
            }
            else {
              sprintf((char *)(g + 0x81d2),"Can\'t read scaling info: %s",local_dc,extraout_ECX_01);
            }
          }
        }
        else {
          sprintf((char *)(g + 0x81d2),"Can\'t read player info: %s",local_dc,
                  GHIDRA_ZEXT8(bVar8));
        }
      }
    }
  }
  return 0;
}
#undef local_128
#undef local_124
#undef local_120
#undef local_11c
#undef local_fc
#undef local_dc

/* GameBGLoad @ 0x0809e630, 254 bytes
 * FIXUP: 1 data addresses written as literals replaced by data-image references
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x1010-byte frame (a local's address escapes, see apply_frame_emulation) */
bool GameBGLoad(void)

{
  int *piVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  undefined4 extraout_ECX;
  unsigned char ghidra_frame[0x1010] __attribute__((aligned(16)));
#define local_100c (*(char (*)[4104])(ghidra_frame + 0x4))
  
  pcVar2 = TPReadFile((char *)(g + 0x805));
  if (pcVar2 == (char *)0x0) {
    sprintf((char *)(g + 0x81d2),"\nError opening %s",g + 0x805,extraout_ECX);
  }
  local_100c[0] = '\0';
  iVar3 = TPGroupSeek((int)pcVar2,"BGdef");
  if (iVar3 != -1) {
    pcVar4 = TPGetValue((int)pcVar2,"spr");
    if (pcVar4 != (char *)0x0) {
      iVar3 = strmatchlen((int)pcVar4,(int)&DAT_0827953b,7);
      if (iVar3 == 0) {
        splitdirfile((char *)(g + 0x805),local_100c,(char *)0x0);
      }
    }
  }
  pcVar4 = BGArrayReadTP(pcVar2,local_100c,"BG",0,0);
  piVar1 = g;
  g[0x6ed4] = (int)pcVar4;
  if (pcVar4 != (char *)0x0) {
    TPFree((undefined4 *)pcVar2);
  }
  else {
    sprintf((char *)(piVar1 + 0x81d2),"\nBG error reading %s",piVar1 + 0x805,0);
  }
  return pcVar4 != (char *)0x0;
}
#undef local_100c

/* GameUnloadStage @ 0x0809e730, 407 bytes
 * REVIEW: pid-unaff_ */
void GameUnloadStage(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int unaff_EBP;
  int iVar4;
  int local_18;
  int local_14;
  
  BGMFree(g + 0x10aa);
  local_14 = 1;
  piVar2 = g;
  if (0 < g[0x7395]) {
    iVar4 = 0x1cf64;
    local_18 = 4;
    do {
      iVar3 = *(int *)(iVar4 + 4 + (int)piVar2);
      if (iVar3 != 0) {
        if (*(int *)(iVar3 + 0x158) != 0) {
          PlayerEnableSet(local_14,0);
          piVar2 = g;
        }
        iVar3 = *(int *)((int)piVar2 + iVar4 + 4);
        if (*(int *)(iVar3 + 0x10) != -1) {
          PlayerSavePersistVars
                    (*(int *)((int)piVar2 + iVar4 + 4),
                     piVar2 + *(int *)(iVar3 + 0x10) * 0x6a7 +
                              *(int *)(iVar3 + 0x14) * 400 + *(int *)(iVar3 + 0x18) * 100 + 0x3417);
          piVar2 = g;
        }
        piVar1 = *(int **)(iVar4 + 4 + (int)piVar2);
        iVar3 = -1;
        if ((*piVar1 != 0) && (piVar1[0x989] == 0)) {
          iVar3 = *(int *)(*piVar1 + 0x10a8);
          if (piVar1[3] == piVar2[0x33b3]) {
            unaff_EBP = piVar2[0x3a61] + piVar2[0x33ba];
          }
          else {
            unaff_EBP = 0;
          }
        }
        PlayerFree(*(int **)(iVar4 + 4 + (int)piVar2));
        if (iVar3 != -1) {
          PlayerCacheFreePriority(iVar3,unaff_EBP);
        }
        piVar2 = g;
        *(undefined4 *)((int)g + local_18 + 0x1ce64) = 0;
        *(undefined4 *)((int)piVar2 + iVar4 + 4) = 0;
      }
      local_14 = local_14 + 1;
      local_18 = local_18 + 4;
      iVar4 = iVar4 + 4;
    } while (local_14 <= piVar2[0x7395]);
  }
  BGArrayFree(piVar2[0x6ed4]);
  g[0x6ed4] = 0;
  return;
}

/* GameStgInitFightData @ 0x0809e8d0, 557 bytes
 * FIXUP: frame emulation: 8 stack locals placed at their original offsets in a 0x1050-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 GameStgInitFightData(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  unsigned char ghidra_frame[0x1050] __attribute__((aligned(16)));
#define local_1048 (*(int **)(ghidra_frame + 0x8))
#define local_1044 (*(int *)(ghidra_frame + 0xc))
#define local_1034 (*(int *)(ghidra_frame + 0x1c))
#define local_1030 (*(int *)(ghidra_frame + 0x20))
#define local_102c (*(char (*)[4096])(ghidra_frame + 0x24))
#define local_2c (*(int *)(ghidra_frame + 0x1024))
#define local_28 (*(int *)(ghidra_frame + 0x1028))
#define local_24 (*(undefined4 *)(ghidra_frame + 0x102c))
  
  piVar1 = g;
  iVar7 = 0;
  do {
    piVar2 = g;
    if (((1 < g[iVar7 * 0x6a7 + 0x33b9]) && (g[0x33b4] != 2 - iVar7)) &&
       (iVar3 = SysExplodParseGetSprGrpImgNo(piVar1 + iVar7 * 0x56 + 0x4af8,&local_1034,&local_1030)
       , iVar3 != 0)) {
      local_2c = local_1034;
      local_28 = local_1030;
      local_24 = 0xffffffff;
      local_1044 = 0;
      if (0 < piVar2[iVar7 * 0x6a7 + 0x33b9]) {
        local_1048 = piVar2 + iVar7 * 0x6a7 + 0x33bf;
        do {
          iVar3 = *local_1048 * 0x702c;
          joindirfile(local_102c,(char *)(iVar3 + g[0x14b4] + 0x200a),
                      (char *)(iVar3 + g[0x14b4] + 0x100b));
          puVar4 = TPReadFile(local_102c);
          if (puVar4 != (undefined4 *)0x0) {
            local_102c[0] = '\0';
            iVar5 = TPGroupSeek((int)puVar4,"Files");
            if ((iVar5 != -1) && (pcVar6 = TPGetValue((int)puVar4,"sprite"), pcVar6 != (char *)0x0))
            {
              joindirfile(local_102c,(char *)(iVar3 + g[0x14b4] + 0x200a),pcVar6);
            }
            TPFree(puVar4);
            if (local_102c[0] != '\0') {
              SpriteSetBufReadMode(0);
              iVar3 = SpriteReadSFFList(local_102c,&local_2c);
              piVar1[iVar7 * 4 + local_1044 + 0x52b5] = iVar3;
              SpriteSetBufReadMode(g[0x757b]);
            }
          }
          local_1044 = local_1044 + 1;
          local_1048 = local_1048 + 0x17;
        } while (local_1044 < piVar2[iVar7 * 0x6a7 + 0x33b9]);
      }
    }
    iVar7 = iVar7 + 1;
  } while (iVar7 < 2);
  return 1;
}
#undef local_1048
#undef local_1044
#undef local_1034
#undef local_1030
#undef local_102c
#undef local_2c
#undef local_28
#undef local_24

/* GameStgDeInitFightData @ 0x0809eb00, 85 bytes */
void GameStgDeInitFightData(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  piVar2 = g;
  iVar4 = 0;
  do {
    iVar5 = 3;
    iVar3 = iVar4 * 0x10 + 0x45b0;
    do {
      piVar1 = *(int **)((int)piVar2 + iVar3 + 0x10524);
      if (piVar1 != (int *)0x0) {
        SpriteArrayFree(piVar1);
        *(undefined4 *)((int)piVar2 + iVar3 + 0x10524) = 0;
      }
      iVar3 = iVar3 + 4;
      iVar5 = iVar5 + -1;
    } while (-1 < iVar5);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 2);
  return;
}

/* GameNextRound @ 0x0809eb60, 380 bytes
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
void GameNextRound(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int local_1c;
  
  iVar6 = 0;
  g[0x7506] = g[0x7506] + 1;
  local_1c = 0;
  do {
    iVar3 = GameRoundWinner();
    piVar2 = g;
    if (iVar3 != iVar6 + 1) {
      if (*(int *)((int)g + local_1c + 0xcee0) + 1 < *(int *)((int)g + local_1c + 0xcee4)) {
        W_Cls(0);
        FrameSkipReset();
        DrawToScreen();
        *(int *)((int)piVar2 + local_1c + 0xcee0) = *(int *)((int)piVar2 + local_1c + 0xcee0) + 1;
        TeamReorderAll(iVar6);
        GameLoadAndActivateTeam(iVar6);
      }
      piVar2 = g;
      iVar3 = *(int *)((int)g + local_1c + 0xcee0) * 0x5c + local_1c + 0xceec;
      iVar4 = 0;
      if (0 < *(int *)((int)g + iVar3 + 8)) {
        do {
          iVar5 = iVar4 + 1;
          iVar1 = g[*(int *)((int)piVar2 + iVar4 * 0x14 + iVar3 + 0xc) + 0x73d9];
          iVar4 = (int)GHIDRA_FIST32((float10)*(int *)(iVar1 + 0x50) *
                             *(float *)((int)piVar2 + local_1c + 0xe96c));
          *(int *)(iVar1 + 0x164) = iVar4;
          *(int *)(iVar1 + 0x16c) = iVar4;
          *(int *)(iVar1 + 0x168) = iVar4;
          *(int *)(iVar1 + 0x160) = iVar4;
          iVar4 = iVar5;
        } while (iVar5 < *(int *)((int)piVar2 + iVar3 + 8));
      }
    }
    iVar6 = iVar6 + 1;
    local_1c = local_1c + 0x1a9c;
  } while (iVar6 < 2);
  if (g[0x33b4] != 0) {
    SurvivalBuildRandomTeam(g + (2 - g[0x33b4]) * 0x6a7 + 0x33b8,2 - g[0x33b4],0);
  }
  GameRoundReset();
  FrameSkipReset();
  return;
}

/* GameReloadStage @ 0x0809ece0, 262 bytes */
undefined4 GameReloadStage(void)

{
  int *piVar1;
  int iVar2;
  
  W_Cls(0);
  V_FontDrawRight("Loading",(int *)g[0x413a],V_Width + -4,V_Height + -2,
                  0x18 << ((byte)_rgb_r_shift_16 & 0x1f) | 0x30 << ((byte)_rgb_g_shift_16 & 0x1f) |
                  0x18 << ((byte)_rgb_b_shift_16 & 0x1f));
  FrameSkipReset();
  DrawToScreen();
  PalGrpClear();
  GameStgDeInitFightData();
  GameUnloadStage();
  GameResetPersistVars();
  PlayerCacheClear();
  g[0x81c9] = Ticks;
  iVar2 = GameLoadStage();
  if ((iVar2 != 0) && (iVar2 = GameStgInitFightData(), piVar1 = g, iVar2 != 0)) {
    g[0x81c9] = Ticks - g[0x81c9];
    GameSetVol(piVar1[0x6ef5],piVar1[0x6ef7]);
    BGMStart(g + 0x10aa);
    GameMatchReset();
    FrameSkipReset();
    return 1;
  }
  return 0;
}

/* GameMatchReset @ 0x0809edf0, 1043 bytes
 * FIXUP: removed 1 x87 control-word save statements
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 6 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 3 stack locals placed at their original offsets in a 0x30-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void GameMatchReset(void)

{
  float10 fVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined2 in_FPUControlWord;
  unsigned char ghidra_frame[0x30] __attribute__((aligned(16)));
#define local_2c (*(float (*)[4])(ghidra_frame + 0x4))
#define local_1c (*(undefined2 *)(ghidra_frame + 0x14))
#define uStack_1a (*(undefined2 *)(ghidra_frame + 0x16))
  
  if (g[0x33b3] == 0) {
    GameResetPersistVars();
  }
  else {
    TeamResetPersistVars(2 - g[0x33b3]);
  }
  iVar5 = 0xe950;
  iVar4 = 0xe960;
  iVar6 = 1;
  TeamReorderAll(0);
  TeamReorderAll(1);
  GameLoadAndActivateTeam(0);
  GameLoadAndActivateTeam(1);
  piVar2 = g;
  piVar3 = g;
  do {
    *(undefined4 *)((int)piVar2 + iVar4 + 0xc) = 0x3f800000;
    iVar4 = iVar4 + 0x1a9c;
    piVar3[0x3a57] = 0;
    piVar3[0x3a58] = 0;
    piVar3[0x3a59] = 0;
    *(undefined4 *)((int)piVar2 + iVar5 + 0x18) = 1;
    iVar5 = iVar5 + 0x1a9c;
    piVar3[0x3a5c] = piVar2[0x4e75];
    piVar3[0x3a5d] = piVar2[0x4e76];
    piVar3 = piVar3 + 0x6a7;
    iVar6 = iVar6 + -1;
  } while (-1 < iVar6);
  piVar2 = g;
  if ((1 < g[0x33b9]) || (1 < g[0x3a60])) {
    iVar4 = 0;
    do {
      piVar2[iVar4 * 0x6a7 + 0x3a57] = 0x7d;
      piVar2[iVar4 * 0x6a7 + 0x3a5a] = 0;
      piVar2[iVar4 * 0x6a7 + 0x3a58] = 0x43898000;
      piVar2[iVar4 * 0x6a7 + 0x3a59] = 0x3f19999a;
      if (1 < piVar2[(1 - iVar4) * 0x6a7 + 0x33b9]) {
        piVar2[iVar4 * 0x6a7 + 0x3a5c] = piVar2[(1 - iVar4) * 0x6a7 + 0x33b9];
      }
      piVar2 = g;
      iVar5 = iVar4 + 1;
      g[iVar4 * 0x6a7 + 0x3a5d] = 0;
      iVar4 = iVar5;
    } while (iVar5 < 2);
  }
  piVar3 = g;
  iVar4 = 0;
  do {
    local_2c[iVar4] = (float10)piVar2[iVar4 * 0x6a7 + 0x33bd] / (float10)piVar2[iVar4 * 0x6a7 + 0x3a5c];
    iVar4 = iVar4 + 1;
    piVar2 = g;
  } while (iVar4 < 2);
  local_2c[0] = local_2c[0] / local_2c[1];
  fVar1 = local_2c[0];
  if (local_2c[0] < 1.0) {
    fVar1 = 1.0 / local_2c[0];
  }
  uVar7 = (uint)(local_2c[0] < 1.0);
  g[uVar7 * 0x6a7 + 0x3a5b] = GHIDRA_F2I(int, (1.0 / fVar1));
  if (piVar3[0x33b4] != 0) {
    uVar7 = piVar3[0x33b4] - 1;
    piVar3[uVar7 * 0x6a7 + 0x3a5c] = 999999;
    if (piVar3[uVar7 * 0x6a7 + 0x33b9] < 2) {
      piVar3[(1 - uVar7) * 0x6a7 + 0x3a5c] = 1;
    }
    else {
      piVar3[uVar7 * 0x6a7 + 0x3a5b] =
           (int)(1.0 - (float)(piVar3[uVar7 * 0x6a7 + 0x33b9] + -1) * ((double)0.1));
      piVar3[uVar7 * 0x6a7 + 0x3a57] =
           (int)GHIDRA_FIST32((float10)piVar3[uVar7 * 0x6a7 + 0x3a57] *
                      (1.0 / (float10)piVar3[uVar7 * 0x6a7 + 0x33b9]));
      piVar3[uVar7 * 0x6a7 + 0x3a58] =
           (int)((1.0 / ((float10)piVar3[uVar7 * 0x6a7 + 0x33b9] - 0.5)) *
                (float10)piVar3[uVar7 * 0x6a7 + 0x3a58]);
    }
  }
  piVar2 = g;
  if (g[0x81cc] != 0) {
    g[uVar7 * 0x6a7 + 0x3a5b] = 0x3f800000;
  }
  piVar3 = g;
  iVar4 = 1;
  if (0 < piVar2[0x7395]) {
    iVar5 = 0x1cf64;
    do {
      iVar6 = *(int *)(iVar5 + 4 + (int)piVar2);
      if (iVar6 != 0) {
        *(undefined4 *)(iVar6 + 0x180) = 0;
        *(undefined4 *)(iVar6 + 0x178) = 0;
        *(undefined4 *)(iVar6 + 0x342c) = 0;
        piVar2 = piVar3;
      }
      iVar4 = iVar4 + 1;
      iVar5 = iVar5 + 4;
    } while (iVar4 <= piVar2[0x7395]);
  }
  iVar5 = 9;
  GameRoundReset();
  piVar2 = g;
  iVar4 = 0;
  g[0x7546] = 0;
  piVar2[0x7517] = 0;
  piVar2[0x7506] = 1;
  piVar2[0x7508] = 0;
  piVar2[0x7507] = 0;
  piVar2[0x750a] = 0;
  do {
    *(undefined4 *)((int)piVar2 + iVar4 + 0x1d48c) = 0xffffffff;
    *(undefined4 *)((int)piVar2 + iVar4 + 0x1d464) = 0xffffffff;
    *(undefined4 *)((int)piVar2 + iVar4 + 0x1d4dc) = 0xffffffff;
    *(undefined4 *)((int)piVar2 + iVar4 + 0x1d4b4) = 0xffffffff;
    iVar4 = iVar4 + 4;
    iVar5 = iVar5 + -1;
  } while (-1 < iVar5);
  piVar2 = g + 0x7317;
  for (iVar4 = 6; piVar3 = g, iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar2 = 0;
    piVar2 = piVar2 + 1;
  }
  g[0x74e1] = 0;
  BGArrayReset(piVar3[0x6ed4]);
  return;
}
#undef local_2c
#undef local_1c
#undef uStack_1a

/* GameRoundReset @ 0x0809f210, 1639 bytes
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 7 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
void GameRoundReset(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_30;
  int local_2c;
  int local_28;
  
  piVar8 = g;
  SndIDStop(-1);
  piVar4 = g;
  iVar5 = g[0x4e61];
  g[0x7510] = g[0x508f];
  piVar4[0x7509] = 0;
  piVar4[0x7518] = 0;
  piVar4[0x750b] = 0;
  piVar4[0x750d] = 0;
  piVar4[0x750c] = 0;
  piVar4[0x750e] = 0;
  piVar4[0x750f] = 0;
  piVar4[0x7511] = 0;
  piVar4[0x7512] = 0;
  piVar4[0x7513] = 0;
  piVar4[0x7514] = 0;
  piVar4[0x7515] = (piVar4[0x79a0] + 1) * iVar5 + -1;
  piVar4[0x7516] = 0;
  if (((piVar4[0x33ae] == 3) || (piVar4[0x74e8] != 0)) || (piVar4[0x33b4] != 0)) {
    g[0x7515] = -1;
  }
  iVar5 = 1;
  piVar4 = g;
  if (0 < g[0x7395]) {
    local_48 = 0x1cf64;
    do {
      piVar3 = *(int **)(local_48 + 4 + (int)piVar4);
      if (piVar3 != (int *)0x0) {
        if (piVar3[7] == 0) {
          iVar7 = piVar3[0x58];
          iVar6 = piVar3[0x98b];
          iVar1 = piVar3[0x5e];
          PlayerReset(piVar3);
          PlayerChangeState((int)piVar3,0x170c);
          KBIRefreshKeyflags((int)(piVar3 + 0x92),piVar3[600]);
          piVar4 = g;
          piVar3[0x98b] = iVar6;
          piVar3[0x60] = iVar1;
          piVar3[0x5e] = iVar1;
          if (piVar4[0x74e8] != 0) {
            iVar6 = *(int *)piVar3[0x5d];
            piVar3[0x60] = iVar6;
            piVar3[0x61] = iVar6;
            piVar3[0x5e] = iVar6;
          }
          if (piVar4[piVar3[4] * 0x6a7 + 0x3a5a] == 0) {
            piVar3[0x58] = iVar7;
          }
          piVar4 = g;
          piVar3[0x5b] = piVar3[0x58];
          piVar3[0x5a] = piVar3[0x58];
        }
        else if (piVar3[0x56] != 0) {
          PlayerEnableSet(piVar3[2],0);
          piVar4 = g;
        }
      }
      iVar5 = iVar5 + 1;
      local_48 = local_48 + 4;
    } while (iVar5 <= piVar4[0x7395]);
  }
  iVar5 = 0;
  do {
    iVar6 = 0;
    iVar7 = piVar4[iVar5 * 0x6a7 + 0x33b8];
    piVar3 = piVar4;
    if (0 < piVar4[iVar5 * 0x6a7 + iVar7 * 0x17 + 0x33bd]) {
      do {
        iVar2 = piVar3[piVar4[iVar5 * 0x6a7 + iVar7 * 0x17 + iVar6 * 5 + 0x33be] + 0x73d9];
        iVar1 = (int)GHIDRA_FIST32((float10)*(int *)(iVar2 + 0x50) * GHIDRA_I2F(piVar4[iVar5 * 0x6a7 + 0x3a5b]) *
                           (float10)piVar3[0x799f] * ((float)0.01f) + 0.5);
        *(int *)(iVar2 + 0x164) = iVar1;
        if (iVar1 < *(int *)(iVar2 + 0x160)) {
          *(int *)(iVar2 + 0x16c) = iVar1;
          *(int *)(iVar2 + 0x168) = iVar1;
          *(int *)(iVar2 + 0x160) = iVar1;
        }
        iVar6 = iVar6 + 1;
        piVar3 = g;
      } while (iVar6 < piVar4[iVar5 * 0x6a7 + iVar7 * 0x17 + 0x33bd]);
    }
    iVar5 = iVar5 + 1;
    piVar4 = g;
  } while (iVar5 < 2);
  iVar5 = 0;
  GameRoundResetPlayerPos();
  piVar4 = g;
  local_3c = 0xe970;
  local_40 = 0;
  local_44 = 0;
  do {
    *(undefined4 *)(local_3c + 8 + (int)piVar4) = 0;
    iVar7 = *(int *)((int)piVar8 + local_40 + 0x10420);
    if (0 < iVar7) {
      piVar3 = piVar8 + local_44 + 0x4109;
      do {
        iVar6 = piVar4[*piVar3 + 0x73d9];
        if (iVar6 != 0) {
          *(float *)((int)piVar4 + local_3c + 8) =
               (float10)*(int *)(iVar6 + 0x160) / (float10)*(int *)(iVar6 + 0x164) +
               *(float *)((int)piVar4 + local_3c + 8);
        }
        piVar3 = piVar3 + 5;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
    iVar7 = *(int *)((int)piVar8 + local_40 + 0x10420);
    if (0 < iVar7) {
      *(float *)((int)piVar4 + local_3c + 8) = *(float *)((int)piVar4 + local_3c + 8) / (float10)iVar7
      ;
    }
    piVar3 = g;
    local_3c = local_3c + 0x1a9c;
    local_40 = local_40 + 0x5c;
    local_44 = local_44 + 0x17;
    iVar5 = iVar5 + 1;
  } while (iVar5 < 2);
  iVar5 = 1;
  if (0 < piVar4[0x7395]) {
    iVar7 = 0x1cf64;
    do {
      iVar6 = *(int *)(iVar7 + 4 + (int)piVar4);
      if (iVar6 != 0) {
        *(undefined4 *)(iVar6 + 0xe0c) = 0;
        piVar4 = piVar3;
      }
      iVar5 = iVar5 + 1;
      iVar7 = iVar7 + 4;
    } while (iVar5 <= piVar4[0x7395]);
  }
  piVar8 = g;
  iVar5 = 0x1cf64;
  local_28 = 0x1e650;
  local_2c = 0x1e640;
  local_30 = 0x1e620;
  iVar7 = 3;
  do {
    iVar6 = *(int *)(iVar5 + 4 + (int)piVar4);
    if (iVar6 != 0) {
      iVar1 = *(int *)(local_30 + 0x14 + (int)piVar4);
      if (iVar1 != -1) {
        *(int *)(iVar6 + 0x262c) = iVar1;
        piVar4 = piVar8;
      }
      iVar1 = *(int *)(local_2c + 0x14 + (int)piVar4);
      if (iVar1 != -1) {
        *(int *)(iVar6 + 0x16c) = iVar1;
        *(int *)(iVar6 + 0x168) = iVar1;
        *(int *)(iVar6 + 0x160) = iVar1;
        *(int *)(iVar6 + 0x164) = iVar1;
        piVar4 = piVar8;
      }
      iVar1 = *(int *)(local_28 + 0x14 + (int)piVar4);
      if (iVar1 != -1) {
        **(int **)(iVar6 + 0x170) = iVar1;
        *(int *)(iVar6 + 0x180) = iVar1;
        *(int *)(iVar6 + 0x184) = iVar1;
        piVar4 = piVar8;
      }
    }
    local_28 = local_28 + 4;
    local_2c = local_2c + 4;
    local_30 = local_30 + 4;
    iVar5 = iVar5 + 4;
    iVar7 = iVar7 + -1;
  } while (-1 < iVar7);
  CameraMoveAbs((float10)piVar4[0x1080],(float10)piVar4[0x1081]);
  piVar8 = g;
  g[0x7316] = 0;
  piVar8[0x7315] = 0;
  AnimPerArrayClear((int *)piVar8[0x413c]);
  MasterPalAdd(0,0,0);
  MasterPalMul(0,0,0);
  piVar8 = g;
  *(undefined1 *)((int)g + 0x1d396) = 0;
  piVar4 = g;
  piVar8[0x74e3] = 0;
  piVar8[0x74e4] = 0;
  *(undefined2 *)(piVar8 + 0x74e5) = 0;
  if (piVar4[0x107f] != 0) {
    BGArrayReset(piVar4[0x6ed4]);
    piVar4 = g;
  }
  PalFXReset(piVar4 + 0x6ed5);
  PalFXReset(g + 0x6ee4);
  PalGrpResetPalette();
  GameAftImgReset(g[0x413f]);
  ExplodArrayReset((undefined4 *)g[0x52be]);
  ExplodArrayReset((undefined4 *)g[0x52bf]);
  piVar8 = g;
  g[0x74f3] = -1;
  piVar8[0x7503] = 0;
  piVar8[0x74fa] = 0;
  piVar8 = piVar8 + 0x7317;
  for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar8 = 0;
    piVar8 = piVar8 + 1;
  }
  piVar8 = g + 0x7547;
  for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar8 = 0;
    piVar8 = piVar8 + 1;
  }
  piVar8 = g + 0x754d;
  for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar8 = 0;
    piVar8 = piVar8 + 1;
  }
  keypauseflag = 0;
  g[0x7309] = 0;
  return;
}

/* GameRoundResetPlayerPos @ 0x0809f880, 221 bytes
 * FIXUP: 6 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
int GameRoundResetPlayerPos(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  piVar4 = g;
  iVar5 = 3;
  iVar3 = 0x1cf64;
  do {
    iVar2 = *(int *)(iVar3 + 4 + (int)piVar4);
    if (iVar2 != 0) {
      *(undefined4 *)(iVar2 + 0x1bc) = 0;
      *(undefined4 *)(iVar2 + 0x1b8) = 0;
      *(undefined4 *)(iVar2 + 0x1b4) = 0;
    }
    iVar3 = iVar3 + 4;
    iVar5 = iVar5 + -1;
  } while (-1 < iVar5);
  iVar3 = 1;
  do {
    iVar5 = piVar4[iVar3 + 0x73d9];
    if (iVar5 != 0) {
      if (piVar4[iVar3 + 0x1094] != *(int *)(iVar5 + 400)) {
        PlayerTurnAround(iVar5);
        piVar4 = g;
      }
      iVar2 = piVar4[iVar3 + 0x1088] + 0xa0;
      *(float *)(iVar5 + 0x19c) = (float10)iVar2;
      *(float *)(iVar5 + 0x1a8) = (float10)iVar2;
      iVar1 = piVar4[iVar3 + 0x108c];
      *(float *)(iVar5 + 0x1a0) = (float10)iVar1;
      *(float *)(iVar5 + 0x1ac) = (float10)iVar1;
      iVar1 = piVar4[iVar3 + 0x1090];
      *(float *)(iVar5 + 0x1a4) = (float10)iVar1;
      *(float *)(iVar5 + 0x1b0) = (float10)iVar1;
    }
    iVar3 = iVar3 + 1;
    piVar4 = g;
  } while (iVar3 < 5);
  return iVar2;
}

/* GameRoundWinner @ 0x0809f960, 12 bytes */
int GameRoundWinner(void)

{
  return g[0x7512];
}

/* GameMatchWinner @ 0x0809f970, 200 bytes */
int GameMatchWinner(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  if (((g[0x7511] == 3) && (g[0x7514] < g[0x508d])) || (iVar1 = 0, g[0x7511] < 3)) {
    iVar3 = 0;
  }
  else {
    for (; iVar1 < 2; iVar1 = iVar1 + 1) {
      iVar2 = g[iVar1 + 0x7507];
      if ((g[0x7509] == 0) &&
         ((g[0x7512] == iVar1 + 1 ||
          ((g[0x7512] == 0 && (g[iVar1 * 0x6a7 + 0x3a5d] < g[0x750a] + 1)))))) {
        iVar2 = iVar2 + 1;
      }
      if (g[iVar1 * 0x6a7 + 0x3a5c] <= iVar2) {
        if (iVar3 == 0) {
          iVar3 = iVar1 + 1;
        }
        else if (g[0x33b3] == 0) {
          iVar3 = 1;
        }
        else {
          iVar3 = 3 - g[0x33b3];
        }
      }
    }
  }
  return iVar3;
}

/* LogPreMatch @ 0x0809fa40, 508 bytes */
void LogPreMatch(void)

{
  FILE *__stream;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar1;
  int *piVar2;
  undefined4 extraout_EDX;
  undefined4 uVar3;
  undefined4 extraout_EDX_00;
  int *piVar4;
  int iVar5;
  int iVar6;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  
  if ((g[0x758c] != 0) && (__stream = fopen((char *)(g + 0x758d),"at"), __stream != (FILE *)0x0)) {
    local_20 = g[0x7543];
    fprintf(__stream,"[Match %i]\n",local_20);
    fprintf(__stream,"totalmatches = %i\n",g[0x7544]);
    local_1c = 0;
    local_28 = 0;
    piVar2 = g;
    do {
      local_18 = 0;
      piVar4 = piVar2;
      if (0 < *(int *)((int)piVar2 + local_28 + 0xcee4)) {
        local_24 = (int)piVar2 + local_28 + 0xcef8;
        iVar5 = (int)piVar2 + local_28 + 0xceec;
        do {
          fprintf(__stream,"team%i.%i = ",local_1c + 1,local_18 + 1);
          uVar1 = extraout_ECX;
          if (0 < *(int *)(iVar5 + 8)) {
            local_20 = 0;
            iVar6 = 0;
            uVar3 = extraout_EDX;
            do {
              if (0 < iVar6) {
                fprintf(__stream,", ",uVar3,uVar3);
              }
              iVar6 = iVar6 + 1;
              fprintf(__stream,(char *)(g[0x1b50] + 4 +
                                       *(int *)(g[0x14b4] + 0x500c +
                                               *(int *)(local_20 + local_24) * 0x702c) * 0x2038),
                      local_20,local_20);
              local_20 = local_20 + 0x14;
              uVar1 = extraout_ECX_00;
              uVar3 = extraout_EDX_00;
            } while (iVar6 < *(int *)(iVar5 + 8));
          }
          iVar5 = iVar5 + 0x5c;
          fprintf(__stream,"\n",uVar1,uVar1);
          local_24 = local_24 + 0x5c;
          local_18 = local_18 + 1;
          piVar4 = g;
        } while (local_18 < *(int *)((int)piVar2 + local_28 + 0xcee4));
      }
      local_1c = local_1c + 1;
      local_28 = local_28 + 0x1a9c;
      piVar2 = piVar4;
    } while (local_1c < 2);
    fprintf(__stream,"stage = %s\n",piVar4 + 0x805,local_20);
    fprintf(__stream,"\n");
    fclose(__stream);
  }
  return;
}

/* LogMatch @ 0x0809fc40, 299 bytes
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void LogMatch(void)

{
  int iVar1;
  float10 dVar2;
  FILE *__stream;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  if (g[0x758c] != 0) {
    __stream = fopen((char *)(g + 0x758d),"at");
    if (__stream != (FILE *)0x0) {
      fprintf(__stream,"[Match %i Round %i]\n",g[0x7543],g[0x7506]);
      iVar3 = GameRoundWinner();
      fprintf(__stream,"winningteam = %i\n",iVar3);
      if (g[0x7515] == -1) {
        dVar2 = -1.0;
      }
      else {
        dVar2 = (double)g[0x7515] / (double)g[0x4e61];
      }
      iVar5 = 1;
      iVar3 = 0x1cf64;
      fprintf(__stream,"timeleft = %.2f\n",dVar2);
      do {
        piVar4 = g + 1;
        iVar1 = *(int *)(iVar3 + (int)piVar4);
        if (iVar1 != 0) {
          fprintf(__stream,"p%i.name = %s\n",iVar5,iVar1 + 0x20);
          fprintf(__stream,"p%i.life = %i\n",iVar5,*(undefined4 *)(iVar1 + 0x160));
          piVar4 = (int *)fprintf(__stream,"p%i.power = %i\n",iVar5,**(undefined4 **)(iVar1 + 0x170)
                                 );
        }
        iVar5 = iVar5 + 1;
        iVar3 = iVar3 + 4;
      } while (iVar5 < 5);
      fprintf(__stream,"\n",piVar4,piVar4);
      fclose(__stream);
    }
  }
  return;
}

