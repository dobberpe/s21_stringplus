#include "s21_string_test.h"

START_TEST(test_s21_strchr_found)
{
    const char str[] = "Hello, World!";
    int c = 'o';
    char *result = s21_strchr(str, c);
    ck_assert_ptr_ne(result, NULL);
    ck_assert_int_eq(result - str, strchr(str, c) - str);
}
END_TEST

START_TEST(test_s21_strchr_not_found)
{
    const char str[] = "Hello, World!";
    int c = 'z';
    char *result = s21_strchr(str, c);
    ck_assert_ptr_eq(result, strchr(str, c));
}
END_TEST

START_TEST(test_s21_strchr_empty_string)
{
    const char str[] = "";
    int c = 'a';
    char *result = s21_strchr(str, c);
    ck_assert_ptr_eq(result, strchr(str, c));
}
END_TEST

Suite *s21_strchr_suite(void)
{
    Suite *suite;
    TCase *tc_core;
    suite = suite_create("s21_strchr");
    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_s21_strchr_found);
    tcase_add_test(tc_core, test_s21_strchr_not_found);
    tcase_add_test(tc_core, test_s21_strchr_empty_string);
    suite_add_tcase(suite, tc_core);
    return suite;
}

