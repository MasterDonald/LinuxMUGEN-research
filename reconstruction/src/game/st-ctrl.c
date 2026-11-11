/*
 * st-ctrl.c -- state controllers
 * Parsing the parameters of every state controller type and executing
 * controllers on players.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/st-ctrl.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* SCtrlParseElemType @ 0x080ba390, 19059 bytes
 *
 * Parses the type-specific parameters of one state controller ("[State n,
 * ...]" group). It reads "type" and then, for each controller type, its
 * parameters: integer and float expressions are compiled to postfix
 * (InfixToPostfix) and constant ones folded.
 *
 * Type names (case-insensitive): changestate, selfstate, targetstate,
 * changeanim, changeanim2, velset, veladd, velmul, posset, posadd, ctrlset,
 * statetypeset, playsnd, stopsnd, sndpan, hitdef, reversaldef, projectile,
 * explod, modifyexplod, removeexplod, explodbindtime, helper, destroyself,
 * varset, varadd, varrandom, varrangeset, parentvarset, parentvaradd,
 * assertspecial, palfx, allpalfx, bgpalfx, afterimage, afterimagetime,
 * envshake, fallenvshake, envcolor, superpause, pause, width, turn,
 * hitoverride, hitby, nothitby, targetbind, targetdrop, targetfacing,
 * targetlifeadd, targetpoweradd, targetveladd, targetvelset, targetstate,
 * bindtoparent, bindtoroot, bindtotarget, lifeadd, lifeset, poweradd,
 * powerset, attackmulset, defencemulset, attackdist, gravity, posfreeze,
 * screenbound, playerpush, sprpriority, movehitreset, hitadd, hitvelset,
 * hitfallset, hitfallvel, hitfalldamage, angledraw, angleset, angleadd,
 * anglemul, trans, offset, displaytoclipboard, appendtoclipboard,
 * clearclipboard, gamemakeanim, makedust, forcefeedback, tagin, tagout,
 * null. Unknown types give "Not a valid elem type: %s".
 *
 * Errors are reported with the parameter name ("Missing channel parameter",
 * "VarRangeSet value not specified.", ...).
 *
 * Parameters:
 *   tp           int
 *   elem2        int  (elem)
 *   player       int
 *
 * Text keys read: "type", "value", "ctrl", "anim", "stateno",
 *                 "partnerstateno", "elem", "channel", "abspan", "pan",
 *                 "kill", "absolute", "x", "y", "z", "reversal.attr",
 *                 "value2", "time", "velocity", "statetype", "movetype",
 *                 "physics", "slot", "flag", ...
 * Globals read: errmsg
 * Calls: TPGetValue, InfixToPostfix, ConstExpI, ecalloc,
 *        SCtrlParsePlaySndInfo, SCtrlParseHitDef, ParseHitAttr, ConstExpF,
 *        SCtrlReadExpList, SCtrlParseHitOverride, ParseSpecialFlag,
 *        SCtrlParseProjectile, expcpytrig, ItoP_TPConstF, ItoP_TPConstI,
 *        ErrorExit, SCtrlParseEnvShake, SCtrlParseAftImgParams,
 *        SCtrlParsePause, SCtrlParseSuperPause, SCtrlParsePalFX,
 *        SCtrlParseExplod, SCtrlParseHelper, TPAccessFirstLine, ...
 * C library: strcpy, _alemu_strlwr, flag, free, strcat, _alemu_stricmp,
 *            sprintf
 * Called by: SCtrlParseElem
 * Messages:
 *   "\nError parsing PlaySnd"
 *   "Missing channel parameter"
 *   "\nError parsing Hitdef"
 *   "Missing reversal.attr parameter"
 *   "\nError parsing Reversaldef"
 *   "Invalid reversal.attr: %s"
 *
 * Elecbyte file: src/mugen/st-ctrl.c
 * Note: decompiler flag: type propagation did not settle
 * Note: call to 0x08102020 (Ghidra label gcc2_compiled.) renamed to its symbol
 *       _alemu_strlwr
 * Note: 33 data addresses refer to the data image (data/mugen_data.S).
 * Note: 9 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: 2 dead flag initialisations of inlined repz cmpsb loops set to constants
 * Note: shared sprintf() call: 19 formats, arguments recovered for 12, others
 *       passed as 0
 * Note: Locals live in `frame`, laid out as on the original stack (0x130 bytes,
 *       4 variables), because their address is taken.
 */
uint32_t SCtrlParseElemType(int tp,int elem2,int player)

