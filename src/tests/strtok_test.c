#include "s21_string_test.h"

START_TEST(test_s21_strtok_basic) {
  char str[] = "Hello, World! How are you?";
  char str2[] = "Hello, World! How are you?";
  const char delim[] = " ,";

  char *result = s21_strtok(str, delim);
  char *result2 = strtok(str2, delim);
  while (result != NULL && result2 != NULL) {
    ck_assert_str_eq(result, result2);
    result = s21_strtok(NULL, delim);
    result2 = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(result, result2);
}
END_TEST

START_TEST(test_s21_strtok_multiple_delimiters) {
  char str[] = " , ,Hello, , World!,,";
  char str2[] = " , ,Hello, , World!,,";
  const char delim[] = " ,";
  char *result = s21_strtok(str, delim);
  char *result2 = strtok(str2, delim);
  while (result != NULL && result2 != NULL) {
    ck_assert_str_eq(result, result2);
    result = s21_strtok(NULL, delim);
    result2 = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(result, result2);
}
END_TEST

START_TEST(test_s21_strtok_empty_string) {
  char str[] = "";
  char str2[] = "";
  const char delim[] = " ,";
  char *result = s21_strtok(str, delim);
  char *result2 = strtok(str2, delim);
  while (result != NULL && result2 != NULL) {
    ck_assert_str_eq(result, result2);
    result = s21_strtok(NULL, delim);
    result2 = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(result, result2);
}
END_TEST

START_TEST(test_s21_strtok_not_found) {
  char str[] = "Hello, World! How are you?";
  char str2[] = "Hello, World! How are you?";
  const char delim[] = "G$^";
  char *result = s21_strtok(str, delim);
  char *result2 = strtok(str2, delim);
  while (result != NULL && result2 != NULL) {
    ck_assert_str_eq(result, result2);
    result = s21_strtok(NULL, delim);
    result2 = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(result, result2);
}
END_TEST

START_TEST(test_s21_strtok_empty_delims) {
  char str[] = "Hello, World! How are you?";
  char str2[] = "Hello, World! How are you?";
  const char delim[] = "";
  char *result = s21_strtok(str, delim);
  char *result2 = strtok(str2, delim);
  while (result != NULL && result2 != NULL) {
    ck_assert_str_eq(result, result2);
    result = s21_strtok(NULL, delim);
    result2 = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(result, result2);
}
END_TEST

START_TEST(test_s21_strtok_empty_both) {
  char *str = "";
  char *str2 = "";
  const char delim[] = "";
  char *result = s21_strtok(str, delim);
  char *result2 = strtok(str2, delim);
  while (result != NULL && result2 != NULL) {
    ck_assert_str_eq(result, result2);
    result = s21_strtok(NULL, delim);
    result2 = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(result, result2);
}
END_TEST

Suite *s21_strtok_suite() {
  Suite *suite;
  TCase *tc_core;
  suite = suite_create("s21_strtok");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_strtok_basic);
  tcase_add_test(tc_core, test_s21_strtok_multiple_delimiters);
  tcase_add_test(tc_core, test_s21_strtok_empty_string);
  tcase_add_test(tc_core, test_s21_strtok_not_found);
  tcase_add_test(tc_core, test_s21_strtok_empty_delims);
  tcase_add_test(tc_core, test_s21_strtok_empty_both);
  suite_add_tcase(suite, tc_core);
  return suite;
}
