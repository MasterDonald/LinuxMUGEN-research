/*
 * common.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x0808d0f0-0x0808d821, 13 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* GlobalInputUpdate @ 0x0808d0f0, 1 bytes */
void GlobalInputUpdate(void)

{
  return;
}

/* Warn @ 0x0808d100, 68 bytes */
undefined4 Warn(int param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    uVar1 = ClipboardAppend((int *)g[0x81d1],"%4i: Warning: Player %s (%i) in state %i:\n%s",
                            g[0x7304],param_1 + 0x20,*(undefined4 *)(param_1 + 4),
                            *(undefined4 *)(param_1 + 0xbf4),param_2);
  }
  return uVar1;
}

/* VWarn @ 0x0808d150, 106 bytes
 * FIXUP: varargs: replaced 1 &stack0x.. with a va_list started after param_2
 * FIXUP: frame emulation: 1 stack locals placed at their original offsets in a 0x810-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 VWarn(int param_1,char *param_2,...)

{
  va_list ghidra_va;
  va_start(ghidra_va, param_2);
  undefined4 in_EAX;
  unsigned char ghidra_frame[0x810] __attribute__((aligned(16)));
#define local_80c (*(char (*)[2052])(ghidra_frame + 0x4))
  
  if (param_1 != 0) {
    vsprintf(local_80c,param_2,ghidra_va);
    in_EAX = ClipboardAppend((int *)g[0x81d1],"%4i: Warning: Player %s (%i) in state %i:\n%s",
                             g[0x7304],param_1 + 0x20,*(undefined4 *)(param_1 + 4),
                             *(undefined4 *)(param_1 + 0xbf4),local_80c);
  }
  return in_EAX;
}
#undef local_80c

/* WarnR @ 0x0808d1c0, 88 bytes */
int WarnR(int param_1,int param_2,int param_3)

{
  if (param_1 != 0) {
    param_2 = ClipboardAppend((int *)g[0x81d1],
                              "%4i: Warning: Player %s (%i) in state %i:\nin redirected trigger from player %s (%i) in state %i:\n%s"
                              ,g[0x7304],param_1 + 0x20,*(undefined4 *)(param_1 + 4),
                              *(undefined4 *)(param_1 + 0xbf4),param_2 + 0x20,
                              *(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 0xbf4),param_3)
    ;
  }
  return param_2;
}

/* StripDoublePercent @ 0x0808d220, 45 bytes */
void StripDoublePercent(char *param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar2 = 0;
  cVar1 = *param_1;
  while (cVar1 != '\0') {
    if ((cVar1 != '%') || (param_1[iVar2 + 1] != '%')) {
      param_1[iVar3] = cVar1;
      iVar3 = iVar3 + 1;
    }
    iVar2 = iVar2 + 1;
    cVar1 = param_1[iVar2];
  }
  param_1[iVar3] = '\0';
  return;
}

/* FontDrawClipboard @ 0x0808d250, 168 bytes */
void FontDrawClipboard(int *param_1,int *param_2,int param_3,int param_4,uint param_5)

{
  uint uVar1;
  
  uVar1 = param_1[4];
  if (uVar1 != param_1[5]) {
    do {
      V_FontDraw(*(char **)(*param_1 + uVar1 * 4),param_2,param_3,param_4,param_5);
      param_4 = param_4 + param_2[6] + param_2[3];
      uVar1 = uVar1 + 1 & (param_1[3] <= (int)(uVar1 + 1)) - 1;
    } while (uVar1 != param_1[5]);
  }
  if (**(char **)(*param_1 + uVar1 * 4) == '\0') {
    return;
  }
  V_FontDraw(*(char **)(*param_1 + uVar1 * 4),param_2,param_3,param_4,param_5);
  return;
}

/* ErrorExit @ 0x0808d300, 194 bytes */
undefined4 ErrorExit(void)

