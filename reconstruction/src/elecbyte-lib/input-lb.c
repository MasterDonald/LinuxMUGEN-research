/*
 * input-lb.c -- unified input
 * Merges keyboard and joystick events into one stream of "uinp" codes with
 * state flags and an optional remap table; generic int ring buffers.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/input-lb.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"

extern int *uinpkeymap __asm__("D_08287134"); /* file-static 0x08287134 */
extern volatile uint8_t uinpbuf[16] __asm__("D_08287138"); /* file-static 0x08287138 */
extern volatile void *uinpbufptr __asm__("D_08287148"); /* file-static 0x08287148 */

/* UInpKBHook @ 0x08053ee0, 116 bytes
 *
 * Keyboard hook of the unified input layer. It maps the scancode through the
 * optional uinp key map, updates the uinp state flag (bit 0 = held) and
 * queues the press/release event (UInpStuff).
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         int
 *
 * Calls: UInpStuff
 *
 * Elecbyte file: src/lib/input-lb.c
 */
uint32_t UInpKBHook(uint32_t arg1,int arg2)

{
  uint8_t b1;
  uint8_t b2;
  uint32_t entry_EAX;
  uint32_t u3;
  
  if (uinpkeymap != (int *)0x0) {
    arg1 = uinpkeymap[arg1];
  }
  b1 = uinpflag[arg1];
  if (arg2 == 0) {
    b2 = uinpflag[arg1] & 0xfe;
  }
  else {
    b2 = uinpflag[arg1] | 1;
  }
  uinpflag[arg1] = b2;
  if ((b1 == 0) != (uinpflag[arg1] == 0)) {
    if (uinpflag[arg1] == 0) {
      arg1 = arg1 | 0x1000;
    }
    u3 = UInpStuff(arg1);
    return u3;
  }
  return entry_EAX;
}

/* UInpPadHook @ 0x08053f60, 118 bytes
 *
 * Joystick hook of the unified input layer: the same as UInpKBHook for
 * joystick codes (offset by 0x100).
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Calls: UInpStuff
 *
 * Elecbyte file: src/lib/input-lb.c
 */
void UInpPadHook(int arg1,int arg2)

{
  uint8_t b1;
  uint8_t b2;
  uint32_t u3;
  
  u3 = arg1 + 0x100;
  if (uinpkeymap != (int *)0x0) {
    u3 = uinpkeymap[u3];
  }
  b1 = uinpflag[u3];
  if (arg2 == 0) {
    b2 = uinpflag[u3] & 0xfd;
  }
  else {
    b2 = uinpflag[u3] | 2;
  }
  uinpflag[u3] = b2;
  if ((b1 == 0) != (uinpflag[u3] == 0)) {
    if (uinpflag[u3] == 0) {
      u3 = u3 | 0x1000;
    }
    UInpStuff(u3);
    return;
  }
  return;
}

/* UInpInit @ 0x08053fe0, 136 bytes
 *
 * Starts the unified input layer: creates its 256-entry event ring, installs
 * the keyboard and joystick hooks, clears all state flags and refreshes them
 * from the devices. Returns nonzero on success.
 *
 * Calls: IntCircBufIsValid, IntCircBufInit, KBInstallHitHook,
 *        PadInstallHitHook, UInpBufClear, UInpRefreshFlags
 * C library: memset
 * Called by: GameInit, UInpReInit
 *
 * Elecbyte file: src/lib/input-lb.c
 * Note: 2 byte results widened with ZEXT8 (upper bytes are zero).
 */
uint32_t UInpInit(void)

{
  bool b1;
  uint32_t stale_var;
  uint32_t stale_var_00;
  int i2;
  
  b1 = IntCircBufIsValid(uinpbufptr);
  if ((((ZEXT8(b1) != 0) ||
       (b1 = IntCircBufInit(uinpbufptr,0x100), ZEXT8(b1) != 0)) &&
      (i2 = KBInstallHitHook(UInpKBHook), i2 != 0)) &&
     (i2 = PadInstallHitHook(UInpPadHook), i2 != 0)) {
    memset(uinpflag,0,0x181);
    UInpBufClear();
    UInpRefreshFlags();
    return 1;
  }
  return 0;
}

/* UInpReInit @ 0x08054070, 21 bytes
 *
 * Removes the hooks and runs UInpInit again (after the joystick
 * configuration changes).
 *
 * Calls: KBRemoveHitHook, PadRemoveHitHook, UInpInit
 * Called by: GameInitPads, GameInputSetup
 *
 * Elecbyte file: src/lib/input-lb.c
 */
uint32_t UInpReInit(void)

{
  uint32_t u1;
  
  KBRemoveHitHook();
  PadRemoveHitHook();
  u1 = UInpInit();
  return u1;
}

