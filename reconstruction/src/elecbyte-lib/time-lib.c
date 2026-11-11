/*
 * time-lib.c -- timer
 * The Allegro timer interrupt, frame synchronisation at a target frame rate,
 * and FPS measurement.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/time-lib.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"

extern int CalculatedFPS __asm__("D_08287a14"); /* file-static 0x08287a14 */
extern int oldtime_0 __asm__("D_08287a18"); /* file-static 0x08287a18 */
extern int CurCall_1 __asm__("D_08287a1c"); /* file-static 0x08287a1c */

/* TimerHandler @ 0x0807af40, 79 bytes
 *
 * Allegro timer interrupt, called TicksPerSecond times a second. It
 * increments Ticks and sets TicksUpdate. When frame sync is on, it adds
 * 0x10000 to the 16.16 fixed-point accumulator SyncLast; each time SyncLast
 * reaches SyncRate, one frame is due (SyncCur + 1).
 *
 * Elecbyte file: src/lib/time-lib.c
 */
void TimerHandler(void)

{
  Ticks = Ticks + 1;
  TicksUpdate = 1;
  if ((0 < SyncRate) && (SyncLast = SyncLast + 0x10000, SyncRate <= SyncLast)) {
    SyncLast = SyncLast - SyncRate;
    SyncCur = SyncCur + 1;
  }
  return;
}

/* TimerInit @ 0x0807af90, 107 bytes
 *
 * Installs the Allegro timer and TimerHandler at `ticks_per_second` (the PIT
 * rate 0x1234dd divided by it). Resets all counters; FPS is measured every
 * 10 calls. Returns true on success.
 *
 * Parameters:
 *   ticks_per_second int
 *
 * C library: install_timer, install_int_ex
 * Called by: GameInit
 *
 * Elecbyte file: src/lib/time-lib.c
 * Note: function addresses written as literals replaced by symbol references
 */
bool TimerInit(int ticks_per_second)

{
  int i1;
  
  Ticks = 0;
  TicksPerSecond = ticks_per_second;
  TicksUpdate = 0;
  FPSUpdateTicks = 10;
  SyncRate = 0;
  SyncLast = 0;
  install_timer();
  i1 = install_int_ex((int)TimerHandler,(int)(0x1234dd / (int64_t)ticks_per_second));
  return i1 == 0;
}

/* TimerDeInit @ 0x0807b000, 21 bytes
 *
 * Removes TimerHandler and the Allegro timer (remove_int, remove_timer).
 *
 * C library: remove_int, remove_timer
 * Called by: GameDeInit
 *
 * Elecbyte file: src/lib/time-lib.c
 * Note: function addresses written as literals replaced by symbol references
 */
void TimerDeInit(void)

{
  remove_int((int)TimerHandler);
  remove_timer();
  return;
}

/* TimerChangeSpeed @ 0x0807b020, 32 bytes
 *
 * Reinstalls TimerHandler at a new tick rate.
 *
 * Parameters:
 *   ticks_per_second int
 *
 * C library: install_int_ex
 *
 * Elecbyte file: src/lib/time-lib.c
 * Note: function addresses written as literals replaced by symbol references
 */
void TimerChangeSpeed(int ticks_per_second)

{
  install_int_ex((int)TimerHandler,(int)(0x1234dd / (int64_t)ticks_per_second));
  return;
}

/* TimerDelay @ 0x0807b040, 5 bytes
 *
 * Waits for a number of milliseconds (Allegro rest). Used by the precache
 * loader.
 *
 * Parameters:
 *   ms           uint32_t
 *
 * C library: rest
 * Called by: PrecacheFinish
 *
 * Elecbyte file: src/lib/time-lib.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to
 *       rest_callback
 */
uint32_t TimerDelay(uint32_t ms)

{
  uint32_t u1;
  
  u1 = rest(ms);
  return u1;
}

/* TimerSetTicks @ 0x0807b050, 10 bytes
 *
 * Sets the tick counter.
 *
 * Parameters:
 *   ticks        int
 *
 * Called by: _mangled_main
 *
 * Elecbyte file: src/lib/time-lib.c
 */
void TimerSetTicks(int ticks)

{
  Ticks = ticks;
  return;
}