{
  int iVar1;
  int iVar2;
  int extraout_EDX;
  int extraout_EDX_00;
  char *__format;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 8;
  iVar4 = 0x19;
  pbVar3 = (byte *)0x50;
  G_SetMode(0xffffffff,0x50,0x19,8);
  iVar1 = ErrorGet();
  iVar2 = extraout_EDX;
  if (iVar1 != 0) {
    pbVar3 = (byte *)ErrorGetStr();
    printf("Library (built in) message: %s.\n\n",pbVar3);
    iVar2 = extraout_EDX_00;
  }
  if ((char)g[0x81d2] == '\0') {
    __format = "Error detected.\n\n";
  }
  else {
    pbVar3 = (byte *)(g + 0x81d2);
    __format = "Error message: %s\n\n";
    iVar4 = iVar2;
    iVar5 = iVar2;
  }
  iVar2 = printf(__format,pbVar3,iVar4,iVar5);
  if (ErrorMessage[0] != 0) {
    pbVar3 = ErrorMessage;
    iVar5 = iVar2;
    printf("Library error message: %s\n\n",ErrorMessage,iVar2,iVar2);
    iVar4 = iVar2;
  }
  if (ElecOutOfMem != 0) {
    printf("Out of memory error.\n\n",pbVar3,iVar4,iVar5);
  }
  if (g[0x800] != 0) {
    chdir((char *)g);
  }
  ElecDeInit();
                    /* WARNING: Subroutine does not return */
  exit(1);
}

/* ErrorExitM @ 0x0808d3d0, 39 bytes
 * FIXUP: varargs: replaced 1 &stack0x.. with a va_list started after param_1 */
undefined4 ErrorExitM(char *param_1,...)

{
  va_list ghidra_va;
  va_start(ghidra_va, param_1);
  undefined4 uVar1;
  
  vsprintf((char *)(g + 0x81d2),param_1,ghidra_va);
  uVar1 = ErrorExit();
  return uVar1;
}

/* fileexist @ 0x0808d400, 51 bytes */
bool fileexist(char *param_1)

{
  FILE *stream;
  
  stream = fopen(param_1,"rb");
  if (stream != (FILE *)0x0) {
    fclose(stream);
  }
  return stream != (FILE *)0x0;
}

/* ChangeFileDir @ 0x0808d440, 372 bytes
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 8 stack locals placed at their original offsets in a 0x5030-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 ChangeFileDir(char *param_1,char *param_2,char *param_3)

{
  bool bVar1;
  int iVar2;
  undefined3 extraout_var;
  undefined4 extraout_ECX;
  int iVar3;
  unsigned char ghidra_frame[0x5030] __attribute__((aligned(16)));
#define acStack_502c (*(char (*)[4096])(ghidra_frame + 0x4))
#define local_402c (*(char (*)[4096])(ghidra_frame + 0x1004))
#define local_302c (*(char (*)[4096])(ghidra_frame + 0x2004))
#define local_202c (*(char (*)[4096])(ghidra_frame + 0x3004))
#define local_102c (*(char (*)[4096])(ghidra_frame + 0x4004))
#define local_2c (*(undefined **)(ghidra_frame + 0x5004))
#define local_28 (*(int *)(ghidra_frame + 0x5008))
#define local_24 (*(char **)(ghidra_frame + 0x500c))
  
  if ((*param_1 != '\0') && (param_1[1] == ':')) {
    param_1 = param_1 + 2;
  }
  getcwd(local_302c,0xfff);
  local_24 = local_402c;
  local_28 = (int)g + 0xfff;
  local_2c = &DAT_08283393;
  sprintf(local_24,"%sdata/",local_28);
  splitdirfile(param_1,local_102c,local_202c);
  if ((local_102c[0] == '/') || (local_102c[0] == '\\')) {
    local_2c = &DAT_0827725f;
  }
  iVar3 = 0;
  do {
    sprintf(acStack_502c,"%s%s",(&local_2c)[iVar3],local_102c);
    iVar2 = chdir(acStack_502c);
    if (iVar2 == 0) {
      bVar1 = fileexist(local_202c);
      if (GHIDRA_ZEXT8(bVar1) != 0) {
        strcpy(param_2,local_302c);
        strcpy(param_3,local_202c);
        return 1;
      }
    }
    iVar3 = iVar3 + 1;
    chdir(local_302c);
  } while (iVar3 < 3);
  sprintf((char *)(g + 0x81d2),"Can\'t find file %s",param_1,extraout_ECX);
  return 0;
}
#undef acStack_502c
#undef local_402c
#undef local_302c
#undef local_202c
#undef local_102c
#undef local_2c
#undef local_28
#undef local_24

/* FindFileDir @ 0x0808d5c0, 29 bytes */
undefined4 FindFileDir(char *param_1,char *param_2,char *param_3)

{
  undefined4 uVar1;
  
  uVar1 = FindFileDirEx(param_1,param_2,param_3,(undefined4 *)0x0);
  return uVar1;
}

