/*
 * pal-lib.c -- palettes and palette effects
 * Palette records with source colours, a 16-bit colour table and effect
 * settings (add, multiply, invert, colour); the master palette applied on
 * top of all palettes; RGB palette helpers and .act loading.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/pal-lib.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* EBPalInit @ 0x080553c0, 160 bytes
 *
 * Initialises a palette record (0x25c bytes): colour count, the
 * 4-byte-per-colour source data (copied or referenced), and two effect
 * settings blocks reset to neutral. Block A (+0xc) is the one effects
 * modify; block B (+0x30) is the one the colour table was last generated
 * with. Flags (+0x54): bit 0 regenerate, bit 2 effects are neutral. The
 * 16-bit colour table starts at +0x5c.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         void *
 *   arg4         int
 *
 * Calls: EBPalSettingsReset, EBPalGenerateFPal
 * C library: calloc, memcpy
 * Called by: AftImgInit, PlayerDefLoadPtr, PlayerDefLoadZip,
 *            SpriteReadPCXRawPtr
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
uint32_t EBPalInit(int *arg1,int arg2,void *arg3,int arg4)

{
  void *dest;
  int i1;
  int *pi2;
  
  pi2 = arg1;
  for (i1 = 0x97; i1 != 0; i1 = i1 + -1) {
    *pi2 = 0;
    pi2 = pi2 + 1;
  }
  EBPalSettingsReset(arg1 + 3);
  EBPalSettingsReset(arg1 + 0xc);
  *arg1 = arg2;
  arg1[0x15] = arg1[0x15] | 4;
  if (arg4 == 0) {
    arg1[2] = (int)arg3;
  }
  else {
    dest = calloc(1,arg2 * 4);
    arg1[2] = (int)dest;
    if (dest == (void *)0x0) {
      return 0;
    }
    memcpy(dest,arg3,arg2 * 4);
    arg1[1] = 1;
  }
  EBPalGenerateFPal(arg1);
  return 1;
}

/* EBPalDeInit @ 0x08055460, 51 bytes
 *
 * Frees a palette's source data if the palette owns it.
 *
 * Parameters:
 *   arg1         int
 *
 * C library: free
 * Called by: AftImgDeInit, SpriteArrayClear, SpriteArrayFree
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void EBPalDeInit(int arg1)

{
  if ((*(int *)(arg1 + 4) != 0) && (*(void **)(arg1 + 8) != (void *)0x0)) {
    free(*(void **)(arg1 + 8));
  }
  *(uint32_t *)(arg1 + 4) = 0;
  *(uint32_t *)(arg1 + 8) = 0;
  return;
}

/* EBPalReset @ 0x080554a0, 41 bytes
 *
 * Resets a palette's effect settings (block A) to neutral and marks it for
 * regeneration, unless they are already neutral.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: EBPalSettingsReset
 * Called by: AftImgDraw, PalGrpResetPalette, PalGrpSetClear
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
uint32_t EBPalReset(int arg1)

{
  uint32_t entry_EAX;
  
  if ((*(uint8_t *)(arg1 + 0x54) & 4) == 0) {
    EBPalSettingsReset((uint32_t *)(arg1 + 0xc));
    entry_EAX = *(uint32_t *)(arg1 + 0x54) | 5;
    *(uint32_t *)(arg1 + 0x54) = entry_EAX;
  }
  return entry_EAX;
}

/* EBPalCopy @ 0x080554d0, 108 bytes
 *
 * Copies a whole palette record from `src` to `dest`. With `deep` set, the
 * colour data is duplicated so the copy owns it; otherwise both share it.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int *
 *   arg3         int
 *
 * C library: calloc, memcpy
 * Called by: FontReadFilePtr_0_01, SpriteArrayPalRemapFromRoot
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
uint32_t EBPalCopy(int *arg1,int *arg2,int arg3)

{
  void *dest;
  int i1;
  int *pi2;
  int *pi3;
  
  pi2 = arg2;
  pi3 = arg1;
  for (i1 = 0x97; i1 != 0; i1 = i1 + -1) {
    *pi3 = *pi2;
    pi2 = pi2 + 1;
    pi3 = pi3 + 1;
  }
  arg1[1] = 0;
  if (arg3 != 0) {
    i1 = *arg2;
    dest = calloc(1,i1 * 4);
    arg1[2] = (int)dest;
    if (dest == (void *)0x0) {
      return 0;
    }
    memcpy(dest,(void *)arg2[2],i1 * 4);
  }
  return 1;
}

/* EBPalGenerateFPal @ 0x08055540, 40 bytes
 *
 * Regenerates a palette's 16-bit colour table from its source colours and
 * current effect settings (Pal4ToFpal) and clears the "data changed" flag.
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: Pal4ToFpal
 * Called by: EBPalInit, FontReadFilePtr_0_01
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void EBPalGenerateFPal(int *arg1)

{
  Pal4ToFpal(arg1[2],(int)(arg1 + 0x17),0,*arg1 + -1);
  arg1[0x15] = arg1[0x15] & 0xfffffffe;
  return;
}

/* EBPalUpdate @ 0x08055570, 229 bytes
 *
 * Brings a palette's 16-bit colour table up to date. The table is
 * regenerated when the source colours changed, when its effect settings
 * changed, or (render mode 0) when the master palette changed since the last
 * update. Its own settings are combined with the master palette's
 * (EBPalSettingsMix).
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: EBPalSettingsAreSame, EBPalSettingsMix, Pal4SettingsToFpal,
 *        EBPalSettingsCopy
 * Called by: SpriteArrayPalUpdateAndAccess, W_PutSprite8to16,
 *            W_PutSpriteFlat8to16, W_PutSpriteMirH8to16,
 *            W_PutSpriteMirHV8to16, W_PutSpriteMirV8to16,
 *            W_PutSpriteTransAdd8to16, W_PutSpriteTransAdd8to16_B,
 *            W_PutSpriteTransAddMirH8to16, W_PutSpriteTransAddMirH8to16_B,
 *            W_PutSpriteTransAddMirHV8to16,
 *            W_PutSpriteTransAddMirHV8to16_B,
 *            W_PutSpriteTransAddMirV8to16, W_PutSpriteTransAddMirV8to16_B,
 *            W_PutSpriteTransSub8to16, W_PutSpriteTransSubMirH8to16, ...
 *            (49 callers)
 *
 * Elecbyte file: src/lib/pal-lib.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x40 bytes, 1
 *       variables), because their address is taken.
 */
