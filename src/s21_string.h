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
	double full;
	unsigned long long bits;
} f_representation;

typedef union {
	long double full;
	unsigned short bits[5];
} fl_representation;

typedef struct {
	bool left_alignment;
	bool positive_sign;
	bool space_instead_of_sign;
	bool oct_hex_notation;
	bool fill_with_nulls;
	int width;
	int precision;
	char length;
} print_modifiers;

typedef struct {
	bool assignment;
	char length;
} scan_modifiers;

typedef struct {
	char c;
	wchar_t lc;
	char* s;
	wchar_t* ls;
	int d;
	short hd;
	long ld;
	unsigned u;
	unsigned short hu;
	unsigned long lu;
	double f;
	long double lf;
} scan_result;

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
//void init_str(char* str);
void reset_mods(print_modifiers *format_modifiers);
int process_format(const char *format, int i, char *str, va_list *params, print_modifiers *format_modifiers);
char* process_specifier(char specifier, const int len, va_list *params, print_modifiers *format_modifiers);
char* get_c(va_list* params, char length);
char* doxtoa(long long d, const int radix, const bool uppercase);
int doxlen(long long d, const int radix);
char* etoa(char* f_str, print_modifiers format_modifiers, char specifier);
char* clear_nulls(char* str);
char* get_f(va_list* params, char length);
char* edge_case(bool inf, bool negative);
char *ftoa(const f_representation* f);
int extract_exp(unsigned long long bits);
char *calculate_int_part(char *integer, const int e, const unsigned long long bits, unsigned long long mask);
char* augment_int(char* integer, int p, char** power_of_2, int* prev_p);
char *calculate_frac_part(char *fraction, int e, const unsigned long long bits, unsigned long long mask);
char* augment_frac(char* fraction, int e, char** power_of_5, int* prev_p);
char* join_frac_to_int(char* integer, char* fraction, bool negative);
char *lftoa(const fl_representation* f);
int extract_exp_long(const unsigned short bits);
char* calculate_int_part_long(char *integer, const int e, const unsigned short *bits, unsigned short mask);
char* calculate_frac_part_long(char *fraction, int e, const unsigned short *bits, unsigned short mask);
char* raise_power_of_2(char *str, int n);
char* raise_power_of_5(char *str, int n);
char* add_width(char *str, int num, char value, bool right_alignment);
char* stradd(char *l_str, char *r_str);
char* get_s(va_list* params, char length);
int point_position(char *str);
char* get_p(unsigned long address);
char *apply_format(char *str, print_modifiers format_modifiers, char specifier);
char *double_round(char *str, print_modifiers format_modifiers, char specifier);
char *set_precision(char *str, print_modifiers format_modifiers, char specifier);
char *set_hex_notation(char *str, print_modifiers format_modifiers, char specifier, char is_zero);
char *set_width(char *str, print_modifiers format_modifiers, char specifier);

int s21_sscanf(const char *str, const char *format, ...);
void reset_scan_mods(scan_modifiers* format_modifiers);
int process_scan_format(const char* format, int i, const char* str, int* j, va_list *params, scan_modifiers *format_modifiers);
int process_scan_specifier(char specifier, const char* str, int len, va_list *params, scan_modifiers *format_modifiers);
int skip_spaces(char* str);
int skip_dox(char* str, char radix);
int skip_feg(char* str);
int skip_s(char* str);
void assign(scan_result* res, va_list* params, char specifier, char length);

#endif