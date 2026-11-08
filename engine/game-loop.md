# Game loop and timing

## Clock (VERIFIED, `time-lib.c`)

- `TimerInit(180)` (called in `GameInit` with 0xb4) installs an Allegro
  timer interrupt, `TimerHandler`, at 180 Hz
  (`install_int_ex(TimerHandler, BPS_TO_TIMER(180))`; the code computes
  `0x1234dd / 180`, Allegro's PIT tick unit).
- `TimerHandler` increments `Ticks` and, when `SyncRate > 0`, adds 0x10000
  to `SyncLast`. Each time `SyncLast >= SyncRate` it subtracts `SyncRate`
  and increments `SyncCur`: 16.16 fixed-point frame accumulation.
- `TimerSetSyncFPS(60)` (in `main`) sets the logic rate. `TimerWaitSync()`
  spins until `SyncCur >= 1`, consumes one frame, and sets `InSync` when no
  backlog remains. `TimerIsSync()` is the non-blocking form.
- `GameSpeed` in mugen.cfg (`[Options] GameSpeed`, `[Config] GameSpeed=60`)
  and Ctrl-S "run as fast as possible" change the sync rate
  (`TimerChangeSpeed`) (STRONGLY INFERRED from names and keys).

## Frame skipping (`display.c`)

`FrameSkipUpdate`/`FrameSkipReset`: auto-frameskip by default. Ctrl-F
cycles auto / none / skip 1 / skip 2 (readme). When the logic falls
behind (`InSync == 0`), drawing is skipped and logic keeps running.

## Per-frame work

See [../architecture/execution-flow.md](../architecture/execution-flow.md):
`TimerWaitSync` -> `GameUpdate` (logic) -> drawing (if not skipped) ->
`DrawToScreen` -> `FrameSkipUpdate`. Music streaming (`MP3Poll` ->
`poll_amp`, `CDAPoll`) is polled from the loops.

## Debug hot keys (readme section IV, VERIFIED as documentation)

Pause, ScrollLock frame-step, Esc, F1-F5, Shift-F4 (reload), F12
(screenshot), Ctrl-C/D/I/L/S/V, Ctrl-1..4 (AI), Ctrl-Alt-1..4, Space.
`AllowDebugKeys`/`AllowDebugMode` in mugen.cfg gate them.
