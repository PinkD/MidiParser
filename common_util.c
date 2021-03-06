#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "common_util.h"

char *int_to_str(int value) {
    static char int_str[12];
    sprintf(int_str, "%d", value);
    return int_str;
}

char *float_to_str(float value) {
    static char float_str[6];
    sprintf(float_str, "%3.2f", value);
    return float_str;
}


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


uint32 swap_bit_32(uint32 raw) {
    return raw >> 24 & 0x000000ff | raw >> 8 & 0x0000ff00 | raw << 8 & 0x00ff0000 | raw << 24 & 0xff000000;
}


uint16 swap_bit_16(uint16 raw) {
    return (uint16) (raw << 8 & 0xff00 | raw >> 8 & 0x00ff);
}

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

uint32 read_vlq(FILE *f) {
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
    if (in < 0x80) {
        return in;
    }
    byte tmp[4];
    memset(tmp, 0x00, 4);
    for (int i = 3; i >= 0; i--) {
        if (in == 0) {
            break;
        }
        tmp[i] = (byte) (in & 0x7f | 0x80);
        in >>= 7;
    }
    return (tmp[0] << 24 & 0xff000000) | (tmp[1] << 16 & 0x00ff0000) | (tmp[2] << 8 & 0x0000ff00) | (tmp[3] & 0x7f);
}

void write_byte(FILE *f, byte in) {
    fputc(in, f);
}

void write_vlq(FILE *f, uint32 in) {
    in = int_to_vlq(in);
    if (in >> 24 & 0xff) {
        write_byte(f, (byte) (in >> 24 & 0xff));
    }
    if (in >> 16 & 0xff) {
        write_byte(f, (byte) (in >> 16 & 0xff));
    }
    if (in >> 8 & 0xff) {
        write_byte(f, (byte) (in >> 8 & 0xff));
    }
    write_byte(f, (byte) (in & 0xff));
}

void write_uint32(FILE *f, uint32 in) {
    write_byte(f, (byte) (in >> 24 & 0xff));
    write_byte(f, (byte) (in >> 16 & 0xff));
    write_byte(f, (byte) (in >> 8 & 0xff));
    write_byte(f, (byte) (in & 0xff));
}

void write_uint16(FILE *f, uint16 in) {
    write_byte(f, (byte) (in >> 8 & 0xff));
    write_byte(f, (byte) (in & 0xff));
}
