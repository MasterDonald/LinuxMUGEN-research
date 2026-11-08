/*
 * charsel.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08085c30-0x0808ca3a, 44 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"

extern int dataSetup __asm__("D_08287a30"); /* file-static 0x08287a30 */
extern int *cellHead __asm__("D_082a6be0"); /* file-static 0x082a6be0 */
extern int slct __asm__("D_082a6be4"); /* file-static 0x082a6be4 */
extern int cellRows __asm__("D_082a6be8"); /* file-static 0x082a6be8 */
extern int cellCols __asm__("D_082a6bec"); /* file-static 0x082a6bec */

/* InitSelectScreenMatrix @ 0x08085c30, 151 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x1010-byte frame (a local's address escapes, see apply_frame_emulation) */
bool InitSelectScreenMatrix(char *param_1)

{
  int iVar1;
  bool bVar2;
  unsigned char ghidra_frame[0x1010] __attribute__((aligned(16)));
#define local_100c (*(char (*)[4100])(ghidra_frame + 0x4))
  
  slct = (int)(g + 0x14e0);
  cellHead = (int *)g[0x1b50];
  cellRows = g[0x18e4];
  cellCols = g[0x18e5];
  iVar1 = FindFileDir(param_1,local_100c,(char *)0x0);
  if (iVar1 == 0) {
    sprintf((char *)(g + 0x81d2),"Couldn\'t find file for selection screen: %s\n",param_1,0);
    bVar2 = false;
  }
  else {
    dataSetup = (int)TPReadFile(local_100c);
    bVar2 = (void *)dataSetup != (void *)0x0;
  }
  return bVar2;
}
#undef local_100c

/* FreeSelectScreenMatrix @ 0x08085cd0, 34 bytes */
void FreeSelectScreenMatrix(void)

{
  if ((void *)g[0x33ac] != (void *)0x0) {
    free((void *)g[0x33ac]);
  }
  return;
}

/* CharInfoInit @ 0x08085d00, 176 bytes */
bool CharInfoInit(void)

{
  void *pvVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = g;
  g[0x14b7] = 0x20;
  slct = (int)(piVar3 + 0x14e0);
  pvVar1 = calloc(piVar3[0x14b7],0x702c);
  piVar3 = g;
  g[0x14b4] = (int)pvVar1;
  if (pvVar1 != (void *)0x0) {
    pvVar1 = calloc(piVar3[0x14b7] + 0x1e,4);
    piVar3 = g;
    g[0x14b8] = (int)pvVar1;
    if (pvVar1 != (void *)0x0) {
      iVar2 = PrecacheInit(piVar3[0x757a]);
      return iVar2 != 0;
    }
  }
  memcpy(piVar3 + 0x81d2,"Out of memory",0xe);
  return false;
}

/* CharInfoFree @ 0x08085db0, 61 bytes */
void CharInfoFree(void)

{
  if ((void *)g[0x14b4] != (void *)0x0) {
    free((void *)g[0x14b4]);
  }
  if ((void *)g[0x14b8] != (void *)0x0) {
    free((void *)g[0x14b8]);
  }
  return;
}

/* FindCharacters @ 0x08085df0, 4958 bytes
 * REVIEW: type-prop
 * FIXUP: frame emulation: 19 stack locals placed at their original offsets in a 0x4670-byte frame (a local's address escapes, see apply_frame_emulation) */
/* WARNING: Type propagation algorithm not settling */

undefined4 FindCharacters(void)

{
  int *piVar1;
  int *piVar2;
  char *pcVar3;
  uint uVar4;
  int *piVar5;
  FILE *stream;
  void *pvVar6;
  int *piVar7;
  int iVar8;
  undefined4 *puVar9;
  int iVar10;
  char *pcVar11;
  undefined4 extraout_ECX;
  uint *puVar12;
  uint *puVar13;
  int *extraout_ECX_00;
  int *piVar14;
  char cVar15;
  undefined4 extraout_EDX;
  uint uVar16;
  int iVar17;
  uint *__dest;
  int iVar18;
  bool bVar19;
  unsigned char ghidra_frame[0x4670] __attribute__((aligned(16)));
#define local_466c (*(uint **)(ghidra_frame + 0x4))
#define local_4668 (*(int *)(ghidra_frame + 0x8))
#define local_4664 (*(int *)(ghidra_frame + 0xc))
#define local_4660 (*(int *)(ghidra_frame + 0x10))
#define local_465c (*(int *)(ghidra_frame + 0x14))
#define local_4640 (*(int **)(ghidra_frame + 0x30))
#define local_4638 (*(uint *)(ghidra_frame + 0x38))
#define local_4628 (*(int *)(ghidra_frame + 0x48))
#define local_4624 (*(int *)(ghidra_frame + 0x4c))
#define local_4620 (*(int *)(ghidra_frame + 0x50))
#define local_461c (*(int (*)[254])(ghidra_frame + 0x54))
#define acStack_4222 (*(char (*)[6])(ghidra_frame + 0x44e))
#define local_421c (*(uint (*)[1023])(ghidra_frame + 0x454))
#define acStack_3220 (*(char (*)[4])(ghidra_frame + 0x1450))
#define local_321c (*(uint (*)[1024])(ghidra_frame + 0x1454))
#define local_221c (*(char (*)[4096])(ghidra_frame + 0x2454))
#define local_121c (*(byte (*)[256])(ghidra_frame + 0x3454))
#define local_111c (*(char (*)[4096])(ghidra_frame + 0x3554))
#define local_11c (*(char (*)[268])(ghidra_frame + 0x4554))
  
  piVar7 = g;
  piVar2 = g + 0x14b4;
  iVar10 = cellRows * cellCols;
  local_4628 = 0;
  local_4620 = 0;
  local_4624 = 0;
  piVar5 = cellHead;
  if (0 < iVar10) {
    do {
      *piVar5 = -1;
      iVar10 = iVar10 + -1;
      piVar5 = piVar5 + 0x80e;
    } while (iVar10 != 0);
  }
  iVar10 = TPGroupSeek(dataSetup,"Options");
  if (iVar10 == -1) {
    sprintf((char *)(g + 0x81d2),"Could not locate Options group.");
  }
  else {
    pcVar3 = TPGetValue(dataSetup,"arcade.maxmatches");
    if (pcVar3 != (char *)0x0) {
      iVar17 = 0;
      iVar10 = 0;
      if (*pcVar3 != '\0') {
        local_466c = (uint *)(piVar7 + 0x14bc);
        do {
          uVar4 = __strtol_internal((byte *)(pcVar3 + iVar10),(undefined4 *)0x0,10,0);
          *local_466c = uVar4;
          do {
            iVar18 = iVar10;
            iVar10 = iVar18 + 1;
            cVar15 = pcVar3[iVar10];
            if (cVar15 == '\0') break;
          } while (cVar15 != ',');
          if (cVar15 != '\0') {
            iVar10 = iVar18 + 2;
          }
          if ((*(byte *)(__ctype_b + 1 + pcVar3[iVar10] * 2) & 0x20) != 0) {
            cVar15 = pcVar3[iVar10];
            while ((cVar15 != '\0' &&
                   (iVar10 = iVar10 + 1, (*(byte *)(__ctype_b + 1 + pcVar3[iVar10] * 2) & 0x20) != 0
                   ))) {
              cVar15 = pcVar3[iVar10];
            }
          }
          iVar17 = iVar17 + 1;
          local_466c = local_466c + 1;
        } while ((iVar17 < 10) && (pcVar3[iVar10] != '\0'));
      }
    }
    pcVar3 = TPGetValue(dataSetup,"team.maxmatches");
    if (pcVar3 != (char *)0x0) {
      iVar17 = 0;
      iVar10 = 0;
      if (*pcVar3 != '\0') {
        local_4668 = 0x40;
        do {
          uVar4 = __strtol_internal((byte *)(pcVar3 + iVar10),(undefined4 *)0x0,10,0);
          *(uint *)(local_4668 + 8 + (int)piVar2) = uVar4;
          do {
            iVar18 = iVar10;
            iVar10 = iVar18 + 1;
            cVar15 = pcVar3[iVar10];
            if (cVar15 == '\0') break;
          } while (cVar15 != ',');
          if (cVar15 != '\0') {
            iVar10 = iVar18 + 2;
          }
          if ((*(byte *)(__ctype_b + 1 + pcVar3[iVar10] * 2) & 0x20) != 0) {
            cVar15 = pcVar3[iVar10];
            while ((cVar15 != '\0' &&
                   (iVar10 = iVar10 + 1, (*(byte *)(__ctype_b + 1 + pcVar3[iVar10] * 2) & 0x20) != 0
                   ))) {
              cVar15 = pcVar3[iVar10];
            }
          }
          iVar17 = iVar17 + 1;
          local_4668 = local_4668 + 4;
        } while ((iVar17 < 10) && (pcVar3[iVar10] != '\0'));
      }
    }
    iVar10 = TPGroupSeek(dataSetup,"Characters");
    if (iVar10 == -1) {
      sprintf((char *)(g + 0x81d2),"Could not locate Characters group.",extraout_EDX,extraout_EDX);
    }
    else {
      __dest = local_421c;
      while (pcVar3 = (char *)TPAccessNextLine(dataSetup), piVar5 = g, pcVar3 != (char *)0x0) {
        bVar19 = false;
        if (g[0x14b7] <= g[0x14b5]) {
          iVar10 = g[0x14b7] + 8;
          g[0x14b7] = iVar10;
          pvVar6 = realloc((void *)piVar5[0x14b4],iVar10 * 0x702c);
          if (pvVar6 == (void *)0x0) {
            return 0;
          }
          memset((void *)((int)pvVar6 + g[0x14b7] * 0x702c + -0x38160),0,0x38160);
          piVar5 = g;
          g[0x14b4] = (int)pvVar6;
          pvVar6 = realloc((void *)piVar5[0x14b8],piVar5[0x14b7] * 4 + 0x78);
          if (pvVar6 == (void *)0x0) {
            return 0;
          }
          puVar9 = (undefined4 *)((int)pvVar6 + g[0x14b7] * 4 + -0x20);
          for (iVar10 = 8; piVar5 = g, iVar10 != 0; iVar10 = iVar10 + -1) {
            *puVar9 = 0;
            puVar9 = puVar9 + 1;
          }
          g[0x14b8] = (int)pvVar6;
        }
        iVar17 = 0;
        piVar1 = cellHead + (local_4624 * cellCols + local_4620) * 0x80e;
        iVar10 = piVar5[0x14b4] + piVar5[0x14b5] * 0x702c;
        cVar15 = *pcVar3;
        while ((cVar15 != ',' && (cVar15 != '\0'))) {
          local_11c[iVar17] = cVar15;
          iVar17 = iVar17 + 1;
          cVar15 = pcVar3[iVar17];
        }
        local_11c[iVar17] = '\0';
        if (pcVar3[iVar17] != '\0') {
          iVar17 = iVar17 + 1;
        }
        iVar18 = (int)pcVar3[iVar17];
        if ((*(byte *)(__ctype_b + 1 + iVar18 * 2) & 0x20) != 0) {
          cVar15 = pcVar3[iVar17];
          while (cVar15 != '\0') {
            iVar17 = iVar17 + 1;
            iVar18 = (int)pcVar3[iVar17];
            if ((*(byte *)(__ctype_b + 1 + iVar18 * 2) & 0x20) == 0) break;
            cVar15 = pcVar3[iVar17];
          }
        }
        iVar8 = 0;
        if ((((*(byte *)(__ctype_b + 1 + iVar18 * 2) & 0x20) == 0) &&
            (cVar15 = pcVar3[iVar17], cVar15 != ',')) && (cVar15 != '\0')) {
          pcVar11 = (char *)(iVar10 + 0x3009);
          iVar18 = __ctype_b;
          do {
            if (iVar8 < 0xffe) {
              *pcVar11 = cVar15;
              pcVar11 = pcVar11 + 1;
              iVar8 = iVar8 + 1;
              iVar18 = __ctype_b;
            }
            iVar17 = iVar17 + 1;
          } while ((((*(byte *)(iVar18 + 1 + pcVar3[iVar17] * 2) & 0x20) == 0) &&
                   (cVar15 = pcVar3[iVar17], cVar15 != ',')) && (cVar15 != '\0'));
        }
        *(undefined1 *)(iVar8 + 0x3009 + iVar10) = 0;
        if ((0 < iVar8) &&
           (iVar18 = _alemu_stricmp((char *)(iVar10 + 0x3009),"random"), iVar18 != 0)) {
          *(undefined4 *)(iVar10 + 0x5008) = 3;
        }
        if ((*(byte *)(__ctype_b + 1 + pcVar3[iVar17] * 2) & 0x20) == 0) goto LAB_08086515;
        cVar15 = '\0';
        if (pcVar3[iVar17] != '\0') {
          do {
            iVar17 = iVar17 + 1;
            if ((*(byte *)(__ctype_b + 1 + pcVar3[iVar17] * 2) & 0x20) == 0) goto LAB_08086515;
          } while (pcVar3[iVar17] != '\0');
          cVar15 = '\0';
        }
        while (cVar15 == ',') {
          iVar17 = iVar17 + 1;
          iVar18 = (int)pcVar3[iVar17];
          if ((*(byte *)(__ctype_b + 1 + iVar18 * 2) & 0x20) == 0) {
LAB_080862b0:
            cVar15 = pcVar3[iVar17];
          }
          else {
            cVar15 = '\0';
            if (pcVar3[iVar17] != '\0') {
              do {
                iVar17 = iVar17 + 1;
                iVar18 = (int)pcVar3[iVar17];
                if ((*(byte *)(__ctype_b + 1 + iVar18 * 2) & 0x20) == 0) goto LAB_080862b0;
              } while (pcVar3[iVar17] != '\0');
              cVar15 = '\0';
            }
          }
          iVar8 = 0;
          if ((cVar15 != '=') && ((*(byte *)(__ctype_b + 1 + iVar18 * 2) & 0x20) == 0)) {
            while (cVar15 != '\0') {
              iVar17 = iVar17 + 1;
              local_121c[iVar8] = (byte)*(undefined4 *)(__ctype_tolower + iVar18 * 4);
              iVar8 = iVar8 + 1;
              cVar15 = pcVar3[iVar17];
              if ((cVar15 == '=') ||
                 (iVar18 = (int)cVar15, (*(byte *)(__ctype_b + 1 + iVar18 * 2) & 0x20) != 0)) break;
            }
          }
          local_121c[iVar8] = 0;
          iVar18 = _alemu_stricmp((char *)local_121c,"includestage");
          local_4638 = 0;
          if (iVar18 != 0) {
            iVar18 = _alemu_stricmp((char *)local_121c,"music");
            local_4638 = 1;
            if (iVar18 != 0) {
              iVar18 = _alemu_stricmp((char *)local_121c,"order");
              local_4638 = 2;
              if (iVar18 != 0) {
                sprintf((char *)(g + 0x81d2),"\n[Characters]: On line: %s\n-- Unknown flag: %s",
                        pcVar3,local_121c);
                return 0;
              }
            }
          }
          if ((*(byte *)(__ctype_b + 1 + pcVar3[iVar17] * 2) & 0x20) == 0) {
LAB_080863b5:
            cVar15 = pcVar3[iVar17];
          }
          else {
            cVar15 = '\0';
            if (pcVar3[iVar17] != '\0') {
              do {
                iVar17 = iVar17 + 1;
                if ((*(byte *)(__ctype_b + 1 + pcVar3[iVar17] * 2) & 0x20) == 0) goto LAB_080863b5;
              } while (pcVar3[iVar17] != '\0');
              cVar15 = '\0';
            }
          }
          if (cVar15 != '=') {
            sprintf((char *)(g + 0x81d2),"\n[Characters]: On line: %s\n-- Param %s missing \'=\'",
                    pcVar3,local_121c);
            return 0;
          }
          iVar17 = iVar17 + 1;
          iVar18 = (int)pcVar3[iVar17];
          if ((*(byte *)(__ctype_b + 1 + iVar18 * 2) & 0x20) == 0) {
LAB_080863f0:
            cVar15 = pcVar3[iVar17];
          }
          else {
            cVar15 = '\0';
            if (pcVar3[iVar17] != '\0') {
              do {
                iVar17 = iVar17 + 1;
                iVar18 = (int)pcVar3[iVar17];
                if ((*(byte *)(__ctype_b + 1 + iVar18 * 2) & 0x20) == 0) goto LAB_080863f0;
              } while (pcVar3[iVar17] != '\0');
              cVar15 = '\0';
            }
          }
          iVar8 = 0;
          if ((cVar15 != ',') && ((*(byte *)(__ctype_b + 1 + iVar18 * 2) & 0x20) == 0)) {
            while (cVar15 != '\0') {
              iVar17 = iVar17 + 1;
              local_121c[iVar8] = (byte)*(undefined4 *)(__ctype_tolower + iVar18 * 4);
              iVar8 = iVar8 + 1;
              cVar15 = pcVar3[iVar17];
              if ((cVar15 == ',') ||
                 (iVar18 = (int)cVar15, (*(byte *)(__ctype_b + 1 + iVar18 * 2) & 0x20) != 0)) break;
            }
          }
          local_121c[iVar8] = 0;
          if (local_4638 == 1) {
            strncpy((char *)(iVar10 + 0x4008),(char *)local_121c,0xffe);
          }
          else if (local_4638 < 2) {
            if (local_4638 == 0) {
              uVar4 = __strtol_internal(local_121c,(undefined4 *)0x0,10,0);
              *(uint *)(iVar10 + 0x5008) = (uint)(uVar4 != 0) * 3;
            }
          }
          else if (local_4638 == 2) {
            uVar4 = __strtol_internal(local_121c,(undefined4 *)0x0,10,0);
            uVar4 = (-2 < (int)(uVar4 - 1)) - 1 | uVar4 - 1;
            *(uint *)(iVar10 + 0x5024) = uVar4;
            if (9 < (int)uVar4) {
              *(undefined4 *)(iVar10 + 0x5024) = 9;
            }
          }
          if ((*(byte *)(__ctype_b + 1 + pcVar3[iVar17] * 2) & 0x20) == 0) {
LAB_08086515:
            cVar15 = pcVar3[iVar17];
          }
          else {
            cVar15 = '\0';
            if (pcVar3[iVar17] != '\0') {
              do {
                iVar17 = iVar17 + 1;
                if ((*(byte *)(__ctype_b + 1 + pcVar3[iVar17] * 2) & 0x20) == 0) goto LAB_08086515;
              } while (pcVar3[iVar17] != '\0');
              cVar15 = '\0';
            }
          }
        }
        iVar17 = _alemu_stricmp(local_11c,"randomselect");
        if (iVar17 == 0) {
          *(undefined1 *)(piVar1 + 1) = 0;
          piVar1[0x80d] = 0;
          *piVar1 = -2;
        }
        else {
          splitdirfile(local_11c,(char *)local_321c,(char *)local_421c);
          iVar17 = CheckExtension(local_11c);
          bVar19 = iVar17 == 9;
          if ((char)local_321c[0] == '\0') {
            sprintf((char *)local_321c,"chars/%s/",local_11c,extraout_ECX);
            strcpy((char *)local_421c,local_11c);
          }
          else {
            iVar17 = isabsolutedir((char *)local_321c);
            if (iVar17 == 0) {
              strcpy(local_111c,(char *)local_321c);
              sprintf((char *)local_321c,"chars/%s",local_111c,iVar8);
            }
          }
          if (bVar19) {
            puVar12 = local_421c;
            do {
              puVar13 = puVar12;
              puVar12 = puVar13 + 1;
              uVar4 = *puVar13 + 0xfefefeff & (*puVar13 ^ 0xffffffff);
              uVar16 = uVar4 & 0x80808080;
            } while (uVar16 == 0);
            if ((uVar4 & 0x8080) == 0) {
              uVar16 = uVar16 >> 0x10;
              puVar12 = (uint *)((int)puVar13 + 6);
            }
            *(char *)((int)__dest +
                     (int)puVar12 +
                     ((-6 - (uint)CARRY1((byte)uVar16,(byte)uVar16)) - (int)local_421c)) = 'd';
            puVar12 = __dest;
            do {
              puVar13 = puVar12;
              puVar12 = puVar13 + 1;
              uVar4 = *puVar13 + 0xfefefeff & (*puVar13 ^ 0xffffffff);
              uVar16 = uVar4 & 0x80808080;
            } while (uVar16 == 0);
            if ((uVar4 & 0x8080) == 0) {
              uVar16 = uVar16 >> 0x10;
              puVar12 = (uint *)((int)puVar13 + 6);
            }
            *(char *)((int)puVar12 + (-5 - (uint)CARRY1((byte)uVar16,(byte)uVar16))) = 'e';
            puVar12 = __dest;
            do {
              puVar13 = puVar12;
              puVar12 = puVar13 + 1;
              uVar4 = *puVar13 + 0xfefefeff & (*puVar13 ^ 0xffffffff);
              uVar16 = uVar4 & 0x80808080;
            } while (uVar16 == 0);
            if ((uVar4 & 0x8080) == 0) {
              uVar16 = uVar16 >> 0x10;
              puVar12 = (uint *)((int)puVar13 + 6);
            }
            *(char *)((int)puVar12 + (-4 - (uint)CARRY1((byte)uVar16,(byte)uVar16))) = 'f';
          }
          else {
            puVar12 = local_421c;
            do {
              puVar13 = puVar12;
              puVar12 = puVar13 + 1;
              uVar4 = *puVar13 + 0xfefefeff & (*puVar13 ^ 0xffffffff);
              uVar16 = uVar4 & 0x80808080;
            } while (uVar16 == 0);
            if ((uVar4 & 0x8080) == 0) {
              uVar16 = uVar16 >> 0x10;
              puVar12 = (uint *)((int)puVar13 + 6);
            }
            if (4 < (int)puVar12 +
                    ((-3 - (uint)CARRY1((byte)uVar16,(byte)uVar16)) - (int)local_421c)) {
              puVar12 = local_421c;
              do {
                puVar13 = puVar12;
                puVar12 = puVar13 + 1;
                uVar4 = *puVar13 + 0xfefefeff & (*puVar13 ^ 0xffffffff);
                uVar16 = uVar4 & 0x80808080;
              } while (uVar16 == 0);
              if ((uVar4 & 0x8080) == 0) {
                uVar16 = uVar16 >> 0x10;
                puVar12 = (uint *)((int)puVar13 + 6);
              }
              iVar17 = _alemu_stricmp((char *)((int)puVar12 +
                                              (-7 - (uint)CARRY1((byte)uVar16,(byte)uVar16))),".def"
                                     );
              if (iVar17 == 0) goto LAB_0808674a;
            }
            strcat((char *)__dest,".def");
          }
LAB_0808674a:
          joindirfile(local_111c,(char *)local_321c,(char *)__dest);
          puVar12 = local_321c;
          if (bVar19) {
            do {
              puVar13 = puVar12;
              puVar12 = puVar13 + 1;
              uVar4 = *puVar13 + 0xfefefeff & (*puVar13 ^ 0xffffffff);
              uVar16 = uVar4 & 0x80808080;
            } while (uVar16 == 0);
            if ((uVar4 & 0x8080) == 0) {
              uVar16 = uVar16 >> 0x10;
              puVar12 = (uint *)((int)puVar13 + 6);
            }
            *(char *)((int)puVar12 +
                     (int)(acStack_3220 +
                          (-(int)local_321c - (uint)CARRY1((byte)uVar16,(byte)uVar16)))) = '\0';
            local_4640 = MFfopenZip((char *)local_321c,(char *)__dest);
            puVar12 = local_321c;
            do {
              puVar13 = puVar12;
              puVar12 = puVar13 + 1;
              uVar4 = *puVar13 + 0xfefefeff & (*puVar13 ^ 0xffffffff);
              uVar16 = uVar4 & 0x80808080;
            } while (uVar16 == 0);
            if ((uVar4 & 0x8080) == 0) {
              uVar16 = uVar16 >> 0x10;
              puVar12 = (uint *)((int)puVar13 + 6);
            }
            *(char *)((int)puVar12 +
                     (int)(acStack_3220 +
                          (-(int)local_321c - (uint)CARRY1((byte)uVar16,(byte)uVar16)) + 2)) = '/';
            puVar12 = local_321c;
            do {
              puVar13 = puVar12;
              puVar12 = puVar13 + 1;
              uVar4 = *puVar13 + 0xfefefeff & (*puVar13 ^ 0xffffffff);
              uVar16 = uVar4 & 0x80808080;
            } while (uVar16 == 0);
            if ((uVar4 & 0x8080) == 0) {
              uVar16 = uVar16 >> 0x10;
              puVar12 = (uint *)((int)puVar13 + 6);
            }
            *(char *)((int)puVar12 +
                     (int)(acStack_3220 +
                          (-(int)local_321c - (uint)CARRY1((byte)uVar16,(byte)uVar16)) + 1)) = '\0';
            if (local_4640 == (int *)0x0) {
              return 0;
            }
            piVar5 = TPReadMF(local_4640,0);
            MFzclose((int)local_4640);
          }
          else {
            piVar5 = TPReadFile(local_111c);
          }
          if (piVar5 == (int *)0x0) {
            *(undefined1 *)(piVar1 + 1) = 0;
            piVar1[0x80d] = 0;
            *piVar1 = -1;
          }
          else {
            pcVar11 = "Info";
            TPGroupSeek((int)piVar5,"Info");
            pcVar3 = TPGetValue((int)piVar5,"displayname");
            if (pcVar3 == (char *)0x0) {
              pcVar3 = TPGetValue((int)piVar5,"name");
              if ((pcVar3 != (char *)0x0) &&
                 (iVar17 = GetQuotedString((int)piVar5,"name",(char *)(piVar1 + 1),0x2f,(char *)0x0)
                 , iVar17 == 0)) {
                strcat((char *)(g + 0x81d2),"\nError reading ");
                __dest = local_421c;
                piVar7 = g + 0x81d2;
                goto LAB_08086d8c;
              }
            }
            else {
              iVar17 = GetQuotedString((int)piVar5,"displayname",(char *)(piVar1 + 1),0x2f,
                                       (char *)0x0);
              if (iVar17 == 0) {
                strcat((char *)(g + 0x81d2),"\nError reading ");
                piVar7 = g + 0x81d2;
                goto LAB_08086d8c;
              }
            }
            strcpy((char *)(piVar1 + 0xd),(char *)__dest);
            strcpy((char *)((int)piVar1 + 0x1033),(char *)local_321c);
            TPGroupSeek((int)piVar5,"Info");
            TPScanf((int)piVar5,"pal.defaults","%i,%i,%i,%i",iVar10 + 0x5014,iVar10 + 0x5018,
                    iVar10 + 0x501c,iVar10 + 0x5020,pcVar11);
            iVar17 = TPGroupSeek((int)piVar5,"Arcade");
            if (iVar17 != -1) {
              TPScanf((int)piVar5,"intro.storyboard","%s",iVar10 + 0x5028);
              TPScanf((int)piVar5,"ending.storyboard","%s",iVar10 + 0x6027);
            }
            TPGroupSeek((int)piVar5,"Files");
            pcVar3 = TPGetValue((int)piVar5,"sprite");
            strcpy(local_111c,pcVar3);
            joindirfile(local_221c,(char *)local_321c,local_111c);
            *piVar1 = g[0x14b5];
            piVar14 = piVar1;
            iVar17 = 0;
            do {
              iVar18 = iVar17 + 1;
              sprintf((char *)local_121c,"pal%i",iVar18,piVar14);
              pcVar3 = TPGetValue((int)piVar5,(char *)local_121c);
              piVar14 = extraout_ECX_00;
              if (pcVar3 != (char *)0x0) {
                piVar14 = (int *)(*(uint *)(iVar10 + 0x5010) | 1 << ((byte)iVar17 & 0x1f));
                *(int **)(iVar10 + 0x5010) = piVar14;
              }
              iVar17 = iVar18;
            } while (iVar18 < 0xc);
            *(undefined4 *)(iVar10 + 0x7028) = *(undefined4 *)(iVar10 + 0x5010);
            strcpy((char *)(iVar10 + 0x100b),(char *)(piVar1 + 0xd));
            strcpy((char *)(iVar10 + 0x200a),(char *)((int)piVar1 + 0x1033));
            *(int *)(iVar10 + 0x500c) = local_4624 * cellCols + local_4620;
            g[0x14b5] = g[0x14b5] + 1;
            local_461c[0] = 9000;
            piVar1[0x80d] = 0;
            local_461c[1] = 0;
            local_461c[2] = 9000;
            local_461c[3] = 1;
            local_461c[4] = 0xffffffff;
            if (bVar19) {
              MFzopen(local_4640,local_111c);
              piVar14 = SpriteReadSFFListPtr(local_4640,local_461c);
              piVar1[0x80d] = (int)piVar14;
            }
            else {
              stream = fopen(local_221c,"rb");
              if (stream != (FILE *)0x0) {
                fclose(stream);
                SpriteSetBufReadMode(0);
                iVar10 = SpriteReadSFFList(local_221c,local_461c);
                piVar1[0x80d] = iVar10;
                SpriteSetBufReadMode(g[0x757b]);
              }
            }
            TPFree(piVar5);
          }
        }
        local_4620 = local_4620 + 1;
        local_11c[0] = '\0';
        if (cellCols <= local_4620) {
          local_4624 = local_4624 + 1;
          local_4620 = 0;
        }
        if (cellRows <= local_4624) break;
        if (bVar19) {
          MFfclose(local_4640);
        }
      }
      iVar10 = TPGroupSeek(dataSetup,"extrastages");
      if (iVar10 != -1) {
        while (pcVar3 = (char *)TPAccessNextLine(dataSetup), pcVar3 != (char *)0x0) {
          if (*pcVar3 != '\0') {
            local_4628 = local_4628 + 1;
          }
        }
      }
      pvVar6 = calloc(local_4628 + piVar7[0x14b5],0x1054);
      piVar5 = g;
      g[0x33ac] = (int)pvVar6;
      if (pvVar6 != (void *)0x0) {
        iVar10 = 0;
        local_465c = piVar7[0x14b5];
        if (0 < local_465c) {
          local_4664 = 0;
          do {
            piVar5 = g;
            if (*(int *)(g[0x14b4] + 0x5008 + local_4664) != 0) {
              iVar17 = g[0x33ad];
              iVar18 = 0;
              pcVar3 = (char *)(local_4664 + *piVar2 + 0x3009);
              if (0 < iVar17) {
                local_4660 = 0;
                do {
                  iVar8 = strcmp((char *)(local_4660 + piVar5[0x33ac]),pcVar3);
                  if (iVar8 == 0) break;
                  iVar18 = iVar18 + 1;
                  local_4660 = local_4660 + 0x1054;
                } while (iVar18 < iVar17);
              }
              if (iVar17 <= iVar18) {
                iVar18 = iVar17 * 0x1054;
                strcpy((char *)(iVar18 + piVar5[0x33ac]),pcVar3);
                iVar8 = g[0x33ac];
                *(undefined4 *)(iVar8 + 0x1050 + iVar18) =
                     *(undefined4 *)(g[0x14b4] + 0x5008 + local_4664);
                puVar9 = TPReadFile((char *)(iVar8 + iVar18));
                if (puVar9 == (undefined4 *)0x0) {
                  *(undefined1 *)(*piVar2 + 0x3009 + local_4664) = 0;
                  local_465c = piVar7[0x14b5];
                }
                else {
                  iVar8 = TPGroupSeek((int)puVar9,"Info");
                  if (((iVar8 != -1) &&
                      (pcVar3 = TPGetValue((int)puVar9,"name"), pcVar3 != (char *)0x0)) &&
                     (iVar8 = GetQuotedString((int)puVar9,"name",
                                              (char *)(iVar18 + g[0x33ac] + 0xfff),0x4f,(char *)0x0)
                     , iVar8 == 0)) {
                    strcat((char *)(g + 0x81d2),"\nError getting stage name for ");
                    piVar7 = g + 0x81d2;
                    __dest = (uint *)(iVar18 + g[0x33ac]);
                    goto LAB_08086d8c;
                  }
                  TPFree(puVar9);
                  if (*(char *)(g[0x33ac] + 0xfff + iVar17 * 0x1054) == '\0') {
                    pcVar3 = (char *)(iVar17 * 0x1054 + g[0x33ac]);
                    strcpy(pcVar3 + 0xfff,pcVar3);
                  }
                  g[0x33ad] = g[0x33ad] + 1;
                  local_465c = piVar7[0x14b5];
                }
              }
            }
            iVar10 = iVar10 + 1;
            local_4664 = local_4664 + 0x702c;
          } while (iVar10 < local_465c);
        }
        if (0 < local_4628) {
          TPGroupReset(dataSetup);
          while (pcVar3 = (char *)TPAccessNextLine(dataSetup), piVar7 = g, pcVar3 != (char *)0x0) {
            iVar17 = 0;
            iVar10 = g[0x33ad];
            if (0 < iVar10) {
              iVar18 = 0;
              do {
                iVar8 = strcmp((char *)(iVar18 + piVar7[0x33ac]),pcVar3);
                if (iVar8 == 0) break;
                iVar17 = iVar17 + 1;
                iVar18 = iVar18 + 0x1054;
              } while (iVar17 < iVar10);
            }
            if (iVar10 <= iVar17) {
              iVar17 = iVar10 * 0x1054;
              strcpy((char *)(iVar17 + piVar7[0x33ac]),pcVar3);
              puVar9 = TPReadFile((char *)(iVar17 + g[0x33ac]));
              if (puVar9 != (undefined4 *)0x0) {
                iVar18 = TPGroupSeek((int)puVar9,"Info");
                if (((iVar18 != -1) &&
                    (pcVar3 = TPGetValue((int)puVar9,"name"), pcVar3 != (char *)0x0)) &&
                   (iVar18 = GetQuotedString((int)puVar9,"name",(char *)(iVar17 + g[0x33ac] + 0xfff)
                                             ,0x4f,(char *)0x0), iVar18 == 0)) {
                  strcat((char *)(g + 0x81d2),"\nError getting stage name for ");
                  piVar7 = g + 0x81d2;
                  __dest = (uint *)(iVar17 + g[0x33ac]);
LAB_08086d8c:
                  strcat((char *)piVar7,(char *)__dest);
                  return 0;
                }
                TPFree(puVar9);
                if (*(char *)(g[0x33ac] + 0xfff + iVar10 * 0x1054) == '\0') {
                  pcVar3 = (char *)(iVar10 * 0x1054 + g[0x33ac]);
                  strcpy(pcVar3 + 0xfff,pcVar3);
                }
                g[0x33ad] = g[0x33ad] + 1;
              }
            }
          }
        }
        TPFree((undefined4 *)dataSetup);
        return 1;
      }
      memcpy(piVar5 + 0x81d2,"Out of memory",0xe);
    }
  }
  return 0;
}
#undef local_466c
#undef local_4668
#undef local_4664
#undef local_4660
#undef local_465c
#undef local_4640
#undef local_4638
#undef local_4628
#undef local_4624
#undef local_4620
#undef local_461c
#undef acStack_4222
#undef local_421c
#undef acStack_3220
#undef local_321c
#undef local_221c
#undef local_121c
#undef local_111c
#undef local_11c

