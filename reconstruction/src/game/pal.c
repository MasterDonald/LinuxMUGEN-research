/*
 * pal.c -- palette groups and PalFX
 * Palette groups (all palettes of one player and its helpers, explods and
 * projectiles) and the PalFX/AllPalFX effects applied to them.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/pal.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* PalGrpAdd @ 0x080b8460, 428 bytes
 *
 * Adds a palette to a palette group (or extends the group's flag) so that
 * PalFX applied to the group reach it. Palette groups let one PalFX recolour
 * a player, its helpers, explods and projectiles together. Returns nonzero
 * on success.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *   arg6         int
 *
 * Calls: PalGrpFlagEqual, ecalloc, PalGrpMakeFlag
 * C library: realloc, memset
 * Called by: PalGrpAddSpr
 *
 * Elecbyte file: src/mugen/pal.c
 * Note: decompiler flag: stack slots read outside the declared parameters
 *       (entry_stack variables)
 * Note: rewrote 1 PalGrpFlag by-value loads
 * Note: PalGrpMakeFlag result written into the argument area: given explicit
 *       temporaries pgf_ffffffc8
 */
uint32_t PalGrpAdd(int arg1,int arg2,int arg3,int arg4,int arg5,int arg6)

{
  PalGrpFlag pgf_ffffffc8;
  int *pi1;
  uint32_t *pu2;
  PalGrpFlag a;
  PalGrpFlag a_00;
  PalGrpFlag b;
  int i3;
  void *mem;
  uint32_t u5;
  int i6;
  int i7;
  int i2;
  int *pi9;
  uint32_t entry_stack_ffffffc8;
  uint32_t entry_stack_ffffffcc;
  uint32_t entry_stack_ffffffd0;
  void *entry_stack_ffffffd4;
  uint32_t entry_stack_ffffffd8;
  
  pu2 = (uint32_t *)g[0x413e];
  i6 = pu2[2];
  if (arg1 == 0) {
L_080b8531:
    u5 = 0;
  }
  else {
    i2 = 0;
    i3 = i6;
    if (i6 < 1) {
      mem = (void *)*pu2;
    }
    else {
      mem = (void *)*pu2;
      i7 = 0;
      do {
        pi1 = (int *)(i7 + (int)mem);
        if (arg1 == *pi1) {
          entry_stack_ffffffd8 = pi1[5];
          entry_stack_ffffffd4 = (void *)pi1[4];
          entry_stack_ffffffd0 = pi1[3];
          entry_stack_ffffffcc = pi1[2];
          entry_stack_ffffffc8 = (*(uint32_t (*) [5])(pi1 + 1))[0];
          a.w[1] = arg3;
          a.w[0] = arg2;
          a.w[2] = arg4;
          a.w[3] = arg5;
          a.w[4] = arg6;
          i3 = PalGrpFlagEqual(a,*(PalGrpFlag *)(pi1 + 1));
          if (i3 != 0) goto L_080b85ff;
          i3 = pu2[2];
          mem = (void *)*pu2;
        }
        i2 = i2 + 1;
        i7 = i7 + 0x18;
      } while (i2 < i3);
    }
    i2 = pu2[1];
    if (i2 <= i3) {
      if (mem == (void *)0x0) {
        mem = (void *)ecalloc(1,i2 * 0x18 + 0x180);
      }
      else {
        mem = realloc((void *)*pu2,i2 * 0x18 + 0x180);
      }
      if (mem == (void *)0x0) goto L_080b8531;
      entry_stack_ffffffd8 = 0;
      entry_stack_ffffffd4 = (void *)((int)mem + pu2[1] * 0x18);
      entry_stack_ffffffd0 = 0x80b854f;
      memset(entry_stack_ffffffd4,0,0x180);
      *pu2 = mem;
      pu2[1] = pu2[1] + 0x10;
    }
    pi1 = (int *)((int)mem + i6 * 0x18);
    pi9 = pi1;
    for (i6 = 6; i6 != 0; i6 = i6 + -1) {
      *pi9 = 0;
      pi9 = pi9 + 1;
    }
    *pi1 = arg1;
    pi1[1] = arg2;
    pi1[2] = arg3;
    pi1[3] = arg4;
    pi1[4] = arg5;
    pi1[5] = arg6;
    pu2[2] = pu2[2] + 1;
    PalGrpMakeFlag(&pgf_ffffffc8,0x100,0);
    a_00.w[1] = arg3;
    a_00.w[0] = arg2;
    a_00.w[2] = arg4;
    a_00.w[3] = arg5;
    a_00.w[4] = arg6;
    b.w[1] = pgf_ffffffc8.w[1];
    b.w[0] = pgf_ffffffc8.w[0];
    b.w[2] = pgf_ffffffc8.w[2];
    b.w[3] = (uint32_t)pgf_ffffffc8.w[3];
    b.w[4] = pgf_ffffffc8.w[4];
    i6 = PalGrpFlagEqual(a_00,b);
    if (i6 != 0) {
      g[0x81ca] = g[0x81ca] + 1;
    }
L_080b85ff:
    u5 = 1;
  }
  return u5;
}

