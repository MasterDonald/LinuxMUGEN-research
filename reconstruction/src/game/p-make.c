/*
 * p-make.c -- characters and players
 * Loading characters (.def, .cns, .cmd, states) with a cache, creating and
 * freeing player records, teams, persistent variables, state and animation
 * changes, life and power.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/p-make.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"

extern int cachelastfreedtime __asm__("D_08287d20"); /* file-static 0x08287d20 */

/* PlayerCacheLoad @ 0x080ac660, 715 bytes
 *
 * Makes sure character `charno` of the character list is loaded into the
 * cache. If its slot holds another character, that one is freed first
 * (saving its AI learning data: "Cannot save AI info for %s"). Then the .def
 * file is loaded (PlayerDefLoad). Returns the chardef, or NULL ("Error
 * loading %s").
 *
 * Parameters:
 *   charno       int
 *
 * Globals read: charinfo, num_chars, clipboard, errmsg
 * Calls: joindirfile, AILearnDataSave, ClipboardAppend, PlayerRCFree,
 *        PlayerDefLoad
 * C library: sprintf
 * Called by: GameLoadAndCreateChars, PrecacheWorkerThread
 * Messages:
 *   "Cannot save AI info for %s"
 *   "\nError loading %s"
 *
 * Elecbyte file: src/mugen/p-make.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x1030 bytes,
 *       2 variables), because their address is taken.
 */
int PlayerCacheLoad(int charno)

{
  int *pi1;
  int *pi2;
  int i3;
  int *pi4;
  int i5;
  void *pv6;
  uint32_t *pu7;
  uint32_t *pu8;
  int i9;
  uint32_t u10;
  uint32_t u11;
  int i2;
  int i13;
  unsigned char frame[0x1030] __attribute__((aligned(16)));
#define stk_102c (*(int *)(frame + 0x4))
#define stk_101c (*(char (*)[4108])(frame + 0x14))
  
  pi4 = g;
  pi1 = g + G_CHARINFO;
  i3 = g[G_CHARINFO];
  pi2 = (int *)(i3 + charno * 0x702c);
  if (pi2[2] != 0) {
    *pi2 = *pi2 + 1;
    return pi2[2];
  }
  if (g[0x14b6] < g[0x7579]) goto L_080ac840;
  i13 = -1;
  i2 = 0;
  stk_102c = -1;
  if (0 < g[G_NUM_CHARS]) {
    i9 = 0;
    do {
      if ((*(int *)(i3 + i9) == 0) && (*(int *)(i3 + 8 + i9) != 0)) {
        if (i13 == -1) {
          i5 = *(int *)(i3 + 4 + i9);
        }
        else {
          i5 = *(int *)(i3 + 4 + i9);
          if (stk_102c <= i5) goto L_080ac73e;
        }
        i13 = i2;
        stk_102c = i5;
      }
L_080ac73e:
      i2 = i2 + 1;
      i9 = i9 + 0x702c;
    } while (i2 < g[G_NUM_CHARS]);
  }
  if (i13 == -1) {
    g[0x7579] = g[0x7579] + 1;
    goto L_080ac840;
  }
  if (g[0x801] == 0) {
L_080ac7f5:
    i2 = *pi1;
  }
  else {
    i2 = *pi1;
    i3 = i13 * 0x702c;
    i9 = *(int *)(i2 + 8 + i3);
    if ((*(char *)(i9 + 0x11d8) != '\0') && (*(int *)(i9 + 0x21d8) != 0)) {
      joindirfile(stk_101c,(char *)(i3 + 0x200a + i2),(char *)(i9 + 0x11d8));
      i2 = AILearnDataSave(stk_101c,*(int *)(*pi1 + 8 + i3) + 0x21d8);
      if (i2 == 0) {
        ClipboardAppend((int *)g[G_CLIPBOARD],"Cannot save AI info for %s",i3 + *pi1 + 0x100b,
                        stk_101c);
      }
      goto L_080ac7f5;
    }
  }
  PlayerRCFree(*(void **)(i2 + 8 + i13 * 0x702c));
  i3 = pi4[0x14b6];
  *(uint32_t *)(*pi1 + 8 + i13 * 0x702c) = 0;
  pi4[0x14b6] = i3 + -1;
L_080ac840:
  pv6 = PlayerDefLoad((char *)((int)pi2 + 0x200a),(char *)((int)pi2 + 0x100b));
  pi2[2] = (int)pv6;
  if (pv6 == (void *)0x0) {
    joindirfile(stk_101c,(char *)((int)pi2 + 0x200a),(char *)((int)pi2 + 0x100b));
    pu8 = (uint32_t *)(g + G_ERRMSG);
    do {
      pu7 = pu8;
      pu8 = pu7 + 1;
      u10 = *pu7 + 0xfefefeff & (*pu7 ^ 0xffffffff);
      u11 = u10 & 0x80808080;
    } while (u11 == 0);
    if ((u10 & 0x8080) == 0) {
      u11 = u11 >> 0x10;
      pu8 = (uint32_t *)((int)pu7 + 6);
    }
    sprintf((char *)((int)pu8 +
                     (-(int)(g + G_ERRMSG) - (uint32_t)CARRY1((uint8_t)u11,(uint8_t)u11)) + 0x20745 +
                    (int)g),"\nError loading %s",stk_101c,pv6);
    i13 = 0;
  }
  else {
    i3 = *pi1;
    i13 = *(int *)(i3 + 8 + charno * 0x702c);
    *(int *)(i13 + 0x10a8) = charno;
    *(uint32_t *)(i3 + charno * 0x702c) = 1;
    pi4[0x14b6] = pi4[0x14b6] + 1;
  }
  return i13;
}
#undef stk_102c
#undef stk_101c

/* PlayerCacheFree @ 0x080ac930, 19 bytes
 *
 * Releases a cached character with priority 0 (PlayerCacheFreePriority).
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: PlayerCacheFreePriority
 * Called by: GameFreeChars
 *
 * Elecbyte file: src/mugen/p-make.c
 */
void PlayerCacheFree(int arg1)

{
  PlayerCacheFreePriority(arg1,0);
  return;
}

/* PlayerCacheFreePriority @ 0x080ac950, 81 bytes
 *
 * Lowers a cached character's priority so its slot can be reused; the data
 * stays loaded until the slot is needed.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Globals read: charinfo
 * Called by: GameUnloadStage, PlayerCacheFree, PrecacheWorkerThread
 *
 * Elecbyte file: src/mugen/p-make.c
 */
int PlayerCacheFreePriority(int arg1,int arg2)

{
  int i1;
  int i2;
  int i3;
  
  i2 = g[G_CHARINFO];
  i1 = arg1 * 0x702c;
  i3 = *(int *)(i2 + i1);
  if (0 < i3) {
    i3 = i3 + -1;
    *(int *)(i2 + i1) = i3;
    if (i3 == 0) {
      i3 = cachelastfreedtime + 1;
      *(int *)(i2 + 4 + i1) = arg2 + cachelastfreedtime;
      cachelastfreedtime = i3;
    }
  }
  return i3;
}

/* PlayerCacheChangePriority @ 0x080ac9b0, 73 bytes
 *
 * Raises or lowers the cache priority of a character if it is cached.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Globals read: charinfo
 * Calls: PlayerIsCached
 * Called by: PrecacheRequestChar
 *
 * Elecbyte file: src/mugen/p-make.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
void PlayerCacheChangePriority(int arg1,int arg2)

{
  bool b1;
  uint32_t stale_var;
  
  b1 = PlayerIsCached(arg1);
  if (ZEXT8(b1) != 0) {
    *(int *)(g[G_CHARINFO] + 4 + arg1 * 0x702c) = arg2 + cachelastfreedtime;
  }
  return;
}

/* PlayerIsCached @ 0x080aca00, 49 bytes
 *
 * Returns true if character `charno` is loaded in the cache.
 *
 * Parameters:
 *   charno       int
 *
 * Globals read: charinfo
 * Called by: PlayerCacheChangePriority, PrecacheRequestChar
 *
 * Elecbyte file: src/mugen/p-make.c
 */
bool PlayerIsCached(int charno)

{
  return *(int *)(g[G_CHARINFO] + 8 + charno * 0x702c) != 0;
}

/* PlayerCacheClear @ 0x080aca40, 243 bytes
 *
 * Frees every cached character (saving AI learning data first).
 *
 * Globals read: charinfo, num_chars, clipboard
 * Calls: joindirfile, AILearnDataSave, ClipboardAppend, PlayerRCFree
 * Called by: GameDeInit, GameReloadStage
 * Messages:
 *   "Cannot save AI info for %s"
 *
 * Elecbyte file: src/mugen/p-make.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x1020 bytes,
 *       1 variables), because their address is taken.
 */
void PlayerCacheClear(void)

{
  int *pi1;
  int i2;
  int *pi3;
  int i4;
  uint32_t stale_ECX;
  int i5;
  int i3;
  unsigned char frame[0x1020] __attribute__((aligned(16)));
#define buf_101c (*(char (*)[4108])(frame + 0x4))
  
  pi3 = g;
  i3 = 0;
  pi1 = g + G_CHARINFO;
  if (0 < g[G_NUM_CHARS]) {
    i5 = 0;
    do {
      i4 = *pi1;
      i2 = *(int *)(i4 + 8 + i5);
      if (i2 != 0) {
        if (((g[0x801] != 0) && (*(char *)(i2 + 0x11d8) != '\0')) &&
           (*(int *)(i2 + 0x21d8) != 0)) {
          joindirfile(buf_101c,(char *)(i5 + 0x200a + i4),(char *)(i2 + 0x11d8));
          i4 = AILearnDataSave(buf_101c,*(int *)(*pi1 + 8 + i5) + 0x21d8);
          if (i4 == 0) {
            ClipboardAppend((int *)g[G_CLIPBOARD],"Cannot save AI info for %s",i5 + *pi1 + 0x100b,
                            stale_ECX);
          }
          i4 = *pi1;
        }
        PlayerRCFree(*(void **)(i4 + 8 + i5));
        i4 = *pi1;
        *(uint32_t *)(i4 + i5) = 0;
        *(uint32_t *)(i4 + 8 + i5) = 0;
        pi3[0x14b6] = pi3[0x14b6] + -1;
      }
      i3 = i3 + 1;
      i5 = i5 + 0x702c;
    } while (i3 < pi3[0x14b5]);
  }
  return;
}
#undef buf_101c

/* PlayerCacheHasUnused @ 0x080acb40, 92 bytes
 *
 * Returns true if a cache slot is free or holds a character with priority 0
 * (the precache thread may then load another one).
 *
 * Globals read: num_chars, charinfo
 * Called by: PrecacheWorkerThread
 *
 * Elecbyte file: src/mugen/p-make.c
 */
uint32_t PlayerCacheHasUnused(void)

{
  int i1;
  uint32_t u2;
  int i2;
  
  if (g[0x14b6] < g[0x7579]) {
L_080acb90:
    u2 = 1;
  }
  else {
    i2 = 0;
    if (0 < g[G_NUM_CHARS]) {
      i1 = 0;
      do {
        if ((*(int *)(g[G_CHARINFO] + i1) == 0) && (*(int *)(g[G_CHARINFO] + 8 + i1) != 0))
        goto L_080acb90;
        i2 = i2 + 1;
        i1 = i1 + 0x702c;
      } while (i2 < g[G_NUM_CHARS]);
    }
    u2 = 0;
  }
  return u2;
}

/* PlayerDefLoad @ 0x080acba0, 195 bytes
 *
 * Loads a character from `dirname`/`filename`: a .zip file goes through
 * PlayerDefLoadZip, a .def file through PlayerDefLoadPtr. "Can't open %s" on
 * failure. Returns the chardef or NULL.
 *
 * Parameters:
 *   dirname      char *
 *   filename     char *
 *
 * Globals read: errmsg
 * Calls: joindirfile, CheckExtension, MFfopenZip, PlayerDefLoadZip,
 *        MFfclose, PlayerDefLoadPtr
 * C library: fopen, sprintf, fclose
 * Called by: PlayerCacheLoad
 * Messages:
 *   "Can\'t open %s"
 *
 * Elecbyte file: src/mugen/p-make.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x1020 bytes,
 *       1 variables), because their address is taken.
 */
void * PlayerDefLoad(char *dirname,char *filename)

{
  int i1;
  int *mf;
  int *pi3;
  FILE *fp;
  uint32_t stale_EDX;
  unsigned char frame[0x1020] __attribute__((aligned(16)));
#define stk_101c (*(char (*)[4108])(frame + 0x4))
  
  joindirfile(stk_101c,dirname,filename);
  i1 = CheckExtension(dirname);
  if (i1 == 9) {
    mf = MFfopenZip(dirname,filename);
    if (mf == (int *)0x0) {
      pi3 = (int *)0x0;
    }
    else {
      pi3 = PlayerDefLoadZip(dirname,mf);
      MFfclose(mf);
    }
  }
  else {
    fp = fopen(stk_101c,"rt");
    if (fp == (FILE *)0x0) {
      sprintf((char *)(g + G_ERRMSG),"Can\'t open %s",filename,stale_EDX);
      pi3 = (int *)0x0;
    }
    else {
      pi3 = (int *)PlayerDefLoadPtr(dirname,fp);
      fclose(fp);
    }
  }
  return pi3;
}
#undef stk_101c

/* PlayerDefLoadZip @ 0x080acc70, 3607 bytes
 *
 * PlayerDefLoadPtr for a character packed in a zip archive: the .def and
 * every file it references are read from the archive (MFzopen).
 *
 * Parameters:
 *   dirname      char *
 *   mf           int *
 *
 * Text keys read: [Info], "name", "displayname", "author", "versiondate",
 *                 "mugenversion", [Files], "cmd", "cns", "st", "stcommon",
 *                 "sprite", "anim", "ai", "sound"
 * Globals read: errmsg, clipboard
 * Calls: MFftell, TPReadMF, ecalloc, TPGroupSeek, GetQuotedString,
 *        TPGetValue, TPScanf, MFzclose, MFzopen, joindirfile, MFfclose,
 *        MFfopenFile, PlayerCMDLoadTP, PlayerCNSLoadTP, TPFree,
 *        PlayerSTLoadTP, MDYDateCmp, SctrlAddFileTP, PlayerSTLoadAppend,
 *        CmdSetFreeLabel, SpriteReadSFFPtr, SpriteReadFile,
 *        AnimRCReadFileTP, GetSndMode, ...
 * C library: strcpy, strcat, strcmp, sprintf, fopen, fclose, strncpy
 * Called by: PlayerDefLoad
 * Messages:
 *   "Can\'t access Info"
 *   "Can\'t access Files"
 *   "\nError in "
 *   "Can\'t open file: %s"
 *   "\nError in %s"
 *   "\nCharacter needs to be updated. See docs/incompt*.txt."
 *
 * Elecbyte file: src/mugen/p-make.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x2790 bytes,
 *       6 variables), because their address is taken.
 */
int * PlayerDefLoadZip(char *dirname,int *mf)

