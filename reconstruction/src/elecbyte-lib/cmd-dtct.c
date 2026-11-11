/*
 * cmd-dtct.c -- command detection
 * Per-player command buffers and the matcher that recognises the .cmd key
 * sequences (charges, holds, releases, strict order, time limits) for the
 * `command` trigger.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/cmd-dtct.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* KBUpdateHold @ 0x0804f140, 29 bytes
 *
 * Stores in the player's command state (+0x650) the bit set of player keys
 * currently held (KBGetHoldFlag). Commands use it for "hold" elements
 * ("/F").
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Calls: KBGetHoldFlag
 * Called by: PlayerKBUpdate
 *
 * Elecbyte file: src/lib/cmd-dtct.c
 */
void KBUpdateHold(int arg1,int arg2)

{
  uint32_t u1;
  
  u1 = KBGetHoldFlag(arg2);
  *(uint32_t *)(arg1 + 0x650) = u1;
  return;
}

/* KBFillBuffer @ 0x0804f160, 571 bytes
 *
 * Records one player key event in the command buffer of `cmdbuf`. The
 * event's KBI code is mapped to command bits (KBKeyMap), and the press time
 * of each key is remembered. For a release, the hold duration (now - press
 * time) is stored, which the "~30a"-style charge elements test. For
 * direction events, the full current direction state is rebuilt so diagonals
 * are recorded as one entry. The entry is then added with KBTimeStuffBuf.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         uint32_t
 *   arg4         int
 *
 * Calls: KBKeyMap, KBKeyIndex, KBTimeStuffBuf
 * Called by: PlayerKBUpdate
 *
 * Elecbyte file: src/lib/cmd-dtct.c
 */
uint32_t KBFillBuffer(int arg1,int arg2,uint32_t arg3,int arg4)

{
  uint32_t u1;
  uint32_t u2;
  int i3;
  uint32_t u4;
  uint32_t u5;
  uint32_t u6;
  uint32_t stk_18;
  int stk_14;
  
  stk_14 = 0;
  stk_18 = 0;
  u2 = KBKeyMap(arg1,arg3);
  if ((u2 == 0) && (arg3 != 0)) {
    return 0;
  }
  u5 = u2 >> 0x14;
  u6 = u2 >> 0x10 & 1;
  i3 = KBKeyIndex(u2);
  if ((i3 != -1) && (u6 == 0)) {
    *(int *)(arg2 + 0x60c + i3 * 4) = arg4;
  }
  if ((i3 != -1) && (u6 != 0)) {
    stk_14 = arg4 - *(int *)(arg2 + 0x60c + i3 * 4);
  }
  if (u2 == 0) goto L_0804f318;
  u4 = u2 & 0xffff;
  if (u4 != 0x2000) {
    if (u4 < 0x2001) {
      if (u4 != 0x1000) goto L_0804f318;
    }
    else if ((u4 != 0x4000) && (u4 != 0x8000)) goto L_0804f318;
  }
  u4 = ((*(int *)(arg1 + 0x7c) != 0) - 1 & 0xfffff000) + 0x1000;
  if (*(int *)(arg1 + 0x80) != 0) {
    u4 = u4 | 0x2000;
  }
  if (*(int *)(arg1 + 0x88) != 0) {
    u4 = u4 | 0x8000;
  }
  if (*(int *)(arg1 + 0x84) != 0) {
    u4 = u4 | 0x4000;
  }
  u1 = *(uint32_t *)(arg2 + 0x654);
  if (u4 != u1) {
    u2 = u4;
    if (u6 == 0) {
      if ((u1 != 0) && (u1 != u4)) {
        KBTimeStuffBuf(arg2,u1 | 0x10000,arg4,stk_14);
        stk_18 = 1;
      }
      *(uint32_t *)(arg2 + 0x654) = u4;
    }
    else {
      if ((u1 != 0) && (u1 != u4)) {
        KBTimeStuffBuf(arg2,u1 | 0x10000,arg4,stk_14);
        stk_18 = 1;
      }
      if ((u5 & 1) != 0) {
        u2 = u4 | 0x100000;
      }
      *(uint32_t *)(arg2 + 0x654) = u4;
    }
  }
L_0804f318:
  if ((u2 & 0x9f000) == 0) {
    if (u2 == 0) {
      u5 = *(uint32_t *)(arg2 + 0x658);
      if (u5 != 0) {
        *(uint32_t *)(arg2 + 0x658) = 0;
        u2 = u5;
      }
    }
    else if (*(uint32_t *)(arg2 + 0x658) == 0) {
      *(uint32_t *)(arg2 + 0x658) = u2;
      u2 = 0;
    }
    else {
      *(uint32_t *)(arg2 + 0x658) = *(uint32_t *)(arg2 + 0x658) | u2;
      u2 = 0;
    }
  }
  if ((short)u2 != 0) {
    KBTimeStuffBuf(arg2,u2,arg4,stk_14);
    stk_18 = 1;
  }
  return stk_18;
}

