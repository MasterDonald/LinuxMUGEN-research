/*
 * pad-lib.c -- joysticks
 * Allegro joystick installation and polling, converted into joystick input
 * events.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/pad-lib.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"

extern int numpads __asm__("D_082879c4"); /* file-static 0x082879c4 */
extern int *PadHitHook __asm__("D_082879c8"); /* file-static 0x082879c8 */
extern int PadType __asm__("D_082a66e0"); /* file-static 0x082a66e0 */
extern int PadID __asm__("D_082a66e4"); /* file-static 0x082a66e4 */
extern uint8_t padbuf[1032] __asm__("D_082a6700"); /* file-static 0x082a6700 */
extern int padbitflag[4] __asm__("D_082a6b08"); /* file-static 0x082a6b08 */
extern int padoldbitflag[4] __asm__("D_082a6b18"); /* file-static 0x082a6b18 */

/* PadInit @ 0x08054e80, 153 bytes
 *
 * Installs joystick support. For the supported joystick type codes (1, 4, 6,
 * 8, 0x14, 0x15, 0x17) it calls install_joystick(JOY_TYPE_AUTODETECT) and
 * takes the pad count from Allegro. Returns nonzero when a joystick with
 * buttons was found; the second argument is stored as the pad id.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Calls: PadReset
 * C library: memset, install_joystick
 * Called by: GameInitPads, OptionsScreen
 *
 * Elecbyte file: src/lib/pad-lib.c
 * Note: 1 accesses to parts of a variable are written as sized accesses.
 */
int PadInit(int arg1,int arg2)

{
  int i1;
  int i2;
  
  if (PadInstalled == 0) {
    memset(padflag,0,0x81);
    PadType = 0;
    i1 = 0;
    switch(arg1) {
    case 1:
    case 4:
    case 6:
    case 8:
    case 0x14:
    case 0x15:
    case 0x17:
      i2 = install_joystick(-1);
      if (i2 == 0) {
        PadReset();
        numpads = num_joysticks;
        i1 = (*(uint32_t *)((char *)&joy + 8));
      }
    }
    PadType = arg1;
    if (i1 != 0) {
      PadID = arg2;
    }
    PadInstalled = (int)(i1 != 0);
  }
  else {
    i1 = 0;
  }
  return i1;
}

/* DeviceInit @ 0x08054f20, 6 bytes
 *
 * Empty device initialisation hook; returns 0.
 *
 * Called by: GameInitPads
 *
 * Elecbyte file: src/lib/pad-lib.c
 */
uint32_t DeviceInit(void)

{
  return 1;
}

/* PadReset @ 0x08054f30, 74 bytes
 *
 * Clears the joystick buffer and state flags.
 *
 * Calls: PadBufClear
 * C library: memset
 * Called by: PadDeInit, PadInit
 *
 * Elecbyte file: src/lib/pad-lib.c
 */
uint32_t PadReset(void)

{
  int i1;
  int i2;
  
  memset(padflag,0,0x81);
  if (0 < numpads) {
    i2 = 0;
    i1 = numpads;
    do {
      *(uint32_t *)((int)padbitflag + i2) = 0;
      *(uint32_t *)((int)padoldbitflag + i2) = 0;
      i2 = i2 + 4;
      i1 = i1 + -1;
    } while (i1 != 0);
  }
  PadBufClear();
  return 1;
}

/* PadDeInit @ 0x08054f80, 87 bytes
 *
 * Removes the hit hook, clears the joystick state and removes the Allegro
 * joystick driver.
 *
 * Calls: PadRemoveHitHook, PadReset
 * C library: remove_joystick
 * Called by: GameDeInit, GameInitPads, OptionsScreen
 *
 * Elecbyte file: src/lib/pad-lib.c
 */
void PadDeInit(void)

{
  if (PadInstalled != 0) {
    PadRemoveHitHook();
    PadReset();
    switch(PadType) {
    case 1:
    case 4:
    case 6:
    case 8:
    case 0x14:
    case 0x15:
    case 0x17:
      remove_joystick();
    }
    PadInstalled = 0;
    PadType = 0;
    numpads = 0;
  }
  return;
}

/* PadPoll @ 0x08054fe0, 671 bytes
 *
 * Polls the joysticks (poll_joystick). It converts each pad's stick
 * directions and buttons into up to 32 inputs per pad. Press and release
 * events are queued (PadStuff) and passed to the hit hook (UInpPadHook) for
 * every change since the last poll.
 *
 * Calls: PadStuff
 * C library: poll_joystick
 * Called by: CharacterSelectScreen, ContinueScreenLoop, GameInputUpdate,
 *            GamePlay, KeyConfigScreen, ModeSelect, OptionsScreen, PadGet,
 *            PlayCutscene, UInpGet, VersusScreen
 *
 * Elecbyte file: src/lib/pad-lib.c
 */
