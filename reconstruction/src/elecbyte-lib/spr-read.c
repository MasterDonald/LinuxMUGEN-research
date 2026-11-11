/*
 * spr-read.c -- sprite file reading
 * Reads SFF v1.01 sprite files (whole or a list of wanted sprites) and PCX
 * images.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/spr-read.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"

extern int ReadMode __asm__("D_08287a0c"); /* file-static 0x08287a0c */
extern int BufferedReadMode __asm__("D_08287a10"); /* file-static 0x08287a10 */

/* SpriteSetReadMode @ 0x0805bf20, 10 bytes
 *
 * Sets the sprite read mode flag. Not called in this build.
 *
 * Parameters:
 *   arg1         int
 *
 * Elecbyte file: src/lib/spr-read.c
 */
void SpriteSetReadMode(int arg1)

{
  ReadMode = arg1;
  return;
}

/* SpriteSetBufReadMode @ 0x0805bf30, 10 bytes
 *
 * Selects how sprite files are read: 0 through an MF file stream, nonzero by
 * loading the whole file into memory first and parsing it from there (faster
 * on slow media). Set from the configuration and before loading characters.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: FindCharacters, GameConfigRead, GameStgInitFightData
 *
 * Elecbyte file: src/lib/spr-read.c
 */
void SpriteSetBufReadMode(int arg1)

{
  BufferedReadMode = arg1;
  return;
}

/* SpriteReadFile @ 0x0805bf40, 317 bytes
 *
 * Loads a sprite file (.sff or .pcx, chosen by CheckExtension) into a new
 * sprite array, either through a file stream or from memory
 * (SpriteSetBufReadMode). Returns the sprite array or NULL.
 *
 * Parameters:
 *   filename     char *
 *
 * Calls: MFfopenFile, ffilelength, MFfopenMem, MFfseek, CheckExtension,
 *        SpriteReadPCXPtr, SpriteReadSFFPtr, MFfclose
 * C library: fopen, malloc, fclose, fread, free
 * Called by: BGArrayReadTP, GameLoadFightData, GameLoadSystem,
 *            GameReloadSystemSprSnd, PlayerDefLoadPtr, PlayerDefLoadZip,
 *            SiSceneReadTP
 *
 * Elecbyte file: src/lib/spr-read.c
 */
int * SpriteReadFile(char *filename)

{
  FILE *stream;
  size_t size;
  void *ptr;
  size_t s1;
  int *mf;
  int i3;
  int *pi4;
  
  if (BufferedReadMode == 0) {
    mf = (int *)MFfopenFile(filename,"rb");
    if (mf == (int *)0x0) {
      return (int *)0x0;
    }
  }
  else {
    stream = fopen(filename,"rb");
    if (stream == (FILE *)0x0) {
      return (int *)0x0;
    }
    size = ffilelength(stream);
    ptr = malloc(size);
    if (ptr == (void *)0x0) {
      fclose(stream);
      return (int *)0x0;
    }
    s1 = fread(ptr,size,1,stream);
    if (s1 == 0) {
      fclose(stream);
      free(ptr);
      return (int *)0x0;
    }
    fclose(stream);
    mf = MFfopenMem((int)ptr,size);
    if (mf == (int *)0x0) {
      free(ptr);
      return (int *)0x0;
    }
    mf[6] = 1;
  }
  MFfseek(mf,0,0);
  i3 = CheckExtension(filename);
  if (i3 == 1) {
    pi4 = SpriteReadPCXPtr(mf,0,0);
  }
  else {
    if (i3 != 2) {
      return (int *)0x0;
    }
    pi4 = SpriteReadSFFPtr(mf);
  }
  if (pi4 == (int *)0x0) {
    MFfclose(mf);
    return (int *)0x0;
  }
  MFfclose(mf);
  return pi4;
}