{
  bool b1;
  int pos;
  int *tp;
  int *player;
  int i4;
  int *tp2;
  uint32_t stale_var;
  int *sprites;
  int *tp3;
  FILE *stream;
  uint32_t *pu8;
  uint32_t *pu9;
  int *stale_ECX;
  int *stale_ECX_00;
  uint32_t stale_ECX_01;
  int *stale_EDX;
  int *stale_EDX_00;
  uint32_t u10;
  uint32_t u11;
  uint32_t stale_EDX_01;
  int *stale_EDX_02;
  int *stale_EDX_03;
  int *stale_EDX_04;
  int *stale_EDX_05;
  int *saved_EBP;
  char *value;
  int *tp4;
  int *pi14;
  unsigned char frame[0x2790] __attribute__((aligned(16)));
#define stk_278c (*(int **)(frame + 0x4))
#define stk_277c (*(uint8_t (*)[1024])(frame + 0x14))
#define stk_237c (*(int (*)[152])(frame + 0x414))
#define keyname (*(char (*)[256])(frame + 0x674))
#define filename (*(int (*)[1024])(frame + 0x774))
#define filename2 (*(int (*)[1027])(frame + 0x1774))
  
  pos = MFftell(mf);
  tp = TPReadMF(mf,0);
  if (tp == (int *)0x0) {
    return (int *)0x0;
  }
  player = (int *)ecalloc(1,0x22e0);
  if (player == (int *)0x0) {
    return (int *)0x0;
  }
  i4 = TPGroupSeek((int)tp,"Info");
  if (i4 == -1) {
    tp = g + G_ERRMSG;
    value = "Can\'t access Info";
    tp2 = mf;
    tp4 = mf;
    goto L_080ad88d;
  }
  i4 = GetQuotedString((int)tp,"name",(char *)player,0x2f,(char *)0x0);
  if (i4 == 0) {
    return (int *)0x0;
  }
  value = TPGetValue((int)tp,"displayname");
  if (value == (char *)0x0) {
    strcpy((char *)(player + 0xc),(char *)player);
  }
  else {
    i4 = GetQuotedString((int)tp,"displayname",(char *)(player + 0xc),0x2f,(char *)0x0);
    saved_EBP = tp;
    if (i4 == 0) {
      return (int *)0x0;
    }
  }
  value = TPGetValue((int)tp,"author");
  if ((value != (char *)0x0) &&
     (i4 = GetQuotedString((int)tp,"author",(char *)(player + 0x18),0x2f,(char *)0x0),
     i4 == 0)) {
    return (int *)0x0;
  }
  TPScanf((int)tp,"versiondate","%i,%i,%i",player + 0x24,player + 0x25,player + 0x26,saved_EBP,
          saved_EBP);
  TPScanf((int)tp,"mugenversion","%i,%i,%i",player + 0x27,player + 0x28,player + 0x29);
  i4 = TPGroupSeek((int)tp,"Files");
  if (i4 == -1) {
    tp = g + G_ERRMSG;
    value = "Can\'t access Files";
    tp2 = stale_EDX;
    tp4 = stale_EDX;
    goto L_080ad88d;
  }
  tp4 = (int *)&str_cmd;
  i4 = TPScanf((int)tp,"cmd","%s",filename2);
  if (i4 != 1) {
    return (int *)0x0;
  }
  if (*mf == 3) {
    MFzclose((int)mf);
    MFzopen(mf,(char *)filename2);
  }
  else {
    joindirfile((char *)filename,dirname,(char *)filename2);
    tp4 = mf;
    MFfclose(mf);
    mf = (int *)MFfopenFile((char *)filename,"rt");
  }
  pu9 = (uint32_t *)(player + 0x46d);
  tp2 = TPReadMF(mf,0);
  i4 = PlayerCMDLoadTP((uint32_t)tp2,pu9);
  if (i4 == 0) {
    strcat((char *)(g + G_ERRMSG),"\nError in ");
    strcat((char *)(g + G_ERRMSG),(char *)filename2);
    return (int *)0x0;
  }
  tp2 = (int *)&str_cns;
  i4 = TPScanf((int)tp,"cns","%s",filename2);
  if (i4 != 1) {
    return (int *)0x0;
  }
  if (*mf == 3) {
    tp4 = tp2;
    MFzclose((int)mf);
    MFzopen(mf,(char *)filename2);
  }
  else {
    MFfclose(mf);
    joindirfile((char *)filename,dirname,(char *)filename2);
    mf = (int *)MFfopenFile((char *)filename,"rt");
  }
  tp2 = TPReadMF(mf,0);
  if (tp2 == (int *)0x0) {
    value = "Can\'t open file: %s";
  }
  else {
    i4 = PlayerCNSLoadTP((int)player,(int)tp2);
    if (i4 == 0) {
      strcat((char *)(g + G_ERRMSG),"\nError in ");
      strcat((char *)(g + G_ERRMSG),(char *)filename2);
      return (int *)0x0;
    }
    value = TPGetValue((int)tp,"st");
    if (value == (char *)0x0) {
      return (int *)0x0;
    }
    i4 = strcmp(value,(char *)filename2);
    if (i4 != 0) {
      TPFree(tp2);
      strcpy((char *)filename2,value);
      if (*mf == 3) {
        MFzclose((int)mf);
        MFzopen(mf,(char *)filename2);
      }
      else {
        value = dirname;
        joindirfile((char *)filename,dirname,(char *)filename2);
        MFfclose(mf);
        mf = (int *)MFfopenFile((char *)filename,"rt");
      }
      tp2 = TPReadMF(mf,0);
      if (tp2 == (int *)0x0) {
        value = "Can\'t open file: %s";
        tp4 = stale_EDX_00;
        goto L_080ad888;
      }
    }
    b1 = PlayerSTLoadTP((int)player,(int)tp2);
    if (ZEXT8(b1) == 0) {
      pu9 = (uint32_t *)(g + G_ERRMSG);
      do {
        pu8 = pu9;
        pu9 = pu8 + 1;
        u10 = *pu8 + 0xfefefeff & (*pu8 ^ 0xffffffff);
        u11 = u10 & 0x80808080;
      } while (u11 == 0);
      if ((u10 & 0x8080) == 0) {
        u11 = u11 >> 0x10;
        pu9 = (uint32_t *)((int)pu8 + 6);
      }
      sprintf((char *)((int)pu9 +
                       (-(int)(g + G_ERRMSG) - (uint32_t)CARRY1((uint8_t)u11,(uint8_t)u11)) + 0x20745 +
                      (int)g),"\nError in %s",filename2,value);
      pos = MDYDateCmp(player[0x27],player[0x28],player[0x29],g[0x802],g[0x803],g[0x804]);
      if (pos < 0) {
        value = "\nCharacter needs to be updated. See docs/incompt*.txt.";
      }
      else {
        pos = MDYDateCmp(player[0x27],player[0x28],player[0x29],g[0x802],g[0x803],g[0x804]);
        if (pos < 1) {
          return (int *)0x0;
        }
        value = "\nCharacter is not designed to run on this version of M.U.G.E.N.";
      }
      strcat((char *)(g + G_ERRMSG),value);
      return (int *)0x0;
    }
    TPFree(tp2);
    stk_278c = (int *)0x0;
    sprites = filename;
    do {
      sprintf(keyname,"st%i",stk_278c,sprites);
      i4 = TPScanf((int)tp,keyname,"%s",filename2);
      if (i4 == 1) {
        if (*mf == 3) {
          MFzclose((int)mf);
          MFzopen(mf,(char *)filename2);
          tp4 = stk_278c;
        }
        else {
          joindirfile((char *)filename,dirname,(char *)filename2);
          MFfclose(mf);
          mf = (int *)MFfopenFile((char *)filename,"rt");
          tp4 = filename;
        }
        if (mf == (int *)0x0) {
          value = "\nCould not open file: %s";
          goto L_080ad888;
        }
        tp4 = TPReadMF(mf,0);
        if (tp4 == (int *)0x0) {
          value = "\nError reading in file: %s";
          tp4 = stale_ECX;
          goto L_080ad888;
        }
        i4 = SctrlAddFileTP((int *)player[0x471],(int)tp4,(int)player);
        if (i4 == 0) {
          sprintf(keyname,"\nError in %s",filename2,stale_EDX_01);
          strcat((char *)(g + G_ERRMSG),keyname);
          pos = MDYDateCmp(player[0x27],player[0x28],player[0x29],g[0x802],g[0x803],g[0x804]);
          if (pos < 0) {
            value = "\nCharacter needs to be updated. See docs/incompt*.txt.";
          }
          else {
            pos = MDYDateCmp(player[0x27],player[0x28],player[0x29],g[0x802],g[0x803],g[0x804]);
            if (pos < 1) {
              return (int *)0x0;
            }
            value = "\nCharacter is not designed to run on this version of M.U.G.E.N.";
          }
          strcat((char *)(g + G_ERRMSG),value);
          return (int *)0x0;
        }
        TPFree(tp4);
      }
      sprites = (int *)((int)stk_278c + 1);
      stk_278c = sprites;
    } while ((int)sprites < 10);
    i4 = TPScanf((int)tp,"cmd","%s",filename2);
    if (i4 != 1) {
      return (int *)0x0;
    }
    if (*mf == 3) {
      MFzclose((int)mf);
      MFzopen(mf,(char *)filename2);
      tp4 = filename2;
    }
    else {
      tp4 = filename;
      joindirfile((char *)tp4,dirname,(char *)filename2);
      MFfclose(mf);
      mf = (int *)MFfopenFile((char *)tp4,"rt");
    }
    if (mf == (int *)0x0) {
      value = "\nCould not open file: %s";
    }
    else {
      tp3 = TPReadMF(mf,0);
      if (tp3 == (int *)0x0) {
        value = "\nError reading in file: %s";
        tp4 = stale_EDX_02;
      }
      else {
        pi14 = tp3;
        i4 = SctrlAddFileTP((int *)player[0x471],(int)tp3,(int)player);
        if (i4 == 0) {
          strcat((char *)(g + G_ERRMSG),"\nError in ");
          strcat((char *)(g + G_ERRMSG),(char *)filename2);
          return (int *)0x0;
        }
        TPFree(tp3);
        tp2 = filename2;
        i4 = TPScanf((int)tp,"stcommon","%s",tp2);
        tp4 = player;
        if (i4 == 1) {
          i4 = 1;
          if (*mf == 3) {
            tp4 = pi14;
            MFzclose((int)mf);
            i4 = MFzopen(mf,(char *)tp2);
          }
          if (i4 == 1) {
            tp3 = TPReadMF(mf,0);
            if (tp3 == (int *)0x0) {
              tp = g + G_ERRMSG;
              value = "\nError reading in file: %s";
              tp4 = stale_EDX_03;
              goto L_080ad88d;
            }
            SctrlAddFileTP((int *)player[0x471],(int)tp3,(int)player);
            tp4 = player;
          }
          else {
            tp3 = filename;
            joindirfile((char *)tp3,"data/",(char *)tp2);
            i4 = PlayerSTLoadAppend((int)player,(char *)tp3);
            if (i4 == 0) {
              strcat((char *)(g + G_ERRMSG),"\nError in ");
              strcat((char *)(g + G_ERRMSG),(char *)tp2);
              return (int *)0x0;
            }
          }
        }
        CmdSetFreeLabel((int)(player + 0x46d));
        tp2 = filename2;
        i4 = TPScanf((int)tp,"sprite","%s",tp2);
        if (i4 != 1) {
          return (int *)0x0;
        }
        if (*mf == 3) {
          MFzclose((int)mf);
          MFzopen(mf,(char *)tp2);
          if (sprites == (int *)0x0) {
            tp = g + G_ERRMSG;
            value = "\nCould not open file: %s";
            tp4 = tp3;
            goto L_080ad88d;
          }
          tp4 = SpriteReadSFFPtr(mf);
          player[0x472] = (int)tp4;
          if (tp4 == (int *)0x0) {
            tp = g + G_ERRMSG;
            value = "Can\'t load %s";
            tp4 = stale_ECX_00;
            goto L_080ad88d;
          }
        }
        else {
          joindirfile((char *)filename,dirname,(char *)tp2);
          sprites = SpriteReadFile((char *)filename);
          player[0x472] = (int)sprites;
          if (sprites == (int *)0x0) {
            tp = g + G_ERRMSG;
            value = "Can\'t load %s";
            goto L_080ad88d;
          }
        }
        i4 = TPScanf((int)tp,"anim","%s",filename2);
        if (i4 != 1) {
          return (int *)0x0;
        }
        if (*mf == 3) {
          MFzclose((int)mf);
          MFzopen(mf,(char *)filename2);
        }
        else {
          joindirfile((char *)filename,dirname,(char *)filename2);
          MFfclose(mf);
          mf = (int *)MFfopenFile((char *)filename,"rt");
        }
        tp4 = TPReadMF(mf,0);
        if (tp4 == (int *)0x0) {
          value = "\nError reading in file: %s";
          tp4 = stale_EDX_04;
        }
        else {
          clsnxscale = player[0x436];
          clsnyscale = player[0x437];
          tp2 = AnimRCReadFileTP((int)tp4);
          player[0x473] = (int)tp2;
          if (tp2 == (int *)0x0) {
            tp4 = (int *)0x0;
          }
          else {
            clsnyscale = 0x3f800000;
            clsnxscale = 0x3f800000;
            TPFree(tp4);
            i4 = GetSndMode();
            if (i4 != 1) {
L_080ad8a0:
              stk_278c = (int *)0x0;
              value = keyname;
              do {
                sprintf(keyname,"pal%i",(char *)((int)stk_278c + 1),value);
                i4 = TPScanf((int)tp,keyname,"%s",filename2);
                if (0 < i4) {
                  if (*mf == 3) {
                    MFzclose((int)mf);
                    MFzopen(mf,(char *)filename2);
                  }
                  else {
                    joindirfile((char *)filename,dirname,(char *)filename2);
                    MFfclose(mf);
                    mf = (int *)MFfopenFile((char *)filename,"rb");
                  }
                  i4 = Pal4Read3FilePtr((int)stk_277c,mf);
                  tp4 = stale_EDX_05;
                  if (i4 == 0) goto L_080ad876;
                  i4 = EBPalInit(stk_237c,0x100,stk_277c,1);
                  if (i4 == 0) {
                    return (int *)0x0;
                  }
                  i4 = SpriteArrayAddPal(player[0x472],stk_237c,1,stk_278c);
                  if (i4 == 0) {
                    return (int *)0x0;
                  }
                }
                value = (char *)((int)stk_278c + 1);
                stk_278c = (int *)value;
                if (0xb < (int)value) {
                  i4 = TPScanf((int)tp,"ai","%s",filename2);
                  if (i4 == 1) {
                    joindirfile((char *)filename,dirname,(char *)filename2);
                    i4 = AILearnDataLoad((char *)filename,player + 0x876);
                    if ((i4 == 0) &&
                       (stream = fopen((char *)filename,"rb"), stream != (FILE *)0x0)) {
                      ClipboardAppend((int *)g[G_CLIPBOARD],"Ignoring invalid AI file: %s\n",filename2,
                                      stale_ECX_01);
                      fclose(stream);
                    }
                    strncpy((char *)(player + 0x476),(char *)filename2,0xffe);
                  }
                  TPFree(tp);
                  MFfseek(mf,pos,0);
                  return player;
                }
              } while( true );
            }
            i4 = TPScanf((int)tp,"sound","%s",filename2);
            if (i4 != 1) goto L_080ad8a0;
            if (*mf == 3) {
              MFzclose((int)mf);
              MFzopen(mf,(char *)filename2);
            }
            else {
              joindirfile((char *)filename,dirname,(char *)filename2);
              MFfclose(mf);
              mf = (int *)MFfopenFile((char *)filename,"rb");
            }
            tp2 = SndReadFileSNDPtr(mf);
            player[0x475] = (int)tp2;
            tp4 = mf;
            if (tp2 != (int *)0x0) goto L_080ad8a0;
          }
L_080ad876:
          value = "Can\'t load %s";
        }
      }
    }
  }
L_080ad888:
  tp2 = filename2;
  tp = g + G_ERRMSG;
L_080ad88d:
  sprintf((char *)tp,value,tp2,tp4);
  return (int *)0x0;
}
#undef stk_278c
#undef stk_277c
#undef stk_237c
#undef keyname
#undef filename
#undef filename2

/* PlayerDefLoadPtr @ 0x080ada90, 2562 bytes
 *
 * Loads a character from its .def file.
 * - "[Info]": name, displayname, author, versiondate, mugenversion. A
 * character made for an older engine version is rejected ("Character needs
 * to be updated. See docs/incompt*.txt.", "Character is not designed to run
 * on this version of M.U.G.E.N.").
 * - "[Files]": cmd (commands), cns (constants), st, st0..st9 and stcommon
 * (states), sprite, anim, sound, ai, pal1..pal12.
 *
 * Each file is loaded relative to the character directory, or "data/" for
 * common files. Errors: "Can't access Info", "Can't access Files", "Can't
 * open file: %s", "Error in %s"; an invalid AI file is ignored ("Ignoring
 * invalid AI file: %s"). Returns the new chardef or NULL.
 *
 * Parameters:
 *   dirname      char *
 *   fp           FILE *
 *
 * Text keys read: [Info], "name", "displayname", "author", "versiondate",
 *                 "mugenversion", [Files], "cmd", "cns", "st", "stcommon",
 *                 "sprite", "anim", "sound", "ai"
 * Globals read: errmsg, clipboard
 * Calls: TPReadFilePtr, ecalloc, TPGroupSeek, GetQuotedString, TPGetValue,
 *        TPScanf, joindirfile, PlayerCMDLoad, TPReadFile, PlayerCNSLoadTP,
 *        TPFree, PlayerSTLoadTP, MDYDateCmp, PlayerSTLoadAppend,
 *        CmdSetFreeLabel, SpriteReadFile, AnimRCReadFile, GetSndMode,
 *        SndReadFile, Pal4Read3File, EBPalInit, SpriteArrayAddPal,
 *        AILearnDataLoad, ClipboardAppend
 * C library: ftell, strcpy, strcat, strcmp, sprintf, fopen, fclose,
 *            strncpy, fseek
 * Called by: PlayerDefLoad
 * Messages:
 *   "Can\'t access Info"
 *   "Can\'t access Files"
 *   "\nError in "
 *   "Can\'t open file: %s"
 *   "\nError in %s"
 *   "\nCharacter needs to be updated. See docs/incompt*.txt."
 *
 * Elecbyte file: src/mugen/p-make.c
 * Note: decompiler flag: stack slots read outside the declared parameters
 *       (entry_stack variables)
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x2780 bytes,
 *       5 variables), because their address is taken.
 */
