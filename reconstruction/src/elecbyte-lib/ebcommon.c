/*
 * ebcommon.c -- common helpers and MF streams
 * Error codes, allocation with out-of-memory flag, file type detection, path
 * and string helpers, and the MF stream abstraction that reads files from
 * disk, memory or zip archives.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/ebcommon.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* ecalloc @ 0x08050cd0, 39 bytes
 *
 * calloc() that sets the global out-of-memory flag ElecOutOfMem when the
 * allocation fails. Returns the block or NULL.
 *
 * Parameters:
 *   count        size_t
 *   size         size_t
 *
 * C library: calloc
 * Called by: AftImgInit, AftImgNew, AnimNew, AnimPerArrayNew,
 *            AnimRCReadFileTP, BGArrayNew, BGArrayReadCtrlTP,
 *            BGParalSetup, ClsnArrayNew, EB_GUIInit, EB_GUINewWindow,
 *            ExplodArrayNew, GameInit, GameVarInit, InfixToPostfix,
 *            MFfopenFile, ... (44 callers)
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
void * ecalloc(size_t count,size_t size)

{
  void *pv1;
  
  pv1 = calloc(count,size);
  if (pv1 == (void *)0x0) {
    ElecOutOfMem = 1;
  }
  return pv1;
}

/* ErrorSet @ 0x08050d00, 10 bytes
 *
 * Stores the engine error code that ErrorGetStr turns into a message: 0
 * none, 1 fonts, 2 sound, 3 graphics, 4 video mode.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: ElecInit, G_Init, G_SetMode, GameInit, GameVarLoadFonts,
 *            SndInit
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
int ErrorSet(int arg1)

{
  ErrorNumber = arg1;
  return arg1;
}

/* ErrorGet @ 0x08050d10, 6 bytes
 *
 * Returns the current engine error code.
 *
 * Called by: ErrorExit, SndInit
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
int ErrorGet(void)

{
  return ErrorNumber;
}

/* ErrorGetStr @ 0x08050d20, 70 bytes
 *
 * Returns the message for the current error code: 1 "Can't load fonts", 2
 * "Can't init sound", 3 "Can't init graphics", 4 "Can't change video mode",
 * anything else "Error not defined". ErrorExit prints it when the engine
 * stops.
 *
 * Called by: ErrorExit
 * Messages:
 *   "Can\'t init sound"
 *   "Can\'t load fonts"
 *   "Can\'t init graphics"
 *   "Can\'t change video mode"
 *   "Error not defined"
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
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

/* CheckExtension @ 0x08050d70, 394 bytes
 *
 * Classifies a file name by its extension (case-insensitive). Returns 1 pcx,
 * 2 sff, 3 wav, 4 snd, 5 mp3, 6 mid, 7 mod/s3m/xm (tracker music), 8 da, 9
 * zip, and 0 for anything else. Callers use it to pick the loader for
 * sprites, sounds, music and zipped characters.
 *
 * Parameters:
 *   arg1         char *
 *
 * C library: strlen, _alemu_stricmp
 * Called by: BGMCheckExtension, FindCharacters, PlayerDefLoad,
 *            SndReadFile, SpriteReadFile
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
uint32_t CheckExtension(char *arg1)

{
  char *pc1;
  size_t s2;
  int i3;
  uint32_t u4;
  
  s2 = strlen(arg1);
  if (((int)s2 < 5) || (arg1[s2 - 4] != '.')) {
L_08050ea3:
    if ((3 < (int)s2) && (arg1[s2 - 3] == '.')) {
      i3 = _alemu_stricmp(arg1 + (s2 - 2),"xm");
      if (i3 == 0) goto L_08050ec8;
      i3 = _alemu_stricmp(arg1 + (s2 - 2),"da");
      if (i3 == 0) {
        return 8;
      }
    }
    u4 = 0;
  }
  else {
    pc1 = arg1 + (s2 - 3);
    i3 = _alemu_stricmp(pc1,"pcx");
    if (i3 == 0) {
      return 1;
    }
    i3 = _alemu_stricmp(pc1,"sff");
    if (i3 == 0) {
      return 2;
    }
    i3 = _alemu_stricmp(pc1,"wav");
    if (i3 == 0) {
      return 3;
    }
    i3 = _alemu_stricmp(pc1,"snd");
    if (i3 == 0) {
      return 4;
    }
    i3 = _alemu_stricmp(pc1,"mp3");
    if (i3 == 0) {
      return 5;
    }
    i3 = _alemu_stricmp(pc1,"mid");
    if (i3 == 0) {
      return 6;
    }
    i3 = _alemu_stricmp(pc1,"mod");
    if ((i3 != 0) && (i3 = _alemu_stricmp(pc1,"s3m"), i3 != 0)) {
      i3 = _alemu_stricmp(pc1,"zip");
      if (i3 == 0) {
        return 9;
      }
      goto L_08050ea3;
    }
L_08050ec8:
    u4 = 7;
  }
  return u4;
}

/* igetw @ 0x08050f00, 56 bytes
 *
 * Reads a little-endian 16-bit value from a stdio FILE (two fgetc calls).
 * Returns -1 at end of file. Not called in this build.
 *
 * Parameters:
 *   arg1         _IO_FILE *
 *
 * C library: fgetc
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
uint32_t igetw(_IO_FILE *arg1)

{
  uint32_t u1;
  int i2;
  
  u1 = fgetc(arg1);
  if ((u1 != 0xffffffff) && (i2 = fgetc(arg1), i2 != -1)) {
    return i2 << 8 | u1;
  }
  return 0xffffffff;
}

/* igetl @ 0x08050f40, 110 bytes
 *
 * Reads a little-endian 32-bit value from a stdio FILE (four fgetc calls).
 * Not called in this build.
 *
 * Parameters:
 *   arg1         _IO_FILE *
 *
 * C library: fgetc
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
uint32_t igetl(_IO_FILE *arg1)

{
  uint32_t u1;
  int i2;
  int i3;
  int i4;
  
  u1 = fgetc(arg1);
  if ((((u1 != 0xffffffff) && (i2 = fgetc(arg1), i2 != -1)) &&
      (i3 = fgetc(arg1), i3 != -1)) && (i4 = fgetc(arg1), i4 != -1)) {
    return i4 << 0x18 | i3 << 0x10 | i2 << 8 | u1;
  }
  return 0xffffffff;
}

/* strimatch @ 0x08050fb0, 74 bytes
 *
 * Case-insensitive prefix comparison: compares character by character until
 * either string ends. Returns true when no character differs, i.e. when one
 * string is a prefix of the other (an empty `str` always matches). Callers
 * rely on this to match keys and group names by their beginning, for example
 * "begin action " against "Begin Action 200".
 *
 * Parameters:
 *   str          char *
 *   pattern      char *
 *
 * Called by: AnimRCReadFileTP, BGArrayReadCtrlTP, BGArrayReadTP,
 *            GameLoadFightData, GameLoadSystem, PlayerCMDLoadTP,
 *            SCtrlParseState, SctrlAddFileTP, SctrlReadFileTP,
 *            SiSceneReadTP, TPGroupMatchCount
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
uint32_t strimatch(char *str,char *pattern)

{
  char c1;
  int i2;
  
  i2 = 0;
  if (*str != '\0') {
    c1 = *pattern;
    while (c1 != '\0') {
      if (*(int *)(__ctype_tolower + str[i2] * 4) !=
          *(int *)(__ctype_tolower + pattern[i2] * 4)) {
        return 0;
      }
      i2 = i2 + 1;
      if (str[i2] == '\0') {
        return 1;
      }
      c1 = pattern[i2];
    }
  }
  return 1;
}

/* strimatchlen @ 0x08051000, 79 bytes
 *
 * Case-insensitive comparison of the first `len` characters of `str` and
 * `pattern`. Used to match key prefixes such as "bg." or "Clsn1[".
 *
 * Parameters:
 *   str          int
 *   pattern      int
 *   len          int
 *
 * Called by: AnimRCReadFileTP, BGArrayReadCtrlTP, ClsnParseLine,
 *            SCtrlParseElemType, SCtrlParseHelper, SCtrlParseTrigger,
 *            TPGetLineNo_Skip, TPGetValue, TPGetValueNext, TPGroupSeek
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
uint32_t strimatchlen(int str,int pattern,int len)

{
  int i2;
  
  i2 = 0;
  if (0 < len) {
    do {
      if (((*(int *)(__ctype_tolower + *(char *)(i2 + str) * 4) !=
            *(int *)(__ctype_tolower + *(char *)(i2 + pattern) * 4)) ||
          (*(char *)(i2 + str) == '\0')) || (*(char *)(i2 + pattern) == '\0')) {
        return 0;
      }
      i2 = i2 + 1;
    } while (i2 < len);
  }
  return 1;
}

/* strmatchlen @ 0x08051050, 49 bytes
 *
 * Case-sensitive comparison of the first `len` characters.
 *
 * Parameters:
 *   str          int
 *   pattern      int
 *   len          int
 *
 * Called by: GameBGLoad, InfoTextDraw, QuickVSSetup, TPGetLineNo_Skip,
 *            TPGetValue, TPGetValueNext
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
uint32_t strmatchlen(int str,int pattern,int len)

{
  int i2;
  
  i2 = 0;
  if (0 < len) {
    do {
      if ((*(char *)(i2 + str) != *(char *)(i2 + pattern)) ||
         (*(char *)(i2 + str) == '\0')) {
        return 0;
      }
      i2 = i2 + 1;
    } while (i2 < len);
  }
  return 1;
}

/* strtoupper @ 0x08051090, 39 bytes
 *
 * Copies the second string into the first, converted to upper case. The
 * terminating NUL is not written. Not called in this build.
 *
 * Parameters:
 *   arg1         uint8_t *
 *   arg2         char *
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
void strtoupper(uint8_t *arg1,char *arg2)

{
  char c1;
  
  c1 = *arg2;
  while (c1 != '\0') {
    c1 = *arg2;
    arg2 = arg2 + 1;
    *arg1 = (char)*(uint32_t *)(__ctype_toupper + c1 * 4);
    arg1 = arg1 + 1;
    c1 = *arg2;
  }
  return;
}

/* splitdirfile @ 0x080510c0, 121 bytes
 *
 * Splits `path` at its last '/' or '\' into `dirname` (up to and including
 * the separator) and `filename`. Either output may be NULL. With no
 * separator, dirname is empty.
 *
 * Parameters:
 *   path         char *
 *   dirname      char *
 *   filename     char *
 *
 * C library: strlen, strcpy, strncpy
 * Called by: BGArrayReadFileSA, ChangeFileDir, FindCharacters,
 *            FindFileDirEx, GameBGLoad, GameInit, GameLoadFightData,
 *            GameLoadOptions, QuickVSSetup, SceneReadFile
 *
 * Elecbyte file: src/lib/ebcommon.c
 * Note: 3 exact-text site patches (see SITE_PATCHES in
 *       tools/build_source_tree.py)
 */
