/*
 * unzip.c -- minizip unzip
 * Gilles Vollant's zip reader from the zlib contrib directory, used to load
 * characters from .zip files.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* unzlocal_getByte @ 0x080802e0, 74 bytes
 *
 * Reads one byte from the archive file into *pi. Returns UNZ_OK, UNZ_EOF or
 * UNZ_ERRNO.
 *
 * Parameters:
 *   fin          _IO_FILE *
 *   pi           uint32_t *
 *
 * C library: fread, ferror
 * Called by: unzlocal_getLong, unzlocal_getShort
 *
 * Note: decompiler flag: a register value with no visible source (saved_
 *       variables)
 * Note: Written by hand from the assembly (reconstruction/overrides/).
 * Note: written by hand from the assembly at 0x080802e0-0x0808032a. Reason: the
 *       one-byte buffer lives in a prologue "push %ebx" slot (0x7(%esp) after
 *       the pushes); Ghidra rendered it as &stack0xfffffffb and read the byte
 *       back as "unaff_EBX >> 0x18". The function matches the public minizip
 *       0.15 unzlocal_getByte (Gilles Vollant, zlib licence): read one byte with
 *       fread; on success store it and return UNZ_OK (0); otherwise return
 *       UNZ_ERRNO (-1) if ferror() is set, else UNZ_EOF (0). VERIFIED: "sete
 *       %al; dec %eax" at 0x8080322 computes (ferror == 0) - 1.
 */
int unzlocal_getByte(_IO_FILE *fin, uint32_t *pi)
{
  unsigned char c;

  if (fread(&c, 1, 1, fin) == 1) {                    /* 0x80802f1 */
    *pi = (uint32_t)c;                                   /* movzbl-style: xor edx; mov dl */
    return 0;
  }
  return (ferror(fin) == 0) - 1;
}

/* unzlocal_getShort @ 0x08080330, 84 bytes
 *
 * Reads a little-endian 16-bit value from the archive file.
 *
 * Parameters:
 *   fin          _IO_FILE *
 *   pX           uint32_t *
 *
 * Calls: unzlocal_getByte
 * Called by: unzOpen, unzlocal_CheckCurrentFileCoherencyHeader,
 *            unzlocal_GetCurrentFileInfoInternal
 *
 * Note: Locals live in `frame`, laid out as on the original stack (0x10 bytes, 1
 *       variables), because their address is taken.
 */
int unzlocal_getShort(_IO_FILE *fin,uint32_t *pX)

{
  uint32_t u1;
  int i2;
  unsigned char frame[0x10] __attribute__((aligned(16)));
#define stk_10 (*(uint32_t *)(frame + 0x0))
  
  i2 = unzlocal_getByte(fin,&stk_10);
  u1 = stk_10;
  if (i2 == 0) {
    i2 = unzlocal_getByte(fin,&stk_10);
  }
  *pX = u1 + stk_10 * 0x100 & (i2 != 0) - 1;
  return i2;
}
#undef stk_10

/* unzlocal_getLong @ 0x08080390, 142 bytes
 *
 * Reads a little-endian 32-bit value from the archive file.
 *
 * Parameters:
 *   fin          _IO_FILE *
 *   pX           uint32_t *
 *
 * Calls: unzlocal_getByte
 * Called by: unzOpen, unzlocal_CheckCurrentFileCoherencyHeader,
 *            unzlocal_GetCurrentFileInfoInternal
 *
 * Note: Locals live in `frame`, laid out as on the original stack (0x10 bytes, 1
 *       variables), because their address is taken.
 */
int unzlocal_getLong(_IO_FILE *fin,uint32_t *pX)

{
  uint32_t u1;
  int i2;
  int i3;
  int i4;
  unsigned char frame[0x10] __attribute__((aligned(16)));
#define stk_10 (*(uint32_t *)(frame + 0x0))
  
  i2 = unzlocal_getByte(fin,&stk_10);
  u1 = stk_10;
  if (i2 == 0) {
    i2 = unzlocal_getByte(fin,&stk_10);
  }
  i3 = stk_10 * 0x100;
  if (i2 == 0) {
    i2 = unzlocal_getByte(fin,&stk_10);
  }
  i4 = stk_10 * 0x10000;
  if (i2 == 0) {
    i2 = unzlocal_getByte(fin,&stk_10);
  }
  *pX = u1 + i3 + i4 + stk_10 * 0x1000000 & (i2 != 0) - 1;
  return i2;
}
#undef stk_10

/* strcmpcasenosensitive_internal @ 0x08080420, 92 bytes
 *
 * Case-insensitive string comparison (ASCII letters folded); returns <0, 0
 * or >0.
 *
 * Parameters:
 *   fileName1    char *
 *   fileName2    char *
 *
 * Called by: unzStringFileNameCompare
 *
 */
int strcmpcasenosensitive_internal(char *fileName1,char *fileName2)

{
  char c1;
  char c2;
  
  while( true ) {
    c1 = *fileName1;
    fileName1 = fileName1 + 1;
    c2 = *fileName2;
    fileName2 = fileName2 + 1;
    if ((uint8_t)(c1 + 0x9fU) < 0x1a) {
      c1 = c1 + -0x20;
    }
    if ((uint8_t)(c2 + 0x9fU) < 0x1a) {
      c2 = c2 + -0x20;
    }
    if (c1 == '\0') {
      return (c2 == '\0') - 1;
    }
    if (c2 == '\0') {
      return 1;
    }
    if (c1 < c2) break;
    if (c2 < c1) {
      return 1;
    }
  }
  return -1;
}

