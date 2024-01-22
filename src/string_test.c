#include "s21_string.h"
#include <stdio.h>

START_TEST(strlen_test) {
    char *test_phrase = "qwe123";
    ck_assert_uint_eq(s21_strlen(test_phrase), strlen(test_phrase));
}
END_TEST

Suite *test_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Add"); // имя вашего тестового набора
    tc_core = tcase_create("Core"); // имя вашего тестового случая

    // Добавление теста в тестовый набор
    tcase_add_test(tc_core, strlen_test);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = test_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}