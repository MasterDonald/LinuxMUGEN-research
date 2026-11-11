/*
 * snd-lib.c -- sound
 * Allegro sound setup, sound arrays (.snd/.wav), voice channels owned by
 * ids, MIDI, MP3 (libamp), tracker modules (jgmod) and CD audio (libcda).
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/snd-lib.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"

extern uint32_t BufferedReadMode __asm__("D_082879d4"); /* file-static 0x082879d4 */
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

/* SndSetMode @ 0x08056760, 10 bytes
 *
 * Sets the sound mode (1 = enabled, 0 = no sound).
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: GameInit, SndDeInit, SndInit
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndSetMode(int arg1)

{
  SndMode = arg1;
  return;
}

/* GetSndMode @ 0x08056770, 6 bytes
 *
 * Returns the sound mode; character loading skips sound files when sound is
 * off.
 *
 * Called by: PlayerDefLoadPtr, PlayerDefLoadZip
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
int GetSndMode(void)

{
  return SndMode;
}

/* SndSetBufReadMode @ 0x08056780, 10 bytes
 *
 * Selects how sound files are read: through a file stream, or loaded into
 * memory first.
 *
 * Parameters:
 *   arg1         uint32_t
 *
 * Called by: GameConfigRead
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndSetBufReadMode(uint32_t arg1)

{
  BufferedReadMode = arg1;
  return;
}

/* GetNumVoices @ 0x08056790, 6 bytes
 *
 * Returns the number of voice channels. Not called in this build.
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
int GetNumVoices(void)

{
  return SndNumVoices;
}

/* SndInit @ 0x080567a0, 655 bytes
 *
 * Installs sound. It builds an Allegro configuration text ("[sound]" with
 * digi_card and midi_card from the configured devices), installs Allegro
 * sound with that driver pair, and allocates the voice channel table for
 * `voices` channels. Sets error 2 ("Can't init sound") on failure, and the
 * sound mode to 1 on success.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         uint32_t
 *   arg3         int
 *
 * Calls: ErrorGet, SndWavDeviceString, SndMidiDeviceString, SndSetMode,
 *        ecalloc, ErrorSet
 * C library: memcpy, strcat, override_config_data, detect_digi_driver,
 *            detect_midi_driver, reserve_voices, install_sound,
 *            create_sample
 * Called by: GameInit
 *
 * Elecbyte file: src/lib/snd-lib.c
 * Note: 1 exact-text site patches (see SITE_PATCHES in
 *       tools/build_source_tree.py)
 * Note: Locals live in `frame`, laid out as on the original stack (0x420 bytes,
 *       2 variables), because their address is taken.
 */
uint32_t SndInit(uint32_t arg1,uint32_t arg2,int arg3)

{
  int i1;
  char *pc2;
  int *pi3;
  uint32_t *pu4;
  uint32_t *pu5;
  uint32_t u6;
  uint32_t u7;
  int i8;
  unsigned char frame[0x420] __attribute__((aligned(16)));
#define stk_420 (*(int *)(frame + 0x0))
#define stk_41c (*(uint32_t (*)[259])(frame + 0x4))
  
  i8 = 0;
  stk_420 = 0;
  i1 = ErrorGet();
  if ((arg1 != 0xffffffff) || (arg2 != 0xffffffff)) {
    memcpy(stk_41c,"[sound]\n",9);
    pc2 = (char *)SndWavDeviceString(arg1);
    if ((pc2 != (char *)0x0) && (arg1 != 0xffffffff)) {
      strcat((char *)stk_41c,"digi_card=");
      strcat((char *)stk_41c,pc2);
      strcat((char *)stk_41c,"\n");
    }
    pc2 = (char *)SndMidiDeviceString(arg2);
    if ((pc2 != (char *)0x0) && (arg2 != 0xffffffff)) {
      strcat((char *)stk_41c,"midi_card=");
      strcat((char *)stk_41c,pc2);
      strcat((char *)stk_41c,"\n");
    }
    pu5 = stk_41c;
    do {
      pu4 = pu5;
      pu5 = pu4 + 1;
      u6 = *pu4 + 0xfefefeff & (*pu4 ^ 0xffffffff);
      u7 = u6 & 0x80808080;
    } while (u7 == 0);
    if ((u6 & 0x8080) == 0) {
      u7 = u7 >> 0x10;
      pu5 = (uint32_t *)((int)pu4 + 6);
    }
    override_config_data
              ((int)stk_41c,
               (int)pu5 + ((-3 - (uint32_t)CARRY1((uint8_t)u7,(uint8_t)u7)) - (int)stk_41c));
  }
  if (SndDriverInstalled != 0) {
    return 0;
  }
  if (arg1 != 0) {
    stk_420 = detect_digi_driver(arg1);
    if (stk_420 == 0) goto L_080569bd;
    if ((0 < arg3) && (arg3 < stk_420)) {
      stk_420 = arg3;
    }
  }
  if (arg2 != 0) {
    i8 = detect_midi_driver(arg2);
    if (i8 == 0) goto L_080569bd;
    if ((i8 == -1) || (i8 == 0xffff)) {
      i8 = 9;
    }
  }
  reserve_voices(stk_420,i8);
  i8 = install_sound(arg1,arg2,0);
  if (i8 != -1) {
    MidiVol = 0x7f;
    VoiceVol = 0x7f;
    SndSetMode(1);
    SndDriverInstalled = 1;
    SndNumVoices = 0x100;
    VoiceInfo = (int *)ecalloc(0x100,0xc);
    if (VoiceInfo != (int *)0x0) {
      if (0 < SndNumVoices) {
        pi3 = VoiceInfo + 1;
        i8 = SndNumVoices;
        do {
          *pi3 = -1;
          pi3 = pi3 + 3;
          i8 = i8 + -1;
        } while (i8 != 0);
      }
      tmpspl = create_sample(8,0,8000,1);
      if (tmpspl == (int *)0x0) {
        return 0;
      }
      tmpspl[3] = 0xff;
      ErrorSet(i1);
      return 1;
    }
  }
L_080569bd:
  ErrorSet(2);
  return 0;
}
#undef stk_420
#undef stk_41c

/* SndDeInit @ 0x08056a30, 116 bytes
 *
 * Removes Allegro sound, frees the voice table and the placeholder sample
 * used to allocate voices, and sets the sound mode to 0.
 *
 * Calls: SndSetMode
 * C library: remove_sound, free, destroy_sample
 * Called by: GameDeInit
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
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

/* SndDetectWavDevice @ 0x08056ab0, 57 bytes
 *
 * Returns 1 if the given digital sound driver is available (Allegro
 * detect_digi_driver), checked only before sound is installed. Not called in
 * this build.
 *
 * Parameters:
 *   arg1         int
 *
 * C library: detect_digi_driver
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t SndDetectWavDevice(int arg1)

{
  int i1;
  uint32_t u2;
  
  if (SndDriverInstalled == 0) {
    if (arg1 != 0) {
      i1 = detect_digi_driver(arg1);
      if (i1 == 0) goto L_08056ad5;
    }
    u2 = 1;
  }
  else {
L_08056ad5:
    u2 = 0;
  }
  return u2;
}

/* SndDetectMidiDevice @ 0x08056af0, 57 bytes
 *
 * Returns 1 if the given MIDI driver is available. Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *
 * C library: detect_midi_driver
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t SndDetectMidiDevice(int arg1)

{
  int i1;
  uint32_t u2;
  
  if (SndDriverInstalled == 0) {
    if (arg1 != 0) {
      i1 = detect_midi_driver(arg1);
      if (i1 == 0) goto L_08056b15;
    }
    u2 = 1;
  }
  else {
L_08056b15:
    u2 = 0;
  }
  return u2;
}

/* SndSetReverseStereo @ 0x08056b30, 21 bytes
 *
 * Sets the stereo direction: panning values are multiplied by -1 when
 * reverse stereo is on (mugen.cfg ReverseStereo).
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: GameConfigRead
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndSetReverseStereo(int arg1)

{
  SndPanMul = (uint32_t)(arg1 == 0) * 2 + -1;
  return;
}

/* SndFree @ 0x08056b50, 23 bytes
 *
 * Frees one sound's Allegro sample.
 *
 * Parameters:
 *   arg1         void *
 *
 * C library: destroy_sample
 * Called by: SndArrayFree
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndFree(void *arg1)

{
  if (arg1 != (void *)0x0) {
    destroy_sample(arg1);
    return;
  }
  return;
}

/* SndMidiFree @ 0x08056b70, 5 bytes
 *
 * Frees a MIDI file (destroy_midi).
 *
 * Parameters:
 *   arg1         void *
 *
 * C library: destroy_midi
 * Called by: BGMFree
 *
 * Elecbyte file: src/lib/snd-lib.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to
 *       free,stop_midi
 */
uint32_t SndMidiFree(void *arg1)

{
  uint32_t u1;
  
  u1 = destroy_midi(arg1);
  return u1;
}

