#ifndef MIDIPARSER_COMMON_UTIL_H
#define MIDIPARSER_COMMON_UTIL_H

#include "base_def.h"

/**
 * int to str
 * !!!WARNING!!! this function can not be used in synchronization place
 * @param value int
 * @return str
 */
char *int_to_str(int value);

/**
 * float to str
 * !!!WARNING!!! this function can not be used in synchronization place
 * @param value float
 * @return str, format is `%3.2f`
 */
char *float_to_str(float value);


/**
 *
 * @param raw 32 bit number, example: 0x12345678
 * @return example: 0x78563412
 */
uint32 swap_bit_32(uint32 raw);

/**
 *
 * @param raw 24 bit number, example: 0x00123456
 * @return example: 0x00563412
 */
uint32 swap_bit_24(uint32 raw);

/**
 *
 * @param raw 16 bit number, example: 0x1234
 * @return example: 0x3412
 */
uint16 swap_bit_16(uint16 raw);

/**
 * read byte
 * @param f file
 * @return byte
 */
byte read_byte(FILE *f);

/**
 * read vlq into uint32
 * @param f file to read
 * @return uint32
 */
uint32 read_vlq(FILE *f);

/**
 * write vlq
 * @param f file
 * @param in vlq to write
 */
void write_vlq(FILE *f, uint32 in);

/**
 * write a uint32 to file
 * @param f file
 * @param in uint32 to write
 */
void write_uint32(FILE *f, uint32 in);

/**
 * write a uint16 to file
 * @param f file
 * @param in uint16 t wirte
 */
void write_uint16(FILE *f, uint16 in);

/**
 * write a single byte to file
 * @param f file
 * @param in byte to write
 */
void write_byte(FILE *f, byte in);

uint32 int_to_vlq(uint32 in);

void printBits(uint32 num);


#endif
