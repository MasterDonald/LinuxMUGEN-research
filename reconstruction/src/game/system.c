/*
 * system.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x080d2b60-0x080d56f7, 12 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* GameLoadSystem @ 0x080d2b60, 3650 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 20 stack locals placed at their original offsets in a 0x2180-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 GameLoadSystem(void)

{
  uint *puVar1;
  uint *puVar2;
  bool bVar3;
  FILE *pFVar4;
  int iVar5;
  FILE *pFVar6;
  int *piVar7;
  int iVar8;
  uint *puVar9;
  undefined3 extraout_var;
  int *piVar10;
  FILE *extraout_ECX;
  FILE *extraout_ECX_00;
  FILE *extraout_EDX;
  FILE *extraout_EDX_00;
  char *pcVar11;
  uint *puVar12;
  uint *puVar13;
  FILE *__src;
  unsigned char ghidra_frame[0x2180] __attribute__((aligned(16)));
#define local_2180 (*(uint **)(ghidra_frame + 0x0))
#define local_217c (*(char *(*)[4])(ghidra_frame + 0x4))
#define local_216c (*(char **)(ghidra_frame + 0x14))
#define local_2168 (*(char **)(ghidra_frame + 0x18))
#define local_2164 (*(char **)(ghidra_frame + 0x1c))
#define local_2160 (*(char **)(ghidra_frame + 0x20))
#define local_215c (*(char **)(ghidra_frame + 0x24))
#define local_2158 (*(char **)(ghidra_frame + 0x28))
#define local_2154 (*(undefined **)(ghidra_frame + 0x2c))
#define local_214c (*(char *(*)[4])(ghidra_frame + 0x34))
#define local_213c (*(char **)(ghidra_frame + 0x44))
#define local_2138 (*(char **)(ghidra_frame + 0x48))
#define local_2134 (*(char **)(ghidra_frame + 0x4c))
#define local_2130 (*(char **)(ghidra_frame + 0x50))
#define local_212c (*(char **)(ghidra_frame + 0x54))
#define local_2128 (*(char **)(ghidra_frame + 0x58))
#define local_2124 (*(undefined **)(ghidra_frame + 0x5c))
#define local_211c (*(char (*)[4096])(ghidra_frame + 0x64))
#define local_111c (*(FILE (*)[27])(ghidra_frame + 0x1064))
#define local_11c (*(int (*)[67])(ghidra_frame + 0x2064))
  
  __src = local_111c;
  joindirfile((char *)__src,(char *)((int)g + 0x15aff),(char *)(g + 0x52c0));
  pFVar4 = TPReadFile((char *)__src);
  if (pFVar4 == (FILE *)0x0) {
    piVar10 = g + 0x81d2;
    pcVar11 = "Can\'t open %s%s";
    pFVar6 = (FILE *)((int)g + 0x15aff);
    __src = (FILE *)(g + 0x52c0);
  }
  else {
    iVar5 = TPGroupSeek((int)pFVar4,"Files");
    if (iVar5 == -1) {
      piVar10 = g + 0x81d2;
      pcVar11 = "Can\'t access [Files] group";
      pFVar6 = extraout_EDX;
      __src = extraout_EDX;
    }
    else {
      pFVar6 = (FILE *)TPGetValue((int)pFVar4,"spr");
      if (pFVar6 == (FILE *)0x0) {
        piVar10 = g + 0x81d2;
        pcVar11 = "Missing spr specification in [Files]";
        pFVar6 = __src;
      }
      else {
        iVar5 = FindFileDir((char *)pFVar6,(char *)__src,(char *)0x0);
        if (iVar5 == 0) {
          return 0;
        }
        piVar7 = SpriteReadFile((char *)__src);
        piVar10 = g;
        g[0x5ac0] = (int)piVar7;
        if (piVar7 == (int *)0x0) {
          piVar10 = piVar10 + 0x81d2;
          pcVar11 = "Can\'t load %s";
          __src = pFVar4;
        }
        else {
          strcpy((char *)(piVar10 + 0x5ac1),(char *)__src);
          pFVar6 = (FILE *)TPGetValue((int)pFVar4,"snd");
          if (pFVar6 != (FILE *)0x0) {
            iVar5 = FindFileDir((char *)pFVar6,(char *)__src,(char *)0x0);
            if (iVar5 == 0) {
              return 0;
            }
            piVar7 = SndReadFile((char *)__src);
            piVar10 = g;
            g[0x5ec1] = (int)piVar7;
            if (piVar7 == (int *)0x0) {
              piVar10 = piVar10 + 0x81d2;
              pcVar11 = "Can\'t load %s";
              goto LAB_080d3985;
            }
            strcpy((char *)(piVar10 + 0x5ec2),(char *)__src);
          }
          pcVar11 = TPGetValue((int)pFVar4,"fight");
          if (pcVar11 == (char *)0x0) {
            return 0;
          }
          strcpy(local_211c,pcVar11);
          iVar5 = TPScanf((int)pFVar4,"select","%s",g + 0x14e0);
          if (iVar5 < 1) {
            return 0;
          }
          TPScanf((int)pFVar4,"logo.storyboard","%s",g + 0x1b51);
          TPScanf((int)pFVar4,"intro.storyboard","%s",g + 0x1f51);
          local_2180 = (uint *)0x0;
          do {
            g[(int)local_2180 + 0x62c3] = g[0x413a];
            sprintf((char *)local_11c,"font%i",local_2180,local_111c);
            pFVar6 = (FILE *)TPGetValue((int)pFVar4,(char *)local_11c);
            if (pFVar6 != (FILE *)0x0) {
              iVar5 = FindFileDir((char *)pFVar6,(char *)local_111c,(char *)0x0);
              if (iVar5 == 0) {
                return 0;
              }
              iVar5 = FontReadFile((char *)local_111c);
              piVar10 = g;
              g[(int)local_2180 + 0x62c3] = iVar5;
              if (iVar5 == 0) {
                piVar10 = piVar10 + 0x81d2;
                pcVar11 = "Can\'t read font %s";
                __src = (FILE *)0x0;
                goto LAB_080d3985;
              }
            }
            local_2180 = (uint *)((int)local_2180 + 1);
          } while ((int)local_2180 < 10);
          iVar5 = TPGroupScanFirst((int)pFVar4);
          do {
            iVar8 = strimatch((char *)(iVar5 + 1),"begin action ");
            if (iVar8 != 0) break;
            iVar5 = TPGroupScanNext((int)pFVar4);
          } while (iVar5 != 0);
          if (iVar5 != 0) {
            piVar7 = AnimRCReadFileTP((int)pFVar4);
            piVar10 = g;
            g[0x62c2] = (int)piVar7;
            if (piVar7 == (int *)0x0) {
              piVar10 = piVar10 + 0x81d2;
              pcVar11 = "Error loading anim";
              pFVar6 = pFVar4;
              __src = pFVar4;
              goto LAB_080d3985;
            }
          }
          iVar5 = TPGroupSeek((int)pFVar4,"Music");
          if (iVar5 != -1) {
            BGMParse((int)pFVar4,(undefined1 *)(g + 0x62d1),"title.bgm");
            BGMParse((int)pFVar4,(undefined1 *)(g + 0x6ad3),"select.bgm");
            BGMParse((int)pFVar4,(undefined1 *)(g + 0x66d2),"vs.bgm");
          }
          iVar5 = TPGroupSeek((int)pFVar4,"title info");
          piVar10 = g;
          puVar9 = (uint *)(iVar5 + 1);
          if (puVar9 == (uint *)0x0) {
            piVar10 = g + 0x81d2;
            pcVar11 = "Can\'t access [Title Info] group";
            pFVar6 = extraout_EDX_00;
            __src = extraout_EDX_00;
          }
          else {
            local_214c[0] = "arcade";
            puVar1 = (uint *)(g + 0x1005);
            g[0x100d] = 0x9f;
            piVar10[0x100e] = 0x9e;
            piVar10[0x1016] = 0xd;
            local_214c[1] = "versus";
            local_214c[2] = "teamarcade";
            local_214c[3] = "teamversus";
            local_213c = "teamcoop";
            local_2138 = "survival";
            local_2134 = "survivalcoop";
            local_2130 = "training";
            local_212c = "watch";
            local_2128 = "options";
            local_2124 = &DAT_0827d0db;
            local_217c[0] = "Arcade";
            local_217c[1] = "VS Mode";
            local_217c[2] = "Team Arcade";
            local_217c[3] = "Team Versus";
            local_216c = "Team Co-op";
            local_2168 = "Survival";
            local_2164 = "Survival Co-op";
            local_2160 = "Training";
            piVar10[0x106f] = 0xc;
            piVar10[0x1070] = 8;
            piVar10[0x1071] = 5;
            piVar10[0x1072] = 1;
            piVar10[0x1073] = -0x20;
            piVar10[0x1074] = -10;
            piVar10[0x1075] = 0x20;
            piVar10[0x1076] = 2;
            piVar10[0x1012] = -1;
            piVar10[0x100f] = -1;
            local_215c = "Watch";
            local_2158 = "Options";
            local_2154 = &DAT_082798d6;
            TPGetValueInt((int)pFVar4,"fadein.time",puVar1);
            puVar12 = (uint *)(piVar10 + 0x1006);
            pcVar11 = "fadeout.time";
            TPGetValueInt((int)pFVar4,"fadeout.time",puVar12);
            puVar2 = (uint *)piVar10[0x1005];
            if ((int)puVar2 < 1) {
              piVar10[0x1005] = 1;
            }
            if (piVar10[0x1006] < 1) {
              piVar10[0x1006] = 1;
            }
            TPScanf((int)pFVar4,"menu.pos","%i,%i",piVar10 + 0x100d,piVar10 + 0x100e,pcVar11,puVar12
                    ,puVar9);
            TPScanf((int)pFVar4,"menu.item.font","%i,%i,%i",piVar10 + 0x100f,piVar10 + 0x1011,
                    piVar10 + 0x1010);
            piVar7 = piVar10 + 0x1013;
            TPScanf((int)pFVar4,"menu.item.active.font","%i,%i,%i",piVar10 + 0x1012,piVar10 + 0x1014
                    ,piVar7);
            TPScanf((int)pFVar4,"menu.item.spacing","%i,%i",piVar10 + 0x1015,piVar10 + 0x1016);
            local_2180 = (uint *)0x0;
            do {
              puVar13 = (uint *)local_214c[(int)local_2180];
              if ((char)*puVar13 != '\0') {
                puVar9 = local_2180;
                sprintf((char *)local_11c,"menu.itemname.%s",puVar13,local_2180);
                piVar7 = local_11c;
                pcVar11 = TPGetValue((int)pFVar4,(char *)local_11c);
                if (pcVar11 == (char *)0x0) {
                  piVar7 = (int *)local_217c[(int)local_2180];
                  puVar12 = puVar2;
                  puVar9 = puVar2;
                  strcpy((char *)(puVar1 + (int)local_2180 * 8 + 0x12),(char *)piVar7);
                }
                else {
                  GetQuotedString((int)pFVar4,(char *)local_11c,
                                  (char *)(puVar1 + (int)local_2180 * 8 + 0x12),0x1f,(char *)0x0);
                  puVar12 = puVar13;
                }
              }
              local_2180 = (uint *)((int)local_2180 + 1);
            } while ((int)local_2180 < 0xb);
            TPScanf((int)pFVar4,"menu.window.margins.y","%i,%i",piVar10 + 0x106f,piVar10 + 0x1070,
                    piVar7,puVar12,puVar9);
            TPGetValueInt((int)pFVar4,"menu.window.visibleitems",(uint *)(piVar10 + 0x1071));
            TPGetValueInt((int)pFVar4,"menu.boxcursor.visible",(uint *)(piVar10 + 0x1072));
            TPScanf((int)pFVar4,"menu.boxcursor.coords","%i,%i,%i,%i",piVar10 + 0x1073,
                    piVar10 + 0x1074,piVar10 + 0x1075,piVar10 + 0x1076);
            ParseSndGI((int)pFVar4,"cursor.move.snd",piVar10 + 0x1007,(int)(piVar10 + 0x1008));
            ParseSndGI((int)pFVar4,"cursor.done.snd",piVar10 + 0x1009,(int)(piVar10 + 0x100a));
            ParseSndGI((int)pFVar4,"cancel.snd",piVar10 + 0x100b,(int)(piVar10 + 0x100c));
            iVar5 = TPGroupSeek((int)pFVar4,"option info");
            piVar10 = g;
            if (iVar5 == -1) {
              pcVar11 = "Can\'t access [Option Info] group";
              piVar10 = g + 0x81d2;
              pFVar6 = (FILE *)0x0;
              __src = (FILE *)0x0;
            }
            else {
              ParseSndGI((int)pFVar4,"cursor.move.snd",g + 0x1079,(int)(g + 0x107a));
              ParseSndGI((int)pFVar4,"cursor.done.snd",piVar10 + 0x107b,(int)(piVar10 + 0x107c));
              pFVar6 = (FILE *)(piVar10 + 0x107d);
              ParseSndGI((int)pFVar4,"cancel.snd",(undefined4 *)pFVar6,(int)(piVar10 + 0x107e));
              iVar5 = TPGroupSeek((int)pFVar4,"select info");
              if (iVar5 == -1) {
                piVar10 = g + 0x81d2;
                pcVar11 = "Can\'t access [Select Info] group";
                __src = pFVar6;
              }
              else {
                bVar3 = CharselReadConfig((int)pFVar4);
                if (GHIDRA_ZEXT8(bVar3) == 0) {
                  return 0;
                }
                iVar5 = TPGroupSeek((int)pFVar4,"vs screen");
                piVar10 = g;
                if (iVar5 == -1) {
                  piVar10 = g + 0x81d2;
                  pcVar11 = "Can\'t access [VS Screen] group\n";
                  pFVar6 = pFVar4;
                  __src = pFVar4;
                }
                else {
                  g[0x3395] = 0x96;
                  puVar9 = (uint *)(piVar10 + 0x3395);
                  TPGetValueInt((int)pFVar4,"time",puVar9);
                  TPGetValueInt((int)pFVar4,"fadein.time",(uint *)(piVar10 + 0x3396));
                  TPGetValueInt((int)pFVar4,"fadeout.time",(uint *)(piVar10 + 0x3397));
                  local_2180 = (uint *)0x0;
                  do {
                    puVar9[(int)local_2180 * 10 + 5] = 0xffffffff;
                    puVar9[(int)local_2180 * 10 + 10] = (uint)(local_2180 == (uint *)0x0) * 2 - 1;
                    puVar9[(int)local_2180 * 10 + 0xc] = 0x3f800000;
                    puVar9[(int)local_2180 * 10 + 0xb] = 0x3f800000;
                    sprintf((char *)local_11c,"p%i.pos",(int)local_2180 + 1,0x3f800000);
                    TPScanf((int)pFVar4,(char *)local_11c,"%i,%i",puVar9 + (int)local_2180 * 10 + 3,
                            puVar9 + (int)local_2180 * 10 + 4);
                    sprintf((char *)local_11c,"p%i.facing",(int)local_2180 + 1);
                    TPScanf((int)pFVar4,(char *)local_11c,"%i",
                            piVar10 + (int)local_2180 * 10 + 0x339f);
                    sprintf((char *)local_11c,"p%i.scale",(int)local_2180 + 1);
                    TPScanf((int)pFVar4,(char *)local_11c,"%f,%f",
                            puVar9 + (int)local_2180 * 10 + 0xb,puVar9 + (int)local_2180 * 10 + 0xc)
                    ;
                    sprintf((char *)local_11c,"p%i.name.pos",(int)local_2180 + 1);
                    TPScanf((int)pFVar4,(char *)local_11c,"%i,%i",puVar9 + (int)local_2180 * 10 + 8,
                            puVar9 + (int)local_2180 * 10 + 9);
                    sprintf((char *)local_11c,"p%i.name.font",(int)local_2180 + 1);
                    TPScanf((int)pFVar4,(char *)local_11c,"%i,%i,%i",
                            puVar9 + (int)local_2180 * 10 + 5,puVar9 + (int)local_2180 * 10 + 6,
                            puVar9 + (int)local_2180 * 10 + 7);
                    local_2180 = (uint *)((int)local_2180 + 1);
                  } while ((int)local_2180 < 2);
                  g[0x74ea] = -1;
                  iVar5 = TPGroupSeek((int)pFVar4,"demo mode");
                  if (iVar5 != -1) {
                    local_2180 = (uint *)0x0;
                    TPGetValueInt((int)pFVar4,"enabled",(uint *)&local_2180);
                    if (local_2180 != (uint *)0x0) {
                      TPGetValueInt((int)pFVar4,"title.waittime",(uint *)(g + 0x74ea));
                    }
                    TPGetValueInt((int)pFVar4,"select.enabled",(uint *)(g + 0x74eb));
                    TPGetValueInt((int)pFVar4,"vsscreen.enabled",(uint *)(g + 0x74ec));
                    TPGetValueInt((int)pFVar4,"fight.endtime",(uint *)(g + 0x74ed));
                    TPGetValueInt((int)pFVar4,"fight.playbgm",(uint *)(g + 0x74ee));
                    TPGetValueInt((int)pFVar4,"fight.bars.display",(uint *)(g + 0x74ef));
                    TPGetValueInt((int)pFVar4,"intro.waitcycles",(uint *)(g + 0x74e9));
                    TPGetValueInt((int)pFVar4,"debuginfo",(uint *)(g + 0x74f0));
                  }
                  iVar5 = TPGroupSeek((int)pFVar4,"continue screen");
                  if (iVar5 != -1) {
                    piVar10 = g + 0x2b94;
                    TPGetValueInt((int)pFVar4,"enabled",(uint *)(g + 0x2b93));
                    TPScanf((int)pFVar4,"storyboard","%s",piVar10);
                  }
                  iVar5 = TPGroupSeek((int)pFVar4,"game over screen");
                  if (iVar5 != -1) {
                    piVar10 = g + 0x2f95;
                    TPGetValueInt((int)pFVar4,"enabled",(uint *)(g + 0x2f94));
                    TPScanf((int)pFVar4,"storyboard","%s",piVar10);
                  }
                  iVar5 = TPGroupSeek((int)pFVar4,"win screen");
                  piVar10 = g;
                  if (iVar5 != -1) {
                    TPGetValueInt((int)pFVar4,"enabled",(uint *)(g + 0x2b54));
                    SysExplodParse((int)pFVar4,piVar10 + 0x2b55,"wintext");
                    TPGetValueInt((int)pFVar4,"fadein.time",(uint *)(piVar10 + 0x2b71));
                    TPGetValueInt((int)pFVar4,"pose.time",(uint *)(piVar10 + 0x2b70));
                    TPGetValueInt((int)pFVar4,"fadeout.time",(uint *)(piVar10 + 0x2b72));
                  }
                  iVar5 = TPGroupSeek((int)pFVar4,"survival results screen");
                  piVar10 = g;
                  if (iVar5 != -1) {
                    TPGetValueInt((int)pFVar4,"enabled",(uint *)(g + 0x2b73));
                    SysExplodParse((int)pFVar4,piVar10 + 0x2b74,"winstext");
                    TPGetValueInt((int)pFVar4,"fadein.time",(uint *)(piVar10 + 0x2b90));
                    TPGetValueInt((int)pFVar4,"show.time",(uint *)(piVar10 + 0x2b8f));
                    TPGetValueInt((int)pFVar4,"fadeout.time",(uint *)(piVar10 + 0x2b91));
                    TPGetValueInt((int)pFVar4,"roundstowin",(uint *)(piVar10 + 0x2b92));
                  }
                  iVar5 = TPGroupSeek((int)pFVar4,"default ending");
                  if (iVar5 != -1) {
                    piVar10 = g + 0x2754;
                    TPGetValueInt((int)pFVar4,"enabled",(uint *)(g + 0x2753));
                    TPScanf((int)pFVar4,"storyboard","%s",piVar10);
                  }
                  iVar5 = TPGroupSeek((int)pFVar4,"end credits");
                  if (iVar5 != -1) {
                    piVar10 = g + 0x2353;
                    TPGetValueInt((int)pFVar4,"enabled",(uint *)(g + 0x2352));
                    TPScanf((int)pFVar4,"storyboard","%s",piVar10);
                  }
                  pcVar11 = BGArrayReadTP((char *)pFVar4,(char *)((int)g + 0x15aff),"TitleBG",
                                          g[0x5ac0],g[0x62c2]);
                  piVar10 = g;
                  g[0x62ce] = (int)pcVar11;
                  if (pcVar11 == (char *)0x0) {
                    piVar10 = piVar10 + 0x81d2;
                    pcVar11 = "Error loading TitleBG";
                    pFVar6 = extraout_ECX;
                    __src = extraout_ECX;
                  }
                  else {
                    pcVar11 = BGArrayReadTP((char *)pFVar4,(char *)((int)piVar10 + 0x15aff),
                                            "VersusBG",piVar10[0x5ac0],piVar10[0x62c2]);
                    piVar10 = g;
                    g[0x62cd] = (int)pcVar11;
                    if (pcVar11 == (char *)0x0) {
                      piVar10 = piVar10 + 0x81d2;
                      pcVar11 = "Error loading VersusBG";
                      pFVar6 = pFVar4;
                      __src = pFVar4;
                    }
                    else {
                      pFVar6 = (FILE *)piVar10[0x62c2];
                      pcVar11 = BGArrayReadTP((char *)pFVar4,(char *)((int)piVar10 + 0x15aff),
                                              "SelectBG",piVar10[0x5ac0],(int)pFVar6);
                      piVar10 = g;
                      g[0x62cf] = (int)pcVar11;
                      if (pcVar11 == (char *)0x0) {
                        piVar10 = piVar10 + 0x81d2;
                        pcVar11 = "Error loading SelectBG";
                        pFVar6 = extraout_ECX_00;
                        __src = extraout_ECX_00;
                      }
                      else {
                        pcVar11 = BGArrayReadTP((char *)pFVar4,(char *)((int)piVar10 + 0x15aff),
                                                "OptionBG",piVar10[0x5ac0],piVar10[0x62c2]);
                        piVar10 = g;
                        g[0x62d0] = (int)pcVar11;
                        if (pcVar11 != (char *)0x0) {
                          TPFree(&pFVar4->_flags);
                          iVar5 = FindFileDir(local_211c,(char *)local_111c,(char *)0x0);
                          if (iVar5 == 0) {
                            return 0;
                          }
                          iVar5 = GameLoadFightData(local_111c);
                          if (iVar5 == 0) {
                            strcat((char *)(g + 0x81d2),"\nError loading fight data: ");
                            strcat((char *)(g + 0x81d2),local_211c);
                            return 0;
                          }
                          return 1;
                        }
                        piVar10 = piVar10 + 0x81d2;
                        pcVar11 = "Error loading OptionBG";
                        __src = pFVar6;
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
  }
LAB_080d3985:
  sprintf((char *)piVar10,pcVar11,pFVar6,__src);
  return 0;
}
#undef local_2180
#undef local_217c
#undef local_216c
#undef local_2168
#undef local_2164
#undef local_2160
#undef local_215c
#undef local_2158
#undef local_2154
#undef local_214c
#undef local_213c
#undef local_2138
#undef local_2134
#undef local_2130
#undef local_212c
#undef local_2128
#undef local_2124
#undef local_211c
#undef local_111c
#undef local_11c

/* GameUnloadSystem @ 0x080d39b0, 393 bytes */
void GameUnloadSystem(void)

