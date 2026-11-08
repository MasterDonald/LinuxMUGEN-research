/*
 * main.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0809c470-0x0809dc47, 10 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* _mangled_main @ 0x0809c470, 636 bytes
 * REVIEW: pid-removed-blocks; pid-StackY; calls-missing-in-pid:FindCharacters,InitSelectScreenMatrix,strcat
 * FIXUP: hand-written override (see overrides/) */
/* OVERRIDE: written by hand from the assembly at 0x0809c470-0x0809c6ec.
 * Reason: the by-value copy of the 0x32c-byte options block (rep movsl) breaks
 * Ghidra's stack tracking; the decompiler dropped GameInit's arguments and
 * removed the "mode == 1" branch as unreachable.
 * Stack layout (D0 = esp after "sub $0x344"): mode at D0+0x10 (zeroed before
 * ParseCmdLine), opts at D0+0x14. After GameInit, esp = D0+4 (GCC 2.96
 * alignment rebalance), so 0xc(%esp) is mode and 0x300(%esp) is opts+0x2ec.
 * Verified: argument order of every call, string addresses 0x8276f0b
 * "scene", 0x8279230 "Debug", 0x8279280, 0x82792c0. */
int _mangled_main(int argc, char **argv)
{
  int mode;
  MugenCmdLine opts;
  int *win;

  mode = 0;
  ParseCmdLine(&opts, argc, argv);
  GameInit(opts, &mode);                       /* 0x809c4b2 */
  if (g[0x104e0 / 4] != 0) {
    V_SetBuf((int *)g[0x104e0 / 4], 0);
    W_Cls(0);
  }
  V_SetBuf((int *)g[0x104d8 / 4], 0);
  W_Cls(0);
  W_Define(0, 0, V_Width - 1, V_Height - 1);
  TimerSetFPSDelay(0x1e);
  TimerSetTicks(0);
  TimerSetSyncFPS(0x3c);
  if (((char *)&opts)[0x2ec] != '\0') {        /* storyboard given on the command line */
    PlayCutscene((char *)&opts + 0x2ec, "scene");
  }
  else {
    install_mouse();
    EB_GUIInit(g[0x104d8 / 4]);
    win = EB_GUINewWindow("Debug", 10, 0x32, 300, (int *)0x3c);
    g[0x20b5c / 4] = (int)win;
    EB_GUISetWinAttr(g[0x20b5c / 4], 1);
    *(undefined4 *)(g[0x20b5c / 4] + 0x20) = 0;
    ClipboardFree(*(undefined4 **)(g[0x20b5c / 4] + 0x30));
    *(int *)(g[0x20b5c / 4] + 0x30) = g[0x20744 / 4];
    PlayCutscene((char *)g + 0x6d44, "scene");  /* logo/intro storyboard */
    if (CharInfoInit() == 0) {
      ErrorExit();
    }
    if (mode == 1) {                           /* 0x809c615: normal start, select screen */
      if (InitSelectScreenMatrix((char *)g + 0x5380) == 0) {
        strcat((char *)g + 0x20748, "\nCannot load char select data in ");
        strcat((char *)g + 0x20748, (char *)g + 0x5380);
        ErrorExit();
      }
      if (FindCharacters() == 0) {
        strcat((char *)g + 0x20748, "\nError finding characters/stages in ");
        strcat((char *)g + 0x20748, (char *)g + 0x5380);
        ErrorExit();
      }
    }
    else {
      QuickVSSetup(&opts);                     /* quick versus from the command line */
    }
    MainLoop(mode);
  }
  EB_GUIDeInit();
  GameDeInit(mode);
  return 0;
}

/* QuickVSSetup @ 0x0809c6f0, 1134 bytes
 * REVIEW: pid-unaff_
 * FIXUP: 1 data addresses written as literals replaced by data-image references
 * FIXUP: frame emulation: 5 stack locals placed at their original offsets in a 0x3030-byte frame (a local's address escapes, see apply_frame_emulation) */
void QuickVSSetup(MugenCmdLine *opts)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  undefined4 extraout_ECX;
  int iVar8;
  int *piVar9;
  MugenCmdLine *__s2;
  int *piVar10;
  int unaff_EBP;
  int iVar11;
  unsigned char ghidra_frame[0x3030] __attribute__((aligned(16)));
