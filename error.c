 /*
-------------------------------------------------------------
    error.c
    Solution to IJC-DU1, example B)
    Date: 14.3.2024
    Author: Václav Matyáš, FIT
    Compiler: gcc 11.4.0
    Description: General error/warning functions.
                 Working like printf.
-------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void warning(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Warning: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
}

void error_exit(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(EXIT_FAILURE);
}
