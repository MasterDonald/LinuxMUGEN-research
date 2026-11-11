/*
 * display.c -- display output
 * Frame skipping, copying the finished frame to the screen (with DoubleRes
 * filters) and screenshots.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/display.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"

extern int framesskipped_0 __asm__("D_08287a64"); /* file-static 0x08287a64 */
extern int snapcount_1 __asm__("D_08287a68"); /* file-static 0x08287a68 */

/* FrameSkipReset @ 0x0808d940, 30 bytes
 *
 * Restarts frame-skip accounting: clears the skip counters and the timer's
 * frame accumulator.
 *
 * Calls: TimerSyncReset
 * Called by: CharacterSelectScreen, ContinueScreenLoop, GameLoop,
 *            GameNextRound, GameReloadStage, KeyConfigScreen, ModeSelect,
 *            OptionsScreen, PlayCutscene, VersusScreen
 *
 * Elecbyte file: src/mugen/display.c
 */
void FrameSkipReset(void)

{
  int *pi1;
  
  pi1 = g;
  g[0x7306] = 0;
  pi1[0x7307] = 0;
  TimerSyncReset();
  return;
}

/* FrameSkipUpdate @ 0x0808d960, 186 bytes
 *
 * Decides whether the next frame is drawn. With automatic frame skip
 * (FrameSkip = -1), drawing is skipped while the timer reports frames due,
 * but at most 4 frames in a row; after 4 the timer is resynchronised. With a
 * fixed FrameSkip value, n frames are skipped for each drawn one. Skipping
 * is disabled while the speed-test flag is set. The result is stored in the
 * "skip drawing" global used by DrawToScreen.
 *
 * Globals read: frameskip, speed_flag
 * Calls: TimerGetSync, TimerSyncReset, TimerSkipSync
 * Called by: CharacterSelectScreenDraw, ContinueScreenLoop, GameLoop,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, PlayCutscene,
 *            VersusScreen
 *
 * Elecbyte file: src/mugen/display.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
void FrameSkipUpdate(void)

{
  int i1;
  int i2;
  int *pi3;
  bool b4;
  uint32_t stale_var;
  
  pi3 = g;
  i1 = g[G_FRAMESKIP];
  g[0x7307] = 0;
  if (i1 == -1) {
    pi3[0x7306] = 0;
    b4 = TimerGetSync();
    if (((ZEXT8(b4) == 0) || (g[G_SPEED_FLAG] != 0)) || (3 < framesskipped_0)) {
      if (framesskipped_0 == 4) {
        TimerSyncReset();
      }
      framesskipped_0 = 0;
    }
    else {
      g[0x7306] = 1;
      framesskipped_0 = framesskipped_0 + 1;
      TimerSkipSync();
    }
  }
  else {
    i2 = pi3[0x7306];
    pi3[0x7306] = i2 + 1;
    if (i1 < i2 + 1) {
      pi3[0x7306] = 0;
    }
  }
  if (g[0x7306] != 0) {
    g[0x7307] = 1;
  }
  return;
}

/* DrawToScreen @ 0x0808da20, 391 bytes
 *
 * Copies the finished frame to the screen unless this frame is skipped.
 * Without DoubleRes, the back buffer is centred on the screen
 * (V_BufToScreenXY). With DoubleRes, the fight screens first double the
 * 320x240 image into the 640x480 buffer with the configured filter (pixel
 * doubling, diagonal, blur or scanlines; V_DoubleRes*) and then copy that
 * buffer.
 *
 * Globals read: video_linux_doubleres, backbuffer
 * Calls: V_BufToScreenXY, SpriteArrayAccess, V_DoubleResDiag,
 *        V_DoubleResBlur, V_DoubleResLines, GameModeInFightScreen,
 *        V_DoubleRes, V_BufToScreenStretch
 * Called by: CharacterSelectScreenDraw, ContinueScreenLoop, GameLoop,
 *            GameNextRound, GameReloadStage, GameRoundUpdate,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, PlayCutscene,
 *            VersusScreen
 *
 * Elecbyte file: src/mugen/display.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
void DrawToScreen(void)

{
  uint32_t *pu1;
  bool b2;
  int sprite;
  int *sprite2;
  uint32_t stale_var;
  
  if (g[0x7307] == 0) {
    if (g[G_VIDEO_LINUX_DOUBLERES] == 0) {
      if (g[0x7558] == 0) {
        V_BufToScreenXY((int *)g[0x4139],0,S_Width - V_Width >> 1,S_Height - V_Height >> 1);
        return;
      }
      sprite2 = (int *)g[0x4139];
    }
    else {
      sprite = SpriteArrayAccess((int *)g[G_BACKBUFFER],0);
      pu1 = *(uint32_t **)(sprite + 0x24);
      sprite2 = (int *)SpriteArrayAccess((int *)g[0x4138],0);
      sprite = sprite2[9];
      if (g[G_VIDEO_LINUX_DOUBLERES] == 1) {
        V_DoubleResDiag((int *)pu1,sprite);
      }
      if (g[G_VIDEO_LINUX_DOUBLERES] == 2) {
        V_DoubleResBlur((int *)pu1,sprite);
      }
      if (g[G_VIDEO_LINUX_DOUBLERES] == 3) {
        V_DoubleResLines(pu1,sprite);
      }
      if ((g[G_VIDEO_LINUX_DOUBLERES] == 4) && (b2 = GameModeInFightScreen(), ZEXT8(b2) == 0))
      {
        V_DoubleRes(pu1,sprite);
      }
      if ((g[0x7558] == 0) || ((V_Width == S_Width && (V_Height == S_Height)))) {
        V_BufToScreenXY((int *)g[0x4138],0,S_Width - *sprite2 >> 1,S_Height - sprite2[1] >> 1);
        return;
      }
      sprite2 = (int *)g[0x4138];
    }
    V_BufToScreenStretch(sprite2,0);
  }
  return;
}

/* ScreenSnap @ 0x0808dbb0, 117 bytes
 *
 * Saves the current back buffer (or the doubled buffer) as the first free
 * "mugen<n>.pcx" in the current directory (Allegro save_pcx). Bound to the
 * screenshot key.
 *
 * Globals read: backbuffer
 * Calls: SpriteArrayAccess
 * C library: sprintf, access, save_pcx
 * Called by: CharacterSelectScreen, GameInputUpdate, ModeSelect,
 *            OptionsScreen, PlayCutscene, VersusScreen
 *
 * Elecbyte file: src/mugen/display.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x20 bytes, 1
 *       variables), because their address is taken.
 */
void ScreenSnap(void)

{
  int sprite;
  uint32_t entry_ECX;
  uint32_t stale_ECX;
  int *sprites;
  unsigned char frame[0x20] __attribute__((aligned(16)));
#define stk_1c (*(uint8_t (*)[20])(frame + 0x4))
  
  sprites = (int *)g[G_BACKBUFFER];
  do {
    sprintf((char *)stk_1c,"mugen%i.pcx",snapcount_1,entry_ECX);
    snapcount_1 = snapcount_1 + 1;
    sprite = access((char *)stk_1c,0);
    entry_ECX = stale_ECX;
  } while (sprite == 0);
  if ((int *)g[0x4138] != (int *)0x0) {
    sprites = (int *)g[0x4138];
  }
  sprite = SpriteArrayAccess(sprites,0);
  save_pcx(stk_1c,*(uint32_t **)(sprite + 0x24),(uint8_t *)0x0);
  return;
}
#undef stk_1c

