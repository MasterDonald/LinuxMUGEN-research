/*
 * state-i.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x080d0830-0x080d19a8, 15 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* SPopI @ 0x080d0830, 201 bytes
 * FIXUP: 1 data addresses written as literals replaced by data-image references */
char SPopI(int param_1,int *param_2)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = MyStackIdx;
  if (-1 < (int)MyStackIdx) {
    iVar1 = MyStack[(int)MyStackIdx];
    piVar2 = (int *)((int)MyStackIdx + -1);
    if (-1 < (int)piVar2) {
      MyStackIdx = (int *)((int)MyStackIdx + -2);
      if (iVar1 == 1) {
        *param_2 = (int)GHIDRA_FIST32(GHIDRA_I2F(MyStack[(int)piVar2]));
        Warn(param_1,(int)&DAT_0827cdc1);
        return '\x02';
      }
      *param_2 = MyStack[(int)piVar2];
      return (iVar1 == 4) * '\x02' + '\x01';
    }
  }
  MyStackIdx = piVar2;
  sprintf((char *)ErrorMessage,"Fatal: Expression stack underflow.",MyStackIdx,MyStackIdx);
  ErrorExit();
  return '\0';
}

/* SPopF @ 0x080d0900, 145 bytes
 * REVIEW: pid-unaff_ */
char SPopF(undefined4 param_1,float *param_2)

{
  int *piVar1;
  int unaff_EBX;
  
  piVar1 = MyStackIdx;
  if (-1 < (int)MyStackIdx) {
    unaff_EBX = MyStack[(int)MyStackIdx];
    piVar1 = (int *)((int)MyStackIdx + -1);
    if (-1 < (int)piVar1) {
      MyStackIdx = (int *)((int)MyStackIdx + -2);
      if (unaff_EBX == 1) {
        *param_2 = GHIDRA_I2F(MyStack[(int)piVar1]);
      }
      else {
        *param_2 = (float)MyStack[(int)piVar1];
      }
      return (unaff_EBX == 4) + '\x02';
    }
  }
  MyStackIdx = piVar1;
  sprintf((char *)ErrorMessage,"Fatal: Expression stack underflow.",unaff_EBX,unaff_EBX);
  ErrorExit();
  return '\0';
}

/* StackUnderflow @ 0x080d09a0, 26 bytes */
undefined4 StackUnderflow(void)

{
  undefined4 uVar1;
  
  sprintf((char *)ErrorMessage,"Fatal: Expression stack underflow.");
  uVar1 = ErrorExit();
  return uVar1;
}

/* ItoP_TPConstI @ 0x080d09c0, 109 bytes */
undefined4 ItoP_TPConstI(int param_1,char *param_2,int *param_3,int param_4,int param_5)

{
  byte *pbVar1;
  undefined4 uVar2;
  
  pbVar1 = (byte *)TPGetValue(param_1,param_2);
  ConstExpI(param_3,param_5);
  if (pbVar1 != (byte *)0x0) {
    uVar2 = InfixToPostfix(pbVar1,param_3,param_4,(undefined4 *)0x0,1);
    return uVar2;
  }
  return 1;
}

/* ItoP_TPConstF @ 0x080d0a30, 109 bytes */
undefined4 ItoP_TPConstF(int param_1,char *param_2,int *param_3,int param_4,int param_5)

{
  byte *pbVar1;
  undefined4 uVar2;
  
  pbVar1 = (byte *)TPGetValue(param_1,param_2);
  ConstExpF(param_3,param_5);
  if (pbVar1 != (byte *)0x0) {
    uVar2 = InfixToPostfix(pbVar1,param_3,param_4,(undefined4 *)0x0,2);
    return uVar2;
  }
  return 1;
}

/* SCtrlReadExpList @ 0x080d0aa0, 484 bytes
 * FIXUP: varargs: replaced 1 &stack0x.. with a va_list started after param_4
 * FIXUP: frame emulation: 7 stack locals placed at their original offsets in a 0x40-byte frame (a local's address escapes, see apply_frame_emulation) */
byte * SCtrlReadExpList(byte *param_1,char *param_2,int param_3,undefined4 *param_4,...)