char * PlayerDefLoadPtr(char *dirname,FILE *fp)

{
  char *pc1;
  bool b2;
  long off;
  int *tp;
  char *player;
  int i2;
  char *tp2;
  char *value;
  uint32_t stale_var;
  int i8;
  int *sprites;
  FILE *stream;
  uint32_t *pu10;
  uint32_t *pu11;
  int *stale_ECX;
  int *stale_ECX_00;
  int *stale_ECX_01;
  uint32_t stale_ECX_02;
  uint32_t stale_EDX;
  uint32_t stale_EDX_00;
  uint32_t u12;
  uint32_t stale_EDX_01;
  uint32_t u13;
  uint32_t u14;
  int *stale_EDX_02;
  int *filename;
  unsigned char frame[0x2780] __attribute__((aligned(16)));
#define stk_277c (*(uint8_t (*)[1024])(frame + 0x4))
#define stk_237c (*(int (*)[152])(frame + 0x404))
#define keyname (*(char (*)[256])(frame + 0x664))
#define filename2 (*(char (*)[4096])(frame + 0x764))
#define filename3 (*(int (*)[1027])(frame + 0x1764))
  
  off = ftell(fp);
  tp = TPReadFilePtr(fp,0);
  if (tp == (int *)0x0) {
    return (char *)0x0;
  }
  player = (char *)ecalloc(1,0x22e0);
  if (player == (char *)0x0) {
    return (char *)0x0;
  }
  i2 = TPGroupSeek((int)tp,"Info");
  if (i2 == -1) {
    sprites = g + G_ERRMSG;
    player = "Can\'t access Info";
    tp = filename;
  }
  else {
    i2 = GetQuotedString((int)tp,"name",player,0x2f,(char *)0x0);
    if (i2 == 0) {
      return (char *)0x0;
    }
    tp2 = TPGetValue((int)tp,"displayname");
    if (tp2 == (char *)0x0) {
      strcpy(player + 0x30,player);
    }
    else {
      i2 = GetQuotedString((int)tp,"displayname",player + 0x30,0x2f,(char *)0x0);
      if (i2 == 0) {
        return (char *)0x0;
      }
    }
    tp2 = TPGetValue((int)tp,"author");
    u12 = stale_EDX;
    if ((tp2 != (char *)0x0) &&
       (i2 = GetQuotedString((int)tp,"author",player + 0x60,0x2f,(char *)0x0),
       u12 = stale_EDX_00, i2 == 0)) {
      return (char *)0x0;
    }
    TPScanf((int)tp,"versiondate","%i,%i,%i",player + 0x90,player + 0x94,player + 0x98,u12,
            u12);
    TPScanf((int)tp,"mugenversion","%i,%i,%i",player + 0x9c,player + 0xa0,player + 0xa4);
    i2 = TPGroupSeek((int)tp,"Files");
    if (i2 == -1) {
      sprites = g + G_ERRMSG;
      player = "Can\'t access Files";
      filename = tp;
    }
    else {
      filename = filename3;
      i2 = TPScanf((int)tp,"cmd","%s",filename);
      if (i2 != 1) {
        return (char *)0x0;
      }
      joindirfile(filename2,dirname,(char *)filename);
      i2 = PlayerCMDLoad(filename2,(uint32_t *)(player + 0x11b4));
      if (i2 == 0) {
        strcat((char *)(g + G_ERRMSG),"\nError in ");
        strcat((char *)(g + G_ERRMSG),(char *)filename);
        return (char *)0x0;
      }
      i2 = TPScanf((int)tp,"cns","%s",filename);
      if (i2 != 1) {
        return (char *)0x0;
      }
      joindirfile(filename2,dirname,(char *)filename);
      tp2 = TPReadFile(filename2);
      if (tp2 == (char *)0x0) {
        sprites = g + G_ERRMSG;
        player = "Can\'t open file: %s";
        tp = (int *)0x0;
      }
      else {
        i2 = PlayerCNSLoadTP((int)player,(int)tp2);
        if (i2 == 0) {
          strcat((char *)(g + G_ERRMSG),"\nError in ");
          strcat((char *)(g + G_ERRMSG),(char *)filename);
          return (char *)0x0;
        }
        value = TPGetValue((int)tp,"st");
        if (value == (char *)0x0) {
          return (char *)0x0;
        }
        i2 = strcmp(value,(char *)filename);
        if (i2 != 0) {
          TPFree((uint32_t *)tp2);
          strcpy((char *)filename,value);
          joindirfile(filename2,dirname,(char *)filename);
          tp2 = TPReadFile(filename2);
          if (tp2 == (char *)0x0) {
            sprites = g + G_ERRMSG;
            player = "Can\'t open file: %s";
            tp = (int *)0x0;
            goto L_080ae2d6;
          }
        }
        b2 = PlayerSTLoadTP((int)player,(int)tp2);
        if (ZEXT8(b2) == 0) {
          pu11 = (uint32_t *)(g + G_ERRMSG);
          do {
            pu10 = pu11;
            pu11 = pu10 + 1;
            u13 = *pu10 + 0xfefefeff & (*pu10 ^ 0xffffffff);
            u14 = u13 & 0x80808080;
          } while (u14 == 0);
          if ((u13 & 0x8080) == 0) {
            u14 = u14 >> 0x10;
            pu11 = (uint32_t *)((int)pu10 + 6);
          }
          sprintf((char *)((int)pu11 +
                           (-(int)(g + G_ERRMSG) - (uint32_t)CARRY1((uint8_t)u14,(uint8_t)u14)) + 0x20745
                          + (int)g),"\nError in %s",filename3,stale_EDX_01);
          i2 = MDYDateCmp(*(int *)(player + 0x9c),*(int *)(player + 0xa0),*(int *)(player + 0xa4)
                             ,g[0x802],g[0x803],g[0x804]);
          if (i2 < 0) {
            player = "\nCharacter needs to be updated. See docs/incompt*.txt.";
          }
          else {
            i2 = MDYDateCmp(*(int *)(player + 0x9c),*(int *)(player + 0xa0),
                               *(int *)(player + 0xa4),g[0x802],g[0x803],g[0x804]);
            if (i2 < 1) {
              return (char *)0x0;
            }
            player = "\nCharacter is not designed to run on this version of M.U.G.E.N.";
          }
          strcat((char *)(g + G_ERRMSG),player);
          return (char *)0x0;
        }
        i2 = 0;
        TPFree((uint32_t *)tp2);
        do {
          sprintf(keyname,"st%i",i2,tp2);
          i8 = TPScanf((int)tp,keyname,"%s",filename3);
          if (i8 == 1) {
            tp2 = filename2;
            joindirfile(tp2,dirname,(char *)filename3);
            i8 = PlayerSTLoadAppend((int)player,tp2);
            if (i8 == 0) {
              sprintf(keyname,"\nError in %s",filename3,i2);
              strcat((char *)(g + G_ERRMSG),keyname);
              i2 = MDYDateCmp(*(int *)(player + 0x9c),*(int *)(player + 0xa0),
                                 *(int *)(player + 0xa4),g[0x802],g[0x803],g[0x804]);
              if (i2 < 0) {
                player = "\nCharacter needs to be updated. See docs/incompt*.txt.";
              }
              else {
                i2 = MDYDateCmp(*(int *)(player + 0x9c),*(int *)(player + 0xa0),
                                   *(int *)(player + 0xa4),g[0x802],g[0x803],g[0x804]);
                if (i2 < 1) {
                  return (char *)0x0;
                }
                player = "\nCharacter is not designed to run on this version of M.U.G.E.N.";
              }
              strcat((char *)(g + G_ERRMSG),player);
              return (char *)0x0;
            }
          }
          i2 = i2 + 1;
        } while (i2 < 10);
        i2 = TPScanf((int)tp,"cmd","%s",filename3);
        if (i2 != 1) {
          return (char *)0x0;
        }
        joindirfile(filename2,dirname,(char *)filename3);
        i2 = PlayerSTLoadAppend((int)player,filename2);
        if (i2 == 0) {
          strcat((char *)(g + G_ERRMSG),"\nError in ");
          strcat((char *)(g + G_ERRMSG),(char *)filename3);
          return (char *)0x0;
        }
        i2 = TPScanf((int)tp,"stcommon","%s",filename3);
        if (i2 == 1) {
          joindirfile(filename2,dirname,(char *)filename3);
          i2 = PlayerSTLoadAppend((int)player,filename2);
          if (i2 == 0) {
            joindirfile(filename2,"data/",(char *)filename3);
            i2 = PlayerSTLoadAppend((int)player,filename2);
            if (i2 == 0) {
              strcat((char *)(g + G_ERRMSG),"\nError in ");
              strcat((char *)(g + G_ERRMSG),(char *)filename3);
              return (char *)0x0;
            }
          }
        }
        CmdSetFreeLabel((int)(player + 0x11b4));
        filename = filename3;
        i2 = TPScanf((int)tp,"sprite","%s",filename);
        if (i2 != 1) {
          return (char *)0x0;
        }
        joindirfile(filename2,dirname,(char *)filename);
        sprites = SpriteReadFile(filename2);
        *(int **)(player + 0x11c8) = sprites;
        if (sprites == (int *)0x0) {
          sprites = g + G_ERRMSG;
          player = "Can\'t load %s";
          tp = stale_ECX;
        }
        else {
          i2 = TPScanf((int)tp,"anim","%s",filename);
          if (i2 != 1) {
            return (char *)0x0;
          }
          joindirfile(filename2,dirname,(char *)filename);
          clsnxscale = *(int *)(player + 0x10d8);
          clsnyscale = *(int *)(player + 0x10dc);
          sprites = AnimRCReadFile(filename2);
          *(int **)(player + 0x11cc) = sprites;
          if (sprites != (int *)0x0) {
            clsnyscale = 0x3f800000;
            clsnxscale = 0x3f800000;
            i2 = GetSndMode();
            if ((i2 == 1) &&
               (i2 = TPScanf((int)tp,"sound","%s",filename), i2 == 1)) {
              joindirfile(filename2,dirname,(char *)filename);
              sprites = SndReadFile(filename2);
              *(int **)(player + 0x11d4) = sprites;
              if (sprites == (int *)0x0) {
                sprites = g + G_ERRMSG;
                player = "Can\'t load %s";
                tp = stale_ECX_01;
                goto L_080ae2d6;
              }
            }
            filename = filename3;
            tp2 = dirname;
            value = (char *)0x0;
            do {
              pc1 = value + 1;
              sprintf(keyname,"pal%i",pc1,tp2);
              i2 = TPScanf((int)tp,keyname,"%s",filename);
              if (0 < i2) {
                joindirfile(filename2,dirname,(char *)filename);
                i2 = Pal4Read3File((int)stk_277c,filename2);
                if (i2 == 0) {
                  player = "Can\'t load %s";
                  sprites = g + G_ERRMSG;
                  tp = stale_EDX_02;
                  goto L_080ae2d6;
                }
                i2 = EBPalInit(stk_237c,0x100,stk_277c,1);
                if (i2 == 0) {
                  return (char *)0x0;
                }
                i2 = SpriteArrayAddPal(*(int *)(player + 0x11c8),stk_237c,1,value);
                if (i2 == 0) {
                  return (char *)0x0;
                }
              }
              tp2 = pc1;
              value = pc1;
              if (0xb < (int)pc1) {
                i2 = TPScanf((int)tp,"ai","%s",filename3);
                if (i2 == 1) {
                  joindirfile(filename2,dirname,(char *)filename3);
                  i2 = AILearnDataLoad(filename2,(uint32_t *)(player + 0x21d8));
                  if ((i2 == 0) && (stream = fopen(filename2,"rb"), stream != (FILE *)0x0)) {
                    ClipboardAppend((int *)g[G_CLIPBOARD],"Ignoring invalid AI file: %s\n",filename3,
                                    stale_ECX_02);
                    fclose(stream);
                  }
                  strncpy(player + 0x11d8,(char *)filename3,0xffe);
                }
                TPFree(tp);
                fseek(fp,off,0);
                return player;
              }
            } while( true );
          }
          sprites = g + G_ERRMSG;
          player = "Can\'t load %s";
          tp = stale_ECX_00;
        }
      }
    }
  }
L_080ae2d6:
  sprintf((char *)sprites,player,filename,tp);
  return (char *)0x0;
}
#undef stk_277c
#undef stk_237c
#undef keyname
#undef filename2
#undef filename3

/* PlayerCNSLoadTP @ 0x080ae4a0, 2036 bytes
 *
 * Reads a character's constants from its .cns file into the chardef:
 * - "[Data]": life, power, attack, defence, fall.defence_up, liedown.time,
 * airjuggle, sparkno, guard.sparkno, ko.echo, volume, IntPersistIndex,
 * FloatPersistIndex;
 * - "[Size]": xscale, yscale, ground/air back and front, height,
 * attack.dist, proj.attack.dist, proj.doscale, head.pos, mid.pos,
 * shadowoffset, draw.offset, z.width, attack.z.width;
 * - "[Velocity]": walk, run, jump, runjump and airjump velocities;
 * - "[Movement]": airjump.num, airjump.height, yaccel, stand.friction,
 * crouch.friction.
 *
 * Missing groups are errors ("Can't access Data", "Can't load Size
 * constants", ...).
 *
 * Parameters:
 *   chardef      int
 *   tp           int
 *
 * Text keys read: [Data], "life", "attack", "defence", "fall.defence_up",
 *                 "liedown.time", "airjuggle", "volume", "power",
 *                 "sparkno", "guard.sparkno", "ko.echo",
 *                 "IntPersistIndex", "FloatPersistIndex", [Size],
 *                 "ground.back", "ground.front", "air.back", "air.front",
 *                 "height", "z.width", "xscale", "yscale", "draw.offset",
 *                 ...
 * Globals read: errmsg
 * CharDef fields: data_life, data_attack, data_defence,
 *                 data_fall_defence_up, data_liedown_time, data_airjuggle,
 *                 data_volume, data_power, data_sparkno,
 *                 data_guard_sparkno, data_ko_echo, data_intpersistindex,
 *                 data_floatpersistindex, size_ground_back,
 *                 size_ground_front, size_air_back
 * Calls: TPGroupSeek, TPGetValueInt, TPGetValueFloat, TPScanf
 * C library: sprintf
 * Called by: PlayerDefLoadPtr, PlayerDefLoadZip
 * Messages:
 *   "Can\'t access Data"
 *   "Can\'t load Data constants"
 *   "Can\'t access Size constants"
 *   "Can\'t load Size constants"
 *   "Can\'t access Velocity constants"
 *   "Can\'t access Movement constants"
 *
 * Elecbyte file: src/mugen/p-make.c
 * Note: 13 byte results widened with ZEXT8 (upper bytes are zero).
 */
uint32_t PlayerCNSLoadTP(int chardef,int tp)