/* SpriteReadSFFPtr @ 0x0805c080, 180 bytes
 *
 * Reads an SFF file from an MF stream. It checks the "ElecbyteSpr" signature
 * and the version: version 1.01 is read by SpriteReadSFFPtr_1_01; 2.00 is
 * recognised but not supported (returns NULL). The stream position is
 * restored on failure.
 *
 * Parameters:
 *   mf           int *
 *
 * Calls: MFftell, MFfread, SpriteReadSFFPtr_1_01, SpriteReadSFFPtr_2_00,
 *        MFfseek
 * Called by: PlayerDefLoadZip, SpriteReadFile
 *
 * Elecbyte file: src/lib/spr-read.c
 * Note: 1 data addresses refer to the data image (data/mugen_data.S).
 * Note: Locals live in `frame`, laid out as on the original stack (0x220 bytes,
 *       2 variables), because their address is taken.
 */
int * SpriteReadSFFPtr(int *mf)

{
  int pos;
  size_t s2;
  int i3;
  int *pi4;
  uint8_t *pb5;
  uint8_t *pb6;
  bool b7;
  bool b8;
  unsigned char frame[0x220] __attribute__((aligned(16)));
#define stk_21c (*(uint8_t (*)[12])(frame + 0x4))
#define stk_210 (*(int *)(frame + 0x10))
  
  pi4 = (int *)0x0;
  pos = MFftell(mf);
  s2 = MFfread(stk_21c,0x200,1,mf);
  b7 = false;
  b8 = s2 == 0;
  if (!b8) {
    i3 = 0xc;
    pb5 = stk_21c;
    pb6 = (uint8_t *)(int)&str_elecbytespr;
    do {
      if (i3 == 0) break;
      i3 = i3 + -1;
      b7 = *pb5 < *pb6;
      b8 = *pb5 == *pb6;
      pb5 = pb5 + 1;
      pb6 = pb6 + 1;
    } while (b8);
    if ((!b7 && !b8) == b7) {
      if (stk_210 == 0x1000100) {
        pi4 = SpriteReadSFFPtr_1_01(mf,(int)stk_21c);
      }
      else {
        pi4 = (int *)SpriteReadSFFPtr_2_00();
      }
      if (pi4 != (int *)0x0) {
        pi4[6] = stk_210;
      }
    }
  }
  MFfseek(mf,pos,0);
  return pi4;
}
#undef stk_21c
#undef stk_210

/* SpriteReadSFFPtr_1_01 @ 0x0805c140, 606 bytes
 *
 * Reads all subfiles of an SFF v1.01 file into a new sprite array. Each
 * subfile header gives the next offset, the PCX length, the axis, the
 * (group, image) key, and the index of the sprite it duplicates (a "linked"
 * sprite copied with SpriteCopy). It also says whether the subfile uses the
 * previous palette. The PCX data is decoded with SpriteReadPCXRawPtr; a
 * subfile with its own palette adds a new palette, otherwise the shared one
 * is used.
 *
 * Parameters:
 *   mf           int *
 *   arg2         int
 *
 * Calls: MFftell, SpriteArrayNewSize, MFfseek, MFfread, SpriteArrayAccess,
 *        SpriteCopy, SpriteSetAxis, SpriteReadPCXRawPtr,
 *        SpriteArrayAddPal, SpriteArrayFree, SpriteInit, SpriteUsePal,
 *        SpriteArrayAddSprite
 * Called by: SpriteReadSFFPtr
 *
 * Elecbyte file: src/lib/spr-read.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x300 bytes,
 *       18 variables), because their address is taken.
 */
int * SpriteReadSFFPtr_1_01(int *mf,int arg2)

