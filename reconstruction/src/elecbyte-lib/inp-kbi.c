/*
 * inp-kbi.c -- player key buffers
 * Per-player key event buffers and held-key states, with facing-dependent
 * left/right swapping; the AI presses keys through the same buffers.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/inp-kbi.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* KBIClearKeyflags @ 0x08053970, 29 bytes
 *
 * Clears the state of the 12 player keys (all released), without generating
 * events.
 *
 * Parameters:
 *   kbi          int
 *
 * Called by: PlayerKBUpdate
 *
 * Elecbyte file: src/lib/inp-kbi.c
 */
void KBIClearKeyflags(int kbi)

{
  uint32_t *pu1;
  int i2;
  
  i2 = 0xb;
  pu1 = (uint32_t *)(kbi + 0x7c);
  do {
    *pu1 = 0;
    pu1 = pu1 + 1;
    i2 = i2 + -1;
  } while (-1 < i2);
  return;
}

/* KBIRefreshKeyflags @ 0x08053990, 117 bytes
 *
 * Synchronises the player's key state with the current input flags. For
 * every player key whose state differs from the real device state (key
 * configuration -> uinp -> uinpflag), it generates a press or release event
 * marked as a refresh (0x20). Called at round reset and every frame.
 *
 * Parameters:
 *   kbi          int
 *   keycfg       int
 *
 * Calls: KBIFlippedKey, KBToUInp, KBIStuffBuf
 * Called by: GameRoundReset, PlayerKBUpdate
 *
 * Elecbyte file: src/lib/inp-kbi.c
 */
void KBIRefreshKeyflags(int kbi,int keycfg)

{
  int i1;
  uint32_t u2;
  uint32_t uinp;
  uint32_t u4;
  
  u4 = 1;
  do {
    u2 = KBIFlippedKey(kbi,u4);
    uinp = KBToUInp(*(uint32_t *)(keycfg + u4 * 4));
    i1 = *(int *)(kbi + 0x78 + u2 * 4);
    if ((i1 != 0) != (uinpflag[uinp] != 0)) {
      KBIStuffBuf(kbi,((i1 != 0) - 1 & 0xfffffff0) + 0x10 | u4 | 0x20);
    }
    u4 = u4 + 1;
  } while ((int)u4 < 0xd);
  return;
}

/* KBISetFlip @ 0x08053a10, 150 bytes
 *
 * Changes the player's facing for input purposes. When the facing changes
 * while a horizontal direction is held, it emits events that move the held
 * direction from "forward" to "back" (or the reverse), so commands see the
 * turn correctly. Then it stores the new flip flag.
 *
 * Parameters:
 *   kbi          int
 *   flip         int
 *
 * Calls: KBIFlippedKey, KBIStuffBuf
 * Called by: HelperMake, PlayerReset, PlayerTurnAround
 *
 * Elecbyte file: src/lib/inp-kbi.c
 */
void KBISetFlip(int kbi,int flip)

{
  uint32_t u1;
  
  if (flip == *(int *)(kbi + 0xb8)) {
    return;
  }
  if ((*(int *)(kbi + 0xb4) == 0) &&
     ((*(int *)(kbi + 0x88) == 0 || (*(int *)(kbi + 0x80) == 0)))) {
    u1 = KBIFlippedKey(kbi,4);
    if (*(int *)(kbi + 0x78 + u1 * 4) == 0) {
      u1 = KBIFlippedKey(kbi,2);
      if (*(int *)(kbi + 0x78 + u1 * 4) == 0) goto L_08053a9c;
      KBIStuffBuf(kbi,0x32);
      u1 = 0x24;
    }
    else {
      KBIStuffBuf(kbi,0x34);
      u1 = 0x22;
    }
    KBIStuffBuf(kbi,u1);
  }
L_08053a9c:
  *(int *)(kbi + 0xb8) = flip;
  return;
}

/* KBIUpdate @ 0x08053ab0, 55 bytes
 *
 * Feeds one uinp event to a player: converts it with the player's key
 * configuration (KBIKeyMap) and, if it is one of that player's keys, adds it
 * to the player's key buffer (KBIStuffBuf).
 *
 * Parameters:
 *   keycfg       int
 *   kbi          int
 *   uinp         uint32_t
 *
 * Calls: KBIKeyMap, KBIStuffBuf
 * Called by: GameUpdate
 *
 * Elecbyte file: src/lib/inp-kbi.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 */
