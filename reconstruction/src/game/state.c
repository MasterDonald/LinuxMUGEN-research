/*
 * state.c -- state machine
 * Loading state files (statedefs and their controllers) and running a
 * player's current state and the special states each tick.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/state.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* SctrlReadFileTP @ 0x080d19b0, 370 bytes
 *
 * Reads every "[Statedef n]" group of a parsed state file into a new state
 * table (SCtrlParseState for each). At least one statedef is required ("Need
 * at least one statedef"). Errors are prefixed with "Error in <file>".
 * Returns the table or NULL.
 *
 * Parameters:
 *   tp           int
 *   player       int
 *
 * Globals read: errmsg
 * Calls: TPGroupMatchCount, ecalloc, ArrayNew, TPGroupScanFirst,
 *        strimatch, TPGroupScanNext, SCtrlParseState, ArrayAdd
 * C library: sprintf, __strtol_internal, strcat
 * Called by: PlayerSTLoadTP
 * Messages:
 *   "statedef "
 *   "Need at least one statedef"
 *   "\nError in "
 *
 * Elecbyte file: src/mugen/state.c
 * Note: Locals live in `frame`, laid out as on the original stack (0xd0 bytes, 1
 *       variables), because their address is taken.
 */
int * SctrlReadFileTP(int tp,int player)

{
  size_t count;
  int *mem;
  uint32_t *array;
  int *expr;
  int i4;
  uint32_t u5;
  int i6;
  unsigned char frame[0xd0] __attribute__((aligned(16)));
#define elems (*(int (*)[47])(frame + 0x4))
  
  count = TPGroupMatchCount(tp,"statedef ");
  if (count == 0) {
    sprintf((char *)(g + G_ERRMSG),"Need at least one statedef");
  }
  else {
    mem = (int *)ecalloc(1,4);
    if (mem != (int *)0x0) {
      array = ArrayNew(count,0xa4,0);
      *mem = (int)array;
      if (array != (uint32_t *)0x0) {
        i6 = 0;
        expr = (int *)TPGroupScanFirst(tp);
        if ((int)count < 1) {
          return mem;
        }
        while( true ) {
          while (i4 = strimatch((char *)((int)expr + 1),"statedef "), i4 == 0) {
            expr = (int *)TPGroupScanNext(tp);
          }
          u5 = __strtol_internal((uint8_t *)((int)expr + 10),(uint32_t *)0x0,10,0);
          i4 = SCtrlParseState(tp,elems,expr,player);
          if (i4 == 0) break;
          i6 = i6 + 1;
          ArrayAdd(*mem,elems,u5,0);
          expr = (int *)TPGroupScanNext(tp);
          if ((int)count <= i6) {
            return mem;
          }
        }
        strcat((char *)(g + G_ERRMSG),"\nError in ");
        strcat((char *)(g + G_ERRMSG),(char *)expr);
      }
    }
  }
  return (int *)0x0;
}
#undef elems

/* SctrlAddFileTP @ 0x080d1b30, 339 bytes
 *
 * Adds the statedefs of another state file to an existing state table (later
 * files override earlier states with the same number). Used for the extra
 * .st files and common1.cns.
 *
 * Parameters:
 *   arg1         int *
 *   tp           int
 *   player       int
 *
 * Globals read: errmsg
 * Calls: TPGroupMatchCount, ArrayResize, TPGroupScanFirst, strimatch,
 *        TPGroupScanNext, SCtrlParseState, ArrayAdd
 * C library: __strtol_internal, strcat
 * Called by: PlayerDefLoadZip, PlayerSTLoadAppend
 * Messages:
 *   "statedef "
 *   "\nError in "
 *
 * Elecbyte file: src/mugen/state.c
 * Note: Locals live in `frame`, laid out as on the original stack (0xd0 bytes, 1
 *       variables), because their address is taken.
 */
uint32_t SctrlAddFileTP(int *arg1,int tp,int player)

