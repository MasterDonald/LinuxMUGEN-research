/*
 * common.c -- common game helpers
 * Warnings to the debug clipboard, fatal error exit, clipboard drawing,
 * quoted string reading and data file lookup.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/common.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* GlobalInputUpdate @ 0x0808d0f0, 1 bytes
 *
 * Empty per-frame global input hook in this build.
 *
 * Called by: CharacterSelectScreen, ContinueScreenLoop, GameInputUpdate,
 *            KeyConfigScreen, ModeSelect, OptionsScreen, PlayCutscene,
 *            VersusScreen
 *
 * Elecbyte file: src/mugen/common.c
 */
void GlobalInputUpdate(void)

{
  return;
}

/* Warn @ 0x0808d100, 68 bytes
 *
 * Appends a run-time warning for a player to the debug clipboard: "<frame>:
 * Warning: Player <name> (<id>) in state <n>:" followed by the message.
 * Shown in the debug display (Ctrl+D); the game continues.
 *
 * Parameters:
 *   player       int
 *   msg          int
 *
 * Player fields read: stateno
 * Globals read: clipboard, frame_count
 * Calls: ClipboardAppend
 * Called by: EvalExpression, ExplodMakeFromInfo, ExplodSetParams,
 *            HelperMake, PlayerSCtrlApplyElem, PlayerSCtrlUpdate,
 *            SCtrlDoPlaySndInfo, SCtrlInitAftImgParams, SCtrlInitEnvShake,
 *            SCtrlInitHitDef, SCtrlInitHitOverride, SCtrlInitPalFX,
 *            SCtrlInitPause, SCtrlInitProjectile, SCtrlTrigEval, SPopI
 * Messages:
 *   "%4i: Warning: Player %s (%i) in state %i:\n%s"
 *
 * Elecbyte file: src/mugen/common.c
 */
uint32_t Warn(int player,int msg)

{
  uint32_t u1;
  
  u1 = 0;
  if (player != 0) {
    u1 = ClipboardAppend((int *)g[G_CLIPBOARD],"%4i: Warning: Player %s (%i) in state %i:\n%s",
                            g[G_FRAME_COUNT],player + 0x20,*(uint32_t *)(player + 4),
                            *(uint32_t *)(player + PLB_STATENO),msg);
  }
  return u1;
}

/* VWarn @ 0x0808d150, 106 bytes
 *
 * printf-style Warn.
 *
 * Parameters:
 *   player       int
 *   fmt          char *
 *
 * Player fields read: stateno
 * Globals read: clipboard, frame_count
 * Calls: ClipboardAppend
 * C library: vsprintf
 * Called by: PlayerChangeAnim, PlayerChangeAnimElem, PlayerChangeState,
 *            PlayerSCtrlApplyElem, SCtrlInitAftImgParams, SCtrlTrigEval
 * Messages:
 *   "%4i: Warning: Player %s (%i) in state %i:\n%s"
 *
 * Elecbyte file: src/mugen/common.c
 * Note: varargs: replaced 1 &stack0x.. with a va_list started after fmt
 * Note: Locals live in `frame`, laid out as on the original stack (0x810 bytes,
 *       1 variables), because their address is taken.
 */
uint32_t VWarn(int player,char *fmt,...)

{
  va_list va;
  va_start(va, fmt);
  uint32_t entry_EAX;
  unsigned char frame[0x810] __attribute__((aligned(16)));
#define stk_80c (*(char (*)[2052])(frame + 0x4))
  
  if (player != 0) {
    vsprintf(stk_80c,fmt,va);
    entry_EAX = ClipboardAppend((int *)g[G_CLIPBOARD],"%4i: Warning: Player %s (%i) in state %i:\n%s",
                             g[G_FRAME_COUNT],player + 0x20,*(uint32_t *)(player + 4),
                             *(uint32_t *)(player + PLB_STATENO),stk_80c);
  }
  return entry_EAX;
}
#undef stk_80c

