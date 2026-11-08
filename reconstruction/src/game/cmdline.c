/*
 * cmdline.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0808ca40-0x0808d0e3, 2 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* ParseCmdLine @ 0x0808ca40, 1615 bytes
 * REVIEW: calls-missing-in-pid:builtin_strncpy
 * FIXUP: 6 data addresses written as literals replaced by data-image references */
void ParseCmdLine(MugenCmdLine *opts,int argc,char **argv)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  int iVar4;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int extraout_ECX_03;
  int extraout_ECX_04;
  int extraout_ECX_05;
  int extraout_ECX_06;
  int extraout_ECX_07;
  int extraout_ECX_08;
  int extraout_ECX_09;
  int extraout_ECX_10;
  int extraout_ECX_11;
  int iVar5;
  MugenCmdLine *pMVar6;
  byte *pbVar7;
  undefined1 uVar8;
  bool bVar9;
  bool bVar10;
  bool bVar11;
  char *__src;
  char *local_1c;
  int local_14;
  
  iVar1 = 0;
  iVar5 = 3;
  pMVar6 = opts;
  for (iVar4 = 0xcb; iVar4 != 0; iVar4 = iVar4 + -1) {
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
    pbVar2 = opts->rest + iVar1 + 0x294;
    pbVar2[0] = 0xff;
    pbVar2[1] = 0xff;
    pbVar2[2] = 0xff;
    pbVar2[3] = 0xff;
    pbVar2 = opts->rest + iVar1 + 0x2a4;
    pbVar2[0] = 0xff;
    pbVar2[1] = 0xff;
    pbVar2[2] = 0xff;
    pbVar2[3] = 0xff;
    pbVar2 = opts->rest + iVar1 + 0x2b4;
    pbVar2[0] = 0xff;
    pbVar2[1] = 0xff;
    pbVar2[2] = 0xff;
    pbVar2[3] = 0xff;
    pbVar2 = opts->rest + iVar1 + 0x2c4;
    pbVar2[0] = 0xff;
    pbVar2[1] = 0xff;
    pbVar2[2] = 0xff;
    pbVar2[3] = 0xff;
    iVar1 = iVar1 + 4;
    iVar5 = iVar5 + -1;
  } while (-1 < iVar5);
  iVar1 = 1;
  local_14 = 0;
  if (1 < argc) {
    iVar4 = 0;
    do {
      local_1c = argv[iVar1];
      if (*local_1c != '-') {
        pMVar6 = opts;
        if (local_14 == 0) {
LAB_0808d06b:
          strcpy((char *)pMVar6,local_1c);
          iVar4 = extraout_ECX_11;
        }
        else if (local_14 == 1) {
          pMVar6 = (MugenCmdLine *)(opts->rest + 0x3c);
          goto LAB_0808d06b;
        }
        local_14 = local_14 + 1;
        goto LAB_0808d07c;
      }
      uVar8 = (int)local_1c[1] - 0x3fU < 0x34;
      switch((int)local_1c[1] - 0x3fU) {
      case 0:
      case 0x29:
        PrintHelp();
        local_1c = argv[iVar1];
      case 0x22:
        bVar9 = (byte *)(local_1c + 1) == (byte *)0x0;
        iVar4 = 8;
        pbVar2 = (byte *)(local_1c + 1);
        pbVar7 = (byte *)"ailevel";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          uVar8 = *pbVar2 < *pbVar7;
          bVar9 = *pbVar2 == *pbVar7;
          pbVar2 = pbVar2 + 1;
          pbVar7 = pbVar7 + 1;
        } while (bVar9);
        if ((!(bool)uVar8 && !bVar9) == (bool)uVar8) {
          iVar1 = iVar1 + 1;
          if (argc <= iVar1) {
            PrintHelp();
          }
          uVar3 = __strtol_internal((byte *)argv[iVar1],(undefined4 *)0x0,10,0);
          *(uint *)(opts->rest + 0x2d8) = uVar3;
          iVar4 = extraout_ECX;
          if (8 < uVar3 - 1) {
            opts->rest[0x2d8] = 4;
            opts->rest[0x2d9] = 0;
            opts->rest[0x2da] = 0;
            opts->rest[0x2db] = 0;
          }
        }
        else {
LAB_0808d020:
          PrintHelp();
          iVar4 = extraout_ECX_09;
        }
        break;
      default:
        printf("Error: Invalid option %s\n\n",argv[iVar1],iVar4,iVar4);
        PrintHelp();
        iVar4 = extraout_ECX_10;
        break;
      case 0x2d:
        uVar3 = (byte)local_1c[1] - 0x6c;
        if (((uVar3 == 0) && (uVar3 = (byte)local_1c[2] - 0x6f, uVar3 == 0)) &&
           (uVar3 = (byte)local_1c[3] - 0x67, uVar3 == 0)) {
          uVar3 = (uint)(byte)local_1c[4];
        }
        if (uVar3 == 0) {
          iVar1 = iVar1 + 1;
          if (argc <= iVar1) {
            PrintHelp();
          }
          strcpy((char *)(opts->rest + 0x184),argv[iVar1]);
          opts->rest[0x180] = 1;
          opts->rest[0x181] = 0;
          opts->rest[0x182] = 0;
          opts->rest[0x183] = 0;
          iVar4 = extraout_ECX_00;
          break;
        }
        goto LAB_0808d020;
      case 0x2f:
        iVar4 = 8;
        bVar9 = (byte *)(local_1c + 1) == (byte *)0x0;
        pbVar2 = (byte *)(local_1c + 1);
        pbVar7 = (byte *)"nomusic";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          uVar8 = *pbVar2 < *pbVar7;
          bVar9 = *pbVar2 == *pbVar7;
          pbVar2 = pbVar2 + 1;
          pbVar7 = pbVar7 + 1;
        } while (bVar9);
        bVar11 = (!(bool)uVar8 && !bVar9) < (byte)uVar8;
        if ((!(bool)uVar8 && !bVar9) == (bool)uVar8) {
          opts->rest[0x288] = 1;
          opts->rest[0x289] = 0;
          opts->rest[0x28a] = 0;
          opts->rest[0x28b] = 0;
        }
        else {
          iVar4 = 8;
          bVar9 = (byte *)(local_1c + 1) == (byte *)0x0;
          pbVar2 = (byte *)(local_1c + 1);
          pbVar7 = (byte *)"nosound";
          do {
            if (iVar4 == 0) break;
            iVar4 = iVar4 + -1;
            bVar11 = *pbVar2 < *pbVar7;
            bVar9 = *pbVar2 == *pbVar7;
            pbVar2 = pbVar2 + 1;
            pbVar7 = pbVar7 + 1;
          } while (bVar9);
          bVar10 = (!bVar11 && !bVar9) < bVar11;
          if ((!bVar11 && !bVar9) == bVar11) {
            opts->rest[0x284] = 1;
            opts->rest[0x285] = 0;
            opts->rest[0x286] = 0;
            opts->rest[0x287] = 0;
          }
          else {
            bVar9 = (byte *)(local_1c + 1) == (byte *)0x0;
            iVar4 = 6;
            pbVar2 = (byte *)(local_1c + 1);
            pbVar7 = &DAT_08277fbf;
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar10 = *pbVar2 < *pbVar7;
              bVar9 = *pbVar2 == *pbVar7;
              pbVar2 = pbVar2 + 1;
              pbVar7 = pbVar7 + 1;
            } while (bVar9);
            if ((!bVar10 && !bVar9) != bVar10) goto LAB_0808d020;
            opts->rest[0x28c] = 1;
            opts->rest[0x28d] = 0;
            opts->rest[0x28e] = 0;
            opts->rest[0x28f] = 0;
          }
        }
        break;
      case 0x31:
        if (3 < (byte)(local_1c[2] - 0x31U)) goto LAB_0808d020;
        if (argc <= iVar1 + 1) {
          PrintHelp();
          local_1c = argv[iVar1];
        }
        iVar4 = (int)local_1c[2];
        local_14 = iVar4 + -0x31;
        if (local_1c[3] != '.') {
          if (local_1c[3] != '\0') goto LAB_0808d020;
          __src = argv[iVar1 + 1];
          pbVar2 = (byte *)(local_14 * 0x40 + (int)opts);
          goto LAB_0808cf5e;
        }
        uVar3 = (byte)local_1c[4] - 0x61;
        if ((uVar3 == 0) && (uVar3 = (byte)local_1c[5] - 0x69, uVar3 == 0)) {
          uVar3 = (uint)(byte)local_1c[6];
        }
        if (uVar3 == 0) {
          iVar1 = iVar1 + 1;
          uVar3 = __strtol_internal((byte *)argv[iVar1],(undefined4 *)0x0,10,0);
          *(uint *)(opts->rest + iVar4 * 4 + 0x1d0) = uVar3;
          iVar4 = extraout_ECX_01;
        }
        else {
          bVar9 = (char *)0xfffffffb < local_1c;
          bVar11 = (byte *)(local_1c + 4) == (byte *)0x0;
          iVar5 = 6;
          pbVar2 = (byte *)(local_1c + 4);
          pbVar7 = (byte *)(int)&DAT_0827fb94;
          do {
            if (iVar5 == 0) break;
            iVar5 = iVar5 + -1;
            bVar9 = *pbVar2 < *pbVar7;
            bVar11 = *pbVar2 == *pbVar7;
            pbVar2 = pbVar2 + 1;
            pbVar7 = pbVar7 + 1;
          } while (bVar11);
          if ((!bVar9 && !bVar11) == bVar9) {
            iVar1 = iVar1 + 1;
            uVar3 = __strtol_internal((byte *)argv[iVar1],(undefined4 *)0x0,10,0);
            *(uint *)(opts->rest + iVar4 * 4 + 0x1e0) = uVar3 - 1;
            iVar4 = extraout_ECX_02;
          }
          else {
            bVar9 = (char *)0xfffffffb < local_1c;
            bVar11 = (byte *)(local_1c + 4) == (byte *)0x0;
            iVar5 = 5;
            pbVar2 = (byte *)(local_1c + 4);
            pbVar7 = (byte *)(int)&DAT_0827a2c1;
            do {
              if (iVar5 == 0) break;
              iVar5 = iVar5 + -1;
              bVar9 = *pbVar2 < *pbVar7;
              bVar11 = *pbVar2 == *pbVar7;
              pbVar2 = pbVar2 + 1;
              pbVar7 = pbVar7 + 1;
            } while (bVar11);
            if ((!bVar9 && !bVar11) == bVar9) {
              iVar1 = iVar1 + 1;
              uVar3 = __strtol_internal((byte *)argv[iVar1],(undefined4 *)0x0,10,0);
              *(uint *)(opts->rest + iVar4 * 4 + 0x1f0) = uVar3;
              iVar4 = extraout_ECX_03;
            }
            else {
              bVar9 = (char *)0xfffffffb < local_1c;
              bVar11 = (byte *)(local_1c + 4) == (byte *)0x0;
              iVar5 = 6;
              pbVar2 = (byte *)(local_1c + 4);
              pbVar7 = (byte *)(int)&DAT_0827a2b6;
              do {
                if (iVar5 == 0) break;
                iVar5 = iVar5 + -1;
                bVar9 = *pbVar2 < *pbVar7;
                bVar11 = *pbVar2 == *pbVar7;
                pbVar2 = pbVar2 + 1;
                pbVar7 = pbVar7 + 1;
              } while (bVar11);
              if ((!bVar9 && !bVar11) != bVar9) goto LAB_0808d020;
              iVar1 = iVar1 + 1;
              uVar3 = __strtol_internal((byte *)argv[iVar1],(undefined4 *)0x0,10,0);
              *(uint *)(opts->rest + iVar4 * 4 + 0x200) = uVar3;
              iVar4 = extraout_ECX_04;
            }
          }
        }
        break;
      case 0x33:
        bVar9 = false;
        if (local_1c[2] != '\0') {
          iVar4 = 7;
          bVar11 = (byte *)(local_1c + 1) == (byte *)0x0;
          pbVar2 = (byte *)(local_1c + 1);
          pbVar7 = (byte *)"rubric";
          do {
            if (iVar4 == 0) break;
            iVar4 = iVar4 + -1;
            bVar9 = *pbVar2 < *pbVar7;
            bVar11 = *pbVar2 == *pbVar7;
            pbVar2 = pbVar2 + 1;
            pbVar7 = pbVar7 + 1;
          } while (bVar11);
          bVar10 = (!bVar9 && !bVar11) < bVar9;
          if ((!bVar9 && !bVar11) != bVar9) {
            bVar9 = (byte *)(local_1c + 1) == (byte *)0x0;
            iVar4 = 7;
            pbVar2 = (byte *)(local_1c + 1);
            pbVar7 = (byte *)"rounds";
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar10 = *pbVar2 < *pbVar7;
              bVar9 = *pbVar2 == *pbVar7;
              pbVar2 = pbVar2 + 1;
              pbVar7 = pbVar7 + 1;
            } while (bVar9);
            if ((!bVar10 && !bVar9) != bVar10) goto LAB_0808d020;
            iVar1 = iVar1 + 1;
            if (argc <= iVar1) {
              PrintHelp();
            }
            uVar3 = __strtol_internal((byte *)argv[iVar1],(undefined4 *)0x0,10,0);
            *(uint *)(opts->rest + 0x290) = uVar3;
            iVar4 = extraout_ECX_05;
            if ((int)uVar3 < 2) {
              opts->rest[0x290] = 1;
              opts->rest[0x291] = 0;
              opts->rest[0x292] = 0;
              opts->rest[0x293] = 0;
            }
            break;
          }
        }
        if (argc <= iVar1 + 1) {
          PrintHelp();
        }
        pbVar2 = opts->rest + 0x13c;
        __src = argv[iVar1 + 1];
        goto LAB_0808cf5e;
      case 0x34:
        bVar9 = false;
        if (local_1c[2] != '\0') {
          iVar4 = 6;
          bVar11 = (byte *)(local_1c + 1) == (byte *)0x0;
          pbVar2 = (byte *)(local_1c + 1);
          pbVar7 = (byte *)(int)&DAT_08277a81;
          do {
            if (iVar4 == 0) break;
            iVar4 = iVar4 + -1;
            bVar9 = *pbVar2 < *pbVar7;
            bVar11 = *pbVar2 == *pbVar7;
            pbVar2 = pbVar2 + 1;
            pbVar7 = pbVar7 + 1;
          } while (bVar11);
          bVar10 = (!bVar9 && !bVar11) < bVar9;
          if ((!bVar9 && !bVar11) != bVar9) {
            iVar4 = 10;
            bVar9 = (byte *)(local_1c + 1) == (byte *)0x0;
            pbVar2 = (byte *)(local_1c + 1);
            pbVar7 = (byte *)"speedtest";
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar10 = *pbVar2 < *pbVar7;
              bVar9 = *pbVar2 == *pbVar7;
              pbVar2 = pbVar2 + 1;
              pbVar7 = pbVar7 + 1;
            } while (bVar9);
            bVar11 = (!bVar10 && !bVar9) < bVar10;
            if ((!bVar10 && !bVar9) == bVar10) {
              opts->rest[0x2e0] = 1;
              opts->rest[0x2e1] = 0;
              opts->rest[0x2e2] = 0;
              opts->rest[0x2e3] = 0;
            }
            else {
              iVar4 = 0xb;
              bVar9 = (byte *)(local_1c + 1) == (byte *)0x0;
              pbVar2 = (byte *)(local_1c + 1);
              pbVar7 = (byte *)(int)&DAT_08277ae8;
              do {
                if (iVar4 == 0) break;
                iVar4 = iVar4 + -1;
                bVar11 = *pbVar2 < *pbVar7;
                bVar9 = *pbVar2 == *pbVar7;
                pbVar2 = pbVar2 + 1;
                pbVar7 = pbVar7 + 1;
              } while (bVar9);
              bVar10 = (!bVar11 && !bVar9) < bVar11;
              if ((!bVar11 && !bVar9) == bVar11) {
                if (argc <= iVar1 + 1) {
                  PrintHelp();
                }
                __src = argv[iVar1 + 1];
                pbVar2 = opts->rest + 0x2e8;
                goto LAB_0808cf5e;
              }
              iVar4 = 0xb;
              bVar9 = (byte *)(local_1c + 1) == (byte *)0x0;
              pbVar2 = (byte *)(local_1c + 1);
              pbVar7 = (byte *)"stresstest";
              do {
                if (iVar4 == 0) break;
                iVar4 = iVar4 + -1;
                bVar10 = *pbVar2 < *pbVar7;
                bVar9 = *pbVar2 == *pbVar7;
                pbVar2 = pbVar2 + 1;
                pbVar7 = pbVar7 + 1;
              } while (bVar9);
              bVar11 = (!bVar10 && !bVar9) < bVar10;
              if ((!bVar10 && !bVar9) == bVar10) {
                iVar1 = iVar1 + 1;
                if (argc <= iVar1) {
                  PrintHelp();
                }
                uVar3 = __strtol_internal((byte *)argv[iVar1],(undefined4 *)0x0,10,0);
                *(uint *)(opts->rest + 0x2e4) = uVar3;
                iVar4 = extraout_ECX_07;
              }
              else {
                bVar9 = (byte *)(local_1c + 1) == (byte *)0x0;
                iVar4 = 6;
                pbVar2 = (byte *)(local_1c + 1);
                pbVar7 = (byte *)(int)&DAT_0827d44d;
                do {
                  if (iVar4 == 0) break;
                  iVar4 = iVar4 + -1;
                  bVar11 = *pbVar2 < *pbVar7;
                  bVar9 = *pbVar2 == *pbVar7;
                  pbVar2 = pbVar2 + 1;
                  pbVar7 = pbVar7 + 1;
                } while (bVar9);
                if ((!bVar11 && !bVar9) != bVar11) goto LAB_0808d020;
                iVar1 = iVar1 + 1;
                if (argc <= iVar1) {
                  PrintHelp();
                }
                uVar3 = __strtol_internal((byte *)argv[iVar1],(undefined4 *)0x0,10,0);
                *(uint *)(opts->rest + 0x2dc) = uVar3;
                iVar4 = extraout_ECX_08;
                if (0x12 < uVar3 + 9) {
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
        if (argc <= iVar1 + 1) {
          PrintHelp();
        }
        pbVar2 = opts->rest + 0xfc;
        __src = argv[iVar1 + 1];
LAB_0808cf5e:
        iVar1 = iVar1 + 1;
        strcpy((char *)pbVar2,__src);
        iVar4 = extraout_ECX_06;
      }
LAB_0808d07c:
      iVar1 = iVar1 + 1;
    } while (iVar1 < argc);
  }
  return;
}