int PadPoll(void)

{
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  uint32_t u6;
  uint32_t u7;
  uint32_t u8;
  int stk_2c;
  int stk_28;
  int stk_24;
  int stk_1c;
  int stk_18;
  int stk_14;
  
  stk_18 = 0;
  if (PadInstalled == 0) {
    i4 = 0;
  }
  else {
    if (0 < numpads) {
      i2 = 0;
      i4 = numpads;
      do {
        *(uint32_t *)((int)padoldbitflag + i2) = *(uint32_t *)((int)padbitflag + i2);
        *(uint32_t *)((int)padbitflag + i2) = 0;
        i2 = i2 + 4;
        i4 = i4 + -1;
      } while (i4 != 0);
    }
    switch(PadType) {
    case 1:
    case 4:
    case 6:
    case 8:
    case 0x14:
    case 0x15:
    case 0x17:
      poll_joystick();
      i2 = numpads;
      stk_14 = 0;
      if (0 < numpads) {
        stk_24 = 0;
        stk_28 = 0;
        stk_2c = 0x10;
        i4 = 0;
        do {
          if (*(int *)(joy + stk_24 + 0x18) != 0) {
            *(uint32_t *)((int)padbitflag + i4) = *(uint32_t *)((int)padbitflag + i4) | 8;
          }
          if (*(int *)(joy + stk_24 + 0x1c) != 0) {
            *(uint32_t *)((int)padbitflag + i4) = *(uint32_t *)((int)padbitflag + i4) | 0x10;
          }
          if (*(int *)(joy + stk_24 + 0x28) != 0) {
            *(uint32_t *)((int)padbitflag + i4) = *(uint32_t *)((int)padbitflag + i4) | 2;
          }
          if (*(int *)(joy + stk_2c + 0x1c) != 0) {
            *(uint32_t *)((int)padbitflag + i4) = *(uint32_t *)((int)padbitflag + i4) | 4;
          }
          i5 = 0;
          i1 = *(int *)(joy + stk_24 + 8);
          if (0 < i1) {
            i3 = stk_28 * 4 + 0xf0;
            do {
              if (*(int *)(joy + i3 + 0xc) != 0) {
                *(uint32_t *)((int)padbitflag + i4) =
                     *(uint32_t *)((int)padbitflag + i4) | 0x20 << ((uint8_t)i5 & 0x1f);
              }
              i5 = i5 + 1;
              i3 = i3 + 8;
            } while (i5 < i1);
          }
          stk_14 = stk_14 + 1;
          stk_24 = stk_24 + 0x17c;
          stk_28 = stk_28 + 0x5f;
          stk_2c = stk_2c + 0x17c;
          i4 = i4 + 4;
        } while (stk_14 < i2);
      }
      break;
    default:
      i2 = numpads;
    }
    stk_14 = 0;
    i4 = stk_18;
    if (0 < i2) {
      stk_1c = 0;
      do {
        u7 = *(uint32_t *)((int)padbitflag + stk_1c) ^ *(uint32_t *)((int)padoldbitflag + stk_1c);
        i4 = 0;
        if ((stk_18 != 0) || (u7 != 0)) {
          i4 = 1;
        }
        if (u7 != 0) {
          u6 = 0;
          do {
            if ((u7 & 1) != 0) {
              i2 = u6 + stk_14 * 0x20;
              padflag[i2] =
                   (uint8_t)(*(int *)((int)padbitflag + stk_1c) >> ((uint8_t)u6 & 0x1f)) & 1;
              u8 = u6;
              if ((char)padflag[i2] == 0) {
                u8 = u6 | 0x100;
              }
              if (PadHitHook != (int *)0x0) {
                (*(generic_fn *)PadHitHook)(i2,(int)(char)padflag[i2],u6 & 0xff,u6 & 0xff);
              }
              PadStuff(u8 + stk_14 * 0x20);
            }
            u7 = (int)u7 >> 1;
            u6 = u6 + 1;
            i2 = numpads;
          } while ((int)u6 < 0x20);
        }
        stk_14 = stk_14 + 1;
        stk_1c = stk_1c + 4;
        stk_18 = i4;
      } while (stk_14 < i2);
    }
  }
  return i4;
}

