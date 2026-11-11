/*
 * charsel.c -- character list and select screen
 * Builds the character list from select.def, runs the character select and
 * versus screens, and manages the arcade opponent order, survival teams and
 * palette reservation.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/charsel.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"

extern int dataSetup __asm__("D_08287a30"); /* file-static 0x08287a30 */
extern int *cellHead __asm__("D_082a6be0"); /* file-static 0x082a6be0 */
extern int slct __asm__("D_082a6be4"); /* file-static 0x082a6be4 */
extern int cellRows __asm__("D_082a6be8"); /* file-static 0x082a6be8 */
extern int cellCols __asm__("D_082a6bec"); /* file-static 0x082a6bec */

/* InitSelectScreenMatrix @ 0x08085c30, 151 bytes
 *
 * Finds and parses the motif's select.def ("Couldn't find file for selection
 * screen: %s").
 *
 * Parameters:
 *   path         char *
 *
 * Globals read: files_select, errmsg
 * Calls: FindFileDir, TPReadFile
 * C library: sprintf
 * Called by: _mangled_main
 * Messages:
 *   "Couldn\'t find file for selection screen: %s\n"
 *
 * Elecbyte file: src/mugen/charsel.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x1010 bytes,
 *       1 variables), because their address is taken.
 */
bool InitSelectScreenMatrix(char *path)

{
  int i1;
  bool b2;
  unsigned char frame[0x1010] __attribute__((aligned(16)));
#define filename (*(char (*)[4100])(frame + 0x4))
  
  slct = (int)(g + G_FILES_SELECT);
  cellHead = (int *)g[0x1b50];
  cellRows = g[0x18e4];
  cellCols = g[0x18e5];
  i1 = FindFileDir(path,filename,(char *)0x0);
  if (i1 == 0) {
    sprintf((char *)(g + G_ERRMSG),"Couldn\'t find file for selection screen: %s\n",path,0);
    b2 = false;
  }
  else {
    dataSetup = (int)TPReadFile(filename);
    b2 = (void *)dataSetup != (void *)0x0;
  }
  return b2;
}
#undef filename

/* FreeSelectScreenMatrix @ 0x08085cd0, 34 bytes
 *
 * Frees the parsed select.def.
 *
 * C library: free
 * Called by: GameDeInit
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void FreeSelectScreenMatrix(void)

{
  if ((void *)g[0x33ac] != (void *)0x0) {
    free((void *)g[0x33ac]);
  }
  return;
}

/* CharInfoInit @ 0x08085d00, 176 bytes
 *
 * Allocates the character list (one entry per selectable character: paths,
 * names, palettes, stage, music, cache state) and initialises the background
 * loader. "Out of memory" on failure.
 *
 * Globals written: charinfo
 * Calls: PrecacheInit
 * C library: calloc, memcpy
 * Called by: _mangled_main
 * Messages:
 *   "Out of memory"
 *
 * Elecbyte file: src/mugen/charsel.c
 */
bool CharInfoInit(void)

{
  void *pv1;
  int i2;
  int *pi3;
  
  pi3 = g;
  g[0x14b7] = 0x20;
  slct = (int)(pi3 + 0x14e0);
  pv1 = calloc(pi3[0x14b7],0x702c);
  pi3 = g;
  g[G_CHARINFO] = (int)pv1;
  if (pv1 != (void *)0x0) {
    pv1 = calloc(pi3[0x14b7] + 0x1e,4);
    pi3 = g;
    g[0x14b8] = (int)pv1;
    if (pv1 != (void *)0x0) {
      i2 = PrecacheInit(pi3[0x757a]);
      return i2 != 0;
    }
  }
  memcpy(pi3 + 0x81d2,"Out of memory",0xe);
  return false;
}

/* CharInfoFree @ 0x08085db0, 61 bytes
 *
 * Frees the character list.
 *
 * Globals read: charinfo
 * C library: free
 * Called by: GameDeInit
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void CharInfoFree(void)

{
  if ((void *)g[G_CHARINFO] != (void *)0x0) {
    free((void *)g[G_CHARINFO]);
  }
  if ((void *)g[0x14b8] != (void *)0x0) {
    free((void *)g[0x14b8]);
  }
  return;
}

/* FindCharacters @ 0x08085df0, 4958 bytes
 *
 * Builds the character list from select.def.
 * - "[Characters]": one line per character, "name, stage, flag=value...",
 * with the flags music, includestage, order and the special entries
 * "randomselect" and empty cells. For each character it locates the .def (or
 * .zip) under chars/ ("chars/%s", "chars/%s/"), reads its "[Info]" (name,
 * displayname, pal.defaults) and "[Files]" (sprite, palettes, intro/ending
 * storyboards), and loads its select portraits.
 * - "[ExtraStages]": stages that are not tied to a character.
 * - "[Options]": arcade.maxmatches, team.maxmatches.
 *
 * Errors: "Could not locate Characters group.", "Unknown flag: %s", "Param
 * %s missing '='", "Error getting stage name for ...".
 *
 * Text keys read: [Options], "arcade.maxmatches", "team.maxmatches",
 *                 [Characters], [Info], "displayname", "name",
 *                 "pal.defaults", [Arcade], "intro.storyboard",
 *                 "ending.storyboard", [Files], "sprite", [extrastages]
 * Globals read: errmsg
 * Globals written: charinfo, num_chars
 * Calls: TPGroupSeek, TPGetValue, TPAccessNextLine, splitdirfile,
 *        CheckExtension, isabsolutedir, joindirfile, MFfopenZip, TPReadMF,
 *        MFzclose, TPReadFile, GetQuotedString, TPScanf, MFzopen,
 *        SpriteReadSFFListPtr, SpriteSetBufReadMode, SpriteReadSFFList,
 *        TPFree, MFfclose, TPGroupReset
 * C library: sprintf, __strtol_internal, realloc, memset, _alemu_stricmp,
 *            strncpy, strcpy, strcat, fopen, fclose, calloc, strcmp,
 *            memcpy
 * Called by: _mangled_main
 * Messages:
 *   "Could not locate Options group."
 *   "Could not locate Characters group."
 *   "\n[Characters]: On line: %s\n-- Unknown flag: %s"
 *   "\n[Characters]: On line: %s\n-- Param %s missing \'=\'"
 *   "\nError reading "
 *   "\nError getting stage name for "
 *
 * Elecbyte file: src/mugen/charsel.c
 * Note: decompiler flag: type propagation did not settle
 * Note: Locals live in `frame`, laid out as on the original stack (0x4670 bytes,
 *       19 variables), because their address is taken.
 */
uint32_t FindCharacters(void)

{
  int *pi1;
  int *pi2;
  char *value;
  uint32_t u4;
  int *tp;
  FILE *stream;
  void *pv6;
  int *pi7;
  int i8;
  uint32_t *tp2;
  int i2;
  char *pc11;
  uint32_t stale_ECX;
  uint32_t *pu12;
  uint32_t *pu13;
  int *stale_ECX_00;
  int *pi14;
  char c15;
  uint32_t stale_EDX;
  uint32_t u16;
  int j;
  uint32_t *filename;
  int k;
  bool b19;
  unsigned char frame[0x4670] __attribute__((aligned(16)));
#define stk_466c (*(uint32_t **)(frame + 0x4))
#define stk_4668 (*(int *)(frame + 0x8))
#define stk_4664 (*(int *)(frame + 0xc))
#define stk_4660 (*(int *)(frame + 0x10))
#define stk_465c (*(int *)(frame + 0x14))
#define mf (*(int **)(frame + 0x30))
#define stk_4638 (*(uint32_t *)(frame + 0x38))
#define stk_4628 (*(int *)(frame + 0x48))
#define stk_4624 (*(int *)(frame + 0x4c))
#define stk_4620 (*(int *)(frame + 0x50))
#define stk_461c (*(int (*)[254])(frame + 0x54))
#define buf_4222 (*(char (*)[6])(frame + 0x44e))
#define filename2 (*(uint32_t (*)[1023])(frame + 0x454))
#define buf_3220 (*(char (*)[4])(frame + 0x1450))
#define dirname (*(uint32_t (*)[1024])(frame + 0x1454))
#define filename3 (*(char (*)[4096])(frame + 0x2454))
#define keyname (*(uint8_t (*)[256])(frame + 0x3454))
#define filename4 (*(char (*)[4096])(frame + 0x3554))
#define path (*(char (*)[268])(frame + 0x4554))
  
  pi7 = g;
  pi2 = g + G_CHARINFO;
  i2 = cellRows * cellCols;
  stk_4628 = 0;
  stk_4620 = 0;
  stk_4624 = 0;
  tp = cellHead;
  if (0 < i2) {
    do {
      *tp = -1;
      i2 = i2 + -1;
      tp = tp + 0x80e;
    } while (i2 != 0);
  }
  i2 = TPGroupSeek(dataSetup,"Options");
  if (i2 == -1) {
    sprintf((char *)(g + G_ERRMSG),"Could not locate Options group.");
  }
  else {
    value = TPGetValue(dataSetup,"arcade.maxmatches");
    if (value != (char *)0x0) {
      j = 0;
      i2 = 0;
      if (*value != '\0') {
        stk_466c = (uint32_t *)(pi7 + 0x14bc);
        do {
          u4 = __strtol_internal((uint8_t *)(value + i2),(uint32_t *)0x0,10,0);
          *stk_466c = u4;
          do {
            k = i2;
            i2 = k + 1;
            c15 = value[i2];
            if (c15 == '\0') break;
          } while (c15 != ',');
          if (c15 != '\0') {
            i2 = k + 2;
          }
          if ((*(uint8_t *)(__ctype_b + 1 + value[i2] * 2) & 0x20) != 0) {
            c15 = value[i2];
            while ((c15 != '\0' &&
                   (i2 = i2 + 1, (*(uint8_t *)(__ctype_b + 1 + value[i2] * 2) & 0x20) != 0
                   ))) {
              c15 = value[i2];
            }
          }
          j = j + 1;
          stk_466c = stk_466c + 1;
        } while ((j < 10) && (value[i2] != '\0'));
      }
    }
    value = TPGetValue(dataSetup,"team.maxmatches");
    if (value != (char *)0x0) {
      j = 0;
      i2 = 0;
      if (*value != '\0') {
        stk_4668 = 0x40;
        do {
          u4 = __strtol_internal((uint8_t *)(value + i2),(uint32_t *)0x0,10,0);
          *(uint32_t *)(stk_4668 + 8 + (int)pi2) = u4;
          do {
            k = i2;
            i2 = k + 1;
            c15 = value[i2];
            if (c15 == '\0') break;
          } while (c15 != ',');
          if (c15 != '\0') {
            i2 = k + 2;
          }
          if ((*(uint8_t *)(__ctype_b + 1 + value[i2] * 2) & 0x20) != 0) {
            c15 = value[i2];
            while ((c15 != '\0' &&
                   (i2 = i2 + 1, (*(uint8_t *)(__ctype_b + 1 + value[i2] * 2) & 0x20) != 0
                   ))) {
              c15 = value[i2];
            }
          }
          j = j + 1;
          stk_4668 = stk_4668 + 4;
        } while ((j < 10) && (value[i2] != '\0'));
      }
    }
    i2 = TPGroupSeek(dataSetup,"Characters");
    if (i2 == -1) {
      sprintf((char *)(g + G_ERRMSG),"Could not locate Characters group.",stale_EDX,stale_EDX);
    }
    else {
      filename = filename2;
      while (value = (char *)TPAccessNextLine(dataSetup), tp = g, value != (char *)0x0) {
        b19 = false;
        if (g[0x14b7] <= g[G_NUM_CHARS]) {
          i2 = g[0x14b7] + 8;
          g[0x14b7] = i2;
          pv6 = realloc((void *)tp[0x14b4],i2 * 0x702c);
          if (pv6 == (void *)0x0) {
            return 0;
          }
          memset((void *)((int)pv6 + g[0x14b7] * 0x702c + -0x38160),0,0x38160);
          tp = g;
          g[G_CHARINFO] = (int)pv6;
          pv6 = realloc((void *)tp[0x14b8],tp[0x14b7] * 4 + 0x78);
          if (pv6 == (void *)0x0) {
            return 0;
          }
          tp2 = (uint32_t *)((int)pv6 + g[0x14b7] * 4 + -0x20);
          for (i2 = 8; tp = g, i2 != 0; i2 = i2 + -1) {
            *tp2 = 0;
            tp2 = tp2 + 1;
          }
          g[0x14b8] = (int)pv6;
        }
        j = 0;
        pi1 = cellHead + (stk_4624 * cellCols + stk_4620) * 0x80e;
        i2 = tp[0x14b4] + tp[0x14b5] * 0x702c;
        c15 = *value;
        while ((c15 != ',' && (c15 != '\0'))) {
          path[j] = c15;
          j = j + 1;
          c15 = value[j];
        }
        path[j] = '\0';
        if (value[j] != '\0') {
          j = j + 1;
        }
        k = (int)value[j];
        if ((*(uint8_t *)(__ctype_b + 1 + k * 2) & 0x20) != 0) {
          c15 = value[j];
          while (c15 != '\0') {
            j = j + 1;
            k = (int)value[j];
            if ((*(uint8_t *)(__ctype_b + 1 + k * 2) & 0x20) == 0) break;
            c15 = value[j];
          }
        }
        i8 = 0;
        if ((((*(uint8_t *)(__ctype_b + 1 + k * 2) & 0x20) == 0) &&
            (c15 = value[j], c15 != ',')) && (c15 != '\0')) {
          pc11 = (char *)(i2 + 0x3009);
          k = __ctype_b;
          do {
            if (i8 < 0xffe) {
              *pc11 = c15;
              pc11 = pc11 + 1;
              i8 = i8 + 1;
              k = __ctype_b;
            }
            j = j + 1;
          } while ((((*(uint8_t *)(k + 1 + value[j] * 2) & 0x20) == 0) &&
                   (c15 = value[j], c15 != ',')) && (c15 != '\0'));
        }
        *(uint8_t *)(i8 + 0x3009 + i2) = 0;
        if ((0 < i8) &&
           (k = _alemu_stricmp((char *)(i2 + 0x3009),"random"), k != 0)) {
          *(uint32_t *)(i2 + 0x5008) = 3;
        }
        if ((*(uint8_t *)(__ctype_b + 1 + value[j] * 2) & 0x20) == 0) goto L_08086515;
        c15 = '\0';
        if (value[j] != '\0') {
          do {
            j = j + 1;
            if ((*(uint8_t *)(__ctype_b + 1 + value[j] * 2) & 0x20) == 0) goto L_08086515;
          } while (value[j] != '\0');
          c15 = '\0';
        }
        while (c15 == ',') {
          j = j + 1;
          k = (int)value[j];
          if ((*(uint8_t *)(__ctype_b + 1 + k * 2) & 0x20) == 0) {
L_080862b0:
            c15 = value[j];
          }
          else {
            c15 = '\0';
            if (value[j] != '\0') {
              do {
                j = j + 1;
                k = (int)value[j];
                if ((*(uint8_t *)(__ctype_b + 1 + k * 2) & 0x20) == 0) goto L_080862b0;
              } while (value[j] != '\0');
              c15 = '\0';
            }
          }
          i8 = 0;
          if ((c15 != '=') && ((*(uint8_t *)(__ctype_b + 1 + k * 2) & 0x20) == 0)) {
            while (c15 != '\0') {
              j = j + 1;
              keyname[i8] = (uint8_t)*(uint32_t *)(__ctype_tolower + k * 4);
              i8 = i8 + 1;
              c15 = value[j];
              if ((c15 == '=') ||
                 (k = (int)c15, (*(uint8_t *)(__ctype_b + 1 + k * 2) & 0x20) != 0)) break;
            }
          }
          keyname[i8] = 0;
          k = _alemu_stricmp((char *)keyname,"includestage");
          stk_4638 = 0;
          if (k != 0) {
            k = _alemu_stricmp((char *)keyname,"music");
            stk_4638 = 1;
            if (k != 0) {
              k = _alemu_stricmp((char *)keyname,"order");
              stk_4638 = 2;
              if (k != 0) {
                sprintf((char *)(g + G_ERRMSG),"\n[Characters]: On line: %s\n-- Unknown flag: %s",
                        value,keyname);
                return 0;
              }
            }
          }
          if ((*(uint8_t *)(__ctype_b + 1 + value[j] * 2) & 0x20) == 0) {
L_080863b5:
            c15 = value[j];
          }
          else {
            c15 = '\0';
            if (value[j] != '\0') {
              do {
                j = j + 1;
                if ((*(uint8_t *)(__ctype_b + 1 + value[j] * 2) & 0x20) == 0) goto L_080863b5;
              } while (value[j] != '\0');
              c15 = '\0';
            }
          }
          if (c15 != '=') {
            sprintf((char *)(g + G_ERRMSG),"\n[Characters]: On line: %s\n-- Param %s missing \'=\'",
                    value,keyname);
            return 0;
          }
          j = j + 1;
          k = (int)value[j];
          if ((*(uint8_t *)(__ctype_b + 1 + k * 2) & 0x20) == 0) {
L_080863f0:
            c15 = value[j];
          }
          else {
            c15 = '\0';
            if (value[j] != '\0') {
              do {
                j = j + 1;
                k = (int)value[j];
                if ((*(uint8_t *)(__ctype_b + 1 + k * 2) & 0x20) == 0) goto L_080863f0;
              } while (value[j] != '\0');
              c15 = '\0';
            }
          }
          i8 = 0;
          if ((c15 != ',') && ((*(uint8_t *)(__ctype_b + 1 + k * 2) & 0x20) == 0)) {
            while (c15 != '\0') {
              j = j + 1;
              keyname[i8] = (uint8_t)*(uint32_t *)(__ctype_tolower + k * 4);
              i8 = i8 + 1;
              c15 = value[j];
              if ((c15 == ',') ||
                 (k = (int)c15, (*(uint8_t *)(__ctype_b + 1 + k * 2) & 0x20) != 0)) break;
            }
          }
          keyname[i8] = 0;
          if (stk_4638 == 1) {
            strncpy((char *)(i2 + 0x4008),(char *)keyname,0xffe);
          }
          else if (stk_4638 < 2) {
            if (stk_4638 == 0) {
              u4 = __strtol_internal(keyname,(uint32_t *)0x0,10,0);
              *(uint32_t *)(i2 + 0x5008) = (uint32_t)(u4 != 0) * 3;
            }
          }
          else if (stk_4638 == 2) {
            u4 = __strtol_internal(keyname,(uint32_t *)0x0,10,0);
            u4 = (-2 < (int)(u4 - 1)) - 1 | u4 - 1;
            *(uint32_t *)(i2 + 0x5024) = u4;
            if (9 < (int)u4) {
              *(uint32_t *)(i2 + 0x5024) = 9;
            }
          }
          if ((*(uint8_t *)(__ctype_b + 1 + value[j] * 2) & 0x20) == 0) {
L_08086515:
            c15 = value[j];
          }
          else {
            c15 = '\0';
            if (value[j] != '\0') {
              do {
                j = j + 1;
                if ((*(uint8_t *)(__ctype_b + 1 + value[j] * 2) & 0x20) == 0) goto L_08086515;
              } while (value[j] != '\0');
              c15 = '\0';
            }
          }
        }
        j = _alemu_stricmp(path,"randomselect");
        if (j == 0) {
          *(uint8_t *)(pi1 + 1) = 0;
          pi1[0x80d] = 0;
          *pi1 = -2;
        }
        else {
          splitdirfile(path,(char *)dirname,(char *)filename2);
          j = CheckExtension(path);
          b19 = j == 9;
          if ((char)dirname[0] == '\0') {
            sprintf((char *)dirname,"chars/%s/",path,stale_ECX);
            strcpy((char *)filename2,path);
          }
          else {
            j = isabsolutedir((char *)dirname);
            if (j == 0) {
              strcpy(filename4,(char *)dirname);
              sprintf((char *)dirname,"chars/%s",filename4,i8);
            }
          }
          if (b19) {
            pu12 = filename2;
            do {
              pu13 = pu12;
              pu12 = pu13 + 1;
              u4 = *pu13 + 0xfefefeff & (*pu13 ^ 0xffffffff);
              u16 = u4 & 0x80808080;
            } while (u16 == 0);
            if ((u4 & 0x8080) == 0) {
              u16 = u16 >> 0x10;
              pu12 = (uint32_t *)((int)pu13 + 6);
            }
            *(char *)((int)filename +
                     (int)pu12 +
                     ((-6 - (uint32_t)CARRY1((uint8_t)u16,(uint8_t)u16)) - (int)filename2)) = 'd';
            pu12 = filename;
            do {
              pu13 = pu12;
              pu12 = pu13 + 1;
              u4 = *pu13 + 0xfefefeff & (*pu13 ^ 0xffffffff);
              u16 = u4 & 0x80808080;
            } while (u16 == 0);
            if ((u4 & 0x8080) == 0) {
              u16 = u16 >> 0x10;
              pu12 = (uint32_t *)((int)pu13 + 6);
            }
            *(char *)((int)pu12 + (-5 - (uint32_t)CARRY1((uint8_t)u16,(uint8_t)u16))) = 'e';
            pu12 = filename;
            do {
              pu13 = pu12;
              pu12 = pu13 + 1;
              u4 = *pu13 + 0xfefefeff & (*pu13 ^ 0xffffffff);
              u16 = u4 & 0x80808080;
            } while (u16 == 0);
            if ((u4 & 0x8080) == 0) {
              u16 = u16 >> 0x10;
              pu12 = (uint32_t *)((int)pu13 + 6);
            }
            *(char *)((int)pu12 + (-4 - (uint32_t)CARRY1((uint8_t)u16,(uint8_t)u16))) = 'f';
          }
          else {
            pu12 = filename2;
            do {
              pu13 = pu12;
              pu12 = pu13 + 1;
              u4 = *pu13 + 0xfefefeff & (*pu13 ^ 0xffffffff);
              u16 = u4 & 0x80808080;
            } while (u16 == 0);
            if ((u4 & 0x8080) == 0) {
              u16 = u16 >> 0x10;
              pu12 = (uint32_t *)((int)pu13 + 6);
            }
            if (4 < (int)pu12 +
                    ((-3 - (uint32_t)CARRY1((uint8_t)u16,(uint8_t)u16)) - (int)filename2)) {
              pu12 = filename2;
              do {
                pu13 = pu12;
                pu12 = pu13 + 1;
                u4 = *pu13 + 0xfefefeff & (*pu13 ^ 0xffffffff);
                u16 = u4 & 0x80808080;
              } while (u16 == 0);
              if ((u4 & 0x8080) == 0) {
                u16 = u16 >> 0x10;
                pu12 = (uint32_t *)((int)pu13 + 6);
              }
              j = _alemu_stricmp((char *)((int)pu12 +
                                              (-7 - (uint32_t)CARRY1((uint8_t)u16,(uint8_t)u16))),".def"
                                     );
              if (j == 0) goto L_0808674a;
            }
            strcat((char *)filename,".def");
          }
L_0808674a:
          joindirfile(filename4,(char *)dirname,(char *)filename);
          pu12 = dirname;
          if (b19) {
            do {
              pu13 = pu12;
              pu12 = pu13 + 1;
              u4 = *pu13 + 0xfefefeff & (*pu13 ^ 0xffffffff);
              u16 = u4 & 0x80808080;
            } while (u16 == 0);
            if ((u4 & 0x8080) == 0) {
              u16 = u16 >> 0x10;
              pu12 = (uint32_t *)((int)pu13 + 6);
            }
            *(char *)((int)pu12 +
                     (int)(buf_3220 +
                          (-(int)dirname - (uint32_t)CARRY1((uint8_t)u16,(uint8_t)u16)))) = '\0';
            mf = MFfopenZip((char *)dirname,(char *)filename);
            pu12 = dirname;
            do {
              pu13 = pu12;
              pu12 = pu13 + 1;
              u4 = *pu13 + 0xfefefeff & (*pu13 ^ 0xffffffff);
              u16 = u4 & 0x80808080;
            } while (u16 == 0);
            if ((u4 & 0x8080) == 0) {
              u16 = u16 >> 0x10;
              pu12 = (uint32_t *)((int)pu13 + 6);
            }
            *(char *)((int)pu12 +
                     (int)(buf_3220 +
                          (-(int)dirname - (uint32_t)CARRY1((uint8_t)u16,(uint8_t)u16)) + 2)) = '/';
            pu12 = dirname;
            do {
              pu13 = pu12;
              pu12 = pu13 + 1;
              u4 = *pu13 + 0xfefefeff & (*pu13 ^ 0xffffffff);
              u16 = u4 & 0x80808080;
            } while (u16 == 0);
            if ((u4 & 0x8080) == 0) {
              u16 = u16 >> 0x10;
              pu12 = (uint32_t *)((int)pu13 + 6);
            }
            *(char *)((int)pu12 +
                     (int)(buf_3220 +
                          (-(int)dirname - (uint32_t)CARRY1((uint8_t)u16,(uint8_t)u16)) + 1)) = '\0';
            if (mf == (int *)0x0) {
              return 0;
            }
            tp = TPReadMF(mf,0);
            MFzclose((int)mf);
          }
          else {
            tp = TPReadFile(filename4);
          }
          if (tp == (int *)0x0) {
            *(uint8_t *)(pi1 + 1) = 0;
            pi1[0x80d] = 0;
            *pi1 = -1;
          }
          else {
            pc11 = "Info";
            TPGroupSeek((int)tp,"Info");
            value = TPGetValue((int)tp,"displayname");
            if (value == (char *)0x0) {
              value = TPGetValue((int)tp,"name");
              if ((value != (char *)0x0) &&
                 (j = GetQuotedString((int)tp,"name",(char *)(pi1 + 1),0x2f,(char *)0x0)
                 , j == 0)) {
                strcat((char *)(g + G_ERRMSG),"\nError reading ");
                filename = filename2;
                pi7 = g + G_ERRMSG;
                goto L_08086d8c;
              }
            }
            else {
              j = GetQuotedString((int)tp,"displayname",(char *)(pi1 + 1),0x2f,
                                       (char *)0x0);
              if (j == 0) {
                strcat((char *)(g + G_ERRMSG),"\nError reading ");
                pi7 = g + G_ERRMSG;
                goto L_08086d8c;
              }
            }
            strcpy((char *)(pi1 + 0xd),(char *)filename);
            strcpy((char *)((int)pi1 + 0x1033),(char *)dirname);
            TPGroupSeek((int)tp,"Info");
            TPScanf((int)tp,"pal.defaults","%i,%i,%i,%i",i2 + 0x5014,i2 + 0x5018,
                    i2 + 0x501c,i2 + 0x5020,pc11);
            j = TPGroupSeek((int)tp,"Arcade");
            if (j != -1) {
              TPScanf((int)tp,"intro.storyboard","%s",i2 + 0x5028);
              TPScanf((int)tp,"ending.storyboard","%s",i2 + 0x6027);
            }
            TPGroupSeek((int)tp,"Files");
            value = TPGetValue((int)tp,"sprite");
            strcpy(filename4,value);
            joindirfile(filename3,(char *)dirname,filename4);
            *pi1 = g[G_NUM_CHARS];
            pi14 = pi1;
            j = 0;
            do {
              k = j + 1;
              sprintf((char *)keyname,"pal%i",k,pi14);
              value = TPGetValue((int)tp,(char *)keyname);
              pi14 = stale_ECX_00;
              if (value != (char *)0x0) {
                pi14 = (int *)(*(uint32_t *)(i2 + 0x5010) | 1 << ((uint8_t)j & 0x1f));
                *(int **)(i2 + 0x5010) = pi14;
              }
              j = k;
            } while (k < 0xc);
            *(uint32_t *)(i2 + 0x7028) = *(uint32_t *)(i2 + 0x5010);
            strcpy((char *)(i2 + 0x100b),(char *)(pi1 + 0xd));
            strcpy((char *)(i2 + 0x200a),(char *)((int)pi1 + 0x1033));
            *(int *)(i2 + 0x500c) = stk_4624 * cellCols + stk_4620;
            g[G_NUM_CHARS] = g[G_NUM_CHARS] + 1;
            stk_461c[0] = 9000;
            pi1[0x80d] = 0;
            stk_461c[1] = 0;
            stk_461c[2] = 9000;
            stk_461c[3] = 1;
            stk_461c[4] = 0xffffffff;
            if (b19) {
              MFzopen(mf,filename4);
              pi14 = SpriteReadSFFListPtr(mf,stk_461c);
              pi1[0x80d] = (int)pi14;
            }
            else {
              stream = fopen(filename3,"rb");
              if (stream != (FILE *)0x0) {
                fclose(stream);
                SpriteSetBufReadMode(0);
                i2 = SpriteReadSFFList(filename3,stk_461c);
                pi1[0x80d] = i2;
                SpriteSetBufReadMode(g[0x757b]);
              }
            }
            TPFree(tp);
          }
        }
        stk_4620 = stk_4620 + 1;
        path[0] = '\0';
        if (cellCols <= stk_4620) {
          stk_4624 = stk_4624 + 1;
          stk_4620 = 0;
        }
        if (cellRows <= stk_4624) break;
        if (b19) {
          MFfclose(mf);
        }
      }
      i2 = TPGroupSeek(dataSetup,"extrastages");
      if (i2 != -1) {
        while (value = (char *)TPAccessNextLine(dataSetup), value != (char *)0x0) {
          if (*value != '\0') {
            stk_4628 = stk_4628 + 1;
          }
        }
      }
      pv6 = calloc(stk_4628 + pi7[0x14b5],0x1054);
      tp = g;
      g[0x33ac] = (int)pv6;
      if (pv6 != (void *)0x0) {
        i2 = 0;
        stk_465c = pi7[0x14b5];
        if (0 < stk_465c) {
          stk_4664 = 0;
          do {
            tp = g;
            if (*(int *)(g[G_CHARINFO] + 0x5008 + stk_4664) != 0) {
              j = g[0x33ad];
              k = 0;
              value = (char *)(stk_4664 + *pi2 + 0x3009);
              if (0 < j) {
                stk_4660 = 0;
                do {
                  i8 = strcmp((char *)(stk_4660 + tp[0x33ac]),value);
                  if (i8 == 0) break;
                  k = k + 1;
                  stk_4660 = stk_4660 + 0x1054;
                } while (k < j);
              }
              if (j <= k) {
                k = j * 0x1054;
                strcpy((char *)(k + tp[0x33ac]),value);
                i8 = g[0x33ac];
                *(uint32_t *)(i8 + 0x1050 + k) =
                     *(uint32_t *)(g[G_CHARINFO] + 0x5008 + stk_4664);
                tp2 = TPReadFile((char *)(i8 + k));
                if (tp2 == (uint32_t *)0x0) {
                  *(uint8_t *)(*pi2 + 0x3009 + stk_4664) = 0;
                  stk_465c = pi7[0x14b5];
                }
                else {
                  i8 = TPGroupSeek((int)tp2,"Info");
                  if (((i8 != -1) &&
                      (value = TPGetValue((int)tp2,"name"), value != (char *)0x0)) &&
                     (i8 = GetQuotedString((int)tp2,"name",
                                              (char *)(k + g[0x33ac] + 0xfff),0x4f,(char *)0x0)
                     , i8 == 0)) {
                    strcat((char *)(g + G_ERRMSG),"\nError getting stage name for ");
                    pi7 = g + G_ERRMSG;
                    filename = (uint32_t *)(k + g[0x33ac]);
                    goto L_08086d8c;
                  }
                  TPFree(tp2);
                  if (*(char *)(g[0x33ac] + 0xfff + j * 0x1054) == '\0') {
                    value = (char *)(j * 0x1054 + g[0x33ac]);
                    strcpy(value + 0xfff,value);
                  }
                  g[0x33ad] = g[0x33ad] + 1;
                  stk_465c = pi7[0x14b5];
                }
              }
            }
            i2 = i2 + 1;
            stk_4664 = stk_4664 + 0x702c;
          } while (i2 < stk_465c);
        }
        if (0 < stk_4628) {
          TPGroupReset(dataSetup);
          while (value = (char *)TPAccessNextLine(dataSetup), pi7 = g, value != (char *)0x0) {
            j = 0;
            i2 = g[0x33ad];
            if (0 < i2) {
              k = 0;
              do {
                i8 = strcmp((char *)(k + pi7[0x33ac]),value);
                if (i8 == 0) break;
                j = j + 1;
                k = k + 0x1054;
              } while (j < i2);
            }
            if (i2 <= j) {
              j = i2 * 0x1054;
              strcpy((char *)(j + pi7[0x33ac]),value);
              tp2 = TPReadFile((char *)(j + g[0x33ac]));
              if (tp2 != (uint32_t *)0x0) {
                k = TPGroupSeek((int)tp2,"Info");
                if (((k != -1) &&
                    (value = TPGetValue((int)tp2,"name"), value != (char *)0x0)) &&
                   (k = GetQuotedString((int)tp2,"name",(char *)(j + g[0x33ac] + 0xfff)
                                             ,0x4f,(char *)0x0), k == 0)) {
                  strcat((char *)(g + G_ERRMSG),"\nError getting stage name for ");
                  pi7 = g + G_ERRMSG;
                  filename = (uint32_t *)(j + g[0x33ac]);
L_08086d8c:
                  strcat((char *)pi7,(char *)filename);
                  return 0;
                }
                TPFree(tp2);
                if (*(char *)(g[0x33ac] + 0xfff + i2 * 0x1054) == '\0') {
                  value = (char *)(i2 * 0x1054 + g[0x33ac]);
                  strcpy(value + 0xfff,value);
                }
                g[0x33ad] = g[0x33ad] + 1;
              }
            }
          }
        }
        TPFree((uint32_t *)dataSetup);
        return 1;
      }
      memcpy(tp + 0x81d2,"Out of memory",0xe);
    }
  }
  return 0;
}
#undef stk_466c
#undef stk_4668
#undef stk_4664
#undef stk_4660
#undef stk_465c
#undef mf
#undef stk_4638
#undef stk_4628
#undef stk_4624
#undef stk_4620
#undef stk_461c
#undef buf_4222
#undef filename2
#undef buf_3220
#undef dirname
#undef filename3
#undef keyname
#undef filename4
#undef path