void EBPalUpdate(int *arg1)

{
  bool b1;
  bool b2;
  uint32_t u3;
  uint32_t stale_var;
  int *pi4;
  unsigned char frame[0x40] __attribute__((aligned(16)));
#define stk_3c (*(int (*)[12])(frame + 0x4))
  
  pi4 = stk_3c;
  b1 = false;
  if ((G_RenderMode == 0) && (arg1[0x16] != MasterPal[0x13])) {
    b1 = true;
  }
  u3 = arg1[0x15] & 2;
  if (((!b1) && ((arg1[0x15] & 1U) == 0)) && (u3 == 0)) {
    return;
  }
  if (((b1) || (u3 != 0)) ||
     (b2 = EBPalSettingsAreSame((uint8_t *)(arg1 + 3),(uint8_t *)(arg1 + 0xc)),
     ZEXT8(b2) == 0)) {
    if (b1) {
      EBPalSettingsMix(stk_3c,MasterPal,arg1 + 3);
    }
    else {
      pi4 = arg1 + 3;
    }
    Pal4SettingsToFpal(arg1[2],pi4,(int)(arg1 + 0x17),0,*arg1 + -1);
    EBPalSettingsCopy(arg1 + 0xc,arg1 + 3);
    palupdatecount = palupdatecount + 1;
  }
  pi4 = MasterPal;
  arg1[0x15] = arg1[0x15] & 0xfffffffc;
  arg1[0x16] = pi4[0x13];
  return;
}
#undef stk_3c

