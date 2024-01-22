#include "s21_string.h"
#include <stdio.h>

START_TEST(test_s21_strlen1)
{
    const char *empty_str = "";
    ck_assert_int_eq(s21_strlen(empty_str), 0);
}
END_TEST

START_TEST(test_s21_strlen2)
{
    const char *hello_world_str = "Hello, World!";
    ck_assert_int_eq(s21_strlen(hello_world_str), 13);
}
END_TEST

START_TEST(test_s21_strlen3)
{
    const char *numbers_str = "12345";
    ck_assert_int_eq(s21_strlen(numbers_str), 5);
}
END_TEST


START_TEST(test_s21_memchr_found)
{
    const char str[] = "Hello, World!";
    char c = 'o';
    size_t n = sizeof(str) - 1;  // Размер строки без учета завершающего нуля
    void *result = s21_memchr(str, c, n);
    
    ck_assert_ptr_ne(result, NULL);
    ck_assert_int_eq((const char *)result - str, 4);  // Ожидаем, что символ 'o' находится в позиции 4
}
END_TEST

START_TEST(test_s21_memchr_not_found)
{
    const char str[] = "Hello, World!";
    char c = 'z';
    size_t n = sizeof(str) - 1;
    void *result = s21_memchr(str, c, n);
    
    ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_s21_memchr_empty_string)
{
    const char str[] = "";
    char c = 'a';
    size_t n = 0;
    void *result = s21_memchr(str, c, n);
    
    ck_assert_ptr_eq(result, NULL);
}
END_TEST

Suite *s21_strlen_suite(void) {
    Suite *suite = suite_create("s21_strlen");
    TCase *tc_core = tcase_create("core");

    tcase_add_test(tc_core, test_s21_strlen1);
    tcase_add_test(tc_core, test_s21_strlen2);
    tcase_add_test(tc_core, test_s21_strlen3);
    suite_add_tcase(suite, tc_core);

    return suite;
}

Suite *s21_memchr_suite(void)
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

int main(void) {
    int number_failed;
    Suite *suite;
    SRunner *runner;

    suite = s21_strlen_suite();
    runner = srunner_create(suite);

    suite = s21_memchr_suite();

    srunner_add_suite(runner, suite);

    srunner_run_all(runner, CK_NORMAL);
    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}