{
  bool b1;
  int i2;
  uint32_t stale_var;
  uint32_t stale_var_00;
  uint32_t stale_var_01;
  uint32_t stale_var_02;
  uint32_t stale_var_03;
  uint32_t stale_var_04;
  uint32_t stale_var_05;
  uint32_t stale_var_06;
  uint32_t stale_var_07;
  uint32_t stale_var_08;
  uint32_t stale_var_09;
  uint32_t stale_var_10;
  uint32_t stale_var_11;
  int *s;
  int stale_ECX;
  int stale_ECX_00;
  int stale_ECX_01;
  int stale_ECX_02;
  int stale_ECX_03;
  int stale_EDX;
  int stale_EDX_00;
  int stale_EDX_01;
  int stale_EDX_02;
  int stale_EDX_03;
  int stale_EDX_04;
  int stale_EDX_05;
  uint32_t stale_EDX_06;
  int stale_EDX_07;
  char *pc3;
  float *pf4;
  uint32_t u5;
  
  i2 = TPGroupSeek(tp,"Data");
  if (i2 == -1) {
    s = g + G_ERRMSG;
    pc3 = "Can\'t access Data";
    chardef = stale_ECX;
  }
  else {
    b1 = TPGetValueInt(tp,"life",(uint32_t *)(chardef + CD_DATA_LIFE));
    i2 = stale_EDX;
    if ((((ZEXT8(b1) == 0) ||
         (b1 = TPGetValueInt(tp,"attack",(uint32_t *)(chardef + CD_DATA_ATTACK)),
         i2 = stale_EDX_00, ZEXT8(b1) == 0)) ||
        (b1 = TPGetValueInt(tp,"defence",(uint32_t *)(chardef + CD_DATA_DEFENCE)),
        i2 = stale_EDX_01, ZEXT8(b1) == 0)) ||
       (((b1 = TPGetValueFloat(tp,"fall.defence_up",(float *)(chardef + CD_DATA_FALL_DEFENCE_UP)),
         i2 = stale_EDX_02, ZEXT8(b1) == 0 ||
         (b1 = TPGetValueInt(tp,"liedown.time",(uint32_t *)(chardef + CD_DATA_LIEDOWN_TIME)),
         i2 = stale_EDX_03, ZEXT8(b1) == 0)) ||
        (b1 = TPGetValueInt(tp,"airjuggle",(uint32_t *)(chardef + CD_DATA_AIRJUGGLE)),
        i2 = stale_EDX_04, ZEXT8(b1) == 0)))) {
      s = g + G_ERRMSG;
      pc3 = "Can\'t load Data constants";
      chardef = i2;
    }
    else {
      TPGetValueInt(tp,"volume",(uint32_t *)(chardef + CD_DATA_VOLUME));
      *(uint32_t *)(chardef + CD_DATA_POWER) = 3000;
      *(uint32_t *)(chardef + CD_DATA_KO_ECHO) = 1;
      *(uint32_t *)(chardef + CD_DATA_INTPERSISTINDEX) = 0x3c;
      *(uint32_t *)(chardef + CD_DATA_FLOATPERSISTINDEX) = 0x28;
      TPGetValueInt(tp,"power",(uint32_t *)(chardef + CD_DATA_POWER));
      *(float *)(chardef + CD_DATA_FALL_DEFENCE_UP) = 100.0 / (*(float *)(chardef + CD_DATA_FALL_DEFENCE_UP) + 100.0);
      TPGetValueInt(tp,"sparkno",(uint32_t *)(chardef + CD_DATA_SPARKNO));
      TPGetValueInt(tp,"guard.sparkno",(uint32_t *)(chardef + CD_DATA_GUARD_SPARKNO));
      TPGetValueInt(tp,"ko.echo",(uint32_t *)(chardef + CD_DATA_KO_ECHO));
      TPGetValueInt(tp,"IntPersistIndex",(uint32_t *)(chardef + CD_DATA_INTPERSISTINDEX));
      TPGetValueInt(tp,"FloatPersistIndex",(uint32_t *)(chardef + CD_DATA_FLOATPERSISTINDEX));
      i2 = *(int *)(chardef + CD_DATA_INTPERSISTINDEX);
      if (0x3c < i2) {
        *(uint32_t *)(chardef + CD_DATA_INTPERSISTINDEX) = 0x3c;
        i2 = 0x3c;
      }
      if (i2 < 0) {
        *(uint32_t *)(chardef + CD_DATA_INTPERSISTINDEX) = 0;
      }
      i2 = *(int *)(chardef + CD_DATA_FLOATPERSISTINDEX);
      if (0x28 < i2) {
        *(uint32_t *)(chardef + CD_DATA_FLOATPERSISTINDEX) = 0x28;
        i2 = 0x28;
      }
      if (i2 < 0) {
        *(uint32_t *)(chardef + CD_DATA_FLOATPERSISTINDEX) = 0;
      }
      i2 = TPGroupSeek(tp,"Size");
      if (i2 == -1) {
        s = g + G_ERRMSG;
        pc3 = "Can\'t access Size constants";
        chardef = stale_EDX_05;
      }
      else {
        *(uint32_t *)(chardef + 0x10dc) = 0x3f800000;
        *(uint32_t *)(chardef + CD_SIZE_XSCALE) = 0x3f800000;
        *(uint32_t *)(chardef + CD_SIZE_ATTACK_DIST) = 0xa0;
        *(uint32_t *)(chardef + CD_SIZE_PROJ_ATTACK_DIST) = 0x5a;
        *(uint32_t *)(chardef + CD_SIZE_ATTACK_Z_WIDTH_1) = 4;
        *(uint32_t *)(chardef + CD_SIZE_ATTACK_Z_WIDTH_0) = 4;
        *(uint32_t *)(chardef + CD_SIZE_Z_WIDTH) = 3;
        *(uint32_t *)(chardef + CD_SIZE_HEIGHT) = 0x3c;
        *(uint32_t *)(chardef + CD_SIZE_HEAD_POS_0) = 0xfffffffb;
        *(uint32_t *)(chardef + CD_SIZE_MID_POS_0) = 0xfffffffb;
        *(uint32_t *)(chardef + CD_SIZE_MID_POS_1) = 0xffffffc4;
        *(uint32_t *)(chardef + CD_SIZE_HEAD_POS_1) = 0xffffffa6;
        b1 = TPGetValueInt(tp,"ground.back",(uint32_t *)(chardef + CD_SIZE_GROUND_BACK));
        i2 = stale_ECX_00;
        if (((ZEXT8(b1) == 0) ||
            (b1 = TPGetValueInt(tp,"ground.front",(uint32_t *)(chardef + CD_SIZE_GROUND_FRONT)),
            i2 = stale_ECX_01, ZEXT8(b1) == 0)) ||
           ((b1 = TPGetValueInt(tp,"air.back",(uint32_t *)(chardef + CD_SIZE_AIR_BACK)),
            i2 = stale_ECX_02, ZEXT8(b1) == 0 ||
            (b1 = TPGetValueInt(tp,"air.front",(uint32_t *)(chardef + CD_SIZE_AIR_FRONT)),
            i2 = stale_ECX_03, ZEXT8(b1) == 0)))) {
          s = g + G_ERRMSG;
          pc3 = "Can\'t load Size constants";
          chardef = i2;
        }
        else {
          u5 = stale_EDX_06;
          TPGetValueInt(tp,"height",(uint32_t *)(chardef + CD_SIZE_HEIGHT));
          TPGetValueInt(tp,"z.width",(uint32_t *)(chardef + CD_SIZE_Z_WIDTH));
          TPGetValueFloat(tp,"xscale",(float *)(chardef + CD_SIZE_XSCALE));
          pf4 = (float *)(chardef + 0x10dc);
          pc3 = "yscale";
          TPGetValueFloat(tp,"yscale",pf4);
          TPScanf(tp,"draw.offset","%i,%i",chardef + 0x11a4,chardef + 0x11a8,pc3,pf4,
                  u5);
          TPScanf(tp,"attack.z.width","%i,%i",chardef + 0x10b8,chardef + 0x10bc);
          TPGetValueInt(tp,"attack.dist",(uint32_t *)(chardef + CD_SIZE_ATTACK_DIST));
          TPGetValueInt(tp,"proj.attack.dist",(uint32_t *)(chardef + CD_SIZE_PROJ_ATTACK_DIST));
          TPGetValueInt(tp,"proj.doscale",(uint32_t *)(chardef + CD_SIZE_PROJ_DOSCALE));
          TPScanf(tp,"head.pos","%i,%i",chardef + 0x10fc,chardef + 0x1100);
          TPScanf(tp,"mid.pos","%i,%i",chardef + 0x1104,chardef + 0x1108);
          TPGetValueInt(tp,"shadowoffset",(uint32_t *)(chardef + CD_SIZE_SHADOWOFFSET));
          i2 = TPGroupSeek(tp,"Velocity");
          i2 = i2 + 1;
          if (i2 == 0) {
            s = g + G_ERRMSG;
            pc3 = "Can\'t access Velocity constants";
            chardef = stale_EDX_07;
          }
          else {
            TPGetValueFloat(tp,"walk.fwd",(float *)(chardef + CD_VELOCITY_WALK_FWD));
            TPGetValueFloat(tp,"walk.back",(float *)(chardef + CD_VELOCITY_WALK_BACK));
            TPGetValueFloat(tp,"walk.up",(float *)(chardef + CD_VELOCITY_WALK_UP));
            pf4 = (float *)(chardef + 0x111c);
            pc3 = "walk.down";
            TPGetValueFloat(tp,"walk.down",pf4);
            TPScanf(tp,"run.fwd","%f,%f",chardef + 0x1120,chardef + 0x1124,pc3,pf4,i2)
            ;
            TPScanf(tp,"run.back","%f,%f",chardef + 0x1128,chardef + 0x112c);
            TPScanf(tp,"run.up","%f,%f",chardef + 0x1138,chardef + 0x113c);
            TPScanf(tp,"run.down","%f,%f",chardef + 0x1130,chardef + 0x1134);
            TPScanf(tp,"jump.neu","%f,%f",chardef + 0x1144,chardef + 0x1140);
            TPScanf(tp,"jump.fwd","%f",chardef + 0x1148);
            TPScanf(tp,"jump.back","%f",chardef + 0x114c);
            TPScanf(tp,"jump.down","%f",chardef + 0x1154);
            TPScanf(tp,"jump.up","%f",chardef + 0x1150);
            *(uint32_t *)(chardef + CD_VELOCITY_AIRJUMP_NEU_0) = *(uint32_t *)(chardef + CD_VELOCITY_JUMP_NEU_0);
            *(uint32_t *)(chardef + CD_VELOCITY_AIRJUMP_NEU_1) = *(uint32_t *)(chardef + CD_VELOCITY_JUMP_NEU_1);
            *(uint32_t *)(chardef + CD_VELOCITY_RUNJUMP_FWD_0) = *(uint32_t *)(chardef + CD_VELOCITY_JUMP_FWD);
            *(uint32_t *)(chardef + CD_VELOCITY_AIRJUMP_FWD) = *(uint32_t *)(chardef + CD_VELOCITY_JUMP_FWD);
            *(uint32_t *)(chardef + CD_VELOCITY_RUNJUMP_BACK) = *(uint32_t *)(chardef + CD_VELOCITY_JUMP_BACK);
            *(uint32_t *)(chardef + CD_VELOCITY_AIRJUMP_BACK) = *(uint32_t *)(chardef + CD_VELOCITY_JUMP_BACK);
            *(uint32_t *)(chardef + CD_VELOCITY_RUNJUMP_UP) = *(uint32_t *)(chardef + CD_VELOCITY_JUMP_UP);
            *(uint32_t *)(chardef + CD_VELOCITY_AIRJUMP_UP) = *(uint32_t *)(chardef + CD_VELOCITY_JUMP_UP);
            *(uint32_t *)(chardef + CD_VELOCITY_RUNJUMP_DOWN) = *(uint32_t *)(chardef + CD_VELOCITY_JUMP_DOWN);
            *(uint32_t *)(chardef + CD_VELOCITY_AIRJUMP_DOWN) = *(uint32_t *)(chardef + CD_VELOCITY_JUMP_DOWN);
            TPScanf(tp,"runjump.fwd","%f,%f",chardef + 0x115c,chardef + 0x1158);
            TPScanf(tp,"runjump.back","%f",chardef + 0x1160);
            TPScanf(tp,"runjump.down","%f",chardef + 0x1168);
            TPScanf(tp,"runjump.up","%f",chardef + 0x1164);
            TPScanf(tp,"airjump.neu","%f,%f",chardef + 0x1178,chardef + 0x1174);
            TPScanf(tp,"airjump.fwd","%f",chardef + 0x117c);
            TPScanf(tp,"airjump.back","%f",chardef + 0x1180);
            TPScanf(tp,"airjump.down","%f",chardef + 0x1188);
            TPScanf(tp,"airjump.up","%f",chardef + 0x1184);
            i2 = TPGroupSeek(tp,"Movement");
            if (i2 == -1) {
              s = g + G_ERRMSG;
              pc3 = "Can\'t access Movement constants";
            }
            else {
              b1 = TPGetValueFloat(tp,"yaccel",(float *)(chardef + CD_MOVEMENT_YACCEL));
              if (((ZEXT8(b1) != 0) &&
                  (b1 = TPGetValueFloat(tp,"stand.friction",(float *)(chardef + CD_MOVEMENT_STAND_FRICTION)),
                  ZEXT8(b1) != 0)) &&
                 (b1 = TPGetValueFloat(tp,"crouch.friction",(float *)(chardef + CD_MOVEMENT_CROUCH_FRICTION)),
                 ZEXT8(b1) != 0)) {
                TPGetValueInt(tp,"airjump.num",(uint32_t *)(chardef + CD_MOVEMENT_AIRJUMP_NUM));
                TPGetValueInt(tp,"airjump.height",(uint32_t *)(chardef + CD_MOVEMENT_AIRJUMP_HEIGHT));
                return 1;
              }
              s = g + G_ERRMSG;
              pc3 = "Can\'t load movement constants";
            }
          }
        }
      }
    }
  }
  sprintf((char *)s,pc3,chardef,chardef);
  return 0;
}

/* PlayerSTLoadTP @ 0x080aeca0, 39 bytes
 *
 * Reads a character's main state file into a new state table
 * (SctrlReadFileTP).
 *
 * Parameters:
 *   player       int
 *   tp           int
 *
 * Calls: SctrlReadFileTP
 * Called by: PlayerDefLoadPtr, PlayerDefLoadZip
 *
 * Elecbyte file: src/mugen/p-make.c
 */
bool PlayerSTLoadTP(int player,int tp)

{
  int *pi1;
  
  pi1 = SctrlReadFileTP(tp,player);
  *(int **)(player + 0x11c4) = pi1;
  return pi1 != (int *)0x0;
}

/* PlayerSTLoadAppend @ 0x080aecd0, 75 bytes
 *
 * Reads another state file (st1.., stcommon) and adds its states to the
 * character's table.
 *
 * Parameters:
 *   player       int
 *   filename     char *
 *
 * Calls: TPReadFile, SctrlAddFileTP, TPFree
 * Called by: PlayerDefLoadPtr, PlayerDefLoadZip
 *
 * Elecbyte file: src/mugen/p-make.c
 */
uint32_t PlayerSTLoadAppend(int player,char *filename)

{
  uint32_t *tp;
  int i2;
  
  tp = TPReadFile(filename);
  if ((tp != (uint32_t *)0x0) &&
     (i2 = SctrlAddFileTP(*(int **)(player + 0x11c4),(int)tp,player), i2 != 0)) {
    TPFree(tp);
    return 1;
  }
  return 0;
}

/* PlayerCMDLoad @ 0x080aed20, 101 bytes
 *
 * Opens and reads a character's .cmd file (PlayerCMDLoadTP). "Can't open
 * file" on failure.
 *
 * Parameters:
 *   filename     char *
 *   arg2         uint32_t *
 *
 * Globals read: errmsg
 * Calls: TPReadFile, PlayerCMDLoadTP, TPFree
 * C library: sprintf
 * Called by: PlayerDefLoadPtr
 * Messages:
 *   "Can\'t open file"
 *
 * Elecbyte file: src/mugen/p-make.c
 */
uint32_t PlayerCMDLoad(char *filename,uint32_t *arg2)

{
  uint32_t *tp;
  uint32_t u2;
  int i3;
  uint32_t stale_ECX;
  
  tp = TPReadFile(filename);
  if (tp == (uint32_t *)0x0) {
    sprintf((char *)(g + G_ERRMSG),"Can\'t open file",stale_ECX,stale_ECX);
    u2 = 0;
  }
  else {
    i3 = PlayerCMDLoadTP((uint32_t)tp,arg2);
    if (i3 == 0) {
      u2 = 0;
    }
    else {
      TPFree(tp);
      u2 = 1;
    }
  }
  return u2;
}