/* SndArrayNew @ 0x08056b80, 78 bytes
 *
 * Creates an empty sound array with room for `capacity` sounds.
 *
 * Parameters:
 *   arg1         size_t
 *
 * Calls: ecalloc, ArrayNew, SndArrayFree
 * Called by: SndReadFile, SndReadFileSNDPtr
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t * SndArrayNew(size_t arg1)

{
  uint32_t *mem;
  uint32_t *array;
  
  mem = (uint32_t *)ecalloc(1,4);
  if (mem == (uint32_t *)0x0) {
    mem = (uint32_t *)0x0;
  }
  else {
    array = ArrayNew(arg1,4,0);
    *mem = array;
    if (array == (uint32_t *)0x0) {
      SndArrayFree(mem);
      mem = (uint32_t *)0x0;
    }
  }
  return mem;
}

/* SndArrayAdd @ 0x08056bd0, 42 bytes
 *
 * Adds a sample to a sound array under key (group, number). Returns true on
 * success.
 *
 * Parameters:
 *   sounds       int *
 *   sample       uint32_t
 *   grpno        uint32_t
 *   itemno       uint32_t
 *
 * Calls: ArrayAdd
 * Called by: SndReadFile, SndReadFileSNDPtr
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
bool SndArrayAdd(int *sounds,uint32_t sample,uint32_t grpno,uint32_t itemno)

{
  int index;
  
  index = ArrayAdd(*sounds,&sample,grpno,itemno);
  return index != -1;
}

/* SndArrayFree @ 0x08056c00, 84 bytes
 *
 * Frees every sample of a sound array, then the array.
 *
 * Parameters:
 *   sounds       uint32_t *
 *
 * Calls: ArrayScanFirst, SndFree, ArrayScanNext, ArrayFree
 * C library: free
 * Called by: GameFreeFightData, GameUnloadSystem, PlayerRCFree,
 *            SndArrayNew, SndReadFile, SndReadFileSNDPtr
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t SndArrayFree(uint32_t *sounds)

{
  void *array;
  uint32_t entry_EAX;
  uint32_t *item;
  uint32_t stale_EAX;
  
  if (sounds != (uint32_t *)0x0) {
    array = (void *)*sounds;
    item = (uint32_t *)ArrayScanFirst((int)array);
    while (item != (uint32_t *)0x0) {
      SndFree((void *)*item);
      item = (uint32_t *)ArrayScanNext((int)array);
    }
    ArrayFree(array);
    free(sounds);
    return stale_EAX;
  }
  return entry_EAX;
}

/* SndPlay @ 0x08056c60, 74 bytes
 *
 * Plays sound (group, number) once at volume `vol`, centred, normal speed
 * (Allegro play_sample). Not called in this build.
 *
 * Parameters:
 *   sounds       int *
 *   grpno        int
 *   itemno       int
 *   vol          uint32_t
 *
 * Calls: ArrayAccessGrpItem
 * C library: play_sample
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndPlay(int *sounds,int grpno,int itemno,uint32_t vol)

{
  int *item;
  
  if (SndMode == 1) {
    item = (int *)ArrayAccessGrpItem(*sounds,grpno,itemno);
    if (item != (int *)0x0) {
      play_sample(*item,vol,0x7f,1000,0);
    }
  }
  return;
}

/* SndPlayLoop @ 0x08056cb0, 74 bytes
 *
 * Plays sound (group, number) looped. Not called in this build.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *   arg4         uint32_t
 *
 * Calls: ArrayAccessGrpItem
 * C library: play_sample
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndPlayLoop(int *arg1,int arg2,int arg3,uint32_t arg4)

{
  int *item;
  
  if (SndMode == 1) {
    item = (int *)ArrayAccessGrpItem(*arg1,arg2,arg3);
    if (item != (int *)0x0) {
      play_sample(*item,arg4,0x7f,1000,1);
    }
  }
  return;
}

/* SndPlayPanFreq @ 0x08056d00, 100 bytes
 *
 * Plays sound (group, number) with volume, panning and frequency. Not called
 * in this build.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *   arg4         uint32_t
 *   arg5         int
 *   arg6         int
 *
 * Calls: ArrayAccessGrpItem
 * C library: play_sample
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndPlayPanFreq(int *arg1,int arg2,int arg3,uint32_t arg4,int arg5,int arg6)

{
  int *item;
  
  if (SndMode == 1) {
    item = (int *)ArrayAccessGrpItem(*arg1,arg2,arg3);
    if (item != (int *)0x0) {
      play_sample(*item,arg4,arg5,arg6,0);
      return;
    }
  }
  return;
}

/* SndMidiPlay @ 0x08056d70, 33 bytes
 *
 * Plays a MIDI file once. Not called in this build.
 *
 * Parameters:
 *   arg1         int *
 *
 * C library: play_midi
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndMidiPlay(int *arg1)

{
  if (SndMode == 1) {
    play_midi(arg1,0);
  }
  return;
}

/* SndMidiPlayLoop @ 0x08056da0, 24 bytes
 *
 * Plays a MIDI file looped between two positions (play_looped_midi). Used
 * for stage music.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         uint32_t
 *   arg3         uint32_t
 *
 * C library: play_looped_midi
 * Called by: BGMStart
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndMidiPlayLoop(int *arg1,uint32_t arg2,uint32_t arg3)

{
  if (SndMode == 1) {
    play_looped_midi(arg1,arg2,arg3);
    return;
  }
  return;
}

/* SndMidiStop @ 0x08056dc0, 24 bytes
 *
 * Stops MIDI playback. Not called in this build.
 *
 * C library: stop_midi
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndMidiStop(void)

{
  if (SndMode == 1) {
    stop_midi();
    return;
  }
  return;
}

/* SndMidiPause @ 0x08056de0, 24 bytes
 *
 * Pauses MIDI playback. Not called in this build.
 *
 * C library: midi_pause
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndMidiPause(void)

{
  if (SndMode == 1) {
    midi_pause();
    return;
  }
  return;
}

/* SndMidiResume @ 0x08056e00, 24 bytes
 *
 * Resumes MIDI playback. Not called in this build.
 *
 * C library: midi_resume
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndMidiResume(void)

{
  if (SndMode == 1) {
    midi_resume();
    return;
  }
  return;
}

/* SndMidiSeek @ 0x08056e20, 24 bytes
 *
 * Seeks in the MIDI file. Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *
 * C library: midi_seek
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndMidiSeek(int arg1)

{
  if (SndMode == 1) {
    midi_seek(arg1);
    return;
  }
  return;
}

/* SndVoiceReserve @ 0x08056e40, 113 bytes
 *
 * Reserves channel `ch`: allocates an Allegro voice for it and marks it
 * reserved, so automatic channel selection skips it. Returns nonzero on
 * success.
 *
 * Parameters:
 *   ch           int
 *
 * C library: deallocate_voice, allocate_voice
 * Called by: SndVoiceReserveAuto
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t SndVoiceReserve(int ch)

{
  int *pi1;
  int i2;
  
  if ((SndMode == 1) && (VoiceInfo[ch * 3 + 2] == 0)) {
    if (VoiceInfo[ch * 3 + 1] != -1) {
      deallocate_voice(VoiceInfo[ch * 3 + 1]);
    }
    i2 = allocate_voice((int)tmpspl);
    pi1 = VoiceInfo;
    VoiceInfo[ch * 3 + 1] = i2;
    if (i2 != -1) {
      pi1[ch * 3 + 2] = 1;
      return 1;
    }
  }
  return 0;
}

/* SndVoiceReserveAuto @ 0x08056ec0, 90 bytes
 *
 * Reserves the first free channel and returns its number, or -1. Not called
 * in this build.
 *
 * Calls: SndVoiceReserve
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t SndVoiceReserveAuto(void)

{
  uint32_t u1;
  int i2;
  int *pi3;
  uint32_t u4;
  
  if (SndMode == 1) {
    u4 = 0;
    if (0 < SndNumVoices) {
      pi3 = VoiceInfo + 2;
      do {
        if (*pi3 == 0) {
          i2 = SndVoiceReserve(u4);
          return u4 | (i2 != 0) - 1;
        }
        u4 = u4 + 1;
        pi3 = pi3 + 3;
      } while ((int)u4 < SndNumVoices);
    }
    u1 = 0xffffffff;
  }
  else {
    u1 = 0;
  }
  return u1;
}

/* SndVoiceUnreserve @ 0x08056f20, 94 bytes
 *
 * Releases a reserved channel and its voice.
 *
 * Parameters:
 *   ch           int
 *
 * C library: deallocate_voice
 * Called by: SndVoiceUnreserveAll
 *
 * Elecbyte file: src/lib/snd-lib.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: Returns nothing (the original left only stale register values).
 */
void SndVoiceUnreserve(int ch)

{
  int *pi1;
  uint32_t saved_EBX;
  
  if (SndMode == 1) {
    if (VoiceInfo[ch * 3 + 2] != 0) {
      if (VoiceInfo[ch * 3 + 1] != -1) {
        deallocate_voice(VoiceInfo[ch * 3 + 1]);
      }
      pi1 = VoiceInfo;
      VoiceInfo[ch * 3] = 0;
      pi1[ch * 3 + 2] = 0;
      pi1[ch * 3 + 1] = -1;
    }
  }
  return;
}

