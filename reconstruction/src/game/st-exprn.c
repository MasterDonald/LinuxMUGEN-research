/*
 * st-exprn.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x080c3810-0x080c9ff6, 33 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* TPGetValuePrefix @ 0x080c3810, 49 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x60-byte frame (a local's address escapes, see apply_frame_emulation) */
char * TPGetValuePrefix(int param_1,undefined4 param_2,undefined4 param_3)

{
  char *pcVar1;
  unsigned char ghidra_frame[0x60] __attribute__((aligned(16)));
#define local_5c (*(char (*)[84])(ghidra_frame + 0x4))
  
  sprintf(local_5c,"%s%s",param_2,param_3);
  pcVar1 = TPGetValue(param_1,local_5c);
  return pcVar1;
}
#undef local_5c

/* StringAdd @ 0x080c3850, 35 bytes */
char * StringAdd(char *param_1,undefined4 param_2,undefined4 param_3)

{
  sprintf(param_1,"%s%s",param_2,param_3);
  return param_1;
}

/* SCtrlParseAftImgParams @ 0x080c3880, 1437 bytes
 * FIXUP: frame emulation: 4 stack locals placed at their original offsets in a 0x70-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 SCtrlParseAftImgParams(int param_1,int param_2,int *param_3,undefined4 param_4)

{
  int *dst0;
  byte *pbVar1;
  int iVar2;
  char *pcVar3;
  int *piVar4;
  int iVar5;
  unsigned char ghidra_frame[0x70] __attribute__((aligned(16)));
#define local_68 (*(int *)(ghidra_frame + 0x8))
#define local_64 (*(int *)(ghidra_frame + 0xc))
#define local_60 (*(char **)(ghidra_frame + 0x10))
#define local_5c (*(char (*)[76])(ghidra_frame + 0x14))
  
  ConstExpI(param_3 + 0x40,0x100);
  ConstExpI(param_3 + 0x43,0x100);
  ConstExpI(param_3 + 3,0x14);
  ConstExpI(param_3 + 6,1);
  ConstExpI(param_3 + 9,4);
  ConstExpI(param_3,1);
  dst0 = param_3 + 0x15;
  ConstExpI(param_3 + 0x12,0x1e);
  ConstExpI(dst0,0x1e);
  ConstExpI(param_3 + 0x18,0x1e);
  ConstExpI(param_3 + 0x1b,0x78);
  ConstExpI(param_3 + 0x1e,0x78);
  ConstExpI(param_3 + 0x21,0xdc);
  ConstExpI(param_3 + 0x24,0);
  ConstExpI(param_3 + 0x27,0);
  ConstExpI(param_3 + 0x2a,0);
  ConstExpI(param_3 + 0x2d,10);
  ConstExpI(param_3 + 0x30,10);
  ConstExpI(param_3 + 0x33,0x19);
  ConstExpF(param_3 + 0x36,0x3f266666);
  ConstExpF(param_3 + 0x39,0x3f266666);
  ConstExpF(param_3 + 0x3c,0x3f400000);
  param_3[0x3f] = 0;
  pbVar1 = (byte *)TPGetValuePrefix(param_1,param_4,"time");
  iVar2 = InfixToPostfix(pbVar1,param_3,param_2,(undefined4 *)0x0,1);
  if (iVar2 != 0) {
    pbVar1 = (byte *)TPGetValuePrefix(param_1,param_4,"length");
    iVar2 = InfixToPostfix(pbVar1,param_3 + 3,param_2,(undefined4 *)0x0,1);
    if (iVar2 != 0) {
      piVar4 = param_3 + 0xc;
      iVar5 = 0x100;
      iVar2 = param_2;
      pcVar3 = StringAdd(local_5c,param_4,"palcolor");
      iVar2 = ItoP_TPConstI(param_1,pcVar3,piVar4,iVar2,iVar5);
      if (iVar2 != 0) {
        iVar5 = 0;
        piVar4 = param_3 + 0xf;
        iVar2 = param_2;
        pcVar3 = StringAdd(local_5c,param_4,"palinvertall");
        iVar2 = ItoP_TPConstI(param_1,pcVar3,piVar4,iVar2,iVar5);
        if ((((iVar2 != 0) &&
             ((pbVar1 = (byte *)TPGetValuePrefix(param_1,param_4,"palbright"), pbVar1 == (byte *)0x0
              || ((pbVar1 = SCtrlReadExpList(pbVar1,"iii",param_2,&local_60,dst0,dst0,param_3 + 0x18
                                            ), pbVar1 != (byte *)0x0 && (*local_60 == '\0')))))) &&
            ((pbVar1 = (byte *)TPGetValuePrefix(param_1,param_4,"palcontrast"),
             pbVar1 == (byte *)0x0 ||
             ((pbVar1 = SCtrlReadExpList(pbVar1,"iii",param_2,&local_60,param_3 + 0x1b,
                                         param_3 + 0x1e,param_3 + 0x21), pbVar1 != (byte *)0x0 &&
              (*local_60 == '\0')))))) &&
           ((((pbVar1 = (byte *)TPGetValuePrefix(param_1,param_4,"palpostbright"),
              pbVar1 == (byte *)0x0 ||
              ((pbVar1 = SCtrlReadExpList(pbVar1,"iii",param_2,&local_60,param_3 + 0x24,
                                          param_3 + 0x27,param_3 + 0x2a), pbVar1 != (byte *)0x0 &&
               (*local_60 == '\0')))) &&
             ((pbVar1 = (byte *)TPGetValuePrefix(param_1,param_4,"paladd"), pbVar1 == (byte *)0x0 ||
              ((pbVar1 = SCtrlReadExpList(pbVar1,"iii",param_2,&local_60,param_3 + 0x2d,
                                          param_3 + 0x30,param_3 + 0x33), pbVar1 != (byte *)0x0 &&
               (*local_60 == '\0')))))) &&
            ((pbVar1 = (byte *)TPGetValuePrefix(param_1,param_4,"palmul"), pbVar1 == (byte *)0x0 ||
             ((pbVar1 = SCtrlReadExpList(pbVar1,"fff",param_2,&local_60,param_3 + 0x36,
                                         param_3 + 0x39,param_3 + 0x3c), pbVar1 != (byte *)0x0 &&
              (*local_60 == '\0')))))))) {
          pbVar1 = (byte *)TPGetValuePrefix(param_1,param_4,"timegap");
          iVar2 = InfixToPostfix(pbVar1,param_3 + 6,param_2,(undefined4 *)0x0,1);
          if (iVar2 != 0) {
            pbVar1 = (byte *)TPGetValuePrefix(param_1,param_4,"framegap");
            iVar2 = InfixToPostfix(pbVar1,param_3 + 9,param_2,(undefined4 *)0x0,1);
            if (iVar2 != 0) {
              param_3[0x3f] = 0;
              pcVar3 = (char *)TPGetValuePrefix(param_1,param_4,"trans");
              if (pcVar3 != (char *)0x0) {
                local_64 = -1;
                local_68 = -1;
                iVar2 = GetDrawType(pcVar3,&local_68,&local_64);
                param_3[0x3f] = iVar2;
                if (iVar2 != -2) {
                  iVar2 = local_68;
                  if (local_68 == -1) {
                    iVar2 = 0x100;
                  }
                  ConstExpI(param_3 + 0x40,iVar2);
                  if (local_64 != -1) {
                    ConstExpI(param_3 + 0x43,local_64);
                  }
                  if ((local_68 == -1) &&
                     (pbVar1 = (byte *)TPGetValuePrefix(param_1,param_4,"alpha"),
                     pbVar1 != (byte *)0x0)) {
                    pbVar1 = SCtrlReadExpList(pbVar1,"ii",param_2,&local_60,param_3 + 0x40,
                                              param_3 + 0x43);
                    if (pbVar1 == (byte *)0x0) {
                      return 0;
                    }
                    if (*local_60 != '\0') {
                      return 0;
                    }
                  }
                }
              }
              return 1;
            }
          }
        }
      }
    }
  }
  return 0;
}
#undef local_68
#undef local_64
#undef local_60
#undef local_5c

/* SCtrlInitAftImgParams @ 0x080c3e20, 671 bytes
 * FIXUP: 4 data addresses written as literals replaced by data-image references
 * FIXUP: frame emulation: 20 stack locals placed at their original offsets in a 0x80-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 SCtrlInitAftImgParams(int param_1,int param_2,undefined4 param_3,int *param_4)

{
  int iVar1;
  int *piVar2;
  unsigned char ghidra_frame[0x80] __attribute__((aligned(16)));
#define local_7c (*(int (*)[5])(ghidra_frame + 0x4))
#define local_68 (*(int *)(ghidra_frame + 0x18))
#define local_64 (*(int *)(ghidra_frame + 0x1c))
#define local_60 (*(int *)(ghidra_frame + 0x20))
#define local_5c (*(int *)(ghidra_frame + 0x24))
#define local_58 (*(int *)(ghidra_frame + 0x28))
#define local_54 (*(int *)(ghidra_frame + 0x2c))
#define local_50 (*(int *)(ghidra_frame + 0x30))
#define local_4c (*(int *)(ghidra_frame + 0x34))
#define local_48 (*(int *)(ghidra_frame + 0x38))
#define local_44 (*(int *)(ghidra_frame + 0x3c))
#define local_40 (*(int *)(ghidra_frame + 0x40))
#define local_3c (*(int *)(ghidra_frame + 0x44))
#define local_38 (*(int *)(ghidra_frame + 0x48))
#define local_34 (*(float *)(ghidra_frame + 0x4c))
#define local_30 (*(float *)(ghidra_frame + 0x50))
#define local_2c (*(float *)(ghidra_frame + 0x54))
#define local_28 (*(undefined4 *)(ghidra_frame + 0x58))
#define local_24 (*(int *)(ghidra_frame + 0x5c))
#define local_20 (*(int *)(ghidra_frame + 0x60))
  
  piVar2 = local_7c;
  for (iVar1 = 0x18; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar2 = 0;
    piVar2 = piVar2 + 1;
  }
  local_7c[0] = EvalExpressionI((int)param_4,param_1,1);
  if (local_7c[0] < -1) {
    local_7c[0] = 1;
    Warn((int)param_4,(int)&DAT_0827b7c4);
  }
  iVar1 = EvalExpressionI((int)param_4,param_1 + 0xc,1);
  if (iVar1 < 1) {
    local_7c[1] = 0x14;
    Warn((int)param_4,(int)&DAT_0827b7e0);
    iVar1 = local_7c[1];
  }
  else {
    local_7c[1] = *(int *)(param_2 + 4);
    if (local_7c[1] < iVar1) {
      VWarn((int)param_4,"length for afterimage exceeds maximum of %i",*(undefined4 *)(param_2 + 4),
            piVar2);
      iVar1 = local_7c[1];
    }
  }
  local_7c[1] = iVar1;
  local_7c[2] = EvalExpressionI((int)param_4,param_1 + 0x18,1);
  if (local_7c[2] < 1) {
    local_7c[2] = 1;
    Warn((int)param_4,(int)&DAT_0827c220);
  }
  local_7c[3] = EvalExpressionI((int)param_4,param_1 + 0x24,1);
  if (local_7c[3] < 1) {
    local_7c[3] = 4;
    Warn((int)param_4,(int)&DAT_0827c240);
  }
  local_7c[4] = EvalExpressionI((int)param_4,param_1 + 0x30,1);
  local_68 = EvalExpressionI((int)param_4,param_1 + 0x3c,1);
  local_64 = EvalExpressionI((int)param_4,param_1 + 0x48,1);
  local_60 = EvalExpressionI((int)param_4,param_1 + 0x54,1);
  local_5c = EvalExpressionI((int)param_4,param_1 + 0x60,1);
  local_58 = EvalExpressionI((int)param_4,param_1 + 0x6c,1);
  local_54 = EvalExpressionI((int)param_4,param_1 + 0x78,1);
  local_50 = EvalExpressionI((int)param_4,param_1 + 0x84,1);
  local_4c = EvalExpressionI((int)param_4,param_1 + 0x90,1);
  local_48 = EvalExpressionI((int)param_4,param_1 + 0x9c,1);
  local_44 = EvalExpressionI((int)param_4,param_1 + 0xa8,1);
  local_40 = EvalExpressionI((int)param_4,param_1 + 0xb4,1);
  local_3c = EvalExpressionI((int)param_4,param_1 + 0xc0,1);
  local_38 = EvalExpressionI((int)param_4,param_1 + 0xcc,1);
  local_34 = EvalExpressionF(param_4,(int *)(param_1 + 0xd8));
  local_30 = EvalExpressionF(param_4,(int *)(param_1 + 0xe4));
  local_2c = EvalExpressionF(param_4,(int *)(param_1 + 0xf0));
  local_28 = *(undefined4 *)(param_1 + 0xfc);
  local_24 = EvalExpressionI((int)param_4,param_1 + 0x100,1);
  local_20 = EvalExpressionI((int)param_4,param_1 + 0x10c,1);
  AftImgSetup(param_2,local_7c,param_3);
  return 1;
}
#undef local_7c
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_20

/* AftImgParamsEFree @ 0x080c40c0, 297 bytes */
void AftImgParamsEFree(int *param_1)

{
  FreeExpression(param_1);
  FreeExpression(param_1 + 3);
  FreeExpression(param_1 + 6);
  FreeExpression(param_1 + 9);
  FreeExpression(param_1 + 0xc);
  FreeExpression(param_1 + 0xf);
  FreeExpression(param_1 + 0x12);
  FreeExpression(param_1 + 0x15);
  FreeExpression(param_1 + 0x18);
  FreeExpression(param_1 + 0x1b);
  FreeExpression(param_1 + 0x1e);
  FreeExpression(param_1 + 0x21);
  FreeExpression(param_1 + 0x24);
  FreeExpression(param_1 + 0x27);
  FreeExpression(param_1 + 0x2a);
  FreeExpression(param_1 + 0x2d);
  FreeExpression(param_1 + 0x30);
  FreeExpression(param_1 + 0x33);
  FreeExpression(param_1 + 0x36);
  FreeExpression(param_1 + 0x39);
  FreeExpression(param_1 + 0x3c);
  FreeExpression(param_1 + 0x40);
  FreeExpression(param_1 + 0x43);
  return;
}

/* SCtrlParseEnvShake @ 0x080c41f0, 285 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x60-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 SCtrlParseEnvShake(int param_1,int param_2,int *param_3,undefined4 param_4)

{
  int iVar1;
  char *pcVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  unsigned char ghidra_frame[0x60] __attribute__((aligned(16)));
#define local_5c (*(char (*)[76])(ghidra_frame + 0x4))
  
  sprintf(local_5c,"%stime",param_4);
  iVar1 = ItoP_TPConstI(param_1,local_5c,param_3,param_2,0);
  if (iVar1 != 0) {
    sprintf(local_5c,"%sdir",param_4,iVar1);
    iVar1 = ItoP_TPConstI(param_1,local_5c,param_3 + 3,param_2,0);
    if (iVar1 != 0) {
      sprintf(local_5c,"%sampl",param_4,extraout_ECX);
      iVar1 = ItoP_TPConstI(param_1,local_5c,param_3 + 9,param_2,-4);
      if (iVar1 != 0) {
        sprintf(local_5c,"%sfreq",param_4,extraout_EDX);
        iVar1 = ItoP_TPConstF(param_1,local_5c,param_3 + 6,param_2,0x42700000);
        if (iVar1 != 0) {
          sprintf(local_5c,"%sphase",param_4,iVar1);
          iVar1 = ItoP_TPConstF(param_1,local_5c,param_3 + 0xc,param_2,0);
          if (iVar1 != 0) {
            pcVar2 = TPGetValue(param_1,local_5c);
            param_3[0xf] = (uint)(pcVar2 == (char *)0x0);
            return 1;
          }
        }
      }
    }
  }
  return 0;
}
#undef local_5c

/* SCtrlInitEnvShake @ 0x080c4310, 200 bytes
 * FIXUP: 1 data addresses written as literals replaced by data-image references
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: untyped (undefined4) <-> float moves kept as bit copies: 3 assignments, 0 calls, 0 returns
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
undefined4 SCtrlInitEnvShake(int *player,undefined4 *param_2,int *param_3)

{
  int iVar1;
  undefined4 *puVar2;
  float10 fVar3;
  
  puVar2 = param_2;
  for (iVar1 = 6; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  iVar1 = EvalExpressionI((int)param_3,player,1);
  param_2[1] = iVar1;
  fVar3 = EvalExpressionF(param_3,player + 9);
  param_2[4] = GHIDRA_F2I(undefined4, fVar3);
  fVar3 = EvalExpressionF(param_3,player + 0xc);
  param_2[5] = GHIDRA_F2I(undefined4, fVar3);
  fVar3 = EvalExpressionF(param_3,player + 6);
  if (fVar3 == 0.0) {
    fVar3 = ((float)0.001f);
  }
  if (fVar3 < 0.0) {
    fVar3 = fVar3 * -1.0;
    Warn((int)param_3,(int)&DAT_0827b821);
  }
  iVar1 = player[0xf];
  param_2[3] = GHIDRA_F2I(undefined4, fVar3);
  if ((iVar1 != 0) && (90.0 <= fVar3)) {
    param_2[5] = 0x42b40000;
  }
  *param_2 = 0;
  return 1;
}

/* EnvShakeEFree @ 0x080c43e0, 63 bytes */
void EnvShakeEFree(int *param_1)

