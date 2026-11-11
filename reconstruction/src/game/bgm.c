/*
 * bgm.c -- background music
 * Loads, starts, pauses and polls the music of stages, menus and storyboards
 * in any supported format (MIDI, MP3, MOD/S3M/XM, CD audio).
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/bgm.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* BGMParse @ 0x08085240, 103 bytes
 *
 * Reads a music key ("bgm" style: file name) and its ".loop" flag from a
 * definition group. Returns true if the key exists.
 *
 * Parameters:
 *   tp           int
 *   bgmdef       uint8_t *
 *   keyname      char *
 *
 * Calls: TPScanf, TPGetValueInt
 * C library: sprintf
 * Called by: GameLoadSystem
 *
 * Elecbyte file: src/mugen/bgm.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x60 bytes, 1
 *       variables), because their address is taken.
 */
bool BGMParse(int tp,uint8_t *bgmdef,char *keyname)

{
  int i1;
  unsigned char frame[0x60] __attribute__((aligned(16)));
#define keyname2 (*(char (*)[80])(frame + 0x4))
  
  *(uint32_t *)(bgmdef + 0x1000) = 1;
  *bgmdef = 0;
  i1 = TPScanf(tp,keyname,"%s",bgmdef);
  if (i1 == 1) {
    sprintf(keyname2,"%s.loop",keyname,0);
    TPGetValueInt(tp,keyname2,(uint32_t *)(bgmdef + 0x1000));
  }
  return i1 == 1;
}
#undef keyname2

/* BGMStart @ 0x080852b0, 259 bytes
 *
 * Starts the loaded music: MIDI (looped), tracker module, or CD audio (a
 * given or random audio track). MP3 starts at load time.
 *
 * Parameters:
 *   bgm          int *
 *
 * Calls: SndMidiPlayLoop, MODPlay, CDAGetTrackRange, CDATrackIsAudio,
 *        CDAPlay
 * C library: random
 * Called by: BGMLoadAndStart, GamePlay, GameReloadStage
 *
 * Elecbyte file: src/mugen/bgm.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x10 bytes, 2
 *       variables), because their address is taken.
 */
void BGMStart(int *bgm)

{
  bool b1;
  uint32_t stale_var;
  uint32_t u2;
  long l3;
  int i4;
  unsigned char frame[0x10] __attribute__((aligned(16)));
#define stk_10 (*(uint32_t *)(frame + 0x0))
#define stk_c (*(uint32_t *)(frame + 0x4))
  
  if (g[0x6ef3] != 0) {
    i4 = *bgm;
    if (i4 == 1) {
      SndMidiPlayLoop((int *)bgm[1],0,0xffffffff);
      i4 = *bgm;
    }
    if (i4 == 2) {
      MODPlay((int *)bgm[2],-1);
      i4 = *bgm;
    }
    if (i4 == 4) {
      stk_10 = 1;
      stk_c = 1;
      u2 = bgm[3];
      if ((u2 == 0) &&
         (b1 = CDAGetTrackRange(&stk_10,&stk_c), ZEXT8(b1) != 0)) {
        while ((u2 = CDATrackIsAudio((char)stk_10), u2 == 0 &&
               ((int)stk_10 < (int)stk_c))) {
          stk_10 = stk_10 + 1;
        }
        if ((int)stk_10 < (int)stk_c) {
          l3 = random();
          u2 = stk_10 + l3 % (int)((stk_c - stk_10) + 1);
        }
        else {
          u2 = 1;
        }
      }
      i4 = CDAPlay(u2,1);
      if (i4 == 0) {
        return;
      }
    }
    bgm[7] = 1;
  }
  return;
}
#undef stk_10
#undef stk_c

/* BGMPause @ 0x080853c0, 119 bytes
 *
 * Pauses the music (user pause): tracker, MP3 (volume to 0 and pause) or CD.
 *
 * Parameters:
 *   bgm          int *
 *
 * Calls: BGMGetPause, MODPause, MP3SetVol, MP3Pause, CDAPause
 * C library: midi_pause
 * Called by: GameLoop, GamePlay, PlayCutscene
 *
 * Elecbyte file: src/mugen/bgm.c
 */
void BGMPause(int *bgm)