/* SndVoiceUnreserveAll @ 0x08056f80, 47 bytes
 *
 * Releases every reserved channel. Not called in this build.
 *
 * Calls: SndVoiceUnreserve
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t SndVoiceUnreserveAll(void)

{
  uint32_t entry_ECX;
  int i1;
  
  if ((SndMode == 1) && (i1 = 0, 0 < SndNumVoices)) {
    do {
      SndVoiceUnreserve(i1);
      i1 = i1 + 1;
    } while (i1 < SndNumVoices);
  }
  return entry_ECX;
}

/* SndVoiceIsReserved @ 0x08056fb0, 30 bytes
 *
 * Returns true if channel `ch` is reserved. Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t SndVoiceIsReserved(int arg1)

{
  if (SndMode != 1) {
    return 0xffffffff;
  }
  return VoiceInfo[arg1 * 3 + 2];
}

/* SndVoiceGetVoiceno @ 0x08056fd0, 30 bytes
 *
 * Returns the Allegro voice of channel `ch`. Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t SndVoiceGetVoiceno(int arg1)

{
  if (SndMode != 1) {
    return 0xffffffff;
  }
  return VoiceInfo[arg1 * 3 + 1];
}

/* SndVoiceIsPlaying @ 0x08056ff0, 72 bytes
 *
 * Returns 1 if channel `ch` is playing (its voice has a position), 0 if not,
 * -1 without sound.
 *
 * Parameters:
 *   ch           int
 *
 * C library: voice_get_position
 * Called by: SndIDIsPlaying, SndVoiceIsFree
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t SndVoiceIsPlaying(int ch)

{
  uint32_t u1;
  int i2;
  
  if (SndMode == 1) {
    if (VoiceInfo[ch * 3 + 1] == -1) {
      u1 = 0;
    }
    else {
      i2 = voice_get_position(VoiceInfo[ch * 3 + 1]);
      u1 = (uint32_t)(i2 != -1);
    }
  }
  else {
    u1 = 0xffffffff;
  }
  return u1;
}

/* SndVoiceIsFree @ 0x08057040, 67 bytes
 *
 * Returns 1 if channel `ch` is neither reserved nor playing.
 *
 * Parameters:
 *   ch           int
 *
 * Calls: SndVoiceIsPlaying
 * Called by: SndVoiceGetFree
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t SndVoiceIsFree(int ch)

{
  uint32_t u1;
  uint32_t u2;
  
  if (SndMode == 1) {
    u1 = 0;
    if ((VoiceInfo[ch * 3 + 2] == 0) && (u2 = SndVoiceIsPlaying(ch), u2 == 0)) {
      u1 = 1;
    }
  }
  else {
    u1 = 0xffffffff;
  }
  return u1;
}

/* SndVoiceGetFree @ 0x08057090, 64 bytes
 *
 * Returns the first free channel, or -1.
 *
 * Calls: SndVoiceIsFree
 * Called by: SndIDGetChannelOrFree
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
int SndVoiceGetFree(void)

{
  int i1;
  int i2;
  
  if ((SndMode == 1) && (i2 = 0, 0 < SndNumVoices)) {
    do {
      i1 = SndVoiceIsFree(i2);
      if (i1 != 0) {
        return i2;
      }
      i2 = i2 + 1;
    } while (i2 < SndNumVoices);
  }
  return -1;
}

/* SndVoicePlay @ 0x080570d0, 87 bytes
 *
 * Prepares channel `ch` with sound (group, number) of a sound array and
 * starts it. Returns the channel or -1.
 *
 * Parameters:
 *   ch           int
 *   sounds       int *
 *   grpno        int
 *   itemno       int
 *   vol          int
 *
 * Calls: SndVoicePrepare
 * C library: voice_set_volume, voice_start
 * Called by: SndIDPlay
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t SndVoicePlay(int ch,int *sounds,int grpno,int itemno,int vol)

{
  int i1;
  
  if ((SndMode == 1) && (i1 = SndVoicePrepare(ch,sounds,grpno,itemno), i1 != -1)) {
    voice_set_volume(i1,vol);
    voice_start(i1);
    return i1;
  }
  return 0xffffffff;
}

/* SndVoicePrepare @ 0x08057130, 190 bytes
 *
 * Loads sound (group, number) into channel `ch` without starting it. It
 * first releases the voices of finished, unreserved channels
 * (SndVoiceCleanup), allocates a voice if the channel has none, attaches the
 * sample and applies the default volume, panning and loop setting. Returns
 * the channel or -1. The caller then sets volume, frequency or panning and
 * calls SndVoiceStart.
 *
 * Parameters:
 *   ch           int
 *   sounds       int *
 *   grpno        int
 *   itemno       int
 *
 * Calls: SndVoiceCleanup, ArrayAccessGrpItem
 * C library: allocate_voice, reallocate_voice, voice_set_volume,
 *            voice_set_pan, voice_set_frequency, voice_set_playmode
 * Called by: SndIDPrepare, SndVoicePlay
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
int SndVoicePrepare(int ch,int *sounds,int grpno,int itemno)

{
  int *item;
  int i2;
  
  if (SndMode == 1) {
    SndVoiceCleanup();
    item = (int *)ArrayAccessGrpItem(*sounds,grpno,itemno);
    if (item != (int *)0x0) {
      i2 = VoiceInfo[ch * 3 + 1];
      if (i2 == -1) {
        i2 = allocate_voice((int)tmpspl);
        if (i2 == -1) {
          return -1;
        }
        VoiceInfo[ch * 3 + 1] = i2;
      }
      if (i2 == -1) {
        return -1;
      }
      reallocate_voice(i2,*item);
      voice_set_volume(i2,0x7f);
      voice_set_pan(i2,0x7f);
      voice_set_frequency(i2,*(int *)(*item + 8));
      voice_set_playmode(i2,0);
      return i2;
    }
  }
  return -1;
}

/* SndVoiceStart @ 0x080571f0, 52 bytes
 *
 * Starts the voice of channel `ch`.
 *
 * Parameters:
 *   ch           int
 *
 * C library: voice_start
 * Called by: GameSndPlayIDPos, SCtrlDoPlaySndInfo, SndIDStart
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t SndVoiceStart(int ch)

{
  uint32_t u1;
  
  if ((SndMode == 1) && (ch = VoiceInfo[ch * 3 + 1], ch != -1)) {
    u1 = voice_start(ch);
    return u1;
  }
  return ch;
}

/* SndVoiceStop @ 0x08057230, 87 bytes
 *
 * Stops channel `ch`: clears its owner id, stops the voice and rewinds it.
 *
 * Parameters:
 *   ch           int
 *
 * C library: voice_stop, voice_check, voice_set_position
 * Called by: SndIDStop, SndVoiceStopAll
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndVoiceStop(int ch)

{
  int i1;
  int i2;
  
  if (SndMode == 1) {
    i1 = VoiceInfo[ch * 3 + 1];
    VoiceInfo[ch * 3] = 0;
    if (i1 != -1) {
      voice_stop(i1);
      i2 = voice_check(i1);
      if (i2 != 0) {
        voice_set_position(i1,*(uint32_t *)(i2 + 0x10));
      }
    }
  }
  return;
}

/* SndVoiceStopAll @ 0x08057290, 47 bytes
 *
 * Stops every channel.
 *
 * Calls: SndVoiceStop
 * Called by: SndIDStop
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t SndVoiceStopAll(void)

{
  uint32_t entry_EDX;
  int i1;
  
  if ((SndMode == 1) && (i1 = 0, 0 < SndNumVoices)) {
    do {
      SndVoiceStop(i1);
      i1 = i1 + 1;
    } while (i1 < SndNumVoices);
  }
  return entry_EDX;
}

/* SndVoiceSetVol @ 0x080572c0, 52 bytes
 *
 * Sets the volume (0-255) of channel `ch`.
 *
 * Parameters:
 *   ch           int
 *   vol          int
 *
 * C library: voice_set_volume
 * Called by: GameSndPlayIDPos, SCtrlDoPlaySndInfo
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndVoiceSetVol(int ch,int vol)

{
  if ((SndMode == 1) && (VoiceInfo[ch * 3 + 1] != -1)) {
    voice_set_volume(VoiceInfo[ch * 3 + 1],vol);
    return;
  }
  return;
}

/* SndVoiceGetVol @ 0x08057300, 54 bytes
 *
 * Returns the volume of channel `ch`. Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *
 * C library: voice_get_volume
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
int SndVoiceGetVol(int arg1)

{
  int i1;
  
  if ((SndMode == 1) && (VoiceInfo[arg1 * 3 + 1] != -1)) {
    i1 = voice_get_volume(VoiceInfo[arg1 * 3 + 1]);
    return i1;
  }
  return 0;
}

/* SndVoiceSetFreq @ 0x08057340, 52 bytes
 *
 * Sets the playback frequency of channel `ch` (pitch changes, PlaySnd
 * freqmul).
 *
 * Parameters:
 *   ch           int
 *   freq         int
 *
 * C library: voice_set_frequency
 * Called by: GameSndPlayIDPos, SCtrlDoPlaySndInfo
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndVoiceSetFreq(int ch,int freq)

{
  if ((SndMode == 1) && (VoiceInfo[ch * 3 + 1] != -1)) {
    voice_set_frequency(VoiceInfo[ch * 3 + 1],freq);
    return;
  }
  return;
}

/* SndVoiceGetFreq @ 0x08057380, 54 bytes
 *
 * Returns the playback frequency of channel `ch`.
 *
 * Parameters:
 *   arg1         int
 *
 * C library: voice_get_frequency
 * Called by: GameSndPlayIDPos, SCtrlDoPlaySndInfo
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t SndVoiceGetFreq(int arg1)

{
  uint32_t u1;
  
  if ((SndMode == 1) && (VoiceInfo[arg1 * 3 + 1] != -1)) {
    u1 = voice_get_frequency(VoiceInfo[arg1 * 3 + 1]);
    return u1;
  }
  return 0;
}

/* SndVoiceSetPan @ 0x080573c0, 69 bytes
 *
 * Sets the panning of channel `ch`: -127 (left) .. +127 (right) around
 * centre 127, mirrored when reverse stereo is on.
 *
 * Parameters:
 *   ch           int
 *   pan          int
 *
 * C library: voice_set_pan
 * Called by: GameSndPlayIDPos, PlayerSCtrlApplyElem, SCtrlDoPlaySndInfo
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndVoiceSetPan(int ch,int pan)

{
  if ((SndMode == 1) && (VoiceInfo[ch * 3 + 1] != -1)) {
    voice_set_pan(VoiceInfo[ch * 3 + 1],pan * SndPanMul + 0x7f);
    return;
  }
  return;
}

/* SndVoiceGetPan @ 0x08057410, 70 bytes
 *
 * Returns the panning of channel `ch`. Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *
 * C library: voice_get_pan
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
int SndVoiceGetPan(int arg1)

{
  int i1;
  
  if ((SndMode == 1) && (VoiceInfo[arg1 * 3 + 1] != -1)) {
    i1 = voice_get_pan(VoiceInfo[arg1 * 3 + 1]);
    i1 = (i1 + -0x7f) * SndPanMul;
  }
  else {
    i1 = 0;
  }
  return i1;
}

/* SndVoiceSetLoop @ 0x08057460, 68 bytes
 *
 * Turns looping on or off for channel `ch`.
 *
 * Parameters:
 *   ch           int
 *   loop         int
 *
 * C library: voice_set_playmode
 * Called by: GameSndPlayIDPos, SCtrlDoPlaySndInfo
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndVoiceSetLoop(int ch,int loop)

{
  if ((SndMode == 1) && (VoiceInfo[ch * 3 + 1] != -1)) {
    voice_set_playmode(VoiceInfo[ch * 3 + 1],(uint32_t)(loop != 0));
    return;
  }
  return;
}

/* SndVoiceCleanup @ 0x080574b0, 134 bytes
 *
 * Releases the Allegro voices of channels that are not reserved and have
 * stopped playing, so voices are not exhausted.
 *
 * C library: voice_get_position, deallocate_voice
 * Called by: SndVoicePrepare
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
int * SndVoiceCleanup(void)

{
  int i1;
  int *entry_EAX;
  int i2;
  int i3;
  int i4;
  
  if ((SndMode == 1) && (i3 = 0, 0 < SndNumVoices)) {
    i4 = 0;
    i2 = SndNumVoices;
    do {
      i1 = *(int *)((int)VoiceInfo + i4 + 4);
      entry_EAX = VoiceInfo;
      if (((i1 != -1) && (*(int *)((int)VoiceInfo + i4 + 8) == 0)) &&
         (entry_EAX = (int *)voice_get_position(i1), i2 = SndNumVoices,
         entry_EAX == (int *)0xffffffff)) {
        deallocate_voice(i1);
        entry_EAX = VoiceInfo;
        i2 = SndNumVoices;
        *(uint32_t *)((int)VoiceInfo + i4 + 4) = 0xffffffff;
        *(uint32_t *)((int)entry_EAX + i4) = 0xffffffff;
      }
      i3 = i3 + 1;
      i4 = i4 + 0xc;
    } while (i3 < i2);
  }
  return entry_EAX;
}

/* SndIDPlay @ 0x08057540, 95 bytes
 *
 * Plays sound (group, number) for owner `id`: reuses the channel that owner
 * already has, otherwise takes a free one, and records the owner. Returns
 * the channel or -1.
 *
 * Parameters:
 *   id           int
 *   sounds       int *
 *   grpno        int
 *   itemno       int
 *   vol          uint32_t
 *
 * Calls: SndIDGetChannelOrFree, SndVoicePlay
 * Called by: GameSndPlayID
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
int SndIDPlay(int id,int *sounds,int grpno,int itemno,uint32_t vol)

{
  int i1;
  int i2;
  
  if (SndMode == 1) {
    i1 = SndIDGetChannelOrFree(id);
    i2 = i1;
    if ((i1 != -1) && (i2 = SndVoicePlay(i1,sounds,grpno,itemno,vol), i2 != -1))
    {
      VoiceInfo[i1 * 3] = id;
      i2 = i1;
    }
  }
  else {
    i2 = -1;
  }
  return i2;
}

/* SndIDPrepare @ 0x080575a0, 87 bytes
 *
 * SndIDPlay without starting the sound (SndVoicePrepare); the caller adjusts
 * the voice and starts it.
 *
 * Parameters:
 *   id           int
 *   sounds       int *
 *   grpno        int
 *   itemno       int
 *
 * Calls: SndIDGetChannelOrFree, SndVoicePrepare
 * Called by: GameSndPlayIDPos, SCtrlDoPlaySndInfo
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
int SndIDPrepare(int id,int *sounds,int grpno,int itemno)

{
  int i1;
  int i2;
  
  if (SndMode == 1) {
    i1 = SndIDGetChannelOrFree(id);
    i2 = i1;
    if ((i1 != -1) && (i2 = SndVoicePrepare(i1,sounds,grpno,itemno), i2 != -1)) {
      VoiceInfo[i1 * 3] = id;
      i2 = i1;
    }
  }
  else {
    i2 = -1;
  }
  return i2;
}

/* SndIDStart @ 0x08057600, 52 bytes
 *
 * Starts the channel owned by `id`. Not called in this build.
 *
 * Parameters:
 *   id           int
 *
 * Calls: SndIDGetChannel, SndVoiceStart
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndIDStart(int id)

{
  int i1;
  
  if (SndMode == 1) {
    i1 = SndIDGetChannel(id);
    if (i1 != -1) {
      SndVoiceStart(i1);
      return;
    }
  }
  return;
}

/* SndIDStop @ 0x08057640, 65 bytes
 *
 * Stops the channel owned by `id`, or every channel when `id` is -1. Used by
 * StopSnd and at round changes.
 *
 * Parameters:
 *   id           int
 *
 * Calls: SndVoiceStopAll, SndIDGetChannel, SndVoiceStop
 * Called by: ArcadeWinScreen, GamePlay, GameRoundReset, PlayerGetHit,
 *            PlayerSCtrlApplyElem, PlayerUpdate, SurvivalResultsScreen
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void SndIDStop(int id)

{
  int i1;
  
  if (SndMode == 1) {
    if (id == -1) {
      SndVoiceStopAll();
      return;
    }
    i1 = SndIDGetChannel(id);
    if (i1 != -1) {
      SndVoiceStop(i1);
    }
  }
  return;
}

/* SndIDIsPlaying @ 0x08057690, 59 bytes
 *
 * Returns true if the channel owned by `id` is playing.
 *
 * Parameters:
 *   id           int
 *
 * Calls: SndIDGetChannel, SndVoiceIsPlaying
 * Called by: SCtrlDoPlaySndInfo
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t SndIDIsPlaying(int id)

{
  int i1;
  uint32_t u2;
  
  if (SndMode == 1) {
    i1 = SndIDGetChannel(id);
    if (i1 != -1) {
      u2 = SndVoiceIsPlaying(i1);
      return u2;
    }
    u2 = 0;
  }
  else {
    u2 = 0xffffffff;
  }
  return u2;
}

/* SndIDGetChannel @ 0x080576d0, 65 bytes
 *
 * Returns the channel owned by `id`, or -1.
 *
 * Parameters:
 *   id           int
 *
 * Called by: PlayerSCtrlApplyElem, SndIDGetChannelOrFree, SndIDIsPlaying,
 *            SndIDStart, SndIDStop
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
int SndIDGetChannel(int id)

{
  int i2;
  int *pi2;
  
  if (SndMode == 1) {
    if (id == -1) {
      return -1;
    }
    i2 = 0;
    pi2 = VoiceInfo;
    if (0 < SndNumVoices) {
      do {
        if (*pi2 == id) {
          return i2;
        }
        i2 = i2 + 1;
        pi2 = pi2 + 3;
      } while (i2 < SndNumVoices);
    }
  }
  return -1;
}

/* SndIDGetChannelOrFree @ 0x08057720, 36 bytes
 *
 * Returns the channel owned by `id`, or else a free channel, or -1.
 *
 * Parameters:
 *   id           int
 *
 * Calls: SndIDGetChannel, SndVoiceGetFree
 * Called by: SndIDPlay, SndIDPrepare
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
int SndIDGetChannelOrFree(int id)

{
  int i1;
  
  i1 = SndIDGetChannel(id);
  if (i1 == -1) {
    i1 = SndVoiceGetFree();
    return i1;
  }
  return i1;
}

/* SndReadFile @ 0x08057750, 408 bytes
 *
 * Loads a sound file into a new sound array. A .snd file is read with
 * SndReadFileSNDPtr; a single .wav becomes a one-sound array under key (0,
 * 0). Other extensions give NULL. Reads through a file stream or from memory
 * (SndSetBufReadMode). Returns the array or NULL.
 *
 * Parameters:
 *   filename     char *
 *
 * Calls: MFfopenFile, ffilelength, MFfopenMem, MFfseek, CheckExtension,
 *        SndArrayNew, SndReadFileWAVPtr, MFfclose, SndArrayFree,
 *        SndArrayAdd, SndReadFileSNDPtr
 * C library: fopen, malloc, fclose, fread, free
 * Called by: GameLoadFightData, GameLoadSystem, GameReloadSystemSprSnd,
 *            PlayerDefLoadPtr
 *
 * Elecbyte file: src/lib/snd-lib.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
int * SndReadFile(char *filename)

{
  bool b1;
  FILE *stream;
  size_t size;
  void *ptr;
  size_t s2;
  int *mf;
  int i4;
  int *pi5;
  uint32_t stale_var;
  int *sounds;
  
  if (BufferedReadMode == 0) {
    mf = (int *)MFfopenFile(filename,"rb");
    if (mf == (int *)0x0) {
      return (int *)0x0;
    }
  }
  else {
    stream = fopen(filename,"rb");
    if (stream == (FILE *)0x0) {
      return (int *)0x0;
    }
    size = ffilelength(stream);
    ptr = malloc(size);
    if (ptr == (void *)0x0) {
      fclose(stream);
      return (int *)0x0;
    }
    s2 = fread(ptr,size,1,stream);
    if (s2 == 0xffffffff) {
      fclose(stream);
      return (int *)0x0;
    }
    fclose(stream);
    mf = MFfopenMem((int)ptr,size);
    if (mf == (int *)0x0) {
      free(ptr);
      return (int *)0x0;
    }
    mf[6] = 1;
  }
  MFfseek(mf,0,0);
  i4 = CheckExtension(filename);
  if (i4 == 3) {
    sounds = SndArrayNew(1);
    if (sounds != (int *)0x0) {
      pi5 = SndReadFileWAVPtr(mf);
      if (pi5 == (int *)0x0) {
        MFfclose(mf);
        SndArrayFree(sounds);
        return (int *)0x0;
      }
      b1 = SndArrayAdd(sounds,pi5,0,0);
      if (ZEXT8(b1) == 0) {
        MFfclose(mf);
        SndArrayFree(sounds);
        return (int *)0x0;
      }
      goto L_080578d2;
    }
  }
  else {
    if (i4 != 4) {
      return (int *)0x0;
    }
    sounds = SndReadFileSNDPtr(mf);
    if (sounds != (int *)0x0) {
L_080578d2:
      MFfclose(mf);
      return sounds;
    }
  }
  MFfclose(mf);
  return (int *)0x0;
}

/* SndMidiReadFile @ 0x080578f0, 5 bytes
 *
 * Loads a MIDI file (Allegro load_midi).
 *
 * Parameters:
 *   arg1         uint8_t *
 *
 * C library: load_midi
 * Called by: BGMLoad
 *
 * Elecbyte file: src/lib/snd-lib.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to destroy_
 *       midi,lock_midi,malloc,pack_fclose,pack_fopen,pack_fread,pack_mgetl,pack_
 *       mgetw
 */