/* PlayerCMDLoadTP @ 0x080aed90, 1648 bytes
 *
 * Reads a .cmd file. "[Defaults]" gives command.time and
 * command.buffer.time; "[Remap]" gives the button remapping. Each
 * "[Command]" group gives name (quoted), command (the key sequence,
 * ParseCMD), time and buffer.time. Commands with the same name share one
 * label. Errors: "Need at least 1 command", "Command %i missing name
 * parameter", "Command %i name not in quotes", "Player has too many
 * commands. Only %i unique commands labels allowed."
 *
 * Parameters:
 *   tp           uint32_t
 *   arg2         uint32_t *
 *
 * Text keys read: [defaults], "command.time", "command.buffer.time",
 *                 [remap], "name", "command", "time", "buffer.time"
 * Globals read: errmsg
 * Calls: TPGroupSeek, TPGetValueInt, TPGetValue, TPGroupMatchCount,
 *        ecalloc, TPGroupScanFirst, strimatch, TPGroupScanNext, ParseCMD
 * C library: sprintf, malloc, strlen, strncpy, strncmp, strcat
 * Called by: PlayerCMDLoad, PlayerDefLoadZip
 * Messages:
 *   "Need at least 1 command"
 *   "Command %i missing name parameter"
 *   "Command %i name not in quotes"
 *   "Player has too many commands. Only %i unique commands labels
 *     allowed."
 *   "Command %i \"%s\" missing command parameter"
 *   "\nError in command: "
 *
 * Elecbyte file: src/mugen/p-make.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x80 bytes, 7
 *       variables), because their address is taken.
 */
uint32_t PlayerCMDLoadTP(uint32_t tp,uint32_t *arg2)

{
  char *value;
  uint32_t count;
  uint32_t *pu3;
  uint8_t *value2;
  size_t s4;
  int *pi5;
  void *pv6;
  uint32_t u7;
  size_t s8;
  int i9;
  uint32_t stale_EDX;
  uint32_t u10;
  void **ppv11;
  uint8_t *pb12;
  int *pi13;
  uint8_t *pb14;
  bool b15;
  bool b16;
  unsigned char frame[0x80] __attribute__((aligned(16)));
#define stk_74 (*(uint32_t *)(frame + 0xc))
#define stk_6c (*(uint32_t *)(frame + 0x14))
#define stk_68 (*(int *)(frame + 0x18))
#define stk_64 (*(uint32_t *)(frame + 0x1c))
#define stk_60 (*(uint32_t *)(frame + 0x20))
#define stk_5c (*(uint32_t (*)[8])(frame + 0x24))
#define stk_3c (*(int (*)[11])(frame + 0x44))
  
  stk_6c = 1;
  pi5 = &INT_08287d24;
  pi13 = stk_3c;
  for (i9 = 7; i9 != 0; i9 = i9 + -1) {
    *pi13 = *pi5;
    pi5 = pi5 + 1;
    pi13 = pi13 + 1;
  }
  ppv11 = &d_08287d40;
  pu3 = stk_5c;
  for (i9 = 7; i9 != 0; i9 = i9 + -1) {
    *pu3 = *ppv11;
    ppv11 = ppv11 + 1;
    pu3 = pu3 + 1;
  }
  stk_64 = 0xf;
  stk_60 = 1;
  i9 = TPGroupSeek(tp,"defaults");
  if (i9 != -1) {
    TPGetValueInt(tp,"command.time",&stk_64);
    if ((int)stk_64 < 1) {
      stk_64 = 1;
    }
    TPGetValueInt(tp,"command.buffer.time",&stk_60);
    if ((int)stk_60 < 1) {
      stk_60 = 1;
    }
    if (0x1e < (int)stk_60) {
      stk_60 = 0x1e;
    }
  }
  i9 = TPGroupSeek(tp,"remap");
  if (i9 != -1) {
    stk_68 = 0;
    do {
      value = TPGetValue(tp,(char *)stk_5c[stk_68]);
      if (value != (char *)0x0) {
        switch(*value) {
        case 'a':
          stk_3c[stk_68] = 0x10;
          break;
        case 'b':
          stk_3c[stk_68] = 0x20;
          break;
        case 'c':
          stk_3c[stk_68] = 0x40;
          break;
        default:
          stk_3c[stk_68] = 1;
          break;
        case 's':
          stk_3c[stk_68] = 0x400;
          break;
        case 'x':
          stk_3c[stk_68] = 0x80;
          break;
        case 'y':
          stk_3c[stk_68] = 0x100;
          break;
        case 'z':
          stk_3c[stk_68] = 0x200;
        }
      }
      stk_68 = stk_68 + 1;
    } while (stk_68 < 7);
  }
  count = TPGroupMatchCount(tp,"command");
  arg2[2] = count;
  u7 = tp;
  if (count == 0) {
    pi5 = g + G_ERRMSG;
    value = "Need at least 1 command";
L_080af160:
    sprintf((char *)pi5,value,tp,u7);
  }
  else {
    count = ecalloc(1,count * 0x18);
    *arg2 = count;
    if (count != 0) {
      pu3 = malloc(arg2[2] << 2);
      arg2[1] = (uint32_t)pu3;
      if (pu3 != (uint32_t *)0x0) {
        for (count = arg2[2] & 0x3fffffff; count != 0; count = count - 1) {
          *pu3 = 0;
          pu3 = pu3 + 1;
        }
        i9 = TPGroupScanFirst(tp);
        stk_68 = 0;
        if (0 < (int)arg2[2]) {
          stk_74 = 0;
          do {
            while (i9 = strimatch((char *)(i9 + 1),"command"), i9 == 0) {
              i9 = TPGroupScanNext(tp);
            }
            value2 = (uint8_t *)TPGetValue(tp,"name");
            if (value2 == (uint8_t *)0x0) {
              value = "Command %i missing name parameter";
              u7 = stale_EDX;
L_080af15b:
              tp = stk_68 + 1;
              pi5 = g + G_ERRMSG;
              goto L_080af160;
            }
            if ((*value2 != 0x22) || (s4 = strlen((char *)value2), value2[s4 - 1] != 0x22)) {
              value = "Command %i name not in quotes";
              goto L_080af15b;
            }
            s4 = strlen((char *)value2);
            pv6 = malloc(s4 - 1);
            *(void **)(arg2[1] + stk_68 * 4) = pv6;
            if (pv6 == (void *)0x0) {
              return 0;
            }
            s4 = strlen((char *)value2);
            strncpy(*(char **)(arg2[1] + stk_68 * 4),(char *)(value2 + 1),s4 - 2);
            u7 = arg2[1];
            s4 = strlen((char *)value2);
            u7 = *(uint32_t *)(u7 + stk_68 * 4);
            b15 = CARRY4(s4,u7);
            *(uint8_t *)(s4 + u7 + -2) = 0;
            count = *arg2;
            *(uint32_t *)(count + 0x10 + stk_74) = stk_6c;
            u10 = stk_6c + 1;
            b16 = u10 == 0;
            *(uint32_t *)(count + 0x14 + stk_74) = 1;
            i9 = 0xb;
            pb12 = value2;
            pb14 = (uint8_t *)"\"recovery\"";
            do {
              if (i9 == 0) break;
              i9 = i9 + -1;
              b15 = *pb12 < *pb14;
              b16 = *pb12 == *pb14;
              pb12 = pb12 + 1;
              pb14 = pb14 + 1;
            } while (b16);
            u7 = (uint32_t)b15;
            if ((!b15 && !b16) == b15) {
              *(uint32_t *)(count + 0x10 + stk_74) = 0;
              *(uint32_t *)(count + 0x14 + stk_74) = 2;
              u7 = stk_74;
            }
            else {
              i9 = stk_68 + -1;
              if (-1 < i9) {
                count = arg2[1];
                do {
                  s4 = strlen((char *)value2);
                  u7 = strncmp((char *)(value2 + 1),*(char **)(count + i9 * 4),s4 - 2);
                  if (u7 == 0) {
                    s4 = strlen(*(char **)(count + i9 * 4));
                    s8 = strlen((char *)value2);
                    u7 = s8 - 2;
                    if (s4 == u7) {
                      u7 = *arg2;
                      *(uint32_t *)(u7 + 0x10 + stk_74) =
                           *(uint32_t *)(u7 + 0x10 + i9 * 0x18);
                      u10 = stk_6c;
                      break;
                    }
                  }
                  i9 = i9 + -1;
                } while (-1 < i9);
              }
            }
            stk_6c = u10;
            if (0x7f < (int)stk_6c) {
              tp = 0x80;
              pi5 = g + G_ERRMSG;
              value = "Player has too many commands. Only %i unique commands labels allowed.";
              goto L_080af160;
            }
            value = TPGetValue(tp,"command");
            if (value == (char *)0x0) {
              u7 = *(uint32_t *)(arg2[1] + stk_68 * 4);
              value = "Command %i \"%s\" missing command parameter";
              goto L_080af15b;
            }
            u7 = *arg2;
            i9 = ParseCMD((int *)(stk_74 + u7),value,stk_3c);
            if (i9 == 0) {
              strcat((char *)(g + G_ERRMSG),"\nError in command: ");
              strcat((char *)(g + G_ERRMSG),*(char **)(arg2[1] + stk_68 * 4));
              return 0;
            }
            count = *arg2;
            *(uint32_t *)(count + 8 + stk_74) = stk_64;
            TPGetValueInt(tp,"time",(uint32_t *)(stk_74 + 8 + count));
            count = *arg2;
            *(uint32_t *)(count + 0xc + stk_74) = stk_60;
            TPGetValueInt(tp,"buffer.time",(uint32_t *)(stk_74 + 0xc + count));
            if (0x1e < *(int *)(*arg2 + 0xc + stk_74)) {
              *(uint32_t *)(*arg2 + 0xc + stk_74) = 0x1e;
            }
            i9 = TPGroupScanNext(tp);
            stk_74 = stk_74 + 0x18;
            stk_68 = stk_68 + 1;
          } while (stk_68 < (int)arg2[2]);
        }
        arg2[3] = stk_6c;
        return 1;
      }
    }
  }
  return 0;
}
#undef stk_74
#undef stk_6c
#undef stk_68
#undef stk_64
#undef stk_60
#undef stk_5c
#undef stk_3c

/* ParseCMD @ 0x080af400, 629 bytes
 *
 * Compiles a command key sequence ("~D, DF, F, x") into an array of command
 * elements (ParseCMDElem for each comma-separated part). Returns the number
 * of elements.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         char *
 *   arg3         uint32_t *
 *
 * Calls: ParseCMDElem, ecalloc
 * Called by: PlayerCMDLoadTP
 *
 * Elecbyte file: src/mugen/p-make.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x840 bytes,
 *       5 variables), because their address is taken.
 */
uint32_t ParseCMD(int *arg1,char *arg2,uint32_t *arg3)

{
  uint32_t u1;
  int i2;
  uint32_t u3;
  char c4;
  int mem;
  uint32_t *pu6;
  bool b7;
  unsigned char frame[0x840] __attribute__((aligned(16)));
#define stk_834 (*(uint32_t *)(frame + 0xc))
#define stk_830 (*(uint32_t *)(frame + 0x10))
#define stk_82c (*(int *)(frame + 0x14))
#define stk_828 (*(uint32_t *)(frame + 0x18))
#define stk_824 (*(uint32_t (*)[517])(frame + 0x1c))
  
  mem = 0;
  stk_82c = 0;
  pu6 = stk_824 + 2;
  for (i2 = 0x200; i2 != 0; i2 = i2 + -1) {
    *pu6 = 0;
    pu6 = pu6 + 1;
  }
  c4 = *arg2;
  while (c4 != '\0') {
    stk_830 = 0;
    i2 = 0;
    if (((*(uint8_t *)(__ctype_b + 1 + arg2[mem] * 2) & 0x20) != 0) && (c4 != '\0')) {
      do {
        mem = mem + 1;
        if ((*(uint8_t *)(__ctype_b + 1 + arg2[mem] * 2) & 0x20) == 0) {
          c4 = arg2[mem];
          goto L_080af478;
        }
      } while (arg2[mem] != '\0');
      c4 = '\0';
    }
L_080af478:
    if (c4 == '\0') goto L_080af630;
    b7 = c4 == '>';
    if (b7) {
      mem = mem + 1;
      c4 = arg2[mem];
    }
    stk_834 = (uint32_t)b7;
    if (c4 == '/') {
      mem = mem + 1;
      stk_830 = 0x20000;
      c4 = arg2[mem];
    }
    if (c4 == '~') {
      while( true ) {
        mem = mem + 1;
        c4 = arg2[mem];
        if (9 < (uint8_t)(c4 - 0x30U)) break;
        i2 = arg2[mem] + -0x30 + i2 * 10;
      }
      stk_830 = stk_830 | 0x10000 | (i2 >> 2) << 0x16;
    }
    if (c4 == '$') {
      mem = mem + 1;
      stk_830 = stk_830 | 0x40000;
    }
    stk_824[0] = 0;
    stk_824[1] = 0;
    c4 = arg2[mem];
    do {
      if (c4 == '+') {
        mem = mem + 1;
      }
      i2 = ParseCMDElem(arg2 + mem,&stk_828,arg3);
      if (i2 == 0) goto L_080af630;
      u3 = stk_828 | stk_824[0];
      mem = mem + i2;
      c4 = arg2[mem];
      stk_824[0] = u3;
    } while (c4 == '+');
    stk_824[0] = u3 | stk_830;
    stk_824[1] = stk_824[1] | stk_834;
    if (((0 < stk_82c) && (stk_824[0] == stk_824[stk_82c * 2])) && ((u3 & 0x8f000) != 0))
    {
      stk_824[stk_82c * 2 + 2] = stk_824[stk_82c * 2];
      stk_824[stk_82c * 2 + 3] = stk_824[stk_82c * 2 + 1];
      stk_824[stk_82c * 2 + 2] = stk_824[stk_82c * 2 + 2] | 0x10000;
      stk_824[stk_82c * 2 + 3] = stk_824[stk_82c * 2 + 3] | 1;
      stk_82c = stk_82c + 1;
      stk_824[1] = stk_824[1] | 1;
    }
    stk_824[stk_82c * 2 + 3] = stk_824[1];
    stk_824[stk_82c * 2 + 2] = stk_824[0];
    stk_82c = stk_82c + 1;
    if (0x100 < stk_82c) goto L_080af630;
    for (; (c4 = arg2[mem], c4 != ',' && (c4 != '\0')); mem = mem + 1) {
    }
    if (c4 == '\0') break;
    mem = mem + 1;
    c4 = arg2[mem];
  }
  mem = ecalloc(1,stk_82c << 3);
  *arg1 = mem;
  if (mem == 0) {
L_080af630:
    u1 = 0;
  }
  else {
    i2 = 0;
    if (0 < stk_82c) {
      do {
        u3 = stk_824[i2 * 2 + 2];
        *(uint32_t *)(mem + 4 + i2 * 8) = stk_824[i2 * 2 + 3];
        *(uint32_t *)(mem + i2 * 8) = u3;
        i2 = i2 + 1;
      } while (i2 < stk_82c);
    }
    arg1[1] = stk_82c;
    u1 = 1;
  }
  return u1;
}
#undef stk_834
#undef stk_830
#undef stk_82c
#undef stk_828
#undef stk_824

/* ParseCMDElem @ 0x080af680, 249 bytes
 *
 * Compiles one element of a command sequence into command bits and
 * modifiers: '~' release (with optional charge time), '/' hold, '$'
 * direction only, '>' strict order, '+' simultaneous keys, and the direction
 * and button names.
 *
 * Parameters:
 *   arg1         uint8_t *
 *   arg2         uint32_t *
 *   arg3         uint32_t *
 *
 * Called by: ParseCMD
 *
 * Elecbyte file: src/mugen/p-make.c
 */
uint32_t ParseCMDElem(uint8_t *arg1,uint32_t *arg2,uint32_t *arg3)

{
  uint32_t u1;
  
  u1 = 1;
  switch(*arg1) {
  case 0x42:
    *arg2 = 0x8000;
    break;
  default:
    u1 = 0;
    break;
  case 0x44:
    if (arg1[1] == 'B') {
      *arg2 = 0xc000;
      u1 = 2;
    }
    else if (arg1[1] == 'F') {
      *arg2 = 0x6000;
      u1 = 2;
    }
    else {
      *arg2 = 0x4000;
    }
    break;
  case 0x46:
    *arg2 = 0x2000;
    break;
  case 0x4e:
    *arg2 = 0x80000;
    break;
  case 0x55:
    if (arg1[1] == 'B') {
      *arg2 = 0x9000;
      u1 = 2;
    }
    else if (arg1[1] == 'F') {
      *arg2 = 0x3000;
      u1 = 2;
    }
    else {
      *arg2 = 0x1000;
    }
    break;
  case 0x61:
    *arg2 = *arg3;
    break;
  case 0x62:
    *arg2 = arg3[1];
    break;
  case 99:
    *arg2 = arg3[2];
    break;
  case 0x73:
    *arg2 = arg3[6];
    break;
  case 0x78:
    *arg2 = arg3[3];
    break;
  case 0x79:
    *arg2 = arg3[4];
    break;
  case 0x7a:
    *arg2 = arg3[5];
  }
  return u1;
}

