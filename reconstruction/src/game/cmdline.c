/*
 * cmdline.c -- command line
 * Parses the command line options (Quick VS, motif, logging, debug switches)
 * and prints the help text.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/cmdline.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* ParseCmdLine @ 0x0808ca40, 1615 bytes
 *
 * Parses the command line into the options record. The options printed by
 * PrintHelp (case-sensitive):
 * - "-h"/"-?" help, "-log <logfile>" match log, "-r <sysfile>" motif;
 * - Quick VS: "-p<n> <player>", "-p<n>.ai 1", "-p<n>.color <col>",
 * "-p<n>.life <life>", "-p<n>.power <power>", "-rounds <num>", "-s <stage>";
 * - debug: "-nojoy", "-nomusic", "-nosound".
 *
 * Also accepted but not in the help text: "-ailevel", "-speed",
 * "-speedtest", "-stresstest", "-storyboard", "-rubric". An unknown option
 * prints "Error: Invalid option %s" and the help text, then exits.
 *
 * Parameters:
 *   opts         MugenCmdLine *
 *   argc         int
 *   argv         char **
 *
 * Calls: PrintHelp
 * C library: strcpy, __strtol_internal, printf
 * Called by: _mangled_main
 * Messages:
 *   "Error: Invalid option %s\n\n"
 *
 * Elecbyte file: src/mugen/cmdline.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to
 *       builtin_strncpy
 * Note: 6 data addresses refer to the data image (data/mugen_data.S).
 */
void ParseCmdLine(MugenCmdLine *opts,int argc,char **argv)