{
  FreeExpression(param_1);
  FreeExpression(param_1 + 3);
  FreeExpression(param_1 + 6);
  FreeExpression(param_1 + 9);
  FreeExpression(param_1 + 0xc);
  return;
}

/* SCtrlParseExplod @ 0x080c4420, 1776 bytes
 * FIXUP: frame emulation: 3 stack locals placed at their original offsets in a 0x20-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 SCtrlParseExplod(int param_1,int param_2,int *param_3,int param_4)

{
  int iVar1;
  byte *pbVar2;
  char *pcVar3;
  undefined4 extraout_EDX;
  unsigned char ghidra_frame[0x20] __attribute__((aligned(16)));
#define local_1c (*(int *)(ghidra_frame + 0x4))
#define local_18 (*(int *)(ghidra_frame + 0x8))
#define local_14 (*(char **)(ghidra_frame + 0xc))
  
  param_3[0x31] = ((param_4 != 0) - 1 & 0x7fef) - 0x7fef;
  if (param_4 == 0) {
    iVar1 = 0x3f800000;
  }
  else {
    iVar1 = -0x39001000;
  }
  ConstExpF(param_3 + 0x2b,iVar1);
  if (param_4 == 0) {
    iVar1 = 0x3f800000;
  }
  else {
    iVar1 = -0x39001000;
  }
  ConstExpF(param_3 + 0x2e,iVar1);
  iVar1 = ItoP_TPConstI(param_1,"id",param_3,param_2,(param_4 == 0) - 1);
  if (iVar1 == 0) {
    return 0;
  }
  pbVar2 = (byte *)TPGetValue(param_1,"anim");
  if (pbVar2 != (byte *)0x0) {
    if ((*pbVar2 == 0x66) || (*pbVar2 == 0x46)) {
      iVar1 = InfixToPostfix(pbVar2 + 1,param_3 + 3,param_2,(undefined4 *)0x0,1);
      if (iVar1 == 0) {
        return 0;
      }
      param_3[6] = 1;
    }
    else {
      iVar1 = InfixToPostfix(pbVar2,param_3 + 3,param_2,(undefined4 *)0x0,1);
      if (iVar1 == 0) {
        return 0;
      }
    }
  }
  pbVar2 = (byte *)TPGetValue(param_1,"pos");
  if (pbVar2 != (byte *)0x0) {
    pbVar2 = SCtrlReadExpList(pbVar2,"ii",param_2,&local_14,param_3 + 7,param_3 + 10);
    if (pbVar2 == (byte *)0x0) {
      return 0;
    }
    if (*local_14 != '\0') {
      return 0;
    }
  }
  pbVar2 = (byte *)TPGetValue(param_1,"vel");
  if (pbVar2 == (byte *)0x0) {
    pbVar2 = (byte *)TPGetValue(param_1,"velocity");
  }
  if (pbVar2 != (byte *)0x0) {
    pbVar2 = SCtrlReadExpList(pbVar2,"ff",param_2,&local_14,param_3 + 0xd,param_3 + 0x10);
    if (pbVar2 == (byte *)0x0) {
      return 0;
    }
    if (*local_14 != '\0') {
      return 0;
    }
  }
  pbVar2 = (byte *)TPGetValue(param_1,"accel");
  if (pbVar2 != (byte *)0x0) {
    pbVar2 = SCtrlReadExpList(pbVar2,"ff",param_2,&local_14,param_3 + 0x13,param_3 + 0x16);
    if (pbVar2 == (byte *)0x0) {
      return 0;
    }
    if (*local_14 != '\0') {
      return 0;
    }
  }
  pbVar2 = (byte *)TPGetValue(param_1,"random");
  if (pbVar2 != (byte *)0x0) {
    pbVar2 = SCtrlReadExpList(pbVar2,"ii",param_2,&local_14,param_3 + 0x19,param_3 + 0x1c);
    if (pbVar2 == (byte *)0x0) {
      return 0;
    }
    if (*local_14 != '\0') {
      return 0;
    }
  }
  iVar1 = ItoP_TPConstI(param_1,"supermove",param_3 + 0x1f,param_2,
                        ((param_4 != 0) - 1 & 0x7fef) - 0x7fef);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = ItoP_TPConstI(param_1,"supermovetime",param_3 + 0x22,param_2,
                        ((param_4 != 0) - 1 & 0x7fef) - 0x7fef);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = ItoP_TPConstI(param_1,"pausemovetime",param_3 + 0x25,param_2,
                        ((param_4 != 0) - 1 & 0x7fef) - 0x7fef);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = ItoP_TPConstI(param_1,"removetime",param_3 + 0x28,param_2,
                        ((param_4 == 0) - 1 & 0xffff8013) - 2);
  if (iVar1 == 0) {
    return 0;
  }
  pbVar2 = (byte *)TPGetValue(param_1,"scale");
  if (pbVar2 != (byte *)0x0) {
    pbVar2 = SCtrlReadExpList(pbVar2,"ff",param_2,&local_14,param_3 + 0x2b,param_3 + 0x2e);
    if (pbVar2 == (byte *)0x0) {
      return 0;
    }
    if (*local_14 != '\0') {
      return 0;
    }
  }
  pcVar3 = TPGetValue(param_1,"postype");
  if (pcVar3 != (char *)0x0) {
    iVar1 = ParsePosType(pcVar3);
    param_3[0x31] = iVar1;
    if (iVar1 == -1) {
      sprintf((char *)(g + 0x81d2),"Illegal postype: %s",pcVar3,extraout_EDX);
      return 0;
    }
  }
  iVar1 = ItoP_TPConstI(param_1,"bindtime",param_3 + 0x32,param_2,
                        ((param_4 == 0) - 1 & 0xffff8010) + 1);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = ItoP_TPConstI(param_1,"sprpriority",param_3 + 0x35,param_2,
                        ((param_4 != 0) - 1 & 0x7fef) - 0x7fef);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = ItoP_TPConstI(param_1,"ontop",param_3 + 0x38,param_2,
                        ((param_4 != 0) - 1 & 0x7fef) - 0x7fef);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = ItoP_TPConstI(param_1,"facing",param_3 + 0x3b,param_2,1);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = ItoP_TPConstI(param_1,"vfacing",param_3 + 0x3e,param_2,1);
  if (iVar1 == 0) {
    return 0;
  }
  if (param_4 != 0) {
    ConstExpI(param_3 + 0x41,-0x7fef);
  }
  pbVar2 = (byte *)TPGetValue(param_1,"shadow");
  if (pbVar2 != (byte *)0x0) {
    pbVar2 = SCtrlReadExpList(pbVar2,"iii",param_2,&local_14,param_3 + 0x41,param_3 + 0x44,
                              param_3 + 0x47);
    if (pbVar2 == (byte *)0x0) {
      return 0;
    }
    if (*local_14 != '\0') {
      return 0;
    }
  }
  iVar1 = ItoP_TPConstI(param_1,"ownpal",param_3 + 0x4a,param_2,
                        ((param_4 != 0) - 1 & 0x7fef) - 0x7fef);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = ItoP_TPConstI(param_1,"removeongethit",param_3 + 0x4d,param_2,
                        ((param_4 != 0) - 1 & 0x7fef) - 0x7fef);
  if (iVar1 == 0) {
    return 0;
  }
  iVar1 = ItoP_TPConstI(param_1,"ignorehitpause",param_3 + 0x50,param_2,
                        ((param_4 == 0) - 1 & 0xffff8010) + 1);
  if (iVar1 == 0) {
    return 0;
  }
  param_3[0x53] = ((param_4 == 0) - 1 & 0xffff8012) - 1;
  pcVar3 = TPGetValue(param_1,"trans");
  if (pcVar3 == (char *)0x0) {
    return 1;
  }
  local_18 = -1;
  local_1c = -1;
  iVar1 = GetDrawType(pcVar3,&local_1c,&local_18);
  param_3[0x53] = iVar1;
  if (iVar1 == -2) {
    return 1;
  }
  iVar1 = local_1c;
  if (local_1c == -1) {
    if (param_4 == 0) {
      iVar1 = 0x100;
    }
    else {
      iVar1 = -0x7fef;
    }
  }
  ConstExpI(param_3 + 0x54,iVar1);
  iVar1 = local_18;
  if (local_18 == -1) {
    if (param_4 == 0) goto LAB_080c4aaa;
    iVar1 = -0x7fef;
  }
  ConstExpI(param_3 + 0x57,iVar1);
LAB_080c4aaa:
  if (((local_1c == -1) && (pbVar2 = (byte *)TPGetValue(param_1,"alpha"), pbVar2 != (byte *)0x0)) &&
     ((pbVar2 = SCtrlReadExpList(pbVar2,"ii",param_2,&local_14,param_3 + 0x54,param_3 + 0x57),
      pbVar2 == (byte *)0x0 || (*local_14 != '\0')))) {
    return 0;
  }
  return 1;
}
#undef local_1c
#undef local_18
#undef local_14

/* ExplodInfoFree @ 0x080c4b10, 381 bytes */
void ExplodInfoFree(int *param_1)

{
  FreeExpression(param_1);
  FreeExpression(param_1 + 3);
  FreeExpression(param_1 + 7);
  FreeExpression(param_1 + 10);
  FreeExpression(param_1 + 0xd);
  FreeExpression(param_1 + 0x10);
  FreeExpression(param_1 + 0x13);
  FreeExpression(param_1 + 0x16);
  FreeExpression(param_1 + 0x19);
  FreeExpression(param_1 + 0x1c);
  FreeExpression(param_1 + 0x1f);
  FreeExpression(param_1 + 0x22);
  FreeExpression(param_1 + 0x25);
  FreeExpression(param_1 + 0x28);
  FreeExpression(param_1 + 0x2b);
  FreeExpression(param_1 + 0x2e);
  FreeExpression(param_1 + 0x32);
  FreeExpression(param_1 + 0x35);
  FreeExpression(param_1 + 0x38);
  FreeExpression(param_1 + 0x3b);
  FreeExpression(param_1 + 0x3e);
  FreeExpression(param_1 + 0x41);
  FreeExpression(param_1 + 0x44);
  FreeExpression(param_1 + 0x47);
  FreeExpression(param_1 + 0x4a);
  FreeExpression(param_1 + 0x4d);
  FreeExpression(param_1 + 0x50);
  FreeExpression(param_1 + 0x54);
  FreeExpression(param_1 + 0x57);
  return;
}

/* SCtrlParsePalFX @ 0x080c4c90, 491 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x20-byte frame (a local's address escapes, see apply_frame_emulation) */
bool SCtrlParsePalFX(int param_1,int param_2,int param_3,int param_4)

{
  char *pcVar1;
  byte *pbVar2;
  int iVar3;
  unsigned char ghidra_frame[0x20] __attribute__((aligned(16)));
#define local_14 (*(char **)(ghidra_frame + 0xc))
  
  ConstExpI((int *)(param_3 + 0x40),0x100);
  ConstExpI((int *)(param_3 + 0x4c),0x100);
  ConstExpI((int *)(param_3 + 0x58),0x100);
  pcVar1 = "palfx.time";
  if (param_4 == 0) {
    pcVar1 = "time";
  }
  pbVar2 = (byte *)TPGetValue(param_1,pcVar1);
  iVar3 = InfixToPostfix(pbVar2,(int *)(param_3 + 4),param_2,(undefined4 *)0x0,1);
  if (iVar3 != 0) {
    pcVar1 = "palfx.mul";
    if (param_4 == 0) {
      pcVar1 = "mul";
    }
    pbVar2 = (byte *)TPGetValue(param_1,pcVar1);
    if ((pbVar2 == (byte *)0x0) ||
       ((pbVar2 = SCtrlReadExpList(pbVar2,"iii",param_2,&local_14,(int *)(param_3 + 0x40),
                                   (int *)(param_3 + 0x4c),(int *)(param_3 + 0x58)),
        pbVar2 == (byte *)0x3 && (*local_14 == '\0')))) {
      pcVar1 = "palfx.add";
      if (param_4 == 0) {
        pcVar1 = "add";
      }
      pbVar2 = (byte *)TPGetValue(param_1,pcVar1);
      if ((pbVar2 == (byte *)0x0) ||
         ((pbVar2 = SCtrlReadExpList(pbVar2,"iii",param_2,&local_14,(int *)(param_3 + 0x1c),
                                     (int *)(param_3 + 0x28),(int *)(param_3 + 0x34)),
          pbVar2 == (byte *)0x3 && (*local_14 == '\0')))) {
        pcVar1 = "palfx.sinadd";
        if (param_4 == 0) {
          pcVar1 = "sinadd";
        }
        pbVar2 = (byte *)TPGetValue(param_1,pcVar1);
        if ((pbVar2 == (byte *)0x0) ||
           ((pbVar2 = SCtrlReadExpList(pbVar2,"iiii",param_2,&local_14,(int *)(param_3 + 100),
                                       (int *)(param_3 + 0x70),(int *)(param_3 + 0x7c),
                                       (int *)(param_3 + 0x94)), pbVar2 + -3 < (byte *)0x2 &&
            (*local_14 == '\0')))) {
          pcVar1 = "palfx.invertall";
          if (param_4 == 0) {
            pcVar1 = "invertall";
          }
          iVar3 = ItoP_TPConstI(param_1,pcVar1,(int *)(param_3 + 0x88),param_2,0);
          if (iVar3 != 0) {
            pcVar1 = "palfx.color";
            if (param_4 == 0) {
              pcVar1 = "color";
            }
            iVar3 = ItoP_TPConstI(param_1,pcVar1,(int *)(param_3 + 0x10),param_2,0x100);
            return iVar3 != 0;
          }
        }
      }
    }
  }
  return false;
}
#undef local_14

/* SCtrlInitPalFX @ 0x080c4e80, 414 bytes
 * FIXUP: 3 data addresses written as literals replaced by data-image references */
undefined4 SCtrlInitPalFX(int *param_1,undefined4 *param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  
  if (*param_1 == 1) {
    param_2 = g + 0x6ed5;
  }
  else if (*param_1 == 2) {
    param_2 = g + 0x6ee4;
  }
  piVar3 = param_2;
  for (iVar2 = 0xf; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar3 = 0;
    piVar3 = piVar3 + 1;
  }
  iVar2 = EvalExpressionI(param_3,param_1 + 1,1);
  param_2[1] = iVar2;
  if (iVar2 < -1) {
    param_2[1] = 0;
    Warn(param_3,(int)&DAT_0827b8cb);
  }
  uVar1 = EvalExpressionI(param_3,param_1 + 4,1);
  param_2[2] = uVar1;
  if (0x100 < uVar1) {
    Warn(param_3,(int)&DAT_0827b8de);
  }
  iVar2 = EvalExpressionI(param_3,param_1 + 7,1);
  param_2[3] = iVar2;
  iVar2 = EvalExpressionI(param_3,param_1 + 10,1);
  param_2[4] = iVar2;
  iVar2 = EvalExpressionI(param_3,param_1 + 0xd,1);
  param_2[5] = iVar2;
  iVar2 = EvalExpressionI(param_3,param_1 + 0x10,1);
  param_2[6] = iVar2;
  iVar2 = EvalExpressionI(param_3,param_1 + 0x13,1);
  param_2[7] = iVar2;
  iVar2 = EvalExpressionI(param_3,param_1 + 0x16,1);
  param_2[8] = iVar2;
  if ((((int)param_2[6] < 0) || ((int)param_2[7] < 0)) || (iVar2 < 0)) {
    Warn(param_3,(int)&DAT_0827b8f8);
  }
  iVar2 = EvalExpressionI(param_3,param_1 + 0x19,1);
  param_2[9] = iVar2;
  iVar2 = EvalExpressionI(param_3,param_1 + 0x1c,1);
  param_2[10] = iVar2;
  iVar2 = EvalExpressionI(param_3,param_1 + 0x1f,1);
  param_2[0xb] = iVar2;
  iVar2 = EvalExpressionI(param_3,param_1 + 0x25,1);
  param_2[0xd] = iVar2;
  iVar2 = EvalExpressionI(param_3,param_1 + 0x22,1);
  param_2[0xc] = iVar2;
  return 1;
}