{
  int count;
  int i2;
  uint32_t u3;
  int *expr;
  int i4;
  uint32_t u5;
  unsigned char frame[0xd0] __attribute__((aligned(16)));
#define elems (*(int (*)[47])(frame + 0x4))
  
  count = TPGroupMatchCount(tp,"statedef ");
  if ((count == 0) || (i2 = ArrayResize(*arg1,count + *(int *)(*arg1 + 8)), i2 == 0)) {
L_080d1bb1:
    u3 = 0;
  }
  else {
    i2 = 0;
    expr = (int *)TPGroupScanFirst(tp);
    if (0 < count) {
      do {
        while (i4 = strimatch((char *)((int)expr + 1),"statedef "), i4 == 0) {
          expr = (int *)TPGroupScanNext(tp);
        }
        u5 = __strtol_internal((uint8_t *)((int)expr + 10),(uint32_t *)0x0,10,0);
        i4 = SCtrlParseState(tp,elems,expr,player);
        if (i4 == 0) {
          strcat((char *)(g + G_ERRMSG),"\nError in ");
          strcat((char *)(g + G_ERRMSG),(char *)expr);
          goto L_080d1bb1;
        }
        i2 = i2 + 1;
        ArrayAdd(*arg1,elems,u5,0);
        expr = (int *)TPGroupScanNext(tp);
      } while (i2 < count);
    }
    u3 = 1;
  }
  return u3;
}
#undef elems

/* SCtrlParseState @ 0x080d1c90, 1998 bytes
 *
 * Parses one "[Statedef n]" group and the "[State n, ...]" controller groups
 * that follow it. The statedef keys are "type", "movetype", "physics",
 * "anim", "velset", "ctrl", "poweradd", "juggle", "facep2", "hitdefpersist",
 * "hitcountpersist", "movehitpersist" and "sprpriority"; invalid values give
 * "State type ...", "State movetype ...", "State physics ..." errors.
 * Returns nonzero on success.
 *
 * Parameters:
 *   tp           int
 *   elems        int *
 *   expr         int *
 *   player       int
 *
 * Text keys read: "type", "movetype", "juggle", "facep2", "hitdefpersist",
 *                 "hitcountpersist", "movehitpersist", "sprpriority",
 *                 "physics", "velset", "ctrl", "anim", "poweradd"
 * Globals read: errmsg
 * Calls: TPGroupSeek, TPGroupScanNext, strimatch, ArrayNew, TPGetValue,
 *        ConstExpI, InfixToPostfix, ItoP_TPConstI, ConstExpF,
 *        SCtrlReadExpList, SCtrlParseElem
 * C library: __strtol_internal, strcpy, sprintf, memset, strcat
 * Called by: SctrlAddFileTP, SctrlReadFileTP
 * Messages:
 *   "Can\'t access %s"
 *   "state "
 *   "Need at least one state controller"
 *   "State type \"%s\" not valid"
 *   "State movetype \"%s\" not valid"
 *   "State physics \"%s\" not valid"
 *
 * Elecbyte file: src/mugen/state.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0xb0 bytes, 5
 *       variables), because their address is taken.
 */
uint32_t SCtrlParseState(int tp,int *elems,int *expr,int player)

