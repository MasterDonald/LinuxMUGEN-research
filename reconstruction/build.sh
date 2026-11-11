#!/bin/sh
# Build the reconstructed M.U.G.E.N beta 2002.04.14 (Linux) and the 2002
# libraries it was linked with, as a 32-bit executable.
#
#   ./build.sh [--online] [OUTDIR]          (default OUTDIR: ./build)
#
#   offline (default): uses the source archives in ./downloads
#   --online:          downloads them first (needs curl and network access)
#   Both modes check every archive against downloads/SHA256SUMS and stop on a
#   mismatch.
#
# Result: OUTDIR/mugen-rebuilt. Nothing is installed system-wide; everything
# is built inside OUTDIR (libraries in OUTDIR/libs32, objects in OUTDIR/game).
#
# Needs: gcc with -m32 (32-bit glibc development files), make, patch, tar,
# sha256sum, and 32-bit development files of libX11, libXext, libXxf86vm and
# zlib. Run it on the oldest distribution the binary should run on: a build
# on Debian 11 (glibc 2.31) needs glibc >= 2.29 at run time. See README.md.
set -e
KIT=$(cd "$(dirname "$0")" && pwd)
ONLINE=0
[ "$1" = "--online" ] && { ONLINE=1; shift; }
OUT=${1:-$KIT/build}; mkdir -p "$OUT"; OUT=$(cd "$OUT" && pwd)
# offline: the bundled archives; online: download into OUTDIR/downloads
# (the bundled copies are never overwritten). DL=... overrides either.
if [ -z "$DL" ]; then [ $ONLINE = 1 ] && DL=$OUT/downloads || DL=$KIT/downloads; fi
SRC=$OUT/thirdparty-src; LIB=$OUT/libs32; TP=$KIT/thirdparty
mkdir -p "$DL" "$SRC" "$LIB/lib" "$LIB/include"

