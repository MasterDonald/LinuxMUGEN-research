/*
 * init.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08098c50-0x0809c464, 18 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* CloseAllFunc @ 0x08098c50, 16 bytes */
void CloseAllFunc(void)

{
  g[0x4135] = 1;
  return;
}

/* GameInit @ 0x08098c60, 1764 bytes
 * REVIEW: pid-in_stack_; calls-missing-in-pid:builtin_strncpy
 * FIXUP: by-value parameters attached: opts, mode
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: 2 exact-text site patches */
void GameInit(MugenCmdLine opts, int *mode)
{
  int *piVar1;
  bool bVar2;
  int *piVar3;
  int iVar4;
  FILE *stream;
  undefined3 extraout_var;
  uint uVar5;
  size_t sVar6;
  uint *puVar7;
  uint *puVar8;
  uint uVar9;
  int *piVar10;
  char *pcVar11;
  
  ElecInit();
  if (*(code **)(system_driver + 0x20) != (code *)0x0) {
    (**(code **)(system_driver + 0x20))("M.U.G.E.N");
  }
  piVar3 = (int *)ecalloc(1,0x20b60);
  if (piVar3 == (int *)0x0) {
    printf("Can\'t allocate game variables.\n\n");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  g = piVar3;
  iVar4 = GameConfigRead("data/mugen.cfg");
  if (iVar4 == 0) {
    strcat((char *)(g + 0x81d2),"\nError reading data/mugen.cfg");
    ErrorExit();
  }
  piVar3 = g;
  if ((*(int *)((char *)&opts + 0x28c)) != 0) {
    g[0x755f] = 1;
    piVar3[0x7563] = 0;
    piVar3[0x7561] = 0;
    piVar3[0x7560] = 0;
    piVar3[0x7562] = 0;
  }
  piVar3 = g;
  if ((*(int *)((char *)&opts + 0x184)) != 0) {
    g[0x758c] = 1;
    strcpy((char *)(piVar3 + 0x758d),((char *)&opts + 0x188));
    stream = fopen((char *)(g + 0x758d),"wt");
    if (stream != (FILE *)0x0) {
      fclose(stream);
    }
  }
  piVar3 = (int *)((char *)&opts + 0x298);
  piVar10 = g + 0x798d;
  for (iVar4 = 0x11; piVar1 = g, iVar4 != 0; iVar4 = iVar4 + -1) {
    *piVar10 = *piVar3;
    piVar3 = piVar3 + 1;
    piVar10 = piVar10 + 1;
  }
  g[0x82d3] = (*(int *)((char *)&opts + 0x2e4));
  piVar1[0x82d6] = (*(int *)((char *)&opts + 0x2e8));
  piVar1[0x799d] = (*(int *)((char *)&opts + 0x290));
  if ((*(char *)((char *)&opts + 0x40)) == '\0') {
    *mode = 1;
  }
  else {
    piVar1[0x81cc] = 1;
  }
  TimerInit(0xb4);
  printf("Initializing keyboard.\n");
  KBInit();
  KBBufferChange(2);
  KBRepeatSet(0,0);
  KBFilterRelease = 0;
  KBLEDLockSet(1);
  KBLEDSet(0);
  GameDefKeyInit();
  iVar4 = UInpInit();
  if (iVar4 == 0) {
    ErrorExitM("Can\'t init input");
  }
  printf("Initializing sound...");
  if ((*(int *)((char *)&opts + 0x288)) != 0) {
    g[0x6ef3] = 0;
    SndSetMode(0);
    printf("sound is disabled\n");
  }
  if (g[0x6ef3] != 0) {
    iVar4 = SndInit(g[0x755b],g[0x755c],g[0x755d]);
    if (iVar4 == 0) {
      iVar4 = SndInit(g[0x755b],0,g[0x755d]);
      if (iVar4 == 0) {
        iVar4 = SndInit(0,g[0x755c],g[0x755d]);
        if (iVar4 == 0) {
          g[0x6ef3] = 0;
          SndSetMode(0);
          pcVar11 = "failed to init hardware.\n";
        }
        else {
          pcVar11 = "no wave device found.\n";
        }
      }
      else {
        pcVar11 = "no midi device found.\n";
      }
    }
    else {
      SndSetMode(1);
      pcVar11 = "ok\n";
    }
    printf(pcVar11);
    ErrorSet(0);
    if (g[0x7560] != 0) {
      MP3Init();
    }
  }
  printf("Initializing graphics.\n");
  bVar2 = G_Init();
  if (GHIDRA_ZEXT8(bVar2) == 0) {
    ErrorExit();
  }
  uVar5 = g[0x7556];
  iVar4 = G_SetRenderMode(0);
  if (iVar4 == 0) {
    ErrorExit();
  }
  iVar4 = G_SetMode(uVar5,g[0x7553],g[0x7554],g[0x7555]);
  if (iVar4 == 0) {
    if (((g[0x7553] == 0x280) && (g[0x7554] == 0x1e0)) && (g[0x7555] == 0x10)) {
      ErrorExit();
    }
    else {
      printf("\nError: Can\'t change video mode to %ix%ix%ibits\n",g[0x7553],g[0x7554],g[0x7555]);
      printf("Switch to 640x480x16bits? (y/n)\n\n");
      fflush((FILE *)stdout);
      KBBufferClear();
      do {
        uVar5 = KBgetchraw();
      } while ((uVar5 & 0x100) != 0);
      if (uVar5 != 0x15) {
        ErrorExit();
      }
      iVar4 = G_SetMode(0,0x280,0x1e0,0x10);
      if (iVar4 == 0) {
        ErrorExitM("Unable to initialize graphics for M.U.G.E.N");
      }
    }
  }
  if (g[0x7555] == 0x20) {
    G_SetRGBtoBGR(1);
  }
  if (g[0x7557] != 0) {
    G_SetBlitMode(g[0x7557],1);
  }
  g[0x74e7] = 1;
  SwitchCallbacksInit();
  iVar4 = GameVarInit();
  if (iVar4 == 0) {
    ErrorExit();
  }
  strcpy((char *)((int)g + 0xfff),(char *)g);
  piVar3 = g;
  pcVar11 = (char *)((int)g + 0xfff);
  sVar6 = strlen(pcVar11);
  if (*(char *)((int)piVar3 + sVar6 + 0xffe) == '\\') {
    sVar6 = strlen(pcVar11);
    *(undefined1 *)((int)piVar3 + sVar6 + 0xffe) = 0;
    piVar3 = g;
  }
  sVar6 = strlen((char *)((int)piVar3 + 0xfff));
  if (*(char *)(sVar6 + 0xffe + (int)piVar3) != '/') {
    strcat((char *)((int)piVar3 + 0xfff),"/");
  }
  iVar4 = GameVarLoadFonts();
  if (iVar4 == 0) {
    ErrorExit();
  }
  GameResetOptions();
  GameLoadOptions();
  if (0 < (*(int *)((char *)&opts + 0x2dc))) {
    g[0x799e] = (*(int *)((char *)&opts + 0x2dc));
  }
  if ((*(int *)((char *)&opts + 0x2e0)) + 9U < 0x13) {
    g[0x79a1] = (*(int *)((char *)&opts + 0x2e0));
  }
  piVar3 = g;
  if ((*(char *)((char *)&opts + 0x140)) == '\0') goto LAB_080992ce;
  *(undefined4 *)((int)g + 0x15aff) = 0x61746164;
  *(undefined2 *)((int)piVar3 + 0x15b03) = 0x2f;
  puVar7 = (uint *)((char *)&opts + 0x140);
  do {
    puVar8 = puVar7;
    puVar7 = puVar8 + 1;
    uVar5 = *puVar8 + 0xfefefeff & (*puVar8 ^ 0xffffffff);
    uVar9 = uVar5 & 0x80808080;
  } while (uVar9 == 0);
  if ((uVar5 & 0x8080) == 0) {
    uVar9 = uVar9 >> 0x10;
    puVar7 = (uint *)((int)puVar8 + 6);
  }
  puVar8 = (uint *)((char *)&opts + 0x140);
  if ((int)puVar7 + ((-3 - (uint)CARRY1((byte)uVar9,(byte)uVar9)) - (int)((char *)&opts + 0x140)) < 4) {
LAB_08099294:
    strcat(((char *)&opts + 0x140),"/system.def");
  }
  else {
    do {
      puVar7 = puVar8;
      puVar8 = puVar7 + 1;
      uVar5 = *puVar7 + 0xfefefeff & (*puVar7 ^ 0xffffffff);
      uVar9 = uVar5 & 0x80808080;
    } while (uVar9 == 0);
    if ((uVar5 & 0x8080) == 0) {
      uVar9 = uVar9 >> 0x10;
      puVar8 = (uint *)((int)puVar7 + 6);
    }
    iVar4 = _alemu_stricmp((char *)((int)puVar8 +
                                   (int)(((char *)&opts + 0x139) +
                                        (-(int)((char *)&opts + 0x140) -
                                        (uint)CARRY1((byte)uVar9,(byte)uVar9)))),".def");
    if (iVar4 != 0) goto LAB_08099294;
  }
  splitdirfile(((char *)&opts + 0x140),(char *)(g + 0x56c1),(char *)(g + 0x52c0));
LAB_080992ce:
  iVar4 = GameLoadSystem();
  if (iVar4 == 0) {
    strcat((char *)(g + 0x81d2),"\nError loading system data: ");
    strcat((char *)(g + 0x81d2),(char *)((int)g + 0x15aff));
    strcat((char *)(g + 0x81d2),(char *)(g + 0x52c0));
    ErrorExit();
  }
  GameSetVol(g[0x6ef5],0xffffffff);
  return;
}

/* GameDeInit @ 0x08099350, 319 bytes
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void GameDeInit(int param_1)

{
  float10 fVar1;
  
  G_SetMode(0xffffffff,0x50,0x19,8);
  printf("M.U.G.E.N test ver %i.%02i.%02i\t\t\t\t\t(c)%i Elecbyte\n\n",MUGENDATE_Y,MUGENDATE_M,
         MUGENDATE_D,MUGENDATE_Y);
  fVar1 = (float)TicksPerSecond;
  printf("BG load time: %.1f ms\nPlayer load time: %.1f ms, %.1f ms\n",
         (double)(((float)g[0x81c4] / fVar1) * 1000.0),(double)(((float)g[0x81c5] / fVar1) * 1000.0)
         ,(double)(((float)g[0x81c6] / fVar1) * 1000.0));
  printf("Total load time: %.1f ms\n",(double)(((float)g[0x81c9] / (float)TicksPerSecond) * 1000.0))
  ;
  printf("Pal groups in background: %i\n",g[0x81ca]);
  printf("\n");
  PlayerCacheClear();
  CharInfoFree();
  if (param_1 != 0) {
    FreeSelectScreenMatrix();
  }
  GameFreeFightData();
  GameUnloadSystem();
  chdir((char *)g);
  GameVarDeInit();
  UInpDeInit();
  PadDeInit();
  KBDeInit();
  SwitchCallbacksDeInit();
  TimerDeInit();
  G_DeInit();
  CDADeInit();
  MP3DeInit();
  SndDeInit();
  ElecDeInit();
  return;
}

/* GameInitPads @ 0x08099490, 344 bytes */
void GameInitPads(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  
  piVar3 = g + 0x736f;
  piVar4 = g + 0x7355;
  for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar4 = *piVar3;
    piVar3 = piVar3 + 1;
    piVar4 = piVar4 + 1;
  }
  piVar3 = g + 0x737c;
  piVar4 = g + 0x7362;
  for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
    *piVar4 = *piVar3;
    piVar3 = piVar3 + 1;
    piVar4 = piVar4 + 1;
  }
  if (g[0x738b] == 0) {
    piVar3 = g + 0x7355;
    for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar3 = 0;
      piVar3 = piVar3 + 1;
    }
    PlayerKeysRemoveZero((int)(g + 0x7355),0x80);
  }
  if (g[0x738c] == 0) {
    piVar3 = g + 0x7362;
    for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
      *piVar3 = 0;
      piVar3 = piVar3 + 1;
    }
    PlayerKeysRemoveZero((int)(g + 0x7362),0x80);
  }
  if (PadInstalled != 0) {
    PadDeInit();
  }
  iVar1 = g[0x738b];
  if (((iVar1 != 0) || (g[0x738c] != 0)) && (g[0x799d] == 0)) {
    if (iVar1 == 0) {
      iVar2 = g[0x738e];
    }
    else {
      iVar2 = g[0x738d];
    }
    if (iVar2 == 0x16) {
      DeviceInit();
    }
    iVar1 = PadInit(iVar2,(uint)(iVar1 == 0));
    piVar3 = g;
    if (iVar1 == 0) {
      g[0x738c] = 0;
      piVar3[0x738b] = 0;
    }
  }
  iVar1 = UInpReInit();
  if (iVar1 == 0) {
    ErrorExitM("Can\'t init input");
  }
  return;
}

