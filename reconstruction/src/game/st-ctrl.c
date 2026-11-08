/*
 * st-ctrl.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x080ba390-0x080c3806, 5 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* SCtrlParseElemType @ 0x080ba390, 19059 bytes
 * REVIEW: type-prop
 * FIXUP: call to 0x08102020 (Ghidra label gcc2_compiled.) renamed to its symbol _alemu_strlwr
 * FIXUP: 33 data addresses written as literals replaced by data-image references
 * FIXUP: 9 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: 2 dead flag initialisations of inlined repz cmpsb loops set to constants
 * FIXUP: shared sprintf() call: 19 formats, arguments recovered for 12, others passed as 0
 * FIXUP: frame emulation: 4 stack locals placed at their original offsets in a 0x130-byte frame (a local's address escapes, see apply_frame_emulation) */
/* WARNING: Type propagation algorithm not settling */

undefined4 SCtrlParseElemType(int param_1,int param_2,int param_3)

{
  void *ghidra_fa[1] = {0};
  byte bVar1;
  char cVar2;
  char cVar3;
  char *pcVar4;
  byte *pbVar5;
  undefined3 extraout_var;
  uint uVar6;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  byte *pbVar7;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  undefined3 extraout_var_07;
  int iVar8;
  int iVar9;
  int iVar10;
  size_t sVar11;
  int *piVar12;
  char *pcVar13;
  bool bVar14;
  bool bVar15;
  bool bVar16;
  undefined1 uVar17;
  unsigned char ghidra_frame[0x130] __attribute__((aligned(16)));
#define local_128 (*(int *)(ghidra_frame + 0x8))
#define local_124 (*(int *)(ghidra_frame + 0xc))
#define local_120 (*(byte **)(ghidra_frame + 0x10))
#define local_11c (*(byte (*)[268])(ghidra_frame + 0x14))
  
  pcVar4 = TPGetValue(param_1,"type");
  if (pcVar4 == (char *)0x0) {
    return 0;
  }
  pcVar13 = ";changestate";
  strcpy((char *)local_11c,pcVar4);
  _alemu_strlwr((char *)local_11c);
  iVar8 = 0xc;
  bVar14 = 0;  /* dead flag (repz cmpsb, count 0xc) */
  bVar16 = 0;  /* dead flag (repz cmpsb, count 0xc) */
  pbVar5 = local_11c;
  do {
    pcVar13 = pcVar13 + 1;
    if (iVar8 == 0) break;
    iVar8 = iVar8 + -1;
    bVar14 = *pbVar5 < (byte)*pcVar13;
    bVar16 = *pbVar5 == *pcVar13;
    pbVar5 = pbVar5 + 1;
  } while (bVar16);
  bVar15 = (!bVar14 && !bVar16) < bVar14;
  bVar14 = (!bVar14 && !bVar16) == bVar14;
  if (bVar14) {
    *(undefined4 *)(param_2 + 0x10) = 1;
    pbVar5 = (byte *)TPGetValue(param_1,"value");
    if (pbVar5 == (byte *)0x0) {
      return 0;
    }
    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x18),param_3,(undefined4 *)0x0,1);
    if (iVar8 == 0) {
      return 0;
    }
    ConstExpI((int *)(param_2 + 0x24),-1);
    piVar12 = (int *)(param_2 + 0x30);
    ConstExpI(piVar12,-1);
    pbVar5 = (byte *)TPGetValue(param_1,"ctrl");
    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x24),param_3,(undefined4 *)0x0,1);
    if (iVar8 == 0) {
      return 0;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"anim");
    iVar8 = 1;
  }
  else {
    iVar8 = 6;
    pbVar5 = local_11c;
    pbVar7 = (byte *)"tagin";
    do {
      if (iVar8 == 0) break;
      iVar8 = iVar8 + -1;
      bVar15 = *pbVar5 < *pbVar7;
      bVar14 = *pbVar5 == *pbVar7;
      pbVar5 = pbVar5 + 1;
      pbVar7 = pbVar7 + 1;
    } while (bVar14);
    bVar16 = (!bVar15 && !bVar14) < bVar15;
    if ((!bVar15 && !bVar14) == bVar15) {
      *(undefined4 *)(param_2 + 0x10) = 0x2743;
      pbVar5 = (byte *)TPGetValue(param_1,"stateno");
      if (pbVar5 == (byte *)0x0) {
        return 0;
      }
      iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x18),param_3,(undefined4 *)0x0,1);
      if (iVar8 == 0) {
        return 0;
      }
      ConstExpI((int *)(param_2 + 0x24),-1);
      piVar12 = (int *)(param_2 + 0x30);
      ConstExpI(piVar12,-1);
      pbVar5 = (byte *)TPGetValue(param_1,"partnerstateno");
      iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x24),param_3,(undefined4 *)0x0,1);
      if (iVar8 == 0) {
        return 0;
      }
      pbVar5 = (byte *)TPGetValue(param_1,"ctrl");
      iVar8 = 1;
    }
    else {
      iVar8 = 7;
      bVar14 = false;
      pbVar5 = local_11c;
      pbVar7 = (byte *)"tagout";
      do {
        if (iVar8 == 0) break;
        iVar8 = iVar8 + -1;
        bVar16 = *pbVar5 < *pbVar7;
        bVar14 = *pbVar5 == *pbVar7;
        pbVar5 = pbVar5 + 1;
        pbVar7 = pbVar7 + 1;
      } while (bVar14);
      bVar15 = (!bVar16 && !bVar14) < bVar16;
      if ((!bVar16 && !bVar14) == bVar16) {
        *(undefined4 *)(param_2 + 0x10) = 0x2744;
        return 1;
      }
      iVar8 = 10;
      bVar14 = false;
      pbVar5 = local_11c;
      pbVar7 = (byte *)"selfstate";
      do {
        if (iVar8 == 0) break;
        iVar8 = iVar8 + -1;
        bVar15 = *pbVar5 < *pbVar7;
        bVar14 = *pbVar5 == *pbVar7;
        pbVar5 = pbVar5 + 1;
        pbVar7 = pbVar7 + 1;
      } while (bVar14);
      bVar16 = (!bVar15 && !bVar14) < bVar15;
      if ((!bVar15 && !bVar14) == bVar15) {
        *(undefined4 *)(param_2 + 0x10) = 2;
        pbVar5 = (byte *)TPGetValue(param_1,"value");
        if (pbVar5 == (byte *)0x0) {
          return 0;
        }
        iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x18),param_3,(undefined4 *)0x0,1);
        if (iVar8 == 0) {
          return 0;
        }
        ConstExpI((int *)(param_2 + 0x24),-1);
        piVar12 = (int *)(param_2 + 0x30);
        ConstExpI(piVar12,-1);
        pbVar5 = (byte *)TPGetValue(param_1,"ctrl");
        iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x24),param_3,(undefined4 *)0x0,1);
        if (iVar8 == 0) {
          return 0;
        }
        pbVar5 = (byte *)TPGetValue(param_1,"anim");
        iVar8 = 1;
      }
      else {
        iVar8 = 8;
        bVar14 = false;
        pbVar5 = local_11c;
        pbVar7 = (byte *)"ctrlset";
        do {
          if (iVar8 == 0) break;
          iVar8 = iVar8 + -1;
          bVar16 = *pbVar5 < *pbVar7;
          bVar14 = *pbVar5 == *pbVar7;
          pbVar5 = pbVar5 + 1;
          pbVar7 = pbVar7 + 1;
        } while (bVar14);
        bVar15 = (!bVar16 && !bVar14) < bVar16;
        if ((!bVar16 && !bVar14) == bVar16) {
          *(undefined4 *)(param_2 + 0x10) = 0x14;
          pbVar5 = (byte *)TPGetValue(param_1,"value");
          if (pbVar5 == (byte *)0x0) {
            return 0;
          }
          iVar8 = 1;
          piVar12 = (int *)(param_2 + 0x18);
        }
        else {
          iVar8 = 5;
          bVar14 = false;
          pbVar5 = local_11c;
          pbVar7 = (byte *)(int)&DAT_0827ce65;
          do {
            if (iVar8 == 0) break;
            iVar8 = iVar8 + -1;
            bVar15 = *pbVar5 < *pbVar7;
            bVar14 = *pbVar5 == *pbVar7;
            pbVar5 = pbVar5 + 1;
            pbVar7 = pbVar7 + 1;
          } while (bVar14);
          bVar16 = (!bVar15 && !bVar14) < bVar15;
          if ((!bVar15 && !bVar14) == bVar15) {
            *(undefined4 *)(param_2 + 0x10) = 3;
            return 1;
          }
          iVar8 = 0xb;
          bVar14 = false;
          pbVar5 = local_11c;
          pbVar7 = (byte *)"changeanim";
          do {
            if (iVar8 == 0) break;
            iVar8 = iVar8 + -1;
            bVar16 = *pbVar5 < *pbVar7;
            bVar14 = *pbVar5 == *pbVar7;
            pbVar5 = pbVar5 + 1;
            pbVar7 = pbVar7 + 1;
          } while (bVar14);
          bVar15 = (!bVar16 && !bVar14) < bVar16;
          if ((!bVar16 && !bVar14) == bVar16) {
            *(undefined4 *)(param_2 + 0x10) = 0x20;
            pbVar5 = (byte *)TPGetValue(param_1,"value");
            if (pbVar5 == (byte *)0x0) {
              return 0;
            }
            iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x18),param_3,(undefined4 *)0x0,1);
            if (iVar8 == 0) {
              return 0;
            }
            pbVar5 = (byte *)TPGetValue(param_1,"elem");
            iVar8 = 1;
            piVar12 = (int *)(param_2 + 0x24);
          }
          else {
            iVar8 = 0xc;
            bVar14 = false;
            pbVar5 = local_11c;
            pbVar7 = (byte *)"changeanim2";
            do {
              if (iVar8 == 0) break;
              iVar8 = iVar8 + -1;
              bVar15 = *pbVar5 < *pbVar7;
              bVar14 = *pbVar5 == *pbVar7;
              pbVar5 = pbVar5 + 1;
              pbVar7 = pbVar7 + 1;
            } while (bVar14);
            bVar16 = (!bVar15 && !bVar14) < bVar15;
            if ((!bVar15 && !bVar14) == bVar15) {
              *(undefined4 *)(param_2 + 0x10) = 0x21;
              pbVar5 = (byte *)TPGetValue(param_1,"value");
              if (pbVar5 == (byte *)0x0) {
                return 0;
              }
              iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x18),param_3,(undefined4 *)0x0,1);
              if (iVar8 == 0) {
                return 0;
              }
              pbVar5 = (byte *)TPGetValue(param_1,"elem");
              iVar8 = 1;
              piVar12 = (int *)(param_2 + 0x24);
            }
            else {
              iVar8 = 8;
              bVar14 = false;
              pbVar5 = local_11c;
              pbVar7 = &DAT_0827ab01;
              do {
                if (iVar8 == 0) break;
                iVar8 = iVar8 + -1;
                bVar16 = *pbVar5 < *pbVar7;
                bVar14 = *pbVar5 == *pbVar7;
                pbVar5 = pbVar5 + 1;
                pbVar7 = pbVar7 + 1;
              } while (bVar14);
              bVar15 = (!bVar16 && !bVar14) < bVar16;
              if ((!bVar16 && !bVar14) == bVar16) {
                piVar12 = (int *)ecalloc(1,0x68);
                if (piVar12 == (int *)0x0) {
                  return 0;
                }
                *(undefined4 *)(param_2 + 0x10) = 0x22;
                iVar8 = SCtrlParsePlaySndInfo(param_1,param_3,piVar12);
                if (iVar8 == 0) {
                  free(piVar12);
                  strcat((char *)(g + 0x81d2),"\nError parsing PlaySnd");
                  return 0;
                }
                goto LAB_080be390;
              }
              iVar8 = 8;
              bVar14 = false;
              pbVar5 = local_11c;
              pbVar7 = (byte *)"stopsnd";
              do {
                if (iVar8 == 0) break;
                iVar8 = iVar8 + -1;
                bVar15 = *pbVar5 < *pbVar7;
                bVar14 = *pbVar5 == *pbVar7;
                pbVar5 = pbVar5 + 1;
                pbVar7 = pbVar7 + 1;
              } while (bVar14);
              bVar16 = (!bVar15 && !bVar14) < bVar15;
              if ((!bVar15 && !bVar14) == bVar15) {
                *(undefined4 *)(param_2 + 0x10) = 0x23;
                pbVar5 = (byte *)TPGetValue(param_1,"channel");
                if (pbVar5 == (byte *)0x0) {
                  piVar12 = g + 0x81d2;
                  pcVar4 = "Missing channel parameter";
                  goto LAB_080bede5;
                }
                iVar8 = 1;
                piVar12 = (int *)(param_2 + 0x18);
              }
              else {
                iVar8 = 7;
                bVar14 = false;
                pbVar5 = local_11c;
                pbVar7 = (byte *)"sndpan";
                do {
                  if (iVar8 == 0) break;
                  iVar8 = iVar8 + -1;
                  bVar16 = *pbVar5 < *pbVar7;
                  bVar14 = *pbVar5 == *pbVar7;
                  pbVar5 = pbVar5 + 1;
                  pbVar7 = pbVar7 + 1;
                } while (bVar14);
                bVar15 = (!bVar16 && !bVar14) < bVar16;
                if ((!bVar16 && !bVar14) == bVar16) {
                  *(undefined4 *)(param_2 + 0x10) = 0x24;
                  pbVar5 = (byte *)TPGetValue(param_1,"channel");
                  if (pbVar5 == (byte *)0x0) {
                    piVar12 = g + 0x81d2;
                    pcVar4 = "Missing channel parameter";
                    goto LAB_080bede5;
                  }
                  iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x18),param_3,(undefined4 *)0x0,1)
                  ;
                  if (iVar8 == 0) {
                    return 0;
                  }
                  pbVar5 = (byte *)TPGetValue(param_1,"abspan");
                  if (pbVar5 != (byte *)0x0) {
                    ConstExpI((int *)(param_2 + 0x30),1);
                    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x24),param_3,(undefined4 *)0x0,
                                           1);
                    if (iVar8 == 0) {
                      return 0;
                    }
                  }
                  pbVar5 = (byte *)TPGetValue(param_1,"pan");
                  iVar8 = 1;
                  piVar12 = (int *)(param_2 + 0x24);
                }
                else {
                  iVar8 = 8;
                  bVar14 = false;
                  pbVar5 = local_11c;
                  pbVar7 = (byte *)"lifeset";
                  do {
                    if (iVar8 == 0) break;
                    iVar8 = iVar8 + -1;
                    bVar15 = *pbVar5 < *pbVar7;
                    bVar14 = *pbVar5 == *pbVar7;
                    pbVar5 = pbVar5 + 1;
                    pbVar7 = pbVar7 + 1;
                  } while (bVar14);
                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                  if ((!bVar15 && !bVar14) == bVar15) {
                    *(undefined4 *)(param_2 + 0x10) = 10;
                    pbVar5 = (byte *)TPGetValue(param_1,"value");
                    if (pbVar5 == (byte *)0x0) {
                      return 0;
                    }
                    iVar8 = 1;
                    piVar12 = (int *)(param_2 + 0x18);
                  }
                  else {
                    iVar8 = 8;
                    bVar14 = false;
                    pbVar5 = local_11c;
                    pbVar7 = (byte *)(int)&DAT_0827adeb;
                    do {
                      if (iVar8 == 0) break;
                      iVar8 = iVar8 + -1;
                      bVar16 = *pbVar5 < *pbVar7;
                      bVar14 = *pbVar5 == *pbVar7;
                      pbVar5 = pbVar5 + 1;
                      pbVar7 = pbVar7 + 1;
                    } while (bVar14);
                    bVar15 = (!bVar16 && !bVar14) < bVar16;
                    if ((!bVar16 && !bVar14) == bVar16) {
                      *(undefined4 *)(param_2 + 0x10) = 0xb;
                      pbVar5 = (byte *)TPGetValue(param_1,"value");
                      if (pbVar5 == (byte *)0x0) {
                        return 0;
                      }
                      iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x18),param_3,
                                             (undefined4 *)0x0,1);
                      if (iVar8 == 0) {
                        return 0;
                      }
                      ConstExpI((int *)(param_2 + 0x24),1);
                      pbVar5 = (byte *)TPGetValue(param_1,"kill");
                      iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x24),param_3,
                                             (undefined4 *)0x0,1);
                      if (iVar8 == 0) {
                        return 0;
                      }
                      pbVar5 = (byte *)TPGetValue(param_1,"absolute");
                      iVar8 = 1;
                      piVar12 = (int *)(param_2 + 0x30);
                    }
                    else {
                      iVar8 = 9;
                      bVar14 = false;
                      pbVar5 = local_11c;
                      pbVar7 = (byte *)"powerset";
                      do {
                        if (iVar8 == 0) break;
                        iVar8 = iVar8 + -1;
                        bVar15 = *pbVar5 < *pbVar7;
                        bVar14 = *pbVar5 == *pbVar7;
                        pbVar5 = pbVar5 + 1;
                        pbVar7 = pbVar7 + 1;
                      } while (bVar14);
                      bVar16 = (!bVar15 && !bVar14) < bVar15;
                      if ((!bVar15 && !bVar14) == bVar15) {
                        *(undefined4 *)(param_2 + 0x10) = 0xc;
                        pbVar5 = (byte *)TPGetValue(param_1,"value");
                        if (pbVar5 == (byte *)0x0) {
                          return 0;
                        }
                        iVar8 = 1;
                        piVar12 = (int *)(param_2 + 0x18);
                      }
                      else {
                        iVar8 = 9;
                        bVar14 = false;
                        pbVar5 = local_11c;
                        pbVar7 = (byte *)(int)&DAT_0827addc;
                        do {
                          if (iVar8 == 0) break;
                          iVar8 = iVar8 + -1;
                          bVar16 = *pbVar5 < *pbVar7;
                          bVar14 = *pbVar5 == *pbVar7;
                          pbVar5 = pbVar5 + 1;
                          pbVar7 = pbVar7 + 1;
                        } while (bVar14);
                        bVar15 = (!bVar16 && !bVar14) < bVar16;
                        if ((!bVar16 && !bVar14) == bVar16) {
                          *(undefined4 *)(param_2 + 0x10) = 0xd;
                          pbVar5 = (byte *)TPGetValue(param_1,"value");
                          if (pbVar5 == (byte *)0x0) {
                            return 0;
                          }
                          iVar8 = 1;
                          piVar12 = (int *)(param_2 + 0x18);
                        }
                        else {
                          iVar8 = 7;
                          bVar14 = false;
                          pbVar5 = local_11c;
                          pbVar7 = (byte *)"posset";
                          do {
                            if (iVar8 == 0) break;
                            iVar8 = iVar8 + -1;
                            bVar15 = *pbVar5 < *pbVar7;
                            bVar14 = *pbVar5 == *pbVar7;
                            pbVar5 = pbVar5 + 1;
                            pbVar7 = pbVar7 + 1;
                          } while (bVar14);
                          bVar16 = (!bVar15 && !bVar14) < bVar15;
                          if ((!bVar15 && !bVar14) == bVar15) {
                            *(undefined4 *)(param_2 + 0x10) = 0x15;
                            pbVar5 = (byte *)TPGetValue(param_1,"x");
                            if (pbVar5 != (byte *)0x0) {
                              ConstExpI((int *)(param_2 + 0x18),1);
                              iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x3c),param_3,
                                                     (undefined4 *)0x0,2);
                              if (iVar8 == 0) {
                                return 0;
                              }
                            }
                            pbVar5 = (byte *)TPGetValue(param_1,"y");
                            if (pbVar5 != (byte *)0x0) {
                              ConstExpI((int *)(param_2 + 0x24),1);
                              iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x48),param_3,
                                                     (undefined4 *)0x0,2);
                              if (iVar8 == 0) {
                                return 0;
                              }
                            }
                            pbVar5 = (byte *)TPGetValue(param_1,"z");
                            if (pbVar5 == (byte *)0x0) {
                              return 1;
                            }
                            ConstExpI((int *)(param_2 + 0x30),1);
                            iVar8 = 2;
                            piVar12 = (int *)(param_2 + 0x54);
                          }
                          else {
                            iVar8 = 7;
                            bVar14 = false;
                            pbVar5 = local_11c;
                            pbVar7 = (byte *)"posadd";
                            do {
                              if (iVar8 == 0) break;
                              iVar8 = iVar8 + -1;
                              bVar16 = *pbVar5 < *pbVar7;
                              bVar14 = *pbVar5 == *pbVar7;
                              pbVar5 = pbVar5 + 1;
                              pbVar7 = pbVar7 + 1;
                            } while (bVar14);
                            bVar15 = (!bVar16 && !bVar14) < bVar16;
                            if ((!bVar16 && !bVar14) == bVar16) {
                              *(undefined4 *)(param_2 + 0x10) = 0x16;
                              pbVar5 = (byte *)TPGetValue(param_1,"x");
                              if (pbVar5 != (byte *)0x0) {
                                ConstExpI((int *)(param_2 + 0x18),1);
                                iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x3c),param_3,
                                                       (undefined4 *)0x0,2);
                                if (iVar8 == 0) {
                                  return 0;
                                }
                              }
                              pbVar5 = (byte *)TPGetValue(param_1,"y");
                              if (pbVar5 != (byte *)0x0) {
                                ConstExpI((int *)(param_2 + 0x24),1);
                                iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x48),param_3,
                                                       (undefined4 *)0x0,2);
                                if (iVar8 == 0) {
                                  return 0;
                                }
                              }
                              pbVar5 = (byte *)TPGetValue(param_1,"z");
                              if (pbVar5 == (byte *)0x0) {
                                return 1;
                              }
                              ConstExpI((int *)(param_2 + 0x30),1);
                              iVar8 = 2;
                              piVar12 = (int *)(param_2 + 0x54);
                            }
                            else {
                              iVar8 = 10;
                              bVar14 = false;
                              pbVar5 = local_11c;
                              pbVar7 = (byte *)"posfreeze";
                              do {
                                if (iVar8 == 0) break;
                                iVar8 = iVar8 + -1;
                                bVar15 = *pbVar5 < *pbVar7;
                                bVar14 = *pbVar5 == *pbVar7;
                                pbVar5 = pbVar5 + 1;
                                pbVar7 = pbVar7 + 1;
                              } while (bVar14);
                              bVar16 = (!bVar15 && !bVar14) < bVar15;
                              if ((!bVar15 && !bVar14) == bVar15) {
                                *(undefined4 *)(param_2 + 0x10) = 0x17;
                                piVar12 = (int *)(param_2 + 0x18);
                                ConstExpI(piVar12,1);
                                pbVar5 = (byte *)TPGetValue(param_1,"value");
                                iVar8 = 1;
                              }
                              else {
                                iVar8 = 7;
                                bVar14 = false;
                                pbVar5 = local_11c;
                                pbVar7 = (byte *)(int)&DAT_0827adf9;
                                do {
                                  if (iVar8 == 0) break;
                                  iVar8 = iVar8 + -1;
                                  bVar16 = *pbVar5 < *pbVar7;
                                  bVar14 = *pbVar5 == *pbVar7;
                                  pbVar5 = pbVar5 + 1;
                                  pbVar7 = pbVar7 + 1;
                                } while (bVar14);
                                bVar15 = (!bVar16 && !bVar14) < bVar16;
                                if ((!bVar16 && !bVar14) == bVar16) {
                                  *(undefined4 *)(param_2 + 0x10) = 0x18;
                                  pbVar5 = (byte *)TPGetValue(param_1,"x");
                                  if (pbVar5 != (byte *)0x0) {
                                    ConstExpI((int *)(param_2 + 0x18),1);
                                    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x3c),param_3,
                                                           (undefined4 *)0x0,2);
                                    if (iVar8 == 0) {
                                      return 0;
                                    }
                                  }
                                  pbVar5 = (byte *)TPGetValue(param_1,"y");
                                  if (pbVar5 != (byte *)0x0) {
                                    ConstExpI((int *)(param_2 + 0x24),1);
                                    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x48),param_3,
                                                           (undefined4 *)0x0,2);
                                    if (iVar8 == 0) {
                                      return 0;
                                    }
                                  }
                                  pbVar5 = (byte *)TPGetValue(param_1,"z");
                                  if (pbVar5 == (byte *)0x0) {
                                    return 1;
                                  }
                                  ConstExpI((int *)(param_2 + 0x30),1);
                                  iVar8 = 2;
                                  piVar12 = (int *)(param_2 + 0x54);
                                }
                                else {
                                  iVar8 = 7;
                                  bVar14 = false;
                                  pbVar5 = local_11c;
                                  pbVar7 = (byte *)(int)&DAT_0827ae06;
                                  do {
                                    if (iVar8 == 0) break;
                                    iVar8 = iVar8 + -1;
                                    bVar15 = *pbVar5 < *pbVar7;
                                    bVar14 = *pbVar5 == *pbVar7;
                                    pbVar5 = pbVar5 + 1;
                                    pbVar7 = pbVar7 + 1;
                                  } while (bVar14);
                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                  if ((!bVar15 && !bVar14) == bVar15) {
                                    *(undefined4 *)(param_2 + 0x10) = 0x19;
                                    pbVar5 = (byte *)TPGetValue(param_1,"x");
                                    if (pbVar5 != (byte *)0x0) {
                                      ConstExpI((int *)(param_2 + 0x18),1);
                                      iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x3c),param_3,
                                                             (undefined4 *)0x0,2);
                                      if (iVar8 == 0) {
                                        return 0;
                                      }
                                    }
                                    pbVar5 = (byte *)TPGetValue(param_1,"y");
                                    if (pbVar5 != (byte *)0x0) {
                                      ConstExpI((int *)(param_2 + 0x24),1);
                                      iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x48),param_3,
                                                             (undefined4 *)0x0,2);
                                      if (iVar8 == 0) {
                                        return 0;
                                      }
                                    }
                                    pbVar5 = (byte *)TPGetValue(param_1,"z");
                                    if (pbVar5 == (byte *)0x0) {
                                      return 1;
                                    }
                                    ConstExpI((int *)(param_2 + 0x30),1);
                                    iVar8 = 2;
                                    piVar12 = (int *)(param_2 + 0x54);
                                  }
                                  else {
                                    iVar8 = 7;
                                    bVar14 = false;
                                    pbVar5 = local_11c;
                                    pbVar7 = &DAT_0827ab7c;
                                    do {
                                      if (iVar8 == 0) break;
                                      iVar8 = iVar8 + -1;
                                      bVar16 = *pbVar5 < *pbVar7;
                                      bVar14 = *pbVar5 == *pbVar7;
                                      pbVar5 = pbVar5 + 1;
                                      pbVar7 = pbVar7 + 1;
                                    } while (bVar14);
                                    bVar15 = (!bVar16 && !bVar14) < bVar16;
                                    if ((!bVar16 && !bVar14) == bVar16) {
                                      *(undefined4 *)(param_2 + 0x10) = 0x1a;
                                      pbVar5 = (byte *)TPGetValue(param_1,"x");
                                      if (pbVar5 != (byte *)0x0) {
                                        ConstExpI((int *)(param_2 + 0x18),1);
                                        iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x3c),
                                                               param_3,(undefined4 *)0x0,2);
                                        if (iVar8 == 0) {
                                          return 0;
                                        }
                                      }
                                      pbVar5 = (byte *)TPGetValue(param_1,"y");
                                      if (pbVar5 != (byte *)0x0) {
                                        ConstExpI((int *)(param_2 + 0x24),1);
                                        iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x48),
                                                               param_3,(undefined4 *)0x0,2);
                                        if (iVar8 == 0) {
                                          return 0;
                                        }
                                      }
                                      pbVar5 = (byte *)TPGetValue(param_1,"z");
                                      if (pbVar5 == (byte *)0x0) {
                                        return 1;
                                      }
                                      ConstExpI((int *)(param_2 + 0x30),1);
                                      iVar8 = 2;
                                      piVar12 = (int *)(param_2 + 0x54);
                                    }
                                    else {
                                      iVar8 = 8;
                                      bVar14 = false;
                                      pbVar5 = local_11c;
                                      pbVar7 = (byte *)"gravity";
                                      do {
                                        if (iVar8 == 0) break;
                                        iVar8 = iVar8 + -1;
                                        bVar15 = *pbVar5 < *pbVar7;
                                        bVar14 = *pbVar5 == *pbVar7;
                                        pbVar5 = pbVar5 + 1;
                                        pbVar7 = pbVar7 + 1;
                                      } while (bVar14);
                                      bVar16 = (!bVar15 && !bVar14) < bVar15;
                                      if ((!bVar15 && !bVar14) == bVar15) {
                                        *(undefined4 *)(param_2 + 0x10) = 0x1b;
                                        return 1;
                                      }
                                      iVar8 = 7;
                                      bVar14 = false;
                                      pbVar5 = local_11c;
                                      pbVar7 = &DAT_0827ab8b;
                                      do {
                                        if (iVar8 == 0) break;
                                        iVar8 = iVar8 + -1;
                                        bVar16 = *pbVar5 < *pbVar7;
                                        bVar14 = *pbVar5 == *pbVar7;
                                        pbVar5 = pbVar5 + 1;
                                        pbVar7 = pbVar7 + 1;
                                      } while (bVar14);
                                      bVar15 = (!bVar16 && !bVar14) < bVar16;
                                      if ((!bVar16 && !bVar14) == bVar16) {
                                        piVar12 = (int *)ecalloc(1,0x514);
                                        if (piVar12 == (int *)0x0) {
                                          return 0;
                                        }
                                        *(undefined4 *)(param_2 + 0x10) = 0x25;
                                        bVar14 = SCtrlParseHitDef(param_1,param_3,piVar12);
                                        if (GHIDRA_ZEXT8(bVar14) == 0) {
                                          free(piVar12);
                                          strcat((char *)(g + 0x81d2),"\nError parsing Hitdef");
                                          return 0;
                                        }
                                        goto LAB_080be2cc;
                                      }
                                      iVar8 = 0xc;
                                      bVar14 = false;
                                      pbVar5 = local_11c;
                                      pbVar7 = (byte *)"reversaldef";
                                      do {
                                        if (iVar8 == 0) break;
                                        iVar8 = iVar8 + -1;
                                        bVar15 = *pbVar5 < *pbVar7;
                                        bVar14 = *pbVar5 == *pbVar7;
                                        pbVar5 = pbVar5 + 1;
                                        pbVar7 = pbVar7 + 1;
                                      } while (bVar14);
                                      bVar16 = (!bVar15 && !bVar14) < bVar15;
                                      if ((!bVar15 && !bVar14) == bVar15) {
                                        piVar12 = (int *)ecalloc(1,0x514);
                                        if (piVar12 == (int *)0x0) {
                                          return 0;
                                        }
                                        *(undefined4 *)(param_2 + 0x10) = 0x26;
                                        pcVar4 = TPGetValue(param_1,"reversal.attr");
                                        if (pcVar4 == (char *)0x0) {
                                          piVar12 = g + 0x81d2;
                                          pcVar4 = "Missing reversal.attr parameter";
                                        }
                                        else {
                                          uVar6 = ParseHitAttr((int)pcVar4,0);
                                          piVar12[0x69] = uVar6;
                                          if (uVar6 != 0xffffffff) {
                                            bVar14 = SCtrlParseHitDef(param_1,param_3,piVar12);
                                            if (GHIDRA_ZEXT8(bVar14) == 0) {
                                              free(piVar12);
                                              strcat((char *)(g + 0x81d2),
                                                     "\nError parsing Reversaldef");
                                              return 0;
                                            }
                                            goto LAB_080be2cc;
                                          }
                                          piVar12 = g + 0x81d2;
                                          ghidra_fa[0] = (void *)(pcVar4);
                                          pcVar4 = "Invalid reversal.attr: %s";
                                        }
                                        goto LAB_080bede5;
                                      }
                                      iVar8 = 6;
                                      bVar14 = false;
                                      pbVar5 = local_11c;
                                      pbVar7 = (byte *)(int)&DAT_0827ac01;
                                      do {
                                        if (iVar8 == 0) break;
                                        iVar8 = iVar8 + -1;
                                        bVar16 = *pbVar5 < *pbVar7;
                                        bVar14 = *pbVar5 == *pbVar7;
                                        pbVar5 = pbVar5 + 1;
                                        pbVar7 = pbVar7 + 1;
                                      } while (bVar14);
                                      bVar15 = (!bVar16 && !bVar14) < bVar16;
                                      if ((!bVar16 && !bVar14) == bVar16) {
                                        *(undefined4 *)(param_2 + 0x10) = 0x1e;
                                        pcVar4 = TPGetValue(param_1,"value");
                                        if (pcVar4 == (char *)0x0) {
                                          pcVar4 = TPGetValue(param_1,"value2");
                                          if (pcVar4 == (char *)0x0) {
                                            return 0;
                                          }
                                          iVar8 = 1;
                                        }
                                        else {
                                          iVar8 = 0;
                                        }
                                        ConstExpI((int *)(param_2 + 0x30),iVar8);
                                        uVar6 = ParseHitAttr((int)pcVar4,0);
                                        ConstExpI((int *)(param_2 + 0x18),uVar6);
                                        if (*(int *)(param_2 + 0x20) == -1) {
                                          return 0;
                                        }
                                        piVar12 = (int *)(param_2 + 0x24);
                                        ConstExpI(piVar12,1);
                                        pbVar5 = (byte *)TPGetValue(param_1,"time");
                                        iVar8 = 1;
                                      }
                                      else {
                                        iVar8 = 9;
                                        bVar14 = false;
                                        pbVar5 = local_11c;
                                        pbVar7 = (byte *)"nothitby";
                                        do {
                                          if (iVar8 == 0) break;
                                          iVar8 = iVar8 + -1;
                                          bVar15 = *pbVar5 < *pbVar7;
                                          bVar14 = *pbVar5 == *pbVar7;
                                          pbVar5 = pbVar5 + 1;
                                          pbVar7 = pbVar7 + 1;
                                        } while (bVar14);
                                        bVar16 = (!bVar15 && !bVar14) < bVar15;
                                        if ((!bVar15 && !bVar14) == bVar15) {
                                          *(undefined4 *)(param_2 + 0x10) = 0x1e;
                                          pcVar4 = TPGetValue(param_1,"value");
                                          if (pcVar4 == (char *)0x0) {
                                            pcVar4 = TPGetValue(param_1,"value2");
                                            if (pcVar4 == (char *)0x0) {
                                              return 0;
                                            }
                                            iVar8 = 1;
                                          }
                                          else {
                                            iVar8 = 0;
                                          }
                                          ConstExpI((int *)(param_2 + 0x30),iVar8);
                                          uVar6 = ParseHitAttr((int)pcVar4,0);
                                          ConstExpI((int *)(param_2 + 0x18),uVar6);
                                          if (*(uint *)(param_2 + 0x20) == 0xffffffff) {
                                            return 0;
                                          }
                                          *(uint *)(param_2 + 0x20) =
                                               (*(uint *)(param_2 + 0x20) ^ 0xffffffff) & 0xfff;
                                          piVar12 = (int *)(param_2 + 0x24);
                                          ConstExpI(piVar12,1);
                                          pbVar5 = (byte *)TPGetValue(param_1,"time");
                                          iVar8 = 1;
                                        }
                                        else {
                                          iVar8 = 10;
                                          bVar14 = false;
                                          pbVar5 = local_11c;
                                          pbVar7 = (byte *)"hitvelset";
                                          do {
                                            if (iVar8 == 0) break;
                                            iVar8 = iVar8 + -1;
                                            bVar16 = *pbVar5 < *pbVar7;
                                            bVar14 = *pbVar5 == *pbVar7;
                                            pbVar5 = pbVar5 + 1;
                                            pbVar7 = pbVar7 + 1;
                                          } while (bVar14);
                                          bVar15 = (!bVar16 && !bVar14) < bVar16;
                                          if ((!bVar16 && !bVar14) == bVar16) {
                                            *(undefined4 *)(param_2 + 0x10) = 0x65;
                                            pbVar5 = (byte *)TPGetValue(param_1,"x");
                                            iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x18),
                                                                   param_3,(undefined4 *)0x0,1);
                                            if (iVar8 == 0) {
                                              return 0;
                                            }
                                            pbVar5 = (byte *)TPGetValue(param_1,"y");
                                            iVar8 = 1;
                                            piVar12 = (int *)(param_2 + 0x24);
                                          }
                                          else {
                                            iVar8 = 0xb;
                                            bVar14 = false;
                                            pbVar5 = local_11c;
                                            pbVar7 = (byte *)"hitfallset";
                                            do {
                                              if (iVar8 == 0) break;
                                              iVar8 = iVar8 + -1;
                                              bVar15 = *pbVar5 < *pbVar7;
                                              bVar14 = *pbVar5 == *pbVar7;
                                              pbVar5 = pbVar5 + 1;
                                              pbVar7 = pbVar7 + 1;
                                            } while (bVar14);
                                            bVar16 = (!bVar15 && !bVar14) < bVar15;
                                            if ((!bVar15 && !bVar14) == bVar15) {
                                              *(undefined4 *)(param_2 + 0x10) = 100;
                                              ConstExpI((int *)(param_2 + 0x18),-1);
                                              ConstExpF((int *)(param_2 + 0x3c),-0x39001000);
                                              ConstExpF((int *)(param_2 + 0x48),-0x39001000);
                                              pbVar5 = (byte *)TPGetValue(param_1,"value");
                                              iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 + 0x18),
                                                                     param_3,(undefined4 *)0x0,1);
                                              if (iVar8 == 0) {
                                                return 0;
                                              }
                                              pbVar5 = (byte *)TPGetValue(param_1,"velocity");
                                              SCtrlReadExpList(pbVar5,"ff",param_3,&local_120,
                                                               (int *)(param_2 + 0x3c),
                                                               (int *)(param_2 + 0x48));
                                              goto joined_r0x080bb972;
                                            }
                                            iVar8 = 0xe;
                                            bVar14 = false;
                                            pbVar5 = local_11c;
                                            pbVar7 = (byte *)"hitfalldamage";
                                            do {
                                              if (iVar8 == 0) break;
                                              iVar8 = iVar8 + -1;
                                              bVar16 = *pbVar5 < *pbVar7;
                                              bVar14 = *pbVar5 == *pbVar7;
                                              pbVar5 = pbVar5 + 1;
                                              pbVar7 = pbVar7 + 1;
                                            } while (bVar14);
                                            bVar15 = (!bVar16 && !bVar14) < bVar16;
                                            if ((!bVar16 && !bVar14) == bVar16) {
                                              *(undefined4 *)(param_2 + 0x10) = 0x66;
                                              return 1;
                                            }
                                            iVar8 = 0xb;
                                            bVar14 = false;
                                            pbVar5 = local_11c;
                                            pbVar7 = (byte *)"hitfallvel";
                                            do {
                                              if (iVar8 == 0) break;
                                              iVar8 = iVar8 + -1;
                                              bVar15 = *pbVar5 < *pbVar7;
                                              bVar14 = *pbVar5 == *pbVar7;
                                              pbVar5 = pbVar5 + 1;
                                              pbVar7 = pbVar7 + 1;
                                            } while (bVar14);
                                            bVar16 = (!bVar15 && !bVar14) < bVar15;
                                            if ((!bVar15 && !bVar14) == bVar15) {
                                              *(undefined4 *)(param_2 + 0x10) = 0x67;
                                              return 1;
                                            }
                                            iVar8 = 7;
                                            bVar14 = false;
                                            pbVar5 = local_11c;
                                            pbVar7 = (byte *)"hitadd";
                                            do {
                                              if (iVar8 == 0) break;
                                              iVar8 = iVar8 + -1;
                                              bVar16 = *pbVar5 < *pbVar7;
                                              bVar14 = *pbVar5 == *pbVar7;
                                              pbVar5 = pbVar5 + 1;
                                              pbVar7 = pbVar7 + 1;
                                            } while (bVar14);
                                            bVar15 = (!bVar16 && !bVar14) < bVar16;
                                            if ((!bVar16 && !bVar14) == bVar16) {
                                              *(undefined4 *)(param_2 + 0x10) = 0x68;
                                              pbVar5 = (byte *)TPGetValue(param_1,"value");
                                              if (pbVar5 == (byte *)0x0) {
                                                return 0;
                                              }
                                              iVar8 = 1;
                                              piVar12 = (int *)(param_2 + 0x18);
                                            }
                                            else {
                                              iVar8 = 0xd;
                                              bVar14 = false;
                                              pbVar5 = local_11c;
                                              pbVar7 = (byte *)"attackmulset";
                                              do {
                                                if (iVar8 == 0) break;
                                                iVar8 = iVar8 + -1;
                                                bVar15 = *pbVar5 < *pbVar7;
                                                bVar14 = *pbVar5 == *pbVar7;
                                                pbVar5 = pbVar5 + 1;
                                                pbVar7 = pbVar7 + 1;
                                              } while (bVar14);
                                              bVar16 = (!bVar15 && !bVar14) < bVar15;
                                              if ((!bVar15 && !bVar14) == bVar15) {
                                                *(undefined4 *)(param_2 + 0x10) = 0x69;
                                                pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                if (pbVar5 == (byte *)0x0) {
                                                  return 0;
                                                }
                                                iVar8 = 2;
                                                piVar12 = (int *)(param_2 + 0x3c);
                                              }
                                              else {
                                                iVar8 = 0xe;
                                                bVar14 = false;
                                                pbVar5 = local_11c;
                                                pbVar7 = (byte *)"defencemulset";
                                                do {
                                                  if (iVar8 == 0) break;
                                                  iVar8 = iVar8 + -1;
                                                  bVar16 = *pbVar5 < *pbVar7;
                                                  bVar14 = *pbVar5 == *pbVar7;
                                                  pbVar5 = pbVar5 + 1;
                                                  pbVar7 = pbVar7 + 1;
                                                } while (bVar14);
                                                bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                if ((!bVar16 && !bVar14) == bVar16) {
                                                  *(undefined4 *)(param_2 + 0x10) = 0x6a;
                                                  pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                  if (pbVar5 == (byte *)0x0) {
                                                    return 0;
                                                  }
                                                  iVar8 = 2;
                                                  piVar12 = (int *)(param_2 + 0x3c);
                                                }
                                                else {
                                                  iVar8 = 0xd;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"statetypeset";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) == bVar15) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0x6e;
                                                    ConstExpI((int *)(param_2 + 0x18),-1);
                                                    ConstExpI((int *)(param_2 + 0x24),-1);
                                                    ConstExpI((int *)(param_2 + 0x30),-1);
                                                    pcVar4 = TPGetValue(param_1,"statetype");
                                                    if (pcVar4 == (char *)0x0) {
                                                      pcVar4 = TPGetValue(param_1,"value");
                                                    }
                                                    if (pcVar4 != (char *)0x0) {
                                                      iVar8 = *(int *)(__ctype_tolower + *pcVar4 * 4
                                                                      );
                                                      if (iVar8 == 99) {
                                                        iVar8 = 2;
                                                      }
                                                      else if (iVar8 < 100) {
                                                        if (iVar8 != 0x61) {
LAB_080bbc25:
                                                          piVar12 = g + 0x81d2;
                                                          ghidra_fa[0] = (void *)(pcVar4);
                                                          pcVar4 = "State type \"%s\" not valid";
                                                          goto LAB_080bede5;
                                                        }
                                                        iVar8 = 3;
                                                      }
                                                      else if (iVar8 == 0x6c) {
                                                        iVar8 = 4;
                                                      }
                                                      else {
                                                        if (iVar8 != 0x73) goto LAB_080bbc25;
                                                        iVar8 = 1;
                                                      }
                                                      ConstExpI((int *)(param_2 + 0x18),iVar8);
                                                    }
                                                    pcVar4 = TPGetValue(param_1,"movetype");
                                                    if (pcVar4 != (char *)0x0) {
                                                      iVar8 = *(int *)(__ctype_tolower + *pcVar4 * 4
                                                                      );
                                                      if (iVar8 == 0x68) {
                                                        iVar8 = 2;
                                                      }
                                                      else if (iVar8 < 0x69) {
                                                        if (iVar8 != 0x61) {
LAB_080bbcb0:
                                                          piVar12 = g + 0x81d2;
                                                          ghidra_fa[0] = (void *)(pcVar4);
                                                          pcVar4 = "State movetype \"%s\" not valid"
                                                          ;
                                                          goto LAB_080bede5;
                                                        }
                                                        iVar8 = 1;
                                                      }
                                                      else {
                                                        if (iVar8 != 0x69) goto LAB_080bbcb0;
                                                        iVar8 = 0;
                                                      }
                                                      ConstExpI((int *)(param_2 + 0x24),iVar8);
                                                    }
                                                    pcVar4 = TPGetValue(param_1,"physics");
                                                    if (pcVar4 == (char *)0x0) {
                                                      return 1;
                                                    }
                                                    iVar8 = *(int *)(__ctype_tolower + *pcVar4 * 4);
                                                    if (iVar8 == 99) {
                                                      iVar8 = 2;
                                                    }
                                                    else if (iVar8 < 100) {
                                                      if (iVar8 != 0x61) {
LAB_080bbd40:
                                                        piVar12 = g + 0x81d2;
                                                        ghidra_fa[0] = (void *)(pcVar4);
                                                        pcVar4 = "State physics \"%s\" not valid";
                                                        goto LAB_080bede5;
                                                      }
                                                      iVar8 = 3;
                                                    }
                                                    else if (iVar8 == 0x6e) {
                                                      iVar8 = 0;
                                                    }
                                                    else {
                                                      if (iVar8 != 0x73) goto LAB_080bbd40;
LAB_080be8a5:
                                                      iVar8 = 1;
                                                    }
                                                    piVar12 = (int *)(param_2 + 0x30);
LAB_080be8b2:
                                                    ConstExpI(piVar12,iVar8);
                                                    return 1;
                                                  }
                                                  iVar8 = 0xc;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"hitoverride";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                  if ((!bVar16 && !bVar14) == bVar16) {
                                                    piVar12 = (int *)ecalloc(1,0x28);
                                                    if (piVar12 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    *(undefined4 *)(param_2 + 0x10) = 0x78;
                                                    bVar14 = SCtrlParseHitOverride
                                                                       (param_1,param_3,piVar12);
                                                    if (GHIDRA_ZEXT8(bVar14) == 0) {
                                                      free(piVar12);
                                                      strcat((char *)(g + 0x81d2),
                                                             "\nError parsing HitOverride");
                                                      return 0;
                                                    }
                                                    pbVar5 = (byte *)TPGetValue(param_1,"slot");
                                                    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                         0x18),
                                                                           param_3,(undefined4 *)0x0
                                                                           ,1);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    goto LAB_080be390;
                                                  }
                                                  iVar8 = 0xd;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"movehitreset";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) == bVar15) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0x82;
                                                    return 1;
                                                  }
                                                  iVar8 = 0xe;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"assertspecial";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                  if ((!bVar16 && !bVar14) == bVar16) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0x96;
                                                    pcVar4 = TPGetValue(param_1,"flag");
                                                    if (pcVar4 == (char *)0x0) {
                                                      piVar12 = g + 0x81d2;
                                                      pcVar4 = 
                                                  "AssertSpecial flag parameter missing";
                                                  }
                                                  else {
                                                    iVar8 = ParseSpecialFlag(pcVar4,&local_128,
                                                                             &local_124);
                                                    if (iVar8 == 0) {
                                                      piVar12 = g + 0x81d2;
                                                      ghidra_fa[0] = (void *)(pcVar4);
                                                      pcVar4 = "AssertSpecial flag \"%s\" not valid"
                                                      ;
                                                    }
                                                    else {
                                                      ConstExpI((int *)(param_2 + 0x18),local_128);
                                                      ConstExpI((int *)(param_2 + 0x3c),local_124);
                                                      ConstExpI((int *)(param_2 + 0x24),-1);
                                                      ConstExpI((int *)(param_2 + 0x30),-1);
                                                      pcVar4 = TPGetValue(param_1,"flag2");
                                                      if (pcVar4 != (char *)0x0) {
                                                        iVar8 = ParseSpecialFlag(pcVar4,&local_128,
                                                                                 &local_124);
                                                        if (iVar8 == 0) {
                                                          piVar12 = g + 0x81d2;
                                                          ghidra_fa[0] = (void *)(pcVar4);
                                                          pcVar4 = 
                                                  "AssertSpecial flag2 \"%s\" not valid";
                                                  goto LAB_080bede5;
                                                  }
                                                  ConstExpI((int *)(param_2 + 0x24),local_128);
                                                  ConstExpI((int *)(param_2 + 0x48),local_124);
                                                  }
                                                  pcVar4 = TPGetValue(param_1,"flag3");
                                                  if (pcVar4 == (char *)0x0) {
                                                    return 1;
                                                  }
                                                  iVar8 = ParseSpecialFlag(pcVar4,&local_128,
                                                                           &local_124);
                                                  if (iVar8 != 0) {
                                                    ConstExpI((int *)(param_2 + 0x30),local_128);
                                                    piVar12 = (int *)(param_2 + 0x54);
                                                    iVar8 = local_124;
                                                    goto LAB_080be8b2;
                                                  }
                                                  piVar12 = g + 0x81d2;
                                                  ghidra_fa[0] = (void *)(pcVar4);
                                                  pcVar4 = "AssertSpecial flag3 \"%s\" not valid";
                                                  }
                                                  }
                                                  goto LAB_080bede5;
                                                  }
                                                  iVar8 = 0xb;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"projectile";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) == bVar15) {
                                                    piVar12 = (int *)ecalloc(1,0x69c);
                                                    if (piVar12 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    *(undefined4 *)(param_2 + 0x10) = 0x27;
                                                    iVar8 = SCtrlParseProjectile
                                                                      (param_1,param_3,piVar12);
                                                    if (iVar8 == 0) {
                                                      free(piVar12);
                                                      strcat((char *)(g + 0x81d2),
                                                             "\nError parsing Projectile");
                                                      return 0;
                                                    }
                                                    goto LAB_080be390;
                                                  }
                                                  iVar8 = 6;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)(int)&DAT_0827a474;
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                  if ((!bVar16 && !bVar14) == bVar16) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0x28;
                                                    ConstExpI((int *)(param_2 + 0x3c),0);
                                                    ConstExpI((int *)(param_2 + 0x18),0);
                                                    ConstExpI((int *)(param_2 + 0x24),0);
                                                    ConstExpI((int *)(param_2 + 0x30),0);
                                                    pbVar5 = (byte *)TPGetValue(param_1,"edge");
                                                    SCtrlReadExpList(pbVar5,"ii",param_3,&local_120,
                                                                     (int *)(param_2 + 0x18),
                                                                     (int *)(param_2 + 0x24));
                                                    if ((pbVar5 != (byte *)0x0) && (*local_120 != 0)
                                                       ) {
                                                      return 0;
                                                    }
                                                    pbVar7 = (byte *)TPGetValue(param_1,"player");
                                                    SCtrlReadExpList(pbVar7,"ii",param_3,&local_120,
                                                                     (int *)(param_2 + 0x30),
                                                                     (int *)(param_2 + 0x3c));
                                                    if ((pbVar7 != (byte *)0x0) && (*local_120 != 0)
                                                       ) {
                                                      return 0;
                                                    }
                                                    if (pbVar5 != (byte *)0x0 ||
                                                        pbVar7 != (byte *)0x0) {
                                                      return 1;
                                                    }
                                                    pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                    pbVar5 = SCtrlReadExpList(pbVar5,"ii",param_3,
                                                                              &local_120,
                                                                              (int *)(param_2 + 0x18
                                                                                     ),(int *)(
                                                  param_2 + 0x24));
                                                  if (pbVar5 != (byte *)0x0) {
                                                    if (*local_120 == 0) {
                                                      expcpytrig((int *)(param_2 + 0x30),
                                                                 (int *)(param_2 + 0x18));
                                                      expcpytrig((int *)(param_2 + 0x3c),
                                                                 (int *)(param_2 + 0x24));
                                                      return 1;
                                                    }
                                                    return 0;
                                                  }
                                                  return 0;
                                                  }
                                                  iVar8 = 0xc;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)(int)&DAT_0827bf86;
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) == bVar15) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0x33;
                                                    pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                    iVar8 = 1;
                                                    piVar12 = (int *)(param_2 + 0x18);
                                                    goto LAB_080be815;
                                                  }
                                                  iVar8 = 10;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"angledraw";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                  if ((!bVar16 && !bVar14) == bVar16) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0x3c;
                                                    ConstExpF((int *)(param_2 + 0x48),0x3f800000);
                                                    ConstExpF((int *)(param_2 + 0x54),0x3f800000);
                                                    iVar8 = ItoP_TPConstF(param_1,"value",
                                                                          (int *)(param_2 + 0x3c),
                                                                          param_3,-0x39001000);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    pbVar5 = (byte *)TPGetValue(param_1,"scale");
                                                    SCtrlReadExpList(pbVar5,"ff",param_3,&local_120,
                                                                     (int *)(param_2 + 0x48),
                                                                     (int *)(param_2 + 0x54));
                                                    goto joined_r0x080bb972;
                                                  }
                                                  iVar8 = 9;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"angleset";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) == bVar15) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0x3d;
                                                    pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                    iVar8 = 2;
                                                    piVar12 = (int *)(param_2 + 0x3c);
                                                  }
                                                  else {
                                                    iVar8 = 9;
                                                    bVar14 = false;
                                                    pbVar5 = local_11c;
                                                    pbVar7 = (byte *)"angleadd";
                                                    do {
                                                      if (iVar8 == 0) break;
                                                      iVar8 = iVar8 + -1;
                                                      bVar16 = *pbVar5 < *pbVar7;
                                                      bVar14 = *pbVar5 == *pbVar7;
                                                      pbVar5 = pbVar5 + 1;
                                                      pbVar7 = pbVar7 + 1;
                                                    } while (bVar14);
                                                    bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                    if ((!bVar16 && !bVar14) == bVar16) {
                                                      *(undefined4 *)(param_2 + 0x10) = 0x3e;
                                                      pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                      iVar8 = 2;
                                                      piVar12 = (int *)(param_2 + 0x3c);
                                                    }
                                                    else {
                                                      iVar8 = 9;
                                                      bVar14 = false;
                                                      pbVar5 = local_11c;
                                                      pbVar7 = (byte *)"anglemul";
                                                      do {
                                                        if (iVar8 == 0) break;
                                                        iVar8 = iVar8 + -1;
                                                        bVar15 = *pbVar5 < *pbVar7;
                                                        bVar14 = *pbVar5 == *pbVar7;
                                                        pbVar5 = pbVar5 + 1;
                                                        pbVar7 = pbVar7 + 1;
                                                      } while (bVar14);
                                                      bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                      if ((!bVar15 && !bVar14) != bVar15) {
                                                        iVar8 = 6;
                                                        bVar14 = false;
                                                        pbVar5 = local_11c;
                                                        pbVar7 = (byte *)(int)&DAT_08284679;
                                                        do {
                                                          if (iVar8 == 0) break;
                                                          iVar8 = iVar8 + -1;
                                                          bVar16 = *pbVar5 < *pbVar7;
                                                          bVar14 = *pbVar5 == *pbVar7;
                                                          pbVar5 = pbVar5 + 1;
                                                          pbVar7 = pbVar7 + 1;
                                                        } while (bVar14);
                                                        bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                        if ((!bVar16 && !bVar14) == bVar16) {
                                                          *(undefined4 *)(param_2 + 0x10) = 0x41;
                                                          piVar12 = (int *)(param_2 + 0x18);
                                                          ConstExpI(piVar12,-1);
                                                          ConstExpI((int *)(param_2 + 0x24),0x100);
                                                          ConstExpI((int *)(param_2 + 0x30),0);
                                                          pcVar4 = TPGetValue(param_1,"trans");
                                                          if (pcVar4 != (char *)0x0) {
                                                            iVar8 = _alemu_stricmp(pcVar4,"none");
                                                            if (iVar8 == 0) {
                                                              iVar8 = 0;
                                                            }
                                                            else if ((*pcVar4 == '\0') ||
                                                                    (iVar8 = _alemu_stricmp(pcVar4,
                                                  "default"), iVar8 == 0)) {
                                                    iVar8 = -1;
                                                  }
                                                  else {
                                                    iVar8 = _alemu_stricmp(pcVar4,"add");
                                                    if (iVar8 == 0) {
                                                      iVar8 = 1;
                                                    }
                                                    else {
                                                      iVar8 = _alemu_stricmp(pcVar4,"add1");
                                                      if (iVar8 == 0) {
                                                        ConstExpI(piVar12,3);
                                                        ConstExpI((int *)(param_2 + 0x24),0x100);
                                                        iVar8 = 0x80;
                                                        piVar12 = (int *)(param_2 + 0x30);
                                                      }
                                                      else {
                                                        iVar8 = _alemu_stricmp(pcVar4,"addalpha");
                                                        if (iVar8 == 0) {
                                                          iVar8 = 3;
                                                        }
                                                        else {
                                                          iVar8 = _alemu_stricmp(pcVar4,"sub");
                                                          if (iVar8 != 0) {
                                                            piVar12 = g + 0x81d2;
                                                            ghidra_fa[0] = (void *)(pcVar4);
                                                            pcVar4 = "Invalid trans type: %s";
                                                            goto LAB_080bede5;
                                                          }
                                                          iVar8 = 2;
                                                        }
                                                      }
                                                    }
                                                  }
                                                  ConstExpI(piVar12,iVar8);
                                                  }
                                                  pbVar5 = (byte *)TPGetValue(param_1,"alpha");
                                                  if (pbVar5 == (byte *)0x0) {
                                                    return 1;
                                                  }
                                                  SCtrlReadExpList(pbVar5,"ii",param_3,&local_120,
                                                                   (int *)(param_2 + 0x24),
                                                                   (int *)(param_2 + 0x30));
                                                  }
                                                  else {
                                                    iVar8 = 0xc;
                                                    bVar14 = false;
                                                    pbVar5 = local_11c;
                                                    pbVar7 = (byte *)"screenbound";
                                                    do {
                                                      if (iVar8 == 0) break;
                                                      iVar8 = iVar8 + -1;
                                                      bVar15 = *pbVar5 < *pbVar7;
                                                      bVar14 = *pbVar5 == *pbVar7;
                                                      pbVar5 = pbVar5 + 1;
                                                      pbVar7 = pbVar7 + 1;
                                                    } while (bVar14);
                                                    bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                    if ((!bVar15 && !bVar14) == bVar15) {
                                                      *(undefined4 *)(param_2 + 0x10) = 0x32;
                                                      pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                      iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 
                                                  + 0x18),param_3,(undefined4 *)0x0,1);
                                                  if (iVar8 == 0) {
                                                    return 0;
                                                  }
                                                  ConstExpI((int *)(param_2 + 0x24),0);
                                                  ConstExpI((int *)(param_2 + 0x30),0);
                                                  pbVar5 = (byte *)TPGetValue(param_1,"movecamera");
                                                  SCtrlReadExpList(pbVar5,"ii",param_3,&local_120,
                                                                   (int *)(param_2 + 0x24),
                                                                   (int *)(param_2 + 0x30));
                                                  }
                                                  else {
                                                    iVar8 = 0xb;
                                                    bVar14 = false;
                                                    pbVar5 = local_11c;
                                                    pbVar7 = (byte *)"targetbind";
                                                    do {
                                                      if (iVar8 == 0) break;
                                                      iVar8 = iVar8 + -1;
                                                      bVar16 = *pbVar5 < *pbVar7;
                                                      bVar14 = *pbVar5 == *pbVar7;
                                                      pbVar5 = pbVar5 + 1;
                                                      pbVar7 = pbVar7 + 1;
                                                    } while (bVar14);
                                                    bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                    if ((!bVar16 && !bVar14) != bVar16) {
                                                      iVar8 = 0xd;
                                                      bVar14 = false;
                                                      pbVar5 = local_11c;
                                                      pbVar7 = (byte *)"bindtotarget";
                                                      do {
                                                        if (iVar8 == 0) break;
                                                        iVar8 = iVar8 + -1;
                                                        bVar15 = *pbVar5 < *pbVar7;
                                                        bVar14 = *pbVar5 == *pbVar7;
                                                        pbVar5 = pbVar5 + 1;
                                                        pbVar7 = pbVar7 + 1;
                                                      } while (bVar14);
                                                      bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                      if ((!bVar15 && !bVar14) == bVar15) {
                                                        *(undefined4 *)(param_2 + 0x10) = 0x47;
                                                        ConstExpI((int *)(param_2 + 0x18),1);
                                                        ConstExpI((int *)(param_2 + 0x30),-1);
                                                        ConstExpF((int *)(param_2 + 0x3c),
                                                                  -0x39001000);
                                                        ConstExpF((int *)(param_2 + 0x48),
                                                                  -0x39001000);
                                                        ConstExpF((int *)(param_2 + 0x54),0);
                                                        ConstExpI((int *)(param_2 + 0x24),0);
                                                        pbVar5 = (byte *)TPGetValue(param_1,"time");
                                                        iVar8 = InfixToPostfix(pbVar5,(int *)(
                                                  param_2 + 0x18),param_3,(undefined4 *)0x0,1);
                                                  if (iVar8 == 0) {
                                                    return 0;
                                                  }
                                                  pbVar5 = (byte *)TPGetValue(param_1,"id");
                                                  iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                       0x30),param_3
                                                                         ,(undefined4 *)0x0,1);
                                                  if (iVar8 == 0) {
                                                    return 0;
                                                  }
                                                  pbVar5 = (byte *)TPGetValue(param_1,"pos");
                                                  if (pbVar5 == (byte *)0x0) {
                                                    return 1;
                                                  }
                                                  pbVar5 = SCtrlReadExpList(pbVar5,"ff:,",param_3,
                                                                            &local_120,
                                                                            (int *)(param_2 + 0x3c),
                                                                            (int *)(param_2 + 0x48))
                                                  ;
                                                  bVar1 = *local_120;
                                                  if ((bVar1 != 0) && (bVar1 != 0x2c)) {
                                                    return 0;
                                                  }
                                                  if ((bVar1 == 0x2c) && ((int)pbVar5 < 2)) {
                                                    return 0;
                                                  }
                                                  if (*local_120 != 0) {
                                                    local_120 = local_120 + 1;
                                                  }
                                                  bVar1 = *(byte *)(__ctype_b + 1 +
                                                                   (char)*local_120 * 2);
                                                  while ((bVar1 & 0x20) != 0) {
                                                    local_120 = local_120 + 1;
                                                    bVar1 = *(byte *)(__ctype_b + 1 +
                                                                     (char)*local_120 * 2);
                                                  }
                                                  iVar8 = *(int *)(__ctype_tolower +
                                                                  (char)*local_120 * 4);
                                                  if (iVar8 == 0x68) {
                                                    iVar8 = 2;
                                                    piVar12 = (int *)(param_2 + 0x24);
                                                    goto LAB_080be8b2;
                                                  }
                                                  if (iVar8 < 0x69) {
                                                    if (iVar8 == 0) {
                                                      return 1;
                                                    }
                                                    if (iVar8 == 0x66) {
                                                      iVar8 = 0;
                                                      piVar12 = (int *)(param_2 + 0x24);
                                                      goto LAB_080be8b2;
                                                    }
                                                  }
                                                  else if (iVar8 == 0x6d) {
                                                    iVar8 = 1;
                                                    piVar12 = (int *)(param_2 + 0x24);
                                                    goto LAB_080be8b2;
                                                  }
                                                  piVar12 = g + 0x81d2;
                                                  ghidra_fa[0] = (void *)(local_120);
                                                  pcVar4 = "Invalid bind position: %s";
                                                  goto LAB_080bede5;
                                                  }
                                                  iVar8 = 0xc;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"targetstate";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                  if ((!bVar16 && !bVar14) == bVar16) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0x48;
                                                    pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                    if (pbVar5 == (byte *)0x0) {
                                                      return 0;
                                                    }
                                                    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                         0x18),
                                                                           param_3,(undefined4 *)0x0
                                                                           ,1);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    iVar8 = ItoP_TPConstI(param_1,"id",
                                                                          (int *)(param_2 + 0x30),
                                                                          param_3,-1);
                                                    goto LAB_080be81a;
                                                  }
                                                  iVar8 = 0xf;
                                                  uVar17 = 0;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"targetpoweradd";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    uVar17 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while ((bool)uVar17);
                                                  bVar14 = (!bVar15 && !(bool)uVar17) < bVar15;
                                                  if ((!bVar15 && !(bool)uVar17) == bVar15) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0x49;
                                                    pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                    if (pbVar5 == (byte *)0x0) {
                                                      return 0;
                                                    }
                                                    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                         0x18),
                                                                           param_3,(undefined4 *)0x0
                                                                           ,1);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    iVar8 = ItoP_TPConstI(param_1,"id",
                                                                          (int *)(param_2 + 0x30),
                                                                          param_3,-1);
                                                    goto LAB_080be81a;
                                                  }
                                                  iVar8 = 0xe;
                                                  bVar16 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"targetlifeadd";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar14 = *pbVar5 < *pbVar7;
                                                    bVar16 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar16);
                                                  bVar15 = (!bVar14 && !bVar16) < bVar14;
                                                  if ((!bVar14 && !bVar16) == bVar14) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0x4a;
                                                    pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                    if (pbVar5 == (byte *)0x0) {
                                                      return 0;
                                                    }
                                                    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                         0x18),
                                                                           param_3,(undefined4 *)0x0
                                                                           ,1);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    ConstExpI((int *)(param_2 + 0x24),1);
                                                    pbVar5 = (byte *)TPGetValue(param_1,"kill");
                                                    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                         0x24),
                                                                           param_3,(undefined4 *)0x0
                                                                           ,1);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    pbVar5 = (byte *)TPGetValue(param_1,"absolute");
                                                    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                         0x30),
                                                                           param_3,(undefined4 *)0x0
                                                                           ,1);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    iVar8 = ItoP_TPConstI(param_1,"id",
                                                                          (int *)(param_2 + 0x54),
                                                                          param_3,-1);
                                                    goto LAB_080be81a;
                                                  }
                                                  iVar8 = 0xd;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"targetvelset";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) == bVar15) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0x4b;
                                                    iVar8 = ItoP_TPConstF(param_1,"x",
                                                                          (int *)(param_2 + 0x3c),
                                                                          param_3,-0x39001000);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    iVar8 = ItoP_TPConstF(param_1,"y",
                                                                          (int *)(param_2 + 0x48),
                                                                          param_3,-0x39001000);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    iVar8 = ItoP_TPConstF(param_1,"z",
                                                                          (int *)(param_2 + 0x54),
                                                                          param_3,-0x39001000);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    iVar8 = ItoP_TPConstI(param_1,"id",
                                                                          (int *)(param_2 + 0x30),
                                                                          param_3,-1);
                                                    goto LAB_080be81a;
                                                  }
                                                  iVar8 = 0xd;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"targetveladd";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                  if ((!bVar16 && !bVar14) == bVar16) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0x4c;
                                                    iVar8 = ItoP_TPConstF(param_1,"x",
                                                                          (int *)(param_2 + 0x3c),
                                                                          param_3,-0x39001000);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    iVar8 = ItoP_TPConstF(param_1,"y",
                                                                          (int *)(param_2 + 0x48),
                                                                          param_3,-0x39001000);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    iVar8 = ItoP_TPConstF(param_1,"z",
                                                                          (int *)(param_2 + 0x54),
                                                                          param_3,-0x39001000);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    iVar8 = ItoP_TPConstI(param_1,"id",
                                                                          (int *)(param_2 + 0x30),
                                                                          param_3,-1);
                                                    goto LAB_080be81a;
                                                  }
                                                  iVar8 = 0xd;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"targetfacing";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) == bVar15) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0x4d;
                                                    pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                         0x18),
                                                                           param_3,(undefined4 *)0x0
                                                                           ,1);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    iVar8 = ItoP_TPConstI(param_1,"id",
                                                                          (int *)(param_2 + 0x30),
                                                                          param_3,-1);
                                                    goto LAB_080be81a;
                                                  }
                                                  iVar8 = 0xb;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"targetdrop";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                  if ((!bVar16 && !bVar14) == bVar16) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0x4e;
                                                    ConstExpI((int *)(param_2 + 0x18),-1);
                                                    piVar12 = (int *)(param_2 + 0x24);
                                                    ConstExpI(piVar12,1);
                                                    pbVar5 = (byte *)TPGetValue(param_1,"excludeID")
                                                    ;
                                                    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                         0x18),
                                                                           param_3,(undefined4 *)0x0
                                                                           ,1);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    pbVar5 = (byte *)TPGetValue(param_1,"keepone");
                                                    iVar8 = 1;
                                                  }
                                                  else {
                                                    iVar8 = 0xb;
                                                    bVar14 = false;
                                                    pbVar5 = local_11c;
                                                    pbVar7 = (byte *)"attackdist";
                                                    do {
                                                      if (iVar8 == 0) break;
                                                      iVar8 = iVar8 + -1;
                                                      bVar15 = *pbVar5 < *pbVar7;
                                                      bVar14 = *pbVar5 == *pbVar7;
                                                      pbVar5 = pbVar5 + 1;
                                                      pbVar7 = pbVar7 + 1;
                                                    } while (bVar14);
                                                    bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                    if ((!bVar15 && !bVar14) == bVar15) {
                                                      *(undefined4 *)(param_2 + 0x10) = 0x50;
                                                      pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                      if (pbVar5 == (byte *)0x0) {
                                                        return 0;
                                                      }
                                                      iVar8 = 1;
                                                      piVar12 = (int *)(param_2 + 0x18);
                                                    }
                                                    else {
                                                      iVar8 = 0xb;
                                                      bVar14 = false;
                                                      pbVar5 = local_11c;
                                                      pbVar7 = (byte *)"playerpush";
                                                      do {
                                                        if (iVar8 == 0) break;
                                                        iVar8 = iVar8 + -1;
                                                        bVar16 = *pbVar5 < *pbVar7;
                                                        bVar14 = *pbVar5 == *pbVar7;
                                                        pbVar5 = pbVar5 + 1;
                                                        pbVar7 = pbVar7 + 1;
                                                      } while (bVar14);
                                                      bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                      if ((!bVar16 && !bVar14) == bVar16) {
                                                        *(undefined4 *)(param_2 + 0x10) = 0x51;
                                                        pbVar5 = (byte *)TPGetValue(param_1,"value")
                                                        ;
                                                        if (pbVar5 == (byte *)0x0) {
                                                          return 0;
                                                        }
                                                        iVar8 = 1;
                                                        piVar12 = (int *)(param_2 + 0x18);
                                                      }
                                                      else {
                                                        iVar8 = 7;
                                                        bVar14 = false;
                                                        pbVar5 = local_11c;
                                                        pbVar7 = (byte *)(int)&DAT_0827b218;
                                                        do {
                                                          if (iVar8 == 0) break;
                                                          iVar8 = iVar8 + -1;
                                                          bVar15 = *pbVar5 < *pbVar7;
                                                          bVar14 = *pbVar5 == *pbVar7;
                                                          pbVar5 = pbVar5 + 1;
                                                          pbVar7 = pbVar7 + 1;
                                                        } while (bVar14);
                                                        bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                        if ((!bVar15 && !bVar14) != bVar15) {
                                                          iVar8 = 7;
                                                          bVar14 = false;
                                                          pbVar5 = local_11c;
                                                          pbVar7 = (byte *)(int)&DAT_0827b24e;
                                                          do {
                                                            bVar15 = bVar16;
                                                            if (iVar8 == 0) break;
                                                            iVar8 = iVar8 + -1;
                                                            bVar16 = *pbVar5 < *pbVar7;
                                                            bVar14 = *pbVar5 == *pbVar7;
                                                            pbVar5 = pbVar5 + 1;
                                                            pbVar7 = pbVar7 + 1;
                                                            bVar15 = bVar16;
                                                          } while (bVar14);
                                                          bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                          if ((!bVar15 && !bVar14) == bVar15)
                                                          goto LAB_080bd21b;
                                                          iVar8 = 0xc;
                                                          bVar14 = false;
                                                          pbVar5 = local_11c;
                                                          pbVar7 = (byte *)"varrangeset";
                                                          do {
                                                            if (iVar8 == 0) break;
                                                            iVar8 = iVar8 + -1;
                                                            bVar16 = *pbVar5 < *pbVar7;
                                                            bVar14 = *pbVar5 == *pbVar7;
                                                            pbVar5 = pbVar5 + 1;
                                                            pbVar7 = pbVar7 + 1;
                                                          } while (bVar14);
                                                          bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                          if ((!bVar16 && !bVar14) == bVar16) {
                                                            *(undefined4 *)(param_2 + 0x10) = 7;
                                                            pbVar5 = (byte *)TPGetValue(param_1,
                                                  "value");
                                                  if (pbVar5 == (byte *)0x0) {
                                                    pbVar5 = (byte *)TPGetValue(param_1,"fvalue");
                                                    if (pbVar5 == (byte *)0x0) {
                                                      sprintf((char *)(g + 0x81d2),
                                                              "VarRangeSet value not specified.");
                                                      ErrorExit();
                                                    }
                                                    iVar8 = 1;
                                                  }
                                                  else {
                                                    iVar8 = 0;
                                                  }
                                                  iVar10 = ItoP_TPConstI(param_1,"first",
                                                                         (int *)(param_2 + 0x18),
                                                                         param_3,0);
                                                  if (iVar10 == 0) {
                                                    return 0;
                                                  }
                                                  iVar10 = ItoP_TPConstI(param_1,"last",
                                                                         (int *)(param_2 + 0x24),
                                                                         param_3,((iVar8 == 0) - 1 &
                                                                                 0xffffffec) + 0x3b)
                                                  ;
                                                  if (iVar10 == 0) {
                                                    return 0;
                                                  }
                                                  iVar10 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                        0x30),
                                                                          param_3,(undefined4 *)0x0,
                                                                          (iVar8 != 0) + 1);
                                                  if (iVar10 == 0) {
                                                    return 0;
                                                  }
                                                  piVar12 = (int *)(param_2 + 0x3c);
                                                  goto LAB_080be8b2;
                                                  }
                                                  iVar8 = 10;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"varrandom";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) == bVar15) {
                                                    *(undefined4 *)(param_2 + 0x10) = 6;
                                                    pbVar5 = (byte *)TPGetValue(param_1,"v");
                                                    if (pbVar5 == (byte *)0x0) {
                                                      return 0;
                                                    }
                                                    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                         0x24),
                                                                           param_3,(undefined4 *)0x0
                                                                           ,1);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    piVar12 = (int *)(param_2 + 0x18);
                                                    ConstExpI(piVar12,0);
                                                    ConstExpI((int *)(param_2 + 0x30),1000);
                                                    pbVar5 = (byte *)TPGetValue(param_1,"range");
                                                    if (pbVar5 == (byte *)0x0) {
                                                      return 1;
                                                    }
                                                    pbVar5 = SCtrlReadExpList(pbVar5,"ii",param_3,
                                                                              &local_120,piVar12,
                                                                              (int *)(param_2 + 0x30
                                                                                     ));
                                                    if (*local_120 != 0) {
                                                      return 0;
                                                    }
                                                    if (pbVar5 == (byte *)0x0) {
                                                      return 0;
                                                    }
                                                    if (pbVar5 != (byte *)0x1) {
                                                      return 1;
                                                    }
                                                    *(undefined4 *)(param_2 + 0x30) =
                                                         *(undefined4 *)(param_2 + 0x18);
                                                    *(undefined4 *)(param_2 + 0x34) =
                                                         *(undefined4 *)(param_2 + 0x1c);
                                                    *(undefined4 *)(param_2 + 0x38) =
                                                         *(undefined4 *)(param_2 + 0x20);
                                                    iVar8 = 0;
                                                    goto LAB_080be8b2;
                                                  }
                                                  iVar8 = 7;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)(int)&DAT_08277eeb;
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                  if ((!bVar16 && !bVar14) == bVar16) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0x1c;
                                                    pbVar5 = (byte *)TPGetValue(param_1,"x");
                                                    if (pbVar5 != (byte *)0x0) {
                                                      ConstExpI((int *)(param_2 + 0x18),1);
                                                      iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 
                                                  + 0x3c),param_3,(undefined4 *)0x0,2);
                                                  if (iVar8 == 0) {
                                                    return 0;
                                                  }
                                                  }
                                                  pbVar5 = (byte *)TPGetValue(param_1,"y");
                                                  if (pbVar5 == (byte *)0x0) {
                                                    return 1;
                                                  }
                                                  ConstExpI((int *)(param_2 + 0x24),1);
                                                  iVar8 = 2;
                                                  piVar12 = (int *)(param_2 + 0x48);
                                                  goto LAB_080be815;
                                                  }
                                                  iVar8 = 9;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)(int)&DAT_0827aea3;
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) == bVar15) {
                                                    *(undefined4 *)(param_2 + 0x10) = 200;
                                                    piVar12 = (int *)ecalloc(1,0x40);
                                                    if (piVar12 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    iVar8 = SCtrlParseEnvShake(param_1,param_3,
                                                                               piVar12,&DAT_0827725f
                                                                              );
                                                    if (iVar8 == 0) {
                                                      free(piVar12);
                                                      strcat((char *)(g + 0x81d2),
                                                             "\nError parsing EnvShake");
                                                      return 0;
                                                    }
                                                    goto LAB_080be2cc;
                                                  }
                                                  iVar8 = 0xd;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"fallenvshake";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                  if ((!bVar16 && !bVar14) == bVar16) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0xc9;
                                                    return 1;
                                                  }
                                                  iVar8 = 9;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"envcolor";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) == bVar15) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0xca;
                                                    ConstExpI((int *)(param_2 + 0x3c),0xff);
                                                    ConstExpI((int *)(param_2 + 0x48),0xff);
                                                    ConstExpI((int *)(param_2 + 0x54),0xff);
                                                    pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                    if (pbVar5 != (byte *)0x0) {
                                                      pbVar5 = SCtrlReadExpList(pbVar5,"iii",param_3
                                                                                ,&local_120,
                                                                                (int *)(param_2 +
                                                                                       0x3c),
                                                                                (int *)(param_2 +
                                                                                       0x48),
                                                                                (int *)(param_2 +
                                                                                       0x54));
                                                      if (*local_120 != 0) {
                                                        return 0;
                                                      }
                                                      if (pbVar5 != (byte *)0x3) {
                                                        return 0;
                                                      }
                                                    }
                                                    ConstExpI((int *)(param_2 + 0x24),1);
                                                    piVar12 = (int *)(param_2 + 0x30);
                                                    ConstExpI(piVar12,0);
                                                    pbVar5 = (byte *)TPGetValue(param_1,"time");
                                                    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                         0x24),
                                                                           param_3,(undefined4 *)0x0
                                                                           ,1);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    pbVar5 = (byte *)TPGetValue(param_1,"under");
                                                    iVar8 = 1;
                                                    goto LAB_080be815;
                                                  }
                                                  iVar8 = 0xd;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"gamemakeanim";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                  if ((!bVar16 && !bVar14) == bVar16) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0xcb;
                                                    ConstExpI((int *)(param_2 + 0x18),0);
                                                    ConstExpI((int *)(param_2 + 0x24),0);
                                                    ConstExpF((int *)(param_2 + 0x3c),0);
                                                    ConstExpF((int *)(param_2 + 0x48),0);
                                                    pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                         0x18),
                                                                           param_3,(undefined4 *)0x0
                                                                           ,1);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    pbVar5 = (byte *)TPGetValue(param_1,"under");
                                                    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                         0x24),
                                                                           param_3,(undefined4 *)0x0
                                                                           ,1);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    pbVar5 = (byte *)TPGetValue(param_1,"pos");
                                                    if (pbVar5 != (byte *)0x0) {
                                                      pbVar5 = SCtrlReadExpList(pbVar5,"ff",param_3,
                                                                                &local_120,
                                                                                (int *)(param_2 +
                                                                                       0x3c),
                                                                                (int *)(param_2 +
                                                                                       0x48));
                                                      if (*local_120 != 0) {
                                                        return 0;
                                                      }
                                                      if (pbVar5 == (byte *)0x0) {
                                                        return 0;
                                                      }
                                                    }
                                                    pbVar5 = (byte *)TPGetValue(param_1,"random");
                                                    iVar8 = 1;
                                                    piVar12 = (int *)(param_2 + 0x30);
                                                    goto LAB_080be815;
                                                  }
                                                  iVar8 = 0xb;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)(int)&DAT_0827b7f3;
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) == bVar15) {
                                                    piVar12 = (int *)ecalloc(1,0x118);
                                                    if (piVar12 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    *(undefined4 *)(param_2 + 0x10) = 0xd2;
                                                    iVar8 = SCtrlParseAftImgParams
                                                                      (param_1,param_3,piVar12,
                                                                       &DAT_0827725f);
                                                    if (iVar8 == 0) {
                                                      free(piVar12);
                                                      strcat((char *)(g + 0x81d2),
                                                             "\nError parsing AfterImage");
                                                      return 0;
                                                    }
                                                    goto LAB_080be2cc;
                                                  }
                                                  iVar8 = 0xf;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)(int)&DAT_0827b156;
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                  if ((!bVar16 && !bVar14) == bVar16) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0xd3;
                                                    pbVar5 = (byte *)TPGetValue(param_1,"time");
                                                    if (pbVar5 == (byte *)0x0) {
                                                      pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                      iVar8 = 1;
                                                      piVar12 = (int *)(param_2 + 0x18);
                                                    }
                                                    else {
                                                      iVar8 = 1;
                                                      piVar12 = (int *)(param_2 + 0x18);
                                                    }
                                                    goto LAB_080be815;
                                                  }
                                                  iVar8 = 6;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)(int)&DAT_0827b086;
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) == bVar15) {
                                                    piVar12 = (int *)ecalloc(1,0x30);
                                                    if (piVar12 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    *(undefined4 *)(param_2 + 0x10) = 0xd4;
                                                    bVar14 = SCtrlParsePause(param_1,param_3,piVar12
                                                                            );
                                                    if (GHIDRA_ZEXT8(bVar14) == 0) {
                                                      free(piVar12);
                                                      strcat((char *)(g + 0x81d2),
                                                             "\nError parsing Pause");
                                                      return 0;
                                                    }
LAB_080be390:
                                                    *(int **)(param_2 + 0x60) = piVar12;
                                                    return 1;
                                                  }
                                                  iVar8 = 0xb;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"superpause";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                  if ((!bVar16 && !bVar14) == bVar16) {
                                                    piVar12 = (int *)ecalloc(1,0xa4);
                                                    if (piVar12 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    *(undefined4 *)(param_2 + 0x10) = 0xd6;
                                                    bVar14 = SCtrlParseSuperPause
                                                                       (param_1,param_3,piVar12);
                                                    if (GHIDRA_ZEXT8(bVar14) == 0) {
                                                      free(piVar12);
                                                      strcat((char *)(g + 0x81d2),
                                                             "\nError parsing SuperPause");
                                                      return 0;
                                                    }
                                                    goto LAB_080be390;
                                                  }
                                                  iVar8 = 9;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"makedust";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) == bVar15) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0xd7;
                                                    ConstExpI((int *)(param_2 + 0x30),3);
                                                    pbVar5 = (byte *)TPGetValue(param_1,"pos");
                                                    if (pbVar5 != (byte *)0x0) {
                                                      pbVar5 = SCtrlReadExpList(pbVar5,"ii",param_3,
                                                                                &local_120,
                                                                                (int *)(param_2 +
                                                                                       0x18),
                                                                                (int *)(param_2 +
                                                                                       0x24));
                                                      if (*local_120 != 0) {
                                                        return 0;
                                                      }
                                                      if (pbVar5 == (byte *)0x0) {
                                                        return 0;
                                                      }
                                                    }
                                                    pbVar5 = (byte *)TPGetValue(param_1,"pos2");
                                                    if (pbVar5 != (byte *)0x0) {
                                                      pbVar5 = SCtrlReadExpList(pbVar5,"ff",param_3,
                                                                                &local_120,
                                                                                (int *)(param_2 +
                                                                                       0x3c),
                                                                                (int *)(param_2 +
                                                                                       0x48));
                                                      if (*local_120 != 0) {
                                                        return 0;
                                                      }
                                                      if (pbVar5 == (byte *)0x0) {
                                                        return 0;
                                                      }
                                                      ConstExpF((int *)(param_2 + 0x54),0x3f800000);
                                                    }
                                                    pbVar5 = (byte *)TPGetValue(param_1,"spacing");
                                                    iVar8 = 1;
                                                    piVar12 = (int *)(param_2 + 0x30);
                                                    goto LAB_080be815;
                                                  }
                                                  iVar8 = 6;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = &DAT_0827af35;
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                  if ((!bVar16 && !bVar14) == bVar16) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0xd8;
                                                    piVar12 = (int *)ecalloc(1,0xa0);
                                                    if (piVar12 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    bVar14 = SCtrlParsePalFX(param_1,param_3,
                                                                             (int)piVar12,0);
                                                    if (GHIDRA_ZEXT8(bVar14) == 0) {
                                                      return 0;
                                                    }
                                                    *piVar12 = 0;
                                                    goto LAB_080be2cc;
                                                  }
                                                  iVar8 = 8;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = &DAT_0827af2a;
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) == bVar15) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0xd8;
                                                    piVar12 = (int *)ecalloc(1,0xa0);
                                                    if (piVar12 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    bVar14 = SCtrlParsePalFX(param_1,param_3,
                                                                             (int)piVar12,0);
                                                    if (GHIDRA_ZEXT8(bVar14) == 0) {
                                                      return 0;
                                                    }
                                                    *piVar12 = 1;
                                                    goto LAB_080be2cc;
                                                  }
                                                  iVar8 = 9;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = &DAT_0827af32;
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                  if ((!bVar16 && !bVar14) == bVar16) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0xd8;
                                                    piVar12 = (int *)ecalloc(1,0xa0);
                                                    if (piVar12 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    bVar14 = SCtrlParsePalFX(param_1,param_3,
                                                                             (int)piVar12,0);
                                                    if (GHIDRA_ZEXT8(bVar14) == 0) {
                                                      return 0;
                                                    }
                                                    *piVar12 = 2;
                                                    goto LAB_080be2cc;
                                                  }
                                                  iVar8 = 7;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)(int)&DAT_0827857c;
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) == bVar15) {
                                                    piVar12 = (int *)ecalloc(1,0x168);
                                                    if (piVar12 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    *(undefined4 *)(param_2 + 0x10) = 0xdc;
                                                    iVar8 = SCtrlParseExplod(param_1,param_3,piVar12
                                                                             ,0);
joined_r0x080be2c6:
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
LAB_080be2cc:
                                                    *(int **)(param_2 + 0x60) = piVar12;
                                                    return 1;
                                                  }
                                                  iVar8 = 0xd;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"removeexplod";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                  if ((!bVar16 && !bVar14) == bVar16) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0xdd;
                                                    piVar12 = (int *)(param_2 + 0x18);
                                                    ConstExpI(piVar12,-1);
                                                    pbVar5 = (byte *)TPGetValue(param_1,"id");
                                                    iVar8 = 1;
                                                    goto LAB_080be815;
                                                  }
                                                  iVar8 = 0xf;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)(int)&DAT_0827b1de;
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) == bVar15) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0xde;
                                                    ConstExpI((int *)(param_2 + 0x18),-1);
                                                    piVar12 = (int *)(param_2 + 0x24);
                                                    ConstExpI(piVar12,1);
                                                    pbVar5 = (byte *)TPGetValue(param_1,"id");
                                                    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                         0x18),
                                                                           param_3,(undefined4 *)0x0
                                                                           ,1);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    pbVar5 = (byte *)TPGetValue(param_1,"time");
                                                    if (pbVar5 == (byte *)0x0) {
                                                      pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                    }
                                                    iVar8 = 1;
                                                    goto LAB_080be815;
                                                  }
                                                  iVar8 = 0xd;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"modifyexplod";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                  if ((!bVar16 && !bVar14) == bVar16) {
                                                    piVar12 = (int *)ecalloc(1,0x168);
                                                    if (piVar12 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    *(undefined4 *)(param_2 + 0x10) = 0xdf;
                                                    iVar8 = SCtrlParseExplod(param_1,param_3,piVar12
                                                                             ,1);
                                                    goto joined_r0x080be2c6;
                                                  }
                                                  iVar8 = 0xe;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"forcefeedback";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) == bVar15) {
LAB_080bedbd:
                                                    *(undefined4 *)(param_2 + 0x10) = 0;
                                                    return 1;
                                                  }
                                                  iVar8 = 7;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)(int)&DAT_0827882d;
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                  if ((!bVar16 && !bVar14) == bVar16) {
                                                    *(undefined4 *)(param_2 + 0x10) = 300;
                                                    piVar12 = (int *)ecalloc(1,0x140);
                                                    if (piVar12 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    bVar14 = SCtrlParseHelper(param_1,param_3,
                                                                              (char *)piVar12);
                                                    if (GHIDRA_ZEXT8(bVar14) == 0) {
                                                      free(piVar12);
                                                      strcat((char *)(g + 0x81d2),
                                                             "\nError parsing Helper");
                                                      return 0;
                                                    }
                                                    goto LAB_080be390;
                                                  }
                                                  iVar8 = 0xc;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"destroyself";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) == bVar15) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0x12d;
                                                    return 1;
                                                  }
                                                  iVar8 = 0xd;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)(int)&DAT_0827b212;
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                  if ((!bVar16 && !bVar14) == bVar16) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0x130;
                                                    pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                    if (pbVar5 == (byte *)0x0) {
                                                      pcVar4 = (char *)TPAccessFirstLine(param_1);
                                                      while (((iVar8 = strimatchlen((int)pcVar4,
                                                                                    (int)&DAT_0827c60a,3),
                                                              iVar8 == 0 &&
                                                              (iVar8 = strimatchlen((int)pcVar4,
                                                                                    (int)&DAT_0827ae57,4),
                                                              iVar8 == 0)) &&
                                                             (pcVar4 != (char *)0x0))) {
                                                        pcVar4 = (char *)TPAccessNextLine(param_1);
                                                      }
                                                      if (pcVar4 == (char *)0x0) {
                                                        return 0;
                                                      }
                                                      uVar6 = (uint)(*pcVar4 != 'v');
                                                      ConstExpI((int *)(param_2 + 0x30),uVar6);
                                                      pcVar13 = pcVar4 + uVar6 + 3;
                                                      bVar1 = *(byte *)(__ctype_b + 1 +
                                                                       pcVar4[uVar6 + 3] * 2);
                                                      while ((bVar1 & 0x20) != 0) {
                                                        pcVar13 = pcVar13 + 1;
                                                        bVar1 = *(byte *)(__ctype_b + 1 +
                                                                         *pcVar13 * 2);
                                                      }
                                                      if (*pcVar13 != '(') {
                                                        return 0;
                                                      }
                                                      iVar8 = InfixToPostfix((byte *)(pcVar13 + 1),
                                                                             (int *)(param_2 + 0x24)
                                                                             ,param_3,&local_120,1);
                                                      if (iVar8 == 0) {
                                                        return 0;
                                                      }
                                                      if (*local_120 != 0x29) {
                                                        return 0;
                                                      }
                                                      pbVar5 = local_120 + 1;
                                                      bVar1 = 0;
                                                      if (local_120[1] != 0) {
                                                        if (local_120[1] == 0x3d) {
                                                          bVar1 = 0x3d;
                                                        }
                                                        else {
                                                          do {
                                                            pbVar5 = pbVar5 + 1;
                                                            bVar1 = *pbVar5;
                                                            if (bVar1 == 0) break;
                                                          } while (bVar1 != 0x3d);
                                                        }
                                                      }
                                                      if (bVar1 != 0x3d) {
                                                        return 0;
                                                      }
                                                      pbVar5 = pbVar5 + 1;
                                                      iVar8 = uVar6 + 1;
                                                      piVar12 = (int *)(param_2 + 0x18);
                                                    }
                                                    else {
                                                      local_120 = (byte *)TPGetValue(param_1,"v");
                                                      if (local_120 == (byte *)0x0) {
                                                        local_120 = (byte *)TPGetValue(param_1,"fv")
                                                        ;
                                                        if (local_120 == (byte *)0x0) {
                                                          return 1;
                                                        }
                                                        iVar8 = InfixToPostfix(local_120,
                                                                               (int *)(param_2 +
                                                                                      0x24),param_3,
                                                                               (undefined4 *)0x0,1);
                                                        if (iVar8 == 0) {
                                                          return 0;
                                                        }
                                                        iVar8 = InfixToPostfix(pbVar5,(int *)(
                                                  param_2 + 0x18),param_3,(undefined4 *)0x0,2);
                                                  goto joined_r0x080be616;
                                                  }
                                                  iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                       0x18),param_3
                                                                         ,(undefined4 *)0x0,1);
                                                  pbVar5 = local_120;