{
  int i2;
  uint8_t *pb2;
  uint32_t u3;
  int i4;
  int stale_ECX;
  int stale_ECX_00;
  int stale_ECX_01;
  int stale_ECX_02;
  int stale_ECX_03;
  int stale_ECX_04;
  int stale_ECX_05;
  int stale_ECX_06;
  int stale_ECX_07;
  int stale_ECX_08;
  int stale_ECX_09;
  int stale_ECX_10;
  int stale_ECX_11;
  int i5;
  MugenCmdLine *pMVar6;
  uint8_t *pb7;
  uint8_t u8;
  bool b9;
  bool b10;
  bool b11;
  char *src;
  char *stk_1c;
  int stk_14;
  
  i2 = 0;
  i5 = 3;
  pMVar6 = opts;
  for (i4 = 0xcb; i4 != 0; i4 = i4 + -1) {
    pMVar6->mode = 0;
    pMVar6 = (MugenCmdLine *)pMVar6->rest;
  }
  opts->rest[0x290] = 0x40;
  opts->rest[0x291] = 0x42;
  opts->rest[0x292] = 0xf;
  opts->rest[0x293] = 0;
  opts->rest[0x2dc] = 0xe7;
  opts->rest[0x2dd] = 3;
  opts->rest[0x2de] = 0;
  opts->rest[0x2df] = 0;
  do {
    pb2 = opts->rest + i2 + 0x294;
    pb2[0] = 0xff;
    pb2[1] = 0xff;
    pb2[2] = 0xff;
    pb2[3] = 0xff;
    pb2 = opts->rest + i2 + 0x2a4;
    pb2[0] = 0xff;
    pb2[1] = 0xff;
    pb2[2] = 0xff;
    pb2[3] = 0xff;
    pb2 = opts->rest + i2 + 0x2b4;
    pb2[0] = 0xff;
    pb2[1] = 0xff;
    pb2[2] = 0xff;
    pb2[3] = 0xff;
    pb2 = opts->rest + i2 + 0x2c4;
    pb2[0] = 0xff;
    pb2[1] = 0xff;
    pb2[2] = 0xff;
    pb2[3] = 0xff;
    i2 = i2 + 4;
    i5 = i5 + -1;
  } while (-1 < i5);
  i2 = 1;
  stk_14 = 0;
  if (1 < argc) {
    i4 = 0;
    do {
      stk_1c = argv[i2];
      if (*stk_1c != '-') {
        pMVar6 = opts;
        if (stk_14 == 0) {
L_0808d06b:
          strcpy((char *)pMVar6,stk_1c);
          i4 = stale_ECX_11;
        }
        else if (stk_14 == 1) {
          pMVar6 = (MugenCmdLine *)(opts->rest + 0x3c);
          goto L_0808d06b;
        }
        stk_14 = stk_14 + 1;
        goto L_0808d07c;
      }
      u8 = (int)stk_1c[1] - 0x3fU < 0x34;
      switch((int)stk_1c[1] - 0x3fU) {
      case 0:
      case 0x29:
        PrintHelp();
        stk_1c = argv[i2];
      case 0x22:
        b9 = (uint8_t *)(stk_1c + 1) == (uint8_t *)0x0;
        i4 = 8;
        pb2 = (uint8_t *)(stk_1c + 1);
        pb7 = (uint8_t *)"ailevel";
        do {
          if (i4 == 0) break;
          i4 = i4 + -1;
          u8 = *pb2 < *pb7;
          b9 = *pb2 == *pb7;
          pb2 = pb2 + 1;
          pb7 = pb7 + 1;
        } while (b9);
        if ((!(bool)u8 && !b9) == (bool)u8) {
          i2 = i2 + 1;
          if (argc <= i2) {
            PrintHelp();
          }
          u3 = __strtol_internal((uint8_t *)argv[i2],(uint32_t *)0x0,10,0);
          *(uint32_t *)(opts->rest + 0x2d8) = u3;
          i4 = stale_ECX;
          if (8 < u3 - 1) {
            opts->rest[0x2d8] = 4;
            opts->rest[0x2d9] = 0;
            opts->rest[0x2da] = 0;
            opts->rest[0x2db] = 0;
          }
        }
        else {
L_0808d020:
          PrintHelp();
          i4 = stale_ECX_09;
        }
        break;
      default:
        printf("Error: Invalid option %s\n\n",argv[i2],i4,i4);
        PrintHelp();
        i4 = stale_ECX_10;
        break;
      case 0x2d:
        u3 = (uint8_t)stk_1c[1] - 0x6c;
        if (((u3 == 0) && (u3 = (uint8_t)stk_1c[2] - 0x6f, u3 == 0)) &&
           (u3 = (uint8_t)stk_1c[3] - 0x67, u3 == 0)) {
          u3 = (uint32_t)(uint8_t)stk_1c[4];
        }
        if (u3 == 0) {
          i2 = i2 + 1;
          if (argc <= i2) {
            PrintHelp();
          }
          strcpy((char *)(opts->rest + 0x184),argv[i2]);
          opts->rest[0x180] = 1;
          opts->rest[0x181] = 0;
          opts->rest[0x182] = 0;
          opts->rest[0x183] = 0;
          i4 = stale_ECX_00;
          break;
        }
        goto L_0808d020;
      case 0x2f:
        i4 = 8;
        b9 = (uint8_t *)(stk_1c + 1) == (uint8_t *)0x0;
        pb2 = (uint8_t *)(stk_1c + 1);
        pb7 = (uint8_t *)"nomusic";
        do {
          if (i4 == 0) break;
          i4 = i4 + -1;
          u8 = *pb2 < *pb7;
          b9 = *pb2 == *pb7;
          pb2 = pb2 + 1;
          pb7 = pb7 + 1;
        } while (b9);
        b11 = (!(bool)u8 && !b9) < (uint8_t)u8;
        if ((!(bool)u8 && !b9) == (bool)u8) {
          opts->rest[0x288] = 1;
          opts->rest[0x289] = 0;
          opts->rest[0x28a] = 0;
          opts->rest[0x28b] = 0;
        }
        else {
          i4 = 8;
          b9 = (uint8_t *)(stk_1c + 1) == (uint8_t *)0x0;
          pb2 = (uint8_t *)(stk_1c + 1);
          pb7 = (uint8_t *)"nosound";
          do {
            if (i4 == 0) break;
            i4 = i4 + -1;
            b11 = *pb2 < *pb7;
            b9 = *pb2 == *pb7;
            pb2 = pb2 + 1;
            pb7 = pb7 + 1;
          } while (b9);
          b10 = (!b11 && !b9) < b11;
          if ((!b11 && !b9) == b11) {
            opts->rest[0x284] = 1;
            opts->rest[0x285] = 0;
            opts->rest[0x286] = 0;
            opts->rest[0x287] = 0;
          }
          else {
            b9 = (uint8_t *)(stk_1c + 1) == (uint8_t *)0x0;
            i4 = 6;
            pb2 = (uint8_t *)(stk_1c + 1);
            pb7 = &str_nojoy;
            do {
              if (i4 == 0) break;
              i4 = i4 + -1;
              b10 = *pb2 < *pb7;
              b9 = *pb2 == *pb7;
              pb2 = pb2 + 1;
              pb7 = pb7 + 1;
            } while (b9);
            if ((!b10 && !b9) != b10) goto L_0808d020;
            opts->rest[0x28c] = 1;
            opts->rest[0x28d] = 0;
            opts->rest[0x28e] = 0;
            opts->rest[0x28f] = 0;
          }
        }
        break;
      case 0x31:
        if (3 < (uint8_t)(stk_1c[2] - 0x31U)) goto L_0808d020;
        if (argc <= i2 + 1) {
          PrintHelp();
          stk_1c = argv[i2];
        }
        i4 = (int)stk_1c[2];
        stk_14 = i4 + -0x31;
        if (stk_1c[3] != '.') {
          if (stk_1c[3] != '\0') goto L_0808d020;
          src = argv[i2 + 1];
          pb2 = (uint8_t *)(stk_14 * 0x40 + (int)opts);
          goto L_0808cf5e;
        }
        u3 = (uint8_t)stk_1c[4] - 0x61;
        if ((u3 == 0) && (u3 = (uint8_t)stk_1c[5] - 0x69, u3 == 0)) {
          u3 = (uint32_t)(uint8_t)stk_1c[6];
        }
        if (u3 == 0) {
          i2 = i2 + 1;
          u3 = __strtol_internal((uint8_t *)argv[i2],(uint32_t *)0x0,10,0);
          *(uint32_t *)(opts->rest + i4 * 4 + 0x1d0) = u3;
          i4 = stale_ECX_01;
        }
        else {
          b9 = (char *)0xfffffffb < stk_1c;
          b11 = (uint8_t *)(stk_1c + 4) == (uint8_t *)0x0;
          i5 = 6;
          pb2 = (uint8_t *)(stk_1c + 4);
          pb7 = (uint8_t *)(int)&str_color;
          do {
            if (i5 == 0) break;
            i5 = i5 + -1;
            b9 = *pb2 < *pb7;
            b11 = *pb2 == *pb7;
            pb2 = pb2 + 1;
            pb7 = pb7 + 1;
          } while (b11);
          if ((!b9 && !b11) == b9) {
            i2 = i2 + 1;
            u3 = __strtol_internal((uint8_t *)argv[i2],(uint32_t *)0x0,10,0);
            *(uint32_t *)(opts->rest + i4 * 4 + 0x1e0) = u3 - 1;
            i4 = stale_ECX_02;
          }
          else {
            b9 = (char *)0xfffffffb < stk_1c;
            b11 = (uint8_t *)(stk_1c + 4) == (uint8_t *)0x0;
            i5 = 5;
            pb2 = (uint8_t *)(stk_1c + 4);
            pb7 = (uint8_t *)(int)&str_life;
            do {
              if (i5 == 0) break;
              i5 = i5 + -1;
              b9 = *pb2 < *pb7;
              b11 = *pb2 == *pb7;
              pb2 = pb2 + 1;
              pb7 = pb7 + 1;
            } while (b11);
            if ((!b9 && !b11) == b9) {
              i2 = i2 + 1;
              u3 = __strtol_internal((uint8_t *)argv[i2],(uint32_t *)0x0,10,0);
              *(uint32_t *)(opts->rest + i4 * 4 + 0x1f0) = u3;
              i4 = stale_ECX_03;
            }
            else {
              b9 = (char *)0xfffffffb < stk_1c;
              b11 = (uint8_t *)(stk_1c + 4) == (uint8_t *)0x0;
              i5 = 6;
              pb2 = (uint8_t *)(stk_1c + 4);
              pb7 = (uint8_t *)(int)&str_power;
              do {
                if (i5 == 0) break;
                i5 = i5 + -1;
                b9 = *pb2 < *pb7;
                b11 = *pb2 == *pb7;
                pb2 = pb2 + 1;
                pb7 = pb7 + 1;
              } while (b11);
              if ((!b9 && !b11) != b9) goto L_0808d020;
              i2 = i2 + 1;
              u3 = __strtol_internal((uint8_t *)argv[i2],(uint32_t *)0x0,10,0);
              *(uint32_t *)(opts->rest + i4 * 4 + 0x200) = u3;
              i4 = stale_ECX_04;
            }
          }
        }
        break;
      case 0x33:
        b9 = false;
        if (stk_1c[2] != '\0') {
          i4 = 7;
          b11 = (uint8_t *)(stk_1c + 1) == (uint8_t *)0x0;
          pb2 = (uint8_t *)(stk_1c + 1);
          pb7 = (uint8_t *)"rubric";
          do {
            if (i4 == 0) break;
            i4 = i4 + -1;
            b9 = *pb2 < *pb7;
            b11 = *pb2 == *pb7;
            pb2 = pb2 + 1;
            pb7 = pb7 + 1;
          } while (b11);
          b10 = (!b9 && !b11) < b9;
          if ((!b9 && !b11) != b9) {
            b9 = (uint8_t *)(stk_1c + 1) == (uint8_t *)0x0;
            i4 = 7;
            pb2 = (uint8_t *)(stk_1c + 1);
            pb7 = (uint8_t *)"rounds";
            do {
              if (i4 == 0) break;
              i4 = i4 + -1;
              b10 = *pb2 < *pb7;
              b9 = *pb2 == *pb7;
              pb2 = pb2 + 1;
              pb7 = pb7 + 1;
            } while (b9);
            if ((!b10 && !b9) != b10) goto L_0808d020;
            i2 = i2 + 1;
            if (argc <= i2) {
              PrintHelp();
            }
            u3 = __strtol_internal((uint8_t *)argv[i2],(uint32_t *)0x0,10,0);
            *(uint32_t *)(opts->rest + 0x290) = u3;
            i4 = stale_ECX_05;
            if ((int)u3 < 2) {
              opts->rest[0x290] = 1;
              opts->rest[0x291] = 0;
              opts->rest[0x292] = 0;
              opts->rest[0x293] = 0;
            }
            break;
          }
        }
        if (argc <= i2 + 1) {
          PrintHelp();
        }
        pb2 = opts->rest + 0x13c;
        src = argv[i2 + 1];
        goto L_0808cf5e;
      case 0x34:
        b9 = false;
        if (stk_1c[2] != '\0') {
          i4 = 6;
          b11 = (uint8_t *)(stk_1c + 1) == (uint8_t *)0x0;
          pb2 = (uint8_t *)(stk_1c + 1);
          pb7 = (uint8_t *)(int)&str_stage;
          do {
            if (i4 == 0) break;
            i4 = i4 + -1;
            b9 = *pb2 < *pb7;
            b11 = *pb2 == *pb7;
            pb2 = pb2 + 1;
            pb7 = pb7 + 1;
          } while (b11);
          b10 = (!b9 && !b11) < b9;
          if ((!b9 && !b11) != b9) {
            i4 = 10;
            b9 = (uint8_t *)(stk_1c + 1) == (uint8_t *)0x0;
            pb2 = (uint8_t *)(stk_1c + 1);
            pb7 = (uint8_t *)"speedtest";
            do {
              if (i4 == 0) break;
              i4 = i4 + -1;
              b10 = *pb2 < *pb7;
              b9 = *pb2 == *pb7;
              pb2 = pb2 + 1;
              pb7 = pb7 + 1;
            } while (b9);
            b11 = (!b10 && !b9) < b10;
            if ((!b10 && !b9) == b10) {
              opts->rest[0x2e0] = 1;
              opts->rest[0x2e1] = 0;
              opts->rest[0x2e2] = 0;
              opts->rest[0x2e3] = 0;
            }
            else {
              i4 = 0xb;
              b9 = (uint8_t *)(stk_1c + 1) == (uint8_t *)0x0;
              pb2 = (uint8_t *)(stk_1c + 1);
              pb7 = (uint8_t *)(int)&str_storyboard;
              do {
                if (i4 == 0) break;
                i4 = i4 + -1;
                b11 = *pb2 < *pb7;
                b9 = *pb2 == *pb7;
                pb2 = pb2 + 1;
                pb7 = pb7 + 1;
              } while (b9);
              b10 = (!b11 && !b9) < b11;
              if ((!b11 && !b9) == b11) {
                if (argc <= i2 + 1) {
                  PrintHelp();
                }
                src = argv[i2 + 1];
                pb2 = opts->rest + 0x2e8;
                goto L_0808cf5e;
              }
              i4 = 0xb;
              b9 = (uint8_t *)(stk_1c + 1) == (uint8_t *)0x0;
              pb2 = (uint8_t *)(stk_1c + 1);
              pb7 = (uint8_t *)"stresstest";
              do {
                if (i4 == 0) break;
                i4 = i4 + -1;
                b10 = *pb2 < *pb7;
                b9 = *pb2 == *pb7;
                pb2 = pb2 + 1;
                pb7 = pb7 + 1;
              } while (b9);
              b11 = (!b10 && !b9) < b10;
              if ((!b10 && !b9) == b10) {
                i2 = i2 + 1;
                if (argc <= i2) {
                  PrintHelp();
                }
                u3 = __strtol_internal((uint8_t *)argv[i2],(uint32_t *)0x0,10,0);
                *(uint32_t *)(opts->rest + 0x2e4) = u3;
                i4 = stale_ECX_07;
              }
              else {
                b9 = (uint8_t *)(stk_1c + 1) == (uint8_t *)0x0;
                i4 = 6;
                pb2 = (uint8_t *)(stk_1c + 1);
                pb7 = (uint8_t *)(int)&str_speed;
                do {
                  if (i4 == 0) break;
                  i4 = i4 + -1;
                  b11 = *pb2 < *pb7;
                  b9 = *pb2 == *pb7;
                  pb2 = pb2 + 1;
                  pb7 = pb7 + 1;
                } while (b9);
                if ((!b11 && !b9) != b11) goto L_0808d020;
                i2 = i2 + 1;
                if (argc <= i2) {
                  PrintHelp();
                }
                u3 = __strtol_internal((uint8_t *)argv[i2],(uint32_t *)0x0,10,0);
                *(uint32_t *)(opts->rest + 0x2dc) = u3;
                i4 = stale_ECX_08;
                if (0x12 < u3 + 9) {
                  opts->rest[0x2dc] = 0xe7;
                  opts->rest[0x2dd] = 3;
                  opts->rest[0x2de] = 0;
                  opts->rest[0x2df] = 0;
                }
              }
            }
            break;
          }
        }
        if (argc <= i2 + 1) {
          PrintHelp();
        }
        pb2 = opts->rest + 0xfc;
        src = argv[i2 + 1];
L_0808cf5e:
        i2 = i2 + 1;
        strcpy((char *)pb2,src);
        i4 = stale_ECX_06;
      }
L_0808d07c:
      i2 = i2 + 1;
    } while (i2 < argc);
  }
  return;
}

