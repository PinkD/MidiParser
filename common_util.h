#ifndef MIDIPARSER_COMMON_UTIL_H
#define MIDIPARSER_COMMON_UTIL_H

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

#endif
