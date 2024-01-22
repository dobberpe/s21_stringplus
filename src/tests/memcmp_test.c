#include "s21_string_test.h"

START_TEST(test_s21_memcmp_equal)
{
    const char str1[] = "Hello, World!";
    const char str2[] = "Hello, World!";
    size_t n = sizeof(str1) - 1;
    ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(test_s21_memcmp_different)
{
    const char str1[] = "Hello, World!";
    const char str2[] = "Hallo, Welt!";
    size_t n = sizeof(str1) - 1;
    ck_assert_int_lt(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(test_s21_memcmp_partial)
{
    const char str1[] = "Hello, World!";
    const char str2[] = "Hello, Universe!";
    size_t n = 6;
    ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

Suite *s21_memcmp_suite()
{
    Suite *suite;
    TCase *tc_core;
    suite = suite_create("s21_memcmp");
    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_s21_memcmp_equal);
    tcase_add_test(tc_core, test_s21_memcmp_different);
    tcase_add_test(tc_core, test_s21_memcmp_partial);
    suite_add_tcase(suite, tc_core);

    return suite;
}