/* PalGrpRemove @ 0x080b8610, 177 bytes
 *
 * Removes the palettes of group flag `f` from the palette group table (when
 * a helper is destroyed).
 *
 * Parameters:
 *   f            PalGrpFlag
 *
 * Calls: PalGrpFlagEqual
 * C library: memmove
 * Called by: HelperDestroy, HelperMake
 *
 * Elecbyte file: src/mugen/pal.c
 * Note: rewrote 1 PalGrpFlag by-value loads
 */
void PalGrpRemove(PalGrpFlag f)

{
  int *pi1;
  int i2;
  int i3;
  int i4;
  
  i4 = 0;
  pi1 = (int *)g[0x413e];
  if (0 < pi1[2]) {
    i3 = 0;
    do {
      i2 = PalGrpFlagEqual(f,*(PalGrpFlag *)(i3 + *pi1 + 4));
      if (i2 == 0) {
        i3 = i3 + 0x18;
        i4 = i4 + 1;
      }
      else {
        i2 = pi1[2];
        if (0 < (i2 - i4) + -1) {
          memmove((void *)(i3 + *pi1),(void *)(i3 + *pi1 + 0x18),
                  (i2 - i4) * 0x18 - 0x18);
          i2 = pi1[2];
        }
        pi1[2] = i2 + -1;
      }
    } while (i4 < pi1[2]);
  }
  return;
}

/* PalGrpAddSpr @ 0x080b86d0, 88 bytes
 *
 * Adds every palette of a sprite array to the palette group with flag `f`.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *   arg6         int
 *
 * Calls: ArrayScanFirst, PalGrpAdd, ArrayScanNext
 * Called by: HelperMake, PalGrpBuildFight
 *
 * Elecbyte file: src/mugen/pal.c
 */
uint32_t PalGrpAddSpr(int arg1,int arg2,int arg3,int arg4,int arg5,int arg6)

{
  int item;
  uint32_t entry_ECX;
  
  if ((arg1 != 0) && (*(int *)(arg1 + 8) != 0)) {
    item = ArrayScanFirst(*(int *)(arg1 + 8));
    while (item != 0) {
      PalGrpAdd(item,arg2,arg3,arg4,arg5,arg6);
      item = ArrayScanNext(*(int *)(arg1 + 8));
    }
  }
  return entry_ECX;
}

/* PalGrpBuildFight @ 0x080b8730, 546 bytes
 *
 * Builds the palette group table for a fight: one group per player (with its
 * helpers), plus the system groups for the fight screen and stage.
 *
 * Calls: PalGrpClear, ecalloc, PalGrpFlagIsNonZero, PalGrpAddSpr,
 *        PalGrpMakeFlag
 * Called by: GameLoadAndActivateTeam
 *
 * Elecbyte file: src/mugen/pal.c
 * Note: decompiler flag: stack slots read outside the declared parameters
 *       (entry_stack variables)
 * Note: rewrote 1 PalGrpFlag by-value loads
 * Note: PalGrpMakeFlag result written into the argument area: given explicit
 *       temporaries pgf_ffffffc8
 */
void PalGrpBuildFight(void)