{
  void *pvVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  BGArrayFree(g[0x62d0]);
  piVar3 = g;
  g[0x62d0] = 0;
  BGArrayFree(piVar3[0x62cf]);
  piVar3 = g;
  g[0x62cf] = 0;
  BGArrayFree(piVar3[0x62cd]);
  piVar3 = g;
  g[0x62cd] = 0;
  BGArrayFree(piVar3[0x62ce]);
  piVar2 = g;
  piVar3 = g + 0x1b50;
  g[0x62ce] = 0;
  if (*piVar3 != 0) {
    iVar4 = 0;
    if (0 < piVar2[0x18e5] * piVar2[0x18e4]) {
      iVar5 = 0;
      do {
        piVar3 = *(int **)(piVar2[0x1b50] + 0x2034 + iVar5);
        if (piVar3 != (int *)0x0) {
          SpriteArrayFree(piVar3);
          piVar2 = g;
        }
        iVar4 = iVar4 + 1;
        iVar5 = iVar5 + 0x2038;
      } while (iVar4 < piVar2[0x18e5] * piVar2[0x18e4]);
    }
    free((void *)piVar2[0x1b50]);
  }
  iVar5 = 0x18b00;
  iVar4 = 9;
  piVar3 = g;
  do {
    pvVar1 = *(void **)(iVar5 + 0xc + (int)piVar3);
    if (pvVar1 != (void *)piVar3[0x413a]) {
      FontFree(pvVar1);
      piVar3 = g;
    }
    iVar5 = iVar5 + 4;
    iVar4 = iVar4 + -1;
  } while (-1 < iVar4);
  AnimRCFree((int *)piVar3[0x62c2]);
  SndArrayFree((undefined4 *)g[0x5ec1]);
  piVar3 = g;
  *(undefined1 *)(g + 0x5ec2) = 0;
  piVar3[0x5ec1] = 0;
  SpriteArrayFree((int *)g[0x5ac0]);
  piVar3 = g;
  g[0x5ac0] = 0;
  *(undefined1 *)(piVar3 + 0x5ac1) = 0;
  return;
}

