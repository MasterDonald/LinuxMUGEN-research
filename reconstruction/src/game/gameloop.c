/*
 * gameloop.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0808fdc0-0x080980ce, 39 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"

extern byte framestep_0 __asm__("D_08287a70"); /* file-static 0x08287a70 */

/* GameLoop @ 0x0808fdc0, 4927 bytes
 * REVIEW: pid-in_stack_
 * FIXUP: rewrote 1 PalGrpFlag by-value loads
 * FIXUP: 3 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: PalGrpMakeFlag result written into the argument area: given explicit temporaries pgf_fffffb88
 * FIXUP: frame emulation: 2 stack locals placed at their original offsets in a 0x440-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
undefined4 GameLoop(int param_1)

{
  PalGrpFlag pgf_fffffb88;
  int *piVar1;
  int iVar2;
  int iVar3;
  PalGrpFlag f;
  PalGrpFlag f_00;
  undefined4 uVar4;
  bool bVar5;
  undefined3 extraout_var;
  int iVar6;
  undefined3 extraout_var_00;
  uint *puVar7;
  float10 fVar8;
  undefined3 extraout_var_01;
  int iVar9;
  byte bVar10;
  byte bVar11;
  bool bVar12;
  int *piVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  uint in_stack_fffffb88;
  uint in_stack_fffffb8c;
  uint uVar17;
  int *piVar18;
  int *piVar19;
  int iVar20;
  unsigned char ghidra_frame[0x440] __attribute__((aligned(16)));
#define aiStack_43c (*(int (*)[256])(ghidra_frame + 0x4))
#define local_3c (*(PalGrpFlag (*)[2])(ghidra_frame + 0x404))
  
  uVar4 = _rgb_r_shift_16;
  piVar18 = g;
  g[0x33b7] = param_1;
  piVar18[0x4135] = 0;
  bVar10 = (byte)_rgb_g_shift_16;
  bVar11 = (byte)_rgb_b_shift_16;
  piVar18[0x7316] = 0;
  piVar18[0x7315] = 0;
  if (piVar18[0x7559] == 4) {
    piVar18 = (int *)piVar18[0x4138];
  }
  else {
    piVar18 = (int *)piVar18[0x4136];
  }
  V_SetBuf(piVar18,0);
  W_Cls(0);
  piVar19 = (int *)0x0;
  piVar18 = (int *)0x0;
  uVar17 = 0x808fe84;
  W_Define(0,0,V_Width - 1,V_Height - 1);
  FrameSkipReset();
  piVar13 = g;
  if (g[0x82d3] == 0) goto LAB_0808fec1;
  g[0x7305] = 2000;
  piVar13[0x82d2] = 1;
  iVar9 = piVar13[0x7304];
  do {
    if (9999 < iVar9) {
LAB_080910a2:
      iVar9 = PrecacheIsRunning();
      if ((iVar9 != 0) && ((g[0x4135] != 0 || (g[0x33b3] == 0)))) {
        PrecacheRequestCancel();
        PrecacheFinish();
      }
      g[0x33b7] = 0;
      FrameSkipReset();
      MasterPalReset();
      return 1;
    }
LAB_0808fee6:
    if (piVar13[0x82d4] != 0) {
      PrecacheRequestCancel();
      PrecacheFinish();
      GameRoundReset();
      piVar13 = g;
      g[0x82d4] = 0;
    }
    if (piVar13[0x82d5] != 0) {
      PrecacheRequestCancel();
      PrecacheFinish();
      iVar9 = GameReloadStage();
      if (iVar9 == 0) {
        return 0;
      }
      g[0x82d5] = 0;
    }
    bVar5 = GameModeInPassiveFightScreen();
    if (GHIDRA_ZEXT8(bVar5) == 0) {
      if ((g[0x10ae] == 0) && (*(char *)((int)g + 0x1d391) != '\0')) {
        BGMPause(g + 0x10aa);
      }
      if ((g[0x10ae] != 0) && (*(char *)((int)g + 0x1d391) == '\0')) {
        BGMResume(g + 0x10aa);
      }
    }
    BGMPoll(g + 0x10aa);
    if (g[0x7559] == 4) {
      V_SetBuf((int *)g[0x4136],0);
      BGArraySetViewScale(g[0x6ed4],1);
    }
    PRSprArrayClear((int *)g[0x413d]);
    piVar13 = g;
    iVar9 = g[0x7315];
    iVar14 = g[0x7311];
    iVar16 = g[0x7316];
    iVar2 = g[0x7312];
    if (g[0x7309] == 0) {
      piVar1 = g + 0x7503;
      iVar15 = 1;
      g[0x74f3] = -1;
      if (*piVar1 < 1) {
        do {
          iVar15 = iVar15 + -1;
          if (iVar15 < 0) goto LAB_0809008d;
        } while (g[iVar15 * 9 + 0x74fa] < 1);
        g[0x74f3] = iVar15;
      }
      else {
        piVar13[0x74f3] = 1;
      }
    }
LAB_0809008d:
    GameInputUpdate();
    piVar13 = g;
    iVar15 = g[0x750c];
    if ((0 < iVar15) && (g[0x7309] == 0)) {
      if (0 < g[0x750d]) {
        iVar15 = -100;
      }
      g[0x750d] = g[0x750d] + iVar15;
    }
    if (piVar13[0x7309] == 0) {
      PalGrpResetPalette();
      piVar13 = g;
    }
    piVar1 = g;
    if (((piVar13[0x7309] == 0) && (iVar15 = piVar13[0x74f3], iVar15 != -1)) &&
       (0 < piVar13[iVar15 * 9 + 0x74fa])) {
      if (piVar13[0x750d] == 0) {
        piVar13[iVar15 * 9 + 0x74fa] = piVar13[iVar15 * 9 + 0x74fa] + -1;
        piVar13 = piVar1;
      }
      if ((piVar13[iVar15 * 9 + 0x74fa] != 0) && (piVar13[iVar15 * 9 + 0x74f9] != 0)) {
        PalGrpMakeFlag(local_3c,0xb00,0);
        f.w[1] = local_3c[0].w[1];
        f.w[0] = local_3c[0].w[0];
        f.w[2] = local_3c[0].w[2];
        f.w[3] = local_3c[0].w[3];
        f.w[4] = local_3c[0].w[4];
        in_stack_fffffb88 = local_3c[0].w[1];
        in_stack_fffffb8c = local_3c[0].w[2];
        PalGrpSetMul(f,0x50,0x50,0x80);
        piVar19 = (int *)g[iVar15 * 9 + 0x74f5];
        piVar18 = (int *)g[iVar15 * 9 + 0x74f4];
        uVar17 = 0x80901cd;
        f_00.w[1] = (uint)piVar19;
        f_00.w[0] = (uint)piVar18;
        f_00.w[2] = g[iVar15 * 9 + 0x74f6];
        f_00.w[3] = g[iVar15 * 9 + 0x74f7];
        f_00.w[4] = g[iVar15 * 9 + 0x74f8];
        PalGrpSetMul(f_00,0x80,0x80,0xc0);
      }
    }
    iVar20 = 1;
    iVar15 = 0;
    PalGrpMakeFlag(&pgf_fffffb88,0x100,0);
    PalFXUpdate(g + 0x6ed5,pgf_fffffb88.w[0],pgf_fffffb88.w[1],pgf_fffffb88.w[2],pgf_fffffb88.w[3],pgf_fffffb88.w[4],iVar15,iVar20);
    iVar15 = g[0x745a];
    piVar18 = g;
    if (g[0x7459] <= iVar15) {
      iVar20 = iVar15 * 4 + 0x1cf60;
      do {
        iVar6 = *(int *)(iVar20 + 4 + (int)piVar18);
        if ((iVar6 == 0) || (bVar5 = true, *(int *)(iVar6 + 0x158) == 0)) {
          bVar5 = false;
        }
        if ((bVar5) &&
           (iVar6 = PalGrpFlagIsNonZero(*(PalGrpFlag *)(*(int *)(iVar20 + 4 + (int)piVar18) + 0x25c8)),
           piVar18 = g, iVar6 != 0)) {
          iVar6 = 0;
          if ((g[0x74f3] == -1) ||
             (*(int *)(*(int *)(iVar20 + 4 + (int)g) + 0x1dc + g[0x74f3] * 4) != 0)) {
            iVar6 = 1;
          }
          iVar3 = *(int *)((int)g + iVar20 + 4);
          PalFXUpdate((int *)(*(int *)((int)g + iVar20 + 4) + 0x25dc),*(int *)(iVar3 + 0x25c8),
                      *(int *)(iVar3 + 0x25cc),*(int *)(iVar3 + 0x25d0),*(int *)(iVar3 + 0x25d4),
                      *(int *)(iVar3 + 0x25d8),0,iVar6);
          piVar18 = g;
        }
        iVar15 = iVar15 + -1;
        iVar20 = iVar20 + -4;
      } while (piVar18[0x7459] <= iVar15);
    }
    piVar18 = piVar18 + 0x6ee4;
    uVar17 = 0x8090340;
    piVar19 = (int *)local_3c[0].w[0];
    PalFXUpdate(piVar18,local_3c[0].w[0],local_3c[0].w[1],local_3c[0].w[2],local_3c[0].w[3],
                local_3c[0].w[4],1,1);
    iVar15 = GameUpdate();
    if (iVar15 == 0) {
      if (g[0x7309] == 0) {
        ExplodArrayUpdate((int *)g[0x52bf]);
      }
      bVar5 = GameModeInPassiveFightScreen();
      if ((((GHIDRA_ZEXT8(bVar5) == 0) || ((g[0x7541] == 0 && (g[0x7542] == 1)))) &&
          ((g[0x74f3] == -1 || (g[g[0x74f3] * 9 + 0x74fb] == 0)))) &&
         ((g[0x7309] == 0 && (g[0x750d] == 0)))) {
        BGArrayUpdate(g[0x6ed4]);
      }
      if (((g[0x7309] == 0) && (g[0x750d] == 0)) && (0 < g[0x4146])) {
        g[0x4146] = g[0x4146] + -1;
      }
      bVar5 = false;
      if ((g[0x52bd] != 0) && ((char)g[0x74e5] == '\0')) {
        bVar5 = true;
      }
      if (g[0x74e8] != 0) {
        bVar5 = (bool)(bVar5 & g[0x74ef] != 0);
      }
      if (g[0x7307] == 0) {
        MasterPalProcessChanges();
        if (g[0x4146] == 0) {
          if (*(char *)((int)g + 0x1d395) == '\0') {
            GameBGDraw();
          }
          else {
            W_Cls(0);
          }
          if (g[0x7559] == 4) {
            iVar15 = V_BufGetSurface((int *)g[0x4138],0);
            piVar19 = (int *)0x0;
            piVar18 = (int *)g[0x4136];
            uVar17 = 0x80904b7;
            puVar7 = (uint *)V_BufGetSurface(piVar18,0);
            V_DoubleRes(puVar7,iVar15);
          }
        }
        if (g[0x7559] == 4) {
          BGArraySetViewScale(g[0x6ed4],2);
          V_SetBuf((int *)g[0x4138],0);
        }
      }
      if (bVar5) {
        GameBarsDraw(0);
      }
      GameBarsUpdate();
      if ((g[0x7307] == 0) && (g[0x4146] == 0)) {
        if (*(char *)((int)g + 0x1d392) == '\0') {
          iVar15 = g[0x745a];
          piVar18 = g;
          if (g[0x7459] <= iVar15) {
            iVar20 = iVar15 * 4 + 0x1cf60;
            do {
              iVar6 = *(int *)(iVar20 + 4 + (int)piVar18);
              if ((iVar6 == 0) || (bVar12 = true, *(int *)(iVar6 + 0x158) == 0)) {
                bVar12 = false;
              }
              if (((bVar12) &&
                  (iVar6 = *(int *)((int)piVar18 + iVar20 + 4), *(char *)(iVar6 + 0x208) == '\0'))
                 && (*(int *)(iVar6 + 0x198) != 0)) {
                PlayerDrawShadow(*(int *)((int)piVar18 + iVar20 + 4),piVar18 + 0x10a4,
                                 piVar18 + 0x10a9);
                piVar18 = g;
              }
              iVar15 = iVar15 + -1;
              iVar20 = iVar20 + -4;
            } while (piVar18[0x7459] <= iVar15);
          }
          iVar15 = piVar18[0x745a];
          if (piVar18[0x7459] <= iVar15) {
            iVar20 = iVar15 * 4 + 0x1cf60;
            iVar6 = iVar20;
            do {
              iVar3 = *(int *)(iVar6 + 4 + (int)piVar18);
              if ((iVar3 == 0) || (bVar12 = true, *(int *)(iVar3 + 0x158) == 0)) {
                bVar12 = false;
              }
              if (bVar12) {
                ProjArrayDrawShadow(*(int **)(*(int *)(iVar20 + 4 + (int)piVar18) + 0x21c));
                piVar18 = g;
              }
              iVar15 = iVar15 + -1;
              iVar20 = iVar20 + -4;
              iVar6 = iVar6 + -4;
            } while (piVar18[0x7459] <= iVar15);
          }
          ExplodArrayDrawShadow((int *)piVar18[0x52be]);
        }
        if (g[0x7559] == 4) {
          fVar8 = 2.0;
        }
        else {
          fVar8 = 1.0;
        }
        piVar19 = (int *)0x2;
        piVar18 = (int *)g[0x413c];
        uVar17 = 0x8090672;
        AnimPerArrayDrawScaleGrp(piVar18,2,-(iVar9 + iVar14),-(iVar16 + iVar2),fVar8);
      }
      if (g[0x7307] == 0) {
        if ((0 < g[0x4146]) && (g[0x4144] != 0)) {
          W_Cls(g[0x4145]);
        }
        iVar15 = g[0x7459];
        piVar13 = g;
        if (iVar15 <= g[0x745a]) {
          iVar20 = iVar15 * 4 + 0x1cf60;
          do {
            iVar6 = *(int *)(iVar20 + 4 + (int)piVar13);
            if ((iVar6 == 0) || (bVar12 = true, *(int *)(iVar6 + 0x158) == 0)) {
              bVar12 = false;
            }
            if ((bVar12) && (*(int *)(*(int *)((int)piVar13 + iVar20 + 4) + 0x198) != 0)) {
              PlayerDrawAnim(*(int *)((int)piVar13 + iVar20 + 4),1.0);
              piVar13 = g;
            }
            iVar15 = iVar15 + 1;
            iVar20 = iVar20 + 4;
          } while (iVar15 <= piVar13[0x745a]);
        }
        iVar15 = piVar13[0x745a];
        if (piVar13[0x7459] <= iVar15) {
          iVar20 = iVar15 * 4 + 0x1cf60;
          iVar6 = iVar20;
          do {
            iVar3 = *(int *)(iVar6 + 4 + (int)piVar13);
            if ((iVar3 == 0) || (bVar12 = true, *(int *)(iVar3 + 0x158) == 0)) {
              bVar12 = false;
            }
            if (bVar12) {
              ProjArrayDraw(*(int **)(*(int *)(iVar20 + 4 + (int)piVar13) + 0x21c));
              piVar13 = g;
            }
            iVar15 = iVar15 + -1;
            iVar20 = iVar20 + -4;
            iVar6 = iVar6 + -4;
          } while (piVar13[0x7459] <= iVar15);
        }
        ExplodArrayDraw((int *)piVar13[0x52be],0);
        iVar15 = g[0x745a];
        piVar13 = g;
        if (g[0x7459] <= iVar15) {
          iVar20 = iVar15 * 4 + 0x1cf60;
          do {
            iVar6 = *(int *)(iVar20 + 4 + (int)piVar13);
            if ((iVar6 == 0) || (bVar12 = true, *(int *)(iVar6 + 0x158) == 0)) {
              bVar12 = false;
            }
            if (bVar12) {
              PlayerAftImgDraw(*(int *)(iVar20 + 4 + (int)piVar13));
              ProjArrayAftImgDraw(*(int **)(*(int *)((int)g + iVar20 + 4) + 0x21c));
              piVar13 = g;
            }
            iVar15 = iVar15 + -1;
            iVar20 = iVar20 + -4;
          } while (piVar13[0x7459] <= iVar15);
        }
        if (piVar13[0x7559] == 4) {
          PRSprArrayScale((int *)piVar13[0x413d],2.0);
          piVar13 = g;
        }
        PRSprArrayDraw((int *)piVar13[0x413d]);
        ExplodArrayDraw((int *)g[0x52be],1);
      }
      if (bVar5) {
        GameBarsDraw(1);
      }
      if ((g[0x7307] == 0) && (*(char *)((int)g + 0x1d396) == '\0')) {
        GameFGDraw();
      }
      GameRoundDraw();
      if (g[0x7307] == 0) {
        if ((0 < g[0x4146]) && (g[0x4144] == 0)) {
          W_Cls(g[0x4145]);
        }
        if (g[0x7559] == 4) {
          fVar8 = 2.0;
        }
        else {
          fVar8 = 1.0;
        }
        piVar19 = (int *)0x1;
        piVar18 = (int *)g[0x413c];
        uVar17 = 0x809090d;
        AnimPerArrayDrawScaleGrp(piVar18,1,-(iVar9 + iVar14),-(iVar16 + iVar2),fVar8);
        ExplodArrayDraw((int *)g[0x52be],2);
      }
      if (bVar5) {
        GameBarsDraw(2);
      }
      piVar13 = g;
      if (g[0x7307] == 0) {
        if (g[0x81d0] != 0) {
          iVar9 = g[0x745a];
          if (g[0x7459] <= iVar9) {
            iVar14 = iVar9 * 4 + 0x1cf60;
            iVar16 = iVar14;
            do {
              iVar2 = *(int *)(iVar16 + 4 + (int)piVar13);
              if ((iVar2 == 0) || (bVar5 = true, *(int *)(iVar2 + 0x158) == 0)) {
                bVar5 = false;
              }
              if (bVar5) {
                if (piVar13[0x7559] == 4) {
                  fVar8 = 2.0;
                }
                else {
                  fVar8 = 1.0;
                }
                PlayerDrawClsn(*(int *)(iVar14 + 4 + (int)piVar13),fVar8);
                piVar13 = g;
              }
              iVar9 = iVar9 + -1;
              iVar14 = iVar14 + -4;
              iVar16 = iVar16 + -4;
            } while (piVar13[0x7459] <= iVar9);
          }
          iVar9 = piVar13[0x745a];
          if (piVar13[0x7459] <= iVar9) {
            iVar14 = iVar9 * 4 + 0x1cf60;
            iVar16 = iVar14;
            do {
              iVar2 = *(int *)(iVar16 + 4 + (int)piVar13);
              if ((iVar2 == 0) || (bVar5 = true, *(int *)(iVar2 + 0x158) == 0)) {
                bVar5 = false;
              }
              if (bVar5) {
                if (piVar13[0x7559] == 4) {
                  fVar8 = 2.0;
                }
                else {
                  fVar8 = 1.0;
                }
                ProjArrayClsnDraw(*(int **)(*(int *)(iVar14 + 4 + (int)piVar13) + 0x21c),fVar8);
                piVar13 = g;
              }
              iVar9 = iVar9 + -1;
              iVar14 = iVar14 + -4;
              iVar16 = iVar16 + -4;
            } while (piVar13[0x7459] <= iVar9);
          }
        }
        if (piVar13[0x52bd] != 0) {
          ComboDisplay(1);
          ComboDisplay(2);
          piVar13 = g;
        }
        if (piVar13[0x730c] != 0) {
          W_BoxFill(0,0,V_Width,piVar13[0x730d],0);
          W_BoxFillTransSub16(0,g[0x730d],V_Width,g[0x730d] + 4,
                              0x10 << ((byte)_rgb_r_shift_16 & 0x1f) |
                              0x20 << ((byte)_rgb_g_shift_16 & 0x1f) |
                              0x10 << ((byte)_rgb_b_shift_16 & 0x1f));
          W_BoxFillTransSub16(0,g[0x730d] + 5,V_Width,g[0x730d] + 9,
                              0xc << ((byte)_rgb_r_shift_16 & 0x1f) |
                              0x18 << ((byte)_rgb_g_shift_16 & 0x1f) |
                              0xc << ((byte)_rgb_b_shift_16 & 0x1f));
          W_BoxFillTransSub16(0,g[0x730d] + 10,V_Width,g[0x730d] + 0xe,
                              8 << ((byte)_rgb_r_shift_16 & 0x1f) |
                              0x10 << ((byte)_rgb_g_shift_16 & 0x1f) |
                              8 << ((byte)_rgb_b_shift_16 & 0x1f));
          W_BoxFillTransSub16(0,g[0x730d] + 0xf,V_Width,g[0x730d] + 0x13,
                              4 << ((byte)_rgb_r_shift_16 & 0x1f) |
                              8 << ((byte)_rgb_g_shift_16 & 0x1f) |
                              4 << ((byte)_rgb_b_shift_16 & 0x1f));
          W_BoxFill(0,(V_Height - g[0x730d]) + -1,V_Width,V_Height + -1,0);
          W_BoxFillTransSub16(0,(V_Height - g[0x730d]) + -1,V_Width,(V_Height - g[0x730d]) + -5,
                              0x10 << ((byte)_rgb_r_shift_16 & 0x1f) |
                              0x20 << ((byte)_rgb_g_shift_16 & 0x1f) |
                              0x10 << ((byte)_rgb_b_shift_16 & 0x1f));
          W_BoxFillTransSub16(0,(V_Height - g[0x730d]) + -6,V_Width,(V_Height - g[0x730d]) + -10,
                              0xc << ((byte)_rgb_r_shift_16 & 0x1f) |
                              0x18 << ((byte)_rgb_g_shift_16 & 0x1f) |
                              0xc << ((byte)_rgb_b_shift_16 & 0x1f));
          W_BoxFillTransSub16(0,(V_Height - g[0x730d]) + -0xb,V_Width,(V_Height - g[0x730d]) + -0xf,
                              8 << ((byte)_rgb_r_shift_16 & 0x1f) |
                              0x10 << ((byte)_rgb_g_shift_16 & 0x1f) |
                              8 << ((byte)_rgb_b_shift_16 & 0x1f));
          piVar19 = (int *)((V_Height - g[0x730d]) + -0x10);
          piVar18 = (int *)0x0;
          uVar17 = 0x8090d72;
          W_BoxFillTransSub16(0,(int)piVar19,V_Width,(V_Height - g[0x730d]) + -0x14,
                              4 << ((byte)_rgb_r_shift_16 & 0x1f) |
                              8 << ((byte)_rgb_g_shift_16 & 0x1f) |
                              4 << ((byte)_rgb_b_shift_16 & 0x1f));
          piVar13 = g;
        }
        if ((piVar13[0x81cd] != 0) && ((piVar13[0x74e8] == 0 || (piVar13[0x74f0] != 0)))) {
          ShowDebugInfo(piVar13[0x81cb]);
          piVar13 = g;
        }
      }
      if ((piVar13[0x730c] != 0) && (piVar13[0x7309] == 0)) {
        iVar9 = piVar13[0x730e];
        iVar14 = iVar9 + piVar13[0x730d];
        piVar13[0x730d] = iVar14;
        piVar13 = g;
        if (((iVar9 < 0) && (iVar14 < 0)) || ((0 < iVar9 && (V_Height / 2 < iVar14)))) {
          g[0x730c] = 0;
        }
      }
      if ((piVar13[0x7309] == 0) && (piVar13[0x750d] == 0)) {
        ComboDisplayUpdate(1);
        ComboDisplayUpdate(2);
        piVar13 = g;
      }
      if ((piVar13[0x7309] != 0) && (piVar13[0x74e2] == 0)) {
        if (piVar13[0x7dba] == 0) {
          piVar18 = aiStack_43c;
          sprintf((char *)piVar18,"PAUSED");
          W_Box(0x85,8,0xb9,0x1b,
                10 << ((byte)_rgb_r_shift_16 & 0x1f) | 0x14 << ((byte)_rgb_g_shift_16 & 0x1f) |
                0x10 << ((byte)_rgb_b_shift_16 & 0x1f));
          W_Box(0x86,9,0xb8,0x1a,
                0x18 << ((byte)_rgb_r_shift_16 & 0x1f) | 0x30 << ((byte)_rgb_g_shift_16 & 0x1f) |
                0x1e << ((byte)_rgb_b_shift_16 & 0x1f));
          W_BoxFillTransAdd16_B50(0x87,10,0xb7,0x19,3 << ((byte)_rgb_b_shift_16 & 0x1f));
          piVar19 = (int *)g[0x413b];
          uVar17 = 0x8090f4c;
          V_FontDraw((char *)piVar18,piVar19,0x8e,0x14,
                     0x1f << ((byte)uVar4 & 0x1f) | 0x3f << (bVar10 & 0x1f) |
                     0x1f << (bVar11 & 0x1f));
          piVar13 = g;
        }
        else {
          TrainingMenuDraw();
          piVar13 = g;
        }
      }
      if (piVar13[0x4137] != 0) {
        V_SetBuf((int *)piVar13[0x4137],0);
        if (keypauseflag == 0) {
          piVar19 = (int *)0x0;
          piVar18 = (int *)g[0x4136];
          uVar17 = 0x8090fab;
          W_PutSpriteTransAdd_B(piVar18,0,0,0,0x80,0x80);
        }
        V_SetBuf((int *)g[0x4136],0);
        piVar13 = g;
      }
      if (piVar13[0x82d2] == 0) {
        TimerWaitSync();
        piVar13 = g;
      }
      if ((piVar13[0x7307] == 0) && (piVar13[0x4143] != 0)) {
        VRetrace();
      }
      DrawToScreen();
      if (g[0x7307] == 0) {
        MasterPalFinishedDraw();
      }
      FrameSkipUpdate();
      piVar1 = g;
      piVar13 = g + 0x7309;
      g[0x7308] = 0;
      if (*piVar13 == 0) {
        piVar1[0x7304] = piVar1[0x7304] + 1;
      }
    }
    bVar5 = GameModeInPassiveFightScreen();
    piVar13 = g;
    if (((GHIDRA_ZEXT8(bVar5) == 0) && (g[0x7546] != 0)) || (g[0x4135] != 0))
    goto LAB_080910a2;
    if (g[0x82d3] == 0) {
LAB_0808fec1:
      piVar13 = g;
      iVar9 = g[0x82d6];
      if ((iVar9 != 0) && (iVar9 != -1)) {
        g[0x7305] = iVar9;
        piVar13[0x82d2] = 1;
        piVar13 = g;
      }
      goto LAB_0808fee6;
    }
    g[0x7305] = 2000;
    piVar13[0x82d2] = 1;
    iVar9 = piVar13[0x7304];
    piVar13 = g;
  } while( true );
}
#undef aiStack_43c
#undef local_3c

/* GameUpdate @ 0x08091100, 3369 bytes
 * FIXUP: 1 float-field accesses rewritten as bit reinterpretations (asm: x87 single loads/stores at offsets 0x1cc70)
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x120-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 GameUpdate(void)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  bool bVar4;
  int *piVar5;
  uint uVar6;
  undefined3 extraout_var;
  uint uVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  longdouble lVar13;
  unsigned char ghidra_frame[0x120] __attribute__((aligned(16)));
#define aiStack_11c (*(int (*)[67])(ghidra_frame + 0x4))
  
  piVar3 = g;
  piVar5 = g + 0x33ae;
  g[0x730b] = 0;
  if ((*piVar5 == 3) || (piVar3[0x74e8] != 0)) {
    piVar3[0x730b] = 1;
  }
  piVar5 = g;
  iVar11 = g[0x7459];
  if (iVar11 <= g[0x745a]) {
    iVar10 = iVar11 * 4 + 0x1cf60;
    do {
      iVar12 = *(int *)(iVar10 + 4 + (int)piVar5);
      if ((iVar12 == 0) || (iVar9 = 1, *(int *)(iVar12 + 0x158) == 0)) {
        iVar9 = 0;
      }
      iVar10 = iVar10 + 4;
      piVar3[iVar11 + 0x749e] = iVar9;
      iVar11 = iVar11 + 1;
    } while (iVar11 <= piVar5[0x745a]);
  }
  iVar11 = 1;
  if (0 < piVar5[0x7395]) {
    iVar10 = 0x1cf64;
    do {
      iVar12 = *(int *)(iVar10 + 4 + (int)piVar5);
      if (iVar12 == 0) {
LAB_080911f5:
        bVar4 = false;
      }
      else {
        aiStack_11c[iVar11] = (int)GHIDRA_FIST32(*(float *)(iVar12 + 0x19c));
        bVar4 = true;
        if (*(int *)(iVar12 + 0x158) == 0) goto LAB_080911f5;
      }
      if (bVar4) {
        iVar9 = *(int *)(iVar12 + 0x3424);
        if (((iVar9 == 0) || (*(int *)(iVar9 + 0x158) == 0)) ||
           (bVar4 = true, *(int *)(iVar9 + 0x1c) != 0)) {
          bVar4 = false;
        }
        if (bVar4) {
          *(int *)(iVar12 + 0x3428) = iVar9;
        }
        iVar9 = PlayerNearestEnemy(iVar12);
        *(int *)(iVar12 + 0x3424) = iVar9;
      }
      iVar11 = iVar11 + 1;
      iVar10 = iVar10 + 4;
      piVar5 = g;
    } while (iVar11 <= g[0x7395]);
  }
  piVar8 = g;
  if ((piVar5[0x74f3] != -1) && (iVar11 = piVar5[0x7459], iVar11 <= piVar5[0x745a])) {
    iVar10 = iVar11 * 4 + 0x1cf60;
    iVar12 = iVar10;
    do {
      iVar9 = *(int *)(iVar12 + 4 + (int)piVar5);
      if ((iVar9 == 0) || (bVar4 = true, *(int *)(iVar9 + 0x158) == 0)) {
        bVar4 = false;
      }
      if ((bVar4) &&
         (*(int *)(*(int *)(iVar10 + 4 + (int)piVar5) + 0x1dc + piVar5[0x74f3] * 4) == 0)) {
        piVar3[iVar11 + 0x749e] = 0;
        piVar5 = piVar8;
      }
      iVar11 = iVar11 + 1;
      iVar10 = iVar10 + 4;
      iVar12 = iVar12 + 4;
    } while (iVar11 <= piVar5[0x745a]);
  }
  while (uVar6 = IntCircBufGet(piVar5 + 0x7391), uVar6 != 0) {
    piVar5 = g;
    if (((g[0x7309] == 0) || ((uVar6 & 0x1000) != 0)) && (iVar11 = g[0x7459], iVar11 <= g[0x745a]))
    {
      iVar10 = iVar11 * 4 + 0x1cf60;
      do {
        iVar12 = *(int *)(iVar10 + 4 + (int)piVar5);
        if ((iVar12 == 0) || (bVar4 = true, *(int *)(iVar12 + 0x158) == 0)) {
          bVar4 = false;
        }
        if ((bVar4) && (iVar12 = *(int *)((int)piVar5 + iVar10 + 4), *(int *)(iVar12 + 0x262c) == 0)
           ) {
          KBIUpdate(*(int *)(*(int *)((int)piVar5 + iVar10 + 4) + 0x960),iVar12 + 0x248,uVar6);
          piVar5 = g;
        }
        iVar11 = iVar11 + 1;
        iVar10 = iVar10 + 4;
      } while (iVar11 <= piVar5[0x745a]);
    }
  }
  if ((g[0x7309] == 0) && (g[0x750d] < 1)) {
    iVar11 = g[0x7459];
    piVar5 = g;
    if (iVar11 <= g[0x745a]) {
      iVar10 = iVar11 * 4 + 0x1cf60;
      iVar12 = iVar10;
      do {
        iVar9 = *(int *)(iVar12 + 4 + (int)piVar5);
        if ((iVar9 == 0) || (bVar4 = true, *(int *)(iVar9 + 0x158) == 0)) {
          bVar4 = false;
        }
        if (bVar4) {
          PlayerAIMsgStateUpdate(*(int *)(iVar10 + 4 + (int)piVar5));
          piVar5 = g;
        }
        iVar11 = iVar11 + 1;
        iVar10 = iVar10 + 4;
        iVar12 = iVar12 + 4;
      } while (iVar11 <= piVar5[0x745a]);
    }
    iVar11 = piVar5[0x7459];
    if (iVar11 <= piVar5[0x745a]) {
      iVar10 = iVar11 * 4 + 0x1cf60;
      iVar12 = iVar10;
      do {
        iVar9 = *(int *)(iVar12 + 4 + (int)piVar5);
        if ((iVar9 == 0) || (bVar4 = true, *(int *)(iVar9 + 0x158) == 0)) {
          bVar4 = false;
        }
        if (bVar4) {
          PlayerAI(*(int *)(iVar10 + 4 + (int)piVar5));
          piVar5 = g;
        }
        iVar11 = iVar11 + 1;
        iVar10 = iVar10 + 4;
        iVar12 = iVar12 + 4;
      } while (iVar11 <= piVar5[0x745a]);
    }
    iVar11 = piVar5[0x7459];
    if (iVar11 <= piVar5[0x745a]) {
      iVar10 = iVar11 * 4 + 0x1cf60;
      iVar12 = iVar10;
      do {
        iVar9 = *(int *)(iVar12 + 4 + (int)piVar5);
        if ((iVar9 == 0) || (bVar4 = true, *(int *)(iVar9 + 0x158) == 0)) {
          bVar4 = false;
        }
        if (bVar4) {
          PlayerAIClearMsg(*(int *)(iVar10 + 4 + (int)piVar5));
          piVar5 = g;
        }
        iVar11 = iVar11 + 1;
        iVar10 = iVar10 + 4;
        iVar12 = iVar12 + 4;
      } while (iVar11 <= piVar5[0x745a]);
    }
    iVar11 = piVar5[0x33b7];
    if (iVar11 == 5) {
      GameWinScreenUpdate();
      piVar5 = g;
    }
    else if (iVar11 < 6) {
      if ((iVar11 == 4) &&
         (((piVar5[0x7309] == 0 && (iVar11 = GameRoundUpdate(), piVar5 = g, iVar11 != 0)) ||
          ((piVar5[0x7309] == 0 &&
           ((piVar5[0x74e8] != 0 && (iVar11 = GameDemoUpdate(), piVar5 = g, iVar11 != 0)))))))) {
        return 1;
      }
    }
    else if (iVar11 == 6) {
      GameSurvivalResultsUpdate();
      piVar5 = g;
    }
    piVar8 = g;
    iVar11 = piVar5[0x7459];
    if (iVar11 <= piVar5[0x745a]) {
      iVar10 = iVar11 * 4 + 0x1cf60;
      iVar12 = iVar10;
      do {
        iVar9 = *(int *)(iVar12 + 4 + (int)piVar5);
        if ((iVar9 == 0) || (bVar4 = true, *(int *)(iVar9 + 0x158) == 0)) {
          bVar4 = false;
        }
        if ((bVar4) && (*(int *)(*(int *)(iVar10 + 4 + (int)piVar5) + 0x15c) != 0)) {
          piVar3[iVar11 + 0x749e] = 0;
          piVar5 = piVar8;
        }
        iVar11 = iVar11 + 1;
        iVar10 = iVar10 + 4;
        iVar12 = iVar12 + 4;
      } while (iVar11 <= piVar5[0x745a]);
    }
    if (((piVar5[0x109d] != 0) &&
        (bVar4 = GameModeInPassiveFightScreen(), piVar5 = g, GHIDRA_ZEXT8(bVar4) == 0)) &&
       (iVar11 = g[0x7459], iVar11 <= g[0x745a])) {
      do {
        iVar10 = piVar5[iVar11 + 0x73d9];
        if (((iVar10 == 0) || (*(int *)(iVar10 + 0x158) == 0)) ||
           (bVar4 = true, *(int *)(iVar10 + 0x1c) != 0)) {
          bVar4 = false;
        }
        if ((bVar4) && (piVar3[iVar11 + 0x749e] != 0)) {
          uVar6 = *(uint *)(piVar5[iVar11 + 0x73d9] + 0x3424);
          if ((uVar6 == 0) || (uVar7 = 1, *(int *)(uVar6 + 0x158) == 0)) {
            uVar7 = 0;
          }
          uVar6 = uVar6 & (uVar7 ^ 1) - 1;
          if ((uVar6 == 0) && (2 < piVar5[0x7511])) {
            if ((*(int *)(piVar5[iVar11 + 0x73d9] + 0x3428) == 0) ||
               (bVar4 = true, *(int *)(*(int *)(piVar5[iVar11 + 0x73d9] + 0x3428) + 0x158) == 0)) {
              bVar4 = false;
            }
            if (bVar4) {
              uVar6 = *(uint *)(piVar5[iVar11 + 0x73d9] + 0x3428);
            }
          }
          if (uVar6 != 0) {
            iVar10 = *(int *)(piVar5[iVar11 + 0x73d9] + 0xbf4);
            if (((((iVar10 == 0) || (iVar10 == 0xb)) || (iVar10 == 0x14)) || (iVar10 == 0x28)) ||
               ((iVar10 == 0x34 &&
                (puVar1 = *(undefined4 **)(piVar5[iVar11 + 0x73d9] + 0x13bc),
                iVar10 = AnimGetLooptime(puVar1), piVar5 = g, iVar10 + -1 <= (int)puVar1[7])))) {
              PlayerAutoTurn(piVar5[iVar11 + 0x73d9],uVar6,1);
              piVar5 = g;
            }
          }
        }
        iVar11 = iVar11 + 1;
      } while (iVar11 <= piVar5[0x745a]);
    }
    iVar11 = piVar5[0x7459];
    if (iVar11 <= piVar5[0x745a]) {
      iVar10 = iVar11 * 4 + 0x1cf60;
      iVar12 = iVar10;
      do {
        iVar9 = *(int *)(iVar12 + 4 + (int)piVar5);
        if ((iVar9 == 0) || (bVar4 = true, *(int *)(iVar9 + 0x158) == 0)) {
          bVar4 = false;
        }
        if (bVar4) {
          PlayerKBUpdate(*(int **)(iVar10 + 4 + (int)piVar5));
          piVar5 = g;
        }
        iVar11 = iVar11 + 1;
        iVar10 = iVar10 + 4;
        iVar12 = iVar12 + 4;
      } while (iVar11 <= piVar5[0x745a]);
    }
    *(undefined1 *)((int)piVar5 + 0x1d396) = 0;
    piVar5[0x74e3] = 0;
    piVar5[0x74e4] = 0;
    *(undefined2 *)(piVar5 + 0x74e5) = 0;
    iVar11 = g[0x7459];
    piVar5 = g;
    if (iVar11 <= g[0x745a]) {
      iVar10 = iVar11 * 4 + 0x1cf60;
      iVar12 = iVar10;
      do {
        iVar9 = *(int *)(iVar12 + 4 + (int)piVar5);
        if ((iVar9 == 0) || (bVar4 = true, *(int *)(iVar9 + 0x158) == 0)) {
          bVar4 = false;
        }
        if ((bVar4) && (piVar3[iVar11 + 0x749e] != 0)) {
          iVar9 = *(int *)(iVar10 + 4 + (int)piVar5);
          *(undefined1 *)(iVar9 + 0x20c) = 0;
          *(undefined4 *)(iVar9 + 0x204) = 0;
          *(undefined4 *)(iVar9 + 0x208) = 0;
          piVar5 = g;
        }
        iVar11 = iVar11 + 1;
        iVar10 = iVar10 + 4;
        iVar12 = iVar12 + 4;
      } while (iVar11 <= piVar5[0x745a]);
    }
    iVar11 = piVar5[0x7459];
    piVar5[0x74de] = 0;
    piVar8 = g;
    if (iVar11 <= piVar5[0x745a]) {
      iVar10 = iVar11 * 4 + 0x1cf60;
      iVar12 = iVar10;
      do {
        iVar9 = *(int *)(iVar12 + 4 + (int)piVar8);
        if ((iVar9 == 0) || (bVar4 = true, *(int *)(iVar9 + 0x158) == 0)) {
          bVar4 = false;
        }
        if (((bVar4) && (piVar3[iVar11 + 0x749e] != 0)) &&
           (piVar5 = *(int **)(iVar10 + 4 + (int)piVar8), piVar5[0x381] == 1)) {
          PlayerUpdate(piVar5);
          piVar8 = g;
        }
        iVar11 = iVar11 + 1;
        iVar10 = iVar10 + 4;
        iVar12 = iVar12 + 4;
      } while (iVar11 <= piVar8[0x745a]);
    }
    iVar11 = piVar8[0x7459];
    if (iVar11 <= piVar8[0x745a]) {
      iVar10 = iVar11 * 4 + 0x1cf60;
      iVar12 = iVar10;
      do {
        iVar9 = *(int *)(iVar12 + 4 + (int)piVar8);
        if ((iVar9 == 0) || (bVar4 = true, *(int *)(iVar9 + 0x158) == 0)) {
          bVar4 = false;
        }
        if (((bVar4) && (piVar3[iVar11 + 0x749e] != 0)) &&
           (piVar5 = *(int **)(iVar10 + 4 + (int)piVar8), piVar5[0x38b] != piVar8[0x7304])) {
          PlayerUpdate(piVar5);
          piVar8 = g;
        }
        iVar11 = iVar11 + 1;
        iVar10 = iVar10 + 4;
        iVar12 = iVar12 + 4;
      } while (iVar11 <= piVar8[0x745a]);
    }
    while (piVar8[0x74de] != 0) {
      iVar11 = piVar8[0x7459];
      piVar8[0x74de] = 0;
      piVar5 = piVar8 + 0x745a;
      piVar8 = g;
      if (iVar11 <= *piVar5) {
        iVar10 = iVar11 * 4 + 0x1cf60;
        iVar12 = iVar10;
        do {
          iVar9 = *(int *)(iVar12 + 4 + (int)piVar8);
          if ((iVar9 == 0) || (bVar4 = true, *(int *)(iVar9 + 0x158) == 0)) {
            bVar4 = false;
          }
          if (((bVar4) && (piVar3[iVar11 + 0x749e] != 0)) &&
             (piVar5 = *(int **)(iVar10 + 4 + (int)piVar8), piVar5[0x38b] != piVar8[0x7304])) {
            PlayerUpdate(piVar5);
            piVar8 = g;
          }
          iVar11 = iVar11 + 1;
          iVar10 = iVar10 + 4;
          iVar12 = iVar12 + 4;
        } while (iVar11 <= piVar8[0x745a]);
      }
    }
    iVar11 = piVar8[0x7459];
    if (iVar11 <= piVar8[0x745a]) {
      iVar10 = iVar11 * 4 + 0x1cf60;
      iVar12 = iVar10;
      do {
        iVar9 = *(int *)(iVar12 + 4 + (int)piVar8);
        if ((iVar9 == 0) || (bVar4 = true, *(int *)(iVar9 + 0x158) == 0)) {
          bVar4 = false;
        }
        if ((bVar4) && (piVar3[iVar11 + 0x749e] != 0)) {
          PlayerUpdateBindTo(*(int *)(iVar10 + 4 + (int)piVar8));
          piVar8 = g;
        }
        iVar11 = iVar11 + 1;
        iVar10 = iVar10 + 4;
        iVar12 = iVar12 + 4;
      } while (iVar11 <= piVar8[0x745a]);
    }
    piVar5 = piVar8;
    if (((0 < piVar8[0x7318]) && (piVar8[0x7309] == 0)) && (piVar8[0x750d] == 0)) {
      lVar13 = (longdouble)
               fsin(((longdouble)piVar8[0x7317] * (longdouble)GHIDRA_I2F(piVar8[0x731a]) +
                    (longdouble)(*(float *)&piVar8[0x731c])) * (longdouble)((double)3.14159) *
                    (longdouble)((double)0.005555555555555556));
      piVar8[0x7316] = (int)GHIDRA_FIST32(lVar13 * (longdouble)GHIDRA_I2F(piVar8[0x731b]));
      iVar11 = piVar8[0x7317];
      piVar8[0x7317] = iVar11 + 1;
      piVar5 = g;
      if (iVar11 + 1 == piVar8[0x7318]) {
        piVar8[0x7318] = 0;
        piVar8[0x7316] = 0;
        piVar8[0x7315] = 0;
        piVar5 = g;
      }
    }
    iVar11 = piVar5[0x7459];
    if (iVar11 <= piVar5[0x745a]) {
      iVar10 = iVar11 * 4 + 0x1cf60;
      iVar12 = iVar10;
      do {
        iVar9 = *(int *)(iVar12 + 4 + (int)piVar5);
        if ((iVar9 == 0) || (bVar4 = true, *(int *)(iVar9 + 0x158) == 0)) {
          bVar4 = false;
        }
        if (((bVar4) && (piVar3[iVar11 + 0x749e] != 0)) &&
           (iVar9 = *(int *)(iVar10 + 4 + (int)piVar5), *(int *)(iVar9 + 0xe18) == 0)) {
          AnimUpdate(*(undefined4 **)(iVar9 + 0x13bc));
          piVar5 = g;
        }
        iVar11 = iVar11 + 1;
        iVar10 = iVar10 + 4;
        iVar12 = iVar12 + 4;
      } while (iVar11 <= piVar5[0x745a]);
    }
    iVar11 = piVar5[0x745a];
    if (piVar5[0x7459] <= iVar11) {
      iVar10 = iVar11 * 4 + 0x1cf60;
      iVar12 = iVar10;
      iVar9 = iVar10;
      do {
        iVar2 = *(int *)(iVar12 + 4 + (int)piVar5);
        if ((iVar2 == 0) || (bVar4 = true, *(int *)(iVar2 + 0x158) == 0)) {
          bVar4 = false;
        }
        if (bVar4) {
          if (piVar3[iVar11 + 0x749e] != 0) {
            ProjArrayUpdate(*(int **)(*(int *)(iVar10 + 4 + (int)piVar5) + 0x21c));
            piVar5 = g;
          }
          ProjArrayCalcDraw(*(int **)(*(int *)(iVar9 + 4 + (int)piVar5) + 0x21c));
          piVar5 = g;
        }
        iVar11 = iVar11 + -1;
        iVar9 = iVar9 + -4;
        iVar10 = iVar10 + -4;
        iVar12 = iVar12 + -4;
      } while (piVar5[0x7459] <= iVar11);
    }
    iVar11 = piVar5[0x745a];
    if (piVar5[0x7459] <= iVar11) {
      iVar10 = iVar11 * 4 + 0x1cf60;
      do {
        iVar12 = *(int *)(iVar10 + 4 + (int)piVar5);
        if ((iVar12 == 0) || (bVar4 = true, *(int *)(iVar12 + 0x158) == 0)) {
          bVar4 = false;
        }
        if ((bVar4) && (*(int *)((int)piVar3 + iVar10 + 0x318) != 0)) {
          PlayerAftImgUpdate(*(int *)(iVar10 + 4 + (int)piVar5));
          ProjArrayAftImgUpdate(*(int **)(*(int *)((int)g + iVar10 + 4) + 0x21c));
          piVar5 = g;
        }
        iVar11 = iVar11 + -1;
        iVar10 = iVar10 + -4;
      } while (piVar5[0x7459] <= iVar11);
    }
    if (piVar5[0x74e0] != 0) {
      GameClsnUpdate();
      piVar5 = g;
    }
    if ((piVar5[0x74f3] == -1) && (iVar11 = piVar5[0x745a], piVar5[0x7459] <= iVar11)) {
      iVar12 = iVar11 * 4;
      iVar10 = iVar12 + 0x1cf60;
      piVar8 = piVar5;
      do {
        iVar9 = *(int *)(iVar10 + 4 + (int)piVar8);
        if ((iVar9 == 0) || (bVar4 = true, *(int *)(iVar9 + 0x158) == 0)) {
          bVar4 = false;
        }
        piVar5 = piVar8;
        if ((bVar4) &&
           (piVar5 = g,
           (int)GHIDRA_FIST32(*(float *)(*(int *)((int)piVar8 + iVar10 + 4) + 0x19c)) !=
           *(int *)((int)aiStack_11c + iVar12))) {
          PlayerMakeDust(*(int *)((int)piVar8 + iVar10 + 4));
          piVar5 = g;
        }
        iVar11 = iVar11 + -1;
        iVar10 = iVar10 + -4;
        iVar12 = iVar12 + -4;
        piVar8 = piVar5;
      } while (piVar5[0x7459] <= iVar11);
    }
    iVar11 = piVar5[0x745a];
    if (piVar5[0x7459] <= iVar11) {
      iVar10 = iVar11 * 4 + 0x1cf60;
      do {
        iVar12 = *(int *)(iVar10 + 4 + (int)piVar5);
        if ((iVar12 == 0) || (bVar4 = true, *(int *)(iVar12 + 0x158) == 0)) {
          bVar4 = false;
        }
        if ((bVar4) && (*(int *)(*(int *)((int)piVar5 + iVar10 + 4) + 0x15c) == 0)) {
          PlayerAILearnMoveUpdate
                    (*(int *)((int)piVar5 + iVar10 + 4),*(int *)((int)piVar3 + iVar10 + 0x318));
          piVar5 = g;
        }
        iVar11 = iVar11 + -1;
        iVar10 = iVar10 + -4;
      } while (piVar5[0x7459] <= iVar11);
    }
    CameraMoveP();
    AnimPerArrayUpdate((int *)g[0x413c]);
    iVar11 = g[0x7459];
    piVar5 = g;
    if (iVar11 <= g[0x745a]) {
      iVar10 = iVar11 * 4 + 0x1cf60;
      iVar12 = iVar10;
      do {
        iVar9 = *(int *)(iVar12 + 4 + (int)piVar5);
        if ((iVar9 == 0) || (bVar4 = true, *(int *)(iVar9 + 0x158) == 0)) {
          bVar4 = false;
        }
        if (bVar4) {
          PlayerComboCountCheck(*(int *)(iVar10 + 4 + (int)piVar5));
          piVar5 = g;
        }
        iVar11 = iVar11 + 1;
        iVar10 = iVar10 + 4;
        iVar12 = iVar12 + 4;
      } while (iVar11 <= piVar5[0x745a]);
    }
    ExplodArrayUpdate((int *)piVar5[0x52be]);
  }
  return 0;
}
#undef aiStack_11c

/* GameWinScreenUpdate @ 0x08091e30, 391 bytes
 * REVIEW: pid-in_stack_
 * FIXUP: PalGrpMakeFlag result written into the argument area: given explicit temporaries pgf_ffffffb4 */
