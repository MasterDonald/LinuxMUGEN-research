/*
 * st-trig.c -- triggers
 * Compiling trigger names and arguments into expression code, testing a
 * controller's triggers, and evaluating each trigger for a player.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/st-trig.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* SCtrlParseTrigger @ 0x080ca000, 12010 bytes
 *
 * Compiles one trigger expression (the text after "triggerN =") into postfix
 * code for the expression evaluator. It recognises every trigger name and
 * its arguments: AnimElem, Command, HitDefAttr, StateType/MoveType
 * comparisons, P2/Enemy/Target redirections, Var/FVar/SysVar, Const(...),
 * GetHitVar(...), and so on. Errors: "Invalid trigger: %s", "Invalid win
 * trigger", ...
 *
 * Parameters:
 *   text         char *
 *   player       int
 *   arg3         uint32_t *
 *   arg4         void *
 *   arg5         int
 *   arg6         int *
 *
 * Globals read: errmsg
 * Calls: ConstExpI, InfixToPostfix, strimatchlen, SCtrlReadExpListArray,
 *        ParseHitAttr, SCtrlParseTriggerRange, ecalloc
 * C library: _alemu_stricmp, __strtol_internal, _alemu_strlwr, flag,
 *            strcmp, sprintf, memcpy
 * Called by: InfToPostArray
 * Messages:
 *   "Invalid trigger: %s"
 *   "Invalid win trigger: %s"
 *   "Invalid lose trigger: %s"
 *   "Need to specify gethitvar(varname): %s"
 *   "Missing closing parenthesis: %s"
 *   "Invalid varname %s in: %s"
 *
 * Elecbyte file: src/mugen/st-trig.c
 * Note: decompiler flag: type propagation did not settle
 * Note: call to 0x08102020 (Ghidra label gcc2_compiled.) renamed to its symbol
 *       _alemu_strlwr
 * Note: 23 data addresses refer to the data image (data/mugen_data.S).
 * Note: 4 dead flag initialisations of inlined repz cmpsb loops set to constants
 * Note: shared sprintf() call: 14 formats, arguments recovered for 12, others
 *       passed as 0
 * Note: Locals live in `frame`, laid out as on the original stack (0x7f0 bytes,
 *       22 variables), because their address is taken.
 */
char * SCtrlParseTrigger(char *text,int player,uint32_t *arg3,void *arg4,int arg5,
                        int *arg6)