/* CharacterSelectScreen @ 0x08087150, 5329 bytes
 *
 * Runs the character select screen for the given mode and sides. Each side
 * moves its cursor over the grid, picks characters, team mode and size (team
 * menu), palettes (the button pressed), and the stage in versus modes. The
 * screen handles random select, AI-controlled sides, cancel back to the
 * title, and demo or stress-test automation. On confirmation it records the
 * selections and starts precaching. Returns 0 if cancelled.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         int
 *
 * Globals read: stresstest, demo_mode, backbuffer, sys_sounds, num_chars
 * Calls: TimerSetSyncFPS, KBBufferClear, PadPoll, PadBufClear,
 *        UInpRefreshFlags, UInpBufClear, BGArrayReset, V_SetBuf, W_Cls,
 *        BuildSelectList, InitSelectDisp, CharStopUsingPalAll,
 *        BGMLoadAndStart, ErrorExit, FrameSkipReset, PalGrpClear,
 *        GameSndPlay, PrecacheFinish, MasterPalReset, BGMPoll, KBPoll,
 *        KBkbhit, KBgetchraw, PadHit, ...
 * C library: random, strcpy
 * Called by: MainLoop
 * Messages:
 *   "Programmer\'s fault"
 *   "Not yet implemented"
 *
 * Elecbyte file: src/mugen/charsel.c
 * Note: 4 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x3cd0 bytes,
 *       20 variables), because their address is taken.
 */
uint32_t CharacterSelectScreen(uint32_t arg1,int arg2)