/* WarnR @ 0x0808d1c0, 88 bytes
 *
 * Warn for an error inside a redirected trigger (helper(n), target,
 * enemy...): also names the player the trigger was redirected from.
 *
 * Parameters:
 *   player       int
 *   msg          int
 *   arg3         int
 *
 * Player fields read: stateno
 * Globals read: clipboard, frame_count
 * Calls: ClipboardAppend
 * Called by: SCtrlTrigEval
 * Messages:
 *   "%4i: Warning: Player %s (%i) in state %i:\nin redirected trigger from
 *     player %s (%i) in state %i:\n%s"
 *
 * Elecbyte file: src/mugen/common.c
 */
int WarnR(int player,int msg,int arg3)

{
  if (player != 0) {
    msg = ClipboardAppend((int *)g[G_CLIPBOARD],
                              "%4i: Warning: Player %s (%i) in state %i:\nin redirected trigger from player %s (%i) in state %i:\n%s"
                              ,g[G_FRAME_COUNT],player + 0x20,*(uint32_t *)(player + 4),
                              *(uint32_t *)(player + PLB_STATENO),msg + 0x20,
                              *(uint32_t *)(msg + 4),*(uint32_t *)(msg + 0xbf4),arg3)
    ;
  }
  return msg;
}

/* StripDoublePercent @ 0x0808d220, 45 bytes
 *
 * Replaces every "%%" in a string by "%" in place (fight.def texts are
 * printf formats).
 *
 * Parameters:
 *   arg1         char *
 *
 * Called by: GameLoadFightData
 *
 * Elecbyte file: src/mugen/common.c
 */
void StripDoublePercent(char *arg1)

{
  char c1;
  int i2;
  int i3;
  
  i3 = 0;
  i2 = 0;
  c1 = *arg1;
  while (c1 != '\0') {
    if ((c1 != '%') || (arg1[i2 + 1] != '%')) {
      arg1[i3] = c1;
      i3 = i3 + 1;
    }
    i2 = i2 + 1;
    c1 = arg1[i2];
  }
  arg1[i3] = '\0';
  return;
}

/* FontDrawClipboard @ 0x0808d250, 168 bytes
 *
 * Draws the lines of a text clipboard, oldest first, one font line apart.
 * Used for the debug text and the select/versus screen texts.
 *
 * Parameters:
 *   arg1         int *
 *   font         int *
 *   arg3         int
 *   arg4         int
 *   arg5         uint32_t
 *
 * Calls: V_FontDraw
 * Called by: CharacterSelectScreenDraw, ShowDebugInfo, VersusScreen
 *
 * Elecbyte file: src/mugen/common.c
 */
void FontDrawClipboard(int *arg1,int *font,int arg3,int arg4,uint32_t arg5)

{
  uint32_t u1;
  
  u1 = arg1[4];
  if (u1 != arg1[5]) {
    do {
      V_FontDraw(*(char **)(*arg1 + u1 * 4),font,arg3,arg4,arg5);
      arg4 = arg4 + font[6] + font[3];
      u1 = u1 + 1 & (arg1[3] <= (int)(u1 + 1)) - 1;
    } while (u1 != arg1[5]);
  }
  if (**(char **)(*arg1 + u1 * 4) == '\0') {
    return;
  }
  V_FontDraw(*(char **)(*arg1 + u1 * 4),font,arg3,arg4,arg5);
  return;
}

/* ErrorExit @ 0x0808d300, 194 bytes
 *
 * Fatal error exit: returns to text mode, prints the library error ("Library
 * (built in) message: %s.") if one is set, then "Error detected." and the
 * engine's ErrorMessage, shuts the library down and exits.
 *
 * Globals read: errmsg
 * Calls: G_SetMode, ErrorGet, ErrorGetStr, ElecDeInit
 * C library: printf, chdir, exit
 * Called by: CharacterSelectScreen, ErrorExitM, EvalExpression,
 *            EvalExpressionF, EvalExpressionI, ExpDivI, ExpMulF, GameInit,
 *            GameLoadAndActivateTeam, GameLoadOptions, GameSaveOptions,
 *            MainLoop, ModeSelect, PlayerGetHitG, PlayerSCtrlApplyElem,
 *            PlayerSCtrlUpdate, ... (32 callers)
 * Messages:
 *   "Library (built in) message: %s.\n\n"
 *   "Error detected.\n\n"
 *   "Error message: %s\n\n"
 *   "Library error message: %s\n\n"
 *   "Out of memory error.\n\n"
 *
 * Elecbyte file: src/mugen/common.c
 */