/* UInpDeInit @ 0x08054090, 36 bytes
 *
 * Removes the hooks, drops the key map and frees the event ring.
 *
 * Calls: KBRemoveHitHook, PadRemoveHitHook, UInpResetKeyMap,
 *        IntCircBufDeInit
 * Called by: GameDeInit
 *
 * Elecbyte file: src/lib/input-lb.c
 */
void UInpDeInit(void)

{
  KBRemoveHitHook();
  PadRemoveHitHook();
  UInpResetKeyMap();
  IntCircBufDeInit(uinpbufptr);
  return;
}

/* UInpRefreshFlags @ 0x080540c0, 217 bytes
 *
 * Rebuilds the uinp state flags from the current keyboard (keyflag) and
 * joystick (padflag) state, through the key map if one is set.
 *
 * C library: memset
 * Called by: CharacterSelectScreen, ContinueScreenLoop, GamePlay,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, PlayCutscene,
 *            SwitchBackCallback, UInpInit, VersusScreen
 *
 * Elecbyte file: src/lib/input-lb.c
 */
void UInpRefreshFlags(void)

{
  uint8_t *pb1;
  int *pi2;
  uint8_t b3;
  int i2;
  int j;
  
  memset(uinpflag,0,0x181);
  if (uinpkeymap == (int *)0x0) {
    i2 = 0;
    do {
      uinpflag[i2] = uinpflag[i2] | keyflag[i2] != 0;
      i2 = i2 + 1;
    } while (i2 < 0x100);
    j = 0;
    i2 = 0x100;
    do {
      b3 = uinpflag[i2];
      if (keyflag[i2 + 0x20] != 0) {
        b3 = b3 | 2;
      }
      j = j + 1;
      uinpflag[i2] = b3;
      i2 = i2 + 1;
    } while (j < 0x80);
  }
  else {
    i2 = 0;
    do {
      pi2 = uinpkeymap + i2;
      pb1 = keyflag + i2;
      i2 = i2 + 1;
      uinpflag[*pi2] = uinpflag[*pi2] | *pb1 != 0;
      pi2 = uinpkeymap;
    } while (i2 < 0x100);
    i2 = 0;
    do {
      j = i2 + 0x100;
      b3 = uinpflag[pi2[j]];
      if (padflag[i2] != 0) {
        b3 = b3 | 2;
      }
      i2 = i2 + 1;
      uinpflag[pi2[j]] = b3;
    } while (i2 < 0x80);
  }
  return;
}

/* UInpSetKeyMap @ 0x080541a0, 68 bytes
 *
 * Installs a 0x180-entry uinp remapping table (copied). Returns 0 if
 * allocation fails.
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * C library: calloc
 * Called by: GameInputSetup
 *
 * Elecbyte file: src/lib/input-lb.c
 */
uint32_t UInpSetKeyMap(uint32_t *arg1)

{
  int i1;
  int *pi2;
  
  if ((uinpkeymap == (int *)0x0) && (uinpkeymap = calloc(4,0x181), uinpkeymap == (int *)0x0)) {
    return 0;
  }
  pi2 = uinpkeymap;
  for (i1 = 0x180; i1 != 0; i1 = i1 + -1) {
    *pi2 = *arg1;
    arg1 = arg1 + 1;
    pi2 = pi2 + 1;
  }
  return 1;
}

/* UInpGetKeyMap @ 0x080541f0, 61 bytes
 *
 * Copies the current uinp remapping table out. Not called in this build.
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * Elecbyte file: src/lib/input-lb.c
 */
uint32_t UInpGetKeyMap(uint32_t *arg1)

{
  uint32_t u1;
  int *pi2;
  int i3;
  
  if (uinpkeymap == (int *)0x0) {
    i3 = 0x17f;
    pi2 = arg1 + 0x17f;
    do {
      *pi2 = i3;
      pi2 = pi2 + -1;
      i3 = i3 + -1;
    } while (-1 < i3);
    u1 = 0;
  }
  else {
    pi2 = uinpkeymap;
    for (i3 = 0x180; i3 != 0; i3 = i3 + -1) {
      *arg1 = *pi2;
      pi2 = pi2 + 1;
      arg1 = arg1 + 1;
    }
    u1 = 1;
  }
  return u1;
}

/* UInpResetKeyMap @ 0x08054230, 38 bytes
 *
 * Frees the uinp remapping table (identity mapping again).
 *
 * C library: free
 * Called by: UInpDeInit
 *
 * Elecbyte file: src/lib/input-lb.c
 */
void UInpResetKeyMap(void)

{
  int *ptr;
  
  ptr = uinpkeymap;
  if (uinpkeymap != (int *)0x0) {
    uinpkeymap = (int *)0x0;
    free(ptr);
  }
  return;
}

