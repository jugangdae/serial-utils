/*  
 * crc8.c
 * 
 * Computes a 8-bit CRC 
 * http://www.rajivchakravorty.com/source-code/uncertainty/multimedia-sim/html/crc8_8c-source.html
 */

#include <stdio.h>
#include <stdint.h>

#define GP  0x107                       /* x^8 + x^2 + x + 1 */
#define DI  0x07

static uint8_t crc8_table[256];         /* 8-bit table */
static int made_table=0;

static void init_crc8()
{
  int i,j;
  uint8_t crc;
  
    if (!made_table) {
        for (i=0; i<256; i++) {
            crc = i;
            for (j=0; j<8; j++)
                crc = (crc << 1) ^ ((crc & 0x80) ? DI : 0);
            crc8_table[i] = crc & 0xFF;
            printf("table[%d] = %d (0x%X)\n", i, crc, crc);
        }
        made_table=1;
    }
}

void crc8(uint8_t *crc, uint8_t m)
     /*
      * For a byte array whose accumulated crc value is stored in *crc, computes
      * resultant crc obtained by appending m to the byte array
      */
{
    if (!made_table)
        init_crc8();
    *crc = crc8_table[(*crc) ^ m];
    *crc &= 0xFF;
}

void main(){
    uint8_t crc8buf;
    crc8(&crc8buf,0x5c);
    printf("\nCRC: %x\n",crc8buf);
}