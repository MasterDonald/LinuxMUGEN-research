/*
 * menus.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0809fd70-0x080a5d6b, 9 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"

extern int ShowInfoNow_0 __asm__("D_08287a94"); /* file-static 0x08287a94 */

/* IntroScreen @ 0x0809fd70, 28 bytes */
void IntroScreen(void)

{
  PlayCutscene((char *)(g + 0x1f51),"scene");
  return;
}

/* PlayCutscene @ 0x0809fd90, 1054 bytes
 * FIXUP: 3 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 8 stack locals placed at their original offsets in a 0x2040-byte frame (a local's address escapes, see apply_frame_emulation) */
void PlayCutscene(char *param_1,char *param_2)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  int iVar6;
  int *piVar7;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  int *piVar8;
  uint uVar9;
  unsigned char ghidra_frame[0x2040] __attribute__((aligned(16)));
#define local_2040 (*(uint *)(ghidra_frame + 0x0))
#define local_2034 (*(uint (*)[2])(ghidra_frame + 0xc))
#define local_202c (*(uint *)(ghidra_frame + 0x14))
#define local_2028 (*(undefined4 *)(ghidra_frame + 0x18))
#define local_2024 (*(int **)(ghidra_frame + 0x1c))
#define local_2020 (*(int **)(ghidra_frame + 0x20))
#define local_201c (*(char (*)[4096])(ghidra_frame + 0x24))
#define local_101c (*(char (*)[4108])(ghidra_frame + 0x1024))
  
  bVar1 = false;
  bVar4 = false;
  bVar3 = false;
  bVar2 = false;
  if ((param_1 != (char *)0x0) && (*param_1 != '\0')) {
    iVar6 = FindFileDir(param_1,local_101c,local_201c);
    if (iVar6 != 0) {
      piVar7 = SceneReadFile(local_101c,param_2,0,0);
      if (piVar7 == (int *)0x0) {
        strcat((char *)(g + 0x81d2),"\nError loading storyboard: ");
        strcat((char *)(g + 0x81d2),param_1);
      }
      else {
        SceneRegisterBGMFn(piVar7,BGMPlayForScene,BGMStopForScene);
        local_2024 = g + 0x733b;
        local_2020 = g + 0x7348;
        V_SetBuf((int *)g[0x4136],0);
        W_Cls(0);
        TimerSetSyncFPS(0x3c);
        KBBufferClear();
        PadPoll();
        PadBufClear();
        UInpRefreshFlags();
        UInpBufClear();
        do {
          piVar8 = g;
          if (g[0x81cd] == 0) {
            keypauseflag = 0;
            g[0x7309] = 0;
          }
          if ((piVar8[0x7309] == 0) || (bVar1)) {
            if ((piVar8[0x7309] == 0) && (bVar1)) {
              bVar1 = false;
              BGMResume(piVar8 + 0x6efa);
              piVar8 = g;
            }
          }
          else {
            bVar1 = true;
            BGMPause(piVar8 + 0x6efa);
            piVar8 = g;
          }
          iVar6 = 0;
          BGMPollIgnoreDefocus(piVar8 + 0x6efa);
          local_202c = 0;
          local_2028 = 0;
          PadPoll();
          KBPoll();
          bVar5 = KBkbhit();
          if (GHIDRA_ZEXT8(bVar5) != 0) {
            local_202c = KBgetchraw();
          }
          bVar5 = PadHit();
          if (GHIDRA_ZEXT8(bVar5) != 0) {
            local_2028 = PadGet();
          }
          GlobalInputUpdate();
          bVar5 = UInpHit();
          if (GHIDRA_ZEXT8(bVar5) != 0) {
            iVar6 = UInpGet();
          }
          KBIMenuGetKey(local_2034,iVar6,(int)&local_2024,2);
          if ((local_2034[0] & 0xff0) != 0) {
            bVar4 = true;
          }
          if (local_202c == 1) {
            bVar4 = true;
          }
          PRSprArrayClear((int *)g[0x413d]);
          if (g[0x756e] != 0) {
            if ((bVar2) || (g[0x74e7] != 0)) {
              if ((!bVar2) || (g[0x74e7] == 0)) goto LAB_080a0075;
              bVar2 = false;
              uVar9 = local_2040;
            }
            else {
              bVar2 = true;
              local_2040 = BGMGetVolume(g + 0x6efa);
              uVar9 = 0;
            }
            BGMSetVolume(g + 0x6efa,uVar9);
          }
LAB_080a0075:
          if ((g[0x7309] == 0) && (iVar6 = SceneUpdate(piVar7), iVar6 != 0)) {
            bVar4 = true;
          }
          iVar6 = (int)(char)keypauseflag;
          g[0x7309] = iVar6;
          if (bVar3) {
            bVar3 = false;
            keypauseflag = 1;
          }
          if (((((iVar6 != 0) && (local_202c != 0)) && (!bVar3)) &&
              (((local_202c & 0x100) == 0 && (local_202c != 0x58)))) && (local_202c == 0x46)) {
            keypauseflag = 0;
            bVar3 = true;
          }
          if (local_202c == 0x58) {
            ScreenSnap();
          }
          if (g[0x7307] == 0) {
            MasterPalReset();
            SceneUpdatePal(piVar7);
            MasterPalProcessChanges();
            SceneDraw(piVar7);
          }
          if (g[0x82d2] == 0) {
            TimerWaitSync();
          }
          if ((g[0x7307] == 0) && (g[0x4143] != 0)) {
            VRetrace();
          }
          DrawToScreen();
          if (g[0x7307] == 0) {
            MasterPalFinishedDraw();
          }
          FrameSkipUpdate();
        } while (!bVar4);
        FrameSkipReset();
        SceneFree(piVar7);
      }
    }
  }
  return;
}
#undef local_2040
#undef local_2034
#undef local_202c
#undef local_2028
#undef local_2024
#undef local_2020
#undef local_201c
#undef local_101c