/* KBClearCommandValidTimes @ 0x0804f3a0, 17 bytes
 *
 * Clears the 128 per-command "remaining valid time" bytes: no command is
 * active afterwards. Called when a hit, reversal or projectile contact
 * lands, so buffered commands do not carry over.
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * Called by: Player1HitP2, Player1ReverseP2, PlayerCheckProjHit,
 *            PlayerDropBoundTargets, PlayerGetHit, PlayerGetHitG,
 *            PlayerKBUpdate, PlayerReset
 *
 * Elecbyte file: src/lib/cmd-dtct.c
 */
void KBClearCommandValidTimes(uint32_t *arg1)

{
  int i1;
  
  for (i1 = 0x20; i1 != 0; i1 = i1 + -1) {
    *arg1 = 0;
    arg1 = arg1 + 1;
  }
  return;
}

/* KBClearCommandLastTimes @ 0x0804f3c0, 20 bytes
 *
 * Clears the 128 per-command "last completion time" words. Called by
 * PlayerReset.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: PlayerReset
 *
 * Elecbyte file: src/lib/cmd-dtct.c
 */
void KBClearCommandLastTimes(int arg1)

{
  int i1;
  uint32_t *pu2;
  
  pu2 = (uint32_t *)(arg1 + 0x80);
  for (i1 = 0x80; i1 != 0; i1 = i1 + -1) {
    *pu2 = 0;
    pu2 = pu2 + 1;
  }
  return;
}

/* KBCountdownCommandValidTimes @ 0x0804f3e0, 50 bytes
 *
 * Ages all 128 command valid-time counters by `dec` ticks, clamping at
 * `floor`. A command stays "active" for the CMD file's buffer.time after it
 * was completed.
 *
 * Parameters:
 *   arg1         int
 *   arg2         char
 *   arg3         int
 *
 * Called by: PlayerKBUpdate
 *
 * Elecbyte file: src/lib/cmd-dtct.c
 */
void KBCountdownCommandValidTimes(int arg1,char arg2,int arg3)

{
  uint8_t b1;
  int i2;
  
  i2 = 0;
  do {
    if ((*(char *)(i2 + arg1) != '\0') &&
       (b1 = *(char *)(i2 + arg1) - arg2, *(uint8_t *)(i2 + arg1) = b1,
       (int)(uint32_t)b1 < arg3)) {
      *(char *)(i2 + arg1) = (char)arg3;
    }
    i2 = i2 + 1;
  } while (i2 < 0x80);
  return;
}

/* KBCommandIsValid @ 0x0804f420, 18 bytes
 *
 * Returns true when command number `cmd` is active (its valid-time counter
 * is not zero). This is the test behind the `command = "name"` trigger.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Called by: SCtrlTrigEval
 *
 * Elecbyte file: src/lib/cmd-dtct.c
 */
bool KBCommandIsValid(int arg1,int arg2)

{
  return *(char *)(arg2 + arg1) != '\0';
}

/* KBGetCommand @ 0x0804f440, 34 bytes
 *
 * KBGetCommandSpecial with mask 0xf (all command classes).
 *
 * Parameters:
 *   arg1         int
 *   arg2         int *
 *   arg3         int
 *   arg4         uint32_t
 *
 * Calls: KBGetCommandSpecial
 *
 * Elecbyte file: src/lib/cmd-dtct.c
 */
void KBGetCommand(int arg1,int *arg2,int arg3,uint32_t arg4)

{
  KBGetCommandSpecial(arg1,arg2,arg3,arg4,0xf);
  return;
}

