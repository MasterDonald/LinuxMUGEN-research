/*
 * kbll-lib.c -- low-level keyboard
 * Allegro keyboard callback, scancode remapping to Elecbyte's raw codes, key
 * flags, the raw key buffer and lock-key LEDs.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/kbll-lib.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"

extern int *KBHitHook __asm__("D_08287160"); /* file-static 0x08287160 */
extern int KBBufferType __asm__("D_08287174"); /* file-static 0x08287174 */
extern int kb_mutex __asm__("D_08287178"); /* file-static 0x08287178 */
extern uint8_t KBAllegRemapMap[464] __asm__("D_08287180"); /* file-static 0x08287180 */
extern uint8_t KBRawNames[1028] __asm__("D_08287480"); /* file-static 0x08287480 */
extern volatile uint8_t KBBuffer[1032] __asm__("D_082a62c0"); /* file-static 0x082a62c0 */
extern volatile uint8_t shiftflags[16] __asm__("D_082a66c8"); /* file-static 0x082a66c8 */

/* KBBufferRawHook @ 0x08054570, 179 bytes
 *
 * Allegro low-level keyboard callback. It converts the scancode (bit 7 =
 * release) into Elecbyte's raw code (KBAllegRemap) and updates `keyflag`. It
 * also tracks the lock keys and queues the raw code (| 0x100 for a release)
 * in the keyboard buffer (KBungetchraw). Calls the installed hit hook
 * (UInpKBHook). The kb_mutex flag guards against reentry.
 *
 * Parameters:
 *   arg1         uint32_t
 *
 * Calls: KBAllegRemap, KBungetchraw
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
uint32_t KBBufferRawHook(uint32_t arg1)

{
  uint32_t entry_EAX;
  uint32_t u1;
  uint32_t stale_EDX;
  uint32_t u2;
  uint32_t u3;
  uint32_t u4;
  
  if (kb_mutex != 0) {
    return entry_EAX;
  }
  u3 = (int)arg1 >> 7 ^ 1;
  kb_mutex = 1;
  u1 = KBAllegRemap(arg1 & 0x7f);
  if (u1 == 0) {
    kb_mutex = 0;
    return entry_EAX;
  }
  keyflag[u1] = (uint8_t)u3;
  if (u1 == 0xde) {
    kb_mutex = 0;
    keypauseflag = keypauseflag ^ 1;
    return entry_EAX;
  }
  u4 = u1;
  if (KBFilterRelease == 0) {
    if (u3 == 0) {
      u4 = u1 | 0x100;
    }
  }
  else {
    u2 = 0;
    if (u3 == 0) goto L_08054603;
  }
  KBungetchraw(u4);
  u2 = stale_EDX;
L_08054603:
  if (KBHitHook != (int *)0x0) {
    (*(generic_fn *)KBHitHook)(u1,u3,u2,u2);
  }
  kb_mutex = 0;
  return entry_EAX;
}

/* KBInit @ 0x08054630, 121 bytes
 *
 * Installs the Allegro keyboard with KBBufferRawHook as its low-level
 * callback. Disables key repeat unless enabled, builds the scancode map and
 * clears the buffer. Returns nonzero on success.
 *
 * Calls: KBLockVarFunc, KBInitAllegRemap, KBBufferClear
 * C library: memset, install_keyboard, set_keyboard_rate
 * Called by: GameInit
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
uint32_t KBInit(void)

{
  uint32_t u1;
  
  if (KBInstalled == 0) {
    memset(keyflag,0,0x101);
    KBLockVarFunc();
    KBHitHook = (int *)0x0;
    install_keyboard();
    keyboard_lowlevel_callback = KBBufferRawHook;
    if (KBRepeat == 0) {
      set_keyboard_rate(0,0);
    }
    KBInitAllegRemap();
    KBBufferClear();
    u1 = 1;
    KBInstalled = 1;
  }
  else {
    u1 = 0;
  }
  return u1;
}

/* KBPoll @ 0x080546b0, 1 bytes
 *
 * Empty: the keyboard is interrupt-driven, there is nothing to poll.
 *
 * Called by: CharacterSelectScreen, ContinueScreenLoop, GameInputUpdate,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, PlayCutscene,
 *            VersusScreen
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
void KBPoll(void)

{
  return;
}

/* KBDeInit @ 0x080546c0, 60 bytes
 *
 * Removes the hit hook, resets the LEDs, clears the keyboard buffer and
 * removes the Allegro keyboard.
 *
 * Calls: KBRemoveHitHook, KBReset, KBBufferClear
 * C library: set_leds, remove_keyboard
 * Called by: GameDeInit
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
void KBDeInit(void)

{
  if (KBInstalled != 0) {
    KBRemoveHitHook();
    KBReset();
    KBBufferClear();
    set_leds(-1);
    remove_keyboard();
    KBInstalled = 0;
  }
  return;
}

/* KBSuspend @ 0x08054700, 11 bytes
 *
 * Detaches the low-level callback while the window is switched away.
 *
 * Called by: SwitchAwayCallback
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
void KBSuspend(void)

{
  keyboard_lowlevel_callback = 0;
  return;
}

/* KBResume @ 0x08054710, 15 bytes
 *
 * Reattaches the low-level callback and resynchronises the key flags
 * (KBRefreshflags).
 *
 * Calls: KBRefreshflags
 * Called by: SwitchBackCallback
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
void KBResume(void)

{
  keyboard_lowlevel_callback = KBBufferRawHook;
  KBRefreshflags();
  return;
}

/* KBRefreshflags @ 0x08054720, 108 bytes
 *
 * Compares Allegro's key[] array with keyflag and queues a press or release
 * for every key whose state changed while input was suspended.
 *
 * Calls: KBAllegRemap, KBungetchraw
 * Called by: KBResume, SwitchBackCallback
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
void KBRefreshflags(void)

{
  uint32_t u1;
  int i2;
  
  i2 = 0;
  do {
    u1 = KBAllegRemap(i2);
    if ((u1 != 0) && (((&key)[i2] != '\0') != (keyflag[u1] != 0))) {
      keyflag[u1] = keyflag[u1] == 0;
      if (keyflag[u1] == 0) {
        u1 = u1 | 0x100;
      }
      KBungetchraw(u1);
    }
    i2 = i2 + 1;
  } while (i2 < 0x73);
  return;
}

/* KBReset @ 0x08054790, 34 bytes
 *
 * Clears the keyboard buffer and state.
 *
 * Calls: KBBufferClear
 * C library: memset
 * Called by: KBDeInit
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
uint32_t KBReset(void)

{
  memset(keyflag,0,0x101);
  KBBufferClear();
  return 1;
}

/* KBRepeatSet @ 0x080547c0, 67 bytes
 *
 * Sets the keyboard auto-repeat delay and rate (set_keyboard_rate); a zero
 * rate disables repeat.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * C library: set_keyboard_rate
 * Called by: GameInit
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
void KBRepeatSet(int arg1,int arg2)

{
  KBRepeat = (int)(arg2 != 0);
  if (KBRepeat == 0) {
    set_keyboard_rate(0,0);
    return;
  }
  set_keyboard_rate(arg1,arg2);
  return;
}

/* KBInstallHitHook @ 0x08054810, 31 bytes
 *
 * Installs the function called on every keyboard event (the unified input
 * layer's hook). Returns nonzero.
 *
 * Parameters:
 *   arg1         int *
 *
 * Called by: UInpInit
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
uint32_t KBInstallHitHook(int *arg1)

{
  if (KBHitHook != (int *)0x0) {
    return 0;
  }
  KBHitHook = arg1;
  return 1;
}

/* KBRemoveHitHook @ 0x08054830, 11 bytes
 *
 * Removes the keyboard hit hook.
 *
 * Called by: KBDeInit, UInpDeInit, UInpReInit
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
void KBRemoveHitHook(void)

{
  KBHitHook = (int *)0x0;
  return;
}

/* KBLEDLockSet @ 0x08054840, 22 bytes
 *
 * Sets whether the lock-key LEDs follow the lock keys (key_led_flag).
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: GameInit
 *
 * Elecbyte file: src/lib/kbll-lib.c
 * Note: 1 accesses to parts of a variable are written as sized accesses.
 */
