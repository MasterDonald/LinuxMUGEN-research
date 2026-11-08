/*
 * ebcommon.c -- reconstructed from LINUXMUGEN 2002.04.14 (unpacked SHA-256
 * d9444262b577c9ff52aa72c3f42bef771fe1fa1342716c44f38858d0b0c409d1).
 * Original object text range: 0x08050cd0-0x0805198d, 36 functions.
 * Bodies are Ghidra 12.1.4 decompiler output (Decompiler Parameter ID pass),
 * cross-checked against the REA baseline. This is NOT Elecbyte source code.
 */
#include "mugen_common.h"


/* ecalloc @ 0x08050cd0, 39 bytes */
void * ecalloc(size_t param_1,size_t param_2)

{
  void *pvVar1;
  
  pvVar1 = calloc(param_1,param_2);
  if (pvVar1 == (void *)0x0) {
    ElecOutOfMem = 1;
  }
  return pvVar1;
}

/* ErrorSet @ 0x08050d00, 10 bytes */
int ErrorSet(int param_1)

{
  ErrorNumber = param_1;
  return param_1;
}

/* ErrorGet @ 0x08050d10, 6 bytes */
int ErrorGet(void)

{
  return ErrorNumber;
}

/* ErrorGetStr @ 0x08050d20, 70 bytes */
char * ErrorGetStr(void)

{
  if (ErrorNumber == 2) {
    return "Can\'t init sound";
  }
  if (ErrorNumber < 3) {
    if (ErrorNumber == 1) {
      return "Can\'t load fonts";
    }
  }
  else {
    if (ErrorNumber == 3) {
      return "Can\'t init graphics";
    }
    if (ErrorNumber == 4) {
      return "Can\'t change video mode";
    }
  }
  return "Error not defined";
}

/* CheckExtension @ 0x08050d70, 394 bytes */
undefined4 CheckExtension(char *param_1)

{
  char *pcVar1;
  size_t sVar2;
  int iVar3;
  undefined4 uVar4;
  
  sVar2 = strlen(param_1);
  if (((int)sVar2 < 5) || (param_1[sVar2 - 4] != '.')) {
LAB_08050ea3:
    if ((3 < (int)sVar2) && (param_1[sVar2 - 3] == '.')) {
      iVar3 = _alemu_stricmp(param_1 + (sVar2 - 2),"xm");
      if (iVar3 == 0) goto LAB_08050ec8;
      iVar3 = _alemu_stricmp(param_1 + (sVar2 - 2),"da");
      if (iVar3 == 0) {
        return 8;
      }
    }
    uVar4 = 0;
  }
  else {
    pcVar1 = param_1 + (sVar2 - 3);
    iVar3 = _alemu_stricmp(pcVar1,"pcx");
    if (iVar3 == 0) {
      return 1;
    }
    iVar3 = _alemu_stricmp(pcVar1,"sff");
    if (iVar3 == 0) {
      return 2;
    }
    iVar3 = _alemu_stricmp(pcVar1,"wav");
    if (iVar3 == 0) {
      return 3;
    }
    iVar3 = _alemu_stricmp(pcVar1,"snd");
    if (iVar3 == 0) {
      return 4;
    }
    iVar3 = _alemu_stricmp(pcVar1,"mp3");
    if (iVar3 == 0) {
      return 5;
    }
    iVar3 = _alemu_stricmp(pcVar1,"mid");
    if (iVar3 == 0) {
      return 6;
    }
    iVar3 = _alemu_stricmp(pcVar1,"mod");
    if ((iVar3 != 0) && (iVar3 = _alemu_stricmp(pcVar1,"s3m"), iVar3 != 0)) {
      iVar3 = _alemu_stricmp(pcVar1,"zip");
      if (iVar3 == 0) {
        return 9;
      }
      goto LAB_08050ea3;
    }
LAB_08050ec8:
    uVar4 = 7;
  }
  return uVar4;
}

/* igetw @ 0x08050f00, 56 bytes */
uint igetw(_IO_FILE *param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = fgetc(param_1);
  if ((uVar1 != 0xffffffff) && (iVar2 = fgetc(param_1), iVar2 != -1)) {
    return iVar2 << 8 | uVar1;
  }
  return 0xffffffff;
}