/* PalFXEFree @ 0x080c5020, 160 bytes */
void PalFXEFree(int param_1)

{
  FreeExpression((int *)(param_1 + 4));
  FreeExpression((int *)(param_1 + 0x10));
  FreeExpression((int *)(param_1 + 0x1c));
  FreeExpression((int *)(param_1 + 0x28));
  FreeExpression((int *)(param_1 + 0x34));
  FreeExpression((int *)(param_1 + 0x40));
  FreeExpression((int *)(param_1 + 0x4c));
  FreeExpression((int *)(param_1 + 0x58));
  FreeExpression((int *)(param_1 + 100));
  FreeExpression((int *)(param_1 + 0x70));
  FreeExpression((int *)(param_1 + 0x7c));
  FreeExpression((int *)(param_1 + 0x88));
  FreeExpression((int *)(param_1 + 0x94));
  return;
}

/* SCtrlParsePlaySndInfo @ 0x080c50c0, 465 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x20-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 SCtrlParsePlaySndInfo(int param_1,int param_2,int *param_3)

{
  byte *pbVar1;
  int iVar2;
  unsigned char ghidra_frame[0x20] __attribute__((aligned(16)));
#define local_14 (*(int *)(ghidra_frame + 0xc))
  
  pbVar1 = (byte *)TPGetValue(param_1,"value");
  if (pbVar1 != (byte *)0x0) {
    ConstExpI(param_3,-1);
    ConstExpI(param_3 + 0x10,1);
    local_14 = 0;
    iVar2 = ParseSnd(pbVar1,param_3 + 3,param_3 + 6,&local_14,param_2);
    if (iVar2 != 0) {
      param_3[0xc] = local_14;
      pbVar1 = (byte *)TPGetValue(param_1,"volume");
      iVar2 = InfixToPostfix(pbVar1,param_3 + 9,param_2,(undefined4 *)0x0,1);
      if (iVar2 != 0) {
        pbVar1 = (byte *)TPGetValue(param_1,"channel");
        iVar2 = InfixToPostfix(pbVar1,param_3,param_2,(undefined4 *)0x0,1);
        if (iVar2 != 0) {
          pbVar1 = (byte *)TPGetValue(param_1,"lowpriority");
          iVar2 = InfixToPostfix(pbVar1,param_3 + 0xd,param_2,(undefined4 *)0x0,1);
          if (iVar2 != 0) {
            pbVar1 = (byte *)TPGetValue(param_1,"freqmul");
            iVar2 = InfixToPostfix(pbVar1,param_3 + 0x10,param_2,(undefined4 *)0x0,2);
            if (iVar2 != 0) {
              pbVar1 = (byte *)TPGetValue(param_1,"loop");
              iVar2 = InfixToPostfix(pbVar1,param_3 + 0x13,param_2,(undefined4 *)0x0,1);
              if (iVar2 != 0) {
                pbVar1 = (byte *)TPGetValue(param_1,"abspan");
                if (pbVar1 == (byte *)0x0) {
                  pbVar1 = (byte *)TPGetValue(param_1,"pan");
                  iVar2 = InfixToPostfix(pbVar1,param_3 + 0x17,param_2,(undefined4 *)0x0,1);
                  if (iVar2 != 0) {
                    return 1;
                  }
                }
                else {
                  iVar2 = InfixToPostfix(pbVar1,param_3 + 0x17,param_2,(undefined4 *)0x0,1);
                  if (iVar2 != 0) {
                    param_3[0x16] = 1;
                    return 1;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return 0;
}
#undef local_14

/* SCtrlDoPlaySndInfo @ 0x080c52a0, 840 bytes
 * REVIEW: calls-missing-in-pid:NAN
 * FIXUP: 4 data addresses written as literals replaced by data-image references
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
int SCtrlDoPlaySndInfo(int *player,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  float10 fVar6;
  
  piVar3 = g;
  if (((g[0x6ef3] != 0) && (param_2 != 0)) && (g[0x7308] == 0)) {
    if (*(int *)(param_2 + 0x30) == 0) {
      piVar5 = (int *)((int *)*player)[0x475];
      piVar3 = (int *)*player;
    }
    else {
      piVar5 = (int *)g[0x4156];
    }
    if (piVar5 != (int *)0x0) {
      iVar1 = EvalExpressionI((int)player,param_2,1);
      if (0x20 < iVar1 + 1U) {
        iVar1 = -1;
        Warn((int)player,(int)&DAT_0827b924);
      }
      iVar1 = PlayerSndID((int)player,iVar1);
      iVar2 = EvalExpressionI((int)player,param_2 + 0x34,1);
      if (((iVar2 == 0) || (iVar1 == -1)) ||
         (piVar3 = (int *)SndIDIsPlaying(iVar1), piVar3 == (int *)0x0)) {
        iVar2 = EvalExpressionI((int)player,param_2 + 0xc,1);
        if (iVar2 < -1) {
          iVar2 = -1;
          Warn((int)player,(int)&DAT_0827b93d);
        }
        iVar4 = EvalExpressionI((int)player,param_2 + 0x18,1);
        if (iVar4 < -1) {
          iVar4 = -1;
          Warn((int)player,(int)&DAT_0827b956);
        }
        piVar3 = (int *)SndIDPrepare(iVar1,piVar5,iVar2,iVar4);
        if ((piVar3 != (int *)0xffffffff) && (iVar2 != -1)) {
          iVar1 = EvalExpressionI((int)player,param_2 + 0x5c,1);
          if (*(int *)(param_2 + 0x58) == 0) {
            iVar1 = (int)GHIDRA_FIST32((GHIDRA_I2F(player[0x67]) - (float)g[0x7311]) +
                               (float)(iVar1 * player[100]));
          }
          else {
            iVar1 = iVar1 * player[100] + 0xa0;
          }
          if (g[0x756c] == 0) {
            iVar1 = 0;
          }
          else {
            iVar1 = ScrPositionToPan(iVar1);
          }
          iVar2 = EvalExpressionI((int)player,param_2 + 0x24,1);
          iVar2 = SndCorrectVolOff(iVar2);
          iVar2 = iVar2 + g[0x6ef4];
          if (*(int *)(param_2 + 0x30) == 0) {
            iVar4 = SndCorrectVolOff(*(int *)(*player + 0x11d0));
            iVar2 = iVar2 + iVar4;
          }
          iVar4 = PanVolumeAdjust(iVar2,iVar1);
          iVar2 = SndVoiceGetFreq((int)piVar3);
          fVar6 = EvalExpressionF(player,(int *)(param_2 + 0x40));
          if (fVar6 <= 0.0) {
            fVar6 = 1.0;
            Warn((int)player,(int)&DAT_0827b96d);
          }
          if ((fVar6 != 1.0) && (iVar2 = (int)GHIDRA_FIST32((float10)iVar2 * fVar6), iVar2 < 0x65)) {
            iVar2 = 100;
          }
          SndVoiceSetVol((int)piVar3,iVar4);
          SndVoiceSetFreq((int)piVar3,iVar2);
          SndVoiceSetPan((int)piVar3,iVar1);
          iVar1 = EvalExpressionI((int)player,param_2 + 0x4c,1);
          SndVoiceSetLoop((int)piVar3,(uint)(iVar1 != 0));
          piVar3 = (int *)SndVoiceStart((int)piVar3);
        }
      }
    }
  }
  return (int)piVar3;
}

/* PlaySndInfoFree @ 0x080c55f0, 96 bytes */
void PlaySndInfoFree(int *param_1)

{
  FreeExpression(param_1);
  FreeExpression(param_1 + 3);
  FreeExpression(param_1 + 6);
  FreeExpression(param_1 + 9);
  FreeExpression(param_1 + 0xd);
  FreeExpression(param_1 + 0x10);
  FreeExpression(param_1 + 0x13);
  FreeExpression(param_1 + 0x17);
  return;
}

/* SCtrlParseHitOverride @ 0x080c5650, 238 bytes */
bool SCtrlParseHitOverride(int param_1,int param_2,int *param_3)

{
  char *pcVar1;
  uint uVar2;
  byte *pbVar3;
  int iVar4;
  undefined4 extraout_ECX;
  
  ConstExpI(param_3 + 4,1);
  ConstExpI(param_3 + 1,-1);
  pcVar1 = TPGetValue(param_1,"attr");
  if (pcVar1 != (char *)0x0) {
    uVar2 = ParseHitAttr((int)pcVar1,0);
    *param_3 = uVar2;
    if (uVar2 == 0xffffffff) {
      sprintf((char *)(g + 0x81d2),"Invalid attr: %s",pcVar1,extraout_ECX);
      return false;
    }
  }
  pbVar3 = (byte *)TPGetValue(param_1,"stateno");
  iVar4 = InfixToPostfix(pbVar3,param_3 + 1,param_2,(undefined4 *)0x0,1);
  if (iVar4 != 0) {
    pbVar3 = (byte *)TPGetValue(param_1,"time");
    iVar4 = InfixToPostfix(pbVar3,param_3 + 4,param_2,(undefined4 *)0x0,1);
    if (iVar4 != 0) {
      iVar4 = ItoP_TPConstI(param_1,"forceair",param_3 + 7,param_2,0);
      return iVar4 != 0;
    }
  }
  return false;
}

/* SCtrlInitHitOverride @ 0x080c5740, 151 bytes
 * FIXUP: 2 data addresses written as literals replaced by data-image references */
undefined4 SCtrlInitHitOverride(undefined4 *param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  
  *param_2 = 1;
  param_2[1] = *param_1;
  iVar1 = EvalExpressionI(param_3,param_1 + 1,1);
  if (iVar1 < -1) {
    iVar1 = -1;
    Warn(param_3,(int)&DAT_0827b99d);
  }
  param_2[2] = iVar1;
  iVar1 = EvalExpressionI(param_3,param_1 + 4,1);
  if (iVar1 < -1) {
    iVar1 = 1;
    Warn(param_3,(int)&DAT_0827b9ba);
  }
  param_2[3] = iVar1;
  iVar1 = EvalExpressionI(param_3,param_1 + 7,1);
  param_2[4] = iVar1;
  return 1;
}

/* HitOverrideEFree @ 0x080c57e0, 44 bytes */
void HitOverrideEFree(int param_1)

{
  FreeExpression((int *)(param_1 + 4));
  FreeExpression((int *)(param_1 + 0x10));
  FreeExpression((int *)(param_1 + 0x1c));
  return;
}

/* SCtrlParseHitDef @ 0x080c5810, 6992 bytes
 * FIXUP: 3 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x20-byte frame (a local's address escapes, see apply_frame_emulation) */
bool SCtrlParseHitDef(int param_1,int param_2,undefined4 *param_3)