uint32_t * SndMidiReadFile(uint8_t *arg1)

{
  uint32_t *pu1;
  
  pu1 = load_midi(arg1);
  return pu1;
}

/* SndReadFileWAVPtr @ 0x08057900, 735 bytes
 *
 * Reads a RIFF WAVE sound from an MF stream into an Allegro SAMPLE. It walks
 * the chunks until "fmt " and "data", accepting PCM with 1 or 2 channels at
 * 8 or 16 bits. Returns the sample or NULL.
 *
 * Parameters:
 *   mf           int *
 *
 * Calls: MFftell, MFfread, MFfeof, MFigetl, MFigetw, MFfseek, MFgetc
 * C library: flag, create_sample, lock_sample
 * Called by: SndReadFile, SndReadFileSNDPtr
 * Messages:
 *   "fmt "
 *
 * Elecbyte file: src/lib/snd-lib.c
 * Note: 1 data addresses refer to the data image (data/mugen_data.S).
 * Note: 3 dead flag initialisations of inlined repz cmpsb loops set to constants
 * Note: 1 exact-text site patches (see SITE_PATCHES in
 *       tools/build_source_tree.py)
 * Note: Locals live in `frame`, laid out as on the original stack (0x60 bytes,
 *       10 variables), because their address is taken.
 */
