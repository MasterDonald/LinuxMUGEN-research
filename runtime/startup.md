# Startup

Observed with strace (experiments T2/T3) and read in the reconstructed
code. Order as executed.

## 1. Before MUGEN code runs (VERIFIED)

1. UPX 1.20 stub: self-read, decompress to `/tmp/upxXXXXXXXXXXX`,
   `execve("/proc/<pid>/fd/3")`.
2. glibc 2.2.4 static start-up: `uname`, uid/gid queries,
   `setrlimit(RLIMIT_STACK, 2044 KiB)` (linuxthreads), RT signal handlers
   (SIGRTMIN..+2), `_sysctl` (ENOSYS on modern kernels) then
   `/proc/sys/kernel/version`.
3. Allegro `main` (`umain.c`) -> `_mangled_main`.

## 2. `_mangled_main` -> `ParseCmdLine`

Options (from `PrintHelp`, VERIFIED): `-h`/`-?`, `-log <file>`,
`-r <motif>`, `-p<n> <name>`, `-p<n>.ai 1`, `-p<n>.color <c>`,
`-p<n>.life <l>`, `-p<n>.power <p>`, `-rounds <n>`, `-s <stage>`,
`-nojoy`, `-nomusic`, `-nosound`. Positional: `player1 player2`.
**Undocumented options** also parsed: `-ailevel`, `-rubric`,
`-speedtest`, `-stresstest` (VERIFIED: strings compared in `ParseCmdLine`;
their effects are not traced).

## 3. `GameInit(opts, &mode)` (VERIFIED: reconstructed code)

| Step | Calls | Output on stdout |
|---|---|---|
| Library init, game block | `ElecInit`; allocate `g` | "Can't allocate game variables." on failure |
| Configuration | `GameConfigRead("data/mugen.cfg")` (including `expires`) | |
| Timer | `TimerInit(180)` | |
| Keyboard | `KBInit`, `KBBufferChange(2)`, `KBRepeatSet(0,0)`, LEDs, `GameDefKeyInit`, `UInpInit` | "Initializing keyboard." |
| Sound | unless `-nosound`/`Sound=0`: `SndInit(wav, midi, ...)`; if that fails, retry WAV only, then MIDI only; `MP3Init` | "Initializing sound...", "sound is disabled" |
| Graphics | `G_Init`, `G_SetRenderMode(0)`, `G_SetMode(depth, width, height, ...)`; if that fails it **asks on the terminal** "Switch to 640x480x16bits? (y/n)" and retries `G_SetMode(0,640,480,16)`; `G_SetRGBtoBGR(1)`, `G_SetBlitMode` | "Initializing graphics." |
| Callbacks | `SwitchCallbacksInit` (display switching, focus) | |
| Game variables | `GameVarInit` (below) | |
| Mode | `*mode = 1` when no player name was given (string at opts+0x40 empty) | |

### Inside `GameVarInit` (VERIFIED)

- Writes and deletes `_mugen__.tmp`; success sets "directory writable"
  (`g[0x801] = 1`). If it fails, the info screen is shown.
- Expiry: `time()` + **`gmtime()`** (UTC) date compared with
  `MUGENEXPDATE` by `MDYDateCmp`; if later, `g[0x74e6] = 1` (expired).
- Allocates the 320x240x16 back buffer (`V_AllocDepth(0x140,0xf0,0x10)`).

### Expiry date override (VERIFIED, documented only)

`GameConfigRead` reads `expires = M,D,Y,checksum` (format `%i,%i,%i,%x`).
If the checksum equals a 16-bit value computed from the given date and
the build date constants, the three values replace `MUGENEXPDATE_*`.
This was presumably Elecbyte's way to extend a beta without a new build
(HYPOTHESIS). No values were generated in this project. The flag only
affects the info screen and banner anyway.

## 4. Resource loading after init

See [resource-loading.md](resource-loading.md): fonts, motif, fight data,
select.def, characters (precache), then the logo storyboard.
