/*
 * array.c -- keyed arrays
 * The engine's general container: a fixed-element-size array with a slot
 * index, keyed by two numbers (group, item), with first/last used tracking
 * and one scan cursor. Sprites, animations, sounds, projectiles, explods and
 * AI data live in these.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/lib/array.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* ArrayNew @ 0x0804a930, 139 bytes
 *
 * Creates a keyed array: a 0x2c-byte header, a data block with room for
 * `capacity` elements of `elem_size` bytes, and an index of capacity+1
 * entries of 16 bytes. Each index entry holds {used flag, serial number,
 * group number, item number}. The first and last used slots start at 0.
 * Returns the header, or NULL if any allocation fails (the partial array is
 * freed).
 *
 * The engine keeps most of its collections in these arrays: sprites,
 * animations, sounds, explods, projectiles, AI states and so on.
 *
 * Parameters:
 *   capacity     size_t
 *   elem_size    size_t
 *   flags        uint32_t
 *
 * Calls: ArrayFree
 * C library: calloc
 * Called by: AIStateSetInit, AIStateSetMerge, AnimPerArrayNew,
 *            AnimRCReadFileTP, BGArrayNew, GameAftImgArrayNew,
 *            PRSprArrayNew, PlayerNew, ProjArrayNew, SCtrlParseElem,
 *            SCtrlParseState, SctrlReadFileTP, SiSceneReadTP, SndArrayNew,
 *            SpriteArrayAddPal, SpriteArrayAddSprite, ... (17 callers)
 *
 * Elecbyte file: src/lib/array.c
 */
uint32_t * ArrayNew(size_t capacity,size_t elem_size,uint32_t flags)

{
  uint32_t *array;
  void *pv2;
  
  array = calloc(1,0x2c);
  if (array != (uint32_t *)0x0) {
    *array = flags;
    array[1] = elem_size;
    array[3] = capacity;
    array[2] = 0;
    array[4] = 0;
    pv2 = calloc(capacity,elem_size);
    array[5] = pv2;
    if (pv2 != (void *)0x0) {
      pv2 = calloc(capacity + 1,0x10);
      array[6] = pv2;
      if (pv2 != (void *)0x0) {
        array[10] = 0;
        array[9] = 0;
        return array;
      }
    }
    ArrayFree(array);
  }
  return (uint32_t *)0x0;
}

/* ArrayCopy @ 0x0804a9c0, 183 bytes
 *
 * Allocates a new array with the same capacity, element size and flags as
 * `array`, then copies its header, data block and index into it. Returns the
 * copy, or NULL on failure.
 *
 * Parameters:
 *   array        uint32_t *
 *
 * Calls: ArrayFree
 * C library: calloc, memcpy
 * Called by: SpriteArrayNewInstance
 *
 * Elecbyte file: src/lib/array.c
 */
uint32_t * ArrayCopy(uint32_t *array)

{
  size_t size;
  size_t nmemb;
  uint32_t *array2;
  void *pv2;
  int i3;
  uint32_t *pu4;
  uint32_t *pu5;
  
  array2 = calloc(1,0x2c);
  if (array2 != (uint32_t *)0x0) {
    pu4 = array;
    pu5 = array2;
    for (i3 = 0xb; i3 != 0; i3 = i3 + -1) {
      *pu5 = *pu4;
      pu4 = pu4 + 1;
      pu5 = pu5 + 1;
    }
    size = array[1];
    nmemb = array[3];
    array2[6] = 0;
    array2[5] = 0;
    pv2 = calloc(nmemb,size);
    array2[5] = pv2;
    if (pv2 != (void *)0x0) {
      pv2 = calloc(array[3] + 1,0x10);
      array2[6] = pv2;
      if (pv2 != (void *)0x0) {
        memcpy((void *)array2[5],(void *)array[5],array[1] * array[3]);
        pu4 = (uint32_t *)array[6];
        pu5 = (uint32_t *)array2[6];
        for (i3 = (array[3] & 0xfffffff) << 2; i3 != 0; i3 = i3 + -1) {
          *pu5 = *pu4;
          pu4 = pu4 + 1;
          pu5 = pu5 + 1;
        }
        return array2;
      }
    }
    ArrayFree(array2);
  }
  return (uint32_t *)0x0;
}