/* CmdSetFreeLabel @ 0x080af780, 33 bytes
 *
 * Frees a command set's label strings.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: StringArrayFree
 * Called by: CmdSetDeInit, PlayerDefLoadPtr, PlayerDefLoadZip
 *
 * Elecbyte file: src/mugen/p-make.c
 */
void CmdSetFreeLabel(int arg1)

{
  StringArrayFree(*(void **)(arg1 + 4),*(int *)(arg1 + 8));
  *(uint32_t *)(arg1 + 4) = 0;
  return;
}

/* StringArrayFree @ 0x080af7b0, 68 bytes
 *
 * Frees `count` strings of a string array and the array.
 *
 * Parameters:
 *   arg1         void *
 *   arg2         int
 *
 * C library: free
 * Called by: CmdSetFreeLabel
 *
 * Elecbyte file: src/mugen/p-make.c
 */
void StringArrayFree(void *arg1,int arg2)

{
  void *ptr;
  int i2;
  
  if (arg1 != (void *)0x0) {
    i2 = 0;
    if (0 < arg2) {
      do {
        ptr = *(void **)((int)arg1 + i2 * 4);
        if (ptr != (void *)0x0) {
          free(ptr);
        }
        i2 = i2 + 1;
      } while (i2 < arg2);
    }
    free(arg1);
    return;
  }
  return;
}

/* CmdSetDeInit @ 0x080af800, 100 bytes
 *
 * Frees a command set: labels and command element arrays.
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: CmdSetFreeLabel
 * C library: free
 * Called by: PlayerRCFree
 *
 * Elecbyte file: src/mugen/p-make.c
 */
void CmdSetDeInit(int *arg1)

{
  void *ptr;
  int i1;
  int i2;
  int i3;
  
  if (arg1 == (int *)0x0) {
    return;
  }
  i2 = *arg1;
  if (i2 != 0) {
    i3 = 0;
    i1 = arg1[2];
    if (0 < i1) {
      while( true ) {
        ptr = *(void **)(i2 + i3 * 0x18);
        if (ptr != (void *)0x0) {
          free(ptr);
          i1 = arg1[2];
        }
        i3 = i3 + 1;
        if (i1 <= i3) break;
        i2 = *arg1;
      }
    }
    free((void *)*arg1);
  }
  CmdSetFreeLabel((int)arg1);
  return;
}

/* PlayerRCFree @ 0x080af870, 116 bytes
 *
 * Frees a chardef's resources: AI data, commands, states, sprites,
 * animations and sounds.
 *
 * Parameters:
 *   arg1         void *
 *
 * Calls: AIStateSetDeInit, CmdSetDeInit, SCtrlRCFree, SpriteArrayFree,
 *        AnimRCFree, SndArrayFree
 * C library: free
 * Called by: PlayerCacheClear, PlayerCacheLoad
 *
 * Elecbyte file: src/mugen/p-make.c
 */
void PlayerRCFree(void *arg1)

{
  if (arg1 != (void *)0x0) {
    AIStateSetDeInit((uint32_t *)((int)arg1 + 0x21d8));
    CmdSetDeInit((int *)((int)arg1 + 0x11b4));
    SCtrlRCFree(*(uint32_t **)((int)arg1 + 0x11c4));
    SpriteArrayFree(*(int **)((int)arg1 + 0x11c8));
    AnimRCFree(*(int **)((int)arg1 + 0x11cc));
    SndArrayFree(*(uint32_t **)((int)arg1 + 0x11d4));
    free(arg1);
    return;
  }
  return;
}

/* PlayerNew @ 0x080af8f0, 969 bytes
 *
 * Creates a player record for a chardef: allocates it, gives it an instance
 * of the character's sprites (own palettes), an animation instance, a
 * projectile array, the state machine pointers, key buffers, the AI state, a
 * debug clipboard and the target list. AI-controlled players get the ramped
 * AI level (GetRampedAILevel). Errors: "Out of memory for player.", "Out of
 * memory for sprite", "Out of memory for anim".
 *
 * Parameters:
 *   chardef      int
 *
 * Player fields written: ishelper, id, teammode, anim, projectiles,
 *                        targets
 * Globals read: errmsg, next_player_id, playerpalmax
 * CharDef fields: data_life
 * Calls: ecalloc, SpriteArrayNewSize, SpriteArrayNewInstanceOnto,
 *        SpriteArrayNewInstance, AnimNew, ProjArrayNew, SCtrlInit,
 *        PlayerAIInit, GetRampedAILevel, PlayerAISetLevel, AIStateSetCopy,
 *        ArrayNew, ClipboardNew, PlayerReset
 * C library: strcpy, sprintf
 * Called by: GameLoadAndCreateChars, GameLoadStage
 * Messages:
 *   "Out of memory for player."
 *   "Out of memory for sprite\n"
 *   "Out of memory for anim\n"
 *   "Can\'t create projectile array."
 *   "Can\'t create state controller."
 *   "Can\'t create target array."
 *
 * Elecbyte file: src/mugen/p-make.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 */
int * PlayerNew(int chardef)

{
  int *player;
  uint32_t *anim;
  int *clipboard;
  int *stale_ECX;
  int mem;
  int *stale_ECX_00;
  int *stale_ECX_01;
  int *stale_EDX;
  int *stale_EDX_00;
  int *saved_EDI;
  char *format;
  
  player = (int *)ecalloc(1,0x3464);
  if (player == (int *)0x0) {
    clipboard = g + G_ERRMSG;
    format = "Out of memory for player.";
    saved_EDI = stale_ECX;
  }
  else {
    player[PL_ISHELPER] = (uint32_t)(chardef == 0);
    *player = chardef;
    if (chardef != 0) {
      player[0x259] = chardef + 0x11b4;
    }
    clipboard = g;
    player[PL_ID] = g[G_NEXT_PLAYER_ID];
    clipboard[0x749d] = clipboard[0x749d] + 1;
    player[PL_TEAMMODE] = -1;
    if (chardef != 0) {
      clipboard = (int *)(chardef + CD_DATA_LIFE);
      saved_EDI = player + 0x14;
      for (mem = 0x42; mem != 0; mem = mem + -1) {
        *saved_EDI = *clipboard;
        clipboard = clipboard + 1;
        saved_EDI = saved_EDI + 1;
      }
    }
    anim = SpriteArrayNewSize(0,g[G_PLAYERPALMAX]);
    player[0x4ec] = (int)anim;
    if (anim == (uint32_t *)0x0) {
      clipboard = g + G_ERRMSG;
      format = "Out of memory for sprite\n";
      saved_EDI = player;
    }
    else {
      if (chardef == 0) {
        player[0x4ee] = 0;
      }
      else {
        clipboard = SpriteArrayNewInstanceOnto((int *)player[0x4ec],*(int **)(chardef + 0x11c8));
        if (clipboard == (int *)0x0) {
          clipboard = g + G_ERRMSG;
          format = "Out of memory for sprite\n";
          goto L_080afc20;
        }
        clipboard = SpriteArrayNewInstance((int *)player[0x4ec]);
        player[0x4ee] = (int)clipboard;
        if (clipboard == (int *)0x0) {
          clipboard = g + G_ERRMSG;
          format = "Out of memory for sprite\n";
          saved_EDI = player;
          goto L_080afc20;
        }
      }
      player[0x4eb] = player[0x4ec];
      player[0x4ed] = player[0x4ee];
      if (chardef == 0) {
        anim = AnimNew(0,0);
        player[PL_ANIM] = (int)anim;
        if (anim == (uint32_t *)0x0) {
          clipboard = g + G_ERRMSG;
          format = "Out of memory for anim\n";
          saved_EDI = stale_ECX_00;
          goto L_080afc20;
        }
      }
      else {
        anim = AnimNew(*(uint32_t *)(chardef + 0x11cc),player[0x4ec]);
        player[PL_ANIM] = (int)anim;
        if (anim == (uint32_t *)0x0) {
          clipboard = g + G_ERRMSG;
          format = "Out of memory for anim\n";
          goto L_080afc20;
        }
      }
      clipboard = g;
      *(int *)(player[PL_ANIM] + 0x30) = g[0x413d];
      if (chardef == 0) {
        mem = ProjArrayNew(clipboard[0x7576],0,0);
        player[PL_PROJECTILES] = mem;
        if (mem == 0) {
          clipboard = g + G_ERRMSG;
          format = "Can\'t create projectile array.";
          goto L_080afc20;
        }
      }
      else {
        saved_EDI = *(int **)(chardef + 0x11cc);
        mem = ProjArrayNew(clipboard[0x7576],saved_EDI,player[0x4ed]);
        player[PL_PROJECTILES] = mem;
        if (mem == 0) {
          clipboard = g + G_ERRMSG;
          format = "Can\'t create projectile array.";
          saved_EDI = stale_ECX_01;
          goto L_080afc20;
        }
      }
      if (chardef == 0) {
        mem = SCtrlInit(player + 0x2fa,0);
        if (mem == 0) {
          clipboard = g + G_ERRMSG;
          format = "Can\'t create state controller.";
          goto L_080afc20;
        }
      }
      else {
        mem = SCtrlInit(player + 0x2fa,*(uint32_t *)(chardef + 0x11c4));
        if (mem == 0) {
          clipboard = g + G_ERRMSG;
          format = "Can\'t create state controller.";
          saved_EDI = stale_EDX;
          goto L_080afc20;
        }
      }
      if (chardef != 0) {
        mem = PlayerAIInit((int)player,1);
        if (mem == 0) {
          clipboard = g + G_ERRMSG;
          format = "Can\'t create state controller.";
          saved_EDI = player;
          goto L_080afc20;
        }
        mem = GetRampedAILevel();
        PlayerAISetLevel((int)player,mem);
        if (player[0xb6b] != 0) {
          AIStateSetCopy((int)(player + 0xb6c),chardef + 0x21d8);
        }
      }
      anim = ArrayNew(8,0x20,0);
      player[PL_TARGETS] = (int)anim;
      if (anim != (uint32_t *)0x0) {
        mem = ecalloc(g[0x7395] + 1,4);
        player[0x455] = mem;
        if (mem == 0) {
          return (int *)0x0;
        }
        mem = ecalloc(g[0x7395] + 1,4);
        player[0x452] = mem;
        if (mem == 0) {
          return (int *)0x0;
        }
        if ((char *)*player != (char *)0x0) {
          strcpy((char *)(player + 8),(char *)*player);
        }
        clipboard = ClipboardNew(0x4d,3);
        player[0xd17] = (int)clipboard;
        if (clipboard == (int *)0x0) {
          return (int *)0x0;
        }
        PlayerReset(player);
        return player;
      }
      clipboard = g + G_ERRMSG;
      format = "Can\'t create target array.";
      saved_EDI = stale_EDX_00;
    }
  }
L_080afc20:
  sprintf((char *)clipboard,format,saved_EDI,saved_EDI);
  return (int *)0x0;
}

/* GetRampedAILevel @ 0x080afcc0, 257 bytes
 *
 * Returns the AI level for the current match, clamped to 1..8. It starts
 * from the difficulty setting (4 in survival co-op). In arcade, team and
 * survival runs it adds a ramp interpolated between a start and an end value
 * over a range of match (or round) numbers, using the motif's
 * arcade/team/survival ramp settings.
 *
 * Globals read: difficulty, slct_coop_side, round_no
 * Called by: PlayerNew
 *
 * Elecbyte file: src/mugen/p-make.c
 */
int GetRampedAILevel(void)

{
  int i1;
  int i2;
  int *pi3;
  int i4;
  int i5;
  
  pi3 = (int *)0x0;
  i2 = g[0x7543] + -1;
  i5 = g[G_DIFFICULTY];
  if (g[0x33b3] != 0) {
    pi3 = g + 0x7580;
    i4 = 2 - g[0x33b3];
    if ((g[i4 * 0x6a7 + 0x33bb] != 0) || (1 < g[i4 * 0x6a7 + 0x33b9])) {
      pi3 = g + 0x7584;
    }
  }
  if (g[G_SLCT_COOP_SIDE] != 0) {
    pi3 = g + 0x7588;
    i5 = 4;
    i2 = g[G_ROUND_NO];
  }
  if (pi3 != (int *)0x0) {
    i4 = *pi3;
    if (i4 < i2) {
      i1 = pi3[2];
      if (i2 < i1) {
        if (i4 < i1) {
          i5 = i5 + ((i2 - i4) * (pi3[3] - pi3[1])) / (i1 - i4) + pi3[1];
        }
      }
      else {
        i5 = i5 + pi3[3];
      }
    }
    else {
      i5 = i5 + pi3[1];
    }
    if (i5 < 1) {
      i5 = 1;
    }
    if (8 < i5) {
      i5 = 8;
    }
  }
  return i5;
}

/* PlayerChangePal @ 0x080afdd0, 417 bytes
 *
 * Switches a player to palette number `palno` of its character (copied from
 * the root sprite array, SpriteArrayPalRemapFromRoot). "Out of memory for
 * sprite" on failure.
 *
 * Parameters:
 *   player       int
 *   palno        int
 *
 * Calls: SpriteArrayGetNum, SpriteArrayAccess, SpriteArrayPalGetNum,
 *        SpriteArrayPalRemapFromRoot, SpriteArrayNewInstanceOnto,
 *        ErrorExitM
 * Called by: GameLoadAndCreateChars
 * Messages:
 *   "Out of memory for sprite\n"
 *
 * Elecbyte file: src/mugen/p-make.c
 */
uint32_t PlayerChangePal(int player,int palno)

{
  int index;
  int i2;
  int *pi3;
  uint32_t stale_EDX;
  uint32_t stale_EDX_00;
  uint32_t stale_EDX_01;
  uint32_t stale_EDX_02;
  uint32_t stale_EDX_03;
  uint32_t u4;
  int *pi5;
  uint32_t u6;
  
  index = SpriteArrayGetNum(*(int **)(player + 0x13ac),0,0);
  if ((index != -1) && (*(int *)(*(int *)(player + 0x13ac) + 0xc) != 0)) {
    index = SpriteArrayAccess(*(int **)(player + 0x13ac),index);
    index = *(int *)(index + 0x30);
    i2 = SpriteArrayPalGetNum(*(int *)(*(int *)(player + 0x13ac) + 0xc),1,palno);
    if (i2 == -1) {
      i2 = SpriteArrayPalGetNum(*(int *)(*(int *)(player + 0x13ac) + 0xc),1,0);
      if (i2 == -1) {
        i2 = SpriteArrayPalGetNum(*(int *)(*(int *)(player + 0x13ac) + 0xc),0,0);
      }
    }
    if ((index != -1) && (i2 != -1)) {
      SpriteArrayPalRemapFromRoot(*(int *)(player + 0x13ac),index,i2);
    }
  }
  index = SpriteArrayGetNum(*(int **)(player + 0x13ac),9000,0);
  u4 = stale_EDX;
  if ((index != -1) && (*(int *)(*(int *)(player + 0x13ac) + 0xc) != 0)) {
    index = SpriteArrayAccess(*(int **)(player + 0x13ac),index);
    index = *(int *)(index + 0x30);
    i2 = SpriteArrayPalGetNum(*(int *)(*(int *)(player + 0x13ac) + 0xc),1,palno);
    u4 = stale_EDX_00;
    if (i2 == -1) {
      i2 = SpriteArrayPalGetNum(*(int *)(*(int *)(player + 0x13ac) + 0xc),1,0);
      u4 = stale_EDX_01;
      if (i2 == -1) {
        i2 = SpriteArrayPalGetNum(*(int *)(*(int *)(player + 0x13ac) + 0xc),0,0);
        u4 = stale_EDX_02;
      }
    }
    if ((index != -1) && (i2 != -1)) {
      SpriteArrayPalRemapFromRoot(*(int *)(player + 0x13ac),index,i2);
      u4 = stale_EDX_03;
    }
  }
  if (*(int *)(player + 0x13b8) != 0) {
    pi5 = *(int **)(player + 0x13ac);
    u6 = u4;
    pi3 = SpriteArrayNewInstanceOnto(*(int **)(player + 0x13b8),pi5);
    if (pi3 == (int *)0x0) {
      ErrorExitM("Out of memory for sprite\n",pi5,u4,u6);
    }
  }
  return 1;
}