int * SndReadFileWAVPtr(int *mf)

{
  uint32_t u1;
  uint32_t ch;
  size_t s3;
  int pos;
  uint8_t *pb5;
  int i2;
  uint8_t *pb7;
  uint8_t u8;
  bool b9;
  uint8_t u10;
  bool b11;
  unsigned char frame[0x60] __attribute__((aligned(16)));
#define buf_5c (*(uint8_t (*)[8])(frame + 0x4))
#define stk_54 (*(int *)(frame + 0xc))
#define pos2 (*(int *)(frame + 0x10))
#define stk_4c (*(int **)(frame + 0x14))
#define stk_48 (*(uint32_t *)(frame + 0x18))
#define stk_44 (*(uint32_t *)(frame + 0x1c))
#define stk_40 (*(uint32_t *)(frame + 0x20))
#define stk_3c (*(uint8_t (*)[4])(frame + 0x24))
#define stk_38 (*(int *)(frame + 0x28))
#define stk_34 (*(uint8_t (*)[36])(frame + 0x2c))
  
  u8 = 0;  /* dead flag (repz cmpsb, count 4) */
  u10 = 0;  /* dead flag (repz cmpsb, count 4) */
  stk_40 = 0x5622;
  stk_44 = 8;
  stk_48 = 1;
  stk_4c = (int *)0x0;
  pos2 = MFftell(mf);
  MFfread(stk_3c,0xc,1,mf);
  pos = 4;
  pb5 = stk_3c;
  pb7 = &str_riff;
  do {
    if (pos == 0) break;
    pos = pos + -1;
    u8 = *pb5 < *pb7;
    u10 = *pb5 == *pb7;
    pb5 = pb5 + 1;
    pb7 = pb7 + 1;
  } while ((bool)u10);
  b9 = (!(bool)u8 && !(bool)u10) < (uint8_t)u8;
  if ((!(bool)u8 && !(bool)u10) == (bool)u8) {
    pos = 4;
    b11 = true;
    pb5 = stk_34;
    pb7 = &str_wave;
    do {
      if (pos == 0) break;
      pos = pos + -1;
      b9 = *pb5 < *pb7;
      b11 = *pb5 == *pb7;
      pb5 = pb5 + 1;
      pb7 = pb7 + 1;
    } while (b11);
    if ((!b9 && !b11) == b9) {
      stk_54 = stk_38 + 8;
      while (pos = MFfeof(mf), pos == 0) {
        s3 = MFfread(stk_3c,4,1,mf);
        if (s3 != 1) break;
        u8 = buf_5c < (uint8_t *)0xc;
        u10 = 0;  /* dead flag (repz cmpsb, count 4) */
        u1 = MFigetl(mf);
        pos = 4;
        pb5 = stk_3c;
        pb7 = &str_fmt;
        do {
          if (pos == 0) break;
          pos = pos + -1;
          u8 = *pb5 < *pb7;
          u10 = *pb5 == *pb7;
          pb5 = pb5 + 1;
          pb7 = pb7 + 1;
        } while ((bool)u10);
        b9 = (!(bool)u8 && !(bool)u10) < (uint8_t)u8;
        b11 = (!(bool)u8 && !(bool)u10) == (bool)u8;
        if (b11) {
          ch = MFigetw(mf);
          if ((ch != 1) || (stk_48 = MFigetw(mf), 1 < stk_48 - 1)) break;
          u1 = u1 - 0x10;
          stk_40 = MFigetl(mf);
          MFigetl(mf);
          MFigetw(mf);
          stk_44 = MFigetw(mf);
          if ((stk_44 != 8) && (stk_44 != 0x10)) break;
        }
        else {
          pos = 4;
          pb5 = stk_3c;
          pb7 = (uint8_t *)(int)&str_data;
          do {
            if (pos == 0) break;
            pos = pos + -1;
            b9 = *pb5 < *pb7;
            b11 = *pb5 == *pb7;
            pb5 = pb5 + 1;
            pb7 = pb7 + 1;
          } while (b11);
          if ((!b9 && !b11) == b9) {
            s3 = (int)u1 / (int)stk_48;
            if (stk_44 == 0x10) {
              s3 = (int)s3 / 2;
            }
            stk_4c = create_sample(stk_44,(stk_48 != 2) - 1,stk_40,s3);
            if (stk_4c == (int *)0x0) goto L_08057b61;
            if (stk_44 == 8) {
              MFfread((void *)stk_4c[8],u1,1,mf);
            }
            else {
              i2 = 0;
              pos = stk_48 * s3;
              if (0 < pos) {
                do {
                  u1 = MFigetw(mf);
                  *(uint16_t *)(stk_4c[8] + i2 * 2) = (uint16_t)u1 ^ 0x8000;
                  i2 = i2 + 1;
                } while (i2 < pos);
              }
            }
          }
          else if ((((int)u1 < 1) || (pos = MFfseek(mf,u1,1), pos != 0)) ||
                  (pos = MFftell(mf), pos2 < pos - stk_54)) break;
          u1 = 0;
        }
L_08057b61:
        while ((0 < (int)u1 && (ch = MFgetc(mf), ch != 0xffffffff))) {
          u1 = u1 - 1;
        }
      }
    }
  }
  if (stk_4c != (int *)0x0) {
    lock_sample(stk_4c);
  }
  MFfseek(mf,pos2,0);
  return stk_4c;
}
#undef buf_5c
#undef stk_54
#undef pos2
#undef stk_4c
#undef stk_48
#undef stk_44
#undef stk_40
#undef stk_3c
#undef stk_38
#undef stk_34