/* ArrayCopyOnto @ 0x0804aa80, 124 bytes
 *
 * Copies the contents of the second array into `array`, growing `array`
 * first (ArrayResize) if it is smaller. The destination keeps its own data
 * and index blocks; the header fields are copied and the data and index
 * entries are memcpy'd across. Returns `array`, or NULL if the resize
 * failed.
 *
 * Parameters:
 *   array        uint32_t *
 *   arg2         uint32_t *
 *
 * Calls: ArrayResize
 * C library: memcpy
 * Called by: SpriteArrayNewInstanceOnto
 *
 * Elecbyte file: src/lib/array.c
 */
uint32_t * ArrayCopyOnto(uint32_t *array,uint32_t *arg2)

{
  uint32_t u1;
  void *dest;
  int i2;
  int i3;
  uint32_t *pu4;
  uint32_t *pu5;
  
  if (((int)array[3] < (int)arg2[3]) &&
     (i3 = ArrayResize((int)array,arg2[3]), i3 == 0)) {
    array = (uint32_t *)0x0;
  }
  else {
    u1 = array[6];
    dest = (void *)array[5];
    pu4 = arg2;
    pu5 = array;
    for (i3 = 0xb; i3 != 0; i3 = i3 + -1) {
      *pu5 = *pu4;
      pu4 = pu4 + 1;
      pu5 = pu5 + 1;
    }
    i3 = arg2[3];
    array[6] = u1;
    i2 = arg2[1];
    array[5] = dest;
    memcpy(dest,(void *)arg2[5],i2 * i3);
    pu4 = (uint32_t *)arg2[6];
    pu5 = (uint32_t *)array[6];
    for (i3 = (arg2[3] & 0xfffffff) << 2; i3 != 0; i3 = i3 + -1) {
      *pu5 = *pu4;
      pu4 = pu4 + 1;
      pu5 = pu5 + 1;
    }
  }
  return array;
}

/* ArrayFree @ 0x0804ab00, 68 bytes
 *
 * Frees the data block, the index and the header of an array. Accepts NULL.
 *
 * Parameters:
 *   array        void *
 *
 * C library: free
 * Called by: AIStateSetDeInit, AnimPerArrayFree, AnimRCFree, ArrayCopy,
 *            ArrayNew, BGArrayFree, FreeExpArray, GameAftImgArrayFree,
 *            PRSprArrayFree, PlayerFree, ProjArrayFree, SCtrlRCFree,
 *            SiSceneFree, SndArrayFree, SpriteArrayFree,
 *            SpriteArrayNewInstanceOnto
 *
 * Elecbyte file: src/lib/array.c
 */
uint32_t ArrayFree(void *array)

{
  uint32_t entry_EAX;
  uint32_t stale_EAX;
  
  if (array != (void *)0x0) {
    if (*(void **)((int)array + 0x14) != (void *)0x0) {
      free(*(void **)((int)array + 0x14));
    }
    if (*(void **)((int)array + 0x18) != (void *)0x0) {
      free(*(void **)((int)array + 0x18));
    }
    free(array);
    return stale_EAX;
  }
  return entry_EAX;
}

/* ArrayHasSpace @ 0x0804ab50, 16 bytes
 *
 * Returns true when the array holds fewer elements than its capacity.
 *
 * Parameters:
 *   array        int
 *
 * Called by: ArrayAddResize, ArrayAddUniqueResize
 *
 * Elecbyte file: src/lib/array.c
 */
bool ArrayHasSpace(int array)

{
  return *(int *)(array + 8) < *(int *)(array + ARRAY_CAPACITY);
}