{
  int *pi1;
  uint32_t u2;
  uint32_t u3;
  bool b4;
  bool b5;
  bool b6;
  bool b7;
  uint32_t stale_var;
  uint32_t stale_var_00;
  uint32_t stale_var_01;
  uint32_t u8;
  uint32_t stale_var_02;
  uint32_t u9;
  long l10;
  int i2;
  uint32_t u12;
  int *pi13;
  uint32_t u14;
  uint32_t *pu15;
  int *pi16;
  int *pi17;
  uint32_t *pu18;
  int i19;
  int group;
  int *sounds;
  char *fmt;
  int i23;
  unsigned char frame[0x3cd0] __attribute__((aligned(16)));
#define stk_3cc8 (*(int *)(frame + 0x8))
#define stk_3ca8 (*(int *)(frame + 0x28))
#define stk_3ca4 (*(int *)(frame + 0x2c))
#define stk_3ca0 (*(int *)(frame + 0x30))
#define stk_3c84 (*(uint32_t *)(frame + 0x4c))
#define stk_3c80 (*(int *)(frame + 0x50))
#define stk_3c64 (*(uint32_t **)(frame + 0x6c))
#define stk_3c5c (*(int (*)[7])(frame + 0x74))
#define stk_3c40 (*(int *)(frame + 0x90))
#define stk_3c3c (*(uint32_t *)(frame + 0x94))
#define stk_3c38 (*(uint32_t *)(frame + 0x98))
#define stk_3c34 (*(int (*)[11])(frame + 0x9c))
#define buf_3c08 (*(int (*)[91])(frame + 0xc8))
#define buf_3a9c (*(int (*)[110])(frame + 0x234))
#define stk_38e4 (*(uint32_t (*)[3406])(frame + 0x3ec))
#define buf_3ac (*(uint32_t (*)[62])(frame + 0x3924))
#define buf_2b4 (*(uint32_t (*)[74])(frame + 0x3a1c))
#define stk_18c (*(uint32_t *)(frame + 0x3b44))
#define buf_188 (*(int (*)[90])(frame + 0x3b48))
#define stk_20 (*(int *)(frame + 0x3cb0))
  
  pi16 = stk_3c34 + 2;
  stk_3c3c = 0;
  b5 = false;
  stk_3c5c[2] = 0;
  stk_3c5c[3] = 0;
  b4 = false;
  if ((g[G_STRESSTEST] != 0) || (g[G_DEMO_MODE] != 0)) {
    b4 = true;
  }
  stk_3ca4 = -1;
  i2 = 0;
  stk_3ca0 = 0;
  stk_3ca8 = -1;
  do {
    stk_3c34[i2] = (int)(g + i2 * 0xd + 0x733b);
    i2 = i2 + 1;
  } while (i2 < 2);
  TimerSetSyncFPS(0x3c);
  KBRepeat = 0;
  KBBufferClear();
  PadPoll();
  PadBufClear();
  UInpRefreshFlags();
  UInpBufClear();
  BGArrayReset(g[0x62cf]);
  V_SetBuf((int *)g[G_BACKBUFFER],0);
  W_Cls(0);
  *(uint8_t *)(g + 0x805) = 0;
  pu15 = stk_38e4;
  for (i2 = 0xd4e; i2 != 0; i2 = i2 + -1) {
    *pu15 = 0;
    pu15 = pu15 + 1;
  }
  pi13 = pi16;
  for (i2 = 0xf04; i2 != 0; i2 = i2 + -1) {
    *pi13 = 0;
    pi13 = pi13 + 1;
  }
  buf_3ac[2] = -1;
  BuildSelectList((int)pi16,arg1,arg2);
  InitSelectDisp((int)buf_2b4);
  CharStopUsingPalAll();
  i2 = BGMLoadAndStart(g + 0x6efa,(uint8_t *)(g + 0x6ad3),g[0x6ed3],0);
  if (i2 == 0) {
    ErrorExit();
  }
  FrameSkipReset();
  if (stk_3c3c == 1) {
L_0808844d:
    PalGrpClear();
    if (stk_3c3c == 1) {
      if (g[G_DEMO_MODE] == 0) {
        GameSndPlay((int *)g[G_SYS_SOUNDS],*(int *)(slct + 0x10d8),*(int *)(slct + 0x10dc),0);
      }
      PrecacheFinish();
      MasterPalReset();
      u9 = 0;
    }
    else {
      pu15 = stk_38e4;
      pu18 = (uint32_t *)(g + 0x33b8);
      for (i2 = 0xd4e; i2 != 0; i2 = i2 + -1) {
        *pu18 = *pu15;
        pu15 = pu15 + 1;
        pu18 = pu18 + 1;
      }
      stk_3c80 = 0;
      stk_3cc8 = 0;
      pi16 = g + 0x33b8;
      do {
        i2 = 0;
        *(uint32_t *)((int)stk_3c5c + stk_3cc8) = 0;
        if (0 < pi16[1]) {
          pi13 = pi16 + 5;
          do {
            if (*(int *)((int)stk_3c5c + stk_3cc8) < *pi13) {
              *(int *)((int)stk_3c5c + stk_3cc8) = *pi13;
            }
            i2 = i2 + 1;
            pi13 = pi13 + 0x17;
          } while (i2 < pi16[1]);
        }
        stk_3c80 = stk_3c80 + 1;
        stk_3cc8 = stk_3cc8 + 4;
        pi16 = pi16 + 0x6a7;
      } while (stk_3c80 < 2);
      if (g[0x7579] < stk_3c5c[1] + stk_3c5c[0]) {
        g[0x7579] = stk_3c5c[1] + stk_3c5c[0];
      }
      if (buf_3ac[3] != 0) {
        if (buf_3ac[2] == -1) {
          if (g[0x33ad] < 1) {
            pi16 = g + 0x7dc4;
          }
          else {
            l10 = random();
            pi16 = (int *)(g[0x33ac] + (l10 % g[0x33ad]) * 0x1054);
          }
          strcpy((char *)(g + 0x805),(char *)pi16);
        }
        else {
          strcpy((char *)(g + 0x805),(char *)(g[0x33ac] + buf_3ac[2] * 0x1054));
        }
      }
      MasterPalReset();
      u9 = 1;
    }
    return u9;
  }
L_08087348:
  i2 = 0;
  BGMPoll(g + 0x6efa);
  stk_3c3c = 0;
  stk_3c38 = 0;
  PadPoll();
  KBPoll();
  b6 = KBkbhit();
  if (ZEXT8(b6) != 0) {
    stk_3c3c = KBgetchraw();
  }
  b6 = PadHit();
  if (ZEXT8(b6) != 0) {
    stk_3c38 = PadGet();
  }
  GlobalInputUpdate();
  b6 = UInpHit();
  if (ZEXT8(b6) != 0) {
    i2 = UInpGet();
  }
  KBIMenuGetKey((uint32_t *)(stk_3c5c + 6),i2,(int)stk_3c34,2);
  stk_3c5c[4] = stk_3c5c[6];
  stk_3c5c[5] = stk_3c40;
  if ((g[G_DEMO_MODE] != 0) &&
     ((((stk_3c3c != 0 && ((stk_3c3c & 0x100) == 0)) ||
       ((stk_3c38 != 0 && ((stk_3c38 & 0x100) == 0)))) || (stk_3c5c[6] != 0)))) {
    stk_3c3c = 1;
    stk_3c38 = 0;
    stk_3c5c[4] = 0;
  }
  stk_3c80 = 0;
L_08087466:
  pi13 = pi16 + stk_3c80 * 0x68;
  do {
    b6 = false;
    stk_3c84 = -1;
    if (buf_3a9c[stk_3c80 * 0x68] <= buf_3a9c[stk_3c80 * 0x68 + 1]) {
      stk_3c5c[stk_3c80 + 2] = 1;
      goto L_default_080874eb;
    }
    pi1 = pi13 + buf_3a9c[stk_3c80 * 0x68 + 1] * 10;
    i2 = SlctStateListChanged((int)pi13);
    b7 = false;
    switch(*pi1) {
    case 0:
    case 5:
    case 6:
      goto L_080881c0;
    case 1:
      pi17 = buf_188 + stk_3c80 * 0x2d;
      if (i2 != 0) {
        BuildMenuCtrl((int)pi16,(int)pi1,stk_3c80);
      }
      if (g[0x4134] == 0) {
        if (stk_3c5c[5] == stk_3c80) {
          i2 = buf_188[stk_3c80 * 0x2d + 3];
          group = buf_188[stk_3c80 * 0x2d + i2 * 5 + 7];
          stk_3c84 = CharacterSelectMenuKey
                                 (stk_3c5c[4],stk_3c5c[5],(int)pi17,
                                  (uint32_t)(buf_188[stk_3c80 * 0x2d + 2] == 0) * 2 + -1);
          if (i2 == buf_188[stk_3c80 * 0x2d + 3]) {
            if (group == buf_188[stk_3c80 * 0x2d + i2 * 5 + 7]) goto L_08087632;
            i2 = *(int *)(buf_188[stk_3c80 * 0x2d + 2] * 0x2e4 + 0x1550 + slct);
            group = *(int *)(buf_188[stk_3c80 * 0x2d + 2] * 0x2e4 + 0x154c + slct);
            sounds = (int *)g[G_SYS_SOUNDS];
          }
          else {
            i2 = *(int *)(buf_188[stk_3c80 * 0x2d + 2] * 0x2e4 + 0x1548 + slct);
            group = *(int *)(buf_188[stk_3c80 * 0x2d + 2] * 0x2e4 + 0x1544 + slct);
            sounds = (int *)g[G_SYS_SOUNDS];
          }
          GameSndPlay(sounds,group,i2,0);
        }
      }
      else {
        stk_3c84 = buf_188[stk_3c80 * 0x2d + 3];
      }
L_08087632:
      if (b4) {
        i2 = buf_3a9c[stk_3c80 * 0x68 + 3];
        if ((i2 < 0x3c) && ((i2 + stk_3c80 * 4 & 7U) == 0)) {
          l10 = random();
          i2 = (l10 % (buf_188[stk_3c80 * 0x2d + 4] + -1) +
                    buf_188[stk_3c80 * 0x2d + 3] + 1) % buf_188[stk_3c80 * 0x2d + 4];
          buf_188[stk_3c80 * 0x2d + 3] = i2;
          pi17[i2 * 5 + 7] = pi17[i2 * 5 + 9];
          if (pi17[i2 * 5 + 8] < pi17[i2 * 5 + 9]) {
            l10 = random();
            pi17[i2 * 5 + 7] =
                 l10 % ((pi17[i2 * 5 + 9] - pi17[i2 * 5 + 8]) + 1) +
                 pi17[i2 * 5 + 8];
          }
          GameSndPlay((int *)g[G_SYS_SOUNDS],
                      *(int *)(buf_188[stk_3c80 * 0x2d + 2] * 0x2e4 + 0x1544 + slct),
                      *(int *)(buf_188[stk_3c80 * 0x2d + 2] * 0x2e4 + 0x1548 + slct),0);
          i2 = buf_3a9c[stk_3c80 * 0x68 + 3];
        }
        if (299 < i2) {
          stk_3c84 = buf_188[stk_3c80 * 0x2d + 3];
        }
      }
      if (stk_3c84 != -1) {
        if (buf_188[stk_3c80 * 0x2d + 1] == 0) {
          if (g[0x4134] == 0) {
            GameSndPlay((int *)g[G_SYS_SOUNDS],
                        *(int *)(buf_188[stk_3c80 * 0x2d + 2] * 0x2e4 + 0x1554 + slct),
                        *(int *)(buf_188[stk_3c80 * 0x2d + 2] * 0x2e4 + 0x1558 + slct),0);
          }
          i2 = buf_188[stk_3c80 * 0x2d + buf_188[stk_3c80 * 0x2d + 3] * 5 + 5];
          if (i2 == 1) {
            i2 = pi1[9];
            *(uint32_t *)(i2 + 8) = 1;
            *(uint32_t *)(i2 + 0x10) = 0;
            *(uint32_t *)(i2 + 0xc) = 2;
          }
          else if (i2 < 2) {
            if (i2 == 0) {
              i2 = pi1[9];
              *(uint32_t *)(i2 + 8) = 0;
              *(uint32_t *)(i2 + 0xc) = 1;
            }
            else {
L_08087800:
              fmt = "Programmer\'s fault";
L_08087808:
              ErrorExitM(fmt);
            }
          }
          else {
            if (i2 == 2) {
              fmt = "Not yet implemented";
              goto L_08087808;
            }
            if (i2 != 3) goto L_08087800;
            i2 = pi1[9];
            *(uint32_t *)(i2 + 8) = 3;
            *(int *)(i2 + 0xc) =
                 buf_188[stk_3c80 * 0x2d + buf_188[stk_3c80 * 0x2d + 3] * 5 + 7];
          }
          CharselSaveMenuPos((int)pi16,
                             (uint32_t *)
                             (slct + 0x16d4 + buf_188[stk_3c80 * 0x2d + 2] * 0x2e4),stk_3c80
                            );
        }
        if (stk_3c84 != -1) {
          *pi17 = 0;
          goto L_080881c0;
        }
      }
      break;
    case 2:
      if (i2 != 0) {
        BuildSlctCtrl((int)pi16,(int)pi1,stk_3c80);
      }
      if (pi1[2] == 1) {
        if (pi1[3] == 2) {
          u12 = buf_3ac[stk_3c80 * 0x1d + 9];
          if ((u12 == 1) && (pi1[4] == 1)) {
            b7 = true;
          }
        }
        else {
          u12 = buf_3ac[stk_3c80 * 0x1d + 9];
        }
      }
      else {
        u12 = buf_3ac[stk_3c80 * 0x1d + 9];
      }
      if (u12 != 0xffffffff) {
        u12 = buf_3ac[stk_3c80 * 0x1d + 5];
        u2 = buf_3ac[stk_3c80 * 0x1d + 4];
        u3 = buf_3ac[stk_3c80 * 0x1d + 6];
        u14 = stk_3c80;
        if (b7) {
          u14 = stk_3c80 - 1;
        }
        stk_3c84 = CharacterSelectScreenKey
                               (stk_3c5c[4],stk_3c5c[5],
                                (int *)(buf_3ac + stk_3c80 * 0x1d + 5),
                                (int *)(buf_3ac + stk_3c80 * 0x1d + 6),u14);
        if (stk_3c84 == 0xffffffff) {
          u14 = buf_3ac[stk_3c80 * 0x1d + 0xb];
          if (u14 == 0) {
            l10 = random();
            stk_3c84 = l10 % 0xc;
            l10 = random();
            buf_3ac[stk_3c80 * 0x1d + 0xb] = l10 % 10 + 10;
          }
          else if ((0 < (int)u14) && (stk_20 % *(int *)(slct + 0x11cc) == 0)) {
            buf_3ac[stk_3c80 * 0x1d + 0xb] = u14 - 1;
          }
        }
        u14 = buf_3ac[stk_3c80 * 0x1d + 5];
        if ((u12 != u14) || (u3 != buf_3ac[stk_3c80 * 0x1d + 6])) {
          GameSndPlay((int *)g[G_SYS_SOUNDS],*(int *)(stk_3c80 * 4 + 0x1094 + slct),
                      *(int *)(stk_3c80 * 4 + 0x109c + slct),0);
          u14 = buf_3ac[stk_3c80 * 0x1d + 5];
        }
        if ((u14 == 0xffffffff) || (buf_3ac[stk_3c80 * 0x1d + 6] == 0xffffffff)) {
          pi17 = (int *)0x0;
        }
        else {
          pi17 = cellHead + (buf_3ac[stk_3c80 * 0x1d + 6] * cellCols + u14) * 0x80e;
        }
        if ((pi17 != (int *)0x0) && (0 < g[G_NUM_CHARS])) {
          if ((b4) || (*pi17 == -2)) {
            i2 = cellHead[(cellCols * buf_3ac[stk_3c80 * 0x1d + 8] +
                              buf_3ac[stk_3c80 * 0x1d + 7]) * 0x80e];
            if (i2 < 0) {
              l10 = random();
              i2 = l10 % g[G_NUM_CHARS];
              GetPlayerRowCol(i2,(int *)(buf_3ac + stk_3c80 * 0x1d + 7),
                              (int *)(buf_3ac + stk_3c80 * 0x1d + 8));
            }
            if (stk_20 % *(int *)(slct + 0x11cc) == (*(int *)(slct + 0x11cc) / 2) * stk_3c80) {
              if (g[G_NUM_CHARS] != 1) {
                l10 = random();
                i2 = (l10 % (g[G_NUM_CHARS] + -1) + 1 + i2) % g[G_NUM_CHARS];
              }
              GetPlayerRowCol(i2,(int *)(buf_3ac + stk_3c80 * 0x1d + 7),
                              (int *)(buf_3ac + stk_3c80 * 0x1d + 8));
              if (*(int *)(slct + 0x10c4) == 0) {
                GameSndPlay((int *)g[G_SYS_SOUNDS],*(int *)(stk_3c80 * 4 + 0x10b4 + slct),
                            *(int *)(stk_3c80 * 4 + 0x10bc + slct),0);
              }
              else {
                GameSndPlayID(stk_3c80,(int *)g[G_SYS_SOUNDS],*(int *)(stk_3c80 * 4 + 0x10b4 + slct),
                              *(int *)(stk_3c80 * 4 + 0x10bc + slct),0);
              }
            }
            cellHead[(cellCols * buf_3ac[stk_3c80 * 0x1d + 8] +
                     buf_3ac[stk_3c80 * 0x1d + 7]) * 0x80e] = i2;
            if (b4) {
              u14 = buf_3ac[stk_3c80 * 0x1d + 7];
              buf_3ac[stk_3c80 * 0x1d + 5] = u14;
              buf_3ac[stk_3c80 * 0x1d + 6] = buf_3ac[stk_3c80 * 0x1d + 8];
            }
            else {
              u14 = buf_3ac[stk_3c80 * 0x1d + 5];
            }
          }
          else {
            buf_3ac[stk_3c80 * 0x1d + 7] = u14;
            buf_3ac[stk_3c80 * 0x1d + 8] = buf_3ac[stk_3c80 * 0x1d + 6];
            u14 = buf_3ac[stk_3c80 * 0x1d + 5];
          }
        }
        if (((pi17 == (int *)0x0) || (buf_3ac[stk_3c80 * 0x1d + 7] == 0xffffffff)) ||
           (buf_3ac[stk_3c80 * 0x1d + 8] == 0xffffffff)) {
          stk_3c64 = (uint32_t *)0x0;
        }
        else {
          stk_3c64 = (uint32_t *)(cellHead +
                               (buf_3ac[stk_3c80 * 0x1d + 7] +
                               buf_3ac[stk_3c80 * 0x1d + 8] * cellCols) * 0x80e);
        }
        i2 = u2 * 4;
        buf_2b4[(i2 + buf_3ac[stk_3c80 * 0x1d + 9]) * 8 + 2] = u14;
        buf_2b4[(i2 + buf_3ac[stk_3c80 * 0x1d + 9]) * 8 + 3] =
             buf_3ac[stk_3c80 * 0x1d + 6];
        buf_2b4[(i2 + buf_3ac[stk_3c80 * 0x1d + 9]) * 8 + 5] =
             buf_3ac[stk_3c80 * 0x1d + 7];
        buf_2b4[(i2 + buf_3ac[stk_3c80 * 0x1d + 9]) * 8 + 6] =
             buf_3ac[stk_3c80 * 0x1d + 8];
        buf_2b4[(i2 + buf_3ac[stk_3c80 * 0x1d + 9]) * 8 + 8] = 1;
        if (b7) {
          buf_2b4[(i2 + buf_3ac[stk_3c80 * 0x1d + 9]) * 8 + 9] = 1 - stk_3c80;
        }
        else {
          buf_2b4[(i2 + buf_3ac[stk_3c80 * 0x1d + 9]) * 8 + 9] = stk_3c80;
        }
        if (((stk_3c84 != 0xffffffff) && (stk_3c64 != (uint32_t *)0x0)) &&
           (*stk_3c64 != 0xffffffff)) {
          GameSndPlay((int *)g[G_SYS_SOUNDS],*(int *)(stk_3c80 * 4 + 0x10a4 + slct),
                      *(int *)(stk_3c80 * 4 + 0x10ac + slct),0);
          u12 = buf_3ac[stk_3c80 * 0x1d + 0xc];
          buf_2b4[(buf_3ac[stk_3c80 * 0x1d + 9] + u2 * 4) * 8 + 8] = 2;
          u2 = buf_3ac[stk_3c80 * 0x1d + buf_3ac[stk_3c80 * 0x1d + 9] * 5 + 0xd];
          u3 = stk_38e4[u2 * 0x6a7 + 1];
          pu15 = stk_38e4 + u2 * 0x6a7 + u3 * 0x17 + 3;
          stk_38e4[u2 * 0x6a7 + u3 * 0x17 + 3] = *(uint32_t *)(u12 + 8);
          u14 = stk_38e4[u2 * 0x6a7 + u3 * 0x17 + 5];
          stk_38e4[u2 * 0x6a7 + u3 * 0x17 + 4] = *(uint32_t *)(u12 + 0x10);
          stk_38e4[u2 * 0x6a7 + u3 * 0x17 + u14 * 5 + 7] = *stk_3c64;
          stk_38e4
          [u2 * 0x6a7 + u3 * 0x17 + stk_38e4[u2 * 0x6a7 + u3 * 0x17 + 5] * 5 + 8] =
               stk_3c84;
          u12 = stk_38e4[u2 * 0x6a7 + u3 * 0x17 + 5];
          stk_38e4[u2 * 0x6a7 + u3 * 0x17 + u12 * 5 + 6] = u2 + 1 + u12 * 2;
          stk_38e4
          [u2 * 0x6a7 + u3 * 0x17 + stk_38e4[u2 * 0x6a7 + u3 * 0x17 + 5] * 5 + 10] =
               buf_3ac[stk_3c80 * 0x1d + buf_3ac[stk_3c80 * 0x1d + 9] * 5 + 0xe];
          stk_38e4
          [u2 * 0x6a7 + u3 * 0x17 + stk_38e4[u2 * 0x6a7 + u3 * 0x17 + 5] * 5 + 9] =
               buf_3ac[stk_3c80 * 0x1d + buf_3ac[stk_3c80 * 0x1d + 9] * 5 + 0xf];
          u12 = CharReservePal(stk_38e4
                                  [u2 * 0x6a7 +
                                   u3 * 0x17 +
                                   stk_38e4[u2 * 0x6a7 + u3 * 0x17 + 5] * 5 + 8],
                                  stk_38e4
                                  [u2 * 0x6a7 +
                                   u3 * 0x17 +
                                   stk_38e4[u2 * 0x6a7 + u3 * 0x17 + 5] * 5 + 7]);
          stk_38e4
          [u2 * 0x6a7 + u3 * 0x17 + stk_38e4[u2 * 0x6a7 + u3 * 0x17 + 5] * 5 + 8] =
               u12;
          if (g[0x33b3] == 0) {
            i2 = pi1[1];
            u12 = buf_3ac[stk_3c80 * 0x1d + 9];
            u14 = buf_3ac[stk_3c80 * 0x1d + 6];
            u8 = buf_3ac[stk_3c80 * 0x1d + 5];
          }
          else {
            i2 = pi1[1];
            u12 = buf_3ac[stk_3c80 * 0x1d + 9];
            u14 = buf_3ac[stk_3c80 * 0x1d + 8];
            u8 = buf_3ac[stk_3c80 * 0x1d + 7];
          }
          CharselSaveCursor(pi16,u8,u14,u12,i2);
          FlashBox((int)buf_2b4,buf_3ac[stk_3c80 * 0x1d + 7],
                   buf_3ac[stk_3c80 * 0x1d + 8]);
          if ((g[0x14d0] != 0) && (stk_38e4[u2 * 0x6a7 + 1] == 0)) {
            PrecacheRequestChar(stk_38e4
                                [u2 * 0x6a7 +
                                 u3 * 0x17 + stk_38e4[u2 * 0x6a7 + u3 * 0x17 + 5] * 5 + 7
                                ]);
            PrecacheStart();
          }
          stk_38e4[u2 * 0x6a7 + u3 * 0x17 + 5] =
               stk_38e4[u2 * 0x6a7 + u3 * 0x17 + 5] + 1;
          u12 = buf_3ac[stk_3c80 * 0x1d + 9];
          buf_3ac[stk_3c80 * 0x1d + 9] = u12 + 1;
          u12 = buf_3ac[stk_3c80 * 0x1d + (u12 + 1) * 5 + 0x10];
          if (u12 != 0xffffffff) {
            buf_3ac[stk_3c80 * 0x1d + 7] = u12;
            buf_3ac[stk_3c80 * 0x1d + 5] = u12;
          }
          u12 = buf_3ac[stk_3c80 * 0x1d + buf_3ac[stk_3c80 * 0x1d + 9] * 5 + 0x11];
          if (u12 != 0xffffffff) {
            buf_3ac[stk_3c80 * 0x1d + 8] = u12;
            buf_3ac[stk_3c80 * 0x1d + 6] = u12;
          }
          stk_38e4[u2 * 0x6a7 + 2] = stk_38e4[u2 * 0x6a7 + 2] + 1;
          u12 = *pu15;
          if ((u12 == 3) &&
             ((int)buf_3ac[stk_3c80 * 0x1d + 9] < (int)buf_3ac[stk_3c80 * 0x1d + 10])) {
            stk_38e4[u2 * 0x6a7 + 1] = stk_38e4[u2 * 0x6a7 + 1] + 1;
            u12 = *pu15;
          }
          if (u12 == 3) {
            *pu15 = 0;
          }
          if ((int)buf_3ac[stk_3c80 * 0x1d + 10] <= (int)buf_3ac[stk_3c80 * 0x1d + 9]) {
            stk_38e4[u2 * 0x6a7 + 1] = stk_38e4[u2 * 0x6a7 + 1] + 1;
            buf_3ac[u2] = 1;
            goto L_080881c0;
          }
        }
      }
      break;
    case 3:
      i2 = pi1[1];
      group = pi1[2];
      if (group == 3) {
        i23 = 1;
        group = 0;
        i19 = pi1[3];
      }
      else {
        i23 = pi1[3];
        i19 = 1;
      }
      BuildSlctTeamForArcade((int)(stk_38e4 + i2 * 0x6a7),i2,i19,group,i23);
      if (pi1[2] == 1) {
        stk_38e4[i2 * 0x6a7 + 4] = pi1[4];
      }
      buf_3ac[pi1[1]] = 1;
L_080881c0:
      i2 = SlctStateListNextItem((int)pi13);
      b6 = i2 != 0;
      break;
    case 4:
      if (i2 != 0) {
        stk_18c = 1;
      }
      if (b4) {
        buf_3ac[3] = 1;
        buf_3ac[2] = -1;
      }
      u2 = buf_3ac[3];
      u12 = buf_3ac[2];
      if (buf_3ac[3] == 0) {
        b7 = CharacterSelectStageKey(stk_3c5c[4],stk_3c5c[5],buf_3ac + 2,stk_3c80);
        buf_3ac[3] = ZEXT8(b7);
      }
      if (u12 != buf_3ac[2]) {
        GameSndPlay((int *)g[G_SYS_SOUNDS],*(int *)(slct + 0x10c8),*(int *)(slct + 0x10cc),0);
      }
      u12 = buf_3ac[3];
      if ((u2 == 0) && (u12 = 0, buf_3ac[3] != 0)) {
        GameSndPlay((int *)g[G_SYS_SOUNDS],*(int *)(slct + 0x10d0),*(int *)(slct + 0x10d4),0);
        u12 = buf_3ac[3];
      }
      if (u12 != 0) goto L_080881c0;
    }
L_default_080874eb:
    if (!b6) break;
    stk_3c38 = 0;
    stk_3c3c = 0;
    stk_3c5c[4] = 0;
    stk_3c5c[5] = 0;
  } while( true );
  SlctStateListUpdate((int)pi13);
  stk_3c80 = stk_3c80 + 1;
  if (1 < stk_3c80) goto code_r0x0808824b;
  goto L_08087466;
code_r0x0808824b:
  if ((stk_3c5c[2] != 0) && (stk_3c5c[3] != 0)) {
    if (buf_2b4[0] - 1 < 2) {
      if (((buf_2b4[0] == 2) && (stk_3ca8 == -1)) && (stk_3ca0 == 1)) {
        stk_3ca0 = 2;
        stk_3ca4 = stk_20;
        stk_3ca8 = stk_20 + *(int *)(slct + 0x1004);
      }
    }
    else {
      SelectDispState(buf_2b4,1);
    }
  }
  if ((0 < *(int *)(slct + 0x1000)) && (stk_3ca0 == 0)) {
    i2 = (stk_20 << 8) / *(int *)(slct + 0x1000);
    MasterPalMul(i2,i2,i2);
  }
  if (stk_20 == *(int *)(slct + 0x1000)) {
    stk_3ca0 = 1;
  }
  if ((0 < *(int *)(slct + 0x1004)) && (stk_3ca0 == 2)) {
    u12 = 0x100 - ((stk_20 - stk_3ca4) * 0x100) / *(int *)(slct + 0x1004);
    u12 = u12 & 0xffffffffU - ((int)u12 >> 0x1f);
    MasterPalMul(u12,u12,u12);
  }
  UpdateSelectDisp((int *)buf_2b4);
  if (g[0x7309] == 0) {
    ExplodArrayUpdate((int *)g[0x52bf]);
  }
  CharacterSelectScreenDraw((int)pi16);
  stk_20 = stk_20 + 1;
  if (stk_3c3c == 0x58) {
    ScreenSnap();
  }
  if (b5) goto L_0808844d;
  if ((stk_3ca8 != -1) && (stk_3ca8 < stk_20)) {
    b5 = true;
  }
  if (stk_3c3c == 1) goto L_0808844d;
  goto L_08087348;
}
#undef stk_3cc8
#undef stk_3ca8
#undef stk_3ca4
#undef stk_3ca0
#undef stk_3c84
#undef stk_3c80
#undef stk_3c64
#undef stk_3c5c
#undef stk_3c40
#undef stk_3c3c
#undef stk_3c38
#undef stk_3c34
#undef buf_3c08
#undef buf_3a9c
#undef stk_38e4
#undef buf_3ac
#undef buf_2b4
#undef stk_18c
#undef buf_188
#undef stk_20

