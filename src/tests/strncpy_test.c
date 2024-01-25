#include "s21_string_test.h"

START_TEST(test_s21_strncpy_basic) {
  const char src[] = "Hello, World!";
  char dest[20];
  char dest2[20];
  size_t n = sizeof(dest);
  char *result = s21_strncpy(dest, src, n);
  ck_assert_ptr_eq(result, dest);
  ck_assert_str_eq(dest, strncpy(dest2, src, n));
}
END_TEST

START_TEST(test_s21_strncpy_partial) {
  const char src[] = "Hello, World!";
  char dest[20];
  char dest2[20];
  size_t n = 6;
  char *result = s21_strncpy(dest, src, n);
  ck_assert_ptr_eq(result, dest);
  dest[6] = 0;
  dest2[6] = 0;
  ck_assert_str_eq(dest, strncpy(dest2, src, n));
}
END_TEST

START_TEST(test_s21_strncpy_exact) {
  const char src[] = "Hello, World!";
  char dest[20];
  char dest2[20];
  size_t n = sizeof(src);
  char *result = s21_strncpy(dest, src, n);
  ck_assert_ptr_eq(result, dest);
  ck_assert_str_eq(dest, strncpy(dest2, src, n));
}
END_TEST

Suite *s21_strncpy_suite() {
  Suite *suite;
  TCase *tc_core;
  suite = suite_create("s21_strncpy");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_strncpy_basic);
  tcase_add_test(tc_core, test_s21_strncpy_partial);
  tcase_add_test(tc_core, test_s21_strncpy_exact);
  suite_add_tcase(suite, tc_core);
  return suite;
}
