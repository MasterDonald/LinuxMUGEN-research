/*
 * mugen_types.h -- structure types recovered from the binary.
 * Each matches the definition committed to the Ghidra database by
 * Ghidra Script. Field names are descriptive reconstructions, not
 * Elecbyte's original names.
 */
#pragma once
#include "ghidra_compat.h"

/* 160-bit palette-group flag set. Evidence: PalGrpOrFlag/XorFlag/AndFlagZero/
 * FlagEqual loop over 5 dwords; PalGrpMakeFlag* and Or/Xor return it through a
 * hidden pointer ('ret $4'); others take it by value (5 stack slots). */
typedef struct PalGrpFlag {
  uint w[5];
} PalGrpFlag;

/* Command-line options block, 0x32c bytes. Evidence: ParseCmdLine zeroes 0xcb
 * dwords; _mangled_main copies 0xcb dwords to pass it by value to GameInit.
 * Offset 0x2ec holds a storyboard file name (tested in _mangled_main). */
typedef struct MugenCmdLine {
  int  mode;
  byte rest[0x32c - 4];
} MugenCmdLine;
_Static_assert(sizeof(PalGrpFlag) == 20, "PalGrpFlag size");
_Static_assert(sizeof(MugenCmdLine) == 0x32c, "MugenCmdLine size");