/* UInpStuff @ 0x08054260, 49 bytes
 *
 * Queues one uinp event in the unified input ring.
 *
 * Parameters:
 *   arg1         uint32_t
 *
 * Calls: IntCircBufStuff
 * Called by: UInpKBHook, UInpPadHook
 *
 * Elecbyte file: src/lib/input-lb.c
 */
uint32_t UInpStuff(uint32_t arg1)

{
  uint32_t entry_EAX;
  uint32_t stale_EAX;
  
  if ((PadInstalled != 0) || (KBInstalled != 0)) {
    IntCircBufStuff(uinpbufptr,arg1);
    entry_EAX = stale_EAX;
  }
  return entry_EAX;
}

/* UInpGet @ 0x080542a0, 90 bytes
 *
 * Waits for and returns the next uinp event, polling the joystick while the
 * ring is empty. Returns 0 when no input device is installed.
 *
 * Calls: IntCircBufIsEmpty, PadPoll, IntCircBufGet
 * Called by: CharacterSelectScreen, ContinueScreenLoop, GameInputUpdate,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, PlayCutscene,
 *            VersusScreen
 *
 * Elecbyte file: src/lib/input-lb.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
uint32_t UInpGet(void)

{
  bool b1;
  uint32_t u2;
  uint32_t stale_var;
  
  if ((PadInstalled == 0) && (KBInstalled == 0)) {
    u2 = 0;
  }
  else {
    while( true ) {
      b1 = IntCircBufIsEmpty((int)uinpbufptr);
      if (ZEXT8(b1) == 0) break;
      if (PadInstalled != 0) {
        PadPoll();
      }
    }
    u2 = IntCircBufGet(uinpbufptr);
  }
  return u2;
}

/* UInpHit @ 0x08054300, 63 bytes
 *
 * Returns true when a uinp event is waiting.
 *
 * Calls: IntCircBufIsEmpty
 * Called by: CharacterSelectScreen, ContinueScreenLoop, GameInputUpdate,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, PlayCutscene,
 *            VersusScreen
 *
 * Elecbyte file: src/lib/input-lb.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
bool UInpHit(void)

{
  bool b1;
  uint32_t stale_var;
  
  if ((PadInstalled == 0) && (KBInstalled == 0)) {
    b1 = false;
  }
  else {
    b1 = IntCircBufIsEmpty((int)uinpbufptr);
    b1 = ZEXT8(b1) == 0;
  }
  return b1;
}

/* UInpBufClear @ 0x08054340, 19 bytes
 *
 * Discards all queued uinp events.
 *
 * Calls: IntCircBufClear
 * Called by: CharacterSelectScreen, ContinueScreenLoop, GamePlay,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, PlayCutscene,
 *            UInpInit, VersusScreen
 *
 * Elecbyte file: src/lib/input-lb.c
 */
void UInpBufClear(void)

{
  IntCircBufClear((int)uinpbufptr);
  return;
}

/* KBToUInp @ 0x08054360, 83 bytes
 *
 * Converts a key configuration value (keyboard scancode, bit 0x100 =
 * release) into a uinp code. 0 and 256 become 0x180 (no key). Asserts
 * "uinp_ch <= 256" (src/lib/input-lb.c).
 *
 * Parameters:
 *   keycode      uint32_t
 *
 * C library: __assert_fail
 * Called by: CharacterSelectScreenKey, GameInputSetup, KBIIs6Button,
 *            KBIIs6ButtonOrStart, KBIKeyMap, KBIMenuGetKey,
 *            KBIRefreshKeyflags, TeamReorderAll, TrainingMenuUpdate
 * Messages:
 *   "uinp_ch <= 256"
 *
 * Elecbyte file: src/lib/input-lb.c
 */
uint32_t KBToUInp(uint32_t keycode)

{
  uint32_t u1;
  
  u1 = keycode & 0xfffffeff;
  if (0x100 < (int)u1) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("uinp_ch <= 256","src/lib/input-lb.c",0x130,"KBToUInp");
  }
  if ((u1 == 0x100) || (u1 == 0)) {
    u1 = 0x180;
  }
  else if ((keycode & 0x100) != 0) {
    u1 = u1 | 0x1000;
  }
  return u1;
}

/* PadToUInp @ 0x080543c0, 90 bytes
 *
 * Converts a joystick input code (bit 0x100 = release) into a uinp code
 * (+0x100). Asserts "uinp_ch <= (0x20*4)". Not called in this build.
 *
 * Parameters:
 *   arg1         uint32_t
 *
 * C library: __assert_fail
 * Messages:
 *   "uinp_ch <= (0x20*4)"
 *
 * Elecbyte file: src/lib/input-lb.c
 */
uint32_t PadToUInp(uint32_t arg1)