/* ModeSelect @ 0x080a01b0, 5751 bytes
 * FIXUP: removed 2 x87 control-word save statements
 * FIXUP: 3 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: 19 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 38 stack locals placed at their original offsets in a 0x13a0-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void ModeSelect(void)

{
  int *piVar1;
  float10 fVar2;
  bool bVar3;
  bool bVar4;
  int *piVar5;
  bool bVar6;
  int iVar7;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  uint uVar8;
  int iVar9;
  uint *puVar10;
  uint *puVar11;
  uint uVar12;
  uint uVar13;
  int *piVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  uint uVar21;
  int *piVar22;
  int iVar23;
  int iVar24;
  undefined2 in_FPUControlWord;
  char *pcVar25;
  unsigned char ghidra_frame[0x13a0] __attribute__((aligned(16)));
#define piStack_1398 (*(int **)(ghidra_frame + 0x8))
#define local_1350 (*(int *)(ghidra_frame + 0x50))
#define local_134c (*(int *)(ghidra_frame + 0x54))
#define local_1348 (*(int *)(ghidra_frame + 0x58))
#define local_1344 (*(int *)(ghidra_frame + 0x5c))
#define local_1340 (*(int *)(ghidra_frame + 0x60))
#define local_133c (*(int *)(ghidra_frame + 0x64))
#define local_1334 (*(int *)(ghidra_frame + 0x6c))
#define local_1330 (*(int *)(ghidra_frame + 0x70))
#define local_132c (*(int *)(ghidra_frame + 0x74))
#define local_1328 (*(uint *)(ghidra_frame + 0x78))
#define local_1324 (*(int *)(ghidra_frame + 0x7c))
#define local_131c (*(int **)(ghidra_frame + 0x84))
#define local_1318 (*(int *)(ghidra_frame + 0x88))
#define local_1314 (*(int *)(ghidra_frame + 0x8c))
#define local_1310 (*(int *)(ghidra_frame + 0x90))
#define local_130c (*(int **)(ghidra_frame + 0x94))
#define local_1308 (*(int **)(ghidra_frame + 0x98))
#define local_1304 (*(int *)(ghidra_frame + 0x9c))
#define local_1300 (*(undefined2 *)(ghidra_frame + 0xa0))
#define uStack_12fe (*(undefined2 *)(ghidra_frame + 0xa2))
#define local_12fc (*(int (*)[2])(ghidra_frame + 0xa4))
#define local_12f4 (*(uint **)(ghidra_frame + 0xac))
#define local_12f0 (*(uint *)(ghidra_frame + 0xb0))
#define local_12ec (*(uint *)(ghidra_frame + 0xb4))
#define local_12e8 (*(uint *)(ghidra_frame + 0xb8))
#define local_12e4 (*(uint *)(ghidra_frame + 0xbc))
#define local_12e0 (*(uint *)(ghidra_frame + 0xc0))
#define local_12dc (*(uint *)(ghidra_frame + 0xc4))
#define local_12d8 (*(int *)(ghidra_frame + 0xc8))
#define local_12d4 (*(int *)(ghidra_frame + 0xcc))
#define local_12d0 (*(float *)(ghidra_frame + 0xd0))
#define local_12cc (*(uint *)(ghidra_frame + 0xd4))
#define local_12c8 (*(uint *)(ghidra_frame + 0xd8))
#define local_12bc (*(uint (*)[1024])(ghidra_frame + 0xe4))
#define local_2bc (*(char (*)[192])(ghidra_frame + 0x10e4))
#define local_1fc (*(char (*)[432])(ghidra_frame + 0x11a4))
#define local_4c (*(int (*)[15])(ghidra_frame + 0x1354))
  
  piVar5 = g;
  piVar1 = g + 0x1005;
  local_1328 = g[0x33b5];
  local_134c = -1;
  local_1330 = 0;
  local_1334 = 0;
  bVar3 = false;
  local_133c = 1;
  local_1340 = 0;
  local_1344 = 0;
  local_1348 = 0;
  local_1350 = -1;
  bVar4 = false;
  memcpy(local_1fc,
         "[big]M.U.G.E.N Information\n[small][col=192,192,192]\n. Thanks for using MUGEN! MUGEN betas are available from\n[big]  www.elecbyte.com.\n\n[small]. Please refer to readme.txt before using MUGEN.\n\n. Answers to commonly-asked questions can be found in\n  mugenfaq.txt.\n\n[big][col=255,255,255]\nSummary of Terms of Use\n[small][col=192,192,192]\n. This version of MUGEN is to be used AT YOUR OWN RISK.\n\n. You may use MUGEN beta "
         ,0x1a2);
  memcpy(local_2bc,
         "\n  after which you MUST obtain a new license.\n\n. The full description of the license is in readme.txt. Please\n  read it carefully.\n[small][col=192,192,128]\n\n\n\nPress F1 to continue."
         ,0xb5);
  local_130c = g + 0x733b;
  local_1308 = g + 0x7348;
  V_SetBuf((int *)g[0x4136],0);
  W_Cls(0);
  TimerSetSyncFPS(0x3c);
  KBBufferClear();
  PadPoll();
  PadBufClear();
  UInpRefreshFlags();
  UInpBufClear();
  if (ShowInfoNow_0 == -1) {
    ShowInfoNow_0 = 0;
    if ((g[0x7578] != 0) || (g[0x801] == 0)) {
      ShowInfoNow_0 = 1;
    }
    if (g[0x74e6] != 0) {
      ShowInfoNow_0 = 1;
    }
  }
  local_1328 = local_1328 & (g[0x74e8] != 0) - 1;
  g[0x74e8] = 0;
  CharselResetCursor();
  CharselResetMenuPos();
  GameSetVol(g[0x6ef5],g[0x6ef7]);
  piVar22 = g;
  iVar18 = 10;
  iVar9 = 0;
  iVar7 = 0;
  piVar14 = piVar5 + 0x1017;
  do {
    *(int **)((int)local_4c + iVar7) = piVar14;
    if ((char)piVar5[iVar7 * 2 + 0x1017] == '\0') {
      *(undefined4 *)((int)local_4c + iVar7) = 0;
    }
    else {
      iVar9 = iVar9 + 1;
    }
    piVar14 = piVar14 + 8;
    iVar7 = iVar7 + 4;
    iVar18 = iVar18 + -1;
  } while (-1 < iVar18);
  if (iVar9 == 0) {
    if ((g[0x14b5] < 1) || (keyflag[1] != 0)) {
      local_1328 = 10;
    }
    else {
      g[0x74e8] = 1;
      piVar22[0x74f1] = 0;
      local_1328 = 1;
      local_133c = 1;
    }
  }
  else {
    iVar7 = local_4c[local_1328];
    while (iVar7 == 0) {
      local_1328 = local_1328 + 1 & (10 < (int)(local_1328 + 1)) - 1;
      iVar7 = local_4c[local_1328];
    }
    BGArrayReset(g[0x62ce]);
    piVar22 = local_12fc;
    for (iVar7 = 0xe; iVar7 != 0; iVar7 = iVar7 + -1) {
      *piVar22 = 0;
      piVar22 = piVar22 + 1;
    }
    strcpy((char *)local_12bc,local_1fc);
    puVar10 = local_12bc;
    do {
      puVar11 = puVar10;
      puVar10 = puVar11 + 1;
      uVar15 = *puVar11 + 0xfefefeff & (*puVar11 ^ 0xffffffff);
      uVar16 = uVar15 & 0x80808080;
    } while (uVar16 == 0);
    if ((uVar15 & 0x8080) == 0) {
      uVar16 = uVar16 >> 0x10;
      puVar10 = (uint *)((int)puVar11 + 6);
    }
    sprintf((char *)((int)puVar10 + (-3 - (uint)CARRY1((byte)uVar16,(byte)uVar16))),"%i.%02i.%02i ",
            MUGENDATE_Y,MUGENDATE_M,MUGENDATE_D);
    strcat((char *)local_12bc,"until ");
    puVar10 = local_12bc;
    do {
      puVar11 = puVar10;
      puVar10 = puVar11 + 1;
      uVar15 = *puVar11 + 0xfefefeff & (*puVar11 ^ 0xffffffff);
      uVar16 = uVar15 & 0x80808080;
    } while (uVar16 == 0);
    if ((uVar15 & 0x8080) == 0) {
      uVar16 = uVar16 >> 0x10;
      puVar10 = (uint *)((int)puVar11 + 6);
    }
    datenotostr(MUGENEXPDATE_Y,MUGENEXPDATE_M,(undefined **)MUGENEXPDATE_D,
                (char *)((int)puVar10 + (-3 - (uint)CARRY1((byte)uVar16,(byte)uVar16))));
    strcat((char *)local_12bc,local_2bc);
    local_12f0 = (V_Width + -0x118) / 2;
    local_12ec = 0xffffff33;
    local_12c8 = 0xffffff33;
    local_12e4 = 0xffffff33;
    local_12dc = (V_Height + -200) / 2;
    local_12fc[0] = 0x118;
    local_12fc[1] = 200;
    local_12f4 = local_12bc;
    local_12e8 = local_12f0;
    local_12e0 = local_12f0;
    iVar7 = BGMLoadAndStart(g + 0x6efa,(byte *)(g + 0x62d1),g[0x66d1],0);
    if (iVar7 == 0) {
      ErrorExit();
    }
    FrameSkipReset();
    local_1314 = 0;
    do {
      iVar7 = 0;
      BGMPoll(g + 0x6efa);
      local_1314 = 0;
      local_1310 = 0;
      PadPoll();
      KBPoll();
      bVar6 = KBkbhit();
      if (GHIDRA_ZEXT8(bVar6) != 0) {
        local_1314 = KBgetchraw();
      }
      bVar6 = PadHit();
      if (GHIDRA_ZEXT8(bVar6) != 0) {
        local_1310 = PadGet();
      }
      GlobalInputUpdate();
      bVar6 = UInpHit();
      if (GHIDRA_ZEXT8(bVar6) != 0) {
        iVar7 = UInpGet();
      }
      KBIMenuGetKey((uint *)&local_131c,iVar7,(int)&local_130c,2);
      iVar7 = local_1318;
      piVar22 = local_131c;
      PRSprArrayClear((int *)g[0x413d]);
      if (((g[0x738d] == 0x16) || (g[0x738e] == 0x16)) && (local_1310 == 0xb)) {
        local_1314 = 1;
        local_1310 = 0;
      }
      if ((local_12cc == 0) && (local_1348 == 1)) {
        if (((uint)piVar22 & 1) != 0) {
          do {
            local_1328 = local_1328 - 1;
            if ((int)local_1328 < 0) {
              local_1328 = 10;
            }
          } while (local_4c[local_1328] == 0);
          GameSndPlay((int *)g[0x5ec1],piVar5[0x1007],piVar5[0x1008],0);
        }
        if (((uint)piVar22 & 4) != 0) {
          do {
            local_1328 = local_1328 + 1 & (10 < (int)(local_1328 + 1)) - 1;
          } while (local_4c[local_1328] == 0);
          GameSndPlay((int *)g[0x5ec1],piVar5[0x1007],piVar5[0x1008],0);
        }
        if (((uint)piVar22 & 0xff0) != 0) {
          local_133c = iVar7 + 1;
          bVar3 = true;
        }
      }
      piVar14 = g;
      if ((piVar22 != (int *)0x0) || (local_12d8 != 0)) {
        local_1340 = 0;
      }
      local_1340 = local_1340 + 1;
      if (((g[0x74ea] < local_1340) && (g[0x74ea] != -1)) && (0 < g[0x14b5])) {
        g[0x74e8] = 1;
        piVar14[0x74f1] = 0;
        local_1328 = 1;
        bVar3 = true;
        local_133c = 1;
      }
      if ((local_1314 == 0x3b) || (piVar22 = (int *)ShowInfoNow_0, ShowInfoNow_0 != 0)) {
        local_12cc = (uint)(local_12cc == 0);
        local_12d8 = 1;
        uVar15 = local_12dc;
        if ((local_12cc == 1) || (uVar15 = local_12e4, local_12cc == 0)) {
          local_12c8 = uVar15;
        }
        ShowInfoNow_0 = 0;
      }
      if ((bVar3) && (local_1350 == -1)) {
        if (g[0x74e8] == 0) {
          piVar22 = (int *)g[0x5ec1];
          GameSndPlay(piVar22,piVar5[0x1009],piVar5[0x100a],0);
        }
        if (local_1328 == 9) {
          OptionsScreen();
          W_Cls(0);
          BGArrayReset(g[0x62ce]);
          local_1348 = 0;
          local_134c = local_1350;
          local_1344 = 0;
          bVar3 = false;
          bVar4 = false;
        }
      }
      if (local_1314 == 1) {
        local_1328 = 10;
        bVar3 = true;
      }
      if (local_1314 == 0x58) {
        ScreenSnap();
      }
      iVar7 = 0;
      local_1324 = 0;
      if (local_1328 < 0x80000000) {
        do {
          if (local_4c[iVar7] != 0) {
            local_1324 = local_1324 + 1;
          }
          iVar7 = iVar7 + 1;
        } while (iVar7 <= (int)local_1328);
      }
      if (keyflag[0x10] != 0) {
        ErrorExitM("%i",local_1324,piVar22,piVar22);
      }
      iVar7 = piVar5[0x1016];
      iVar9 = 1;
      do {
        iVar18 = (local_1324 + -1) * iVar7 - local_1334;
        if ((piVar5[0x1071] + -1) * iVar7 < iVar18) {
          local_1334 = local_1334 + iVar7;
        }
        if (iVar18 < 0) {
          local_1334 = local_1334 - iVar7;
        }
        iVar9 = iVar9 + -1;
      } while (-1 < iVar9);
      if (local_1330 < local_1334) {
        iVar7 = (local_1334 - local_1330) / 5 + 1;
LAB_080a0b06:
        local_1330 = iVar7 + local_1330;
      }
      else if (local_1334 < local_1330) {
        iVar7 = (local_1334 - local_1330) / 5 + -1;
        goto LAB_080a0b06;
      }
      if ((ABS((double)(local_1334 - local_1330)) <= 2.0) || (local_1344 == 0)) {
        local_1330 = local_1334;
      }
      if (local_12d8 != 0) {
        if (local_12ec != local_12c8) {
          local_12d4 = (uint)((int)local_12ec < (int)local_12c8) * 2 + -1;
          local_12ec = (int)(local_12c8 - local_12ec) / 0xc + local_12d4 * 5 + local_12ec;
          if (((int)(local_12d4 * (local_12c8 - local_12ec)) < 1) &&
             (local_12ec = local_12c8, local_12cc == 0)) {
            local_12d8 = 0;
          }
        }
        local_12d0 = (float10)(int)(local_12ec - local_12e4) / (float10)(int)(local_12dc - local_12e4);
      }
      BGArrayMove((int *)g[0x62ce],0.0,0.0);
      BGArrayUpdate(g[0x62ce]);
      iVar7 = *piVar1;
      if ((0 < iVar7) && (local_1348 == 0)) {
        iVar7 = (local_1344 << 8) / iVar7;
        MasterPalMul(iVar7,iVar7,iVar7);
        iVar7 = *piVar1;
      }
      if (local_1344 == iVar7) {
        local_1348 = 1;
      }
      if ((0 < piVar5[0x1006]) && (local_1348 == 2)) {
        uVar15 = 0x100 - ((local_1344 - local_134c) * 0x100) / piVar5[0x1006];
        uVar15 = uVar15 & 0xffffffffU - ((int)uVar15 >> 0x1f);
        MasterPalMul(uVar15,uVar15,uVar15);
      }
      if (g[0x7307] == 0) {
        MasterPalProcessChanges();
        BGArrayDrawLayer(g[0x62ce],0);
        uVar15 = 0;
        W_Define(0,piVar5[0x100e] - piVar5[0x106f],V_Width - 1,
                 piVar5[0x1070] + piVar5[0x100e] + (piVar5[0x1071] + -1) * piVar5[0x1016]);
        local_1324 = 0;
        piStack_1398 = local_4c;
        do {
          if (*piStack_1398 != 0) {
            iVar7 = piVar5[0x100d];
            if ((uVar15 & 1) == 0) {
              iVar9 = -0x5b - iVar7;
            }
            else {
              iVar9 = 0x199 - iVar7;
            }
            local_132c = (int)GHIDRA_FIST32((float10)iVar7 + (float10)iVar9 * local_12d0);
            iVar7 = (local_1324 * piVar5[0x1016] + piVar5[0x100e]) - local_1330;
            if ((uVar15 == local_1328) && (g[0x74e8] == 0)) {
              iVar9 = local_1344 * 2;
              if (iVar9 % 0x40 < 0x20) {
                iVar9 = iVar9 % 0x20 + 0x10;
              }
              else {
                iVar9 = 0x2f - iVar9 % 0x20;
              }
              if ((piVar5[0x1072] != 0) && (local_1348 == 1)) {
                W_BoxFillTransAdd16(local_132c + piVar5[0x1073],iVar7 + piVar5[0x1074],
                                    local_132c + piVar5[0x1075],iVar7 + piVar5[0x1076],
                                    (iVar9 - (iVar9 >> 0x1f) >> 4) << ((byte)_rgb_r_shift_16 & 0x1f)
                                    | (iVar9 >> 2) << ((byte)_rgb_g_shift_16 & 0x1f) |
                                    (iVar9 >> 3) << ((byte)_rgb_b_shift_16 & 0x1f));
              }
              if (piVar5[0x1012] == -1) {
                V_FontDrawCenter((char *)*piStack_1398,(int *)g[0x413b],local_132c,iVar7,
                                 0x1f << ((byte)_rgb_r_shift_16 & 0x1f) |
                                 0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
                                 0x1f << ((byte)_rgb_b_shift_16 & 0x1f));
              }
              else {
                iVar9 = piVar5[0x1014];
                iVar18 = piVar5[0x1013];
                piVar22 = (int *)g[piVar5[0x1012] + 0x62c3];
                pcVar25 = (char *)*piStack_1398;
LAB_080a1019:
                V_FontDrawAlignBank(pcVar25,piVar22,local_132c,iVar7,iVar18,iVar9);
              }
            }
            else {
              if (piVar5[0x100f] != -1) {
                iVar9 = piVar5[0x1011];
                iVar18 = piVar5[0x1010];
                piVar22 = (int *)g[piVar5[0x100f] + 0x62c3];
                pcVar25 = (char *)*piStack_1398;
                goto LAB_080a1019;
              }
              V_FontDrawCenter((char *)*piStack_1398,(int *)g[0x413b],local_132c,iVar7,
                               0x10 << ((byte)_rgb_r_shift_16 & 0x1f) |
                               0x20 << ((byte)_rgb_g_shift_16 & 0x1f) |
                               0x10 << ((byte)_rgb_b_shift_16 & 0x1f));
            }
            local_1324 = local_1324 + 1;
          }
          uVar15 = uVar15 + 1;
          piStack_1398 = piStack_1398 + 1;
        } while ((int)uVar15 < 0xb);
        W_Define(0,0,V_Width - 1,V_Height - 1);
        uVar16 = local_12ec;
        uVar15 = local_12f0;
        if (local_12d8 != 0) {
          iVar23 = local_12f0 + local_12fc[0];
          iVar20 = local_12ec + local_12fc[1];
          uVar12 = 10 << ((byte)_rgb_r_shift_16 & 0x1f) | 0x1d << ((byte)_rgb_g_shift_16 & 0x1f) |
                   0x15 << ((byte)_rgb_b_shift_16 & 0x1f);
          uVar21 = 8 << ((byte)_rgb_r_shift_16 & 0x1f) | 0x18 << ((byte)_rgb_g_shift_16 & 0x1f) |
                   0x12 << ((byte)_rgb_b_shift_16 & 0x1f);
          W_Define(local_12f0,local_12ec,iVar23 - 1U,iVar20 - 1U);
          iVar9 = iVar20 + -3;
          uVar8 = iVar23 - 3;
          iVar7 = uVar16 + 2;
          uVar13 = uVar15 + 2;
          W_BoxFillTransAdd16_B50(uVar13,iVar7,uVar8,iVar9,8 << ((byte)_rgb_b_shift_16 & 0x1f));
          iVar18 = iVar20 + -2;
          iVar19 = iVar23 + -2;
          iVar17 = uVar16 + 1;
          iVar24 = uVar15 + 1;
          W_Box(iVar24,iVar17,iVar19,iVar18,uVar12);
          W_Box(uVar13,iVar7,uVar8,iVar9,uVar21);
          W_Line((float10)iVar24,(float10)(int)uVar16,(float10)iVar19,(float10)(int)uVar16,uVar21);
          fVar2 = (float10)(int)(iVar20 - 1U);
          W_Line((float10)iVar24,fVar2,(float10)iVar19,fVar2,uVar21);
          W_Line((float10)(int)uVar15,(float10)iVar17,(float10)(int)uVar15,(float10)iVar18,uVar21);
          fVar2 = (float10)(int)(iVar23 - 1U);
          W_Line(fVar2,(float10)iVar17,fVar2,(float10)iVar18,uVar21);
          W_PutPixel(iVar24,iVar17,uVar21);
          W_PutPixel(iVar19,iVar17,uVar21);
          W_PutPixel(iVar24,iVar18,uVar21);
          W_PutPixel(iVar19,iVar18,uVar21);
          W_PutPixel(uVar13,iVar7,uVar12);
          W_PutPixel(uVar8,iVar7,uVar12);
          W_PutPixel(uVar13,iVar9,uVar12);
          W_PutPixel(uVar8,iVar9,uVar12);
          W_PutPixel(uVar15 + 3,uVar16 + 3,uVar21);
          W_PutPixel(iVar23 + -4,uVar16 + 3,uVar21);
          W_PutPixel(uVar15 + 3,iVar20 + -4,uVar21);
          W_PutPixel(iVar23 + -4,iVar20 + -4,uVar21);
          InfoTextDraw((char *)local_12f4,local_12f0 + 10,local_12ec + 8);
          W_Define(0,0,V_Width - 1,V_Height - 1);
        }
        iVar7 = V_Height + -2;
        if ((local_1348 == 0) && (iVar9 = *piVar1, 0 < iVar9)) {
          iVar18 = iVar9 - local_1344;
LAB_080a13ee:
          iVar7 = iVar7 + (iVar18 * 10) / iVar9;
        }
        else if ((local_1348 == 2) && (local_134c < local_1350)) {
          iVar18 = local_1344 - local_134c;
          iVar9 = local_1350 - local_134c;
          goto LAB_080a13ee;
        }
        W_BoxFillTransAdd16_B50
                  (0,iVar7 + -5,V_Width - 1,iVar7 + 1,8 << ((byte)_rgb_b_shift_16 & 0x1f));
        if ((bVar3) && (g[0x74e8] != 0)) {
          V_FontDrawRight("Loading demo",(int *)g[0x413a],V_Width + -4,iVar7,
                          0x18 << ((byte)_rgb_r_shift_16 & 0x1f) |
                          0x30 << ((byte)_rgb_g_shift_16 & 0x1f) |
                          0x18 << ((byte)_rgb_b_shift_16 & 0x1f));
        }
        else {
          V_FontWrite((int *)g[0x413a],2,iVar7,
                      0x18 << ((byte)_rgb_r_shift_16 & 0x1f) |
                      0x30 << ((byte)_rgb_g_shift_16 & 0x1f) |
                      0x18 << ((byte)_rgb_b_shift_16 & 0x1f),"Beta %i.%02i.%02i",MUGENDATE_Y,
                      MUGENDATE_M,MUGENDATE_D);
          V_FontDrawRight("(c) Elecbyte 2002",(int *)g[0x413a],V_Width + -3,iVar7,
                          0x18 << ((byte)_rgb_r_shift_16 & 0x1f) |
                          0x30 << ((byte)_rgb_g_shift_16 & 0x1f) |
                          0x18 << ((byte)_rgb_b_shift_16 & 0x1f));
          local_1304 = (int)GHIDRA_FIST32(local_12d0 * 18.0 + (float10)iVar7);
          V_FontDrawCenter("Press F1 for info",(int *)g[0x413a],V_Width / 2 + -1,local_1304,
                           0x18 << ((byte)_rgb_r_shift_16 & 0x1f) |
                           0x30 << ((byte)_rgb_g_shift_16 & 0x1f) |
                           0x18 << ((byte)_rgb_b_shift_16 & 0x1f));
          local_1304 = (int)GHIDRA_FIST32((float)(iVar7 + 0x12) - local_12d0 * 18.0);
          V_FontDrawCenter("Press F1 to continue",(int *)g[0x413a],V_Width / 2 + -1,local_1304,
                           0x18 << ((byte)_rgb_r_shift_16 & 0x1f) |
                           0x30 << ((byte)_rgb_g_shift_16 & 0x1f) |
                           0x18 << ((byte)_rgb_b_shift_16 & 0x1f));
        }
        if (g[0x74e6] != 0) {
          W_BoxFillTransAdd16_B50(0,0,V_Width - 1,6,0x18 << ((byte)_rgb_r_shift_16 & 0x1f));
          V_FontDrawCenter("The beta period for this version of M.U.G.E.N has ended",
                           (int *)g[0x413a],V_Width / 2,5,
                           0x18 << ((byte)_rgb_r_shift_16 & 0x1f) |
                           0x30 << ((byte)_rgb_g_shift_16 & 0x1f) |
                           0x18 << ((byte)_rgb_b_shift_16 & 0x1f));
        }
      }
      if (g[0x82d2] == 0) {
        TimerWaitSync();
      }
      if ((g[0x7307] == 0) && (g[0x4143] != 0)) {
        VRetrace();
      }
      DrawToScreen();
      if (g[0x7307] == 0) {
        MasterPalFinishedDraw();
      }
      FrameSkipUpdate();
      if (((bVar3) && (local_1350 == -1)) && (local_1348 == 1)) {
        local_134c = local_1344;
        local_1348 = 2;
        local_1350 = local_1344 + piVar5[0x1006];
      }
      local_1344 = local_1344 + 1;
      if (bVar4) break;
      if ((local_1350 != -1) && (local_1350 < local_1344)) {
        bVar4 = true;
      }
    } while (local_1314 != 1);
  }
  FrameSkipReset();
  PalGrpClear();
  piVar1 = g;
  g[0x33b5] = local_1328;
  piVar1[0x33b6] = local_133c + -1;
  return;
}
#undef piStack_1398
#undef local_1350
#undef local_134c
#undef local_1348
#undef local_1344
#undef local_1340
#undef local_133c
#undef local_1334
#undef local_1330
#undef local_132c
#undef local_1328
#undef local_1324
#undef local_131c
#undef local_1318
#undef local_1314
#undef local_1310
#undef local_130c
#undef local_1308
#undef local_1304
#undef local_1300
#undef uStack_12fe
#undef local_12fc
#undef local_12f4
#undef local_12f0
#undef local_12ec
#undef local_12e8
#undef local_12e4
#undef local_12e0
#undef local_12dc
#undef local_12d8
#undef local_12d4
#undef local_12d0
#undef local_12cc
#undef local_12c8
#undef local_12bc
#undef local_2bc
#undef local_1fc
#undef local_4c

/* OptionsScreen @ 0x080a1830, 8811 bytes
 * FIXUP: rewrote 2 Ghidra partial-variable accesses (x._O_S_)
 * FIXUP: removed pointer casts from 7 case labels; switch operand cast to int
 * FIXUP: 3 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 50 stack locals placed at their original offsets in a 0x200-byte frame (a local's address escapes, see apply_frame_emulation) */
