#ifndef TEST_H
#define TEST_H

#define MAX_BUFFER_SIZE 512

#include <check.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>


#include "../s21_string.h"

char *format_maker(print_modifiers *mod, char ch, char len);
void test_all_falgs_d(print_modifiers mod, char *src, int src2, char spec);
void test_all_falgs_double(print_modifiers mod, char *src, double src2, char spec);
void test_all_falgs_string(print_modifiers mod, char *src, char *src2, char spec);

Suite *s21_strlen_suite();
Suite *s21_memchr_suite();
Suite *s21_memcmp_suite();
Suite *s21_memcpy_suite();
Suite *s21_memset_suite();
Suite *s21_strncat_suite();
Suite *s21_strchr_suite();
Suite *s21_strncmp_suite();
Suite *s21_strncpy_suite();
Suite *s21_strcspn_suite();
Suite *s21_strpbrk_suite();
Suite *s21_strrchr_suite();
Suite *s21_strstr_suite();
Suite *s21_strtok_suite();
Suite *s21_strerror_suite();
Suite *s21_to_upper_suite();
Suite *s21_to_lower_suite();
Suite *s21_insert_suite();
Suite *s21_trim_suite();
Suite *s21_sprintf_suite();
Suite *s21_apply_format_suite();
Suite *s21_sscanf_suite();

#endif