/* FindFileDirEx @ 0x0808d5e0, 367 bytes
 * REVIEW: pid-unaff_
 * FIXUP: 1 CONCAT31(extraout_var, x) written as zero-extension GHIDRA_ZEXT8(x)
 * FIXUP: frame emulation: 10 stack locals placed at their original offsets in a 0x3040-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 FindFileDirEx(char *param_1,char *param_2,char *param_3,undefined4 *param_4)

{
  bool bVar1;
  undefined3 extraout_var;
  char *unaff_EBX;
  int iVar2;
  unsigned char ghidra_frame[0x3040] __attribute__((aligned(16)));
#define local_3040 (*(int *)(ghidra_frame + 0x0))
#define local_303c (*(char (*)[2])(ghidra_frame + 0x4))
#define local_303a (*(undefined1 *)(ghidra_frame + 0x6))
#define local_302c (*(char (*)[4096])(ghidra_frame + 0x14))
#define local_202c (*(char (*)[4096])(ghidra_frame + 0x1014))
#define local_102c (*(char (*)[4096])(ghidra_frame + 0x2014))
#define local_2c (*(undefined4 **)(ghidra_frame + 0x3014))
#define local_28 (*(int *)(ghidra_frame + 0x3018))
#define local_24 (*(undefined1 **)(ghidra_frame + 0x301c))
#define local_20 (*(char **)(ghidra_frame + 0x3020))
  
  if ((*param_1 == '\0') || (param_1[1] != ':')) {
    local_303c[0] = '\0';
  }
  else {
    strncpy(local_303c,param_1,2);
    local_303a = 0;
    param_1 = param_1 + 2;
  }
  local_2c = param_4;
  local_28 = (int)g + 0x15aff;
  local_24 = &DAT_08283393;
  local_20 = "data/";
  splitdirfile(param_1,local_102c,local_202c);
  if ((local_102c[0] == '/') || (local_102c[0] == '\\')) {
    local_2c = (undefined4 *)&DAT_0827725f;
  }
  local_3040 = 0;
  iVar2 = 0;
  do {
    if (*(int *)((int)&local_2c + iVar2) != 0) {
      unaff_EBX = local_302c;
      sprintf(unaff_EBX,"%s%s%s",*(int *)((int)&local_2c + iVar2),local_102c,local_202c);
      bVar1 = fileexist(unaff_EBX);
      if (GHIDRA_ZEXT8(bVar1) != 0) {
        if (param_3 != (char *)0x0) {
          sprintf(param_3,"%s%s",*(undefined4 *)((int)&local_2c + iVar2),local_102c);
        }
        strcpy(param_2,unaff_EBX);
        return 1;
      }
    }
    iVar2 = iVar2 + 4;
    local_3040 = local_3040 + 1;
  } while (local_3040 < 4);
  sprintf((char *)(g + 0x81d2),"Can\'t find file %s",param_1,unaff_EBX);
  return 0;
}
#undef local_3040
#undef local_303c
#undef local_303a
#undef local_302c
#undef local_202c
#undef local_102c
#undef local_2c
#undef local_28
#undef local_24
#undef local_20

/* GetQuotedString @ 0x0808d750, 209 bytes */
undefined4 GetQuotedString(int param_1,char *param_2,char *param_3,size_t param_4,char *param_5)

{
  char *pcVar1;
  size_t sVar2;
  int *__s;
  size_t extraout_ECX;
  size_t extraout_EDX;
  size_t __n;
  
  pcVar1 = TPGetValue(param_1,param_2);
  if (pcVar1 == (char *)0x0) {
    if (param_5 != (char *)0x0) {
      strcpy((char *)(g + 0x81d2),param_5);
      return 0;
    }
    __s = g + 0x81d2;
    pcVar1 = "Cannot find parameter: %s";
    sVar2 = extraout_ECX;
  }
  else {
    sVar2 = strlen(pcVar1);
    if ((*pcVar1 == '\"') && (pcVar1[sVar2 - 1] == '\"')) {
      __n = sVar2 - 2;
      if ((int)param_4 < (int)(sVar2 - 2)) {
        __n = param_4;
      }
      strncpy(param_3,pcVar1 + 1,__n);
      param_3[__n] = '\0';
      return 1;
    }
    if (param_5 == (char *)0x0) {
      __s = g + 0x81d2;
      pcVar1 = "String value for %s must be in quotes";
    }
    else {
      __s = g + 0x81d2;
      pcVar1 = "String must be in quotes\n%s";
      param_2 = param_5;
      sVar2 = extraout_EDX;
    }
  }
  sprintf((char *)__s,pcVar1,param_2,sVar2);
  return 0;
}