/* GameReloadSystemSprSnd @ 0x080d3b40, 651 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x1010-byte frame (a local's address escapes, see apply_frame_emulation) */
int GameReloadSystemSprSnd(void)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  char *pcVar4;
  int iVar5;
  int *extraout_ECX;
  int *extraout_ECX_00;
  int *piVar6;
  int *piVar7;
  unsigned char ghidra_frame[0x1010] __attribute__((aligned(16)));
#define local_100c (*(char (*)[4104])(ghidra_frame + 0x4))
  
  piVar6 = g;
  if ((g[0x5ac0] == 0) && ((char)g[0x5ac1] != '\0')) {
    piVar1 = SpriteReadFile((char *)(g + 0x5ac1));
    piVar6 = g;
    g[0x5ac0] = (int)piVar1;
    if (piVar1 == (int *)0x0) {
      ErrorExitM("Out of memory loading system file %s",piVar6 + 0x5ac1);
      piVar6 = g;
    }
  }
  piVar1 = (int *)piVar6[0x5ec1];
  if ((piVar1 == (int *)0x0) && ((char)piVar6[0x5ec2] != '\0')) {
    piVar2 = SndReadFile((char *)(piVar6 + 0x5ec2));
    piVar6 = g;
    g[0x5ec1] = (int)piVar2;
    piVar1 = extraout_ECX;
    if (piVar2 == (int *)0x0) {
      ErrorExitM("Out of memory loading system file %s",piVar6 + 0x5ec2,0,0);
      piVar1 = extraout_ECX_00;
      piVar6 = g;
    }
  }
  if ((((piVar6[0x62ce] == 0) || (piVar1 = (int *)piVar6[0x62cd], piVar1 == (int *)0x0)) ||
      (iVar5 = piVar6[0x62cf], iVar5 == 0)) || (piVar6[0x62d0] == 0)) {
    piVar2 = piVar6 + 0x52c0;
    piVar6 = (int *)((int)piVar6 + 0x15aff);
    joindirfile(local_100c,(char *)piVar6,(char *)piVar2);
    piVar3 = TPReadFile(local_100c);
    if (piVar3 == (int *)0x0) {
      piVar6 = g + 0x52c0;
      piVar2 = piVar3;
      piVar1 = piVar3;
      ErrorExitM("Out of memory loading system file %s",piVar6,0,0);
    }
    piVar7 = g;
    if (g[0x62ce] == 0) {
      pcVar4 = BGArrayReadTP((char *)piVar3,(char *)((int)g + 0x15aff),"TitleBG",g[0x5ac0],g[0x62c2]
                            );
      piVar7 = g;
      g[0x62ce] = (int)pcVar4;
      if (pcVar4 == (char *)0x0) {
        ErrorExitM("Error reloading TitleBG",piVar6,piVar2,piVar1);
        piVar7 = g;
      }
    }
    if (piVar7[0x62cd] == 0) {
      pcVar4 = BGArrayReadTP((char *)piVar3,(char *)((int)piVar7 + 0x15aff),"VersusBG",
                             piVar7[0x5ac0],piVar7[0x62c2]);
      piVar7 = g;
      g[0x62cd] = (int)pcVar4;
      if (pcVar4 == (char *)0x0) {
        ErrorExitM("Error reloading VersusBG",piVar6,piVar2,piVar1);
        piVar7 = g;
      }
    }
    if (piVar7[0x62cf] == 0) {
      pcVar4 = BGArrayReadTP((char *)piVar3,(char *)((int)piVar7 + 0x15aff),"SelectBG",
                             piVar7[0x5ac0],piVar7[0x62c2]);
      piVar7 = g;
      g[0x62cf] = (int)pcVar4;
      if (pcVar4 == (char *)0x0) {
        ErrorExitM("Error reloading SelectBG");
        piVar7 = g;
      }
    }
    if (piVar7[0x62d0] == 0) {
      pcVar4 = BGArrayReadTP((char *)piVar3,(char *)((int)piVar7 + 0x15aff),"OptionBG",
                             piVar7[0x5ac0],piVar7[0x62c2]);
      g[0x62d0] = (int)pcVar4;
      if (pcVar4 == (char *)0x0) {
        ErrorExitM("Error reloading OptionBG");
      }
    }
    iVar5 = TPFree(piVar3);
  }
  return iVar5;
}
#undef local_100c