{
  bool b1;
  int pos;
  int *sprites;
  size_t s4;
  void *pv5;
  int i6;
  uint32_t stale_var;
  uint32_t *sprite;
  int *pi8;
  void *pv9;
  unsigned char frame[0x300] __attribute__((aligned(16)));
#define stk_300 (*(int *)(frame + 0x0))
#define stk_2fc (*(int *)(frame + 0x4))
#define stk_2f8 (*(int *)(frame + 0x8))
#define stk_2ec (*(int *)(frame + 0x14))
#define stk_2e8 (*(int *)(frame + 0x18))
#define stk_2e4 (*(int *)(frame + 0x1c))
#define stk_2e0 (*(size_t *)(frame + 0x20))
#define stk_2dc (*(int *)(frame + 0x24))
#define stk_2d8 (*(int *)(frame + 0x28))
#define stk_2d4 (*(short *)(frame + 0x2c))
#define stk_2d2 (*(short *)(frame + 0x2e))
#define stk_2d0 (*(short *)(frame + 0x30))
#define stk_2ce (*(short *)(frame + 0x32))
#define stk_2cc (*(short *)(frame + 0x34))
#define stk_2ca (*(char *)(frame + 0x36))
#define stk_2bc (*(int (*)[152])(frame + 0x44))
#define stk_5c (*(int (*)[6])(frame + 0x2a4))
#define stk_44 (*(uint32_t *)(frame + 0x2bc))
  
  stk_2fc = 0;
  stk_300 = -1;
  pos = MFftell(mf);
  sprites = SpriteArrayNewSize(*(size_t *)(arg2 + 0x14),1);
  if (sprites == (int *)0x0) {
    sprites = (int *)0x0;
  }
  else {
    stk_2f8 = 0;
    if (0 < *(int *)(arg2 + 0x14)) {
      i6 = *(int *)(arg2 + 0x18);
      do {
        MFfseek(mf,i6 + pos + -0x200,0);
        s4 = MFfread(&stk_2dc,0x20,1,mf);
        if (s4 == 0) goto L_0805c198;
        if (stk_2d8 < 1) {
          sprite = (uint32_t *)SpriteArrayAccess(sprites,(int)stk_2cc);
          SpriteCopy(stk_5c,sprite,0);
          SpriteSetAxis((int)stk_5c,(int)stk_2d4,(int)stk_2d2);
        }
        else {
          pi8 = (int *)0x0;
          if ((ReadMode != 0x10) && ((stk_300 == -1 || (stk_2ca == '\0')))) {
            pi8 = stk_2bc;
          }
          pv5 = SpriteReadPCXRawPtr(mf,&stk_2ec,&stk_2e8,&stk_2e4,&stk_2e0,pi8);
          if ((pv5 == (void *)0x0) ||
             ((pv9 = (void *)((uint32_t)pi8 & (8 < stk_2e4) - 1), pv9 != (void *)0x0 &&
              (i6 = SpriteArrayAddPal((int)sprites,pv9,0,stk_2fc), i6 == 0)))) {
L_0805c198:
            SpriteArrayFree(sprites);
            return (int *)0x0;
          }
          b1 = SpriteInit(stk_5c,0,pv5,stk_2e0,0,stk_2ec,stk_2e8,stk_2e4,
                             (int)stk_2d4,(int)stk_2d2);
          if (ZEXT8(b1) == 0) goto L_0805c198;
          stk_44 = 1;
          if (pv9 == (void *)0x0) {
            if (stk_2ca != '\0') {
              SpriteUsePal((int)stk_5c,(int)sprites,0,stk_300);
            }
          }
          else {
            SpriteUsePal((int)stk_5c,(int)sprites,0,stk_2fc);
            stk_300 = stk_2fc;
            stk_2fc = stk_2fc + 1;
          }
        }
        SpriteArrayAddSprite(sprites,stk_5c,(int)stk_2d0,(int)stk_2ce);
        stk_2f8 = stk_2f8 + 1;
        i6 = stk_2dc;
      } while (stk_2f8 < *(int *)(arg2 + 0x14));
    }
    MFfseek(mf,pos,0);
  }
  return sprites;
}
#undef stk_300
#undef stk_2fc
#undef stk_2f8
#undef stk_2ec
#undef stk_2e8
#undef stk_2e4
#undef stk_2e0
#undef stk_2dc
#undef stk_2d8
#undef stk_2d4
#undef stk_2d2
#undef stk_2d0
#undef stk_2ce
#undef stk_2cc
#undef stk_2ca
#undef stk_2bc
#undef stk_5c
#undef stk_44

