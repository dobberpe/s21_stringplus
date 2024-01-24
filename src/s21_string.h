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
char *doxtoa(int d, const int radix, const bool uppercase);
int doxlen(int d, const int radix);
int etoa(char* f_str);
char *ftoa(float f);
int extract_exp(unsigned bits);
char* add_rank(char *str, int num, char value);
char *addnulles(char *str, int i, int j);
char* stradd(char *l_str, char *r_str, bool fraction);
void get_num_of_printed(int j, int *n);


#endif