/* unzStringFileNameCompare @ 0x08080480, 56 bytes
 *
 * Compares two file names: iCaseSensitivity 1 (or 0, the Unix default) uses
 * strcmp, 2 compares case-insensitively.
 *
 * Parameters:
 *   fileName1    char *
 *   fileName2    char *
 *   iCaseSensitivity int
 *
 * Calls: strcmpcasenosensitive_internal
 * C library: strcmp
 * Called by: unzLocateFile
 *
 */
int unzStringFileNameCompare(char *fileName1,char *fileName2,int iCaseSensitivity)

{
  int i1;
  
  if (iCaseSensitivity == 0) {
    iCaseSensitivity = 1;
  }
  if (iCaseSensitivity == 1) {
    i1 = strcmp(fileName1,fileName2);
    return i1;
  }
  i1 = strcmpcasenosensitive_internal(fileName1,fileName2);
  return i1;
}

/* unzlocal_SearchCentralDir @ 0x080804c0, 280 bytes
 *
 * Searches backwards from the end of the archive (at most 64 KB plus the
 * comment) for the end-of-central-directory signature "PK\5\6". Returns its
 * file offset, or 0.
 *
 * Parameters:
 *   fin          FILE *
 *
 * C library: fseek, ftell, malloc, fread, free
 * Called by: unzOpen
 *
 */
int unzlocal_SearchCentralDir(FILE *fin)

{
  uint32_t u1;
  int i2;
  uint32_t u3;
  void *ptr;
  size_t s4;
  int i5;
  int i6;
  uint32_t u7;
  size_t size;
  int stk_1c;
  uint32_t stk_18;
  
  stk_18 = 0xffff;
  stk_1c = 0;
  i2 = fseek(fin,0,2);
  if (i2 == 0) {
    u3 = ftell(fin);
    if (u3 < 0xffff) {
      stk_18 = u3;
    }
    u7 = 4;
    ptr = malloc(0x404);
    if (ptr != (void *)0x0) {
      while (u7 < stk_18) {
        u1 = u7 + 0x400;
        u7 = stk_18;
        if (u1 <= stk_18) {
          u7 = u1;
        }
        i2 = u3 - u7;
        size = u3 - i2;
        if (0x404 < size) {
          size = 0x404;
        }
        i5 = fseek(fin,i2,0);
        if ((i5 != 0) || (s4 = fread(ptr,size,1,fin), s4 != 1)) break;
        i5 = size - 3;
        do {
          i6 = i5;
          i5 = i6 + -1;
          if (i6 < 1) goto L_0808056e;
        } while ((((*(char *)(i5 + (int)ptr) != 'P') || (*(char *)(i6 + (int)ptr) != 'K')) ||
                 (*(char *)(i6 + 1 + (int)ptr) != '\x05')) ||
                (*(char *)(i6 + 2 + (int)ptr) != '\x06'));
        stk_1c = i2 + i5;
L_0808056e:
        if (stk_1c != 0) break;
      }
      if (ptr == (void *)0x0) {
        return stk_1c;
      }
      free(ptr);
      return stk_1c;
    }
  }
  return 0;
}

/* unzOpen @ 0x080805e0, 444 bytes
 *
 * Opens a zip archive: finds and reads the end-of-central-directory record
 * (entry count, central directory size and offset, comment size), checks it
 * is a single-disk archive, and positions on the first entry. Returns the
 * handle, or NULL.
 *
 * Parameters:
 *   path         char *
 *
 * Calls: unzlocal_SearchCentralDir, unzlocal_getLong, unzlocal_getShort,
 *        unzGoToFirstFile
 * C library: fopen, fseek, malloc, fclose
 * Called by: MFfopenZip
 *
 * Note: Locals live in `frame`, laid out as on the original stack (0xa0 bytes,
 *       12 variables), because their address is taken.
 */
uint32_t * unzOpen(char *path)

{
  FILE *stream;
  uint32_t *zipfile;
  uint32_t off;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  int i7;
  uint32_t u8;
  FILE **ppFVar9;
  uint32_t *pu10;
  unsigned char frame[0xa0] __attribute__((aligned(16)));
#define stk_9c (*(uint32_t *)(frame + 0x4))
#define stk_98 (*(uint32_t *)(frame + 0x8))
#define stk_94 (*(uint32_t *)(frame + 0xc))
#define stk_90 (*(uint32_t *)(frame + 0x10))
#define stk_8c (*(FILE **)(frame + 0x14))
#define stk_88 (*(uint32_t *)(frame + 0x18))
#define stk_84 (*(uint32_t *)(frame + 0x1c))
#define stk_80 (*(int *)(frame + 0x20))
#define stk_70 (*(uint32_t *)(frame + 0x30))
#define stk_6c (*(uint32_t *)(frame + 0x34))
#define stk_68 (*(uint32_t (*)[22])(frame + 0x38))
#define stk_10 (*(uint32_t *)(frame + 0x90))
  
  stream = fopen(path,"rb");
  if (stream == (FILE *)0x0) {
    zipfile = (uint32_t *)0x0;
  }
  else {
    off = unzlocal_SearchCentralDir(stream);
    i2 = fseek(stream,off,0);
    i3 = unzlocal_getLong(stream,&stk_90);
    i4 = unzlocal_getShort(stream,&stk_94);
    i5 = unzlocal_getShort(stream,&stk_98);
    i6 = unzlocal_getShort(stream,&stk_88);
    i7 = unzlocal_getShort(stream,&stk_9c);
    u8 = (off != 0) - 1 | (i2 == 0) - 1 | (i3 == 0) - 1 | (i4 == 0) - 1 |
            (i5 == 0) - 1 | (i6 == 0) - 1 | (i7 == 0) - 1;
    if (((stk_9c != stk_88) || (stk_98 != 0)) || (stk_94 != 0)) {
      u8 = 0xffffff99;
    }
    i2 = unzlocal_getLong(stream,&stk_6c);
    i3 = unzlocal_getLong(stream,stk_68);
    i4 = unzlocal_getShort(stream,&stk_84);
    u8 = u8 | (i2 == 0) - 1 | (i3 == 0) - 1 | (i4 == 0) - 1;
    if ((off < stk_6c + stk_68[0]) && (u8 == 0)) {
      u8 = 0xffffff99;
    }
    if (u8 == 0) {
      stk_80 = (off - stk_68[0]) - stk_6c;
      stk_10 = 0;
      stk_8c = stream;
      stk_70 = off;
      zipfile = malloc(0x80);
      ppFVar9 = &stk_8c;
      pu10 = zipfile;
      for (i2 = 0x20; i2 != 0; i2 = i2 + -1) {
        *pu10 = *ppFVar9;
        ppFVar9 = ppFVar9 + 1;
        pu10 = pu10 + 1;
      }
      unzGoToFirstFile(zipfile);
    }
    else {
      fclose(stream);
      zipfile = (uint32_t *)0x0;
    }
  }
  return zipfile;
}
#undef stk_9c
#undef stk_98
#undef stk_94
#undef stk_90
#undef stk_8c
#undef stk_88
#undef stk_84
#undef stk_80
#undef stk_70
#undef stk_6c
#undef stk_68
#undef stk_10