/* SpriteReadSFFPtr_2_00 @ 0x0805c3a0, 3 bytes
 *
 * Placeholder for SFF v2.00; returns NULL.
 *
 * Called by: SpriteReadSFFPtr
 *
 * Elecbyte file: src/lib/spr-read.c
 */
uint32_t SpriteReadSFFPtr_2_00(void)

{
  return 0;
}

/* SpriteReadSFFList @ 0x0805c3b0, 89 bytes
 *
 * Opens an SFF file and reads only the sprites listed in `list`
 * (SpriteReadSFFListPtr). Used to load the small portrait sprites of every
 * character on the select screen without loading whole sprite files.
 *
 * Parameters:
 *   filename     char *
 *   arg2         int *
 *
 * Calls: MFfopenFile, SpriteReadSFFListPtr, MFfclose
 * Called by: FindCharacters, GameStgInitFightData
 *
 * Elecbyte file: src/lib/spr-read.c
 */
int * SpriteReadSFFList(char *filename,int *arg2)

{
  int *mf;
  int *pi2;
  
  mf = (int *)MFfopenFile(filename,"rb");
  if (mf == (int *)0x0) {
    pi2 = (int *)0x0;
  }
  else {
    pi2 = SpriteReadSFFListPtr(mf,arg2);
    if (pi2 == (int *)0x0) {
      MFfclose(mf);
      pi2 = (int *)0x0;
    }
    else {
      MFfclose(mf);
    }
  }
  return pi2;
}

/* SpriteReadSFFListPtr @ 0x0805c410, 165 bytes
 *
 * SpriteReadSFFPtr for a list of wanted sprites: checks the signature and
 * version and calls SpriteReadSFFListPtr_1_01.
 *
 * Parameters:
 *   mf           int *
 *   arg2         int *
 *
 * Calls: MFftell, MFfread, SpriteReadSFFListPtr_1_01,
 *        SpriteReadSFFListPtr_2_00, MFfseek
 * Called by: FindCharacters, SpriteReadSFFList
 *
 * Elecbyte file: src/lib/spr-read.c
 * Note: 1 data addresses refer to the data image (data/mugen_data.S).
 * Note: Locals live in `frame`, laid out as on the original stack (0x220 bytes,
 *       3 variables), because their address is taken.
 */
int * SpriteReadSFFListPtr(int *mf,int *arg2)

{
  int pos;
  size_t s2;
  int i3;
  uint8_t *pb4;
  uint8_t *pb5;
  bool b6;
  bool b7;
  unsigned char frame[0x220] __attribute__((aligned(16)));
#define stk_220 (*(int **)(frame + 0x0))
#define stk_21c (*(uint8_t (*)[12])(frame + 0x4))
#define stk_210 (*(int *)(frame + 0x10))
  
  stk_220 = (int *)0x0;
  pos = MFftell(mf);
  s2 = MFfread(stk_21c,0x200,1,mf);
  b6 = false;
  b7 = s2 == 0;
  if (!b7) {
    i3 = 0xc;
    pb4 = stk_21c;
    pb5 = (uint8_t *)(int)&str_elecbytespr;
    do {
      if (i3 == 0) break;
      i3 = i3 + -1;
      b6 = *pb4 < *pb5;
      b7 = *pb4 == *pb5;
      pb4 = pb4 + 1;
      pb5 = pb5 + 1;
    } while (b7);
    if ((!b6 && !b7) == b6) {
      if (stk_210 == 0x1000100) {
        stk_220 = SpriteReadSFFListPtr_1_01(mf,(int)stk_21c,arg2);
      }
      else {
        stk_220 = (int *)SpriteReadSFFListPtr_2_00();
      }
    }
  }
  MFfseek(mf,pos,0);
  return stk_220;
}
#undef stk_220
#undef stk_21c
#undef stk_210

