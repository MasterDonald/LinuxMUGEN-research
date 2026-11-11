/*
 * spr-lib.c -- sprites and blitter dispatch
 * Sprite records and sprite arrays (sprites keyed by group and image,
 * palettes, shared instances), and the W_ drawing entry points that pick the
 * right pixel loop.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/spr-lib.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* SpriteInit @ 0x08058610, 203 bytes
 *
 * Initialises a sprite record: size, axis, colour depth, palette index (-1 =
 * none) and pixel data. With `copy` set, the data is copied into a new block
 * that the sprite owns; otherwise the sprite points at the caller's data.
 * Then builds the row table (SpriteInitLine). Returns false if allocation
 * fails.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         void *
 *   arg4         size_t
 *   arg5         int
 *   arg6         int
 *   arg7         int
 *   arg8         int
 *   arg9         int
 *   arg10        int
 *
 * Calls: SpriteInitLine
 * C library: calloc, memcpy
 * Called by: SpriteReadPCXPtr, SpriteReadSFFListPtr_1_01,
 *            SpriteReadSFFPtr_1_01, V_AllocDepthAry
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
bool SpriteInit(int *arg1,int arg2,void *arg3,size_t arg4,int arg5,int arg6,
               int arg7,int arg8,int arg9,int arg10)

{
  void *dest;
  int i1;
  int *pi2;
  
  pi2 = arg1;
  for (i1 = 0xd; i1 != 0; i1 = i1 + -1) {
    *pi2 = 0;
    pi2 = pi2 + 1;
  }
  arg1[0xc] = -1;
  arg1[7] = arg2;
  if (arg5 == 0) {
    arg1[9] = (int)arg3;
  }
  else {
    dest = calloc(1,arg4);
    arg1[9] = (int)dest;
    if (dest == (void *)0x0) {
      return false;
    }
    arg1[6] = 1;
    memcpy(dest,arg3,arg4);
  }
  arg1[8] = arg4;
  *arg1 = arg6;
  arg1[4] = arg8;
  arg1[1] = arg7;
  if (arg8 < 9) {
    arg1[5] = 1 << ((uint8_t)arg8 & 0x1f);
  }
  arg1[2] = arg9;
  arg1[3] = arg10;
  i1 = SpriteInitLine(arg1,(void *)0x0);
  return i1 != 0;
}

/* SpriteDeInit @ 0x080586e0, 90 bytes
 *
 * Frees what a sprite owns: its pixel data (destroy_bitmap for Allegro
 * bitmaps, free otherwise) and its row table.
 *
 * Parameters:
 *   arg1         int
 *
 * C library: destroy_bitmap, free
 * Called by: SpriteArrayClear, SpriteArrayFree, SpriteCopy
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void SpriteDeInit(int arg1)

{
  int *ptr;
  
  if (arg1 != 0) {
    if ((*(int *)(arg1 + 0x18) != 0) && (ptr = *(int **)(arg1 + 0x24), ptr != (int *)0x0))
    {
      if (*(int *)(arg1 + 0x1c) == 1) {
        destroy_bitmap(ptr);
      }
      else {
        free(ptr);
      }
    }
    if ((*(int *)(arg1 + 0x28) != 0) && (*(void **)(arg1 + 0x2c) != (void *)0x0)) {
      free(*(void **)(arg1 + 0x2c));
      return;
    }
  }
  return;
}

/* SpriteCopy @ 0x08058740, 195 bytes
 *
 * Copies sprite record `src` into `dest`. With `deep` set, the pixel data
 * and row table are duplicated so the copy owns them; otherwise the copy
 * shares them. Used when an SFF subfile refers to a previous sprite
 * ("linked" sprites).
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         uint32_t *
 *   arg3         int
 *
 * Calls: SpriteDeInit
 * C library: calloc, memcpy
 * Called by: SpriteReadSFFPtr_1_01
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t SpriteCopy(uint32_t *arg1,uint32_t *arg2,int arg3)

{
  void *dest;
  uint32_t *pu1;
  int i2;
  uint32_t u3;
  uint32_t *pu4;
  
  pu1 = arg2;
  pu4 = arg1;
  for (i2 = 0xd; i2 != 0; i2 = i2 + -1) {
    *pu4 = *pu1;
    pu1 = pu1 + 1;
    pu4 = pu4 + 1;
  }
  arg1[10] = 0;
  arg1[6] = 0;
  if (arg3 != 0) {
    dest = calloc(1,arg2[8]);
    arg1[9] = dest;
    if (dest == (void *)0x0) {
      return 0;
    }
    memcpy(dest,(void *)arg2[9],arg2[8]);
    arg1[6] = 1;
    if (arg1[0xb] != 0) {
      pu1 = calloc(4,arg2[1]);
      arg1[0xb] = pu1;
      if (pu1 == (uint32_t *)0x0) {
        SpriteDeInit((int)arg1);
        return 0;
      }
      pu4 = (uint32_t *)arg2[0xb];
      for (u3 = arg2[1] & 0x3fffffff; u3 != 0; u3 = u3 - 1) {
        *pu1 = *pu4;
        pu4 = pu4 + 1;
        pu1 = pu1 + 1;
      }
      arg1[10] = 1;
    }
  }
  return 1;
}

/* SpriteInitLine @ 0x08058810, 105 bytes
 *
 * Builds a sprite's row table (row n starts at n * width * bytes per pixel),
 * allocating it unless the caller supplies one. Returns the number of rows.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         void *
 *
 * Calls: ColDepthToBytesPerPixel
 * C library: calloc
 * Called by: SpriteInit
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
int SpriteInitLine(int *arg1,void *arg2)

{
  int i1;
  int i2;
  int i3;
  int i4;
  
  i4 = 0;
  if (arg1[0xb] == 0) {
    if (arg2 == (void *)0x0) {
      arg2 = calloc(4,arg1[1]);
      if (arg2 == (void *)0x0) goto L_0805883e;
      arg1[10] = 1;
    }
    i2 = ColDepthToBytesPerPixel(arg1[4]);
    i1 = *arg1;
    i3 = 0;
    if (0 < arg1[1]) {
      do {
        *(int *)((int)arg2 + i3 * 4) = i4;
        i3 = i3 + 1;
        i4 = i4 + i2 * i1;
      } while (i3 < arg1[1]);
    }
    arg1[0xb] = (int)arg2;
    i4 = arg1[1];
  }
  else {
L_0805883e:
    i4 = 0;
  }
  return i4;
}

/* SpriteUsePal @ 0x08058880, 80 bytes
 *
 * Attaches palette (group, image) from the sprite array to a sprite.
 * Succeeds only if the palette's colour count matches the sprite's. Returns
 * 1 on success.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *   arg4         int
 *
 * Calls: ArrayFind
 * Called by: SpriteReadPCXPtr, SpriteReadSFFListPtr_1_01,
 *            SpriteReadSFFPtr_1_01
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t SpriteUsePal(int arg1,int arg2,int arg3,int arg4)

{
  uint32_t index;
  uint32_t u2;
  
  index = ArrayFind(*(int *)(arg2 + 8),arg3,arg4);
  if ((index == 0xffffffff) ||
     (*(int *)(index * *(int *)(*(int *)(arg2 + 8) + 4) + *(int *)(*(int *)(arg2 + 8) + 0x14))
      != *(int *)(arg1 + 0x14))) {
    u2 = 0;
  }
  else {
    *(uint32_t *)(arg1 + 0x30) = index;
    u2 = 1;
  }
  return u2;
}

/* SpriteSetAxis @ 0x080588d0, 19 bytes
 *
 * Sets a sprite's axis (the point placed at the drawing position).
 *
 * Parameters:
 *   arg1         int
 *   arg2         uint32_t
 *   arg3         uint32_t
 *
 * Called by: SpriteReadSFFPtr_1_01
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void SpriteSetAxis(int arg1,uint32_t arg2,uint32_t arg3)

{
  *(uint32_t *)(arg1 + 0xc) = arg3;
  *(uint32_t *)(arg1 + 8) = arg2;
  return;
}

/* SpriteArrayNew @ 0x080588f0, 16 bytes
 *
 * Creates an empty sprite array (SpriteArrayNewSize(0, 0)). Not called in
 * this build.
 *
 * Calls: SpriteArrayNewSize
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void SpriteArrayNew(void)

{
  SpriteArrayNewSize(0,0);
  return;
}

/* SpriteArrayNewSize @ 0x08058900, 93 bytes
 *
 * Creates a sprite array with room for `nsprites` sprites and `npals`
 * palettes (each array is created only if its size is positive). Returns
 * NULL on failure.
 *
 * Parameters:
 *   arg1         size_t
 *   arg2         size_t
 *
 * Calls: ecalloc, ArrayNew
 * Called by: PlayerNew, SpriteArrayNew, SpriteReadPCXPtr,
 *            SpriteReadSFFListPtr_1_01, SpriteReadSFFPtr_1_01,
 *            V_AllocDepthAry
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t * SpriteArrayNewSize(size_t arg1,size_t arg2)

{
  uint32_t *mem;
  uint32_t *array;
  
  mem = (uint32_t *)ecalloc(1,0x1c);
  if (mem != (uint32_t *)0x0) {
    if (0 < (int)arg1) {
      array = ArrayNew(arg1,0x34,0);
      *mem = array;
      if (array == (uint32_t *)0x0) {
        return (uint32_t *)0x0;
      }
    }
    if ((int)arg2 < 1) {
      return mem;
    }
    array = ArrayNew(arg2,0x25c,0);
    mem[2] = array;
    if (array != (uint32_t *)0x0) {
      return mem;
    }
  }
  return (uint32_t *)0x0;
}

/* SpriteArrayNewInstance @ 0x08058960, 191 bytes
 *
 * Creates an instance of a sprite array: a new header that shares the
 * sprites of the root array but has its own copy of the palettes. Each
 * player gets an instance of its character's sprites, so two players using
 * the same character can show different palettes (colour selection, PalFX).
 * Returns NULL on failure.
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: ecalloc, ArrayCopy, SpriteArrayFree, ArrayScanFirst,
 *        ArrayScanNext
 * Called by: PlayerNew
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
int * SpriteArrayNewInstance(int *arg1)

{
  int array;
  int *mem;
  uint32_t *array2;
  int item;
  int *pi5;
  int *pi6;
  int *stk_14;
  
  mem = (int *)ecalloc(1,0x1c);
  if (mem == (int *)0x0) {
    mem = (int *)0x0;
  }
  else {
    stk_14 = (int *)arg1[3];
    if (stk_14 == (int *)0x0) {
      stk_14 = arg1;
    }
    pi5 = arg1;
    pi6 = mem;
    for (item = 7; item != 0; item = item + -1) {
      *pi6 = *pi5;
      pi5 = pi5 + 1;
      pi6 = pi6 + 1;
    }
    mem[2] = 0;
    mem[3] = (int)stk_14;
    array2 = (uint32_t *)arg1[2];
    mem[4] = 0;
    if (array2 != (uint32_t *)0x0) {
      array2 = ArrayCopy(array2);
      mem[2] = (int)array2;
      if (array2 == (uint32_t *)0x0) {
        SpriteArrayFree(mem);
        return (int *)0x0;
      }
      item = ArrayScanFirst((int)array2);
      while (item != 0) {
        array = mem[2];
        *(uint32_t *)(item + 4) = 0;
        item = ArrayScanNext(array);
      }
    }
    stk_14[4] = stk_14[4] + 1;
  }
  return mem;
}

/* SpriteArrayNewInstanceOnto @ 0x08058a20, 207 bytes
 *
 * Turns an existing sprite array into an instance of `src`: clears it, then
 * shares src's sprites and copies its palettes, reusing the existing palette
 * storage. Used for helpers and when a player changes palette. Fails if the
 * array itself has instances.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int *
 *
 * Calls: SpriteArrayClear, ArrayFree, ArrayCopyOnto, ArrayScanFirst,
 *        ArrayScanNext
 * Called by: HelperMake, PlayerChangePal, PlayerNew
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
int * SpriteArrayNewInstanceOnto(int *arg1,int *arg2)

{
  int item;
  uint32_t *array;
  int array2;
  int *pi4;
  int *pi5;
  int *stk_14;
  
  if (arg1[4] < 1) {
    stk_14 = (int *)arg2[3];
    if (stk_14 == (int *)0x0) {
      stk_14 = arg2;
    }
    item = SpriteArrayClear(arg1);
    if (item != 0) {
      if ((void *)*arg1 != (void *)0x0) {
        ArrayFree((void *)*arg1);
        *arg1 = 0;
      }
      item = arg1[2];
      pi4 = arg2;
      pi5 = arg1;
      for (array2 = 7; array2 != 0; array2 = array2 + -1) {
        *pi5 = *pi4;
        pi4 = pi4 + 1;
        pi5 = pi5 + 1;
      }
      arg1[2] = item;
      array = (uint32_t *)arg2[2];
      arg1[3] = (int)stk_14;
      arg1[4] = 0;
      if (array != (uint32_t *)0x0) {
        array = ArrayCopyOnto((uint32_t *)arg1[2],array);
        if (array == (uint32_t *)0x0) {
          return (int *)0x0;
        }
        item = ArrayScanFirst(arg1[2]);
        while (item != 0) {
          array2 = arg1[2];
          *(uint32_t *)(item + 4) = 0;
          item = ArrayScanNext(array2);
        }
      }
      stk_14[4] = stk_14[4] + 1;
      return arg1;
    }
  }
  return (int *)0x0;
}

/* SpriteArrayAddSprite @ 0x08058af0, 76 bytes
 *
 * Adds a sprite record under key (group, image), creating the sprite list on
 * first use and growing it as needed. Returns nonzero on success.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         void *
 *   arg3         uint32_t
 *   arg4         uint32_t
 *
 * Calls: ArrayNew, ArrayAddResize
 * Called by: SpriteReadPCXPtr, SpriteReadSFFListPtr_1_01,
 *            SpriteReadSFFPtr_1_01, V_AllocDepthAry
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t SpriteArrayAddSprite(int *arg1,void *arg2,uint32_t arg3,uint32_t arg4)

{
  uint32_t *array;
  int index;
  
  if (*arg1 == 0) {
    array = ArrayNew(1,0x34,0);
    *arg1 = (int)array;
    if (array == (uint32_t *)0x0) {
      return 0;
    }
  }
  index = ArrayAddResize(*arg1,arg2,arg3,arg4);
  return (uint32_t)(index != -1);
}

/* SpriteArrayAddPal @ 0x08058b40, 87 bytes
 *
 * Adds a palette under key (group, image), creating the palette list on
 * first use. Returns nonzero on success.
 *
 * Parameters:
 *   arg1         int
 *   arg2         void *
 *   arg3         uint32_t
 *   arg4         uint32_t
 *
 * Calls: ArrayNew, ArrayAddResize
 * Called by: FontReadFilePtr_0_01, PlayerDefLoadPtr, PlayerDefLoadZip,
 *            SpriteReadPCXPtr, SpriteReadSFFListPtr_1_01,
 *            SpriteReadSFFPtr_1_01
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t SpriteArrayAddPal(int arg1,void *arg2,uint32_t arg3,uint32_t arg4)

{
  uint32_t *array;
  int index;
  
  if (*(int *)(arg1 + 8) == 0) {
    array = ArrayNew(1,0x25c,0);
    *(uint32_t **)(arg1 + 8) = array;
    if (array == (uint32_t *)0x0) {
      return 0;
    }
  }
  index = ArrayAddResize(*(int *)(arg1 + 8),arg2,arg3,arg4);
  return (uint32_t)(index != -1);
}

/* SpriteArrayNumImages @ 0x08058ba0, 10 bytes
 *
 * Returns the number of sprites in a sprite array. Not called in this build.
 *
 * Parameters:
 *   arg1         int *
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t SpriteArrayNumImages(int *arg1)

{
  return *(uint32_t *)(*arg1 + 8);
}

/* SpriteArrayNumPals @ 0x08058bb0, 11 bytes
 *
 * Returns the number of palettes in a sprite array.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: V_FontDrawLineBank
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t SpriteArrayNumPals(int arg1)

{
  return *(uint32_t *)(*(int *)(arg1 + 8) + 8);
}

/* SpriteArrayFree @ 0x08058bc0, 208 bytes
 *
 * Frees a sprite array: every palette (EBPalDeInit) and the palette list,
 * and every sprite (SpriteDeInit) and the sprite list unless they belong to
 * a root array. Then the raw file data and the header. Instances decrement
 * their root's instance count.
 *
 * Parameters:
 *   sprites      int *
 *
 * Calls: ArrayScanFirst, EBPalDeInit, ArrayScanNext, ArrayFree,
 *        SpriteDeInit
 * C library: free
 * Called by: AnimFree, BGArrayFree, FontFree, GameFreeFightData,
 *            GameStgDeInitFightData, GameUnloadSystem,
 *            GameUnloadSystemSprSnd, PlayerFree, PlayerRCFree,
 *            SiSceneFree, SpriteArrayNewInstance, SpriteReadPCXPtr,
 *            SpriteReadSFFListPtr_1_01, SpriteReadSFFPtr_1_01,
 *            V_AllocDepthAry, V_DeAlloc
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t SpriteArrayFree(int *sprites)

{
  int item;
  
  if (sprites != (int *)0x0) {
    if (0 < sprites[4]) {
      return 0;
    }
    if (sprites[2] != 0) {
      item = ArrayScanFirst(sprites[2]);
      while (item != 0) {
        EBPalDeInit(item);
        item = ArrayScanNext(sprites[2]);
      }
      ArrayFree((void *)sprites[2]);
    }
    item = sprites[3];
    if (item == 0) {
      if (*sprites != 0) {
        item = ArrayScanFirst(*sprites);
        while (item != 0) {
          SpriteDeInit(item);
          item = ArrayScanNext(*sprites);
        }
        ArrayFree((void *)*sprites);
      }
      if ((void *)sprites[1] != (void *)0x0) {
        free((void *)sprites[1]);
      }
      item = sprites[3];
    }
    if (item != 0) {
      *(int *)(item + 0x10) = *(int *)(item + 0x10) + -1;
    }
    free(sprites);
  }
  return 1;
}

/* SpriteArrayClear @ 0x08058c90, 219 bytes
 *
 * Empties a sprite array (palettes and sprites deinitialised, lists cleared)
 * but keeps the header and the lists for reuse.
 *
 * Parameters:
 *   arg1         int *
 *
 * Calls: ArrayScanFirst, EBPalDeInit, ArrayScanNext, ArrayClear,
 *        SpriteDeInit
 * C library: free
 * Called by: SpriteArrayNewInstanceOnto
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t SpriteArrayClear(int *arg1)

{
  int item;
  
  if (arg1 == (int *)0x0) {
    return 1;
  }
  if (0 < arg1[4]) {
    return 0;
  }
  if (arg1[2] != 0) {
    item = ArrayScanFirst(arg1[2]);
    while (item != 0) {
      EBPalDeInit(item);
      item = ArrayScanNext(arg1[2]);
    }
    ArrayClear(arg1[2]);
  }
  if (arg1[3] == 0) {
    if (*arg1 != 0) {
      item = ArrayScanFirst(*arg1);
      while (item != 0) {
        SpriteDeInit(item);
        item = ArrayScanNext(*arg1);
      }
      ArrayClear(*arg1);
    }
    if ((void *)arg1[1] == (void *)0x0) goto L_08058d4d;
    free((void *)arg1[1]);
  }
  else {
    *arg1 = 0;
  }
  arg1[1] = 0;
L_08058d4d:
  item = arg1[3];
  if (item != 0) {
    *(int *)(item + 0x10) = *(int *)(item + 0x10) + -1;
  }
  arg1[3] = 0;
  return 1;
}

/* SpriteArrayGetNum @ 0x08058d70, 15 bytes
 *
 * Returns the index of sprite (group, image), or -1. Animations call this to
 * find the sprite of each element.
 *
 * Parameters:
 *   sprites      int *
 *   group        int
 *   number       int
 *
 * Calls: ArrayFind
 * Called by: AnimUpdate, BGArrayAdd, CharacterSelectScreenDraw,
 *            ExplodAddSprite, PlayerChangePal, PlayerCheck,
 *            SpriteArrayPalRemapFromRootGrpItem, VersusScreen,
 *            W_PutSpriteA, W_PutSpriteAMirH, W_PutSpriteAMirHPal,
 *            W_PutSpriteAPal
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t SpriteArrayGetNum(int *sprites,int group,int number)

{
  uint32_t index;
  
  index = ArrayFind(*sprites,group,number);
  return index;
}

/* SpriteArrayPalGetNum @ 0x08058d80, 16 bytes
 *
 * Returns the index of palette (group, image), or -1.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *
 * Calls: ArrayFind
 * Called by: PlayerChangePal
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t SpriteArrayPalGetNum(int arg1,int arg2,int arg3)

{
  uint32_t index;
  
  index = ArrayFind(*(int *)(arg1 + 8),arg2,arg3);
  return index;
}

/* SpriteArrayAccess @ 0x08058d90, 22 bytes
 *
 * Returns the sprite record at `index` (no check).
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *
 * Called by: AftImgDraw, AnimDrawFlip, AnimDrawRotateFlip,
 *            AnimDrawScaleFlip, BGArrayAdd, BGNormalDrawTile,
 *            BGParalDraw8to16, BGParalDraw8to16Flat, BGParalDrawScale,
 *            BGParalSetup, DrawToScreen, FontReadFilePtr_0_01,
 *            PlayerChangePal, ScreenSnap, SpriteDecompGetData,
 *            SpriteReadSFFPtr_1_01, ... (145 callers)
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
int SpriteArrayAccess(int *sprites,int index)

{
  return *(int *)(*sprites + 4) * index + *(int *)(*sprites + 0x14);
}

/* SpriteArrayAccessGrpItem @ 0x08058db0, 15 bytes
 *
 * Returns the sprite record with key (group, image), or NULL.
 *
 * Parameters:
 *   arg1         int *
 *   arg2         int
 *   arg3         int
 *
 * Calls: ArrayAccessGrpItem
 * Called by: BGArrayReadTP
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t SpriteArrayAccessGrpItem(int *arg1,int arg2,int arg3)

{
  uint32_t item;
  
  item = ArrayAccessGrpItem(*arg1,arg2,arg3);
  return item;
}

/* SpriteArrayPalAccess @ 0x08058dc0, 23 bytes
 *
 * Returns the palette at `index`.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *
 * Called by: AftImgDraw, FontReadFilePtr_0_01, SpriteArrayPalRemapFromRoot
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
int SpriteArrayPalAccess(int arg1,int arg2)

{
  return *(int *)(*(int *)(arg1 + 8) + 4) * arg2 + *(int *)(*(int *)(arg1 + 8) + 0x14);
}

/* SpriteArrayPalAccessGrpItem @ 0x08058de0, 16 bytes
 *
 * Returns the palette with key (group, image), or NULL. Not called in this
 * build.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *
 * Calls: ArrayAccessGrpItem
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void SpriteArrayPalAccessGrpItem(int arg1,int arg2,int arg3)

{
  ArrayAccessGrpItem(*(int *)(arg1 + 8),arg2,arg3);
  return;
}

/* SpriteArrayPalUpdateAndAccess @ 0x08058df0, 39 bytes
 *
 * Returns the palette at `index` after bringing its 16-bit colour table up
 * to date (EBPalUpdate). Blitters call this before drawing an 8-bit sprite
 * on a 16-bit buffer.
 *
 * Parameters:
 *   sprites      int
 *   index        int
 *
 * Calls: EBPalUpdate
 * Called by: BGParalDraw8to16, BGParalDraw8to16Flat, V_FontDrawLineBank,
 *            W_PutSprite8to16, W_PutSpriteFlat8to16, W_PutSpriteMirH8to16,
 *            W_PutSpriteMirHV8to16, W_PutSpriteMirV8to16,
 *            W_PutSpriteTransAdd8to16, W_PutSpriteTransAdd8to16_B,
 *            W_PutSpriteTransAddMirH8to16, W_PutSpriteTransAddMirH8to16_B,
 *            W_PutSpriteTransAddMirHV8to16,
 *            W_PutSpriteTransAddMirHV8to16_B,
 *            W_PutSpriteTransAddMirV8to16, W_PutSpriteTransAddMirV8to16_B,
 *            ... (51 callers)
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
int * SpriteArrayPalUpdateAndAccess(int sprites,int index)

{
  int *pi1;
  
  pi1 = (int *)(index * *(int *)(*(int *)(sprites + 8) + 4) +
                  *(int *)(*(int *)(sprites + 8) + 0x14));
  EBPalUpdate(pi1);
  return pi1;
}

/* SpriteArrayPalRemapFromRoot @ 0x08058e20, 73 bytes
 *
 * Copies palette `src` of the root sprite array into palette `dest` of this
 * instance (EBPalCopy). This is how a player's colour selection or the
 * RemapPal state controller swaps palettes. Returns false when the array is
 * not an instance.
 *
 * Parameters:
 *   arg1         int
 *   arg2         int
 *   arg3         int
 *
 * Calls: SpriteArrayPalAccess, EBPalCopy
 * Called by: PlayerChangePal, SpriteArrayPalRemapFromRootGrpItem
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
bool SpriteArrayPalRemapFromRoot(int arg1,int arg2,int arg3)

{
  int *pi1;
  int *pi2;
  bool b3;
  
  b3 = *(int *)(arg1 + 0xc) != 0;
  if (b3) {
    pi1 = (int *)SpriteArrayPalAccess(*(int *)(arg1 + 0xc),arg3);
    pi2 = (int *)SpriteArrayPalAccess(arg1,arg2);
    EBPalCopy(pi2,pi1,0);
  }
  return b3;
}

/* SpriteArrayPalRemapFromRootGrpItem @ 0x08058e70, 106 bytes
 *
 * SpriteArrayPalRemapFromRoot with both palettes given by key (group,
 * image). Not called in this build.
 *
 * Parameters:
 *   sprites      int *
 *   group        int
 *   arg3         int
 *   group2       int  (group)
 *   arg5         int
 *
 * Calls: SpriteArrayGetNum, SpriteArrayPalRemapFromRoot
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
bool SpriteArrayPalRemapFromRootGrpItem
               (int *sprites,int group,int arg3,int group2,int arg5)

{
  bool b1;
  int index;
  int index2;
  
  if (sprites[3] != 0) {
    index = SpriteArrayGetNum(sprites,group,arg3);
    index2 = SpriteArrayGetNum(sprites,group2,arg5);
    if ((index != -1) && (index2 != -1)) {
      b1 = SpriteArrayPalRemapFromRoot((int)sprites,index,index2);
      return b1;
    }
  }
  return false;
}

/* ColDepthToBytesPerPixel @ 0x08058ee0, 11 bytes
 *
 * Returns (depth + 7) / 8: 1 for 8-bit, 2 for 15/16-bit, 3 or 4 for
 * 24/32-bit.
 *
 * Parameters:
 *   arg1         int
 *
 * Called by: SpriteInitLine, W_Cls, W_PutPixel
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
int ColDepthToBytesPerPixel(int arg1)

{
  return arg1 + 7 >> 3;
}

/* SpriteDecompGetData @ 0x08058ef0, 60 bytes
 *
 * Returns a pointer to a sprite's pixels: the data block for raw sprites,
 * the bitmap's line memory for Allegro bitmaps, or NULL.
 *
 * Parameters:
 *   sprites      int *
 *   arg2         int
 *
 * Calls: SpriteArrayAccess
 * Called by: BGParalDraw8to16, BGParalDraw8to16Flat,
 *            SpriteDecompGetAndLockData, V_FontDrawLineBank,
 *            W_PutSprite8to16, W_PutSpriteFlat8to16, W_PutSpriteMirH8to16,
 *            W_PutSpriteMirHV8to16, W_PutSpriteMirV8to16,
 *            W_PutSpriteShadow8to16, W_PutSpriteTransAdd8to16,
 *            W_PutSpriteTransAdd8to16_B, W_PutSpriteTransAddMirH8to16,
 *            W_PutSpriteTransAddMirH8to16_B,
 *            W_PutSpriteTransAddMirHV8to16,
 *            W_PutSpriteTransAddMirHV8to16_B, ... (53 callers)
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t SpriteDecompGetData(int *sprites,int arg2)

{
  int sprite;
  uint32_t u2;
  
  sprite = SpriteArrayAccess(sprites,arg2);
  u2 = 0;
  if (sprite != 0) {
    if (*(int *)(sprite + 0x1c) == 0) {
      u2 = *(uint32_t *)(sprite + 0x24);
    }
    else if (*(int *)(sprite + 0x1c) == 1) {
      u2 = *(uint32_t *)(*(int *)(sprite + 0x24) + 0x28);
    }
  }
  return u2;
}

/* SpriteDecompGetAndLockData @ 0x08058f30, 5 bytes
 *
 * SpriteDecompGetData; the "lock" is a no-op in this build (sprites are
 * stored decompressed).
 *
 * Parameters:
 *   sprites      int *
 *   arg2         int
 *
 * Calls: SpriteDecompGetData
 * Called by: BGParalDraw8to16, BGParalDraw8to16Flat, V_FontDrawLineBank,
 *            W_PutSprite8to16, W_PutSpriteFlat8to16, W_PutSpriteMirH8to16,
 *            W_PutSpriteMirHV8to16, W_PutSpriteMirV8to16,
 *            W_PutSpriteShadow8to16, W_PutSpriteTransAdd8to16,
 *            W_PutSpriteTransAdd8to16_B, W_PutSpriteTransAddMirH8to16,
 *            W_PutSpriteTransAddMirH8to16_B,
 *            W_PutSpriteTransAddMirHV8to16,
 *            W_PutSpriteTransAddMirHV8to16_B,
 *            W_PutSpriteTransAddMirV8to16, ... (52 callers)
 *
 * Elecbyte file: src/lib/spr-lib.c
 * Note: decompiler flag: the second decompiler pass lost the call(s) to
 *       SpriteArrayAccess
 */