{
  void *fmt_args[1] = {0};
  uint8_t b1;
  char c2;
  char c3;
  char *value;
  uint8_t *value2;
  uint32_t stale_var;
  uint32_t u6;
  uint32_t stale_var_00;
  uint32_t stale_var_01;
  uint8_t *value3;
  uint32_t stale_var_02;
  uint32_t stale_var_03;
  uint32_t stale_var_04;
  uint32_t stale_var_05;
  uint32_t stale_var_06;
  uint32_t stale_var_07;
  int mem;
  int i9;
  int i10;
  size_t s11;
  int *mem2;
  char *pc13;
  bool b14;
  bool b15;
  bool b16;
  uint8_t u17;
  unsigned char frame[0x130] __attribute__((aligned(16)));
#define stk_128 (*(int *)(frame + 0x8))
#define stk_124 (*(int *)(frame + 0xc))
#define value4 (*(uint8_t **)(frame + 0x10))
#define stk_11c (*(uint8_t (*)[268])(frame + 0x14))
  
  value = TPGetValue(tp,"type");
  if (value == (char *)0x0) {
    return 0;
  }
  pc13 = ";changestate";
  strcpy((char *)stk_11c,value);
  _alemu_strlwr((char *)stk_11c);
  mem = 0xc;
  b14 = 0;  /* dead flag (repz cmpsb, count 0xc) */
  b16 = 0;  /* dead flag (repz cmpsb, count 0xc) */
  value2 = stk_11c;
  do {
    pc13 = pc13 + 1;
    if (mem == 0) break;
    mem = mem + -1;
    b14 = *value2 < (uint8_t)*pc13;
    b16 = *value2 == *pc13;
    value2 = value2 + 1;
  } while (b16);
  b15 = (!b14 && !b16) < b14;
  b14 = (!b14 && !b16) == b14;
  if (b14) {
    *(uint32_t *)(elem2 + ELEM_TYPE) = 1;
    value2 = (uint8_t *)TPGetValue(tp,"value");
    if (value2 == (uint8_t *)0x0) {
      return 0;
    }
    mem = InfixToPostfix(value2,(int *)(elem2 + 0x18),player,(uint32_t *)0x0,1);
    if (mem == 0) {
      return 0;
    }
    ConstExpI((int *)(elem2 + 0x24),-1);
    mem2 = (int *)(elem2 + 0x30);
    ConstExpI(mem2,-1);
    value2 = (uint8_t *)TPGetValue(tp,"ctrl");
    mem = InfixToPostfix(value2,(int *)(elem2 + 0x24),player,(uint32_t *)0x0,1);
    if (mem == 0) {
      return 0;
    }
    value2 = (uint8_t *)TPGetValue(tp,"anim");
    mem = 1;
  }
  else {
    mem = 6;
    value2 = stk_11c;
    value3 = (uint8_t *)"tagin";
    do {
      if (mem == 0) break;
      mem = mem + -1;
      b15 = *value2 < *value3;
      b14 = *value2 == *value3;
      value2 = value2 + 1;
      value3 = value3 + 1;
    } while (b14);
    b16 = (!b15 && !b14) < b15;
    if ((!b15 && !b14) == b15) {
      *(uint32_t *)(elem2 + ELEM_TYPE) = 0x2743;
      value2 = (uint8_t *)TPGetValue(tp,"stateno");
      if (value2 == (uint8_t *)0x0) {
        return 0;
      }
      mem = InfixToPostfix(value2,(int *)(elem2 + 0x18),player,(uint32_t *)0x0,1);
      if (mem == 0) {
        return 0;
      }
      ConstExpI((int *)(elem2 + 0x24),-1);
      mem2 = (int *)(elem2 + 0x30);
      ConstExpI(mem2,-1);
      value2 = (uint8_t *)TPGetValue(tp,"partnerstateno");
      mem = InfixToPostfix(value2,(int *)(elem2 + 0x24),player,(uint32_t *)0x0,1);
      if (mem == 0) {
        return 0;
      }
      value2 = (uint8_t *)TPGetValue(tp,"ctrl");
      mem = 1;
    }
    else {
      mem = 7;
      b14 = false;
      value2 = stk_11c;
      value3 = (uint8_t *)"tagout";
      do {
        if (mem == 0) break;
        mem = mem + -1;
        b16 = *value2 < *value3;
        b14 = *value2 == *value3;
        value2 = value2 + 1;
        value3 = value3 + 1;
      } while (b14);
      b15 = (!b16 && !b14) < b16;
      if ((!b16 && !b14) == b16) {
        *(uint32_t *)(elem2 + ELEM_TYPE) = 0x2744;
        return 1;
      }
      mem = 10;
      b14 = false;
      value2 = stk_11c;
      value3 = (uint8_t *)"selfstate";
      do {
        if (mem == 0) break;
        mem = mem + -1;
        b15 = *value2 < *value3;
        b14 = *value2 == *value3;
        value2 = value2 + 1;
        value3 = value3 + 1;
      } while (b14);
      b16 = (!b15 && !b14) < b15;
      if ((!b15 && !b14) == b15) {
        *(uint32_t *)(elem2 + ELEM_TYPE) = 2;
        value2 = (uint8_t *)TPGetValue(tp,"value");
        if (value2 == (uint8_t *)0x0) {
          return 0;
        }
        mem = InfixToPostfix(value2,(int *)(elem2 + 0x18),player,(uint32_t *)0x0,1);
        if (mem == 0) {
          return 0;
        }
        ConstExpI((int *)(elem2 + 0x24),-1);
        mem2 = (int *)(elem2 + 0x30);
        ConstExpI(mem2,-1);
        value2 = (uint8_t *)TPGetValue(tp,"ctrl");
        mem = InfixToPostfix(value2,(int *)(elem2 + 0x24),player,(uint32_t *)0x0,1);
        if (mem == 0) {
          return 0;
        }
        value2 = (uint8_t *)TPGetValue(tp,"anim");
        mem = 1;
      }
      else {
        mem = 8;
        b14 = false;
        value2 = stk_11c;
        value3 = (uint8_t *)"ctrlset";
        do {
          if (mem == 0) break;
          mem = mem + -1;
          b16 = *value2 < *value3;
          b14 = *value2 == *value3;
          value2 = value2 + 1;
          value3 = value3 + 1;
        } while (b14);
        b15 = (!b16 && !b14) < b16;
        if ((!b16 && !b14) == b16) {
          *(uint32_t *)(elem2 + ELEM_TYPE) = 0x14;
          value2 = (uint8_t *)TPGetValue(tp,"value");
          if (value2 == (uint8_t *)0x0) {
            return 0;
          }
          mem = 1;
          mem2 = (int *)(elem2 + 0x18);
        }
        else {
          mem = 5;
          b14 = false;
          value2 = stk_11c;
          value3 = (uint8_t *)(int)&str_turn;
          do {
            if (mem == 0) break;
            mem = mem + -1;
            b15 = *value2 < *value3;
            b14 = *value2 == *value3;
            value2 = value2 + 1;
            value3 = value3 + 1;
          } while (b14);
          b16 = (!b15 && !b14) < b15;
          if ((!b15 && !b14) == b15) {
            *(uint32_t *)(elem2 + ELEM_TYPE) = 3;
            return 1;
          }
          mem = 0xb;
          b14 = false;
          value2 = stk_11c;
          value3 = (uint8_t *)"changeanim";
          do {
            if (mem == 0) break;
            mem = mem + -1;
            b16 = *value2 < *value3;
            b14 = *value2 == *value3;
            value2 = value2 + 1;
            value3 = value3 + 1;
          } while (b14);
          b15 = (!b16 && !b14) < b16;
          if ((!b16 && !b14) == b16) {
            *(uint32_t *)(elem2 + ELEM_TYPE) = 0x20;
            value2 = (uint8_t *)TPGetValue(tp,"value");
            if (value2 == (uint8_t *)0x0) {
              return 0;
            }
            mem = InfixToPostfix(value2,(int *)(elem2 + 0x18),player,(uint32_t *)0x0,1);
            if (mem == 0) {
              return 0;
            }
            value2 = (uint8_t *)TPGetValue(tp,"elem");
            mem = 1;
            mem2 = (int *)(elem2 + 0x24);
          }
          else {
            mem = 0xc;
            b14 = false;
            value2 = stk_11c;
            value3 = (uint8_t *)"changeanim2";
            do {
              if (mem == 0) break;
              mem = mem + -1;
              b15 = *value2 < *value3;
              b14 = *value2 == *value3;
              value2 = value2 + 1;
              value3 = value3 + 1;
            } while (b14);
            b16 = (!b15 && !b14) < b15;
            if ((!b15 && !b14) == b15) {
              *(uint32_t *)(elem2 + ELEM_TYPE) = 0x21;
              value2 = (uint8_t *)TPGetValue(tp,"value");
              if (value2 == (uint8_t *)0x0) {
                return 0;
              }
              mem = InfixToPostfix(value2,(int *)(elem2 + 0x18),player,(uint32_t *)0x0,1);
              if (mem == 0) {
                return 0;
              }
              value2 = (uint8_t *)TPGetValue(tp,"elem");
              mem = 1;
              mem2 = (int *)(elem2 + 0x24);
            }
            else {
              mem = 8;
              b14 = false;
              value2 = stk_11c;
              value3 = &str_playsnd;
              do {
                if (mem == 0) break;
                mem = mem + -1;
                b16 = *value2 < *value3;
                b14 = *value2 == *value3;
                value2 = value2 + 1;
                value3 = value3 + 1;
              } while (b14);
              b15 = (!b16 && !b14) < b16;
              if ((!b16 && !b14) == b16) {
                mem2 = (int *)ecalloc(1,0x68);
                if (mem2 == (int *)0x0) {
                  return 0;
                }
                *(uint32_t *)(elem2 + ELEM_TYPE) = 0x22;
                mem = SCtrlParsePlaySndInfo(tp,player,mem2);
                if (mem == 0) {
                  free(mem2);
                  strcat((char *)(g + G_ERRMSG),"\nError parsing PlaySnd");
                  return 0;
                }
                goto L_080be390;
              }
              mem = 8;
              b14 = false;
              value2 = stk_11c;
              value3 = (uint8_t *)"stopsnd";
              do {
                if (mem == 0) break;
                mem = mem + -1;
                b15 = *value2 < *value3;
                b14 = *value2 == *value3;
                value2 = value2 + 1;
                value3 = value3 + 1;
              } while (b14);
              b16 = (!b15 && !b14) < b15;
              if ((!b15 && !b14) == b15) {
                *(uint32_t *)(elem2 + ELEM_TYPE) = 0x23;
                value2 = (uint8_t *)TPGetValue(tp,"channel");
                if (value2 == (uint8_t *)0x0) {
                  mem2 = g + G_ERRMSG;
                  value = "Missing channel parameter";
                  goto L_080bede5;
                }
                mem = 1;
                mem2 = (int *)(elem2 + 0x18);
              }
              else {
                mem = 7;
                b14 = false;
                value2 = stk_11c;
                value3 = (uint8_t *)"sndpan";
                do {
                  if (mem == 0) break;
                  mem = mem + -1;
                  b16 = *value2 < *value3;
                  b14 = *value2 == *value3;
                  value2 = value2 + 1;
                  value3 = value3 + 1;
                } while (b14);
                b15 = (!b16 && !b14) < b16;
                if ((!b16 && !b14) == b16) {
                  *(uint32_t *)(elem2 + ELEM_TYPE) = 0x24;
                  value2 = (uint8_t *)TPGetValue(tp,"channel");
                  if (value2 == (uint8_t *)0x0) {
                    mem2 = g + G_ERRMSG;
                    value = "Missing channel parameter";
                    goto L_080bede5;
                  }
                  mem = InfixToPostfix(value2,(int *)(elem2 + 0x18),player,(uint32_t *)0x0,1)
                  ;
                  if (mem == 0) {
                    return 0;
                  }
                  value2 = (uint8_t *)TPGetValue(tp,"abspan");
                  if (value2 != (uint8_t *)0x0) {
                    ConstExpI((int *)(elem2 + 0x30),1);
                    mem = InfixToPostfix(value2,(int *)(elem2 + 0x24),player,(uint32_t *)0x0,
                                           1);
                    if (mem == 0) {
                      return 0;
                    }
                  }
                  value2 = (uint8_t *)TPGetValue(tp,"pan");
                  mem = 1;
                  mem2 = (int *)(elem2 + 0x24);
                }
                else {
                  mem = 8;
                  b14 = false;
                  value2 = stk_11c;
                  value3 = (uint8_t *)"lifeset";
                  do {
                    if (mem == 0) break;
                    mem = mem + -1;
                    b15 = *value2 < *value3;
                    b14 = *value2 == *value3;
                    value2 = value2 + 1;
                    value3 = value3 + 1;
                  } while (b14);
                  b16 = (!b15 && !b14) < b15;
                  if ((!b15 && !b14) == b15) {
                    *(uint32_t *)(elem2 + ELEM_TYPE) = 10;
                    value2 = (uint8_t *)TPGetValue(tp,"value");
                    if (value2 == (uint8_t *)0x0) {
                      return 0;
                    }
                    mem = 1;
                    mem2 = (int *)(elem2 + 0x18);
                  }
                  else {
                    mem = 8;
                    b14 = false;
                    value2 = stk_11c;
                    value3 = (uint8_t *)(int)&str_lifeadd;
                    do {
                      if (mem == 0) break;
                      mem = mem + -1;
                      b16 = *value2 < *value3;
                      b14 = *value2 == *value3;
                      value2 = value2 + 1;
                      value3 = value3 + 1;
                    } while (b14);
                    b15 = (!b16 && !b14) < b16;
                    if ((!b16 && !b14) == b16) {
                      *(uint32_t *)(elem2 + ELEM_TYPE) = 0xb;
                      value2 = (uint8_t *)TPGetValue(tp,"value");
                      if (value2 == (uint8_t *)0x0) {
                        return 0;
                      }
                      mem = InfixToPostfix(value2,(int *)(elem2 + 0x18),player,
                                             (uint32_t *)0x0,1);
                      if (mem == 0) {
                        return 0;
                      }
                      ConstExpI((int *)(elem2 + 0x24),1);
                      value2 = (uint8_t *)TPGetValue(tp,"kill");
                      mem = InfixToPostfix(value2,(int *)(elem2 + 0x24),player,
                                             (uint32_t *)0x0,1);
                      if (mem == 0) {
                        return 0;
                      }
                      value2 = (uint8_t *)TPGetValue(tp,"absolute");
                      mem = 1;
                      mem2 = (int *)(elem2 + 0x30);
                    }
                    else {
                      mem = 9;
                      b14 = false;
                      value2 = stk_11c;
                      value3 = (uint8_t *)"powerset";
                      do {
                        if (mem == 0) break;
                        mem = mem + -1;
                        b15 = *value2 < *value3;
                        b14 = *value2 == *value3;
                        value2 = value2 + 1;
                        value3 = value3 + 1;
                      } while (b14);
                      b16 = (!b15 && !b14) < b15;
                      if ((!b15 && !b14) == b15) {
                        *(uint32_t *)(elem2 + ELEM_TYPE) = 0xc;
                        value2 = (uint8_t *)TPGetValue(tp,"value");
                        if (value2 == (uint8_t *)0x0) {
                          return 0;
                        }
                        mem = 1;
                        mem2 = (int *)(elem2 + 0x18);
                      }
                      else {
                        mem = 9;
                        b14 = false;
                        value2 = stk_11c;
                        value3 = (uint8_t *)(int)&str_poweradd;
                        do {
                          if (mem == 0) break;
                          mem = mem + -1;
                          b16 = *value2 < *value3;
                          b14 = *value2 == *value3;
                          value2 = value2 + 1;
                          value3 = value3 + 1;
                        } while (b14);
                        b15 = (!b16 && !b14) < b16;
                        if ((!b16 && !b14) == b16) {
                          *(uint32_t *)(elem2 + ELEM_TYPE) = 0xd;
                          value2 = (uint8_t *)TPGetValue(tp,"value");
                          if (value2 == (uint8_t *)0x0) {
                            return 0;
                          }
                          mem = 1;
                          mem2 = (int *)(elem2 + 0x18);
                        }
                        else {
                          mem = 7;
                          b14 = false;
                          value2 = stk_11c;
                          value3 = (uint8_t *)"posset";
                          do {
                            if (mem == 0) break;
                            mem = mem + -1;
                            b15 = *value2 < *value3;
                            b14 = *value2 == *value3;
                            value2 = value2 + 1;
                            value3 = value3 + 1;
                          } while (b14);
                          b16 = (!b15 && !b14) < b15;
                          if ((!b15 && !b14) == b15) {
                            *(uint32_t *)(elem2 + ELEM_TYPE) = 0x15;
                            value2 = (uint8_t *)TPGetValue(tp,"x");
                            if (value2 != (uint8_t *)0x0) {
                              ConstExpI((int *)(elem2 + 0x18),1);
                              mem = InfixToPostfix(value2,(int *)(elem2 + 0x3c),player,
                                                     (uint32_t *)0x0,2);
                              if (mem == 0) {
                                return 0;
                              }
                            }
                            value2 = (uint8_t *)TPGetValue(tp,"y");
                            if (value2 != (uint8_t *)0x0) {
                              ConstExpI((int *)(elem2 + 0x24),1);
                              mem = InfixToPostfix(value2,(int *)(elem2 + 0x48),player,
                                                     (uint32_t *)0x0,2);
                              if (mem == 0) {
                                return 0;
                              }
                            }
                            value2 = (uint8_t *)TPGetValue(tp,"z");
                            if (value2 == (uint8_t *)0x0) {
                              return 1;
                            }
                            ConstExpI((int *)(elem2 + 0x30),1);
                            mem = 2;
                            mem2 = (int *)(elem2 + 0x54);
                          }
                          else {
                            mem = 7;
                            b14 = false;
                            value2 = stk_11c;
                            value3 = (uint8_t *)"posadd";
                            do {
                              if (mem == 0) break;
                              mem = mem + -1;
                              b16 = *value2 < *value3;
                              b14 = *value2 == *value3;
                              value2 = value2 + 1;
                              value3 = value3 + 1;
                            } while (b14);
                            b15 = (!b16 && !b14) < b16;
                            if ((!b16 && !b14) == b16) {
                              *(uint32_t *)(elem2 + ELEM_TYPE) = 0x16;
                              value2 = (uint8_t *)TPGetValue(tp,"x");
                              if (value2 != (uint8_t *)0x0) {
                                ConstExpI((int *)(elem2 + 0x18),1);
                                mem = InfixToPostfix(value2,(int *)(elem2 + 0x3c),player,
                                                       (uint32_t *)0x0,2);
                                if (mem == 0) {
                                  return 0;
                                }
                              }
                              value2 = (uint8_t *)TPGetValue(tp,"y");
                              if (value2 != (uint8_t *)0x0) {
                                ConstExpI((int *)(elem2 + 0x24),1);
                                mem = InfixToPostfix(value2,(int *)(elem2 + 0x48),player,
                                                       (uint32_t *)0x0,2);
                                if (mem == 0) {
                                  return 0;
                                }
                              }
                              value2 = (uint8_t *)TPGetValue(tp,"z");
                              if (value2 == (uint8_t *)0x0) {
                                return 1;
                              }
                              ConstExpI((int *)(elem2 + 0x30),1);
                              mem = 2;
                              mem2 = (int *)(elem2 + 0x54);
                            }
                            else {
                              mem = 10;
                              b14 = false;
                              value2 = stk_11c;
                              value3 = (uint8_t *)"posfreeze";
                              do {
                                if (mem == 0) break;
                                mem = mem + -1;
                                b15 = *value2 < *value3;
                                b14 = *value2 == *value3;
                                value2 = value2 + 1;
                                value3 = value3 + 1;
                              } while (b14);
                              b16 = (!b15 && !b14) < b15;
                              if ((!b15 && !b14) == b15) {
                                *(uint32_t *)(elem2 + ELEM_TYPE) = 0x17;
                                mem2 = (int *)(elem2 + 0x18);
                                ConstExpI(mem2,1);
                                value2 = (uint8_t *)TPGetValue(tp,"value");
                                mem = 1;
                              }
                              else {
                                mem = 7;
                                b14 = false;
                                value2 = stk_11c;
                                value3 = (uint8_t *)(int)&str_velset;
                                do {
                                  if (mem == 0) break;
                                  mem = mem + -1;
                                  b16 = *value2 < *value3;
                                  b14 = *value2 == *value3;
                                  value2 = value2 + 1;
                                  value3 = value3 + 1;
                                } while (b14);
                                b15 = (!b16 && !b14) < b16;
                                if ((!b16 && !b14) == b16) {
                                  *(uint32_t *)(elem2 + ELEM_TYPE) = 0x18;
                                  value2 = (uint8_t *)TPGetValue(tp,"x");
                                  if (value2 != (uint8_t *)0x0) {
                                    ConstExpI((int *)(elem2 + 0x18),1);
                                    mem = InfixToPostfix(value2,(int *)(elem2 + 0x3c),player,
                                                           (uint32_t *)0x0,2);
                                    if (mem == 0) {
                                      return 0;
                                    }
                                  }
                                  value2 = (uint8_t *)TPGetValue(tp,"y");
                                  if (value2 != (uint8_t *)0x0) {
                                    ConstExpI((int *)(elem2 + 0x24),1);
                                    mem = InfixToPostfix(value2,(int *)(elem2 + 0x48),player,
                                                           (uint32_t *)0x0,2);
                                    if (mem == 0) {
                                      return 0;
                                    }
                                  }
                                  value2 = (uint8_t *)TPGetValue(tp,"z");
                                  if (value2 == (uint8_t *)0x0) {
                                    return 1;
                                  }
                                  ConstExpI((int *)(elem2 + 0x30),1);
                                  mem = 2;
                                  mem2 = (int *)(elem2 + 0x54);
                                }
                                else {
                                  mem = 7;
                                  b14 = false;
                                  value2 = stk_11c;
                                  value3 = (uint8_t *)(int)&str_veladd;
                                  do {
                                    if (mem == 0) break;
                                    mem = mem + -1;
                                    b15 = *value2 < *value3;
                                    b14 = *value2 == *value3;
                                    value2 = value2 + 1;
                                    value3 = value3 + 1;
                                  } while (b14);
                                  b16 = (!b15 && !b14) < b15;
                                  if ((!b15 && !b14) == b15) {
                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x19;
                                    value2 = (uint8_t *)TPGetValue(tp,"x");
                                    if (value2 != (uint8_t *)0x0) {
                                      ConstExpI((int *)(elem2 + 0x18),1);
                                      mem = InfixToPostfix(value2,(int *)(elem2 + 0x3c),player,
                                                             (uint32_t *)0x0,2);
                                      if (mem == 0) {
                                        return 0;
                                      }
                                    }
                                    value2 = (uint8_t *)TPGetValue(tp,"y");
                                    if (value2 != (uint8_t *)0x0) {
                                      ConstExpI((int *)(elem2 + 0x24),1);
                                      mem = InfixToPostfix(value2,(int *)(elem2 + 0x48),player,
                                                             (uint32_t *)0x0,2);
                                      if (mem == 0) {
                                        return 0;
                                      }
                                    }
                                    value2 = (uint8_t *)TPGetValue(tp,"z");
                                    if (value2 == (uint8_t *)0x0) {
                                      return 1;
                                    }
                                    ConstExpI((int *)(elem2 + 0x30),1);
                                    mem = 2;
                                    mem2 = (int *)(elem2 + 0x54);
                                  }
                                  else {
                                    mem = 7;
                                    b14 = false;
                                    value2 = stk_11c;
                                    value3 = &str_velmul;
                                    do {
                                      if (mem == 0) break;
                                      mem = mem + -1;
                                      b16 = *value2 < *value3;
                                      b14 = *value2 == *value3;
                                      value2 = value2 + 1;
                                      value3 = value3 + 1;
                                    } while (b14);
                                    b15 = (!b16 && !b14) < b16;
                                    if ((!b16 && !b14) == b16) {
                                      *(uint32_t *)(elem2 + ELEM_TYPE) = 0x1a;
                                      value2 = (uint8_t *)TPGetValue(tp,"x");
                                      if (value2 != (uint8_t *)0x0) {
                                        ConstExpI((int *)(elem2 + 0x18),1);
                                        mem = InfixToPostfix(value2,(int *)(elem2 + 0x3c),
                                                               player,(uint32_t *)0x0,2);
                                        if (mem == 0) {
                                          return 0;
                                        }
                                      }
                                      value2 = (uint8_t *)TPGetValue(tp,"y");
                                      if (value2 != (uint8_t *)0x0) {
                                        ConstExpI((int *)(elem2 + 0x24),1);
                                        mem = InfixToPostfix(value2,(int *)(elem2 + 0x48),
                                                               player,(uint32_t *)0x0,2);
                                        if (mem == 0) {
                                          return 0;
                                        }
                                      }
                                      value2 = (uint8_t *)TPGetValue(tp,"z");
                                      if (value2 == (uint8_t *)0x0) {
                                        return 1;
                                      }
                                      ConstExpI((int *)(elem2 + 0x30),1);
                                      mem = 2;
                                      mem2 = (int *)(elem2 + 0x54);
                                    }
                                    else {
                                      mem = 8;
                                      b14 = false;
                                      value2 = stk_11c;
                                      value3 = (uint8_t *)"gravity";
                                      do {
                                        if (mem == 0) break;
                                        mem = mem + -1;
                                        b15 = *value2 < *value3;
                                        b14 = *value2 == *value3;
                                        value2 = value2 + 1;
                                        value3 = value3 + 1;
                                      } while (b14);
                                      b16 = (!b15 && !b14) < b15;
                                      if ((!b15 && !b14) == b15) {
                                        *(uint32_t *)(elem2 + ELEM_TYPE) = 0x1b;
                                        return 1;
                                      }
                                      mem = 7;
                                      b14 = false;
                                      value2 = stk_11c;
                                      value3 = &str_hitdef;
                                      do {
                                        if (mem == 0) break;
                                        mem = mem + -1;
                                        b16 = *value2 < *value3;
                                        b14 = *value2 == *value3;
                                        value2 = value2 + 1;
                                        value3 = value3 + 1;
                                      } while (b14);
                                      b15 = (!b16 && !b14) < b16;
                                      if ((!b16 && !b14) == b16) {
                                        mem2 = (int *)ecalloc(1,0x514);
                                        if (mem2 == (int *)0x0) {
                                          return 0;
                                        }
                                        *(uint32_t *)(elem2 + ELEM_TYPE) = 0x25;
                                        b14 = SCtrlParseHitDef(tp,player,mem2);
                                        if (ZEXT8(b14) == 0) {
                                          free(mem2);
                                          strcat((char *)(g + G_ERRMSG),"\nError parsing Hitdef");
                                          return 0;
                                        }
                                        goto L_080be2cc;
                                      }
                                      mem = 0xc;
                                      b14 = false;
                                      value2 = stk_11c;
                                      value3 = (uint8_t *)"reversaldef";
                                      do {
                                        if (mem == 0) break;
                                        mem = mem + -1;
                                        b15 = *value2 < *value3;
                                        b14 = *value2 == *value3;
                                        value2 = value2 + 1;
                                        value3 = value3 + 1;
                                      } while (b14);
                                      b16 = (!b15 && !b14) < b15;
                                      if ((!b15 && !b14) == b15) {
                                        mem2 = (int *)ecalloc(1,0x514);
                                        if (mem2 == (int *)0x0) {
                                          return 0;
                                        }
                                        *(uint32_t *)(elem2 + ELEM_TYPE) = 0x26;
                                        value = TPGetValue(tp,"reversal.attr");
                                        if (value == (char *)0x0) {
                                          mem2 = g + G_ERRMSG;
                                          value = "Missing reversal.attr parameter";
                                        }
                                        else {
                                          u6 = ParseHitAttr((int)value,0);
                                          mem2[0x69] = u6;
                                          if (u6 != 0xffffffff) {
                                            b14 = SCtrlParseHitDef(tp,player,mem2);
                                            if (ZEXT8(b14) == 0) {
                                              free(mem2);
                                              strcat((char *)(g + G_ERRMSG),
                                                     "\nError parsing Reversaldef");
                                              return 0;
                                            }
                                            goto L_080be2cc;
                                          }
                                          mem2 = g + G_ERRMSG;
                                          fmt_args[0] = (void *)(value);
                                          value = "Invalid reversal.attr: %s";
                                        }
                                        goto L_080bede5;
                                      }
                                      mem = 6;
                                      b14 = false;
                                      value2 = stk_11c;
                                      value3 = (uint8_t *)(int)&str_hitby;
                                      do {
                                        if (mem == 0) break;
                                        mem = mem + -1;
                                        b16 = *value2 < *value3;
                                        b14 = *value2 == *value3;
                                        value2 = value2 + 1;
                                        value3 = value3 + 1;
                                      } while (b14);
                                      b15 = (!b16 && !b14) < b16;
                                      if ((!b16 && !b14) == b16) {
                                        *(uint32_t *)(elem2 + ELEM_TYPE) = 0x1e;
                                        value = TPGetValue(tp,"value");
                                        if (value == (char *)0x0) {
                                          value = TPGetValue(tp,"value2");
                                          if (value == (char *)0x0) {
                                            return 0;
                                          }
                                          mem = 1;
                                        }
                                        else {
                                          mem = 0;
                                        }
                                        ConstExpI((int *)(elem2 + 0x30),mem);
                                        u6 = ParseHitAttr((int)value,0);
                                        ConstExpI((int *)(elem2 + 0x18),u6);
                                        if (*(int *)(elem2 + 0x20) == -1) {
                                          return 0;
                                        }
                                        mem2 = (int *)(elem2 + 0x24);
                                        ConstExpI(mem2,1);
                                        value2 = (uint8_t *)TPGetValue(tp,"time");
                                        mem = 1;
                                      }
                                      else {
                                        mem = 9;
                                        b14 = false;
                                        value2 = stk_11c;
                                        value3 = (uint8_t *)"nothitby";
                                        do {
                                          if (mem == 0) break;
                                          mem = mem + -1;
                                          b15 = *value2 < *value3;
                                          b14 = *value2 == *value3;
                                          value2 = value2 + 1;
                                          value3 = value3 + 1;
                                        } while (b14);
                                        b16 = (!b15 && !b14) < b15;
                                        if ((!b15 && !b14) == b15) {
                                          *(uint32_t *)(elem2 + ELEM_TYPE) = 0x1e;
                                          value = TPGetValue(tp,"value");
                                          if (value == (char *)0x0) {
                                            value = TPGetValue(tp,"value2");
                                            if (value == (char *)0x0) {
                                              return 0;
                                            }
                                            mem = 1;
                                          }
                                          else {
                                            mem = 0;
                                          }
                                          ConstExpI((int *)(elem2 + 0x30),mem);
                                          u6 = ParseHitAttr((int)value,0);
                                          ConstExpI((int *)(elem2 + 0x18),u6);
                                          if (*(uint32_t *)(elem2 + 0x20) == 0xffffffff) {
                                            return 0;
                                          }
                                          *(uint32_t *)(elem2 + 0x20) =
                                               (*(uint32_t *)(elem2 + 0x20) ^ 0xffffffff) & 0xfff;
                                          mem2 = (int *)(elem2 + 0x24);
                                          ConstExpI(mem2,1);
                                          value2 = (uint8_t *)TPGetValue(tp,"time");
                                          mem = 1;
                                        }
                                        else {
                                          mem = 10;
                                          b14 = false;
                                          value2 = stk_11c;
                                          value3 = (uint8_t *)"hitvelset";
                                          do {
                                            if (mem == 0) break;
                                            mem = mem + -1;
                                            b16 = *value2 < *value3;
                                            b14 = *value2 == *value3;
                                            value2 = value2 + 1;
                                            value3 = value3 + 1;
                                          } while (b14);
                                          b15 = (!b16 && !b14) < b16;
                                          if ((!b16 && !b14) == b16) {
                                            *(uint32_t *)(elem2 + ELEM_TYPE) = 0x65;
                                            value2 = (uint8_t *)TPGetValue(tp,"x");
                                            mem = InfixToPostfix(value2,(int *)(elem2 + 0x18),
                                                                   player,(uint32_t *)0x0,1);
                                            if (mem == 0) {
                                              return 0;
                                            }
                                            value2 = (uint8_t *)TPGetValue(tp,"y");
                                            mem = 1;
                                            mem2 = (int *)(elem2 + 0x24);
                                          }
                                          else {
                                            mem = 0xb;
                                            b14 = false;
                                            value2 = stk_11c;
                                            value3 = (uint8_t *)"hitfallset";
                                            do {
                                              if (mem == 0) break;
                                              mem = mem + -1;
                                              b15 = *value2 < *value3;
                                              b14 = *value2 == *value3;
                                              value2 = value2 + 1;
                                              value3 = value3 + 1;
                                            } while (b14);
                                            b16 = (!b15 && !b14) < b15;
                                            if ((!b15 && !b14) == b15) {
                                              *(uint32_t *)(elem2 + ELEM_TYPE) = 100;
                                              ConstExpI((int *)(elem2 + 0x18),-1);
                                              ConstExpF((int *)(elem2 + 0x3c),-0x39001000);
                                              ConstExpF((int *)(elem2 + 0x48),-0x39001000);
                                              value2 = (uint8_t *)TPGetValue(tp,"value");
                                              mem = InfixToPostfix(value2,(int *)(elem2 + 0x18),
                                                                     player,(uint32_t *)0x0,1);
                                              if (mem == 0) {
                                                return 0;
                                              }
                                              value2 = (uint8_t *)TPGetValue(tp,"velocity");
                                              SCtrlReadExpList(value2,"ff",player,&value4,
                                                               (int *)(elem2 + 0x3c),
                                                               (int *)(elem2 + 0x48));
                                              goto L_join_080bb972;
                                            }
                                            mem = 0xe;
                                            b14 = false;
                                            value2 = stk_11c;
                                            value3 = (uint8_t *)"hitfalldamage";
                                            do {
                                              if (mem == 0) break;
                                              mem = mem + -1;
                                              b16 = *value2 < *value3;
                                              b14 = *value2 == *value3;
                                              value2 = value2 + 1;
                                              value3 = value3 + 1;
                                            } while (b14);
                                            b15 = (!b16 && !b14) < b16;
                                            if ((!b16 && !b14) == b16) {
                                              *(uint32_t *)(elem2 + ELEM_TYPE) = 0x66;
                                              return 1;
                                            }
                                            mem = 0xb;
                                            b14 = false;
                                            value2 = stk_11c;
                                            value3 = (uint8_t *)"hitfallvel";
                                            do {
                                              if (mem == 0) break;
                                              mem = mem + -1;
                                              b15 = *value2 < *value3;
                                              b14 = *value2 == *value3;
                                              value2 = value2 + 1;
                                              value3 = value3 + 1;
                                            } while (b14);
                                            b16 = (!b15 && !b14) < b15;
                                            if ((!b15 && !b14) == b15) {
                                              *(uint32_t *)(elem2 + ELEM_TYPE) = 0x67;
                                              return 1;
                                            }
                                            mem = 7;
                                            b14 = false;
                                            value2 = stk_11c;
                                            value3 = (uint8_t *)"hitadd";
                                            do {
                                              if (mem == 0) break;
                                              mem = mem + -1;
                                              b16 = *value2 < *value3;
                                              b14 = *value2 == *value3;
                                              value2 = value2 + 1;
                                              value3 = value3 + 1;
                                            } while (b14);
                                            b15 = (!b16 && !b14) < b16;
                                            if ((!b16 && !b14) == b16) {
                                              *(uint32_t *)(elem2 + ELEM_TYPE) = 0x68;
                                              value2 = (uint8_t *)TPGetValue(tp,"value");
                                              if (value2 == (uint8_t *)0x0) {
                                                return 0;
                                              }
                                              mem = 1;
                                              mem2 = (int *)(elem2 + 0x18);
                                            }
                                            else {
                                              mem = 0xd;
                                              b14 = false;
                                              value2 = stk_11c;
                                              value3 = (uint8_t *)"attackmulset";
                                              do {
                                                if (mem == 0) break;
                                                mem = mem + -1;
                                                b15 = *value2 < *value3;
                                                b14 = *value2 == *value3;
                                                value2 = value2 + 1;
                                                value3 = value3 + 1;
                                              } while (b14);
                                              b16 = (!b15 && !b14) < b15;
                                              if ((!b15 && !b14) == b15) {
                                                *(uint32_t *)(elem2 + ELEM_TYPE) = 0x69;
                                                value2 = (uint8_t *)TPGetValue(tp,"value");
                                                if (value2 == (uint8_t *)0x0) {
                                                  return 0;
                                                }
                                                mem = 2;
                                                mem2 = (int *)(elem2 + 0x3c);
                                              }
                                              else {
                                                mem = 0xe;
                                                b14 = false;
                                                value2 = stk_11c;
                                                value3 = (uint8_t *)"defencemulset";
                                                do {
                                                  if (mem == 0) break;
                                                  mem = mem + -1;
                                                  b16 = *value2 < *value3;
                                                  b14 = *value2 == *value3;
                                                  value2 = value2 + 1;
                                                  value3 = value3 + 1;
                                                } while (b14);
                                                b15 = (!b16 && !b14) < b16;
                                                if ((!b16 && !b14) == b16) {
                                                  *(uint32_t *)(elem2 + ELEM_TYPE) = 0x6a;
                                                  value2 = (uint8_t *)TPGetValue(tp,"value");
                                                  if (value2 == (uint8_t *)0x0) {
                                                    return 0;
                                                  }
                                                  mem = 2;
                                                  mem2 = (int *)(elem2 + 0x3c);
                                                }
                                                else {
                                                  mem = 0xd;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"statetypeset";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) == b15) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x6e;
                                                    ConstExpI((int *)(elem2 + 0x18),-1);
                                                    ConstExpI((int *)(elem2 + 0x24),-1);
                                                    ConstExpI((int *)(elem2 + 0x30),-1);
                                                    value = TPGetValue(tp,"statetype");
                                                    if (value == (char *)0x0) {
                                                      value = TPGetValue(tp,"value");
                                                    }
                                                    if (value != (char *)0x0) {
                                                      mem = *(int *)(__ctype_tolower + *value * 4
                                                                      );
                                                      if (mem == 99) {
                                                        mem = 2;
                                                      }
                                                      else if (mem < 100) {
                                                        if (mem != 0x61) {
L_080bbc25:
                                                          mem2 = g + G_ERRMSG;
                                                          fmt_args[0] = (void *)(value);
                                                          value = "State type \"%s\" not valid";
                                                          goto L_080bede5;
                                                        }
                                                        mem = 3;
                                                      }
                                                      else if (mem == 0x6c) {
                                                        mem = 4;
                                                      }
                                                      else {
                                                        if (mem != 0x73) goto L_080bbc25;
                                                        mem = 1;
                                                      }
                                                      ConstExpI((int *)(elem2 + 0x18),mem);
                                                    }
                                                    value = TPGetValue(tp,"movetype");
                                                    if (value != (char *)0x0) {
                                                      mem = *(int *)(__ctype_tolower + *value * 4
                                                                      );
                                                      if (mem == 0x68) {
                                                        mem = 2;
                                                      }
                                                      else if (mem < 0x69) {
                                                        if (mem != 0x61) {
L_080bbcb0:
                                                          mem2 = g + G_ERRMSG;
                                                          fmt_args[0] = (void *)(value);
                                                          value = "State movetype \"%s\" not valid"
                                                          ;
                                                          goto L_080bede5;
                                                        }
                                                        mem = 1;
                                                      }
                                                      else {
                                                        if (mem != 0x69) goto L_080bbcb0;
                                                        mem = 0;
                                                      }
                                                      ConstExpI((int *)(elem2 + 0x24),mem);
                                                    }
                                                    value = TPGetValue(tp,"physics");
                                                    if (value == (char *)0x0) {
                                                      return 1;
                                                    }
                                                    mem = *(int *)(__ctype_tolower + *value * 4);
                                                    if (mem == 99) {
                                                      mem = 2;
                                                    }
                                                    else if (mem < 100) {
                                                      if (mem != 0x61) {
L_080bbd40:
                                                        mem2 = g + G_ERRMSG;
                                                        fmt_args[0] = (void *)(value);
                                                        value = "State physics \"%s\" not valid";
                                                        goto L_080bede5;
                                                      }
                                                      mem = 3;
                                                    }
                                                    else if (mem == 0x6e) {
                                                      mem = 0;
                                                    }
                                                    else {
                                                      if (mem != 0x73) goto L_080bbd40;
L_080be8a5:
                                                      mem = 1;
                                                    }
                                                    mem2 = (int *)(elem2 + 0x30);
L_080be8b2:
                                                    ConstExpI(mem2,mem);
                                                    return 1;
                                                  }
                                                  mem = 0xc;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"hitoverride";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b15 = (!b16 && !b14) < b16;
                                                  if ((!b16 && !b14) == b16) {
                                                    mem2 = (int *)ecalloc(1,0x28);
                                                    if (mem2 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x78;
                                                    b14 = SCtrlParseHitOverride
                                                                       (tp,player,mem2);
                                                    if (ZEXT8(b14) == 0) {
                                                      free(mem2);
                                                      strcat((char *)(g + G_ERRMSG),
                                                             "\nError parsing HitOverride");
                                                      return 0;
                                                    }
                                                    value2 = (uint8_t *)TPGetValue(tp,"slot");
                                                    mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                         0x18),
                                                                           player,(uint32_t *)0x0
                                                                           ,1);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    goto L_080be390;
                                                  }
                                                  mem = 0xd;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"movehitreset";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) == b15) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x82;
                                                    return 1;
                                                  }
                                                  mem = 0xe;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"assertspecial";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b15 = (!b16 && !b14) < b16;
                                                  if ((!b16 && !b14) == b16) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x96;
                                                    value = TPGetValue(tp,"flag");
                                                    if (value == (char *)0x0) {
                                                      mem2 = g + G_ERRMSG;
                                                      value = 
                                                  "AssertSpecial flag parameter missing";
                                                  }
                                                  else {
                                                    mem = ParseSpecialFlag(value,&stk_128,
                                                                             &stk_124);
                                                    if (mem == 0) {
                                                      mem2 = g + G_ERRMSG;
                                                      fmt_args[0] = (void *)(value);
                                                      value = "AssertSpecial flag \"%s\" not valid"
                                                      ;
                                                    }
                                                    else {
                                                      ConstExpI((int *)(elem2 + 0x18),stk_128);
                                                      ConstExpI((int *)(elem2 + 0x3c),stk_124);
                                                      ConstExpI((int *)(elem2 + 0x24),-1);
                                                      ConstExpI((int *)(elem2 + 0x30),-1);
                                                      value = TPGetValue(tp,"flag2");
                                                      if (value != (char *)0x0) {
                                                        mem = ParseSpecialFlag(value,&stk_128,
                                                                                 &stk_124);
                                                        if (mem == 0) {
                                                          mem2 = g + G_ERRMSG;
                                                          fmt_args[0] = (void *)(value);
                                                          value = 
                                                  "AssertSpecial flag2 \"%s\" not valid";
                                                  goto L_080bede5;
                                                  }
                                                  ConstExpI((int *)(elem2 + 0x24),stk_128);
                                                  ConstExpI((int *)(elem2 + 0x48),stk_124);
                                                  }
                                                  value = TPGetValue(tp,"flag3");
                                                  if (value == (char *)0x0) {
                                                    return 1;
                                                  }
                                                  mem = ParseSpecialFlag(value,&stk_128,
                                                                           &stk_124);
                                                  if (mem != 0) {
                                                    ConstExpI((int *)(elem2 + 0x30),stk_128);
                                                    mem2 = (int *)(elem2 + 0x54);
                                                    mem = stk_124;
                                                    goto L_080be8b2;
                                                  }
                                                  mem2 = g + G_ERRMSG;
                                                  fmt_args[0] = (void *)(value);
                                                  value = "AssertSpecial flag3 \"%s\" not valid";
                                                  }
                                                  }
                                                  goto L_080bede5;
                                                  }
                                                  mem = 0xb;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"projectile";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) == b15) {
                                                    mem2 = (int *)ecalloc(1,0x69c);
                                                    if (mem2 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x27;
                                                    mem = SCtrlParseProjectile
                                                                      (tp,player,mem2);
                                                    if (mem == 0) {
                                                      free(mem2);
                                                      strcat((char *)(g + G_ERRMSG),
                                                             "\nError parsing Projectile");
                                                      return 0;
                                                    }
                                                    goto L_080be390;
                                                  }
                                                  mem = 6;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)(int)&str_width;
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b15 = (!b16 && !b14) < b16;
                                                  if ((!b16 && !b14) == b16) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x28;
                                                    ConstExpI((int *)(elem2 + 0x3c),0);
                                                    ConstExpI((int *)(elem2 + 0x18),0);
                                                    ConstExpI((int *)(elem2 + 0x24),0);
                                                    ConstExpI((int *)(elem2 + 0x30),0);
                                                    value2 = (uint8_t *)TPGetValue(tp,"edge");
                                                    SCtrlReadExpList(value2,"ii",player,&value4,
                                                                     (int *)(elem2 + 0x18),
                                                                     (int *)(elem2 + 0x24));
                                                    if ((value2 != (uint8_t *)0x0) && (*value4 != 0)
                                                       ) {
                                                      return 0;
                                                    }
                                                    value3 = (uint8_t *)TPGetValue(tp,"player");
                                                    SCtrlReadExpList(value3,"ii",player,&value4,
                                                                     (int *)(elem2 + 0x30),
                                                                     (int *)(elem2 + 0x3c));
                                                    if ((value3 != (uint8_t *)0x0) && (*value4 != 0)
                                                       ) {
                                                      return 0;
                                                    }
                                                    if (value2 != (uint8_t *)0x0 ||
                                                        value3 != (uint8_t *)0x0) {
                                                      return 1;
                                                    }
                                                    value2 = (uint8_t *)TPGetValue(tp,"value");
                                                    value2 = SCtrlReadExpList(value2,"ii",player,
                                                                              &value4,
                                                                              (int *)(elem2 + 0x18
                                                                                     ),(int *)(
                                                  elem2 + 0x24));
                                                  if (value2 != (uint8_t *)0x0) {
                                                    if (*value4 == 0) {
                                                      expcpytrig((int *)(elem2 + 0x30),
                                                                 (int *)(elem2 + 0x18));
                                                      expcpytrig((int *)(elem2 + 0x3c),
                                                                 (int *)(elem2 + 0x24));
                                                      return 1;
                                                    }
                                                    return 0;
                                                  }
                                                  return 0;
                                                  }
                                                  mem = 0xc;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)(int)&str_sprpriority;
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) == b15) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x33;
                                                    value2 = (uint8_t *)TPGetValue(tp,"value");
                                                    mem = 1;
                                                    mem2 = (int *)(elem2 + 0x18);
                                                    goto L_080be815;
                                                  }
                                                  mem = 10;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"angledraw";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b15 = (!b16 && !b14) < b16;
                                                  if ((!b16 && !b14) == b16) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x3c;
                                                    ConstExpF((int *)(elem2 + 0x48),0x3f800000);
                                                    ConstExpF((int *)(elem2 + 0x54),0x3f800000);
                                                    mem = ItoP_TPConstF(tp,"value",
                                                                          (int *)(elem2 + 0x3c),
                                                                          player,-0x39001000);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    value2 = (uint8_t *)TPGetValue(tp,"scale");
                                                    SCtrlReadExpList(value2,"ff",player,&value4,
                                                                     (int *)(elem2 + 0x48),
                                                                     (int *)(elem2 + 0x54));
                                                    goto L_join_080bb972;
                                                  }
                                                  mem = 9;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"angleset";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) == b15) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x3d;
                                                    value2 = (uint8_t *)TPGetValue(tp,"value");
                                                    mem = 2;
                                                    mem2 = (int *)(elem2 + 0x3c);
                                                  }
                                                  else {
                                                    mem = 9;
                                                    b14 = false;
                                                    value2 = stk_11c;
                                                    value3 = (uint8_t *)"angleadd";
                                                    do {
                                                      if (mem == 0) break;
                                                      mem = mem + -1;
                                                      b16 = *value2 < *value3;
                                                      b14 = *value2 == *value3;
                                                      value2 = value2 + 1;
                                                      value3 = value3 + 1;
                                                    } while (b14);
                                                    b15 = (!b16 && !b14) < b16;
                                                    if ((!b16 && !b14) == b16) {
                                                      *(uint32_t *)(elem2 + ELEM_TYPE) = 0x3e;
                                                      value2 = (uint8_t *)TPGetValue(tp,"value");
                                                      mem = 2;
                                                      mem2 = (int *)(elem2 + 0x3c);
                                                    }
                                                    else {
                                                      mem = 9;
                                                      b14 = false;
                                                      value2 = stk_11c;
                                                      value3 = (uint8_t *)"anglemul";
                                                      do {
                                                        if (mem == 0) break;
                                                        mem = mem + -1;
                                                        b15 = *value2 < *value3;
                                                        b14 = *value2 == *value3;
                                                        value2 = value2 + 1;
                                                        value3 = value3 + 1;
                                                      } while (b14);
                                                      b16 = (!b15 && !b14) < b15;
                                                      if ((!b15 && !b14) != b15) {
                                                        mem = 6;
                                                        b14 = false;
                                                        value2 = stk_11c;
                                                        value3 = (uint8_t *)(int)&str_trans;
                                                        do {
                                                          if (mem == 0) break;
                                                          mem = mem + -1;
                                                          b16 = *value2 < *value3;
                                                          b14 = *value2 == *value3;
                                                          value2 = value2 + 1;
                                                          value3 = value3 + 1;
                                                        } while (b14);
                                                        b15 = (!b16 && !b14) < b16;
                                                        if ((!b16 && !b14) == b16) {
                                                          *(uint32_t *)(elem2 + ELEM_TYPE) = 0x41;
                                                          mem2 = (int *)(elem2 + 0x18);
                                                          ConstExpI(mem2,-1);
                                                          ConstExpI((int *)(elem2 + 0x24),0x100);
                                                          ConstExpI((int *)(elem2 + 0x30),0);
                                                          value = TPGetValue(tp,"trans");
                                                          if (value != (char *)0x0) {
                                                            mem = _alemu_stricmp(value,"none");
                                                            if (mem == 0) {
                                                              mem = 0;
                                                            }
                                                            else if ((*value == '\0') ||
                                                                    (mem = _alemu_stricmp(value,
                                                  "default"), mem == 0)) {
                                                    mem = -1;
                                                  }
                                                  else {
                                                    mem = _alemu_stricmp(value,"add");
                                                    if (mem == 0) {
                                                      mem = 1;
                                                    }
                                                    else {
                                                      mem = _alemu_stricmp(value,"add1");
                                                      if (mem == 0) {
                                                        ConstExpI(mem2,3);
                                                        ConstExpI((int *)(elem2 + 0x24),0x100);
                                                        mem = 0x80;
                                                        mem2 = (int *)(elem2 + 0x30);
                                                      }
                                                      else {
                                                        mem = _alemu_stricmp(value,"addalpha");
                                                        if (mem == 0) {
                                                          mem = 3;
                                                        }
                                                        else {
                                                          mem = _alemu_stricmp(value,"sub");
                                                          if (mem != 0) {
                                                            mem2 = g + G_ERRMSG;
                                                            fmt_args[0] = (void *)(value);
                                                            value = "Invalid trans type: %s";
                                                            goto L_080bede5;
                                                          }
                                                          mem = 2;
                                                        }
                                                      }
                                                    }
                                                  }
                                                  ConstExpI(mem2,mem);
                                                  }
                                                  value2 = (uint8_t *)TPGetValue(tp,"alpha");
                                                  if (value2 == (uint8_t *)0x0) {
                                                    return 1;
                                                  }
                                                  SCtrlReadExpList(value2,"ii",player,&value4,
                                                                   (int *)(elem2 + 0x24),
                                                                   (int *)(elem2 + 0x30));
                                                  }
                                                  else {
                                                    mem = 0xc;
                                                    b14 = false;
                                                    value2 = stk_11c;
                                                    value3 = (uint8_t *)"screenbound";
                                                    do {
                                                      if (mem == 0) break;
                                                      mem = mem + -1;
                                                      b15 = *value2 < *value3;
                                                      b14 = *value2 == *value3;
                                                      value2 = value2 + 1;
                                                      value3 = value3 + 1;
                                                    } while (b14);
                                                    b16 = (!b15 && !b14) < b15;
                                                    if ((!b15 && !b14) == b15) {
                                                      *(uint32_t *)(elem2 + ELEM_TYPE) = 0x32;
                                                      value2 = (uint8_t *)TPGetValue(tp,"value");
                                                      mem = InfixToPostfix(value2,(int *)(elem2 
                                                  + 0x18),player,(uint32_t *)0x0,1);
                                                  if (mem == 0) {
                                                    return 0;
                                                  }
                                                  ConstExpI((int *)(elem2 + 0x24),0);
                                                  ConstExpI((int *)(elem2 + 0x30),0);
                                                  value2 = (uint8_t *)TPGetValue(tp,"movecamera");
                                                  SCtrlReadExpList(value2,"ii",player,&value4,
                                                                   (int *)(elem2 + 0x24),
                                                                   (int *)(elem2 + 0x30));
                                                  }
                                                  else {
                                                    mem = 0xb;
                                                    b14 = false;
                                                    value2 = stk_11c;
                                                    value3 = (uint8_t *)"targetbind";
                                                    do {
                                                      if (mem == 0) break;
                                                      mem = mem + -1;
                                                      b16 = *value2 < *value3;
                                                      b14 = *value2 == *value3;
                                                      value2 = value2 + 1;
                                                      value3 = value3 + 1;
                                                    } while (b14);
                                                    b15 = (!b16 && !b14) < b16;
                                                    if ((!b16 && !b14) != b16) {
                                                      mem = 0xd;
                                                      b14 = false;
                                                      value2 = stk_11c;
                                                      value3 = (uint8_t *)"bindtotarget";
                                                      do {
                                                        if (mem == 0) break;
                                                        mem = mem + -1;
                                                        b15 = *value2 < *value3;
                                                        b14 = *value2 == *value3;
                                                        value2 = value2 + 1;
                                                        value3 = value3 + 1;
                                                      } while (b14);
                                                      b16 = (!b15 && !b14) < b15;
                                                      if ((!b15 && !b14) == b15) {
                                                        *(uint32_t *)(elem2 + ELEM_TYPE) = 0x47;
                                                        ConstExpI((int *)(elem2 + 0x18),1);
                                                        ConstExpI((int *)(elem2 + 0x30),-1);
                                                        ConstExpF((int *)(elem2 + 0x3c),
                                                                  -0x39001000);
                                                        ConstExpF((int *)(elem2 + 0x48),
                                                                  -0x39001000);
                                                        ConstExpF((int *)(elem2 + 0x54),0);
                                                        ConstExpI((int *)(elem2 + 0x24),0);
                                                        value2 = (uint8_t *)TPGetValue(tp,"time");
                                                        mem = InfixToPostfix(value2,(int *)(
                                                  elem2 + 0x18),player,(uint32_t *)0x0,1);
                                                  if (mem == 0) {
                                                    return 0;
                                                  }
                                                  value2 = (uint8_t *)TPGetValue(tp,"id");
                                                  mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                       0x30),player
                                                                         ,(uint32_t *)0x0,1);
                                                  if (mem == 0) {
                                                    return 0;
                                                  }
                                                  value2 = (uint8_t *)TPGetValue(tp,"pos");
                                                  if (value2 == (uint8_t *)0x0) {
                                                    return 1;
                                                  }
                                                  value2 = SCtrlReadExpList(value2,"ff:,",player,
                                                                            &value4,
                                                                            (int *)(elem2 + 0x3c),
                                                                            (int *)(elem2 + 0x48))
                                                  ;
                                                  b1 = *value4;
                                                  if ((b1 != 0) && (b1 != 0x2c)) {
                                                    return 0;
                                                  }
                                                  if ((b1 == 0x2c) && ((int)value2 < 2)) {
                                                    return 0;
                                                  }
                                                  if (*value4 != 0) {
                                                    value4 = value4 + 1;
                                                  }
                                                  b1 = *(uint8_t *)(__ctype_b + 1 +
                                                                   (char)*value4 * 2);
                                                  while ((b1 & 0x20) != 0) {
                                                    value4 = value4 + 1;
                                                    b1 = *(uint8_t *)(__ctype_b + 1 +
                                                                     (char)*value4 * 2);
                                                  }
                                                  mem = *(int *)(__ctype_tolower +
                                                                  (char)*value4 * 4);
                                                  if (mem == 0x68) {
                                                    mem = 2;
                                                    mem2 = (int *)(elem2 + 0x24);
                                                    goto L_080be8b2;
                                                  }
                                                  if (mem < 0x69) {
                                                    if (mem == 0) {
                                                      return 1;
                                                    }
                                                    if (mem == 0x66) {
                                                      mem = 0;
                                                      mem2 = (int *)(elem2 + 0x24);
                                                      goto L_080be8b2;
                                                    }
                                                  }
                                                  else if (mem == 0x6d) {
                                                    mem = 1;
                                                    mem2 = (int *)(elem2 + 0x24);
                                                    goto L_080be8b2;
                                                  }
                                                  mem2 = g + G_ERRMSG;
                                                  fmt_args[0] = (void *)(value4);
                                                  value = "Invalid bind position: %s";
                                                  goto L_080bede5;
                                                  }
                                                  mem = 0xc;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"targetstate";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b15 = (!b16 && !b14) < b16;
                                                  if ((!b16 && !b14) == b16) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x48;
                                                    value2 = (uint8_t *)TPGetValue(tp,"value");
                                                    if (value2 == (uint8_t *)0x0) {
                                                      return 0;
                                                    }
                                                    mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                         0x18),
                                                                           player,(uint32_t *)0x0
                                                                           ,1);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    mem = ItoP_TPConstI(tp,"id",
                                                                          (int *)(elem2 + 0x30),
                                                                          player,-1);
                                                    goto L_080be81a;
                                                  }
                                                  mem = 0xf;
                                                  u17 = 0;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"targetpoweradd";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    u17 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while ((bool)u17);
                                                  b14 = (!b15 && !(bool)u17) < b15;
                                                  if ((!b15 && !(bool)u17) == b15) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x49;
                                                    value2 = (uint8_t *)TPGetValue(tp,"value");
                                                    if (value2 == (uint8_t *)0x0) {
                                                      return 0;
                                                    }
                                                    mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                         0x18),
                                                                           player,(uint32_t *)0x0
                                                                           ,1);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    mem = ItoP_TPConstI(tp,"id",
                                                                          (int *)(elem2 + 0x30),
                                                                          player,-1);
                                                    goto L_080be81a;
                                                  }
                                                  mem = 0xe;
                                                  b16 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"targetlifeadd";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b14 = *value2 < *value3;
                                                    b16 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b16);
                                                  b15 = (!b14 && !b16) < b14;
                                                  if ((!b14 && !b16) == b14) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x4a;
                                                    value2 = (uint8_t *)TPGetValue(tp,"value");
                                                    if (value2 == (uint8_t *)0x0) {
                                                      return 0;
                                                    }
                                                    mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                         0x18),
                                                                           player,(uint32_t *)0x0
                                                                           ,1);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    ConstExpI((int *)(elem2 + 0x24),1);
                                                    value2 = (uint8_t *)TPGetValue(tp,"kill");
                                                    mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                         0x24),
                                                                           player,(uint32_t *)0x0
                                                                           ,1);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    value2 = (uint8_t *)TPGetValue(tp,"absolute");
                                                    mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                         0x30),
                                                                           player,(uint32_t *)0x0
                                                                           ,1);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    mem = ItoP_TPConstI(tp,"id",
                                                                          (int *)(elem2 + 0x54),
                                                                          player,-1);
                                                    goto L_080be81a;
                                                  }
                                                  mem = 0xd;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"targetvelset";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) == b15) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x4b;
                                                    mem = ItoP_TPConstF(tp,"x",
                                                                          (int *)(elem2 + 0x3c),
                                                                          player,-0x39001000);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    mem = ItoP_TPConstF(tp,"y",
                                                                          (int *)(elem2 + 0x48),
                                                                          player,-0x39001000);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    mem = ItoP_TPConstF(tp,"z",
                                                                          (int *)(elem2 + 0x54),
                                                                          player,-0x39001000);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    mem = ItoP_TPConstI(tp,"id",
                                                                          (int *)(elem2 + 0x30),
                                                                          player,-1);
                                                    goto L_080be81a;
                                                  }
                                                  mem = 0xd;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"targetveladd";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b15 = (!b16 && !b14) < b16;
                                                  if ((!b16 && !b14) == b16) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x4c;
                                                    mem = ItoP_TPConstF(tp,"x",
                                                                          (int *)(elem2 + 0x3c),
                                                                          player,-0x39001000);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    mem = ItoP_TPConstF(tp,"y",
                                                                          (int *)(elem2 + 0x48),
                                                                          player,-0x39001000);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    mem = ItoP_TPConstF(tp,"z",
                                                                          (int *)(elem2 + 0x54),
                                                                          player,-0x39001000);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    mem = ItoP_TPConstI(tp,"id",
                                                                          (int *)(elem2 + 0x30),
                                                                          player,-1);
                                                    goto L_080be81a;
                                                  }
                                                  mem = 0xd;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"targetfacing";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) == b15) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x4d;
                                                    value2 = (uint8_t *)TPGetValue(tp,"value");
                                                    mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                         0x18),
                                                                           player,(uint32_t *)0x0
                                                                           ,1);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    mem = ItoP_TPConstI(tp,"id",
                                                                          (int *)(elem2 + 0x30),
                                                                          player,-1);
                                                    goto L_080be81a;
                                                  }
                                                  mem = 0xb;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"targetdrop";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b15 = (!b16 && !b14) < b16;
                                                  if ((!b16 && !b14) == b16) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x4e;
                                                    ConstExpI((int *)(elem2 + 0x18),-1);
                                                    mem2 = (int *)(elem2 + 0x24);
                                                    ConstExpI(mem2,1);
                                                    value2 = (uint8_t *)TPGetValue(tp,"excludeID")
                                                    ;
                                                    mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                         0x18),
                                                                           player,(uint32_t *)0x0
                                                                           ,1);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    value2 = (uint8_t *)TPGetValue(tp,"keepone");
                                                    mem = 1;
                                                  }
                                                  else {
                                                    mem = 0xb;
                                                    b14 = false;
                                                    value2 = stk_11c;
                                                    value3 = (uint8_t *)"attackdist";
                                                    do {
                                                      if (mem == 0) break;
                                                      mem = mem + -1;
                                                      b15 = *value2 < *value3;
                                                      b14 = *value2 == *value3;
                                                      value2 = value2 + 1;
                                                      value3 = value3 + 1;
                                                    } while (b14);
                                                    b16 = (!b15 && !b14) < b15;
                                                    if ((!b15 && !b14) == b15) {
                                                      *(uint32_t *)(elem2 + ELEM_TYPE) = 0x50;
                                                      value2 = (uint8_t *)TPGetValue(tp,"value");
                                                      if (value2 == (uint8_t *)0x0) {
                                                        return 0;
                                                      }
                                                      mem = 1;
                                                      mem2 = (int *)(elem2 + 0x18);
                                                    }
                                                    else {
                                                      mem = 0xb;
                                                      b14 = false;
                                                      value2 = stk_11c;
                                                      value3 = (uint8_t *)"playerpush";
                                                      do {
                                                        if (mem == 0) break;
                                                        mem = mem + -1;
                                                        b16 = *value2 < *value3;
                                                        b14 = *value2 == *value3;
                                                        value2 = value2 + 1;
                                                        value3 = value3 + 1;
                                                      } while (b14);
                                                      b15 = (!b16 && !b14) < b16;
                                                      if ((!b16 && !b14) == b16) {
                                                        *(uint32_t *)(elem2 + ELEM_TYPE) = 0x51;
                                                        value2 = (uint8_t *)TPGetValue(tp,"value")
                                                        ;
                                                        if (value2 == (uint8_t *)0x0) {
                                                          return 0;
                                                        }
                                                        mem = 1;
                                                        mem2 = (int *)(elem2 + 0x18);
                                                      }
                                                      else {
                                                        mem = 7;
                                                        b14 = false;
                                                        value2 = stk_11c;
                                                        value3 = (uint8_t *)(int)&str_varset;
                                                        do {
                                                          if (mem == 0) break;
                                                          mem = mem + -1;
                                                          b15 = *value2 < *value3;
                                                          b14 = *value2 == *value3;
                                                          value2 = value2 + 1;
                                                          value3 = value3 + 1;
                                                        } while (b14);
                                                        b16 = (!b15 && !b14) < b15;
                                                        if ((!b15 && !b14) != b15) {
                                                          mem = 7;
                                                          b14 = false;
                                                          value2 = stk_11c;
                                                          value3 = (uint8_t *)(int)&str_varadd;
                                                          do {
                                                            b15 = b16;
                                                            if (mem == 0) break;
                                                            mem = mem + -1;
                                                            b16 = *value2 < *value3;
                                                            b14 = *value2 == *value3;
                                                            value2 = value2 + 1;
                                                            value3 = value3 + 1;
                                                            b15 = b16;
                                                          } while (b14);
                                                          b16 = (!b15 && !b14) < b15;
                                                          if ((!b15 && !b14) == b15)
                                                          goto L_080bd21b;
                                                          mem = 0xc;
                                                          b14 = false;
                                                          value2 = stk_11c;
                                                          value3 = (uint8_t *)"varrangeset";
                                                          do {
                                                            if (mem == 0) break;
                                                            mem = mem + -1;
                                                            b16 = *value2 < *value3;
                                                            b14 = *value2 == *value3;
                                                            value2 = value2 + 1;
                                                            value3 = value3 + 1;
                                                          } while (b14);
                                                          b15 = (!b16 && !b14) < b16;
                                                          if ((!b16 && !b14) == b16) {
                                                            *(uint32_t *)(elem2 + ELEM_TYPE) = 7;
                                                            value2 = (uint8_t *)TPGetValue(tp,
                                                  "value");
                                                  if (value2 == (uint8_t *)0x0) {
                                                    value2 = (uint8_t *)TPGetValue(tp,"fvalue");
                                                    if (value2 == (uint8_t *)0x0) {
                                                      sprintf((char *)(g + G_ERRMSG),
                                                              "VarRangeSet value not specified.");
                                                      ErrorExit();
                                                    }
                                                    mem = 1;
                                                  }
                                                  else {
                                                    mem = 0;
                                                  }
                                                  i10 = ItoP_TPConstI(tp,"first",
                                                                         (int *)(elem2 + 0x18),
                                                                         player,0);
                                                  if (i10 == 0) {
                                                    return 0;
                                                  }
                                                  i10 = ItoP_TPConstI(tp,"last",
                                                                         (int *)(elem2 + 0x24),
                                                                         player,((mem == 0) - 1 &
                                                                                 0xffffffec) + 0x3b)
                                                  ;
                                                  if (i10 == 0) {
                                                    return 0;
                                                  }
                                                  i10 = InfixToPostfix(value2,(int *)(elem2 +
                                                                                        0x30),
                                                                          player,(uint32_t *)0x0,
                                                                          (mem != 0) + 1);
                                                  if (i10 == 0) {
                                                    return 0;
                                                  }
                                                  mem2 = (int *)(elem2 + 0x3c);
                                                  goto L_080be8b2;
                                                  }
                                                  mem = 10;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"varrandom";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) == b15) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 6;
                                                    value2 = (uint8_t *)TPGetValue(tp,"v");
                                                    if (value2 == (uint8_t *)0x0) {
                                                      return 0;
                                                    }
                                                    mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                         0x24),
                                                                           player,(uint32_t *)0x0
                                                                           ,1);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    mem2 = (int *)(elem2 + 0x18);
                                                    ConstExpI(mem2,0);
                                                    ConstExpI((int *)(elem2 + 0x30),1000);
                                                    value2 = (uint8_t *)TPGetValue(tp,"range");
                                                    if (value2 == (uint8_t *)0x0) {
                                                      return 1;
                                                    }
                                                    value2 = SCtrlReadExpList(value2,"ii",player,
                                                                              &value4,mem2,
                                                                              (int *)(elem2 + 0x30
                                                                                     ));
                                                    if (*value4 != 0) {
                                                      return 0;
                                                    }
                                                    if (value2 == (uint8_t *)0x0) {
                                                      return 0;
                                                    }
                                                    if (value2 != (uint8_t *)0x1) {
                                                      return 1;
                                                    }
                                                    *(uint32_t *)(elem2 + 0x30) =
                                                         *(uint32_t *)(elem2 + 0x18);
                                                    *(uint32_t *)(elem2 + 0x34) =
                                                         *(uint32_t *)(elem2 + 0x1c);
                                                    *(uint32_t *)(elem2 + 0x38) =
                                                         *(uint32_t *)(elem2 + 0x20);
                                                    mem = 0;
                                                    goto L_080be8b2;
                                                  }
                                                  mem = 7;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)(int)&str_offset;
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b15 = (!b16 && !b14) < b16;
                                                  if ((!b16 && !b14) == b16) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x1c;
                                                    value2 = (uint8_t *)TPGetValue(tp,"x");
                                                    if (value2 != (uint8_t *)0x0) {
                                                      ConstExpI((int *)(elem2 + 0x18),1);
                                                      mem = InfixToPostfix(value2,(int *)(elem2 
                                                  + 0x3c),player,(uint32_t *)0x0,2);
                                                  if (mem == 0) {
                                                    return 0;
                                                  }
                                                  }
                                                  value2 = (uint8_t *)TPGetValue(tp,"y");
                                                  if (value2 == (uint8_t *)0x0) {
                                                    return 1;
                                                  }
                                                  ConstExpI((int *)(elem2 + 0x24),1);
                                                  mem = 2;
                                                  mem2 = (int *)(elem2 + 0x48);
                                                  goto L_080be815;
                                                  }
                                                  mem = 9;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)(int)&str_envshake;
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) == b15) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 200;
                                                    mem2 = (int *)ecalloc(1,0x40);
                                                    if (mem2 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    mem = SCtrlParseEnvShake(tp,player,
                                                                               mem2,&d_0827725f
                                                                              );
                                                    if (mem == 0) {
                                                      free(mem2);
                                                      strcat((char *)(g + G_ERRMSG),
                                                             "\nError parsing EnvShake");
                                                      return 0;
                                                    }
                                                    goto L_080be2cc;
                                                  }
                                                  mem = 0xd;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"fallenvshake";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b15 = (!b16 && !b14) < b16;
                                                  if ((!b16 && !b14) == b16) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0xc9;
                                                    return 1;
                                                  }
                                                  mem = 9;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"envcolor";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) == b15) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0xca;
                                                    ConstExpI((int *)(elem2 + 0x3c),0xff);
                                                    ConstExpI((int *)(elem2 + 0x48),0xff);
                                                    ConstExpI((int *)(elem2 + 0x54),0xff);
                                                    value2 = (uint8_t *)TPGetValue(tp,"value");
                                                    if (value2 != (uint8_t *)0x0) {
                                                      value2 = SCtrlReadExpList(value2,"iii",player
                                                                                ,&value4,
                                                                                (int *)(elem2 +
                                                                                       0x3c),
                                                                                (int *)(elem2 +
                                                                                       0x48),
                                                                                (int *)(elem2 +
                                                                                       0x54));
                                                      if (*value4 != 0) {
                                                        return 0;
                                                      }
                                                      if (value2 != (uint8_t *)0x3) {
                                                        return 0;
                                                      }
                                                    }
                                                    ConstExpI((int *)(elem2 + 0x24),1);
                                                    mem2 = (int *)(elem2 + 0x30);
                                                    ConstExpI(mem2,0);
                                                    value2 = (uint8_t *)TPGetValue(tp,"time");
                                                    mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                         0x24),
                                                                           player,(uint32_t *)0x0
                                                                           ,1);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    value2 = (uint8_t *)TPGetValue(tp,"under");
                                                    mem = 1;
                                                    goto L_080be815;
                                                  }
                                                  mem = 0xd;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"gamemakeanim";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b15 = (!b16 && !b14) < b16;
                                                  if ((!b16 && !b14) == b16) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0xcb;
                                                    ConstExpI((int *)(elem2 + 0x18),0);
                                                    ConstExpI((int *)(elem2 + 0x24),0);
                                                    ConstExpF((int *)(elem2 + 0x3c),0);
                                                    ConstExpF((int *)(elem2 + 0x48),0);
                                                    value2 = (uint8_t *)TPGetValue(tp,"value");
                                                    mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                         0x18),
                                                                           player,(uint32_t *)0x0
                                                                           ,1);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    value2 = (uint8_t *)TPGetValue(tp,"under");
                                                    mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                         0x24),
                                                                           player,(uint32_t *)0x0
                                                                           ,1);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    value2 = (uint8_t *)TPGetValue(tp,"pos");
                                                    if (value2 != (uint8_t *)0x0) {
                                                      value2 = SCtrlReadExpList(value2,"ff",player,
                                                                                &value4,
                                                                                (int *)(elem2 +
                                                                                       0x3c),
                                                                                (int *)(elem2 +
                                                                                       0x48));
                                                      if (*value4 != 0) {
                                                        return 0;
                                                      }
                                                      if (value2 == (uint8_t *)0x0) {
                                                        return 0;
                                                      }
                                                    }
                                                    value2 = (uint8_t *)TPGetValue(tp,"random");
                                                    mem = 1;
                                                    mem2 = (int *)(elem2 + 0x30);
                                                    goto L_080be815;
                                                  }
                                                  mem = 0xb;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)(int)&str_afterimage;
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) == b15) {
                                                    mem2 = (int *)ecalloc(1,0x118);
                                                    if (mem2 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0xd2;
                                                    mem = SCtrlParseAftImgParams
                                                                      (tp,player,mem2,
                                                                       &d_0827725f);
                                                    if (mem == 0) {
                                                      free(mem2);
                                                      strcat((char *)(g + G_ERRMSG),
                                                             "\nError parsing AfterImage");
                                                      return 0;
                                                    }
                                                    goto L_080be2cc;
                                                  }
                                                  mem = 0xf;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)(int)&str_afterimagetime;
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b15 = (!b16 && !b14) < b16;
                                                  if ((!b16 && !b14) == b16) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0xd3;
                                                    value2 = (uint8_t *)TPGetValue(tp,"time");
                                                    if (value2 == (uint8_t *)0x0) {
                                                      value2 = (uint8_t *)TPGetValue(tp,"value");
                                                      mem = 1;
                                                      mem2 = (int *)(elem2 + 0x18);
                                                    }
                                                    else {
                                                      mem = 1;
                                                      mem2 = (int *)(elem2 + 0x18);
                                                    }
                                                    goto L_080be815;
                                                  }
                                                  mem = 6;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)(int)&str_pause;
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) == b15) {
                                                    mem2 = (int *)ecalloc(1,0x30);
                                                    if (mem2 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0xd4;
                                                    b14 = SCtrlParsePause(tp,player,mem2
                                                                            );
                                                    if (ZEXT8(b14) == 0) {
                                                      free(mem2);
                                                      strcat((char *)(g + G_ERRMSG),
                                                             "\nError parsing Pause");
                                                      return 0;
                                                    }
L_080be390:
                                                    *(int **)(elem2 + 0x60) = mem2;
                                                    return 1;
                                                  }
                                                  mem = 0xb;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"superpause";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b15 = (!b16 && !b14) < b16;
                                                  if ((!b16 && !b14) == b16) {
                                                    mem2 = (int *)ecalloc(1,0xa4);
                                                    if (mem2 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0xd6;
                                                    b14 = SCtrlParseSuperPause
                                                                       (tp,player,mem2);
                                                    if (ZEXT8(b14) == 0) {
                                                      free(mem2);
                                                      strcat((char *)(g + G_ERRMSG),
                                                             "\nError parsing SuperPause");
                                                      return 0;
                                                    }
                                                    goto L_080be390;
                                                  }
                                                  mem = 9;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"makedust";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) == b15) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0xd7;
                                                    ConstExpI((int *)(elem2 + 0x30),3);
                                                    value2 = (uint8_t *)TPGetValue(tp,"pos");
                                                    if (value2 != (uint8_t *)0x0) {
                                                      value2 = SCtrlReadExpList(value2,"ii",player,
                                                                                &value4,
                                                                                (int *)(elem2 +
                                                                                       0x18),
                                                                                (int *)(elem2 +
                                                                                       0x24));
                                                      if (*value4 != 0) {
                                                        return 0;
                                                      }
                                                      if (value2 == (uint8_t *)0x0) {
                                                        return 0;
                                                      }
                                                    }
                                                    value2 = (uint8_t *)TPGetValue(tp,"pos2");
                                                    if (value2 != (uint8_t *)0x0) {
                                                      value2 = SCtrlReadExpList(value2,"ff",player,
                                                                                &value4,
                                                                                (int *)(elem2 +
                                                                                       0x3c),
                                                                                (int *)(elem2 +
                                                                                       0x48));
                                                      if (*value4 != 0) {
                                                        return 0;
                                                      }
                                                      if (value2 == (uint8_t *)0x0) {
                                                        return 0;
                                                      }
                                                      ConstExpF((int *)(elem2 + 0x54),0x3f800000);
                                                    }
                                                    value2 = (uint8_t *)TPGetValue(tp,"spacing");
                                                    mem = 1;
                                                    mem2 = (int *)(elem2 + 0x30);
                                                    goto L_080be815;
                                                  }
                                                  mem = 6;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = &str_palfx;
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b15 = (!b16 && !b14) < b16;
                                                  if ((!b16 && !b14) == b16) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0xd8;
                                                    mem2 = (int *)ecalloc(1,0xa0);
                                                    if (mem2 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    b14 = SCtrlParsePalFX(tp,player,
                                                                             (int)mem2,0);
                                                    if (ZEXT8(b14) == 0) {
                                                      return 0;
                                                    }
                                                    *mem2 = 0;
                                                    goto L_080be2cc;
                                                  }
                                                  mem = 8;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = &str_bgpalfx;
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) == b15) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0xd8;
                                                    mem2 = (int *)ecalloc(1,0xa0);
                                                    if (mem2 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    b14 = SCtrlParsePalFX(tp,player,
                                                                             (int)mem2,0);
                                                    if (ZEXT8(b14) == 0) {
                                                      return 0;
                                                    }
                                                    *mem2 = 1;
                                                    goto L_080be2cc;
                                                  }
                                                  mem = 9;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = &str_allpalfx;
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b15 = (!b16 && !b14) < b16;
                                                  if ((!b16 && !b14) == b16) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0xd8;
                                                    mem2 = (int *)ecalloc(1,0xa0);
                                                    if (mem2 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    b14 = SCtrlParsePalFX(tp,player,
                                                                             (int)mem2,0);
                                                    if (ZEXT8(b14) == 0) {
                                                      return 0;
                                                    }
                                                    *mem2 = 2;
                                                    goto L_080be2cc;
                                                  }
                                                  mem = 7;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)(int)&str_explod;
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) == b15) {
                                                    mem2 = (int *)ecalloc(1,0x168);
                                                    if (mem2 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0xdc;
                                                    mem = SCtrlParseExplod(tp,player,mem2
                                                                             ,0);
L_join_080be2c6:
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
L_080be2cc:
                                                    *(int **)(elem2 + 0x60) = mem2;
                                                    return 1;
                                                  }
                                                  mem = 0xd;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"removeexplod";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b15 = (!b16 && !b14) < b16;
                                                  if ((!b16 && !b14) == b16) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0xdd;
                                                    mem2 = (int *)(elem2 + 0x18);
                                                    ConstExpI(mem2,-1);
                                                    value2 = (uint8_t *)TPGetValue(tp,"id");
                                                    mem = 1;
                                                    goto L_080be815;
                                                  }
                                                  mem = 0xf;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)(int)&str_explodbindtime;
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) == b15) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0xde;
                                                    ConstExpI((int *)(elem2 + 0x18),-1);
                                                    mem2 = (int *)(elem2 + 0x24);
                                                    ConstExpI(mem2,1);
                                                    value2 = (uint8_t *)TPGetValue(tp,"id");
                                                    mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                         0x18),
                                                                           player,(uint32_t *)0x0
                                                                           ,1);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    value2 = (uint8_t *)TPGetValue(tp,"time");
                                                    if (value2 == (uint8_t *)0x0) {
                                                      value2 = (uint8_t *)TPGetValue(tp,"value");
                                                    }
                                                    mem = 1;
                                                    goto L_080be815;
                                                  }
                                                  mem = 0xd;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"modifyexplod";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b15 = (!b16 && !b14) < b16;
                                                  if ((!b16 && !b14) == b16) {
                                                    mem2 = (int *)ecalloc(1,0x168);
                                                    if (mem2 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0xdf;
                                                    mem = SCtrlParseExplod(tp,player,mem2
                                                                             ,1);
                                                    goto L_join_080be2c6;
                                                  }
                                                  mem = 0xe;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"forcefeedback";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) == b15) {
L_080bedbd:
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0;
                                                    return 1;
                                                  }
                                                  mem = 7;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)(int)&str_helper;
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b15 = (!b16 && !b14) < b16;
                                                  if ((!b16 && !b14) == b16) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 300;
                                                    mem2 = (int *)ecalloc(1,0x140);
                                                    if (mem2 == (int *)0x0) {
                                                      return 0;
                                                    }
                                                    b14 = SCtrlParseHelper(tp,player,
                                                                              (char *)mem2);
                                                    if (ZEXT8(b14) == 0) {
                                                      free(mem2);
                                                      strcat((char *)(g + G_ERRMSG),
                                                             "\nError parsing Helper");
                                                      return 0;
                                                    }
                                                    goto L_080be390;
                                                  }
                                                  mem = 0xc;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"destroyself";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) == b15) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x12d;
                                                    return 1;
                                                  }
                                                  mem = 0xd;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)(int)&str_parentvarset;
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b15 = (!b16 && !b14) < b16;
                                                  if ((!b16 && !b14) == b16) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x130;
                                                    value2 = (uint8_t *)TPGetValue(tp,"value");
                                                    if (value2 == (uint8_t *)0x0) {
                                                      value = (char *)TPAccessFirstLine(tp);
                                                      while (((mem = strimatchlen((int)value,
                                                                                    (int)&str_var,3),
                                                              mem == 0 &&
                                                              (mem = strimatchlen((int)value,
                                                                                    (int)&str_fvar,4),
                                                              mem == 0)) &&
                                                             (value != (char *)0x0))) {
                                                        value = (char *)TPAccessNextLine(tp);
                                                      }
                                                      if (value == (char *)0x0) {
                                                        return 0;
                                                      }
                                                      u6 = (uint32_t)(*value != 'v');
                                                      ConstExpI((int *)(elem2 + 0x30),u6);
                                                      pc13 = value + u6 + 3;
                                                      b1 = *(uint8_t *)(__ctype_b + 1 +
                                                                       value[u6 + 3] * 2);
                                                      while ((b1 & 0x20) != 0) {
                                                        pc13 = pc13 + 1;
                                                        b1 = *(uint8_t *)(__ctype_b + 1 +
                                                                         *pc13 * 2);
                                                      }
                                                      if (*pc13 != '(') {
                                                        return 0;
                                                      }
                                                      mem = InfixToPostfix((uint8_t *)(pc13 + 1),
                                                                             (int *)(elem2 + 0x24)
                                                                             ,player,&value4,1);
                                                      if (mem == 0) {
                                                        return 0;
                                                      }
                                                      if (*value4 != 0x29) {
                                                        return 0;
                                                      }
                                                      value2 = value4 + 1;
                                                      b1 = 0;
                                                      if (value4[1] != 0) {
                                                        if (value4[1] == 0x3d) {
                                                          b1 = 0x3d;
                                                        }
                                                        else {
                                                          do {
                                                            value2 = value2 + 1;
                                                            b1 = *value2;
                                                            if (b1 == 0) break;
                                                          } while (b1 != 0x3d);
                                                        }
                                                      }
                                                      if (b1 != 0x3d) {
                                                        return 0;
                                                      }
                                                      value2 = value2 + 1;
                                                      mem = u6 + 1;
                                                      mem2 = (int *)(elem2 + 0x18);
                                                    }
                                                    else {
                                                      value4 = (uint8_t *)TPGetValue(tp,"v");
                                                      if (value4 == (uint8_t *)0x0) {
                                                        value4 = (uint8_t *)TPGetValue(tp,"fv")
                                                        ;
                                                        if (value4 == (uint8_t *)0x0) {
                                                          return 1;
                                                        }
                                                        mem = InfixToPostfix(value4,
                                                                               (int *)(elem2 +
                                                                                      0x24),player,
                                                                               (uint32_t *)0x0,1);
                                                        if (mem == 0) {
                                                          return 0;
                                                        }
                                                        mem = InfixToPostfix(value2,(int *)(
                                                  elem2 + 0x18),player,(uint32_t *)0x0,2);
                                                  goto L_join_080be616;
                                                  }
                                                  mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                       0x18),player
                                                                         ,(uint32_t *)0x0,1);
                                                  value2 = value4;