/* CharacterSelectScreenDraw @ 0x08088630, 4562 bytes
 *
 * Draws the select screen: background, grid cells and portraits, cursors
 * (blinking for the second player when shared), big portraits and names of
 * the hovered and chosen characters, team menus, the stage name ("Stage:
 * Random", "Stage %i: %s") and the title ("Versus Mode", ...).
 *
 * Parameters:
 *   arg1         int
 *
 * Globals read: debug_display, demo_mode, debuginfo, clipboard,
 *               speed_flag, vretrace
 * Calls: MasterPalProcessChanges, PRSprArrayClear, BGArrayMove,
 *        BGArrayUpdate, BGArrayDrawLayer, SpriteArrayGetNum,
 *        W_ScaleSprite_S, SysExplodCreateDraw_Sys, W_BoxFillTransAdd16,
 *        V_FontDrawAlignBank, PRSprArrayDraw, FontDrawClipboard,
 *        TimerWaitSync, VRetrace, DrawToScreen, MasterPalFinishedDraw,
 *        FrameSkipUpdate
 * C library: makecol, sprintf
 * Called by: CharacterSelectScreen
 * Messages:
 *   "Stage: Random"
 *   "Stage %i: %s"
 *   "Versus Mode"
 *   "Team Arcade"
 *   "Team Versus"
 *   "Team Cooperative"
 *
 * Elecbyte file: src/mugen/charsel.c
 * Note: 10 data addresses refer to the data image (data/mugen_data.S).
 * Note: 4 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0x210 bytes,
 *       27 variables), because their address is taken.
 */
uint32_t CharacterSelectScreenDraw(int arg1)

