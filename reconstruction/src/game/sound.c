/*
 * sound.c -- game sound helpers
 * Playing sounds for players and the fight screen with volume, panning from
 * screen position, and per-player channels.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/sound.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* GameSndPlay @ 0x080b9fd0, 34 bytes
 *
 * Plays sound (group, number) of a sound array with no owner (GameSndPlayID
 * with id -1).
 *
 * Parameters:
 *   sounds       int *
 *   group        int
 *   number       int
 *   arg4         int
 *
 * Calls: GameSndPlayID
 * Called by: CharacterSelectScreen, GamePowerBarUpdate, GameRoundUpdate,
 *            ModeSelect, OptionsScreen
 *
 * Elecbyte file: src/mugen/sound.c
 * Note: Returns nothing (the original left only stale register values).
 */
void GameSndPlay(int *sounds,int group,int number,int arg4)

{
  uint32_t stale_EAX;
  
  GameSndPlayID(-1,sounds,group,number,arg4);
  return;
}

/* GameSndPlayID @ 0x080ba000, 142 bytes
 *
 * Plays sound (group, number) for owner `id` at the configured volume plus
 * `vol_offset` (clamped to 0-255). Does nothing when sound is off or the
 * sound number is -1.
 *
 * Parameters:
 *   arg1         int
 *   sounds       int *
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *
 * Globals read: sound_linux_wavvolume
 * Calls: SndCorrectVolOff, SndIDPlay
 * Called by: CharacterSelectScreen, GameSndPlay
 *
 * Elecbyte file: src/mugen/sound.c
 */
void GameSndPlayID(int arg1,int *sounds,int arg3,int arg4,int arg5)

{
  int i1;
  uint32_t u2;
  
  i1 = SndCorrectVolOff(arg5);
  u2 = i1 + g[G_SOUND_LINUX_WAVVOLUME] & 0xffffffffU - (i1 + g[G_SOUND_LINUX_WAVVOLUME] >> 0x1f);
  if (0xff < (int)u2) {
    u2 = 0xff;
  }
  if ((((g[0x6ef3] != 0) && (sounds != (int *)0x0)) && (g[0x7308] == 0)) && (arg3 != -1)) {
    SndIDPlay(arg1,sounds,arg3,arg4,u2);
    return;
  }
  return;
}

/* GameSndPlayIDPos @ 0x080ba090, 237 bytes
 *
 * Plays a sound for owner `id` positioned on screen. Panning comes from the
 * screen x position (ScrPositionToPan) when stereo effects are enabled, and
 * the volume is adjusted for the pan (PanVolumeAdjust). The frequency
 * multiplier, volume offset and loop flag are applied before the voice
 * starts. Used for hit sounds and PlaySnd.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   sounds       int *
 *   arg4         int
 *   arg5         int
 *   arg6         int
 *
 * Globals read: sound_linux_stereoeffects, sound_linux_wavvolume
 * Calls: SndIDPrepare, ScrPositionToPan, SndCorrectVolOff,
 *        PanVolumeAdjust, SndVoiceGetFreq, SndVoiceSetVol,
 *        SndVoiceSetFreq, SndVoiceSetPan, SndVoiceSetLoop, SndVoiceStart
 * Called by: PlayerCheckHitProj, PlayerGetHit, PlayerGetHitG,
 *            PlayerSCtrlApplyElem, PlayerUpdate
 *
 * Elecbyte file: src/mugen/sound.c
 */
int GameSndPlayIDPos(int arg1,int arg2,int *sounds,int arg4,int arg5,int arg6)

{
  int *pi1;
  int i2;
  int i3;
  int i4;
  
  pi1 = g;
  if ((((g[0x6ef3] != 0) && (sounds != (int *)0x0)) && (g[0x7308] == 0)) && (arg4 != -1)) {
    pi1 = (int *)SndIDPrepare(arg1,sounds,arg4,arg5);
    if (pi1 != (int *)0xffffffff) {
      if (g[G_SOUND_LINUX_STEREOEFFECTS] == 0) {
        i2 = 0;
      }
      else {
        i2 = ScrPositionToPan(arg2);
      }
      i3 = SndCorrectVolOff(arg6);
      i3 = PanVolumeAdjust(i3 + g[G_SOUND_LINUX_WAVVOLUME],i2);
      i4 = SndVoiceGetFreq((int)pi1);
      SndVoiceSetVol((int)pi1,i3);
      SndVoiceSetFreq((int)pi1,i4);
      SndVoiceSetPan((int)pi1,i2);
      SndVoiceSetLoop((int)pi1,0);
      pi1 = (int *)SndVoiceStart((int)pi1);
    }
  }
  return (int)pi1;
}