/* TimerGetFPS @ 0x0807b060, 97 bytes
 *
 * Returns the measured frame rate. Every FPSUpdateTicks calls it computes
 * TicksPerSecond * FPSUpdateTicks / (ticks elapsed). In between, it returns
 * the last value. Shown by the debug display.
 *
 * Called by: ShowDebugInfo
 *
 * Elecbyte file: src/lib/time-lib.c
 * Note: 1 exact-text site patches (see SITE_PATCHES in
 *       tools/build_source_tree.py)
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
float80 TimerGetFPS(void)

{
  int i1;
  
  if ((FPSUpdateTicks <= CurCall_1) && (Ticks != oldtime_0)) {
    i1 = Ticks - oldtime_0;
    oldtime_0 = Ticks;
    CurCall_1 = 0;
    CalculatedFPS = BITS_F2I(int, (((float)TicksPerSecond * (float)FPSUpdateTicks) / (float80)i1));
  }
  CurCall_1 = CurCall_1 + 1;
  return (float80)BITS_I2F(CalculatedFPS);
}

/* TimerSetFPSDelay @ 0x0807b0d0, 24 bytes
 *
 * Sets how many calls TimerGetFPS waits between measurements (when >= 0) and
 * resets the shown value to -1.0.
 *
 * Parameters:
 *   calls        int
 *
 * Called by: _mangled_main
 *
 * Elecbyte file: src/lib/time-lib.c
 */
void TimerSetFPSDelay(int calls)

{
  if (-1 < calls) {
    FPSUpdateTicks = calls;
  }
  CalculatedFPS = -0x40800000;
  return;
}

/* TimerSyncReset @ 0x0807b0f0, 21 bytes
 *
 * Clears the frame sync accumulator and the count of due frames.
 *
 * Called by: FrameSkipReset, FrameSkipUpdate, GameInputUpdate,
 *            TimerSetSyncFPS
 *
 * Elecbyte file: src/lib/time-lib.c
 */
void TimerSyncReset(void)

{
  SyncCur = 0;
  SyncLast = 0;
  return;
}

/* TimerSetSyncFPS @ 0x0807b110, 60 bytes
 *
 * Sets the target frame rate for TimerWaitSync/TimerIsSync: SyncRate =
 * TicksPerSecond / fps in 16.16 fixed point. The game runs at 60 frames per
 * second, scaled by GameSpeed.
 *
 * Parameters:
 *   fps          int
 *
 * Calls: TimerSyncReset
 * Called by: ArcadeWinScreen, CharacterSelectScreen, ContinueScreenLoop,
 *            GamePlay, KeyConfigScreen, MainLoop, ModeSelect,
 *            OptionsScreen, PlayCutscene, SurvivalResultsScreen,
 *            VersusScreen, _mangled_main
 *
 * Elecbyte file: src/lib/time-lib.c
 */
void TimerSetSyncFPS(int fps)

{
  if (0 < fps) {
    TimerFPS = fps;
    SyncRate = (TicksPerSecond << 0x10) / fps;
    InSync = 1;
    TimerSyncReset();
    return;
  }
  return;
}

/* TimerGetSync @ 0x0807b150, 14 bytes
 *
 * Returns the number of frames due (SyncCur). FrameSkipUpdate uses it to
 * decide whether to skip drawing.
 *
 * Called by: FrameSkipUpdate
 *
 * Elecbyte file: src/lib/time-lib.c
 */
bool TimerGetSync(void)

{
  return InSync == 0;
}

/* TimerWaitSync @ 0x0807b160, 56 bytes
 *
 * Busy-waits until at least one frame is due, then consumes one. InSync is
 * set when the engine is on time (exactly one frame was due) and cleared
 * when it is behind.
 *
 * Called by: CharacterSelectScreenDraw, ContinueScreenLoop, GameLoop,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, PlayCutscene,
 *            VersusScreen
 *
 * Elecbyte file: src/lib/time-lib.c
 */
void TimerWaitSync(void)

{
  do {
  } while (SyncCur < 1);
  if (SyncCur == 1) {
    SyncCur = 0;
    InSync = 1;
    return;
  }
  SyncCur = SyncCur + -1;
  InSync = 0;
  return;
}

/* TimerIsSync @ 0x0807b1a0, 75 bytes
 *
 * Non-blocking TimerWaitSync: returns 0 when no frame is due, otherwise
 * consumes one, sets InSync as TimerWaitSync does and returns 1. Not called
 * in this build.
 *
 * Elecbyte file: src/lib/time-lib.c
 */
uint32_t TimerIsSync(void)

{
  bool b1;
  
  if (SyncCur < 1) {
    return 0;
  }
  b1 = SyncCur == 1;
  SyncCur = SyncCur + -1;
  InSync = (int)b1;
  return 1;
}

/* TimerSkipSync @ 0x0807b1f0, 1 bytes
 *
 * Empty; frame skipping needs no timer action in this build.
 *
 * Called by: FrameSkipUpdate
 *
 * Elecbyte file: src/lib/time-lib.c
 */
void TimerSkipSync(void)

{
  return;
}