/* GameUnloadSystemSprSnd @ 0x080d3dd0, 151 bytes */
void GameUnloadSystemSprSnd(void)

{
  int *piVar1;
  
  BGArrayFree(g[0x62d0]);
  piVar1 = g;
  g[0x62d0] = 0;
  BGArrayFree(piVar1[0x62cf]);
  piVar1 = g;
  g[0x62cf] = 0;
  BGArrayFree(piVar1[0x62cd]);
  piVar1 = g;
  g[0x62cd] = 0;
  BGArrayFree(piVar1[0x62ce]);
  piVar1 = g;
  g[0x62ce] = 0;
  SpriteArrayFree((int *)piVar1[0x5ac0]);
  g[0x5ac0] = 0;
  return;
}

/* GameConfigRead @ 0x080d3e70, 4132 bytes
 * FIXUP: 10 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: shared sprintf() call: 19 formats, arguments recovered for 6, others passed as 0
 * FIXUP: frame emulation: 7 stack locals placed at their original offsets in a 0x140-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 GameConfigRead(char *param_1)

{
  void *ghidra_fa[1] = {0};
  char cVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  int *piVar8;
  undefined3 extraout_var_07;
  undefined3 extraout_var_08;
  void *pvVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  char *pcVar13;
  void *pvVar14;
  unsigned char ghidra_frame[0x140] __attribute__((aligned(16)));
#define local_134 (*(int **)(ghidra_frame + 0xc))
#define local_130 (*(int **)(ghidra_frame + 0x10))
#define local_12c (*(uint *)(ghidra_frame + 0x14))
#define local_128 (*(uint *)(ghidra_frame + 0x18))
#define local_124 (*(int *)(ghidra_frame + 0x1c))
#define local_120 (*(int **)(ghidra_frame + 0x20))
#define local_11c (*(char (*)[268])(ghidra_frame + 0x24))
  
  puVar6 = TPReadFile(param_1);
  if ((puVar6 == (undefined4 *)0x0) && (puVar6 = TPReadFile(param_1), puVar6 == (undefined4 *)0x0))
  {
    piVar8 = g + 0x81d2;
    ghidra_fa[0] = (void *)(param_1);
    pcVar13 = "Can\'t open %s. Make sure you have extracted with directories";
    goto LAB_080d4c73;
  }
  iVar7 = TPGroupSeek((int)puVar6,"Rules");
  if (iVar7 == -1) {
    piVar8 = g + 0x81d2;
    pcVar13 = "Can\'t load rules.";
    goto LAB_080d4c73;
  }
  pcVar13 = TPGetValue((int)puVar6,"gametype");
  if (pcVar13 == (char *)0x0) {
    piVar8 = g + 0x81d2;
    pcVar13 = "Can\'t get game type.";
    goto LAB_080d4c73;
  }
  iVar7 = *(int *)(__ctype_tolower + *pcVar13 * 4);
  if (iVar7 == 0x6d) {
    g[0x731d] = 1;
  }
  else {
    if (iVar7 != 0x76) {
      piVar8 = g + 0x81d2;
      pcVar13 = "Can\'t get game type.";
      goto LAB_080d4c73;
    }
    g[0x731d] = 0;
  }
  piVar8 = g;
  g[0x731e] = 0x40400000;
  piVar8[0x731f] = 0x40000000;
  piVar8[0x7320] = 0x3f800000;
  TPGetValueFloat((int)puVar6,"default.attack.lifetopowermul",(float *)(piVar8 + 0x731e));
  TPGetValueFloat((int)puVar6,"default.gethit.lifetopowermul",(float *)(g + 0x731f));
  TPGetValueFloat((int)puVar6,"super.targetdefencemul",(float *)(g + 0x7320));
  iVar7 = TPGroupSeek((int)puVar6,"config");
  piVar8 = g;
  if (iVar7 == -1) {
    piVar8 = g + 0x81d2;
    pcVar13 = "Can\'t access config.";
    goto LAB_080d4c73;
  }
  g[0x756f] = 0x3c;
  piVar8[0x7570] = 1;
  TPGetValueInt((int)puVar6,"gamespeed",(uint *)(piVar8 + 0x756f));
  TPGetValueInt((int)puVar6,"drawshadows",(uint *)(g + 0x7570));
  TPGetValueInt((int)puVar6,"afterimagemax",(uint *)(g + 0x7571));
  piVar8 = g;
  if (g[0x7571] < 1) {
    g[0x7571] = 1;
  }
  TPGetValueInt((int)puVar6,"layeredspritemax",(uint *)(piVar8 + 0x7572));
  piVar8 = g;
  if (g[0x7572] < 0x20) {
    g[0x7572] = 0x20;
  }
  TPGetValueInt((int)puVar6,"explodmax",(uint *)(piVar8 + 0x7573));
  piVar8 = g;
  if (g[0x7573] < 8) {
    g[0x7573] = 8;
  }
  TPGetValueInt((int)puVar6,"sysexplodmax",(uint *)(piVar8 + 0x7574));
  piVar8 = g;
  if (g[0x7574] < 8) {
    g[0x7574] = 8;
  }
  TPGetValueInt((int)puVar6,"helpermax",(uint *)(piVar8 + 0x7575));
  piVar8 = g;
  if (g[0x7575] < 4) {
    g[0x7575] = 4;
  }
  if (0x38 < piVar8[0x7575]) {
    piVar8[0x7575] = 0x38;
    piVar8 = g;
  }
  TPGetValueInt((int)puVar6,"playerprojectilemax",(uint *)(piVar8 + 0x7576));
  piVar8 = g;
  if (g[0x7576] < 5) {
    g[0x7576] = 5;
  }
  TPGetValueInt((int)puVar6,"playerpalmax",(uint *)(piVar8 + 0x7577));
  piVar8 = g;
  if (g[0x7577] < 0xc) {
    g[0x7577] = 0xc;
  }
  TPGetValueInt((int)puVar6,"firstrun",(uint *)(piVar8 + 0x7578));
  iVar7 = TPGroupSeek((int)puVar6,"Debug");
  if (iVar7 != -1) {
    TPGetValueInt((int)puVar6,"debug",(uint *)(g + 0x81cd));
    TPGetValueInt((int)puVar6,"allowdebugmode",(uint *)(g + 0x81ce));
    TPGetValueInt((int)puVar6,"allowdebugkeys",(uint *)(g + 0x81cf));
    piVar8 = g;
    if (g[0x81cd] != 0) {
      g[0x81ce] = 1;
      TPGetValueInt((int)puVar6,"speedup",(uint *)(piVar8 + 0x82d2));
    }
    pcVar13 = TPGetValue((int)puVar6,"startstage");
    if (pcVar13 != (char *)0x0) {
      strncpy((char *)(g + 0x7dc4),pcVar13,0xfff);
    }
  }
  iVar7 = TPGroupSeek((int)puVar6,"video linux");
  if (iVar7 == -1) {
    piVar8 = g + 0x81d2;
    ghidra_fa[0] = (void *)("video linux");
    pcVar13 = "Can\'t load video config: [%s]";
    goto LAB_080d4c73;
  }
  bVar2 = TPGetValueInt((int)puVar6,"width",(uint *)(g + 0x7553));
  bVar3 = TPGetValueInt((int)puVar6,"height",(uint *)(g + 0x7554));
  bVar4 = TPGetValueInt((int)puVar6,"depth",(uint *)(g + 0x7555));
  bVar5 = TPGetValueInt((int)puVar6,"vretrace",(uint *)(g + 0x755a));
  piVar8 = g;
  if ((GHIDRA_ZEXT8(bVar2) & GHIDRA_ZEXT8(bVar3) &
       GHIDRA_ZEXT8(bVar4) & GHIDRA_ZEXT8(bVar5)) != 1) {
    piVar8 = g + 0x81d2;
    pcVar13 = "Can\'t read video config.";
    goto LAB_080d4c73;
  }
  g[0x7558] = 0;
  TPGetValueInt((int)puVar6,"stretch",(uint *)(piVar8 + 0x7558));
  piVar8 = g;
  g[0x7559] = 0;
  TPGetValueInt((int)puVar6,"doubleres",(uint *)(piVar8 + 0x7559));
  piVar8 = g;
  if (g[0x7559] < 0) {
    g[0x7559] = 0;
  }
  if (4 < piVar8[0x7559]) {
    piVar8[0x7559] = 4;
    piVar8 = g;
  }
  piVar8[0x7556] = 1;
  pcVar13 = TPGetValue((int)puVar6,"fullscreen");
  piVar8 = g;
  if (pcVar13 != (char *)0x0) {
    cVar1 = *pcVar13;
    iVar7 = *(int *)(__ctype_tolower + cVar1 * 4);
    if (iVar7 == 0x30) {
      g[0x7556] = 2;
    }
    else if (iVar7 == 0x31) {
      g[0x7556] = 1;
    }
    else {
      g[0x7556] = 0;
      sprintf((char *)(piVar8 + 0x81d2),"Unrecognised option: %s.  Trying to autodetect...",pcVar13,
              (int)cVar1);
    }
  }
  if (*(code **)(system_driver + 0x6c) == (code *)0x0) {
    local_130 = (int *)0x0;
  }
  else {
    local_130 = (int *)(**(code **)(system_driver + 0x6c))();
  }
  piVar8 = g;
  if (((local_130 != (int *)0x0) && (local_130 != (int *)g[0x7555])) && (g[0x7556] == 2)) {
    g[0x7555] = (int)local_130;
  }
  piVar8[0x7557] = 0;
  pcVar13 = TPGetValue((int)puVar6,"blitmode");
  if (pcVar13 != (char *)0x0) {
    iVar7 = *(int *)(__ctype_tolower + *pcVar13 * 4);
    if (iVar7 == 0x70) {
      g[0x7557] = 1;
    }
    else if (iVar7 < 0x71) {
      if (iVar7 != 0x6e) {
LAB_080d44f2:
        piVar8 = g + 0x81d2;
        ghidra_fa[0] = (void *)(pcVar13);
        pcVar13 = "Unrecognised BlitMode: %s";
        goto LAB_080d4c73;
      }
      g[0x7557] = 0;
    }
    else {
      if (iVar7 != 0x74) goto LAB_080d44f2;
      g[0x7557] = 2;
    }
  }
  iVar7 = TPGroupSeek((int)puVar6,"sound linux");
  piVar8 = g;
  if (iVar7 == -1) {
    piVar8 = g + 0x81d2;
    ghidra_fa[0] = (void *)("sound linux");
    pcVar13 = "Can\'t load sound config: [%s]";
  }
  else {
    g[0x6ef4] = 0xaf;
    piVar8[0x6ef5] = 200;
    piVar8[0x6ef9] = 0xaf;
    piVar8[0x6ef8] = 0xaf;
    piVar8[0x6ef6] = -1;
    piVar8[0x6ef3] = 1;
    piVar8[0x756c] = 1;
    piVar8[0x756d] = 0xa0;
    TPGetValueInt((int)puVar6,"sound",(uint *)(piVar8 + 0x6ef3));
    TPGetValueInt((int)puVar6,"stereoeffects",(uint *)(g + 0x756c));
    TPGetValueInt((int)puVar6,"panningwidth",(uint *)(g + 0x756d));
    bVar2 = TPGetValueInt((int)puVar6,"reversestereo",(uint *)&local_130);
    if (GHIDRA_ZEXT8(bVar2) != 0) {
      SndSetReverseStereo((int)local_130);
    }
    TPGetValueInt((int)puVar6,"pausebgmondefocus",(uint *)(g + 0x756e));
    TPGetValueInt((int)puVar6,"masterwavvolume",(uint *)(g + 0x6ef5));
    TPGetValueInt((int)puVar6,"wavvolume",(uint *)(g + 0x6ef4));
    TPGetValueInt((int)puVar6,"midivolume",(uint *)(g + 0x6ef7));
    TPGetValueInt((int)puVar6,"mp3volume",(uint *)(g + 0x6ef8));
    TPGetValueInt((int)puVar6,"modvolume",(uint *)(g + 0x6ef9));
    TPGetValueInt((int)puVar6,"cdavolume",(uint *)(g + 0x6ef6));
    piVar8 = g;
    g[0x7562] = 1;
    piVar8[0x7561] = 1;
    piVar8[0x7560] = 1;
    piVar8[0x7563] = 1;
    TPGetValueInt((int)puVar6,"playcda",(uint *)(piVar8 + 0x7563));
    TPGetValueInt((int)puVar6,"playmp3",(uint *)(g + 0x7560));
    TPGetValueInt((int)puVar6,"playmidi",(uint *)(g + 0x7561));
    TPGetValueInt((int)puVar6,"playmod",(uint *)(g + 0x7562));
    pcVar13 = TPGetValue((int)puVar6,"cdadevice");
    if (pcVar13 != (char *)0x0) {
      strncpy((char *)(g + 0x7564),pcVar13,0x1f);
    }
    g[0x755b] = -1;
    pcVar13 = TPGetValue((int)puVar6,"wavdevice");
    if (pcVar13 != (char *)0x0) {
      iVar7 = SndParseWavDevice(pcVar13);
      piVar8 = g;
      g[0x755b] = iVar7;
      if (iVar7 == -2) {
        piVar8 = piVar8 + 0x81d2;
        ghidra_fa[0] = (void *)(pcVar13);
        pcVar13 = "Invalid wav device: %s";
        goto LAB_080d4c73;
      }
    }
    piVar8 = g;
    g[0x755d] = 8;
    TPGetValueInt((int)puVar6,"wavchannels",(uint *)(piVar8 + 0x755d));
    TPGetValueInt((int)puVar6,"modvoices",(uint *)(g + 0x755e));
    g[0x755c] = -1;
    pcVar13 = TPGetValue((int)puVar6,"mididevice");
    if (pcVar13 != (char *)0x0) {
      iVar7 = SndParseMidiDevice(pcVar13);
      piVar8 = g;
      g[0x755c] = iVar7;
      if (iVar7 == -2) {
        piVar8 = piVar8 + 0x81d2;
        ghidra_fa[0] = (void *)(pcVar13);
        pcVar13 = "Invalid midi device: %s";
        goto LAB_080d4c73;
      }
    }
    iVar7 = TPGroupSeek((int)puVar6,"Misc");
    piVar8 = g;
    if (iVar7 == -1) {
      piVar8 = g + 0x81d2;
      pcVar13 = "Can\'t load misc config.";
    }
    else {
      g[0x7579] = 0;
      TPGetValueInt((int)puVar6,"playercache",(uint *)(piVar8 + 0x7579));
      piVar8 = g;
      g[0x7579] = g[0x7579] + 2;
      piVar8[0x757a] = 0;
      TPGetValueInt((int)puVar6,"precache",(uint *)(piVar8 + 0x757a));
      bVar2 = TPGetValueInt((int)puVar6,"bufferedread",(uint *)&local_130);
      if (GHIDRA_ZEXT8(bVar2) != 0) {
        SpriteSetBufReadMode(local_130);
        SndSetBufReadMode(local_130);
        g[0x757b] = (int)local_130;
      }
      TPGetValueInt((int)puVar6,"unloadsystem",(uint *)(g + 0x757c));
      TPGetValueInt((int)puVar6,"pauseondefocus",(uint *)(g + 0x757d));
      piVar8 = g;
      if (g[0x757d] != 0) {
        g[0x756e] = 1;
      }
      iVar7 = TPScanf((int)puVar6,"expires","%i,%i,%i,%x",&local_128,&local_12c,&local_124,
                      &local_120,piVar8);
      if ((iVar7 == 4) &&
         (local_130 = (int *)((int)((local_12c ^ local_128) * local_124 -
                                    (MUGENDATE_M ^ MUGENDATE_D) ^ MUGENDATE_Y) % 0x10000),
         local_120 == local_130)) {
        MUGENEXPDATE_D = local_12c;
        MUGENEXPDATE_M = local_128;
        MUGENEXPDATE_Y = local_124;
      }
      iVar7 = TPGroupSeek((int)puVar6,"Arcade");
      if (iVar7 == -1) {
        piVar8 = g + 0x81d2;
        pcVar13 = "Can\'t load arcade config.";
      }
      else {
        TPGetValueInt((int)puVar6,"ai.randomcolor",(uint *)(g + 0x757e));
        local_130 = (int *)0x0;
        do {
          if (local_130 == (int *)0x1) {
            pcVar13 = "team";
            local_134 = g + 0x7584;
            piVar8 = local_134;
          }
          else {
            piVar8 = local_130;
            if ((int)local_130 < 2) {
              if (local_130 == (int *)0x0) {
                pcVar13 = "arcade";
                local_134 = g + 0x7580;
                piVar8 = local_134;
              }
            }
            else if (local_130 == (int *)0x2) {
              pcVar13 = "survival";
              local_134 = g + 0x7588;
              piVar8 = local_134;
            }
          }
          sprintf(local_11c,"%s.AIramp.start",pcVar13,piVar8);
          TPScanf((int)puVar6,local_11c,"%i,%i",local_134,local_134 + 1);
          sprintf(local_11c,"%s.AIramp.end",pcVar13);
          TPScanf((int)puVar6,local_11c,"%i,%i",local_134 + 2,local_134 + 3);
          local_130 = (int *)((int)local_130 + 1);
        } while ((int)local_130 < 3);
        iVar7 = TPGroupSeek((int)puVar6,"Input");
        if (iVar7 == -1) {
          piVar8 = g + 0x81d2;
          pcVar13 = "Can\'t load input config.";
        }
        else {
          TPGetValueInt((int)puVar6,"p1.usekeyboard",(uint *)(g + 0x7389));
          TPGetValueInt((int)puVar6,"p2.usekeyboard",(uint *)(g + 0x738a));
          TPGetValueInt((int)puVar6,"p1.joystick.type",(uint *)(g + 0x738d));
          TPGetValueInt((int)puVar6,"p2.joystick.type",(uint *)(g + 0x738e));
          piVar8 = g;
          iVar7 = g[0x738e];
          iVar10 = g[0x738d];
          g[0x738b] = (uint)(iVar10 != 0);
          piVar8[0x738c] = (uint)(iVar7 != 0);
          iVar11 = 0;
          if (((iVar10 != 0) != 0) || ((iVar7 != 0) != 0)) {
            iVar11 = 1;
          }
          piVar8[0x738f] = iVar11;
          TPGetValueInt((int)puVar6,"forcefeedback",(uint *)(g + 0x738f));
          TPGetValueInt((int)puVar6,"psxdelay",(uint *)(g + 0x7390));
          if ((g[0x7389] == 0) ||
             (bVar2 = PlayerLoadKeys((int)puVar6,(int)(g + 0x7321),"p1 keys"),
             GHIDRA_ZEXT8(bVar2) != 0)) {
            PlayerKeysRemoveZero((int)(g + 0x7321),0x100);
            if ((g[0x738a] == 0) ||
               (bVar2 = PlayerLoadKeys((int)puVar6,(int)(g + 0x732e),"p2 keys"),
               GHIDRA_ZEXT8(bVar2) != 0)) {
              iVar7 = iVar11;
              PlayerKeysRemoveZero((int)(g + 0x732e),0x100);
              piVar8 = g;
              g[0x7370] = 1;
              piVar8[0x7372] = 2;
              piVar8[0x7373] = 3;
              piVar8[0x7371] = 4;
              piVar12 = piVar8 + 0x736f;
              piVar8 = piVar8 + 0x737c;
              for (iVar10 = 0xd; iVar10 != 0; iVar10 = iVar10 + -1) {
                *piVar8 = *piVar12;
                piVar12 = piVar12 + 1;
                piVar8 = piVar8 + 1;
              }
              sprintf(local_11c,"P1 joystick",iVar11,iVar7);
              bVar2 = PlayerLoadKeys((int)puVar6,(int)(g + 0x736f),local_11c);
              iVar7 = GHIDRA_ZEXT8(bVar2);
              if (iVar7 != 0) {
                printf("Loading button config for %s.\n",local_11c,iVar7,iVar7);
              }
              sprintf(local_11c,"P2 joystick",piVar8,piVar8);
              bVar2 = PlayerLoadKeys((int)puVar6,(int)(g + 0x737c),local_11c);
              if (GHIDRA_ZEXT8(bVar2) != 0) {
                printf("Loading button config for %s.\n",local_11c,piVar12,piVar12);
              }
              piVar8 = g + 0x736f;
              piVar12 = g + 0x7355;
              for (iVar7 = 0xd; iVar7 != 0; iVar7 = iVar7 + -1) {
                *piVar12 = *piVar8;
                piVar8 = piVar8 + 1;
                piVar12 = piVar12 + 1;
              }
              piVar8 = g + 0x737c;
              piVar12 = g + 0x7362;
              for (iVar7 = 0xd; iVar7 != 0; iVar7 = iVar7 + -1) {
                *piVar12 = *piVar8;
                piVar8 = piVar8 + 1;
                piVar12 = piVar12 + 1;
              }
              if (g[0x738b] == 0) {
                piVar8 = g + 0x7355;
                for (iVar7 = 0xd; iVar7 != 0; iVar7 = iVar7 + -1) {
                  *piVar8 = 0;
                  piVar8 = piVar8 + 1;
                }
              }
              if (g[0x738c] == 0) {
                piVar8 = g + 0x7362;
                for (iVar7 = 0xd; iVar7 != 0; iVar7 = iVar7 + -1) {
                  *piVar8 = 0;
                  piVar8 = piVar8 + 1;
                }
              }
              PlayerKeysRemoveZero((int)(g + 0x7355),0x80);
              PlayerKeysRemoveZero((int)(g + 0x7362),0x80);
              PlayerKeysRemoveZero((int)(g + 0x736f),0x80);
              PlayerKeysRemoveZero((int)(g + 0x737c),0x80);
              TPFree(puVar6);
              if ((g[0x7578] != 0) && (pvVar9 = TPReadFileForWrite(param_1), pvVar9 != (void *)0x0))
              {
                pvVar14 = pvVar9;
                TPGroupSeek((int)pvVar9,"Config");
                TPPrintf((int)pvVar9,"FirstRun","0",pvVar14);
                TPWriteFile((int)pvVar9,param_1);
              }
              return 1;
            }
            piVar8 = g + 0x81d2;
            pcVar13 = "Can\'t read p2 key config.";
          }
          else {
            piVar8 = g + 0x81d2;
            pcVar13 = "Can\'t read p1 key config.";
          }
        }
      }
    }
  }
LAB_080d4c73:
  sprintf((char *)piVar8,pcVar13,ghidra_fa[0]);
  return 0;
}
#undef local_134
#undef local_130
#undef local_12c
#undef local_128
#undef local_124
#undef local_120
#undef local_11c

/* GameResetOptions @ 0x080d4ea0, 66 bytes */
void GameResetOptions(void)

