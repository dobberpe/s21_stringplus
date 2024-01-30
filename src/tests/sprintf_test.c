#include "s21_string_test.h"

START_TEST(test_s21_sprintf_d2) {
    int src = 4;
    char res[20];
    s21_sprintf(res, "%d%d", 4, 5);
    ck_assert_str_eq(res, "45");
}
END_TEST

START_TEST(test_s21_sprintf_d) {
    int src = 4;
    char res[20];
    s21_sprintf(res, "%d", src);
    ck_assert_str_eq(res, "4");
}
END_TEST

START_TEST(test_s21_sprintf_f) {
    int src = 4;
    char res[1000];
    char res2[1000];
    // double a = pow(2, 1000);
    double a = 3.14;
    s21_sprintf(res, "%f", a);
    sprintf(res2, "%.51f", a);
    ck_assert_str_eq(res, res2);
}
END_TEST

START_TEST(test_s21_sprintf_f2) {
    int src = 4;
    char res[1000];
    char res2[1000];
    double a = pow(2, 1000);
    // double a = 3.14;
    s21_sprintf(res, "%f", a);
    sprintf(res2, "%.1f", a);
    ck_assert_str_eq(res, res2);
}
END_TEST

START_TEST(test_s21_sprintf_f3) {
    int src = 4;
    char res[1010];
    char res2[1010];
    double a = pow(2, -1000);
    // double a = 3.14;
    s21_sprintf(res, "%f", a);
    sprintf(res2, "%.1000f", a);
    ck_assert_str_eq(res, res2);
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
  suite_add_tcase(suite, tc_core);
  return suite;
}
