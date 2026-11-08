/*
 * p-make.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x080ac660-0x080b0fd2, 37 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"

extern int cachelastfreedtime __asm__("D_08287d20"); /* file-static 0x08287d20 */

/* PlayerCacheLoad @ 0x080ac660, 715 bytes
 * FIXUP: frame emulation: 2 stack locals placed at their original offsets in a 0x1030-byte frame (a local's address escapes, see apply_frame_emulation) */
int PlayerCacheLoad(int param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  void *pvVar6;
  uint *puVar7;
  uint *puVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  unsigned char ghidra_frame[0x1030] __attribute__((aligned(16)));
#define local_102c (*(int *)(ghidra_frame + 0x4))
#define local_101c (*(char (*)[4108])(ghidra_frame + 0x14))
  
  piVar4 = g;
  piVar1 = g + 0x14b4;
  iVar3 = g[0x14b4];
  piVar2 = (int *)(iVar3 + param_1 * 0x702c);
  if (piVar2[2] != 0) {
    *piVar2 = *piVar2 + 1;
    return piVar2[2];
  }
  if (g[0x14b6] < g[0x7579]) goto LAB_080ac840;
  iVar13 = -1;
  iVar12 = 0;
  local_102c = -1;
  if (0 < g[0x14b5]) {
    iVar9 = 0;
    do {
      if ((*(int *)(iVar3 + iVar9) == 0) && (*(int *)(iVar3 + 8 + iVar9) != 0)) {
        if (iVar13 == -1) {
          iVar5 = *(int *)(iVar3 + 4 + iVar9);
        }
        else {
          iVar5 = *(int *)(iVar3 + 4 + iVar9);
          if (local_102c <= iVar5) goto LAB_080ac73e;
        }
        iVar13 = iVar12;
        local_102c = iVar5;
      }
LAB_080ac73e:
      iVar12 = iVar12 + 1;
      iVar9 = iVar9 + 0x702c;
    } while (iVar12 < g[0x14b5]);
  }
  if (iVar13 == -1) {
    g[0x7579] = g[0x7579] + 1;
    goto LAB_080ac840;
  }
  if (g[0x801] == 0) {
LAB_080ac7f5:
    iVar12 = *piVar1;
  }
  else {
    iVar12 = *piVar1;
    iVar3 = iVar13 * 0x702c;
    iVar9 = *(int *)(iVar12 + 8 + iVar3);
    if ((*(char *)(iVar9 + 0x11d8) != '\0') && (*(int *)(iVar9 + 0x21d8) != 0)) {
      joindirfile(local_101c,(char *)(iVar3 + 0x200a + iVar12),(char *)(iVar9 + 0x11d8));
      iVar12 = AILearnDataSave(local_101c,*(int *)(*piVar1 + 8 + iVar3) + 0x21d8);
      if (iVar12 == 0) {
        ClipboardAppend((int *)g[0x81d1],"Cannot save AI info for %s",iVar3 + *piVar1 + 0x100b,
                        local_101c);
      }
      goto LAB_080ac7f5;
    }
  }
  PlayerRCFree(*(void **)(iVar12 + 8 + iVar13 * 0x702c));
  iVar3 = piVar4[0x14b6];
  *(undefined4 *)(*piVar1 + 8 + iVar13 * 0x702c) = 0;
  piVar4[0x14b6] = iVar3 + -1;
LAB_080ac840:
  pvVar6 = PlayerDefLoad((char *)((int)piVar2 + 0x200a),(char *)((int)piVar2 + 0x100b));
  piVar2[2] = (int)pvVar6;
  if (pvVar6 == (void *)0x0) {
    joindirfile(local_101c,(char *)((int)piVar2 + 0x200a),(char *)((int)piVar2 + 0x100b));
    puVar8 = (uint *)(g + 0x81d2);
    do {
      puVar7 = puVar8;
      puVar8 = puVar7 + 1;
      uVar10 = *puVar7 + 0xfefefeff & (*puVar7 ^ 0xffffffff);
      uVar11 = uVar10 & 0x80808080;
    } while (uVar11 == 0);
    if ((uVar10 & 0x8080) == 0) {
      uVar11 = uVar11 >> 0x10;
      puVar8 = (uint *)((int)puVar7 + 6);
    }
    sprintf((char *)((int)puVar8 +
                     (-(int)(g + 0x81d2) - (uint)CARRY1((byte)uVar11,(byte)uVar11)) + 0x20745 +
                    (int)g),"\nError loading %s",local_101c,pvVar6);
    iVar13 = 0;
  }
  else {
    iVar3 = *piVar1;
    iVar13 = *(int *)(iVar3 + 8 + param_1 * 0x702c);
    *(int *)(iVar13 + 0x10a8) = param_1;
    *(undefined4 *)(iVar3 + param_1 * 0x702c) = 1;
    piVar4[0x14b6] = piVar4[0x14b6] + 1;
  }
  return iVar13;
}
#undef local_102c
#undef local_101c

/* PlayerCacheFree @ 0x080ac930, 19 bytes */
void PlayerCacheFree(int param_1)

{
  PlayerCacheFreePriority(param_1,0);
  return;
}

/* PlayerCacheFreePriority @ 0x080ac950, 81 bytes */
int PlayerCacheFreePriority(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = g[0x14b4];
  iVar1 = param_1 * 0x702c;
  iVar3 = *(int *)(iVar2 + iVar1);
  if (0 < iVar3) {
    iVar3 = iVar3 + -1;
    *(int *)(iVar2 + iVar1) = iVar3;
    if (iVar3 == 0) {
      iVar3 = cachelastfreedtime + 1;
      *(int *)(iVar2 + 4 + iVar1) = param_2 + cachelastfreedtime;
      cachelastfreedtime = iVar3;
    }
  }
  return iVar3;
}

/* PlayerCacheChangePriority @ 0x080ac9b0, 73 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
void PlayerCacheChangePriority(int param_1,int param_2)

{
  bool bVar1;
  undefined3 extraout_var;
  
  bVar1 = PlayerIsCached(param_1);
  if (GHIDRA_ZEXT8(bVar1) != 0) {
    *(int *)(g[0x14b4] + 4 + param_1 * 0x702c) = param_2 + cachelastfreedtime;
  }
  return;
}

/* PlayerIsCached @ 0x080aca00, 49 bytes */
bool PlayerIsCached(int param_1)

{
  return *(int *)(g[0x14b4] + 8 + param_1 * 0x702c) != 0;
}

/* PlayerCacheClear @ 0x080aca40, 243 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x1020-byte frame (a local's address escapes, see apply_frame_emulation) */
void PlayerCacheClear(void)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 extraout_ECX;
  int iVar5;
  int iVar6;
  unsigned char ghidra_frame[0x1020] __attribute__((aligned(16)));
#define acStack_101c (*(char (*)[4108])(ghidra_frame + 0x4))
  
  piVar3 = g;
  iVar6 = 0;
  piVar1 = g + 0x14b4;
  if (0 < g[0x14b5]) {
    iVar5 = 0;
    do {
      iVar4 = *piVar1;
      iVar2 = *(int *)(iVar4 + 8 + iVar5);
      if (iVar2 != 0) {
        if (((g[0x801] != 0) && (*(char *)(iVar2 + 0x11d8) != '\0')) &&
           (*(int *)(iVar2 + 0x21d8) != 0)) {
          joindirfile(acStack_101c,(char *)(iVar5 + 0x200a + iVar4),(char *)(iVar2 + 0x11d8));
          iVar4 = AILearnDataSave(acStack_101c,*(int *)(*piVar1 + 8 + iVar5) + 0x21d8);
          if (iVar4 == 0) {
            ClipboardAppend((int *)g[0x81d1],"Cannot save AI info for %s",iVar5 + *piVar1 + 0x100b,
                            extraout_ECX);
          }
          iVar4 = *piVar1;
        }
        PlayerRCFree(*(void **)(iVar4 + 8 + iVar5));
        iVar4 = *piVar1;
        *(undefined4 *)(iVar4 + iVar5) = 0;
        *(undefined4 *)(iVar4 + 8 + iVar5) = 0;
        piVar3[0x14b6] = piVar3[0x14b6] + -1;
      }
      iVar6 = iVar6 + 1;
      iVar5 = iVar5 + 0x702c;
    } while (iVar6 < piVar3[0x14b5]);
  }
  return;
}
#undef acStack_101c

/* PlayerCacheHasUnused @ 0x080acb40, 92 bytes */
undefined4 PlayerCacheHasUnused(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  if (g[0x14b6] < g[0x7579]) {
LAB_080acb90:
    uVar2 = 1;
  }
  else {
    iVar3 = 0;
    if (0 < g[0x14b5]) {
      iVar1 = 0;
      do {
        if ((*(int *)(g[0x14b4] + iVar1) == 0) && (*(int *)(g[0x14b4] + 8 + iVar1) != 0))
        goto LAB_080acb90;
        iVar3 = iVar3 + 1;
        iVar1 = iVar1 + 0x702c;
      } while (iVar3 < g[0x14b5]);
    }
    uVar2 = 0;
  }
  return uVar2;
}

/* PlayerDefLoad @ 0x080acba0, 195 bytes
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x1020-byte frame (a local's address escapes, see apply_frame_emulation) */
void * PlayerDefLoad(char *param_1,char *param_2)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  FILE *stream;
  undefined4 extraout_EDX;
  unsigned char ghidra_frame[0x1020] __attribute__((aligned(16)));
#define local_101c (*(char (*)[4108])(ghidra_frame + 0x4))
  
  joindirfile(local_101c,param_1,param_2);
  iVar1 = CheckExtension(param_1);
  if (iVar1 == 9) {
    piVar2 = MFfopenZip(param_1,param_2);
    if (piVar2 == (int *)0x0) {
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = PlayerDefLoadZip(param_1,piVar2);
      MFfclose(piVar2);
    }
  }
  else {
    stream = fopen(local_101c,"rt");
    if (stream == (FILE *)0x0) {
      sprintf((char *)(g + 0x81d2),"Can\'t open %s",param_2,extraout_EDX);
      piVar3 = (int *)0x0;
    }
    else {
      piVar3 = (int *)PlayerDefLoadPtr(param_1,stream);
      fclose(stream);
    }
  }
  return piVar3;
}
#undef local_101c

/* PlayerDefLoadZip @ 0x080acc70, 3607 bytes
 * REVIEW: pid-unaff_
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 6 stack locals placed at their original offsets in a 0x2790-byte frame (a local's address escapes, see apply_frame_emulation) */
int * PlayerDefLoadZip(char *param_1,int *param_2)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  int *__src;
  int iVar4;
  int *piVar5;
  undefined3 extraout_var;
  int *piVar6;
  int *piVar7;
  FILE *stream;
  uint *puVar8;
  uint *puVar9;
  int *extraout_ECX;
  int *extraout_ECX_00;
  undefined4 extraout_ECX_01;
  int *extraout_EDX;
  int *extraout_EDX_00;
  uint uVar10;
  uint uVar11;
  undefined4 extraout_EDX_01;
  int *extraout_EDX_02;
  int *extraout_EDX_03;
  int *extraout_EDX_04;
  int *extraout_EDX_05;
  int *unaff_EBP;
  char *pcVar12;
  int *piVar13;
  int *piVar14;
  unsigned char ghidra_frame[0x2790] __attribute__((aligned(16)));