/* SpriteReadSFFListPtr_1_01 @ 0x0805c4c0, 747 bytes
 *
 * Reads from an SFF v1.01 file only the sprites whose keys appear in `list`
 * (pairs of group, image ended by -1), following links and palettes as
 * SpriteReadSFFPtr_1_01 does. Returns a new sprite array, or NULL.
 *
 * Parameters:
 *   mf           int *
 *   arg2         int
 *   arg3         int *
 *
 * Calls: MFftell, SpriteArrayNewSize, MFfseek, MFfread,
 *        SpriteReadPCXRawPtr, SpriteArrayAddPal, SpriteArrayFree,
 *        SpriteInit, SpriteUsePal, SpriteArrayAddSprite
 * C library: free
 * Called by: SpriteReadSFFListPtr
 *
 * Elecbyte file: src/lib/spr-read.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x310 bytes,
 *       18 variables), because their address is taken.
 */
int * SpriteReadSFFListPtr_1_01(int *mf,int arg2,int *arg3)

{
  bool b1;
  int pos;
  int *sprites;
  size_t s4;
  void *ptr;
  uint32_t stale_var;
  int i5;
  int i6;
  int *pi7;
  void *pv8;
  bool b9;
  unsigned char frame[0x310] __attribute__((aligned(16)));
#define stk_308 (*(size_t *)(frame + 0x8))
#define stk_304 (*(int *)(frame + 0xc))
#define stk_300 (*(int *)(frame + 0x10))
#define stk_2fc (*(int *)(frame + 0x14))
#define stk_2f8 (*(int *)(frame + 0x18))
#define stk_2ec (*(int *)(frame + 0x24))
#define stk_2e8 (*(int *)(frame + 0x28))
#define stk_2e4 (*(int *)(frame + 0x2c))
#define stk_2e0 (*(size_t *)(frame + 0x30))
#define stk_2dc (*(int *)(frame + 0x34))
#define stk_2d8 (*(int *)(frame + 0x38))
#define stk_2d4 (*(short *)(frame + 0x3c))
#define stk_2d2 (*(short *)(frame + 0x3e))
#define stk_2d0 (*(short *)(frame + 0x40))
#define stk_2ce (*(short *)(frame + 0x42))
#define stk_2ca (*(char *)(frame + 0x46))
#define stk_2bc (*(int (*)[152])(frame + 0x54))
#define stk_5c (*(int (*)[19])(frame + 0x2b4))
  
  stk_2fc = 0;
  stk_300 = -1;
  stk_304 = 0;
  stk_308 = 0;
  stk_2f8 = 0;
  pos = *arg3;
  while (pos != -1) {
    stk_2f8 = stk_2f8 + 2;
    stk_308 = stk_308 + 1;
    pos = arg3[stk_2f8];
  }
  pos = MFftell(mf);
  sprites = SpriteArrayNewSize(stk_308,1);
  if (sprites == (int *)0x0) {
    sprites = (int *)0x0;
  }
  else {
    stk_2f8 = 0;
    i5 = *(int *)(arg2 + 0x18);
    if (0 < *(int *)(arg2 + 0x14)) {
      do {
        MFfseek(mf,i5 + pos + -0x200,0);
        s4 = MFfread(&stk_2dc,0x20,1,mf);
        if (s4 == 0) goto L_0805c560;
        b1 = false;
        i5 = 0;
        if (*arg3 != -1) {
          if ((int)stk_2d0 != *arg3) goto L_0805c5f5;
          b9 = (int)stk_2ce == arg3[1];
          while (!b9) {
L_0805c5f5:
            do {
              i6 = i5;
              i5 = i6 + 2;
              if (arg3[i5] == -1) goto L_0805c61d;
            } while ((int)stk_2d0 != arg3[i5]);
            b9 = (int)stk_2ce == arg3[i6 + 3];
          }
          b1 = true;
        }
L_0805c61d:
        if (0 < stk_2d8) {
          pi7 = (int *)0x0;
          if ((ReadMode != 0x10) && ((stk_300 == -1 || (stk_2ca == '\0')))) {
            pi7 = stk_2bc;
          }
          if (b1) {
            ptr = SpriteReadPCXRawPtr(mf,&stk_2ec,&stk_2e8,&stk_2e4,&stk_2e0,pi7);
            if ((ptr == (void *)0x0) ||
               ((pv8 = (void *)((uint32_t)pi7 & (8 < stk_2e4) - 1), pv8 != (void *)0x0 &&
                (i5 = SpriteArrayAddPal((int)sprites,pv8,0,stk_2fc), i5 == 0)))) {
L_0805c560:
              SpriteArrayFree(sprites);
              return (int *)0x0;
            }
            b9 = SpriteInit(stk_5c,0,ptr,stk_2e0,1,stk_2ec,stk_2e8,stk_2e4,
                               (int)stk_2d4,(int)stk_2d2);
            if (ZEXT8(b9) == 0) goto L_0805c560;
            free(ptr);
            if (pv8 == (void *)0x0) {
              if (stk_2ca != '\0') {
                SpriteUsePal((int)stk_5c,(int)sprites,0,stk_300);
              }
            }
            else {
              SpriteUsePal((int)stk_5c,(int)sprites,0,stk_2fc);
              stk_300 = stk_2fc;
              stk_2fc = stk_2fc + 1;
            }
          }
        }
        if (b1) {
          SpriteArrayAddSprite(sprites,stk_5c,(int)stk_2d0,(int)stk_2ce);
          stk_304 = stk_304 + 1;
        }
      } while ((stk_304 < (int)stk_308) &&
              (stk_2f8 = stk_2f8 + 1, i5 = stk_2dc, stk_2f8 < *(int *)(arg2 + 0x14)));
    }
    MFfseek(mf,pos,0);
  }
  return sprites;
}
#undef stk_308
#undef stk_304
#undef stk_300
#undef stk_2fc
#undef stk_2f8
#undef stk_2ec
#undef stk_2e8
#undef stk_2e4
#undef stk_2e0
#undef stk_2dc
#undef stk_2d8
#undef stk_2d4
#undef stk_2d2
#undef stk_2d0
#undef stk_2ce
#undef stk_2ca
#undef stk_2bc
#undef stk_5c