/* CharacterSelectScreen @ 0x08087150, 5329 bytes
 * FIXUP: 4 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 20 stack locals placed at their original offsets in a 0x3cd0-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 CharacterSelectScreen(undefined4 param_1,int param_2)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  uint uVar8;
  undefined3 extraout_var_02;
  undefined4 uVar9;
  long lVar10;
  int iVar11;
  uint uVar12;
  int *piVar13;
  uint uVar14;
  uint *puVar15;
  int *piVar16;
  int *piVar17;
  uint *puVar18;
  int iVar19;
  int iVar20;
  int *piVar21;
  char *pcVar22;
  int iVar23;
  unsigned char ghidra_frame[0x3cd0] __attribute__((aligned(16)));
#define iStack_3cc8 (*(int *)(ghidra_frame + 0x8))
#define local_3ca8 (*(int *)(ghidra_frame + 0x28))
#define local_3ca4 (*(int *)(ghidra_frame + 0x2c))
#define local_3ca0 (*(int *)(ghidra_frame + 0x30))
#define local_3c84 (*(uint *)(ghidra_frame + 0x4c))
#define local_3c80 (*(int *)(ghidra_frame + 0x50))
#define local_3c64 (*(uint **)(ghidra_frame + 0x6c))
#define local_3c5c (*(int (*)[7])(ghidra_frame + 0x74))
#define local_3c40 (*(int *)(ghidra_frame + 0x90))
#define local_3c3c (*(uint *)(ghidra_frame + 0x94))
#define local_3c38 (*(uint *)(ghidra_frame + 0x98))
#define local_3c34 (*(int (*)[11])(ghidra_frame + 0x9c))
#define aiStack_3c08 (*(int (*)[91])(ghidra_frame + 0xc8))
#define aiStack_3a9c (*(int (*)[110])(ghidra_frame + 0x234))
#define local_38e4 (*(uint (*)[3406])(ghidra_frame + 0x3ec))
#define auStack_3ac (*(uint (*)[62])(ghidra_frame + 0x3924))
#define auStack_2b4 (*(uint (*)[74])(ghidra_frame + 0x3a1c))
#define uStack_18c (*(undefined4 *)(ghidra_frame + 0x3b44))
#define aiStack_188 (*(int (*)[90])(ghidra_frame + 0x3b48))
#define iStack_20 (*(int *)(ghidra_frame + 0x3cb0))
  
  piVar16 = local_3c34 + 2;
  local_3c3c = 0;
  bVar5 = false;
  local_3c5c[2] = 0;
  local_3c5c[3] = 0;
  bVar4 = false;
  if ((g[0x82d6] != 0) || (g[0x74e8] != 0)) {
    bVar4 = true;
  }
  local_3ca4 = -1;
  iVar11 = 0;
  local_3ca0 = 0;
  local_3ca8 = -1;
  do {
    local_3c34[iVar11] = (int)(g + iVar11 * 0xd + 0x733b);
    iVar11 = iVar11 + 1;
  } while (iVar11 < 2);
  TimerSetSyncFPS(0x3c);
  KBRepeat = 0;
  KBBufferClear();
  PadPoll();
  PadBufClear();
  UInpRefreshFlags();
  UInpBufClear();
  BGArrayReset(g[0x62cf]);
  V_SetBuf((int *)g[0x4136],0);
  W_Cls(0);
  *(undefined1 *)(g + 0x805) = 0;
  puVar15 = local_38e4;
  for (iVar11 = 0xd4e; iVar11 != 0; iVar11 = iVar11 + -1) {
    *puVar15 = 0;
    puVar15 = puVar15 + 1;
  }
  piVar13 = piVar16;
  for (iVar11 = 0xf04; iVar11 != 0; iVar11 = iVar11 + -1) {
    *piVar13 = 0;
    piVar13 = piVar13 + 1;
  }
  auStack_3ac[2] = -1;
  BuildSelectList((int)piVar16,param_1,param_2);
  InitSelectDisp((int)auStack_2b4);
  CharStopUsingPalAll();
  iVar11 = BGMLoadAndStart(g + 0x6efa,(byte *)(g + 0x6ad3),g[0x6ed3],0);
  if (iVar11 == 0) {
    ErrorExit();
  }
  FrameSkipReset();
  if (local_3c3c == 1) {
LAB_0808844d:
    PalGrpClear();
    if (local_3c3c == 1) {
      if (g[0x74e8] == 0) {
        GameSndPlay((int *)g[0x5ec1],*(int *)(slct + 0x10d8),*(int *)(slct + 0x10dc),0);
      }
      PrecacheFinish();
      MasterPalReset();
      uVar9 = 0;
    }
    else {
      puVar15 = local_38e4;
      puVar18 = (uint *)(g + 0x33b8);
      for (iVar11 = 0xd4e; iVar11 != 0; iVar11 = iVar11 + -1) {
        *puVar18 = *puVar15;
        puVar15 = puVar15 + 1;
        puVar18 = puVar18 + 1;
      }
      local_3c80 = 0;
      iStack_3cc8 = 0;
      piVar16 = g + 0x33b8;
      do {
        iVar11 = 0;
        *(undefined4 *)((int)local_3c5c + iStack_3cc8) = 0;
        if (0 < piVar16[1]) {
          piVar13 = piVar16 + 5;
          do {
            if (*(int *)((int)local_3c5c + iStack_3cc8) < *piVar13) {
              *(int *)((int)local_3c5c + iStack_3cc8) = *piVar13;
            }
            iVar11 = iVar11 + 1;
            piVar13 = piVar13 + 0x17;
          } while (iVar11 < piVar16[1]);
        }
        local_3c80 = local_3c80 + 1;
        iStack_3cc8 = iStack_3cc8 + 4;
        piVar16 = piVar16 + 0x6a7;
      } while (local_3c80 < 2);
      if (g[0x7579] < local_3c5c[1] + local_3c5c[0]) {
        g[0x7579] = local_3c5c[1] + local_3c5c[0];
      }
      if (auStack_3ac[3] != 0) {
        if (auStack_3ac[2] == -1) {
          if (g[0x33ad] < 1) {
            piVar16 = g + 0x7dc4;
          }
          else {
            lVar10 = random();
            piVar16 = (int *)(g[0x33ac] + (lVar10 % g[0x33ad]) * 0x1054);
          }
          strcpy((char *)(g + 0x805),(char *)piVar16);
        }
        else {
          strcpy((char *)(g + 0x805),(char *)(g[0x33ac] + auStack_3ac[2] * 0x1054));
        }
      }
      MasterPalReset();
      uVar9 = 1;
    }
    return uVar9;
  }
LAB_08087348:
  iVar11 = 0;
  BGMPoll(g + 0x6efa);
  local_3c3c = 0;
  local_3c38 = 0;
  PadPoll();
  KBPoll();
  bVar6 = KBkbhit();
  if (GHIDRA_ZEXT8(bVar6) != 0) {
    local_3c3c = KBgetchraw();
  }
  bVar6 = PadHit();
  if (GHIDRA_ZEXT8(bVar6) != 0) {
    local_3c38 = PadGet();
  }
  GlobalInputUpdate();
  bVar6 = UInpHit();
  if (GHIDRA_ZEXT8(bVar6) != 0) {
    iVar11 = UInpGet();
  }
  KBIMenuGetKey((uint *)(local_3c5c + 6),iVar11,(int)local_3c34,2);
  local_3c5c[4] = local_3c5c[6];
  local_3c5c[5] = local_3c40;
  if ((g[0x74e8] != 0) &&
     ((((local_3c3c != 0 && ((local_3c3c & 0x100) == 0)) ||
       ((local_3c38 != 0 && ((local_3c38 & 0x100) == 0)))) || (local_3c5c[6] != 0)))) {
    local_3c3c = 1;
    local_3c38 = 0;
    local_3c5c[4] = 0;
  }
  local_3c80 = 0;
LAB_08087466:
  piVar13 = piVar16 + local_3c80 * 0x68;
  do {
    bVar6 = false;
    local_3c84 = -1;
    if (aiStack_3a9c[local_3c80 * 0x68] <= aiStack_3a9c[local_3c80 * 0x68 + 1]) {
      local_3c5c[local_3c80 + 2] = 1;
      goto switchD_080874eb_default;
    }
    piVar1 = piVar13 + aiStack_3a9c[local_3c80 * 0x68 + 1] * 10;
    iVar11 = SlctStateListChanged((int)piVar13);
    bVar7 = false;
    switch(*piVar1) {
    case 0:
    case 5:
    case 6:
      goto LAB_080881c0;
    case 1:
      piVar17 = aiStack_188 + local_3c80 * 0x2d;
      if (iVar11 != 0) {
        BuildMenuCtrl((int)piVar16,(int)piVar1,local_3c80);
      }
      if (g[0x4134] == 0) {
        if (local_3c5c[5] == local_3c80) {
          iVar11 = aiStack_188[local_3c80 * 0x2d + 3];
          iVar20 = aiStack_188[local_3c80 * 0x2d + iVar11 * 5 + 7];
          local_3c84 = CharacterSelectMenuKey
                                 (local_3c5c[4],local_3c5c[5],(int)piVar17,
                                  (uint)(aiStack_188[local_3c80 * 0x2d + 2] == 0) * 2 + -1);
          if (iVar11 == aiStack_188[local_3c80 * 0x2d + 3]) {
            if (iVar20 == aiStack_188[local_3c80 * 0x2d + iVar11 * 5 + 7]) goto LAB_08087632;
            iVar11 = *(int *)(aiStack_188[local_3c80 * 0x2d + 2] * 0x2e4 + 0x1550 + slct);
            iVar20 = *(int *)(aiStack_188[local_3c80 * 0x2d + 2] * 0x2e4 + 0x154c + slct);
            piVar21 = (int *)g[0x5ec1];
          }
          else {
            iVar11 = *(int *)(aiStack_188[local_3c80 * 0x2d + 2] * 0x2e4 + 0x1548 + slct);
            iVar20 = *(int *)(aiStack_188[local_3c80 * 0x2d + 2] * 0x2e4 + 0x1544 + slct);
            piVar21 = (int *)g[0x5ec1];
          }
          GameSndPlay(piVar21,iVar20,iVar11,0);
        }
      }
      else {
        local_3c84 = aiStack_188[local_3c80 * 0x2d + 3];
      }
LAB_08087632:
      if (bVar4) {
        iVar11 = aiStack_3a9c[local_3c80 * 0x68 + 3];
        if ((iVar11 < 0x3c) && ((iVar11 + local_3c80 * 4 & 7U) == 0)) {
          lVar10 = random();
          iVar11 = (lVar10 % (aiStack_188[local_3c80 * 0x2d + 4] + -1) +
                    aiStack_188[local_3c80 * 0x2d + 3] + 1) % aiStack_188[local_3c80 * 0x2d + 4];
          aiStack_188[local_3c80 * 0x2d + 3] = iVar11;
          piVar17[iVar11 * 5 + 7] = piVar17[iVar11 * 5 + 9];
          if (piVar17[iVar11 * 5 + 8] < piVar17[iVar11 * 5 + 9]) {
            lVar10 = random();
            piVar17[iVar11 * 5 + 7] =
                 lVar10 % ((piVar17[iVar11 * 5 + 9] - piVar17[iVar11 * 5 + 8]) + 1) +
                 piVar17[iVar11 * 5 + 8];
          }
          GameSndPlay((int *)g[0x5ec1],
                      *(int *)(aiStack_188[local_3c80 * 0x2d + 2] * 0x2e4 + 0x1544 + slct),
                      *(int *)(aiStack_188[local_3c80 * 0x2d + 2] * 0x2e4 + 0x1548 + slct),0);
          iVar11 = aiStack_3a9c[local_3c80 * 0x68 + 3];
        }
        if (299 < iVar11) {
          local_3c84 = aiStack_188[local_3c80 * 0x2d + 3];
        }
      }
      if (local_3c84 != -1) {
        if (aiStack_188[local_3c80 * 0x2d + 1] == 0) {
          if (g[0x4134] == 0) {
            GameSndPlay((int *)g[0x5ec1],
                        *(int *)(aiStack_188[local_3c80 * 0x2d + 2] * 0x2e4 + 0x1554 + slct),
                        *(int *)(aiStack_188[local_3c80 * 0x2d + 2] * 0x2e4 + 0x1558 + slct),0);
          }
          iVar11 = aiStack_188[local_3c80 * 0x2d + aiStack_188[local_3c80 * 0x2d + 3] * 5 + 5];
          if (iVar11 == 1) {
            iVar11 = piVar1[9];
            *(undefined4 *)(iVar11 + 8) = 1;
            *(undefined4 *)(iVar11 + 0x10) = 0;
            *(undefined4 *)(iVar11 + 0xc) = 2;
          }
          else if (iVar11 < 2) {
            if (iVar11 == 0) {
              iVar11 = piVar1[9];
              *(undefined4 *)(iVar11 + 8) = 0;
              *(undefined4 *)(iVar11 + 0xc) = 1;
            }
            else {
LAB_08087800:
              pcVar22 = "Programmer\'s fault";
LAB_08087808:
              ErrorExitM(pcVar22);
            }
          }
          else {
            if (iVar11 == 2) {
              pcVar22 = "Not yet implemented";
              goto LAB_08087808;
            }
            if (iVar11 != 3) goto LAB_08087800;
            iVar11 = piVar1[9];
            *(undefined4 *)(iVar11 + 8) = 3;
            *(int *)(iVar11 + 0xc) =
                 aiStack_188[local_3c80 * 0x2d + aiStack_188[local_3c80 * 0x2d + 3] * 5 + 7];
          }
          CharselSaveMenuPos((int)piVar16,
                             (undefined4 *)
                             (slct + 0x16d4 + aiStack_188[local_3c80 * 0x2d + 2] * 0x2e4),local_3c80
                            );
        }
        if (local_3c84 != -1) {
          *piVar17 = 0;
          goto LAB_080881c0;
        }
      }
      break;
    case 2:
      if (iVar11 != 0) {
        BuildSlctCtrl((int)piVar16,(int)piVar1,local_3c80);
      }
      if (piVar1[2] == 1) {
        if (piVar1[3] == 2) {
          uVar12 = auStack_3ac[local_3c80 * 0x1d + 9];
          if ((uVar12 == 1) && (piVar1[4] == 1)) {
            bVar7 = true;
          }
        }
        else {
          uVar12 = auStack_3ac[local_3c80 * 0x1d + 9];
        }
      }
      else {
        uVar12 = auStack_3ac[local_3c80 * 0x1d + 9];
      }
      if (uVar12 != 0xffffffff) {
        uVar12 = auStack_3ac[local_3c80 * 0x1d + 5];
        uVar2 = auStack_3ac[local_3c80 * 0x1d + 4];
        uVar3 = auStack_3ac[local_3c80 * 0x1d + 6];
        uVar14 = local_3c80;
        if (bVar7) {
          uVar14 = local_3c80 - 1;
        }
        local_3c84 = CharacterSelectScreenKey
                               (local_3c5c[4],local_3c5c[5],
                                (int *)(auStack_3ac + local_3c80 * 0x1d + 5),
                                (int *)(auStack_3ac + local_3c80 * 0x1d + 6),uVar14);
        if (local_3c84 == 0xffffffff) {
          uVar14 = auStack_3ac[local_3c80 * 0x1d + 0xb];
          if (uVar14 == 0) {
            lVar10 = random();
            local_3c84 = lVar10 % 0xc;
            lVar10 = random();
            auStack_3ac[local_3c80 * 0x1d + 0xb] = lVar10 % 10 + 10;
          }
          else if ((0 < (int)uVar14) && (iStack_20 % *(int *)(slct + 0x11cc) == 0)) {
            auStack_3ac[local_3c80 * 0x1d + 0xb] = uVar14 - 1;
          }
        }
        uVar14 = auStack_3ac[local_3c80 * 0x1d + 5];
        if ((uVar12 != uVar14) || (uVar3 != auStack_3ac[local_3c80 * 0x1d + 6])) {
          GameSndPlay((int *)g[0x5ec1],*(int *)(local_3c80 * 4 + 0x1094 + slct),
                      *(int *)(local_3c80 * 4 + 0x109c + slct),0);
          uVar14 = auStack_3ac[local_3c80 * 0x1d + 5];
        }
        if ((uVar14 == 0xffffffff) || (auStack_3ac[local_3c80 * 0x1d + 6] == 0xffffffff)) {
          piVar17 = (int *)0x0;
        }
        else {
          piVar17 = cellHead + (auStack_3ac[local_3c80 * 0x1d + 6] * cellCols + uVar14) * 0x80e;
        }
        if ((piVar17 != (int *)0x0) && (0 < g[0x14b5])) {
          if ((bVar4) || (*piVar17 == -2)) {
            iVar11 = cellHead[(cellCols * auStack_3ac[local_3c80 * 0x1d + 8] +
                              auStack_3ac[local_3c80 * 0x1d + 7]) * 0x80e];
            if (iVar11 < 0) {
              lVar10 = random();
              iVar11 = lVar10 % g[0x14b5];
              GetPlayerRowCol(iVar11,(int *)(auStack_3ac + local_3c80 * 0x1d + 7),
                              (int *)(auStack_3ac + local_3c80 * 0x1d + 8));
            }
            if (iStack_20 % *(int *)(slct + 0x11cc) == (*(int *)(slct + 0x11cc) / 2) * local_3c80) {
              if (g[0x14b5] != 1) {
                lVar10 = random();
                iVar11 = (lVar10 % (g[0x14b5] + -1) + 1 + iVar11) % g[0x14b5];
              }
              GetPlayerRowCol(iVar11,(int *)(auStack_3ac + local_3c80 * 0x1d + 7),
                              (int *)(auStack_3ac + local_3c80 * 0x1d + 8));
              if (*(int *)(slct + 0x10c4) == 0) {
                GameSndPlay((int *)g[0x5ec1],*(int *)(local_3c80 * 4 + 0x10b4 + slct),
                            *(int *)(local_3c80 * 4 + 0x10bc + slct),0);
              }
              else {
                GameSndPlayID(local_3c80,(int *)g[0x5ec1],*(int *)(local_3c80 * 4 + 0x10b4 + slct),
                              *(int *)(local_3c80 * 4 + 0x10bc + slct),0);
              }
            }
            cellHead[(cellCols * auStack_3ac[local_3c80 * 0x1d + 8] +
                     auStack_3ac[local_3c80 * 0x1d + 7]) * 0x80e] = iVar11;
            if (bVar4) {
              uVar14 = auStack_3ac[local_3c80 * 0x1d + 7];
              auStack_3ac[local_3c80 * 0x1d + 5] = uVar14;
              auStack_3ac[local_3c80 * 0x1d + 6] = auStack_3ac[local_3c80 * 0x1d + 8];
            }
            else {
              uVar14 = auStack_3ac[local_3c80 * 0x1d + 5];
            }
          }
          else {
            auStack_3ac[local_3c80 * 0x1d + 7] = uVar14;
            auStack_3ac[local_3c80 * 0x1d + 8] = auStack_3ac[local_3c80 * 0x1d + 6];
            uVar14 = auStack_3ac[local_3c80 * 0x1d + 5];
          }
        }
        if (((piVar17 == (int *)0x0) || (auStack_3ac[local_3c80 * 0x1d + 7] == 0xffffffff)) ||
           (auStack_3ac[local_3c80 * 0x1d + 8] == 0xffffffff)) {
          local_3c64 = (uint *)0x0;
        }
        else {
          local_3c64 = (uint *)(cellHead +
                               (auStack_3ac[local_3c80 * 0x1d + 7] +
                               auStack_3ac[local_3c80 * 0x1d + 8] * cellCols) * 0x80e);
        }
        iVar11 = uVar2 * 4;
        auStack_2b4[(iVar11 + auStack_3ac[local_3c80 * 0x1d + 9]) * 8 + 2] = uVar14;
        auStack_2b4[(iVar11 + auStack_3ac[local_3c80 * 0x1d + 9]) * 8 + 3] =
             auStack_3ac[local_3c80 * 0x1d + 6];
        auStack_2b4[(iVar11 + auStack_3ac[local_3c80 * 0x1d + 9]) * 8 + 5] =
             auStack_3ac[local_3c80 * 0x1d + 7];
        auStack_2b4[(iVar11 + auStack_3ac[local_3c80 * 0x1d + 9]) * 8 + 6] =
             auStack_3ac[local_3c80 * 0x1d + 8];
        auStack_2b4[(iVar11 + auStack_3ac[local_3c80 * 0x1d + 9]) * 8 + 8] = 1;
        if (bVar7) {
          auStack_2b4[(iVar11 + auStack_3ac[local_3c80 * 0x1d + 9]) * 8 + 9] = 1 - local_3c80;
        }
        else {
          auStack_2b4[(iVar11 + auStack_3ac[local_3c80 * 0x1d + 9]) * 8 + 9] = local_3c80;
        }
        if (((local_3c84 != 0xffffffff) && (local_3c64 != (uint *)0x0)) &&
           (*local_3c64 != 0xffffffff)) {
          GameSndPlay((int *)g[0x5ec1],*(int *)(local_3c80 * 4 + 0x10a4 + slct),
                      *(int *)(local_3c80 * 4 + 0x10ac + slct),0);
          uVar12 = auStack_3ac[local_3c80 * 0x1d + 0xc];
          auStack_2b4[(auStack_3ac[local_3c80 * 0x1d + 9] + uVar2 * 4) * 8 + 8] = 2;
          uVar2 = auStack_3ac[local_3c80 * 0x1d + auStack_3ac[local_3c80 * 0x1d + 9] * 5 + 0xd];
          uVar3 = local_38e4[uVar2 * 0x6a7 + 1];
          puVar15 = local_38e4 + uVar2 * 0x6a7 + uVar3 * 0x17 + 3;
          local_38e4[uVar2 * 0x6a7 + uVar3 * 0x17 + 3] = *(uint *)(uVar12 + 8);
          uVar14 = local_38e4[uVar2 * 0x6a7 + uVar3 * 0x17 + 5];
          local_38e4[uVar2 * 0x6a7 + uVar3 * 0x17 + 4] = *(uint *)(uVar12 + 0x10);
          local_38e4[uVar2 * 0x6a7 + uVar3 * 0x17 + uVar14 * 5 + 7] = *local_3c64;
          local_38e4
          [uVar2 * 0x6a7 + uVar3 * 0x17 + local_38e4[uVar2 * 0x6a7 + uVar3 * 0x17 + 5] * 5 + 8] =
               local_3c84;
          uVar12 = local_38e4[uVar2 * 0x6a7 + uVar3 * 0x17 + 5];
          local_38e4[uVar2 * 0x6a7 + uVar3 * 0x17 + uVar12 * 5 + 6] = uVar2 + 1 + uVar12 * 2;
          local_38e4
          [uVar2 * 0x6a7 + uVar3 * 0x17 + local_38e4[uVar2 * 0x6a7 + uVar3 * 0x17 + 5] * 5 + 10] =
               auStack_3ac[local_3c80 * 0x1d + auStack_3ac[local_3c80 * 0x1d + 9] * 5 + 0xe];
          local_38e4
          [uVar2 * 0x6a7 + uVar3 * 0x17 + local_38e4[uVar2 * 0x6a7 + uVar3 * 0x17 + 5] * 5 + 9] =
               auStack_3ac[local_3c80 * 0x1d + auStack_3ac[local_3c80 * 0x1d + 9] * 5 + 0xf];
          uVar12 = CharReservePal(local_38e4
                                  [uVar2 * 0x6a7 +
                                   uVar3 * 0x17 +
                                   local_38e4[uVar2 * 0x6a7 + uVar3 * 0x17 + 5] * 5 + 8],
                                  local_38e4
                                  [uVar2 * 0x6a7 +
                                   uVar3 * 0x17 +
                                   local_38e4[uVar2 * 0x6a7 + uVar3 * 0x17 + 5] * 5 + 7]);
          local_38e4
          [uVar2 * 0x6a7 + uVar3 * 0x17 + local_38e4[uVar2 * 0x6a7 + uVar3 * 0x17 + 5] * 5 + 8] =
               uVar12;
          if (g[0x33b3] == 0) {
            iVar11 = piVar1[1];
            uVar12 = auStack_3ac[local_3c80 * 0x1d + 9];
            uVar14 = auStack_3ac[local_3c80 * 0x1d + 6];
            uVar8 = auStack_3ac[local_3c80 * 0x1d + 5];
          }
          else {
            iVar11 = piVar1[1];
            uVar12 = auStack_3ac[local_3c80 * 0x1d + 9];
            uVar14 = auStack_3ac[local_3c80 * 0x1d + 8];
            uVar8 = auStack_3ac[local_3c80 * 0x1d + 7];
          }
          CharselSaveCursor(piVar16,uVar8,uVar14,uVar12,iVar11);
          FlashBox((int)auStack_2b4,auStack_3ac[local_3c80 * 0x1d + 7],
                   auStack_3ac[local_3c80 * 0x1d + 8]);
          if ((g[0x14d0] != 0) && (local_38e4[uVar2 * 0x6a7 + 1] == 0)) {
            PrecacheRequestChar(local_38e4
                                [uVar2 * 0x6a7 +
                                 uVar3 * 0x17 + local_38e4[uVar2 * 0x6a7 + uVar3 * 0x17 + 5] * 5 + 7
                                ]);
            PrecacheStart();
          }
          local_38e4[uVar2 * 0x6a7 + uVar3 * 0x17 + 5] =
               local_38e4[uVar2 * 0x6a7 + uVar3 * 0x17 + 5] + 1;
          uVar12 = auStack_3ac[local_3c80 * 0x1d + 9];
          auStack_3ac[local_3c80 * 0x1d + 9] = uVar12 + 1;
          uVar12 = auStack_3ac[local_3c80 * 0x1d + (uVar12 + 1) * 5 + 0x10];
          if (uVar12 != 0xffffffff) {
            auStack_3ac[local_3c80 * 0x1d + 7] = uVar12;
            auStack_3ac[local_3c80 * 0x1d + 5] = uVar12;
          }
          uVar12 = auStack_3ac[local_3c80 * 0x1d + auStack_3ac[local_3c80 * 0x1d + 9] * 5 + 0x11];
          if (uVar12 != 0xffffffff) {
            auStack_3ac[local_3c80 * 0x1d + 8] = uVar12;
            auStack_3ac[local_3c80 * 0x1d + 6] = uVar12;
          }
          local_38e4[uVar2 * 0x6a7 + 2] = local_38e4[uVar2 * 0x6a7 + 2] + 1;
          uVar12 = *puVar15;
          if ((uVar12 == 3) &&
             ((int)auStack_3ac[local_3c80 * 0x1d + 9] < (int)auStack_3ac[local_3c80 * 0x1d + 10])) {
            local_38e4[uVar2 * 0x6a7 + 1] = local_38e4[uVar2 * 0x6a7 + 1] + 1;
            uVar12 = *puVar15;
          }
          if (uVar12 == 3) {
            *puVar15 = 0;
          }
          if ((int)auStack_3ac[local_3c80 * 0x1d + 10] <= (int)auStack_3ac[local_3c80 * 0x1d + 9]) {
            local_38e4[uVar2 * 0x6a7 + 1] = local_38e4[uVar2 * 0x6a7 + 1] + 1;
            auStack_3ac[uVar2] = 1;
            goto LAB_080881c0;
          }
        }
      }
      break;
    case 3:
      iVar11 = piVar1[1];
      iVar20 = piVar1[2];
      if (iVar20 == 3) {
        iVar23 = 1;
        iVar20 = 0;
        iVar19 = piVar1[3];
      }
      else {
        iVar23 = piVar1[3];
        iVar19 = 1;
      }
      BuildSlctTeamForArcade((int)(local_38e4 + iVar11 * 0x6a7),iVar11,iVar19,iVar20,iVar23);
      if (piVar1[2] == 1) {
        local_38e4[iVar11 * 0x6a7 + 4] = piVar1[4];
      }
      auStack_3ac[piVar1[1]] = 1;
LAB_080881c0:
      iVar11 = SlctStateListNextItem((int)piVar13);
      bVar6 = iVar11 != 0;
      break;
    case 4:
      if (iVar11 != 0) {
        uStack_18c = 1;
      }
      if (bVar4) {
        auStack_3ac[3] = 1;
        auStack_3ac[2] = -1;
      }
      uVar2 = auStack_3ac[3];
      uVar12 = auStack_3ac[2];
      if (auStack_3ac[3] == 0) {
        bVar7 = CharacterSelectStageKey(local_3c5c[4],local_3c5c[5],auStack_3ac + 2,local_3c80);
        auStack_3ac[3] = GHIDRA_ZEXT8(bVar7);
      }
      if (uVar12 != auStack_3ac[2]) {
        GameSndPlay((int *)g[0x5ec1],*(int *)(slct + 0x10c8),*(int *)(slct + 0x10cc),0);
      }
      uVar12 = auStack_3ac[3];
      if ((uVar2 == 0) && (uVar12 = 0, auStack_3ac[3] != 0)) {
        GameSndPlay((int *)g[0x5ec1],*(int *)(slct + 0x10d0),*(int *)(slct + 0x10d4),0);
        uVar12 = auStack_3ac[3];
      }
      if (uVar12 != 0) goto LAB_080881c0;
    }
switchD_080874eb_default:
    if (!bVar6) break;
    local_3c38 = 0;
    local_3c3c = 0;
    local_3c5c[4] = 0;
    local_3c5c[5] = 0;
  } while( true );
  SlctStateListUpdate((int)piVar13);
  local_3c80 = local_3c80 + 1;
  if (1 < local_3c80) goto code_r0x0808824b;
  goto LAB_08087466;
code_r0x0808824b:
  if ((local_3c5c[2] != 0) && (local_3c5c[3] != 0)) {
    if (auStack_2b4[0] - 1 < 2) {
      if (((auStack_2b4[0] == 2) && (local_3ca8 == -1)) && (local_3ca0 == 1)) {
        local_3ca0 = 2;
        local_3ca4 = iStack_20;
        local_3ca8 = iStack_20 + *(int *)(slct + 0x1004);
      }
    }
    else {
      SelectDispState(auStack_2b4,1);
    }
  }
  if ((0 < *(int *)(slct + 0x1000)) && (local_3ca0 == 0)) {
    iVar11 = (iStack_20 << 8) / *(int *)(slct + 0x1000);
    MasterPalMul(iVar11,iVar11,iVar11);
  }
  if (iStack_20 == *(int *)(slct + 0x1000)) {
    local_3ca0 = 1;
  }
  if ((0 < *(int *)(slct + 0x1004)) && (local_3ca0 == 2)) {
    uVar12 = 0x100 - ((iStack_20 - local_3ca4) * 0x100) / *(int *)(slct + 0x1004);
    uVar12 = uVar12 & 0xffffffffU - ((int)uVar12 >> 0x1f);
    MasterPalMul(uVar12,uVar12,uVar12);
  }
  UpdateSelectDisp((int *)auStack_2b4);
  if (g[0x7309] == 0) {
    ExplodArrayUpdate((int *)g[0x52bf]);
  }
  CharacterSelectScreenDraw((int)piVar16);
  iStack_20 = iStack_20 + 1;
  if (local_3c3c == 0x58) {
    ScreenSnap();
  }
  if (bVar5) goto LAB_0808844d;
  if ((local_3ca8 != -1) && (local_3ca8 < iStack_20)) {
    bVar5 = true;
  }
  if (local_3c3c == 1) goto LAB_0808844d;
  goto LAB_08087348;
}
#undef iStack_3cc8
#undef local_3ca8
#undef local_3ca4
#undef local_3ca0
#undef local_3c84
#undef local_3c80
#undef local_3c64
#undef local_3c5c
#undef local_3c40
#undef local_3c3c
#undef local_3c38
#undef local_3c34
#undef aiStack_3c08
#undef aiStack_3a9c
#undef local_38e4
#undef auStack_3ac
#undef auStack_2b4
#undef uStack_18c
#undef aiStack_188
#undef iStack_20

/* CharacterSelectScreenDraw @ 0x08088630, 4562 bytes
 * FIXUP: 10 data addresses written as literals replaced by data-image references
 * FIXUP: 4 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 27 stack locals placed at their original offsets in a 0x210-byte frame (a local's address escapes, see apply_frame_emulation) */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