#define local_3030 (*(MugenCmdLine **)(ghidra_frame + 0x0))
#define local_302c (*(uint *)(ghidra_frame + 0x4))
#define local_301c (*(char (*)[4096])(ghidra_frame + 0x14))
#define local_201c (*(char (*)[4096])(ghidra_frame + 0x1014))
#define local_101c (*(char (*)[4108])(ghidra_frame + 0x2014))
  
  piVar9 = g;
  g[0x3a60] = 1;
  piVar9[0x33b9] = 1;
  piVar9[0x3a64] = 0;
  piVar9[0x33bd] = 0;
  piVar9[0x3a62] = 0;
  piVar9[0x33bb] = 0;
  local_302c = 0;
  local_3030 = opts;
  do {
    iVar2 = (int)local_302c / 2;
    iVar7 = (int)local_302c % 2;
    piVar10 = piVar9;
    if ((char)local_3030->mode != '\0') {
      iVar11 = 0;
      piVar9[iVar7 * 0x6a7 + iVar2 * 5 + 0x33be] = local_302c + 1;
      piVar9[iVar7 * 0x6a7 + iVar2 * 5 + 0x33c1] = iVar7;
      unaff_EBP = 0;
      __s2 = opts;
      if (0 < (int)local_302c) {
        do {
          iVar3 = strcmp((char *)local_3030,(char *)__s2);
          if (iVar3 == 0) {
            unaff_EBP = 1;
            piVar9[iVar7 * 0x6a7 + iVar2 * 5 + 0x33bf] =
                 g[(iVar11 / 2) * 5 + (iVar11 % 2) * 0x6a7 + 0x33bf];
            break;
          }
          iVar11 = iVar11 + 1;
          __s2 = (MugenCmdLine *)(__s2->rest + 0x3c);
        } while (iVar11 < (int)local_302c);
      }
      if (unaff_EBP == 0) {
        iVar11 = g[0x14b5];
        iVar3 = g[0x14b4] + iVar11 * 0x702c;
        piVar9[iVar7 * 0x6a7 + iVar2 * 5 + 0x33bf] = iVar11;
        uVar4 = splitdirfile((char *)local_3030,local_301c,local_201c);
        if (local_301c[0] == '\0') {
          sprintf(local_301c,"chars/%s/",local_3030,uVar4);
          sprintf(local_201c,"%s.def",local_3030);
        }
        else {
          iVar6 = strmatchlen((int)local_301c,(int)&DAT_08279236,5);
          if (iVar6 == 0) {
            sprintf(local_101c,"chars/%s",local_301c,local_201c);
            strcpy(local_301c,local_101c);
          }
        }
        sprintf(local_101c,"%s%s",local_301c,local_201c);
        puVar5 = TPReadFile(local_101c);
        if (puVar5 == (undefined4 *)0x0) {
          sprintf((char *)(g + 0x81d2),"Cannot find character: %s",local_101c,0);
          ErrorExit();
        }
        TPGroupSeek((int)puVar5,"Info");
        iVar8 = 3;
        iVar6 = 4;
        do {
          *(int *)(iVar3 + 0x5010 + iVar6 * 4) = iVar6;
          iVar6 = iVar6 + -1;
          iVar8 = iVar8 + -1;
        } while (-1 < iVar8);
        TPScanf((int)puVar5,"pal.defaults","%i,%i,%i,%i",iVar3 + 0x5014,iVar3 + 0x5018,
                iVar3 + 0x501c,iVar3 + 0x5020,extraout_ECX);
        TPFree(puVar5);
        sprintf((char *)(iVar11 * 0x702c + g[0x14b4] + 0x200a),local_301c);
        sprintf((char *)(iVar11 * 0x702c + g[0x14b4] + 0x100b),local_201c);
        unaff_EBP = g[0x14b5] + 1;
        g[0x14b5] = unaff_EBP;
      }
      piVar10 = g;
      piVar9[iVar7 * 0x6a7 + iVar2 * 5 + 0x33c0] =
           *(int *)(local_302c * 4 + 0x5014 + iVar11 * 0x702c + g[0x14b4]) + -1;
      if (piVar10[local_302c + 0x7991] != -1) {
        piVar9[iVar7 * 0x6a7 + iVar2 * 5 + 0x33c0] = piVar10[local_302c + 0x7991];
      }
      iVar2 = piVar9[iVar7 * 0x6a7 + 0x33bd];
      piVar9[iVar7 * 0x6a7 + 0x33bd] = iVar2 + 1;
      piVar10 = g;
      if (1 < iVar2 + 1) {
        piVar9[iVar7 * 0x6a7 + 0x33bb] = 1;
        piVar9[iVar7 * 0x6a7 + 0x33bc] = 1;
        piVar10[0x33ae] = 0;
      }
      piVar10 = g;
      piVar9[iVar7 * 0x6a7 + 0x33ba] = piVar9[iVar7 * 0x6a7 + 0x33ba] + 1;
      piVar10[local_302c + 0x33af] = local_302c & 1;
      piVar10[local_302c + 0x741a] = 1;
    }
    local_302c = local_302c + 1;
    local_3030 = (MugenCmdLine *)(local_3030->rest + 0x3c);
    piVar9 = piVar10;
    if (3 < (int)local_302c) {
      piVar9 = piVar10 + 0x33bb;
      piVar10 = piVar10 + 0x4106;
      for (iVar2 = 0x17; iVar2 != 0; iVar2 = iVar2 + -1) {
        *piVar10 = *piVar9;
        piVar9 = piVar9 + 1;
        piVar10 = piVar10 + 1;
      }
      piVar9 = g + 0x3a62;
      piVar10 = g + 0x411d;
      for (iVar2 = 0x17; piVar1 = g, iVar2 != 0; iVar2 = iVar2 + -1) {
        *piVar10 = *piVar9;
        piVar9 = piVar9 + 1;
        piVar10 = piVar10 + 1;
      }
      g[0x4e75] = *(int *)(opts->rest + 0x290);
      if (opts->rest[0xfc] != 0) {
        sprintf((char *)(piVar1 + 0x805),"stages/%s.def",opts->rest + 0xfc,unaff_EBP);
      }
      return;
    }
  } while( true );
}
#undef local_3030
#undef local_302c
#undef local_301c
#undef local_201c
#undef local_101c