/* unzClose @ 0x080807a0, 63 bytes
 *
 * Closes the current member (if open), the archive file and frees the
 * handle.
 *
 * Parameters:
 *   zipfile      void *
 *
 * Calls: unzCloseCurrentFile
 * C library: fclose, free
 * Called by: MFfclose
 *
 */
uint32_t unzClose(void *zipfile)

{
  uint32_t u1;
  
  u1 = 0xffffff9a;
  if (zipfile != (void *)0x0) {
    if (*(int *)((int)zipfile + 0x7c) != 0) {
      unzCloseCurrentFile((int)zipfile);
    }
    fclose(*(FILE **)zipfile);
    free(zipfile);
    u1 = 0;
  }
  return u1;
}

/* unzGetGlobalInfo @ 0x080807e0, 34 bytes
 *
 * Copies the archive's global information (entry count, comment size). Not
 * called in this build.
 *
 * Parameters:
 *   zipfile      int
 *   pglobal_info uint32_t *
 *
 */
uint32_t unzGetGlobalInfo(int zipfile,uint32_t *pglobal_info)

{
  uint32_t u1;
  
  if (zipfile == 0) {
    return 0xffffff9a;
  }
  u1 = *(uint32_t *)(zipfile + 8);
  *pglobal_info = *(uint32_t *)(zipfile + 4);
  pglobal_info[1] = u1;
  return 0;
}

/* unzlocal_DosDateToTmuDate @ 0x08080810, 83 bytes
 *
 * Converts an MS-DOS date/time into a tm_unz structure.
 *
 * Parameters:
 *   ulDosDate    uint32_t
 *   ptm          int *
 *
 * Called by: unzlocal_GetCurrentFileInfoInternal
 *
 */
void unzlocal_DosDateToTmuDate(uint32_t ulDosDate,int *ptm)

{
  ptm[3] = ulDosDate >> 0x10 & 0x1f;
  ptm[5] = (ulDosDate >> 0x19) + 0x7bc;
  ptm[4] = ((ulDosDate >> 0x10 & 0x1e0) >> 5) - 1;
  ptm[2] = (ulDosDate & 0xf800) >> 0xb;
  ptm[1] = (ulDosDate & 0x7e0) >> 5;
  *ptm = (ulDosDate & 0x1f) * 2;
  return;
}

/* unzlocal_GetCurrentFileInfoInternal @ 0x08080870, 955 bytes
 *
 * Reads the central directory header of the current entry: version, flags,
 * compression method, DOS date, CRC, sizes, name, extra field and comment
 * lengths, disk and attributes. Copies the name, extra field and comment
 * into the caller's buffers when given.
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         uint32_t *
 *   arg3         uint32_t *
 *   arg4         size_t
 *   arg5         uint32_t
 *   arg6         size_t
 *   arg7         void *
 *   arg8         size_t
 *   arg9         void *
 *
 * Calls: unzlocal_getLong, unzlocal_getShort, unzlocal_DosDateToTmuDate
 * C library: fseek, fread
 * Called by: unzGetCurrentFileInfo, unzGoToFirstFile, unzGoToNextFile
 *
 * Note: Locals live in `frame`, laid out as on the original stack (0x80 bytes,
 *       14 variables), because their address is taken.
 */
uint32_t unzlocal_GetCurrentFileInfoInternal
               (uint32_t *arg1,uint32_t *arg2,uint32_t *arg3,size_t arg4,uint32_t arg5,
               size_t arg6,void *arg7,size_t arg8,void *arg9)

