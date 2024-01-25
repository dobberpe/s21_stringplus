#include "s21_string_test.h"

START_TEST(test_s21_to_upper_basic) {
  const char str[] = "Hello, World!";
  char *result = s21_to_upper(str);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "HELLO, WORLD!");
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_empty_string) {
  const char str[] = "";
  char *result = s21_to_upper(str);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_s21_to_upper_null_input) {
  const char *str = NULL;
  char *result = s21_to_upper(str);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

Suite *s21_to_upper_suite() {
  Suite *suite;
  TCase *tc_core;
  suite = suite_create("s21_to_upper");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_to_upper_basic);
  tcase_add_test(tc_core, test_s21_to_upper_empty_string);
  tcase_add_test(tc_core, test_s21_to_upper_null_input);
  suite_add_tcase(suite, tc_core);
  return suite;
}