/* ArrayAdd @ 0x0804ab60, 129 bytes
 *
 * Copies `elem_size` bytes from `item` into the first free slot
 * (ArrayFindEmpty). Marks the index entry used and stamps it with the next
 * serial number and the key (grpno, itemno). Updates the element count and
 * the first/last used slot. Returns the slot index, or -1 if the array is
 * full.
 *
 * Parameters:
 *   array        int
 *   item         void *
 *   grpno        uint32_t
 *   itemno       uint32_t
 *
 * Calls: ArrayFindEmpty, ArrayAccessUnsafe
 * C library: memcpy
 * Called by: AILearnDataLoad, AIStateSetMerge, AnimPerArrayAdd,
 *            AnimRCReadFileTP, ArrayAddResize, ArrayAddUnique, BGArrayAdd,
 *            BGArrayAddAnim, GameAftImgArrayNew, PRSprAdd, Player1HitP2,
 *            Player1ReverseP2, PlayerAILearnMoveEnd, PlayerCheckProjHit,
 *            ProjArrayAdd, SCtrlParseElem, ... (20 callers)
 *
 * Elecbyte file: src/lib/array.c
 */
int ArrayAdd(int array,void *item,uint32_t grpno,uint32_t itemno)

{
  int i1;
  int index;
  void *item2;
  int i3;
  
  index = ArrayFindEmpty(array);
  if (index != -1) {
    item2 = (void *)ArrayAccessUnsafe(array,index);
    memcpy(item2,item,*(size_t *)(array + 4));
    i1 = *(int *)(array + ARRAY_INDEX);
    *(int *)(array + 8) = *(int *)(array + 8) + 1;
    i3 = index * 0x10;
    *(uint32_t *)(i1 + i3) = 1;
    *(uint32_t *)(i1 + 4 + i3) = *(uint32_t *)(array + ARRAY_NEXT_SERIAL);
    *(uint32_t *)(i1 + 8 + i3) = grpno;
    *(uint32_t *)(i1 + 0xc + i3) = itemno;
    *(int *)(array + ARRAY_NEXT_SERIAL) = *(int *)(array + ARRAY_NEXT_SERIAL) + 1;
    if (index < *(int *)(array + ARRAY_FIRST_USED)) {
      *(int *)(array + ARRAY_FIRST_USED) = index;
    }
    if (*(int *)(array + ARRAY_LAST_USED) < index) {
      *(int *)(array + ARRAY_LAST_USED) = index;
    }
  }
  return index;
}

/* ArrayAddUnique @ 0x0804abf0, 94 bytes
 *
 * Like ArrayAdd, but if an element with the same key (grpno, itemno) already
 * exists, its data is overwritten instead and its slot index is returned.
 *
 * Parameters:
 *   array        int
 *   item         void *
 *   grpno        int
 *   itemno       int
 *
 * Calls: ArrayFind, ArrayAdd, ArrayAccessUnsafe
 * C library: memcpy
 * Called by: ArrayAddUniqueResize
 *
 * Elecbyte file: src/lib/array.c
 */
uint32_t ArrayAddUnique(int array,void *item,int grpno,int itemno)

{
  uint32_t index;
  void *item2;
  
  index = ArrayFind(array,grpno,itemno);
  if (index == 0xffffffff) {
    index = ArrayAdd(array,item,grpno,itemno);
  }
  else {
    item2 = (void *)ArrayAccessUnsafe(array,index);
    memcpy(item2,item,*(size_t *)(array + 4));
  }
  return index;
}

/* ArrayAddResize @ 0x0804ac50, 95 bytes
 *
 * ArrayAdd that first grows a full array by one slot (ArrayResize to
 * capacity + 1). Returns -1 if the resize fails. Used for sprite and palette
 * lists whose size is not known in advance.
 *
 * Parameters:
 *   array        int
 *   item         void *
 *   grpno        uint32_t
 *   itemno       uint32_t
 *
 * Calls: ArrayHasSpace, ArrayResize, ArrayAdd
 * Called by: SpriteArrayAddPal, SpriteArrayAddSprite
 *
 * Elecbyte file: src/lib/array.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
int ArrayAddResize(int array,void *item,uint32_t grpno,uint32_t itemno)

{
  bool b1;
  uint32_t stale_var;
  int index;
  
  b1 = ArrayHasSpace(array);
  if (ZEXT8(b1) == 0) {
    index = ArrayResize(array,*(int *)(array + ARRAY_CAPACITY) + 1);
    if (index == 0) {
      return -1;
    }
  }
  index = ArrayAdd(array,item,grpno,itemno);
  return index;
}

/* ArrayAddUniqueResize @ 0x0804acb0, 95 bytes
 *
 * ArrayAddUnique that first grows a full array by one slot.
 *
 * Parameters:
 *   array        int
 *   item         void *
 *   grpno        int
 *   itemno       int
 *
 * Calls: ArrayHasSpace, ArrayResize, ArrayAddUnique
 *
 * Elecbyte file: src/lib/array.c
 * Note: 1 byte results widened with ZEXT8 (upper bytes are zero).
 */