/* MainLoop @ 0x0809cb60, 1469 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x1020-byte frame (a local's address escapes, see apply_frame_emulation) */
void MainLoop(int param_1)

{
  char *__src;
  bool bVar1;
  int *piVar2;
  bool bVar3;
  int iVar4;
  long lVar5;
  undefined3 extraout_var;
  uint uVar6;
  int *piVar7;
  unsigned char ghidra_frame[0x1020] __attribute__((aligned(16)));
#define local_101c (*(char (*)[4108])(ghidra_frame + 0x4))
  
LAB_0809d0ad:
  if (((param_1 != 0) && ((char)g[0x1f51] != '\0')) && (g[0x2351] == 0)) {
    IntroScreen();
    g[0x2351] = 1;
  }
LAB_0809d0dd:
  GameResetPersistVars();
  if (param_1 == 0) {
    g[0x33b5] = 1;
  }
  else {
    ModeSelect();
    if (g[0x33b5] == 10) {
      BGMFree(g + 0x6efa);
      return;
    }
  }
LAB_0809cb85:
  GameResetPersistVars();
  piVar7 = g;
  g[0x7543] = 0;
  if ((param_1 == 0) || ((piVar7[0x74e8] != 0 && (piVar7[0x74eb] == 0)))) {
    if (g[0x74e8] != 0) {
      DemoFightSetup();
      BGMFree(g + 0x6efa);
    }
  }
  else {
    iVar4 = CharacterSelectScreen(piVar7[0x33b5],piVar7[0x33b6]);
    if (iVar4 == 0) goto LAB_0809d0dd;
    if ((g[0x33b3] != 0) && (ArcadeListBuild(), g[0x14d0] != 0)) {
      PrecacheRequestCurArcadeTeam();
      PrecacheStart();
    }
    if (g[0x33b4] != 0) {
      SurvivalBuildRandomTeam(g + (2 - g[0x33b4]) * 0x6a7 + 0x33b8,2 - g[0x33b4],1);
    }
  }
  if (param_1 == 0) {
    if ((char)g[0x805] != '\0') goto LAB_0809cd09;
    piVar7 = g + 0x7dc4;
  }
  else {
    if ((char)g[0x805] != '\0') goto LAB_0809cd09;
    lVar5 = random();
    piVar7 = (int *)(g[0x14b4] + 0x3009 + (lVar5 % g[0x14b5]) * 0x702c);
  }
  strcpy((char *)(g + 0x805),(char *)piVar7);
LAB_0809cd09:
  TrainingMenuReset();
  do {
    piVar2 = g;
    piVar7 = g + 0x7543;
    iVar4 = g[0x7544];
    *(undefined1 *)((int)g + 0x3013) = 0;
    piVar2[0x7543] = *piVar7 + 1;
    piVar2[0x7544] = iVar4 + 1;
    bVar1 = false;
    if ((g[0x33b3] != 0) && (iVar4 = ArcadeListGetCurrent(), iVar4 != -1)) {
      iVar4 = g[0x14b4] + iVar4 * 0x702c;
      strcpy((char *)(g + 0x805),(char *)(iVar4 + 0x3009));
      strcpy((char *)((int)g + 0x3013),(char *)(iVar4 + 0x4008));
    }
    if (((char)g[0x805] == '\0') ||
       (iVar4 = _alemu_stricmp((char *)(g + 0x805),"random"), iVar4 == 0)) {
      if (g[0x33ad] < 1) {
        piVar7 = g + 0x7dc4;
      }
      else {
        lVar5 = random();
        piVar7 = (int *)(g[0x33ac] + (lVar5 % g[0x33ad]) * 0x1054);
      }
      strcpy((char *)(g + 0x805),(char *)piVar7);
    }
    if ((g[0x33b3] != 0) && (g[0x7543] == 1)) {
      TimerSetSyncFPS(0x3c);
      if (g[g[0x33b3] * 0x6a7 + 0x2d18] != -1) {
        iVar4 = g[g[0x33b3] * 0x6a7 + 0x2d18] * 0x702c;
        __src = (char *)(iVar4 + g[0x14b4] + 0x5028);
        sprintf(local_101c,"%s/%s",iVar4 + g[0x14b4] + 0x200a,__src);
        bVar3 = fileexist(local_101c);
        if (GHIDRA_ZEXT8(bVar3) == 0) {
          strcpy(local_101c,__src);
        }
        PlayCutscene(local_101c,"scene");
      }
    }
    while( true ) {
      if ((param_1 != 0) &&
         (((g[0x74e8] == 0 || (g[0x74ec] != 0)) && (uVar6 = VersusScreen(), uVar6 == 0))))
      goto LAB_0809d066;
      iVar4 = GamePlay();
      if (iVar4 == 0) {
        ErrorExit();
      }
      if (g[0x4134] == 0) break;
      GameResetPersistVars();
      iVar4 = CharacterSelectScreen(g[0x33b5],g[0x33b6]);
      if (iVar4 == 0) {
        g[0x4134] = 0;
        goto LAB_0809d0dd;
      }
      g[0x4134] = 0;
      iVar4 = ArcadeListGetCurrent();
      if (iVar4 != -1) {
        iVar4 = g[0x14b4] + iVar4 * 0x702c;
        strcpy((char *)(g + 0x805),(char *)(iVar4 + 0x3009));
        strcpy((char *)((int)g + 0x3013),(char *)(iVar4 + 0x4008));
      }
      g[0x7544] = g[0x7544] + 1;
    }
    if (g[0x33b3] != 0) {
      g[0x14bb] = g[0x14bb] + 1;
      iVar4 = ArcadeListGetCurSize();
      g[0x14ba] = g[0x14ba] + iVar4;
      iVar4 = ArcadeListEnemiesLeft();
      if (iVar4 == 0) break;
      bVar1 = true;
    }
    if ((!bVar1) || (g[0x4135] != 0)) break;
  } while( true );
LAB_0809d066:
  iVar4 = PrecacheIsRunning();
  if (iVar4 != 0) {
    PrecacheRequestCancel();
    PrecacheFinish();
  }
  if (param_1 == 0) {
    return;
  }
  CharStopUsingPalAll();
  if (((g[0x33b3] != 0) || (g[0x74e8] != 0)) || (g[0x33b4] != 0)) goto LAB_0809d0ad;
  goto LAB_0809cb85;
}
#undef local_101c

