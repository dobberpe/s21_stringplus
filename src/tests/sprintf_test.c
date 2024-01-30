#include "s21_string_test.h"

START_TEST(test_s21_sprintf_d) {
    char s21_res[20];
    char io_res[20];
    s21_sprintf(s21_res, "%d", 4);
    sprintf(io_res, "%d", 4);
    ck_assert_str_eq(s21_res, io_res);
}
END_TEST

START_TEST(test_s21_sprintf_d2) {
    char s21_res[20];
    char io_res[20];
    s21_sprintf(s21_res, "%d%d", 4, 5);
    sprintf(io_res, "%d%d", 4, 5);
    ck_assert_str_eq(s21_res, io_res);
}
END_TEST

START_TEST(test_s21_sprintf_f) {
    char s21_res[1000];
    char io_res[1000];
    double a = 3.14;
    s21_sprintf(s21_res, "%f", a);
    sprintf(io_res, "%f", a);
    ck_assert_str_eq(s21_res, io_res);
}
END_TEST

START_TEST(test_s21_sprintf_f2) {
    char s21_res[1000];
    char io_res[1000];
    double a = pow(2, 1000);
    s21_sprintf(s21_res, "%f", a);
    sprintf(io_res, "%f", a);
    ck_assert_str_eq(s21_res, io_res);
}
END_TEST

START_TEST(test_s21_sprintf_f3) {
    char s21_res[1000];
    char io_res[1000];
    double a = pow(2, -1000);
    s21_sprintf(s21_res, "%f", a);
    sprintf(io_res, "%f", a);
    ck_assert_str_eq(s21_res, io_res);
}
END_TEST

START_TEST(test_s21_sprintf_E_precision) {
    char s21_res[100];
    char io_res[100];
    double a = -0.000999999;
    s21_sprintf(s21_res, "%.3E", a);
    sprintf(io_res, "%.3E", a);
    ck_assert_str_eq(s21_res, io_res);
}
END_TEST

Suite *s21_sprintf_suite() {
  Suite *suite;
  TCase *tc_core;
  suite = suite_create("s21_sprintf");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_sprintf_d);
  tcase_add_test(tc_core, test_s21_sprintf_d2);
  tcase_add_test(tc_core, test_s21_sprintf_f);
  tcase_add_test(tc_core, test_s21_sprintf_f2);
  tcase_add_test(tc_core, test_s21_sprintf_f3);
  tcase_add_test(tc_core, test_s21_sprintf_E_precision);
  suite_add_tcase(suite, tc_core);
  return suite;
}