uint32_t ArrayAddUniqueResize(int array,void *item,int grpno,int itemno)

{
  bool b1;
  uint32_t stale_var;
  int i2;
  uint32_t index;
  
  b1 = ArrayHasSpace(array);
  if (ZEXT8(b1) == 0) {
    i2 = ArrayResize(array,*(int *)(array + ARRAY_CAPACITY) + 1);
    if (i2 == 0) {
      return 0xffffffff;
    }
  }
  index = ArrayAddUnique(array,item,grpno,itemno);
  return index;
}

/* ArrayDelete @ 0x0804ad10, 139 bytes
 *
 * Marks slot `index` unused and decrements the element count. If the slot
 * was the first or last used one, the first/last bounds are moved inward to
 * the next used slot. When the array becomes empty, both bounds are reset to
 * 0. The element data is not cleared.
 *
 * Parameters:
 *   array        int
 *   index        int
 *
 * Called by: AnimPerArrayDelete, FontReadFilePtr_0_01,
 *            PlayerComboCountCheck, PlayerDropBoundTargets,
 *            PlayerSCtrlApplyElem, ProjArrayDelete
 *
 * Elecbyte file: src/lib/array.c
 */
void ArrayDelete(int array,int index)

{
  int i1;
  int i2;
  
  i1 = *(int *)(array + ARRAY_INDEX);
  *(uint32_t *)(i1 + index * 0x10) = 0;
  i2 = *(int *)(array + 8) + -1;
  *(int *)(array + 8) = i2;
  if (i2 == 0) {
    *(uint32_t *)(array + ARRAY_LAST_USED) = 0;
    *(uint32_t *)(array + ARRAY_FIRST_USED) = 0;
  }
  else {
    i2 = *(int *)(array + ARRAY_FIRST_USED);
    if (index == i2) {
      i1 = *(int *)(i1 + index * 0x10);
      while (i1 == 0) {
        i2 = i2 + 1;
        *(int *)(array + ARRAY_FIRST_USED) = i2;
        i1 = *(int *)(*(int *)(array + ARRAY_INDEX) + i2 * 0x10);
      }
    }
    else {
      i1 = *(int *)(array + ARRAY_LAST_USED);
      if (index == i1) {
        i2 = *(int *)(*(int *)(array + ARRAY_INDEX) + i1 * 0x10);
        while (i2 == 0) {
          i1 = i1 + -1;
          *(int *)(array + ARRAY_LAST_USED) = i1;
          i2 = *(int *)(*(int *)(array + ARRAY_INDEX) + i1 * 0x10);
        }
      }
    }
  }
  return;
}

/* ArrayClear @ 0x0804ada0, 66 bytes
 *
 * Empties the array: zeroes the whole index and resets the count, the
 * first/last used bounds and the scan cursor. The serial counter is kept.
 *
 * Parameters:
 *   array        int
 *
 * C library: memset
 * Called by: AIStateSetClear, AnimPerArrayClear, PRSprArrayClear,
 *            PlayerReset, SpriteArrayClear
 *
 * Elecbyte file: src/lib/array.c
 */
void ArrayClear(int array)

{
  memset(*(void **)(array + ARRAY_INDEX),0,*(int *)(array + ARRAY_CAPACITY) << 4);
  *(uint32_t *)(array + 8) = 0;
  *(uint32_t *)(array + ARRAY_LAST_USED) = 0;
  *(uint32_t *)(array + ARRAY_FIRST_USED) = 0;
  *(uint32_t *)(array + 0x20) = 0;
  *(uint32_t *)(array + 0x1c) = 0;
  return;
}

