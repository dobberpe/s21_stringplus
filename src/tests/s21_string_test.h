#ifndef TEST_H
#define TEST_H

#include "../s21_string.h"

#include <check.h>
#include <string.h>
#include <stdio.h>

Suite *s21_strlen_suite();
Suite *s21_memchr_suite();
Suite *s21_memcmp_suite();
Suite *s21_memcpy_suite();
Suite *s21_memset_suite();

#endif