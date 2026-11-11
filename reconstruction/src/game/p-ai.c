/*
 * p-ai.c -- computer AI
 * The computer opponent: decision making, movement, attacks and guarding by
 * pressing keys, attack learning, and AI data files.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/p-ai.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* PlayerAIInit @ 0x080a5d70, 86 bytes
 *
 * Creates a player's AI state set and sets its AI level.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Calls: AIStateSetInit, PlayerAISetLevel
 * Called by: PlayerNew
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
uint32_t PlayerAIInit(int arg1,int arg2)

{
  int i1;
  
  if (arg2 != 0) {
    *(uint32_t *)(arg1 + 0x2dac) = 1;
    i1 = AIStateSetInit(arg1 + 0x2db0);
    if (i1 == 0) {
      return 0;
    }
  }
  *(uint32_t *)(arg1 + 0x33e4) = 0xffffffff;
  PlayerAISetLevel(arg1,4);
  return 1;
}

/* PlayerAIDeInit @ 0x080a5dd0, 40 bytes
 *
 * Frees a player's AI state set.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: AIStateSetDeInit
 * Called by: PlayerFree
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void PlayerAIDeInit(int arg1)

{
  int i1;
  uint32_t *pu2;
  
  AIStateSetDeInit((uint32_t *)(arg1 + 0x2db0));
  pu2 = (uint32_t *)(arg1 + 0x262c);
  for (i1 = 0x37e; i1 != 0; i1 = i1 + -1) {
    *pu2 = 0;
    pu2 = pu2 + 1;
  }
  return;
}

/* AILearnDataLoad @ 0x080a5e00, 640 bytes
 *
 * Loads AI learning data from a file into an AI state set. The file has a
 * 64-byte header with the "ElecbyteAIB" signature and the engine version,
 * followed by the learned entries. Errors: "Error reading file header",
 * "Incorrect MUGEN version for AI: %i.", "Out of AI learning space". Returns
 * nonzero on success.
 *
 * Parameters:
 *   arg1         char *
 *   arg2         uint32_t *
 *
 * Globals read: errmsg
 * Calls: AIStateSetDeInit, AIStateSetInit, ArrayAdd
 * C library: fopen, fread, sprintf, fclose
 * Called by: PlayerDefLoadPtr, PlayerDefLoadZip
 * Messages:
 *   "Error reading file header"
 *   "Out of AI learning space"
 *   "Incorrect MUGEN version for AI: %i.%02i.%02i"
 *   "Incorrect AI version"
 *   "Not an AI file"
 *
 * Elecbyte file: src/mugen/p-ai.c
 * Note: 4 accesses to parts of a variable are written as sized accesses.
 * Note: Locals live in `frame`, laid out as on the original stack (0x520 bytes,
 *       6 variables), because their address is taken.
 */
uint32_t AILearnDataLoad(char *arg1,uint32_t *arg2)

{
  int array;
  int i2;
  FILE *stream;
  size_t s3;
  int index;
  uint8_t *pb5;
  int i3;
  uint8_t *pb7;
  bool b8;
  bool b9;
  char *format;
  unsigned char frame[0x520] __attribute__((aligned(16)));
#define stk_520 (*(int *)(frame + 0x0))
#define stk_51c (*(uint8_t (*)[516])(frame + 0x4))
#define stk_318 (*(uint32_t *)(frame + 0x208))
#define stk_5c (*(uint8_t (*)[12])(frame + 0x4c4))
#define stk_50 (*(int *)(frame + 0x4d0))
#define stk_4c (*(uint32_t *)(frame + 0x4d4))
  
  AIStateSetDeInit(arg2);
  i2 = AIStateSetInit((int)arg2);
  if ((i2 != 0) && (stream = fopen(arg1,"rb"), stream != (FILE *)0x0)) {
    s3 = fread(stk_5c,0x40,1,stream);
    b8 = false;
    b9 = s3 == 0;
    if (b9) {
      format = "Error reading file header";
L_080a6041:
      sprintf((char *)(g + G_ERRMSG),format);
    }
    else {
      i2 = 0xc;
      pb5 = stk_5c;
      pb7 = (uint8_t *)"ElecbyteAIB";
      do {
        if (i2 == 0) break;
        i2 = i2 + -1;
        b8 = *pb5 < *pb7;
        b9 = *pb5 == *pb7;
        pb5 = pb5 + 1;
        pb7 = pb7 + 1;
      } while (b9);
      if ((!b8 && !b9) == b8) {
        if (stk_50 == 0x100) {
          if ((((stk_4c & 0xffff) == MUGENDATE_Y) && ((uint32_t)(*(uint8_t *)((char *)&stk_4c + 2)) == MUGENDATE_M)) &&
             (i2 = 0, (uint32_t)(*(uint8_t *)((char *)&stk_4c + 3)) == MUGENDATE_D)) {
            for (; i2 < 2; i2 = i2 + 1) {
              array = arg2[i2];
              s3 = fread(&stk_520,4,1,stream);
              if (s3 == 0) goto L_080a604d;
              i3 = 0;
              if (0 < stk_520) {
                do {
                  s3 = fread(stk_51c,0x4b4,1,stream);
                  if (s3 == 0) goto L_080a604d;
                  index = ArrayAdd(array,stk_51c,0,stk_318);
                  if (index == -1) {
                    format = "Out of AI learning space";
                    goto L_080a6041;
                  }
                  i3 = i3 + 1;
                } while (i3 < stk_520);
              }
            }
            s3 = fread(arg2 + 2,0x100,1,stream);
            if (s3 != 0) {
              fclose(stream);
              return 1;
            }
          }
          else {
            sprintf((char *)(g + G_ERRMSG),"Incorrect MUGEN version for AI: %i.%02i.%02i",
                    stk_4c & 0xffff,(uint32_t)(*(uint8_t *)((char *)&stk_4c + 2)),(uint32_t)(*(uint8_t *)((char *)&stk_4c + 3)));
          }
        }
        else {
          sprintf((char *)(g + G_ERRMSG),"Incorrect AI version",stream,stream);
        }
      }
      else {
        sprintf((char *)(g + G_ERRMSG),"Not an AI file",i2,i2);
      }
    }
L_080a604d:
    fclose(stream);
  }
  return 0;
}
#undef stk_520
#undef stk_51c
#undef stk_318
#undef stk_5c
#undef stk_50
#undef stk_4c

/* AILearnDataSave @ 0x080a6080, 329 bytes
 *
 * Writes an AI state set's learning data to a file (header and entries).
 *
 * Parameters:
 *   arg1         char *
 *   arg2         int
 *
 * Calls: ArrayScanFirst, ArrayScanNext
 * C library: fopen, memcpy, fwrite, fclose
 * Called by: PlayerCacheClear, PlayerCacheLoad
 *
 * Elecbyte file: src/mugen/p-ai.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x60 bytes, 5
 *       variables), because their address is taken.
 */
uint32_t AILearnDataSave(char *arg1,int arg2)

{
  int array;
  FILE *stream;
  size_t s2;
  void *item;
  int i2;
  uint32_t *pu4;
  unsigned char frame[0x60] __attribute__((aligned(16)));
#define stk_60 (*(uint32_t *)(frame + 0x0))
#define stk_5c (*(uint32_t (*)[4])(frame + 0x4))
#define stk_4c (*(uint16_t *)(frame + 0x14))
#define stk_4a (*(uint8_t *)(frame + 0x16))
#define stk_49 (*(uint8_t *)(frame + 0x17))
  
  i2 = 0;
  do {
    if (*(int *)(arg2 + i2 * 4) == 0) {
      return 0;
    }
    i2 = i2 + 1;
  } while (i2 < 2);
  stream = fopen(arg1,"wb");
  if (stream != (FILE *)0x0) {
    pu4 = stk_5c;
    for (i2 = 0x10; i2 != 0; i2 = i2 + -1) {
      *pu4 = 0;
      pu4 = pu4 + 1;
    }
    memcpy(stk_5c,"ElecbyteAIB",0xc);
    stk_4c = (uint16_t)MUGENDATE_Y;
    stk_4a = (uint8_t)MUGENDATE_M;
    stk_5c[3] = 0x100;
    stk_49 = (uint8_t)MUGENDATE_D;
    s2 = fwrite(stk_5c,0x40,1,stream);
    if (s2 != 0) {
      i2 = 0;
      do {
        array = *(int *)(arg2 + i2 * 4);
        stk_60 = *(uint32_t *)(array + 8);
        s2 = fwrite(&stk_60,4,1,stream);
        if (s2 == 0) goto L_080a6199;
        item = (void *)ArrayScanFirst(array);
        while (item != (void *)0x0) {
          s2 = fwrite(item,*(size_t *)(array + 4),1,stream);
          if (s2 == 0) goto L_080a6199;
          item = (void *)ArrayScanNext(array);
        }
        i2 = i2 + 1;
      } while (i2 < 2);
      s2 = fwrite((void *)(arg2 + 8),0x100,1,stream);
      if (s2 != 0) {
        fclose(stream);
        return 1;
      }
    }
L_080a6199:
    fclose(stream);
  }
  return 0;
}
#undef stk_60
#undef stk_5c
#undef stk_4c
#undef stk_4a
#undef stk_49

/* AIStateSetInit @ 0x080a61d0, 91 bytes
 *
 * Creates the keyed array of learned attack entries of an AI state set.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: ArrayNew
 * Called by: AILearnDataLoad, PlayerAIInit
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
uint32_t AIStateSetInit(int arg1)

{
  uint32_t *array;
  int i2;
  int i3;
  
  i2 = 0;
  i3 = 0;
  do {
    array = ArrayNew(*(size_t *)((int)&AIMaxStateInfo + i3),0x4b4,0);
    *(uint32_t **)(arg1 + i3) = array;
    if (array == (uint32_t *)0x0) {
      return 0;
    }
    i2 = i2 + 1;
    i3 = i3 + 4;
  } while (i2 < 2);
  i2 = 3;
  array = (uint32_t *)(arg1 + 200);
  do {
    *array = 0xc6fff000;
    array = array + -0x10;
    i2 = i2 + -1;
  } while (-1 < i2);
  return 1;
}

/* AIStateSetDeInit @ 0x080a6230, 57 bytes
 *
 * Frees an AI state set's array.
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * Calls: ArrayFree
 * Called by: AILearnDataLoad, PlayerAIDeInit, PlayerRCFree
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void AIStateSetDeInit(uint32_t *arg1)

{
  int i2;
  
  i2 = 0;
  do {
    if ((void *)arg1[i2] != (void *)0x0) {
      ArrayFree((void *)arg1[i2]);
    }
    i2 = i2 + 1;
  } while (i2 < 2);
  for (i2 = 0x42; i2 != 0; i2 = i2 + -1) {
    *arg1 = 0;
    arg1 = arg1 + 1;
  }
  return;
}

/* AIStateSetClear @ 0x080a6270, 45 bytes
 *
 * Empties an AI state set.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: ArrayClear
 * Called by: AIStateSetCopy
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void AIStateSetClear(int arg1)

{
  int array;
  int i2;
  
  i2 = 0;
  do {
    array = *(int *)(arg1 + i2 * 4);
    if (array != 0) {
      ArrayClear(array);
    }
    i2 = i2 + 1;
  } while (i2 < 2);
  return;
}

/* AIStateSetMerge @ 0x080a62a0, 222 bytes
 *
 * Merges the entries of one AI state set into another: matching entries
 * (same state) are combined (AIMergeLearnData), new ones are added. Used to
 * fold what a player learned back into its character's data.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Calls: ArrayNew, ArrayScanFirst, ArrayFind, ArrayAdd, AIMergeLearnData,
 *        ArrayScanNext
 * Called by: AIStateSetCopy, PlayerFree
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
uint32_t AIStateSetMerge(int arg1,int arg2)

{
  int array;
  int array2;
  uint32_t *array3;
  void *item;
  uint32_t index;
  int i6;
  int stk_14;
  
  i6 = 0;
  stk_14 = 0;
  do {
    array = *(int *)(arg2 + i6);
    if (array != 0) {
      if (*(int *)(arg1 + i6) == 0) {
        array3 = ArrayNew(*(size_t *)((int)&AIMaxStateInfo + i6),0x4b4,0);
        *(uint32_t **)(arg1 + i6) = array3;
        if (array3 == (uint32_t *)0x0) {
          return 0;
        }
      }
      array2 = *(int *)(arg1 + i6);
      item = (void *)ArrayScanFirst(array);
      while (item != (void *)0x0) {
        index = ArrayFind(array2,0,*(int *)((int)item + 0x204));
        if (index == 0xffffffff) {
          ArrayAdd(array2,item,0,*(uint32_t *)((int)item + 0x204));
        }
        else {
          AIMergeLearnData((int *)(index * *(int *)(array2 + 4) + *(int *)(array2 + ARRAY_DATA)),(int)item
                           ,-1);
        }
        item = (void *)ArrayScanNext(array);
      }
    }
    i6 = i6 + 4;
    stk_14 = stk_14 + 1;
  } while (stk_14 < 2);
  return 1;
}

/* AIStateSetCopy @ 0x080a6380, 37 bytes
 *
 * Replaces an AI state set's contents with a copy of another (clear, then
 * merge).
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Calls: AIStateSetClear, AIStateSetMerge
 * Called by: PlayerNew
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void AIStateSetCopy(int arg1,int arg2)

{
  AIStateSetClear(arg1);
  AIStateSetMerge(arg1,arg2);
  return;
}

/* PlayerAISetLevel @ 0x080a63b0, 15 bytes
 *
 * Sets a player's AI level (1-8).
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t
 *
 * Called by: PlayerAIInit, PlayerNew
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void PlayerAISetLevel(int arg1,uint32_t arg2)

{
  *(uint32_t *)(arg1 + 0x33f8) = arg2;
  return;
}

/* PlayerResetAI @ 0x080a63c0, 114 bytes
 *
 * Resets a player's AI between rounds: clears its queued commands and
 * messages.
 *
 * Parameters:
 *   player       int
 *
 * Calls: AIClearCommands, PlayerAIClearMsg
 * Called by: PlayerReset
 *
 * Elecbyte file: src/mugen/p-ai.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x670 bytes,
 *       1 variables), because their address is taken.
 */
void PlayerResetAI(int player)

{
  uint32_t u1;
  int i2;
  uint32_t *pu3;
  uint32_t *pu4;
  unsigned char frame[0x670] __attribute__((aligned(16)));
#define stk_66c (*(uint32_t (*)[407])(frame + 0x4))
  
  pu3 = (uint32_t *)(player + 0x2dac);
  pu4 = stk_66c;
  for (i2 = 0x193; i2 != 0; i2 = i2 + -1) {
    *pu4 = *pu3;
    pu3 = pu3 + 1;
    pu4 = pu4 + 1;
  }
  u1 = *(uint32_t *)(player + 0x33f8);
  pu3 = (uint32_t *)(player + 0x262c);
  for (i2 = 0x37e; i2 != 0; i2 = i2 + -1) {
    *pu3 = 0;
    pu3 = pu3 + 1;
  }
  AIClearCommands((uint32_t *)(player + 0x33fc));
  PlayerAIClearMsg(player);
  pu3 = stk_66c;
  pu4 = (uint32_t *)(player + 0x2dac);
  for (i2 = 0x193; i2 != 0; i2 = i2 + -1) {
    *pu4 = *pu3;
    pu3 = pu3 + 1;
    pu4 = pu4 + 1;
  }
  *(uint32_t *)(player + 0x33f8) = u1;
  return;
}
#undef stk_66c