/* SndReadFileSNDPtr @ 0x08057be0, 278 bytes
 *
 * Reads an Elecbyte .snd file: checks the "ElecbyteSnd" signature, then
 * follows the subfile list. Each subfile has its next offset, length and
 * (group, number) key followed by WAV data (SndReadFileWAVPtr). Returns a
 * new sound array, or NULL.
 *
 * Parameters:
 *   mf           int *
 *
 * Calls: MFftell, MFfread, SndArrayNew, MFfseek, SndReadFileWAVPtr,
 *        SndArrayAdd, SndArrayFree
 * C library: flag
 * Called by: PlayerDefLoadZip, SndReadFile
 *
 * Elecbyte file: src/lib/snd-lib.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: 1 dead flag initialisations of inlined repz cmpsb loops set to constants
 * Note: Locals live in `frame`, laid out as on the original stack (0x230 bytes,
 *       6 variables), because their address is taken.
 */
int * SndReadFileSNDPtr(int *mf)

{
  int pos;
  size_t s2;
  int *pi3;
  uint32_t stale_var;
  int i2;
  uint8_t *pb5;
  uint8_t *pb6;
  bool b7;
  bool b8;
  int *sounds;
  unsigned char frame[0x230] __attribute__((aligned(16)));
#define stk_22c (*(int (*)[2])(frame + 0x4))
#define stk_224 (*(uint32_t *)(frame + 0xc))
#define stk_220 (*(uint32_t *)(frame + 0x10))
#define stk_21c (*(uint8_t (*)[16])(frame + 0x14))
#define stk_20c (*(size_t *)(frame + 0x24))
#define stk_208 (*(int *)(frame + 0x28))
  
  pos = MFftell(mf);
  s2 = MFfread(stk_21c,0x200,1,mf);
  b7 = 0;  /* dead flag (repz cmpsb, count 0xc) */
  if (s2 == 1) {
    i2 = 0xc;
    b8 = true;
    pb5 = stk_21c;
    pb6 = (uint8_t *)"ElecbyteSnd";
    do {
      if (i2 == 0) break;
      i2 = i2 + -1;
      b7 = *pb5 < *pb6;
      b8 = *pb5 == *pb6;
      pb5 = pb5 + 1;
      pb6 = pb6 + 1;
    } while (b8);
    if ((!b7 && !b8) == b7) {
      sounds = SndArrayNew(stk_20c);
      if (sounds == (int *)0x0) {
        return (int *)0x0;
      }
      if (0 < (int)stk_20c) {
        i2 = 0;
        do {
          MFfseek(mf,stk_208 + pos,0);
          s2 = MFfread(stk_22c,0x10,1,mf);
          if (((s2 != 1) || (pi3 = SndReadFileWAVPtr(mf), pi3 == (int *)0x0)) ||
             (b7 = SndArrayAdd(sounds,pi3,stk_224,stk_220),
             ZEXT8(b7) == 0)) goto L_08057c64;
          i2 = i2 + 1;
          stk_208 = stk_22c[0];
        } while (i2 < (int)stk_20c);
      }
      MFfseek(mf,pos,0);
      return sounds;
    }
    sounds = (int *)0x0;
  }
  else {
    sounds = (int *)0x0;
  }
L_08057c64:
  SndArrayFree(sounds);
  return (int *)0x0;
}
#undef stk_22c
#undef stk_224
#undef stk_220
#undef stk_21c
#undef stk_20c
#undef stk_208