void OptionsScreen(void)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  int *piVar6;
  uint3 uVar7;
  bool bVar8;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  int *piVar9;
  int *piVar10;
  byte bVar11;
  byte bVar12;
  byte bVar13;
  int *extraout_ECX;
  uint *puVar16;
  uint *puVar17;
  uint uVar18;
  uint uVar19;
  int *extraout_EDX;
  int *extraout_EDX_00;
  int *piVar20;
  int iVar21;
  int *piVar22;
  undefined4 *puVar23;
  undefined4 *puVar24;
  uint uVar25;
  bool bVar26;
  bool bVar27;
  bool bVar28;
  char *pcVar29;
  uint uVar30;
  uint uVar31;
  int iVar32;
  size_t __n;
  byte bVar14;
  byte bVar15;
  unsigned char ghidra_frame[0x200] __attribute__((aligned(16)));
#define local_1f4 (*(byte *)(ghidra_frame + 0xc))
#define local_1e8 (*(int *)(ghidra_frame + 0x18))
#define local_1e4 (*(int *)(ghidra_frame + 0x1c))
#define local_1e0 (*(int *)(ghidra_frame + 0x20))
#define iStack_1dc (*(int *)(ghidra_frame + 0x24))
#define local_1b0 (*(int *)(ghidra_frame + 0x50))
#define local_1ac (*(int *)(ghidra_frame + 0x54))
#define local_1a8 (*(uint *)(ghidra_frame + 0x58))
#define local_194 (*(uint *)(ghidra_frame + 0x6c))
#define local_188 (*(int *)(ghidra_frame + 0x78))
#define local_184 (*(int *)(ghidra_frame + 0x7c))
#define local_17c (*(uint *)(ghidra_frame + 0x84))
#define local_178 (*(int *)(ghidra_frame + 0x88))
#define local_164 (*(int *)(ghidra_frame + 0x9c))
#define local_160 (*(int *)(ghidra_frame + 0xa0))
#define local_15c (*(int *)(ghidra_frame + 0xa4))
#define local_158 (*(int *)(ghidra_frame + 0xa8))
#define local_154 (*(int *)(ghidra_frame + 0xac))
#define local_150 (*(int **)(ghidra_frame + 0xb0))
#define local_14c (*(uint (*)[4])(ghidra_frame + 0xb4))
#define local_13c (*(int *)(ghidra_frame + 0xc4))
#define local_138 (*(int *)(ghidra_frame + 0xc8))
#define local_134 (*(int **)(ghidra_frame + 0xcc))
#define local_130 (*(int **)(ghidra_frame + 0xd0))
#define local_12c (*(uint *)(ghidra_frame + 0xd4))
#define local_120 (*(int *)(ghidra_frame + 0xe0))
#define local_10c (*(char **(*)[4])(ghidra_frame + 0xf4))
#define local_fc (*(uint *)(ghidra_frame + 0x104))
#define iStack_f8 (*(int *)(ghidra_frame + 0x108))
#define uStack_f7 (*(uint3 *)(ghidra_frame + 0x109))
#define local_7c (*(char **)(ghidra_frame + 0x184))
#define local_78 (*(char **)(ghidra_frame + 0x188))
#define local_74 (*(char **)(ghidra_frame + 0x18c))
#define local_70 (*(char **)(ghidra_frame + 0x190))
#define local_6c (*(char **)(ghidra_frame + 0x194))
#define local_68 (*(char **)(ghidra_frame + 0x198))
#define local_64 (*(char **)(ghidra_frame + 0x19c))
#define local_60 (*(char **)(ghidra_frame + 0x1a0))
#define local_5c (*(char **)(ghidra_frame + 0x1a4))
#define local_4c (*(char **)(ghidra_frame + 0x1b4))
#define local_48 (*(undefined **)(ghidra_frame + 0x1b8))
#define local_44 (*(char **)(ghidra_frame + 0x1bc))
#define local_40 (*(char **)(ghidra_frame + 0x1c0))
#define local_3c (*(char **)(ghidra_frame + 0x1c4))
#define local_38 (*(char **)(ghidra_frame + 0x1c8))
#define local_34 (*(char **)(ghidra_frame + 0x1cc))
#define local_30 (*(char **)(ghidra_frame + 0x1d0))
#define local_2c (*(char **)(ghidra_frame + 0x1d4))
#define local_28 (*(char **)(ghidra_frame + 0x1d8))
#define local_24 (*(char **)(ghidra_frame + 0x1dc))
  
  piVar6 = g;
  bVar11 = (byte)_rgb_r_shift_16;
  bVar1 = (byte)_rgb_g_shift_16;
  bVar12 = (byte)_rgb_b_shift_16;
  uVar18 = 8 << (bVar11 & 0x1f) | 0xc << (bVar1 & 0x1f) | 4 << (bVar12 & 0x1f);
  local_14c[0] = 0;
  local_134 = g + 0x733b;
  local_14c[1] = 0;
  local_178 = 0;
  bVar3 = false;
  bVar5 = false;
  bVar4 = false;
  local_1a8 = 0;
  local_1b0 = 1;
  bVar2 = false;
  local_130 = g + 0x7348;
  V_SetBuf((int *)g[0x4136],0);
  TimerSetSyncFPS(0x3c);
  KBBufferClear();
  KBRepeat = 1;
  PadPoll();
  PadBufClear();
  UInpRefreshFlags();
  UInpBufClear();
  BGArrayReset(g[0x62d0]);
  local_4c = "Difficulty";
  g[0x79a6] = 0;
  local_10c[0] = &local_4c;
  local_10c[2] = &local_6c;
  local_10c[1] = &local_7c;
  local_48 = &DAT_0827d876;
  local_44 = "Time Limit";
  local_40 = "Game Speed";
  local_3c = "Wav Volume";
  local_38 = "Midi Volume";
  local_34 = "Input Config";
  local_30 = "Team Mode Config";
  local_28 = "Default Values";
  local_2c = "Load/Save";
  local_24 = "Return to Main Menu";
  local_6c = "Key Config";
  local_68 = "Joystick Type";
  local_64 = "Joystick Config";
  local_60 = "Default Values";
  local_5c = "Return to Options";
  local_7c = "1P VS Team Advantage";
  local_78 = "If player KOed";
  local_74 = "Default Values";
  local_70 = "Return to Options";
  FrameSkipReset();
LAB_080a1af0:
  iVar21 = 0;
  BGMPoll(g + 0x6efa);
  local_13c = 0;
  local_138 = 0;
  PadPoll();
  KBPoll();
  bVar8 = KBkbhit();
  if (GHIDRA_ZEXT8(bVar8) != 0) {
    local_13c = KBgetchraw();
  }
  bVar8 = PadHit();
  if (GHIDRA_ZEXT8(bVar8) != 0) {
    local_138 = PadGet();
  }
  GlobalInputUpdate();
  bVar8 = UInpHit();
  if (GHIDRA_ZEXT8(bVar8) != 0) {
    iVar21 = UInpGet();
  }
  if (bVar2) {
    iVar21 = 0;
    local_13c = 0;
    local_138 = 0;
    bVar2 = false;
  }
  KBIMenuGetKey(local_14c + 2,iVar21,(int)&local_134,2);
  uVar25 = local_14c[3];
  uVar19 = local_14c[2];
  PRSprArrayClear((int *)g[0x413d]);
  if (((g[0x738d] == 0x16) || (g[0x738e] == 0x16)) && (local_138 == 0xb)) {
    local_13c = 1;
    local_138 = 0;
  }
  if (local_1a8 == 1) {
    local_1ac = 4;
    local_158 = 0x31;
    local_15c = 0xdc;
    local_160 = 0x50;
    local_164 = 0xdc;
LAB_080a1cf8:
    local_1b0 = 1;
  }
  else if (local_1a8 < 2) {
    if (local_1a8 == 0) {
      local_1ac = 0xb;
      local_158 = 0x45;
      local_15c = 0xb4;
      local_160 = 0xa9;
      local_164 = 0xb4;
      goto LAB_080a1cf8;
    }
  }
  else if (local_1a8 == 2) {
    local_1ac = 5;
    local_158 = 0x1d;
    local_15c = 0x104;
    local_160 = 0x69;
    local_164 = 0x82;
    local_1b0 = 2;
  }
  if ((!bVar3) || ((local_14c[uVar25] == 8 && (local_1a8 == 0)))) {
    if ((uVar19 & 1) != 0) {
      uVar30 = local_14c[uVar25];
      local_14c[uVar25] = uVar30 - 1;
      if ((int)(uVar30 - 1) < 0) {
        local_14c[uVar25] = local_1ac - 1;
      }
      bVar4 = false;
      bVar3 = false;
      GameSndPlay((int *)g[0x5ec1],piVar6[0x1079],piVar6[0x107a],0);
    }
    if ((uVar19 & 4) != 0) {
      local_14c[uVar25] = local_14c[uVar25] + 1 & (local_1ac <= (int)(local_14c[uVar25] + 1)) - 1;
      bVar4 = false;
      bVar3 = false;
      GameSndPlay((int *)g[0x5ec1],piVar6[0x1079],piVar6[0x107a],0);
    }
  }
  if (local_1b0 == 1) {
    local_14c[1 - uVar25] = local_14c[uVar25];
  }
  bVar26 = (uVar19 & 0xff0) != 0;
  local_194 = (uint)((uVar19 & 8) != 0);
  bVar8 = (uVar19 & 2) != 0;
  if (bVar3) {
    if ((local_194 != 0) || (local_13c == 1)) {
      bVar5 = false;
    }
    if (bVar8) {
      bVar5 = true;
    }
    if ((bVar26) || (local_13c == 1)) {
      bVar4 = true;
    }
    bVar8 = false;
    local_194 = 0;
    bVar26 = false;
    if (local_13c == 1) {
      local_13c = 0;
    }
  }
  if (local_1a8 == 0) {
    uVar19 = g[local_14c[uVar25] + 0x799e];
    switch(local_14c[uVar25]) {
    case 0:
      if ((local_194 != 0) && (1 < (int)uVar19)) {
        uVar19 = uVar19 - 1;
      }
      if (bVar8) {
        bVar28 = SBORROW4(uVar19,7);
        bVar27 = (int)(uVar19 - 7) < 0;
        bVar8 = uVar19 == 7;
LAB_080a2018:
        if (bVar8 || bVar28 != bVar27) {
          uVar19 = uVar19 + 1;
        }
      }
      break;
    case 1:
      if ((local_194 != 0) && (0x1e < (int)uVar19)) {
        uVar19 = uVar19 - 10;
      }
      if ((bVar8) && ((int)uVar19 < 300)) {
        uVar19 = uVar19 + 10;
      }
      break;
    case 2:
      if (((local_194 == 0) || ((int)uVar19 < 0x15)) || (uVar19 == 99)) {
        if ((local_194 == 0) || (uVar19 != 99)) {
          if ((local_194 != 0) && (uVar19 == 0xffffffff)) {
            uVar19 = 99;
          }
        }
        else {
          uVar19 = 0x50;
        }
      }
      else {
        uVar19 = uVar19 - 0x14;
      }
      if (((bVar8) && ((int)uVar19 < 0x50)) && (uVar19 != 0xffffffff)) {
        uVar19 = uVar19 + 0x14;
      }
      else if ((bVar8) && (uVar19 == 0x50)) {
        uVar19 = 99;
      }
      else if ((bVar8) && (uVar19 == 99)) {
        uVar19 = 0xffffffff;
      }
      break;
    case 3:
      if ((local_194 != 0) && (-9 < (int)uVar19)) {
        uVar19 = uVar19 - 1;
      }
      if (bVar8) {
        bVar28 = SBORROW4(uVar19,8);
        bVar27 = (int)(uVar19 - 8) < 0;
        bVar8 = uVar19 == 8;
        goto LAB_080a2018;
      }
      break;
    case 4:
    case 5:
      if ((local_194 != 0) && (0 < (int)uVar19)) {
        uVar19 = uVar19 - 1;
      }
      if (bVar8) {
        bVar28 = SBORROW4(uVar19,99);
        bVar27 = (int)(uVar19 - 99) < 0;
        bVar8 = uVar19 == 99;
        goto LAB_080a2018;
      }
      break;
    case 8:
      uVar19 = uVar19 & local_194 - 1;
      if (bVar8) {
        uVar19 = 1;
      }
      if ((bVar3) && (bVar4)) {
LAB_080a2066:
        bVar4 = false;
        bVar3 = false;
      }
      break;
    case 9:
      if ((bVar3) && (bVar4)) {
        if (bVar5) {
          GameResetOptions();
        }
        goto LAB_080a2066;
      }
    }
    g[local_14c[uVar25] + 0x799e] = uVar19;
    if (!bVar3) {
      iVar21 = local_13c;
      if (local_13c == 1) {
        local_14c[uVar25] = 10;
        iVar21 = 1;
        bVar26 = true;
      }
      if (iVar21 == 0x3b) {
        local_14c[uVar25] = 6;
        bVar26 = true;
        iVar21 = local_13c;
      }
      if (iVar21 == 0x3c) {
        local_14c[uVar25] = 7;
        bVar26 = true;
      }
    }
    if (!bVar26) goto switchD_080a210f_caseD_a;
    switch(local_14c[uVar25]) {
    case 6:
      GameSndPlay((int *)g[0x5ec1],piVar6[0x107b],piVar6[0x107c],0);
      local_12c = local_14c[0];
      local_120 = local_14c[1];
      local_1a8 = 2;
      goto LAB_080a2196;
    case 7:
      GameSndPlay((int *)g[0x5ec1],piVar6[0x107b],piVar6[0x107c],0);
      local_12c = local_14c[0];
      local_120 = local_14c[1];
      local_1a8 = 1;
LAB_080a2196:
      local_14c[1] = 0;
      local_14c[0] = 0;
      goto LAB_080a1af0;
    case 8:
      GameSndPlay((int *)g[0x5ec1],piVar6[0x107b],piVar6[0x107c],0);
      if (g[local_14c[uVar25] + 0x799e] == 0) {
        GameLoadOptions();
      }
      else {
        GameSaveOptions();
      }
      bVar3 = true;
      bVar2 = true;
    default:
      bVar26 = false;
      break;
    case 9:
      GameSndPlay((int *)g[0x5ec1],piVar6[0x107b],piVar6[0x107c],0);
      bVar3 = true;
      bVar5 = false;
      bVar26 = false;
      piVar9 = g;
      goto LAB_080a286d;
    case 10:
      break;
    }
  }
  else if (local_1a8 == 2) {
    uVar19 = g[uVar25 * 5 + local_14c[uVar25] + 0x79aa];
    uVar30 = uVar19;
    piVar9 = g;
    if (local_14c[uVar25] == 1) {
      if (local_194 != 0) {
        uVar30 = uVar19 & (uVar19 != 0) - 1;
      }
      if ((bVar8) && (uVar30 == 0)) {
        uVar30 = 1;
      }
      if (uVar30 != uVar19) {
        iVar21 = 0;
        g[uVar25 * 5 + local_14c[uVar25] + 0x79aa] = uVar30;
        iStack_1dc = 0x1ce30;
        local_1e0 = 0x1ce30;
        local_1e4 = 0x1e6a4;
        local_1e8 = 0x1ce20;
        local_150 = (int *)0x1;
        do {
          piVar9 = g;
          uVar19 = (uint)(*(int *)(local_1e4 + 8 + (int)g) != 0);
          *(uint *)(local_1e8 + 0xc + (int)g) = uVar19;
          if (uVar19 == 0) {
            puVar23 = (undefined4 *)((int)piVar9 + iVar21 + 0x1cd54);
            for (iVar32 = 0xd; piVar9 = g, iVar32 != 0; iVar32 = iVar32 + -1) {
              *puVar23 = 0;
              puVar23 = puVar23 + 1;
            }
            *(undefined4 *)(iStack_1dc + 4 + (int)g) = 0;
            PlayerKeysRemoveZero(iVar21 + 0x1cd54 + (int)piVar9,0x80);
          }
          else {
            puVar23 = (undefined4 *)((int)piVar9 + iVar21 + 0x1cdbc);
            puVar24 = (undefined4 *)((int)piVar9 + iVar21 + 0x1cd54);
            for (iVar32 = 0xd; iVar32 != 0; iVar32 = iVar32 + -1) {
              *puVar24 = *puVar23;
              puVar23 = puVar23 + 1;
              puVar24 = puVar24 + 1;
            }
            *(uint *)((int)g + local_1e0 + 4) = uVar30;
          }
          iStack_1dc = iStack_1dc + 4;
          local_1e0 = local_1e0 + 4;
          local_1e4 = local_1e4 + 0x14;
          local_1e8 = local_1e8 + 4;
          iVar21 = iVar21 + 0x34;
          local_150 = (int *)((int)local_150 + -1);
        } while (-1 < (int)local_150);
        if (((g[0x738b] == 0) && (g[0x738c] == 0)) && (PadInstalled != 0)) {
          PadDeInit();
          piVar9 = g;
        }
        else {
          piVar9 = g;
          if ((g[0x799d] == 0) && (PadInstalled == 0)) {
            iVar21 = PadInit(g[(g[0x738c] != 0) + 0x738d],(uint)(g[0x738c] != 0));
            piVar9 = g;
            if (iVar21 == 0) {
              g[0x738c] = 0;
              piVar9[0x738b] = 0;
            }
            else {
              GameInputSetup();
              piVar9 = g;
            }
          }
        }
      }
    }
    piVar9[uVar25 * 5 + local_14c[uVar25] + 0x79aa] = uVar30;
    iVar21 = local_13c;
    if (local_13c == 1) {
      local_14c[1] = 4;
      local_14c[0] = 4;
      bVar26 = true;
      iVar21 = 1;
    }
    if (iVar21 == 0x3b) {
      local_14c[1] = 0;
      local_14c[0] = 0;
      bVar26 = true;
      iVar21 = local_13c;
    }
    if (iVar21 == 0x3c) {
      local_14c[1] = 2;
      local_14c[0] = 2;
      bVar26 = true;
    }
    if (!bVar26) goto switchD_080a210f_caseD_a;
    uVar19 = local_14c[uVar25];
    if (uVar19 == 2) {
      if ((g[0x738b] != 0) || (g[0x738c] != 0)) {
        GameSndPlay((int *)g[0x5ec1],piVar6[0x107b],piVar6[0x107c],0);
        local_178 = KeyConfigScreen(1,local_178);
        GameSndPlay((int *)g[0x5ec1],piVar6[0x107d],piVar6[0x107e],0);
      }
      bVar26 = false;
      piVar9 = g;
      goto LAB_080a286d;
    }
    if ((int)uVar19 < 3) {
      if (uVar19 == 0) {
        GameSndPlay((int *)g[0x5ec1],piVar6[0x107b],piVar6[0x107c],0);
        local_178 = KeyConfigScreen(0,local_178);
        GameSndPlay((int *)g[0x5ec1],piVar6[0x107d],piVar6[0x107e],0);
        bVar26 = false;
        piVar9 = g;
        goto LAB_080a286d;
      }
    }
    else {
      if (uVar19 == 3) {
        GameSndPlay((int *)g[0x5ec1],piVar6[0x107b],piVar6[0x107c],0);
        piVar9 = g;
        g[uVar25 * 5 + 0x79ab] = 0;
        goto LAB_080a2813;
      }
      if (uVar19 == 4) {
        GameSndPlay((int *)g[0x5ec1],piVar6[0x107d],piVar6[0x107e],0);
        local_14c[0] = local_12c;
        local_14c[1] = local_120;
        local_1a8 = 0;
        goto LAB_080a1af0;
      }
    }
  }
  else if (local_1a8 == 1) {
    uVar19 = local_14c[uVar25];
    iVar21 = g[uVar19 + 0x79b4];
    if (uVar19 == 0) {
      if ((local_194 != 0) && (100 < iVar21)) {
        iVar21 = iVar21 + -10;
      }
      if ((bVar8) && (iVar21 < 300)) {
        iVar21 = iVar21 + 10;
      }
    }
    else if (uVar19 == 1) {
      if ((local_194 != 0) && (0 < iVar21)) {
        iVar21 = iVar21 + -1;
      }
      if ((bVar8) && (iVar21 < 1)) {
        iVar21 = iVar21 + 1;
      }
    }
    g[local_14c[uVar25] + 0x79b4] = iVar21;
    if (local_13c == 1) {
      local_14c[uVar25] = 3;
      bVar26 = true;
    }
    if (bVar26) {
      if (local_14c[uVar25] == 2) {
        GameSndPlay((int *)g[0x5ec1],piVar6[0x107b],piVar6[0x107c],0);
        piVar9 = g;
        g[0x79b4] = 200;
        piVar9[0x79b5] = 0;
LAB_080a2813:
        bVar26 = false;
        goto LAB_080a286d;
      }
      if (local_14c[uVar25] == 3) {
        GameSndPlay((int *)g[0x5ec1],piVar6[0x107d],piVar6[0x107e],0);
        local_14c[0] = local_12c;
        local_1a8 = 0;
        local_14c[1] = local_120;
        goto LAB_080a1af0;
      }
    }
  }