/* PlayerAI @ 0x080a6440, 303 bytes
 *
 * Runs the AI of a computer-controlled player for one tick. It releases the
 * keys, applies guard and hold keys from the previous decision and consumes
 * the key buffer. Then it decides with AIForTrainingMode (training dummy) or
 * AIForNormal, and checks for incoming attacks (AICheckForAttacks).
 *
 * Parameters:
 *   player       int
 *
 * Calls: AIClearCommands, AIKBReleaseAll, KBIStuffBufNoFlip, KBIGetch,
 *        AICheckForAttacks, AIForTrainingMode, AIForNormal
 * Called by: GameUpdate
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void PlayerAI(int player)

{
  int i1;
  int i2;
  uint32_t u3;
  uint32_t u4;
  
  i2 = *(int *)(player + 0x3424);
  i1 = player + 0x248;
  if (((*(int *)(player + 0x262c) != 0) && (i2 != 0)) && (*(int *)(i2 + 0x158) != 0)) {
    AIClearCommands((uint32_t *)(player + 0x33fc));
    if (g[0x7511] != 2) {
      AIKBReleaseAll(player);
      return;
    }
    if ((*(int *)(player + 0x2c8) != 0) && (*(int *)(player + 0x2d0) != 0)) {
      if (*(int *)(player + 0xe10) == 0) {
        u4 = 0x14;
      }
      else {
        u4 = 0x12;
      }
      KBIStuffBufNoFlip(i1,u4);
    }
    if ((*(int *)(player + 0x2c4) != 0) && (*(int *)(player + 0x2cc) != 0)) {
      KBIStuffBufNoFlip(i1,0x11);
    }
    u4 = KBIGetch(player + 0x2cec);
    if (u4 == 0) {
      u3 = AICheckForAttacks(player);
      *(uint32_t *)(player + 0x2da8) = u3;
      if ((g[0x33ae] == 3) && (*(int *)(player + 0x2cd0) == 0)) {
        AIForTrainingMode(player,i2);
      }
      else {
        AIForNormal(player,*(int *)(player + 0x33f8));
      }
    }
    else {
      KBIStuffBufNoFlip(i1,u4);
    }
  }
  return;
}

/* PlayerAIProcessCommands @ 0x080a6570, 76 bytes
 *
 * Marks the commands the AI has queued (for itself or through its root
 * player) as active in the player's command table, so `command = "..."`
 * triggers see them.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: PlayerKBUpdate
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void PlayerAIProcessCommands(int arg1)

{
  int *pi1;
  int i2;
  int i3;
  int i4;
  
  i2 = arg1;
  if (*(int *)(arg1 + 0x2624) != 0) {
    i2 = *(int *)(arg1 + 0x2624);
  }
  if (*(int *)(i2 + 0x262c) != 0) {
    i3 = 0x33f0;
    if (*(int *)(i2 + 0x33fc) != -1) {
      i4 = 0x33f0;
      do {
        pi1 = (int *)(i4 + i2 + 0xc);
        i4 = i4 + 4;
        i3 = i3 + 4;
        *(uint8_t *)(*pi1 + arg1 + 0x968) = 1;
      } while (*(int *)(i3 + i2 + 0xc) != -1);
    }
  }
  return;
}

/* AIInsertCommand @ 0x080a65c0, 52 bytes
 *
 * Appends a command index to the AI's -1-terminated command queue (at most 9
 * entries).
 *
 * Parameters:
 *   cmdqueue     int *
 *   cmd          int
 *
 * Called by: AIForNormalAttack, AIForNormalRandom, SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
uint32_t AIInsertCommand(int *cmdqueue,int cmd)

{
  int i1;
  int i2;
  
  i2 = 0;
  i1 = *cmdqueue;
  while (i1 != -1) {
    i2 = i2 + 1;
    i1 = cmdqueue[i2];
  }
  if (i2 < 9) {
    cmdqueue[i2] = cmd;
    cmdqueue[i2 + 1] = -1;
    return 1;
  }
  return 0;
}

/* AICopyCommands @ 0x080a6600, 39 bytes
 *
 * Copies a command queue.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int *
 *
 * Called by: PlayerAILearnMoveStart, PlayerDoSCtrlApplyElem
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void AICopyCommands(int arg1,int *arg2)

{
  int i1;
  int i2;
  
  i2 = 0;
  i1 = *arg2;
  while (i1 != -1) {
    *(int *)(arg1 + i2 * 4) = i1;
    i2 = i2 + 1;
    i1 = arg2[i2];
  }
  *(uint32_t *)(arg1 + i2 * 4) = 0xffffffff;
  return;
}

/* AIClearCommands @ 0x080a6630, 11 bytes
 *
 * Empties a command queue.
 *
 * Parameters:
 *   cmdqueue     uint32_t *
 *
 * Called by: PlayerAI, PlayerResetAI, PlayerSCtrlUpdate,
 *            PlayerSCtrlUpdateSpec
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void AIClearCommands(uint32_t *cmdqueue)

{
  *cmdqueue = 0xffffffff;
  return;
}

/* AICountCommands @ 0x080a6640, 24 bytes
 *
 * Returns the number of commands in a queue.
 *
 * Parameters:
 *   cmdqueue     int *
 *
 * Called by: PlayerDoSCtrlApplyElem
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
int AICountCommands(int *cmdqueue)

{
  int i1;
  int i2;
  
  i2 = 0;
  i1 = *cmdqueue;
  while (i1 != -1) {
    i2 = i2 + 1;
    i1 = cmdqueue[i2];
  }
  return i2;
}

/* PlayerAILearnMoveStart @ 0x080a6660, 392 bytes
 *
 * Starts recording an attack for learning when a player enters an attack
 * state: fetches the entry for that state and opponent hit-state class and
 * remembers the start position and commands.
 *
 * Parameters:
 *   player       int
 *
 * Player fields read: statetype, stateno, pos_x, pos_y
 * Calls: AIFetchLearnDataArray, ArrayAccessGrpItem, PlayerAILearnMoveEnd,
 *        AICopyCommands
 * Called by: PlayerDoSCtrlApplyElem
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
uint32_t PlayerAILearnMoveStart(int player)

{
  int array;
  uint32_t item;
  uint32_t *pu3;
  
  array = AIFetchLearnDataArray(player + 0x2dac,*(int *)(player + PLB_STATETYPE));
  if (array == 0) {
    *(uint32_t *)(player + 0x267c) = 0;
  }
  else {
    item = ArrayAccessGrpItem(array,0,*(int *)(player + PLB_STATENO));
    *(uint32_t *)(player + 0x267c) = item;
  }
  if (*(int *)(player + 0x2dac) == 0) {
    item = 0;
  }
  else {
    if (*(int *)(player + 0x2eb8) != 0) {
      PlayerAILearnMoveEnd(player,0);
    }
    pu3 = (uint32_t *)(player + 0x2eb8);
    for (array = 0x136; array != 0; array = array + -1) {
      *pu3 = 0;
      pu3 = pu3 + 1;
    }
    *(uint32_t *)(player + 0x2eb8) = 1;
    *(uint32_t *)(player + 0x2ec0) = *(uint32_t *)(player + PLB_STATETYPE);
    *(uint32_t *)(player + 0x2ecc) = *(uint32_t *)(player + 400);
    *(int *)(player + 0x2ec4) = (int)X87_FIST32(*(float *)(player + PLB_POS_X));
    *(int *)(player + 0x2ec8) = (int)X87_FIST32(*(float *)(player + PLB_POS_Y));
    *(uint32_t *)(player + 0x2ed8) = 0;
    *(uint32_t *)(player + 0x30e0) = *(uint32_t *)(player + PLB_STATENO);
    *(uint32_t *)(player + 0x30e4) = *(uint32_t *)(player + PLB_STATETYPE);
    *(uint32_t *)(player + 0x2edc) = *(uint32_t *)(player + 0x33e8);
    *(uint32_t *)(player + 12000) = *(uint32_t *)(player + 0x33ec);
    *(uint32_t *)(player + 0x2ee4) = *(uint32_t *)(player + 0x33f0);
    *(uint32_t *)(player + 0x2ee8) = *(uint32_t *)(player + 0x33f4);
    *(uint32_t *)(player + 0x30dc) = 1;
    AICopyCommands(player + 0x30e8,(int *)(player + 0x3390));
    *(uint32_t *)(player + 0x3210) = 0xc6fff000;
    *(uint32_t *)(player + 0x31d0) = 0xc6fff000;
    item = 1;
  }
  return item;
}

/* PlayerAILearnMoveUpdate @ 0x080a67f0, 2550 bytes
 *
 * Updates the attack being recorded each tick: extends the recorded attack
 * box extents (AILearnClsnUpdate) or idle box extents, notes hits,
 * projectiles and recovery, and ends the record when the attack is over
 * (PlayerAILearnMoveEnd).
 *
 * Parameters:
 *   player       int
 *   arg2         int
 *
 * Player fields read: anim, movetype, ctrl, hitpausetime, hitdef, pos_x,
 *                     pos_y, projectiles, hitdef_damage
 * Calls: AILearnIdleClsnUpdate, PlayerAILearnMoveEnd, PlayerAIGetAIPLHS,
 *        AILearnClsnUpdate, AIValMake, ProjArrayCountActiveID
 * Called by: GameUpdate
 *
 * Elecbyte file: src/mugen/p-ai.c
 * Note: removed 5 x87 control-word save statements
 * Note: 12 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x100 bytes,
 *       52 variables), because their address is taken.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void PlayerAILearnMoveUpdate(int player,int arg2)

{
  float80 f1;
  bool b2;
  bool b3;
  int i4;
  int i5;
  int i6;
  uint16_t entry_FPUControlWord;
  unsigned char frame[0x100] __attribute__((aligned(16)));
#define stk_f4 (*(uint32_t *)(frame + 0xc))
#define stk_ec (*(float *)(frame + 0x14))
#define stk_e8 (*(uint32_t *)(frame + 0x18))
#define stk_e4 (*(uint32_t *)(frame + 0x1c))
#define stk_e0 (*(uint32_t *)(frame + 0x20))
#define stk_dc (*(float *)(frame + 0x24))
#define stk_d8 (*(uint32_t *)(frame + 0x28))
#define stk_d4 (*(uint32_t *)(frame + 0x2c))
#define stk_d0 (*(uint32_t *)(frame + 0x30))
#define stk_cc (*(float *)(frame + 0x34))
#define stk_c8 (*(uint32_t *)(frame + 0x38))
#define stk_c4 (*(uint32_t *)(frame + 0x3c))
#define stk_c0 (*(uint32_t *)(frame + 0x40))
#define stk_bc (*(float *)(frame + 0x44))
#define stk_b8 (*(uint32_t *)(frame + 0x48))
#define stk_b4 (*(uint32_t *)(frame + 0x4c))
#define stk_b0 (*(uint32_t *)(frame + 0x50))
#define stk_ac (*(float *)(frame + 0x54))
#define stk_a8 (*(uint32_t *)(frame + 0x58))
#define stk_a4 (*(uint32_t *)(frame + 0x5c))
#define stk_a0 (*(uint32_t *)(frame + 0x60))
#define stk_9c (*(float *)(frame + 0x64))
#define stk_98 (*(uint32_t *)(frame + 0x68))
#define stk_94 (*(uint32_t *)(frame + 0x6c))
#define stk_90 (*(uint32_t *)(frame + 0x70))
#define stk_8c (*(float *)(frame + 0x74))
#define stk_88 (*(uint32_t *)(frame + 0x78))
#define stk_84 (*(uint32_t *)(frame + 0x7c))
#define stk_80 (*(uint32_t *)(frame + 0x80))
#define stk_7c (*(float *)(frame + 0x84))
#define stk_78 (*(uint32_t *)(frame + 0x88))
#define stk_74 (*(uint32_t *)(frame + 0x8c))
#define stk_70 (*(uint32_t *)(frame + 0x90))
#define stk_6c (*(float *)(frame + 0x94))
#define stk_68 (*(uint32_t *)(frame + 0x98))
#define stk_64 (*(uint32_t *)(frame + 0x9c))
#define stk_60 (*(uint32_t *)(frame + 0xa0))
#define stk_5c (*(float *)(frame + 0xa4))
#define stk_58 (*(uint32_t *)(frame + 0xa8))
#define stk_54 (*(uint32_t *)(frame + 0xac))
#define stk_50 (*(uint32_t *)(frame + 0xb0))
#define stk_44 (*(float *)(frame + 0xbc))
#define stk_40 (*(uint16_t *)(frame + 0xc0))
#define stk_3e (*(uint16_t *)(frame + 0xc2))
#define stk_3c (*(float *)(frame + 0xc4))
#define stk_38 (*(uint32_t *)(frame + 0xc8))
#define stk_34 (*(uint32_t *)(frame + 0xcc))
#define stk_30 (*(uint32_t *)(frame + 0xd0))
#define stk_2c (*(float *)(frame + 0xd4))
#define stk_28 (*(uint32_t *)(frame + 0xd8))
#define stk_24 (*(uint32_t *)(frame + 0xdc))
#define stk_20 (*(uint32_t *)(frame + 0xe0))
  
  b3 = true;
  b2 = false;
  i6 = player + 0x2edc;
  f1 = *(float *)(player + 0x2ebc);
  stk_f4 = 0;
  if (((*(int *)(*(int *)(player + PLB_ANIM) + 0x10) == 0) || (*(int *)(player + 0x2dac) == 0)) ||
     (*(int *)(player + 0x2eb8) == 0)) {
    b3 = false;
  }
  if ((*(int *)(player + PLB_MOVETYPE) == 0) && (*(int *)(player + PLB_CTRL) != 0)) {
    if (b3) {
      stk_f4 = (uint32_t)(1 < *(int *)(player + 0x2eb8));
    }
    b2 = true;
  }
  if ((*(int *)(player + 0xbec) != 0) || (*(int *)(player + PLB_MOVETYPE) == 2)) {
    b2 = true;
  }
  if (b2) {
    *(uint32_t *)(player + 0x267c) = 0;
  }
  if (*(int *)(player + 0x2dac) != 0) {
    AILearnIdleClsnUpdate(player);
  }
  if (b3) {
    if (b2) {
      PlayerAILearnMoveEnd(player,stk_f4);
    }
    else {
      i4 = PlayerAIGetAIPLHS(player);
      i5 = *(int *)(player + 0x2ed8);
      if (i5 == 0) {
        *(int *)(player + 0x2ed8) = i4;
        i5 = i4;
      }
      if (((arg2 != 0) && (*(int *)(player + PLB_HITPAUSETIME) == 0)) && (g[0x74f3] == -1)) {
        AILearnClsnUpdate(player,i6);
      }
      if (*(int *)(player + 0x2eb8) == 1) {
        if ((*(int *)(player + PLB_HITDEF) != 0) &&
           (*(int *)(*(int *)(*(int *)(player + PLB_ANIM) + 0x10) + 0x28) != 0)) {
          i4 = i5 * 0x30;
          AIValMake(&stk_2c,f1);
          *(float *)(player + 0x3110) = stk_2c;
          *(uint32_t *)(player + 0x3114) = stk_28;
          *(uint32_t *)(player + 0x3118) = stk_24;
          *(uint32_t *)(player + 0x311c) = stk_20;
          *(float *)(i4 + 0x264 + i6) = stk_2c;
          *(uint32_t *)(i4 + 0x268 + i6) = *(uint32_t *)(player + 0x3114);
          *(uint32_t *)(i4 + 0x26c + i6) = *(uint32_t *)(player + 0x3118);
          *(uint32_t *)(i4 + 0x270 + i6) = *(uint32_t *)(player + 0x311c);
          stk_44 = BITS_I2F((int)X87_FIST32((*(float *)(player + PLB_POS_X) -
                                       (float80)*(int *)(player + 0x2ec4)) *
                                       (float80)*(int *)(player + 0x2ecc)));
          AIValMake(&stk_3c,stk_44);
          *(float *)(player + 0x3120) = stk_3c;
          *(uint32_t *)(player + 0x3124) = stk_38;
          *(uint32_t *)(player + 0x3128) = stk_34;
          *(uint32_t *)(player + 0x312c) = stk_30;
          *(float *)(i4 + 0x274 + i6) = stk_3c;
          *(uint32_t *)(i4 + 0x278 + i6) = *(uint32_t *)(player + 0x3124);
          *(uint32_t *)(i4 + 0x27c + i6) = *(uint32_t *)(player + 0x3128);
          *(uint32_t *)(i4 + 0x280 + i6) = *(uint32_t *)(player + 0x312c);
          stk_44 = BITS_I2F((int)X87_FIST32(*(float *)(player + PLB_POS_Y) -
                                       (float80)*(int *)(player + 0x2ec8)));
          AIValMake(&stk_5c,stk_44);
          *(float *)(player + 0x3130) = stk_5c;
          *(uint32_t *)(player + 0x3134) = stk_58;
          *(uint32_t *)(player + 0x3138) = stk_54;
          *(uint32_t *)(player + 0x313c) = stk_50;
          *(float *)(i4 + 0x284 + i6) = stk_5c;
          *(uint32_t *)(i4 + 0x288 + i6) = *(uint32_t *)(player + 0x3134);
          *(uint32_t *)(i4 + 0x28c + i6) = *(uint32_t *)(player + 0x3138);
          *(uint32_t *)(i4 + 0x290 + i6) = *(uint32_t *)(player + 0x313c);
          *(uint32_t *)(player + 0x3250) = *(uint32_t *)(player + 0x11d0);
          *(uint32_t *)(player + 0x3254) = *(uint32_t *)(player + 0x11cc);
          *(uint32_t *)(player + 0x3258) = *(uint32_t *)(player + 0x1164);
          *(uint32_t *)(player + 0x325c) = *(uint32_t *)(player + 0x1204);
          *(uint32_t *)(player + 0x2eb8) = 2;
        }
        if (*(int *)(player + 0x33e4) != -1) {
          i5 = i5 * 0x30;
          AIValMake(&stk_6c,f1);
          *(float *)(player + 0x3110) = stk_6c;
          *(uint32_t *)(player + 0x3114) = stk_68;
          *(uint32_t *)(player + 0x3118) = stk_64;
          *(uint32_t *)(player + 0x311c) = stk_60;
          *(float *)(i5 + 0x264 + i6) = stk_6c;
          *(uint32_t *)(i5 + 0x268 + i6) = *(uint32_t *)(player + 0x3114);
          *(uint32_t *)(i5 + 0x26c + i6) = *(uint32_t *)(player + 0x3118);
          *(uint32_t *)(i5 + 0x270 + i6) = *(uint32_t *)(player + 0x311c);
          stk_44 = BITS_I2F((int)X87_FIST32((*(float *)(player + PLB_POS_X) -
                                       (float80)*(int *)(player + 0x2ec4)) *
                                       (float80)*(int *)(player + 0x2ecc)));
          AIValMake(&stk_7c,stk_44);
          *(float *)(player + 0x3120) = stk_7c;
          *(uint32_t *)(player + 0x3124) = stk_78;
          *(uint32_t *)(player + 0x3128) = stk_74;
          *(uint32_t *)(player + 0x312c) = stk_70;
          *(float *)(i5 + 0x274 + i6) = stk_7c;
          *(uint32_t *)(i5 + 0x278 + i6) = *(uint32_t *)(player + 0x3124);
          *(uint32_t *)(i5 + 0x27c + i6) = *(uint32_t *)(player + 0x3128);
          *(uint32_t *)(i5 + 0x280 + i6) = *(uint32_t *)(player + 0x312c);
          stk_44 = BITS_I2F((int)X87_FIST32(*(float *)(player + PLB_POS_Y) -
                                       (float80)*(int *)(player + 0x2ec8)));
          AIValMake(&stk_8c,stk_44);
          *(float *)(player + 0x3130) = stk_8c;
          *(uint32_t *)(player + 0x3134) = stk_88;
          *(uint32_t *)(player + 0x3138) = stk_84;
          *(uint32_t *)(player + 0x313c) = stk_80;
          *(float *)(i5 + 0x284 + i6) = stk_8c;
          *(uint32_t *)(i5 + 0x288 + i6) = *(uint32_t *)(player + 0x3134);
          *(uint32_t *)(i5 + 0x28c + i6) = *(uint32_t *)(player + 0x3138);
          *(uint32_t *)(i5 + 0x290 + i6) = *(uint32_t *)(player + 0x313c);
          *(uint32_t *)(player + 0x2ed4) = *(uint32_t *)(player + 0x33e4);
          *(uint32_t *)(player + 0x33e4) = 0xffffffff;
          *(uint32_t *)(player + 0x2eb8) = 2;
        }
      }
      else if (*(int *)(player + 0x2eb8) == 2) {
        if (((*(int *)(player + PLB_HITDEF) != 0) &&
            (*(int *)(*(int *)(*(int *)(player + PLB_ANIM) + 0x10) + 0x28) != 0)) ||
           (i4 = ProjArrayCountActiveID(*(int **)(player + PLB_PROJECTILES),*(int *)(player + 0x2ed4)),
           i4 != 0)) {
          i4 = i5 * 0x30;
          AIValMake(&stk_9c,f1);
          *(float *)(i4 + 0x264 + i6) = stk_9c;
          *(uint32_t *)(i4 + 0x268 + i6) = stk_98;
          *(uint32_t *)(i4 + 0x26c + i6) = stk_94;
          *(uint32_t *)(i4 + 0x270 + i6) = stk_90;
          stk_44 = BITS_I2F((int)X87_FIST32((*(float *)(player + PLB_POS_X) -
                                       (float80)*(int *)(player + 0x2ec4)) *
                                       (float80)*(int *)(player + 0x2ecc)));
          AIValMake(&stk_ac,stk_44);
          *(float *)(i4 + 0x274 + i6) = stk_ac;
          *(uint32_t *)(i4 + 0x278 + i6) = stk_a8;
          *(uint32_t *)(i4 + 0x27c + i6) = stk_a4;
          *(uint32_t *)(i4 + 0x280 + i6) = stk_a0;
          stk_44 = BITS_I2F((int)X87_FIST32(*(float *)(player + PLB_POS_Y) -
                                       (float80)*(int *)(player + 0x2ec8)));
          AIValMake(&stk_bc,stk_44);
          *(float *)(i4 + 0x284 + i6) = stk_bc;
          *(uint32_t *)(i4 + 0x288 + i6) = stk_b8;
          *(uint32_t *)(i4 + 0x28c + i6) = stk_b4;
          *(uint32_t *)(i4 + 0x290 + i6) = stk_b0;
          if (*(int *)(player + 0x1168) != *(int *)(player + 0x2ed0)) {
            stk_44 = BITS_I2F((int)X87_FIST32(*(float *)(player + 0x3260)));
            AIValMake(&stk_cc,BITS_I2F((BITS_F2I(int, stk_44) + *(int *)(player + PLB_HITDEF_DAMAGE))));
            *(float *)(player + 0x3260) = stk_cc;
            *(uint32_t *)(player + 0x3264) = stk_c8;
            *(uint32_t *)(player + 0x3268) = stk_c4;
            *(uint32_t *)(player + 0x326c) = stk_c0;
            *(uint32_t *)(player + 0x2ed0) = *(uint32_t *)(player + 0x1168);
          }
        }
        i5 = i5 * 0x30;
        if ((*(float *)(i5 + 0x394 + i6) == 0.0) && (*(int *)(player + PLB_CTRL) != 0)) {
          AIValMake(&stk_cc,f1);
          *(float *)(i5 + 0x394 + i6) = stk_cc;
          *(uint32_t *)(i5 + 0x398 + i6) = stk_c8;
          *(uint32_t *)(i5 + 0x39c + i6) = stk_c4;
          *(uint32_t *)(i5 + 0x3a0 + i6) = stk_c0;
          stk_44 = BITS_I2F((int)X87_FIST32((*(float *)(player + PLB_POS_X) -
                                       (float80)*(int *)(player + 0x2ec4)) *
                                       (float80)*(int *)(player + 0x2ecc)));
          AIValMake(&stk_dc,stk_44);
          *(float *)(i5 + 0x3a4 + i6) = stk_dc;
          *(uint32_t *)(i5 + 0x3a8 + i6) = stk_d8;
          *(uint32_t *)(i5 + 0x3ac + i6) = stk_d4;
          *(uint32_t *)(i5 + 0x3b0 + i6) = stk_d0;
          stk_44 = BITS_I2F((int)X87_FIST32(*(float *)(player + PLB_POS_Y) -
                                       (float80)*(int *)(player + 0x2ec8)));
          AIValMake(&stk_ec,stk_44);
          *(float *)(i5 + 0x3b4 + i6) = stk_ec;
          *(uint32_t *)(i5 + 0x3b8 + i6) = stk_e8;
          *(uint32_t *)(i5 + 0x3bc + i6) = stk_e4;
          *(uint32_t *)(i5 + 0x3c0 + i6) = stk_e0;
        }
      }
      if (((arg2 != 0) && (*(int *)(player + PLB_HITPAUSETIME) == 0)) && (g[0x74f3] == -1)) {
        *(int *)(player + 0x2ebc) = *(int *)(player + 0x2ebc) + 1;
      }
    }
  }
  return;
}
#undef stk_f4
#undef stk_ec
#undef stk_e8
#undef stk_e4
#undef stk_e0
#undef stk_dc
#undef stk_d8
#undef stk_d4
#undef stk_d0
#undef stk_cc
#undef stk_c8
#undef stk_c4
#undef stk_c0
#undef stk_bc
#undef stk_b8
#undef stk_b4
#undef stk_b0
#undef stk_ac
#undef stk_a8
#undef stk_a4
#undef stk_a0
#undef stk_9c
#undef stk_98
#undef stk_94
#undef stk_90
#undef stk_8c
#undef stk_88
#undef stk_84
#undef stk_80
#undef stk_7c
#undef stk_78
#undef stk_74
#undef stk_70
#undef stk_6c
#undef stk_68
#undef stk_64
#undef stk_60
#undef stk_5c
#undef stk_58
#undef stk_54
#undef stk_50
#undef stk_44
#undef stk_40
#undef stk_3e
#undef stk_3c
#undef stk_38
#undef stk_34
#undef stk_30
#undef stk_2c
#undef stk_28
#undef stk_24
#undef stk_20

/* AILearnClsnUpdate @ 0x080a71f0, 609 bytes
 *
 * Extends the recorded attack box extents with the attacker's current Clsn1
 * boxes, relative to its start position.
 *
 * Parameters:
 *   player       int
 *   arg2         int
 *
 * Player fields read: pos_x, pos_y, anim
 * Calls: IntMin, IntMax
 * Called by: PlayerAILearnMoveUpdate
 *
 * Elecbyte file: src/mugen/p-ai.c
 * Note: 8 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
int AILearnClsnUpdate(int player,int arg2)

{
  int i1;
  int i2;
  float80 f3;
  int i4;
  int i5;
  int i6;
  int i7;
  float *pf8;
  int stk_2c;
  int stk_20;
  int stk_1c;
  
  pf8 = (float *)(arg2 + 0x2f4);
  i1 = (int)X87_FIST32((*(float *)(player + PLB_POS_X) - (float80)*(int *)(player + 0x2ec4)) *
                     (float80)*(int *)(player + 0x2ecc));
  stk_1c = 0;
  i2 = (int)X87_FIST32(*(float *)(player + PLB_POS_Y) - (float80)*(int *)(player + 0x2ec8));
  do {
    i7 = 0;
    i4 = *(int *)(*(int *)(player + PLB_ANIM) + 0x10);
    if (i4 != 0) {
      if (stk_1c == 0) {
        i7 = *(int *)(i4 + 0x28);
      }
      else {
        i7 = *(int *)(i4 + 0x2c);
      }
    }
    if (i7 != 0) {
      f3 = *pf8;
      i4 = CONCAT22((short)((uint32_t)i4 >> 0x10),
                       (uint16_t)(f3 < -32760.0) << 8 | (uint16_t)IS_NAN(f3) << 10 |
                       (uint16_t)(f3 == -32760.0) << 0xe);
      if ((f3 == -32760.0) != 0) {
        i4 = *(int *)(i7 + 8);
        i5 = *(int *)(i4 + 8);
        *pf8 = (float)(i1 + *(int *)(i4 + 4));
        i6 = *(int *)(i4 + 0xc);
        pf8[4] = (float)(i2 + i5);
        i4 = *(int *)(i4 + 0x10);
        pf8[8] = (float)(i1 + i6);
        i4 = i2 + i4;
        pf8[0xc] = (float80)i4;
      }
      stk_20 = 0;
      if (0 < *(int *)(i7 + 4)) {
        stk_2c = 0;
        do {
          i6 = stk_2c + *(int *)(i7 + 8);
          i5 = IntMin((int)X87_FIST32(*pf8),i1 + *(int *)(i6 + 4));
          i4 = *(int *)(i6 + 8);
          *pf8 = (float80)i5;
          i5 = IntMin((int)X87_FIST32(pf8[4]),i2 + i4);
          i4 = *(int *)(i6 + 0xc);
          pf8[4] = (float80)i5;
          i5 = IntMax((int)X87_FIST32(pf8[8]),i1 + i4);
          i4 = *(int *)(i6 + 0x10);
          pf8[8] = (float80)i5;
          i4 = IntMax((int)X87_FIST32(pf8[0xc]),i2 + i4);
          pf8[0xc] = (float80)i4;
          stk_20 = stk_20 + 1;
          stk_2c = stk_2c + 0x14;
        } while (stk_20 < *(int *)(i7 + 4));
      }
    }
    pf8 = pf8 + 0x10;
    stk_1c = stk_1c + 1;
  } while (stk_1c < 2);
  return i4;
}

/* AILearnIdleClsnUpdate @ 0x080a7460, 436 bytes
 *
 * Extends the recorded body box extents for the idle states (stand, crouch,
 * air, lie...).
 *
 * Parameters:
 *   player       int
 *
 * Player fields read: anim, stateno
 * Calls: AIIdleClsnMatchState, IntMin, IntMax
 * Called by: PlayerAILearnMoveUpdate
 *
 * Elecbyte file: src/mugen/p-ai.c
 * Note: 8 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
void AILearnIdleClsnUpdate(int player)

{
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  uint32_t stk_1c;
  
  if (*(int *)(*(int *)(player + PLB_ANIM) + 0x10) != 0) {
    i2 = AIIdleClsnMatchState(*(int *)(player + PLB_STATENO));
    if ((i2 != -1) &&
       (i1 = *(int *)(*(int *)(*(int *)(player + PLB_ANIM) + 0x10) + 0x2c), i1 != 0)) {
      i2 = i2 * 0x40 + player + 0x262c;
      if (*(float *)(i2 + 0x78c) == -32760.0) {
        i6 = *(int *)(i1 + 8);
        *(float *)(i2 + 0x78c) = (float80)*(int *)(i6 + 4);
        *(float *)(i2 + 0x79c) = (float80)*(int *)(i6 + 8);
        *(float *)(i2 + 0x7ac) = (float80)*(int *)(i6 + 0xc);
        *(float *)(i2 + 0x7bc) = (float80)*(int *)(i6 + 0x10);
      }
      i6 = 0;
      if (0 < *(int *)(i1 + 4)) {
        stk_1c = 0;
        do {
          i5 = stk_1c + *(int *)(i1 + 8);
          i6 = i6 + 1;
          i3 = IntMin((int)X87_FIST32(*(float *)(i2 + 0x78c)),*(int *)(i5 + 4));
          i4 = *(int *)(i5 + 8);
          *(float *)(i2 + 0x78c) = (float80)i3;
          i3 = IntMin((int)X87_FIST32(*(float *)(i2 + 0x79c)),i4);
          i4 = *(int *)(i5 + 0xc);
          *(float *)(i2 + 0x79c) = (float80)i3;
          i3 = IntMax((int)X87_FIST32(*(float *)(i2 + 0x7ac)),i4);
          i4 = *(int *)(i5 + 0x10);
          *(float *)(i2 + 0x7ac) = (float80)i3;
          i4 = IntMax((int)X87_FIST32(*(float *)(i2 + 0x7bc)),i4);
          *(float *)(i2 + 0x7bc) = (float80)i4;
          stk_1c = stk_1c + 0x14;
        } while (i6 < *(int *)(i1 + 4));
      }
    }
  }
  return;
}

/* AIIdleClsnMatchState @ 0x080a7620, 66 bytes
 *
 * Returns the index of an idle state number (0 stand, 11 crouch, 20 walk, 50
 * jump) in the idle table, or -1.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: AIAttackInRange, AILearnIdleClsnUpdate
 *
 * Elecbyte file: src/mugen/p-ai.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x20 bytes, 1
 *       variables), because their address is taken.
 */