/* igetl @ 0x08050f40, 110 bytes */
uint igetl(_IO_FILE *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = fgetc(param_1);
  if ((((uVar1 != 0xffffffff) && (iVar2 = fgetc(param_1), iVar2 != -1)) &&
      (iVar3 = fgetc(param_1), iVar3 != -1)) && (iVar4 = fgetc(param_1), iVar4 != -1)) {
    return iVar4 << 0x18 | iVar3 << 0x10 | iVar2 << 8 | uVar1;
  }
  return 0xffffffff;
}

/* strimatch @ 0x08050fb0, 74 bytes */
undefined4 strimatch(char *param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  
  iVar2 = 0;
  if (*param_1 != '\0') {
    cVar1 = *param_2;
    while (cVar1 != '\0') {
      if (*(int *)(__ctype_tolower + param_1[iVar2] * 4) !=
          *(int *)(__ctype_tolower + param_2[iVar2] * 4)) {
        return 0;
      }
      iVar2 = iVar2 + 1;
      if (param_1[iVar2] == '\0') {
        return 1;
      }
      cVar1 = param_2[iVar2];
    }
  }
  return 1;
}

/* strimatchlen @ 0x08051000, 79 bytes */
undefined4 strimatchlen(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = 0;
  if (0 < param_3) {
    do {
      if (((*(int *)(__ctype_tolower + *(char *)(iVar1 + param_1) * 4) !=
            *(int *)(__ctype_tolower + *(char *)(iVar1 + param_2) * 4)) ||
          (*(char *)(iVar1 + param_1) == '\0')) || (*(char *)(iVar1 + param_2) == '\0')) {
        return 0;
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < param_3);
  }
  return 1;
}

/* strmatchlen @ 0x08051050, 49 bytes */
undefined4 strmatchlen(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  iVar1 = 0;
  if (0 < param_3) {
    do {
      if ((*(char *)(iVar1 + param_1) != *(char *)(iVar1 + param_2)) ||
         (*(char *)(iVar1 + param_1) == '\0')) {
        return 0;
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < param_3);
  }
  return 1;
}

/* strtoupper @ 0x08051090, 39 bytes */
void strtoupper(undefined1 *param_1,char *param_2)

{
  char cVar1;
  
  cVar1 = *param_2;
  while (cVar1 != '\0') {
    cVar1 = *param_2;
    param_2 = param_2 + 1;
    *param_1 = (char)*(undefined4 *)(__ctype_toupper + cVar1 * 4);
    param_1 = param_1 + 1;
    cVar1 = *param_2;
  }
  return;
}

/* splitdirfile @ 0x080510c0, 121 bytes
 * FIXUP: 3 exact-text site patches */
char * splitdirfile(char *param_1,char *param_2,char *param_3)

{
  char cVar1;
  char *in_EAX;
  char *pcVar2;
  char *__n;
  
  if (*param_1 == '\0') {
    if (param_2 != (char *)0x0) {
      *param_2 = '\0';
    }
    if (param_3 != (char *)0x0) {
      *param_3 = '\0';
    }
  }
  else {
    in_EAX = (char *)strlen(param_1);
    pcVar2 = in_EAX;
    while (__n = pcVar2, pcVar2 = __n + -1, -1 < (int)pcVar2) {
      cVar1 = param_1[(int)pcVar2];
      in_EAX = (char *)CONCAT31((int3)((uint)in_EAX >> 8),cVar1);
      if ((cVar1 == '\\') || (cVar1 == '/')) break;
    }
    if (param_3 != (char *)0x0) {
      in_EAX = strcpy(param_3,param_1 + (int)__n);
    }
    if (param_2 != (char *)0x0) {
      if (0 < (int)__n) {
        in_EAX = strncpy(param_2,param_1,(size_t)__n);
      }
      param_2[(int)__n] = '\0';
    }
  }
  return in_EAX;
}

/* joindirfile @ 0x08051140, 116 bytes */
char * joindirfile(char *param_1,char *param_2,char *param_3)

{
  int iVar1;
  char *pcVar2;
  size_t sVar3;
  
  iVar1 = isabsolutedir(param_3);
  if (iVar1 != 0) {
    pcVar2 = strcpy(param_1,param_3);
    return pcVar2;
  }
  strcpy(param_1,param_2);
  sVar3 = strlen(param_1);
  if (((0 < (int)sVar3) && (param_1[sVar3 - 1] != '/')) && (param_1[sVar3 - 1] != '\\')) {
    strcat(param_1,"/");
  }
  pcVar2 = strcat(param_1,param_3);
  return pcVar2;
}

/* isabsolutedir @ 0x080511c0, 34 bytes */
undefined4 isabsolutedir(char *param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  cVar1 = *param_1;
  if (((cVar1 == '/') || (cVar1 == '\\')) || ((cVar1 != '\0' && (param_1[1] == ':')))) {
    uVar2 = 1;
  }
  return uVar2;
}

/* ffilelength @ 0x080511f0, 62 bytes */
long ffilelength(FILE *param_1)

{
  long __off;
  long lVar1;
  
  __off = ftell(param_1);
  fseek(param_1,0,2);
  lVar1 = ftell(param_1);
  fseek(param_1,__off,0);
  return lVar1;
}

/* strcpyslash @ 0x08051230, 42 bytes */
void strcpyslash(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  
  iVar2 = 0;
  cVar1 = *param_2;
  while (cVar1 != '\0') {
    *(char *)(iVar2 + param_1) = cVar1;
    if (cVar1 == '\\') {
      *(undefined1 *)(iVar2 + param_1) = 0x2f;
    }
    iVar2 = iVar2 + 1;
    cVar1 = param_2[iVar2];
  }
  *(undefined1 *)(iVar2 + param_1) = 0;
  return;
}

/* IntSwap @ 0x08051260, 19 bytes */
void IntSwap(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = *param_1;
  *param_1 = *param_2;
  *param_2 = uVar1;
  return;
}

/* IntMin @ 0x08051280, 15 bytes */
int IntMin(int param_1,int param_2)

{
  if (param_2 < param_1) {
    param_1 = param_2;
  }
  return param_1;
}

/* IntMax @ 0x08051290, 15 bytes */
int IntMax(int param_1,int param_2)

{
  if (param_1 < param_2) {
    param_1 = param_2;
  }
  return param_1;
}

/* DebugErrorExit @ 0x080512a0, 83 bytes */
void DebugErrorExit(int param_1)

{
  undefined4 uVar1;
  char *__format;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar4 = 8;
  uVar3 = 0x19;
  iVar2 = 0x50;
  uVar1 = G_SetMode(0xffffffff,0x50,0x19,8);
  if (param_1 == 0) {
    __format = "Error detected.\n\n";
  }
  else {
    __format = "Error message: %s\n\n";
    iVar2 = param_1;
    uVar3 = uVar1;
    uVar4 = uVar1;
  }
  printf(__format,iVar2,uVar3,uVar4);
  chdir("/djgpp/elecbyte");
                    /* WARNING: Subroutine does not return */
  exit(1);
}

/* MFgetc @ 0x08051300, 80 bytes */
uint MFgetc(int *param_1)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  uint uVar4;
  
  iVar2 = *param_1;
  if (iVar2 == 1) {
    uVar4 = fgetc((_IO_FILE *)param_1[1]);
    return uVar4;
  }
  if ((0 < iVar2) && (iVar2 < 4)) {
    pbVar3 = (byte *)param_1[5];
    if (pbVar3 != (byte *)param_1[4]) {
      bVar1 = *pbVar3;
      param_1[5] = (int)(pbVar3 + 1);
      return (uint)bVar1;
    }
    param_1[8] = 1;
  }
  return 0xffffffff;
}

/* MFfgets @ 0x08051350, 145 bytes */
char * MFfgets(char *s,int n,int *mf)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  int iVar4;
  
  iVar4 = *mf;
  if (iVar4 == 1) {
    pcVar3 = fgets(s,n,(FILE *)mf[1]);
    return pcVar3;
  }
  if ((iVar4 < 1) || (3 < iVar4)) {
LAB_080513d7:
    s = (char *)0x0;
  }
  else {
    pcVar3 = s;
    for (iVar4 = 0; iVar4 < n + -1; iVar4 = iVar4 + 1) {
      pcVar2 = (char *)mf[5];
      if (pcVar2 == (char *)mf[4]) {
        mf[8] = 1;
        goto LAB_080513d7;
      }
      cVar1 = *pcVar2;
      mf[5] = (int)(pcVar2 + 1);
      if ((cVar1 == '\n') || (cVar1 == '\r')) break;
      *pcVar3 = cVar1;
      pcVar3 = pcVar3 + 1;
    }
    *pcVar3 = '\0';
  }
  return s;
}

