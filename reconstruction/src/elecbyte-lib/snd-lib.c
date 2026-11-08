/*
 * snd-lib.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08056760-0x08058609, 99 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"

extern undefined4 BufferedReadMode __asm__("D_082879d4"); /* file-static 0x082879d4 */
extern int SndMode __asm__("D_082879d8"); /* file-static 0x082879d8 */
extern int SndDriverInstalled __asm__("D_082879dc"); /* file-static 0x082879dc */
extern int SndPanMul __asm__("D_082879e0"); /* file-static 0x082879e0 */
extern int SndNumVoices __asm__("D_082879e4"); /* file-static 0x082879e4 */
extern int *VoiceInfo __asm__("D_082879e8"); /* file-static 0x082879e8 */
extern int *tmpspl __asm__("D_082879ec"); /* file-static 0x082879ec */
extern int MP3Installed __asm__("D_082879f0"); /* file-static 0x082879f0 */
extern int MP3Paused __asm__("D_082879f4"); /* file-static 0x082879f4 */
extern int MODInstalled __asm__("D_082879f8"); /* file-static 0x082879f8 */
extern int CDAInstalled __asm__("D_082879fc"); /* file-static 0x082879fc */
extern int CDALoop __asm__("D_08287a00"); /* file-static 0x08287a00 */
extern int CDATrack __asm__("D_08287a04"); /* file-static 0x08287a04 */
extern int CDAPauseflag __asm__("D_08287a08"); /* file-static 0x08287a08 */
extern int VoiceVol __asm__("D_082a6b40"); /* file-static 0x082a6b40 */
extern int MidiVol __asm__("D_082a6b44"); /* file-static 0x082a6b44 */

/* SndSetMode @ 0x08056760, 10 bytes */
void SndSetMode(int param_1)

{
  SndMode = param_1;
  return;
}

/* GetSndMode @ 0x08056770, 6 bytes */
int GetSndMode(void)

{
  return SndMode;
}

/* SndSetBufReadMode @ 0x08056780, 10 bytes */
void SndSetBufReadMode(undefined4 param_1)

{
  BufferedReadMode = param_1;
  return;
}

/* GetNumVoices @ 0x08056790, 6 bytes */
int GetNumVoices(void)

{
  return SndNumVoices;
}

/* SndInit @ 0x080567a0, 655 bytes
 * FIXUP: 1 exact-text site patches
 * FIXUP: frame emulation: 2 stack locals placed at their original offsets in a 0x420-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 SndInit(uint param_1,uint param_2,int param_3)

{
  int iVar1;
  char *pcVar2;
  int *piVar3;
  uint *puVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  unsigned char ghidra_frame[0x420] __attribute__((aligned(16)));
#define local_420 (*(int *)(ghidra_frame + 0x0))
#define local_41c (*(uint (*)[259])(ghidra_frame + 0x4))
  
  iVar8 = 0;
  local_420 = 0;
  iVar1 = ErrorGet();
  if ((param_1 != 0xffffffff) || (param_2 != 0xffffffff)) {
    memcpy(local_41c,"[sound]\n",9);
    pcVar2 = (char *)SndWavDeviceString(param_1);
    if ((pcVar2 != (char *)0x0) && (param_1 != 0xffffffff)) {
      strcat((char *)local_41c,"digi_card=");
      strcat((char *)local_41c,pcVar2);
      strcat((char *)local_41c,"\n");
    }
    pcVar2 = (char *)SndMidiDeviceString(param_2);
    if ((pcVar2 != (char *)0x0) && (param_2 != 0xffffffff)) {
      strcat((char *)local_41c,"midi_card=");
      strcat((char *)local_41c,pcVar2);
      strcat((char *)local_41c,"\n");
    }
    puVar5 = local_41c;
    do {
      puVar4 = puVar5;
      puVar5 = puVar4 + 1;
      uVar6 = *puVar4 + 0xfefefeff & (*puVar4 ^ 0xffffffff);
      uVar7 = uVar6 & 0x80808080;
    } while (uVar7 == 0);
    if ((uVar6 & 0x8080) == 0) {
      uVar7 = uVar7 >> 0x10;
      puVar5 = (uint *)((int)puVar4 + 6);
    }
    override_config_data
              ((int)local_41c,
               (int)puVar5 + ((-3 - (uint)CARRY1((byte)uVar7,(byte)uVar7)) - (int)local_41c));
  }
  if (SndDriverInstalled != 0) {
    return 0;
  }
  if (param_1 != 0) {
    local_420 = detect_digi_driver(param_1);
    if (local_420 == 0) goto LAB_080569bd;
    if ((0 < param_3) && (param_3 < local_420)) {
      local_420 = param_3;
    }
  }
  if (param_2 != 0) {
    iVar8 = detect_midi_driver(param_2);
    if (iVar8 == 0) goto LAB_080569bd;
    if ((iVar8 == -1) || (iVar8 == 0xffff)) {
      iVar8 = 9;
    }
  }
  reserve_voices(local_420,iVar8);
  iVar8 = install_sound(param_1,param_2,0);
  if (iVar8 != -1) {
    MidiVol = 0x7f;
    VoiceVol = 0x7f;
    SndSetMode(1);
    SndDriverInstalled = 1;
    SndNumVoices = 0x100;
    VoiceInfo = (int *)ecalloc(0x100,0xc);
    if (VoiceInfo != (int *)0x0) {
      if (0 < SndNumVoices) {
        piVar3 = VoiceInfo + 1;
        iVar8 = SndNumVoices;
        do {
          *piVar3 = -1;
          piVar3 = piVar3 + 3;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      tmpspl = create_sample(8,0,8000,1);
      if (tmpspl == (int *)0x0) {
        return 0;
      }
      tmpspl[3] = 0xff;
      ErrorSet(iVar1);
      return 1;
    }
  }
LAB_080569bd:
  ErrorSet(2);
  return 0;
}
#undef local_420
#undef local_41c

/* SndDeInit @ 0x08056a30, 116 bytes */
void SndDeInit(void)

{
  if (SndDriverInstalled != 0) {
    remove_sound();
    SndDriverInstalled = 0;
    SndNumVoices = 0;
    if (VoiceInfo != (int *)0x0) {
      free(VoiceInfo);
      VoiceInfo = (int *)0x0;
    }
    if (tmpspl != (int *)0x0) {
      destroy_sample(tmpspl);
      tmpspl = (int *)0x0;
    }
    SndSetMode(0);
  }
  return;
}

/* SndDetectWavDevice @ 0x08056ab0, 57 bytes */
undefined4 SndDetectWavDevice(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (SndDriverInstalled == 0) {
    if (param_1 != 0) {
      iVar1 = detect_digi_driver(param_1);
      if (iVar1 == 0) goto LAB_08056ad5;
    }
    uVar2 = 1;
  }
  else {
LAB_08056ad5:
    uVar2 = 0;
  }
  return uVar2;
}

