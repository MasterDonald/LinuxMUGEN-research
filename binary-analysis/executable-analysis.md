# Executable analysis

## 1. The shipped file (packed)

| Property | Value | Evidence |
|---|---|---|
| Size | 1,695,688 bytes | stat |
| SHA-256 | c6edaee6b4ce6736f20cfbe9ce1e6e1104d30b6aaf124a52a1d60950be1fe4fc | sha256sum |
| Format | ELF32 LSB EXEC, i386, OS/ABI byte 0x00 with `Linux` written into the e_ident padding (UPX marker), no section headers, 2 PT_LOAD | `readelf -h -l` |
| Entry | 0x08048080 (UPX stub) | ELF header |
| Packer | UPX 1.20, format `linux.exec/i386`; packed 5,121,061 -> 1,695,688 bytes (33.11%) | `$Id: UPX 1.20 ...$`, `$Info: This file is packed with the UPX executable packer ...$`; `upx -l` |

All VERIFIED.

### UPX 1.20 stub behaviour (VERIFIED, strace: experiments T2)

1. `open("/proc/<pid>/exe")` and read the packed blocks (the file reads itself).
2. Create `/tmp/upx` + 11 random characters with `O_CREAT|O_EXCL`, mode 0700,
   and `ftruncate` it to 5,121,061 bytes.
3. Decompress 10 blocks of 512 KiB each (NRV) into the file.
4. Reopen it read-only, `unlink` it, then
   `execve("/proc/<pid>/fd/3", argv, envp)`.

So the packed program needs a **writable `/tmp` that is not mounted
`noexec`** (exec goes through the fd, which counts as `/tmp` for `noexec`),
plus a mounted `/proc`.

### Unpacking

`upx -d` (UPX 5.2.0) restores the original ELF without errors (VERIFIED).
The result is a complete static executable with section headers and symbols,
which shows the restore is lossless and not a memory dump.

## 2. The unpacked executable

| Property | Value | Class |
|---|---|---|
| Size / SHA-256 | 5,121,061 bytes / d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1 | VERIFIED |
| Type | ELF32 EXEC i386, statically linked, `for GNU/Linux 2.2.5`, **not stripped** | VERIFIED (`file`, `.note.ABI-tag`) |
| Entry | 0x08048100 (`_start`, glibc csu) | VERIFIED |
| Program headers | LOAD R-X 0x08048000 (0x23e0cc), LOAD RW- 0x082870e0 (filesz 0x1f15c, memsz 0x50824), NOTE | VERIFIED |

### Sections (VERIFIED, `readelf -S`)

| # | Name | Address | Size | Notes |
|---|---|---|---|---|
| 1 | .init | 080480d4 | 0x18 | |
| 2 | .text | 08048100 | 0x1d9400 (1.94 MB) | all code |
| 3 | .fini | 08221500 | 0x1e | |
| 4 | .rodata | 08221520 | 0x64b44 | Elecbyte's jump tables at the start; merged string sections (all objects' literals) at the end, from ~0x08277000 |
| 5-7 | __libc_subfreeres, __libc_atexit, __libc_subinit | 08286064.. | small | glibc static link-sets |
| 8 | .data | 082870e0 | 0x1e37c | Elecbyte data 0x082870f0-0x08288060 |
| 9 | .eh_frame | 082a545c | 0xd70 | |
| 10-11 | .ctors/.dtors | 082a61cc | | |
| 12 | .got | 082a61f0 | 0x4c | |
| 13 | .dynamic | 082a623c | 0x30 | present but unused (static glibc supporting dlopen) |
| 15 | .bss | 082a6280 | 0x31684 | Elecbyte statics 0x082a6298-0x082a6c00; Elecbyte COMMON block 0x082c0680-0x082ca680 |
| 16-17 | .stab/.stabstr | - | 1.54 MB / 0.72 MB | STABS for glibc 2.2.4 and libgcc only |
| 18 | .comment | - | 0xb658 | 778 identical GCC idents |
| 20 | .note | - | 0x3cc8 | 01.01 version notes |
| 22-23 | .symtab/.strtab | - | 10,563 symbols | 5,750 FUNC, 2,143 OBJECT, 1,869 NOTYPE, 778 FILE |

## 3. Toolchain

