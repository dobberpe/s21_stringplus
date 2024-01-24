#include "s21_string_test.h"

START_TEST(test_s21_strrchr_found) {
  const char str[] = "Hello, World!";
  int c = 'o';
  ck_assert_int_eq(s21_strrchr(str, c) - str, strrchr(str, c) - str);
}
END_TEST

START_TEST(test_s21_strrchr_not_found) {
  const char str[] = "Hello, World!";
  int c = 'z';
  ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

START_TEST(test_s21_strrchr_empty_string) {
  const char str[] = "";
  int c = 'a';
  ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));
}
END_TEST

Suite *s21_strrchr_suite() {
  Suite *suite;
  TCase *tc_core;
  suite = suite_create("s21_strrchr");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_strrchr_found);
  tcase_add_test(tc_core, test_s21_strrchr_not_found);
  tcase_add_test(tc_core, test_s21_strrchr_empty_string);
  suite_add_tcase(suite, tc_core);
  return suite;
}