/* KBGetCommandSpecial @ 0x0804f470, 309 bytes
 *
 * Runs command detection on the buffer entries added since the last call.
 * For each new entry, every command of the list whose class bits intersect
 * `mask` is matched against the buffer (PatternMatch). A match newer than
 * the command's last completion sets its valid time (the command's
 * buffer.time) and records the completion time. The read position then
 * catches up with the buffer.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int *
 *   arg3         int
 *   arg4         uint32_t
 *   arg5         uint32_t
 *
 * Calls: PatternMatch
 * Called by: KBGetCommand, PlayerKBUpdate
 *
 * Elecbyte file: src/lib/cmd-dtct.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x20 bytes, 1
 *       variables), because their address is taken.
 */
uint32_t KBGetCommandSpecial(int arg1,int *arg2,int arg3,uint32_t arg4,uint32_t arg5)

{
  int i1;
  int i2;
  int i3;
  int j;
  unsigned char frame[0x20] __attribute__((aligned(16)));
#define stk_14 (*(int *)(frame + 0xc))
  
  j = *(int *)(arg3 + 0x608);
  if (j == *(int *)(arg3 + 0x604)) {
    i2 = arg2[2];
  }
  else {
    do {
      i3 = 0;
      *(uint32_t *)(arg3 + 0x608) = j + 1U & (0x7f < (int)(j + 1U)) - 1;
      i2 = arg2[2];
      if (0 < i2) {
        j = 0;
        do {
          if ((*(uint32_t *)(*arg2 + 0x14 + j) & arg5) != 0) {
            i2 = PatternMatch(arg3,(int *)(j + *arg2),&stk_14);
            if (i2 != 0) {
              i1 = *(int *)(*arg2 + 0x10 + j);
              i2 = i1 * 4 + 0x80;
              if (*(int *)(i2 + arg1) < stk_14) {
                *(uint8_t *)(i1 + arg1) = *(uint8_t *)(*arg2 + 0xc + j);
                *(uint32_t *)(i2 + arg1) = arg4;
              }
            }
            i2 = arg2[2];
          }
          i3 = i3 + 1;
          j = j + 0x18;
        } while (i3 < i2);
      }
      j = *(int *)(arg3 + 0x608);
    } while (j != *(int *)(arg3 + 0x604));
  }
  j = 0;
  if (0 < i2) {
    i3 = 0;
    do {
      i1 = *arg2;
      if ((((*(uint32_t *)(i1 + 0x14 + i3) & arg5) != 0) &&
          ((*(uint8_t *)(*(int *)(i1 + i3) + 2) & 2) != 0)) && (*(int *)(i1 + 4 + i3) == 1)
         ) {
        i2 = PatternMatch(arg3,(int *)(i3 + i1),&stk_14);
        if (i2 != 0) {
          i2 = *(int *)(*arg2 + 0x10 + i3);
          *(uint8_t *)(i2 + arg1) = 1;
          *(uint32_t *)(arg1 + 0x80 + i2 * 4) = arg4;
        }
        i2 = arg2[2];
      }
      j = j + 1;
      i3 = i3 + 0x18;
    } while (j < i2);
  }
  return 0;
}
#undef stk_14

/* KBGetHoldFlag @ 0x0804f5b0, 170 bytes
 *
 * Converts a player's held keys into command bits: directions to
 * 0x1000-0x8000, the buttons and start to the low bits.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: KBUpdateHold
 *
 * Elecbyte file: src/lib/cmd-dtct.c
 */
uint32_t KBGetHoldFlag(int arg1)

{
  uint32_t u1;
  
  u1 = ((*(int *)(arg1 + 0x7c) != 0) - 1 & 0xfffff000) + 0x1000;
  if (*(int *)(arg1 + 0x80) != 0) {
    u1 = u1 | 0x2000;
  }
  if (*(int *)(arg1 + 0x84) != 0) {
    u1 = u1 | 0x4000;
  }
  if (*(int *)(arg1 + 0x88) != 0) {
    u1 = u1 | 0x8000;
  }
  if (*(int *)(arg1 + 0x8c) != 0) {
    u1 = u1 | 0x10;
  }
  if (*(int *)(arg1 + 0x90) != 0) {
    u1 = u1 | 0x20;
  }
  if (*(int *)(arg1 + 0x94) != 0) {
    u1 = u1 | 0x40;
  }
  if (*(int *)(arg1 + 0x98) != 0) {
    u1 = u1 | 0x80;
  }
  if (*(int *)(arg1 + 0x9c) != 0) {
    u1 = u1 | 0x100;
  }
  if (*(int *)(arg1 + 0xa0) != 0) {
    u1 = u1 | 0x200;
  }
  if (*(int *)(arg1 + 0xa4) != 0) {
    u1 = u1 | 0x400;
  }
  return u1;
}