uint32_t KBIUpdate(int keycfg,int kbi,uint32_t uinp)

{
  uint32_t u1;
  uint32_t u2;
  uint32_t saved_EBX;
  
  if (uinp != 0) {
    u1 = KBIKeyMap(keycfg,uinp);
    if (u1 != 0) {
      u2 = KBIStuffBuf(kbi,u1);
      return u2;
    }
  }
  return saved_EBX;
}

/* KBIStuffBuf @ 0x08053af0, 36 bytes
 *
 * Adds a key event to the player's buffer after swapping the horizontal
 * directions if the player faces left (KBIFlippedKey).
 *
 * Parameters:
 *   kbi          int
 *   code         uint32_t
 *
 * Calls: KBIFlippedKey, KBIStuffBufNoFlip
 * Called by: KBIClearAll, KBIRefreshKeyflags, KBISetFlip, KBIUpdate,
 *            TrainingMenuUpdate
 *
 * Elecbyte file: src/lib/inp-kbi.c
 */
uint32_t KBIStuffBuf(int kbi,uint32_t code)

{
  uint32_t u1;
  uint32_t u2;
  
  u1 = KBIFlippedKey(kbi,code);
  u2 = KBIStuffBufNoFlip(kbi,u1);
  return u2;
}

/* KBIStuffBufNoFlip @ 0x08053b20, 104 bytes
 *
 * Adds a key event to the player's 30-entry key ring buffer and updates the
 * key's held state. Ignored while the buffer is disabled (+0xb4). Also used
 * by the AI to "press" keys for computer-controlled players.
 *
 * Parameters:
 *   kbi          int
 *   code         uint32_t
 *
 * Called by: AIForNormalAttack, AIForNormalGuard, AIForNormalIdle,
 *            AIForNormalMove, AIForNormalRandom, AIForTrainingMode,
 *            AIKBReleaseAll, AIKBReleaseAllExcept, AIKBReleaseDir,
 *            AIKBReleaseDirExcept, KBIStuffBuf, PlayerAI
 *
 * Elecbyte file: src/lib/inp-kbi.c
 */
uint32_t KBIStuffBufNoFlip(int kbi,uint32_t code)

{
  uint32_t entry_EAX;
  uint32_t u1;
  
  if (((code & 0xf) != 0) && (*(int *)(kbi + 0xb4) == 0)) {
    *(uint32_t *)(kbi + *(int *)(kbi + 0xb0) * 4) = code;
    u1 = *(int *)(kbi + 0xb0) + 1;
    entry_EAX = (0x1d < (int)u1) - 1 & u1;
    *(uint32_t *)(kbi + 0xb0) = entry_EAX;
    if (entry_EAX == *(uint32_t *)(kbi + 0xac)) {
      u1 = entry_EAX + 1;
      entry_EAX = (0x1d < (int)u1) - 1;
      *(uint32_t *)(kbi + 0xac) = u1 & entry_EAX;
    }
    *(uint32_t *)(kbi + 0x78 + (code & 0xf) * 4) = (code >> 4 ^ 1) & 1;
  }
  return entry_EAX;
}

/* KBIGetch @ 0x08053b90, 48 bytes
 *
 * Takes the oldest event from the player's key buffer; returns 0 when the
 * buffer is empty.
 *
 * Parameters:
 *   kbi          int
 *
 * Called by: PlayerAI, PlayerKBUpdate
 *
 * Elecbyte file: src/lib/inp-kbi.c
 */
uint32_t KBIGetch(int kbi)

{
  int i1;
  uint32_t u2;
  
  i1 = *(int *)(kbi + 0xac);
  if (i1 == *(int *)(kbi + 0xb0)) {
    u2 = 0;
  }
  else {
    u2 = *(uint32_t *)(kbi + i1 * 4);
    *(uint32_t *)(kbi + 0xac) = i1 + 1U & (0x1d < (int)(i1 + 1U)) - 1;
  }
  return u2;
}

/* KBIClearAll @ 0x08053bc0, 57 bytes
 *
 * Generates a release event for every player key that is held.
 *
 * Parameters:
 *   kbi          int
 *
 * Calls: KBIStuffBuf
 *
 * Elecbyte file: src/lib/inp-kbi.c
 */