L_join_080be7f4:
                                                  if (mem == 0) {
                                                    return 0;
                                                  }
                                                  mem = 1;
                                                  mem2 = (int *)(elem2 + 0x24);
                                                  value4 = value2;
                                                  }
                                                  goto L_080be815;
                                                  }
                                                  mem = 0xd;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)(int)&str_parentvaradd;
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) != b15) {
                                                    mem = 0xd;
                                                    b14 = false;
                                                    value2 = stk_11c;
                                                    value3 = (uint8_t *)(int)&str_bindtoparent;
                                                    do {
                                                      if (mem == 0) break;
                                                      mem = mem + -1;
                                                      b16 = *value2 < *value3;
                                                      b14 = *value2 == *value3;
                                                      value2 = value2 + 1;
                                                      value3 = value3 + 1;
                                                    } while (b14);
                                                    b15 = (!b16 && !b14) < b16;
                                                    if ((!b16 && !b14) == b16) {
                                                      *(uint32_t *)(elem2 + ELEM_TYPE) = 0x140;
                                                      ConstExpI((int *)(elem2 + 0x18),1);
                                                      value2 = (uint8_t *)TPGetValue(tp,"time");
                                                      mem = InfixToPostfix(value2,(int *)(elem2 
                                                  + 0x18),player,(uint32_t *)0x0,1);
                                                  if (mem == 0) {
                                                    return 0;
                                                  }
                                                  value2 = (uint8_t *)TPGetValue(tp,"facing");
                                                  mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                       0x24),player
                                                                         ,(uint32_t *)0x0,1);
                                                  if (mem == 0) {
                                                    return 0;
                                                  }
                                                  value2 = (uint8_t *)TPGetValue(tp,"pos");
                                                  if (value2 == (uint8_t *)0x0) {
                                                    return 1;
                                                  }
                                                  value2 = SCtrlReadExpList(value2,"fff",player,
                                                                            &value4,
                                                                            (int *)(elem2 + 0x3c),
                                                                            (int *)(elem2 + 0x48),
                                                                            (int *)(elem2 + 0x54))
                                                  ;
                                                  if (value2 == (uint8_t *)0x0) {
                                                    return 0;
                                                  }
                                                  b1 = *value4;
                                                  goto L_join_080beb19;
                                                  }
                                                  mem = 0xb;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)(int)&str_bindtoroot;
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b15 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b16 = (!b15 && !b14) < b15;
                                                  if ((!b15 && !b14) == b15) {
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) = 0x141;
                                                    ConstExpI((int *)(elem2 + 0x18),1);
                                                    value2 = (uint8_t *)TPGetValue(tp,"time");
                                                    mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                         0x18),
                                                                           player,(uint32_t *)0x0
                                                                           ,1);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    value2 = (uint8_t *)TPGetValue(tp,"facing");
                                                    mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                         0x24),
                                                                           player,(uint32_t *)0x0
                                                                           ,1);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    value2 = (uint8_t *)TPGetValue(tp,"pos");
                                                    if (value2 == (uint8_t *)0x0) {
                                                      return 1;
                                                    }
                                                    value2 = SCtrlReadExpList(value2,"fff",player,
                                                                              &value4,
                                                                              (int *)(elem2 + 0x3c
                                                                                     ),(int *)(
                                                  elem2 + 0x48),(int *)(elem2 + 0x54));
                                                  if (value2 == (uint8_t *)0x0) {
                                                    return 0;
                                                  }
                                                  b1 = *value4;
                                                  goto L_join_080beb19;
                                                  }
                                                  mem = 0x13;
                                                  b14 = false;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)"displaytoclipboard";
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  b15 = (!b16 && !b14) < b16;
                                                  if ((!b16 && !b14) == b16) {
L_080beb5d:
                                                    *(uint32_t *)(elem2 + ELEM_TYPE) =
                                                         (stk_11c[0] != 100) + 0x136;
                                                    value = TPGetValue(tp,"text");
                                                    if (value == (char *)0x0) {
                                                      fmt_args[0] = (void *)(stk_11c);
                                                      value = "Text not specified for %s.";
                                                    }
                                                    else {
                                                      if (*value != '\"') {
                                                        mem2 = g + G_ERRMSG;
                                                        value = "Message text not quote-delimited."
                                                        ;
                                                        goto L_080bede5;
                                                      }
                                                      c2 = value[1];
                                                      value2 = (uint8_t *)0x0;
                                                      s11 = 1;
                                                      c3 = '\0';
                                                      if ((c2 != '\0') &&
                                                         (c3 = '\"', c2 != '\"')) {
                                                        value2 = (uint8_t *)0x0;
                                                        do {
                                                          if (c2 == '%') {
                                                            if (value[s11 + 1] == '%') {
                                                              s11 = s11 + 1;
                                                              c2 = value[s11];
                                                            }
                                                            else {
                                                              value2 = value2 + 1;
                                                            }
                                                          }
                                                          if ((c2 == '\\') &&
                                                             (value[s11 + 1] == '\"')) {
                                                            s11 = s11 + 1;
                                                          }
                                                          s11 = s11 + 1;
                                                          c2 = value[s11];
                                                          c3 = c2;
                                                        } while ((c2 != '\0') && (c2 != '\"'))
                                                        ;
                                                      }
                                                      if (c3 == '\0') {
                                                        mem2 = g + G_ERRMSG;
                                                        value = "Message text not quote-delimited."
                                                        ;
                                                        goto L_080bede5;
                                                      }
                                                      if ((int)value2 < 6) {
                                                        ConstExpI((int *)(elem2 + 0x54),
                                                                  (int)value2);
                                                        mem = ecalloc(1,s11);
                                                        *(int *)(elem2 + 0x60) = mem;
                                                        if (mem == 0) {
                                                          return 0;
                                                        }
                                                        i9 = 1;
                                                        i10 = 0;
                                                        if (1 < (int)s11) {
L_080bec80:
                                                          c2 = value[i9];
                                                          if (c2 == '\\') {
                                                            i9 = i9 + 1;
                                                            c2 = value[i9];
                                                            if (c2 == 'n') {
                                                              *(uint8_t *)(i10 + mem) = 10;
                                                              goto L_080becd3;
                                                            }
                                                            if ('n' < c2) {
                                                              if (c2 == 't') {
                                                                *(uint8_t *)(i10 + mem) = 9;
                                                                goto L_080becd3;
                                                              }
                                                              goto L_080becd0;
                                                            }
                                                            if (c2 == '\0') {
                                                              mem2 = g + G_ERRMSG;
                                                              value = 
                                                  "Unterminated backslash escape sequence";
                                                  goto L_080bede5;
                                                  }
                                                  }
L_080becd0:
                                                  *(char *)(i10 + mem) = c2;
L_080becd3:
                                                  i10 = i10 + 1;
                                                  i9 = i9 + 1;
                                                  if ((int)s11 <= i9) goto L_080becd9;
                                                  goto L_080bec80;
                                                  }
L_080becd9:
                                                  *(uint8_t *)(i10 + mem) = 0;
                                                  value3 = (uint8_t *)TPGetValue(tp,"params");
                                                  if (value3 == (uint8_t *)0x0) {
                                                    return 1;
                                                  }
                                                  value3 = SCtrlReadExpList(value3,"nnnnn",player,
                                                                            &value4,
                                                                            (int *)(elem2 + 0x18),
                                                                            (int *)(elem2 + 0x24),
                                                                            (int *)(elem2 + 0x30),
                                                                            (int *)(elem2 + 0x3c),
                                                                            (int *)(elem2 + 0x48))
                                                  ;
                                                  if (value3 == (uint8_t *)0x0) {
                                                    return 0;
                                                  }
                                                  if (value3 != value2) {
                                                    return 0;
                                                  }
                                                  goto L_080bed65;
                                                  }
                                                  fmt_args[0] = (void *)(stk_11c);
                                                  value = "More than 5 parameters to %s.";
                                                  }
                                                  }
                                                  else {
                                                    mem = 0x12;
                                                    b14 = false;
                                                    value2 = stk_11c;
                                                    value3 = (uint8_t *)"appendtoclipboard";
                                                    do {
                                                      if (mem == 0) break;
                                                      mem = mem + -1;
                                                      b15 = *value2 < *value3;
                                                      b14 = *value2 == *value3;
                                                      value2 = value2 + 1;
                                                      value3 = value3 + 1;
                                                    } while (b14);
                                                    b16 = (!b15 && !b14) < b15;
                                                    if ((!b15 && !b14) == b15)
                                                    goto L_080beb5d;
                                                    mem = 0xf;
                                                    b14 = false;
                                                    value2 = stk_11c;
                                                    value3 = (uint8_t *)"clearclipboard";
                                                    do {
                                                      if (mem == 0) break;
                                                      mem = mem + -1;
                                                      b16 = *value2 < *value3;
                                                      b14 = *value2 == *value3;
                                                      value2 = value2 + 1;
                                                      value3 = value3 + 1;
                                                    } while (b14);
                                                    b15 = (!b16 && !b14) < b16;
                                                    if ((!b16 && !b14) == b16) {
                                                      *(uint32_t *)(elem2 + ELEM_TYPE) = 0x138;
                                                      return 1;
                                                    }
                                                    mem = 5;
                                                    b14 = false;
                                                    value2 = stk_11c;
                                                    value3 = (uint8_t *)(int)&str_null;
                                                    do {
                                                      if (mem == 0) break;
                                                      mem = mem + -1;
                                                      b15 = *value2 < *value3;
                                                      b14 = *value2 == *value3;
                                                      value2 = value2 + 1;
                                                      value3 = value3 + 1;
                                                    } while (b14);
                                                    if ((!b15 && !b14) == b15)
                                                    goto L_080bedbd;
                                                    fmt_args[0] = (void *)(stk_11c);
                                                    value = "Not a valid elem type: %s";
                                                  }
                                                  mem2 = g + G_ERRMSG;