#define local_278c (*(int **)(ghidra_frame + 0x4))
#define local_277c (*(undefined1 (*)[1024])(ghidra_frame + 0x14))
#define local_237c (*(int (*)[152])(ghidra_frame + 0x414))
#define local_211c (*(char (*)[256])(ghidra_frame + 0x674))
#define local_201c (*(int (*)[1024])(ghidra_frame + 0x774))
#define local_101c (*(int (*)[1027])(ghidra_frame + 0x1774))
  
  iVar2 = MFftell(param_2);
  piVar3 = TPReadMF(param_2,0);
  if (piVar3 == (int *)0x0) {
    return (int *)0x0;
  }
  __src = (int *)ecalloc(1,0x22e0);
  if (__src == (int *)0x0) {
    return (int *)0x0;
  }
  iVar4 = TPGroupSeek((int)piVar3,"Info");
  if (iVar4 == -1) {
    piVar3 = g + 0x81d2;
    pcVar12 = "Can\'t access Info";
    piVar5 = param_2;
    piVar13 = param_2;
    goto LAB_080ad88d;
  }
  iVar4 = GetQuotedString((int)piVar3,"name",(char *)__src,0x2f,(char *)0x0);
  if (iVar4 == 0) {
    return (int *)0x0;
  }
  pcVar12 = TPGetValue((int)piVar3,"displayname");
  if (pcVar12 == (char *)0x0) {
    strcpy((char *)(__src + 0xc),(char *)__src);
  }
  else {
    iVar4 = GetQuotedString((int)piVar3,"displayname",(char *)(__src + 0xc),0x2f,(char *)0x0);
    unaff_EBP = piVar3;
    if (iVar4 == 0) {
      return (int *)0x0;
    }
  }
  pcVar12 = TPGetValue((int)piVar3,"author");
  if ((pcVar12 != (char *)0x0) &&
     (iVar4 = GetQuotedString((int)piVar3,"author",(char *)(__src + 0x18),0x2f,(char *)0x0),
     iVar4 == 0)) {
    return (int *)0x0;
  }
  TPScanf((int)piVar3,"versiondate","%i,%i,%i",__src + 0x24,__src + 0x25,__src + 0x26,unaff_EBP,
          unaff_EBP);
  TPScanf((int)piVar3,"mugenversion","%i,%i,%i",__src + 0x27,__src + 0x28,__src + 0x29);
  iVar4 = TPGroupSeek((int)piVar3,"Files");
  if (iVar4 == -1) {
    piVar3 = g + 0x81d2;
    pcVar12 = "Can\'t access Files";
    piVar5 = extraout_EDX;
    piVar13 = extraout_EDX;
    goto LAB_080ad88d;
  }
  piVar13 = (int *)&DAT_0827a342;
  iVar4 = TPScanf((int)piVar3,"cmd","%s",local_101c);
  if (iVar4 != 1) {
    return (int *)0x0;
  }
  if (*param_2 == 3) {
    MFzclose((int)param_2);
    MFzopen(param_2,(char *)local_101c);
  }
  else {
    joindirfile((char *)local_201c,param_1,(char *)local_101c);
    piVar13 = param_2;
    MFfclose(param_2);
    param_2 = (int *)MFfopenFile((char *)local_201c,"rt");
  }
  puVar9 = (uint *)(__src + 0x46d);
  piVar5 = TPReadMF(param_2,0);
  iVar4 = PlayerCMDLoadTP((uint)piVar5,puVar9);
  if (iVar4 == 0) {
    strcat((char *)(g + 0x81d2),"\nError in ");
    strcat((char *)(g + 0x81d2),(char *)local_101c);
    return (int *)0x0;
  }
  piVar5 = (int *)&DAT_0827a346;
  iVar4 = TPScanf((int)piVar3,"cns","%s",local_101c);
  if (iVar4 != 1) {
    return (int *)0x0;
  }
  if (*param_2 == 3) {
    piVar13 = piVar5;
    MFzclose((int)param_2);
    MFzopen(param_2,(char *)local_101c);
  }
  else {
    MFfclose(param_2);
    joindirfile((char *)local_201c,param_1,(char *)local_101c);
    param_2 = (int *)MFfopenFile((char *)local_201c,"rt");
  }
  piVar5 = TPReadMF(param_2,0);
  if (piVar5 == (int *)0x0) {
    pcVar12 = "Can\'t open file: %s";
  }
  else {
    iVar4 = PlayerCNSLoadTP((int)__src,(int)piVar5);
    if (iVar4 == 0) {
      strcat((char *)(g + 0x81d2),"\nError in ");
      strcat((char *)(g + 0x81d2),(char *)local_101c);
      return (int *)0x0;
    }
    pcVar12 = TPGetValue((int)piVar3,"st");
    if (pcVar12 == (char *)0x0) {
      return (int *)0x0;
    }
    iVar4 = strcmp(pcVar12,(char *)local_101c);
    if (iVar4 != 0) {
      TPFree(piVar5);
      strcpy((char *)local_101c,pcVar12);
      if (*param_2 == 3) {
        MFzclose((int)param_2);
        MFzopen(param_2,(char *)local_101c);
      }
      else {
        pcVar12 = param_1;
        joindirfile((char *)local_201c,param_1,(char *)local_101c);
        MFfclose(param_2);
        param_2 = (int *)MFfopenFile((char *)local_201c,"rt");
      }
      piVar5 = TPReadMF(param_2,0);
      if (piVar5 == (int *)0x0) {
        pcVar12 = "Can\'t open file: %s";
        piVar13 = extraout_EDX_00;
        goto LAB_080ad888;
      }
    }
    bVar1 = PlayerSTLoadTP((int)__src,(int)piVar5);
    if (GHIDRA_ZEXT8(bVar1) == 0) {
      puVar9 = (uint *)(g + 0x81d2);
      do {
        puVar8 = puVar9;
        puVar9 = puVar8 + 1;
        uVar10 = *puVar8 + 0xfefefeff & (*puVar8 ^ 0xffffffff);
        uVar11 = uVar10 & 0x80808080;
      } while (uVar11 == 0);
      if ((uVar10 & 0x8080) == 0) {
        uVar11 = uVar11 >> 0x10;
        puVar9 = (uint *)((int)puVar8 + 6);
      }
      sprintf((char *)((int)puVar9 +
                       (-(int)(g + 0x81d2) - (uint)CARRY1((byte)uVar11,(byte)uVar11)) + 0x20745 +
                      (int)g),"\nError in %s",local_101c,pcVar12);
      iVar2 = MDYDateCmp(__src[0x27],__src[0x28],__src[0x29],g[0x802],g[0x803],g[0x804]);
      if (iVar2 < 0) {
        pcVar12 = "\nCharacter needs to be updated. See docs/incompt*.txt.";
      }
      else {
        iVar2 = MDYDateCmp(__src[0x27],__src[0x28],__src[0x29],g[0x802],g[0x803],g[0x804]);
        if (iVar2 < 1) {
          return (int *)0x0;
        }
        pcVar12 = "\nCharacter is not designed to run on this version of M.U.G.E.N.";
      }
      strcat((char *)(g + 0x81d2),pcVar12);
      return (int *)0x0;
    }
    TPFree(piVar5);
    local_278c = (int *)0x0;
    piVar6 = local_201c;
    do {
      sprintf(local_211c,"st%i",local_278c,piVar6);
      iVar4 = TPScanf((int)piVar3,local_211c,"%s",local_101c);
      if (iVar4 == 1) {
        if (*param_2 == 3) {
          MFzclose((int)param_2);
          MFzopen(param_2,(char *)local_101c);
          piVar13 = local_278c;
        }
        else {
          joindirfile((char *)local_201c,param_1,(char *)local_101c);
          MFfclose(param_2);
          param_2 = (int *)MFfopenFile((char *)local_201c,"rt");
          piVar13 = local_201c;
        }
        if (param_2 == (int *)0x0) {
          pcVar12 = "\nCould not open file: %s";
          goto LAB_080ad888;
        }
        piVar13 = TPReadMF(param_2,0);
        if (piVar13 == (int *)0x0) {
          pcVar12 = "\nError reading in file: %s";
          piVar13 = extraout_ECX;
          goto LAB_080ad888;
        }
        iVar4 = SctrlAddFileTP((int *)__src[0x471],(int)piVar13,(int)__src);
        if (iVar4 == 0) {
          sprintf(local_211c,"\nError in %s",local_101c,extraout_EDX_01);
          strcat((char *)(g + 0x81d2),local_211c);
          iVar2 = MDYDateCmp(__src[0x27],__src[0x28],__src[0x29],g[0x802],g[0x803],g[0x804]);
          if (iVar2 < 0) {
            pcVar12 = "\nCharacter needs to be updated. See docs/incompt*.txt.";
          }
          else {
            iVar2 = MDYDateCmp(__src[0x27],__src[0x28],__src[0x29],g[0x802],g[0x803],g[0x804]);
            if (iVar2 < 1) {
              return (int *)0x0;
            }
            pcVar12 = "\nCharacter is not designed to run on this version of M.U.G.E.N.";
          }
          strcat((char *)(g + 0x81d2),pcVar12);
          return (int *)0x0;
        }
        TPFree(piVar13);
      }
      piVar6 = (int *)((int)local_278c + 1);
      local_278c = piVar6;
    } while ((int)piVar6 < 10);
    iVar4 = TPScanf((int)piVar3,"cmd","%s",local_101c);
    if (iVar4 != 1) {
      return (int *)0x0;
    }
    if (*param_2 == 3) {
      MFzclose((int)param_2);
      MFzopen(param_2,(char *)local_101c);
      piVar13 = local_101c;
    }
    else {
      piVar13 = local_201c;
      joindirfile((char *)piVar13,param_1,(char *)local_101c);
      MFfclose(param_2);
      param_2 = (int *)MFfopenFile((char *)piVar13,"rt");
    }
    if (param_2 == (int *)0x0) {
      pcVar12 = "\nCould not open file: %s";
    }
    else {
      piVar7 = TPReadMF(param_2,0);
      if (piVar7 == (int *)0x0) {
        pcVar12 = "\nError reading in file: %s";
        piVar13 = extraout_EDX_02;
      }
      else {
        piVar14 = piVar7;
        iVar4 = SctrlAddFileTP((int *)__src[0x471],(int)piVar7,(int)__src);
        if (iVar4 == 0) {
          strcat((char *)(g + 0x81d2),"\nError in ");
          strcat((char *)(g + 0x81d2),(char *)local_101c);
          return (int *)0x0;
        }
        TPFree(piVar7);
        piVar5 = local_101c;
        iVar4 = TPScanf((int)piVar3,"stcommon","%s",piVar5);
        piVar13 = __src;
        if (iVar4 == 1) {
          iVar4 = 1;
          if (*param_2 == 3) {
            piVar13 = piVar14;
            MFzclose((int)param_2);
            iVar4 = MFzopen(param_2,(char *)piVar5);
          }
          if (iVar4 == 1) {
            piVar7 = TPReadMF(param_2,0);
            if (piVar7 == (int *)0x0) {
              piVar3 = g + 0x81d2;
              pcVar12 = "\nError reading in file: %s";
              piVar13 = extraout_EDX_03;
              goto LAB_080ad88d;
            }
            SctrlAddFileTP((int *)__src[0x471],(int)piVar7,(int)__src);
            piVar13 = __src;
          }
          else {
            piVar7 = local_201c;
            joindirfile((char *)piVar7,"data/",(char *)piVar5);
            iVar4 = PlayerSTLoadAppend((int)__src,(char *)piVar7);
            if (iVar4 == 0) {
              strcat((char *)(g + 0x81d2),"\nError in ");
              strcat((char *)(g + 0x81d2),(char *)piVar5);
              return (int *)0x0;
            }
          }
        }
        CmdSetFreeLabel((int)(__src + 0x46d));
        piVar5 = local_101c;
        iVar4 = TPScanf((int)piVar3,"sprite","%s",piVar5);
        if (iVar4 != 1) {
          return (int *)0x0;
        }
        if (*param_2 == 3) {
          MFzclose((int)param_2);
          MFzopen(param_2,(char *)piVar5);
          if (piVar6 == (int *)0x0) {
            piVar3 = g + 0x81d2;
            pcVar12 = "\nCould not open file: %s";
            piVar13 = piVar7;
            goto LAB_080ad88d;
          }
          piVar13 = SpriteReadSFFPtr(param_2);
          __src[0x472] = (int)piVar13;
          if (piVar13 == (int *)0x0) {
            piVar3 = g + 0x81d2;
            pcVar12 = "Can\'t load %s";
            piVar13 = extraout_ECX_00;
            goto LAB_080ad88d;
          }
        }
        else {
          joindirfile((char *)local_201c,param_1,(char *)piVar5);
          piVar6 = SpriteReadFile((char *)local_201c);
          __src[0x472] = (int)piVar6;
          if (piVar6 == (int *)0x0) {
            piVar3 = g + 0x81d2;
            pcVar12 = "Can\'t load %s";
            goto LAB_080ad88d;
          }
        }
        iVar4 = TPScanf((int)piVar3,"anim","%s",local_101c);
        if (iVar4 != 1) {
          return (int *)0x0;
        }
        if (*param_2 == 3) {
          MFzclose((int)param_2);
          MFzopen(param_2,(char *)local_101c);
        }
        else {
          joindirfile((char *)local_201c,param_1,(char *)local_101c);
          MFfclose(param_2);
          param_2 = (int *)MFfopenFile((char *)local_201c,"rt");
        }
        piVar13 = TPReadMF(param_2,0);
        if (piVar13 == (int *)0x0) {
          pcVar12 = "\nError reading in file: %s";
          piVar13 = extraout_EDX_04;
        }
        else {
          clsnxscale = __src[0x436];
          clsnyscale = __src[0x437];
          piVar5 = AnimRCReadFileTP((int)piVar13);
          __src[0x473] = (int)piVar5;
          if (piVar5 == (int *)0x0) {
            piVar13 = (int *)0x0;
          }
          else {
            clsnyscale = 0x3f800000;
            clsnxscale = 0x3f800000;
            TPFree(piVar13);
            iVar4 = GetSndMode();
            if (iVar4 != 1) {
LAB_080ad8a0:
              local_278c = (int *)0x0;
              pcVar12 = local_211c;
              do {
                sprintf(local_211c,"pal%i",(char *)((int)local_278c + 1),pcVar12);
                iVar4 = TPScanf((int)piVar3,local_211c,"%s",local_101c);
                if (0 < iVar4) {
                  if (*param_2 == 3) {
                    MFzclose((int)param_2);
                    MFzopen(param_2,(char *)local_101c);
                  }
                  else {
                    joindirfile((char *)local_201c,param_1,(char *)local_101c);
                    MFfclose(param_2);
                    param_2 = (int *)MFfopenFile((char *)local_201c,"rb");
                  }
                  iVar4 = Pal4Read3FilePtr((int)local_277c,param_2);
                  piVar13 = extraout_EDX_05;
                  if (iVar4 == 0) goto LAB_080ad876;
                  iVar4 = EBPalInit(local_237c,0x100,local_277c,1);
                  if (iVar4 == 0) {
                    return (int *)0x0;
                  }
                  iVar4 = SpriteArrayAddPal(__src[0x472],local_237c,1,local_278c);
                  if (iVar4 == 0) {
                    return (int *)0x0;
                  }
                }
                pcVar12 = (char *)((int)local_278c + 1);
                local_278c = (int *)pcVar12;
                if (0xb < (int)pcVar12) {
                  iVar4 = TPScanf((int)piVar3,"ai","%s",local_101c);
                  if (iVar4 == 1) {
                    joindirfile((char *)local_201c,param_1,(char *)local_101c);
                    iVar4 = AILearnDataLoad((char *)local_201c,__src + 0x876);
                    if ((iVar4 == 0) &&
                       (stream = fopen((char *)local_201c,"rb"), stream != (FILE *)0x0)) {
                      ClipboardAppend((int *)g[0x81d1],"Ignoring invalid AI file: %s\n",local_101c,
                                      extraout_ECX_01);
                      fclose(stream);
                    }
                    strncpy((char *)(__src + 0x476),(char *)local_101c,0xffe);
                  }
                  TPFree(piVar3);
                  MFfseek(param_2,iVar2,0);
                  return __src;
                }
              } while( true );
            }
            iVar4 = TPScanf((int)piVar3,"sound","%s",local_101c);
            if (iVar4 != 1) goto LAB_080ad8a0;
            if (*param_2 == 3) {
              MFzclose((int)param_2);
              MFzopen(param_2,(char *)local_101c);
            }
            else {
              joindirfile((char *)local_201c,param_1,(char *)local_101c);
              MFfclose(param_2);
              param_2 = (int *)MFfopenFile((char *)local_201c,"rb");
            }
            piVar5 = SndReadFileSNDPtr(param_2);
            __src[0x475] = (int)piVar5;
            piVar13 = param_2;
            if (piVar5 != (int *)0x0) goto LAB_080ad8a0;
          }
LAB_080ad876:
          pcVar12 = "Can\'t load %s";
        }
      }
    }
  }
LAB_080ad888:
  piVar5 = local_101c;
  piVar3 = g + 0x81d2;
LAB_080ad88d:
  sprintf((char *)piVar3,pcVar12,piVar5,piVar13);
  return (int *)0x0;
}
#undef local_278c
#undef local_277c
#undef local_237c
#undef local_211c
#undef local_201c
#undef local_101c