/* KBKeyMap @ 0x0804f660, 152 bytes
 *
 * Converts one KBI key event into command bits. The key number selects the
 * bit (1..4 directions, 5.. buttons). Bit 0x10 of the event (release)
 * becomes 0x10000, and bit 0x20 (state refresh rather than a real key event)
 * becomes 0x100000.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         uint32_t
 *
 * Called by: KBFillBuffer
 *
 * Elecbyte file: src/lib/cmd-dtct.c
 */
uint32_t KBKeyMap(uint32_t arg1,uint32_t arg2)

{
  uint32_t u1;
  uint32_t u2;
  
  u1 = 0;
  u2 = 0;
  if (arg2 != 0) {
    if ((arg2 & 0x10) != 0) {
      u2 = 0x10000;
    }
    if ((arg2 & 0x20) != 0) {
      u2 = u2 | 0x100000;
    }
    switch(arg2 & 0xf) {
    case 1:
      u1 = 0x1000;
      break;
    case 2:
      u1 = 0x2000;
      break;
    case 3:
      u1 = 0x4000;
      break;
    case 4:
      u1 = 0x8000;
      break;
    case 5:
      u1 = 0x10;
      break;
    case 6:
      u1 = 0x20;
      break;
    case 7:
      u1 = 0x40;
      break;
    case 8:
      u1 = 0x80;
      break;
    case 9:
      u1 = 0x100;
      break;
    case 10:
      u1 = 0x200;
      break;
    case 0xb:
      u1 = 0x400;
    }
    u1 = u1 | u2;
  }
  return u1;
}

/* KBKeyIndex @ 0x0804f700, 28 bytes
 *
 * Returns the number (0-15) of the lowest set bit of a command-bit value, or
 * -1. Used to index the per-key press times.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: KBFillBuffer
 *
 * Elecbyte file: src/lib/cmd-dtct.c
 */
int KBKeyIndex(int arg1)

{
  int i2;
  
  i2 = 0;
  do {
    if ((arg1 >> ((uint8_t)i2 & 0x1f) & 1U) != 0) {
      return i2;
    }
    i2 = i2 + 1;
  } while (i2 < 0x10);
  return -1;
}

/* CharMatch @ 0x0804f720, 270 bytes
 *
 * Tests whether command buffer entry `idx` satisfies one command element. It
 * compares the key bits, the release flag, the "direction only" ('$') rule
 * and the minimum hold time of charge elements ('~30'). Returns nonzero on a
 * match.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         uint32_t
 *
 * Called by: PatternMatch
 *
 * Elecbyte file: src/lib/cmd-dtct.c
 */
uint32_t CharMatch(int arg1,int arg2,uint32_t arg3)

{
  uint32_t u1;
  uint32_t u2;
  uint32_t u3;
  bool b4;
  
  if ((arg3 & 0x20000) == 0) {
    u3 = *(uint32_t *)(arg2 * 4 + arg1);
    if ((((int)arg3 >> 0x16) * 4 <= *(int *)(arg1 + 0x400 + arg2 * 4)) &&
       ((u3 & 0x110000) != 0x100000)) {
      if ((arg3 & 0x8f000) == 0) {
        if ((((arg3 & 0xfff) != 0) && ((arg3 & 0x10000) == (u3 & 0x10000))) &&
           ((u3 & arg3 & 0xffff) == (arg3 & 0xffff))) {
          return 1;
        }
      }
      else {
        u1 = arg3 & 0x1ffff;
        if ((arg3 & 0x40000) == 0) {
          b4 = u3 == u1;
        }
        else {
          if ((u3 & u1) != u1) goto L_0804f829;
          b4 = (u3 & 0x10000) == (arg3 & 0x10000);
        }
L_0804f7fb:
        if (b4) goto L_0804f791;
      }
    }
L_0804f829:
    u2 = 0;
  }
  else {
    u3 = arg3 & 0x8f000;
    if (u3 == 0) {
      if (((arg3 & 0xfff) == 0) || ((arg3 & 0xfff & *(uint32_t *)(arg1 + 0x650) & 0xfff) == 0))
      goto L_0804f829;
    }
    else {
      u1 = *(uint32_t *)(arg1 + 0x650) & 0x8f000;
      if (((arg3 & 0x80000) == 0) || (u1 != 0)) {
        if ((arg3 & 0x40000) == 0) {
          b4 = u1 == u3;
        }
        else {
          b4 = (u1 & u3) == u3;
        }
        goto L_0804f7fb;
      }
    }
L_0804f791:
    u2 = 1;
  }
  return u2;
}