L_080bede5:
                                                  sprintf((char *)mem2,value,fmt_args[0]);
                                                  return 0;
                                                  }
                                                  *(uint32_t *)(elem2 + ELEM_TYPE) = 0x131;
                                                  value2 = (uint8_t *)TPGetValue(tp,"value");
                                                  if (value2 == (uint8_t *)0x0) {
                                                    value = (char *)TPAccessFirstLine(tp);
                                                    while (((mem = strimatchlen((int)value,
                                                                                  (int)&str_var,3),
                                                            mem == 0 &&
                                                            (mem = strimatchlen((int)value,
                                                                                  (int)&str_fvar,4),
                                                            mem == 0)) && (value != (char *)0x0))
                                                          ) {
                                                      value = (char *)TPAccessNextLine(tp);
                                                    }
                                                    if (value == (char *)0x0) {
                                                      return 0;
                                                    }
                                                    u6 = (uint32_t)(*value != 'v');
                                                    ConstExpI((int *)(elem2 + 0x30),u6);
                                                    pc13 = value + u6 + 3;
                                                    b1 = *(uint8_t *)(__ctype_b + 1 +
                                                                     value[u6 + 3] * 2);
                                                    while ((b1 & 0x20) != 0) {
                                                      pc13 = pc13 + 1;
                                                      b1 = *(uint8_t *)(__ctype_b + 1 + *pc13 * 2
                                                                       );
                                                    }
                                                    if (*pc13 != '(') {
                                                      return 0;
                                                    }
                                                    mem = InfixToPostfix((uint8_t *)(pc13 + 1),
                                                                           (int *)(elem2 + 0x24),
                                                                           player,&value4,1);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    if (*value4 != 0x29) {
                                                      return 0;
                                                    }
                                                    value2 = value4 + 1;
                                                    b1 = 0;
                                                    if (value4[1] != 0) {
                                                      if (value4[1] == 0x3d) {
                                                        b1 = 0x3d;
                                                      }
                                                      else {
                                                        do {
                                                          value2 = value2 + 1;
                                                          b1 = *value2;
                                                          if (b1 == 0) break;
                                                        } while (b1 != 0x3d);
                                                      }
                                                    }
                                                    if (b1 != 0x3d) {
                                                      return 0;
                                                    }
                                                    value2 = value2 + 1;
                                                    mem = u6 + 1;
                                                    mem2 = (int *)(elem2 + 0x18);
                                                    goto L_080be815;
                                                  }
                                                  value4 = (uint8_t *)TPGetValue(tp,"v");
                                                  if (value4 != (uint8_t *)0x0) {
                                                    mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                         0x18),
                                                                           player,(uint32_t *)0x0
                                                                           ,1);
                                                    value2 = value4;
                                                    goto L_join_080be7f4;
                                                  }
                                                  value4 = (uint8_t *)TPGetValue(tp,"fv");
                                                  if (value4 == (uint8_t *)0x0) {
                                                    return 1;
                                                  }
                                                  mem = InfixToPostfix(value4,
                                                                         (int *)(elem2 + 0x24),
                                                                         player,(uint32_t *)0x0,1
                                                                        );
                                                  if (mem == 0) {
                                                    return 0;
                                                  }
                                                  mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                       0x18),player
                                                                         ,(uint32_t *)0x0,2);
