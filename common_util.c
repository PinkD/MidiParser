#include <stdio.h>
#include "common_util.h"

/**
 * int to str
 * !!!WARNING!!! this function can not be used in synchronization place
 * @param value int
 * @return str
 */
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