{
  int *piVar1;
  
  piVar1 = g;
  g[0x799e] = 4;
  piVar1[0x799f] = 100;
  piVar1[0x79a0] = 99;
  piVar1[0x79a1] = 0;
  piVar1[0x79a2] = 0x32;
  piVar1[0x79a3] = 0x32;
  return;
}

/* GameLoadOptions @ 0x080d4ef0, 745 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
undefined4 GameLoadOptions(void)

{
  int *piVar1;
  int *piVar2;
  bool bVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined3 extraout_var;
  undefined4 uStack_c;
  
  puVar4 = TPReadFile("data/mugen.cfg");
  if (puVar4 == (undefined4 *)0x0) {
    sprintf((char *)(g + 0x81d2),"Error loading options",0,0);
    ErrorExit();
  }
  iVar5 = TPGroupSeek((int)puVar4,"Options");
  if (iVar5 != -1) {
    TPGetValueInt((int)puVar4,"Difficulty",(uint *)(g + 0x799e));
    TPGetValueInt((int)puVar4,"Life",(uint *)(g + 0x799f));
    TPGetValueInt((int)puVar4,"Time",(uint *)(g + 0x79a0));
    TPGetValueInt((int)puVar4,"GameSpeed",(uint *)(g + 0x79a1));
    TPGetValueInt((int)puVar4,"WavVolume",(uint *)(g + 0x79a2));
    TPGetValueInt((int)puVar4,"MidiVolume",(uint *)(g + 0x79a3));
    TPScanf((int)puVar4,"motif","%s",g + 0x79b8);
    if ((char)g[0x79b8] == '\0') {
      memcpy(g + 0x79b8,"data/system.def",0x10);
    }
    splitdirfile((char *)(g + 0x79b8),(char *)((int)g + 0x15aff),(char *)(g + 0x52c0));
    TPGetValueInt((int)puVar4,"Team.1VS2Life",(uint *)(g + 0x79b4));
    TPGetValueInt((int)puVar4,"Team.LoseOnKO",(uint *)(g + 0x79b5));
  }
  piVar1 = g;
  g[0x79a9] = 1;
  PlayerLoadKeys((int)puVar4,(int)(piVar1 + 0x7321),"p1 keys");
  PlayerLoadKeys((int)puVar4,(int)(g + 0x732e),"p2 keys");
  PlayerKeysRemoveZero((int)(g + 0x7321),0x100);
  PlayerKeysRemoveZero((int)(g + 0x732e),0x100);
  iVar5 = TPGroupSeek((int)puVar4,"Input");
  if (iVar5 != -1) {
    TPGetValueInt((int)puVar4,"p1.joystick.type",(uint *)(g + 0x79ab));
    TPGetValueInt((int)puVar4,"p2.joystick.type",(uint *)(g + 0x79b0));
  }
  piVar2 = g;
  piVar1 = g + 0x79ab;
  iVar5 = g[0x79b0];
  g[0x738d] = *piVar1;
  piVar2[0x738b] = (uint)(*piVar1 != 0);
  piVar2[0x738e] = iVar5;
  piVar2[0x738c] = (uint)(iVar5 != 0);
  PlayerLoadKeys((int)puVar4,(int)(piVar2 + 0x736f),"P1 joystick");
  PlayerLoadKeys((int)puVar4,(int)(g + 0x737c),"P2 joystick");
  PlayerKeysRemoveZero((int)(g + 0x736f),0x80);
  PlayerKeysRemoveZero((int)(g + 0x737c),0x80);
  TPFree(puVar4);
  GameInitPads();
  bVar3 = GameInputSetup();
  if (GHIDRA_ZEXT8(bVar3) == 0) {
    ErrorExitM("Cannot init input");
  }
  return uStack_c;
}

/* GameSaveOptions @ 0x080d51e0, 667 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x60-byte frame (a local's address escapes, see apply_frame_emulation) */
void GameSaveOptions(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 extraout_EDX;
  int *piVar3;
  int *piVar4;
  unsigned char ghidra_frame[0x60] __attribute__((aligned(16)));
#define aiStack_5c (*(int (*)[19])(ghidra_frame + 0x4))
  
  puVar1 = TPReadFileForWrite("data/mugen.cfg");
  if (puVar1 == (undefined4 *)0x0) {
    sprintf((char *)(g + 0x81d2),"Error saving options");
    ErrorExit();
  }
  iVar2 = TPGroupSeek((int)puVar1,"Options");
  if (iVar2 != -1) {
    TPPrintf((int)puVar1,"Difficulty","%i",g[0x799e]);
    TPPrintf((int)puVar1,"Life","%i",g[0x799f]);
    TPPrintf((int)puVar1,"Time","%i",g[0x79a0]);
    TPPrintf((int)puVar1,"GameSpeed","%i",g[0x79a1]);
    TPPrintf((int)puVar1,"WavVolume","%i",g[0x79a2]);
    TPPrintf((int)puVar1,"MidiVolume","%i",g[0x79a3]);
    TPPrintf((int)puVar1,"Team.1VS2Life","%i",g[0x79b4]);
    TPPrintf((int)puVar1,"Team.LoseOnKO","%i",g[0x79b5]);
  }
  iVar2 = TPGroupSeek((int)puVar1,"Input");
  if (iVar2 != -1) {
    TPPrintf((int)puVar1,"p1.joystick.type","%i",g[0x79ab]);
    TPPrintf((int)puVar1,"p2.joystick.type","%i",g[0x79b0]);
  }
  piVar3 = g + 0x7321;
  piVar4 = aiStack_5c;
  for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar4 = *piVar3;
    piVar3 = piVar3 + 1;
    piVar4 = piVar4 + 1;
  }
  PlayerKeysConvertToZero((int)aiStack_5c,0x100);
  PlayerSaveKeys((int)puVar1,aiStack_5c,"p1 keys");
  piVar3 = g + 0x732e;
  piVar4 = aiStack_5c;
  for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar4 = *piVar3;
    piVar3 = piVar3 + 1;
    piVar4 = piVar4 + 1;
  }
  PlayerKeysConvertToZero((int)aiStack_5c,0x100);
  PlayerSaveKeys((int)puVar1,aiStack_5c,"p2 keys");
  piVar3 = g + 0x736f;
  piVar4 = aiStack_5c;
  for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar4 = *piVar3;
    piVar3 = piVar3 + 1;
    piVar4 = piVar4 + 1;
  }
  PlayerKeysConvertToZero((int)aiStack_5c,0x80);
  PlayerSaveKeys((int)puVar1,aiStack_5c,"p1 joystick");
  piVar3 = g + 0x737c;
  piVar4 = aiStack_5c;
  for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar4 = *piVar3;
    piVar3 = piVar3 + 1;
    piVar4 = piVar4 + 1;
  }
  PlayerKeysConvertToZero((int)aiStack_5c,0x80);
  PlayerSaveKeys((int)puVar1,aiStack_5c,"p2 joystick");
  iVar2 = TPWriteFile((int)puVar1,"data/mugen.cfg");
  if (iVar2 == 0) {
    sprintf((char *)(g + 0x81d2),"Error saving options",extraout_EDX,extraout_EDX);
    ErrorExit();
  }
  TPFree(puVar1);
  return;
}
#undef aiStack_5c