/* ArrayResize @ 0x0804adf0, 172 bytes
 *
 * Grows the data block and the index to hold `capacity` elements; the new
 * data and index entries are zeroed. Returns 1 on success or when the
 * capacity is unchanged. Returns 0 if realloc fails or if `capacity` is
 * smaller than the current one (arrays never shrink).
 *
 * Parameters:
 *   array        int
 *   capacity     int
 *
 * C library: realloc, memset
 * Called by: ArrayAddResize, ArrayAddUniqueResize, ArrayCopyOnto,
 *            SctrlAddFileTP
 *
 * Elecbyte file: src/lib/array.c
 */
uint32_t ArrayResize(int array,int capacity)

{
  int i1;
  void *pv2;
  uint32_t u3;
  uint32_t *pu4;
  
  i1 = *(int *)(array + ARRAY_CAPACITY);
  if (i1 <= capacity) {
    if (capacity == i1) {
      return 1;
    }
    pv2 = realloc(*(void **)(array + ARRAY_DATA),capacity * *(int *)(array + 4));
    if (pv2 != (void *)0x0) {
      *(void **)(array + ARRAY_DATA) = pv2;
      pv2 = realloc(*(void **)(array + ARRAY_INDEX),capacity * 0x10 + 0x10);
      if (pv2 != (void *)0x0) {
        *(void **)(array + ARRAY_INDEX) = pv2;
        memset((void *)(i1 * *(int *)(array + 4) + *(int *)(array + ARRAY_DATA)),0,
               (capacity - i1) * *(int *)(array + 4));
        pu4 = (uint32_t *)(i1 * 0x10 + *(int *)(array + ARRAY_INDEX));
        for (u3 = (capacity - i1) * 0x10 + 0x10U >> 2; u3 != 0; u3 = u3 - 1) {
          *pu4 = 0;
          pu4 = pu4 + 1;
        }
        *(int *)(array + ARRAY_CAPACITY) = capacity;
        return 1;
      }
    }
  }
  return 0;
}

/* ArrayFindEmpty @ 0x0804aea0, 119 bytes
 *
 * Returns the index of the first unused slot, or -1 when the array is full.
 *
 * Parameters:
 *   array        int
 *
 * Called by: ArrayAdd, ProjArrayAdd
 *
 * Elecbyte file: src/lib/array.c
 */
int ArrayFindEmpty(int array)

{
  int i1;
  int i2;
  int i3;
  
  i1 = *(int *)(array + 8);
  if (i1 < *(int *)(array + ARRAY_CAPACITY)) {
    if (i1 == 0) {
      return 0;
    }
    i2 = *(int *)(array + ARRAY_LAST_USED);
    i3 = *(int *)(array + ARRAY_FIRST_USED);
    if (i1 < (i2 - i3) + 1) {
      i3 = i3 + 1;
      i1 = *(int *)(*(int *)(array + ARRAY_INDEX) + i3 * 0x10);
      while (i1 != 0) {
        i3 = i3 + 1;
        i1 = *(int *)(*(int *)(array + ARRAY_INDEX) + i3 * 0x10);
      }
      return i3;
    }
    if (0 < i3) {
      return i3 + -1;
    }
    if (i2 < *(int *)(array + ARRAY_CAPACITY) + -1) {
      return i2 + 1;
    }
  }
  return -1;
}

/* ArrayAccessSafe @ 0x0804af20, 32 bytes
 *
 * Returns a pointer to element `index`, or NULL when `index` is negative or
 * not below the element count. Note that the check is against the count, not
 * the capacity, so it is only "safe" for densely filled arrays.
 *
 * Parameters:
 *   array        int
 *   index        int
 *
 * Elecbyte file: src/lib/array.c
 */
int ArrayAccessSafe(int array,int index)

{
  if ((-1 < index) && (index < *(int *)(array + 8))) {
    return index * *(int *)(array + 4) + *(int *)(array + ARRAY_DATA);
  }
  return 0;
}