L_join_080be616:
                                                  if (mem == 0) {
                                                    return 0;
                                                  }
                                                  goto L_080be8a5;
                                                  }
L_080bd21b:
                                                  b14 = true;
                                                  mem = 7;
                                                  value2 = stk_11c;
                                                  value3 = (uint8_t *)(int)&str_varset;
                                                  do {
                                                    if (mem == 0) break;
                                                    mem = mem + -1;
                                                    b16 = *value2 < *value3;
                                                    b14 = *value2 == *value3;
                                                    value2 = value2 + 1;
                                                    value3 = value3 + 1;
                                                  } while (b14);
                                                  *(uint32_t *)(elem2 + ELEM_TYPE) =
                                                       ((!b16 && !b14) != b16) + 4;
                                                  value2 = (uint8_t *)TPGetValue(tp,"value");
                                                  if (value2 == (uint8_t *)0x0) {
                                                    value = (char *)TPAccessFirstLine(tp);
                                                    while ((((mem = strimatchlen((int)value,
                                                                                   (int)&str_var,3),
                                                             mem == 0 &&
                                                             (mem = strimatchlen((int)value,
                                                                                   (int)&str_fvar,4),
                                                             mem == 0)) &&
                                                            (mem = strimatchlen((int)value,
                                                                                  (int)&str_sysvar_ae4d,6),
                                                            mem == 0)) &&
                                                           ((mem = strimatchlen((int)value,
                                                                                  (int)&str_sysfvar,7),
                                                            mem == 0 && (value != (char *)0x0))))
                                                          ) {
                                                      value = (char *)TPAccessNextLine(tp);
                                                    }
                                                    if (value == (char *)0x0) {
                                                      return 0;
                                                    }
                                                    i10 = 0;
                                                    if ((*value != 'v') &&
                                                       (i10 = 1, *value != 'f')) {
                                                      i10 = (value[3] != 'v') + 3;
                                                    }
                                                    pc13 = value + i10 + 3;
                                                    ConstExpI((int *)(elem2 + 0x30),i10);
                                                    b1 = *(uint8_t *)(__ctype_b + 1 +
                                                                     value[i10 + 3] * 2);
                                                    while ((b1 & 0x20) != 0) {
                                                      pc13 = pc13 + 1;
                                                      b1 = *(uint8_t *)(__ctype_b + 1 + *pc13 * 2
                                                                       );
                                                    }
                                                    if (*pc13 != '(') {
                                                      return 0;
                                                    }
                                                    mem = InfixToPostfix((uint8_t *)(pc13 + 1),
                                                                           (int *)(elem2 + 0x24),
                                                                           player,&value4,1);
                                                    if (mem == 0) {
                                                      return 0;
                                                    }
                                                    if (*value4 != 0x29) {
                                                      return 0;
                                                    }
                                                    value2 = value4 + 1;
                                                    b1 = 0;
                                                    if (value4[1] != 0) {
                                                      if (value4[1] == 0x3d) {
                                                        b1 = 0x3d;
                                                      }
                                                      else {
                                                        do {
                                                          value2 = value2 + 1;
                                                          b1 = *value2;
                                                          if (b1 == 0) break;
                                                        } while (b1 != 0x3d);
                                                      }
                                                    }
                                                    if (b1 != 0x3d) {
                                                      return 0;
                                                    }
                                                    if ((i10 == 1) || (mem = 1, i10 == 4)) {
                                                      mem = 2;
                                                    }
                                                    mem2 = (int *)(elem2 + 0x18);
                                                    value2 = value2 + 1;
                                                  }
                                                  else {
                                                    value4 = (uint8_t *)TPGetValue(tp,"v");
                                                    if (value4 == (uint8_t *)0x0) {
                                                      value4 = (uint8_t *)TPGetValue(tp,"fv");
                                                      if (value4 == (uint8_t *)0x0) {
                                                        return 1;
                                                      }
                                                      mem = InfixToPostfix(value4,
                                                                             (int *)(elem2 + 0x24)
                                                                             ,player,(uint32_t *)
                                                                                      0x0,1);
                                                      if (mem == 0) {
                                                        return 0;
                                                      }
                                                      mem = InfixToPostfix(value2,(int *)(elem2 
                                                  + 0x18),player,(uint32_t *)0x0,2);
                                                  goto L_join_080be616;
                                                  }
                                                  mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                       0x18),player
                                                                         ,(uint32_t *)0x0,1);
                                                  if (mem == 0) {
                                                    return 0;
                                                  }
                                                  mem = 1;
                                                  mem2 = (int *)(elem2 + 0x24);
                                                  value2 = value4;
                                                  }
                                                  }
                                                  }
                                                  }
                                                  goto L_080be815;
                                                  }
                                                  *(uint32_t *)(elem2 + ELEM_TYPE) = 0x46;
                                                  ConstExpI((int *)(elem2 + 0x18),1);
                                                  ConstExpI((int *)(elem2 + 0x30),-1);
                                                  ConstExpF((int *)(elem2 + 0x3c),-0x39001000);
                                                  ConstExpF((int *)(elem2 + 0x48),-0x39001000);
                                                  ConstExpF((int *)(elem2 + 0x54),0);
                                                  value2 = (uint8_t *)TPGetValue(tp,"time");
                                                  mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                       0x18),player
                                                                         ,(uint32_t *)0x0,1);
                                                  if (mem == 0) {
                                                    return 0;
                                                  }
                                                  value2 = (uint8_t *)TPGetValue(tp,"id");
                                                  mem = InfixToPostfix(value2,(int *)(elem2 +
                                                                                       0x30),player
                                                                         ,(uint32_t *)0x0,1);
                                                  if (mem == 0) {
                                                    return 0;
                                                  }
                                                  value2 = (uint8_t *)TPGetValue(tp,"pos");
                                                  SCtrlReadExpList(value2,"ff",player,&value4,
                                                                   (int *)(elem2 + 0x3c),
                                                                   (int *)(elem2 + 0x48));
                                                  }
L_join_080bb972:
                                                  if (value2 == (uint8_t *)0x0) {
                                                    return 1;
                                                  }
                                                  }
L_080bed65:
                                                  b1 = *value4;
L_join_080beb19:
                                                  if (b1 != 0) {
                                                    return 0;
                                                  }
                                                  return 1;
                                                  }
                                                  *(uint32_t *)(elem2 + ELEM_TYPE) = 0x3f;
                                                  value2 = (uint8_t *)TPGetValue(tp,"value");
                                                  mem = 2;
                                                  mem2 = (int *)(elem2 + 0x3c);
                                                  }
                                                  }
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
L_080be815:
  mem = InfixToPostfix(value2,mem2,player,(uint32_t *)0x0,mem);
L_080be81a:
  if (mem == 0) {
    return 0;
  }
  return 1;
}
#undef stk_128
#undef stk_124
#undef value4
#undef stk_11c

/* SCtrlParseElem @ 0x080bee10, 947 bytes
 *
 * Parses one state controller group: its "triggerall" and numbered
 * "trigger1", "trigger2"... lines (several lines per trigger number are
 * ANDed), "persistent" and "ignorehitpause". Then it parses the type
 * parameters (SCtrlParseElemType). "Need at least 1 trigger" when none is
 * given. Returns nonzero on success.
 *
 * Parameters:
 *   tp           int
 *   elems        int *
 *   arg3         uint32_t
 *   player       int
 *
 * Text keys read: "triggerall", "persistent", "ignorehitpause"
 * Globals read: errmsg
 * Calls: TPGroupReset, TPGetValue, TPGetValueNext, ArrayNew,
 *        InfixToPostfix, ArrayAdd, TPGetValueInt, SCtrlParseElemType
 * C library: memset, memcpy, sprintf, strcat
 * Called by: SCtrlParseState
 * Messages:
 *   "Need at least 1 trigger"
 *   ", %i"
 *   "\nError parsing "
 *   "\nError parsing triggerall"
 *
 * Elecbyte file: src/mugen/st-ctrl.c
 * Note: Locals live in `frame`, laid out as on the original stack (0xf0 bytes, 9
 *       variables), because their address is taken.
 */
bool SCtrlParseElem(int tp,int *elems,uint32_t arg3,int player)

{
  char *value;
  uint8_t *value2;
  int i3;
  int index;
  uint32_t stale_ECX;
  uint32_t stale_EDX;
  uint32_t u5;
  uint32_t stale_EDX_00;
  int i2;
  unsigned char frame[0xf0] __attribute__((aligned(16)));
#define stk_e8 (*(int *)(frame + 0x8))
#define stk_e4 (*(int *)(frame + 0xc))
#define stk_e0 (*(int *)(frame + 0x10))
#define stk_dc (*(char (*)[32])(frame + 0x14))
#define keyname (*(char (*)[32])(frame + 0x34))
#define expr (*(int (*)[4])(frame + 0x54))
#define array (*(uint32_t **)(frame + 0x64))
#define stk_88 (*(int *)(frame + 0x68))
#define stk_84 (*(uint32_t (*)[29])(frame + 0x6c))
  
  stk_e0 = 0;
  stk_e8 = 0;
  memset(&array,0,100);
  TPGroupReset(tp);
  value = TPGetValue(tp,"triggerall");
  if (value != (char *)0x0) {
    stk_e8 = 1;
    while (value = TPGetValueNext(tp,"triggerall"), value != (char *)0x0) {
      stk_e8 = stk_e8 + 1;
    }
  }
  memcpy(keyname,"trigger1",9);
  TPGroupReset(tp);
  index = 0;
  while (value = TPGetValue(tp,keyname), value != (char *)0x0) {
    do {
      stk_e0 = stk_e0 + 1;
      value = TPGetValueNext(tp,keyname);
    } while (value != (char *)0x0);
    sprintf(keyname,"trigger%i",index + 2,stale_ECX);
    index = index + 1;
  }
  if (stk_e0 == 0) {
    sprintf((char *)(g + G_ERRMSG),"Need at least 1 trigger",index,index);
  }
  else {
    array = ArrayNew(stk_e0 + stk_e8,0xc,0);
    if (array != (uint32_t *)0x0) {
      i2 = 0;
      stk_e4 = 0;
      stk_88 = index;
      TPGroupReset(tp);
      expr[0] = 0;
      expr[1] = 0;
      expr[2] = 0;
      if (0 < stk_e0) {
        u5 = stale_EDX;
        do {
          sprintf(keyname,"trigger%i",stk_e4 + 1,u5);
          value2 = (uint8_t *)TPGetValue(tp,keyname);
          index = 0;
          do {
            i3 = InfixToPostfix(value2,expr,player,(uint32_t *)0x0,0);
            if (i3 == 0) {
              value = stk_dc;
              sprintf(value,", %i",index + 1,0);
              strcat((char *)(g + G_ERRMSG),"\nError parsing ");
              strcat((char *)(g + G_ERRMSG),keyname);
              goto L_080bf182;
            }
            i2 = i2 + 1;
            ArrayAdd((int)array,expr,stk_e4,index);
            value2 = (uint8_t *)TPGetValueNext(tp,keyname);
            index = index + 1;
          } while (value2 != (uint8_t *)0x0);
          stk_e4 = stk_e4 + 1;
          u5 = stale_EDX_00;
        } while (i2 < stk_e0);
      }
      if (0 < stk_e8) {
        TPGroupReset(tp);
        value2 = (uint8_t *)TPGetValue(tp,"triggerall");
        if (value2 != (uint8_t *)0x0) {
          index = 0;
          do {
            i2 = InfixToPostfix(value2,expr,player,(uint32_t *)0x0,0);
            if (i2 == 0) {
              value = "\nError parsing triggerall";
L_080bf182:
              strcat((char *)(g + G_ERRMSG),value);
              return false;
            }
            ArrayAdd((int)array,expr,0xffffffff,index);
            value2 = (uint8_t *)TPGetValueNext(tp,"triggerall");
            index = index + 1;
          } while (value2 != (uint8_t *)0x0);
        }
      }
      stk_84[0] = 1;
      TPGetValueInt(tp,"persistent",stk_84);
      stk_84[1] = 0;
      TPGetValueInt(tp,"ignorehitpause",stk_84 + 1);
      index = SCtrlParseElemType(tp,(int)&array,player);
      if (index != 0) {
        index = ArrayAdd(*elems,&array,stk_84[2],arg3);
        return index != -1;
      }
    }
  }
  return false;
}
#undef stk_e8
#undef stk_e4
#undef stk_e0
#undef stk_dc
#undef keyname
#undef expr
#undef array
#undef stk_88
#undef stk_84