undefined4 CharacterSelectScreenDraw(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  char *__format;
  unsigned char ghidra_frame[0x210] __attribute__((aligned(16)));
#define local_210 (*(int *)(ghidra_frame + 0x0))
#define local_1c4 (*(int *)(ghidra_frame + 0x4c))
#define local_1c0 (*(int **)(ghidra_frame + 0x50))
#define local_1bc (*(int *)(ghidra_frame + 0x54))
#define local_1b8 (*(uint *)(ghidra_frame + 0x58))
#define local_1b4 (*(int *)(ghidra_frame + 0x5c))
#define local_1b0 (*(int *)(ghidra_frame + 0x60))
#define local_1ac (*(int **)(ghidra_frame + 0x64))
#define local_1a8 (*(int *)(ghidra_frame + 0x68))
#define local_1a4 (*(int *)(ghidra_frame + 0x6c))
#define local_1a0 (*(int *)(ghidra_frame + 0x70))
#define local_19c (*(int *)(ghidra_frame + 0x74))
#define local_198 (*(int *)(ghidra_frame + 0x78))
#define local_194 (*(int *)(ghidra_frame + 0x7c))
#define local_18c (*(int *)(ghidra_frame + 0x84))
#define local_168 (*(int *)(ghidra_frame + 0xa8))
#define local_164 (*(int *)(ghidra_frame + 0xac))
#define local_160 (*(uint *)(ghidra_frame + 0xb0))
#define local_15c (*(int *)(ghidra_frame + 0xb4))
#define local_158 (*(int *)(ghidra_frame + 0xb8))
#define local_154 (*(int **)(ghidra_frame + 0xbc))
#define local_14c (*(int (*)[28])(ghidra_frame + 0xc4))
#define local_dc (*(int *)(ghidra_frame + 0x134))
#define local_d4 (*(int *)(ghidra_frame + 0x13c))
#define local_d0 (*(int *)(ghidra_frame + 0x140))
#define local_c8 (*(int *)(ghidra_frame + 0x148))
#define local_7c (*(char (*)[108])(ghidra_frame + 0x194))
  
  iVar9 = 0;
  iVar2 = param_1 + 0x3978;
  local_14c[2] = 0xffffffff;
  local_14c[3] = 0xffffffff;
  local_14c[0] = 0;
  local_14c[1] = 0;
  MasterPalProcessChanges();
  iVar10 = cellCols;
  local_168 = 0;
  do {
    iVar3 = local_168 * 0x80;
    local_160 = 0;
    iVar7 = iVar3 + 0x10;
    do {
      iVar4 = *(int *)(param_1 + 0x3970 + iVar7);
      if ((iVar4 == -1) || (iVar8 = *(int *)(param_1 + 0x3974 + iVar7), iVar8 == -1)) {
        *(undefined4 *)(iVar2 + iVar7) = 0xffffffff;
      }
      else {
        *(int *)(iVar2 + iVar7) = iVar4 + iVar8 * iVar10;
        if (*(int *)(param_1 + 0x3988 + iVar7) != 0) {
          *(uint *)((int)local_14c + iVar9 + 8) = local_160;
        }
      }
      iVar4 = *(int *)(iVar3 + 0x14 + iVar2);
      if ((iVar4 == -1) || (iVar8 = *(int *)(param_1 + 0x3980 + iVar7), iVar8 == -1)) {
        *(undefined4 *)(param_1 + 0x3994 + iVar3) = 0xffffffff;
      }
      else {
        *(int *)(iVar7 + param_1 + 0x3984) = iVar4 + iVar8 * iVar10;
      }
      iVar7 = iVar7 + 0x20;
      local_160 = local_160 + 1;
      iVar3 = iVar3 + 0x20;
    } while ((int)local_160 < 4);
    iVar9 = iVar9 + 4;
    local_168 = local_168 + 1;
  } while (local_168 < 2);
  local_1c0 = local_14c;
  local_168 = 0;
  do {
    iVar9 = local_168 * 0x80;
    local_160 = 0;
    iVar10 = iVar9 + 0x10;
    local_210 = iVar10;
    do {
      if ((*(int *)(iVar9 + 8 + iVar2) != -1) && (*(int *)(iVar9 + 0xc + iVar2) != -1)) {
        iVar7 = *(int *)(local_210 + 0x10 + iVar2);
        if (iVar7 == 2) {
          local_164 = 0;
        }
        else if (iVar7 == 1) {
          local_164 = 1;
        }
        local_14c[local_14c[local_164] * 3 + local_164 * 0x18 + 5] = *(int *)(iVar10 + 0x14 + iVar2)
        ;
        local_14c[local_14c[local_164] * 3 + local_164 * 0x18 + 4] = local_168;
        local_14c[local_14c[local_164] * 3 + local_164 * 0x18 + 6] = local_160;
        local_14c[local_164] = local_14c[local_164] + 1;
      }
      local_160 = local_160 + 1;
      local_210 = local_210 + 0x20;
      iVar10 = iVar10 + 0x20;
      iVar9 = iVar9 + 0x20;
    } while ((int)local_160 < 4);
    local_168 = local_168 + 1;
  } while (local_168 < 2);
  PRSprArrayClear((int *)g[0x413d]);
  BGArrayMove((int *)g[0x62cf],0.0,0.0);
  BGArrayUpdate(g[0x62cf]);
  if (g[0x7306] == 0) {
    BGArrayDrawLayer(g[0x62cf],0);
  }
  if (g[0x7306] == 0) {
    iVar9 = 0x13a0;
    iVar10 = 0x13b0;
    iVar7 = 0;
    local_168 = 1;
    do {
      piVar6 = cellHead;
      iVar3 = *(int *)((int)local_14c + iVar7 + 8);
      if (((iVar3 != -1) &&
          (iVar3 = *(int *)((iVar3 + iVar7) * 0x20 + 0x1c + iVar2),
          cellHead[iVar3 * 0x80e + 0x80d] != 0)) &&
         (iVar4 = SpriteArrayGetNum((int *)cellHead[iVar3 * 0x80e + 0x80d],9000,1), iVar4 != -1)) {
        W_ScaleSprite_S((int *)piVar6[iVar3 * 0x80e + 0x80d],iVar4,(float10)*(int *)(iVar9 + slct + 4)
                        ,(float10)*(int *)(iVar9 + 8 + slct),
                        (float10)*(int *)(iVar9 + 0xc + slct) * *(float *)(iVar9 + 0x10 + slct),
                        *(float *)(iVar10 + slct + 4));
      }
      iVar9 = iVar9 + 0x28;
      iVar10 = iVar10 + 0x28;
      iVar7 = iVar7 + 4;
      local_168 = local_168 + -1;
    } while (-1 < local_168);
  }
  local_1b8 = *(uint *)(slct + 0x1008);
  iVar10 = *(int *)(slct + 0x100c);
  local_158 = 0;
  iVar9 = cellRows;
  iVar3 = slct;
  iVar7 = cellCols;
  if (0 < cellRows) {
    do {
      local_15c = 0;
      if (0 < iVar7) {
        do {
          piVar6 = cellHead + (local_158 * iVar7 + local_15c) * 0x80e;
          if ((*piVar6 != -1) || (iVar9 = -1, *(int *)(iVar3 + 0x1028) != 0)) {
            SysExplodCreateDraw_Sys((int *)(iVar3 + 0x10f4),local_1b8,iVar10,0);
            iVar9 = *piVar6;
          }
          if (iVar9 == -2) {
            SysExplodCreateDraw_Sys
                      ((int *)(slct + 0x1160),local_1b8 + *(int *)(slct + 0x1038),
                       iVar10 + *(int *)(slct + 0x103c),0);
          }
          if (((g[0x7306] == 0) && (piVar6[0x80d] != 0)) &&
             ((piVar6 != (int *)0xffffffcc &&
              (iVar9 = SpriteArrayGetNum((int *)piVar6[0x80d],9000,0), iVar9 != -1)))) {
            W_ScaleSprite_S((int *)piVar6[0x80d],iVar9,
                            (float10)(int)(local_1b8 + *(int *)(slct + 0x1038)),
                            (float)(iVar10 + *(int *)(slct + 0x103c)),*(float *)(slct + 0x1030),
                            *(float *)(slct + 0x1034));
          }
          local_15c = local_15c + 1;
          local_1b8 = local_1b8 + *(int *)(slct + 0x101c) + *(int *)(slct + 0x1018);
          iVar9 = cellRows;
          iVar7 = cellCols;
          iVar3 = slct;
        } while (local_15c < cellCols);
      }
      local_1b8 = *(uint *)(iVar3 + 0x1008);
      iVar10 = iVar10 + *(int *)(iVar3 + 0x1020) + *(int *)(iVar3 + 0x1018);
      local_158 = local_158 + 1;
    } while (local_158 < iVar9);
  }
  if (g[0x7306] == 0) {
    local_160 = 1;
    iVar10 = 0x100;
    do {
      iVar9 = *(int *)(iVar10 + 0x10 + iVar2);
      if (0 < iVar9) {
        iVar9 = (iVar9 * 0xff) / *(int *)(iVar10 + 0x14 + iVar2);
        uVar5 = makecol(iVar9,iVar9,iVar9);
        local_1b8 = *(int *)(param_1 + 0x3980 + iVar10) *
                    (*(int *)(slct + 0x1018) + *(int *)(slct + 0x101c)) + *(int *)(slct + 0x1008);
        iVar9 = *(int *)(iVar10 + 0xc + iVar2) * (*(int *)(slct + 0x1018) + *(int *)(slct + 0x1020))
                + *(int *)(slct + 0x100c);
        W_BoxFillTransAdd16(local_1b8,iVar9,(local_1b8 + *(int *)(slct + 0x101c)) - 2,
                            iVar9 + *(int *)(slct + 0x1020) + -2,uVar5);
      }
      iVar10 = iVar10 + 0x10;
      local_160 = local_160 + -1;
    } while (-1 < (int)local_160);
  }
  local_164 = 0;
  local_1c4 = 0;
  do {
    local_160 = 0;
    if (0 < *local_1c0) {
      iVar9 = param_1 + 0x3980;
      iVar10 = param_1 + 0x3984;
      local_1bc = 0;
      do {
        iVar3 = local_1bc + local_1c4;
        iVar7 = *(int *)((int)local_14c + iVar3 + 0x14);
        iVar3 = (*(int *)((int)local_14c + iVar3 + 0x10) * 4 +
                *(int *)((int)local_14c + iVar3 + 0x18)) * 0x20;
        if (local_164 == 0) {
          piVar6 = (int *)(slct + 0x12a8 + iVar7 * 0x6c);
LAB_08088ecc:
          SysExplodCreateDraw_Sys
                    (piVar6,*(int *)(iVar3 + iVar9) *
                            (*(int *)(slct + 0x1018) + *(int *)(slct + 0x101c)) +
                            *(int *)(slct + 0x1008),
                     *(int *)(iVar3 + iVar10) * (*(int *)(slct + 0x1018) + *(int *)(slct + 0x1020))
                     + *(int *)(slct + 0x100c),0);
        }
        else if (local_164 == 1) {
          if ((local_14c[1] == 2) && (*(int *)(slct + 0x1090) != 0)) {
            iVar4 = (local_d4 + local_dc * 4) * 0x20;
            iVar8 = (local_c8 + local_d0 * 4) * 0x20;
            if ((*(int *)(iVar4 + iVar9) == *(int *)(iVar8 + iVar9)) &&
               (*(int *)(iVar4 + iVar10) == *(int *)(iVar8 + iVar10))) {
              if ((*(uint *)(param_1 + 0x3c0c) & 7) < 4 == local_160) {
                piVar6 = (int *)(slct + 0x11d0 + iVar7 * 0x6c);
                goto LAB_08088ecc;
              }
              goto LAB_08088ed5;
            }
          }
          piVar6 = (int *)(slct + 0x11d0 + iVar7 * 0x6c);
          goto LAB_08088ecc;
        }
LAB_08088ed5:
        local_1b8 = local_160 + 1;
        local_1bc = local_1bc + 0xc;
        local_160 = local_1b8;
      } while ((int)local_1b8 < *local_1c0);
    }
    local_164 = local_164 + 1;
    local_1c0 = local_1c0 + 1;
    local_1c4 = local_1c4 + 0x60;
    if (1 < local_164) {
      piVar6 = g;
      if (g[0x7306] == 0) {
        local_168 = 0;
        local_1b4 = 0;
        local_1b8 = 0x13c0;
        do {
          iVar10 = *(int *)(local_1b8 + 4 + slct);
          iVar9 = *(int *)(local_1b8 + 8 + slct);
          local_1b0 = local_168 << 7;
          local_160 = 3;
          do {
            iVar7 = *(int *)(local_1b0 + 0x10 + iVar2);
            if (iVar7 != -1) {
              local_154 = (int *)0x0;
              piVar1 = cellHead + iVar7 * 0x80e;
              if ((char)piVar1[1] == '\0') {
                if (*piVar1 == -2) {
                  local_154 = (int *)(int)&DAT_08277b3a;
                }
              }
              else {
                local_154 = piVar1 + 1;
              }
              if (local_154 != (int *)0x0) {
                iVar7 = *(int *)(local_1b4 + 0x13b8 + slct);
                if (iVar7 != -1) {
                  V_FontDrawAlignBank((char *)local_154,(int *)piVar6[iVar7 + 0x62c3],iVar10,iVar9,
                                      *(int *)(local_1b4 + 0x13c0 + slct),
                                      *(int *)(local_1b4 + 0x13bc + slct));
                  piVar6 = g;
                }
                iVar9 = iVar9 + 0xe;
              }
            }
            local_1b0 = local_1b0 + 0x20;
            local_160 = local_160 + -1;
          } while (-1 < (int)local_160);
          local_168 = local_168 + 1;
          local_1b4 = local_1b4 + 0x28;
          local_1b8 = local_1b8 + 0x28;
        } while (local_168 < 2);
      }
      if (piVar6[0x7306] == 0) {
        PRSprArrayDraw((int *)piVar6[0x413d]);
      }
      if ((*(int *)(param_1 + 0x3aa0) != 0) && (g[0x7306] == 0)) {
        iVar10 = *(int *)(param_1 + 0x3888);
        if (iVar10 == -1) {
          __format = "Stage: Random";
          uVar5 = local_1b8;
        }
        else {
          uVar5 = g[0x33ac] + 0xfff + iVar10 * 0x1054;
          local_1b8 = iVar10 + 1;
          __format = "Stage %i: %s";
        }
        sprintf(local_7c,__format,local_1b8,uVar5);
        if (*(int *)(param_1 + 0x388c) == 0) {
          iVar10 = *(int *)(((*(int *)(param_1 + 0x3c0c) - (*(int *)(param_1 + 0x3c0c) >> 0x1f)) * 2
                            & 4U) + 0x1394 + slct);
          iVar2 = *(int *)(slct + 0x13a0);
          iVar9 = *(int *)(slct + 0x1384);
          iVar7 = *(int *)(slct + 0x1380);
          iVar3 = *(int *)(((*(int *)(param_1 + 0x3c0c) - (*(int *)(param_1 + 0x3c0c) >> 0x1f)) * 2
                           & 4U) + 5000 + slct);
        }
        else {
          iVar10 = *(int *)(slct + 0x139c);
          iVar2 = *(int *)(slct + 0x13a0);
          iVar9 = *(int *)(slct + 0x1384);
          iVar7 = *(int *)(slct + 0x1380);
          iVar3 = *(int *)(slct + 0x1390);
        }
        V_FontDrawAlignBank(local_7c,(int *)g[iVar3 + 0x62c3],iVar7,iVar9,iVar2,iVar10);
      }
      local_1a0 = param_1 + 0x3ab8;
      local_19c = param_1 + 0x3ab0;
      local_1a4 = param_1 + 0x3ab4;
      local_1a8 = param_1 + 0x3aac;
      local_1ac = (int *)(param_1 + 0x3aa4);
      local_168 = 0;
      local_198 = local_1a0;
      do {
        if (*local_1ac != 0) {
          iVar9 = local_1ac[2] * 0x2e4;
          iVar10 = *(int *)(iVar9 + 0x13f8 + slct);
          iVar2 = *(int *)(iVar9 + 0x13fc + slct);
          SysExplodCreateDraw_Sys((int *)(iVar9 + 0x1400 + slct),iVar10,iVar2,0);
          if ((g[0x33b3] == 0) || (local_168 == local_1ac[2])) {
            piVar6 = (int *)(slct + 0x146c + local_1ac[2] * 0x2e4);
          }
          else {
            piVar6 = (int *)(slct + 0x14d8 + local_1ac[2] * 0x2e4);
          }
          SysExplodCreateDraw_Sys(piVar6,iVar10,iVar2,0);
          iVar9 = local_1ac[2];
          iVar10 = iVar10 + *(int *)(iVar9 * 0x2e4 + 0x155c + slct);
          local_160 = 0;
          iVar2 = iVar2 + *(int *)(iVar9 * 0x2e4 + 0x1560 + slct);
          if (0 < local_1ac[4]) {
            local_194 = 0x10;
            do {
              if (local_160 == local_1ac[3]) {
                iVar7 = (iVar9 * 0xb9 + 1 + (*(int *)(param_1 + 0x3c0c) / 2 & 1U)) * 4;
                local_18c = *(int *)(iVar7 + 0x1564 + slct);
                iVar7 = *(int *)(iVar7 + 0x1570 + slct);
                SysExplodCreateDraw_Sys((int *)(slct + 0x1588 + iVar9 * 0x2e4),iVar10,iVar2,0);
                iVar9 = local_1ac[2];
              }
              else {
                local_18c = *(int *)(iVar9 * 0x2e4 + 0x1564 + slct);
                iVar7 = *(int *)(iVar9 * 0x2e4 + 0x1570 + slct);
              }
              V_FontDrawAlignBank(*(char **)(local_194 + local_1a8),(int *)g[local_18c + 0x62c3],
                                  iVar10,iVar2,*(int *)(slct + 0x157c + iVar9 * 0x2e4),iVar7);
              if (*(int *)(local_194 + local_1a0) < *(int *)(local_194 + local_1a4)) {
                iVar9 = local_1ac[2];
              }
              else {
                local_164 = 0;
                if (*(int *)(local_194 + local_1a0) < 1) {
                  iVar9 = local_1ac[2];
                }
                else {
                  iVar9 = local_1ac[2];
                  iVar7 = iVar10;
                  iVar3 = iVar2;
                  do {
                    if (local_164 < *(int *)(local_194 + local_19c)) {
                      piVar6 = (int *)(slct + 0x15f4 + iVar9 * 0x2e4);
                    }
                    else {
                      piVar6 = (int *)(slct + 0x1668 + iVar9 * 0x2e4);
                    }
                    SysExplodCreateDraw_Sys(piVar6,iVar7,iVar3,0);
                    iVar9 = local_1ac[2];
                    iVar7 = iVar7 + *(int *)(iVar9 * 0x2e4 + 0x1660 + slct);
                    iVar3 = iVar3 + *(int *)(iVar9 * 0x2e4 + 0x1664 + slct);
                    local_164 = local_164 + 1;
                  } while (local_164 < *(int *)(local_194 + local_198));
                }
              }
              iVar10 = iVar10 + *(int *)(iVar9 * 0x2e4 + 0x1580 + slct);
              local_160 = local_160 + 1;
              local_194 = local_194 + 0x14;
              iVar2 = iVar2 + *(int *)(iVar9 * 0x2e4 + 0x1584 + slct);
            } while ((int)local_160 < local_1ac[4]);
          }
        }
        local_168 = local_168 + 1;
        local_198 = local_198 + 0xb4;
        local_19c = local_19c + 0xb4;
        local_1a0 = local_1a0 + 0xb4;
        local_1a4 = local_1a4 + 0xb4;
        local_1a8 = local_1a8 + 0xb4;
        local_1ac = local_1ac + 0x2d;
      } while (local_168 < 2);
      if (g[0x7306] == 0) {
        local_154 = (int *)0x0;
        switch(g[0x33b5]) {
        case 0:
          local_154 = (int *)(int)&DAT_08277b5f;
          break;
        case 1:
          local_154 = (int *)(int)&DAT_08277b4e;
          break;
        case 2:
          local_154 = (int *)(int)&DAT_08277b5a;
          break;
        case 3:
          local_154 = (int *)(int)&DAT_08277b66;
          break;
        case 4:
          local_154 = (int *)(int)&DAT_08277b72;
          break;
        case 5:
          local_154 = (int *)(int)&DAT_08277b83;
          break;
        case 6:
          local_154 = (int *)(int)&DAT_08277b8c;
          break;
        case 7:
          local_154 = (int *)(int)&DAT_08277ba1;
          break;
        case 8:
          local_154 = (int *)(int)&DAT_08277baf;
        }
        if ((*(int *)(slct + 0x10e8) != -1) && (local_154 != (int *)0x0)) {
          V_FontDrawAlignBank((char *)local_154,(int *)g[*(int *)(slct + 0x10e8) + 0x62c3],
                              *(int *)(slct + 0x10e0),*(int *)(slct + 0x10e4),
                              *(int *)(slct + 0x10f0),*(int *)(slct + 0x10ec));
        }
        BGArrayDrawLayer(g[0x62cf],1);
      }
      if ((g[0x81cd] != 0) && ((g[0x74e8] == 0 || (g[0x74f0] != 0)))) {
        uVar5 = makecol(0xff,0xff,0xff);
        FontDrawClipboard((int *)g[0x81d1],(int *)g[0x413a],10,0x32,uVar5);
      }
      if (g[0x82d2] == 0) {
        TimerWaitSync();
      }
      if ((g[0x7306] == 0) && (g[0x4143] != 0)) {
        VRetrace();
      }
      DrawToScreen();
      if (g[0x7307] == 0) {
        MasterPalFinishedDraw();
      }
      FrameSkipUpdate();
      return 0;
    }
  } while( true );
}
#undef local_210
#undef local_1c4
#undef local_1c0
#undef local_1bc
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
#undef local_18c
#undef local_168
#undef local_164
#undef local_160
#undef local_15c
#undef local_158
#undef local_154
#undef local_14c
#undef local_dc
#undef local_d4
#undef local_d0
#undef local_c8
#undef local_7c