{
  uint32_t u1;
  bool b2;
  uint32_t u3;
  int i2;
  int i5;
  uint32_t *array;
  char *value;
  uint8_t *value2;
  uint32_t stale_var;
  uint32_t *pu9;
  uint32_t *pu10;
  char c11;
  uint32_t u12;
  uint32_t u13;
  uint32_t u14;
  unsigned char frame[0xb0] __attribute__((aligned(16)));
#define stk_a4 (*(size_t *)(frame + 0xc))
#define stk_a0 (*(char **)(frame + 0x10))
#define stk_9c (*(char (*)[60])(frame + 0x14))
#define buf_60 (*(char (*)[4])(frame + 0x50))
#define group (*(uint32_t (*)[19])(frame + 0x54))
  
  u1 = *(uint32_t *)(tp + 0x18);
  u3 = __strtol_internal((uint8_t *)((int)expr + 10),(uint32_t *)0x0,10,0);
  strcpy((char *)group,(char *)((int)expr + 1));
  pu10 = group;
  do {
    pu9 = pu10;
    pu10 = pu9 + 1;
    u12 = *pu9 + 0xfefefeff & (*pu9 ^ 0xffffffff);
    u13 = u12 & 0x80808080;
  } while (u13 == 0);
  if ((u12 & 0x8080) == 0) {
    u13 = u13 >> 0x10;
    pu10 = (uint32_t *)((int)pu9 + 6);
  }
  u14 = u13 & 0xffffff00;
  *(char *)((int)pu10 +
           (int)(buf_60 + (-(int)group - (uint32_t)CARRY1((uint8_t)u13,(uint8_t)u13)))) = '\0';
  u12 = u14;
  i2 = TPGroupSeek(tp,(char *)group);
  if (i2 == -1) {
    sprintf((char *)(g + G_ERRMSG),"Can\'t access %s",expr,u3);
    return 0;
  }
  stk_a4 = 0;
  i2 = TPGroupScanNext(tp);
  sprintf(stk_9c,"state ",u14,u12);
  while ((i2 != 0 && (i5 = strimatch((char *)(i2 + 1),stk_9c), i5 != 0))) {
    stk_a4 = stk_a4 + 1;
    i2 = TPGroupScanNext(tp);
  }
  TPGroupSeek(tp,(char *)group);
  if ((int)stk_a4 < 1) {
    sprintf((char *)(g + G_ERRMSG),"Need at least one state controller",expr,expr);
    return 0;
  }
  memset(elems,0,0xa4);
  array = ArrayNew(stk_a4,100,0);
  *elems = (int)array;
  if (array == (uint32_t *)0x0) {
    return 0;
  }
  if (-1 < (int)u3) {
    elems[1] = 1;
    value = TPGetValue(tp,"type");
    if (value != (char *)0x0) {
      switch(*(uint32_t *)(__ctype_tolower + *value * 4)) {
      case 0x61:
        elems[1] = 3;
        break;
      default:
        sprintf((char *)(g + G_ERRMSG),"State type \"%s\" not valid",value,elems);
        return 0;
      case 99:
        elems[1] = 2;
        break;
      case 0x6c:
        elems[1] = 4;
        break;
      case 0x73:
        elems[1] = 1;
        break;
      case 0x75:
        elems[1] = -1;
      }
    }
    elems[2] = 0;
    value = TPGetValue(tp,"movetype");
    if (value != (char *)0x0) {
      i5 = *(int *)(__ctype_tolower + *value * 4);
      if (i5 == 0x68) {
        elems[2] = 2;
      }
      else if (i5 < 0x69) {
        if (i5 != 0x61) {
L_080d1f60:
          sprintf((char *)(g + G_ERRMSG),"State movetype \"%s\" not valid",value,i2);
          return 0;
        }
        elems[2] = 1;
      }
      else if (i5 == 0x69) {
        elems[2] = 0;
      }
      else {
        if (i5 != 0x75) goto L_080d1f60;
        elems[2] = -1;
      }
    }
    ConstExpI(elems + 4,-1);
    value2 = (uint8_t *)TPGetValue(tp,"juggle");
    i2 = InfixToPostfix(value2,elems + 4,player,(uint32_t *)0x0,1);
    if (i2 != 0) {
      ConstExpI(elems + 7,0);
      value2 = (uint8_t *)TPGetValue(tp,"facep2");
      i2 = InfixToPostfix(value2,elems + 7,player,(uint32_t *)0x0,1);
      if ((((i2 != 0) &&
           (i2 = ItoP_TPConstI(tp,"hitdefpersist",elems + 10,player,0), i2 != 0)) &&
          (i2 = ItoP_TPConstI(tp,"hitcountpersist",elems + 0xd,player,0), i2 != 0)) &&
         (i2 = ItoP_TPConstI(tp,"movehitpersist",elems + 0x10,player,0), i2 != 0)) {
        value2 = (uint8_t *)TPGetValue(tp,"sprpriority");
        if (value2 != (uint8_t *)0x0) {
          i2 = InfixToPostfix(value2,elems + 0x14,player,(uint32_t *)0x0,1);
          if (i2 == 0) {
            return 0;
          }
          elems[0x13] = 1;
        }
        elems[3] = 0;
        value = TPGetValue(tp,"physics");
        if (value != (char *)0x0) {
          switch(*(uint32_t *)(__ctype_tolower + *value * 4)) {
          case 0x61:
            elems[3] = 3;
            break;
          default:
            sprintf((char *)(g + G_ERRMSG),"State physics \"%s\" not valid",value,player);
            return 0;
          case 99:
            elems[3] = 2;
            break;
          case 0x6e:
            elems[3] = 0;
            break;
          case 0x73:
            elems[3] = 1;
            break;
          case 0x75:
            elems[3] = -1;
          }
        }
        expr = elems + 0x1a;
        ConstExpF(elems + 0x17,-0x39001000);
        ConstExpF(expr,-0x39001000);
        ConstExpF(elems + 0x1d,-0x39001000);
        ConstExpI(elems + 0x20,-1);
        ConstExpI(elems + 0x23,-1);
        ConstExpI(elems + 0x26,0);
        value2 = (uint8_t *)TPGetValue(tp,"velset");
        if ((value2 == (uint8_t *)0x0) ||
           ((value2 = SCtrlReadExpList(value2,"fff",player,&stk_a0,elems + 0x17,expr,
                                       elems + 0x1d), value2 != (uint8_t *)0x0 && (*stk_a0 == '\0')
            ))) {
          value2 = (uint8_t *)TPGetValue(tp,"ctrl");
          i2 = InfixToPostfix(value2,elems + 0x20,player,(uint32_t *)0x0,1);
          if (i2 != 0) {
            value2 = (uint8_t *)TPGetValue(tp,"anim");
            i2 = InfixToPostfix(value2,elems + 0x23,player,(uint32_t *)0x0,1);
            if (i2 != 0) {
              value2 = (uint8_t *)TPGetValue(tp,"poweradd");
              i2 = InfixToPostfix(value2,elems + 0x26,player,(uint32_t *)0x0,1);
              if (i2 != 0) goto L_080d2369;
            }
          }
        }
      }
    }
    return 0;
  }
L_080d2369:
  i2 = 0;
  sprintf(stk_9c,"state ",expr,expr);
  if (0 < (int)stk_a4) {
    do {
      value = (char *)TPGroupScanNext(tp);
      if (value == (char *)0x0) {
        sprintf((char *)(g + G_ERRMSG),"Can\'t access [%s] controller %i",stk_9c,i2 + 1);
        return 0;
      }
      i5 = strimatch(value + 1,stk_9c);
      if (i5 == 0) {
        sprintf((char *)(g + G_ERRMSG),"Can\'t access [%s] controller %i",stk_9c,i2 + 1);
        return 0;
      }
      i5 = 7;
      c11 = ',';
      if (value[7] != ',') {
        if (value[7] == '\0') {
          c11 = '\0';
        }
        else {
          do {
            i5 = i5 + 1;
            c11 = value[i5];
            if (c11 == ',') break;
          } while (c11 != '\0');
        }
      }
      if (c11 == '\0') {
        u3 = 0xffffffff;
      }
      else {
        u3 = __strtol_internal((uint8_t *)(value + i5 + 1),(uint32_t *)0x0,10,0);
      }
      b2 = SCtrlParseElem(tp,elems,u3,player);
      if (ZEXT8(b2) == 0) {
        strcat((char *)(g + G_ERRMSG),"\nError parsing ");
        strcat((char *)(g + G_ERRMSG),value);
        return 0;
      }
      i2 = i2 + 1;
    } while (i2 < (int)stk_a4);
  }
  *(uint32_t *)(tp + 0x18) = u1;
  return 1;
}
#undef stk_a4
#undef stk_a0
#undef stk_9c
#undef buf_60
#undef group