/* GamePlay @ 0x0809d120, 1282 bytes
 * FIXUP: 2 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 6 stack locals placed at their original offsets in a 0x4030-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 GamePlay(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  bool bVar5;
  int iVar6;
  int *piVar7;
  undefined4 uVar8;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  unsigned char ghidra_frame[0x4030] __attribute__((aligned(16)));
#define local_4024 (*(int *)(ghidra_frame + 0xc))
#define local_4020 (*(int *)(ghidra_frame + 0x10))
#define local_401c (*(char (*)[4096])(ghidra_frame + 0x14))
#define local_301c (*(char (*)[4096])(ghidra_frame + 0x1014))
#define local_201c (*(char (*)[4096])(ghidra_frame + 0x2014))
#define local_101c (*(int (*)[1027])(ghidra_frame + 0x3014))
  
  memset(local_201c,0,0xfff);
  memset(local_301c,0,0xfff);
  memset(local_401c,0,0xfff);
  piVar7 = g + 0x757c;
  g[0x52bd] = 1;
  if (*piVar7 != 0) {
    GameUnloadSystemSprSnd();
  }
  LogPreMatch();
  g[0x81c9] = Ticks;
  iVar6 = GameLoadStage();
  if ((iVar6 == 0) || (iVar6 = GameStgInitFightData(), piVar7 = g, iVar6 == 0)) {
LAB_0809d30d:
    uVar8 = 0;
  }
  else {
    g[0x81c9] = Ticks - g[0x81c9];
    GameSetVol(piVar7[0x6ef5],piVar7[0x6ef7]);
    BGMStart(g + 0x10aa);
    while( true ) {
      iVar6 = 1;
      KBBufferClear();
      PadPoll();
      PadBufClear();
      UInpRefreshFlags();
      UInpBufClear();
      piVar7 = g + 0x33b8;
      do {
        *piVar7 = 0;
        piVar7 = piVar7 + 0x6a7;
        iVar6 = iVar6 + -1;
      } while (-1 < iVar6);
      local_4020 = 0xcee0;
      local_4024 = 0;
      iVar10 = 0x10410;
      iVar6 = 1;
      do {
        iVar2 = iVar10 + 8;
        iVar10 = iVar10 + 0x5c;
        iVar3 = local_4024 + *(int *)(local_4020 + (int)g) * 0x5c;
        local_4024 = local_4024 + 0x1a9c;
        puVar11 = (undefined4 *)(iVar3 + 0xceec + (int)g);
        puVar12 = (undefined4 *)(iVar2 + (int)g);
        for (iVar9 = 0x17; iVar9 != 0; iVar9 = iVar9 + -1) {
          *puVar12 = *puVar11;
          puVar11 = puVar11 + 1;
          puVar12 = puVar12 + 1;
        }
        local_4020 = local_4020 + 0x1a9c;
        iVar6 = iVar6 + -1;
      } while (-1 < iVar6);
      GameMatchReset();
      iVar6 = g[0x79a1] * 5 + g[0x756f];
      if (iVar6 < 10) {
        iVar6 = 10;
      }
      TimerSetSyncFPS(iVar6);
      CameraMoveAbs((float)g[0x1080],(float)g[0x1081]);
      piVar7 = g;
      g[0x74e0] = 1;
      piVar7[0x74df] = 1;
      iVar6 = GameLoop(4);
      if (iVar6 == 0) goto LAB_0809d30d;
      PalGrpResetPalette();
      SndIDStop(-1);
      LogMatch();
      piVar7 = g;
      if (((g[0x7546] == 0) || (g[0x4135] != 0)) || (g[0x33b3] == 0)) goto LAB_0809d55a;
      if (g[0x7545] == g[0x33b3]) break;
      GameSetVol(0,0);
      BGMPause(g + 0x10aa);
      piVar7 = g;
      piVar1 = g + 0x2b93;
      g[0x4135] = 1;
      if (*piVar1 == 0) {
        if (piVar7[0x2f94] != 0) {
          strcpy(local_401c,(char *)(piVar7 + 0x2f95));
          piVar7 = g;
          g[0x2351] = 0;
        }
        goto LAB_0809d55a;
      }
      bVar4 = ContinueScreen();
      piVar7 = g;
      if ((GHIDRA_ZEXT8(bVar4) == 0) || (piVar1 = g + 0x4134, g[0x4135] = 0, *piVar1 != 0))
      goto LAB_0809d55a;
      GameSetVol(piVar7[0x6ef5],piVar7[0x6ef7]);
      BGMResume(g + 0x10aa);
    }
    iVar6 = ArcadeListEnemiesLeft();
    iVar10 = ArcadeListGetCurSize();
    piVar7 = g;
    if (iVar6 <= iVar10) {
      BGMFree(g + 0x10aa);
      iVar6 = g[0x14b4] + g[g[0x33b3] * 0x6a7 + 0x2d18] * 0x702c;
      piVar7 = (int *)(iVar6 + 0x6027);
      if (*(char *)(iVar6 + 0x6027) == '\0') {
        if (g[0x2b54] != 0) {
          ArcadeWinScreen();
        }
        if (g[0x2753] != 0) {
          piVar7 = g + 0x2754;
          goto LAB_0809d500;
        }
      }
      else {
        joindirfile((char *)local_101c,(char *)(iVar6 + 0x200a),(char *)piVar7);
        bVar5 = fileexist((char *)local_101c);
        if (GHIDRA_ZEXT8(bVar5) != 0) {
          piVar7 = local_101c;
        }
LAB_0809d500:
        strcpy(local_201c,(char *)piVar7);
      }
      if (g[0x2352] != 0) {
        strcpy(local_301c,(char *)(g + 0x2353));
      }
      g[0x2351] = 0;
      piVar7 = g;
    }
LAB_0809d55a:
    if (((piVar7[0x7546] != 0) && (piVar7[0x4135] == 0)) &&
       ((piVar7[0x33b4] != 0 && (BGMFree(piVar7 + 0x10aa), g[0x2b73] != 0)))) {
      SurvivalResultsScreen();
    }
    PalGrpClear();
    GameStgDeInitFightData();
    GameUnloadStage();
    TimerSetSyncFPS(0x3c);
    PlayCutscene(local_201c,"scene");
    PlayCutscene(local_301c,"scene");
    PlayCutscene(local_401c,"scene");
    GameReloadSystemSprSnd();
    GameSetVol(g[0x6ef5],g[0x6ef7]);
    uVar8 = 1;
  }
  return uVar8;
}
#undef local_4024
#undef local_4020
#undef local_401c
#undef local_301c
#undef local_201c
#undef local_101c

/* ArcadeWinScreen @ 0x0809d630, 505 bytes
 * FIXUP: return type set to void: only unaffected-register values were returned
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void ArcadeWinScreen(void)

{
  float10 fVar1;
  bool bVar2;
  undefined4 extraout_EAX;
  int *piVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  
  g[0x52bd] = 0;
  TimerSetSyncFPS(0x3c);
  GameRoundReset();
  CameraMoveAbs((float)g[0x1080],(float)g[0x1081]);
  iVar5 = g[0x7459];
  piVar3 = g;
  if (iVar5 <= g[0x745a]) {
    iVar7 = iVar5 * 4 + 0x1cf60;
    do {
      iVar4 = *(int *)(iVar7 + 4 + (int)piVar3);
      if ((iVar4 == 0) || (bVar2 = true, *(int *)(iVar4 + 0x158) == 0)) {
        bVar2 = false;
      }
      if (bVar2) {
        PlayerEnableSet(iVar5,0);
        piVar3 = g;
      }
      iVar5 = iVar5 + 1;
      iVar7 = iVar7 + 4;
    } while (iVar5 <= piVar3[0x745a]);
  }
  if (piVar3[0x33b3] == 2) {
    piVar6 = (int *)piVar3[0x73db];
    piVar3 = (int *)piVar3[0x73dd];
  }
  else {
    piVar6 = (int *)piVar3[0x73da];
    piVar3 = (int *)piVar3[0x73dc];
  }
  if (piVar6 != (int *)0x0) {
    PlayerEnableSet(piVar6[2],1);
    PlayerReset(piVar6);
    PlayerChangeState((int)piVar6,0xb4);
    fVar1 = (float)(V_Width / 2 + g[0x7311]);
    piVar6[0x67] = GHIDRA_F2I(int, fVar1);
    if (piVar3 != (int *)0x0) {
      piVar6[0x67] = GHIDRA_F2I(int, (fVar1 - (float)(piVar6[100] * 0x28)));
    }
    piVar6[0x8f] = 1;
  }
  if (piVar3 != (int *)0x0) {
    PlayerEnableSet(piVar3[2],1);
    PlayerReset(piVar3);
    PlayerChangeState((int)piVar3,0xb4);
    iVar5 = g[0x7311];
    iVar4 = V_Width / 2;
    iVar7 = piVar6[100];
    piVar3[100] = -iVar7;
    piVar3[0x8f] = 1;
    piVar3[0x67] = GHIDRA_F2I(int, (float)(iVar4 + iVar5 + iVar7 * 0x28));
  }
  piVar3 = g;
  g[0x7541] = 0;
  piVar3[0x7542] = 0;
  piVar3[0x74e0] = 0;
  piVar3[0x74df] = 1;
  GameLoop(5);
  PalGrpResetPalette();
  SndIDStop(-1);
  return;
}

/* SurvivalResultsScreen @ 0x0809d830, 552 bytes
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void SurvivalResultsScreen(void)

{
  int iVar1;
  float10 fVar2;
  bool bVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  
  piVar4 = g;
  iVar9 = g[g[0x33b4] + 0x7506];
  g[0x52bd] = 0;
  TimerSetSyncFPS(0x3c);
  GameRoundReset();
  CameraMoveAbs((float)g[0x1080],(float)g[0x1081]);
  iVar6 = g[0x7459];
  piVar5 = g;
  if (iVar6 <= g[0x745a]) {
    iVar8 = iVar6 * 4 + 0x1cf60;
    do {
      iVar1 = *(int *)(iVar8 + 4 + (int)piVar5);
      if ((iVar1 == 0) || (bVar3 = true, *(int *)(iVar1 + 0x158) == 0)) {
        bVar3 = false;
      }
      if (bVar3) {
        PlayerEnableSet(iVar6,0);
        piVar5 = g;
      }
      iVar6 = iVar6 + 1;
      iVar8 = iVar8 + 4;
    } while (iVar6 <= piVar5[0x745a]);
  }
  if (piVar5[0x33b4] == 2) {
    piVar7 = (int *)piVar5[0x73db];
    piVar5 = (int *)piVar5[0x73dd];
  }
  else {
    piVar7 = (int *)piVar5[0x73da];
    piVar5 = (int *)piVar5[0x73dc];
  }
  iVar9 = ((piVar4[0x2b92] <= iVar9) - 1 & 0xfffffff6) + 0xb4;
  if (piVar7 != (int *)0x0) {
    PlayerEnableSet(piVar7[2],1);
    PlayerReset(piVar7);
    PlayerChangeState((int)piVar7,iVar9);
    fVar2 = (float)(V_Width / 2 + g[0x7311]);
    piVar7[0x67] = GHIDRA_F2I(int, fVar2);
    if (piVar5 != (int *)0x0) {
      piVar7[0x67] = GHIDRA_F2I(int, (fVar2 - (float)(piVar7[100] * 0x28)));
    }
    piVar7[0x8f] = 1;
  }
  if (piVar5 != (int *)0x0) {
    PlayerEnableSet(piVar5[2],1);
    PlayerReset(piVar5);
    PlayerChangeState((int)piVar5,iVar9);
    iVar9 = g[0x7311];
    iVar6 = piVar7[100];
    iVar8 = V_Width / 2;
    piVar5[100] = -iVar6;
    piVar5[0x8f] = 1;
    piVar5[0x67] = GHIDRA_F2I(int, (float)(iVar8 + iVar9 + iVar6 * 0x28));
  }
  piVar4 = g;
  g[0x7541] = 0;
  piVar4[0x7542] = 0;
  piVar4[0x74e0] = 0;
  piVar4[0x74df] = 1;
  GameLoop(6);
  PalGrpResetPalette();
  SndIDStop(-1);
  return;
}

/* DemoFightSetup @ 0x0809da60, 410 bytes */
void DemoFightSetup(void)