{
  PalGrpFlag pgf_ffffffc8;
  int *pi1;
  int mem;
  int i3;
  int *pi4;
  int i2;
  uint32_t entry_stack_ffffffc8;
  uint32_t entry_stack_ffffffcc;
  uint32_t u6;
  uint32_t u7;
  uint32_t u8;
  
  PalGrpClear();
  g[0x81ca] = 0;
  u8 = 0x18;
  u7 = 0x40;
  u6 = 0x80b8756;
  mem = ecalloc(0x40,0x18);
  pi4 = g;
  pi1 = (int *)g[0x413e];
  *pi1 = mem;
  if (mem != 0) {
    pi1[1] = 0x40;
    mem = 1;
    if (0 < pi4[0x7395]) {
      i2 = 0x1cf64;
      do {
        i3 = *(int *)(i2 + 4 + (int)pi4);
        if (i3 != 0) {
          u7 = *(uint32_t *)(i3 + 0x25d8);
          u6 = *(uint32_t *)(i3 + 0x25d4);
          entry_stack_ffffffcc = *(uint32_t *)(i3 + 0x25d0);
          entry_stack_ffffffc8 = *(uint32_t *)(i3 + 0x25cc);
          i3 = PalGrpFlagIsNonZero(*(PalGrpFlag *)(i3 + 0x25c8));
          pi4 = g;
          if (i3 != 0) {
            i3 = *(int *)((int)g + i2 + 4);
            u8 = *(uint32_t *)(i3 + 0x25d8);
            u7 = *(uint32_t *)(i3 + 0x25d4);
            u6 = *(uint32_t *)(i3 + 0x25d0);
            entry_stack_ffffffcc = *(uint32_t *)(i3 + 0x25cc);
            entry_stack_ffffffc8 = *(uint32_t *)(i3 + 0x25c8);
            PalGrpAddSpr(*(int *)(*(int *)((int)g + i2 + 4) + 0x13ac),entry_stack_ffffffc8,
                         entry_stack_ffffffcc,u6,u7,u8);
            pi4 = g;
          }
        }
        mem = mem + 1;
        i2 = i2 + 4;
      } while (mem <= pi4[0x7395]);
    }
    mem = 0;
    PalGrpMakeFlag(&pgf_ffffffc8,0x100,0);
    PalGrpAddSpr(*(int *)(g[0x6ed4] + 0x28),pgf_ffffffc8.w[0],pgf_ffffffc8.w[1],pgf_ffffffc8.w[2],pgf_ffffffc8.w[3],pgf_ffffffc8.w[4]);
    PalGrpMakeFlag(&pgf_ffffffc8,0x200,0);
    PalGrpAddSpr(g[0x4149],pgf_ffffffc8.w[0],pgf_ffffffc8.w[1],pgf_ffffffc8.w[2],pgf_ffffffc8.w[3],pgf_ffffffc8.w[4]);
    PalGrpMakeFlag(&pgf_ffffffc8,0x400,0);
    PalGrpAddSpr(g[0x4147],pgf_ffffffc8.w[0],pgf_ffffffc8.w[1],pgf_ffffffc8.w[2],pgf_ffffffc8.w[3],pgf_ffffffc8.w[4]);
    do {
      i2 = 0;
      do {
        i3 = i2 + mem * 4;
        i2 = i2 + 1;
        i3 = g[i3 + 0x52b5];
        PalGrpMakeFlag(&pgf_ffffffc8,0x200,0);
        PalGrpAddSpr(i3,pgf_ffffffc8.w[0],pgf_ffffffc8.w[1],pgf_ffffffc8.w[2],pgf_ffffffc8.w[3],pgf_ffffffc8.w[4]);
      } while (i2 < 4);
      mem = mem + 1;
    } while (mem < 2);
    i2 = 9;
    mem = 0x10520;
    do {
      if (*(int *)((int)g + mem + 0xc) != 0) {
        PalGrpMakeFlag(&pgf_ffffffc8,0x800,0);
        PalGrpAddSpr(*(int *)(*(int *)((int)g + mem + 0xc) + 0x818),pgf_ffffffc8.w[0],pgf_ffffffc8.w[1],pgf_ffffffc8.w[2],pgf_ffffffc8.w[3],pgf_ffffffc8.w[4]);
      }
      mem = mem + 4;
      i2 = i2 + -1;
    } while (-1 < i2);
  }
  return;
}