int AIIdleClsnMatchState(int arg1)

{
  int i2;
  unsigned char frame[0x20] __attribute__((aligned(16)));
#define stk_1c (*(int (*)[7])(frame + 0x4))
  
  i2 = 0;
  stk_1c[0] = 0;
  stk_1c[1] = 0x14;
  stk_1c[2] = 0xb;
  stk_1c[3] = 0x32;
  do {
    if (arg1 == stk_1c[i2]) {
      return i2;
    }
    i2 = i2 + 1;
  } while (i2 < 4);
  return -1;
}
#undef stk_1c

/* PlayerAILearnMoveEnd @ 0x080a7670, 857 bytes
 *
 * Finishes an attack record: computes its values (AIValMake), adds or merges
 * the entry in the player's AI state set, and stops recording.
 *
 * Parameters:
 *   player       int
 *   arg2         int
 *
 * Player fields read: pos_x, pos_y, ctrl
 * Calls: AIValMake, AIFetchLearnDataArray, ArrayFind, ArrayAdd,
 *        ArrayAccessGrpItem, AIMergeLearnData, AILearnStopRecord
 * Called by: PlayerAILearnMoveStart, PlayerAILearnMoveUpdate
 *
 * Elecbyte file: src/mugen/p-ai.c
 * Note: removed 2 x87 control-word save statements
 * Note: 6 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x90 bytes,
 *       27 variables), because their address is taken.
 */
uint32_t PlayerAILearnMoveEnd(int player,int arg2)

{
  uint32_t index;
  int index2;
  void *pv3;
  int array;
  int i5;
  uint16_t entry_FPUControlWord;
  unsigned char frame[0x90] __attribute__((aligned(16)));
#define stk_8c (*(float *)(frame + 0x4))
#define stk_88 (*(uint32_t *)(frame + 0x8))
#define stk_84 (*(uint32_t *)(frame + 0xc))
#define stk_80 (*(uint32_t *)(frame + 0x10))
#define stk_7c (*(float *)(frame + 0x14))
#define stk_78 (*(uint32_t *)(frame + 0x18))
#define stk_74 (*(uint32_t *)(frame + 0x1c))
#define stk_70 (*(uint32_t *)(frame + 0x20))
#define stk_6c (*(float *)(frame + 0x24))
#define stk_68 (*(uint32_t *)(frame + 0x28))
#define stk_64 (*(uint32_t *)(frame + 0x2c))
#define stk_60 (*(uint32_t *)(frame + 0x30))
#define stk_5c (*(float *)(frame + 0x34))
#define stk_58 (*(uint32_t *)(frame + 0x38))
#define stk_54 (*(uint32_t *)(frame + 0x3c))
#define stk_50 (*(uint32_t *)(frame + 0x40))
#define stk_44 (*(float *)(frame + 0x4c))
#define stk_40 (*(uint16_t *)(frame + 0x50))
#define stk_3e (*(uint16_t *)(frame + 0x52))
#define stk_3c (*(float *)(frame + 0x54))
#define stk_38 (*(uint32_t *)(frame + 0x58))
#define stk_34 (*(uint32_t *)(frame + 0x5c))
#define stk_30 (*(uint32_t *)(frame + 0x60))
#define stk_2c (*(float *)(frame + 0x64))
#define stk_28 (*(uint32_t *)(frame + 0x68))
#define stk_24 (*(uint32_t *)(frame + 0x6c))
#define stk_20 (*(uint32_t *)(frame + 0x70))
  
  i5 = player + 0x2dac;
  pv3 = (void *)(player + 0x2edc);
  if (*(int *)(player + 0x2dac) == 0) {
    return 0;
  }
  if (arg2 != 0) {
    index2 = *(int *)(player + 0x2ed8);
    AIValMake(&stk_2c,*(float *)(player + 0x2ebc));
    array = index2 * 0x30;
    *(float *)(array + 0x424 + (int)pv3) = stk_2c;
    *(uint32_t *)(array + 0x428 + (int)pv3) = stk_28;
    *(uint32_t *)(array + 0x42c + (int)pv3) = stk_24;
    *(uint32_t *)(array + 0x430 + (int)pv3) = stk_20;
    stk_44 = BITS_I2F((int)X87_FIST32((*(float *)(player + PLB_POS_X) - (float80)*(int *)(player + 0x2ec4)) *
                                 (float80)*(int *)(player + 0x2ecc)));
    AIValMake(&stk_3c,stk_44);
    *(float *)(array + 0x434 + (int)pv3) = stk_3c;
    *(uint32_t *)(array + 0x438 + (int)pv3) = stk_38;
    *(uint32_t *)(array + 0x43c + (int)pv3) = stk_34;
    *(uint32_t *)(array + 0x440 + (int)pv3) = stk_30;
    stk_44 = BITS_I2F((int)X87_FIST32(*(float *)(player + PLB_POS_Y) - (float80)*(int *)(player + 0x2ec8)));
    AIValMake(&stk_5c,stk_44);
    *(float *)(array + 0x444 + (int)pv3) = stk_5c;
    *(uint32_t *)(array + 0x448 + (int)pv3) = stk_58;
    *(uint32_t *)(array + 0x44c + (int)pv3) = stk_54;
    *(uint32_t *)(array + 0x450 + (int)pv3) = stk_50;
    if ((*(float *)(array + 0x394 + (int)pv3) == 0.0) && (*(int *)(player + PLB_CTRL) != 0)) {
      AIValMake(&stk_6c,*(float *)(player + 0x2ebc));
      *(float *)(array + 0x394 + (int)pv3) = stk_6c;
      *(uint32_t *)(array + 0x398 + (int)pv3) = stk_68;
      *(uint32_t *)(array + 0x39c + (int)pv3) = stk_64;
      *(uint32_t *)(array + 0x3a0 + (int)pv3) = stk_60;
      stk_44 = BITS_I2F((int)X87_FIST32((*(float *)(player + PLB_POS_X) - (float80)*(int *)(player + 0x2ec4))
                                   * (float80)*(int *)(player + 0x2ecc)));
      AIValMake(&stk_7c,stk_44);
      *(float *)(array + 0x3a4 + (int)pv3) = stk_7c;
      *(uint32_t *)(array + 0x3a8 + (int)pv3) = stk_78;
      *(uint32_t *)(array + 0x3ac + (int)pv3) = stk_74;
      *(uint32_t *)(array + 0x3b0 + (int)pv3) = stk_70;
      stk_44 = BITS_I2F((int)X87_FIST32(*(float *)(player + PLB_POS_Y) - (float80)*(int *)(player + 0x2ec8)));
      AIValMake(&stk_8c,stk_44);
      *(float *)(array + 0x3b4 + (int)pv3) = stk_8c;
      *(uint32_t *)(array + 0x3b8 + (int)pv3) = stk_88;
      *(uint32_t *)(array + 0x3bc + (int)pv3) = stk_84;
      *(uint32_t *)(array + 0x3c0 + (int)pv3) = stk_80;
    }
    array = AIFetchLearnDataArray(i5,*(int *)(player + 0x2ec0));
    if (array != 0) {
      index = ArrayFind(array,0,*(int *)(player + 0x30e0));
      if (index == 0xffffffff) {
        index2 = ArrayAdd(array,pv3,0,*(uint32_t *)(player + 0x30e0));
        if (index2 == -1) goto L_080a7970;
        ArrayAccessGrpItem(array,0,*(int *)(player + 0x30e0));
      }
      else {
        AIMergeLearnData((int *)(index * *(int *)(array + 4) + *(int *)(array + ARRAY_DATA)),(int)pv3,
                         index2);
      }
      AILearnStopRecord(i5);
      return 1;
    }
  }
L_080a7970:
  AILearnStopRecord(i5);
  return 0;
}
#undef stk_8c
#undef stk_88
#undef stk_84
#undef stk_80
#undef stk_7c
#undef stk_78
#undef stk_74
#undef stk_70
#undef stk_6c
#undef stk_68
#undef stk_64
#undef stk_60
#undef stk_5c
#undef stk_58
#undef stk_54
#undef stk_50
#undef stk_44
#undef stk_40
#undef stk_3e
#undef stk_3c
#undef stk_38
#undef stk_34
#undef stk_30
#undef stk_2c
#undef stk_28
#undef stk_24
#undef stk_20

