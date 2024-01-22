#include "s21_string_test.h"


int main(void) {
    int number_failed;
    Suite *suite = NULL;
    SRunner *runner = srunner_create(suite);

    Suite *suits_list[] = {s21_strlen_suite(), s21_memchr_suite(), s21_memcmp_suite(), s21_memcpy_suite(),
    s21_memset_suite(), NULL};
    
    for (Suite **current = suits_list; *current != NULL; current++) srunner_add_suite(runner, *current);

    srunner_run_all(runner, CK_ENV);
    number_failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
    return 0;
}