/* PrintHelp @ 0x0808d090, 83 bytes
 *
 * Prints the version banner ("M.U.G.E.N test ver ... (c) Elecbyte") and the
 * list of command line options to stdout.
 *
 * C library: sprintf, strcat, printf, exit
 * Called by: ParseCmdLine
 * Messages:
 *   "M.U.G.E.N test ver %i.%02i.%02i \t(c)%i Elecbyte\n\n"
 *   "Options (case sensitive):\n -h -? \tHelp\n -log <logfile> \tRecords
 *     match data to <logfile>\n -r <sysfile> \tLoads motif <sysfile>. eg. -r
 *     motifdir or -r motifdir/system.def\nQuick VS Options:\n -p<?>
 *     <playername> \tLoads player ?, eg. -p3 kfm\n -p<?>.ai 1 \tEnables AI
 *     for player ?, eg. -p1.ai 1\n -p<?>.color <col> \tSet player ?\'s color
 *     to <col>\n -p<?>.life <life> \tSets player ?\'s life to <life>\n
 *     -p<?>.power <power> \tSets player ?\'s power to <power>\n -rounds
 *     <num> \tPlays for <num> rounds, and then quits\n -s <stagename>
 *     \tLoads stage <stagename>\nDebug Options:\n -nojoy   \tDisables
 *     joysticks\n -nomusic \tDisables music\n -nosound \tDisables all sound
 *     effects and music\n\n"
 *
 * Elecbyte file: src/mugen/cmdline.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x4010 bytes,
 *       1 variables), because their address is taken.
 */