/* PatternMatch @ 0x0804f830, 300 bytes
 *
 * Matches a whole command (its list of elements) backwards against the
 * command buffer, from the newest entry. Every element must be found in
 * order (CharMatch), and the whole sequence must fit within the command's
 * time limit. Strict elements ('>') forbid other keys in between. On
 * success, returns nonzero and stores the tick of the first element through
 * `start_time`.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int *
 *   arg3         uint32_t *
 *
 * Calls: CharMatch
 * Called by: KBGetCommandSpecial
 *
 * Elecbyte file: src/lib/cmd-dtct.c
 */
uint32_t PatternMatch(int arg1,int *arg2,uint32_t *arg3)

{
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  uint32_t u7;
  uint32_t stk_1c;
  int stk_14;
  
  i1 = *arg2;
  i2 = arg2[2];
  stk_1c = 0;
  i6 = arg2[1] + -1;
  i5 = *(int *)(arg1 + 0x608);
  if (i5 < 1) {
    stk_14 = *(int *)(arg1 + 0x3fc);
    u7 = *(uint32_t *)(i1 + i6 * 8);
    i3 = 0x7f;
  }
  else {
    stk_14 = *(int *)(arg1 + 0x1fc + i5 * 4);
    u7 = *(uint32_t *)(i1 + i6 * 8);
    i3 = i5 + -1;
  }
  i3 = CharMatch(arg1,i3,u7);
  if (i3 != 0) {
    i3 = i5 * 4 + 0x200;
    do {
      if (i5 == *(int *)(arg1 + 0x600)) {
        return 0;
      }
      i3 = i3 + -4;
      i5 = i5 + -1;
      if (i5 < 0) {
        i3 = 0x3fc;
        i5 = 0x7f;
      }
      if ((i2 < stk_14 - *(int *)(arg1 + i3)) &&
         ((*(uint8_t *)(i1 + 2 + i6 * 8) & 2) == 0)) {
        return 0;
      }
      i4 = CharMatch(arg1,i5,*(uint32_t *)(i1 + i6 * 8));
      if (i4 == 0) {
        if ((stk_1c & 1) != 0) {
          return 0;
        }
        stk_1c = 0;
      }
      else {
        stk_1c = *(uint32_t *)(i1 + 4 + i6 * 8);
        i6 = i6 + -1;
        if (i6 < 0) {
          if (arg3 != (uint32_t *)0x0) {
            *arg3 = *(uint32_t *)(i3 + arg1);
          }
          return 1;
        }
      }
    } while ((stk_14 - *(int *)(arg1 + i3) <= i2) ||
            ((*(uint8_t *)(i1 + 2 + i6 * 8) & 2) == 0));
  }
  return 0;
}

/* KBTimeStuffBuf @ 0x0804f960, 114 bytes
 *
 * Appends (key bits, time, hold time) to a player's 128-entry command ring
 * buffer, dropping the oldest entry when it is full.
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t
 *   arg3         uint32_t
 *   arg4         uint32_t
 *
 * Called by: KBFillBuffer
 *
 * Elecbyte file: src/lib/cmd-dtct.c
 */
void KBTimeStuffBuf(int arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4)

{
  uint32_t u1;
  
  *(uint32_t *)(arg1 + *(int *)(arg1 + 0x604) * 4) = arg2;
  *(uint32_t *)(arg1 + 0x200 + *(int *)(arg1 + 0x604) * 4) = arg3;
  *(uint32_t *)(arg1 + 0x400 + *(int *)(arg1 + 0x604) * 4) = arg4;
  u1 = *(int *)(arg1 + 0x604) + 1;
  u1 = (0x7f < (int)u1) - 1 & u1;
  *(uint32_t *)(arg1 + 0x604) = u1;
  if (u1 == *(uint32_t *)(arg1 + 0x600)) {
    *(uint32_t *)(arg1 + 0x600) = u1 + 1 & (0x7f < (int)(u1 + 1)) - 1;
  }
  return;
}