/* PlayerDefLoadPtr @ 0x080ada90, 2562 bytes
 * REVIEW: pid-in_stack_
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 5 stack locals placed at their original offsets in a 0x2780-byte frame (a local's address escapes, see apply_frame_emulation) */
char * PlayerDefLoadPtr(char *param_1,FILE *param_2)

{
  char *pcVar1;
  bool bVar2;
  long __off;
  int *piVar3;
  char *pcVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  undefined3 extraout_var;
  int iVar8;
  int *piVar9;
  FILE *stream;
  uint *puVar10;
  uint *puVar11;
  int *extraout_ECX;
  int *extraout_ECX_00;
  int *extraout_ECX_01;
  undefined4 extraout_ECX_02;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar12;
  undefined4 extraout_EDX_01;
  uint uVar13;
  uint uVar14;
  int *extraout_EDX_02;
  int *in_stack_ffffd858;
  unsigned char ghidra_frame[0x2780] __attribute__((aligned(16)));
#define local_277c (*(undefined1 (*)[1024])(ghidra_frame + 0x4))
#define local_237c (*(int (*)[152])(ghidra_frame + 0x404))
#define local_211c (*(char (*)[256])(ghidra_frame + 0x664))
#define local_201c (*(char (*)[4096])(ghidra_frame + 0x764))
#define local_101c (*(int (*)[1027])(ghidra_frame + 0x1764))
  
  __off = ftell(param_2);
  piVar3 = TPReadFilePtr(param_2,0);
  if (piVar3 == (int *)0x0) {
    return (char *)0x0;
  }
  pcVar4 = (char *)ecalloc(1,0x22e0);
  if (pcVar4 == (char *)0x0) {
    return (char *)0x0;
  }
  iVar5 = TPGroupSeek((int)piVar3,"Info");
  if (iVar5 == -1) {
    piVar9 = g + 0x81d2;
    pcVar4 = "Can\'t access Info";
    piVar3 = in_stack_ffffd858;
  }
  else {
    iVar5 = GetQuotedString((int)piVar3,"name",pcVar4,0x2f,(char *)0x0);
    if (iVar5 == 0) {
      return (char *)0x0;
    }
    pcVar6 = TPGetValue((int)piVar3,"displayname");
    if (pcVar6 == (char *)0x0) {
      strcpy(pcVar4 + 0x30,pcVar4);
    }
    else {
      iVar5 = GetQuotedString((int)piVar3,"displayname",pcVar4 + 0x30,0x2f,(char *)0x0);
      if (iVar5 == 0) {
        return (char *)0x0;
      }
    }
    pcVar6 = TPGetValue((int)piVar3,"author");
    uVar12 = extraout_EDX;
    if ((pcVar6 != (char *)0x0) &&
       (iVar5 = GetQuotedString((int)piVar3,"author",pcVar4 + 0x60,0x2f,(char *)0x0),
       uVar12 = extraout_EDX_00, iVar5 == 0)) {
      return (char *)0x0;
    }
    TPScanf((int)piVar3,"versiondate","%i,%i,%i",pcVar4 + 0x90,pcVar4 + 0x94,pcVar4 + 0x98,uVar12,
            uVar12);
    TPScanf((int)piVar3,"mugenversion","%i,%i,%i",pcVar4 + 0x9c,pcVar4 + 0xa0,pcVar4 + 0xa4);
    iVar5 = TPGroupSeek((int)piVar3,"Files");
    if (iVar5 == -1) {
      piVar9 = g + 0x81d2;
      pcVar4 = "Can\'t access Files";
      in_stack_ffffd858 = piVar3;
    }
    else {
      in_stack_ffffd858 = local_101c;
      iVar5 = TPScanf((int)piVar3,"cmd","%s",in_stack_ffffd858);
      if (iVar5 != 1) {
        return (char *)0x0;
      }
      joindirfile(local_201c,param_1,(char *)in_stack_ffffd858);
      iVar5 = PlayerCMDLoad(local_201c,(uint *)(pcVar4 + 0x11b4));
      if (iVar5 == 0) {
        strcat((char *)(g + 0x81d2),"\nError in ");
        strcat((char *)(g + 0x81d2),(char *)in_stack_ffffd858);
        return (char *)0x0;
      }
      iVar5 = TPScanf((int)piVar3,"cns","%s",in_stack_ffffd858);
      if (iVar5 != 1) {
        return (char *)0x0;
      }
      joindirfile(local_201c,param_1,(char *)in_stack_ffffd858);
      pcVar6 = TPReadFile(local_201c);
      if (pcVar6 == (char *)0x0) {
        piVar9 = g + 0x81d2;
        pcVar4 = "Can\'t open file: %s";
        piVar3 = (int *)0x0;
      }
      else {
        iVar5 = PlayerCNSLoadTP((int)pcVar4,(int)pcVar6);
        if (iVar5 == 0) {
          strcat((char *)(g + 0x81d2),"\nError in ");
          strcat((char *)(g + 0x81d2),(char *)in_stack_ffffd858);
          return (char *)0x0;
        }
        pcVar7 = TPGetValue((int)piVar3,"st");
        if (pcVar7 == (char *)0x0) {
          return (char *)0x0;
        }
        iVar5 = strcmp(pcVar7,(char *)in_stack_ffffd858);
        if (iVar5 != 0) {
          TPFree((undefined4 *)pcVar6);
          strcpy((char *)in_stack_ffffd858,pcVar7);
          joindirfile(local_201c,param_1,(char *)in_stack_ffffd858);
          pcVar6 = TPReadFile(local_201c);
          if (pcVar6 == (char *)0x0) {
            piVar9 = g + 0x81d2;
            pcVar4 = "Can\'t open file: %s";
            piVar3 = (int *)0x0;
            goto LAB_080ae2d6;
          }
        }
        bVar2 = PlayerSTLoadTP((int)pcVar4,(int)pcVar6);
        if (GHIDRA_ZEXT8(bVar2) == 0) {
          puVar11 = (uint *)(g + 0x81d2);
          do {
            puVar10 = puVar11;
            puVar11 = puVar10 + 1;
            uVar13 = *puVar10 + 0xfefefeff & (*puVar10 ^ 0xffffffff);
            uVar14 = uVar13 & 0x80808080;
          } while (uVar14 == 0);
          if ((uVar13 & 0x8080) == 0) {
            uVar14 = uVar14 >> 0x10;
            puVar11 = (uint *)((int)puVar10 + 6);
          }
          sprintf((char *)((int)puVar11 +
                           (-(int)(g + 0x81d2) - (uint)CARRY1((byte)uVar14,(byte)uVar14)) + 0x20745
                          + (int)g),"\nError in %s",local_101c,extraout_EDX_01);
          iVar5 = MDYDateCmp(*(int *)(pcVar4 + 0x9c),*(int *)(pcVar4 + 0xa0),*(int *)(pcVar4 + 0xa4)
                             ,g[0x802],g[0x803],g[0x804]);
          if (iVar5 < 0) {
            pcVar4 = "\nCharacter needs to be updated. See docs/incompt*.txt.";
          }
          else {
            iVar5 = MDYDateCmp(*(int *)(pcVar4 + 0x9c),*(int *)(pcVar4 + 0xa0),
                               *(int *)(pcVar4 + 0xa4),g[0x802],g[0x803],g[0x804]);
            if (iVar5 < 1) {
              return (char *)0x0;
            }
            pcVar4 = "\nCharacter is not designed to run on this version of M.U.G.E.N.";
          }
          strcat((char *)(g + 0x81d2),pcVar4);
          return (char *)0x0;
        }
        iVar5 = 0;
        TPFree((undefined4 *)pcVar6);
        do {
          sprintf(local_211c,"st%i",iVar5,pcVar6);
          iVar8 = TPScanf((int)piVar3,local_211c,"%s",local_101c);
          if (iVar8 == 1) {
            pcVar6 = local_201c;
            joindirfile(pcVar6,param_1,(char *)local_101c);
            iVar8 = PlayerSTLoadAppend((int)pcVar4,pcVar6);
            if (iVar8 == 0) {
              sprintf(local_211c,"\nError in %s",local_101c,iVar5);
              strcat((char *)(g + 0x81d2),local_211c);
              iVar5 = MDYDateCmp(*(int *)(pcVar4 + 0x9c),*(int *)(pcVar4 + 0xa0),
                                 *(int *)(pcVar4 + 0xa4),g[0x802],g[0x803],g[0x804]);
              if (iVar5 < 0) {
                pcVar4 = "\nCharacter needs to be updated. See docs/incompt*.txt.";
              }
              else {
                iVar5 = MDYDateCmp(*(int *)(pcVar4 + 0x9c),*(int *)(pcVar4 + 0xa0),
                                   *(int *)(pcVar4 + 0xa4),g[0x802],g[0x803],g[0x804]);
                if (iVar5 < 1) {
                  return (char *)0x0;
                }
                pcVar4 = "\nCharacter is not designed to run on this version of M.U.G.E.N.";
              }
              strcat((char *)(g + 0x81d2),pcVar4);
              return (char *)0x0;
            }
          }
          iVar5 = iVar5 + 1;
        } while (iVar5 < 10);
        iVar5 = TPScanf((int)piVar3,"cmd","%s",local_101c);
        if (iVar5 != 1) {
          return (char *)0x0;
        }
        joindirfile(local_201c,param_1,(char *)local_101c);
        iVar5 = PlayerSTLoadAppend((int)pcVar4,local_201c);
        if (iVar5 == 0) {
          strcat((char *)(g + 0x81d2),"\nError in ");
          strcat((char *)(g + 0x81d2),(char *)local_101c);
          return (char *)0x0;
        }
        iVar5 = TPScanf((int)piVar3,"stcommon","%s",local_101c);
        if (iVar5 == 1) {
          joindirfile(local_201c,param_1,(char *)local_101c);
          iVar5 = PlayerSTLoadAppend((int)pcVar4,local_201c);
          if (iVar5 == 0) {
            joindirfile(local_201c,"data/",(char *)local_101c);
            iVar5 = PlayerSTLoadAppend((int)pcVar4,local_201c);
            if (iVar5 == 0) {
              strcat((char *)(g + 0x81d2),"\nError in ");
              strcat((char *)(g + 0x81d2),(char *)local_101c);
              return (char *)0x0;
            }
          }
        }
        CmdSetFreeLabel((int)(pcVar4 + 0x11b4));
        in_stack_ffffd858 = local_101c;
        iVar5 = TPScanf((int)piVar3,"sprite","%s",in_stack_ffffd858);
        if (iVar5 != 1) {
          return (char *)0x0;
        }
        joindirfile(local_201c,param_1,(char *)in_stack_ffffd858);
        piVar9 = SpriteReadFile(local_201c);
        *(int **)(pcVar4 + 0x11c8) = piVar9;
        if (piVar9 == (int *)0x0) {
          piVar9 = g + 0x81d2;
          pcVar4 = "Can\'t load %s";
          piVar3 = extraout_ECX;
        }
        else {
          iVar5 = TPScanf((int)piVar3,"anim","%s",in_stack_ffffd858);
          if (iVar5 != 1) {
            return (char *)0x0;
          }
          joindirfile(local_201c,param_1,(char *)in_stack_ffffd858);
          clsnxscale = *(int *)(pcVar4 + 0x10d8);
          clsnyscale = *(int *)(pcVar4 + 0x10dc);
          piVar9 = AnimRCReadFile(local_201c);
          *(int **)(pcVar4 + 0x11cc) = piVar9;
          if (piVar9 != (int *)0x0) {
            clsnyscale = 0x3f800000;
            clsnxscale = 0x3f800000;
            iVar5 = GetSndMode();
            if ((iVar5 == 1) &&
               (iVar5 = TPScanf((int)piVar3,"sound","%s",in_stack_ffffd858), iVar5 == 1)) {
              joindirfile(local_201c,param_1,(char *)in_stack_ffffd858);
              piVar9 = SndReadFile(local_201c);
              *(int **)(pcVar4 + 0x11d4) = piVar9;
              if (piVar9 == (int *)0x0) {
                piVar9 = g + 0x81d2;
                pcVar4 = "Can\'t load %s";
                piVar3 = extraout_ECX_01;
                goto LAB_080ae2d6;
              }
            }
            in_stack_ffffd858 = local_101c;
            pcVar6 = param_1;
            pcVar7 = (char *)0x0;
            do {
              pcVar1 = pcVar7 + 1;
              sprintf(local_211c,"pal%i",pcVar1,pcVar6);
              iVar5 = TPScanf((int)piVar3,local_211c,"%s",in_stack_ffffd858);
              if (0 < iVar5) {
                joindirfile(local_201c,param_1,(char *)in_stack_ffffd858);
                iVar5 = Pal4Read3File((int)local_277c,local_201c);
                if (iVar5 == 0) {
                  pcVar4 = "Can\'t load %s";
                  piVar9 = g + 0x81d2;
                  piVar3 = extraout_EDX_02;
                  goto LAB_080ae2d6;
                }
                iVar5 = EBPalInit(local_237c,0x100,local_277c,1);
                if (iVar5 == 0) {
                  return (char *)0x0;
                }
                iVar5 = SpriteArrayAddPal(*(int *)(pcVar4 + 0x11c8),local_237c,1,pcVar7);
                if (iVar5 == 0) {
                  return (char *)0x0;
                }
              }
              pcVar6 = pcVar1;
              pcVar7 = pcVar1;
              if (0xb < (int)pcVar1) {
                iVar5 = TPScanf((int)piVar3,"ai","%s",local_101c);
                if (iVar5 == 1) {
                  joindirfile(local_201c,param_1,(char *)local_101c);
                  iVar5 = AILearnDataLoad(local_201c,(undefined4 *)(pcVar4 + 0x21d8));
                  if ((iVar5 == 0) && (stream = fopen(local_201c,"rb"), stream != (FILE *)0x0)) {
                    ClipboardAppend((int *)g[0x81d1],"Ignoring invalid AI file: %s\n",local_101c,
                                    extraout_ECX_02);
                    fclose(stream);
                  }
                  strncpy(pcVar4 + 0x11d8,(char *)local_101c,0xffe);
                }
                TPFree(piVar3);
                fseek(param_2,__off,0);
                return pcVar4;
              }
            } while( true );
          }
          piVar9 = g + 0x81d2;
          pcVar4 = "Can\'t load %s";
          piVar3 = extraout_ECX_00;
        }
      }
    }
  }
LAB_080ae2d6:
  sprintf((char *)piVar9,pcVar4,in_stack_ffffd858,piVar3);
  return (char *)0x0;
}
#undef local_277c
#undef local_237c
#undef local_211c
#undef local_201c
#undef local_101c