void KBLEDLockSet(int arg1)

{
  (*(uint32_t *)((char *)&shiftflags + 12)) = arg1;
  key_led_flag = (uint32_t)(arg1 == 1);
  return;
}

/* KBLEDSet @ 0x08054860, 45 bytes
 *
 * Sets the keyboard LEDs: bit 0 scroll, bit 1 num, bit 2 caps lock (Allegro
 * set_leds).
 *
 * Parameters:
 *   arg1         uint32_t
 *
 * C library: set_leds
 * Called by: GameInit
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
void KBLEDSet(uint32_t arg1)

{
  set_leds((arg1 & 1) << 8 | ((uint8_t)arg1 >> 1 & 1) << 9 | ((uint8_t)arg1 >> 2 & 1) << 10);
  return;
}

/* KBBufferChange @ 0x08054890, 14 bytes
 *
 * Selects the keyboard buffer type and clears the buffer.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: KBBufferClear
 * Called by: GameInit
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
void KBBufferChange(int arg1)

{
  KBBufferType = arg1;
  KBBufferClear();
  return;
}

/* KBBufferClear @ 0x080548a0, 40 bytes
 *
 * Empties the 256-entry raw keyboard buffer.
 *
 * Called by: CharacterSelectScreen, ContinueScreenLoop, GameInit,
 *            GamePlay, KBBufferChange, KBDeInit, KBInit, KBReset,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, PlayCutscene,
 *            VersusScreen
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
void KBBufferClear(void)

{
  do {
  } while (kb_mutex != 0);
  KBBuffer[0x404] = 0;
  KBBuffer[0x405] = 0;
  KBBuffer[0x406] = 0;
  KBBuffer[0x407] = 0;
  KBBuffer[0x400] = 0;
  KBBuffer[0x401] = 0;
  KBBuffer[0x402] = 0;
  KBBuffer[0x403] = 0;
  kb_mutex = 0;
  return;
}

/* KBungetchraw @ 0x080548d0, 102 bytes
 *
 * Appends a raw key code to the keyboard ring buffer (oldest entry dropped
 * when full).
 *
 * Parameters:
 *   arg1         uint32_t
 *
 * Called by: KBBufferRawHook, KBRefreshflags
 *
 * Elecbyte file: src/lib/kbll-lib.c
 * Note: 9 accesses to parts of a variable are written as sized accesses.
 */