/* BuildSelectList @ 0x08089810, 1421 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x20-byte frame (a local's address escapes, see apply_frame_emulation) */
int BuildSelectList(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  unsigned char ghidra_frame[0x20] __attribute__((aligned(16)));
#define local_14 (*(int (*)[2])(ghidra_frame + 0xc))
  
  piVar2 = g;
  local_14[0] = param_1;
  local_14[1] = param_1 + 0x1a0;
  *(undefined4 *)local_14[param_3] = 0;
  piVar2[0x33b3] = 0;
  piVar2[0x33b4] = 0;
  piVar2[0x33ae] = 0;
  switch(param_2) {
  case 0:
    iVar1 = local_14[param_3];
    *(undefined4 *)(iVar1 + 0x28) = 2;
    *(int *)(iVar1 + 0x2c) = param_3;
    *(undefined4 *)(iVar1 + 0x30) = 0;
    *(undefined4 *)(iVar1 + 0x34) = 1;
    *(int *)(iVar1 + 0x54) = 1 - param_3;
    *(undefined4 *)(iVar1 + 0x50) = 3;
    *(undefined4 *)(iVar1 + 0x58) = 0;
    *(undefined4 *)(iVar1 + 0x5c) = 1;
    *(undefined4 *)(iVar1 + 0x78) = 5;
    *(undefined4 *)(iVar1 + 400) = 4;
    piVar2 = g;
    goto LAB_08089b29;
  case 1:
    *(undefined4 *)(param_1 + 0x28) = 2;
    *(undefined4 *)(param_1 + 0x2c) = 0;
    *(undefined4 *)(param_1 + 0x30) = 0;
    *(undefined4 *)(param_1 + 0x34) = 1;
    *(undefined4 *)(param_1 + 0x50) = 4;
    *(undefined4 *)(param_1 + 0x78) = 5;
    *(undefined4 *)(param_1 + 400) = 4;
    iVar1 = 0x19;
    iVar4 = 6;
    *(undefined4 *)(param_1 + 0x240) = 2;
    *(undefined4 *)(param_1 + 0x244) = 1;
    *(undefined4 *)(param_1 + 0x248) = 0;
    *(undefined4 *)(param_1 + 0x24c) = 1;
    goto LAB_08089a76;
  case 2:
    iVar1 = local_14[param_3];
    *(undefined4 *)(iVar1 + 0x28) = 1;
    *(int *)(iVar1 + 0x4c) = iVar1 + 0x50;
    *(int *)(iVar1 + 0x48) = param_3;
    *(undefined4 *)(iVar1 + 0x3c) = 0;
    *(undefined4 *)(iVar1 + 0x40) = 0xb;
    *(undefined4 *)(iVar1 + 0x44) = 1;
    puVar3 = (undefined4 *)(iVar1 + 0x50);
    iVar4 = 0xf;
    iVar5 = 4;
    *puVar3 = 2;
    *(int *)(iVar1 + 0x54) = param_3;
    *(undefined4 *)(iVar1 + 0x58) = 1;
    *(undefined4 *)(iVar1 + 0x60) = 0;
    goto LAB_08089abf;
  case 3:
    *(undefined4 *)(param_1 + 0x28) = 1;
    *(int *)(param_1 + 0x4c) = param_1 + 0x50;
    *(undefined4 *)(param_1 + 0x3c) = 0;
    *(undefined4 *)(param_1 + 0x40) = 0xb;
    *(undefined4 *)(param_1 + 0x48) = 0;
    *(undefined4 *)(param_1 + 0x44) = 1;
    *(undefined4 *)(param_1 + 0x50) = 2;
    *(undefined4 *)(param_1 + 0x54) = 0;
    *(undefined4 *)(param_1 + 0x58) = 1;
    *(undefined4 *)(param_1 + 0x60) = 0;
    *(undefined4 *)(param_1 + 0x5c) = 2;
    *(undefined4 *)(param_1 + 0x78) = 4;
    *(undefined4 *)(param_1 + 0xa0) = 5;
    *(undefined4 *)(param_1 + 400) = 5;
    *(undefined4 *)(param_1 + 0x268) = 1;
    *(int *)(param_1 + 0x28c) = param_1 + 0x290;
    *(undefined4 *)(param_1 + 0x27c) = 0;
    *(undefined4 *)(param_1 + 0x280) = 0xb;
    *(undefined4 *)(param_1 + 0x288) = 1;
    *(undefined4 *)(param_1 + 0x284) = 1;
    iVar1 = 0x23;
    iVar4 = 8;
    *(undefined4 *)(param_1 + 0x290) = 2;
    *(undefined4 *)(param_1 + 0x294) = 1;
    *(undefined4 *)(param_1 + 0x298) = 1;
    *(undefined4 *)(param_1 + 0x2a0) = 0;
    *(undefined4 *)(param_1 + 0x29c) = 2;
LAB_08089a76:
    *(undefined4 *)(local_14[1] + iVar1 * 8) = 4;
    *(undefined4 *)(local_14[1] + iVar4 * 0x28) = 5;
    *(int *)(param_1 + 0x330) = iVar4 + 1;
    break;
  case 4:
    iVar1 = local_14[param_3];
    puVar3 = (undefined4 *)(iVar1 + 0x28);
    iVar4 = 10;
    iVar5 = 3;
    *puVar3 = 2;
    *(int *)(iVar1 + 0x2c) = param_3;
    *(undefined4 *)(iVar1 + 0x30) = 1;
    *(undefined4 *)(iVar1 + 0x38) = 1;
LAB_08089abf:
    puVar3[3] = 2;
    puVar3 = (undefined4 *)(iVar1 + iVar4 * 8);
    *puVar3 = 1;
    puVar3[9] = puVar3 + 10;
    puVar3[8] = 1 - param_3;
    puVar3[5] = 0;
    puVar3[6] = 0xb;
    puVar3[7] = 1;
    puVar3 = (undefined4 *)(iVar1 + iVar5 * 0x28);
    puVar3[1] = 1 - param_3;
    piVar2 = g;
    *puVar3 = 3;
    puVar3[2] = 1;
    puVar3[4] = 2;
    puVar3[3] = 2;
    *(undefined4 *)(iVar1 + (iVar5 + 1) * 0x28) = 5;
    *(int *)(iVar1 + 400) = iVar5 + 2;
LAB_08089b29:
    piVar2[0x33b3] = param_3 + 1;
    break;
  case 5:
    iVar1 = local_14[param_3];
    *(undefined4 *)(iVar1 + 0x28) = 1;
    *(int *)(iVar1 + 0x4c) = iVar1 + 0x50;
    *(int *)(iVar1 + 0x48) = param_3;
    *(undefined4 *)(iVar1 + 0x3c) = 0;
    *(undefined4 *)(iVar1 + 0x40) = 0xb;
    *(undefined4 *)(iVar1 + 0x44) = 0;
    puVar3 = (undefined4 *)(iVar1 + 0x50);
    iVar4 = 0xf;
    iVar5 = 4;
    *puVar3 = 2;
    *(int *)(iVar1 + 0x54) = param_3;
    *(undefined4 *)(iVar1 + 0x58) = 1;
    *(undefined4 *)(iVar1 + 0x60) = 0;
    goto LAB_08089bbc;
  case 6:
    iVar1 = local_14[param_3];
    puVar3 = (undefined4 *)(iVar1 + 0x28);
    iVar4 = 10;
    iVar5 = 3;
    *puVar3 = 2;
    *(int *)(iVar1 + 0x2c) = param_3;
    *(undefined4 *)(iVar1 + 0x30) = 1;
    *(undefined4 *)(iVar1 + 0x38) = 1;
LAB_08089bbc:
    puVar3[3] = 2;
    puVar3 = (undefined4 *)(iVar1 + iVar4 * 8);
    *puVar3 = 1;
    puVar3[9] = puVar3 + 10;
    puVar3[8] = 1 - param_3;
    puVar3[5] = 0;
    puVar3[6] = 3;
    puVar3[7] = 0;
    puVar3 = (undefined4 *)(iVar1 + iVar5 * 0x28);
    puVar3[1] = 1 - param_3;
    *puVar3 = 3;
    puVar3[2] = 1;
    puVar3[4] = 2;
    puVar3[3] = 2;
    *(undefined4 *)(param_1 + (iVar5 + 1) * 0x28) = 4;
    *(undefined4 *)(iVar1 + (iVar5 + 2) * 0x28) = 5;
    *(int *)(iVar1 + 400) = iVar5 + 3;
    piVar2 = g;
    g[0x33b3] = 0;
    piVar2[0x33b4] = param_3 + 1;
    piVar2[0x33ae] = 1;
    break;
  case 7:
    iVar1 = local_14[param_3];
    *(undefined4 *)(iVar1 + 0x28) = 2;
    *(int *)(iVar1 + 0x2c) = param_3;
    *(undefined4 *)(iVar1 + 0x30) = 0;
    *(undefined4 *)(iVar1 + 0x34) = 1;
    *(int *)(iVar1 + 0x54) = 1 - param_3;
    *(undefined4 *)(iVar1 + 0x50) = 2;
    *(undefined4 *)(iVar1 + 0x58) = 0;
    *(undefined4 *)(iVar1 + 0x5c) = 1;
    *(undefined4 *)(iVar1 + 0x78) = 4;
    *(undefined4 *)(iVar1 + 0xa0) = 5;
    *(undefined4 *)(iVar1 + 400) = 5;
    g[0x33ae] = 3;
    break;
  case 8:
    iVar1 = local_14[param_3];
    *(undefined4 *)(iVar1 + 0x28) = 1;
    *(int *)(iVar1 + 0x4c) = iVar1 + 0x50;
    *(int *)(iVar1 + 0x48) = param_3;
    *(undefined4 *)(iVar1 + 0x3c) = 0;
    *(undefined4 *)(iVar1 + 0x40) = 0xb;
    *(undefined4 *)(iVar1 + 0x44) = 0;
    *(undefined4 *)(iVar1 + 0x50) = 2;
    *(int *)(iVar1 + 0x54) = param_3;
    *(undefined4 *)(iVar1 + 0x58) = 0;
    *(undefined4 *)(iVar1 + 0x5c) = 1;
    *(undefined4 *)(iVar1 + 0x78) = 1;
    *(int *)(iVar1 + 0x9c) = iVar1 + 0xa0;
    *(int *)(iVar1 + 0x98) = 1 - param_3;
    *(undefined4 *)(iVar1 + 0x8c) = 0;
    *(undefined4 *)(iVar1 + 0x90) = 0xb;
    *(undefined4 *)(iVar1 + 0x94) = 0;
    *(undefined4 *)(iVar1 + 0xa0) = 2;
    *(int *)(iVar1 + 0xa4) = 1 - param_3;
    *(undefined4 *)(iVar1 + 0xa8) = 0;
    *(undefined4 *)(iVar1 + 0xac) = 1;
    *(undefined4 *)(iVar1 + 200) = 4;
    *(undefined4 *)(iVar1 + 0xf0) = 5;
    *(undefined4 *)(iVar1 + 400) = 7;
    g[0x33ae] = 2;
  }
  return local_14[1];
}
#undef local_14