{
  uint32_t u1;
  int i2;
  int i3;
  int i4;
  int i5;
  int i6;
  int i7;
  int i8;
  int i9;
  int i10;
  int i11;
  int i12;
  int i13;
  int i14;
  int i15;
  int i16;
  size_t s17;
  uint32_t u18;
  void *pv19;
  uint32_t *pu20;
  unsigned char frame[0x80] __attribute__((aligned(16)));
#define stk_74 (*(uint32_t *)(frame + 0xc))
#define stk_70 (*(uint32_t *)(frame + 0x10))
#define stk_6c (*(uint32_t (*)[4])(frame + 0x14))
#define stk_5c (*(uint32_t *)(frame + 0x24))
#define stk_58 (*(uint32_t *)(frame + 0x28))
#define stk_54 (*(uint32_t *)(frame + 0x2c))
#define stk_50 (*(uint32_t *)(frame + 0x30))
#define stk_4c (*(uint32_t *)(frame + 0x34))
#define stk_48 (*(void **)(frame + 0x38))
#define stk_44 (*(void **)(frame + 0x3c))
#define stk_40 (*(uint32_t *)(frame + 0x40))
#define stk_3c (*(uint32_t *)(frame + 0x44))
#define stk_38 (*(uint32_t *)(frame + 0x48))
#define stk_34 (*(int (*)[9])(frame + 0x4c))
  
  u1 = 0xffffff9a;
  if (arg1 != (uint32_t *)0x0) {
    i2 = fseek((FILE *)*arg1,arg1[3] + arg1[5],0);
    u1 = (i2 == 0) - 1;
    if (u1 == 0) {
      i2 = unzlocal_getLong((_IO_FILE *)*arg1,&stk_70);
      if (i2 == 0) {
        if (stk_70 != 0x2014b50) {
          u1 = 0xffffff99;
        }
      }
      else {
        u1 = 0xffffffff;
      }
    }
    i2 = unzlocal_getShort((_IO_FILE *)*arg1,stk_6c);
    i3 = unzlocal_getShort((_IO_FILE *)*arg1,stk_6c + 1);
    i4 = unzlocal_getShort((_IO_FILE *)*arg1,stk_6c + 2);
    i5 = unzlocal_getShort((_IO_FILE *)*arg1,stk_6c + 3);
    i6 = unzlocal_getLong((_IO_FILE *)*arg1,&stk_5c);
    unzlocal_DosDateToTmuDate(stk_5c,stk_34);
    i7 = unzlocal_getLong((_IO_FILE *)*arg1,&stk_58);
    i8 = unzlocal_getLong((_IO_FILE *)*arg1,&stk_54);
    i9 = unzlocal_getLong((_IO_FILE *)*arg1,&stk_50);
    i10 = unzlocal_getShort((_IO_FILE *)*arg1,&stk_4c);
    i11 = unzlocal_getShort((_IO_FILE *)*arg1,(uint32_t *)&stk_48);
    i12 = unzlocal_getShort((_IO_FILE *)*arg1,(uint32_t *)&stk_44);
    i13 = unzlocal_getShort((_IO_FILE *)*arg1,&stk_40);
    i14 = unzlocal_getShort((_IO_FILE *)*arg1,&stk_3c);
    i15 = unzlocal_getLong((_IO_FILE *)*arg1,&stk_38);
    i16 = unzlocal_getLong((_IO_FILE *)*arg1,&stk_74);
    u1 = u1 | (i2 == 0) - 1 | (i3 == 0) - 1 | (i4 == 0) - 1 | (i5 == 0) - 1 |
            (i6 == 0) - 1 | (i7 == 0) - 1 | (i8 == 0) - 1 | (i9 == 0) - 1 |
            (i10 == 0) - 1 | (i11 == 0) - 1 | (i12 == 0) - 1 | (i13 == 0) - 1 |
            (i14 == 0) - 1 | (i15 == 0) - 1 | (i16 == 0) - 1;
    u18 = stk_4c;
    if ((u1 == 0) && (arg4 != 0)) {
      u18 = arg5;
      if (stk_4c < arg5) {
        *(uint8_t *)(stk_4c + arg4) = 0;
        u18 = stk_4c;
      }
      if ((stk_4c != 0) && (arg5 != 0)) {
        s17 = fread((void *)arg4,u18,1,(FILE *)*arg1);
        u1 = (s17 == 1) - 1;
      }
      u18 = stk_4c - u18;
    }
    if ((u1 == 0) && (arg6 != 0)) {
      pv19 = stk_48;
      if (arg7 <= stk_48) {
        pv19 = arg7;
      }
      if (u18 != 0) {
        i2 = fseek((FILE *)*arg1,u18,1);
        if (i2 == 0) {
          u18 = 0;
        }
        else {
          u1 = 0xffffffff;
        }
      }
      if ((stk_48 != (void *)0x0) && (arg7 != (void *)0x0)) {
        s17 = fread((void *)arg6,(size_t)pv19,1,(FILE *)*arg1);
        u1 = u1 | (s17 == 1) - 1;
      }
      stk_48 = (void *)((int)stk_48 - (int)pv19);
    }
    if ((u1 == 0) && (arg8 != 0)) {
      pv19 = arg9;
      if (stk_44 < arg9) {
        *(uint8_t *)((int)stk_44 + arg8) = 0;
        pv19 = stk_44;
      }
      if ((u18 + (int)stk_48 != 0) &&
         (i2 = fseek((FILE *)*arg1,u18 + (int)stk_48,1), i2 != 0)) {
        u1 = 0xffffffff;
      }
      if ((stk_44 != (void *)0x0) && (arg9 != (void *)0x0)) {
        s17 = fread((void *)arg8,(size_t)pv19,1,(FILE *)*arg1);
        u1 = u1 | (s17 == 1) - 1;
      }
    }
    if ((u1 == 0) && (arg2 != (uint32_t *)0x0)) {
      pu20 = stk_6c;
      for (i2 = 0x14; i2 != 0; i2 = i2 + -1) {
        *arg2 = *pu20;
        pu20 = pu20 + 1;
        arg2 = arg2 + 1;
      }
    }
    if ((u1 == 0) && (arg3 != (uint32_t *)0x0)) {
      *arg3 = stk_74;
    }
  }
  return u1;
}
#undef stk_74
#undef stk_70
#undef stk_6c
#undef stk_5c
#undef stk_58
#undef stk_54
#undef stk_50
#undef stk_4c
#undef stk_48
#undef stk_44
#undef stk_40
#undef stk_3c
#undef stk_38
#undef stk_34

