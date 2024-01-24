#include "s21_string_test.h"

START_TEST(test_s21_memset_basic) {
  char buffer[20];
  char buffer2[20];
  size_t n = sizeof(buffer);
  int c = 'A';

  void *result = s21_memset(buffer, c, n);

  ck_assert_ptr_eq(result, buffer);
  ck_assert_mem_eq(buffer, memset(buffer2, c, n), n);
}
END_TEST

START_TEST(test_s21_memset_partial) {
  char buffer[20];
  char buffer2[20];
  size_t n = 10;
  int c = 'B';

  void *result = s21_memset(buffer, c, n);

  ck_assert_ptr_eq(result, buffer);
  ck_assert_mem_eq(buffer, memset(buffer2, c, n), n);
}
END_TEST

Suite *s21_memset_suite() {
  Suite *suite;
  TCase *tc_core;
  suite = suite_create("s21_memset");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_memset_basic);
  tcase_add_test(tc_core, test_s21_memset_partial);
  suite_add_tcase(suite, tc_core);
  return suite;
}