/* PlayerAIGetAIPLHS @ 0x080a79d0, 67 bytes
 *
 * Returns the hit-state class of a player's current state type for the AI
 * tables.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: PlayerAILearnMoveUpdate
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
uint32_t PlayerAIGetAIPLHS(int arg1)

{
  int i1;
  
  i1 = *(int *)(arg1 + 0xe30);
  if (i1 == 1) {
    return 1;
  }
  if (i1 < 2) {
    if (i1 == 0) {
      return 0;
    }
  }
  else if (i1 == 2) {
    return 2;
  }
  return 0;
}

/* AIFetchLearnDataArray @ 0x080a7a20, 43 bytes
 *
 * Returns the learned-data array for a hit-state class.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Called by: AIBuildCounterAttackList, PlayerAILearnMoveEnd,
 *            PlayerAILearnMoveStart, PlayerAIMsgAttack
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
uint32_t AIFetchLearnDataArray(int arg1,int arg2)

{
  if (0 < arg2) {
    if (arg2 < 3) {
      return *(uint32_t *)(arg1 + 4);
    }
    if (arg2 == 3) {
      return *(uint32_t *)(arg1 + 8);
    }
  }
  return 0;
}

/* PlayerAIMsgAttack @ 0x080a7a50, 124 bytes
 *
 * Tells the other AI players that this player has started an attack
 * (broadcast message), so they can react.
 *
 * Parameters:
 *   player       int
 *
 * Player fields read: statetype, stateno
 * Calls: AIFetchLearnDataArray, PlayerAIBroadcastMsg
 * Called by: PlayerDoSCtrlApplyElem
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void PlayerAIMsgAttack(int player)

{
  int i1;
  uint32_t stk_14;
  
  stk_14 = 0;
  i1 = AIFetchLearnDataArray(player + 0x2dac,*(int *)(player + PLB_STATETYPE));
  if (i1 != 0) {
    stk_14 = *(uint32_t *)(player + PLB_STATENO);
  }
  *(uint32_t *)(player + 0x2ccc) = 1;
  PlayerAIBroadcastMsg(player,0,0,stk_14,i1);
  return;
}

/* PlayerAIMsgAttackEnd @ 0x080a7ad0, 76 bytes
 *
 * Tells the other AI players that this player's attack has ended.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: PlayerAIBroadcastMsg
 * Called by: PlayerAIMsgStateUpdate
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void PlayerAIMsgAttackEnd(int arg1)

{
  *(uint32_t *)(arg1 + 0x2ccc) = 0;
  PlayerAIBroadcastMsg(arg1,0,1,0xffffffff,0);
  return;
}

/* PlayerAIBroadcastMsg @ 0x080a7b20, 200 bytes
 *
 * Posts a message (sender, type, values) into the message queue of every
 * other active AI player (up to 10 messages each).
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t
 *   arg3         uint32_t
 *   arg4         uint32_t
 *   arg5         uint32_t
 *
 * Globals read: slot_first, slot_last
 * Called by: PlayerAIMsgAttack, PlayerAIMsgAttackEnd
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
int PlayerAIBroadcastMsg
              (int arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4,
              uint32_t arg5)

{
  int i1;
  int i2;
  bool b3;
  int *pi4;
  int i5;
  int i6;
  int i7;
  int i8;
  
  pi4 = g;
  i8 = 0;
  i7 = g[G_SLOT_FIRST];
  if (i7 <= g[G_SLOT_LAST]) {
    i6 = i7 * 4 + 0x1cf60;
    do {
      i1 = *(int *)(i6 + 4 + (int)pi4);
      if ((i1 == 0) || (b3 = true, *(int *)(i1 + 0x158) == 0)) {
        b3 = false;
      }
      if (((b3) && (i1 != arg1)) && (*(int *)(i1 + 0x262c) != 0)) {
        i2 = *(int *)(i1 + 0x2cc8);
        if (i2 < 10) {
          i5 = i2 * 0x10;
          *(int *)(i1 + 0x2c28 + i5) = arg1;
          *(uint32_t *)(i1 + 0x2c2c + i5) = arg3;
          *(uint32_t *)(i1 + 0x2c30 + i5) = arg4;
          *(uint32_t *)(i1 + 0x2c34 + i5) = arg5;
          *(int *)(i1 + 0x2cc8) = i2 + 1;
          i8 = i8 + 1;
        }
      }
      i7 = i7 + 1;
      i6 = i6 + 4;
    } while (i7 <= pi4[0x745a]);
  }
  return i8;
}

/* PlayerAIFindMsg @ 0x080a7bf0, 65 bytes
 *
 * Returns the index of the first message of a given type from a given
 * sender, or -1.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *
 * Called by: PlayerAIGetAndRemoveMsg, PlayerAIGetMsg
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
int PlayerAIFindMsg(int arg1,int arg2,int arg3)

{
  int i2;
  int i22;
  
  i2 = 0;
  if (0 < *(int *)(arg1 + 0x2cc8)) {
    i22 = 0;
    do {
      if (*(int *)(arg1 + 0x2c2c + i22) == arg3) {
        if (arg2 == 0) {
          return i2;
        }
        if (arg2 == *(int *)(arg1 + 0x2c28 + i22)) {
          return i2;
        }
      }
      i2 = i2 + 1;
      i22 = i22 + 0x10;
    } while (i2 < *(int *)(arg1 + 0x2cc8));
  }
  return -1;
}

/* PlayerAIGetMsg @ 0x080a7c40, 145 bytes
 *
 * Reads a message of a given type without removing it.
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Calls: PlayerAIFindMsg
 * Called by: AIForNormalDecisions, AIForNormalRandom
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
uint32_t * PlayerAIGetMsg(uint32_t *arg1,int arg2,int arg3,int arg4)

{
  int i1;
  uint32_t stk_1c;
  uint32_t stk_18;
  uint32_t stk_14;
  uint32_t stk_10;
  
  i1 = PlayerAIFindMsg(arg2,arg3,arg4);
  stk_1c = 0;
  stk_14 = 0;
  stk_10 = 0;
  stk_18 = 0xffffffff;
  if (i1 != -1) {
    i1 = i1 * 0x10;
    stk_1c = *(uint32_t *)(i1 + 0x2c28 + arg2);
    stk_18 = *(uint32_t *)(i1 + 0x2c2c + arg2);
    stk_14 = *(uint32_t *)(i1 + 0x2c30 + arg2);
    stk_10 = *(uint32_t *)(i1 + 0x2c34 + arg2);
  }
  *arg1 = stk_1c;
  arg1[1] = stk_18;
  arg1[2] = stk_14;
  arg1[3] = stk_10;
  return arg1;
}

/* PlayerAIGetAndRemoveMsg @ 0x080a7ce0, 153 bytes
 *
 * Reads and removes a message of a given type.
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Calls: PlayerAIFindMsg
 * Called by: AIForNormalDecisions, AIForNormalRandom
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
uint32_t * PlayerAIGetAndRemoveMsg(uint32_t *arg1,int arg2,int arg3,int arg4)

{
  int i1;
  uint32_t stk_1c;
  uint32_t stk_18;
  uint32_t stk_14;
  uint32_t stk_10;
  
  i1 = PlayerAIFindMsg(arg2,arg3,arg4);
  stk_1c = 0;
  stk_14 = 0;
  stk_10 = 0;
  stk_18 = 0xffffffff;
  if (i1 != -1) {
    i1 = i1 * 0x10;
    stk_1c = *(uint32_t *)(i1 + 0x2c28 + arg2);
    stk_18 = *(uint32_t *)(i1 + 0x2c2c + arg2);
    stk_14 = *(uint32_t *)(i1 + 0x2c30 + arg2);
    stk_10 = *(uint32_t *)(i1 + 0x2c34 + arg2);
    *(uint32_t *)(i1 + 0x2c2c + arg2) = 2;
  }
  *arg1 = stk_1c;
  arg1[1] = stk_18;
  arg1[2] = stk_14;
  arg1[3] = stk_10;
  return arg1;
}

/* PlayerAIClearMsg @ 0x080a7d80, 15 bytes
 *
 * Empties a player's AI message queue.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: GameUpdate, PlayerResetAI
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void PlayerAIClearMsg(int arg1)

{
  *(uint32_t *)(arg1 + 0x2cc8) = 0;
  return;
}

/* PlayerAIMsgStateUpdate @ 0x080a7d90, 68 bytes
 *
 * Sends the "attack ended" message when a player leaves its attack (move
 * type no longer attack, or control regained).
 *
 * Parameters:
 *   player       int
 *
 * Player fields read: movetype, ctrl
 * Calls: PlayerAIMsgAttackEnd
 * Called by: GameUpdate
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void PlayerAIMsgStateUpdate(int player)

{
  if ((*(int *)(player + 0x2ccc) == 1) &&
     ((((*(int *)(player + PLB_MOVETYPE) == 0 && (*(int *)(player + PLB_CTRL) != 0)) ||
       (*(int *)(player + 0xbec) != 0)) || (*(int *)(player + PLB_MOVETYPE) == 2)))) {
    PlayerAIMsgAttackEnd(player);
    return;
  }
  return;
}

/* PlayerAISctrlProjectile @ 0x080a7de0, 17 bytes
 *
 * Records the id of the projectile a player just fired, for the AI.
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t *
 *
 * Called by: PlayerSCtrlApplyElem
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void PlayerAISctrlProjectile(int arg1,uint32_t *arg2)

{
  *(uint32_t *)(arg1 + 0x33e4) = *arg2;
  return;
}

/* AIForNormal @ 0x080a7e00, 293 bytes
 *
 * The normal AI step. It repeats the decision (AIForNormalDecisions) and the
 * action for the current mode (idle, move, attack, guard, random) until
 * neither changes anything, at most 100 times. Then it advances the AI
 * timers.
 *
 * Parameters:
 *   player       int
 *   arg2         int
 *
 * Calls: AIForNormalDecisions, AIForNormalIdle, AIForNormalMove,
 *        AIForNormalAttack, AIForNormalGuard, AIForNormalRandom
 * Called by: PlayerAI
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void AIForNormal(int player,int arg2)

{
  int i1;
  int i2;
  int stk_14;
  
  stk_14 = 100;
  do {
    i1 = AIForNormalDecisions(player,arg2);
    i2 = 0;
    switch(*(uint32_t *)(player + 0x2630)) {
    case 0:
      i2 = AIForNormalIdle(player);
      break;
    case 1:
      i2 = AIForNormalMove(player);
      break;
    case 2:
      i2 = AIForNormalAttack(player,arg2);
      break;
    case 3:
      i2 = AIForNormalGuard(player,arg2);
      break;
    case 4:
      i2 = AIForNormalRandom(player,*(int *)(player + 0x3424),arg2);
    }
  } while (((i1 != 0) || (i2 != 0)) && (stk_14 = stk_14 + -1, stk_14 != 0));
  *(int *)(player + 0x2638) = *(int *)(player + 0x2638) + 1;
  if (0 < *(int *)(player + 0x2b54)) {
    *(int *)(player + 0x2b54) = *(int *)(player + 0x2b54) + -1;
  }
  if (*(int *)(player + 0x2b44) == 0) {
    if ((*(int *)(player + 0x268c) == 0) || (*(int *)(*(int *)(player + 0x268c) + 0xe04) != 1)) {
      *(int *)(player + 0x2b4c) = *(int *)(player + 0x2b4c) + 1;
      return;
    }
  }
  else if (((*(int *)(player + 0x268c) != 0) && (*(int *)(*(int *)(player + 0x268c) + 0xe18) == 0)
           ) && (g[0x74f3] == -1)) {
    *(int *)(player + 0x2b48) = *(int *)(player + 0x2b48) + 1;
  }
  *(uint32_t *)(player + 0x2b4c) = 0;
  return;
}

/* AIForNormalDecisions @ 0x080a7f30, 1946 bytes
 *
 * Chooses the AI's mode and target for this tick from the situation:
 * distance to the enemy, the enemy's state and messages (incoming attacks),
 * learned attacks that would hit from here (AIAttackInRange,
 * AIBuildCounterAttackList), and the AI level (which scales reaction and
 * randomness). It plans movement routes (AIMovePlanRoute) and sets up
 * attacks (AIAttackSetupAttack). Returns nonzero if it changed the plan.
 *
 * Parameters:
 *   player       int
 *   arg2         int
 *
 * Player fields read: pos_x, movetype, statetype, hitcount, ctrl
 * Calls: AIMovePlanRoute, AIMoveReachedDest, AIKBReleaseDir,
 *        PlayerAIGetMsg, PlayerAIGetAndRemoveMsg, AIAttackInRange,
 *        AIBuildCounterAttackList, AIAttackSetupAttack, AIChangeState
 * C library: random
 * Called by: AIForNormal
 *
 * Elecbyte file: src/mugen/p-ai.c
 * Note: 4 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x50 bytes, 8
 *       variables), because their address is taken.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t AIForNormalDecisions(int player,int arg2)

{
  float80 f1;
  bool b2;
  int i3;
  long l4;
  int i5;
  uint32_t u6;
  uint32_t *pu7;
  uint32_t u8;
  unsigned char frame[0x50] __attribute__((aligned(16)));
#define stk_50 (*(float *)(frame + 0x0))
#define stk_4c (*(int *)(frame + 0x4))
#define stk_40 (*(int *)(frame + 0x10))
#define stk_38 (*(uint32_t **)(frame + 0x18))
#define stk_34 (*(uint32_t *)(frame + 0x1c))
#define stk_2c (*(uint32_t *)(frame + 0x24))
#define stk_28 (*(int *)(frame + 0x28))
#define stk_20 (*(int *)(frame + 0x30))
  
  stk_38 = (uint32_t *)0x0;
  i5 = *(int *)(player + 0x268c);
  stk_40 = (int)X87_FIST32(*(float *)(player + PLB_POS_X) - *(float *)(*(int *)(player + 0x3424) + 0x19c)
                       );
  if (stk_40 < 0) {
    stk_40 = -stk_40;
  }
  i3 = *(int *)(player + 0x3424);
  if (i3 == 0) {
    return 0;
  }
  if ((*(int *)(player + 0x2630) == 0) && (*(int *)(i3 + 0x2ec) != 0)) {
    AIMovePlanRoute(player,arg2,
                    (int)X87_FIST32(*(float *)(*(int *)(player + 0x3424) + 0x19c) -
                               (float)(*(int *)(player + 400) * 0x28)),
                    (int)X87_FIST32(*(float *)(i3 + 0x1a0)));
    u8 = 1;
    goto L_080a86b4;
  }
  if ((*(int *)(player + 0x2630) == 1) && (i3 = AIMoveReachedDest(player), i3 != 0)) {
    AIKBReleaseDir(player);
  }
  else {
    PlayerAIGetMsg(&stk_2c,player,*(int *)(player + 0x3424),1);
    if (((stk_28 != -1) || (i3 = *(int *)(*(int *)(player + 0x3424) + 0xe04), i3 == 0)) ||
       (i3 == 2)) {
      *(uint32_t *)(player + 0x2b44) = 0;
      *(uint32_t *)(player + 0x2b48) = 0;
    }
    if ((*(int *)(player + 0x2630) == 0) && (arg2 != 9)) {
      l4 = random();
      i3 = l4 % 0x3c;
      if (0x96 < *(int *)(player + 0x2638)) {
        i3 = i3 / 2;
      }
      if (stk_40 < 100) {
        i3 = i3 / 2;
      }
      if (stk_40 < 0x32) {
        i3 = i3 / 2;
      }
      if ((*(int *)(player + PLB_MOVETYPE) == 2) && (2 < *(int *)(player + 0x102c))) {
        i3 = i3 / 2;
      }
      if ((*(int *)(player + PLB_MOVETYPE) == 2) && (*(int *)(player + PLB_STATETYPE) == 4)) {
        i3 = i3 / 2;
      }
      if ((i3 == 0) || ((0 < *(int *)(player + 0x2638) && (*(int *)(player + PLB_HITCOUNT) != 0)))) {
        u8 = 4;
        goto L_080a86b4;
      }
    }
    PlayerAIGetAndRemoveMsg(&stk_2c,player,*(int *)(player + 0x3424),0);
    if ((stk_28 != -1) && (l4 = random(), l4 % 0xc < arg2 + 3)) {
      if (stk_20 != 0) {
        stk_38 = *(uint32_t **)(*(int *)(player + 0x3424) + 0x267c);
      }
      if (stk_38 != (uint32_t *)0x0) {
        pu7 = (uint32_t *)(player + 0x2690);
        for (i3 = 0x12d; i3 != 0; i3 = i3 + -1) {
          *pu7 = *stk_38;
          stk_38 = stk_38 + 1;
          pu7 = pu7 + 1;
        }
        *(uint32_t *)(player + 0x2b44) = 1;
        *(uint32_t *)(player + 0x2b48) = 0;
        *(uint32_t *)(player + 0x268c) = *(uint32_t *)(player + 0x3424);
      }
    }
    u6 = *(uint32_t *)(player + 0x2630);
    if ((((u6 < 2) || (u6 == 4)) && (*(int *)(player + 0x2b44) != 0)) &&
       (((*(int *)(player + 0x2b54) == 0 && (u6 != 3)) &&
        ((u6 != 2 || (2 < *(int *)(player + 0x2638))))))) {
      if ((*(int *)(player + PLB_CTRL) != 0) &&
         (((float80)*(int *)(player + 0x2b48) < *(float *)(player + 0x28f4) ||
          (*(float *)(player + 0x28f4) == 0.0)))) {
        i3 = AIAttackInRange(player,arg2,*(int *)(player + 0x3424),player + 0x2690);
        if (0 < i3) {
          *(uint32_t *)(player + 0x2b54) = 5;
          if (arg2 - 1U < 3) {
            l4 = random();
            *(int *)(player + 0x2b54) = *(int *)(player + 0x2b54) + l4 % (4 - arg2);
          }
          l4 = random();
          if (l4 % 0x14 <= arg2 + 0xb) {
            u8 = 3;
            goto L_080a86b4;
          }
        }
        u6 = *(uint32_t *)(player + 0x2630);
      }
    }
    if (u6 != 3) {
      return 0;
    }
    if (*(int *)(player + 0x2b44) != 0) {
      if ((i5 == 0) || (b2 = true, *(int *)(i5 + 0x158) == 0)) {
        b2 = false;
      }
      if ((b2) && (*(int *)(player + 0x2b44) != 0)) {
        i3 = *(int *)(player + 0x2b48);
        if (player + 0x2690 == 0) {
          return 0;
        }
        stk_4c = *(int *)(i5 + 0x2ed8);
        if ((stk_4c == 0) && ((int)X87_FIST32(*(float *)(player + 0x28f4)) == 0)) {
          stk_4c = 1;
        }
        if ((stk_4c == 1) && ((int)X87_FIST32(*(float *)(player + 0x2924)) == 0)) {
          stk_4c = 2;
        }
        PlayerAIGetMsg(&stk_2c,player,*(int *)(player + 0x3424),0);
        if (stk_28 == -1) {
          if ((i3 < 1) || ((int)X87_FIST32(*(float *)(player + 0x28c4)) <= i3)) {
L_080a8558:
            stk_50 = (float80)i3;
            if ((*(int *)(player + 0x2638) == 0) &&
               (u6 = *(uint32_t *)(player + 0x2a08), u6 != 0xffffffff)) {
              if ((u6 & 0xc) == 0xc) {
                *(uint32_t *)(player + 0x2b58) = (uint32_t)(*(int *)(player + PLB_STATETYPE) == 2);
              }
              else {
                *(uint32_t *)(player + 0x2b58) = u6 >> 3 & 1;
              }
            }
            f1 = *(float *)(stk_4c * 0x30 + 0x264 + player + 0x2690);
            PlayerAIGetAndRemoveMsg(&stk_2c,player,*(int *)(player + 0x3424),1);
            if ((stk_28 == -1 && stk_50 < f1) || (*(int *)(player + PLB_CTRL) == 0)) {
              return 0;
            }
            i5 = arg2 * 5;
            if (200 < stk_40) {
              i5 = i5 / 2;
            }
            if (0x96 < stk_40) {
              i5 = i5 / 2;
            }
            if (stk_40 < 100) {
              i5 = i5 + 10;
            }
            if (stk_40 < 0x4b) {
              i5 = i5 + 10;
            }
            if (stk_40 < 0x32) {
              i5 = i5 + 10;
            }
            l4 = random();
            if (((i5 <= l4 % 100) && (arg2 != 9)) ||
               (i5 = AIBuildCounterAttackList(player,arg2), i5 < 1)) goto L_080a86b2;
          }
          else {
            i5 = i3;
            if (i3 < 0) {
              i5 = i3 + 3;
            }
            if (i3 < 3) {
              i5 = (i5 >> 2) + 5;
            }
            else {
              i5 = (i5 >> 2) + 2;
            }
            stk_34 = (uint32_t)X87_FIST32((float80)i5 -
                                   6.0 / (*(float *)(player + 0x28c4) - (float80)i3));
            l4 = random();
            if (((int)(stk_34 & (arg2 == 9) - 1) <= l4 % 100) ||
               (i5 = AIBuildCounterAttackList(player,arg2), i5 < 1)) goto L_080a8558;
          }
          l4 = random();
          AIAttackSetupAttack(player,arg2,
                              *(uint32_t *)
                               (player + 0x2b5c + (l4 % *(int *)(player + 0x2c24)) * 4));
          u8 = 2;
          goto L_080a86b4;
        }
      }
    }
  }
L_080a86b2:
  u8 = 0;
L_080a86b4:
  u8 = AIChangeState(player + 0x262c,u8);
  return u8;
}
#undef stk_50
#undef stk_4c
#undef stk_40
#undef stk_38
#undef stk_34
#undef stk_2c
#undef stk_28
#undef stk_20

/* AIMovePlanRoute @ 0x080a86d0, 504 bytes
 *
 * Plans a movement toward a destination position (walk, run or jump keys and
 * the target x).
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t
 *   arg3         int
 *   arg4         int
 *
 * Called by: AIForNormalDecisions
 *
 * Elecbyte file: src/mugen/p-ai.c
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t AIMovePlanRoute(int arg1,uint32_t arg2,int arg3,int arg4)

{
  int i1;
  float80 f2;
  int i3;
  uint32_t stk_20;
  
  i3 = (int)X87_FIST32((float80)*(int *)(arg1 + 400) * ((float)arg3 - *(float *)(arg1 + 0x19c))
                    );
  *(uint32_t *)(arg1 + 0x2660) = 0;
  *(uint32_t *)(arg1 + 0x266c) = 0;
  if (arg4 == 0) {
    *(int *)(arg1 + 0x2658) = arg3;
    *(uint32_t *)(arg1 + 0x265c) = 0;
    *(uint32_t *)(arg1 + 0x2654) = 1;
  }
  else {
    if (i3 < 0) {
      f2 = (*(float *)(arg1 + 0xf0) * -2.0 * *(float *)(arg1 + 0xe4)) /
              *(float *)(arg1 + 0x130);
    }
    else {
      f2 = (*(float *)(arg1 + 0xec) * -2.0 * *(float *)(arg1 + 0xe4)) /
              *(float *)(arg1 + 0x130);
    }
    stk_20 = (int)X87_FIST32(f2);
    i1 = (int)X87_FIST32((-*(float *)(arg1 + 0xe4) * *(float *)(arg1 + 0xe4)) /
                       (*(float *)(arg1 + 0x130) + *(float *)(arg1 + 0x130)));
    if (((i3 < 0) || (stk_20 <= i3)) && ((-1 < i3 || (i3 <= stk_20)))) {
      if (i1 < arg4) {
        i3 = arg3 - ((stk_20 * arg4) / i1) * *(int *)(arg1 + 400);
      }
      else {
        i3 = (int)X87_FIST32((double)arg3 -
                           (double)*(int *)(arg1 + 400) * (double)stk_20 * 0.5);
      }
      *(int *)(arg1 + 0x2658) = i3;
      *(uint32_t *)(arg1 + 0x265c) = 0;
      *(uint32_t *)(arg1 + 0x2654) = 1;
      *(int *)(arg1 + 0x2664) = arg3;
      *(int *)(arg1 + 0x2668) = arg4;
      *(uint32_t *)(arg1 + 0x2660) = 2;
    }
    else {
      *(int *)(arg1 + 0x2658) = arg3;
      *(int *)(arg1 + 0x265c) = arg4;
      *(uint32_t *)(arg1 + 0x2654) = 2;
    }
  }
  return 1;
}

/* AIMoveReachedDest @ 0x080a88d0, 54 bytes
 *
 * Returns true if the AI has reached its movement destination.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: AIMoveReachedDestIdx
 * Called by: AIForNormalDecisions
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
uint32_t AIMoveReachedDest(int arg1)

{
  int i1;
  uint32_t u2;
  
  i1 = *(int *)(arg1 + 0x266c);
  if ((i1 < 1) && (*(int *)(arg1 + 0x2660 + i1 * 0xc) != 0)) {
    u2 = 0;
  }
  else {
    u2 = AIMoveReachedDestIdx(arg1,i1);
  }
  return u2;
}

/* AIMoveReachedDestIdx @ 0x080a8910, 246 bytes
 *
 * Returns true if the AI has reached step `idx` of its movement plan.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Called by: AIForNormalMove, AIMoveReachedDest
 *
 * Elecbyte file: src/mugen/p-ai.c
 * Note: 2 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t AIMoveReachedDestIdx(int arg1,int arg2)

{
  float80 f1;
  int i2;
  int i3;
  
  i2 = *(int *)(arg2 * 0xc + 0x2c + arg1 + 0x262c);
  i3 = *(int *)(arg2 * 0xc + 0x30 + arg1 + 0x262c);
  if (((*(int *)(arg1 + 0x264c) <= i2) && ((float)(i2 + -1) <= *(float *)(arg1 + 0x19c))
      ) || ((i2 <= *(int *)(arg1 + 0x264c) &&
            (*(float *)(arg1 + 0x19c) <= (float)(i2 + 1))))) {
    f1 = *(float *)(arg1 + 0x1b4);
    if (f1 != 0.0) {
      return 1;
    }
    if (*(int *)(arg1 + 0x2644) != 2) {
      return 1;
    }
  }
  else {
    f1 = *(float *)(arg1 + 0x1b4);
  }
  if ((f1 == 0.0) &&
     (((*(float *)(arg1 + 0x1b8) < 0.0 && (*(float *)(arg1 + 0x1a0) < (float80)i3)) ||
      ((f1 == 0.0 &&
       ((0.0 < *(float *)(arg1 + 0x1b8) && ((float80)i3 <= *(float *)(arg1 + 0x1a0))))))))) {
    return 1;
  }
  return 0;
}

/* AIForNormalIdle @ 0x080a8a10, 189 bytes
 *
 * Idle mode: releases keys except the ones to keep, optionally holding a
 * direction.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: AIKBReleaseAllExcept, KBIStuffBufNoFlip, AIKBReleaseDirExcept
 * Called by: AIForNormal
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
uint32_t AIForNormalIdle(int arg1)

{
  uint32_t u1;
  
  u1 = 0;
  if (*(int *)(arg1 + 0x3424) != 0) {
    if (*(int *)(arg1 + 0x263c) == 1) {
      u1 = 3;
    }
    if ((*(int *)(arg1 + 0x2638) == 0) &&
       (*(uint32_t *)(arg1 + 0x2640) = 0, *(int *)(arg1 + 0x2634) == 4)) {
      AIKBReleaseAllExcept(arg1,u1);
    }
    if ((*(int *)(arg1 + 0x263c) == 1) && (*(int *)(arg1 + 0x2cc) == 0)) {
      KBIStuffBufNoFlip(arg1 + 0x248,3);
    }
    if (((0 < *(int *)(arg1 + 0x2638)) && (*(int *)(arg1 + 0x2634) - 2U < 2)) &&
       (*(int *)(arg1 + 0x2da8) == 0)) {
      AIKBReleaseDirExcept(arg1,u1);
    }
    *(int *)(arg1 + 0x2640) = *(int *)(arg1 + 0x2640) + 1;
  }
  return 0;
}

/* AISetIdleAction @ 0x080a8ad0, 15 bytes
 *
 * Sets the AI's idle action. Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void AISetIdleAction(int arg1,uint32_t arg2)

{
  *(uint32_t *)(arg1 + 0x263c) = arg2;
  return;
}

/* AIForNormalMove @ 0x080a8ae0, 737 bytes
 *
 * Move mode: presses the direction (and jump) keys of the movement plan
 * until the destination is reached.
 *
 * Parameters:
 *   player       int
 *
 * Player fields read: pos_x, pos_y, statetype
 * Calls: AIMoveReachedDestIdx, KBIStuffBufNoFlip
 * Called by: AIForNormal
 *
 * Elecbyte file: src/mugen/p-ai.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to NAN
 * Note: 7 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
uint32_t AIForNormalMove(int player)

{
  int i1;
  int i2;
  bool b3;
  int i4;
  int i5;
  uint32_t u6;
  int i7;
  uint32_t stk_20;
  
  stk_20 = 0xffffffff;
  i1 = player + 0x248;
  if (*(int *)(player + 0x3424) == 0) {
    return 0;
  }
  if (*(int *)(player + 0x2638) == 0) {
    *(uint32_t *)(player + 0x2648) = 0;
  }
  do {
    b3 = false;
    i5 = *(int *)(player + 0x266c);
    i4 = i5 * 0xc;
    i7 = (int)X87_FIST32(((float80)*(int *)(i4 + 0x2c + player + 0x262c) -
                       *(float *)(player + PLB_POS_X)) * (float80)*(int *)(player + 400));
    i2 = (int)X87_FIST32((float80)*(int *)(i4 + 0x30 + player + 0x262c) -
                       *(float *)(player + PLB_POS_Y));
    if (*(int *)(player + 0x2648) == 0) {
      *(int *)(player + 0x264c) = (int)X87_FIST32(*(float *)(player + PLB_POS_X));
      *(int *)(player + 0x2650) = (int)X87_FIST32(*(float *)(player + PLB_POS_Y));
      *(uint32_t *)(player + 0x2644) = *(uint32_t *)(i4 + player + 0x2654);
    }
    else if (((i5 < 1) && (*(int *)(player + 0x2660 + i4) != 0)) &&
            (i5 = AIMoveReachedDestIdx(player,i5), i5 != 0)) {
      *(int *)(player + 0x266c) = *(int *)(player + 0x266c) + 1;
      *(uint32_t *)(player + 0x2648) = 0;
      b3 = true;
    }
  } while (b3);
  if (*(int *)(player + 0x2644) == 1) {
    if (i7 < 1) {
      if (i7 < 0) {
        stk_20 = 4;
      }
    }
    else {
      stk_20 = 2;
    }
    u6 = 1;
    i7 = 0x74;
    do {
      if ((*(int *)(i7 + player + 0x250) != 0) && (u6 != stk_20)) {
        KBIStuffBufNoFlip(i1,u6 | 0x10);
      }
      u6 = u6 + 1;
      i7 = i7 + 4;
    } while ((int)u6 < 5);
    if ((stk_20 == 0xffffffff) || (*(int *)(player + 0x2c0 + stk_20 * 4) != 0))
    goto L_080a8db0;
  }
  else {
    if ((*(int *)(player + 0x2644) != 2) || (*(int *)(player + PLB_STATETYPE) == 3)) goto L_080a8db0;
    if (i7 < 1) {
      if ((i7 < 0) &&
         ((float80)i2 * *(float *)(player + 0xf0) < (float80)i7 * *(float *)(player + 0xe4))) {
        stk_20 = 4;
      }
    }
    else if ((float80)i7 * *(float *)(player + 0xe4) < (float80)i2 * *(float *)(player + 0xec))
    {
      stk_20 = 2;
    }
    u6 = 1;
    i7 = 0x74;
    do {
      if (((*(int *)(i7 + 8 + i1) != 0) && (u6 != stk_20)) && (u6 != 1)) {
        KBIStuffBufNoFlip(i1,u6 | 0x10);
      }
      u6 = u6 + 1;
      i7 = i7 + 4;
    } while ((int)u6 < 5);
    if ((stk_20 != 0xffffffff) && (*(int *)(player + 0x2c0 + stk_20 * 4) == 0)) {
      KBIStuffBufNoFlip(i1,stk_20);
    }
    if (*(int *)(player + 0x2c4) != 0) goto L_080a8db0;
    stk_20 = 1;
  }
  KBIStuffBufNoFlip(i1,stk_20);
L_080a8db0:
  *(int *)(player + 0x2648) = *(int *)(player + 0x2648) + 1;
  return 0;
}

/* AIForNormalAttack @ 0x080a8dd0, 474 bytes
 *
 * Attack mode: performs the chosen attack by pressing its keys or queuing
 * its command (AIInsertCommand), then returns to another mode.
 *
 * Parameters:
 *   player       int
 *   arg2         int
 *
 * Player fields read: statetype, movetype
 * Calls: AIChangeState, KBIStuffBufNoFlip, AIInsertCommand
 * Called by: AIForNormal
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
uint32_t AIForNormalAttack(int player,int arg2)

{
  int i1;
  int i2;
  uint32_t u3;
  int i4;
  int i5;
  uint32_t stk_18;
  
  i2 = *(int *)(player + 0x2670);
  i1 = player + 0x248;
  if (i2 == 0) {
    u3 = AIChangeState(player + 0x262c,0);
    return u3;
  }
  if (*(int *)(player + 0x2638) == 0) {
    *(uint32_t *)(player + 0x2674) = 0;
    i5 = 0;
    stk_18 = *(int *)(i2 + 0x200);
    if (0 < stk_18) {
      i4 = *(int *)(i2 + 4);
      if (i4 == *(int *)(player + PLB_STATETYPE)) {
        *(int *)(player + 0x2674) = i4;
      }
      else {
        do {
          if (*(int *)(player + 0x2674) == 0) {
            *(int *)(player + 0x2674) = i4;
            stk_18 = *(int *)(i2 + 0x200);
          }
          i5 = i5 + 1;
          if (stk_18 <= i5) goto L_080a8e87;
          i4 = *(int *)(i5 * 0x10 + 4 + i2);
        } while (i4 != *(int *)(player + PLB_STATETYPE));
        *(int *)(player + 0x2674) = i4;
      }
    }
  }
L_080a8e87:
  if (*(int *)(player + 0x2678) != 0) goto L_080a8f6e;
  i5 = *(int *)(player + 0x2674);
  if (i5 == 0) {
L_080a8f3b:
    i4 = *(int *)(player + PLB_STATETYPE);
  }
  else {
    i4 = *(int *)(player + PLB_STATETYPE);
    if (i4 != i5) {
      if (i5 == 2) {
        if (*(int *)(player + 0x2c4) != 0) {
          KBIStuffBufNoFlip(i1,0x11);
        }
        if (*(int *)(player + 0x2cc) == 0) {
          KBIStuffBufNoFlip(i1,3);
        }
      }
      if (i5 == 1) {
        if (*(int *)(player + 0x2c4) != 0) {
          KBIStuffBufNoFlip(i1,0x11);
        }
        if (*(int *)(player + 0x2cc) != 0) {
          KBIStuffBufNoFlip(i1,0x13);
        }
      }
      if (i5 == 3) {
        if (*(int *)(player + 0x2cc) != 0) {
          KBIStuffBufNoFlip(i1,0x13);
        }
        if (*(int *)(player + 0x2c4) == 0) {
          KBIStuffBufNoFlip(i1,1);
        }
      }
      goto L_080a8f3b;
    }
  }
  if ((i4 == i5) || (4 < *(int *)(player + 0x2638))) {
    AIInsertCommand((int *)(player + 0x33fc),*(int *)(i2 + 0x20c));
    *(uint32_t *)(player + 0x2678) = 1;
  }
L_080a8f6e:
  if (((*(int *)(player + PLB_MOVETYPE) == 0) && (*(int *)(player + 0x2678) != 0)) &&
     (0 < *(int *)(player + 0x2638))) {
    u3 = AIChangeState(player + 0x262c,0);
    return u3;
  }
  return 0;
}

/* AIAttackSetupAttack @ 0x080a8fb0, 40 bytes
 *
 * Stores the attack the AI has chosen (learned entry and command).
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t
 *   arg3         uint32_t
 *
 * Called by: AIForNormalDecisions
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
uint32_t AIAttackSetupAttack(int arg1,uint32_t arg2,uint32_t arg3)

{
  *(uint32_t *)(arg1 + 0x2670) = arg3;
  *(uint32_t *)(arg1 + 0x2674) = 0;
  *(uint32_t *)(arg1 + 0x2678) = 0;
  return 1;
}

/* AIForNormalGuard @ 0x080a8fe0, 211 bytes
 *
 * Guard mode: holds back (and down for low attacks) while an attack is
 * coming, then returns to another mode.
 *
 * Parameters:
 *   player       int
 *   arg2         int
 *
 * Player fields read: movetype, ctrl
 * Calls: AIChangeState, KBIStuffBufNoFlip
 * Called by: AIForNormal
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
uint32_t AIForNormalGuard(int player,int arg2)

{
  int i1;
  uint32_t u2;
  uint32_t u3;
  
  i1 = player + 0x248;
  if (*(int *)(player + 0x3424) == 0) {
    u2 = AIChangeState(player + 0x262c,0);
    return u2;
  }
  if (((*(int *)(player + 0x2da8) != 0) && (*(int *)(player + PLB_MOVETYPE) == 0)) &&
     (*(int *)(player + PLB_CTRL) != 0)) {
    if (*(int *)(player + 0x2c4) != 0) {
      KBIStuffBufNoFlip(i1,0x11);
    }
    if (*(int *)(player + 0x2c8) != 0) {
      KBIStuffBufNoFlip(i1,0x12);
    }
    if (*(int *)(player + 0x2d0) == 0) {
      KBIStuffBufNoFlip(i1,4);
    }
    if (*(int *)(player + 0x2b58) == 0) {
      if (*(int *)(player + 0x2cc) == 0) {
        return 0;
      }
      u3 = 0x13;
    }
    else {
      if (*(int *)(player + 0x2cc) != 0) {
        return 0;
      }
      u3 = 3;
    }
    KBIStuffBufNoFlip(i1,u3);
  }
  return 0;
}

/* AIAttackInRange @ 0x080a90c0, 723 bytes
 *
 * Returns true if a learned attack, done from the AI's position, would hit
 * the enemy's current body boxes (ClsnArrayDetectRectFlip against the
 * recorded extents).
 *
 * Parameters:
 *   player       int
 *   arg2         uint32_t
 *   player2      int  (player)
 *   arg4         int
 *
 * Player fields read: pos_x, pos_y, anim
 * Calls: AIIdleClsnMatchState, ClsnArrayDetectRectFlip
 * Called by: AIBuildCounterAttackList, AIForNormalDecisions
 *
 * Elecbyte file: src/mugen/p-ai.c
 * Note: Locals live in `frame`, laid out as on the original stack (0xa0 bytes, 7
 *       variables), because their address is taken.
 * Note: 6 temporaries are float80, as the original kept them in x87 registers.
 */