/* PlayerCNSLoadTP @ 0x080ae4a0, 2036 bytes
 * FIXUP: 13 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x) */
undefined4 PlayerCNSLoadTP(int param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  undefined3 extraout_var_07;
  undefined3 extraout_var_08;
  undefined3 extraout_var_09;
  undefined3 extraout_var_10;
  undefined3 extraout_var_11;
  int *__s;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int extraout_ECX_03;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int extraout_EDX_02;
  int extraout_EDX_03;
  int extraout_EDX_04;
  int extraout_EDX_05;
  undefined4 extraout_EDX_06;
  int extraout_EDX_07;
  char *pcVar3;
  float *pfVar4;
  undefined4 uVar5;
  
  iVar2 = TPGroupSeek(param_2,"Data");
  if (iVar2 == -1) {
    __s = g + 0x81d2;
    pcVar3 = "Can\'t access Data";
    param_1 = extraout_ECX;
  }
  else {
    bVar1 = TPGetValueInt(param_2,"life",(uint *)(param_1 + 0x10ac));
    iVar2 = extraout_EDX;
    if ((((GHIDRA_ZEXT8(bVar1) == 0) ||
         (bVar1 = TPGetValueInt(param_2,"attack",(uint *)(param_1 + 0x10b4)),
         iVar2 = extraout_EDX_00, GHIDRA_ZEXT8(bVar1) == 0)) ||
        (bVar1 = TPGetValueInt(param_2,"defence",(uint *)(param_1 + 0x10cc)),
        iVar2 = extraout_EDX_01, GHIDRA_ZEXT8(bVar1) == 0)) ||
       (((bVar1 = TPGetValueFloat(param_2,"fall.defence_up",(float *)(param_1 + 0x10d0)),
         iVar2 = extraout_EDX_02, GHIDRA_ZEXT8(bVar1) == 0 ||
         (bVar1 = TPGetValueInt(param_2,"liedown.time",(uint *)(param_1 + 0x10d4)),
         iVar2 = extraout_EDX_03, GHIDRA_ZEXT8(bVar1) == 0)) ||
        (bVar1 = TPGetValueInt(param_2,"airjuggle",(uint *)(param_1 + 0x10c0)),
        iVar2 = extraout_EDX_04, GHIDRA_ZEXT8(bVar1) == 0)))) {
      __s = g + 0x81d2;
      pcVar3 = "Can\'t load Data constants";
      param_1 = iVar2;
    }
    else {
      TPGetValueInt(param_2,"volume",(uint *)(param_1 + 0x11d0));
      *(undefined4 *)(param_1 + 0x10b0) = 3000;
      *(undefined4 *)(param_1 + 0x11a0) = 1;
      *(undefined4 *)(param_1 + 0x11ac) = 0x3c;
      *(undefined4 *)(param_1 + 0x11b0) = 0x28;
      TPGetValueInt(param_2,"power",(uint *)(param_1 + 0x10b0));
      *(float *)(param_1 + 0x10d0) = 100.0 / (*(float *)(param_1 + 0x10d0) + 100.0);
      TPGetValueInt(param_2,"sparkno",(uint *)(param_1 + 0x1198));
      TPGetValueInt(param_2,"guard.sparkno",(uint *)(param_1 + 0x119c));
      TPGetValueInt(param_2,"ko.echo",(uint *)(param_1 + 0x11a0));
      TPGetValueInt(param_2,"IntPersistIndex",(uint *)(param_1 + 0x11ac));
      TPGetValueInt(param_2,"FloatPersistIndex",(uint *)(param_1 + 0x11b0));
      iVar2 = *(int *)(param_1 + 0x11ac);
      if (0x3c < iVar2) {
        *(undefined4 *)(param_1 + 0x11ac) = 0x3c;
        iVar2 = 0x3c;
      }
      if (iVar2 < 0) {
        *(undefined4 *)(param_1 + 0x11ac) = 0;
      }
      iVar2 = *(int *)(param_1 + 0x11b0);
      if (0x28 < iVar2) {
        *(undefined4 *)(param_1 + 0x11b0) = 0x28;
        iVar2 = 0x28;
      }
      if (iVar2 < 0) {
        *(undefined4 *)(param_1 + 0x11b0) = 0;
      }
      iVar2 = TPGroupSeek(param_2,"Size");
      if (iVar2 == -1) {
        __s = g + 0x81d2;
        pcVar3 = "Can\'t access Size constants";
        param_1 = extraout_EDX_05;
      }
      else {
        *(undefined4 *)(param_1 + 0x10dc) = 0x3f800000;
        *(undefined4 *)(param_1 + 0x10d8) = 0x3f800000;
        *(undefined4 *)(param_1 + 0x10c4) = 0xa0;
        *(undefined4 *)(param_1 + 0x10c8) = 0x5a;
        *(undefined4 *)(param_1 + 0x10bc) = 4;
        *(undefined4 *)(param_1 + 0x10b8) = 4;
        *(undefined4 *)(param_1 + 0x10f0) = 3;
        *(undefined4 *)(param_1 + 0x10f4) = 0x3c;
        *(undefined4 *)(param_1 + 0x10fc) = 0xfffffffb;
        *(undefined4 *)(param_1 + 0x1104) = 0xfffffffb;
        *(undefined4 *)(param_1 + 0x1108) = 0xffffffc4;
        *(undefined4 *)(param_1 + 0x1100) = 0xffffffa6;
        bVar1 = TPGetValueInt(param_2,"ground.back",(uint *)(param_1 + 0x10e0));
        iVar2 = extraout_ECX_00;
        if (((GHIDRA_ZEXT8(bVar1) == 0) ||
            (bVar1 = TPGetValueInt(param_2,"ground.front",(uint *)(param_1 + 0x10e4)),
            iVar2 = extraout_ECX_01, GHIDRA_ZEXT8(bVar1) == 0)) ||
           ((bVar1 = TPGetValueInt(param_2,"air.back",(uint *)(param_1 + 0x10e8)),
            iVar2 = extraout_ECX_02, GHIDRA_ZEXT8(bVar1) == 0 ||
            (bVar1 = TPGetValueInt(param_2,"air.front",(uint *)(param_1 + 0x10ec)),
            iVar2 = extraout_ECX_03, GHIDRA_ZEXT8(bVar1) == 0)))) {
          __s = g + 0x81d2;
          pcVar3 = "Can\'t load Size constants";
          param_1 = iVar2;
        }
        else {
          uVar5 = extraout_EDX_06;
          TPGetValueInt(param_2,"height",(uint *)(param_1 + 0x10f4));
          TPGetValueInt(param_2,"z.width",(uint *)(param_1 + 0x10f0));
          TPGetValueFloat(param_2,"xscale",(float *)(param_1 + 0x10d8));
          pfVar4 = (float *)(param_1 + 0x10dc);
          pcVar3 = "yscale";
          TPGetValueFloat(param_2,"yscale",pfVar4);
          TPScanf(param_2,"draw.offset","%i,%i",param_1 + 0x11a4,param_1 + 0x11a8,pcVar3,pfVar4,
                  uVar5);
          TPScanf(param_2,"attack.z.width","%i,%i",param_1 + 0x10b8,param_1 + 0x10bc);
          TPGetValueInt(param_2,"attack.dist",(uint *)(param_1 + 0x10c4));
          TPGetValueInt(param_2,"proj.attack.dist",(uint *)(param_1 + 0x10c8));
          TPGetValueInt(param_2,"proj.doscale",(uint *)(param_1 + 0x10f8));
          TPScanf(param_2,"head.pos","%i,%i",param_1 + 0x10fc,param_1 + 0x1100);
          TPScanf(param_2,"mid.pos","%i,%i",param_1 + 0x1104,param_1 + 0x1108);
          TPGetValueInt(param_2,"shadowoffset",(uint *)(param_1 + 0x110c));
          iVar2 = TPGroupSeek(param_2,"Velocity");
          iVar2 = iVar2 + 1;
          if (iVar2 == 0) {
            __s = g + 0x81d2;
            pcVar3 = "Can\'t access Velocity constants";
            param_1 = extraout_EDX_07;
          }
          else {
            TPGetValueFloat(param_2,"walk.fwd",(float *)(param_1 + 0x1110));
            TPGetValueFloat(param_2,"walk.back",(float *)(param_1 + 0x1114));
            TPGetValueFloat(param_2,"walk.up",(float *)(param_1 + 0x1118));
            pfVar4 = (float *)(param_1 + 0x111c);
            pcVar3 = "walk.down";
            TPGetValueFloat(param_2,"walk.down",pfVar4);
            TPScanf(param_2,"run.fwd","%f,%f",param_1 + 0x1120,param_1 + 0x1124,pcVar3,pfVar4,iVar2)
            ;
            TPScanf(param_2,"run.back","%f,%f",param_1 + 0x1128,param_1 + 0x112c);
            TPScanf(param_2,"run.up","%f,%f",param_1 + 0x1138,param_1 + 0x113c);
            TPScanf(param_2,"run.down","%f,%f",param_1 + 0x1130,param_1 + 0x1134);
            TPScanf(param_2,"jump.neu","%f,%f",param_1 + 0x1144,param_1 + 0x1140);
            TPScanf(param_2,"jump.fwd","%f",param_1 + 0x1148);
            TPScanf(param_2,"jump.back","%f",param_1 + 0x114c);
            TPScanf(param_2,"jump.down","%f",param_1 + 0x1154);
            TPScanf(param_2,"jump.up","%f",param_1 + 0x1150);
            *(undefined4 *)(param_1 + 0x1178) = *(undefined4 *)(param_1 + 0x1144);
            *(undefined4 *)(param_1 + 0x1174) = *(undefined4 *)(param_1 + 0x1140);
            *(undefined4 *)(param_1 + 0x115c) = *(undefined4 *)(param_1 + 0x1148);
            *(undefined4 *)(param_1 + 0x117c) = *(undefined4 *)(param_1 + 0x1148);
            *(undefined4 *)(param_1 + 0x1160) = *(undefined4 *)(param_1 + 0x114c);
            *(undefined4 *)(param_1 + 0x1180) = *(undefined4 *)(param_1 + 0x114c);
            *(undefined4 *)(param_1 + 0x1164) = *(undefined4 *)(param_1 + 0x1150);
            *(undefined4 *)(param_1 + 0x1184) = *(undefined4 *)(param_1 + 0x1150);
            *(undefined4 *)(param_1 + 0x1168) = *(undefined4 *)(param_1 + 0x1154);
            *(undefined4 *)(param_1 + 0x1188) = *(undefined4 *)(param_1 + 0x1154);
            TPScanf(param_2,"runjump.fwd","%f,%f",param_1 + 0x115c,param_1 + 0x1158);
            TPScanf(param_2,"runjump.back","%f",param_1 + 0x1160);
            TPScanf(param_2,"runjump.down","%f",param_1 + 0x1168);
            TPScanf(param_2,"runjump.up","%f",param_1 + 0x1164);
            TPScanf(param_2,"airjump.neu","%f,%f",param_1 + 0x1178,param_1 + 0x1174);
            TPScanf(param_2,"airjump.fwd","%f",param_1 + 0x117c);
            TPScanf(param_2,"airjump.back","%f",param_1 + 0x1180);
            TPScanf(param_2,"airjump.down","%f",param_1 + 0x1188);
            TPScanf(param_2,"airjump.up","%f",param_1 + 0x1184);
            iVar2 = TPGroupSeek(param_2,"Movement");
            if (iVar2 == -1) {
              __s = g + 0x81d2;
              pcVar3 = "Can\'t access Movement constants";
            }
            else {
              bVar1 = TPGetValueFloat(param_2,"yaccel",(float *)(param_1 + 0x118c));
              if (((GHIDRA_ZEXT8(bVar1) != 0) &&
                  (bVar1 = TPGetValueFloat(param_2,"stand.friction",(float *)(param_1 + 0x1190)),
                  GHIDRA_ZEXT8(bVar1) != 0)) &&
                 (bVar1 = TPGetValueFloat(param_2,"crouch.friction",(float *)(param_1 + 0x1194)),
                 GHIDRA_ZEXT8(bVar1) != 0)) {
                TPGetValueInt(param_2,"airjump.num",(uint *)(param_1 + 0x116c));
                TPGetValueInt(param_2,"airjump.height",(uint *)(param_1 + 0x1170));
                return 1;
              }
              __s = g + 0x81d2;
              pcVar3 = "Can\'t load movement constants";
            }
          }
        }
      }
    }
  }
  sprintf((char *)__s,pcVar3,param_1,param_1);
  return 0;
}

/* PlayerSTLoadTP @ 0x080aeca0, 39 bytes */
bool PlayerSTLoadTP(int param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = SctrlReadFileTP(param_2,param_1);
  *(int **)(param_1 + 0x11c4) = piVar1;
  return piVar1 != (int *)0x0;
}

/* PlayerSTLoadAppend @ 0x080aecd0, 75 bytes */
undefined4 PlayerSTLoadAppend(int param_1,char *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = TPReadFile(param_2);
  if ((puVar1 != (undefined4 *)0x0) &&
     (iVar2 = SctrlAddFileTP(*(int **)(param_1 + 0x11c4),(int)puVar1,param_1), iVar2 != 0)) {
    TPFree(puVar1);
    return 1;
  }
  return 0;
}

/* PlayerCMDLoad @ 0x080aed20, 101 bytes */
undefined4 PlayerCMDLoad(char *param_1,uint *param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_ECX;
  
  puVar1 = TPReadFile(param_1);
  if (puVar1 == (undefined4 *)0x0) {
    sprintf((char *)(g + 0x81d2),"Can\'t open file",extraout_ECX,extraout_ECX);
    uVar2 = 0;
  }
  else {
    iVar3 = PlayerCMDLoadTP((uint)puVar1,param_2);
    if (iVar3 == 0) {
      uVar2 = 0;
    }
    else {
      TPFree(puVar1);
      uVar2 = 1;
    }
  }
  return uVar2;
}