joined_r0x080be7f4:
                                                  if (iVar8 == 0) {
                                                    return 0;
                                                  }
                                                  iVar8 = 1;
                                                  piVar12 = (int *)(param_2 + 0x24);
                                                  local_120 = pbVar5;
                                                  }
                                                  goto LAB_080be815;
                                                  }
                                                  iVar8 = 0xd;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)(int)&DAT_0827b248;
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) != bVar15) {
                                                    iVar8 = 0xd;
                                                    bVar14 = false;
                                                    pbVar5 = local_11c;
                                                    pbVar7 = (byte *)(int)&DAT_0827b263;
                                                    do {
                                                      if (iVar8 == 0) break;
                                                      iVar8 = iVar8 + -1;
                                                      bVar16 = *pbVar5 < *pbVar7;
                                                      bVar14 = *pbVar5 == *pbVar7;
                                                      pbVar5 = pbVar5 + 1;
                                                      pbVar7 = pbVar7 + 1;
                                                    } while (bVar14);
                                                    bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                    if ((!bVar16 && !bVar14) == bVar16) {
                                                      *(undefined4 *)(param_2 + 0x10) = 0x140;
                                                      ConstExpI((int *)(param_2 + 0x18),1);
                                                      pbVar5 = (byte *)TPGetValue(param_1,"time");
                                                      iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 
                                                  + 0x18),param_3,(undefined4 *)0x0,1);
                                                  if (iVar8 == 0) {
                                                    return 0;
                                                  }
                                                  pbVar5 = (byte *)TPGetValue(param_1,"facing");
                                                  iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                       0x24),param_3
                                                                         ,(undefined4 *)0x0,1);
                                                  if (iVar8 == 0) {
                                                    return 0;
                                                  }
                                                  pbVar5 = (byte *)TPGetValue(param_1,"pos");
                                                  if (pbVar5 == (byte *)0x0) {
                                                    return 1;
                                                  }
                                                  pbVar5 = SCtrlReadExpList(pbVar5,"fff",param_3,
                                                                            &local_120,
                                                                            (int *)(param_2 + 0x3c),
                                                                            (int *)(param_2 + 0x48),
                                                                            (int *)(param_2 + 0x54))
                                                  ;
                                                  if (pbVar5 == (byte *)0x0) {
                                                    return 0;
                                                  }
                                                  bVar1 = *local_120;
                                                  goto joined_r0x080beb19;
                                                  }
                                                  iVar8 = 0xb;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)(int)&DAT_0827b27c;
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar15 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                  if ((!bVar15 && !bVar14) == bVar15) {
                                                    *(undefined4 *)(param_2 + 0x10) = 0x141;
                                                    ConstExpI((int *)(param_2 + 0x18),1);
                                                    pbVar5 = (byte *)TPGetValue(param_1,"time");
                                                    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                         0x18),
                                                                           param_3,(undefined4 *)0x0
                                                                           ,1);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    pbVar5 = (byte *)TPGetValue(param_1,"facing");
                                                    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                         0x24),
                                                                           param_3,(undefined4 *)0x0
                                                                           ,1);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    pbVar5 = (byte *)TPGetValue(param_1,"pos");
                                                    if (pbVar5 == (byte *)0x0) {
                                                      return 1;
                                                    }
                                                    pbVar5 = SCtrlReadExpList(pbVar5,"fff",param_3,
                                                                              &local_120,
                                                                              (int *)(param_2 + 0x3c
                                                                                     ),(int *)(
                                                  param_2 + 0x48),(int *)(param_2 + 0x54));
                                                  if (pbVar5 == (byte *)0x0) {
                                                    return 0;
                                                  }
                                                  bVar1 = *local_120;
                                                  goto joined_r0x080beb19;
                                                  }
                                                  iVar8 = 0x13;
                                                  bVar14 = false;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)"displaytoclipboard";
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                  if ((!bVar16 && !bVar14) == bVar16) {
LAB_080beb5d:
                                                    *(uint *)(param_2 + 0x10) =
                                                         (local_11c[0] != 100) + 0x136;
                                                    pcVar4 = TPGetValue(param_1,"text");
                                                    if (pcVar4 == (char *)0x0) {
                                                      ghidra_fa[0] = (void *)(local_11c);
                                                      pcVar4 = "Text not specified for %s.";
                                                    }
                                                    else {
                                                      if (*pcVar4 != '\"') {
                                                        piVar12 = g + 0x81d2;
                                                        pcVar4 = "Message text not quote-delimited."
                                                        ;
                                                        goto LAB_080bede5;
                                                      }
                                                      cVar2 = pcVar4[1];
                                                      pbVar5 = (byte *)0x0;
                                                      sVar11 = 1;
                                                      cVar3 = '\0';
                                                      if ((cVar2 != '\0') &&
                                                         (cVar3 = '\"', cVar2 != '\"')) {
                                                        pbVar5 = (byte *)0x0;
                                                        do {
                                                          if (cVar2 == '%') {
                                                            if (pcVar4[sVar11 + 1] == '%') {
                                                              sVar11 = sVar11 + 1;
                                                              cVar2 = pcVar4[sVar11];
                                                            }
                                                            else {
                                                              pbVar5 = pbVar5 + 1;
                                                            }
                                                          }
                                                          if ((cVar2 == '\\') &&
                                                             (pcVar4[sVar11 + 1] == '\"')) {
                                                            sVar11 = sVar11 + 1;
                                                          }
                                                          sVar11 = sVar11 + 1;
                                                          cVar2 = pcVar4[sVar11];
                                                          cVar3 = cVar2;
                                                        } while ((cVar2 != '\0') && (cVar2 != '\"'))
                                                        ;
                                                      }
                                                      if (cVar3 == '\0') {
                                                        piVar12 = g + 0x81d2;
                                                        pcVar4 = "Message text not quote-delimited."
                                                        ;
                                                        goto LAB_080bede5;
                                                      }
                                                      if ((int)pbVar5 < 6) {
                                                        ConstExpI((int *)(param_2 + 0x54),
                                                                  (int)pbVar5);
                                                        iVar8 = ecalloc(1,sVar11);
                                                        *(int *)(param_2 + 0x60) = iVar8;
                                                        if (iVar8 == 0) {
                                                          return 0;
                                                        }
                                                        iVar9 = 1;
                                                        iVar10 = 0;
                                                        if (1 < (int)sVar11) {
LAB_080bec80:
                                                          cVar2 = pcVar4[iVar9];
                                                          if (cVar2 == '\\') {
                                                            iVar9 = iVar9 + 1;
                                                            cVar2 = pcVar4[iVar9];
                                                            if (cVar2 == 'n') {
                                                              *(undefined1 *)(iVar10 + iVar8) = 10;
                                                              goto LAB_080becd3;
                                                            }
                                                            if ('n' < cVar2) {
                                                              if (cVar2 == 't') {
                                                                *(undefined1 *)(iVar10 + iVar8) = 9;
                                                                goto LAB_080becd3;
                                                              }
                                                              goto LAB_080becd0;
                                                            }
                                                            if (cVar2 == '\0') {
                                                              piVar12 = g + 0x81d2;
                                                              pcVar4 = 
                                                  "Unterminated backslash escape sequence";
                                                  goto LAB_080bede5;
                                                  }
                                                  }
LAB_080becd0:
                                                  *(char *)(iVar10 + iVar8) = cVar2;
LAB_080becd3:
                                                  iVar10 = iVar10 + 1;
                                                  iVar9 = iVar9 + 1;
                                                  if ((int)sVar11 <= iVar9) goto LAB_080becd9;
                                                  goto LAB_080bec80;
                                                  }
LAB_080becd9:
                                                  *(undefined1 *)(iVar10 + iVar8) = 0;
                                                  pbVar7 = (byte *)TPGetValue(param_1,"params");
                                                  if (pbVar7 == (byte *)0x0) {
                                                    return 1;
                                                  }
                                                  pbVar7 = SCtrlReadExpList(pbVar7,"nnnnn",param_3,
                                                                            &local_120,
                                                                            (int *)(param_2 + 0x18),
                                                                            (int *)(param_2 + 0x24),
                                                                            (int *)(param_2 + 0x30),
                                                                            (int *)(param_2 + 0x3c),
                                                                            (int *)(param_2 + 0x48))
                                                  ;
                                                  if (pbVar7 == (byte *)0x0) {
                                                    return 0;
                                                  }
                                                  if (pbVar7 != pbVar5) {
                                                    return 0;
                                                  }
                                                  goto LAB_080bed65;
                                                  }
                                                  ghidra_fa[0] = (void *)(local_11c);
                                                  pcVar4 = "More than 5 parameters to %s.";
                                                  }
                                                  }
                                                  else {
                                                    iVar8 = 0x12;
                                                    bVar14 = false;
                                                    pbVar5 = local_11c;
                                                    pbVar7 = (byte *)"appendtoclipboard";
                                                    do {
                                                      if (iVar8 == 0) break;
                                                      iVar8 = iVar8 + -1;
                                                      bVar15 = *pbVar5 < *pbVar7;
                                                      bVar14 = *pbVar5 == *pbVar7;
                                                      pbVar5 = pbVar5 + 1;
                                                      pbVar7 = pbVar7 + 1;
                                                    } while (bVar14);
                                                    bVar16 = (!bVar15 && !bVar14) < bVar15;
                                                    if ((!bVar15 && !bVar14) == bVar15)
                                                    goto LAB_080beb5d;
                                                    iVar8 = 0xf;
                                                    bVar14 = false;
                                                    pbVar5 = local_11c;
                                                    pbVar7 = (byte *)"clearclipboard";
                                                    do {
                                                      if (iVar8 == 0) break;
                                                      iVar8 = iVar8 + -1;
                                                      bVar16 = *pbVar5 < *pbVar7;
                                                      bVar14 = *pbVar5 == *pbVar7;
                                                      pbVar5 = pbVar5 + 1;
                                                      pbVar7 = pbVar7 + 1;
                                                    } while (bVar14);
                                                    bVar15 = (!bVar16 && !bVar14) < bVar16;
                                                    if ((!bVar16 && !bVar14) == bVar16) {
                                                      *(undefined4 *)(param_2 + 0x10) = 0x138;
                                                      return 1;
                                                    }
                                                    iVar8 = 5;
                                                    bVar14 = false;
                                                    pbVar5 = local_11c;
                                                    pbVar7 = (byte *)(int)&DAT_082827b2;
                                                    do {
                                                      if (iVar8 == 0) break;
                                                      iVar8 = iVar8 + -1;
                                                      bVar15 = *pbVar5 < *pbVar7;
                                                      bVar14 = *pbVar5 == *pbVar7;
                                                      pbVar5 = pbVar5 + 1;
                                                      pbVar7 = pbVar7 + 1;
                                                    } while (bVar14);
                                                    if ((!bVar15 && !bVar14) == bVar15)
                                                    goto LAB_080bedbd;
                                                    ghidra_fa[0] = (void *)(local_11c);
                                                    pcVar4 = "Not a valid elem type: %s";
                                                  }
                                                  piVar12 = g + 0x81d2;