/* EBPalSetDataptr @ 0x08055660, 71 bytes
 *
 * Points a palette at new source colours and/or sets its colour count,
 * marking it changed. Fails (returns 0) for palettes that own their data.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *
 * Calls: EBPalMarkDataChanged
 * Called by: AftImgDraw
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
uint32_t EBPalSetDataptr(int *arg1,int arg2,int arg3)

{
  uint32_t u1;
  
  if (arg1[1] == 0) {
    if (-1 < arg2) {
      *arg1 = arg2;
    }
    if ((arg3 != 0) && (arg3 != arg1[2])) {
      arg1[2] = arg3;
      EBPalMarkDataChanged((int)arg1);
    }
    u1 = 1;
  }
  else {
    u1 = 0;
  }
  return u1;
}

/* EBPalGetDataptr @ 0x080556b0, 8 bytes
 *
 * Returns a palette's source colour data.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: AftImgDraw
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
uint32_t EBPalGetDataptr(int arg1)

{
  return *(uint32_t *)(arg1 + 8);
}

/* EBPalGetNumcols @ 0x080556c0, 7 bytes
 *
 * Returns a palette's colour count.
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
uint32_t EBPalGetNumcols(uint32_t *arg1)

{
  return *arg1;
}

/* EBPalMarkDataChanged @ 0x080556d0, 14 bytes
 *
 * Flags a palette for regeneration after its source colours changed.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: AftImgDraw, EBPalSetDataptr
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void EBPalMarkDataChanged(int arg1)

{
  *(uint32_t *)(arg1 + 0x54) = *(uint32_t *)(arg1 + 0x54) | 2;
  return;
}

/* EBPalSettingsReset @ 0x080556e0, 48 bytes
 *
 * Resets an effect settings block to neutral. Words: [0] colour factor 256,
 * [1..3] add r g b = 0, [4..6] multiply r g b = 256, [8] invert off.
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * Called by: EBPalInit, EBPalReset, MasterPalInit, MasterPalReset
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void EBPalSettingsReset(uint32_t *arg1)

{
  int i1;
  uint32_t *pu2;
  
  pu2 = arg1;
  for (i1 = 9; i1 != 0; i1 = i1 + -1) {
    *pu2 = 0;
    pu2 = pu2 + 1;
  }
  arg1[6] = 0x100;
  arg1[5] = 0x100;
  arg1[4] = 0x100;
  *arg1 = 0x100;
  return;
}

/* EBPalSettingsCopy @ 0x08055710, 21 bytes
 *
 * Copies an effect settings block (9 ints).
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         uint32_t *
 *
 * Called by: EBPalUpdate, MasterPalFinishedDraw
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void EBPalSettingsCopy(uint32_t *arg1,uint32_t *arg2)

{
  int i1;
  
  for (i1 = 9; i1 != 0; i1 = i1 + -1) {
    *arg1 = *arg2;
    arg2 = arg2 + 1;
    arg1 = arg1 + 1;
  }
  return;
}

/* EBPalSettingsMix @ 0x08055730, 115 bytes
 *
 * Combines two effect settings blocks into a third: factors and per-channel
 * multipliers are multiplied (>> 8), additions are summed, and invert is set
 * if either has it.
 *
 * As in the original machine code, the green and blue additions both add the
 * second block's red addition (arg2[1]) rather than its green and blue ones.
 * This looks like an Elecbyte typo; it only matters when both blocks have
 * different per-channel additions.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int *
 *   arg3         int *
 *
 * Called by: EBPalUpdate
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void EBPalSettingsMix(int *arg1,int *arg2,int *arg3)

{
  int i1;
  
  *arg1 = *arg3 * *arg2 >> 8;
  arg1[1] = arg3[1] + arg2[1];
  arg1[2] = arg3[2] + arg2[1];
  arg1[3] = arg3[3] + arg2[1];
  arg1[4] = arg3[4] * arg2[4] >> 8;
  arg1[5] = arg3[5] * arg2[5] >> 8;
  arg1[6] = arg3[6] * arg2[6] >> 8;
  i1 = 0;
  if ((arg2[8] != 0) || (arg3[8] != 0)) {
    i1 = 1;
  }
  arg1[8] = i1;
  return;
}

/* EBPalSettingsAreSame @ 0x080557b0, 34 bytes
 *
 * Returns true when two effect settings blocks are identical.
 *
 * Parameters:
 *   arg1         uint8_t *
 *   arg2         uint8_t *
 *
 * Called by: EBPalUpdate, MasterPalProcessChanges
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
bool EBPalSettingsAreSame(uint8_t *arg1,uint8_t *arg2)

{
  int i1;
  uint8_t entry_CF;
  uint8_t entry_ZF;
  
  i1 = 0x24;
  do {
    if (i1 == 0) break;
    i1 = i1 + -1;
    entry_CF = *arg1 < *arg2;
    entry_ZF = *arg1 == *arg2;
    arg1 = arg1 + 1;
    arg2 = arg2 + 1;
  } while ((bool)entry_ZF);
  return (!(bool)entry_CF && !(bool)entry_ZF) == (bool)entry_CF;
}

/* EBPalAdd @ 0x080557e0, 67 bytes
 *
 * Adds (r, g, b) to a palette's effect additions and marks it for
 * regeneration (does nothing for 0, 0, 0). Used by PalFX "add".
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Called by: AftImgDraw, PalGrpSetAdd
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
uint32_t EBPalAdd(int arg1,int arg2,int arg3,int arg4)

{
  uint32_t u1;
  
  u1 = arg1 + 0xc;
  if (((arg2 != 0) || (arg3 != 0)) || (arg4 != 0)) {
    *(int *)(arg1 + 0x10) = *(int *)(arg1 + 0x10) + arg2;
    *(int *)(arg1 + 0x14) = *(int *)(arg1 + 0x14) + arg3;
    *(int *)(arg1 + 0x18) = *(int *)(arg1 + 0x18) + arg4;
    u1 = *(uint32_t *)(arg1 + 0x54) & 0xfffffffb | 1;
    *(uint32_t *)(arg1 + 0x54) = u1;
  }
  return u1;
}

/* EBPalMul @ 0x08055830, 93 bytes
 *
 * Multiplies a palette's per-channel multipliers by (r, g, b) / 256 and
 * marks it for regeneration (nothing happens for 256, 256, 256). Used by
 * PalFX "mul".
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Called by: AftImgDraw, PalGrpSetMul
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void EBPalMul(int arg1,int arg2,int arg3,int arg4)

{
  if (((arg2 != 0x100) || (arg3 != 0x100)) || (arg4 != 0x100)) {
    *(int *)(arg1 + 0x1c) = arg2 * *(int *)(arg1 + 0x1c) >> 8;
    *(int *)(arg1 + 0x20) = *(int *)(arg1 + 0x20) * arg3 >> 8;
    *(int *)(arg1 + 0x24) = *(int *)(arg1 + 0x24) * arg4 >> 8;
    *(uint32_t *)(arg1 + 0x54) = *(uint32_t *)(arg1 + 0x54) & 0xfffffffb | 1;
  }
  return;
}

/* EBPalInvertAll @ 0x08055890, 40 bytes
 *
 * Toggles the invert flag of a palette's effects when `on` is nonzero (PalFX
 * "invertall").
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Called by: PalGrpSetInvertAll
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void EBPalInvertAll(int arg1,int arg2)

{
  if (arg2 != 0) {
    *(uint32_t *)(arg1 + 0x2c) = (uint32_t)(*(int *)(arg1 + 0x2c) == 0);
    *(uint32_t *)(arg1 + 0x54) = *(uint32_t *)(arg1 + 0x54) & 0xfffffffb | 1;
  }
  return;
}

/* EBPalColorBal @ 0x080558c0, 40 bytes
 *
 * Multiplies a palette's overall colour factor (settings word 0) by `factor`
 * / 256 and marks it for regeneration (PalFX "color").
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Called by: PalGrpSetColorBal
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
int EBPalColorBal(int arg1,int arg2)

{
  if (arg2 != 0x100) {
    *(int *)(arg1 + 0xc) = arg2 * *(int *)(arg1 + 0xc) >> 8;
    arg2 = *(uint32_t *)(arg1 + 0x54) & 0xfffffffb | 1;
    *(int *)(arg1 + 0x54) = arg2;
  }
  return arg2;
}

/* MasterPalInit @ 0x080558f0, 91 bytes
 *
 * Creates the master palette: two settings blocks (current, last drawn) and
 * a change counter. Its effects apply on top of every palette (screen-wide
 * fades and flashes, AllPalFX). Returns false if allocation fails.
 *
 * Calls: EBPalSettingsReset
 * C library: calloc
 * Called by: G_Init
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
bool MasterPalInit(void)

{
  int *pi1;
  
  if (MasterPal == (int *)0x0) {
    MasterPal = calloc(1,0x54);
  }
  pi1 = MasterPal;
  if (MasterPal != (int *)0x0) {
    EBPalSettingsReset(MasterPal);
    EBPalSettingsReset(MasterPal + 9);
    pi1 = MasterPal;
    MasterPal[0x14] = 1;
  }
  return pi1 != (int *)0x0;
}

/* MasterPalDeInit @ 0x08055950, 38 bytes
 *
 * Frees the master palette.
 *
 * C library: free
 * Called by: G_DeInit
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void MasterPalDeInit(void)

{
  if (MasterPal != (int *)0x0) {
    free(MasterPal);
    MasterPal = (int *)0x0;
  }
  return;
}

/* MasterPalProcessChanges @ 0x08055980, 65 bytes
 *
 * Called before drawing a frame: if the master settings were modified and
 * differ from the last drawn ones, the change counter is incremented so
 * every palette regenerates (EBPalUpdate).
 *
 * Calls: EBPalSettingsAreSame
 * Called by: CharacterSelectScreenDraw, ContinueScreenLoop, GameLoop,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, PlayCutscene,
 *            VersusScreen
 *
 * Elecbyte file: src/lib/pal-lib.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
void MasterPalProcessChanges(void)

{
  bool b1;
  uint32_t stale_var;
  
  if (MasterPal[0x12] != 0) {
    b1 = EBPalSettingsAreSame((uint8_t *)MasterPal,(uint8_t *)(MasterPal + 9));
    if (ZEXT8(b1) == 0) {
      MasterPal[0x13] = MasterPal[0x13] + 1;
    }
    else {
      MasterPal[0x12] = 0;
    }
  }
  return;
}

/* MasterPalFinishedDraw @ 0x080559d0, 46 bytes
 *
 * Called after a frame is drawn: copies the current master settings to "last
 * drawn" and clears the modified flag.
 *
 * Calls: EBPalSettingsCopy
 * Called by: CharacterSelectScreenDraw, ContinueScreenLoop, GameLoop,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, PlayCutscene,
 *            VersusScreen
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void MasterPalFinishedDraw(void)

{
  if (MasterPal[0x12] != 0) {
    EBPalSettingsCopy(MasterPal + 9,MasterPal);
    MasterPal[0x12] = 0;
  }
  return;
}

/* MasterPalReset @ 0x08055a00, 37 bytes
 *
 * Resets the master palette effects to neutral and flags the change.
 *
 * Calls: EBPalSettingsReset
 * Called by: CharacterSelectScreen, GameLoop, PalFXUpdate, PlayCutscene,
 *            VersusScreen
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void MasterPalReset(void)

{
  int *pi1;
  
  EBPalSettingsReset(MasterPal);
  pi1 = MasterPal;
  MasterPal[0x12] = 1;
  pi1[0x14] = 1;
  return;
}

/* MasterPalAdd @ 0x08055a30, 63 bytes
 *
 * Sets the master palette additions to (r, g, b) (screen-wide) and flags the
 * change if they differ.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *
 * Called by: GameRoundReset, PalFXUpdate, SiSceneUpdatePal
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
int * MasterPalAdd(int arg1,int arg2,int arg3)

{
  int *pi1;
  
  pi1 = MasterPal;
  if (((MasterPal[1] != arg1) || (MasterPal[2] != arg2)) || (MasterPal[3] != arg3)) {
    MasterPal[1] = arg1;
    pi1[2] = arg2;
    pi1[3] = arg3;
    pi1 = MasterPal;
    MasterPal[0x12] = 1;
    pi1[0x14] = 0;
  }
  return pi1;
}

/* MasterPalMul @ 0x08055a70, 63 bytes
 *
 * Sets the master palette multipliers to (r, g, b) (256 = unchanged) and
 * flags the change if they differ.
 *
 * Parameters:
 *   r            int
 *   g2           int  (g)
 *   b            int
 *
 * Called by: CharacterSelectScreen, ContinueScreenLoop, GameDemoUpdate,
 *            GameRoundReset, GameRoundUpdate, GameSurvivalResultsUpdate,
 *            GameWinScreenUpdate, ModeSelect, PalFXUpdate, PlayerKBUpdate,
 *            SiSceneUpdatePal, VersusScreen
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
int * MasterPalMul(int r,int g2,int b)

{
  int *pi1;
  
  pi1 = MasterPal;
  if (((MasterPal[4] != r) || (MasterPal[5] != g2)) || (MasterPal[6] != b)) {
    MasterPal[4] = r;
    pi1[5] = g2;
    pi1[6] = b;
    pi1 = MasterPal;
    MasterPal[0x12] = 1;
    pi1[0x14] = 0;
  }
  return pi1;
}

/* MasterPalInvertAll @ 0x08055ab0, 32 bytes
 *
 * Sets the master palette's invert flag and flags the change if it differs.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: PalFXUpdate
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void MasterPalInvertAll(int arg1)

{
  int *pi1;
  
  pi1 = MasterPal;
  if (MasterPal[8] != arg1) {
    MasterPal[8] = arg1;
    pi1[0x12] = 1;
    pi1[0x14] = 0;
  }
  return;
}

/* MasterPalColorBal @ 0x08055ad0, 30 bytes
 *
 * Sets the master palette's colour factor (256 = unchanged) and flags the
 * change if it differs.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: PalFXUpdate
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void MasterPalColorBal(int arg1)

{
  int *pi1;
  
  pi1 = MasterPal;
  if (*MasterPal != arg1) {
    *MasterPal = arg1;
    pi1[0x12] = 1;
    pi1[0x14] = 0;
  }
  return;
}

/* MasterPalConvertCol16 @ 0x08055af0, 129 bytes
 *
 * Converts a 16-bit (5-6-5) colour through the master palette effects, so
 * that primitives (boxes, lines) fade and flash like sprites. Returns the
 * colour unchanged when the master effects are neutral.
 *
 * Parameters:
 *   arg1         uint32_t
 *
 * Calls: Pal4SettingsToFpal
 * Called by: V_FontDrawLine, W_Box, W_BoxFill, W_BoxFillTransAdd16,
 *            W_BoxFillTransAdd16_B50, W_BoxFillTransSub16,
 *            W_BoxFillTransSub16_B50, W_Cls, W_HLine, W_HLineTransAdd16,
 *            W_HLineTransAdd16_B50, W_HLineTransSub16,
 *            W_HLineTransSub16_B50, W_Line, W_PutPixel,
 *            W_PutPixelTransAdd16, ... (21 callers)
 *
 * Elecbyte file: src/lib/pal-lib.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x10 bytes, 2
 *       variables), because their address is taken.
 */