int AIAttackInRange(int player,uint32_t arg2,int player2,int arg4)

{
  float80 f1;
  float80 f2;
  float80 f3;
  float80 f4;
  float80 f5;
  float80 f6;
  int i7;
  int i8;
  int i9;
  int i2;
  int *pi11;
  float *pf12;
  unsigned char frame[0xa0] __attribute__((aligned(16)));
#define stk_a0 (*(int **)(frame + 0x0))
#define stk_94 (*(uint32_t *)(frame + 0xc))
#define stk_90 (*(uint32_t *)(frame + 0x10))
#define stk_8c (*(int **)(frame + 0x14))
#define stk_88 (*(int **)(frame + 0x18))
#define stk_7c (*(int (*)[12])(frame + 0x24))
#define stk_4c (*(int (*)[15])(frame + 0x54))
  
  stk_90 = (uint32_t)(*(int *)(player + 400) != 1);
  stk_94 = (uint32_t)(*(int *)(player2 + 400) != 1);
  f1 = *(float *)(player + PLB_POS_X);
  f2 = *(float *)(player2 + PLB_POS_X);
  f3 = *(float *)(player + PLB_POS_Y);
  f4 = *(float *)(player2 + PLB_POS_Y);
  i8 = *(int *)(*(int *)(player + PLB_ANIM) + 0x10);
  if ((i8 != 0) && (i2 = *(int *)(*(int *)(player2 + PLB_ANIM) + 0x10), i2 != 0)) {
    stk_88 = *(int **)(i8 + 0x2c);
    stk_8c = *(int **)(i2 + 0x28);
    i2 = 0;
    stk_a0 = stk_7c;
    pi11 = stk_4c;
    for (i8 = 10; i8 != 0; i8 = i8 + -1) {
      *pi11 = 0;
      pi11 = pi11 + 1;
    }
    i8 = 0;
    do {
      if (i2 == 0) {
        i7 = *(int *)(player + 0x267c);
        i9 = player;
      }
      else {
        i7 = *(int *)(player2 + 0x267c);
        i9 = player2;
        if (arg4 != 0) {
          i7 = arg4;
        }
      }
      pf12 = (float *)(i7 + 0x2f4U & (i7 == 0) - 1);
      if ((i2 == 0) && (i7 = AIIdleClsnMatchState(*(int *)(i9 + 0xbf4)), i7 != -1)) {
        pf12 = (float *)(i7 * 0x40 + 0x2db8 + i9);
      }
      pi11 = stk_88;
      if ((pf12 != (float *)0x0) && (f5 = *pf12, f5 != -32760.0)) {
        *(uint32_t *)((int)stk_7c + i8) = 0;
        f6 = pf12[4];
        *(int *)((int)stk_7c + i8 + 4) = (int)X87_FIST32(f5);
        f5 = pf12[8];
        *(int *)((int)stk_7c + i8 + 8) = (int)X87_FIST32(f6);
        f6 = pf12[0xc];
        *(int *)((int)stk_7c + i8 + 0xc) = (int)X87_FIST32(f5);
        *(int *)((int)stk_7c + i8 + 0x10) = (int)X87_FIST32(f6);
        *(uint32_t *)(i8 + (int)stk_4c) = 1;
        *(uint32_t *)((int)stk_4c + i8 + 4) = 1;
        *(int **)((int)stk_4c + i8 + 8) = stk_a0;
        pi11 = stk_4c;
        if (i2 != 0) {
          stk_8c = (int *)((int)stk_4c + i8);
          pi11 = stk_88;
        }
      }
      stk_88 = pi11;
      i2 = i2 + 1;
      stk_a0 = stk_a0 + 5;
      i8 = i8 + 0x14;
    } while (i2 < 2);
    if ((((stk_88 != (int *)0x0) && (stk_8c != (int *)0x0)) && (*stk_88 != 0)) &&
       (*stk_8c != 0)) {
      i8 = ClsnArrayDetectRectFlip
                        (stk_88,stk_8c,(int)X87_FIST32(f2 - f1),(int)X87_FIST32(f4 - f3),
                         stk_90,stk_94);
      return ((i8 != 0) - 1 & 0xffffff9c) + 100;
    }
  }
  return 0;
}
#undef stk_a0
#undef stk_94
#undef stk_90
#undef stk_8c
#undef stk_88
#undef stk_7c
#undef stk_4c

