#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

typedef union {
	double full;
	unsigned long long bits;
} f_representation;


void *s21_memchr(const void *str, int c, size_t n);
int s21_memcmp(const void *str1, const void *str2, size_t n);
void *s21_memcpy(void *dest, const void *src, size_t n);
void *s21_memset(void *str, int c, size_t n);
char *s21_strncat(char *dest, const char *src, size_t n);
char *s21_strchr(const char *str, int c);
int s21_strncmp(const char *str1, const char *str2, size_t n);
char *s21_strncpy(char *dest, const char *src, size_t n);
size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
size_t s21_strlen(const char *str);
char *s21_strpbrk(const char *str1, const char *str2);
char *s21_strrchr(const char *str, int c);
char *s21_strstr(const char *haystack, const char *needle);
char *s21_strtok(char *str, const char *delim);
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
void *s21_insert(const char *src, const char *str, size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);

int s21_sprintf(char *str, const char *format, ...);
void specifier(const char *format, int i, char *str, int *j, va_list *params);
char *doxtoa(long long d, const int radix, const bool uppercase);
int doxlen(long long d, const int radix);
int etoa(char* f_str);
char *ftoa(double f);
int extract_exp(unsigned long long bits);
char* add_rank(char *str, int num, char value);
char *addnulles(char *str, int i, int j);
char* stradd(char *l_str, char *r_str, bool fraction);
void get_num_of_printed(int j, int *n);


#endif