uint32_t ErrorExit(void)

{
  int i1;
  int i2;
  int stale_EDX;
  int stale_EDX_00;
  char *format;
  uint8_t *pb3;
  int i4;
  int i5;
  
  i5 = 8;
  i4 = 0x19;
  pb3 = (uint8_t *)0x50;
  G_SetMode(0xffffffff,0x50,0x19,8);
  i1 = ErrorGet();
  i2 = stale_EDX;
  if (i1 != 0) {
    pb3 = (uint8_t *)ErrorGetStr();
    printf("Library (built in) message: %s.\n\n",pb3);
    i2 = stale_EDX_00;
  }
  if ((char)g[G_ERRMSG] == '\0') {
    format = "Error detected.\n\n";
  }
  else {
    pb3 = (uint8_t *)(g + G_ERRMSG);
    format = "Error message: %s\n\n";
    i4 = i2;
    i5 = i2;
  }
  i2 = printf(format,pb3,i4,i5);
  if (ErrorMessage[0] != 0) {
    pb3 = ErrorMessage;
    i5 = i2;
    printf("Library error message: %s\n\n",ErrorMessage,i2,i2);
    i4 = i2;
  }
  if (ElecOutOfMem != 0) {
    printf("Out of memory error.\n\n",pb3,i4,i5);
  }
  if (g[0x800] != 0) {
    chdir((char *)g);
  }
  ElecDeInit();
                    /* WARNING: Subroutine does not return */
  exit(1);
}

/* ErrorExitM @ 0x0808d3d0, 39 bytes
 *
 * Stores the printf-formatted message in ErrorMessage and calls ErrorExit.
 *
 * Parameters:
 *   fmt          char *
 *
 * Globals read: errmsg
 * Calls: ErrorExit
 * C library: vsprintf
 * Called by: BuildMenuCtrl, CharacterSelectScreen, GameInit, GameInitPads,
 *            GameLoadOptions, GameReloadSystemSprSnd, ModeSelect,
 *            PlayerChangePal
 *
 * Elecbyte file: src/mugen/common.c
 * Note: varargs: replaced 1 &stack0x.. with a va_list started after fmt
 */
uint32_t ErrorExitM(char *fmt,...)

{
  va_list va;
  va_start(va, fmt);
  uint32_t u1;
  
  vsprintf((char *)(g + G_ERRMSG),fmt,va);
  u1 = ErrorExit();
  return u1;
}

/* fileexist @ 0x0808d400, 51 bytes
 *
 * Returns true if the file can be opened for reading.
 *
 * Parameters:
 *   arg1         char *
 *
 * C library: fopen, fclose
 * Called by: ChangeFileDir, FindFileDirEx, GamePlay, MainLoop
 *
 * Elecbyte file: src/mugen/common.c
 */
bool fileexist(char *arg1)

{
  FILE *stream;
  
  stream = fopen(arg1,"rb");
  if (stream != (FILE *)0x0) {
    fclose(stream);
  }
  return stream != (FILE *)0x0;
}

/* ChangeFileDir @ 0x0808d440, 372 bytes
 *
 * Resolves a data file name the way the content expects: the name (DOS drive
 * letters stripped) is tried relative to the given directory, then in
 * "data/", then in the working directory. The full path found is stored.
 * Sets "Can't find file %s" and returns 0 if none exists. Not called in this
 * build.
 *
 * Parameters:
 *   path         char *
 *   arg2         char *
 *   arg3         char *
 *
 * Globals read: errmsg
 * Calls: splitdirfile, fileexist
 * C library: getcwd, sprintf, chdir, strcpy
 * Messages:
 *   "Can\'t find file %s"
 *
 * Elecbyte file: src/mugen/common.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x5030 bytes,
 *       8 variables), because their address is taken.
 */
uint32_t ChangeFileDir(char *path,char *arg2,char *arg3)