/* PadStuff @ 0x08055280, 84 bytes
 *
 * Appends a joystick event to the 256-entry joystick ring buffer.
 *
 * Parameters:
 *   arg1         uint32_t
 *
 * Called by: PadPoll
 *
 * Elecbyte file: src/lib/pad-lib.c
 * Note: 9 accesses to parts of a variable are written as sized accesses.
 */
void PadStuff(uint32_t arg1)

{
  if (PadInstalled != 0) {
    *(uint32_t *)(padbuf + (*(uint32_t *)((char *)&padbuf + 1028)) * 4) = arg1;
    (*(uint32_t *)((char *)&padbuf + 1028)) = (0xff < (int)((*(uint32_t *)((char *)&padbuf + 1028)) + 1)) - 1 & (*(uint32_t *)((char *)&padbuf + 1028)) + 1;
    if ((*(uint32_t *)((char *)&padbuf + 1028)) == (*(uint32_t *)((char *)&padbuf + 1024))) {
      (*(uint32_t *)((char *)&padbuf + 1024)) = (*(uint32_t *)((char *)&padbuf + 1028)) + 1 & (0xff < (int)((*(uint32_t *)((char *)&padbuf + 1028)) + 1)) - 1;
    }
  }
  return;
}

/* PadGet @ 0x080552e0, 85 bytes
 *
 * Polls until a joystick event is available, then returns it.
 *
 * Calls: PadPoll
 * Called by: CharacterSelectScreen, ContinueScreenLoop, GameInputUpdate,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, PlayCutscene,
 *            VersusScreen
 *
 * Elecbyte file: src/lib/pad-lib.c
 * Note: 8 accesses to parts of a variable are written as sized accesses.
 */
uint32_t PadGet(void)

{
  uint32_t u1;
  
  if (PadInstalled == 0) {
    u1 = 0;
  }
  else {
    if ((*(uint32_t *)((char *)&padbuf + 1024)) == (*(uint32_t *)((char *)&padbuf + 1028))) {
      do {
        PadPoll();
      } while ((*(uint32_t *)((char *)&padbuf + 1024)) == (*(uint32_t *)((char *)&padbuf + 1028)));
    }
    u1 = *(uint32_t *)(padbuf + (*(uint32_t *)((char *)&padbuf + 1024)) * 4);
    (*(uint32_t *)((char *)&padbuf + 1024)) = (*(uint32_t *)((char *)&padbuf + 1024)) + 1 & (0xff < (int)((*(uint32_t *)((char *)&padbuf + 1024)) + 1)) - 1;
  }
  return u1;
}

/* PadHit @ 0x08055340, 34 bytes
 *
 * Returns true when a joystick event is waiting.
 *
 * Called by: CharacterSelectScreen, ContinueScreenLoop, GameInputUpdate,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, PlayCutscene,
 *            VersusScreen
 *
 * Elecbyte file: src/lib/pad-lib.c
 * Note: 2 accesses to parts of a variable are written as sized accesses.
 */
bool PadHit(void)

{
  if (PadInstalled == 0) {
    return false;
  }
  return (*(uint32_t *)((char *)&padbuf + 1024)) != (*(uint32_t *)((char *)&padbuf + 1028));
}

/* PadBufClear @ 0x08055370, 21 bytes
 *
 * Empties the joystick event buffer.
 *
 * Called by: CharacterSelectScreen, ContinueScreenLoop, GamePlay,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, PadReset,
 *            PlayCutscene, VersusScreen
 *
 * Elecbyte file: src/lib/pad-lib.c
 */
void PadBufClear(void)

{
  padbuf[0x404] = 0;
  padbuf[0x405] = 0;
  padbuf[0x406] = 0;
  padbuf[0x407] = 0;
  padbuf[0x400] = 0;
  padbuf[0x401] = 0;
  padbuf[0x402] = 0;
  padbuf[0x403] = 0;
  return;
}

/* PadInstallHitHook @ 0x08055390, 31 bytes
 *
 * Installs the function called on every joystick event. Returns nonzero.
 *
 * Parameters:
 *   arg1         int *
 *
 * Called by: UInpInit
 *
 * Elecbyte file: src/lib/pad-lib.c
 */
uint32_t PadInstallHitHook(int *arg1)

{
  if (PadHitHook != (int *)0x0) {
    return 0;
  }
  PadHitHook = arg1;
  return 1;
}

/* PadRemoveHitHook @ 0x080553b0, 11 bytes
 *
 * Removes the joystick hit hook.
 *
 * Called by: PadDeInit, UInpDeInit, UInpReInit
 *
 * Elecbyte file: src/lib/pad-lib.c
 */
void PadRemoveHitHook(void)

{
  PadHitHook = (int *)0x0;
  return;
}