switchD_080a210f_caseD_a:
  piVar9 = g;
LAB_080a286d:
  BGArrayMove((int *)piVar9[0x62d0],0.0,0.0);
  BGArrayUpdate(g[0x62d0]);
  if (g[0x7307] == 0) {
    MasterPalProcessChanges();
    BGArrayDrawLayer(g[0x62d0],0);
    iVar21 = local_158 + local_15c;
    W_BoxFillTransSub16(local_158 - 0xf,0x24,iVar21 + 0xe,local_160 + 0x31,
                        0x10 << (bVar11 & 0x1f) | 0x18 << (bVar1 & 0x1f) | 8 << (bVar12 & 0x1f));
    W_BoxFillTransSub16(local_158 - 0x10U,0x25,local_158 - 0x10U,local_160 + 0x30,uVar18);
    W_BoxFillTransSub16(iVar21 + 0xfU,0x25,iVar21 + 0xfU,local_160 + 0x30,uVar18);
    W_BoxFillTransSub16(local_158 - 0xeU,0x23,iVar21 + 0xdU,0x23,uVar18);
    W_BoxFillTransSub16(local_158 - 0xeU,local_160 + 0x32,iVar21 + 0xdU,local_160 + 0x32,uVar18);
    bVar13 = (byte)_rgb_r_shift_16;
    bVar14 = (byte)_rgb_g_shift_16;
    bVar15 = (byte)_rgb_b_shift_16;
    if (local_1a8 == 0) {
      uVar19 = 0x1f << (bVar13 & 0x1f) | 0x3f << (bVar14 & 0x1f) | 0x1f << (bVar15 & 0x1f);
      iVar32 = 0x14;
      iVar21 = V_Width / 2;
      piVar9 = (int *)g[0x413b];
      pcVar29 = "OPTIONS";
LAB_080a2b57:
      V_FontDrawCenter(pcVar29,piVar9,iVar21,iVar32,uVar19);
    }
    else {
      if (local_1a8 == 2) {
        V_FontDrawCenter("INPUT CONFIG",(int *)g[0x413b],V_Width / 2,0x14,
                         0x1f << (bVar13 & 0x1f) | 0x3f << (bVar14 & 0x1f) | 0x1f << (bVar15 & 0x1f)
                        );
        iVar21 = local_15c;
        if (local_15c < 0) {
          iVar21 = local_15c + 3;
        }
        V_FontDrawCenter("PLAYER 1",(int *)g[0x413b],(iVar21 >> 2) + local_158,0x2f,
                         0x10 << ((byte)_rgb_r_shift_16 & 0x1f) |
                         0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
                         0x1f << ((byte)_rgb_b_shift_16 & 0x1f));
        uVar19 = 0x1f << ((byte)_rgb_r_shift_16 & 0x1f) | 0x20 << ((byte)_rgb_g_shift_16 & 0x1f) |
                 0x10 << ((byte)_rgb_b_shift_16 & 0x1f);
        iVar32 = 0x2f;
        iVar21 = local_15c * 3;
        if (iVar21 < 0) {
          iVar21 = iVar21 + 3;
        }
        iVar21 = (iVar21 >> 2) + local_158;
        piVar9 = (int *)g[0x413b];
        pcVar29 = "PLAYER 2";
        goto LAB_080a2b57;
      }
      if (local_1a8 == 1) {
        uVar19 = 0x1f << (bVar13 & 0x1f) | 0x3f << (bVar14 & 0x1f) | 0x1f << (bVar15 & 0x1f);
        iVar32 = 0x14;
        iVar21 = V_Width / 2;
        piVar9 = (int *)g[0x413b];
        pcVar29 = "TEAM MODE CONFIG";
        goto LAB_080a2b57;
      }
    }
    local_154 = 0;
    do {
      local_150 = (int *)0x0;
      local_184 = 0;
      if (0 < local_1ac) {
        do {
          local_188 = local_158 + (local_154 * local_15c) / 2;
          if (local_1b0 == 2) {
            if (local_154 == 0) {
              local_188 = local_188 + -7;
            }
            else {
              local_188 = local_188 + 7;
            }
          }
          local_1f4 = (byte)_rgb_b_shift_16;
          uVar19 = 0x18 << ((byte)_rgb_r_shift_16 & 0x1f) | 0x30 << ((byte)_rgb_g_shift_16 & 0x1f) |
                   0x18 << (local_1f4 & 0x1f);
          if (local_1a8 == 0) {
            if ((local_150 == (int *)0xa) || (local_150 == (int *)0x8)) {
              local_184 = local_184 + 1;
            }
          }
          else if (local_1a8 == 2) {
            if (((local_150 == (int *)0x0) || (local_150 == (int *)0x3)) ||
               (local_150 == (int *)0x1)) {
              local_184 = local_184 + 1;
            }
          }
          else if ((local_1a8 == 1) && (local_150 == (int *)0x3)) {
            local_184 = local_184 + 1;
          }
          iVar21 = ((int)local_150 + local_184) * 0xd;
          piVar9 = (int *)(iVar21 + 0x32);
          if (local_150 == (int *)local_14c[local_154]) {
            iVar32 = local_178 * 4;
            if (iVar32 % 0x80 < 0x40) {
              iVar32 = iVar32 % 0x40 + 0x20;
            }
            else {
              iVar32 = 0x5f - iVar32 % 0x40;
            }
            local_17c = (iVar32 >> 3) << ((byte)_rgb_r_shift_16 & 0x1f) |
                        (iVar32 >> 2) << ((byte)_rgb_g_shift_16 & 0x1f) |
                        (iVar32 >> 3) << (local_1f4 & 0x1f);
            W_BoxFillTransAdd16(local_188 - 5,iVar21 + 0x28,
                                local_15c / (int)((local_1b0 != 1) + 1) + 4 + local_188,
                                iVar21 + 0x35,local_17c);
            local_1f4 = (byte)_rgb_b_shift_16;
            uVar19 = 0x1f << ((byte)_rgb_r_shift_16 & 0x1f) | 0x3f << ((byte)_rgb_g_shift_16 & 0x1f)
                     | 0x1f << (local_1f4 & 0x1f);
          }
          if (((local_1a8 == 2) && (local_150 == (int *)0x2)) &&
             ((g[0x738b] == 0 && (g[0x738c] == 0)))) {
            local_1f4 = (byte)_rgb_b_shift_16;
            uVar19 = 0x12 << ((byte)_rgb_r_shift_16 & 0x1f) | 0x20 << ((byte)_rgb_g_shift_16 & 0x1f)
                     | 0x10 << (local_1f4 & 0x1f);
          }
          V_FontDraw(local_10c[local_1a8][(int)local_150],(int *)g[0x413b],local_188,(int)piVar9,
                     uVar19);
          local_fc = local_fc & 0xffffff00;
          uVar7 = uStack_f7;
          piVar10 = g;
          if (local_1a8 != 0) {
            if (local_1a8 == 2) {
              iVar21 = g[(int)local_150 + local_154 * 5 + 0x79aa];
              if (local_150 == (int *)0x1) {
                if (iVar21 == 0) {
                  __n = 9;
                  pcVar29 = "Disabled";
LAB_080a3134:
                  memcpy(&local_fc,pcVar29,__n);
                }
                else if (iVar21 == 1) {
                  local_fc = 0x6f747541;
                  iStack_f8 = (uint)uStack_f7 << 8;
                }
                else if (iVar21 - 4U < 5) {
                  sprintf((char *)&local_fc,"%i button",iVar21,extraout_ECX);
                }
                else {
                  if (iVar21 == 0x14) {
                    __n = 0xb;
                    pcVar29 = "Sidewinder";
                    goto LAB_080a3134;
                  }
                  if (iVar21 == 0x15) {
                    local_fc = 0x53454e53;
                    iStack_f8 = 0x79654b;
                  }
                  else {
                    if (iVar21 == 0x16) {
                      local_fc = 0x20585350;
                    }
                    else {
                      if (iVar21 != 0x17) goto LAB_080a318f;
                      local_fc = 0x2034364e;
                    }
                    iStack_f8 = 0x646150;
                  }
                }
              }
LAB_080a318f:
              if ((g[local_154 + 0x738b] == 0) && (iVar21 != 0)) {
                uVar19 = 0x12 << ((byte)_rgb_r_shift_16 & 0x1f) |
                         0x20 << ((byte)_rgb_g_shift_16 & 0x1f) |
                         0x10 << ((byte)_rgb_b_shift_16 & 0x1f);
              }
            }
            else if (local_1a8 == 1) {
              piVar22 = (int *)g[(int)(local_150 + 0x1e6d)];
              if (local_150 == (int *)0x0) {
                pcVar29 = "%i%%";
                puVar17 = &local_fc;
                goto LAB_080a2f6f;
              }
              if (local_150 == (int *)0x1) {
                piVar10 = (int *)0x0;
                piVar20 = extraout_EDX;
                if (piVar22 == (int *)0x0) {
                  piVar10 = (int *)sprintf((char *)&local_fc,"Team loses",extraout_ECX,extraout_ECX)
                  ;
                  piVar20 = extraout_EDX_00;
                }
                if (piVar22 == (int *)0x1) {
                  piVar10 = (int *)sprintf((char *)&local_fc,"AI keeps fighting",piVar20,piVar20);
                }
                if (piVar22 == (int *)0x2) {
                  pcVar29 = "Control AI";
                  puVar17 = &local_fc;
                  piVar22 = piVar10;
                  goto LAB_080a2f6f;
                }
              }
            }
            goto switchD_080a2ecf_caseD_6;
          }
          piVar22 = (int *)g[(int)local_150 + 0x799e];
          switch((int)local_150) {
          case 0x0:
            if ((int)piVar22 < 3) {
              local_fc = 0x79736145;
              iStack_f8 = (uint)uVar7 << 8;
            }
            else if ((int)piVar22 < 6) {
              local_fc = 0x6964654d;
              iStack_f8 = CONCAT13((*(uchar *)((char *)&uStack_f7 + 2)),0x6d75);
            }
            else {
              local_fc = 0x64726148;
              iStack_f8 = (uint)uVar7 << 8;
            }
            pcVar29 = " %i";
            puVar17 = &local_fc;
            do {
              puVar16 = puVar17;
              puVar17 = puVar16 + 1;
              uVar30 = *puVar16 + 0xfefefeff & (*puVar16 ^ 0xffffffff);
              uVar31 = uVar30 & 0x80808080;
            } while (uVar31 == 0);
            if ((uVar30 & 0x8080) == 0) {
              uVar31 = uVar31 >> 0x10;
              puVar17 = (uint *)((int)puVar16 + 6);
            }
            puVar17 = (uint *)((int)puVar17 + (-3 - (uint)CARRY1((byte)uVar31,(byte)uVar31)));
            piVar10 = local_150;
            goto LAB_080a2f6f;
          case 0x1:
            pcVar29 = "%i%%";
            puVar17 = &local_fc;
            piVar10 = piVar9;
LAB_080a2f6f:
            sprintf((char *)puVar17,pcVar29,piVar22,piVar10);
            break;
          case 0x2:
            if (piVar22 != (int *)0xffffffff) {
              pcVar29 = "%i";
              puVar17 = &local_fc;
              goto LAB_080a2f6f;
            }
            local_fc = 0x656e6f4e;
            iStack_f8 = (uint)uVar7 << 8;
            break;
          case 0x3:
            if (piVar22 != (int *)0x0) {
              if ((int)piVar22 < 1) {
                piVar22 = (int *)-(int)piVar22;
                pcVar29 = "Slow %i";
                puVar17 = &local_fc;
                piVar10 = extraout_EDX;
              }
              else {
                pcVar29 = "Fast %i";
                puVar17 = &local_fc;
                piVar10 = extraout_ECX;
              }
              goto LAB_080a2f6f;
            }
            local_fc = 0x6d726f4e;
            iStack_f8 = CONCAT13((*(uchar *)((char *)&uStack_f7 + 2)),0x6c61);
            break;
          case 0x4:
          case 0x5:
            if (piVar22 == (int *)0x0) {
              local_fc = 0x66664f;
            }
            else {
              if (piVar22 != (int *)0x64) {
                pcVar29 = "%i";
                puVar17 = &local_fc;
                piVar10 = local_150;
                goto LAB_080a2f6f;
              }
              local_fc = 0x78614d;
            }
            break;
          case 0x8:
            if (piVar22 == (int *)0x0) {
              local_fc = 0x64616f4c;
              iStack_f8 = (uint)uVar7 << 8;
            }
            else {
              local_fc = 0x65766153;
              iStack_f8 = (uint)uVar7 << 8;
            }
          }
switchD_080a2ecf_caseD_6:
          iVar21 = local_188 + local_164;
          V_FontDrawRight((char *)&local_fc,(int *)g[0x413b],iVar21,(int)piVar9,uVar19);
          bVar13 = (byte)_rgb_r_shift_16;
          bVar14 = (byte)_rgb_g_shift_16;
          bVar15 = (byte)_rgb_b_shift_16;
          if (local_1a8 == 0) {
            if (local_150 == (int *)0x6) {
              V_FontDrawRight("(F1)",(int *)g[0x413b],iVar21,(int)piVar9,
                              0x1f << (bVar13 & 0x1f) | 0x3f << (bVar14 & 0x1f) |
                              0x10 << (bVar15 & 0x1f));
            }
            if (local_150 == (int *)0x7) {
              V_FontDrawRight("(F2)",(int *)g[0x413b],iVar21,(int)piVar9,
                              0x1f << ((byte)_rgb_r_shift_16 & 0x1f) |
                              0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
                              0x10 << ((byte)_rgb_b_shift_16 & 0x1f));
            }
            if (local_150 == (int *)0xa) {
              uVar19 = 0x1f << ((byte)_rgb_r_shift_16 & 0x1f) |
                       0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
                       0x10 << ((byte)_rgb_b_shift_16 & 0x1f);
              piVar10 = (int *)g[0x413b];
              goto LAB_080a3549;
            }
          }
          else if ((local_1a8 == 2) && (local_154 == 1)) {
            if (local_150 == (int *)0x0) {
              V_FontDrawRight("(F1)",(int *)g[0x413b],iVar21,(int)piVar9,
                              0x1f << (bVar13 & 0x1f) | 0x3f << (bVar14 & 0x1f) |
                              0x10 << (bVar15 & 0x1f));
            }
            if (local_150 == (int *)0x2) {
              V_FontDrawRight("(F2)",(int *)g[0x413b],iVar21,(int)piVar9,
                              0x1f << ((byte)_rgb_r_shift_16 & 0x1f) |
                              0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
                              0x10 << ((byte)_rgb_b_shift_16 & 0x1f));
            }
            if (local_150 == (int *)0x4) {
              uVar19 = 0x1f << ((byte)_rgb_r_shift_16 & 0x1f) |
                       0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
                       0x10 << ((byte)_rgb_b_shift_16 & 0x1f);
              piVar10 = (int *)g[0x413b];
LAB_080a3549:
              V_FontDrawRight("(Esc)",piVar10,local_188 + local_164,(int)piVar9,uVar19);
            }
          }
          else if ((local_1a8 == 1) && (local_150 == (int *)0x3)) {
            uVar19 = 0x1f << (bVar13 & 0x1f) | 0x3f << (bVar14 & 0x1f) | 0x10 << (bVar15 & 0x1f);
            piVar10 = (int *)g[0x413b];
            goto LAB_080a3549;
          }
          local_150 = (int *)((int)local_150 + 1);
        } while ((int)local_150 < local_1ac);
      }
    } while ((local_1b0 != 1) && (local_154 = local_154 + 1, local_154 < 2));
    if (bVar3) {
      W_Line(100.0,99.0,(float)(V_Width + -100),99.0,
             7 << ((byte)_rgb_r_shift_16 & 0x1f) | 0xe << ((byte)_rgb_g_shift_16 & 0x1f) |
             0xc << ((byte)_rgb_b_shift_16 & 0x1f));
      W_Line(100.0,131.0,(float)(V_Width + -100),131.0,
             7 << ((byte)_rgb_r_shift_16 & 0x1f) | 0xe << ((byte)_rgb_g_shift_16 & 0x1f) |
             0xc << ((byte)_rgb_b_shift_16 & 0x1f));
      W_Line(99.0,100.0,99.0,130.0,
             7 << ((byte)_rgb_r_shift_16 & 0x1f) | 0xe << ((byte)_rgb_g_shift_16 & 0x1f) |
             0xc << ((byte)_rgb_b_shift_16 & 0x1f));
      W_Line((float)(V_Width + -99),100.0,(float)(V_Width + -99),130.0,
             7 << ((byte)_rgb_r_shift_16 & 0x1f) | 0xe << ((byte)_rgb_g_shift_16 & 0x1f) |
             0xc << ((byte)_rgb_b_shift_16 & 0x1f));
      W_BoxFill(100,100,V_Width + -100,0x82,
                10 << ((byte)_rgb_r_shift_16 & 0x1f) | 0x15 << ((byte)_rgb_g_shift_16 & 0x1f) |
                0x11 << ((byte)_rgb_b_shift_16 & 0x1f));
      bVar14 = (byte)_rgb_r_shift_16;
      bVar15 = (byte)_rgb_g_shift_16;
      bVar13 = (byte)_rgb_b_shift_16;
      if (local_14c[uVar25] == 9) {
        if (bVar5) {
          local_150 = (int *)(0x18 << (bVar14 & 0x1f) | 0x30 << (bVar15 & 0x1f) |
                             0x18 << (bVar13 & 0x1f));
          uVar31 = 0xb4;
          uVar25 = 0x1f << (bVar14 & 0x1f) | 0x3f << (bVar15 & 0x1f);
          uVar30 = 0xa2;
          uVar19 = 0x1f << (bVar13 & 0x1f);
        }
        else {
          local_150 = (int *)(0x1f << (bVar14 & 0x1f) | 0x3f << (bVar15 & 0x1f) |
                             0x1f << (bVar13 & 0x1f));
          uVar25 = 0x18 << (bVar14 & 0x1f) | 0x30 << (bVar15 & 0x1f);
          uVar31 = 0x9d;
          uVar19 = 0x18 << (bVar13 & 0x1f);
          uVar30 = 0x8e;
        }
        W_BoxFillTransAdd16(uVar30,0x73,uVar31,0x7f,local_17c);
        V_FontDrawCenter("Confirm",(int *)g[0x413b],0x9f,0x70,
                         0x1f << ((byte)_rgb_r_shift_16 & 0x1f) |
                         0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
                         0x1f << ((byte)_rgb_b_shift_16 & 0x1f));
        V_FontDrawRight("No",(int *)g[0x413b],0x9a,0x7d,(uint)local_150);
        V_FontDraw("Yes",(int *)g[0x413b],0xa4,0x7d,uVar25 | uVar19);
      }
      else if (local_14c[uVar25] == 8) {
        if (g[0x79a6] == 0) {
          uVar19 = 0x1f << (bVar14 & 0x1f) | 0x3f << (bVar15 & 0x1f) | 0x1f << (bVar13 & 0x1f);
          piVar9 = (int *)g[0x413b];
          pcVar29 = "Options Loaded";
        }
        else {
          uVar19 = 0x1f << (bVar14 & 0x1f) | 0x3f << (bVar15 & 0x1f) | 0x1f << (bVar13 & 0x1f);
          piVar9 = (int *)g[0x413b];
          pcVar29 = "Options Saved";
        }
        V_FontDrawCenter(pcVar29,piVar9,0x9f,0x76,uVar19);
      }
    }
    BGArrayDrawLayer(g[0x62d0],1);
  }
  if (local_13c == 0x58) {
    ScreenSnap();
  }
  if (g[0x82d2] == 0) {
    TimerWaitSync();
  }
  if ((g[0x7307] == 0) && (g[0x4143] != 0)) {
    VRetrace();
  }
  DrawToScreen();
  if (g[0x7307] == 0) {
    MasterPalFinishedDraw();
  }
  FrameSkipUpdate();
  local_178 = local_178 + 1;
  if ((bVar26) && (((local_14c[0] == 10 || (local_14c[1] == 10)) && (local_1a8 == 0)))) {
    FrameSkipReset();
    GameSndPlay((int *)g[0x5ec1],piVar6[0x107d],piVar6[0x107e],0);
    KBRepeat = 0;
    return;
  }
  goto LAB_080a1af0;
}
#undef local_1f4
#undef local_1e8
#undef local_1e4
#undef local_1e0
#undef iStack_1dc
#undef local_1b0
#undef local_1ac
#undef local_1a8
#undef local_194
#undef local_188
#undef local_184
#undef local_17c
#undef local_178
#undef local_164
#undef local_160
#undef local_15c
#undef local_158
#undef local_154
#undef local_150
#undef local_14c
#undef local_13c
#undef local_138
#undef local_134
#undef local_130
#undef local_12c
#undef local_120
#undef local_10c
#undef local_fc
#undef iStack_f8
#undef uStack_f7
#undef local_7c
#undef local_78
#undef local_74
#undef local_70
#undef local_6c
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_24

