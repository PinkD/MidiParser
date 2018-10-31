#ifndef COMMON_LOG_H
#define COMMON_LOG_H

const static size_t TIME_STR_LEN = 20;
static char result[20];

extern const static int DEBUG;
extern const static int VERBOSE;

extern int DEBUG_LEVEL;


//NOTE: log functions are not thread safe

/**
 * get time string like `2018-12-31 12:12:12` , len is 20(include string end)
 * @return time now string, need to be free
 */
char *time_now();

/**
 * log message to stderr, key word is `EEE`
 * @param error message to log
 */
void log_e(char *error);

/**
 * log message to stdout, key word is `WWW`
 * @param warning message to log
 */
void log_w(char *warning);

/**
 * log message to stdout, key word is `VVV`
 * @param verbose message to log
 */
void log_v(char *verbose);

/**
 * log message to stdout, key word is `DDD`
 * @param debug message to log
 */
void log_d(char *debug);

#endif
