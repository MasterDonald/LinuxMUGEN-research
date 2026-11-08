# LINUXMUGEN-RESEARCH

Reverse-engineering, preservation and source reconstruction of **M.U.G.E.N
beta 2002.04.14 for Linux** ("LINUXMUGEN"), the Linux-era build of Elecbyte's
2D fighting game engine.

The main goal is to make the program **rebuildable on modern Linux**; that
goal is reached (see the status table). The repository holds:

- an evidence-graded technical reconstruction of the original program and
  its runtime environment (the documentation tree below);
- a **reconstructed C source tree** that mirrors the original module
  layout: 59 files and 1,307 functions, with a byte-exact data image,
  that builds into a working executable;
- the 2002 libraries rebuilt from source (with documented patches) and a
  reconstructed LibAmp;
  
## DISCLAIMERS

The following repository was made with Claude Opus 5.5 (under human 
revisions and interventions). Documentation in some areas has been
cut due to sensible data / intermediate environment preparations,
if necessary, it will be updated accordingly. Code is NOT translated
yet, though it is planned to be.

## Status at a glance

| Item | State |
|---|---|
| Identity and version | VERIFIED: beta **2002.04.14** (not 14.02.2002), Elecbyte, embedded date constants |
| Packing | VERIFIED: UPX 1.20 `linux.exec/i386`; unpacked losslessly with UPX 5.2.0 |
| Toolchain | VERIFIED: GCC 2.96 20000731 (Mandrake Linux 8.1 2.96-0.62mdk), static glibc 2.2.4 |
| Libraries | VERIFIED: Allegro **3.9.37 (CVS)** (the readme says 4.0.0), JGMOD, LibAmp, libcda, zlib 1.1.3, minizip 0.15, XFree86 Xlib/Xext/XShm/DGA/VidMode, linuxthreads |
| Symbols | VERIFIED: not stripped. 778 object files, 5,750 functions; game code has no debug info, glibc has STABS |
| Elecbyte code decompiled | 1,307 / 1,307 functions (100%), all bodies cover their full symbol range |
| Reconstructed source | **59 / 59 files compile and link** into a working 32-bit executable (`mugen-rebuilt`); a standalone rebuild kit (`reconstruction`, offline and online build) reproduces the release binary's code byte for byte |
| Libraries for the rebuild | Built from source: **Allegro 3.9.37** (the exact version), JGMOD 0.99, libcda 0.5.1 (+3 functions recovered from the binary), **LibAmp reconstructed** (amp 0.7.6 + Allegro glue decompiled from the binary) |
| Behaviour vs the original | VERIFIED by frame-locked comparison with scripted input on the host (78 scenarios, 213,595 frames: all game modes, menus, select screens, hot keys, 27 mugen.cfg variants, select.def rosters, motifs, command-line options, storyboards, sound/music/CD/joystick paths, a CNS test character; session 4: 25 parser error messages, 91 controller templates, 8 third-party characters): **game state identical** in every game-mode test with fights (except an X-path harness smoke test), including full matches with all 8 third-party characters (session 5); the release is built with -O2 and runs as fast as the original; 46 tests pixel-identical, the rest differ by at most one 7-pixel scanline (x87, COMPLETENESS-REPORT.md). |
| Distributions tested | VERIFIED, headless (Xvfb), same results everywhere: Debian 11 and 12 (i386), Ubuntu 24.04, Fedora 42, Arch Linux, openSUSE Tumbleweed (x86-64 with 32-bit libraries), and natively on CachyOS (host campaign). Alpine (musl): the static original runs, the glibc build does not |
| Sound | VERIFIED: effects, MP3 (LibAmp), MOD (JGMOD) and MIDI (DIGMID) play through the OSS driver with the 32-bit `libpulsedsp` (PulseAudio in Debian 12; PipeWire 1.6 on the host); CD audio with an emulated drive; the static original cannot use this route |
| Original binary on modern Linux | VERIFIED: runs (X11/XWayland, windowed) on Linux x86-64 with IA32 emulation; no sound without OSS `/dev/dsp` |
| Beta expiry | VERIFIED: expiry date 2002-07-01 in the binary. Expiry only forces the info screen and shows a red banner; nothing else reads the flag |

Full details: [COMPLETENESS-REPORT.md](COMPLETENESS-REPORT.md).

## Legal note

The readme's license (Appendix A) forbids redistributing the executable and
non-exempt files, and its term ended in 2002. The reconstructed source in
`reconstruction/` is derived from the executable. It exists for
preservation and interoperability (running your own copy on current
systems).

## How to read this repository

| Start here | Then |
|---|---|
| [PROJECT-HISTORY.md](PROJECT-HISTORY.md): what LINUXMUGEN is and how this project went | [historical/](historical/): release, provenance, requirements |
| [architecture/system-overview.md](architecture/system-overview.md): the program in one page | [architecture/](architecture/), [engine/](engine/), [runtime/](runtime/) |
| [binary-analysis/executable-analysis.md](binary-analysis/executable-analysis.md) | [binary-analysis/](binary-analysis/), [linux/](linux/) |
| [formats/](formats/): DEF/AIR/CMD/CNS/SFF/SND/ACT/stages | TBA (If more doc is needed) |
| [preservation/original-environment.md](preservation/original-environment.md) |  [preservation/modern-linux.md](preservation/modern-linux.md): run the original or the rebuild today |
| [reconstruction/README.md](reconstruction/README.md): the source tree, libraries and how to build | [RESEARCH-METHODOLOGY.md](RESEARCH-METHODOLOGY.md), TBA (If more doc is needed) |
| [reconstruction/thirdparty/README.md](reconstruction/thirdparty/README.md): library provenance and patches | TBA (If more doc is needed) |
| [engine/struct-map.md](engine/struct-map.md): structure sizes and field offsets (player record, character definition, `g`, controller elements) | TBA (If more doc is needed) |

## Evidence classes

Every technical statement is tagged with one of:

- **VERIFIED**: confirmed directly by the binary, the shipped files, or a
  reproducible test (the offset, symbol or command is given).
- **STRONGLY INFERRED**: supported by several independent pieces of evidence.
- **HYPOTHESIS**: plausible, not established.
- **UNKNOWN**: not enough evidence.

## Artifact identities

| Artifact | SHA-256 |
|---|---|
| `mugen` (as shipped, UPX-packed, 1,695,688 bytes) | `c6edaee6b4ce6736f20cfbe9ce1e6e1104d30b6aaf124a52a1d60950be1fe4fc` |
| `mugen` unpacked with `upx -d` (5,121,061 bytes) | `d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1` |

The full per-file inventory with hashes is in
[artifacts/inventory.tsv](artifacts/inventory.tsv) and
[binary-analysis/binary-formats.md](binary-analysis/binary-formats.md).
