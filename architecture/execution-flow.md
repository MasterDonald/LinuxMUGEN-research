# Execution flow

## Process level (VERIFIED: strace T2/T3 and code)

```
UPX stub (0x08048080)
  -> decompress to /tmp/upxXXXXXXXXXXX -> execve(/proc/self/fd/3)
_start (0x08048100) -> __libc_start_main -> ctors
main (Allegro umain.c, 0x08113aa0) -> _mangled_main (0x0809c470)
```

## `_mangled_main` (hand-verified, reconstruction/overrides/0x0809c470._mangled_main.c)

```
mode = 0
ParseCmdLine(&opts, argc, argv)          zero opts, parse -r -s -p<n> -rounds ...
GameInit(opts, &mode)                    install_allegro, config, video, input,
                                         sound, timers; mode = 1 if no character
                                         given on the command line
clear buffers; W_Define(0,0,V_Width-1,V_Height-1)
TimerSetFPSDelay(30); TimerSetTicks(0); TimerSetSyncFPS(60)
if opts.storyboard (offset 0x2ec) given:
    PlayCutscene(storyboard)             play one storyboard and quit
else:
    install_mouse; EB_GUIInit; debug window "Debug"
    PlayCutscene(logo storyboard)
    CharInfoInit() or ErrorExit
    if mode == 1: InitSelectScreenMatrix(motif select), FindCharacters()
    else:         QuickVSSetup(&opts)
    MainLoop(mode)
EB_GUIDeInit; GameDeInit(mode); return 0
```

## `MainLoop` (main.c, 0x0809cb60): from the decompiled control flow

```
IntroScreen()                     intro storyboard / attract
loop:
  GameResetPersistVars()
  ModeSelect()                    title menu (menus.c); expired banner drawn here
  -> demo:   DemoFightSetup()
  -> modes:  CharacterSelectScreen(...)   charsel.c
             ArcadeListBuild(), PrecacheRequest..(), PrecacheStart()
             per match:  [intro storyboard] VersusScreen() GamePlay()
             arcade/survival bookkeeping: ArcadeListGetCurrent/EnemiesLeft,
             ContinueScreen, ending storyboard
  -> exit:   leave loop
PrecacheRequestCancel(); PrecacheFinish()
```

## `GamePlay` -> `GameLoop` (gameloop.c, 0x0808fdc0)

Per frame (from the calls in `GameLoop`, VERIFIED as call sequence;
ordering details in the code):

```
TimerWaitSync()                         wait for the next 1/60 s logic tick
GameInputUpdate()                       sample keyboard/pad buffers (called from GameLoop)
GameUpdate()                            players (state machines,
                                        physics, hit detection), helpers,
                                        projectiles, explods, camera, stage BG
                                        controllers, round state
if not frame-skipped:
   BGArrayDrawLayer(back) ; shadows (PlayerDrawShadow, ProjArrayDrawShadow)
   afterimages ; PlayerDrawAnim / ExplodArrayDraw / ProjArrayDraw (by priority)
   BGArrayDrawLayer(front) ; GameBarsDraw (fight.def lifebars) ; GameRoundDraw
   ComboDisplay ; debug: PlayerDrawClsn, ShowDebugInfo ; TrainingMenuDraw
   PalFXUpdate / MasterPalProcessChanges (palette effects)
   VRetrace (if enabled) ; DrawToScreen
FrameSkipUpdate()
hot keys: pause, F1-F5, Ctrl-keys (readme section IV)
```

Shutdown: [../runtime/shutdown.md](../runtime/shutdown.md).