/* PalGrpClear @ 0x080b8960, 113 bytes
 *
 * Empties the palette group table and resets every palette's effects.
 *
 * Calls: PalGrpResetPalette
 * C library: free
 * Called by: CharacterSelectScreen, GameLoadAndActivateTeam, GamePlay,
 *            GameReloadStage, ModeSelect, PalGrpBuildFight
 *
 * Elecbyte file: src/mugen/pal.c
 */
uint32_t * PalGrpClear(void)

{
  uint32_t *pu1;
  int *pi2;
  
  pi2 = g;
  if (*(int *)g[0x413e] != 0) {
    PalGrpResetPalette();
    free(*(void **)g[0x413e]);
    pi2 = g;
    pu1 = (uint32_t *)g[0x413e];
    *pu1 = 0;
    pu1[2] = 0;
    pu1[1] = 0;
  }
  pu1 = (uint32_t *)pi2[0x413e];
  *pu1 = 0;
  pu1[1] = 0;
  pu1[2] = 0;
  return pu1;
}

/* PalGrpResetPalette @ 0x080b89e0, 53 bytes
 *
 * Resets the effects of every palette in the group table (EBPalReset).
 *
 * Calls: EBPalReset
 * Called by: ArcadeWinScreen, ContinueScreenLoop, GameLoop, GamePlay,
 *            GameRoundReset, PalGrpClear, SurvivalResultsScreen
 *
 * Elecbyte file: src/mugen/pal.c
 */
void PalGrpResetPalette(void)

{
  int *pi1;
  int *pi2;
  int i2;
  int i4;
  
  i2 = 0;
  pi2 = (int *)g[0x413e];
  if (0 < pi2[2]) {
    i4 = 0;
    do {
      i2 = i2 + 1;
      pi1 = (int *)(*pi2 + i4);
      i4 = i4 + 0x18;
      EBPalReset(*pi1);
    } while (i2 < pi2[2]);
  }
  return;
}

/* PalGrpSetAdd @ 0x080b8a20, 159 bytes
 *
 * Applies a colour addition to every palette whose group flag intersects `f`
 * (EBPalAdd).
 *
 * Parameters:
 *   f            PalGrpFlag
 *   r            int
 *   g_local      int
 *   b            int
 *
 * Calls: PalGrpAndFlagZero, EBPalAdd
 * Called by: PalFXUpdate
 *
 * Elecbyte file: src/mugen/pal.c
 * Note: rewrote 1 PalGrpFlag by-value loads
 * Note: renamed locals shadowing globals: g
 */
void PalGrpSetAdd(PalGrpFlag f,int r,int g_local,int b)

{
  int *pi1;
  int i2;
  int i3;
  int i4;
  int i5;
  
  pi1 = (int *)g[0x413e];
  if ((((r != 0) || (g_local != 0)) || (b != 0)) && (i5 = 0, 0 < pi1[2])) {
    i4 = 0;
    do {
      i2 = *pi1;
      i3 = PalGrpAndFlagZero(*(PalGrpFlag *)((int *)(i4 + i2) + 1),f);
      if (i3 != 0) {
        EBPalAdd(*(int *)(i4 + i2),r,g_local,b);
      }
      i5 = i5 + 1;
      i4 = i4 + 0x18;
    } while (i5 < pi1[2]);
  }
  return;
}

/* PalGrpSetMul @ 0x080b8ac0, 172 bytes
 *
 * Applies colour multipliers to every palette whose group flag intersects
 * `f` (EBPalMul).
 *
 * Parameters:
 *   f            PalGrpFlag
 *   r            int
 *   g_local      int
 *   b            int
 *
 * Calls: PalGrpAndFlagZero, EBPalMul
 * Called by: ContinueScreenLoop, GameLoop, GameSurvivalResultsUpdate,
 *            GameWinScreenUpdate, PalFXUpdate
 *
 * Elecbyte file: src/mugen/pal.c
 * Note: rewrote 1 PalGrpFlag by-value loads
 * Note: renamed locals shadowing globals: g
 */
void PalGrpSetMul(PalGrpFlag f,int r,int g_local,int b)

