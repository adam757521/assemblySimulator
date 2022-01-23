#ifndef ASMVM_ERRORS_H
#define ASMVM_ERRORS_H

#include <stdio.h>

#define ErrorExit(message, ...) \
    fprintf(stderr, message, ##__VA_ARGS__); \
    exit(EXIT_FAILURE);

void Assert(int expression, const char *message, ...);
#endif