/*
 * date.c -- dates
 * Date comparison (character versions) and date formatting.
 *
 * Reconstructed from the LINUXMUGEN 2002.04.14 executable (Elecbyte, GCC 2.96).
 * Elecbyte's file: src/mugen/date.c.
 * Not Elecbyte source code: rebuilt from the machine code, see
 * reconstruction/README.md. Function blocks: tools/translate/docs.py.
 */
#include "mugen_common.h"


/* MDYDateCmp @ 0x0808d830, 51 bytes
 *
 * Compares two dates given as (month, day, year) triples, year first, then
 * month, then day. Returns -1, 0 or 1. Used to compare a character's
 * "mugenversion" with the engine's version date.
 *
 * Parameters:
 *   m1           int
 *   d1           int
 *   y1           int
 *   m2           int
 *   d2           int
 *   y2           int
 *
 * Called by: GameVarInit, PlayerDefLoadPtr, PlayerDefLoadZip
 *
 * Elecbyte file: src/mugen/date.c
 */
int MDYDateCmp(int m1,int d1,int y1,int m2,int d2,int y2)

{
  if (y1 == y2) {
    y1 = m1;
    y2 = m2;
    if (m1 == m2) {
      y1 = d1;
      y2 = d2;
      if (d1 == d2) {
        return 0;
      }
    }
  }
  return (uint32_t)(y2 < y1) * 2 + -1;
}

/* datenotostr @ 0x0808d870, 197 bytes
 *
 * Formats a date as text ("April 14th, 2002"): month name from a table, day
 * with its English ordinal suffix ("st", "nd", "rd", "th", with 11-13 as
 * "th"), and year. Used by the information box of the mode select screen.
 *
 * Parameters:
 *   arg1         uint32_t
 *   arg2         int
 *   arg3         uint8_t **
 *   arg4         char *
 *
 * C library: sprintf, strcat, strlen
 * Called by: ModeSelect
 *
 * Elecbyte file: src/mugen/date.c
 * Note: decompiler flag: type propagation did not settle
 */
void datenotostr(uint32_t arg1,int arg2,uint8_t **arg3,char *arg4)

{
  size_t s1;
  int i2;
  uint8_t *****pppppu3;
  uint8_t *****pppppu4;
  char *pc5;
  uint8_t *****buf_50 [16];
  
  pppppu4 = (uint8_t *****)buf_50;
  pppppu3 = &d_08287a34;
  for (i2 = 0xc; pppppu4 = pppppu4 + 1, i2 != 0; i2 = i2 + -1) {
    *pppppu4 = *pppppu3;
    pppppu3 = pppppu3 + 1;
  }
  sprintf(arg4,"%i",arg3);
  if (((int)arg3 % 10 == 1) && (arg3 != (uint8_t **)0xb)) {
    pc5 = "st ";
    buf_50[0] = (uint8_t *****)((int)arg3 / 10);
  }
  else if (((int)arg3 % 10 == 2) && (arg3 != (uint8_t **)0xc)) {
    pc5 = "nd ";
    buf_50[0] = pppppu4;
  }
  else {
    pc5 = "th ";
    buf_50[0] = pppppu3;
  }
  strcat(arg4,pc5);
  if (arg2 - 1U < 0xc) {
    buf_50[0] = (uint8_t *****)arg3;
    strcat(arg4,(char *)buf_50[arg2]);
  }
  pc5 = " %i";
  s1 = strlen(arg4);
  sprintf(arg4 + s1,pc5,arg1);
  return;
}