/* MFfread @ 0x080513f0, 171 bytes */
size_t MFfread(void *ptr,size_t size,size_t n,int *mf)

{
  int iVar1;
  void *__src;
  size_t sVar2;
  
  iVar1 = *mf;
  if (iVar1 != 1) {
    if ((iVar1 < 1) || (3 < iVar1)) {
      n = 0xffffffff;
    }
    else {
      __src = (void *)mf[5];
      sVar2 = size * n;
      if ((void *)mf[4] < (void *)(sVar2 + (int)__src)) {
        sVar2 = mf[4] - (int)__src;
        memcpy(ptr,__src,sVar2);
        n = 0xffffffff;
        mf[5] = mf[5] + sVar2;
        mf[8] = 1;
      }
      else {
        memcpy(ptr,__src,sVar2);
        mf[5] = mf[5] + sVar2;
      }
    }
    return n;
  }
  sVar2 = fread(ptr,size,n,(FILE *)mf[1]);
  return sVar2;
}

/* MFfeof @ 0x080514a0, 57 bytes */
int MFfeof(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (iVar1 != 1) {
    if ((iVar1 < 1) || (3 < iVar1)) {
      iVar1 = 1;
    }
    else {
      iVar1 = param_1[8];
    }
    return iVar1;
  }
  iVar1 = feof((FILE *)param_1[1]);
  return iVar1;
}