{
  va_list ghidra_va;
  va_start(ghidra_va, param_4);
  char cVar1;
  byte bVar2;
  int *piVar3;
  size_t sVar4;
  int iVar5;
  byte *pbVar6;
  byte *pbVar7;
  unsigned char ghidra_frame[0x40] __attribute__((aligned(16)));
#define local_3c (*(undefined4 **)(ghidra_frame + 0x4))
#define local_38 (*(int *)(ghidra_frame + 0x8))
#define local_34 (*(int *)(ghidra_frame + 0xc))
#define local_30 (*(byte **)(ghidra_frame + 0x10))
#define local_2c (*(int *)(ghidra_frame + 0x14))
#define local_28 (*(int *)(ghidra_frame + 0x18))
#define local_24 (*(int *)(ghidra_frame + 0x1c))
  
  local_34 = 0;
  local_38 = 0;
  if (param_1 != (byte *)0x0) {
    for (iVar5 = 0; sVar4 = strlen(param_2), iVar5 < (int)sVar4; iVar5 = iVar5 + 1) {
      cVar1 = param_2[iVar5];
      if (((cVar1 == 'n') || (cVar1 == 'i')) || (cVar1 == 'f')) {
        local_34 = local_34 + 1;
      }
    }
    if ((param_2[local_34] == ':') || (param_2[local_34] == '\0')) {
      pbVar6 = (byte *)0x0;
      pbVar7 = param_1;
      if (0 < local_34) {
        local_3c = ghidra_va;
        do {
          bVar2 = pbVar6[(int)param_2];
          if (bVar2 == 0x69) {
            local_38 = 1;
          }
          else if ((char)bVar2 < 'j') {
            if (bVar2 == 0x66) {
              local_38 = 2;
            }
            else {
LAB_080d0b80:
              ErrorExit();
            }
          }
          else {
            if (bVar2 != 0x6e) goto LAB_080d0b80;
            local_38 = 0;
          }
          piVar3 = (int *)*local_3c;
          local_2c = *piVar3;
          local_28 = piVar3[1];
          local_24 = piVar3[2];
          iVar5 = InfixToPostfix(pbVar7,piVar3,param_3,&local_30,local_38);
          if (iVar5 == 0) break;
          bVar2 = *local_30;
          if (bVar2 == 0x2c) {
            if ((int)pbVar6 < local_34 + -1) {
              local_30 = local_30 + 1;
            }
          }
          else if (bVar2 != 0) {
            iVar5 = local_34;
            if (pbVar6 == (byte *)(local_34 + -1)) {
              do {
                iVar5 = iVar5 + 1;
              } while (param_1[iVar5] != bVar2);
              if (param_1[iVar5] != 0) goto LAB_080d0c46;
            }
            FreeExpression(piVar3);
            *piVar3 = local_2c;
            piVar3[1] = local_28;
            piVar3[2] = local_24;
            break;
          }
LAB_080d0c46:
          pbVar6 = pbVar6 + 1;
          pbVar7 = local_30;
          local_3c = local_3c + 1;
        } while ((int)pbVar6 < local_34);
      }
      bVar2 = *(byte *)(__ctype_b + 1 + (char)*pbVar7 * 2);
      while ((bVar2 & 0x20) != 0) {
        pbVar7 = pbVar7 + 1;
        bVar2 = *(byte *)(__ctype_b + 1 + (char)*pbVar7 * 2);
      }
      if (param_4 == (undefined4 *)0x0) {
        return pbVar6;
      }
      *param_4 = pbVar7;
      return pbVar6;
    }
  }
  return (byte *)0x0;
}
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_24

/* SCtrlReadExpListArray @ 0x080d0c90, 493 bytes
 * REVIEW: type-prop
 * FIXUP: frame emulation: 4 stack locals placed at their original offsets in a 0x20-byte frame (a local's address escapes, see apply_frame_emulation) */
/* WARNING: Type propagation algorithm not settling */

int SCtrlReadExpListArray
              (byte *param_1,char *param_2,int param_3,undefined4 *param_4,int param_5,int param_6,
              int *param_7,int param_8)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  size_t sVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  byte *pbVar8;
  unsigned char ghidra_frame[0x20] __attribute__((aligned(16)));
#define local_20 (*(char **)(ghidra_frame + 0x0))
#define local_1c (*(int *)(ghidra_frame + 0x4))
#define local_18 (*(int *)(ghidra_frame + 0x8))
#define local_14 (*(byte **)(ghidra_frame + 0xc))
  
  iVar7 = 0;
  local_18 = 0;
  local_1c = 0;
  local_20 = (char *)0x0;
  if (param_1 != (byte *)0x0) {
    for (; sVar4 = strlen(param_2), iVar7 < (int)sVar4; iVar7 = iVar7 + 1) {
      cVar1 = param_2[iVar7];
      if (((cVar1 == 'n') || (cVar1 == 'i')) || (cVar1 == 'f')) {
        local_18 = local_18 + 1;
      }
    }
    if ((param_2[local_18] == ':') || (param_2[local_18] == '\0')) {
      iVar7 = 0;
      pbVar8 = param_1;
      if (0 < local_18) {
        do {
          cVar1 = param_2[iVar7];
          if (cVar1 == 'i') {
            local_1c = 1;
          }
          else if (cVar1 < 'j') {
            if (cVar1 == 'f') {
              local_1c = 2;
            }
            else {
LAB_080d0d60:
              ErrorExit();
            }
          }
          else {
            if (cVar1 != 'n') goto LAB_080d0d60;
            local_1c = 0;
          }
          pcVar5 = InfToPostArray(pbVar8,(float *)(param_5 + (int)local_20 * 4),local_20 + param_6,
                                  param_3,(byte *)(param_8 - (int)local_20),&local_14,local_1c);
          if (pcVar5 == (char *)0x0) break;
          local_20 = local_20 + (int)pcVar5;
          bVar2 = *local_14;
          if (bVar2 == 0x2c) {
            if (iVar7 < local_18 + -1) {
              local_14 = local_14 + 1;
            }
          }
          else if (bVar2 != 0) {
            if (iVar7 != local_18 + -1) {
              local_20 = local_20 + -(int)pcVar5;
              break;
            }
            bVar3 = param_1[local_18];
            iVar6 = local_18;
            while (bVar3 != bVar2) {
              iVar6 = iVar6 + 1;
              bVar3 = param_1[iVar6];
            }
            if (bVar3 == 0) {
              local_20 = local_20 + -(int)pcVar5;
              break;
            }
          }
          iVar7 = iVar7 + 1;
          pbVar8 = local_14;
        } while (iVar7 < local_18);
      }
      bVar2 = *(byte *)(__ctype_b + 1 + (char)*pbVar8 * 2);
      while ((bVar2 & 0x20) != 0) {
        pbVar8 = pbVar8 + 1;
        bVar2 = *(byte *)(__ctype_b + 1 + (char)*pbVar8 * 2);
      }
      if (param_4 != (undefined4 *)0x0) {
        *param_4 = pbVar8;
      }
      *param_7 = (int)local_20;
      return iVar7;
    }
  }
  return 0;
}
#undef local_20
#undef local_1c
#undef local_18
#undef local_14

