#include "s21_string_test.h"

START_TEST(test_s21_strncat_basic) {
  char dest[20] = "Hello, ";
  char dest2[20] = "Hello, ";
  const char src[] = "World!";
  size_t n = sizeof(dest) - strlen(dest) - 1;
  char *result = s21_strncat(dest, src, n);
  ck_assert_ptr_eq(result, dest);
  ck_assert_str_eq(dest, strncat(dest2, src, n));
}
END_TEST

START_TEST(test_s21_strncat_partial) {
  char dest[20] = "Hello, ";
  char dest2[20] = "Hello, ";
  const char src[] = "World!";
  size_t n = 3;
  char *result = s21_strncat(dest, src, n);
  ck_assert_ptr_eq(result, dest);
  ck_assert_str_eq(dest, strncat(dest2, src, n));
}
END_TEST

START_TEST(test_s21_strncat_exact) {
  char dest[20] = "Hello, ";
  char dest2[20] = "Hello, ";
  const char src[] = "World!";
  size_t n = strlen(src) + 2;

  char *result = s21_strncat(dest, src, n);

  ck_assert_ptr_eq(result, dest);
  ck_assert_str_eq(dest, strncat(dest2, src, n));
}
END_TEST

Suite *s21_strncat_suite() {
  Suite *suite;
  TCase *tc_core;
  suite = suite_create("s21_strncat");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_strncat_basic);
  tcase_add_test(tc_core, test_s21_strncat_partial);
  tcase_add_test(tc_core, test_s21_strncat_exact);
  suite_add_tcase(suite, tc_core);
  return suite;
}
