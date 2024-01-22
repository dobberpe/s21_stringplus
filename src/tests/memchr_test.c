#include "s21_string_test.h"

START_TEST(test_s21_memchr_found)
{
    const char str[] = "Hello, World!";
    char c = 'o';
    size_t n = sizeof(str) - 1;
    ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
    ck_assert_int_eq((const char *)s21_memchr(str, c, n) - str, (const char *)memchr(str, c, n) - str);
}
END_TEST

START_TEST(test_s21_memchr_not_found)
{
    const char str[] = "Hello, World!";
    char c = 'z';
    size_t n = sizeof(str) - 1;
    ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(test_s21_memchr_empty_string)
{
    const char str[] = "";
    char c = 'a';
    size_t n = 0;
    ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}

Suite *s21_memchr_suite()
{
    Suite *suite;
    TCase *tc_core;
    suite = suite_create("s21_memchr");
    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_s21_memchr_found);
    tcase_add_test(tc_core, test_s21_memchr_not_found);
    tcase_add_test(tc_core, test_s21_memchr_empty_string);
    suite_add_tcase(suite, tc_core);
    return suite;
}