uint32_t SpriteDecompGetAndLockData(int *sprites,int arg2)

{
  uint32_t u1;
  
  u1 = SpriteDecompGetData(sprites,arg2);
  return u1;
}

/* SpriteDecompUnlockData @ 0x08058f40, 1 bytes
 *
 * Empty counterpart of SpriteDecompGetAndLockData.
 *
 * Called by: BGParalDraw8to16, BGParalDraw8to16Flat, V_FontDrawLineBank,
 *            W_PutSprite8to16, W_PutSpriteFlat8to16, W_PutSpriteMirH8to16,
 *            W_PutSpriteMirHV8to16, W_PutSpriteMirV8to16,
 *            W_PutSpriteShadow8to16, W_PutSpriteTransAdd8to16,
 *            W_PutSpriteTransAdd8to16_B, W_PutSpriteTransAddMirH8to16,
 *            W_PutSpriteTransAddMirH8to16_B,
 *            W_PutSpriteTransAddMirHV8to16,
 *            W_PutSpriteTransAddMirHV8to16_B,
 *            W_PutSpriteTransAddMirV8to16, ... (52 callers)
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t SpriteDecompUnlockData(void)

{
  uint32_t entry_EAX;
  
  return entry_EAX;
}

/* W_PutSurface @ 0x08058f50, 1 bytes
 *
 * Empty: drawing a sprite onto a surface of the same depth is not
 * implemented in this build.
 *
 * Called by: W_PutSprite
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_PutSurface(void)

{
  return;
}

/* W_PutSprite @ 0x08058f60, 136 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * with colour 0 transparent. Clipped to the window set by W_Define.
 * Dispatcher: when the screen is 15/16-bit and the sprite is 8-bit it calls
 * the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *
 * Calls: SpriteArrayAccess, W_PutSprite8to16, W_PutSurface
 * Called by: AnimDrawSprFlip, EB_GUIPutSprite, V_FontDrawLine,
 *            W_PutSpriteA, W_PutSpriteAPal, W_ScaleSprite
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t W_PutSprite(int *sprites,int index,int x,int y)

{
  int sprite;
  uint32_t stale_EAX;
  uint32_t stale_EAX_00;
  
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) && (0xe < V_ColDepth)) {
    sprite = SpriteArrayAccess(sprites,index);
    if (*(int *)(sprite + 0x10) == 8) {
      W_PutSprite8to16(sprites,index,x,y);
      return stale_EAX;
    }
    W_PutSurface();
    return stale_EAX_00;
  }
  return V_ColDepth;
}

/* W_PutSpriteA @ 0x08058ff0, 76 bytes
 *
 * Draws the sprite with key (group, image) at (x, y). Looks the key up with
 * SpriteArrayGetNum. Not called in this build.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *   arg5         int
 *
 * Calls: SpriteArrayGetNum, W_PutSprite
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_PutSpriteA(int *sprites,int index,int x,int y,int arg5)

{
  int index2;
  
  if ((-1 < index) && (-1 < x)) {
    index2 = SpriteArrayGetNum(sprites,index,x);
    if (index2 != -1) {
      W_PutSprite(sprites,index2,y,arg5);
      return;
    }
  }
  return;
}

/* W_PutSpriteAMirH @ 0x08059040, 76 bytes
 *
 * Draws the sprite with key (group, image) at (x, y), mirrored horizontally.
 * Looks the key up with SpriteArrayGetNum. Not called in this build.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *   arg5         int
 *
 * Calls: SpriteArrayGetNum, W_PutSpriteMirH
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_PutSpriteAMirH(int *sprites,int index,int x,int y,int arg5)

{
  int index2;
  
  if ((-1 < index) && (-1 < x)) {
    index2 = SpriteArrayGetNum(sprites,index,x);
    if (index2 != -1) {
      W_PutSpriteMirH(sprites,index2,y,arg5);
      return;
    }
  }
  return;
}

/* W_PutSpriteAPal @ 0x08059090, 98 bytes
 *
 * Draws the sprite with key (group, image) at (x, y), using an explicitly
 * given palette. Looks the key up with SpriteArrayGetNum. Not called in this
 * build.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            uint32_t
 *   arg5         int
 *   arg6         int
 *
 * Calls: SpriteArrayGetNum, SpriteArrayAccess, W_PutSprite
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_PutSpriteAPal(int *sprites,int index,int x,uint32_t y,int arg5,int arg6
                    )

{
  uint32_t u1;
  int index2;
  int sprite;
  
  if ((-1 < index) && (-1 < x)) {
    index2 = SpriteArrayGetNum(sprites,index,x);
    if (index2 != -1) {
      sprite = SpriteArrayAccess(sprites,index2);
      u1 = *(uint32_t *)(sprite + 0x30);
      *(uint32_t *)(sprite + 0x30) = y;
      W_PutSprite(sprites,index2,arg5,arg6);
      *(uint32_t *)(sprite + 0x30) = u1;
    }
  }
  return;
}

/* W_PutSpriteAMirHPal @ 0x08059100, 98 bytes
 *
 * Draws the sprite with key (group, image) at (x, y), mirrored horizontally,
 * using an explicitly given palette. Looks the key up with
 * SpriteArrayGetNum. Not called in this build.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            uint32_t
 *   arg5         int
 *   arg6         int
 *
 * Calls: SpriteArrayGetNum, SpriteArrayAccess, W_PutSpriteMirH
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_PutSpriteAMirHPal(int *sprites,int index,int x,uint32_t y,int arg5,
                        int arg6)

{
  uint32_t u1;
  int index2;
  int sprite;
  
  if ((-1 < index) && (-1 < x)) {
    index2 = SpriteArrayGetNum(sprites,index,x);
    if (index2 != -1) {
      sprite = SpriteArrayAccess(sprites,index2);
      u1 = *(uint32_t *)(sprite + 0x30);
      *(uint32_t *)(sprite + 0x30) = y;
      W_PutSpriteMirH(sprites,index2,arg5,arg6);
      *(uint32_t *)(sprite + 0x30) = u1;
    }
  }
  return;
}

/* W_PutSpriteFlat @ 0x08059170, 92 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * opaque (colour 0 is drawn too). Clipped to the window set by W_Define.
 * Dispatcher: when the screen is 15/16-bit and the sprite is 8-bit it calls
 * the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteFlat8to16
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_PutSpriteFlat(int *sprites,int index,int x,int y)

{
  int sprite;
  
  if ((V_ColDepth < 0x11) && (0xe < V_ColDepth)) {
    sprite = SpriteArrayAccess(sprites,index);
    if (*(int *)(sprite + 0x10) == 8) {
      W_PutSpriteFlat8to16(sprites,index,x,y);
      return;
    }
  }
  return;
}

/* W_PutSpriteMirH @ 0x080591d0, 92 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * with colour 0 transparent, mirrored horizontally. Clipped to the window
 * set by W_Define. Dispatcher: when the screen is 15/16-bit and the sprite
 * is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteMirH8to16
 * Called by: AnimDrawSprFlip, W_PutSpriteAMirH, W_PutSpriteAMirHPal
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t W_PutSpriteMirH(int *sprites,int index,int x,int y)

{
  int sprite;
  uint32_t stale_EAX;
  
  sprite = V_ColDepth;
  if ((V_ColDepth < 0x11) && (0xe < V_ColDepth)) {
    sprite = SpriteArrayAccess(sprites,index);
    if (*(int *)(sprite + 0x10) == 8) {
      W_PutSpriteMirH8to16(sprites,index,x,y);
      return stale_EAX;
    }
  }
  return sprite;
}

/* W_PutSpriteMirV @ 0x08059230, 92 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * with colour 0 transparent, mirrored vertically. Clipped to the window set
 * by W_Define. Dispatcher: when the screen is 15/16-bit and the sprite is
 * 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteMirV8to16
 * Called by: AnimDrawSprFlip
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t W_PutSpriteMirV(int *sprites,int index,int x,int y)

{
  int sprite;
  uint32_t stale_EAX;
  
  sprite = V_ColDepth;
  if ((V_ColDepth < 0x11) && (0xe < V_ColDepth)) {
    sprite = SpriteArrayAccess(sprites,index);
    if (*(int *)(sprite + 0x10) == 8) {
      W_PutSpriteMirV8to16(sprites,index,x,y);
      return stale_EAX;
    }
  }
  return sprite;
}

/* W_PutSpriteMirHV @ 0x08059290, 92 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * with colour 0 transparent, mirrored horizontally and vertically. Clipped
 * to the window set by W_Define. Dispatcher: when the screen is 15/16-bit
 * and the sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteMirHV8to16
 * Called by: AnimDrawSprFlip
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t W_PutSpriteMirHV(int *sprites,int index,int x,int y)

{
  int sprite;
  uint32_t stale_EAX;
  
  sprite = V_ColDepth;
  if ((V_ColDepth < 0x11) && (0xe < V_ColDepth)) {
    sprite = SpriteArrayAccess(sprites,index);
    if (*(int *)(sprite + 0x10) == 8) {
      W_PutSpriteMirHV8to16(sprites,index,x,y);
      return stale_EAX;
    }
  }
  return sprite;
}

/* W_PutSpriteShadow @ 0x080592f0, 152 bytes
 *
 * Draws the shape of sprite `index` (a shadow) of a sprite array into the
 * current drawing buffer, in a solid colour. Clipped to the window set by
 * W_Define. Dispatcher: when the screen is 15/16-bit and the sprite is 8-bit
 * it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *   arg5         uint16_t
 *
 * Calls: SpriteArrayAccess, W_PutSpriteShadow8to16, W_PutSpriteShadow16
 * Called by: V_FontDrawLine
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_PutSpriteShadow(int *sprites,int index,int x,int y,uint16_t arg5)

{
  int sprite;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((V_ColDepth < 0x11) && (0xe < V_ColDepth)) {
    if (*(int *)(sprite + 0x10) == 8) {
      W_PutSpriteShadow8to16(sprites,index,x,y,arg5);
      return;
    }
    if (*(int *)(sprite + 0x10) == 0x10) {
      W_PutSpriteShadow16();
      return;
    }
  }
  return;
}

/* W_ScaleSprite @ 0x08059390, 239 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, with colour 0 transparent. Clipped to the window set by W_Define.
 * Dispatcher: when the screen is 15/16-bit and the sprite is 8-bit it calls
 * the 8to16 pixel loop. At scale 1 it uses W_PutSprite.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, W_ScaleSprite8to16, W_PutSprite
 * Called by: W_ScaleSprite_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
void W_ScaleSprite(int *sprites,int index,float x,float y,float arg5,float arg6)

{
  int sprite;
  int *sprite2;
  
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (sprite = SpriteArrayAccess(sprites,index), *(int *)(sprite + 0x10) == 8)
      ))) {
    W_ScaleSprite8to16(sprites,index,x,y,arg5,arg6);
    return;
  }
  sprite2 = (int *)SpriteArrayAccess(sprites,index);
  if (((float)*sprite2 == arg5) &&
     (sprite = SpriteArrayAccess(sprites,index), (float80)*(int *)(sprite + 4) == arg6)) {
    W_PutSprite(sprites,index,(int)X87_FIST32(x),(int)X87_FIST32(y));
  }
  return;
}

/* W_ScaleSpriteFlat @ 0x08059480, 124 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, opaque (colour 0 is drawn too). Clipped to the window set by
 * W_Define. Dispatcher: when the screen is 15/16-bit and the sprite is 8-bit
 * it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteFlat8to16
 * Called by: W_ScaleSpriteFlat_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleSpriteFlat(int *sprites,int index,float x,float y,float arg5,
                      float arg6)

{
  int sprite;
  
  if ((V_ColDepth < 0x11) && (0xe < V_ColDepth)) {
    sprite = SpriteArrayAccess(sprites,index);
    if (*(int *)(sprite + 0x10) == 8) {
      W_ScaleSpriteFlat8to16(sprites,index,x,y,arg5,arg6);
      return;
    }
  }
  return;
}

/* W_ScaleSpriteMirH @ 0x08059500, 136 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, with colour 0 transparent, mirrored horizontally. Clipped to the
 * window set by W_Define. Dispatcher: when the screen is 15/16-bit and the
 * sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteMirH8to16
 * Called by: W_ScaleSprite_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleSpriteMirH(int *sprites,int index,float x,float y,float arg5,
                      float arg6)

{
  int sprite;
  
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) && (0xe < V_ColDepth)) {
    sprite = SpriteArrayAccess(sprites,index);
    if (*(int *)(sprite + 0x10) == 8) {
      W_ScaleSpriteMirH8to16(sprites,index,x,y,arg5,arg6);
      return;
    }
  }
  return;
}

/* W_ScaleSpriteMirV @ 0x08059590, 136 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, with colour 0 transparent, mirrored vertically. Clipped to the
 * window set by W_Define. Dispatcher: when the screen is 15/16-bit and the
 * sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteMirV8to16
 * Called by: W_ScaleSprite_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleSpriteMirV(int *sprites,int index,float x,float y,float arg5,
                      float arg6)

{
  int sprite;
  
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) && (0xe < V_ColDepth)) {
    sprite = SpriteArrayAccess(sprites,index);
    if (*(int *)(sprite + 0x10) == 8) {
      W_ScaleSpriteMirV8to16(sprites,index,x,y,arg5,arg6);
      return;
    }
  }
  return;
}

/* W_ScaleSpriteMirHV @ 0x08059620, 136 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, with colour 0 transparent, mirrored horizontally and vertically.
 * Clipped to the window set by W_Define. Dispatcher: when the screen is
 * 15/16-bit and the sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteMirHV8to16
 * Called by: W_ScaleSprite_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleSpriteMirHV(int *sprites,int index,float x,float y,float arg5,
                       float arg6)

{
  int sprite;
  
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) && (0xe < V_ColDepth)) {
    sprite = SpriteArrayAccess(sprites,index);
    if (*(int *)(sprite + 0x10) == 8) {
      W_ScaleSpriteMirHV8to16(sprites,index,x,y,arg5,arg6);
      return;
    }
  }
  return;
}

/* W_ScaleSprite_S @ 0x080596b0, 328 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, with colour 0 transparent. Clipped to the window set by W_Define.
 * Takes float scale factors: a negative x or y scale selects the mirrored
 * variant, so this is the entry point used by animations and backgrounds.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, W_ScaleSprite, W_ScaleSpriteMirH,
 *        W_ScaleSpriteMirV, W_ScaleSpriteMirHV
 * Called by: AnimScaleSpr_S, BGDraw, BGNormalDrawTile,
 *            CharacterSelectScreenDraw, ExplodDraw, VersusScreen,
 *            W_RotateSprite8to16_P, W_RotateSpriteMirH8to16_P,
 *            W_ScaleSpriteMirHV_S, W_ScaleSpriteMirH_S,
 *            W_ScaleSpriteMirV_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
uint32_t
W_ScaleSprite_S(int *sprites,int index,float x,float y,float arg5,float arg6)

{
  int *sprite;
  int sprite2;
  uint16_t u4;
  uint16_t stale_var;
  uint16_t stale_var_00;
  uint32_t u3;
  uint16_t stale_var_01;
  uint32_t stale_EAX;
  float stk_2c;
  float stk_28;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  stk_28 = (float)*sprite * arg5;
  sprite2 = SpriteArrayAccess(sprites,index);
  stk_2c = (float80)*(int *)(sprite2 + 4) * arg6;
  u4 = (uint16_t)((uint32_t)sprite2 >> 0x10);
  if (0.0 < arg6) {
    if (0.0 < arg5) {
      W_ScaleSprite(sprites,index,x,y,stk_28,stk_2c);
      u4 = stale_var;
    }
    if (arg5 < 0.0) {
      W_ScaleSpriteMirH(sprites,index,x,y,-stk_28,stk_2c);
      u4 = stale_var_00;
    }
  }
  u3 = CONCAT22(u4,(uint16_t)(arg6 < 0.0) << 8 | (uint16_t)IS_NAN(arg6) << 10 |
                         (uint16_t)(arg6 == 0.0) << 0xe);
  if (arg6 < 0.0) {
    if (0.0 < arg5) {
      W_ScaleSpriteMirV(sprites,index,x,y,stk_28,-stk_2c);
      u4 = stale_var_01;
    }
    u3 = CONCAT22(u4,(uint16_t)(arg5 < 0.0) << 8 | (uint16_t)IS_NAN(arg5) << 10 |
                           (uint16_t)(arg5 == 0.0) << 0xe);
    if (arg5 < 0.0) {
      stk_2c = -stk_2c;
      stk_28 = -stk_28;
      W_ScaleSpriteMirHV(sprites,index,x,y,stk_28,stk_2c);
      return stale_EAX;
    }
  }
  return u3;
}

/* W_ScaleSpriteFlat_S @ 0x08059800, 168 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, opaque (colour 0 is drawn too). Clipped to the window set by
 * W_Define. Takes float scale factors: a negative x or y scale selects the
 * mirrored variant, so this is the entry point used by animations and
 * backgrounds.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteFlat
 * Called by: BGDraw, BGNormalDrawTile
 *
 * Elecbyte file: src/lib/spr-lib.c
 * Note: 2 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
void W_ScaleSpriteFlat_S(int *sprites,int index,int x,int y,float arg5,
                        float arg6)

{
  int i1;
  int *sprite;
  int sprite2;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  i1 = *sprite;
  sprite2 = SpriteArrayAccess(sprites,index);
  if ((0.0 < arg6) && (0.0 < arg5)) {
    W_ScaleSpriteFlat(sprites,index,(float)x,(float)y,(float80)i1 * arg5,
                      (float80)*(int *)(sprite2 + 4) * arg6);
    return;
  }
  return;
}

/* W_ScaleSpriteMirH_S @ 0x080598b0, 50 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, with colour 0 transparent, mirrored horizontally. Clipped to the
 * window set by W_Define. Wrapper: calls W_ScaleSprite_S with the scale of
 * the mirrored axis negated.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *   arg5         float
 *   arg6         float
 *
 * Calls: W_ScaleSprite_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleSpriteMirH_S(int *sprites,int index,int x,int y,float arg5,
                        float arg6)

{
  W_ScaleSprite_S(sprites,index,(float)x,(float)y,-arg5,arg6);
  return;
}

/* W_ScaleSpriteMirV_S @ 0x080598f0, 42 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, with colour 0 transparent, mirrored vertically. Clipped to the
 * window set by W_Define. Wrapper: calls W_ScaleSprite_S with the scale of
 * the mirrored axis negated.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *   arg5         float
 *   arg6         float
 *
 * Calls: W_ScaleSprite_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleSpriteMirV_S(int *sprites,int index,int x,int y,float arg5,
                        float arg6)

{
  arg6 = -arg6;
  W_ScaleSprite_S(sprites,index,(float)x,(float)y,arg5,arg6);
  return;
}

/* W_ScaleSpriteMirHV_S @ 0x08059920, 55 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, with colour 0 transparent, mirrored horizontally and vertically.
 * Clipped to the window set by W_Define. Wrapper: calls W_ScaleSprite_S with
 * the scale of the mirrored axis negated.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *   arg5         float
 *   arg6         float
 *
 * Calls: W_ScaleSprite_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleSpriteMirHV_S
               (int *sprites,int index,int x,int y,float arg5,float arg6)

{
  arg6 = -arg6;
  W_ScaleSprite_S(sprites,index,(float)x,(float)y,-arg5,arg6);
  return;
}

/* W_RotateSprite @ 0x08059960, 57 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, with colour 0 transparent. Clipped to the window
 * set by W_Define. Wrapper: calls W_RotateSprite_P (the pivot form).
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *
 * Calls: W_RotateSprite_P
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_RotateSprite(int *sprites,int index,float x,float y,float arg5,float arg6
                   ,float arg7)

{
  W_RotateSprite_P(sprites,index,x,y,arg5,arg6,arg7,1.0,1.0);
  return;
}

/* W_RotateSpriteMirH @ 0x080599a0, 57 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, with colour 0 transparent, mirrored horizontally.
 * Clipped to the window set by W_Define. Wrapper: calls W_RotateSpriteMirH_P
 * (the pivot form).
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *
 * Calls: W_RotateSpriteMirH_P
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_RotateSpriteMirH(int *sprites,int index,float x,float y,float arg5,
                       float arg6,float arg7)

{
  W_RotateSpriteMirH_P(sprites,index,x,y,arg5,arg6,arg7,1.0,1.0);
  return;
}

/* W_RotateSprite_P @ 0x080599e0, 541 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, with colour 0 transparent. Clipped to the window
 * set by W_Define. Takes an angle in degrees and scale factors around a
 * pivot; negative scales are turned into an angle change and a mirror flag.
 * Then calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         float
 *   arg9         float
 *
 * Calls: SpriteArrayAccess, W_RotateSpriteMirH8to16_P,
 *        W_RotateSprite8to16_P
 * Called by: AnimRotateSpr, W_RotateSprite, W_RotateSpriteMirH_P
 *
 * Elecbyte file: src/lib/spr-lib.c
 * Note: untyped (undefined4) <-> float moves kept as bit copies: 0 assignments,
 *       0 calls, 2 returns
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t
W_RotateSprite_P(int *sprites,int index,float x,float y,float arg5,float arg6,
                float arg7,float arg8,float arg9)

{
  bool b1;
  float80 f2;
  int sprite;
  uint32_t u4;
  
  b1 = arg6 < 0.0;
  if (b1) {
    arg6 = arg6 * -1.0;
    arg5 = 360.0 - arg5;
  }
  if (arg7 < 0.0) {
    f2 = arg5 + 180.0;
    b1 = !b1;
    arg7 = arg7 * -1.0;
    if (360.0 <= f2) {
      f2 = f2 - 360.0;
    }
    arg5 = 360.0 - f2;
  }
  if (arg8 < 0.0) {
    arg8 = arg8 * -1.0;
    b1 = !b1;
  }
  if (arg9 < 0.0) {
    arg5 = arg5 + 180.0;
    b1 = !b1;
    arg9 = arg9 * -1.0;
    if (360.0 <= arg5) {
      arg5 = arg5 - 360.0;
    }
  }
  sprite = V_ColDepth;
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (sprite = SpriteArrayAccess(sprites,index), *(int *)(sprite + 0x10) == 8)
      ))) {
    if (b1) {
      u4 = W_RotateSpriteMirH8to16_P
                        (sprites,index,x,y,arg5,arg6,arg7,arg8,arg9);
      return BITS_I2F(u4);
    }
    u4 = W_RotateSprite8to16_P
                      (sprites,index,x,y,arg5,arg6,arg7,arg8,arg9);
    return BITS_I2F(u4);
  }
  return sprite;
}

/* W_RotateSpriteMirH_P @ 0x08059c00, 41 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, with colour 0 transparent, mirrored horizontally.
 * Clipped to the window set by W_Define. Wrapper: calls W_RotateSprite_P
 * with the scale of the mirrored axis negated.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         float
 *   arg9         float
 *
 * Calls: W_RotateSprite_P
 * Called by: W_RotateSpriteMirH
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_RotateSpriteMirH_P
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               float arg7,float arg8,float arg9)

{
  W_RotateSprite_P(sprites,index,x,y,360.0 - arg5,-arg6,arg7,arg8,arg9)
  ;
  return;
}

/* W_PutSpriteTransAdd @ 0x08059c30, 104 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended additively (colour 0 transparent). Clipped to the window set by
 * W_Define. Dispatcher: when the screen is 15/16-bit and the sprite is 8-bit
 * it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteTransAdd8to16
 * Called by: AnimDrawSprFlip, W_PutSpriteTransAddFlip
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t W_PutSpriteTransAdd(int *sprites,int index,int x,int y)

{
  int sprite;
  uint32_t stale_EAX;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_PutSpriteTransAdd8to16(sprites,index,x,y);
    return stale_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransAddMirH @ 0x08059ca0, 104 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended additively (colour 0 transparent), mirrored horizontally. Clipped
 * to the window set by W_Define. Dispatcher: when the screen is 15/16-bit
 * and the sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteTransAddMirH8to16
 * Called by: AnimDrawSprFlip, W_PutSpriteTransAddFlip
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t W_PutSpriteTransAddMirH(int *sprites,int index,int x,int y)

{
  int sprite;
  uint32_t stale_EAX;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_PutSpriteTransAddMirH8to16(sprites,index,x,y);
    return stale_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransAddMirV @ 0x08059d10, 104 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended additively (colour 0 transparent), mirrored vertically. Clipped to
 * the window set by W_Define. Dispatcher: when the screen is 15/16-bit and
 * the sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteTransAddMirV8to16
 * Called by: AnimDrawSprFlip, W_PutSpriteTransAddFlip
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t W_PutSpriteTransAddMirV(int *sprites,int index,int x,int y)

{
  int sprite;
  uint32_t stale_EAX;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_PutSpriteTransAddMirV8to16(sprites,index,x,y);
    return stale_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransAddMirHV @ 0x08059d80, 104 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended additively (colour 0 transparent), mirrored horizontally and
 * vertically. Clipped to the window set by W_Define. Dispatcher: when the
 * screen is 15/16-bit and the sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteTransAddMirHV8to16
 * Called by: AnimDrawSprFlip, W_PutSpriteTransAddFlip
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t W_PutSpriteTransAddMirHV(int *sprites,int index,int x,int y)

{
  int sprite;
  uint32_t stale_EAX;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_PutSpriteTransAddMirHV8to16(sprites,index,x,y);
    return stale_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransAddFlip @ 0x08059df0, 156 bytes
 *
 * Draws a sprite additively with flip flags (bit 0 horizontal, bit 1
 * vertical), choosing among the four mirrored TransAdd blitters. Not called
 * in this build.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *   arg5         int
 *
 * Calls: W_PutSpriteTransAddMirH, W_PutSpriteTransAdd,
 *        W_PutSpriteTransAddMirV, W_PutSpriteTransAddMirHV
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_PutSpriteTransAddFlip(int *sprites,int index,int x,int y,int arg5)

{
  if (arg5 == 1) {
    W_PutSpriteTransAddMirH(sprites,index,x,y);
    return;
  }
  if (arg5 < 2) {
    if (arg5 == 0) {
      W_PutSpriteTransAdd(sprites,index,x,y);
      return;
    }
  }
  else {
    if (arg5 == 2) {
      W_PutSpriteTransAddMirV(sprites,index,x,y);
      return;
    }
    if (arg5 == 3) {
      W_PutSpriteTransAddMirHV(sprites,index,x,y);
      return;
    }
  }
  return;
}

/* W_PutSpriteTransAdd_B @ 0x08059e90, 136 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended additively (colour 0 transparent), with explicit source and
 * destination alpha (256 = full). Clipped to the window set by W_Define.
 * Dispatcher: when the screen is 15/16-bit and the sprite is 8-bit it calls
 * the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *   arg5         int
 *   arg6         int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteTransAdd8to16_B
 * Called by: AnimDrawSprFlip, GameLoop, W_PutSpriteTransAddFlip_B
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t
W_PutSpriteTransAdd_B(int *sprites,int index,int x,int y,int arg5,int arg6)

{
  int sprite;
  uint32_t stale_EAX;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_PutSpriteTransAdd8to16_B(sprites,index,x,y,arg5,arg6);
    return stale_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransAddMirH_B @ 0x08059f20, 136 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended additively (colour 0 transparent), mirrored horizontally, with
 * explicit source and destination alpha (256 = full). Clipped to the window
 * set by W_Define. Dispatcher: when the screen is 15/16-bit and the sprite
 * is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *   arg5         int
 *   arg6         int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteTransAddMirH8to16_B
 * Called by: AnimDrawSprFlip, W_PutSpriteTransAddFlip_B
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t
W_PutSpriteTransAddMirH_B(int *sprites,int index,int x,int y,int arg5,int arg6)

{
  int sprite;
  uint32_t stale_EAX;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_PutSpriteTransAddMirH8to16_B(sprites,index,x,y,arg5,arg6);
    return stale_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransAddMirV_B @ 0x08059fb0, 136 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended additively (colour 0 transparent), mirrored vertically, with
 * explicit source and destination alpha (256 = full). Clipped to the window
 * set by W_Define. Dispatcher: when the screen is 15/16-bit and the sprite
 * is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *   arg5         int
 *   arg6         int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteTransAddMirV8to16_B
 * Called by: AnimDrawSprFlip, W_PutSpriteTransAddFlip_B
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t
W_PutSpriteTransAddMirV_B(int *sprites,int index,int x,int y,int arg5,int arg6)

{
  int sprite;
  uint32_t stale_EAX;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_PutSpriteTransAddMirV8to16_B(sprites,index,x,y,arg5,arg6);
    return stale_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransAddMirHV_B @ 0x0805a040, 136 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended additively (colour 0 transparent), mirrored horizontally and
 * vertically, with explicit source and destination alpha (256 = full).
 * Clipped to the window set by W_Define. Dispatcher: when the screen is
 * 15/16-bit and the sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *   arg5         int
 *   arg6         int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteTransAddMirHV8to16_B
 * Called by: AnimDrawSprFlip, W_PutSpriteTransAddFlip_B
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t
W_PutSpriteTransAddMirHV_B(int *sprites,int index,int x,int y,int arg5,int arg6)

{
  int sprite;
  uint32_t stale_EAX;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_PutSpriteTransAddMirHV8to16_B(sprites,index,x,y,arg5,arg6);
    return stale_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransAddFlip_B @ 0x0805a0d0, 232 bytes
 *
 * W_PutSpriteTransAddFlip with explicit source and destination alpha. Not
 * called in this build.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *   arg5         int
 *   arg6         int
 *   arg7         int
 *
 * Calls: W_PutSpriteTransAddMirH_B, W_PutSpriteTransAdd_B,
 *        W_PutSpriteTransAddMirV_B, W_PutSpriteTransAddMirHV_B
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_PutSpriteTransAddFlip_B
               (int *sprites,int index,int x,int y,int arg5,int arg6,int arg7
               )

{
  if (arg5 == 1) {
    W_PutSpriteTransAddMirH_B(sprites,index,x,y,arg6,arg7);
    return;
  }
  if (arg5 < 2) {
    if (arg5 == 0) {
      W_PutSpriteTransAdd_B(sprites,index,x,y,arg6,arg7);
      return;
    }
  }
  else {
    if (arg5 == 2) {
      W_PutSpriteTransAddMirV_B(sprites,index,x,y,arg6,arg7);
      return;
    }
    if (arg5 == 3) {
      W_PutSpriteTransAddMirHV_B(sprites,index,x,y,arg6,arg7);
      return;
    }
  }
  return;
}

/* W_ScaleSpriteTransAdd @ 0x0805a1c0, 136 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended additively (colour 0 transparent). Clipped to the window
 * set by W_Define. Dispatcher: when the screen is 15/16-bit and the sprite
 * is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteTransAdd8to16
 * Called by: W_ScaleSpriteTransAdd_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t
W_ScaleSpriteTransAdd
          (int *sprites,int index,float x,float y,float arg5,float arg6)

{
  int sprite;
  uint32_t stale_EAX;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_ScaleSpriteTransAdd8to16(sprites,index,x,y,arg5,arg6);
    return stale_EAX;
  }
  return V_ColDepth;
}

/* W_ScaleSpriteTransAdd_S @ 0x0805a250, 328 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended additively (colour 0 transparent). Clipped to the window
 * set by W_Define. Takes float scale factors: a negative x or y scale
 * selects the mirrored variant, so this is the entry point used by
 * animations and backgrounds.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteTransAdd,
 *        W_ScaleSpriteTransAddMirH, W_ScaleSpriteTransAddMirV,
 *        W_ScaleSpriteTransAddMirHV
 * Called by: AnimScaleSpr_S, BGDraw, BGNormalDrawTile,
 *            W_RotateSpriteTransAdd8to16_P,
 *            W_RotateSpriteTransAddMirH8to16_P
 *
 * Elecbyte file: src/lib/spr-lib.c
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
uint32_t
W_ScaleSpriteTransAdd_S
          (int *sprites,int index,float x,float y,float arg5,float arg6)

{
  int *sprite;
  uint16_t u3;
  uint32_t u2;
  uint16_t stale_var;
  uint16_t stale_var_00;
  uint32_t stale_EAX;
  float stk_2c;
  float stk_28;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  stk_28 = (float)*sprite * arg5;
  stk_2c = (float80)sprite[1] * arg6;
  u3 = (uint16_t)((uint32_t)sprite >> 0x10);
  if (0.0 < arg6) {
    if (0.0 < arg5) {
      u2 = W_ScaleSpriteTransAdd(sprites,index,x,y,stk_28,stk_2c);
      u3 = (uint16_t)((uint32_t)u2 >> 0x10);
    }
    if (arg5 < 0.0) {
      W_ScaleSpriteTransAddMirH(sprites,index,x,y,-stk_28,stk_2c);
      u3 = stale_var;
    }
  }
  u2 = CONCAT22(u3,(uint16_t)(arg6 < 0.0) << 8 | (uint16_t)IS_NAN(arg6) << 10 |
                         (uint16_t)(arg6 == 0.0) << 0xe);
  if (arg6 < 0.0) {
    if (0.0 < arg5) {
      W_ScaleSpriteTransAddMirV(sprites,index,x,y,stk_28,-stk_2c);
      u3 = stale_var_00;
    }
    u2 = CONCAT22(u3,(uint16_t)(arg5 < 0.0) << 8 | (uint16_t)IS_NAN(arg5) << 10 |
                           (uint16_t)(arg5 == 0.0) << 0xe);
    if (arg5 < 0.0) {
      stk_2c = -stk_2c;
      stk_28 = -stk_28;
      W_ScaleSpriteTransAddMirHV(sprites,index,x,y,stk_28,stk_2c);
      return stale_EAX;
    }
  }
  return u2;
}

/* W_ScaleSpriteTransAddMirH @ 0x0805a3a0, 136 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended additively (colour 0 transparent), mirrored horizontally.
 * Clipped to the window set by W_Define. Dispatcher: when the screen is
 * 15/16-bit and the sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteTransAddMirH8to16
 * Called by: W_ScaleSpriteTransAdd_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleSpriteTransAddMirH
               (int *sprites,int index,float x,float y,float arg5,float arg6)

{
  int sprite;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_ScaleSpriteTransAddMirH8to16(sprites,index,x,y,arg5,arg6);
    return;
  }
  return;
}

/* W_ScaleSpriteTransAddMirV @ 0x0805a430, 136 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended additively (colour 0 transparent), mirrored vertically.
 * Clipped to the window set by W_Define. Dispatcher: when the screen is
 * 15/16-bit and the sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteTransAddMirV8to16
 * Called by: W_ScaleSpriteTransAdd_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleSpriteTransAddMirV
               (int *sprites,int index,float x,float y,float arg5,float arg6)

{
  int sprite;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_ScaleSpriteTransAddMirV8to16(sprites,index,x,y,arg5,arg6);
    return;
  }
  return;
}

/* W_ScaleSpriteTransAddMirHV @ 0x0805a4c0, 136 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended additively (colour 0 transparent), mirrored horizontally
 * and vertically. Clipped to the window set by W_Define. Dispatcher: when
 * the screen is 15/16-bit and the sprite is 8-bit it calls the 8to16 pixel
 * loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteTransAddMirHV8to16
 * Called by: W_ScaleSpriteTransAdd_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleSpriteTransAddMirHV
               (int *sprites,int index,float x,float y,float arg5,float arg6)

{
  int sprite;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_ScaleSpriteTransAddMirHV8to16(sprites,index,x,y,arg5,arg6);
    return;
  }
  return;
}

/* W_ScaleSpriteTransAdd_B @ 0x0805a550, 168 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended additively (colour 0 transparent), with explicit source
 * and destination alpha (256 = full). Clipped to the window set by W_Define.
 * Dispatcher: when the screen is 15/16-bit and the sprite is 8-bit it calls
 * the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         int
 *   arg8         int
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteTransAdd8to16_B
 * Called by: W_ScaleSpriteTransAdd_B_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleSpriteTransAdd_B
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               int arg7,int arg8)

{
  int sprite;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_ScaleSpriteTransAdd8to16_B(sprites,index,x,y,arg5,arg6,arg7,arg8);
    return;
  }
  return;
}

/* W_ScaleSpriteTransAdd_B_S @ 0x0805a600, 392 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended additively (colour 0 transparent), with explicit source
 * and destination alpha (256 = full). Clipped to the window set by W_Define.
 * Takes float scale factors: a negative x or y scale selects the mirrored
 * variant, so this is the entry point used by animations and backgrounds.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         int
 *   arg8         int
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteTransAdd_B,
 *        W_ScaleSpriteTransAddMirH_B, W_ScaleSpriteTransAddMirV_B,
 *        W_ScaleSpriteTransAddMirHV_B
 * Called by: AnimScaleSpr_S, BGDraw, BGNormalDrawTile,
 *            W_RotateSpriteTransAdd8to16_B_P,
 *            W_RotateSpriteTransAddMirH8to16_B_P
 *
 * Elecbyte file: src/lib/spr-lib.c
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
uint32_t
W_ScaleSpriteTransAdd_B_S
          (int *sprites,int index,float x,float y,float arg5,float arg6,
          int arg7,int arg8)

{
  int *sprite;
  uint16_t u3;
  uint16_t stale_var;
  uint16_t stale_var_00;
  uint32_t u2;
  uint16_t stale_var_01;
  uint32_t stale_EAX;
  float stk_34;
  float stk_30;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  stk_30 = (float)*sprite * arg5;
  stk_34 = (float80)sprite[1] * arg6;
  u3 = (uint16_t)((uint32_t)sprite >> 0x10);
  if (0.0 < arg6) {
    if (0.0 < arg5) {
      W_ScaleSpriteTransAdd_B(sprites,index,x,y,stk_30,stk_34,arg7,arg8);
      u3 = stale_var;
    }
    if (arg5 < 0.0) {
      W_ScaleSpriteTransAddMirH_B
                (sprites,index,x,y,-stk_30,stk_34,arg7,arg8);
      u3 = stale_var_00;
    }
  }
  u2 = CONCAT22(u3,(uint16_t)(arg6 < 0.0) << 8 | (uint16_t)IS_NAN(arg6) << 10 |
                         (uint16_t)(arg6 == 0.0) << 0xe);
  if (arg6 < 0.0) {
    if (0.0 < arg5) {
      W_ScaleSpriteTransAddMirV_B
                (sprites,index,x,y,stk_30,-stk_34,arg7,arg8);
      u3 = stale_var_01;
    }
    u2 = CONCAT22(u3,(uint16_t)(arg5 < 0.0) << 8 | (uint16_t)IS_NAN(arg5) << 10 |
                           (uint16_t)(arg5 == 0.0) << 0xe);
    if (arg5 < 0.0) {
      stk_34 = -stk_34;
      stk_30 = -stk_30;
      W_ScaleSpriteTransAddMirHV_B
                (sprites,index,x,y,stk_30,stk_34,arg7,arg8);
      return stale_EAX;
    }
  }
  return u2;
}

/* W_ScaleSpriteTransAddMirH_B @ 0x0805a790, 168 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended additively (colour 0 transparent), mirrored horizontally,
 * with explicit source and destination alpha (256 = full). Clipped to the
 * window set by W_Define. Dispatcher: when the screen is 15/16-bit and the
 * sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         int
 *   arg8         int
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteTransAddMirH8to16_B
 * Called by: W_ScaleSpriteTransAdd_B_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleSpriteTransAddMirH_B
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               int arg7,int arg8)

{
  int sprite;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_ScaleSpriteTransAddMirH8to16_B
              (sprites,index,x,y,arg5,arg6,arg7,arg8);
    return;
  }
  return;
}

/* W_ScaleSpriteTransAddMirV_B @ 0x0805a840, 168 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended additively (colour 0 transparent), mirrored vertically,
 * with explicit source and destination alpha (256 = full). Clipped to the
 * window set by W_Define. Dispatcher: when the screen is 15/16-bit and the
 * sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         int
 *   arg8         int
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteTransAddMirV8to16_B
 * Called by: W_ScaleSpriteTransAdd_B_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleSpriteTransAddMirV_B
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               int arg7,int arg8)

{
  int sprite;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_ScaleSpriteTransAddMirV8to16_B
              (sprites,index,x,y,arg5,arg6,arg7,arg8);
    return;
  }
  return;
}

/* W_ScaleSpriteTransAddMirHV_B @ 0x0805a8f0, 168 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended additively (colour 0 transparent), mirrored horizontally
 * and vertically, with explicit source and destination alpha (256 = full).
 * Clipped to the window set by W_Define. Dispatcher: when the screen is
 * 15/16-bit and the sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         int
 *   arg8         int
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteTransAddMirHV8to16_B
 * Called by: W_ScaleSpriteTransAdd_B_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleSpriteTransAddMirHV_B
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               int arg7,int arg8)

{
  int sprite;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_ScaleSpriteTransAddMirHV8to16_B
              (sprites,index,x,y,arg5,arg6,arg7,arg8);
    return;
  }
  return;
}

/* W_RotateSpriteTransAdd @ 0x0805a9a0, 57 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, blended additively (colour 0 transparent). Clipped
 * to the window set by W_Define. Wrapper: calls W_RotateSpriteTransAdd_P
 * (the pivot form).
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *
 * Calls: W_RotateSpriteTransAdd_P
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_RotateSpriteTransAdd
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               float arg7)

{
  W_RotateSpriteTransAdd_P(sprites,index,x,y,arg5,arg6,arg7,1.0,1.0);
  return;
}

/* W_RotateSpriteTransAddMirH @ 0x0805a9e0, 57 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, blended additively (colour 0 transparent),
 * mirrored horizontally. Clipped to the window set by W_Define. Wrapper:
 * calls W_RotateSpriteTransAddMirH_P (the pivot form).
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *
 * Calls: W_RotateSpriteTransAddMirH_P
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_RotateSpriteTransAddMirH
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               float arg7)

{
  W_RotateSpriteTransAddMirH_P(sprites,index,x,y,arg5,arg6,arg7,1.0,1.0);
  return;
}

/* W_RotateSpriteTransAdd_P @ 0x0805aa20, 541 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, blended additively (colour 0 transparent). Clipped
 * to the window set by W_Define. Takes an angle in degrees and scale factors
 * around a pivot; negative scales are turned into an angle change and a
 * mirror flag. Then calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         float
 *   arg9         float
 *
 * Calls: SpriteArrayAccess, W_RotateSpriteTransAddMirH8to16_P,
 *        W_RotateSpriteTransAdd8to16_P
 * Called by: AnimRotateSpr, W_RotateSpriteTransAdd,
 *            W_RotateSpriteTransAddMirH_P
 *
 * Elecbyte file: src/lib/spr-lib.c
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t W_RotateSpriteTransAdd_P
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               float arg7,float arg8,float arg9)

{
  bool b1;
  float80 f2;
  int sprite;
  uint32_t u4;
  
  b1 = arg6 < 0.0;
  if (b1) {
    arg6 = arg6 * -1.0;
    arg5 = 360.0 - arg5;
  }
  if (arg7 < 0.0) {
    f2 = arg5 + 180.0;
    b1 = !b1;
    arg7 = arg7 * -1.0;
    if (360.0 <= f2) {
      f2 = f2 - 360.0;
    }
    arg5 = 360.0 - f2;
  }
  if (arg8 < 0.0) {
    arg8 = arg8 * -1.0;
    b1 = !b1;
  }
  if (arg9 < 0.0) {
    arg5 = arg5 + 180.0;
    b1 = !b1;
    arg9 = arg9 * -1.0;
    if (360.0 <= arg5) {
      arg5 = arg5 - 360.0;
    }
  }
  sprite = V_ColDepth;
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (sprite = SpriteArrayAccess(sprites,index), *(int *)(sprite + 0x10) == 8)
      ))) {
    if (b1) {
      u4 = W_RotateSpriteTransAddMirH8to16_P
                        (sprites,index,x,y,arg5,arg6,arg7,arg8,arg9);
      return u4;
    }
    u4 = W_RotateSpriteTransAdd8to16_P
                      (sprites,index,x,y,arg5,arg6,arg7,arg8,arg9);
    return u4;
  }
  return sprite;
}

/* W_RotateSpriteTransAddMirH_P @ 0x0805ac40, 41 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, blended additively (colour 0 transparent),
 * mirrored horizontally. Clipped to the window set by W_Define. Wrapper:
 * calls W_RotateSpriteTransAdd_P with the scale of the mirrored axis
 * negated.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         float
 *   arg9         float
 *
 * Calls: W_RotateSpriteTransAdd_P
 * Called by: W_RotateSpriteTransAddMirH
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_RotateSpriteTransAddMirH_P
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               float arg7,float arg8,float arg9)

{
  W_RotateSpriteTransAdd_P
            (sprites,index,x,y,360.0 - arg5,-arg6,arg7,arg8,arg9);
  return;
}

/* W_RotateSpriteTransAdd_B @ 0x0805ac70, 67 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, blended additively (colour 0 transparent), with
 * explicit source and destination alpha (256 = full). Clipped to the window
 * set by W_Define. Wrapper: calls W_RotateSpriteTransAdd_B_P.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         int
 *   arg9         int
 *
 * Calls: W_RotateSpriteTransAdd_B_P
 * Called by: ExplodDrawShadow, PlayerDrawShadow, ProjDrawShadow
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_RotateSpriteTransAdd_B
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               float arg7,int arg8,int arg9)

{
  W_RotateSpriteTransAdd_B_P
            (sprites,index,x,y,arg5,arg6,arg7,1.0,1.0,arg8,arg9);
  return;
}

/* W_RotateSpriteTransAddMirH_B @ 0x0805acc0, 67 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, blended additively (colour 0 transparent),
 * mirrored horizontally, with explicit source and destination alpha (256 =
 * full). Clipped to the window set by W_Define. Wrapper: calls
 * W_RotateSpriteTransAddMirH_B_P.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         int
 *   arg9         int
 *
 * Calls: W_RotateSpriteTransAddMirH_B_P
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_RotateSpriteTransAddMirH_B
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               float arg7,int arg8,int arg9)

{
  W_RotateSpriteTransAddMirH_B_P
            (sprites,index,x,y,arg5,arg6,arg7,1.0,1.0,arg8,arg9);
  return;
}

/* W_RotateSpriteTransAdd_B_P @ 0x0805ad10, 639 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, blended additively (colour 0 transparent), with
 * explicit source and destination alpha (256 = full). Clipped to the window
 * set by W_Define. Takes an angle in degrees and scale factors around a
 * pivot; negative scales are turned into an angle change and a mirror flag.
 * Then calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         float
 *   arg9         float
 *   arg10        int
 *   arg11        int
 *
 * Calls: SpriteArrayAccess, W_RotateSpriteTransAddMirH8to16_B_P,
 *        W_RotateSpriteTransAdd8to16_B_P
 * Called by: AnimRotateSpr, ExplodDrawShadow, PlayerDrawShadow,
 *            ProjDrawShadow, W_RotateSpriteTransAddMirH_B_P,
 *            W_RotateSpriteTransAdd_B
 *
 * Elecbyte file: src/lib/spr-lib.c
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t W_RotateSpriteTransAdd_B_P
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               float arg7,float arg8,float arg9,int arg10,int arg11)

{
  bool b1;
  float80 f2;
  int sprite;
  uint32_t u4;
  
  b1 = arg6 < 0.0;
  if (b1) {
    arg6 = arg6 * -1.0;
    arg5 = 360.0 - arg5;
  }
  if (arg7 < 0.0) {
    f2 = arg5 + 180.0;
    b1 = !b1;
    arg7 = arg7 * -1.0;
    if (360.0 <= f2) {
      f2 = f2 - 360.0;
    }
    arg5 = 360.0 - f2;
  }
  if (arg8 < 0.0) {
    arg8 = arg8 * -1.0;
    b1 = !b1;
  }
  if (arg9 < 0.0) {
    arg5 = arg5 + 180.0;
    b1 = !b1;
    arg9 = arg9 * -1.0;
    if (360.0 <= arg5) {
      arg5 = arg5 - 360.0;
    }
  }
  sprite = V_ColDepth;
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (sprite = SpriteArrayAccess(sprites,index), *(int *)(sprite + 0x10) == 8)
      ))) {
    if (b1) {
      u4 = W_RotateSpriteTransAddMirH8to16_B_P
                        (sprites,index,x,y,arg5,arg6,arg7,arg8,arg9,
                         arg10,arg11);
      return u4;
    }
    u4 = W_RotateSpriteTransAdd8to16_B_P
                      (sprites,index,x,y,arg5,arg6,arg7,arg8,arg9,
                       arg10,arg11);
    return u4;
  }
  return sprite;
}

/* W_RotateSpriteTransAddMirH_B_P @ 0x0805af90, 41 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, blended additively (colour 0 transparent),
 * mirrored horizontally, with explicit source and destination alpha (256 =
 * full). Clipped to the window set by W_Define. Wrapper: calls
 * W_RotateSpriteTransAdd_B_P with the scale of the mirrored axis negated.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         float
 *   arg9         float
 *   arg10        int
 *   arg11        int
 *
 * Calls: W_RotateSpriteTransAdd_B_P
 * Called by: W_RotateSpriteTransAddMirH_B
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_RotateSpriteTransAddMirH_B_P
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               float arg7,float arg8,float arg9,int arg10,int arg11)

{
  W_RotateSpriteTransAdd_B_P
            (sprites,index,x,y,360.0 - arg5,-arg6,arg7,arg8,arg9,
             arg10,arg11);
  return;
}

/* W_PutSpriteTransSub @ 0x0805afc0, 104 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended subtractively (colour 0 transparent). Clipped to the window set by
 * W_Define. Dispatcher: when the screen is 15/16-bit and the sprite is 8-bit
 * it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteTransSub8to16
 * Called by: AnimDrawSprFlip, BGDraw, BGNormalDrawTile
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t W_PutSpriteTransSub(int *sprites,int index,int x,int y)

{
  int sprite;
  uint32_t stale_EAX;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_PutSpriteTransSub8to16(sprites,index,x,y);
    return stale_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransSubMirH @ 0x0805b030, 104 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended subtractively (colour 0 transparent), mirrored horizontally.
 * Clipped to the window set by W_Define. Dispatcher: when the screen is
 * 15/16-bit and the sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteTransSubMirH8to16
 * Called by: AnimDrawSprFlip
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t W_PutSpriteTransSubMirH(int *sprites,int index,int x,int y)

{
  int sprite;
  uint32_t stale_EAX;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_PutSpriteTransSubMirH8to16(sprites,index,x,y);
    return stale_EAX;
  }
  return V_ColDepth;
}

/* W_PutSpriteTransSubMirV @ 0x0805b0a0, 104 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended subtractively (colour 0 transparent), mirrored vertically. Clipped
 * to the window set by W_Define. Dispatcher: when the screen is 15/16-bit
 * and the sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteTransSubMirV8to16
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_PutSpriteTransSubMirV(int *sprites,int index,int x,int y)

{
  int sprite;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_PutSpriteTransSubMirV8to16(sprites,index,x,y);
    return;
  }
  return;
}

/* W_PutSpriteTransSubMirHV @ 0x0805b110, 104 bytes
 *
 * Draws sprite `index` of a sprite array into the current drawing buffer,
 * blended subtractively (colour 0 transparent), mirrored horizontally and
 * vertically. Clipped to the window set by W_Define. Dispatcher: when the
 * screen is 15/16-bit and the sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            int
 *   y            int
 *
 * Calls: SpriteArrayAccess, W_PutSpriteTransSubMirHV8to16
 * Called by: AnimDrawSprFlip
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t W_PutSpriteTransSubMirHV(int *sprites,int index,int x,int y)

{
  int sprite;
  uint32_t stale_EAX;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_PutSpriteTransSubMirHV8to16(sprites,index,x,y);
    return stale_EAX;
  }
  return V_ColDepth;
}

/* W_ScaleSpriteTransSub @ 0x0805b180, 136 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended subtractively (colour 0 transparent). Clipped to the
 * window set by W_Define. Dispatcher: when the screen is 15/16-bit and the
 * sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteTransSub8to16
 * Called by: W_ScaleSpriteTransSub_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
uint32_t
W_ScaleSpriteTransSub
          (int *sprites,int index,float x,float y,float arg5,float arg6)

{
  int sprite;
  uint32_t stale_EAX;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_ScaleSpriteTransSub8to16(sprites,index,x,y,arg5,arg6);
    return stale_EAX;
  }
  return V_ColDepth;
}

/* W_ScaleSpriteTransSub_S @ 0x0805b210, 328 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended subtractively (colour 0 transparent). Clipped to the
 * window set by W_Define. Takes float scale factors: a negative x or y scale
 * selects the mirrored variant, so this is the entry point used by
 * animations and backgrounds.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteTransSub,
 *        W_ScaleSpriteTransSubMirH, W_ScaleSpriteTransSubMirV,
 *        W_ScaleSpriteTransSubMirHV
 * Called by: AnimScaleSpr_S, W_RotateSpriteTransSub8to16_P,
 *            W_RotateSpriteTransSubMirH8to16_P
 *
 * Elecbyte file: src/lib/spr-lib.c
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
uint32_t
W_ScaleSpriteTransSub_S
          (int *sprites,int index,float x,float y,float arg5,float arg6)

{
  int *sprite;
  uint16_t u3;
  uint32_t u2;
  uint16_t stale_var;
  uint16_t stale_var_00;
  uint32_t stale_EAX;
  float stk_2c;
  float stk_28;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  stk_28 = (float)*sprite * arg5;
  stk_2c = (float80)sprite[1] * arg6;
  u3 = (uint16_t)((uint32_t)sprite >> 0x10);
  if (0.0 < arg6) {
    if (0.0 < arg5) {
      u2 = W_ScaleSpriteTransSub(sprites,index,x,y,stk_28,stk_2c);
      u3 = (uint16_t)((uint32_t)u2 >> 0x10);
    }
    if (arg5 < 0.0) {
      W_ScaleSpriteTransSubMirH(sprites,index,x,y,-stk_28,stk_2c);
      u3 = stale_var;
    }
  }
  u2 = CONCAT22(u3,(uint16_t)(arg6 < 0.0) << 8 | (uint16_t)IS_NAN(arg6) << 10 |
                         (uint16_t)(arg6 == 0.0) << 0xe);
  if (arg6 < 0.0) {
    if (0.0 < arg5) {
      W_ScaleSpriteTransSubMirV(sprites,index,x,y,stk_28,-stk_2c);
      u3 = stale_var_00;
    }
    u2 = CONCAT22(u3,(uint16_t)(arg5 < 0.0) << 8 | (uint16_t)IS_NAN(arg5) << 10 |
                           (uint16_t)(arg5 == 0.0) << 0xe);
    if (arg5 < 0.0) {
      stk_2c = -stk_2c;
      stk_28 = -stk_28;
      W_ScaleSpriteTransSubMirHV(sprites,index,x,y,stk_28,stk_2c);
      return stale_EAX;
    }
  }
  return u2;
}

/* W_ScaleSpriteTransSubMirH @ 0x0805b360, 136 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended subtractively (colour 0 transparent), mirrored
 * horizontally. Clipped to the window set by W_Define. Dispatcher: when the
 * screen is 15/16-bit and the sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteTransSubMirH8to16
 * Called by: W_ScaleSpriteTransSub_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleSpriteTransSubMirH
               (int *sprites,int index,float x,float y,float arg5,float arg6)

{
  int sprite;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_ScaleSpriteTransSubMirH8to16(sprites,index,x,y,arg5,arg6);
    return;
  }
  return;
}

/* W_ScaleSpriteTransSubMirV @ 0x0805b3f0, 136 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended subtractively (colour 0 transparent), mirrored vertically.
 * Clipped to the window set by W_Define. Dispatcher: when the screen is
 * 15/16-bit and the sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteTransSubMirV8to16
 * Called by: W_ScaleSpriteTransSub_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleSpriteTransSubMirV
               (int *sprites,int index,float x,float y,float arg5,float arg6)

{
  int sprite;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_ScaleSpriteTransSubMirV8to16(sprites,index,x,y,arg5,arg6);
    return;
  }
  return;
}

/* W_ScaleSpriteTransSubMirHV @ 0x0805b480, 136 bytes
 *
 * Draws sprite `index` of a sprite array, scaled, into the current drawing
 * buffer, blended subtractively (colour 0 transparent), mirrored
 * horizontally and vertically. Clipped to the window set by W_Define.
 * Dispatcher: when the screen is 15/16-bit and the sprite is 8-bit it calls
 * the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *
 * Calls: SpriteArrayAccess, W_ScaleSpriteTransSubMirHV8to16
 * Called by: W_ScaleSpriteTransSub_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleSpriteTransSubMirHV
               (int *sprites,int index,float x,float y,float arg5,float arg6)

{
  int sprite;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_ScaleSpriteTransSubMirHV8to16(sprites,index,x,y,arg5,arg6);
    return;
  }
  return;
}

/* W_RotateSpriteTransSub @ 0x0805b510, 57 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, blended subtractively (colour 0 transparent).
 * Clipped to the window set by W_Define. Wrapper: calls
 * W_RotateSpriteTransSub_P (the pivot form).
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *
 * Calls: W_RotateSpriteTransSub_P
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_RotateSpriteTransSub
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               float arg7)

{
  W_RotateSpriteTransSub_P(sprites,index,x,y,arg5,arg6,arg7,1.0,1.0);
  return;
}

/* W_RotateSpriteTransSubMirH @ 0x0805b550, 57 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, blended subtractively (colour 0 transparent),
 * mirrored horizontally. Clipped to the window set by W_Define. Wrapper:
 * calls W_RotateSpriteTransSubMirH_P (the pivot form).
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *
 * Calls: W_RotateSpriteTransSubMirH_P
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_RotateSpriteTransSubMirH
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               float arg7)

{
  W_RotateSpriteTransSubMirH_P(sprites,index,x,y,arg5,arg6,arg7,1.0,1.0);
  return;
}

/* W_RotateSpriteTransSub_P @ 0x0805b590, 541 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, blended subtractively (colour 0 transparent).
 * Clipped to the window set by W_Define. Takes an angle in degrees and scale
 * factors around a pivot; negative scales are turned into an angle change
 * and a mirror flag. Then calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         float
 *   arg9         float
 *
 * Calls: SpriteArrayAccess, W_RotateSpriteTransSubMirH8to16_P,
 *        W_RotateSpriteTransSub8to16_P
 * Called by: AnimRotateSpr, W_RotateSpriteTransSub,
 *            W_RotateSpriteTransSubMirH_P
 *
 * Elecbyte file: src/lib/spr-lib.c
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
uint32_t W_RotateSpriteTransSub_P
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               float arg7,float arg8,float arg9)

{
  bool b1;
  float80 f2;
  int sprite;
  uint32_t u4;
  
  b1 = arg6 < 0.0;
  if (b1) {
    arg6 = arg6 * -1.0;
    arg5 = 360.0 - arg5;
  }
  if (arg7 < 0.0) {
    f2 = arg5 + 180.0;
    b1 = !b1;
    arg7 = arg7 * -1.0;
    if (360.0 <= f2) {
      f2 = f2 - 360.0;
    }
    arg5 = 360.0 - f2;
  }
  if (arg8 < 0.0) {
    arg8 = arg8 * -1.0;
    b1 = !b1;
  }
  if (arg9 < 0.0) {
    arg5 = arg5 + 180.0;
    b1 = !b1;
    arg9 = arg9 * -1.0;
    if (360.0 <= arg5) {
      arg5 = arg5 - 360.0;
    }
  }
  sprite = V_ColDepth;
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (sprite = SpriteArrayAccess(sprites,index), *(int *)(sprite + 0x10) == 8)
      ))) {
    if (b1) {
      u4 = W_RotateSpriteTransSubMirH8to16_P
                        (sprites,index,x,y,arg5,arg6,arg7,arg8,arg9);
      return u4;
    }
    u4 = W_RotateSpriteTransSub8to16_P
                      (sprites,index,x,y,arg5,arg6,arg7,arg8,arg9);
    return u4;
  }
  return sprite;
}

/* W_RotateSpriteTransSubMirH_P @ 0x0805b7b0, 41 bytes
 *
 * Draws sprite `index` of a sprite array, rotated and scaled, into the
 * current drawing buffer, blended subtractively (colour 0 transparent),
 * mirrored horizontally. Clipped to the window set by W_Define. Wrapper:
 * calls W_RotateSpriteTransSub_P with the scale of the mirrored axis
 * negated.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         float
 *   arg9         float
 *
 * Calls: W_RotateSpriteTransSub_P
 * Called by: W_RotateSpriteTransSubMirH
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_RotateSpriteTransSubMirH_P
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               float arg7,float arg8,float arg9)

{
  W_RotateSpriteTransSub_P
            (sprites,index,x,y,360.0 - arg5,-arg6,arg7,arg8,arg9);
  return;
}

/* W_ScaleShadowTransSub @ 0x0805b7e0, 152 bytes
 *
 * Draws the shape of sprite `index` (a shadow) of a sprite array, scaled,
 * into the current drawing buffer, in a solid colour subtracted from the
 * screen. Clipped to the window set by W_Define. Dispatcher: when the screen
 * is 15/16-bit and the sprite is 8-bit it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         uint32_t
 *
 * Calls: SpriteArrayAccess, W_ScaleShadowTransSub8to16
 * Called by: W_ScaleShadowTransSub_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleShadowTransSub
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               uint32_t arg7)

{
  int sprite;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_ScaleShadowTransSub8to16(sprites,index,x,y,arg5,arg6,arg7);
    return;
  }
  return;
}

/* W_ScaleShadowTransSub_S @ 0x0805b880, 360 bytes
 *
 * Draws the shape of sprite `index` (a shadow) of a sprite array, scaled,
 * into the current drawing buffer, in a solid colour subtracted from the
 * screen. Clipped to the window set by W_Define. Takes float scale factors:
 * a negative x or y scale selects the mirrored variant, so this is the entry
 * point used by animations and backgrounds.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         uint32_t
 *
 * Calls: SpriteArrayAccess, W_ScaleShadowTransSub,
 *        W_ScaleShadowTransSubMirH, W_ScaleShadowTransSubMirV,
 *        W_ScaleShadowTransSubMirHV
 * Called by: W_RotateShadowTransSub8to16_P,
 *            W_RotateShadowTransSubMirH8to16_P
 *
 * Elecbyte file: src/lib/spr-lib.c
 * Note: 1 int-to-float conversions keep full precision (long double), as the x87
 *       fild instruction did.
 */