{
  int *pi1;
  int i2;
  int i3;
  int i4;
  int i5;
  
  pi1 = (int *)g[0x413e];
  if ((((r != 0x100) || (g_local != 0x100)) || (b != 0x100)) && (0 < pi1[2])) {
    i4 = 0;
    i5 = 0;
    do {
      i2 = *pi1;
      i3 = PalGrpAndFlagZero(*(PalGrpFlag *)((int *)(i4 + i2) + 1),f);
      if (i3 != 0) {
        EBPalMul(*(int *)(i4 + i2),r,g_local,b);
      }
      i5 = i5 + 1;
      i4 = i4 + 0x18;
    } while (i5 < pi1[2]);
  }
  return;
}

/* PalGrpSetInvertAll @ 0x080b8b70, 135 bytes
 *
 * Toggles colour inversion of every palette whose group flag intersects `f`.
 *
 * Parameters:
 *   f            PalGrpFlag
 *   invert       int
 *
 * Calls: PalGrpAndFlagZero, EBPalInvertAll
 * Called by: PalFXUpdate
 *
 * Elecbyte file: src/mugen/pal.c
 * Note: rewrote 1 PalGrpFlag by-value loads
 */
void PalGrpSetInvertAll(PalGrpFlag f,int invert)

{
  int *pi1;
  int i2;
  int i3;
  int i4;
  int i5;
  
  pi1 = (int *)g[0x413e];
  if ((invert != 0) && (i5 = 0, 0 < pi1[2])) {
    i4 = 0;
    do {
      i2 = *pi1;
      i3 = PalGrpAndFlagZero(*(PalGrpFlag *)((int *)(i4 + i2) + 1),f);
      if (i3 != 0) {
        EBPalInvertAll(*(int *)(i4 + i2),invert);
      }
      i5 = i5 + 1;
      i4 = i4 + 0x18;
    } while (i5 < pi1[2]);
  }
  return;
}

/* PalGrpSetColorBal @ 0x080b8c00, 137 bytes
 *
 * Applies a colour factor to every palette whose group flag intersects `f`.
 *
 * Parameters:
 *   f            PalGrpFlag
 *   colorbal     int
 *
 * Calls: PalGrpAndFlagZero, EBPalColorBal
 * Called by: PalFXUpdate
 *
 * Elecbyte file: src/mugen/pal.c
 * Note: rewrote 1 PalGrpFlag by-value loads
 */
void PalGrpSetColorBal(PalGrpFlag f,int colorbal)

{
  int *pi1;
  int i2;
  int i3;
  int i4;
  int i5;
  
  pi1 = (int *)g[0x413e];
  if ((colorbal != 0x100) && (i5 = 0, 0 < pi1[2])) {
    i4 = 0;
    do {
      i2 = *pi1;
      i3 = PalGrpAndFlagZero(*(PalGrpFlag *)((int *)(i4 + i2) + 1),f);
      if (i3 != 0) {
        EBPalColorBal(*(int *)(i4 + i2),colorbal);
      }
      i5 = i5 + 1;
      i4 = i4 + 0x18;
    } while (i5 < pi1[2]);
  }
  return;
}

/* PalGrpSetClear @ 0x080b8c90, 128 bytes
 *
 * Resets the effects of every palette whose group flag intersects `f`.
 *
 * Parameters:
 *   f            PalGrpFlag
 *
 * Calls: PalGrpAndFlagZero, EBPalReset
 * Called by: PalFXUpdate
 *
 * Elecbyte file: src/mugen/pal.c
 * Note: rewrote 1 PalGrpFlag by-value loads
 */
void PalGrpSetClear(PalGrpFlag f)

{
  int *pi1;
  int i2;
  int i3;
  int i4;
  int i5;
  
  i5 = 0;
  pi1 = (int *)g[0x413e];
  if (0 < pi1[2]) {
    i4 = 0;
    do {
      i2 = *pi1;
      i3 = PalGrpAndFlagZero(*(PalGrpFlag *)((int *)(i4 + i2) + 1),f);
      if (i3 != 0) {
        EBPalReset(*(int *)(i4 + i2));
      }
      i5 = i5 + 1;
      i4 = i4 + 0x18;
    } while (i5 < pi1[2]);
  }
  return;
}

