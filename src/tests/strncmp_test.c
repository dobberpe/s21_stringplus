#include "s21_string_test.h"

START_TEST(test_s21_strncmp_equal) {
  const char str1[] = "Hello, World!";
  const char str2[] = "Hello, World!";
  size_t n = strlen(str1);
  ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n));
}
END_TEST

START_TEST(test_s21_strncmp_less) {
  const char str1[] = "Hello,";
  const char str2[] = "Hello, Universe!";
  size_t n = strlen(str2);
  ck_assert_int_lt(strncmp(str1, str2, n), 0);
  ck_assert_int_lt(s21_strncmp(str1, str2, n), 0);
}
END_TEST

START_TEST(test_s21_strncmp_greater) {
  const char str1[] = "Hello, World!";
  const char str2[] = "Hello, Galaxy!";
  size_t n = strlen(str2);
  ck_assert_int_gt(strncmp(str1, str2, n), 0);
  ck_assert_int_gt(s21_strncmp(str1, str2, n), 0);
}
END_TEST

START_TEST(test_s21_strncmp_partial) {
  const char str1[] = "Hello, World!";
  const char str2[] = "Hello, Universe!";
  size_t n = 6;
  ck_assert_int_eq(s21_strncmp(str1, str2, n), strncmp(str1, str2, n));
}
END_TEST

Suite *s21_strncmp_suite() {
  Suite *suite;
  TCase *tc_core;
  suite = suite_create("s21_strncmp");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_strncmp_equal);
  tcase_add_test(tc_core, test_s21_strncmp_less);
  tcase_add_test(tc_core, test_s21_strncmp_greater);
  tcase_add_test(tc_core, test_s21_strncmp_partial);
  suite_add_tcase(suite, tc_core);
  return suite;
}
