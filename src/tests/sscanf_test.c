#include "s21_string_test.h"

// Тестовый случай для s21_sscanf с использованием целочисленных знаковых
// спецификаторов
START_TEST(test_s21_sscanf_integer) {
  const char *input_str = "123";
  int value_my = -1;
  int value_original = -1;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%d", &value_original);
  int my_result = s21_sscanf(input_str, "%d", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием краевого случая: пустая
// строка
START_TEST(test_s21_sscanf_empty_string_edge_case) {
  const char *input_str = "";
  int value_my = -1;
  int value_original = -1;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%d", &value_original);
  int my_result = s21_sscanf(input_str, "%d", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений (должно быть не изменено)
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием нескольких значений за раз
START_TEST(test_s21_sscanf_multiple_values) {
  const char *input_str = "123 456";
  int value1_my = -1, value2_my = -1;
  int value1_original = -1, value2_original = -1;

  // Сравнение с оригинальной функцией sscanf
  int original_result =
      sscanf(input_str, "%d %d", &value1_original, &value2_original);
  int my_result = s21_sscanf(input_str, "%d %d", &value1_my, &value2_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value1_my, value1_original);
  ck_assert_int_eq(value2_my, value2_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %c
START_TEST(test_s21_sscanf_char) {
  const char *input_str = "A";
  char value_my = '\0';
  char value_original = '\0';

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%c", &value_original);
  int my_result = s21_sscanf(input_str, "%c", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %c и краевого
// случая: пустая строка
START_TEST(test_s21_sscanf_char_empty_string) {
  const char *input_str = "";
  char value_my = 'A';        // Начальное значение
  char value_original = 'A';  // Начальное значение

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%c", &value_original);
  int my_result = s21_sscanf(input_str, "%c", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений (должно быть не изменено)
  ck_assert_int_eq(value_my, 'A');
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %c и краевого
// случая: пробельные символы
START_TEST(test_s21_sscanf_char_whitespace) {
  const char *input_str = " \t\n";  // пробел, табуляция, перенос строки
  char value_my = '\0';
  char value_original = '\0';

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%c", &value_original);
  int my_result = s21_sscanf(input_str, "%c", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %c и
// считыванием нескольких значений
START_TEST(test_s21_sscanf_multiple_chars) {
  const char *input_str = "ABC";
  char value1_my = '\0', value2_my = '\0', value3_my = '\0';
  char value1_original = '\0', value2_original = '\0', value3_original = '\0';

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%c %c %c", &value1_original,
                               &value2_original, &value3_original);
  int my_result =
      s21_sscanf(input_str, "%c %c %c", &value1_my, &value2_my, &value3_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value1_my, value1_original);
  ck_assert_int_eq(value2_my, value2_original);
  ck_assert_int_eq(value3_my, value3_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %c и символов
// табуляции, пробелов, переносов строк
START_TEST(test_s21_sscanf_char_no_delim) {
  const char *input_str = "A B\nC";
  char value1_my = '\0', value2_my = '\0', value3_my = '\0';
  char value1_original = '\0', value2_original = '\0', value3_original = '\0';

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%c%c%c", &value1_original,
                               &value2_original, &value3_original);
  int my_result =
      s21_sscanf(input_str, "%c%c%c", &value1_my, &value2_my, &value3_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value1_my, value1_original);
  ck_assert_int_eq(value2_my, value2_original);
  ck_assert_int_eq(value3_my, value3_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %c и
// игнорированием пробельных символов
START_TEST(test_s21_sscanf_char_ignore_whitespace) {
  const char *input_str = " A \tB\nC";
  char value1_my = '\0', value2_my = '\0', value3_my = '\0';
  char value1_original = '\0', value2_original = '\0', value3_original = '\0';

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, " %c %c %c", &value1_original,
                               &value2_original, &value3_original);
  int my_result =
      s21_sscanf(input_str, " %c %c %c", &value1_my, &value2_my, &value3_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value1_my, value1_original);
  ck_assert_int_eq(value2_my, value2_original);
  ck_assert_int_eq(value3_my, value3_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %i в десятичной
// форме
START_TEST(test_s21_sscanf_integer_decimal) {
  const char *input_str = "123";
  int value_my = -1;
  int value_original = -1;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%i", &value_original);
  int my_result = s21_sscanf(input_str, "%i", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %i в
// восьмеричной форме
START_TEST(test_s21_sscanf_integer_octal) {
  const char *input_str = "0123";
  int value_my = -1;
  int value_original = -1;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%i", &value_original);
  int my_result = s21_sscanf(input_str, "%i", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %i в
// шестнадцатеричной форме
START_TEST(test_s21_sscanf_integer_hexadecimal) {
  const char *input_str = "0x7B";
  int value_my = -1;
  int value_original = -1;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%i", &value_original);
  int my_result = s21_sscanf(input_str, "%i", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %i с
// минимальным значением INT
START_TEST(test_s21_sscanf_integer_min_value) {
  const char *input_str = "-2147483648";  // Минимальное значение для int
  int value_my = 0;
  int value_original = 0;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%i", &value_original);
  int my_result = s21_sscanf(input_str, "%i", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %i с
// максимальным значением INT
START_TEST(test_s21_sscanf_integer_max_value) {
  const char *input_str = "2147483647";  // Максимальное значение для int
  int value_my = 0;
  int value_original = 0;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%i", &value_original);
  int my_result = s21_sscanf(input_str, "%i", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %i с
// минимальным значением восьмеричного числа
START_TEST(test_s21_sscanf_integer_min_octal) {
  const char *input_str = "-020000000000";  // Минимальное значение для int в
                                            // восьмеричной системе счисления
  int value_my = 0;
  int value_original = 0;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%i", &value_original);
  int my_result = s21_sscanf(input_str, "%i", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %i с
// максимальным значением восьмеричного числа
START_TEST(test_s21_sscanf_integer_max_octal) {
  const char *input_str = "017777777777";  // Максимальное значение для int в
                                           // восьмеричной системе счисления
  int value_my = 0;
  int value_original = 0;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%i", &value_original);
  int my_result = s21_sscanf(input_str, "%i", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %i с
// минимальным значением шестнадцатеричного числа
START_TEST(test_s21_sscanf_integer_min_hexadecimal) {
  const char *input_str = "-0x80000000";  // Минимальное значение для int в
                                          // шестнадцатеричной системе счисления
  int value_my = 0;
  int value_original = 0;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%i", &value_original);
  int my_result = s21_sscanf(input_str, "%i", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %i с
// максимальным значением шестнадцатеричного числа
START_TEST(test_s21_sscanf_integer_max_hexadecimal) {
  const char *input_str = "0x7FFFFFFF";  // Максимальное значение для int в
                                         // шестнадцатеричной системе счисления
  int value_my = 0;
  int value_original = 0;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%i", &value_original);
  int my_result = s21_sscanf(input_str, "%i", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %i с значением
// 0 в десятичной системе счисления
START_TEST(test_s21_sscanf_decimal_zero_value) {
  const char *input_str = "0";  // Значение 0 в десятичной системе счисления
  int value_my = 1;  // Искусственно установим начальное значение, чтобы
                     // проверить, что оно действительно изменится
  int value_original = 1;  // Искусственно установим начальное значение, чтобы
                           // проверить, что оно действительно изменится

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%i", &value_original);
  int my_result = s21_sscanf(input_str, "%i", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %o с значением
// 0 в восьмеричной системе счисления
START_TEST(test_s21_sscanf_octal_zero_value) {
  const char *input_str = "00";  // Значение 0 в восьмеричной системе счисления
  int value_my = 1;  // Искусственно установим начальное значение, чтобы
                     // проверить, что оно действительно изменится
  int value_original = 1;  // Искусственно установим начальное значение, чтобы
                           // проверить, что оно действительно изменится

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%i", &value_original);
  int my_result = s21_sscanf(input_str, "%i", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %x с значением
// 0 в шестнадцатеричной системе счисления
START_TEST(test_s21_sscanf_hexadecimal_zero_value) {
  const char *input_str =
      "0x0";  // Значение 0 в шестнадцатеричной системе счисления
  int value_my = 1;  // Искусственно установим начальное значение, чтобы
                     // проверить, что оно действительно изменится
  int value_original = 1;  // Искусственно установим начальное значение, чтобы
                           // проверить, что оно действительно изменится

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%i", &value_original);
  int my_result = s21_sscanf(input_str, "%i", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %e для
// десятичного числа с плавающей точкой
START_TEST(test_s21_sscanf_decimal_float_exponential) {
  const char *input_str =
      "-123.456e3";  // Десятичное число с плавающей точкой в научной нотации
  float value_my = 0.0f;
  float value_original = 0.0f;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%e", &value_original);
  int my_result = s21_sscanf(input_str, "%e", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_float_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %f для
// десятичного числа с плавающей точкой
START_TEST(test_s21_sscanf_decimal_float) {
  const char *input_str = "-0.4156";  // Десятичное число с плавающей точкой
  float value_my = 0.0f;
  float value_original = 0.0f;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%f", &value_original);
  int my_result = s21_sscanf(input_str, "%f", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_float_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %E для
// десятичного числа с плавающей точкой в научной нотации
START_TEST(test_s21_sscanf_decimal_float_exponential_uppercase) {
  const char *input_str =
      "-99.956E-6";  // Десятичное число с плавающей точкой в научной нотации
  float value_my = 0.0f;
  float value_original = 0.0f;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%E", &value_original);
  int my_result = s21_sscanf(input_str, "%E", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_float_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %g для
// десятичного числа с плавающей точкой
START_TEST(test_s21_sscanf_decimal_float_general) {
  const char *input_str = "-0.00001";  // Десятичное число с плавающей точкой
  float value_my = 0.0f;
  float value_original = 0.0f;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%g", &value_original);
  int my_result = s21_sscanf(input_str, "%g", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_float_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %G для
// десятичного числа с плавающей точкой
START_TEST(test_s21_sscanf_decimal_float_general_uppercase) {
  const char *input_str = "-2e-1";  // Десятичное число с плавающей точкой
  float value_my = 0.0f;
  float value_original = 0.0f;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%G", &value_original);
  int my_result = s21_sscanf(input_str, "%G", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_float_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %s для строки
// без пробелов
START_TEST(test_s21_sscanf_string_no_whitespace) {
  const char *input_str = "HelloWorld";  // Строка без пробелов
  char buffer_my[20] = "";
  char buffer_original[20] = "";

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%19s", buffer_original);
  int my_result = s21_sscanf(input_str, "%19s", buffer_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_str_eq(buffer_my, buffer_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %s для строки с
// пробелами
START_TEST(test_s21_sscanf_string_with_whitespace) {
  const char *input_str = "Hello World";  // Строка с пробелами
  char buffer_my[20] = "";
  char buffer_original[20] = "";

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%19s", buffer_original);
  int my_result = s21_sscanf(input_str, "%19s", buffer_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_str_eq(buffer_my, buffer_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %s с шириной
// поля
START_TEST(test_s21_sscanf_string_with_width) {
  const char *input_str = "HelloWorld123";  // Строка и числа без пробелов
  char buffer_my[10] = "";
  char buffer_original[10] = "";

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%9s", buffer_original);
  int my_result = s21_sscanf(input_str, "%9s", buffer_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_str_eq(buffer_my, buffer_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %s для пустой
// строки
START_TEST(test_s21_sscanf_empty_string) {
  const char *input_str = "";    // Пустая строка
  char buffer_my[20] = "Hello";  // Исходное значение буфера
  char buffer_original[20] = "Hello";  // Исходное значение буфера

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%19s", buffer_original);
  int my_result = s21_sscanf(input_str, "%19s", buffer_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_str_eq(buffer_my, buffer_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %s для строки с
// одним символом
START_TEST(test_s21_sscanf_single_char_string) {
  const char *input_str = "X";  // Строка с одним символом
  char buffer_my[20] = "Hello";  // Исходное значение буфера
  char buffer_original[20] = "Hello";  // Исходное значение буфера

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%19s", buffer_original);
  int my_result = s21_sscanf(input_str, "%19s", buffer_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_str_eq(buffer_my, buffer_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %s и
// предстоящими пробелами
START_TEST(test_s21_sscanf_string_with_leading_spaces) {
  const char *input_str = "    HelloWorld";  // Строка с предстоящими пробелами
  char buffer_my[20] = "";  // Исходное значение буфера
  char buffer_original[20] = "";  // Исходное значение буфера

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%19s", buffer_original);
  int my_result = s21_sscanf(input_str, "%19s", buffer_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_str_eq(buffer_my, buffer_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %s и
// предстоящими пробелами с шириной поля
START_TEST(test_s21_sscanf_string_with_leading_spaces_and_width) {
  const char *input_str = "    HelloWorld";  // Строка с предстоящими пробелами
  char buffer_my[10] = "";        // Буфер с шириной поля
  char buffer_original[10] = "";  // Буфер с шириной поля

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%9s", buffer_original);
  int my_result = s21_sscanf(input_str, "%9s", buffer_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_str_eq(buffer_my, buffer_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %u для
// беззнакового целого числа
START_TEST(test_s21_sscanf_unsigned_integer) {
  const char *input_str = "12345";  // Беззнаковое целое число
  unsigned int value_my = 0;
  unsigned int value_original = 0;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%u", &value_original);
  int my_result = s21_sscanf(input_str, "%u", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_uint_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %x для
// шестнадцатеричного целого числа
START_TEST(test_s21_sscanf_hexadecimal_integer) {
  const char *input_str = "01a2b";  // Шестнадцатеричное целое число
  unsigned int value_my = 0;
  unsigned int value_original = 0;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%x", &value_original);
  int my_result = s21_sscanf(input_str, "%x", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_uint_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %X для
// шестнадцатеричного целого числа (верхний регистр)
START_TEST(test_s21_sscanf_hexadecimal_integer_uppercase) {
  const char *input_str =
      "0x1A2B";  // Шестнадцатеричное целое число (верхний регистр)
  unsigned int value_my = 0;
  unsigned int value_original = 0;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%X", &value_original);
  int my_result = s21_sscanf(input_str, "%X", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_uint_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %o для
// восьмеричного целого числа
START_TEST(test_s21_sscanf_octal_integer) {
  const char *input_str = "765";  // Восьмеричное целое число
  unsigned int value_my = 0;
  unsigned int value_original = 0;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%o", &value_original);
  int my_result = s21_sscanf(input_str, "%o", &value_my);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_uint_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием флага h для целочисленного
// значения
START_TEST(test_s21_sscanf_short_integer) {
  short value_my = 0;
  short value_original = 0;

  const char *input_str = "12345";

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%hd", &value_original);
  int my_result = s21_sscanf(input_str, "%hd", &value_my);

  // Сравнение результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием флага l для целочисленного
// значения
START_TEST(test_s21_sscanf_long_integer) {
  long value_my = 0;
  long value_original = 0;

  const char *input_str = "123456789012345";

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%ld", &value_original);
  int my_result = s21_sscanf(input_str, "%ld", &value_my);

  // Сравнение результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием флага l для значения типа
// double
START_TEST(test_s21_sscanf_double) {
  double value_my = 0.0;
  double value_original = 0.0;

  const char *input_str = "4.3291991e+18";

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%lf", &value_original);
  int my_result = s21_sscanf(input_str, "%lf", &value_my);

  // Сравнение результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_double_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием флага L для значения типа
// long double
START_TEST(test_s21_sscanf_long_double) {
  long double value_my = 0.0;
  long double value_original = 0.0;

  const char *input_str = "-3e-29";

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%Lf", &value_original);
  int my_result = s21_sscanf(input_str, "%Lf", &value_my);

  // Сравнение результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_ldouble_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием флага * для игнорирования
// считанных значений
START_TEST(test_s21_sscanf_ignore_values) {
  int value1_my, value2_my = 0;
  int value1_original, value2_original = 0;

  const char *input_str = "123 456 -3";

  // Сравнение с оригинальной функцией sscanf, но с использованием *
  int original_result =
      sscanf(input_str, "%d %*d %d", &value1_original, &value2_original);
  int my_result = s21_sscanf(input_str, "%d %*d %d", &value1_my, &value2_my);

  // Сравнение результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений (игнорирование второго числа)
  ck_assert_int_eq(value1_my, value1_original);
  ck_assert_int_eq(value2_my, value2_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %%
START_TEST(test_s21_sscanf_percent_percent) {
  const char *input_str = "Hello %% World";

  // Переменные для хранения считанных значений
  char buffer_my[20];
  char buffer_original[20];

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "Hello %%%19s", buffer_original);
  int my_result = s21_sscanf(input_str, "Hello %%%19s", buffer_my);

  // Сравнение результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_str_eq(buffer_my, buffer_original);
}

// Тестовый случай для s21_sscanf с использованием целочисленных знаковых
// спецификаторов
START_TEST(test_s21_sscanf_integer_with_error) {
  const char *input_str = "123 418d 312";
  int value_my1 = -1;
  int value_my2 = -1;
  int value_my3 = -1;
  int value_original1 = -1;
  int value_original2 = -1;
  int value_original3 = -1;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%d%d%d", &value_original1,
                               &value_original2, &value_original3);
  int my_result =
      s21_sscanf(input_str, "%d%d%d", &value_my1, &value_my2, &value_my3);

  // Проверка результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my1, value_original1);
  ck_assert_int_eq(value_my2, value_original2);
  ck_assert_int_eq(value_my3, value_original3);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %n
START_TEST(test_s21_sscanf_percent_n) {
  const char *input_str = "Hello World";
  int chars_read_my = 0;
  int chars_read_original = 0;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "Hello%n", &chars_read_original);
  int my_result = s21_sscanf(input_str, "Hello%n", &chars_read_my);

  // Сравнение результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значения %n
  ck_assert_int_eq(chars_read_my, chars_read_original);
}

START_TEST(test_s21_sscanf_percent_n2) {
  int n1_my = 1, n1_original = 5;

  char s1_my[20] = {'\0'};
  char s2_my[20] = {'\0'};
  char s3_my[20] = {'\0'};
  char s1_original[20] = {'\0'};
  char s2_original[20] = {'\0'};
  char s3_original[20] = {'\0'};

  const char *input_str =
      "cbobErobM fl? asdfasdflkasdf asdfasdf asdfasdf 88888";

  int original_result = sscanf(input_str, "%19s %19s %n %19s", s1_original,
                               s2_original, &n1_original, s3_original);
  int my_result =
      s21_sscanf(input_str, "%19s %19s %n %19s", s1_my, s2_my, &n1_my, s3_my);

  ck_assert_int_eq(original_result, my_result);

  ck_assert_int_eq(n1_original, n1_my);
  ck_assert_str_eq(s1_original, s1_my);
  ck_assert_str_eq(s2_original, s2_my);
  ck_assert_str_eq(s3_original, s3_my);
}
END_TEST

// Тестовый случай для s21_sscanf с использованием спецификатора %n
START_TEST(test_s21_sscanf_percent_n_with_string) {
  const char *input_str = "Hello World";
  char buffer_my[20];
  char buffer_original[20];
  int chars_read_my = 0;
  int chars_read_original = 0;

  // Сравнение с оригинальной функцией sscanf
  int original_result =
      sscanf(input_str, "%19s%n", buffer_original, &chars_read_original);
  int my_result = s21_sscanf(input_str, "%19s%n", buffer_my, &chars_read_my);

  // Сравнение результатов
  ck_assert_int_eq(my_result, original_result);
  // Сравнение строк
  ck_assert_str_eq(buffer_my, buffer_original);
  // Проверка значения %n
  ck_assert_int_eq(chars_read_my, chars_read_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %n
START_TEST(test_s21_sscanf_percent_n_with_int) {
  const char *input_str = "   123 qwe914";
  int n_my1 = 0;
  int n_my2 = 0;
  int n_my3 = 0;
  int n_orig1 = 0;
  int n_orig2 = 0;
  int n_orig3 = 0;
  int val_my1 = 0;
  int val_my2 = 0;
  int val_orig1 = 0;
  int val_orig2 = 0;

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%n%d%n qwe%d%n", &n_orig1,
                               &val_orig1, &n_orig2, &val_orig2, &n_orig3);
  int my_result = s21_sscanf(input_str, "%n%d%n qwe%d%n", &n_my1, &val_my1,
                             &n_my2, &val_my2, &n_my3);

  // Сравнение результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значения %n
  ck_assert_int_eq(n_my1, n_orig1);
  ck_assert_int_eq(n_my2, n_orig2);
  ck_assert_int_eq(n_my3, n_orig3);
  // Проверка значений %d
  ck_assert_int_eq(val_my1, val_orig1);
  ck_assert_int_eq(val_my2, val_orig2);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %5f
START_TEST(test_s21_sscanf_fixed_width_float) {
  float value_my;
  float value_original;

  const char *input_str = "123.456";

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%5f", &value_original);
  int my_result = s21_sscanf(input_str, "%5f", &value_my);

  // Сравнение результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_float_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %3d
START_TEST(test_s21_sscanf_fixed_width_integer) {
  int value_my;
  int value_original;

  const char *input_str = "123456";

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%3d", &value_original);
  int my_result = s21_sscanf(input_str, "%3d", &value_my);

  // Сравнение результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификаторов %3d%d
START_TEST(test_s21_sscanf_multiple_specifiers) {
  int value1_my, value2_my;
  int value1_original, value2_original;

  const char *input_str = "123456";

  // Сравнение с оригинальной функцией sscanf
  int original_result =
      sscanf(input_str, "%3d%d", &value1_original, &value2_original);
  int my_result = s21_sscanf(input_str, "%3d%d", &value1_my, &value2_my);

  // Сравнение результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value1_my, value1_original);
  ck_assert_int_eq(value2_my, value2_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %5x (ширина без
// префикса)
START_TEST(test_s21_sscanf_fixed_width_hex) {
  unsigned int value_my;
  unsigned int value_original;

  const char *input_str = "1a2b3c";

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%5x", &value_original);
  int my_result = s21_sscanf(input_str, "%5x", &value_my);

  // Сравнение результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %#5x (ширина с
// префиксом)
START_TEST(test_s21_sscanf_fixed_width_hex_with_prefix) {
  unsigned int value_my;
  unsigned int value_original;

  const char *input_str = "0x1a2b3c";

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%5x", &value_original);
  int my_result = s21_sscanf(input_str, "%5x", &value_my);

  // Сравнение результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %5o (ширина без
// префикса)
START_TEST(test_s21_sscanf_fixed_width_octal) {
  unsigned int value_my;
  unsigned int value_original;

  const char *input_str = "123456";

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%5o", &value_original);
  int my_result = s21_sscanf(input_str, "%5o", &value_my);

  // Сравнение результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %#5o (ширина с
// префиксом)
START_TEST(test_s21_sscanf_fixed_width_octal_with_prefix) {
  unsigned int value_my;
  unsigned int value_original;

  const char *input_str = "0123456";

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%5o", &value_original);
  int my_result = s21_sscanf(input_str, "%5o", &value_my);

  // Сравнение результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для sscanf с использованием спецификатора %p
START_TEST(test_sscanf_pointer) {
  void *value_my;
  void *value_original;

  const char *input_str = "0x7ffeefbf2a10";

  // Сравнение с оригинальной функцией sscanf
  int original_result = sscanf(input_str, "%p", &value_original);
  int my_result = s21_sscanf(input_str, "%p", &value_my);

  // Сравнение результатов
  ck_assert_int_eq(my_result, original_result);
  // Проверка значений
  ck_assert_ptr_eq(value_my, value_original);
}

Suite *s21_sscanf_suite() {
  Suite *suite;
  TCase *tc_core;
  suite = suite_create("s21_sscanf");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_s21_sscanf_integer);
  tcase_add_test(tc_core, test_s21_sscanf_empty_string_edge_case);
  tcase_add_test(tc_core, test_s21_sscanf_multiple_values);
  tcase_add_test(tc_core, test_s21_sscanf_char);
  tcase_add_test(tc_core, test_s21_sscanf_char_empty_string);
  tcase_add_test(tc_core, test_s21_sscanf_char_whitespace);
  tcase_add_test(tc_core, test_s21_sscanf_multiple_chars);
  tcase_add_test(tc_core, test_s21_sscanf_char_no_delim);
  tcase_add_test(tc_core, test_s21_sscanf_char_ignore_whitespace);
  tcase_add_test(tc_core, test_s21_sscanf_integer_decimal);
  tcase_add_test(tc_core, test_s21_sscanf_integer_octal);
  tcase_add_test(tc_core, test_s21_sscanf_integer_hexadecimal);
  tcase_add_test(tc_core, test_s21_sscanf_integer_min_value);
  tcase_add_test(tc_core, test_s21_sscanf_integer_max_value);
  tcase_add_test(tc_core, test_s21_sscanf_integer_min_octal);
  tcase_add_test(tc_core, test_s21_sscanf_integer_max_octal);
  tcase_add_test(tc_core, test_s21_sscanf_integer_min_hexadecimal);
  tcase_add_test(tc_core, test_s21_sscanf_decimal_zero_value);
  tcase_add_test(tc_core, test_s21_sscanf_octal_zero_value);
  tcase_add_test(tc_core, test_s21_sscanf_hexadecimal_zero_value);
  tcase_add_test(tc_core, test_s21_sscanf_decimal_float_exponential);
  tcase_add_test(tc_core, test_s21_sscanf_decimal_float);
  tcase_add_test(tc_core, test_s21_sscanf_decimal_float_exponential_uppercase);
  tcase_add_test(tc_core, test_s21_sscanf_decimal_float_general);
  tcase_add_test(tc_core, test_s21_sscanf_decimal_float_general_uppercase);
  tcase_add_test(tc_core, test_s21_sscanf_string_no_whitespace);
  tcase_add_test(tc_core, test_s21_sscanf_string_with_whitespace);
  tcase_add_test(tc_core, test_s21_sscanf_string_with_width);
  tcase_add_test(tc_core, test_s21_sscanf_empty_string);
  tcase_add_test(tc_core, test_s21_sscanf_single_char_string);
  tcase_add_test(tc_core, test_s21_sscanf_string_with_leading_spaces);
  tcase_add_test(tc_core, test_s21_sscanf_string_with_leading_spaces_and_width);
  tcase_add_test(tc_core, test_s21_sscanf_unsigned_integer);
  tcase_add_test(tc_core, test_s21_sscanf_hexadecimal_integer);
  tcase_add_test(tc_core, test_s21_sscanf_hexadecimal_integer_uppercase);
  tcase_add_test(tc_core, test_s21_sscanf_octal_integer);
  tcase_add_test(tc_core, test_s21_sscanf_short_integer);
  tcase_add_test(tc_core, test_s21_sscanf_long_integer);
  tcase_add_test(tc_core, test_s21_sscanf_double);
  tcase_add_test(tc_core, test_s21_sscanf_long_double);
  tcase_add_test(tc_core, test_s21_sscanf_ignore_values);
  tcase_add_test(tc_core, test_s21_sscanf_integer_max_hexadecimal);
  tcase_add_test(tc_core, test_s21_sscanf_percent_percent);
  tcase_add_test(tc_core, test_s21_sscanf_integer_with_error);
  tcase_add_test(tc_core, test_s21_sscanf_percent_n);
  tcase_add_test(tc_core, test_s21_sscanf_percent_n2);
  tcase_add_test(tc_core, test_s21_sscanf_percent_n_with_string);
  tcase_add_test(tc_core, test_s21_sscanf_percent_n_with_int);
  tcase_add_test(tc_core, test_s21_sscanf_fixed_width_float);
  tcase_add_test(tc_core, test_s21_sscanf_fixed_width_integer);
  tcase_add_test(tc_core, test_s21_sscanf_multiple_specifiers);
  tcase_add_test(tc_core, test_s21_sscanf_fixed_width_hex);
  tcase_add_test(tc_core, test_s21_sscanf_fixed_width_hex_with_prefix);
  tcase_add_test(tc_core, test_s21_sscanf_fixed_width_octal);
  tcase_add_test(tc_core, test_s21_sscanf_fixed_width_octal_with_prefix);
  tcase_add_test(tc_core, test_sscanf_pointer);
  suite_add_tcase(suite, tc_core);
  return suite;
}