/* KeyConfigScreen @ 0x080a3aa0, 5453 bytes
 * FIXUP: 3 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 51 stack locals placed at their original offsets in a 0x270-byte frame (a local's address escapes, see apply_frame_emulation) */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

int KeyConfigScreen(int param_1,int param_2)

{
  byte bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  uint uVar10;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined4 uVar11;
  uint uVar12;
  char *pcVar13;
  undefined4 *puVar14;
  int iVar15;
  uint uVar16;
  uint extraout_ECX;
  int iVar17;
  int iVar18;
  char *pcVar19;
  int iVar20;
  undefined4 *puVar21;
  int *piVar22;
  uint uVar23;
  unsigned char ghidra_frame[0x270] __attribute__((aligned(16)));
#define local_270 (*(uint *)(ghidra_frame + 0x0))
#define local_26c (*(int *)(ghidra_frame + 0x4))
#define local_268 (*(int *)(ghidra_frame + 0x8))
#define local_264 (*(int *)(ghidra_frame + 0xc))
#define local_254 (*(uint *)(ghidra_frame + 0x1c))
#define local_248 (*(byte *)(ghidra_frame + 0x28))
#define local_244 (*(byte *)(ghidra_frame + 0x2c))
#define local_240 (*(int *)(ghidra_frame + 0x30))
#define local_23c (*(int *)(ghidra_frame + 0x34))
#define local_22c (*(int *)(ghidra_frame + 0x44))
#define local_224 (*(uint *)(ghidra_frame + 0x4c))
#define local_220 (*(int *)(ghidra_frame + 0x50))
#define local_21c (*(uint *)(ghidra_frame + 0x54))
#define local_218 (*(uint *)(ghidra_frame + 0x58))
#define local_214 (*(int *(*)[15])(ghidra_frame + 0x5c))
#define auStack_1d8 (*(uint (*)[10])(ghidra_frame + 0x98))
#define auStack_1b0 (*(uint (*)[25])(ghidra_frame + 0xc0))
#define local_14c (*(char *(*)[4])(ghidra_frame + 0x124))
#define local_13c (*(char **)(ghidra_frame + 0x134))
#define local_138 (*(char **)(ghidra_frame + 0x138))
#define local_134 (*(char **)(ghidra_frame + 0x13c))
#define local_130 (*(char **)(ghidra_frame + 0x140))
#define local_12c (*(char **)(ghidra_frame + 0x144))
#define local_128 (*(char **)(ghidra_frame + 0x148))
#define local_124 (*(undefined **)(ghidra_frame + 0x14c))
#define local_120 (*(char **)(ghidra_frame + 0x150))
#define local_11c (*(char **)(ghidra_frame + 0x154))
#define local_118 (*(undefined **)(ghidra_frame + 0x158))
#define local_10c (*(char (*)[2])(ghidra_frame + 0x164))
#define acStack_10a (*(char (*)[126])(ghidra_frame + 0x166))
#define local_8c (*(uint *)(ghidra_frame + 0x1e4))
#define local_88 (*(int *)(ghidra_frame + 0x1e8))
#define local_84 (*(int *)(ghidra_frame + 0x1ec))
#define local_7c (*(int *)(ghidra_frame + 0x1f4))
#define local_78 (*(int *)(ghidra_frame + 0x1f8))
#define local_74 (*(int *)(ghidra_frame + 0x1fc))
#define local_70 (*(int *)(ghidra_frame + 0x200))
#define local_6c (*(int *)(ghidra_frame + 0x204))
#define local_60 (*(int *)(ghidra_frame + 0x210))
#define local_5c (*(int *)(ghidra_frame + 0x214))
#define local_58 (*(uint *)(ghidra_frame + 0x218))
#define local_54 (*(uint *)(ghidra_frame + 0x21c))
#define local_50 (*(int *)(ghidra_frame + 0x220))
#define local_4c (*(undefined4 *)(ghidra_frame + 0x224))
#define local_48 (*(undefined4 *)(ghidra_frame + 0x228))
#define local_44 (*(undefined4 *)(ghidra_frame + 0x22c))
#define local_40 (*(undefined4 *)(ghidra_frame + 0x230))
#define local_34 (*(undefined4 *)(ghidra_frame + 0x23c))
#define local_30 (*(undefined4 *)(ghidra_frame + 0x240))
#define local_2c (*(uint *)(ghidra_frame + 0x244))
#define local_28 (*(uint *)(ghidra_frame + 0x248))
  
  iVar8 = TimerFPS;
  iVar7 = KBRepeat;
  local_254 = (uint)(param_1 == 0);
  uVar10 = (local_254 - 1 & 0xffffff80) + 0x100;
  local_58 = 0x10 << ((byte)_rgb_r_shift_16 & 0x1f) | 0x18 << ((byte)_rgb_g_shift_16 & 0x1f) |
             8 << ((byte)_rgb_b_shift_16 & 0x1f);
  local_54 = 8 << ((byte)_rgb_r_shift_16 & 0x1f) | 0xc << ((byte)_rgb_g_shift_16 & 0x1f) |
             4 << ((byte)_rgb_b_shift_16 & 0x1f);
  local_23c = 0;
  local_8c = 0;
  local_88 = 0;
  local_84 = 0;
  local_7c = 0x31;
  local_78 = 0x1e;
  local_74 = 0xdc;
  local_70 = 0xcd;
  local_6c = 0xd;
  local_60 = 0x50;
  local_5c = 0xf;
  local_50 = V_Width + 0x31;
  local_4c = 0x1e;
  local_48 = 0xdc;
  local_44 = 0xcd;
  local_40 = 0xd;
  local_34 = 0x50;
  local_30 = 0xf;
  if (param_1 == 0) {
    local_214[0] = g + 0x7321;
    local_214[1] = g + 0x732e;
  }
  else {
    local_214[0] = g + 0x736f;
    local_214[1] = g + 0x737c;
  }
  local_14c[0] = "Config all";
  local_14c[1] = "Up";
  local_14c[2] = "Down";
  local_14c[3] = "Left";
  local_13c = "Right";
  local_138 = "A";
  local_134 = "B";
  local_130 = "C";
  local_12c = "X";
  local_128 = "Y";
  local_124 = &DAT_0828334d;
  local_120 = "Start";
  local_11c = "Default";
  local_118 = &DAT_082798d6;
  local_220 = 0;
  iVar15 = 0;
  local_2c = local_58;
  local_28 = local_54;
  do {
    piVar22 = local_214[local_220];
    *(int *)((int)auStack_1b0 + iVar15 + 4) = piVar22[1];
    *(int *)((int)auStack_1b0 + iVar15 + 8) = piVar22[3];
    *(int *)((int)auStack_1b0 + iVar15 + 0xc) = piVar22[4];
    *(int *)((int)auStack_1b0 + iVar15 + 0x10) = piVar22[2];
    *(int *)((int)auStack_1b0 + iVar15 + 0x14) = piVar22[5];
    *(int *)((int)auStack_1b0 + iVar15 + 0x18) = piVar22[6];
    *(int *)((int)auStack_1b0 + iVar15 + 0x1c) = piVar22[7];
    *(int *)((int)auStack_1b0 + iVar15 + 0x20) = piVar22[8];
    *(int *)((int)auStack_1b0 + iVar15 + 0x24) = piVar22[9];
    *(int *)((int)auStack_1b0 + iVar15 + 0x28) = piVar22[10];
    *(int *)((int)auStack_1b0 + iVar15 + 0x2c) = piVar22[0xb];
    iVar15 = iVar15 + 0x2c;
    local_220 = local_220 + 1;
  } while (local_220 < 2);
  V_SetBuf((int *)g[0x4136],0);
  TimerSetSyncFPS(0x3c);
  KBBufferClear();
  PadPoll();
  PadBufClear();
  UInpRefreshFlags();
  UInpBufClear();
  KBRepeat = 1;
  FrameSkipReset();
  local_26c = param_2 << 2;
  do {
    bVar3 = false;
    BGMPoll(g + 0x6efa);
    bVar2 = false;
    bVar4 = false;
    local_21c = 0;
    local_218 = 0;
    bVar5 = false;
    local_84 = 0;
    PadPoll();
    KBPoll();
    bVar9 = KBkbhit();
    if (GHIDRA_ZEXT8(bVar9) != 0) {
      local_21c = KBgetchraw();
    }
    bVar9 = PadHit();
    if (GHIDRA_ZEXT8(bVar9) != 0) {
      local_218 = PadGet();
    }
    GlobalInputUpdate();
    bVar9 = UInpHit();
    if (GHIDRA_ZEXT8(bVar9) != 0) {
      UInpGet();
    }
    uVar16 = local_218 & 0xffffff9f;
    if ((local_21c == 0x1c) || (uVar16 - 5 < 0x1b)) {
      local_84 = 1;
    }
    if ((local_21c == 200) || (uVar16 == 1)) {
      bVar2 = true;
    }
    if ((local_21c == 0xd0) || (uVar16 == 2)) {
      bVar3 = true;
    }
    if ((local_21c == 0xcb) || (uVar16 == 3)) {
      bVar4 = true;
    }
    if ((local_21c == 0xcd) || (uVar16 == 4)) {
      bVar5 = true;
    }
    if (local_23c != 0) {
      bVar3 = false;
      bVar2 = false;
      bVar4 = false;
      bVar5 = false;
      local_84 = 0;
    }
    if (local_21c - 0x3b < 2) {
      local_8c = (uint)(local_21c != 0x3b);
      local_88 = 0;
      local_84 = 1;
    }
    if (local_21c - 0x3d < 2) {
      local_8c = (uint)(local_21c != 0x3d);
      local_88 = 0xc;
      local_84 = 1;
    }
    if ((local_21c == 1) && (local_23c == 0)) {
      local_88 = 0xd;
      local_84 = 1;
    }
    if ((local_21c == 1) && (local_23c != 0)) {
      local_88 = 0;
      local_84 = 0;
      local_23c = 0;
      local_220 = 0;
      do {
        iVar15 = local_8c * 0xb + local_220;
        auStack_1b0[iVar15 + 1] = (uint)local_214[iVar15 + 2];
        local_220 = local_220 + 1;
      } while (local_220 < 0xb);
    }
    if (bVar2) {
      if (local_88 < 1) {
        local_88 = 0xd;
      }
      else {
        local_88 = local_88 + -1;
      }
      if (local_88 - 1U < 0xb) {
        local_88 = 0;
      }
    }
    if (bVar3) {
      if (local_88 < 0xd) {
        local_88 = local_88 + 1;
      }
      else {
        local_88 = 0;
      }
      if (local_88 - 1U < 0xb) {
        local_88 = 0xc;
      }
    }
    if (bVar4) {
      local_8c = 0;
    }
    if (bVar5) {
      local_8c = 1;
    }
    if ((local_84 != 0) && (local_88 == 0)) {
      local_220 = 0;
      do {
        iVar15 = local_8c * 0xb + local_220;
        local_214[iVar15 + 2] = (int *)auStack_1b0[iVar15 + 1];
        local_220 = local_220 + 1;
      } while (local_220 < 0xb);
      local_23c = local_8c + 1;
      local_240 = 0;
      KBRepeat = 0;
      local_21c = 0;
      local_218 = 0;
    }
    if ((local_88 == 0xc) && (local_84 != 0)) {
      local_220 = 0;
      do {
        if (param_1 == 0) {
          iVar18 = local_8c * 0xb + local_220;
          iVar15 = iVar18 * 4;
          uVar11 = (&DefaultKeyCfg)[iVar18];
        }
        else {
          iVar15 = (local_8c * 0xb + local_220) * 4;
          uVar11 = *(undefined4 *)(DefaultJoyCfg + iVar15);
        }
        *(undefined4 *)((int)auStack_1b0 + iVar15 + 4) = uVar11;
        local_220 = local_220 + 1;
      } while (local_220 < 0xb);
    }
    if (((local_23c != 0) && (local_21c != 1)) &&
       ((((param_1 == 0 && ((local_21c != 0 && ((local_21c & 0x100) == 0)))) ||
         ((param_1 == 1 && ((local_218 != 0 && ((local_218 & 0x100) == 0)))))) ||
        (local_21c == 0x39)))) {
      if (local_21c == 0x39) {
        auStack_1d8[local_23c * 0xb + local_240] = uVar10;
      }
      else if (local_23c != 0) {
        if (param_1 != 0) {
          local_21c = local_218;
        }
        auStack_1d8[local_23c * 0xb + local_240] = local_21c;
      }
      local_240 = local_240 + 1;
      if (10 < local_240) {
        local_23c = 0;
        KBRepeat = 1;
      }
    }
    BGArrayMove((int *)g[0x62d0],0.0,0.0);
    BGArrayUpdate(g[0x62d0]);
    if (g[0x7307] == 0) {
      MasterPalProcessChanges();
      uVar16 = extraout_ECX;
      BGArrayDrawLayer(g[0x62d0],0);
      W_BoxFillTransSub16(local_7c - local_5c,local_78 + -0xe,local_5c + -1 + local_7c + local_74,
                          local_78 + local_70 + -1,local_58);
      uVar12 = (local_7c - local_5c) - 1;
      W_BoxFillTransSub16(uVar12,local_78 + -0xd,uVar12,local_78 + local_70 + -2,local_54);
      uVar12 = local_74 + local_7c + local_5c;
      W_BoxFillTransSub16(uVar12,local_78 + -0xd,uVar12,local_78 + local_70 + -2,local_54);
      W_BoxFillTransSub16((local_7c - local_5c) + 1,local_78 + -0xf,
                          local_5c + -2 + local_7c + local_74,local_78 + -0xf,local_54);
      W_BoxFillTransSub16((local_7c - local_5c) + 1,local_70 + local_78,
                          local_5c + -2 + local_7c + local_74,local_70 + local_78,local_54);
      pcVar13 = "JOYSTICK CONFIG";
      if (param_1 == 0) {
        pcVar13 = "KEY CONFIG";
      }
      V_FontDrawCenter(pcVar13,(int *)g[0x413b],V_Width / 2,10,
                       0x1f << ((byte)_rgb_r_shift_16 & 0x1f) |
                       0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
                       0x1f << ((byte)_rgb_b_shift_16 & 0x1f));
      V_FontDrawCenter("PLAYER 1",(int *)g[0x413b],0x5a,local_78 + -3,
                       0x10 << ((byte)_rgb_r_shift_16 & 0x1f) |
                       0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
                       0x1f << ((byte)_rgb_b_shift_16 & 0x1f));
      V_FontDrawCenter("PLAYER 2",(int *)g[0x413b],0xe5,local_78 + -3,
                       0x1f << ((byte)_rgb_r_shift_16 & 0x1f) |
                       0x20 << ((byte)_rgb_g_shift_16 & 0x1f) |
                       0x10 << ((byte)_rgb_b_shift_16 & 0x1f));
      uVar12 = param_2 % 0x1c2;
      if ((int)uVar12 < 0x96) {
        pcVar13 = "Press a key to assign to entry";
        pcVar19 = local_10c;
        for (iVar15 = 7; iVar15 != 0; iVar15 = iVar15 + -1) {
          *(undefined4 *)pcVar19 = *(undefined4 *)pcVar13;
          pcVar13 = pcVar13 + 4;
          pcVar19 = pcVar19 + 4;
        }
        pcVar19[0] = 'r';
        pcVar19[1] = 'y';
        pcVar19[2] = '\0';
      }
      else if ((int)uVar12 < 300) {
        pcVar13 = "Press spacebar to disable entry";
        pcVar19 = local_10c;
        for (iVar15 = 8; iVar15 != 0; iVar15 = iVar15 + -1) {
          *(undefined4 *)pcVar19 = *(undefined4 *)pcVar13;
          pcVar13 = pcVar13 + 4;
          pcVar19 = pcVar19 + 4;
        }
      }
      else {
        memcpy(local_10c,"Press esc to cancel",0x14);
        uVar16 = uVar12;
      }
      if (local_23c == 1) {
        V_FontDraw(local_10c,(int *)g[0x413a],local_7c,local_6c * 0xd + local_78 + 10,
                   0x18 << ((byte)_rgb_r_shift_16 & 0x1f) | 0x30 << ((byte)_rgb_g_shift_16 & 0x1f) |
                   0x18 << ((byte)_rgb_b_shift_16 & 0x1f));
      }
      else if (local_23c == 2) {
        V_FontDrawRight(local_10c,(int *)g[0x413a],local_74 + local_7c,
                        local_6c * 0xd + local_78 + 10,
                        0x18 << ((byte)_rgb_r_shift_16 & 0x1f) |
                        0x30 << ((byte)_rgb_g_shift_16 & 0x1f) |
                        0x18 << ((byte)_rgb_b_shift_16 & 0x1f));
      }
      local_22c = 0;
      local_220 = 0;
      local_268 = 0;
      do {
        bVar1 = (byte)_rgb_r_shift_16;
        local_244 = (byte)_rgb_g_shift_16;
        local_248 = (byte)_rgb_b_shift_16;
        uVar12 = 0x18 << (bVar1 & 0x1f) | 0x30 << (local_244 & 0x1f) | 0x18 << (local_248 & 0x1f);
        if (((local_220 == 0xe) || (local_220 == 0xc)) || (local_220 == 0)) {
          local_22c = local_22c + 1;
        }
        iVar15 = (local_220 + local_22c) * local_6c + local_78;
        local_224 = uVar12;
        if (local_220 == local_88) {
          if (local_26c % 0x80 < 0x40) {
            iVar18 = local_26c % 0x40 + 0x20;
          }
          else {
            iVar18 = 0x5f - local_26c % 0x40;
          }
          if (local_23c == 0) {
            local_270 = (iVar18 >> 3) << (bVar1 & 0x1f) | (iVar18 >> 2) << (local_244 & 0x1f) |
                        (iVar18 >> 3) << (local_248 & 0x1f);
          }
          else {
            local_270 = 0xc << (bVar1 & 0x1f) | 0x18 << (local_244 & 0x1f) |
                        0xc << (local_248 & 0x1f);
          }
          iVar18 = local_7c;
          if (local_220 < 0xd) {
            iVar18 = local_8c * 0x8c + local_7c;
          }
          W_BoxFillTransAdd16(iVar18 - 5,iVar15 + -10,iVar18 + 0x56,iVar15 + 3,local_270);
          if ((local_8c == 0) || (local_88 == 0xd)) {
            uVar12 = 0x1f << ((byte)_rgb_r_shift_16 & 0x1f) | 0x3f << ((byte)_rgb_g_shift_16 & 0x1f)
                     | 0x1f << ((byte)_rgb_b_shift_16 & 0x1f);
          }
          else {
            local_224 = 0x1f << ((byte)_rgb_r_shift_16 & 0x1f) |
                        0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
                        0x1f << ((byte)_rgb_b_shift_16 & 0x1f);
          }
        }
        if ((0xb < local_220) && (local_23c != 0)) break;
        V_FontDraw(*(char **)((int)local_14c + local_268),(int *)g[0x413b],local_7c,iVar15,uVar12);
        if (local_220 < 0xd) {
          V_FontDraw(*(char **)((int)local_14c + local_268),(int *)g[0x413b],local_7c + 0x8c,iVar15,
                     local_224);
        }
        if (local_220 == 0) {
          V_FontDrawRight("(F1)",(int *)g[0x413b],local_60 + local_7c,iVar15,
                          0x1f << ((byte)_rgb_r_shift_16 & 0x1f) |
                          0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
                          0x10 << ((byte)_rgb_b_shift_16 & 0x1f));
          V_FontDrawRight("(F2)",(int *)g[0x413b],local_7c + 0x8c + local_60,iVar15,
                          0x1f << ((byte)_rgb_r_shift_16 & 0x1f) |
                          0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
                          0x10 << ((byte)_rgb_b_shift_16 & 0x1f));
        }
        if (local_220 == 0xc) {
          V_FontDrawRight("(F3)",(int *)g[0x413b],local_60 + local_7c,iVar15,
                          0x1f << ((byte)_rgb_r_shift_16 & 0x1f) |
                          0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
                          0x10 << ((byte)_rgb_b_shift_16 & 0x1f));
          V_FontDrawRight("(F4)",(int *)g[0x413b],local_7c + 0x8c + local_60,iVar15,
                          0x1f << ((byte)_rgb_r_shift_16 & 0x1f) |
                          0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
                          0x10 << ((byte)_rgb_b_shift_16 & 0x1f));
        }
        if (local_220 == 0xd) {
          V_FontDrawRight("(Esc)",(int *)g[0x413b],local_60 + local_7c,iVar15,
                          0x1f << ((byte)_rgb_r_shift_16 & 0x1f) |
                          0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
                          0x10 << ((byte)_rgb_b_shift_16 & 0x1f));
        }
        if (local_220 - 1U < 0xb) {
          if (param_1 == 0) {
            uVar23 = *(uint *)((int)auStack_1b0 + local_268);
            if (uVar23 == 0x100) {
              memcpy(local_10c,"Not used",9);
              uVar16 = uVar23;
            }
            else {
              puVar14 = KBRawToName((byte)uVar23);
              sprintf(local_10c,"%s",puVar14);
            }
            V_FontDrawRight(local_10c,(int *)g[0x413b],local_60 + local_7c,iVar15,uVar12);
            uVar12 = *(uint *)((int)auStack_1b0 + local_268 + 0x2c);
            if (uVar12 == 0x100) {
              memcpy(local_10c,"Not used",9);
              uVar16 = uVar12;
            }
            else {
              puVar14 = KBRawToName((byte)uVar12);
              sprintf(local_10c,"%s",puVar14,uVar16);
            }
            iVar18 = local_7c + 0x8c + local_60;
            piVar22 = (int *)g[0x413b];
          }
          else {
            uVar16 = *(uint *)((int)auStack_1b0 + local_268);
            if (uVar16 == uVar10) {
              memcpy(local_10c,"Not used",9);
            }
            else {
              sprintf(local_10c,"%c-%02i",((int)uVar16 >> 5 & 0x11U) + 0x41,uVar16 & 0xffffff9f);
            }
            V_FontDrawRight(local_10c,(int *)g[0x413b],local_60 + local_7c,iVar15,uVar12);
            uVar23 = *(uint *)((int)auStack_1b0 + local_268 + 0x2c);
            if (uVar23 == uVar10) {
              memcpy(local_10c,"Not used",9);
              uVar16 = uVar12;
            }
            else {
              uVar16 = uVar23 & 0xffffff9f;
              sprintf(local_10c,"%c-%02i",((int)uVar23 >> 5 & 0x11U) + 0x41,uVar16);
            }
            iVar18 = local_7c + 0x8c + local_60;
            piVar22 = (int *)g[0x413b];
          }
          V_FontDrawRight(local_10c,piVar22,iVar18,iVar15,local_224);
        }
        local_220 = local_220 + 1;
        local_268 = local_268 + 4;
      } while (local_220 < 0xe);
      if (local_23c != 0) {
        iVar15 = (local_240 + 2) * local_6c + local_78;
        if (local_26c % 0x80 < 0x40) {
          iVar18 = local_26c % 0x40 + 0x20;
        }
        else {
          iVar18 = 0x5f - local_26c % 0x40;
        }
        if (local_23c == 1) {
          uVar16 = local_7c + 0x56;
          iVar17 = local_7c;
        }
        else {
          uVar16 = local_7c + 0xe2;
          iVar17 = local_7c + 0x8c;
        }
        W_BoxFillTransAdd16(iVar17 - 5,iVar15 + -9,uVar16,iVar15 + 2,
                            (iVar18 >> 3) << ((byte)_rgb_r_shift_16 & 0x1f) |
                            (0x60 - iVar18 >> 2) << ((byte)_rgb_g_shift_16 & 0x1f) |
                            (0x60 - iVar18 / 2 >> 3) << ((byte)_rgb_b_shift_16 & 0x1f));
      }
      BGArrayDrawLayer(g[0x62d0],1);
    }
    if (g[0x82d2] == 0) {
      TimerWaitSync();
    }
    if ((g[0x7307] == 0) && (g[0x4143] != 0)) {
      VRetrace();
    }
    DrawToScreen();
    if (g[0x7307] == 0) {
      MasterPalFinishedDraw();
    }
    FrameSkipUpdate();
    local_26c = local_26c + 4;
    param_2 = param_2 + 1;
    if ((local_84 != 0) && (local_88 == 0xd)) {
      iVar15 = 0;
      FrameSkipReset();
      local_220 = 0;
      local_264 = 0;
      do {
        iVar20 = 0;
        iVar18 = *(int *)((int)local_214 + local_264);
        iVar17 = iVar15;
        do {
          piVar22 = &KeyCfgToKBIMap + iVar20;
          iVar20 = iVar20 + 1;
          iVar6 = iVar17 + 4;
          iVar17 = iVar17 + 4;
          *(undefined4 *)(iVar18 + *piVar22 * 4) = *(undefined4 *)((int)auStack_1b0 + iVar6);
        } while (iVar20 < 0xb);
        local_220 = local_220 + 1;
        local_264 = local_264 + 4;
        iVar15 = iVar15 + 0x2c;
      } while (local_220 < 2);
      if (param_1 == 1) {
        iVar18 = 0;
        iVar15 = 0x1ce20;
        local_220 = 1;
        do {
          if (*(int *)(iVar15 + 0xc + (int)g) != 0) {
            puVar14 = (undefined4 *)((int)g + iVar18 + 0x1cdbc);
            puVar21 = (undefined4 *)((int)g + iVar18 + 0x1cd54);
            for (iVar17 = 0xd; iVar17 != 0; iVar17 = iVar17 + -1) {
              *puVar21 = *puVar14;
              puVar14 = puVar14 + 1;
              puVar21 = puVar21 + 1;
            }
          }
          iVar18 = iVar18 + 0x34;
          iVar15 = iVar15 + 4;
          local_220 = local_220 + -1;
        } while (-1 < local_220);
      }
      GameInputSetup();
      KBRepeat = iVar7;
      TimerSetSyncFPS(iVar8);
      return param_2;
    }
  } while( true );
}
#undef local_270
#undef local_26c
#undef local_268
#undef local_264
#undef local_254
#undef local_248
#undef local_244
#undef local_240
#undef local_23c
#undef local_22c
#undef local_224
#undef local_220
#undef local_21c
#undef local_218
#undef local_214
#undef auStack_1d8
#undef auStack_1b0
#undef local_14c
#undef local_13c
#undef local_138
#undef local_134
#undef local_130
#undef local_12c
#undef local_128
#undef local_124
#undef local_120
#undef local_11c
#undef local_118
#undef local_10c
#undef acStack_10a
#undef local_8c
#undef local_88
#undef local_84
#undef local_7c
#undef local_78
#undef local_74
#undef local_70
#undef local_6c
#undef local_60
#undef local_5c
#undef local_58
#undef local_54
#undef local_50
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_34
#undef local_30
#undef local_2c
#undef local_28