/* PlayerCMDLoadTP @ 0x080aed90, 1648 bytes
 * FIXUP: frame emulation: 7 stack locals placed at their original offsets in a 0x80-byte frame (a local's address escapes, see apply_frame_emulation) */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

undefined4 PlayerCMDLoadTP(uint param_1,uint *param_2)

{
  char *pcVar1;
  uint uVar2;
  undefined4 *puVar3;
  byte *__s;
  size_t sVar4;
  int *piVar5;
  void *pvVar6;
  uint uVar7;
  size_t sVar8;
  int iVar9;
  uint extraout_EDX;
  uint uVar10;
  void **ppvVar11;
  byte *pbVar12;
  int *piVar13;
  byte *pbVar14;
  bool bVar15;
  bool bVar16;
  unsigned char ghidra_frame[0x80] __attribute__((aligned(16)));
#define local_74 (*(uint *)(ghidra_frame + 0xc))
#define local_6c (*(uint *)(ghidra_frame + 0x14))
#define local_68 (*(int *)(ghidra_frame + 0x18))
#define local_64 (*(uint *)(ghidra_frame + 0x1c))
#define local_60 (*(uint *)(ghidra_frame + 0x20))
#define local_5c (*(undefined4 (*)[8])(ghidra_frame + 0x24))
#define local_3c (*(int (*)[11])(ghidra_frame + 0x44))
  
  local_6c = 1;
  piVar5 = &INT_08287d24;
  piVar13 = local_3c;
  for (iVar9 = 7; iVar9 != 0; iVar9 = iVar9 + -1) {
    *piVar13 = *piVar5;
    piVar5 = piVar5 + 1;
    piVar13 = piVar13 + 1;
  }
  ppvVar11 = &PTR_s_a_0828363f_0x14_08287d40;
  puVar3 = local_5c;
  for (iVar9 = 7; iVar9 != 0; iVar9 = iVar9 + -1) {
    *puVar3 = *ppvVar11;
    ppvVar11 = ppvVar11 + 1;
    puVar3 = puVar3 + 1;
  }
  local_64 = 0xf;
  local_60 = 1;
  iVar9 = TPGroupSeek(param_1,"defaults");
  if (iVar9 != -1) {
    TPGetValueInt(param_1,"command.time",&local_64);
    if ((int)local_64 < 1) {
      local_64 = 1;
    }
    TPGetValueInt(param_1,"command.buffer.time",&local_60);
    if ((int)local_60 < 1) {
      local_60 = 1;
    }
    if (0x1e < (int)local_60) {
      local_60 = 0x1e;
    }
  }
  iVar9 = TPGroupSeek(param_1,"remap");
  if (iVar9 != -1) {
    local_68 = 0;
    do {
      pcVar1 = TPGetValue(param_1,(char *)local_5c[local_68]);
      if (pcVar1 != (char *)0x0) {
        switch(*pcVar1) {
        case 'a':
          local_3c[local_68] = 0x10;
          break;
        case 'b':
          local_3c[local_68] = 0x20;
          break;
        case 'c':
          local_3c[local_68] = 0x40;
          break;
        default:
          local_3c[local_68] = 1;
          break;
        case 's':
          local_3c[local_68] = 0x400;
          break;
        case 'x':
          local_3c[local_68] = 0x80;
          break;
        case 'y':
          local_3c[local_68] = 0x100;
          break;
        case 'z':
          local_3c[local_68] = 0x200;
        }
      }
      local_68 = local_68 + 1;
    } while (local_68 < 7);
  }
  uVar2 = TPGroupMatchCount(param_1,"command");
  param_2[2] = uVar2;
  uVar7 = param_1;
  if (uVar2 == 0) {
    piVar5 = g + 0x81d2;
    pcVar1 = "Need at least 1 command";
LAB_080af160:
    sprintf((char *)piVar5,pcVar1,param_1,uVar7);
  }
  else {
    uVar2 = ecalloc(1,uVar2 * 0x18);
    *param_2 = uVar2;
    if (uVar2 != 0) {
      puVar3 = malloc(param_2[2] << 2);
      param_2[1] = (uint)puVar3;
      if (puVar3 != (undefined4 *)0x0) {
        for (uVar2 = param_2[2] & 0x3fffffff; uVar2 != 0; uVar2 = uVar2 - 1) {
          *puVar3 = 0;
          puVar3 = puVar3 + 1;
        }
        iVar9 = TPGroupScanFirst(param_1);
        local_68 = 0;
        if (0 < (int)param_2[2]) {
          local_74 = 0;
          do {
            while (iVar9 = strimatch((char *)(iVar9 + 1),"command"), iVar9 == 0) {
              iVar9 = TPGroupScanNext(param_1);
            }
            __s = (byte *)TPGetValue(param_1,"name");
            if (__s == (byte *)0x0) {
              pcVar1 = "Command %i missing name parameter";
              uVar7 = extraout_EDX;
LAB_080af15b:
              param_1 = local_68 + 1;
              piVar5 = g + 0x81d2;
              goto LAB_080af160;
            }
            if ((*__s != 0x22) || (sVar4 = strlen((char *)__s), __s[sVar4 - 1] != 0x22)) {
              pcVar1 = "Command %i name not in quotes";
              goto LAB_080af15b;
            }
            sVar4 = strlen((char *)__s);
            pvVar6 = malloc(sVar4 - 1);
            *(void **)(param_2[1] + local_68 * 4) = pvVar6;
            if (pvVar6 == (void *)0x0) {
              return 0;
            }
            sVar4 = strlen((char *)__s);
            strncpy(*(char **)(param_2[1] + local_68 * 4),(char *)(__s + 1),sVar4 - 2);
            uVar7 = param_2[1];
            sVar4 = strlen((char *)__s);
            uVar7 = *(uint *)(uVar7 + local_68 * 4);
            bVar15 = CARRY4(sVar4,uVar7);
            *(undefined1 *)(sVar4 + uVar7 + -2) = 0;
            uVar2 = *param_2;
            *(uint *)(uVar2 + 0x10 + local_74) = local_6c;
            uVar10 = local_6c + 1;
            bVar16 = uVar10 == 0;
            *(undefined4 *)(uVar2 + 0x14 + local_74) = 1;
            iVar9 = 0xb;
            pbVar12 = __s;
            pbVar14 = (byte *)"\"recovery\"";
            do {
              if (iVar9 == 0) break;
              iVar9 = iVar9 + -1;
              bVar15 = *pbVar12 < *pbVar14;
              bVar16 = *pbVar12 == *pbVar14;
              pbVar12 = pbVar12 + 1;
              pbVar14 = pbVar14 + 1;
            } while (bVar16);
            uVar7 = (uint)bVar15;
            if ((!bVar15 && !bVar16) == bVar15) {
              *(undefined4 *)(uVar2 + 0x10 + local_74) = 0;
              *(undefined4 *)(uVar2 + 0x14 + local_74) = 2;
              uVar7 = local_74;
            }
            else {
              iVar9 = local_68 + -1;
              if (-1 < iVar9) {
                uVar2 = param_2[1];
                do {
                  sVar4 = strlen((char *)__s);
                  uVar7 = strncmp((char *)(__s + 1),*(char **)(uVar2 + iVar9 * 4),sVar4 - 2);
                  if (uVar7 == 0) {
                    sVar4 = strlen(*(char **)(uVar2 + iVar9 * 4));
                    sVar8 = strlen((char *)__s);
                    uVar7 = sVar8 - 2;
                    if (sVar4 == uVar7) {
                      uVar7 = *param_2;
                      *(undefined4 *)(uVar7 + 0x10 + local_74) =
                           *(undefined4 *)(uVar7 + 0x10 + iVar9 * 0x18);
                      uVar10 = local_6c;
                      break;
                    }
                  }
                  iVar9 = iVar9 + -1;
                } while (-1 < iVar9);
              }
            }
            local_6c = uVar10;
            if (0x7f < (int)local_6c) {
              param_1 = 0x80;
              piVar5 = g + 0x81d2;
              pcVar1 = "Player has too many commands. Only %i unique commands labels allowed.";
              goto LAB_080af160;
            }
            pcVar1 = TPGetValue(param_1,"command");
            if (pcVar1 == (char *)0x0) {
              uVar7 = *(uint *)(param_2[1] + local_68 * 4);
              pcVar1 = "Command %i \"%s\" missing command parameter";
              goto LAB_080af15b;
            }
            uVar7 = *param_2;
            iVar9 = ParseCMD((int *)(local_74 + uVar7),pcVar1,local_3c);
            if (iVar9 == 0) {
              strcat((char *)(g + 0x81d2),"\nError in command: ");
              strcat((char *)(g + 0x81d2),*(char **)(param_2[1] + local_68 * 4));
              return 0;
            }
            uVar2 = *param_2;
            *(uint *)(uVar2 + 8 + local_74) = local_64;
            TPGetValueInt(param_1,"time",(uint *)(local_74 + 8 + uVar2));
            uVar2 = *param_2;
            *(uint *)(uVar2 + 0xc + local_74) = local_60;
            TPGetValueInt(param_1,"buffer.time",(uint *)(local_74 + 0xc + uVar2));
            if (0x1e < *(int *)(*param_2 + 0xc + local_74)) {
              *(undefined4 *)(*param_2 + 0xc + local_74) = 0x1e;
            }
            iVar9 = TPGroupScanNext(param_1);
            local_74 = local_74 + 0x18;
            local_68 = local_68 + 1;
          } while (local_68 < (int)param_2[2]);
        }
        param_2[3] = local_6c;
        return 1;
      }
    }
  }
  return 0;
}
#undef local_74
#undef local_6c
#undef local_68
#undef local_64
#undef local_60
#undef local_5c
#undef local_3c

/* ParseCMD @ 0x080af400, 629 bytes
 * FIXUP: frame emulation: 5 stack locals placed at their original offsets in a 0x840-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 ParseCMD(int *param_1,char *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  int iVar5;
  uint *puVar6;
  bool bVar7;
  unsigned char ghidra_frame[0x840] __attribute__((aligned(16)));
#define local_834 (*(uint *)(ghidra_frame + 0xc))
#define local_830 (*(uint *)(ghidra_frame + 0x10))
#define local_82c (*(int *)(ghidra_frame + 0x14))
#define local_828 (*(uint *)(ghidra_frame + 0x18))
#define local_824 (*(uint (*)[517])(ghidra_frame + 0x1c))
  
  iVar5 = 0;
  local_82c = 0;
  puVar6 = local_824 + 2;
  for (iVar2 = 0x200; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  cVar4 = *param_2;
  while (cVar4 != '\0') {
    local_830 = 0;
    iVar2 = 0;
    if (((*(byte *)(__ctype_b + 1 + param_2[iVar5] * 2) & 0x20) != 0) && (cVar4 != '\0')) {
      do {
        iVar5 = iVar5 + 1;
        if ((*(byte *)(__ctype_b + 1 + param_2[iVar5] * 2) & 0x20) == 0) {
          cVar4 = param_2[iVar5];
          goto LAB_080af478;
        }
      } while (param_2[iVar5] != '\0');
      cVar4 = '\0';
    }
LAB_080af478:
    if (cVar4 == '\0') goto LAB_080af630;
    bVar7 = cVar4 == '>';
    if (bVar7) {
      iVar5 = iVar5 + 1;
      cVar4 = param_2[iVar5];
    }
    local_834 = (uint)bVar7;
    if (cVar4 == '/') {
      iVar5 = iVar5 + 1;
      local_830 = 0x20000;
      cVar4 = param_2[iVar5];
    }
    if (cVar4 == '~') {
      while( true ) {
        iVar5 = iVar5 + 1;
        cVar4 = param_2[iVar5];
        if (9 < (byte)(cVar4 - 0x30U)) break;
        iVar2 = param_2[iVar5] + -0x30 + iVar2 * 10;
      }
      local_830 = local_830 | 0x10000 | (iVar2 >> 2) << 0x16;
    }
    if (cVar4 == '$') {
      iVar5 = iVar5 + 1;
      local_830 = local_830 | 0x40000;
    }
    local_824[0] = 0;
    local_824[1] = 0;
    cVar4 = param_2[iVar5];
    do {
      if (cVar4 == '+') {
        iVar5 = iVar5 + 1;
      }
      iVar2 = ParseCMDElem(param_2 + iVar5,&local_828,param_3);
      if (iVar2 == 0) goto LAB_080af630;
      uVar3 = local_828 | local_824[0];
      iVar5 = iVar5 + iVar2;
      cVar4 = param_2[iVar5];
      local_824[0] = uVar3;
    } while (cVar4 == '+');
    local_824[0] = uVar3 | local_830;
    local_824[1] = local_824[1] | local_834;
    if (((0 < local_82c) && (local_824[0] == local_824[local_82c * 2])) && ((uVar3 & 0x8f000) != 0))
    {
      local_824[local_82c * 2 + 2] = local_824[local_82c * 2];
      local_824[local_82c * 2 + 3] = local_824[local_82c * 2 + 1];
      local_824[local_82c * 2 + 2] = local_824[local_82c * 2 + 2] | 0x10000;
      local_824[local_82c * 2 + 3] = local_824[local_82c * 2 + 3] | 1;
      local_82c = local_82c + 1;
      local_824[1] = local_824[1] | 1;
    }
    local_824[local_82c * 2 + 3] = local_824[1];
    local_824[local_82c * 2 + 2] = local_824[0];
    local_82c = local_82c + 1;
    if (0x100 < local_82c) goto LAB_080af630;
    for (; (cVar4 = param_2[iVar5], cVar4 != ',' && (cVar4 != '\0')); iVar5 = iVar5 + 1) {
    }
    if (cVar4 == '\0') break;
    iVar5 = iVar5 + 1;
    cVar4 = param_2[iVar5];
  }
  iVar5 = ecalloc(1,local_82c << 3);
  *param_1 = iVar5;
  if (iVar5 == 0) {
LAB_080af630:
    uVar1 = 0;
  }
  else {
    iVar2 = 0;
    if (0 < local_82c) {
      do {
        uVar3 = local_824[iVar2 * 2 + 2];
        *(uint *)(iVar5 + 4 + iVar2 * 8) = local_824[iVar2 * 2 + 3];
        *(uint *)(iVar5 + iVar2 * 8) = uVar3;
        iVar2 = iVar2 + 1;
      } while (iVar2 < local_82c);
    }
    param_1[1] = local_82c;
    uVar1 = 1;
  }
  return uVar1;
}
#undef local_834
#undef local_830
#undef local_82c
#undef local_828
#undef local_824

/* ParseCMDElem @ 0x080af680, 249 bytes */
undefined4 ParseCMDElem(undefined1 *param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  switch(*param_1) {
  case 0x42:
    *param_2 = 0x8000;
    break;
  default:
    uVar1 = 0;
    break;
  case 0x44:
    if (param_1[1] == 'B') {
      *param_2 = 0xc000;
      uVar1 = 2;
    }
    else if (param_1[1] == 'F') {
      *param_2 = 0x6000;
      uVar1 = 2;
    }
    else {
      *param_2 = 0x4000;
    }
    break;
  case 0x46:
    *param_2 = 0x2000;
    break;
  case 0x4e:
    *param_2 = 0x80000;
    break;
  case 0x55:
    if (param_1[1] == 'B') {
      *param_2 = 0x9000;
      uVar1 = 2;
    }
    else if (param_1[1] == 'F') {
      *param_2 = 0x3000;
      uVar1 = 2;
    }
    else {
      *param_2 = 0x1000;
    }
    break;
  case 0x61:
    *param_2 = *param_3;
    break;
  case 0x62:
    *param_2 = param_3[1];
    break;
  case 99:
    *param_2 = param_3[2];
    break;
  case 0x73:
    *param_2 = param_3[6];
    break;
  case 0x78:
    *param_2 = param_3[3];
    break;
  case 0x79:
    *param_2 = param_3[4];
    break;
  case 0x7a:
    *param_2 = param_3[5];
  }
  return uVar1;
}