void GameWinScreenUpdate(void)

{
  PalGrpFlag pgf_ffffffb4;
  bool bVar1;
  int *piVar2;
  int *piVar3;
  PalGrpFlag in_stack_ffffffb4;
  int iVar4;
  int iVar5;
  int iVar6;
  
  piVar2 = g;
  do {
    piVar3 = g;
    iVar4 = g[0x7541];
    bVar1 = false;
    iVar5 = g[0x7542];
    if (iVar4 == 1) {
      if (iVar5 == piVar2[0x2b70]) {
        g[0x7541] = 2;
        piVar3[0x7542] = 0;
        bVar1 = true;
      }
    }
    else if (iVar4 < 2) {
      if (iVar4 == 0) {
        iVar4 = piVar2[0x2b71];
        if (iVar5 < iVar4) {
          iVar6 = (iVar5 << 8) / iVar4;
          MasterPalMul(iVar6,iVar6,iVar6);
        }
        if (iVar5 == iVar4) {
          bVar1 = true;
          MasterPalMul(0x100,0x100,0x100);
          piVar3 = g;
          g[0x7541] = 1;
          piVar3[0x7542] = 0;
        }
      }
    }
    else if (iVar4 == 2) {
      iVar4 = piVar2[0x2b72];
      if (iVar5 < iVar4) {
        iVar6 = 0x100 - (iVar5 << 8) / iVar4;
        MasterPalMul(iVar6,iVar6,iVar6);
      }
      if (iVar5 == iVar4) {
        MasterPalMul(0,0,0);
        g[0x4135] = 1;
      }
    }
  } while (bVar1);
  iVar6 = 0x80;
  iVar5 = 0x80;
  iVar4 = 0x80;
  PalGrpMakeFlag(&pgf_ffffffb4,0xffffffff,0);
  PalGrpSetMul(pgf_ffffffb4,iVar4,iVar5,iVar6);
  SysExplodCreate_Sys(piVar2 + 0x2b55,0,0);
  g[0x7542] = g[0x7542] + 1;
  return;
}