/* TrainingMenuUpdate @ 0x080a4ff0, 1167 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 15 stack locals placed at their original offsets in a 0x90-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 TrainingMenuUpdate(uint param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  bool bVar4;
  int *piVar5;
  bool bVar6;
  uint uVar7;
  undefined3 extraout_var;
  int *piVar8;
  int *piVar9;
  int iVar10;
  unsigned char ghidra_frame[0x90] __attribute__((aligned(16)));
#define local_8c (*(undefined4 *)(ghidra_frame + 0x4))
#define local_88 (*(undefined4 *)(ghidra_frame + 0x8))
#define local_84 (*(undefined4 *)(ghidra_frame + 0xc))
#define local_80 (*(undefined4 *)(ghidra_frame + 0x10))
#define local_7c (*(int *(*)[4])(ghidra_frame + 0x14))
#define local_6c (*(int (*)[4])(ghidra_frame + 0x24))
#define local_5c (*(undefined4 **)(ghidra_frame + 0x34))
#define local_58 (*(undefined4 **)(ghidra_frame + 0x38))
#define local_54 (*(undefined4 **)(ghidra_frame + 0x3c))
#define local_4c (*(undefined4 *(*)[4])(ghidra_frame + 0x44))
#define local_3c (*(undefined4 *)(ghidra_frame + 0x54))
#define local_38 (*(undefined4 *)(ghidra_frame + 0x58))
#define local_34 (*(undefined4 *)(ghidra_frame + 0x5c))
#define local_30 (*(undefined4 *)(ghidra_frame + 0x60))
#define local_2c (*(undefined4 *)(ghidra_frame + 0x64))
  
  local_5c = &local_3c;
  local_4c[0] = &local_3c;
  local_54 = &local_88;
  local_4c[2] = &local_88;
  local_58 = &local_84;
  local_7c[0] = g + 0x7dbc;
  bVar4 = false;
  local_3c = 3;
  local_38 = 2;
  local_34 = 4;
  local_30 = 4;
  local_2c = 8;
  local_84 = 3;
  local_80 = 8;
  local_88 = 3;
  local_4c[1] = &local_84;
  local_7c[1] = g + 0x7dc1;
  local_6c[0] = 5;
  local_6c[1] = 2;
  local_6c[2] = 1;
  iVar1 = g[0x7dbb];
  local_7c[2] = g + 0x7dc3;
  piVar9 = local_7c[iVar1];
  if (g[0x7309] == 0) {
    return 0;
  }
  if (g[0x33b6] == 1) {
    piVar8 = g + 0x7348;
    iVar10 = g[0x73da];
  }
  else {
    piVar8 = g + 0x733b;
    iVar10 = g[0x73db];
  }
  uVar7 = KBToUInp(piVar8[10]);
  if ((param_1 == uVar7) && (g[0x33ae] == 3)) {
    g[0x7dba] = (uint)(g[0x7dba] == 0);
    return 0;
  }
  if (g[0x7dba] == 0) {
    return 0;
  }
  *piVar9 = iVar1;
  if (iVar1 == 1) {
    piVar9[1] = *(int *)(iVar10 + 0x33f8) + -1;
  }
  else if ((iVar1 < 2) && (iVar1 == 0)) {
    piVar9[1] = *(int *)(iVar10 + 0x2cd8);
    piVar9[2] = *(int *)(iVar10 + 0x2cd4);
    piVar9[4] = *(int *)(iVar10 + 0x2ce4);
    iVar2 = *(int *)(iVar10 + 0x2cdc);
    if ((iVar2 == 0) && (*(int *)(iVar10 + 0x2ce0) == 0)) {
      piVar9[3] = 0;
    }
    else if (iVar2 == 0x32) {
      piVar9[3] = 1;
    }
    else {
      piVar9[3] = (iVar2 != 0x96) + 2;
    }
  }
  local_8c = 0;
  uVar7 = KBToUInp(piVar8[4]);
  piVar5 = g;
  if (param_1 == uVar7) {
    iVar2 = g[0x7db9];
    g[0x7db9] = iVar2 + -1;
    if (iVar2 + -1 < 0) {
      piVar5[0x7db9] = local_4c[iVar1][piVar5[0x7db8]] + -1;
    }
  }
  else {
    uVar7 = KBToUInp(piVar8[2]);
    piVar5 = g;
    if (param_1 != uVar7) {
      uVar7 = KBToUInp(piVar8[1]);
      piVar5 = g;
      if (param_1 == uVar7) {
        iVar2 = g[0x7db8];
        g[0x7db8] = iVar2 + -1;
        if (iVar2 + -1 < 0) {
          piVar5[0x7db8] = local_6c[iVar1] + -1;
        }
      }
      else {
        uVar7 = KBToUInp(piVar8[3]);
        piVar5 = g;
        if (param_1 != uVar7) {
          bVar6 = KBIIs6ButtonOrStart(param_1,(int)piVar8);
          if ((GHIDRA_ZEXT8(bVar6) != 0) || (uVar7 = KBToUInp(1), param_1 == uVar7)) {
            local_8c = 1;
          }
          goto LAB_080a532d;
        }
        iVar2 = g[0x7db8];
        g[0x7db8] = iVar2 + 1;
        if (local_6c[iVar1] <= iVar2 + 1) {
          piVar5[0x7db8] = 0;
        }
      }
      g[0x7db9] = piVar9[g[0x7db8]];
      goto LAB_080a532d;
    }
    iVar2 = g[0x7db9];
    piVar8 = g + 0x7db8;
    puVar3 = local_4c[iVar1];
    g[0x7db9] = iVar2 + 1;
    if (iVar2 + 1 == puVar3[*piVar8]) {
      piVar5[0x7db9] = 0;
    }
  }
  bVar4 = true;
LAB_080a532d:
  piVar9[g[0x7db8]] = g[0x7db9];
  if (iVar1 == 2) {
    *(undefined4 *)(iVar10 + 0x262c) = 0;
  }
  else {
    *(undefined4 *)(iVar10 + 0x262c) = 1;
    *(int *)(iVar10 + 0x2cd0) = iVar1;
  }
  if (iVar1 == 1) {
    *(int *)(iVar10 + 0x33f8) = piVar9[1] + 1;
  }
  else if ((iVar1 < 2) && (iVar1 == 0)) {
    *(int *)(iVar10 + 0x2cd8) = piVar9[1];
    *(int *)(iVar10 + 0x2cd4) = piVar9[2];
    *(int *)(iVar10 + 0x2ce4) = piVar9[4];
    iVar1 = piVar9[3];
    if (iVar1 == 1) {
      *(undefined4 *)(iVar10 + 0x2cdc) = 0x32;
      *(undefined4 *)(iVar10 + 0x2ce0) = 0;
    }
    else if (iVar1 < 2) {
      if (iVar1 == 0) {
        *(undefined4 *)(iVar10 + 0x2ce0) = 0;
        *(undefined4 *)(iVar10 + 0x2cdc) = 0;
      }
    }
    else if (iVar1 == 2) {
      *(undefined4 *)(iVar10 + 0x2cdc) = 0x96;
      *(undefined4 *)(iVar10 + 0x2ce0) = 100;
    }
    else if (iVar1 == 3) {
      *(undefined4 *)(iVar10 + 0x2cdc) = 0;
      *(undefined4 *)(iVar10 + 0x2ce0) = 0x118;
    }
  }
  g[0x7dbb] = *piVar9;
  if (bVar4) {
    piVar9 = (int *)(iVar10 + 0x2c4);
    uVar7 = 1;
    do {
      if (*piVar9 != 0) {
        KBIStuffBuf(iVar10 + 0x248,uVar7 | 0x10);
      }
      uVar7 = uVar7 + 1;
      piVar9 = piVar9 + 1;
    } while ((int)uVar7 < 0xc);
    return local_8c;
  }
  return local_8c;
}
#undef local_8c
#undef local_88
#undef local_84
#undef local_80
#undef local_7c
#undef local_6c
#undef local_5c
#undef local_58
#undef local_54
#undef local_4c
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c

/* TrainingMenuReset @ 0x080a5480, 45 bytes */
uint TrainingMenuReset(void)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = g;
  iVar1 = g[0x33ae];
  g[0x7db9] = 0;
  piVar2[0x7db8] = 0;
  piVar2[0x7dba] = (uint)(iVar1 == 3);
  return (uint)(iVar1 == 3);
}