/* MFfopenFile @ 0x080514e0, 87 bytes */
undefined4 * MFfopenFile(char *param_1,char *param_2)

{
  undefined4 *__ptr;
  FILE *pFVar1;
  
  __ptr = (undefined4 *)ecalloc(1,0x24);
  if (__ptr == (undefined4 *)0x0) {
    __ptr = (undefined4 *)0x0;
  }
  else {
    *__ptr = 1;
    pFVar1 = fopen(param_1,param_2);
    __ptr[1] = pFVar1;
    if (pFVar1 == (FILE *)0x0) {
      free(__ptr);
      __ptr = (undefined4 *)0x0;
    }
  }
  return __ptr;
}

/* MFfopenMem @ 0x08051540, 61 bytes */
undefined4 * MFfopenMem(int param_1,int param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)ecalloc(1,0x24);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    *puVar1 = 2;
    puVar1[5] = param_1;
    puVar1[3] = param_1;
    puVar1[4] = param_1 + param_2;
  }
  return puVar1;
}

/* MFzopen @ 0x08051580, 204 bytes
 * FIXUP: frame emulation: 2 stack locals placed at their original offsets in a 0x60-byte frame (a local's address escapes, see apply_frame_emulation) */
undefined4 MFzopen(int *param_1,char *param_2)

{
  uint uVar1;
  int iVar2;
  unsigned char ghidra_frame[0x60] __attribute__((aligned(16)));
#define local_5c (*(uint (*)[7])(ghidra_frame + 0x4))
#define local_40 (*(size_t *)(ghidra_frame + 0x20))
  
  if ((((*param_1 == 3) && (uVar1 = unzLocateFile((undefined4 *)param_1[2],param_2,2), uVar1 == 0))
      && (iVar2 = unzOpenCurrentFile((undefined4 *)param_1[2]), iVar2 == 0)) &&
     (iVar2 = unzGetCurrentFileInfo
                        ((undefined4 *)param_1[2],local_5c,0,0,0,(void *)0x0,0,(void *)0x0),
     iVar2 == 0)) {
    iVar2 = ecalloc(1,local_40);
    param_1[5] = iVar2;
    param_1[3] = iVar2;
    param_1[4] = iVar2 + local_40;
    do {
      uVar1 = unzeof(param_1[2]);
      if (uVar1 != 0) {
        return 1;
      }
      uVar1 = unzReadCurrentFile(param_1[2],param_1[3],local_40);
    } while (-1 < (int)uVar1);
    unzCloseCurrentFile(param_1[2]);
  }
  return 0;
}
#undef local_5c
#undef local_40

/* MFzclose @ 0x08051650, 16 bytes */
void MFzclose(int param_1)

{
  unzCloseCurrentFile(*(int *)(param_1 + 8));
  return;
}

/* MFfopenZip @ 0x08051660, 102 bytes */
int * MFfopenZip(char *param_1,char *param_2)

