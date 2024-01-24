#include "s21_string_test.h"

START_TEST(test_s21_trim_basic) {
  const char src[] = " !  Hello, World! @ @ ";
  const char trim_chars[] = " @!";
  char *result = s21_trim(src, trim_chars);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello, World");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_no_trim_chars) {
  const char src[] = "Hello, World!";
  const char trim_chars[] = "";
  char *result = s21_trim(src, trim_chars);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_empty_string) {
  const char src[] = "";
  const char trim_chars[] = " ";
  char *result = s21_trim(src, trim_chars);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(test_s21_trim_null_input) {
  const char *src = NULL;
  const char trim_chars[] = " ";
  char *result = s21_trim(src, trim_chars);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

Suite *s21_trim_suite() {
  Suite *suite;
  TCase *tc_core;
  suite = suite_create("s21_trim");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_trim_basic);
  tcase_add_test(tc_core, test_s21_trim_no_trim_chars);
  tcase_add_test(tc_core, test_s21_trim_empty_string);
  tcase_add_test(tc_core, test_s21_trim_null_input);
  suite_add_tcase(suite, tc_core);
  return suite;
}
