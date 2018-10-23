
#include <stdlib.h>
#include <tiff.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include "bit_util.h"


void printBits(uint32 num) {
    int counter = 0;
    for (int bit = 0; bit < (sizeof(int) * 8); bit++) {
        printf("%i", (num & 0x80000000) >> 31);
        counter++;
        if (counter == 8) {
            counter -= 8;
            printf(" ");
        }
        num = num << 1;
    }
    printf("\n");
}


/**
 *
 * @param raw 32 bit number, example: 0x12345678
 * @return example: 0x78563412
 */
uint32 swap_bit_32(uint32 raw) {
    return raw >> 24 & 0x000000ff | raw >> 8 & 0x0000ff00 | raw << 8 & 0x00ff0000 | raw << 24 & 0xff000000;
}


/**
 *
 * @param raw 16 bit number, example: 0x1234
 * @return example: 0x3412
 */
uint16 swap_bit_16(uint16 raw) {
    return (uint16) (raw << 8 & 0xff00 | raw >> 8 & 0x00ff);
}

/**
 *
 * @param raw 24 bit number, example: 0x00123456
 * @return example: 0x00563412
 */
uint32 swap_bit_24(uint32 raw) {
    raw = raw & 0x00ffffff;//just in case
    return (raw << 16 & 0x00ff0000) | (raw & 0x0000ff00) | (raw >> 16 & 0x000000ff);
}

byte read_byte(FILE *f) {
    byte tmp;
    if (fread(&tmp, 1, 1, f) != 1) {//just in case
        fprintf(stderr, "EOF\n");
        exit(-1);
    }
    return tmp;
}

uint32 read_vlq(FILE *f) {//DONE
    unsigned char bit;
    uint32 result = 0;
    while ((bit = read_byte(f)) & 0x80) {
        result += bit & 0x7f;
        result <<= 7;
    }
    result += bit;
    return result;
}


uint32 int_to_vlq(uint32 in) {
//    in = swap_bit_32(in);
    uint32 result = 0;
    if (in < 0x80) {
        return in;
    }

//    printBits(result);
//    printBits(in);
//    printf("---------\n");
    while (in > 0x7f) {
        result += in & 0x7f | 0x80;
        result = result << 8;
        in = in >> 7;
//        printBits(result);
//        printBits(in);
//        printf("---------\n");
    }

    result += in & 0x7f | 0x80;
    if (result > 0xffff) {//TODO: byte based
        return swap_bit_32(result & 0x7fffffff);
    } else {
        return swap_bit_16((uint16) (result & 0x7fff));
    }
//    return swap_bit_32(result & 0x7fffffff);
}
