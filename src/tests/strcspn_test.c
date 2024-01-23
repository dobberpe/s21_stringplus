#include "s21_string_test.h"

START_TEST(test_s21_strcspn_basic)
{
    const char str1[] = "Hello, World!";
    const char str2[] = ",!";
    ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_s21_strcspn_not_found)
{
    const char str1[] = "Hello, World!";
    const char str2[] = "xyz";

    ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_s21_strcspn_empty_str2)
{
    const char str1[] = "Hello, World!";
    const char str2[] = "";
    ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

START_TEST(test_s21_strcspn_empty_str1)
{
    const char str1[] = "";
    const char str2[] = "xyx";
    ck_assert_uint_eq(s21_strcspn(str1, str2), strcspn(str1, str2));
}
END_TEST

Suite *s21_strcspn_suite()
{
    Suite *suite;
    TCase *tc_core;
    suite = suite_create("s21_strcspn");
    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_s21_strcspn_basic);
    tcase_add_test(tc_core, test_s21_strcspn_not_found);
    tcase_add_test(tc_core, test_s21_strcspn_empty_str2);
    tcase_add_test(tc_core, test_s21_strcspn_empty_str1);
    suite_add_tcase(suite, tc_core);
    return suite;
}