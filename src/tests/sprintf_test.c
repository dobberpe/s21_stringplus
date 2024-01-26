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
    char res[100];
    char res2[100];
    float a = 3.14;
    s21_sprintf(res, "%f", a);
    sprintf(res2, "%.22f", a);
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
  suite_add_tcase(suite, tc_core);
  return suite;
}