{
  uint uVar1;
  long lVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int *piVar8;
  int *piVar9;
  
  piVar8 = g;
  g[0x33ae] = 0;
  piVar8[0x33b3] = 0;
  piVar8[0x3a60] = 1;
  piVar8[0x33b9] = 1;
  piVar8[0x3a64] = 0;
  piVar8[0x33bd] = 0;
  piVar8[0x3a62] = 0;
  piVar8[0x33bb] = 0;
  uVar7 = 0;
  do {
    piVar8 = g;
    iVar6 = (int)uVar7 / 2;
    iVar4 = (int)uVar7 % 2;
    uVar1 = uVar7 + 1;
    g[iVar4 * 0x6a7 + iVar6 * 5 + 0x33c1] = iVar4;
    piVar8[iVar4 * 0x6a7 + iVar6 * 5 + 0x33be] = uVar1;
    lVar2 = random();
    iVar5 = lVar2 % g[0x14b5];
    piVar8[iVar4 * 0x6a7 + iVar6 * 5 + 0x33bf] = iVar5;
    lVar2 = random();
    uVar3 = CharReservePal(lVar2 % 0xc,iVar5);
    piVar8[iVar4 * 0x6a7 + iVar6 * 5 + 0x33c0] = uVar3;
    iVar5 = piVar8[iVar4 * 0x6a7 + 0x33bd];
    piVar8[iVar4 * 0x6a7 + 0x33bd] = iVar5 + 1;
    piVar9 = g;
    if (1 < iVar5 + 1) {
      piVar8[iVar4 * 0x6a7 + 0x33bb] = 1;
      piVar8[iVar4 * 0x6a7 + 0x33bc] = 1;
      piVar9[0x33ae] = 0;
    }
    piVar8[iVar4 * 0x6a7 + 0x33ba] = piVar8[iVar4 * 0x6a7 + 0x33ba] + 1;
    piVar8 = g;
    g[uVar7 + 0x33af] = uVar7 & 1;
    piVar8[uVar7 + 0x741a] = 1;
    uVar7 = uVar1;
  } while ((int)uVar1 < 2);
  *(undefined1 *)(piVar8 + 0x805) = 0;
  piVar8 = g + 0x33bb;
  piVar9 = g + 0x4106;
  for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar9 = *piVar8;
    piVar8 = piVar8 + 1;
    piVar9 = piVar9 + 1;
  }
  piVar8 = g + 0x3a62;
  piVar9 = g + 0x411d;
  for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar9 = *piVar8;
    piVar8 = piVar8 + 1;
    piVar9 = piVar9 + 1;
  }
  return;
}

