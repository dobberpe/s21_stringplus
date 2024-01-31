#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <wchar.h>
#include <stdio.h>
#include <string.h>

#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))

typedef union {
	long double full;
	unsigned short bits[5];
} f_representation;

typedef struct {
	bool left_alignment;
	bool positive_sign;
	bool space_instead_of_sign;
	bool oct_hex_notation;
	bool fill_with_nulls;
	int width;
	int precision;
	char length;
} modifiers;


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
void init_str(char* str);
void reset_mods(modifiers *format_modifiers);
int process_format(const char *format, int i, char *str, const int j, va_list *params, modifiers *format_modifiers);
char *process_specifier(char specifier, const int len, va_list *params, modifiers *format_modifiers);
char *doxtoa(long long d, const int radix, const bool uppercase);
int doxlen(long long d, const int radix);
char *etoa(char* f_str, modifiers *format_modifiers, char specifier);
char* clear_nulls(char* str);
char *ftoa(long double f);
int extract_exp(const unsigned short bits);
char* edge_case(unsigned short* bits, bool negative);
char *calculate_int_part(char *integer, const int e, const unsigned short *bits, unsigned short mask);
char* raise_power_of_2(char *str, int n);
char *calculate_frac_part(char *fraction, int e, const unsigned short *bits, unsigned short mask);
char* raise_power_of_5(char *str, int n);
char* add_width(char *str, int num, char value, bool right_alignment);
char* stradd(char *l_str, char *r_str);
int point_position(char *str);
char *apply_format(char *str, modifiers *format_modifiers, char specifier);


#endif