/* AIBuildCounterAttackList @ 0x080a93a0, 661 bytes
 *
 * Builds the list of learned attacks that would hit the enemy from here, for
 * the enemy's hit-state class. Asserts "e_hitstateidx >= 0 && e_hitstateidx
 * < AIPLHS_NUM".
 *
 * Parameters:
 *   player       int
 *   arg2         uint32_t
 *
 * Player fields read: statetype, active, ctrl
 * Calls: AIFetchLearnDataArray, ArrayScanFirst, AIAttackInRange,
 *        ArrayScanNext
 * C library: __assert_fail
 * Called by: AIForNormalDecisions
 * Messages:
 *   "e_hitstateidx >= 0 && e_hitstateidx < AIPLHS_NUM"
 *
 * Elecbyte file: src/mugen/p-ai.c
 * Note: 3 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
int AIBuildCounterAttackList(int player,uint32_t arg2)

{
  int i1;
  float80 f2;
  int player2;
  bool b4;
  bool b5;
  int array;
  int item;
  int i8;
  uint32_t u9;
  uint32_t u10;
  int i11;
  
  player2 = *(int *)(player + 0x268c);
  b5 = false;
  *(uint32_t *)(player + 0x2c24) = 0;
  if (*(int *)(player + 0x2b44) != 0) {
    array = AIFetchLearnDataArray(player + 0x2dac,*(int *)(player + PLB_STATETYPE));
    if (array != 0) {
      if ((player2 == 0) || (b4 = true, *(int *)(player2 + PLB_ACTIVE) == 0)) {
        b4 = false;
      }
      if (b4) {
        u10 = *(uint32_t *)(player2 + 0x2ed8);
        if (2 < u10) {
                    /* WARNING: Subroutine does not return */
          __assert_fail("e_hitstateidx >= 0 && e_hitstateidx < AIPLHS_NUM","src/mugen/p-ai.c",0x783,
                        "AIBuildCounterAttackList");
        }
        f2 = *(float *)(player + 0x28c4);
        if (f2 <= (float80)*(int *)(player + 0x2b48)) {
          if (*(float *)(u10 * 0x30 + 0x394 + player + 0x2690) == 0.0) {
            return 0;
          }
          f2 = *(float *)(u10 * 0x30 + 0x394 + player + 0x2690);
        }
        else {
          b5 = true;
        }
        i1 = (int)X87_FIST32(f2 - (float80)*(int *)(player + 0x2b48));
        i11 = 0;
        item = ArrayScanFirst(array);
        if (item != 0) {
          do {
            u10 = ((float80)i1 <= *(float *)(item + 0x234)) - 1 & 100;
            i8 = AIAttackInRange(player2,arg2,player,item);
            if (i8 == 0) {
              u10 = u10 - 100;
            }
            if (*(int *)(item + 0x380) != 0) {
              if (b5) {
                if ((int)X87_FIST32(*(float *)(item + 0x264)) < i1) {
                  u10 = u10 - 100;
                }
                u9 = *(uint32_t *)(player + 0x2a0c) & *(uint32_t *)(item + 0x380);
                if (((u9 & 7) != 0) && ((u9 & 0xfffffff8) != 0)) goto L_080a95ac;
              }
              u10 = u10 - 100;
            }
L_080a95ac:
            if ((((*(uint32_t *)(player + 0x2a10) != 0) &&
                 (u9 = *(uint32_t *)(player + 0x2a10) & *(uint32_t *)(item + 0x37c), b5)) &&
                ((u9 & 7) != 0)) && ((u9 & 0xfffffff8) != 0)) {
              u10 = u10 - 100;
            }
            if (*(int *)(player + PLB_CTRL) == 0) {
              u10 = u10 - 100;
            }
            if (0 < (int)u10) {
              *(int *)(player + 0x2b5c + i11 * 4) = item;
              i11 = i11 + 1;
            }
            item = ArrayScanNext(array);
          } while ((item != 0) && (i11 < 0x31));
        }
        *(uint32_t *)(player + 0x2b5c + i11 * 4) = 0;
        *(int *)(player + 0x2c24) = i11;
        return i11;
      }
    }
  }
  return 0;
}

/* AIForNormalRandom @ 0x080a9640, 2057 bytes
 *
 * Random mode: picks random actions (move, jump, guard, attack with a random
 * command), weighted by distance and by messages from the enemy.
 *
 * Parameters:
 *   player       int
 *   player2      int  (player)
 *   arg3         int
 *
 * Player fields read: pos_x, movetype, ctrl, statetime, statetype,
 *                     movecontact, hitfall, pos_y, vel_y
 * Calls: PlayerAIGetAndRemoveMsg, PlayerAIGetMsg, AIChangeState,
 *        PlayerInGuardDist, KBIStuffBufNoFlip, AIInsertCommand
 * C library: random
 * Called by: AIForNormal
 *
 * Elecbyte file: src/mugen/p-ai.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x50 bytes, 4
 *       variables), because their address is taken.
 */
uint32_t AIForNormalRandom(int player,int player2,int arg3)

{
  long l1;
  uint32_t u2;
  int i3;
  int i4;
  int i5;
  uint32_t u6;
  int *pi7;
  int i8;
  unsigned char frame[0x50] __attribute__((aligned(16)));
#define stk_44 (*(uint32_t *)(frame + 0xc))
#define stk_40 (*(int *)(frame + 0x10))
#define stk_2c (*(uint32_t *)(frame + 0x24))
#define stk_28 (*(int *)(frame + 0x28))
  
  i4 = player + 0x2cec;
  i5 = player + 0x248;
  stk_40 = (int)X87_FIST32(*(float *)(player + PLB_POS_X) - *(float *)(player2 + PLB_POS_X));
  if (stk_40 < 0) {
    stk_40 = -stk_40;
  }
  l1 = random();
  u6 = l1 % 6 + 5;
  l1 = random();
  stk_44 = l1 % 6 + 5;
  if (((arg3 == 9) && (PlayerAIGetAndRemoveMsg(&stk_2c,player,player2,1), stk_28 != -1)) ||
     (PlayerAIGetMsg(&stk_2c,player,player2,0), stk_28 != -1)) {
    u2 = AIChangeState(player + 0x262c,0);
    return u2;
  }
  l1 = random();
  if (l1 % 100 == 0) {
    u6 = 0xb;
  }
  if ((stk_44 == u6) || (u6 = random(), (u6 & 7) != 0)) {
    stk_44 = 0;
  }
  i8 = *(int *)(player + 0x2da8);
  if (i8 != 0) {
    i3 = *(int *)(player + PLB_MOVETYPE);
    if ((i3 != 0) || (*(int *)(player + PLB_CTRL) == 0)) goto L_080a97a0;
L_080a97a9:
    i8 = 10;
    i3 = *(int *)(player + PLB_STATETIME);
    if (i3 < 2) {
      i8 = arg3 / 2 + 0x1a;
    }
    if (i3 < 5) {
      i8 = i8 + 5;
    }
    if (10 < i3) {
      i8 = i8 + -5;
    }
    if ((stk_40 < 0x1e) && (i8 = arg3 / 2 + 6 + i8, i3 < 2)) {
      i8 = i8 + 10;
    }
    if (0xa0 < stk_40) {
      i8 = i8 / 2;
    }
    i3 = PlayerInGuardDist(player,player2);
    if (i3 == 0) {
      i8 = i8 / 5;
    }
    l1 = random();
    if (((arg3 + 6) * i8) / 0xe <= l1 % 100) {
      i8 = *(int *)(player + 0x2da8);
      goto L_080a999a;
    }
    if (*(int *)(player + 0xe10) == 0) {
      i4 = *(int *)(player2 + PLB_STATETYPE);
      if (*(int *)(player + 0x2c4) != 0) {
        KBIStuffBufNoFlip(i5,0x11);
      }
      if (*(int *)(player + 0x2c8) != 0) {
        KBIStuffBufNoFlip(i5,0x12);
      }
      if (*(int *)(player + 0x2d0) == 0) {
        KBIStuffBufNoFlip(i5,4);
      }
      l1 = random();
      if ((int)(((i4 == 2) - 1 & 0xffffffce) + 0x4b) <= l1 % 100) {
        i4 = *(int *)(player + 0x2cc);
        goto L_join_080a9980;
      }
      if (*(int *)(player + 0x2cc) != 0) {
        return 0;
      }
      u6 = 3;
    }
    else {
      l1 = random();
      if (0x1d < l1 % 100) {
        return 0;
      }
      u6 = *(uint32_t *)(player2 + 0x11cc);
      if (((u6 & 0xc) == 8) && (*(int *)(player + 0x2cc) == 0)) {
        KBIStuffBufNoFlip(i5,3);
        u6 = *(uint32_t *)(player2 + 0x11cc);
      }
      if ((u6 & 0xc) != 4) {
        return 0;
      }
      i4 = *(int *)(player + 0x2cc);
L_join_080a9980:
      if (i4 == 0) {
        return 0;
      }
      u6 = 0x13;
    }
    goto L_080a9e37;
  }
  i3 = *(int *)(player + PLB_MOVETYPE);
L_080a97a0:
  if (i3 == 2) goto L_080a97a9;
L_080a999a:
  if ((i8 == 0) && (*(int *)(player + 0x2d0) != 0)) {
    KBIStuffBufNoFlip(i5,0x14);
  }
  l1 = random();
  if (0x39 < l1 % 100) goto L_080a9d75;
  l1 = random();
  if (((l1 % 1000 < 0x3e) && (0x7d < stk_40)) && (*(int *)(player + 0x2c8) == 0)) {
    u6 = 1;
    pi7 = (int *)(player + 0x2c4);
    do {
      if (*pi7 != 0) {
        KBIStuffBufNoFlip(i5,u6 | 0x10);
      }
      u6 = u6 + 1;
      pi7 = pi7 + 1;
    } while ((int)u6 < 5);
    l1 = random();
    if (l1 % 1000 < 0x96) {
      KBIStuffBufNoFlip(i5,1);
    }
    l1 = random();
    if (l1 % 1000 < 0x2ee) {
      KBIStuffBufNoFlip(i5,2);
    }
  }
  l1 = random();
  if (0x3d < l1 % 1000) goto L_default_080a9ada;
  u6 = 1;
  pi7 = (int *)(player + 0x2c4);
  do {
    if (*pi7 != 0) {
      KBIStuffBufNoFlip(i5,u6 | 0x10);
    }
    u6 = u6 + 1;
    pi7 = pi7 + 1;
  } while ((int)u6 < 5);
  l1 = random();
  switch(l1 % 0x13) {
  case 0:
    KBIStuffBufNoFlip(i5,1);
    u6 = 4;
    break;
  case 1:
    u6 = 1;
    break;
  case 2:
  case 3:
  case 4:
    KBIStuffBufNoFlip(i5,1);
    goto L_080a9b3c;
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
    goto L_080a9b3c;
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
    u6 = 4;
    break;
  case 0xf:
    KBIStuffBufNoFlip(i5,3);
    u6 = 4;
    break;
  case 0x10:
  case 0x11:
    u6 = 3;
    break;
  case 0x12:
    KBIStuffBufNoFlip(i5,3);
L_080a9b3c:
    u6 = 2;
    break;
  default:
    goto L_default_080a9ada;
  }
  KBIStuffBufNoFlip(i5,u6);
L_default_080a9ada:
  i8 = 100;
  if ((*(int *)(player + PLB_MOVETYPE) == 1) && (i8 = 0x96, *(int *)(player + PLB_MOVECONTACT) == 2)) {
    i8 = (arg3 * 0x15e + 0x1068) / 0x14 + 0x96;
  }
  if (stk_40 < 0x96) {
    i8 = i8 + 0x32;
  }
  if (stk_40 < 100) {
    i8 = i8 + 0x4b;
  }
  if (stk_40 < 0x3c) {
    i8 = arg3 * 5 + 0x69 + i8;
  }
  if (stk_40 < 0x2d) {
    i8 = arg3 * 3 + 0x78 + i8;
  }
  if (stk_40 < 0x1e) {
    i8 = arg3 * 3 + 0x78 + i8;
  }
  i8 = ((arg3 + 6) * i8) / 0xe;
  if (*(int *)(player + PLB_MOVETYPE) == 2) {
    i8 = i8 / 10;
  }
  l1 = random();
  if (l1 % 1000 < i8) {
    i8 = 500;
    if (*(int *)(player + PLB_MOVECONTACT) == 2) {
      if ((*(uint32_t *)(player + 0x1164) & 0x6d8) != 0) {
        i8 = 0xfa;
      }
    }
    else {
      i8 = 0x2ee;
    }
    l1 = random();
    if (l1 % 1000 < i8) {
      l1 = random();
      stk_44 = l1 % 6 + 5;
      if (*(int *)(player + 0x2c0 + stk_44 * 4) != 0) {
        stk_44 = stk_44 | 0x10;
      }
    }
    else {
      u6 = 1;
      pi7 = (int *)(player + 0x2c4);
      do {
        if (*pi7 != 0) {
          KBIStuffBufNoFlip(i5,u6 | 0x10);
        }
        u6 = u6 + 1;
        pi7 = pi7 + 1;
      } while ((int)u6 < 5);
      l1 = random();
      if ((l1 % 1000 < arg3 * 0x1e + 0x226) && (g[0x757f] != 0)) {
        l1 = random();
        AIInsertCommand((int *)(player + 0x33fc),l1 % *(int *)(*(int *)(player + 0x964) + 0xc))
        ;
      }
      KBIStuffBufNoFlip(i4,stk_44);
      stk_44 = stk_44 | 0x10;
      i5 = i4;
    }
    KBIStuffBufNoFlip(i5,stk_44);
  }
L_080a9d75:
  if ((*(int *)(player + PLB_MOVETYPE) == 2) && (*(int *)(player + PLB_HITFALL) != 0)) {
    i5 = 2;
    if (-20.0 < *(float *)(player + PLB_POS_Y)) {
      i5 = 0x14;
    }
    if ((-1.0 < *(float *)(player + PLB_VEL_Y)) && (*(float *)(player + PLB_VEL_Y) < 3.0)) {
      i5 = i5 + 8;
    }
    l1 = random();
    if (l1 % 100 < i5) {
      l1 = random();
      if (l1 % 100 < 0x32) {
        KBIStuffBufNoFlip(i4,5);
        u6 = 6;
        i5 = i4;
      }
      else {
        KBIStuffBufNoFlip(i4,8);
        u6 = 9;
        i5 = i4;
      }
L_080a9e37:
      KBIStuffBufNoFlip(i5,u6);
    }
  }
  return 0;
}
#undef stk_44
#undef stk_40
#undef stk_2c
#undef stk_28