/* ParsePosType @ 0x080d0e80, 84 bytes */
int ParsePosType(char *param_1)

{
  switch(*(undefined4 *)(__ctype_tolower + *param_1 * 4)) {
  case 0x62:
    return 2;
  default:
    return -1;
  case 0x66:
    return 1;
  case 0x6c:
    return 3;
  case 0x70:
    return (uint)(*(int *)(__ctype_tolower + param_1[1] * 4) == 0x32) * 5;
  case 0x72:
    return 4;
  }
}

/* ParseSpecialFlag @ 0x080d0ee0, 1025 bytes
 * FIXUP: call to 0x08102020 (Ghidra label gcc2_compiled.) renamed to its symbol _alemu_strlwr
 * FIXUP: 1 data addresses written as literals replaced by data-image references
 * FIXUP: 2 dead flag initialisations of inlined repz cmpsb loops set to constants
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x60-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 ParseSpecialFlag(char *param_1,undefined4 *param_2,undefined4 *param_3)

{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  unsigned char ghidra_frame[0x60] __attribute__((aligned(16)));
#define local_5c (*(byte (*)[76])(ghidra_frame + 0x4))
  
  strcpy((char *)local_5c,param_1);
  _alemu_strlwr((char *)local_5c);
  bVar4 = 0;  /* dead flag (repz cmpsb, count 6) */
  bVar6 = 0;  /* dead flag (repz cmpsb, count 6) */
  iVar1 = 6;
  pbVar2 = local_5c;
  pbVar3 = (byte *)"intro";
  do {
    if (iVar1 == 0) break;
    iVar1 = iVar1 + -1;
    bVar4 = *pbVar2 < *pbVar3;
    bVar6 = *pbVar2 == *pbVar3;
    pbVar2 = pbVar2 + 1;
    pbVar3 = pbVar3 + 1;
  } while (bVar6);
  bVar5 = (!bVar4 && !bVar6) < bVar4;
  bVar4 = (!bVar4 && !bVar6) == bVar4;
  if (bVar4) {
    *param_2 = 0;
    *param_3 = 0;
  }
  else {
    iVar1 = 0xd;
    pbVar2 = local_5c;
    pbVar3 = (byte *)"roundnotover";
    do {
      if (iVar1 == 0) break;
      iVar1 = iVar1 + -1;
      bVar5 = *pbVar2 < *pbVar3;
      bVar4 = *pbVar2 == *pbVar3;
      pbVar2 = pbVar2 + 1;
      pbVar3 = pbVar3 + 1;
    } while (bVar4);
    bVar6 = (!bVar5 && !bVar4) < bVar5;
    bVar4 = (!bVar5 && !bVar4) == bVar5;
    if (bVar4) {
      *param_2 = 1;
      *param_3 = 0;
    }
    else {
      iVar1 = 5;
      pbVar2 = local_5c;
      pbVar3 = &DAT_0827cdf1;
      do {
        if (iVar1 == 0) break;
        iVar1 = iVar1 + -1;
        bVar6 = *pbVar2 < *pbVar3;
        bVar4 = *pbVar2 == *pbVar3;
        pbVar2 = pbVar2 + 1;
        pbVar3 = pbVar3 + 1;
      } while (bVar4);
      bVar5 = (!bVar6 && !bVar4) < bVar6;
      bVar4 = (!bVar6 && !bVar4) == bVar6;
      if (bVar4) {
        *param_2 = 2;
        *param_3 = 0;
      }
      else {
        iVar1 = 8;
        pbVar2 = local_5c;
        pbVar3 = &DAT_0827cdf6;
        do {
          if (iVar1 == 0) break;
          iVar1 = iVar1 + -1;
          bVar5 = *pbVar2 < *pbVar3;
          bVar4 = *pbVar2 == *pbVar3;
          pbVar2 = pbVar2 + 1;
          pbVar3 = pbVar3 + 1;
        } while (bVar4);
        bVar6 = (!bVar5 && !bVar4) < bVar5;
        bVar4 = (!bVar5 && !bVar4) == bVar5;
        if (bVar4) {
          *param_2 = 3;
          *param_3 = 0;
        }
        else {
          iVar1 = 9;
          pbVar2 = local_5c;
          pbVar3 = (byte *)"nokoslow";
          do {
            if (iVar1 == 0) break;
            iVar1 = iVar1 + -1;
            bVar6 = *pbVar2 < *pbVar3;
            bVar4 = *pbVar2 == *pbVar3;
            pbVar2 = pbVar2 + 1;
            pbVar3 = pbVar3 + 1;
          } while (bVar4);
          bVar5 = (!bVar6 && !bVar4) < bVar6;
          bVar4 = (!bVar6 && !bVar4) == bVar6;
          if (bVar4) {
            *param_2 = 4;
            *param_3 = 0;
          }
          else {
            iVar1 = 8;
            pbVar2 = local_5c;
            pbVar3 = (byte *)"nomusic";
            do {
              if (iVar1 == 0) break;
              iVar1 = iVar1 + -1;
              bVar5 = *pbVar2 < *pbVar3;
              bVar4 = *pbVar2 == *pbVar3;
              pbVar2 = pbVar2 + 1;
              pbVar3 = pbVar3 + 1;
            } while (bVar4);
            bVar6 = (!bVar5 && !bVar4) < bVar5;
            bVar4 = (!bVar5 && !bVar4) == bVar5;
            if (bVar4) {
              *param_2 = 5;
              *param_3 = 0;
            }
            else {
              iVar1 = 0xf;
              pbVar2 = local_5c;
              pbVar3 = (byte *)"globalnoshadow";
              do {
                if (iVar1 == 0) break;
                iVar1 = iVar1 + -1;
                bVar6 = *pbVar2 < *pbVar3;
                bVar4 = *pbVar2 == *pbVar3;
                pbVar2 = pbVar2 + 1;
                pbVar3 = pbVar3 + 1;
              } while (bVar4);
              bVar5 = (!bVar6 && !bVar4) < bVar6;
              bVar4 = (!bVar6 && !bVar4) == bVar6;
              if (bVar4) {
                *param_2 = 6;
                *param_3 = 0;
              }
              else {
                iVar1 = 0xc;
                pbVar2 = local_5c;
                pbVar3 = (byte *)"timerfreeze";
                do {
                  if (iVar1 == 0) break;
                  iVar1 = iVar1 + -1;
                  bVar5 = *pbVar2 < *pbVar3;
                  bVar4 = *pbVar2 == *pbVar3;
                  pbVar2 = pbVar2 + 1;
                  pbVar3 = pbVar3 + 1;
                } while (bVar4);
                bVar6 = (!bVar5 && !bVar4) < bVar5;
                bVar4 = (!bVar5 && !bVar4) == bVar5;
                if (bVar4) {
                  *param_2 = 7;
                  *param_3 = 0;
                }
                else {
                  iVar1 = 0xd;
                  pbVar2 = local_5c;
                  pbVar3 = (byte *)"nobardisplay";
                  do {
                    if (iVar1 == 0) break;
                    iVar1 = iVar1 + -1;
                    bVar6 = *pbVar2 < *pbVar3;
                    bVar4 = *pbVar2 == *pbVar3;
                    pbVar2 = pbVar2 + 1;
                    pbVar3 = pbVar3 + 1;
                  } while (bVar4);
                  bVar5 = (!bVar6 && !bVar4) < bVar6;
                  bVar4 = (!bVar6 && !bVar4) == bVar6;
                  if (bVar4) {
                    *param_2 = 8;
                    *param_3 = 0;
                  }
                  else {
                    iVar1 = 5;
                    pbVar2 = local_5c;
                    pbVar3 = &DAT_0827ce2f;
                    do {
                      if (iVar1 == 0) break;
                      iVar1 = iVar1 + -1;
                      bVar5 = *pbVar2 < *pbVar3;
                      bVar4 = *pbVar2 == *pbVar3;
                      pbVar2 = pbVar2 + 1;
                      pbVar3 = pbVar3 + 1;
                    } while (bVar4);
                    bVar6 = (!bVar5 && !bVar4) < bVar5;
                    bVar4 = (!bVar5 && !bVar4) == bVar5;
                    if (bVar4) {
                      *param_2 = 9;
                      *param_3 = 0;
                    }
                    else {
                      iVar1 = 5;
                      pbVar2 = local_5c;
                      pbVar3 = &DAT_0827ce34;
                      do {
                        if (iVar1 == 0) break;
                        iVar1 = iVar1 + -1;
                        bVar6 = *pbVar2 < *pbVar3;
                        bVar4 = *pbVar2 == *pbVar3;
                        pbVar2 = pbVar2 + 1;
                        pbVar3 = pbVar3 + 1;
                      } while (bVar4);
                      bVar5 = (!bVar6 && !bVar4) < bVar6;
                      bVar4 = (!bVar6 && !bVar4) == bVar6;
                      if (bVar4) {
                        *param_2 = 10;
                        *param_3 = 0;
                      }
                      else {
                        iVar1 = 0xd;
                        pbVar2 = local_5c;
                        pbVar3 = (byte *)"nostandguard";
                        do {
                          if (iVar1 == 0) break;
                          iVar1 = iVar1 + -1;
                          bVar5 = *pbVar2 < *pbVar3;
                          bVar4 = *pbVar2 == *pbVar3;
                          pbVar2 = pbVar2 + 1;
                          pbVar3 = pbVar3 + 1;
                        } while (bVar4);
                        bVar6 = (!bVar5 && !bVar4) < bVar5;
                        bVar4 = (!bVar5 && !bVar4) == bVar5;
                        if (bVar4) {
                          *param_2 = 0;
                          *param_3 = 1;
                        }
                        else {
                          iVar1 = 0xe;
                          pbVar2 = local_5c;
                          pbVar3 = (byte *)"nocrouchguard";
                          do {
                            if (iVar1 == 0) break;
                            iVar1 = iVar1 + -1;
                            bVar6 = *pbVar2 < *pbVar3;
                            bVar4 = *pbVar2 == *pbVar3;
                            pbVar2 = pbVar2 + 1;
                            pbVar3 = pbVar3 + 1;
                          } while (bVar4);
                          bVar5 = (!bVar6 && !bVar4) < bVar6;
                          bVar4 = (!bVar6 && !bVar4) == bVar6;
                          if (bVar4) {
                            *param_2 = 1;
                            *param_3 = 1;
                          }
                          else {
                            iVar1 = 0xb;
                            pbVar2 = local_5c;
                            pbVar3 = (byte *)"noairguard";
                            do {
                              if (iVar1 == 0) break;
                              iVar1 = iVar1 + -1;
                              bVar5 = *pbVar2 < *pbVar3;
                              bVar4 = *pbVar2 == *pbVar3;
                              pbVar2 = pbVar2 + 1;
                              pbVar3 = pbVar3 + 1;
                            } while (bVar4);
                            bVar6 = (!bVar5 && !bVar4) < bVar5;
                            bVar4 = (!bVar5 && !bVar4) == bVar5;
                            if (bVar4) {
                              *param_2 = 2;
                              *param_3 = 1;
                            }
                            else {
                              iVar1 = 0xb;
                              pbVar2 = local_5c;
                              pbVar3 = (byte *)"noautoturn";
                              do {
                                if (iVar1 == 0) break;
                                iVar1 = iVar1 + -1;
                                bVar6 = *pbVar2 < *pbVar3;
                                bVar4 = *pbVar2 == *pbVar3;
                                pbVar2 = pbVar2 + 1;
                                pbVar3 = pbVar3 + 1;
                              } while (bVar4);
                              bVar5 = (!bVar6 && !bVar4) < bVar6;
                              bVar4 = (!bVar6 && !bVar4) == bVar6;
                              if (bVar4) {
                                *param_2 = 3;
                                *param_3 = 1;
                              }
                              else {
                                iVar1 = 9;
                                pbVar2 = local_5c;
                                pbVar3 = (byte *)(int)&DAT_0827ce0d;
                                do {
                                  if (iVar1 == 0) break;
                                  iVar1 = iVar1 + -1;
                                  bVar5 = *pbVar2 < *pbVar3;
                                  bVar4 = *pbVar2 == *pbVar3;
                                  pbVar2 = pbVar2 + 1;
                                  pbVar3 = pbVar3 + 1;
                                } while (bVar4);
                                bVar6 = (!bVar5 && !bVar4) < bVar5;
                                bVar4 = (!bVar5 && !bVar4) == bVar5;
                                if (bVar4) {
                                  *param_2 = 4;
                                  *param_3 = 1;
                                }
                                else {
                                  iVar1 = 0xe;
                                  pbVar2 = local_5c;
                                  pbVar3 = (byte *)"nojugglecheck";
                                  do {
                                    if (iVar1 == 0) break;
                                    iVar1 = iVar1 + -1;
                                    bVar6 = *pbVar2 < *pbVar3;
                                    bVar4 = *pbVar2 == *pbVar3;
                                    pbVar2 = pbVar2 + 1;
                                    pbVar3 = pbVar3 + 1;
                                  } while (bVar4);
                                  bVar5 = (!bVar6 && !bVar4) < bVar6;
                                  bVar4 = (!bVar6 && !bVar4) == bVar6;
                                  if (bVar4) {
                                    *param_2 = 5;
                                    *param_3 = 1;
                                  }
                                  else {
                                    iVar1 = 7;
                                    pbVar2 = local_5c;
                                    pbVar3 = (byte *)"nowalk";
                                    do {
                                      if (iVar1 == 0) break;
                                      iVar1 = iVar1 + -1;
                                      bVar5 = *pbVar2 < *pbVar3;
                                      bVar4 = *pbVar2 == *pbVar3;
                                      pbVar2 = pbVar2 + 1;
                                      pbVar3 = pbVar3 + 1;
                                    } while (bVar4);
                                    bVar6 = (!bVar5 && !bVar4) < bVar5;
                                    bVar4 = (!bVar5 && !bVar4) == bVar5;
                                    if (bVar4) {
                                      *param_2 = 6;
                                      *param_3 = 1;
                                    }
                                    else {
                                      iVar1 = 0xc;
                                      pbVar2 = local_5c;
                                      pbVar3 = (byte *)"unguardable";
                                      do {
                                        if (iVar1 == 0) break;
                                        iVar1 = iVar1 + -1;
                                        bVar6 = *pbVar2 < *pbVar3;
                                        bVar4 = *pbVar2 == *pbVar3;
                                        pbVar2 = pbVar2 + 1;
                                        pbVar3 = pbVar3 + 1;
                                      } while (bVar4);
                                      bVar5 = (!bVar6 && !bVar4) < bVar6;
                                      bVar4 = (!bVar6 && !bVar4) == bVar6;
                                      if (bVar4) {
                                        *param_2 = 7;
                                        *param_3 = 1;
                                      }
                                      else {
                                        iVar1 = 10;
                                        pbVar2 = local_5c;
                                        pbVar3 = (byte *)"invisible";
                                        do {
                                          if (iVar1 == 0) break;
                                          iVar1 = iVar1 + -1;
                                          bVar5 = *pbVar2 < *pbVar3;
                                          bVar4 = *pbVar2 == *pbVar3;
                                          pbVar2 = pbVar2 + 1;
                                          pbVar3 = pbVar3 + 1;
                                        } while (bVar4);
                                        if ((!bVar5 && !bVar4) != bVar5) {
                                          return 0;
                                        }
                                        *param_2 = 8;
                                        *param_3 = 1;
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
  return 1;
}
#undef local_5c

/* ParseAnim @ 0x080d12f0, 119 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x10-byte frame (a local's address escapes, see apply_frame_emulation) */
bool ParseAnim(byte *param_1,int *param_2,undefined4 *param_3,int param_4)

{
  int iVar1;
  byte *pbVar2;
  char *in_ECX;
  bool bVar3;
  unsigned char ghidra_frame[0x10] __attribute__((aligned(16)));
#define local_8 (*(char **)(ghidra_frame + 0x8))
  
  if (param_1 == (byte *)0x0) {
    return true;
  }
  iVar1 = *(int *)(__ctype_tolower + (char)*param_1 * 4);
  if (iVar1 == 0x66) {
    *param_3 = 1;
  }
  else {
    if (iVar1 != 0x73) goto LAB_080d132f;
    *param_3 = 0;
  }
  param_1 = param_1 + 1;
LAB_080d132f:
  local_8 = in_ECX;
  pbVar2 = SCtrlReadExpList(param_1,"i",param_4,&local_8,param_2);
  if (pbVar2 == (byte *)0x0) {
    bVar3 = false;
  }
  else {
    bVar3 = *local_8 == '\0';
  }
  return bVar3;
}
#undef local_8

/* ParseSnd @ 0x080d1370, 128 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x10-byte frame (a local's address escapes, see apply_frame_emulation) */
uint ParseSnd(byte *param_1,int *param_2,int *param_3,undefined4 *param_4,int param_5)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  unsigned char ghidra_frame[0x10] __attribute__((aligned(16)));
#define local_8 (*(char **)(ghidra_frame + 0x8))
  
  if (param_1 == (byte *)0x0) {
    return 1;
  }
  iVar1 = *(int *)(__ctype_tolower + (char)*param_1 * 4);
  if (iVar1 == 0x66) {
    *param_4 = 1;
  }
  else {
    if (iVar1 != 0x73) goto LAB_080d13af;
    *param_4 = 0;
  }
  param_1 = param_1 + 1;
LAB_080d13af:
  pbVar2 = SCtrlReadExpList(param_1,"ii",param_5,&local_8,param_2,param_3);
  if (pbVar2 == (byte *)0x0) {
    uVar3 = 0;
  }
  else {
    uVar3 = (uint)(*local_8 == '\0');
  }
  return uVar3;
}
#undef local_8

/* ParseVel @ 0x080d13f0, 306 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x10-byte frame (a local's address escapes, see apply_frame_emulation) */
bool ParseVel(byte *param_1,int *param_2,int *param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  bool bVar5;
  unsigned char ghidra_frame[0x10] __attribute__((aligned(16)));
#define local_10 (*(byte **)(ghidra_frame + 0x0))
  
  if (param_1 == (byte *)0x0) {
    return true;
  }
  if ((*(int *)(__ctype_tolower + (char)*param_1 * 4) == 0x6e) &&
     ((((*(byte *)(__ctype_b + 1 + (char)param_1[1] * 2) & 0x20) != 0 || (param_1[1] == 0x2c)) ||
      (param_1[1] == 0)))) {
    ConstExpF(param_2,-0x39001000);
    pbVar3 = param_1 + 1;
LAB_080d1471:
    if (*pbVar3 != 0x2c) {
      return *pbVar3 == 0;
    }
    do {
      pbVar4 = pbVar3;
      pbVar3 = pbVar4 + 1;
    } while ((*(byte *)(__ctype_b + 1 + (char)*pbVar3 * 2) & 0x20) != 0);
    if ((*(int *)(__ctype_tolower + (char)*pbVar3 * 4) == 0x6e) &&
       (((*(byte *)(__ctype_b + 1 + (char)pbVar4[2] * 2) & 0x20) != 0 || (pbVar4[2] == 0)))) {
      ConstExpF(param_3,-0x39001000);
      local_10 = pbVar4 + 2;
    }
    else {
      iVar2 = InfixToPostfix(pbVar3,param_3,param_4,&local_10,2);
      if (iVar2 == 0) goto LAB_080d14f0;
    }
    bVar1 = *(byte *)(__ctype_b + 1 + (char)*local_10 * 2);
    while ((bVar1 & 0x20) != 0) {
      local_10 = local_10 + 1;
      bVar1 = *(byte *)(__ctype_b + 1 + (char)*local_10 * 2);
    }
    bVar5 = *local_10 == 0;
  }
  else {
    iVar2 = InfixToPostfix(param_1,param_2,param_4,&local_10,2);
    pbVar3 = local_10;
    if (iVar2 != 0) goto LAB_080d1471;
LAB_080d14f0:
    bVar5 = false;
  }
  return bVar5;
}
#undef local_10

/* ParseHitAttr @ 0x080d1530, 796 bytes
 * REVIEW: type-prop */
/* WARNING: Type propagation algorithm not settling */

uint ParseHitAttr(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  uint uVar5;
  
  uVar5 = 0;
  if (param_1 == 0) {
    return 0xffffffff;
  }
  iVar2 = (int)*(char *)param_1;
  iVar3 = 0;
  bVar1 = *(byte *)(__ctype_b + 1 + iVar2 * 2);
  while ((bVar1 & 4) != 0) {
    iVar2 = *(int *)(__ctype_tolower + iVar2 * 4);
    if (iVar2 == 99) {
      uVar5 = uVar5 | 2;
    }
    else if (iVar2 < 100) {
      if (iVar2 != 0x61) {
        return 0xffffffff;
      }
      uVar5 = uVar5 | 4;
    }
    else {
      if (iVar2 != 0x73) {
        return 0xffffffff;
      }
      uVar5 = uVar5 | 1;
    }
    iVar3 = iVar3 + 1;
    iVar2 = (int)*(char *)(iVar3 + param_1);
    bVar1 = *(byte *)(__ctype_b + 1 + iVar2 * 2);
  }
  cVar4 = *(char *)(iVar3 + param_1);
  while (cVar4 != '\0') {
    if ((*(byte *)(__ctype_b + 1 + *(char *)(iVar3 + param_1) * 2) & 0x20) != 0) {
      do {
        iVar3 = iVar3 + 1;
      } while ((*(byte *)(__ctype_b + 1 + *(char *)(iVar3 + param_1) * 2) & 0x20) != 0);
      cVar4 = *(char *)(iVar3 + param_1);
    }
    if (cVar4 != ',') break;
    iVar3 = iVar3 + 1;
    iVar2 = (int)*(char *)(iVar3 + param_1);
    bVar1 = *(byte *)(__ctype_b + 1 + iVar2 * 2);
    while ((bVar1 & 0x20) != 0) {
      iVar3 = iVar3 + 1;
      iVar2 = (int)*(char *)(iVar3 + param_1);
      bVar1 = *(byte *)(__ctype_b + 1 + iVar2 * 2);
    }
    iVar2 = *(int *)(__ctype_tolower + iVar2 * 4);
    if (iVar2 == 0x68) {
      iVar2 = *(int *)(__ctype_tolower + *(char *)(iVar3 + 1 + param_1) * 4);
      if (iVar2 == 0x61) {
        uVar5 = uVar5 | 0x20;
        iVar3 = iVar3 + 1;
      }
      else if (iVar2 < 0x62) {
        if (iVar2 != 0x20) {
          if (iVar2 < 0x21) goto joined_r0x080d1752;
joined_r0x080d1769:
          if (iVar2 != 0x2c) {
            return 0xffffffff;
          }
        }
LAB_080d1820:
        uVar5 = uVar5 | 0x920;
      }
      else if (iVar2 == 0x70) {
        uVar5 = uVar5 | 0x800;
        iVar3 = iVar3 + 1;
      }
      else {
        if (iVar2 != 0x74) {
          return 0xffffffff;
        }
        uVar5 = uVar5 | 0x100;
        iVar3 = iVar3 + 1;
      }
    }
    else if (iVar2 < 0x69) {
      if (iVar2 != 0x61) {
        return 0xffffffff;
      }
      iVar2 = *(int *)(__ctype_tolower + *(char *)(iVar3 + 1 + param_1) * 4);
      if (iVar2 == 0x61) {
        uVar5 = uVar5 | 0x38;
        iVar3 = iVar3 + 1;
      }
      else {
        if (iVar2 < 0x62) {
          if (iVar2 != 0x20) {
            if (0x20 < iVar2) goto joined_r0x080d1769;
joined_r0x080d1752:
            if ((iVar2 != 0) && (iVar2 != 9)) {
              return 0xffffffff;
            }
          }
          goto LAB_080d1820;
        }
        if (iVar2 == 0x70) {
          uVar5 = uVar5 | 0xe00;
          iVar3 = iVar3 + 1;
        }
        else {
          if (iVar2 != 0x74) {
            return 0xffffffff;
          }
          uVar5 = uVar5 | 0x1c0;
          iVar3 = iVar3 + 1;
        }
      }
    }
    else if (iVar2 == 0x6e) {
      iVar2 = *(int *)(__ctype_tolower + *(char *)(iVar3 + 1 + param_1) * 4);
      if (iVar2 == 0x61) {
        uVar5 = uVar5 | 8;
        iVar3 = iVar3 + 1;
      }
      else if (iVar2 < 0x62) {
        if (iVar2 != 0x20) {
          if (iVar2 < 0x21) {
            if ((iVar2 != 0) && (iVar2 != 9)) {
              return 0xffffffff;
            }
          }
          else if (iVar2 != 0x2c) {
            return 0xffffffff;
          }
        }
        uVar5 = uVar5 | 0x248;
      }
      else if (iVar2 == 0x70) {
        uVar5 = uVar5 | 0x200;
        iVar3 = iVar3 + 1;
      }
      else {
        if (iVar2 != 0x74) {
          return 0xffffffff;
        }
        uVar5 = uVar5 | 0x40;
        iVar3 = iVar3 + 1;
      }
    }
    else {
      if (iVar2 != 0x73) {
        return 0xffffffff;
      }
      iVar2 = *(int *)(__ctype_tolower + *(char *)(iVar3 + 1 + param_1) * 4);
      if (iVar2 == 0x61) {
        uVar5 = uVar5 | 0x10;
        iVar3 = iVar3 + 1;
      }
      else if (iVar2 < 0x62) {
        if (iVar2 != 0x20) {
          if (iVar2 < 0x21) {
            if ((iVar2 != 0) && (iVar2 != 9)) {
              return 0xffffffff;
            }
          }
          else if (iVar2 != 0x2c) {
            return 0xffffffff;
          }
        }
        uVar5 = uVar5 | 0x490;
      }
      else if (iVar2 == 0x70) {
        uVar5 = uVar5 | 0x400;
        iVar3 = iVar3 + 1;
      }
      else {
        if (iVar2 != 0x74) {
          return 0xffffffff;
        }
        uVar5 = uVar5 | 0x80;
        iVar3 = iVar3 + 1;
      }
    }
    iVar3 = iVar3 + 1;
    cVar4 = *(char *)(iVar3 + param_1);
  }
  if (param_2 != 0) {
    *(int *)param_2 = iVar3 + param_1;
  }
  return uVar5;
}

/* ParseHitFlag @ 0x080d1850, 130 bytes */
uint ParseHitFlag(char *param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = 0;
  uVar3 = 2;
  cVar1 = *param_1;
  while (cVar1 != '\0') {
    switch(*(undefined4 *)(__ctype_tolower + param_1[iVar2] * 4)) {
    case 0x2b:
      uVar3 = uVar3 | 0x100;
      break;
    case 0x2d:
      uVar3 = uVar3 & 0xfffffffd;
      break;
    case 0x61:
      uVar3 = uVar3 | 0x10;
      break;
    case 100:
      uVar3 = uVar3 | 0x40;
      break;
    case 0x66:
      uVar3 = uVar3 | 0x20;
      break;
    case 0x68:
      uVar3 = uVar3 | 4;
      break;
    case 0x6c:
      uVar3 = uVar3 | 8;
      break;
    case 0x6d:
      uVar3 = uVar3 | 0xc;
      break;
    case 0x70:
      uVar3 = uVar3 | 0x80;
    }
    iVar2 = iVar2 + 1;
    cVar1 = param_1[iVar2];
  }
  return uVar3;
}

/* PlayerGetRedirInfo @ 0x080d18e0, 200 bytes */
void PlayerGetRedirInfo(int param_1,undefined4 *param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int *piVar4;
  
  piVar4 = g;
  *param_2 = 0;
  param_2[1] = param_1;
  param_2[2] = 0;
  param_2[3] = 0;
  param_2[4] = 0;
  if (piVar4[0x731d] == 0) {
    iVar1 = *(int *)(param_1 + 0xc);
    *param_2 = *(undefined4 *)(param_1 + 0x3424);
    if (iVar1 == 1) {
      param_2[1] = piVar4[0x73da];
    }
    piVar4 = g;
    if (iVar1 == 2) {
      param_2[1] = g[0x73db];
    }
  }
  iVar1 = piVar4[0x73da];
  if (param_1 == iVar1) {
    iVar1 = piVar4[0x73dc];
  }
  else if (param_1 != piVar4[0x73dc]) {
    iVar1 = piVar4[0x73db];
    if (param_1 == iVar1) {
      iVar1 = piVar4[0x73dd];
    }
    else if (param_1 != piVar4[0x73dd]) goto LAB_080d198b;
  }
  param_2[2] = iVar1;
LAB_080d198b:
  uVar2 = HelperParent(param_1);
  param_2[3] = uVar2;
  uVar3 = HelperRoot(param_1);
  param_2[4] = uVar3;
  return;
}