LAB_080bede5:
                                                  sprintf((char *)piVar12,pcVar4,ghidra_fa[0]);
                                                  return 0;
                                                  }
                                                  *(undefined4 *)(param_2 + 0x10) = 0x131;
                                                  pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                  if (pbVar5 == (byte *)0x0) {
                                                    pcVar4 = (char *)TPAccessFirstLine(param_1);
                                                    while (((iVar8 = strimatchlen((int)pcVar4,
                                                                                  (int)&DAT_0827c60a,3),
                                                            iVar8 == 0 &&
                                                            (iVar8 = strimatchlen((int)pcVar4,
                                                                                  (int)&DAT_0827ae57,4),
                                                            iVar8 == 0)) && (pcVar4 != (char *)0x0))
                                                          ) {
                                                      pcVar4 = (char *)TPAccessNextLine(param_1);
                                                    }
                                                    if (pcVar4 == (char *)0x0) {
                                                      return 0;
                                                    }
                                                    uVar6 = (uint)(*pcVar4 != 'v');
                                                    ConstExpI((int *)(param_2 + 0x30),uVar6);
                                                    pcVar13 = pcVar4 + uVar6 + 3;
                                                    bVar1 = *(byte *)(__ctype_b + 1 +
                                                                     pcVar4[uVar6 + 3] * 2);
                                                    while ((bVar1 & 0x20) != 0) {
                                                      pcVar13 = pcVar13 + 1;
                                                      bVar1 = *(byte *)(__ctype_b + 1 + *pcVar13 * 2
                                                                       );
                                                    }
                                                    if (*pcVar13 != '(') {
                                                      return 0;
                                                    }
                                                    iVar8 = InfixToPostfix((byte *)(pcVar13 + 1),
                                                                           (int *)(param_2 + 0x24),
                                                                           param_3,&local_120,1);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    if (*local_120 != 0x29) {
                                                      return 0;
                                                    }
                                                    pbVar5 = local_120 + 1;
                                                    bVar1 = 0;
                                                    if (local_120[1] != 0) {
                                                      if (local_120[1] == 0x3d) {
                                                        bVar1 = 0x3d;
                                                      }
                                                      else {
                                                        do {
                                                          pbVar5 = pbVar5 + 1;
                                                          bVar1 = *pbVar5;
                                                          if (bVar1 == 0) break;
                                                        } while (bVar1 != 0x3d);
                                                      }
                                                    }
                                                    if (bVar1 != 0x3d) {
                                                      return 0;
                                                    }
                                                    pbVar5 = pbVar5 + 1;
                                                    iVar8 = uVar6 + 1;
                                                    piVar12 = (int *)(param_2 + 0x18);
                                                    goto LAB_080be815;
                                                  }
                                                  local_120 = (byte *)TPGetValue(param_1,"v");
                                                  if (local_120 != (byte *)0x0) {
                                                    iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                         0x18),
                                                                           param_3,(undefined4 *)0x0
                                                                           ,1);
                                                    pbVar5 = local_120;
                                                    goto joined_r0x080be7f4;
                                                  }
                                                  local_120 = (byte *)TPGetValue(param_1,"fv");
                                                  if (local_120 == (byte *)0x0) {
                                                    return 1;
                                                  }
                                                  iVar8 = InfixToPostfix(local_120,
                                                                         (int *)(param_2 + 0x24),
                                                                         param_3,(undefined4 *)0x0,1
                                                                        );
                                                  if (iVar8 == 0) {
                                                    return 0;
                                                  }
                                                  iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                       0x18),param_3
                                                                         ,(undefined4 *)0x0,2);
