#include "s21_string_test.h"

START_TEST(test_s21_strerror_known_error) {
  int errornum = 1;
  ck_assert_str_eq(s21_strerror(errornum), strerror(errornum));
}
END_TEST

START_TEST(test_s21_strerror_known_error2) {
  int errornum = 15;
  ck_assert_str_eq(s21_strerror(errornum), strerror(errornum));
}
END_TEST

START_TEST(test_s21_strerror_unknown_error) {
  int errornum = -1;
  ck_assert_str_eq(s21_strerror(errornum), strerror(errornum));
}
END_TEST

Suite *s21_strerror_suite() {
  Suite *suite;
  TCase *tc_core;
  suite = suite_create("s21_strerror");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_strerror_known_error);
  tcase_add_test(tc_core, test_s21_strerror_known_error2);
  tcase_add_test(tc_core, test_s21_strerror_unknown_error);
  suite_add_tcase(suite, tc_core);
  return suite;
}