{
  bool b1;
  int i2;
  uint32_t stale_var;
  uint32_t stale_ECX;
  int i3;
  unsigned char frame[0x5030] __attribute__((aligned(16)));
#define buf_502c (*(char (*)[4096])(frame + 0x4))
#define stk_402c (*(char (*)[4096])(frame + 0x1004))
#define stk_302c (*(char (*)[4096])(frame + 0x2004))
#define filename (*(char (*)[4096])(frame + 0x3004))
#define dirname (*(char (*)[4096])(frame + 0x4004))
#define stk_2c (*(uint8_t **)(frame + 0x5004))
#define stk_28 (*(int *)(frame + 0x5008))
#define stk_24 (*(char **)(frame + 0x500c))
  
  if ((*path != '\0') && (path[1] == ':')) {
    path = path + 2;
  }
  getcwd(stk_302c,0xfff);
  stk_24 = stk_402c;
  stk_28 = (int)g + 0xfff;
  stk_2c = &str_empty_3393;
  sprintf(stk_24,"%sdata/",stk_28);
  splitdirfile(path,dirname,filename);
  if ((dirname[0] == '/') || (dirname[0] == '\\')) {
    stk_2c = &d_0827725f;
  }
  i3 = 0;
  do {
    sprintf(buf_502c,"%s%s",(&stk_2c)[i3],dirname);
    i2 = chdir(buf_502c);
    if (i2 == 0) {
      b1 = fileexist(filename);
      if (ZEXT8(b1) != 0) {
        strcpy(arg2,stk_302c);
        strcpy(arg3,filename);
        return 1;
      }
    }
    i3 = i3 + 1;
    chdir(stk_302c);
  } while (i3 < 3);
  sprintf((char *)(g + G_ERRMSG),"Can\'t find file %s",path,stale_ECX);
  return 0;
}
#undef buf_502c
#undef stk_402c
#undef stk_302c
#undef filename
#undef dirname
#undef stk_2c
#undef stk_28
#undef stk_24

/* FindFileDir @ 0x0808d5c0, 29 bytes
 *
 * FindFileDirEx without returning which location matched.
 *
 * Parameters:
 *   path         char *
 *   arg2         char *
 *   arg3         char *
 *
 * Calls: FindFileDirEx
 * Called by: GameLoadSystem, InitSelectScreenMatrix, PlayCutscene
 *
 * Elecbyte file: src/mugen/common.c
 */
uint32_t FindFileDir(char *path,char *arg2,char *arg3)

{
  uint32_t u1;
  
  u1 = FindFileDirEx(path,arg2,arg3,(uint32_t *)0x0);
  return u1;
}

/* FindFileDirEx @ 0x0808d5e0, 367 bytes
 *
 * Looks for a file referenced from a definition file. It tries four prefixes
 * in order: the directory given by the caller (none for absolute paths), the
 * motif's directory, no prefix (relative to the working directory), and
 * "data/". A DOS drive letter is stripped first. On success it stores the
 * full path (and, if asked, the directory part) and returns 1. Otherwise it
 * sets "Can't find file %s" and returns 0.
 *
 * Parameters:
 *   path         char *
 *   arg2         char *
 *   arg3         char *
 *   arg4         uint32_t *
 *
 * Globals read: errmsg
 * Calls: splitdirfile, fileexist
 * C library: strncpy, sprintf, strcpy
 * Called by: FindFileDir, GameLoadFightData
 * Messages:
 *   "Can\'t find file %s"
 *
 * Elecbyte file: src/mugen/common.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x3040 bytes,
 *       10 variables), because their address is taken.
 */
uint32_t FindFileDirEx(char *path,char *arg2,char *arg3,uint32_t *arg4)