/* GameSurvivalResultsUpdate @ 0x08091fc0, 439 bytes
 * REVIEW: pid-in_stack_
 * FIXUP: PalGrpMakeFlag result written into the argument area: given explicit temporaries pgf_fffffeb4
 * FIXUP: 1 exact-text site patches
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x120-byte frame (a local's address escapes, see apply_frame_emulation) */
void GameSurvivalResultsUpdate(void)

{
  PalGrpFlag pgf_fffffeb4;
  int *piVar1;
  bool bVar2;
  int *piVar3;
  PalGrpFlag in_stack_fffffeb4;
  int iVar4;
  int iVar5;
  int iVar6;
  unsigned char ghidra_frame[0x120] __attribute__((aligned(16)));
#define acStack_11c (*(char (*)[268])(ghidra_frame + 0x4))
  
  piVar3 = g;
  do {
    piVar1 = g;
    iVar4 = g[0x7541];
    bVar2 = false;
    iVar5 = g[0x7542];
    if (iVar4 == 1) {
      if (iVar5 == piVar3[0x2b8f]) {
        g[0x7541] = 2;
        piVar1[0x7542] = 0;
        bVar2 = true;
      }
    }
    else if (iVar4 < 2) {
      if (iVar4 == 0) {
        iVar4 = piVar3[0x2b90];
        if (iVar5 < iVar4) {
          iVar6 = (iVar5 << 8) / iVar4;
          MasterPalMul(iVar6,iVar6,iVar6);
        }
        if (iVar5 == iVar4) {
          bVar2 = true;
          MasterPalMul(0x100,0x100,0x100);
          piVar1 = g;
          g[0x7541] = 1;
          piVar1[0x7542] = 0;
        }
      }
    }
    else if (iVar4 == 2) {
      iVar4 = piVar3[0x2b91];
      if (iVar5 < iVar4) {
        iVar6 = 0x100 - (iVar5 << 8) / iVar4;
        MasterPalMul(iVar6,iVar6,iVar6);
      }
      if (iVar5 == iVar4) {
        MasterPalMul(0,0,0);
        g[0x4135] = 1;
      }
    }
  } while (bVar2);
  piVar1 = piVar3 + 0x2b83;
  iVar6 = 0x80;
  iVar5 = 0x80;
  iVar4 = 0x80;
  PalGrpMakeFlag(&pgf_fffffeb4,0xffffffff,0);
  PalGrpSetMul(pgf_fffffeb4,iVar4,iVar5,iVar6);
  strcpy(acStack_11c,(char *)piVar1);
  sprintf((char *)piVar1,acStack_11c,g[0x7506 + g[0x33b4]]);
  SysExplodCreate_Sys(piVar3 + 0x2b74,0,0);
  strcpy((char *)piVar1,acStack_11c);
  g[0x7542] = g[0x7542] + 1;
  return;
}
#undef acStack_11c

/* GameDemoUpdate @ 0x08092180, 200 bytes */
undefined4 GameDemoUpdate(void)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  if (g[0x7511] == 2) {
    if (g[0x74e8] != 0) {
      if (g[0x74ed] + -0x78 <= g[0x74f1]) {
        iVar1 = ((g[0x74ed] - g[0x74f1]) * 0x100) / 0x78;
        MasterPalMul(iVar1,iVar1,iVar1);
      }
      piVar2 = g;
      if (g[0x74ed] <= g[0x74f1]) {
        iVar1 = g[0x74f2];
        uVar3 = 1;
        g[0x4135] = 1;
        piVar2[0x74f2] = iVar1 + 1;
        if (piVar2[0x74e9] <= iVar1) {
          piVar2[0x74f2] = 0;
          piVar2[0x2351] = 0;
        }
      }
    }
    g[0x74f1] = g[0x74f1] + 1;
  }
  return uVar3;
}