/* SndSetVol @ 0x08057d00, 81 bytes
 *
 * Sets the digital and MIDI master volumes, clamped to 0-255 (Allegro
 * set_volume).
 *
 * Parameters:
 *   wav_vol      uint32_t
 *   midi_vol     uint32_t
 *
 * C library: set_volume
 * Called by: GameSetVol
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t SndSetVol(uint32_t wav_vol,uint32_t midi_vol)

{
  uint32_t u1;
  
  VoiceVol = wav_vol & 0xffffffffU - ((int)wav_vol >> 0x1f);
  if (0xff < VoiceVol) {
    VoiceVol = 0xff;
  }
  MidiVol = midi_vol & 0xffffffffU - ((int)midi_vol >> 0x1f);
  if (0xff < MidiVol) {
    MidiVol = 0xff;
  }
  u1 = set_volume(VoiceVol,MidiVol);
  return u1;
}

/* SndGetVoiceVol @ 0x08057d60, 6 bytes
 *
 * Returns the digital master volume. Not called in this build.
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
int SndGetVoiceVol(void)

{
  return VoiceVol;
}

/* SndGetMidiVol @ 0x08057d70, 6 bytes
 *
 * Returns the MIDI master volume. Not called in this build.
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
int SndGetMidiVol(void)

{
  return MidiVol;
}

/* SndCorrectVolOff @ 0x08057d80, 40 bytes
 *
 * Converts a volume value through the FPU (int -> long double -> int); the
 * value is unchanged in this build.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: BGMLoad, BGMResume, BGMSysResume, GameSndPlayID,
 *            GameSndPlayIDPos, SCtrlDoPlaySndInfo, ScrPositionToPan
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
int SndCorrectVolOff(int arg1)

{
  return (int)X87_FIST32((float80)arg1);
}

/* SndParseWavDevice @ 0x08057db0, 143 bytes
 *
 * Parses the configured digital sound device name: "none" 0, "auto" -1,
 * "oss", "esd", "alsa" and the other Allegro Linux drivers as their driver
 * ids. Returns the id.
 *
 * Parameters:
 *   arg1         char *
 *
 * C library: _alemu_stricmp
 * Called by: GameConfigRead
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
int SndParseWavDevice(char *arg1)

{
  int i1;
  int i2;
  
  i1 = _alemu_stricmp(arg1,"none");
  i2 = 0;
  if (i1 != 0) {
    i1 = _alemu_stricmp(arg1,"auto");
    i2 = -1;
    if (i1 != 0) {
      i1 = _alemu_stricmp(arg1,"oss");
      i2 = 0x4f535344;
      if (i1 != 0) {
        i1 = _alemu_stricmp(arg1,"esd");
        i2 = 0x45534444;
        if (i1 != 0) {
          i1 = _alemu_stricmp(arg1,"alsa");
          i2 = ((i1 == 0) - 1 & 0xfffffc17) + 999;
        }
      }
    }
  }
  return i2;
}

/* SndWavDeviceString @ 0x08057e40, 73 bytes
 *
 * Returns the Allegro configuration name ("oss", "esd", "alsa", "0"...) of a
 * digital driver id, for the "[sound]" configuration text built by SndInit.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: SndInit
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t * SndWavDeviceString(int arg1)

{
  if (arg1 == 999) {
    return (uint32_t *)&str_alsa;
  }
  if (arg1 < 1000) {
    if (arg1 == 0) {
      return (uint32_t *)"0";
    }
  }
  else {
    if (arg1 == 0x45534444) {
      return (uint32_t *)&str_esd;
    }
    if (arg1 == 0x4f535344) {
      return (uint32_t *)&str_oss;
    }
  }
  return (uint32_t *)0x0;
}

/* SndParseMidiDevice @ 0x08057e90, 143 bytes
 *
 * Parses the configured MIDI device name into an Allegro MIDI driver id.
 *
 * Parameters:
 *   arg1         char *
 *
 * C library: _alemu_stricmp
 * Called by: GameConfigRead
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
int SndParseMidiDevice(char *arg1)

{
  int i1;
  int i2;
  
  i1 = _alemu_stricmp(arg1,"none");
  i2 = 0;
  if (i1 != 0) {
    i1 = _alemu_stricmp(arg1,"auto");
    i2 = -1;
    if (i1 != 0) {
      i1 = _alemu_stricmp(arg1,"oss");
      i2 = 0x4f53534d;
      if (i1 != 0) {
        i1 = _alemu_stricmp(arg1,"alsa");
        i2 = 1000;
        if (i1 != 0) {
          i1 = _alemu_stricmp(arg1,"digmid");
          i2 = ((i1 == 0) - 1 & 0xbbb6b8b5) + 0x44494749;
        }
      }
    }
  }
  return i2;
}

/* SndMidiDeviceString @ 0x08057f20, 89 bytes
 *
 * Returns the Allegro configuration name of a MIDI driver id.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: SndInit
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t * SndMidiDeviceString(int arg1)

{
  if (arg1 == 1000) {
    return (uint32_t *)&str_alsa_72b7;
  }
  if (arg1 < 0x3e9) {
    if (arg1 == -1) {
      return (uint32_t *)&str_auto;
    }
    if (arg1 == 0) {
      return (uint32_t *)"0";
    }
  }
  else {
    if (arg1 == 0x44494749) {
      return (uint32_t *)&str_digi;
    }
    if (arg1 == 0x4f53534d) {
      return (uint32_t *)&str_oss_72b3;
    }
  }
  return (uint32_t *)0x0;
}

/* MP3Init @ 0x08057f80, 45 bytes
 *
 * Installs the MP3 player (libamp install_amp). Returns true on success.
 *
 * C library: install_amp
 * Called by: GameInit
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
bool MP3Init(void)

{
  int i1;
  
  MP3Paused = 0;
  i1 = install_amp();
  if (i1 != 0) {
    MP3Installed = 1;
  }
  return i1 != 0;
}

/* MP3DeInit @ 0x08057fb0, 21 bytes
 *
 * Unloads any MP3 and shuts the player down.
 *
 * Called by: GameDeInit
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void MP3DeInit(void)

{
  if (MP3Installed != 0) {
    MP3Installed = 0;
  }
  return;
}

/* MP3LoadAndPlay @ 0x08057fd0, 27 bytes
 *
 * Loads an MP3 file and starts playing it (libamp load_amp, looping per the
 * flag).
 *
 * Parameters:
 *   arg1         char *
 *   arg2         uint32_t
 *
 * C library: load_amp
 * Called by: BGMLoad
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t MP3LoadAndPlay(char *arg1,uint32_t arg2)

{
  uint32_t u1;
  
  if (MP3Installed != 0) {
    u1 = load_amp(arg1,arg2);
    return u1;
  }
  return 0;
}

/* MP3Unload @ 0x08057ff0, 31 bytes
 *
 * Stops and unloads the current MP3.
 *
 * C library: unload_amp
 * Called by: BGMFree
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void MP3Unload(void)

{
  if (MP3Installed != 0) {
    unload_amp();
  }
  MP3Paused = 0;
  return;
}

/* MP3Poll @ 0x08058010, 39 bytes
 *
 * Lets libamp decode the next part of the MP3 (must be called regularly).
 *
 * C library: poll_amp
 * Called by: BGMPollIgnoreDefocus
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void MP3Poll(void)

{
  if ((MP3Installed != 0) && (MP3Paused == 0)) {
    poll_amp();
    return;
  }
  return;
}

/* MP3SetVol @ 0x08058040, 24 bytes
 *
 * Sets the MP3 volume.
 *
 * Parameters:
 *   arg1         int
 *
 * C library: set_volume_mp3
 * Called by: BGMLoad, BGMPause, BGMPollIgnoreDefocus, BGMResume,
 *            BGMSetVolume, BGMSysPause, BGMSysResume
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void MP3SetVol(int arg1)

{
  if (MP3Installed != 0) {
    set_volume_mp3(arg1);
    return;
  }
  return;
}

/* MP3GetVol @ 0x08058060, 27 bytes
 *
 * Returns the MP3 volume.
 *
 * C library: get_volume_mp3
 * Called by: BGMGetVolume, BGMPollIgnoreDefocus
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t MP3GetVol(void)

{
  uint32_t u1;
  
  if (MP3Installed != 0) {
    u1 = get_volume_mp3();
    return u1;
  }
  return 0;
}

/* MP3Pause @ 0x08058080, 11 bytes
 *
 * Pauses the MP3.
 *
 * Called by: BGMPause, BGMSysPause
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void MP3Pause(void)

{
  MP3Paused = 1;
  return;
}

/* MP3Resume @ 0x08058090, 11 bytes
 *
 * Resumes the MP3.
 *
 * Called by: BGMResume, BGMSysResume
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void MP3Resume(void)

{
  MP3Paused = 0;
  return;
}

/* MODInit @ 0x080580a0, 43 bytes
 *
 * Installs the tracker music player (jgmod install_mod) with `voices`
 * voices. Returns true on success.
 *
 * Parameters:
 *   arg1         int
 *
 * C library: install_mod
 * Called by: BGMLoad
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
bool MODInit(int arg1)

{
  int i1;
  
  i1 = install_mod(arg1);
  if (0 < i1) {
    MODInstalled = 1;
  }
  return 0 < i1;
}

/* MODDeInit @ 0x080580d0, 31 bytes
 *
 * Removes the tracker music player.
 *
 * C library: remove_mod
 * Called by: BGMFree
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void MODDeInit(void)

{
  if (MODInstalled != 0) {
    remove_mod();
    MODInstalled = 0;
  }
  return;
}

/* MODLoad @ 0x080580f0, 86 bytes
 *
 * Loads a MOD/S3M/XM file (jgmod load_mod) into a holder record. Returns the
 * record or NULL.
 *
 * Parameters:
 *   arg1         uint8_t *
 *
 * C library: calloc, load_mod, free
 * Called by: BGMLoad
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t MODLoad(uint8_t *arg1)

{
  uint32_t *ptr;
  uint8_t *pu1;
  
  if ((MODInstalled != 0) && (ptr = calloc(1,4), ptr != (uint32_t *)0x0)) {
    pu1 = load_mod(arg1);
    *ptr = pu1;
    if (pu1 != (uint8_t *)0x0) {
      return ptr;
    }
    free(ptr);
  }
  return 0;
}

/* MODUnload @ 0x08058150, 54 bytes
 *
 * Frees a loaded tracker module.
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * C library: destroy_mod, free
 * Called by: BGMFree
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t MODUnload(uint32_t *arg1)

{
  uint32_t stale_EAX;
  uint32_t entry_EDX;
  
  if ((MODInstalled != 0) && (arg1 != (uint32_t *)0x0)) {
    if ((void *)*arg1 != (void *)0x0) {
      destroy_mod((void *)*arg1);
    }
    free(arg1);
    return stale_EAX;
  }
  return entry_EDX;
}

/* MODPlay @ 0x08058190, 36 bytes
 *
 * Starts playing a tracker module (looped when `loop` is set).
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *
 * C library: play_mod
 * Called by: BGMStart
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void MODPlay(int *arg1,int arg2)

{
  if (MODInstalled != 0) {
    play_mod(*arg1,arg2);
    return;
  }
  return;
}

/* MODStop @ 0x080581c0, 24 bytes
 *
 * Stops tracker music.
 *
 * C library: stop_mod
 * Called by: BGMFree
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void MODStop(void)

{
  if (MODInstalled != 0) {
    stop_mod();
    return;
  }
  return;
}

/* MODPause @ 0x080581e0, 25 bytes
 *
 * Pauses tracker music.
 *
 * C library: pause_mod
 * Called by: BGMPause, BGMSysPause
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void MODPause(void)

{
  if (MODInstalled != 0) {
    pause_mod();
    return;
  }
  return;
}

/* MODResume @ 0x08058200, 25 bytes
 *
 * Resumes tracker music.
 *
 * C library: resume_mod
 * Called by: BGMResume, BGMSysResume
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void MODResume(void)

{
  if (MODInstalled != 0) {
    resume_mod();
    return;
  }
  return;
}

/* MODSetVol @ 0x08058220, 24 bytes
 *
 * Sets the tracker music volume.
 *
 * Parameters:
 *   arg1         int
 *
 * C library: set_mod_volume
 * Called by: BGMLoad, BGMSetVolume
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void MODSetVol(int arg1)

{
  if (MODInstalled != 0) {
    set_mod_volume(arg1);
    return;
  }
  return;
}

/* MODGetVol @ 0x08058240, 27 bytes
 *
 * Returns the tracker music volume.
 *
 * C library: get_mod_volume
 * Called by: BGMGetVolume
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t MODGetVol(void)

{
  uint32_t u1;
  
  if (MODInstalled != 0) {
    u1 = get_mod_volume();
    return u1;
  }
  return 0;
}

/* CDAInit @ 0x08058260, 47 bytes
 *
 * Opens the CD drive (libcda cd_init) once. Returns nonzero on success.
 *
 * Parameters:
 *   arg1         char *
 *
 * C library: cd_init
 * Called by: BGMLoad
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t CDAInit(char *arg1)

{
  int i1;
  
  if (CDAInstalled == 0) {
    i1 = cd_init(arg1);
    CDAInstalled = (int)(i1 == 0);
  }
  return CDAInstalled;
}

/* CDADeInit @ 0x08058290, 38 bytes
 *
 * Stops CD playback and closes the drive.
 *
 * Calls: CDAIsPlaying, CDAStop
 * C library: cd_exit
 * Called by: GameDeInit
 *
 * Elecbyte file: src/lib/snd-lib.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
void CDADeInit(void)

{
  bool b1;
  uint32_t stale_var;
  
  if (CDAInstalled != 0) {
    b1 = CDAIsPlaying();
    if (ZEXT8(b1) != 0) {
      CDAStop();
    }
    cd_exit();
    return;
  }
  return;
}

/* CDAPlay @ 0x080582c0, 118 bytes
 *
 * Plays CD track `track` (once, or looped when `loop` is set) if nothing is
 * playing and the track is audio. Remembers the track for CDAPoll.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         int
 *
 * Calls: CDAIsPlaying
 * C library: cd_is_audio, cd_play, cd_play_loop
 * Called by: BGMStart
 *
 * Elecbyte file: src/lib/snd-lib.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
uint32_t CDAPlay(uint32_t arg1,int arg2)

{
  bool b1;
  uint32_t stale_var;
  uint32_t u2;
  int i3;
  
  if (((CDAInstalled != 0) && (b1 = CDAIsPlaying(), ZEXT8(b1) == 0)) &&
     (u2 = cd_is_audio((char)arg1), u2 == 1)) {
    if (arg2 == 0) {
      i3 = cd_play(arg1);
    }
    else {
      i3 = cd_play_loop(arg1);
    }
    if (i3 == 0) {
      CDALoop = arg2;
      CDATrack = arg1;
      CDAPauseflag = 0;
      return 1;
    }
  }
  return 0;
}

/* CDAStop @ 0x08058340, 51 bytes
 *
 * Stops CD playback.
 *
 * C library: cd_stop
 * Called by: BGMFree, CDADeInit
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
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
 *
 * Pauses CD playback.
 *
 * C library: cd_is_paused, cd_pause
 * Called by: BGMPause, BGMSysPause
 *
 * Elecbyte file: src/lib/snd-lib.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
void CDAPause(void)

{
  bool b1;
  uint32_t stale_var;
  
  if ((CDAInstalled != 0) && (CDATrack != 0)) {
    b1 = cd_is_paused();
    if (ZEXT8(b1) == 0) {
      CDAPauseflag = 1;
      cd_pause();
      return;
    }
  }
  return;
}

/* CDAResume @ 0x080583c0, 50 bytes
 *
 * Resumes CD playback.
 *
 * C library: cd_is_paused, cd_resume
 * Called by: BGMResume, BGMSysResume
 *
 * Elecbyte file: src/lib/snd-lib.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
void CDAResume(void)

{
  bool b1;
  uint32_t stale_var;
  
  if ((CDAInstalled != 0) && (CDATrack != 0)) {
    b1 = cd_is_paused();
    if (ZEXT8(b1) != 0) {
      cd_resume();
      CDAPauseflag = 0;
    }
  }
  return;
}

/* CDAPoll @ 0x08058400, 95 bytes
 *
 * Keeps CD music going: a looped track that has ended is restarted; a
 * non-looped one is forgotten.
 *
 * Calls: CDAIsPlaying
 * C library: cd_play_now
 * Called by: BGMPollIgnoreDefocus
 *
 * Elecbyte file: src/lib/snd-lib.c
 * Note: 2 byte results widened with ZEXT8 (upper bytes are zero).
 */