/* PlayerLoadKeys @ 0x080d5480, 246 bytes */
bool PlayerLoadKeys(int param_1,int param_2,char *param_3)

{
  int iVar1;
  
  iVar1 = TPGroupSeek(param_1,param_3);
  if (iVar1 != -1) {
    TPGetValueInt(param_1,"Jump",(uint *)(param_2 + 4));
    TPGetValueInt(param_1,"Crouch",(uint *)(param_2 + 0xc));
    TPGetValueInt(param_1,"Left",(uint *)(param_2 + 0x10));
    TPGetValueInt(param_1,"Right",(uint *)(param_2 + 8));
    TPGetValueInt(param_1,"A",(uint *)(param_2 + 0x14));
    TPGetValueInt(param_1,"B",(uint *)(param_2 + 0x18));
    TPGetValueInt(param_1,"C",(uint *)(param_2 + 0x1c));
    TPGetValueInt(param_1,"X",(uint *)(param_2 + 0x20));
    TPGetValueInt(param_1,"Y",(uint *)(param_2 + 0x24));
    TPGetValueInt(param_1,"Z",(uint *)(param_2 + 0x28));
    TPGetValueInt(param_1,"Start",(uint *)(param_2 + 0x2c));
  }
  return iVar1 != -1;
}

/* PlayerSaveKeys @ 0x080d5580, 276 bytes */
void PlayerSaveKeys(int param_1,int param_2,char *param_3)

