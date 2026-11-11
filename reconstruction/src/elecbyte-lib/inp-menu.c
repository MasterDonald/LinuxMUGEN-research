/*
 * inp-menu.c -- menu input
 * Converts the keyboard state into menu input bits with auto-repeat for the
 * screens outside the fight.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/inp-menu.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* KBIMenuGetKey @ 0x08053d30, 418 bytes
 *
 * Reads menu input for the screens outside the fight (mode select, character
 * select, options, continue). For each of the `count` input configurations
 * in the table, it converts the keyboard state of that player (KBToUInp)
 * into the engine's input bits. It keeps per-player auto-repeat state so a
 * held direction repeats in menus. Returns a pointer to the combined result
 * in its static buffer (filled through the output argument).
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Calls: KBToUInp
 * Called by: CharacterSelectScreen, ContinueScreenLoop, ModeSelect,
 *            OptionsScreen, PlayCutscene, VersusScreen
 *
 * Elecbyte file: src/lib/inp-menu.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x70 bytes,
 *       12 variables), because their address is taken.
 */
uint32_t * KBIMenuGetKey(uint32_t *arg1,int arg2,int arg3,int arg4)

{
  uint32_t uinp;
  int i2;
  uint32_t u3;
  uint32_t *pu4;
  uint32_t *pu5;
  int i6;
  unsigned char frame[0x70] __attribute__((aligned(16)));
#define stk_64 (*(uint32_t *)(frame + 0xc))
#define stk_60 (*(uint32_t *)(frame + 0x10))
#define stk_5c (*(uint32_t (*)[4])(frame + 0x14))
#define stk_4c (*(int *)(frame + 0x24))
#define stk_48 (*(int *)(frame + 0x28))
#define stk_44 (*(int *)(frame + 0x2c))
#define stk_40 (*(int *)(frame + 0x30))
#define stk_3c (*(int *)(frame + 0x34))
#define stk_38 (*(int *)(frame + 0x38))
#define stk_34 (*(int *)(frame + 0x3c))
#define stk_30 (*(int *)(frame + 0x40))
#define stk_2c (*(int *)(frame + 0x44))
  
  u3 = 0;
  stk_64 = 0;
  stk_60 = 0;
  uinp = stk_60;
  if (0 < arg4) {
    do {
      pu4 = *(uint32_t **)(arg3 + u3 * 4);
      pu5 = stk_5c;
      for (i2 = 0xd; i2 != 0; i2 = i2 + -1) {
        *pu5 = *pu4;
        pu4 = pu4 + 1;
        pu5 = pu5 + 1;
      }
      i2 = 0;
      i6 = 0xc;
      do {
        uinp = KBToUInp(*(uint32_t *)((int)stk_5c + i2));
        *(uint32_t *)((int)stk_5c + i2) = uinp;
        i2 = i2 + 4;
        i6 = i6 + -1;
      } while (-1 < i6);
      if (arg2 == stk_5c[1]) {
        stk_64 = stk_64 | 1;
      }
      else if (arg2 == stk_5c[2]) {
        stk_64 = stk_64 | 2;
      }
      else if (arg2 == stk_5c[3]) {
        stk_64 = stk_64 | 4;
      }
      else if (arg2 == stk_4c) {
        stk_64 = stk_64 | 8;
      }
      else if (arg2 == stk_48) {
        stk_64 = stk_64 | 0x10;
      }
      else if (arg2 == stk_44) {
        stk_64 = stk_64 | 0x20;
      }
      else if (arg2 == stk_40) {
        stk_64 = stk_64 | 0x40;
      }
      else if (arg2 == stk_3c) {
        stk_64 = stk_64 | 0x80;
      }
      else if (arg2 == stk_38) {
        stk_64 = stk_64 | 0x100;
      }
      else if (arg2 == stk_34) {
        stk_64 = stk_64 | 0x200;
      }
      else if (arg2 == stk_30) {
        stk_64 = stk_64 | 0x400;
      }
      else if (arg2 == stk_2c) {
        stk_64 = stk_64 | 0x800;
      }
      uinp = u3;
    } while ((stk_64 == 0) && (u3 = u3 + 1, uinp = stk_60, (int)u3 < arg4));
  }
  stk_60 = uinp;
  arg1[1] = stk_60;
  *arg1 = stk_64;
  return arg1;
}
#undef stk_64
#undef stk_60
#undef stk_5c
#undef stk_4c
#undef stk_48
#undef stk_44
#undef stk_40
#undef stk_3c
#undef stk_38
#undef stk_34
#undef stk_30
#undef stk_2c