uint32_t MasterPalConvertCol16(uint32_t arg1)

{
  uint32_t entry_EDX;
  unsigned char frame[0x10] __attribute__((aligned(16)));
#define stk_a (*(uint16_t *)(frame + 0x6))
#define stk_8 (*(uint32_t *)(frame + 0x8))
  
  stk_a = (uint16_t)((uint32_t)entry_EDX >> 0x10);
  if (MasterPal[0x14] == 0) {
    stk_8 = (uint32_t)(CONCAT11((char)((arg1 & 0x7e0) >> 3),(char)(arg1 >> 8)) & 0xfff8);
    stk_8 = stk_8 | (arg1 & 0x1f) << 0x13;
    Pal4SettingsToFpal((int)&stk_8,MasterPal,(int)&stk_a,0,0);
  }
  else {
    stk_a = (uint16_t)arg1;
  }
  return (uint32_t)stk_a;
}
#undef stk_a
#undef stk_8

/* Pal3toPal4 @ 0x08055b80, 92 bytes
 *
 * Converts `count` RGB triplets into 4-byte RGBA entries; the fourth byte is
 * 255, or 0 when `zero_alpha` is set.
 *
 * Parameters:
 *   arg1         uint8_t *
 *   arg2         uint8_t *
 *   arg3         int
 *   arg4         int
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void Pal3toPal4(uint8_t *arg1,uint8_t *arg2,int arg3,int arg4)

{
  uint8_t *pu1;
  int i2;
  uint8_t u3;
  
  u3 = 0xff;
  if (arg4 != 0) {
    u3 = 0;
  }
  if (0 < arg3) {
    *arg1 = *arg2;
    pu1 = arg2 + 2;
    arg1[1] = arg2[1];
    arg2 = arg2 + 3;
    arg1[2] = *pu1;
    arg1[3] = u3;
    arg1 = arg1 + 4;
  }
  if (1 < arg3) {
    i2 = arg3 + -1;
    do {
      *arg1 = *arg2;
      pu1 = arg2 + 2;
      arg1[1] = arg2[1];
      arg2 = arg2 + 3;
      arg1[2] = *pu1;
      arg1[3] = 0xff;
      arg1 = arg1 + 4;
      i2 = i2 + -1;
    } while (i2 != 0);
  }
  return;
}

/* Pal4Copy @ 0x08055be0, 69 bytes
 *
 * Copies `count` 4-byte palette entries. Used by the other Pal4 effect
 * functions to copy the source range first.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * C library: memcpy
 * Called by: Pal4Brightness, Pal4BrightnessRGB, Pal4ColorBal,
 *            Pal4Contrast, Pal4ContrastRGB
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void Pal4Copy(int arg1,int arg2,int arg3,int arg4)

{
  if (arg1 != arg2) {
    memcpy((void *)(arg3 * 4 + arg2),(void *)(arg3 * 4 + arg1),
           (arg4 - arg3) * 4 + 4);
    return;
  }
  return;
}

/* Pal4SetSingle @ 0x08055c30, 41 bytes
 *
 * Sets one 4-byte palette entry to (r, g, b). Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         uint8_t
 *   arg4         uint8_t
 *   arg5         uint8_t
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void Pal4SetSingle(int arg1,int arg2,uint8_t arg3,uint8_t arg4,uint8_t arg5)

{
  int i1;
  
  i1 = arg2 * 4;
  *(uint8_t *)(i1 + arg1) = arg3;
  *(uint8_t *)(i1 + 1 + arg1) = arg4;
  *(uint8_t *)(i1 + 2 + arg1) = arg5;
  return;
}

/* Pal4Contrast @ 0x08055c60, 155 bytes
 *
 * Applies a contrast factor to a range of palette entries. Not called in
 * this build.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *
 * Calls: Pal4Copy
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void Pal4Contrast(int arg1,int arg2,int arg3,int arg4,int arg5)

{
  int i1;
  int i2;
  
  if (arg3 == 0x100) {
    Pal4Copy(arg1,arg2,arg4,arg5);
    return;
  }
  for (i2 = arg4 * 4; i2 < arg5 * 4 + 4; i2 = i2 + 4) {
    i1 = (int)((uint32_t)*(uint8_t *)(i2 + arg1) * arg3) >> 8;
    if (0xff < i1) {
      i1 = 0xff;
    }
    *(char *)(i2 + arg2) = (char)i1;
    i1 = (int)((uint32_t)*(uint8_t *)(i2 + 1 + arg1) * arg3) >> 8;
    if (0xff < i1) {
      i1 = 0xff;
    }
    *(char *)(i2 + 1 + arg2) = (char)i1;
    i1 = (int)((uint32_t)*(uint8_t *)(i2 + 2 + arg1) * arg3) >> 8;
    if (0xff < i1) {
      i1 = 0xff;
    }
    *(char *)(i2 + 2 + arg2) = (char)i1;
  }
  return;
}

/* Pal4ContrastRGB @ 0x08055d00, 200 bytes
 *
 * Applies per-channel contrast factors to a range of palette entries
 * (copying from a source palette). Used by AftImgDraw for afterimage colour
 * effects.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *   arg6         int
 *   arg7         int
 *
 * Calls: Pal4Copy
 * Called by: AftImgDraw
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void Pal4ContrastRGB(int arg1,int arg2,int arg3,int arg4,int arg5,int arg6,
                    int arg7)

{
  int i1;
  int i2;
  
  if (((arg3 == 0x100) && (arg4 == 0x100)) && (arg5 == 0x100)) {
    Pal4Copy(arg1,arg2,arg6,arg7);
    return;
  }
  for (i2 = arg6 * 4; i2 < arg7 * 4 + 4; i2 = i2 + 4) {
    i1 = (int)((uint32_t)*(uint8_t *)(i2 + arg1) * arg3) >> 8;
    if (0xff < i1) {
      i1 = 0xff;
    }
    *(char *)(i2 + arg2) = (char)i1;
    i1 = (int)((uint32_t)*(uint8_t *)(i2 + 1 + arg1) * arg4) >> 8;
    if (0xff < i1) {
      i1 = 0xff;
    }
    *(char *)(i2 + 1 + arg2) = (char)i1;
    i1 = (int)((uint32_t)*(uint8_t *)(i2 + 2 + arg1) * arg5) >> 8;
    if (0xff < i1) {
      i1 = 0xff;
    }
    *(char *)(i2 + 2 + arg2) = (char)i1;
  }
  return;
}

/* Pal4Brightness @ 0x08055dd0, 193 bytes
 *
 * Adds a brightness offset to a range of palette entries, clamped to 0-255.
 * Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *
 * Calls: Pal4Copy
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void Pal4Brightness(int arg1,int arg2,int arg3,int arg4,int arg5)

{
  int i1;
  int i2;
  
  if (arg3 == 0) {
    Pal4Copy(arg1,arg2,arg4,arg5);
    return;
  }
  for (i1 = arg4 * 4; i1 < arg5 * 4 + 4; i1 = i1 + 4) {
    i2 = (uint32_t)*(uint8_t *)(i1 + arg1) + arg3;
    if (0xff < i2) {
      i2 = 0xff;
    }
    *(uint8_t *)(i1 + arg2) = (uint8_t)i2 & -(char)(i2 >> 0x1f) - 1U;
    i2 = (uint32_t)*(uint8_t *)(i1 + 1 + arg1) + arg3;
    if (0xff < i2) {
      i2 = 0xff;
    }
    *(uint8_t *)(i1 + 1 + arg2) = (uint8_t)i2 & -(char)(i2 >> 0x1f) - 1U;
    i2 = (uint32_t)*(uint8_t *)(i1 + 2 + arg1) + arg3;
    if (0xff < i2) {
      i2 = 0xff;
    }
    *(uint8_t *)(i1 + 2 + arg2) = (uint8_t)i2 & -(char)(i2 >> 0x1f) - 1U;
  }
  return;
}

/* Pal4BrightnessRGB @ 0x08055ea0, 231 bytes
 *
 * Adds per-channel brightness offsets to a range of palette entries, clamped
 * to 0-255. Used by AftImgDraw.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *   arg6         int
 *   arg7         int
 *
 * Calls: Pal4Copy
 * Called by: AftImgDraw
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void Pal4BrightnessRGB(int arg1,int arg2,int arg3,int arg4,int arg5,int arg6,
                      int arg7)

{
  int i1;
  int i2;
  
  if (((arg3 == 0) && (arg4 == 0)) && (arg5 == 0)) {
    Pal4Copy(arg1,arg2,arg6,arg7);
    return;
  }
  for (i1 = arg6 * 4; i1 < arg7 * 4 + 4; i1 = i1 + 4) {
    i2 = arg3 + (uint32_t)*(uint8_t *)(i1 + arg1);
    if (0xff < i2) {
      i2 = 0xff;
    }
    *(uint8_t *)(i1 + arg2) = (uint8_t)i2 & -(char)(i2 >> 0x1f) - 1U;
    i2 = arg4 + (uint32_t)*(uint8_t *)(i1 + 1 + arg1);
    if (0xff < i2) {
      i2 = 0xff;
    }
    *(uint8_t *)(i1 + 1 + arg2) = (uint8_t)i2 & -(char)(i2 >> 0x1f) - 1U;
    i2 = (uint32_t)*(uint8_t *)(i1 + 2 + arg1) + arg5;
    if (0xff < i2) {
      i2 = 0xff;
    }
    *(uint8_t *)(i1 + 2 + arg2) = (uint8_t)i2 & -(char)(i2 >> 0x1f) - 1U;
  }
  return;
}

/* Pal4ColorBal @ 0x08055f90, 312 bytes
 *
 * Applies a colour (saturation) factor to a range of palette entries. Used
 * by AftImgDraw.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *
 * Calls: Pal4Copy
 * Called by: AftImgDraw
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void Pal4ColorBal(int arg1,int arg2,int arg3,int arg4,int arg5)

{
  uint8_t *pb1;
  uint8_t *pb2;
  int i3;
  uint8_t b4;
  uint8_t u5;
  int i6;
  int i7;
  uint8_t *pb8;
  
  i3 = arg5 * 4 + 4;
  if (arg3 == 0) {
    i7 = arg4 * 4;
    pb8 = (uint8_t *)(i7 + arg1);
    for (; i7 < i3; i7 = i7 + 4) {
      b4 = *pb8;
      pb1 = pb8 + 1;
      pb2 = pb8 + 2;
      pb8 = pb8 + 4;
      u5 = (uint8_t)((int)((uint32_t)b4 * 5 + (uint32_t)*pb1 * 7 + (uint32_t)*pb2 * 4) >> 4);
      *(uint8_t *)(i7 + 2 + arg2) = u5;
      *(uint8_t *)(i7 + 1 + arg2) = u5;
      *(uint8_t *)(i7 + arg2) = u5;
    }
  }
  else {
    if (0xfe < arg3 - 1U) {
      Pal4Copy(arg1,arg2,arg4,arg5);
      return;
    }
    i7 = arg4 * 4;
    pb8 = (uint8_t *)(i7 + arg1);
    for (; i7 < i3; i7 = i7 + 4) {
      i6 = ((int)((uint32_t)*pb8 * 5 + (uint32_t)pb8[1] * 7 + (uint32_t)pb8[2] * 4) >> 4) *
              (0x100 - arg3);
      *(char *)(i7 + arg2) = (char)((uint32_t)*pb8 * arg3 + i6 >> 8);
      *(char *)(i7 + 1 + arg2) = (char)((uint32_t)pb8[1] * arg3 + i6 >> 8);
      pb1 = pb8 + 2;
      pb8 = pb8 + 4;
      *(char *)(i7 + 2 + arg2) = (char)((uint32_t)*pb1 * arg3 + i6 >> 8);
    }
  }
  return;
}

/* Pal4InvertAll @ 0x080560d0, 72 bytes
 *
 * Inverts a range of palette entries (255 - value). Used by AftImgDraw.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Called by: AftImgDraw
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void Pal4InvertAll(int arg1,int arg2,int arg3,int arg4)

{
  int i1;
  
  for (i1 = arg3 * 4; i1 < (arg4 + 1) * 4; i1 = i1 + 4) {
    *(uint8_t *)(i1 + arg2) = *(uint8_t *)(i1 + arg1) ^ 0xff;
    *(uint8_t *)(i1 + 1 + arg2) = *(uint8_t *)(i1 + 1 + arg1) ^ 0xff;
    *(uint8_t *)(i1 + 2 + arg2) = *(uint8_t *)(i1 + 2 + arg1) ^ 0xff;
  }
  return;
}

/* Pal4Read3File @ 0x08056120, 159 bytes
 *
 * Opens an .act palette file and reads it (Pal4Read3FilePtr). Returns
 * nonzero on success.
 *
 * Parameters:
 *   arg1         int
 *   arg2         char *
 *
 * C library: fopen, fgetc, feof, fclose
 * Called by: PlayerDefLoadPtr
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
uint32_t Pal4Read3File(int arg1,char *arg2)

{
  FILE *fp;
  uint32_t u1;
  int i2;
  int i3;
  int i4;
  
  i4 = 0;
  fp = fopen(arg2,"rb");
  if (fp == (FILE *)0x0) {
    u1 = 0;
  }
  else {
    do {
      i3 = (0xff - i4) * 4;
      i2 = fgetc(fp);
      *(char *)(i3 + arg1) = (char)i2;
      i2 = fgetc(fp);
      *(char *)(i3 + 1 + arg1) = (char)i2;
      i2 = fgetc(fp);
      *(char *)(i3 + 2 + arg1) = (char)i2;
      i2 = feof(fp);
      if (i2 != 0) {
        fclose(fp);
        return 0;
      }
      i4 = i4 + 1;
    } while (i4 < 0x100);
    fclose(fp);
    u1 = 1;
  }
  return u1;
}

/* Pal4Read3FilePtr @ 0x080561c0, 151 bytes
 *
 * Reads a 256-colour .act palette (RGB triplets) from an MF stream into
 * 4-byte entries, stored in reverse order (entry 255 first), as character
 * palettes expect. A short file is an error.
 *
 * Parameters:
 *   arg1         int
 *   mf           int *
 *
 * Calls: MFgetc, MFfeof, MFfclose
 * Called by: PlayerDefLoadZip
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
uint32_t Pal4Read3FilePtr(int arg1,int *mf)

{
  uint32_t ch;
  int i2;
  int i3;
  
  i3 = 0;
  while( true ) {
    i2 = (0xff - i3) * 4;
    ch = MFgetc(mf);
    *(char *)(i2 + arg1) = (char)ch;
    ch = MFgetc(mf);
    *(char *)(i2 + 1 + arg1) = (char)ch;
    ch = MFgetc(mf);
    *(char *)(i2 + 2 + arg1) = (char)ch;
    i2 = MFfeof(mf);
    if ((i2 != 0) && (i3 != 0xff)) break;
    i3 = i3 + 1;
    if (0xff < i3) {
      if (*mf != 3) {
        MFfclose(mf);
      }
      return 1;
    }
  }
  if (*mf != 3) {
    MFfclose(mf);
  }
  return 0;
}

/* Pal4ToFpal @ 0x08056260, 93 bytes
 *
 * Converts a range of 4-byte palette entries into the 16-bit colour table,
 * with neutral effects.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Called by: EBPalGenerateFPal
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void Pal4ToFpal(int arg1,int arg2,int arg3,int arg4)

{
  uint8_t *pb1;
  uint8_t *pb2;
  uint8_t b3;
  uint8_t *pb4;
  uint16_t *pu5;
  int i6;
  
  pb4 = (uint8_t *)(arg3 * 4 + arg1);
  pu5 = (uint16_t *)(arg3 * 2 + arg2);
  for (i6 = (arg4 - arg3) + 1; i6 != 0; i6 = i6 + -1) {
    b3 = *pb4;
    pb1 = pb4 + 1;
    pb2 = pb4 + 2;
    pb4 = pb4 + 4;
    *pu5 = (uint16_t)(b3 >> 3) << 0xb | (uint16_t)(*pb1 >> 2) << 5 | (uint16_t)(*pb2 >> 3);
    pu5 = pu5 + 1;
  }
  return;
}

/* Pal4SettingsToFpal @ 0x080562c0, 1183 bytes
 *
 * Converts a range of 4-byte palette entries into 16-bit (5-6-5) colours
 * while applying an effect settings block: invert, overall factor,
 * per-channel multiply, add, colour balance, clamped to 0-255. This is where
 * PalFX and AllPalFX colours are computed.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int *
 *   arg3         int
 *   arg4         int
 *   arg5         int
 *
 * Called by: EBPalUpdate, MasterPalConvertCol16
 *
 * Elecbyte file: src/lib/pal-lib.c
 */