{
  int iVar1;
  
  iVar1 = TPGroupSeek(param_1,param_3);
  if (iVar1 != -1) {
    TPPrintf(param_1,"Jump","%i",*(undefined4 *)(param_2 + 4));
    TPPrintf(param_1,"Crouch","%i",*(undefined4 *)(param_2 + 0xc));
    TPPrintf(param_1,"Left","%i",*(undefined4 *)(param_2 + 0x10));
    TPPrintf(param_1,"Right","%i",*(undefined4 *)(param_2 + 8));
    TPPrintf(param_1,"A","%i",*(undefined4 *)(param_2 + 0x14));
    TPPrintf(param_1,"B","%i",*(undefined4 *)(param_2 + 0x18));
    TPPrintf(param_1,"C","%i",*(undefined4 *)(param_2 + 0x1c));
    TPPrintf(param_1,"X","%i",*(undefined4 *)(param_2 + 0x20));
    TPPrintf(param_1,"Y","%i",*(undefined4 *)(param_2 + 0x24));
    TPPrintf(param_1,"Z","%i",*(undefined4 *)(param_2 + 0x28));
    TPPrintf(param_1,"Start","%i",*(undefined4 *)(param_2 + 0x2c));
  }
  return;
}

/* PlayerKeysRemoveZero @ 0x080d56a0, 36 bytes */
void PlayerKeysRemoveZero(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 4;
  iVar2 = 0xb;
  do {
    if (*(int *)(param_1 + iVar1) == 0) {
      *(undefined4 *)(param_1 + iVar1) = param_2;
    }
    iVar1 = iVar1 + 4;
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  return;
}

/* PlayerKeysConvertToZero @ 0x080d56d0, 39 bytes */
void PlayerKeysConvertToZero(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 4;
  iVar2 = 0xb;
  do {
    if (*(int *)(param_1 + iVar1) == param_2) {
      *(undefined4 *)(param_1 + iVar1) = 0;
    }
    iVar1 = iVar1 + 4;
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  return;
}