/* SndDetectMidiDevice @ 0x08056af0, 57 bytes */
undefined4 SndDetectMidiDevice(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (SndDriverInstalled == 0) {
    if (param_1 != 0) {
      iVar1 = detect_midi_driver(param_1);
      if (iVar1 == 0) goto LAB_08056b15;
    }
    uVar2 = 1;
  }
  else {
LAB_08056b15:
    uVar2 = 0;
  }
  return uVar2;
}

/* SndSetReverseStereo @ 0x08056b30, 21 bytes */
void SndSetReverseStereo(int param_1)

{
  SndPanMul = (uint)(param_1 == 0) * 2 + -1;
  return;
}

/* SndFree @ 0x08056b50, 23 bytes */
void SndFree(void *param_1)

{
  if (param_1 != (void *)0x0) {
    destroy_sample(param_1);
    return;
  }
  return;
}

/* SndMidiFree @ 0x08056b70, 5 bytes
 * REVIEW: calls-missing-in-pid:free,stop_midi */
undefined4 SndMidiFree(void *param_1)

{
  undefined4 uVar1;
  
  uVar1 = destroy_midi(param_1);
  return uVar1;
}

/* SndArrayNew @ 0x08056b80, 78 bytes */
undefined4 * SndArrayNew(size_t param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = (undefined4 *)ecalloc(1,4);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar2 = ArrayNew(param_1,4,0);
    *puVar1 = puVar2;
    if (puVar2 == (undefined4 *)0x0) {
      SndArrayFree(puVar1);
      puVar1 = (undefined4 *)0x0;
    }
  }
  return puVar1;
}

/* SndArrayAdd @ 0x08056bd0, 42 bytes */
bool SndArrayAdd(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = ArrayAdd(*param_1,&param_2,param_3,param_4);
  return iVar1 != -1;
}

/* SndArrayFree @ 0x08056c00, 84 bytes */
undefined4 SndArrayFree(undefined4 *param_1)

{
  void *pvVar1;
  undefined4 in_EAX;
  undefined4 *puVar2;
  undefined4 extraout_EAX;
  
  if (param_1 != (undefined4 *)0x0) {
    pvVar1 = (void *)*param_1;
    puVar2 = (undefined4 *)ArrayScanFirst((int)pvVar1);
    while (puVar2 != (undefined4 *)0x0) {
      SndFree((void *)*puVar2);
      puVar2 = (undefined4 *)ArrayScanNext((int)pvVar1);
    }
    ArrayFree(pvVar1);
    free(param_1);
    return extraout_EAX;
  }
  return in_EAX;
}

/* SndPlay @ 0x08056c60, 74 bytes */
void SndPlay(int *param_1,int param_2,int param_3,undefined4 param_4)

{
  int *piVar1;
  
  if (SndMode == 1) {
    piVar1 = (int *)ArrayAccessGrpItem(*param_1,param_2,param_3);
    if (piVar1 != (int *)0x0) {
      play_sample(*piVar1,param_4,0x7f,1000,0);
    }
  }
  return;
}

/* SndPlayLoop @ 0x08056cb0, 74 bytes */
void SndPlayLoop(int *param_1,int param_2,int param_3,undefined4 param_4)

{
  int *piVar1;
  
  if (SndMode == 1) {
    piVar1 = (int *)ArrayAccessGrpItem(*param_1,param_2,param_3);
    if (piVar1 != (int *)0x0) {
      play_sample(*piVar1,param_4,0x7f,1000,1);
    }
  }
  return;
}

/* SndPlayPanFreq @ 0x08056d00, 100 bytes */
void SndPlayPanFreq(int *param_1,int param_2,int param_3,undefined4 param_4,int param_5,int param_6)

{
  int *piVar1;
  
  if (SndMode == 1) {
    piVar1 = (int *)ArrayAccessGrpItem(*param_1,param_2,param_3);
    if (piVar1 != (int *)0x0) {
      play_sample(*piVar1,param_4,param_5,param_6,0);
      return;
    }
  }
  return;
}

/* SndMidiPlay @ 0x08056d70, 33 bytes */
void SndMidiPlay(int *param_1)

{
  if (SndMode == 1) {
    play_midi(param_1,0);
  }
  return;
}

/* SndMidiPlayLoop @ 0x08056da0, 24 bytes */
void SndMidiPlayLoop(int *param_1,undefined4 param_2,undefined4 param_3)

{
  if (SndMode == 1) {
    play_looped_midi(param_1,param_2,param_3);
    return;
  }
  return;
}

/* SndMidiStop @ 0x08056dc0, 24 bytes */
void SndMidiStop(void)

{
  if (SndMode == 1) {
    stop_midi();
    return;
  }
  return;
}

/* SndMidiPause @ 0x08056de0, 24 bytes */
void SndMidiPause(void)

{
  if (SndMode == 1) {
    midi_pause();
    return;
  }
  return;
}

/* SndMidiResume @ 0x08056e00, 24 bytes */
void SndMidiResume(void)

{
  if (SndMode == 1) {
    midi_resume();
    return;
  }
  return;
}

/* SndMidiSeek @ 0x08056e20, 24 bytes */
void SndMidiSeek(int param_1)

{
  if (SndMode == 1) {
    midi_seek(param_1);
    return;
  }
  return;
}

/* SndVoiceReserve @ 0x08056e40, 113 bytes */
undefined4 SndVoiceReserve(int param_1)

{
  int *piVar1;
  int iVar2;
  
  if ((SndMode == 1) && (VoiceInfo[param_1 * 3 + 2] == 0)) {
    if (VoiceInfo[param_1 * 3 + 1] != -1) {
      deallocate_voice(VoiceInfo[param_1 * 3 + 1]);
    }
    iVar2 = allocate_voice((int)tmpspl);
    piVar1 = VoiceInfo;
    VoiceInfo[param_1 * 3 + 1] = iVar2;
    if (iVar2 != -1) {
      piVar1[param_1 * 3 + 2] = 1;
      return 1;
    }
  }
  return 0;
}