/* AIForTrainingMode @ 0x080a9e50, 1796 bytes
 *
 * The training dummy: acts as configured in the training menu (stand,
 * crouch, jump, guard, button jam, keep distance, cooperative...).
 *
 * Parameters:
 *   player       int
 *   arg2         int
 *
 * Player fields read: movetype, ctrl, pos_x, vel_x, pos_y, vel_y
 * Calls: KBIStuffBufNoFlip, PlayerInCorner
 * Called by: PlayerAI
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void AIForTrainingMode(int player,int arg2)

{
  int i1;
  int i2;
  uint32_t u3;
  
  i2 = *(int *)(player + 0x2ce8);
  i1 = player + 0x248;
  if (i2 != 0) goto L_080aa545;
  if (((*(int *)(player + 0x2da8) == 0) || (*(int *)(player + PLB_MOVETYPE) != 0)) ||
     (*(int *)(player + PLB_CTRL) == 0)) {
L_080a9f6f:
    i2 = *(int *)(player + 0xe10);
  }
  else {
    if (*(int *)(player + 0x2cd8) == 0) {
      if (*(int *)(player + 0x2d0) != 0) {
        KBIStuffBufNoFlip(i1,0x14);
      }
      goto L_080a9f6f;
    }
    i2 = *(int *)(player + 0xe10);
    if (i2 == 0) {
      if (*(int *)(player + 0x2c4) != 0) {
        KBIStuffBufNoFlip(i1,0x11);
      }
      if (*(int *)(player + 0x2c8) != 0) {
        KBIStuffBufNoFlip(i1,0x12);
      }
      u3 = *(uint32_t *)(arg2 + 0x11cc);
      if (((u3 & 0xc) == 8) && (*(int *)(player + 0x2cc) == 0)) {
        KBIStuffBufNoFlip(i1,3);
        u3 = *(uint32_t *)(arg2 + 0x11cc);
      }
      if (((u3 & 0xc) == 4) && (*(int *)(player + 0x2cc) != 0)) {
        KBIStuffBufNoFlip(i1,0x13);
      }
      if (*(int *)(player + 0x2d0) != 0) {
        return;
      }
      u3 = 4;
      goto L_080aa514;
    }
  }
  if (i2 != 0) {
    if (*(int *)(player + 0x2da8) != 0) {
      return;
    }
    if (*(int *)(player + 0x2d0) == 0) {
      return;
    }
    u3 = 0x14;
    goto L_080aa514;
  }
  if (*(int *)(player + 0x2cdc) != 0) {
    i2 = (int)X87_FIST32(*(float *)(player + PLB_POS_X) - *(float *)(arg2 + 0x19c));
    if (i2 < 0) {
      i2 = -i2;
    }
    if (*(int *)(player + 0x2cdc) < i2) {
      if (*(int *)(player + 0x2cd4) == 1) {
        if (((*(int *)(player + 0x2c4) != 0) || (*(int *)(player + 0x2cc) != 0)) ||
           (i2 = 0, *(int *)(player + 0x2d0) != 0)) {
          *(uint32_t *)(player + 0x2ce8) = 5;
          goto L_080aa01b;
        }
      }
      else {
L_080aa01b:
        i2 = *(int *)(player + 0x2c4);
      }
      if (i2 != 0) {
        KBIStuffBufNoFlip(i1,0x11);
      }
      if (*(int *)(player + 0x2cc) != 0) {
        KBIStuffBufNoFlip(i1,0x13);
      }
      if (*(int *)(player + 0x2d0) != 0) {
        KBIStuffBufNoFlip(i1,0x14);
      }
      if (*(int *)(player + 0x2ce8) != 0) {
        return;
      }
      if (*(int *)(player + 0x2c8) != 0) {
        return;
      }
      u3 = 2;
      goto L_080aa514;
    }
    i2 = (int)X87_FIST32(*(float *)(player + PLB_POS_X) - *(float *)(arg2 + 0x19c));
    if (i2 < 0) {
      i2 = -i2;
    }
    if (((float)(*(int *)(player + 0x2cdc) - i2) <
         (float)(*(int *)(arg2 + 400) * -0x14) * *(float *)(arg2 + 0x1b4)) &&
       ((*(float *)(player + PLB_POS_X) - *(float *)(arg2 + 0x19c)) * *(float *)(player + PLB_VEL_X) <=
        0.0)) {
      return;
    }
    if (*(int *)(player + 0x2c8) != 0) {
      u3 = 0x12;
      goto L_080aa514;
    }
  }
  if ((*(int *)(player + 0x2ce0) != 0) && (i2 = PlayerInCorner(player), i2 == 0)) {
    i2 = (int)X87_FIST32(*(float *)(player + PLB_POS_X) - *(float *)(arg2 + 0x19c));
    if (i2 < 0) {
      i2 = -i2;
    }
    if (i2 < *(int *)(player + 0x2ce0)) {
      if (*(int *)(player + 0x2cd4) == 1) {
        if (((*(int *)(player + 0x2c4) != 0) || (*(int *)(player + 0x2cc) != 0)) ||
           (i2 = 0, *(int *)(player + 0x2c8) != 0)) {
          *(uint32_t *)(player + 0x2ce8) = 5;
          goto L_080aa1af;
        }
      }
      else {
L_080aa1af:
        i2 = *(int *)(player + 0x2c4);
      }
      if (i2 != 0) {
        KBIStuffBufNoFlip(i1,0x11);
      }
      if (*(int *)(player + 0x2cc) != 0) {
        KBIStuffBufNoFlip(i1,0x13);
      }
      if (*(int *)(player + 0x2c8) != 0) {
        KBIStuffBufNoFlip(i1,0x12);
      }
      if (*(int *)(player + 0x2ce8) != 0) {
        return;
      }
      if (*(int *)(player + 0x2d0) != 0) {
        return;
      }
      u3 = 4;
      goto L_080aa514;
    }
    i2 = (int)X87_FIST32(*(float *)(player + PLB_POS_X) - *(float *)(arg2 + 0x19c));
    if (i2 < 0) {
      i2 = -i2;
    }
    if (((float)(i2 - *(int *)(player + 0x2ce0)) <
         (float)(*(int *)(arg2 + 400) * 0x14) * *(float *)(arg2 + 0x1b4)) &&
       (0.0 <= (*(float *)(player + PLB_POS_X) - *(float *)(arg2 + 0x19c)) *
               *(float *)(player + PLB_VEL_X))) {
      return;
    }
    if (*(int *)(player + 0x2d0) != 0) {
      u3 = 0x14;
      goto L_080aa514;
    }
  }
  i2 = *(int *)(player + 0x2cd4);
  if (i2 == 1) {
    if (*(int *)(player + 0x2c4) != 0) {
      KBIStuffBufNoFlip(i1,0x11);
    }
    if (*(int *)(player + 0x2cc) == 0) {
      KBIStuffBufNoFlip(i1,3);
    }
    if (*(int *)(player + 0x2d0) != 0) {
      KBIStuffBufNoFlip(i1,0x14);
    }
    if (*(int *)(player + 0x2c8) != 0) {
      u3 = 0x12;
L_080aa497:
      KBIStuffBufNoFlip(i1,u3);
    }
  }
  else if (i2 < 2) {
    if (i2 == 0) {
      if (*(int *)(player + 0x2c4) != 0) {
        KBIStuffBufNoFlip(i1,0x11);
      }
      if (*(int *)(player + 0x2cc) != 0) {
        KBIStuffBufNoFlip(i1,0x13);
      }
      if (*(int *)(player + 0x2d0) != 0) {
        KBIStuffBufNoFlip(i1,0x14);
      }
      if (*(int *)(player + 0x2c8) != 0) {
        u3 = 0x12;
        goto L_080aa497;
      }
    }
  }
  else if (i2 == 2) {
    if (*(int *)(player + 0x2cc) != 0) {
      KBIStuffBufNoFlip(i1,0x13);
    }
    if (*(int *)(player + 0x2d0) != 0) {
      KBIStuffBufNoFlip(i1,0x14);
    }
    if (*(int *)(player + 0x2c8) != 0) {
      KBIStuffBufNoFlip(i1,0x12);
    }
    if (*(float *)(player + PLB_POS_Y) == 0.0) {
L_080aa46a:
      if (*(int *)(player + 0x2c4) == 0) {
        u3 = 1;
        goto L_080aa497;
      }
    }
    else if (*(int *)(player + 0x2c4) != 0) {
L_080aa495:
      u3 = 0x11;
      goto L_080aa497;
    }
  }
  else if (i2 == 3) {
    if (*(int *)(player + 0x2cc) != 0) {
      KBIStuffBufNoFlip(i1,0x13);
    }
    if (*(int *)(player + 0x2d0) != 0) {
      KBIStuffBufNoFlip(i1,0x14);
    }
    if (*(int *)(player + 0x2c8) != 0) {
      KBIStuffBufNoFlip(i1,0x12);
    }
    if (*(float *)(player + PLB_POS_Y) == 0.0) goto L_080aa46a;
    if (*(float *)(player + PLB_VEL_Y) <= 0.0) goto L_080aa495;
    if (*(int *)(player + 0x2c4) == 0) {
      u3 = 1;
      goto L_080aa497;
    }
  }
  u3 = *(uint32_t *)(player + 0x2ce4);
  if (u3 == 0) {
    return;
  }
  switch(u3) {
  case 1:
    u3 = 5;
    break;
  case 2:
    u3 = 6;
    break;
  case 3:
    u3 = 7;
    break;
  case 4:
    u3 = 8;
    break;
  case 5:
    u3 = 9;
    break;
  case 6:
    u3 = 10;
    break;
  case 7:
    u3 = 0xb;
  }
  if (*(int *)(player + 0x2c0 + u3 * 4) == 0) {
    i2 = *(int *)(player + 0x2ce8);
    if (i2 == 0) {
      *(uint32_t *)(player + 0x2ce8) = 5;
L_080aa514:
      KBIStuffBufNoFlip(i1,u3);
      return;
    }
  }
  else {
    i2 = *(int *)(player + 0x2ce8);
    if (i2 == 0) {
      KBIStuffBufNoFlip(i1,u3 | 0x10);
      *(uint32_t *)(player + 0x2ce8) = 5;
      return;
    }
  }
L_080aa545:
  *(int *)(player + 0x2ce8) = i2 + -1;
  return;
}

/* AICheckForAttacks @ 0x080aa560, 158 bytes
 *
 * Returns true if any active player that is attacking (or has live
 * projectiles) is within guard distance of the AI player.
 *
 * Parameters:
 *   arg1         int
 *
 * Player fields read: active, movetype, projectiles
 * Globals read: slot_first, slot_last
 * Calls: ProjArrayCountActive, PlayerInGuardDist
 * Called by: PlayerAI
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
uint32_t AICheckForAttacks(int arg1)

{
  bool b1;
  int i2;
  int player;
  int *pi4;
  int i5;
  int i6;
  
  i5 = g[G_SLOT_FIRST];
  if (i5 <= g[G_SLOT_LAST]) {
    i6 = i5 * 4 + 0x1cf60;
    pi4 = g;
    do {
      player = *(int *)(i6 + 4 + (int)pi4);
      if ((player == 0) || (b1 = true, *(int *)(player + PLB_ACTIVE) == 0)) {
        b1 = false;
      }
      if ((b1) &&
         (((*(int *)(player + PLB_MOVETYPE) == 1 ||
           (i2 = ProjArrayCountActive(*(int **)(player + PLB_PROJECTILES)), pi4 = g, 0 < i2)) &&
          (player = PlayerInGuardDist(arg1,player), pi4 = g, player != 0)))) {
        return 1;
      }
      i5 = i5 + 1;
      i6 = i6 + 4;
    } while (i5 <= pi4[0x745a]);
  }
  return 0;
}

/* AIValMake @ 0x080aa600, 67 bytes
 *
 * Initialises a learned value record from a sample (value, min, max, count
 * 0).
 *
 * Parameters:
 *   arg1         float *
 *   arg2         float
 *
 * Called by: PlayerAILearnMoveEnd, PlayerAILearnMoveUpdate
 *
 * Elecbyte file: src/mugen/p-ai.c
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
void AIValMake(float *arg1,float arg2)

{
  *arg1 = (float80)BITS_F2I(int, arg2);
  arg1[1] = arg2;
  arg1[2] = arg2;
  arg1[3] = 0.0;
  return;
}

/* AIValMerge @ 0x080aa650, 200 bytes
 *
 * Merges two learned value records (weighted average, min and max).
 *
 * Parameters:
 *   arg1         float *
 *   arg2         float
 *   arg3         float
 *   arg4         float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         float
 *
 * Called by: AIValMergeR
 *
 * Elecbyte file: src/mugen/p-ai.c
 * Note: 4 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
float * AIValMerge(float *arg1,float arg2,float arg3,float arg4,float arg5,
                  float arg6,float arg7,float arg8)

{
  int i1;
  
  if (BITS_F2I(int, arg7) < BITS_F2I(int, arg3)) {
    arg3 = arg7;
  }
  if (BITS_F2I(int, arg4) < BITS_F2I(int, arg8)) {
    arg4 = arg8;
  }
  i1 = (int)X87_FIST32(arg6 - arg2);
  if (i1 < 0) {
    i1 = -i1;
  }
  *arg1 = arg6 * ((double)0.05) + arg2 * ((double)0.95);
  arg1[1] = arg3;
  arg1[2] = arg4;
  arg1[3] = arg5 * ((double)0.95) + (float80)i1 * ((double)0.05);
  return arg1;
}

/* AIValMergeR @ 0x080aa720, 86 bytes
 *
 * AIValMerge for a pair of records (used field by field).
 *
 * Parameters:
 *   arg1         float *
 *   arg2         float
 *   arg3         float
 *   arg4         float
 *   arg5         int
 *
 * Calls: AIValMerge
 * Called by: AIMergeLearnData
 *
 * Elecbyte file: src/mugen/p-ai.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x20 bytes, 4
 *       variables), because their address is taken.
 */
void AIValMergeR(float *arg1,float arg2,float arg3,float arg4,int arg5)

{

  unsigned char frame[0x20] __attribute__((aligned(16)));
#define stk_1c (*(float *)(frame + 0x4))
#define stk_18 (*(float *)(frame + 0x8))
#define stk_14 (*(float *)(frame + 0xc))
#define stk_10 (*(float *)(frame + 0x10))
  
  AIValMerge(&stk_1c,*arg1,arg1[1],arg1[2],arg1[3],arg2,arg3,arg4);
  *arg1 = stk_1c;
  arg1[1] = stk_18;
  arg1[2] = stk_14;
  arg1[3] = stk_10;
  return;
}
#undef stk_1c
#undef stk_18
#undef stk_14
#undef stk_10