void KBungetchraw(uint32_t arg1)

{
  *(uint32_t *)(KBBuffer + (*(uint32_t *)((char *)&KBBuffer + 1028)) * 4) = arg1;
  (*(uint32_t *)((char *)&KBBuffer + 1028)) = (*(uint32_t *)((char *)&KBBuffer + 1028)) + 1;
  if (0xff < (int)(*(uint32_t *)((char *)&KBBuffer + 1028))) {
    KBBuffer[0x404] = 0;
    KBBuffer[0x405] = 0;
    KBBuffer[0x406] = 0;
    KBBuffer[0x407] = 0;
  }
  if (((*(uint32_t *)((char *)&KBBuffer + 1028)) == (*(uint32_t *)((char *)&KBBuffer + 1024))) &&
     ((*(uint32_t *)((char *)&KBBuffer + 1024)) = (*(uint32_t *)((char *)&KBBuffer + 1024)) + 1, 0xff < (int)(*(uint32_t *)((char *)&KBBuffer + 1024)))) {
    KBBuffer[0x400] = 0;
    KBBuffer[0x401] = 0;
    KBBuffer[0x402] = 0;
    KBBuffer[0x403] = 0;
  }
  return;
}

/* KBgetchraw @ 0x08054940, 112 bytes
 *
 * Waits for and returns the next raw key code from the keyboard buffer.
 *
 * Called by: CharacterSelectScreen, ContinueScreenLoop, GameInit,
 *            GameInputUpdate, KeyConfigScreen, ModeSelect, OptionsScreen,
 *            PlayCutscene, VersusScreen
 *
 * Elecbyte file: src/lib/kbll-lib.c
 * Note: 6 accesses to parts of a variable are written as sized accesses.
 */
uint32_t KBgetchraw(void)

{
  int i1;
  
  if (KBInstalled != 0) {
    do {
    } while ((*(uint32_t *)((char *)&KBBuffer + 1024)) == (*(uint32_t *)((char *)&KBBuffer + 1028)));
    do {
    } while (kb_mutex != 0);
    i1 = (*(uint32_t *)((char *)&KBBuffer + 1024)) * 4;
    (*(uint32_t *)((char *)&KBBuffer + 1024)) = (*(uint32_t *)((char *)&KBBuffer + 1024)) + 1;
    if (0xff < (int)(*(uint32_t *)((char *)&KBBuffer + 1024))) {
      KBBuffer[0x400] = 0;
      KBBuffer[0x401] = 0;
      KBBuffer[0x402] = 0;
      KBBuffer[0x403] = 0;
    }
    kb_mutex = 0;
    return *(uint32_t *)(KBBuffer + i1);
  }
  return 0;
}

/* KBkbhit @ 0x080549b0, 20 bytes
 *
 * Returns true when a raw key code is waiting in the keyboard buffer.
 *
 * Called by: CharacterSelectScreen, ContinueScreenLoop, GameInputUpdate,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, PlayCutscene,
 *            VersusScreen
 *
 * Elecbyte file: src/lib/kbll-lib.c
 * Note: 2 accesses to parts of a variable are written as sized accesses.
 */
bool KBkbhit(void)

{
  return (*(uint32_t *)((char *)&KBBuffer + 1024)) != (*(uint32_t *)((char *)&KBBuffer + 1028));
}