/* PlayerFree @ 0x080aff80, 260 bytes
 *
 * Frees a player record: AI state, clipboard, target and projectile arrays,
 * sprite instance and animation.
 *
 * Parameters:
 *   player       int *
 *
 * Player fields read: targets, projectiles, anim
 * Calls: AIStateSetMerge, ClipboardFree, PlayerAIDeInit, ArrayFree,
 *        ProjArrayFree, SpriteArrayFree, AnimFree
 * C library: free
 * Called by: GameFreeChars, GameUnloadStage
 *
 * Elecbyte file: src/mugen/p-make.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: Returns nothing (the original left only stale register values).
 */
void PlayerFree(int *player)

{
  int i1;
  uint32_t stale_EAX;
  uint32_t saved_EBX;
  
  if (player != (int *)0x0) {
    if (player[0xb6b] != 0) {
      AIStateSetMerge(*player + 0x21d8,(int)(player + 0xb6c));
    }
    if ((uint32_t *)player[0xd17] != (uint32_t *)0x0) {
      ClipboardFree((uint32_t *)player[0xd17]);
    }
    PlayerAIDeInit((int)player);
    ArrayFree((void *)player[PL_TARGETS]);
    ProjArrayFree((uint32_t *)player[PL_PROJECTILES]);
    i1 = player[0x4e5];
    if (i1 != 0) {
      *(uint32_t *)(i1 + 0x18) = 0;
      *(uint32_t *)(i1 + 8) = 0;
      player[0x4e5] = 0;
    }
    if ((int *)player[0x4ee] != (int *)0x0) {
      SpriteArrayFree((int *)player[0x4ee]);
    }
    SpriteArrayFree((int *)player[0x4ec]);
    AnimFree((void *)player[PL_ANIM]);
    if ((void *)player[0x455] != (void *)0x0) {
      free((void *)player[0x455]);
    }
    if ((void *)player[0x452] != (void *)0x0) {
      free((void *)player[0x452]);
    }
    free(player);
    return;
  }
  return;
}

/* PlayerCheck @ 0x080b0090, 569 bytes
 *
 * Checks that a character has the sprites and animations the engine
 * requires. Missing ones are listed in the debug clipboard ("%s (%i) missing
 * required sprites:", "missing required animation actions").
 *
 * Parameters:
 *   arg1         int *
 *
 * Globals read: clipboard
 * Calls: SpriteArrayGetNum, ClipboardAppend, AnimGrpNoToIdx
 * Called by: GameLoadAndCreateChars
 * Messages:
 *   "%s (%i) missing required sprites:\n"
 *   " (more)"
 *   "%s (%i) missing required animation actions:\n"
 *
 * Elecbyte file: src/mugen/p-make.c
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: Locals live in `frame`, laid out as on the original stack (0x320 bytes,
 *       4 variables), because their address is taken.
 */
uint32_t PlayerCheck(int *arg1)

{
  int *clipboard;
  uint32_t *anim;
  int index;
  uint32_t u4;
  int i5;
  uint32_t stale_ECX;
  uint32_t stale_ECX_00;
  uint32_t stale_ECX_01;
  uint32_t stale_EDX;
  int *saved_EBP;
  int *pi6;
  int *pi7;
  int index2;
  char *fmt;
  int *sprites;
  unsigned char frame[0x320] __attribute__((aligned(16)));
#define stk_318 (*(int *)(frame + 0x8))
#define stk_314 (*(int **)(frame + 0xc))
#define stk_30c (*(int (*)[60])(frame + 0x14))
#define stk_21c (*(int (*)[131])(frame + 0x104))
  
  sprites = *(int **)(*arg1 + 0x11c8);
  clipboard = (int *)g[G_CLIPBOARD];
  pi6 = &INT_08287d5c;
  pi7 = stk_21c;
  for (i5 = 0x7f; i5 != 0; i5 = i5 + -1) {
    *pi7 = *pi6;
    pi6 = pi6 + 1;
    pi7 = pi7 + 1;
  }
  pi6 = &INT_08287f58;
  pi7 = stk_30c;
  for (i5 = 0x3a; i5 != 0; i5 = i5 + -1) {
    *pi7 = *pi6;
    pi6 = pi6 + 1;
    pi7 = pi7 + 1;
  }
  stk_314 = (int *)0x0;
  stk_318 = 0;
  u4 = 0;
  if (stk_21c[0] != -1) {
    saved_EBP = (int *)0x4;
    index2 = 4;
    i5 = 0;
    do {
      index = SpriteArrayGetNum(sprites,*(int *)((int)stk_21c + i5),
                                *(int *)((int)stk_21c + index2));
      u4 = stale_ECX;
      if (index == -1) {
        if (stk_314 == (int *)0x0) {
          fmt = "%s (%i) missing required sprites:\n";
          pi6 = arg1 + 8;
          pi7 = (int *)arg1[1];
        }
        else {
          if (7 < (int)stk_314) {
            ClipboardAppend(clipboard," (more)",stale_EDX,stale_EDX);
            u4 = stale_ECX_00;
            break;
          }
          fmt = ", ";
          pi6 = stk_314;
          pi7 = stk_314;
        }
        ClipboardAppend(clipboard,fmt,pi6,pi7);
        ClipboardAppend(clipboard,"%i,%i",*(uint32_t *)(i5 + (int)stk_21c),
                        *(uint32_t *)((int)saved_EBP + (int)stk_21c));
        stk_314 = (int *)((int)stk_314 + 1);
        u4 = stale_ECX_01;
      }
      saved_EBP = saved_EBP + 2;
      index2 = index2 + 8;
      index = i5 + 8;
      i5 = i5 + 8;
    } while (*(int *)((int)stk_21c + index) != -1);
  }
  if (stk_314 != (int *)0x0) {
    ClipboardAppend(clipboard,"\n",u4,u4);
  }
  if (stk_30c[0] != -1) {
    i5 = 0;
    do {
      saved_EBP = (int *)stk_30c[i5];
      anim = (uint32_t *)arg1[0x4ef];
      index2 = AnimGrpNoToIdx(anim,0,(int)saved_EBP);
      if (index2 == -1) {
        if (stk_318 == 0) {
          fmt = "%s (%i) missing required animation actions:\n";
          sprites = arg1 + 8;
          pi6 = (int *)arg1[1];
        }
        else {
          if (7 < stk_318) {
            ClipboardAppend(clipboard," (more)",0,0);
            break;
          }
          fmt = ", ";
          sprites = saved_EBP;
          pi6 = saved_EBP;
        }
        ClipboardAppend(clipboard,fmt,sprites,pi6);
        ClipboardAppend(clipboard,"%i",stk_30c[i5],anim);
        stk_318 = stk_318 + 1;
      }
      i5 = i5 + 1;
    } while (stk_30c[i5] != -1);
  }
  if (stk_318 != 0) {
    ClipboardAppend(clipboard,"\n",saved_EBP,saved_EBP);
  }
  u4 = 0;
  if ((stk_314 == (int *)0x0) && (stk_318 == 0)) {
    u4 = 1;
  }
  return u4;
}
#undef stk_318
#undef stk_314
#undef stk_30c
#undef stk_21c

/* ResetPersistVar @ 0x080b02d0, 17 bytes
 *
 * Clears one player slot's saved variables.
 *
 * Parameters:
 *   arg1         uint32_t *
 *
 * Called by: PlayerSavePersistVars, SurvivalBuildRandomTeam,
 *            TeamResetPersistVars
 *
 * Elecbyte file: src/mugen/p-make.c
 */
void ResetPersistVar(uint32_t *arg1)

{
  int i1;
  
  for (i1 = 100; i1 != 0; i1 = i1 + -1) {
    *arg1 = 0;
    arg1 = arg1 + 1;
  }
  return;
}

/* GameResetPersistVars @ 0x080b02f0, 26 bytes
 *
 * Clears the saved variables of both teams.
 *
 * Calls: TeamResetPersistVars
 * Called by: ContinueScreenLoop, GameMatchReset, GameReloadStage, MainLoop
 *
 * Elecbyte file: src/mugen/p-make.c
 * Note: Returns nothing (the original left only stale register values).
 */
void GameResetPersistVars(void)

{
  uint32_t stale_EAX;
  
  TeamResetPersistVars(0);
  TeamResetPersistVars(1);
  return;
}

/* TeamResetPersistVars @ 0x080b0310, 132 bytes
 *
 * Clears the saved variables of every member of a team.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: ResetPersistVar
 * Called by: GameMatchReset, GameResetPersistVars
 *
 * Elecbyte file: src/mugen/p-make.c
 */
void TeamResetPersistVars(int arg1)

{
  int i1;
  int i2;
  int i3;
  int i4;
  int stk_14;
  
  i3 = 0;
  stk_14 = 0;
  do {
    i2 = 3;
    i4 = 0;
    do {
      i1 = i4 + 0xd05c;
      i4 = i4 + 400;
      ResetPersistVar((uint32_t *)((int)g + i1 + arg1 * 0x1a9c + i3));
      i2 = i2 + -1;
    } while (-1 < i2);
    i3 = i3 + 0x640;
    stk_14 = stk_14 + 1;
  } while (stk_14 < 4);
  return;
}

/* PlayerSavePersistVars @ 0x080b03a0, 111 bytes
 *
 * Saves a player's variables (those from IntPersistIndex / FloatPersistIndex
 * on) so they survive to the next round or match.
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t *
 *
 * Calls: ResetPersistVar
 * Called by: GameFreeChars, GameUnloadStage
 *
 * Elecbyte file: src/mugen/p-make.c
 */
void PlayerSavePersistVars(int arg1,uint32_t *arg2)

{
  int i1;
  uint32_t u2;
  uint32_t *pu3;
  uint32_t *pu4;
  
  ResetPersistVar(arg2);
  i1 = *(int *)(arg1 + 0x150);
  pu3 = (uint32_t *)(arg1 + 0xe40 + i1 * 4);
  pu4 = arg2 + i1;
  for (u2 = 0x3cU - i1 & 0x3fffffff; u2 != 0; u2 = u2 - 1) {
    *pu4 = *pu3;
    pu3 = pu3 + 1;
    pu4 = pu4 + 1;
  }
  i1 = *(int *)(arg1 + 0x154);
  pu3 = (uint32_t *)(arg1 + 0xf30 + i1 * 4);
  pu4 = arg2 + i1 + 0x3c;
  for (u2 = 0x28U - i1 & 0x3fffffff; u2 != 0; u2 = u2 - 1) {
    *pu4 = *pu3;
    pu3 = pu3 + 1;
    pu4 = pu4 + 1;
  }
  return;
}

/* PlayerRestorePersistVars @ 0x080b0410, 85 bytes
 *
 * Restores a player's saved variables.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Called by: GameLoadAndCreateChars
 *
 * Elecbyte file: src/mugen/p-make.c
 */
void PlayerRestorePersistVars(int arg1,int arg2)

{
  uint32_t u1;
  int i2;
  uint32_t *pu3;
  uint32_t *pu4;
  
  i2 = *(int *)(arg1 + 0x150) * 4;
  pu3 = (uint32_t *)(i2 + arg2);
  pu4 = (uint32_t *)(arg1 + 0xe40 + i2);
  for (u1 = 0x3cU - *(int *)(arg1 + 0x150) & 0x3fffffff; u1 != 0; u1 = u1 - 1) {
    *pu4 = *pu3;
    pu3 = pu3 + 1;
    pu4 = pu4 + 1;
  }
  i2 = *(int *)(arg1 + 0x154) * 4;
  pu3 = (uint32_t *)(arg2 + 0xf0 + i2);
  pu4 = (uint32_t *)(arg1 + 0xf30 + i2);
  for (u1 = 0x28U - *(int *)(arg1 + 0x154) & 0x3fffffff; u1 != 0; u1 = u1 - 1) {
    *pu4 = *pu3;
    pu3 = pu3 + 1;
    pu4 = pu4 + 1;
  }
  return;
}

/* GameLoadAndActivateTeam @ 0x080b0470, 226 bytes
 *
 * Loads and creates the active members of a team (GameLoadAndCreateChars),
 * rebuilds the palette groups and switches on AI for computer players. A
 * failure is fatal.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: PalGrpClear, GameFreeChars, ErrorExit, GameLoadAndCreateChars,
 *        PalGrpBuildFight, GameActivateAI
 * Called by: GameMatchReset, GameNextRound
 *
 * Elecbyte file: src/mugen/p-make.c
 */
void GameLoadAndActivateTeam(int arg1)

{
  int i1;
  int *pi2;
  int i3;
  int *pi4;
  
  i3 = -1;
  pi2 = g + arg1 * 0x6a7 + g[arg1 * 0x6a7 + 0x33b8] * 0x17 + 0x33bb;
  PalGrpClear();
  if (g[arg1 + 0x73da] != 0) {
    i3 = *(int *)(g[arg1 + 0x73da] + 0x178);
  }
  i1 = GameFreeChars(arg1);
  if (i1 == 0) {
    ErrorExit();
  }
  i1 = GameLoadAndCreateChars(arg1);
  if (i1 == 0) {
    ErrorExit();
  }
  if ((i3 != -1) && (i1 = g[arg1 + 0x73da], i1 != 0)) {
    *(int *)(i1 + 0x184) = i3;
    *(int *)(i1 + 0x180) = i3;
    *(int *)(i1 + 0x178) = i3;
  }
  PalGrpBuildFight();
  pi4 = g + arg1 * 0x17 + 0x4106;
  for (i3 = 0x17; i3 != 0; i3 = i3 + -1) {
    *pi4 = *pi2;
    pi2 = pi2 + 1;
    pi4 = pi4 + 1;
  }
  GameActivateAI();
  return;
}

/* GameActivateAI @ 0x080b0560, 175 bytes
 *
 * Switches each player's AI on or off: computer-controlled sides, demo mode
 * and stress test get AI.
 *
 * Globals read: stresstest, demo_mode
 * Called by: GameLoadAndActivateTeam
 *
 * Elecbyte file: src/mugen/p-make.c
 */
void GameActivateAI(void)

{
  int i1;
  int i2;
  bool b3;
  int *pi4;
  int i3;
  int *pi6;
  int j;
  
  b3 = false;
  if ((g[G_STRESSTEST] != 0) || (g[G_DEMO_MODE] != 0)) {
    b3 = true;
  }
  j = 0;
  do {
    pi4 = g;
    i1 = g[j * 0x6a7 + 0x33b8];
    i3 = 0;
    if (0 < g[i1 * 0x17 + j * 0x6a7 + 0x33bd]) {
      pi6 = g + i1 * 0x17 + j * 0x6a7 + 0x33be;
      do {
        if ((b3) && (i2 = pi4[*pi6 + 0x73d9], i2 != 0)) {
          *(uint32_t *)(i2 + 0x262c) = 1;
        }
        i3 = i3 + 1;
        pi6 = pi6 + 5;
      } while (i3 < pi4[i1 * 0x17 + j * 0x6a7 + 0x33bd]);
    }
    j = j + 1;
  } while (j < 2);
  return;
}

/* GameLoadAndCreateChars @ 0x080b0610, 952 bytes
 *
 * For each active member of a team: loads the character into the cache,
 * creates its player record, restores its saved variables, applies its
 * palette, checks it, enables it and puts it in its palette group. Errors:
 * "Can't create player %i", "Error loading p%i".
 *
 * Parameters:
 *   arg1         int
 *
 * Player fields written: teamside, teammode, palno
 * Globals written: players
 * Calls: PlayerNew, PlayerRestorePersistVars, PlayerChangePal,
 *        PlayerEnableSet, PlayerCheck, PalGrpMakeFlag, PlayerCacheLoad
 * C library: sprintf
 * Called by: GameLoadAndActivateTeam
 * Messages:
 *   "Can\'t create player %i"
 *   "\nError loading p%i"
 *
 * Elecbyte file: src/mugen/p-make.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x70 bytes, 3
 *       variables), because their address is taken.
 */
uint32_t GameLoadAndCreateChars(int arg1)