uint32_t
W_ScaleShadowTransSub_S
          (int *sprites,int index,float x,float y,float arg5,float arg6,
          uint32_t arg7)

{
  int *sprite;
  uint16_t u3;
  uint16_t stale_var;
  uint16_t stale_var_00;
  uint32_t u2;
  uint16_t stale_var_01;
  uint32_t stale_EAX;
  float stk_30;
  float stk_2c;
  
  sprite = (int *)SpriteArrayAccess(sprites,index);
  stk_2c = (float)*sprite * arg5;
  stk_30 = (float80)sprite[1] * arg6;
  u3 = (uint16_t)((uint32_t)sprite >> 0x10);
  if (0.0 < arg6) {
    if (0.0 < arg5) {
      W_ScaleShadowTransSub(sprites,index,x,y,stk_2c,stk_30,arg7);
      u3 = stale_var;
    }
    if (arg5 < 0.0) {
      W_ScaleShadowTransSubMirH(sprites,index,x,y,-stk_2c,stk_30,arg7);
      u3 = stale_var_00;
    }
  }
  u2 = CONCAT22(u3,(uint16_t)(arg6 < 0.0) << 8 | (uint16_t)IS_NAN(arg6) << 10 |
                         (uint16_t)(arg6 == 0.0) << 0xe);
  if (arg6 < 0.0) {
    if (0.0 < arg5) {
      W_ScaleShadowTransSubMirV(sprites,index,x,y,stk_2c,-stk_30,arg7);
      u3 = stale_var_01;
    }
    u2 = CONCAT22(u3,(uint16_t)(arg5 < 0.0) << 8 | (uint16_t)IS_NAN(arg5) << 10 |
                           (uint16_t)(arg5 == 0.0) << 0xe);
    if (arg5 < 0.0) {
      stk_30 = -stk_30;
      stk_2c = -stk_2c;
      W_ScaleShadowTransSubMirHV(sprites,index,x,y,stk_2c,stk_30,arg7);
      return stale_EAX;
    }
  }
  return u2;
}