{
  int i1;
  
  if ((g[0x6ef3] != 0) && (i1 = BGMGetPause((int)bgm), i1 == 0)) {
    i1 = *bgm;
    if (i1 == 2) {
      MODPause();
    }
    else if (i1 < 3) {
      if (i1 == 1) {
        midi_pause();
      }
    }
    else if (i1 == 3) {
      MP3SetVol(0);
      MP3Pause();
    }
    else if (i1 == 4) {
      CDAPause();
    }
    bgm[4] = 1;
  }
  return;
}

/* BGMSysPause @ 0x08085440, 119 bytes
 *
 * Pauses the music because the window lost focus (PauseBGMOnDefocus); same
 * actions as BGMPause, tracked separately.
 *
 * Parameters:
 *   bgm          int *
 *
 * Calls: BGMGetPause, MODPause, MP3SetVol, MP3Pause, CDAPause
 * C library: midi_pause
 * Called by: BGMPoll
 *
 * Elecbyte file: src/mugen/bgm.c
 */
void BGMSysPause(int *bgm)

{
  int i1;
  
  if ((g[0x6ef3] != 0) && (i1 = BGMGetPause((int)bgm), i1 == 0)) {
    i1 = *bgm;
    if (i1 == 2) {
      MODPause();
    }
    else if (i1 < 3) {
      if (i1 == 1) {
        midi_pause();
      }
    }
    else if (i1 == 3) {
      MP3SetVol(0);
      MP3Pause();
    }
    else if (i1 == 4) {
      CDAPause();
    }
    bgm[5] = 1;
  }
  return;
}

/* BGMGetPause @ 0x080854c0, 26 bytes
 *
 * Returns the user pause flag of a music record.
 *
 * Parameters:
 *   bgm          int
 *
 * Called by: BGMPause, BGMPollIgnoreDefocus, BGMSysPause
 *
 * Elecbyte file: src/mugen/bgm.c
 */
uint32_t BGMGetPause(int bgm)

{
  uint32_t u1;
  
  u1 = 0;
  if ((*(int *)(bgm + 0x10) != 0) || (*(int *)(bgm + 0x14) != 0)) {
    u1 = 1;
  }
  return u1;
}

/* BGMResume @ 0x080854e0, 144 bytes
 *
 * Resumes paused music, restoring the MP3 volume.
 *
 * Parameters:
 *   bgm          int *
 *
 * Globals read: sound_linux_mp3volume
 * Calls: MODResume, MP3Resume, SndCorrectVolOff, MP3SetVol, CDAResume
 * C library: midi_resume
 * Called by: GameLoop, GamePlay, PlayCutscene
 *
 * Elecbyte file: src/mugen/bgm.c
 */
uint32_t BGMResume(int *bgm)

{
  int i1;
  uint32_t entry_EDX;
  
  if (((g[0x6ef3] != 0) && (bgm[4] != 0)) && (bgm[5] == 0)) {
    i1 = *bgm;
    if (i1 == 2) {
      MODResume();
    }
    else if (i1 < 3) {
      if (i1 == 1) {
        midi_resume();
      }
    }
    else if (i1 == 3) {
      MP3Resume();
      i1 = SndCorrectVolOff(bgm[6]);
      MP3SetVol(i1 + g[G_SOUND_LINUX_MP3VOLUME]);
    }
    else if (i1 == 4) {
      CDAResume();
    }
    bgm[4] = 0;
  }
  return entry_EDX;
}

/* BGMSysResume @ 0x08085570, 144 bytes
 *
 * Resumes music paused by BGMSysPause.
 *
 * Parameters:
 *   bgm          int *
 *
 * Globals read: sound_linux_mp3volume
 * Calls: MODResume, MP3Resume, SndCorrectVolOff, MP3SetVol, CDAResume
 * C library: midi_resume
 * Called by: BGMPoll
 *
 * Elecbyte file: src/mugen/bgm.c
 */
void BGMSysResume(int *bgm)

{
  int i1;
  
  if (((g[0x6ef3] != 0) && (bgm[4] == 0)) && (bgm[5] != 0)) {
    i1 = *bgm;
    if (i1 == 2) {
      MODResume();
    }
    else if (i1 < 3) {
      if (i1 == 1) {
        midi_resume();
      }
    }
    else if (i1 == 3) {
      MP3Resume();
      i1 = SndCorrectVolOff(bgm[6]);
      MP3SetVol(i1 + g[G_SOUND_LINUX_MP3VOLUME]);
    }
    else if (i1 == 4) {
      CDAResume();
    }
    bgm[5] = 0;
  }
  return;
}