/* TrainingMenuDraw @ 0x080a54b0, 1716 bytes
 * FIXUP: frame emulation: 63 stack locals placed at their original offsets in a 0x1f0-byte frame (a local's address escapes, see apply_frame_emulation) */
void TrainingMenuDraw(void)

{
  int *piVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  uint uVar5;
  void **ppvVar6;
  int iVar7;
  undefined4 *puVar8;
  char *pcVar9;
  int *piVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  unsigned char ghidra_frame[0x1f0] __attribute__((aligned(16)));
#define local_1f0 (*(byte *)(ghidra_frame + 0x0))
#define local_1e0 (*(int *)(ghidra_frame + 0x10))
#define local_1dc (*(int *)(ghidra_frame + 0x14))
#define local_1b8 (*(char **)(ghidra_frame + 0x38))
#define local_1b4 (*(undefined4 *)(ghidra_frame + 0x3c))
#define local_1b0 (*(char ***)(ghidra_frame + 0x40))
#define local_1ac (*(char **)(ghidra_frame + 0x44))
#define local_1a8 (*(char **)(ghidra_frame + 0x48))
#define local_1a4 (*(undefined4 *)(ghidra_frame + 0x4c))
#define local_1a0 (*(undefined4 *)(ghidra_frame + 0x50))
#define local_19c (*(char ***)(ghidra_frame + 0x54))
#define local_198 (*(undefined4 **)(ghidra_frame + 0x58))
#define local_194 (*(undefined1 **)(ghidra_frame + 0x5c))
#define local_190 (*(undefined **)(ghidra_frame + 0x60))
#define local_18c (*(int *(*)[4])(ghidra_frame + 0x64))
#define local_17c (*(int (*)[4])(ghidra_frame + 0x74))
#define local_16c (*(char ***)(ghidra_frame + 0x84))
#define local_168 (*(char ***)(ghidra_frame + 0x88))
#define local_164 (*(char ***)(ghidra_frame + 0x8c))
#define local_15c (*(char **(*)[4])(ghidra_frame + 0x94))
#define local_14c (*(undefined4 **)(ghidra_frame + 0xa4))
#define local_148 (*(undefined4 **)(ghidra_frame + 0xa8))
#define local_144 (*(undefined4 **)(ghidra_frame + 0xac))
#define local_13c (*(undefined4 **)(ghidra_frame + 0xb4))
#define local_138 (*(undefined4 **)(ghidra_frame + 0xb8))
#define local_134 (*(undefined4 **)(ghidra_frame + 0xbc))
#define local_12c (*(char ****)(ghidra_frame + 0xc4))
#define local_128 (*(char ****)(ghidra_frame + 0xc8))
#define local_124 (*(char ****)(ghidra_frame + 0xcc))
#define local_11c (*(char ***(*)[4])(ghidra_frame + 0xd4))
#define local_10c (*(undefined4 (*)[8])(ghidra_frame + 0xe4))
#define local_ec (*(char **)(ghidra_frame + 0x104))
#define local_e8 (*(char **)(ghidra_frame + 0x108))
#define local_e4 (*(char **)(ghidra_frame + 0x10c))
#define local_e0 (*(char **)(ghidra_frame + 0x110))
#define local_dc (*(char **)(ghidra_frame + 0x114))
#define local_cc (*(undefined4 *)(ghidra_frame + 0x124))
#define local_c8 (*(undefined4 *)(ghidra_frame + 0x128))
#define local_c4 (*(undefined4 *)(ghidra_frame + 0x12c))
#define local_c0 (*(undefined4 *)(ghidra_frame + 0x130))
#define local_bc (*(undefined4 *)(ghidra_frame + 0x134))
#define local_ac (*(char ***)(ghidra_frame + 0x144))
#define local_a8 (*(undefined1 ***)(ghidra_frame + 0x148))
#define local_a4 (*(char ***)(ghidra_frame + 0x14c))
#define local_a0 (*(undefined ***)(ghidra_frame + 0x150))
#define local_9c (*(undefined4 **)(ghidra_frame + 0x154))
#define local_8c (*(char ***)(ghidra_frame + 0x164))
#define local_88 (*(undefined1 ***)(ghidra_frame + 0x168))
#define local_84 (*(char ***)(ghidra_frame + 0x16c))
#define local_80 (*(undefined ***)(ghidra_frame + 0x170))
#define local_7c (*(undefined4 **)(ghidra_frame + 0x174))
#define local_6c (*(undefined4 (*)[8])(ghidra_frame + 0x184))
#define local_4c (*(undefined **)(ghidra_frame + 0x1a4))
#define local_48 (*(char **)(ghidra_frame + 0x1a8))
#define local_44 (*(char **)(ghidra_frame + 0x1ac))
#define local_40 (*(undefined **)(ghidra_frame + 0x1b0))
#define local_3c (*(char **)(ghidra_frame + 0x1b4))
#define local_38 (*(char **)(ghidra_frame + 0x1b8))
#define local_34 (*(undefined **)(ghidra_frame + 0x1bc))
#define local_30 (*(undefined **)(ghidra_frame + 0x1c0))
#define local_2c (*(char **)(ghidra_frame + 0x1c4))
#define local_28 (*(char **)(ghidra_frame + 0x1c8))
#define local_24 (*(char **)(ghidra_frame + 0x1cc))
  
  local_2c = "Cooperative";
  local_28 = "AI";
  local_24 = "Manual";
  local_194 = &DAT_08279809;
  local_190 = &DAT_0827982e;
  local_3c = "Stand";
  local_38 = "Crouch";
  local_34 = &DAT_0827993b;
  local_30 = &DAT_08279939;
  local_4c = &DAT_08279940;
  local_48 = "Close";
  local_44 = "Medium";
  local_40 = &DAT_0827994a;
  local_1b0 = &local_2c;
  ppvVar6 = &PTR_DAT_08287a98;
  puVar8 = local_6c;
  for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar8 = *ppvVar6;
    ppvVar6 = ppvVar6 + 1;
    puVar8 = puVar8 + 1;
  }
  local_ac = local_1b0;
  local_a8 = &local_194;
  local_a4 = &local_3c;
  local_a0 = &local_4c;
  local_9c = local_6c;
  local_8c = local_1b0;
  local_88 = &local_194;
  local_84 = &local_3c;
  local_80 = &local_4c;
  local_7c = local_6c;
  local_198 = local_10c;
  local_cc = 3;
  local_c8 = 2;
  local_c4 = 4;
  local_c0 = 4;
  local_bc = 8;
  local_ec = "Dummy control";
  local_e8 = "Guard mode";
  local_e4 = "Dummy mode";
  local_e0 = "Distance";
  local_dc = "Button jam";
  ppvVar6 = &PTR_s_1_08283cdb_0x13_08287ab8;
  puVar8 = local_10c;
  for (iVar4 = 8; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar8 = *ppvVar6;
    ppvVar6 = ppvVar6 + 1;
    puVar8 = puVar8 + 1;
  }
  local_1b8 = "Dummy control";
  local_1ac = "Dummy control";
  local_12c = &local_8c;
  local_124 = &local_1b0;
  local_11c[0] = &local_8c;
  local_11c[2] = &local_1b0;
  local_128 = &local_19c;
  local_11c[1] = &local_19c;
  local_14c = &local_cc;
  local_148 = &local_1a4;
  local_144 = &local_1b4;
  local_13c = &local_cc;
  local_1a4 = 3;
  local_1a0 = 8;
  local_1a8 = "AI Level";
  local_1b4 = 3;
  local_138 = &local_1a4;
  local_134 = &local_1b4;
  local_16c = &local_ec;
  local_168 = &local_1ac;
  local_15c[0] = &local_ec;
  local_15c[1] = &local_1ac;
  local_164 = &local_1b8;
  local_15c[2] = &local_1b8;
  local_17c[0] = 5;
  local_17c[1] = 2;
  local_17c[2] = 1;
  iVar4 = g[0x7dbb];
  local_18c[0] = g + 0x7dbc;
  local_18c[1] = g + 0x7dc1;
  local_18c[2] = g + 0x7dc3;
  piVar1 = local_18c[iVar4];
  local_19c = local_1b0;
  W_Box(0x4f,0x1d,0xf1,0x97,
        10 << ((byte)_rgb_r_shift_16 & 0x1f) | 0x14 << ((byte)_rgb_g_shift_16 & 0x1f) |
        0x10 << ((byte)_rgb_b_shift_16 & 0x1f));
  W_Box(0x50,0x1e,0xf0,0x96,
        0x18 << ((byte)_rgb_r_shift_16 & 0x1f) | 0x30 << ((byte)_rgb_g_shift_16 & 0x1f) |
        0x1e << ((byte)_rgb_b_shift_16 & 0x1f));
  W_BoxFillTransAdd16_B50(0x50,0x1e,0xf0,0x96,3 << ((byte)_rgb_b_shift_16 & 0x1f));
  bVar2 = (byte)_rgb_r_shift_16;
  bVar3 = (byte)_rgb_g_shift_16;
  uVar5 = 0x1f << (bVar2 & 0x1f) | 0x3f << (bVar3 & 0x1f);
  local_1f0 = (byte)_rgb_b_shift_16;
  iVar7 = 0;
  V_FontDrawCenter("Training Menu",(int *)g[0x413b],0xa0,0x29,0);
  V_FontDrawCenter("Training Menu",(int *)g[0x413b],0x9f,0x28,
                   0x1f << ((byte)_rgb_r_shift_16 & 0x1f) | 0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
                   0x1f << ((byte)_rgb_b_shift_16 & 0x1f));
  *piVar1 = iVar4;
  if (0 < local_17c[iVar4]) {
    local_1dc = 0x3c;
    local_1e0 = 0x3d;
    do {
      V_FontDraw(local_15c[iVar4][iVar7],(int *)g[0x413b],0x5b,local_1e0,0);
      if (piVar1[iVar7] == -1) {
        iVar11 = 0x5a;
        piVar10 = (int *)g[0x413b];
        pcVar9 = local_15c[iVar4][iVar7];
        iVar12 = local_1e0;
        uVar13 = 0xc << (bVar2 & 0x1f) | 0x19 << (bVar3 & 0x1f) | 0xc << (local_1f0 & 0x1f);
      }
      else {
        V_FontDraw(local_11c[iVar4][iVar7][piVar1[iVar7]],(int *)g[0x413b],0xb5,local_1e0,0);
        iVar12 = local_1dc;
        if (g[0x7db8] == iVar7) {
          V_FontDraw(local_15c[iVar4][iVar7],(int *)g[0x413b],0x5a,local_1dc,
                     0x1f << (local_1f0 & 0x1f) | uVar5);
          iVar11 = 0xb4;
          piVar10 = (int *)g[0x413b];
          pcVar9 = local_11c[iVar4][iVar7][piVar1[iVar7]];
          uVar13 = 0x19 << (local_1f0 & 0x1f) | uVar5;
        }
        else {
          V_FontDraw(local_15c[iVar4][iVar7],(int *)g[0x413b],0x5a,local_1dc,
                     0x10 << ((byte)_rgb_r_shift_16 & 0x1f) | 0x20 << ((byte)_rgb_g_shift_16 & 0x1f)
                     | 0x10 << ((byte)_rgb_b_shift_16 & 0x1f));
          iVar11 = 0xb4;
          piVar10 = (int *)g[0x413b];
          pcVar9 = local_11c[iVar4][iVar7][piVar1[iVar7]];
          uVar13 = uVar5;
        }
      }
      V_FontDraw(pcVar9,piVar10,iVar11,iVar12,uVar13);
      local_1dc = local_1dc + 0x14;
      local_1e0 = local_1e0 + 0x14;
      iVar7 = iVar7 + 1;
    } while (iVar7 < local_17c[iVar4]);
  }
  return;
}
#undef local_1f0
#undef local_1e0
#undef local_1dc
#undef local_1b8
#undef local_1b4
#undef local_1b0
#undef local_1ac
#undef local_1a8
#undef local_1a4
#undef local_1a0
#undef local_19c
#undef local_198
#undef local_194
#undef local_190
#undef local_18c
#undef local_17c
#undef local_16c
#undef local_168
#undef local_164
#undef local_15c
#undef local_14c
#undef local_148
#undef local_144
#undef local_13c
#undef local_138
#undef local_134
#undef local_12c
#undef local_128
#undef local_124
#undef local_11c
#undef local_10c
#undef local_ec
#undef local_e8
#undef local_e4
#undef local_e0
#undef local_dc
#undef local_cc
#undef local_c8
#undef local_c4
#undef local_c0
#undef local_bc
#undef local_ac
#undef local_a8
#undef local_a4
#undef local_a0
#undef local_9c
#undef local_8c
#undef local_88
#undef local_84
#undef local_80
#undef local_7c
#undef local_6c
#undef local_4c
#undef local_48
#undef local_44
#undef local_40
#undef local_3c
#undef local_38
#undef local_34
#undef local_30
#undef local_2c
#undef local_28
#undef local_24