/* PlayerDoSCtrlApplyElem @ 0x080bf1d0, 185 bytes
 *
 * Executes one state controller whose triggers passed: PlayerSCtrlApplyElem,
 * plus bookkeeping for the AI (records commands and attack starts so the AI
 * can learn).
 *
 * Parameters:
 *   player       int *
 *   elem         int
 *   arg3         int *
 *
 * Player fields read: stateno, statetype, movetype, ctrl
 * Globals read: frame_count
 * Calls: PlayerSCtrlApplyElem, AICountCommands, AICopyCommands,
 *        PlayerAILearnMoveStart, PlayerAIMsgAttack
 * Called by: PlayerSCtrlUpdate, PlayerSCtrlUpdateSpec
 *
 * Elecbyte file: src/mugen/st-ctrl.c
 */
uint32_t PlayerDoSCtrlApplyElem(int *player,int elem,int *arg3)

{
  int i1;
  int i2;
  uint32_t u3;
  
  i2 = player[0x2fb];
  player[0xcfa] = player[PL_STATENO];
  player[0xcfb] = player[PL_STATETYPE];
  player[0xcfc] = player[PL_MOVETYPE];
  player[0xcfd] = player[PL_CTRL];
  i1 = PlayerSCtrlApplyElem(player,elem,arg3);
  if (i1 == 0) {
    u3 = 0;
  }
  else {
    if ((i2 == 0) && (player[0x2fb] == 0)) {
      i2 = AICountCommands(player + 0xcef);
      if (0 < i2) {
        AICopyCommands((int)(player + 0xce4),player + 0xcef);
        player[0xcee] = g[G_FRAME_COUNT];
        PlayerAILearnMoveStart((int)player);
        PlayerAIMsgAttack((int)player);
      }
    }
    u3 = 1;
  }
  return u3;
}