joined_r0x080be616:
                                                  if (iVar8 == 0) {
                                                    return 0;
                                                  }
                                                  goto LAB_080be8a5;
                                                  }
LAB_080bd21b:
                                                  bVar14 = true;
                                                  iVar8 = 7;
                                                  pbVar5 = local_11c;
                                                  pbVar7 = (byte *)(int)&DAT_0827b218;
                                                  do {
                                                    if (iVar8 == 0) break;
                                                    iVar8 = iVar8 + -1;
                                                    bVar16 = *pbVar5 < *pbVar7;
                                                    bVar14 = *pbVar5 == *pbVar7;
                                                    pbVar5 = pbVar5 + 1;
                                                    pbVar7 = pbVar7 + 1;
                                                  } while (bVar14);
                                                  *(uint *)(param_2 + 0x10) =
                                                       ((!bVar16 && !bVar14) != bVar16) + 4;
                                                  pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                  if (pbVar5 == (byte *)0x0) {
                                                    pcVar4 = (char *)TPAccessFirstLine(param_1);
                                                    while ((((iVar8 = strimatchlen((int)pcVar4,
                                                                                   (int)&DAT_0827c60a,3),
                                                             iVar8 == 0 &&
                                                             (iVar8 = strimatchlen((int)pcVar4,
                                                                                   (int)&DAT_0827ae57,4),
                                                             iVar8 == 0)) &&
                                                            (iVar8 = strimatchlen((int)pcVar4,
                                                                                  (int)&DAT_0827ae4d,6),
                                                            iVar8 == 0)) &&
                                                           ((iVar8 = strimatchlen((int)pcVar4,
                                                                                  (int)&DAT_0827ae54,7),
                                                            iVar8 == 0 && (pcVar4 != (char *)0x0))))
                                                          ) {
                                                      pcVar4 = (char *)TPAccessNextLine(param_1);
                                                    }
                                                    if (pcVar4 == (char *)0x0) {
                                                      return 0;
                                                    }
                                                    iVar10 = 0;
                                                    if ((*pcVar4 != 'v') &&
                                                       (iVar10 = 1, *pcVar4 != 'f')) {
                                                      iVar10 = (pcVar4[3] != 'v') + 3;
                                                    }
                                                    pcVar13 = pcVar4 + iVar10 + 3;
                                                    ConstExpI((int *)(param_2 + 0x30),iVar10);
                                                    bVar1 = *(byte *)(__ctype_b + 1 +
                                                                     pcVar4[iVar10 + 3] * 2);
                                                    while ((bVar1 & 0x20) != 0) {
                                                      pcVar13 = pcVar13 + 1;
                                                      bVar1 = *(byte *)(__ctype_b + 1 + *pcVar13 * 2
                                                                       );
                                                    }
                                                    if (*pcVar13 != '(') {
                                                      return 0;
                                                    }
                                                    iVar8 = InfixToPostfix((byte *)(pcVar13 + 1),
                                                                           (int *)(param_2 + 0x24),
                                                                           param_3,&local_120,1);
                                                    if (iVar8 == 0) {
                                                      return 0;
                                                    }
                                                    if (*local_120 != 0x29) {
                                                      return 0;
                                                    }
                                                    pbVar5 = local_120 + 1;
                                                    bVar1 = 0;
                                                    if (local_120[1] != 0) {
                                                      if (local_120[1] == 0x3d) {
                                                        bVar1 = 0x3d;
                                                      }
                                                      else {
                                                        do {
                                                          pbVar5 = pbVar5 + 1;
                                                          bVar1 = *pbVar5;
                                                          if (bVar1 == 0) break;
                                                        } while (bVar1 != 0x3d);
                                                      }
                                                    }
                                                    if (bVar1 != 0x3d) {
                                                      return 0;
                                                    }
                                                    if ((iVar10 == 1) || (iVar8 = 1, iVar10 == 4)) {
                                                      iVar8 = 2;
                                                    }
                                                    piVar12 = (int *)(param_2 + 0x18);
                                                    pbVar5 = pbVar5 + 1;
                                                  }
                                                  else {
                                                    local_120 = (byte *)TPGetValue(param_1,"v");
                                                    if (local_120 == (byte *)0x0) {
                                                      local_120 = (byte *)TPGetValue(param_1,"fv");
                                                      if (local_120 == (byte *)0x0) {
                                                        return 1;
                                                      }
                                                      iVar8 = InfixToPostfix(local_120,
                                                                             (int *)(param_2 + 0x24)
                                                                             ,param_3,(undefined4 *)
                                                                                      0x0,1);
                                                      if (iVar8 == 0) {
                                                        return 0;
                                                      }
                                                      iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 
                                                  + 0x18),param_3,(undefined4 *)0x0,2);
                                                  goto joined_r0x080be616;
                                                  }
                                                  iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                       0x18),param_3
                                                                         ,(undefined4 *)0x0,1);
                                                  if (iVar8 == 0) {
                                                    return 0;
                                                  }
                                                  iVar8 = 1;
                                                  piVar12 = (int *)(param_2 + 0x24);
                                                  pbVar5 = local_120;
                                                  }
                                                  }
                                                  }
                                                  }
                                                  goto LAB_080be815;
                                                  }
                                                  *(undefined4 *)(param_2 + 0x10) = 0x46;
                                                  ConstExpI((int *)(param_2 + 0x18),1);
                                                  ConstExpI((int *)(param_2 + 0x30),-1);
                                                  ConstExpF((int *)(param_2 + 0x3c),-0x39001000);
                                                  ConstExpF((int *)(param_2 + 0x48),-0x39001000);
                                                  ConstExpF((int *)(param_2 + 0x54),0);
                                                  pbVar5 = (byte *)TPGetValue(param_1,"time");
                                                  iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                       0x18),param_3
                                                                         ,(undefined4 *)0x0,1);
                                                  if (iVar8 == 0) {
                                                    return 0;
                                                  }
                                                  pbVar5 = (byte *)TPGetValue(param_1,"id");
                                                  iVar8 = InfixToPostfix(pbVar5,(int *)(param_2 +
                                                                                       0x30),param_3
                                                                         ,(undefined4 *)0x0,1);
                                                  if (iVar8 == 0) {
                                                    return 0;
                                                  }
                                                  pbVar5 = (byte *)TPGetValue(param_1,"pos");
                                                  SCtrlReadExpList(pbVar5,"ff",param_3,&local_120,
                                                                   (int *)(param_2 + 0x3c),
                                                                   (int *)(param_2 + 0x48));
                                                  }