/* GameRoundUpdate @ 0x08092250, 4836 bytes
 * FIXUP: frame emulation: 10 stack locals placed at their original offsets in a 0x80-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 GameRoundUpdate(void)

{
  int *piVar1;
  bool bVar2;
  bool bVar3;
  byte bVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  unsigned char ghidra_frame[0x80] __attribute__((aligned(16)));
#define local_78 (*(int *)(ghidra_frame + 0x8))
#define local_74 (*(int *)(ghidra_frame + 0xc))
#define local_6c (*(int *)(ghidra_frame + 0x14))
#define local_68 (*(int *)(ghidra_frame + 0x18))
#define local_64 (*(int *)(ghidra_frame + 0x1c))
#define local_60 (*(int *)(ghidra_frame + 0x20))
#define local_5c (*(int *)(ghidra_frame + 0x24))
#define local_4c (*(undefined4 *)(ghidra_frame + 0x34))
#define local_48 (*(int *)(ghidra_frame + 0x38))
#define local_3c (*(int (*)[11])(ghidra_frame + 0x44))
  
  piVar8 = g;
  piVar7 = g + 0x4109;
  local_3c[4] = 0xffffffff;
  local_3c[5] = -1;
  local_3c[6] = -1;
  local_3c[0] = 0;
  local_3c[1] = 0;
  local_3c[2] = 0;
  local_4c = 0;
  local_78 = 4;
  piVar6 = g + 0x4106;
  local_48 = 1;
  do {
    iVar10 = 0;
    iVar11 = piVar6[2];
    if (0 < iVar11) {
      do {
        iVar11 = g[piVar7[iVar10 * 5] + 0x73d9];
        iVar10 = iVar10 + 1;
        *(uint *)((int)local_3c + local_78) =
             (*(int *)(iVar11 + 0x160) * 1000) / *(int *)(iVar11 + 0x164) +
             *(int *)((int)local_3c + local_78) + (uint)(*(int *)(iVar11 + 0xe24) != 0);
        iVar11 = piVar6[2];
      } while (iVar10 < iVar11);
    }
    piVar7 = piVar7 + 0x17;
    piVar6 = piVar6 + 0x17;
    *(int *)((int)local_3c + local_78) = *(int *)((int)local_3c + local_78) / iVar11;
    local_78 = local_78 + 4;
    local_48 = local_48 + -1;
  } while (-1 < local_48);
  local_74 = 0;
  local_48 = 1;
  do {
    iVar11 = 0;
    piVar6 = (int *)((int)g + local_74 + 0x10418);
    if (0 < *(int *)((int)g + local_74 + 0x10420)) {
      local_64 = -4;
      local_68 = 0x10;
      local_6c = 0;
      do {
        iVar10 = g[*(int *)(local_6c + 0xc + (int)piVar6) + 0x73d9];
        if (((iVar10 == 0) || (*(int *)(iVar10 + 0x158) == 0)) ||
           (bVar2 = true, *(int *)(iVar10 + 0x1c) != 0)) {
          bVar2 = false;
        }
        if (bVar2) {
          if (local_3c[*(int *)(iVar10 + 0xc) + 4] == -1) {
            local_3c[*(int *)(iVar10 + 0xc) + 4] = 1;
          }
          if ((((*piVar6 != 1) || (iVar11 < 1)) ||
              ((g[0x79b5] != 0 ||
               ((*(int *)((int)g + local_68 + local_74 + 0x10424) == 0 ||
                (*(int *)((int)g + local_64 + local_74 + 0x10424) != 0)))))) &&
             (*(int *)(iVar10 + 0xe24) != 0)) {
            local_3c[*(int *)(iVar10 + 0xc) + 4] = 0;
          }
        }
        local_64 = local_64 + 0x14;
        local_68 = local_68 + 0x14;
        local_6c = local_6c + 0x14;
        iVar11 = iVar11 + 1;
      } while (iVar11 < *(int *)((int)g + local_74 + 0x10420));
    }
    local_74 = local_74 + 0x5c;
    local_48 = local_48 + -1;
  } while (-1 < local_48);
  piVar6 = g;
  if ((local_3c[5] != -1) && (local_3c[6] != -1)) {
    if ((local_3c[5] == 0) || (local_3c[6] == 0)) {
      if (local_3c[5] == 0) {
        if (local_3c[6] == 0) {
          if (g[0x7515] == 0) {
            g[0x7513] = 3;
            if (local_3c[2] < local_3c[1]) {
              piVar8[0x7512] = 1;
              iVar11 = 1;
            }
            else {
              if (local_3c[2] <= local_3c[1]) {
                WinIconCheck(1,0,4);
                WinIconCheck(2,0,4);
                piVar6 = g;
                g[0x7512] = 0;
                goto LAB_080925c2;
              }
              piVar8[0x7512] = 2;
              if ((piVar8[0x7511] != 3) && (piVar8[0x7508] < 10)) {
                piVar8[piVar8[0x7508] + 0x7523] = 4;
              }
              iVar11 = 2;
            }
            WinIconCheck(iVar11,0,4);
            piVar6 = g;
          }
        }
        else {
          g[0x7513] = 1;
          piVar8[0x7512] = 1;
          piVar6 = g;
        }
      }
      else {
        g[0x7513] = 1;
        piVar8[0x7512] = 2;
        piVar6 = g;
      }
    }
    else {
      g[0x7513] = 2;
      piVar8[0x7512] = 0;
      piVar6 = g;
    }
  }
LAB_080925c2:
  if (piVar6[0x730b] != 0) {
    piVar6[0x7513] = 0;
    piVar6 = g;
  }
  if (1 < (uint)piVar6[0x7511]) {
    piVar6[0x7517] = 0;
    piVar6 = g;
  }
  if ((piVar6[0x7517] != 0) && (piVar6[0x730c] == 0)) {
    piVar6[0x7517] = 0;
    piVar6[0x7511] = 2;
    GameRoundResetPlayerPos();
    MasterPalMul(0x100,0x100,0x100);
    iVar11 = V_Height;
    piVar6 = g;
    g[0x7514] = -1;
    piVar6[0x730c] = 1;
    if (piVar6[0x7559] != 4) {
      iVar11 = iVar11 / 2;
    }
    iVar10 = piVar6[0x7459];
    piVar6[0x730d] = iVar11;
    piVar6[0x730e] = -piVar6[0x730e];
    if (iVar10 <= piVar6[0x745a]) {
      iVar11 = iVar10 * 4 + 0x1cf60;
      iVar9 = iVar11;
      do {
        iVar5 = *(int *)(iVar11 + 4 + (int)piVar6);
        if (((iVar5 == 0) || (*(int *)(iVar5 + 0x158) == 0)) ||
           (bVar2 = true, *(int *)(iVar5 + 0x1c) != 0)) {
          bVar2 = false;
        }
        if (bVar2) {
          PlayerChangeState(*(int *)(iVar9 + 4 + (int)piVar6),0);
          piVar6 = g;
        }
        iVar10 = iVar10 + 1;
        iVar9 = iVar9 + 4;
        iVar11 = iVar11 + 4;
      } while (iVar10 <= piVar6[0x745a]);
    }
    iVar11 = piVar6[0x7459];
    if (iVar11 <= piVar6[0x745a]) {
      iVar10 = iVar11 * 4 + 0x1cf60;
      do {
        iVar9 = *(int *)(iVar10 + 4 + (int)piVar6);
        if (iVar9 != 0) {
          *(undefined4 *)(iVar9 + 0x15c) = 0;
          piVar6 = g;
        }
        iVar9 = *(int *)(iVar10 + 4 + (int)piVar6);
        if (((iVar9 == 0) || (*(int *)(iVar9 + 0x158) == 0)) ||
           (bVar2 = true, *(int *)(iVar9 + 0x1c) != 0)) {
          bVar2 = false;
        }
        if (bVar2) {
          iVar9 = **(int **)(*(int *)(iVar10 + 4 + (int)piVar6) + 0x21c);
          iVar5 = ArrayScanFirst(iVar9);
          while (piVar6 = g, iVar5 != 0) {
            ProjArrayDelete(*(int **)(*(int *)((int)g + iVar10 + 4) + 0x21c),*(int *)(iVar9 + 0x1c))
            ;
            iVar5 = ArrayScanNext(iVar9);
          }
        }
        else {
          iVar9 = *(int *)(iVar10 + 4 + (int)piVar6);
          if ((iVar9 == 0) || (bVar2 = true, *(int *)(iVar9 + 0x158) == 0)) {
            bVar2 = false;
          }
          if ((bVar2) && (iVar9 = *(int *)(iVar10 + 4 + (int)piVar6), *(int *)(iVar9 + 0x1c) == 1))
          {
            HelperDestroy(iVar9);
            piVar6 = g;
          }
        }
        iVar11 = iVar11 + 1;
        iVar10 = iVar10 + 4;
      } while (iVar11 <= piVar6[0x745a]);
    }
    ExplodArrayReset((undefined4 *)piVar6[0x52be]);
    ExplodArrayReset((undefined4 *)g[0x52bf]);
    piVar6 = g;
  }
  do {
    piVar6[0x74e0] = 1;
    piVar7 = g;
    switch(piVar6[0x7511]) {
    case 0:
      piVar6 = g + 0x7514;
      g[0x74e0] = 0;
      uVar12 = *piVar6 - 2U & 0xffffffffU - ((int)(*piVar6 - 2U) >> 0x1f);
      if ((int)uVar12 < 0x10) {
        iVar11 = uVar12 << 4;
      }
      else {
        iVar11 = 0x100;
      }
      MasterPalMul(iVar11,iVar11,iVar11);
      piVar7 = g;
      if (g[0x7514] < piVar8[0x4e77]) goto switchD_0809282e_default;
      MasterPalMul(0x100,0x100,0x100);
      piVar6 = g;
      g[0x7511] = 1;
      piVar6[0x7514] = 0;
      break;
    case 1:
      iVar11 = g[0x7459];
      piVar6 = g;
      if (iVar11 <= g[0x745a]) {
        iVar10 = iVar11 * 4 + 0x1cf60;
        iVar9 = iVar10;
        do {
          piVar7 = g;
          iVar5 = *(int *)(iVar9 + 4 + (int)piVar6);
          if (((iVar5 == 0) || (*(int *)(iVar5 + 0x158) == 0)) ||
             (bVar2 = true, *(int *)(iVar5 + 0x1c) != 0)) {
            bVar2 = false;
          }
          if ((bVar2) && (piVar6[0x7506] == 1)) {
            if (piVar6[0x7514] < 0) {
              *(undefined1 *)(piVar6 + 0x74e3) = 1;
              piVar6 = g;
            }
            else {
              *(undefined4 *)(*(int *)(iVar10 + 4 + (int)piVar6) + 0x15c) = 0;
              piVar6 = piVar7;
            }
          }
          iVar11 = iVar11 + 1;
          iVar10 = iVar10 + 4;
          iVar9 = iVar9 + 4;
        } while (iVar11 <= piVar6[0x745a]);
      }
      if ((char)piVar6[0x74e3] != '\0') {
        piVar6[0x750e] = 0;
        piVar6 = g;
      }
      if (((piVar6[0x750e] == piVar8[0x4fa5] + 1) && (piVar6[0x7506] < 10)) && (piVar6[0x74e8] == 0)
         ) {
        GameSndPlay((int *)piVar6[0x4155],piVar8[piVar6[0x7506] + 0x4fa6],
                    piVar8[piVar6[0x7506] + 0x4fb0],0);
        piVar6 = g;
      }
      if (piVar6[0x750e] < piVar8[0x4e78]) {
        piVar6[0x750e] = piVar6[0x750e] + 1;
        piVar7 = g;
        goto switchD_0809282e_default;
      }
      piVar6[0x7511] = 2;
      piVar6[0x7514] = 0;
      GameRoundResetPlayerPos();
      piVar6 = g;
      break;
    case 2:
      if ((g[0x74f3] == -1) && (g[0x750d] == 0)) {
        piVar6 = g + 0x7514;
        piVar1 = g + 0x508a;
        if (((*piVar1 <= *piVar6) && ((0 < g[0x7515] && (*(char *)((int)g + 0x1d393) == '\0')))) &&
           ((iVar11 = g[0x7515] + -1, g[0x7515] = iVar11, iVar11 == 0 && (*piVar1 < *piVar6)))) {
          piVar7[0x7511] = 3;
          piVar7[0x7514] = 0;
          piVar6 = piVar7;
          break;
        }
      }
      if ((piVar7[0x7514] == piVar8[0x4fd6]) && (piVar7[0x74e8] == 0)) {
        GameSndPlay((int *)piVar7[0x4155],piVar8[0x4fd7],piVar8[0x4fd8],0);
        piVar7 = g;
      }
      if ((piVar7[0x7514] == piVar8[0x508a]) && (iVar11 = piVar7[0x7459], iVar11 <= piVar7[0x745a]))
      {
        iVar10 = iVar11 * 4 + 0x1cf60;
        piVar6 = piVar7;
        do {
          iVar9 = *(int *)(iVar10 + 4 + (int)piVar6);
          if (((iVar9 == 0) || (*(int *)(iVar9 + 0x158) == 0)) ||
             (bVar2 = true, *(int *)(iVar9 + 0x1c) != 0)) {
            bVar2 = false;
          }
          piVar7 = piVar6;
          if ((bVar2) &&
             (iVar9 = *(int *)((int)piVar6 + iVar10 + 4), *(undefined4 *)(iVar9 + 0xe0c) = 1,
             piVar7 = g, *(int *)(iVar9 + 0xbf4) != 0)) {
            PlayerChangeState(*(int *)((int)piVar6 + iVar10 + 4),0);
            piVar7 = g;
          }
          iVar11 = iVar11 + 1;
          iVar10 = iVar10 + 4;
          piVar6 = piVar7;
        } while (iVar11 <= piVar7[0x745a]);
      }
      if (((piVar7[0x7513] == 0) || (*(char *)((int)piVar7 + 0x1d38e) != '\0')) ||
         (piVar7[0x7514] <= piVar7[0x508a])) {
        piVar7[0x7516] = piVar7[0x7516] + 1;
        piVar7 = g;
        goto switchD_0809282e_default;
      }
      piVar7[0x7511] = 3;
      piVar7[0x7514] = 0;
      piVar6 = g;
      if ((piVar7[0x7513] != 3) && ((char)piVar7[0x74e4] == '\0')) {
        piVar7[0x750b] = piVar8[0x508b];
        piVar7[0x750c] = 500;
        piVar7[0x750d] = 500;
        piVar6 = g;
      }
      break;
    case 3:
      piVar6 = g + 0x7514;
      g[0x750f] = *piVar6;
      if (*piVar6 == piVar8[0x502b]) {
        iVar11 = piVar7[0x7513];
        if (iVar11 == 3) {
          iVar11 = piVar8[0x5031];
          iVar10 = piVar8[0x5030];
          piVar6 = (int *)piVar7[0x4155];
        }
        else if (iVar11 == 2) {
          iVar11 = piVar8[0x502f];
          iVar10 = piVar8[0x502e];
          piVar6 = (int *)piVar7[0x4155];
        }
        else {
          if (iVar11 != 1) goto LAB_08092c58;
          iVar11 = piVar8[0x502d];
          iVar10 = piVar8[0x502c];
          piVar6 = (int *)piVar7[0x4155];
        }
        GameSndPlay(piVar6,iVar10,iVar11,0);
      }
LAB_08092c58:
      piVar7 = g;
      if (g[0x7513] != 3) {
        if ((g[0x7514] < g[0x508b] / 2) && (g[0x7514] == 5)) {
          g[0x750c] = 200;
          piVar7[0x750d] = 200;
        }
        if (piVar7[0x7514] == piVar7[0x508b] / 2) {
          piVar7[0x750c] = 100;
          piVar7[0x750d] = 100;
          piVar7 = g;
        }
        if (piVar7[0x7514] == (piVar7[0x508b] * 7) / 10) {
          piVar7[0x750c] = 0x32;
          piVar7[0x750d] = 0x32;
          piVar7 = g;
        }
        if (piVar7[0x7514] == (piVar7[0x508b] * 9) / 10) {
          piVar7[0x750c] = 0x19;
          piVar7[0x750d] = 0x19;
          piVar7 = g;
        }
      }
      piVar6 = g;
      if (((piVar7[0x7514] == piVar8[0x508c]) || ((piVar7[0x7514] == 0 && (piVar7[0x7515] == 0))))
         && (iVar11 = piVar7[0x7459], iVar11 <= piVar7[0x745a])) {
        iVar10 = iVar11 * 4 + 0x1cf60;
        iVar9 = iVar10;
        do {
          iVar5 = *(int *)(iVar9 + 4 + (int)piVar7);
          if ((iVar5 == 0) || (bVar2 = true, *(int *)(iVar5 + 0x158) == 0)) {
            bVar2 = false;
          }
          if (bVar2) {
            *(undefined4 *)(*(int *)(iVar10 + 4 + (int)piVar7) + 0x244) = 1;
            piVar7 = piVar6;
          }
          iVar11 = iVar11 + 1;
          iVar10 = iVar10 + 4;
          iVar9 = iVar9 + 4;
        } while (iVar11 <= piVar7[0x745a]);
      }
      if ((piVar7[0x14d0] != 0) && (piVar7[0x7514] == piVar7[0x508d])) {
        local_48 = 0;
        local_60 = 0;
        iVar11 = 1;
        do {
          iVar10 = GameRoundWinner();
          piVar6 = g;
          if (iVar10 != iVar11) {
            iVar10 = *(int *)((int)g + local_60 + 0xcee0) + 1;
            if (iVar10 < *(int *)((int)g + local_60 + 0xcee4)) {
              ClipboardAppend((int *)g[0x81d1],"start pre-caching team %i next %i\n",iVar11,iVar10);
              iVar10 = *(int *)((int)piVar6 + local_60 + 0xcee0) * 0x5c + local_60 + 0xcf48;
LAB_08092eb2:
              PrecacheRequestTeam((int)piVar6 + iVar10);
            }
            else if ((2 - g[0x33b3] == local_48) &&
                    (iVar10 = GameMatchWinner(), iVar10 == 2 - local_48)) {
              PrecacheRequestNextArcadeTeam();
            }
            else if ((g[0x33b3] == local_48) && (iVar10 = GameMatchWinner(), iVar10 == iVar11)) {
              iVar10 = local_60 + 0xceec;
              goto LAB_08092eb2;
            }
          }
          local_48 = local_48 + 1;
          local_60 = local_60 + 0x1a9c;
          iVar11 = iVar11 + 1;
        } while (local_48 < 2);
        PrecacheStart();
        piVar7 = g;
      }
      if (piVar8[0x508c] + 0xb4 <= piVar7[0x7514]) {
        piVar7[0x74e0] = 0;
        piVar7 = g;
      }
      bVar2 = true;
      iVar11 = piVar7[0x7459];
      if (iVar11 <= piVar7[0x745a]) {
        iVar10 = iVar11 * 4 + 0x1cf60;
        iVar9 = iVar10;
        local_5c = iVar10;
        do {
          iVar5 = *(int *)(local_5c + 4 + (int)piVar7);
          if (((iVar5 == 0) || (*(int *)(iVar5 + 0x158) == 0)) ||
             (bVar3 = true, *(int *)(iVar5 + 0x1c) != 0)) {
            bVar3 = false;
          }
          if (bVar3) {
            bVar4 = 0;
            iVar5 = *(int *)(iVar9 + 4 + (int)piVar7);
            if ((((*(int *)(iVar5 + 0xe0c) != 0) && (*(int *)(iVar5 + 0xe00) == 1)) &&
                (*(int *)(iVar5 + 0xe04) == 0)) ||
               (iVar5 = PlayerLyingDead(*(int *)(iVar10 + 4 + (int)piVar7)), piVar7 = g, 0 < iVar5))
            {
              bVar4 = 1;
            }
            bVar2 = (bool)(bVar2 & bVar4);
          }
          iVar11 = iVar11 + 1;
          local_5c = local_5c + 4;
          iVar10 = iVar10 + 4;
          iVar9 = iVar9 + 4;
        } while (iVar11 <= piVar7[0x745a]);
      }
      piVar6 = g;
      if (899 < piVar7[0x7514]) {
        bVar2 = true;
      }
      if ((!bVar2) || (piVar7[0x7514] < piVar8[0x508c])) goto switchD_0809282e_default;
      iVar11 = piVar7[0x7459];
      if (iVar11 <= piVar7[0x745a]) {
        iVar10 = iVar11 * 4 + 0x1cf60;
        iVar9 = iVar10;
        do {
          iVar5 = *(int *)(iVar9 + 4 + (int)piVar7);
          if (((iVar5 == 0) || (*(int *)(iVar5 + 0x158) == 0)) ||
             (bVar2 = true, *(int *)(iVar5 + 0x1c) != 0)) {
            bVar2 = false;
          }
          if (bVar2) {
            *(undefined4 *)(*(int *)(iVar10 + 4 + (int)piVar7) + 0xe0c) = 0;
            piVar7 = piVar6;
          }
          iVar11 = iVar11 + 1;
          iVar10 = iVar10 + 4;
          iVar9 = iVar9 + 4;
        } while (iVar11 <= piVar7[0x745a]);
      }
      piVar7[0x7511] = 4;
      piVar7[0x7514] = 0;
      piVar7[0x750b] = 0;
      piVar6 = g;
      break;
    case 4:
      goto switchD_0809282e_caseD_4;
    default:
      goto switchD_0809282e_default;
    }
  } while( true );
switchD_0809282e_caseD_4:
  g[0x74e0] = 0;
  if (piVar8[0x508c] + piVar7[0x7514] == piVar8[0x502b]) {
    iVar11 = piVar7[0x7513];
    if (iVar11 == 3) {
      iVar11 = piVar8[0x5031];
      iVar10 = piVar8[0x5030];
      piVar6 = (int *)piVar7[0x4155];
    }
    else if (iVar11 == 2) {
      iVar11 = piVar8[0x502f];
      iVar10 = piVar8[0x502e];
      piVar6 = (int *)piVar7[0x4155];
    }
    else {
      if (iVar11 != 1) goto LAB_0809312e;
      iVar11 = piVar8[0x502d];
      iVar10 = piVar8[0x502c];
      piVar6 = (int *)piVar7[0x4155];
    }
    GameSndPlay(piVar6,iVar10,iVar11,0);
  }
LAB_0809312e:
  if (g[0x7514] == piVar8[0x508e]) {
    iVar11 = g[0x7459];
    piVar8 = g;
    if (iVar11 <= g[0x745a]) {
      iVar10 = iVar11 * 4 + 0x1cf60;
      piVar6 = g;
      do {
        iVar9 = *(int *)(iVar10 + 4 + (int)piVar6);
        if (((iVar9 == 0) || (*(int *)(iVar9 + 0x158) == 0)) ||
           (bVar2 = true, *(int *)(iVar9 + 0x1c) != 0)) {
          bVar2 = false;
        }
        piVar8 = piVar6;
        if (bVar2) {
          iVar9 = *(int *)((int)piVar6 + iVar10 + 4);
          if (piVar6[0x7512] == *(int *)(iVar9 + 0xc)) {
            *(undefined4 *)(iVar9 + 0x244) = 0;
            piVar8 = g;
            if (*(int *)(iVar9 + 0xe24) != 0) {
              iVar5 = 0xb4;
LAB_080931b5:
              iVar9 = *(int *)((int)piVar6 + iVar10 + 4);
LAB_080931ec:
              PlayerChangeState(iVar9,iVar5);
              piVar8 = g;
            }
          }
          else if (piVar6[0x7512] == 0) {
            if (*(int *)(iVar9 + 0xe24) != 0) {
              iVar5 = 0xaf;
              iVar9 = *(int *)((int)piVar6 + iVar10 + 4);
              goto LAB_080931ec;
            }
          }
          else if (*(int *)(iVar9 + 0xe24) != 0) {
            iVar5 = 0xaa;
            goto LAB_080931b5;
          }
        }
        iVar11 = iVar11 + 1;
        iVar10 = iVar10 + 4;
        piVar6 = piVar8;
      } while (iVar11 <= piVar8[0x745a]);
    }
    iVar11 = piVar8[0x7512];
    if (iVar11 == 0) {
      iVar10 = 0x1d410;
      iVar11 = 0xe970;
      piVar8[0x750a] = piVar8[0x750a] + 1;
      piVar8 = g;
      local_48 = 1;
      do {
        if (*(int *)(iVar11 + 4 + (int)piVar8) < piVar8[0x750a]) {
          *(int *)(iVar10 + 0xc + (int)piVar8) = *(int *)(iVar10 + 0xc + (int)piVar8) + 1;
        }
        iVar10 = iVar10 + 4;
        iVar11 = iVar11 + 0x1a9c;
        local_48 = local_48 + -1;
      } while (-1 < local_48);
      piVar8[0x7509] = 1;
    }
    else {
      piVar8[0x7509] = 1;
      piVar8[iVar11 + 0x7506] = piVar8[iVar11 + 0x7506] + 1;
      iVar11 = GameMatchWinner();
      piVar8 = g;
      if (iVar11 == 0) {
        iVar9 = g[0x7512] + -1;
        iVar11 = g[iVar9 * 0x6a7 + 0x33b8];
        iVar10 = 0;
        if (0 < g[iVar11 * 0x17 + iVar9 * 0x6a7 + 0x33bd]) {
          do {
            iVar13 = iVar10 + 1;
            iVar10 = g[piVar8[iVar11 * 0x17 + iVar9 * 0x6a7 + iVar10 * 5 + 0x33be] + 0x73d9];
            iVar5 = TeamLifeBack(iVar9);
            PlayerLifeSet(iVar10,(iVar5 * *(int *)(iVar10 + 0x164)) / 1000 +
                                 *(int *)(iVar10 + 0x160));
            iVar10 = iVar13;
          } while (iVar13 < piVar8[iVar11 * 0x17 + iVar9 * 0x6a7 + 0x33bd]);
        }
      }
    }
  }
  if ((*(char *)((int)g + 0x1d38d) != '\0') && (g[0x7518] == 0)) {
    g[0x7510] = g[0x7514] + 0x13;
  }
  iVar11 = g[0x7510] - g[0x7514];
  if (iVar11 < 0x10) {
    iVar10 = GameMatchWinner();
    if (iVar10 != 0) {
      GameSetVol(g[0x6ef5] + (0x10 - iVar11) * -2,g[0x6ef7] + (0x10 - iVar11) * -2);
    }
    iVar11 = iVar11 * 0x10;
    MasterPalMul(iVar11,iVar11,iVar11);
  }
  piVar7 = g;
  if (g[0x7510] <= g[0x7514]) {
    iVar11 = GameMatchWinner();
    piVar8 = g;
    if (iVar11 != 0) {
      g[0x7546] = 1;
      piVar8[0x7545] = iVar11;
    }
    if (g[0x7546] == 0) {
      LogMatch();
      piVar8 = g;
      iVar11 = g[0x7459];
      if (iVar11 <= g[0x745a]) {
        iVar10 = iVar11 * 4 + 0x1cf60;
        iVar9 = iVar10;
        do {
          iVar5 = *(int *)(iVar9 + 4 + (int)piVar8);
          if (((iVar5 == 0) || (*(int *)(iVar5 + 0x158) == 0)) ||
             (bVar2 = true, *(int *)(iVar5 + 0x1c) != 0)) {
            bVar2 = false;
          }
          if (bVar2) {
            iVar5 = *(int *)(iVar10 + 4 + (int)piVar8);
            *(int *)(iVar5 + 0x342c) = *(int *)(iVar5 + 0x342c) + 1;
          }
          iVar11 = iVar11 + 1;
          iVar10 = iVar10 + 4;
          iVar9 = iVar9 + 4;
        } while (iVar11 <= piVar8[0x745a]);
      }
      PrecacheFinish();
      W_Cls(0);
      g[0x7307] = 0;
      DrawToScreen();
      DrawToScreen();
      GameNextRound();
    }
    local_4c = 1;
    piVar7 = g;
  }
switchD_0809282e_default:
  if (0 < piVar7[0x750b]) {
    piVar7[0x750b] = piVar7[0x750b] + -1;
    piVar7 = g;
  }
  if ((piVar7[0x750b] == 0) && (piVar7[0x750c] != 0)) {
    piVar7[0x750c] = 0;
    piVar7[0x750d] = 0;
    piVar7 = g;
  }
  piVar7[0x7514] = piVar7[0x7514] + 1;
  return local_4c;
}
#undef local_78
#undef local_74
#undef local_6c
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_4c
#undef local_48
#undef local_3c

/* GameRoundDraw @ 0x08093540, 956 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x60-byte frame (a local's address escapes, see apply_frame_emulation) */
void GameRoundDraw(void)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  undefined4 in_EDX;
  undefined4 extraout_EDX;
  int iVar6;
  int *__src;
  int iVar7;
  unsigned char ghidra_frame[0x60] __attribute__((aligned(16)));
#define local_5c (*(char (*)[76])(ghidra_frame + 0x4))
  
  piVar4 = g;
  piVar5 = (int *)g[0x73da];
  piVar1 = (int *)g[0x73db];
  piVar2 = (int *)g[0x73dc];
  piVar3 = (int *)g[0x73dd];
  iVar6 = g[0x7511];
  if (iVar6 == 2) {
    if ((g[0x7514] == g[0x4fd5] + 1) && (g[0x74e8] == 0)) {
      SysExplodCreate_Fight(g + 0x4fba,g[0x4e79],g[0x4e7a]);
    }
  }
  else if (iVar6 < 3) {
    if (((iVar6 == 1) && (g[0x750e] == g[0x4fa4] + 2)) && (g[0x74e8] == 0)) {
      if (g[0x7506] < 10) {
        SysExplodCreate_Fight(g + g[0x7506] * 0x1b + 0x4e96,g[0x4e79],g[0x4e7a]);
        in_EDX = extraout_EDX;
      }
      __src = piVar4 + 0x4e8a;
      strcpy(local_5c,(char *)__src);
      sprintf((char *)__src,local_5c,g[0x7506],in_EDX);
      iVar6 = piVar4[0x4e7a];
      piVar5 = piVar4 + 0x4e7b;
      iVar7 = piVar4[0x4e79];
LAB_08093848:
      SysExplodCreate_Fight(piVar5,iVar7,iVar6);
      strcpy((char *)__src,local_5c);
    }
  }
  else if ((iVar6 == 4) && (g[0x7514] == g[0x5089] + 1)) {
    iVar6 = GameRoundWinner();
    if (iVar6 == 1) {
      if (piVar2 == (int *)0x0) {
        __src = piVar4 + 0x5041;
        strcpy(local_5c,(char *)__src);
        sprintf((char *)__src,local_5c,*piVar5 + 0x30);
        iVar6 = piVar4[0x4e7a];
        piVar5 = piVar4 + 0x5032;
        iVar7 = piVar4[0x4e79];
      }
      else {
        __src = piVar4 + 0x505c;
        strcpy(local_5c,(char *)__src);
        sprintf((char *)__src,local_5c,*piVar5 + 0x30,*piVar2 + 0x30);
        iVar6 = piVar4[0x4e7a];
        piVar5 = piVar4 + 0x504d;
        iVar7 = piVar4[0x4e79];
      }
    }
    else {
      iVar6 = GameRoundWinner();
      if (iVar6 == 2) {
        if (piVar3 == (int *)0x0) {
          __src = piVar4 + 0x5041;
          strcpy(local_5c,(char *)__src);
          sprintf((char *)__src,local_5c,*piVar1 + 0x30);
          iVar6 = piVar4[0x4e7a];
          piVar5 = piVar4 + 0x5032;
          iVar7 = piVar4[0x4e79];
        }
        else {
          __src = piVar4 + 0x505c;
          strcpy(local_5c,(char *)__src);
          sprintf((char *)__src,local_5c,*piVar1 + 0x30,*piVar3 + 0x30);
          iVar6 = piVar4[0x4e7a];
          piVar5 = piVar4 + 0x504d;
          iVar7 = piVar4[0x4e79];
        }
      }
      else {
        if (g[0x7513] != 3) goto LAB_08093860;
        __src = piVar4 + 0x5077;
        strcpy(local_5c,(char *)__src);
        sprintf((char *)__src,local_5c,*piVar1 + 0x30);
        iVar6 = piVar4[0x4e7a];
        iVar7 = piVar4[0x4e79];
        piVar5 = piVar4 + 0x5068;
      }
    }
    goto LAB_08093848;
  }
LAB_08093860:
  if (1 < g[0x7511] - 3U) goto LAB_080938d7;
  iVar6 = g[0x7514];
  if (g[0x7511] == 4) {
    iVar6 = iVar6 + g[0x750f];
  }
  if (iVar6 != piVar4[0x502a] + 1) goto LAB_080938d7;
  iVar6 = g[0x7513];
  if (iVar6 == 3) {
    piVar5 = piVar4 + 0x500f;
LAB_080938bf:
    iVar6 = piVar4[0x4e7a];
    iVar7 = piVar4[0x4e79];
  }
  else {
    if (iVar6 != 2) {
      if (iVar6 != 1) goto LAB_080938d7;
      piVar5 = piVar4 + 0x4fd9;
      goto LAB_080938bf;
    }
    piVar5 = piVar4 + 0x4ff4;
    iVar6 = piVar4[0x4e7a];
    iVar7 = piVar4[0x4e79];
  }
  SysExplodCreate_Fight(piVar5,iVar7,iVar6);
LAB_080938d7:
  if (g[0x7307] == 0) {
    ExplodArrayDraw((int *)g[0x52bf],-1);
  }
  return;
}
#undef local_5c