/* SpriteReadSFFListPtr_2_00 @ 0x0805c7b0, 3 bytes
 *
 * Placeholder for SFF v2.00; returns NULL.
 *
 * Called by: SpriteReadSFFListPtr
 *
 * Elecbyte file: src/lib/spr-read.c
 */
uint32_t SpriteReadSFFListPtr_2_00(void)

{
  return 0;
}

/* SpriteReadPCXRawPtr @ 0x0805c7c0, 1210 bytes
 *
 * Decodes a PCX image from an MF stream: reads the header (size, bits per
 * pixel, planes), decompresses the RLE pixel rows into a new buffer and, for
 * 8-bit images, reads the 256-colour palette at the end of the data
 * (EBPalInit). Returns the pixel buffer and fills width, height, depth, size
 * and palette. Returns NULL on a bad or truncated file.
 *
 * Parameters:
 *   mf           int *
 *   arg2         int *
 *   arg3         int *
 *   arg4         int *
 *   arg5         size_t *
 *   arg6         int *
 *
 * Calls: MFftell, MFgetc, MFigetw, MFigetl, MFfeof, EBPalInit, MFfseek
 * C library: calloc
 * Called by: SpriteReadPCXPtr, SpriteReadSFFListPtr_1_01,
 *            SpriteReadSFFPtr_1_01
 *
 * Elecbyte file: src/lib/spr-read.c
 * Note: Locals live in `frame`, laid out as on the original stack (0x450 bytes,
 *       4 variables), because their address is taken.
 */
void * SpriteReadPCXRawPtr(int *mf,int *arg2,int *arg3,int *arg4,size_t *arg5,
                          int *arg6)