joined_r0x080bb972:
                                                  if (pbVar5 == (byte *)0x0) {
                                                    return 1;
                                                  }
                                                  }
LAB_080bed65:
                                                  bVar1 = *local_120;
joined_r0x080beb19:
                                                  if (bVar1 != 0) {
                                                    return 0;
                                                  }
                                                  return 1;
                                                  }
                                                  *(undefined4 *)(param_2 + 0x10) = 0x3f;
                                                  pbVar5 = (byte *)TPGetValue(param_1,"value");
                                                  iVar8 = 2;
                                                  piVar12 = (int *)(param_2 + 0x3c);
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
LAB_080be815:
  iVar8 = InfixToPostfix(pbVar5,piVar12,param_3,(undefined4 *)0x0,iVar8);
LAB_080be81a:
  if (iVar8 == 0) {
    return 0;
  }
  return 1;
}
#undef local_128
#undef local_124
#undef local_120
#undef local_11c

/* SCtrlParseElem @ 0x080bee10, 947 bytes
 * FIXUP: frame emulation: 9 stack locals placed at their original offsets in a 0xf0-byte frame (a local's address escapes, see apply_frame_emulation) */
bool SCtrlParseElem(int param_1,int *param_2,undefined4 param_3,int param_4)

{
  char *pcVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 uVar5;
  undefined4 extraout_EDX_00;
  int iVar6;
  unsigned char ghidra_frame[0xf0] __attribute__((aligned(16)));
#define local_e8 (*(int *)(ghidra_frame + 0x8))
#define local_e4 (*(int *)(ghidra_frame + 0xc))
#define local_e0 (*(int *)(ghidra_frame + 0x10))
#define local_dc (*(char (*)[32])(ghidra_frame + 0x14))
#define local_bc (*(char (*)[32])(ghidra_frame + 0x34))
#define local_9c (*(int (*)[4])(ghidra_frame + 0x54))
#define local_8c (*(undefined4 **)(ghidra_frame + 0x64))
#define local_88 (*(int *)(ghidra_frame + 0x68))
#define local_84 (*(uint (*)[29])(ghidra_frame + 0x6c))
  
  local_e0 = 0;
  local_e8 = 0;
  memset(&local_8c,0,100);
  TPGroupReset(param_1);
  pcVar1 = TPGetValue(param_1,"triggerall");
  if (pcVar1 != (char *)0x0) {
    local_e8 = 1;
    while (pcVar1 = TPGetValueNext(param_1,"triggerall"), pcVar1 != (char *)0x0) {
      local_e8 = local_e8 + 1;
    }
  }
  memcpy(local_bc,"trigger1",9);
  TPGroupReset(param_1);
  iVar4 = 0;
  while (pcVar1 = TPGetValue(param_1,local_bc), pcVar1 != (char *)0x0) {
    do {
      local_e0 = local_e0 + 1;
      pcVar1 = TPGetValueNext(param_1,local_bc);
    } while (pcVar1 != (char *)0x0);
    sprintf(local_bc,"trigger%i",iVar4 + 2,extraout_ECX);
    iVar4 = iVar4 + 1;
  }
  if (local_e0 == 0) {
    sprintf((char *)(g + 0x81d2),"Need at least 1 trigger",iVar4,iVar4);
  }
  else {
    local_8c = ArrayNew(local_e0 + local_e8,0xc,0);
    if (local_8c != (undefined4 *)0x0) {
      iVar6 = 0;
      local_e4 = 0;
      local_88 = iVar4;
      TPGroupReset(param_1);
      local_9c[0] = 0;
      local_9c[1] = 0;
      local_9c[2] = 0;
      if (0 < local_e0) {
        uVar5 = extraout_EDX;
        do {
          sprintf(local_bc,"trigger%i",local_e4 + 1,uVar5);
          pbVar2 = (byte *)TPGetValue(param_1,local_bc);
          iVar4 = 0;
          do {
            iVar3 = InfixToPostfix(pbVar2,local_9c,param_4,(undefined4 *)0x0,0);
            if (iVar3 == 0) {
              pcVar1 = local_dc;
              sprintf(pcVar1,", %i",iVar4 + 1,0);
              strcat((char *)(g + 0x81d2),"\nError parsing ");
              strcat((char *)(g + 0x81d2),local_bc);
              goto LAB_080bf182;
            }
            iVar6 = iVar6 + 1;
            ArrayAdd((int)local_8c,local_9c,local_e4,iVar4);
            pbVar2 = (byte *)TPGetValueNext(param_1,local_bc);
            iVar4 = iVar4 + 1;
          } while (pbVar2 != (byte *)0x0);
          local_e4 = local_e4 + 1;
          uVar5 = extraout_EDX_00;
        } while (iVar6 < local_e0);
      }
      if (0 < local_e8) {
        TPGroupReset(param_1);
        pbVar2 = (byte *)TPGetValue(param_1,"triggerall");
        if (pbVar2 != (byte *)0x0) {
          iVar4 = 0;
          do {
            iVar6 = InfixToPostfix(pbVar2,local_9c,param_4,(undefined4 *)0x0,0);
            if (iVar6 == 0) {
              pcVar1 = "\nError parsing triggerall";
LAB_080bf182:
              strcat((char *)(g + 0x81d2),pcVar1);
              return false;
            }
            ArrayAdd((int)local_8c,local_9c,0xffffffff,iVar4);
            pbVar2 = (byte *)TPGetValueNext(param_1,"triggerall");
            iVar4 = iVar4 + 1;
          } while (pbVar2 != (byte *)0x0);
        }
      }
      local_84[0] = 1;
      TPGetValueInt(param_1,"persistent",local_84);
      local_84[1] = 0;
      TPGetValueInt(param_1,"ignorehitpause",local_84 + 1);
      iVar4 = SCtrlParseElemType(param_1,(int)&local_8c,param_4);
      if (iVar4 != 0) {
        iVar4 = ArrayAdd(*param_2,&local_8c,local_84[2],param_3);
        return iVar4 != -1;
      }
    }
  }
  return false;
}
#undef local_e8
#undef local_e4
#undef local_e0
#undef local_dc
#undef local_bc
#undef local_9c
#undef local_8c
#undef local_88
#undef local_84