/* AILearnStopRecord @ 0x080aa780, 33 bytes
 *
 * Stops recording the current attack.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: PlayerAILearnMoveEnd
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
uint32_t AILearnStopRecord(int arg1)

{
  int i1;
  uint32_t *pu2;
  
  pu2 = (uint32_t *)(arg1 + 0x10c);
  for (i1 = 0x136; i1 != 0; i1 = i1 + -1) {
    *pu2 = 0;
    pu2 = pu2 + 1;
  }
  *(uint32_t *)(arg1 + 0x10c) = 0;
  return 0;
}

/* AIMergeLearnData @ 0x080aa7b0, 2255 bytes
 *
 * Merges one learned attack entry into another, field by field
 * (AIValMergeR): box extents, timings, hit results.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *
 * Calls: AIValMergeR
 * Called by: AIStateSetMerge, PlayerAILearnMoveEnd
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void AIMergeLearnData(int *arg1,int arg2,int arg3)

{
  int i1;
  int i2;
  float *pf3;
  int *pi4;
  float *pf5;
  int *pi6;
  int stk_68;
  float *stk_64;
  float *stk_60;
  float *stk_5c;
  int stk_58;
  int stk_54;
  float *stk_50;
  float *stk_4c;
  float *stk_48;
  int *stk_44;
  int *stk_40;
  float *stk_3c;
  float *stk_38;
  float *stk_34;
  int stk_30;
  int *stk_2c;
  int *stk_28;
  int stk_24;
  int stk_20;
  int stk_1c;
  
  stk_20 = 0;
  stk_24 = *(int *)(arg2 + 0x200);
  if (0 < stk_24) {
    i2 = 0;
    do {
      stk_1c = 0;
      i1 = arg1[0x80];
      if ((0 < i1) && (*arg1 != *(int *)(arg2 + i2))) {
        do {
          stk_1c = stk_1c + 1;
          if (i1 <= stk_1c) break;
        } while (arg1[stk_1c * 4] != *(int *)(i2 + arg2));
      }
      if ((stk_1c == i1) && (stk_1c < 0x20)) {
        arg1[stk_1c * 4] = *(int *)(arg2 + i2);
        arg1[stk_1c * 4 + 1] = *(int *)(arg2 + 4 + i2);
        arg1[stk_1c * 4 + 2] = *(int *)(arg2 + 8 + i2);
        arg1[stk_1c * 4 + 3] = *(int *)(arg2 + 0xc + i2);
        arg1[0x80] = arg1[0x80] + 1;
        stk_24 = *(int *)(arg2 + 0x200);
      }
      i2 = i2 + 0x10;
      stk_20 = stk_20 + 1;
    } while (stk_20 < stk_24);
  }
  arg1[0x83] = *(int *)(arg2 + 0x20c);
  arg1[0x84] = -1;
  AIValMergeR((float *)(arg1 + 0x8d),*(float *)(arg2 + 0x234),*(float *)(arg2 + 0x238),
              *(float *)(arg2 + 0x23c),*(int *)(arg2 + 0x240));
  AIValMergeR((float *)(arg1 + 0x91),*(float *)(arg2 + 0x244),*(float *)(arg2 + 0x248),
              *(float *)(arg2 + 0x24c),*(int *)(arg2 + 0x250));
  i2 = 0x280;
  AIValMergeR((float *)(arg1 + 0x95),*(float *)(arg2 + 0x254),*(float *)(arg2 + 600),
              *(float *)(arg2 + 0x25c),*(int *)(arg2 + 0x260));
  stk_1c = 0;
  stk_64 = (float *)(arg1 + 0xa1);
  pf3 = (float *)(arg1 + 0x9d);
  pf5 = (float *)(arg1 + 0x99);
  stk_68 = 0x260;
  do {
    if (((int)X87_FIST32(*(float *)(stk_68 + 4 + arg2)) != 0) &&
       ((arg3 == -1 || (arg3 == stk_1c)))) {
      if ((int)X87_FIST32(*(float *)(stk_68 + 4 + (int)arg1)) == 0) {
        *(uint32_t *)((int)arg1 + i2 + -0x1c) = *(uint32_t *)(arg2 + -0x1c + i2);
        *(uint32_t *)((int)arg1 + i2 + -0x18) = *(uint32_t *)(arg2 + -0x18 + i2);
        *(uint32_t *)((int)arg1 + i2 + -0x14) = *(uint32_t *)(arg2 + -0x14 + i2);
        *(uint32_t *)((int)arg1 + i2 + -0x10) = *(uint32_t *)(arg2 + -0x10 + i2);
        *(uint32_t *)((int)arg1 + i2 + -0xc) = *(uint32_t *)(arg2 + -0xc + i2);
        *(uint32_t *)((int)arg1 + i2 + -8) = *(uint32_t *)(arg2 + -8 + i2);
        *(uint32_t *)((int)arg1 + i2 + -4) = *(uint32_t *)(arg2 + -4 + i2);
        *(uint32_t *)((int)arg1 + i2) = *(uint32_t *)(arg2 + i2);
        *(uint32_t *)((int)arg1 + i2 + 4) = *(uint32_t *)(arg2 + 4 + i2);
        *(uint32_t *)((int)arg1 + i2 + 8) = *(uint32_t *)(arg2 + 8 + i2);
        *(uint32_t *)((int)arg1 + i2 + 0xc) = *(uint32_t *)(arg2 + 0xc + i2);
        *(uint32_t *)((int)arg1 + i2 + 0x10) = *(uint32_t *)(arg2 + 0x10 + i2);
      }
      else {
        AIValMergeR(pf5,*(float *)(arg2 + -0x1c + i2),*(float *)(arg2 + -0x18 + i2),
                    *(float *)(arg2 + -0x14 + i2),*(int *)(arg2 + -0x10 + i2));
        AIValMergeR(pf3,*(float *)(arg2 + -0xc + i2),*(float *)(arg2 + -8 + i2),
                    *(float *)(arg2 + -4 + i2),*(int *)(arg2 + i2));
        AIValMergeR(stk_64,*(float *)(arg2 + 4 + i2),*(float *)(arg2 + 8 + i2),
                    *(float *)(arg2 + 0xc + i2),*(int *)(arg2 + 0x10 + i2));
      }
    }
    stk_1c = stk_1c + 1;
    stk_64 = stk_64 + 0xc;
    stk_68 = stk_68 + 0x30;
    i2 = i2 + 0x30;
    pf3 = pf3 + 0xc;
    pf5 = pf5 + 0xc;
  } while (stk_1c < 3);
  stk_5c = (float *)(arg1 + 0xc9);
  stk_60 = (float *)(arg1 + 0xc1);
  i2 = 800;
  stk_58 = 0x2f0;
  pf3 = (float *)(arg1 + 0xc5);
  pf5 = (float *)(arg1 + 0xbd);
  stk_1c = 1;
  do {
    if (*(float *)(stk_58 + 4 + arg2) != -32760.0) {
      if (*(float *)(stk_58 + 4 + (int)arg1) == -32760.0) {
        *(uint32_t *)((int)arg1 + i2 + -0x2c) = *(uint32_t *)(arg2 + -0x2c + i2);
        *(uint32_t *)((int)arg1 + i2 + -0x28) = *(uint32_t *)(arg2 + -0x28 + i2);
        *(uint32_t *)((int)arg1 + i2 + -0x24) = *(uint32_t *)(arg2 + -0x24 + i2);
        *(uint32_t *)((int)arg1 + i2 + -0x20) = *(uint32_t *)(arg2 + -0x20 + i2);
        *(uint32_t *)((int)arg1 + i2 + -0xc) = *(uint32_t *)(arg2 + -0xc + i2);
        *(uint32_t *)((int)arg1 + i2 + -8) = *(uint32_t *)(arg2 + -8 + i2);
        *(uint32_t *)((int)arg1 + i2 + -4) = *(uint32_t *)(arg2 + -4 + i2);
        *(uint32_t *)((int)arg1 + i2) = *(uint32_t *)(arg2 + i2);
        *(uint32_t *)((int)arg1 + i2 + -0x1c) = *(uint32_t *)(arg2 + -0x1c + i2);
        *(uint32_t *)((int)arg1 + i2 + -0x18) = *(uint32_t *)(arg2 + -0x18 + i2);
        *(uint32_t *)((int)arg1 + i2 + -0x14) = *(uint32_t *)(arg2 + -0x14 + i2);
        *(uint32_t *)((int)arg1 + i2 + -0x10) = *(uint32_t *)(arg2 + -0x10 + i2);
        *(uint32_t *)((int)arg1 + i2 + 4) = *(uint32_t *)(arg2 + 4 + i2);
        *(uint32_t *)((int)arg1 + i2 + 8) = *(uint32_t *)(arg2 + 8 + i2);
        *(uint32_t *)((int)arg1 + i2 + 0xc) = *(uint32_t *)(arg2 + 0xc + i2);
        *(uint32_t *)((int)arg1 + i2 + 0x10) = *(uint32_t *)(arg2 + 0x10 + i2);
      }
      else {
        AIValMergeR(pf5,*(float *)(arg2 + -0x2c + i2),*(float *)(arg2 + -0x28 + i2),
                    *(float *)(arg2 + -0x24 + i2),*(int *)(arg2 + -0x20 + i2));
        AIValMergeR(pf3,*(float *)(arg2 + -0xc + i2),*(float *)(arg2 + -8 + i2),
                    *(float *)(arg2 + -4 + i2),*(int *)(arg2 + i2));
        AIValMergeR(stk_60,*(float *)(arg2 + -0x1c + i2),*(float *)(arg2 + -0x18 + i2)
                    ,*(float *)(arg2 + -0x14 + i2),*(int *)(arg2 + -0x10 + i2));
        AIValMergeR(stk_5c,*(float *)(arg2 + 4 + i2),*(float *)(arg2 + 8 + i2),
                    *(float *)(arg2 + 0xc + i2),*(int *)(arg2 + 0x10 + i2));
      }
    }
    stk_58 = stk_58 + 0x40;
    stk_5c = stk_5c + 0x10;
    stk_60 = stk_60 + 0x10;
    i2 = i2 + 0x40;
    pf3 = pf3 + 0x10;
    pf5 = pf5 + 0x10;
    stk_1c = stk_1c + -1;
  } while (-1 < stk_1c);
  if (arg1[0xdd] != *(int *)(arg2 + 0x374)) {
    arg1[0xdd] = -1;
  }
  if (arg1[0xde] != *(int *)(arg2 + 0x378)) {
    arg1[0xde] = -1;
  }
  if (((arg1[0xdf] != *(int *)(arg2 + 0x37c)) && (arg1[0xdf] != 0)) &&
     (*(int *)(arg2 + 0x37c) != 0)) {
    arg1[0xdf] = -1;
  }
  if (((arg1[0xe0] != *(int *)(arg2 + 0x380)) && (arg1[0xe0] != 0)) &&
     (*(int *)(arg2 + 0x380) != 0)) {
    arg1[0xe0] = -1;
  }
  i2 = 0;
  AIValMergeR((float *)(arg1 + 0xe1),*(float *)(arg2 + 900),*(float *)(arg2 + 0x388),
              *(float *)(arg2 + 0x38c),*(int *)(arg2 + 0x390));
  stk_28 = (int *)(arg2 + 0x420);
  stk_1c = 0;
  stk_2c = arg1 + 0x108;
  stk_34 = (float *)(arg1 + 0x111);
  stk_38 = (float *)(arg1 + 0x10d);
  stk_3c = (float *)(arg1 + 0x109);
  stk_40 = (int *)(arg2 + 0x390);
  stk_48 = (float *)(arg1 + 0xed);
  stk_44 = arg1 + 0xe4;
  stk_4c = (float *)(arg1 + 0xe9);
  stk_50 = (float *)(arg1 + 0xe5);
  stk_30 = 0x420;
  stk_54 = 0x390;
  do {
    if (((int)X87_FIST32(*(float *)(stk_54 + 4 + arg2)) != 0) &&
       ((arg3 == -1 || (arg3 == stk_1c)))) {
      if ((int)X87_FIST32(*(float *)(stk_54 + 4 + (int)arg1)) == 0) {
        i1 = 0xc;
        pi4 = stk_40;
        pi6 = stk_44;
        while( true ) {
          pi6 = pi6 + 1;
          pi4 = pi4 + 1;
          if (i1 == 0) break;
          i1 = i1 + -1;
          *pi6 = *pi4;
        }
      }
      else {
        AIValMergeR(stk_50,*(float *)(arg2 + 0x394 + i2),*(float *)(arg2 + 0x398 + i2)
                    ,*(float *)(arg2 + 0x39c + i2),*(int *)(arg2 + 0x3a0 + i2));
        AIValMergeR(stk_4c,*(float *)(arg2 + 0x3a4 + i2),*(float *)(arg2 + 0x3a8 + i2)
                    ,*(float *)(arg2 + 0x3ac + i2),*(int *)(arg2 + 0x3b0 + i2));
        AIValMergeR(stk_48,*(float *)(arg2 + 0x3b4 + i2),*(float *)(arg2 + 0x3b8 + i2)
                    ,*(float *)(arg2 + 0x3bc + i2),*(int *)(arg2 + 0x3c0 + i2));
      }
    }
    if (*(float *)(stk_30 + 4 + arg2) != 0.0) {
      if (*(float *)(stk_30 + 4 + (int)arg1) == 0.0) {
        i1 = 0xc;
        pi4 = stk_28;
        pi6 = stk_2c;
        while( true ) {
          pi6 = pi6 + 1;
          pi4 = pi4 + 1;
          if (i1 == 0) break;
          i1 = i1 + -1;
          *pi6 = *pi4;
        }
      }
      else {
        AIValMergeR(stk_3c,*(float *)(arg2 + 0x424 + i2),*(float *)(arg2 + 0x428 + i2)
                    ,*(float *)(arg2 + 0x42c + i2),*(int *)(arg2 + 0x430 + i2));
        AIValMergeR(stk_38,*(float *)(arg2 + 0x434 + i2),*(float *)(arg2 + 0x438 + i2)
                    ,*(float *)(arg2 + 0x43c + i2),*(int *)(arg2 + 0x440 + i2));
        AIValMergeR(stk_34,*(float *)(arg2 + 0x444 + i2),*(float *)(arg2 + 0x448 + i2)
                    ,*(float *)(arg2 + 0x44c + i2),*(int *)(arg2 + 0x450 + i2));
      }
    }
    stk_30 = stk_30 + 0x30;
    stk_28 = stk_28 + 0xc;
    stk_2c = stk_2c + 0xc;
    stk_44 = stk_44 + 0xc;
    stk_34 = stk_34 + 0xc;
    stk_38 = stk_38 + 0xc;
    stk_3c = stk_3c + 0xc;
    stk_40 = stk_40 + 0xc;
    stk_1c = stk_1c + 1;
    stk_48 = stk_48 + 0xc;
    stk_4c = stk_4c + 0xc;
    stk_50 = stk_50 + 0xc;
    stk_54 = stk_54 + 0x30;
    i2 = i2 + 0x30;
  } while (stk_1c < 3);
  return;
}

/* AIChangeState @ 0x080ab080, 30 bytes
 *
 * Switches the AI's mode, remembering the previous one and resetting the
 * mode timer.
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t
 *
 * Called by: AIForNormalAttack, AIForNormalDecisions, AIForNormalGuard,
 *            AIForNormalRandom
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
uint32_t AIChangeState(int arg1,uint32_t arg2)

{
  uint32_t u1;
  
  u1 = *(uint32_t *)(arg1 + 4);
  *(uint32_t *)(arg1 + 4) = arg2;
  *(uint32_t *)(arg1 + 8) = u1;
  *(uint32_t *)(arg1 + 0xc) = 0;
  return 1;
}

/* AIKBReleaseDir @ 0x080ab0a0, 57 bytes
 *
 * Releases all direction keys of the AI player.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: KBIStuffBufNoFlip
 * Called by: AIForNormalDecisions
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void AIKBReleaseDir(int arg1)

{
  int *pi1;
  uint32_t u2;
  
  u2 = 1;
  pi1 = (int *)(arg1 + 0x2c4);
  do {
    if (*pi1 != 0) {
      KBIStuffBufNoFlip(arg1 + 0x248,u2 | 0x10);
    }
    u2 = u2 + 1;
    pi1 = pi1 + 1;
  } while ((int)u2 < 5);
  return;
}

/* AIKBReleaseDirExcept @ 0x080ab0e0, 79 bytes
 *
 * Releases the direction keys except one.
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t
 *
 * Calls: KBIStuffBufNoFlip
 * Called by: AIForNormalIdle
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void AIKBReleaseDirExcept(int arg1,uint32_t arg2)

{
  uint32_t u1;
  int i2;
  
  i2 = 0x74;
  u1 = 1;
  do {
    if ((u1 != arg2) && (*(int *)(i2 + arg1 + 0x250) != 0)) {
      KBIStuffBufNoFlip(arg1 + 0x248,u1 | 0x10);
    }
    u1 = u1 + 1;
    i2 = i2 + 4;
  } while ((int)u1 < 5);
  return;
}

/* AIKBReleaseAll @ 0x080ab130, 57 bytes
 *
 * Releases every key of the AI player.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: KBIStuffBufNoFlip
 * Called by: PlayerAI
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void AIKBReleaseAll(int arg1)

{
  int *pi1;
  uint32_t u2;
  
  u2 = 1;
  pi1 = (int *)(arg1 + 0x2c4);
  do {
    if (*pi1 != 0) {
      KBIStuffBufNoFlip(arg1 + 0x248,u2 | 0x10);
    }
    u2 = u2 + 1;
    pi1 = pi1 + 1;
  } while ((int)u2 < 0xe);
  return;
}

/* AIKBReleaseAllExcept @ 0x080ab170, 79 bytes
 *
 * Releases every key except one.
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t
 *
 * Calls: KBIStuffBufNoFlip
 * Called by: AIForNormalIdle
 *
 * Elecbyte file: src/mugen/p-ai.c
 */
void AIKBReleaseAllExcept(int arg1,uint32_t arg2)

{
  uint32_t u1;
  int i2;
  
  i2 = 0x74;
  u1 = 1;
  do {
    if ((u1 != arg2) && (*(int *)(i2 + arg1 + 0x250) != 0)) {
      KBIStuffBufNoFlip(arg1 + 0x248,u1 | 0x10);
    }
    u1 = u1 + 1;
    i2 = i2 + 4;
  } while ((int)u1 < 0xe);
  return;
}