/* unzGetCurrentFileInfo @ 0x08080c30, 54 bytes
 *
 * Public wrapper of unzlocal_GetCurrentFileInfoInternal. MFzopen uses it to
 * learn the uncompressed size of a member.
 *
 * Parameters:
 *   zipfile      uint32_t *
 *   pfile_info   uint32_t *
 *   szFileName   size_t
 *   fileNameBufferSize uint32_t
 *   extraField   size_t
 *   extraFieldBufferSize void *
 *   szComment    size_t
 *   commentBufferSize void *
 *
 * Calls: unzlocal_GetCurrentFileInfoInternal
 * Called by: MFzopen, unzLocateFile
 *
 */
uint32_t unzGetCurrentFileInfo
               (uint32_t *zipfile,uint32_t *pfile_info,size_t szFileName,uint32_t fileNameBufferSize,size_t extraField,
               void *extraFieldBufferSize,size_t szComment,void *commentBufferSize)

{
  uint32_t u1;
  
  u1 = unzlocal_GetCurrentFileInfoInternal
                    (zipfile,pfile_info,(uint32_t *)0x0,szFileName,fileNameBufferSize,extraField,extraFieldBufferSize,szComment,commentBufferSize);
  return u1;
}

/* unzGoToFirstFile @ 0x08080c70, 75 bytes
 *
 * Makes the first entry of the central directory current.
 *
 * Parameters:
 *   zipfile      uint32_t *
 *
 * Calls: unzlocal_GetCurrentFileInfoInternal
 * Called by: unzLocateFile, unzOpen
 *
 */
uint32_t unzGoToFirstFile(uint32_t *zipfile)

{
  uint32_t u1;
  
  u1 = 0xffffff9a;
  if (zipfile != (uint32_t *)0x0) {
    zipfile[5] = zipfile[9];
    zipfile[4] = 0;
    u1 = unzlocal_GetCurrentFileInfoInternal
                      (zipfile,zipfile + 10,zipfile + 0x1e,0,0,0,(void *)0x0,0,(void *)0x0);
    zipfile[6] = (uint32_t)(u1 == 0);
  }
  return u1;
}

/* unzGoToNextFile @ 0x08080cc0, 119 bytes
 *
 * Makes the next entry current. Returns UNZ_END_OF_LIST_OF_FILE after the
 * last one.
 *
 * Parameters:
 *   zipfile      uint32_t *
 *
 * Calls: unzlocal_GetCurrentFileInfoInternal
 * Called by: unzLocateFile
 *
 */
uint32_t unzGoToNextFile(uint32_t *zipfile)

{
  uint32_t u1;
  
  u1 = 0xffffff9a;
  if (zipfile != (uint32_t *)0x0) {
    if (zipfile[6] == 0) {
      u1 = 0xffffff9c;
    }
    else {
      u1 = 0xffffff9c;
      if (zipfile[4] + 1 != zipfile[1]) {
        zipfile[4] = zipfile[4] + 1;
        zipfile[5] = zipfile[0x13] + zipfile[0x12] + zipfile[0x14] + zipfile[5] + 0x2e;
        u1 = unzlocal_GetCurrentFileInfoInternal
                          (zipfile,zipfile + 10,zipfile + 0x1e,0,0,0,(void *)0x0,0,(void *)0x0);
        zipfile[6] = (uint32_t)(u1 == 0);
      }
    }
  }
  return u1;
}

/* unzLocateFile @ 0x08080d40, 198 bytes
 *
 * Searches the central directory for `szFileName` (comparison per
 * iCaseSensitivity) and makes that entry current. Returns UNZ_OK or
 * UNZ_END_OF_LIST_OF_FILE (the previous position is restored).
 *
 * Parameters:
 *   zipfile      uint32_t *
 *   szFileName   char *
 *   iCaseSensitivity int
 *
 * Calls: unzGoToFirstFile, unzGetCurrentFileInfo,
 *        unzStringFileNameCompare, unzGoToNextFile
 * C library: strlen
 * Called by: MFzopen
 *
 * Note: Locals live in `frame`, laid out as on the original stack (0x130 bytes,
 *       1 variables), because their address is taken.
 */
uint32_t unzLocateFile(uint32_t *zipfile,char *szFileName,int iCaseSensitivity)

{
  uint32_t u1;
  uint32_t u2;
  uint32_t u3;
  size_t s4;
  int i5;
  unsigned char frame[0x130] __attribute__((aligned(16)));
#define stk_12c (*(char (*)[284])(frame + 0x4))
  
  u3 = 0xffffff9a;
  if (zipfile != (uint32_t *)0x0) {
    s4 = strlen(szFileName);
    if (s4 < 0x100) {
      if (zipfile[6] == 0) {
        u3 = 0xffffff9c;
      }
      else {
        u1 = zipfile[5];
        u2 = zipfile[4];
        u3 = unzGoToFirstFile(zipfile);
        if (u3 == 0) {
          do {
            unzGetCurrentFileInfo
                      (zipfile,(uint32_t *)0x0,(size_t)stk_12c,0x100,0,(void *)0x0,0,(void *)0x0);
            i5 = unzStringFileNameCompare(stk_12c,szFileName,iCaseSensitivity);
            if (i5 == 0) {
              return 0;
            }
            u3 = unzGoToNextFile(zipfile);
          } while (u3 == 0);
        }
        zipfile[4] = u2;
        zipfile[5] = u1;
      }
    }
    else {
      u3 = 0xffffff9a;
    }
  }
  return u3;
}
#undef stk_12c