/* PlayerDoSCtrlApplyElem @ 0x080bf1d0, 185 bytes */
undefined4 PlayerDoSCtrlApplyElem(int *param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = param_1[0x2fb];
  param_1[0xcfa] = param_1[0x2fd];
  param_1[0xcfb] = param_1[0x380];
  param_1[0xcfc] = param_1[0x381];
  param_1[0xcfd] = param_1[899];
  iVar1 = PlayerSCtrlApplyElem(param_1,param_2,param_3);
  if (iVar1 == 0) {
    uVar3 = 0;
  }
  else {
    if ((iVar2 == 0) && (param_1[0x2fb] == 0)) {
      iVar2 = AICountCommands(param_1 + 0xcef);
      if (0 < iVar2) {
        AICopyCommands((int)(param_1 + 0xce4),param_1 + 0xcef);
        param_1[0xcee] = g[0x7304];
        PlayerAILearnMoveStart((int)param_1);
        PlayerAIMsgAttack((int)param_1);
      }
    }
    uVar3 = 1;
  }
  return uVar3;
}

/* PlayerSCtrlApplyElem @ 0x080bf290, 17297 bytes
 * REVIEW: pid-unaff_
 * FIXUP: rewrote 2 PalGrpFlag by-value loads
 * FIXUP: 28 data addresses written as literals replaced by data-image references
 * FIXUP: 1 partial-variable block copies written as memcpy
 * FIXUP: rewrote 11 Ghidra partial-variable accesses (x._O_S_)
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: 3 exact-text site patches
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 29 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 10 stack locals placed at their original offsets in a 0x10d0-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
undefined4 PlayerSCtrlApplyElem(int *player,int param_2,int *param_3)

{
  PalGrpFlag a;
  PalGrpFlag b;
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  int iVar3;
  int iVar4;
  int iVar5;
  long lVar6;
  uint uVar7;
  int *piVar8;
  undefined4 uVar9;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  double *pdVar10;
  double *pdVar11;
  int *piVar12;
  int *unaff_ESI;
  undefined4 *puVar13;
  bool bVar14;
  undefined2 in_FPUControlWord;
  float10 fVar15;
  char *pcVar16;
  uint uVar17;
  unsigned char ghidra_frame[0x10d0] __attribute__((aligned(16)));
#define local_10c4 (*(int *)(ghidra_frame + 0xc))
#define local_10c0 (*(float *)(ghidra_frame + 0x10))
#define local_10bc (*(undefined1 (*)[40])(ghidra_frame + 0x14))
#define local_10ac (*(undefined4 (*)[8])(ghidra_frame + 0x24))
#define local_108c (*(char (*)[4096])(ghidra_frame + 0x44))
#define local_8c (*(PalGrpFlag *)(ghidra_frame + 0x1044))
#define local_6c (*(PalGrpFlag *)(ghidra_frame + 0x1064))
#define local_4c (*(PalGrpFlag (*)[2])(ghidra_frame + 0x1084))
#define local_24 (*(int *)(ghidra_frame + 0x10ac))
#define local_20 (*(undefined4 *)(ghidra_frame + 0x10b0))
  
  local_10c4 = 0;
  iVar3 = *param_3;
  piVar8 = (int *)param_3[3];
  iVar2 = param_3[2];
  piVar12 = (int *)param_3[4];
  iVar4 = *(int *)(param_2 + 0x10);
  if (iVar4 == 0x4a) {
    piVar8 = (int *)ArrayScanFirst(player[0x88]);
    while (piVar8 != (int *)0x0) {
      iVar3 = *piVar8;
      iVar2 = EvalExpressionI((int)player,param_2 + 0x54,1);
      if ((*(int *)(iVar3 + 0xe10) == 0) && ((iVar2 == -1 || (iVar2 == *(int *)(iVar3 + 0x1064)))))
      {
        iVar2 = EvalExpressionI((int)player,param_2 + 0x30,0);
        iVar4 = EvalExpressionI((int)player,param_2 + 0x24,0);
        iVar5 = EvalExpressionI((int)player,param_2 + 0x18,1);
        PlayerTakeDamage(iVar3,-iVar5,iVar4,iVar2);
      }
      piVar8 = (int *)ArrayScanNext(player[0x88]);
    }
    return 0;
  }
  if (0x4a < iVar4) {
    if (iVar4 == 0xcb) {
      PlayerCalcDraw((int)player);
      local_10c4 = EvalExpressionI((int)player,param_2 + 0x18,1);
      if (local_10c4 < 0) {
        local_10c4 = 0;
        Warn((int)player,(int)&DAT_0827b133);
      }
      fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
      iVar3 = (int)GHIDRA_FIST32((float10)player[100] * fVar15 + GHIDRA_I2F(player[0x4d5]) + (float)g[0x7311]);
      local_24 = iVar3;
      fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x48));
      local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
      iVar2 = (int)GHIDRA_FIST32((float)g[0x7312] + GHIDRA_I2F(player[0x4d6]) + fVar15);
      local_24 = iVar2;
      iVar4 = EvalExpressionI((int)player,param_2 + 0x30,1);
      if (iVar4 < 1) {
        if (iVar4 < 0) {
          Warn((int)player,(int)&DAT_0827b680);
        }
      }
      else {
        lVar6 = random();
        iVar3 = iVar3 + (lVar6 % iVar4 - (iVar4 >> 1)) * player[100];
        lVar6 = random();
        iVar2 = iVar2 + (lVar6 % iVar4 - (iVar4 >> 1));
      }
      uVar7 = AnimPerArrayAdd((int *)g[0x413c],g[0x4148],g[0x4147],0,local_10c4,iVar3,iVar2,
                              (uint)(player[100] != 1),0xffffffff);
      local_10c4 = EvalExpressionI((int)player,param_2 + 0x24,0);
      if (uVar7 == 0xffffffff) {
        return 0;
      }
      AnimPerArraySetNo((int *)g[0x413c],uVar7,(local_10c4 != 0) + 1);
      return 0;
    }
    if (iVar4 < 0xcc) {
      if (iVar4 == 0x67) {
        if (GHIDRA_I2F(player[0x41e]) != -32760.0) {
          player[0x6d] = GHIDRA_F2I(int, ((float10)player[100] * GHIDRA_I2F(player[0x41e])));
        }
        if (GHIDRA_I2F(player[0x41f]) == -32760.0) {
          return 0;
        }
        player[0x6e] = player[0x41f];
        return 0;
      }
      if (iVar4 < 0x68) {
        if (iVar4 == 0x50) {
          iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
          player[0x4b3] = iVar3;
          return 0;
        }
        if (iVar4 < 0x51) {
          if (iVar4 == 0x4c) {
            piVar8 = (int *)ArrayScanFirst(player[0x88]);
            while (piVar8 != (int *)0x0) {
              iVar3 = *piVar8;
              iVar2 = EvalExpressionI((int)player,param_2 + 0x30,1);
              if ((*(int *)(iVar3 + 0xe10) == 0) &&
                 ((iVar2 == -1 || (iVar2 == *(int *)(iVar3 + 0x1064))))) {
                fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
                if (fVar15 != -32760.0) {
                  *(float *)(iVar3 + 0x1b4) =
                       (float10)*(int *)(iVar3 + 400) * fVar15 + *(float *)(iVar3 + 0x1b4);
                }
                fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x48));
                if (fVar15 != -32760.0) {
                  *(float *)(iVar3 + 0x1b8) = *(float *)(iVar3 + 0x1b8) + fVar15;
                }
              }
              piVar8 = (int *)ArrayScanNext(player[0x88]);
            }
            return 0;
          }
          if (iVar4 < 0x4c) {
            piVar8 = (int *)ArrayScanFirst(player[0x88]);
            while (piVar8 != (int *)0x0) {
              iVar3 = *piVar8;
              iVar2 = EvalExpressionI((int)player,param_2 + 0x30,1);
              if ((*(int *)(iVar3 + 0xe10) == 0) &&
                 ((iVar2 == -1 || (iVar2 == *(int *)(iVar3 + 0x1064))))) {
                fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
                if (fVar15 != -32760.0) {
                  *(float *)(iVar3 + 0x1b4) = (float10)*(int *)(iVar3 + 400) * fVar15;
                }
                fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x48));
                if (fVar15 != -32760.0) {
                  *(float *)(iVar3 + 0x1b8) = fVar15;
                }
              }
              piVar8 = (int *)ArrayScanNext(player[0x88]);
            }
            return 0;
          }
          if (iVar4 == 0x4d) {
            piVar8 = (int *)ArrayScanFirst(player[0x88]);
            while (piVar8 != (int *)0x0) {
              iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
              if (((0 < iVar3) && (iVar2 = *piVar8, player[100] != *(int *)(iVar2 + 400))) ||
                 ((iVar3 < 0 && (iVar2 = *piVar8, player[100] == *(int *)(iVar2 + 400))))) {
                PlayerTurnAround(iVar2);
              }
              piVar8 = (int *)ArrayScanNext(player[0x88]);
            }
            return 0;
          }
          if (iVar4 == 0x4e) {
            bVar1 = false;
            piVar8 = (int *)ArrayScanFirst(player[0x88]);
            while (piVar8 != (int *)0x0) {
              iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
              iVar2 = EvalExpressionI((int)player,param_2 + 0x24,1);
              if ((iVar3 != *(int *)(*piVar8 + 0x1064)) || (bVar1)) {
                ArrayDelete(player[0x88],*(int *)(player[0x88] + 0x1c));
              }
              else if (iVar2 != 0) {
                bVar1 = true;
              }
              piVar8 = (int *)ArrayScanNext(player[0x88]);
            }
            return 0;
          }
        }
        else {
          if (iVar4 == 100) {
            iVar3 = EvalExpressionI((int)player,param_2 + 0x18,0);
            if (iVar3 != -1) {
              player[0x41c] = iVar3;
            }
            fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
            if (fVar15 != -32760.0) {
              player[0x41e] = GHIDRA_F2I(int, fVar15);
            }
            fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
            if (fVar15 == -32760.0) {
              return 0;
            }
            player[0x41f] = GHIDRA_F2I(int, fVar15);
            return 0;
          }
          if (iVar4 < 0x65) {
            if (iVar4 == 0x51) {
              iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
              player[0x7c] = (uint)(iVar3 != 0);
              return 0;
            }
          }
          else {
            if (iVar4 == 0x65) {
              iVar3 = EvalExpressionI((int)player,param_2 + 0x18,0);
              if (iVar3 != 0) {
                player[0x6d] = GHIDRA_F2I(int, ((float10)player[0x403] + GHIDRA_I2F(player[0x416])));
              }
              iVar3 = EvalExpressionI((int)player,param_2 + 0x24,0);
              if (iVar3 == 0) {
                return 0;
              }
              player[0x6e] = GHIDRA_F2I(int, ((float10)player[0x404] + GHIDRA_I2F(player[0x417])));
              return 0;
            }
            if (iVar4 == 0x66) {
              PlayerTakeDamage((int)player,player[0x41d],1,1);
              player[0x41d] = 0;
              return 0;
            }
          }
        }
      }
      else {
        if (iVar4 == 0x78) {
          uVar7 = EvalExpressionI((int)player,param_2 + 0x18,1);
          if (7 < uVar7) {
            uVar7 = 0;
            Warn((int)player,(int)&DAT_0827b600);
          }
          SCtrlInitHitOverride
                    (*(undefined4 **)(param_2 + 0x60),player + uVar7 * 5 + 0x42a,(int)player);
          return 0;
        }
        if (iVar4 < 0x79) {
          if (iVar4 == 0x69) {
            fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
            player[0x62] = GHIDRA_F2I(int, ((float10)player[0x16] * fVar15 * ((float)0.01f)));
            return 0;
          }
          if (iVar4 < 0x69) {
            iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
            player[0x4e6] = player[0x4e6] + iVar3;
            player[0x4e7] = player[0x4e7] + iVar3;
            player[0x4e8] = player[0x4e8] + iVar3;
            ComboAdd(player[3],iVar3);
            return 0;
          }
          if (iVar4 == 0x6a) {
            fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
            player[99] = GHIDRA_F2I(int, ((fVar15 * 100.0) / (float10)player[0x1c]));
            return 0;
          }
          if (iVar4 == 0x6e) {
            iVar3 = EvalExpressionI((int)player,param_2 + 0x18,0);
            if (iVar3 != -1) {
              player[0x380] = iVar3;
            }
            iVar3 = EvalExpressionI((int)player,param_2 + 0x24,0);
            if (iVar3 != -1) {
              player[0x381] = iVar3;
            }
            iVar3 = EvalExpressionI((int)player,param_2 + 0x30,0);
            if (iVar3 == -1) {
              return 0;
            }
            player[0x382] = iVar3;
            return 0;
          }
        }
        else {
          if (iVar4 == 200) {
            SCtrlInitEnvShake(*(int **)(param_2 + 0x60),g + 0x7317,player);
            return 0;
          }
          if (iVar4 < 0xc9) {
            if (iVar4 == 0x82) {
              player[0x38c] = 0;
              return 0;
            }
            if (iVar4 == 0x96) {
              iVar3 = EvalExpressionI((int)player,param_2 + 0x18,0);
              if (iVar3 != -1) {
                iVar2 = EvalExpressionI((int)player,param_2 + 0x3c,0);
                if (iVar2 == 0) {
                  *(undefined1 *)((int)g + iVar3 + 0x1d38c) = 1;
                }
                else {
                  *(undefined1 *)(iVar3 + 0x204 + (int)player) = 1;
                }
              }
              iVar3 = EvalExpressionI((int)player,param_2 + 0x24,0);
              if (iVar3 != -1) {
                iVar2 = EvalExpressionI((int)player,param_2 + 0x48,0);
                if (iVar2 == 0) {
                  *(undefined1 *)((int)g + iVar3 + 0x1d38c) = 1;
                }
                else {
                  *(undefined1 *)(iVar3 + 0x204 + (int)player) = 1;
                }
              }
              iVar3 = EvalExpressionI((int)player,param_2 + 0x30,0);
              if (iVar3 == -1) {
                return 0;
              }
              iVar2 = EvalExpressionI((int)player,param_2 + 0x54,0);
              if (iVar2 == 0) {
                *(undefined1 *)((int)g + iVar3 + 0x1d38c) = 1;
                return 0;
              }
              *(undefined1 *)(iVar3 + 0x204 + (int)player) = 1;
              return 0;
            }
          }
          else {
            if (iVar4 == 0xc9) {
              if (player[0x425] < 1) {
                return 0;
              }
              piVar8 = player + 0x424;
              piVar12 = g + 0x7317;
              for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
                *piVar12 = *piVar8;
                piVar8 = piVar8 + 1;
                piVar12 = piVar12 + 1;
              }
              player[0x425] = 0;
              return 0;
            }
            if (iVar4 == 0xca) {
              iVar3 = EvalExpressionI((int)player,param_2 + 0x3c,1);
              iVar2 = EvalExpressionI((int)player,param_2 + 0x48,1);
              local_10c4 = EvalExpressionI((int)player,param_2 + 0x54,1);
              iVar3 = makecol(iVar3,iVar2,local_10c4);
              g[0x4145] = iVar3;
              iVar3 = EvalExpressionI((int)player,param_2 + 0x24,1);
              piVar8 = g;
              g[0x4146] = iVar3;
              if (iVar3 != -1) {
                piVar8[0x4146] = iVar3 + 1;
              }
              if (g[0x4146] < -1) {
                Warn((int)player,(int)&DAT_0827b11a);
                g[0x4146] = 1;
              }
              iVar3 = EvalExpressionI((int)player,param_2 + 0x30,1);
              g[0x4144] = (uint)(iVar3 != 0);
              return 0;
            }
          }
        }
      }
      goto LAB_080c35f1;
    }
    if (iVar4 == 300) {
      HelperMake(player,*(char **)(param_2 + 0x60),param_3);
      return 0;
    }
    if (iVar4 < 0x12d) {
      if (iVar4 == 0xd7) {
        iVar3 = EvalExpressionI((int)player,param_2 + 0x30,1);
        if (iVar3 < 1) {
          iVar3 = 1;
          Warn((int)player,(int)&DAT_0827b19d);
        }
        if (g[0x7514] % iVar3 != 0) {
          return 0;
        }
        PlayerCalcDraw((int)player);
        iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
        lVar6 = random();
        iVar3 = (int)GHIDRA_FIST32(((float)(lVar6 % 3) +
                           (float)(iVar3 * player[100]) + GHIDRA_I2F(player[0x4d5]) + (float)g[0x7311]) -
                           1.0);
        local_24 = iVar3;
        iVar2 = EvalExpressionI((int)player,param_2 + 0x24,1);
        lVar6 = random();
        local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
        iVar2 = (int)GHIDRA_FIST32(((float)(lVar6 % 3) +
                           (float)g[0x7312] + (float10)iVar2 + GHIDRA_I2F(player[0x4d6])) - 1.0);
        local_24 = iVar2;
        local_10c4 = ExplodAdd((undefined4 *)g[0x52be],0x78,(int *)g[0x4148],g[0x4147]);
        if (local_10c4 != -1) {
          iVar4 = *(int *)g[0x52be] + local_10c4 * 0xe4;
          *(float *)(iVar4 + 0x14) = (float10)iVar3;
          *(float *)(iVar4 + 0x18) = (float10)iVar2;
          *(undefined4 *)(iVar4 + 0x6c) = 1;
          uVar9 = AnimGetLooptime(*(undefined4 **)(iVar4 + 0x80));
          iVar3 = *(int *)(iVar4 + 0x80);
          *(undefined4 *)(iVar4 + 0x40) = uVar9;
          piVar8 = g;
          *(undefined4 *)(iVar3 + 0x34) = 10;
          *(int *)(iVar3 + 0x30) = piVar8[0x413d];
        }
        fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x54));
        if (fVar15 == 0.0) {
          return 0;
        }
        fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
        lVar6 = random();
        iVar3 = (int)GHIDRA_FIST32(((float)(lVar6 % 3) +
                           (float10)player[100] * fVar15 + GHIDRA_I2F(player[0x4d5]) + (float)g[0x7311]) -
                           1.0);
        local_24 = iVar3;
        fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x48));
        lVar6 = random();
        local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
        iVar2 = (int)GHIDRA_FIST32(((float)(lVar6 % 3) + (float)g[0x7312] + GHIDRA_I2F(player[0x4d6]) + fVar15) -
                           1.0);
        local_24 = iVar2;
        local_10c4 = ExplodAdd((undefined4 *)g[0x52be],0x78,(int *)g[0x4148],g[0x4147]);
        if (local_10c4 == -1) {
          return 0;
        }
        iVar4 = *(int *)g[0x52be] + local_10c4 * 0xe4;
        *(float *)(iVar4 + 0x14) = (float10)iVar3;
        *(float *)(iVar4 + 0x18) = (float10)iVar2;
        *(undefined4 *)(iVar4 + 0x6c) = 1;
        uVar9 = AnimGetLooptime(*(undefined4 **)(iVar4 + 0x80));
        iVar3 = *(int *)(iVar4 + 0x80);
        *(undefined4 *)(iVar4 + 0x40) = uVar9;
        piVar8 = g;
        *(undefined4 *)(iVar3 + 0x34) = 10;
        *(int *)(iVar3 + 0x30) = piVar8[0x413d];
        return 0;
      }
      if (iVar4 < 0xd8) {
        if (iVar4 == 0xd3) {
          if (player[0x4e5] == 0) {
            return 0;
          }
          *(undefined4 *)(player[0x4e5] + 0x14) = 0;
          iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
          *(int *)(player[0x4e5] + 0x1c) = iVar3;
          if (-2 < iVar3) {
            return 0;
          }
          Warn((int)player,(int)&DAT_0827b14a);
          *(undefined4 *)(player[0x4e5] + 0x1c) = 1;
          return 0;
        }
        if (iVar4 < 0xd4) {
          if (iVar4 == 0xd2) {
            iVar3 = player[0x4e5];
            if (iVar3 == 0) {
              iVar3 = RequestNewAftImg(g[0x413f]);
              player[0x4e5] = iVar3;
            }
            if (iVar3 == 0) {
              return 0;
            }
            SCtrlInitAftImgParams(*(int *)(param_2 + 0x60),player[0x4e5],player[0x4ef],player);
            return 0;
          }
        }
        else {
          if (iVar4 == 0xd4) {
            SCtrlInitPause(*(int *)(param_2 + 0x60),0,(int)player);
            return 0;
          }
          if (iVar4 == 0xd6) {
            iVar3 = *(int *)(param_2 + 0x60);
            SCtrlInitPause(iVar3,1,(int)player);
            iVar2 = EvalExpressionI((int)player,iVar3 + 0x58,1);
            if (iVar2 == 0) {
              g[0x7502] = 0;
            }
            else {
              PalGrpMakeFlag(local_4c,0xffffffff,1);
              piVar8 = g;
              g[0x74fd] = local_4c[0].w[0];
              piVar8[0x74fe] = local_4c[0].w[1];
              piVar8[0x74ff] = local_4c[0].w[2];
              piVar8[0x7500] = local_4c[0].w[3];
              piVar8[0x7501] = local_4c[0].w[4];
              PalGrpMakeFlag(&local_8c,0xffffffff,3);
              b.w[1] = local_8c.w[1];
              b.w[0] = local_8c.w[0];
              b.w[2] = local_8c.w[2];
              b.w[3] = local_8c.w[3];
              b.w[4] = local_8c.w[4];
              PalGrpOrFlag(&local_6c,*(PalGrpFlag *)(g + 0x74fd),b);
              piVar8 = g;
              g[0x74fd] = local_6c.w[0];
              piVar8[0x74fe] = local_6c.w[1];
              piVar8[0x74ff] = local_6c.w[2];
              piVar8[0x7500] = local_6c.w[3];
              piVar8[0x7501] = local_6c.w[4];
              a.w[4] = local_6c.w[4];
              memcpy((char *)&a.w + 0, (piVar8 + 0x74fd), 16);
              PalGrpXorFlag(&local_8c,a,*(PalGrpFlag *)(player + 0x972));
              piVar8 = g;
              g[0x74fd] = local_8c.w[0];
              piVar8[0x74fe] = local_8c.w[1];
              piVar8[0x74ff] = local_8c.w[2];
              piVar8[0x7500] = local_8c.w[3];
              piVar8[0x7501] = local_8c.w[4];
              piVar8[0x7502] = 1;
            }
            if ((player[0x78] < 0) || (g[0x7503] < player[0x78])) {
              Warn((int)player,(int)&DAT_0827b165);
              player[0x78] = 0;
            }
            iVar2 = EvalExpressionI((int)player,iVar3 + 0x34,1);
            if (iVar2 < -1) {
              iVar2 = -1;
              Warn((int)player,(int)&DAT_0827b17f);
            }
            if (iVar2 != -1) {
              fVar15 = EvalExpressionF(player,(int *)(iVar3 + 0x40));
              iVar4 = (int)GHIDRA_FIST32((float10)player[100] * (fVar15 - (float10)player[0x70]) *
                                 GHIDRA_I2F(player[0x4d2]) + GHIDRA_I2F(player[0x4d5]) + (float)g[0x7311]);
              local_24 = iVar4;
              fVar15 = EvalExpressionF(player,(int *)(iVar3 + 0x4c));
              local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
              local_24 = (int)GHIDRA_FIST32((fVar15 - (float10)player[0x71]) * GHIDRA_I2F(player[0x4d2]) +
                                    GHIDRA_I2F(player[0x4d6]) + (float)g[0x7312]);
              PlayerSparkCreate(player,iVar2,iVar4,local_24,(uint)(*(int *)(iVar3 + 0x30) == 0),
                                (uint)(player[100] != 1),0);
            }
            fVar15 = EvalExpressionF(player,(int *)(iVar3 + 100));
            if (fVar15 < 0.0) {
              Warn((int)player,(int)&DAT_0827b6c0);
              fVar15 = 0.0;
            }
            if (fVar15 == 0.0) {
              fVar15 = GHIDRA_I2F(g[0x7320]);
            }
            if (fVar15 != 1.0) {
              piVar8 = (int *)ArrayScanFirst(player[0x88]);
              while (piVar8 != (int *)0x0) {
                iVar2 = *piVar8;
                if (*(int *)(iVar2 + 0xe10) == 0) {
                  *(float *)(iVar2 + 0x18c) = *(float *)(iVar2 + 0x18c) / fVar15;
                }
                piVar8 = (int *)ArrayScanNext(player[0x88]);
              }
            }
            iVar2 = EvalExpressionI((int)player,iVar3 + 0x70,1);
            PlayerPowerSet(param_3[1],iVar2 + **(int **)(param_3[1] + 0x170));
            iVar2 = EvalExpressionI((int)player,iVar3 + 0x7c,0);
            if ((iVar2 != 0) && (player[0x3fe] < g[0x7503])) {
              player[0x3fe] = g[0x7503];
            }
            iVar2 = EvalExpressionI((int)player,iVar3 + 0x8c,1);
            iVar4 = EvalExpressionI((int)player,iVar3 + 0x98,1);
            if (*(int *)(iVar3 + 0x88) == 0) {
              iVar3 = *(int *)(*player + 0x11d0);
              piVar8 = *(int **)(*player + 0x11d4);
              fVar15 = GHIDRA_I2F(player[0x4d5]);
            }
            else {
              iVar3 = 0;
              piVar8 = (int *)g[0x4156];
              fVar15 = GHIDRA_I2F(player[0x4d5]);
            }
            local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
            local_24 = (int)GHIDRA_FIST32(fVar15);
            GameSndPlayIDPos(-1,local_24,piVar8,iVar2,iVar4,iVar3);
            return 0;
          }
        }
      }
      else {
        if (iVar4 == 0xdd) {
          iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
          if (iVar3 < -1) {
            iVar3 = -1;
            Warn((int)player,(int)&DAT_0827b1b3);
          }
          ExplodRemoveID((undefined4 *)g[0x52be],player[1],iVar3);
          return 0;
        }
        if (iVar4 < 0xde) {
          if (iVar4 == 0xd8) {
            SCtrlInitPalFX(*(int **)(param_2 + 0x60),player + 0x977,(int)player);
            return 0;
          }
          if (iVar4 == 0xdc) {
            ExplodMakeFromInfo(player,*(int *)(param_2 + 0x60),param_3);
            return 0;
          }
        }
        else {
          if (iVar4 == 0xde) {
            iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
            iVar2 = EvalExpressionI((int)player,param_2 + 0x24,1);
            if (iVar3 < -1) {
              iVar3 = -1;
              Warn((int)player,(int)&DAT_0827b1d0);
            }
            if (iVar2 < -1) {
              iVar2 = -1;
              Warn((int)player,(int)&DAT_0827b1ed);
            }
            ExplodBindChange((undefined4 *)g[0x52be],player[1],iVar3,iVar2);
            return 0;
          }
          if (iVar4 == 0xdf) {
            ExplodModifyFromInfo(player,*(int *)(param_2 + 0x60),param_3);
            return 0;
          }
        }
      }
      goto LAB_080c35f1;
    }
    if (0x137 < iVar4) {
      if (0x141 < iVar4) {
        if (iVar4 == 0x2743) {
          if (iVar2 == 0) {
            return 1;
          }
          iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
          if (-1 < iVar3) {
            PlayerChangeState((int)player,iVar3);
          }
          iVar3 = EvalExpressionI((int)player,param_2 + 0x24,1);
          if (*(int *)(iVar2 + 400) != player[100]) {
            PlayerTurnAround(iVar2);
          }
          if (-1 < iVar3) {
            PlayerChangeState(iVar2,iVar3);
            *(undefined4 *)(iVar2 + 0x3460) = 0;
            return 1;
          }
          pcVar16 = "attempted change to negative anim";
          goto LAB_080c3484;
        }
        if (iVar4 == 0x2744) {
          player[0xd18] = 1;
          return 1;
        }
        goto LAB_080c35f1;
      }
      if (iVar4 < 0x140) {
        if (iVar4 == 0x138) {
          ClipboardClear((undefined4 *)player[0xd17]);
          return 0;
        }
        goto LAB_080c35f1;
      }
      if (player[7] != 1) {
        return 0;
      }
      if (iVar4 == 0x140) {
        piVar12 = piVar8;
        if (piVar8 == (int *)0x0) {
          pcVar16 = "No parent for bindtoparent";
LAB_080c3484:
          Warn((int)player,(int)pcVar16);
          return 0;
        }
      }
      else if (piVar12 == (int *)0x0) {
        pcVar16 = "No root for bindtoroot";
        goto LAB_080c3484;
      }
      iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
      player[0xd0c] = iVar3;
      if (iVar3 < -1) {
        player[0xd0c] = 1;
        Warn((int)player,(int)&DAT_0827b287);
      }
      iVar3 = EvalExpressionI((int)player,param_2 + 0x24,1);
      player[0xd11] = iVar3;
      if (iVar3 < 0) {
        if (iVar3 == -1) goto LAB_080c3558;
        player[0xd11] = -1;
      }
      else {
        if ((iVar3 < 1) || (iVar3 == 1)) goto LAB_080c3558;
        player[0xd11] = 1;
      }
      Warn((int)player,(int)&DAT_0827b700);
LAB_080c3558:
      fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
      player[0xd12] = GHIDRA_F2I(int, fVar15);
      fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x48));
      player[0xd13] = GHIDRA_F2I(int, fVar15);
      fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x54));
      player[0xd14] = GHIDRA_F2I(int, fVar15);
      player[0xd0d] = (int)(piVar12 + 0x67);
      player[0xd0e] = (int)(piVar12 + 0x68);
      player[0xd0f] = (int)(piVar12 + 0x69);
      player[0xd15] = (int)piVar12;
      player[0xd10] = (int)(piVar12 + 100);
      return 0;
    }
    if (0x135 < iVar4) {
      iVar3 = *(int *)(param_2 + 0x5c);
      if (iVar3 != 0) {
        unaff_ESI = &local_10c4;
        iVar2 = EvalExpression(player,(int *)(param_2 + 0x18),unaff_ESI,(int *)&local_10c0);
        if (iVar2 == 2) {
          pdVar10 = (double *)(local_10bc + 8);
          *(double *)local_10bc = (double)local_10c0;
        }
        else {
          pdVar10 = (double *)(local_10bc + 4);
          (*(uint *)((char *)&local_10bc + 0)) = local_10c4;
        }
        if (iVar3 != 1) {
          iVar2 = EvalExpression(player,(int *)(param_2 + 0x24),unaff_ESI,(int *)&local_10c0);
          if (iVar2 == 2) {
            pdVar11 = pdVar10 + 1;
            *pdVar10 = (double)local_10c0;
          }
          else {
            pdVar11 = (double *)((int)pdVar10 + 4);
            *(int *)pdVar10 = local_10c4;
          }
          if (iVar3 != 2) {
            iVar2 = EvalExpression(player,(int *)(param_2 + 0x30),unaff_ESI,(int *)&local_10c0);
            if (iVar2 == 2) {
              pdVar10 = pdVar11 + 1;
              *pdVar11 = (double)local_10c0;
            }
            else {
              pdVar10 = (double *)((int)pdVar11 + 4);
              *(int *)pdVar11 = local_10c4;
            }
            if (iVar3 != 3) {
              iVar2 = EvalExpression(player,(int *)(param_2 + 0x3c),unaff_ESI,(int *)&local_10c0);
              if (iVar2 == 2) {
                pdVar11 = pdVar10 + 1;
                *pdVar10 = (double)local_10c0;
              }
              else {
                pdVar11 = (double *)((int)pdVar10 + 4);
                *(int *)pdVar10 = local_10c4;
              }
              if (iVar3 != 4) {
                iVar3 = EvalExpression(player,(int *)(param_2 + 0x48),unaff_ESI,(int *)&local_10c0);
                if (iVar3 == 2) {
                  *pdVar11 = (double)local_10c0;
                }
                else {
                  *(int *)pdVar11 = local_10c4;
                }
              }
            }
          }
        }
      }
      vsprintf(local_108c,*(char **)(param_2 + 0x60),(va_list)local_10bc);
      if (*(int *)(param_2 + 0x10) == 0x137) {
        ClipboardAppend((int *)player[0xd17],local_108c,unaff_ESI,unaff_ESI);
        return 0;
      }
      ClipboardPrint((int *)player[0xd17],local_108c,extraout_ECX_01,extraout_ECX_01);
      return 0;
    }
    if (iVar4 == 0x130) {
      if (player[7] != 1) {
        return 0;
      }
      if (piVar8 == (int *)0x0) {
        pcVar16 = "no parent for parentvarset";
        goto LAB_080c3484;
      }
      iVar3 = EvalExpressionI((int)player,param_2 + 0x30,0);
      iVar2 = EvalExpressionI((int)player,param_2 + 0x24,1);
      if (-1 < iVar2) {
        if (iVar3 == 0) {
          if (0x3b < iVar2) goto LAB_080c32c5;
        }
        else if (0x27 < iVar2) goto LAB_080c32c5;
        if (iVar3 != 0) {
          fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x18));
          piVar8[iVar2 + 0x3cc] = GHIDRA_F2I(int, fVar15);
          return 0;
        }
        iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
        piVar8[iVar2 + 0x390] = iVar3;
        return 0;
      }
LAB_080c32c5:
      Warn((int)player,(int)&DAT_0827b21f);
      return 0;
    }
    if (iVar4 < 0x131) {
      if (iVar4 == 0x12d) {
        HelperDestroy((int)player);
        return 0;
      }
      goto LAB_080c35f1;
    }
    if (iVar4 != 0x131) goto LAB_080c35f1;
    if (player[7] != 1) {
      return 0;
    }
    if (piVar8 == (int *)0x0) {
      Warn((int)player,(int)&DAT_0827b23a);
      return 0;
    }
    iVar3 = EvalExpressionI((int)player,param_2 + 0x30,0);
    iVar2 = EvalExpressionI((int)player,param_2 + 0x24,1);
    if (iVar2 < 0) {
LAB_080c33ba:
      Warn((int)player,(int)&DAT_0827b21f);
      return 0;
    }
    if (iVar3 == 0) {
      if (0x3b < iVar2) goto LAB_080c33ba;
    }
    else if (0x27 < iVar2) goto LAB_080c33ba;
    if (iVar3 == 0) {
      iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
      piVar8[iVar2 + 0x390] = piVar8[iVar2 + 0x390] + iVar3;
      return 0;
    }
    fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x18));
    iVar3 = iVar2 * 4 + 0xf20;
    piVar8 = piVar8 + 4;
    goto LAB_080c33fe;
  }
  if (iVar4 == 0x1c) {
    iVar3 = EvalExpressionI((int)player,param_2 + 0x18,0);
    if (iVar3 != 0) {
      fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
      local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
      local_24 = (int)GHIDRA_FIST32(fVar15);
      player[0x70] = local_24;
    }
    iVar3 = EvalExpressionI((int)player,param_2 + 0x24,0);
    if (iVar3 == 0) {
      return 0;
    }
    fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x48));
    player[0x71] = (int)GHIDRA_FIST32(fVar15);
    return 0;
  }
  if (0x1c < iVar4) {
    if (iVar4 == 0x32) {
      iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
      player[0x79] = (uint)(iVar3 != 0);
      iVar3 = EvalExpressionI((int)player,param_2 + 0x24,1);
      player[0x7a] = (uint)(iVar3 != 0);
      iVar3 = EvalExpressionI((int)player,param_2 + 0x30,1);
      player[0x7b] = (uint)(iVar3 != 0);
      return 0;
    }
    if (iVar4 < 0x33) {
      if (iVar4 == 0x23) {
        uVar7 = EvalExpressionI((int)player,param_2 + 0x18,1);
        uVar17 = uVar7 + 1;
        if (uVar17 < 0x21) {
          iVar3 = PlayerSndID((int)player,uVar7);
          SndIDStop(iVar3);
          return 0;
        }
        pcVar16 = "stopped illegal channel number %i";
LAB_080c001f:
        VWarn((int)player,pcVar16,uVar7,uVar17);
        return 0;
      }
      if (iVar4 < 0x24) {
        if (iVar4 == 0x20) {
          iVar3 = EvalExpressionI((int)player,param_2 + 0x24,1);
          iVar2 = EvalExpressionI((int)player,param_2 + 0x18,1);
          if (iVar3 < 0) {
            iVar3 = 0;
            Warn((int)player,(int)&DAT_0827b08c);
          }
          if (iVar2 < 0) {
            iVar2 = 0;
            Warn((int)player,(int)&DAT_0827b480);
          }
          if (iVar3 == 0) {
            PlayerSelfAnim(player,iVar2);
            return 0;
          }
          PlayerSelfAnimElem(player,iVar2,iVar3);
          return 0;
        }
        if (iVar4 < 0x21) {
          if (iVar4 == 0x1e) {
            iVar3 = EvalExpressionI((int)player,param_2 + 0x30,0);
            if (iVar3 == 0) {
              iVar3 = EvalExpressionI((int)player,param_2 + 0x18,0);
              player[0x3ff] = iVar3;
              iVar3 = EvalExpressionI((int)player,param_2 + 0x24,0);
              player[0x401] = iVar3;
              return 0;
            }
            iVar3 = EvalExpressionI((int)player,param_2 + 0x18,0);
            player[0x400] = iVar3;
            iVar3 = EvalExpressionI((int)player,param_2 + 0x24,0);
            player[0x402] = iVar3;
            return 0;
          }
        }
        else {
          if (iVar4 == 0x21) {
            iVar3 = player[0x4f0];
            if (iVar3 == 0) {
              piVar8 = (int *)player[0x4ef];
              iVar3 = *(int *)(*player + 0x11cc);
            }
            else {
              piVar8 = (int *)player[0x4ef];
            }
            *piVar8 = iVar3;
            iVar3 = EvalExpressionI((int)player,param_2 + 0x24,1);
            iVar2 = EvalExpressionI((int)player,param_2 + 0x18,1);
            if (iVar3 < 0) {
              iVar3 = 0;
              Warn((int)player,(int)&DAT_0827b08c);
            }
            if (iVar2 < 0) {
              iVar2 = 0;
              Warn((int)player,(int)&DAT_0827b480);
            }
            if (iVar3 == 0) {
              PlayerChangeAnim(player,iVar2);
              return 0;
            }
            PlayerChangeAnimElem(player,iVar2,iVar3);
            return 0;
          }
          if (iVar4 == 0x22) {
            SCtrlDoPlaySndInfo(player,*(int *)(param_2 + 0x60));
            return 0;
          }
        }
      }
      else {
        if (iVar4 < 0x27) {
          if (0x24 < iVar4) {
            iVar3 = player[0x463];
            iVar2 = player[0x4b3];
            SCtrlInitHitDef(*(undefined4 **)(param_2 + 0x60),(int)(player + 0x456),player);
            player[0x456] = 1;
            if (*(int *)(param_2 + 0x10) == 0x26) {
              player[0x457] = 0;
            }
            player[0x463] = iVar3;
            iVar4 = player[0x464];
            iVar3 = (int)GHIDRA_FIST32((float10)iVar4 * GHIDRA_I2F(player[0x62]) + 0.5);
            player[0x464] = iVar3;
            if ((0 < iVar4) && (iVar3 == 0)) {
              player[0x464] = 1;
            }
            if (player[0x4b3] == -1) {
              player[0x4b3] = iVar2;
            }
            piVar8 = g;
            player[0x45a] = g[0x74e1];
            piVar8[0x74e1] = piVar8[0x74e1] + 1;
            return 0;
          }
          uVar7 = EvalExpressionI((int)player,param_2 + 0x18,1);
          if (uVar7 < 0x20) {
            iVar3 = PlayerSndID((int)player,uVar7);
            if (iVar3 == -1) {
              return 0;
            }
            iVar3 = SndIDGetChannel(iVar3);
            if (iVar3 == -1) {
              return 0;
            }
            iVar4 = EvalExpressionI((int)player,param_2 + 0x24,1);
            iVar2 = player[100];
            iVar5 = EvalExpressionI((int)player,param_2 + 0x30,1);
            if (iVar5 == 0) {
              local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
              iVar2 = (int)GHIDRA_FIST32((GHIDRA_I2F(player[0x67]) - (float)g[0x7311]) + (float)(iVar4 * iVar2));
              local_24 = iVar2;
            }
            else {
              iVar2 = iVar4 * iVar2 + 0xa0;
            }
            iVar2 = ScrPositionToPan(iVar2);
            SndVoiceSetPan(iVar3,iVar2);
            return 0;
          }
          pcVar16 = "attemted to pan illegal channel number %i";
          uVar17 = uVar7;
          goto LAB_080c001f;
        }
        if (iVar4 == 0x27) {
          puVar13 = (undefined4 *)0x0;
          piVar8 = player;
          if (piVar12 != (int *)0x0) {
            piVar8 = piVar12;
          }
          iVar3 = SCtrlInitProjectile(*(int *)(param_2 + 0x60),player,iVar3,piVar8);
          if (iVar3 != -1) {
            puVar13 = (undefined4 *)
                      (iVar3 * *(int *)(*(int *)piVar8[0x87] + 4) +
                      *(int *)(*(int *)piVar8[0x87] + 0x14));
          }
          if (puVar13 == (undefined4 *)0x0) {
            return 0;
          }
          PlayerAISctrlProjectile((int)player,puVar13);
          iVar2 = puVar13[0x34];
          iVar3 = (int)GHIDRA_FIST32((float10)iVar2 * GHIDRA_I2F(player[0x62]) + 0.5);
          puVar13[0x34] = iVar3;
          if (iVar2 < 1) {
            return 0;
          }
          if (iVar3 != 0) {
            return 0;
          }
          puVar13[0x34] = 1;
          return 0;
        }
        if (iVar4 == 0x28) {
          iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
          player[0x7d] = iVar3;
          iVar3 = EvalExpressionI((int)player,param_2 + 0x24,1);
          player[0x7e] = iVar3;
          iVar3 = EvalExpressionI((int)player,param_2 + 0x30,1);
          player[0x7f] = iVar3;
          iVar3 = EvalExpressionI((int)player,param_2 + 0x3c,1);
          player[0x80] = iVar3;
          return 0;
        }
      }
    }
    else {
      if (iVar4 == 0x3f) {
        fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
        player[0x4df] = GHIDRA_F2I(int, (GHIDRA_I2F(player[0x4df]) * fVar15));
        return 0;
      }
      if (iVar4 < 0x40) {
        if (iVar4 == 0x3c) {
          player[0x4e0] = 1;
          fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
          if (fVar15 != -32760.0) {
            player[0x4df] = GHIDRA_F2I(int, fVar15);
          }
          fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x48));
          player[0x4d3] = GHIDRA_F2I(int, (GHIDRA_I2F(player[0x4d3]) * fVar15));
          fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x54));
          player[0x4d4] = GHIDRA_F2I(int, (GHIDRA_I2F(player[0x4d4]) * fVar15));
          return 0;
        }
        if (iVar4 < 0x3d) {
          if (iVar4 == 0x33) {
            iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
            player[0x73] = iVar3;
            return 0;
          }
        }
        else {
          if (iVar4 == 0x3d) {
            fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
            player[0x4df] = GHIDRA_F2I(int, fVar15);
            return 0;
          }
          if (iVar4 == 0x3e) {
            fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
            player[0x4df] = GHIDRA_F2I(int, (GHIDRA_I2F(player[0x4df]) + fVar15));
            return 0;
          }
        }
      }
      else {
        if (iVar4 == 0x47) {
          piVar8 = (int *)ArrayScanFirst(player[0x88]);
          iVar3 = EvalExpressionI((int)player,param_2 + 0x30,1);
          if (piVar8 != (int *)0x0) {
            iVar2 = *piVar8;
            iVar4 = *(int *)(iVar2 + 0xe10);
            while (((iVar4 != 0 || ((iVar3 != -1 && (iVar3 != *(int *)(iVar2 + 0x1064))))) &&
                   (piVar8 = (int *)ArrayScanNext(player[0x88]), piVar8 != (int *)0x0))) {
              iVar2 = *piVar8;
              iVar4 = *(int *)(iVar2 + 0xe10);
            }
          }
          if (piVar8 == (int *)0x0) {
            return 0;
          }
          iVar3 = *piVar8;
          iVar4 = 0;
          iVar2 = 0;
          iVar5 = EvalExpressionI((int)player,param_2 + 0x24,0);
          if (iVar5 == 1) {
            iVar2 = *(int *)(iVar3 + 0xa8);
            iVar4 = *(int *)(iVar3 + 0xac);
          }
          else {
            iVar5 = EvalExpressionI((int)player,param_2 + 0x24,0);
            if (iVar5 == 2) {
              iVar2 = *(int *)(iVar3 + 0xa0);
              iVar4 = *(int *)(iVar3 + 0xa4);
            }
          }
          iVar5 = EvalExpressionI((int)player,param_2 + 0x18,1);
          piVar8[6] = iVar5;
          if (iVar5 < -1) {
            Warn((int)player,(int)&DAT_0827b0fe);
            piVar8[6] = 1;
          }
          fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
          if (fVar15 != -32760.0) {
            iVar5 = *(int *)(iVar3 + 400);
            player[0x67] = GHIDRA_F2I(int, (((float10)iVar2 + fVar15) * (float10)iVar5 + *(float *)(iVar3 + 0x19c)))
            ;
            local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
            local_24 = (int)GHIDRA_FIST32((float10)player[100] * -((float10)iVar2 + fVar15) * (float10)iVar5);
            piVar8[3] = local_24;
          }
          fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x48));
          if (fVar15 == -32760.0) {
            return 0;
          }
          player[0x68] = GHIDRA_F2I(int, (*(float *)(iVar3 + 0x1a0) + (float10)iVar4 + fVar15));
          piVar8[4] = (int)GHIDRA_FIST32(-((float10)iVar4 + fVar15));
          return 0;
        }
        if (iVar4 < 0x48) {
          if (iVar4 == 0x41) {
            iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
            player[0x4e2] = iVar3;
            iVar3 = EvalExpressionI((int)player,param_2 + 0x24,1);
            player[0x4e3] = iVar3;
            if (iVar3 < 0) {
              player[0x4e3] = 0;
            }
            if (0x100 < player[0x4e3]) {
              player[0x4e3] = 0x100;
            }
            iVar3 = EvalExpressionI((int)player,param_2 + 0x30,1);
            player[0x4e4] = iVar3;
            if (iVar3 < 0) {
              player[0x4e4] = 0;
            }
            if (player[0x4e4] < 0x101) {
              return 0;
            }
            player[0x4e4] = 0x100;
            return 0;
          }
          if (iVar4 == 0x46) {
            piVar8 = (int *)ArrayScanFirst(player[0x88]);
            while (piVar8 != (int *)0x0) {
              iVar3 = EvalExpressionI((int)player,param_2 + 0x30,1);
              if ((*(int *)(*piVar8 + 0xe10) == 0) &&
                 ((iVar3 == -1 || (iVar3 == *(int *)(*piVar8 + 0x1064))))) {
                iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
                piVar8[6] = iVar3;
                if (iVar3 < -1) {
                  Warn((int)player,(int)&DAT_0827b0fe);
                  piVar8[6] = 1;
                }
                fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
                if (fVar15 != -32760.0) {
                  local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
                  local_24 = (int)GHIDRA_FIST32(fVar15);
                  piVar8[3] = local_24;
                }
                fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x48));
                if (fVar15 != -32760.0) {
                  local_20 = CONCAT22((*(ushort *)((char *)&local_20 + 2)),in_FPUControlWord);
                  local_24 = (int)GHIDRA_FIST32(fVar15);
                  piVar8[4] = local_24;
                }
              }
              piVar8 = (int *)ArrayScanNext(player[0x88]);
            }
            return 0;
          }
        }
        else {
          if (iVar4 == 0x48) {
            piVar8 = (int *)ArrayScanFirst(player[0x88]);
            while (piVar8 != (int *)0x0) {
              iVar3 = *piVar8;
              iVar2 = EvalExpressionI((int)player,param_2 + 0x30,1);
              if ((*(int *)(iVar3 + 0xe10) == 0) &&
                 ((iVar2 == -1 || (iVar2 == *(int *)(iVar3 + 0x1064))))) {
                *(int *)(iVar3 + 0xbec) = player[0x2fa];
                *(int *)(iVar3 + 0xbf0) = player[2];
                *(int *)(iVar3 + 0x964) = player[0x259];
                if (player[0x2fb] != 0) {
                  *(int *)(iVar3 + 0xbec) = player[0x2fb];
                  *(int *)(iVar3 + 0xbf0) = player[0x2fc];
                }
                iVar2 = player[0x4f0];
                if (iVar2 == 0) {
                  iVar2 = *(int *)player[0x4ef];
                }
                *(int *)(iVar3 + 0x13c0) = iVar2;
                iVar2 = EvalExpressionI((int)player,param_2 + 0x18,1);
                if (iVar2 < 0) {
                  iVar2 = 0;
                  Warn((int)player,(int)&DAT_0827b640);
                }
                PlayerChangeState(iVar3,iVar2);
              }
              piVar8 = (int *)ArrayScanNext(player[0x88]);
            }
            return 0;
          }
          if (iVar4 == 0x49) {
            piVar8 = (int *)ArrayScanFirst(player[0x88]);
            while (piVar8 != (int *)0x0) {
              iVar2 = EvalExpressionI((int)player,param_2 + 0x18,1);
              iVar3 = *piVar8;
              iVar4 = EvalExpressionI((int)player,param_2 + 0x30,1);
              if ((*(int *)(iVar3 + 0xe10) == 0) &&
                 ((iVar4 == -1 || (iVar4 == *(int *)(iVar3 + 0x1064))))) {
                PlayerPowerSet(iVar3,iVar2 + **(int **)(iVar3 + 0x170));
              }
              piVar8 = (int *)ArrayScanNext(player[0x88]);
            }
            return 0;
          }
        }
      }
    }
LAB_080c35f1:
    sprintf((char *)(g + 0x81d2),"PlayerSCtrlApplyElem not recognised",piVar8,piVar8);
    ErrorExit();
    return 0;
  }
  if (iVar4 == 0xb) {
    iVar3 = EvalExpressionI((int)player,param_2 + 0x30,0);
    iVar2 = EvalExpressionI((int)player,param_2 + 0x24,0);
    iVar4 = EvalExpressionI((int)player,param_2 + 0x18,1);
    PlayerTakeDamage((int)player,-iVar4,iVar2,iVar3);
    return 0;
  }
  if (0xb < iVar4) {
    if (iVar4 == 0x16) {
      iVar3 = EvalExpressionI((int)player,param_2 + 0x18,0);
      if (iVar3 != 0) {
        fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
        player[0x67] = GHIDRA_F2I(int, ((float10)player[100] * fVar15 + GHIDRA_I2F(player[0x67])));
      }
      iVar3 = EvalExpressionI((int)player,param_2 + 0x24,0);
      if (iVar3 == 0) {
        return 0;
      }
      fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x48));
      player[0x68] = GHIDRA_F2I(int, (GHIDRA_I2F(player[0x68]) + fVar15));
      return 0;
    }
    if (iVar4 < 0x17) {
      if (iVar4 == 0xd) {
        iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
        PlayerPowerSet(param_3[1],iVar3 + **(int **)(param_3[1] + 0x170));
        return 0;
      }
      if (iVar4 < 0xd) {
        uVar7 = EvalExpressionI((int)player,param_2 + 0x18,1);
        PlayerPowerSet(param_3[1],uVar7);
        return 0;
      }
      if (iVar4 == 0x14) {
        iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
        player[899] = (uint)(iVar3 != 0);
        return 0;
      }
      if (iVar4 == 0x15) {
        iVar3 = EvalExpressionI((int)player,param_2 + 0x18,0);
        if (iVar3 != 0) {
          fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
          player[0x67] = GHIDRA_F2I(int, (GHIDRA_I2F(g[0x730f]) + fVar15 + 160.0));
        }
        iVar3 = EvalExpressionI((int)player,param_2 + 0x24,0);
        if (iVar3 == 0) {
          return 0;
        }
        fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x48));
        player[0x68] = GHIDRA_F2I(int, fVar15);
        return 0;
      }
    }
    else {
      if (iVar4 == 0x19) {
        iVar3 = EvalExpressionI((int)player,param_2 + 0x18,0);
        if (iVar3 != 0) {
          fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
          player[0x6d] = GHIDRA_F2I(int, ((float10)player[100] * fVar15 + GHIDRA_I2F(player[0x6d])));
        }
        iVar3 = EvalExpressionI((int)player,param_2 + 0x24,0);
        if (iVar3 == 0) {
          return 0;
        }
        fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x48));
        player[0x6e] = GHIDRA_F2I(int, (GHIDRA_I2F(player[0x6e]) + fVar15));
        return 0;
      }
      if (iVar4 < 0x1a) {
        if (iVar4 == 0x17) {
          iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
          player[0x388] = (uint)(iVar3 != 0);
          return 0;
        }
        if (iVar4 == 0x18) {
          iVar3 = EvalExpressionI((int)player,param_2 + 0x18,0);
          if (iVar3 != 0) {
            fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
            player[0x6d] = GHIDRA_F2I(int, ((float10)player[100] * fVar15));
          }
          iVar3 = EvalExpressionI((int)player,param_2 + 0x24,0);
          if (iVar3 == 0) {
            return 0;
          }
          fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x48));
          player[0x6e] = GHIDRA_F2I(int, fVar15);
          return 0;
        }
      }
      else {
        if (iVar4 == 0x1a) {
          iVar3 = EvalExpressionI((int)player,param_2 + 0x18,0);
          if (iVar3 != 0) {
            fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x3c));
            player[0x6d] = GHIDRA_F2I(int, (GHIDRA_I2F(player[0x6d]) * fVar15));
          }
          iVar3 = EvalExpressionI((int)player,param_2 + 0x24,0);
          if (iVar3 == 0) {
            return 0;
          }
          fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x48));
          player[0x6e] = GHIDRA_F2I(int, (GHIDRA_I2F(player[0x6e]) * fVar15));
          return 0;
        }
        if (iVar4 == 0x1b) {
          player[0x6e] = GHIDRA_F2I(int, (GHIDRA_I2F(player[0x6e]) + GHIDRA_I2F(player[0x4c])));
          return 0;
        }
      }
    }
    goto LAB_080c35f1;
  }
  if (iVar4 == 4) {
    iVar3 = EvalExpressionI((int)player,param_2 + 0x30,0);
    uVar7 = EvalExpressionI((int)player,param_2 + 0x24,1);
    if (iVar3 < 2) {
      if (-1 < (int)uVar7) {
        if (iVar3 == 0) {
          if ((int)uVar7 < 0x3c) goto LAB_080bfeb5;
        }
        else if ((int)uVar7 < 0x28) {
LAB_080bfeb5:
          if (iVar3 == 1) {
            fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x18));
            player[uVar7 + 0x3cc] = GHIDRA_F2I(int, fVar15);
            return 0;
          }
          if (iVar3 < 2) {
            if (iVar3 != 0) {
              return 0;
            }
            iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
            player[uVar7 + 0x390] = iVar3;
            return 0;
          }
          if (iVar3 == 3) {
            iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
            player[uVar7 + 0x3f4] = iVar3;
            return 0;
          }
          if (iVar3 != 4) {
            return 0;
          }
          fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x18));
          player[uVar7 + 0x3f9] = GHIDRA_F2I(int, fVar15);
          return 0;
        }
      }
      pcVar16 = "set var out of range (%i)";
LAB_080c02dc:
      VWarn((int)player,pcVar16,uVar7,iVar2);
      return 0;
    }
    if (uVar7 < 5) goto LAB_080bfeb5;
    pcVar16 = "set sysvar out of range (%i)";
    uVar9 = extraout_ECX;
    goto LAB_080c0001;
  }
  if (iVar4 < 5) {
    if (iVar4 == 1) {
      iVar2 = EvalExpressionI((int)player,param_2 + 0x18,1);
      if (iVar2 < 0) {
        iVar2 = 0;
        Warn((int)player,(int)&DAT_0827b4c0);
      }
      PlayerChangeState((int)player,iVar2);
      if ((((player[7] == 0) && (player[899] != 0)) && (player[0x380] - 1U < 2)) &&
         ((g[0x109d] != 0 &&
          (bVar1 = GameModeInPassiveFightScreen(), GHIDRA_ZEXT8(bVar1) == 0)))) {
        if ((iVar3 == 0) || (bVar1 = true, *(int *)(iVar3 + 0x158) == 0)) {
          bVar1 = false;
        }
        if (bVar1) {
          PlayerAutoTurn((int)player,iVar3,0);
        }
      }
      iVar3 = EvalExpressionI((int)player,param_2 + 0x24,1);
      if (iVar3 != -1) {
        player[899] = (uint)(iVar3 != 0);
      }
      iVar3 = EvalExpressionI((int)player,param_2 + 0x30,1);
      if (iVar3 == -1) {
        return 1;
      }
      if (iVar3 < 0) {
        iVar3 = 0;
        Warn((int)player,(int)&DAT_0827b480);
      }
LAB_080bfaf2:
      PlayerSelfAnim(player,iVar3);
      return 1;
    }
    if (iVar4 < 2) {
      if (iVar4 == 0) {
        return 0;
      }
    }
    else {
      if (iVar4 == 2) {
        player[0x2fc] = -1;
        player[0x2fb] = 0;
        player[0x4f0] = 0;
        player[0x259] = *player + 0x11b4;
        puVar13 = (undefined4 *)player[0x4ef];
        piVar8 = *(int **)(*player + 0x11cc);
        *puVar13 = piVar8;
        if (*(int *)(*piVar8 + 8) <= (int)puVar13[3]) {
          PlayerSelfAnim(player,0);
        }
        iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
        if (iVar3 < 0) {
          iVar3 = 0;
          Warn((int)player,(int)&DAT_0827b500);
        }
        PlayerChangeState((int)player,iVar3);
        iVar3 = EvalExpressionI((int)player,param_2 + 0x24,1);
        if (iVar3 != -1) {
          player[899] = (uint)(iVar3 != 0);
        }
        iVar3 = EvalExpressionI((int)player,param_2 + 0x30,1);
        if (iVar3 == -1) {
          return 1;
        }
        if (iVar3 < 0) {
          iVar3 = 0;
          Warn((int)player,(int)&DAT_0827b480);
        }
        goto LAB_080bfaf2;
      }
      if (iVar4 == 3) {
        PlayerTurnAround((int)player);
        return 0;
      }
    }
    goto LAB_080c35f1;
  }
  if (iVar4 == 6) {
    uVar7 = EvalExpressionI((int)player,param_2 + 0x24,1);
    if (uVar7 < 0x3c) {
      iVar4 = EvalExpressionI((int)player,param_2 + 0x18,1);
      iVar5 = EvalExpressionI((int)player,param_2 + 0x30,1);
      iVar3 = iVar4;
      iVar2 = iVar5;
      if (iVar5 < iVar4) {
        iVar3 = iVar5;
        iVar2 = iVar4;
        local_10c4 = iVar5;
      }
      lVar6 = random();
      player[uVar7 + 0x390] = lVar6 % ((iVar2 - iVar3) + 1) + iVar3;
      return 0;
    }
    pcVar16 = "randomized var out of range (%i)";
    goto LAB_080c02dc;
  }
  if (5 < iVar4) {
    if (iVar4 == 7) {
      iVar2 = EvalExpressionI((int)player,param_2 + 0x3c,0);
      iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
      iVar4 = EvalExpressionI((int)player,param_2 + 0x24,1);
      if (-1 < iVar3) {
        if (iVar2 == 0) {
          bVar14 = SBORROW4(iVar4,0x3b);
          iVar5 = -0x3b;
          bVar1 = iVar4 == 0x3b;
        }
        else {
          bVar14 = SBORROW4(iVar4,0x27);
          iVar5 = -0x27;
          bVar1 = iVar4 == 0x27;
        }
        if ((bVar1 || bVar14 != iVar4 + iVar5 < 0) && (iVar3 <= iVar4)) {
          if (iVar2 == 0) {
            iVar2 = EvalExpressionI((int)player,param_2 + 0x30,1);
            if (iVar2 == 0) {
              piVar8 = player + iVar3 + 0x390;
              for (uVar7 = (iVar4 - iVar3) * 4 + 4U >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                *piVar8 = 0;
                piVar8 = piVar8 + 1;
              }
              return 0;
            }
            for (; iVar3 <= iVar4; iVar3 = iVar3 + 1) {
              player[iVar3 + 0x390] = iVar2;
            }
            return 0;
          }
          fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x30));
          if (fVar15 == 0.0) {
            piVar8 = player + iVar3 + 0x3cc;
            for (uVar7 = (iVar4 - iVar3) * 4 + 4U >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
              *piVar8 = 0;
              piVar8 = piVar8 + 1;
            }
            return 0;
          }
          for (; iVar3 <= iVar4; iVar3 = iVar3 + 1) {
            player[iVar3 + 0x3cc] = GHIDRA_F2I(int, fVar15);
          }
          return 0;
        }
      }
      VWarn((int)player,"set illegal var range (%i-%i)",iVar3,iVar4);
      return 0;
    }
    if (iVar4 == 10) {
      uVar7 = EvalExpressionI((int)player,param_2 + 0x18,1);
      PlayerLifeSet((int)player,uVar7);
      return 0;
    }
    goto LAB_080c35f1;
  }
  iVar3 = EvalExpressionI((int)player,param_2 + 0x30,0);
  uVar7 = EvalExpressionI((int)player,param_2 + 0x24,1);
  if (1 < iVar3) {
    if (4 < uVar7) {
      pcVar16 = "set sysvar out of range (%i)";
      uVar17 = uVar7;
      goto LAB_080c001f;
    }
    goto LAB_080c0031;
  }
  if (-1 < (int)uVar7) {
    if (iVar3 == 0) {
      if ((int)uVar7 < 0x3c) goto LAB_080c0031;
    }
    else if ((int)uVar7 < 0x28) {
LAB_080c0031:
      if (iVar3 == 1) {
        fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x18));
        iVar3 = uVar7 * 4 + 0xf20;
        piVar8 = player + 4;
      }
      else {
        if (iVar3 < 2) {
          if (iVar3 != 0) {
            return 0;
          }
          iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
          player[uVar7 + 0x390] = player[uVar7 + 0x390] + iVar3;
          return 0;
        }
        if (iVar3 == 3) {
          iVar3 = EvalExpressionI((int)player,param_2 + 0x18,1);
          player[uVar7 + 0x3f4] = player[uVar7 + 0x3f4] + iVar3;
          return 0;
        }
        if (iVar3 != 4) {
          return 0;
        }
        fVar15 = EvalExpressionF(player,(int *)(param_2 + 0x18));
        iVar3 = uVar7 * 4 + 0xfd0;
        piVar8 = player + 5;
      }
LAB_080c33fe:
      *(float *)(iVar3 + (int)piVar8) = *(float *)(iVar3 + (int)piVar8) + fVar15;
      return 0;
    }
  }
  pcVar16 = "set var out of range (%i)";
  uVar9 = extraout_ECX_00;
LAB_080c0001:
  VWarn((int)player,pcVar16,uVar7,uVar9);
  return 0;
}
#undef local_10c4
#undef local_10c0
#undef local_10bc
#undef local_10ac
#undef local_108c
#undef local_8c
#undef local_6c
#undef local_4c
#undef local_24
#undef local_20

/* SCtrlRCElemFree @ 0x080c3630, 470 bytes */
undefined4 SCtrlRCElemFree(undefined4 *param_1)