{
  int *dst1;
  int *dst2;
  byte bVar1;
  bool bVar2;
  char *pcVar3;
  uint uVar4;
  byte *pbVar5;
  int iVar6;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int *piVar7;
  undefined3 extraout_var_01;
  size_t __n;
  unsigned char ghidra_frame[0x20] __attribute__((aligned(16)));
#define local_14 (*(char **)(ghidra_frame + 0xc))
  
  ConstExpI(param_3 + 0x38,-1);
  ConstExpI(param_3 + 0x3f,-1);
  param_3[0x45] = 1;
  param_3[0x3e] = 1;
  ConstExpI(param_3 + 0x4c,-1);
  ConstExpI(param_3 + 0x4f,-1);
  ConstExpI(param_3 + 0xf2,-1);
  ConstExpI(param_3 + 5,-1);
  ConstExpI(param_3 + 8,-1);
  ConstExpI(param_3 + 0xb,-1);
  *param_3 = 2;
  pcVar3 = TPGetValue(param_1,"attr");
  if (pcVar3 != (char *)0x0) {
    uVar4 = ParseHitAttr((int)pcVar3,0);
    param_3[1] = uVar4;
    if (uVar4 == 0xffffffff) {
      return false;
    }
  }
  pcVar3 = TPGetValue(param_1,"affectteam");
  if (pcVar3 == (char *)0x0) {
LAB_080c5957:
    ConstExpI(param_3 + 0x1a,-1);
    ConstExpI(param_3 + 0x35,1);
    ConstExpI(param_3 + 0x65,0);
    pbVar5 = (byte *)TPGetValue(param_1,"id");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 2,param_2,(undefined4 *)0x0,1);
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"chainid");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 5,param_2,(undefined4 *)0x0,1);
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"nochainid");
    if (pbVar5 != (byte *)0x0) {
      pbVar5 = SCtrlReadExpList(pbVar5,"ii",param_2,&local_14,param_3 + 8,param_3 + 0xb);
      if (pbVar5 == (byte *)0x0) {
        return false;
      }
      if (*local_14 != '\0') {
        return false;
      }
    }
    piVar7 = param_3 + 0x8d;
    ConstExpI(piVar7,-2);
    pbVar5 = (byte *)TPGetValue(param_1,"sparkno");
    if (pbVar5 != (byte *)0x0) {
      if (*(int *)(__ctype_tolower + (char)*pbVar5 * 4) == 0x73) {
        iVar6 = InfixToPostfix(pbVar5 + 1,piVar7,param_2,(undefined4 *)0x0,1);
        if (iVar6 == 0) {
          return false;
        }
        param_3[0x90] = 1;
      }
      else {
        iVar6 = InfixToPostfix(pbVar5,piVar7,param_2,(undefined4 *)0x0,1);
        if (iVar6 == 0) {
          return false;
        }
      }
    }
    piVar7 = param_3 + 0x91;
    ConstExpI(piVar7,-2);
    pbVar5 = (byte *)TPGetValue(param_1,"guard.sparkno");
    if (pbVar5 != (byte *)0x0) {
      if (*(int *)(__ctype_tolower + (char)*pbVar5 * 4) == 0x73) {
        iVar6 = InfixToPostfix(pbVar5 + 1,piVar7,param_2,(undefined4 *)0x0,1);
        if (iVar6 == 0) {
          return false;
        }
        param_3[0x94] = 1;
      }
      else {
        iVar6 = InfixToPostfix(pbVar5,piVar7,param_2,(undefined4 *)0x0,1);
        if (iVar6 == 0) {
          return false;
        }
      }
    }
    pbVar5 = (byte *)TPGetValue(param_1,"sparkxy");
    if (pbVar5 != (byte *)0x0) {
      pbVar5 = SCtrlReadExpList(pbVar5,"ii",param_2,&local_14,param_3 + 0x95,param_3 + 0x98);
      if (pbVar5 == (byte *)0x0) {
        return false;
      }
      if (*local_14 != '\0') {
        return false;
      }
    }
    pbVar5 = (byte *)TPGetValue(param_1,"pausetime");
    if (pbVar5 != (byte *)0x0) {
      pbVar5 = SCtrlReadExpList(pbVar5,"ii",param_2,&local_14,param_3 + 0x32,param_3 + 0x2f);
      if (pbVar5 == (byte *)0x0) {
        return false;
      }
      if (*local_14 != '\0') {
        return false;
      }
    }
    pbVar5 = (byte *)TPGetValue(param_1,"guard.pausetime");
    if (pbVar5 == (byte *)0x0) {
      expcpytrig(param_3 + 0xf8,param_3 + 0x32);
LAB_080c5c8d:
      expcpytrig(param_3 + 0xf5,param_3 + 0x2f);
    }
    else {
      pbVar5 = SCtrlReadExpList(pbVar5,"ii",param_2,&local_14,param_3 + 0xf8,param_3 + 0xf5);
      if (pbVar5 == (byte *)0x0) {
        return false;
      }
      if (*local_14 != '\0') {
        return false;
      }
      if (pbVar5 == (byte *)0x1) goto LAB_080c5c8d;
    }
    iVar6 = ItoP_TPConstI(param_1,"kill",param_3 + 0xe,param_2,1);
    if (iVar6 == 0) {
      return false;
    }
    iVar6 = ItoP_TPConstI(param_1,"guard.kill",param_3 + 0x11,param_2,1);
    if (iVar6 == 0) {
      return false;
    }
    iVar6 = ItoP_TPConstI(param_1,"fall.kill",param_3 + 0x14,param_2,1);
    if (iVar6 == 0) {
      return false;
    }
    iVar6 = ItoP_TPConstI(param_1,"hitonce",param_3 + 0x17,param_2,(uint)((param_3[1] & 0x1c0) != 0)
                         );
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"numhits");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 0x35,param_2,(undefined4 *)0x0,1);
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"damage");
    if (pbVar5 != (byte *)0x0) {
      pbVar5 = SCtrlReadExpList(pbVar5,"ii",param_2,&local_14,param_3 + 0x1d,param_3 + 0x20);
      if (pbVar5 == (byte *)0x0) {
        return false;
      }
      if (*local_14 != '\0') {
        return false;
      }
    }
    pbVar5 = (byte *)TPGetValue(param_1,"getpower");
    if (pbVar5 == (byte *)0x0) {
      piVar7 = param_3 + 0x23;
      expcpytrig(piVar7,param_3 + 0x1d);
      ExpMulF(piVar7,GHIDRA_I2F(g[0x731e]));
      expcpytrig(param_3 + 0x26,piVar7);
LAB_080c5e6f:
      ExpDivI(param_3 + 0x26,2);
    }
    else {
      pbVar5 = SCtrlReadExpList(pbVar5,"ii",param_2,&local_14,param_3 + 0x23,param_3 + 0x26);
      if (pbVar5 == (byte *)0x0) {
        return false;
      }
      if (*local_14 != '\0') {
        return false;
      }
      if (pbVar5 == (byte *)0x1) {
        expcpytrig(param_3 + 0x26,param_3 + 0x23);
        goto LAB_080c5e6f;
      }
    }
    pbVar5 = (byte *)TPGetValue(param_1,"givepower");
    if (pbVar5 == (byte *)0x0) {
      piVar7 = param_3 + 0x29;
      expcpytrig(piVar7,param_3 + 0x1d);
      ExpMulF(piVar7,GHIDRA_I2F(g[0x731f]));
      expcpytrig(param_3 + 0x2c,piVar7);
LAB_080c5f1a:
      ExpDivI(param_3 + 0x2c,2);
    }
    else {
      pbVar5 = SCtrlReadExpList(pbVar5,"ii",param_2,&local_14,param_3 + 0x29,param_3 + 0x2c);
      if (pbVar5 == (byte *)0x0) {
        return false;
      }
      if (*local_14 != '\0') {
        return false;
      }
      if (pbVar5 == (byte *)0x1) {
        expcpytrig(param_3 + 0x2c,param_3 + 0x29);
        goto LAB_080c5f1a;
      }
    }
    ConstExpI(param_3 + 0x48,4);
    param_3[0x4b] = 0;
    pbVar5 = (byte *)TPGetValue(param_1,"priority");
    if (pbVar5 != (byte *)0x0) {
      pbVar5 = SCtrlReadExpList(pbVar5,"i:,",param_2,&local_14,param_3 + 0x48);
      if (pbVar5 == (byte *)0x0) {
        return false;
      }
      if (*local_14 != '\0') {
        bVar1 = *(byte *)(__ctype_b + 1 + local_14[1] * 2);
        local_14 = local_14 + 1;
        while ((bVar1 & 0x20) != 0) {
          local_14 = local_14 + 1;
          bVar1 = *(byte *)(__ctype_b + 1 + *local_14 * 2);
        }
        iVar6 = *(int *)(__ctype_tolower + *local_14 * 4);
        if (iVar6 == 0x68) {
          param_3[0x4b] = 0;
        }
        else if (iVar6 < 0x69) {
          if (iVar6 != 100) {
            return false;
          }
          param_3[0x4b] = 2;
        }
        else {
          if (iVar6 != 0x6d) {
            return false;
          }
          param_3[0x4b] = 1;
        }
      }
    }
    pbVar5 = (byte *)TPGetValue(param_1,"hitsound");
    iVar6 = ParseSnd(pbVar5,param_3 + 0x38,param_3 + 0x3b,param_3 + 0x3e,param_2);
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"guardsound");
    iVar6 = ParseSnd(pbVar5,param_3 + 0x3f,param_3 + 0x42,param_3 + 0x45,param_2);
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"ground.slidetime");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 0xba,param_2,(undefined4 *)0x0,1);
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"ground.hittime");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 0xb7,param_2,(undefined4 *)0x0,1);
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"ground.velocity");
    bVar2 = ParseVel(pbVar5,param_3 + 0xbd,param_3 + 0xc0,param_2);
    if (GHIDRA_ZEXT8(bVar2) == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"air.velocity");
    bVar2 = ParseVel(pbVar5,param_3 + 0xce,param_3 + 0xd1,param_2);
    if (GHIDRA_ZEXT8(bVar2) == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"air.juggle");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 0x1a,param_2,(undefined4 *)0x0,1);
    if (iVar6 == 0) {
      return false;
    }
    ConstExpI(param_3 + 200,0x14);
    pbVar5 = (byte *)TPGetValue(param_1,"air.hittime");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 200,param_2,(undefined4 *)0x0,1);
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"attack.width");
    if (pbVar5 != (byte *)0x0) {
      pbVar5 = SCtrlReadExpList(pbVar5,"ii",param_2,&local_14,param_3 + 0x4c,param_3 + 0x4f);
      if (pbVar5 == (byte *)0x0) {
        return false;
      }
      if (*local_14 != '\0') {
        return false;
      }
    }
    piVar7 = param_3 + 0xa1;
    dst1 = param_3 + 0xa4;
    ConstExpI(piVar7,-0x401);
    dst2 = param_3 + 0xa7;
    ConstExpI(dst1,-0x401);
    ConstExpI(dst2,-0x401);
    ConstExpI(param_3 + 0xaa,-0x401);
    ConstExpI(param_3 + 0xad,-0x401);
    ConstExpI(param_3 + 0xb0,-0x401);
    pbVar5 = (byte *)TPGetValue(param_1,"snap");
    if (pbVar5 == (byte *)0x0) {
      pbVar5 = (byte *)TPGetValue(param_1,"mindist");
      if (pbVar5 != (byte *)0x0) {
        pbVar5 = SCtrlReadExpList(pbVar5,"iii",param_2,&local_14,piVar7,dst1,dst2);
        if (pbVar5 == (byte *)0x0) {
          return false;
        }
        if (*local_14 != '\0') {
          return false;
        }
      }
      pbVar5 = (byte *)TPGetValue(param_1,"maxdist");
      if (pbVar5 != (byte *)0x0) {
        pbVar5 = SCtrlReadExpList(pbVar5,"iii",param_2,&local_14,param_3 + 0xaa,param_3 + 0xad,
                                  param_3 + 0xb0);
        if (pbVar5 == (byte *)0x0) {
          return false;
        }
        if (*local_14 != '\0') {
          return false;
        }
      }
    }
    else {
      pbVar5 = SCtrlReadExpList(pbVar5,"iiii",param_2,&local_14,piVar7,dst1,dst2,param_3 + 0x5b);
      if (pbVar5 == (byte *)0x0) {
        return false;
      }
      if (*local_14 != '\0') {
        return false;
      }
      param_3[0xaa] = param_3[0xa1];
      param_3[0xab] = param_3[0xa2];
      param_3[0xac] = param_3[0xa3];
      param_3[0xad] = param_3[0xa4];
      param_3[0xae] = param_3[0xa5];
      param_3[0xaf] = param_3[0xa6];
      param_3[0xb0] = param_3[0xa7];
      param_3[0xb1] = param_3[0xa8];
      param_3[0xb2] = param_3[0xa9];
    }
    ConstExpI(param_3 + 0x5e,1);
    pbVar5 = (byte *)TPGetValue(param_1,"p1sprpriority");
    if (pbVar5 == (byte *)0x0) {
      pbVar5 = (byte *)TPGetValue(param_1,"sprpriority");
    }
    iVar6 = InfixToPostfix(pbVar5,param_3 + 0x5e,param_2,(undefined4 *)0x0,1);
    if (iVar6 == 0) {
      return false;
    }
    iVar6 = ItoP_TPConstI(param_1,"p2sprpriority",param_3 + 0x61,param_2,0);
    if (iVar6 == 0) {
      return false;
    }
    ConstExpI(param_3 + 0x9b,0);
    pbVar5 = (byte *)TPGetValue(param_1,"p1facing");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 0x9b,param_2,(undefined4 *)0x0,1);
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"p1getp2facing");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 0x9e,param_2,(undefined4 *)0x0,1);
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"p2facing");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 0xb3,param_2,(undefined4 *)0x0,1);
    if (iVar6 == 0) {
      return false;
    }
    ConstExpI(param_3 + 0x52,-1);
    ConstExpI(param_3 + 0x55,-1);
    ConstExpI(param_3 + 0x58,0);
    pbVar5 = (byte *)TPGetValue(param_1,"p1stateno");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 0x52,param_2,(undefined4 *)0x0,1);
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"p2stateno");
    if (pbVar5 != (byte *)0x0) {
      ConstExpI(param_3 + 0x58,1);
      iVar6 = InfixToPostfix(pbVar5,param_3 + 0x55,param_2,(undefined4 *)0x0,1);
      if (iVar6 == 0) {
        return false;
      }
    }
    pbVar5 = (byte *)TPGetValue(param_1,"p2getp1state");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 0x58,param_2,(undefined4 *)0x0,1);
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"forcestand");
    if (pbVar5 != (byte *)0x0) {
      param_3[0x68] = 1;
      iVar6 = InfixToPostfix(pbVar5,param_3 + 0x65,param_2,(undefined4 *)0x0,1);
      if (iVar6 == 0) {
        return false;
      }
    }
    ConstExpI(param_3 + 0x6a,0);
    ConstExpF(param_3 + 0x6e,-0x39001000);
    ConstExpF(param_3 + 0x71,-0x3f700000);
    ConstExpI(param_3 + 0x74,1);
    ConstExpI(param_3 + 0x77,4);
    pbVar5 = (byte *)TPGetValue(param_1,"fall.damage");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 0x6a,param_2,(undefined4 *)0x0,1);
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"fall.xvelocity");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 0x6e,param_2,(undefined4 *)0x0,2);
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"fall.yvelocity");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 0x71,param_2,(undefined4 *)0x0,2);
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"fall.recover");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 0x74,param_2,(undefined4 *)0x0,1);
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"fall.recovertime");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 0x77,param_2,(undefined4 *)0x0,1);
    if (iVar6 == 0) {
      return false;
    }
    ConstExpI(param_3 + 0x10a,-0x7ff8);
    pbVar5 = (byte *)TPGetValue(param_1,"yaccel");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 0x10a,param_2,(undefined4 *)0x0,2);
    if (iVar6 == 0) {
      return false;
    }
    ConstExpI(param_3 + 0xd7,0);
    ConstExpI(param_3 + 0xda,0x14);
    pbVar5 = (byte *)TPGetValue(param_1,"down.velocity");
    if (pbVar5 == (byte *)0x0) {
      expcpytrig(param_3 + 0xdd,param_3 + 0xce);
LAB_080c6915:
      expcpytrig(param_3 + 0xe0,param_3 + 0xd1);
    }
    else {
      pbVar5 = SCtrlReadExpList(pbVar5,"ff",param_2,&local_14,param_3 + 0xdd,param_3 + 0xe0);
      if (pbVar5 == (byte *)0x0) {
        return false;
      }
      if (*local_14 != '\0') {
        return false;
      }
      if (pbVar5 == (byte *)0x1) goto LAB_080c6915;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"down.bounce");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 0xd7,param_2,(undefined4 *)0x0,1);
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"down.hittime");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 0xda,param_2,(undefined4 *)0x0,1);
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"guard.slidetime");
    if (pbVar5 == (byte *)0x0) {
      expcpytrig(param_3 + 0xec,param_3 + 0xba);
    }
    else {
      iVar6 = InfixToPostfix(pbVar5,param_3 + 0xec,param_2,(undefined4 *)0x0,1);
      if (iVar6 == 0) {
        return false;
      }
    }
    pbVar5 = (byte *)TPGetValue(param_1,"guard.hittime");
    if (pbVar5 == (byte *)0x0) {
      expcpytrig(param_3 + 0xe9,param_3 + 0xb7);
    }
    else {
      iVar6 = InfixToPostfix(pbVar5,param_3 + 0xe9,param_2,(undefined4 *)0x0,1);
      if (iVar6 == 0) {
        return false;
      }
    }
    pbVar5 = (byte *)TPGetValue(param_1,"guard.velocity");
    if (pbVar5 == (byte *)0x0) {
      expcpytrig(param_3 + 0xe6,param_3 + 0xbd);
    }
    else {
      iVar6 = InfixToPostfix(pbVar5,param_3 + 0xe6,param_2,(undefined4 *)0x0,2);
      if (iVar6 == 0) {
        return false;
      }
    }
    pbVar5 = (byte *)TPGetValue(param_1,"guard.ctrltime");
    if (pbVar5 == (byte *)0x0) {
      expcpytrig(param_3 + 0xef,param_3 + 0xec);
    }
    else {
      iVar6 = InfixToPostfix(pbVar5,param_3 + 0xef,param_2,(undefined4 *)0x0,1);
      if (iVar6 == 0) {
        return false;
      }
    }
    pbVar5 = (byte *)TPGetValue(param_1,"guard.dist");
    iVar6 = InfixToPostfix(pbVar5,param_3 + 0xf2,param_2,(undefined4 *)0x0,1);
    if (iVar6 == 0) {
      return false;
    }
    pbVar5 = (byte *)TPGetValue(param_1,"ground.cornerpush.veloff");
    if (pbVar5 == (byte *)0x0) {
      if ((*(byte *)(param_3 + 1) & 4) == 0) {
        expcpytrig(param_3 + 0xc3,param_3 + 0xe6);
        ExpMulF(param_3 + 0xc3,((double)1.3));
      }
      else {
        ConstExpF(param_3 + 0xc3,0);
      }
    }
    else {
      iVar6 = InfixToPostfix(pbVar5,param_3 + 0xc3,param_2,(undefined4 *)0x0,2);
      if (iVar6 == 0) {
        return false;
      }
    }
    pbVar5 = (byte *)TPGetValue(param_1,"air.cornerpush.veloff");
    if (pbVar5 == (byte *)0x0) {
      expcpytrig(param_3 + 0xd4,param_3 + 0xc3);
    }
    else {
      iVar6 = InfixToPostfix(pbVar5,param_3 + 0xd4,param_2,(undefined4 *)0x0,2);
      if (iVar6 == 0) {
        return false;
      }
    }
    pbVar5 = (byte *)TPGetValue(param_1,"down.cornerpush.veloff");
    if (pbVar5 == (byte *)0x0) {
      expcpytrig(param_3 + 0xe3,param_3 + 0xc3);
    }
    else {
      iVar6 = InfixToPostfix(pbVar5,param_3 + 0xe3,param_2,(undefined4 *)0x0,2);
      if (iVar6 == 0) {
        return false;
      }
    }
    pbVar5 = (byte *)TPGetValue(param_1,"guard.cornerpush.veloff");
    if (pbVar5 == (byte *)0x0) {
      expcpytrig(param_3 + 0xfb,param_3 + 0xc3);
    }
    else {
      iVar6 = InfixToPostfix(pbVar5,param_3 + 0xfb,param_2,(undefined4 *)0x0,2);
      if (iVar6 == 0) {
        return false;
      }
    }
    pbVar5 = (byte *)TPGetValue(param_1,"airguard.cornerpush.veloff");
    if (pbVar5 == (byte *)0x0) {
      expcpytrig(param_3 + 0x107,param_3 + 0xfb);
    }
    else {
      iVar6 = InfixToPostfix(pbVar5,param_3 + 0x107,param_2,(undefined4 *)0x0,2);
      if (iVar6 == 0) {
        return false;
      }
    }
    pbVar5 = (byte *)TPGetValue(param_1,"airguard.velocity");
    if (pbVar5 == (byte *)0x0) {
      expcpytrig(param_3 + 0xfe,param_3 + 0xce);
      ExpMulF(param_3 + 0xfe,1.5);
      expcpytrig(param_3 + 0x101,param_3 + 0xd1);
LAB_080c6da9:
      ExpMulF(param_3 + 0x101,0.5);
    }
    else {
      pbVar5 = SCtrlReadExpList(pbVar5,"ff",param_2,&local_14,param_3 + 0xfe,param_3 + 0x101);
      if (pbVar5 == (byte *)0x0) {
        return false;
      }
      if (*local_14 != '\0') {
        return false;
      }
      if (pbVar5 == (byte *)0x1) {
        expcpytrig(param_3 + 0x101,param_3 + 0xd1);
        goto LAB_080c6da9;
      }
    }
    pbVar5 = (byte *)TPGetValue(param_1,"airguard.ctrltime");
    if (pbVar5 == (byte *)0x0) {
      expcpytrig(param_3 + 0x104,param_3 + 0xef);
    }
    else {
      iVar6 = InfixToPostfix(pbVar5,param_3 + 0x104,param_2,(undefined4 *)0x0,1);
      if (iVar6 == 0) {
        return false;
      }
    }
    ConstExpI(param_3 + 0xcb,0);
    pbVar5 = (byte *)TPGetValue(param_1,"fall");
    if (pbVar5 != (byte *)0x0) {
      iVar6 = InfixToPostfix(pbVar5,param_3 + 0x8a,param_2,(undefined4 *)0x0,1);
      if (iVar6 == 0) {
        return false;
      }
      expcpytrig(param_3 + 0xcb,param_3 + 0x8a);
    }
    pbVar5 = (byte *)TPGetValue(param_1,"air.fall");
    if (pbVar5 != (byte *)0x0) {
      FreeExpression(param_3 + 0xcb);
      iVar6 = InfixToPostfix(pbVar5,param_3 + 0xcb,param_2,(undefined4 *)0x0,1);
      if (iVar6 == 0) {
        return false;
      }
    }
    pcVar3 = TPGetValue(param_1,"guardflag");
    if (pcVar3 != (char *)0x0) {
      uVar4 = ParseHitFlag(pcVar3);
      param_3[0x46] = param_3[0x46] | uVar4;
    }
    pcVar3 = TPGetValue(param_1,"hitflag");
    if (pcVar3 == (char *)0x0) {
      param_3[0x47] = param_3[0x47] | 0x3e;
    }
    else {
      uVar4 = ParseHitFlag(pcVar3);
      param_3[0x47] = param_3[0x47] | uVar4;
    }
    param_3[100] = 0;
    pcVar3 = TPGetValue(param_1,"animtype");
    if (pcVar3 != (char *)0x0) {
      switch(*(undefined4 *)(__ctype_tolower + *pcVar3 * 4)) {
      case 0x62:
        param_3[100] = 3;
        break;
      default:
        piVar7 = g + 0x81d2;
        __n = 0x11;
        pcVar3 = "Invalid animtype";
        goto LAB_080c72d2;
      case 100:
        param_3[100] = 5;
        break;
      case 0x68:
        param_3[100] = 2;
        break;
      case 0x6c:
        param_3[100] = 0;
        break;
      case 0x6d:
        param_3[100] = 1;
        break;
      case 0x75:
        param_3[100] = 4;
      }
    }
    param_3[199] = param_3[100];
    pcVar3 = TPGetValue(param_1,"air.animtype");
    if (pcVar3 != (char *)0x0) {
      switch(*(undefined4 *)(__ctype_tolower + *pcVar3 * 4)) {
      case 0x62:
        param_3[199] = 3;
        break;
      default:
        piVar7 = g + 0x81d2;
        __n = 0x15;
        pcVar3 = "Invalid air.animtype";
        goto LAB_080c72d2;
      case 100:
        param_3[199] = 5;
        break;
      case 0x68:
        param_3[199] = 2;
        break;
      case 0x6c:
        param_3[199] = 0;
        break;
      case 0x6d:
        param_3[199] = 1;
        break;
      case 0x75:
        param_3[199] = 4;
      }
    }
    if (param_3[199] == 4) {
      param_3[0x6d] = 4;
    }
    else {
      param_3[0x6d] = (uint)(param_3[199] == 5) * 2 + 3;
    }
    pcVar3 = TPGetValue(param_1,"fall.animtype");
    if (pcVar3 != (char *)0x0) {
      switch(*(undefined4 *)(__ctype_tolower + *pcVar3 * 4)) {
      case 0x62:
        param_3[0x6d] = 3;
        break;
      default:
        piVar7 = g + 0x81d2;
        __n = 0x16;
        pcVar3 = "Invalid fall.animtype";
        goto LAB_080c72d2;
      case 100:
        param_3[0x6d] = 5;
        break;
      case 0x68:
        param_3[0x6d] = 2;
        break;
      case 0x6c:
        param_3[0x6d] = 0;
        break;
      case 0x6d:
        param_3[0x6d] = 1;
        break;
      case 0x75:
        param_3[0x6d] = 4;
      }
    }
    param_3[0xb6] = 1;
    pcVar3 = TPGetValue(param_1,"ground.type");
    if (pcVar3 != (char *)0x0) {
      iVar6 = *(int *)(__ctype_tolower + *pcVar3 * 4);
      if (iVar6 == 0x6c) {
        param_3[0xb6] = 2;
      }
      else if (iVar6 < 0x6d) {
        if (iVar6 != 0x68) {
LAB_080c7210:
          piVar7 = g + 0x81d2;
          __n = 0x14;
          pcVar3 = "Invalid ground.type";
          goto LAB_080c72d2;
        }
        param_3[0xb6] = 1;
      }
      else if (iVar6 == 0x6e) {
        param_3[0xb6] = 0;
      }
      else {
        if (iVar6 != 0x74) goto LAB_080c7210;
        param_3[0xb6] = 3;
      }
    }
    param_3[0xc6] = param_3[0xb6];
    pcVar3 = TPGetValue(param_1,"air.type");
    if (pcVar3 != (char *)0x0) {
      iVar6 = *(int *)(__ctype_tolower + *pcVar3 * 4);
      if (iVar6 == 0x6c) {
        param_3[0xc6] = 2;
      }
      else if (iVar6 < 0x6d) {
        if (iVar6 != 0x68) {
LAB_080c72c0:
          piVar7 = g + 0x81d2;
          __n = 0x11;
          pcVar3 = "Invalid air.type";
          goto LAB_080c72d2;
        }
        param_3[0xc6] = 1;
      }
      else if (iVar6 == 0x6e) {
        param_3[0xc6] = 0;
      }
      else {
        if (iVar6 != 0x74) goto LAB_080c72c0;
        param_3[0xc6] = 3;
      }
    }
    bVar2 = SCtrlParsePalFX(param_1,param_2,(int)(param_3 + 0x10d),1);
    if (GHIDRA_ZEXT8(bVar2) != 0) {
      param_3[0x10d] = 0;
      iVar6 = SCtrlParseEnvShake(param_1,param_2,param_3 + 0x135,"envshake.");
      if (iVar6 != 0) {
        iVar6 = SCtrlParseEnvShake(param_1,param_2,param_3 + 0x7a,"fall.envshake.");
        return iVar6 != 0;
      }
    }
  }
  else {
    iVar6 = *(int *)(__ctype_tolower + *pcVar3 * 4);
    if (iVar6 == 0x65) {
      *param_3 = 2;
      goto LAB_080c5957;
    }
    if (iVar6 < 0x66) {
      if (iVar6 == 0x62) {
        *param_3 = 3;
        goto LAB_080c5957;
      }
    }
    else if (iVar6 == 0x66) {
      *param_3 = 1;
      goto LAB_080c5957;
    }
    piVar7 = g + 0x81d2;
    __n = 0x19;
    pcVar3 = "Invalid affectteam value";
LAB_080c72d2:
    memcpy(piVar7,pcVar3,__n);
  }
  return false;
}
#undef local_14