/* BGMGetVolume @ 0x08085600, 86 bytes
 *
 * Returns the current music volume of the active music type.
 *
 * Parameters:
 *   bgm          int *
 *
 * Globals read: sound_linux_midivolume
 * Calls: MODGetVol, MP3GetVol, CDAGetVol
 * Called by: PlayCutscene
 *
 * Elecbyte file: src/mugen/bgm.c
 */
int BGMGetVolume(int *bgm)

{
  int i1;
  
  i1 = *bgm;
  if (i1 == 2) {
    i1 = MODGetVol();
    return i1;
  }
  if (i1 < 3) {
    if (i1 == 1) {
      return g[G_SOUND_LINUX_MIDIVOLUME];
    }
  }
  else {
    if (i1 == 3) {
      i1 = MP3GetVol();
      return i1;
    }
    if (i1 == 4) {
      i1 = CDAGetVol();
      return i1;
    }
  }
  return 0;
}

/* BGMSetVolume @ 0x08085660, 116 bytes
 *
 * Sets the music volume of the active music type (tracker, MP3, CD).
 *
 * Parameters:
 *   bgm          int *
 *   vol          uint32_t
 *
 * Globals written: sound_linux_midivolume
 * Calls: MODSetVol, MP3SetVol, CDASetVol
 * Called by: PlayCutscene
 *
 * Elecbyte file: src/mugen/bgm.c
 */
void BGMSetVolume(int *bgm,uint32_t vol)

{
  int i1;
  
  i1 = *bgm;
  if (i1 == 2) {
    MODSetVol(vol);
    return;
  }
  if (i1 < 3) {
    if (i1 == 1) {
      g[G_SOUND_LINUX_MIDIVOLUME] = vol;
    }
  }
  else {
    if (i1 == 3) {
      MP3SetVol(vol);
      return;
    }
    if (i1 == 4) {
      CDASetVol(vol);
      return;
    }
  }
  return;
}

/* BGMPoll @ 0x080856e0, 116 bytes
 *
 * Per-frame music service: pauses or resumes on focus changes
 * (PauseBGMOnDefocus) and calls BGMPollIgnoreDefocus.
 *
 * Parameters:
 *   bgm          int *
 *
 * Globals read: sound_linux_pausebgmondefocus
 * Calls: BGMSysPause, BGMSysResume, BGMPollIgnoreDefocus
 * Called by: CharacterSelectScreen, ContinueScreenLoop, GameLoop,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, VersusScreen
 *
 * Elecbyte file: src/mugen/bgm.c
 */
void BGMPoll(int *bgm)

{
  if (g[0x6ef3] != 0) {
    if (g[G_SOUND_LINUX_PAUSEBGMONDEFOCUS] != 0) {
      if ((g[0x74e7] == 0) && (bgm[5] == 0)) {
        BGMSysPause(bgm);
      }
      else if ((g[0x74e7] != 0) && (bgm[5] != 0)) {
        BGMSysResume(bgm);
      }
    }
    BGMPollIgnoreDefocus(bgm);
    return;
  }
  return;
}

/* BGMPollIgnoreDefocus @ 0x08085760, 148 bytes
 *
 * Per-frame music service without the focus check: lets the MP3 decoder run
 * and keeps CD looping (CDAPoll).
 *
 * Parameters:
 *   bgm          int *
 *
 * Globals read: frame_count
 * Calls: MP3Poll, BGMGetPause, MP3GetVol, MP3SetVol, CDAPoll
 * Called by: BGMPoll, PlayCutscene
 *
 * Elecbyte file: src/mugen/bgm.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: Returns nothing (the original left only stale register values).
 */
void BGMPollIgnoreDefocus(int *bgm)

{
  int i1;
  uint32_t saved_EBX;
  
  if (g[0x6ef3] != 0) {
    if (*bgm == 3) {
      MP3Poll();
      i1 = BGMGetPause((int)bgm);
      if ((i1 != 0) && (i1 = MP3GetVol(), 0 < i1)) {
        i1 = MP3GetVol();
        MP3SetVol((i1 * 10) / 0xb + -4);
      }
    }
    else if ((*bgm == 4) && (g[G_FRAME_COUNT] % 6 == 0)) {
      CDAPoll();
    }
  }
  return;
}

/* BGMCheckExtension @ 0x08085800, 5 bytes
 *
 * Returns the file type of a music file name (CheckExtension).
 *
 * Parameters:
 *   arg1         char *
 *
 * Calls: CheckExtension
 * Called by: BGMLoad
 *
 * Elecbyte file: src/mugen/bgm.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to
 *       _alemu_stricmp,strlen
 */
