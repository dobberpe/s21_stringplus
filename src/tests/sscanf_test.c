#include "s21_string_test.h"

// Тестовый случай для s21_sscanf с использованием целочисленных знаковых спецификаторов
START_TEST(test_s21_sscanf_integer)
{
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

// Тестовый случай для s21_sscanf с использованием краевого случая: пустая строка
START_TEST(test_s21_sscanf_empty_string)
{
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

// Тестовый случай для s21_sscanf с использованием краевого случая: нулевой формат
START_TEST(test_s21_sscanf_empty_format)
{
    const char *input_str = "123";
    int value_my = -1;
    int value_original = -1;

    // Сравнение с оригинальной функцией sscanf
    int original_result = sscanf(input_str, "", &value_original);
    int my_result = s21_sscanf(input_str, "", &value_my);

    // Проверка результатов
    ck_assert_int_eq(my_result, original_result);
    // Проверка значений (должно быть не изменено)
    ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием нескольких значений за раз
START_TEST(test_s21_sscanf_multiple_values)
{
    const char *input_str = "123 456";
    int value1_my = -1, value2_my = -1;
    int value1_original = -1, value2_original = -1;

    // Сравнение с оригинальной функцией sscanf
    int original_result = sscanf(input_str, "%d %d", &value1_original, &value2_original);
    int my_result = s21_sscanf(input_str, "%d %d", &value1_my, &value2_my);

    // Проверка результатов
    ck_assert_int_eq(my_result, original_result);
    // Проверка значений
    ck_assert_int_eq(value1_my, value1_original);
    ck_assert_int_eq(value2_my, value2_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %c
START_TEST(test_s21_sscanf_char)
{
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

// Тестовый случай для s21_sscanf с использованием спецификатора %c и краевого случая: пустая строка
START_TEST(test_s21_sscanf_char_empty_string)
{
    const char *input_str = "";
    char value_my = 'A';  // Начальное значение
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

// Тестовый случай для s21_sscanf с использованием спецификатора %c и краевого случая: пробельные символы
START_TEST(test_s21_sscanf_char_whitespace)
{
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

// Тестовый случай для s21_sscanf с использованием спецификатора %c и считыванием нескольких значений
START_TEST(test_s21_sscanf_multiple_chars)
{
    const char *input_str = "ABC";
    char value1_my = '\0', value2_my = '\0', value3_my = '\0';
    char value1_original = '\0', value2_original = '\0', value3_original = '\0';

    // Сравнение с оригинальной функцией sscanf
    int original_result = sscanf(input_str, "%c %c %c", &value1_original, &value2_original, &value3_original);
    int my_result = s21_sscanf(input_str, "%c %c %c", &value1_my, &value2_my, &value3_my);

    // Проверка результатов
    ck_assert_int_eq(my_result, original_result);
    // Проверка значений
    ck_assert_int_eq(value1_my, value1_original);
    ck_assert_int_eq(value2_my, value2_original);
    ck_assert_int_eq(value3_my, value3_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %c и символов табуляции, пробелов, переносов строк
START_TEST(test_s21_sscanf_char_no_delim)
{
    const char *input_str = "A B\nC";
    char value1_my = '\0', value2_my = '\0', value3_my = '\0';
    char value1_original = '\0', value2_original = '\0', value3_original = '\0';

    // Сравнение с оригинальной функцией sscanf
    int original_result = sscanf(input_str, "%c%c%c", &value1_original, &value2_original, &value3_original);
    int my_result = s21_sscanf(input_str, "%c%c%c", &value1_my, &value2_my, &value3_my);

    // Проверка результатов
    ck_assert_int_eq(my_result, original_result);
    // Проверка значений
    ck_assert_int_eq(value1_my, value1_original);
    ck_assert_int_eq(value2_my, value2_original);
    ck_assert_int_eq(value3_my, value3_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %c и игнорированием пробельных символов
START_TEST(test_s21_sscanf_char_ignore_whitespace)
{
    const char *input_str = " A \tB\nC";
    char value1_my = '\0', value2_my = '\0', value3_my = '\0';
    char value1_original = '\0', value2_original = '\0', value3_original = '\0';

    // Сравнение с оригинальной функцией sscanf
    int original_result = sscanf(input_str, " %c %c %c", &value1_original, &value2_original, &value3_original);
    int my_result = s21_sscanf(input_str, " %c %c %c", &value1_my, &value2_my, &value3_my);

    // Проверка результатов
    ck_assert_int_eq(my_result, original_result);
    // Проверка значений
    ck_assert_int_eq(value1_my, value1_original);
    ck_assert_int_eq(value2_my, value2_original);
    ck_assert_int_eq(value3_my, value3_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %i в десятичной форме
START_TEST(test_s21_sscanf_integer_decimal)
{
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

// Тестовый случай для s21_sscanf с использованием спецификатора %i в восьмеричной форме
START_TEST(test_s21_sscanf_integer_octal)
{
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

// Тестовый случай для s21_sscanf с использованием спецификатора %i в шестнадцатеричной форме
START_TEST(test_s21_sscanf_integer_hexadecimal)
{
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

// Тестовый случай для s21_sscanf с использованием спецификатора %i с минимальным значением INT
START_TEST(test_s21_sscanf_integer_min_value)
{
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

// Тестовый случай для s21_sscanf с использованием спецификатора %i с максимальным значением INT
START_TEST(test_s21_sscanf_integer_max_value)
{
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

// Тестовый случай для s21_sscanf с использованием спецификатора %i с минимальным значением восьмеричного числа
START_TEST(test_s21_sscanf_integer_min_octal)
{
    const char *input_str = "-020000000000";  // Минимальное значение для int в восьмеричной системе счисления
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

// Тестовый случай для s21_sscanf с использованием спецификатора %i с максимальным значением восьмеричного числа
START_TEST(test_s21_sscanf_integer_max_octal)
{
    const char *input_str = "017777777777";  // Максимальное значение для int в восьмеричной системе счисления
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

// Тестовый случай для s21_sscanf с использованием спецификатора %i с минимальным значением шестнадцатеричного числа
START_TEST(test_s21_sscanf_integer_min_hexadecimal)
{
    const char *input_str = "-0x80000000";  // Минимальное значение для int в шестнадцатеричной системе счисления
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

// Тестовый случай для s21_sscanf с использованием спецификатора %i с максимальным значением шестнадцатеричного числа
START_TEST(test_s21_sscanf_integer_max_hexadecimal)
{
    const char *input_str = "0x7FFFFFFF";  // Максимальное значение для int в шестнадцатеричной системе счисления
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

// Тестовый случай для s21_sscanf с использованием спецификатора %i с значением 0 в десятичной системе счисления
START_TEST(test_s21_sscanf_decimal_zero_value)
{
    const char *input_str = "0";  // Значение 0 в десятичной системе счисления
    int value_my = 1;  // Искусственно установим начальное значение, чтобы проверить, что оно действительно изменится
    int value_original = 1;  // Искусственно установим начальное значение, чтобы проверить, что оно действительно изменится

    // Сравнение с оригинальной функцией sscanf
    int original_result = sscanf(input_str, "%i", &value_original);
    int my_result = s21_sscanf(input_str, "%i", &value_my);

    // Проверка результатов
    ck_assert_int_eq(my_result, original_result);
    // Проверка значений
    ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %o с значением 0 в восьмеричной системе счисления
START_TEST(test_s21_sscanf_octal_zero_value)
{
    const char *input_str = "00";  // Значение 0 в восьмеричной системе счисления
    int value_my = 1;  // Искусственно установим начальное значение, чтобы проверить, что оно действительно изменится
    int value_original = 1;  // Искусственно установим начальное значение, чтобы проверить, что оно действительно изменится

    // Сравнение с оригинальной функцией sscanf
    int original_result = sscanf(input_str, "%i", &value_original);
    int my_result = s21_sscanf(input_str, "%i", &value_my);

    // Проверка результатов
    ck_assert_int_eq(my_result, original_result);
    // Проверка значений
    ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %x с значением 0 в шестнадцатеричной системе счисления
START_TEST(test_s21_sscanf_hexadecimal_zero_value)
{
    const char *input_str = "0x0";  // Значение 0 в шестнадцатеричной системе счисления
    int value_my = 1;  // Искусственно установим начальное значение, чтобы проверить, что оно действительно изменится
    int value_original = 1;  // Искусственно установим начальное значение, чтобы проверить, что оно действительно изменится

    // Сравнение с оригинальной функцией sscanf
    int original_result = sscanf(input_str, "%i", &value_original);
    int my_result = s21_sscanf(input_str, "%i", &value_my);

    // Проверка результатов
    ck_assert_int_eq(my_result, original_result);
    // Проверка значений
    ck_assert_int_eq(value_my, value_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %e для десятичного числа с плавающей точкой
START_TEST(test_s21_sscanf_decimal_float_exponential)
{
    const char *input_str = "-123.456e3";  // Десятичное число с плавающей точкой в научной нотации
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

// Тестовый случай для s21_sscanf с использованием спецификатора %f для десятичного числа с плавающей точкой
START_TEST(test_s21_sscanf_decimal_float)
{
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

// Тестовый случай для s21_sscanf с использованием спецификатора %E для десятичного числа с плавающей точкой в научной нотации
START_TEST(test_s21_sscanf_decimal_float_exponential_uppercase)
{
    const char *input_str = "-99.956E-6";  // Десятичное число с плавающей точкой в научной нотации
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

// Тестовый случай для s21_sscanf с использованием спецификатора %g для десятичного числа с плавающей точкой
START_TEST(test_s21_sscanf_decimal_float_general)
{
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

// Тестовый случай для s21_sscanf с использованием спецификатора %G для десятичного числа с плавающей точкой
START_TEST(test_s21_sscanf_decimal_float_general_uppercase)
{
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

// Тестовый случай для s21_sscanf с использованием спецификатора %s для строки без пробелов
START_TEST(test_s21_sscanf_string_no_whitespace)
{
    const char *input_str = "HelloWorld";  // Строка без пробелов
    char buffer_my[20] = "";
    char buffer_original[20] = "";

    // Сравнение с оригинальной функцией sscanf
    int original_result = sscanf(input_str, "%s", buffer_original);
    int my_result = s21_sscanf(input_str, "%s", buffer_my);

    // Проверка результатов
    ck_assert_int_eq(my_result, original_result);
    // Проверка значений
    ck_assert_str_eq(buffer_my, buffer_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %s для строки с пробелами
START_TEST(test_s21_sscanf_string_with_whitespace)
{
    const char *input_str = "Hello World";  // Строка с пробелами
    char buffer_my[20] = "";
    char buffer_original[20] = "";

    // Сравнение с оригинальной функцией sscanf
    int original_result = sscanf(input_str, "%s", buffer_original);
    int my_result = s21_sscanf(input_str, "%s", buffer_my);

    // Проверка результатов
    ck_assert_int_eq(my_result, original_result);
    // Проверка значений
    ck_assert_str_eq(buffer_my, buffer_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %s с шириной поля
START_TEST(test_s21_sscanf_string_with_width)
{
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

// Тестовый случай для s21_sscanf с использованием спецификатора %s для пустой строки
START_TEST(test_s21_sscanf_empty_string)
{
    const char *input_str = "";  // Пустая строка
    char buffer_my[20] = "Hello";  // Исходное значение буфера
    char buffer_original[20] = "Hello";  // Исходное значение буфера

    // Сравнение с оригинальной функцией sscanf
    int original_result = sscanf(input_str, "%s", buffer_original);
    int my_result = s21_sscanf(input_str, "%s", buffer_my);

    // Проверка результатов
    ck_assert_int_eq(my_result, original_result);
    // Проверка значений
    ck_assert_str_eq(buffer_my, buffer_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %s для строки с одним символом
START_TEST(test_s21_sscanf_single_char_string)
{
    const char *input_str = "X";  // Строка с одним символом
    char buffer_my[20] = "Hello";  // Исходное значение буфера
    char buffer_original[20] = "Hello";  // Исходное значение буфера

    // Сравнение с оригинальной функцией sscanf
    int original_result = sscanf(input_str, "%s", buffer_original);
    int my_result = s21_sscanf(input_str, "%s", buffer_my);

    // Проверка результатов
    ck_assert_int_eq(my_result, original_result);
    // Проверка значений
    ck_assert_str_eq(buffer_my, buffer_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %s и предстоящими пробелами
START_TEST(test_s21_sscanf_string_with_leading_spaces)
{
    const char *input_str = "    HelloWorld";  // Строка с предстоящими пробелами
    char buffer_my[20] = "";  // Исходное значение буфера
    char buffer_original[20] = "";  // Исходное значение буфера

    // Сравнение с оригинальной функцией sscanf
    int original_result = sscanf(input_str, "%s", buffer_original);
    int my_result = s21_sscanf(input_str, "%s", buffer_my);

    // Проверка результатов
    ck_assert_int_eq(my_result, original_result);
    // Проверка значений
    ck_assert_str_eq(buffer_my, buffer_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %s и предстоящими пробелами с шириной поля
START_TEST(test_s21_sscanf_string_with_leading_spaces_and_width)
{
    const char *input_str = "    HelloWorld";  // Строка с предстоящими пробелами
    char buffer_my[10] = "";  // Буфер с шириной поля
    char buffer_original[10] = "";  // Буфер с шириной поля

    // Сравнение с оригинальной функцией sscanf
    int original_result = sscanf(input_str, "%9s", buffer_original);
    int my_result = s21_sscanf(input_str, "%9s", buffer_my);

    // Проверка результатов
    ck_assert_int_eq(my_result, original_result);
    // Проверка значений
    ck_assert_str_eq(buffer_my, buffer_original);
}

// Тестовый случай для s21_sscanf с использованием спецификатора %u для беззнакового целого числа
START_TEST(test_s21_sscanf_unsigned_integer)
{
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

// Тестовый случай для s21_sscanf с использованием спецификатора %x для шестнадцатеричного целого числа
START_TEST(test_s21_sscanf_hexadecimal_integer)
{
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

// Тестовый случай для s21_sscanf с использованием спецификатора %X для шестнадцатеричного целого числа (верхний регистр)
START_TEST(test_s21_sscanf_hexadecimal_integer_uppercase)
{
    const char *input_str = "0x1A2B";  // Шестнадцатеричное целое число (верхний регистр)
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

// Тестовый случай для s21_sscanf с использованием спецификатора %o для восьмеричного целого числа
START_TEST(test_s21_sscanf_octal_integer)
{
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

// Тестовый случай для s21_sscanf с использованием спецификатора %n
START_TEST(test_s21_sscanf_percent_n)
{
    int value_my = 0;
    int value_original = 0;

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

    // Проверка, что значение %n записалось в переменную
    ck_assert_int_eq(value_my, chars_read_my);
}

Suite *s21_sscanf_suite() {
  Suite *suite;
  TCase *tc_core;
  suite = suite_create("s21_sscanf");
  tc_core = tcase_create("core");
    tcase_add_test(tc_core, test_s21_sscanf_integer);
    tcase_add_test(tc_core, test_s21_sscanf_empty_string);
    tcase_add_test(tc_core, test_s21_sscanf_empty_format);
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
    tcase_add_test(tc_core, test_s21_sscanf_percent_n);


    
    // Добавьте другие тесты как необходимо

  suite_add_tcase(suite, tc_core);
  return suite;
}