/* CmdSetFreeLabel @ 0x080af780, 33 bytes */
void CmdSetFreeLabel(int param_1)

{
  StringArrayFree(*(void **)(param_1 + 4),*(int *)(param_1 + 8));
  *(undefined4 *)(param_1 + 4) = 0;
  return;
}

/* StringArrayFree @ 0x080af7b0, 68 bytes */
void StringArrayFree(void *param_1,int param_2)

{
  void *__ptr;
  int iVar1;
  
  if (param_1 != (void *)0x0) {
    iVar1 = 0;
    if (0 < param_2) {
      do {
        __ptr = *(void **)((int)param_1 + iVar1 * 4);
        if (__ptr != (void *)0x0) {
          free(__ptr);
        }
        iVar1 = iVar1 + 1;
      } while (iVar1 < param_2);
    }
    free(param_1);
    return;
  }
  return;
}

/* CmdSetDeInit @ 0x080af800, 100 bytes */
void CmdSetDeInit(int *param_1)

{
  void *__ptr;
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (param_1 == (int *)0x0) {
    return;
  }
  iVar2 = *param_1;
  if (iVar2 != 0) {
    iVar3 = 0;
    iVar1 = param_1[2];
    if (0 < iVar1) {
      while( true ) {
        __ptr = *(void **)(iVar2 + iVar3 * 0x18);
        if (__ptr != (void *)0x0) {
          free(__ptr);
          iVar1 = param_1[2];
        }
        iVar3 = iVar3 + 1;
        if (iVar1 <= iVar3) break;
        iVar2 = *param_1;
      }
    }
    free((void *)*param_1);
  }
  CmdSetFreeLabel((int)param_1);
  return;
}

/* PlayerRCFree @ 0x080af870, 116 bytes */
void PlayerRCFree(void *param_1)

{
  if (param_1 != (void *)0x0) {
    AIStateSetDeInit((undefined4 *)((int)param_1 + 0x21d8));
    CmdSetDeInit((int *)((int)param_1 + 0x11b4));
    SCtrlRCFree(*(undefined4 **)((int)param_1 + 0x11c4));
    SpriteArrayFree(*(int **)((int)param_1 + 0x11c8));
    AnimRCFree(*(int **)((int)param_1 + 0x11cc));
    SndArrayFree(*(undefined4 **)((int)param_1 + 0x11d4));
    free(param_1);
    return;
  }
  return;
}

/* PlayerNew @ 0x080af8f0, 969 bytes
 * REVIEW: pid-unaff_ */
int * PlayerNew(int param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int *piVar3;
  int *extraout_ECX;
  int iVar4;
  int *extraout_ECX_00;
  int *extraout_ECX_01;
  int *extraout_EDX;
  int *extraout_EDX_00;
  int *unaff_EDI;
  char *__format;
  
  piVar1 = (int *)ecalloc(1,0x3464);
  if (piVar1 == (int *)0x0) {
    piVar3 = g + 0x81d2;
    __format = "Out of memory for player.";
    unaff_EDI = extraout_ECX;
  }
  else {
    piVar1[7] = (uint)(param_1 == 0);
    *piVar1 = param_1;
    if (param_1 != 0) {
      piVar1[0x259] = param_1 + 0x11b4;
    }
    piVar3 = g;
    piVar1[1] = g[0x749d];
    piVar3[0x749d] = piVar3[0x749d] + 1;
    piVar1[4] = -1;
    if (param_1 != 0) {
      piVar3 = (int *)(param_1 + 0x10ac);
      unaff_EDI = piVar1 + 0x14;
      for (iVar4 = 0x42; iVar4 != 0; iVar4 = iVar4 + -1) {
        *unaff_EDI = *piVar3;
        piVar3 = piVar3 + 1;
        unaff_EDI = unaff_EDI + 1;
      }
    }
    puVar2 = SpriteArrayNewSize(0,g[0x7577]);
    piVar1[0x4ec] = (int)puVar2;
    if (puVar2 == (undefined4 *)0x0) {
      piVar3 = g + 0x81d2;
      __format = "Out of memory for sprite\n";
      unaff_EDI = piVar1;
    }
    else {
      if (param_1 == 0) {
        piVar1[0x4ee] = 0;
      }
      else {
        piVar3 = SpriteArrayNewInstanceOnto((int *)piVar1[0x4ec],*(int **)(param_1 + 0x11c8));
        if (piVar3 == (int *)0x0) {
          piVar3 = g + 0x81d2;
          __format = "Out of memory for sprite\n";
          goto LAB_080afc20;
        }
        piVar3 = SpriteArrayNewInstance((int *)piVar1[0x4ec]);
        piVar1[0x4ee] = (int)piVar3;
        if (piVar3 == (int *)0x0) {
          piVar3 = g + 0x81d2;
          __format = "Out of memory for sprite\n";
          unaff_EDI = piVar1;
          goto LAB_080afc20;
        }
      }
      piVar1[0x4eb] = piVar1[0x4ec];
      piVar1[0x4ed] = piVar1[0x4ee];
      if (param_1 == 0) {
        puVar2 = AnimNew(0,0);
        piVar1[0x4ef] = (int)puVar2;
        if (puVar2 == (undefined4 *)0x0) {
          piVar3 = g + 0x81d2;
          __format = "Out of memory for anim\n";
          unaff_EDI = extraout_ECX_00;
          goto LAB_080afc20;
        }
      }
      else {
        puVar2 = AnimNew(*(undefined4 *)(param_1 + 0x11cc),piVar1[0x4ec]);
        piVar1[0x4ef] = (int)puVar2;
        if (puVar2 == (undefined4 *)0x0) {
          piVar3 = g + 0x81d2;
          __format = "Out of memory for anim\n";
          goto LAB_080afc20;
        }
      }
      piVar3 = g;
      *(int *)(piVar1[0x4ef] + 0x30) = g[0x413d];
      if (param_1 == 0) {
        iVar4 = ProjArrayNew(piVar3[0x7576],0,0);
        piVar1[0x87] = iVar4;
        if (iVar4 == 0) {
          piVar3 = g + 0x81d2;
          __format = "Can\'t create projectile array.";
          goto LAB_080afc20;
        }
      }
      else {
        unaff_EDI = *(int **)(param_1 + 0x11cc);
        iVar4 = ProjArrayNew(piVar3[0x7576],unaff_EDI,piVar1[0x4ed]);
        piVar1[0x87] = iVar4;
        if (iVar4 == 0) {
          piVar3 = g + 0x81d2;
          __format = "Can\'t create projectile array.";
          unaff_EDI = extraout_ECX_01;
          goto LAB_080afc20;
        }
      }
      if (param_1 == 0) {
        iVar4 = SCtrlInit(piVar1 + 0x2fa,0);
        if (iVar4 == 0) {
          piVar3 = g + 0x81d2;
          __format = "Can\'t create state controller.";
          goto LAB_080afc20;
        }
      }
      else {
        iVar4 = SCtrlInit(piVar1 + 0x2fa,*(undefined4 *)(param_1 + 0x11c4));
        if (iVar4 == 0) {
          piVar3 = g + 0x81d2;
          __format = "Can\'t create state controller.";
          unaff_EDI = extraout_EDX;
          goto LAB_080afc20;
        }
      }
      if (param_1 != 0) {
        iVar4 = PlayerAIInit((int)piVar1,1);
        if (iVar4 == 0) {
          piVar3 = g + 0x81d2;
          __format = "Can\'t create state controller.";
          unaff_EDI = piVar1;
          goto LAB_080afc20;
        }
        iVar4 = GetRampedAILevel();
        PlayerAISetLevel((int)piVar1,iVar4);
        if (piVar1[0xb6b] != 0) {
          AIStateSetCopy((int)(piVar1 + 0xb6c),param_1 + 0x21d8);
        }
      }
      puVar2 = ArrayNew(8,0x20,0);
      piVar1[0x88] = (int)puVar2;
      if (puVar2 != (undefined4 *)0x0) {
        iVar4 = ecalloc(g[0x7395] + 1,4);
        piVar1[0x455] = iVar4;
        if (iVar4 == 0) {
          return (int *)0x0;
        }
        iVar4 = ecalloc(g[0x7395] + 1,4);
        piVar1[0x452] = iVar4;
        if (iVar4 == 0) {
          return (int *)0x0;
        }
        if ((char *)*piVar1 != (char *)0x0) {
          strcpy((char *)(piVar1 + 8),(char *)*piVar1);
        }
        piVar3 = ClipboardNew(0x4d,3);
        piVar1[0xd17] = (int)piVar3;
        if (piVar3 == (int *)0x0) {
          return (int *)0x0;
        }
        PlayerReset(piVar1);
        return piVar1;
      }
      piVar3 = g + 0x81d2;
      __format = "Can\'t create target array.";
      unaff_EDI = extraout_EDX_00;
    }
  }
LAB_080afc20:
  sprintf((char *)piVar3,__format,unaff_EDI,unaff_EDI);
  return (int *)0x0;
}

/* GetRampedAILevel @ 0x080afcc0, 257 bytes */
int GetRampedAILevel(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  piVar3 = (int *)0x0;
  iVar2 = g[0x7543] + -1;
  iVar5 = g[0x799e];
  if (g[0x33b3] != 0) {
    piVar3 = g + 0x7580;
    iVar4 = 2 - g[0x33b3];
    if ((g[iVar4 * 0x6a7 + 0x33bb] != 0) || (1 < g[iVar4 * 0x6a7 + 0x33b9])) {
      piVar3 = g + 0x7584;
    }
  }
  if (g[0x33b4] != 0) {
    piVar3 = g + 0x7588;
    iVar5 = 4;
    iVar2 = g[0x7506];
  }
  if (piVar3 != (int *)0x0) {
    iVar4 = *piVar3;
    if (iVar4 < iVar2) {
      iVar1 = piVar3[2];
      if (iVar2 < iVar1) {
        if (iVar4 < iVar1) {
          iVar5 = iVar5 + ((iVar2 - iVar4) * (piVar3[3] - piVar3[1])) / (iVar1 - iVar4) + piVar3[1];
        }
      }
      else {
        iVar5 = iVar5 + piVar3[3];
      }
    }
    else {
      iVar5 = iVar5 + piVar3[1];
    }
    if (iVar5 < 1) {
      iVar5 = 1;
    }
    if (8 < iVar5) {
      iVar5 = 8;
    }
  }
  return iVar5;
}

/* PlayerChangePal @ 0x080afdd0, 417 bytes */
undefined4 PlayerChangePal(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 extraout_EDX_03;
  undefined4 uVar4;
  int *piVar5;
  undefined4 uVar6;
  
  iVar1 = SpriteArrayGetNum(*(int **)(param_1 + 0x13ac),0,0);
  if ((iVar1 != -1) && (*(int *)(*(int *)(param_1 + 0x13ac) + 0xc) != 0)) {
    iVar1 = SpriteArrayAccess(*(int **)(param_1 + 0x13ac),iVar1);
    iVar1 = *(int *)(iVar1 + 0x30);
    iVar2 = SpriteArrayPalGetNum(*(int *)(*(int *)(param_1 + 0x13ac) + 0xc),1,param_2);
    if (iVar2 == -1) {
      iVar2 = SpriteArrayPalGetNum(*(int *)(*(int *)(param_1 + 0x13ac) + 0xc),1,0);
      if (iVar2 == -1) {
        iVar2 = SpriteArrayPalGetNum(*(int *)(*(int *)(param_1 + 0x13ac) + 0xc),0,0);
      }
    }
    if ((iVar1 != -1) && (iVar2 != -1)) {
      SpriteArrayPalRemapFromRoot(*(int *)(param_1 + 0x13ac),iVar1,iVar2);
    }
  }
  iVar1 = SpriteArrayGetNum(*(int **)(param_1 + 0x13ac),9000,0);
  uVar4 = extraout_EDX;
  if ((iVar1 != -1) && (*(int *)(*(int *)(param_1 + 0x13ac) + 0xc) != 0)) {
    iVar1 = SpriteArrayAccess(*(int **)(param_1 + 0x13ac),iVar1);
    iVar1 = *(int *)(iVar1 + 0x30);
    iVar2 = SpriteArrayPalGetNum(*(int *)(*(int *)(param_1 + 0x13ac) + 0xc),1,param_2);
    uVar4 = extraout_EDX_00;
    if (iVar2 == -1) {
      iVar2 = SpriteArrayPalGetNum(*(int *)(*(int *)(param_1 + 0x13ac) + 0xc),1,0);
      uVar4 = extraout_EDX_01;
      if (iVar2 == -1) {
        iVar2 = SpriteArrayPalGetNum(*(int *)(*(int *)(param_1 + 0x13ac) + 0xc),0,0);
        uVar4 = extraout_EDX_02;
      }
    }
    if ((iVar1 != -1) && (iVar2 != -1)) {
      SpriteArrayPalRemapFromRoot(*(int *)(param_1 + 0x13ac),iVar1,iVar2);
      uVar4 = extraout_EDX_03;
    }
  }
  if (*(int *)(param_1 + 0x13b8) != 0) {
    piVar5 = *(int **)(param_1 + 0x13ac);
    uVar6 = uVar4;
    piVar3 = SpriteArrayNewInstanceOnto(*(int **)(param_1 + 0x13b8),piVar5);
    if (piVar3 == (int *)0x0) {
      ErrorExitM("Out of memory for sprite\n",piVar5,uVar4,uVar6);
    }
  }
  return 1;
}