uint32_t BGMCheckExtension(char *arg1)

{
  uint32_t u1;
  
  u1 = CheckExtension(arg1);
  return u1;
}

/* BGMLoad @ 0x08085810, 584 bytes
 *
 * Loads a music file into a music record by its type: MIDI (if PlayMIDI),
 * MP3 (if PlayMP3; starts playing), tracker module (if PlayMOD; "Warning:
 * could not allocate mod voices"), or a CD track number (if PlayCDA).
 * Volumes come from the configuration.
 *
 * Parameters:
 *   bgm          int *
 *   filename     uint8_t *
 *   loop         int
 *
 * Globals read: sound_linux_playmidi, sound_linux_playmp3,
 *               sound_linux_mp3volume, sound_linux_playcda,
 *               sound_linux_cdavolume, sound_linux_playmod,
 *               sound_linux_modvoices, clipboard, sound_linux_modvolume
 * Calls: BGMFree, BGMCheckExtension, SndMidiReadFile, SndCorrectVolOff,
 *        MP3SetVol, MP3LoadAndPlay, CDAInit, CDASetVol, MODInit,
 *        ClipboardAppend, MODLoad, MODSetVol
 * C library: __strtol_internal, strcpy
 * Called by: BGMLoadAndStart, GameLoadStage
 * Messages:
 *   "Warning: could not allocate mod voices\n"
 *
 * Elecbyte file: src/mugen/bgm.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
uint32_t BGMLoad(int *bgm,uint8_t *filename,int loop)

{
  bool b1;
  int i2;
  uint32_t *pu3;
  uint32_t stale_var;
  uint32_t u4;
  int *pi5;
  
  if ((g[0x6ef3] != 0) && (g[0x755f] == 0)) {
    BGMFree(bgm);
    *bgm = 0;
    bgm[9] = loop;
    if ((*filename != 0) && (g[0x6ef3] != 0)) {
      i2 = BGMCheckExtension((char *)filename);
      if (i2 == 6) {
        if (g[G_SOUND_LINUX_PLAYMIDI] == 0) {
          return 1;
        }
        pu3 = SndMidiReadFile(filename);
        bgm[1] = (int)pu3;
        if (pu3 == (uint32_t *)0x0) {
          return 1;
        }
        *bgm = 1;
      }
      else if (i2 < 7) {
        if (i2 != 5) {
          return 1;
        }
        if (g[G_SOUND_LINUX_PLAYMP3] == 0) {
          return 1;
        }
        i2 = SndCorrectVolOff(bgm[6]);
        MP3SetVol(i2 + g[G_SOUND_LINUX_MP3VOLUME]);
        i2 = MP3LoadAndPlay((char *)filename,loop);
        if (i2 == 0) {
          return 1;
        }
        *bgm = 3;
      }
      else {
        if (i2 != 7) {
          if (i2 != 8) {
            return 1;
          }
          if (g[G_SOUND_LINUX_PLAYCDA] == 0) {
            return 1;
          }
          if ((char)g[0x7564] == '\0') {
            pi5 = (int *)0x0;
          }
          else {
            pi5 = g + 0x7564;
          }
          CDAInit((char *)pi5);
          u4 = __strtol_internal(filename,(uint32_t *)0x0,10,0);
          if ((int)u4 < 0) {
            return 1;
          }
          if (g[G_SOUND_LINUX_CDAVOLUME] != -1) {
            CDASetVol(g[G_SOUND_LINUX_CDAVOLUME] + bgm[6]);
          }
          *bgm = 4;
          bgm[3] = u4;
          return 1;
        }
        if (g[G_SOUND_LINUX_PLAYMOD] == 0) {
          return 1;
        }
        b1 = MODInit(g[G_SOUND_LINUX_MODVOICES]);
        if (ZEXT8(b1) == 0) {
          ClipboardAppend((int *)g[G_CLIPBOARD],"Warning: could not allocate mod voices\n",bgm,
                          bgm);
          return 1;
        }
        bgm[2] = 0;
        i2 = MODLoad(filename);
        bgm[2] = i2;
        if (i2 == 0) {
          return 1;
        }
        *bgm = 2;
        i2 = SndCorrectVolOff(bgm[6]);
        MODSetVol(i2 + g[G_SOUND_LINUX_MODVOLUME]);
      }
      strcpy((char *)(bgm + 10),(char *)filename);
    }
  }
  return 1;
}

/* BGMLoadAndStart @ 0x08085a60, 221 bytes
 *
 * Frees the current music, applies the volumes, loads the new file and
 * starts it. "Error loading BGM: %s" goes to the debug output on failure.
 *
 * Parameters:
 *   bgm          int *
 *   filename     uint8_t *
 *   arg3         int
 *   arg4         int
 *
 * Globals read: sound_linux_masterwavvolume, sound_linux_midivolume,
 *               errmsg
 * Calls: BGMFree, GameSetVol, BGMLoad, BGMStart
 * C library: _alemu_stricmp, sprintf
 * Called by: BGMPlayForScene, CharacterSelectScreen, ModeSelect,
 *            VersusScreen
 * Messages:
 *   "Error loading BGM: %s"
 *
 * Elecbyte file: src/mugen/bgm.c
 */