| Indicator | Value | Class |
|---|---|---|
| `.comment` (all 778 objects) | `GCC: (GNU) 2.96 20000731 (Mandrake Linux 8.1 2.96-0.62mdk)` | VERIFIED |
| Object start markers | `gcc2_compiled.` label per object (GCC 2.x) | VERIFIED |
| glibc | 2.2.4 (STABS paths `/usr/src/RPM/BUILD/glibc-2.2.4/...`) | VERIFIED |
| libgcc | STABS path `/home/gb/rpm/BUILD/gcc-2.95.2/obj-i586-mandrake-linux-gnu/gcc/` | VERIFIED (string); meaning: libgcc came from a Mandrake gcc 2.95.2 RPM build tree (HYPOTHESIS) |
| Readme claim "compiled with gcc 2.95.2 and linked with Allegro 4.0.0" | contradicted for this build: GCC 2.96 and Allegro 3.9.37 | VERIFIED contradiction |
| Optimisation | -O2-style code: no frame pointer in most functions, tail calls as `jmp`, 16-byte call alignment with dummy pushes, `pop reg` stack cleanup | VERIFIED (disassembly) |
| Debug info | none for Elecbyte, Allegro, JGMOD, LibAmp, X11 (no STABS SO entries for them) | VERIFIED |

### x87 conversions (VERIFIED at 0x80495ee)

GCC 2.96 converts float to int with `fnstcw; movb $0xc,hi(cw); fldcw;
fistp; fldcw(restore)`. That sets RC=11 (truncate), which is C's `(int)`
cast. Ghidra prints this as `ROUND()` plus `in_FPUControlWord` noise; the
reconstruction defines `ROUND(x)` as truncation.

## 4. Composition (functions and code bytes by component)

See also Python Script. Source-file counts for glibc are lower
bounds, because its assembler objects have no `gcc2_compiled.` marker.

| Component | source files | functions | code bytes |
|---|---|---|---|
| Elecbyte (engine library + game) | 58 | 1284 | 566,158 |
| glibc 2.2.4 | 71 | 1209 | 494,523 |
| libX11 (XFree86) | 201 | 1719 | 422,574 |
| Allegro 3.9.37 (CVS), Unix | 72 | 1143 | 343,560 |
| LibAmp (Allegro MP3 port) | 13 | 70 | 50,525 |
| JGMOD | 11 | 128 | 43,168 |
| libXext / XShm / Xxf86dga / Xxf86vm | 5 | 88 | 26,862 |
| zlib 1.1.3 | 9 | 30 | 12,898 |
| minizip 0.15 (inside Elecbyte range) | 1 | 23 | 4,592 |
| linuxthreads | 8 | 22 | 4,083 |
| libcda | 1 | 22 | 1,901 |
| libdl | 4 | 5 | 257 |
| crt (init) | 3 | 7 | 0 |
| **total** | | 5750 | 1,971,101 |

## 5. Elecbyte code

- Address range 0x08048200-0x080d5e70: 58 Elecbyte source files plus
  minizip `unzip.c`; 1,307 functions (VERIFIED, `artifacts/funcmap.tsv`).
- Two layers, judging by naming and link order (STRONGLY INFERRED):
  - **Elecbyte engine library** (`*-lib.c`, `ebcommon.c`, `vbuf.c`,
    `txtparse.c`, `spr16*.c`, `gui-lib.c`, `lthreads.c`, ...): generic 2D,
    input, sound, text-parser and sprite code, with prefixes `V_`, `W_`,
    `TP`, `Snd`, `Sprite`, `Anim`, `BG`, `KB`, `Pad`, `UInp`, `EB_GUI`, `EBT_`.
  - **MUGEN game** (`afterimg.c` .. `precache.c`): players, states,
    expression evaluator, menus, match, stage, AI, precaching.
- Full per-file function list:
  [../architecture/module-index.md](../architecture/module-index.md).

## 6. Runtime initialization (static glibc)

`_start` -> `__libc_start_main` -> `.init`/ctors -> **`main` (Allegro
`umain.c`)** -> `_mangled_main` (MUGEN's `main` renamed by Allegro's
`END_OF_MAIN()`) (VERIFIED: `main` at 0x08113aa0, 36 bytes, in `umain.c`;
`_mangled_main` at 0x0809c470 in `main.c`). See
[../runtime/startup.md](../runtime/startup.md).
