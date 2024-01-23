#include "s21_string_test.h"

START_TEST(test_s21_memcpy_basic)
{
    const char src[] = "Hello, World!";
    char dest[20] = {0};
    char dest2[20] = {0};
    size_t n = sizeof(src) - 1;

    void *result = s21_memcpy(dest, src, n);

    ck_assert_ptr_eq(result, dest);
    ck_assert_str_eq(result, memcpy(dest2, src, n));
}
END_TEST

START_TEST(test_s21_memcpy_overlap)
{
    char buffer[20];
    char *src = buffer + 5;
    const char *expected = "World!";
    size_t n = strlen(expected) + 1;

    strcpy(buffer, "Hello, World!");

    void *result = s21_memcpy(buffer, src, n);

    ck_assert_ptr_eq(result, buffer);
    ck_assert_str_eq(buffer, memcpy(buffer, src, n));
}
END_TEST

Suite *s21_memcpy_suite()
{
    Suite *suite;
    TCase *tc_core;
    suite = suite_create("s21_memcpy");
    tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_s21_memcpy_basic);
    tcase_add_test(tc_core, test_s21_memcpy_overlap);
    suite_add_tcase(suite, tc_core);
    return suite;
}