{
  int i1;
  int i2;
  int i3;
  uint8_t u4;
  uint32_t ch;
  uint32_t u6;
  uint32_t ch2;
  void *pv8;
  uint32_t ch3;
  int i10;
  int i11;
  int pos;
  int i13;
  int i14;
  uint32_t *pu15;
  int i16;
  int i4;
  int i18;
  unsigned char frame[0x450] __attribute__((aligned(16)));
#define stk_450 (*(int *)(frame + 0x0))
#define stk_444 (*(int *)(frame + 0xc))
#define stk_440 (*(int *)(frame + 0x10))
#define stk_41c (*(uint32_t *)(frame + 0x34))
  
  pu15 = &stk_41c;
  for (pos = 0x100; pos != 0; pos = pos + -1) {
    *pu15 = 0;
    pu15 = pu15 + 1;
  }
  pos = MFftell(mf);
  MFgetc(mf);
  MFgetc(mf);
  MFgetc(mf);
  ch = MFgetc(mf);
  if (ch != 8) {
    return (void *)0x0;
  }
  ch = MFigetw(mf);
  u6 = MFigetw(mf);
  ch2 = MFigetw(mf);
  i1 = (ch2 + 1) - ch;
  ch = MFigetw(mf);
  i16 = 0xf;
  i2 = (ch + 1) - u6;
  i14 = 0;
  MFigetl(mf);
  do {
    ch = MFgetc(mf);
    *(char *)((int)&stk_41c + i14) = (char)ch;
    ch = MFgetc(mf);
    *(char *)((int)&stk_41c + i14 + 1) = (char)ch;
    ch = MFgetc(mf);
    *(char *)((int)&stk_41c + i14 + 2) = (char)ch;
    *(uint8_t *)((int)&stk_41c + i14 + 3) = 0xff;
    i14 = i14 + 4;
    i16 = i16 + -1;
  } while (-1 < i16);
  MFgetc(mf);
  ch = MFgetc(mf);
  i14 = ch * 8;
  if ((i14 != 8) && (i14 != 0x18)) {
    return (void *)0x0;
  }
  i16 = i14 + -1;
  if (i16 < 0) {
    i16 = i14 + 6;
  }
  i4 = 0x3b;
  i16 = (i16 >> 3) + 1;
  ch = MFigetw(mf);
  *arg5 = i16 * i1 * i2;
  do {
    MFgetc(mf);
    i4 = i4 + -1;
  } while (-1 < i4);
  pv8 = calloc(1,*arg5);
  if (pv8 == (void *)0x0) {
    ElecOutOfMem = 1;
    return (void *)0x0;
  }
  stk_444 = 0;
  if (0 < i2) {
    stk_450 = 0;
    do {
      u6 = 0;
      stk_440 = 0;
      i4 = _rgb_r_shift_24;
      if (_rgb_r_shift_24 < 0) {
        i4 = _rgb_r_shift_24 + 7;
      }
      i4 = i4 >> 3;
      while( true ) {
        i11 = ch * i14;
        if (i11 < 0) {
          i11 = i11 + 7;
        }
        if (i11 >> 3 <= (int)u6) break;
        ch2 = MFgetc(mf);
        u4 = (uint8_t)ch2;
        if ((ch2 & 0xc0) == 0xc0) {
          ch2 = ch2 & 0x3f;
          ch3 = MFgetc(mf);
          u4 = (uint8_t)ch3;
        }
        else {
          ch2 = 1;
        }
        i3 = _rgb_b_shift_24;
        i11 = _rgb_g_shift_24;
        if (i14 == 8) {
          while (ch2 = ch2 - 1, ch2 != 0xffffffff) {
            if ((int)u6 < i1) {
              *(uint8_t *)((int)pv8 + u6 + stk_450 * i1) = u4;
            }
            u6 = u6 + 1;
          }
        }
        else {
          i18 = ch2 - 1;
          if (i18 != -1) {
            i13 = stk_440 * 3;
            do {
              if (stk_440 < i1) {
                *(uint8_t *)((int)pv8 + i4 + i13 + stk_450 * i1) = u4;
              }
              u6 = u6 + 1;
              i10 = i11;
              if ((u6 == ch) || (i10 = i3, u6 == ch * 2)) {
                i13 = 0;
                stk_440 = 0;
                if (i10 < 0) {
                  i10 = i10 + 7;
                }
                i4 = i10 >> 3;
              }
              else {
                i13 = i13 + 3;
                stk_440 = stk_440 + 1;
              }
              i18 = i18 + -1;
            } while (i18 != -1);
          }
        }
      }
      stk_444 = stk_444 + 1;
      stk_450 = stk_450 + i16;
    } while (stk_444 < i2);
  }
  if ((i14 == 8) && (arg6 != (int *)0x0)) {
    do {
      i16 = MFfeof(mf);
      if (i16 != 0) goto L_0805cbeb;
      ch = MFgetc(mf);
    } while (ch != 0xc);
    i4 = 0;
    i16 = 0;
    do {
      i4 = i4 + 1;
      ch = MFgetc(mf);
      *(char *)((int)&stk_41c + i16) = (char)ch;
      ch = MFgetc(mf);
      *(char *)((int)&stk_41c + i16 + 1) = (char)ch;
      ch = MFgetc(mf);
      *(char *)((int)&stk_41c + i16 + 2) = (char)ch;
      *(uint8_t *)((int)&stk_41c + i16 + 3) = 0xff;
      i16 = i16 + 4;
    } while (i4 < 0x100);
L_0805cbeb:
    i16 = 0x100;
  }
  else {
    if ((i14 != 4) || (arg6 == (int *)0x0)) goto L_0805cc2c;
    i16 = 0x10;
  }
  EBPalInit(arg6,i16,&stk_41c,1);
L_0805cc2c:
  *arg4 = i14;
  *arg2 = i1;
  *arg3 = i2;
  MFfseek(mf,pos,0);
  return pv8;
}
#undef stk_450
#undef stk_444
#undef stk_440
#undef stk_41c