/* PlayerSCtrlApplyElem @ 0x080bf290, 17297 bytes
 *
 * Executes one state controller on a player. A large switch over the
 * controller type: evaluates the parameter expressions (EvalExpressionI/F)
 * and applies the effect to the player, its targets, helpers, explods,
 * projectiles, sounds or the screen. Run-time errors are reported as
 * warnings: "attempted change to negative anim", "No parent for
 * bindtoparent", ... Returns nonzero when the controller changed the
 * player's state (ChangeState, SelfState...), so the caller stops processing
 * the old state.
 *
 * Parameters:
 *   player       int *
 *   elem         int
 *   arg3         int *
 *
 * Player fields read: targets, facing, hitvel, teamside, anim, id,
 *                     ishelper
 * Player fields written: vel_x, vel_y, hitfall, attackmul, hitcount,
 *                        uniqhitcount, defencemul, statetype, movetype,
 *                        movecontact, standby, offset_x, offset_y, hitdef,
 *                        hitdef_damage, width, sprpriority, pos_x, pos_y,
 *                        ctrl
 * Globals read: rules_super_targetdefencemul, errmsg, stageinfo_autoturn
 * Calls: ArrayScanFirst, EvalExpressionI, PlayerTakeDamage, ArrayScanNext,
 *        PlayerCalcDraw, Warn, EvalExpressionF, AnimPerArrayAdd,
 *        AnimPerArraySetNo, PlayerTurnAround, ArrayDelete,
 *        SCtrlInitHitOverride, ComboAdd, SCtrlInitEnvShake, HelperMake,
 *        ExplodAdd, AnimGetLooptime, RequestNewAftImg,
 *        SCtrlInitAftImgParams, SCtrlInitPause, PalGrpMakeFlag,
 *        PalGrpOrFlag, PalGrpXorFlag, PlayerSparkCreate, ...
 * C library: random, makecol, memcpy, vsprintf, sprintf
 * Called by: PlayerDoSCtrlApplyElem
 * Messages:
 *   "attempted change to negative anim"
 *   "No parent for bindtoparent"
 *   "No root for bindtoroot"
 *   "no parent for parentvarset"
 *   "stopped illegal channel number %i"
 *   "attemted to pan illegal channel number %i"
 *
 * Elecbyte file: src/mugen/st-ctrl.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: rewrote 2 PalGrpFlag by-value loads
 * Note: 28 data addresses refer to the data image (data/mugen_data.S).
 * Note: 1 partial-variable block copies written as memcpy
 * Note: 11 accesses to parts of a variable are written as sized accesses.
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: 3 exact-text site patches (see SITE_PATCHES in
 *       tools/build_source_tree.py)
 * Note: 1 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 29 int-to-float conversions keep full precision (long double), as the
 *       x87 fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x10d0 bytes,
 *       10 variables), because their address is taken.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t PlayerSCtrlApplyElem(int *player,int elem,int *arg3)

{
  PalGrpFlag a;
  PalGrpFlag b;
  bool b1;
  int value2;
  uint32_t stale_var;
  int value3;
  int value4;
  int value5;
  long l6;
  uint32_t value6;
  int *item;
  uint32_t looptime;
  uint32_t stale_ECX;
  uint32_t stale_ECX_00;
  uint32_t stale_ECX_01;
  double *pd10;
  double *pd11;
  int *pi12;
  int *saved_ESI;
  uint32_t *pu13;
  bool b14;
  uint16_t entry_FPUControlWord;
  float80 value7;
  char *fmt;
  uint32_t u17;
  unsigned char frame[0x10d0] __attribute__((aligned(16)));
#define value8 (*(int *)(frame + 0xc))
#define stk_10c0 (*(float *)(frame + 0x10))
#define stk_10bc (*(uint8_t (*)[40])(frame + 0x14))
#define stk_10ac (*(uint32_t (*)[8])(frame + 0x24))
#define fmt2 (*(char (*)[4096])(frame + 0x44))
#define stk_8c (*(PalGrpFlag *)(frame + 0x1044))
#define stk_6c (*(PalGrpFlag *)(frame + 0x1064))
#define stk_4c (*(PalGrpFlag (*)[2])(frame + 0x1084))
#define stk_24 (*(int *)(frame + 0x10ac))
#define stk_20 (*(uint32_t *)(frame + 0x10b0))
  
  value8 = 0;
  value3 = *arg3;
  item = (int *)arg3[3];
  value2 = arg3[2];
  pi12 = (int *)arg3[4];
  value4 = *(int *)(elem + ELEM_TYPE);
  if (value4 == 0x4a) {
    item = (int *)ArrayScanFirst(player[PL_TARGETS]);
    while (item != (int *)0x0) {
      value3 = *item;
      value2 = EvalExpressionI((int)player,elem + 0x54,1);
      if ((*(int *)(value3 + 0xe10) == 0) && ((value2 == -1 || (value2 == *(int *)(value3 + 0x1064)))))
      {
        value2 = EvalExpressionI((int)player,elem + 0x30,0);
        value4 = EvalExpressionI((int)player,elem + 0x24,0);
        value5 = EvalExpressionI((int)player,elem + 0x18,1);
        PlayerTakeDamage(value3,-value5,value4,value2);
      }
      item = (int *)ArrayScanNext(player[PL_TARGETS]);
    }
    return 0;
  }
  if (0x4a < value4) {
    if (value4 == 0xcb) {
      PlayerCalcDraw((int)player);
      value8 = EvalExpressionI((int)player,elem + 0x18,1);
      if (value8 < 0) {
        value8 = 0;
        Warn((int)player,(int)&str_made_negative_gameanim_b133);
      }
      value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
      value3 = (int)X87_FIST32((float80)player[PL_FACING] * value7 + BITS_I2F(player[0x4d5]) + (float)g[0x7311]);
      stk_24 = value3;
      value7 = EvalExpressionF(player,(int *)(elem + 0x48));
      stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
      value2 = (int)X87_FIST32((float)g[0x7312] + BITS_I2F(player[0x4d6]) + value7);
      stk_24 = value2;
      value4 = EvalExpressionI((int)player,elem + 0x30,1);
      if (value4 < 1) {
        if (value4 < 0) {
          Warn((int)player,(int)&str_negative_random_param_for_ga_b680);
        }
      }
      else {
        l6 = random();
        value3 = value3 + (l6 % value4 - (value4 >> 1)) * player[PL_FACING];
        l6 = random();
        value2 = value2 + (l6 % value4 - (value4 >> 1));
      }
      value6 = AnimPerArrayAdd((int *)g[0x413c],g[0x4148],g[0x4147],0,value8,value3,value2,
                              (uint32_t)(player[PL_FACING] != 1),0xffffffff);
      value8 = EvalExpressionI((int)player,elem + 0x24,0);
      if (value6 == 0xffffffff) {
        return 0;
      }
      AnimPerArraySetNo((int *)g[0x413c],value6,(value8 != 0) + 1);
      return 0;
    }
    if (value4 < 0xcc) {
      if (value4 == 0x67) {
        if (BITS_I2F(player[0x41e]) != -32760.0) {
          player[PL_VEL_X] = BITS_F2I(int, ((float80)player[PL_FACING] * BITS_I2F(player[0x41e])));
        }
        if (BITS_I2F(player[0x41f]) == -32760.0) {
          return 0;
        }
        player[PL_VEL_Y] = player[0x41f];
        return 0;
      }
      if (value4 < 0x68) {
        if (value4 == 0x50) {
          value3 = EvalExpressionI((int)player,elem + 0x18,1);
          player[0x4b3] = value3;
          return 0;
        }
        if (value4 < 0x51) {
          if (value4 == 0x4c) {
            item = (int *)ArrayScanFirst(player[PL_TARGETS]);
            while (item != (int *)0x0) {
              value3 = *item;
              value2 = EvalExpressionI((int)player,elem + 0x30,1);
              if ((*(int *)(value3 + 0xe10) == 0) &&
                 ((value2 == -1 || (value2 == *(int *)(value3 + 0x1064))))) {
                value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
                if (value7 != -32760.0) {
                  *(float *)(value3 + 0x1b4) =
                       (float80)*(int *)(value3 + 400) * value7 + *(float *)(value3 + 0x1b4);
                }
                value7 = EvalExpressionF(player,(int *)(elem + 0x48));
                if (value7 != -32760.0) {
                  *(float *)(value3 + 0x1b8) = *(float *)(value3 + 0x1b8) + value7;
                }
              }
              item = (int *)ArrayScanNext(player[PL_TARGETS]);
            }
            return 0;
          }
          if (value4 < 0x4c) {
            item = (int *)ArrayScanFirst(player[PL_TARGETS]);
            while (item != (int *)0x0) {
              value3 = *item;
              value2 = EvalExpressionI((int)player,elem + 0x30,1);
              if ((*(int *)(value3 + 0xe10) == 0) &&
                 ((value2 == -1 || (value2 == *(int *)(value3 + 0x1064))))) {
                value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
                if (value7 != -32760.0) {
                  *(float *)(value3 + 0x1b4) = (float80)*(int *)(value3 + 400) * value7;
                }
                value7 = EvalExpressionF(player,(int *)(elem + 0x48));
                if (value7 != -32760.0) {
                  *(float *)(value3 + 0x1b8) = value7;
                }
              }
              item = (int *)ArrayScanNext(player[PL_TARGETS]);
            }
            return 0;
          }
          if (value4 == 0x4d) {
            item = (int *)ArrayScanFirst(player[PL_TARGETS]);
            while (item != (int *)0x0) {
              value3 = EvalExpressionI((int)player,elem + 0x18,1);
              if (((0 < value3) && (value2 = *item, player[PL_FACING] != *(int *)(value2 + 400))) ||
                 ((value3 < 0 && (value2 = *item, player[PL_FACING] == *(int *)(value2 + 400))))) {
                PlayerTurnAround(value2);
              }
              item = (int *)ArrayScanNext(player[PL_TARGETS]);
            }
            return 0;
          }
          if (value4 == 0x4e) {
            b1 = false;
            item = (int *)ArrayScanFirst(player[PL_TARGETS]);
            while (item != (int *)0x0) {
              value3 = EvalExpressionI((int)player,elem + 0x18,1);
              value2 = EvalExpressionI((int)player,elem + 0x24,1);
              if ((value3 != *(int *)(*item + 0x1064)) || (b1)) {
                ArrayDelete(player[PL_TARGETS],*(int *)(player[PL_TARGETS] + 0x1c));
              }
              else if (value2 != 0) {
                b1 = true;
              }
              item = (int *)ArrayScanNext(player[PL_TARGETS]);
            }
            return 0;
          }
        }
        else {
          if (value4 == 100) {
            value3 = EvalExpressionI((int)player,elem + 0x18,0);
            if (value3 != -1) {
              player[PL_HITFALL] = value3;
            }
            value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
            if (value7 != -32760.0) {
              player[0x41e] = BITS_F2I(int, value7);
            }
            value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
            if (value7 == -32760.0) {
              return 0;
            }
            player[0x41f] = BITS_F2I(int, value7);
            return 0;
          }
          if (value4 < 0x65) {
            if (value4 == 0x51) {
              value3 = EvalExpressionI((int)player,elem + 0x18,1);
              player[0x7c] = (uint32_t)(value3 != 0);
              return 0;
            }
          }
          else {
            if (value4 == 0x65) {
              value3 = EvalExpressionI((int)player,elem + 0x18,0);
              if (value3 != 0) {
                player[PL_VEL_X] = BITS_F2I(int, ((float80)player[0x403] + BITS_I2F(player[PL_HITVEL])));
              }
              value3 = EvalExpressionI((int)player,elem + 0x24,0);
              if (value3 == 0) {
                return 0;
              }
              player[PL_VEL_Y] = BITS_F2I(int, ((float80)player[0x404] + BITS_I2F(player[0x417])));
              return 0;
            }
            if (value4 == 0x66) {
              PlayerTakeDamage((int)player,player[0x41d],1,1);
              player[0x41d] = 0;
              return 0;
            }
          }
        }
      }
      else {
        if (value4 == 0x78) {
          value6 = EvalExpressionI((int)player,elem + 0x18,1);
          if (7 < value6) {
            value6 = 0;
            Warn((int)player,(int)&str_illegal_override_slot_0_assu_b600);
          }
          SCtrlInitHitOverride
                    (*(uint32_t **)(elem + 0x60),player + value6 * 5 + 0x42a,(int)player);
          return 0;
        }
        if (value4 < 0x79) {
          if (value4 == 0x69) {
            value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
            player[PL_ATTACKMUL] = BITS_F2I(int, ((float80)player[0x16] * value7 * ((float)0.01f)));
            return 0;
          }
          if (value4 < 0x69) {
            value3 = EvalExpressionI((int)player,elem + 0x18,1);
            player[0x4e6] = player[0x4e6] + value3;
            player[PL_HITCOUNT] = player[PL_HITCOUNT] + value3;
            player[PL_UNIQHITCOUNT] = player[PL_UNIQHITCOUNT] + value3;
            ComboAdd(player[PL_TEAMSIDE],value3);
            return 0;
          }
          if (value4 == 0x6a) {
            value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
            player[PL_DEFENCEMUL] = BITS_F2I(int, ((value7 * 100.0) / (float80)player[0x1c]));
            return 0;
          }
          if (value4 == 0x6e) {
            value3 = EvalExpressionI((int)player,elem + 0x18,0);
            if (value3 != -1) {
              player[PL_STATETYPE] = value3;
            }
            value3 = EvalExpressionI((int)player,elem + 0x24,0);
            if (value3 != -1) {
              player[PL_MOVETYPE] = value3;
            }
            value3 = EvalExpressionI((int)player,elem + 0x30,0);
            if (value3 == -1) {
              return 0;
            }
            player[0x382] = value3;
            return 0;
          }
        }
        else {
          if (value4 == 200) {
            SCtrlInitEnvShake(*(int **)(elem + 0x60),g + 0x7317,player);
            return 0;
          }
          if (value4 < 0xc9) {
            if (value4 == 0x82) {
              player[PL_MOVECONTACT] = 0;
              return 0;
            }
            if (value4 == 0x96) {
              value3 = EvalExpressionI((int)player,elem + 0x18,0);
              if (value3 != -1) {
                value2 = EvalExpressionI((int)player,elem + 0x3c,0);
                if (value2 == 0) {
                  *(uint8_t *)((int)g + value3 + 0x1d38c) = 1;
                }
                else {
                  *(uint8_t *)(value3 + 0x204 + (int)player) = 1;
                }
              }
              value3 = EvalExpressionI((int)player,elem + 0x24,0);
              if (value3 != -1) {
                value2 = EvalExpressionI((int)player,elem + 0x48,0);
                if (value2 == 0) {
                  *(uint8_t *)((int)g + value3 + 0x1d38c) = 1;
                }
                else {
                  *(uint8_t *)(value3 + 0x204 + (int)player) = 1;
                }
              }
              value3 = EvalExpressionI((int)player,elem + 0x30,0);
              if (value3 == -1) {
                return 0;
              }
              value2 = EvalExpressionI((int)player,elem + 0x54,0);
              if (value2 == 0) {
                *(uint8_t *)((int)g + value3 + 0x1d38c) = 1;
                return 0;
              }
              *(uint8_t *)(value3 + 0x204 + (int)player) = 1;
              return 0;
            }
          }
          else {
            if (value4 == 0xc9) {
              if (player[0x425] < 1) {
                return 0;
              }
              item = player + 0x424;
              pi12 = g + 0x7317;
              for (value3 = 6; value3 != 0; value3 = value3 + -1) {
                *pi12 = *item;
                item = item + 1;
                pi12 = pi12 + 1;
              }
              player[0x425] = 0;
              return 0;
            }
            if (value4 == 0xca) {
              value3 = EvalExpressionI((int)player,elem + 0x3c,1);
              value2 = EvalExpressionI((int)player,elem + 0x48,1);
              value8 = EvalExpressionI((int)player,elem + 0x54,1);
              value3 = makecol(value3,value2,value8);
              g[0x4145] = value3;
              value3 = EvalExpressionI((int)player,elem + 0x24,1);
              item = g;
              g[0x4146] = value3;
              if (value3 != -1) {
                item[0x4146] = value3 + 1;
              }
              if (g[0x4146] < -1) {
                Warn((int)player,(int)&str_set_illegal_envcolortime_b11a);
                g[0x4146] = 1;
              }
              value3 = EvalExpressionI((int)player,elem + 0x30,1);
              g[0x4144] = (uint32_t)(value3 != 0);
              return 0;
            }
          }
        }
      }
      goto L_080c35f1;
    }
    if (value4 == 300) {
      HelperMake(player,*(char **)(elem + 0x60),arg3);
      return 0;
    }
    if (value4 < 0x12d) {
      if (value4 == 0xd7) {
        value3 = EvalExpressionI((int)player,elem + 0x30,1);
        if (value3 < 1) {
          value3 = 1;
          Warn((int)player,(int)&str_makedust_spacing_0_b19d);
        }
        if (g[0x7514] % value3 != 0) {
          return 0;
        }
        PlayerCalcDraw((int)player);
        value3 = EvalExpressionI((int)player,elem + 0x18,1);
        l6 = random();
        value3 = (int)X87_FIST32(((float)(l6 % 3) +
                           (float)(value3 * player[PL_FACING]) + BITS_I2F(player[0x4d5]) + (float)g[0x7311]) -
                           1.0);
        stk_24 = value3;
        value2 = EvalExpressionI((int)player,elem + 0x24,1);
        l6 = random();
        stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
        value2 = (int)X87_FIST32(((float)(l6 % 3) +
                           (float)g[0x7312] + (float80)value2 + BITS_I2F(player[0x4d6])) - 1.0);
        stk_24 = value2;
        value8 = ExplodAdd((uint32_t *)g[0x52be],0x78,(int *)g[0x4148],g[0x4147]);
        if (value8 != -1) {
          value4 = *(int *)g[0x52be] + value8 * 0xe4;
          *(float *)(value4 + 0x14) = (float80)value3;
          *(float *)(value4 + 0x18) = (float80)value2;
          *(uint32_t *)(value4 + 0x6c) = 1;
          looptime = AnimGetLooptime(*(uint32_t **)(value4 + 0x80));
          value3 = *(int *)(value4 + 0x80);
          *(uint32_t *)(value4 + 0x40) = looptime;
          item = g;
          *(uint32_t *)(value3 + 0x34) = 10;
          *(int *)(value3 + 0x30) = item[0x413d];
        }
        value7 = EvalExpressionF(player,(int *)(elem + 0x54));
        if (value7 == 0.0) {
          return 0;
        }
        value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
        l6 = random();
        value3 = (int)X87_FIST32(((float)(l6 % 3) +
                           (float80)player[PL_FACING] * value7 + BITS_I2F(player[0x4d5]) + (float)g[0x7311]) -
                           1.0);
        stk_24 = value3;
        value7 = EvalExpressionF(player,(int *)(elem + 0x48));
        l6 = random();
        stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
        value2 = (int)X87_FIST32(((float)(l6 % 3) + (float)g[0x7312] + BITS_I2F(player[0x4d6]) + value7) -
                           1.0);
        stk_24 = value2;
        value8 = ExplodAdd((uint32_t *)g[0x52be],0x78,(int *)g[0x4148],g[0x4147]);
        if (value8 == -1) {
          return 0;
        }
        value4 = *(int *)g[0x52be] + value8 * 0xe4;
        *(float *)(value4 + 0x14) = (float80)value3;
        *(float *)(value4 + 0x18) = (float80)value2;
        *(uint32_t *)(value4 + 0x6c) = 1;
        looptime = AnimGetLooptime(*(uint32_t **)(value4 + 0x80));
        value3 = *(int *)(value4 + 0x80);
        *(uint32_t *)(value4 + 0x40) = looptime;
        item = g;
        *(uint32_t *)(value3 + 0x34) = 10;
        *(int *)(value3 + 0x30) = item[0x413d];
        return 0;
      }
      if (value4 < 0xd8) {
        if (value4 == 0xd3) {
          if (player[0x4e5] == 0) {
            return 0;
          }
          *(uint32_t *)(player[0x4e5] + 0x14) = 0;
          value3 = EvalExpressionI((int)player,elem + 0x18,1);
          *(int *)(player[0x4e5] + 0x1c) = value3;
          if (-2 < value3) {
            return 0;
          }
          Warn((int)player,(int)&str_set_illegal_afterimagetime_b14a);
          *(uint32_t *)(player[0x4e5] + 0x1c) = 1;
          return 0;
        }
        if (value4 < 0xd4) {
          if (value4 == 0xd2) {
            value3 = player[0x4e5];
            if (value3 == 0) {
              value3 = RequestNewAftImg(g[0x413f]);
              player[0x4e5] = value3;
            }
            if (value3 == 0) {
              return 0;
            }
            SCtrlInitAftImgParams(*(int *)(elem + 0x60),player[0x4e5],player[PL_ANIM],player);
            return 0;
          }
        }
        else {
          if (value4 == 0xd4) {
            SCtrlInitPause(*(int *)(elem + 0x60),0,(int)player);
            return 0;
          }
          if (value4 == 0xd6) {
            value3 = *(int *)(elem + 0x60);
            SCtrlInitPause(value3,1,(int)player);
            value2 = EvalExpressionI((int)player,value3 + 0x58,1);
            if (value2 == 0) {
              g[0x7502] = 0;
            }
            else {
              PalGrpMakeFlag(stk_4c,0xffffffff,1);
              item = g;
              g[0x74fd] = stk_4c[0].w[0];
              item[0x74fe] = stk_4c[0].w[1];
              item[0x74ff] = stk_4c[0].w[2];
              item[0x7500] = stk_4c[0].w[3];
              item[0x7501] = stk_4c[0].w[4];
              PalGrpMakeFlag(&stk_8c,0xffffffff,3);
              b.w[1] = stk_8c.w[1];
              b.w[0] = stk_8c.w[0];
              b.w[2] = stk_8c.w[2];
              b.w[3] = stk_8c.w[3];
              b.w[4] = stk_8c.w[4];
              PalGrpOrFlag(&stk_6c,*(PalGrpFlag *)(g + 0x74fd),b);
              item = g;
              g[0x74fd] = stk_6c.w[0];
              item[0x74fe] = stk_6c.w[1];
              item[0x74ff] = stk_6c.w[2];
              item[0x7500] = stk_6c.w[3];
              item[0x7501] = stk_6c.w[4];
              a.w[4] = stk_6c.w[4];
              memcpy((char *)&a.w + 0, (item + 0x74fd), 16);
              PalGrpXorFlag(&stk_8c,a,*(PalGrpFlag *)(player + 0x972));
              item = g;
              g[0x74fd] = stk_8c.w[0];
              item[0x74fe] = stk_8c.w[1];
              item[0x74ff] = stk_8c.w[2];
              item[0x7500] = stk_8c.w[3];
              item[0x7501] = stk_8c.w[4];
              item[0x7502] = 1;
            }
            if ((player[0x78] < 0) || (g[0x7503] < player[0x78])) {
              Warn((int)player,(int)&str_set_illegal_supermovetime_b165);
              player[0x78] = 0;
            }
            value2 = EvalExpressionI((int)player,value3 + 0x34,1);
            if (value2 < -1) {
              value2 = -1;
              Warn((int)player,(int)&str_negative_spark_animno_ignore_b17f);
            }
            if (value2 != -1) {
              value7 = EvalExpressionF(player,(int *)(value3 + 0x40));
              value4 = (int)X87_FIST32((float80)player[PL_FACING] * (value7 - (float80)player[PL_OFFSET_X]) *
                                 BITS_I2F(player[0x4d2]) + BITS_I2F(player[0x4d5]) + (float)g[0x7311]);
              stk_24 = value4;
              value7 = EvalExpressionF(player,(int *)(value3 + 0x4c));
              stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
              stk_24 = (int)X87_FIST32((value7 - (float80)player[PL_OFFSET_Y]) * BITS_I2F(player[0x4d2]) +
                                    BITS_I2F(player[0x4d6]) + (float)g[0x7312]);
              PlayerSparkCreate(player,value2,value4,stk_24,(uint32_t)(*(int *)(value3 + 0x30) == 0),
                                (uint32_t)(player[PL_FACING] != 1),0);
            }
            value7 = EvalExpressionF(player,(int *)(value3 + 100));
            if (value7 < 0.0) {
              Warn((int)player,(int)&str_negative_p2defmul_for_superp_b6c0);
              value7 = 0.0;
            }
            if (value7 == 0.0) {
              value7 = BITS_I2F(g[G_RULES_SUPER_TARGETDEFENCEMUL]);
            }
            if (value7 != 1.0) {
              item = (int *)ArrayScanFirst(player[PL_TARGETS]);
              while (item != (int *)0x0) {
                value2 = *item;
                if (*(int *)(value2 + 0xe10) == 0) {
                  *(float *)(value2 + 0x18c) = *(float *)(value2 + 0x18c) / value7;
                }
                item = (int *)ArrayScanNext(player[PL_TARGETS]);
              }
            }
            value2 = EvalExpressionI((int)player,value3 + 0x70,1);
            PlayerPowerSet(arg3[1],value2 + **(int **)(arg3[1] + 0x170));
            value2 = EvalExpressionI((int)player,value3 + 0x7c,0);
            if ((value2 != 0) && (player[0x3fe] < g[0x7503])) {
              player[0x3fe] = g[0x7503];
            }
            value2 = EvalExpressionI((int)player,value3 + 0x8c,1);
            value4 = EvalExpressionI((int)player,value3 + 0x98,1);
            if (*(int *)(value3 + 0x88) == 0) {
              value3 = *(int *)(*player + 0x11d0);
              item = *(int **)(*player + 0x11d4);
              value7 = BITS_I2F(player[0x4d5]);
            }
            else {
              value3 = 0;
              item = (int *)g[0x4156];
              value7 = BITS_I2F(player[0x4d5]);
            }
            stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
            stk_24 = (int)X87_FIST32(value7);
            GameSndPlayIDPos(-1,stk_24,item,value2,value4,value3);
            return 0;
          }
        }
      }
      else {
        if (value4 == 0xdd) {
          value3 = EvalExpressionI((int)player,elem + 0x18,1);
          if (value3 < -1) {
            value3 = -1;
            Warn((int)player,(int)&str_removal_of_illegal_explod_id_b1b3);
          }
          ExplodRemoveID((uint32_t *)g[0x52be],player[PL_ID],value3);
          return 0;
        }
        if (value4 < 0xde) {
          if (value4 == 0xd8) {
            SCtrlInitPalFX(*(int **)(elem + 0x60),player + 0x977,(int)player);
            return 0;
          }
          if (value4 == 0xdc) {
            ExplodMakeFromInfo(player,*(int *)(elem + 0x60),arg3);
            return 0;
          }
        }
        else {
          if (value4 == 0xde) {
            value3 = EvalExpressionI((int)player,elem + 0x18,1);
            value2 = EvalExpressionI((int)player,elem + 0x24,1);
            if (value3 < -1) {
              value3 = -1;
              Warn((int)player,(int)&str_illegal_id_to_explodbindtime_b1d0);
            }
            if (value2 < -1) {
              value2 = -1;
              Warn((int)player,(int)&str_illegal_explodbindtime_b1ed);
            }
            ExplodBindChange((uint32_t *)g[0x52be],player[PL_ID],value3,value2);
            return 0;
          }
          if (value4 == 0xdf) {
            ExplodModifyFromInfo(player,*(int *)(elem + 0x60),arg3);
            return 0;
          }
        }
      }
      goto L_080c35f1;
    }
    if (0x137 < value4) {
      if (0x141 < value4) {
        if (value4 == 0x2743) {
          if (value2 == 0) {
            return 1;
          }
          value3 = EvalExpressionI((int)player,elem + 0x18,1);
          if (-1 < value3) {
            PlayerChangeState((int)player,value3);
          }
          value3 = EvalExpressionI((int)player,elem + 0x24,1);
          if (*(int *)(value2 + 400) != player[PL_FACING]) {
            PlayerTurnAround(value2);
          }
          if (-1 < value3) {
            PlayerChangeState(value2,value3);
            *(uint32_t *)(value2 + 0x3460) = 0;
            return 1;
          }
          fmt = "attempted change to negative anim";
          goto L_080c3484;
        }
        if (value4 == 0x2744) {
          player[PL_STANDBY] = 1;
          return 1;
        }
        goto L_080c35f1;
      }
      if (value4 < 0x140) {
        if (value4 == 0x138) {
          ClipboardClear((uint32_t *)player[0xd17]);
          return 0;
        }
        goto L_080c35f1;
      }
      if (player[PL_ISHELPER] != 1) {
        return 0;
      }
      if (value4 == 0x140) {
        pi12 = item;
        if (item == (int *)0x0) {
          fmt = "No parent for bindtoparent";
L_080c3484:
          Warn((int)player,(int)fmt);
          return 0;
        }
      }
      else if (pi12 == (int *)0x0) {
        fmt = "No root for bindtoroot";
        goto L_080c3484;
      }
      value3 = EvalExpressionI((int)player,elem + 0x18,1);
      player[0xd0c] = value3;
      if (value3 < -1) {
        player[0xd0c] = 1;
        Warn((int)player,(int)&str_illegal_helper_bindtime_b287);
      }
      value3 = EvalExpressionI((int)player,elem + 0x24,1);
      player[0xd11] = value3;
      if (value3 < 0) {
        if (value3 == -1) goto L_080c3558;
        player[0xd11] = -1;
      }
      else {
        if ((value3 < 1) || (value3 == 1)) goto L_080c3558;
        player[0xd11] = 1;
      }
      Warn((int)player,(int)&str_bind_s_facing_param_not_1_or_b700);
L_080c3558:
      value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
      player[0xd12] = BITS_F2I(int, value7);
      value7 = EvalExpressionF(player,(int *)(elem + 0x48));
      player[0xd13] = BITS_F2I(int, value7);
      value7 = EvalExpressionF(player,(int *)(elem + 0x54));
      player[0xd14] = BITS_F2I(int, value7);
      player[0xd0d] = (int)(pi12 + 0x67);
      player[0xd0e] = (int)(pi12 + 0x68);
      player[0xd0f] = (int)(pi12 + 0x69);
      player[0xd15] = (int)pi12;
      player[0xd10] = (int)(pi12 + 100);
      return 0;
    }
    if (0x135 < value4) {
      value3 = *(int *)(elem + 0x5c);
      if (value3 != 0) {
        saved_ESI = &value8;
        value2 = EvalExpression(player,(int *)(elem + 0x18),saved_ESI,(int *)&stk_10c0);
        if (value2 == 2) {
          pd10 = (double *)(stk_10bc + 8);
          *(double *)stk_10bc = (double)stk_10c0;
        }
        else {
          pd10 = (double *)(stk_10bc + 4);
          (*(uint32_t *)((char *)&stk_10bc + 0)) = value8;
        }
        if (value3 != 1) {
          value2 = EvalExpression(player,(int *)(elem + 0x24),saved_ESI,(int *)&stk_10c0);
          if (value2 == 2) {
            pd11 = pd10 + 1;
            *pd10 = (double)stk_10c0;
          }
          else {
            pd11 = (double *)((int)pd10 + 4);
            *(int *)pd10 = value8;
          }
          if (value3 != 2) {
            value2 = EvalExpression(player,(int *)(elem + 0x30),saved_ESI,(int *)&stk_10c0);
            if (value2 == 2) {
              pd10 = pd11 + 1;
              *pd11 = (double)stk_10c0;
            }
            else {
              pd10 = (double *)((int)pd11 + 4);
              *(int *)pd11 = value8;
            }
            if (value3 != 3) {
              value2 = EvalExpression(player,(int *)(elem + 0x3c),saved_ESI,(int *)&stk_10c0);
              if (value2 == 2) {
                pd11 = pd10 + 1;
                *pd10 = (double)stk_10c0;
              }
              else {
                pd11 = (double *)((int)pd10 + 4);
                *(int *)pd10 = value8;
              }
              if (value3 != 4) {
                value3 = EvalExpression(player,(int *)(elem + 0x48),saved_ESI,(int *)&stk_10c0);
                if (value3 == 2) {
                  *pd11 = (double)stk_10c0;
                }
                else {
                  *(int *)pd11 = value8;
                }
              }
            }
          }
        }
      }
      vsprintf(fmt2,*(char **)(elem + 0x60),(va_list)stk_10bc);
      if (*(int *)(elem + ELEM_TYPE) == 0x137) {
        ClipboardAppend((int *)player[0xd17],fmt2,saved_ESI,saved_ESI);
        return 0;
      }
      ClipboardPrint((int *)player[0xd17],fmt2,stale_ECX_01,stale_ECX_01);
      return 0;
    }
    if (value4 == 0x130) {
      if (player[PL_ISHELPER] != 1) {
        return 0;
      }
      if (item == (int *)0x0) {
        fmt = "no parent for parentvarset";
        goto L_080c3484;
      }
      value3 = EvalExpressionI((int)player,elem + 0x30,0);
      value2 = EvalExpressionI((int)player,elem + 0x24,1);
      if (-1 < value2) {
        if (value3 == 0) {
          if (0x3b < value2) goto L_080c32c5;
        }
        else if (0x27 < value2) goto L_080c32c5;
        if (value3 != 0) {
          value7 = EvalExpressionF(player,(int *)(elem + 0x18));
          item[value2 + 0x3cc] = BITS_F2I(int, value7);
          return 0;
        }
        value3 = EvalExpressionI((int)player,elem + 0x18,1);
        item[value2 + 0x390] = value3;
        return 0;
      }
L_080c32c5:
      Warn((int)player,(int)&str_set_parentvar_out_of_range_b21f);
      return 0;
    }
    if (value4 < 0x131) {
      if (value4 == 0x12d) {
        HelperDestroy((int)player);
        return 0;
      }
      goto L_080c35f1;
    }
    if (value4 != 0x131) goto L_080c35f1;
    if (player[PL_ISHELPER] != 1) {
      return 0;
    }
    if (item == (int *)0x0) {
      Warn((int)player,(int)&str_no_parent_for_parentvaradd_b23a);
      return 0;
    }
    value3 = EvalExpressionI((int)player,elem + 0x30,0);
    value2 = EvalExpressionI((int)player,elem + 0x24,1);
    if (value2 < 0) {
L_080c33ba:
      Warn((int)player,(int)&str_set_parentvar_out_of_range_b21f);
      return 0;
    }
    if (value3 == 0) {
      if (0x3b < value2) goto L_080c33ba;
    }
    else if (0x27 < value2) goto L_080c33ba;
    if (value3 == 0) {
      value3 = EvalExpressionI((int)player,elem + 0x18,1);
      item[value2 + 0x390] = item[value2 + 0x390] + value3;
      return 0;
    }
    value7 = EvalExpressionF(player,(int *)(elem + 0x18));
    value3 = value2 * 4 + 0xf20;
    item = item + 4;
    goto L_080c33fe;
  }
  if (value4 == 0x1c) {
    value3 = EvalExpressionI((int)player,elem + 0x18,0);
    if (value3 != 0) {
      value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
      stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
      stk_24 = (int)X87_FIST32(value7);
      player[PL_OFFSET_X] = stk_24;
    }
    value3 = EvalExpressionI((int)player,elem + 0x24,0);
    if (value3 == 0) {
      return 0;
    }
    value7 = EvalExpressionF(player,(int *)(elem + 0x48));
    player[PL_OFFSET_Y] = (int)X87_FIST32(value7);
    return 0;
  }
  if (0x1c < value4) {
    if (value4 == 0x32) {
      value3 = EvalExpressionI((int)player,elem + 0x18,1);
      player[0x79] = (uint32_t)(value3 != 0);
      value3 = EvalExpressionI((int)player,elem + 0x24,1);
      player[0x7a] = (uint32_t)(value3 != 0);
      value3 = EvalExpressionI((int)player,elem + 0x30,1);
      player[0x7b] = (uint32_t)(value3 != 0);
      return 0;
    }
    if (value4 < 0x33) {
      if (value4 == 0x23) {
        value6 = EvalExpressionI((int)player,elem + 0x18,1);
        u17 = value6 + 1;
        if (u17 < 0x21) {
          value3 = PlayerSndID((int)player,value6);
          SndIDStop(value3);
          return 0;
        }
        fmt = "stopped illegal channel number %i";
L_080c001f:
        VWarn((int)player,fmt,value6,u17);
        return 0;
      }
      if (value4 < 0x24) {
        if (value4 == 0x20) {
          value3 = EvalExpressionI((int)player,elem + 0x24,1);
          value2 = EvalExpressionI((int)player,elem + 0x18,1);
          if (value3 < 0) {
            value3 = 0;
            Warn((int)player,(int)&str_changed_to_negative_animelem_b08c);
          }
          if (value2 < 0) {
            value2 = 0;
            Warn((int)player,(int)&str_attempted_change_to_negative_b480);
          }
          if (value3 == 0) {
            PlayerSelfAnim(player,value2);
            return 0;
          }
          PlayerSelfAnimElem(player,value2,value3);
          return 0;
        }
        if (value4 < 0x21) {
          if (value4 == 0x1e) {
            value3 = EvalExpressionI((int)player,elem + 0x30,0);
            if (value3 == 0) {
              value3 = EvalExpressionI((int)player,elem + 0x18,0);
              player[0x3ff] = value3;
              value3 = EvalExpressionI((int)player,elem + 0x24,0);
              player[0x401] = value3;
              return 0;
            }
            value3 = EvalExpressionI((int)player,elem + 0x18,0);
            player[0x400] = value3;
            value3 = EvalExpressionI((int)player,elem + 0x24,0);
            player[0x402] = value3;
            return 0;
          }
        }
        else {
          if (value4 == 0x21) {
            value3 = player[0x4f0];
            if (value3 == 0) {
              item = (int *)player[PL_ANIM];
              value3 = *(int *)(*player + 0x11cc);
            }
            else {
              item = (int *)player[PL_ANIM];
            }
            *item = value3;
            value3 = EvalExpressionI((int)player,elem + 0x24,1);
            value2 = EvalExpressionI((int)player,elem + 0x18,1);
            if (value3 < 0) {
              value3 = 0;
              Warn((int)player,(int)&str_changed_to_negative_animelem_b08c);
            }
            if (value2 < 0) {
              value2 = 0;
              Warn((int)player,(int)&str_attempted_change_to_negative_b480);
            }
            if (value3 == 0) {
              PlayerChangeAnim(player,value2);
              return 0;
            }
            PlayerChangeAnimElem(player,value2,value3);
            return 0;
          }
          if (value4 == 0x22) {
            SCtrlDoPlaySndInfo(player,*(int *)(elem + 0x60));
            return 0;
          }
        }
      }
      else {
        if (value4 < 0x27) {
          if (0x24 < value4) {
            value3 = player[0x463];
            value2 = player[0x4b3];
            SCtrlInitHitDef(*(uint32_t **)(elem + 0x60),(int)(player + PL_HITDEF),player);
            player[PL_HITDEF] = 1;
            if (*(int *)(elem + ELEM_TYPE) == 0x26) {
              player[0x457] = 0;
            }
            player[0x463] = value3;
            value4 = player[PL_HITDEF_DAMAGE];
            value3 = (int)X87_FIST32((float80)value4 * BITS_I2F(player[PL_ATTACKMUL]) + 0.5);
            player[PL_HITDEF_DAMAGE] = value3;
            if ((0 < value4) && (value3 == 0)) {
              player[PL_HITDEF_DAMAGE] = 1;
            }
            if (player[0x4b3] == -1) {
              player[0x4b3] = value2;
            }
            item = g;
            player[0x45a] = g[0x74e1];
            item[0x74e1] = item[0x74e1] + 1;
            return 0;
          }
          value6 = EvalExpressionI((int)player,elem + 0x18,1);
          if (value6 < 0x20) {
            value3 = PlayerSndID((int)player,value6);
            if (value3 == -1) {
              return 0;
            }
            value3 = SndIDGetChannel(value3);
            if (value3 == -1) {
              return 0;
            }
            value4 = EvalExpressionI((int)player,elem + 0x24,1);
            value2 = player[PL_FACING];
            value5 = EvalExpressionI((int)player,elem + 0x30,1);
            if (value5 == 0) {
              stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
              value2 = (int)X87_FIST32((BITS_I2F(player[PL_POS_X]) - (float)g[0x7311]) + (float)(value4 * value2));
              stk_24 = value2;
            }
            else {
              value2 = value4 * value2 + 0xa0;
            }
            value2 = ScrPositionToPan(value2);
            SndVoiceSetPan(value3,value2);
            return 0;
          }
          fmt = "attemted to pan illegal channel number %i";
          u17 = value6;
          goto L_080c001f;
        }
        if (value4 == 0x27) {
          pu13 = (uint32_t *)0x0;
          item = player;
          if (pi12 != (int *)0x0) {
            item = pi12;
          }
          value3 = SCtrlInitProjectile(*(int *)(elem + 0x60),player,value3,item);
          if (value3 != -1) {
            pu13 = (uint32_t *)
                      (value3 * *(int *)(*(int *)item[0x87] + 4) +
                      *(int *)(*(int *)item[0x87] + 0x14));
          }
          if (pu13 == (uint32_t *)0x0) {
            return 0;
          }
          PlayerAISctrlProjectile((int)player,pu13);
          value2 = pu13[0x34];
          value3 = (int)X87_FIST32((float80)value2 * BITS_I2F(player[PL_ATTACKMUL]) + 0.5);
          pu13[0x34] = value3;
          if (value2 < 1) {
            return 0;
          }
          if (value3 != 0) {
            return 0;
          }
          pu13[0x34] = 1;
          return 0;
        }
        if (value4 == 0x28) {
          value3 = EvalExpressionI((int)player,elem + 0x18,1);
          player[PL_WIDTH] = value3;
          value3 = EvalExpressionI((int)player,elem + 0x24,1);
          player[0x7e] = value3;
          value3 = EvalExpressionI((int)player,elem + 0x30,1);
          player[0x7f] = value3;
          value3 = EvalExpressionI((int)player,elem + 0x3c,1);
          player[0x80] = value3;
          return 0;
        }
      }
    }
    else {
      if (value4 == 0x3f) {
        value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
        player[0x4df] = BITS_F2I(int, (BITS_I2F(player[0x4df]) * value7));
        return 0;
      }
      if (value4 < 0x40) {
        if (value4 == 0x3c) {
          player[0x4e0] = 1;
          value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
          if (value7 != -32760.0) {
            player[0x4df] = BITS_F2I(int, value7);
          }
          value7 = EvalExpressionF(player,(int *)(elem + 0x48));
          player[0x4d3] = BITS_F2I(int, (BITS_I2F(player[0x4d3]) * value7));
          value7 = EvalExpressionF(player,(int *)(elem + 0x54));
          player[0x4d4] = BITS_F2I(int, (BITS_I2F(player[0x4d4]) * value7));
          return 0;
        }
        if (value4 < 0x3d) {
          if (value4 == 0x33) {
            value3 = EvalExpressionI((int)player,elem + 0x18,1);
            player[PL_SPRPRIORITY] = value3;
            return 0;
          }
        }
        else {
          if (value4 == 0x3d) {
            value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
            player[0x4df] = BITS_F2I(int, value7);
            return 0;
          }
          if (value4 == 0x3e) {
            value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
            player[0x4df] = BITS_F2I(int, (BITS_I2F(player[0x4df]) + value7));
            return 0;
          }
        }
      }
      else {
        if (value4 == 0x47) {
          item = (int *)ArrayScanFirst(player[PL_TARGETS]);
          value3 = EvalExpressionI((int)player,elem + 0x30,1);
          if (item != (int *)0x0) {
            value2 = *item;
            value4 = *(int *)(value2 + 0xe10);
            while (((value4 != 0 || ((value3 != -1 && (value3 != *(int *)(value2 + 0x1064))))) &&
                   (item = (int *)ArrayScanNext(player[PL_TARGETS]), item != (int *)0x0))) {
              value2 = *item;
              value4 = *(int *)(value2 + 0xe10);
            }
          }
          if (item == (int *)0x0) {
            return 0;
          }
          value3 = *item;
          value4 = 0;
          value2 = 0;
          value5 = EvalExpressionI((int)player,elem + 0x24,0);
          if (value5 == 1) {
            value2 = *(int *)(value3 + 0xa8);
            value4 = *(int *)(value3 + 0xac);
          }
          else {
            value5 = EvalExpressionI((int)player,elem + 0x24,0);
            if (value5 == 2) {
              value2 = *(int *)(value3 + 0xa0);
              value4 = *(int *)(value3 + 0xa4);
            }
          }
          value5 = EvalExpressionI((int)player,elem + 0x18,1);
          item[6] = value5;
          if (value5 < -1) {
            Warn((int)player,(int)&str_set_illegal_target_bindtime_b0fe);
            item[6] = 1;
          }
          value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
          if (value7 != -32760.0) {
            value5 = *(int *)(value3 + 400);
            player[PL_POS_X] = BITS_F2I(int, (((float80)value2 + value7) * (float80)value5 + *(float *)(value3 + 0x19c)))
            ;
            stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
            stk_24 = (int)X87_FIST32((float80)player[PL_FACING] * -((float80)value2 + value7) * (float80)value5);
            item[3] = stk_24;
          }
          value7 = EvalExpressionF(player,(int *)(elem + 0x48));
          if (value7 == -32760.0) {
            return 0;
          }
          player[PL_POS_Y] = BITS_F2I(int, (*(float *)(value3 + 0x1a0) + (float80)value4 + value7));
          item[4] = (int)X87_FIST32(-((float80)value4 + value7));
          return 0;
        }
        if (value4 < 0x48) {
          if (value4 == 0x41) {
            value3 = EvalExpressionI((int)player,elem + 0x18,1);
            player[0x4e2] = value3;
            value3 = EvalExpressionI((int)player,elem + 0x24,1);
            player[0x4e3] = value3;
            if (value3 < 0) {
              player[0x4e3] = 0;
            }
            if (0x100 < player[0x4e3]) {
              player[0x4e3] = 0x100;
            }
            value3 = EvalExpressionI((int)player,elem + 0x30,1);
            player[0x4e4] = value3;
            if (value3 < 0) {
              player[0x4e4] = 0;
            }
            if (player[0x4e4] < 0x101) {
              return 0;
            }
            player[0x4e4] = 0x100;
            return 0;
          }
          if (value4 == 0x46) {
            item = (int *)ArrayScanFirst(player[PL_TARGETS]);
            while (item != (int *)0x0) {
              value3 = EvalExpressionI((int)player,elem + 0x30,1);
              if ((*(int *)(*item + 0xe10) == 0) &&
                 ((value3 == -1 || (value3 == *(int *)(*item + 0x1064))))) {
                value3 = EvalExpressionI((int)player,elem + 0x18,1);
                item[6] = value3;
                if (value3 < -1) {
                  Warn((int)player,(int)&str_set_illegal_target_bindtime_b0fe);
                  item[6] = 1;
                }
                value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
                if (value7 != -32760.0) {
                  stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
                  stk_24 = (int)X87_FIST32(value7);
                  item[3] = stk_24;
                }
                value7 = EvalExpressionF(player,(int *)(elem + 0x48));
                if (value7 != -32760.0) {
                  stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
                  stk_24 = (int)X87_FIST32(value7);
                  item[4] = stk_24;
                }
              }
              item = (int *)ArrayScanNext(player[PL_TARGETS]);
            }
            return 0;
          }
        }
        else {
          if (value4 == 0x48) {
            item = (int *)ArrayScanFirst(player[PL_TARGETS]);
            while (item != (int *)0x0) {
              value3 = *item;
              value2 = EvalExpressionI((int)player,elem + 0x30,1);
              if ((*(int *)(value3 + 0xe10) == 0) &&
                 ((value2 == -1 || (value2 == *(int *)(value3 + 0x1064))))) {
                *(int *)(value3 + 0xbec) = player[0x2fa];
                *(int *)(value3 + 0xbf0) = player[2];
                *(int *)(value3 + 0x964) = player[0x259];
                if (player[0x2fb] != 0) {
                  *(int *)(value3 + 0xbec) = player[0x2fb];
                  *(int *)(value3 + 0xbf0) = player[0x2fc];
                }
                value2 = player[0x4f0];
                if (value2 == 0) {
                  value2 = *(int *)player[PL_ANIM];
                }
                *(int *)(value3 + 0x13c0) = value2;
                value2 = EvalExpressionI((int)player,elem + 0x18,1);
                if (value2 < 0) {
                  value2 = 0;
                  Warn((int)player,(int)&str_attempted_targetstate_to_neg_b640);
                }
                PlayerChangeState(value3,value2);
              }
              item = (int *)ArrayScanNext(player[PL_TARGETS]);
            }
            return 0;
          }
          if (value4 == 0x49) {
            item = (int *)ArrayScanFirst(player[PL_TARGETS]);
            while (item != (int *)0x0) {
              value2 = EvalExpressionI((int)player,elem + 0x18,1);
              value3 = *item;
              value4 = EvalExpressionI((int)player,elem + 0x30,1);
              if ((*(int *)(value3 + 0xe10) == 0) &&
                 ((value4 == -1 || (value4 == *(int *)(value3 + 0x1064))))) {
                PlayerPowerSet(value3,value2 + **(int **)(value3 + 0x170));
              }
              item = (int *)ArrayScanNext(player[PL_TARGETS]);
            }
            return 0;
          }
        }
      }
    }
L_080c35f1:
    sprintf((char *)(g + G_ERRMSG),"PlayerSCtrlApplyElem not recognised",item,item);
    ErrorExit();
    return 0;
  }
  if (value4 == 0xb) {
    value3 = EvalExpressionI((int)player,elem + 0x30,0);
    value2 = EvalExpressionI((int)player,elem + 0x24,0);
    value4 = EvalExpressionI((int)player,elem + 0x18,1);
    PlayerTakeDamage((int)player,-value4,value2,value3);
    return 0;
  }
  if (0xb < value4) {
    if (value4 == 0x16) {
      value3 = EvalExpressionI((int)player,elem + 0x18,0);
      if (value3 != 0) {
        value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
        player[PL_POS_X] = BITS_F2I(int, ((float80)player[PL_FACING] * value7 + BITS_I2F(player[PL_POS_X])));
      }
      value3 = EvalExpressionI((int)player,elem + 0x24,0);
      if (value3 == 0) {
        return 0;
      }
      value7 = EvalExpressionF(player,(int *)(elem + 0x48));
      player[PL_POS_Y] = BITS_F2I(int, (BITS_I2F(player[PL_POS_Y]) + value7));
      return 0;
    }
    if (value4 < 0x17) {
      if (value4 == 0xd) {
        value3 = EvalExpressionI((int)player,elem + 0x18,1);
        PlayerPowerSet(arg3[1],value3 + **(int **)(arg3[1] + 0x170));
        return 0;
      }
      if (value4 < 0xd) {
        value6 = EvalExpressionI((int)player,elem + 0x18,1);
        PlayerPowerSet(arg3[1],value6);
        return 0;
      }
      if (value4 == 0x14) {
        value3 = EvalExpressionI((int)player,elem + 0x18,1);
        player[PL_CTRL] = (uint32_t)(value3 != 0);
        return 0;
      }
      if (value4 == 0x15) {
        value3 = EvalExpressionI((int)player,elem + 0x18,0);
        if (value3 != 0) {
          value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
          player[PL_POS_X] = BITS_F2I(int, (BITS_I2F(g[0x730f]) + value7 + 160.0));
        }
        value3 = EvalExpressionI((int)player,elem + 0x24,0);
        if (value3 == 0) {
          return 0;
        }
        value7 = EvalExpressionF(player,(int *)(elem + 0x48));
        player[PL_POS_Y] = BITS_F2I(int, value7);
        return 0;
      }
    }
    else {
      if (value4 == 0x19) {
        value3 = EvalExpressionI((int)player,elem + 0x18,0);
        if (value3 != 0) {
          value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
          player[PL_VEL_X] = BITS_F2I(int, ((float80)player[PL_FACING] * value7 + BITS_I2F(player[PL_VEL_X])));
        }
        value3 = EvalExpressionI((int)player,elem + 0x24,0);
        if (value3 == 0) {
          return 0;
        }
        value7 = EvalExpressionF(player,(int *)(elem + 0x48));
        player[PL_VEL_Y] = BITS_F2I(int, (BITS_I2F(player[PL_VEL_Y]) + value7));
        return 0;
      }
      if (value4 < 0x1a) {
        if (value4 == 0x17) {
          value3 = EvalExpressionI((int)player,elem + 0x18,1);
          player[0x388] = (uint32_t)(value3 != 0);
          return 0;
        }
        if (value4 == 0x18) {
          value3 = EvalExpressionI((int)player,elem + 0x18,0);
          if (value3 != 0) {
            value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
            player[PL_VEL_X] = BITS_F2I(int, ((float80)player[PL_FACING] * value7));
          }
          value3 = EvalExpressionI((int)player,elem + 0x24,0);
          if (value3 == 0) {
            return 0;
          }
          value7 = EvalExpressionF(player,(int *)(elem + 0x48));
          player[PL_VEL_Y] = BITS_F2I(int, value7);
          return 0;
        }
      }
      else {
        if (value4 == 0x1a) {
          value3 = EvalExpressionI((int)player,elem + 0x18,0);
          if (value3 != 0) {
            value7 = EvalExpressionF(player,(int *)(elem + 0x3c));
            player[PL_VEL_X] = BITS_F2I(int, (BITS_I2F(player[PL_VEL_X]) * value7));
          }
          value3 = EvalExpressionI((int)player,elem + 0x24,0);
          if (value3 == 0) {
            return 0;
          }
          value7 = EvalExpressionF(player,(int *)(elem + 0x48));
          player[PL_VEL_Y] = BITS_F2I(int, (BITS_I2F(player[PL_VEL_Y]) * value7));
          return 0;
        }
        if (value4 == 0x1b) {
          player[PL_VEL_Y] = BITS_F2I(int, (BITS_I2F(player[PL_VEL_Y]) + BITS_I2F(player[0x4c])));
          return 0;
        }
      }
    }
    goto L_080c35f1;
  }
  if (value4 == 4) {
    value3 = EvalExpressionI((int)player,elem + 0x30,0);
    value6 = EvalExpressionI((int)player,elem + 0x24,1);
    if (value3 < 2) {
      if (-1 < (int)value6) {
        if (value3 == 0) {
          if ((int)value6 < 0x3c) goto L_080bfeb5;
        }
        else if ((int)value6 < 0x28) {
L_080bfeb5:
          if (value3 == 1) {
            value7 = EvalExpressionF(player,(int *)(elem + 0x18));
            player[value6 + PL_FVAR] = BITS_F2I(int, value7);
            return 0;
          }
          if (value3 < 2) {
            if (value3 != 0) {
              return 0;
            }
            value3 = EvalExpressionI((int)player,elem + 0x18,1);
            player[value6 + PL_VAR] = value3;
            return 0;
          }
          if (value3 == 3) {
            value3 = EvalExpressionI((int)player,elem + 0x18,1);
            player[value6 + PL_SYSVAR] = value3;
            return 0;
          }
          if (value3 != 4) {
            return 0;
          }
          value7 = EvalExpressionF(player,(int *)(elem + 0x18));
          player[value6 + 0x3f9] = BITS_F2I(int, value7);
          return 0;
        }
      }
      fmt = "set var out of range (%i)";
L_080c02dc:
      VWarn((int)player,fmt,value6,value2);
      return 0;
    }
    if (value6 < 5) goto L_080bfeb5;
    fmt = "set sysvar out of range (%i)";
    looptime = stale_ECX;
    goto L_080c0001;
  }
  if (value4 < 5) {
    if (value4 == 1) {
      value2 = EvalExpressionI((int)player,elem + 0x18,1);
      if (value2 < 0) {
        value2 = 0;
        Warn((int)player,(int)&str_attempted_change_to_negative_b4c0);
      }
      PlayerChangeState((int)player,value2);
      if ((((player[PL_ISHELPER] == 0) && (player[PL_CTRL] != 0)) && (player[PL_STATETYPE] - 1U < 2)) &&
         ((g[G_STAGEINFO_AUTOTURN] != 0 &&
          (b1 = GameModeInPassiveFightScreen(), ZEXT8(b1) == 0)))) {
        if ((value3 == 0) || (b1 = true, *(int *)(value3 + 0x158) == 0)) {
          b1 = false;
        }
        if (b1) {
          PlayerAutoTurn((int)player,value3,0);
        }
      }
      value3 = EvalExpressionI((int)player,elem + 0x24,1);
      if (value3 != -1) {
        player[PL_CTRL] = (uint32_t)(value3 != 0);
      }
      value3 = EvalExpressionI((int)player,elem + 0x30,1);
      if (value3 == -1) {
        return 1;
      }
      if (value3 < 0) {
        value3 = 0;
        Warn((int)player,(int)&str_attempted_change_to_negative_b480);
      }
L_080bfaf2:
      PlayerSelfAnim(player,value3);
      return 1;
    }
    if (value4 < 2) {
      if (value4 == 0) {
        return 0;
      }
    }
    else {
      if (value4 == 2) {
        player[0x2fc] = -1;
        player[0x2fb] = 0;
        player[0x4f0] = 0;
        player[0x259] = *player + 0x11b4;
        pu13 = (uint32_t *)player[PL_ANIM];
        item = *(int **)(*player + 0x11cc);
        *pu13 = item;
        if (*(int *)(*item + 8) <= (int)pu13[3]) {
          PlayerSelfAnim(player,0);
        }
        value3 = EvalExpressionI((int)player,elem + 0x18,1);
        if (value3 < 0) {
          value3 = 0;
          Warn((int)player,(int)&str_attempted_to_selfstate_to_ne_b500);
        }
        PlayerChangeState((int)player,value3);
        value3 = EvalExpressionI((int)player,elem + 0x24,1);
        if (value3 != -1) {
          player[PL_CTRL] = (uint32_t)(value3 != 0);
        }
        value3 = EvalExpressionI((int)player,elem + 0x30,1);
        if (value3 == -1) {
          return 1;
        }
        if (value3 < 0) {
          value3 = 0;
          Warn((int)player,(int)&str_attempted_change_to_negative_b480);
        }
        goto L_080bfaf2;
      }
      if (value4 == 3) {
        PlayerTurnAround((int)player);
        return 0;
      }
    }
    goto L_080c35f1;
  }
  if (value4 == 6) {
    value6 = EvalExpressionI((int)player,elem + 0x24,1);
    if (value6 < 0x3c) {
      value4 = EvalExpressionI((int)player,elem + 0x18,1);
      value5 = EvalExpressionI((int)player,elem + 0x30,1);
      value3 = value4;
      value2 = value5;
      if (value5 < value4) {
        value3 = value5;
        value2 = value4;
        value8 = value5;
      }
      l6 = random();
      player[value6 + PL_VAR] = l6 % ((value2 - value3) + 1) + value3;
      return 0;
    }
    fmt = "randomized var out of range (%i)";
    goto L_080c02dc;
  }
  if (5 < value4) {
    if (value4 == 7) {
      value2 = EvalExpressionI((int)player,elem + 0x3c,0);
      value3 = EvalExpressionI((int)player,elem + 0x18,1);
      value4 = EvalExpressionI((int)player,elem + 0x24,1);
      if (-1 < value3) {
        if (value2 == 0) {
          b14 = SBORROW4(value4,0x3b);
          value5 = -0x3b;
          b1 = value4 == 0x3b;
        }
        else {
          b14 = SBORROW4(value4,0x27);
          value5 = -0x27;
          b1 = value4 == 0x27;
        }
        if ((b1 || b14 != value4 + value5 < 0) && (value3 <= value4)) {
          if (value2 == 0) {
            value2 = EvalExpressionI((int)player,elem + 0x30,1);
            if (value2 == 0) {
              item = player + value3 + 0x390;
              for (value6 = (value4 - value3) * 4 + 4U >> 2; value6 != 0; value6 = value6 - 1) {
                *item = 0;
                item = item + 1;
              }
              return 0;
            }
            for (; value3 <= value4; value3 = value3 + 1) {
              player[value3 + PL_VAR] = value2;
            }
            return 0;
          }
          value7 = EvalExpressionF(player,(int *)(elem + 0x30));
          if (value7 == 0.0) {
            item = player + value3 + 0x3cc;
            for (value6 = (value4 - value3) * 4 + 4U >> 2; value6 != 0; value6 = value6 - 1) {
              *item = 0;
              item = item + 1;
            }
            return 0;
          }
          for (; value3 <= value4; value3 = value3 + 1) {
            player[value3 + PL_FVAR] = BITS_F2I(int, value7);
          }
          return 0;
        }
      }
      VWarn((int)player,"set illegal var range (%i-%i)",value3,value4);
      return 0;
    }
    if (value4 == 10) {
      value6 = EvalExpressionI((int)player,elem + 0x18,1);
      PlayerLifeSet((int)player,value6);
      return 0;
    }
    goto L_080c35f1;
  }
  value3 = EvalExpressionI((int)player,elem + 0x30,0);
  value6 = EvalExpressionI((int)player,elem + 0x24,1);
  if (1 < value3) {
    if (4 < value6) {
      fmt = "set sysvar out of range (%i)";
      u17 = value6;
      goto L_080c001f;
    }
    goto L_080c0031;
  }
  if (-1 < (int)value6) {
    if (value3 == 0) {
      if ((int)value6 < 0x3c) goto L_080c0031;
    }
    else if ((int)value6 < 0x28) {
L_080c0031:
      if (value3 == 1) {
        value7 = EvalExpressionF(player,(int *)(elem + 0x18));
        value3 = value6 * 4 + 0xf20;
        item = player + 4;
      }
      else {
        if (value3 < 2) {
          if (value3 != 0) {
            return 0;
          }
          value3 = EvalExpressionI((int)player,elem + 0x18,1);
          player[value6 + PL_VAR] = player[value6 + PL_VAR] + value3;
          return 0;
        }
        if (value3 == 3) {
          value3 = EvalExpressionI((int)player,elem + 0x18,1);
          player[value6 + PL_SYSVAR] = player[value6 + PL_SYSVAR] + value3;
          return 0;
        }
        if (value3 != 4) {
          return 0;
        }
        value7 = EvalExpressionF(player,(int *)(elem + 0x18));
        value3 = value6 * 4 + 0xfd0;
        item = player + 5;
      }
L_080c33fe:
      *(float *)(value3 + (int)item) = *(float *)(value3 + (int)item) + value7;
      return 0;
    }
  }
  fmt = "set var out of range (%i)";
  looptime = stale_ECX_00;
L_080c0001:
  VWarn((int)player,fmt,value6,looptime);
  return 0;
}
#undef value8
#undef stk_10c0
#undef stk_10bc
#undef stk_10ac
#undef fmt2
#undef stk_8c
#undef stk_6c
#undef stk_4c
#undef stk_24
#undef stk_20

/* SCtrlRCElemFree @ 0x080c3630, 470 bytes
 *
 * Frees one parsed state controller: its trigger expressions and the
 * type-specific data (HitDef, Projectile, PlaySnd, AfterImage, Explod...
 * parameter blocks).
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * Calls: FreeExpArray, FreeExpression, AftImgParamsEFree, PlaySndInfoFree,
 *        HitDefEFree, HitOverrideEFree, ProjMakeInfoFree, EnvShakeEFree,
 *        ExplodInfoFree, SuperPauseInfoFree, PalFXEFree, HelperInfoFree
 * C library: free
 * Called by: SCtrlRCFree
 *
 * Elecbyte file: src/mugen/st-ctrl.c
 */