/* SndVoiceReserveAuto @ 0x08056ec0, 90 bytes */
undefined4 SndVoiceReserveAuto(void)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  
  if (SndMode == 1) {
    uVar4 = 0;
    if (0 < SndNumVoices) {
      piVar3 = VoiceInfo + 2;
      do {
        if (*piVar3 == 0) {
          iVar2 = SndVoiceReserve(uVar4);
          return uVar4 | (iVar2 != 0) - 1;
        }
        uVar4 = uVar4 + 1;
        piVar3 = piVar3 + 3;
      } while ((int)uVar4 < SndNumVoices);
    }
    uVar1 = 0xffffffff;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* SndVoiceUnreserve @ 0x08056f20, 94 bytes
 * REVIEW: pid-unaff_
 * FIXUP: return type set to void: only unaffected-register values were returned */
void SndVoiceUnreserve(int param_1)

{
  int *piVar1;
  undefined4 unaff_EBX;
  
  if (SndMode == 1) {
    if (VoiceInfo[param_1 * 3 + 2] != 0) {
      if (VoiceInfo[param_1 * 3 + 1] != -1) {
        deallocate_voice(VoiceInfo[param_1 * 3 + 1]);
      }
      piVar1 = VoiceInfo;
      VoiceInfo[param_1 * 3] = 0;
      piVar1[param_1 * 3 + 2] = 0;
      piVar1[param_1 * 3 + 1] = -1;
    }
  }
  return;
}

/* SndVoiceUnreserveAll @ 0x08056f80, 47 bytes */
undefined4 SndVoiceUnreserveAll(void)

{
  undefined4 in_ECX;
  int iVar1;
  
  if ((SndMode == 1) && (iVar1 = 0, 0 < SndNumVoices)) {
    do {
      SndVoiceUnreserve(iVar1);
      iVar1 = iVar1 + 1;
    } while (iVar1 < SndNumVoices);
  }
  return in_ECX;
}

/* SndVoiceIsReserved @ 0x08056fb0, 30 bytes */
undefined4 SndVoiceIsReserved(int param_1)

{
  if (SndMode != 1) {
    return 0xffffffff;
  }
  return VoiceInfo[param_1 * 3 + 2];
}

/* SndVoiceGetVoiceno @ 0x08056fd0, 30 bytes */
undefined4 SndVoiceGetVoiceno(int param_1)

{
  if (SndMode != 1) {
    return 0xffffffff;
  }
  return VoiceInfo[param_1 * 3 + 1];
}

/* SndVoiceIsPlaying @ 0x08056ff0, 72 bytes */
uint SndVoiceIsPlaying(int param_1)

{
  uint uVar1;
  int iVar2;
  
  if (SndMode == 1) {
    if (VoiceInfo[param_1 * 3 + 1] == -1) {
      uVar1 = 0;
    }
    else {
      iVar2 = voice_get_position(VoiceInfo[param_1 * 3 + 1]);
      uVar1 = (uint)(iVar2 != -1);
    }
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

/* SndVoiceIsFree @ 0x08057040, 67 bytes */
undefined4 SndVoiceIsFree(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  
  if (SndMode == 1) {
    uVar1 = 0;
    if ((VoiceInfo[param_1 * 3 + 2] == 0) && (uVar2 = SndVoiceIsPlaying(param_1), uVar2 == 0)) {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

/* SndVoiceGetFree @ 0x08057090, 64 bytes */
int SndVoiceGetFree(void)

{
  int iVar1;
  int iVar2;
  
  if ((SndMode == 1) && (iVar2 = 0, 0 < SndNumVoices)) {
    do {
      iVar1 = SndVoiceIsFree(iVar2);
      if (iVar1 != 0) {
        return iVar2;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < SndNumVoices);
  }
  return -1;
}

/* SndVoicePlay @ 0x080570d0, 87 bytes */
undefined4 SndVoicePlay(int param_1,int *param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  
  if ((SndMode == 1) && (iVar1 = SndVoicePrepare(param_1,param_2,param_3,param_4), iVar1 != -1)) {
    voice_set_volume(iVar1,param_5);
    voice_start(iVar1);
    return iVar1;
  }
  return 0xffffffff;
}

/* SndVoicePrepare @ 0x08057130, 190 bytes */
int SndVoicePrepare(int param_1,int *param_2,int param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  
  if (SndMode == 1) {
    SndVoiceCleanup();
    piVar1 = (int *)ArrayAccessGrpItem(*param_2,param_3,param_4);
    if (piVar1 != (int *)0x0) {
      iVar2 = VoiceInfo[param_1 * 3 + 1];
      if (iVar2 == -1) {
        iVar2 = allocate_voice((int)tmpspl);
        if (iVar2 == -1) {
          return -1;
        }
        VoiceInfo[param_1 * 3 + 1] = iVar2;
      }
      if (iVar2 == -1) {
        return -1;
      }
      reallocate_voice(iVar2,*piVar1);
      voice_set_volume(iVar2,0x7f);
      voice_set_pan(iVar2,0x7f);
      voice_set_frequency(iVar2,*(int *)(*piVar1 + 8));
      voice_set_playmode(iVar2,0);
      return iVar2;
    }
  }
  return -1;
}

/* SndVoiceStart @ 0x080571f0, 52 bytes */
undefined4 SndVoiceStart(int param_1)

{
  undefined4 uVar1;
  
  if ((SndMode == 1) && (param_1 = VoiceInfo[param_1 * 3 + 1], param_1 != -1)) {
    uVar1 = voice_start(param_1);
    return uVar1;
  }
  return param_1;
}

/* SndVoiceStop @ 0x08057230, 87 bytes */
void SndVoiceStop(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (SndMode == 1) {
    iVar1 = VoiceInfo[param_1 * 3 + 1];
    VoiceInfo[param_1 * 3] = 0;
    if (iVar1 != -1) {
      voice_stop(iVar1);
      iVar2 = voice_check(iVar1);
      if (iVar2 != 0) {
        voice_set_position(iVar1,*(undefined4 *)(iVar2 + 0x10));
      }
    }
  }
  return;
}

/* SndVoiceStopAll @ 0x08057290, 47 bytes */
undefined4 SndVoiceStopAll(void)

{
  undefined4 in_EDX;
  int iVar1;
  
  if ((SndMode == 1) && (iVar1 = 0, 0 < SndNumVoices)) {
    do {
      SndVoiceStop(iVar1);
      iVar1 = iVar1 + 1;
    } while (iVar1 < SndNumVoices);
  }
  return in_EDX;
}

/* SndVoiceSetVol @ 0x080572c0, 52 bytes */
void SndVoiceSetVol(int param_1,int param_2)

{
  if ((SndMode == 1) && (VoiceInfo[param_1 * 3 + 1] != -1)) {
    voice_set_volume(VoiceInfo[param_1 * 3 + 1],param_2);
    return;
  }
  return;
}

/* SndVoiceGetVol @ 0x08057300, 54 bytes */
int SndVoiceGetVol(int param_1)

{
  int iVar1;
  
  if ((SndMode == 1) && (VoiceInfo[param_1 * 3 + 1] != -1)) {
    iVar1 = voice_get_volume(VoiceInfo[param_1 * 3 + 1]);
    return iVar1;
  }
  return 0;
}

/* SndVoiceSetFreq @ 0x08057340, 52 bytes */
void SndVoiceSetFreq(int param_1,int param_2)

{
  if ((SndMode == 1) && (VoiceInfo[param_1 * 3 + 1] != -1)) {
    voice_set_frequency(VoiceInfo[param_1 * 3 + 1],param_2);
    return;
  }
  return;
}

/* SndVoiceGetFreq @ 0x08057380, 54 bytes */
undefined4 SndVoiceGetFreq(int param_1)

{
  undefined4 uVar1;
  
  if ((SndMode == 1) && (VoiceInfo[param_1 * 3 + 1] != -1)) {
    uVar1 = voice_get_frequency(VoiceInfo[param_1 * 3 + 1]);
    return uVar1;
  }
  return 0;
}

/* SndVoiceSetPan @ 0x080573c0, 69 bytes */
void SndVoiceSetPan(int param_1,int param_2)

{
  if ((SndMode == 1) && (VoiceInfo[param_1 * 3 + 1] != -1)) {
    voice_set_pan(VoiceInfo[param_1 * 3 + 1],param_2 * SndPanMul + 0x7f);
    return;
  }
  return;
}

/* SndVoiceGetPan @ 0x08057410, 70 bytes */
int SndVoiceGetPan(int param_1)

{
  int iVar1;
  
  if ((SndMode == 1) && (VoiceInfo[param_1 * 3 + 1] != -1)) {
    iVar1 = voice_get_pan(VoiceInfo[param_1 * 3 + 1]);
    iVar1 = (iVar1 + -0x7f) * SndPanMul;
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

/* SndVoiceSetLoop @ 0x08057460, 68 bytes */
void SndVoiceSetLoop(int param_1,int param_2)

{
  if ((SndMode == 1) && (VoiceInfo[param_1 * 3 + 1] != -1)) {
    voice_set_playmode(VoiceInfo[param_1 * 3 + 1],(uint)(param_2 != 0));
    return;
  }
  return;
}

/* SndVoiceCleanup @ 0x080574b0, 134 bytes */
int * SndVoiceCleanup(void)

{
  int iVar1;
  int *in_EAX;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if ((SndMode == 1) && (iVar3 = 0, 0 < SndNumVoices)) {
    iVar4 = 0;
    iVar2 = SndNumVoices;
    do {
      iVar1 = *(int *)((int)VoiceInfo + iVar4 + 4);
      in_EAX = VoiceInfo;
      if (((iVar1 != -1) && (*(int *)((int)VoiceInfo + iVar4 + 8) == 0)) &&
         (in_EAX = (int *)voice_get_position(iVar1), iVar2 = SndNumVoices,
         in_EAX == (int *)0xffffffff)) {
        deallocate_voice(iVar1);
        in_EAX = VoiceInfo;
        iVar2 = SndNumVoices;
        *(undefined4 *)((int)VoiceInfo + iVar4 + 4) = 0xffffffff;
        *(undefined4 *)((int)in_EAX + iVar4) = 0xffffffff;
      }
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + 0xc;
    } while (iVar3 < iVar2);
  }
  return in_EAX;
}

/* SndIDPlay @ 0x08057540, 95 bytes */
int SndIDPlay(int param_1,int *param_2,int param_3,int param_4,undefined4 param_5)

{
  int iVar1;
  int iVar2;
  
  if (SndMode == 1) {
    iVar1 = SndIDGetChannelOrFree(param_1);
    iVar2 = iVar1;
    if ((iVar1 != -1) && (iVar2 = SndVoicePlay(iVar1,param_2,param_3,param_4,param_5), iVar2 != -1))
    {
      VoiceInfo[iVar1 * 3] = param_1;
      iVar2 = iVar1;
    }
  }
  else {
    iVar2 = -1;
  }
  return iVar2;
}

/* SndIDPrepare @ 0x080575a0, 87 bytes */
int SndIDPrepare(int param_1,int *param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  if (SndMode == 1) {
    iVar1 = SndIDGetChannelOrFree(param_1);
    iVar2 = iVar1;
    if ((iVar1 != -1) && (iVar2 = SndVoicePrepare(iVar1,param_2,param_3,param_4), iVar2 != -1)) {
      VoiceInfo[iVar1 * 3] = param_1;
      iVar2 = iVar1;
    }
  }
  else {
    iVar2 = -1;
  }
  return iVar2;
}

/* SndIDStart @ 0x08057600, 52 bytes */
void SndIDStart(int param_1)

{
  int iVar1;
  
  if (SndMode == 1) {
    iVar1 = SndIDGetChannel(param_1);
    if (iVar1 != -1) {
      SndVoiceStart(iVar1);
      return;
    }
  }
  return;
}

/* SndIDStop @ 0x08057640, 65 bytes */
void SndIDStop(int param_1)

{
  int iVar1;
  
  if (SndMode == 1) {
    if (param_1 == -1) {
      SndVoiceStopAll();
      return;
    }
    iVar1 = SndIDGetChannel(param_1);
    if (iVar1 != -1) {
      SndVoiceStop(iVar1);
    }
  }
  return;
}

/* SndIDIsPlaying @ 0x08057690, 59 bytes */
uint SndIDIsPlaying(int param_1)

{
  int iVar1;
  uint uVar2;
  
  if (SndMode == 1) {
    iVar1 = SndIDGetChannel(param_1);
    if (iVar1 != -1) {
      uVar2 = SndVoiceIsPlaying(iVar1);
      return uVar2;
    }
    uVar2 = 0;
  }
  else {
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

/* SndIDGetChannel @ 0x080576d0, 65 bytes */
int SndIDGetChannel(int param_1)

{
  int iVar1;
  int *piVar2;
  
  if (SndMode == 1) {
    if (param_1 == -1) {
      return -1;
    }
    iVar1 = 0;
    piVar2 = VoiceInfo;
    if (0 < SndNumVoices) {
      do {
        if (*piVar2 == param_1) {
          return iVar1;
        }
        iVar1 = iVar1 + 1;
        piVar2 = piVar2 + 3;
      } while (iVar1 < SndNumVoices);
    }
  }
  return -1;
}

/* SndIDGetChannelOrFree @ 0x08057720, 36 bytes */
int SndIDGetChannelOrFree(int param_1)

{
  int iVar1;
  
  iVar1 = SndIDGetChannel(param_1);
  if (iVar1 == -1) {
    iVar1 = SndVoiceGetFree();
    return iVar1;
  }
  return iVar1;
}

/* SndReadFile @ 0x08057750, 408 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
int * SndReadFile(char *param_1)

{
  bool bVar1;
  FILE *stream;
  size_t __size;
  void *ptr;
  size_t sVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  undefined3 extraout_var;
  int *piVar6;
  
  if (BufferedReadMode == 0) {
    piVar3 = (int *)MFfopenFile(param_1,"rb");
    if (piVar3 == (int *)0x0) {
      return (int *)0x0;
    }
  }
  else {
    stream = fopen(param_1,"rb");
    if (stream == (FILE *)0x0) {
      return (int *)0x0;
    }
    __size = ffilelength(stream);
    ptr = malloc(__size);
    if (ptr == (void *)0x0) {
      fclose(stream);
      return (int *)0x0;
    }
    sVar2 = fread(ptr,__size,1,stream);
    if (sVar2 == 0xffffffff) {
      fclose(stream);
      return (int *)0x0;
    }
    fclose(stream);
    piVar3 = MFfopenMem((int)ptr,__size);
    if (piVar3 == (int *)0x0) {
      free(ptr);
      return (int *)0x0;
    }
    piVar3[6] = 1;
  }
  MFfseek(piVar3,0,0);
  iVar4 = CheckExtension(param_1);
  if (iVar4 == 3) {
    piVar6 = SndArrayNew(1);
    if (piVar6 != (int *)0x0) {
      piVar5 = SndReadFileWAVPtr(piVar3);
      if (piVar5 == (int *)0x0) {
        MFfclose(piVar3);
        SndArrayFree(piVar6);
        return (int *)0x0;
      }
      bVar1 = SndArrayAdd(piVar6,piVar5,0,0);
      if (GHIDRA_ZEXT8(bVar1) == 0) {
        MFfclose(piVar3);
        SndArrayFree(piVar6);
        return (int *)0x0;
      }
      goto LAB_080578d2;
    }
  }
  else {
    if (iVar4 != 4) {
      return (int *)0x0;
    }
    piVar6 = SndReadFileSNDPtr(piVar3);
    if (piVar6 != (int *)0x0) {
LAB_080578d2:
      MFfclose(piVar3);
      return piVar6;
    }
  }
  MFfclose(piVar3);
  return (int *)0x0;
}

/* SndMidiReadFile @ 0x080578f0, 5 bytes
 * REVIEW: calls-missing-in-pid:destroy_midi,lock_midi,malloc,pack_fclose,pack_fopen,pack_fread,pack_mgetl,pack_mgetw */
uint * SndMidiReadFile(byte *param_1)

{
  uint *puVar1;
  
  puVar1 = load_midi(param_1);
  return puVar1;
}

/* SndReadFileWAVPtr @ 0x08057900, 735 bytes
 * FIXUP: 1 data addresses written as literals replaced by data-image references
 * FIXUP: 3 dead flag initialisations of inlined repz cmpsb loops set to constants
 * FIXUP: 1 exact-text site patches
 * FIXUP: frame emulation: 10 stack locals placed at their original offsets in a 0x60-byte frame (a local's address escapes, see apply_frame_emulation) */
int * SndReadFileWAVPtr(int *param_1)

{
  uint uVar1;
  uint uVar2;
  size_t sVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  byte *pbVar7;
  undefined1 uVar8;
  bool bVar9;
  undefined1 uVar10;
  bool bVar11;
  unsigned char ghidra_frame[0x60] __attribute__((aligned(16)));
#define auStack_5c (*(undefined1 (*)[8])(ghidra_frame + 0x4))
#define local_54 (*(int *)(ghidra_frame + 0xc))
#define local_50 (*(int *)(ghidra_frame + 0x10))
#define local_4c (*(int **)(ghidra_frame + 0x14))
#define local_48 (*(uint *)(ghidra_frame + 0x18))
#define local_44 (*(uint *)(ghidra_frame + 0x1c))
#define local_40 (*(uint *)(ghidra_frame + 0x20))
#define local_3c (*(byte (*)[4])(ghidra_frame + 0x24))
#define local_38 (*(int *)(ghidra_frame + 0x28))
#define local_34 (*(byte (*)[36])(ghidra_frame + 0x2c))
  
  uVar8 = 0;  /* dead flag (repz cmpsb, count 4) */
  uVar10 = 0;  /* dead flag (repz cmpsb, count 4) */
  local_40 = 0x5622;
  local_44 = 8;
  local_48 = 1;
  local_4c = (int *)0x0;
  local_50 = MFftell(param_1);
  MFfread(local_3c,0xc,1,param_1);
  iVar4 = 4;
  pbVar5 = local_3c;
  pbVar7 = &DAT_0827727f;
  do {
    if (iVar4 == 0) break;
    iVar4 = iVar4 + -1;
    uVar8 = *pbVar5 < *pbVar7;
    uVar10 = *pbVar5 == *pbVar7;
    pbVar5 = pbVar5 + 1;
    pbVar7 = pbVar7 + 1;
  } while ((bool)uVar10);
  bVar9 = (!(bool)uVar8 && !(bool)uVar10) < (byte)uVar8;
  if ((!(bool)uVar8 && !(bool)uVar10) == (bool)uVar8) {
    iVar4 = 4;
    bVar11 = true;
    pbVar5 = local_34;
    pbVar7 = &DAT_08277284;
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar9 = *pbVar5 < *pbVar7;
      bVar11 = *pbVar5 == *pbVar7;
      pbVar5 = pbVar5 + 1;
      pbVar7 = pbVar7 + 1;
    } while (bVar11);
    if ((!bVar9 && !bVar11) == bVar9) {
      local_54 = local_38 + 8;
      while (iVar4 = MFfeof(param_1), iVar4 == 0) {
        sVar3 = MFfread(local_3c,4,1,param_1);
        if (sVar3 != 1) break;
        uVar8 = auStack_5c < (undefined1 *)0xc;
        uVar10 = 0;  /* dead flag (repz cmpsb, count 4) */
        uVar1 = MFigetl(param_1);
        iVar4 = 4;
        pbVar5 = local_3c;
        pbVar7 = &DAT_08277289;
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          uVar8 = *pbVar5 < *pbVar7;
          uVar10 = *pbVar5 == *pbVar7;
          pbVar5 = pbVar5 + 1;
          pbVar7 = pbVar7 + 1;
        } while ((bool)uVar10);
        bVar9 = (!(bool)uVar8 && !(bool)uVar10) < (byte)uVar8;
        bVar11 = (!(bool)uVar8 && !(bool)uVar10) == (bool)uVar8;
        if (bVar11) {
          uVar2 = MFigetw(param_1);
          if ((uVar2 != 1) || (local_48 = MFigetw(param_1), 1 < local_48 - 1)) break;
          uVar1 = uVar1 - 0x10;
          local_40 = MFigetl(param_1);
          MFigetl(param_1);
          MFigetw(param_1);
          local_44 = MFigetw(param_1);
          if ((local_44 != 8) && (local_44 != 0x10)) break;
        }
        else {
          iVar4 = 4;
          pbVar5 = local_3c;
          pbVar7 = (byte *)(int)&DAT_08283650;
          do {
            if (iVar4 == 0) break;
            iVar4 = iVar4 + -1;
            bVar9 = *pbVar5 < *pbVar7;
            bVar11 = *pbVar5 == *pbVar7;
            pbVar5 = pbVar5 + 1;
            pbVar7 = pbVar7 + 1;
          } while (bVar11);
          if ((!bVar9 && !bVar11) == bVar9) {
            sVar3 = (int)uVar1 / (int)local_48;
            if (local_44 == 0x10) {
              sVar3 = (int)sVar3 / 2;
            }
            local_4c = create_sample(local_44,(local_48 != 2) - 1,local_40,sVar3);
            if (local_4c == (int *)0x0) goto LAB_08057b61;
            if (local_44 == 8) {
              MFfread((void *)local_4c[8],uVar1,1,param_1);
            }
            else {
              iVar6 = 0;
              iVar4 = local_48 * sVar3;
              if (0 < iVar4) {
                do {
                  uVar1 = MFigetw(param_1);
                  *(ushort *)(local_4c[8] + iVar6 * 2) = (ushort)uVar1 ^ 0x8000;
                  iVar6 = iVar6 + 1;
                } while (iVar6 < iVar4);
              }
            }
          }
          else if ((((int)uVar1 < 1) || (iVar4 = MFfseek(param_1,uVar1,1), iVar4 != 0)) ||
                  (iVar4 = MFftell(param_1), local_50 < iVar4 - local_54)) break;
          uVar1 = 0;
        }
LAB_08057b61:
        while ((0 < (int)uVar1 && (uVar2 = MFgetc(param_1), uVar2 != 0xffffffff))) {
          uVar1 = uVar1 - 1;
        }
      }
    }
  }
  if (local_4c != (int *)0x0) {
    lock_sample(local_4c);
  }
  MFfseek(param_1,local_50,0);
  return local_4c;
}
#undef auStack_5c
#undef local_54
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef local_34

/* SndReadFileSNDPtr @ 0x08057be0, 278 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: 1 dead flag initialisations of inlined repz cmpsb loops set to constants
 * FIXUP: frame emulation: 6 stack locals placed at their original offsets in a 0x230-byte frame (a local's address escapes, see apply_frame_emulation) */
int * SndReadFileSNDPtr(int *param_1)

{
  int iVar1;
  size_t sVar2;
  int *piVar3;
  undefined3 extraout_var;
  int iVar4;
  byte *pbVar5;
  byte *pbVar6;
  bool bVar7;
  bool bVar8;
  int *piVar9;
  unsigned char ghidra_frame[0x230] __attribute__((aligned(16)));
#define local_22c (*(int (*)[2])(ghidra_frame + 0x4))
#define local_224 (*(undefined4 *)(ghidra_frame + 0xc))
#define local_220 (*(undefined4 *)(ghidra_frame + 0x10))
#define local_21c (*(byte (*)[16])(ghidra_frame + 0x14))
#define local_20c (*(size_t *)(ghidra_frame + 0x24))
#define local_208 (*(int *)(ghidra_frame + 0x28))
  
  iVar1 = MFftell(param_1);
  sVar2 = MFfread(local_21c,0x200,1,param_1);
  bVar7 = 0;  /* dead flag (repz cmpsb, count 0xc) */
  if (sVar2 == 1) {
    iVar4 = 0xc;
    bVar8 = true;
    pbVar5 = local_21c;
    pbVar6 = (byte *)"ElecbyteSnd";
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar7 = *pbVar5 < *pbVar6;
      bVar8 = *pbVar5 == *pbVar6;
      pbVar5 = pbVar5 + 1;
      pbVar6 = pbVar6 + 1;
    } while (bVar8);
    if ((!bVar7 && !bVar8) == bVar7) {
      piVar9 = SndArrayNew(local_20c);
      if (piVar9 == (int *)0x0) {
        return (int *)0x0;
      }
      if (0 < (int)local_20c) {
        iVar4 = 0;
        do {
          MFfseek(param_1,local_208 + iVar1,0);
          sVar2 = MFfread(local_22c,0x10,1,param_1);
          if (((sVar2 != 1) || (piVar3 = SndReadFileWAVPtr(param_1), piVar3 == (int *)0x0)) ||
             (bVar7 = SndArrayAdd(piVar9,piVar3,local_224,local_220),
             GHIDRA_ZEXT8(bVar7) == 0)) goto LAB_08057c64;
          iVar4 = iVar4 + 1;
          local_208 = local_22c[0];
        } while (iVar4 < (int)local_20c);
      }
      MFfseek(param_1,iVar1,0);
      return piVar9;
    }
    piVar9 = (int *)0x0;
  }
  else {
    piVar9 = (int *)0x0;
  }
LAB_08057c64:
  SndArrayFree(piVar9);
  return (int *)0x0;
}
#undef local_22c
#undef local_224
#undef local_220
#undef local_21c
#undef local_20c
#undef local_208

/* SndSetVol @ 0x08057d00, 81 bytes */
undefined4 SndSetVol(uint param_1,uint param_2)

{
  undefined4 uVar1;
  
  VoiceVol = param_1 & 0xffffffffU - ((int)param_1 >> 0x1f);
  if (0xff < VoiceVol) {
    VoiceVol = 0xff;
  }
  MidiVol = param_2 & 0xffffffffU - ((int)param_2 >> 0x1f);
  if (0xff < MidiVol) {
    MidiVol = 0xff;
  }
  uVar1 = set_volume(VoiceVol,MidiVol);
  return uVar1;
}

/* SndGetVoiceVol @ 0x08057d60, 6 bytes */
int SndGetVoiceVol(void)

{
  return VoiceVol;
}

/* SndGetMidiVol @ 0x08057d70, 6 bytes */
int SndGetMidiVol(void)

{
  return MidiVol;
}

/* SndCorrectVolOff @ 0x08057d80, 40 bytes */
int SndCorrectVolOff(int param_1)

{
  return (int)GHIDRA_FIST32((longdouble)param_1);
}

/* SndParseWavDevice @ 0x08057db0, 143 bytes */
int SndParseWavDevice(char *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = _alemu_stricmp(param_1,"none");
  iVar2 = 0;
  if (iVar1 != 0) {
    iVar1 = _alemu_stricmp(param_1,"auto");
    iVar2 = -1;
    if (iVar1 != 0) {
      iVar1 = _alemu_stricmp(param_1,"oss");
      iVar2 = 0x4f535344;
      if (iVar1 != 0) {
        iVar1 = _alemu_stricmp(param_1,"esd");
        iVar2 = 0x45534444;
        if (iVar1 != 0) {
          iVar1 = _alemu_stricmp(param_1,"alsa");
          iVar2 = ((iVar1 == 0) - 1 & 0xfffffc17) + 999;
        }
      }
    }
  }
  return iVar2;
}

/* SndWavDeviceString @ 0x08057e40, 73 bytes */
undefined4 * SndWavDeviceString(int param_1)

{
  if (param_1 == 999) {
    return (undefined4 *)&DAT_082772a7;
  }
  if (param_1 < 1000) {
    if (param_1 == 0) {
      return (undefined4 *)"0";
    }
  }
  else {
    if (param_1 == 0x45534444) {
      return (undefined4 *)&DAT_082772a3;
    }
    if (param_1 == 0x4f535344) {
      return (undefined4 *)&DAT_0827729f;
    }
  }
  return (undefined4 *)0x0;
}

/* SndParseMidiDevice @ 0x08057e90, 143 bytes */
int SndParseMidiDevice(char *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = _alemu_stricmp(param_1,"none");
  iVar2 = 0;
  if (iVar1 != 0) {
    iVar1 = _alemu_stricmp(param_1,"auto");
    iVar2 = -1;
    if (iVar1 != 0) {
      iVar1 = _alemu_stricmp(param_1,"oss");
      iVar2 = 0x4f53534d;
      if (iVar1 != 0) {
        iVar1 = _alemu_stricmp(param_1,"alsa");
        iVar2 = 1000;
        if (iVar1 != 0) {
          iVar1 = _alemu_stricmp(param_1,"digmid");
          iVar2 = ((iVar1 == 0) - 1 & 0xbbb6b8b5) + 0x44494749;
        }
      }
    }
  }
  return iVar2;
}

/* SndMidiDeviceString @ 0x08057f20, 89 bytes */
undefined4 * SndMidiDeviceString(int param_1)

{
  if (param_1 == 1000) {
    return (undefined4 *)&DAT_082772b7;
  }
  if (param_1 < 0x3e9) {
    if (param_1 == -1) {
      return (undefined4 *)&DAT_0827729a;
    }
    if (param_1 == 0) {
      return (undefined4 *)"0";
    }
  }
  else {
    if (param_1 == 0x44494749) {
      return (undefined4 *)&DAT_082772bc;
    }
    if (param_1 == 0x4f53534d) {
      return (undefined4 *)&DAT_082772b3;
    }
  }
  return (undefined4 *)0x0;
}

/* MP3Init @ 0x08057f80, 45 bytes */
bool MP3Init(void)

{
  int iVar1;
  
  MP3Paused = 0;
  iVar1 = install_amp();
  if (iVar1 != 0) {
    MP3Installed = 1;
  }
  return iVar1 != 0;
}

/* MP3DeInit @ 0x08057fb0, 21 bytes */
void MP3DeInit(void)

{
  if (MP3Installed != 0) {
    MP3Installed = 0;
  }
  return;
}

/* MP3LoadAndPlay @ 0x08057fd0, 27 bytes */
undefined4 MP3LoadAndPlay(char *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (MP3Installed != 0) {
    uVar1 = load_amp(param_1,param_2);
    return uVar1;
  }
  return 0;
}

/* MP3Unload @ 0x08057ff0, 31 bytes */
void MP3Unload(void)

{
  if (MP3Installed != 0) {
    unload_amp();
  }
  MP3Paused = 0;
  return;
}

/* MP3Poll @ 0x08058010, 39 bytes */
void MP3Poll(void)

{
  if ((MP3Installed != 0) && (MP3Paused == 0)) {
    poll_amp();
    return;
  }
  return;
}

/* MP3SetVol @ 0x08058040, 24 bytes */
void MP3SetVol(int param_1)

{
  if (MP3Installed != 0) {
    set_volume_mp3(param_1);
    return;
  }
  return;
}

/* MP3GetVol @ 0x08058060, 27 bytes */
undefined4 MP3GetVol(void)

{
  undefined4 uVar1;
  
  if (MP3Installed != 0) {
    uVar1 = get_volume_mp3();
    return uVar1;
  }
  return 0;
}

/* MP3Pause @ 0x08058080, 11 bytes */
void MP3Pause(void)

{
  MP3Paused = 1;
  return;
}

/* MP3Resume @ 0x08058090, 11 bytes */
void MP3Resume(void)

{
  MP3Paused = 0;
  return;
}

/* MODInit @ 0x080580a0, 43 bytes */
bool MODInit(int param_1)

{
  int iVar1;
  
  iVar1 = install_mod(param_1);
  if (0 < iVar1) {
    MODInstalled = 1;
  }
  return 0 < iVar1;
}

/* MODDeInit @ 0x080580d0, 31 bytes */
void MODDeInit(void)

{
  if (MODInstalled != 0) {
    remove_mod();
    MODInstalled = 0;
  }
  return;
}

/* MODLoad @ 0x080580f0, 86 bytes */
undefined4 MODLoad(byte *param_1)

{
  undefined4 *__ptr;
  undefined1 *puVar1;
  
  if ((MODInstalled != 0) && (__ptr = calloc(1,4), __ptr != (undefined4 *)0x0)) {
    puVar1 = load_mod(param_1);
    *__ptr = puVar1;
    if (puVar1 != (undefined1 *)0x0) {
      return __ptr;
    }
    free(__ptr);
  }
  return 0;
}

/* MODUnload @ 0x08058150, 54 bytes */
undefined4 MODUnload(undefined4 *param_1)

{
  undefined4 extraout_EAX;
  undefined4 in_EDX;
  
  if ((MODInstalled != 0) && (param_1 != (undefined4 *)0x0)) {
    if ((void *)*param_1 != (void *)0x0) {
      destroy_mod((void *)*param_1);
    }
    free(param_1);
    return extraout_EAX;
  }
  return in_EDX;
}

/* MODPlay @ 0x08058190, 36 bytes */
void MODPlay(int *param_1,int param_2)

{
  if (MODInstalled != 0) {
    play_mod(*param_1,param_2);
    return;
  }
  return;
}

/* MODStop @ 0x080581c0, 24 bytes */
void MODStop(void)

{
  if (MODInstalled != 0) {
    stop_mod();
    return;
  }
  return;
}

/* MODPause @ 0x080581e0, 25 bytes */
void MODPause(void)

{
  if (MODInstalled != 0) {
    pause_mod();
    return;
  }
  return;
}

/* MODResume @ 0x08058200, 25 bytes */
void MODResume(void)

{
  if (MODInstalled != 0) {
    resume_mod();
    return;
  }
  return;
}

/* MODSetVol @ 0x08058220, 24 bytes */
void MODSetVol(int param_1)

{
  if (MODInstalled != 0) {
    set_mod_volume(param_1);
    return;
  }
  return;
}

/* MODGetVol @ 0x08058240, 27 bytes */
undefined4 MODGetVol(void)

{
  undefined4 uVar1;
  
  if (MODInstalled != 0) {
    uVar1 = get_mod_volume();
    return uVar1;
  }
  return 0;
}

/* CDAInit @ 0x08058260, 47 bytes */
uint CDAInit(char *param_1)

{
  int iVar1;
  
  if (CDAInstalled == 0) {
    iVar1 = cd_init(param_1);
    CDAInstalled = (int)(iVar1 == 0);
  }
  return CDAInstalled;
}

/* CDADeInit @ 0x08058290, 38 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
void CDADeInit(void)

{
  bool bVar1;
  undefined3 extraout_var;
  
  if (CDAInstalled != 0) {
    bVar1 = CDAIsPlaying();
    if (GHIDRA_ZEXT8(bVar1) != 0) {
      CDAStop();
    }
    cd_exit();
    return;
  }
  return;
}

/* CDAPlay @ 0x080582c0, 118 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
undefined4 CDAPlay(uint param_1,int param_2)

{
  bool bVar1;
  undefined3 extraout_var;
  uint uVar2;
  int iVar3;
  
  if (((CDAInstalled != 0) && (bVar1 = CDAIsPlaying(), GHIDRA_ZEXT8(bVar1) == 0)) &&
     (uVar2 = cd_is_audio((char)param_1), uVar2 == 1)) {
    if (param_2 == 0) {
      iVar3 = cd_play(param_1);
    }
    else {
      iVar3 = cd_play_loop(param_1);
    }
    if (iVar3 == 0) {
      CDALoop = param_2;
      CDATrack = param_1;
      CDAPauseflag = 0;
      return 1;
    }
  }
  return 0;
}

/* CDAStop @ 0x08058340, 51 bytes */
void CDAStop(void)

{
  if (CDAInstalled != 0) {
    cd_stop();
    CDATrack = 0;
    CDALoop = 0;
    CDAPauseflag = 0;
  }
  return;
}

/* CDAPause @ 0x08058380, 54 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
void CDAPause(void)

{
  bool bVar1;
  undefined3 extraout_var;
  
  if ((CDAInstalled != 0) && (CDATrack != 0)) {
    bVar1 = cd_is_paused();
    if (GHIDRA_ZEXT8(bVar1) == 0) {
      CDAPauseflag = 1;
      cd_pause();
      return;
    }
  }
  return;
}

/* CDAResume @ 0x080583c0, 50 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
void CDAResume(void)

{
  bool bVar1;
  undefined3 extraout_var;
  
  if ((CDAInstalled != 0) && (CDATrack != 0)) {
    bVar1 = cd_is_paused();
    if (GHIDRA_ZEXT8(bVar1) != 0) {
      cd_resume();
      CDAPauseflag = 0;
    }
  }
  return;
}

/* CDAPoll @ 0x08058400, 95 bytes
 * FIXUP: 2 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
void CDAPoll(void)

{
  bool bVar1;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  
  if (((CDAInstalled != 0) && (CDATrack != 0)) && (CDAPauseflag == 0)) {
    if (CDALoop == 0) {
      bVar1 = CDAIsPlaying();
      if (GHIDRA_ZEXT8(bVar1) == 0) {
        CDATrack = 0;
      }
    }
    else {
      bVar1 = CDAIsPlaying();
      if (GHIDRA_ZEXT8(bVar1) == 0) {
        cd_play_now(CDATrack);
      }
    }
  }
  return;
}

/* CDAIsPlaying @ 0x08058460, 38 bytes */
bool CDAIsPlaying(void)

{
  bool bVar1;
  
  if ((CDAInstalled != 0) && (CDATrack != 0)) {
    bVar1 = cd_is_playing();
    return bVar1;
  }
  return false;
}

/* CDAIsPaused @ 0x08058490, 38 bytes */
bool CDAIsPaused(void)

{
  bool bVar1;
  
  if ((CDAInstalled != 0) && (CDATrack != 0)) {
    bVar1 = cd_is_paused();
    return bVar1;
  }
  return false;
}

/* CDATrackIsAudio @ 0x080584c0, 27 bytes */
uint CDATrackIsAudio(undefined1 param_1)

{
  uint uVar1;
  
  if (CDAInstalled != 0) {
    uVar1 = cd_is_audio(param_1);
    return uVar1;
  }
  return 0xffffffff;
}

/* CDACurrentTrack @ 0x080584e0, 38 bytes */
undefined1 CDACurrentTrack(void)

{
  undefined1 uVar1;
  
  if ((CDAInstalled != 0) && (CDATrack != 0)) {
    uVar1 = cd_current_track();
    return uVar1;
  }
  return 0;
}

/* CDAGetTrackRange @ 0x08058510, 54 bytes */
bool CDAGetTrackRange(uint *param_1,uint *param_2)

{
  int iVar1;
  bool bVar2;
  
  if (CDAInstalled == 0) {
    bVar2 = false;
  }
  else {
    iVar1 = cd_get_tracks(param_1,param_2);
    bVar2 = iVar1 == 0;
  }
  return bVar2;
}

/* CDASetVol @ 0x08058550, 53 bytes */
void CDASetVol(uint param_1)

{
  uint l;
  
  if (CDAInstalled != 0) {
    l = param_1 & 0xffffffffU - ((int)param_1 >> 0x1f);
    if (0xfe < (int)l) {
      l = 0xff;
    }
    cd_set_volume(l,l);
  }
  return;
}

/* CDAGetVol @ 0x08058590, 54 bytes
 * FIXUP: frame emulation: 2 stack locals placed at their original offsets in a 0x10-byte frame (a local's address escapes, see apply_frame_emulation) */
int CDAGetVol(void)

{
  int iVar1;
  unsigned char ghidra_frame[0x10] __attribute__((aligned(16)));
#define local_8 (*(uint *)(ghidra_frame + 0x8))
#define local_4 (*(uint *)(ghidra_frame + 0xc))
  
  if (CDAInstalled == 0) {
    iVar1 = 0;
  }
  else {
    cd_get_volume(&local_8,&local_4);
    iVar1 = (int)(local_4 + local_8) >> 1;
  }
  return iVar1;
}
#undef local_8
#undef local_4

/* CDAEject @ 0x080585d0, 25 bytes */
void CDAEject(void)

{
  if (CDAInstalled != 0) {
    cd_eject();
    return;
  }
  return;
}

/* CDAClose @ 0x080585f0, 25 bytes */
void CDAClose(void)

{
  if (CDAInstalled != 0) {
    cd_close();
    return;
  }
  return;
}