{
  uint32_t u1;
  
  u1 = arg1 & 0xfffffeff;
  if (0x80 < (int)u1) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("uinp_ch <= (0x20*4)","src/lib/input-lb.c",0x140,"PadToUInp");
  }
  if (u1 == 0x80) {
    u1 = 0x180;
  }
  else if ((u1 != 0) && (u1 = u1 + 0x100, (arg1 & 0x100) != 0)) {
    u1 = u1 | 0x1000;
  }
  return u1;
}

/* IntCircBufInit @ 0x08054420, 80 bytes
 *
 * Creates an int ring buffer of `size` entries. Header: [0] storage, [1]
 * read index, [2] write index, [3] size. Returns false if allocation fails.
 *
 * Parameters:
 *   buf          uint32_t *
 *   size         int
 *
 * C library: calloc
 * Called by: GameVarInit, UInpInit
 *
 * Elecbyte file: src/lib/input-lb.c
 */
bool IntCircBufInit(uint32_t *buf,int size)

{
  void *pv1;
  
  *buf = 0;
  buf[1] = 0;
  buf[2] = 0;
  buf[3] = 0;
  pv1 = calloc(1,size * 4);
  *buf = pv1;
  if (pv1 != (void *)0x0) {
    buf[3] = size;
  }
  return pv1 != (void *)0x0;
}

/* IntCircBufDeInit @ 0x08054470, 56 bytes
 *
 * Frees an int ring buffer's storage and clears the header.
 *
 * Parameters:
 *   buf          uint32_t *
 *
 * C library: free
 * Called by: GameVarDeInit, UInpDeInit
 *
 * Elecbyte file: src/lib/input-lb.c
 */
uint32_t IntCircBufDeInit(uint32_t *buf)

{
  uint32_t entry_ECX;
  
  if ((void *)*buf != (void *)0x0) {
    free((void *)*buf);
  }
  *buf = 0;
  buf[1] = 0;
  buf[2] = 0;
  buf[3] = 0;
  return entry_ECX;
}

/* IntCircBufIsValid @ 0x080544b0, 14 bytes
 *
 * Returns true when the ring buffer has storage.
 *
 * Parameters:
 *   buf          int *
 *
 * Called by: UInpInit
 *
 * Elecbyte file: src/lib/input-lb.c
 */
bool IntCircBufIsValid(int *buf)

{
  return *buf != 0;
}

/* IntCircBufStuff @ 0x080544c0, 60 bytes
 *
 * Appends a value to an int ring buffer; when full, the oldest value is
 * dropped.
 *
 * Parameters:
 *   buf          int *
 *   value        uint32_t
 *
 * Called by: GameInputUpdate, UInpStuff
 *
 * Elecbyte file: src/lib/input-lb.c
 */
void IntCircBufStuff(int *buf,uint32_t value)

{
  uint32_t u1;
  
  *(uint32_t *)(*buf + buf[2] * 4) = value;
  u1 = buf[2] + 1U & (buf[3] <= (int)(buf[2] + 1U)) - 1;
  buf[2] = u1;
  if (u1 == buf[1]) {
    buf[1] = u1 + 1 & (buf[3] <= (int)(u1 + 1)) - 1;
  }
  return;
}

/* IntCircBufGet @ 0x08054500, 61 bytes
 *
 * Removes and returns the oldest value, or 0 if the buffer is empty.
 *
 * Parameters:
 *   buf          int *
 *
 * Calls: IntCircBufIsEmpty
 * Called by: GameUpdate, UInpGet
 *
 * Elecbyte file: src/lib/input-lb.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
uint32_t IntCircBufGet(int *buf)

{
  bool b1;
  uint32_t stale_var;
  uint32_t u2;
  uint32_t u3;
  
  b1 = IntCircBufIsEmpty((int)buf);
  if (ZEXT8(b1) == 0) {
    u2 = *(uint32_t *)(*buf + buf[1] * 4);
    u3 = buf[1] + 1;
    buf[1] = u3 & (buf[3] <= (int)u3) - 1;
  }
  else {
    u2 = 0;
  }
  return u2;
}

/* IntCircBufIsEmpty @ 0x08054540, 16 bytes
 *
 * Returns true when read index == write index.
 *
 * Parameters:
 *   buf          int
 *
 * Called by: IntCircBufGet, UInpGet, UInpHit
 *
 * Elecbyte file: src/lib/input-lb.c
 */
bool IntCircBufIsEmpty(int buf)

{
  return *(int *)(buf + 4) == *(int *)(buf + 8);
}

/* IntCircBufClear @ 0x08054550, 19 bytes
 *
 * Empties an int ring buffer (read index = write index).
 *
 * Parameters:
 *   buf          int
 *
 * Called by: GameInputUpdate, UInpBufClear
 *
 * Elecbyte file: src/lib/input-lb.c
 */
void IntCircBufClear(int buf)

{
  *(uint32_t *)(buf + 8) = 0;
  *(uint32_t *)(buf + 4) = 0;
  return;
}