void CDAPoll(void)

{
  bool b1;
  uint32_t stale_var;
  uint32_t stale_var_00;
  
  if (((CDAInstalled != 0) && (CDATrack != 0)) && (CDAPauseflag == 0)) {
    if (CDALoop == 0) {
      b1 = CDAIsPlaying();
      if (ZEXT8(b1) == 0) {
        CDATrack = 0;
      }
    }
    else {
      b1 = CDAIsPlaying();
      if (ZEXT8(b1) == 0) {
        cd_play_now(CDATrack);
      }
    }
  }
  return;
}

/* CDAIsPlaying @ 0x08058460, 38 bytes
 *
 * Returns true while the CD is playing.
 *
 * C library: cd_is_playing
 * Called by: CDADeInit, CDAPlay, CDAPoll
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
bool CDAIsPlaying(void)

{
  bool b1;
  
  if ((CDAInstalled != 0) && (CDATrack != 0)) {
    b1 = cd_is_playing();
    return b1;
  }
  return false;
}

/* CDAIsPaused @ 0x08058490, 38 bytes
 *
 * Returns true while the CD is paused. Not called in this build.
 *
 * C library: cd_is_paused
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
bool CDAIsPaused(void)

{
  bool b1;
  
  if ((CDAInstalled != 0) && (CDATrack != 0)) {
    b1 = cd_is_paused();
    return b1;
  }
  return false;
}

/* CDATrackIsAudio @ 0x080584c0, 27 bytes
 *
 * Returns true if CD track `track` is an audio track.
 *
 * Parameters:
 *   arg1         uint8_t
 *
 * C library: cd_is_audio
 * Called by: BGMStart
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint32_t CDATrackIsAudio(uint8_t arg1)

{
  uint32_t u1;
  
  if (CDAInstalled != 0) {
    u1 = cd_is_audio(arg1);
    return u1;
  }
  return 0xffffffff;
}

/* CDACurrentTrack @ 0x080584e0, 38 bytes
 *
 * Returns the current CD track. Not called in this build.
 *
 * C library: cd_current_track
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
uint8_t CDACurrentTrack(void)

{
  uint8_t u1;
  
  if ((CDAInstalled != 0) && (CDATrack != 0)) {
    u1 = cd_current_track();
    return u1;
  }
  return 0;
}

/* CDAGetTrackRange @ 0x08058510, 54 bytes
 *
 * Gets the first and last track numbers of the CD.
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         uint32_t *
 *
 * C library: cd_get_tracks
 * Called by: BGMStart
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
bool CDAGetTrackRange(uint32_t *arg1,uint32_t *arg2)

{
  int i1;
  bool b2;
  
  if (CDAInstalled == 0) {
    b2 = false;
  }
  else {
    i1 = cd_get_tracks(arg1,arg2);
    b2 = i1 == 0;
  }
  return b2;
}

/* CDASetVol @ 0x08058550, 53 bytes
 *
 * Sets the CD audio volume (0-255).
 *
 * Parameters:
 *   arg1         uint32_t
 *
 * C library: cd_set_volume
 * Called by: BGMLoad, BGMSetVolume
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void CDASetVol(uint32_t arg1)

{
  uint32_t l;
  
  if (CDAInstalled != 0) {
    l = arg1 & 0xffffffffU - ((int)arg1 >> 0x1f);
    if (0xfe < (int)l) {
      l = 0xff;
    }
    cd_set_volume(l,l);
  }
  return;
}

/* CDAGetVol @ 0x08058590, 54 bytes
 *
 * Returns the CD audio volume.
 *
 * C library: cd_get_volume
 * Called by: BGMGetVolume
 *
 * Elecbyte file: src/lib/snd-lib.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x10 bytes, 2
 *       variables), because their address is taken.
 */
int CDAGetVol(void)

{
  int i1;
  unsigned char frame[0x10] __attribute__((aligned(16)));
#define stk_8 (*(uint32_t *)(frame + 0x8))
#define stk_4 (*(uint32_t *)(frame + 0xc))
  
  if (CDAInstalled == 0) {
    i1 = 0;
  }
  else {
    cd_get_volume(&stk_8,&stk_4);
    i1 = (int)(stk_4 + stk_8) >> 1;
  }
  return i1;
}
#undef stk_8
#undef stk_4

/* CDAEject @ 0x080585d0, 25 bytes
 *
 * Ejects the CD. Not called in this build.
 *
 * C library: cd_eject
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void CDAEject(void)

{
  if (CDAInstalled != 0) {
    cd_eject();
    return;
  }
  return;
}

/* CDAClose @ 0x080585f0, 25 bytes
 *
 * Closes the CD tray. Not called in this build.
 *
 * C library: cd_close
 *
 * Elecbyte file: src/lib/snd-lib.c
 */
void CDAClose(void)

{
  if (CDAInstalled != 0) {
    cd_close();
    return;
  }
  return;
}

