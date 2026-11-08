# Input system

## Keyboard (VERIFIED, `kbll-lib.c`)

- `KBInit` installs Allegro's keyboard and sets
  `keyboard_lowlevel_callback = KBBufferRawHook`. Every key event lands in
  MUGEN's ring buffer `KBBuffer` and the flag arrays `keyflag` and
  `shiftflags`.
- Key codes are translated from Allegro key codes to **DOS set-1
  scancodes** with `KBAllegRemapMap` (`KBInitAllegRemap`; e.g. Allegro 28
  `KEY_1` -> 0x02). mugen.cfg `[P1 Keys]`/`[P2 Keys]` therefore store DOS
  scancodes (`Jump = 200` = 0xC8, extended Up).
- Key repeat: `KBRepeatSet(0,0)` -> `set_keyboard_rate(0,0)`. Under X,
  repeat cannot be disabled by the program (readme; use `xset r off`).
- LEDs: `KBLEDSet`, `KBLEDLockSet` (`set_leds`).

## Joysticks (`pad-lib.c`, VERIFIED names)

`PadInit` -> `install_joystick`; polled with `poll_joystick`; mapped
through `[P1 Joystick]`/`[P2 Joystick]` button numbers;
`P1.Joystick.type`. `-nojoy` disables joysticks. PlayStation pads were
supported on DOS through a parallel-port converter (readme credits
DirectPad Pro); on Linux any `/dev/js*` device works.

## Unified input (`input-lb.c`, `inp-kbi.c`, `inp-menu.c`, `p-input.c`)

`UInp*` merges keyboard and pad into per-player bit flags (`uinpflag`,
`padflag`), with buffers for menus (`KBIMenuGetKey`). `PlayerKBUpdate`
feeds the player's command buffer. `cmd-dtct.c` matches the CMD command
definitions against the buffer (`command.time`, `command.buffer.time`).

## Polling rate

Input is sampled once per logic frame (60 Hz) from the buffers filled by
the asynchronous keyboard callback (VERIFIED: `GameLoop` calls
`GameInputUpdate` each iteration; STRONGLY INFERRED that this is the only
per-frame sampling point during matches).