/* GameInputUpdate @ 0x08093900, 2629 bytes
 * FIXUP: 3 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

undefined4 GameInputUpdate(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  bool bVar5;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  int iVar6;
  undefined3 extraout_var_01;
  bool bVar7;
  int *piVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  uint local_18;
  uint local_14;
  
  local_18 = 0;
  iVar10 = g[0x73da];
  iVar12 = g[0x73db];
  iVar1 = g[0x73dc];
  iVar2 = g[0x73dd];
  bVar7 = false;
  local_14 = 0;
  if ((g[0x81cb] != 0) || (g[0x81cf] != 0)) {
    bVar7 = true;
  }
  g[0x7309] = (int)(char)keypauseflag;
  PadPoll();
  KBPoll();
  bVar5 = KBkbhit();
  if (GHIDRA_ZEXT8(bVar5) != 0) {
    local_18 = KBgetchraw();
  }
  bVar5 = PadHit();
  if (GHIDRA_ZEXT8(bVar5) != 0) {
    local_14 = PadGet();
  }
  GlobalInputUpdate();
  IntCircBufClear((int)(g + 0x7391));
  uVar14 = 0;
  while( true ) {
    iVar6 = TrainingMenuUpdate(uVar14);
    if (iVar6 != 0) {
      keypauseflag = 0;
    }
    bVar5 = UInpHit();
    if (GHIDRA_ZEXT8(bVar5) == 0) break;
    uVar14 = UInpGet();
    IntCircBufStuff(g + 0x7391,uVar14);
  }
  if (local_18 == 1) {
    g[0x4135] = 1;
  }
  piVar8 = g;
  if ((g[0x74e8] != 0) &&
     ((((local_18 != 0 && ((local_18 & 0x100) == 0)) && (local_18 != 0x46)) ||
      ((local_14 != 0 && ((local_14 & 0x100) == 0)))))) {
    g[0x4135] = 1;
    piVar8[0x82d2] = 0;
  }
  if (bVar7) {
    if ((local_18 == 0x39) || (keyflag[0x39] != 0)) {
      iVar6 = g[0x7459];
      piVar8 = g;
      if (iVar6 <= g[0x745a]) {
        iVar11 = iVar6 * 4 + 0x1cf60;
        do {
          iVar13 = *(int *)(iVar11 + 4 + (int)piVar8);
          if (((iVar13 == 0) || (*(int *)(iVar13 + 0x158) == 0)) ||
             (bVar5 = true, *(int *)(iVar13 + 0x1c) != 0)) {
            bVar5 = false;
          }
          if (bVar5) {
            iVar13 = *(int *)((int)piVar8 + iVar11 + 4);
            if (*(int *)(iVar13 + 0xbf4) == 0x141e) {
              PlayerChangeState(iVar13,0x1400);
              piVar8 = g;
            }
            iVar13 = *(int *)(iVar11 + 4 + (int)piVar8);
            *(undefined4 *)(iVar13 + 0x160) = *(undefined4 *)(iVar13 + 0x164);
            *(undefined4 *)(iVar13 + 0xe24) = 1;
            *(undefined4 *)(iVar13 + 0x198) = 1;
            *(undefined4 *)(iVar13 + 0x1010) = 0;
            *(undefined4 *)(iVar13 + 0x100c) = 0;
            **(undefined4 **)(iVar13 + 0x170) = **(undefined4 **)(iVar13 + 0x174);
            piVar8 = g;
          }
          iVar6 = iVar6 + 1;
          iVar11 = iVar11 + 4;
        } while (iVar6 <= piVar8[0x745a]);
      }
      if ((piVar8[0x33ae] != 3) && (piVar8[0x74e8] == 0)) {
        piVar8[0x7515] = (piVar8[0x79a0] + 1) * piVar8[0x4e61] + -1;
      }
    }
    if (local_18 == 0x3b) {
      if ((keyflag[0x9d] == 0) && (keyflag[0x1d] == 0)) {
        PlayerLifeSet(iVar12,0);
        iVar6 = iVar2;
      }
      else {
        PlayerLifeSet(iVar10,0);
        iVar6 = iVar1;
      }
      if (iVar6 != 0) {
        PlayerLifeSet(iVar6,0);
      }
    }
    if (local_18 == 0x3c) {
      if (((keyflag[0x36] == 0) && (keyflag[0x2a] == 0)) && (PlayerLifeSet(iVar10,1), iVar1 != 0)) {
        PlayerLifeSet(iVar1,1);
      }
      if (((keyflag[0x9d] == 0) && (keyflag[0x1d] == 0)) && (PlayerLifeSet(iVar12,1), iVar2 != 0)) {
        PlayerLifeSet(iVar2,1);
      }
    }
    if ((keyflag[0x3d] != 0) || (local_18 == 0x3d)) {
      **(undefined4 **)(iVar10 + 0x170) = **(undefined4 **)(iVar10 + 0x174);
      **(undefined4 **)(iVar12 + 0x170) = **(undefined4 **)(iVar12 + 0x174);
    }
    piVar8 = g;
    if (local_18 == 0x3e) {
      iVar6 = g[0x7459];
      if (iVar6 <= g[0x745a]) {
        iVar11 = iVar6 * 4 + 0x1cf60;
        iVar13 = iVar11;
        do {
          iVar3 = *(int *)(iVar13 + 4 + (int)piVar8);
          if (((iVar3 == 0) || (*(int *)(iVar3 + 0x158) == 0)) ||
             (bVar5 = true, *(int *)(iVar3 + 0x1c) != 0)) {
            bVar5 = false;
          }
          if (bVar5) {
            iVar3 = *(int *)(iVar11 + 4 + (int)piVar8);
            *(undefined4 *)(iVar3 + 0x160) = *(undefined4 *)(iVar3 + 0x164);
          }
          iVar6 = iVar6 + 1;
          iVar11 = iVar11 + 4;
          iVar13 = iVar13 + 4;
        } while (iVar6 <= piVar8[0x745a]);
      }
      if ((keyflag[0x36] == 0) && (keyflag[0x2a] == 0)) {
        piVar8[0x82d4] = 1;
      }
      else {
        piVar8[0x82d5] = 1;
      }
    }
    if (local_18 == 0x3f) {
      g[0x7515] = 1;
    }
    if (local_18 == 0x42) {
      ClipboardClear((undefined4 *)g[0x81d1]);
      iVar6 = g[0x7459];
      if (iVar6 <= g[0x745a]) {
        iVar11 = iVar6 * 4 + 0x1cf60;
        piVar8 = g;
        iVar13 = iVar11;
        do {
          iVar3 = *(int *)(iVar13 + 4 + (int)piVar8);
          if ((iVar3 == 0) || (bVar5 = true, *(int *)(iVar3 + 0x158) == 0)) {
            bVar5 = false;
          }
          if ((bVar5) &&
             (puVar4 = *(undefined4 **)(*(int *)(iVar11 + 4 + (int)piVar8) + 0x345c),
             puVar4 != (undefined4 *)0x0)) {
            ClipboardClear(puVar4);
            piVar8 = g;
          }
          iVar6 = iVar6 + 1;
          iVar11 = iVar11 + 4;
          iVar13 = iVar13 + 4;
        } while (iVar6 <= piVar8[0x745a]);
      }
    }
  }
  if ((keyflag[0x1d] != 0) || (keyflag[0x9d] != 0)) {
    if (bVar7) {
      if ((keyflag[0x38] == 0) && (keyflag[0xb8] == 0)) {
        if (local_18 == 2) {
          *(uint *)(iVar10 + 0x262c) = *(uint *)(iVar10 + 0x262c) ^ 1;
        }
        if (local_18 == 3) {
          *(uint *)(iVar12 + 0x262c) = *(uint *)(iVar12 + 0x262c) ^ 1;
        }
        if ((local_18 == 4) && (iVar1 != 0)) {
          *(uint *)(iVar1 + 0x262c) = *(uint *)(iVar1 + 0x262c) ^ 1;
        }
        if ((local_18 == 5) && (iVar2 != 0)) {
          *(uint *)(iVar2 + 0x262c) = *(uint *)(iVar2 + 0x262c) ^ 1;
        }
      }
      else {
        if (local_18 == 2) {
          PlayerEnableSet(*(int *)(iVar10 + 8),(uint)(*(int *)(iVar10 + 0x158) == 0));
        }
        if (local_18 == 3) {
          PlayerEnableSet(*(int *)(iVar12 + 8),(uint)(*(int *)(iVar12 + 0x158) == 0));
        }
        if ((local_18 == 4) && (iVar1 != 0)) {
          PlayerEnableSet(*(int *)(iVar1 + 8),(uint)(*(int *)(iVar1 + 0x158) == 0));
        }
        if ((local_18 == 5) && (iVar2 != 0)) {
          PlayerEnableSet(*(int *)(iVar2 + 8),(uint)(*(int *)(iVar2 + 0x158) == 0));
        }
      }
      if (local_18 == 0x2f) {
        if (g[0x4143] == 0) {
          g[0x4143] = 1;
        }
        else {
          g[0x4143] = 0;
        }
      }
      if (local_18 == 0x1f) {
        if (g[0x82d2] == 0) {
          g[0x82d2] = 1;
        }
        else {
          g[0x82d2] = 0;
          TimerSyncReset();
        }
      }
      piVar8 = g;
      if (local_18 == 0x21) {
        iVar10 = g[0x7305];
        g[0x7305] = iVar10 + 1;
        if (iVar10 + 1 == 3) {
          piVar8[0x7305] = 2000;
          piVar8[0x6ef3] = 0;
        }
        piVar8 = g;
        if (2000 < g[0x7305]) {
          g[0x7305] = -1;
          piVar8[0x6ef3] = 1;
        }
      }
      if ((1999 < piVar8[0x7305]) && (piVar8[0x82d2] == 0)) {
        piVar8[0x7305] = -1;
        piVar8[0x6ef3] = 1;
        piVar8 = g;
      }
      if (local_18 == 0x26) {
        piVar8[0x52bd] = (uint)(piVar8[0x52bd] == 0);
        piVar8 = g;
      }
      piVar9 = piVar8;
      if ((local_18 == 0x2e) &&
         (iVar10 = piVar8[0x81d0], piVar8[0x81d0] = iVar10 + 1, piVar9 = g, 2 < iVar10 + 1)) {
        piVar8[0x81d0] = 0;
        piVar9 = g;
      }
      if ((local_18 == 0x17) && (iVar10 = piVar9[0x7459], iVar10 <= piVar9[0x745a])) {
        iVar12 = iVar10 * 4 + 0x1cf60;
        do {
          iVar1 = *(int *)(iVar12 + 4 + (int)piVar9);
          if (((iVar1 == 0) || (*(int *)(iVar1 + 0x158) == 0)) ||
             (bVar7 = true, *(int *)(iVar1 + 0x1c) != 0)) {
            bVar7 = false;
          }
          if (bVar7) {
            PlayerChangeState(*(int *)(iVar12 + 4 + (int)piVar9),0);
            piVar9 = g;
            iVar1 = *(int *)(iVar12 + 4 + (int)g);
            *(undefined4 *)(iVar1 + 0xe0c) = 1;
            *(undefined4 *)(iVar1 + 0x1b8) = 0;
            *(undefined4 *)(iVar1 + 0x1b4) = 0;
          }
          iVar10 = iVar10 + 1;
          iVar12 = iVar12 + 4;
        } while (iVar10 <= piVar9[0x745a]);
      }
      if ((piVar9[0x81cc] != 0) && (local_18 == 0x14)) {
        piVar9[0x33b6] = 0;
        if ((piVar9[0x73db] == 0) || (bVar7 = true, *(int *)(piVar9[0x73db] + 0x158) == 0)) {
          bVar7 = false;
        }
        if (bVar7) {
          *(undefined4 *)(g[0x73db] + 0x262c) = 0;
        }
        piVar9 = g;
        piVar8 = g + 0x33ae;
        g[0x7515] = -1;
        piVar9[0x33ae] = (uint)(*piVar8 != 3) * 3;
        TrainingMenuReset();
      }
    }
    piVar8 = g;
    if ((local_18 == 0x20) && (g[0x81ce] != 0)) {
      do {
        piVar8[0x81cd] = 1;
        *(undefined4 *)(piVar8[0x82d7] + 0x20) = 1;
        iVar10 = piVar8[0x81cb];
        piVar8[0x81cb] = iVar10 + 1;
        if ((piVar8[iVar10 + 0x73da] == 0) ||
           (bVar7 = true, *(int *)(piVar8[iVar10 + 0x73da] + 0x158) == 0)) {
          bVar7 = false;
        }
        piVar9 = g;
      } while ((!bVar7) && (piVar9 = piVar8, piVar8[0x81cb] < piVar8[0x745a]));
      if (piVar9[0x745a] < piVar9[0x81cb]) {
        piVar9[0x81cd] = 0;
        *(undefined4 *)(piVar9[0x82d7] + 0x20) = 0;
        piVar9[0x81cb] = 0;
      }
    }
  }
  if (framestep_0 != 0) {
    framestep_0 = 0;
    keypauseflag = 1;
  }
  if ((((g[0x7309] != 0) && (local_18 != 0)) && (framestep_0 == 0)) &&
     (((local_18 & 0x100) == 0 && (local_18 != 0x58)))) {
    if ((g[0x33ae] != 3) || (local_18 == 0x46)) {
      keypauseflag = 0;
    }
    if (local_18 == 0x46) {
      framestep_0 = 1;
    }
  }
  if (g[0x74e2] == 1) {
    ScreenSnap();
    g[0x74e2] = 0;
  }
  if (local_18 == 0x58) {
    if (g[0x7309] == 0) {
      ScreenSnap();
    }
    else {
      g[0x74e2] = 1;
    }
  }
  return 0;
}

/* CameraMoveAbs @ 0x08094350, 119 bytes */
int CameraMoveAbs(float param_1,float param_2)

{
  int *piVar1;
  
  piVar1 = g;
  g[0x730f] = GHIDRA_F2I(int, param_1);
  piVar1[0x7313] = GHIDRA_F2I(int, param_1);
  piVar1[0x7310] = GHIDRA_F2I(int, param_2);
  piVar1[0x7314] = GHIDRA_F2I(int, param_2);
  piVar1[0x7311] = (int)GHIDRA_FIST32(param_1);
  piVar1[0x7312] = (int)GHIDRA_FIST32(param_2);
  return (int)GHIDRA_FIST32(param_2);
}

/* CameraMoveP @ 0x080943d0, 2350 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: 4 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 16 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 4 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void CameraMoveP(void)

{
  float10 fVar1;
  float10 fVar2;
  float10 fVar3;
  float10 fVar4;
  bool bVar5;
  undefined3 extraout_var;
  int iVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  float local_38;
  int local_24;
  int local_20;
  
  iVar13 = 0;
  local_20 = 0;
  local_24 = 0;
  iVar10 = g[0x1087];
  iVar12 = g[0x1088];
  fVar1 = GHIDRA_I2F(g[0x1086]);
  local_38 = 1.0;
  fVar2 = GHIDRA_I2F(g[0x7313]);
  fVar3 = GHIDRA_I2F(g[0x7314]);
  bVar5 = GameModeInPassiveFightScreen();
  if (GHIDRA_ZEXT8(bVar5) != 0) {
    return;
  }
  iVar15 = g[0x7459];
  piVar9 = g;
  if (iVar15 <= g[0x745a]) {
    iVar11 = iVar15 * 4 + 0x1cf60;
    iVar14 = iVar11;
    do {
      iVar7 = *(int *)(iVar14 + 4 + (int)piVar9);
      if ((iVar7 == 0) || (bVar5 = true, *(int *)(iVar7 + 0x158) == 0)) {
        bVar5 = false;
      }
      if (bVar5) {
        PlayerCalcDraw(*(int *)(iVar11 + 4 + (int)piVar9));
        piVar9 = g;
      }
      iVar15 = iVar15 + 1;
      iVar11 = iVar11 + 4;
      iVar14 = iVar14 + 4;
    } while (iVar15 <= piVar9[0x745a]);
  }
  iVar15 = piVar9[0x7459];
  if (iVar15 <= piVar9[0x745a]) {
    iVar11 = iVar15 * 4 + 0x1cf60;
    do {
      iVar14 = *(int *)(iVar11 + 4 + (int)piVar9);
      if ((iVar14 == 0) || (bVar5 = true, *(int *)(iVar14 + 0x158) == 0)) {
        bVar5 = false;
      }
      if (bVar5) {
        iVar14 = *(int *)((int)piVar9 + iVar11 + 4);
        if (*(int *)(iVar14 + 0x1e8) != 0) {
          if (iVar13 != 0) {
            iVar7 = PlayerGetWidth(*(int *)((int)piVar9 + iVar11 + 4),3,4);
            fVar4 = *(float *)(*(int *)((int)g + iVar11 + 4) + 0x19c);
            iVar6 = PlayerGetWidth(iVar13,3,4);
            piVar9 = g;
            iVar14 = iVar13;
            if ((int)GHIDRA_FIST32(fVar4) - iVar7 < (int)GHIDRA_FIST32(*(float *)(iVar13 + 0x19c)) - iVar6) {
              iVar14 = *(int *)(iVar11 + 4 + (int)g);
            }
          }
          iVar13 = iVar14;
          if (local_20 != 0) {
            iVar14 = PlayerGetWidth(*(int *)(iVar11 + 4 + (int)piVar9),4,4);
            fVar4 = *(float *)(*(int *)((int)g + iVar11 + 4) + 0x19c);
            iVar7 = PlayerGetWidth(local_20,4,4);
            piVar9 = g;
            if ((int)GHIDRA_FIST32(fVar4) + iVar14 <= (int)GHIDRA_FIST32(*(float *)(local_20 + 0x19c)) + iVar7)
            goto LAB_08094646;
          }
          local_20 = *(int *)(iVar11 + 4 + (int)piVar9);
        }
LAB_08094646:
        iVar14 = *(int *)(iVar11 + 4 + (int)piVar9);
        if ((*(int *)(iVar14 + 0x1ec) != 0) &&
           ((local_24 == 0 || (*(float *)(iVar14 + 0x1a0) < *(float *)(local_24 + 0x1a0))))) {
          local_24 = iVar14;
        }
      }
      iVar15 = iVar15 + 1;
      iVar11 = iVar11 + 4;
    } while (iVar15 <= piVar9[0x745a]);
  }
  if (((local_24 != 0) && (iVar13 != 0)) && (local_20 != 0)) {
    iVar7 = PlayerGetWidth(iVar13,3,4);
    iVar14 = PlayerGetWidth(local_20,4,4);
    iVar15 = (int)GHIDRA_FIST32((((float10)(int)GHIDRA_FIST32(*(float *)(iVar13 + 0x19c)) - GHIDRA_I2F(g[0x730f])) -
                        (float10)iVar10) - (float10)iVar7);
    iVar11 = (int)GHIDRA_FIST32(((float)(0x13f - iVar10) -
                        ((float10)(int)GHIDRA_FIST32(*(float *)(local_20 + 0x19c)) - GHIDRA_I2F(g[0x730f]))) -
                        (float10)iVar14);
    iVar7 = (int)GHIDRA_FIST32(*(float *)(iVar13 + 0x19c)) - iVar7;
    iVar10 = iVar14 + -0xa0 + (int)GHIDRA_FIST32(*(float *)(local_20 + 0x19c));
    iVar14 = iVar7 + -0xa0;
    if (*(int *)(iVar13 + 0xe00) == 3) {
      iVar15 = iVar15 + -1;
      iVar14 = iVar7 + -0xa1;
    }
    if (*(int *)(iVar13 + 0xe00) == 4) {
      iVar14 = iVar14 + -2;
      iVar15 = iVar15 + -2;
    }
    if (*(int *)(local_20 + 0xe00) == 3) {
      iVar10 = iVar10 + 1;
      iVar11 = iVar11 + -1;
    }
    if (*(int *)(local_20 + 0xe00) == 4) {
      iVar10 = iVar10 + 2;
      iVar11 = iVar11 + -2;
    }
    if (((iVar15 < 0) && (iVar11 < 0)) ||
       (((iVar15 < -1 || (iVar11 < -1)) && (iVar15 + iVar11 < 0)))) {
      g[0x7313] = GHIDRA_F2I(int, (float)((iVar10 + iVar14) / 2));
    }
    else {
      if (iVar15 < -1) {
        fVar4 = (float10)iVar15 + GHIDRA_I2F(g[0x730f]);
      }
      else {
        if (-2 < iVar11) goto LAB_080948b2;
        fVar4 = GHIDRA_I2F(g[0x730f]) - (float10)iVar11;
      }
      g[0x7313] = GHIDRA_F2I(int, fVar4);
    }
LAB_080948b2:
    piVar9 = g;
    if (((*(float *)(iVar13 + 0x1b4) < -1.0) && (iVar15 < 0)) && (0 < iVar11)) {
      local_38 = ABS(*(float *)(iVar13 + 0x1b4));
    }
    if (((local_38 < *(float *)(local_20 + 0x1b4)) && (iVar11 < 0)) && (0 < iVar15)) {
      local_38 = ABS(*(float *)(local_20 + 0x1b4));
    }
    g[0x7314] = GHIDRA_F2I(int, ((float10)(int)GHIDRA_FIST32((float10)iVar12 + *(float *)(local_24 + 0x1a0)) * fVar1));
  }
  if (piVar9[0x7511] != 0) {
    piVar9[0x7313] = GHIDRA_F2I(int, (float)((int)GHIDRA_FIST32(fVar2 + GHIDRA_I2F(piVar9[0x7313])) / 2));
    piVar9[0x7314] = GHIDRA_F2I(int, (GHIDRA_I2F(piVar9[0x7314]) * ((double)0.15) + fVar3 * ((double)0.85)));
  }
  piVar8 = g;
  if (g[0x7309] != 0) goto LAB_08094b58;
  if (piVar9[0x7511] == 0) {
    g[0x730f] = g[0x7313];
  }
  if (GHIDRA_I2F(piVar8[0x730f]) < GHIDRA_I2F(piVar8[0x7313])) {
    piVar8[0x730f] = GHIDRA_F2I(int, (GHIDRA_I2F(piVar8[0x730f]) + local_38));
    piVar8 = g;
  }
  if (GHIDRA_I2F(piVar8[0x7313]) < GHIDRA_I2F(piVar8[0x730f])) {
    piVar8[0x730f] = GHIDRA_F2I(int, (GHIDRA_I2F(piVar8[0x730f]) - local_38));
    piVar8 = g;
  }
  if (GHIDRA_I2F(piVar8[0x7314]) <= GHIDRA_I2F(piVar8[0x7310])) {
    if (GHIDRA_I2F(piVar8[0x7310]) <= GHIDRA_I2F(piVar8[0x7314])) goto LAB_08094b58;
    fVar2 = GHIDRA_I2F(piVar8[0x7310]) - 0.5;
    piVar8[0x7310] = GHIDRA_F2I(int, fVar2);
    if (GHIDRA_I2F(piVar8[0x7314]) + 5.0 < fVar2) {
      piVar8[0x7310] = GHIDRA_F2I(int, (fVar2 - (fVar2 - GHIDRA_I2F(piVar8[0x7314])) * fVar1 * ((float)0.1f)));
    }
    fVar1 = GHIDRA_I2F(g[0x7314]);
    piVar8 = g;
    if (fVar1 + 0.5 < GHIDRA_I2F(g[0x7310])) goto LAB_08094b58;
  }
  else {
    fVar2 = GHIDRA_I2F(piVar8[0x7310]) + 0.5;
    piVar8[0x7310] = GHIDRA_F2I(int, fVar2);
    if (fVar2 < GHIDRA_I2F(piVar8[0x7314]) - 5.0) {
      piVar8[0x7310] = GHIDRA_F2I(int, ((GHIDRA_I2F(piVar8[0x7314]) - fVar2) * fVar1 * ((float)0.1f) + fVar2));
    }
    fVar1 = GHIDRA_I2F(g[0x7314]);
    piVar8 = g;
    if (GHIDRA_I2F(g[0x7310]) < fVar1 - 0.5) goto LAB_08094b58;
  }
  piVar8 = g;
  g[0x7310] = GHIDRA_F2I(int, fVar1);
LAB_08094b58:
  iVar10 = (int)GHIDRA_FIST32(GHIDRA_I2F(piVar8[0x730f]) - GHIDRA_I2F(piVar8[0x7313]));
  if (iVar10 < 0) {
    iVar10 = -iVar10;
  }
  if ((float10)iVar10 <= local_38 + local_38) {
    piVar8[0x730f] = piVar8[0x7313];
  }
  piVar9 = g;
  if (GHIDRA_I2F(g[0x730f]) < (float)g[0x1082]) {
    g[0x730f] = GHIDRA_F2I(int, (float)g[0x1082]);
  }
  if ((float10)piVar9[0x1083] < GHIDRA_I2F(piVar9[0x730f])) {
    piVar9[0x730f] = GHIDRA_F2I(int, (float10)piVar9[0x1083]);
    piVar9 = g;
  }
  if ((float10)piVar9[0x1085] < GHIDRA_I2F(piVar9[0x7310])) {
    piVar9[0x7310] = GHIDRA_F2I(int, (float10)piVar9[0x1085]);
    piVar9 = g;
  }
  if (GHIDRA_I2F(piVar9[0x7310]) < (float10)piVar9[0x1084]) {
    piVar9[0x7310] = GHIDRA_F2I(int, (float10)piVar9[0x1084]);
    piVar9 = g;
  }
  piVar9[0x7311] = (int)GHIDRA_FIST32(GHIDRA_I2F(piVar9[0x730f]));
  iVar10 = piVar9[0x7459];
  piVar9[0x7312] = (int)GHIDRA_FIST32(GHIDRA_I2F(piVar9[0x7310]));
  if (iVar10 <= piVar9[0x745a]) {
    iVar12 = iVar10 * 4 + 0x1cf60;
    piVar9 = g;
    iVar13 = iVar12;
    do {
      iVar15 = *(int *)(iVar13 + 4 + (int)piVar9);
      if ((iVar15 == 0) || (bVar5 = true, *(int *)(iVar15 + 0x158) == 0)) {
        bVar5 = false;
      }
      if (bVar5) {
        PlayerCalcDraw(*(int *)(iVar12 + 4 + (int)piVar9));
        piVar9 = g;
      }
      iVar10 = iVar10 + 1;
      iVar12 = iVar12 + 4;
      iVar13 = iVar13 + 4;
    } while (iVar10 <= piVar9[0x745a]);
  }
  return;
}

/* ComboAdd @ 0x08094d00, 112 bytes */
void ComboAdd(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  
  piVar4 = g;
  if (param_1 - 1U < 2) {
    iVar2 = g[param_1 * 6 + 0x7542];
    piVar1 = g + param_1 * 6 + 0x7541;
    g[param_1 * 6 + 0x7542] = param_2 + iVar2;
    if ((piVar4[param_1 * 6 + 0x7541] == 0) && (1 < param_2 + iVar2)) {
      piVar4[param_1 * 6 + 0x7545] = piVar4[0x4e64];
    }
    iVar2 = piVar4[param_1 * 6 + 0x7542];
    if (1 < iVar2) {
      iVar3 = piVar4[0x4e65];
      piVar4[param_1 * 6 + 0x7544] = iVar2;
      *piVar1 = iVar3;
      if (999 < iVar2) {
        piVar4[param_1 * 6 + 0x7544] = 999;
      }
    }
  }
  return;
}

