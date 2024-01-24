#include "s21_string_test.h"

int main(void) {
  int number_failed;
  Suite *suite = NULL;
  SRunner *runner = srunner_create(suite);

  Suite *suits_list[] = {s21_strlen_suite(),   s21_memchr_suite(),
                         s21_memcmp_suite(),   s21_memcpy_suite(),
                         s21_memset_suite(),   s21_strncat_suite(),
                         s21_strchr_suite(),   s21_strncmp_suite(),
                         s21_strncpy_suite(),  s21_strcspn_suite(),
                         s21_strpbrk_suite(),  s21_strrchr_suite(),
                         s21_strstr_suite(),   s21_strtok_suite(),
                         s21_strerror_suite(), NULL};

  for (Suite **current = suits_list; *current != NULL; current++)
    srunner_add_suite(runner, *current);

  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}