/* SCtrlInitHitDef @ 0x080c7360, 3018 bytes
 * FIXUP: 29 data addresses written as literals replaced by data-image references
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
undefined4 SCtrlInitHitDef(undefined4 *param_1,int param_2,int *param_3)

{
  int iVar1;
  uint uVar2;
  float10 fVar3;
  
  *(undefined4 *)(param_2 + 8) = *param_1;
  *(undefined4 *)(param_2 + 0xc) = param_1[1];
  iVar1 = EvalExpressionI((int)param_3,param_1 + 2,1);
  *(int *)(param_2 + 0x14) = iVar1;
  if (iVar1 < 0) {
    *(undefined4 *)(param_2 + 0x14) = 0;
    Warn((int)param_3,(int)&DAT_0827bcca);
  }
  iVar1 = EvalExpressionI((int)param_3,param_1 + 5,1);
  *(int *)(param_2 + 0x18) = iVar1;
  if (iVar1 < -1) {
    *(undefined4 *)(param_2 + 0x18) = 0xffffffff;
    Warn((int)param_3,(int)&DAT_0827bce2);
  }
  iVar1 = EvalExpressionI((int)param_3,param_1 + 8,1);
  *(int *)(param_2 + 0x1c) = iVar1;
  if (iVar1 < -1) {
    *(undefined4 *)(param_2 + 0x1c) = 0xffffffff;
    Warn((int)param_3,(int)&DAT_0827bcfd);
  }
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0xb,1);
  *(int *)(param_2 + 0x20) = iVar1;
  if (iVar1 < -1) {
    *(undefined4 *)(param_2 + 0x20) = 0xffffffff;
    Warn((int)param_3,(int)&DAT_0827bd1a);
  }
  iVar1 = *(int *)(param_2 + 0x18);
  if (((iVar1 == *(int *)(param_2 + 0x1c)) || (iVar1 == *(int *)(param_2 + 0x20))) && (iVar1 != -1))
  {
    *(undefined4 *)(param_2 + 0x20) = 0xffffffff;
    *(undefined4 *)(param_2 + 0x1c) = 0xffffffff;
    *(undefined4 *)(param_2 + 0x18) = 0xffffffff;
  }
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0xe,1);
  *(uint *)(param_2 + 0x24) = (uint)(iVar1 != 0);
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x11,1);
  *(uint *)(param_2 + 0x28) = (uint)(iVar1 != 0);
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x14,1);
  *(uint *)(param_2 + 0x2c) = (uint)(iVar1 != 0);
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x17,1);
  *(uint *)(param_2 + 0x30) = (uint)(iVar1 != 0);
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x1a,1);
  *(int *)(param_2 + 0x34) = iVar1;
  if (iVar1 < -1) {
    *(undefined4 *)(param_2 + 0x34) = 0xffffffff;
    Warn((int)param_3,(int)&DAT_0827bd38);
  }
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x1d,1);
  *(int *)(param_2 + 0x38) = iVar1;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x20,1);
  *(int *)(param_2 + 0x3c) = iVar1;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x23,0);
  *(int *)(param_2 + 0x40) = iVar1;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x26,0);
  *(int *)(param_2 + 0x44) = iVar1;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x29,0);
  *(int *)(param_2 + 0x48) = iVar1;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x2c,0);
  *(int *)(param_2 + 0x4c) = iVar1;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x2f,1);
  *(int *)(param_2 + 0x50) = iVar1;
  if (iVar1 < 0) {
    *(undefined4 *)(param_2 + 0x50) = 0;
    Warn((int)param_3,(int)&DAT_0827c260);
  }
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x32,1);
  *(int *)(param_2 + 0x54) = iVar1;
  if (iVar1 < 0) {
    *(undefined4 *)(param_2 + 0x54) = 0;
    Warn((int)param_3,(int)&DAT_0827bd4e);
  }
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x35,1);
  *(int *)(param_2 + 0x58) = iVar1;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x38,1);
  *(int *)(param_2 + 0x5c) = iVar1;
  if (iVar1 < -1) {
    *(undefined4 *)(param_2 + 0x5c) = 0xffffffff;
    Warn((int)param_3,(int)&DAT_0827bd6b);
  }
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x3b,1);
  *(int *)(param_2 + 0x60) = iVar1;
  if (iVar1 < -1) {
    *(undefined4 *)(param_2 + 0x60) = 0xffffffff;
    Warn((int)param_3,(int)&DAT_0827bd89);
  }
  *(undefined4 *)(param_2 + 100) = param_1[0x3e];
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x3f,1);
  *(int *)(param_2 + 0x68) = iVar1;
  if (iVar1 < -1) {
    *(undefined4 *)(param_2 + 0x68) = 0xffffffff;
    Warn((int)param_3,(int)&DAT_0827c280);
  }
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x42,1);
  *(int *)(param_2 + 0x6c) = iVar1;
  if (iVar1 < -1) {
    *(undefined4 *)(param_2 + 0x6c) = 0xffffffff;
    Warn((int)param_3,(int)&DAT_0827bda4);
  }
  *(undefined4 *)(param_2 + 0x70) = param_1[0x45];
  *(undefined4 *)(param_2 + 0x74) = param_1[0x46];
  *(undefined4 *)(param_2 + 0x78) = param_1[0x47];
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x48,1);
  *(int *)(param_2 + 0x7c) = iVar1;
  if (iVar1 < 0) {
    *(undefined4 *)(param_2 + 0x7c) = 0;
    Warn((int)param_3,(int)&DAT_0827c2a0);
  }
  *(undefined4 *)(param_2 + 0x80) = param_1[0x4b];
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x4c,1);
  *(int *)(param_2 + 0x84) = iVar1;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x4f,1);
  *(int *)(param_2 + 0x88) = iVar1;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x52,1);
  *(int *)(param_2 + 0x8c) = iVar1;
  if (iVar1 < -1) {
    *(undefined4 *)(param_2 + 0x8c) = 0xffffffff;
    Warn((int)param_3,(int)&DAT_0827bdc0);
  }
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x55,1);
  *(int *)(param_2 + 0x90) = iVar1;
  if (iVar1 < -1) {
    *(undefined4 *)(param_2 + 0x90) = 0xffffffff;
    Warn((int)param_3,(int)&DAT_0827bddd);
  }
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x58,1);
  *(uint *)(param_2 + 0x94) = (uint)(iVar1 != 0);
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x5b,1);
  *(int *)(param_2 + 0x98) = iVar1;
  if (iVar1 < -1) {
    *(undefined4 *)(param_2 + 0x98) = 1;
    Warn((int)param_3,(int)&DAT_0827bdfa);
  }
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x5e,1);
  *(int *)(param_2 + 0x9c) = iVar1;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x61,1);
  *(int *)(param_2 + 0xa0) = iVar1;
  *(undefined4 *)(param_2 + 0xa4) = param_1[100];
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x65,1);
  *(uint *)(param_2 + 0xa8) = (uint)(iVar1 != 0);
  *(undefined4 *)(param_2 + 0xac) = param_1[0x69];
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x8a,1);
  if (iVar1 != 0) {
    *(uint *)(param_2 + 0x78) = *(uint *)(param_2 + 0x78) | 1;
  }
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x6a,1);
  *(int *)(param_2 + 0xb0) = iVar1;
  *(undefined4 *)(param_2 + 0xb4) = param_1[0x6d];
  fVar3 = EvalExpressionF(param_3,param_1 + 0x6e);
  *(float *)(param_2 + 0xb8) = fVar3;
  fVar3 = EvalExpressionF(param_3,param_1 + 0x71);
  *(float *)(param_2 + 0xbc) = fVar3;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x74,1);
  *(uint *)(param_2 + 0xc0) = (uint)(iVar1 != 0);
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x77,1);
  *(int *)(param_2 + 0xc4) = iVar1;
  if (iVar1 < 0) {
    *(undefined4 *)(param_2 + 0xc4) = 4;
    Warn((int)param_3,(int)&DAT_0827c2c0);
  }
  *(undefined4 *)(param_2 + 0xe4) = param_1[0x90];
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x8d,1);
  *(int *)(param_2 + 0xe0) = iVar1;
  if (iVar1 < -2) {
    *(undefined4 *)(param_2 + 0xe0) = 0xfffffffe;
    Warn((int)param_3,(int)&DAT_0827be17);
  }
  *(undefined4 *)(param_2 + 0xec) = param_1[0x94];
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x91,1);
  *(int *)(param_2 + 0xe8) = iVar1;
  if (iVar1 < -2) {
    *(undefined4 *)(param_2 + 0xe8) = 0xfffffffe;
    Warn((int)param_3,(int)&DAT_0827be28);
  }
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x95,1);
  *(int *)(param_2 + 0xf0) = iVar1;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x98,1);
  *(int *)(param_2 + 0xf4) = iVar1;
  uVar2 = EvalExpressionI((int)param_3,param_1 + 0x9b,1);
  *(uint *)(param_2 + 0xf8) = uVar2 >> 0x1f;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x9e,1);
  if (iVar1 < 0) {
    iVar1 = -1;
  }
  else if (0 < iVar1) {
    iVar1 = 1;
  }
  if (iVar1 != 0) {
    *(undefined4 *)(param_2 + 0xf8) = 0;
  }
  *(int *)(param_2 + 0xfc) = iVar1;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0xa1,1);
  *(int *)(param_2 + 0x100) = iVar1;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0xa4,1);
  *(int *)(param_2 + 0x104) = iVar1;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0xaa,1);
  *(int *)(param_2 + 0x10c) = iVar1;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0xad,1);
  *(int *)(param_2 + 0x110) = iVar1;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0xb3,1);
  *(int *)(param_2 + 0x118) = iVar1;
  if (2 < iVar1 + 1U) {
    *(undefined4 *)(param_2 + 0x118) = 0;
    Warn((int)param_3,(int)&DAT_0827be3a);
  }
  *(undefined4 *)(param_2 + 0x11c) = param_1[0xb6];
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0xb7,1);
  *(int *)(param_2 + 0x120) = iVar1;
  if (iVar1 < 0) {
    *(undefined4 *)(param_2 + 0x120) = 0;
    Warn((int)param_3,(int)&DAT_0827be55);
  }
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0xba,1);
  *(int *)(param_2 + 0x124) = iVar1;
  if (iVar1 < 0) {
    *(undefined4 *)(param_2 + 0x124) = 0;
    Warn((int)param_3,(int)&DAT_0827be6f);
  }
  fVar3 = EvalExpressionF(param_3,param_1 + 0xbd);
  *(float *)(param_2 + 0x128) = fVar3;
  fVar3 = EvalExpressionF(param_3,param_1 + 0xc0);
  *(float *)(param_2 + 300) = fVar3;
  if ((fVar3 != 0.0) && (param_1[0x68] == 0)) {
    *(undefined4 *)(param_2 + 0xa8) = 1;
  }
  fVar3 = EvalExpressionF(param_3,param_1 + 0xc3);
  *(undefined4 *)(param_2 + 0x134) = param_1[0xc6];
  *(undefined4 *)(param_2 + 0x138) = param_1[199];
  *(float *)(param_2 + 0x130) = fVar3;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 200,1);
  *(int *)(param_2 + 0x13c) = iVar1;
  if (iVar1 < 0) {
    *(undefined4 *)(param_2 + 0x13c) = 0;
    Warn((int)param_3,(int)&DAT_0827be8b);
  }
  fVar3 = EvalExpressionF(param_3,param_1 + 0xcb);
  *(int *)(param_2 + 0x140) = (int)GHIDRA_FIST32(fVar3);
  fVar3 = EvalExpressionF(param_3,param_1 + 0xce);
  *(float *)(param_2 + 0x144) = fVar3;
  fVar3 = EvalExpressionF(param_3,param_1 + 0xd1);
  *(float *)(param_2 + 0x148) = fVar3;
  fVar3 = EvalExpressionF(param_3,param_1 + 0xd4);
  *(float *)(param_2 + 0x14c) = fVar3;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0xd7,1);
  *(uint *)(param_2 + 0x150) = (uint)(iVar1 != 0);
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0xda,1);
  *(int *)(param_2 + 0x154) = iVar1;
  if (iVar1 < 0) {
    *(undefined4 *)(param_2 + 0x154) = 0;
    Warn((int)param_3,(int)&DAT_0827bea2);
  }
  fVar3 = EvalExpressionF(param_3,param_1 + 0xdd);
  *(float *)(param_2 + 0x158) = fVar3;
  fVar3 = EvalExpressionF(param_3,param_1 + 0xe0);
  *(float *)(param_2 + 0x15c) = fVar3;
  fVar3 = EvalExpressionF(param_3,param_1 + 0xe3);
  *(float *)(param_2 + 0x160) = fVar3;
  fVar3 = EvalExpressionF(param_3,param_1 + 0xe6);
  *(float *)(param_2 + 0x164) = fVar3;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0xe9,1);
  *(int *)(param_2 + 0x168) = iVar1;
  if (iVar1 < 0) {
    *(undefined4 *)(param_2 + 0x168) = 0;
    Warn((int)param_3,(int)&DAT_0827beba);
  }
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0xec,1);
  *(int *)(param_2 + 0x16c) = iVar1;
  if (iVar1 < 0) {
    *(undefined4 *)(param_2 + 0x16c) = 0;
    Warn((int)param_3,(int)&DAT_0827bed3);
  }
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0xef,1);
  *(int *)(param_2 + 0x170) = iVar1;
  if (iVar1 < 0) {
    *(undefined4 *)(param_2 + 0x170) = 0;
    Warn((int)param_3,(int)&DAT_0827beee);
  }
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0xf2,1);
  *(int *)(param_2 + 0x174) = iVar1;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0xf5,1);
  *(int *)(param_2 + 0x178) = iVar1;
  if (iVar1 < 0) {
    *(undefined4 *)(param_2 + 0x178) = 0;
    Warn((int)param_3,(int)&DAT_0827bf08);
  }
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0xf8,1);
  *(int *)(param_2 + 0x17c) = iVar1;
  if (iVar1 < 0) {
    *(undefined4 *)(param_2 + 0x17c) = 0;
    Warn((int)param_3,(int)&DAT_0827bf23);
  }
  fVar3 = EvalExpressionF(param_3,param_1 + 0xfb);
  *(float *)(param_2 + 0x180) = fVar3;
  fVar3 = EvalExpressionF(param_3,param_1 + 0xfe);
  *(float *)(param_2 + 0x184) = fVar3;
  fVar3 = EvalExpressionF(param_3,param_1 + 0x101);
  *(float *)(param_2 + 0x188) = fVar3;
  iVar1 = EvalExpressionI((int)param_3,param_1 + 0x104,1);
  *(int *)(param_2 + 0x18c) = iVar1;
  if (iVar1 < 0) {
    *(undefined4 *)(param_2 + 0x18c) = 0;
    Warn((int)param_3,(int)&DAT_0827bf3e);
  }
  fVar3 = EvalExpressionF(param_3,param_1 + 0x107);
  *(float *)(param_2 + 400) = fVar3;
  fVar3 = EvalExpressionF(param_3,param_1 + 0x10a);
  *(float *)(param_2 + 0x194) = fVar3;
  SCtrlInitPalFX(param_1 + 0x10d,(undefined4 *)(param_2 + 0x198),(int)param_3);
  SCtrlInitEnvShake(param_1 + 0x135,(undefined4 *)(param_2 + 0x1d4),param_3);
  SCtrlInitEnvShake(param_1 + 0x7a,(undefined4 *)(param_2 + 200),param_3);
  return 1;
}

/* HitDefEFree @ 0x080c7f30, 1129 bytes */
void HitDefEFree(int param_1)