/* ComboClear @ 0x08094d70, 32 bytes */
void ComboClear(int param_1)

{
  if (param_1 - 1U < 2) {
    g[param_1 * 6 + 0x7542] = 0;
  }
  return;
}

/* ComboDisplay @ 0x08094d90, 696 bytes
 * FIXUP: frame emulation: 2 stack locals placed at their original offsets in a 0x70-byte frame (a local's address escapes, see apply_frame_emulation) */
void ComboDisplay(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  unsigned char ghidra_frame[0x70] __attribute__((aligned(16)));
#define local_68 (*(int *)(ghidra_frame + 0x8))
#define local_5c (*(char (*)[76])(ghidra_frame + 0x14))
  
  piVar4 = g;
  if (param_1 - 1U < 2) {
    piVar1 = g + param_1 * 6 + 0x7541;
    iVar5 = g[param_1 * 6 + 0x7544];
    if (1 < iVar5) {
      local_68 = g[0x4e63];
      if (g[0x7559] == 4) {
        local_68 = local_68 * 2;
      }
      if (param_1 + -1 == 0) {
        iVar2 = g[param_1 * 6 + 0x7545];
        iVar7 = 0;
        sprintf(local_5c,(char *)(g + 0x4e6d),iVar5);
        if (piVar4[0x4e66] != -1) {
          uVar8 = (uint)(9 < piVar4[param_1 * 6 + 0x7544]);
          if (piVar4[param_1 * 6 + 0x7544] < 100) {
            iVar7 = uVar8 + 1;
          }
          else {
            iVar7 = uVar8 + 2;
          }
          iVar7 = *(int *)(g[piVar4[0x4e66] + 0x414b] + 8) * iVar7;
        }
        piVar6 = (int *)piVar4[0x4e6a];
        uVar8 = 0;
        V_FontDrawBank(local_5c,(int *)g[piVar4[0x4e69] + 0x414b],iVar2 + iVar7 + piVar4[0x4e6b],
                       local_68 + piVar4[0x4e6c],(int)piVar6);
        if (piVar4[0x4e68] != 0) {
          iVar5 = piVar4[0x4e65];
          iVar7 = *piVar1;
          uVar8 = (uint)(iVar7 == iVar5 + -1);
          if (iVar7 == iVar5 + -2) {
            uVar8 = 2;
          }
          if (iVar7 == iVar5 + -3) {
            uVar8 = 1;
          }
          if (iVar7 == iVar5 + -5) {
            uVar8 = 1;
          }
          piVar6 = piVar1;
          if (iVar7 == iVar5 + -7) {
            uVar8 = 1;
          }
        }
        if (piVar4[0x4e66] != -1) {
          V_FontWriteBank((int *)g[piVar4[0x4e66] + 0x414b],iVar2 + uVar8,local_68,piVar4[0x4e67],
                          "%i",piVar4[param_1 * 6 + 0x7544],piVar6,piVar6);
        }
      }
      else {
        iVar7 = (V_Width - g[param_1 * 6 + 0x7545]) + -1;
        sprintf(local_5c,(char *)(g + 0x4e6d),iVar5,param_1 + -1);
        V_FontDrawRightBank(local_5c,(int *)g[piVar4[0x4e69] + 0x414b],iVar7,
                            local_68 + piVar4[0x4e6c],piVar4[0x4e6a]);
        if (piVar4[0x4e66] != -1) {
          iVar5 = FontGetWidth(g[piVar4[0x4e69] + 0x414b],local_5c);
          iVar5 = iVar5 + piVar4[0x4e6b];
          if (piVar4[0x4e68] != 0) {
            iVar2 = piVar4[0x4e65];
            iVar3 = piVar4[param_1 * 6 + 0x7541];
            if (iVar3 == iVar2 + -1) {
              iVar5 = iVar5 + 1;
            }
            if (iVar3 == iVar2 + -2) {
              iVar5 = iVar5 + 2;
            }
            if (iVar3 == iVar2 + -3) {
              iVar5 = iVar5 + 1;
            }
            if (iVar3 == iVar2 + -5) {
              iVar5 = iVar5 + 1;
            }
            if (iVar3 == iVar2 + -7) {
              iVar5 = iVar5 + 1;
            }
          }
          sprintf(local_5c,"%i",piVar4[param_1 * 6 + 0x7544],piVar4);
          V_FontDrawRightBank(local_5c,(int *)g[piVar4[0x4e66] + 0x414b],iVar7 - iVar5,local_68,
                              piVar4[0x4e67]);
        }
      }
    }
  }
  return;
}
#undef local_68
#undef local_5c

/* ComboDisplayUpdate @ 0x08095050, 189 bytes */
void ComboDisplayUpdate(int param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  piVar2 = g;
  if (param_1 - 1U < 2) {
    piVar1 = g + param_1 * 6 + 0x7541;
    if (g[param_1 * 6 + 0x7546] == 0) {
      g[param_1 * 6 + 0x7542] = 0;
    }
    piVar2[param_1 * 6 + 0x7546] = 0;
    if (0 < piVar2[param_1 * 6 + 0x7541]) {
      iVar4 = piVar2[param_1 * 6 + 0x7545];
      if (iVar4 < piVar2[0x4e62]) {
        iVar3 = piVar2[0x4e62] - iVar4;
        if (iVar3 < 0) {
          iVar3 = iVar3 + 7;
        }
        iVar4 = (iVar3 >> 3) + 1 + iVar4;
        piVar2[param_1 * 6 + 0x7545] = iVar4;
        if (piVar2[0x4e62] < iVar4) {
          piVar2[param_1 * 6 + 0x7545] = piVar2[0x4e62];
        }
      }
      *piVar1 = *piVar1 + -1;
    }
    if ((piVar2[param_1 * 6 + 0x7542] < 2) && (*piVar1 == 0)) {
      iVar4 = piVar2[param_1 * 6 + 0x7545];
      iVar3 = piVar2[0x4e64];
      if (iVar3 < iVar4) {
        iVar4 = iVar4 + -3;
        piVar2[param_1 * 6 + 0x7545] = iVar4;
        iVar3 = piVar2[0x4e64];
      }
      if (iVar4 < iVar3) {
        piVar2[param_1 * 6 + 0x7545] = iVar3;
        piVar2[param_1 * 6 + 0x7544] = 0;
      }
    }
  }
  return;
}

/* PlayerComboCountCheck @ 0x08095110, 155 bytes */
void PlayerComboCountCheck(int param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)ArrayScanFirst(*(int *)(param_1 + 0x220));
  while( true ) {
    if (piVar1 == (int *)0x0) {
      *(undefined4 *)(param_1 + 0x1398) = 0;
      return;
    }
    if (((*(int *)(*piVar1 + 0xe04) == 2) && (iVar2 = PlayerLyingDead(*piVar1), iVar2 == 0)) ||
       ((*(int *)(param_1 + 0x1158) != 0 && (*(int *)(param_1 + 0x1204) != 0)))) break;
    ArrayDelete(*(int *)(param_1 + 0x220),*(int *)(*(int *)(param_1 + 0x220) + 0x1c));
    piVar1 = (int *)ArrayScanNext(*(int *)(param_1 + 0x220));
  }
  g[*(int *)(param_1 + 0xc) * 6 + 0x7546] = 1;
  return;
}

/* GameBGDraw @ 0x080951b0, 309 bytes
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 1 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact) */
void GameBGDraw(void)

{
  int *piVar1;
  int iVar2;
  
  BGArrayMoveOffset((int *)g[0x6ed4],(float)g[0x7311],(float)g[0x7312],-g[0x7315],-g[0x7316]);
  BGArrayDrawLayer(g[0x6ed4],0);
  piVar1 = g;
  g[0x4140] = g[0x4141];
  iVar2 = piVar1[0x4142];
  if (iVar2 != -1) {
    iVar2 = BGAccessID(piVar1[0x6ed4],iVar2);
    if (iVar2 != 0) {
      g[0x4140] = (int)GHIDRA_FIST32((float)g[0x4140] +
                             ((float10)*(int *)(iVar2 + 0x10) -
                             (float)g[0x7312] * *(float *)(iVar2 + 0x20)) + ((double)0.999999));
    }
  }
  if (0 < g[0x7316]) {
    W_BoxFill(0,V_Height + -1,V_Width + -1,V_Height - g[0x7316],0);
  }
  if (g[0x7316] < 0) {
    W_BoxFill(0,0,V_Width + -1,g[0x7316] ^ 0xffffffff,0);
  }
  return;
}

/* GameFGDraw @ 0x080952f0, 26 bytes */
void GameFGDraw(void)

{
  BGArrayDrawLayer(g[0x6ed4],1);
  return;
}

/* GameBarsDraw @ 0x08095310, 4327 bytes */
void GameBarsDraw(int param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  undefined4 extraout_EDX;
  undefined4 uVar4;
  undefined4 extraout_EDX_00;
  int *piVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  int iVar10;
  int *piVar11;
  int iVar12;
  int iVar13;
  char *__format;
  int local_c4;
  int local_c0;
  int local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  int *local_a0;
  int local_9c;
  int local_98;
  int local_94;
  int *local_90;
  int local_8c;
  int *local_88;
  int *local_84;
  int local_80;
  int local_7c;
  int local_78;
  int *local_74;
  int local_70;
  int local_6c;
  int local_68;
  int *local_64;
  int local_60;
  int *local_5c;
  int *local_58;
  int local_54;
  int *local_50;
  int local_34;
  int local_30;
  int local_2c;
  
  piVar2 = g;
  local_50 = g;
  piVar11 = g + 0x46cf;
  piVar3 = g + 0x4e29;
  piVar8 = g + 0x4157;
  piVar5 = g + 0x5090;
  local_30 = 0;
  local_c4 = 0;
  do {
    local_2c = 0;
    local_ac = 0;
    local_b8 = 0;
    local_bc = 0;
    local_c0 = 0x1cf6c;
    do {
      if (*(int *)(local_c0 + 4 + (int)local_50) == 0) {
        local_34 = 1;
        piVar7 = piVar8;
        if (1 < *(int *)((int)local_50 + local_ac + 0xcee4)) {
          piVar7 = piVar2 + 0x449f;
        }
      }
      else {
        local_34 = 3;
        piVar7 = piVar2 + 0x426f;
      }
      if (local_2c < local_34 + local_2c) {
        piVar9 = (int *)((int)piVar7 + local_bc + local_c4 + 0x14);
        iVar6 = local_b8;
        iVar12 = local_2c;
        do {
          iVar12 = iVar12 + 2;
          iVar10 = iVar6 + 4;
          piVar1 = (int *)((int)piVar7 + iVar6);
          iVar6 = iVar6 + 0x460;
          SysExplodCreateDraw_Fight(piVar9,*piVar1,*(int *)((int)piVar7 + iVar10),param_1);
          piVar9 = piVar9 + 0x118;
        } while (iVar12 < local_34 + local_2c);
        local_50 = g;
      }
      local_2c = local_2c + 1;
      local_ac = local_ac + 0x1a9c;
      local_b8 = local_b8 + 0x230;
      local_bc = local_bc + 0x230;
      local_c0 = local_c0 + 4;
    } while (local_2c < 2);
    local_30 = local_30 + 1;
    local_c4 = local_c4 + 0x6c;
  } while (local_30 < 3);
  local_2c = 0;
  while( true ) {
    if (local_50[local_2c + 0x73dc] == 0) {
      local_34 = 1;
      piVar7 = piVar8;
      if (1 < local_50[local_2c * 0x6a7 + 0x33b9]) {
        piVar7 = piVar2 + 0x449f;
      }
    }
    else {
      local_34 = 3;
      piVar7 = piVar2 + 0x426f;
    }
    iVar6 = local_2c;
    if (local_2c < local_34 + local_2c) {
      while( true ) {
        GameLifeBarDraw(iVar6 + 1,local_50[iVar6 + 0x73da],piVar7 + iVar6 * 0x8c,param_1);
        if (local_34 + local_2c <= iVar6 + 2) break;
        local_50 = g;
        iVar6 = iVar6 + 2;
      }
    }
    local_2c = local_2c + 1;
    if (1 < local_2c) break;
    local_50 = g;
  }
  local_30 = 0;
  piVar8 = piVar11;
  do {
    piVar7 = piVar8 + 5;
    iVar12 = 1;
    iVar6 = 0;
    do {
      iVar10 = iVar6 + 4;
      piVar9 = (int *)((int)piVar11 + iVar6);
      iVar6 = iVar6 + 0x230;
      SysExplodCreateDraw_Fight(piVar7,*piVar9,*(int *)(iVar10 + (int)piVar11),param_1);
      piVar7 = piVar7 + 0x8c;
      iVar12 = iVar12 + -1;
    } while (-1 < iVar12);
    piVar8 = piVar8 + 0x1b;
    local_30 = local_30 + 1;
  } while (local_30 < 3);
  iVar6 = 0;
  do {
    iVar12 = iVar6 + 1;
    GamePowerBarDraw(iVar12,g[iVar6 + 0x73da],piVar2[iVar6 * 0x8c + 0x46d1] + piVar11[iVar6 * 0x8c],
                     piVar11[iVar6 * 0x8c + 1],piVar2[iVar6 * 0x8c + 0x46d2] + piVar11[iVar6 * 0x8c]
                     ,param_1);
    iVar6 = iVar12;
  } while (iVar12 < 2);
  piVar7 = piVar2 + 0x47e7;
  iVar6 = 0;
  piVar8 = piVar2 + 0x47f6;
  iVar12 = 1;
  local_a8 = 0x1cf64;
  uVar4 = extraout_EDX;
  do {
    sprintf((char *)piVar8,"%i",*(int *)(*(int *)((int)g + local_a8 + 4) + 0x180) / 1000,uVar4);
    piVar8 = piVar8 + 0x1b;
    iVar10 = iVar6 + 4;
    piVar9 = (int *)((int)piVar11 + iVar6);
    iVar6 = iVar6 + 0x230;
    SysExplodCreateDraw_Fight(piVar7,*piVar9,*(int *)(iVar10 + (int)piVar11),param_1);
    piVar7 = piVar7 + 0x1b;
    local_a8 = local_a8 + 4;
    iVar12 = iVar12 + -1;
    uVar4 = extraout_EDX_00;
  } while (-1 < iVar12);
  local_a0 = piVar2 + 0x4add;
  local_50 = g;
  local_2c = 0;
  local_a4 = 0;
  do {
    if (local_50[0x33b4] != 2 - local_2c) {
      iVar6 = *(int *)((int)local_50 + local_a4 + 0xcee4);
      if (1 < iVar6) {
        iVar13 = 0;
        iVar12 = local_a0[0x51];
        iVar10 = local_a0[0x52];
        if (0 < iVar6 + -1) {
          do {
            iVar13 = iVar13 + 1;
            SysExplodCreateDraw_Fight(local_a0,iVar12,iVar10,param_1);
            iVar10 = iVar10 + local_a0[0x55];
            iVar12 = iVar12 + local_a0[0x54];
          } while (iVar13 < *(int *)((int)local_50 + local_a4 + 0xcee4) + -1);
          local_50 = g;
        }
      }
    }
    local_2c = local_2c + 1;
    local_a0 = local_a0 + 0x56;
    local_a4 = local_a4 + 0x1a9c;
  } while (local_2c < 2);
  local_2c = 0;
  local_98 = 0x1cf6c;
  local_9c = 0;
  local_b4 = 0;
  do {
    if (*(int *)(local_98 + 4 + (int)local_50) == 0) {
      local_34 = 1;
      piVar8 = piVar2 + 0x4831;
      if (1 < *(int *)((int)local_50 + local_9c + 0xcee4)) {
        piVar8 = piVar2 + 0x49f9;
      }
    }
    else {
      local_34 = 3;
      piVar8 = piVar2 + 0x4915;
    }
    if (local_2c < local_34 + local_2c) {
      iVar6 = local_2c * 4;
      piVar11 = (int *)(local_b4 + (int)piVar8);
      iVar12 = local_2c;
      do {
        iVar12 = iVar12 + 2;
        iVar10 = iVar6 + 0x370;
        iVar13 = iVar6 + 0x360;
        iVar6 = iVar6 + 8;
        SysExplodCreateDraw_Fight
                  (piVar11,*(int *)((int)piVar8 + iVar13),*(int *)((int)piVar8 + iVar10),param_1);
        piVar11 = piVar11 + 0x6c;
      } while (iVar12 < local_34 + local_2c);
      local_50 = g;
    }
    local_2c = local_2c + 1;
    local_98 = local_98 + 4;
    local_9c = local_9c + 0x1a9c;
    local_b4 = local_b4 + 0xd8;
  } while (local_2c < 2);
  local_2c = 0;
  iVar6 = 0;
  iVar12 = 0x1cf6c;
  do {
    if (*(int *)(iVar12 + 4 + (int)local_50) == 0) {
      local_34 = 1;
      piVar8 = piVar2 + 0x4831;
      if (1 < *(int *)((int)local_50 + iVar6 + 0xcee4)) {
        piVar8 = piVar2 + 0x49f9;
      }
    }
    else {
      local_34 = 3;
      piVar8 = piVar2 + 0x4915;
    }
    local_34 = local_2c + -1 + local_34;
    if (-1 < local_34) {
      while( true ) {
        SysExplodCreateDraw((int *)local_50[0x52bf],piVar8 + local_34 * 0x36 + 0x1b,
                            *(int **)(local_50[local_34 + 0x73da] + 0x13ac),
                            *(int **)(*(int *)local_50[local_34 + 0x73da] + 0x11cc),
                            (int)(local_50 + 0x414b),piVar8[local_34 + 0xd8],piVar8[local_34 + 0xdc]
                            ,param_1);
        local_34 = local_34 + -2;
        if (local_34 < 0) break;
        local_50 = g;
      }
      local_50 = g;
    }
    iVar12 = iVar12 + 4;
    local_2c = local_2c + 1;
    iVar6 = iVar6 + 0x1a9c;
  } while (local_2c < 2);
  local_90 = piVar2 + 0x4add;
  local_2c = 0;
  local_94 = 0;
  do {
    piVar8 = local_50;
    if (local_50[0x33b4] != 2 - local_2c) {
      piVar11 = (int *)((int)local_50 + local_94 + 0xcee0);
      iVar6 = *(int *)((int)local_50 + local_94 + 0xcee4);
      if (1 < iVar6) {
        iVar13 = 0;
        iVar12 = local_90[0x51];
        iVar10 = local_90[0x52];
        if (0 < iVar6) {
          do {
            if (iVar13 != *piVar11) {
              iVar6 = iVar13 + local_2c * 4;
              if (piVar2[iVar6 + 0x52b5] != 0) {
                SysExplodCreateDraw((int *)local_50[0x52bf],local_90 + 0x1b,
                                    (int *)piVar2[iVar6 + 0x52b5],(int *)piVar2[0x414a],
                                    (int)(local_50 + 0x414b),iVar12,iVar10,param_1);
                local_50 = g;
              }
              iVar12 = iVar12 + local_90[0x54];
              iVar10 = iVar10 + local_90[0x55];
            }
            iVar13 = iVar13 + 1;
          } while (iVar13 < *(int *)((int)piVar8 + local_94 + 0xcee4));
        }
      }
    }
    local_2c = local_2c + 1;
    local_90 = local_90 + 0x56;
    local_94 = local_94 + 0x1a9c;
  } while (local_2c < 2);
  local_84 = piVar2 + 0x4b13;
  local_88 = piVar2 + 0x4add;
  local_8c = 0;
  local_2c = 1;
  do {
    if (1 < *(int *)((int)local_50 + local_8c + 0xcee4)) {
      iVar10 = 0;
      iVar6 = local_88[0x51];
      iVar12 = local_88[0x52];
      if (0 < *(int *)((int)local_50 + local_8c + 0xcee0)) {
        do {
          iVar10 = iVar10 + 1;
          SysExplodCreateDraw_Fight(local_84,iVar6,iVar12,param_1);
          iVar6 = iVar6 + local_88[0x54];
          iVar12 = iVar12 + local_88[0x55];
        } while (iVar10 < *(int *)((int)local_50 + local_8c + 0xcee0));
        local_50 = g;
      }
    }
    local_84 = local_84 + 0x56;
    local_88 = local_88 + 0x56;
    local_8c = local_8c + 0x1a9c;
    local_2c = local_2c + -1;
  } while (-1 < local_2c);
  local_2c = 0;
  local_7c = 0x1cf6c;
  local_80 = 0;
  local_b0 = 0;
  do {
    if (*(int *)(local_7c + 4 + (int)local_50) == 0) {
      local_34 = 1;
      piVar8 = piVar2 + 0x4b89;
      if (1 < *(int *)((int)local_50 + local_80 + 0xcee4)) {
        piVar8 = piVar2 + 0x4d49;
      }
    }
    else {
      local_34 = 3;
      piVar8 = piVar2 + 0x4c69;
    }
    if (local_2c < local_34 + local_2c) {
      iVar6 = local_2c * 4;
      piVar11 = (int *)(local_b0 + (int)piVar8);
      iVar12 = local_2c;
      do {
        iVar12 = iVar12 + 2;
        iVar10 = iVar6 + 0x370;
        iVar13 = iVar6 + 0x360;
        iVar6 = iVar6 + 8;
        SysExplodCreateDraw_Fight
                  (piVar11,*(int *)((int)piVar8 + iVar13),*(int *)((int)piVar8 + iVar10),param_1);
        piVar11 = piVar11 + 0x36;
      } while (iVar12 < local_34 + local_2c);
      local_50 = g;
    }
    iVar6 = local_2c + 1;
    local_7c = local_7c + 4;
    local_80 = local_80 + 0x1a9c;
    local_b0 = local_b0 + 0x6c;
    local_2c = iVar6;
  } while (iVar6 < 2);
  local_2c = 0;
  while( true ) {
    if (local_50[local_2c + 0x73dc] == 0) {
      local_34 = 1;
      piVar8 = piVar2 + 0x4b89;
      if (1 < local_50[local_2c * 0x6a7 + 0x33b9]) {
        piVar8 = piVar2 + 0x4d49;
      }
    }
    else {
      local_34 = 3;
      piVar8 = piVar2 + 0x4c69;
    }
    iVar12 = local_2c;
    iVar10 = local_2c;
    if (local_2c < local_34 + local_2c) {
      while( true ) {
        iVar12 = iVar10 + 2;
        strncpy((char *)(piVar8 + iVar10 * 0x1b + 0x7b),
                (char *)(*(int *)local_50[iVar10 + 0x73da] + 0x30),0x2f);
        iVar6 = piVar8[iVar10 + 0xd8];
        SysExplodCreateDraw_Fight(piVar8 + iVar10 * 0x1b + 0x6c,iVar6,piVar8[iVar10 + 0xdc],param_1)
        ;
        if (local_34 + local_2c <= iVar12) break;
        local_50 = g;
        iVar10 = iVar12;
      }
    }
    local_2c = local_2c + 1;
    if (1 < local_2c) break;
    local_50 = g;
  }
  SysExplodCreateDraw_Fight(piVar3,piVar2[0x4e5f],piVar2[0x4e60],param_1);
  if (g[0x7515] == -1) {
    iVar10 = 0x6f;
    __format = "%c";
  }
  else {
    iVar10 = g[0x7515] / piVar2[0x4e61];
    __format = "%i";
    iVar6 = iVar12;
  }
  sprintf((char *)(piVar2 + 0x4e53),__format,iVar10,iVar6);
  iVar6 = 0;
  SysExplodCreateDraw_Fight(piVar2 + 0x4e44,piVar2[0x4e5f],piVar2[0x4e60],param_1);
  local_58 = piVar2 + 0x509f;
  local_54 = 0x870;
  local_60 = 0;
  local_68 = 0;
  local_6c = 0x1d410;
  local_70 = 0x880;
  local_78 = 0;
  local_74 = piVar5;
  local_64 = piVar5;
  local_5c = piVar5;
  do {
    local_50 = g;
    iVar12 = *(int *)(local_60 + 0x1d41c + (int)g);
    if (piVar2[0x52b4] < iVar12) {
      sprintf((char *)local_58,"%i",*(undefined4 *)(local_60 + 0x1d41c + (int)g),iVar12);
      SysExplodCreateDraw_Fight
                (local_5c,*(int *)((int)piVar2 + local_60 + 0x14ab0),
                 *(int *)(local_54 + 8 + (int)piVar5),param_1);
    }
    else {
      local_30 = 0;
      if (0 < iVar12) {
        iVar12 = local_78 * 4 + 0x1d450;
        iVar10 = local_60;
        do {
          iVar13 = *(int *)(iVar12 + 0x14 + (int)local_50);
          if (iVar13 != -1) {
            SysExplodCreateDraw_Fight
                      (local_74 + iVar13 * 0x1b + 0x36,
                       local_30 * *(int *)(iVar10 + 0x880 + (int)piVar5) +
                       *(int *)(iVar10 + 0x870 + (int)piVar5),
                       local_30 * *(int *)((int)piVar2 + iVar10 + 0x14ac8) +
                       *(int *)((int)piVar2 + iVar10 + 0x14ab8),param_1);
            local_50 = g;
          }
          local_30 = local_30 + 1;
          iVar12 = iVar12 + 4;
          iVar13 = iVar10 + 0x1d41c;
          iVar10 = iVar6 * 4;
        } while (local_30 < *(int *)(iVar13 + (int)local_50));
      }
      local_30 = 0;
      if (0 < *(int *)(local_60 + 0x1d41c + (int)local_50)) {
        iVar12 = local_68 * 4 + 0x1d4a0;
        do {
          iVar10 = *(int *)(iVar12 + 0x14 + (int)local_50);
          if (iVar10 != -1) {
            SysExplodCreateDraw_Fight
                      (local_64 + iVar10 * 0x1b + 0x36,
                       local_30 * *(int *)(local_70 + (int)piVar5) +
                       *(int *)(local_54 + (int)piVar5),
                       local_30 * *(int *)((int)piVar2 + local_70 + 0x14248) +
                       *(int *)((int)piVar2 + local_54 + 0x14248),param_1);
            local_50 = g;
          }
          local_30 = local_30 + 1;
          iVar12 = iVar12 + 4;
        } while (local_30 < *(int *)(local_6c + 0xc + (int)local_50));
      }
    }
    local_54 = local_54 + 4;
    local_58 = local_58 + 0x1b;
    local_5c = local_5c + 0x1b;
    local_60 = local_60 + 4;
    local_64 = local_64 + 0xf3;
    local_68 = local_68 + 10;
    local_6c = local_6c + 4;
    local_70 = local_70 + 4;
    local_74 = local_74 + 0xf3;
    local_78 = local_78 + 10;
    iVar6 = iVar6 + 1;
  } while (iVar6 < 2);
  return;
}