/* ScrPositionToPan @ 0x080ba180, 170 bytes
 *
 * Converts a screen x coordinate (0-319, centre 160) into a panning value. A
 * 40-pixel dead zone sits around the centre; beyond it, the offset is scaled
 * by the configured PanningWidth.
 *
 * Parameters:
 *   x            int
 *
 * Globals read: sound_linux_panningwidth
 * Calls: SndCorrectVolOff
 * Called by: GameSndPlayIDPos, PlayerSCtrlApplyElem, SCtrlDoPlaySndInfo
 *
 * Elecbyte file: src/mugen/sound.c
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
int ScrPositionToPan(int x)

{
  int i1;
  uint32_t u2;
  
  u2 = x - 0xa0;
  if (-0x29 < (int)u2) {
    u2 = u2 & ((int)u2 < 0x29) - 1;
  }
  if ((int)u2 < -0x28) {
    u2 = u2 + 0x28;
  }
  else if (0x28 < (int)u2) {
    u2 = u2 - 0x28;
  }
  if (g[G_SOUND_LINUX_PANNINGWIDTH] + -0x14 < 1) {
    i1 = 0;
  }
  else {
    i1 = (int)X87_FIST32(((float80)(int)u2 * 128.0) / (float)(g[G_SOUND_LINUX_PANNINGWIDTH] + -0x14));
  }
  i1 = SndCorrectVolOff(i1);
  if (i1 < -0x7f) {
    i1 = -0x7f;
  }
  if (0x7f < i1) {
    i1 = 0x7f;
  }
  return i1;
}

/* PanVolumeAdjust @ 0x080ba230, 98 bytes
 *
 * Lowers a volume for a panned sound: vol * (1 - |pan| / 256), clamped to
 * 0-255.
 *
 * Parameters:
 *   vol          int
 *   pan          int
 *
 * Called by: GameSndPlayIDPos, SCtrlDoPlaySndInfo
 *
 * Elecbyte file: src/mugen/sound.c
 */
uint32_t PanVolumeAdjust(int vol,int pan)

{
  uint32_t u1;
  
  if (pan < 0) {
    pan = -pan;
  }
  u1 = (uint32_t)X87_FIST32((1.0 - (float)pan * 0.00390625) * (float)vol);
  u1 = u1 & 0xffffffffU - ((int)u1 >> 0x1f);
  if (0xff < (int)u1) {
    u1 = 0xff;
  }
  return u1;
}

/* GameSetVol @ 0x080ba2a0, 132 bytes
 *
 * Applies the configured sound effect and music volumes (options or
 * mugen.cfg) to the sound library.
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t
 *
 * Globals read: options_wavvolume, options_midivolume
 * Calls: SndSetVol
 * Called by: BGMLoadAndStart, GameInit, GamePlay, GameReloadStage,
 *            GameRoundUpdate, ModeSelect
 *
 * Elecbyte file: src/mugen/sound.c
 */
void GameSetVol(int arg1,uint32_t arg2)

{
  uint32_t u1;
  
  if (arg1 == -1) {
    u1 = 0xffffffff;
  }
  else {
    u1 = (arg1 * g[G_OPTIONS_WAVVOLUME]) / 0x32;
  }
  if (arg2 != 0xffffffff) {
    arg2 = (int)(arg2 * g[G_OPTIONS_MIDIVOLUME]) / 0x32;
  }
  if (g[0x6ef3] != 0) {
    SndSetVol(u1,arg2);
    return;
  }
  return;
}

/* PlayerSndID @ 0x080ba330, 46 bytes
 *
 * Returns the sound owner id of channel `channel` of a player: channel *
 * (ids per channel) + player id + 1000, or -1 for channel -1. Each player
 * channel gets its own id so PlaySnd/StopSnd channels act per player.
 *
 * Parameters:
 *   player       int
 *   channel      int
 *
 * Called by: PlayerGetHit, PlayerSCtrlApplyElem, PlayerUpdate,
 *            SCtrlDoPlaySndInfo
 *
 * Elecbyte file: src/mugen/sound.c
 */
int PlayerSndID(int player,int channel)

{
  if (channel == -1) {
    return -1;
  }
  return channel * g[0x7395] + *(int *)(player + 8) + 1000;
}

/* ParseSndGI @ 0x080ba360, 45 bytes
 *
 * Reads a "group, index" sound key (TPScanf "%i,%i"); missing keys get the
 * default pair.
 *
 * Parameters:
 *   tp           int
 *   keyname      char *
 *   out          uint32_t *
 *   defval       int
 *
 * Calls: TPScanf
 * Called by: CharselReadConfig, GameLoadSystem
 *
 * Elecbyte file: src/mugen/sound.c
 */
void ParseSndGI(int tp,char *keyname,uint32_t *out,int defval)

{
  *out = 0xffffffff;
  TPScanf(tp,keyname,"%i,%i",out,defval);
  return;
}