/* PrintHelp @ 0x0808d090, 83 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x4010-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 PrintHelp(void)

{

  unsigned char ghidra_frame[0x4010] __attribute__((aligned(16)));
#define local_400c (*(char (*)[16392])(ghidra_frame + 0x4))
  
  sprintf(local_400c,"M.U.G.E.N test ver %i.%02i.%02i \t(c)%i Elecbyte\n\n",MUGENDATE_Y,MUGENDATE_M,
          MUGENDATE_D,MUGENDATE_Y);
  strcat(local_400c,
         "Options (case sensitive):\n -h -? \tHelp\n -log <logfile> \tRecords match data to <logfile>\n -r <sysfile> \tLoads motif <sysfile>. eg. -r motifdir or -r motifdir/system.def\nQuick VS Options:\n -p<?> <playername> \tLoads player ?, eg. -p3 kfm\n -p<?>.ai 1 \tEnables AI for player ?, eg. -p1.ai 1\n -p<?>.color <col> \tSet player ?\'s color to <col>\n -p<?>.life <life> \tSets player ?\'s life to <life>\n -p<?>.power <power> \tSets player ?\'s power to <power>\n -rounds <num> \tPlays for <num> rounds, and then quits\n -s <stagename> \tLoads stage <stagename>\nDebug Options:\n -nojoy   \tDisables joysticks\n -nomusic \tDisables music\n -nosound \tDisables all sound effects and music\n\n"
        );
  printf(local_400c);
                    /* WARNING: Subroutine does not return */
  exit(0);
}
#undef local_400c