void Pal4SettingsToFpal(int arg1,int *arg2,int arg3,int arg4,int arg5)

{
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  int i7;
  uint32_t u8;
  int i9;
  uint32_t u10;
  int i11;
  uint32_t u12;
  int i13;
  int i14;
  uint32_t u15;
  int i16;
  int i17;
  int stk_18;
  
  i1 = (arg5 - arg4) * 4 + 4;
  i9 = arg4 * 2 + arg3;
  u8 = ((arg2[8] != 0) - 1 & 0xffffff01) + 0xff;
  i16 = arg4 * 4 + arg1;
  i17 = *arg2;
  i2 = arg2[1];
  i3 = arg2[2];
  i4 = arg2[3];
  i5 = arg2[4];
  i6 = arg2[5];
  i7 = arg2[6];
  if ((((i5 == 0x100) && (i6 == 0x100)) && (i7 == 0x100)) && (i17 == 0x100)) {
    stk_18 = 0;
    if (0 < i1) {
      i17 = 0;
      do {
        u12 = i2 + (*(uint8_t *)(i17 + i16) ^ u8);
        u12 = u12 & 0xffffffffU - ((int)u12 >> 0x1f);
        if (0xff < (int)u12) {
          u12 = 0xff;
        }
        u15 = i3 + (*(uint8_t *)(i17 + 1 + i16) ^ u8);
        u15 = u15 & 0xffffffffU - ((int)u15 >> 0x1f);
        if (0xff < (int)u15) {
          u15 = 0xff;
        }
        u10 = i4 + (*(uint8_t *)(i17 + 2 + i16) ^ u8);
        u10 = u10 & 0xffffffffU - ((int)u10 >> 0x1f);
        if (0xff < (int)u10) {
          u10 = 0xff;
        }
        i17 = i17 + 4;
        *(uint16_t *)(i9 + stk_18 * 2) =
             (uint16_t)(((int)u12 >> 3) << 0xb) | (uint16_t)(((int)u15 >> 2) << 5) |
             (uint16_t)((int)u10 >> 3);
        stk_18 = stk_18 + 1;
      } while (i17 < i1);
    }
  }
  else if (i17 == 0) {
    i17 = 0;
    stk_18 = 0;
    if (0 < i1) {
      do {
        u12 = (int)((uint32_t)*(uint8_t *)(i17 + i16) * 5 +
                       (uint32_t)*(uint8_t *)(i17 + 1 + i16) * 7 +
                      (uint32_t)*(uint8_t *)(i17 + 2 + i16) * 4) >> 4 ^ u8;
        i13 = (i2 + u12) * i5;
        u15 = i13 >> 8 & 0xffffffffU - (i13 >> 0x1f);
        if (0xff < (int)u15) {
          u15 = 0xff;
        }
        i13 = (i3 + u12) * i6;
        u10 = i13 >> 8 & 0xffffffffU - (i13 >> 0x1f);
        if (0xff < (int)u10) {
          u10 = 0xff;
        }
        i13 = (u12 + i4) * i7;
        u12 = i13 >> 8 & 0xffffffffU - (i13 >> 0x1f);
        if (0xff < (int)u12) {
          u12 = 0xff;
        }
        i17 = i17 + 4;
        *(uint16_t *)(i9 + stk_18 * 2) =
             (uint16_t)(((int)u15 >> 3) << 0xb) | (uint16_t)(((int)u10 >> 2) << 5) |
             (uint16_t)((int)u12 >> 3);
        stk_18 = stk_18 + 1;
      } while (i17 < i1);
    }
  }
  else if (i17 < 0x100) {
    i13 = 0;
    stk_18 = 0;
    if (0 < i1) {
      do {
        u10 = (uint32_t)*(uint8_t *)(i13 + 1 + i16);
        u12 = (uint32_t)*(uint8_t *)(i13 + 2 + i16);
        i11 = ((int)((uint32_t)*(uint8_t *)(i13 + i16) * 5 + u10 * 7 + u12 * 4) >> 4) *
                 (0x100 - i17);
        i14 = (((int)((uint32_t)*(uint8_t *)(i13 + i16) * i17 + i11) >> 8 ^ u8) + i2)
                 * i5;
        u15 = i14 >> 8 & 0xffffffffU - (i14 >> 0x1f);
        if (0xff < (int)u15) {
          u15 = 0xff;
        }
        i14 = (i3 + ((int)(i11 + u10 * i17) >> 8 ^ u8)) * i6;
        u10 = i14 >> 8 & 0xffffffffU - (i14 >> 0x1f);
        if (0xff < (int)u10) {
          u10 = 0xff;
        }
        i11 = (i4 + ((int)(u12 * i17 + i11) >> 8 ^ u8)) * i7;
        u12 = i11 >> 8 & 0xffffffffU - (i11 >> 0x1f);
        if (0xff < (int)u12) {
          u12 = 0xff;
        }
        i13 = i13 + 4;
        *(uint16_t *)(i9 + stk_18 * 2) =
             (uint16_t)(((int)u15 >> 3) << 0xb) | (uint16_t)(((int)u10 >> 2) << 5) |
             (uint16_t)((int)u12 >> 3);
        stk_18 = stk_18 + 1;
      } while (i13 < i1);
    }
  }
  else {
    stk_18 = 0;
    if (0 < i1) {
      i17 = 0;
      do {
        i13 = (i2 + (*(uint8_t *)(i17 + i16) ^ u8)) * i5;
        u12 = i13 >> 8 & 0xffffffffU - (i13 >> 0x1f);
        if (0xff < (int)u12) {
          u12 = 0xff;
        }
        i13 = (i3 + (*(uint8_t *)(i17 + 1 + i16) ^ u8)) * i6;
        u15 = i13 >> 8 & 0xffffffffU - (i13 >> 0x1f);
        if (0xff < (int)u15) {
          u15 = 0xff;
        }
        i13 = (i4 + (*(uint8_t *)(i17 + 2 + i16) ^ u8)) * i7;
        u10 = i13 >> 8 & 0xffffffffU - (i13 >> 0x1f);
        if (0xff < (int)u10) {
          u10 = 0xff;
        }
        i17 = i17 + 4;
        *(uint16_t *)(i9 + stk_18 * 2) =
             (uint16_t)(((int)u12 >> 3) << 0xb) | (uint16_t)(((int)u15 >> 2) << 5) |
             (uint16_t)((int)u10 >> 3);
        stk_18 = stk_18 + 1;
      } while (i17 < i1);
    }
  }
  return;
}