char * splitdirfile(char *path,char *dirname,char *filename)

{
  char c1;
  char *entry_EAX;
  char *pc2;
  char *n;
  
  if (*path == '\0') {
    if (dirname != (char *)0x0) {
      *dirname = '\0';
    }
    if (filename != (char *)0x0) {
      *filename = '\0';
    }
  }
  else {
    entry_EAX = (char *)strlen(path);
    pc2 = entry_EAX;
    while (n = pc2, pc2 = n + -1, -1 < (int)pc2) {
      c1 = path[(int)pc2];
      entry_EAX = (char *)CONCAT31((uint32_t)((uint32_t)entry_EAX >> 8),c1);
      if ((c1 == '\\') || (c1 == '/')) break;
    }
    if (filename != (char *)0x0) {
      entry_EAX = strcpy(filename,path + (int)n);
    }
    if (dirname != (char *)0x0) {
      if (0 < (int)n) {
        entry_EAX = strncpy(dirname,path,(size_t)n);
      }
      dirname[(int)n] = '\0';
    }
  }
  return entry_EAX;
}

/* joindirfile @ 0x08051140, 116 bytes
 *
 * Builds `dest` = dirname + "/" + filename. The "/" is added only when
 * dirname is not empty and does not already end in a separator. If
 * `filename` is already absolute (isabsolutedir), it is copied unchanged.
 *
 * Parameters:
 *   dest         char *
 *   dirname      char *
 *   filename     char *
 *
 * Calls: isabsolutedir
 * C library: strcpy, strlen, strcat
 * Called by: BGArrayReadTP, FindCharacters, GameLoadSystem, GamePlay,
 *            GameReloadSystemSprSnd, GameStgInitFightData,
 *            PlayerCacheClear, PlayerCacheLoad, PlayerDefLoad,
 *            PlayerDefLoadPtr, PlayerDefLoadZip, SiSceneReadTP,
 *            SiSceneUpdate
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
char * joindirfile(char *dest,char *dirname,char *filename)

{
  int i1;
  char *pc2;
  size_t s3;
  
  i1 = isabsolutedir(filename);
  if (i1 != 0) {
    pc2 = strcpy(dest,filename);
    return pc2;
  }
  strcpy(dest,dirname);
  s3 = strlen(dest);
  if (((0 < (int)s3) && (dest[s3 - 1] != '/')) && (dest[s3 - 1] != '\\')) {
    strcat(dest,"/");
  }
  pc2 = strcat(dest,filename);
  return pc2;
}

/* isabsolutedir @ 0x080511c0, 34 bytes
 *
 * Returns true when `path` starts with '/' or '\', or with a DOS drive
 * letter ("C:").
 *
 * Parameters:
 *   path         char *
 *
 * Called by: FindCharacters, joindirfile
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
uint32_t isabsolutedir(char *path)

{
  char c1;
  uint32_t u2;
  
  u2 = 0;
  c1 = *path;
  if (((c1 == '/') || (c1 == '\\')) || ((c1 != '\0' && (path[1] == ':')))) {
    u2 = 1;
  }
  return u2;
}

/* ffilelength @ 0x080511f0, 62 bytes
 *
 * Returns the length of an open stdio file (seek to end, ftell, seek back to
 * the old position).
 *
 * Parameters:
 *   arg1         FILE *
 *
 * C library: ftell, fseek
 * Called by: SndReadFile, SpriteReadFile, TPReadFilePtr
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
long ffilelength(FILE *arg1)

{
  long off;
  long l1;
  
  off = ftell(arg1);
  fseek(arg1,0,2);
  l1 = ftell(arg1);
  fseek(arg1,off,0);
  return l1;
}

/* strcpyslash @ 0x08051230, 42 bytes
 *
 * Copies a string, turning every '\' into '/'. Used to accept DOS-style
 * paths from the Windows-era content. Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *   arg2         char *
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
void strcpyslash(int arg1,char *arg2)

{
  char c1;
  int i2;
  
  i2 = 0;
  c1 = *arg2;
  while (c1 != '\0') {
    *(char *)(i2 + arg1) = c1;
    if (c1 == '\\') {
      *(uint8_t *)(i2 + arg1) = 0x2f;
    }
    i2 = i2 + 1;
    c1 = arg2[i2];
  }
  *(uint8_t *)(i2 + arg1) = 0;
  return;
}

/* IntSwap @ 0x08051260, 19 bytes
 *
 * Swaps two ints through pointers.
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         uint32_t *
 *
 * Called by: CharacterSelectMenuKey
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
void IntSwap(uint32_t *arg1,uint32_t *arg2)

{
  uint32_t u1;
  
  u1 = *arg1;
  *arg1 = *arg2;
  *arg2 = u1;
  return;
}

/* IntMin @ 0x08051280, 15 bytes
 *
 * Returns the smaller of two ints.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Called by: AILearnClsnUpdate, AILearnIdleClsnUpdate
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
int IntMin(int arg1,int arg2)

{
  if (arg2 < arg1) {
    arg1 = arg2;
  }
  return arg1;
}

/* IntMax @ 0x08051290, 15 bytes
 *
 * Returns the larger of two ints.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Called by: AILearnClsnUpdate, AILearnIdleClsnUpdate
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
int IntMax(int arg1,int arg2)

{
  if (arg1 < arg2) {
    arg1 = arg2;
  }
  return arg1;
}

/* DebugErrorExit @ 0x080512a0, 83 bytes
 *
 * Leaves graphics mode (G_SetMode text), prints "Error detected." with the
 * given message and exits. A debugging helper with no callers in this build.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: G_SetMode
 * C library: printf, chdir, exit
 * Messages:
 *   "Error detected.\n\n"
 *   "Error message: %s\n\n"
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
void DebugErrorExit(int arg1)

{
  uint32_t u1;
  char *format;
  int i2;
  uint32_t u3;
  uint32_t u4;
  
  u4 = 8;
  u3 = 0x19;
  i2 = 0x50;
  u1 = G_SetMode(0xffffffff,0x50,0x19,8);
  if (arg1 == 0) {
    format = "Error detected.\n\n";
  }
  else {
    format = "Error message: %s\n\n";
    i2 = arg1;
    u3 = u1;
    u4 = u1;
  }
  printf(format,i2,u3,u4);
  chdir("/djgpp/elecbyte");
                    /* WARNING: Subroutine does not return */
  exit(1);
}