/* GameDefKeyInit @ 0x080995f0, 70 bytes */
void GameDefKeyInit(void)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  
  iVar5 = 0;
  iVar7 = 0;
  piVar6 = g + 0x733b;
  do {
    iVar4 = 0;
    piVar3 = (int *)((int)&DefaultKeyCfg + iVar7);
    do {
      piVar1 = &KeyCfgToKBIMap + iVar4;
      iVar4 = iVar4 + 1;
      iVar2 = *piVar3;
      piVar3 = piVar3 + 1;
      piVar6[*piVar1] = iVar2;
    } while (iVar4 < 0xb);
    iVar5 = iVar5 + 1;
    piVar6 = piVar6 + 0xd;
    iVar7 = iVar7 + 0x2c;
  } while (iVar5 < 2);
  return;
}

/* GameInputSetup @ 0x08099640, 377 bytes
 * FIXUP: frame emulation: 8 stack locals placed at their original offsets in a 0x650-byte frame (a local's address escapes, see apply_frame_emulation) */
bool GameInputSetup(void)

{
  uint *puVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  unsigned char ghidra_frame[0x650] __attribute__((aligned(16)));
#define local_644 (*(int *)(ghidra_frame + 0xc))
#define local_640 (*(int *)(ghidra_frame + 0x10))
#define local_63c (*(undefined4 **)(ghidra_frame + 0x14))
#define local_638 (*(code **)(ghidra_frame + 0x18))
#define local_634 (*(int *)(ghidra_frame + 0x1c))
#define local_630 (*(int *)(ghidra_frame + 0x20))
#define local_62c (*(uint (*)[383])(ghidra_frame + 0x24))
#define local_30 (*(int (*)[8])(ghidra_frame + 0x620))
  
  iVar6 = 0x17f;
  piVar2 = local_30;
  do {
    *piVar2 = iVar6;
    piVar2 = piVar2 + -1;
    iVar6 = iVar6 + -1;
  } while (-1 < iVar6);
  local_634 = 0;
  do {
    local_638 = KBToUInp;
    if (local_634 != 0) {
      local_638 = PadToUInp;
    }
    local_630 = 0;
    local_63c = &DefaultKeyCfg;
    local_640 = 0;
    local_644 = 0;
    do {
      piVar2 = g;
      if (local_634 == 0) {
        iVar6 = local_644 + 0x1cc84;
      }
      else {
        iVar6 = local_640 + 0x1cd54;
      }
      iVar7 = 0;
      do {
        iVar4 = (&KeyCfgToKBIMap)[iVar7];
        iVar3 = (*local_638)(*(undefined4 *)((int)piVar2 + iVar4 * 4 + iVar6));
        if (0x180 < iVar3) {
                    /* WARNING: Subroutine does not return */
          __assert_fail("KeyConvFunc(key_pad->sc[KeyCfgToKBIMap[i]]) < ((0x20*4)+256)+1",
                        "src/mugen/init.c",0x254,"GameInputSetup");
        }
        iVar4 = (*local_638)(*(undefined4 *)((int)piVar2 + iVar4 * 4 + iVar6));
        puVar1 = local_63c + iVar7;
        iVar7 = iVar7 + 1;
        uVar5 = KBToUInp(*puVar1);
        local_62c[iVar4] = uVar5;
      } while (iVar7 < 0xb);
      local_630 = local_630 + 1;
      local_63c = local_63c + 0xb;
      local_640 = local_640 + 0x34;
      local_644 = local_644 + 0x34;
    } while (local_630 < 2);
    local_634 = local_634 + 1;
  } while (local_634 < 2);
  iVar6 = UInpSetKeyMap(local_62c);
  if (iVar6 == 0) {
    bVar8 = false;
  }
  else {
    iVar6 = UInpReInit();
    bVar8 = iVar6 != 0;
  }
  return bVar8;
}
#undef local_644
#undef local_640
#undef local_63c
#undef local_638
#undef local_634
#undef local_630
#undef local_62c
#undef local_30