/* SCtrlInit @ 0x080d2460, 32 bytes
 *
 * Initialises a player's state data pointers (own state table, no custom
 * state).
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         uint32_t
 *
 * Called by: PlayerNew
 *
 * Elecbyte file: src/mugen/state.c
 */
uint32_t SCtrlInit(uint32_t *arg1,uint32_t arg2)

{
  int i1;
  uint32_t *pu2;
  
  pu2 = arg1;
  for (i1 = 0x104; i1 != 0; i1 = i1 + -1) {
    *pu2 = 0;
    pu2 = pu2 + 1;
  }
  *arg1 = arg2;
  return 1;
}

/* SCtrlRCFree @ 0x080d2480, 257 bytes
 *
 * Frees a state table: every state's controllers (SCtrlRCElemFree) and
 * statedef expressions, then the table.
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * Calls: ArrayScanFirst, SCtrlRCElemFree, ArrayScanNext, FreeExpression,
 *        ArrayFree
 * C library: free
 * Called by: PlayerRCFree
 *
 * Elecbyte file: src/mugen/state.c
 */
void SCtrlRCFree(uint32_t *arg1)

{
  void *array;
  int *item;
  uint32_t *item2;
  
  array = (void *)*arg1;
  item = (int *)ArrayScanFirst((int)array);
  while (item != (int *)0x0) {
    item2 = (uint32_t *)ArrayScanFirst(*item);
    while (item2 != (uint32_t *)0x0) {
      SCtrlRCElemFree(item2);
      item2 = (uint32_t *)ArrayScanNext(*item);
    }
    FreeExpression(item + 4);
    FreeExpression(item + 7);
    FreeExpression(item + 10);
    FreeExpression(item + 0xd);
    FreeExpression(item + 0x10);
    FreeExpression(item + 0x14);
    FreeExpression(item + 0x17);
    FreeExpression(item + 0x1a);
    FreeExpression(item + 0x1d);
    FreeExpression(item + 0x20);
    FreeExpression(item + 0x23);
    FreeExpression(item + 0x26);
    ArrayFree((void *)*item);
    item = (int *)ArrayScanNext((int)array);
  }
  ArrayFree(array);
  free(arg1);
  return;
}