{
  bool b1;
  uint32_t stale_var;
  char *saved_EBX;
  int i2;
  unsigned char frame[0x3040] __attribute__((aligned(16)));
#define stk_3040 (*(int *)(frame + 0x0))
#define stk_303c (*(char (*)[2])(frame + 0x4))
#define stk_303a (*(uint8_t *)(frame + 0x6))
#define stk_302c (*(char (*)[4096])(frame + 0x14))
#define filename (*(char (*)[4096])(frame + 0x1014))
#define dirname (*(char (*)[4096])(frame + 0x2014))
#define stk_2c (*(uint32_t **)(frame + 0x3014))
#define stk_28 (*(int *)(frame + 0x3018))
#define stk_24 (*(uint8_t **)(frame + 0x301c))
#define stk_20 (*(char **)(frame + 0x3020))
  
  if ((*path == '\0') || (path[1] != ':')) {
    stk_303c[0] = '\0';
  }
  else {
    strncpy(stk_303c,path,2);
    stk_303a = 0;
    path = path + 2;
  }
  stk_2c = arg4;
  stk_28 = (int)g + 0x15aff;
  stk_24 = &str_empty_3393;
  stk_20 = "data/";
  splitdirfile(path,dirname,filename);
  if ((dirname[0] == '/') || (dirname[0] == '\\')) {
    stk_2c = (uint32_t *)&d_0827725f;
  }
  stk_3040 = 0;
  i2 = 0;
  do {
    if (*(int *)((int)&stk_2c + i2) != 0) {
      saved_EBX = stk_302c;
      sprintf(saved_EBX,"%s%s%s",*(int *)((int)&stk_2c + i2),dirname,filename);
      b1 = fileexist(saved_EBX);
      if (ZEXT8(b1) != 0) {
        if (arg3 != (char *)0x0) {
          sprintf(arg3,"%s%s",*(uint32_t *)((int)&stk_2c + i2),dirname);
        }
        strcpy(arg2,saved_EBX);
        return 1;
      }
    }
    i2 = i2 + 4;
    stk_3040 = stk_3040 + 1;
  } while (stk_3040 < 4);
  sprintf((char *)(g + G_ERRMSG),"Can\'t find file %s",path,saved_EBX);
  return 0;
}
#undef stk_3040
#undef stk_303c
#undef stk_303a
#undef stk_302c
#undef filename
#undef dirname
#undef stk_2c
#undef stk_28
#undef stk_24
#undef stk_20

/* GetQuotedString @ 0x0808d750, 209 bytes
 *
 * Reads a quoted string value ("name = \"Kung Fu Man\"") into a buffer,
 * stripping the quotes. A missing key uses `defval` when given; otherwise it
 * sets "Cannot find parameter: %s". A value without quotes is an error
 * ("String value for %s must be in quotes").
 *
 * Parameters:
 *   tp           int
 *   keyname      char *
 *   buf          char *
 *   size         size_t
 *   defval       char *
 *
 * Globals read: errmsg
 * Calls: TPGetValue
 * C library: strcpy, strlen, sprintf
 * Called by: FindCharacters, GameLoadSystem, PlayerDefLoadPtr,
 *            PlayerDefLoadZip, SCtrlParseHelper
 * Messages:
 *   "Cannot find parameter: %s"
 *   "') && (value2[s2 - 1] == '\"')) {       n2 = s2 - 2;       if
 *     ((int)size < (int)(s2 - 2)) {         n2 = size;       }
 *     strncpy(buf,value2 + 1,n2);       buf[n2] = '\0';       return 1;
 *     }     if (defval == (char *)0x0) {       s3 = g + G_ERRMSG;
 *     value2 = "
 *   ";     }     else {       s3 = g + G_ERRMSG;       value2 = "
 *
 * Elecbyte file: src/mugen/common.c
 */
uint32_t GetQuotedString(int tp,char *keyname,char *buf,size_t size,char *defval)

{
  char *value2;
  size_t s2;
  int *s3;
  size_t stale_ECX;
  size_t stale_EDX;
  size_t n2;
  
  value2 = TPGetValue(tp,keyname);
  if (value2 == (char *)0x0) {
    if (defval != (char *)0x0) {
      strcpy((char *)(g + G_ERRMSG),defval);
      return 0;
    }
    s3 = g + G_ERRMSG;
    value2 = "Cannot find parameter: %s";
    s2 = stale_ECX;
  }
  else {
    s2 = strlen(value2);
    if ((*value2 == '\"') && (value2[s2 - 1] == '\"')) {
      n2 = s2 - 2;
      if ((int)size < (int)(s2 - 2)) {
        n2 = size;
      }
      strncpy(buf,value2 + 1,n2);
      buf[n2] = '\0';
      return 1;
    }
    if (defval == (char *)0x0) {
      s3 = g + G_ERRMSG;
      value2 = "String value for %s must be in quotes";
    }
    else {
      s3 = g + G_ERRMSG;
      value2 = "String must be in quotes\n%s";
      keyname = defval;
      s2 = stale_EDX;
    }
  }
  sprintf((char *)s3,value2,keyname,s2);
  return 0;
}