/* PlayerFree @ 0x080aff80, 260 bytes
 * REVIEW: pid-unaff_
 * FIXUP: return type set to void: only unaffected-register values were returned */
void PlayerFree(int *param_1)

{
  int iVar1;
  undefined4 extraout_EAX;
  undefined4 unaff_EBX;
  
  if (param_1 != (int *)0x0) {
    if (param_1[0xb6b] != 0) {
      AIStateSetMerge(*param_1 + 0x21d8,(int)(param_1 + 0xb6c));
    }
    if ((undefined4 *)param_1[0xd17] != (undefined4 *)0x0) {
      ClipboardFree((undefined4 *)param_1[0xd17]);
    }
    PlayerAIDeInit((int)param_1);
    ArrayFree((void *)param_1[0x88]);
    ProjArrayFree((undefined4 *)param_1[0x87]);
    iVar1 = param_1[0x4e5];
    if (iVar1 != 0) {
      *(undefined4 *)(iVar1 + 0x18) = 0;
      *(undefined4 *)(iVar1 + 8) = 0;
      param_1[0x4e5] = 0;
    }
    if ((int *)param_1[0x4ee] != (int *)0x0) {
      SpriteArrayFree((int *)param_1[0x4ee]);
    }
    SpriteArrayFree((int *)param_1[0x4ec]);
    AnimFree((void *)param_1[0x4ef]);
    if ((void *)param_1[0x455] != (void *)0x0) {
      free((void *)param_1[0x455]);
    }
    if ((void *)param_1[0x452] != (void *)0x0) {
      free((void *)param_1[0x452]);
    }
    free(param_1);
    return;
  }
  return;
}

/* PlayerCheck @ 0x080b0090, 569 bytes
 * REVIEW: pid-unaff_
 * FIXUP: frame emulation: 4 stack locals placed at their original offsets in a 0x320-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 PlayerCheck(int *param_1)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 extraout_ECX_01;
  undefined4 extraout_EDX;
  int *unaff_EBP;
  int *piVar6;
  int *piVar7;
  int iVar8;
  char *pcVar9;
  int *piVar10;
  unsigned char ghidra_frame[0x320] __attribute__((aligned(16)));
#define local_318 (*(int *)(ghidra_frame + 0x8))
#define local_314 (*(int **)(ghidra_frame + 0xc))
#define local_30c (*(int (*)[60])(ghidra_frame + 0x14))
#define local_21c (*(int (*)[131])(ghidra_frame + 0x104))
  
  piVar10 = *(int **)(*param_1 + 0x11c8);
  piVar1 = (int *)g[0x81d1];
  piVar6 = &INT_08287d5c;
  piVar7 = local_21c;
  for (iVar5 = 0x7f; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar7 = *piVar6;
    piVar6 = piVar6 + 1;
    piVar7 = piVar7 + 1;
  }
  piVar6 = &INT_08287f58;
  piVar7 = local_30c;
  for (iVar5 = 0x3a; iVar5 != 0; iVar5 = iVar5 + -1) {
    *piVar7 = *piVar6;
    piVar6 = piVar6 + 1;
    piVar7 = piVar7 + 1;
  }
  local_314 = (int *)0x0;
  local_318 = 0;
  uVar4 = 0;
  if (local_21c[0] != -1) {
    unaff_EBP = (int *)0x4;
    iVar8 = 4;
    iVar5 = 0;
    do {
      iVar3 = SpriteArrayGetNum(piVar10,*(int *)((int)local_21c + iVar5),
                                *(int *)((int)local_21c + iVar8));
      uVar4 = extraout_ECX;
      if (iVar3 == -1) {
        if (local_314 == (int *)0x0) {
          pcVar9 = "%s (%i) missing required sprites:\n";
          piVar6 = param_1 + 8;
          piVar7 = (int *)param_1[1];
        }
        else {
          if (7 < (int)local_314) {
            ClipboardAppend(piVar1," (more)",extraout_EDX,extraout_EDX);
            uVar4 = extraout_ECX_00;
            break;
          }
          pcVar9 = ", ";
          piVar6 = local_314;
          piVar7 = local_314;
        }
        ClipboardAppend(piVar1,pcVar9,piVar6,piVar7);
        ClipboardAppend(piVar1,"%i,%i",*(undefined4 *)(iVar5 + (int)local_21c),
                        *(undefined4 *)((int)unaff_EBP + (int)local_21c));
        local_314 = (int *)((int)local_314 + 1);
        uVar4 = extraout_ECX_01;
      }
      unaff_EBP = unaff_EBP + 2;
      iVar8 = iVar8 + 8;
      iVar3 = iVar5 + 8;
      iVar5 = iVar5 + 8;
    } while (*(int *)((int)local_21c + iVar3) != -1);
  }
  if (local_314 != (int *)0x0) {
    ClipboardAppend(piVar1,"\n",uVar4,uVar4);
  }
  if (local_30c[0] != -1) {
    iVar5 = 0;
    do {
      unaff_EBP = (int *)local_30c[iVar5];
      puVar2 = (undefined4 *)param_1[0x4ef];
      iVar8 = AnimGrpNoToIdx(puVar2,0,(int)unaff_EBP);
      if (iVar8 == -1) {
        if (local_318 == 0) {
          pcVar9 = "%s (%i) missing required animation actions:\n";
          piVar10 = param_1 + 8;
          piVar6 = (int *)param_1[1];
        }
        else {
          if (7 < local_318) {
            ClipboardAppend(piVar1," (more)",0,0);
            break;
          }
          pcVar9 = ", ";
          piVar10 = unaff_EBP;
          piVar6 = unaff_EBP;
        }
        ClipboardAppend(piVar1,pcVar9,piVar10,piVar6);
        ClipboardAppend(piVar1,"%i",local_30c[iVar5],puVar2);
        local_318 = local_318 + 1;
      }
      iVar5 = iVar5 + 1;
    } while (local_30c[iVar5] != -1);
  }
  if (local_318 != 0) {
    ClipboardAppend(piVar1,"\n",unaff_EBP,unaff_EBP);
  }
  uVar4 = 0;
  if ((local_314 == (int *)0x0) && (local_318 == 0)) {
    uVar4 = 1;
  }
  return uVar4;
}
#undef local_318
#undef local_314
#undef local_30c
#undef local_21c

/* ResetPersistVar @ 0x080b02d0, 17 bytes */
void ResetPersistVar(undefined4 *param_1)

{
  int iVar1;
  
  for (iVar1 = 100; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = 0;
    param_1 = param_1 + 1;
  }
  return;
}

/* GameResetPersistVars @ 0x080b02f0, 26 bytes
 * FIXUP: return type set to void: only unaffected-register values were returned */
void GameResetPersistVars(void)

{
  undefined4 extraout_EAX;
  
  TeamResetPersistVars(0);
  TeamResetPersistVars(1);
  return;
}

/* TeamResetPersistVars @ 0x080b0310, 132 bytes */
void TeamResetPersistVars(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int local_14;
  
  iVar3 = 0;
  local_14 = 0;
  do {
    iVar2 = 3;
    iVar4 = 0;
    do {
      iVar1 = iVar4 + 0xd05c;
      iVar4 = iVar4 + 400;
      ResetPersistVar((undefined4 *)((int)g + iVar1 + param_1 * 0x1a9c + iVar3));
      iVar2 = iVar2 + -1;
    } while (-1 < iVar2);
    iVar3 = iVar3 + 0x640;
    local_14 = local_14 + 1;
  } while (local_14 < 4);
  return;
}