/* PalGrpMakeFlag @ 0x080b8d10, 100 bytes
 *
 * Builds a 160-bit palette group flag (5 words) with bit set `group` in word
 * `word`.
 *
 * Parameters:
 *   ret_storage  PalGrpFlag *
 *   group        uint32_t
 *   unused       int
 *
 * Called by: ContinueScreenLoop, GameLoadAndCreateChars, GameLoadStage,
 *            GameLoop, GameSurvivalResultsUpdate, GameWinScreenUpdate,
 *            PalGrpAdd, PalGrpBuildFight, PlayerSCtrlApplyElem
 *
 * Elecbyte file: src/mugen/pal.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x30 bytes, 1
 *       variables), because their address is taken.
 */
PalGrpFlag * PalGrpMakeFlag(PalGrpFlag *ret_storage,uint32_t group,int unused)

{

  unsigned char frame[0x30] __attribute__((aligned(16)));
#define stk_2c (*(uint32_t (*)[10])(frame + 0x4))
  
  stk_2c[0] = 0;
  stk_2c[1] = 0;
  stk_2c[2] = 0;
  stk_2c[3] = 0;
  stk_2c[4] = 0;
  stk_2c[unused] = stk_2c[unused] | group;
  ret_storage->w[0] = stk_2c[0];
  ret_storage->w[1] = stk_2c[1];
  ret_storage->w[2] = stk_2c[2];
  ret_storage->w[3] = stk_2c[3];
  ret_storage->w[4] = stk_2c[4];
  return ret_storage;
}
#undef stk_2c

/* PalGrpMakeFlagALL @ 0x080b8d80, 69 bytes
 *
 * Builds a palette group flag with every bit set. Not called in this build.
 *
 * Parameters:
 *   ret_storage  PalGrpFlag *
 *
 * Elecbyte file: src/mugen/pal.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x30 bytes, 5
 *       variables), because their address is taken.
 */
PalGrpFlag * PalGrpMakeFlagALL(PalGrpFlag *ret_storage)

{
  uint32_t *pu1;
  int i2;
  unsigned char frame[0x30] __attribute__((aligned(16)));
#define stk_2c (*(uint32_t *)(frame + 0x4))
#define stk_28 (*(uint32_t *)(frame + 0x8))
#define stk_24 (*(uint32_t *)(frame + 0xc))
#define stk_20 (*(uint32_t *)(frame + 0x10))
#define stk_1c (*(uint32_t (*)[7])(frame + 0x14))
  
  i2 = 4;
  pu1 = stk_1c;
  do {
    *pu1 = 0xffffffff;
    pu1 = pu1 + -1;
    i2 = i2 + -1;
  } while (-1 < i2);
  ret_storage->w[0] = stk_2c;
  ret_storage->w[1] = stk_28;
  ret_storage->w[2] = stk_24;
  ret_storage->w[3] = stk_20;
  ret_storage->w[4] = stk_1c[0];
  return ret_storage;
}
#undef stk_2c
#undef stk_28
#undef stk_24
#undef stk_20
#undef stk_1c

/* PalGrpOrFlag @ 0x080b8dd0, 70 bytes
 *
 * Returns a | b of two palette group flags.
 *
 * Parameters:
 *   ret_storage  PalGrpFlag *
 *   a            PalGrpFlag
 *   b            PalGrpFlag
 *
 * Called by: PlayerSCtrlApplyElem
 *
 * Elecbyte file: src/mugen/pal.c
 */
PalGrpFlag * PalGrpOrFlag(PalGrpFlag *ret_storage,PalGrpFlag a,PalGrpFlag b)

{
  uint32_t *pu1;
  int i2;
  int i3;
  
  i3 = 0;
  i2 = 4;
  do {
    pu1 = (uint32_t *)((int)a.w + i3);
    *pu1 = *pu1 | *(uint32_t *)((int)b.w + i3);
    i3 = i3 + 4;
    i2 = i2 + -1;
  } while (-1 < i2);
  ret_storage->w[0] = a.w[0];
  ret_storage->w[1] = a.w[1];
  ret_storage->w[2] = a.w[2];
  ret_storage->w[3] = a.w[3];
  ret_storage->w[4] = a.w[4];
  return ret_storage;
}