/* unzlocal_CheckCurrentFileCoherencyHeader @ 0x08080e10, 554 bytes
 *
 * Reads the local header of the current entry and checks it agrees with the
 * central directory (method, CRC, sizes, name length). Returns the offset of
 * the local extra field and its size.
 *
 * Parameters:
 *   arg1         uint32_t *
 *   arg2         int *
 *   arg3         int *
 *   arg4         uint32_t *
 *
 * Calls: unzlocal_getLong, unzlocal_getShort
 * C library: fseek
 * Called by: unzOpenCurrentFile
 *
 * Note: Locals live in `frame`, laid out as on the original stack (0x30 bytes, 5
 *       variables), because their address is taken.
 */
uint32_t unzlocal_CheckCurrentFileCoherencyHeader
               (uint32_t *arg1,int *arg2,int *arg3,uint32_t *arg4)

{
  int i1;
  int i2;
  uint32_t u3;
  unsigned char frame[0x30] __attribute__((aligned(16)));
#define stk_24 (*(uint32_t *)(frame + 0xc))
#define stk_20 (*(uint32_t *)(frame + 0x10))
#define stk_1c (*(uint32_t *)(frame + 0x14))
#define stk_18 (*(uint32_t *)(frame + 0x18))
#define stk_14 (*(uint32_t *)(frame + 0x1c))
  
  u3 = 0;
  *arg2 = 0;
  *arg3 = 0;
  *arg4 = 0;
  i1 = fseek((FILE *)*arg1,arg1[3] + arg1[0x1e],0);
  if (i1 == 0) {
    i1 = unzlocal_getLong((_IO_FILE *)*arg1,&stk_14);
    if (i1 == 0) {
      if (stk_14 != 0x4034b50) {
        u3 = 0xffffff99;
      }
    }
    else {
      u3 = 0xffffffff;
    }
    i1 = unzlocal_getShort((_IO_FILE *)*arg1,&stk_18);
    i2 = unzlocal_getShort((_IO_FILE *)*arg1,&stk_1c);
    u3 = u3 | (i1 == 0) - 1 | (i2 == 0) - 1;
    i1 = unzlocal_getShort((_IO_FILE *)*arg1,&stk_18);
    if (i1 == 0) {
      if ((u3 == 0) && (stk_18 != arg1[0xd])) {
        u3 = 0xffffff99;
      }
    }
    else {
      u3 = 0xffffffff;
    }
    if (((u3 == 0) && (arg1[0xd] != 0)) && (arg1[0xd] != 8)) {
      u3 = 0xffffff99;
    }
    i1 = unzlocal_getLong((_IO_FILE *)*arg1,&stk_18);
    u3 = u3 | (i1 == 0) - 1;
    i1 = unzlocal_getLong((_IO_FILE *)*arg1,&stk_18);
    if (i1 == 0) {
      if (((u3 == 0) && (stk_18 != arg1[0xf])) && ((stk_1c & 8) == 0)) {
        u3 = 0xffffff99;
      }
    }
    else {
      u3 = 0xffffffff;
    }
    i1 = unzlocal_getLong((_IO_FILE *)*arg1,&stk_18);
    if (i1 == 0) {
      if (((u3 == 0) && (stk_18 != arg1[0x10])) && ((stk_1c & 8) == 0)) {
        u3 = 0xffffff99;
      }
    }
    else {
      u3 = 0xffffffff;
    }
    i1 = unzlocal_getLong((_IO_FILE *)*arg1,&stk_18);
    if (i1 == 0) {
      if (((u3 == 0) && (stk_18 != arg1[0x11])) && ((stk_1c & 8) == 0)) {
        u3 = 0xffffff99;
      }
    }
    else {
      u3 = 0xffffffff;
    }
    i1 = unzlocal_getShort((_IO_FILE *)*arg1,&stk_20);
    if (i1 == 0) {
      if ((u3 == 0) && (stk_20 != arg1[0x12])) {
        u3 = 0xffffff99;
      }
    }
    else {
      u3 = 0xffffffff;
    }
    *arg2 = *arg2 + stk_20;
    i1 = unzlocal_getShort((_IO_FILE *)*arg1,&stk_24);
    u3 = u3 | (i1 == 0) - 1;
    *arg3 = stk_20 + arg1[0x1e] + 0x1e;
    *arg4 = stk_24;
    *arg2 = *arg2 + stk_24;
  }
  else {
    u3 = 0xffffffff;
  }
  return u3;
}
#undef stk_24
#undef stk_20
#undef stk_1c
#undef stk_18
#undef stk_14

/* unzOpenCurrentFile @ 0x08081040, 340 bytes
 *
 * Opens the current entry for reading: checks the local header, allocates
 * the read buffer and, for deflated entries, starts zlib inflate (stored
 * entries are copied as they are).
 *
 * Parameters:
 *   zipfile      uint32_t *
 *
 * Calls: unzCloseCurrentFile, unzlocal_CheckCurrentFileCoherencyHeader
 * C library: malloc, free, inflateInit2_
 * Called by: MFzopen
 *
 * Note: Locals live in `frame`, laid out as on the original stack (0x20 bytes, 3
 *       variables), because their address is taken.
 */
uint32_t unzOpenCurrentFile(uint32_t *zipfile)