{
  FreeExpression((int *)(param_1 + 8));
  FreeExpression((int *)(param_1 + 0x14));
  FreeExpression((int *)(param_1 + 0x20));
  FreeExpression((int *)(param_1 + 0x2c));
  FreeExpression((int *)(param_1 + 0x38));
  FreeExpression((int *)(param_1 + 0x44));
  FreeExpression((int *)(param_1 + 0x50));
  FreeExpression((int *)(param_1 + 0x5c));
  FreeExpression((int *)(param_1 + 0x68));
  FreeExpression((int *)(param_1 + 0x74));
  FreeExpression((int *)(param_1 + 0x80));
  FreeExpression((int *)(param_1 + 0x8c));
  FreeExpression((int *)(param_1 + 0x98));
  FreeExpression((int *)(param_1 + 0xa4));
  FreeExpression((int *)(param_1 + 0xb0));
  FreeExpression((int *)(param_1 + 0xbc));
  FreeExpression((int *)(param_1 + 200));
  FreeExpression((int *)(param_1 + 0xd4));
  FreeExpression((int *)(param_1 + 0xe0));
  FreeExpression((int *)(param_1 + 0xec));
  FreeExpression((int *)(param_1 + 0xfc));
  FreeExpression((int *)(param_1 + 0x108));
  FreeExpression((int *)(param_1 + 0x120));
  FreeExpression((int *)(param_1 + 0x130));
  FreeExpression((int *)(param_1 + 0x13c));
  FreeExpression((int *)(param_1 + 0x148));
  FreeExpression((int *)(param_1 + 0x154));
  FreeExpression((int *)(param_1 + 0x160));
  FreeExpression((int *)(param_1 + 0x16c));
  FreeExpression((int *)(param_1 + 0x178));
  FreeExpression((int *)(param_1 + 0x184));
  FreeExpression((int *)(param_1 + 0x194));
  FreeExpression((int *)(param_1 + 0x1a8));
  FreeExpression((int *)(param_1 + 0x1b8));
  FreeExpression((int *)(param_1 + 0x1c4));
  FreeExpression((int *)(param_1 + 0x1d0));
  FreeExpression((int *)(param_1 + 0x1dc));
  FreeExpression((int *)(param_1 + 0x228));
  FreeExpression((int *)(param_1 + 0x234));
  FreeExpression((int *)(param_1 + 0x244));
  FreeExpression((int *)(param_1 + 0x254));
  FreeExpression((int *)(param_1 + 0x260));
  FreeExpression((int *)(param_1 + 0x26c));
  FreeExpression((int *)(param_1 + 0x278));
  FreeExpression((int *)(param_1 + 0x284));
  FreeExpression((int *)(param_1 + 0x290));
  FreeExpression((int *)(param_1 + 0x29c));
  FreeExpression((int *)(param_1 + 0x2a8));
  FreeExpression((int *)(param_1 + 0x2b4));
  FreeExpression((int *)(param_1 + 0x2c0));
  FreeExpression((int *)(param_1 + 0x2cc));
  FreeExpression((int *)(param_1 + 0x2dc));
  FreeExpression((int *)(param_1 + 0x2e8));
  FreeExpression((int *)(param_1 + 0x2f4));
  FreeExpression((int *)(param_1 + 0x300));
  FreeExpression((int *)(param_1 + 0x30c));
  FreeExpression((int *)(param_1 + 800));
  FreeExpression((int *)(param_1 + 0x32c));
  FreeExpression((int *)(param_1 + 0x338));
  FreeExpression((int *)(param_1 + 0x344));
  FreeExpression((int *)(param_1 + 0x350));
  FreeExpression((int *)(param_1 + 0x35c));
  FreeExpression((int *)(param_1 + 0x368));
  FreeExpression((int *)(param_1 + 0x374));
  FreeExpression((int *)(param_1 + 0x380));
  FreeExpression((int *)(param_1 + 0x38c));
  FreeExpression((int *)(param_1 + 0x398));
  FreeExpression((int *)(param_1 + 0x3a4));
  FreeExpression((int *)(param_1 + 0x3b0));
  FreeExpression((int *)(param_1 + 0x3bc));
  FreeExpression((int *)(param_1 + 0x3ec));
  FreeExpression((int *)(param_1 + 0x3c8));
  FreeExpression((int *)(param_1 + 0x3d4));
  FreeExpression((int *)(param_1 + 0x3e0));
  FreeExpression((int *)(param_1 + 0x3f8));
  FreeExpression((int *)(param_1 + 0x404));
  FreeExpression((int *)(param_1 + 0x410));
  FreeExpression((int *)(param_1 + 0x41c));
  FreeExpression((int *)(param_1 + 0x428));
  PalFXEFree(param_1 + 0x434);
  EnvShakeEFree((int *)(param_1 + 0x4d4));
  EnvShakeEFree((int *)(param_1 + 0x1e8));
  return;
}

