#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef union {
    float full;
    unsigned bits;
} f_representation;

int s21_sprintf(char *str, const char *format, ...);
void specifier(const char *format, int i, char *str, int *j, va_list *params);
char* process_dox(int d, const int radix, const bool uppercase);
int doxlen(int d, const int radix);
char *doxtoa(int d, const int radix, const bool uppercase)
void print_exp(char *str, int *j, float e);
void print_float(char *str, int *j, float f);
void print_str(char *str, int *j, char *s);
void print_address(char *str, int *j, void *p);
void print_n(int j, int *n);

#endif