uint32_t BGMLoadAndStart(int *bgm,uint8_t *filename,int arg3,int arg4)

{
  bool b1;
  int i2;
  uint32_t stale_ECX;
  
  b1 = false;
  if ((g[0x6ef3] != 0) && (g[0x755f] == 0)) {
    if ((filename == (uint8_t *)0x0) || (*filename == 0)) {
      b1 = true;
    }
    if (b1) {
      BGMFree(bgm);
    }
    else if ((((bgm[7] == 0) ||
              (i2 = _alemu_stricmp((char *)(bgm + 10),(char *)filename), i2 != 0)) ||
             (bgm[9] == 0)) || (arg3 == 0)) {
      GameSetVol(g[G_SOUND_LINUX_MASTERWAVVOLUME],g[G_SOUND_LINUX_MIDIVOLUME]);
      bgm[6] = arg4;
      i2 = BGMLoad(bgm,filename,arg3);
      if (i2 == 0) {
        sprintf((char *)(g + G_ERRMSG),"Error loading BGM: %s",filename,stale_ECX);
        return 0;
      }
      BGMStart(bgm);
    }
  }
  return 1;
}

/* BGMFree @ 0x08085b40, 152 bytes
 *
 * Stops and frees whatever the music record holds (tracker, MIDI, MP3, CD).
 *
 * Parameters:
 *   bgm          int *
 *
 * Calls: MODStop, MODUnload, MODDeInit, SndMidiFree, MP3Unload, CDAStop
 * Called by: BGMLoad, BGMLoadAndStart, BGMStopForScene, GamePlay,
 *            GameUnloadStage, MainLoop, VersusScreen
 *
 * Elecbyte file: src/mugen/bgm.c
 */
int * BGMFree(int *bgm)

{
  int i1;
  int *pi2;
  int i3;
  int *pi4;
  
  i1 = bgm[6];
  pi2 = g;
  if (g[0x6ef3] != 0) {
    i3 = *bgm;
    if (i3 == 2) {
      MODStop();
      MODUnload((uint32_t *)bgm[2]);
      MODDeInit();
    }
    else if (i3 < 3) {
      if (i3 == 1) {
        SndMidiFree((void *)bgm[1]);
      }
    }
    else if (i3 == 3) {
      MP3Unload();
    }
    else if (i3 == 4) {
      CDAStop();
    }
    pi2 = (int *)0x0;
    pi4 = bgm;
    for (i3 = 0x40a; i3 != 0; i3 = i3 + -1) {
      *pi4 = 0;
      pi4 = pi4 + 1;
    }
    *bgm = 0;
    bgm[6] = i1;
    bgm[7] = 0;
  }
  return pi2;
}

/* BGMPlayForScene @ 0x08085be0, 35 bytes
 *
 * Storyboard callback: loads and starts a scene's music. Called through the
 * function pointer registered with SceneRegisterBGMFn.
 *
 * Parameters:
 *   filename     uint8_t *
 *   arg2         int
 *
 * Calls: BGMLoadAndStart
 *
 * Elecbyte file: src/mugen/bgm.c
 */
void BGMPlayForScene(uint8_t *filename,int arg2)

{
  BGMLoadAndStart(g + 0x6efa,filename,arg2,0);
  return;
}

/* BGMStopForScene @ 0x08085c10, 23 bytes
 *
 * Storyboard callback: stops the scene music.
 *
 * Calls: BGMFree
 *
 * Elecbyte file: src/mugen/bgm.c
 */
void BGMStopForScene(void)

{
  BGMFree(g + 0x6efa);
  return;
}