uint32_t SCtrlRCElemFree(uint32_t *arg1)

{
  int i1;
  uint32_t stale_EAX;
  uint32_t stk_c;
  
  FreeExpArray((void *)*arg1);
  FreeExpression(arg1 + 6);
  FreeExpression(arg1 + 9);
  FreeExpression(arg1 + 0xc);
  FreeExpression(arg1 + 0xf);
  FreeExpression(arg1 + 0x12);
  FreeExpression(arg1 + 0x15);
  i1 = arg1[4];
  if (i1 == 0xd2) {
    AftImgParamsEFree((int *)arg1[0x18]);
  }
  else if (i1 < 0xd3) {
    if (i1 < 0x27) {
      if (i1 < 0x25) {
        if (i1 == 0x22) {
          PlaySndInfoFree((int *)arg1[0x18]);
        }
      }
      else {
        HitDefEFree(arg1[0x18]);
      }
    }
    else if (i1 == 0x78) {
      HitOverrideEFree(arg1[0x18]);
    }
    else if (i1 < 0x79) {
      if (i1 == 0x27) {
        ProjMakeInfoFree((int *)arg1[0x18]);
      }
    }
    else if (i1 == 200) {
      EnvShakeEFree((int *)arg1[0x18]);
    }
  }
  else if (i1 == 0xdc) {
    ExplodInfoFree((int *)arg1[0x18]);
  }
  else if (i1 < 0xdd) {
    if (i1 == 0xd6) {
      SuperPauseInfoFree((int *)arg1[0x18]);
    }
    else if (i1 == 0xd8) {
      PalFXEFree(arg1[0x18]);
    }
  }
  else if (i1 != 0xe6) {
    if (i1 < 0xe7) {
      if (i1 == 0xdf) {
        ExplodInfoFree((int *)arg1[0x18]);
      }
    }
    else if (i1 == 300) {
      HelperInfoFree(arg1[0x18]);
    }
  }
  if ((void *)arg1[0x18] == (void *)0x0) {
    return stk_c;
  }
  free((void *)arg1[0x18]);
  return stale_EAX;
}

