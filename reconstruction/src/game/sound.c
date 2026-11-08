/*
 * sound.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x080b9fd0-0x080ba38d, 8 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* GameSndPlay @ 0x080b9fd0, 34 bytes
 * FIXUP: return type set to void: only unaffected-register values were returned */
void GameSndPlay(int *param_1,int param_2,int param_3,int param_4)

{
  undefined4 extraout_EAX;
  
  GameSndPlayID(-1,param_1,param_2,param_3,param_4);
  return;
}

/* GameSndPlayID @ 0x080ba000, 142 bytes */
void GameSndPlayID(int param_1,int *param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = SndCorrectVolOff(param_5);
  uVar2 = iVar1 + g[0x6ef4] & 0xffffffffU - (iVar1 + g[0x6ef4] >> 0x1f);
  if (0xff < (int)uVar2) {
    uVar2 = 0xff;
  }
  if ((((g[0x6ef3] != 0) && (param_2 != (int *)0x0)) && (g[0x7308] == 0)) && (param_3 != -1)) {
    SndIDPlay(param_1,param_2,param_3,param_4,uVar2);
    return;
  }
  return;
}

/* GameSndPlayIDPos @ 0x080ba090, 237 bytes */
int GameSndPlayIDPos(int param_1,int param_2,int *param_3,int param_4,int param_5,int param_6)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  piVar1 = g;
  if ((((g[0x6ef3] != 0) && (param_3 != (int *)0x0)) && (g[0x7308] == 0)) && (param_4 != -1)) {
    piVar1 = (int *)SndIDPrepare(param_1,param_3,param_4,param_5);
    if (piVar1 != (int *)0xffffffff) {
      if (g[0x756c] == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = ScrPositionToPan(param_2);
      }
      iVar3 = SndCorrectVolOff(param_6);
      iVar3 = PanVolumeAdjust(iVar3 + g[0x6ef4],iVar2);
      iVar4 = SndVoiceGetFreq((int)piVar1);
      SndVoiceSetVol((int)piVar1,iVar3);
      SndVoiceSetFreq((int)piVar1,iVar4);
      SndVoiceSetPan((int)piVar1,iVar2);
      SndVoiceSetLoop((int)piVar1,0);
      piVar1 = (int *)SndVoiceStart((int)piVar1);
    }
  }
  return (int)piVar1;
}

/* ScrPositionToPan @ 0x080ba180, 170 bytes
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
int ScrPositionToPan(int param_1)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = param_1 - 0xa0;
  if (-0x29 < (int)uVar2) {
    uVar2 = uVar2 & ((int)uVar2 < 0x29) - 1;
  }
  if ((int)uVar2 < -0x28) {
    uVar2 = uVar2 + 0x28;
  }
  else if (0x28 < (int)uVar2) {
    uVar2 = uVar2 - 0x28;
  }
  if (g[0x756d] + -0x14 < 1) {
    iVar1 = 0;
  }
  else {
    iVar1 = (int)GHIDRA_FIST32(((float10)(int)uVar2 * 128.0) / (float)(g[0x756d] + -0x14));
  }
  iVar1 = SndCorrectVolOff(iVar1);
  if (iVar1 < -0x7f) {
    iVar1 = -0x7f;
  }
  if (0x7f < iVar1) {
    iVar1 = 0x7f;
  }
  return iVar1;
}

/* PanVolumeAdjust @ 0x080ba230, 98 bytes */
uint PanVolumeAdjust(int param_1,int param_2)

{
  uint uVar1;
  
  if (param_2 < 0) {
    param_2 = -param_2;
  }
  uVar1 = (uint)GHIDRA_FIST32((1.0 - (float)param_2 * 0.00390625) * (float)param_1);
  uVar1 = uVar1 & 0xffffffffU - ((int)uVar1 >> 0x1f);
  if (0xff < (int)uVar1) {
    uVar1 = 0xff;
  }
  return uVar1;
}

/* GameSetVol @ 0x080ba2a0, 132 bytes */
void GameSetVol(int param_1,uint param_2)

{
  uint uVar1;
  
  if (param_1 == -1) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = (param_1 * g[0x79a2]) / 0x32;
  }
  if (param_2 != 0xffffffff) {
    param_2 = (int)(param_2 * g[0x79a3]) / 0x32;
  }
  if (g[0x6ef3] != 0) {
    SndSetVol(uVar1,param_2);
    return;
  }
  return;
}

/* PlayerSndID @ 0x080ba330, 46 bytes */
int PlayerSndID(int param_1,int param_2)

{
  if (param_2 == -1) {
    return -1;
  }
  return param_2 * g[0x7395] + *(int *)(param_1 + 8) + 1000;
}

/* ParseSndGI @ 0x080ba360, 45 bytes */
void ParseSndGI(int param_1,char *param_2,undefined4 *param_3,int param_4)

{
  *param_3 = 0xffffffff;
  TPScanf(param_1,param_2,"%i,%i",param_3,param_4);
  return;
}