{
  int i1;
  uint32_t u2;
  uint32_t u3;
  uint32_t *ptr;
  void *pv4;
  uint64_t u5;
  unsigned char frame[0x20] __attribute__((aligned(16)));
#define stk_14 (*(int *)(frame + 0xc))
#define stk_10 (*(int *)(frame + 0x10))
#define stk_c (*(uint32_t *)(frame + 0x14))
  
  u2 = 0xffffff9a;
  if (zipfile != (uint32_t *)0x0) {
    if (zipfile[6] == 0) {
      u2 = 0xffffff9a;
    }
    else {
      if (zipfile[0x1f] != 0) {
        unzCloseCurrentFile((int)zipfile);
      }
      u3 = unzlocal_CheckCurrentFileCoherencyHeader(zipfile,&stk_14,&stk_10,&stk_c);
      if (u3 == 0) {
        ptr = malloc(0x6c);
        u2 = 0xffffff98;
        if (ptr != (uint32_t *)0x0) {
          pv4 = malloc(0x4000);
          *ptr = pv4;
          ptr[0x11] = stk_10;
          ptr[0x12] = stk_c;
          ptr[0x13] = 0;
          if (pv4 == (void *)0x0) {
            free(ptr);
            u2 = 0xffffff98;
          }
          else {
            ptr[0x10] = 0;
            i1 = zipfile[0xd];
            u2 = zipfile[0xf];
            ptr[0x19] = i1;
            ptr[0x15] = u2;
            u2 = *zipfile;
            ptr[0x14] = 0;
            ptr[0x18] = u2;
            ptr[0x1a] = zipfile[3];
            ptr[6] = 0;
            if (i1 != 0) {
              ptr[9] = 0;
              ptr[10] = 0;
              ptr[0xb] = 0;
              u5 = inflateInit2_((int)(ptr + 1),-0xf,"1.1.3",0x38);
              if ((int)u5 == 0) {
                ptr[0x10] = 1;
              }
            }
            zipfile[0x1f] = ptr;
            ptr[0x16] = zipfile[0x10];
            ptr[0x17] = zipfile[0x11];
            ptr[0xf] = stk_14 + zipfile[0x1e] + 0x1e;
            u2 = 0;
            ptr[2] = 0;
          }
        }
      }
      else {
        u2 = 0xffffff99;
      }
    }
  }
  return u2;
}
#undef stk_14
#undef stk_10
#undef stk_c

/* unzReadCurrentFile @ 0x080811a0, 497 bytes
 *
 * Reads and decompresses up to `len` bytes of the current entry into `buf`,
 * refilling the input buffer from the archive as needed and updating the
 * CRC. Returns the number of bytes read, 0 at the end, or a negative error.
 *
 * Parameters:
 *   zipfile      int
 *   buf          int
 *   len          uint32_t
 *
 * C library: fseek, fread, crc32, inflate
 * Called by: MFzopen
 *
 */
uint32_t unzReadCurrentFile(int zipfile,int buf,uint32_t len)

{
  int *pi1;
  uint8_t *pb2;
  int i3;
  size_t s4;
  uint32_t u5;
  uint32_t i2;
  size_t size;
  uint32_t stk_18;
  uint32_t stk_14;
  
  stk_14 = 0;
  stk_18 = 0;
  if (zipfile == 0) {
    u5 = 0xffffff9a;
  }
  else {
    pi1 = *(int **)(zipfile + 0x7c);
    u5 = 0xffffff9a;
    if (pi1 != (int *)0x0) {
      if (*pi1 == 0) {
        u5 = 0xffffff9c;
      }
      else if (len == 0) {
L_080811f5:
        u5 = 0;
      }
      else {
        pi1[5] = len;
        pi1[4] = buf;
        if ((uint32_t)pi1[0x17] < len) {
          pi1[5] = pi1[0x17];
        }
        i3 = pi1[5];
        while (i3 != 0) {
          if ((pi1[2] == 0) && (u5 = pi1[0x16], u5 != 0)) {
            size = 0x4000;
            if (u5 < 0x4000) {
              size = u5;
            }
            if (size == 0) goto L_080811f5;
            i3 = fseek((FILE *)pi1[0x18],pi1[0x1a] + pi1[0xf],0);
            if ((i3 != 0) ||
               (s4 = fread((void *)*pi1,size,1,(FILE *)pi1[0x18]), s4 != 1)) {
              return 0xffffffff;
            }
            pi1[0xf] = pi1[0xf] + size;
            pi1[0x16] = pi1[0x16] - size;
            pi1[1] = *pi1;
            pi1[2] = size;
          }
          if (pi1[0x19] == 0) {
            u5 = pi1[5];
            if ((uint32_t)pi1[2] <= (uint32_t)pi1[5]) {
              u5 = pi1[2];
            }
            i2 = 0;
            if (u5 != 0) {
              do {
                *(uint8_t *)(i2 + pi1[4]) = *(uint8_t *)(i2 + pi1[1]);
                i2 = i2 + 1;
              } while (i2 < u5);
            }
            i2 = crc32(pi1[0x14],(uint8_t *)pi1[4],u5);
            pi1[0x14] = i2;
            pi1[0x17] = pi1[0x17] - u5;
            pi1[2] = pi1[2] - u5;
            stk_18 = stk_18 + u5;
            pi1[5] = pi1[5] - u5;
            pi1[4] = pi1[4] + u5;
            pi1[1] = pi1[1] + u5;
            pi1[6] = pi1[6] + u5;
          }
          else {
            i3 = pi1[6];
            pb2 = (uint8_t *)pi1[4];
            stk_14 = inflate(pi1 + 1,2);
            i2 = pi1[6] - i3;
            u5 = crc32(pi1[0x14],pb2,i2);
            stk_18 = stk_18 + i2;
            pi1[0x14] = u5;
            pi1[0x17] = pi1[0x17] - i2;
            if (stk_14 == 1) goto L_08081376;
            if (stk_14 != 0) break;
          }
          i3 = pi1[5];
        }
        u5 = stk_14;
        if (stk_14 == 0) {
L_08081376:
          u5 = stk_18;
        }
      }
    }
  }
  return u5;
}