# ---- sources ---------------------------------------------------------------
# name|url  (hashes in downloads/SHA256SUMS)
URLS="allegro-3.9.37.tar.gz|https://sourceforge.net/projects/alleg/files/allegro/3.9.37/allegro-3.9.37.tar.gz/download
jgmod-master.tar.gz|https://github.com/ArtificialRaccoon/JGMOD/archive/refs/heads/main.tar.gz
libcda-master.tar.gz|https://github.com/wangp/libcda/archive/refs/heads/master.tar.gz
amp-0.7.6.tgz|https://ftp.netbsd.org/pub/pkgsrc/distfiles/amp-0.7.6.tgz"
if [ $ONLINE = 1 ]; then
  if command -v curl >/dev/null; then GET="curl -fsSL -m 300 -o"
  elif command -v wget >/dev/null; then GET="wget -q -T 300 -O"
  else echo "--online needs curl or wget" >&2; exit 1; fi
  for line in $URLS; do
    name=${line%%|*}; url=${line#*|}
    echo "downloading $name"
    $GET "$DL/$name.part" "$url" || { echo "download failed: $url" >&2; exit 1; }
    mv "$DL/$name.part" "$DL/$name"
  done
fi
( cd "$DL" && sha256sum -c "$KIT/downloads/SHA256SUMS" ) || {
  echo "source archives missing or different from downloads/SHA256SUMS." >&2
  echo "(The JGMOD and libcda archives are branch snapshots; if upstream changed, use the offline copies.)" >&2
  exit 1; }

# 32-bit X11 libraries: /usr/lib/i386-linux-gnu (Debian/Ubuntu), /usr/lib32 (Arch), /usr/lib (i386 systems)
if [ -z "$XLIBDIR" ]; then
  for d in /usr/lib/i386-linux-gnu /usr/lib32 /usr/lib; do
    [ -e "$d/libX11.so" ] && { XLIBDIR=$d; break; }
  done
fi
# -fno-aggressive-loop-optimizations: amp indexes past inner array bounds on
# purpose (misc2.c); modern GCC would otherwise turn such loops into infinite loops.
CC32="gcc -m32 -std=gnu89 -fcommon -fno-strict-aliasing -fno-aggressive-loop-optimizations -fno-pie -fno-stack-protector"
SHIM=$TP/allegro-3.9.37/glibc-c23-shim.h
LOG=$OUT/build.log; : > "$LOG"
step() { echo "== $*"; echo "== $*" >> "$LOG"; }

# ---- Allegro 3.9.37 (exact version in the original binary) -----------------
step "Allegro 3.9.37"
rm -rf "$SRC/allegro-3.9.37" && tar xzf "$DL/allegro-3.9.37.tar.gz" -C "$SRC"
cd "$SRC/allegro-3.9.37"
patch -p1 -s < "$TP/allegro-3.9.37/modern-toolchain.patch"
sh fix.sh unix >/dev/null
touch stamp-h.in          # keep the shipped include/allegro/alunixac.hin (see PROVENANCE.md)
CC="$CC32" LDFLAGS="-m32" ./configure --prefix="$LIB" \
   --x-includes=/usr/include --x-libraries="$XLIBDIR" \
   --enable-static --disable-shared --disable-modules --disable-svgalib \
   --disable-alsadigi --disable-alsamidi --disable-esddigi >> "$LOG" 2>&1
make -j"$(nproc)" CFLAGS="-O2 -fomit-frame-pointer -w -include $SHIM" lib/unix/liballeg.a >> "$LOG" 2>&1
cp lib/unix/liballeg.a "$LIB/lib/"
rm -rf "$LIB/include/allegro" && cp -r include/allegro include/allegro.h "$LIB/include/"
INC="-include $SHIM -I$LIB/include"

# ---- JGMOD 0.99 -------------------------------------------------------------
step "JGMOD 0.99"
rm -rf "$SRC/JGMOD-main" "$LIB/build/jgmod" && tar xzf "$DL/jgmod-master.tar.gz" -C "$SRC"
B=$LIB/build/jgmod; mkdir -p "$B"
for f in mod player player2 player3 player4 load_it load_jgm load_mod load_s3m load_xm file_io; do
  $CC32 -O2 -w $INC -c "$SRC/JGMOD-main/src/$f.c" -o "$B/$f.o"
done
rm -f "$LIB/lib/libjgmod.a"; ar rcs "$LIB/lib/libjgmod.a" "$B"/*.o
cp "$SRC/JGMOD-main/src/jgmod.h" "$LIB/include/"

# ---- libcda 0.5.1 + three entry points recovered from the binary ------------
step "libcda 0.5.1"
rm -rf "$SRC/libcda-master" "$LIB/build/libcda" && tar xzf "$DL/libcda-master.tar.gz" -C "$SRC"
B=$LIB/build/libcda; mkdir -p "$B"
$CC32 -O2 -w -c "$SRC/libcda-master/linux.c" -o "$B/linux.o"
$CC32 -O2 -w -I"$SRC/libcda-master" -c "$TP/libcda/libcda-mugen-additions.c" -o "$B/additions.o"
rm -f "$LIB/lib/libcda.a"; ar rcs "$LIB/lib/libcda.a" "$B"/*.o
cp "$SRC/libcda-master/libcda.h" "$LIB/include/"

# ---- LibAmp = amp 0.7.6 + patch + reconstructed Allegro glue ----------------
step "LibAmp (amp 0.7.6 + reconstruction)"
rm -rf "$SRC/amp-0.7.6" "$SRC/libamp-build" "$LIB/build/libamp"
tar xzf "$DL/amp-0.7.6.tgz" -C "$SRC" && mv "$SRC/amp-0.7.6" "$SRC/libamp-build"
cd "$SRC/libamp-build"
patch -p1 -s < "$TP/libamp/amp-0.7.6-libamp.patch"
cp "$TP/libamp/config.h" .
B=$LIB/build/libamp; mkdir -p "$B"
for f in getbits getdata huffman layer2 layer3 misc2 position transform formats util dump; do
  $CC32 -O2 -w $INC -I. -c "$f.c" -o "$B/$f.o"
done
for f in audiolib audioalg; do
  $CC32 -O2 -w $INC -I. -c "$TP/libamp/$f.c" -o "$B/$f.o"
done
rm -f "$LIB/lib/libamp.a"; ar rcs "$LIB/lib/libamp.a" "$B"/*.o
cp "$TP/libamp/libamp.h" "$LIB/include/"

# ---- the game ---------------------------------------------------------------
step "M.U.G.E.N 2002.04.14 (reconstructed source)"
rm -rf "$OUT/game" && mkdir -p "$OUT/game"
cp -r "$KIT/src" "$KIT/include" "$KIT/data" "$KIT/compat" "$KIT/thirdparty" "$KIT/Makefile" "$OUT/game/"
cd "$OUT/game"
make objects >> "$LOG" 2>&1
grep -q "compiled 59 files, 0 pending" "$LOG" || { tail -20 "$LOG"; exit 1; }
make link LIBS32="$LIB" >> "$LOG" 2>&1 || { tail -20 "$LOG"; exit 1; }
cp mugen-rebuilt "$OUT/"
cp "$KIT/run-with-sound.sh" "$OUT/"
echo "built $OUT/mugen-rebuilt"
echo "  $(gcc --version | head -1); $(ldd --version 2>&1 | head -1)"
echo "  copy mugen-rebuilt and run-with-sound.sh into a copy of the game directory, then:"
echo "    ./run-with-sound.sh     (sound; needs the 32-bit libpulsedsp.so, see README.md)"
echo "    ./mugen-rebuilt         (no sound)"