uint32_t KBIClearAll(int kbi)

{
  int *pi1;
  uint32_t u2;
  
  u2 = 1;
  pi1 = (int *)(kbi + 0x7c);
  do {
    if (*pi1 != 0) {
      KBIStuffBuf(kbi,u2 | 0x10);
    }
    u2 = u2 + 1;
    pi1 = pi1 + 1;
  } while ((int)u2 < 0xd);
  return 1;
}

/* KBIIs6Button @ 0x08053c00, 60 bytes
 *
 * Returns nonzero when uinp code `uinp` is one of the six attack buttons in
 * key configuration `keycfg`.
 *
 * Parameters:
 *   uinp         uint32_t
 *   keycfg       int
 *
 * Calls: KBToUInp
 * Called by: KBIIs6ButtonOrStart
 *
 * Elecbyte file: src/lib/inp-kbi.c
 */
uint32_t KBIIs6Button(uint32_t uinp,int keycfg)

{
  uint32_t uinp2;
  int i2;
  
  i2 = 5;
  do {
    uinp2 = KBToUInp(*(uint32_t *)(keycfg + i2 * 4));
    if (uinp == uinp2) {
      return 1;
    }
    i2 = i2 + 1;
  } while (i2 < 0xb);
  return 0;
}

/* KBIIs6ButtonOrStart @ 0x08053c40, 62 bytes
 *
 * KBIIs6Button, also accepting the start key. Used by the training menu.
 *
 * Parameters:
 *   uinp         uint32_t
 *   keycfg       int
 *
 * Calls: KBIIs6Button, KBToUInp
 * Called by: TrainingMenuUpdate
 *
 * Elecbyte file: src/lib/inp-kbi.c
 */
bool KBIIs6ButtonOrStart(uint32_t uinp,int keycfg)

{
  int i1;
  uint32_t uinp2;
  bool b3;
  
  i1 = KBIIs6Button(uinp,keycfg);
  if (i1 == 0) {
    uinp2 = KBToUInp(*(uint32_t *)(keycfg + 0x2c));
    b3 = uinp == uinp2;
  }
  else {
    b3 = true;
  }
  return b3;
}

/* KBIKeyMap @ 0x08053c80, 99 bytes
 *
 * Converts a uinp event into a player key event using key configuration
 * `keycfg`. Returns key number | 0x10 for a release, or 0 when the input is
 * not one of that player's keys.
 *
 * Parameters:
 *   keycfg       int
 *   uinp         uint32_t
 *
 * Calls: KBToUInp
 * Called by: KBIUpdate
 *
 * Elecbyte file: src/lib/inp-kbi.c
 */
uint32_t KBIKeyMap(int keycfg,uint32_t uinp)

{
  uint32_t uinp2;
  uint32_t u2;
  uint32_t u3;
  uint32_t u4;
  
  u4 = 0;
  if ((uinp & 0x1000) != 0) {
    u4 = 0x10;
  }
  u2 = 1;
  while ((u3 = 0, (int)u2 < 0xd &&
         (uinp2 = KBToUInp(*(uint32_t *)(keycfg + u2 * 4)), u3 = u2,
         (uinp & 0xffffefff) != uinp2))) {
    u2 = u2 + 1;
  }
  if (u3 == 0) {
    u4 = 0;
  }
  else {
    u4 = u4 | u3;
  }
  return u4;
}

/* KBIFlippedKey @ 0x08053cf0, 50 bytes
 *
 * Swaps player keys 2 and 4 (right and left) when the player's flip flag is
 * set, so key 2 means "forward"; other keys are returned unchanged.
 *
 * Parameters:
 *   kbi          int
 *   key2         uint32_t  (key)
 *
 * Called by: KBIRefreshKeyflags, KBISetFlip, KBIStuffBuf
 *
 * Elecbyte file: src/lib/inp-kbi.c
 */
uint32_t KBIFlippedKey(int kbi,uint32_t key2)

{
  if (*(int *)(kbi + 0xb8) != 0) {
    if ((key2 & 0xf) == 4) {
      key2 = key2 & 0xfffffff0 | 2;
    }
    else if ((key2 & 0xf) == 2) {
      key2 = key2 & 0xfffffff0 | 4;
    }
  }
  return key2;
}