uint32_t PrintHelp(void)

{

  unsigned char frame[0x4010] __attribute__((aligned(16)));
#define stk_400c (*(char (*)[16392])(frame + 0x4))
  
  sprintf(stk_400c,"M.U.G.E.N test ver %i.%02i.%02i \t(c)%i Elecbyte\n\n",MUGENDATE_Y,MUGENDATE_M,
          MUGENDATE_D,MUGENDATE_Y);
  strcat(stk_400c,
         "Options (case sensitive):\n -h -? \tHelp\n -log <logfile> \tRecords match data to <logfile>\n -r <sysfile> \tLoads motif <sysfile>. eg. -r motifdir or -r motifdir/system.def\nQuick VS Options:\n -p<?> <playername> \tLoads player ?, eg. -p3 kfm\n -p<?>.ai 1 \tEnables AI for player ?, eg. -p1.ai 1\n -p<?>.color <col> \tSet player ?\'s color to <col>\n -p<?>.life <life> \tSets player ?\'s life to <life>\n -p<?>.power <power> \tSets player ?\'s power to <power>\n -rounds <num> \tPlays for <num> rounds, and then quits\n -s <stagename> \tLoads stage <stagename>\nDebug Options:\n -nojoy   \tDisables joysticks\n -nomusic \tDisables music\n -nosound \tDisables all sound effects and music\n\n"
        );
  printf(stk_400c);
                    /* WARNING: Subroutine does not return */
  exit(0);
}
#undef stk_400c