/* InfoTextDraw @ 0x080a5b70, 507 bytes
 * FIXUP: 3 data addresses written as literals replaced by data-image references
 * FIXUP: frame emulation: 6 stack locals placed at their original offsets in a 0x240-byte frame (a local's address escapes, see apply_frame_emulation) */
void InfoTextDraw(char *param_1,int param_2,int param_3)

{
  char *pcVar1;
  int *piVar2;
  int *piVar3;
  char cVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined *puVar10;
  undefined4 uVar11;
  unsigned char ghidra_frame[0x240] __attribute__((aligned(16)));
#define local_238 (*(uint *)(ghidra_frame + 0x8))
#define local_22c (*(int **)(ghidra_frame + 0x14))
#define local_228 (*(undefined4 *)(ghidra_frame + 0x18))
#define local_224 (*(int *)(ghidra_frame + 0x1c))
#define local_220 (*(int *)(ghidra_frame + 0x20))
#define local_21c (*(char (*)[524])(ghidra_frame + 0x24))
  
  iVar9 = 0;
  piVar2 = (int *)g[0x413b];
  piVar3 = (int *)g[0x413a];
  local_238 = makecol(0xff,0xff,0xff);
  cVar4 = *param_1;
  local_22c = piVar2;
  do {
    if (cVar4 == '\0') {
      return;
    }
    iVar8 = 0;
    while (cVar4 == '[') {
      pcVar1 = param_1 + iVar9 + 1;
      iVar6 = strmatchlen((int)pcVar1,(int)&DAT_0827999d,4);
      if (iVar6 == 0) {
        iVar6 = strmatchlen((int)pcVar1,(int)&DAT_082799a2,6);
        if (iVar6 == 0) {
          uVar11 = 3;
          puVar10 = &DAT_082799a9;
          iVar7 = strmatchlen((int)pcVar1,(int)&DAT_082799a9,3);
          if (iVar7 == 0) {
            cVar4 = *pcVar1;
            iVar9 = iVar9 + 1;
          }
          else {
            iVar9 = iVar9 + 5;
            sscanf(param_1 + iVar9,"%i,%i,%i",&local_228,&local_224,&local_220,puVar10,uVar11,iVar6)
            ;
            local_238 = makecol(local_228,local_224,local_220);
            cVar4 = param_1[iVar9];
            cVar5 = '\0';
            if (cVar4 != '\0') {
              if (cVar4 == ']') {
                cVar5 = ']';
              }
              else {
                do {
                  iVar9 = iVar9 + 1;
                  cVar5 = param_1[iVar9];
                  if (cVar5 == '\0') break;
                } while (cVar5 != ']');
              }
            }
            cVar4 = '\0';
            if (cVar5 != '\0') {
              cVar4 = param_1[iVar9 + 1];
              iVar9 = iVar9 + 1;
            }
          }
        }
        else {
          cVar4 = param_1[iVar9 + 7];
          iVar9 = iVar9 + 7;
          local_22c = piVar3;
        }
      }
      else {
        cVar4 = param_1[iVar9 + 5];
        iVar9 = iVar9 + 5;
        local_22c = piVar2;
      }
    }
    if ((cVar4 != '\0') && (cVar4 != '\n')) {
      while( true ) {
        iVar9 = iVar9 + 1;
        local_21c[iVar8] = cVar4;
        iVar8 = iVar8 + 1;
        cVar4 = param_1[iVar9];
        if (cVar4 == '\0') break;
        if ((cVar4 == '\n') || (0x1fd < iVar8)) break;
      }
    }
    local_21c[iVar8] = '\0';
    if (param_1[iVar9] == '\n') {
      param_3 = param_3 + local_22c[3];
    }
    V_FontDraw(local_21c,local_22c,param_2,param_3,local_238);
    cVar4 = param_1[iVar9];
    if (cVar4 == '\n') {
      iVar9 = iVar9 + 1;
      param_3 = param_3 + 1;
      cVar4 = param_1[iVar9];
    }
  } while( true );
}
#undef local_238
#undef local_22c
#undef local_228
#undef local_224
#undef local_220
#undef local_21c