/* GameLifeBarDraw @ 0x08096400, 1210 bytes
 * FIXUP: frame emulation: 3 stack locals placed at their original offsets in a 0x140-byte frame (a local's address escapes, see apply_frame_emulation) */
void GameLifeBarDraw(undefined4 param_1,int param_2,int *param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int *piVar11;
  unsigned char ghidra_frame[0x140] __attribute__((aligned(16)));
#define local_134 (*(int *)(ghidra_frame + 0xc))
#define local_120 (*(uint *)(ghidra_frame + 0x20))
#define local_11c (*(char (*)[268])(ghidra_frame + 0x24))
  
  iVar4 = W_y1;
  iVar3 = W_x2;
  iVar2 = W_x1;
  iVar1 = W_y2;
  local_134 = -1;
  iVar7 = (g[0x7559] == 4) + 1;
  iVar8 = param_3[1] * iVar7;
  uVar9 = (*param_3 + param_3[2]) * iVar7;
  uVar10 = (*param_3 + param_3[3]) * iVar7;
  uVar5 = uVar9;
  if (uVar9 - uVar10 != 0 && (int)uVar10 <= (int)uVar9) {
    local_134 = 1;
    uVar5 = uVar10;
    uVar10 = uVar9;
  }
  uVar9 = (int)(*(int *)(param_2 + 0x16c) * (uVar10 - uVar5)) / *(int *)(param_2 + 0x164);
  iVar7 = (int)(*(int *)(param_2 + 0x168) * (uVar10 - uVar5)) / *(int *)(param_2 + 0x164);
  local_120 = iVar7 + 1U & (*(int *)(param_2 + 0x168) == 0) - 1;
  if ((int)uVar9 < (int)local_120) {
    local_120 = uVar9;
  }
  W_Define(uVar5,W_y1,uVar10,W_y2);
  if (local_134 == 1) {
    iVar6 = *(int *)(param_2 + 0x168);
    if (iVar6 < *(int *)(param_2 + 0x16c)) {
      W_Define(uVar10 - local_120,iVar4,uVar10 - uVar9,iVar1);
      SysExplodCreateDraw_Fight(param_3 + 0x56,*param_3,param_3[1],param_4);
      iVar6 = *(int *)(param_2 + 0x168);
    }
    if (0 < iVar6) {
      W_Define(uVar10 - iVar7,iVar4,uVar10,iVar1);
      SysExplodCreateDraw_Fight(param_3 + 0x71,*param_3,param_3[1],param_4);
    }
    if ((g[0x81cd] == 0) || (param_3[0x79] != param_4)) goto LAB_08096896;
    W_Define(uVar5,0,uVar10,V_Height - 1);
    sprintf(local_11c,"%i",*(undefined4 *)(param_2 + 0x160));
    uVar5 = makecol(0x80,0x80,0);
    V_FontDraw(local_11c,(int *)g[0x413a],(uVar10 - iVar7) + 1,iVar8 + 5,uVar5);
    sprintf(local_11c,"%3i",*(int *)(param_2 + 0x16c) - *(int *)(param_2 + 0x160));
    if (*(int *)(param_2 + 0x16c) == *(int *)(param_2 + 0x160) ||
        *(int *)(param_2 + 0x16c) - *(int *)(param_2 + 0x160) < 0) goto LAB_08096896;
    uVar9 = makecol(0x80,0,0);
    iVar7 = (uVar10 - local_120) + -0xb;
    piVar11 = (int *)g[0x413a];
  }
  else {
    iVar6 = *(int *)(param_2 + 0x168);
    if (iVar6 < *(int *)(param_2 + 0x16c)) {
      W_Define(uVar5 + local_120,iVar4,uVar5 + uVar9,iVar1);
      SysExplodCreateDraw_Fight(param_3 + 0x56,*param_3,param_3[1],param_4);
      iVar6 = *(int *)(param_2 + 0x168);
    }
    if (0 < iVar6) {
      W_Define(uVar5 + iVar7,iVar4,uVar5,iVar1);
      SysExplodCreateDraw_Fight(param_3 + 0x71,*param_3,param_3[1],param_4);
    }
    if ((g[0x81cd] == 0) || (param_3[0x79] != param_4)) goto LAB_08096896;
    W_Define(uVar5,0,uVar10,V_Height - 1);
    sprintf(local_11c,"%i",*(undefined4 *)(param_2 + 0x160));
    uVar10 = makecol(0x80,0x80,0);
    V_FontDrawRight(local_11c,(int *)g[0x413a],iVar7 + -1 + uVar5,iVar8 + 5,uVar10);
    sprintf(local_11c,"%i",*(int *)(param_2 + 0x16c) - *(int *)(param_2 + 0x160));
    if (*(int *)(param_2 + 0x16c) == *(int *)(param_2 + 0x160) ||
        *(int *)(param_2 + 0x16c) - *(int *)(param_2 + 0x160) < 0) goto LAB_08096896;
    uVar9 = makecol(0x80,0,0);
    iVar7 = local_120 + 1 + uVar5;
    piVar11 = (int *)g[0x413a];
  }
  V_FontDraw(local_11c,piVar11,iVar7,iVar8 + 5,uVar9);
LAB_08096896:
  W_Define(iVar2,iVar4,iVar3,iVar1);
  return;
}
#undef local_134
#undef local_120
#undef local_11c

/* GameBarsUpdate @ 0x080968c0, 110 bytes */
void GameBarsUpdate(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = g[0x73da];
  iVar2 = g[0x73db];
  iVar3 = g[0x73dc];
  iVar4 = g[0x73dd];
  GameLifeBarUpdate(iVar1);
  GameLifeBarUpdate(iVar2);
  if (iVar3 != 0) {
    GameLifeBarUpdate(iVar3);
  }
  if (iVar4 != 0) {
    GameLifeBarUpdate(iVar4);
  }
  GamePowerBarUpdate(iVar1);
  GamePowerBarUpdate(iVar2);
  return;
}

/* GameLifeBarUpdate @ 0x08096930, 372 bytes
 * FIXUP: 2 inexact floating constants cast to their type (apply_const_casts) */
void GameLifeBarUpdate(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = (*(int *)(param_1 + 0x164) * 9) / 1000;
  iVar4 = *(int *)(param_1 + 0x164) / 0x19;
  if (iVar2 == 0) {
    iVar2 = 1;
  }
  if (iVar4 == 0) {
    iVar4 = 1;
  }
  if ((g[0x7309] == 0) && (g[0x750d] == 0)) {
    iVar1 = *(int *)(param_1 + 0x168);
    iVar3 = *(int *)(param_1 + 0x160);
    if (iVar3 < iVar1) {
      iVar1 = (int)GHIDRA_FIST32((double)iVar1 - ((double)(iVar1 - iVar3) * ((double)0.1) + (double)iVar2));
      iVar3 = *(int *)(param_1 + 0x160);
      *(int *)(param_1 + 0x168) = iVar1;
      if (iVar1 < iVar3) {
        *(int *)(param_1 + 0x168) = iVar3;
        iVar1 = iVar3;
      }
    }
    if (iVar1 < iVar3) {
      if (iVar3 - iVar1 < iVar4) {
        iVar4 = iVar3 - iVar1;
      }
      *(int *)(param_1 + 0x168) = iVar4 + iVar1;
    }
    if (((*(int *)(param_1 + 0xe04) != 2) || (iVar2 = PlayerLyingDead(param_1), 0x3c < iVar2)) &&
       (iVar2 = *(int *)(param_1 + 0x168), iVar2 == *(int *)(param_1 + 0x160))) {
      iVar4 = *(int *)(param_1 + 0x16c);
      if (iVar2 < iVar4) {
        iVar4 = (int)GHIDRA_FIST32((double)iVar4 - (double)(iVar4 - iVar2) * ((double)0.1));
        iVar2 = *(int *)(param_1 + 0x168);
        *(int *)(param_1 + 0x16c) = iVar4;
      }
      if (iVar4 < iVar2) {
        *(int *)(param_1 + 0x16c) = iVar2;
      }
    }
  }
  return;
}

/* GamePowerBarDraw @ 0x08096ab0, 338 bytes */
undefined4
GamePowerBarDraw(int param_1,int param_2,int param_3,undefined4 param_4,int param_5,int param_6)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  int local_28;
  
  iVar5 = W_y1;
  iVar4 = W_x2;
  iVar3 = W_x1;
  iVar2 = W_y2;
  piVar1 = g;
  local_28 = -1;
  iVar6 = (g[0x7559] == 4) + 1;
  uVar10 = param_3 * iVar6;
  uVar8 = param_5 * iVar6;
  uVar9 = uVar8;
  if (uVar10 - uVar8 != 0 && (int)uVar8 <= (int)uVar10) {
    local_28 = 1;
    uVar9 = uVar10;
    uVar10 = uVar8;
  }
  iVar6 = (int)(((uVar9 - uVar10) + 1) * *(int *)(param_2 + 0x180)) / **(int **)(param_2 + 0x174);
  if (local_28 == 1) {
    if (iVar6 < 1) goto LAB_08096bd6;
    W_Define((uVar9 - iVar6) + 1,0,uVar9,V_Height - 1);
    iVar6 = piVar1[param_1 * 0x8c + 0x4644];
    iVar11 = piVar1[param_1 * 0x8c + 0x4643];
  }
  else {
    if (iVar6 < 1) goto LAB_08096bd6;
    W_Define(iVar6 + -1 + uVar10,0,uVar10,V_Height - 1);
    iVar6 = piVar1[param_1 * 0x8c + 0x4644];
    iVar11 = piVar1[param_1 * 0x8c + 0x4643];
  }
  SysExplodCreateDraw_Fight(piVar1 + param_1 * 0x8c + 0x46b4,iVar11,iVar6,param_6);
LAB_08096bd6:
  uVar7 = W_Define(iVar3,iVar5,iVar4,iVar2);
  return uVar7;
}

/* GamePowerBarUpdate @ 0x08096c10, 225 bytes */
int GamePowerBarUpdate(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if ((g[0x7309] == 0) && (g[0x750d] == 0)) {
    iVar2 = *(int *)(param_1 + 0x180);
    iVar3 = *(int *)(param_1 + 0x178);
    if (iVar2 < iVar3) {
      iVar2 = (iVar3 - iVar2) / 0x14 + 0xf + iVar2;
      *(int *)(param_1 + 0x180) = iVar2;
    }
    if (iVar2 <= iVar3) goto LAB_08096c71;
    *(int *)(param_1 + 0x180) = iVar3;
  }
  iVar3 = *(int *)(param_1 + 0x178);
LAB_08096c71:
  iVar1 = iVar3 / 1000;
  iVar2 = *(int *)(param_1 + 0x184);
  if (iVar2 != iVar1) {
    if ((iVar2 < iVar1) && (iVar1 < 10)) {
      GameSndPlay((int *)g[0x4155],g[*(int *)(param_1 + 0x178) / 1000 + 0x481d],g[iVar1 + 0x4827],0)
      ;
      iVar3 = *(int *)(param_1 + 0x178);
    }
    iVar2 = iVar3 * 0x10624dd3;
    *(int *)(param_1 + 0x184) = iVar3 / 1000;
  }
  return iVar2;
}

/* RequestNewAftImg @ 0x08096d00, 48 bytes */
int RequestNewAftImg(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < *(int *)(param_1 + 0xc)) {
    do {
      iVar1 = ArrayAccessGrpItem(param_1,0,iVar2);
      if (*(int *)(iVar1 + 8) == 0) {
        return iVar1;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < *(int *)(param_1 + 0xc));
  }
  return 0;
}

/* GameAftImgReset @ 0x08096d30, 53 bytes */
void GameAftImgReset(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  if (0 < *(int *)(param_1 + 0xc)) {
    do {
      iVar2 = iVar1 + 1;
      iVar1 = ArrayAccessGrpItem(param_1,0,iVar1);
      *(undefined4 *)(iVar1 + 0x18) = 0;
      *(undefined4 *)(iVar1 + 8) = 0;
      iVar1 = iVar2;
    } while (iVar2 < *(int *)(param_1 + 0xc));
  }
  return;
}

/* GameAftImgCount @ 0x08096d70, 49 bytes */
int GameAftImgCount(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar2 = 0;
  if (0 < *(int *)(param_1 + 0xc)) {
    do {
      iVar1 = ArrayAccessGrpItem(param_1,0,iVar2);
      if (*(int *)(iVar1 + 8) != 0) {
        iVar3 = iVar3 + 1;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < *(int *)(param_1 + 0xc));
  }
  return iVar3;
}

/* PlayerAftImgUpdate @ 0x08096db0, 200 bytes
 * FIXUP: untyped (undefined4) <-> float moves kept as bit copies: 0 assignments, 1 calls, 0 returns
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void PlayerAftImgUpdate(int param_1)

{
  int *piVar1;
  float10 fVar2;
  int iVar3;
  
  piVar1 = *(int **)(param_1 + 0x1394);
  if ((*(int *)(param_1 + 0x15c) == 0) && (piVar1 != (int *)0x0)) {
    if (*(int *)(param_1 + 0x1380) == 0) {
      fVar2 = 0.0;
    }
    else {
      fVar2 = *(float *)(param_1 + 0x137c);
    }
    iVar3 = AftImgUpdate(piVar1,(float)g[0x7311] + *(float *)(param_1 + 0x1354),(float)g[0x7312] + *(float *)(param_1 + 0x1358),*(float *)(param_1 + 0x7c) * *(float *)(param_1 + 0x1348) *
                         *(float *)(param_1 + 0x134c),GHIDRA_F2I(undefined4, *(float *)(param_1 + 0x80) * *(float *)(param_1 + 0x1348) *
                         *(float *)(param_1 + 0x1350)),fVar2,(uint)(*(int *)(param_1 + 400) != 1),(uint)(*(int *)(param_1 + 0xe18) == 0));
    if (iVar3 == 0) {
      piVar1[2] = 0;
      *(undefined4 *)(param_1 + 0x1394) = 0;
    }
  }
  return;
}

/* PlayerAftImgDraw @ 0x08096e80, 72 bytes */
void PlayerAftImgDraw(int param_1)

{
  if (*(int **)(param_1 + 0x1394) != (int *)0x0) {
    AftImgDraw(*(int **)(param_1 + 0x1394),-g[0x7315] - g[0x7311],-g[0x7316] - g[0x7312],
               *(int *)(param_1 + 0x1cc));
  }
  return;
}

/* ProjArrayAftImgUpdate @ 0x08096ed0, 46 bytes */
void ProjArrayAftImgUpdate(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *param_1;
  iVar2 = ArrayScanFirst(iVar1);
  while (iVar2 != 0) {
    ProjAftImgUpdate(iVar2);
    iVar2 = ArrayScanNext(iVar1);
  }
  return;
}

/* ProjAftImgUpdate @ 0x08096f00, 156 bytes
 * FIXUP: untyped (undefined4) <-> float moves kept as bit copies: 0 assignments, 1 calls, 0 returns */
void ProjAftImgUpdate(int param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)(param_1 + 0x2d8);
  if ((*(int *)(param_1 + 0x2c0) == 0) && (piVar1 != (int *)0x0)) {
    iVar2 = AftImgUpdate(piVar1,(float)(g[0x7311] + *(int *)(param_1 + 0x5c)),(float)(g[0x7312] + *(int *)(param_1 + 0x60)),*(float *)(param_1 + 0x54) * *(float *)(param_1 + 0x50),GHIDRA_F2I(undefined4, *(float *)(param_1 + 0x58) * *(float *)(param_1 + 0x50)),0.0,(uint)(*(int *)(param_1 + 0x34) != 1),(uint)(*(int *)(param_1 + 0x28) == 0));
    if (iVar2 == 0) {
      piVar1[2] = 0;
      *(undefined4 *)(param_1 + 0x2d8) = 0;
    }
  }
  return;
}

