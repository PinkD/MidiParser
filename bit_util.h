#ifndef BITUTIL_LIBRARY_H
#define BITUTIL_LIBRARY_H

#include "base_def.h"

uint32 swap_bit_32(uint32 raw);

uint32 swap_bit_24(uint32 raw);

uint16 swap_bit_16(uint16 raw);

byte read_byte(FILE *f);

uint32 read_vlq(FILE *f);

void write_vlq(FILE *f, uint32 in);

uint32 int_to_vlq(uint32 in);

void printBits(uint32 num);


#endif