/* SCtrlParseProjectile @ 0x080c83a0, 2029 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x20-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 SCtrlParseProjectile(int param_1,int param_2,int *param_3)

{
  bool bVar1;
  byte *pbVar2;
  int iVar3;
  char *pcVar4;
  undefined3 extraout_var;
  unsigned char ghidra_frame[0x20] __attribute__((aligned(16)));
#define local_14 (*(char **)(ghidra_frame + 0xc))
  
  param_3[9] = 0;
  ConstExpF(param_3 + 0x3d,0);
  ConstExpF(param_3 + 0x40,0);
  ConstExpI(param_3 + 0xd,-1);
  ConstExpI(param_3 + 0x1f,1);
  ConstExpI(param_3 + 0x22,1);
  ConstExpI(param_3 + 0x28,-1);
  ConstExpI(param_3 + 0x2e,-1);
  ConstExpF(param_3 + 0x43,0x3f800000);
  ConstExpF(param_3 + 0x46,0x3f800000);
  ConstExpF(param_3 + 0x4f,0);
  ConstExpF(param_3 + 0x52,0);
  ConstExpF(param_3 + 0x55,0x3f800000);
  ConstExpF(param_3 + 0x58,0x3f800000);
  ConstExpI(param_3 + 10,1);
  ConstExpI(param_3 + 0x13,0x28);
  ConstExpI(param_3 + 0x16,0x28);
  ConstExpI(param_3 + 0x19,-0xf0);
  ConstExpI(param_3 + 0x1c,1);
  ConstExpI(param_3 + 0x3a,3);
  pbVar2 = (byte *)TPGetValue(param_1,"projid");
  iVar3 = InfixToPostfix(pbVar2,param_3,param_2,(undefined4 *)0x0,1);
  if (iVar3 != 0) {
    pbVar2 = (byte *)TPGetValue(param_1,"projanim");
    iVar3 = InfixToPostfix(pbVar2,param_3 + 0x25,param_2,(undefined4 *)0x0,1);
    if (iVar3 != 0) {
      pbVar2 = (byte *)TPGetValue(param_1,"offset");
      SCtrlReadExpList(pbVar2,"ii",param_2,&local_14,param_3 + 3,param_3 + 6);
      if ((pbVar2 == (byte *)0x0) || (*local_14 == '\0')) {
        pcVar4 = TPGetValue(param_1,"postype");
        if (pcVar4 != (char *)0x0) {
          iVar3 = ParsePosType(pcVar4);
          param_3[9] = iVar3;
          if (iVar3 == -1) {
            sprintf((char *)(g + 0x81d2),"Illegal postype: %s",pcVar4,&local_14);
            return 0;
          }
        }
        pbVar2 = (byte *)TPGetValue(param_1,"projhitanim");
        iVar3 = InfixToPostfix(pbVar2,param_3 + 0x28,param_2,(undefined4 *)0x0,1);
        if (iVar3 != 0) {
          pbVar2 = (byte *)TPGetValue(param_1,"projremanim");
          if (pbVar2 == (byte *)0x0) {
            expcpytrig(param_3 + 0x2b,param_3 + 0x28);
          }
          else {
            iVar3 = InfixToPostfix(pbVar2,param_3 + 0x2b,param_2,(undefined4 *)0x0,1);
            if (iVar3 == 0) {
              return 0;
            }
          }
          pbVar2 = (byte *)TPGetValue(param_1,"projcancelanim");
          if (pbVar2 == (byte *)0x0) {
            expcpytrig(param_3 + 0x2e,param_3 + 0x2b);
          }
          else {
            iVar3 = InfixToPostfix(pbVar2,param_3 + 0x2e,param_2,(undefined4 *)0x0,1);
            if (iVar3 == 0) {
              return 0;
            }
          }
          pbVar2 = (byte *)TPGetValue(param_1,"projsprpriority");
          iVar3 = InfixToPostfix(pbVar2,param_3 + 0x3a,param_2,(undefined4 *)0x0,1);
          if (iVar3 != 0) {
            pbVar2 = (byte *)TPGetValue(param_1,"projedgebound");
            iVar3 = InfixToPostfix(pbVar2,param_3 + 0x13,param_2,(undefined4 *)0x0,1);
            if (iVar3 != 0) {
              pbVar2 = (byte *)TPGetValue(param_1,"projstagebound");
              iVar3 = InfixToPostfix(pbVar2,param_3 + 0x16,param_2,(undefined4 *)0x0,1);
              if (iVar3 != 0) {
                pbVar2 = (byte *)TPGetValue(param_1,"projheightbound");
                SCtrlReadExpList(pbVar2,"ii",param_2,&local_14,param_3 + 0x19,param_3 + 0x1c);
                if ((pbVar2 == (byte *)0x0) || (*local_14 == '\0')) {
                  pbVar2 = (byte *)TPGetValue(param_1,"velocity");
                  SCtrlReadExpList(pbVar2,"ff",param_2,&local_14,param_3 + 0x3d,param_3 + 0x40);
                  if ((pbVar2 == (byte *)0x0) || (*local_14 == '\0')) {
                    pbVar2 = (byte *)TPGetValue(param_1,"remvelocity");
                    SCtrlReadExpList(pbVar2,"ff",param_2,&local_14,param_3 + 0x49,param_3 + 0x4c);
                    if ((pbVar2 == (byte *)0x0) || (*local_14 == '\0')) {
                      pbVar2 = (byte *)TPGetValue(param_1,"velmul");
                      SCtrlReadExpList(pbVar2,"ff",param_2,&local_14,param_3 + 0x43,param_3 + 0x46);
                      if ((pbVar2 == (byte *)0x0) || (*local_14 == '\0')) {
                        pbVar2 = (byte *)TPGetValue(param_1,"accel");
                        SCtrlReadExpList(pbVar2,"ff",param_2,&local_14,param_3 + 0x4f,param_3 + 0x52
                                        );
                        if ((pbVar2 == (byte *)0x0) || (*local_14 == '\0')) {
                          pbVar2 = (byte *)TPGetValue(param_1,"projscale");
                          SCtrlReadExpList(pbVar2,"ff",param_2,&local_14,param_3 + 0x55,
                                           param_3 + 0x58);
                          if ((pbVar2 == (byte *)0x0) || (*local_14 == '\0')) {
                            pbVar2 = (byte *)TPGetValue(param_1,"projhits");
                            SCtrlReadExpList(pbVar2,"i",param_2,&local_14,param_3 + 0x1f);
                            if ((pbVar2 == (byte *)0x0) || (*local_14 == '\0')) {
                              pbVar2 = (byte *)TPGetValue(param_1,"projpriority");
                              SCtrlReadExpList(pbVar2,"i",param_2,&local_14,param_3 + 0x22);
                              if ((pbVar2 == (byte *)0x0) || (*local_14 == '\0')) {
                                pbVar2 = (byte *)TPGetValue(param_1,"projremove");
                                SCtrlReadExpList(pbVar2,"i",param_2,&local_14,param_3 + 10);
                                if ((pbVar2 == (byte *)0x0) || (*local_14 == '\0')) {
                                  pbVar2 = (byte *)TPGetValue(param_1,"projremovetime");
                                  SCtrlReadExpList(pbVar2,"i",param_2,&local_14,param_3 + 0xd);
                                  if ((pbVar2 == (byte *)0x0) || (*local_14 == '\0')) {
                                    pbVar2 = (byte *)TPGetValue(param_1,"projmisstime");
                                    SCtrlReadExpList(pbVar2,"i",param_2,&local_14,param_3 + 0x10);
                                    if ((pbVar2 == (byte *)0x0) || (*local_14 == '\0')) {
                                      pbVar2 = (byte *)TPGetValue(param_1,"projshadow");
                                      SCtrlReadExpList(pbVar2,"iii",param_2,&local_14,param_3 + 0x31
                                                       ,param_3 + 0x34,param_3 + 0x37);
                                      iVar3 = ItoP_TPConstI(param_1,"pausemovetime",param_3 + 0x5e,
                                                            param_2,0);
                                      if ((iVar3 != 0) &&
                                         (iVar3 = ItoP_TPConstI(param_1,"supermovetime",
                                                                param_3 + 0x5b,param_2,0),
                                         iVar3 != 0)) {
                                        bVar1 = SCtrlParseHitDef(param_1,param_2,param_3 + 0x61);
                                        if (GHIDRA_ZEXT8(bVar1) == 0) {
                                          pcVar4 = "\nError parsing Hitdef of projectile";
                                        }
                                        else {
                                          pcVar4 = TPGetValue(param_1,"afterimage.time");
                                          if (pcVar4 == (char *)0x0) {
                                            return 1;
                                          }
                                          iVar3 = ecalloc(1,0x118);
                                          param_3[0x1a6] = iVar3;
                                          if (iVar3 == 0) {
                                            return 0;
                                          }
                                          iVar3 = SCtrlParseAftImgParams
                                                            (param_1,param_2,(int *)param_3[0x1a6],
                                                             "afterimage.");
                                          if (iVar3 != 0) {
                                            return 1;
                                          }
                                          pcVar4 = "\nError parsing Afterimage of projectile";
                                        }
                                        strcat((char *)(g + 0x81d2),pcVar4);
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
  return 0;
}
#undef local_14

/* SCtrlInitProjectile @ 0x080c8b90, 2110 bytes
 * FIXUP: 9 data addresses written as literals replaced by data-image references
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 40 stack locals placed at their original offsets in a 0x310-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
int SCtrlInitProjectile(int param_1,int *param_2,int param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  float10 fVar5;
  unsigned char ghidra_frame[0x310] __attribute__((aligned(16)));
#define local_30c (*(int *)(ghidra_frame + 0x4))
#define local_308 (*(int *)(ghidra_frame + 0x8))
#define local_2fc (*(int (*)[4])(ghidra_frame + 0x14))
#define local_2ec (*(int *)(ghidra_frame + 0x24))
#define local_2e8 (*(int *)(ghidra_frame + 0x28))
#define local_2e4 (*(int *)(ghidra_frame + 0x2c))
#define local_2e0 (*(int *)(ghidra_frame + 0x30))
#define local_2dc (*(undefined4 *)(ghidra_frame + 0x34))
#define local_2d8 (*(undefined4 *)(ghidra_frame + 0x38))
#define local_2d4 (*(undefined4 *)(ghidra_frame + 0x3c))
#define local_2cc (*(int *)(ghidra_frame + 0x44))
#define local_2c8 (*(int *)(ghidra_frame + 0x48))
#define local_2c4 (*(uint *)(ghidra_frame + 0x4c))
#define local_2c0 (*(int *)(ghidra_frame + 0x50))
#define local_2bc (*(uint *)(ghidra_frame + 0x54))
#define local_2b8 (*(float *)(ghidra_frame + 0x58))
#define local_2b4 (*(float *)(ghidra_frame + 0x5c))
#define local_2b0 (*(int *)(ghidra_frame + 0x60))
#define local_2a8 (*(float *)(ghidra_frame + 0x68))
#define local_2a4 (*(float *)(ghidra_frame + 0x6c))
#define local_298 (*(float *)(ghidra_frame + 0x78))
#define local_294 (*(float *)(ghidra_frame + 0x7c))
#define local_290 (*(float *)(ghidra_frame + 0x80))
#define local_28c (*(float *)(ghidra_frame + 0x84))
#define local_288 (*(float *)(ghidra_frame + 0x88))
#define local_284 (*(float *)(ghidra_frame + 0x8c))
#define local_280 (*(float *)(ghidra_frame + 0x90))
#define local_27c (*(float *)(ghidra_frame + 0x94))
#define local_278 (*(int *)(ghidra_frame + 0x98))
#define local_274 (*(int *)(ghidra_frame + 0x9c))
#define local_270 (*(int *)(ghidra_frame + 0xa0))
#define local_26c (*(int *)(ghidra_frame + 0xa4))
#define local_268 (*(int *)(ghidra_frame + 0xa8))
#define local_264 (*(undefined4 (*)[3])(ghidra_frame + 0xac))
#define local_258 (*(int *)(ghidra_frame + 0xb8))
#define local_254 (*(int *)(ghidra_frame + 0xbc))
#define local_f0 (*(int *)(ghidra_frame + 0x220))
#define local_40 (*(int *)(ghidra_frame + 0x2d0))
#define local_2c (*(int *)(ghidra_frame + 0x2e4))
#define local_28 (*(int *)(ghidra_frame + 0x2e8))
  
  piVar4 = local_2fc;
  for (iVar3 = 0xb7; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar4 = 0;
    piVar4 = piVar4 + 1;
  }
  local_2fc[0] = EvalExpressionI((int)param_2,param_1,1);
  if (local_2fc[0] < 0) {
    local_2fc[0] = 0;
    Warn((int)param_2,(int)&DAT_0827c02a);
  }
  local_2fc[2] = param_2[3];
  iVar3 = EvalExpressionI((int)param_2,param_1 + 0x28,1);
  local_2c4 = (uint)(iVar3 != 0);
  local_2c0 = EvalExpressionI((int)param_2,param_1 + 0x34,1);
  if (local_2c0 < -1) {
    local_2c0 = 1;
    Warn((int)param_2,(int)&DAT_0827c041);
  }
  iVar3 = EvalExpressionI((int)param_2,param_1 + 0xc4,1);
  iVar1 = EvalExpressionI((int)param_2,param_1 + 0xd0,1);
  iVar2 = EvalExpressionI((int)param_2,param_1 + 0xdc,1);
  if (((((iVar3 < -1) || (iVar1 < -1)) || (iVar2 < -1)) || ((0xff < iVar3 || (0xff < iVar1)))) ||
     (0xff < iVar2)) {
    local_2bc = 0xffffffff;
    Warn((int)param_2,(int)&DAT_0827c058);
  }
  else if (((iVar3 == -1) || (iVar1 == -1)) || (iVar2 == -1)) {
    local_2bc = 0xffffffff;
  }
  else {
    local_2bc = (iVar3 >> 3) << ((byte)_rgb_r_shift_16 & 0x1f) |
                (iVar1 >> 2) << ((byte)_rgb_g_shift_16 & 0x1f) |
                (iVar2 >> 3) << ((byte)_rgb_b_shift_16 & 0x1f);
  }
  local_2cc = EvalExpressionI((int)param_2,param_1 + 0x40,1);
  if (local_2cc < 0) {
    local_2cc = 2;
    Warn((int)param_2,(int)&DAT_0827c06c);
  }
  local_2e0 = EvalExpressionI((int)param_2,param_1 + 0x7c,1);
  if (local_2e0 < 0) {
    local_2e0 = 1;
    Warn((int)param_2,(int)&DAT_0827c08a);
  }
  local_2fc[3] = EvalExpressionI((int)param_2,param_1 + 0x88,1);
  local_2ec = EvalExpressionI((int)param_2,param_1 + 0xa0,1);
  if (local_2ec < -1) {
    local_2ec = -1;
    Warn((int)param_2,(int)&DAT_0827c0a8);
  }
  local_2e8 = EvalExpressionI((int)param_2,param_1 + 0xac,1);
  if (local_2e8 < -1) {
    Warn((int)param_2,(int)&DAT_0827c0c1);
  }
  local_2e4 = EvalExpressionI((int)param_2,param_1 + 0xb8,1);
  if (local_2e4 < -1) {
    Warn((int)param_2,(int)&DAT_0827c0dd);
  }
  local_298 = EvalExpressionF(param_2,(int *)(param_1 + 0xf4));
  local_294 = EvalExpressionF(param_2,(int *)(param_1 + 0x100));
  local_288 = EvalExpressionF(param_2,(int *)(param_1 + 0x10c));
  local_284 = EvalExpressionF(param_2,(int *)(param_1 + 0x118));
  local_290 = EvalExpressionF(param_2,(int *)(param_1 + 0x124));
  local_28c = EvalExpressionF(param_2,(int *)(param_1 + 0x130));
  local_280 = EvalExpressionF(param_2,(int *)(param_1 + 0x13c));
  local_27c = EvalExpressionF(param_2,(int *)(param_1 + 0x148));
  local_2a8 = EvalExpressionF(param_2,(int *)(param_1 + 0x154));
  local_2a4 = EvalExpressionF(param_2,(int *)(param_1 + 0x160));
  if (param_2[0x27] != 0) {
    local_2a8 = local_2a8 * GHIDRA_I2F(param_2[0x1f]);
    local_2a4 = local_2a4 * GHIDRA_I2F(param_2[0x20]);
  }
  SCtrlInitHitDef((undefined4 *)(param_1 + 0x184),(int)local_264,param_2);
  local_254 = g[0x74e1];
  g[0x74e1] = g[0x74e1] + 1;
  if (local_258 != 0) {
    local_264[0] = 1;
  }
  if (local_f0 == -1) {
    local_f0 = param_2[0x1b];
  }
  local_2d4 = 0;
  local_2d8 = 0;
  local_2dc = 0;
  local_2fc[1] = 1;
  local_2c8 = param_2[100];
  iVar3 = *(int *)(param_1 + 0x24);
  if (iVar3 < 5) {
    if (iVar3 < 1) {
      if (iVar3 == 0) {
        local_308 = (int)GHIDRA_FIST32(GHIDRA_I2F(param_2[0x67]));
        local_30c = (int)GHIDRA_FIST32(GHIDRA_I2F(param_2[0x68]));
      }
    }
    else {
      if ((((iVar3 == 2) && (param_2[100] == 1)) || ((iVar3 == 1 && (param_2[100] == -1)))) ||
         (iVar3 == 3)) {
        local_308 = g[0x7311];
      }
      else {
        local_308 = g[0x7311] + 0x140;
      }
      local_30c = 0;
    }
  }
  else if (iVar3 == 5) {
    if (param_3 == 0) {
      local_308 = (int)GHIDRA_FIST32(GHIDRA_I2F(param_2[0x67]));
      local_30c = (int)GHIDRA_FIST32(GHIDRA_I2F(param_2[0x68]));
    }
    else {
      local_308 = (int)GHIDRA_FIST32(*(float *)(param_3 + 0x19c));
      local_30c = (int)GHIDRA_FIST32(*(float *)(param_3 + 0x1a0));
    }
  }
  iVar3 = EvalExpressionI((int)param_2,param_1 + 0xc,0);
  local_2b8 = (float)(iVar3 * param_2[100] + local_308);
  iVar3 = EvalExpressionI((int)param_2,param_1 + 0x18,0);
  local_2b4 = (float)(iVar3 + local_30c);
  fVar5 = (float10)param_2[100];
  local_2b0 = param_2[0x69];
  local_298 = local_298 * fVar5;
  local_290 = local_290 * fVar5;
  local_280 = local_280 * fVar5;
  local_40 = EvalExpressionI((int)param_2,param_1 + 0xe8,1);
  iVar3 = EvalExpressionI((int)param_2,param_1 + 0x58,0);
  local_274 = g[0x1082] - iVar3;
  local_26c = iVar3 + g[0x1083] + 0x140;
  local_278 = EvalExpressionI((int)param_2,param_1 + 0x4c,0);
  local_270 = EvalExpressionI((int)param_2,param_1 + 100,0);
  local_268 = EvalExpressionI((int)param_2,param_1 + 0x70,0);
  iVar3 = EvalExpressionI((int)param_2,param_1 + 0x94,1);
  if (iVar3 < -1) {
    iVar3 = 0;
    Warn((int)param_2,(int)&DAT_0827c0f9);
  }
  fVar5 = EvalExpressionF(param_2,(int *)(param_1 + 0x178));
  local_2c = (int)GHIDRA_FIST32(fVar5);
  fVar5 = EvalExpressionF(param_2,(int *)(param_1 + 0x16c));
  local_28 = (int)GHIDRA_FIST32(fVar5);
  iVar3 = ProjArrayAdd(param_4,(int *)param_4[0x87],local_2fc,iVar3);
  if ((iVar3 != -1) &&
     (iVar1 = iVar3 * *(int *)(*(int *)param_4[0x87] + 4) + *(int *)(*(int *)param_4[0x87] + 0x14),
     *(int *)(param_1 + 0x698) != 0)) {
    iVar2 = *(int *)(iVar1 + 0x2d8);
    if (iVar2 == 0) {
      iVar2 = RequestNewAftImg(g[0x413f]);
      *(int *)(iVar1 + 0x2d8) = iVar2;
    }
    if (iVar2 != 0) {
      SCtrlInitAftImgParams(*(int *)(param_1 + 0x698),*(int *)(iVar1 + 0x2d8),iVar1 + 0x284,param_2)
      ;
    }
  }
  return iVar3;
}
#undef local_30c
#undef local_308
#undef local_2fc
#undef local_2ec
#undef local_2e8
#undef local_2e4
#undef local_2e0
#undef local_2dc
#undef local_2d8
#undef local_2d4
#undef local_2cc
#undef local_2c8
#undef local_2c4
#undef local_2c0
#undef local_2bc
#undef local_2b8
#undef local_2b4
#undef local_2b0
#undef local_2a8
#undef local_2a4
#undef local_298
#undef local_294
#undef local_290
#undef local_28c
#undef local_288
#undef local_284
#undef local_280
#undef local_27c
#undef local_278
#undef local_274
#undef local_270
#undef local_26c
#undef local_268
#undef local_264
#undef local_258
#undef local_254
#undef local_f0
#undef local_40
#undef local_2c
#undef local_28

/* ProjMakeInfoFree @ 0x080c93d0, 484 bytes */
void ProjMakeInfoFree(int *param_1)

