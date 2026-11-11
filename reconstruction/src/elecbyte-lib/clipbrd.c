/*
 * clipbrd.c -- text clipboards
 * Ring buffers of text lines used for the debug text output and the debug
 * GUI windows.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/clipbrd.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* ClipboardNew @ 0x0804e440, 153 bytes
 *
 * Creates a text clipboard: a ring of `lines` text lines of `width`
 * characters each. One block holds the text; a pointer table points at each
 * line. Header layout: [0] line table, [1] text block, [2] width, [3] line
 * count, [4] first line, [5] current line. Returns NULL if `lines` is not
 * positive or an allocation fails.
 *
 * The engine uses clipboards for the debug text that
 * DisplayToClipboard/AppendToClipboard state controllers write and that the
 * debug display shows (Ctrl+D), and for GUI windows.
 *
 * Parameters:
 *   arg1         int
 *   arg2         size_t
 *
 * Calls: ClipboardFree
 * C library: calloc
 * Called by: EB_GUINewWindow, GameVarInit, PlayerNew
 *
 * Elecbyte file: src/lib/clipbrd.c
 */
int * ClipboardNew(int arg1,size_t arg2)

{
  int i1;
  int *clipboard;
  void *pv3;
  int i4;
  int i2;
  
  if ((0 < (int)arg2) && (clipboard = calloc(1,0x18), clipboard != (int *)0x0)) {
    clipboard[2] = arg1;
    clipboard[3] = arg2;
    pv3 = calloc(arg2,4);
    *clipboard = (int)pv3;
    if (pv3 != (void *)0x0) {
      pv3 = calloc(arg1 * arg2,1);
      clipboard[1] = (int)pv3;
      if (pv3 != (void *)0x0) {
        i2 = 0;
        if ((int)arg2 < 1) {
          return clipboard;
        }
        i1 = *clipboard;
        i4 = 0;
        do {
          *(int *)(i1 + i2 * 4) = i4 + clipboard[1];
          i2 = i2 + 1;
          i4 = i4 + arg1;
        } while (i2 < (int)arg2);
        return clipboard;
      }
    }
    ClipboardFree(clipboard);
  }
  return (int *)0x0;
}

/* ClipboardFree @ 0x0804e4e0, 68 bytes
 *
 * Frees a clipboard's text block, line table and header.
 *
 * Parameters:
 *   clipboard    uint32_t *
 *
 * C library: free
 * Called by: ClipboardNew, EB_GUICloseWindow, GameVarDeInit, PlayerFree,
 *            _mangled_main
 *
 * Elecbyte file: src/lib/clipbrd.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: Returns nothing (the original left only stale register values).
 */
void ClipboardFree(uint32_t *clipboard)

{
  uint32_t stale_EAX;
  uint32_t saved_EBX;
  
  if (clipboard != (uint32_t *)0x0) {
    if ((void *)*clipboard != (void *)0x0) {
      free((void *)*clipboard);
    }
    if ((void *)clipboard[1] != (void *)0x0) {
      free((void *)clipboard[1]);
    }
    free(clipboard);
    return;
  }
  return;
}

/* ClipboardClear @ 0x0804e530, 26 bytes
 *
 * Empties a clipboard: first and current line set to 0 and the first line's
 * text cleared.
 *
 * Parameters:
 *   clipboard    uint32_t *
 *
 * Called by: ClipboardPrint, EB_GUINewWindow, GameInputUpdate,
 *            PlayerReset, PlayerSCtrlApplyElem
 *
 * Elecbyte file: src/lib/clipbrd.c
 */
void ClipboardClear(uint32_t *clipboard)

{
  clipboard[5] = 0;
  clipboard[4] = 0;
  **(uint8_t **)*clipboard = 0;
  return;
}

/* ClipboardPrint @ 0x0804e550, 68 bytes
 *
 * Clears the clipboard, then appends the printf-style text
 * (ClipboardAppend).
 *
 * Parameters:
 *   clipboard    int *
 *   fmt          char *
 *
 * Calls: ClipboardClear, ClipboardAppend
 * C library: vsprintf
 * Called by: PlayerSCtrlApplyElem
 *
 * Elecbyte file: src/lib/clipbrd.c
 * Note: varargs: replaced 1 &stack0x.. with a va_list started after fmt
 * Note: Locals live in `frame`, laid out as on the original stack (0x410 bytes,
 *       1 variables), because their address is taken.
 */
void ClipboardPrint(int *clipboard,char *fmt,...)

{
  va_list va;
  va_start(va, fmt);
  unsigned char frame[0x410] __attribute__((aligned(16)));
#define fmt2 (*(char (*)[1028])(frame + 0x4))
  
  ClipboardClear(clipboard);
  vsprintf(fmt2,fmt,va);
  ClipboardAppend(clipboard,fmt2);
  return;
}
#undef fmt2

/* ClipboardAppend @ 0x0804e5a0, 180 bytes
 *
 * Formats the printf-style text (vsprintf into a 1 KB buffer) and appends it
 * to the current line. A '\n' or a full line starts a new line. Lines wrap
 * around the ring; when the ring is full the oldest line is dropped. Returns
 * the length of the current line.
 *
 * Parameters:
 *   clipboard    int *
 *   fmt          char *
 *
 * C library: vsprintf, strlen
 * Called by: BGMLoad, ClipboardPrint, EvalExpressionF, EvalExpressionI,
 *            GameRoundUpdate, PlayerCacheClear, PlayerCacheLoad,
 *            PlayerCheck, PlayerDefLoadPtr, PlayerDefLoadZip,
 *            PlayerSCtrlApplyElem, VWarn, Warn, WarnR
 *
 * Elecbyte file: src/lib/clipbrd.c
 * Note: varargs: replaced 1 &stack0x.. with a va_list started after fmt
 * Note: Locals live in `frame`, laid out as on the original stack (0x420 bytes,
 *       1 variables), because their address is taken.
 */
size_t ClipboardAppend(int *clipboard,char *fmt,...)

{
  va_list va;
  va_start(va, fmt);
  int i1;
  int i2;
  size_t s3;
  uint32_t u4;
  size_t s5;
  char *s2;
  char *s_00;
  unsigned char frame[0x420] __attribute__((aligned(16)));
#define stk_41c (*(char (*)[1036])(frame + 0x4))
  
  s_00 = *(char **)(*clipboard + clipboard[5] * 4);
  i1 = clipboard[2];
  i2 = clipboard[3];
  s2 = stk_41c;
  vsprintf(s2,fmt,va);
  s3 = strlen(s_00);
  s5 = s3;
  while (stk_41c[0] != '\0') {
    if ((i1 + -1 <= (int)s5) ||
       (s3 = CONCAT31((uint32_t)((uint32_t)(i1 + -1) >> 8),*s2), *s2 == '\n')) {
      s_00[s5] = '\0';
      u4 = (i2 <= (int)(clipboard[5] + 1U)) - 1 & clipboard[5] + 1U;
      clipboard[5] = u4;
      if (u4 == clipboard[4]) {
        clipboard[4] = u4 + 1 & (i2 <= (int)(u4 + 1)) - 1;
      }
      s5 = 0;
      s_00 = *(char **)(*clipboard + u4 * 4);
      s3 = CONCAT31((uint32_t)((uint32_t)*clipboard >> 8),*s2);
    }
    if ((char)s3 != '\n') {
      s_00[s5] = (char)s3;
      s5 = s5 + 1;
    }
    s2 = s2 + 1;
    stk_41c[0] = *s2;
  }
  s_00[s5] = '\0';
  return s3;
}
#undef stk_41c