/* W_ScaleShadowTransSubMirH @ 0x0805b9f0, 152 bytes
 *
 * Draws the shape of sprite `index` (a shadow) of a sprite array, scaled,
 * into the current drawing buffer, in a solid colour subtracted from the
 * screen, mirrored horizontally. Clipped to the window set by W_Define.
 * Dispatcher: when the screen is 15/16-bit and the sprite is 8-bit it calls
 * the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         uint32_t
 *
 * Calls: SpriteArrayAccess, W_ScaleShadowTransSubMirH8to16
 * Called by: W_ScaleShadowTransSub_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleShadowTransSubMirH
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               uint32_t arg7)

{
  int sprite;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_ScaleShadowTransSubMirH8to16(sprites,index,x,y,arg5,arg6,arg7);
    return;
  }
  return;
}

/* W_ScaleShadowTransSubMirV @ 0x0805ba90, 152 bytes
 *
 * Draws the shape of sprite `index` (a shadow) of a sprite array, scaled,
 * into the current drawing buffer, in a solid colour subtracted from the
 * screen, mirrored vertically. Clipped to the window set by W_Define.
 * Dispatcher: when the screen is 15/16-bit and the sprite is 8-bit it calls
 * the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         uint32_t
 *
 * Calls: SpriteArrayAccess, W_ScaleShadowTransSubMirV8to16
 * Called by: W_ScaleShadowTransSub_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleShadowTransSubMirV
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               uint32_t arg7)

{
  int sprite;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_ScaleShadowTransSubMirV8to16(sprites,index,x,y,arg5,arg6,arg7);
    return;
  }
  return;
}

/* W_ScaleShadowTransSubMirHV @ 0x0805bb30, 152 bytes
 *
 * Draws the shape of sprite `index` (a shadow) of a sprite array, scaled,
 * into the current drawing buffer, in a solid colour subtracted from the
 * screen, mirrored horizontally and vertically. Clipped to the window set by
 * W_Define. Dispatcher: when the screen is 15/16-bit and the sprite is 8-bit
 * it calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         uint32_t
 *
 * Calls: SpriteArrayAccess, W_ScaleShadowTransSubMirHV8to16
 * Called by: W_ScaleShadowTransSub_S
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_ScaleShadowTransSubMirHV
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               uint32_t arg7)

{
  int sprite;
  
  sprite = SpriteArrayAccess(sprites,index);
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (*(int *)(sprite + 0x10) == 8)))) {
    W_ScaleShadowTransSubMirHV8to16(sprites,index,x,y,arg5,arg6,arg7);
    return;
  }
  return;
}

/* W_RotateShadowTransSub @ 0x0805bbd0, 62 bytes
 *
 * Draws the shape of sprite `index` (a shadow) of a sprite array, rotated
 * and scaled, into the current drawing buffer, in a solid colour subtracted
 * from the screen. Clipped to the window set by W_Define. Wrapper: calls
 * W_RotateShadowTransSub_P (the pivot form).
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         uint32_t
 *
 * Calls: W_RotateShadowTransSub_P
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_RotateShadowTransSub
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               float arg7,uint32_t arg8)

{
  W_RotateShadowTransSub_P(sprites,index,x,y,arg5,arg6,arg7,1.0,1.0,arg8);
  return;
}

/* W_RotateShadowTransSubMirH @ 0x0805bc10, 62 bytes
 *
 * Draws the shape of sprite `index` (a shadow) of a sprite array, rotated
 * and scaled, into the current drawing buffer, in a solid colour subtracted
 * from the screen, mirrored horizontally. Clipped to the window set by
 * W_Define. Wrapper: calls W_RotateShadowTransSubMirH_P (the pivot form).
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         uint32_t
 *
 * Calls: W_RotateShadowTransSubMirH_P
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_RotateShadowTransSubMirH
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               float arg7,uint32_t arg8)

{
  W_RotateShadowTransSubMirH_P
            (sprites,index,x,y,arg5,arg6,arg7,1.0,1.0,arg8);
  return;
}

/* W_RotateShadowTransSub_P @ 0x0805bc50, 601 bytes
 *
 * Draws the shape of sprite `index` (a shadow) of a sprite array, rotated
 * and scaled, into the current drawing buffer, in a solid colour subtracted
 * from the screen. Clipped to the window set by W_Define. Takes an angle in
 * degrees and scale factors around a pivot; negative scales are turned into
 * an angle change and a mirror flag. Then calls the 8to16 pixel loop.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         float
 *   arg9         float
 *   arg10        uint32_t
 *
 * Calls: SpriteArrayAccess, W_RotateShadowTransSubMirH8to16_P,
 *        W_RotateShadowTransSub8to16_P
 * Called by: ExplodDrawShadow, PlayerDrawShadow, ProjDrawShadow,
 *            W_RotateShadowTransSub, W_RotateShadowTransSubMirH_P
 *
 * Elecbyte file: src/lib/spr-lib.c
 * Note: 1 temporaries are float80, as the original kept them in x87 registers.
 */
