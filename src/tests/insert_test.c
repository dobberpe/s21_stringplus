#include "s21_string_test.h"

START_TEST(test_s21_insert_basic) {
  const char src[] = "Hello, World!";
  const char str[] = " Beautiful";
  size_t start_index = 6;
  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello, Beautiful World!");
  free(result);
}
END_TEST

START_TEST(test_s21_insert_at_beginning) {
  const char src[] = "World!";
  const char str[] = "Hello, ";
  size_t start_index = 0;
  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}
END_TEST

START_TEST(test_s21_insert_at_end) {
  const char src[] = "Hello, ";
  const char str[] = "World!";
  size_t start_index = s21_strlen(src);
  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_ne(result, NULL);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}
END_TEST

START_TEST(test_s21_insert_null_input) {
  const char *src = NULL;
  const char *str = "Insert";
  size_t start_index = 0;
  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

START_TEST(test_s21_insert_invalid_index) {
  const char src[] = "Hello, ";
  const char str[] = "World!";
  size_t start_index = 20;
  char *result = s21_insert(src, str, start_index);
  ck_assert_ptr_eq(result, NULL);
}
END_TEST

Suite *s21_insert_suite() {
  Suite *suite;
  TCase *tc_core;
  suite = suite_create("s21_insert");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_insert_basic);
  tcase_add_test(tc_core, test_s21_insert_at_beginning);
  tcase_add_test(tc_core, test_s21_insert_at_end);
  tcase_add_test(tc_core, test_s21_insert_null_input);
  tcase_add_test(tc_core, test_s21_insert_invalid_index);
  suite_add_tcase(suite, tc_core);
  return suite;
}
