#!/bin/sh
# Start mugen-rebuilt with sound through PulseAudio or PipeWire.
#
# The engine (Allegro 3.9.37) only has an OSS sound driver (/dev/dsp).
# PulseAudio's OSS wrapper library, libpulsedsp.so, provides /dev/dsp to the
# program. The game is a 32-bit program, so it needs the 32-bit build of
# that library. `padsp` asks the loader for /usr/$LIB/pulseaudio/libpulsedsp.so,
# and on x86-64 systems the 32-bit copy is usually not installed. The loader
# then prints
#   ERROR: ld.so: object '/usr/$LIB/pulseaudio/libpulsedsp.so' from LD_PRELOAD
#   cannot be preloaded (cannot open shared object file): ignored.
# and the game runs without sound. This script looks for the 32-bit library
# and, if it is missing, says which package provides it.
#
# Usage: run-with-sound.sh [game arguments]     (from the game directory)
#   MUGEN_BIN=path          the executable (default: ./mugen-rebuilt)
#   MUGEN_PULSEDSP=file     a 32-bit libpulsedsp.so in a non-standard place
#   MUGEN_PULSE_LIBDIR=dir  extra directory with its 32-bit libraries (libpulse.so.0, ...)
#   MUGEN_OSS_MIXER=1       let the game drive the volume of the output device
#                           (the original's behaviour, see below)
#
# Volume: Allegro's set_volume() writes the OSS PCM mixer with the game's
# MasterWavVolume (mugen.cfg, default 255 = 100%) at start-up, on the title
# screen and at every match. libpulsedsp maps that to the volume of the
# whole output device, so the desktop volume jumps to 100% and cannot be
# lowered while the game runs. This script disables libpulsedsp's mixer
# emulation (PADSP_NO_MIXER=1, the same as `padsp -M`). Allegro then falls
# back to scaling MasterWavVolume in software, and the system and per-app
# volume controls work normally. With MUGEN_OSS_MIXER=1 the volume of the
# *default* output device is changed, even if PULSE_SINK points elsewhere.
#
# Debian 12's own padsp script is broken: $LIB is escaped twice in its
# LD_PRELOAD line, so the loader looks for a path containing a literal
# "\$LIB" and preloads nothing. This script does not use padsp.
BIN=${MUGEN_BIN:-./mugen-rebuilt}
[ -x "$BIN" ] || { echo "run-with-sound.sh: $BIN not found; run this from the game directory or set MUGEN_BIN" >&2; exit 2; }

is_elf32() {   # ELF class byte (offset 4) = 1 for 32-bit
    [ -f "$1" ] && [ "$(od -An -tu1 -j4 -N1 "$1" 2>/dev/null | tr -d ' ')" = 1 ]
}

DSP=""
for f in "$MUGEN_PULSEDSP" \
         /usr/lib32/pulseaudio/libpulsedsp.so \
         /usr/lib/i386-linux-gnu/pulseaudio/libpulsedsp.so \
         /usr/lib/pulseaudio/libpulsedsp.so; do
    if [ -n "$f" ] && is_elf32 "$f"; then DSP=$f; break; fi
done

if [ -z "$DSP" ]; then
    cat >&2 <<'EOF'
run-with-sound.sh: no 32-bit libpulsedsp.so found, so the game would have no sound.
Install the 32-bit PulseAudio client library for your distribution (it also
works with PipeWire's PulseAudio server):
  Arch Linux, CachyOS, Manjaro (multilib repository):  sudo pacman -S lib32-libpulse
  Fedora:                                              sudo dnf install pulseaudio-libs.i686
  openSUSE:                                            sudo zypper install pulseaudio-utils-32bit
  Debian/Ubuntu (x86-64): the 32-bit library is in pulseaudio-utils:i386, which
    cannot be installed next to the 64-bit pulseaudio-utils. Install
    libpulse0:i386, then unpack the library from the i386 package without
    installing it:
      apt-get download pulseaudio-utils:i386 && dpkg-deb -x pulseaudio-utils_*_i386.deb pa32
    and run with MUGEN_PULSEDSP=$PWD/pa32/usr/lib/i386-linux-gnu/pulseaudio/libpulsedsp.so
To start the game without sound instead, run the executable directly.
EOF
    exit 1
fi

# A library outside the system paths needs its companions (libpulsecommon-*.so
# lives next to libpulsedsp.so; libpulse.so.0 etc. in MUGEN_PULSE_LIBDIR).
if [ "$DSP" = "$MUGEN_PULSEDSP" ]; then
    export LD_LIBRARY_PATH="$(dirname "$DSP")${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
fi
[ -n "$MUGEN_PULSE_LIBDIR" ] && export LD_LIBRARY_PATH="$MUGEN_PULSE_LIBDIR${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}"
[ "$MUGEN_OSS_MIXER" = 1 ] || export PADSP_NO_MIXER=1
export LD_PRELOAD="$DSP${LD_PRELOAD:+ $LD_PRELOAD}"
exec "$BIN" "$@"