/* MFgetc @ 0x08051300, 80 bytes
 *
 * Reads one byte from an MF stream (the engine's file abstraction; see
 * MFfopenFile). Type 1 streams wrap a stdio FILE and use fgetc. Types 2 and
 * 3 (memory and zip) read from the memory buffer and set the EOF flag at its
 * end. Returns the byte, or -1 at end of file.
 *
 * Parameters:
 *   mf           int *
 *
 * C library: fgetc
 * Called by: MFigetl, MFigetw, Pal4Read3FilePtr, SndReadFileWAVPtr,
 *            SpriteReadPCXRawPtr
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
uint32_t MFgetc(int *mf)

{
  uint8_t b1;
  int i2;
  uint8_t *pb3;
  uint32_t u4;
  
  i2 = *mf;
  if (i2 == 1) {
    u4 = fgetc((_IO_FILE *)mf[1]);
    return u4;
  }
  if ((0 < i2) && (i2 < 4)) {
    pb3 = (uint8_t *)mf[5];
    if (pb3 != (uint8_t *)mf[4]) {
      b1 = *pb3;
      mf[5] = (int)(pb3 + 1);
      return (uint32_t)b1;
    }
    mf[8] = 1;
  }
  return 0xffffffff;
}

/* MFfgets @ 0x08051350, 145 bytes
 *
 * fgets() for MF streams: reads up to size-1 bytes, stopping after a
 * newline, and NUL-terminates the buffer. Returns `buf`, or NULL at end of
 * file. TPReadMFPtr reads text files with it.
 *
 * Parameters:
 *   buf          char *
 *   size         int
 *   mf           int *
 *
 * C library: fgets
 * Called by: TPReadMFPtr
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
char * MFfgets(char *buf,int size,int *mf)

{
  char c1;
  char *pc2;
  char *pc3;
  int i4;
  
  i4 = *mf;
  if (i4 == 1) {
    pc3 = fgets(buf,size,(FILE *)mf[1]);
    return pc3;
  }
  if ((i4 < 1) || (3 < i4)) {
L_080513d7:
    buf = (char *)0x0;
  }
  else {
    pc3 = buf;
    for (i4 = 0; i4 < size + -1; i4 = i4 + 1) {
      pc2 = (char *)mf[5];
      if (pc2 == (char *)mf[4]) {
        mf[8] = 1;
        goto L_080513d7;
      }
      c1 = *pc2;
      mf[5] = (int)(pc2 + 1);
      if ((c1 == '\n') || (c1 == '\r')) break;
      *pc3 = c1;
      pc3 = pc3 + 1;
    }
    *pc3 = '\0';
  }
  return buf;
}

/* MFfread @ 0x080513f0, 171 bytes
 *
 * fread() for MF streams: stdio for type 1, a memcpy from the buffer for
 * memory and zip streams (setting EOF when the buffer runs out). Returns the
 * number of complete items read.
 *
 * Parameters:
 *   ptr          void *
 *   size         size_t
 *   n            size_t
 *   mf           int *
 *
 * C library: memcpy, fread
 * Called by: FontReadFilePtr, SndReadFileSNDPtr, SndReadFileWAVPtr,
 *            SpriteReadSFFListPtr, SpriteReadSFFListPtr_1_01,
 *            SpriteReadSFFPtr, SpriteReadSFFPtr_1_01
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
size_t MFfread(void *ptr,size_t size,size_t n,int *mf)

{
  int i1;
  void *src;
  size_t s2;
  
  i1 = *mf;
  if (i1 != 1) {
    if ((i1 < 1) || (3 < i1)) {
      n = 0xffffffff;
    }
    else {
      src = (void *)mf[5];
      s2 = size * n;
      if ((void *)mf[4] < (void *)(s2 + (int)src)) {
        s2 = mf[4] - (int)src;
        memcpy(ptr,src,s2);
        n = 0xffffffff;
        mf[5] = mf[5] + s2;
        mf[8] = 1;
      }
      else {
        memcpy(ptr,src,s2);
        mf[5] = mf[5] + s2;
      }
    }
    return n;
  }
  s2 = fread(ptr,size,n,(FILE *)mf[1]);
  return s2;
}

/* MFfeof @ 0x080514a0, 57 bytes
 *
 * Returns the end-of-file flag of an MF stream (feof for stdio streams).
 *
 * Parameters:
 *   mf           int *
 *
 * C library: feof
 * Called by: Pal4Read3FilePtr, SndReadFileWAVPtr, SpriteReadPCXRawPtr
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
int MFfeof(int *mf)

{
  int i1;
  
  i1 = *mf;
  if (i1 != 1) {
    if ((i1 < 1) || (3 < i1)) {
      i1 = 1;
    }
    else {
      i1 = mf[8];
    }
    return i1;
  }
  i1 = feof((FILE *)mf[1]);
  return i1;
}

/* MFfopenFile @ 0x080514e0, 87 bytes
 *
 * Opens a disk file as an MF stream of type 1 (stdio FILE). Returns the
 * stream or NULL.
 *
 * Parameters:
 *   filename     char *
 *   mode2        char *  (mode)
 *
 * Calls: ecalloc
 * C library: fopen, free
 * Called by: FontReadFile, PlayerDefLoadZip, SndReadFile, SpriteReadFile,
 *            SpriteReadSFFList
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
uint32_t * MFfopenFile(char *filename,char *mode2)

{
  uint32_t *mem;
  FILE *pFVar1;
  
  mem = (uint32_t *)ecalloc(1,0x24);
  if (mem == (uint32_t *)0x0) {
    mem = (uint32_t *)0x0;
  }
  else {
    *mem = 1;
    pFVar1 = fopen(filename,mode2);
    mem[1] = pFVar1;
    if (pFVar1 == (FILE *)0x0) {
      free(mem);
      mem = (uint32_t *)0x0;
    }
  }
  return mem;
}

/* MFfopenMem @ 0x08051540, 61 bytes
 *
 * Wraps a memory block as an MF stream of type 2: read cursor at `data`, end
 * at data + size. Used when a sound or sprite file is already in memory.
 *
 * Parameters:
 *   data         int
 *   size         int
 *
 * Calls: ecalloc
 * Called by: SndReadFile, SpriteReadFile
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
uint32_t * MFfopenMem(int data,int size)

{
  uint32_t *mem;
  
  mem = (uint32_t *)ecalloc(1,0x24);
  if (mem == (uint32_t *)0x0) {
    mem = (uint32_t *)0x0;
  }
  else {
    *mem = 2;
    mem[5] = data;
    mem[3] = data;
    mem[4] = data + size;
  }
  return mem;
}

/* MFzopen @ 0x08051580, 204 bytes
 *
 * Selects a member of the zip archive behind a type-3 MF stream. It locates
 * `filename` (case-insensitive), opens it and reads it into a newly
 * allocated buffer, which becomes the stream's data. Returns 1 on success, 0
 * if the member is missing or unreadable. Characters can be loaded from .zip
 * files this way (PlayerDefLoadZip).
 *
 * Parameters:
 *   mf           int *
 *   filename     char *
 *
 * Calls: unzLocateFile, unzOpenCurrentFile, unzGetCurrentFileInfo,
 *        ecalloc, unzeof, unzReadCurrentFile, unzCloseCurrentFile
 * Called by: FindCharacters, MFfopenZip, PlayerDefLoadZip
 *
 * Elecbyte file: src/lib/ebcommon.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x60 bytes, 2
 *       variables), because their address is taken.
 */