{
  int iVar1;
  undefined4 extraout_EAX;
  undefined4 uStack_c;
  
  FreeExpArray((void *)*param_1);
  FreeExpression(param_1 + 6);
  FreeExpression(param_1 + 9);
  FreeExpression(param_1 + 0xc);
  FreeExpression(param_1 + 0xf);
  FreeExpression(param_1 + 0x12);
  FreeExpression(param_1 + 0x15);
  iVar1 = param_1[4];
  if (iVar1 == 0xd2) {
    AftImgParamsEFree((int *)param_1[0x18]);
  }
  else if (iVar1 < 0xd3) {
    if (iVar1 < 0x27) {
      if (iVar1 < 0x25) {
        if (iVar1 == 0x22) {
          PlaySndInfoFree((int *)param_1[0x18]);
        }
      }
      else {
        HitDefEFree(param_1[0x18]);
      }
    }
    else if (iVar1 == 0x78) {
      HitOverrideEFree(param_1[0x18]);
    }
    else if (iVar1 < 0x79) {
      if (iVar1 == 0x27) {
        ProjMakeInfoFree((int *)param_1[0x18]);
      }
    }
    else if (iVar1 == 200) {
      EnvShakeEFree((int *)param_1[0x18]);
    }
  }
  else if (iVar1 == 0xdc) {
    ExplodInfoFree((int *)param_1[0x18]);
  }
  else if (iVar1 < 0xdd) {
    if (iVar1 == 0xd6) {
      SuperPauseInfoFree((int *)param_1[0x18]);
    }
    else if (iVar1 == 0xd8) {
      PalFXEFree(param_1[0x18]);
    }
  }
  else if (iVar1 != 0xe6) {
    if (iVar1 < 0xe7) {
      if (iVar1 == 0xdf) {
        ExplodInfoFree((int *)param_1[0x18]);
      }
    }
    else if (iVar1 == 300) {
      HelperInfoFree(param_1[0x18]);
    }
  }
  if ((void *)param_1[0x18] == (void *)0x0) {
    return uStack_c;
  }
  free((void *)param_1[0x18]);
  return extraout_EAX;
}