/* KBRawToChar @ 0x080549d0, 76 bytes
 *
 * Converts a raw key code into its character, applying Shift and Caps Lock
 * (KBRawTable). Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: KBGetCapsLock
 *
 * Elecbyte file: src/lib/kbll-lib.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
int KBRawToChar(int arg1)

{
  uint8_t b1;
  uint32_t stale_var;
  uint32_t u2;
  
  u2 = 0;
  if ((keyflag[0x2a] != 0) || (keyflag[0x36] != 0)) {
    u2 = 1;
  }
  if ((uint8_t)(KBRawTable[arg1] + 0x9f) < 0x1a) {
    b1 = KBGetCapsLock();
    u2 = u2 ^ ZEXT8(b1);
  }
  if (u2 == 0) {
    b1 = KBRawTable[arg1];
  }
  else {
    b1 = KBRawTableShift[arg1];
  }
  return (int)(char)b1;
}

/* KBGetNumLock @ 0x08054a20, 8 bytes
 *
 * Returns the Num Lock state. Not called in this build.
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
uint8_t KBGetNumLock(void)

{
  return shiftflags[3];
}

/* KBGetCapsLock @ 0x08054a30, 8 bytes
 *
 * Returns the Caps Lock state.
 *
 * Called by: KBRawToChar
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
uint8_t KBGetCapsLock(void)

{
  return shiftflags[2];
}

/* KBGetScrollLock @ 0x08054a40, 8 bytes
 *
 * Returns the Scroll Lock state. Not called in this build.
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
uint8_t KBGetScrollLock(void)

{
  return shiftflags[4];
}

/* KBRawToName @ 0x08054a50, 23 bytes
 *
 * Returns the display name of a raw key code (KBRawNames), or an empty
 * string. Used by the key configuration screen.
 *
 * Parameters:
 *   arg1         uint8_t
 *
 * Called by: KeyConfigScreen
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
uint32_t * KBRawToName(uint8_t arg1)

{
  uint32_t *pu1;
  
  pu1 = *(uint32_t **)(KBRawNames + (uint32_t)arg1 * 4);
  if (pu1 == (uint32_t *)0x0) {
    pu1 = (uint32_t *)&d_0827725f;
  }
  return pu1;
}

/* KBInitAllegRemap @ 0x08054a70, 1001 bytes
 *
 * Fills the table that maps Allegro scancodes to Elecbyte's raw key codes
 * (PC set-1 numbering, as in the DOS version).
 *
 * Called by: KBInit
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
void KBInitAllegRemap(void)

{
  KBAllegRemapMap[0xec] = 1;
  KBAllegRemapMap[0xed] = 0;
  KBAllegRemapMap[0xee] = 0;
  KBAllegRemapMap[0xef] = 0;
  KBAllegRemapMap[0x70] = 2;
  KBAllegRemapMap[0x71] = 0;
  KBAllegRemapMap[0x72] = 0;
  KBAllegRemapMap[0x73] = 0;
  KBAllegRemapMap[0x74] = 3;
  KBAllegRemapMap[0x75] = 0;
  KBAllegRemapMap[0x76] = 0;
  KBAllegRemapMap[0x77] = 0;
  KBAllegRemapMap[0x78] = 4;
  KBAllegRemapMap[0x79] = 0;
  KBAllegRemapMap[0x7a] = 0;
  KBAllegRemapMap[0x7b] = 0;
  KBAllegRemapMap[0x7c] = 5;
  KBAllegRemapMap[0x7d] = 0;
  KBAllegRemapMap[0x7e] = 0;
  KBAllegRemapMap[0x7f] = 0;
  KBAllegRemapMap[0x80] = 6;
  KBAllegRemapMap[0x81] = 0;
  KBAllegRemapMap[0x82] = 0;
  KBAllegRemapMap[0x83] = 0;
  KBAllegRemapMap[0x84] = 7;
  KBAllegRemapMap[0x85] = 0;
  KBAllegRemapMap[0x86] = 0;
  KBAllegRemapMap[0x87] = 0;
  KBAllegRemapMap[0x88] = 8;
  KBAllegRemapMap[0x89] = 0;
  KBAllegRemapMap[0x8a] = 0;
  KBAllegRemapMap[0x8b] = 0;
  KBAllegRemapMap[0x8c] = 9;
  KBAllegRemapMap[0x8d] = 0;
  KBAllegRemapMap[0x8e] = 0;
  KBAllegRemapMap[0x8f] = 0;
  KBAllegRemapMap[0x90] = 10;
  KBAllegRemapMap[0x91] = 0;
  KBAllegRemapMap[0x92] = 0;
  KBAllegRemapMap[0x93] = 0;
  KBAllegRemapMap[0x6c] = 0xb;
  KBAllegRemapMap[0x6d] = 0;
  KBAllegRemapMap[0x6e] = 0;
  KBAllegRemapMap[0x6f] = 0;
  KBAllegRemapMap[0xf4] = 0xc;
  KBAllegRemapMap[0xf5] = 0;
  KBAllegRemapMap[0xf6] = 0;
  KBAllegRemapMap[0xf7] = 0;
  KBAllegRemapMap[0xf8] = 0xd;
  KBAllegRemapMap[0xf9] = 0;
  KBAllegRemapMap[0xfa] = 0;
  KBAllegRemapMap[0xfb] = 0;
  KBAllegRemapMap[0xfc] = 0xe;
  KBAllegRemapMap[0xfd] = 0;
  KBAllegRemapMap[0xfe] = 0;
  KBAllegRemapMap[0xff] = 0;
  KBAllegRemapMap[0x100] = 0xf;
  KBAllegRemapMap[0x101] = 0;
  KBAllegRemapMap[0x102] = 0;
  KBAllegRemapMap[0x103] = 0;
  KBAllegRemapMap[0x44] = 0x10;
  KBAllegRemapMap[0x45] = 0;
  KBAllegRemapMap[0x46] = 0;
  KBAllegRemapMap[0x47] = 0;
  KBAllegRemapMap[0x5c] = 0x11;
  KBAllegRemapMap[0x5d] = 0;
  KBAllegRemapMap[0x5e] = 0;
  KBAllegRemapMap[0x5f] = 0;
  KBAllegRemapMap[0x14] = 0x12;
  KBAllegRemapMap[0x15] = 0;
  KBAllegRemapMap[0x16] = 0;
  KBAllegRemapMap[0x17] = 0;
  KBAllegRemapMap[0x48] = 0x13;
  KBAllegRemapMap[0x49] = 0;
  KBAllegRemapMap[0x4a] = 0;
  KBAllegRemapMap[0x4b] = 0;
  KBAllegRemapMap[0x50] = 0x14;
  KBAllegRemapMap[0x51] = 0;
  KBAllegRemapMap[0x52] = 0;
  KBAllegRemapMap[0x53] = 0;
  KBAllegRemapMap[100] = 0x15;
  KBAllegRemapMap[0x65] = 0;
  KBAllegRemapMap[0x66] = 0;
  KBAllegRemapMap[0x67] = 0;
  KBAllegRemapMap[0x54] = 0x16;
  KBAllegRemapMap[0x55] = 0;
  KBAllegRemapMap[0x56] = 0;
  KBAllegRemapMap[0x57] = 0;
  KBAllegRemapMap[0x24] = 0x17;
  KBAllegRemapMap[0x25] = 0;
  KBAllegRemapMap[0x26] = 0;
  KBAllegRemapMap[0x27] = 0;
  KBAllegRemapMap[0x3c] = 0x18;
  KBAllegRemapMap[0x3d] = 0;
  KBAllegRemapMap[0x3e] = 0;
  KBAllegRemapMap[0x3f] = 0;
  KBAllegRemapMap[0x40] = 0x19;
  KBAllegRemapMap[0x41] = 0;
  KBAllegRemapMap[0x42] = 0;
  KBAllegRemapMap[0x43] = 0;
  KBAllegRemapMap[0x104] = 0x1a;
  KBAllegRemapMap[0x105] = 0;
  KBAllegRemapMap[0x106] = 0;
  KBAllegRemapMap[0x107] = 0;
  KBAllegRemapMap[0x108] = 0x1b;
  KBAllegRemapMap[0x109] = 0;
  KBAllegRemapMap[0x10a] = 0;
  KBAllegRemapMap[0x10b] = 0;
  KBAllegRemapMap[0x10c] = 0x1c;
  KBAllegRemapMap[0x10d] = 0;
  KBAllegRemapMap[0x10e] = 0;
  KBAllegRemapMap[0x10f] = 0;
  KBAllegRemapMap[0x1a4] = 0x1d;
  KBAllegRemapMap[0x1a5] = 0;
  KBAllegRemapMap[0x1a6] = 0;
  KBAllegRemapMap[0x1a7] = 0;
  KBAllegRemapMap[4] = 0x1e;
  KBAllegRemapMap[5] = 0;
  KBAllegRemapMap[6] = 0;
  KBAllegRemapMap[7] = 0;
  KBAllegRemapMap[0x4c] = 0x1f;
  KBAllegRemapMap[0x4d] = 0;
  KBAllegRemapMap[0x4e] = 0;
  KBAllegRemapMap[0x4f] = 0;
  KBAllegRemapMap[0x10] = 0x20;
  KBAllegRemapMap[0x11] = 0;
  KBAllegRemapMap[0x12] = 0;
  KBAllegRemapMap[0x13] = 0;
  KBAllegRemapMap[0x18] = 0x21;
  KBAllegRemapMap[0x19] = 0;
  KBAllegRemapMap[0x1a] = 0;
  KBAllegRemapMap[0x1b] = 0;
  KBAllegRemapMap[0x1c] = 0x22;
  KBAllegRemapMap[0x1d] = 0;
  KBAllegRemapMap[0x1e] = 0;
  KBAllegRemapMap[0x1f] = 0;
  KBAllegRemapMap[0x20] = 0x23;
  KBAllegRemapMap[0x21] = 0;
  KBAllegRemapMap[0x22] = 0;
  KBAllegRemapMap[0x23] = 0;
  KBAllegRemapMap[0x28] = 0x24;
  KBAllegRemapMap[0x29] = 0;
  KBAllegRemapMap[0x2a] = 0;
  KBAllegRemapMap[0x2b] = 0;
  KBAllegRemapMap[0x2c] = 0x25;
  KBAllegRemapMap[0x2d] = 0;
  KBAllegRemapMap[0x2e] = 0;
  KBAllegRemapMap[0x2f] = 0;
  KBAllegRemapMap[0x30] = 0x26;
  KBAllegRemapMap[0x31] = 0;
  KBAllegRemapMap[0x32] = 0;
  KBAllegRemapMap[0x33] = 0;
  KBAllegRemapMap[0x110] = 0x27;
  KBAllegRemapMap[0x111] = 0;
  KBAllegRemapMap[0x112] = 0;
  KBAllegRemapMap[0x113] = 0;
  KBAllegRemapMap[0x114] = 0x28;
  KBAllegRemapMap[0x115] = 0;
  KBAllegRemapMap[0x116] = 0;
  KBAllegRemapMap[0x117] = 0;
  KBAllegRemapMap[0xf0] = 0x29;
  KBAllegRemapMap[0xf1] = 0;
  KBAllegRemapMap[0xf2] = 0;
  KBAllegRemapMap[0xf3] = 0;
  KBAllegRemapMap[0x19c] = 0x2a;
  KBAllegRemapMap[0x19d] = 0;
  KBAllegRemapMap[0x19e] = 0;
  KBAllegRemapMap[0x19f] = 0;
  KBAllegRemapMap[0x118] = 0x2b;
  KBAllegRemapMap[0x119] = 0;
  KBAllegRemapMap[0x11a] = 0;
  KBAllegRemapMap[0x11b] = 0;
  KBAllegRemapMap[0x68] = 0x2c;
  KBAllegRemapMap[0x69] = 0;
  KBAllegRemapMap[0x6a] = 0;
  KBAllegRemapMap[0x6b] = 0;
  KBAllegRemapMap[0x60] = 0x2d;
  KBAllegRemapMap[0x61] = 0;
  KBAllegRemapMap[0x62] = 0;
  KBAllegRemapMap[99] = 0;
  KBAllegRemapMap[0xc] = 0x2e;
  KBAllegRemapMap[0xd] = 0;
  KBAllegRemapMap[0xe] = 0;
  KBAllegRemapMap[0xf] = 0;
  KBAllegRemapMap[0x58] = 0x2f;
  KBAllegRemapMap[0x59] = 0;
  KBAllegRemapMap[0x5a] = 0;
  KBAllegRemapMap[0x5b] = 0;
  KBAllegRemapMap[8] = 0x30;
  KBAllegRemapMap[9] = 0;
  KBAllegRemapMap[10] = 0;
  KBAllegRemapMap[0xb] = 0;
  KBAllegRemapMap[0x38] = 0x31;
  KBAllegRemapMap[0x39] = 0;
  KBAllegRemapMap[0x3a] = 0;
  KBAllegRemapMap[0x3b] = 0;
  KBAllegRemapMap[0x34] = 0x32;
  KBAllegRemapMap[0x35] = 0;
  KBAllegRemapMap[0x36] = 0;
  KBAllegRemapMap[0x37] = 0;
  KBAllegRemapMap[0x120] = 0x33;
  KBAllegRemapMap[0x121] = 0;
  KBAllegRemapMap[0x122] = 0;
  KBAllegRemapMap[0x123] = 0;
  KBAllegRemapMap[0x124] = 0x34;
  KBAllegRemapMap[0x125] = 0;
  KBAllegRemapMap[0x126] = 0;
  KBAllegRemapMap[0x127] = 0;
  KBAllegRemapMap[0x128] = 0x35;
  KBAllegRemapMap[0x129] = 0;
  KBAllegRemapMap[0x12a] = 0;
  KBAllegRemapMap[299] = 0;
  KBAllegRemapMap[0x1a0] = 0x36;
  KBAllegRemapMap[0x1a1] = 0;
  KBAllegRemapMap[0x1a2] = 0;
  KBAllegRemapMap[0x1a3] = 0;
  KBAllegRemapMap[0x15c] = 0x37;
  KBAllegRemapMap[0x15d] = 0;
  KBAllegRemapMap[0x15e] = 0;
  KBAllegRemapMap[0x15f] = 0;
  KBAllegRemapMap[0x1ac] = 0x38;
  KBAllegRemapMap[0x1ad] = 0;
  KBAllegRemapMap[0x1ae] = 0;
  KBAllegRemapMap[0x1af] = 0;
  KBAllegRemapMap[300] = 0x39;
  KBAllegRemapMap[0x12d] = 0;
  KBAllegRemapMap[0x12e] = 0;
  KBAllegRemapMap[0x12f] = 0;
  KBAllegRemapMap[0x1c8] = 0x3a;
  KBAllegRemapMap[0x1c9] = 0;
  KBAllegRemapMap[0x1ca] = 0;
  KBAllegRemapMap[0x1cb] = 0;
  KBAllegRemapMap[0xbc] = 0x3b;
  KBAllegRemapMap[0xbd] = 0;
  KBAllegRemapMap[0xbe] = 0;
  KBAllegRemapMap[0xbf] = 0;
  KBAllegRemapMap[0xc0] = 0x3c;
  KBAllegRemapMap[0xc1] = 0;
  KBAllegRemapMap[0xc2] = 0;
  KBAllegRemapMap[0xc3] = 0;
  KBAllegRemapMap[0xc4] = 0x3d;
  KBAllegRemapMap[0xc5] = 0;
  KBAllegRemapMap[0xc6] = 0;
  KBAllegRemapMap[199] = 0;
  KBAllegRemapMap[200] = 0x3e;
  KBAllegRemapMap[0xc9] = 0;
  KBAllegRemapMap[0xca] = 0;
  KBAllegRemapMap[0xcb] = 0;
  KBAllegRemapMap[0xcc] = 0x3f;
  KBAllegRemapMap[0xcd] = 0;
  KBAllegRemapMap[0xce] = 0;
  KBAllegRemapMap[0xcf] = 0;
  KBAllegRemapMap[0xd0] = 0x40;
  KBAllegRemapMap[0xd1] = 0;
  KBAllegRemapMap[0xd2] = 0;
  KBAllegRemapMap[0xd3] = 0;
  KBAllegRemapMap[0xd4] = 0x41;
  KBAllegRemapMap[0xd5] = 0;
  KBAllegRemapMap[0xd6] = 0;
  KBAllegRemapMap[0xd7] = 0;
  KBAllegRemapMap[0xd8] = 0x42;
  KBAllegRemapMap[0xd9] = 0;
  KBAllegRemapMap[0xda] = 0;
  KBAllegRemapMap[0xdb] = 0;
  KBAllegRemapMap[0xdc] = 0x43;
  KBAllegRemapMap[0xdd] = 0;
  KBAllegRemapMap[0xde] = 0;
  KBAllegRemapMap[0xdf] = 0;
  KBAllegRemapMap[0xe0] = 0x44;
  KBAllegRemapMap[0xe1] = 0;
  KBAllegRemapMap[0xe2] = 0;
  KBAllegRemapMap[0xe3] = 0;
  KBAllegRemapMap[0x1c4] = 0x45;
  KBAllegRemapMap[0x1c5] = 0;
  KBAllegRemapMap[0x1c6] = 0;
  KBAllegRemapMap[0x1c7] = 0;
  KBAllegRemapMap[0x1c0] = 0x46;
  KBAllegRemapMap[0x1c1] = 0;
  KBAllegRemapMap[0x1c2] = 0;
  KBAllegRemapMap[0x1c3] = 0;
  KBAllegRemapMap[0xb0] = 0x47;
  KBAllegRemapMap[0xb1] = 0;
  KBAllegRemapMap[0xb2] = 0;
  KBAllegRemapMap[0xb3] = 0;
  KBAllegRemapMap[0xb4] = 0x48;
  KBAllegRemapMap[0xb5] = 0;
  KBAllegRemapMap[0xb6] = 0;
  KBAllegRemapMap[0xb7] = 0;
  KBAllegRemapMap[0xb8] = 0x49;
  KBAllegRemapMap[0xb9] = 0;
  KBAllegRemapMap[0xba] = 0;
  KBAllegRemapMap[0xbb] = 0;
  KBAllegRemapMap[0x160] = 0x4a;
  KBAllegRemapMap[0x161] = 0;
  KBAllegRemapMap[0x162] = 0;
  KBAllegRemapMap[0x163] = 0;
  KBAllegRemapMap[0xa4] = 0x4b;
  KBAllegRemapMap[0xa5] = 0;
  KBAllegRemapMap[0xa6] = 0;
  KBAllegRemapMap[0xa7] = 0;
  KBAllegRemapMap[0xa8] = 0x4c;
  KBAllegRemapMap[0xa9] = 0;
  KBAllegRemapMap[0xaa] = 0;
  KBAllegRemapMap[0xab] = 0;
  KBAllegRemapMap[0xac] = 0x4d;
  KBAllegRemapMap[0xad] = 0;
  KBAllegRemapMap[0xae] = 0;
  KBAllegRemapMap[0xaf] = 0;
  KBAllegRemapMap[0x164] = 0x4e;
  KBAllegRemapMap[0x165] = 0;
  KBAllegRemapMap[0x166] = 0;
  KBAllegRemapMap[0x167] = 0;
  KBAllegRemapMap[0x98] = 0x4f;
  KBAllegRemapMap[0x99] = 0;
  KBAllegRemapMap[0x9a] = 0;
  KBAllegRemapMap[0x9b] = 0;
  KBAllegRemapMap[0x9c] = 0x50;
  KBAllegRemapMap[0x9d] = 0;
  KBAllegRemapMap[0x9e] = 0;
  KBAllegRemapMap[0x9f] = 0;
  KBAllegRemapMap[0xa0] = 0x51;
  KBAllegRemapMap[0xa1] = 0;
  KBAllegRemapMap[0xa2] = 0;
  KBAllegRemapMap[0xa3] = 0;
  KBAllegRemapMap[0x94] = 0x52;
  KBAllegRemapMap[0x95] = 0;
  KBAllegRemapMap[0x96] = 0;
  KBAllegRemapMap[0x97] = 0;
  KBAllegRemapMap[0x168] = 0x53;
  KBAllegRemapMap[0x169] = 0;
  KBAllegRemapMap[0x16a] = 0;
  KBAllegRemapMap[0x16b] = 0;
  KBAllegRemapMap[0xe4] = 0x57;
  KBAllegRemapMap[0xe5] = 0;
  KBAllegRemapMap[0xe6] = 0;
  KBAllegRemapMap[0xe7] = 0;
  KBAllegRemapMap[0xe8] = 0x58;
  KBAllegRemapMap[0xe9] = 0;
  KBAllegRemapMap[0xea] = 0;
  KBAllegRemapMap[0xeb] = 0;
  KBAllegRemapMap[0x16c] = 0x9c;
  KBAllegRemapMap[0x16d] = 0;
  KBAllegRemapMap[0x16e] = 0;
  KBAllegRemapMap[0x16f] = 0;
  KBAllegRemapMap[0x1a8] = 0x9d;
  KBAllegRemapMap[0x1a9] = 0;
  KBAllegRemapMap[0x1aa] = 0;
  KBAllegRemapMap[0x1ab] = 0;
  KBAllegRemapMap[0x158] = 0xb5;
  KBAllegRemapMap[0x159] = 0;
  KBAllegRemapMap[0x15a] = 0;
  KBAllegRemapMap[0x15b] = 0;
  KBAllegRemapMap[0x1b0] = 0xb8;
  KBAllegRemapMap[0x1b1] = 0;
  KBAllegRemapMap[0x1b2] = 0;
  KBAllegRemapMap[0x1b3] = 0;
  KBAllegRemapMap[0x138] = 199;
  KBAllegRemapMap[0x139] = 0;
  KBAllegRemapMap[0x13a] = 0;
  KBAllegRemapMap[0x13b] = 0;
  KBAllegRemapMap[0x150] = 200;
  KBAllegRemapMap[0x151] = 0;
  KBAllegRemapMap[0x152] = 0;
  KBAllegRemapMap[0x153] = 0;
  KBAllegRemapMap[0x140] = 0xc9;
  KBAllegRemapMap[0x141] = 0;
  KBAllegRemapMap[0x142] = 0;
  KBAllegRemapMap[0x143] = 0;
  KBAllegRemapMap[0x148] = 0xcb;
  KBAllegRemapMap[0x149] = 0;
  KBAllegRemapMap[0x14a] = 0;
  KBAllegRemapMap[0x14b] = 0;
  KBAllegRemapMap[0x14c] = 0xcd;
  KBAllegRemapMap[0x14d] = 0;
  KBAllegRemapMap[0x14e] = 0;
  KBAllegRemapMap[0x14f] = 0;
  KBAllegRemapMap[0x13c] = 0xcf;
  KBAllegRemapMap[0x13d] = 0;
  KBAllegRemapMap[0x13e] = 0;
  KBAllegRemapMap[0x13f] = 0;
  KBAllegRemapMap[0x154] = 0xd0;
  KBAllegRemapMap[0x155] = 0;
  KBAllegRemapMap[0x156] = 0;
  KBAllegRemapMap[0x157] = 0;
  KBAllegRemapMap[0x144] = 0xd1;
  KBAllegRemapMap[0x145] = 0;
  KBAllegRemapMap[0x146] = 0;
  KBAllegRemapMap[0x147] = 0;
  KBAllegRemapMap[0x130] = 0xd2;
  KBAllegRemapMap[0x131] = 0;
  KBAllegRemapMap[0x132] = 0;
  KBAllegRemapMap[0x133] = 0;
  KBAllegRemapMap[0x134] = 0xd3;
  KBAllegRemapMap[0x135] = 0;
  KBAllegRemapMap[0x136] = 0;
  KBAllegRemapMap[0x137] = 0;
  KBAllegRemapMap[0x174] = 0xde;
  KBAllegRemapMap[0x175] = 0;
  KBAllegRemapMap[0x176] = 0;
  KBAllegRemapMap[0x177] = 0;
  return;
}

/* KBLockVarFunc @ 0x08054e60, 1 bytes
 *
 * Empty: under DOS this locked the keyboard handler's memory; nothing to do
 * on Linux.
 *
 * Called by: KBInit
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
void KBLockVarFunc(void)

{
  return;
}

/* KBAllegRemap @ 0x08054e70, 12 bytes
 *
 * Maps an Allegro scancode to Elecbyte's raw key code through the remap
 * table.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: KBBufferRawHook, KBRefreshflags
 *
 * Elecbyte file: src/lib/kbll-lib.c
 */
uint32_t KBAllegRemap(int arg1)

{
  return *(uint32_t *)(KBAllegRemapMap + arg1 * 4);
}