/* PalGrpXorFlag @ 0x080b8e20, 70 bytes
 *
 * Returns a ^ b of two palette group flags.
 *
 * Parameters:
 *   ret_storage  PalGrpFlag *
 *   a            PalGrpFlag
 *   b            PalGrpFlag
 *
 * Called by: PlayerSCtrlApplyElem
 *
 * Elecbyte file: src/mugen/pal.c
 */
PalGrpFlag * PalGrpXorFlag(PalGrpFlag *ret_storage,PalGrpFlag a,PalGrpFlag b)

{
  uint32_t *pu1;
  int i2;
  int i3;
  
  i3 = 0;
  i2 = 4;
  do {
    pu1 = (uint32_t *)((int)a.w + i3);
    *pu1 = *pu1 ^ *(uint32_t *)((int)b.w + i3);
    i3 = i3 + 4;
    i2 = i2 + -1;
  } while (-1 < i2);
  ret_storage->w[0] = a.w[0];
  ret_storage->w[1] = a.w[1];
  ret_storage->w[2] = a.w[2];
  ret_storage->w[3] = a.w[3];
  ret_storage->w[4] = a.w[4];
  return ret_storage;
}

/* PalGrpAndFlagZero @ 0x080b8e70, 32 bytes
 *
 * Returns true when two palette group flags have no bit in common.
 *
 * Parameters:
 *   a            PalGrpFlag
 *   b            PalGrpFlag
 *
 * Called by: PalGrpSetAdd, PalGrpSetClear, PalGrpSetColorBal,
 *            PalGrpSetInvertAll, PalGrpSetMul
 *
 * Elecbyte file: src/mugen/pal.c
 */
int PalGrpAndFlagZero(PalGrpFlag a,PalGrpFlag b)

{
  int i2;
  int i22;
  
  i2 = 0;
  i22 = 0;
  do {
    if ((*(uint32_t *)((int)a.w + i22) & *(uint32_t *)((int)b.w + i22)) != 0) {
      return 1;
    }
    i2 = i2 + 1;
    i22 = i22 + 4;
  } while (i2 < 5);
  return 0;
}

/* PalGrpFlagEqual @ 0x080b8e90, 32 bytes
 *
 * Returns true when two palette group flags are equal.
 *
 * Parameters:
 *   a            PalGrpFlag
 *   b            PalGrpFlag
 *
 * Called by: PalGrpAdd, PalGrpRemove
 *
 * Elecbyte file: src/mugen/pal.c
 */
int PalGrpFlagEqual(PalGrpFlag a,PalGrpFlag b)

{
  int i2;
  int i22;
  
  i2 = 0;
  i22 = 0;
  do {
    if (*(int *)((int)a.w + i22) != *(int *)((int)b.w + i22)) {
      return 0;
    }
    i2 = i2 + 1;
    i22 = i22 + 4;
  } while (i2 < 5);
  return 1;
}

/* PalGrpFlagIsNonZero @ 0x080b8eb0, 25 bytes
 *
 * Returns true when a palette group flag has any bit set.
 *
 * Parameters:
 *   a            PalGrpFlag
 *
 * Called by: GameLoop, HelperDestroy, HelperMake, PalGrpBuildFight
 *
 * Elecbyte file: src/mugen/pal.c
 */
int PalGrpFlagIsNonZero(PalGrpFlag a)

{
  int i2;
  
  i2 = 0;
  do {
    if (a.w[i2] != 0) {
      return 1;
    }
    i2 = i2 + 1;
  } while (i2 < 5);
  return 0;
}

/* PalFXReset @ 0x080b8ed0, 56 bytes
 *
 * Stops a PalFX effect record (time 0, neutral values).
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * Called by: GameRoundReset, PalFXUpdate, PlayerReset
 *
 * Elecbyte file: src/mugen/pal.c
 */
void PalFXReset(uint32_t *arg1)

{
  int i1;
  uint32_t *pu2;
  
  pu2 = arg1;
  for (i1 = 0xf; i1 != 0; i1 = i1 + -1) {
    *pu2 = 0;
    pu2 = pu2 + 1;
  }
  arg1[8] = 0x100;
  arg1[7] = 0x100;
  arg1[6] = 0x100;
  arg1[2] = 0x100;
  arg1[0xe] = 1;
  return;
}

