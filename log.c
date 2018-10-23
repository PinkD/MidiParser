#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include "log.h"

void log_e(char *error) {
    char *now = time_now();
    fprintf(stderr, "%s:EEE: %s\n", now, error);
    free(now);
}

void log_w(char *warning) {
    char *now = time_now();
    fprintf(stdout, "%s:WWW: %s\n", now, warning);
    free(now);
}

void log_v(char *verbose) {
    char *now = time_now();
    fprintf(stdout, "%s:VVV: %s\n", now, verbose);
    free(now);

}

void log_d(char *debug) {
    char *now = time_now();
    fprintf(stdout, "%s:DDD: %s\n", now, debug);
    free(now);
}

char *time_now() {
    size_t len = 20;
    char *result = malloc(sizeof(char) * len);
    time_t now = time(NULL);
    strftime(result, len, "%Y-%m-%d %H:%M:%S", localtime(&now));
    return result;
}