{
  int *__ptr;
  undefined4 *puVar1;
  
  __ptr = (int *)ecalloc(1,0x24);
  if (__ptr == (int *)0x0) {
    __ptr = (int *)0x0;
  }
  else {
    *__ptr = 3;
    puVar1 = unzOpen(param_1);
    __ptr[2] = (int)puVar1;
    if (puVar1 == (undefined4 *)0x0) {
      free(__ptr);
      __ptr = (int *)0x0;
    }
    else {
      MFzopen(__ptr,param_2);
    }
  }
  return __ptr;
}

/* MFfclose @ 0x080516d0, 156 bytes */
undefined4 MFfclose(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_1 == (int *)0x0) {
    uVar2 = 0;
  }
  else {
    iVar1 = *param_1;
    if (iVar1 == 2) {
      if ((param_1[6] != 0) && (param_1[7] == 0)) {
        free((void *)param_1[3]);
      }
      param_1[3] = 0;
    }
    else if (iVar1 < 3) {
      if (iVar1 == 1) {
        fclose((FILE *)param_1[1]);
      }
    }
    else if (iVar1 == 3) {
      unzCloseCurrentFile(param_1[2]);
      unzClose((void *)param_1[2]);
      free((void *)param_1[3]);
    }
    free(param_1);
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

/* MFfseek @ 0x08051770, 145 bytes */
undefined4 MFfseek(int *param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = *param_1;
  if (iVar1 == 1) {
    iVar1 = fseek((FILE *)param_1[1],param_2,param_3);
    return iVar1;
  }
  if (iVar1 < 1) {
    return 1;
  }
  if (3 < iVar1) {
    return 1;
  }
  param_1[8] = 0;
  if (param_3 == 1) {
    uVar3 = param_1[5];
  }
  else {
    if (param_3 < 2) {
      if (param_3 != 0) {
        return 1;
      }
      uVar2 = param_1[3];
      uVar3 = uVar2;
      goto LAB_080517e8;
    }
    if (param_3 != 2) {
      return 1;
    }
    uVar3 = param_1[4];
  }
  uVar2 = param_1[3];
LAB_080517e8:
  uVar3 = param_2 + uVar3;
  if ((uVar2 <= uVar3) && (uVar3 <= (uint)param_1[4])) {
    param_1[5] = uVar3;
    return 0;
  }
  return 1;
}

/* MFftell @ 0x08051810, 56 bytes */
int MFftell(int *param_1)

{
  int iVar1;
  long lVar2;
  
  iVar1 = *param_1;
  if (iVar1 != 1) {
    if ((iVar1 < 1) || (3 < iVar1)) {
      iVar1 = -1;
    }
    else {
      iVar1 = param_1[5] - param_1[3];
    }
    return iVar1;
  }
  lVar2 = ftell((FILE *)param_1[1]);
  return lVar2;
}

/* MFigetw @ 0x08051850, 56 bytes */
uint MFigetw(int *param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = MFgetc(param_1);
  if ((uVar1 != 0xffffffff) && (uVar2 = MFgetc(param_1), uVar2 != 0xffffffff)) {
    return uVar2 << 8 | uVar1;
  }
  return 0xffffffff;
}

/* MFigetl @ 0x08051890, 110 bytes */
uint MFigetl(int *param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar1 = MFgetc(param_1);
  if ((((uVar1 != 0xffffffff) && (uVar2 = MFgetc(param_1), uVar2 != 0xffffffff)) &&
      (uVar3 = MFgetc(param_1), uVar3 != 0xffffffff)) &&
     (uVar4 = MFgetc(param_1), uVar4 != 0xffffffff)) {
    return uVar4 << 0x18 | uVar3 << 0x10 | uVar2 << 8 | uVar1;
  }
  return 0xffffffff;
}

/* roundfloat @ 0x08051900, 92 bytes */
int roundfloat(float param_1)

{
  return (int)GHIDRA_FIST32(GHIDRA_FLOOR(param_1 + 0.5));
}

/* _getfileonly @ 0x08051960, 45 bytes */
char * _getfileonly(char *param_1)

{
  size_t sVar1;
  char *pcVar2;
  
  sVar1 = strlen(param_1);
  pcVar2 = param_1 + (sVar1 - 1);
  while( true ) {
    if (pcVar2 <= param_1) {
      return pcVar2;
    }
    if ((*pcVar2 == '/') || (*pcVar2 == '\\')) break;
    pcVar2 = pcVar2 + -1;
  }
  return pcVar2 + 1;
}

