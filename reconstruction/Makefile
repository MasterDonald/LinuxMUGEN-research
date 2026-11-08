# Build the reconstructed LINUXMUGEN 2002.04.14 sources (32-bit).
#
#   make objects   compile every file that currently compiles, plus data
#   make check     report compile errors per file (does not stop)
#   make link      link against Allegro 3.9.37 + JGMOD + LibAmp + libcda + zlib
#                  (32-bit builds from build.sh; see README.md)
#
# Optimisation (session 5): -O2 for speed, with the options that keep the
# decompiled code's meaning: -fexcess-precision=standard (every assignment
# and cast rounds to its type, as the -O0 build stored them), wrapping
# integer and pointer arithmetic, no deletion of null-pointer checks or of
# stores through provably null pointers (Ghidra writes integer[pointer]).
# Files listed in O0_SRC are built with -O0 instead (none at present;
# see README.md). -fpermissive downgrades GCC >= 14 errors about int/pointer
# conversions that decompiled code relies on.
CC      ?= gcc
BASEFLAGS = -m32 -std=gnu99 -fpermissive -w -g -fno-pie -fno-strict-aliasing -fwrapv -fno-aggressive-loop-optimizations
OPTFLAGS  = -O2 -fexcess-precision=standard -fno-strict-overflow -fno-delete-null-pointer-checks -fno-isolate-erroneous-paths-dereference
CFLAGS    ?= $(BASEFLAGS) $(OPTFLAGS)
CFLAGS_O0 ?= $(BASEFLAGS) -O0
O0_SRC    :=
CPPFLAGS = -Iinclude
LDFLAGS ?= -m32 -no-pie
# Libraries built by build.sh (Allegro 3.9.37, JGMOD, libcda,
# LibAmp); system 32-bit zlib, X11, pthread, libm.
LIBS32  ?= build/libs32
LIBS    ?= -L$(LIBS32)/lib -lamp -ljgmod -lcda -lalleg -lz -lm -lpthread -lXxf86vm -lXext -lX11 -ldl

SRC  := $(wildcard src/elecbyte-lib/*.c src/game/*.c src/thirdparty/minizip/*.c)
OBJ  := $(patsubst src/%.c,build/obj/%.o,$(SRC)) build/obj/mugen_data.o build/obj/compat/allegro_inline.o

.PHONY: objects check link clean
objects:
	@ok=0; bad=0; for f in $(SRC); do o=build/obj/$${f#src/}; o=$${o%.c}.o; mkdir -p $$(dirname $$o); \
	  fl="$(CFLAGS)"; case " $(O0_SRC) " in *" $$f "*) fl="$(CFLAGS_O0)";; esac; \
	  if $(CC) $$fl $(CPPFLAGS) -c $$f -o $$o 2>/dev/null; then ok=$$((ok+1)); \
	  else bad=$$((bad+1)); echo "  does not compile yet: $$f"; fi; done; \
	  echo "compiled $$ok files, $$bad pending"
	@mkdir -p build/obj && $(CC) -m32 -c data/mugen_data.S -o build/obj/mugen_data.o && echo "assembled data/mugen_data.S"

check:
	@for f in $(SRC); do n=$$($(CC) $(CFLAGS) $(CPPFLAGS) -fsyntax-only $$f 2>&1 | grep -c 'error:'); \
	  [ $$n -ne 0 ] && echo "$$n errors: $$f"; done; true

build/obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# hand-written compatibility code, compiled against the real Allegro header
build/obj/compat/%.o: compat/%.c
	@mkdir -p $(dir $@)
	$(CC) -m32 -std=gnu89 -O2 -w -fno-pie -include thirdparty/allegro-3.9.37/glibc-c23-shim.h -I$(LIBS32)/include -c $< -o $@

build/obj/mugen_data.o: data/mugen_data.S
	@mkdir -p build/obj
	$(CC) -m32 -c $< -o $@

link: $(OBJ)
	$(CC) $(LDFLAGS) -o mugen-rebuilt $(OBJ) $(LIBS)

clean:
	rm -rf build/obj mugen-rebuilt