/* PlayerSavePersistVars @ 0x080b03a0, 111 bytes */
void PlayerSavePersistVars(int param_1,undefined4 *param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  ResetPersistVar(param_2);
  iVar1 = *(int *)(param_1 + 0x150);
  puVar3 = (undefined4 *)(param_1 + 0xe40 + iVar1 * 4);
  puVar4 = param_2 + iVar1;
  for (uVar2 = 0x3cU - iVar1 & 0x3fffffff; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  iVar1 = *(int *)(param_1 + 0x154);
  puVar3 = (undefined4 *)(param_1 + 0xf30 + iVar1 * 4);
  puVar4 = param_2 + iVar1 + 0x3c;
  for (uVar2 = 0x28U - iVar1 & 0x3fffffff; uVar2 != 0; uVar2 = uVar2 - 1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  return;
}

/* PlayerRestorePersistVars @ 0x080b0410, 85 bytes */
void PlayerRestorePersistVars(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar2 = *(int *)(param_1 + 0x150) * 4;
  puVar3 = (undefined4 *)(iVar2 + param_2);
  puVar4 = (undefined4 *)(param_1 + 0xe40 + iVar2);
  for (uVar1 = 0x3cU - *(int *)(param_1 + 0x150) & 0x3fffffff; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  iVar2 = *(int *)(param_1 + 0x154) * 4;
  puVar3 = (undefined4 *)(param_2 + 0xf0 + iVar2);
  puVar4 = (undefined4 *)(param_1 + 0xf30 + iVar2);
  for (uVar1 = 0x28U - *(int *)(param_1 + 0x154) & 0x3fffffff; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  return;
}

/* GameLoadAndActivateTeam @ 0x080b0470, 226 bytes */
void GameLoadAndActivateTeam(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  
  iVar3 = -1;
  piVar2 = g + param_1 * 0x6a7 + g[param_1 * 0x6a7 + 0x33b8] * 0x17 + 0x33bb;
  PalGrpClear();
  if (g[param_1 + 0x73da] != 0) {
    iVar3 = *(int *)(g[param_1 + 0x73da] + 0x178);
  }
  iVar1 = GameFreeChars(param_1);
  if (iVar1 == 0) {
    ErrorExit();
  }
  iVar1 = GameLoadAndCreateChars(param_1);
  if (iVar1 == 0) {
    ErrorExit();
  }
  if ((iVar3 != -1) && (iVar1 = g[param_1 + 0x73da], iVar1 != 0)) {
    *(int *)(iVar1 + 0x184) = iVar3;
    *(int *)(iVar1 + 0x180) = iVar3;
    *(int *)(iVar1 + 0x178) = iVar3;
  }
  PalGrpBuildFight();
  piVar4 = g + param_1 * 0x17 + 0x4106;
  for (iVar3 = 0x17; iVar3 != 0; iVar3 = iVar3 + -1) {
    *piVar4 = *piVar2;
    piVar2 = piVar2 + 1;
    piVar4 = piVar4 + 1;
  }
  GameActivateAI();
  return;
}

/* GameActivateAI @ 0x080b0560, 175 bytes */
void GameActivateAI(void)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  
  bVar3 = false;
  if ((g[0x82d6] != 0) || (g[0x74e8] != 0)) {
    bVar3 = true;
  }
  iVar7 = 0;
  do {
    piVar4 = g;
    iVar1 = g[iVar7 * 0x6a7 + 0x33b8];
    iVar5 = 0;
    if (0 < g[iVar1 * 0x17 + iVar7 * 0x6a7 + 0x33bd]) {
      piVar6 = g + iVar1 * 0x17 + iVar7 * 0x6a7 + 0x33be;
      do {
        if ((bVar3) && (iVar2 = piVar4[*piVar6 + 0x73d9], iVar2 != 0)) {
          *(undefined4 *)(iVar2 + 0x262c) = 1;
        }
        iVar5 = iVar5 + 1;
        piVar6 = piVar6 + 5;
      } while (iVar5 < piVar4[iVar1 * 0x17 + iVar7 * 0x6a7 + 0x33bd]);
    }
    iVar7 = iVar7 + 1;
  } while (iVar7 < 2);
  return;
}

/* GameLoadAndCreateChars @ 0x080b0610, 952 bytes
 * FIXUP: frame emulation: 3 stack locals placed at their original offsets in a 0x70-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 GameLoadAndCreateChars(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  uint *puVar8;
  uint *puVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  char *__format;
  int iVar13;
  unsigned char ghidra_frame[0x70] __attribute__((aligned(16)));
#define local_68 (*(int *)(ghidra_frame + 0x8))
#define local_5c (*(PalGrpFlag *)(ghidra_frame + 0x14))
#define local_3c (*(PalGrpFlag (*)[2])(ghidra_frame + 0x34))
  
  piVar7 = g;
  iVar2 = g[param_1 * 0x6a7 + 0x33b8];
  local_68 = 0;
  iVar3 = iVar2 * 0x5c + param_1 * 0x1a9c + 0xceec;
  iVar5 = g[param_1 * 0x6a7 + iVar2 * 0x17 + 0x33bd];
  if (iVar5 < 1) {
LAB_080b075a:
    piVar4 = g;
    piVar1 = g + param_1 * 0x6a7 + 0x33b8;
    iVar2 = g[param_1 * 0x6a7 + 0x33b8];
    local_68 = 0;
    if (0 < g[param_1 * 0x6a7 + iVar2 * 0x17 + 0x33bd]) {
      do {
        iVar13 = piVar4[param_1 * 0x6a7 + iVar2 * 0x17 + local_68 * 5 + 0x33be];
        iVar12 = iVar13 * 4;
        piVar6 = PlayerNew(g[iVar13 + 0x7399]);
        piVar7 = g;
        g[iVar13 + 0x73d9] = (int)piVar6;
        if (piVar6 == (int *)0x0) {
          if ((char)piVar7[0x81d2] == '\0') {
            piVar7 = piVar7 + 0x81d2;
            __format = "Can\'t create player %i";
LAB_080b0818:
            sprintf((char *)piVar7,__format,iVar13,iVar12);
          }
          return 0;
        }
        piVar6[3] = (param_1 != 0) + 1;
        piVar6[4] = param_1;
        piVar6[5] = *piVar1;
        piVar6[6] = local_68;
        PlayerRestorePersistVars
                  ((int)piVar6,
                   (int)(piVar7 + param_1 * 0x6a7 + *piVar1 * 400 + local_68 * 100 + 0x3417));
        piVar6[600] = (int)(g + piVar4[param_1 * 0x6a7 + iVar2 * 0x17 + local_68 * 5 + 0x33c1] * 0xd
                                + 0x733b);
        if (piVar4[param_1 * 0x6a7 + iVar2 * 0x17 + local_68 * 5 + 0x33c2] != 0) {
          piVar6[0x98b] = 1;
        }
        PlayerChangePal((int)piVar6,piVar4[param_1 * 0x6a7 + iVar2 * 0x17 + local_68 * 5 + 0x33c0]);
        piVar6[0x4f1] = piVar4[param_1 * 0x6a7 + iVar2 * 0x17 + local_68 * 5 + 0x33c0];
        PlayerEnableSet(iVar13,1);
        PlayerCheck(piVar6);
        piVar6[2] = iVar13;
        if (iVar13 + -1 < 0x20) {
          PalGrpMakeFlag(local_3c,1 << ((byte)(iVar13 + -1) & 0x1f),1);
          piVar6[0x972] = local_3c[0].w[0];
          piVar6[0x973] = local_3c[0].w[1];
          piVar6[0x974] = local_3c[0].w[2];
          piVar6[0x975] = local_3c[0].w[3];
          uVar10 = local_3c[0].w[4];
        }
        else {
          PalGrpMakeFlag(&local_5c,1 << ((char)iVar13 - 0x21U & 0x1f),2);
          piVar6[0x972] = local_5c.w[0];
          piVar6[0x973] = local_5c.w[1];
          piVar6[0x974] = local_5c.w[2];
          piVar6[0x975] = local_5c.w[3];
          uVar10 = local_5c.w[4];
        }
        piVar6[0x976] = uVar10;
        local_68 = local_68 + 1;
      } while (local_68 < piVar4[param_1 * 0x6a7 + iVar2 * 0x17 + 0x33bd]);
    }
    return 1;
  }
  iVar12 = 0;
LAB_080b0668:
  iVar13 = *(int *)((int)piVar7 + iVar12 + 0xc + iVar3);
  if (*(int *)((int)piVar7 + iVar12 + iVar3 + 0x10) == -1) goto LAB_080b073e;
  if (iVar13 + -1 < 4) {
    g[iVar13 + 0x81c4] = Ticks;
  }
  iVar5 = PlayerCacheLoad(*(int *)((int)piVar7 + iVar12 + iVar3 + 0x10));
  piVar1 = g;
  g[iVar13 + 0x7399] = iVar5;
  if (iVar5 != 0) {
    if (iVar13 + -1 < 4) {
      piVar1[iVar13 + 0x81c4] = Ticks - piVar1[iVar13 + 0x81c4];
      iVar5 = piVar7[param_1 * 0x6a7 + iVar2 * 0x17 + 0x33bd];
    }
    else {
      iVar5 = piVar7[param_1 * 0x6a7 + iVar2 * 0x17 + 0x33bd];
    }
    goto LAB_080b073e;
  }
  __format = "\nError loading p%i";
  puVar9 = (uint *)(piVar1 + 0x81d2);
  do {
    puVar8 = puVar9;
    puVar9 = puVar8 + 1;
    uVar10 = *puVar8 + 0xfefefeff & (*puVar8 ^ 0xffffffff);
    uVar11 = uVar10 & 0x80808080;
  } while (uVar11 == 0);
  if ((uVar10 & 0x8080) == 0) {
    uVar11 = uVar11 >> 0x10;
    puVar9 = (uint *)((int)puVar8 + 6);
  }
  piVar7 = (int *)((int)g + (int)puVar9 +
                            (-(int)(piVar1 + 0x81d2) - (uint)CARRY1((byte)uVar11,(byte)uVar11)) +
                            0x20745);
  goto LAB_080b0818;
LAB_080b073e:
  iVar12 = iVar12 + 0x14;
  local_68 = local_68 + 1;
  if (iVar5 <= local_68) goto LAB_080b075a;
  goto LAB_080b0668;
}
#undef local_68
#undef local_5c
#undef local_3c

/* GameFreeChars @ 0x080b09d0, 378 bytes */
undefined4 GameFreeChars(int param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int local_18;
  
  piVar2 = g;
  local_18 = 0;
  if (0 < g[param_1 * 0x17 + 0x4108]) {
    do {
      iVar1 = piVar2[param_1 * 0x17 + local_18 * 5 + 0x4109];
      if (g[iVar1 + 0x73d9] != 0) {
        if (*(int *)(g[iVar1 + 0x73d9] + 0x158) != 0) {
          PlayerEnableSet(iVar1,0);
        }
        iVar4 = g[iVar1 + 0x73d9];
        if (*(int *)(iVar4 + 0x10) != -1) {
          PlayerSavePersistVars
                    (g[iVar1 + 0x73d9],
                     g + *(int *)(iVar4 + 0x10) * 0x6a7 +
                         *(int *)(iVar4 + 0x14) * 400 + *(int *)(iVar4 + 0x18) * 100 + 0x3417);
        }
        iVar4 = -1;
        if (*(int *)g[iVar1 + 0x73d9] != 0) {
          iVar4 = *(int *)(*(int *)g[iVar1 + 0x73d9] + 0x10a8);
        }
        GameFreePlayerDependencies((int *)g[iVar1 + 0x73d9]);
        PlayerFree((int *)g[iVar1 + 0x73d9]);
        if (iVar4 != -1) {
          PlayerCacheFree(iVar4);
        }
        piVar3 = g;
        g[iVar1 + 0x7399] = 0;
        piVar3[iVar1 + 0x73d9] = 0;
      }
      local_18 = local_18 + 1;
    } while (local_18 < piVar2[param_1 * 0x17 + 0x4108]);
  }
  return 1;
}

/* GameFreePlayerDependencies @ 0x080b0b50, 349 bytes */
undefined4 GameFreePlayerDependencies(int *param_1)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  ExplodRemoveID((undefined4 *)g[0x52be],param_1[1],-1);
  PlayerDropBoundTargets((int)param_1,(int *)0x0);
  iVar5 = g[0x7459];
  if (iVar5 <= g[0x745a]) {
    iVar4 = iVar5 * 4 + 0x1cf60;
    piVar3 = g;
    do {
      piVar1 = *(int **)(iVar4 + 4 + (int)piVar3);
      if ((piVar1 != param_1) && (piVar1 != (int *)0x0)) {
        if ((int *)piVar1[0x989] == param_1) {
          ExplodRemoveID((undefined4 *)piVar3[0x52be],piVar1[1],-1);
          HelperDestroy((int)piVar1);
          piVar3 = g;
        }
        else {
          iVar2 = param_1[0x4e5];
          if (iVar2 != 0) {
            *(undefined4 *)(iVar2 + 0x18) = 0;
            *(undefined4 *)(iVar2 + 8) = 0;
            param_1[0x4e5] = 0;
          }
          if (piVar1[0x4f0] == *(int *)(*param_1 + 0x11cc)) {
            piVar1[0x4f0] = 0;
          }
          if (piVar1[0x2fb] == param_1[0x2fa]) {
            piVar1[0x2fb] = 0;
            piVar1[0x2fc] = -1;
          }
          if ((int *)piVar1[0xd09] == param_1) {
            piVar1[0xd09] = 0;
          }
          if ((int *)piVar1[0xd0a] == param_1) {
            piVar1[0xd0a] = 0;
          }
          piVar3 = g;
          if (((int *)piVar1[0xd15] == param_1) && (piVar1[0xd0c] != 0)) {
            piVar1[0xd0c] = 0;
            piVar1[0xd15] = 0;
            piVar3 = g;
          }
        }
      }
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 4;
    } while (iVar5 <= piVar3[0x745a]);
  }
  return 1;
}

/* TeamReorderAll @ 0x080b0cb0, 802 bytes
 * FIXUP: frame emulation: 8 stack locals placed at their original offsets in a 0x700-byte frame (a local's address escapes, see apply_frame_emulation) */
int TeamReorderAll(int param_1)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  unsigned char ghidra_frame[0x700] __attribute__((aligned(16)));
#define local_6f8 (*(int **)(ghidra_frame + 0x8))
#define local_6ec (*(int **)(ghidra_frame + 0x14))
#define local_6e8 (*(int **)(ghidra_frame + 0x18))
#define local_6e0 (*(int **)(ghidra_frame + 0x20))
#define local_6c8 (*(int *)(ghidra_frame + 0x38))
#define local_6c4 (*(int *)(ghidra_frame + 0x3c))
#define local_6bc (*(int (*)[400])(ghidra_frame + 0x44))
#define local_7c (*(int (*)[27])(ghidra_frame + 0x684))
  
  piVar2 = g;
  iVar1 = g[param_1 * 0x6a7 + 0x33b8];
  iVar9 = g[param_1 * 0x6a7 + 0x33b9] - iVar1;
  piVar4 = g + param_1 * 0x6a7 + iVar1 * 0x17 + 0x33bb;
  if ((1 < iVar9) && (piVar4[7] == 0)) {
    iVar6 = piVar4[6];
    uVar3 = KBToUInp(g[iVar6 * 0xd + 0x733f]);
    local_6c4 = (uinpflag[uVar3] == 0) - 1;
    uVar3 = KBToUInp(piVar2[iVar6 * 0xd + 0x733d]);
    if (uinpflag[uVar3] != 0) {
      local_6c4 = 1;
    }
    if (param_1 == 1) {
      local_6c4 = -local_6c4;
    }
    uVar3 = KBToUInp(piVar2[iVar6 * 0xd + 0x733c]);
    if ((uinpflag[uVar3] != 0) && (iVar9 == 4)) {
      local_6c4 = 2;
    }
    piVar4 = (int *)(local_6c4 / iVar9);
    local_6c4 = local_6c4 % iVar9;
    if (local_6c4 < 0) {
      local_6c4 = local_6c4 + iVar9;
    }
    if (0 < local_6c4) {
      iVar9 = param_1 * 4;
      do {
        piVar4 = piVar2 + param_1 * 0x6a7 + iVar1 * 0x17 + 0x33bb;
        piVar10 = local_7c;
        for (iVar6 = 0x17; iVar6 != 0; iVar6 = iVar6 + -1) {
          *piVar10 = *piVar4;
          piVar4 = piVar4 + 1;
          piVar10 = piVar10 + 1;
        }
        piVar4 = piVar2 + param_1 * 0x6a7 + iVar1 * 400 + 0x3417;
        piVar10 = local_6bc;
        for (iVar6 = 400; iVar6 != 0; iVar6 = iVar6 + -1) {
          *piVar10 = *piVar4;
          piVar4 = piVar4 + 1;
          piVar10 = piVar10 + 1;
        }
        iVar6 = g[iVar9 + iVar1 + 0x52b5];
        iVar7 = piVar2[param_1 * 0x6a7 + 0x33b9];
        if (iVar1 < iVar7 + -1) {
          local_6e0 = piVar2 + param_1 * 0x6a7 + iVar1 * 400 + 0x35a4;
          local_6f8 = piVar2 + param_1 * 0x6a7 + iVar1 * 0x17 + 0x33b8;
          iVar5 = (iVar9 + iVar1) * 4;
          local_6e8 = piVar2 + param_1 * 0x6a7 + iVar1 * 400 + 0x3414;
          iVar8 = iVar5 + 0x14ad4;
          iVar5 = iVar5 + 0x14ad0;
          local_6c8 = iVar1;
          piVar4 = piVar2 + param_1 * 0x6a7 + iVar1 * 0x17 + 0x33b8;
          do {
            local_6ec = piVar4 + 0x17;
            piVar4 = piVar4 + 0x1a;
            piVar10 = local_6f8 + 3;
            for (iVar7 = 0x17; iVar7 != 0; iVar7 = iVar7 + -1) {
              *piVar10 = *piVar4;
              piVar4 = piVar4 + 1;
              piVar10 = piVar10 + 1;
            }
            piVar4 = local_6e0 + 3;
            piVar10 = local_6e8 + 3;
            for (iVar7 = 400; iVar7 != 0; iVar7 = iVar7 + -1) {
              *piVar10 = *piVar4;
              piVar4 = piVar4 + 1;
              piVar10 = piVar10 + 1;
            }
            iVar7 = iVar8 + 4;
            iVar8 = iVar8 + 4;
            *(undefined4 *)((int)g + iVar5 + 4) = *(undefined4 *)((int)g + iVar7);
            iVar5 = iVar5 + 4;
            local_6e0 = local_6e0 + 400;
            local_6e8 = local_6e8 + 400;
            local_6f8 = local_6f8 + 0x17;
            local_6c8 = local_6c8 + 1;
            iVar7 = piVar2[param_1 * 0x6a7 + 0x33b9];
            piVar4 = local_6ec;
          } while (local_6c8 < iVar7 + -1);
        }
        piVar4 = local_7c;
        piVar10 = piVar2 + param_1 * 0x6a7 + iVar7 * 0x17 + 0x33a4;
        for (iVar8 = 0x17; iVar8 != 0; iVar8 = iVar8 + -1) {
          *piVar10 = *piVar4;
          piVar4 = piVar4 + 1;
          piVar10 = piVar10 + 1;
        }
        piVar4 = local_6bc;
        piVar10 = piVar2 + param_1 * 0x6a7 + piVar2[param_1 * 0x6a7 + 0x33b9] * 400 + 0x3287;
        for (iVar7 = 400; iVar7 != 0; iVar7 = iVar7 + -1) {
          *piVar10 = *piVar4;
          piVar4 = piVar4 + 1;
          piVar10 = piVar10 + 1;
        }
        piVar4 = (int *)(iVar9 + piVar2[param_1 * 0x6a7 + 0x33b9]);
        g[(int)(piVar4 + 0x14ad)] = iVar6;
        local_6c4 = local_6c4 + -1;
      } while (local_6c4 != 0);
    }
  }
  return (int)piVar4;
}
#undef local_6f8
#undef local_6ec
#undef local_6e8
#undef local_6e0
#undef local_6c8
#undef local_6c4
#undef local_6bc
#undef local_7c