/* ArrayFind @ 0x0804af40, 153 bytes
 *
 * Looks up the element whose key is (grpno, itemno) and returns its slot
 * index, or -1 if none exists.
 *
 * It uses a sentinel: the key is first written into the index entry just
 * after the last used slot, so the scan loop needs no bounds check. When the
 * used range is dense (last - first + 1 == count) it compares keys only.
 * Otherwise it also checks each entry's used flag.
 *
 * Parameters:
 *   array        int
 *   grpno        int
 *   itemno       int
 *
 * Called by: AIStateSetMerge, AnimGrpNoToIdx, ArrayAccessGrpItem,
 *            ArrayAddUnique, ExplodAdd, PlayerAILearnMoveEnd,
 *            SpriteArrayGetNum, SpriteArrayPalGetNum, SpriteUsePal
 *
 * Elecbyte file: src/lib/array.c
 */
uint32_t ArrayFind(int array,int grpno,int itemno)

{
  int i1;
  int i2;
  uint32_t u3;
  int i4;
  int *pi5;
  int *pi6;
  
  i1 = *(int *)(array + ARRAY_LAST_USED);
  if (*(int *)(array + 8) == 0) {
    u3 = 0xffffffff;
  }
  else {
    i2 = *(int *)(array + ARRAY_FIRST_USED);
    if ((i1 - i2) + 1 == *(int *)(array + 8)) {
      u3 = i2 - 1;
      i4 = *(int *)(array + ARRAY_INDEX);
      i2 = i4 + 0x10 + i1 * 0x10;
      *(int *)(i2 + 8) = grpno;
      *(int *)(i2 + 0xc) = itemno;
      i2 = u3 * 0x10 + i4;
      do {
        do {
          i4 = i2;
          u3 = u3 + 1;
          i2 = i4 + 0x10;
        } while (*(int *)(i4 + 0x18) != grpno);
      } while (*(int *)(i4 + 0x1c) != itemno);
    }
    else {
      u3 = i2 - 1;
      i4 = *(int *)(array + ARRAY_INDEX);
      i2 = i4 + 0x10 + i1 * 0x10;
      *(int *)(i2 + 8) = grpno;
      *(int *)(i2 + 0xc) = itemno;
      pi5 = (int *)(u3 * 0x10 + i4);
      do {
        do {
          pi6 = pi5;
          pi5 = pi6 + 4;
          u3 = u3 + 1;
        } while (pi6[6] != grpno);
      } while ((pi6[7] != itemno) || (*pi5 == 0));
    }
    u3 = u3 | ((int)u3 <= i1) - 1;
  }
  return u3;
}

/* ArrayAccessGrpItem @ 0x0804afe0, 54 bytes
 *
 * Returns a pointer to the element keyed (grpno, itemno), or NULL if none
 * exists (ArrayFind + element address).
 *
 * Parameters:
 *   array        int
 *   grpno        int
 *   itemno       int
 *
 * Calls: ArrayFind
 * Called by: BGAccess, GameAftImgArrayFree, GameAftImgCount,
 *            GameAftImgReset, PlayerAILearnMoveEnd,
 *            PlayerAILearnMoveStart, PlayerChangeState, PlayerSCtrlUpdate,
 *            PlayerSCtrlUpdateSpec, RequestNewAftImg, SCtrlTrigArrayTest,
 *            SiSceneDraw, SiSceneUpdate, SiSceneUpdatePal, SndPlay,
 *            SndPlayLoop, ... (20 callers)
 *
 * Elecbyte file: src/lib/array.c
 */
int ArrayAccessGrpItem(int array,int grpno,int itemno)

{
  uint32_t index;
  int i2;
  
  index = ArrayFind(array,grpno,itemno);
  if (index == 0xffffffff) {
    i2 = 0;
  }
  else {
    i2 = index * *(int *)(array + 4) + *(int *)(array + ARRAY_DATA);
  }
  return i2;
}

/* ArrayIdxToGrp @ 0x0804b020, 19 bytes
 *
 * Returns the group number (first key) stored in the index entry of slot
 * `index`.
 *
 * Parameters:
 *   array        int
 *   index        int
 *
 * Called by: AnimCurIDGrp, AnimIdxToIDGrp, AnimPerArrayDrawGrp,
 *            AnimPerArrayDrawScaleGrp, AnimPerArrayUpdateGrp
 *
 * Elecbyte file: src/lib/array.c
 */