{
  int *pi1;
  int i2;
  int i3;
  int *pi4;
  int chardef;
  int *player;
  int *pi7;
  uint32_t *pu8;
  uint32_t *pu9;
  uint32_t u10;
  uint32_t u11;
  int i12;
  char *format;
  int player2;
  unsigned char frame[0x70] __attribute__((aligned(16)));
#define stk_68 (*(int *)(frame + 0x8))
#define stk_5c (*(PalGrpFlag *)(frame + 0x14))
#define stk_3c (*(PalGrpFlag (*)[2])(frame + 0x34))
  
  pi7 = g;
  i2 = g[arg1 * 0x6a7 + 0x33b8];
  stk_68 = 0;
  i3 = i2 * 0x5c + arg1 * 0x1a9c + 0xceec;
  chardef = g[arg1 * 0x6a7 + i2 * 0x17 + 0x33bd];
  if (chardef < 1) {
L_080b075a:
    pi4 = g;
    pi1 = g + arg1 * 0x6a7 + 0x33b8;
    i2 = g[arg1 * 0x6a7 + 0x33b8];
    stk_68 = 0;
    if (0 < g[arg1 * 0x6a7 + i2 * 0x17 + 0x33bd]) {
      do {
        player2 = pi4[arg1 * 0x6a7 + i2 * 0x17 + stk_68 * 5 + 0x33be];
        i12 = player2 * 4;
        player = PlayerNew(g[player2 + 0x7399]);
        pi7 = g;
        g[player2 + G_PLAYERS] = (int)player;
        if (player == (int *)0x0) {
          if ((char)pi7[0x81d2] == '\0') {
            pi7 = pi7 + 0x81d2;
            format = "Can\'t create player %i";
L_080b0818:
            sprintf((char *)pi7,format,player2,i12);
          }
          return 0;
        }
        player[PL_TEAMSIDE] = (arg1 != 0) + 1;
        player[PL_TEAMMODE] = arg1;
        player[5] = *pi1;
        player[6] = stk_68;
        PlayerRestorePersistVars
                  ((int)player,
                   (int)(pi7 + arg1 * 0x6a7 + *pi1 * 400 + stk_68 * 100 + 0x3417));
        player[600] = (int)(g + pi4[arg1 * 0x6a7 + i2 * 0x17 + stk_68 * 5 + 0x33c1] * 0xd
                                + 0x733b);
        if (pi4[arg1 * 0x6a7 + i2 * 0x17 + stk_68 * 5 + 0x33c2] != 0) {
          player[0x98b] = 1;
        }
        PlayerChangePal((int)player,pi4[arg1 * 0x6a7 + i2 * 0x17 + stk_68 * 5 + 0x33c0]);
        player[PL_PALNO] = pi4[arg1 * 0x6a7 + i2 * 0x17 + stk_68 * 5 + 0x33c0];
        PlayerEnableSet(player2,1);
        PlayerCheck(player);
        player[2] = player2;
        if (player2 + -1 < 0x20) {
          PalGrpMakeFlag(stk_3c,1 << ((uint8_t)(player2 + -1) & 0x1f),1);
          player[0x972] = stk_3c[0].w[0];
          player[0x973] = stk_3c[0].w[1];
          player[0x974] = stk_3c[0].w[2];
          player[0x975] = stk_3c[0].w[3];
          u10 = stk_3c[0].w[4];
        }
        else {
          PalGrpMakeFlag(&stk_5c,1 << ((char)player2 - 0x21U & 0x1f),2);
          player[0x972] = stk_5c.w[0];
          player[0x973] = stk_5c.w[1];
          player[0x974] = stk_5c.w[2];
          player[0x975] = stk_5c.w[3];
          u10 = stk_5c.w[4];
        }
        player[0x976] = u10;
        stk_68 = stk_68 + 1;
      } while (stk_68 < pi4[arg1 * 0x6a7 + i2 * 0x17 + 0x33bd]);
    }
    return 1;
  }
  i12 = 0;
L_080b0668:
  player2 = *(int *)((int)pi7 + i12 + 0xc + i3);
  if (*(int *)((int)pi7 + i12 + i3 + 0x10) == -1) goto L_080b073e;
  if (player2 + -1 < 4) {
    g[player2 + 0x81c4] = Ticks;
  }
  chardef = PlayerCacheLoad(*(int *)((int)pi7 + i12 + i3 + 0x10));
  pi1 = g;
  g[player2 + 0x7399] = chardef;
  if (chardef != 0) {
    if (player2 + -1 < 4) {
      pi1[player2 + 0x81c4] = Ticks - pi1[player2 + 0x81c4];
      chardef = pi7[arg1 * 0x6a7 + i2 * 0x17 + 0x33bd];
    }
    else {
      chardef = pi7[arg1 * 0x6a7 + i2 * 0x17 + 0x33bd];
    }
    goto L_080b073e;
  }
  format = "\nError loading p%i";
  pu9 = (uint32_t *)(pi1 + 0x81d2);
  do {
    pu8 = pu9;
    pu9 = pu8 + 1;
    u10 = *pu8 + 0xfefefeff & (*pu8 ^ 0xffffffff);
    u11 = u10 & 0x80808080;
  } while (u11 == 0);
  if ((u10 & 0x8080) == 0) {
    u11 = u11 >> 0x10;
    pu9 = (uint32_t *)((int)pu8 + 6);
  }
  pi7 = (int *)((int)g + (int)pu9 +
                            (-(int)(pi1 + 0x81d2) - (uint32_t)CARRY1((uint8_t)u11,(uint8_t)u11)) +
                            0x20745);
  goto L_080b0818;
L_080b073e:
  i12 = i12 + 0x14;
  stk_68 = stk_68 + 1;
  if (chardef <= stk_68) goto L_080b075a;
  goto L_080b0668;
}
#undef stk_68
#undef stk_5c
#undef stk_3c

/* GameFreeChars @ 0x080b09d0, 378 bytes
 *
 * Disables and frees a team's players, saving their variables and removing
 * what depends on them (explods, bindings, helpers), and releases their
 * cache entries.
 *
 * Parameters:
 *   arg1         int
 *
 * Globals read: players
 * Calls: PlayerEnableSet, PlayerSavePersistVars,
 *        GameFreePlayerDependencies, PlayerFree, PlayerCacheFree
 * Called by: GameLoadAndActivateTeam
 *
 * Elecbyte file: src/mugen/p-make.c
 */
uint32_t GameFreeChars(int arg1)

{
  int player;
  int *pi2;
  int *pi3;
  int i4;
  int stk_18;
  
  pi2 = g;
  stk_18 = 0;
  if (0 < g[arg1 * 0x17 + 0x4108]) {
    do {
      player = pi2[arg1 * 0x17 + stk_18 * 5 + 0x4109];
      if (g[player + G_PLAYERS] != 0) {
        if (*(int *)(g[player + G_PLAYERS] + 0x158) != 0) {
          PlayerEnableSet(player,0);
        }
        i4 = g[player + G_PLAYERS];
        if (*(int *)(i4 + 0x10) != -1) {
          PlayerSavePersistVars
                    (g[player + G_PLAYERS],
                     g + *(int *)(i4 + 0x10) * 0x6a7 +
                         *(int *)(i4 + 0x14) * 400 + *(int *)(i4 + 0x18) * 100 + 0x3417);
        }
        i4 = -1;
        if (*(int *)g[player + G_PLAYERS] != 0) {
          i4 = *(int *)(*(int *)g[player + G_PLAYERS] + 0x10a8);
        }
        GameFreePlayerDependencies((int *)g[player + G_PLAYERS]);
        PlayerFree((int *)g[player + G_PLAYERS]);
        if (i4 != -1) {
          PlayerCacheFree(i4);
        }
        pi3 = g;
        g[player + 0x7399] = 0;
        pi3[player + 0x73d9] = 0;
      }
      stk_18 = stk_18 + 1;
    } while (stk_18 < pi2[arg1 * 0x17 + 0x4108]);
  }
  return 1;
}

/* GameFreePlayerDependencies @ 0x080b0b50, 349 bytes
 *
 * Removes everything that refers to a player that is going away: its
 * explods, bindings and its helpers.
 *
 * Parameters:
 *   arg1         int *
 *
 * Globals read: slot_first, slot_last
 * Calls: ExplodRemoveID, PlayerDropBoundTargets, HelperDestroy
 * Called by: GameFreeChars
 *
 * Elecbyte file: src/mugen/p-make.c
 */
uint32_t GameFreePlayerDependencies(int *arg1)

{
  int *pi1;
  int i2;
  int *pi3;
  int i4;
  int i5;
  
  ExplodRemoveID((uint32_t *)g[0x52be],arg1[1],-1);
  PlayerDropBoundTargets((int)arg1,(int *)0x0);
  i5 = g[G_SLOT_FIRST];
  if (i5 <= g[G_SLOT_LAST]) {
    i4 = i5 * 4 + 0x1cf60;
    pi3 = g;
    do {
      pi1 = *(int **)(i4 + 4 + (int)pi3);
      if ((pi1 != arg1) && (pi1 != (int *)0x0)) {
        if ((int *)pi1[0x989] == arg1) {
          ExplodRemoveID((uint32_t *)pi3[0x52be],pi1[1],-1);
          HelperDestroy((int)pi1);
          pi3 = g;
        }
        else {
          i2 = arg1[0x4e5];
          if (i2 != 0) {
            *(uint32_t *)(i2 + 0x18) = 0;
            *(uint32_t *)(i2 + 8) = 0;
            arg1[0x4e5] = 0;
          }
          if (pi1[0x4f0] == *(int *)(*arg1 + 0x11cc)) {
            pi1[0x4f0] = 0;
          }
          if (pi1[0x2fb] == arg1[0x2fa]) {
            pi1[0x2fb] = 0;
            pi1[0x2fc] = -1;
          }
          if ((int *)pi1[0xd09] == arg1) {
            pi1[0xd09] = 0;
          }
          if ((int *)pi1[0xd0a] == arg1) {
            pi1[0xd0a] = 0;
          }
          pi3 = g;
          if (((int *)pi1[0xd15] == arg1) && (pi1[0xd0c] != 0)) {
            pi1[0xd0c] = 0;
            pi1[0xd15] = 0;
            pi3 = g;
          }
        }
      }
      i5 = i5 + 1;
      i4 = i4 + 4;
    } while (i5 <= pi3[0x745a]);
  }
  return 1;
}

/* TeamReorderAll @ 0x080b0cb0, 802 bytes
 *
 * Rebuilds both teams' member order and side assignment for the next match
 * or round (turns, simul, single), including the players' input assignment.
 *
 * Parameters:
 *   arg1         int
 *
 * Calls: KBToUInp
 * Called by: GameMatchReset, GameNextRound
 *
 * Elecbyte file: src/mugen/p-make.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x700 bytes,
 *       8 variables), because their address is taken.
 */
int TeamReorderAll(int arg1)

{
  int i1;
  int *pi2;
  uint32_t uinp;
  int *pi4;
  int i5;
  int i6;
  int i7;
  int i8;
  int i9;
  int *pi10;
  unsigned char frame[0x700] __attribute__((aligned(16)));
#define stk_6f8 (*(int **)(frame + 0x8))
#define stk_6ec (*(int **)(frame + 0x14))
#define stk_6e8 (*(int **)(frame + 0x18))
#define stk_6e0 (*(int **)(frame + 0x20))
#define stk_6c8 (*(int *)(frame + 0x38))
#define stk_6c4 (*(int *)(frame + 0x3c))
#define stk_6bc (*(int (*)[400])(frame + 0x44))
#define stk_7c (*(int (*)[27])(frame + 0x684))
  
  pi2 = g;
  i1 = g[arg1 * 0x6a7 + 0x33b8];
  i9 = g[arg1 * 0x6a7 + 0x33b9] - i1;
  pi4 = g + arg1 * 0x6a7 + i1 * 0x17 + 0x33bb;
  if ((1 < i9) && (pi4[7] == 0)) {
    i6 = pi4[6];
    uinp = KBToUInp(g[i6 * 0xd + 0x733f]);
    stk_6c4 = (uinpflag[uinp] == 0) - 1;
    uinp = KBToUInp(pi2[i6 * 0xd + 0x733d]);
    if (uinpflag[uinp] != 0) {
      stk_6c4 = 1;
    }
    if (arg1 == 1) {
      stk_6c4 = -stk_6c4;
    }
    uinp = KBToUInp(pi2[i6 * 0xd + 0x733c]);
    if ((uinpflag[uinp] != 0) && (i9 == 4)) {
      stk_6c4 = 2;
    }
    pi4 = (int *)(stk_6c4 / i9);
    stk_6c4 = stk_6c4 % i9;
    if (stk_6c4 < 0) {
      stk_6c4 = stk_6c4 + i9;
    }
    if (0 < stk_6c4) {
      i9 = arg1 * 4;
      do {
        pi4 = pi2 + arg1 * 0x6a7 + i1 * 0x17 + 0x33bb;
        pi10 = stk_7c;
        for (i6 = 0x17; i6 != 0; i6 = i6 + -1) {
          *pi10 = *pi4;
          pi4 = pi4 + 1;
          pi10 = pi10 + 1;
        }
        pi4 = pi2 + arg1 * 0x6a7 + i1 * 400 + 0x3417;
        pi10 = stk_6bc;
        for (i6 = 400; i6 != 0; i6 = i6 + -1) {
          *pi10 = *pi4;
          pi4 = pi4 + 1;
          pi10 = pi10 + 1;
        }
        i6 = g[i9 + i1 + 0x52b5];
        i7 = pi2[arg1 * 0x6a7 + 0x33b9];
        if (i1 < i7 + -1) {
          stk_6e0 = pi2 + arg1 * 0x6a7 + i1 * 400 + 0x35a4;
          stk_6f8 = pi2 + arg1 * 0x6a7 + i1 * 0x17 + 0x33b8;
          i5 = (i9 + i1) * 4;
          stk_6e8 = pi2 + arg1 * 0x6a7 + i1 * 400 + 0x3414;
          i8 = i5 + 0x14ad4;
          i5 = i5 + 0x14ad0;
          stk_6c8 = i1;
          pi4 = pi2 + arg1 * 0x6a7 + i1 * 0x17 + 0x33b8;
          do {
            stk_6ec = pi4 + 0x17;
            pi4 = pi4 + 0x1a;
            pi10 = stk_6f8 + 3;
            for (i7 = 0x17; i7 != 0; i7 = i7 + -1) {
              *pi10 = *pi4;
              pi4 = pi4 + 1;
              pi10 = pi10 + 1;
            }
            pi4 = stk_6e0 + 3;
            pi10 = stk_6e8 + 3;
            for (i7 = 400; i7 != 0; i7 = i7 + -1) {
              *pi10 = *pi4;
              pi4 = pi4 + 1;
              pi10 = pi10 + 1;
            }
            i7 = i8 + 4;
            i8 = i8 + 4;
            *(uint32_t *)((int)g + i5 + 4) = *(uint32_t *)((int)g + i7);
            i5 = i5 + 4;
            stk_6e0 = stk_6e0 + 400;
            stk_6e8 = stk_6e8 + 400;
            stk_6f8 = stk_6f8 + 0x17;
            stk_6c8 = stk_6c8 + 1;
            i7 = pi2[arg1 * 0x6a7 + 0x33b9];
            pi4 = stk_6ec;
          } while (stk_6c8 < i7 + -1);
        }
        pi4 = stk_7c;
        pi10 = pi2 + arg1 * 0x6a7 + i7 * 0x17 + 0x33a4;
        for (i8 = 0x17; i8 != 0; i8 = i8 + -1) {
          *pi10 = *pi4;
          pi4 = pi4 + 1;
          pi10 = pi10 + 1;
        }
        pi4 = stk_6bc;
        pi10 = pi2 + arg1 * 0x6a7 + pi2[arg1 * 0x6a7 + 0x33b9] * 400 + 0x3287;
        for (i7 = 400; i7 != 0; i7 = i7 + -1) {
          *pi10 = *pi4;
          pi4 = pi4 + 1;
          pi10 = pi10 + 1;
        }
        pi4 = (int *)(i9 + pi2[arg1 * 0x6a7 + 0x33b9]);
        g[(int)(pi4 + 0x14ad)] = i6;
        stk_6c4 = stk_6c4 + -1;
      } while (stk_6c4 != 0);
    }
  }
  return (int)pi4;
}
#undef stk_6f8
#undef stk_6ec
#undef stk_6e8
#undef stk_6e0
#undef stk_6c8
#undef stk_6c4
#undef stk_6bc
#undef stk_7c