int W_RotateShadowTransSub_P
              (int *sprites,int index,float x,float y,float arg5,float arg6,
              float arg7,float arg8,float arg9,uint32_t arg10)

{
  bool b1;
  float80 f2;
  int sprite;
  
  b1 = arg6 < 0.0;
  if (b1) {
    arg6 = arg6 * -1.0;
    arg5 = 360.0 - arg5;
  }
  if (arg7 < 0.0) {
    f2 = arg5 + 180.0;
    b1 = !b1;
    arg7 = arg7 * -1.0;
    if (360.0 <= f2) {
      f2 = f2 - 360.0;
    }
    arg5 = 360.0 - f2;
  }
  if (arg8 < 0.0) {
    arg8 = arg8 * -1.0;
    b1 = !b1;
  }
  if (arg9 < 0.0) {
    arg5 = arg5 + 180.0;
    b1 = !b1;
    arg9 = arg9 * -1.0;
    if (360.0 <= arg5) {
      arg5 = arg5 - 360.0;
    }
  }
  sprite = V_ColDepth;
  if ((((V_ColDepth != 8) && (7 < V_ColDepth)) && (V_ColDepth < 0x11)) &&
     ((0xe < V_ColDepth && (sprite = SpriteArrayAccess(sprites,index), *(int *)(sprite + 0x10) == 8)
      ))) {
    if (b1) {
      sprite = W_RotateShadowTransSubMirH8to16_P
                        (sprites,index,x,y,arg5,arg6,arg7,arg8,arg9,
                         arg10);
      return sprite;
    }
    sprite = W_RotateShadowTransSub8to16_P
                      (sprites,index,x,y,arg5,arg6,arg7,arg8,arg9,
                       arg10);
    return sprite;
  }
  return sprite;
}