/* PlayerSCtrlUpdate @ 0x080d2590, 1225 bytes
 *
 * Runs the player's current state for one tick. On entering a state, it
 * applies the statedef settings (type, movetype, physics, anim, velset,
 * ctrl, poweradd, juggle, facep2, sprpriority). Then it tests each
 * controller's triggers in order (skipping those that do not ignore hit
 * pause during a hit pause) and executes those that pass. It stops early
 * when a controller changes state. Errors: "state %i can only have max of %i
 * controllers", "Illegal juggle points", "illegal anim number".
 *
 * Parameters:
 *   player       int *
 *
 * Player fields read: stateno, hitpausetime, statetime, facing
 * Player fields written: uniqhitcount, hitcount, movecontact,
 *                        movereversed, hitdef, sprpriority, statetype,
 *                        movetype, vel_x, vel_y, vel_z, ctrl
 * Globals read: errmsg
 * Calls: PlayerGetRedirInfo, ArrayAccessGrpItem, EvalExpressionI,
 *        ErrorExit, PlayerDistX, PlayerTurnAround, Warn, EvalExpressionF,
 *        PlayerSelfAnim, PlayerPowerSet, ArrayScanFirst, AIClearCommands,
 *        SCtrlTrigArrayTest, PlayerDoSCtrlApplyElem, ArrayScanNext
 * C library: sprintf
 * Called by: PlayerUpdate
 * Messages:
 *   "state %i can only have max of %i controllers"
 *   "Illegal juggle points"
 *   "illegal anim number"
 *   "ctrl in statedef should be 1 or 0"
 *
 * Elecbyte file: src/mugen/state.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to NAN
 * Note: 4 data addresses refer to the data image (data/mugen_data.S).
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x40 bytes, 2
 *       variables), because their address is taken.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t PlayerSCtrlUpdate(int *player)

{
  char c1;
  int *item;
  int value;
  int *item2;
  int array;
  float80 value2;
  unsigned char frame[0x40] __attribute__((aligned(16)));
#define stk_3c (*(int *)(frame + 0x4))
#define player2 (*(int *)(frame + 0x8))
  
  PlayerGetRedirInfo((int)player,&stk_3c);
  if ((int *)player[0x2fb] == (int *)0x0) {
    value = player[PL_STATENO];
    array = *(int *)player[0x2fa];
  }
  else {
    value = player[PL_STATENO];
    array = *(int *)player[0x2fb];
  }
  item = (int *)ArrayAccessGrpItem(array,value,0);
  if (player[PL_HITPAUSETIME] < 1) {
    if (item == (int *)0x0) {
      player[0x38f] = 0;
      if (player[PL_STATETIME] != 0) {
        return 0;
      }
      player[PL_UNIQHITCOUNT] = 0;
      player[PL_HITCOUNT] = 0;
      player[PL_MOVECONTACT] = 0;
      player[PL_MOVEREVERSED] = 0;
      player[0x459] = 0;
      return 0;
    }
    value = player[PL_STATETIME];
    player[0x38f] = 1;
    if (value == 0) {
      value = EvalExpressionI((int)player,item + 0xd,1);
      if (value == 0) {
        player[PL_HITCOUNT] = 0;
        player[PL_UNIQHITCOUNT] = 0;
      }
      value = EvalExpressionI((int)player,item + 0x10,1);
      if (value == 0) {
        player[PL_MOVECONTACT] = 0;
        player[PL_MOVEREVERSED] = 0;
      }
      value = EvalExpressionI((int)player,item + 10,1);
      if (value == 0) {
        player[0x459] = 0;
        player[PL_HITDEF] = 0;
      }
      if (item[0x13] != 0) {
        value = EvalExpressionI((int)player,item + 0x14,1);
        player[PL_SPRPRIORITY] = value;
      }
      value = player[PL_STATETIME];
    }
    if (value == 0) {
      value = *item;
      array = 0;
      if (0 < *(int *)(value + 8)) {
        do {
          *(uint8_t *)((int)player + array + 0xbfc) = 0;
          value = *item;
          array = array + 1;
        } while (array < *(int *)(value + 8));
      }
      if (0x200 < *(int *)(value + 8)) {
        sprintf((char *)(g + G_ERRMSG),"state %i can only have max of %i controllers",player[PL_STATENO],
                0x200);
        ErrorExit();
      }
      if (item[1] != -1) {
        player[PL_STATETYPE] = item[1];
      }
      if (item[2] != -1) {
        player[PL_MOVETYPE] = item[2];
      }
      if (item[3] != -1) {
        player[0x382] = item[3];
      }
      if (((stk_3c != 0) && (value = EvalExpressionI((int)player,item + 7,1), value != 0)) &&
         (value = PlayerDistX((int)player,stk_3c), value < 0)) {
        PlayerTurnAround((int)player);
      }
      value = EvalExpressionI((int)player,item + 4,1);
      if (value < -1) {
        value = -1;
        Warn((int)player,(int)&str_illegal_juggle_points_cf33);
      }
      if (value != -1) {
        player[0x463] = value;
      }
      player[0x4b3] = player[0x1a];
      value2 = EvalExpressionF(player,item + 0x17);
      if (value2 != -32760.0) {
        player[PL_VEL_X] = BITS_F2I(int, ((float80)player[PL_FACING] * value2));
      }
      value2 = EvalExpressionF(player,item + 0x1a);
      if (value2 != -32760.0) {
        player[PL_VEL_Y] = BITS_F2I(int, value2);
      }
      value2 = EvalExpressionF(player,item + 0x1d);
      if (value2 != -32760.0) {
        player[PL_VEL_Z] = BITS_F2I(int, value2);
      }
      value = EvalExpressionI((int)player,item + 0x23,1);
      if (value < -1) {
        value = -1;
        Warn((int)player,(int)&str_illegal_anim_number_cf49);
      }
      if (value != -1) {
        PlayerSelfAnim(player,value);
      }
      value = EvalExpressionI((int)player,item + 0x20,1);
      if (value < -1) {
        value = -1;
        Warn((int)player,(int)&str_ctrl_in_statedef_should_be_1_d000);
      }
      if (1 < value) {
        value = 1;
        Warn((int)player,(int)&str_ctrl_in_statedef_should_be_1_d000);
      }
      if (value != -1) {
        player[PL_CTRL] = value;
      }
      value = EvalExpressionI((int)player,item + 0x26,1);
      PlayerPowerSet(player2,value + **(int **)(player2 + 0x170));
    }
  }
  if ((item != (int *)0x0) && (item2 = (int *)ArrayScanFirst(*item), item2 != (int *)0x0)) {
    value = 0x10;
    do {
      if ((*(char *)((int)player + value + 0xbec) == '\0') &&
         ((player[PL_HITPAUSETIME] == 0 || (item2[3] != 0)))) {
        AIClearCommands(player + 0xcef);
        array = SCtrlTrigArrayTest(player,*item2,item2[1]);
        if (array != 0) {
          if (item2[2] < 1) {
            *(uint8_t *)((int)player + value + 0xbec) = 1;
          }
          else {
            *(char *)((int)player + value + 0xbec) = (char)item2[2];
          }
          array = PlayerDoSCtrlApplyElem(player,(int)item2,&stk_3c);
          if (array != 0) {
            return 1;
          }
        }
      }
      if ((0 < item2[2]) &&
         (((player[PL_HITPAUSETIME] == 0 || (item2[3] != 0)) &&
          (c1 = *(char *)((int)player + value + 0xbec) + -1,
          *(char *)((int)player + value + 0xbec) = c1, c1 < '\0')))) {
        *(uint8_t *)((int)player + value + 0xbec) = 0;
      }
      value = value + 1;
      item2 = (int *)ArrayScanNext(*item);
    } while (item2 != (int *)0x0);
  }
  return 0;
}
#undef stk_3c
#undef player2

/* PlayerSCtrlUpdateSpec @ 0x080d2a60, 243 bytes
 *
 * Runs one of the special always-active states (Statedef -1, -2, -3) for a
 * player: tests and executes its controllers. Flag bits select whether the
 * player's own states or the states of the player whose states it is
 * currently using (custom state) are run.
 *
 * Parameters:
 *   player       int *
 *   arg2         int
 *   arg3         uint32_t
 *
 * Player fields read: hitpausetime
 * Calls: PlayerGetRedirInfo, ArrayAccessGrpItem, ArrayScanFirst,
 *        AIClearCommands, SCtrlTrigArrayTest, PlayerDoSCtrlApplyElem,
 *        ArrayScanNext
 * Called by: PlayerUpdate
 *
 * Elecbyte file: src/mugen/state.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x40 bytes, 1
 *       variables), because their address is taken.
 */