uint32_t MFzopen(int *mf,char *filename)

{
  uint32_t u1;
  int mem;
  unsigned char frame[0x60] __attribute__((aligned(16)));
#define stk_5c (*(uint32_t (*)[7])(frame + 0x4))
#define stk_40 (*(size_t *)(frame + 0x20))
  
  if ((((*mf == 3) && (u1 = unzLocateFile((uint32_t *)mf[2],filename,2), u1 == 0))
      && (mem = unzOpenCurrentFile((uint32_t *)mf[2]), mem == 0)) &&
     (mem = unzGetCurrentFileInfo
                        ((uint32_t *)mf[2],stk_5c,0,0,0,(void *)0x0,0,(void *)0x0),
     mem == 0)) {
    mem = ecalloc(1,stk_40);
    mf[5] = mem;
    mf[3] = mem;
    mf[4] = mem + stk_40;
    do {
      u1 = unzeof(mf[2]);
      if (u1 != 0) {
        return 1;
      }
      u1 = unzReadCurrentFile(mf[2],mf[3],stk_40);
    } while (-1 < (int)u1);
    unzCloseCurrentFile(mf[2]);
  }
  return 0;
}
#undef stk_5c
#undef stk_40

/* MFzclose @ 0x08051650, 16 bytes
 *
 * Closes the current member of a zip MF stream (unzCloseCurrentFile).
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: unzCloseCurrentFile
 * Called by: FindCharacters, PlayerDefLoadZip
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
void MFzclose(int arg1)

{
  unzCloseCurrentFile(*(int *)(arg1 + 8));
  return;
}

/* MFfopenZip @ 0x08051660, 102 bytes
 *
 * Opens a zip archive (unzOpen) as an MF stream of type 3 and, when
 * `filename` is given, selects that member with MFzopen. Returns the stream
 * or NULL.
 *
 * Parameters:
 *   path         char *
 *   filename     char *
 *
 * Calls: ecalloc, unzOpen, MFzopen
 * C library: free
 * Called by: FindCharacters, PlayerDefLoad
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
int * MFfopenZip(char *path,char *filename)

{
  int *mem;
  uint32_t *zipfile;
  
  mem = (int *)ecalloc(1,0x24);
  if (mem == (int *)0x0) {
    mem = (int *)0x0;
  }
  else {
    *mem = 3;
    zipfile = unzOpen(path);
    mem[2] = (int)zipfile;
    if (zipfile == (uint32_t *)0x0) {
      free(mem);
      mem = (int *)0x0;
    }
    else {
      MFzopen(mem,filename);
    }
  }
  return mem;
}

/* MFfclose @ 0x080516d0, 156 bytes
 *
 * Closes an MF stream: fclose for stdio streams; frees the buffer and closes
 * the zip member and archive for zip streams. Then frees the stream record.
 *
 * Parameters:
 *   mf           int *
 *
 * Calls: unzCloseCurrentFile, unzClose
 * C library: free, fclose
 * Called by: FindCharacters, FontReadFile, Pal4Read3FilePtr,
 *            PlayerDefLoad, PlayerDefLoadZip, SndReadFile, SpriteReadFile,
 *            SpriteReadSFFList
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
uint32_t MFfclose(int *mf)

{
  int i1;
  uint32_t u2;
  
  if (mf == (int *)0x0) {
    u2 = 0;
  }
  else {
    i1 = *mf;
    if (i1 == 2) {
      if ((mf[6] != 0) && (mf[7] == 0)) {
        free((void *)mf[3]);
      }
      mf[3] = 0;
    }
    else if (i1 < 3) {
      if (i1 == 1) {
        fclose((FILE *)mf[1]);
      }
    }
    else if (i1 == 3) {
      unzCloseCurrentFile(mf[2]);
      unzClose((void *)mf[2]);
      free((void *)mf[3]);
    }
    free(mf);
    u2 = 0xffffffff;
  }
  return u2;
}

/* MFfseek @ 0x08051770, 145 bytes
 *
 * fseek() for MF streams. Memory and zip streams move their read cursor
 * (SEEK_SET, SEEK_CUR or SEEK_END) and clear the EOF flag. Returns 0 on
 * success, 1 if the target is outside the buffer or `whence` is invalid.
 *
 * Parameters:
 *   mf           int *
 *   offset       int
 *   whence       int
 *
 * C library: fseek
 * Called by: FontReadFilePtr, FontReadFilePtr_0_01, PlayerDefLoadZip,
 *            SndReadFile, SndReadFileSNDPtr, SndReadFileWAVPtr,
 *            SpriteReadFile, SpriteReadPCXRawPtr, SpriteReadSFFListPtr,
 *            SpriteReadSFFListPtr_1_01, SpriteReadSFFPtr,
 *            SpriteReadSFFPtr_1_01
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
uint32_t MFfseek(int *mf,int offset,int whence)

{
  int i1;
  uint32_t u2;
  uint32_t u3;
  
  i1 = *mf;
  if (i1 == 1) {
    i1 = fseek((FILE *)mf[1],offset,whence);
    return i1;
  }
  if (i1 < 1) {
    return 1;
  }
  if (3 < i1) {
    return 1;
  }
  mf[8] = 0;
  if (whence == 1) {
    u3 = mf[5];
  }
  else {
    if (whence < 2) {
      if (whence != 0) {
        return 1;
      }
      u2 = mf[3];
      u3 = u2;
      goto L_080517e8;
    }
    if (whence != 2) {
      return 1;
    }
    u3 = mf[4];
  }
  u2 = mf[3];
L_080517e8:
  u3 = offset + u3;
  if ((u2 <= u3) && (u3 <= (uint32_t)mf[4])) {
    mf[5] = u3;
    return 0;
  }
  return 1;
}

/* MFftell @ 0x08051810, 56 bytes
 *
 * ftell() for MF streams (cursor - start for memory streams).
 *
 * Parameters:
 *   mf           int *
 *
 * C library: ftell
 * Called by: FontReadFilePtr, FontReadFilePtr_0_01, PlayerDefLoadZip,
 *            SndReadFileSNDPtr, SndReadFileWAVPtr, SpriteReadPCXRawPtr,
 *            SpriteReadSFFListPtr, SpriteReadSFFListPtr_1_01,
 *            SpriteReadSFFPtr, SpriteReadSFFPtr_1_01, TPReadMFPtr
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
int MFftell(int *mf)

{
  int i1;
  long l2;
  
  i1 = *mf;
  if (i1 != 1) {
    if ((i1 < 1) || (3 < i1)) {
      i1 = -1;
    }
    else {
      i1 = mf[5] - mf[3];
    }
    return i1;
  }
  l2 = ftell((FILE *)mf[1]);
  return l2;
}

/* MFigetw @ 0x08051850, 56 bytes
 *
 * Reads a little-endian 16-bit value from an MF stream.
 *
 * Parameters:
 *   mf           int *
 *
 * Calls: MFgetc
 * Called by: SndReadFileWAVPtr, SpriteReadPCXRawPtr
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
uint32_t MFigetw(int *mf)

{
  uint32_t ch;
  uint32_t ch2;
  
  ch = MFgetc(mf);
  if ((ch != 0xffffffff) && (ch2 = MFgetc(mf), ch2 != 0xffffffff)) {
    return ch2 << 8 | ch;
  }
  return 0xffffffff;
}

/* MFigetl @ 0x08051890, 110 bytes
 *
 * Reads a little-endian 32-bit value from an MF stream.
 *
 * Parameters:
 *   mf           int *
 *
 * Calls: MFgetc
 * Called by: SndReadFileWAVPtr, SpriteReadPCXRawPtr
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
uint32_t MFigetl(int *mf)

{
  uint32_t ch;
  uint32_t ch2;
  uint32_t ch3;
  uint32_t ch4;
  
  ch = MFgetc(mf);
  if ((((ch != 0xffffffff) && (ch2 = MFgetc(mf), ch2 != 0xffffffff)) &&
      (ch3 = MFgetc(mf), ch3 != 0xffffffff)) &&
     (ch4 = MFgetc(mf), ch4 != 0xffffffff)) {
    return ch4 << 0x18 | ch3 << 0x10 | ch2 << 8 | ch;
  }
  return 0xffffffff;
}

/* roundfloat @ 0x08051900, 92 bytes
 *
 * Rounds a float to the nearest int, halves upward: floor(x + 0.5) converted
 * with x87 FIST semantics (out-of-range values give 0x80000000).
 *
 * Parameters:
 *   x            float
 *
 * Called by: AnimDrawScaleFlip, BGArrayMoveOffset, BGDraw,
 *            BGParalDraw8to16, BGParalDraw8to16Flat,
 *            W_RotateShadowTransSub8to16_P,
 *            W_RotateShadowTransSubMirH8to16_P, W_RotateSprite8to16_P,
 *            W_RotateSpriteMirH8to16_P, W_RotateSpriteTransAdd8to16_B_P,
 *            W_RotateSpriteTransAdd8to16_P,
 *            W_RotateSpriteTransAddMirH8to16_B_P,
 *            W_RotateSpriteTransAddMirH8to16_P,
 *            W_RotateSpriteTransSub8to16_P,
 *            W_RotateSpriteTransSubMirH8to16_P
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
int roundfloat(float x)

{
  return (int)X87_FIST32(X87_FLOOR(x + 0.5));
}

/* _getfileonly @ 0x08051960, 45 bytes
 *
 * Returns a pointer to the file-name part of a path (after the last '/' or
 * '\'). Not called in this build.
 *
 * Parameters:
 *   arg1         char *
 *
 * C library: strlen
 *
 * Elecbyte file: src/lib/ebcommon.c
 */
char * _getfileonly(char *arg1)

{
  size_t s1;
  char *pc2;
  
  s1 = strlen(arg1);
  pc2 = arg1 + (s1 - 1);
  while( true ) {
    if (pc2 <= arg1) {
      return pc2;
    }
    if ((*pc2 == '/') || (*pc2 == '\\')) break;
    pc2 = pc2 + -1;
  }
  return pc2 + 1;
}

