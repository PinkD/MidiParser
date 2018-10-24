#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include "log.h"

void log_e(char *error) {
    char *now = time_now();
    fprintf(stderr, "%s:EEE: %s\n", now, error);
}

void log_w(char *warning) {
    char *now = time_now();
    fprintf(stdout, "%s:WWW: %s\n", now, warning);
}

void log_v(char *verbose) {
    char *now = time_now();
    fprintf(stdout, "%s:VVV: %s\n", now, verbose);

}

void log_d(char *debug) {
    char *now = time_now();
    fprintf(stdout, "%s:DDD: %s\n", now, debug);
}

char *time_now() {
    time_t now = time(NULL);
    strftime(result, TIME_STR_LEN, "%Y-%m-%d %H:%M:%S", localtime(&now));
    return result;
}
