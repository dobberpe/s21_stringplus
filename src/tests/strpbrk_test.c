#include "s21_string_test.h"

START_TEST(test_s21_strpbrk_found)
{
    const char str1[] = "Hello, World!";
    const char str2[] = "aeiou";
    ck_assert_int_eq(s21_strpbrk(str1, str2) - str1, strpbrk(str1, str2) - str1);
}
END_TEST

START_TEST(test_s21_strpbrk_not_found)
{
    const char str1[] = "Hello, World!";
    const char str2[] = "xyz";
    ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_s21_strpbrk_empty_str1)
{
    const char str1[] = "";
    const char str2[] = "aeiou";
    ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

START_TEST(test_s21_strpbrk_empty_str2)
{
    const char str1[] = "Hello, World!";
    const char str2[] = "";
    ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
}
END_TEST

Suite *s21_strpbrk_suite()
{
    Suite *suite;
    TCase *tc_core;
    suite = suite_create("s21_strpbrk");
    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_s21_strpbrk_found);
    tcase_add_test(tc_core, test_s21_strpbrk_not_found);
    tcase_add_test(tc_core, test_s21_strpbrk_empty_str1);
    tcase_add_test(tc_core, test_s21_strpbrk_empty_str2);
    suite_add_tcase(suite, tc_core);
    return suite;
}