uint32_t ArrayIdxToGrp(int array,int index)

{
  return *(uint32_t *)(*(int *)(array + ARRAY_INDEX) + 8 + index * 0x10);
}

/* ArrayIdxToItem @ 0x0804b040, 19 bytes
 *
 * Returns the item number (second key) stored in the index entry of slot
 * `index`.
 *
 * Parameters:
 *   array        int
 *   index        int
 *
 * Called by: AnimCurIDno, AnimIdxToIDno
 *
 * Elecbyte file: src/lib/array.c
 */
uint32_t ArrayIdxToItem(int array,int index)

{
  return *(uint32_t *)(*(int *)(array + ARRAY_INDEX) + 0xc + index * 0x10);
}

/* ArrayScanFirst @ 0x0804b060, 41 bytes
 *
 * Starts an iteration: sets the array's scan cursor to the first used slot
 * and returns a pointer to that element, or NULL if the array is empty. Use
 * ArrayScanNext to continue. Each array has only one cursor, so nested scans
 * of the same array are not possible.
 *
 * Parameters:
 *   array        int
 *
 * Called by: AIBuildCounterAttackList, AILearnDataSave, AIStateSetMerge,
 *            AnimPerArrayDraw, AnimPerArrayDrawGrp,
 *            AnimPerArrayDrawScaleGrp, AnimPerArrayUpdate,
 *            AnimPerArrayUpdateGrp, AnimRCFree, BGAccessID,
 *            BGArrayCtrlUpdate, BGArrayDraw, BGArrayDrawLayer,
 *            BGArrayFree, BGArrayMoveOffset, BGArrayReset, ... (55
 *            callers)
 *
 * Elecbyte file: src/lib/array.c
 */
int ArrayScanFirst(int array)

{
  if (*(int *)(array + 8) == 0) {
    return 0;
  }
  *(int *)(array + 0x1c) = *(int *)(array + ARRAY_FIRST_USED);
  *(uint32_t *)(array + 0x20) = 1;
  return *(int *)(array + ARRAY_FIRST_USED) * *(int *)(array + 4) + *(int *)(array + ARRAY_DATA);
}

/* ArrayScanNext @ 0x0804b090, 58 bytes
 *
 * Advances the scan cursor to the next used slot and returns a pointer to
 * its element. Returns NULL after the last used slot.
 *
 * Parameters:
 *   array        int
 *
 * Called by: AIBuildCounterAttackList, AILearnDataSave, AIStateSetMerge,
 *            AnimPerArrayDraw, AnimPerArrayDrawGrp,
 *            AnimPerArrayDrawScaleGrp, AnimPerArrayUpdate,
 *            AnimPerArrayUpdateGrp, AnimRCFree, BGAccessID,
 *            BGArrayCtrlUpdate, BGArrayDraw, BGArrayDrawLayer,
 *            BGArrayFree, BGArrayMoveOffset, BGArrayReset, ... (55
 *            callers)
 *
 * Elecbyte file: src/lib/array.c
 */
int ArrayScanNext(int array)

{
  int i1;
  
  i1 = *(int *)(array + 0x1c);
  if (i1 < *(int *)(array + ARRAY_LAST_USED)) {
    do {
      i1 = i1 + 1;
    } while (*(int *)(*(int *)(array + ARRAY_INDEX) + i1 * 0x10) == 0);
    *(int *)(array + 0x1c) = i1;
    *(int *)(array + 0x20) = *(int *)(array + 0x20) + 1;
    i1 = i1 * *(int *)(array + 4) + *(int *)(array + ARRAY_DATA);
  }
  else {
    i1 = 0;
  }
  return i1;
}

/* ArrayAccessUnsafe @ 0x0804b0d0, 20 bytes
 *
 * Returns the address of element `index` without any check (data + index *
 * elem_size).
 *
 * Parameters:
 *   array        int
 *   index        int
 *
 * Called by: ArrayAdd, ArrayAddUnique
 *
 * Elecbyte file: src/lib/array.c
 */
int ArrayAccessUnsafe(int array,int index)

{
  return *(int *)(array + 4) * index + *(int *)(array + ARRAY_DATA);
}