/* ContinueScreen @ 0x0809dc00, 5 bytes
 * REVIEW: calls-missing-in-pid:AnimPerArrayDrawGrp,AnimPerArrayUpdate,AnimUpdate,BGArrayUpdate,BGMPoll,DrawToScreen,FrameSkipReset,FrameSkipUpdate,GameBGDraw,GameFGDraw,GameResetPersistVars,GameRoundReset,GlobalInputUpdate,KBBufferClear,KBIMenuGetKey,KBPoll,KBgetchraw,KBkbhit,MasterPalFinishedDraw,MasterPalMul,MasterPalProcessChanges,PRSprArrayClear,PRSprArrayDraw,PadBufClear,PadGet,PadHit,PadPoll,PalGrpMakeFlag,PalGrpResetPalette,PalGrpSetMul,PlayerChangeState,PlayerDrawAnim,PlayerDrawShadow,PlayerReset,PlayerUpdate,TimerSetSyncFPS,TimerWaitSync,UInpBufClear,UInpGet,UInpHit,UInpRefreshFlags,VRetrace,V_FontDraw,V_FontDrawCenter,V_FontDrawRight,V_SetBuf */
byte ContinueScreen(void)

{
  byte bVar1;
  
  bVar1 = ContinueScreenLoop();
  return bVar1;
}

/* GameModeInFightScreen @ 0x0809dc10, 23 bytes */
bool GameModeInFightScreen(void)

{
  return g[0x33b7] - 4U < 4;
}

/* GameModeInPassiveFightScreen @ 0x0809dc30, 23 bytes */
bool GameModeInPassiveFightScreen(void)

{
  return g[0x33b7] - 5U < 3;
}

