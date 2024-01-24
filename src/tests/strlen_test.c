#include "s21_string_test.h"

START_TEST(test_s21_strlen_empty) {
  const char *empty_str = "";
  ck_assert_int_eq(s21_strlen(empty_str), strlen(empty_str));
}
END_TEST

START_TEST(test_s21_strlen_letters) {
  const char *hello_world_str = "Hello, World!";
  ck_assert_int_eq(s21_strlen(hello_world_str), strlen(hello_world_str));
}
END_TEST

START_TEST(test_s21_strlen_numbers) {
  const char *numbers_str = "12345";
  ck_assert_int_eq(s21_strlen(numbers_str), strlen(numbers_str));
}
END_TEST

Suite *s21_strlen_suite() {
  Suite *suite = suite_create("s21_strlen");
  TCase *tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_strlen_empty);
  tcase_add_test(tc_core, test_s21_strlen_letters);
  tcase_add_test(tc_core, test_s21_strlen_numbers);
  suite_add_tcase(suite, tc_core);
  return suite;
}