{
  void *fmt_args[2] = {0};
  uint8_t b1;
  uint16_t u2;
  int i3;
  int *mem;
  int i5;
  char c6;
  uint32_t *pu7;
  int *pi8;
  uint8_t *pb9;
  uint32_t u10;
  uint32_t *pu11;
  int *pi12;
  bool b13;
  bool b14;
  bool b15;
  uint8_t *pb16;
  char *pc17;
  unsigned char frame[0x7f0] __attribute__((aligned(16)));
#define stk_7ec (*(char **)(frame + 0x4))
#define stk_7e8 (*(char **)(frame + 0x8))
#define stk_7e4 (*(char **)(frame + 0xc))
#define stk_7e0 (*(char **)(frame + 0x10))
#define stk_7dc (*(uint8_t (*)[256])(frame + 0x14))
#define stk_6dc (*(char (*)[256])(frame + 0x114))
#define stk_5dc (*(char (*)[256])(frame + 0x214))
#define stk_4dc (*(uint8_t (*)[256])(frame + 0x314))
#define stk_3dc (*(int (*)[5])(frame + 0x414))
#define stk_3c8 (*(uint32_t *)(frame + 0x428))
#define stk_3c4 (*(uint32_t *)(frame + 0x42c))
#define stk_3c0 (*(uint32_t *)(frame + 0x430))
#define stk_3bc (*(uint32_t *)(frame + 0x434))
#define stk_3b8 (*(uint32_t *)(frame + 0x438))
#define stk_3b4 (*(uint32_t *)(frame + 0x43c))
#define mem2 (*(char **)(frame + 0x448))
#define stk_39c (*(char (*)[128])(frame + 0x454))
#define stk_31c (*(uint32_t (*)[128])(frame + 0x4d4))
#define stk_11c (*(char (*)[4])(frame + 0x6d4))
#define stk_118 (*(char (*)[3])(frame + 0x6d8))
#define stk_115 (*(uint8_t (*)[4])(frame + 0x6db))
#define stk_111 (*(uint8_t (*)[257])(frame + 0x6df))
  
  stk_7ec = (char *)0x0;
  pi8 = stk_3dc;
  for (i5 = 0xe; i5 != 0; i5 = i5 + -1) {
    *pi8 = 0;
    pi8 = pi8 + 1;
  }
  stk_7e8 = (char *)0x0;
  stk_7e4 = (char *)0x0;
  while( true ) {
    c6 = text[(int)stk_7e8];
    b13 = false;
    if (((*(uint8_t *)(__ctype_b + c6 * 2) & 8) != 0) || (c6 == '_')) {
      b13 = true;
    }
    if (!b13) break;
    stk_11c[(int)stk_7e4] = c6;
    stk_7e4 = stk_7e4 + 1;
    stk_7e8 = stk_7e8 + 1;
  }
  stk_11c[(int)stk_7e4] = '\0';
  b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
  while ((b1 & 0x20) != 0) {
    stk_7e8 = stk_7e8 + 1;
    b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
  }
  stk_3dc[1] = 0;
  b13 = false;
  i5 = _alemu_stricmp(stk_11c,"parent");
  if (i5 == 0) {
    stk_3dc[1] = 1;
  }
  else {
    i5 = _alemu_stricmp(stk_11c,"root");
    if (i5 == 0) {
      stk_3dc[1] = 2;
    }
    else {
      i5 = _alemu_stricmp(stk_11c,"helper");
      if (i5 == 0) {
        stk_3dc[1] = 3;
        i5 = 0;
      }
      else {
        i5 = _alemu_stricmp(stk_11c,"target");
        if (i5 == 0) {
          stk_3dc[1] = 4;
L_080ca220:
          i5 = -1;
        }
        else {
          i5 = _alemu_stricmp(stk_11c,"partner");
          if (i5 == 0) {
            stk_3dc[1] = 5;
            i5 = 0;
          }
          else {
            i5 = _alemu_stricmp(stk_11c,"enemy");
            if (i5 == 0) {
              stk_3dc[1] = 6;
              i5 = 0;
            }
            else {
              i5 = _alemu_stricmp(stk_11c,"enemynear");
              if (i5 != 0) {
                i5 = _alemu_stricmp(stk_11c,"playerid");
                if (i5 != 0) goto L_080ca230;
                stk_3dc[1] = 8;
                goto L_080ca220;
              }
              stk_3dc[1] = 7;
              i5 = 0;
            }
          }
        }
      }
      b13 = true;
      ConstExpI(stk_3dc + 2,i5);
    }
  }
L_080ca230:
  if (b13) {
    if (text[(int)stk_7e8] == '(') {
      i5 = InfixToPostfix((uint8_t *)(text + (int)(stk_7e8 + 1)),stk_3dc + 2,player,
                             &stk_7e0,1);
      if (i5 == 0) {
        return (char *)0x0;
      }
      if (*stk_7e0 != ')') {
        return (char *)0x0;
      }
      stk_7e8 = stk_7e0 + (1 - (int)text);
    }
    else if (stk_3dc[1] == 8) {
      return (char *)0x0;
    }
  }
  if (stk_3dc[1] != 0) {
    stk_7e8 = text + (int)stk_7e8;
    b1 = *(uint8_t *)(__ctype_b + 1 + *stk_7e8 * 2);
    while ((b1 & 0x20) != 0) {
      stk_7e8 = stk_7e8 + 1;
      b1 = *(uint8_t *)(__ctype_b + 1 + *stk_7e8 * 2);
    }
    if (*stk_7e8 != ',') {
      return (char *)0x0;
    }
    text = stk_7e8 + 1;
    b1 = *(uint8_t *)(__ctype_b + 1 + *text * 2);
    while ((b1 & 0x20) != 0) {
      text = text + 1;
      b1 = *(uint8_t *)(__ctype_b + 1 + *text * 2);
    }
    stk_7e8 = (char *)0x0;
    stk_7e4 = (char *)0x0;
    while( true ) {
      c6 = text[(int)stk_7e8];
      b13 = false;
      if (((*(uint8_t *)(__ctype_b + c6 * 2) & 8) != 0) || (c6 == '_')) {
        b13 = true;
      }
      if (!b13) break;
      stk_11c[(int)stk_7e4] = c6;
      stk_7e4 = stk_7e4 + 1;
      stk_7e8 = stk_7e8 + 1;
    }
    stk_11c[(int)stk_7e4] = '\0';
  }
  i5 = _alemu_stricmp(stk_11c,"time");
  if ((i5 == 0) || (i5 = _alemu_stricmp(stk_11c,"statetime"), i5 == 0)) {
    stk_3dc[0] = 0;
  }
  else {
    i5 = _alemu_stricmp(stk_11c,"animtime");
    if (i5 == 0) {
      stk_3dc[0] = 1;
    }
    else {
      i5 = _alemu_stricmp(stk_11c,"animelem");
      if (i5 == 0) {
        stk_3dc[0] = 2;
      }
      else {
        i5 = _alemu_stricmp(stk_11c,"anim");
        if (i5 == 0) {
          stk_3dc[0] = 3;
        }
        else {
          i5 = _alemu_stricmp(stk_11c,"vel");
          if (i5 == 0) {
            stk_3dc[0] = 6;
          }
          else {
            i5 = _alemu_stricmp(stk_11c,"pos");
            if (i5 == 0) {
              stk_3dc[0] = 4;
            }
            else {
              i5 = _alemu_stricmp(stk_11c,"screenpos");
              if (i5 == 0) {
                stk_3dc[0] = 5;
              }
              else {
                i5 = _alemu_stricmp(stk_11c,"timemod");
                if (i5 == 0) {
                  stk_3dc[0] = 7;
                }
                else {
                  i5 = _alemu_stricmp(stk_11c,"p2dist");
                  if (i5 == 0) {
                    stk_3dc[0] = 8;
                  }
                  else {
                    i5 = _alemu_stricmp(stk_11c,"p2bodydist");
                    if (i5 == 0) {
                      stk_3dc[0] = 9;
                    }
                    else {
                      i5 = _alemu_stricmp(stk_11c,"p2life");
                      if (i5 == 0) {
                        stk_3dc[0] = 10;
                      }
                      else {
                        i5 = _alemu_stricmp(stk_11c,"winperfect");
                        if (i5 == 0) {
                          stk_3dc[0] = 0x6c;
                        }
                        else {
                          i5 = strimatchlen((int)stk_11c,(int)&str_win,3);
                          if (i5 == 0) {
                            i5 = strimatchlen((int)stk_11c,(int)&str_lose,4);
                            if (i5 == 0) {
                              i5 = _alemu_stricmp(stk_11c,"drawgame");
                              if (i5 == 0) {
                                stk_3dc[0] = 0x6f;
                              }
                              else {
                                i5 = _alemu_stricmp(stk_11c,"matchover");
                                if (i5 == 0) {
                                  stk_3dc[0] = 0x70;
                                }
                                else {
                                  i5 = _alemu_stricmp(stk_11c,"gametime");
                                  if (i5 == 0) {
                                    stk_3dc[0] = 0x71;
                                  }
                                  else {
                                    i5 = _alemu_stricmp(stk_11c,"roundno");
                                    if (i5 == 0) {
                                      stk_3dc[0] = 0x72;
                                    }
                                    else {
                                      i5 = _alemu_stricmp(stk_11c,"roundstate");
                                      if (i5 == 0) {
                                        stk_3dc[0] = 0x73;
                                      }
                                      else {
                                        i5 = _alemu_stricmp(stk_11c,"matchno");
                                        if (i5 == 0) {
                                          stk_3dc[0] = 0x74;
                                        }
                                        else {
                                          i5 = _alemu_stricmp(stk_11c,"roundsexisted");
                                          if (i5 == 0) {
                                            stk_3dc[0] = 0x75;
                                          }
                                          else {
                                            i5 = _alemu_stricmp(stk_11c,"teamside");
                                            if (i5 == 0) {
                                              stk_3dc[0] = 0x78;
                                            }
                                            else {
                                              i5 = _alemu_stricmp(stk_11c,"teammode");
                                              if (i5 == 0) {
                                                stk_3dc[0] = 0x79;
                                              }
                                              else {
                                                i5 = _alemu_stricmp(stk_11c,"ishometeam");
                                                if (i5 == 0) {
                                                  stk_3dc[0] = 0x7a;
                                                }
                                                else {
                                                  i5 = _alemu_stricmp(stk_11c,"frontedgedist");
                                                  if (i5 == 0) {
                                                    stk_3dc[0] = 0xb;
                                                  }
                                                  else {
                                                    i5 = _alemu_stricmp(stk_11c,"backedgedist")
                                                    ;
                                                    if (i5 == 0) {
                                                      stk_3dc[0] = 0xc;
                                                    }
                                                    else {
                                                      i5 = _alemu_stricmp(stk_11c,
                                                                             "frontedgebodydist");
                                                      if (i5 == 0) {
                                                        stk_3dc[0] = 0xb;
                                                        stk_3b8 = 1;
                                                      }
                                                      else {
                                                        i5 = _alemu_stricmp(stk_11c,
                                                                               "backedgebodydist");
                                                        if (i5 == 0) {
                                                          stk_3dc[0] = 0xc;
                                                          stk_3b8 = 1;
                                                        }
                                                        else {
                                                          i5 = _alemu_stricmp(stk_11c,"life");
                                                          if (i5 == 0) {
                                                            stk_3dc[0] = 0xf;
                                                          }
                                                          else {
                                                            i5 = _alemu_stricmp(stk_11c,
                                                                                   "lifemax");
                                                            if (i5 == 0) {
                                                              stk_3dc[0] = 0x10;
                                                            }
                                                            else {
                                                              i5 = _alemu_stricmp(stk_11c,
                                                                                     "power");
                                                              if (i5 == 0) {
                                                                stk_3dc[0] = 0x11;
                                                              }
                                                              else {
                                                                i5 = _alemu_stricmp(stk_11c,
                                                                                       "powermax");
                                                                if (i5 == 0) {
                                                                  stk_3dc[0] = 0x12;
                                                                }
                                                                else {
                                                                  i5 = _alemu_stricmp(stk_11c,
                                                                                         "alive");
                                                                  if (i5 == 0) {
                                                                    stk_3dc[0] = 0x13;
                                                                  }
                                                                  else {
                                                                    i5 = _alemu_stricmp(stk_11c
                                                  ,"command");
                                                  if (i5 == 0) {
                                                    stk_3dc[0] = 0x14;
                                                  }
                                                  else {
                                                    i5 = _alemu_stricmp(stk_11c,"hitcount");
                                                    if (i5 == 0) {
                                                      stk_3dc[0] = 0x1e;
                                                    }
                                                    else {
                                                      i5 = _alemu_stricmp(stk_11c,
                                                                             "uniqhitcount");
                                                      if (i5 == 0) {
                                                        stk_3dc[0] = 0x1f;
                                                      }
                                                      else {
                                                        i5 = _alemu_stricmp(stk_11c,"movehit");
                                                        if (i5 == 0) {
                                                          stk_3dc[0] = 0x20;
                                                        }
                                                        else {
                                                          i5 = _alemu_stricmp(stk_11c,
                                                                                 "moveguarded");
                                                          if (i5 == 0) {
                                                            stk_3dc[0] = 0x21;
                                                          }
                                                          else {
                                                            i5 = _alemu_stricmp(stk_11c,
                                                                                   "movecontact");
                                                            if (i5 == 0) {
                                                              stk_3dc[0] = 0x22;
                                                            }
                                                            else {
                                                              i5 = _alemu_stricmp(stk_11c,
                                                                                     "movereversed")
                                                              ;
                                                              if (i5 == 0) {
                                                                stk_3dc[0] = 0x23;
                                                              }
                                                              else {
                                                                i5 = _alemu_stricmp(stk_11c,
                                                                                       "inguarddist"
                                                                                      );
                                                                if (i5 == 0) {
                                                                  stk_3dc[0] = 0x24;
                                                                }
                                                                else {
                                                                  i5 = _alemu_stricmp(stk_11c,
                                                                                         "stateno");
                                                                  if (i5 == 0) {
                                                                    stk_3dc[0] = 0x28;
                                                                  }
                                                                  else {
                                                                    i5 = _alemu_stricmp(stk_11c
                                                  ,"prevstateno");
                                                  if (i5 == 0) {
                                                    stk_3dc[0] = 0x29;
                                                  }
                                                  else {
                                                    i5 = _alemu_stricmp(stk_11c,"p2stateno");
                                                    if (i5 == 0) {
                                                      stk_3dc[0] = 0x2a;
                                                    }
                                                    else {
                                                      i5 = _alemu_stricmp(stk_11c,"statetype");
                                                      if (i5 == 0) {
                                                        stk_3dc[0] = 0x2b;
                                                      }
                                                      else {
                                                        i5 = _alemu_stricmp(stk_11c,
                                                                               "p2statetype");
                                                        if (i5 == 0) {
                                                          stk_3dc[0] = 0x2c;
                                                        }
                                                        else {
                                                          i5 = _alemu_stricmp(stk_11c,
                                                                                 "movetype");
                                                          if (i5 == 0) {
                                                            stk_3dc[0] = 0x2d;
                                                          }
                                                          else {
                                                            i5 = _alemu_stricmp(stk_11c,
                                                                                   "p2movetype");
                                                            if (i5 == 0) {
                                                              stk_3dc[0] = 0x2e;
                                                            }
                                                            else {
                                                              i5 = _alemu_stricmp(stk_11c,
                                                                                     "ctrl");
                                                              if (i5 == 0) {
                                                                stk_3dc[0] = 0x2f;
                                                              }
                                                              else {
                                                                i5 = _alemu_stricmp(stk_11c,
                                                                                       "hitdefattr")
                                                                ;
                                                                if (i5 == 0) {
                                                                  stk_3dc[0] = 0x30;
                                                                }
                                                                else {
                                                                  i5 = _alemu_stricmp(stk_11c,
                                                                                         "var");
                                                                  if (i5 == 0) {
                                                                    stk_3dc[0] = 0x157;
                                                                  }
                                                                  else {
                                                                    i5 = _alemu_stricmp(stk_11c
                                                  ,"fvar");
                                                  if (i5 == 0) {
                                                    stk_3dc[0] = 0x158;
                                                  }
                                                  else {
                                                    i5 = _alemu_stricmp(stk_11c,"sysvar");
                                                    if (i5 == 0) {
                                                      stk_3dc[0] = 0x159;
                                                    }
                                                    else {
                                                      i5 = _alemu_stricmp(stk_11c,"sysfvar");
                                                      if (i5 == 0) {
                                                        stk_3dc[0] = 0x15a;
                                                      }
                                                      else {
                                                        i5 = _alemu_stricmp(stk_11c,"random");
                                                        if (i5 == 0) {
                                                          stk_3dc[0] = 0x33;
                                                        }
                                                        else {
                                                          i5 = _alemu_stricmp(stk_11c,"numproj"
                                                                                );
                                                          if (i5 == 0) {
                                                            stk_3dc[0] = 0x3c;
                                                          }
                                                          else {
                                                            i5 = _alemu_stricmp(stk_11c,
                                                                                   "numprojid");
                                                            if (i5 == 0) {
                                                              stk_3dc[0] = 0x154;
                                                            }
                                                            else {
                                                              i5 = _alemu_stricmp(stk_11c,
                                                                                                                                                                          
                                                  "projcanceltime");
                                                  if (i5 == 0) {
                                                    stk_3dc[0] = 0x15b;
                                                  }
                                                  else {
                                                    i5 = _alemu_stricmp(stk_11c,"projhittime");
                                                    if (i5 == 0) {
                                                      stk_3dc[0] = 0x151;
                                                    }
                                                    else {
                                                      i5 = strimatchlen((int)stk_11c,(int)&str_projhit_c50c,
                                                                           7);
                                                      if (i5 == 0) {
                                                        i5 = _alemu_stricmp(stk_11c,
                                                                               "projguardedtime");
                                                        if (i5 == 0) {
                                                          stk_3dc[0] = 0x152;
                                                        }
                                                        else {
                                                          i5 = strimatchlen((int)stk_11c,
                                                                               (int)&str_projguarded_c524,0xb);
                                                          if (i5 == 0) {
                                                            i5 = _alemu_stricmp(stk_11c,
                                                                                   "projcontacttime"
                                                                                  );
                                                            if (i5 == 0) {
                                                              stk_3dc[0] = 0x153;
                                                            }
                                                            else {
                                                              i5 = strimatchlen((int)stk_11c,
                                                                                   (int)&str_projcontact_c540,0xb);
                                                              if (i5 == 0) {
                                                                i5 = _alemu_stricmp(stk_11c,
                                                                                       "p1name");
                                                                if ((i5 == 0) ||
                                                                   (i5 = _alemu_stricmp(stk_11c
                                                  ,"name"), i5 == 0)) {
                                                    stk_3dc[0] = 0x5a;
                                                  }
                                                  else {
                                                    i5 = _alemu_stricmp(stk_11c,"p2name");
                                                    if (i5 == 0) {
                                                      stk_3dc[0] = 0x5b;
                                                    }
                                                    else {
                                                      i5 = _alemu_stricmp(stk_11c,"p3name");
                                                      if (i5 == 0) {
                                                        stk_3dc[0] = 0x5c;
                                                      }
                                                      else {
                                                        i5 = _alemu_stricmp(stk_11c,"p4name");
                                                        if (i5 == 0) {
                                                          stk_3dc[0] = 0x5d;
                                                        }
                                                        else {
                                                          i5 = _alemu_stricmp(stk_11c,
                                                                                 "authorname");
                                                          if (i5 == 0) {
                                                            stk_3dc[0] = 0x5e;
                                                          }
                                                          else {
                                                            i5 = _alemu_stricmp(stk_11c,
                                                                                   "numpartner");
                                                            if (i5 == 0) {
                                                              stk_3dc[0] = 0x5f;
                                                            }
                                                            else {
                                                              i5 = _alemu_stricmp(stk_11c,
                                                                                     "numenemy");
                                                              if (i5 == 0) {
                                                                stk_3dc[0] = 0x60;
                                                              }
                                                              else {
                                                                i5 = _alemu_stricmp(stk_11c,
                                                                                       "id");
                                                                if (i5 == 0) {
                                                                  stk_3dc[0] = 0x61;
                                                                }
                                                                else {
                                                                  i5 = _alemu_stricmp(stk_11c,
                                                                                         "facing");
                                                                  if (i5 == 0) {
                                                                    stk_3dc[0] = 99;
                                                                  }
                                                                  else {
                                                                    i5 = _alemu_stricmp(stk_11c
                                                  ,"hitfall");
                                                  if (i5 == 0) {
                                                    stk_3dc[0] = 100;
                                                  }
                                                  else {
                                                    i5 = _alemu_stricmp(stk_11c,"hitshakeover")
                                                    ;
                                                    if (i5 == 0) {
                                                      stk_3dc[0] = 0x65;
                                                    }
                                                    else {
                                                      i5 = _alemu_stricmp(stk_11c,"hitover");
                                                      if (i5 == 0) {
                                                        stk_3dc[0] = 0x66;
                                                      }
                                                      else {
                                                        i5 = _alemu_stricmp(stk_11c,"hitvel");
                                                        if (i5 == 0) {
                                                          stk_3dc[0] = 0x67;
                                                        }
                                                        else {
                                                          i5 = _alemu_stricmp(stk_11c,
                                                                                 "hitpausetime");
                                                          if (i5 == 0) {
                                                            stk_3dc[0] = 0x68;
                                                          }
                                                          else {
                                                            i5 = _alemu_stricmp(stk_11c,
                                                                                   "canrecover");
                                                            if (i5 == 0) {
                                                              stk_3dc[0] = 0x69;
                                                            }
                                                            else {
                                                              i5 = _alemu_stricmp(stk_11c,
                                                                                     "animelemno");
                                                              if (i5 == 0) {
                                                                stk_3dc[0] = 0x15c;
                                                              }
                                                              else {
                                                                i5 = _alemu_stricmp(stk_11c,
                                                                                       "animexist");
                                                                if (i5 == 0) {
                                                                  stk_3dc[0] = 0x14c;
                                                                }
                                                                else {
                                                                  i5 = _alemu_stricmp(stk_11c,
                                                                                                                                                                                  
                                                  "selfanimexist");
                                                  if (i5 == 0) {
                                                    stk_3dc[0] = 0x14d;
                                                  }
                                                  else {
                                                    i5 = _alemu_stricmp(stk_11c,"playeridexist"
                                                                          );
                                                    if (i5 == 0) {
                                                      stk_3dc[0] = 0x14e;
                                                    }
                                                    else {
                                                      i5 = _alemu_stricmp(stk_11c,"palno");
                                                      if (i5 == 0) {
                                                        stk_3dc[0] = 0x6b;
                                                      }
                                                      else {
                                                        i5 = _alemu_stricmp(stk_11c,"numexplod"
                                                                              );
                                                        if (i5 == 0) {
                                                          stk_3dc[0] = 0x96;
                                                        }
                                                        else {
                                                          i5 = _alemu_stricmp(stk_11c,
                                                                                 "numtarget");
                                                          if (i5 == 0) {
                                                            stk_3dc[0] = 0xa0;
                                                          }
                                                          else {
                                                            i5 = _alemu_stricmp(stk_11c,
                                                                                   "gethitvar");
                                                            if (i5 == 0) {
                                                              stk_3dc[0] = 0xb4;
                                                            }
                                                            else {
                                                              i5 = _alemu_stricmp(stk_11c,
                                                                                     "const");
                                                              if (i5 == 0) {
                                                                stk_3dc[0] = 0xb5;
                                                              }
                                                              else {
                                                                i5 = _alemu_stricmp(stk_11c,
                                                                                       "stagevar");
                                                                if (i5 == 0) {
                                                                  stk_3dc[0] = 0xb6;
                                                                }
                                                                else {
                                                                  i5 = _alemu_stricmp(stk_11c,
                                                                                                                                                                                  
                                                  "tickspersecond");
                                                  if (i5 == 0) {
                                                    stk_3dc[0] = 0xbe;
                                                  }
                                                  else {
                                                    i5 = _alemu_stricmp(stk_11c,"ishelper");
                                                    if (i5 == 0) {
                                                      stk_3dc[0] = 0xc9;
                                                    }
                                                    else {
                                                      i5 = _alemu_stricmp(stk_11c,"numhelper");
                                                      if (i5 == 0) {
                                                        stk_3dc[0] = 0xca;
                                                      }
                                                      else {
                                                        i5 = _alemu_stricmp(stk_11c,
                                                                               "parentdist");
                                                        if (i5 == 0) {
                                                          stk_3dc[0] = 0xcb;
                                                        }
                                                        else {
                                                          i5 = _alemu_stricmp(stk_11c,
                                                                                 "rootdist");
                                                          if (i5 == 0) {
                                                            stk_3dc[0] = 0xcc;
                                                          }
                                                          else {
                                                            i5 = _alemu_stricmp(stk_11c,
                                                                                   "standby");
                                                            if (i5 == 0) {
                                                              stk_3dc[0] = 0xcd;
                                                            }
                                                            else {
                                                              i5 = _alemu_stricmp(stk_11c,"pi")
                                                              ;
                                                              if (i5 == 0) {
                                                                stk_3dc[0] = 300;
                                                              }
                                                              else {
                                                                i5 = _alemu_stricmp(stk_11c,"e"
                                                                                      );
                                                                if (i5 == 0) {
                                                                  stk_3dc[0] = 0x12d;
                                                                }
                                                                else {
                                                                  i5 = _alemu_stricmp(stk_11c,
                                                                                         "ifelse");
                                                                  if (i5 == 0) {
                                                                    stk_3dc[0] = 0x131;
                                                                  }
                                                                  else {
                                                                    i5 = _alemu_stricmp(stk_11c
                                                  ,"log");
                                                  if (i5 == 0) {
                                                    stk_3dc[0] = 0x136;
                                                  }
                                                  else {
                                                    i5 = _alemu_stricmp(stk_11c,"sin");
                                                    if (i5 == 0) {
                                                      stk_3dc[0] = 0x140;
                                                    }
                                                    else {
                                                      i5 = _alemu_stricmp(stk_11c,"cos");
                                                      if (i5 == 0) {
                                                        stk_3dc[0] = 0x141;
                                                      }
                                                      else {
                                                        i5 = _alemu_stricmp(stk_11c,"tan");
                                                        if (i5 == 0) {
                                                          stk_3dc[0] = 0x142;
                                                        }
                                                        else {
                                                          i5 = _alemu_stricmp(stk_11c,"asin");
                                                          if (i5 == 0) {
                                                            stk_3dc[0] = 0x143;
                                                          }
                                                          else {
                                                            i5 = _alemu_stricmp(stk_11c,"acos")
                                                            ;
                                                            if (i5 == 0) {
                                                              stk_3dc[0] = 0x144;
                                                            }
                                                            else {
                                                              i5 = _alemu_stricmp(stk_11c,
                                                                                     "atan");
                                                              if (i5 == 0) {
                                                                stk_3dc[0] = 0x145;
                                                              }
                                                              else {
                                                                i5 = _alemu_stricmp(stk_11c,
                                                                                       "exp");
                                                                if (i5 == 0) {
                                                                  stk_3dc[0] = 0x146;
                                                                }
                                                                else {
                                                                  i5 = _alemu_stricmp(stk_11c,
                                                                                         "ln");
                                                                  if (i5 == 0) {
                                                                    stk_3dc[0] = 0x147;
                                                                  }
                                                                  else {
                                                                    i5 = _alemu_stricmp(stk_11c
                                                  ,"abs");
                                                  if (i5 == 0) {
                                                    stk_3dc[0] = 0x148;
                                                  }
                                                  else {
                                                    i5 = _alemu_stricmp(stk_11c,"floor");
                                                    if (i5 == 0) {
                                                      stk_3dc[0] = 0x149;
                                                    }
                                                    else {
                                                      i5 = _alemu_stricmp(stk_11c,"ceil");
                                                      if (i5 == 0) {
                                                        stk_3dc[0] = 0x14a;
                                                      }
                                                      else {
                                                        i5 = _alemu_stricmp(stk_11c,
                                                                               "animelemtime");
                                                        if (i5 != 0) {
                                                          pb16 = (uint8_t *)(g + G_ERRMSG);
                                                          fmt_args[0] = (void *)(stk_11c);
                                                          pc17 = "Invalid trigger: %s";
                                                          goto L_080cccd9;
                                                        }
                                                        stk_3dc[0] = 0x14b;
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
                                                  else {
                                                    stk_3dc[0] = 0x40;
                                                  }
                                                  }
                                                  }
                                                  else {
                                                    stk_3dc[0] = 0x3f;
                                                  }
                                                  }
                                                  }
                                                  else {
                                                    stk_3dc[0] = 0x3e;
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
                            else {
                              stk_3dc[0] = 0x6e;
                            }
                          }
                          else {
                            stk_3dc[0] = 0x6d;
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
  b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
  while ((b1 & 0x20) != 0) {
    stk_7e8 = stk_7e8 + 1;
    b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
  }
  if ((stk_3dc[0] == 0xc9) && (text[(int)stk_7e8] == '(')) {
    stk_3dc[0] = 0x14f;
  }
  if ((stk_3dc[0] == 0xca) && (text[(int)stk_7e8] == '(')) {
    stk_3dc[0] = 0x150;
  }
  if ((stk_3dc[0] == 0x96) && (text[(int)stk_7e8] == '(')) {
    stk_3dc[0] = 0x155;
  }
  if ((stk_3dc[0] == 0xa0) && (text[(int)stk_7e8] == '(')) {
    stk_3dc[0] = 0x156;
  }
  if (stk_3dc[0] - 0x140U < 0x1d) {
    if (text[(int)stk_7e8] != '(') {
      return (char *)0x0;
    }
    i5 = SCtrlReadExpListArray
                      ((uint8_t *)(text + (int)(stk_7e8 + 1)),"n:)",player,&stk_7e0,
                       (int)stk_31c,(int)stk_39c,(int *)&stk_7e4,arg5);
    if (i5 != 1) {
      return (char *)0x0;
    }
    if (*stk_7e0 != ')') {
      return (char *)0x0;
    }
    stk_7ec = stk_7e4;
    stk_7e8 = stk_7e0 + (1 - (int)text);
  }
  if (stk_3dc[0] == 0x136) {
    b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
    while ((b1 & 0x20) != 0) {
      stk_7e8 = stk_7e8 + 1;
      b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
    }
    if (text[(int)stk_7e8] != '(') {
      return (char *)0x0;
    }
    i5 = SCtrlReadExpListArray
                      ((uint8_t *)(text + (int)(stk_7e8 + 1)),"nn:)",player,&stk_7e0,
                       (int)(stk_31c + (int)stk_7ec),(int)(stk_39c + (int)stk_7ec),
                       (int *)&stk_7e4,arg5 - (int)stk_7ec);
    if (i5 != 2) {
      return (char *)0x0;
    }
    if (*stk_7e0 != ')') {
      return (char *)0x0;
    }
    stk_7ec = stk_7ec + (int)stk_7e4;
    stk_7e8 = stk_7e0 + (1 - (int)text);
  }
  if (stk_3dc[0] == 0x131) {
    b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
    while ((b1 & 0x20) != 0) {
      stk_7e8 = stk_7e8 + 1;
      b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
    }
    if (text[(int)stk_7e8] != '(') {
      return (char *)0x0;
    }
    i5 = SCtrlReadExpListArray
                      ((uint8_t *)(text + (int)(stk_7e8 + 1)),"nnn:)",player,&stk_7e0,
                       (int)(stk_31c + (int)stk_7ec),(int)(stk_39c + (int)stk_7ec),
                       (int *)&stk_7e4,arg5 - (int)stk_7ec);
    if (i5 != 3) {
      return (char *)0x0;
    }
    if (*stk_7e0 != ')') {
      return (char *)0x0;
    }
    stk_7ec = stk_7ec + (int)stk_7e4;
    stk_7e8 = stk_7e0 + (1 - (int)text);
  }
  if (stk_3dc[0] == 0x3e) {
    stk_3b8 = __strtol_internal(stk_115,(uint32_t *)0x0,10,0);
  }
  if (stk_3dc[0] - 0x3fU < 2) {
    stk_3b8 = __strtol_internal(stk_111,(uint32_t *)0x0,10,0);
  }
  if (stk_3dc[0] == 0x6d) {
    i5 = strimatchlen((int)(stk_11c + 3),(int)&str_ko,2);
    if (i5 == 0) {
      i5 = strimatchlen((int)(stk_11c + 3),(int)&str_time,2);
      if (i5 == 0) {
        if (stk_11c[3] != '\0') {
          pb16 = (uint8_t *)(g + G_ERRMSG);
          fmt_args[0] = (void *)(stk_11c);
          pc17 = "Invalid win trigger: %s";
          goto L_080cccd9;
        }
        stk_3b8 = 0xffffffff;
      }
      else {
        stk_3b8 = 3;
      }
    }
    else {
      stk_3b8 = 1;
    }
  }
  if (stk_3dc[0] == 0x6e) {
    i5 = strimatchlen((int)stk_118,(int)&str_ko,2);
    if (i5 == 0) {
      i5 = strimatchlen((int)stk_118,(int)&str_time,2);
      if (i5 == 0) {
        if (stk_118[0] != '\0') {
          pb16 = (uint8_t *)(g + G_ERRMSG);
          fmt_args[0] = (void *)(stk_11c);
          pc17 = "Invalid lose trigger: %s";
          goto L_080cccd9;
        }
        stk_3b8 = 0xffffffff;
      }
      else {
        stk_3b8 = 3;
      }
    }
    else {
      stk_3b8 = 1;
    }
  }
  if (stk_3dc[0] == 0xb4) {
    if (text[(int)stk_7e8] != '(') {
      fmt_args[0] = (void *)(stk_11c);
      pc17 = "Need to specify gethitvar(varname): %s";
      pb16 = (uint8_t *)(g + G_ERRMSG);
      goto L_080cccd9;
    }
    stk_7e8 = stk_7e8 + 1;
    b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
    while ((b1 & 0x20) != 0) {
      stk_7e8 = stk_7e8 + 1;
      b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
    }
    i5 = 0;
    while( true ) {
      b1 = text[(int)stk_7e8];
      b13 = false;
      if (((*(uint8_t *)(__ctype_b + (char)b1 * 2) & 8) != 0) || (b1 == 0x5f)) {
        b13 = true;
      }
      if ((!b13) && (b1 != 0x2e)) break;
      stk_4dc[i5] = b1;
      i5 = i5 + 1;
      stk_7e8 = stk_7e8 + 1;
    }
    stk_4dc[i5] = 0;
    b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
    while ((b1 & 0x20) != 0) {
      stk_7e8 = stk_7e8 + 1;
      b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
    }
    if (text[(int)stk_7e8] != ')') {
      fmt_args[0] = (void *)(stk_11c);
      pc17 = "Missing closing parenthesis: %s";
      pb16 = (uint8_t *)(g + G_ERRMSG);
      goto L_080cccd9;
    }
    _alemu_strlwr((char *)stk_4dc);
    i5 = 8;
    b13 = 0;  /* dead flag (repz cmpsb, count 8) */
    b15 = 0;  /* dead flag (repz cmpsb, count 8) */
    pb16 = stk_4dc;
    pb9 = (uint8_t *)"xveladd";
    do {
      if (i5 == 0) break;
      i5 = i5 + -1;
      b13 = *pb16 < *pb9;
      b15 = *pb16 == *pb9;
      pb16 = pb16 + 1;
      pb9 = pb9 + 1;
    } while (b15);
    b14 = (!b13 && !b15) < b13;
    b13 = (!b13 && !b15) == b13;
    if (b13) {
      stk_3c0 = 0;
    }
    else {
      i5 = 8;
      pb16 = stk_4dc;
      pb9 = (uint8_t *)"yveladd";
      do {
        if (i5 == 0) break;
        i5 = i5 + -1;
        b14 = *pb16 < *pb9;
        b13 = *pb16 == *pb9;
        pb16 = pb16 + 1;
        pb9 = pb9 + 1;
      } while (b13);
      b15 = (!b14 && !b13) < b14;
      b13 = (!b14 && !b13) == b14;
      if (b13) {
        stk_3c0 = 1;
      }
      else {
        i5 = 5;
        pb16 = stk_4dc;
        pb9 = (uint8_t *)(int)&str_type;
        do {
          if (i5 == 0) break;
          i5 = i5 + -1;
          b15 = *pb16 < *pb9;
          b13 = *pb16 == *pb9;
          pb16 = pb16 + 1;
          pb9 = pb9 + 1;
        } while (b13);
        b14 = (!b15 && !b13) < b15;
        b13 = (!b15 && !b13) == b15;
        if (b13) {
          stk_3c0 = 2;
        }
        else {
          i5 = 9;
          pb16 = stk_4dc;
          pb9 = (uint8_t *)(int)&str_animtype;
          do {
            if (i5 == 0) break;
            i5 = i5 + -1;
            b14 = *pb16 < *pb9;
            b13 = *pb16 == *pb9;
            pb16 = pb16 + 1;
            pb9 = pb9 + 1;
          } while (b13);
          b15 = (!b14 && !b13) < b14;
          b13 = (!b14 && !b13) == b14;
          if (b13) {
            stk_3c0 = 3;
          }
          else {
            i5 = 8;
            pb16 = stk_4dc;
            pb9 = (uint8_t *)"airtype";
            do {
              if (i5 == 0) break;
              i5 = i5 + -1;
              b15 = *pb16 < *pb9;
              b13 = *pb16 == *pb9;
              pb16 = pb16 + 1;
              pb9 = pb9 + 1;
            } while (b13);
            b14 = (!b15 && !b13) < b15;
            b13 = (!b15 && !b13) == b15;
            if (b13) {
              stk_3c0 = 4;
            }
            else {
              i5 = 0xb;
              pb16 = stk_4dc;
              pb9 = (uint8_t *)"groundtype";
              do {
                if (i5 == 0) break;
                i5 = i5 + -1;
                b14 = *pb16 < *pb9;
                b13 = *pb16 == *pb9;
                pb16 = pb16 + 1;
                pb9 = pb9 + 1;
              } while (b13);
              b15 = (!b14 && !b13) < b14;
              b13 = (!b14 && !b13) == b14;
              if (b13) {
                stk_3c0 = 5;
              }
              else {
                i5 = 7;
                pb16 = stk_4dc;
                pb9 = (uint8_t *)(int)&str_damage;
                do {
                  if (i5 == 0) break;
                  i5 = i5 + -1;
                  b15 = *pb16 < *pb9;
                  b13 = *pb16 == *pb9;
                  pb16 = pb16 + 1;
                  pb9 = pb9 + 1;
                } while (b13);
                b14 = (!b15 && !b13) < b15;
                b13 = (!b15 && !b13) == b15;
                if (b13) {
                  stk_3c0 = 6;
                }
                else {
                  i5 = 9;
                  pb16 = stk_4dc;
                  pb9 = (uint8_t *)(int)&str_hitcount;
                  do {
                    if (i5 == 0) break;
                    i5 = i5 + -1;
                    b14 = *pb16 < *pb9;
                    b13 = *pb16 == *pb9;
                    pb16 = pb16 + 1;
                    pb9 = pb9 + 1;
                  } while (b13);
                  b15 = (!b14 && !b13) < b14;
                  b13 = (!b14 && !b13) == b14;
                  if (b13) {
                    stk_3c0 = 7;
                  }
                  else {
                    i5 = 10;
                    pb16 = stk_4dc;
                    pb9 = (uint8_t *)"fallcount";
                    do {
                      if (i5 == 0) break;
                      i5 = i5 + -1;
                      b15 = *pb16 < *pb9;
                      b13 = *pb16 == *pb9;
                      pb16 = pb16 + 1;
                      pb9 = pb9 + 1;
                    } while (b13);
                    b14 = (!b15 && !b13) < b15;
                    b13 = (!b15 && !b13) == b15;
                    if (b13) {
                      stk_3c0 = 8;
                    }
                    else {
                      i5 = 0xd;
                      pb16 = stk_4dc;
                      pb9 = (uint8_t *)"hitshaketime";
                      do {
                        if (i5 == 0) break;
                        i5 = i5 + -1;
                        b14 = *pb16 < *pb9;
                        b13 = *pb16 == *pb9;
                        pb16 = pb16 + 1;
                        pb9 = pb9 + 1;
                      } while (b13);
                      b15 = (!b14 && !b13) < b14;
                      b13 = (!b14 && !b13) == b14;
                      if (b13) {
                        stk_3c0 = 9;
                      }
                      else {
                        i5 = 8;
                        pb16 = stk_4dc;
                        pb9 = (uint8_t *)(int)&str_hittime;
                        do {
                          if (i5 == 0) break;
                          i5 = i5 + -1;
                          b15 = *pb16 < *pb9;
                          b13 = *pb16 == *pb9;
                          pb16 = pb16 + 1;
                          pb9 = pb9 + 1;
                        } while (b13);
                        b14 = (!b15 && !b13) < b15;
                        b13 = (!b15 && !b13) == b15;
                        if (b13) {
                          stk_3c0 = 10;
                        }
                        else {
                          i5 = 10;
                          pb16 = stk_4dc;
                          pb9 = (uint8_t *)(int)&str_slidetime;
                          do {
                            if (i5 == 0) break;
                            i5 = i5 + -1;
                            b14 = *pb16 < *pb9;
                            b13 = *pb16 == *pb9;
                            pb16 = pb16 + 1;
                            pb9 = pb9 + 1;
                          } while (b13);
                          b15 = (!b14 && !b13) < b14;
                          b13 = (!b14 && !b13) == b14;
                          if (b13) {
                            stk_3c0 = 0xb;
                          }
                          else {
                            i5 = 9;
                            pb16 = stk_4dc;
                            pb9 = (uint8_t *)(int)&str_ctrltime;
                            do {
                              if (i5 == 0) break;
                              i5 = i5 + -1;
                              b15 = *pb16 < *pb9;
                              b13 = *pb16 == *pb9;
                              pb16 = pb16 + 1;
                              pb9 = pb9 + 1;
                            } while (b13);
                            b14 = (!b15 && !b13) < b15;
                            b13 = (!b15 && !b13) == b15;
                            if (b13) {
                              stk_3c0 = 0xc;
                            }
                            else {
                              i5 = 0xc;
                              pb16 = stk_4dc;
                              pb9 = (uint8_t *)(int)&str_recovertime;
                              do {
                                if (i5 == 0) break;
                                i5 = i5 + -1;
                                b14 = *pb16 < *pb9;
                                b13 = *pb16 == *pb9;
                                pb16 = pb16 + 1;
                                pb9 = pb9 + 1;
                              } while (b13);
                              b15 = (!b14 && !b13) < b14;
                              b13 = (!b14 && !b13) == b14;
                              if (b13) {
                                stk_3c0 = 0xd;
                              }
                              else {
                                i5 = 5;
                                pb16 = stk_4dc;
                                pb9 = &str_xoff;
                                do {
                                  if (i5 == 0) break;
                                  i5 = i5 + -1;
                                  b15 = *pb16 < *pb9;
                                  b13 = *pb16 == *pb9;
                                  pb16 = pb16 + 1;
                                  pb9 = pb9 + 1;
                                } while (b13);
                                b14 = (!b15 && !b13) < b15;
                                b13 = (!b15 && !b13) == b15;
                                if (b13) {
                                  stk_3c0 = 0xe;
                                  stk_3c4 = 1;
                                }
                                else {
                                  i5 = 5;
                                  pb16 = stk_4dc;
                                  pb9 = &str_yoff;
                                  do {
                                    if (i5 == 0) break;
                                    i5 = i5 + -1;
                                    b14 = *pb16 < *pb9;
                                    b13 = *pb16 == *pb9;
                                    pb16 = pb16 + 1;
                                    pb9 = pb9 + 1;
                                  } while (b13);
                                  b15 = (!b14 && !b13) < b14;
                                  b13 = (!b14 && !b13) == b14;
                                  if (b13) {
                                    stk_3c0 = 0xf;
                                    stk_3c4 = 1;
                                  }
                                  else {
                                    i5 = 5;
                                    pb16 = stk_4dc;
                                    pb9 = &str_zoff;
                                    do {
                                      if (i5 == 0) break;
                                      i5 = i5 + -1;
                                      b15 = *pb16 < *pb9;
                                      b13 = *pb16 == *pb9;
                                      pb16 = pb16 + 1;
                                      pb9 = pb9 + 1;
                                    } while (b13);
                                    b14 = (!b15 && !b13) < b15;
                                    b13 = (!b15 && !b13) == b15;
                                    if (b13) {
                                      stk_3c0 = 0x10;
                                      stk_3c4 = 1;
                                    }
                                    else {
                                      i5 = 5;
                                      pb16 = stk_4dc;
                                      pb9 = (uint8_t *)(int)&str_xvel;
                                      do {
                                        if (i5 == 0) break;
                                        i5 = i5 + -1;
                                        b14 = *pb16 < *pb9;
                                        b13 = *pb16 == *pb9;
                                        pb16 = pb16 + 1;
                                        pb9 = pb9 + 1;
                                      } while (b13);
                                      b15 = (!b14 && !b13) < b14;
                                      b13 = (!b14 && !b13) == b14;
                                      if (b13) {
                                        stk_3c0 = 0x11;
                                        stk_3c4 = 1;
                                      }
                                      else {
                                        i5 = 5;
                                        pb16 = stk_4dc;
                                        pb9 = (uint8_t *)(int)&str_yvel;
                                        do {
                                          if (i5 == 0) break;
                                          i5 = i5 + -1;
                                          b15 = *pb16 < *pb9;
                                          b13 = *pb16 == *pb9;
                                          pb16 = pb16 + 1;
                                          pb9 = pb9 + 1;
                                        } while (b13);
                                        b14 = (!b15 && !b13) < b15;
                                        b13 = (!b15 && !b13) == b15;
                                        if (b13) {
                                          stk_3c0 = 0x12;
                                          stk_3c4 = 1;
                                        }
                                        else {
                                          i5 = 7;
                                          pb16 = stk_4dc;
                                          pb9 = (uint8_t *)(int)&str_yaccel;
                                          do {
                                            if (i5 == 0) break;
                                            i5 = i5 + -1;
                                            b14 = *pb16 < *pb9;
                                            b13 = *pb16 == *pb9;
                                            pb16 = pb16 + 1;
                                            pb9 = pb9 + 1;
                                          } while (b13);
                                          b15 = (!b14 && !b13) < b14;
                                          b13 = (!b14 && !b13) == b14;
                                          if (b13) {
                                            stk_3c0 = 0x13;
                                            stk_3c4 = 1;
                                          }
                                          else {
                                            i5 = 8;
                                            pb16 = stk_4dc;
                                            pb9 = (uint8_t *)(int)&str_chainid;
                                            do {
                                              if (i5 == 0) break;
                                              i5 = i5 + -1;
                                              b15 = *pb16 < *pb9;
                                              b13 = *pb16 == *pb9;
                                              pb16 = pb16 + 1;
                                              pb9 = pb9 + 1;
                                            } while (b13);
                                            b14 = (!b15 && !b13) < b15;
                                            b13 = (!b15 && !b13) == b15;
                                            if (b13) {
                                              stk_3c0 = 0x14;
                                            }
                                            else {
                                              i5 = 8;
                                              pb16 = stk_4dc;
                                              pb9 = (uint8_t *)(int)&str_guarded;
                                              do {
                                                if (i5 == 0) break;
                                                i5 = i5 + -1;
                                                b14 = *pb16 < *pb9;
                                                b13 = *pb16 == *pb9;
                                                pb16 = pb16 + 1;
                                                pb9 = pb9 + 1;
                                              } while (b13);
                                              b15 = (!b14 && !b13) < b14;
                                              b13 = (!b14 && !b13) == b14;
                                              if (b13) {
                                                stk_3c0 = 0x15;
                                              }
                                              else {
                                                i5 = 8;
                                                pb16 = stk_4dc;
                                                pb9 = (uint8_t *)"isbound";
                                                do {
                                                  if (i5 == 0) break;
                                                  i5 = i5 + -1;
                                                  b15 = *pb16 < *pb9;
                                                  b13 = *pb16 == *pb9;
                                                  pb16 = pb16 + 1;
                                                  pb9 = pb9 + 1;
                                                } while (b13);
                                                b14 = (!b15 && !b13) < b15;
                                                b13 = (!b15 && !b13) == b15;
                                                if (b13) {
                                                  stk_3c0 = 0x16;
                                                }
                                                else {
                                                  i5 = 5;
                                                  pb16 = stk_4dc;
                                                  pb9 = (uint8_t *)(int)&str_fall;
                                                  do {
                                                    if (i5 == 0) break;
                                                    i5 = i5 + -1;
                                                    b14 = *pb16 < *pb9;
                                                    b13 = *pb16 == *pb9;
                                                    pb16 = pb16 + 1;
                                                    pb9 = pb9 + 1;
                                                  } while (b13);
                                                  b15 = (!b14 && !b13) < b14;
                                                  b13 = (!b14 && !b13) == b14;
                                                  if (b13) {
                                                    stk_3c0 = 0x17;
                                                  }
                                                  else {
                                                    i5 = 0xc;
                                                    pb16 = stk_4dc;
                                                    pb9 = (uint8_t *)"fall.damage";
                                                    do {
                                                      if (i5 == 0) break;
                                                      i5 = i5 + -1;
                                                      b15 = *pb16 < *pb9;
                                                      b13 = *pb16 == *pb9;
                                                      pb16 = pb16 + 1;
                                                      pb9 = pb9 + 1;
                                                    } while (b13);
                                                    b14 = (!b15 && !b13) < b15;
                                                    b13 = (!b15 && !b13) == b15;
                                                    if (b13) {
                                                      stk_3c0 = 0x18;
                                                    }
                                                    else {
                                                      i5 = 10;
                                                      pb16 = stk_4dc;
                                                      pb9 = (uint8_t *)"fall.xvel";
                                                      do {
                                                        if (i5 == 0) break;
                                                        i5 = i5 + -1;
                                                        b14 = *pb16 < *pb9;
                                                        b13 = *pb16 == *pb9;
                                                        pb16 = pb16 + 1;
                                                        pb9 = pb9 + 1;
                                                      } while (b13);
                                                      b15 = (!b14 && !b13) < b14;
                                                      b13 = (!b14 && !b13) == b14;
                                                      if (b13) {
                                                        stk_3c0 = 0x19;
                                                        stk_3c4 = 1;
                                                      }
                                                      else {
                                                        i5 = 10;
                                                        pb16 = stk_4dc;
                                                        pb9 = (uint8_t *)"fall.yvel";
                                                        do {
                                                          if (i5 == 0) break;
                                                          i5 = i5 + -1;
                                                          b15 = *pb16 < *pb9;
                                                          b13 = *pb16 == *pb9;
                                                          pb16 = pb16 + 1;
                                                          pb9 = pb9 + 1;
                                                        } while (b13);
                                                        b14 = (!b15 && !b13) < b15;
                                                        b13 = (!b15 && !b13) == b15;
                                                        if (b13) {
                                                          stk_3c0 = 0x1a;
                                                          stk_3c4 = 1;
                                                        }
                                                        else {
                                                          i5 = 0xd;
                                                          pb16 = stk_4dc;
                                                          pb9 = (uint8_t *)"fall.recover";
                                                          do {
                                                            if (i5 == 0) break;
                                                            i5 = i5 + -1;
                                                            b14 = *pb16 < *pb9;
                                                            b13 = *pb16 == *pb9;
                                                            pb16 = pb16 + 1;
                                                            pb9 = pb9 + 1;
                                                          } while (b13);
                                                          b15 = (!b14 && !b13) < b14;
                                                          b13 = (!b14 && !b13) == b14;
                                                          if (b13) {
                                                            stk_3c0 = 0x1b;
                                                          }
                                                          else {
                                                            i5 = 10;
                                                            pb16 = stk_4dc;
                                                            pb9 = (uint8_t *)"fall.time";
                                                            do {
                                                              if (i5 == 0) break;
                                                              i5 = i5 + -1;
                                                              b15 = *pb16 < *pb9;
                                                              b13 = *pb16 == *pb9;
                                                              pb16 = pb16 + 1;
                                                              pb9 = pb9 + 1;
                                                            } while (b13);
                                                            b14 = (!b15 && !b13) < b15;
                                                            b13 = (!b15 && !b13) == b15;
                                                            if (b13) {
                                                              stk_3c0 = 0x1c;
                                                            }
                                                            else {
                                                              i5 = 0x11;
                                                              pb16 = stk_4dc;
                                                              pb9 = (uint8_t *)"fall.recovertime";
                                                              do {
                                                                if (i5 == 0) break;
                                                                i5 = i5 + -1;
                                                                b14 = *pb16 < *pb9;
                                                                b13 = *pb16 == *pb9;
                                                                pb16 = pb16 + 1;
                                                                pb9 = pb9 + 1;
                                                              } while (b13);
                                                              b15 = (!b14 && !b13) < b14
                                                              ;
                                                              b13 = (!b14 && !b13) ==
                                                                       b14;
                                                              if (b13) {
                                                                stk_3c0 = 0x1d;
                                                              }
                                                              else {
                                                                i5 = 10;
                                                                pb16 = stk_4dc;
                                                                pb9 = (uint8_t *)"fall.kill";
                                                                do {
                                                                  if (i5 == 0) break;
                                                                  i5 = i5 + -1;
                                                                  b15 = *pb16 < *pb9;
                                                                  b13 = *pb16 == *pb9;
                                                                  pb16 = pb16 + 1;
                                                                  pb9 = pb9 + 1;
                                                                } while (b13);
                                                                b14 = (!b15 && !b13) <
                                                                         b15;
                                                                b13 = (!b15 && !b13) ==
                                                                         b15;
                                                                if (b13) {
                                                                  stk_3c0 = 0x1e;
                                                                }
                                                                else {
                                                                  i5 = 0x13;
                                                                  pb16 = stk_4dc;
                                                                  pb9 = (uint8_t *)
                                                  "fall.envshake.time";
                                                  do {
                                                    if (i5 == 0) break;
                                                    i5 = i5 + -1;
                                                    b14 = *pb16 < *pb9;
                                                    b13 = *pb16 == *pb9;
                                                    pb16 = pb16 + 1;
                                                    pb9 = pb9 + 1;
                                                  } while (b13);
                                                  b15 = (!b14 && !b13) < b14;
                                                  b13 = (!b14 && !b13) == b14;
                                                  if (b13) {
                                                    stk_3c0 = 0x1f;
                                                  }
                                                  else {
                                                    i5 = 0x12;
                                                    pb16 = stk_4dc;
                                                    pb9 = (uint8_t *)"fall.envshake.dir";
                                                    do {
                                                      if (i5 == 0) break;
                                                      i5 = i5 + -1;
                                                      b15 = *pb16 < *pb9;
                                                      b13 = *pb16 == *pb9;
                                                      pb16 = pb16 + 1;
                                                      pb9 = pb9 + 1;
                                                    } while (b13);
                                                    b14 = (!b15 && !b13) < b15;
                                                    b13 = (!b15 && !b13) == b15;
                                                    if (b13) {
                                                      stk_3c0 = 0x20;
                                                    }
                                                    else {
                                                      i5 = 0x13;
                                                      pb16 = stk_4dc;
                                                      pb9 = (uint8_t *)"fall.envshake.ampl";
                                                      do {
                                                        if (i5 == 0) break;
                                                        i5 = i5 + -1;
                                                        b14 = *pb16 < *pb9;
                                                        b13 = *pb16 == *pb9;
                                                        pb16 = pb16 + 1;
                                                        pb9 = pb9 + 1;
                                                      } while (b13);
                                                      b15 = (!b14 && !b13) < b14;
                                                      b13 = (!b14 && !b13) == b14;
                                                      if (b13) {
                                                        stk_3c0 = 0x21;
                                                      }
                                                      else {
                                                        i5 = 0x13;
                                                        pb16 = stk_4dc;
                                                        pb9 = (uint8_t *)"fall.envshake.freq";
                                                        do {
                                                          if (i5 == 0) break;
                                                          i5 = i5 + -1;
                                                          b15 = *pb16 < *pb9;
                                                          b13 = *pb16 == *pb9;
                                                          pb16 = pb16 + 1;
                                                          pb9 = pb9 + 1;
                                                        } while (b13);
                                                        b14 = (!b15 && !b13) < b15;
                                                        b13 = (!b15 && !b13) == b15;
                                                        if (b13) {
                                                          stk_3c0 = 0x22;
                                                          stk_3c4 = 1;
                                                        }
                                                        else {
                                                          i5 = 0x14;
                                                          pb16 = stk_4dc;
                                                          pb9 = (uint8_t *)"fall.envshake.phase";
                                                          do {
                                                            if (i5 == 0) break;
                                                            i5 = i5 + -1;
                                                            b14 = *pb16 < *pb9;
                                                            b13 = *pb16 == *pb9;
                                                            pb16 = pb16 + 1;
                                                            pb9 = pb9 + 1;
                                                          } while (b13);
                                                          if ((!b14 && !b13) != b14) {
                                                            pb16 = (uint8_t *)(g + G_ERRMSG);
                                                            fmt_args[0] = (void *)(stk_4dc);
                                                            fmt_args[1] = (void *)(stk_11c);
                                                            pc17 = "Invalid varname %s in: %s";
                                                            goto L_080cccd9;
                                                          }
                                                          stk_3c0 = 0x23;
                                                          stk_3c4 = 1;
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
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    stk_7e8 = stk_7e8 + 1;
  }
  if (stk_3dc[0] == 0xb5) {
    if (text[(int)stk_7e8] != '(') {
      fmt_args[0] = (void *)(stk_11c);
      pc17 = "Need to specify const(varname): %s";
      pb16 = (uint8_t *)(g + G_ERRMSG);
      goto L_080cccd9;
    }
    stk_7e8 = stk_7e8 + 1;
    b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
    while ((b1 & 0x20) != 0) {
      stk_7e8 = stk_7e8 + 1;
      b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
    }
    i5 = 0;
    while( true ) {
      c6 = text[(int)stk_7e8];
      b13 = false;
      if (((*(uint8_t *)(__ctype_b + c6 * 2) & 8) != 0) || (c6 == '_')) {
        b13 = true;
      }
      if ((!b13) && (c6 != '.')) break;
      stk_5dc[i5] = c6;
      i5 = i5 + 1;
      stk_7e8 = stk_7e8 + 1;
    }
    stk_5dc[i5] = '\0';
    b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
    while ((b1 & 0x20) != 0) {
      stk_7e8 = stk_7e8 + 1;
      b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
    }
    if (text[(int)stk_7e8] == '\0') {
      fmt_args[0] = (void *)(stk_11c);
      pc17 = "Missing closing parenthesis: %s";
      pb16 = (uint8_t *)(g + G_ERRMSG);
      goto L_080cccd9;
    }
    u10 = 0;
    _alemu_strlwr(stk_5dc);
    i5 = 0;
    do {
      i3 = strcmp(stk_5dc,*(char **)((int)CnstName + i5));
      if (i3 == 0) {
        stk_3c0 = u10;
        stk_3c4 = (uint32_t)(*(int *)((int)CnstType + i5) == 1);
        break;
      }
      u10 = u10 + 1;
      i5 = i5 + 4;
    } while ((int)u10 < 0x42);
    if (u10 == 0x42) {
      fmt_args[0] = (void *)(stk_5dc);
      fmt_args[1] = (void *)(stk_11c);
      pc17 = "Invalid cnstname %s in: %s";
      pb16 = (uint8_t *)(g + G_ERRMSG);
      goto L_080cccd9;
    }
    stk_7e8 = stk_7e8 + 1;
  }
  if (stk_3dc[0] == 0xb6) {
    if (text[(int)stk_7e8] == '(') {
      stk_7e8 = stk_7e8 + 1;
      b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
      while ((b1 & 0x20) != 0) {
        stk_7e8 = stk_7e8 + 1;
        b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
      }
      i5 = 0;
      while( true ) {
        c6 = text[(int)stk_7e8];
        b13 = false;
        if (((*(uint8_t *)(__ctype_b + c6 * 2) & 8) != 0) || (c6 == '_')) {
          b13 = true;
        }
        if ((!b13) && (c6 != '.')) break;
        stk_6dc[i5] = c6;
        i5 = i5 + 1;
        stk_7e8 = stk_7e8 + 1;
      }
      stk_6dc[i5] = '\0';
      b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
      while ((b1 & 0x20) != 0) {
        stk_7e8 = stk_7e8 + 1;
        b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
      }
      if (text[(int)stk_7e8] != '\0') {
        _alemu_strlwr(stk_6dc);
        sprintf((char *)(g + G_ERRMSG),"Invalid varname %s in: %s",stk_6dc,stk_11c);
        return (char *)0x0;
      }
      fmt_args[0] = (void *)(stk_11c);
      pc17 = "Missing closing parenthesis: %s";
      pb16 = (uint8_t *)(g + G_ERRMSG);
    }
    else {
      fmt_args[0] = (void *)(stk_11c);
      pc17 = "Need to specify stagevar(varname): %s";
      pb16 = (uint8_t *)(g + G_ERRMSG);
    }
    goto L_080cccd9;
  }
  if (2 < stk_3dc[0] - 0xb4U) {
    stk_3c4 = 0;
  }
  if (stk_3dc[0] == 0x67) goto L_080cc280;
  if (stk_3dc[0] < 0x68) {
    if (stk_3dc[0] == 7) {
L_080cc340:
      c6 = text[(int)stk_7e8];
      while ((c6 != '\0' && (c6 != '='))) {
        stk_7e8 = stk_7e8 + 1;
        c6 = text[(int)stk_7e8];
      }
      if (c6 != '\0') {
        stk_7e8 = stk_7e8 + 1;
      }
      b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
      while ((b1 & 0x20) != 0) {
        stk_7e8 = stk_7e8 + 1;
        b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
      }
      if (9 < (uint8_t)(text[(int)stk_7e8] - 0x30U)) {
        return (char *)0x0;
      }
      stk_3b8 = __strtol_internal((uint8_t *)(text + (int)stk_7e8),(uint32_t *)0x0,10,0);
      if (stk_3dc[0] == 2) {
        stk_3b8 = stk_3b8 - 1;
      }
      if ((int)stk_3b8 < 0) {
        if (stk_3dc[0] != 2) {
          return (char *)0x0;
        }
        pb16 = (uint8_t *)(g + G_ERRMSG);
        pc17 = "Anim must be > 0";
        goto L_080cccd9;
      }
      if ((stk_3dc[0] == 7) && ((int)stk_3b8 < 1)) {
        return (char *)0x0;
      }
      i5 = (int)text[(int)stk_7e8];
      u2 = *(uint16_t *)(__ctype_b + i5 * 2);
      while ((u2 & 0x2800) != 0) {
        stk_7e8 = stk_7e8 + 1;
        i5 = (int)text[(int)stk_7e8];
        u2 = *(uint16_t *)(__ctype_b + i5 * 2);
      }
      if (text[(int)stk_7e8] == ',') {
        stk_7e8 = stk_7e8 + 1;
        i5 = (int)text[(int)stk_7e8];
      }
    }
    else {
      if (stk_3dc[0] < 8) {
        if (stk_3dc[0] == 2) goto L_080cc340;
        if (stk_3dc[0] < 2) goto L_080cc622;
        if (stk_3dc[0] < 4) goto L_080cc600;
      }
      else if (9 < stk_3dc[0]) {
        if (stk_3dc[0] < 0x41) {
          if (stk_3dc[0] < 0x3e) goto L_080cc600;
          for (; (c6 = text[(int)stk_7e8], c6 != '\0' && (c6 != '='));
              stk_7e8 = stk_7e8 + 1) {
          }
          if (c6 != '\0') {
            stk_7e8 = stk_7e8 + 1;
          }
          i5 = (int)text[(int)stk_7e8];
          b1 = *(uint8_t *)(__ctype_b + 1 + i5 * 2);
          while ((b1 & 0x20) != 0) {
            stk_7e8 = stk_7e8 + 1;
            i5 = (int)text[(int)stk_7e8];
            b1 = *(uint8_t *)(__ctype_b + 1 + i5 * 2);
          }
          if ((*(uint8_t *)(__ctype_b + 1 + i5 * 2) & 8) == 0) {
            return (char *)0x0;
          }
          stk_3b4 = __strtol_internal((uint8_t *)(text + (int)stk_7e8),(uint32_t *)0x0,10,0);
          u2 = *(uint16_t *)(__ctype_b + text[(int)stk_7e8] * 2);
          while ((u2 & 0x2800) != 0) {
            stk_7e8 = stk_7e8 + 1;
            u2 = *(uint16_t *)(__ctype_b + text[(int)stk_7e8] * 2);
          }
          if (text[(int)stk_7e8] != ',') goto L_080cc622;
          stk_7e8 = stk_7e8 + 1;
          i5 = (int)text[(int)stk_7e8];
        }
        else {
L_080cc622:
          i5 = (int)text[(int)stk_7e8];
        }
        goto L_080cc626;
      }
L_080cc280:
      stk_3c4 = 1;
      i5 = (int)text[(int)stk_7e8];
      b1 = *(uint8_t *)(__ctype_b + 1 + i5 * 2);
      while ((b1 & 0x20) != 0) {
        stk_7e8 = stk_7e8 + 1;
        i5 = (int)text[(int)stk_7e8];
        b1 = *(uint8_t *)(__ctype_b + 1 + i5 * 2);
      }
      i5 = *(int *)(__ctype_tolower + i5 * 4);
      if (i5 == 0x79) {
        stk_3c0 = 1;
      }
      else if (i5 < 0x7a) {
        if (i5 != 0x78) {
          return (char *)0x0;
        }
        stk_3c0 = 0;
      }
      else {
        if (i5 != 0x7a) {
          return (char *)0x0;
        }
        stk_3c0 = 2;
      }
      stk_7e8 = stk_7e8 + 1;
      i5 = (int)text[(int)stk_7e8];
    }
  }
  else {
    if (stk_3dc[0] != 0x136) {
      if (stk_3dc[0] < 0x137) {
        if (0xca < stk_3dc[0]) {
          if (stk_3dc[0] < 0xcd) goto L_080cc280;
          if (0x12d < stk_3dc[0]) goto L_080cc600;
          if (299 < stk_3dc[0]) goto L_080cc25c;
        }
        goto L_080cc622;
      }
      if (stk_3dc[0] != 0x158) {
        if (stk_3dc[0] < 0x159) {
          if (stk_3dc[0] < 0x148) {
            if (stk_3dc[0] < 0x140) goto L_080cc622;
            goto L_080cc25c;
          }
        }
        else if (stk_3dc[0] == 0x15a) goto L_080cc25c;
L_080cc600:
        i5 = (int)text[(int)stk_7e8];
        goto L_080cc626;
      }
    }
L_080cc25c:
    stk_3c4 = 1;
    i5 = (int)text[(int)stk_7e8];
  }
L_080cc626:
  b1 = *(uint8_t *)(__ctype_b + 1 + i5 * 2);
  while ((b1 & 0x20) != 0) {
    stk_7e8 = stk_7e8 + 1;
    b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
  }
  pc17 = text + (int)stk_7e8;
  *arg6 = (int)pc17;
  if (stk_3dc[0] == 0x14) {
    c6 = *pc17;
    while ((c6 != '\0' && (c6 != '='))) {
      stk_7e8 = stk_7e8 + 1;
      c6 = text[(int)stk_7e8];
    }
    stk_3c8 = (uint32_t)((text + (int)stk_7e8)[-1] == '!');
    if (text[(int)stk_7e8] != '\0') {
      stk_7e8 = stk_7e8 + 1;
    }
    b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
    while ((b1 & 0x20) != 0) {
      stk_7e8 = stk_7e8 + 1;
      b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
    }
    if (text[(int)stk_7e8] != '\"') {
      return (char *)0x0;
    }
    i5 = SCtrlParseTriggerCMD(text + (int)(stk_7e8 + 1),(int)stk_3dc,player,arg6);
    if (i5 == 0) {
      pc17 = "Couldn\'t parse command.";
      pb16 = ErrorMessage;
L_080cccd9:
      sprintf((char *)pb16,pc17,fmt_args[0],fmt_args[1]);
      return (char *)0x0;
    }
    if (*(char *)*arg6 != '\"') {
      return (char *)0x0;
    }
    *arg6 = (int)((char *)*arg6 + 1);
    goto L_080cce5b;
  }
  if (stk_3dc[0] - 0x5aU < 5) {
    stk_3c8 = 0;
    c6 = *pc17;
    while ((c6 != '\0' && (c6 != '='))) {
      stk_7e8 = stk_7e8 + 1;
      c6 = text[(int)stk_7e8];
    }
    if ((0 < (int)stk_7e8) && (text[(int)(stk_7e8 + -1)] == '!')) {
      stk_3c8 = 1;
    }
    if (text[(int)stk_7e8] != '\0') {
      stk_7e8 = stk_7e8 + 1;
    }
    b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
    while ((b1 & 0x20) != 0) {
      stk_7e8 = stk_7e8 + 1;
      b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
    }
    if (text[(int)stk_7e8] != '\"') {
      return (char *)0x0;
    }
    stk_7e8 = stk_7e8 + 1;
    c6 = text[(int)stk_7e8];
    stk_7e4 = stk_7e8;
    while ((c6 != '\0' && (c6 != '\"'))) {
      stk_7e4 = stk_7e4 + 1;
      c6 = text[(int)stk_7e4];
    }
    if (text[(int)stk_7e4] != '\"') {
      return (char *)0x0;
    }
    mem2 = (char *)ecalloc(1,(size_t)(stk_7e4 + (1 - (int)stk_7e8)));
    if (mem2 == (char *)0x0) {
      return (char *)0x0;
    }
    strncpy(mem2,text + (int)stk_7e8,(int)stk_7e4 - (int)stk_7e8);
    mem2[(int)stk_7e4 - (int)stk_7e8] = '\0';
    stk_3c0 = 1;
    *arg6 = (int)(text + (int)(stk_7e4 + 1));
    goto L_080cce5b;
  }
  if (stk_3dc[0] - 0x2bU < 2) {
    stk_3c8 = 0;
    c6 = *pc17;
    while ((c6 != '\0' && (c6 != '='))) {
      stk_7e8 = stk_7e8 + 1;
      c6 = text[(int)stk_7e8];
    }
    b13 = (text + (int)stk_7e8)[-1] == '!';
    if (b13) {
      stk_3c8 = 1;
    }
    stk_3c8 = (uint32_t)b13;
    if (text[(int)stk_7e8] != '\0') {
      stk_7e8 = stk_7e8 + 1;
    }
    i5 = (int)text[(int)stk_7e8];
    b1 = *(uint8_t *)(__ctype_b + 1 + i5 * 2);
    while ((b1 & 0x20) != 0) {
      stk_7e8 = stk_7e8 + 1;
      i5 = (int)text[(int)stk_7e8];
      b1 = *(uint8_t *)(__ctype_b + 1 + i5 * 2);
    }
    i5 = *(int *)(__ctype_tolower + i5 * 4);
    if (i5 == 99) {
L_080ccaf0:
      stk_3c0 = 2;
    }
    else if (i5 < 100) {
      if (i5 != 0x61) {
        return (char *)0x0;
      }
      stk_3c0 = 3;
    }
    else {
      if (i5 != 0x6c) {
        if (i5 != 0x73) {
          return (char *)0x0;
        }
        goto L_080ccad0;
      }
      stk_3c0 = 4;
    }
  }
  else {
    if (1 < stk_3dc[0] - 0x2dU) {
      if (stk_3dc[0] == 0x79) {
        c6 = *pc17;
        while ((c6 != '\0' && (c6 != '='))) {
          stk_7e8 = stk_7e8 + 1;
          c6 = text[(int)stk_7e8];
        }
        stk_3c8 = (uint32_t)((text + (int)stk_7e8)[-1] == '!');
        if (text[(int)stk_7e8] != '\0') {
          stk_7e8 = stk_7e8 + 1;
        }
        b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
        while ((b1 & 0x20) != 0) {
          stk_7e8 = stk_7e8 + 1;
          b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
        }
        c6 = text[(int)stk_7e8];
        stk_7e4 = stk_7e8;
        if ((((c6 != '\0') && ((*(uint8_t *)(__ctype_b + 1 + c6 * 2) & 0x20) == 0)) &&
            (c6 != ',')) && (c6 != ')')) {
          while( true ) {
            stk_7e4 = stk_7e4 + 1;
            c6 = text[(int)stk_7e4];
            if ((c6 == '\0') || ((*(uint8_t *)(__ctype_b + 1 + c6 * 2) & 0x20) != 0)) break;
            if ((c6 == ',') || (c6 == ')')) break;
          }
        }
        strncpy((char *)stk_7dc,text + (int)stk_7e8,(int)stk_7e4 - (int)stk_7e8);
        stk_7dc[(int)stk_7e4 - (int)stk_7e8] = 0;
        _alemu_strlwr((char *)stk_7dc);
        i5 = 7;
        b13 = 0;  /* dead flag (repz cmpsb, count 7) */
        b15 = 0;  /* dead flag (repz cmpsb, count 7) */
        pb16 = stk_7dc;
        pb9 = (uint8_t *)"single";
        do {
          if (i5 == 0) break;
          i5 = i5 + -1;
          b13 = *pb16 < *pb9;
          b15 = *pb16 == *pb9;
          pb16 = pb16 + 1;
          pb9 = pb9 + 1;
        } while (b15);
        b14 = (!b13 && !b15) < b13;
        b13 = (!b13 && !b15) == b13;
        if (b13) {
          stk_3c0 = 0;
        }
        else {
          i5 = 6;
          pb16 = stk_7dc;
          pb9 = (uint8_t *)"simul";
          do {
            if (i5 == 0) break;
            i5 = i5 + -1;
            b14 = *pb16 < *pb9;
            b13 = *pb16 == *pb9;
            pb16 = pb16 + 1;
            pb9 = pb9 + 1;
          } while (b13);
          b15 = (!b14 && !b13) < b14;
          b13 = (!b14 && !b13) == b14;
          if (b13) {
            stk_3c0 = 1;
          }
          else {
            i5 = 6;
            pb16 = stk_7dc;
            pb9 = (uint8_t *)"turns";
            do {
              if (i5 == 0) break;
              i5 = i5 + -1;
              b15 = *pb16 < *pb9;
              b13 = *pb16 == *pb9;
              pb16 = pb16 + 1;
              pb9 = pb9 + 1;
            } while (b13);
            if ((!b15 && !b13) != b15) {
              pb16 = (uint8_t *)(g + G_ERRMSG);
              fmt_args[0] = (void *)(text + (int)stk_7e8);
              fmt_args[1] = (void *)(stk_11c);
              pc17 = "Invalid TeamMode %s in %s";
              goto L_080cccd9;
            }
            stk_3c0 = 3;
          }
        }
        *arg6 = (int)(text + (int)stk_7e4);
        goto L_080cce5b;
      }
      if (stk_3dc[0] == 0x30) {
        c6 = *pc17;
        while ((c6 != '\0' && (c6 != '='))) {
          stk_7e8 = stk_7e8 + 1;
          c6 = text[(int)stk_7e8];
        }
        stk_3c8 = (uint32_t)((text + (int)stk_7e8)[-1] == '!');
        if (text[(int)stk_7e8] != '\0') {
          stk_7e8 = stk_7e8 + 1;
        }
        b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
        while ((b1 & 0x20) != 0) {
          stk_7e8 = stk_7e8 + 1;
          b1 = *(uint8_t *)(__ctype_b + 1 + text[(int)stk_7e8] * 2);
        }
        stk_3c0 = ParseHitAttr((int)(text + (int)stk_7e8),(int)arg6);
        i5 = stk_3c0 + 1;
      }
      else {
        if (stk_3dc[0] != 7) {
          if (stk_3dc[0] < 8) {
            if (stk_3dc[0] != 2) goto L_080cce5b;
          }
          else if ((0x40 < stk_3dc[0]) || (stk_3dc[0] < 0x3e)) goto L_080cce5b;
          i5 = SCtrlParseTriggerRange(text + (int)stk_7e8,(int)stk_3dc,arg6);
          if (i5 == 0) {
            stk_3c8 = 10;
            stk_3bc = 0;
            stk_3c0 = 0;
          }
          goto L_080cce5b;
        }
        i5 = SCtrlParseTriggerRange(pc17,(int)stk_3dc,arg6);
      }
      if (i5 == 0) {
        return (char *)0x0;
      }
      goto L_080cce5b;
    }
    stk_3c8 = 0;
    c6 = *pc17;
    while ((c6 != '\0' && (c6 != '='))) {
      stk_7e8 = stk_7e8 + 1;
      c6 = text[(int)stk_7e8];
    }
    b13 = (text + (int)stk_7e8)[-1] == '!';
    if (b13) {
      stk_3c8 = 1;
    }
    stk_3c8 = (uint32_t)b13;
    if (text[(int)stk_7e8] != '\0') {
      stk_7e8 = stk_7e8 + 1;
    }
    i5 = (int)text[(int)stk_7e8];
    b1 = *(uint8_t *)(__ctype_b + 1 + i5 * 2);
    while ((b1 & 0x20) != 0) {
      stk_7e8 = stk_7e8 + 1;
      i5 = (int)text[(int)stk_7e8];
      b1 = *(uint8_t *)(__ctype_b + 1 + i5 * 2);
    }
    i5 = *(int *)(__ctype_tolower + i5 * 4);
    if (i5 == 0x68) goto L_080ccaf0;
    if (i5 < 0x69) {
      if (i5 != 0x61) {
        return (char *)0x0;
      }
L_080ccad0:
      stk_3c0 = 1;
    }
    else {
      if (i5 != 0x69) {
        return (char *)0x0;
      }
      stk_3c0 = 0;
    }
  }
  *arg6 = (int)(text + (int)(stk_7e8 + 1));
L_080cce5b:
  if (arg5 < (int)(stk_7ec + 1)) {
    return (char *)0x0;
  }
  pu7 = stk_31c;
  pu11 = arg3;
  for (u10 = (uint32_t)stk_7ec & 0x3fffffff; u10 != 0; u10 = u10 - 1) {
    *pu11 = *pu7;
    pu7 = pu7 + 1;
    pu11 = pu11 + 1;
  }
  memcpy(arg4,stk_39c,(size_t)stk_7ec);
  mem = (int *)ecalloc(1,0x38);
  pi8 = stk_3dc;
  pi12 = mem;
  for (i5 = 0xe; i5 != 0; i5 = i5 + -1) {
    *pi12 = *pi8;
    pi8 = pi8 + 1;
    pi12 = pi12 + 1;
  }
  arg3[(int)stk_7ec] = mem;
  stk_7ec[(int)arg4] = '\x03';
  return stk_7ec + 1;
}
#undef stk_7ec
#undef stk_7e8
#undef stk_7e4
#undef stk_7e0
#undef stk_7dc
#undef stk_6dc
#undef stk_5dc
#undef stk_4dc
#undef stk_3dc
#undef stk_3c8
#undef stk_3c4
#undef stk_3c0
#undef stk_3bc
#undef stk_3b8
#undef stk_3b4
#undef mem2
#undef stk_39c
#undef stk_31c
#undef stk_11c
#undef stk_118
#undef stk_115
#undef stk_111

/* SCtrlParseTriggerCMD @ 0x080ccef0, 199 bytes
 *
 * Compiles the argument of a `command = "name"` trigger: copies the quoted
 * command name and looks it up in the player's command list, storing its
 * index. An unknown name is an error.
 *
 * Parameters:
 *   arg1         char *
 *   arg2         int
 *   arg3         int
 *   arg4         uint32_t *
 * Messages:
 *   "') break;       stk_5c[i6] = c1;       i6 = i6 + 1;       c1 =
 *     arg1[i6];       pc5 = stk_5c;       entry_ECX = stk_5c;     } while
 *     (c1 != '\0');     stk_5c[i6] = '\0';     i3 = 0;     i6 = *(int
 *     *)(arg3 + 0x11bc);     if (0 < i6) {       i2 = *(int *)(arg3 +
 *     0x11b8);       do {         i4 = strcmp(*(char **)(i2 + i3 *
 *     4),stk_5c);         if (i4 == 0) {           pc5 = *(char **)(i2 + i3
 *     * 4);           *(uint32_t *)(arg2 + 0x1c) =                *(uint32_t
 *     *)(*(int *)(arg3 + 0x11b4) + 0x10 + i3 * 0x18);           s3 =
 *     strlen(pc5);           *arg4 = arg1 + s3;           return 1;
 *     }         i3 = i3 + 1;         pc5 = stale_ECX;       } while (i3 <
 *     i6);     }     sprintf((char *)(g + G_ERRMSG),             "
 *   "%s\".\nIf not misspelling in CNS, check CMD"
 *
 * Elecbyte file: src/mugen/st-trig.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x60 bytes, 1
 *       variables), because their address is taken.
 */
uint32_t SCtrlParseTriggerCMD(char *arg1,int arg2,int arg3,uint32_t *arg4)

{
  char c1;
  int i2;
  size_t s3;
  int i4;
  char *entry_ECX;
  uint8_t *stale_ECX;
  char *pc5;
  int i6;
  int i3;
  unsigned char frame[0x60] __attribute__((aligned(16)));
#define stk_5c (*(char (*)[76])(frame + 0x4))
  
  c1 = *arg1;
  if (c1 != '\0') {
    i6 = 0;
    do {
      pc5 = entry_ECX;
      if (c1 == '\"') break;
      stk_5c[i6] = c1;
      i6 = i6 + 1;
      c1 = arg1[i6];
      pc5 = stk_5c;
      entry_ECX = stk_5c;
    } while (c1 != '\0');
    stk_5c[i6] = '\0';
    i3 = 0;
    i6 = *(int *)(arg3 + 0x11bc);
    if (0 < i6) {
      i2 = *(int *)(arg3 + 0x11b8);
      do {
        i4 = strcmp(*(char **)(i2 + i3 * 4),stk_5c);
        if (i4 == 0) {
          pc5 = *(char **)(i2 + i3 * 4);
          *(uint32_t *)(arg2 + 0x1c) =
               *(uint32_t *)(*(int *)(arg3 + 0x11b4) + 0x10 + i3 * 0x18);
          s3 = strlen(pc5);
          *arg4 = arg1 + s3;
          return 1;
        }
        i3 = i3 + 1;
        pc5 = stale_ECX;
      } while (i3 < i6);
    }
    sprintf((char *)(g + G_ERRMSG),
            "Undefined command label: \"%s\".\nIf not misspelling in CNS, check CMD",stk_5c,pc5
           );
  }
  return 0;
}
#undef stk_5c

/* SCtrlParseTriggerRange @ 0x080ccfc0, 737 bytes
 *
 * Parses an interval argument ("[a, b]", "(a, b)", half-open forms) of a
 * trigger comparison.
 *
 * Parameters:
 *   arg1         char *
 *   arg2         int
 *   arg3         int *
 *
 * C library: __strtol_internal, __strtod_internal
 * Called by: SCtrlParseTrigger
 *
 * Elecbyte file: src/mugen/st-trig.c
 * Note: decompiler flag: type propagation did not settle
 */
uint32_t SCtrlParseTriggerRange(char *arg1,int arg2,int *arg3)

{
  uint32_t u1;
  char c2;
  char c3;
  int i4;
  int i5;
  int i6;
  float80 l7;
  
  i4 = 0;
  i5 = (int)*arg1;
  c3 = arg1[1];
  c2 = *arg1;
  if (c2 != '\0') {
    if (((*(uint8_t *)(__ctype_b + 1 + i5 * 2) & 8) != 0) || (i6 = i5, i5 == 0x2d)) {
      i6 = 0x3d;
    }
    if (((c2 == '\0') || ((*(uint8_t *)(__ctype_b + 1 + i5 * 2) & 8) != 0)) || (c2 == '-')) {
      c2 = *arg1;
    }
    else {
      do {
        i4 = i4 + 1;
        if (i6 == 0x3d) {
          c2 = arg1[i4];
          if (c2 == '(') {
            i6 = 0x28;
          }
        }
        else {
          c2 = arg1[i4];
        }
        if ((i6 == 0x3d) && (c2 == '[')) {
          i6 = 0x5b;
        }
      } while (((c2 != '\0') && ((*(uint8_t *)(__ctype_b + 1 + arg1[i4] * 2) & 8) == 0)) &&
              (c2 != '-'));
    }
    if (c2 == '\0') {
      return 0;
    }
    switch(i6) {
    case 0x21:
      if (c3 != '=') {
        return 0;
      }
      i5 = *(int *)(arg2 + 0x18);
      *(uint32_t *)(arg2 + 0x14) = 1;
      break;
    default:
      goto L_080cd299;
    case 0x28:
    case 0x5b:
      if (*(int *)(arg2 + 0x18) == 0) {
        u1 = __strtol_internal((uint8_t *)(arg1 + i4),(uint32_t *)0x0,10,0);
        *(uint32_t *)(arg2 + 0x1c) = u1;
      }
      else {
        l7 = __strtod_internal((int)(arg1 + i4),(int *)0x0,0);
        *(float *)(arg2 + 0x2c) = (float)l7;
      }
      for (; (c3 = arg1[i4], c3 != '\0' && (c3 != ',')); i4 = i4 + 1) {
      }
      while (((c3 != '\0' && (9 < (uint8_t)(c3 - 0x30U))) && (c3 != '-'))) {
        i4 = i4 + 1;
        c3 = arg1[i4];
      }
      if (*(int *)(arg2 + 0x18) == 0) {
        u1 = __strtol_internal((uint8_t *)(arg1 + i4),(uint32_t *)0x0,10,0);
        *(uint32_t *)(arg2 + 0x20) = u1;
      }
      else {
        l7 = __strtod_internal((int)(arg1 + i4),(int *)0x0,0);
        *(float *)(arg2 + 0x30) = (float)l7;
      }
      for (; ((c3 = arg1[i4], c3 != '\0' && (c3 != ')')) && (c3 != ']'));
          i4 = i4 + 1) {
      }
      c3 = arg1[i4];
      *arg3 = (int)(arg1 + i4 + 1);
      if ((i6 == 0x5b) && (c3 == ']')) {
        *(uint32_t *)(arg2 + 0x14) = 10;
        return 1;
      }
      if ((i6 == 0x5b) && (c3 == ')')) {
        *(uint32_t *)(arg2 + 0x14) = 0xb;
        return 1;
      }
      if ((i6 == 0x28) && (c3 == ']')) {
        *(uint32_t *)(arg2 + 0x14) = 0xc;
        return 1;
      }
      if (i6 != 0x28) {
        return 0;
      }
      if (c3 == ')') {
        *(uint32_t *)(arg2 + 0x14) = 0xd;
        return 1;
      }
      return 0;
    case 0x3c:
      *(uint32_t *)(arg2 + 0x14) = (c3 == '=') + 4;
      i5 = *(int *)(arg2 + 0x18);
      break;
    case 0x3d:
      i5 = *(int *)(arg2 + 0x18);
      *(uint32_t *)(arg2 + 0x14) = 0;
      break;
    case 0x3e:
      i5 = *(int *)(arg2 + 0x18);
      *(uint32_t *)(arg2 + 0x14) = (c3 == '=') + 2;
    }
    if (i5 == 0) {
      u1 = __strtol_internal((uint8_t *)(arg1 + i4),arg3,10,0);
      *(uint32_t *)(arg2 + 0x1c) = u1;
    }
    else {
      l7 = __strtod_internal((int)(arg1 + i4),arg3,0);
      *(float *)(arg2 + 0x2c) = (float)l7;
    }
    return 1;
  }
L_080cd299:
  return 0;
}

/* SCtrlTrigArity @ 0x080cd2b0, 50 bytes
 *
 * Returns how many arguments a trigger code takes from the expression stack
 * (1 for the codes 0x140-0x15c, 2 for 0x136, 3 for 0x131, else 0).
 *
 * Parameters:
 *   trigger      int
 *
 * Called by: InfToPostArray, SCtrlTrigEval
 *
 * Elecbyte file: src/mugen/st-trig.c
 */
char SCtrlTrigArity(int trigger)

{
  if (trigger - 0x140U < 0x1d) {
    return '\x01';
  }
  if (trigger == 0x136) {
    return '\x02';
  }
  return (trigger == 0x131) * '\x03';
}

/* SCtrlTrigArrayTest @ 0x080cd2f0, 197 bytes
 *
 * Tests a state controller's triggers: every "triggerall" expression must be
 * true, and at least one numbered trigger group must have all its
 * expressions true. Returns true if the controller should run.
 *
 * Parameters:
 *   player       int *
 *   triggers     int
 *   num_groups   int
 *
 * Globals read: errmsg
 * Calls: ArrayAccessGrpItem, SCtrlTrigTest, ErrorExit
 * C library: memcpy
 * Called by: PlayerSCtrlUpdate, PlayerSCtrlUpdateSpec
 * Messages:
 *   "TrigArrayTest bug"
 *
 * Elecbyte file: src/mugen/st-trig.c
 * Note: 2 byte results widened with ZEXT8 (upper bytes are zero).
 */
uint32_t SCtrlTrigArrayTest(int *player,int triggers,int num_groups)

{
  bool b1;
  uint32_t stale_var;
  int *item;
  uint32_t stale_var_00;
  int i3;
  int i2;
  
  i2 = 0;
  while (item = (int *)ArrayAccessGrpItem(triggers,-1,i2), item != (int *)0x0) {
    b1 = SCtrlTrigTest(player,item);
    if (ZEXT8(b1) == 0) {
      return 0;
    }
    i2 = i2 + 1;
  }
  i2 = 0;
  if (0 < num_groups) {
    do {
      i3 = 0;
      item = (int *)ArrayAccessGrpItem(triggers,i2,0);
      if (item == (int *)0x0) {
        memcpy(g + G_ERRMSG,"TrigArrayTest bug",0x12);
        ErrorExit();
      }
      while (b1 = SCtrlTrigTest(player,item), ZEXT8(b1) != 0) {
        i3 = i3 + 1;
        item = (int *)ArrayAccessGrpItem(triggers,i2,i3);
        if (item == (int *)0x0) {
          return 1;
        }
      }
      i2 = i2 + 1;
    } while (i2 < num_groups);
  }
  return 0;
}

/* SCtrlTrigTest @ 0x080cd3c0, 142 bytes
 *
 * Evaluates one trigger expression for a player and returns whether it is
 * nonzero. A malformed expression is fatal ("Fatal: Player %s (%i) in state
 * %i: malformed expression").
 *
 * Parameters:
 *   player       int *
 *   expr         int *
 *
 * Player fields read: id, stateno
 * Globals read: frame_count
 * Calls: EvalExpression, ErrorExit
 * C library: sprintf
 * Called by: SCtrlTrigArrayTest
 * Messages:
 *   "%4i: Fatal: Player %s (%i) in state %i: malformed expression"
 *
 * Elecbyte file: src/mugen/st-trig.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x10 bytes, 2
 *       variables), because their address is taken.
 */
bool SCtrlTrigTest(int *player,int *expr)

{
  int type;
  uint32_t stale_ECX;
  bool b2;
  unsigned char frame[0x10] __attribute__((aligned(16)));
#define stk_10 (*(int *)(frame + 0x0))
#define stk_c (*(float *)(frame + 0x4))
  
  type = EvalExpression(player,expr,&stk_10,(int *)&stk_c);
  if (type == 0) {
    sprintf((char *)ErrorMessage,"%4i: Fatal: Player %s (%i) in state %i: malformed expression",
            g[G_FRAME_COUNT],player + 8,player[PL_ID],player[PL_STATENO],stale_ECX,stale_ECX);
    ErrorExit();
  }
  if (type == 1) {
    b2 = stk_10 != 0;
  }
  else {
    b2 = stk_c != 0.0;
  }
  return b2;
}
#undef stk_10
#undef stk_c

/* SCtrlTrigEval @ 0x080cd450, 13030 bytes
 *
 * Evaluates one trigger code for a player and pushes its value on the
 * expression stack. A large switch over all triggers:
 * - player state: life, power, position, velocity, state numbers, anim and
 * anim time, ctrl, move contact, hit counts...;
 * - game state: round, time, match over, game time...;
 * - redirections: parent, root, helper(id), target(id), partner, enemy(n),
 * enemynear(n), playerid(id).
 *
 * Missing redirection targets give warnings ("has no helper %i", "has no
 * target"...).
 *
 * Parameters:
 *   player       int *
 *   trigger      int *
 *
 * Player fields read: targets, teamside, ishelper, statetime, anim, pos_y,
 *                     pos_x, pos_z, vel_y, facing, vel_x, vel_z, life,
 *                     statetype, width, lifemax, alive, hitcount,
 *                     uniqhitcount, movecontact
 * Globals read: players, stageinfo_zoffset, bound_screenleft, errmsg,
 *               frame_count, round_no
 * Calls: Warn, SCtrlTrigArity, ErrorExit, EvalExpressionI, HelperAccessID,
 *        VWarn, TargetAccessID, PartnerAccess, EnemyAccess,
 *        PlayerAccessID, EnemyAccessNear, HelperParent, HelperRoot,
 *        PlayerDistX, AnimGetLooptime, AnimCurIDno, PlayerBodyDistX,
 *        KBCommandIsValid, AIInsertCommand, PlayerInAnyGuardDist,
 *        ProjArrayCountActive, PartnerCount, EnemyCount, TeamHasFullLife,
 *        ...
 * C library: sprintf, random, _alemu_stricmp, log2, fsin, fcos, fptan,
 *            fpatan, f2xm1, fscale
 * Called by: EvalExpression
 * Messages:
 *   "Expression stack overflow."
 *   "has no helper %i"
 *   "has no target with hit ID %i"
 *   "has no %i-th partner"
 *   "has no %i-th enemy"
 *   "tried to access non-existent player with ID %i"
 *
 * Elecbyte file: src/mugen/st-trig.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: decompiler flag: the second decompiler pass lost the call(s) to ABS,NAN
 * Note: 33 data addresses refer to the data image (data/mugen_data.S).
 * Note: 13 accesses to parts of a variable are written as sized accesses.
 * Note: removed pointer casts from 112 case labels; switch operand cast to int
 * Note: 39 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: 7 floating constants are cast to float/double as the original stored
 *       them.
 * Note: 7 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x150 bytes,
 *       26 variables), because their address is taken.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
void SCtrlTrigEval(int *player,int *trigger)

{
  float80 f1;
  int *pi2;
  int *pi3;
  char c4;
  uint32_t stale_var;
  int *player2;
  uint32_t stale_var_00;
  int value;
  uint32_t stale_var_01;
  uint32_t *pu7;
  uint32_t stale_var_02;
  uint32_t stale_var_03;
  uint32_t stale_var_04;
  uint32_t stale_var_05;
  uint32_t stale_var_06;
  int *player3;
  int *player4;
  int *value2;
  int *player5;
  int i12;
  uint32_t stale_var_07;
  uint32_t u13;
  uint32_t stale_var_08;
  uint32_t stale_var_09;
  uint32_t stale_var_10;
  uint32_t stale_var_11;
  long l14;
  uint32_t stale_var_12;
  uint32_t stale_var_13;
  uint32_t stale_var_14;
  uint32_t stale_var_15;
  uint32_t stale_var_16;
  uint32_t stale_var_17;
  uint32_t stale_var_18;
  uint32_t stale_var_19;
  uint32_t stale_var_20;
  uint32_t stale_var_21;
  uint32_t stale_var_22;
  uint32_t stale_var_23;
  uint32_t stale_var_24;
  uint32_t stale_var_25;
  uint32_t stale_var_26;
  uint32_t stale_var_27;
  uint32_t stale_var_28;
  uint32_t stale_var_29;
  uint32_t stale_var_30;
  uint32_t stale_var_31;
  int i15;
  uint32_t stale_var_32;
  uint32_t stale_var_33;
  uint32_t stale_var_34;
  uint32_t stale_var_35;
  uint32_t stale_var_36;
  uint32_t stale_var_37;
  int *stale_ECX;
  int *stale_ECX_00;
  int *stale_ECX_01;
  int *stale_ECX_02;
  uint32_t stale_ECX_03;
  uint32_t stale_EDX;
  int *stale_EDX_00;
  uint32_t stale_EDX_01;
  uint32_t stale_EDX_02;
  uint32_t stale_EDX_03;
  uint32_t stale_EDX_04;
  int *stale_EDX_05;
  int *stale_EDX_06;
  int *stale_EDX_07;
  uint32_t stale_EDX_08;
  uint32_t stale_EDX_09;
  int *stale_EDX_10;
  uint32_t stale_EDX_11;
  uint32_t stale_EDX_12;
  uint32_t stale_EDX_13;
  uint32_t stale_EDX_14;
  uint32_t stale_EDX_15;
  uint32_t stale_EDX_16;
  int *stale_EDX_17;
  int *stale_EDX_18;
  int *stale_EDX_19;
  int *stale_EDX_20;
  int *stale_EDX_21;
  int *stale_EDX_22;
  int *stale_EDX_23;
  int *stale_EDX_24;
  int *stale_EDX_25;
  int *pi16;
  int *anim;
  bool b17;
  bool b18;
  bool b19;
  uint16_t entry_FPUControlWord;
  float80 l20;
  float80 l21;
  uint8_t *s2;
  char *msg;
  unsigned char frame[0x150] __attribute__((aligned(16)));
#define stk_150 (*(int **)(frame + 0x0))
#define stk_14c (*(int **)(frame + 0x4))
#define stk_148 (*(int *)(frame + 0x8))
#define stk_144 (*(int *)(frame + 0xc))
#define stk_140 (*(int *)(frame + 0x10))
#define stk_13c (*(int *)(frame + 0x14))
#define stk_138 (*(int *)(frame + 0x18))
#define stk_134 (*(int **)(frame + 0x1c))
#define stk_11c (*(int **)(frame + 0x34))
#define stk_118 (*(int **)(frame + 0x38))
#define stk_114 (*(int **)(frame + 0x3c))
#define player6 (*(int **)(frame + 0x40))
#define stk_10c (*(float *)(frame + 0x44))
#define stk_108 (*(float *)(frame + 0x48))
#define count (*(int **)(frame + 0x4c))
#define stk_100 (*(float (*)[5])(frame + 0x50))
#define stk_ec (*(double *)(frame + 0x64))
#define stk_e0 (*(uint16_t *)(frame + 0x70))
#define stk_cc (*(double *)(frame + 0x84))
#define stk_c0 (*(uint16_t *)(frame + 0x90))
#define stk_8c (*(double *)(frame + 0xc4))
#define stk_7c (*(double *)(frame + 0xd4))
#define stk_6c (*(double *)(frame + 0xe4))
#define stk_5c (*(double *)(frame + 0xf4))
#define stk_24 (*(int **)(frame + 0x12c))
#define stk_20 (*(uint32_t *)(frame + 0x130))
  
  player6 = (int *)0x0;
  stk_114 = (int *)0x0;
  stk_118 = (int *)0x0;
  stk_11c = player;
  count = (int *)0x0;
  i15 = trigger[5];
  b17 = false;
  value = trigger[1];
  stk_100[0] = 0.0;
  if (value == 1) {
    player2 = (int *)player[0x988];
    if (player2 != (int *)0x0) goto L_080cd965;
    Warn((int)player,(int)&str_has_no_parent_c84d);
    c4 = SCtrlTrigArity(*trigger);
    MyStackIdx = (int *)((int)MyStackIdx + ZEXT8(c4) * -2);
    player5 = stale_ECX;
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.");
      ErrorExit();
      player5 = stale_ECX_00;
    }
    player2 = (int *)((int)MyStackIdx + 1);
    b19 = SBORROW4((int)player2,0x7e);
    b18 = (int)MyStackIdx + -0x7d < 0;
    b17 = player2 == (int *)0x7e;
    MyStackIdx = player2;
    MyStack[(int)player2] = 0;
L_080cfcc3:
    player2 = player5;
    if (b17 || b19 != b18) goto L_080d04a0;
    goto L_080d0489;
  }
  player2 = player;
  if (value != 2) {
    if (value == 3) {
      value = EvalExpressionI((int)player,trigger + 2,1);
      if (value < 0) {
        value = 0;
        Warn((int)player,(int)&str_illegal_helper_id_in_retarge_cae0);
      }
      player2 = (int *)HelperAccessID((int)player,value);
      if (player2 == (int *)0x0) {
        VWarn((int)player,"has no helper %i",value,0);
        c4 = SCtrlTrigArity(*trigger);
        MyStackIdx = (int *)((int)MyStackIdx + ZEXT8(c4) * -2);
        player5 = stale_ECX_01;
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.",value,value);
          ErrorExit();
          player5 = stale_ECX_02;
        }
        player2 = (int *)((int)MyStackIdx + 1);
        b19 = SBORROW4((int)player2,0x7e);
        b18 = (int)MyStackIdx + -0x7d < 0;
        b17 = player2 == (int *)0x7e;
        MyStackIdx = player2;
        MyStack[(int)player2] = 0;
        goto L_080cfcc3;
      }
      goto L_080cd965;
    }
    if (value == 4) {
      value = EvalExpressionI((int)player,trigger + 2,1);
      if (value < -1) {
        value = -1;
        Warn((int)player,(int)&str_illegal_target_id_in_retarge_cb20);
      }
      pu7 = (uint32_t *)TargetAccessID(player[PL_TARGETS],value);
      if (pu7 == (uint32_t *)0x0) {
        if (count == (int *)0xffffffff) {
          Warn((int)player,(int)&str_has_no_target_c895);
        }
        else {
          VWarn((int)player,"has no target with hit ID %i",value,stale_EDX);
        }
        c4 = SCtrlTrigArity(*trigger);
        MyStackIdx = (int *)((int)MyStackIdx + ZEXT8(c4) * -2);
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.",trigger,trigger);
          ErrorExit();
        }
        MyStackIdx = (int *)((int)MyStackIdx + 1);
        goto L_080d03bd;
      }
      player2 = (int *)*pu7;
      goto L_080cd965;
    }
    if (value == 5) {
      value2 = (int *)EvalExpressionI((int)player,trigger + 2,1);
      if ((int)value2 < 0) {
        value2 = (int *)0x0;
        Warn((int)player,(int)&str_illegal_partner_number_in_re_cb60);
      }
      player2 = (int *)PartnerAccess((int)player,(int)value2);
      if (player2 != (int *)0x0) goto L_080cd965;
      VWarn((int)player,"has no %i-th partner",value2,0);
      c4 = SCtrlTrigArity(*trigger);
      MyStackIdx = (int *)((int)MyStackIdx + ZEXT8(c4) * -2);
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",player,player);
        ErrorExit();
      }
      player2 = (int *)((int)MyStackIdx + 1);
      b19 = SBORROW4((int)player2,0x7e);
      b18 = (int)MyStackIdx + -0x7d < 0;
      b17 = player2 == (int *)0x7e;
      MyStackIdx = player2;
      MyStack[(int)player2] = 0;
      goto L_080cfec3;
    }
    if (value == 6) {
      value = EvalExpressionI((int)player,trigger + 2,1);
      if (value < 0) {
        value = 0;
        Warn((int)player,(int)&str_illegal_enemy_number_in_reta_cba0);
      }
      player2 = (int *)EnemyAccess((int)player,value);
      if (player2 != (int *)0x0) goto L_080cd965;
      VWarn((int)player,"has no %i-th enemy",value);
      c4 = SCtrlTrigArity(*trigger);
      stk_14c = (int *)((int)MyStackIdx + ZEXT8(c4) * -2);
      player2 = stk_14c;
      if (0x7e < (int)stk_14c) {
        MyStackIdx = stk_14c;
        sprintf((char *)ErrorMessage,"Expression stack overflow.",stale_ECX_03,stale_ECX_03);
        ErrorExit();
        stk_14c = stale_EDX_00;
        player2 = MyStackIdx;
      }
      goto L_080ce674;
    }
    if (value != 7) {
      if (value == 8) {
        value = EvalExpressionI((int)player,trigger + 2,1);
        if (value < 0) {
          value = 0;
          Warn((int)player,(int)&str_illegal_player_number_in_ret_cc20);
        }
        player2 = (int *)PlayerAccessID(value);
        if (player2 == (int *)0x0) {
          VWarn((int)player,"tried to access non-existent player with ID %i",value,stale_EDX_02)
          ;
          c4 = SCtrlTrigArity(*trigger);
          MyStackIdx = (int *)((int)MyStackIdx + ZEXT8(c4) * -2);
          if (0x7e < (int)MyStackIdx) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.",trigger,trigger);
            ErrorExit();
          }
          MyStackIdx = (int *)((int)MyStackIdx + 1);
          player2 = player;
          goto L_080d03bd;
        }
      }
      goto L_080cd965;
    }
    value = EvalExpressionI((int)player,trigger + 2,1);
    if (value < 0) {
      value = 0;
      Warn((int)player,(int)&str_illegal_near_enemy_number_in_cbe0);
    }
    player2 = (int *)EnemyAccessNear((int)player,value);
    if (player2 != (int *)0x0) goto L_080cd965;
    VWarn((int)player,"has no %i-th nearest enemy",value,stale_EDX_01);
    c4 = SCtrlTrigArity(*trigger);
    MyStackIdx = (int *)((int)MyStackIdx + ZEXT8(c4) * -2);
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",trigger,trigger);
      ErrorExit();
    }
    MyStackIdx = (int *)((int)MyStackIdx + 1);
    player2 = player;
    goto L_080d03bd;
  }
  player2 = (int *)player[0x989];
  if (player2 == (int *)0x0) {
    Warn((int)player,(int)&str_has_no_root_c85b);
    c4 = SCtrlTrigArity(*trigger);
    MyStackIdx = (int *)((int)MyStackIdx + ZEXT8(c4) * -2);
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",trigger,trigger);
      ErrorExit();
    }
    MyStackIdx = (int *)((int)MyStackIdx + 1);
    player2 = player;
    goto L_080d03bd;
  }
L_080cd965:
  player3 = (int *)HelperParent((int)player2);
  player4 = (int *)HelperRoot((int)player2);
  b18 = player2 != player;
  value2 = (int *)g[0x731d];
  player5 = g;
  if (value2 == (int *)0x0) {
    stk_134 = (int *)0x0;
    anim = (int *)0x0;
    if (player2[PL_TEAMSIDE] == 1) {
      anim = (int *)g[0x73db];
      stk_134 = (int *)g[0x73dd];
    }
    else if (player2[PL_TEAMSIDE] == 2) {
      anim = (int *)g[0x73da];
      stk_134 = (int *)g[0x73dc];
    }
    player6 = (int *)player2[0xd09];
    player5 = player6;
    if ((anim == (int *)0x0) || (stk_134 == (int *)0x0)) {
      if (player6 != (int *)0x0) {
        if (player6[PL_ISHELPER] == 1) {
          player5 = (int *)HelperRoot((int)player6);
          stk_118 = anim;
          if (player5 == anim) {
            stk_118 = stk_134;
            player5 = stk_134;
          }
        }
        else {
          stk_118 = anim;
          if (player6 == anim) {
            stk_118 = stk_134;
          }
        }
      }
    }
    else {
      stk_118 = stk_134;
      if ((player6 != anim) && (stk_118 = anim, player6 != stk_134)) {
        value2 = (int *)PlayerDistX((int)player2,(int)anim);
        if ((int)value2 < 0) {
          value2 = (int *)-(int)value2;
        }
        player5 = (int *)PlayerDistX((int)player2,(int)stk_134);
        if ((int)player5 < 0) {
          player5 = (int *)-(int)player5;
        }
        stk_118 = stk_134;
        if ((int)player5 <= (int)value2) {
          stk_118 = anim;
        }
      }
    }
    if (player2[PL_ISHELPER] == 1) {
      value2 = player4;
      if (player4 != (int *)0x0) {
        value = player4[2];
        goto L_080cdb03;
      }
      value = player2[PL_TEAMSIDE];
      if (value == 1) {
        player5 = (int *)g[0x73da];
        stk_114 = player5;
        if (player5 == (int *)0x0) {
          player5 = (int *)g[0x73dc];
          stk_114 = player5;
        }
      }
      else if ((value == 2) &&
              (player5 = (int *)g[0x73db], stk_114 = player5, player5 == (int *)0x0)) {
        player5 = (int *)g[0x73dd];
        stk_114 = player5;
      }
    }
    else {
      value = player2[2];
L_080cdb03:
      count = (int *)(value + 2);
      if (4 < (int)count) {
        count = (int *)(value + -2);
      }
      player5 = (int *)g[(int)count + G_PLAYERS];
      value = player2[PL_TEAMSIDE];
      stk_114 = player5;
    }
    if (value == 1) {
      player5 = (int *)g[0x73da];
      stk_11c = player5;
    }
    if (value == 2) {
      player5 = (int *)g[0x73db];
      stk_11c = player5;
    }
  }
  pi3 = g;
  pi2 = MyStackIdx;
  pi16 = (int *)*trigger;
  switch((int)pi16) {
  case 0x0:
    count = (int *)player2[PL_STATETIME];
    break;
  case 0x1:
    value = AnimGetLooptime((uint32_t *)player2[PL_ANIM]);
    count = (int *)(*(int *)(player2[PL_ANIM] + 0x1c) - value);
    break;
  case 0x2:
    value = trigger[9];
    goto L_080d0371;
  case 0x3:
    count = (int *)AnimCurIDno((uint32_t *)player2[PL_ANIM]);
    break;
  case 0x4:
    value = trigger[7];
    if (value == 1) {
      stk_100[0] = BITS_I2F(player2[PL_POS_Y]);
      goto L_080cf4e5;
    }
    if (value < 2) {
      if (value == 0) {
        pi16 = (int *)*trigger;
        stk_100[0] = (BITS_I2F(player2[PL_POS_X]) - BITS_I2F(g[0x730f])) - 160.0;
      }
    }
    else {
L_080ce0c8:
      if (value == 2) {
        stk_100[0] = BITS_I2F(player2[PL_POS_Z]);
        goto L_080cf4e5;
      }
    }
    goto L_080d04fc;
  case 0x5:
    value = trigger[7];
    if (value == 1) {
      pi16 = (int *)*trigger;
      stk_100[0] = (BITS_I2F(player2[PL_POS_Y]) - BITS_I2F(g[0x7310])) + (float)g[G_STAGEINFO_ZOFFSET];
    }
    else {
      if (1 < value) goto L_080ce0c8;
      if (value == 0) {
        pi16 = (int *)*trigger;
        stk_100[0] = BITS_I2F(player2[PL_POS_X]) - BITS_I2F(g[0x730f]);
      }
    }
    goto L_080d04fc;
  case 0x6:
    value = trigger[7];
    if (value == 1) {
      stk_100[0] = BITS_I2F(player2[PL_VEL_Y]);
      goto L_080cf4e5;
    }
    if (value < 2) {
      if (value == 0) {
        pi16 = (int *)*trigger;
        stk_100[0] = (float80)player2[PL_FACING] * BITS_I2F(player2[PL_VEL_X]);
      }
    }
    else if (value == 2) {
      stk_100[0] = BITS_I2F(player2[PL_VEL_Z]);
      goto L_080cf4e5;
    }
    goto L_080d04fc;
  case 0x7:
    count = (int *)(player2[PL_STATETIME] % trigger[9]);
    break;
  case 0x8:
    if (player6 == (int *)0x0) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",player2,player2);
        ErrorExit();
      }
      player2 = (int *)((int)MyStackIdx + 1);
      b19 = SBORROW4((int)player2,0x7e);
      b18 = (int)MyStackIdx + -0x7d < 0;
      b17 = player2 == (int *)0x7e;
      MyStackIdx = player2;
      MyStack[(int)player2] = 0;
      goto L_080cfec3;
    }
    value = trigger[7];
    if (value == 1) {
      stk_100[0] = BITS_I2F(player2[PL_POS_Y]);
L_080cf44b:
      stk_100[0] = BITS_I2F(player6[PL_POS_Y]) - stk_100[0];
L_080cf451:
      pi16 = (int *)*trigger;
    }
    else if (value < 2) {
L_join_080cf410:
      if (value == 0) {
        value = PlayerDistX((int)player2,(int)player6);
L_080cf42e:
        stk_100[0] = (float80)value;
        pi16 = (int *)*trigger;
        anim = player6;
      }
    }
    else if (value == 2) {
      stk_100[0] = BITS_I2F(player2[PL_POS_Z]);
L_080cf46a:
      pi16 = (int *)*trigger;
      stk_100[0] = BITS_I2F(player6[PL_POS_Z]) - stk_100[0];
    }
    goto L_080d04fc;
  case 0x9:
    if (player6 == (int *)0x0) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",player2,player2);
        ErrorExit();
      }
      player2 = (int *)((int)MyStackIdx + 1);
      b19 = SBORROW4((int)player2,0x7e);
      b18 = (int)MyStackIdx + -0x7d < 0;
      b17 = player2 == (int *)0x7e;
      MyStackIdx = player2;
      MyStack[(int)player2] = 0;
      goto L_080cfec3;
    }
    value = trigger[7];
    if (value == 1) {
      pi16 = (int *)*trigger;
      stk_100[0] = BITS_I2F(player6[PL_POS_Y]) - BITS_I2F(player2[PL_POS_Y]);
    }
    else if (value < 2) {
      if (value == 0) {
        value = PlayerBodyDistX((int)player2,(int)player6);
        goto L_080cf42e;
      }
    }
    else if (value == 2) {
      stk_100[0] = BITS_I2F(player6[PL_POS_Z]) - BITS_I2F(player2[PL_POS_Z]);
      goto L_080cf451;
    }
    goto L_080d04fc;
  case 0xa:
    if (player6 == (int *)0x0) {
L_080cffd7:
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",pi16,pi16);
        ErrorExit();
      }
      player2 = (int *)((int)MyStackIdx + 1);
      b19 = SBORROW4((int)player2,0x7e);
      b18 = (int)MyStackIdx + -0x7d < 0;
      b17 = player2 == (int *)0x7e;
      MyStackIdx = player2;
      MyStack[(int)player2] = 0;
      goto L_080d0017;
    }
    count = (int *)player6[PL_LIFE];
    break;
  case 0xb:
  case 0xc:
    player2[0x75] = (int)X87_FIST32((float)(g[G_BOUND_SCREENLEFT] + -0xa0) / BITS_I2F(player2[0x4d2]) + (float)g[0x7311] +
                              160.0);
    stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
    player2[0x76] = (int)X87_FIST32((float)(0xa0 - pi3[0x10a2]) / BITS_I2F(player2[0x4d2]) +
                              (float80)pi3[0x7311] + 160.0);
    count = (int *)0x0;
    value = trigger[9];
    if ((value != 0) && (count = (int *)(uint32_t)(player2[PL_STATETYPE] == 3), player2[PL_STATETYPE] == 4)) {
      anim = (int *)0x2;
      count = anim;
    }
    if (*trigger == 0xb) {
      if (value != 0) {
        count = (int *)((int)count + player2[PL_WIDTH]);
      }
      value = player2[PL_FACING];
      if (value == 1) {
        i12 = player2[0x76];
      }
      else {
        i12 = player2[0x75];
      }
      f1 = (float)(value * (int)count) + BITS_I2F(player2[PL_POS_X]);
      value = -value;
    }
    else {
      if (value != 0) {
        anim = (int *)player2[0x7e];
        count = (int *)((int)count + (int)anim);
      }
      value = player2[PL_FACING];
      if (value == 1) {
        i12 = player2[0x75];
      }
      else {
        i12 = player2[0x76];
      }
      f1 = BITS_I2F(player2[PL_POS_X]) - (float)(value * (int)count);
    }
    f1 = (float80)value * (f1 - (float80)i12);
L_080cdf3d:
    stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
    stk_24 = (int *)(int)X87_FIST32(f1);
    goto L_080cdf6f;
  default:
    s2 = (uint8_t *)(g + G_ERRMSG);
    player2 = (int *)*trigger;
    msg = "Missing trigger code %i";
    player5 = anim;
L_080d04e9:
    sprintf((char *)s2,msg,player2,player5);
    ErrorExit();
    pi16 = (int *)*trigger;
    goto L_080d04fc;
  case 0xf:
    count = (int *)player2[PL_LIFE];
    break;
  case 0x10:
    count = (int *)player2[PL_LIFEMAX];
    break;
  case 0x11:
    count = (int *)stk_11c[0x5c];
    goto L_080cdffa;
  case 0x12:
    count = (int *)stk_11c[0x5d];
L_080cdffa:
    count = (int *)*count;
    break;
  case 0x13:
    count = (int *)player2[PL_ALIVE];
    break;
  case 0x14:
    count = (int *)(trigger[7] + -1);
    b18 = KBCommandIsValid((int)(player2 + 0x25a),trigger[7]);
    if ((ZEXT8(b18) != 0) && (count = (int *)trigger[7], i15 == 0)) {
      AIInsertCommand(player2 + 0xcef,(int)count);
    }
    break;
  case 0x1e:
    count = (int *)player2[PL_HITCOUNT];
    break;
  case 0x1f:
    count = (int *)player2[PL_UNIQHITCOUNT];
    break;
  case 0x20:
    b18 = player2[PL_MOVECONTACT] == 2;
    goto L_080ce1f7;
  case 0x21:
    b18 = player2[PL_MOVECONTACT] == 1;
    goto L_080ce1f7;
  case 0x22:
    if (1 < player2[PL_MOVECONTACT] - 1U) goto L_080cdd3a;
    goto L_080ce1fd;
  case 0x23:
    b18 = player2[PL_MOVECONTACT] == 4;
L_080ce1f7:
    if (!b18) goto L_080cdd3a;
L_080ce1fd:
    value = player2[PL_MOVEREVERSED];
L_080ce203:
    count = (int *)(value + 1);
    break;
  case 0x24:
    count = (int *)PlayerInAnyGuardDist((int)player2);
    break;
  case 0x28:
    count = (int *)player2[PL_STATENO];
    break;
  case 0x29:
    count = (int *)player2[PL_PREVSTATENO];
    break;
  case 0x2a:
    stk_14c = pi16;
    if (player6 == (int *)0x0) {
L_080ce647:
      player2 = MyStackIdx;
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",MyStackIdx,MyStackIdx);
        ErrorExit();
        stk_14c = stale_EDX_07;
        player2 = MyStackIdx;
      }
L_080ce674:
      MyStackIdx = (int *)((int)player2 + 1);
      b19 = SBORROW4((int)MyStackIdx,0x7e);
      b18 = (int)player2 + -0x7d < 0;
      b17 = MyStackIdx == (int *)0x7e;
      MyStack[(int)MyStackIdx] = 0;
      goto L_080d0485;
    }
    count = (int *)player6[PL_STATENO];
    break;
  case 0x2b:
    count = (int *)player2[PL_STATETYPE];
    break;
  case 0x2c:
    if (player6 == (int *)0x0) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",anim,anim);
        ErrorExit();
      }
      player5 = (int *)((int)MyStackIdx + 1);
      MyStackIdx = player5;
      MyStack[(int)player5] = 0;
      anim = trigger;
L_join_080cf697:
      player2 = anim;
      if ((int)player5 < 0x7f) goto L_080d04a0;
      goto L_080d0489;
    }
    count = (int *)player6[PL_STATETYPE];
    break;
  case 0x2d:
    count = (int *)player2[PL_MOVETYPE];
    break;
  case 0x2e:
    if (player6 == (int *)0x0) {
      player5 = MyStackIdx;
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",value2,value2);
        ErrorExit();
        player5 = MyStackIdx;
      }
      MyStackIdx = (int *)((int)player5 + 1);
      b19 = SBORROW4((int)MyStackIdx,0x7e);
      b18 = (int)player5 + -0x7d < 0;
      b17 = MyStackIdx == (int *)0x7e;
      MyStack[(int)MyStackIdx] = 0;
      goto L_080cfcc3;
    }
    count = (int *)player6[PL_MOVETYPE];
    break;
  case 0x2f:
    count = (int *)player2[PL_CTRL];
    break;
  case 0x30:
    count = (int *)0x0;
    if ((player2[PL_MOVETYPE] == 1) && ((trigger[7] & player2[0x459] & 7U) != 0)) {
      u13 = trigger[7] & player2[0x459] & 0xfffffff8;
L_080cddb3:
      count = (int *)0x0;
      if (u13 != 0) goto L_080cddb9;
    }
    break;
  case 0x33:
    l14 = random();
    count = (int *)(l14 % 1000);
    break;
  case 0x3c:
    count = (int *)ProjArrayCountActive((int *)player2[PL_PROJECTILES]);
    break;
  case 0x3e:
    if ((player2[0x85] == 2) && ((player2[0x84] == trigger[9] || (trigger[9] == 0)))) {
      count = (int *)player2[0x86];
      anim = (int *)trigger[10];
      player2 = anim;
L_080cea1d:
      if (player2 == (int *)0x0) {
        b17 = true;
      }
      break;
    }
    stk_150 = (int *)(uint32_t)(trigger[10] == 0);
L_080d00b0:
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",player2,player2);
      ErrorExit();
    }
    player2 = (int *)((int)MyStackIdx + 1);
    MyStackIdx = player2;
    MyStack[(int)player2] = (int)stk_150;
    goto L_join_080d00e6;
  case 0x3f:
    if (player2[0x85] == 1) {
      value = trigger[9];
      if (player2[0x84] != value) {
L_join_080cea0c:
        if (value != 0) goto L_080cea30;
      }
L_080cea0e:
      count = (int *)player2[0x86];
      player2 = (int *)trigger[10];
      goto L_080cea1d;
    }
    goto L_080cea30;
  case 0x40:
    if ((player2[0x85] != 0) && (player2[0x85] != 3)) {
      value = trigger[9];
      if (player2[0x84] != value) goto L_join_080cea0c;
      goto L_080cea0e;
    }
L_080cea30:
    player2 = (int *)(uint32_t)(trigger[10] == 0);
    goto L_080d0643;
  case 0x5a:
    player5 = (int *)trigger[0xd];
    stk_118 = (int *)*player2;
    goto L_080ceb09;
  case 0x5b:
    if (player6 != (int *)0x0) {
      player5 = (int *)trigger[0xd];
      stk_118 = (int *)*player6;
      goto L_080ceb09;
    }
    goto L_080cdd3a;
  case 0x5c:
    if (stk_114 != (int *)0x0) {
      player5 = (int *)trigger[0xd];
      anim = (int *)*stk_114;
      stk_118 = anim;
      goto L_080ceb09;
    }
    goto L_080cdd3a;
  case 0x5d:
    if (stk_118 != (int *)0x0) {
      player5 = (int *)trigger[0xd];
      stk_118 = (int *)*stk_118;
      goto L_080ceb09;
    }
    goto L_080cdd3a;
  case 0x5e:
    anim = (int *)trigger[0xd];
    stk_118 = (int *)(*player2 + 0x60);
    player5 = anim;
L_080ceb09:
    value = _alemu_stricmp((char *)stk_118,(char *)player5);
L_080ceb15:
    count = (int *)(uint32_t)(value == 0);
    break;
  case 0x5f:
    count = (int *)PartnerCount((int)player2);
    break;
  case 0x60:
    count = (int *)EnemyCount((int)player2);
    break;
  case 0x61:
    count = (int *)player2[PL_ID];
    break;
  case 0x63:
    count = (int *)player2[PL_FACING];
    break;
  case 0x64:
L_case_080cdb66_64:
    count = (int *)player2[PL_HITFALL];
    break;
  case 0x65:
    count = (int *)(uint32_t)(player2[PL_HITSHAKEOVER] < 1);
    break;
  case 0x66:
    count = (int *)((uint32_t)player2[PL_HITOVER] >> 0x1f);
    break;
  case 0x67:
    if (trigger[7] == 0) {
      pi16 = (int *)*trigger;
      stk_100[0] = (float80)player2[PL_FACING] * BITS_I2F(player2[PL_HITVEL]);
    }
    else if (trigger[7] == 1) goto L_case_080ceefc_12;
    goto L_080d04fc;
  case 0x68:
    count = (int *)player2[PL_HITPAUSETIME];
    break;
  case 0x69:
    count = (int *)0x0;
    if ((player2[PL_CANRECOVER] != 0) && (player2[0x422] <= player2[0x421])) {
      count = (int *)0x1;
    }
    break;
  case 0x6b:
    value = player2[PL_PALNO];
    goto L_080ce203;
  case 0x6c:
    anim = (int *)g[0x7513];
    if (((anim == (int *)0x0) || (g[0x7512] != player2[PL_TEAMSIDE])) ||
       (value = TeamHasFullLife(g[0x7512]), value == 0)) goto L_080cdd3a;
L_080cddb9:
    count = (int *)0x1;
    break;
  case 0x6d:
    if (((g[0x7513] == trigger[9]) || (trigger[9] == -1)) && (g[0x7512] == player2[PL_TEAMSIDE]))
    goto L_080cddb9;
    goto L_080cdd3a;
  case 0x6e:
    if (((g[0x7513] == trigger[9]) || (trigger[9] == -1)) &&
       ((g[0x7512] != player2[PL_TEAMSIDE] && (g[0x7512] != 0)))) goto L_080cddb9;
    goto L_080cdd3a;
  case 0x6f:
    count = (int *)0x0;
    if (g[0x7512] == 0) {
      u13 = g[0x7513];
      goto L_080cddb3;
    }
    break;
  case 0x70:
    value = GameMatchWinner();
    goto L_080cddcb;
  case 0x71:
    count = (int *)g[G_FRAME_COUNT];
    break;
  case 0x72:
    count = (int *)g[G_ROUND_NO];
    break;
  case 0x73:
    count = (int *)g[0x7511];
    break;
  case 0x74:
    count = (int *)g[0x7543];
    break;
  case 0x75:
    count = (int *)player2[PL_ROUNDSEXISTED];
    break;
  case 0x78:
    count = (int *)player2[PL_TEAMSIDE];
    break;
  case 0x79:
    count = (int *)g[player2[PL_TEAMMODE] * 0x17 + 0x4106];
    if (1 < g[player2[PL_TEAMMODE] * 0x6a7 + 0x33b9]) {
      count = (int *)0x3;
    }
    player2 = (int *)trigger[7];
L_080cedc3:
    b18 = count == player2;
    goto L_080cedc9;
  case 0x7a:
    if (g[0x33b3] == 0) {
      b18 = player2[PL_TEAMSIDE] == 1;
      goto L_080cedc9;
    }
    value = player2[PL_TEAMSIDE] - (3 - g[0x33b3]);
    goto L_080ceb15;
  case 0x96:
    count = (int *)ExplodCount((int *)g[0x52be],player2[PL_ID],-1);
    break;
  case 0xa0:
    player5 = (int *)0xffffffff;
    goto L_080cf217;
  case 0xb4:
    switch(trigger[7]) {
    case 0:
      count = (int *)player2[0x403];
      break;
    case 1:
      count = (int *)player2[0x404];
      break;
    case 2:
      count = (int *)player2[0x406];
      break;
    case 3:
      count = (int *)player2[0x407];
      break;
    case 4:
      count = (int *)player2[0x408];
      break;
    case 5:
      count = (int *)player2[0x409];
      break;
    case 6:
      count = (int *)player2[0x40a];
      break;
    case 7:
      count = (int *)player2[0x40b];
      break;
    case 8:
      count = (int *)player2[0x40c];
      break;
    case 9:
      count = (int *)player2[PL_HITSHAKEOVER];
      break;
    case 10:
      count = (int *)player2[PL_HITOVER];
      break;
    case 0xb:
      count = (int *)player2[0x40f];
      break;
    case 0xc:
      count = (int *)player2[0x410];
      break;
    case 0xd:
      count = (int *)player2[0x411];
      break;
    case 0xe:
      stk_100[0] = BITS_I2F(player2[0x413]);
      goto L_080cf4e5;
    case 0xf:
      stk_100[0] = BITS_I2F(player2[0x414]);
      goto L_080cf4e5;
    case 0x10:
      stk_100[0] = BITS_I2F(player2[0x415]);
      goto L_080cf4e5;
    case 0x11:
      stk_100[0] = BITS_I2F(player2[PL_HITVEL]);
      goto L_080cf4e5;
    case 0x12:
L_case_080ceefc_12:
      stk_100[0] = BITS_I2F(player2[0x417]);
      goto L_080cf4e5;
    case 0x13:
      stk_100[0] = BITS_I2F(player2[0x418]);
      goto L_080cf4e5;
    case 0x14:
      count = (int *)player2[0x419];
      break;
    case 0x15:
      count = (int *)player2[0x41a];
      break;
    case 0x16:
      count = (int *)(uint32_t)(player2[0x41b] != 0);
      break;
    case 0x17:
      goto L_case_080cdb66_64;
    case 0x18:
      count = (int *)player2[0x41d];
      break;
    case 0x19:
      stk_100[0] = BITS_I2F(player2[0x41e]);
      goto L_080cf4e5;
    case 0x1a:
      stk_100[0] = BITS_I2F(player2[0x41f]);
      goto L_080cf4e5;
    case 0x1b:
      count = (int *)player2[PL_CANRECOVER];
      break;
    case 0x1c:
      count = (int *)player2[0x421];
      break;
    case 0x1d:
      count = (int *)player2[0x422];
      break;
    case 0x1e:
      count = (int *)player2[0x423];
      break;
    case 0x1f:
      count = (int *)player2[0x425];
      break;
    case 0x20:
      count = (int *)player2[0x426];
      break;
    case 0x21:
      f1 = BITS_I2F(player2[0x428]);
      goto L_080cdf3d;
    case 0x22:
      stk_100[0] = BITS_I2F(player2[0x427]);
      goto L_080cf4e5;
    case 0x23:
      stk_100[0] = BITS_I2F(player2[0x429]);
L_080cf4e5:
      pi16 = (int *)*trigger;
      goto L_080d04fc;
    default:
      if (b18) {
        WarnR((int)player,(int)player2,(int)&str_illegal_gethitvar_programmer_cd00);
      }
      else {
        Warn((int)player2,(int)&str_illegal_gethitvar_programmer_cd00);
      }
    }
    break;
  case 0xb5:
    value = trigger[7];
    if (CnstType[value] != 0) {
      stk_100[0] = BITS_I2F(player2[value + 0x14]);
      goto L_080cf4e5;
    }
    count = (int *)player2[value + 0x14];
    break;
  case 0xbe:
    count = (int *)TimerFPS;
    break;
  case 0xc9:
    b18 = player2[PL_ISHELPER] == 1;
L_080cedc9:
    count = (int *)(uint32_t)b18;
    break;
  case 0xca:
    player5 = (int *)0x0;
L_080cf327:
    count = (int *)HelperCount((int)player2,(int)player5);
    break;
  case 0xcb:
    if (player3 == (int *)0x0) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",player2,player2);
        ErrorExit();
      }
      player2 = (int *)((int)MyStackIdx + 1);
      b19 = SBORROW4((int)player2,0x7e);
      b18 = (int)MyStackIdx + -0x7d < 0;
      b17 = player2 == (int *)0x7e;
      MyStackIdx = player2;
      MyStack[(int)player2] = 0;
      goto L_080cfec3;
    }
    value = trigger[7];
    if (value == 1) {
      pi16 = (int *)*trigger;
      stk_100[0] = BITS_I2F(player3[PL_POS_Y]) - BITS_I2F(player2[PL_POS_Y]);
    }
    else {
      player6 = player3;
      if (value < 2) goto L_join_080cf410;
      if (value == 2) {
        pi16 = (int *)*trigger;
        stk_100[0] = BITS_I2F(player3[PL_POS_Z]) - BITS_I2F(player2[PL_POS_Z]);
      }
    }
    goto L_080d04fc;
  case 0xcc:
    if (player4 == (int *)0x0) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",player2,player2);
        ErrorExit();
      }
      player2 = (int *)((int)MyStackIdx + 1);
      b19 = SBORROW4((int)player2,0x7e);
      b18 = (int)MyStackIdx + -0x7d < 0;
      b17 = player2 == (int *)0x7e;
      MyStackIdx = player2;
      MyStack[(int)player2] = 0;
      goto L_080cfec3;
    }
    value = trigger[7];
    player6 = player4;
    if (value == 1) {
      stk_100[0] = BITS_I2F(player2[PL_POS_Y]);
      goto L_080cf44b;
    }
    if (value < 2) goto L_join_080cf410;
    if (value == 2) {
      stk_100[0] = BITS_I2F(player2[PL_POS_Z]);
      goto L_080cf46a;
    }
    goto L_080d04fc;
  case 0xcd:
    count = (int *)player2[PL_STANDBY];
    break;
  case 0x12c:
    stk_100[0] = ((double)3.1415927);
    goto L_080cf4e5;
  case 0x12d:
    stk_100[0] = ((double)2.7182817);
    goto L_080cf4e5;
  case 0x131:
    if (-1 < (int)MyStackIdx) {
      stk_138 = MyStack[(int)MyStackIdx];
      player5 = (int *)((int)MyStackIdx + -1);
      MyStackIdx = player5;
    }
    if ((int *)0x7fffffff < pi2) {
      player5 = (int *)StackUnderflow();
    }
    player3 = MyStackIdx;
    if (-1 < (int)MyStackIdx) {
      stk_13c = MyStack[(int)MyStackIdx];
      player5 = (int *)((int)MyStackIdx + -1);
      MyStackIdx = player5;
    }
    if ((int *)0x7fffffff < player3) {
      player5 = (int *)StackUnderflow();
    }
    player3 = MyStackIdx;
    if (-1 < (int)MyStackIdx) {
      stk_140 = MyStack[(int)MyStackIdx];
      player5 = (int *)((int)MyStackIdx + -1);
      MyStackIdx = player5;
    }
    if ((int *)0x7fffffff < player3) {
      player5 = (int *)StackUnderflow();
    }
    player3 = MyStackIdx;
    if (-1 < (int)MyStackIdx) {
      stk_144 = MyStack[(int)MyStackIdx];
      player5 = (int *)((int)MyStackIdx + -1);
      MyStackIdx = player5;
    }
    if ((int *)0x7fffffff < player3) {
      player5 = (int *)StackUnderflow();
    }
    player3 = MyStackIdx;
    if (-1 < (int)MyStackIdx) {
      stk_148 = MyStack[(int)MyStackIdx];
      player5 = (int *)((int)MyStackIdx + -1);
      MyStackIdx = player5;
    }
    if ((int *)0x7fffffff < player3) {
      player5 = (int *)StackUnderflow();
    }
    player3 = MyStackIdx;
    if (-1 < (int)MyStackIdx) {
      stk_14c = (int *)MyStack[(int)MyStackIdx];
      player5 = (int *)((int)MyStackIdx + -1);
      MyStackIdx = player5;
    }
    u13 = (uint32_t)(player3 < (int *)0x80000000);
    if (u13 == 0) {
      player5 = (int *)StackUnderflow();
      u13 = stale_EDX_13;
    }
    if (stk_148 != 3) {
      if (stk_140 == 3) {
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.",player5,player5);
          ErrorExit();
        }
        player5 = (int *)((int)MyStackIdx + 1);
        MyStackIdx = player5;
        MyStack[(int)player5] = stk_144;
        goto L_join_080cf697;
      }
      if (stk_138 == 3) {
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.",trigger,trigger);
          ErrorExit();
        }
        player5 = (int *)((int)MyStackIdx + 1);
        b19 = SBORROW4((int)player5,0x7e);
        b18 = (int)MyStackIdx + -0x7d < 0;
        b17 = player5 == (int *)0x7e;
        MyStackIdx = player5;
        MyStack[(int)player5] = stk_13c;
        goto L_080d03d0;
      }
      if (stk_148 == 2) {
        if ((float80)(int)stk_14c == 0.0) {
          if (0x7e < (int)MyStackIdx) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.",u13,u13);
            ErrorExit();
          }
          player2 = (int *)((int)MyStackIdx + 1);
          MyStackIdx = player2;
          MyStack[(int)player2] = stk_13c;
          player5 = player2;
L_join_080cf853:
          stk_140 = stk_138;
          if (0x7e < (int)player5) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.",player2,player2);
            ErrorExit();
          }
          goto L_080cf877;
        }
        player2 = MyStackIdx;
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.",value2,value2);
          ErrorExit();
          player2 = MyStackIdx;
        }
        player5 = (int *)((int)player2 + 1);
        MyStackIdx = player5;
        MyStack[(int)player5] = stk_144;
      }
      else {
        if (stk_14c == (int *)0x0) {
          player2 = MyStackIdx;
          if (0x7e < (int)MyStackIdx) {
            sprintf((char *)ErrorMessage,"Expression stack overflow.",value2,value2);
            ErrorExit();
            player2 = MyStackIdx;
          }
          player5 = (int *)((int)player2 + 1);
          MyStackIdx = player5;
          MyStack[(int)player5] = stk_13c;
          goto L_join_080cf853;
        }
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.",trigger,trigger);
          ErrorExit();
        }
        player5 = (int *)((int)MyStackIdx + 1);
        MyStackIdx = player5;
        MyStack[(int)player5] = stk_144;
      }
      if (0x7e < (int)player5) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",player2,player2);
        ErrorExit();
      }
L_080cf877:
      MyStackIdx = (int *)((int)MyStackIdx + 1);
      MyStack[(int)MyStackIdx] = stk_140;
      return;
    }
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",MyStackIdx,MyStackIdx);
      ErrorExit();
    }
    player2 = (int *)((int)MyStackIdx + 1);
    b19 = SBORROW4((int)player2,0x7e);
    b18 = (int)MyStackIdx + -0x7d < 0;
    b17 = player2 == (int *)0x7e;
    MyStackIdx = player2;
    MyStack[(int)player2] = (int)stk_14c;
L_080d0485:
    player2 = stk_14c;
    if (b17 || b19 != b18) goto L_080d04a0;
    goto L_080d0489;
  case 0x136:
    anim = player2;
    c4 = SPopF(player2,&stk_108);
    count = (int *)ZEXT8(c4);
    c4 = SPopF(player2,&stk_10c);
    if (ZEXT8(c4) == 3) {
L_080cfc4e:
      stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
      stk_24 = (int *)(int)X87_FIST32(stk_10c);
      player3 = stk_24;
L_080cfc8d:
      player5 = MyStackIdx;
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",player2,player2);
        ErrorExit();
        player5 = MyStackIdx;
      }
      MyStackIdx = (int *)((int)player5 + 1);
      b19 = SBORROW4((int)MyStackIdx,0x7e);
      b18 = (int)player5 + -0x7d < 0;
      b17 = MyStackIdx == (int *)0x7e;
      MyStack[(int)MyStackIdx] = (int)player3;
      goto L_080cfcc3;
    }
    if (count != (int *)0x3) {
      l20 = (float80)stk_10c;
      if (((l20 <= (float80)0) || (l20 == (float80)1.0)) ||
         ((float80)stk_108 <= (float80)0)) {
        if (!b18) {
          msg = "took log with non-positive base or argument.";
          goto L_080cffce;
        }
        msg = "took log with non-positive base or argument.";
        goto L_080cffb7;
      }
      l21 = (float80)log2((float80)stk_108);
      l20 = (float80)log2(l20);
      l20 = ((float80)((double)0.6931471805599453) * l21) / ((float80)((double)0.6931471805599453) * l20)
      ;
      goto L_080cfef8;
    }
    stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
    player5 = (int *)(int)X87_FIST32(stk_108);
    stk_24 = player5;
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",stk_20,stk_20);
      ErrorExit();
    }
    player2 = (int *)((int)MyStackIdx + 1);
    b19 = SBORROW4((int)player2,0x7e);
    b18 = (int)MyStackIdx + -0x7d < 0;
    b17 = player2 == (int *)0x7e;
    MyStackIdx = player2;
    MyStack[(int)player2] = (int)player5;
    goto L_080d0017;
  case 0x140:
    c4 = SPopF(player2,stk_100);
    if (ZEXT8(c4) == 3) {
      stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
      value2 = (int *)(int)X87_FIST32(stk_100[0]);
      stk_24 = value2;
L_080cfe8d:
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",player2,player2);
        ErrorExit();
      }
      player2 = (int *)((int)MyStackIdx + 1);
      b19 = SBORROW4((int)player2,0x7e);
      b18 = (int)MyStackIdx + -0x7d < 0;
      b17 = player2 == (int *)0x7e;
      MyStackIdx = player2;
      MyStack[(int)player2] = (int)value2;
      goto L_080cfec3;
    }
    l20 = (float80)fsin((float80)stk_100[0]);
    stk_100[0] = (float)l20;
    break;
  case 0x141:
    c4 = SPopF(player2,stk_100);
    if (ZEXT8(c4) == 3) {
      stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
      player5 = (int *)(int)X87_FIST32(stk_100[0]);
      stk_24 = player5;
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",stk_20,stk_20);
        ErrorExit();
      }
      player2 = (int *)((int)MyStackIdx + 1);
      b19 = SBORROW4((int)player2,0x7e);
      b18 = (int)MyStackIdx + -0x7d < 0;
      b17 = player2 == (int *)0x7e;
      MyStackIdx = player2;
      MyStack[(int)player2] = (int)player5;
      goto L_080d0017;
    }
    l20 = (float80)fcos((float80)stk_100[0]);
    stk_100[0] = (float)l20;
    break;
  case 0x142:
    c4 = SPopF(player2,stk_100);
    if (ZEXT8(c4) == 3) {
      stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
      value2 = (int *)(int)X87_FIST32(stk_100[0]);
      stk_24 = value2;
      goto L_080cfe8d;
    }
    l20 = (float80)fptan((float80)stk_100[0]);
    stk_5c = (double)l20;
    l20 = (float80)stk_5c;
    goto L_080cfef8;
  case 0x143:
    c4 = SPopF(player2,stk_100);
    if (ZEXT8(c4) != 3) {
      l20 = (float80)stk_100[0];
      if (((float80)-1.0 <= l20) && (l20 <= (float80)1.0)) {
        l20 = (float80)fpatan(l20,SQRT((float80)1.0 - l20 * l20));
        stk_6c = (double)l20;
        l20 = (float80)stk_6c;
        goto L_080cfef8;
      }
      if (b18) {
        msg = "asin argument out of range";
        goto L_080cffb7;
      }
      msg = "asin argument out of range";
L_080cffce:
      Warn((int)player2,(int)msg);
      pi16 = stale_EDX_18;
      goto L_080cffd7;
    }
    stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
    player5 = (int *)(int)X87_FIST32(stk_100[0]);
    stk_24 = player5;
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",stale_EDX_14,stale_EDX_14);
      ErrorExit();
    }
    player2 = (int *)((int)MyStackIdx + 1);
    b19 = SBORROW4((int)player2,0x7e);
    b18 = (int)MyStackIdx + -0x7d < 0;
    b17 = player2 == (int *)0x7e;
    MyStackIdx = player2;
    MyStack[(int)player2] = (int)player5;
    goto L_080d0017;
  case 0x144:
    c4 = SPopF(player2,stk_100);
    stk_10c = stk_100[0];
    if (ZEXT8(c4) == 3) goto L_080cfc4e;
    l20 = (float80)stk_100[0];
    if (((float80)-1.0 <= l20) && (l20 <= (float80)1.0)) {
      l20 = (float80)fpatan(SQRT((float80)1.0 - l20 * l20),l20);
      stk_7c = (double)l20;
      l20 = (float80)stk_7c;
      goto L_080cfef8;
    }
    if (b18) {
      WarnR((int)player,(int)player2,(int)&str_acos_argument_out_of_range_c951);
    }
    else {
      Warn((int)player2,(int)&str_acos_argument_out_of_range_c951);
    }
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",player2,player2);
      ErrorExit();
    }
    player2 = (int *)((int)MyStackIdx + 1);
    b19 = SBORROW4((int)player2,0x7e);
    b18 = (int)MyStackIdx + -0x7d < 0;
    b17 = player2 == (int *)0x7e;
    MyStackIdx = player2;
    MyStack[(int)player2] = 0;
L_080cfec3:
    player2 = value2;
    if (b17 || b19 != b18) goto L_080d04a0;
    goto L_080d0489;
  case 0x145:
    c4 = SPopF(player2,stk_100);
    if (ZEXT8(c4) == 3) {
      stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
      player5 = (int *)(int)X87_FIST32(stk_100[0]);
      stk_24 = player5;
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",stale_EDX_15,stale_EDX_15);
        ErrorExit();
      }
      player2 = (int *)((int)MyStackIdx + 1);
      b19 = SBORROW4((int)player2,0x7e);
      b18 = (int)MyStackIdx + -0x7d < 0;
      b17 = player2 == (int *)0x7e;
      MyStackIdx = player2;
      MyStack[(int)player2] = (int)player5;
      goto L_080d0017;
    }
    l20 = (float80)fpatan((float80)stk_100[0],(float80)1);
    stk_100[0] = (float)l20;
    break;
  case 0x146:
    c4 = SPopF(player2,stk_100);
    if (ZEXT8(c4) == 3) {
      stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
      value2 = (int *)(int)X87_FIST32(stk_100[0]);
      stk_24 = value2;
      goto L_080cfe8d;
    }
    l20 = X87_TRUNC((float80)((double)1.4426950408889634) * (float80)stk_100[0]);
    l21 = (float80)f2xm1((float80)((double)1.4426950408889634) * (float80)stk_100[0] - l20);
    l20 = (float80)fscale((float80)1 + l21,l20);
    stk_8c = (double)l20;
    l20 = (float80)stk_8c;
L_080cfef8:
    pi16 = (int *)*trigger;
    stk_100[0] = (float)l20;
    goto L_080d04fc;
  case 0x147:
    c4 = SPopF(player2,stk_100);
    if (ZEXT8(c4) == 3) {
      stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
      player5 = (int *)(int)X87_FIST32(stk_100[0]);
      stk_24 = player5;
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",stale_EDX_16,stale_EDX_16);
        ErrorExit();
      }
      player2 = (int *)((int)MyStackIdx + 1);
      b19 = SBORROW4((int)player2,0x7e);
      b18 = (int)MyStackIdx + -0x7d < 0;
      b17 = player2 == (int *)0x7e;
      MyStackIdx = player2;
      MyStack[(int)player2] = (int)player5;
      goto L_080d0017;
    }
    if ((float80)stk_100[0] <= (float80)0.0) {
      if (!b18) {
        msg = "took ln of a non-positive number";
        goto L_080cffce;
      }
      msg = "took ln of a non-positive number";
L_080cffb7:
      WarnR((int)player,(int)player2,(int)msg);
      pi16 = stale_EDX_17;
      goto L_080cffd7;
    }
    l20 = (float80)log2((float80)stk_100[0]);
    stk_100[0] = (float)((float80)((double)0.6931471805599453) * l20);
    break;
  case 0x148:
    if (-1 < (int)MyStackIdx) {
      count = (int *)MyStack[(int)MyStackIdx];
      MyStackIdx = (int *)((int)MyStackIdx + -1);
    }
    if ((int *)0x7fffffff < pi2) {
      StackUnderflow();
    }
    player5 = MyStackIdx;
    if (-1 < (int)MyStackIdx) {
      stk_150 = (int *)MyStack[(int)MyStackIdx];
      MyStackIdx = (int *)((int)MyStackIdx + -1);
    }
    player5 = (int *)(uint32_t)(player5 < (int *)0x80000000);
    if (player5 == (int *)0x0) {
      StackUnderflow();
      player5 = stale_EDX_19;
    }
    if (count == (int *)0x4) {
L_080d01d5:
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",anim,anim);
        ErrorExit();
      }
      player5 = (int *)((int)MyStackIdx + 1);
      MyStackIdx = player5;
      MyStack[(int)player5] = (int)stk_150;
      anim = trigger;
      goto L_join_080cf697;
    }
    if (count == (int *)0x0) {
      if ((int)stk_150 < 0) {
        stk_150 = (int *)-(int)stk_150;
      }
      goto L_080d00b0;
    }
    i15 = (int)count + -1;
    if (i15 != 0) {
      sprintf((char *)ErrorMessage,"Panic: aborting",i15,i15);
      ErrorExit();
      return;
    }
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",MyStackIdx,MyStackIdx);
      ErrorExit();
      player5 = stale_EDX_20;
    }
    player2 = (int *)((int)MyStackIdx + 1);
    MyStackIdx = player2;
    MyStack[(int)player2] = (uint32_t)stk_150 & 0x7fffffff;
    trigger = player5;
    goto L_join_080d013d;
  case 0x149:
  case 0x14a:
    if (-1 < (int)MyStackIdx) {
      count = (int *)MyStack[(int)MyStackIdx];
      MyStackIdx = (int *)((int)MyStackIdx + -1);
    }
    if ((int *)0x7fffffff < pi2) {
      StackUnderflow();
    }
    player5 = MyStackIdx;
    if (-1 < (int)MyStackIdx) {
      stk_150 = (int *)MyStack[(int)MyStackIdx];
      MyStackIdx = (int *)((int)MyStackIdx + -1);
    }
    if ((int *)0x7fffffff < player5) {
      StackUnderflow();
    }
    if (count == (int *)0x4) goto L_080d01d5;
    if (count == (int *)0x0) {
      count = stk_150;
      break;
    }
    if (count != (int *)0x1) {
      msg = "Panic: aborting";
      s2 = ErrorMessage;
      player5 = player2;
      goto L_080d04e9;
    }
    if (*trigger == 0x149) {
      stk_c0 = entry_FPUControlWord & 0xf3ff | 0x400;
      stk_cc = (double)X87_FLOOR(BITS_I2F(stk_150));
      stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
      stk_24 = (int *)(int)X87_FIST32(stk_cc);
    }
    else {
      stk_e0 = entry_FPUControlWord & 0xf3ff | 0x800;
      stk_ec = (double)X87_CEIL(BITS_I2F(stk_150));
      stk_20 = CONCAT22((*(uint16_t *)((char *)&stk_20 + 2)),entry_FPUControlWord);
      stk_24 = (int *)(int)X87_FIST32(stk_ec);
    }
L_080cdf6f:
    count = stk_24;
    break;
  case 0x14b:
    c4 = SPopI((int)player2,(int *)&count);
    stk_14c = stale_EDX_21;
    if (ZEXT8(c4) == 3) {
L_080d0445:
      player2 = count;
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",MyStackIdx,MyStackIdx);
        ErrorExit();
        stk_14c = stale_EDX_25;
      }
      player5 = (int *)((int)MyStackIdx + 1);
      b19 = SBORROW4((int)player5,0x7e);
      b18 = (int)MyStackIdx + -0x7d < 0;
      b17 = player5 == (int *)0x7e;
      MyStackIdx = player5;
      MyStack[(int)player5] = (int)player2;
      goto L_080d0485;
    }
    value = (int)count + -1;
L_080d0371:
    anim = (int *)player2[PL_ANIM];
    count = (int *)AnimCurElemStartTime(anim,value);
    if (count == (int *)0xffffffff) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",trigger,trigger);
        ErrorExit();
      }
      MyStackIdx = (int *)((int)MyStackIdx + 1);
L_080d03bd:
      b19 = SBORROW4((int)MyStackIdx,0x7e);
      b18 = (int)MyStackIdx + -0x7e < 0;
      b17 = MyStackIdx == (int *)0x7e;
      MyStack[(int)MyStackIdx] = 0;
      goto L_080d03d0;
    }
    count = (int *)(*(int *)(player2[PL_ANIM] + 0x1c) - (int)count);
    break;
  case 0x14c:
    c4 = SPopI((int)player2,(int *)&count);
    anim = count;
    stk_14c = stale_EDX_22;
    if (ZEXT8(c4) == 3) goto L_080d0445;
    b18 = PlayerAnimExist((int)player2,(int)count);
    count = (int *)ZEXT8(b18);
    break;
  case 0x14d:
    c4 = SPopI((int)player2,(int *)&count);
    anim = count;
    stk_14c = stale_EDX_23;
    if (ZEXT8(c4) == 3) goto L_080d0445;
    b18 = PlayerSelfAnimExist(player2,(int)count);
    count = (int *)ZEXT8(b18);
    break;
  case 0x14e:
    c4 = SPopI((int)player2,(int *)&count);
    stk_14c = stale_EDX_24;
    if (ZEXT8(c4) == 3) goto L_080d0445;
    value = PlayerAccessID((int)count);
L_080cddcb:
    count = (int *)(uint32_t)(value != 0);
    break;
  case 0x14f:
    c4 = SPopI((int)player2,(int *)&count);
    player5 = count;
    if (player2[PL_ISHELPER] == 1) {
      if (ZEXT8(c4) == 3) {
        if (0x7e < (int)MyStackIdx) {
          sprintf((char *)ErrorMessage,"Expression stack overflow.",trigger,trigger);
          ErrorExit();
        }
        value2 = (int *)((int)MyStackIdx + 1);
        b19 = SBORROW4((int)value2,0x7e);
        b18 = (int)MyStackIdx + -0x7d < 0;
        b17 = value2 == (int *)0x7e;
        MyStackIdx = value2;
        MyStack[(int)value2] = (int)player5;
        goto L_080d03d0;
      }
      player2 = (int *)player2[0x986];
      goto L_080cedc3;
    }
L_080cdd3a:
    count = (int *)0x0;
    break;
  case 0x150:
    c4 = SPopI((int)player2,(int *)&count);
    player5 = count;
    if (ZEXT8(c4) != 3) goto L_080cf327;
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",stale_EDX_12,stale_EDX_12);
      ErrorExit();
    }
    player2 = (int *)((int)MyStackIdx + 1);
    b19 = SBORROW4((int)player2,0x7e);
    b18 = (int)MyStackIdx + -0x7d < 0;
    b17 = player2 == (int *)0x7e;
    MyStackIdx = player2;
    MyStack[(int)player2] = (int)player5;
L_080d0017:
    if (b17 || b19 != b18) goto L_080d04a0;
    goto L_080d0489;
  case 0x151:
    c4 = SPopI((int)player2,(int *)&count);
    anim = count;
    if (ZEXT8(c4) == 3) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",stale_EDX_08,stale_EDX_08);
        ErrorExit();
      }
      player2 = (int *)((int)MyStackIdx + 1);
      b19 = SBORROW4((int)player2,0x7e);
      b18 = (int)MyStackIdx + -0x7d < 0;
      b17 = player2 == (int *)0x7e;
      MyStackIdx = player2;
      MyStack[(int)player2] = (int)anim;
      goto L_080d0017;
    }
    if ((int)count < 0) {
      count = (int *)0x0;
      if (b18) {
        WarnR((int)player,(int)player2,(int)&str_negative_projectile_id_speci_cca0);
      }
      else {
        Warn((int)player2,(int)&str_negative_projectile_id_speci_cca0);
      }
    }
    b18 = player2[0x85] == 2;
L_080ce837:
    if (b18) {
L_080ce839:
      if (((int *)player2[0x84] == count) || (count == (int *)0x0)) {
        count = (int *)player2[0x86];
        break;
      }
    }
L_080ce858:
    count = (int *)0xffffffff;
    break;
  case 0x152:
    c4 = SPopI((int)player2,(int *)&count);
    player5 = count;
    if (ZEXT8(c4) != 3) {
      if ((int)count < 0) {
        count = (int *)0x0;
        if (b18) {
          WarnR((int)player,(int)player2,(int)&str_negative_projectile_id_speci_cca0);
        }
        else {
          Warn((int)player2,(int)&str_negative_projectile_id_speci_cca0);
        }
      }
      b18 = player2[0x85] == 1;
      goto L_080ce837;
    }
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",trigger,trigger);
      ErrorExit();
    }
    value2 = (int *)((int)MyStackIdx + 1);
    b19 = SBORROW4((int)value2,0x7e);
    b18 = (int)MyStackIdx + -0x7d < 0;
    b17 = value2 == (int *)0x7e;
    MyStackIdx = value2;
    MyStack[(int)value2] = (int)player5;
    goto L_080d03d0;
  case 0x153:
    c4 = SPopI((int)player2,(int *)&count);
    player5 = count;
    if (ZEXT8(c4) != 3) {
      if ((int)count < 0) {
        count = (int *)0x0;
        if (b18) {
          WarnR((int)player,(int)player2,(int)&str_negative_projectile_id_speci_cca0);
        }
        else {
          Warn((int)player2,(int)&str_negative_projectile_id_speci_cca0);
        }
      }
      if ((player2[0x85] != 0) && (player2[0x85] != 3)) goto L_080ce839;
      goto L_080ce858;
    }
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",trigger,trigger);
      ErrorExit();
    }
    value2 = (int *)((int)MyStackIdx + 1);
    b19 = SBORROW4((int)value2,0x7e);
    b18 = (int)MyStackIdx + -0x7d < 0;
    b17 = value2 == (int *)0x7e;
    MyStackIdx = value2;
    MyStack[(int)value2] = (int)player5;
    goto L_080d03d0;
  case 0x154:
    c4 = SPopI((int)player2,(int *)&count);
    value2 = count;
    if (ZEXT8(c4) == 3) goto L_080cfe8d;
    if ((int)count < 0) {
      count = (int *)0x0;
      if (b18) {
        WarnR((int)player,(int)player2,(int)&str_negative_projid_specified_c91b);
        anim = player;
      }
      else {
        Warn((int)player2,(int)&str_negative_projid_specified_c91b);
      }
    }
    count = (int *)ProjArrayCountActiveID((int *)player2[PL_PROJECTILES],(int)count);
    break;
  case 0x155:
    c4 = SPopI((int)player2,(int *)&count);
    player5 = count;
    if (ZEXT8(c4) == 3) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",stale_EDX_11,stale_EDX_11);
        ErrorExit();
      }
      player2 = (int *)((int)MyStackIdx + 1);
      b19 = SBORROW4((int)player2,0x7e);
      b18 = (int)MyStackIdx + -0x7d < 0;
      b17 = player2 == (int *)0x7e;
      MyStackIdx = player2;
      MyStack[(int)player2] = (int)player5;
      goto L_080d0017;
    }
    if ((int)count < -1) {
      count = (int *)0xffffffff;
      if (b18) {
        WarnR((int)player,(int)player2,(int)&str_illegal_explod_id_for_numexp_cce0);
      }
      else {
        Warn((int)player2,(int)&str_illegal_explod_id_for_numexp_cce0);
      }
    }
    anim = count;
    count = (int *)ExplodCount((int *)g[0x52be],player2[PL_ID],(int)count);
    break;
  case 0x156:
    c4 = SPopI((int)player2,(int *)&count);
    player3 = count;
    if (ZEXT8(c4) == 3) goto L_080cfc8d;
    player5 = count;
    if ((int)count < -1) {
      count = (int *)0xffffffff;
      if (b18) {
        WarnR((int)player,(int)player2,(int)&str_illegal_target_id_for_numtar_cd40);
        anim = player;
        player5 = count;
      }
      else {
        Warn((int)player2,(int)&str_illegal_target_id_for_numtar_cd40);
        player5 = count;
      }
    }
L_080cf217:
    count = (int *)TargetCount(player2[PL_TARGETS],(int)player5);
    break;
  case 0x157:
    c4 = SPopI((int)player2,(int *)&count);
    player3 = count;
    if (ZEXT8(c4) == 3) goto L_080cfc8d;
    if ((int *)0x3b < count) {
      if (b18) {
        WarnR((int)player,(int)player2,(int)&str_var_index_out_of_range);
      }
      else {
        Warn((int)player2,(int)&str_var_index_out_of_range);
      }
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",player2,player2);
        ErrorExit();
      }
      player2 = (int *)((int)MyStackIdx + 1);
      b19 = SBORROW4((int)player2,0x7e);
      b18 = (int)MyStackIdx + -0x7d < 0;
      b17 = player2 == (int *)0x7e;
      MyStackIdx = player2;
      MyStack[(int)player2] = 0;
      goto L_080cfec3;
    }
    count = (int *)player2[(int)(count + 0xe4)];
    break;
  case 0x158:
    c4 = SPopI((int)player2,(int *)&count);
    player5 = count;
    if (ZEXT8(c4) == 3) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",stale_EDX_03,stale_EDX_03);
        ErrorExit();
      }
      player2 = (int *)((int)MyStackIdx + 1);
      b19 = SBORROW4((int)player2,0x7e);
      b18 = (int)MyStackIdx + -0x7d < 0;
      b17 = player2 == (int *)0x7e;
      MyStackIdx = player2;
      MyStack[(int)player2] = (int)player5;
      goto L_080d0017;
    }
    if ((int *)0x27 < count) {
      if (!b18) {
        msg = "fvar index out of range";
        goto L_080cffce;
      }
      msg = "fvar index out of range";
      goto L_080cffb7;
    }
    stk_100[0] = BITS_I2F(player2[(int)(count + 0xf3)]);
    goto L_080cf4e5;
  case 0x159:
    c4 = SPopI((int)player2,(int *)&count);
    player3 = count;
    if (ZEXT8(c4) == 3) goto L_080cfc8d;
    if ((int *)0x4 < count) {
      if (b18) {
        WarnR((int)player,(int)player2,(int)&str_sysvar_index_out_of_range_c8e6);
      }
      else {
        Warn((int)player2,(int)&str_sysvar_index_out_of_range_c8e6);
      }
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",player2,player2);
        ErrorExit();
      }
      player2 = (int *)((int)MyStackIdx + 1);
      b19 = SBORROW4((int)player2,0x7e);
      b18 = (int)MyStackIdx + -0x7d < 0;
      b17 = player2 == (int *)0x7e;
      MyStackIdx = player2;
      MyStack[(int)player2] = 0;
      goto L_080cfec3;
    }
    count = (int *)player2[(int)(count + 0xfd)];
    break;
  case 0x15a:
    c4 = SPopI((int)player2,(int *)&count);
    player5 = count;
    if (ZEXT8(c4) == 3) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",stale_EDX_04,stale_EDX_04);
        ErrorExit();
      }
      player2 = (int *)((int)MyStackIdx + 1);
      b19 = SBORROW4((int)player2,0x7e);
      b18 = (int)MyStackIdx + -0x7d < 0;
      b17 = player2 == (int *)0x7e;
      MyStackIdx = player2;
      MyStack[(int)player2] = (int)player5;
      goto L_080d0017;
    }
    if ((int *)0x4 < count) {
      if (b18) {
        WarnR((int)player,(int)player2,(int)&str_sysfvar_index_out_of_range_c900);
        stk_14c = stale_EDX_05;
      }
      else {
        Warn((int)player2,(int)&str_sysfvar_index_out_of_range_c900);
        stk_14c = stale_EDX_06;
      }
      goto L_080ce647;
    }
    stk_100[0] = BITS_I2F(player2[(int)count + 0x3f9]);
    goto L_080cf4e5;
  case 0x15b:
    c4 = SPopI((int)player2,(int *)&count);
    player5 = count;
    if (ZEXT8(c4) != 3) {
      if ((int)count < 0) {
        count = (int *)0x0;
        if (b18) {
          WarnR((int)player,(int)player2,(int)&str_negative_projectile_id_speci_cca0);
        }
        else {
          Warn((int)player2,(int)&str_negative_projectile_id_speci_cca0);
        }
      }
      b18 = player2[0x85] == 3;
      goto L_080ce837;
    }
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",trigger,trigger);
      ErrorExit();
    }
    value2 = (int *)((int)MyStackIdx + 1);
    b19 = SBORROW4((int)value2,0x7e);
    b18 = (int)MyStackIdx + -0x7d < 0;
    b17 = value2 == (int *)0x7e;
    MyStackIdx = value2;
    MyStack[(int)value2] = (int)player5;
L_080d03d0:
    if (!b17 && b19 == b18) {
L_080d0489:
      sprintf((char *)ErrorMessage,"Expression stack overflow.",player2,player2);
      ErrorExit();
    }
L_080d04a0:
    MyStackIdx = (int *)((int)MyStackIdx + 1);
    MyStack[(int)MyStackIdx] = 4;
    return;
  case 0x15c:
    c4 = SPopI((int)player2,(int *)&count);
    player5 = count;
    if (ZEXT8(c4) == 3) {
      if (0x7e < (int)MyStackIdx) {
        sprintf((char *)ErrorMessage,"Expression stack overflow.",stale_EDX_09,stale_EDX_09);
        ErrorExit();
      }
      player2 = (int *)((int)MyStackIdx + 1);
      b19 = SBORROW4((int)player2,0x7e);
      b18 = (int)MyStackIdx + -0x7d < 0;
      b17 = player2 == (int *)0x7e;
      MyStackIdx = player2;
      MyStack[(int)player2] = (int)player5;
      goto L_080d0017;
    }
    count = (int *)AnimElemNo((uint32_t *)player2[PL_ANIM],(int)count);
    if (count == (int *)0xffffffff) {
      count = (int *)0xffffffff;
      pi16 = stale_EDX_10;
      goto L_080cffd7;
    }
  }
  pi16 = (int *)*trigger;
L_080d04fc:
  f1 = stk_100[0];
  if (((((((pi16 == (int *)0x14) || (pi16 == (int *)0x2)) || ((int)pi16 - 0x5aU < 4)) ||
        ((pi16 == (int *)0x2b || (pi16 == (int *)0x2c)))) ||
       ((pi16 == (int *)0x2d || ((pi16 == (int *)0x2e || (pi16 == (int *)0x7)))))) ||
      (pi16 == (int *)0x3e)) || ((pi16 == (int *)0x40 || (pi16 == (int *)0x3f)))) {
    player2 = count;
    switch((int)i15) {
    case 0:
      pi16 = (int *)trigger[7];
      player2 = (int *)(uint32_t)(count == pi16);
      break;
    case 1:
      pi16 = (int *)trigger[7];
      player2 = (int *)(uint32_t)(count != pi16);
      break;
    case 2:
      pi16 = (int *)trigger[7];
      player2 = (int *)(uint32_t)((int)pi16 < (int)count);
      break;
    case 3:
      pi16 = (int *)trigger[7];
      player2 = (int *)(uint32_t)((int)pi16 <= (int)count);
      break;
    case 4:
      pi16 = (int *)trigger[7];
      player2 = (int *)(uint32_t)((int)count < (int)pi16);
      break;
    case 5:
      pi16 = (int *)trigger[7];
      player2 = (int *)(uint32_t)((int)count <= (int)pi16);
      break;
    case 10:
      pi16 = (int *)0x0;
      player2 = pi16;
      if (trigger[7] <= (int)count) {
L_080d05fb:
        pi16 = (int *)0x0;
        player2 = pi16;
        if ((int)count <= trigger[8]) {
L_080d0612:
          pi16 = (int *)0x1;
          player2 = pi16;
        }
      }
      break;
    case 0xb:
      pi16 = (int *)0x0;
      player2 = pi16;
      if (trigger[7] <= (int)count) {
L_080d060d:
        pi16 = (int *)0x0;
        player2 = pi16;
        if ((int)count < trigger[8]) goto L_080d0612;
      }
      break;
    case 0xc:
      pi16 = (int *)0x0;
      player2 = pi16;
      if (trigger[7] < (int)count) goto L_080d05fb;
      break;
    case 0xd:
      pi16 = (int *)0x0;
      player2 = pi16;
      if (trigger[7] < (int)count) goto L_080d060d;
    }
    count = player2;
    if (b17) {
      count = (int *)(1 - (int)count);
    }
  }
  player2 = count;
  if (trigger[6] == 0) {
L_080d0643:
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",pi16,pi16);
      ErrorExit();
    }
    stk_150 = (int *)((int)MyStackIdx + 1);
    MyStackIdx = stk_150;
    MyStack[(int)stk_150] = (int)player2;
    player2 = stk_150;
L_join_080d00e6:
    if (0x7e < (int)player2) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",stk_150,stk_150);
      ErrorExit();
    }
    MyStackIdx = (int *)((int)MyStackIdx + 1);
    MyStack[(int)MyStackIdx] = 0;
  }
  else if (trigger[6] == 1) {
    if (0x7e < (int)MyStackIdx) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",anim,anim);
      ErrorExit();
    }
    player2 = (int *)((int)MyStackIdx + 1);
    MyStackIdx = player2;
    MyStack[(int)player2] = BITS_F2I(int, f1);
L_join_080d013d:
    if (0x7e < (int)player2) {
      sprintf((char *)ErrorMessage,"Expression stack overflow.",trigger,trigger);
      ErrorExit();
    }
    MyStackIdx = (int *)((int)MyStackIdx + 1);
    MyStack[(int)MyStackIdx] = 1;
  }
  else {
    ErrorExit();
  }
  return;
}
#undef stk_150
#undef stk_14c
#undef stk_148
#undef stk_144
#undef stk_140
#undef stk_13c
#undef stk_138
#undef stk_134
#undef stk_11c
#undef stk_118
#undef stk_114
#undef player6
#undef stk_10c
#undef stk_108
#undef count
#undef stk_100
#undef stk_ec
#undef stk_e0
#undef stk_cc
#undef stk_c0
#undef stk_8c
#undef stk_7c
#undef stk_6c
#undef stk_5c
#undef stk_24
#undef stk_20

/* TriggerFree @ 0x080d0740, 51 bytes
 *
 * Frees a trigger argument block of an expression.
 *
 * Parameters:
 *   arg1         void *
 *
 * Calls: FreeExpression
 * C library: free
 * Called by: FreeExpression, InfToPostArray
 *
 * Elecbyte file: src/mugen/st-trig.c
 */
void TriggerFree(void *arg1)

{
  if (*(void **)((int)arg1 + 0x34) != (void *)0x0) {
    free(*(void **)((int)arg1 + 0x34));
  }
  FreeExpression((int *)((int)arg1 + 8));
  free(arg1);
  return;
}

/* trigcpy @ 0x080d0780, 161 bytes
 *
 * Copies a trigger argument block (deep copy of its expression lists).
 * "Alloc error" on failure.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int *
 *
 * Calls: expcpytrig, ecalloc, ErrorExit
 * C library: strlen, strcpy, sprintf
 * Called by: expcpytrig
 * Messages:
 *   "Alloc error"
 *   "Random data"
 *
 * Elecbyte file: src/mugen/st-trig.c
 */
uint32_t trigcpy(int *arg1,int *arg2)

{
  size_t s1;
  uint32_t u2;
  int mem;
  int *stale_ECX;
  int *pi4;
  int *pi5;
  char *format;
  
  pi4 = arg2;
  pi5 = arg1;
  for (mem = 0xe; mem != 0; mem = mem + -1) {
    *pi5 = *pi4;
    pi4 = pi4 + 1;
    pi5 = pi5 + 1;
  }
  expcpytrig(arg1 + 2,arg2 + 2);
  if ((char *)arg2[0xd] == (char *)0x0) {
L_080d0814:
    u2 = 1;
  }
  else {
    if (*arg2 - 0x5aU < 4) {
      s1 = strlen((char *)arg2[0xd]);
      mem = ecalloc(1,s1 + 1);
      arg1[0xd] = mem;
      if (mem != 0) {
        strcpy((char *)arg1[0xd],(char *)arg2[0xd]);
        goto L_080d0814;
      }
      format = "Alloc error";
    }
    else {
      format = "Random data";
      arg1 = stale_ECX;
    }
    sprintf((char *)ErrorMessage,format,arg1,arg1);
    ErrorExit();
    u2 = 0;
  }
  return u2;
}