void PlayerSCtrlUpdateSpec(int *player,int arg2,uint32_t arg3)

{
  int *item;
  int *item2;
  int i3;
  unsigned char frame[0x40] __attribute__((aligned(16)));
#define buf_3c (*(int (*)[11])(frame + 0x4))
  
  PlayerGetRedirInfo((int)player,buf_3c);
  item = (int *)player[0x2fb];
  if ((item == (int *)0x0) || ((arg3 & 1) != 0)) {
    item = (int *)player[0x2fa];
  }
  if ((((item != (int *)0x0) && (((arg3 & 2) != 0 || (player[0x2fb] != 0)))) &&
      (((arg3 & 4) != 0 || (player[0x2fb] == 0)))) &&
     (item = (int *)ArrayAccessGrpItem(*item,arg2,0), item != (int *)0x0)) {
    item2 = (int *)ArrayScanFirst(*item);
    while (item2 != (int *)0x0) {
      if ((player[PL_HITPAUSETIME] == 0) || (item2[3] != 0)) {
        AIClearCommands(player + 0xcef);
        i3 = SCtrlTrigArrayTest(player,*item2,item2[1]);
        if ((i3 != 0) &&
           (i3 = PlayerDoSCtrlApplyElem(player,(int)item2,buf_3c), i3 != 0)) {
          return;
        }
      }
      item2 = (int *)ArrayScanNext(*item);
    }
  }
  return;
}
#undef buf_3c

