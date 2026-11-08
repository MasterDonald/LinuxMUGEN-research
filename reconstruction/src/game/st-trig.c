/*
 * st-trig.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x080ca000-0x080d0821, 9 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* SCtrlParseTrigger @ 0x080ca000, 12010 bytes
 * REVIEW: type-prop
 * FIXUP: call to 0x08102020 (Ghidra label gcc2_compiled.) renamed to its symbol _alemu_strlwr
 * FIXUP: 23 data addresses written as literals replaced by data-image references
 * FIXUP: 4 dead flag initialisations of inlined repz cmpsb loops set to constants
 * FIXUP: shared sprintf() call: 14 formats, arguments recovered for 12, others passed as 0
 * FIXUP: frame emulation: 22 stack locals placed at their original offsets in a 0x7f0-byte frame (a local's address escapes, see apply_frame_emulation) */
/* WARNING: Type propagation algorithm not settling */

char * SCtrlParseTrigger(char *param_1,int param_2,undefined4 *param_3,void *param_4,int param_5,
                        int *param_6)

{
  void *ghidra_fa[2] = {0};
  byte bVar1;
  ushort uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  char cVar6;
  undefined4 *puVar7;
  int *piVar8;
  byte *pbVar9;
  uint uVar10;
  undefined4 *puVar11;
  int *piVar12;
  bool bVar13;
  bool bVar14;
  bool bVar15;
  byte *pbVar16;
  char *pcVar17;
  unsigned char ghidra_frame[0x7f0] __attribute__((aligned(16)));
#define local_7ec (*(char **)(ghidra_frame + 0x4))
#define local_7e8 (*(char **)(ghidra_frame + 0x8))
#define local_7e4 (*(char **)(ghidra_frame + 0xc))
#define local_7e0 (*(char **)(ghidra_frame + 0x10))
#define local_7dc (*(byte (*)[256])(ghidra_frame + 0x14))
#define local_6dc (*(char (*)[256])(ghidra_frame + 0x114))
#define local_5dc (*(char (*)[256])(ghidra_frame + 0x214))
#define local_4dc (*(byte (*)[256])(ghidra_frame + 0x314))
#define local_3dc (*(int (*)[5])(ghidra_frame + 0x414))
#define local_3c8 (*(uint *)(ghidra_frame + 0x428))
#define local_3c4 (*(uint *)(ghidra_frame + 0x42c))
#define local_3c0 (*(uint *)(ghidra_frame + 0x430))
#define local_3bc (*(undefined4 *)(ghidra_frame + 0x434))
#define local_3b8 (*(uint *)(ghidra_frame + 0x438))
#define local_3b4 (*(uint *)(ghidra_frame + 0x43c))
#define local_3a8 (*(char **)(ghidra_frame + 0x448))
#define local_39c (*(char (*)[128])(ghidra_frame + 0x454))
#define local_31c (*(undefined4 (*)[128])(ghidra_frame + 0x4d4))
#define local_11c (*(char (*)[4])(ghidra_frame + 0x6d4))
#define local_118 (*(char (*)[3])(ghidra_frame + 0x6d8))
#define local_115 (*(byte (*)[4])(ghidra_frame + 0x6db))
#define local_111 (*(byte (*)[257])(ghidra_frame + 0x6df))
  
  local_7ec = (char *)0x0;
  piVar8 = local_3dc;
  for (iVar5 = 0xe; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar8 = 0;
    piVar8 = piVar8 + 1;
  }
  local_7e8 = (char *)0x0;
  local_7e4 = (char *)0x0;
  while( true ) {
    cVar6 = param_1[(int)local_7e8];
    bVar13 = false;
    if (((*(byte *)(__ctype_b + cVar6 * 2) & 8) != 0) || (cVar6 == '_')) {
      bVar13 = true;
    }
    if (!bVar13) break;
    local_11c[(int)local_7e4] = cVar6;
    local_7e4 = local_7e4 + 1;
    local_7e8 = local_7e8 + 1;
  }
  local_11c[(int)local_7e4] = '\0';
  bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
  while ((bVar1 & 0x20) != 0) {
    local_7e8 = local_7e8 + 1;
    bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
  }
  local_3dc[1] = 0;
  bVar13 = false;
  iVar5 = _alemu_stricmp(local_11c,"parent");
  if (iVar5 == 0) {
    local_3dc[1] = 1;
  }
  else {
    iVar5 = _alemu_stricmp(local_11c,"root");
    if (iVar5 == 0) {
      local_3dc[1] = 2;
    }
    else {
      iVar5 = _alemu_stricmp(local_11c,"helper");
      if (iVar5 == 0) {
        local_3dc[1] = 3;
        iVar5 = 0;
      }
      else {
        iVar5 = _alemu_stricmp(local_11c,"target");
        if (iVar5 == 0) {
          local_3dc[1] = 4;
LAB_080ca220:
          iVar5 = -1;
        }
        else {
          iVar5 = _alemu_stricmp(local_11c,"partner");
          if (iVar5 == 0) {
            local_3dc[1] = 5;
            iVar5 = 0;
          }
          else {
            iVar5 = _alemu_stricmp(local_11c,"enemy");
            if (iVar5 == 0) {
              local_3dc[1] = 6;
              iVar5 = 0;
            }
            else {
              iVar5 = _alemu_stricmp(local_11c,"enemynear");
              if (iVar5 != 0) {
                iVar5 = _alemu_stricmp(local_11c,"playerid");
                if (iVar5 != 0) goto LAB_080ca230;
                local_3dc[1] = 8;
                goto LAB_080ca220;
              }
              local_3dc[1] = 7;
              iVar5 = 0;
            }
          }
        }
      }
      bVar13 = true;
      ConstExpI(local_3dc + 2,iVar5);
    }
  }
LAB_080ca230:
  if (bVar13) {
    if (param_1[(int)local_7e8] == '(') {
      iVar5 = InfixToPostfix((byte *)(param_1 + (int)(local_7e8 + 1)),local_3dc + 2,param_2,
                             &local_7e0,1);
      if (iVar5 == 0) {
        return (char *)0x0;
      }
      if (*local_7e0 != ')') {
        return (char *)0x0;
      }
      local_7e8 = local_7e0 + (1 - (int)param_1);
    }
    else if (local_3dc[1] == 8) {
      return (char *)0x0;
    }
  }
  if (local_3dc[1] != 0) {
    local_7e8 = param_1 + (int)local_7e8;
    bVar1 = *(byte *)(__ctype_b + 1 + *local_7e8 * 2);
    while ((bVar1 & 0x20) != 0) {
      local_7e8 = local_7e8 + 1;
      bVar1 = *(byte *)(__ctype_b + 1 + *local_7e8 * 2);
    }
    if (*local_7e8 != ',') {
      return (char *)0x0;
    }
    param_1 = local_7e8 + 1;
    bVar1 = *(byte *)(__ctype_b + 1 + *param_1 * 2);
    while ((bVar1 & 0x20) != 0) {
      param_1 = param_1 + 1;
      bVar1 = *(byte *)(__ctype_b + 1 + *param_1 * 2);
    }
    local_7e8 = (char *)0x0;
    local_7e4 = (char *)0x0;
    while( true ) {
      cVar6 = param_1[(int)local_7e8];
      bVar13 = false;
      if (((*(byte *)(__ctype_b + cVar6 * 2) & 8) != 0) || (cVar6 == '_')) {
        bVar13 = true;
      }
      if (!bVar13) break;
      local_11c[(int)local_7e4] = cVar6;
      local_7e4 = local_7e4 + 1;
      local_7e8 = local_7e8 + 1;
    }
    local_11c[(int)local_7e4] = '\0';
  }
  iVar5 = _alemu_stricmp(local_11c,"time");
  if ((iVar5 == 0) || (iVar5 = _alemu_stricmp(local_11c,"statetime"), iVar5 == 0)) {
    local_3dc[0] = 0;
  }
  else {
    iVar5 = _alemu_stricmp(local_11c,"animtime");
    if (iVar5 == 0) {
      local_3dc[0] = 1;
    }
    else {
      iVar5 = _alemu_stricmp(local_11c,"animelem");
      if (iVar5 == 0) {
        local_3dc[0] = 2;
      }
      else {
        iVar5 = _alemu_stricmp(local_11c,"anim");
        if (iVar5 == 0) {
          local_3dc[0] = 3;
        }
        else {
          iVar5 = _alemu_stricmp(local_11c,"vel");
          if (iVar5 == 0) {
            local_3dc[0] = 6;
          }
          else {
            iVar5 = _alemu_stricmp(local_11c,"pos");
            if (iVar5 == 0) {
              local_3dc[0] = 4;
            }
            else {
              iVar5 = _alemu_stricmp(local_11c,"screenpos");
              if (iVar5 == 0) {
                local_3dc[0] = 5;
              }
              else {
                iVar5 = _alemu_stricmp(local_11c,"timemod");
                if (iVar5 == 0) {
                  local_3dc[0] = 7;
                }
                else {
                  iVar5 = _alemu_stricmp(local_11c,"p2dist");
                  if (iVar5 == 0) {
                    local_3dc[0] = 8;
                  }
                  else {
                    iVar5 = _alemu_stricmp(local_11c,"p2bodydist");
                    if (iVar5 == 0) {
                      local_3dc[0] = 9;
                    }
                    else {
                      iVar5 = _alemu_stricmp(local_11c,"p2life");
                      if (iVar5 == 0) {
                        local_3dc[0] = 10;
                      }
                      else {
                        iVar5 = _alemu_stricmp(local_11c,"winperfect");
                        if (iVar5 == 0) {
                          local_3dc[0] = 0x6c;
                        }
                        else {
                          iVar5 = strimatchlen((int)local_11c,(int)&DAT_0827d2ab,3);
                          if (iVar5 == 0) {
                            iVar5 = strimatchlen((int)local_11c,(int)&DAT_08279945,4);
                            if (iVar5 == 0) {
                              iVar5 = _alemu_stricmp(local_11c,"drawgame");
                              if (iVar5 == 0) {
                                local_3dc[0] = 0x6f;
                              }
                              else {
                                iVar5 = _alemu_stricmp(local_11c,"matchover");
                                if (iVar5 == 0) {
                                  local_3dc[0] = 0x70;
                                }
                                else {
                                  iVar5 = _alemu_stricmp(local_11c,"gametime");
                                  if (iVar5 == 0) {
                                    local_3dc[0] = 0x71;
                                  }
                                  else {
                                    iVar5 = _alemu_stricmp(local_11c,"roundno");
                                    if (iVar5 == 0) {
                                      local_3dc[0] = 0x72;
                                    }
                                    else {
                                      iVar5 = _alemu_stricmp(local_11c,"roundstate");
                                      if (iVar5 == 0) {
                                        local_3dc[0] = 0x73;
                                      }
                                      else {
                                        iVar5 = _alemu_stricmp(local_11c,"matchno");
                                        if (iVar5 == 0) {
                                          local_3dc[0] = 0x74;
                                        }
                                        else {
                                          iVar5 = _alemu_stricmp(local_11c,"roundsexisted");
                                          if (iVar5 == 0) {
                                            local_3dc[0] = 0x75;
                                          }
                                          else {
                                            iVar5 = _alemu_stricmp(local_11c,"teamside");
                                            if (iVar5 == 0) {
                                              local_3dc[0] = 0x78;
                                            }
                                            else {
                                              iVar5 = _alemu_stricmp(local_11c,"teammode");
                                              if (iVar5 == 0) {
                                                local_3dc[0] = 0x79;
                                              }
                                              else {
                                                iVar5 = _alemu_stricmp(local_11c,"ishometeam");
                                                if (iVar5 == 0) {
                                                  local_3dc[0] = 0x7a;
                                                }
                                                else {
                                                  iVar5 = _alemu_stricmp(local_11c,"frontedgedist");
                                                  if (iVar5 == 0) {
                                                    local_3dc[0] = 0xb;
                                                  }
                                                  else {
                                                    iVar5 = _alemu_stricmp(local_11c,"backedgedist")
                                                    ;
                                                    if (iVar5 == 0) {
                                                      local_3dc[0] = 0xc;
                                                    }
                                                    else {
                                                      iVar5 = _alemu_stricmp(local_11c,
                                                                             "frontedgebodydist");
                                                      if (iVar5 == 0) {
                                                        local_3dc[0] = 0xb;
                                                        local_3b8 = 1;
                                                      }
                                                      else {
                                                        iVar5 = _alemu_stricmp(local_11c,
                                                                               "backedgebodydist");
                                                        if (iVar5 == 0) {
                                                          local_3dc[0] = 0xc;
                                                          local_3b8 = 1;
                                                        }
                                                        else {
                                                          iVar5 = _alemu_stricmp(local_11c,"life");
                                                          if (iVar5 == 0) {
                                                            local_3dc[0] = 0xf;
                                                          }
                                                          else {
                                                            iVar5 = _alemu_stricmp(local_11c,
                                                                                   "lifemax");
                                                            if (iVar5 == 0) {
                                                              local_3dc[0] = 0x10;
                                                            }
                                                            else {
                                                              iVar5 = _alemu_stricmp(local_11c,
                                                                                     "power");
                                                              if (iVar5 == 0) {
                                                                local_3dc[0] = 0x11;
                                                              }
                                                              else {
                                                                iVar5 = _alemu_stricmp(local_11c,
                                                                                       "powermax");
                                                                if (iVar5 == 0) {
                                                                  local_3dc[0] = 0x12;
                                                                }
                                                                else {
                                                                  iVar5 = _alemu_stricmp(local_11c,
                                                                                         "alive");
                                                                  if (iVar5 == 0) {
                                                                    local_3dc[0] = 0x13;
                                                                  }
                                                                  else {
                                                                    iVar5 = _alemu_stricmp(local_11c
                                                  ,"command");
                                                  if (iVar5 == 0) {
                                                    local_3dc[0] = 0x14;
                                                  }
                                                  else {
                                                    iVar5 = _alemu_stricmp(local_11c,"hitcount");
                                                    if (iVar5 == 0) {
                                                      local_3dc[0] = 0x1e;
                                                    }
                                                    else {
                                                      iVar5 = _alemu_stricmp(local_11c,
                                                                             "uniqhitcount");
                                                      if (iVar5 == 0) {
                                                        local_3dc[0] = 0x1f;
                                                      }
                                                      else {
                                                        iVar5 = _alemu_stricmp(local_11c,"movehit");
                                                        if (iVar5 == 0) {
                                                          local_3dc[0] = 0x20;
                                                        }
                                                        else {
                                                          iVar5 = _alemu_stricmp(local_11c,
                                                                                 "moveguarded");
                                                          if (iVar5 == 0) {
                                                            local_3dc[0] = 0x21;
                                                          }
                                                          else {
                                                            iVar5 = _alemu_stricmp(local_11c,
                                                                                   "movecontact");
                                                            if (iVar5 == 0) {
                                                              local_3dc[0] = 0x22;
                                                            }
                                                            else {
                                                              iVar5 = _alemu_stricmp(local_11c,
                                                                                     "movereversed")
                                                              ;
                                                              if (iVar5 == 0) {
                                                                local_3dc[0] = 0x23;
                                                              }
                                                              else {
                                                                iVar5 = _alemu_stricmp(local_11c,
                                                                                       "inguarddist"
                                                                                      );
                                                                if (iVar5 == 0) {
                                                                  local_3dc[0] = 0x24;
                                                                }
                                                                else {
                                                                  iVar5 = _alemu_stricmp(local_11c,
                                                                                         "stateno");
                                                                  if (iVar5 == 0) {
                                                                    local_3dc[0] = 0x28;
                                                                  }
                                                                  else {
                                                                    iVar5 = _alemu_stricmp(local_11c
                                                  ,"prevstateno");
                                                  if (iVar5 == 0) {
                                                    local_3dc[0] = 0x29;
                                                  }
                                                  else {
                                                    iVar5 = _alemu_stricmp(local_11c,"p2stateno");
                                                    if (iVar5 == 0) {
                                                      local_3dc[0] = 0x2a;
                                                    }
                                                    else {
                                                      iVar5 = _alemu_stricmp(local_11c,"statetype");
                                                      if (iVar5 == 0) {
                                                        local_3dc[0] = 0x2b;
                                                      }
                                                      else {
                                                        iVar5 = _alemu_stricmp(local_11c,
                                                                               "p2statetype");
                                                        if (iVar5 == 0) {
                                                          local_3dc[0] = 0x2c;
                                                        }
                                                        else {
                                                          iVar5 = _alemu_stricmp(local_11c,
                                                                                 "movetype");
                                                          if (iVar5 == 0) {
                                                            local_3dc[0] = 0x2d;
                                                          }
                                                          else {
                                                            iVar5 = _alemu_stricmp(local_11c,
                                                                                   "p2movetype");
                                                            if (iVar5 == 0) {
                                                              local_3dc[0] = 0x2e;
                                                            }
                                                            else {
                                                              iVar5 = _alemu_stricmp(local_11c,
                                                                                     "ctrl");
                                                              if (iVar5 == 0) {
                                                                local_3dc[0] = 0x2f;
                                                              }
                                                              else {
                                                                iVar5 = _alemu_stricmp(local_11c,
                                                                                       "hitdefattr")
                                                                ;
                                                                if (iVar5 == 0) {
                                                                  local_3dc[0] = 0x30;
                                                                }
                                                                else {
                                                                  iVar5 = _alemu_stricmp(local_11c,
                                                                                         "var");
                                                                  if (iVar5 == 0) {
                                                                    local_3dc[0] = 0x157;
                                                                  }
                                                                  else {
                                                                    iVar5 = _alemu_stricmp(local_11c
                                                  ,"fvar");
                                                  if (iVar5 == 0) {
                                                    local_3dc[0] = 0x158;
                                                  }
                                                  else {
                                                    iVar5 = _alemu_stricmp(local_11c,"sysvar");
                                                    if (iVar5 == 0) {
                                                      local_3dc[0] = 0x159;
                                                    }
                                                    else {
                                                      iVar5 = _alemu_stricmp(local_11c,"sysfvar");
                                                      if (iVar5 == 0) {
                                                        local_3dc[0] = 0x15a;
                                                      }
                                                      else {
                                                        iVar5 = _alemu_stricmp(local_11c,"random");
                                                        if (iVar5 == 0) {
                                                          local_3dc[0] = 0x33;
                                                        }
                                                        else {
                                                          iVar5 = _alemu_stricmp(local_11c,"numproj"
                                                                                );
                                                          if (iVar5 == 0) {
                                                            local_3dc[0] = 0x3c;
                                                          }
                                                          else {
                                                            iVar5 = _alemu_stricmp(local_11c,
                                                                                   "numprojid");
                                                            if (iVar5 == 0) {
                                                              local_3dc[0] = 0x154;
                                                            }
                                                            else {
                                                              iVar5 = _alemu_stricmp(local_11c,
                                                                                                                                                                          
                                                  "projcanceltime");
                                                  if (iVar5 == 0) {
                                                    local_3dc[0] = 0x15b;
                                                  }
                                                  else {
                                                    iVar5 = _alemu_stricmp(local_11c,"projhittime");
                                                    if (iVar5 == 0) {
                                                      local_3dc[0] = 0x151;
                                                    }
                                                    else {
                                                      iVar5 = strimatchlen((int)local_11c,(int)&DAT_0827c50c,
                                                                           7);
                                                      if (iVar5 == 0) {
                                                        iVar5 = _alemu_stricmp(local_11c,
                                                                               "projguardedtime");
                                                        if (iVar5 == 0) {
                                                          local_3dc[0] = 0x152;
                                                        }
                                                        else {
                                                          iVar5 = strimatchlen((int)local_11c,
                                                                               (int)&DAT_0827c524,0xb);
                                                          if (iVar5 == 0) {
                                                            iVar5 = _alemu_stricmp(local_11c,
                                                                                   "projcontacttime"
                                                                                  );
                                                            if (iVar5 == 0) {
                                                              local_3dc[0] = 0x153;
                                                            }
                                                            else {
                                                              iVar5 = strimatchlen((int)local_11c,
                                                                                   (int)&DAT_0827c540,0xb);
                                                              if (iVar5 == 0) {
                                                                iVar5 = _alemu_stricmp(local_11c,
                                                                                       "p1name");
                                                                if ((iVar5 == 0) ||
                                                                   (iVar5 = _alemu_stricmp(local_11c
                                                  ,"name"), iVar5 == 0)) {
                                                    local_3dc[0] = 0x5a;
                                                  }
                                                  else {
                                                    iVar5 = _alemu_stricmp(local_11c,"p2name");
                                                    if (iVar5 == 0) {
                                                      local_3dc[0] = 0x5b;
                                                    }
                                                    else {
                                                      iVar5 = _alemu_stricmp(local_11c,"p3name");
                                                      if (iVar5 == 0) {
                                                        local_3dc[0] = 0x5c;
                                                      }
                                                      else {
                                                        iVar5 = _alemu_stricmp(local_11c,"p4name");
                                                        if (iVar5 == 0) {
                                                          local_3dc[0] = 0x5d;
                                                        }
                                                        else {
                                                          iVar5 = _alemu_stricmp(local_11c,
                                                                                 "authorname");
                                                          if (iVar5 == 0) {
                                                            local_3dc[0] = 0x5e;
                                                          }
                                                          else {
                                                            iVar5 = _alemu_stricmp(local_11c,
                                                                                   "numpartner");
                                                            if (iVar5 == 0) {
                                                              local_3dc[0] = 0x5f;
                                                            }
                                                            else {
                                                              iVar5 = _alemu_stricmp(local_11c,
                                                                                     "numenemy");
                                                              if (iVar5 == 0) {
                                                                local_3dc[0] = 0x60;
                                                              }
                                                              else {
                                                                iVar5 = _alemu_stricmp(local_11c,
                                                                                       "id");
                                                                if (iVar5 == 0) {
                                                                  local_3dc[0] = 0x61;
                                                                }
                                                                else {
                                                                  iVar5 = _alemu_stricmp(local_11c,
                                                                                         "facing");
                                                                  if (iVar5 == 0) {
                                                                    local_3dc[0] = 99;
                                                                  }
                                                                  else {
                                                                    iVar5 = _alemu_stricmp(local_11c
                                                  ,"hitfall");
                                                  if (iVar5 == 0) {
                                                    local_3dc[0] = 100;
                                                  }
                                                  else {
                                                    iVar5 = _alemu_stricmp(local_11c,"hitshakeover")
                                                    ;
                                                    if (iVar5 == 0) {
                                                      local_3dc[0] = 0x65;
                                                    }
                                                    else {
                                                      iVar5 = _alemu_stricmp(local_11c,"hitover");
                                                      if (iVar5 == 0) {
                                                        local_3dc[0] = 0x66;
                                                      }
                                                      else {
                                                        iVar5 = _alemu_stricmp(local_11c,"hitvel");
                                                        if (iVar5 == 0) {
                                                          local_3dc[0] = 0x67;
                                                        }
                                                        else {
                                                          iVar5 = _alemu_stricmp(local_11c,
                                                                                 "hitpausetime");
                                                          if (iVar5 == 0) {
                                                            local_3dc[0] = 0x68;
                                                          }
                                                          else {
                                                            iVar5 = _alemu_stricmp(local_11c,
                                                                                   "canrecover");
                                                            if (iVar5 == 0) {
                                                              local_3dc[0] = 0x69;
                                                            }
                                                            else {
                                                              iVar5 = _alemu_stricmp(local_11c,
                                                                                     "animelemno");
                                                              if (iVar5 == 0) {
                                                                local_3dc[0] = 0x15c;
                                                              }
                                                              else {
                                                                iVar5 = _alemu_stricmp(local_11c,
                                                                                       "animexist");
                                                                if (iVar5 == 0) {
                                                                  local_3dc[0] = 0x14c;
                                                                }
                                                                else {
                                                                  iVar5 = _alemu_stricmp(local_11c,
                                                                                                                                                                                  
                                                  "selfanimexist");
                                                  if (iVar5 == 0) {
                                                    local_3dc[0] = 0x14d;
                                                  }
                                                  else {
                                                    iVar5 = _alemu_stricmp(local_11c,"playeridexist"
                                                                          );
                                                    if (iVar5 == 0) {
                                                      local_3dc[0] = 0x14e;
                                                    }
                                                    else {
                                                      iVar5 = _alemu_stricmp(local_11c,"palno");
                                                      if (iVar5 == 0) {
                                                        local_3dc[0] = 0x6b;
                                                      }
                                                      else {
                                                        iVar5 = _alemu_stricmp(local_11c,"numexplod"
                                                                              );
                                                        if (iVar5 == 0) {
                                                          local_3dc[0] = 0x96;
                                                        }
                                                        else {
                                                          iVar5 = _alemu_stricmp(local_11c,
                                                                                 "numtarget");
                                                          if (iVar5 == 0) {
                                                            local_3dc[0] = 0xa0;
                                                          }
                                                          else {
                                                            iVar5 = _alemu_stricmp(local_11c,
                                                                                   "gethitvar");
                                                            if (iVar5 == 0) {
                                                              local_3dc[0] = 0xb4;
                                                            }
                                                            else {
                                                              iVar5 = _alemu_stricmp(local_11c,
                                                                                     "const");
                                                              if (iVar5 == 0) {
                                                                local_3dc[0] = 0xb5;
                                                              }
                                                              else {
                                                                iVar5 = _alemu_stricmp(local_11c,
                                                                                       "stagevar");
                                                                if (iVar5 == 0) {
                                                                  local_3dc[0] = 0xb6;
                                                                }
                                                                else {
                                                                  iVar5 = _alemu_stricmp(local_11c,
                                                                                                                                                                                  
                                                  "tickspersecond");
                                                  if (iVar5 == 0) {
                                                    local_3dc[0] = 0xbe;
                                                  }
                                                  else {
                                                    iVar5 = _alemu_stricmp(local_11c,"ishelper");
                                                    if (iVar5 == 0) {
                                                      local_3dc[0] = 0xc9;
                                                    }
                                                    else {
                                                      iVar5 = _alemu_stricmp(local_11c,"numhelper");
                                                      if (iVar5 == 0) {
                                                        local_3dc[0] = 0xca;
                                                      }
                                                      else {
                                                        iVar5 = _alemu_stricmp(local_11c,
                                                                               "parentdist");
                                                        if (iVar5 == 0) {
                                                          local_3dc[0] = 0xcb;
                                                        }
                                                        else {
                                                          iVar5 = _alemu_stricmp(local_11c,
                                                                                 "rootdist");
                                                          if (iVar5 == 0) {
                                                            local_3dc[0] = 0xcc;
                                                          }
                                                          else {
                                                            iVar5 = _alemu_stricmp(local_11c,
                                                                                   "standby");
                                                            if (iVar5 == 0) {
                                                              local_3dc[0] = 0xcd;
                                                            }
                                                            else {
                                                              iVar5 = _alemu_stricmp(local_11c,"pi")
                                                              ;
                                                              if (iVar5 == 0) {
                                                                local_3dc[0] = 300;
                                                              }
                                                              else {
                                                                iVar5 = _alemu_stricmp(local_11c,"e"
                                                                                      );
                                                                if (iVar5 == 0) {
                                                                  local_3dc[0] = 0x12d;
                                                                }
                                                                else {
                                                                  iVar5 = _alemu_stricmp(local_11c,
                                                                                         "ifelse");
                                                                  if (iVar5 == 0) {
                                                                    local_3dc[0] = 0x131;
                                                                  }
                                                                  else {
                                                                    iVar5 = _alemu_stricmp(local_11c
                                                  ,"log");
                                                  if (iVar5 == 0) {
                                                    local_3dc[0] = 0x136;
                                                  }
                                                  else {
                                                    iVar5 = _alemu_stricmp(local_11c,"sin");
                                                    if (iVar5 == 0) {
                                                      local_3dc[0] = 0x140;
                                                    }
                                                    else {
                                                      iVar5 = _alemu_stricmp(local_11c,"cos");
                                                      if (iVar5 == 0) {
                                                        local_3dc[0] = 0x141;
                                                      }
                                                      else {
                                                        iVar5 = _alemu_stricmp(local_11c,"tan");
                                                        if (iVar5 == 0) {
                                                          local_3dc[0] = 0x142;
                                                        }
                                                        else {
                                                          iVar5 = _alemu_stricmp(local_11c,"asin");
                                                          if (iVar5 == 0) {
                                                            local_3dc[0] = 0x143;
                                                          }
                                                          else {
                                                            iVar5 = _alemu_stricmp(local_11c,"acos")
                                                            ;
                                                            if (iVar5 == 0) {
                                                              local_3dc[0] = 0x144;
                                                            }
                                                            else {
                                                              iVar5 = _alemu_stricmp(local_11c,
                                                                                     "atan");
                                                              if (iVar5 == 0) {
                                                                local_3dc[0] = 0x145;
                                                              }
                                                              else {
                                                                iVar5 = _alemu_stricmp(local_11c,
                                                                                       "exp");
                                                                if (iVar5 == 0) {
                                                                  local_3dc[0] = 0x146;
                                                                }
                                                                else {
                                                                  iVar5 = _alemu_stricmp(local_11c,
                                                                                         "ln");
                                                                  if (iVar5 == 0) {
                                                                    local_3dc[0] = 0x147;
                                                                  }
                                                                  else {
                                                                    iVar5 = _alemu_stricmp(local_11c
                                                  ,"abs");
                                                  if (iVar5 == 0) {
                                                    local_3dc[0] = 0x148;
                                                  }
                                                  else {
                                                    iVar5 = _alemu_stricmp(local_11c,"floor");
                                                    if (iVar5 == 0) {
                                                      local_3dc[0] = 0x149;
                                                    }
                                                    else {
                                                      iVar5 = _alemu_stricmp(local_11c,"ceil");
                                                      if (iVar5 == 0) {
                                                        local_3dc[0] = 0x14a;
                                                      }
                                                      else {
                                                        iVar5 = _alemu_stricmp(local_11c,
                                                                               "animelemtime");
                                                        if (iVar5 != 0) {
                                                          pbVar16 = (byte *)(g + 0x81d2);
                                                          ghidra_fa[0] = (void *)(local_11c);
                                                          pcVar17 = "Invalid trigger: %s";
                                                          goto LAB_080cccd9;
                                                        }
                                                        local_3dc[0] = 0x14b;
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
                                                  }
                                                  }
                                                  }
                                                  else {
                                                    local_3dc[0] = 0x40;
                                                  }
                                                  }
                                                  }
                                                  else {
                                                    local_3dc[0] = 0x3f;
                                                  }
                                                  }
                                                  }
                                                  else {
                                                    local_3dc[0] = 0x3e;
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
                                }
                              }
                            }
                            else {
                              local_3dc[0] = 0x6e;
                            }
                          }
                          else {
                            local_3dc[0] = 0x6d;
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
    }
  }
  bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
  while ((bVar1 & 0x20) != 0) {
    local_7e8 = local_7e8 + 1;
    bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
  }
  if ((local_3dc[0] == 0xc9) && (param_1[(int)local_7e8] == '(')) {
    local_3dc[0] = 0x14f;
  }
  if ((local_3dc[0] == 0xca) && (param_1[(int)local_7e8] == '(')) {
    local_3dc[0] = 0x150;
  }
  if ((local_3dc[0] == 0x96) && (param_1[(int)local_7e8] == '(')) {
    local_3dc[0] = 0x155;
  }
  if ((local_3dc[0] == 0xa0) && (param_1[(int)local_7e8] == '(')) {
    local_3dc[0] = 0x156;
  }
  if (local_3dc[0] - 0x140U < 0x1d) {
    if (param_1[(int)local_7e8] != '(') {
      return (char *)0x0;
    }
    iVar5 = SCtrlReadExpListArray
                      ((byte *)(param_1 + (int)(local_7e8 + 1)),"n:)",param_2,&local_7e0,
                       (int)local_31c,(int)local_39c,(int *)&local_7e4,param_5);
    if (iVar5 != 1) {
      return (char *)0x0;
    }
    if (*local_7e0 != ')') {
      return (char *)0x0;
    }
    local_7ec = local_7e4;
    local_7e8 = local_7e0 + (1 - (int)param_1);
  }
  if (local_3dc[0] == 0x136) {
    bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
    while ((bVar1 & 0x20) != 0) {
      local_7e8 = local_7e8 + 1;
      bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
    }
    if (param_1[(int)local_7e8] != '(') {
      return (char *)0x0;
    }
    iVar5 = SCtrlReadExpListArray
                      ((byte *)(param_1 + (int)(local_7e8 + 1)),"nn:)",param_2,&local_7e0,
                       (int)(local_31c + (int)local_7ec),(int)(local_39c + (int)local_7ec),
                       (int *)&local_7e4,param_5 - (int)local_7ec);
    if (iVar5 != 2) {
      return (char *)0x0;
    }
    if (*local_7e0 != ')') {
      return (char *)0x0;
    }
    local_7ec = local_7ec + (int)local_7e4;
    local_7e8 = local_7e0 + (1 - (int)param_1);
  }
  if (local_3dc[0] == 0x131) {
    bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
    while ((bVar1 & 0x20) != 0) {
      local_7e8 = local_7e8 + 1;
      bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
    }
    if (param_1[(int)local_7e8] != '(') {
      return (char *)0x0;
    }
    iVar5 = SCtrlReadExpListArray
                      ((byte *)(param_1 + (int)(local_7e8 + 1)),"nnn:)",param_2,&local_7e0,
                       (int)(local_31c + (int)local_7ec),(int)(local_39c + (int)local_7ec),
                       (int *)&local_7e4,param_5 - (int)local_7ec);
    if (iVar5 != 3) {
      return (char *)0x0;
    }
    if (*local_7e0 != ')') {
      return (char *)0x0;
    }
    local_7ec = local_7ec + (int)local_7e4;
    local_7e8 = local_7e0 + (1 - (int)param_1);
  }
  if (local_3dc[0] == 0x3e) {
    local_3b8 = __strtol_internal(local_115,(undefined4 *)0x0,10,0);
  }
  if (local_3dc[0] - 0x3fU < 2) {
    local_3b8 = __strtol_internal(local_111,(undefined4 *)0x0,10,0);
  }
  if (local_3dc[0] == 0x6d) {
    iVar5 = strimatchlen((int)(local_11c + 3),(int)&DAT_08278c70,2);
    if (iVar5 == 0) {
      iVar5 = strimatchlen((int)(local_11c + 3),(int)&DAT_0827c085,2);
      if (iVar5 == 0) {
        if (local_11c[3] != '\0') {
          pbVar16 = (byte *)(g + 0x81d2);
          ghidra_fa[0] = (void *)(local_11c);
          pcVar17 = "Invalid win trigger: %s";
          goto LAB_080cccd9;
        }
        local_3b8 = 0xffffffff;
      }
      else {
        local_3b8 = 3;
      }
    }
    else {
      local_3b8 = 1;
    }
  }
  if (local_3dc[0] == 0x6e) {
    iVar5 = strimatchlen((int)local_118,(int)&DAT_08278c70,2);
    if (iVar5 == 0) {
      iVar5 = strimatchlen((int)local_118,(int)&DAT_0827c085,2);
      if (iVar5 == 0) {
        if (local_118[0] != '\0') {
          pbVar16 = (byte *)(g + 0x81d2);
          ghidra_fa[0] = (void *)(local_11c);
          pcVar17 = "Invalid lose trigger: %s";
          goto LAB_080cccd9;
        }
        local_3b8 = 0xffffffff;
      }
      else {
        local_3b8 = 3;
      }
    }
    else {
      local_3b8 = 1;
    }
  }
  if (local_3dc[0] == 0xb4) {
    if (param_1[(int)local_7e8] != '(') {
      ghidra_fa[0] = (void *)(local_11c);
      pcVar17 = "Need to specify gethitvar(varname): %s";
      pbVar16 = (byte *)(g + 0x81d2);
      goto LAB_080cccd9;
    }
    local_7e8 = local_7e8 + 1;
    bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
    while ((bVar1 & 0x20) != 0) {
      local_7e8 = local_7e8 + 1;
      bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
    }
    iVar5 = 0;
    while( true ) {
      bVar1 = param_1[(int)local_7e8];
      bVar13 = false;
      if (((*(byte *)(__ctype_b + (char)bVar1 * 2) & 8) != 0) || (bVar1 == 0x5f)) {
        bVar13 = true;
      }
      if ((!bVar13) && (bVar1 != 0x2e)) break;
      local_4dc[iVar5] = bVar1;
      iVar5 = iVar5 + 1;
      local_7e8 = local_7e8 + 1;
    }
    local_4dc[iVar5] = 0;
    bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
    while ((bVar1 & 0x20) != 0) {
      local_7e8 = local_7e8 + 1;
      bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
    }
    if (param_1[(int)local_7e8] != ')') {
      ghidra_fa[0] = (void *)(local_11c);
      pcVar17 = "Missing closing parenthesis: %s";
      pbVar16 = (byte *)(g + 0x81d2);
      goto LAB_080cccd9;
    }
    _alemu_strlwr((char *)local_4dc);
    iVar5 = 8;
    bVar13 = 0;  /* dead flag (repz cmpsb, count 8) */
    bVar15 = 0;  /* dead flag (repz cmpsb, count 8) */
    pbVar16 = local_4dc;
    pbVar9 = (byte *)"xveladd";
    do {
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      bVar13 = *pbVar16 < *pbVar9;
      bVar15 = *pbVar16 == *pbVar9;
      pbVar16 = pbVar16 + 1;
      pbVar9 = pbVar9 + 1;
    } while (bVar15);
    bVar14 = (!bVar13 && !bVar15) < bVar13;
    bVar13 = (!bVar13 && !bVar15) == bVar13;
    if (bVar13) {
      local_3c0 = 0;
    }
    else {
      iVar5 = 8;
      pbVar16 = local_4dc;
      pbVar9 = (byte *)"yveladd";
      do {
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        bVar14 = *pbVar16 < *pbVar9;
        bVar13 = *pbVar16 == *pbVar9;
        pbVar16 = pbVar16 + 1;
        pbVar9 = pbVar9 + 1;
      } while (bVar13);
      bVar15 = (!bVar14 && !bVar13) < bVar14;
      bVar13 = (!bVar14 && !bVar13) == bVar14;
      if (bVar13) {
        local_3c0 = 1;
      }
      else {
        iVar5 = 5;
        pbVar16 = local_4dc;
        pbVar9 = (byte *)(int)&DAT_08284c55;
        do {
          if (iVar5 == 0) break;
          iVar5 = iVar5 + -1;
          bVar15 = *pbVar16 < *pbVar9;
          bVar13 = *pbVar16 == *pbVar9;
          pbVar16 = pbVar16 + 1;
          pbVar9 = pbVar9 + 1;
        } while (bVar13);
        bVar14 = (!bVar15 && !bVar13) < bVar15;
        bVar13 = (!bVar15 && !bVar13) == bVar15;
        if (bVar13) {
          local_3c0 = 2;
        }
        else {
          iVar5 = 9;
          pbVar16 = local_4dc;
          pbVar9 = (byte *)(int)&DAT_0827bc8d;
          do {
            if (iVar5 == 0) break;
            iVar5 = iVar5 + -1;
            bVar14 = *pbVar16 < *pbVar9;
            bVar13 = *pbVar16 == *pbVar9;
            pbVar16 = pbVar16 + 1;
            pbVar9 = pbVar9 + 1;
          } while (bVar13);
          bVar15 = (!bVar14 && !bVar13) < bVar14;
          bVar13 = (!bVar14 && !bVar13) == bVar14;
          if (bVar13) {
            local_3c0 = 3;
          }
          else {
            iVar5 = 8;
            pbVar16 = local_4dc;
            pbVar9 = (byte *)"airtype";
            do {
              if (iVar5 == 0) break;
              iVar5 = iVar5 + -1;
              bVar15 = *pbVar16 < *pbVar9;
              bVar13 = *pbVar16 == *pbVar9;
              pbVar16 = pbVar16 + 1;
              pbVar9 = pbVar9 + 1;
            } while (bVar13);
            bVar14 = (!bVar15 && !bVar13) < bVar15;
            bVar13 = (!bVar15 && !bVar13) == bVar15;
            if (bVar13) {
              local_3c0 = 4;
            }
            else {
              iVar5 = 0xb;
              pbVar16 = local_4dc;
              pbVar9 = (byte *)"groundtype";
              do {
                if (iVar5 == 0) break;
                iVar5 = iVar5 + -1;
                bVar14 = *pbVar16 < *pbVar9;
                bVar13 = *pbVar16 == *pbVar9;
                pbVar16 = pbVar16 + 1;
                pbVar9 = pbVar9 + 1;
              } while (bVar13);
              bVar15 = (!bVar14 && !bVar13) < bVar14;
              bVar13 = (!bVar14 && !bVar13) == bVar14;
              if (bVar13) {
                local_3c0 = 5;
              }
              else {
                iVar5 = 7;
                pbVar16 = local_4dc;
                pbVar9 = (byte *)(int)&DAT_0827ac23;
                do {
                  if (iVar5 == 0) break;
                  iVar5 = iVar5 + -1;
                  bVar15 = *pbVar16 < *pbVar9;
                  bVar13 = *pbVar16 == *pbVar9;
                  pbVar16 = pbVar16 + 1;
                  pbVar9 = pbVar9 + 1;
                } while (bVar13);
                bVar14 = (!bVar15 && !bVar13) < bVar15;
                bVar13 = (!bVar15 && !bVar13) == bVar15;
                if (bVar13) {
                  local_3c0 = 6;
                }
                else {
                  iVar5 = 9;
                  pbVar16 = local_4dc;
                  pbVar9 = (byte *)(int)&DAT_0827c46f;
                  do {
                    if (iVar5 == 0) break;
                    iVar5 = iVar5 + -1;
                    bVar14 = *pbVar16 < *pbVar9;
                    bVar13 = *pbVar16 == *pbVar9;
                    pbVar16 = pbVar16 + 1;
                    pbVar9 = pbVar9 + 1;
                  } while (bVar13);
                  bVar15 = (!bVar14 && !bVar13) < bVar14;
                  bVar13 = (!bVar14 && !bVar13) == bVar14;
                  if (bVar13) {
                    local_3c0 = 7;
                  }
                  else {
                    iVar5 = 10;
                    pbVar16 = local_4dc;
                    pbVar9 = (byte *)"fallcount";
                    do {
                      if (iVar5 == 0) break;
                      iVar5 = iVar5 + -1;
                      bVar15 = *pbVar16 < *pbVar9;
                      bVar13 = *pbVar16 == *pbVar9;
                      pbVar16 = pbVar16 + 1;
                      pbVar9 = pbVar9 + 1;
                    } while (bVar13);
                    bVar14 = (!bVar15 && !bVar13) < bVar15;
                    bVar13 = (!bVar15 && !bVar13) == bVar15;
                    if (bVar13) {
                      local_3c0 = 8;
                    }
                    else {
                      iVar5 = 0xd;
                      pbVar16 = local_4dc;
                      pbVar9 = (byte *)"hitshaketime";
                      do {
                        if (iVar5 == 0) break;
                        iVar5 = iVar5 + -1;
                        bVar14 = *pbVar16 < *pbVar9;
                        bVar13 = *pbVar16 == *pbVar9;
                        pbVar16 = pbVar16 + 1;
                        pbVar9 = pbVar9 + 1;
                      } while (bVar13);
                      bVar15 = (!bVar14 && !bVar13) < bVar14;
                      bVar13 = (!bVar14 && !bVar13) == bVar14;
                      if (bVar13) {
                        local_3c0 = 9;
                      }
                      else {
                        iVar5 = 8;
                        pbVar16 = local_4dc;
                        pbVar9 = (byte *)(int)&DAT_0827be67;
                        do {
                          if (iVar5 == 0) break;
                          iVar5 = iVar5 + -1;
                          bVar15 = *pbVar16 < *pbVar9;
                          bVar13 = *pbVar16 == *pbVar9;
                          pbVar16 = pbVar16 + 1;
                          pbVar9 = pbVar9 + 1;
                        } while (bVar13);
                        bVar14 = (!bVar15 && !bVar13) < bVar15;
                        bVar13 = (!bVar15 && !bVar13) == bVar15;
                        if (bVar13) {
                          local_3c0 = 10;
                        }
                        else {
                          iVar5 = 10;
                          pbVar16 = local_4dc;
                          pbVar9 = (byte *)(int)&DAT_0827be81;
                          do {
                            if (iVar5 == 0) break;
                            iVar5 = iVar5 + -1;
                            bVar14 = *pbVar16 < *pbVar9;
                            bVar13 = *pbVar16 == *pbVar9;
                            pbVar16 = pbVar16 + 1;
                            pbVar9 = pbVar9 + 1;
                          } while (bVar13);
                          bVar15 = (!bVar14 && !bVar13) < bVar14;
                          bVar13 = (!bVar14 && !bVar13) == bVar14;
                          if (bVar13) {
                            local_3c0 = 0xb;
                          }
                          else {
                            iVar5 = 9;
                            pbVar16 = local_4dc;
                            pbVar9 = (byte *)(int)&DAT_0827bf52;
                            do {
                              if (iVar5 == 0) break;
                              iVar5 = iVar5 + -1;
                              bVar15 = *pbVar16 < *pbVar9;
                              bVar13 = *pbVar16 == *pbVar9;
                              pbVar16 = pbVar16 + 1;
                              pbVar9 = pbVar9 + 1;
                            } while (bVar13);
                            bVar14 = (!bVar15 && !bVar13) < bVar15;
                            bVar13 = (!bVar15 && !bVar13) == bVar15;
                            if (bVar13) {
                              local_3c0 = 0xc;
                            }
                            else {
                              iVar5 = 0xc;
                              pbVar16 = local_4dc;
                              pbVar9 = (byte *)(int)&DAT_0827bb5e;
                              do {
                                if (iVar5 == 0) break;
                                iVar5 = iVar5 + -1;
                                bVar14 = *pbVar16 < *pbVar9;
                                bVar13 = *pbVar16 == *pbVar9;
                                pbVar16 = pbVar16 + 1;
                                pbVar9 = pbVar9 + 1;
                              } while (bVar13);
                              bVar15 = (!bVar14 && !bVar13) < bVar14;
                              bVar13 = (!bVar14 && !bVar13) == bVar14;
                              if (bVar13) {
                                local_3c0 = 0xd;
                              }
                              else {
                                iVar5 = 5;
                                pbVar16 = local_4dc;
                                pbVar9 = &DAT_0827c71c;
                                do {
                                  if (iVar5 == 0) break;
                                  iVar5 = iVar5 + -1;
                                  bVar15 = *pbVar16 < *pbVar9;
                                  bVar13 = *pbVar16 == *pbVar9;
                                  pbVar16 = pbVar16 + 1;
                                  pbVar9 = pbVar9 + 1;
                                } while (bVar13);
                                bVar14 = (!bVar15 && !bVar13) < bVar15;
                                bVar13 = (!bVar15 && !bVar13) == bVar15;
                                if (bVar13) {
                                  local_3c0 = 0xe;
                                  local_3c4 = 1;
                                }
                                else {
                                  iVar5 = 5;
                                  pbVar16 = local_4dc;
                                  pbVar9 = &DAT_0827c721;
                                  do {
                                    if (iVar5 == 0) break;
                                    iVar5 = iVar5 + -1;
                                    bVar14 = *pbVar16 < *pbVar9;
                                    bVar13 = *pbVar16 == *pbVar9;
                                    pbVar16 = pbVar16 + 1;
                                    pbVar9 = pbVar9 + 1;
                                  } while (bVar13);
                                  bVar15 = (!bVar14 && !bVar13) < bVar14;
                                  bVar13 = (!bVar14 && !bVar13) == bVar14;
                                  if (bVar13) {
                                    local_3c0 = 0xf;
                                    local_3c4 = 1;
                                  }
                                  else {
                                    iVar5 = 5;
                                    pbVar16 = local_4dc;
                                    pbVar9 = &DAT_0827c726;
                                    do {
                                      if (iVar5 == 0) break;
                                      iVar5 = iVar5 + -1;
                                      bVar15 = *pbVar16 < *pbVar9;
                                      bVar13 = *pbVar16 == *pbVar9;
                                      pbVar16 = pbVar16 + 1;
                                      pbVar9 = pbVar9 + 1;
                                    } while (bVar13);
                                    bVar14 = (!bVar15 && !bVar13) < bVar15;
                                    bVar13 = (!bVar15 && !bVar13) == bVar15;
                                    if (bVar13) {
                                      local_3c0 = 0x10;
                                      local_3c4 = 1;
                                    }
                                    else {
                                      iVar5 = 5;
                                      pbVar16 = local_4dc;
                                      pbVar9 = (byte *)(int)&DAT_0827c738;
                                      do {
                                        if (iVar5 == 0) break;
                                        iVar5 = iVar5 + -1;
                                        bVar14 = *pbVar16 < *pbVar9;
                                        bVar13 = *pbVar16 == *pbVar9;
                                        pbVar16 = pbVar16 + 1;
                                        pbVar9 = pbVar9 + 1;
                                      } while (bVar13);
                                      bVar15 = (!bVar14 && !bVar13) < bVar14;
                                      bVar13 = (!bVar14 && !bVar13) == bVar14;
                                      if (bVar13) {
                                        local_3c0 = 0x11;
                                        local_3c4 = 1;
                                      }
                                      else {
                                        iVar5 = 5;
                                        pbVar16 = local_4dc;
                                        pbVar9 = (byte *)(int)&DAT_0827c742;
                                        do {
                                          if (iVar5 == 0) break;
                                          iVar5 = iVar5 + -1;
                                          bVar15 = *pbVar16 < *pbVar9;
                                          bVar13 = *pbVar16 == *pbVar9;
                                          pbVar16 = pbVar16 + 1;
                                          pbVar9 = pbVar9 + 1;
                                        } while (bVar13);
                                        bVar14 = (!bVar15 && !bVar13) < bVar15;
                                        bVar13 = (!bVar15 && !bVar13) == bVar15;
                                        if (bVar13) {
                                          local_3c0 = 0x12;
                                          local_3c4 = 1;
                                        }
                                        else {
                                          iVar5 = 7;
                                          pbVar16 = local_4dc;
                                          pbVar9 = (byte *)(int)&DAT_08279ea9;
                                          do {
                                            if (iVar5 == 0) break;
                                            iVar5 = iVar5 + -1;
                                            bVar14 = *pbVar16 < *pbVar9;
                                            bVar13 = *pbVar16 == *pbVar9;
                                            pbVar16 = pbVar16 + 1;
                                            pbVar9 = pbVar9 + 1;
                                          } while (bVar13);
                                          bVar15 = (!bVar14 && !bVar13) < bVar14;
                                          bVar13 = (!bVar14 && !bVar13) == bVar14;
                                          if (bVar13) {
                                            local_3c0 = 0x13;
                                            local_3c4 = 1;
                                          }
                                          else {
                                            iVar5 = 8;
                                            pbVar16 = local_4dc;
                                            pbVar9 = (byte *)(int)&DAT_0827b9fa;
                                            do {
                                              if (iVar5 == 0) break;
                                              iVar5 = iVar5 + -1;
                                              bVar15 = *pbVar16 < *pbVar9;
                                              bVar13 = *pbVar16 == *pbVar9;
                                              pbVar16 = pbVar16 + 1;
                                              pbVar9 = pbVar9 + 1;
                                            } while (bVar13);
                                            bVar14 = (!bVar15 && !bVar13) < bVar15;
                                            bVar13 = (!bVar15 && !bVar13) == bVar15;
                                            if (bVar13) {
                                              local_3c0 = 0x14;
                                            }
                                            else {
                                              iVar5 = 8;
                                              pbVar16 = local_4dc;
                                              pbVar9 = (byte *)(int)&DAT_0827c484;
                                              do {
                                                if (iVar5 == 0) break;
                                                iVar5 = iVar5 + -1;
                                                bVar14 = *pbVar16 < *pbVar9;
                                                bVar13 = *pbVar16 == *pbVar9;
                                                pbVar16 = pbVar16 + 1;
                                                pbVar9 = pbVar9 + 1;
                                              } while (bVar13);
                                              bVar15 = (!bVar14 && !bVar13) < bVar14;
                                              bVar13 = (!bVar14 && !bVar13) == bVar14;
                                              if (bVar13) {
                                                local_3c0 = 0x15;
                                              }
                                              else {
                                                iVar5 = 8;
                                                pbVar16 = local_4dc;
                                                pbVar9 = (byte *)"isbound";
                                                do {
                                                  if (iVar5 == 0) break;
                                                  iVar5 = iVar5 + -1;
                                                  bVar15 = *pbVar16 < *pbVar9;
                                                  bVar13 = *pbVar16 == *pbVar9;
                                                  pbVar16 = pbVar16 + 1;
                                                  pbVar9 = pbVar9 + 1;
                                                } while (bVar13);
                                                bVar14 = (!bVar15 && !bVar13) < bVar15;
                                                bVar13 = (!bVar15 && !bVar13) == bVar15;
                                                if (bVar13) {
                                                  local_3c0 = 0x16;
                                                }
                                                else {
                                                  iVar5 = 5;
                                                  pbVar16 = local_4dc;
                                                  pbVar9 = (byte *)(int)&DAT_0827bc43;
                                                  do {
                                                    if (iVar5 == 0) break;
                                                    iVar5 = iVar5 + -1;
                                                    bVar14 = *pbVar16 < *pbVar9;
                                                    bVar13 = *pbVar16 == *pbVar9;
                                                    pbVar16 = pbVar16 + 1;
                                                    pbVar9 = pbVar9 + 1;
                                                  } while (bVar13);
                                                  bVar15 = (!bVar14 && !bVar13) < bVar14;
                                                  bVar13 = (!bVar14 && !bVar13) == bVar14;
                                                  if (bVar13) {
                                                    local_3c0 = 0x17;
                                                  }
                                                  else {
                                                    iVar5 = 0xc;
                                                    pbVar16 = local_4dc;
                                                    pbVar9 = (byte *)"fall.damage";
                                                    do {
                                                      if (iVar5 == 0) break;
                                                      iVar5 = iVar5 + -1;
                                                      bVar15 = *pbVar16 < *pbVar9;
                                                      bVar13 = *pbVar16 == *pbVar9;
                                                      pbVar16 = pbVar16 + 1;
                                                      pbVar9 = pbVar9 + 1;
                                                    } while (bVar13);
                                                    bVar14 = (!bVar15 && !bVar13) < bVar15;
                                                    bVar13 = (!bVar15 && !bVar13) == bVar15;
                                                    if (bVar13) {
                                                      local_3c0 = 0x18;
                                                    }
                                                    else {
                                                      iVar5 = 10;
                                                      pbVar16 = local_4dc;
                                                      pbVar9 = (byte *)"fall.xvel";
                                                      do {
                                                        if (iVar5 == 0) break;
                                                        iVar5 = iVar5 + -1;
                                                        bVar14 = *pbVar16 < *pbVar9;
                                                        bVar13 = *pbVar16 == *pbVar9;
                                                        pbVar16 = pbVar16 + 1;
                                                        pbVar9 = pbVar9 + 1;
                                                      } while (bVar13);
                                                      bVar15 = (!bVar14 && !bVar13) < bVar14;
                                                      bVar13 = (!bVar14 && !bVar13) == bVar14;
                                                      if (bVar13) {
                                                        local_3c0 = 0x19;
                                                        local_3c4 = 1;
                                                      }
                                                      else {
                                                        iVar5 = 10;
                                                        pbVar16 = local_4dc;
                                                        pbVar9 = (byte *)"fall.yvel";
                                                        do {
                                                          if (iVar5 == 0) break;
                                                          iVar5 = iVar5 + -1;
                                                          bVar15 = *pbVar16 < *pbVar9;
                                                          bVar13 = *pbVar16 == *pbVar9;
                                                          pbVar16 = pbVar16 + 1;
                                                          pbVar9 = pbVar9 + 1;
                                                        } while (bVar13);
                                                        bVar14 = (!bVar15 && !bVar13) < bVar15;
                                                        bVar13 = (!bVar15 && !bVar13) == bVar15;
                                                        if (bVar13) {
                                                          local_3c0 = 0x1a;
                                                          local_3c4 = 1;
                                                        }
                                                        else {
                                                          iVar5 = 0xd;
                                                          pbVar16 = local_4dc;
                                                          pbVar9 = (byte *)"fall.recover";
                                                          do {
                                                            if (iVar5 == 0) break;
                                                            iVar5 = iVar5 + -1;
                                                            bVar14 = *pbVar16 < *pbVar9;
                                                            bVar13 = *pbVar16 == *pbVar9;
                                                            pbVar16 = pbVar16 + 1;
                                                            pbVar9 = pbVar9 + 1;
                                                          } while (bVar13);
                                                          bVar15 = (!bVar14 && !bVar13) < bVar14;
                                                          bVar13 = (!bVar14 && !bVar13) == bVar14;
                                                          if (bVar13) {
                                                            local_3c0 = 0x1b;
                                                          }
                                                          else {
                                                            iVar5 = 10;
                                                            pbVar16 = local_4dc;
                                                            pbVar9 = (byte *)"fall.time";
                                                            do {
                                                              if (iVar5 == 0) break;
                                                              iVar5 = iVar5 + -1;
                                                              bVar15 = *pbVar16 < *pbVar9;
                                                              bVar13 = *pbVar16 == *pbVar9;
                                                              pbVar16 = pbVar16 + 1;
                                                              pbVar9 = pbVar9 + 1;
                                                            } while (bVar13);
                                                            bVar14 = (!bVar15 && !bVar13) < bVar15;
                                                            bVar13 = (!bVar15 && !bVar13) == bVar15;
                                                            if (bVar13) {
                                                              local_3c0 = 0x1c;
                                                            }
                                                            else {
                                                              iVar5 = 0x11;
                                                              pbVar16 = local_4dc;
                                                              pbVar9 = (byte *)"fall.recovertime";
                                                              do {
                                                                if (iVar5 == 0) break;
                                                                iVar5 = iVar5 + -1;
                                                                bVar14 = *pbVar16 < *pbVar9;
                                                                bVar13 = *pbVar16 == *pbVar9;
                                                                pbVar16 = pbVar16 + 1;
                                                                pbVar9 = pbVar9 + 1;
                                                              } while (bVar13);
                                                              bVar15 = (!bVar14 && !bVar13) < bVar14
                                                              ;
                                                              bVar13 = (!bVar14 && !bVar13) ==
                                                                       bVar14;
                                                              if (bVar13) {
                                                                local_3c0 = 0x1d;
                                                              }
                                                              else {
                                                                iVar5 = 10;
                                                                pbVar16 = local_4dc;
                                                                pbVar9 = (byte *)"fall.kill";
                                                                do {
                                                                  if (iVar5 == 0) break;
                                                                  iVar5 = iVar5 + -1;
                                                                  bVar15 = *pbVar16 < *pbVar9;
                                                                  bVar13 = *pbVar16 == *pbVar9;
                                                                  pbVar16 = pbVar16 + 1;
                                                                  pbVar9 = pbVar9 + 1;
                                                                } while (bVar13);
                                                                bVar14 = (!bVar15 && !bVar13) <
                                                                         bVar15;
                                                                bVar13 = (!bVar15 && !bVar13) ==
                                                                         bVar15;
                                                                if (bVar13) {
                                                                  local_3c0 = 0x1e;
                                                                }
                                                                else {
                                                                  iVar5 = 0x13;
                                                                  pbVar16 = local_4dc;
                                                                  pbVar9 = (byte *)
                                                  "fall.envshake.time";
                                                  do {
                                                    if (iVar5 == 0) break;
                                                    iVar5 = iVar5 + -1;
                                                    bVar14 = *pbVar16 < *pbVar9;
                                                    bVar13 = *pbVar16 == *pbVar9;
                                                    pbVar16 = pbVar16 + 1;
                                                    pbVar9 = pbVar9 + 1;
                                                  } while (bVar13);
                                                  bVar15 = (!bVar14 && !bVar13) < bVar14;
                                                  bVar13 = (!bVar14 && !bVar13) == bVar14;
                                                  if (bVar13) {
                                                    local_3c0 = 0x1f;
                                                  }
                                                  else {
                                                    iVar5 = 0x12;
                                                    pbVar16 = local_4dc;
                                                    pbVar9 = (byte *)"fall.envshake.dir";
                                                    do {
                                                      if (iVar5 == 0) break;
                                                      iVar5 = iVar5 + -1;
                                                      bVar15 = *pbVar16 < *pbVar9;
                                                      bVar13 = *pbVar16 == *pbVar9;
                                                      pbVar16 = pbVar16 + 1;
                                                      pbVar9 = pbVar9 + 1;
                                                    } while (bVar13);
                                                    bVar14 = (!bVar15 && !bVar13) < bVar15;
                                                    bVar13 = (!bVar15 && !bVar13) == bVar15;
                                                    if (bVar13) {
                                                      local_3c0 = 0x20;
                                                    }
                                                    else {
                                                      iVar5 = 0x13;
                                                      pbVar16 = local_4dc;
                                                      pbVar9 = (byte *)"fall.envshake.ampl";
                                                      do {
                                                        if (iVar5 == 0) break;
                                                        iVar5 = iVar5 + -1;
                                                        bVar14 = *pbVar16 < *pbVar9;
                                                        bVar13 = *pbVar16 == *pbVar9;
                                                        pbVar16 = pbVar16 + 1;
                                                        pbVar9 = pbVar9 + 1;
                                                      } while (bVar13);
                                                      bVar15 = (!bVar14 && !bVar13) < bVar14;
                                                      bVar13 = (!bVar14 && !bVar13) == bVar14;
                                                      if (bVar13) {
                                                        local_3c0 = 0x21;
                                                      }
                                                      else {
                                                        iVar5 = 0x13;
                                                        pbVar16 = local_4dc;
                                                        pbVar9 = (byte *)"fall.envshake.freq";
                                                        do {
                                                          if (iVar5 == 0) break;
                                                          iVar5 = iVar5 + -1;
                                                          bVar15 = *pbVar16 < *pbVar9;
                                                          bVar13 = *pbVar16 == *pbVar9;
                                                          pbVar16 = pbVar16 + 1;
                                                          pbVar9 = pbVar9 + 1;
                                                        } while (bVar13);
                                                        bVar14 = (!bVar15 && !bVar13) < bVar15;
                                                        bVar13 = (!bVar15 && !bVar13) == bVar15;
                                                        if (bVar13) {
                                                          local_3c0 = 0x22;
                                                          local_3c4 = 1;
                                                        }
                                                        else {
                                                          iVar5 = 0x14;
                                                          pbVar16 = local_4dc;
                                                          pbVar9 = (byte *)"fall.envshake.phase";
                                                          do {
                                                            if (iVar5 == 0) break;
                                                            iVar5 = iVar5 + -1;
                                                            bVar14 = *pbVar16 < *pbVar9;
                                                            bVar13 = *pbVar16 == *pbVar9;
                                                            pbVar16 = pbVar16 + 1;
                                                            pbVar9 = pbVar9 + 1;
                                                          } while (bVar13);
                                                          if ((!bVar14 && !bVar13) != bVar14) {
                                                            pbVar16 = (byte *)(g + 0x81d2);
                                                            ghidra_fa[0] = (void *)(local_4dc);
                                                            ghidra_fa[1] = (void *)(local_11c);
                                                            pcVar17 = "Invalid varname %s in: %s";
                                                            goto LAB_080cccd9;
                                                          }
                                                          local_3c0 = 0x23;
                                                          local_3c4 = 1;
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
      }
    }
    local_7e8 = local_7e8 + 1;
  }
  if (local_3dc[0] == 0xb5) {
    if (param_1[(int)local_7e8] != '(') {
      ghidra_fa[0] = (void *)(local_11c);
      pcVar17 = "Need to specify const(varname): %s";
      pbVar16 = (byte *)(g + 0x81d2);
      goto LAB_080cccd9;
    }
    local_7e8 = local_7e8 + 1;
    bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
    while ((bVar1 & 0x20) != 0) {
      local_7e8 = local_7e8 + 1;
      bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
    }
    iVar5 = 0;
    while( true ) {
      cVar6 = param_1[(int)local_7e8];
      bVar13 = false;
      if (((*(byte *)(__ctype_b + cVar6 * 2) & 8) != 0) || (cVar6 == '_')) {
        bVar13 = true;
      }
      if ((!bVar13) && (cVar6 != '.')) break;
      local_5dc[iVar5] = cVar6;
      iVar5 = iVar5 + 1;
      local_7e8 = local_7e8 + 1;
    }
    local_5dc[iVar5] = '\0';
    bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
    while ((bVar1 & 0x20) != 0) {
      local_7e8 = local_7e8 + 1;
      bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
    }
    if (param_1[(int)local_7e8] == '\0') {
      ghidra_fa[0] = (void *)(local_11c);
      pcVar17 = "Missing closing parenthesis: %s";
      pbVar16 = (byte *)(g + 0x81d2);
      goto LAB_080cccd9;
    }
    uVar10 = 0;
    _alemu_strlwr(local_5dc);
    iVar5 = 0;
    do {
      iVar3 = strcmp(local_5dc,*(char **)((int)CnstName + iVar5));
      if (iVar3 == 0) {
        local_3c0 = uVar10;
        local_3c4 = (uint)(*(int *)((int)CnstType + iVar5) == 1);
        break;
      }
      uVar10 = uVar10 + 1;
      iVar5 = iVar5 + 4;
    } while ((int)uVar10 < 0x42);
    if (uVar10 == 0x42) {
      ghidra_fa[0] = (void *)(local_5dc);
      ghidra_fa[1] = (void *)(local_11c);
      pcVar17 = "Invalid cnstname %s in: %s";
      pbVar16 = (byte *)(g + 0x81d2);
      goto LAB_080cccd9;
    }
    local_7e8 = local_7e8 + 1;
  }
  if (local_3dc[0] == 0xb6) {
    if (param_1[(int)local_7e8] == '(') {
      local_7e8 = local_7e8 + 1;
      bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
      while ((bVar1 & 0x20) != 0) {
        local_7e8 = local_7e8 + 1;
        bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
      }
      iVar5 = 0;
      while( true ) {
        cVar6 = param_1[(int)local_7e8];
        bVar13 = false;
        if (((*(byte *)(__ctype_b + cVar6 * 2) & 8) != 0) || (cVar6 == '_')) {
          bVar13 = true;
        }
        if ((!bVar13) && (cVar6 != '.')) break;
        local_6dc[iVar5] = cVar6;
        iVar5 = iVar5 + 1;
        local_7e8 = local_7e8 + 1;
      }
      local_6dc[iVar5] = '\0';
      bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
      while ((bVar1 & 0x20) != 0) {
        local_7e8 = local_7e8 + 1;
        bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
      }
      if (param_1[(int)local_7e8] != '\0') {
        _alemu_strlwr(local_6dc);
        sprintf((char *)(g + 0x81d2),"Invalid varname %s in: %s",local_6dc,local_11c);
        return (char *)0x0;
      }
      ghidra_fa[0] = (void *)(local_11c);
      pcVar17 = "Missing closing parenthesis: %s";
      pbVar16 = (byte *)(g + 0x81d2);
    }
    else {
      ghidra_fa[0] = (void *)(local_11c);
      pcVar17 = "Need to specify stagevar(varname): %s";
      pbVar16 = (byte *)(g + 0x81d2);
    }
    goto LAB_080cccd9;
  }
  if (2 < local_3dc[0] - 0xb4U) {
    local_3c4 = 0;
  }
  if (local_3dc[0] == 0x67) goto LAB_080cc280;
  if (local_3dc[0] < 0x68) {
    if (local_3dc[0] == 7) {
LAB_080cc340:
      cVar6 = param_1[(int)local_7e8];
      while ((cVar6 != '\0' && (cVar6 != '='))) {
        local_7e8 = local_7e8 + 1;
        cVar6 = param_1[(int)local_7e8];
      }
      if (cVar6 != '\0') {
        local_7e8 = local_7e8 + 1;
      }
      bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
      while ((bVar1 & 0x20) != 0) {
        local_7e8 = local_7e8 + 1;
        bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
      }
      if (9 < (byte)(param_1[(int)local_7e8] - 0x30U)) {
        return (char *)0x0;
      }
      local_3b8 = __strtol_internal((byte *)(param_1 + (int)local_7e8),(undefined4 *)0x0,10,0);
      if (local_3dc[0] == 2) {
        local_3b8 = local_3b8 - 1;
      }
      if ((int)local_3b8 < 0) {
        if (local_3dc[0] != 2) {
          return (char *)0x0;
        }
        pbVar16 = (byte *)(g + 0x81d2);
        pcVar17 = "Anim must be > 0";
        goto LAB_080cccd9;
      }
      if ((local_3dc[0] == 7) && ((int)local_3b8 < 1)) {
        return (char *)0x0;
      }
      iVar5 = (int)param_1[(int)local_7e8];
      uVar2 = *(ushort *)(__ctype_b + iVar5 * 2);
      while ((uVar2 & 0x2800) != 0) {
        local_7e8 = local_7e8 + 1;
        iVar5 = (int)param_1[(int)local_7e8];
        uVar2 = *(ushort *)(__ctype_b + iVar5 * 2);
      }
      if (param_1[(int)local_7e8] == ',') {
        local_7e8 = local_7e8 + 1;
        iVar5 = (int)param_1[(int)local_7e8];
      }
    }
    else {
      if (local_3dc[0] < 8) {
        if (local_3dc[0] == 2) goto LAB_080cc340;
        if (local_3dc[0] < 2) goto LAB_080cc622;
        if (local_3dc[0] < 4) goto LAB_080cc600;
      }
      else if (9 < local_3dc[0]) {
        if (local_3dc[0] < 0x41) {
          if (local_3dc[0] < 0x3e) goto LAB_080cc600;
          for (; (cVar6 = param_1[(int)local_7e8], cVar6 != '\0' && (cVar6 != '='));
              local_7e8 = local_7e8 + 1) {
          }
          if (cVar6 != '\0') {
            local_7e8 = local_7e8 + 1;
          }
          iVar5 = (int)param_1[(int)local_7e8];
          bVar1 = *(byte *)(__ctype_b + 1 + iVar5 * 2);
          while ((bVar1 & 0x20) != 0) {
            local_7e8 = local_7e8 + 1;
            iVar5 = (int)param_1[(int)local_7e8];
            bVar1 = *(byte *)(__ctype_b + 1 + iVar5 * 2);
          }
          if ((*(byte *)(__ctype_b + 1 + iVar5 * 2) & 8) == 0) {
            return (char *)0x0;
          }
          local_3b4 = __strtol_internal((byte *)(param_1 + (int)local_7e8),(undefined4 *)0x0,10,0);
          uVar2 = *(ushort *)(__ctype_b + param_1[(int)local_7e8] * 2);
          while ((uVar2 & 0x2800) != 0) {
            local_7e8 = local_7e8 + 1;
            uVar2 = *(ushort *)(__ctype_b + param_1[(int)local_7e8] * 2);
          }
          if (param_1[(int)local_7e8] != ',') goto LAB_080cc622;
          local_7e8 = local_7e8 + 1;
          iVar5 = (int)param_1[(int)local_7e8];
        }
        else {
LAB_080cc622:
          iVar5 = (int)param_1[(int)local_7e8];
        }
        goto LAB_080cc626;
      }
LAB_080cc280:
      local_3c4 = 1;
      iVar5 = (int)param_1[(int)local_7e8];
      bVar1 = *(byte *)(__ctype_b + 1 + iVar5 * 2);
      while ((bVar1 & 0x20) != 0) {
        local_7e8 = local_7e8 + 1;
        iVar5 = (int)param_1[(int)local_7e8];
        bVar1 = *(byte *)(__ctype_b + 1 + iVar5 * 2);
      }
      iVar5 = *(int *)(__ctype_tolower + iVar5 * 4);
      if (iVar5 == 0x79) {
        local_3c0 = 1;
      }
      else if (iVar5 < 0x7a) {
        if (iVar5 != 0x78) {
          return (char *)0x0;
        }
        local_3c0 = 0;
      }
      else {
        if (iVar5 != 0x7a) {
          return (char *)0x0;
        }
        local_3c0 = 2;
      }
      local_7e8 = local_7e8 + 1;
      iVar5 = (int)param_1[(int)local_7e8];
    }
  }
  else {
    if (local_3dc[0] != 0x136) {
      if (local_3dc[0] < 0x137) {
        if (0xca < local_3dc[0]) {
          if (local_3dc[0] < 0xcd) goto LAB_080cc280;
          if (0x12d < local_3dc[0]) goto LAB_080cc600;
          if (299 < local_3dc[0]) goto LAB_080cc25c;
        }
        goto LAB_080cc622;
      }
      if (local_3dc[0] != 0x158) {
        if (local_3dc[0] < 0x159) {
          if (local_3dc[0] < 0x148) {
            if (local_3dc[0] < 0x140) goto LAB_080cc622;
            goto LAB_080cc25c;
          }
        }
        else if (local_3dc[0] == 0x15a) goto LAB_080cc25c;
LAB_080cc600:
        iVar5 = (int)param_1[(int)local_7e8];
        goto LAB_080cc626;
      }
    }
LAB_080cc25c:
    local_3c4 = 1;
    iVar5 = (int)param_1[(int)local_7e8];
  }
LAB_080cc626:
  bVar1 = *(byte *)(__ctype_b + 1 + iVar5 * 2);
  while ((bVar1 & 0x20) != 0) {
    local_7e8 = local_7e8 + 1;
    bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
  }
  pcVar17 = param_1 + (int)local_7e8;
  *param_6 = (int)pcVar17;
  if (local_3dc[0] == 0x14) {
    cVar6 = *pcVar17;
    while ((cVar6 != '\0' && (cVar6 != '='))) {
      local_7e8 = local_7e8 + 1;
      cVar6 = param_1[(int)local_7e8];
    }
    local_3c8 = (uint)((param_1 + (int)local_7e8)[-1] == '!');
    if (param_1[(int)local_7e8] != '\0') {
      local_7e8 = local_7e8 + 1;
    }
    bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
    while ((bVar1 & 0x20) != 0) {
      local_7e8 = local_7e8 + 1;
      bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
    }
    if (param_1[(int)local_7e8] != '\"') {
      return (char *)0x0;
    }
    iVar5 = SCtrlParseTriggerCMD(param_1 + (int)(local_7e8 + 1),(int)local_3dc,param_2,param_6);
    if (iVar5 == 0) {
      pcVar17 = "Couldn\'t parse command.";
      pbVar16 = ErrorMessage;
LAB_080cccd9:
      sprintf((char *)pbVar16,pcVar17,ghidra_fa[0],ghidra_fa[1]);
      return (char *)0x0;
    }
    if (*(char *)*param_6 != '\"') {
      return (char *)0x0;
    }
    *param_6 = (int)((char *)*param_6 + 1);
    goto LAB_080cce5b;
  }
  if (local_3dc[0] - 0x5aU < 5) {
    local_3c8 = 0;
    cVar6 = *pcVar17;
    while ((cVar6 != '\0' && (cVar6 != '='))) {
      local_7e8 = local_7e8 + 1;
      cVar6 = param_1[(int)local_7e8];
    }
    if ((0 < (int)local_7e8) && (param_1[(int)(local_7e8 + -1)] == '!')) {
      local_3c8 = 1;
    }
    if (param_1[(int)local_7e8] != '\0') {
      local_7e8 = local_7e8 + 1;
    }
    bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
    while ((bVar1 & 0x20) != 0) {
      local_7e8 = local_7e8 + 1;
      bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
    }
    if (param_1[(int)local_7e8] != '\"') {
      return (char *)0x0;
    }
    local_7e8 = local_7e8 + 1;
    cVar6 = param_1[(int)local_7e8];
    local_7e4 = local_7e8;
    while ((cVar6 != '\0' && (cVar6 != '\"'))) {
      local_7e4 = local_7e4 + 1;
      cVar6 = param_1[(int)local_7e4];
    }
    if (param_1[(int)local_7e4] != '\"') {
      return (char *)0x0;
    }
    local_3a8 = (char *)ecalloc(1,(size_t)(local_7e4 + (1 - (int)local_7e8)));
    if (local_3a8 == (char *)0x0) {
      return (char *)0x0;
    }
    strncpy(local_3a8,param_1 + (int)local_7e8,(int)local_7e4 - (int)local_7e8);
    local_3a8[(int)local_7e4 - (int)local_7e8] = '\0';
    local_3c0 = 1;
    *param_6 = (int)(param_1 + (int)(local_7e4 + 1));
    goto LAB_080cce5b;
  }
  if (local_3dc[0] - 0x2bU < 2) {
    local_3c8 = 0;
    cVar6 = *pcVar17;
    while ((cVar6 != '\0' && (cVar6 != '='))) {
      local_7e8 = local_7e8 + 1;
      cVar6 = param_1[(int)local_7e8];
    }
    bVar13 = (param_1 + (int)local_7e8)[-1] == '!';
    if (bVar13) {
      local_3c8 = 1;
    }
    local_3c8 = (uint)bVar13;
    if (param_1[(int)local_7e8] != '\0') {
      local_7e8 = local_7e8 + 1;
    }
    iVar5 = (int)param_1[(int)local_7e8];
    bVar1 = *(byte *)(__ctype_b + 1 + iVar5 * 2);
    while ((bVar1 & 0x20) != 0) {
      local_7e8 = local_7e8 + 1;
      iVar5 = (int)param_1[(int)local_7e8];
      bVar1 = *(byte *)(__ctype_b + 1 + iVar5 * 2);
    }
    iVar5 = *(int *)(__ctype_tolower + iVar5 * 4);
    if (iVar5 == 99) {
LAB_080ccaf0:
      local_3c0 = 2;
    }
    else if (iVar5 < 100) {
      if (iVar5 != 0x61) {
        return (char *)0x0;
      }
      local_3c0 = 3;
    }
    else {
      if (iVar5 != 0x6c) {
        if (iVar5 != 0x73) {
          return (char *)0x0;
        }
        goto LAB_080ccad0;
      }
      local_3c0 = 4;
    }
  }
  else {
    if (1 < local_3dc[0] - 0x2dU) {
      if (local_3dc[0] == 0x79) {
        cVar6 = *pcVar17;
        while ((cVar6 != '\0' && (cVar6 != '='))) {
          local_7e8 = local_7e8 + 1;
          cVar6 = param_1[(int)local_7e8];
        }
        local_3c8 = (uint)((param_1 + (int)local_7e8)[-1] == '!');
        if (param_1[(int)local_7e8] != '\0') {
          local_7e8 = local_7e8 + 1;
        }
        bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
        while ((bVar1 & 0x20) != 0) {
          local_7e8 = local_7e8 + 1;
          bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
        }
        cVar6 = param_1[(int)local_7e8];
        local_7e4 = local_7e8;
        if ((((cVar6 != '\0') && ((*(byte *)(__ctype_b + 1 + cVar6 * 2) & 0x20) == 0)) &&
            (cVar6 != ',')) && (cVar6 != ')')) {
          while( true ) {
            local_7e4 = local_7e4 + 1;
            cVar6 = param_1[(int)local_7e4];
            if ((cVar6 == '\0') || ((*(byte *)(__ctype_b + 1 + cVar6 * 2) & 0x20) != 0)) break;
            if ((cVar6 == ',') || (cVar6 == ')')) break;
          }
        }
        strncpy((char *)local_7dc,param_1 + (int)local_7e8,(int)local_7e4 - (int)local_7e8);
        local_7dc[(int)local_7e4 - (int)local_7e8] = 0;
        _alemu_strlwr((char *)local_7dc);
        iVar5 = 7;
        bVar13 = 0;  /* dead flag (repz cmpsb, count 7) */
        bVar15 = 0;  /* dead flag (repz cmpsb, count 7) */
        pbVar16 = local_7dc;
        pbVar9 = (byte *)"single";
        do {
          if (iVar5 == 0) break;
          iVar5 = iVar5 + -1;
          bVar13 = *pbVar16 < *pbVar9;
          bVar15 = *pbVar16 == *pbVar9;
          pbVar16 = pbVar16 + 1;
          pbVar9 = pbVar9 + 1;
        } while (bVar15);
        bVar14 = (!bVar13 && !bVar15) < bVar13;
        bVar13 = (!bVar13 && !bVar15) == bVar13;
        if (bVar13) {
          local_3c0 = 0;
        }
        else {
          iVar5 = 6;
          pbVar16 = local_7dc;
          pbVar9 = (byte *)"simul";
          do {
            if (iVar5 == 0) break;
            iVar5 = iVar5 + -1;
            bVar14 = *pbVar16 < *pbVar9;
            bVar13 = *pbVar16 == *pbVar9;
            pbVar16 = pbVar16 + 1;
            pbVar9 = pbVar9 + 1;
          } while (bVar13);
          bVar15 = (!bVar14 && !bVar13) < bVar14;
          bVar13 = (!bVar14 && !bVar13) == bVar14;
          if (bVar13) {
            local_3c0 = 1;
          }
          else {
            iVar5 = 6;
            pbVar16 = local_7dc;
            pbVar9 = (byte *)"turns";
            do {
              if (iVar5 == 0) break;
              iVar5 = iVar5 + -1;
              bVar15 = *pbVar16 < *pbVar9;
              bVar13 = *pbVar16 == *pbVar9;
              pbVar16 = pbVar16 + 1;
              pbVar9 = pbVar9 + 1;
            } while (bVar13);
            if ((!bVar15 && !bVar13) != bVar15) {
              pbVar16 = (byte *)(g + 0x81d2);
              ghidra_fa[0] = (void *)(param_1 + (int)local_7e8);
              ghidra_fa[1] = (void *)(local_11c);
              pcVar17 = "Invalid TeamMode %s in %s";
              goto LAB_080cccd9;
            }
            local_3c0 = 3;
          }
        }
        *param_6 = (int)(param_1 + (int)local_7e4);
        goto LAB_080cce5b;
      }
      if (local_3dc[0] == 0x30) {
        cVar6 = *pcVar17;
        while ((cVar6 != '\0' && (cVar6 != '='))) {
          local_7e8 = local_7e8 + 1;
          cVar6 = param_1[(int)local_7e8];
        }
        local_3c8 = (uint)((param_1 + (int)local_7e8)[-1] == '!');
        if (param_1[(int)local_7e8] != '\0') {
          local_7e8 = local_7e8 + 1;
        }
        bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
        while ((bVar1 & 0x20) != 0) {
          local_7e8 = local_7e8 + 1;
          bVar1 = *(byte *)(__ctype_b + 1 + param_1[(int)local_7e8] * 2);
        }
        local_3c0 = ParseHitAttr((int)(param_1 + (int)local_7e8),(int)param_6);
        iVar5 = local_3c0 + 1;
      }
      else {
        if (local_3dc[0] != 7) {
          if (local_3dc[0] < 8) {
            if (local_3dc[0] != 2) goto LAB_080cce5b;
          }
          else if ((0x40 < local_3dc[0]) || (local_3dc[0] < 0x3e)) goto LAB_080cce5b;
          iVar5 = SCtrlParseTriggerRange(param_1 + (int)local_7e8,(int)local_3dc,param_6);
          if (iVar5 == 0) {
            local_3c8 = 10;
            local_3bc = 0;
            local_3c0 = 0;
          }
          goto LAB_080cce5b;
        }
        iVar5 = SCtrlParseTriggerRange(pcVar17,(int)local_3dc,param_6);
      }
      if (iVar5 == 0) {
        return (char *)0x0;
      }
      goto LAB_080cce5b;
    }
    local_3c8 = 0;
    cVar6 = *pcVar17;
    while ((cVar6 != '\0' && (cVar6 != '='))) {
      local_7e8 = local_7e8 + 1;
      cVar6 = param_1[(int)local_7e8];
    }
    bVar13 = (param_1 + (int)local_7e8)[-1] == '!';
    if (bVar13) {
      local_3c8 = 1;
    }
    local_3c8 = (uint)bVar13;
    if (param_1[(int)local_7e8] != '\0') {
      local_7e8 = local_7e8 + 1;
    }
    iVar5 = (int)param_1[(int)local_7e8];
    bVar1 = *(byte *)(__ctype_b + 1 + iVar5 * 2);
    while ((bVar1 & 0x20) != 0) {
      local_7e8 = local_7e8 + 1;
      iVar5 = (int)param_1[(int)local_7e8];
      bVar1 = *(byte *)(__ctype_b + 1 + iVar5 * 2);
    }
    iVar5 = *(int *)(__ctype_tolower + iVar5 * 4);
    if (iVar5 == 0x68) goto LAB_080ccaf0;
    if (iVar5 < 0x69) {
      if (iVar5 != 0x61) {
        return (char *)0x0;
      }
LAB_080ccad0:
      local_3c0 = 1;
    }
    else {
      if (iVar5 != 0x69) {
        return (char *)0x0;
      }
      local_3c0 = 0;
    }
  }
  *param_6 = (int)(param_1 + (int)(local_7e8 + 1));
LAB_080cce5b:
  if (param_5 < (int)(local_7ec + 1)) {
    return (char *)0x0;
  }
  puVar7 = local_31c;
  puVar11 = param_3;
  for (uVar10 = (uint)local_7ec & 0x3fffffff; uVar10 != 0; uVar10 = uVar10 - 1) {
    *puVar11 = *puVar7;
    puVar7 = puVar7 + 1;
    puVar11 = puVar11 + 1;
  }
  memcpy(param_4,local_39c,(size_t)local_7ec);
  piVar4 = (int *)ecalloc(1,0x38);
  piVar8 = local_3dc;
  piVar12 = piVar4;
  for (iVar5 = 0xe; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar12 = *piVar8;
    piVar8 = piVar8 + 1;
    piVar12 = piVar12 + 1;
  }
  param_3[(int)local_7ec] = piVar4;
  local_7ec[(int)param_4] = '\x03';
  return local_7ec + 1;
}
#undef local_7ec
#undef local_7e8
#undef local_7e4
#undef local_7e0
#undef local_7dc
#undef local_6dc
#undef local_5dc
#undef local_4dc
#undef local_3dc
#undef local_3c8
#undef local_3c4
#undef local_3c0
#undef local_3bc
#undef local_3b8
#undef local_3b4
#undef local_3a8
#undef local_39c
#undef local_31c
#undef local_11c
#undef local_118
#undef local_115
#undef local_111

/* SCtrlParseTriggerCMD @ 0x080ccef0, 199 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x60-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 SCtrlParseTriggerCMD(char *param_1,int param_2,int param_3,undefined4 *param_4)

{
  char cVar1;
  int iVar2;
  size_t sVar3;
  int iVar4;
  char *in_ECX;
  undefined1 *extraout_ECX;
  char *pcVar5;
  int iVar6;
  int iVar7;
  unsigned char ghidra_frame[0x60] __attribute__((aligned(16)));
#define local_5c (*(char (*)[76])(ghidra_frame + 0x4))
  
  cVar1 = *param_1;
  if (cVar1 != '\0') {
    iVar6 = 0;
    do {
      pcVar5 = in_ECX;
      if (cVar1 == '\"') break;
      local_5c[iVar6] = cVar1;
      iVar6 = iVar6 + 1;
      cVar1 = param_1[iVar6];
      pcVar5 = local_5c;
      in_ECX = local_5c;
    } while (cVar1 != '\0');
    local_5c[iVar6] = '\0';
    iVar7 = 0;
    iVar6 = *(int *)(param_3 + 0x11bc);
    if (0 < iVar6) {
      iVar2 = *(int *)(param_3 + 0x11b8);
      do {
        iVar4 = strcmp(*(char **)(iVar2 + iVar7 * 4),local_5c);
        if (iVar4 == 0) {
          pcVar5 = *(char **)(iVar2 + iVar7 * 4);
          *(undefined4 *)(param_2 + 0x1c) =
               *(undefined4 *)(*(int *)(param_3 + 0x11b4) + 0x10 + iVar7 * 0x18);
          sVar3 = strlen(pcVar5);
          *param_4 = param_1 + sVar3;
          return 1;
        }
        iVar7 = iVar7 + 1;
        pcVar5 = extraout_ECX;
      } while (iVar7 < iVar6);
    }
    sprintf((char *)(g + 0x81d2),
            "Undefined command label: \"%s\".\nIf not misspelling in CNS, check CMD",local_5c,pcVar5
           );
  }
  return 0;
}
#undef local_5c

/* SCtrlParseTriggerRange @ 0x080ccfc0, 737 bytes
 * REVIEW: type-prop */
/* WARNING: Type propagation algorithm not settling */

undefined4 SCtrlParseTriggerRange(char *param_1,int param_2,int *param_3)

{
  uint uVar1;
  char cVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  longdouble lVar7;
  
  iVar4 = 0;
  iVar5 = (int)*param_1;
  cVar3 = param_1[1];
  cVar2 = *param_1;
  if (cVar2 != '\0') {
    if (((*(byte *)(__ctype_b + 1 + iVar5 * 2) & 8) != 0) || (iVar6 = iVar5, iVar5 == 0x2d)) {
      iVar6 = 0x3d;
    }
    if (((cVar2 == '\0') || ((*(byte *)(__ctype_b + 1 + iVar5 * 2) & 8) != 0)) || (cVar2 == '-')) {
      cVar2 = *param_1;
    }
    else {
      do {
        iVar4 = iVar4 + 1;
        if (iVar6 == 0x3d) {
          cVar2 = param_1[iVar4];
          if (cVar2 == '(') {
            iVar6 = 0x28;
          }
        }
        else {
          cVar2 = param_1[iVar4];
        }
        if ((iVar6 == 0x3d) && (cVar2 == '[')) {
          iVar6 = 0x5b;
        }
      } while (((cVar2 != '\0') && ((*(byte *)(__ctype_b + 1 + param_1[iVar4] * 2) & 8) == 0)) &&
              (cVar2 != '-'));
    }
    if (cVar2 == '\0') {
      return 0;
    }
    switch(iVar6) {
    case 0x21:
      if (cVar3 != '=') {
        return 0;
      }
      iVar5 = *(int *)(param_2 + 0x18);
      *(undefined4 *)(param_2 + 0x14) = 1;
      break;
    default:
      goto LAB_080cd299;
    case 0x28:
    case 0x5b:
      if (*(int *)(param_2 + 0x18) == 0) {
        uVar1 = __strtol_internal((byte *)(param_1 + iVar4),(undefined4 *)0x0,10,0);
        *(uint *)(param_2 + 0x1c) = uVar1;
      }
      else {
        lVar7 = __strtod_internal((int)(param_1 + iVar4),(int *)0x0,0);
        *(float *)(param_2 + 0x2c) = (float)lVar7;
      }
      for (; (cVar3 = param_1[iVar4], cVar3 != '\0' && (cVar3 != ',')); iVar4 = iVar4 + 1) {
      }
      while (((cVar3 != '\0' && (9 < (byte)(cVar3 - 0x30U))) && (cVar3 != '-'))) {
        iVar4 = iVar4 + 1;
        cVar3 = param_1[iVar4];
      }
      if (*(int *)(param_2 + 0x18) == 0) {
        uVar1 = __strtol_internal((byte *)(param_1 + iVar4),(undefined4 *)0x0,10,0);
        *(uint *)(param_2 + 0x20) = uVar1;
      }
      else {
        lVar7 = __strtod_internal((int)(param_1 + iVar4),(int *)0x0,0);
        *(float *)(param_2 + 0x30) = (float)lVar7;
      }
      for (; ((cVar3 = param_1[iVar4], cVar3 != '\0' && (cVar3 != ')')) && (cVar3 != ']'));
          iVar4 = iVar4 + 1) {
      }
      cVar3 = param_1[iVar4];
      *param_3 = (int)(param_1 + iVar4 + 1);
      if ((iVar6 == 0x5b) && (cVar3 == ']')) {
        *(undefined4 *)(param_2 + 0x14) = 10;
        return 1;
      }
      if ((iVar6 == 0x5b) && (cVar3 == ')')) {
        *(undefined4 *)(param_2 + 0x14) = 0xb;
        return 1;
      }
      if ((iVar6 == 0x28) && (cVar3 == ']')) {
        *(undefined4 *)(param_2 + 0x14) = 0xc;
        return 1;
      }
      if (iVar6 != 0x28) {
        return 0;
      }
      if (cVar3 == ')') {
        *(undefined4 *)(param_2 + 0x14) = 0xd;
        return 1;
      }
      return 0;
    case 0x3c:
      *(uint *)(param_2 + 0x14) = (cVar3 == '=') + 4;
      iVar5 = *(int *)(param_2 + 0x18);
      break;
    case 0x3d:
      iVar5 = *(int *)(param_2 + 0x18);
      *(undefined4 *)(param_2 + 0x14) = 0;
      break;
    case 0x3e:
      iVar5 = *(int *)(param_2 + 0x18);
      *(uint *)(param_2 + 0x14) = (cVar3 == '=') + 2;
    }
    if (iVar5 == 0) {
      uVar1 = __strtol_internal((byte *)(param_1 + iVar4),param_3,10,0);
      *(uint *)(param_2 + 0x1c) = uVar1;
    }
    else {
      lVar7 = __strtod_internal((int)(param_1 + iVar4),param_3,0);
      *(float *)(param_2 + 0x2c) = (float)lVar7;
    }
    return 1;
  }
LAB_080cd299:
  return 0;
}

/* SCtrlTrigArity @ 0x080cd2b0, 50 bytes */
char SCtrlTrigArity(int param_1)

{
  if (param_1 - 0x140U < 0x1d) {
    return '\x01';
  }
  if (param_1 == 0x136) {
    return '\x02';
  }
  return (param_1 == 0x131) * '\x03';
}

/* SCtrlTrigArrayTest @ 0x080cd2f0, 197 bytes
 * FIXUP: 2 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
undefined4 SCtrlTrigArrayTest(int *param_1,int param_2,int param_3)

{
  bool bVar1;
  undefined3 extraout_var;
  int *piVar2;
  undefined3 extraout_var_00;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  while (piVar2 = (int *)ArrayAccessGrpItem(param_2,-1,iVar4), piVar2 != (int *)0x0) {
    bVar1 = SCtrlTrigTest(param_1,piVar2);
    if (GHIDRA_ZEXT8(bVar1) == 0) {
      return 0;
    }
    iVar4 = iVar4 + 1;
  }
  iVar4 = 0;
  if (0 < param_3) {
    do {
      iVar3 = 0;
      piVar2 = (int *)ArrayAccessGrpItem(param_2,iVar4,0);
      if (piVar2 == (int *)0x0) {
        memcpy(g + 0x81d2,"TrigArrayTest bug",0x12);
        ErrorExit();
      }
      while (bVar1 = SCtrlTrigTest(param_1,piVar2), GHIDRA_ZEXT8(bVar1) != 0) {
        iVar3 = iVar3 + 1;
        piVar2 = (int *)ArrayAccessGrpItem(param_2,iVar4,iVar3);
        if (piVar2 == (int *)0x0) {
          return 1;
        }
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < param_3);
  }
  return 0;
}

/* SCtrlTrigTest @ 0x080cd3c0, 142 bytes
 * FIXUP: frame emulation: 2 stack locals placed at their original offsets in a 0x10-byte frame (a local's address escapes, see apply_frame_emulation) */
bool SCtrlTrigTest(int *param_1,int *param_2)

{
  int iVar1;
  undefined4 extraout_ECX;
  bool bVar2;
  unsigned char ghidra_frame[0x10] __attribute__((aligned(16)));
#define local_10 (*(int *)(ghidra_frame + 0x0))
#define local_c (*(float *)(ghidra_frame + 0x4))
  
  iVar1 = EvalExpression(param_1,param_2,&local_10,(int *)&local_c);
  if (iVar1 == 0) {
    sprintf((char *)ErrorMessage,"%4i: Fatal: Player %s (%i) in state %i: malformed expression",
            g[0x7304],param_1 + 8,param_1[1],param_1[0x2fd],extraout_ECX,extraout_ECX);
    ErrorExit();
  }
  if (iVar1 == 1) {
    bVar2 = local_10 != 0;
  }
  else {
    bVar2 = local_c != 0.0;
  }
  return bVar2;
}
#undef local_10
#undef local_c

/* SCtrlTrigEval @ 0x080cd450, 13030 bytes
 * REVIEW: pid-unaff_; calls-missing-in-pid:ABS,NAN
 * FIXUP: 33 data addresses written as literals replaced by data-image references
 * FIXUP: rewrote 13 Ghidra partial-variable accesses (x._O_S_)
 * FIXUP: removed pointer casts from 112 case labels; switch operand cast to int
 * FIXUP: 39 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: 7 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 7 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 26 stack locals placed at their original offsets in a 0x150-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void SCtrlTrigEval(int *param_1,int *param_2)

{
  float10 fVar1;
  int *piVar2;
  int *piVar3;
  char cVar4;
  undefined3 extraout_var;
  int *piVar5;
  undefined3 extraout_var_00;
  int iVar6;
  undefined3 extraout_var_01;
  undefined4 *puVar7;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  int *piVar8;
  int *piVar9;
  int *piVar10;
  int *piVar11;
  int iVar12;
  undefined3 extraout_var_07;
  uint uVar13;
  undefined3 extraout_var_08;
  undefined3 extraout_var_09;
  undefined3 extraout_var_10;
  undefined3 extraout_var_11;
  long lVar14;
  undefined3 extraout_var_12;
  undefined3 extraout_var_13;
  undefined3 extraout_var_14;
  undefined3 extraout_var_15;
  undefined3 extraout_var_16;
  undefined3 extraout_var_17;
  undefined3 extraout_var_18;
  undefined3 extraout_var_19;
  undefined3 extraout_var_20;
  undefined3 extraout_var_21;
  undefined3 extraout_var_22;
  undefined3 extraout_var_23;
  undefined3 extraout_var_24;
  undefined3 extraout_var_25;
  undefined3 extraout_var_26;
  undefined3 extraout_var_27;
  undefined3 extraout_var_28;
  undefined3 extraout_var_29;
  undefined3 extraout_var_30;
  undefined3 extraout_var_31;
  int iVar15;
  undefined3 extraout_var_32;
  undefined3 extraout_var_33;
  undefined3 extraout_var_34;
  undefined3 extraout_var_35;
  undefined3 extraout_var_36;
  undefined3 extraout_var_37;
  int *extraout_ECX;
  int *extraout_ECX_00;
  int *extraout_ECX_01;
  int *extraout_ECX_02;
  undefined4 extraout_ECX_03;
  undefined4 extraout_EDX;
  int *extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 extraout_EDX_04;
  int *extraout_EDX_05;
  int *extraout_EDX_06;
  int *extraout_EDX_07;
  undefined4 extraout_EDX_08;
  undefined4 extraout_EDX_09;
  int *extraout_EDX_10;
  undefined4 extraout_EDX_11;
  undefined4 extraout_EDX_12;
  uint extraout_EDX_13;
  undefined4 extraout_EDX_14;
  undefined4 extraout_EDX_15;
  undefined4 extraout_EDX_16;
  int *extraout_EDX_17;
  int *extraout_EDX_18;
  int *extraout_EDX_19;
  int *extraout_EDX_20;
  int *extraout_EDX_21;
  int *extraout_EDX_22;
  int *extraout_EDX_23;
  int *extraout_EDX_24;
  int *extraout_EDX_25;
  int *piVar16;
  int *unaff_EBP;
  bool bVar17;
  bool bVar18;
  bool bVar19;
  ushort in_FPUControlWord;
  longdouble lVar20;
  longdouble lVar21;
  byte *__s;
  char *pcVar22;
  unsigned char ghidra_frame[0x150] __attribute__((aligned(16)));
#define local_150 (*(int **)(ghidra_frame + 0x0))
#define local_14c (*(int **)(ghidra_frame + 0x4))
#define local_148 (*(int *)(ghidra_frame + 0x8))
#define local_144 (*(int *)(ghidra_frame + 0xc))
#define local_140 (*(int *)(ghidra_frame + 0x10))
#define local_13c (*(int *)(ghidra_frame + 0x14))
#define local_138 (*(int *)(ghidra_frame + 0x18))
#define local_134 (*(int **)(ghidra_frame + 0x1c))
#define local_11c (*(int **)(ghidra_frame + 0x34))
#define local_118 (*(int **)(ghidra_frame + 0x38))
#define local_114 (*(int **)(ghidra_frame + 0x3c))
#define local_110 (*(int **)(ghidra_frame + 0x40))
#define local_10c (*(float *)(ghidra_frame + 0x44))
#define local_108 (*(float *)(ghidra_frame + 0x48))
#define local_104 (*(int **)(ghidra_frame + 0x4c))
#define local_100 (*(float (*)[5])(ghidra_frame + 0x50))
#define local_ec (*(double *)(ghidra_frame + 0x64))
#define local_e0 (*(ushort *)(ghidra_frame + 0x70))
#define local_cc (*(double *)(ghidra_frame + 0x84))
#define local_c0 (*(ushort *)(ghidra_frame + 0x90))
#define local_8c (*(double *)(ghidra_frame + 0xc4))
#define local_7c (*(double *)(ghidra_frame + 0xd4))
#define local_6c (*(double *)(ghidra_frame + 0xe4))
#define local_5c (*(double *)(ghidra_frame + 0xf4))
#define local_24 (*(int **)(ghidra_frame + 0x12c))
#define local_20 (*(undefined4 *)(ghidra_frame + 0x130))
  
  local_110 = (int *)0x0;
  local_114 = (int *)0x0;
  local_118 = (int *)0x0;
  local_11c = param_1;
  local_104 = (int *)0x0;
  iVar15 = param_2[5];
  bVar17 = false;
  iVar6 = param_2[1];
  local_100[0] = 0.0;
  if (iVar6 == 1) {
    piVar5 = (int *)param_1[0x988];
    if (piVar5 != (int *)0x0) goto LAB_080cd965;
    Warn((int)param_1,(int)&DAT_0827c84d);
    cVar4 = SCtrlTrigArity(*param_2);
    MyStackIdx = (int *)((int)MyStackIdx + GHIDRA_ZEXT8(cVar4) * -2);
    piVar11 = extraout_ECX;
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.");
      ErrorExit();
      piVar11 = extraout_ECX_00;
    }
    piVar5 = (int *)((int)MyStackIdx + 1);
    bVar19 = SBORROW4((int)piVar5,0x7e);
    bVar18 = (int)MyStackIdx + -0x7d < 0;
    bVar17 = piVar5 == (int *)0x7e;
    MyStackIdx = piVar5;
    MyStack[(int)piVar5] = 0;
LAB_080cfcc3:
    piVar5 = piVar11;
    if (bVar17 || bVar19 != bVar18) goto LAB_080d04a0;
    goto LAB_080d0489;
  }
  piVar5 = param_1;
  if (iVar6 != 2) {
    if (iVar6 == 3) {
      iVar6 = EvalExpressionI((int)param_1,param_2 + 2,1);
      if (iVar6 < 0) {
        iVar6 = 0;
        Warn((int)param_1,(int)&DAT_0827cae0);
      }
      piVar5 = (int *)HelperAccessID((int)param_1,iVar6);
      if (piVar5 == (int *)0x0) {
        VWarn((int)param_1,"has no helper %i",iVar6,0);
        cVar4 = SCtrlTrigArity(*param_2);
        MyStackIdx = (int *)((int)MyStackIdx + GHIDRA_ZEXT8(cVar4) * -2);
        piVar11 = extraout_ECX_01;
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.",iVar6,iVar6);
          ErrorExit();
          piVar11 = extraout_ECX_02;
        }
        piVar5 = (int *)((int)MyStackIdx + 1);
        bVar19 = SBORROW4((int)piVar5,0x7e);
        bVar18 = (int)MyStackIdx + -0x7d < 0;
        bVar17 = piVar5 == (int *)0x7e;
        MyStackIdx = piVar5;
        MyStack[(int)piVar5] = 0;
        goto LAB_080cfcc3;
      }
      goto LAB_080cd965;
    }
    if (iVar6 == 4) {
      iVar6 = EvalExpressionI((int)param_1,param_2 + 2,1);
      if (iVar6 < -1) {
        iVar6 = -1;
        Warn((int)param_1,(int)&DAT_0827cb20);
      }
      puVar7 = (undefined4 *)TargetAccessID(param_1[0x88],iVar6);
      if (puVar7 == (undefined4 *)0x0) {
        if (local_104 == (int *)0xffffffff) {
          Warn((int)param_1,(int)&DAT_0827c895);
        }
        else {
          VWarn((int)param_1,"has no target with hit ID %i",iVar6,extraout_EDX);
        }
        cVar4 = SCtrlTrigArity(*param_2);
        MyStackIdx = (int *)((int)MyStackIdx + GHIDRA_ZEXT8(cVar4) * -2);
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.",param_2,param_2);
          ErrorExit();
        }
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        goto LAB_080d03bd;
      }
      piVar5 = (int *)*puVar7;
      goto LAB_080cd965;
    }
    if (iVar6 == 5) {
      piVar10 = (int *)EvalExpressionI((int)param_1,param_2 + 2,1);
      if ((int)piVar10 < 0) {
        piVar10 = (int *)0x0;
        Warn((int)param_1,(int)&DAT_0827cb60);
      }
      piVar5 = (int *)PartnerAccess((int)param_1,(int)piVar10);
      if (piVar5 != (int *)0x0) goto LAB_080cd965;
      VWarn((int)param_1,"has no %i-th partner",piVar10,0);
      cVar4 = SCtrlTrigArity(*param_2);
      MyStackIdx = (int *)((int)MyStackIdx + GHIDRA_ZEXT8(cVar4) * -2);
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",param_1,param_1);
        ErrorExit();
      }
      piVar5 = (int *)((int)MyStackIdx + 1);
      bVar19 = SBORROW4((int)piVar5,0x7e);
      bVar18 = (int)MyStackIdx + -0x7d < 0;
      bVar17 = piVar5 == (int *)0x7e;
      MyStackIdx = piVar5;
      MyStack[(int)piVar5] = 0;
      goto LAB_080cfec3;
    }
    if (iVar6 == 6) {
      iVar6 = EvalExpressionI((int)param_1,param_2 + 2,1);
      if (iVar6 < 0) {
        iVar6 = 0;
        Warn((int)param_1,(int)&DAT_0827cba0);
      }
      piVar5 = (int *)EnemyAccess((int)param_1,iVar6);
      if (piVar5 != (int *)0x0) goto LAB_080cd965;
      VWarn((int)param_1,"has no %i-th enemy",iVar6);
      cVar4 = SCtrlTrigArity(*param_2);
      local_14c = (int *)((int)MyStackIdx + GHIDRA_ZEXT8(cVar4) * -2);
      piVar5 = local_14c;
      if (0x7e < (int)local_14c) {
        MyStackIdx = local_14c;
        sprintf((char *)ErrorMessage,"Expression stack overflow.",extraout_ECX_03,extraout_ECX_03);
        ErrorExit();
        local_14c = extraout_EDX_00;
        piVar5 = MyStackIdx;
      }
      goto LAB_080ce674;
    }
    if (iVar6 != 7) {
      if (iVar6 == 8) {
        iVar6 = EvalExpressionI((int)param_1,param_2 + 2,1);
        if (iVar6 < 0) {
          iVar6 = 0;
          Warn((int)param_1,(int)&DAT_0827cc20);
        }
        piVar5 = (int *)PlayerAccessID(iVar6);
        if (piVar5 == (int *)0x0) {
          VWarn((int)param_1,"tried to access non-existent player with ID %i",iVar6,extraout_EDX_02)
          ;
          cVar4 = SCtrlTrigArity(*param_2);
          MyStackIdx = (int *)((int)MyStackIdx + GHIDRA_ZEXT8(cVar4) * -2);
          if (0x7e < (int)MyStackIdx) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.",param_2,param_2);
            ErrorExit();
          }
          MyStackIdx = (int *)((int)MyStackIdx + 1);
          piVar5 = param_1;
          goto LAB_080d03bd;
        }
      }
      goto LAB_080cd965;
    }
    iVar6 = EvalExpressionI((int)param_1,param_2 + 2,1);
    if (iVar6 < 0) {
      iVar6 = 0;
      Warn((int)param_1,(int)&DAT_0827cbe0);
    }
    piVar5 = (int *)EnemyAccessNear((int)param_1,iVar6);
    if (piVar5 != (int *)0x0) goto LAB_080cd965;
    VWarn((int)param_1,"has no %i-th nearest enemy",iVar6,extraout_EDX_01);
    cVar4 = SCtrlTrigArity(*param_2);
    MyStackIdx = (int *)((int)MyStackIdx + GHIDRA_ZEXT8(cVar4) * -2);
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",param_2,param_2);
      ErrorExit();
    }
    MyStackIdx = (int *)((int)MyStackIdx + 1);
    piVar5 = param_1;
    goto LAB_080d03bd;
  }
  piVar5 = (int *)param_1[0x989];
  if (piVar5 == (int *)0x0) {
    Warn((int)param_1,(int)&DAT_0827c85b);
    cVar4 = SCtrlTrigArity(*param_2);
    MyStackIdx = (int *)((int)MyStackIdx + GHIDRA_ZEXT8(cVar4) * -2);
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",param_2,param_2);
      ErrorExit();
    }
    MyStackIdx = (int *)((int)MyStackIdx + 1);
    piVar5 = param_1;
    goto LAB_080d03bd;
  }
LAB_080cd965:
  piVar8 = (int *)HelperParent((int)piVar5);
  piVar9 = (int *)HelperRoot((int)piVar5);
  bVar18 = piVar5 != param_1;
  piVar10 = (int *)g[0x731d];
  piVar11 = g;
  if (piVar10 == (int *)0x0) {
    local_134 = (int *)0x0;
    unaff_EBP = (int *)0x0;
    if (piVar5[3] == 1) {
      unaff_EBP = (int *)g[0x73db];
      local_134 = (int *)g[0x73dd];
    }
    else if (piVar5[3] == 2) {
      unaff_EBP = (int *)g[0x73da];
      local_134 = (int *)g[0x73dc];
    }
    local_110 = (int *)piVar5[0xd09];
    piVar11 = local_110;
    if ((unaff_EBP == (int *)0x0) || (local_134 == (int *)0x0)) {
      if (local_110 != (int *)0x0) {
        if (local_110[7] == 1) {
          piVar11 = (int *)HelperRoot((int)local_110);
          local_118 = unaff_EBP;
          if (piVar11 == unaff_EBP) {
            local_118 = local_134;
            piVar11 = local_134;
          }
        }
        else {
          local_118 = unaff_EBP;
          if (local_110 == unaff_EBP) {
            local_118 = local_134;
          }
        }
      }
    }
    else {
      local_118 = local_134;
      if ((local_110 != unaff_EBP) && (local_118 = unaff_EBP, local_110 != local_134)) {
        piVar10 = (int *)PlayerDistX((int)piVar5,(int)unaff_EBP);
        if ((int)piVar10 < 0) {
          piVar10 = (int *)-(int)piVar10;
        }
        piVar11 = (int *)PlayerDistX((int)piVar5,(int)local_134);
        if ((int)piVar11 < 0) {
          piVar11 = (int *)-(int)piVar11;
        }
        local_118 = local_134;
        if ((int)piVar11 <= (int)piVar10) {
          local_118 = unaff_EBP;
        }
      }
    }
    if (piVar5[7] == 1) {
      piVar10 = piVar9;
      if (piVar9 != (int *)0x0) {
        iVar6 = piVar9[2];
        goto LAB_080cdb03;
      }
      iVar6 = piVar5[3];
      if (iVar6 == 1) {
        piVar11 = (int *)g[0x73da];
        local_114 = piVar11;
        if (piVar11 == (int *)0x0) {
          piVar11 = (int *)g[0x73dc];
          local_114 = piVar11;
        }
      }
      else if ((iVar6 == 2) &&
              (piVar11 = (int *)g[0x73db], local_114 = piVar11, piVar11 == (int *)0x0)) {
        piVar11 = (int *)g[0x73dd];
        local_114 = piVar11;
      }
    }
    else {
      iVar6 = piVar5[2];
LAB_080cdb03:
      local_104 = (int *)(iVar6 + 2);
      if (4 < (int)local_104) {
        local_104 = (int *)(iVar6 + -2);
      }
      piVar11 = (int *)g[(int)local_104 + 0x73d9];
      iVar6 = piVar5[3];
      local_114 = piVar11;
    }
    if (iVar6 == 1) {
      piVar11 = (int *)g[0x73da];
      local_11c = piVar11;
    }
    if (iVar6 == 2) {
      piVar11 = (int *)g[0x73db];
      local_11c = piVar11;
    }
  }
  piVar3 = g;
  piVar2 = MyStackIdx;
  piVar16 = (int *)*param_2;
  switch((int)piVar16) {
  case 0x0:
    local_104 = (int *)piVar5[0x37f];
    break;
  case 0x1:
    iVar6 = AnimGetLooptime((undefined4 *)piVar5[0x4ef]);
    local_104 = (int *)(*(int *)(piVar5[0x4ef] + 0x1c) - iVar6);
    break;
  case 0x2:
    iVar6 = param_2[9];
    goto LAB_080d0371;
  case 0x3:
    local_104 = (int *)AnimCurIDno((undefined4 *)piVar5[0x4ef]);
    break;
  case 0x4:
    iVar6 = param_2[7];
    if (iVar6 == 1) {
      local_100[0] = GHIDRA_I2F(piVar5[0x68]);
      goto LAB_080cf4e5;
    }
    if (iVar6 < 2) {
      if (iVar6 == 0) {
        piVar16 = (int *)*param_2;
        local_100[0] = (GHIDRA_I2F(piVar5[0x67]) - GHIDRA_I2F(g[0x730f])) - 160.0;
      }
    }
    else {
LAB_080ce0c8:
      if (iVar6 == 2) {
        local_100[0] = GHIDRA_I2F(piVar5[0x69]);
        goto LAB_080cf4e5;
      }
    }
    goto LAB_080d04fc;
  case 0x5:
    iVar6 = param_2[7];
    if (iVar6 == 1) {
      piVar16 = (int *)*param_2;
      local_100[0] = (GHIDRA_I2F(piVar5[0x68]) - GHIDRA_I2F(g[0x7310])) + (float)g[0x4140];
    }
    else {
      if (1 < iVar6) goto LAB_080ce0c8;
      if (iVar6 == 0) {
        piVar16 = (int *)*param_2;
        local_100[0] = GHIDRA_I2F(piVar5[0x67]) - GHIDRA_I2F(g[0x730f]);
      }
    }
    goto LAB_080d04fc;
  case 0x6:
    iVar6 = param_2[7];
    if (iVar6 == 1) {
      local_100[0] = GHIDRA_I2F(piVar5[0x6e]);
      goto LAB_080cf4e5;
    }
    if (iVar6 < 2) {
      if (iVar6 == 0) {
        piVar16 = (int *)*param_2;
        local_100[0] = (float10)piVar5[100] * GHIDRA_I2F(piVar5[0x6d]);
      }
    }
    else if (iVar6 == 2) {
      local_100[0] = GHIDRA_I2F(piVar5[0x6f]);
      goto LAB_080cf4e5;
    }
    goto LAB_080d04fc;
  case 0x7:
    local_104 = (int *)(piVar5[0x37f] % param_2[9]);
    break;
  case 0x8:
    if (local_110 == (int *)0x0) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",piVar5,piVar5);
        ErrorExit();
      }
      piVar5 = (int *)((int)MyStackIdx + 1);
      bVar19 = SBORROW4((int)piVar5,0x7e);
      bVar18 = (int)MyStackIdx + -0x7d < 0;
      bVar17 = piVar5 == (int *)0x7e;
      MyStackIdx = piVar5;
      MyStack[(int)piVar5] = 0;
      goto LAB_080cfec3;
    }
    iVar6 = param_2[7];
    if (iVar6 == 1) {
      local_100[0] = GHIDRA_I2F(piVar5[0x68]);
LAB_080cf44b:
      local_100[0] = GHIDRA_I2F(local_110[0x68]) - local_100[0];
LAB_080cf451:
      piVar16 = (int *)*param_2;
    }
    else if (iVar6 < 2) {
joined_r0x080cf410:
      if (iVar6 == 0) {
        iVar6 = PlayerDistX((int)piVar5,(int)local_110);
LAB_080cf42e:
        local_100[0] = (float10)iVar6;
        piVar16 = (int *)*param_2;
        unaff_EBP = local_110;
      }
    }
    else if (iVar6 == 2) {
      local_100[0] = GHIDRA_I2F(piVar5[0x69]);
LAB_080cf46a:
      piVar16 = (int *)*param_2;
      local_100[0] = GHIDRA_I2F(local_110[0x69]) - local_100[0];
    }
    goto LAB_080d04fc;
  case 0x9:
    if (local_110 == (int *)0x0) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",piVar5,piVar5);
        ErrorExit();
      }
      piVar5 = (int *)((int)MyStackIdx + 1);
      bVar19 = SBORROW4((int)piVar5,0x7e);
      bVar18 = (int)MyStackIdx + -0x7d < 0;
      bVar17 = piVar5 == (int *)0x7e;
      MyStackIdx = piVar5;
      MyStack[(int)piVar5] = 0;
      goto LAB_080cfec3;
    }
    iVar6 = param_2[7];
    if (iVar6 == 1) {
      piVar16 = (int *)*param_2;
      local_100[0] = GHIDRA_I2F(local_110[0x68]) - GHIDRA_I2F(piVar5[0x68]);
    }
    else if (iVar6 < 2) {
      if (iVar6 == 0) {
        iVar6 = PlayerBodyDistX((int)piVar5,(int)local_110);
        goto LAB_080cf42e;
      }
    }
    else if (iVar6 == 2) {
      local_100[0] = GHIDRA_I2F(local_110[0x69]) - GHIDRA_I2F(piVar5[0x69]);
      goto LAB_080cf451;
    }
    goto LAB_080d04fc;
  case 0xa:
    if (local_110 == (int *)0x0) {
LAB_080cffd7:
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",piVar16,piVar16);
        ErrorExit();
      }
      piVar5 = (int *)((int)MyStackIdx + 1);
      bVar19 = SBORROW4((int)piVar5,0x7e);
      bVar18 = (int)MyStackIdx + -0x7d < 0;
      bVar17 = piVar5 == (int *)0x7e;
      MyStackIdx = piVar5;
      MyStack[(int)piVar5] = 0;
      goto LAB_080d0017;
    }
    local_104 = (int *)local_110[0x58];
    break;
  case 0xb:
  case 0xc:
    piVar5[0x75] = (int)GHIDRA_FIST32((float)(g[0x10a3] + -0xa0) / GHIDRA_I2F(piVar5[0x4d2]) + (float)g[0x7311] +
                              160.0);
    local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
    piVar5[0x76] = (int)GHIDRA_FIST32((float)(0xa0 - piVar3[0x10a2]) / GHIDRA_I2F(piVar5[0x4d2]) +
                              (float10)piVar3[0x7311] + 160.0);
    local_104 = (int *)0x0;
    iVar6 = param_2[9];
    if ((iVar6 != 0) && (local_104 = (int *)(uint)(piVar5[0x380] == 3), piVar5[0x380] == 4)) {
      unaff_EBP = (int *)0x2;
      local_104 = unaff_EBP;
    }
    if (*param_2 == 0xb) {
      if (iVar6 != 0) {
        local_104 = (int *)((int)local_104 + piVar5[0x7d]);
      }
      iVar6 = piVar5[100];
      if (iVar6 == 1) {
        iVar12 = piVar5[0x76];
      }
      else {
        iVar12 = piVar5[0x75];
      }
      fVar1 = (float)(iVar6 * (int)local_104) + GHIDRA_I2F(piVar5[0x67]);
      iVar6 = -iVar6;
    }
    else {
      if (iVar6 != 0) {
        unaff_EBP = (int *)piVar5[0x7e];
        local_104 = (int *)((int)local_104 + (int)unaff_EBP);
      }
      iVar6 = piVar5[100];
      if (iVar6 == 1) {
        iVar12 = piVar5[0x75];
      }
      else {
        iVar12 = piVar5[0x76];
      }
      fVar1 = GHIDRA_I2F(piVar5[0x67]) - (float)(iVar6 * (int)local_104);
    }
    fVar1 = (float10)iVar6 * (fVar1 - (float10)iVar12);
LAB_080cdf3d:
    local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
    local_24 = (int *)(int)GHIDRA_FIST32(fVar1);
    goto LAB_080cdf6f;
  default:
    __s = (byte *)(g + 0x81d2);
    piVar5 = (int *)*param_2;
    pcVar22 = "Missing trigger code %i";
    piVar11 = unaff_EBP;
LAB_080d04e9:
    sprintf((char *)__s,pcVar22,piVar5,piVar11);
    ErrorExit();
    piVar16 = (int *)*param_2;
    goto LAB_080d04fc;
  case 0xf:
    local_104 = (int *)piVar5[0x58];
    break;
  case 0x10:
    local_104 = (int *)piVar5[0x59];
    break;
  case 0x11:
    local_104 = (int *)local_11c[0x5c];
    goto LAB_080cdffa;
  case 0x12:
    local_104 = (int *)local_11c[0x5d];
LAB_080cdffa:
    local_104 = (int *)*local_104;
    break;
  case 0x13:
    local_104 = (int *)piVar5[0x389];
    break;
  case 0x14:
    local_104 = (int *)(param_2[7] + -1);
    bVar18 = KBCommandIsValid((int)(piVar5 + 0x25a),param_2[7]);
    if ((GHIDRA_ZEXT8(bVar18) != 0) && (local_104 = (int *)param_2[7], iVar15 == 0)) {
      AIInsertCommand(piVar5 + 0xcef,(int)local_104);
    }
    break;
  case 0x1e:
    local_104 = (int *)piVar5[0x4e7];
    break;
  case 0x1f:
    local_104 = (int *)piVar5[0x4e8];
    break;
  case 0x20:
    bVar18 = piVar5[0x38c] == 2;
    goto LAB_080ce1f7;
  case 0x21:
    bVar18 = piVar5[0x38c] == 1;
    goto LAB_080ce1f7;
  case 0x22:
    if (1 < piVar5[0x38c] - 1U) goto LAB_080cdd3a;
    goto LAB_080ce1fd;
  case 0x23:
    bVar18 = piVar5[0x38c] == 4;
LAB_080ce1f7:
    if (!bVar18) goto LAB_080cdd3a;
LAB_080ce1fd:
    iVar6 = piVar5[0x38d];
LAB_080ce203:
    local_104 = (int *)(iVar6 + 1);
    break;
  case 0x24:
    local_104 = (int *)PlayerInAnyGuardDist((int)piVar5);
    break;
  case 0x28:
    local_104 = (int *)piVar5[0x2fd];
    break;
  case 0x29:
    local_104 = (int *)piVar5[0x2fe];
    break;
  case 0x2a:
    local_14c = piVar16;
    if (local_110 == (int *)0x0) {
LAB_080ce647:
      piVar5 = MyStackIdx;
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",MyStackIdx,MyStackIdx);
        ErrorExit();
        local_14c = extraout_EDX_07;
        piVar5 = MyStackIdx;
      }
LAB_080ce674:
      MyStackIdx = (int *)((int)piVar5 + 1);
      bVar19 = SBORROW4((int)MyStackIdx,0x7e);
      bVar18 = (int)piVar5 + -0x7d < 0;
      bVar17 = MyStackIdx == (int *)0x7e;
      MyStack[(int)MyStackIdx] = 0;
      goto LAB_080d0485;
    }
    local_104 = (int *)local_110[0x2fd];
    break;
  case 0x2b:
    local_104 = (int *)piVar5[0x380];
    break;
  case 0x2c:
    if (local_110 == (int *)0x0) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",unaff_EBP,unaff_EBP);
        ErrorExit();
      }
      piVar11 = (int *)((int)MyStackIdx + 1);
      MyStackIdx = piVar11;
      MyStack[(int)piVar11] = 0;
      unaff_EBP = param_2;
joined_r0x080cf697:
      piVar5 = unaff_EBP;
      if ((int)piVar11 < 0x7f) goto LAB_080d04a0;
      goto LAB_080d0489;
    }
    local_104 = (int *)local_110[0x380];
    break;
  case 0x2d:
    local_104 = (int *)piVar5[0x381];
    break;
  case 0x2e:
    if (local_110 == (int *)0x0) {
      piVar11 = MyStackIdx;
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",piVar10,piVar10);
        ErrorExit();
        piVar11 = MyStackIdx;
      }
      MyStackIdx = (int *)((int)piVar11 + 1);
      bVar19 = SBORROW4((int)MyStackIdx,0x7e);
      bVar18 = (int)piVar11 + -0x7d < 0;
      bVar17 = MyStackIdx == (int *)0x7e;
      MyStack[(int)MyStackIdx] = 0;
      goto LAB_080cfcc3;
    }
    local_104 = (int *)local_110[0x381];
    break;
  case 0x2f:
    local_104 = (int *)piVar5[899];
    break;
  case 0x30:
    local_104 = (int *)0x0;
    if ((piVar5[0x381] == 1) && ((param_2[7] & piVar5[0x459] & 7U) != 0)) {
      uVar13 = param_2[7] & piVar5[0x459] & 0xfffffff8;
LAB_080cddb3:
      local_104 = (int *)0x0;
      if (uVar13 != 0) goto LAB_080cddb9;
    }
    break;
  case 0x33:
    lVar14 = random();
    local_104 = (int *)(lVar14 % 1000);
    break;
  case 0x3c:
    local_104 = (int *)ProjArrayCountActive((int *)piVar5[0x87]);
    break;
  case 0x3e:
    if ((piVar5[0x85] == 2) && ((piVar5[0x84] == param_2[9] || (param_2[9] == 0)))) {
      local_104 = (int *)piVar5[0x86];
      unaff_EBP = (int *)param_2[10];
      piVar5 = unaff_EBP;
LAB_080cea1d:
      if (piVar5 == (int *)0x0) {
        bVar17 = true;
      }
      break;
    }
    local_150 = (int *)(uint)(param_2[10] == 0);
LAB_080d00b0:
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",piVar5,piVar5);
      ErrorExit();
    }
    piVar5 = (int *)((int)MyStackIdx + 1);
    MyStackIdx = piVar5;
    MyStack[(int)piVar5] = (int)local_150;
    goto joined_r0x080d00e6;
  case 0x3f:
    if (piVar5[0x85] == 1) {
      iVar6 = param_2[9];
      if (piVar5[0x84] != iVar6) {
joined_r0x080cea0c:
        if (iVar6 != 0) goto LAB_080cea30;
      }
LAB_080cea0e:
      local_104 = (int *)piVar5[0x86];
      piVar5 = (int *)param_2[10];
      goto LAB_080cea1d;
    }
    goto LAB_080cea30;
  case 0x40:
    if ((piVar5[0x85] != 0) && (piVar5[0x85] != 3)) {
      iVar6 = param_2[9];
      if (piVar5[0x84] != iVar6) goto joined_r0x080cea0c;
      goto LAB_080cea0e;
    }
LAB_080cea30:
    piVar5 = (int *)(uint)(param_2[10] == 0);
    goto LAB_080d0643;
  case 0x5a:
    piVar11 = (int *)param_2[0xd];
    local_118 = (int *)*piVar5;
    goto LAB_080ceb09;
  case 0x5b:
    if (local_110 != (int *)0x0) {
      piVar11 = (int *)param_2[0xd];
      local_118 = (int *)*local_110;
      goto LAB_080ceb09;
    }
    goto LAB_080cdd3a;
  case 0x5c:
    if (local_114 != (int *)0x0) {
      piVar11 = (int *)param_2[0xd];
      unaff_EBP = (int *)*local_114;
      local_118 = unaff_EBP;
      goto LAB_080ceb09;
    }
    goto LAB_080cdd3a;
  case 0x5d:
    if (local_118 != (int *)0x0) {
      piVar11 = (int *)param_2[0xd];
      local_118 = (int *)*local_118;
      goto LAB_080ceb09;
    }
    goto LAB_080cdd3a;
  case 0x5e:
    unaff_EBP = (int *)param_2[0xd];
    local_118 = (int *)(*piVar5 + 0x60);
    piVar11 = unaff_EBP;
LAB_080ceb09:
    iVar6 = _alemu_stricmp((char *)local_118,(char *)piVar11);
LAB_080ceb15:
    local_104 = (int *)(uint)(iVar6 == 0);
    break;
  case 0x5f:
    local_104 = (int *)PartnerCount((int)piVar5);
    break;
  case 0x60:
    local_104 = (int *)EnemyCount((int)piVar5);
    break;
  case 0x61:
    local_104 = (int *)piVar5[1];
    break;
  case 0x63:
    local_104 = (int *)piVar5[100];
    break;
  case 0x64:
switchD_080cdb66_caseD_64:
    local_104 = (int *)piVar5[0x41c];
    break;
  case 0x65:
    local_104 = (int *)(uint)(piVar5[0x40d] < 1);
    break;
  case 0x66:
    local_104 = (int *)((uint)piVar5[0x40e] >> 0x1f);
    break;
  case 0x67:
    if (param_2[7] == 0) {
      piVar16 = (int *)*param_2;
      local_100[0] = (float10)piVar5[100] * GHIDRA_I2F(piVar5[0x416]);
    }
    else if (param_2[7] == 1) goto switchD_080ceefc_caseD_12;
    goto LAB_080d04fc;
  case 0x68:
    local_104 = (int *)piVar5[0x386];
    break;
  case 0x69:
    local_104 = (int *)0x0;
    if ((piVar5[0x420] != 0) && (piVar5[0x422] <= piVar5[0x421])) {
      local_104 = (int *)0x1;
    }
    break;
  case 0x6b:
    iVar6 = piVar5[0x4f1];
    goto LAB_080ce203;
  case 0x6c:
    unaff_EBP = (int *)g[0x7513];
    if (((unaff_EBP == (int *)0x0) || (g[0x7512] != piVar5[3])) ||
       (iVar6 = TeamHasFullLife(g[0x7512]), iVar6 == 0)) goto LAB_080cdd3a;
LAB_080cddb9:
    local_104 = (int *)0x1;
    break;
  case 0x6d:
    if (((g[0x7513] == param_2[9]) || (param_2[9] == -1)) && (g[0x7512] == piVar5[3]))
    goto LAB_080cddb9;
    goto LAB_080cdd3a;
  case 0x6e:
    if (((g[0x7513] == param_2[9]) || (param_2[9] == -1)) &&
       ((g[0x7512] != piVar5[3] && (g[0x7512] != 0)))) goto LAB_080cddb9;
    goto LAB_080cdd3a;
  case 0x6f:
    local_104 = (int *)0x0;
    if (g[0x7512] == 0) {
      uVar13 = g[0x7513];
      goto LAB_080cddb3;
    }
    break;
  case 0x70:
    iVar6 = GameMatchWinner();
    goto LAB_080cddcb;
  case 0x71:
    local_104 = (int *)g[0x7304];
    break;
  case 0x72:
    local_104 = (int *)g[0x7506];
    break;
  case 0x73:
    local_104 = (int *)g[0x7511];
    break;
  case 0x74:
    local_104 = (int *)g[0x7543];
    break;
  case 0x75:
    local_104 = (int *)piVar5[0xd0b];
    break;
  case 0x78:
    local_104 = (int *)piVar5[3];
    break;
  case 0x79:
    local_104 = (int *)g[piVar5[4] * 0x17 + 0x4106];
    if (1 < g[piVar5[4] * 0x6a7 + 0x33b9]) {
      local_104 = (int *)0x3;
    }
    piVar5 = (int *)param_2[7];
LAB_080cedc3:
    bVar18 = local_104 == piVar5;
    goto LAB_080cedc9;
  case 0x7a:
    if (g[0x33b3] == 0) {
      bVar18 = piVar5[3] == 1;
      goto LAB_080cedc9;
    }
    iVar6 = piVar5[3] - (3 - g[0x33b3]);
    goto LAB_080ceb15;
  case 0x96:
    local_104 = (int *)ExplodCount((int *)g[0x52be],piVar5[1],-1);
    break;
  case 0xa0:
    piVar11 = (int *)0xffffffff;
    goto LAB_080cf217;
  case 0xb4:
    switch(param_2[7]) {
    case 0:
      local_104 = (int *)piVar5[0x403];
      break;
    case 1:
      local_104 = (int *)piVar5[0x404];
      break;
    case 2:
      local_104 = (int *)piVar5[0x406];
      break;
    case 3:
      local_104 = (int *)piVar5[0x407];
      break;
    case 4:
      local_104 = (int *)piVar5[0x408];
      break;
    case 5:
      local_104 = (int *)piVar5[0x409];
      break;
    case 6:
      local_104 = (int *)piVar5[0x40a];
      break;
    case 7:
      local_104 = (int *)piVar5[0x40b];
      break;
    case 8:
      local_104 = (int *)piVar5[0x40c];
      break;
    case 9:
      local_104 = (int *)piVar5[0x40d];
      break;
    case 10:
      local_104 = (int *)piVar5[0x40e];
      break;
    case 0xb:
      local_104 = (int *)piVar5[0x40f];
      break;
    case 0xc:
      local_104 = (int *)piVar5[0x410];
      break;
    case 0xd:
      local_104 = (int *)piVar5[0x411];
      break;
    case 0xe:
      local_100[0] = GHIDRA_I2F(piVar5[0x413]);
      goto LAB_080cf4e5;
    case 0xf:
      local_100[0] = GHIDRA_I2F(piVar5[0x414]);
      goto LAB_080cf4e5;
    case 0x10:
      local_100[0] = GHIDRA_I2F(piVar5[0x415]);
      goto LAB_080cf4e5;
    case 0x11:
      local_100[0] = GHIDRA_I2F(piVar5[0x416]);
      goto LAB_080cf4e5;
    case 0x12:
switchD_080ceefc_caseD_12:
      local_100[0] = GHIDRA_I2F(piVar5[0x417]);
      goto LAB_080cf4e5;
    case 0x13:
      local_100[0] = GHIDRA_I2F(piVar5[0x418]);
      goto LAB_080cf4e5;
    case 0x14:
      local_104 = (int *)piVar5[0x419];
      break;
    case 0x15:
      local_104 = (int *)piVar5[0x41a];
      break;
    case 0x16:
      local_104 = (int *)(uint)(piVar5[0x41b] != 0);
      break;
    case 0x17:
      goto switchD_080cdb66_caseD_64;
    case 0x18:
      local_104 = (int *)piVar5[0x41d];
      break;
    case 0x19:
      local_100[0] = GHIDRA_I2F(piVar5[0x41e]);
      goto LAB_080cf4e5;
    case 0x1a:
      local_100[0] = GHIDRA_I2F(piVar5[0x41f]);
      goto LAB_080cf4e5;
    case 0x1b:
      local_104 = (int *)piVar5[0x420];
      break;
    case 0x1c:
      local_104 = (int *)piVar5[0x421];
      break;
    case 0x1d:
      local_104 = (int *)piVar5[0x422];
      break;
    case 0x1e:
      local_104 = (int *)piVar5[0x423];
      break;
    case 0x1f:
      local_104 = (int *)piVar5[0x425];
      break;
    case 0x20:
      local_104 = (int *)piVar5[0x426];
      break;
    case 0x21:
      fVar1 = GHIDRA_I2F(piVar5[0x428]);
      goto LAB_080cdf3d;
    case 0x22:
      local_100[0] = GHIDRA_I2F(piVar5[0x427]);
      goto LAB_080cf4e5;
    case 0x23:
      local_100[0] = GHIDRA_I2F(piVar5[0x429]);
LAB_080cf4e5:
      piVar16 = (int *)*param_2;
      goto LAB_080d04fc;
    default:
      if (bVar18) {
        WarnR((int)param_1,(int)piVar5,(int)&DAT_0827cd00);
      }
      else {
        Warn((int)piVar5,(int)&DAT_0827cd00);
      }
    }
    break;
  case 0xb5:
    iVar6 = param_2[7];
    if (CnstType[iVar6] != 0) {
      local_100[0] = GHIDRA_I2F(piVar5[iVar6 + 0x14]);
      goto LAB_080cf4e5;
    }
    local_104 = (int *)piVar5[iVar6 + 0x14];
    break;
  case 0xbe:
    local_104 = (int *)TimerFPS;
    break;
  case 0xc9:
    bVar18 = piVar5[7] == 1;
LAB_080cedc9:
    local_104 = (int *)(uint)bVar18;
    break;
  case 0xca:
    piVar11 = (int *)0x0;
LAB_080cf327:
    local_104 = (int *)HelperCount((int)piVar5,(int)piVar11);
    break;
  case 0xcb:
    if (piVar8 == (int *)0x0) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",piVar5,piVar5);
        ErrorExit();
      }
      piVar5 = (int *)((int)MyStackIdx + 1);
      bVar19 = SBORROW4((int)piVar5,0x7e);
      bVar18 = (int)MyStackIdx + -0x7d < 0;
      bVar17 = piVar5 == (int *)0x7e;
      MyStackIdx = piVar5;
      MyStack[(int)piVar5] = 0;
      goto LAB_080cfec3;
    }
    iVar6 = param_2[7];
    if (iVar6 == 1) {
      piVar16 = (int *)*param_2;
      local_100[0] = GHIDRA_I2F(piVar8[0x68]) - GHIDRA_I2F(piVar5[0x68]);
    }
    else {
      local_110 = piVar8;
      if (iVar6 < 2) goto joined_r0x080cf410;
      if (iVar6 == 2) {
        piVar16 = (int *)*param_2;
        local_100[0] = GHIDRA_I2F(piVar8[0x69]) - GHIDRA_I2F(piVar5[0x69]);
      }
    }
    goto LAB_080d04fc;
  case 0xcc:
    if (piVar9 == (int *)0x0) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",piVar5,piVar5);
        ErrorExit();
      }
      piVar5 = (int *)((int)MyStackIdx + 1);
      bVar19 = SBORROW4((int)piVar5,0x7e);
      bVar18 = (int)MyStackIdx + -0x7d < 0;
      bVar17 = piVar5 == (int *)0x7e;
      MyStackIdx = piVar5;
      MyStack[(int)piVar5] = 0;
      goto LAB_080cfec3;
    }
    iVar6 = param_2[7];
    local_110 = piVar9;
    if (iVar6 == 1) {
      local_100[0] = GHIDRA_I2F(piVar5[0x68]);
      goto LAB_080cf44b;
    }
    if (iVar6 < 2) goto joined_r0x080cf410;
    if (iVar6 == 2) {
      local_100[0] = GHIDRA_I2F(piVar5[0x69]);
      goto LAB_080cf46a;
    }
    goto LAB_080d04fc;
  case 0xcd:
    local_104 = (int *)piVar5[0xd18];
    break;
  case 0x12c:
    local_100[0] = ((double)3.1415927);
    goto LAB_080cf4e5;
  case 0x12d:
    local_100[0] = ((double)2.7182817);
    goto LAB_080cf4e5;
  case 0x131:
    if (-1 < (int)MyStackIdx) {
      local_138 = MyStack[(int)MyStackIdx];
      piVar11 = (int *)((int)MyStackIdx + -1);
      MyStackIdx = piVar11;
    }
    if ((int *)0x7fffffff < piVar2) {
      piVar11 = (int *)StackUnderflow();
    }
    piVar8 = MyStackIdx;
    if (-1 < (int)MyStackIdx) {
      local_13c = MyStack[(int)MyStackIdx];
      piVar11 = (int *)((int)MyStackIdx + -1);
      MyStackIdx = piVar11;
    }
    if ((int *)0x7fffffff < piVar8) {
      piVar11 = (int *)StackUnderflow();
    }
    piVar8 = MyStackIdx;
    if (-1 < (int)MyStackIdx) {
      local_140 = MyStack[(int)MyStackIdx];
      piVar11 = (int *)((int)MyStackIdx + -1);
      MyStackIdx = piVar11;
    }
    if ((int *)0x7fffffff < piVar8) {
      piVar11 = (int *)StackUnderflow();
    }
    piVar8 = MyStackIdx;
    if (-1 < (int)MyStackIdx) {
      local_144 = MyStack[(int)MyStackIdx];
      piVar11 = (int *)((int)MyStackIdx + -1);
      MyStackIdx = piVar11;
    }
    if ((int *)0x7fffffff < piVar8) {
      piVar11 = (int *)StackUnderflow();
    }
    piVar8 = MyStackIdx;
    if (-1 < (int)MyStackIdx) {
      local_148 = MyStack[(int)MyStackIdx];
      piVar11 = (int *)((int)MyStackIdx + -1);
      MyStackIdx = piVar11;
    }
    if ((int *)0x7fffffff < piVar8) {
      piVar11 = (int *)StackUnderflow();
    }
    piVar8 = MyStackIdx;
    if (-1 < (int)MyStackIdx) {
      local_14c = (int *)MyStack[(int)MyStackIdx];
      piVar11 = (int *)((int)MyStackIdx + -1);
      MyStackIdx = piVar11;
    }
    uVar13 = (uint)(piVar8 < (int *)0x80000000);
    if (uVar13 == 0) {
      piVar11 = (int *)StackUnderflow();
      uVar13 = extraout_EDX_13;
    }
    if (local_148 != 3) {
      if (local_140 == 3) {
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.",piVar11,piVar11);
          ErrorExit();
        }
        piVar11 = (int *)((int)MyStackIdx + 1);
        MyStackIdx = piVar11;
        MyStack[(int)piVar11] = local_144;
        goto joined_r0x080cf697;
      }
      if (local_138 == 3) {
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.",param_2,param_2);
          ErrorExit();
        }
        piVar11 = (int *)((int)MyStackIdx + 1);
        bVar19 = SBORROW4((int)piVar11,0x7e);
        bVar18 = (int)MyStackIdx + -0x7d < 0;
        bVar17 = piVar11 == (int *)0x7e;
        MyStackIdx = piVar11;
        MyStack[(int)piVar11] = local_13c;
        goto LAB_080d03d0;
      }
      if (local_148 == 2) {
        if ((float10)(int)local_14c == 0.0) {
          if (0x7e < (int)MyStackIdx) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.",uVar13,uVar13);
            ErrorExit();
          }
          piVar5 = (int *)((int)MyStackIdx + 1);
          MyStackIdx = piVar5;
          MyStack[(int)piVar5] = local_13c;
          piVar11 = piVar5;
joined_r0x080cf853:
          local_140 = local_138;
          if (0x7e < (int)piVar11) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.",piVar5,piVar5);
            ErrorExit();
          }
          goto LAB_080cf877;
        }
        piVar5 = MyStackIdx;
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.",piVar10,piVar10);
          ErrorExit();
          piVar5 = MyStackIdx;
        }
        piVar11 = (int *)((int)piVar5 + 1);
        MyStackIdx = piVar11;
        MyStack[(int)piVar11] = local_144;
      }
      else {
        if (local_14c == (int *)0x0) {
          piVar5 = MyStackIdx;
          if (0x7e < (int)MyStackIdx) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.",piVar10,piVar10);
            ErrorExit();
            piVar5 = MyStackIdx;
          }
          piVar11 = (int *)((int)piVar5 + 1);
          MyStackIdx = piVar11;
          MyStack[(int)piVar11] = local_13c;
          goto joined_r0x080cf853;
        }
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.",param_2,param_2);
          ErrorExit();
        }
        piVar11 = (int *)((int)MyStackIdx + 1);
        MyStackIdx = piVar11;
        MyStack[(int)piVar11] = local_144;
      }
      if (0x7e < (int)piVar11) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",piVar5,piVar5);
        ErrorExit();
      }
LAB_080cf877:
      MyStackIdx = (int *)((int)MyStackIdx + 1);
      MyStack[(int)MyStackIdx] = local_140;
      return;
    }
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",MyStackIdx,MyStackIdx);
      ErrorExit();
    }
    piVar5 = (int *)((int)MyStackIdx + 1);
    bVar19 = SBORROW4((int)piVar5,0x7e);
    bVar18 = (int)MyStackIdx + -0x7d < 0;
    bVar17 = piVar5 == (int *)0x7e;
    MyStackIdx = piVar5;
    MyStack[(int)piVar5] = (int)local_14c;
LAB_080d0485:
    piVar5 = local_14c;
    if (bVar17 || bVar19 != bVar18) goto LAB_080d04a0;
    goto LAB_080d0489;
  case 0x136:
    unaff_EBP = piVar5;
    cVar4 = SPopF(piVar5,&local_108);
    local_104 = (int *)GHIDRA_ZEXT8(cVar4);
    cVar4 = SPopF(piVar5,&local_10c);
    if (GHIDRA_ZEXT8(cVar4) == 3) {
LAB_080cfc4e:
      local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
      local_24 = (int *)(int)GHIDRA_FIST32(local_10c);
      piVar8 = local_24;
LAB_080cfc8d:
      piVar11 = MyStackIdx;
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",piVar5,piVar5);
        ErrorExit();
        piVar11 = MyStackIdx;
      }
      MyStackIdx = (int *)((int)piVar11 + 1);
      bVar19 = SBORROW4((int)MyStackIdx,0x7e);
      bVar18 = (int)piVar11 + -0x7d < 0;
      bVar17 = MyStackIdx == (int *)0x7e;
      MyStack[(int)MyStackIdx] = (int)piVar8;
      goto LAB_080cfcc3;
    }
    if (local_104 != (int *)0x3) {
      lVar20 = (longdouble)local_10c;
      if (((lVar20 <= (longdouble)0) || (lVar20 == (longdouble)1.0)) ||
         ((longdouble)local_108 <= (longdouble)0)) {
        if (!bVar18) {
          pcVar22 = "took log with non-positive base or argument.";
          goto LAB_080cffce;
        }
        pcVar22 = "took log with non-positive base or argument.";
        goto LAB_080cffb7;
      }
      lVar21 = (longdouble)log2((longdouble)local_108);
      lVar20 = (longdouble)log2(lVar20);
      lVar20 = ((longdouble)((double)0.6931471805599453) * lVar21) / ((longdouble)((double)0.6931471805599453) * lVar20)
      ;
      goto LAB_080cfef8;
    }
    local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
    piVar11 = (int *)(int)GHIDRA_FIST32(local_108);
    local_24 = piVar11;
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",local_20,local_20);
      ErrorExit();
    }
    piVar5 = (int *)((int)MyStackIdx + 1);
    bVar19 = SBORROW4((int)piVar5,0x7e);
    bVar18 = (int)MyStackIdx + -0x7d < 0;
    bVar17 = piVar5 == (int *)0x7e;
    MyStackIdx = piVar5;
    MyStack[(int)piVar5] = (int)piVar11;
    goto LAB_080d0017;
  case 0x140:
    cVar4 = SPopF(piVar5,local_100);
    if (GHIDRA_ZEXT8(cVar4) == 3) {
      local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
      piVar10 = (int *)(int)GHIDRA_FIST32(local_100[0]);
      local_24 = piVar10;
LAB_080cfe8d:
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",piVar5,piVar5);
        ErrorExit();
      }
      piVar5 = (int *)((int)MyStackIdx + 1);
      bVar19 = SBORROW4((int)piVar5,0x7e);
      bVar18 = (int)MyStackIdx + -0x7d < 0;
      bVar17 = piVar5 == (int *)0x7e;
      MyStackIdx = piVar5;
      MyStack[(int)piVar5] = (int)piVar10;
      goto LAB_080cfec3;
    }
    lVar20 = (longdouble)fsin((longdouble)local_100[0]);
    local_100[0] = (float)lVar20;
    break;
  case 0x141:
    cVar4 = SPopF(piVar5,local_100);
    if (GHIDRA_ZEXT8(cVar4) == 3) {
      local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
      piVar11 = (int *)(int)GHIDRA_FIST32(local_100[0]);
      local_24 = piVar11;
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",local_20,local_20);
        ErrorExit();
      }
      piVar5 = (int *)((int)MyStackIdx + 1);
      bVar19 = SBORROW4((int)piVar5,0x7e);
      bVar18 = (int)MyStackIdx + -0x7d < 0;
      bVar17 = piVar5 == (int *)0x7e;
      MyStackIdx = piVar5;
      MyStack[(int)piVar5] = (int)piVar11;
      goto LAB_080d0017;
    }
    lVar20 = (longdouble)fcos((longdouble)local_100[0]);
    local_100[0] = (float)lVar20;
    break;
  case 0x142:
    cVar4 = SPopF(piVar5,local_100);
    if (GHIDRA_ZEXT8(cVar4) == 3) {
      local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
      piVar10 = (int *)(int)GHIDRA_FIST32(local_100[0]);
      local_24 = piVar10;
      goto LAB_080cfe8d;
    }
    lVar20 = (longdouble)fptan((longdouble)local_100[0]);
    local_5c = (double)lVar20;
    lVar20 = (longdouble)local_5c;
    goto LAB_080cfef8;
  case 0x143:
    cVar4 = SPopF(piVar5,local_100);
    if (GHIDRA_ZEXT8(cVar4) != 3) {
      lVar20 = (longdouble)local_100[0];
      if (((longdouble)-1.0 <= lVar20) && (lVar20 <= (longdouble)1.0)) {
        lVar20 = (longdouble)fpatan(lVar20,SQRT((longdouble)1.0 - lVar20 * lVar20));
        local_6c = (double)lVar20;
        lVar20 = (longdouble)local_6c;
        goto LAB_080cfef8;
      }
      if (bVar18) {
        pcVar22 = "asin argument out of range";
        goto LAB_080cffb7;
      }
      pcVar22 = "asin argument out of range";
LAB_080cffce:
      Warn((int)piVar5,(int)pcVar22);
      piVar16 = extraout_EDX_18;
      goto LAB_080cffd7;
    }
    local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
    piVar11 = (int *)(int)GHIDRA_FIST32(local_100[0]);
    local_24 = piVar11;
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",extraout_EDX_14,extraout_EDX_14);
      ErrorExit();
    }
    piVar5 = (int *)((int)MyStackIdx + 1);
    bVar19 = SBORROW4((int)piVar5,0x7e);
    bVar18 = (int)MyStackIdx + -0x7d < 0;
    bVar17 = piVar5 == (int *)0x7e;
    MyStackIdx = piVar5;
    MyStack[(int)piVar5] = (int)piVar11;
    goto LAB_080d0017;
  case 0x144:
    cVar4 = SPopF(piVar5,local_100);
    local_10c = local_100[0];
    if (GHIDRA_ZEXT8(cVar4) == 3) goto LAB_080cfc4e;
    lVar20 = (longdouble)local_100[0];
    if (((longdouble)-1.0 <= lVar20) && (lVar20 <= (longdouble)1.0)) {
      lVar20 = (longdouble)fpatan(SQRT((longdouble)1.0 - lVar20 * lVar20),lVar20);
      local_7c = (double)lVar20;
      lVar20 = (longdouble)local_7c;
      goto LAB_080cfef8;
    }
    if (bVar18) {
      WarnR((int)param_1,(int)piVar5,(int)&DAT_0827c951);
    }
    else {
      Warn((int)piVar5,(int)&DAT_0827c951);
    }
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",piVar5,piVar5);
      ErrorExit();
    }
    piVar5 = (int *)((int)MyStackIdx + 1);
    bVar19 = SBORROW4((int)piVar5,0x7e);
    bVar18 = (int)MyStackIdx + -0x7d < 0;
    bVar17 = piVar5 == (int *)0x7e;
    MyStackIdx = piVar5;
    MyStack[(int)piVar5] = 0;
LAB_080cfec3:
    piVar5 = piVar10;
    if (bVar17 || bVar19 != bVar18) goto LAB_080d04a0;
    goto LAB_080d0489;
  case 0x145:
    cVar4 = SPopF(piVar5,local_100);
    if (GHIDRA_ZEXT8(cVar4) == 3) {
      local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
      piVar11 = (int *)(int)GHIDRA_FIST32(local_100[0]);
      local_24 = piVar11;
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",extraout_EDX_15,extraout_EDX_15);
        ErrorExit();
      }
      piVar5 = (int *)((int)MyStackIdx + 1);
      bVar19 = SBORROW4((int)piVar5,0x7e);
      bVar18 = (int)MyStackIdx + -0x7d < 0;
      bVar17 = piVar5 == (int *)0x7e;
      MyStackIdx = piVar5;
      MyStack[(int)piVar5] = (int)piVar11;
      goto LAB_080d0017;
    }
    lVar20 = (longdouble)fpatan((longdouble)local_100[0],(longdouble)1);
    local_100[0] = (float)lVar20;
    break;
  case 0x146:
    cVar4 = SPopF(piVar5,local_100);
    if (GHIDRA_ZEXT8(cVar4) == 3) {
      local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
      piVar10 = (int *)(int)GHIDRA_FIST32(local_100[0]);
      local_24 = piVar10;
      goto LAB_080cfe8d;
    }
    lVar20 = GHIDRA_TRUNC((longdouble)((double)1.4426950408889634) * (longdouble)local_100[0]);
    lVar21 = (longdouble)f2xm1((longdouble)((double)1.4426950408889634) * (longdouble)local_100[0] - lVar20);
    lVar20 = (longdouble)fscale((longdouble)1 + lVar21,lVar20);
    local_8c = (double)lVar20;
    lVar20 = (longdouble)local_8c;
LAB_080cfef8:
    piVar16 = (int *)*param_2;
    local_100[0] = (float)lVar20;
    goto LAB_080d04fc;
  case 0x147:
    cVar4 = SPopF(piVar5,local_100);
    if (GHIDRA_ZEXT8(cVar4) == 3) {
      local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
      piVar11 = (int *)(int)GHIDRA_FIST32(local_100[0]);
      local_24 = piVar11;
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",extraout_EDX_16,extraout_EDX_16);
        ErrorExit();
      }
      piVar5 = (int *)((int)MyStackIdx + 1);
      bVar19 = SBORROW4((int)piVar5,0x7e);
      bVar18 = (int)MyStackIdx + -0x7d < 0;
      bVar17 = piVar5 == (int *)0x7e;
      MyStackIdx = piVar5;
      MyStack[(int)piVar5] = (int)piVar11;
      goto LAB_080d0017;
    }
    if ((longdouble)local_100[0] <= (longdouble)0.0) {
      if (!bVar18) {
        pcVar22 = "took ln of a non-positive number";
        goto LAB_080cffce;
      }
      pcVar22 = "took ln of a non-positive number";
LAB_080cffb7:
      WarnR((int)param_1,(int)piVar5,(int)pcVar22);
      piVar16 = extraout_EDX_17;
      goto LAB_080cffd7;
    }
    lVar20 = (longdouble)log2((longdouble)local_100[0]);
    local_100[0] = (float)((longdouble)((double)0.6931471805599453) * lVar20);
    break;
  case 0x148:
    if (-1 < (int)MyStackIdx) {
      local_104 = (int *)MyStack[(int)MyStackIdx];
      MyStackIdx = (int *)((int)MyStackIdx + -1);
    }
    if ((int *)0x7fffffff < piVar2) {
      StackUnderflow();
    }
    piVar11 = MyStackIdx;
    if (-1 < (int)MyStackIdx) {
      local_150 = (int *)MyStack[(int)MyStackIdx];
      MyStackIdx = (int *)((int)MyStackIdx + -1);
    }
    piVar11 = (int *)(uint)(piVar11 < (int *)0x80000000);
    if (piVar11 == (int *)0x0) {
      StackUnderflow();
      piVar11 = extraout_EDX_19;
    }
    if (local_104 == (int *)0x4) {
LAB_080d01d5:
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",unaff_EBP,unaff_EBP);
        ErrorExit();
      }
      piVar11 = (int *)((int)MyStackIdx + 1);
      MyStackIdx = piVar11;
      MyStack[(int)piVar11] = (int)local_150;
      unaff_EBP = param_2;
      goto joined_r0x080cf697;
    }
    if (local_104 == (int *)0x0) {
      if ((int)local_150 < 0) {
        local_150 = (int *)-(int)local_150;
      }
      goto LAB_080d00b0;
    }
    iVar15 = (int)local_104 + -1;
    if (iVar15 != 0) {
      sprintf((char *)ErrorMessage,"Panic: aborting",iVar15,iVar15);
      ErrorExit();
      return;
    }
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",MyStackIdx,MyStackIdx);
      ErrorExit();
      piVar11 = extraout_EDX_20;
    }
    piVar5 = (int *)((int)MyStackIdx + 1);
    MyStackIdx = piVar5;
    MyStack[(int)piVar5] = (uint)local_150 & 0x7fffffff;
    param_2 = piVar11;
    goto joined_r0x080d013d;
  case 0x149:
  case 0x14a:
    if (-1 < (int)MyStackIdx) {
      local_104 = (int *)MyStack[(int)MyStackIdx];
      MyStackIdx = (int *)((int)MyStackIdx + -1);
    }
    if ((int *)0x7fffffff < piVar2) {
      StackUnderflow();
    }
    piVar11 = MyStackIdx;
    if (-1 < (int)MyStackIdx) {
      local_150 = (int *)MyStack[(int)MyStackIdx];
      MyStackIdx = (int *)((int)MyStackIdx + -1);
    }
    if ((int *)0x7fffffff < piVar11) {
      StackUnderflow();
    }
    if (local_104 == (int *)0x4) goto LAB_080d01d5;
    if (local_104 == (int *)0x0) {
      local_104 = local_150;
      break;
    }
    if (local_104 != (int *)0x1) {
      pcVar22 = "Panic: aborting";
      __s = ErrorMessage;
      piVar11 = piVar5;
      goto LAB_080d04e9;
    }
    if (*param_2 == 0x149) {
      local_c0 = in_FPUControlWord & 0xf3ff | 0x400;
      local_cc = (double)GHIDRA_FLOOR(GHIDRA_I2F(local_150));
      local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
      local_24 = (int *)(int)GHIDRA_FIST32(local_cc);
    }
    else {
      local_e0 = in_FPUControlWord & 0xf3ff | 0x800;
      local_ec = (double)GHIDRA_CEIL(GHIDRA_I2F(local_150));
      local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
      local_24 = (int *)(int)GHIDRA_FIST32(local_ec);
    }
LAB_080cdf6f:
    local_104 = local_24;
    break;
  case 0x14b:
    cVar4 = SPopI((int)piVar5,(int *)&local_104);
    local_14c = extraout_EDX_21;
    if (GHIDRA_ZEXT8(cVar4) == 3) {
LAB_080d0445:
      piVar5 = local_104;
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",MyStackIdx,MyStackIdx);
        ErrorExit();
        local_14c = extraout_EDX_25;
      }
      piVar11 = (int *)((int)MyStackIdx + 1);
      bVar19 = SBORROW4((int)piVar11,0x7e);
      bVar18 = (int)MyStackIdx + -0x7d < 0;
      bVar17 = piVar11 == (int *)0x7e;
      MyStackIdx = piVar11;
      MyStack[(int)piVar11] = (int)piVar5;
      goto LAB_080d0485;
    }
    iVar6 = (int)local_104 + -1;
LAB_080d0371:
    unaff_EBP = (int *)piVar5[0x4ef];
    local_104 = (int *)AnimCurElemStartTime(unaff_EBP,iVar6);
    if (local_104 == (int *)0xffffffff) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",param_2,param_2);
        ErrorExit();
      }
      MyStackIdx = (int *)((int)MyStackIdx + 1);
LAB_080d03bd:
      bVar19 = SBORROW4((int)MyStackIdx,0x7e);
      bVar18 = (int)MyStackIdx + -0x7e < 0;
      bVar17 = MyStackIdx == (int *)0x7e;
      MyStack[(int)MyStackIdx] = 0;
      goto LAB_080d03d0;
    }
    local_104 = (int *)(*(int *)(piVar5[0x4ef] + 0x1c) - (int)local_104);
    break;
  case 0x14c:
    cVar4 = SPopI((int)piVar5,(int *)&local_104);
    unaff_EBP = local_104;
    local_14c = extraout_EDX_22;
    if (GHIDRA_ZEXT8(cVar4) == 3) goto LAB_080d0445;
    bVar18 = PlayerAnimExist((int)piVar5,(int)local_104);
    local_104 = (int *)GHIDRA_ZEXT8(bVar18);
    break;
  case 0x14d:
    cVar4 = SPopI((int)piVar5,(int *)&local_104);
    unaff_EBP = local_104;
    local_14c = extraout_EDX_23;
    if (GHIDRA_ZEXT8(cVar4) == 3) goto LAB_080d0445;
    bVar18 = PlayerSelfAnimExist(piVar5,(int)local_104);
    local_104 = (int *)GHIDRA_ZEXT8(bVar18);
    break;
  case 0x14e:
    cVar4 = SPopI((int)piVar5,(int *)&local_104);
    local_14c = extraout_EDX_24;
    if (GHIDRA_ZEXT8(cVar4) == 3) goto LAB_080d0445;
    iVar6 = PlayerAccessID((int)local_104);
LAB_080cddcb:
    local_104 = (int *)(uint)(iVar6 != 0);
    break;
  case 0x14f:
    cVar4 = SPopI((int)piVar5,(int *)&local_104);
    piVar11 = local_104;
    if (piVar5[7] == 1) {
      if (GHIDRA_ZEXT8(cVar4) == 3) {
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.",param_2,param_2);
          ErrorExit();
        }
        piVar10 = (int *)((int)MyStackIdx + 1);
        bVar19 = SBORROW4((int)piVar10,0x7e);
        bVar18 = (int)MyStackIdx + -0x7d < 0;
        bVar17 = piVar10 == (int *)0x7e;
        MyStackIdx = piVar10;
        MyStack[(int)piVar10] = (int)piVar11;
        goto LAB_080d03d0;
      }
      piVar5 = (int *)piVar5[0x986];
      goto LAB_080cedc3;
    }
LAB_080cdd3a:
    local_104 = (int *)0x0;
    break;
  case 0x150:
    cVar4 = SPopI((int)piVar5,(int *)&local_104);
    piVar11 = local_104;
    if (GHIDRA_ZEXT8(cVar4) != 3) goto LAB_080cf327;
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",extraout_EDX_12,extraout_EDX_12);
      ErrorExit();
    }
    piVar5 = (int *)((int)MyStackIdx + 1);
    bVar19 = SBORROW4((int)piVar5,0x7e);
    bVar18 = (int)MyStackIdx + -0x7d < 0;
    bVar17 = piVar5 == (int *)0x7e;
    MyStackIdx = piVar5;
    MyStack[(int)piVar5] = (int)piVar11;
LAB_080d0017:
    if (bVar17 || bVar19 != bVar18) goto LAB_080d04a0;
    goto LAB_080d0489;
  case 0x151:
    cVar4 = SPopI((int)piVar5,(int *)&local_104);
    unaff_EBP = local_104;
    if (GHIDRA_ZEXT8(cVar4) == 3) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",extraout_EDX_08,extraout_EDX_08);
        ErrorExit();
      }
      piVar5 = (int *)((int)MyStackIdx + 1);
      bVar19 = SBORROW4((int)piVar5,0x7e);
      bVar18 = (int)MyStackIdx + -0x7d < 0;
      bVar17 = piVar5 == (int *)0x7e;
      MyStackIdx = piVar5;
      MyStack[(int)piVar5] = (int)unaff_EBP;
      goto LAB_080d0017;
    }
    if ((int)local_104 < 0) {
      local_104 = (int *)0x0;
      if (bVar18) {
        WarnR((int)param_1,(int)piVar5,(int)&DAT_0827cca0);
      }
      else {
        Warn((int)piVar5,(int)&DAT_0827cca0);
      }
    }
    bVar18 = piVar5[0x85] == 2;
LAB_080ce837:
    if (bVar18) {
LAB_080ce839:
      if (((int *)piVar5[0x84] == local_104) || (local_104 == (int *)0x0)) {
        local_104 = (int *)piVar5[0x86];
        break;
      }
    }
LAB_080ce858:
    local_104 = (int *)0xffffffff;
    break;
  case 0x152:
    cVar4 = SPopI((int)piVar5,(int *)&local_104);
    piVar11 = local_104;
    if (GHIDRA_ZEXT8(cVar4) != 3) {
      if ((int)local_104 < 0) {
        local_104 = (int *)0x0;
        if (bVar18) {
          WarnR((int)param_1,(int)piVar5,(int)&DAT_0827cca0);
        }
        else {
          Warn((int)piVar5,(int)&DAT_0827cca0);
        }
      }
      bVar18 = piVar5[0x85] == 1;
      goto LAB_080ce837;
    }
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",param_2,param_2);
      ErrorExit();
    }
    piVar10 = (int *)((int)MyStackIdx + 1);
    bVar19 = SBORROW4((int)piVar10,0x7e);
    bVar18 = (int)MyStackIdx + -0x7d < 0;
    bVar17 = piVar10 == (int *)0x7e;
    MyStackIdx = piVar10;
    MyStack[(int)piVar10] = (int)piVar11;
    goto LAB_080d03d0;
  case 0x153:
    cVar4 = SPopI((int)piVar5,(int *)&local_104);
    piVar11 = local_104;
    if (GHIDRA_ZEXT8(cVar4) != 3) {
      if ((int)local_104 < 0) {
        local_104 = (int *)0x0;
        if (bVar18) {
          WarnR((int)param_1,(int)piVar5,(int)&DAT_0827cca0);
        }
        else {
          Warn((int)piVar5,(int)&DAT_0827cca0);
        }
      }
      if ((piVar5[0x85] != 0) && (piVar5[0x85] != 3)) goto LAB_080ce839;
      goto LAB_080ce858;
    }
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",param_2,param_2);
      ErrorExit();
    }
    piVar10 = (int *)((int)MyStackIdx + 1);
    bVar19 = SBORROW4((int)piVar10,0x7e);
    bVar18 = (int)MyStackIdx + -0x7d < 0;
    bVar17 = piVar10 == (int *)0x7e;
    MyStackIdx = piVar10;
    MyStack[(int)piVar10] = (int)piVar11;
    goto LAB_080d03d0;
  case 0x154:
    cVar4 = SPopI((int)piVar5,(int *)&local_104);
    piVar10 = local_104;
    if (GHIDRA_ZEXT8(cVar4) == 3) goto LAB_080cfe8d;
    if ((int)local_104 < 0) {
      local_104 = (int *)0x0;
      if (bVar18) {
        WarnR((int)param_1,(int)piVar5,(int)&DAT_0827c91b);
        unaff_EBP = param_1;
      }
      else {
        Warn((int)piVar5,(int)&DAT_0827c91b);
      }
    }
    local_104 = (int *)ProjArrayCountActiveID((int *)piVar5[0x87],(int)local_104);
    break;
  case 0x155:
    cVar4 = SPopI((int)piVar5,(int *)&local_104);
    piVar11 = local_104;
    if (GHIDRA_ZEXT8(cVar4) == 3) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",extraout_EDX_11,extraout_EDX_11);
        ErrorExit();
      }
      piVar5 = (int *)((int)MyStackIdx + 1);
      bVar19 = SBORROW4((int)piVar5,0x7e);
      bVar18 = (int)MyStackIdx + -0x7d < 0;
      bVar17 = piVar5 == (int *)0x7e;
      MyStackIdx = piVar5;
      MyStack[(int)piVar5] = (int)piVar11;
      goto LAB_080d0017;
    }
    if ((int)local_104 < -1) {
      local_104 = (int *)0xffffffff;
      if (bVar18) {
        WarnR((int)param_1,(int)piVar5,(int)&DAT_0827cce0);
      }
      else {
        Warn((int)piVar5,(int)&DAT_0827cce0);
      }
    }
    unaff_EBP = local_104;
    local_104 = (int *)ExplodCount((int *)g[0x52be],piVar5[1],(int)local_104);
    break;
  case 0x156:
    cVar4 = SPopI((int)piVar5,(int *)&local_104);
    piVar8 = local_104;
    if (GHIDRA_ZEXT8(cVar4) == 3) goto LAB_080cfc8d;
    piVar11 = local_104;
    if ((int)local_104 < -1) {
      local_104 = (int *)0xffffffff;
      if (bVar18) {
        WarnR((int)param_1,(int)piVar5,(int)&DAT_0827cd40);
        unaff_EBP = param_1;
        piVar11 = local_104;
      }
      else {
        Warn((int)piVar5,(int)&DAT_0827cd40);
        piVar11 = local_104;
      }
    }
LAB_080cf217:
    local_104 = (int *)TargetCount(piVar5[0x88],(int)piVar11);
    break;
  case 0x157:
    cVar4 = SPopI((int)piVar5,(int *)&local_104);
    piVar8 = local_104;
    if (GHIDRA_ZEXT8(cVar4) == 3) goto LAB_080cfc8d;
    if ((int *)0x3b < local_104) {
      if (bVar18) {
        WarnR((int)param_1,(int)piVar5,(int)&DAT_0827c904);
      }
      else {
        Warn((int)piVar5,(int)&DAT_0827c904);
      }
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",piVar5,piVar5);
        ErrorExit();
      }
      piVar5 = (int *)((int)MyStackIdx + 1);
      bVar19 = SBORROW4((int)piVar5,0x7e);
      bVar18 = (int)MyStackIdx + -0x7d < 0;
      bVar17 = piVar5 == (int *)0x7e;
      MyStackIdx = piVar5;
      MyStack[(int)piVar5] = 0;
      goto LAB_080cfec3;
    }
    local_104 = (int *)piVar5[(int)(local_104 + 0xe4)];
    break;
  case 0x158:
    cVar4 = SPopI((int)piVar5,(int *)&local_104);
    piVar11 = local_104;
    if (GHIDRA_ZEXT8(cVar4) == 3) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",extraout_EDX_03,extraout_EDX_03);
        ErrorExit();
      }
      piVar5 = (int *)((int)MyStackIdx + 1);
      bVar19 = SBORROW4((int)piVar5,0x7e);
      bVar18 = (int)MyStackIdx + -0x7d < 0;
      bVar17 = piVar5 == (int *)0x7e;
      MyStackIdx = piVar5;
      MyStack[(int)piVar5] = (int)piVar11;
      goto LAB_080d0017;
    }
    if ((int *)0x27 < local_104) {
      if (!bVar18) {
        pcVar22 = "fvar index out of range";
        goto LAB_080cffce;
      }
      pcVar22 = "fvar index out of range";
      goto LAB_080cffb7;
    }
    local_100[0] = GHIDRA_I2F(piVar5[(int)(local_104 + 0xf3)]);
    goto LAB_080cf4e5;
  case 0x159:
    cVar4 = SPopI((int)piVar5,(int *)&local_104);
    piVar8 = local_104;
    if (GHIDRA_ZEXT8(cVar4) == 3) goto LAB_080cfc8d;
    if ((int *)0x4 < local_104) {
      if (bVar18) {
        WarnR((int)param_1,(int)piVar5,(int)&DAT_0827c8e6);
      }
      else {
        Warn((int)piVar5,(int)&DAT_0827c8e6);
      }
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",piVar5,piVar5);
        ErrorExit();
      }
      piVar5 = (int *)((int)MyStackIdx + 1);
      bVar19 = SBORROW4((int)piVar5,0x7e);
      bVar18 = (int)MyStackIdx + -0x7d < 0;
      bVar17 = piVar5 == (int *)0x7e;
      MyStackIdx = piVar5;
      MyStack[(int)piVar5] = 0;
      goto LAB_080cfec3;
    }
    local_104 = (int *)piVar5[(int)(local_104 + 0xfd)];
    break;
  case 0x15a:
    cVar4 = SPopI((int)piVar5,(int *)&local_104);
    piVar11 = local_104;
    if (GHIDRA_ZEXT8(cVar4) == 3) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",extraout_EDX_04,extraout_EDX_04);
        ErrorExit();
      }
      piVar5 = (int *)((int)MyStackIdx + 1);
      bVar19 = SBORROW4((int)piVar5,0x7e);
      bVar18 = (int)MyStackIdx + -0x7d < 0;
      bVar17 = piVar5 == (int *)0x7e;
      MyStackIdx = piVar5;
      MyStack[(int)piVar5] = (int)piVar11;
      goto LAB_080d0017;
    }
    if ((int *)0x4 < local_104) {
      if (bVar18) {
        WarnR((int)param_1,(int)piVar5,(int)&DAT_0827c900);
        local_14c = extraout_EDX_05;
      }
      else {
        Warn((int)piVar5,(int)&DAT_0827c900);
        local_14c = extraout_EDX_06;
      }
      goto LAB_080ce647;
    }
    local_100[0] = GHIDRA_I2F(piVar5[(int)local_104 + 0x3f9]);
    goto LAB_080cf4e5;
  case 0x15b:
    cVar4 = SPopI((int)piVar5,(int *)&local_104);
    piVar11 = local_104;
    if (GHIDRA_ZEXT8(cVar4) != 3) {
      if ((int)local_104 < 0) {
        local_104 = (int *)0x0;
        if (bVar18) {
          WarnR((int)param_1,(int)piVar5,(int)&DAT_0827cca0);
        }
        else {
          Warn((int)piVar5,(int)&DAT_0827cca0);
        }
      }
      bVar18 = piVar5[0x85] == 3;
      goto LAB_080ce837;
    }
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",param_2,param_2);
      ErrorExit();
    }
    piVar10 = (int *)((int)MyStackIdx + 1);
    bVar19 = SBORROW4((int)piVar10,0x7e);
    bVar18 = (int)MyStackIdx + -0x7d < 0;
    bVar17 = piVar10 == (int *)0x7e;
    MyStackIdx = piVar10;
    MyStack[(int)piVar10] = (int)piVar11;
LAB_080d03d0:
    if (!bVar17 && bVar19 == bVar18) {
LAB_080d0489:
      sprintf((char *)ErrorMessage,"Expression stack overflow.",piVar5,piVar5);
      ErrorExit();
    }
LAB_080d04a0:
    MyStackIdx = (int *)((int)MyStackIdx + 1);
    MyStack[(int)MyStackIdx] = 4;
    return;
  case 0x15c:
    cVar4 = SPopI((int)piVar5,(int *)&local_104);
    piVar11 = local_104;
    if (GHIDRA_ZEXT8(cVar4) == 3) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",extraout_EDX_09,extraout_EDX_09);
        ErrorExit();
      }
      piVar5 = (int *)((int)MyStackIdx + 1);
      bVar19 = SBORROW4((int)piVar5,0x7e);
      bVar18 = (int)MyStackIdx + -0x7d < 0;
      bVar17 = piVar5 == (int *)0x7e;
      MyStackIdx = piVar5;
      MyStack[(int)piVar5] = (int)piVar11;
      goto LAB_080d0017;
    }
    local_104 = (int *)AnimElemNo((undefined4 *)piVar5[0x4ef],(int)local_104);
    if (local_104 == (int *)0xffffffff) {
      local_104 = (int *)0xffffffff;
      piVar16 = extraout_EDX_10;
      goto LAB_080cffd7;
    }
  }
  piVar16 = (int *)*param_2;
LAB_080d04fc:
  fVar1 = local_100[0];
  if (((((((piVar16 == (int *)0x14) || (piVar16 == (int *)0x2)) || ((int)piVar16 - 0x5aU < 4)) ||
        ((piVar16 == (int *)0x2b || (piVar16 == (int *)0x2c)))) ||
       ((piVar16 == (int *)0x2d || ((piVar16 == (int *)0x2e || (piVar16 == (int *)0x7)))))) ||
      (piVar16 == (int *)0x3e)) || ((piVar16 == (int *)0x40 || (piVar16 == (int *)0x3f)))) {
    piVar5 = local_104;
    switch((int)iVar15) {
    case 0:
      piVar16 = (int *)param_2[7];
      piVar5 = (int *)(uint)(local_104 == piVar16);
      break;
    case 1:
      piVar16 = (int *)param_2[7];
      piVar5 = (int *)(uint)(local_104 != piVar16);
      break;
    case 2:
      piVar16 = (int *)param_2[7];
      piVar5 = (int *)(uint)((int)piVar16 < (int)local_104);
      break;
    case 3:
      piVar16 = (int *)param_2[7];
      piVar5 = (int *)(uint)((int)piVar16 <= (int)local_104);
      break;
    case 4:
      piVar16 = (int *)param_2[7];
      piVar5 = (int *)(uint)((int)local_104 < (int)piVar16);
      break;
    case 5:
      piVar16 = (int *)param_2[7];
      piVar5 = (int *)(uint)((int)local_104 <= (int)piVar16);
      break;
    case 10:
      piVar16 = (int *)0x0;
      piVar5 = piVar16;
      if (param_2[7] <= (int)local_104) {
LAB_080d05fb:
        piVar16 = (int *)0x0;
        piVar5 = piVar16;
        if ((int)local_104 <= param_2[8]) {
LAB_080d0612:
          piVar16 = (int *)0x1;
          piVar5 = piVar16;
        }
      }
      break;
    case 0xb:
      piVar16 = (int *)0x0;
      piVar5 = piVar16;
      if (param_2[7] <= (int)local_104) {
LAB_080d060d:
        piVar16 = (int *)0x0;
        piVar5 = piVar16;
        if ((int)local_104 < param_2[8]) goto LAB_080d0612;
      }
      break;
    case 0xc:
      piVar16 = (int *)0x0;
      piVar5 = piVar16;
      if (param_2[7] < (int)local_104) goto LAB_080d05fb;
      break;
    case 0xd:
      piVar16 = (int *)0x0;
      piVar5 = piVar16;
      if (param_2[7] < (int)local_104) goto LAB_080d060d;
    }
    local_104 = piVar5;
    if (bVar17) {
      local_104 = (int *)(1 - (int)local_104);
    }
  }
  piVar5 = local_104;
  if (param_2[6] == 0) {
LAB_080d0643:
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",piVar16,piVar16);
      ErrorExit();
    }
    local_150 = (int *)((int)MyStackIdx + 1);
    MyStackIdx = local_150;
    MyStack[(int)local_150] = (int)piVar5;
    piVar5 = local_150;
joined_r0x080d00e6:
    if (0x7e < (int)piVar5) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",local_150,local_150);
      ErrorExit();
    }
    MyStackIdx = (int *)((int)MyStackIdx + 1);
    MyStack[(int)MyStackIdx] = 0;
  }
  else if (param_2[6] == 1) {
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",unaff_EBP,unaff_EBP);
      ErrorExit();
    }
    piVar5 = (int *)((int)MyStackIdx + 1);
    MyStackIdx = piVar5;
    MyStack[(int)piVar5] = GHIDRA_F2I(int, fVar1);
joined_r0x080d013d:
    if (0x7e < (int)piVar5) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",param_2,param_2);
      ErrorExit();
    }
    MyStackIdx = (int *)((int)MyStackIdx + 1);
    MyStack[(int)MyStackIdx] = 1;
  }
  else {
    ErrorExit();
  }
  return;
}
#undef local_150
#undef local_14c
#undef local_148
#undef local_144
#undef local_140
#undef local_13c
#undef local_138
#undef local_134
#undef local_11c
#undef local_118
#undef local_114
#undef local_110
#undef local_10c
#undef local_108
#undef local_104
#undef local_100
#undef local_ec
#undef local_e0
#undef local_cc
#undef local_c0
#undef local_8c
#undef local_7c
#undef local_6c
#undef local_5c
#undef local_24
#undef local_20

/* TriggerFree @ 0x080d0740, 51 bytes */
void TriggerFree(void *param_1)

{
  if (*(void **)((int)param_1 + 0x34) != (void *)0x0) {
    free(*(void **)((int)param_1 + 0x34));
  }
  FreeExpression((int *)((int)param_1 + 8));
  free(param_1);
  return;
}

/* trigcpy @ 0x080d0780, 161 bytes */
undefined4 trigcpy(int *param_1,int *param_2)

{
  size_t sVar1;
  undefined4 uVar2;
  int iVar3;
  int *extraout_ECX;
  int *piVar4;
  int *piVar5;
  char *__format;
  
  piVar4 = param_2;
  piVar5 = param_1;
  for (iVar3 = 0xe; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar5 = *piVar4;
    piVar4 = piVar4 + 1;
    piVar5 = piVar5 + 1;
  }
  expcpytrig(param_1 + 2,param_2 + 2);
  if ((char *)param_2[0xd] == (char *)0x0) {
LAB_080d0814:
    uVar2 = 1;
  }
  else {
    if (*param_2 - 0x5aU < 4) {
      sVar1 = strlen((char *)param_2[0xd]);
      iVar3 = ecalloc(1,sVar1 + 1);
      param_1[0xd] = iVar3;
      if (iVar3 != 0) {
        strcpy((char *)param_1[0xd],(char *)param_2[0xd]);
        goto LAB_080d0814;
      }
      __format = "Alloc error";
    }
    else {
      __format = "Random data";
      param_1 = extraout_ECX;
    }
    sprintf((char *)ErrorMessage,__format,param_1,param_1);
    ErrorExit();
    uVar2 = 0;
  }
  return uVar2;
}

