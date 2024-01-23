#include "s21_string_test.h"

START_TEST(test_s21_strstr_found)
{
    const char haystack[] = "Hello, World!";
    const char needle[] = "World";
    ck_assert_int_eq(s21_strstr(haystack, needle) - haystack, strstr(haystack, needle) - haystack);
}
END_TEST

START_TEST(test_s21_strstr_not_found)
{
    const char haystack[] = "Hello, World!";
    const char needle[] = "Universe";
    ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_empty_needle)
{
    const char haystack[] = "Hello, World!";
    const char needle[] = "";
    ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_s21_strstr_empty_haystack)
{
    const char haystack[] = "";
    const char needle[] = "Hello";
    ck_assert_ptr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

Suite *s21_strstr_suite()
{
    Suite *suite;
    TCase *tc_core;
    suite = suite_create("s21_strstr");
    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_s21_strstr_found);
    tcase_add_test(tc_core, test_s21_strstr_not_found);
    tcase_add_test(tc_core, test_s21_strstr_empty_needle);
    tcase_add_test(tc_core, test_s21_strstr_empty_haystack);
    suite_add_tcase(suite, tc_core);
    return suite;
}