{
  int *pi1;
  int i2;
  int i3;
  int index;
  uint32_t u5;
  int *pi6;
  int i7;
  int i8;
  int index2;
  int i10;
  char *format;
  unsigned char frame[0x210] __attribute__((aligned(16)));
#define stk_210 (*(int *)(frame + 0x0))
#define stk_1c4 (*(int *)(frame + 0x4c))
#define stk_1c0 (*(int **)(frame + 0x50))
#define stk_1bc (*(int *)(frame + 0x54))
#define stk_1b8 (*(uint32_t *)(frame + 0x58))
#define stk_1b4 (*(int *)(frame + 0x5c))
#define stk_1b0 (*(int *)(frame + 0x60))
#define stk_1ac (*(int **)(frame + 0x64))
#define stk_1a8 (*(int *)(frame + 0x68))
#define stk_1a4 (*(int *)(frame + 0x6c))
#define stk_1a0 (*(int *)(frame + 0x70))
#define stk_19c (*(int *)(frame + 0x74))
#define stk_198 (*(int *)(frame + 0x78))
#define stk_194 (*(int *)(frame + 0x7c))
#define stk_18c (*(int *)(frame + 0x84))
#define stk_168 (*(int *)(frame + 0xa8))
#define stk_164 (*(int *)(frame + 0xac))
#define stk_160 (*(uint32_t *)(frame + 0xb0))
#define stk_15c (*(int *)(frame + 0xb4))
#define stk_158 (*(int *)(frame + 0xb8))
#define stk_154 (*(int **)(frame + 0xbc))
#define stk_14c (*(int (*)[28])(frame + 0xc4))
#define stk_dc (*(int *)(frame + 0x134))
#define stk_d4 (*(int *)(frame + 0x13c))
#define stk_d0 (*(int *)(frame + 0x140))
#define stk_c8 (*(int *)(frame + 0x148))
#define stk_7c (*(char (*)[108])(frame + 0x194))
  
  index2 = 0;
  i2 = arg1 + 0x3978;
  stk_14c[2] = 0xffffffff;
  stk_14c[3] = 0xffffffff;
  stk_14c[0] = 0;
  stk_14c[1] = 0;
  MasterPalProcessChanges();
  i10 = cellCols;
  stk_168 = 0;
  do {
    i3 = stk_168 * 0x80;
    stk_160 = 0;
    i7 = i3 + 0x10;
    do {
      index = *(int *)(arg1 + 0x3970 + i7);
      if ((index == -1) || (i8 = *(int *)(arg1 + 0x3974 + i7), i8 == -1)) {
        *(uint32_t *)(i2 + i7) = 0xffffffff;
      }
      else {
        *(int *)(i2 + i7) = index + i8 * i10;
        if (*(int *)(arg1 + 0x3988 + i7) != 0) {
          *(uint32_t *)((int)stk_14c + index2 + 8) = stk_160;
        }
      }
      index = *(int *)(i3 + 0x14 + i2);
      if ((index == -1) || (i8 = *(int *)(arg1 + 0x3980 + i7), i8 == -1)) {
        *(uint32_t *)(arg1 + 0x3994 + i3) = 0xffffffff;
      }
      else {
        *(int *)(i7 + arg1 + 0x3984) = index + i8 * i10;
      }
      i7 = i7 + 0x20;
      stk_160 = stk_160 + 1;
      i3 = i3 + 0x20;
    } while ((int)stk_160 < 4);
    index2 = index2 + 4;
    stk_168 = stk_168 + 1;
  } while (stk_168 < 2);
  stk_1c0 = stk_14c;
  stk_168 = 0;
  do {
    index2 = stk_168 * 0x80;
    stk_160 = 0;
    i10 = index2 + 0x10;
    stk_210 = i10;
    do {
      if ((*(int *)(index2 + 8 + i2) != -1) && (*(int *)(index2 + 0xc + i2) != -1)) {
        i7 = *(int *)(stk_210 + 0x10 + i2);
        if (i7 == 2) {
          stk_164 = 0;
        }
        else if (i7 == 1) {
          stk_164 = 1;
        }
        stk_14c[stk_14c[stk_164] * 3 + stk_164 * 0x18 + 5] = *(int *)(i10 + 0x14 + i2)
        ;
        stk_14c[stk_14c[stk_164] * 3 + stk_164 * 0x18 + 4] = stk_168;
        stk_14c[stk_14c[stk_164] * 3 + stk_164 * 0x18 + 6] = stk_160;
        stk_14c[stk_164] = stk_14c[stk_164] + 1;
      }
      stk_160 = stk_160 + 1;
      stk_210 = stk_210 + 0x20;
      i10 = i10 + 0x20;
      index2 = index2 + 0x20;
    } while ((int)stk_160 < 4);
    stk_168 = stk_168 + 1;
  } while (stk_168 < 2);
  PRSprArrayClear((int *)g[0x413d]);
  BGArrayMove((int *)g[0x62cf],0.0,0.0);
  BGArrayUpdate(g[0x62cf]);
  if (g[0x7306] == 0) {
    BGArrayDrawLayer(g[0x62cf],0);
  }
  if (g[0x7306] == 0) {
    index2 = 0x13a0;
    i10 = 0x13b0;
    i7 = 0;
    stk_168 = 1;
    do {
      pi6 = cellHead;
      i3 = *(int *)((int)stk_14c + i7 + 8);
      if (((i3 != -1) &&
          (i3 = *(int *)((i3 + i7) * 0x20 + 0x1c + i2),
          cellHead[i3 * 0x80e + 0x80d] != 0)) &&
         (index = SpriteArrayGetNum((int *)cellHead[i3 * 0x80e + 0x80d],9000,1), index != -1)) {
        W_ScaleSprite_S((int *)pi6[i3 * 0x80e + 0x80d],index,(float80)*(int *)(index2 + slct + 4)
                        ,(float80)*(int *)(index2 + 8 + slct),
                        (float80)*(int *)(index2 + 0xc + slct) * *(float *)(index2 + 0x10 + slct),
                        *(float *)(i10 + slct + 4));
      }
      index2 = index2 + 0x28;
      i10 = i10 + 0x28;
      i7 = i7 + 4;
      stk_168 = stk_168 + -1;
    } while (-1 < stk_168);
  }
  stk_1b8 = *(uint32_t *)(slct + 0x1008);
  i10 = *(int *)(slct + 0x100c);
  stk_158 = 0;
  index2 = cellRows;
  i3 = slct;
  i7 = cellCols;
  if (0 < cellRows) {
    do {
      stk_15c = 0;
      if (0 < i7) {
        do {
          pi6 = cellHead + (stk_158 * i7 + stk_15c) * 0x80e;
          if ((*pi6 != -1) || (index2 = -1, *(int *)(i3 + 0x1028) != 0)) {
            SysExplodCreateDraw_Sys((int *)(i3 + 0x10f4),stk_1b8,i10,0);
            index2 = *pi6;
          }
          if (index2 == -2) {
            SysExplodCreateDraw_Sys
                      ((int *)(slct + 0x1160),stk_1b8 + *(int *)(slct + 0x1038),
                       i10 + *(int *)(slct + 0x103c),0);
          }
          if (((g[0x7306] == 0) && (pi6[0x80d] != 0)) &&
             ((pi6 != (int *)0xffffffcc &&
              (index2 = SpriteArrayGetNum((int *)pi6[0x80d],9000,0), index2 != -1)))) {
            W_ScaleSprite_S((int *)pi6[0x80d],index2,
                            (float80)(int)(stk_1b8 + *(int *)(slct + 0x1038)),
                            (float)(i10 + *(int *)(slct + 0x103c)),*(float *)(slct + 0x1030),
                            *(float *)(slct + 0x1034));
          }
          stk_15c = stk_15c + 1;
          stk_1b8 = stk_1b8 + *(int *)(slct + 0x101c) + *(int *)(slct + 0x1018);
          index2 = cellRows;
          i7 = cellCols;
          i3 = slct;
        } while (stk_15c < cellCols);
      }
      stk_1b8 = *(uint32_t *)(i3 + 0x1008);
      i10 = i10 + *(int *)(i3 + 0x1020) + *(int *)(i3 + 0x1018);
      stk_158 = stk_158 + 1;
    } while (stk_158 < index2);
  }
  if (g[0x7306] == 0) {
    stk_160 = 1;
    i10 = 0x100;
    do {
      index2 = *(int *)(i10 + 0x10 + i2);
      if (0 < index2) {
        index2 = (index2 * 0xff) / *(int *)(i10 + 0x14 + i2);
        u5 = makecol(index2,index2,index2);
        stk_1b8 = *(int *)(arg1 + 0x3980 + i10) *
                    (*(int *)(slct + 0x1018) + *(int *)(slct + 0x101c)) + *(int *)(slct + 0x1008);
        index2 = *(int *)(i10 + 0xc + i2) * (*(int *)(slct + 0x1018) + *(int *)(slct + 0x1020))
                + *(int *)(slct + 0x100c);
        W_BoxFillTransAdd16(stk_1b8,index2,(stk_1b8 + *(int *)(slct + 0x101c)) - 2,
                            index2 + *(int *)(slct + 0x1020) + -2,u5);
      }
      i10 = i10 + 0x10;
      stk_160 = stk_160 + -1;
    } while (-1 < (int)stk_160);
  }
  stk_164 = 0;
  stk_1c4 = 0;
  do {
    stk_160 = 0;
    if (0 < *stk_1c0) {
      index2 = arg1 + 0x3980;
      i10 = arg1 + 0x3984;
      stk_1bc = 0;
      do {
        i3 = stk_1bc + stk_1c4;
        i7 = *(int *)((int)stk_14c + i3 + 0x14);
        i3 = (*(int *)((int)stk_14c + i3 + 0x10) * 4 +
                *(int *)((int)stk_14c + i3 + 0x18)) * 0x20;
        if (stk_164 == 0) {
          pi6 = (int *)(slct + 0x12a8 + i7 * 0x6c);
L_08088ecc:
          SysExplodCreateDraw_Sys
                    (pi6,*(int *)(i3 + index2) *
                            (*(int *)(slct + 0x1018) + *(int *)(slct + 0x101c)) +
                            *(int *)(slct + 0x1008),
                     *(int *)(i3 + i10) * (*(int *)(slct + 0x1018) + *(int *)(slct + 0x1020))
                     + *(int *)(slct + 0x100c),0);
        }
        else if (stk_164 == 1) {
          if ((stk_14c[1] == 2) && (*(int *)(slct + 0x1090) != 0)) {
            index = (stk_d4 + stk_dc * 4) * 0x20;
            i8 = (stk_c8 + stk_d0 * 4) * 0x20;
            if ((*(int *)(index + index2) == *(int *)(i8 + index2)) &&
               (*(int *)(index + i10) == *(int *)(i8 + i10))) {
              if ((*(uint32_t *)(arg1 + 0x3c0c) & 7) < 4 == stk_160) {
                pi6 = (int *)(slct + 0x11d0 + i7 * 0x6c);
                goto L_08088ecc;
              }
              goto L_08088ed5;
            }
          }
          pi6 = (int *)(slct + 0x11d0 + i7 * 0x6c);
          goto L_08088ecc;
        }
L_08088ed5:
        stk_1b8 = stk_160 + 1;
        stk_1bc = stk_1bc + 0xc;
        stk_160 = stk_1b8;
      } while ((int)stk_1b8 < *stk_1c0);
    }
    stk_164 = stk_164 + 1;
    stk_1c0 = stk_1c0 + 1;
    stk_1c4 = stk_1c4 + 0x60;
    if (1 < stk_164) {
      pi6 = g;
      if (g[0x7306] == 0) {
        stk_168 = 0;
        stk_1b4 = 0;
        stk_1b8 = 0x13c0;
        do {
          i10 = *(int *)(stk_1b8 + 4 + slct);
          index2 = *(int *)(stk_1b8 + 8 + slct);
          stk_1b0 = stk_168 << 7;
          stk_160 = 3;
          do {
            i7 = *(int *)(stk_1b0 + 0x10 + i2);
            if (i7 != -1) {
              stk_154 = (int *)0x0;
              pi1 = cellHead + i7 * 0x80e;
              if ((char)pi1[1] == '\0') {
                if (*pi1 == -2) {
                  stk_154 = (int *)(int)&str_random;
                }
              }
              else {
                stk_154 = pi1 + 1;
              }
              if (stk_154 != (int *)0x0) {
                i7 = *(int *)(stk_1b4 + 0x13b8 + slct);
                if (i7 != -1) {
                  V_FontDrawAlignBank((char *)stk_154,(int *)pi6[i7 + 0x62c3],i10,index2,
                                      *(int *)(stk_1b4 + 0x13c0 + slct),
                                      *(int *)(stk_1b4 + 0x13bc + slct));
                  pi6 = g;
                }
                index2 = index2 + 0xe;
              }
            }
            stk_1b0 = stk_1b0 + 0x20;
            stk_160 = stk_160 + -1;
          } while (-1 < (int)stk_160);
          stk_168 = stk_168 + 1;
          stk_1b4 = stk_1b4 + 0x28;
          stk_1b8 = stk_1b8 + 0x28;
        } while (stk_168 < 2);
      }
      if (pi6[0x7306] == 0) {
        PRSprArrayDraw((int *)pi6[0x413d]);
      }
      if ((*(int *)(arg1 + 0x3aa0) != 0) && (g[0x7306] == 0)) {
        i10 = *(int *)(arg1 + 0x3888);
        if (i10 == -1) {
          format = "Stage: Random";
          u5 = stk_1b8;
        }
        else {
          u5 = g[0x33ac] + 0xfff + i10 * 0x1054;
          stk_1b8 = i10 + 1;
          format = "Stage %i: %s";
        }
        sprintf(stk_7c,format,stk_1b8,u5);
        if (*(int *)(arg1 + 0x388c) == 0) {
          i10 = *(int *)(((*(int *)(arg1 + 0x3c0c) - (*(int *)(arg1 + 0x3c0c) >> 0x1f)) * 2
                            & 4U) + 0x1394 + slct);
          i2 = *(int *)(slct + 0x13a0);
          index2 = *(int *)(slct + 0x1384);
          i7 = *(int *)(slct + 0x1380);
          i3 = *(int *)(((*(int *)(arg1 + 0x3c0c) - (*(int *)(arg1 + 0x3c0c) >> 0x1f)) * 2
                           & 4U) + 5000 + slct);
        }
        else {
          i10 = *(int *)(slct + 0x139c);
          i2 = *(int *)(slct + 0x13a0);
          index2 = *(int *)(slct + 0x1384);
          i7 = *(int *)(slct + 0x1380);
          i3 = *(int *)(slct + 0x1390);
        }
        V_FontDrawAlignBank(stk_7c,(int *)g[i3 + 0x62c3],i7,index2,i2,i10);
      }
      stk_1a0 = arg1 + 0x3ab8;
      stk_19c = arg1 + 0x3ab0;
      stk_1a4 = arg1 + 0x3ab4;
      stk_1a8 = arg1 + 0x3aac;
      stk_1ac = (int *)(arg1 + 0x3aa4);
      stk_168 = 0;
      stk_198 = stk_1a0;
      do {
        if (*stk_1ac != 0) {
          index2 = stk_1ac[2] * 0x2e4;
          i10 = *(int *)(index2 + 0x13f8 + slct);
          i2 = *(int *)(index2 + 0x13fc + slct);
          SysExplodCreateDraw_Sys((int *)(index2 + 0x1400 + slct),i10,i2,0);
          if ((g[0x33b3] == 0) || (stk_168 == stk_1ac[2])) {
            pi6 = (int *)(slct + 0x146c + stk_1ac[2] * 0x2e4);
          }
          else {
            pi6 = (int *)(slct + 0x14d8 + stk_1ac[2] * 0x2e4);
          }
          SysExplodCreateDraw_Sys(pi6,i10,i2,0);
          index2 = stk_1ac[2];
          i10 = i10 + *(int *)(index2 * 0x2e4 + 0x155c + slct);
          stk_160 = 0;
          i2 = i2 + *(int *)(index2 * 0x2e4 + 0x1560 + slct);
          if (0 < stk_1ac[4]) {
            stk_194 = 0x10;
            do {
              if (stk_160 == stk_1ac[3]) {
                i7 = (index2 * 0xb9 + 1 + (*(int *)(arg1 + 0x3c0c) / 2 & 1U)) * 4;
                stk_18c = *(int *)(i7 + 0x1564 + slct);
                i7 = *(int *)(i7 + 0x1570 + slct);
                SysExplodCreateDraw_Sys((int *)(slct + 0x1588 + index2 * 0x2e4),i10,i2,0);
                index2 = stk_1ac[2];
              }
              else {
                stk_18c = *(int *)(index2 * 0x2e4 + 0x1564 + slct);
                i7 = *(int *)(index2 * 0x2e4 + 0x1570 + slct);
              }
              V_FontDrawAlignBank(*(char **)(stk_194 + stk_1a8),(int *)g[stk_18c + 0x62c3],
                                  i10,i2,*(int *)(slct + 0x157c + index2 * 0x2e4),i7);
              if (*(int *)(stk_194 + stk_1a0) < *(int *)(stk_194 + stk_1a4)) {
                index2 = stk_1ac[2];
              }
              else {
                stk_164 = 0;
                if (*(int *)(stk_194 + stk_1a0) < 1) {
                  index2 = stk_1ac[2];
                }
                else {
                  index2 = stk_1ac[2];
                  i7 = i10;
                  i3 = i2;
                  do {
                    if (stk_164 < *(int *)(stk_194 + stk_19c)) {
                      pi6 = (int *)(slct + 0x15f4 + index2 * 0x2e4);
                    }
                    else {
                      pi6 = (int *)(slct + 0x1668 + index2 * 0x2e4);
                    }
                    SysExplodCreateDraw_Sys(pi6,i7,i3,0);
                    index2 = stk_1ac[2];
                    i7 = i7 + *(int *)(index2 * 0x2e4 + 0x1660 + slct);
                    i3 = i3 + *(int *)(index2 * 0x2e4 + 0x1664 + slct);
                    stk_164 = stk_164 + 1;
                  } while (stk_164 < *(int *)(stk_194 + stk_198));
                }
              }
              i10 = i10 + *(int *)(index2 * 0x2e4 + 0x1580 + slct);
              stk_160 = stk_160 + 1;
              stk_194 = stk_194 + 0x14;
              i2 = i2 + *(int *)(index2 * 0x2e4 + 0x1584 + slct);
            } while ((int)stk_160 < stk_1ac[4]);
          }
        }
        stk_168 = stk_168 + 1;
        stk_198 = stk_198 + 0xb4;
        stk_19c = stk_19c + 0xb4;
        stk_1a0 = stk_1a0 + 0xb4;
        stk_1a4 = stk_1a4 + 0xb4;
        stk_1a8 = stk_1a8 + 0xb4;
        stk_1ac = stk_1ac + 0x2d;
      } while (stk_168 < 2);
      if (g[0x7306] == 0) {
        stk_154 = (int *)0x0;
        switch(g[0x33b5]) {
        case 0:
          stk_154 = (int *)(int)&str_arcade;
          break;
        case 1:
          stk_154 = (int *)(int)&str_versus_mode_7b4e;
          break;
        case 2:
          stk_154 = (int *)(int)&str_team_arcade_7b5a;
          break;
        case 3:
          stk_154 = (int *)(int)&str_team_versus_7b66;
          break;
        case 4:
          stk_154 = (int *)(int)&str_team_cooperative_7b72;
          break;
        case 5:
          stk_154 = (int *)(int)&str_survival_7b83;
          break;
        case 6:
          stk_154 = (int *)(int)&str_survival_cooperative_7b8c;
          break;
        case 7:
          stk_154 = (int *)(int)&str_training_mode_7ba1;
          break;
        case 8:
          stk_154 = (int *)(int)&str_watch_mode_7baf;
        }
        if ((*(int *)(slct + 0x10e8) != -1) && (stk_154 != (int *)0x0)) {
          V_FontDrawAlignBank((char *)stk_154,(int *)g[*(int *)(slct + 0x10e8) + 0x62c3],
                              *(int *)(slct + 0x10e0),*(int *)(slct + 0x10e4),
                              *(int *)(slct + 0x10f0),*(int *)(slct + 0x10ec));
        }
        BGArrayDrawLayer(g[0x62cf],1);
      }
      if ((g[G_DEBUG_DISPLAY] != 0) && ((g[G_DEMO_MODE] == 0 || (g[G_DEBUGINFO] != 0)))) {
        u5 = makecol(0xff,0xff,0xff);
        FontDrawClipboard((int *)g[G_CLIPBOARD],(int *)g[0x413a],10,0x32,u5);
      }
      if (g[G_SPEED_FLAG] == 0) {
        TimerWaitSync();
      }
      if ((g[0x7306] == 0) && (g[G_VRETRACE] != 0)) {
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
#undef stk_210
#undef stk_1c4
#undef stk_1c0
#undef stk_1bc
#undef stk_1b8
#undef stk_1b4
#undef stk_1b0
#undef stk_1ac
#undef stk_1a8
#undef stk_1a4
#undef stk_1a0
#undef stk_19c
#undef stk_198
#undef stk_194
#undef stk_18c
#undef stk_168
#undef stk_164
#undef stk_160
#undef stk_15c
#undef stk_158
#undef stk_154
#undef stk_14c
#undef stk_dc
#undef stk_d4
#undef stk_d0
#undef stk_c8
#undef stk_7c

/* BuildSelectList @ 0x08089810, 1421 bytes
 *
 * Builds the list of grid cells for the select screen from the character
 * list and the configured rows and columns (empty cells, random cells).
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t
 *   arg3         int
 *
 * Called by: CharacterSelectScreen
 *
 * Elecbyte file: src/mugen/charsel.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x20 bytes, 1
 *       variables), because their address is taken.
 */
int BuildSelectList(int arg1,uint32_t arg2,int arg3)

{
  int i1;
  int *pi2;
  uint32_t *pu3;
  int i4;
  int i5;
  unsigned char frame[0x20] __attribute__((aligned(16)));
#define stk_14 (*(int (*)[2])(frame + 0xc))
  
  pi2 = g;
  stk_14[0] = arg1;
  stk_14[1] = arg1 + 0x1a0;
  *(uint32_t *)stk_14[arg3] = 0;
  pi2[0x33b3] = 0;
  pi2[0x33b4] = 0;
  pi2[0x33ae] = 0;
  switch(arg2) {
  case 0:
    i1 = stk_14[arg3];
    *(uint32_t *)(i1 + 0x28) = 2;
    *(int *)(i1 + 0x2c) = arg3;
    *(uint32_t *)(i1 + 0x30) = 0;
    *(uint32_t *)(i1 + 0x34) = 1;
    *(int *)(i1 + 0x54) = 1 - arg3;
    *(uint32_t *)(i1 + 0x50) = 3;
    *(uint32_t *)(i1 + 0x58) = 0;
    *(uint32_t *)(i1 + 0x5c) = 1;
    *(uint32_t *)(i1 + 0x78) = 5;
    *(uint32_t *)(i1 + 400) = 4;
    pi2 = g;
    goto L_08089b29;
  case 1:
    *(uint32_t *)(arg1 + 0x28) = 2;
    *(uint32_t *)(arg1 + 0x2c) = 0;
    *(uint32_t *)(arg1 + 0x30) = 0;
    *(uint32_t *)(arg1 + 0x34) = 1;
    *(uint32_t *)(arg1 + 0x50) = 4;
    *(uint32_t *)(arg1 + 0x78) = 5;
    *(uint32_t *)(arg1 + 400) = 4;
    i1 = 0x19;
    i4 = 6;
    *(uint32_t *)(arg1 + 0x240) = 2;
    *(uint32_t *)(arg1 + 0x244) = 1;
    *(uint32_t *)(arg1 + 0x248) = 0;
    *(uint32_t *)(arg1 + 0x24c) = 1;
    goto L_08089a76;
  case 2:
    i1 = stk_14[arg3];
    *(uint32_t *)(i1 + 0x28) = 1;
    *(int *)(i1 + 0x4c) = i1 + 0x50;
    *(int *)(i1 + 0x48) = arg3;
    *(uint32_t *)(i1 + 0x3c) = 0;
    *(uint32_t *)(i1 + 0x40) = 0xb;
    *(uint32_t *)(i1 + 0x44) = 1;
    pu3 = (uint32_t *)(i1 + 0x50);
    i4 = 0xf;
    i5 = 4;
    *pu3 = 2;
    *(int *)(i1 + 0x54) = arg3;
    *(uint32_t *)(i1 + 0x58) = 1;
    *(uint32_t *)(i1 + 0x60) = 0;
    goto L_08089abf;
  case 3:
    *(uint32_t *)(arg1 + 0x28) = 1;
    *(int *)(arg1 + 0x4c) = arg1 + 0x50;
    *(uint32_t *)(arg1 + 0x3c) = 0;
    *(uint32_t *)(arg1 + 0x40) = 0xb;
    *(uint32_t *)(arg1 + 0x48) = 0;
    *(uint32_t *)(arg1 + 0x44) = 1;
    *(uint32_t *)(arg1 + 0x50) = 2;
    *(uint32_t *)(arg1 + 0x54) = 0;
    *(uint32_t *)(arg1 + 0x58) = 1;
    *(uint32_t *)(arg1 + 0x60) = 0;
    *(uint32_t *)(arg1 + 0x5c) = 2;
    *(uint32_t *)(arg1 + 0x78) = 4;
    *(uint32_t *)(arg1 + 0xa0) = 5;
    *(uint32_t *)(arg1 + 400) = 5;
    *(uint32_t *)(arg1 + 0x268) = 1;
    *(int *)(arg1 + 0x28c) = arg1 + 0x290;
    *(uint32_t *)(arg1 + 0x27c) = 0;
    *(uint32_t *)(arg1 + 0x280) = 0xb;
    *(uint32_t *)(arg1 + 0x288) = 1;
    *(uint32_t *)(arg1 + 0x284) = 1;
    i1 = 0x23;
    i4 = 8;
    *(uint32_t *)(arg1 + 0x290) = 2;
    *(uint32_t *)(arg1 + 0x294) = 1;
    *(uint32_t *)(arg1 + 0x298) = 1;
    *(uint32_t *)(arg1 + 0x2a0) = 0;
    *(uint32_t *)(arg1 + 0x29c) = 2;
L_08089a76:
    *(uint32_t *)(stk_14[1] + i1 * 8) = 4;
    *(uint32_t *)(stk_14[1] + i4 * 0x28) = 5;
    *(int *)(arg1 + 0x330) = i4 + 1;
    break;
  case 4:
    i1 = stk_14[arg3];
    pu3 = (uint32_t *)(i1 + 0x28);
    i4 = 10;
    i5 = 3;
    *pu3 = 2;
    *(int *)(i1 + 0x2c) = arg3;
    *(uint32_t *)(i1 + 0x30) = 1;
    *(uint32_t *)(i1 + 0x38) = 1;
L_08089abf:
    pu3[3] = 2;
    pu3 = (uint32_t *)(i1 + i4 * 8);
    *pu3 = 1;
    pu3[9] = pu3 + 10;
    pu3[8] = 1 - arg3;
    pu3[5] = 0;
    pu3[6] = 0xb;
    pu3[7] = 1;
    pu3 = (uint32_t *)(i1 + i5 * 0x28);
    pu3[1] = 1 - arg3;
    pi2 = g;
    *pu3 = 3;
    pu3[2] = 1;
    pu3[4] = 2;
    pu3[3] = 2;
    *(uint32_t *)(i1 + (i5 + 1) * 0x28) = 5;
    *(int *)(i1 + 400) = i5 + 2;
L_08089b29:
    pi2[0x33b3] = arg3 + 1;
    break;
  case 5:
    i1 = stk_14[arg3];
    *(uint32_t *)(i1 + 0x28) = 1;
    *(int *)(i1 + 0x4c) = i1 + 0x50;
    *(int *)(i1 + 0x48) = arg3;
    *(uint32_t *)(i1 + 0x3c) = 0;
    *(uint32_t *)(i1 + 0x40) = 0xb;
    *(uint32_t *)(i1 + 0x44) = 0;
    pu3 = (uint32_t *)(i1 + 0x50);
    i4 = 0xf;
    i5 = 4;
    *pu3 = 2;
    *(int *)(i1 + 0x54) = arg3;
    *(uint32_t *)(i1 + 0x58) = 1;
    *(uint32_t *)(i1 + 0x60) = 0;
    goto L_08089bbc;
  case 6:
    i1 = stk_14[arg3];
    pu3 = (uint32_t *)(i1 + 0x28);
    i4 = 10;
    i5 = 3;
    *pu3 = 2;
    *(int *)(i1 + 0x2c) = arg3;
    *(uint32_t *)(i1 + 0x30) = 1;
    *(uint32_t *)(i1 + 0x38) = 1;
L_08089bbc:
    pu3[3] = 2;
    pu3 = (uint32_t *)(i1 + i4 * 8);
    *pu3 = 1;
    pu3[9] = pu3 + 10;
    pu3[8] = 1 - arg3;
    pu3[5] = 0;
    pu3[6] = 3;
    pu3[7] = 0;
    pu3 = (uint32_t *)(i1 + i5 * 0x28);
    pu3[1] = 1 - arg3;
    *pu3 = 3;
    pu3[2] = 1;
    pu3[4] = 2;
    pu3[3] = 2;
    *(uint32_t *)(arg1 + (i5 + 1) * 0x28) = 4;
    *(uint32_t *)(i1 + (i5 + 2) * 0x28) = 5;
    *(int *)(i1 + 400) = i5 + 3;
    pi2 = g;
    g[0x33b3] = 0;
    pi2[0x33b4] = arg3 + 1;
    pi2[0x33ae] = 1;
    break;
  case 7:
    i1 = stk_14[arg3];
    *(uint32_t *)(i1 + 0x28) = 2;
    *(int *)(i1 + 0x2c) = arg3;
    *(uint32_t *)(i1 + 0x30) = 0;
    *(uint32_t *)(i1 + 0x34) = 1;
    *(int *)(i1 + 0x54) = 1 - arg3;
    *(uint32_t *)(i1 + 0x50) = 2;
    *(uint32_t *)(i1 + 0x58) = 0;
    *(uint32_t *)(i1 + 0x5c) = 1;
    *(uint32_t *)(i1 + 0x78) = 4;
    *(uint32_t *)(i1 + 0xa0) = 5;
    *(uint32_t *)(i1 + 400) = 5;
    g[0x33ae] = 3;
    break;
  case 8:
    i1 = stk_14[arg3];
    *(uint32_t *)(i1 + 0x28) = 1;
    *(int *)(i1 + 0x4c) = i1 + 0x50;
    *(int *)(i1 + 0x48) = arg3;
    *(uint32_t *)(i1 + 0x3c) = 0;
    *(uint32_t *)(i1 + 0x40) = 0xb;
    *(uint32_t *)(i1 + 0x44) = 0;
    *(uint32_t *)(i1 + 0x50) = 2;
    *(int *)(i1 + 0x54) = arg3;
    *(uint32_t *)(i1 + 0x58) = 0;
    *(uint32_t *)(i1 + 0x5c) = 1;
    *(uint32_t *)(i1 + 0x78) = 1;
    *(int *)(i1 + 0x9c) = i1 + 0xa0;
    *(int *)(i1 + 0x98) = 1 - arg3;
    *(uint32_t *)(i1 + 0x8c) = 0;
    *(uint32_t *)(i1 + 0x90) = 0xb;
    *(uint32_t *)(i1 + 0x94) = 0;
    *(uint32_t *)(i1 + 0xa0) = 2;
    *(int *)(i1 + 0xa4) = 1 - arg3;
    *(uint32_t *)(i1 + 0xa8) = 0;
    *(uint32_t *)(i1 + 0xac) = 1;
    *(uint32_t *)(i1 + 200) = 4;
    *(uint32_t *)(i1 + 0xf0) = 5;
    *(uint32_t *)(i1 + 400) = 7;
    g[0x33ae] = 2;
  }
  return stk_14[1];
}
#undef stk_14

/* InitSelectDisp @ 0x08089da0, 85 bytes
 *
 * Initialises a side's portrait display state.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: CharacterSelectScreen
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void InitSelectDisp(int arg1)

{
  uint32_t *pu1;
  int i2;
  int i3;
  int i4;
  
  i4 = 0;
  i2 = arg1;
  do {
    pu1 = (uint32_t *)(i2 + 0x10);
    i3 = 3;
    do {
      pu1[-1] = 0xffffffff;
      pu1[-2] = 0xffffffff;
      *pu1 = 0xffffffff;
      pu1 = pu1 + 8;
      i3 = i3 + -1;
    } while (-1 < i3);
    i4 = i4 + 1;
    i2 = i2 + 0x80;
  } while (i4 < 2);
  i2 = 1;
  pu1 = (uint32_t *)(arg1 + 0x124);
  do {
    *pu1 = 4;
    pu1 = pu1 + -4;
    i2 = i2 + -1;
  } while (-1 < i2);
  return;
}

/* UpdateSelectDisp @ 0x08089e00, 75 bytes
 *
 * Advances a side's portrait display (random cycling with
 * cell.random.switchtime).
 *
 * Parameters:
 *   arg1         int *
 *
 * Called by: CharacterSelectScreen
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void UpdateSelectDisp(int *arg1)

{
  int i1;
  int i2;
  int i3;
  
  i3 = 1;
  i2 = 0x100;
  do {
    i1 = *(int *)((int)arg1 + i2 + 0x10);
    if (0 < i1) {
      *(int *)((int)arg1 + i2 + 0x10) = i1 + -1;
    }
    i2 = i2 + 0x10;
    i3 = i3 + -1;
  } while (-1 < i3);
  arg1[1] = arg1[1] + 1;
  if (((*arg1 == 1) && (arg1[0x44] < 1)) && (arg1[0x48] < 1)) {
    *arg1 = 2;
  }
  return;
}

/* SelectDispState @ 0x08089e50, 18 bytes
 *
 * Sets a side's portrait display state.
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         uint32_t
 *
 * Called by: CharacterSelectScreen
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void SelectDispState(uint32_t *arg1,uint32_t arg2)

{
  *arg1 = arg2;
  arg1[1] = 0;
  return;
}

/* FlashBox @ 0x08089e70, 79 bytes
 *
 * Returns whether a flashing cursor box is visible at time `t` (blink
 * period).
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t
 *   arg3         uint32_t
 *
 * Called by: CharacterSelectScreen
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void FlashBox(int arg1,uint32_t arg2,uint32_t arg3)

{
  int *pi1;
  int i2;
  int i3;
  int i4;
  
  i2 = 0;
  i4 = 0;
  i3 = 999;
  pi1 = (int *)(arg1 + 0x110);
  do {
    if (*pi1 < i3) {
      i3 = *pi1;
      i4 = i2;
    }
    i2 = i2 + 1;
    pi1 = pi1 + 4;
  } while (i2 < 2);
  i4 = i4 * 0x10;
  *(int *)(i4 + 0x110 + arg1) = *(int *)(i4 + 0x114 + arg1) + 1;
  *(uint32_t *)(i4 + 0x108 + arg1) = arg2;
  *(uint32_t *)(i4 + 0x10c + arg1) = arg3;
  return;
}

/* CharacterSelectScreenKey @ 0x08089ec0, 867 bytes
 *
 * Handles a key for a side's cursor on the grid: movement with wrapping and
 * empty-box skipping, random select, confirm with the palette chosen by the
 * button, cancel.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         int
 *   arg3         int *
 *   arg4         int *
 *   arg5         int
 *
 * Globals read: num_chars
 * Calls: KBToUInp
 * Called by: CharacterSelectScreen
 *
 * Elecbyte file: src/mugen/charsel.c
 */
int CharacterSelectScreenKey(uint32_t arg1,int arg2,int *arg3,int *arg4,int arg5)

{
  uint32_t uinp;
  int i2;
  int i3;
  int i4;
  int i5;
  int stk_20;
  
  stk_20 = -1;
  if (arg2 != arg5) {
    return -1;
  }
  if (g[G_NUM_CHARS] == 0) {
    return -1;
  }
  if ((arg1 & 8) != 0) {
    i2 = *arg3;
    i4 = cellCols;
    i5 = i2;
    do {
      if (cellHead[(*arg4 * cellCols + i2) * 0x80e] != -1) {
        i5 = i2;
      }
      i2 = i2 + -1;
      if (i2 < 0) {
        i2 = i5;
        if (*(int *)(slct + 0x1024) == 0) goto L_08089f98;
        i2 = cellCols + -1;
      }
      if (((cellHead[(*arg4 * cellCols + i2) * 0x80e] != -1) || (*(int *)(slct + 0x102c) != 0)
          ) || (i4 = i4 + -1, i4 == 0)) goto L_08089f98;
    } while( true );
  }
L_08089f9e:
  if ((arg1 & 2) != 0) {
    i2 = *arg3;
    i4 = cellCols;
    i5 = i2;
    do {
      if (cellHead[(*arg4 * cellCols + i2) * 0x80e] != -1) {
        i5 = i2;
      }
      i2 = i2 + 1;
    } while (((i2 < cellCols) || (i2 = 0, i3 = i5, *(int *)(slct + 0x1024) != 0)) &&
            ((i3 = i2, cellHead[(*arg4 * cellCols + i2) * 0x80e] == -1 &&
             ((*(int *)(slct + 0x102c) == 0 && (i4 = i4 + -1, i4 != 0))))));
    *arg3 = i3;
  }
  if ((arg1 & 1) != 0) {
    i2 = *arg4;
    i4 = cellRows;
    i5 = i2;
    do {
      if (cellHead[(i2 * cellCols + *arg3) * 0x80e] != -1) {
        i5 = i2;
      }
      i2 = i2 + -1;
      if (i2 < 0) {
        i2 = i5;
        if (*(int *)(slct + 0x1024) == 0) goto L_0808a0e0;
        i2 = cellRows + -1;
      }
      if (((cellHead[(i2 * cellCols + *arg3) * 0x80e] != -1) || (*(int *)(slct + 0x102c) != 0)
          ) || (i4 = i4 + -1, i4 == 0)) goto L_0808a0e0;
    } while( true );
  }
L_0808a0e6:
  if ((arg1 & 4) != 0) {
    i2 = *arg4;
    i4 = cellRows;
    i5 = i2;
    do {
      if (cellHead[(i2 * cellCols + *arg3) * 0x80e] != -1) {
        i5 = i2;
      }
      i2 = i2 + 1;
    } while (((i2 < cellRows) || (i2 = 0, i3 = i5, *(int *)(slct + 0x1024) != 0)) &&
            ((i3 = i2, cellHead[(i2 * cellCols + *arg3) * 0x80e] == -1 &&
             ((*(int *)(slct + 0x102c) == 0 && (i4 = i4 + -1, i4 != 0))))));
    *arg4 = i3;
  }
  if (cellHead[(cellCols * *arg4 + *arg3) * 0x80e] != -1) {
    i2 = 0;
    do {
      if ((arg1 & 0x10 << ((uint8_t)i2 & 0x1f)) != 0) {
        stk_20 = i2;
      }
      i2 = i2 + 1;
    } while (i2 < 6);
  }
  uinp = KBToUInp(g[arg5 * 0xd + 0x7346]);
  if ((uinpflag[uinp] != 0) && (stk_20 != -1)) {
    stk_20 = stk_20 + 6;
  }
  return stk_20;
L_08089f98:
  *arg3 = i2;
  goto L_08089f9e;
L_0808a0e0:
  *arg4 = i2;
  goto L_0808a0e6;
}

/* CharacterSelectStageKey @ 0x0808a230, 104 bytes
 *
 * Handles a key on the stage selection: left/right through the stages (and
 * "random"), confirm.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         int
 *   arg3         uint32_t *
 *   arg4         int
 *
 * Called by: CharacterSelectScreen
 *
 * Elecbyte file: src/mugen/charsel.c
 */
bool CharacterSelectStageKey(uint32_t arg1,int arg2,uint32_t *arg3,int arg4)

{
  uint32_t u1;
  bool b2;
  
  u1 = *arg3;
  if (arg2 == arg4) {
    if (((arg1 & 8) != 0) && (u1 = u1 - 1, (int)u1 < -1)) {
      u1 = g[0x33ad] - 1;
    }
    if ((arg1 & 2) != 0) {
      u1 = u1 + 1 | ((int)(u1 + 1) < g[0x33ad]) - 1;
    }
    b2 = (arg1 & 0x7f0) != 0;
    *arg3 = u1;
  }
  else {
    b2 = false;
  }
  return b2;
}

/* CharacterSelectMenuKey @ 0x0808a2a0, 256 bytes
 *
 * Handles a key in a side's team menu: choose single, simul or turns and the
 * team size.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         uint32_t
 *   arg3         int
 *   arg4         int
 *
 * Calls: IntSwap
 * Called by: CharacterSelectScreen
 *
 * Elecbyte file: src/mugen/charsel.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x20 bytes, 2
 *       variables), because their address is taken.
 */
uint32_t CharacterSelectMenuKey(uint32_t arg1,uint32_t arg2,int arg3,int arg4)

{
  int i1;
  int i2;
  uint32_t u3;
  unsigned char frame[0x20] __attribute__((aligned(16)));
#define stk_18 (*(uint32_t *)(frame + 0x8))
#define stk_14 (*(uint32_t *)(frame + 0xc))
  
  stk_18 = 2;
  stk_14 = 8;
  if (arg4 == -1) {
    IntSwap(&stk_18,&stk_14);
  }
  if (((arg1 & 1) != 0) &&
     (i2 = *(int *)(arg3 + 0xc) + -1, *(int *)(arg3 + 0xc) = i2, i2 < 0)) {
    if (*(int *)(slct + 0x13f4) == 0) {
      *(uint32_t *)(arg3 + 0xc) = 0;
    }
    else {
      *(int *)(arg3 + 0xc) = *(int *)(arg3 + 0x10) + -1;
    }
  }
  if ((arg1 & 4) != 0) {
    i2 = *(int *)(arg3 + 0xc) + 1;
    *(int *)(arg3 + 0xc) = i2;
    if (*(int *)(arg3 + 0x10) <= i2) {
      if (*(int *)(slct + 0x13f4) == 0) {
        *(int *)(arg3 + 0xc) = *(int *)(arg3 + 0x10) + -1;
      }
      else {
        *(uint32_t *)(arg3 + 0xc) = 0;
      }
    }
  }
  i2 = arg3 + *(int *)(arg3 + 0xc) * 0x14;
  if (*(int *)(i2 + 0x20) < *(int *)(i2 + 0x24)) {
    if (((arg1 & stk_18) != 0) && (*(int *)(i2 + 0x1c) < *(int *)(i2 + 0x24))) {
      *(int *)(i2 + 0x1c) = *(int *)(i2 + 0x1c) + 1;
    }
    if (((arg1 & stk_14) != 0) &&
       (i1 = *(int *)(i2 + 0x1c), *(int *)(i2 + 0x20) < i1)) {
      *(int *)(i2 + 0x1c) = i1 + -1;
    }
  }
  if ((arg1 & 0x7f0) == 0) {
    u3 = 0xffffffff;
  }
  else {
    u3 = *(uint32_t *)(arg3 + 0xc);
  }
  return u3;
}
#undef stk_18
#undef stk_14

/* CharselResetCursor @ 0x0808a3a0, 62 bytes
 *
 * Puts both select cursors back on their start cells
 * (p1/p2.cursor.startcell).
 *
 * Called by: ModeSelect
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void CharselResetCursor(void)

{
  uint32_t *pu1;
  int i2;
  int i3;
  int i4;
  
  i4 = 0;
  i2 = slct;
  do {
    pu1 = (uint32_t *)(i2 + 0x1070);
    i3 = 3;
    do {
      pu1[-8] = 0xffffffff;
      *pu1 = 0xffffffff;
      pu1 = pu1 + 1;
      i3 = i3 + -1;
    } while (-1 < i3);
    i4 = i4 + 1;
    i2 = i2 + 0x10;
  } while (i4 < 2);
  return;
}

/* CharselSaveCursor @ 0x0808a3e0, 45 bytes
 *
 * Remembers a side's cursor position for the next visit of the select
 * screen.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         uint32_t
 *   arg3         uint32_t
 *   arg4         int
 *   arg5         int
 *
 * Called by: CharacterSelectScreen
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void CharselSaveCursor(uint32_t arg1,uint32_t arg2,uint32_t arg3,int arg4,
                      int arg5)

{
  int i1;
  int i2;
  
  i1 = slct;
  i2 = (arg5 * 4 + arg4) * 4;
  *(uint32_t *)(slct + 0x1070 + i2) = arg2;
  *(uint32_t *)(i1 + 0x1050 + i2) = arg3;
  return;
}

/* CharselRestoreCursor @ 0x0808a410, 173 bytes
 *
 * Restores a side's remembered cursor position.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *
 * Called by: BuildSlctCtrl
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void CharselRestoreCursor(int arg1,int arg2,int arg3)

{
  int i1;
  int i2;
  int *pi3;
  int i4;
  int i5;
  int stk_20;
  int stk_14;
  
  i1 = slct;
  i5 = 0x20;
  stk_20 = 0x30;
  stk_14 = 0;
  i2 = arg3 * 0x74 + arg1;
  i4 = arg2 * 0x10 + 0x1050;
  pi3 = (int *)(slct + 0x1070 + arg2 * 0x10);
  do {
    if (*pi3 != -1) {
      *(int *)(i5 + i2 + 0x38a0) = *pi3;
    }
    if (*(int *)(i4 + i1) != -1) {
      *(int *)(stk_20 + i2 + 0x3894) = *(int *)(i4 + i1);
    }
    stk_14 = stk_14 + 1;
    stk_20 = stk_20 + 0x14;
    i5 = i5 + 0x14;
    i4 = i4 + 4;
    pi3 = pi3 + 1;
  } while (stk_14 < 4);
  return;
}

/* CharselResetMenuPos @ 0x0808a4c0, 31 bytes
 *
 * Resets the remembered team menu positions.
 *
 * Called by: ModeSelect
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void CharselResetMenuPos(void)

{
  uint32_t *pu1;
  int i2;
  
  i2 = 1;
  pu1 = (uint32_t *)(slct + 0x16d4);
  do {
    *pu1 = 0xffffffff;
    pu1 = pu1 + 0xb9;
    i2 = i2 + -1;
  } while (-1 < i2);
  return;
}

/* CharselSaveMenuPos @ 0x0808a4e0, 55 bytes
 *
 * Remembers a side's team menu position.
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t *
 *   arg3         int
 *
 * Called by: CharacterSelectScreen
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void CharselSaveMenuPos(int arg1,uint32_t *arg2,int arg3)

{
  int i1;
  
  i1 = arg3 * 0xb4 + arg1;
  *arg2 = *(uint32_t *)(i1 + 0x3ab0);
  arg2[1] = *(uint32_t *)(i1 + 0x3ac0 + *(int *)(i1 + 0x3ab0) * 0x14);
  return;
}

/* CharselRestoreMenuPos @ 0x0808a520, 59 bytes
 *
 * Restores a side's team menu position.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int *
 *   arg3         int
 *
 * Called by: BuildMenuCtrl
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void CharselRestoreMenuPos(int arg1,int *arg2,int arg3)

{
  int i1;
  int i2;
  
  i2 = arg3 * 0xb4 + arg1;
  i1 = *arg2;
  if (i1 != -1) {
    *(int *)(i2 + 0x3ab0) = i1;
    *(int *)(i2 + 0x3ac0 + i1 * 0x14) = arg2[1];
  }
  return;
}

/* CharselReadConfig @ 0x0808a560, 2576 bytes
 *
 * Reads the "[Select Info]" group of system.def: fade times, rows, columns,
 * wrapping, pos, showemptyboxes, moveoveremptyboxes, cell.size,
 * cell.spacing, cell.bg, cell.random, portrait offset and scale, title font
 * and offset, the per-side cursor, face, name and team menu settings
 * ("p1."/"p2." keys), the stage selection fonts, and the select sounds.
 *
 * Parameters:
 *   tp           int
 *
 * Text keys read: "fadein.time", "fadeout.time", "rows", "columns",
 *                 "wrapping", "pos", "showemptyboxes",
 *                 "moveoveremptyboxes", "p1.cursor.startcell",
 *                 "p2.cursor.startcell", "p2.cursor.blink", "cell.size",
 *                 "cell.spacing", "portrait.scale", "portrait.offset",
 *                 "title.offset", "title.font", "p1.cursor.move.snd",
 *                 "p2.cursor.move.snd", "p1.cursor.done.snd",
 *                 "p2.cursor.done.snd", "p1.random.move.snd",
 *                 "p2.random.move.snd", "random.move.snd.cancel", ...
 * Globals read: files_select, fadein_time, errmsg
 * Calls: TPGetValueInt, TPScanf, ParseSndGI, SysExplodParse
 * C library: sprintf, calloc
 * Called by: GameLoadSystem
 * Messages:
 *   "Out of memory"
 *
 * Elecbyte file: src/mugen/charsel.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: Locals live in `frame`, laid out as on the original stack (0x130 bytes,
 *       3 variables), because their address is taken.
 */
bool CharselReadConfig(int tp)

{
  int *pi1;
  int i2;
  void *pv3;
  uint32_t *pu4;
  int i3;
  uint32_t stale_ECX;
  int saved_EBX;
  int j;
  int i7;
  unsigned char frame[0x130] __attribute__((aligned(16)));
#define stk_124 (*(int *)(frame + 0xc))
#define stk_120 (*(int *)(frame + 0x10))
#define keyname (*(char (*)[268])(frame + 0x14))
  
  pi1 = g;
  slct = (int)(g + G_FILES_SELECT);
  pu4 = (uint32_t *)(g + G_FADEIN_TIME);
  g[0x18ed] = 0x3f800000;
  pi1[0x18ec] = 0x3f800000;
  pi1[0x1953] = 4;
  TPGetValueInt(tp,"fadein.time",pu4);
  TPGetValueInt(tp,"fadeout.time",(uint32_t *)(slct + 0x1004));
  i3 = slct;
  if (*(int *)(slct + 0x1000) < 1) {
    *(uint32_t *)(slct + 0x1000) = 1;
  }
  if (*(int *)(i3 + 0x1004) < 1) {
    *(uint32_t *)(i3 + 0x1004) = 1;
    i3 = slct;
  }
  TPGetValueInt(tp,"rows",(uint32_t *)(i3 + 0x1010));
  TPGetValueInt(tp,"columns",(uint32_t *)(slct + 0x1014));
  TPGetValueInt(tp,"wrapping",(uint32_t *)(slct + 0x1024));
  TPScanf(tp,"pos","%i,%i",slct + 0x1008,slct + 0x100c);
  TPGetValueInt(tp,"showemptyboxes",(uint32_t *)(slct + 0x1028));
  TPGetValueInt(tp,"moveoveremptyboxes",(uint32_t *)(slct + 0x102c));
  TPScanf(tp,"p1.cursor.startcell","%i,%i",slct + 0x1040,slct + 0x1048);
  TPScanf(tp,"p2.cursor.startcell","%i,%i",slct + 0x1044,slct + 0x104c);
  TPGetValueInt(tp,"p2.cursor.blink",(uint32_t *)(slct + 0x1090));
  TPScanf(tp,"cell.size","%i,%i",slct + 0x101c,slct + 0x1020);
  TPGetValueInt(tp,"cell.spacing",(uint32_t *)(slct + 0x1018));
  TPScanf(tp,"portrait.scale","%f,%f",slct + 0x1030,slct + 0x1034);
  TPScanf(tp,"portrait.offset","%i,%i",slct + 0x1038,slct + 0x103c);
  TPScanf(tp,"title.offset","%i,%i",slct + 0x10e0,slct + 0x10e4);
  TPScanf(tp,"title.font","%i,%i,%i",slct + 0x10e8,slct + 0x10ec,slct + 0x10f0);
  ParseSndGI(tp,"p1.cursor.move.snd",(uint32_t *)(slct + 0x1094),slct + 0x109c);
  ParseSndGI(tp,"p2.cursor.move.snd",(uint32_t *)(slct + 0x1098),slct + 0x10a0);
  ParseSndGI(tp,"p1.cursor.done.snd",(uint32_t *)(slct + 0x10a4),slct + 0x10ac);
  ParseSndGI(tp,"p2.cursor.done.snd",(uint32_t *)(slct + 0x10a8),slct + 0x10b0);
  ParseSndGI(tp,"p1.random.move.snd",(uint32_t *)(slct + 0x10b4),slct + 0x10bc);
  ParseSndGI(tp,"p2.random.move.snd",(uint32_t *)(slct + 0x10b8),slct + 0x10c0);
  TPGetValueInt(tp,"random.move.snd.cancel",(uint32_t *)(slct + 0x10c4));
  ParseSndGI(tp,"stage.move.snd",(uint32_t *)(slct + 0x10c8),slct + 0x10cc);
  ParseSndGI(tp,"stage.done.snd",(uint32_t *)(slct + 0x10d0),slct + 0x10d4);
  ParseSndGI(tp,"cancel.snd",(uint32_t *)(slct + 0x10d8),slct + 0x10dc);
  SysExplodParse(tp,(int *)(slct + 0x10f4),"cell.bg");
  SysExplodParse(tp,(int *)(slct + 0x1160),"cell.random");
  TPGetValueInt(tp,"cell.random.switchtime",(uint32_t *)(slct + 0x11cc));
  if (*(int *)(slct + 0x11cc) < 1) {
    *(uint32_t *)(slct + 0x11cc) = 1;
  }
  i3 = 0;
  j = 0;
  do {
    i3 = i3 + 1;
    sprintf(keyname,"p%i.cursor.active",i3,saved_EBX);
    SysExplodParse(tp,(int *)(j + slct + 0x11d0),keyname);
    sprintf(keyname,"p%i.cursor.done",i3);
    SysExplodParse(tp,(int *)(j + slct + 0x12a8),keyname);
    saved_EBX = i3;
    j = j + 0x6c;
  } while (i3 < 2);
  i3 = 0;
  stk_120 = 0x13a0;
  stk_124 = 0x13b0;
  j = 0;
  do {
    i7 = slct;
    *(uint32_t *)(stk_124 + 8 + slct) = 0xffffffff;
    *(uint32_t *)(stk_124 + 4 + i7) = 0x3f800000;
    *(uint32_t *)(stk_120 + 0x10 + i7) = 0x3f800000;
    *(uint32_t *)(stk_120 + 0xc + i7) = (uint32_t)(i3 == 0) * 2 + -1;
    i3 = i3 + 1;
    sprintf(keyname,"p%i.face.offset",i3,stk_120);
    TPScanf(tp,keyname,"%i,%i",j + slct + 0x13a4,j + slct + 0x13a8);
    sprintf(keyname,"p%i.face.scale",i3);
    TPScanf(tp,keyname,"%f,%f",j + slct + 0x13b0,j + slct + 0x13b4);
    sprintf(keyname,"p%i.face.facing",i3);
    TPScanf(tp,keyname,"%i",j + slct + 0x13ac);
    sprintf(keyname,"p%i.name.offset",i3);
    TPScanf(tp,keyname,"%i,%i",j + slct + 0x13c4,j + slct + 0x13c8);
    sprintf(keyname,"p%i.name.font",i3);
    i2 = j + slct;
    j = j + 0x28;
    i7 = i2 + 0x13c0;
    TPScanf(tp,keyname,"%i,%i,%i",i2 + 0x13b8,i2 + 0x13bc,i7);
    stk_120 = stk_120 + 0x28;
    stk_124 = stk_124 + 0x28;
  } while (i3 < 2);
  i2 = 0;
  TPScanf(tp,"stage.pos","%i,%i",slct + 0x1380,slct + 0x1384,i7);
  TPScanf(tp,"stage.active.font","%i,%i,%i",slct + 5000,slct + 0x1394,slct + 0x13a0);
  TPScanf(tp,"stage.active2.font","%i,%i",slct + 0x138c,slct + 0x1398);
  TPScanf(tp,"stage.done.font","%i,%i",slct + 0x1390,slct + 0x139c);
  TPGetValueInt(tp,"teammenu.move.wrapping",(uint32_t *)(slct + 0x13f4));
  j = 0;
  do {
    j = j + 1;
    sprintf(keyname,"p%i.teammenu.pos",j,i3);
    TPScanf(tp,keyname,"%i,%i",i2 + slct + 0x13f8,i2 + slct + 0x13fc);
    sprintf(keyname,"p%i.teammenu.bg",j);
    SysExplodParse(tp,(int *)(i2 + slct + 0x1400),keyname);
    sprintf(keyname,"p%i.teammenu.selftitle",j);
    SysExplodParse(tp,(int *)(i2 + slct + 0x146c),keyname);
    sprintf(keyname,"p%i.teammenu.enemytitle",j);
    SysExplodParse(tp,(int *)(i2 + slct + 0x14d8),keyname);
    sprintf(keyname,"p%i.teammenu.move.snd",j);
    ParseSndGI(tp,keyname,(uint32_t *)(i2 + slct + 0x1544),i2 + slct + 0x1548);
    sprintf(keyname,"p%i.teammenu.value.snd",j);
    ParseSndGI(tp,keyname,(uint32_t *)(i2 + slct + 0x154c),i2 + slct + 0x1550);
    sprintf(keyname,"p%i.teammenu.done.snd",j);
    ParseSndGI(tp,keyname,(uint32_t *)(i2 + slct + 0x1554),i2 + slct + 0x1558);
    sprintf(keyname,"p%i.teammenu.item.font",j);
    i3 = i2 + slct;
    TPScanf(tp,keyname,"%i,%i,%i",i3 + 0x1564,i3 + 0x1570,i3 + 0x157c);
    sprintf(keyname,"p%i.teammenu.item.active.font",j);
    TPScanf(tp,keyname,"%i,%i",i2 + slct + 0x1568,i2 + slct + 0x1574);
    sprintf(keyname,"p%i.teammenu.item.active2.font",j);
    TPScanf(tp,keyname,"%i,%i",i2 + slct + 0x156c,i2 + slct + 0x1578);
    sprintf(keyname,"p%i.teammenu.item.offset",j);
    TPScanf(tp,keyname,"%i,%i",i2 + slct + 0x155c,i2 + slct + 0x1560);
    sprintf(keyname,"p%i.teammenu.item.spacing",j);
    TPScanf(tp,keyname,"%i,%i",i2 + slct + 0x1580,i2 + slct + 0x1584);
    sprintf(keyname,"p%i.teammenu.item.cursor",j);
    SysExplodParse(tp,(int *)(i2 + slct + 0x1588),keyname);
    sprintf(keyname,"p%i.teammenu.value.icon",j);
    SysExplodParse(tp,(int *)(i2 + slct + 0x15f4),keyname);
    sprintf(keyname,"p%i.teammenu.value.empty.icon",j);
    SysExplodParse(tp,(int *)(i2 + slct + 0x1668),keyname);
    sprintf(keyname,"p%i.teammenu.value.spacing",j);
    i3 = i2 + slct;
    i2 = i2 + 0x2e4;
    TPScanf(tp,keyname,"%i,%i",i3 + 0x1660,i3 + 0x1664);
    i3 = j;
  } while (j < 2);
  pv3 = calloc(*(int *)(slct + 0x1014) * *(int *)(slct + 0x1010),0x2038);
  *(void **)(slct + 0x19c0) = pv3;
  if (pv3 == (void *)0x0) {
    sprintf((char *)(g + G_ERRMSG),"Out of memory",stale_ECX,stale_ECX);
  }
  return pv3 != (void *)0x0;
}
#undef stk_124
#undef stk_120
#undef keyname

/* VersusScreen @ 0x0808af70, 2673 bytes
 *
 * Shows the versus screen: both teams' big portraits and names for the
 * configured time while the loader precaches the fighters. A key skips it.
 *
 * Globals read: backbuffer, debug_display, demo_mode, debuginfo,
 *               clipboard, speed_flag, vretrace
 * Calls: PrecacheRequestTeam, PrecacheStart, TimerSetSyncFPS,
 *        KBBufferClear, PadPoll, PadBufClear, UInpRefreshFlags,
 *        UInpBufClear, V_SetBuf, W_Cls, BGArrayReset, BGMLoadAndStart,
 *        ErrorExit, FrameSkipReset, BGMPoll, KBPoll, KBkbhit, KBgetchraw,
 *        PadHit, PadGet, GlobalInputUpdate, UInpHit, UInpGet,
 *        KBIMenuGetKey, ...
 * C library: makecol
 * Called by: MainLoop
 *
 * Elecbyte file: src/mugen/charsel.c
 * Note: 3 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: 3 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 * Note: Locals live in `frame`, laid out as on the original stack (0xf0 bytes,
 *       22 variables), because their address is taken.
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t VersusScreen(void)

{
  bool b1;
  int *pi2;
  uint32_t u3;
  uint32_t stale_var;
  uint32_t stale_var_00;
  uint32_t stale_var_01;
  int index;
  int i2;
  int i6;
  int *pi7;
  int *pi8;
  uint32_t u9;
  int i10;
  int *pi11;
  int *pi12;
  int *pi13;
  int i14;
  bool b15;
  float80 f16;
  unsigned char frame[0xf0] __attribute__((aligned(16)));
#define stk_f0 (*(int *)(frame + 0x0))
#define stk_d4 (*(int **)(frame + 0x1c))
#define stk_d0 (*(uint8_t **)(frame + 0x20))
#define stk_bc (*(int *)(frame + 0x34))
#define stk_b8 (*(int *)(frame + 0x38))
#define stk_b4 (*(int *)(frame + 0x3c))
#define stk_b0 (*(int *)(frame + 0x40))
#define stk_ac (*(int *)(frame + 0x44))
#define stk_a8 (*(int *)(frame + 0x48))
#define stk_a4 (*(int *)(frame + 0x4c))
#define stk_a0 (*(int *)(frame + 0x50))
#define stk_74 (*(int *)(frame + 0x7c))
#define stk_70 (*(int *)(frame + 0x80))
#define stk_6c (*(int *)(frame + 0x84))
#define stk_68 (*(int *)(frame + 0x88))
#define stk_60 (*(uint32_t *)(frame + 0x90))
#define stk_58 (*(int *)(frame + 0x98))
#define stk_54 (*(uint32_t (*)[2])(frame + 0x9c))
#define stk_4c (*(uint32_t *)(frame + 0xa4))
#define stk_48 (*(uint32_t *)(frame + 0xa8))
#define stk_44 (*(int (*)[10])(frame + 0xac))
#define stk_1c (*(uint8_t (*)[12])(frame + 0xd4))
  
  pi2 = g;
  b1 = false;
  stk_60 = 0;
  pi12 = stk_44 + 2;
  for (i2 = 6; i2 != 0; i2 = i2 + -1) {
    *pi12 = 0;
    pi12 = pi12 + 1;
  }
  stk_6c = 0;
  pi12 = g + 0x3395;
  stk_70 = -1;
  if (g[0x14d0] != 0) {
    stk_58 = 0;
    do {
      i2 = stk_58 + 1;
      PrecacheRequestTeam((int)(g + stk_58 * 0x6a7 + 0x33bb));
      b15 = stk_58 == 0;
      stk_58 = i2;
    } while (b15 || i2 < 1);
    PrecacheStart();
  }
  i2 = 0;
  do {
    stk_44[i2] = (int)(g + i2 * 0xd + 0x733b);
    i2 = i2 + 1;
  } while (i2 < 2);
  TimerSetSyncFPS(0x3c);
  KBBufferClear();
  PadPoll();
  PadBufClear();
  UInpRefreshFlags();
  UInpBufClear();
  V_SetBuf((int *)g[G_BACKBUFFER],0);
  W_Cls(0);
  BGArrayReset(g[0x62cd]);
  i2 = BGMLoadAndStart(g + 0x6efa,(uint8_t *)(g + 0x66d2),g[0x6ad2],0);
  if (i2 == 0) {
    ErrorExit();
  }
  pi8 = cellHead;
  pi7 = g;
  stk_d0 = stk_1c;
  stk_d4 = g + 0x33bf;
  stk_58 = 0;
  pi13 = g + 0x33bb;
  do {
    i2 = 0;
    if (0 < pi13[2]) {
      pi11 = (int *)(stk_d0 + -0x20);
      i10 = 0;
      do {
        if (*(int *)(i10 + (int)stk_d4) == -1) {
          *pi11 = 0;
        }
        else {
          *pi11 = (int)(pi8 + *(int *)(pi7[0x14b4] + 0x500c +
                                            *(int *)(i10 + (int)stk_d4) * 0x702c) * 0x80e);
        }
        i2 = i2 + 1;
        pi11 = pi11 + 1;
        i10 = i10 + 0x14;
      } while (i2 < pi13[2]);
    }
    stk_58 = stk_58 + 1;
    stk_d4 = stk_d4 + 0x6a7;
    stk_d0 = stk_d0 + 0xc;
    pi13 = pi13 + 0x6a7;
  } while (stk_58 < 2);
  FrameSkipReset();
  stk_68 = 0;
  stk_74 = *pi12;
  do {
    i2 = 0;
    BGMPoll(g + 0x6efa);
    stk_4c = 0;
    stk_48 = 0;
    PadPoll();
    KBPoll();
    b15 = KBkbhit();
    if (ZEXT8(b15) != 0) {
      stk_4c = KBgetchraw();
    }
    b15 = PadHit();
    if (ZEXT8(b15) != 0) {
      stk_48 = PadGet();
    }
    GlobalInputUpdate();
    b15 = UInpHit();
    if (ZEXT8(b15) != 0) {
      i2 = UInpGet();
    }
    KBIMenuGetKey(stk_54,i2,(int)stk_44,2);
    u3 = stk_54[0];
    PRSprArrayClear((int *)g[0x413d]);
    BGArrayMove((int *)g[0x62cd],0.0,0.0);
    BGArrayUpdate(g[0x62cd]);
    if (b1) {
      FrameSkipReset();
    }
    i2 = pi2[0x3396];
    if ((0 < i2) && (stk_6c == 0)) {
      i2 = (stk_68 << 8) / i2;
      MasterPalMul(i2,i2,i2);
      i2 = pi2[0x3396];
    }
    if (stk_68 == i2) {
      stk_6c = 1;
    }
    if (stk_6c == 1) {
      if (stk_70 == -1) {
        i2 = pi2[0x3397];
        if (stk_68 == *pi12 - i2) {
          stk_6c = 2;
          stk_70 = stk_68;
        }
      }
      else {
        i2 = pi2[0x3397];
      }
    }
    else {
      i2 = pi2[0x3397];
    }
    if ((0 < i2) && (stk_6c == 2)) {
      u9 = 0x100 - ((stk_68 - stk_70) * 0x100) / i2;
      u9 = u9 & 0xffffffffU - ((int)u9 >> 0x1f);
      MasterPalMul(u9,u9,u9);
    }
    if (g[0x7306] == 0) {
      i10 = 0x20;
      MasterPalProcessChanges();
      i14 = 0;
      i2 = 0;
      BGArrayDrawLayer(g[0x62cd],0);
      stk_b8 = 0x10;
      stk_bc = 0x10;
      stk_58 = 1;
      pi7 = g;
      do {
        index = *(int *)(i2 + 0xcef4 + (int)pi7);
        if (index == 1) {
          index = *(int *)((int)stk_44 + i14 + 8);
          if (((index != 0) && (*(int *)(index + 0x2034) != 0)) &&
             (index = SpriteArrayGetNum(*(int **)(index + 0x2034),9000,1), pi7 = g, index != -1))
          {
            f16 = *(float *)((int)pi2 + i10 + 0xce64);
            i6 = stk_bc;
            goto L_0808b4e4;
          }
        }
        else if (((index == 2) && (index = *(int *)((int)stk_44 + i14 + 8), index != 0)) &&
                ((*(int *)(index + 0x2034) != 0 &&
                 (index = SpriteArrayGetNum(*(int **)(index + 0x2034),9000,1), pi7 = g,
                 index != -1)))) {
          f16 = *(float *)((int)pi2 + i10 + 0xce64);
          i6 = stk_b8;
L_0808b4e4:
          W_ScaleSprite_S(*(int **)(*(int *)((int)stk_44 + i14 + 8) + 0x2034),index,
                          (float80)*(int *)((int)pi2 + i10 + 0xce40),
                          (float80)*(int *)((int)pi2 + i10 + 0xce44),
                          (float80)*(int *)(i6 + 0x18 + (int)pi12) *
                          *(float *)((int)pi2 + i10 + 0xce60),f16);
          pi7 = g;
        }
        stk_b8 = stk_b8 + 0x28;
        stk_bc = stk_bc + 0x28;
        i10 = i10 + 0x28;
        i14 = i14 + 0xc;
        i2 = i2 + 0x1a9c;
        stk_58 = stk_58 + -1;
      } while (-1 < stk_58);
      stk_58 = 0;
      stk_a4 = 0x10;
      stk_a8 = 0;
      stk_ac = 0;
      stk_b0 = 0;
      stk_b4 = 0;
      do {
        i2 = *(int *)((int)pi7 + stk_b0 + 0xcef4);
        pi8 = pi7;
        if (i2 == 1) {
          i2 = *(int *)((int)pi2 + stk_a8 + 0xce68);
          if ((i2 != -1) && (i10 = *(int *)((int)stk_44 + stk_ac + 8), i10 != 0)) {
            V_FontDrawAlignBank((char *)(i10 + 4),(int *)pi7[i2 + 0x62c3],
                                *(int *)(stk_a4 + 0x10 + (int)pi12),
                                *(int *)((int)pi2 + stk_a4 + 0xce68),
                                *(int *)(stk_a4 + 0xc + (int)pi12),
                                *(int *)(stk_a8 + 0x18 + (int)pi12));
            pi8 = g;
          }
        }
        else if (i2 == 2) {
          i10 = stk_b4 << 2;
          i2 = 0;
          stk_a0 = 0;
          stk_f0 = 2;
          do {
            i14 = *(int *)((int)pi2 + stk_a8 + 0xce68);
            if ((i14 != -1) && (index = *(int *)((int)stk_44 + i10 + 8), index != 0)) {
              V_FontDrawAlignBank((char *)(index + 4),(int *)pi8[i14 + 0x62c3],
                                  *(int *)(stk_a4 + 0x10 + (int)pi12),
                                  stk_a0 + *(int *)((int)pi2 + stk_a4 + 0xce68),
                                  *(int *)(stk_a4 + 0xc + (int)pi12),
                                  *(int *)(stk_a8 + 0x18 + (int)pi12));
              stk_f0 = *(int *)((int)pi7 + stk_b0 + 0xcef4);
              pi8 = g;
            }
            i2 = i2 + 1;
            stk_a0 = stk_a0 + 0xe;
            i10 = i10 + 4;
          } while (i2 < stk_f0);
        }
        stk_58 = stk_58 + 1;
        stk_a4 = stk_a4 + 0x28;
        stk_a8 = stk_a8 + 0x28;
        stk_ac = stk_ac + 0xc;
        stk_b0 = stk_b0 + 0x1a9c;
        stk_b4 = stk_b4 + 3;
        pi7 = pi8;
      } while (stk_58 < 2);
      BGArrayDrawLayer(pi8[0x62cd],1);
    }
    if ((g[G_DEBUG_DISPLAY] != 0) && ((g[G_DEMO_MODE] == 0 || (g[G_DEBUGINFO] != 0)))) {
      u9 = makecol(0xff,0xff,0xff);
      FontDrawClipboard((int *)g[G_CLIPBOARD],(int *)g[0x413a],10,0x32,u9);
    }
    if (stk_4c == 0x58) {
      ScreenSnap();
    }
    if (g[G_SPEED_FLAG] == 0) {
      TimerWaitSync();
    }
    if ((g[0x7306] == 0) && (g[G_VRETRACE] != 0)) {
      VRetrace();
    }
    DrawToScreen();
    if (g[0x7307] == 0) {
      MasterPalFinishedDraw();
    }
    FrameSkipUpdate();
    stk_68 = stk_68 + 1;
    if (b1) {
      FrameSkipReset();
      BGMFree(g + 0x6efa);
      KBBufferClear();
      PadPoll();
      PadBufClear();
      UInpRefreshFlags();
      UInpBufClear();
      PrecacheFinish();
      MasterPalReset();
      return stk_60 ^ 1;
    }
    if (stk_74 < stk_68) {
      b1 = true;
    }
    if (((u3 & 0xff0) != 0) && (stk_6c == 1)) {
      stk_6c = 2;
      stk_74 = stk_68 + pi2[0x3397];
      stk_70 = stk_68;
    }
    if ((stk_4c == 1) && (stk_60 == 0)) {
      stk_60 = 1;
      b1 = true;
      PrecacheRequestCancel();
    }
    if (((g[G_DEMO_MODE] != 0) && (stk_60 == 0)) &&
       (((stk_4c != 0 && ((stk_4c & 0x100) == 0)) ||
        ((stk_48 != 0 && ((stk_48 & 0x100) == 0)))))) {
      stk_60 = 1;
      b1 = true;
      PrecacheRequestCancel();
    }
  } while( true );
}
#undef stk_f0
#undef stk_d4
#undef stk_d0
#undef stk_bc
#undef stk_b8
#undef stk_b4
#undef stk_b0
#undef stk_ac
#undef stk_a8
#undef stk_a4
#undef stk_a0
#undef stk_74
#undef stk_70
#undef stk_6c
#undef stk_68
#undef stk_60
#undef stk_58
#undef stk_54
#undef stk_4c
#undef stk_48
#undef stk_44
#undef stk_1c

/* ArcadeListBuild @ 0x0808b9f0, 107 bytes
 *
 * Builds the arcade opponent order (ArcadeListBuildSet), using each
 * character's "order" value and the maximum number of matches.
 *
 * Calls: ArcadeListBuildSet
 * Called by: MainLoop
 *
 * Elecbyte file: src/mugen/charsel.c
 */
uint32_t ArcadeListBuild(void)

{
  uint32_t stale_EAX;
  uint32_t u1;
  int i2;
  int *pi3;
  
  i2 = 2 - g[0x33b3];
  u1 = 0;
  if (g[0x33b3] != 0) {
    pi3 = g + 0x14bc;
    if ((g[i2 * 0x6a7 + 0x33bb] != 0) || (1 < g[i2 * 0x6a7 + 0x33b9])) {
      pi3 = g + 0x14c6;
    }
    ArcadeListBuildSet(g + 0x14b8,g[i2 * 0x6a7 + 0x33ba],(int)pi3);
    u1 = stale_EAX;
  }
  return u1;
}

/* ArcadeListBuildSet @ 0x0808ba60, 796 bytes
 *
 * Fills the arcade order: for each order group in turn, picks random
 * characters (not the player's own) up to arcade.maxmatches (team.maxmatches
 * in team mode).
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *
 * Globals read: num_chars, charinfo
 * C library: calloc, random, free
 * Called by: ArcadeListBuild
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void ArcadeListBuildSet(int *arg1,int arg2,int arg3)

{
  int i1;
  uint32_t u2;
  bool b3;
  int *pi4;
  void *ptr;
  long l5;
  int i6;
  int i7;
  int i2;
  int i9;
  int i10;
  int stk_2c;
  int stk_20;
  
  i2 = 0;
  i1 = g[G_NUM_CHARS];
  stk_2c = 0;
  ptr = calloc(i1 + 1,4);
  if (0 < i1) {
    do {
      *(int *)((int)ptr + i2 * 4) = i2;
      i2 = i2 + 1;
    } while (i2 < i1);
  }
  stk_20 = 4;
  do {
    i2 = 0;
    if (0 < i1) {
      do {
        l5 = random();
        u2 = *(uint32_t *)((int)ptr + i2 * 4);
        *(uint32_t *)((int)ptr + i2 * 4) = *(uint32_t *)((int)ptr + (l5 % i1) * 4);
        *(uint32_t *)((int)ptr + (l5 % i1) * 4) = u2;
        i2 = i2 + 1;
      } while (i2 < i1);
    }
    stk_20 = stk_20 + -1;
  } while (-1 < stk_20);
  i2 = i1;
  if (1 < i1) {
    do {
      b3 = true;
      for (i9 = 0; i10 = i2 + -1, i9 < i10; i9 = i9 + 1) {
        i10 = *(int *)((int)ptr + i9 * 4);
        i6 = *(int *)((int)ptr + i9 * 4 + 4);
        if (*(int *)(g[G_CHARINFO] + 0x5024 + i6 * 0x702c) <
            *(int *)(g[G_CHARINFO] + 0x5024 + i10 * 0x702c)) {
          *(int *)((int)ptr + i9 * 4) = i6;
          *(int *)((int)ptr + i9 * 4 + 4) = i10;
          b3 = false;
        }
      }
    } while ((1 < i10) && (i2 = i10, !b3));
  }
  i2 = 0;
  stk_20 = 0;
  while( true ) {
    pi4 = g;
    i9 = i2;
    if (i2 < i1) {
      i2 = *(int *)(g[G_CHARINFO] + 0x5024 + *(int *)((int)ptr + i2 * 4) * 0x702c);
      while ((i2 < stk_20 && (i9 = i9 + 1, i9 < i1))) {
        i2 = *(int *)(g[G_CHARINFO] + 0x5024 + *(int *)((int)ptr + i9 * 4) * 0x702c);
      }
    }
    if (i1 <= i9) break;
    i10 = 0;
    i2 = i9;
    if (0 < arg2 * *(int *)(arg3 + stk_20 * 4)) {
      i6 = *(int *)((int)ptr + i9 * 4);
      i7 = g[G_CHARINFO];
      while (*(int *)(i7 + 0x5024 + i6 * 0x702c) == stk_20) {
        i10 = i10 + 1;
        i2 = i2 + 1;
        *(int *)(*arg1 + stk_2c * 4) = i6;
        stk_2c = stk_2c + 1;
        if ((arg2 * *(int *)(arg3 + stk_20 * 4) <= i10) || (i1 <= i2)) break;
        i6 = *(int *)((int)ptr + i2 * 4);
        i7 = pi4[0x14b4];
      }
    }
    if ((i10 % arg2 != 0) && (i2 != i9)) {
      do {
        i10 = i10 + 1;
        l5 = random();
        *(uint32_t *)(*arg1 + stk_2c * 4) =
             *(uint32_t *)((int)ptr + (i9 + l5 % (i2 - i9)) * 4);
        stk_2c = stk_2c + 1;
        if (i10 % arg2 == 0) break;
      } while (i2 != i9);
    }
    if ((i1 <= i2) || (stk_20 = stk_20 + 1, 9 < stk_20)) break;
  }
  *(uint32_t *)(*arg1 + stk_2c * 4) = 0xffffffff;
  arg1[1] = stk_2c;
  arg1[2] = 0;
  arg1[3] = 0;
  free(ptr);
  return;
}

/* ArcadeListGetCurrent @ 0x0808bd80, 14 bytes
 *
 * Returns the current arcade opponent team (ArcadeListGet).
 *
 * Calls: ArcadeListGet
 * Called by: MainLoop
 *
 * Elecbyte file: src/mugen/charsel.c
 */
int ArcadeListGetCurrent(void)

{
  int i1;
  
  i1 = ArcadeListGet(0);
  return i1;
}

/* ArcadeListGet @ 0x0808bd90, 480 bytes
 *
 * Fills the opponent team for the current arcade match from the order,
 * reserving palettes (a random colour if arcade.ai.randomcolor is set, else
 * the first free one).
 *
 * Parameters:
 *   arg1         int
 *
 * Globals read: arcade_ai_randomcolor, charinfo
 * Calls: CharStopUsingPal, CharReservePal
 * C library: random
 * Called by: ArcadeListGetCurrent
 *
 * Elecbyte file: src/mugen/charsel.c
 */
int ArcadeListGet(int arg1)

{
  int *pi1;
  int *pi2;
  int i3;
  long l4;
  uint32_t u5;
  int i6;
  int i7;
  int *pi8;
  int pal;
  int i10;
  int *stk_34;
  int *stk_30;
  int *stk_2c;
  int stk_28;
  int stk_24;
  int stk_20;
  int stk_1c;
  
  pi2 = g;
  pal = -1;
  pi1 = g + 0x14b8;
  stk_24 = g[0x14ba];
  i6 = 2 - g[0x33b3];
  stk_20 = 0;
  if (0 < g[i6 * 0x6a7 + 0x33b9]) {
    stk_2c = g + i6 * 0x6a7 + 0x33be;
    stk_34 = g + i6 * 0x6a7 + 0x33bf;
    pi8 = g + i6 * 0x6a7 + 0x33c0;
    stk_30 = stk_34;
    do {
      stk_1c = 0;
      i7 = pi8[-3];
      if (0 < i7) {
        stk_28 = 0x10;
        i10 = 0;
        do {
          i3 = *pi1;
          if (*(int *)(i3 + stk_24 * 4) != -1) {
            if (*(int *)(i10 + (int)pi8) != -1) {
              CharStopUsingPal((uint8_t)*(uint32_t *)(i10 + (int)pi8),
                               *(int *)(i10 + (int)stk_34));
              i3 = *pi1;
            }
            pal = *(int *)(i3 + stk_24 * 4);
            *(int *)(i10 + (int)stk_30) = pal;
            if (g[G_ARCADE_AI_RANDOMCOLOR] == 0) {
              *(int *)(i10 + (int)pi8) = *(int *)(g[G_CHARINFO] + 0x5014 + pal * 0x702c) + -1;
            }
            else {
              l4 = random();
              *(int *)(i10 + (int)pi8) = l4 % 0xc;
            }
            u5 = CharReservePal(*(uint32_t *)(i10 + (int)pi8),pal);
            *(uint32_t *)(i10 + (int)pi8) = u5;
            stk_24 = stk_24 + 1;
            *(uint32_t *)(stk_28 + (int)stk_2c) = 1;
            i7 = pi8[-3];
          }
          stk_1c = stk_1c + 1;
          stk_28 = stk_28 + 0x14;
          i10 = i10 + 0x14;
        } while (stk_1c < i7);
      }
      stk_34 = stk_34 + 0x17;
      stk_20 = stk_20 + 1;
      stk_2c = stk_2c + 0x17;
      stk_30 = stk_30 + 0x17;
      pi8 = pi8 + 0x17;
    } while (stk_20 < pi2[i6 * 0x6a7 + 0x33b9]);
  }
  if (arg1 != 0) {
    pi2[0x14ba] = stk_24;
  }
  return pal;
}

/* ArcadeListGetCurSize @ 0x0808bf70, 120 bytes
 *
 * Returns the size of the current opponent team.
 *
 * Called by: ArcadeListPeek, GamePlay, MainLoop
 *
 * Elecbyte file: src/mugen/charsel.c
 */
int ArcadeListGetCurSize(void)

{
  int i1;
  int i2;
  int i3;
  int *pi4;
  int i5;
  
  i5 = 0;
  i3 = g[0x14ba];
  i1 = g[(2 - g[0x33b3]) * 0x6a7 + 0x33b9];
  if (0 < i1) {
    pi4 = g + (2 - g[0x33b3]) * 0x6a7 + 0x33bd;
    do {
      i2 = *pi4;
      if (0 < i2) {
        do {
          if (*(int *)(g[0x14b8] + i3 * 4) != -1) {
            i3 = i3 + 1;
            i5 = i5 + 1;
          }
          i2 = i2 + -1;
        } while (i2 != 0);
      }
      pi4 = pi4 + 0x17;
      i1 = i1 + -1;
    } while (i1 != 0);
  }
  return i5;
}

/* ArcadeListPeekCur @ 0x0808bff0, 19 bytes
 *
 * Returns the characters of the current opponent team without reserving
 * them. Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: ArcadeListPeek
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void ArcadeListPeekCur(int arg1)

{
  ArcadeListPeek(arg1,0);
  return;
}

/* ArcadeListPeekNext @ 0x0808c010, 19 bytes
 *
 * Returns the characters of the next opponent team without reserving them.
 * Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: ArcadeListPeek
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void ArcadeListPeekNext(int arg1)

{
  ArcadeListPeek(arg1,1);
  return;
}

/* ArcadeListPeek @ 0x0808c030, 201 bytes
 *
 * Returns the characters of the opponent team at offset `n` from the current
 * position.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Calls: ArcadeListGetCurSize
 * Called by: ArcadeListPeekCur, ArcadeListPeekNext,
 *            PrecacheRequestArcadeTeam
 *
 * Elecbyte file: src/mugen/charsel.c
 */
int ArcadeListPeek(int arg1,int arg2)

{
  int *pi1;
  int i2;
  int i3;
  int *pi4;
  int i5;
  int *pi6;
  int i7;
  int i4;
  int i9;
  int i10;
  int stk_1c;
  
  pi4 = g;
  i9 = 0;
  pi1 = g + 0x14b8;
  i10 = g[0x14ba];
  i7 = 2 - g[0x33b3];
  if (arg2 != 0) {
    i5 = ArcadeListGetCurSize();
    i10 = i10 + i5;
  }
  if (i10 < pi4[0x14b9]) {
    stk_1c = 0;
    if (0 < pi4[i7 * 0x6a7 + 0x33b9]) {
      pi6 = pi4 + i7 * 0x6a7 + 0x33bb;
      do {
        i4 = 0;
        i5 = pi6[2];
        if (0 < i5) {
          i2 = *pi1;
          do {
            i3 = *(int *)(i2 + i10 * 4);
            if (i3 != -1) {
              i10 = i10 + 1;
              *(int *)(arg1 + i9 * 4) = i3;
              i9 = i9 + 1;
              i5 = pi6[2];
            }
            i4 = i4 + 1;
          } while (i4 < i5);
        }
        stk_1c = stk_1c + 1;
        pi6 = pi6 + 0x17;
      } while (stk_1c < pi4[i7 * 0x6a7 + 0x33b9]);
    }
  }
  else {
    i9 = 0;
  }
  return i9;
}

/* ArcadeListEnemiesLeft @ 0x0808c100, 21 bytes
 *
 * Returns how many arcade opponents remain.
 *
 * Called by: GamePlay, MainLoop
 *
 * Elecbyte file: src/mugen/charsel.c
 */
int ArcadeListEnemiesLeft(void)

{
  return g[0x14b9] - g[0x14ba];
}

/* SurvivalBuildRandomTeam @ 0x0808c120, 610 bytes
 *
 * Builds a random opponent team for survival mode (and the random partner in
 * co-op), reserving palettes.
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         int
 *   arg3         int
 *
 * Globals read: num_chars
 * Calls: CharStopUsingPal, ResetPersistVar, CharReservePal
 * C library: random
 * Called by: GameNextRound, MainLoop
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void SurvivalBuildRandomTeam(uint32_t *arg1,int arg2,int arg3)

{
  int i1;
  int *pi2;
  long l3;
  uint32_t u4;
  int i5;
  uint32_t *pu6;
  int pal;
  uint32_t *pu8;
  uint32_t *pu9;
  uint32_t *stk_28;
  uint32_t *stk_24;
  int stk_20;
  uint32_t stk_18;
  int stk_14;
  
  i1 = arg1[5];
  arg1[1] = 2;
  *arg1 = 0;
  arg1[2] = i1 * 2;
  if (arg3 == 0) {
    stk_14 = 0;
    i5 = arg1[5];
    if (0 < i5) {
      pal = 0;
      do {
        if (*(int *)((int)arg1 + pal + 0x20) != -1) {
          CharStopUsingPal((uint8_t)*(uint32_t *)((int)arg1 + pal + 0x20),
                           *(int *)((int)arg1 + pal + 0x1c));
          i5 = arg1[5];
        }
        pal = pal + 0x14;
        stk_14 = stk_14 + 1;
      } while (stk_14 < i5);
    }
    pu6 = arg1 + 0x1ef;
    pu8 = arg1 + 0x1a;
    pu9 = arg1 + 3;
    for (i5 = 0x17; i5 != 0; i5 = i5 + -1) {
      *pu9 = *pu8;
      pu8 = pu8 + 1;
      pu9 = pu9 + 1;
    }
    pu8 = arg1 + 0x1ef;
    pu9 = arg1 + 0x5f;
    for (i5 = 400; i5 != 0; i5 = i5 + -1) {
      *pu9 = *pu8;
      pu8 = pu8 + 1;
      pu9 = pu9 + 1;
    }
    stk_14 = 3;
    do {
      ResetPersistVar(pu6);
      pu6 = pu6 + 100;
      stk_14 = stk_14 + -1;
    } while (-1 < stk_14);
  }
  stk_18 = (uint32_t)(arg3 == 0);
  if (stk_18 == 1 || arg3 != 0) {
    stk_24 = arg1 + stk_18 * 0x17 + 7;
    stk_28 = arg1 + stk_18 * 0x17 + 9;
    pu6 = arg1 + stk_18 * 0x17 + 8;
    pu8 = arg1 + stk_18 * 0x17 + 3;
    do {
      if ((arg3 != 0) || (stk_18 == 1)) {
        pu6[5] = 0xffffffff;
        *pu6 = 0xffffffff;
        pu6[4] = 0xffffffff;
        pu6[-1] = 0xffffffff;
      }
      pu6[-5] = (uint32_t)(i1 != 1);
      if (i1 == 2) {
        pu6[-4] = 2;
      }
      pu6[-3] = i1;
      if (0 < i1) {
        i5 = 0;
        stk_20 = arg2 + 1;
        stk_14 = i1;
        do {
          *(int *)(i5 + (int)stk_28) = arg2;
          *(int *)((int)pu8 + i5 + 0xc) = stk_20;
          l3 = random();
          pi2 = g;
          pal = l3 % g[G_NUM_CHARS];
          *(int *)(i5 + (int)stk_24) = pal;
          if (pi2[0x757e] == 0) {
            *(int *)((int)pu8 + i5 + 0x14) =
                 *(int *)(pi2[0x14b4] + 0x5014 + pal * 0x702c) + -1;
          }
          else {
            l3 = random();
            *(int *)((int)pu8 + i5 + 0x14) = l3 % 0xc;
          }
          u4 = CharReservePal(*(uint32_t *)((int)pu8 + i5 + 0x14),pal);
          *(uint32_t *)((int)pu8 + i5 + 0x14) = u4;
          *(uint32_t *)((int)pu8 + i5 + 0x1c) = 1;
          i5 = i5 + 0x14;
          stk_20 = stk_20 + 2;
          stk_14 = stk_14 + -1;
        } while (stk_14 != 0);
      }
      stk_18 = stk_18 + 1;
      stk_24 = stk_24 + 0x17;
      stk_28 = stk_28 + 0x17;
      pu6 = pu6 + 0x17;
      pu8 = pu8 + 0x17;
    } while ((int)stk_18 < 2);
  }
  return;
}

/* GetPlayerRowCol @ 0x0808c390, 123 bytes
 *
 * Converts a grid cell index into row and column.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int *
 *   arg3         int *
 *
 * Called by: CharacterSelectScreen
 *
 * Elecbyte file: src/mugen/charsel.c
 */
uint32_t GetPlayerRowCol(int arg1,int *arg2,int *arg3)

{
  int *pi1;
  int i2;
  
  i2 = 0;
  pi1 = cellHead;
  if (0 < cellCols * cellRows) {
    do {
      if (arg1 == *pi1) {
        *arg2 = i2 % cellCols;
        *arg3 = i2 / cellCols;
        return 1;
      }
      i2 = i2 + 1;
      pi1 = pi1 + 0x80e;
    } while (i2 < cellCols * cellRows);
  }
  return 0;
}

/* SlctStateListChanged @ 0x0808c410, 21 bytes
 *
 * Returns true if a select state list changed since the last check.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: CharacterSelectScreen
 *
 * Elecbyte file: src/mugen/charsel.c
 */
uint32_t SlctStateListChanged(int arg1)

{
  uint32_t u1;
  
  u1 = *(uint32_t *)(arg1 + 0x198);
  *(uint32_t *)(arg1 + 0x198) = 0;
  return u1;
}

/* SlctStateListNextItem @ 0x0808c430, 55 bytes
 *
 * Moves a select state list to its next item.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: CharacterSelectScreen
 *
 * Elecbyte file: src/mugen/charsel.c
 */
int SlctStateListNextItem(int arg1)

{
  int i1;
  
  if (*(int *)(arg1 + 400) <= *(int *)(arg1 + 0x194)) {
    return 0;
  }
  i1 = *(int *)(arg1 + 0x194) + 1;
  *(int *)(arg1 + 0x194) = i1;
  *(uint32_t *)(arg1 + 0x198) = 1;
  *(uint32_t *)(arg1 + 0x19c) = 0;
  return arg1 + i1 * 0x28;
}

/* SlctStateListUpdate @ 0x0808c470, 18 bytes
 *
 * Marks a select state list as seen.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: CharacterSelectScreen
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void SlctStateListUpdate(int arg1)

{
  *(int *)(arg1 + 0x19c) = *(int *)(arg1 + 0x19c) + 1;
  return;
}

/* BuildSlctCtrl @ 0x0808c490, 410 bytes
 *
 * Sets up who controls each side of the select screen for the mode (player,
 * computer, demo), restoring cursor positions.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *
 * Globals read: stresstest, demo_mode
 * Calls: CharselRestoreCursor
 * C library: random
 * Called by: CharacterSelectScreen
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void BuildSlctCtrl(int arg1,int arg2,int arg3)

{
  int i1;
  uint32_t u2;
  bool b3;
  int *pi4;
  long l5;
  int i2;
  int i7;
  
  b3 = false;
  if ((g[G_STRESSTEST] != 0) || (g[G_DEMO_MODE] != 0)) {
    b3 = true;
  }
  i1 = arg1 + arg3 * 0x74;
  *(uint32_t *)(i1 + 0x3890) = *(uint32_t *)(arg2 + 4);
  *(uint32_t *)(i1 + 0x38a4) = 0;
  u2 = *(uint32_t *)(arg2 + 0xc);
  *(int *)(i1 + 0x38b0) = arg2;
  *(uint32_t *)(i1 + 0x38a8) = u2;
  *(uint32_t *)(i1 + 0x38ac) = 0xffffffff;
  if (b3) {
    l5 = random();
    i2 = slct;
    *(int *)(i1 + 0x38ac) = l5 % 0x14 + 0x14;
    *(uint32_t *)(i2 + 0x11cc) = 6;
  }
  pi4 = g;
  i2 = 0;
  if (0 < *(int *)(i1 + 0x38a8)) {
    i7 = 0x20;
    do {
      *(uint32_t *)(i1 + 0x389c + i7) = *(uint32_t *)(arg2 + 4);
      *(uint32_t *)(i1 + 0x3894 + i7) = *(uint32_t *)(i1 + 0x3890);
      *(uint32_t *)(i1 + 0x38a0 + i7) = 0xffffffff;
      *(uint32_t *)(i1 + 0x38a4 + i7) = 0xffffffff;
      if (pi4[0x33ae] == 2) {
        *(uint32_t *)(i7 + i1 + 0x3898) = 1;
      }
      i2 = i2 + 1;
      i7 = i7 + 0x14;
    } while (i2 < *(int *)(i1 + 0x38a8));
  }
  CharselRestoreCursor(arg1,*(int *)(arg2 + 4),arg3);
  *(int *)(i1 + 0x3894) = *(int *)(i1 + 0x38c0);
  if (*(int *)(i1 + 0x38c0) == -1) {
    *(uint32_t *)(i1 + 0x3894) = *(uint32_t *)(slct + 0x1048 + *(int *)(arg2 + 4) * 4);
  }
  *(int *)(i1 + 0x3898) = *(int *)(i1 + 0x38c4);
  if (*(int *)(i1 + 0x38c4) == -1) {
    *(uint32_t *)(i1 + 0x3898) = *(uint32_t *)(slct + 0x1040 + *(int *)(arg2 + 4) * 4);
  }
  *(uint32_t *)(i1 + 0x389c) = *(uint32_t *)(i1 + 0x3894);
  *(uint32_t *)(i1 + 0x38a0) = *(uint32_t *)(i1 + 0x3898);
  if ((*(int *)(arg2 + 8) == 1) && (*(int *)(arg2 + 0xc) == 2)) {
    i2 = *(int *)(arg2 + 0x10);
    if ((i2 == 0) || (i2 == 2)) {
      *(uint32_t *)(i1 + 0x38cc) = 1;
      i2 = *(int *)(arg2 + 0x10);
    }
    if (i2 == 2) {
      *(uint32_t *)(i1 + 0x38b8) = 1;
      i2 = *(int *)(arg2 + 0x10);
    }
    if (i2 == 1) {
      *(int *)(i1 + 0x38d0) = 1 - *(int *)(i1 + 0x38d0);
    }
  }
  return;
}

/* BuildSlctTeamForArcade @ 0x0808c630, 146 bytes
 *
 * Sets up the team selection for arcade modes.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         uint32_t
 *   arg5         int
 *
 * Called by: CharacterSelectScreen
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void BuildSlctTeamForArcade(int arg1,int arg2,int arg3,uint32_t arg4,int arg5)

{
  int i1;
  int i2;
  int i3;
  int i4;
  int i5;
  uint32_t stk_14;
  
  *(int *)(arg1 + 4) = arg3;
  stk_14 = 0;
  if (0 < arg3) {
    i4 = arg1 + 0x20;
    i3 = arg1 + 0xc;
    do {
      *(int *)(i4 + -0xc) = arg5;
      *(uint32_t *)(i4 + -0x14) = arg4;
      if (0 < arg5) {
        i1 = 0;
        i2 = arg2 + 1;
        i5 = 0;
        do {
          *(uint32_t *)(i3 + 0x1c + i1) = 1;
          *(uint32_t *)(i3 + 0x10 + i1) = 0xffffffff;
          *(int *)(i3 + 0xc + i1) = i2;
          *(int *)(i3 + 0x18 + i1) = arg2;
          i5 = i5 + 1;
          *(uint32_t *)(i3 + 0x14 + i1) = 0xffffffff;
          i2 = i2 + 2;
          i1 = i1 + 0x14;
          *(int *)(arg1 + 8) = *(int *)(arg1 + 8) + 1;
        } while (i5 < *(int *)(i4 + -0xc));
      }
      i4 = i4 + 0x5c;
      stk_14 = stk_14 + 1;
      i3 = i3 + 0x5c;
    } while (stk_14 < *(int *)(arg1 + 4));
  }
  return;
}

/* BuildMenuCtrl @ 0x0808c6d0, 460 bytes
 *
 * Sets up the team menus for the mode; "Menu - programmer's fault" for an
 * impossible combination.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *
 * Calls: MenuItemVal, CharselRestoreMenuPos, ErrorExitM
 * Called by: CharacterSelectScreen
 * Messages:
 *   "Menu - programmer\'s fault"
 *
 * Elecbyte file: src/mugen/charsel.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x60 bytes,
 *       12 variables), because their address is taken.
 */
void BuildMenuCtrl(int arg1,int arg2,int arg3)

{
  int i1;
  int i2;
  int i3;
  uint32_t u4;
  uint32_t u5;
  uint32_t u6;
  bool b7;
  unsigned char frame[0x60] __attribute__((aligned(16)));
#define stk_5c (*(uint32_t *)(frame + 0x4))
#define stk_58 (*(uint32_t *)(frame + 0x8))
#define stk_54 (*(uint32_t *)(frame + 0xc))
#define stk_4c (*(uint32_t *)(frame + 0x14))
#define stk_48 (*(uint32_t *)(frame + 0x18))
#define stk_44 (*(uint32_t *)(frame + 0x1c))
#define stk_3c (*(uint32_t *)(frame + 0x24))
#define stk_38 (*(uint32_t *)(frame + 0x28))
#define stk_34 (*(uint32_t *)(frame + 0x2c))
#define stk_2c (*(uint32_t *)(frame + 0x34))
#define stk_28 (*(uint32_t *)(frame + 0x38))
#define stk_24 (*(uint32_t *)(frame + 0x3c))
  
  i2 = arg1 + arg3 * 0xb4;
  *(uint32_t *)(i2 + 0x3aa4) = 1;
  i1 = i2 + 0x3aa4;
  *(uint32_t *)(i2 + 0x3aac) = *(uint32_t *)(arg2 + 0x20);
  i3 = *(int *)(arg2 + 0x14);
  *(int *)(i2 + 0x3aa8) = i3;
  *(uint32_t *)(i2 + 0x3ab0) = *(uint32_t *)(arg2 + 0x1c);
  u4 = *(uint32_t *)(arg2 + 0x18);
  if (i3 == 0) {
    b7 = (u4 & 1) != 0;
    if (b7) {
      *(uint32_t *)(i2 + 0x3ab8) = 0;
      *(char **)(i2 + 0x3abc) = "Single";
      MenuItemVal(&stk_2c,0xffffffff,0,0xffffffff);
      *(uint32_t *)(i2 + 0x3ac0) = stk_2c;
      *(uint32_t *)(i2 + 0x3ac4) = stk_28;
      *(uint32_t *)(i2 + 0x3ac8) = stk_24;
    }
    u6 = (uint32_t)b7;
    u5 = u6;
    if ((u4 & 2) != 0) {
      u5 = u6 + 1;
      i3 = i1 + u6 * 0x14;
      *(uint32_t *)(i3 + 0x14) = 1;
      *(char **)(i3 + 0x18) = "Simul";
      MenuItemVal(&stk_3c,2,2,2);
      *(uint32_t *)(i3 + 0x1c) = stk_3c;
      *(uint32_t *)(i3 + 0x20) = stk_38;
      *(uint32_t *)(i3 + 0x24) = stk_34;
    }
    u6 = u5;
    if ((u4 & 4) != 0) {
      u6 = u5 + 1;
      i3 = i1 + u5 * 0x14;
      *(uint32_t *)(i3 + 0x14) = 2;
      *(uint8_t **)(i3 + 0x18) = &str_tag;
      MenuItemVal(&stk_4c,2,2,2);
      *(uint32_t *)(i3 + 0x1c) = stk_4c;
      *(uint32_t *)(i3 + 0x20) = stk_48;
      *(uint32_t *)(i3 + 0x24) = stk_44;
    }
    u5 = u6;
    if ((u4 & 8) != 0) {
      u5 = u6 + 1;
      i1 = i1 + u6 * 0x14;
      *(uint32_t *)(i1 + 0x14) = 3;
      *(char **)(i1 + 0x18) = "Turns";
      MenuItemVal(&stk_5c,2,2,4);
      *(uint32_t *)(i1 + 0x1c) = stk_5c;
      *(uint32_t *)(i1 + 0x20) = stk_58;
      *(uint32_t *)(i1 + 0x24) = stk_54;
    }
    *(uint32_t *)(i2 + 0x3ab4) = u5;
    CharselRestoreMenuPos(arg1,(int *)(slct + 0x16d4 + *(int *)(i2 + 0x3aac) * 0x2e4),arg3)
    ;
  }
  else {
    ErrorExitM("Menu - programmer\'s fault");
  }
  return;
}
#undef stk_5c
#undef stk_58
#undef stk_54
#undef stk_4c
#undef stk_48
#undef stk_44
#undef stk_3c
#undef stk_38
#undef stk_34
#undef stk_2c
#undef stk_28
#undef stk_24

/* MenuItemVal @ 0x0808c8a0, 51 bytes
 *
 * Returns the value shown for a team menu item.
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         uint32_t
 *   arg3         uint32_t
 *   arg4         uint32_t
 *
 * Called by: BuildMenuCtrl
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void MenuItemVal(uint32_t *arg1,uint32_t arg2,uint32_t arg3,uint32_t arg4)

{
  *arg1 = arg2;
  arg1[1] = arg3;
  arg1[2] = arg4;
  return;
}

/* CharReservePal @ 0x0808c8e0, 200 bytes
 *
 * Reserves palette `pal` of character `charno` (so two players never share a
 * colour); if it is taken, the next free one is used. Returns the palette
 * reserved.
 *
 * Parameters:
 *   charno       uint32_t
 *   pal          int
 *
 * Globals read: charinfo
 * Called by: ArcadeListGet, CharacterSelectScreen, DemoFightSetup,
 *            SurvivalBuildRandomTeam
 *
 * Elecbyte file: src/mugen/charsel.c
 */
uint32_t CharReservePal(uint32_t charno,int pal)

{
  uint32_t u1;
  uint8_t b2;
  int i2;
  
  u1 = *(uint32_t *)(g[G_CHARINFO] + 0x7028 + pal * 0x702c);
  if ((((int)u1 >> ((uint8_t)charno & 0x1f) & 1U) == 0) && (5 < (int)charno)) {
    charno = charno - 6;
  }
  if ((((int)u1 >> ((uint8_t)charno & 0x1f) & 1U) == 0) || (0xb < (int)charno)) {
    i2 = 0;
    do {
      i2 = i2 + 1;
      charno = charno + 1 & (5 < (int)(charno + 1)) - 1;
      if (((int)u1 >> ((uint8_t)charno & 0x1f) & 1U) != 0) break;
    } while (i2 < 6);
    if (5 < i2) {
      do {
        charno = charno + 1;
        if (0xb < (int)charno) {
          charno = 6;
        }
        i2 = i2 + 1;
      } while ((((int)u1 >> ((uint8_t)charno & 0x1f) & 1U) == 0) && (i2 < 0xc));
    }
    charno = charno & (0xb < i2) - 1;
  }
  b2 = (uint8_t)charno & 0x1f;
  *(uint32_t *)(g[G_CHARINFO] + 0x7028 + pal * 0x702c) =
       u1 & (-2 << b2 | 0xfffffffeU >> 0x20 - b2);
  return charno;
}

/* CharStopUsingPal @ 0x0808c9b0, 65 bytes
 *
 * Releases a reserved palette of a character.
 *
 * Parameters:
 *   charno       uint8_t
 *   pal          int
 *
 * Globals read: charinfo
 * Called by: ArcadeListGet, SurvivalBuildRandomTeam
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void CharStopUsingPal(uint8_t charno,int pal)

{
  *(uint32_t *)(g[G_CHARINFO] + 0x7028 + pal * 0x702c) =
       *(uint32_t *)(g[G_CHARINFO] + 0x7028 + pal * 0x702c) | 1 << (charno & 0x1f);
  return;
}

/* CharStopUsingPalAll @ 0x0808ca00, 58 bytes
 *
 * Releases every reserved palette.
 *
 * Globals read: num_chars
 * Called by: CharacterSelectScreen, MainLoop
 *
 * Elecbyte file: src/mugen/charsel.c
 */
void CharStopUsingPalAll(void)

{
  int i1;
  int *pi2;
  int i3;
  int i2;
  
  pi2 = g;
  i2 = 0;
  if (0 < g[G_NUM_CHARS]) {
    i3 = 0;
    do {
      i1 = pi2[0x14b4];
      i2 = i2 + 1;
      *(uint32_t *)(i1 + 0x7028 + i3) = *(uint32_t *)(i1 + 0x5010 + i3);
      i3 = i3 + 0x702c;
    } while (i2 < pi2[0x14b5]);
  }
  return;
}