/* GfxResize @ 0x080997c0, 184 bytes */
bool GfxResize(int param_1,int param_2,undefined4 param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  uVar1 = g[0x7556];
  if ((param_4 == 0) || (uVar1 != 1)) {
    uVar2 = uVar1;
    if ((param_4 == 0) && (uVar1 != 1)) {
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 2;
  }
  iVar3 = G_SetMode(uVar2,param_1,param_2,param_3);
  if (iVar3 == 0) {
    G_SetMode(uVar1,g[0x7553],g[0x7554],g[0x7555]);
  }
  if (g[0x7557] != 0) {
    G_SetBlitMode(g[0x7557],1);
  }
  V_SetBuf(V_Current,0);
  return iVar3 != 0;
}

/* GameLoadFightData @ 0x08099880, 9120 bytes
 * FIXUP: frame emulation: 71 stack locals placed at their original offsets in a 0x2250-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 GameLoadFightData(FILE *param_1)

{
  int *piVar1;
  int *piVar2;
  bool bVar3;
  int *piVar4;
  FILE *pFVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  int iVar9;
  char *__src;
  FILE *extraout_ECX;
  FILE *extraout_ECX_00;
  FILE *extraout_ECX_01;
  FILE *extraout_ECX_02;
  FILE *extraout_ECX_03;
  undefined4 extraout_ECX_04;
  FILE *extraout_ECX_05;
  undefined4 extraout_ECX_06;
  FILE *extraout_ECX_07;
  undefined4 extraout_ECX_08;
  FILE *extraout_ECX_09;
  char *extraout_ECX_10;
  FILE *extraout_ECX_11;
  FILE *extraout_ECX_12;
  FILE *extraout_EDX;
  FILE *extraout_EDX_00;
  FILE *extraout_EDX_01;
  FILE *extraout_EDX_02;
  int *extraout_EDX_03;
  FILE *extraout_EDX_04;
  FILE *pFVar10;
  char *pcVar11;
  int *piVar12;
  uint *puVar13;
  unsigned char ghidra_frame[0x2250] __attribute__((aligned(16)));
#define local_2248 (*(int *)(ghidra_frame + 0x8))
#define local_2244 (*(int **)(ghidra_frame + 0xc))
#define local_2240 (*(int **)(ghidra_frame + 0x10))
#define local_223c (*(int **)(ghidra_frame + 0x14))
#define local_2238 (*(int **)(ghidra_frame + 0x18))
#define local_2234 (*(int *)(ghidra_frame + 0x1c))
#define local_2230 (*(int **)(ghidra_frame + 0x20))
#define local_222c (*(int **)(ghidra_frame + 0x24))
#define local_2228 (*(int **)(ghidra_frame + 0x28))
#define local_2224 (*(int **)(ghidra_frame + 0x2c))
#define local_2220 (*(int **)(ghidra_frame + 0x30))
#define local_221c (*(int **)(ghidra_frame + 0x34))
#define local_2218 (*(int *)(ghidra_frame + 0x38))
#define local_2214 (*(int **)(ghidra_frame + 0x3c))
#define local_2210 (*(int **)(ghidra_frame + 0x40))
#define local_220c (*(int **)(ghidra_frame + 0x44))
#define local_2208 (*(int **)(ghidra_frame + 0x48))
#define local_2204 (*(int **)(ghidra_frame + 0x4c))
#define local_2200 (*(int **)(ghidra_frame + 0x50))
#define local_21fc (*(int *)(ghidra_frame + 0x54))
#define local_21f8 (*(int **)(ghidra_frame + 0x58))
#define local_21f4 (*(int **)(ghidra_frame + 0x5c))
#define local_21f0 (*(int **)(ghidra_frame + 0x60))
#define local_21ec (*(int **)(ghidra_frame + 0x64))
#define local_21e8 (*(int **)(ghidra_frame + 0x68))
#define local_21e4 (*(int **)(ghidra_frame + 0x6c))
#define local_21e0 (*(int *)(ghidra_frame + 0x70))
#define local_21dc (*(int **)(ghidra_frame + 0x74))
#define local_21d8 (*(int **)(ghidra_frame + 0x78))
#define local_21d4 (*(int **)(ghidra_frame + 0x7c))
#define local_21d0 (*(int **)(ghidra_frame + 0x80))
#define local_21cc (*(int **)(ghidra_frame + 0x84))
#define local_21c8 (*(int **)(ghidra_frame + 0x88))
#define local_21c0 (*(uint **)(ghidra_frame + 0x90))
#define local_21bc (*(int **)(ghidra_frame + 0x94))
#define local_21b8 (*(int **)(ghidra_frame + 0x98))
#define local_21b0 (*(uint **)(ghidra_frame + 0xa0))
#define local_21ac (*(int **)(ghidra_frame + 0xa4))
#define local_21a8 (*(int **)(ghidra_frame + 0xa8))
#define local_21a0 (*(uint **)(ghidra_frame + 0xb0))
#define local_219c (*(int **)(ghidra_frame + 0xb4))
#define local_2198 (*(int **)(ghidra_frame + 0xb8))
#define local_2194 (*(int **)(ghidra_frame + 0xbc))
#define local_2190 (*(int **)(ghidra_frame + 0xc0))
#define local_218c (*(int **)(ghidra_frame + 0xc4))
#define local_2188 (*(int **)(ghidra_frame + 0xc8))
#define local_2180 (*(int **)(ghidra_frame + 0xd0))
#define local_217c (*(int **)(ghidra_frame + 0xd4))
#define local_2174 (*(int **)(ghidra_frame + 0xdc))
#define local_2170 (*(int **)(ghidra_frame + 0xe0))
#define local_216c (*(int **)(ghidra_frame + 0xe4))
#define local_2168 (*(int **)(ghidra_frame + 0xe8))
#define local_2164 (*(int **)(ghidra_frame + 0xec))
#define local_2160 (*(int *)(ghidra_frame + 0xf0))
#define local_215c (*(int **)(ghidra_frame + 0xf4))
#define local_2158 (*(int **)(ghidra_frame + 0xf8))
#define local_2154 (*(int **)(ghidra_frame + 0xfc))
#define local_2150 (*(int **)(ghidra_frame + 0x100))
#define local_214c (*(int **)(ghidra_frame + 0x104))
#define local_2148 (*(int **)(ghidra_frame + 0x108))
#define local_2144 (*(int **)(ghidra_frame + 0x10c))
#define local_2140 (*(int **)(ghidra_frame + 0x110))
#define local_213c (*(int **)(ghidra_frame + 0x114))
#define local_2138 (*(int **)(ghidra_frame + 0x118))
#define local_2134 (*(int **)(ghidra_frame + 0x11c))
#define local_2130 (*(int **)(ghidra_frame + 0x120))
#define local_212c (*(int **)(ghidra_frame + 0x124))
#define local_20fc (*(char (*)[4096])(ghidra_frame + 0x154))
#define local_10fc (*(FILE (*)[27])(ghidra_frame + 0x1154))
#define local_fc (*(char (*)[32])(ghidra_frame + 0x2154))
#define local_dc (*(char (*)[204])(ghidra_frame + 0x2174))
  
  piVar4 = g;
  piVar12 = g + 0x4149;
  local_2244 = g + 0x4157;
  pFVar5 = TPReadFile((char *)param_1);
  if (pFVar5 == (FILE *)0x0) {
    piVar7 = g + 0x81d2;
    pcVar11 = "Can\'t open %s";
    pFVar10 = extraout_ECX;
  }
  else {
    splitdirfile((char *)param_1,local_20fc,(char *)0x0);
    iVar6 = TPGroupSeek((int)pFVar5,"Files");
    if (iVar6 == -1) {
      piVar7 = g + 0x81d2;
      pcVar11 = "Missing files info";
      pFVar10 = param_1;
    }
    else {
      param_1 = (FILE *)TPGetValue((int)pFVar5,"sff");
      if (param_1 == (FILE *)0x0) {
        piVar7 = g + 0x81d2;
        pcVar11 = "Can\'t read Files|sff";
        param_1 = extraout_EDX;
        pFVar10 = extraout_EDX;
      }
      else {
        iVar6 = FindFileDirEx((char *)param_1,(char *)local_10fc,(char *)0x0,
                              (undefined4 *)local_20fc);
        if (iVar6 == 0) {
          return 0;
        }
        piVar7 = SpriteReadFile((char *)local_10fc);
        piVar4[0x4149] = (int)piVar7;
        if (piVar7 == (int *)0x0) {
          piVar7 = g + 0x81d2;
          pcVar11 = "Can\'t read %s";
          pFVar10 = pFVar5;
        }
        else {
          param_1 = (FILE *)TPGetValue((int)pFVar5,"snd");
          if (param_1 == (FILE *)0x0) {
            piVar7 = g + 0x81d2;
            pcVar11 = "Can\'t read Files|snd";
            param_1 = local_10fc;
            pFVar10 = local_10fc;
          }
          else {
            iVar6 = FindFileDirEx((char *)param_1,(char *)local_10fc,(char *)0x0,
                                  (undefined4 *)local_20fc);
            if (iVar6 == 0) {
              return 0;
            }
            piVar7 = SndReadFile((char *)local_10fc);
            piVar4[0x4155] = (int)piVar7;
            if (piVar7 == (int *)0x0) {
              piVar7 = g + 0x81d2;
              pcVar11 = "Can\'t read %s";
              pFVar10 = extraout_EDX_00;
            }
            else {
              param_1 = (FILE *)TPGetValue((int)pFVar5,"fightfx.sff");
              if (param_1 == (FILE *)0x0) {
                piVar7 = g + 0x81d2;
                pcVar11 = "Can\'t read Files|fightfx.sff";
                pFVar10 = (FILE *)0x0;
              }
              else {
                iVar6 = FindFileDirEx((char *)param_1,(char *)local_10fc,(char *)0x0,
                                      (undefined4 *)local_20fc);
                if (iVar6 == 0) {
                  return 0;
                }
                piVar8 = SpriteReadFile((char *)local_10fc);
                piVar7 = g;
                g[0x4147] = (int)piVar8;
                if (piVar8 == (int *)0x0) {
                  piVar7 = piVar7 + 0x81d2;
                  pcVar11 = "Can\'t load %s";
                  pFVar10 = extraout_ECX_00;
                }
                else {
                  param_1 = (FILE *)TPGetValue((int)pFVar5,"fightfx.air");
                  if (param_1 == (FILE *)0x0) {
                    piVar7 = g + 0x81d2;
                    pcVar11 = "Can\'t read Files|fightfx.air";
                    pFVar10 = (FILE *)0x0;
                  }
                  else {
                    iVar6 = FindFileDirEx((char *)param_1,(char *)local_10fc,(char *)0x0,
                                          (undefined4 *)local_20fc);
                    if (iVar6 == 0) {
                      return 0;
                    }
                    piVar8 = AnimRCReadFile((char *)local_10fc);
                    piVar7 = g;
                    g[0x4148] = (int)piVar8;
                    if (piVar8 == (int *)0x0) {
                      piVar7 = piVar7 + 0x81d2;
                      pcVar11 = "Can\'t load %s";
                      pFVar10 = extraout_ECX_01;
                    }
                    else {
                      param_1 = (FILE *)TPGetValue((int)pFVar5,"common.snd");
                      if (param_1 == (FILE *)0x0) {
                        piVar7 = g + 0x81d2;
                        pcVar11 = "Can\'t read Files|common.snd";
                        pFVar10 = (FILE *)0x0;
                      }
                      else {
                        iVar6 = FindFileDirEx((char *)param_1,(char *)local_10fc,(char *)0x0,
                                              (undefined4 *)local_20fc);
                        if (iVar6 == 0) {
                          return 0;
                        }
                        piVar8 = SndReadFile((char *)local_10fc);
                        piVar7 = g;
                        g[0x4156] = (int)piVar8;
                        if (piVar8 == (int *)0x0) {
                          piVar7 = piVar7 + 0x81d2;
                          pcVar11 = "Can\'t load %s";
                          pFVar10 = extraout_ECX_02;
                        }
                        else {
                          iVar6 = 0;
                          local_2248 = 0;
                          do {
                            *(int *)((int)piVar4 + local_2248 + 0x1052c) = g[0x413a];
                            sprintf(local_fc,"font%i",iVar6,local_2248);
                            param_1 = (FILE *)TPGetValue((int)pFVar5,local_fc);
                            if (param_1 != (FILE *)0x0) {
                              pFVar10 = local_10fc;
                              iVar9 = FindFileDirEx((char *)param_1,(char *)pFVar10,(char *)0x0,
                                                    (undefined4 *)local_20fc);
                              if (iVar9 == 0) {
                                return 0;
                              }
                              iVar9 = FontReadFile((char *)pFVar10);
                              *(int *)((int)piVar4 + local_2248 + 0x1052c) = iVar9;
                              if (iVar9 == 0) {
                                piVar7 = g + 0x81d2;
                                pcVar11 = "Can\'t read font %s";
                                goto LAB_0809bc03;
                              }
                            }
                            iVar6 = iVar6 + 1;
                            local_2248 = local_2248 + 4;
                          } while (iVar6 < 10);
                          iVar6 = TPGroupScanFirst((int)pFVar5);
                          do {
                            iVar9 = strimatch((char *)(iVar6 + 1),"begin action ");
                            if (iVar9 != 0) break;
                            iVar6 = TPGroupScanNext((int)pFVar5);
                          } while (iVar6 != 0);
                          if (iVar6 != 0) {
                            piVar7 = AnimRCReadFileTP((int)pFVar5);
                            piVar4[0x414a] = (int)piVar7;
                            if (piVar7 == (int *)0x0) {
                              strcat((char *)(g + 0x81d2),"\nError loading anim in Files");
                              return 0;
                            }
                          }
                          iVar6 = TPGroupSeek((int)pFVar5,"Lifebar");
                          if (iVar6 == -1) {
                            piVar7 = g + 0x81d2;
                            pcVar11 = "Missing lifebar info";
                            param_1 = extraout_ECX_03;
                            pFVar10 = extraout_ECX_03;
                          }
                          else {
                            local_222c = piVar4 + 0x41c8;
                            local_2230 = piVar4 + 0x41ad;
                            local_223c = piVar4 + 0x4158;
                            piVar7 = piVar4 + 0x4159;
                            local_2234 = 1;
                            local_2240 = piVar7;
                            local_2238 = piVar4 + 0x415a;
                            do {
                              iVar6 = 4;
                              piVar8 = local_2244 + 0x76;
                              do {
                                *piVar8 = 1;
                                piVar8 = piVar8 + -0x1b;
                                iVar6 = iVar6 + -1;
                              } while (-1 < iVar6);
                              sprintf(local_dc,"p%i.pos",local_2234,piVar7);
                              TPScanf((int)pFVar5,local_dc,"%i,%i",local_2244,local_223c);
                              sprintf(local_dc,"p%i.range.x",local_2234);
                              TPScanf((int)pFVar5,local_dc,"%i,%i",local_2240,local_2238);
                              iVar6 = 0;
                              piVar7 = local_2244 + 5;
                              do {
                                iVar9 = iVar6 + 1;
                                sprintf(local_dc,"p%i.bg%i",local_2234,iVar6);
                                SysExplodParse((int)pFVar5,piVar7,local_dc);
                                iVar6 = iVar9;
                                piVar7 = piVar7 + 0x1b;
                              } while (iVar9 < 3);
                              sprintf(local_dc,"p%i.mid",local_2234,extraout_ECX_04);
                              SysExplodParse((int)pFVar5,local_2230,local_dc);
                              sprintf(local_dc,"p%i.front",local_2234);
                              SysExplodParse((int)pFVar5,local_222c,local_dc);
                              local_222c = local_222c + 0x8c;
                              local_2230 = local_2230 + 0x8c;
                              piVar7 = local_2238 + 0x8c;
                              local_223c = local_223c + 0x8c;
                              local_2240 = local_2240 + 0x8c;
                              local_2244 = local_2244 + 0x8c;
                              bVar3 = local_2234 < 2;
                              local_2238 = piVar7;
                              local_2234 = local_2234 + 1;
                            } while (bVar3);
                            iVar6 = TPGroupSeek((int)pFVar5,"Turns Lifebar");
                            if (iVar6 == -1) {
                              piVar7 = g + 0x81d2;
                              pcVar11 = "Missing turns lifebar info";
                              param_1 = extraout_ECX_05;
                              pFVar10 = extraout_ECX_05;
                            }
                            else {
                              local_2210 = piVar4 + 0x4510;
                              local_2214 = piVar4 + 0x44f5;
                              piVar7 = piVar4 + 0x44a0;
                              local_2224 = piVar4 + 0x44a1;
                              local_2228 = piVar4 + 0x449f;
                              local_2218 = 1;
                              local_2220 = piVar7;
                              local_221c = piVar4 + 0x44a2;
                              do {
                                iVar6 = 4;
                                piVar8 = local_2228 + 0x76;
                                do {
                                  *piVar8 = 1;
                                  piVar8 = piVar8 + -0x1b;
                                  iVar6 = iVar6 + -1;
                                } while (-1 < iVar6);
                                sprintf(local_dc,"p%i.pos",local_2218,piVar7);
                                TPScanf((int)pFVar5,local_dc,"%i,%i",local_2228,local_2220);
                                sprintf(local_dc,"p%i.range.x",local_2218);
                                TPScanf((int)pFVar5,local_dc,"%i,%i",local_2224,local_221c);
                                iVar6 = 0;
                                piVar7 = local_2228 + 5;
                                do {
                                  iVar9 = iVar6 + 1;
                                  sprintf(local_dc,"p%i.bg%i",local_2218,iVar6);
                                  SysExplodParse((int)pFVar5,piVar7,local_dc);
                                  iVar6 = iVar9;
                                  piVar7 = piVar7 + 0x1b;
                                } while (iVar9 < 3);
                                sprintf(local_dc,"p%i.mid",local_2218,extraout_ECX_06);
                                SysExplodParse((int)pFVar5,local_2214,local_dc);
                                sprintf(local_dc,"p%i.front",local_2218);
                                SysExplodParse((int)pFVar5,local_2210,local_dc);
                                local_2210 = local_2210 + 0x8c;
                                local_2214 = local_2214 + 0x8c;
                                piVar7 = local_221c + 0x8c;
                                local_2220 = local_2220 + 0x8c;
                                local_2224 = local_2224 + 0x8c;
                                local_2228 = local_2228 + 0x8c;
                                bVar3 = local_2218 < 2;
                                local_221c = piVar7;
                                local_2218 = local_2218 + 1;
                              } while (bVar3);
                              iVar6 = TPGroupSeek((int)pFVar5,"Simul Lifebar");
                              if (iVar6 == -1) {
                                piVar7 = g + 0x81d2;
                                pcVar11 = "Missing simul lifebar info";
                                param_1 = extraout_ECX_07;
                                pFVar10 = extraout_ECX_07;
                              }
                              else {
                                local_21f4 = piVar4 + 0x42e0;
                                local_21f8 = piVar4 + 0x42c5;
                                local_2204 = piVar4 + 0x4270;
                                local_2208 = piVar4 + 0x4271;
                                piVar7 = piVar4 + 0x426f;
                                local_21fc = 1;
                                local_220c = piVar7;
                                local_2200 = piVar4 + 0x4272;
                                do {
                                  iVar6 = 4;
                                  piVar8 = local_220c + 0x76;
                                  do {
                                    *piVar8 = 1;
                                    piVar8 = piVar8 + -0x1b;
                                    iVar6 = iVar6 + -1;
                                  } while (-1 < iVar6);
                                  sprintf(local_dc,"p%i.pos",local_21fc,piVar7);
                                  TPScanf((int)pFVar5,local_dc,"%i,%i",local_220c,local_2204);
                                  sprintf(local_dc,"p%i.range.x",local_21fc);
                                  TPScanf((int)pFVar5,local_dc,"%i,%i",local_2208,local_2200);
                                  iVar6 = 0;
                                  piVar7 = local_220c + 5;
                                  do {
                                    iVar9 = iVar6 + 1;
                                    sprintf(local_dc,"p%i.bg%i",local_21fc,iVar6);
                                    SysExplodParse((int)pFVar5,piVar7,local_dc);
                                    iVar6 = iVar9;
                                    piVar7 = piVar7 + 0x1b;
                                  } while (iVar9 < 3);
                                  sprintf(local_dc,"p%i.mid",local_21fc,extraout_ECX_08);
                                  SysExplodParse((int)pFVar5,local_21f8,local_dc);
                                  sprintf(local_dc,"p%i.front",local_21fc);
                                  SysExplodParse((int)pFVar5,local_21f4,local_dc);
                                  local_21f4 = local_21f4 + 0x8c;
                                  local_21f8 = local_21f8 + 0x8c;
                                  piVar7 = local_2200 + 0x8c;
                                  local_2204 = local_2204 + 0x8c;
                                  local_2208 = local_2208 + 0x8c;
                                  local_220c = local_220c + 0x8c;
                                  bVar3 = local_21fc < 4;
                                  local_2200 = piVar7;
                                  local_21fc = local_21fc + 1;
                                } while (bVar3);
                                iVar6 = TPGroupSeek((int)pFVar5,"Powerbar");
                                if (iVar6 == -1) {
                                  piVar7 = g + 0x81d2;
                                  pcVar11 = "Missing Powerbar info";
                                  param_1 = extraout_ECX_09;
                                  pFVar10 = extraout_ECX_09;
                                }
                                else {
                                  local_21dc = piVar4 + 0x46cf;
                                  iVar6 = 9;
                                  piVar7 = piVar4 + 0x4826;
                                  do {
                                    *piVar7 = -1;
                                    piVar7 = piVar7 + -1;
                                    iVar6 = iVar6 + -1;
                                  } while (-1 < iVar6);
                                  local_21d0 = piVar4 + 0x47e7;
                                  local_21d4 = piVar4 + 0x4740;
                                  local_21d8 = piVar4 + 0x4725;
                                  piVar7 = piVar4 + 0x46d0;
                                  local_21e8 = piVar4 + 0x46d1;
                                  local_21ec = piVar4 + 0x46d2;
                                  local_21e0 = 1;
                                  local_21e4 = (int *)0x0;
                                  local_21f0 = piVar7;
                                  do {
                                    iVar6 = 4;
                                    piVar8 = piVar4 + (int)local_21e4 * 4 + 0x4745;
                                    do {
                                      *piVar8 = 1;
                                      piVar8 = piVar8 + -0x1b;
                                      iVar6 = iVar6 + -1;
                                    } while (-1 < iVar6);
                                    sprintf(local_dc,"p%i.pos",local_21e0,piVar7);
                                    TPScanf((int)pFVar5,local_dc,"%i,%i",local_21dc,local_21f0);
                                    sprintf(local_dc,"p%i.range.x",local_21e0);
                                    TPScanf((int)pFVar5,local_dc,"%i,%i",local_21e8,local_21ec);
                                    iVar6 = 0;
                                    piVar7 = piVar4 + (int)local_21e4 * 4 + 0x46d4;
                                    do {
                                      iVar9 = iVar6 + 1;
                                      sprintf(local_dc,"p%i.bg%i",local_21e0,iVar6);
                                      SysExplodParse((int)pFVar5,piVar7,local_dc);
                                      iVar6 = iVar9;
                                      piVar7 = piVar7 + 0x1b;
                                    } while (iVar9 < 3);
                                    sprintf(local_dc,"p%i.mid",local_21e0,iVar9);
                                    SysExplodParse((int)pFVar5,local_21d8,local_dc);
                                    sprintf(local_dc,"p%i.front",local_21e0);
                                    SysExplodParse((int)pFVar5,local_21d4,local_dc);
                                    sprintf(local_dc,"p%i.counter",local_21e0);
                                    SysExplodParse((int)pFVar5,local_21d0,local_dc);
                                    local_21d0 = local_21d0 + 0x1b;
                                    local_21d4 = local_21d4 + 0x8c;
                                    local_21d8 = local_21d8 + 0x8c;
                                    local_21dc = local_21dc + 0x8c;
                                    piVar7 = (int *)((int)local_21e4 + 0x23);
                                    local_21e8 = local_21e8 + 0x8c;
                                    local_21ec = local_21ec + 0x8c;
                                    local_21f0 = local_21f0 + 0x8c;
                                    bVar3 = local_21e0 < 2;
                                    local_21e4 = piVar7;
                                    local_21e0 = local_21e0 + 1;
                                  } while (bVar3);
                                  pcVar11 = local_fc;
                                  pFVar10 = (FILE *)0x0;
                                  piVar7 = piVar4 + 0x4827;
                                  piVar8 = piVar4 + 0x481d;
                                  do {
                                    param_1 = (FILE *)((int)&pFVar10->_flags + 1);
                                    sprintf(local_fc,"level%i.snd",pFVar10,pcVar11);
                                    TPScanf((int)pFVar5,local_fc,"%i,%i",piVar8,piVar7);
                                    pcVar11 = extraout_ECX_10;
                                    pFVar10 = param_1;
                                    piVar7 = piVar7 + 1;
                                    piVar8 = piVar8 + 1;
                                  } while ((int)param_1 < 10);
                                  iVar6 = TPGroupSeek((int)pFVar5,"face");
                                  if (iVar6 == -1) {
                                    piVar7 = g + 0x81d2;
                                    pcVar11 = "Missing face info";
                                  }
                                  else {
                                    param_1 = (FILE *)0x0;
                                    local_21c8 = piVar4 + 0x4831;
                                    piVar4[0x4911] = 1;
                                    piVar4[0x4912] = -1;
                                    piVar7 = piVar4 + 0x484c;
                                    local_21c0 = (uint *)(piVar4 + 0x4911);
                                    local_21cc = piVar4 + 0x4909;
                                    piVar8 = piVar4 + 0x490d;
                                    do {
                                      param_1 = (FILE *)((int)&param_1->_flags + 1);
                                      sprintf(local_dc,"p%i.pos",param_1,piVar7);
                                      TPScanf((int)pFVar5,local_dc,"%i,%i",local_21cc,piVar8);
                                      sprintf(local_dc,"p%i.bg",param_1);
                                      SysExplodParse((int)pFVar5,local_21c8,local_dc);
                                      sprintf(local_dc,"p%i.face",param_1);
                                      SysExplodParse((int)pFVar5,piVar7,local_dc);
                                      sprintf(local_dc,"p%i.facing",param_1);
                                      TPGetValueInt((int)pFVar5,local_dc,local_21c0);
                                      local_21c0 = local_21c0 + 1;
                                      piVar7 = piVar7 + 0x36;
                                      local_21c8 = local_21c8 + 0x36;
                                      local_21cc = local_21cc + 1;
                                      piVar8 = piVar8 + 1;
                                    } while ((int)param_1 < 2);
                                    iVar6 = TPGroupSeek((int)pFVar5,"simul face");
                                    if (iVar6 == -1) {
                                      piVar7 = g + 0x81d2;
                                      pcVar11 = "Missing simul face info";
                                      pFVar10 = param_1;
                                    }
                                    else {
                                      param_1 = (FILE *)0x0;
                                      local_21b8 = piVar4 + 0x4915;
                                      piVar4[0x49f7] = 1;
                                      piVar4[0x49f5] = 1;
                                      piVar4[0x49f8] = -1;
                                      piVar4[0x49f6] = -1;
                                      piVar7 = piVar4 + 0x4930;
                                      local_21b0 = (uint *)(piVar4 + 0x49f5);
                                      local_21bc = piVar4 + 0x49ed;
                                      piVar8 = piVar4 + 0x49f1;
                                      do {
                                        param_1 = (FILE *)((int)&param_1->_flags + 1);
                                        sprintf(local_dc,"p%i.pos",param_1,piVar7);
                                        TPScanf((int)pFVar5,local_dc,"%i,%i",local_21bc,piVar8);
                                        sprintf(local_dc,"p%i.bg",param_1);
                                        SysExplodParse((int)pFVar5,local_21b8,local_dc);
                                        sprintf(local_dc,"p%i.face",param_1);
                                        SysExplodParse((int)pFVar5,piVar7,local_dc);
                                        sprintf(local_dc,"p%i.facing",param_1);
                                        TPGetValueInt((int)pFVar5,local_dc,local_21b0);
                                        local_21b0 = local_21b0 + 1;
                                        piVar7 = piVar7 + 0x36;
                                        local_21b8 = local_21b8 + 0x36;
                                        local_21bc = local_21bc + 1;
                                        piVar8 = piVar8 + 1;
                                      } while ((int)param_1 < 4);
                                      iVar6 = TPGroupSeek((int)pFVar5,"turns face");
                                      if (iVar6 == -1) {
                                        piVar7 = g + 0x81d2;
                                        pcVar11 = "Missing turns face info";
                                        pFVar10 = param_1;
                                      }
                                      else {
                                        iVar6 = 0;
                                        piVar8 = piVar4 + 0x49f9;
                                        piVar4[0x4ad9] = 1;
                                        piVar4[0x4ada] = -1;
                                        local_2188 = piVar4 + 0x4b13;
                                        local_218c = piVar4 + 0x4af8;
                                        local_2190 = piVar4 + 0x4b31;
                                        local_2194 = piVar4 + 0x4b32;
                                        local_2198 = piVar4 + 0x4b2e;
                                        local_219c = piVar4 + 0x4b2f;
                                        piVar7 = piVar4 + 0x4a14;
                                        local_21a0 = (uint *)(piVar4 + 0x4ad9);
                                        local_21ac = piVar4 + 0x4add;
                                        local_21a8 = piVar8;
                                        do {
                                          iVar6 = iVar6 + 1;
                                          sprintf(local_dc,"p%i.pos",iVar6,piVar7);
                                          piVar1 = piVar8 + 0xdc;
                                          piVar2 = piVar8 + 0xd8;
                                          piVar8 = piVar8 + 1;
                                          TPScanf((int)pFVar5,local_dc,"%i,%i",piVar2,piVar1);
                                          sprintf(local_dc,"p%i.bg",iVar6);
                                          SysExplodParse((int)pFVar5,local_21a8,local_dc);
                                          sprintf(local_dc,"p%i.face",iVar6);
                                          SysExplodParse((int)pFVar5,piVar7,local_dc);
                                          sprintf(local_dc,"p%i.facing",iVar6);
                                          TPGetValueInt((int)pFVar5,local_dc,local_21a0);
                                          sprintf(local_dc,"p%i.teammate.pos",iVar6);
                                          TPScanf((int)pFVar5,local_dc,"%i,%i",local_2198,local_219c
                                                 );
                                          sprintf(local_dc,"p%i.teammate.spacing",iVar6);
                                          TPScanf((int)pFVar5,local_dc,"%i,%i",local_2190,local_2194
                                                 );
                                          sprintf(local_dc,"p%i.teammate.bg",iVar6);
                                          SysExplodParse((int)pFVar5,local_21ac,local_dc);
                                          sprintf(local_dc,"p%i.teammate.face",iVar6);
                                          SysExplodParse((int)pFVar5,local_218c,local_dc);
                                          sprintf(local_dc,"p%i.teammate.ko",iVar6);
                                          SysExplodParse((int)pFVar5,local_2188,local_dc);
                                          sprintf(local_dc,"p%i.teammate.facing",iVar6);
                                          TPGetValueInt((int)pFVar5,local_dc,local_21a0);
                                          local_2188 = local_2188 + 0x56;
                                          local_218c = local_218c + 0x56;
                                          local_2190 = local_2190 + 0x56;
                                          local_2194 = local_2194 + 0x56;
                                          local_2198 = local_2198 + 0x56;
                                          local_219c = local_219c + 0x56;
                                          local_21a0 = local_21a0 + 1;
                                          piVar7 = piVar7 + 0x36;
                                          local_21a8 = local_21a8 + 0x36;
                                          local_21ac = local_21ac + 0x56;
                                        } while (iVar6 < 2);
                                        iVar6 = TPGroupSeek((int)pFVar5,"name");
                                        if (iVar6 == -1) {
                                          piVar7 = g + 0x81d2;
                                          pcVar11 = "Missing name info";
                                          param_1 = extraout_EDX_01;
                                          pFVar10 = extraout_EDX_01;
                                        }
                                        else {
                                          local_217c = piVar4 + 0x4bf5;
                                          local_2180 = piVar4 + 0x4b89;
                                          piVar8 = piVar4 + 0x4c61;
                                          iVar6 = 0;
                                          piVar7 = piVar4 + 0x4c65;
                                          do {
                                            iVar6 = iVar6 + 1;
                                            sprintf(local_dc,"p%i.pos",iVar6,piVar8);
                                            TPScanf((int)pFVar5,local_dc,"%i,%i",piVar8,piVar7);
                                            sprintf(local_dc,"p%i.bg",iVar6);
                                            SysExplodParse((int)pFVar5,local_2180,local_dc);
                                            sprintf(local_dc,"p%i.name",iVar6);
                                            SysExplodParse((int)pFVar5,local_217c,local_dc);
                                            local_217c = local_217c + 0x1b;
                                            local_2180 = local_2180 + 0x1b;
                                            piVar8 = piVar8 + 1;
                                            piVar7 = piVar7 + 1;
                                          } while (iVar6 < 2);
                                          iVar6 = TPGroupSeek((int)pFVar5,"simul name");
                                          if (iVar6 == -1) {
                                            piVar7 = g + 0x81d2;
                                            pcVar11 = "Missing simul name info";
                                            param_1 = extraout_EDX_02;
                                            pFVar10 = extraout_EDX_02;
                                          }
                                          else {
                                            local_2170 = piVar4 + 0x4cd5;
                                            local_2174 = piVar4 + 0x4c69;
                                            piVar8 = piVar4 + 0x4d41;
                                            iVar6 = 0;
                                            piVar7 = piVar4 + 0x4d45;
                                            do {
                                              iVar6 = iVar6 + 1;
                                              sprintf(local_dc,"p%i.pos",iVar6,piVar8);
                                              TPScanf((int)pFVar5,local_dc,"%i,%i",piVar8,piVar7);
                                              sprintf(local_dc,"p%i.bg",iVar6);
                                              SysExplodParse((int)pFVar5,local_2174,local_dc);
                                              sprintf(local_dc,"p%i.name",iVar6);
                                              SysExplodParse((int)pFVar5,local_2170,local_dc);
                                              local_2170 = local_2170 + 0x1b;
                                              local_2174 = local_2174 + 0x1b;
                                              piVar8 = piVar8 + 1;
                                              piVar7 = piVar7 + 1;
                                            } while (iVar6 < 4);
                                            iVar6 = TPGroupSeek((int)pFVar5,"turns name");
                                            if (iVar6 == -1) {
                                              piVar7 = g + 0x81d2;
                                              pcVar11 = "Missing turns name info";
                                              param_1 = extraout_ECX_11;
                                              pFVar10 = extraout_ECX_11;
                                            }
                                            else {
                                              piVar8 = piVar4 + 0x4db5;
                                              local_2168 = piVar4 + 0x4d49;
                                              iVar6 = 0;
                                              piVar7 = piVar4 + 0x4e25;
                                              local_216c = piVar4 + 0x4e21;
                                              local_2164 = piVar8;
                                              do {
                                                iVar6 = iVar6 + 1;
                                                sprintf(local_dc,"p%i.pos",iVar6,piVar8);
                                                TPScanf((int)pFVar5,local_dc,"%i,%i",local_216c,
                                                        piVar7);
                                                sprintf(local_dc,"p%i.bg",iVar6);
                                                SysExplodParse((int)pFVar5,local_2168,local_dc);
                                                sprintf(local_dc,"p%i.name",iVar6);
                                                SysExplodParse((int)pFVar5,local_2164,local_dc);
                                                local_2164 = local_2164 + 0x1b;
                                                local_2168 = local_2168 + 0x1b;
                                                piVar8 = local_216c + 1;
                                                piVar7 = piVar7 + 1;
                                                local_216c = piVar8;
                                              } while (iVar6 < 4);
                                              pcVar11 = "time";
                                              piVar7 = local_2164;
                                              iVar6 = TPGroupSeek((int)pFVar5,"time");
                                              if (iVar6 == -1) {
                                                piVar7 = g + 0x81d2;
                                                pcVar11 = "Missing time info";
                                                param_1 = pFVar5;
                                                pFVar10 = pFVar5;
                                              }
                                              else {
                                                piVar4[0x4e61] = 0x3c;
                                                TPScanf((int)pFVar5,"pos","%i,%i",piVar4 + 0x4e5f,
                                                        piVar4 + 0x4e60,pcVar11,local_2164,piVar7);
                                                SysExplodParse((int)pFVar5,piVar4 + 0x4e29,"bg");
                                                param_1 = (FILE *)(piVar4 + 0x4e61);
                                                SysExplodParse((int)pFVar5,piVar4 + 0x4e44,"counter"
                                                              );
                                                TPGetValueInt((int)pFVar5,"framespercount",
                                                              (uint *)param_1);
                                                iVar6 = TPGroupSeek((int)pFVar5,"combo");
                                                if (iVar6 == -1) {
                                                  piVar7 = g + 0x81d2;
                                                  pcVar11 = "Missing combo info";
                                                  pFVar10 = param_1;
                                                }
                                                else {
                                                  piVar8 = piVar4 + 0x4e62;
                                                  piVar4[0x4e62] = 10;
                                                  piVar4[0x4e63] = 0x50;
                                                  piVar4[0x4e64] = -0x28;
                                                  piVar4[0x4e65] = 0x5a;
                                                  piVar4[0x4e66] = -1;
                                                  piVar4[0x4e6d] = 0x48206925;
                                                  piVar4[0x4e6e] = 0x217469;
                                                  param_1 = (FILE *)(piVar4 + 0x4e6d);
                                                  pcVar11 = "text.text";
                                                  piVar7 = piVar12;
                                                  __src = TPGetValue((int)pFVar5,"text.text");
                                                  if (__src != (char *)0x0) {
                                                    piVar12 = (int *)0x1f;
                                                    piVar7 = extraout_EDX_03;
                                                    strncpy((char *)param_1,__src,0x1f);
                                                    pcVar11 = __src;
                                                  }
                                                  TPScanf((int)pFVar5,"pos","%i,%i",piVar8,
                                                          piVar4 + 0x4e63,pcVar11,piVar12,piVar7);
                                                  TPGetValueInt((int)pFVar5,"start.x",
                                                                (uint *)(piVar4 + 0x4e64));
                                                  TPScanf((int)pFVar5,"counter.font","%i,%i",
                                                          piVar4 + 0x4e66,piVar4 + 0x4e67);
                                                  TPGetValueInt((int)pFVar5,"counter.shake",
                                                                (uint *)(piVar4 + 0x4e68));
                                                  TPScanf((int)pFVar5,"text.font","%i,%i",
                                                          piVar4 + 0x4e69,piVar4 + 0x4e6a);
                                                  TPScanf((int)pFVar5,"text.offset","%i,%i",
                                                          piVar4 + 0x4e6b,piVar4 + 0x4e6c);
                                                  TPGetValueInt((int)pFVar5,"displaytime",
                                                                (uint *)(piVar4 + 0x4e65));
                                                  iVar6 = TPGroupSeek((int)pFVar5,"round");
                                                  if (iVar6 == -1) {
                                                    piVar7 = g + 0x81d2;
                                                    pcVar11 = "Missing round info";
                                                    pFVar10 = param_1;
                                                  }
                                                  else {
                                                    piVar4[0x4e77] = 0x1e;
                                                    piVar4[0x4e78] = 0x46;
                                                    piVar4[0x5038] = 0xa0;
                                                    piVar4[0x4fdf] = 0xa0;
                                                    piVar4[0x4fc0] = 0xa0;
                                                    piVar4[0x5039] = 0x78;
                                                    piVar4[0x4fe0] = 0x78;
                                                    piVar4[0x4fc1] = 0x78;
                                                    piVar4[0x4fc9] = 0x68676946;
                                                    *(undefined2 *)(piVar4 + 0x4fca) = 0x2174;
                                                    *(undefined1 *)((int)piVar4 + 0x13f2a) = 0;
                                                    piVar4[0x4fe8] = 0x4f2e4b;
                                                    piVar4[0x4fa4] = 0;
                                                    piVar4[0x4fd5] = 0;
                                                    piVar4[0x502a] = 0;
                                                    piVar4[0x5089] = 0x3c;
                                                    piVar4[0x508b] = 0x3c;
                                                    piVar4[0x508c] = 0;
                                                    piVar4[0x508d] = 10;
                                                    piVar4[0x508e] = 0x2d;
                                                    piVar4[0x508f] = 0x96;
                                                    piVar4[0x4e75] = 2;
                                                    piVar4[0x4e76] = 1;
                                                    TPGetValueInt((int)pFVar5,"match.wins",
                                                                  (uint *)(piVar4 + 0x4e75));
                                                    TPGetValueInt((int)pFVar5,"match.maxdrawgames",
                                                                  (uint *)(piVar4 + 0x4e76));
                                                    TPGetValueInt((int)pFVar5,"start.waittime",
                                                                  (uint *)(piVar4 + 0x4e77));
                                                    puVar13 = (uint *)(piVar4 + 0x4e78);
                                                    pcVar11 = "intro.time";
                                                    TPGetValueInt((int)pFVar5,"intro.time",puVar13);
                                                    TPScanf((int)pFVar5,"pos","%i,%i",
                                                            piVar4 + 0x4e79,piVar4 + 0x4e7a,pcVar11,
                                                            puVar13,piVar8);
                                                    SysExplodParse((int)pFVar5,piVar4 + 0x4e7b,
                                                                   "round.default");
                                                    StripDoublePercent((char *)(piVar4 + 0x4e8a));
                                                    TPGetValueInt((int)pFVar5,"round.time",
                                                                  (uint *)(piVar4 + 0x4fa4));
                                                    piVar4[0x4fa5] = piVar4[0x4fa4];
                                                    TPGetValueInt((int)pFVar5,"round.sndtime",
                                                                  (uint *)(piVar4 + 0x4fa5));
                                                    local_2154 = piVar4 + 0x4eb1;
                                                    local_2158 = piVar4 + 0x4fa7;
                                                    local_215c = piVar4 + 0x4fb1;
                                                    local_2160 = 0x4c4;
                                                    iVar6 = 1;
                                                    do {
                                                      *(undefined4 *)
                                                       (local_2160 + 4 + (int)(piVar4 + 0x4e75)) =
                                                           0xffffffff;
                                                      sprintf(local_dc,"round%i.snd",iVar6,
                                                              local_2160);
                                                      TPScanf((int)pFVar5,local_dc,"%i,%i",
                                                              local_2158,local_215c);
                                                      iVar9 = iVar6 + 1;
                                                      sprintf(local_dc,"round%i",iVar6);
                                                      SysExplodParse((int)pFVar5,local_2154,local_dc
                                                                    );
                                                      local_2154 = local_2154 + 0x1b;
                                                      local_2158 = local_2158 + 1;
                                                      local_215c = local_215c + 1;
                                                      local_2160 = local_2160 + 4;
                                                      iVar6 = iVar9;
                                                    } while (iVar9 < 10);
                                                    piVar4[0x4fd7] = -1;
                                                    SysExplodParse((int)pFVar5,piVar4 + 0x4fba,
                                                                   "fight");
                                                    TPGetValueInt((int)pFVar5,"fight.time",
                                                                  (uint *)(piVar4 + 0x4fd5));
                                                    piVar4[0x4fd6] = piVar4[0x4fd5];
                                                    puVar13 = (uint *)(piVar4 + 0x4fd6);
                                                    pcVar11 = "fight.sndtime";
                                                    TPGetValueInt((int)pFVar5,"fight.sndtime",
                                                                  puVar13);
                                                    TPScanf((int)pFVar5,"fight.snd","%i,%i",
                                                            piVar4 + 0x4fd7,piVar4 + 0x4fd8,pcVar11,
                                                            puVar13,local_2158);
                                                    TPGetValueInt((int)pFVar5,"ctrl.time",
                                                                  (uint *)(piVar4 + 0x508a));
                                                    piVar4[0x5030] = -1;
                                                    piVar4[0x502e] = -1;
                                                    piVar4[0x502c] = -1;
                                                    SysExplodParse((int)pFVar5,piVar4 + 0x4fd9,"KO")
                                                    ;
                                                    SysExplodParse((int)pFVar5,piVar4 + 0x4ff4,
                                                                   &DAT_08278e31);
                                                    SysExplodParse((int)pFVar5,piVar4 + 0x500f,
                                                                   &DAT_08278e35);
                                                    TPGetValueInt((int)pFVar5,"KO.time",
                                                                  (uint *)(piVar4 + 0x502a));
                                                    piVar4[0x502b] = piVar4[0x502a];
                                                    TPGetValueInt((int)pFVar5,"KO.sndtime",
                                                                  (uint *)(piVar4 + 0x502b));
                                                    TPScanf((int)pFVar5,"KO.snd","%i,%i",
                                                            piVar4 + 0x502c,piVar4 + 0x502d);
                                                    TPScanf((int)pFVar5,"DKO.snd","%i,%i",
                                                            piVar4 + 0x502e,piVar4 + 0x502f);
                                                    TPScanf((int)pFVar5,"TO.snd","%i,%i",
                                                            piVar4 + 0x5030,piVar4 + 0x5031);
                                                    piVar4[0x502a] = piVar4[0x502a] + piVar4[0x508d]
                                                    ;
                                                    piVar4[0x502b] = piVar4[0x502b] + piVar4[0x508d]
                                                    ;
                                                    TPGetValueInt((int)pFVar5,"win.time",
                                                                  (uint *)(piVar4 + 0x5089));
                                                    SysExplodParse((int)pFVar5,piVar4 + 0x5032,"win"
                                                                  );
                                                    SysExplodParse((int)pFVar5,piVar4 + 0x504d,
                                                                   &DAT_08278e63);
                                                    SysExplodParse((int)pFVar5,piVar4 + 0x5068,
                                                                   "draw");
                                                    piVar4[0x5087] = -1;
                                                    piVar4[0x5085] = -1;
                                                    piVar4[0x5083] = -1;
                                                    TPScanf((int)pFVar5,"win.snd","%i,%i",
                                                            piVar4 + 0x5083,piVar4 + 0x5084);
                                                    TPScanf((int)pFVar5,"lose.snd","%i,%i",
                                                            piVar4 + 0x5085,piVar4 + 0x5086);
                                                    TPScanf((int)pFVar5,"draw.snd","%i,%i",
                                                            piVar4 + 0x5087,piVar4 + 0x5088);
                                                    TPGetValueInt((int)pFVar5,"slow.time",
                                                                  (uint *)(piVar4 + 0x508b));
                                                    TPGetValueInt((int)pFVar5,"over.waittime",
                                                                  (uint *)(piVar4 + 0x508c));
                                                    TPGetValueInt((int)pFVar5,"over.hittime",
                                                                  (uint *)(piVar4 + 0x508d));
                                                    TPGetValueInt((int)pFVar5,"over.wintime",
                                                                  (uint *)(piVar4 + 0x508e));
                                                    TPGetValueInt((int)pFVar5,"over.time",
                                                                  (uint *)(piVar4 + 0x508f));
                                                    iVar6 = TPGroupSeek((int)pFVar5,"winicon");
                                                    if (iVar6 == -1) {
                                                      piVar7 = g + 0x81d2;
                                                      pcVar11 = "Missing winicon info";
                                                      param_1 = extraout_EDX_04;
                                                      pFVar10 = extraout_EDX_04;
                                                    }
                                                    else {
                                                      piVar12 = piVar4 + 0x5090;
                                                      local_212c = piVar4 + 0x519e;
                                                      local_2134 = piVar4 + 0x5168;
                                                      local_2130 = piVar4 + 0x5183;
                                                      local_2138 = piVar4 + 0x5117;
                                                      local_213c = piVar4 + 0x5132;
                                                      local_2140 = piVar4 + 0x514d;
                                                      local_2144 = piVar4 + 0x50fc;
                                                      piVar7 = piVar4 + 0x50c6;
                                                      iVar6 = 0;
                                                      local_2150 = piVar12;
                                                      local_214c = piVar7;
                                                      local_2148 = piVar4 + 0x50e1;
                                                      do {
                                                        iVar6 = iVar6 + 1;
                                                        sprintf(local_dc,"p%i.pos",iVar6,piVar7);
                                                        TPScanf((int)pFVar5,local_dc,"%i,%i",
                                                                piVar12 + 0x21c,piVar12 + 0x21e);
                                                        sprintf(local_dc,"p%i.iconoffset",iVar6);
                                                        piVar7 = piVar12 + 0x222;
                                                        piVar8 = piVar12 + 0x220;
                                                        piVar12 = piVar12 + 1;
                                                        TPScanf((int)pFVar5,local_dc,"%i,%i",piVar8,
                                                                piVar7);
                                                        sprintf(local_dc,"p%i.counter",iVar6);
                                                        SysExplodParse((int)pFVar5,local_2150,
                                                                       local_dc);
                                                        sprintf(local_dc,"p%i.n",iVar6);
                                                        SysExplodParse((int)pFVar5,local_214c,
                                                                       local_dc);
                                                        sprintf(local_dc,"p%i.s",iVar6);
                                                        SysExplodParse((int)pFVar5,local_2148,
                                                                       local_dc);
                                                        sprintf(local_dc,"p%i.h",iVar6);
                                                        SysExplodParse((int)pFVar5,local_2144,
                                                                       local_dc);
                                                        sprintf(local_dc,"p%i.throw",iVar6);
                                                        SysExplodParse((int)pFVar5,local_2140,
                                                                       local_dc);
                                                        sprintf(local_dc,"p%i.t",iVar6);
                                                        SysExplodParse((int)pFVar5,local_213c,
                                                                       local_dc);
                                                        sprintf(local_dc,"p%i.c",iVar6);
                                                        SysExplodParse((int)pFVar5,local_2138,
                                                                       local_dc);
                                                        sprintf(local_dc,"p%i.suicide",iVar6);
                                                        SysExplodParse((int)pFVar5,local_2134,
                                                                       local_dc);
                                                        sprintf(local_dc,"p%i.teammate",iVar6);
                                                        SysExplodParse((int)pFVar5,local_2130,
                                                                       local_dc);
                                                        sprintf(local_dc,"p%i.perfect",iVar6);
                                                        SysExplodParse((int)pFVar5,local_212c,
                                                                       local_dc);
                                                        local_212c = local_212c + 0xf3;
                                                        local_2130 = local_2130 + 0xf3;
                                                        local_2134 = local_2134 + 0xf3;
                                                        local_2138 = local_2138 + 0xf3;
                                                        local_213c = local_213c + 0xf3;
                                                        local_2140 = local_2140 + 0xf3;
                                                        local_2144 = local_2144 + 0xf3;
                                                        piVar7 = local_2148 + 0xf3;
                                                        local_214c = local_214c + 0xf3;
                                                        local_2150 = local_2150 + 0x1b;
                                                        local_2148 = piVar7;
                                                      } while (iVar6 < 2);
                                                      TPGetValueInt((int)pFVar5,"useiconupto",
                                                                    (uint *)(piVar4 + 0x52b4));
                                                      if (9 < piVar4[0x52b4]) {
                                                        piVar4[0x52b4] = 9;
                                                      }
                                                      TPFree(&pFVar5->_flags);
                                                      piVar12 = ExplodArrayNew(g[0x7573],g[0x413d]);
                                                      piVar7 = g;
                                                      g[0x52be] = (int)piVar12;
                                                      if (piVar12 == (int *)0x0) {
                                                        piVar7 = piVar7 + 0x81d2;
                                                        pcVar11 = "Can\'t allocate explods";
                                                        param_1 = extraout_ECX_12;
                                                        pFVar10 = extraout_ECX_12;
                                                      }
                                                      else {
                                                        piVar12 = ExplodArrayNew(piVar7[0x7574],0);
                                                        piVar7 = g;
                                                        g[0x52bf] = (int)piVar12;
                                                        if (piVar12 != (int *)0x0) {
                                                          return 1;
                                                        }
                                                        piVar7 = piVar7 + 0x81d2;
                                                        pcVar11 = "Can\'t allocate sysexplods";
                                                        param_1 = pFVar5;
                                                        pFVar10 = pFVar5;
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
LAB_0809bc03:
  sprintf((char *)piVar7,pcVar11,param_1,pFVar10);
  return 0;
}
#undef local_2248
#undef local_2244
#undef local_2240
#undef local_223c
#undef local_2238
#undef local_2234
#undef local_2230
#undef local_222c
#undef local_2228
#undef local_2224
#undef local_2220
#undef local_221c
#undef local_2218
#undef local_2214
#undef local_2210
#undef local_220c
#undef local_2208
#undef local_2204
#undef local_2200
#undef local_21fc
#undef local_21f8
#undef local_21f4
#undef local_21f0
#undef local_21ec
#undef local_21e8
#undef local_21e4
#undef local_21e0
#undef local_21dc
#undef local_21d8
#undef local_21d4
#undef local_21d0
#undef local_21cc
#undef local_21c8
#undef local_21c0
#undef local_21bc
#undef local_21b8
#undef local_21b0
#undef local_21ac
#undef local_21a8
#undef local_21a0
#undef local_219c
#undef local_2198
#undef local_2194
#undef local_2190
#undef local_218c
#undef local_2188
#undef local_2180
#undef local_217c
#undef local_2174
#undef local_2170
#undef local_216c
#undef local_2168
#undef local_2164
#undef local_2160
#undef local_215c
#undef local_2158
#undef local_2154
#undef local_2150
#undef local_214c
#undef local_2148
#undef local_2144
#undef local_2140
#undef local_213c
#undef local_2138
#undef local_2134
#undef local_2130
#undef local_212c
#undef local_20fc
#undef local_10fc
#undef local_fc
#undef local_dc

/* GameFreeFightData @ 0x0809bc20, 202 bytes */
void GameFreeFightData(void)

{
  void *pvVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0x10520;
  iVar3 = 9;
  piVar2 = g;
  do {
    pvVar1 = *(void **)(iVar4 + 0xc + (int)piVar2);
    if (pvVar1 != (void *)piVar2[0x413a]) {
      FontFree(pvVar1);
      piVar2 = g;
    }
    iVar4 = iVar4 + 4;
    iVar3 = iVar3 + -1;
  } while (-1 < iVar3);
  AnimRCFree((int *)piVar2[0x414a]);
  SpriteArrayFree((int *)g[0x4149]);
  SndArrayFree((undefined4 *)g[0x4156]);
  SndArrayFree((undefined4 *)g[0x4155]);
  SpriteArrayFree((int *)g[0x4147]);
  AnimRCFree((int *)g[0x4148]);
  ExplodArrayFree((int *)g[0x52bf]);
  ExplodArrayFree((int *)g[0x52be]);
  return;
}

/* GameVarInit @ 0x0809bcf0, 1132 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 7 stack locals placed at their original offsets in a 0x30-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 GameVarInit(void)

{
  int *piVar1;
  bool bVar2;
  char *pcVar3;
  FILE *stream;
  tm *ptVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined3 extraout_var;
  uint __seed;
  int *__s;
  int *piVar7;
  int *piVar8;
  unsigned char ghidra_frame[0x30] __attribute__((aligned(16)));
#define local_30 (*(time_t *)(ghidra_frame + 0x0))
#define local_2c (*(int *)(ghidra_frame + 0x4))
#define local_28 (*(int *)(ghidra_frame + 0x8))
#define local_24 (*(int *)(ghidra_frame + 0xc))
#define local_1c (*(int **)(ghidra_frame + 0x14))
#define local_18 (*(int *)(ghidra_frame + 0x18))
#define local_14 (*(int **)(ghidra_frame + 0x1c))
  
  pcVar3 = getcwd((char *)g,0xfff);
  piVar7 = g;
  if (pcVar3 == (char *)0x0) {
LAB_0809bfc7:
    GameVarDeInit();
  }
  else {
    g[0x804] = MUGENDATE_Y;
    piVar7[0x802] = MUGENDATE_M;
    piVar7[0x803] = MUGENDATE_D;
    piVar7[0x33ae] = 0;
    stream = fopen("_mugen__.tmp","wb");
    if (stream != (FILE *)0x0) {
      g[0x801] = 1;
      fclose(stream);
      remove("_mugen__.tmp");
    }
    time(&local_30);
    ptVar4 = gmtime(&local_30);
    piVar7 = (int *)(ptVar4->tm_year + 0x76c);
    piVar8 = (int *)(ptVar4->tm_mon + 1);
    local_18 = ptVar4->tm_mday;
    local_24 = MUGENEXPDATE_Y;
    local_2c = MUGENEXPDATE_M;
    local_28 = MUGENEXPDATE_D;
    local_1c = piVar8;
    local_14 = piVar7;
    iVar5 = MDYDateCmp((int)piVar8,local_18,(int)piVar7,MUGENEXPDATE_M,MUGENEXPDATE_D,MUGENEXPDATE_Y
                      );
    if (0 < iVar5) {
      g[0x74e6] = 1;
    }
    iVar5 = V_AllocDepth(0x140,0xf0,0x10);
    piVar1 = g;
    g[0x4136] = iVar5;
    if (iVar5 == 0) {
      GameVarDeInit();
      __s = g + 0x81d2;
      pcVar3 = "Can\'t create screen buffer.";
      piVar7 = piVar8;
    }
    else {
      piVar1 = (int *)piVar1[0x4136];
      V_SetBuf(piVar1,0);
      W_Cls(0);
      piVar8 = g + 0x7559;
      g[0x4139] = g[0x4136];
      if (*piVar8 != 0) {
        iVar5 = V_AllocDepth(0x280,0x1e0,0x10);
        piVar8 = g;
        g[0x4138] = iVar5;
        if (iVar5 == 0) {
          piVar7 = (int *)GameVarDeInit();
          pcVar3 = "Can\'t create screen buffer.";
          __s = g + 0x81d2;
          goto LAB_0809c142;
        }
        piVar8[0x4139] = iVar5;
      }
      puVar6 = PRSprArrayNew(g[0x7572]);
      g[0x413d] = (int)puVar6;
      if (puVar6 == (undefined4 *)0x0) {
        GameVarDeInit();
        __s = g + 0x81d2;
        pcVar3 = "Can\'t create priority sprites layer 1.";
      }
      else {
        iVar5 = AnimPerArrayNew(0x20);
        piVar8 = g;
        g[0x413c] = iVar5;
        if (iVar5 == 0) {
          GameVarDeInit();
          __s = g + 0x81d2;
          pcVar3 = "Can\'t create persistent animation array.";
          piVar7 = piVar1;
        }
        else {
          puVar6 = GameAftImgArrayNew(piVar8[0x7571],0x3c);
          g[0x413f] = (int)puVar6;
          if (puVar6 == (undefined4 *)0x0) {
            piVar7 = (int *)GameVarDeInit();
            pcVar3 = "Can\'t init afterimages.";
            __s = g + 0x81d2;
          }
          else {
            iVar5 = ecalloc(1,0xc);
            piVar8 = g;
            g[0x413e] = iVar5;
            if (iVar5 == 0) {
              GameVarDeInit();
              __s = g + 0x81d2;
              pcVar3 = "Can\'t create palgroup array.";
            }
            else {
              bVar2 = IntCircBufInit(piVar8 + 0x7391,0x20);
              piVar8 = g;
              if (GHIDRA_ZEXT8(bVar2) == 0) goto LAB_0809bfc7;
              g[0x4143] = g[0x755a];
              piVar8[0x52bd] = 1;
              memcpy(piVar8 + 0x52c0,"system.def",0xb);
              piVar1 = g;
              piVar8 = g + 0x7575;
              g[0x7396] = *piVar8;
              piVar1[0x7395] = *piVar8 + 4;
              *(undefined4 *)((int)piVar1 + 0x15aff) = 0x61746164;
              *(undefined2 *)((int)piVar1 + 0x15b03) = 0x2f;
              piVar1[0x7304] = 0;
              piVar1[0x7305] = -1;
              piVar1[0x7307] = 0;
              piVar1[0x7306] = 0;
              piVar1[0x7310] = 0;
              piVar1[0x730f] = 0;
              piVar1[0x7312] = 0;
              piVar1[0x7311] = 0;
              piVar1[0x7316] = 0;
              piVar1[0x7315] = 0;
              piVar1[0x4135] = 0;
              piVar1[0x741a] = 1;
              piVar1[0x741b] = 1;
              piVar1[0x741c] = 0;
              piVar1[0x741d] = 0;
              piVar1[0x745a] = -1;
              piVar1[0x7397] = 4;
              piVar1[0x33af] = 1;
              piVar1[0x33b0] = 2;
              __seed = time((time_t *)0x0);
              g[0x730a] = __seed;
              srandom(__seed);
              piVar8 = ClipboardNew(0x4d,8);
              g[0x81d1] = (int)piVar8;
              if (piVar8 != (int *)0x0) {
                return 1;
              }
              GameVarDeInit();
              __s = g + 0x81d2;
              pcVar3 = "Can\'t create clipboard.";
            }
          }
        }
      }
    }
LAB_0809c142:
    sprintf((char *)__s,pcVar3,piVar7,piVar7);
  }
  return 0;
}
#undef local_30
#undef local_2c
#undef local_28
#undef local_24
#undef local_1c
#undef local_18
#undef local_14

/* GameVarLoadFonts @ 0x0809c160, 153 bytes */
undefined4 GameVarLoadFonts(void)

{
  int iVar1;
  char *__src;
  
  iVar1 = FontReadFile("font/f-4x6.fnt");
  g[0x413a] = iVar1;
  if (iVar1 == 0) {
    ErrorSet(1);
    __src = "f-4x6.fnt";
  }
  else {
    iVar1 = FontReadFile("font/f-6x9.fnt");
    g[0x413b] = iVar1;
    if (iVar1 != 0) {
      return 1;
    }
    ErrorSet(1);
    __src = "f-6x9.fnt";
  }
  memcpy(g + 0x81d2,__src,10);
  GameVarDeInit();
  return 0;
}

/* GameVarDeInit @ 0x0809c200, 273 bytes */
undefined4 GameVarDeInit(void)

{
  undefined4 extraout_EAX;
  undefined4 uVar1;
  
  uVar1 = 0;
  if (g != (int *)0x0) {
    FontFree((void *)g[0x413a]);
    FontFree((void *)g[0x413b]);
    IntCircBufDeInit(g + 0x7391);
    free((void *)g[0x413e]);
    PRSprArrayFree((undefined4 *)g[0x413d]);
    GameAftImgArrayFree((void *)g[0x413f]);
    AnimPerArrayFree((undefined4 *)g[0x413c]);
    V_DeAlloc(g[0x4136]);
    if (g[0x4137] != 0) {
      V_DeAlloc(g[0x4137]);
    }
    if (g[0x4138] != 0) {
      V_DeAlloc(g[0x4138]);
    }
    if ((undefined4 *)g[0x81d1] != (undefined4 *)0x0) {
      ClipboardFree((undefined4 *)g[0x81d1]);
    }
    free(g);
    g = (int *)0x0;
    uVar1 = extraout_EAX;
  }
  return uVar1;
}

/* GameAftImgArrayNew @ 0x0809c320, 140 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0xa0-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 * GameAftImgArrayNew(size_t param_1,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  unsigned char ghidra_frame[0xa0] __attribute__((aligned(16)));
#define aiStack_9c (*(int (*)[35])(ghidra_frame + 0x4))
  
  puVar1 = ArrayNew(param_1,0x7c,0);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    iVar3 = 0;
    if (0 < (int)param_1) {
      do {
        piVar4 = aiStack_9c;
        for (iVar2 = 0x1f; iVar2 != 0; iVar2 = iVar2 + -1) {
          *piVar4 = 0;
          piVar4 = piVar4 + 1;
        }
        iVar2 = AftImgInit(aiStack_9c,param_2);
        if (iVar2 == 0) {
          GameAftImgArrayFree(puVar1);
          return (undefined4 *)0x0;
        }
        iVar2 = iVar3 + 1;
        ArrayAdd((int)puVar1,aiStack_9c,0,iVar3);
        iVar3 = iVar2;
      } while (iVar2 < (int)param_1);
    }
  }
  return puVar1;
}
#undef aiStack_9c

/* GameAftImgArrayFree @ 0x0809c3b0, 68 bytes
 * REVIEW: pid-unaff_ */
undefined4 GameAftImgArrayFree(void *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  undefined4 unaff_EBX;
  int iVar3;
  int iVar4;
  
  if (param_1 != (void *)0x0) {
    iVar3 = 0;
    if (0 < *(int *)((int)param_1 + 0xc)) {
      do {
        iVar4 = iVar3 + 1;
        piVar1 = (int *)ArrayAccessGrpItem((int)param_1,0,iVar3);
        AftImgDeInit(piVar1);
        iVar3 = iVar4;
      } while (iVar4 < *(int *)((int)param_1 + 0xc));
    }
    uVar2 = ArrayFree(param_1);
    return uVar2;
  }
  return unaff_EBX;
}

/* SwitchCallbacksInit @ 0x0809c400, 1 bytes */
void SwitchCallbacksInit(void)

{
  return;
}

/* SwitchCallbacksDeInit @ 0x0809c410, 1 bytes */
void SwitchCallbacksDeInit(void)

{
  return;
}

/* SwitchAwayCallback @ 0x0809c420, 20 bytes */
void SwitchAwayCallback(void)

{
  g[0x74e7] = 0;
  KBSuspend();
  return;
}

/* SwitchBackCallback @ 0x0809c440, 36 bytes */
void SwitchBackCallback(void)

{
  g[0x74e7] = 1;
  KBResume();
  KBRefreshflags();
  UInpRefreshFlags();
  return;
}

