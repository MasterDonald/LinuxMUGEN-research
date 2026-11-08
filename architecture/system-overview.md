# System overview

```
+--------------------------------------------------------------------+
|  mugen  (static i386 ELF, UPX 1.20 packed)                         |
|                                                                    |
|  +---------------------------+   +------------------------------+  |
|  | MUGEN game (30 files)     |   | Elecbyte engine lib (28)     |  |
|  | main/init/system/menus    |-->| vbuf (V_/W_ 2D), spr16*      |  |
|  | charsel/match/gameloop    |   | spr-lib/spr-read (SFF)       |  |
|  | player p-* , state*,      |   | anim-lib (AIR), bg-lib       |  |
|  | st-ctrl/st-trig/st-exprn, |   | snd-lib (SND, MIDI, MOD,     |  |
|  | arith (expressions)       |   |   MP3, CDA), txtparse (TP)   |  |
|  | helper/projctl/explod,    |   | kbll/pad/input-lb (input)    |  |
|  | afterimg, pal, sound, bgm |   | time-lib, font-lib, gui-lib  |  |
|  | p-ai (AI + learning)      |   | cutscene (storyboards)       |  |
|  | precache (worker thread)  |   | ebcommon (MF streams, misc)  |  |
|  +---------------------------+   | lthreads (pthread wrappers)  |  |
|                                  +------------------------------+  |
|           |                                 |                      |
|  +--------v---------------------------------v-------------------+  |
|  | Allegro 3.9.37 Unix | JGMOD | LibAmp | libcda | zlib+minizip |  |
|  +--------------------------------------------------------------+  |
|  | XFree86 Xlib/Xext/DGA/VidMode | linuxthreads | glibc 2.2.4   |  |
+--+--------------------------------------------------------------+--+
          |  X11 socket     |  /dev/dsp, /dev/sequencer, /dev/js*, /dev/cdrom
          v                 v
       X server          Linux 2.2/2.4 kernel
```

- **Data-driven engine.** Almost everything that defines the game is in
  text files (motif `system.def`, `fight.def`, `select.def`; character
  DEF/CNS/CMD/AIR; stage DEF; storyboards) plus SFF/SND/FNT/ACT resources
  (VERIFIED, [../formats/](../formats/)).
- **One process, a few threads.** The main thread runs menus and matches.
  Allegro's background manager uses SIGALRM and a thread. MUGEN starts a
  precache worker thread (`PrecacheWorkerThread`, created through
  `EBT_ThreadCreate` -> `pthread_create`) (VERIFIED names and calls;
  strace shows the linuxthreads manager clone).
- **Fixed internal resolution** 320x240, 16-bit colour, fixed logic rate
  (`TimerSetSyncFPS(60)` in `main`; 180 Hz timer) (VERIFIED).
- **Global state** sits mainly in one large block pointed to by `g`
  (`.data` 0x08287a74), more than 133 KB, accessed by offset (VERIFIED).

Details: [engine-architecture.md](engine-architecture.md),
[execution-flow.md](execution-flow.md),
[subsystem-analysis.md](subsystem-analysis.md),
[module-index.md](module-index.md) (all 1,307 functions by file).
