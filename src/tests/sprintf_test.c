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
    s21_sprintf(s21_res, "%.3LE", a);
    sprintf(io_res, "%.3LE", a);
    ck_assert_str_eq(s21_res, io_res);
}
END_TEST


START_TEST(test_s21_sprintf_integer)
{
    int value = 42;
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    sprintf(expected_output, "Integer: %d", value);
    s21_sprintf(buffer, "Integer: %d", value);

    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_s21_sprintf_float)
{
    double value = 3.14;
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    sprintf(expected_output, "Float: %.2f", value);
    s21_sprintf(buffer, "Float: %.2f", value);

    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_s21_sprintf_string)
{
    const char *value = "TestString";
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    sprintf(expected_output, "String: %s", value);
    s21_sprintf(buffer, "String: %s", value);

    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_s21_sprintf_integer_flags)
{
    int value = 42;
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Флаги: ширина 8, выравнивание по левому краю
    sprintf(expected_output, "Integer: %-8d", value);
    s21_sprintf(buffer, "Integer: %-8d", value);

    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_s21_sprintf_float_flags)
{
    double value = 3.14159265359;
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Флаги: ширина 10, точность 2
    sprintf(expected_output, "Float: %10.2f", value);
    s21_sprintf(buffer, "Float: %10.2f", value);

    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_s21_sprintf_string_flags)
{
    const char *value = "TestString";
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Флаги: ширина 15, выравнивание по правому краю
    sprintf(expected_output, "String: %15s", value);
    s21_sprintf(buffer, "String: %15s", value);

    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_s21_sprintf_multiple_flags)
{
    int intValue = 42;
    double floatValue = 3.14159265359;
    const char *stringValue = "TestString";
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Комбинация флагов для разных типов данных
    sprintf(expected_output, "Integer: %+d, Float: %010.4f, String: %-10s", intValue, floatValue, stringValue);
    s21_sprintf(buffer, "Integer: %+d, Float: %010.4f, String: %-10s", intValue, floatValue, stringValue);

    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_s21_sprintf_complex)
{
    int intValue = 123456;
    double floatValue = 9876.54321;
    const char *stringValue = "TestString";
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Комплексное форматирование
    sprintf(expected_output, "Int: %+010d, Float: %.3e, String: %-20s", intValue, floatValue, stringValue);
    s21_sprintf(buffer, "Int: %+010d, Float: %.3e, String: %-20s", intValue, floatValue, stringValue);

    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_s21_sprintf_padding)
{
    int intValue = 42;
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Пустые символы перед числом
    sprintf(expected_output, "   Integer: %d", intValue);
    s21_sprintf(buffer, "   Integer: %d", intValue);

    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_s21_sprintf_alignment)
{
    int intValue = 123;
    double floatValue = 456.789;
    const char *stringValue = "Align";
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Выравнивание по центру
    sprintf(expected_output, "Int: %*d, Float: %*.2f, String: %*s", 8, intValue, 10, floatValue, 15, stringValue);
    s21_sprintf(buffer, "Int: %*d, Float: %*.2f, String: %*s", 8, intValue, 10, floatValue, 15, stringValue);

    ck_assert_str_eq(buffer, expected_output);
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
  tcase_add_test(tc_core, test_s21_sprintf_alignment);
  tcase_add_test(tc_core, test_s21_sprintf_padding);
  tcase_add_test(tc_core, test_s21_sprintf_complex);
  tcase_add_test(tc_core, test_s21_sprintf_multiple_flags);
  tcase_add_test(tc_core, test_s21_sprintf_float_flags);
  tcase_add_test(tc_core, test_s21_sprintf_integer_flags);
  tcase_add_test(tc_core, test_s21_sprintf_string);
  tcase_add_test(tc_core, test_s21_sprintf_float);
  tcase_add_test(tc_core, test_s21_sprintf_integer);
  
  suite_add_tcase(suite, tc_core);
  return suite;
}