/* W_RotateShadowTransSubMirH_P @ 0x0805beb0, 41 bytes
 *
 * Draws the shape of sprite `index` (a shadow) of a sprite array, rotated
 * and scaled, into the current drawing buffer, in a solid colour subtracted
 * from the screen, mirrored horizontally. Clipped to the window set by
 * W_Define. Wrapper: calls W_RotateShadowTransSub_P with the scale of the
 * mirrored axis negated.
 *
 * Parameters:
 *   sprites      int *
 *   index        int
 *   x            float
 *   y            float
 *   arg5         float
 *   arg6         float
 *   arg7         float
 *   arg8         float
 *   arg9         float
 *   arg10        uint32_t
 *
 * Calls: W_RotateShadowTransSub_P
 * Called by: W_RotateShadowTransSubMirH
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
void W_RotateShadowTransSubMirH_P
               (int *sprites,int index,float x,float y,float arg5,float arg6,
               float arg7,float arg8,float arg9,uint32_t arg10)

{
  W_RotateShadowTransSub_P
            (sprites,index,x,y,360.0 - arg5,-arg6,arg7,arg8,arg9,
             arg10);
  return;
}

/* HFlipToSgn @ 0x0805bee0, 18 bytes
 *
 * Returns -1 when the horizontal flip bit (bit 0) is set, otherwise 1. Used
 * to mirror x offsets.
 *
 * Parameters:
 *   arg1         uint32_t
 *
 * Called by: AftImgUpdate, AnimDrawFlip, AnimDrawRotateFlip,
 *            AnimDrawScaleFlip, PRSprDraw
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
int HFlipToSgn(uint32_t arg1)

{
  return (uint32_t)((arg1 & 1) == 0) * 2 + -1;
}

/* VFlipToSgn @ 0x0805bf00, 18 bytes
 *
 * Returns -1 when the vertical flip bit (bit 1) is set, otherwise 1.
 *
 * Parameters:
 *   arg1         uint32_t
 *
 * Called by: AnimDrawFlip, AnimDrawRotateFlip, AnimDrawScaleFlip,
 *            PRSprDraw
 *
 * Elecbyte file: src/lib/spr-lib.c
 */
int VFlipToSgn(uint32_t arg1)

{
  return (uint32_t)((arg1 & 2) == 0) * 2 + -1;
}