/* PalFXUpdate @ 0x080b8f10, 593 bytes
 *
 * Applies a running PalFX effect for one tick to the palette group `f`, or
 * to the master palette for AllPalFX. On start, the old effect is cleared.
 * Each tick it applies "add" plus the "sinadd" term (a sine of the effect
 * clock with the given period), "mul", "invertall" and "color", then counts
 * down the time. When the time runs out, the palettes are reset.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *   arg6         int
 *   arg7         int
 *   arg8         int
 *
 * Calls: PalGrpSetClear, MasterPalReset, PalGrpSetAdd, PalGrpSetMul,
 *        PalGrpSetInvertAll, PalGrpSetColorBal, MasterPalAdd,
 *        MasterPalMul, MasterPalInvertAll, MasterPalColorBal, PalFXReset
 * C library: fsin
 * Called by: GameLoop
 *
 * Elecbyte file: src/mugen/pal.c
 * Note: renamed locals shadowing globals: g
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 4 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void PalFXUpdate(int *arg1,int arg2,int arg3,int arg4,int arg5,int arg6,
                int arg7,int arg8)

{
  float80 f1;
  int i2;
  PalGrpFlag f;
  PalGrpFlag f_00;
  PalGrpFlag f_01;
  PalGrpFlag f_02;
  PalGrpFlag f_03;
  int g_local;
  int b;
  int i3;
  float80 l4;
  
  if (arg1[0xe] != 0) {
    if (arg7 == 0) {
      f.w[1] = arg3;
      f.w[0] = arg2;
      f.w[2] = arg4;
      f.w[3] = arg5;
      f.w[4] = arg6;
      PalGrpSetClear(f);
    }
    else {
      MasterPalReset();
    }
    arg1[0xe] = 0;
  }
  i3 = arg1[1];
  if ((i3 != 0) && (i2 = g[0x750d], g[0x7309] == 0)) {
    if ((*arg1 < i3) || (i3 == -1)) {
      if (i3 != 0) {
        i3 = arg1[3];
        g_local = arg1[4];
        b = arg1[5];
        if (arg1[0xd] != 0) {
          l4 = (float80)((double)3.14159) * ((float80)*arg1 / (float80)arg1[0xd]);
          l4 = (float80)fsin(l4 + l4);
          f1 = (float)l4;
          i3 = (int)X87_FIST32((float80)arg1[9] * f1 + (float80)i3);
          g_local = (int)X87_FIST32((float80)arg1[10] * f1 + (float)g_local);
          b = (int)X87_FIST32((float)b + (float80)arg1[0xb] * f1);
        }
        if (arg7 == 0) {
          f_00.w[1] = arg3;
          f_00.w[0] = arg2;
          f_00.w[2] = arg4;
          f_00.w[3] = arg5;
          f_00.w[4] = arg6;
          PalGrpSetAdd(f_00,i3,g_local,b);
          f_01.w[1] = arg3;
          f_01.w[0] = arg2;
          f_01.w[2] = arg4;
          f_01.w[3] = arg5;
          f_01.w[4] = arg6;
          PalGrpSetMul(f_01,arg1[6],arg1[7],arg1[8]);
          f_02.w[1] = arg3;
          f_02.w[0] = arg2;
          f_02.w[2] = arg4;
          f_02.w[3] = arg5;
          f_02.w[4] = arg6;
          PalGrpSetInvertAll(f_02,arg1[0xc]);
          f_03.w[1] = arg3;
          f_03.w[0] = arg2;
          f_03.w[2] = arg4;
          f_03.w[3] = arg5;
          f_03.w[4] = arg6;
          PalGrpSetColorBal(f_03,arg1[2]);
        }
        else {
          MasterPalAdd(i3,g_local,b);
          MasterPalMul(arg1[6],arg1[7],arg1[8]);
          MasterPalInvertAll(arg1[0xc]);
          MasterPalColorBal(arg1[2]);
        }
        if ((arg8 & (i2 != 0) - 1) != 0) {
          *arg1 = *arg1 + 1;
        }
      }
    }
    else {
      PalFXReset(arg1);
    }
  }
  return;
}