{
  FreeExpression(param_1);
  FreeExpression(param_1 + 3);
  FreeExpression(param_1 + 6);
  FreeExpression(param_1 + 10);
  FreeExpression(param_1 + 0xd);
  FreeExpression(param_1 + 0x10);
  FreeExpression(param_1 + 0x13);
  FreeExpression(param_1 + 0x16);
  FreeExpression(param_1 + 0x19);
  FreeExpression(param_1 + 0x1c);
  FreeExpression(param_1 + 0x1f);
  FreeExpression(param_1 + 0x22);
  FreeExpression(param_1 + 0x25);
  FreeExpression(param_1 + 0x28);
  FreeExpression(param_1 + 0x2b);
  FreeExpression(param_1 + 0x2e);
  FreeExpression(param_1 + 0x31);
  FreeExpression(param_1 + 0x34);
  FreeExpression(param_1 + 0x37);
  FreeExpression(param_1 + 0x3a);
  FreeExpression(param_1 + 0x3d);
  FreeExpression(param_1 + 0x40);
  FreeExpression(param_1 + 0x43);
  FreeExpression(param_1 + 0x46);
  FreeExpression(param_1 + 0x49);
  FreeExpression(param_1 + 0x4c);
  FreeExpression(param_1 + 0x4f);
  FreeExpression(param_1 + 0x52);
  FreeExpression(param_1 + 0x55);
  FreeExpression(param_1 + 0x58);
  FreeExpression(param_1 + 0x5e);
  FreeExpression(param_1 + 0x5b);
  HitDefEFree((int)(param_1 + 0x61));
  if ((int *)param_1[0x1a6] != (int *)0x0) {
    AftImgParamsEFree((int *)param_1[0x1a6]);
    free((void *)param_1[0x1a6]);
    return;
  }
  return;
}

/* SCtrlParseHelper @ 0x080c95c0, 1230 bytes
 * FIXUP: 1 data addresses written as literals replaced by data-image references
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x20-byte frame (a local's address escapes, see apply_frame_emulation) */
bool SCtrlParseHelper(int param_1,int param_2,char *param_3)

{
  char *pcVar1;
  int iVar2;
  byte *pbVar3;
  char *__format;
  unsigned char ghidra_frame[0x20] __attribute__((aligned(16)));
#define local_14 (*(char **)(ghidra_frame + 0xc))
  
  pcVar1 = TPGetValue(param_1,"helpertype");
  if (pcVar1 == (char *)0x0) {
LAB_080c9656:
    pcVar1 = TPGetValue(param_1,"name");
    if ((pcVar1 != (char *)0x0) &&
       (iVar2 = GetQuotedString(param_1,"name",param_3,0x2f,(char *)0x0), iVar2 == 0)) {
      return false;
    }
    pbVar3 = (byte *)TPGetValue(param_1,"id");
    iVar2 = InfixToPostfix(pbVar3,(int *)(param_3 + 0x30),param_2,(undefined4 *)0x0,1);
    if (iVar2 == 0) {
      return false;
    }
    pbVar3 = (byte *)TPGetValue(param_1,"pos");
    if (pbVar3 != (byte *)0x0) {
      pbVar3 = SCtrlReadExpList(pbVar3,"ii",param_2,&local_14,(int *)(param_3 + 0x40),
                                (int *)(param_3 + 0x4c));
      if (pbVar3 == (byte *)0x0) {
        return false;
      }
      if (*local_14 != '\0') {
        return false;
      }
    }
    pcVar1 = TPGetValue(param_1,"postype");
    if (pcVar1 != (char *)0x0) {
      iVar2 = ParsePosType(pcVar1);
      *(int *)(param_3 + 0x58) = iVar2;
      if (iVar2 == -1) {
        __format = "Illegal postype: %s";
        param_3 = (char *)0x0;
        goto LAB_080c9738;
      }
    }
    iVar2 = ItoP_TPConstI(param_1,"facing",(int *)(param_3 + 0x5c),param_2,1);
    if ((((((iVar2 != 0) &&
           (iVar2 = ItoP_TPConstI(param_1,"stateno",(int *)(param_3 + 0x68),param_2,0), iVar2 != 0))
          && (iVar2 = ItoP_TPConstI(param_1,"keyctrl",(int *)(param_3 + 0x74),param_2,0), iVar2 != 0
             )) && ((iVar2 = ItoP_TPConstI(param_1,"ownpal",(int *)(param_3 + 0x80),param_2,0),
                    iVar2 != 0 &&
                    (iVar2 = ItoP_TPConstI(param_1,"pausemovetime",(int *)(param_3 + 0x98),param_2,0
                                          ), iVar2 != 0)))) &&
        ((iVar2 = ItoP_TPConstI(param_1,"supermovetime",(int *)(param_3 + 0x8c),param_2,0),
         iVar2 != 0 &&
         ((iVar2 = ItoP_TPConstF(param_1,"size.xscale",(int *)(param_3 + 0xa4),param_2,-0x39001000),
          iVar2 != 0 &&
          (iVar2 = ItoP_TPConstF(param_1,"size.yscale",(int *)(param_3 + 0xb0),param_2,-0x39001000),
          iVar2 != 0)))))) &&
       ((iVar2 = ItoP_TPConstI(param_1,"size.ground.back",(int *)(param_3 + 0xbc),param_2,-0x7fef),
        iVar2 != 0 &&
        ((((iVar2 = ItoP_TPConstI(param_1,"size.ground.front",(int *)(param_3 + 200),param_2,-0x7fef
                                 ), iVar2 != 0 &&
           (iVar2 = ItoP_TPConstI(param_1,"size.air.back",(int *)(param_3 + 0xd4),param_2,-0x7fef),
           iVar2 != 0)) &&
          (iVar2 = ItoP_TPConstI(param_1,"size.air.front",(int *)(param_3 + 0xe0),param_2,-0x7fef),
          iVar2 != 0)) &&
         ((iVar2 = ItoP_TPConstI(param_1,"size.height",(int *)(param_3 + 0xec),param_2,-0x7fef),
          iVar2 != 0 &&
          (iVar2 = ItoP_TPConstI(param_1,"size.proj.doscale",(int *)(param_3 + 0xf8),param_2,-0x7fef
                                ), iVar2 != 0)))))))) {
      ConstExpI((int *)(param_3 + 0x104),-0x7fef);
      ConstExpI((int *)(param_3 + 0x110),-0x7fef);
      ConstExpI((int *)(param_3 + 0x11c),-0x7fef);
      ConstExpI((int *)(param_3 + 0x128),-0x7fef);
      pbVar3 = (byte *)TPGetValue(param_1,"size.head.pos");
      if (((pbVar3 == (byte *)0x0) ||
          ((pbVar3 = SCtrlReadExpList(pbVar3,"ii",param_2,&local_14,(int *)(param_3 + 0x104),
                                      (int *)(param_3 + 0x110)), pbVar3 != (byte *)0x0 &&
           (*local_14 == '\0')))) &&
         ((pbVar3 = (byte *)TPGetValue(param_1,"size.mid.pos"), pbVar3 == (byte *)0x0 ||
          ((pbVar3 = SCtrlReadExpList(pbVar3,"ii",param_2,&local_14,(int *)(param_3 + 0x11c),
                                      (int *)(param_3 + 0x128)), pbVar3 != (byte *)0x0 &&
           (*local_14 == '\0')))))) {
        iVar2 = ItoP_TPConstI(param_1,"size.shadowoffset",(int *)(param_3 + 0x134),param_2,-0x7fef);
        return iVar2 != 0;
      }
    }
  }
  else {
    iVar2 = _alemu_stricmp(pcVar1,"normal");
    if (iVar2 == 0) {
      param_3[0x3c] = '\0';
      param_3[0x3d] = '\0';
      param_3[0x3e] = '\0';
      param_3[0x3f] = '\0';
      goto LAB_080c9656;
    }
    iVar2 = _alemu_stricmp(pcVar1,"player");
    if (iVar2 == 0) {
      param_3[0x3c] = '\x01';
      param_3[0x3d] = '\0';
      param_3[0x3e] = '\0';
      param_3[0x3f] = '\0';
      goto LAB_080c9656;
    }
    iVar2 = strimatchlen((int)pcVar1,(int)&DAT_0827c4e2,4);
    if (iVar2 != 0) {
      param_3[0x3c] = '\x02';
      param_3[0x3d] = '\0';
      param_3[0x3e] = '\0';
      param_3[0x3f] = '\0';
      goto LAB_080c9656;
    }
    __format = "Illegal helper type: %s";
LAB_080c9738:
    sprintf((char *)(g + 0x81d2),__format,pcVar1,param_3);
  }
  return false;
}
#undef local_14

/* HelperInfoFree @ 0x080c9a90, 301 bytes */
void HelperInfoFree(int param_1)

{
  FreeExpression((int *)(param_1 + 0x30));
  FreeExpression((int *)(param_1 + 0x40));
  FreeExpression((int *)(param_1 + 0x4c));
  FreeExpression((int *)(param_1 + 0x5c));
  FreeExpression((int *)(param_1 + 0x68));
  FreeExpression((int *)(param_1 + 0x74));
  FreeExpression((int *)(param_1 + 0x80));
  FreeExpression((int *)(param_1 + 0x98));
  FreeExpression((int *)(param_1 + 0x8c));
  FreeExpression((int *)(param_1 + 0xa4));
  FreeExpression((int *)(param_1 + 0xb0));
  FreeExpression((int *)(param_1 + 0xbc));
  FreeExpression((int *)(param_1 + 200));
  FreeExpression((int *)(param_1 + 0xd4));
  FreeExpression((int *)(param_1 + 0xe0));
  FreeExpression((int *)(param_1 + 0xec));
  FreeExpression((int *)(param_1 + 0xf8));
  FreeExpression((int *)(param_1 + 0x104));
  FreeExpression((int *)(param_1 + 0x110));
  FreeExpression((int *)(param_1 + 0x11c));
  FreeExpression((int *)(param_1 + 0x128));
  FreeExpression((int *)(param_1 + 0x134));
  return;
}

/* SCtrlParsePause @ 0x080c9bc0, 137 bytes */
bool SCtrlParsePause(int param_1,int param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = ItoP_TPConstI(param_1,"time",param_3,param_2,0);
  if (((iVar1 != 0) && (iVar1 = ItoP_TPConstI(param_1,"movetime",param_3 + 3,param_2,0), iVar1 != 0)
      ) && (iVar1 = ItoP_TPConstI(param_1,"endcmdbuftime",param_3 + 6,param_2,0), iVar1 != 0)) {
    iVar1 = ItoP_TPConstI(param_1,"pausebg",param_3 + 9,param_2,1);
    return iVar1 != 0;
  }
  return false;
}

/* SCtrlInitPause @ 0x080c9c50, 304 bytes
 * FIXUP: 3 data addresses written as literals replaced by data-image references */
undefined4 SCtrlInitPause(int param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = EvalExpressionI(param_3,param_1,1);
  g[param_2 * 9 + 0x74fa] = iVar2;
  if (iVar2 < 0) {
    Warn(param_3,(int)&DAT_0827c15f);
    g[param_2 * 9 + 0x74fa] = 0;
  }
  iVar3 = EvalExpressionI(param_3,param_1 + 0xc,1);
  iVar2 = param_2 * 4 + 0x1d0;
  *(int *)(iVar2 + param_3 + 0xc) = iVar3;
  if ((iVar3 < 0) || (g[param_2 * 9 + 0x74fa] < iVar3)) {
    Warn(param_3,(int)&DAT_0827c175);
    *(undefined4 *)(iVar2 + param_3 + 0xc) = 0;
  }
  iVar2 = EvalExpressionI(param_3,param_1 + 0x24,1);
  g[param_2 * 9 + 0x74fb] = iVar2;
  iVar2 = EvalExpressionI(param_3,param_1 + 0x18,1);
  piVar1 = g;
  g[param_2 * 9 + 0x74fc] = iVar2;
  if ((iVar2 < 0) || (piVar1[param_2 * 9 + 0x74fa] < iVar2)) {
    Warn(param_3,(int)&DAT_0827c18f);
    g[param_2 * 9 + 0x74fc] = 0;
  }
  return 1;
}

/* PauseInfoFree @ 0x080c9d80, 52 bytes */
void PauseInfoFree(int *param_1)

{
  FreeExpression(param_1);
  FreeExpression(param_1 + 3);
  FreeExpression(param_1 + 6);
  FreeExpression(param_1 + 9);
  return;
}

/* SCtrlParseSuperPause @ 0x080c9dc0, 389 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x20-byte frame (a local's address escapes, see apply_frame_emulation) */
bool SCtrlParseSuperPause(int param_1,int param_2,int *param_3)

{
  bool bVar1;
  int iVar2;
  byte *pbVar3;
  undefined3 extraout_var;
  unsigned char ghidra_frame[0x20] __attribute__((aligned(16)));
#define local_14 (*(char **)(ghidra_frame + 0xc))
  
  SCtrlParsePause(param_1,param_2,param_3);
  iVar2 = ItoP_TPConstI(param_1,"time",param_3,param_2,0x1e);
  if (iVar2 != 0) {
    ConstExpI(param_3 + 0xd,100);
    param_3[0xc] = 1;
    pbVar3 = (byte *)TPGetValue(param_1,"anim");
    bVar1 = ParseAnim(pbVar3,param_3 + 0xd,param_3 + 0xc,param_2);
    if (((GHIDRA_ZEXT8(bVar1) != 0) &&
        (((pbVar3 = (byte *)TPGetValue(param_1,"pos"), pbVar3 == (byte *)0x0 ||
          ((pbVar3 = SCtrlReadExpList(pbVar3,"ff",param_2,&local_14,param_3 + 0x10,param_3 + 0x13),
           *local_14 == '\0' && (pbVar3 != (byte *)0x0)))) &&
         (iVar2 = ItoP_TPConstI(param_1,"darken",param_3 + 0x16,param_2,1), iVar2 != 0)))) &&
       (((iVar2 = ItoP_TPConstF(param_1,"p2defmul",param_3 + 0x19,param_2,0), iVar2 != 0 &&
         (iVar2 = ItoP_TPConstI(param_1,"poweradd",param_3 + 0x1c,param_2,0), iVar2 != 0)) &&
        (iVar2 = ItoP_TPConstI(param_1,"unhittable",param_3 + 0x1f,param_2,1), iVar2 != 0)))) {
      ConstExpI(param_3 + 0x23,-1);
      param_3[0x22] = 1;
      pbVar3 = (byte *)TPGetValue(param_1,"sound");
      iVar2 = ParseSnd(pbVar3,param_3 + 0x23,param_3 + 0x26,param_3 + 0x22,param_2);
      return iVar2 != 0;
    }
  }
  return false;
}
#undef local_14

/* SuperPauseInfoFree @ 0x080c9f50, 124 bytes */
void SuperPauseInfoFree(int *param_1)

{
  PauseInfoFree(param_1);
  FreeExpression(param_1 + 0x16);
  FreeExpression(param_1 + 0x19);
  FreeExpression(param_1 + 0x1c);
  FreeExpression(param_1 + 0x1f);
  FreeExpression(param_1 + 0xd);
  FreeExpression(param_1 + 0x10);
  FreeExpression(param_1 + 0x13);
  FreeExpression(param_1 + 0x23);
  FreeExpression(param_1 + 0x26);
  return;
}

/* MoreExpFree @ 0x080c9fd0, 38 bytes */
void MoreExpFree(int *param_1)

{
  int iVar1;
  
  iVar1 = 4;
  do {
    FreeExpression(param_1);
    param_1 = param_1 + 3;
    iVar1 = iVar1 + -1;
  } while (-1 < iVar1);
  return;
}

