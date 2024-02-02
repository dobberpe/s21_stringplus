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
//   tcase_add_test(tc_core, test_s21_sprintf_f);
  tcase_add_test(tc_core, test_s21_sprintf_f2);
  tcase_add_test(tc_core, test_s21_sprintf_f3);
//   tcase_add_test(tc_core, test_s21_sprintf_E_precision);
  suite_add_tcase(suite, tc_core);
  return suite;
}


// void test_all_falgs_sprintf(char spec, ...) {
//     char *str2 = (char *)malloc(2000);
//     char *format;
//     for (int i = 0; i < 32; i++) {
//         char *str = (char *)malloc((strlen(src) + 1) * sizeof(char));
//         mod.left_alignment = i & 1;
//         mod.positive_sign = (i >> 1) & 1;
//         mod.space_instead_of_sign = (i >> 2) & 1;
//         mod.oct_hex_notation = (i >> 3) & 1;
//         mod.fill_with_nulls = (i >> 4) & 1;
//         format = format_maker(&mod, spec, '\0');
//         s21_memcpy(str, src, strlen(src) + 1);
//         str = apply_format(str, mod, spec);
//         sprintf(str2, format, src2);

//         // DEBUG
//         str = (char *)realloc(str, (s21_strlen(str) + s21_strlen(format) + 1) * sizeof(char));
//         str = strcat(str, format);
//         str2 = (char *)realloc(str2, (s21_strlen(str2) + s21_strlen(format) + 1) * sizeof(char));
//         str2 = strcat(str2, format);
//         // END DEBUG

//         ck_assert_str_eq(str, str2);
//         free(str);
//         free(format);
//     }
//     free(str2);
// }