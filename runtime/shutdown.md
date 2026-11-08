# Shutdown

`_mangled_main` ends with `EB_GUIDeInit(); GameDeInit(mode);`. `GameDeInit`
(init.c, 0x08099350), VERIFIED from the reconstructed code:

1. `G_SetMode(-1, 80, 25, 8)`: back to text mode (console).
2. Prints the version banner and load-time statistics to stdout:
   "M.U.G.E.N test ver 2002.04.14 (c)2002 Elecbyte", "BG load time",
   "Player load time", "Total load time", "Pal groups in background".
3. Frees players and caches (`PlayerCacheClear`, `CharInfoFree`,
   `FreeSelectScreenMatrix`), fight data (`GameFreeFightData`), motif
   (`GameUnloadSystem`).
4. `chdir` back to the starting directory (saved in `g`).
5. `GameVarDeInit`, `UInpDeInit`, `PadDeInit`, `KBDeInit`,
   `SwitchCallbacksDeInit`, `TimerDeInit`, `G_DeInit`, `CDADeInit`,
   `MP3DeInit`, `SndDeInit`, `ElecDeInit` (-> `allegro_exit`).

Error path: `ErrorExit` / `ErrorExitM` show the text collected in
`ErrorMessage` (built with `strcat`, e.g. "\nTXTPARSE error opening ...")
and exit (VERIFIED names and strings). Allegro's signal handlers restore
the display on SIGSEGV, SIGINT and the others listed in strace.

Files written during a session: `data/mugen.cfg` (options), `mugen?.pcx`
(F12), the `-log` file, AI learning files (if used).
