# Operating-system requirements

| Area | Requirement | Evidence | Class |
|---|---|---|---|
| Kernel ABI | Linux >= 2.2.5, i386 syscalls (`int 0x80`); on x86-64 the kernel needs IA32 emulation (`CONFIG_IA32_EMULATION=y`) | `.note.ABI-tag`; test T2/T3 on Linux 7.3 (CachyOS) | VERIFIED |
| Removed syscalls | `_sysctl` (linuxthreads startup) returns ENOSYS on modern kernels and is handled (falls back to `/proc/sys/kernel/version`) | strace T2 | VERIFIED |
| Threads | linuxthreads (clone + manager thread + RT signals SIGRTMIN..SIGRTMIN+2) | strace: `rt_sigaction(SIGRTMIN..)`, `clone(CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND)`, pipe to manager | VERIFIED |
| Timers | `setitimer(ITIMER_REAL, 10 ms)` + SIGALRM: Allegro's Unix background manager | strace | VERIFIED |
| Signals | SIGABRT, SIGFPE, SIGILL, SIGSEGV, SIGTERM, SIGINT, SIGQUIT caught by Allegro to restore the console/display | strace | VERIFIED |
| `/proc` | needed by the UPX stub (`/proc/<pid>/exe`, `/proc/<pid>/fd/3`) and linuxthreads | strace | VERIFIED |
| `/tmp` | writable and exec-allowed (UPX) | strace | VERIFIED |
| Filesystem case | case-sensitive paths; readme warns about `\` vs `/` and case | readme | VERIFIED (warning) |
| Working directory | must be the game root: relative paths `data/`, `font/`, `chars/`, `stages/` | strace (all opens relative) | VERIFIED |
| Permissions | console graphics and keyboard need access to `/dev/tty*`, `/dev/console`, `/dev/mem`, `/dev/fb0` (root or group membership); X needs none of that | strings; readme "running MUGEN as root may improve video performance" | VERIFIED |
| Environment variables | `DISPLAY`, `XAUTHORITY` (Xlib), `HOME` (Allegro looks for config there), `ALLEGRO_*` (Allegro debugging) | strings `DISPLAY`, `HOME`, `ALLEGRO_TRACE`, `ALLEGRO_ASSERT` | VERIFIED (strings); exact `HOME` use STRONGLY INFERRED |
| Locale | glibc 2.2.4 static locale code; reads `/etc/localtime` | strace | VERIFIED |