/* ProjArrayAftImgDraw @ 0x08096fa0, 46 bytes */
void ProjArrayAftImgDraw(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *param_1;
  iVar2 = ArrayScanFirst(iVar1);
  while (iVar2 != 0) {
    ProjAftImgDraw(iVar2);
    iVar2 = ArrayScanNext(iVar1);
  }
  return;
}

/* ProjAftImgDraw @ 0x08096fd0, 72 bytes */
void ProjAftImgDraw(int param_1)

{
  if (*(int **)(param_1 + 0x2d8) != (int *)0x0) {
    AftImgDraw(*(int **)(param_1 + 0x2d8),-g[0x7315] - g[0x7311],-g[0x7316] - g[0x7312],
               *(int *)(param_1 + 700));
  }
  return;
}

/* GameClsnDraw @ 0x08097020, 486 bytes
 * FIXUP: 5 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
void GameClsnDraw(int param_1,float param_2,float param_3,float param_4,float param_5,uint param_6,
                 uint param_7,int param_8)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  float10 fVar5;
  int *piVar6;
  int iVar7;
  int local_24;
  int local_1c;
  
  if (((param_1 != 0) && (param_4 != 0.0)) && (param_5 != 0.0)) {
    local_1c = 0;
    iVar7 = *(int *)(param_1 + 4);
    if (0 < iVar7) {
      local_24 = 0;
      do {
        piVar6 = (int *)(local_24 + *(int *)(param_1 + 8));
        if (*piVar6 == 0) {
          fVar5 = (float10)(int)((uint)((param_7 & 1) == 0) * 2 + -1);
          uVar1 = (uint)GHIDRA_FIST32((float10)piVar6[1] * param_4 * fVar5 + param_2);
          uVar2 = (uint)GHIDRA_FIST32((float10)piVar6[2] * param_5 + param_3);
          uVar3 = (uint)GHIDRA_FIST32((float10)piVar6[3] * param_4 * fVar5 + param_2);
          uVar4 = (uint)GHIDRA_FIST32((float10)piVar6[4] * param_5 + param_3);
          W_BoxTransSub16(uVar1,uVar2,uVar3,uVar4,
                          4 << ((byte)_rgb_r_shift_16 & 0x1f) | 8 << ((byte)_rgb_g_shift_16 & 0x1f)
                          | 4 << ((byte)_rgb_b_shift_16 & 0x1f));
          if (param_8 == 0) {
            W_BoxTransAdd16(uVar1,uVar2,uVar3,uVar4,param_6);
            iVar7 = *(int *)(param_1 + 4);
          }
          else {
            W_BoxFillTransAdd16(uVar1,uVar2,uVar3,uVar4,param_6);
            iVar7 = *(int *)(param_1 + 4);
          }
        }
        local_1c = local_1c + 1;
        local_24 = local_24 + 0x14;
      } while (local_1c < iVar7);
    }
  }
  return;
}

/* TeamLifeBack @ 0x08097210, 194 bytes
 * FIXUP: 1 inexact floating constants cast to their type (apply_const_casts)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
int TeamLifeBack(int param_1)

{
  float10 fVar1;
  
  fVar1 = (100.0 - (float)g[0x7516] / (float)g[0x4e61]) * ((float)0.01f);
  if (fVar1 < 0.0) {
    fVar1 = 0.0;
  }
  return (int)GHIDRA_FIST32((float)g[param_1 * 0x6a7 + 0x3a57] +
                    ((1.0 - GHIDRA_I2F(g[param_1 * 0x6a7 + 0x3a59])) +
                    GHIDRA_I2F(g[(1 - param_1) * 0x6a7 + 0x3a5e]) * GHIDRA_I2F(g[param_1 * 0x6a7 + 0x3a59])) *
                    GHIDRA_I2F(g[param_1 * 0x6a7 + 0x3a58]) * fVar1);
}

/* WinIconCheckTeam @ 0x080972e0, 122 bytes */
void WinIconCheckTeam(int param_1,int param_2,uint param_3)

{
  if ((param_1 != param_2) && (param_1 != 0)) {
    WinIconCheck(param_2,param_3,-1);
    return;
  }
  if (param_1 == param_2) {
    WinIconCheck((param_1 == 1) + 1,0,7);
    return;
  }
  WinIconCheck((param_1 == 1) + 1,0,0);
  return;
}

/* WinIconCheck @ 0x08097360, 188 bytes */
void WinIconCheck(int param_1,uint param_2,int param_3)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  piVar2 = g;
  iVar3 = g[param_1 + 0x7506];
  if ((iVar3 < 10) && (g[0x7511] != 3)) {
    piVar1 = g + param_1 * 10 + iVar3 + 0x7523;
    if (param_3 == -1) {
      g[param_1 * 10 + iVar3 + 0x750f] = 0;
      if ((param_2 & 0x1c0) != 0) {
        piVar2[param_1 * 10 + iVar3 + 0x750f] = 5;
      }
      if ((param_2 & 0x490) == 0) {
        if ((param_2 & 0x920) != 0) {
          piVar2[param_1 * 10 + iVar3 + 0x750f] = 2;
        }
      }
      else {
        piVar2[param_1 * 10 + iVar3 + 0x750f] = 1;
      }
    }
    else {
      g[param_1 * 10 + iVar3 + 0x750f] = param_3;
    }
    iVar3 = TeamHasFullLife(param_1);
    *piVar1 = (uint)(iVar3 != 0) * 9 + -1;
  }
  return;
}

/* TeamHasFullLife @ 0x08097420, 139 bytes */
undefined4 TeamHasFullLife(int param_1)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  iVar3 = g[0x7459];
  if (iVar3 <= g[0x745a]) {
    piVar5 = g + iVar3 + 0x73d9;
    iVar4 = iVar3 * 4 + 0x1cf60;
    do {
      iVar1 = *(int *)(iVar4 + 4 + (int)g);
      if (((iVar1 == 0) || (*(int *)(iVar1 + 0x158) == 0)) ||
         (bVar2 = true, *(int *)(iVar1 + 0x1c) != 0)) {
        bVar2 = false;
      }
      if (((bVar2) && (iVar1 = *piVar5, *(int *)(iVar1 + 0xc) == param_1)) &&
         (*(int *)(iVar1 + 0x160) != *(int *)(iVar1 + 0x164))) {
        return 0;
      }
      iVar3 = iVar3 + 1;
      piVar5 = piVar5 + 1;
      iVar4 = iVar4 + 4;
    } while (iVar3 <= g[0x745a]);
  }
  return 1;
}

/* ShowDebugInfo @ 0x080974b0, 1160 bytes
 * FIXUP: 2 exact-text site patches
 * FIXUP: frame emulation: 2 stack locals placed at their original offsets in a 0x160-byte frame (a local's address escapes, see apply_frame_emulation) */
void ShowDebugInfo(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  bool bVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 extraout_EDX;
  uint uVar11;
  uint uVar12;
  longdouble lVar13;
  int *piVar14;
  undefined8 uVar15;
  unsigned char ghidra_frame[0x160] __attribute__((aligned(16)));
#define local_15c (*(char (*)[64])(ghidra_frame + 0x4))
#define local_11c (*(char (*)[268])(ghidra_frame + 0x44))
  
  iVar5 = V_Height;
  iVar1 = g[param_1 + 0x73d9];
  uVar12 = 0x1f << ((byte)_rgb_r_shift_16 & 0x1f) | 0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
           0x1f << ((byte)_rgb_b_shift_16 & 0x1f);
  if (param_1 != 0) {
    lVar13 = TimerGetFPS();
    if (lVar13 < (longdouble)0) {
      lVar13 = (longdouble)0;
    }
    sprintf(local_11c,"Frames: %i (%.1f FPS)",g[0x7304],(double)lVar13);
    V_FontDraw(local_11c,(int *)g[0x413a],10,iVar5 + -0x27,uVar12);
    sprintf(local_11c,"VRet: %i, Speed: %i, Skip: %c",g[0x4143],g[0x82d2],(g[0x7305] == -1) ? 0x61 : g[0x7305] + 0x30);
    V_FontDraw(local_11c,(int *)g[0x413a],0x6e,iVar5 + -0x27,uVar12);
    if ((iVar1 == 0) || (bVar4 = true, *(int *)(iVar1 + 0x158) == 0)) {
      bVar4 = false;
    }
    if (bVar4) {
      if (*(int *)(iVar1 + 4) == param_1 + -1) {
        sprintf(local_11c,"%s %i",iVar1 + 0x20,param_1 + -1);
      }
      else {
        sprintf(local_11c,"%s %i (%i)",iVar1 + 0x20,*(undefined4 *)(iVar1 + 4),param_1 + -1);
      }
      if ((*(int *)(iVar1 + 0xbec) != 0) && (iVar2 = *(int *)(iVar1 + 0xbf0), iVar2 != -1)) {
        sprintf(local_15c," (in %s %i\'s state rc)",g[iVar2 + 0x73d9] + 0x20,
                *(undefined4 *)(g[iVar2 + 0x73d9] + 4));
        strcat(local_11c,local_15c);
      }
      V_FontDraw(local_11c,(int *)g[0x413a],10,iVar5 + -0x1f,
                 0x19 << ((byte)_rgb_r_shift_16 & 0x1f) | 0x32 << ((byte)_rgb_g_shift_16 & 0x1f) |
                 0x1b << ((byte)_rgb_b_shift_16 & 0x1f));
      uVar6 = AnimGetLooptime(*(undefined4 **)(iVar1 + 0x13bc));
      puVar3 = *(undefined4 **)(iVar1 + 0x13bc);
      uVar15 = CONCAT44(uVar6,puVar3[7]);
      uVar9 = 0xffffffff;
      uVar6 = *(undefined4 *)
               (*(int *)(*(int *)*puVar3 + 4) * puVar3[3] + *(int *)(*(int *)*puVar3 + 0x14) + 4);
      iVar7 = *(int *)(*(int *)(iVar1 + 0x13bc) + 0x14) + 1;
      iVar2 = *(int *)(*(int *)(iVar1 + 0x13bc) + 0x10);
      if (iVar2 != 0) {
        uVar9 = *(undefined4 *)(iVar2 + 0xc);
      }
      iVar2 = *(int *)(*(int *)(iVar1 + 0x13bc) + 0x10);
      uVar10 = 0xffffffff;
      if (iVar2 != 0) {
        uVar10 = *(undefined4 *)(iVar2 + 8);
      }
      uVar8 = AnimCurIDno(*(undefined4 **)(iVar1 + 0x13bc));
      sprintf(local_11c,"ActionID: %i; Spr: %i,%i; Elemno: %i/%i; Time: %i/%i",uVar8,uVar10,uVar9,
              iVar7,uVar6,uVar15);
      if (*(int *)(iVar1 + 0x3458) != 0) {
        strcat(local_11c," (invalid)");
      }
      if (*(int *)(iVar1 + 0x13c0) == 0) {
        piVar14 = (int *)g[0x413a];
        uVar11 = uVar12;
      }
      else {
        uVar11 = 0x1f << ((byte)_rgb_r_shift_16 & 0x1f) | 0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
                 0xf << ((byte)_rgb_b_shift_16 & 0x1f);
        piVar14 = (int *)g[0x413a];
      }
      V_FontDraw(local_11c,piVar14,10,iVar5 + -0x18,uVar11);
      sprintf(local_11c,"State no: %i; Ctrl: %i; Type: %i; Movetype %i; Time: %i",
              *(undefined4 *)(iVar1 + 0xbf4),*(undefined4 *)(iVar1 + 0xe0c),
              *(undefined4 *)(iVar1 + 0xe00),*(undefined4 *)(iVar1 + 0xe04),
              *(int *)(iVar1 + 0xdfc) + -1,extraout_EDX);
      if ((*(int *)(iVar1 + 0xe3c) == 0) && (199 < *(int *)(iVar1 + 0xbf4))) {
        strcat(local_11c," (invalid)");
      }
      if (*(int *)(iVar1 + 0xbec) == 0) {
        piVar14 = (int *)g[0x413a];
        uVar11 = uVar12;
      }
      else {
        uVar11 = 0x1f << ((byte)_rgb_r_shift_16 & 0x1f) | 0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
                 0xf << ((byte)_rgb_b_shift_16 & 0x1f);
        piVar14 = (int *)g[0x413a];
      }
      V_FontDraw(local_11c,piVar14,10,iVar5 + -0x11,uVar11);
      EB_GUIUpdate();
      FontDrawClipboard(*(int **)(iVar1 + 0x345c),(int *)g[0x413a],10,V_Height + -10,uVar12);
    }
    else {
      sprintf(local_11c,"Player %i Disabled",param_1 + -1,local_11c);
      V_FontDraw(local_11c,(int *)g[0x413a],10,iVar5 + -0x1f,
                 0x19 << ((byte)_rgb_r_shift_16 & 0x1f) | 0x32 << ((byte)_rgb_g_shift_16 & 0x1f) |
                 0x1b << ((byte)_rgb_b_shift_16 & 0x1f));
    }
  }
  return;
}
#undef local_15c
#undef local_11c

/* ContinueScreenLoop @ 0x08097940, 1934 bytes
 * REVIEW: pid-in_stack_
 * FIXUP: rewrote 3 Ghidra partial-variable accesses (x._O_S_)
 * FIXUP: 3 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: PalGrpMakeFlag result written into the argument area: given explicit temporaries pgf_ffffff74
 * FIXUP: frame emulation: 8 stack locals placed at their original offsets in a 0x40-byte frame (a local's address escapes, see apply_frame_emulation) */
byte ContinueScreenLoop(void)

{
  PalGrpFlag pgf_ffffff74;
  byte bVar1;
  PalGrpFlag f;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  int *player;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  byte bVar6;
  byte bVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  undefined1 in_stack_ffffff74 [12];
  uint in_stack_ffffff80;
  undefined *in_stack_ffffff84;
  int iVar12;
  int *plist;
  unsigned char ghidra_frame[0x40] __attribute__((aligned(16)));
#define local_40 (*(int *)(ghidra_frame + 0x0))
#define local_38 (*(int *)(ghidra_frame + 0x8))
#define local_2c (*(uint *)(ghidra_frame + 0x14))
#define local_28 (*(int *)(ghidra_frame + 0x18))
#define local_24 (*(int *)(ghidra_frame + 0x1c))
#define local_20 (*(undefined4 *)(ghidra_frame + 0x20))
#define local_1c (*(int **)(ghidra_frame + 0x24))
#define local_18 (*(int **)(ghidra_frame + 0x28))
  
  local_1c = g + 0x733b;
  local_18 = g + 0x7348;
  bVar2 = false;
  bVar3 = true;
  local_38 = 0;
  bVar4 = false;
  local_40 = 0;
  V_SetBuf((int *)g[0x4136],0);
  TimerSetSyncFPS(0x3c);
  KBBufferClear();
  PadPoll();
  PadBufClear();
  UInpRefreshFlags();
  UInpBufClear();
  GameRoundReset();
  BGArrayUpdate(g[0x6ed4]);
  FrameSkipReset();
  if (g[0x33b3] == 2) {
    plist = (int *)g[0x73db];
    player = (int *)g[0x73dd];
  }
  else {
    plist = (int *)g[0x73da];
    player = (int *)g[0x73dc];
  }
  PlayerReset(plist);
  PlayerChangeState((int)plist,0x157c);
  plist[0x67] = GHIDRA_F2I(int, (float)(V_Width / 2 + g[0x7311]));
  if (player != (int *)0x0) {
    PlayerReset(player);
    PlayerChangeState((int)player,0x157c);
    iVar9 = g[0x7311];
    iVar8 = V_Width / 2;
    iVar12 = plist[100];
    player[100] = -iVar12;
    player[0x67] = GHIDRA_F2I(int, (float)(iVar8 + iVar9 + iVar12 * 0x28));
    plist[0x67] = GHIDRA_F2I(int, (GHIDRA_I2F(plist[0x67]) - (float)(plist[100] * 0x28)));
  }
  do {
    local_24 = 0;
    local_20 = 0;
    iVar9 = 0;
    PadPoll();
    KBPoll();
    bVar5 = KBkbhit();
    if (GHIDRA_ZEXT8(bVar5) != 0) {
      local_24 = KBgetchraw();
    }
    bVar5 = PadHit();
    if (GHIDRA_ZEXT8(bVar5) != 0) {
      local_20 = PadGet();
    }
    GlobalInputUpdate();
    bVar5 = UInpHit();
    if (GHIDRA_ZEXT8(bVar5) != 0) {
      iVar9 = UInpGet();
    }
    KBIMenuGetKey(&local_2c,iVar9,(int)&local_1c,2);
    iVar9 = local_28;
    uVar10 = local_2c;
    PRSprArrayClear((int *)g[0x413d]);
    if ((iVar9 + 1 == g[0x33b3]) || (g[0x33af] == g[0x33b0])) {
      if ((uVar10 & 8) != 0) {
        bVar3 = true;
      }
      bVar3 = (bool)(bVar3 & (uVar10 & 2) == 0);
      if ((uVar10 & 0xff0) != 0) {
        bVar2 = true;
      }
    }
    if (local_24 == 1) {
      bVar3 = false;
      bVar2 = true;
    }
    if (bVar2) {
      if (local_40 < 8) {
        iVar9 = local_40 * -0x20 + 0x100;
        MasterPalMul(iVar9,iVar9,iVar9);
      }
      if (local_40 == 8) {
        MasterPalMul(0,0,0);
      }
      local_40 = local_40 + 1;
      if (local_40 == 8) {
        bVar4 = true;
      }
    }
    BGMPoll(g + 0x6efa);
    if (g[0x7309] == 0) {
      PalGrpResetPalette();
    }
    PlayerUpdate(plist);
    if (player != (int *)0x0) {
      PlayerUpdate(player);
    }
    AnimUpdate((undefined4 *)plist[0x4ef]);
    if (player != (int *)0x0) {
      AnimUpdate((undefined4 *)player[0x4ef]);
    }
    AnimPerArrayUpdate((int *)g[0x413c]);
    if (0 < local_38) {
      iVar8 = 0x80;
      iVar12 = 0x80;
      iVar9 = 0x80;
      PalGrpMakeFlag(&pgf_ffffff74,0xffffffff,0);
      f.w[3] = pgf_ffffff74.w[3];
      f.w[0] = pgf_ffffff74.w[0];
      f.w[1] = pgf_ffffff74.w[1];
      f.w[2] = pgf_ffffff74.w[2];
      f.w[4] = (uint)pgf_ffffff74.w[4];
      PalGrpSetMul(f,iVar9,iVar12,iVar8);
    }
    if (local_38 < 8) {
      iVar9 = local_38 << 5;
      MasterPalMul(iVar9,iVar9,iVar9);
    }
    if (local_38 == 8) {
      MasterPalMul(0x100,0x100,0x100);
    }
    if (g[0x7307] == 0) {
      MasterPalProcessChanges();
      GameBGDraw();
      PlayerDrawShadow((int)plist,g + 0x10a4,g + 0x10a9);
      if (player != (int *)0x0) {
        PlayerDrawShadow((int)player,g + 0x10a4,g + 0x10a9);
      }
      AnimPerArrayDrawGrp((int *)g[0x413c],2,-g[0x7311],-g[0x7312]);
      PlayerDrawAnim((int)plist,1.0);
      if (player != (int *)0x0) {
        PlayerDrawAnim((int)player,1.0);
      }
      PRSprArrayDraw((int *)g[0x413d]);
      GameFGDraw();
      AnimPerArrayDrawGrp((int *)g[0x413c],1,-g[0x7311],-g[0x7312]);
      bVar7 = (byte)_rgb_b_shift_16;
      bVar1 = (byte)_rgb_r_shift_16;
      bVar6 = (byte)_rgb_g_shift_16;
      if (bVar3) {
        uVar11 = 0x1f << (bVar1 & 0x1f) | 0x3f << (bVar6 & 0x1f) | 0x1f << (bVar7 & 0x1f);
        uVar10 = 0x10 << (bVar1 & 0x1f) | 0x20 << (bVar6 & 0x1f);
        iVar9 = 0x10;
      }
      else {
        uVar11 = 0x10 << (bVar1 & 0x1f) | 0x20 << (bVar6 & 0x1f) | 0x10 << (bVar7 & 0x1f);
        uVar10 = 0x1f << (bVar1 & 0x1f) | 0x3f << (bVar6 & 0x1f);
        iVar9 = 0x1f;
      }
      V_FontDrawCenter("Continue?",(int *)g[0x413b],0xa0,0x29,0);
      V_FontDrawCenter("Continue?",(int *)g[0x413b],0x9f,0x28,
                       0x1f << ((byte)_rgb_r_shift_16 & 0x1f) |
                       0x3f << ((byte)_rgb_g_shift_16 & 0x1f) |
                       0x1f << ((byte)_rgb_b_shift_16 & 0x1f));
      V_FontDrawRight("Yes",(int *)g[0x413b],0x96,0x3d,0);
      V_FontDrawRight("Yes",(int *)g[0x413b],0x95,0x3c,uVar11);
      V_FontDraw("No",(int *)g[0x413b],0xaa,0x3d,0);
      in_stack_ffffff84 = &DAT_08278732;
      in_stack_ffffff80 = 0x8098037;
      V_FontDraw("No",(int *)g[0x413b],0xa9,0x3c,uVar10 | iVar9 << (bVar7 & 0x1f));
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
    local_38 = local_38 + 1;
  } while (!bVar4);
  FrameSkipReset();
  GameResetPersistVars();
  if (bVar3) {
    g[0x4134] = 1;
  }
  return bVar3;
}
#undef local_40
#undef local_38
#undef local_2c
#undef local_28
#undef local_24
#undef local_20
#undef local_1c
#undef local_18