/* unztell @ 0x080813a0, 25 bytes
 *
 * Returns the number of uncompressed bytes read from the current entry. Not
 * called in this build.
 *
 * Parameters:
 *   zipfile      int
 *
 */
uint32_t unztell(int zipfile)

{
  if ((zipfile != 0) && (*(int *)(zipfile + 0x7c) != 0)) {
    return *(uint32_t *)(*(int *)(zipfile + 0x7c) + 0x18);
  }
  return 0xffffff9a;
}

/* unzeof @ 0x080813c0, 32 bytes
 *
 * Returns 1 when the whole current entry has been read.
 *
 * Parameters:
 *   zipfile      int
 *
 * Called by: MFzopen
 *
 */
uint32_t unzeof(int zipfile)

{
  if ((zipfile != 0) && (*(int *)(zipfile + 0x7c) != 0)) {
    return (uint32_t)(*(int *)(*(int *)(zipfile + 0x7c) + 0x5c) == 0);
  }
  return 0xffffff9a;
}

/* unzGetLocalExtrafield @ 0x080813e0, 147 bytes
 *
 * Reads the local extra field of the current entry. Not called in this
 * build.
 *
 * Parameters:
 *   zipfile      int
 *   buf          size_t
 *   len          uint32_t
 *
 * C library: fseek, fread
 *
 */
uint32_t unzGetLocalExtrafield(int zipfile,size_t buf,uint32_t len)

{
  int i1;
  uint32_t size;
  int i2;
  size_t s3;
  uint32_t u4;
  
  if (zipfile == 0) {
    size = 0xffffff9a;
  }
  else {
    i1 = *(int *)(zipfile + 0x7c);
    size = 0xffffff9a;
    if (i1 != 0) {
      size = *(int *)(i1 + 0x48) - *(int *)(i1 + 0x4c);
      if (buf != 0) {
        u4 = size;
        if (len <= size) {
          u4 = len;
        }
        if (u4 == 0) {
          size = 0;
        }
        else {
          i2 = fseek(*(FILE **)(i1 + 0x60),*(int *)(i1 + 0x4c) + *(int *)(i1 + 0x44),0);
          if (i2 == 0) {
            s3 = fread((void *)buf,size,1,*(FILE **)(i1 + 0x60));
            size = (s3 == 1) - 1 | u4;
          }
          else {
            size = 0xffffffff;
          }
        }
      }
    }
  }
  return size;
}

/* unzCloseCurrentFile @ 0x08081480, 123 bytes
 *
 * Closes the current entry: ends zlib inflate, frees the read buffer and
 * returns UNZ_CRCERROR if the whole entry was read and its CRC does not
 * match.
 *
 * Parameters:
 *   zipfile      int
 *
 * C library: free, inflateEnd
 * Called by: MFfclose, MFzclose, MFzopen, unzClose, unzOpenCurrentFile
 *
 */
uint32_t unzCloseCurrentFile(int zipfile)

{
  uint32_t *ptr;
  uint32_t u1;
  
  u1 = 0xffffff9a;
  if ((zipfile != 0) && (ptr = *(uint32_t **)(zipfile + 0x7c), ptr != (uint32_t *)0x0)) {
    u1 = 0;
    if ((ptr[0x17] == 0) && (ptr[0x14] != ptr[0x15])) {
      u1 = 0xffffff97;
    }
    if ((void *)*ptr != (void *)0x0) {
      free((void *)*ptr);
    }
    *ptr = 0;
    if (ptr[0x10] != 0) {
      inflateEnd((int)(ptr + 1));
    }
    ptr[0x10] = 0;
    free(ptr);
    *(uint32_t *)(zipfile + 0x7c) = 0;
  }
  return u1;
}

/* unzGetGlobalComment @ 0x08081500, 121 bytes
 *
 * Copies the archive comment. Not called in this build.
 *
 * Parameters:
 *   zipfile      uint32_t *
 *   szComment    uint8_t *
 *   uSizeBuf     uint32_t
 *
 * C library: fseek, fread
 *
 */
uint32_t unzGetGlobalComment(uint32_t *zipfile,uint8_t *szComment,uint32_t uSizeBuf)

{
  int i1;
  size_t s2;
  uint32_t size;
  
  if (zipfile == (uint32_t *)0x0) {
    return 0xffffff9a;
  }
  size = uSizeBuf;
  if ((uint32_t)zipfile[2] < uSizeBuf) {
    size = zipfile[2];
  }
  i1 = fseek((FILE *)*zipfile,zipfile[7] + 0x16,0);
  if (i1 == 0) {
    if (size != 0) {
      *szComment = 0;
      s2 = fread(szComment,size,1,(FILE *)*zipfile);
      if (s2 != 1) goto L_08081559;
    }
    if ((szComment != (uint8_t *)0x0) && ((uint32_t)zipfile[2] < uSizeBuf)) {
      szComment[zipfile[2]] = 0;
    }
  }
  else {
L_08081559:
    size = 0xffffffff;
  }
  return size;
}