/* SpriteReadPCXPtr @ 0x0805cc80, 239 bytes
 *
 * Reads a single PCX image as a sprite array with one sprite (and its
 * palette for 8-bit images), with the given axis.
 *
 * Parameters:
 *   mf           int *
 *   arg2         int
 *   arg3         int
 *
 * Calls: SpriteArrayNewSize, SpriteReadPCXRawPtr, SpriteArrayAddPal,
 *        SpriteInit, SpriteUsePal, SpriteArrayAddSprite, SpriteArrayFree
 * Called by: FontReadFilePtr_0_01, SpriteReadFile
 *
 * Elecbyte file: src/lib/spr-read.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 * Note: Locals live in `frame`, laid out as on the original stack (0x2c0 bytes,
 *       6 variables), because their address is taken.
 */
int * SpriteReadPCXPtr(int *mf,int arg2,int arg3)

{
  bool b1;
  int *sprites;
  void *pv3;
  uint32_t stale_var;
  unsigned char frame[0x2c0] __attribute__((aligned(16)));
#define stk_2bc (*(int *)(frame + 0x4))
#define stk_2b8 (*(int *)(frame + 0x8))
#define stk_2b4 (*(int *)(frame + 0xc))
#define stk_2b0 (*(size_t *)(frame + 0x10))
#define stk_2ac (*(int (*)[152])(frame + 0x14))
#define stk_4c (*(int (*)[16])(frame + 0x274))
  
  sprites = SpriteArrayNewSize(1,1);
  if (sprites != (int *)0x0) {
    pv3 = SpriteReadPCXRawPtr(mf,&stk_2bc,&stk_2b8,&stk_2b4,&stk_2b0,stk_2ac);
    if (pv3 != (void *)0x0) {
      if (stk_2b4 < 9) {
        SpriteArrayAddPal((int)sprites,stk_2ac,0,0);
      }
      sprites[1] = (int)pv3;
      b1 = SpriteInit(stk_4c,0,pv3,stk_2b0,0,stk_2bc,stk_2b8,stk_2b4,arg2,arg3
                        );
      if (ZEXT8(b1) != 0) {
        if (stk_2b4 < 9) {
          SpriteUsePal((int)stk_4c,(int)sprites,0,0);
        }
        SpriteArrayAddSprite(sprites,stk_4c,0,0);
        return sprites;
      }
    }
    SpriteArrayFree(sprites);
  }
  return (int *)0x0;
}
#undef stk_2bc
#undef stk_2b8
#undef stk_2b4
#undef stk_2b0
#undef stk_2ac
#undef stk_4c