/* InitSelectDisp @ 0x08089da0, 85 bytes */
void InitSelectDisp(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar2 = param_1;
  do {
    puVar1 = (undefined4 *)(iVar2 + 0x10);
    iVar3 = 3;
    do {
      puVar1[-1] = 0xffffffff;
      puVar1[-2] = 0xffffffff;
      *puVar1 = 0xffffffff;
      puVar1 = puVar1 + 8;
      iVar3 = iVar3 + -1;
    } while (-1 < iVar3);
    iVar4 = iVar4 + 1;
    iVar2 = iVar2 + 0x80;
  } while (iVar4 < 2);
  iVar2 = 1;
  puVar1 = (undefined4 *)(param_1 + 0x124);
  do {
    *puVar1 = 4;
    puVar1 = puVar1 + -4;
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  return;
}

/* UpdateSelectDisp @ 0x08089e00, 75 bytes */
void UpdateSelectDisp(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 1;
  iVar2 = 0x100;
  do {
    iVar1 = *(int *)((int)param_1 + iVar2 + 0x10);
    if (0 < iVar1) {
      *(int *)((int)param_1 + iVar2 + 0x10) = iVar1 + -1;
    }
    iVar2 = iVar2 + 0x10;
    iVar3 = iVar3 + -1;
  } while (-1 < iVar3);
  param_1[1] = param_1[1] + 1;
  if (((*param_1 == 1) && (param_1[0x44] < 1)) && (param_1[0x48] < 1)) {
    *param_1 = 2;
  }
  return;
}

/* SelectDispState @ 0x08089e50, 18 bytes */
void SelectDispState(undefined4 *param_1,undefined4 param_2)

{
  *param_1 = param_2;
  param_1[1] = 0;
  return;
}

/* FlashBox @ 0x08089e70, 79 bytes */
void FlashBox(int param_1,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = 0;
  iVar4 = 0;
  iVar3 = 999;
  piVar1 = (int *)(param_1 + 0x110);
  do {
    if (*piVar1 < iVar3) {
      iVar3 = *piVar1;
      iVar4 = iVar2;
    }
    iVar2 = iVar2 + 1;
    piVar1 = piVar1 + 4;
  } while (iVar2 < 2);
  iVar4 = iVar4 * 0x10;
  *(int *)(iVar4 + 0x110 + param_1) = *(int *)(iVar4 + 0x114 + param_1) + 1;
  *(undefined4 *)(iVar4 + 0x108 + param_1) = param_2;
  *(undefined4 *)(iVar4 + 0x10c + param_1) = param_3;
  return;
}

/* CharacterSelectScreenKey @ 0x08089ec0, 867 bytes */
int CharacterSelectScreenKey(uint param_1,int param_2,int *param_3,int *param_4,int param_5)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_20;
  
  local_20 = -1;
  if (param_2 != param_5) {
    return -1;
  }
  if (g[0x14b5] == 0) {
    return -1;
  }
  if ((param_1 & 8) != 0) {
    iVar2 = *param_3;
    iVar4 = cellCols;
    iVar5 = iVar2;
    do {
      if (cellHead[(*param_4 * cellCols + iVar2) * 0x80e] != -1) {
        iVar5 = iVar2;
      }
      iVar2 = iVar2 + -1;
      if (iVar2 < 0) {
        iVar2 = iVar5;
        if (*(int *)(slct + 0x1024) == 0) goto LAB_08089f98;
        iVar2 = cellCols + -1;
      }
      if (((cellHead[(*param_4 * cellCols + iVar2) * 0x80e] != -1) || (*(int *)(slct + 0x102c) != 0)
          ) || (iVar4 = iVar4 + -1, iVar4 == 0)) goto LAB_08089f98;
    } while( true );
  }
LAB_08089f9e:
  if ((param_1 & 2) != 0) {
    iVar2 = *param_3;
    iVar4 = cellCols;
    iVar5 = iVar2;
    do {
      if (cellHead[(*param_4 * cellCols + iVar2) * 0x80e] != -1) {
        iVar5 = iVar2;
      }
      iVar2 = iVar2 + 1;
    } while (((iVar2 < cellCols) || (iVar2 = 0, iVar3 = iVar5, *(int *)(slct + 0x1024) != 0)) &&
            ((iVar3 = iVar2, cellHead[(*param_4 * cellCols + iVar2) * 0x80e] == -1 &&
             ((*(int *)(slct + 0x102c) == 0 && (iVar4 = iVar4 + -1, iVar4 != 0))))));
    *param_3 = iVar3;
  }
  if ((param_1 & 1) != 0) {
    iVar2 = *param_4;
    iVar4 = cellRows;
    iVar5 = iVar2;
    do {
      if (cellHead[(iVar2 * cellCols + *param_3) * 0x80e] != -1) {
        iVar5 = iVar2;
      }
      iVar2 = iVar2 + -1;
      if (iVar2 < 0) {
        iVar2 = iVar5;
        if (*(int *)(slct + 0x1024) == 0) goto LAB_0808a0e0;
        iVar2 = cellRows + -1;
      }
      if (((cellHead[(iVar2 * cellCols + *param_3) * 0x80e] != -1) || (*(int *)(slct + 0x102c) != 0)
          ) || (iVar4 = iVar4 + -1, iVar4 == 0)) goto LAB_0808a0e0;
    } while( true );
  }
LAB_0808a0e6:
  if ((param_1 & 4) != 0) {
    iVar2 = *param_4;
    iVar4 = cellRows;
    iVar5 = iVar2;
    do {
      if (cellHead[(iVar2 * cellCols + *param_3) * 0x80e] != -1) {
        iVar5 = iVar2;
      }
      iVar2 = iVar2 + 1;
    } while (((iVar2 < cellRows) || (iVar2 = 0, iVar3 = iVar5, *(int *)(slct + 0x1024) != 0)) &&
            ((iVar3 = iVar2, cellHead[(iVar2 * cellCols + *param_3) * 0x80e] == -1 &&
             ((*(int *)(slct + 0x102c) == 0 && (iVar4 = iVar4 + -1, iVar4 != 0))))));
    *param_4 = iVar3;
  }
  if (cellHead[(cellCols * *param_4 + *param_3) * 0x80e] != -1) {
    iVar2 = 0;
    do {
      if ((param_1 & 0x10 << ((byte)iVar2 & 0x1f)) != 0) {
        local_20 = iVar2;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 < 6);
  }
  uVar1 = KBToUInp(g[param_5 * 0xd + 0x7346]);
  if ((uinpflag[uVar1] != 0) && (local_20 != -1)) {
    local_20 = local_20 + 6;
  }
  return local_20;
LAB_08089f98:
  *param_3 = iVar2;
  goto LAB_08089f9e;
LAB_0808a0e0:
  *param_4 = iVar2;
  goto LAB_0808a0e6;
}

/* CharacterSelectStageKey @ 0x0808a230, 104 bytes */
bool CharacterSelectStageKey(uint param_1,int param_2,uint *param_3,int param_4)

{
  uint uVar1;
  bool bVar2;
  
  uVar1 = *param_3;
  if (param_2 == param_4) {
    if (((param_1 & 8) != 0) && (uVar1 = uVar1 - 1, (int)uVar1 < -1)) {
      uVar1 = g[0x33ad] - 1;
    }
    if ((param_1 & 2) != 0) {
      uVar1 = uVar1 + 1 | ((int)(uVar1 + 1) < g[0x33ad]) - 1;
    }
    bVar2 = (param_1 & 0x7f0) != 0;
    *param_3 = uVar1;
  }
  else {
    bVar2 = false;
  }
  return bVar2;
}

/* CharacterSelectMenuKey @ 0x0808a2a0, 256 bytes
 * FIXUP: frame emulation: 2 stack locals placed at their original offsets in a 0x20-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 CharacterSelectMenuKey(uint param_1,undefined4 param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  unsigned char ghidra_frame[0x20] __attribute__((aligned(16)));
#define local_18 (*(uint *)(ghidra_frame + 0x8))
#define local_14 (*(uint *)(ghidra_frame + 0xc))
  
  local_18 = 2;
  local_14 = 8;
  if (param_4 == -1) {
    IntSwap(&local_18,&local_14);
  }
  if (((param_1 & 1) != 0) &&
     (iVar2 = *(int *)(param_3 + 0xc) + -1, *(int *)(param_3 + 0xc) = iVar2, iVar2 < 0)) {
    if (*(int *)(slct + 0x13f4) == 0) {
      *(undefined4 *)(param_3 + 0xc) = 0;
    }
    else {
      *(int *)(param_3 + 0xc) = *(int *)(param_3 + 0x10) + -1;
    }
  }
  if ((param_1 & 4) != 0) {
    iVar2 = *(int *)(param_3 + 0xc) + 1;
    *(int *)(param_3 + 0xc) = iVar2;
    if (*(int *)(param_3 + 0x10) <= iVar2) {
      if (*(int *)(slct + 0x13f4) == 0) {
        *(int *)(param_3 + 0xc) = *(int *)(param_3 + 0x10) + -1;
      }
      else {
        *(undefined4 *)(param_3 + 0xc) = 0;
      }
    }
  }
  iVar2 = param_3 + *(int *)(param_3 + 0xc) * 0x14;
  if (*(int *)(iVar2 + 0x20) < *(int *)(iVar2 + 0x24)) {
    if (((param_1 & local_18) != 0) && (*(int *)(iVar2 + 0x1c) < *(int *)(iVar2 + 0x24))) {
      *(int *)(iVar2 + 0x1c) = *(int *)(iVar2 + 0x1c) + 1;
    }
    if (((param_1 & local_14) != 0) &&
       (iVar1 = *(int *)(iVar2 + 0x1c), *(int *)(iVar2 + 0x20) < iVar1)) {
      *(int *)(iVar2 + 0x1c) = iVar1 + -1;
    }
  }
  if ((param_1 & 0x7f0) == 0) {
    uVar3 = 0xffffffff;
  }
  else {
    uVar3 = *(undefined4 *)(param_3 + 0xc);
  }
  return uVar3;
}
#undef local_18
#undef local_14

/* CharselResetCursor @ 0x0808a3a0, 62 bytes */
void CharselResetCursor(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar2 = slct;
  do {
    puVar1 = (undefined4 *)(iVar2 + 0x1070);
    iVar3 = 3;
    do {
      puVar1[-8] = 0xffffffff;
      *puVar1 = 0xffffffff;
      puVar1 = puVar1 + 1;
      iVar3 = iVar3 + -1;
    } while (-1 < iVar3);
    iVar4 = iVar4 + 1;
    iVar2 = iVar2 + 0x10;
  } while (iVar4 < 2);
  return;
}

/* CharselSaveCursor @ 0x0808a3e0, 45 bytes */
void CharselSaveCursor(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,
                      int param_5)

{
  int iVar1;
  int iVar2;
  
  iVar1 = slct;
  iVar2 = (param_5 * 4 + param_4) * 4;
  *(undefined4 *)(slct + 0x1070 + iVar2) = param_2;
  *(undefined4 *)(iVar1 + 0x1050 + iVar2) = param_3;
  return;
}

/* CharselRestoreCursor @ 0x0808a410, 173 bytes */
void CharselRestoreCursor(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int local_20;
  int local_14;
  
  iVar1 = slct;
  iVar5 = 0x20;
  local_20 = 0x30;
  local_14 = 0;
  iVar2 = param_3 * 0x74 + param_1;
  iVar4 = param_2 * 0x10 + 0x1050;
  piVar3 = (int *)(slct + 0x1070 + param_2 * 0x10);
  do {
    if (*piVar3 != -1) {
      *(int *)(iVar5 + iVar2 + 0x38a0) = *piVar3;
    }
    if (*(int *)(iVar4 + iVar1) != -1) {
      *(int *)(local_20 + iVar2 + 0x3894) = *(int *)(iVar4 + iVar1);
    }
    local_14 = local_14 + 1;
    local_20 = local_20 + 0x14;
    iVar5 = iVar5 + 0x14;
    iVar4 = iVar4 + 4;
    piVar3 = piVar3 + 1;
  } while (local_14 < 4);
  return;
}

/* CharselResetMenuPos @ 0x0808a4c0, 31 bytes */
void CharselResetMenuPos(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 1;
  puVar1 = (undefined4 *)(slct + 0x16d4);
  do {
    *puVar1 = 0xffffffff;
    puVar1 = puVar1 + 0xb9;
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  return;
}

/* CharselSaveMenuPos @ 0x0808a4e0, 55 bytes */
void CharselSaveMenuPos(int param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  
  iVar1 = param_3 * 0xb4 + param_1;
  *param_2 = *(undefined4 *)(iVar1 + 0x3ab0);
  param_2[1] = *(undefined4 *)(iVar1 + 0x3ac0 + *(int *)(iVar1 + 0x3ab0) * 0x14);
  return;
}

/* CharselRestoreMenuPos @ 0x0808a520, 59 bytes */
void CharselRestoreMenuPos(int param_1,int *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_3 * 0xb4 + param_1;
  iVar1 = *param_2;
  if (iVar1 != -1) {
    *(int *)(iVar2 + 0x3ab0) = iVar1;
    *(int *)(iVar2 + 0x3ac0 + iVar1 * 0x14) = param_2[1];
  }
  return;
}

/* CharselReadConfig @ 0x0808a560, 2576 bytes
 * REVIEW: pid-unaff_
 * FIXUP: frame emulation: 3 stack locals placed at their original offsets in a 0x130-byte frame (a local's address escapes, see apply_frame_emulation) */
bool CharselReadConfig(int param_1)

{
  int *piVar1;
  int iVar2;
  void *pvVar3;
  uint *puVar4;
  int iVar5;
  undefined4 extraout_ECX;
  int unaff_EBX;
  int iVar6;
  int iVar7;
  unsigned char ghidra_frame[0x130] __attribute__((aligned(16)));
#define local_124 (*(int *)(ghidra_frame + 0xc))
#define local_120 (*(int *)(ghidra_frame + 0x10))
#define local_11c (*(char (*)[268])(ghidra_frame + 0x14))
  
  piVar1 = g;
  slct = (int)(g + 0x14e0);
  puVar4 = (uint *)(g + 0x18e0);
  g[0x18ed] = 0x3f800000;
  piVar1[0x18ec] = 0x3f800000;
  piVar1[0x1953] = 4;
  TPGetValueInt(param_1,"fadein.time",puVar4);
  TPGetValueInt(param_1,"fadeout.time",(uint *)(slct + 0x1004));
  iVar5 = slct;
  if (*(int *)(slct + 0x1000) < 1) {
    *(undefined4 *)(slct + 0x1000) = 1;
  }
  if (*(int *)(iVar5 + 0x1004) < 1) {
    *(undefined4 *)(iVar5 + 0x1004) = 1;
    iVar5 = slct;
  }
  TPGetValueInt(param_1,"rows",(uint *)(iVar5 + 0x1010));
  TPGetValueInt(param_1,"columns",(uint *)(slct + 0x1014));
  TPGetValueInt(param_1,"wrapping",(uint *)(slct + 0x1024));
  TPScanf(param_1,"pos","%i,%i",slct + 0x1008,slct + 0x100c);
  TPGetValueInt(param_1,"showemptyboxes",(uint *)(slct + 0x1028));
  TPGetValueInt(param_1,"moveoveremptyboxes",(uint *)(slct + 0x102c));
  TPScanf(param_1,"p1.cursor.startcell","%i,%i",slct + 0x1040,slct + 0x1048);
  TPScanf(param_1,"p2.cursor.startcell","%i,%i",slct + 0x1044,slct + 0x104c);
  TPGetValueInt(param_1,"p2.cursor.blink",(uint *)(slct + 0x1090));
  TPScanf(param_1,"cell.size","%i,%i",slct + 0x101c,slct + 0x1020);
  TPGetValueInt(param_1,"cell.spacing",(uint *)(slct + 0x1018));
  TPScanf(param_1,"portrait.scale","%f,%f",slct + 0x1030,slct + 0x1034);
  TPScanf(param_1,"portrait.offset","%i,%i",slct + 0x1038,slct + 0x103c);
  TPScanf(param_1,"title.offset","%i,%i",slct + 0x10e0,slct + 0x10e4);
  TPScanf(param_1,"title.font","%i,%i,%i",slct + 0x10e8,slct + 0x10ec,slct + 0x10f0);
  ParseSndGI(param_1,"p1.cursor.move.snd",(undefined4 *)(slct + 0x1094),slct + 0x109c);
  ParseSndGI(param_1,"p2.cursor.move.snd",(undefined4 *)(slct + 0x1098),slct + 0x10a0);
  ParseSndGI(param_1,"p1.cursor.done.snd",(undefined4 *)(slct + 0x10a4),slct + 0x10ac);
  ParseSndGI(param_1,"p2.cursor.done.snd",(undefined4 *)(slct + 0x10a8),slct + 0x10b0);
  ParseSndGI(param_1,"p1.random.move.snd",(undefined4 *)(slct + 0x10b4),slct + 0x10bc);
  ParseSndGI(param_1,"p2.random.move.snd",(undefined4 *)(slct + 0x10b8),slct + 0x10c0);
  TPGetValueInt(param_1,"random.move.snd.cancel",(uint *)(slct + 0x10c4));
  ParseSndGI(param_1,"stage.move.snd",(undefined4 *)(slct + 0x10c8),slct + 0x10cc);
  ParseSndGI(param_1,"stage.done.snd",(undefined4 *)(slct + 0x10d0),slct + 0x10d4);
  ParseSndGI(param_1,"cancel.snd",(undefined4 *)(slct + 0x10d8),slct + 0x10dc);
  SysExplodParse(param_1,(int *)(slct + 0x10f4),"cell.bg");
  SysExplodParse(param_1,(int *)(slct + 0x1160),"cell.random");
  TPGetValueInt(param_1,"cell.random.switchtime",(uint *)(slct + 0x11cc));
  if (*(int *)(slct + 0x11cc) < 1) {
    *(undefined4 *)(slct + 0x11cc) = 1;
  }
  iVar5 = 0;
  iVar6 = 0;
  do {
    iVar5 = iVar5 + 1;
    sprintf(local_11c,"p%i.cursor.active",iVar5,unaff_EBX);
    SysExplodParse(param_1,(int *)(iVar6 + slct + 0x11d0),local_11c);
    sprintf(local_11c,"p%i.cursor.done",iVar5);
    SysExplodParse(param_1,(int *)(iVar6 + slct + 0x12a8),local_11c);
    unaff_EBX = iVar5;
    iVar6 = iVar6 + 0x6c;
  } while (iVar5 < 2);
  iVar5 = 0;
  local_120 = 0x13a0;
  local_124 = 0x13b0;
  iVar6 = 0;
  do {
    iVar7 = slct;
    *(undefined4 *)(local_124 + 8 + slct) = 0xffffffff;
    *(undefined4 *)(local_124 + 4 + iVar7) = 0x3f800000;
    *(undefined4 *)(local_120 + 0x10 + iVar7) = 0x3f800000;
    *(uint *)(local_120 + 0xc + iVar7) = (uint)(iVar5 == 0) * 2 + -1;
    iVar5 = iVar5 + 1;
    sprintf(local_11c,"p%i.face.offset",iVar5,local_120);
    TPScanf(param_1,local_11c,"%i,%i",iVar6 + slct + 0x13a4,iVar6 + slct + 0x13a8);
    sprintf(local_11c,"p%i.face.scale",iVar5);
    TPScanf(param_1,local_11c,"%f,%f",iVar6 + slct + 0x13b0,iVar6 + slct + 0x13b4);
    sprintf(local_11c,"p%i.face.facing",iVar5);
    TPScanf(param_1,local_11c,"%i",iVar6 + slct + 0x13ac);
    sprintf(local_11c,"p%i.name.offset",iVar5);
    TPScanf(param_1,local_11c,"%i,%i",iVar6 + slct + 0x13c4,iVar6 + slct + 0x13c8);
    sprintf(local_11c,"p%i.name.font",iVar5);
    iVar2 = iVar6 + slct;
    iVar6 = iVar6 + 0x28;
    iVar7 = iVar2 + 0x13c0;
    TPScanf(param_1,local_11c,"%i,%i,%i",iVar2 + 0x13b8,iVar2 + 0x13bc,iVar7);
    local_120 = local_120 + 0x28;
    local_124 = local_124 + 0x28;
  } while (iVar5 < 2);
  iVar2 = 0;
  TPScanf(param_1,"stage.pos","%i,%i",slct + 0x1380,slct + 0x1384,iVar7);
  TPScanf(param_1,"stage.active.font","%i,%i,%i",slct + 5000,slct + 0x1394,slct + 0x13a0);
  TPScanf(param_1,"stage.active2.font","%i,%i",slct + 0x138c,slct + 0x1398);
  TPScanf(param_1,"stage.done.font","%i,%i",slct + 0x1390,slct + 0x139c);
  TPGetValueInt(param_1,"teammenu.move.wrapping",(uint *)(slct + 0x13f4));
  iVar6 = 0;
  do {
    iVar6 = iVar6 + 1;
    sprintf(local_11c,"p%i.teammenu.pos",iVar6,iVar5);
    TPScanf(param_1,local_11c,"%i,%i",iVar2 + slct + 0x13f8,iVar2 + slct + 0x13fc);
    sprintf(local_11c,"p%i.teammenu.bg",iVar6);
    SysExplodParse(param_1,(int *)(iVar2 + slct + 0x1400),local_11c);
    sprintf(local_11c,"p%i.teammenu.selftitle",iVar6);
    SysExplodParse(param_1,(int *)(iVar2 + slct + 0x146c),local_11c);
    sprintf(local_11c,"p%i.teammenu.enemytitle",iVar6);
    SysExplodParse(param_1,(int *)(iVar2 + slct + 0x14d8),local_11c);
    sprintf(local_11c,"p%i.teammenu.move.snd",iVar6);
    ParseSndGI(param_1,local_11c,(undefined4 *)(iVar2 + slct + 0x1544),iVar2 + slct + 0x1548);
    sprintf(local_11c,"p%i.teammenu.value.snd",iVar6);
    ParseSndGI(param_1,local_11c,(undefined4 *)(iVar2 + slct + 0x154c),iVar2 + slct + 0x1550);
    sprintf(local_11c,"p%i.teammenu.done.snd",iVar6);
    ParseSndGI(param_1,local_11c,(undefined4 *)(iVar2 + slct + 0x1554),iVar2 + slct + 0x1558);
    sprintf(local_11c,"p%i.teammenu.item.font",iVar6);
    iVar5 = iVar2 + slct;
    TPScanf(param_1,local_11c,"%i,%i,%i",iVar5 + 0x1564,iVar5 + 0x1570,iVar5 + 0x157c);
    sprintf(local_11c,"p%i.teammenu.item.active.font",iVar6);
    TPScanf(param_1,local_11c,"%i,%i",iVar2 + slct + 0x1568,iVar2 + slct + 0x1574);
    sprintf(local_11c,"p%i.teammenu.item.active2.font",iVar6);
    TPScanf(param_1,local_11c,"%i,%i",iVar2 + slct + 0x156c,iVar2 + slct + 0x1578);
    sprintf(local_11c,"p%i.teammenu.item.offset",iVar6);
    TPScanf(param_1,local_11c,"%i,%i",iVar2 + slct + 0x155c,iVar2 + slct + 0x1560);
    sprintf(local_11c,"p%i.teammenu.item.spacing",iVar6);
    TPScanf(param_1,local_11c,"%i,%i",iVar2 + slct + 0x1580,iVar2 + slct + 0x1584);
    sprintf(local_11c,"p%i.teammenu.item.cursor",iVar6);
    SysExplodParse(param_1,(int *)(iVar2 + slct + 0x1588),local_11c);
    sprintf(local_11c,"p%i.teammenu.value.icon",iVar6);
    SysExplodParse(param_1,(int *)(iVar2 + slct + 0x15f4),local_11c);
    sprintf(local_11c,"p%i.teammenu.value.empty.icon",iVar6);
    SysExplodParse(param_1,(int *)(iVar2 + slct + 0x1668),local_11c);
    sprintf(local_11c,"p%i.teammenu.value.spacing",iVar6);
    iVar5 = iVar2 + slct;
    iVar2 = iVar2 + 0x2e4;
    TPScanf(param_1,local_11c,"%i,%i",iVar5 + 0x1660,iVar5 + 0x1664);
    iVar5 = iVar6;
  } while (iVar6 < 2);
  pvVar3 = calloc(*(int *)(slct + 0x1014) * *(int *)(slct + 0x1010),0x2038);
  *(void **)(slct + 0x19c0) = pvVar3;
  if (pvVar3 == (void *)0x0) {
    sprintf((char *)(g + 0x81d2),"Out of memory",extraout_ECX,extraout_ECX);
  }
  return pvVar3 != (void *)0x0;
}
#undef local_124
#undef local_120
#undef local_11c

/* VersusScreen @ 0x0808af70, 2673 bytes
 * FIXUP: 3 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: 3 integer-to-float conversions made exact (float10, as x87 fild) (apply_int2float_exact)
 * FIXUP: frame emulation: 22 stack locals placed at their original offsets in a 0xf0-byte frame (a local's address escapes, see apply_frame_emulation)
 * FIXUP: 1 x87 register temporaries (fVar/dVar) declared float10 (80-bit) instead of float/double */
uint VersusScreen(void)

{
  bool bVar1;
  int *piVar2;
  uint uVar3;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  int *piVar8;
  uint uVar9;
  int iVar10;
  int *piVar11;
  int *piVar12;
  int *piVar13;
  int iVar14;
  bool bVar15;
  float10 fVar16;
  unsigned char ghidra_frame[0xf0] __attribute__((aligned(16)));
#define iStack_f0 (*(int *)(ghidra_frame + 0x0))
#define local_d4 (*(int **)(ghidra_frame + 0x1c))
#define local_d0 (*(undefined1 **)(ghidra_frame + 0x20))
#define local_bc (*(int *)(ghidra_frame + 0x34))
#define local_b8 (*(int *)(ghidra_frame + 0x38))
#define local_b4 (*(int *)(ghidra_frame + 0x3c))
#define local_b0 (*(int *)(ghidra_frame + 0x40))
#define local_ac (*(int *)(ghidra_frame + 0x44))
#define local_a8 (*(int *)(ghidra_frame + 0x48))
#define local_a4 (*(int *)(ghidra_frame + 0x4c))
#define iStack_a0 (*(int *)(ghidra_frame + 0x50))
#define local_74 (*(int *)(ghidra_frame + 0x7c))
#define local_70 (*(int *)(ghidra_frame + 0x80))
#define local_6c (*(int *)(ghidra_frame + 0x84))
#define local_68 (*(int *)(ghidra_frame + 0x88))
#define local_60 (*(uint *)(ghidra_frame + 0x90))
#define local_58 (*(int *)(ghidra_frame + 0x98))
#define local_54 (*(uint (*)[2])(ghidra_frame + 0x9c))
#define local_4c (*(uint *)(ghidra_frame + 0xa4))
#define local_48 (*(uint *)(ghidra_frame + 0xa8))
#define local_44 (*(int (*)[10])(ghidra_frame + 0xac))
#define local_1c (*(undefined1 (*)[12])(ghidra_frame + 0xd4))
  
  piVar2 = g;
  bVar1 = false;
  local_60 = 0;
  piVar12 = local_44 + 2;
  for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar12 = 0;
    piVar12 = piVar12 + 1;
  }
  local_6c = 0;
  piVar12 = g + 0x3395;
  local_70 = -1;
  if (g[0x14d0] != 0) {
    local_58 = 0;
    do {
      iVar5 = local_58 + 1;
      PrecacheRequestTeam((int)(g + local_58 * 0x6a7 + 0x33bb));
      bVar15 = local_58 == 0;
      local_58 = iVar5;
    } while (bVar15 || iVar5 < 1);
    PrecacheStart();
  }
  iVar5 = 0;
  do {
    local_44[iVar5] = (int)(g + iVar5 * 0xd + 0x733b);
    iVar5 = iVar5 + 1;
  } while (iVar5 < 2);
  TimerSetSyncFPS(0x3c);
  KBBufferClear();
  PadPoll();
  PadBufClear();
  UInpRefreshFlags();
  UInpBufClear();
  V_SetBuf((int *)g[0x4136],0);
  W_Cls(0);
  BGArrayReset(g[0x62cd]);
  iVar5 = BGMLoadAndStart(g + 0x6efa,(byte *)(g + 0x66d2),g[0x6ad2],0);
  if (iVar5 == 0) {
    ErrorExit();
  }
  piVar8 = cellHead;
  piVar7 = g;
  local_d0 = local_1c;
  local_d4 = g + 0x33bf;
  local_58 = 0;
  piVar13 = g + 0x33bb;
  do {
    iVar5 = 0;
    if (0 < piVar13[2]) {
      piVar11 = (int *)(local_d0 + -0x20);
      iVar10 = 0;
      do {
        if (*(int *)(iVar10 + (int)local_d4) == -1) {
          *piVar11 = 0;
        }
        else {
          *piVar11 = (int)(piVar8 + *(int *)(piVar7[0x14b4] + 0x500c +
                                            *(int *)(iVar10 + (int)local_d4) * 0x702c) * 0x80e);
        }
        iVar5 = iVar5 + 1;
        piVar11 = piVar11 + 1;
        iVar10 = iVar10 + 0x14;
      } while (iVar5 < piVar13[2]);
    }
    local_58 = local_58 + 1;
    local_d4 = local_d4 + 0x6a7;
    local_d0 = local_d0 + 0xc;
    piVar13 = piVar13 + 0x6a7;
  } while (local_58 < 2);
  FrameSkipReset();
  local_68 = 0;
  local_74 = *piVar12;
  do {
    iVar5 = 0;
    BGMPoll(g + 0x6efa);
    local_4c = 0;
    local_48 = 0;
    PadPoll();
    KBPoll();
    bVar15 = KBkbhit();
    if (GHIDRA_ZEXT8(bVar15) != 0) {
      local_4c = KBgetchraw();
    }
    bVar15 = PadHit();
    if (GHIDRA_ZEXT8(bVar15) != 0) {
      local_48 = PadGet();
    }
    GlobalInputUpdate();
    bVar15 = UInpHit();
    if (GHIDRA_ZEXT8(bVar15) != 0) {
      iVar5 = UInpGet();
    }
    KBIMenuGetKey(local_54,iVar5,(int)local_44,2);
    uVar3 = local_54[0];
    PRSprArrayClear((int *)g[0x413d]);
    BGArrayMove((int *)g[0x62cd],0.0,0.0);
    BGArrayUpdate(g[0x62cd]);
    if (bVar1) {
      FrameSkipReset();
    }
    iVar5 = piVar2[0x3396];
    if ((0 < iVar5) && (local_6c == 0)) {
      iVar5 = (local_68 << 8) / iVar5;
      MasterPalMul(iVar5,iVar5,iVar5);
      iVar5 = piVar2[0x3396];
    }
    if (local_68 == iVar5) {
      local_6c = 1;
    }
    if (local_6c == 1) {
      if (local_70 == -1) {
        iVar5 = piVar2[0x3397];
        if (local_68 == *piVar12 - iVar5) {
          local_6c = 2;
          local_70 = local_68;
        }
      }
      else {
        iVar5 = piVar2[0x3397];
      }
    }
    else {
      iVar5 = piVar2[0x3397];
    }
    if ((0 < iVar5) && (local_6c == 2)) {
      uVar9 = 0x100 - ((local_68 - local_70) * 0x100) / iVar5;
      uVar9 = uVar9 & 0xffffffffU - ((int)uVar9 >> 0x1f);
      MasterPalMul(uVar9,uVar9,uVar9);
    }
    if (g[0x7306] == 0) {
      iVar10 = 0x20;
      MasterPalProcessChanges();
      iVar14 = 0;
      iVar5 = 0;
      BGArrayDrawLayer(g[0x62cd],0);
      local_b8 = 0x10;
      local_bc = 0x10;
      local_58 = 1;
      piVar7 = g;
      do {
        iVar4 = *(int *)(iVar5 + 0xcef4 + (int)piVar7);
        if (iVar4 == 1) {
          iVar4 = *(int *)((int)local_44 + iVar14 + 8);
          if (((iVar4 != 0) && (*(int *)(iVar4 + 0x2034) != 0)) &&
             (iVar4 = SpriteArrayGetNum(*(int **)(iVar4 + 0x2034),9000,1), piVar7 = g, iVar4 != -1))
          {
            fVar16 = *(float *)((int)piVar2 + iVar10 + 0xce64);
            iVar6 = local_bc;
            goto LAB_0808b4e4;
          }
        }
        else if (((iVar4 == 2) && (iVar4 = *(int *)((int)local_44 + iVar14 + 8), iVar4 != 0)) &&
                ((*(int *)(iVar4 + 0x2034) != 0 &&
                 (iVar4 = SpriteArrayGetNum(*(int **)(iVar4 + 0x2034),9000,1), piVar7 = g,
                 iVar4 != -1)))) {
          fVar16 = *(float *)((int)piVar2 + iVar10 + 0xce64);
          iVar6 = local_b8;
LAB_0808b4e4:
          W_ScaleSprite_S(*(int **)(*(int *)((int)local_44 + iVar14 + 8) + 0x2034),iVar4,
                          (float10)*(int *)((int)piVar2 + iVar10 + 0xce40),
                          (float10)*(int *)((int)piVar2 + iVar10 + 0xce44),
                          (float10)*(int *)(iVar6 + 0x18 + (int)piVar12) *
                          *(float *)((int)piVar2 + iVar10 + 0xce60),fVar16);
          piVar7 = g;
        }
        local_b8 = local_b8 + 0x28;
        local_bc = local_bc + 0x28;
        iVar10 = iVar10 + 0x28;
        iVar14 = iVar14 + 0xc;
        iVar5 = iVar5 + 0x1a9c;
        local_58 = local_58 + -1;
      } while (-1 < local_58);
      local_58 = 0;
      local_a4 = 0x10;
      local_a8 = 0;
      local_ac = 0;
      local_b0 = 0;
      local_b4 = 0;
      do {
        iVar5 = *(int *)((int)piVar7 + local_b0 + 0xcef4);
        piVar8 = piVar7;
        if (iVar5 == 1) {
          iVar5 = *(int *)((int)piVar2 + local_a8 + 0xce68);
          if ((iVar5 != -1) && (iVar10 = *(int *)((int)local_44 + local_ac + 8), iVar10 != 0)) {
            V_FontDrawAlignBank((char *)(iVar10 + 4),(int *)piVar7[iVar5 + 0x62c3],
                                *(int *)(local_a4 + 0x10 + (int)piVar12),
                                *(int *)((int)piVar2 + local_a4 + 0xce68),
                                *(int *)(local_a4 + 0xc + (int)piVar12),
                                *(int *)(local_a8 + 0x18 + (int)piVar12));
            piVar8 = g;
          }
        }
        else if (iVar5 == 2) {
          iVar10 = local_b4 << 2;
          iVar5 = 0;
          iStack_a0 = 0;
          iStack_f0 = 2;
          do {
            iVar14 = *(int *)((int)piVar2 + local_a8 + 0xce68);
            if ((iVar14 != -1) && (iVar4 = *(int *)((int)local_44 + iVar10 + 8), iVar4 != 0)) {
              V_FontDrawAlignBank((char *)(iVar4 + 4),(int *)piVar8[iVar14 + 0x62c3],
                                  *(int *)(local_a4 + 0x10 + (int)piVar12),
                                  iStack_a0 + *(int *)((int)piVar2 + local_a4 + 0xce68),
                                  *(int *)(local_a4 + 0xc + (int)piVar12),
                                  *(int *)(local_a8 + 0x18 + (int)piVar12));
              iStack_f0 = *(int *)((int)piVar7 + local_b0 + 0xcef4);
              piVar8 = g;
            }
            iVar5 = iVar5 + 1;
            iStack_a0 = iStack_a0 + 0xe;
            iVar10 = iVar10 + 4;
          } while (iVar5 < iStack_f0);
        }
        local_58 = local_58 + 1;
        local_a4 = local_a4 + 0x28;
        local_a8 = local_a8 + 0x28;
        local_ac = local_ac + 0xc;
        local_b0 = local_b0 + 0x1a9c;
        local_b4 = local_b4 + 3;
        piVar7 = piVar8;
      } while (local_58 < 2);
      BGArrayDrawLayer(piVar8[0x62cd],1);
    }
    if ((g[0x81cd] != 0) && ((g[0x74e8] == 0 || (g[0x74f0] != 0)))) {
      uVar9 = makecol(0xff,0xff,0xff);
      FontDrawClipboard((int *)g[0x81d1],(int *)g[0x413a],10,0x32,uVar9);
    }
    if (local_4c == 0x58) {
      ScreenSnap();
    }
    if (g[0x82d2] == 0) {
      TimerWaitSync();
    }
    if ((g[0x7306] == 0) && (g[0x4143] != 0)) {
      VRetrace();
    }
    DrawToScreen();
    if (g[0x7307] == 0) {
      MasterPalFinishedDraw();
    }
    FrameSkipUpdate();
    local_68 = local_68 + 1;
    if (bVar1) {
      FrameSkipReset();
      BGMFree(g + 0x6efa);
      KBBufferClear();
      PadPoll();
      PadBufClear();
      UInpRefreshFlags();
      UInpBufClear();
      PrecacheFinish();
      MasterPalReset();
      return local_60 ^ 1;
    }
    if (local_74 < local_68) {
      bVar1 = true;
    }
    if (((uVar3 & 0xff0) != 0) && (local_6c == 1)) {
      local_6c = 2;
      local_74 = local_68 + piVar2[0x3397];
      local_70 = local_68;
    }
    if ((local_4c == 1) && (local_60 == 0)) {
      local_60 = 1;
      bVar1 = true;
      PrecacheRequestCancel();
    }
    if (((g[0x74e8] != 0) && (local_60 == 0)) &&
       (((local_4c != 0 && ((local_4c & 0x100) == 0)) ||
        ((local_48 != 0 && ((local_48 & 0x100) == 0)))))) {
      local_60 = 1;
      bVar1 = true;
      PrecacheRequestCancel();
    }
  } while( true );
}
#undef iStack_f0
#undef local_d4
#undef local_d0
#undef local_bc
#undef local_b8
#undef local_b4
#undef local_b0
#undef local_ac
#undef local_a8
#undef local_a4
#undef iStack_a0
#undef local_74
#undef local_70
#undef local_6c
#undef local_68
#undef local_60
#undef local_58
#undef local_54
#undef local_4c
#undef local_48
#undef local_44
#undef local_1c

/* ArcadeListBuild @ 0x0808b9f0, 107 bytes */
undefined4 ArcadeListBuild(void)

{
  undefined4 extraout_EAX;
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = 2 - g[0x33b3];
  uVar1 = 0;
  if (g[0x33b3] != 0) {
    piVar3 = g + 0x14bc;
    if ((g[iVar2 * 0x6a7 + 0x33bb] != 0) || (1 < g[iVar2 * 0x6a7 + 0x33b9])) {
      piVar3 = g + 0x14c6;
    }
    ArcadeListBuildSet(g + 0x14b8,g[iVar2 * 0x6a7 + 0x33ba],(int)piVar3);
    uVar1 = extraout_EAX;
  }
  return uVar1;
}

/* ArcadeListBuildSet @ 0x0808ba60, 796 bytes */
void ArcadeListBuildSet(int *param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  bool bVar3;
  int *piVar4;
  void *__ptr;
  long lVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int local_2c;
  int local_20;
  
  iVar8 = 0;
  iVar1 = g[0x14b5];
  local_2c = 0;
  __ptr = calloc(iVar1 + 1,4);
  if (0 < iVar1) {
    do {
      *(int *)((int)__ptr + iVar8 * 4) = iVar8;
      iVar8 = iVar8 + 1;
    } while (iVar8 < iVar1);
  }
  local_20 = 4;
  do {
    iVar8 = 0;
    if (0 < iVar1) {
      do {
        lVar5 = random();
        uVar2 = *(undefined4 *)((int)__ptr + iVar8 * 4);
        *(undefined4 *)((int)__ptr + iVar8 * 4) = *(undefined4 *)((int)__ptr + (lVar5 % iVar1) * 4);
        *(undefined4 *)((int)__ptr + (lVar5 % iVar1) * 4) = uVar2;
        iVar8 = iVar8 + 1;
      } while (iVar8 < iVar1);
    }
    local_20 = local_20 + -1;
  } while (-1 < local_20);
  iVar8 = iVar1;
  if (1 < iVar1) {
    do {
      bVar3 = true;
      for (iVar9 = 0; iVar10 = iVar8 + -1, iVar9 < iVar10; iVar9 = iVar9 + 1) {
        iVar10 = *(int *)((int)__ptr + iVar9 * 4);
        iVar6 = *(int *)((int)__ptr + iVar9 * 4 + 4);
        if (*(int *)(g[0x14b4] + 0x5024 + iVar6 * 0x702c) <
            *(int *)(g[0x14b4] + 0x5024 + iVar10 * 0x702c)) {
          *(int *)((int)__ptr + iVar9 * 4) = iVar6;
          *(int *)((int)__ptr + iVar9 * 4 + 4) = iVar10;
          bVar3 = false;
        }
      }
    } while ((1 < iVar10) && (iVar8 = iVar10, !bVar3));
  }
  iVar8 = 0;
  local_20 = 0;
  while( true ) {
    piVar4 = g;
    iVar9 = iVar8;
    if (iVar8 < iVar1) {
      iVar8 = *(int *)(g[0x14b4] + 0x5024 + *(int *)((int)__ptr + iVar8 * 4) * 0x702c);
      while ((iVar8 < local_20 && (iVar9 = iVar9 + 1, iVar9 < iVar1))) {
        iVar8 = *(int *)(g[0x14b4] + 0x5024 + *(int *)((int)__ptr + iVar9 * 4) * 0x702c);
      }
    }
    if (iVar1 <= iVar9) break;
    iVar10 = 0;
    iVar8 = iVar9;
    if (0 < param_2 * *(int *)(param_3 + local_20 * 4)) {
      iVar6 = *(int *)((int)__ptr + iVar9 * 4);
      iVar7 = g[0x14b4];
      while (*(int *)(iVar7 + 0x5024 + iVar6 * 0x702c) == local_20) {
        iVar10 = iVar10 + 1;
        iVar8 = iVar8 + 1;
        *(int *)(*param_1 + local_2c * 4) = iVar6;
        local_2c = local_2c + 1;
        if ((param_2 * *(int *)(param_3 + local_20 * 4) <= iVar10) || (iVar1 <= iVar8)) break;
        iVar6 = *(int *)((int)__ptr + iVar8 * 4);
        iVar7 = piVar4[0x14b4];
      }
    }
    if ((iVar10 % param_2 != 0) && (iVar8 != iVar9)) {
      do {
        iVar10 = iVar10 + 1;
        lVar5 = random();
        *(undefined4 *)(*param_1 + local_2c * 4) =
             *(undefined4 *)((int)__ptr + (iVar9 + lVar5 % (iVar8 - iVar9)) * 4);
        local_2c = local_2c + 1;
        if (iVar10 % param_2 == 0) break;
      } while (iVar8 != iVar9);
    }
    if ((iVar1 <= iVar8) || (local_20 = local_20 + 1, 9 < local_20)) break;
  }
  *(undefined4 *)(*param_1 + local_2c * 4) = 0xffffffff;
  param_1[1] = local_2c;
  param_1[2] = 0;
  param_1[3] = 0;
  free(__ptr);
  return;
}

/* ArcadeListGetCurrent @ 0x0808bd80, 14 bytes */
int ArcadeListGetCurrent(void)

{
  int iVar1;
  
  iVar1 = ArcadeListGet(0);
  return iVar1;
}

/* ArcadeListGet @ 0x0808bd90, 480 bytes */
int ArcadeListGet(int param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  long lVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  int *local_34;
  int *local_30;
  int *local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  
  piVar2 = g;
  iVar9 = -1;
  piVar1 = g + 0x14b8;
  local_24 = g[0x14ba];
  iVar6 = 2 - g[0x33b3];
  local_20 = 0;
  if (0 < g[iVar6 * 0x6a7 + 0x33b9]) {
    local_2c = g + iVar6 * 0x6a7 + 0x33be;
    local_34 = g + iVar6 * 0x6a7 + 0x33bf;
    piVar8 = g + iVar6 * 0x6a7 + 0x33c0;
    local_30 = local_34;
    do {
      local_1c = 0;
      iVar7 = piVar8[-3];
      if (0 < iVar7) {
        local_28 = 0x10;
        iVar10 = 0;
        do {
          iVar3 = *piVar1;
          if (*(int *)(iVar3 + local_24 * 4) != -1) {
            if (*(int *)(iVar10 + (int)piVar8) != -1) {
              CharStopUsingPal((byte)*(undefined4 *)(iVar10 + (int)piVar8),
                               *(int *)(iVar10 + (int)local_34));
              iVar3 = *piVar1;
            }
            iVar9 = *(int *)(iVar3 + local_24 * 4);
            *(int *)(iVar10 + (int)local_30) = iVar9;
            if (g[0x757e] == 0) {
              *(int *)(iVar10 + (int)piVar8) = *(int *)(g[0x14b4] + 0x5014 + iVar9 * 0x702c) + -1;
            }
            else {
              lVar4 = random();
              *(int *)(iVar10 + (int)piVar8) = lVar4 % 0xc;
            }
            uVar5 = CharReservePal(*(uint *)(iVar10 + (int)piVar8),iVar9);
            *(uint *)(iVar10 + (int)piVar8) = uVar5;
            local_24 = local_24 + 1;
            *(undefined4 *)(local_28 + (int)local_2c) = 1;
            iVar7 = piVar8[-3];
          }
          local_1c = local_1c + 1;
          local_28 = local_28 + 0x14;
          iVar10 = iVar10 + 0x14;
        } while (local_1c < iVar7);
      }
      local_34 = local_34 + 0x17;
      local_20 = local_20 + 1;
      local_2c = local_2c + 0x17;
      local_30 = local_30 + 0x17;
      piVar8 = piVar8 + 0x17;
    } while (local_20 < piVar2[iVar6 * 0x6a7 + 0x33b9]);
  }
  if (param_1 != 0) {
    piVar2[0x14ba] = local_24;
  }
  return iVar9;
}

/* ArcadeListGetCurSize @ 0x0808bf70, 120 bytes */
int ArcadeListGetCurSize(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  iVar5 = 0;
  iVar3 = g[0x14ba];
  iVar1 = g[(2 - g[0x33b3]) * 0x6a7 + 0x33b9];
  if (0 < iVar1) {
    piVar4 = g + (2 - g[0x33b3]) * 0x6a7 + 0x33bd;
    do {
      iVar2 = *piVar4;
      if (0 < iVar2) {
        do {
          if (*(int *)(g[0x14b8] + iVar3 * 4) != -1) {
            iVar3 = iVar3 + 1;
            iVar5 = iVar5 + 1;
          }
          iVar2 = iVar2 + -1;
        } while (iVar2 != 0);
      }
      piVar4 = piVar4 + 0x17;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return iVar5;
}

/* ArcadeListPeekCur @ 0x0808bff0, 19 bytes */
void ArcadeListPeekCur(int param_1)

{
  ArcadeListPeek(param_1,0);
  return;
}

/* ArcadeListPeekNext @ 0x0808c010, 19 bytes */
void ArcadeListPeekNext(int param_1)

{
  ArcadeListPeek(param_1,1);
  return;
}

/* ArcadeListPeek @ 0x0808c030, 201 bytes */
int ArcadeListPeek(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int local_1c;
  
  piVar4 = g;
  iVar9 = 0;
  piVar1 = g + 0x14b8;
  iVar10 = g[0x14ba];
  iVar7 = 2 - g[0x33b3];
  if (param_2 != 0) {
    iVar5 = ArcadeListGetCurSize();
    iVar10 = iVar10 + iVar5;
  }
  if (iVar10 < piVar4[0x14b9]) {
    local_1c = 0;
    if (0 < piVar4[iVar7 * 0x6a7 + 0x33b9]) {
      piVar6 = piVar4 + iVar7 * 0x6a7 + 0x33bb;
      do {
        iVar8 = 0;
        iVar5 = piVar6[2];
        if (0 < iVar5) {
          iVar2 = *piVar1;
          do {
            iVar3 = *(int *)(iVar2 + iVar10 * 4);
            if (iVar3 != -1) {
              iVar10 = iVar10 + 1;
              *(int *)(param_1 + iVar9 * 4) = iVar3;
              iVar9 = iVar9 + 1;
              iVar5 = piVar6[2];
            }
            iVar8 = iVar8 + 1;
          } while (iVar8 < iVar5);
        }
        local_1c = local_1c + 1;
        piVar6 = piVar6 + 0x17;
      } while (local_1c < piVar4[iVar7 * 0x6a7 + 0x33b9]);
    }
  }
  else {
    iVar9 = 0;
  }
  return iVar9;
}

/* ArcadeListEnemiesLeft @ 0x0808c100, 21 bytes */
int ArcadeListEnemiesLeft(void)

{
  return g[0x14b9] - g[0x14ba];
}

/* SurvivalBuildRandomTeam @ 0x0808c120, 610 bytes */
void SurvivalBuildRandomTeam(undefined4 *param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  long lVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 *local_28;
  undefined4 *local_24;
  int local_20;
  uint local_18;
  int local_14;
  
  iVar1 = param_1[5];
  param_1[1] = 2;
  *param_1 = 0;
  param_1[2] = iVar1 * 2;
  if (param_3 == 0) {
    local_14 = 0;
    iVar5 = param_1[5];
    if (0 < iVar5) {
      iVar7 = 0;
      do {
        if (*(int *)((int)param_1 + iVar7 + 0x20) != -1) {
          CharStopUsingPal((byte)*(undefined4 *)((int)param_1 + iVar7 + 0x20),
                           *(int *)((int)param_1 + iVar7 + 0x1c));
          iVar5 = param_1[5];
        }
        iVar7 = iVar7 + 0x14;
        local_14 = local_14 + 1;
      } while (local_14 < iVar5);
    }
    puVar6 = param_1 + 0x1ef;
    puVar8 = param_1 + 0x1a;
    puVar9 = param_1 + 3;
    for (iVar5 = 0x17; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + 1;
      puVar9 = puVar9 + 1;
    }
    puVar8 = param_1 + 0x1ef;
    puVar9 = param_1 + 0x5f;
    for (iVar5 = 400; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + 1;
      puVar9 = puVar9 + 1;
    }
    local_14 = 3;
    do {
      ResetPersistVar(puVar6);
      puVar6 = puVar6 + 100;
      local_14 = local_14 + -1;
    } while (-1 < local_14);
  }
  local_18 = (uint)(param_3 == 0);
  if (local_18 == 1 || param_3 != 0) {
    local_24 = param_1 + local_18 * 0x17 + 7;
    local_28 = param_1 + local_18 * 0x17 + 9;
    puVar6 = param_1 + local_18 * 0x17 + 8;
    puVar8 = param_1 + local_18 * 0x17 + 3;
    do {
      if ((param_3 != 0) || (local_18 == 1)) {
        puVar6[5] = 0xffffffff;
        *puVar6 = 0xffffffff;
        puVar6[4] = 0xffffffff;
        puVar6[-1] = 0xffffffff;
      }
      puVar6[-5] = (uint)(iVar1 != 1);
      if (iVar1 == 2) {
        puVar6[-4] = 2;
      }
      puVar6[-3] = iVar1;
      if (0 < iVar1) {
        iVar5 = 0;
        local_20 = param_2 + 1;
        local_14 = iVar1;
        do {
          *(int *)(iVar5 + (int)local_28) = param_2;
          *(int *)((int)puVar8 + iVar5 + 0xc) = local_20;
          lVar3 = random();
          piVar2 = g;
          iVar7 = lVar3 % g[0x14b5];
          *(int *)(iVar5 + (int)local_24) = iVar7;
          if (piVar2[0x757e] == 0) {
            *(int *)((int)puVar8 + iVar5 + 0x14) =
                 *(int *)(piVar2[0x14b4] + 0x5014 + iVar7 * 0x702c) + -1;
          }
          else {
            lVar3 = random();
            *(int *)((int)puVar8 + iVar5 + 0x14) = lVar3 % 0xc;
          }
          uVar4 = CharReservePal(*(uint *)((int)puVar8 + iVar5 + 0x14),iVar7);
          *(uint *)((int)puVar8 + iVar5 + 0x14) = uVar4;
          *(undefined4 *)((int)puVar8 + iVar5 + 0x1c) = 1;
          iVar5 = iVar5 + 0x14;
          local_20 = local_20 + 2;
          local_14 = local_14 + -1;
        } while (local_14 != 0);
      }
      local_18 = local_18 + 1;
      local_24 = local_24 + 0x17;
      local_28 = local_28 + 0x17;
      puVar6 = puVar6 + 0x17;
      puVar8 = puVar8 + 0x17;
    } while ((int)local_18 < 2);
  }
  return;
}

/* GetPlayerRowCol @ 0x0808c390, 123 bytes */
undefined4 GetPlayerRowCol(int param_1,int *param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = 0;
  piVar1 = cellHead;
  if (0 < cellCols * cellRows) {
    do {
      if (param_1 == *piVar1) {
        *param_2 = iVar2 % cellCols;
        *param_3 = iVar2 / cellCols;
        return 1;
      }
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + 0x80e;
    } while (iVar2 < cellCols * cellRows);
  }
  return 0;
}

/* SlctStateListChanged @ 0x0808c410, 21 bytes */
undefined4 SlctStateListChanged(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(param_1 + 0x198);
  *(undefined4 *)(param_1 + 0x198) = 0;
  return uVar1;
}

/* SlctStateListNextItem @ 0x0808c430, 55 bytes */
int SlctStateListNextItem(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 400) <= *(int *)(param_1 + 0x194)) {
    return 0;
  }
  iVar1 = *(int *)(param_1 + 0x194) + 1;
  *(int *)(param_1 + 0x194) = iVar1;
  *(undefined4 *)(param_1 + 0x198) = 1;
  *(undefined4 *)(param_1 + 0x19c) = 0;
  return param_1 + iVar1 * 0x28;
}

/* SlctStateListUpdate @ 0x0808c470, 18 bytes */
void SlctStateListUpdate(int param_1)

{
  *(int *)(param_1 + 0x19c) = *(int *)(param_1 + 0x19c) + 1;
  return;
}

/* BuildSlctCtrl @ 0x0808c490, 410 bytes */
void BuildSlctCtrl(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  bool bVar3;
  int *piVar4;
  long lVar5;
  int iVar6;
  int iVar7;
  
  bVar3 = false;
  if ((g[0x82d6] != 0) || (g[0x74e8] != 0)) {
    bVar3 = true;
  }
  iVar1 = param_1 + param_3 * 0x74;
  *(undefined4 *)(iVar1 + 0x3890) = *(undefined4 *)(param_2 + 4);
  *(undefined4 *)(iVar1 + 0x38a4) = 0;
  uVar2 = *(undefined4 *)(param_2 + 0xc);
  *(int *)(iVar1 + 0x38b0) = param_2;
  *(undefined4 *)(iVar1 + 0x38a8) = uVar2;
  *(undefined4 *)(iVar1 + 0x38ac) = 0xffffffff;
  if (bVar3) {
    lVar5 = random();
    iVar6 = slct;
    *(int *)(iVar1 + 0x38ac) = lVar5 % 0x14 + 0x14;
    *(undefined4 *)(iVar6 + 0x11cc) = 6;
  }
  piVar4 = g;
  iVar6 = 0;
  if (0 < *(int *)(iVar1 + 0x38a8)) {
    iVar7 = 0x20;
    do {
      *(undefined4 *)(iVar1 + 0x389c + iVar7) = *(undefined4 *)(param_2 + 4);
      *(undefined4 *)(iVar1 + 0x3894 + iVar7) = *(undefined4 *)(iVar1 + 0x3890);
      *(undefined4 *)(iVar1 + 0x38a0 + iVar7) = 0xffffffff;
      *(undefined4 *)(iVar1 + 0x38a4 + iVar7) = 0xffffffff;
      if (piVar4[0x33ae] == 2) {
        *(undefined4 *)(iVar7 + iVar1 + 0x3898) = 1;
      }
      iVar6 = iVar6 + 1;
      iVar7 = iVar7 + 0x14;
    } while (iVar6 < *(int *)(iVar1 + 0x38a8));
  }
  CharselRestoreCursor(param_1,*(int *)(param_2 + 4),param_3);
  *(int *)(iVar1 + 0x3894) = *(int *)(iVar1 + 0x38c0);
  if (*(int *)(iVar1 + 0x38c0) == -1) {
    *(undefined4 *)(iVar1 + 0x3894) = *(undefined4 *)(slct + 0x1048 + *(int *)(param_2 + 4) * 4);
  }
  *(int *)(iVar1 + 0x3898) = *(int *)(iVar1 + 0x38c4);
  if (*(int *)(iVar1 + 0x38c4) == -1) {
    *(undefined4 *)(iVar1 + 0x3898) = *(undefined4 *)(slct + 0x1040 + *(int *)(param_2 + 4) * 4);
  }
  *(undefined4 *)(iVar1 + 0x389c) = *(undefined4 *)(iVar1 + 0x3894);
  *(undefined4 *)(iVar1 + 0x38a0) = *(undefined4 *)(iVar1 + 0x3898);
  if ((*(int *)(param_2 + 8) == 1) && (*(int *)(param_2 + 0xc) == 2)) {
    iVar6 = *(int *)(param_2 + 0x10);
    if ((iVar6 == 0) || (iVar6 == 2)) {
      *(undefined4 *)(iVar1 + 0x38cc) = 1;
      iVar6 = *(int *)(param_2 + 0x10);
    }
    if (iVar6 == 2) {
      *(undefined4 *)(iVar1 + 0x38b8) = 1;
      iVar6 = *(int *)(param_2 + 0x10);
    }
    if (iVar6 == 1) {
      *(int *)(iVar1 + 0x38d0) = 1 - *(int *)(iVar1 + 0x38d0);
    }
  }
  return;
}

/* BuildSlctTeamForArcade @ 0x0808c630, 146 bytes */
void BuildSlctTeamForArcade(int param_1,int param_2,int param_3,undefined4 param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 local_14;
  
  *(int *)(param_1 + 4) = param_3;
  local_14 = 0;
  if (0 < param_3) {
    iVar4 = param_1 + 0x20;
    iVar3 = param_1 + 0xc;
    do {
      *(int *)(iVar4 + -0xc) = param_5;
      *(undefined4 *)(iVar4 + -0x14) = param_4;
      if (0 < param_5) {
        iVar1 = 0;
        iVar2 = param_2 + 1;
        iVar5 = 0;
        do {
          *(undefined4 *)(iVar3 + 0x1c + iVar1) = 1;
          *(undefined4 *)(iVar3 + 0x10 + iVar1) = 0xffffffff;
          *(int *)(iVar3 + 0xc + iVar1) = iVar2;
          *(int *)(iVar3 + 0x18 + iVar1) = param_2;
          iVar5 = iVar5 + 1;
          *(undefined4 *)(iVar3 + 0x14 + iVar1) = 0xffffffff;
          iVar2 = iVar2 + 2;
          iVar1 = iVar1 + 0x14;
          *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
        } while (iVar5 < *(int *)(iVar4 + -0xc));
      }
      iVar4 = iVar4 + 0x5c;
      local_14 = local_14 + 1;
      iVar3 = iVar3 + 0x5c;
    } while (local_14 < *(int *)(param_1 + 4));
  }
  return;
}

/* BuildMenuCtrl @ 0x0808c6d0, 460 bytes
 * FIXUP: frame emulation: 12 stack locals placed at their original offsets in a 0x60-byte frame (a local's address escapes, see apply_frame_emulation) */
void BuildMenuCtrl(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  bool bVar7;
  unsigned char ghidra_frame[0x60] __attribute__((aligned(16)));
#define uStack_5c (*(undefined4 *)(ghidra_frame + 0x4))
#define local_58 (*(undefined4 *)(ghidra_frame + 0x8))
#define local_54 (*(undefined4 *)(ghidra_frame + 0xc))
#define uStack_4c (*(undefined4 *)(ghidra_frame + 0x14))
#define uStack_48 (*(undefined4 *)(ghidra_frame + 0x18))
#define local_44 (*(undefined4 *)(ghidra_frame + 0x1c))
#define local_3c (*(undefined4 *)(ghidra_frame + 0x24))
#define uStack_38 (*(undefined4 *)(ghidra_frame + 0x28))
#define uStack_34 (*(undefined4 *)(ghidra_frame + 0x2c))
#define local_2c (*(undefined4 *)(ghidra_frame + 0x34))
#define local_28 (*(undefined4 *)(ghidra_frame + 0x38))
#define uStack_24 (*(undefined4 *)(ghidra_frame + 0x3c))
  
  iVar2 = param_1 + param_3 * 0xb4;
  *(undefined4 *)(iVar2 + 0x3aa4) = 1;
  iVar1 = iVar2 + 0x3aa4;
  *(undefined4 *)(iVar2 + 0x3aac) = *(undefined4 *)(param_2 + 0x20);
  iVar3 = *(int *)(param_2 + 0x14);
  *(int *)(iVar2 + 0x3aa8) = iVar3;
  *(undefined4 *)(iVar2 + 0x3ab0) = *(undefined4 *)(param_2 + 0x1c);
  uVar4 = *(uint *)(param_2 + 0x18);
  if (iVar3 == 0) {
    bVar7 = (uVar4 & 1) != 0;
    if (bVar7) {
      *(undefined4 *)(iVar2 + 0x3ab8) = 0;
      *(char **)(iVar2 + 0x3abc) = "Single";
      MenuItemVal(&local_2c,0xffffffff,0,0xffffffff);
      *(undefined4 *)(iVar2 + 0x3ac0) = local_2c;
      *(undefined4 *)(iVar2 + 0x3ac4) = local_28;
      *(undefined4 *)(iVar2 + 0x3ac8) = uStack_24;
    }
    uVar6 = (uint)bVar7;
    uVar5 = uVar6;
    if ((uVar4 & 2) != 0) {
      uVar5 = uVar6 + 1;
      iVar3 = iVar1 + uVar6 * 0x14;
      *(undefined4 *)(iVar3 + 0x14) = 1;
      *(char **)(iVar3 + 0x18) = "Simul";
      MenuItemVal(&local_3c,2,2,2);
      *(undefined4 *)(iVar3 + 0x1c) = local_3c;
      *(undefined4 *)(iVar3 + 0x20) = uStack_38;
      *(undefined4 *)(iVar3 + 0x24) = uStack_34;
    }
    uVar6 = uVar5;
    if ((uVar4 & 4) != 0) {
      uVar6 = uVar5 + 1;
      iVar3 = iVar1 + uVar5 * 0x14;
      *(undefined4 *)(iVar3 + 0x14) = 2;
      *(undefined **)(iVar3 + 0x18) = &DAT_08277f83;
      MenuItemVal(&uStack_4c,2,2,2);
      *(undefined4 *)(iVar3 + 0x1c) = uStack_4c;
      *(undefined4 *)(iVar3 + 0x20) = uStack_48;
      *(undefined4 *)(iVar3 + 0x24) = local_44;
    }
    uVar5 = uVar6;
    if ((uVar4 & 8) != 0) {
      uVar5 = uVar6 + 1;
      iVar1 = iVar1 + uVar6 * 0x14;
      *(undefined4 *)(iVar1 + 0x14) = 3;
      *(char **)(iVar1 + 0x18) = "Turns";
      MenuItemVal(&uStack_5c,2,2,4);
      *(undefined4 *)(iVar1 + 0x1c) = uStack_5c;
      *(undefined4 *)(iVar1 + 0x20) = local_58;
      *(undefined4 *)(iVar1 + 0x24) = local_54;
    }
    *(uint *)(iVar2 + 0x3ab4) = uVar5;
    CharselRestoreMenuPos(param_1,(int *)(slct + 0x16d4 + *(int *)(iVar2 + 0x3aac) * 0x2e4),param_3)
    ;
  }
  else {
    ErrorExitM("Menu - programmer\'s fault");
  }
  return;
}
#undef uStack_5c
#undef local_58
#undef local_54
#undef uStack_4c
#undef uStack_48
#undef local_44
#undef local_3c
#undef uStack_38
#undef uStack_34
#undef local_2c
#undef local_28
#undef uStack_24

/* MenuItemVal @ 0x0808c8a0, 51 bytes */
void MenuItemVal(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  return;
}

/* CharReservePal @ 0x0808c8e0, 200 bytes */
uint CharReservePal(uint param_1,int param_2)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  
  uVar1 = *(uint *)(g[0x14b4] + 0x7028 + param_2 * 0x702c);
  if ((((int)uVar1 >> ((byte)param_1 & 0x1f) & 1U) == 0) && (5 < (int)param_1)) {
    param_1 = param_1 - 6;
  }
  if ((((int)uVar1 >> ((byte)param_1 & 0x1f) & 1U) == 0) || (0xb < (int)param_1)) {
    iVar3 = 0;
    do {
      iVar3 = iVar3 + 1;
      param_1 = param_1 + 1 & (5 < (int)(param_1 + 1)) - 1;
      if (((int)uVar1 >> ((byte)param_1 & 0x1f) & 1U) != 0) break;
    } while (iVar3 < 6);
    if (5 < iVar3) {
      do {
        param_1 = param_1 + 1;
        if (0xb < (int)param_1) {
          param_1 = 6;
        }
        iVar3 = iVar3 + 1;
      } while ((((int)uVar1 >> ((byte)param_1 & 0x1f) & 1U) == 0) && (iVar3 < 0xc));
    }
    param_1 = param_1 & (0xb < iVar3) - 1;
  }
  bVar2 = (byte)param_1 & 0x1f;
  *(uint *)(g[0x14b4] + 0x7028 + param_2 * 0x702c) =
       uVar1 & (-2 << bVar2 | 0xfffffffeU >> 0x20 - bVar2);
  return param_1;
}

/* CharStopUsingPal @ 0x0808c9b0, 65 bytes */
void CharStopUsingPal(byte param_1,int param_2)

{
  *(uint *)(g[0x14b4] + 0x7028 + param_2 * 0x702c) =
       *(uint *)(g[0x14b4] + 0x7028 + param_2 * 0x702c) | 1 << (param_1 & 0x1f);
  return;
}

/* CharStopUsingPalAll @ 0x0808ca00, 58 bytes */
void CharStopUsingPalAll(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  piVar2 = g;
  iVar4 = 0;
  if (0 < g[0x14b5]) {
    iVar3 = 0;
    do {
      iVar1 = piVar2[0x14b4];
      iVar4 = iVar4 + 1;
      *(undefined4 *)(iVar1 + 0x7028 + iVar3) = *(undefined4 *)(iVar1 + 0x5010 + iVar3);
      iVar3 = iVar3 + 0x702c;
    } while (iVar4 < piVar2[0x14b5]);
  }
  return;
}

