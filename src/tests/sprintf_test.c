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
    s21_sprintf(s21_res, "%.3lE", a);
    sprintf(io_res, "%.3lE", a);
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

START_TEST(test_my_sprintf_random_int)
{
    srand((unsigned int)time(NULL));
    int intValue = rand() % 1000 - 500;  // Случайное целое число от -500 до 499
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    sprintf(expected_output, "Random Integer: %d", intValue);
    s21_sprintf(buffer, "Random Integer: %d", intValue);

    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_my_sprintf_random_float)
{
    srand((unsigned int)time(NULL));
    double floatValue = (rand() % 10000) / 100.0 - 50.0;  // Случайное число с плавающей точкой от -50.0 до 49.99
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    sprintf(expected_output, "Random Float: %.2f", floatValue);
    s21_sprintf(buffer, "Random Float: %.2f", floatValue);

    ck_assert_str_eq(buffer, expected_output);
}
END_TEST


START_TEST(test_my_sprintf_random_large_order)
{
    srand((unsigned int)time(NULL));
    int order = rand() % 200 - 100;  // Случайный порядок от -100 до 100
    double floatValue = (rand() % 10000) / 100.0 - 50.0;  // Случайное число с плавающей точкой от -50.0 до 49.99
    floatValue *= pow(10, order);  // Умножаем на 10 в степени порядка

    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    sprintf(expected_output, "Random Float with Large Order: %.2le", floatValue);
    s21_sprintf(buffer, "Random Float with Large Order: %.2le", floatValue);

    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_my_sprintf_complex_flags)
{
    srand((unsigned int)time(NULL));

    // Случайные значения
    int intValue = rand() % 200 - 100;
    double floatValue = ((double)rand() / RAND_MAX) * 200.0 - 100.0;
    const char *stringValue = "TestString";

    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Флаги: ширина 10, выравнивание по левому краю
    sprintf(expected_output, "Int: %-10d", intValue);
    s21_sprintf(buffer, "Int: %-10d", intValue);
    ck_assert_str_eq(buffer, expected_output);

    // Флаги: ширина 15, выравнивание по правому краю, знак "+"
    sprintf(expected_output, "Float: %+15.2f", floatValue);
    s21_sprintf(buffer, "Float: %+15.2f", floatValue);
    ck_assert_str_eq(buffer, expected_output);

    // Флаги: выравнивание по левому краю, символ " "
    sprintf(expected_output, "String: %-10s", stringValue);
    s21_sprintf(buffer, "String: %-10s", stringValue);
    ck_assert_str_eq(buffer, expected_output);

    // Флаги: выравнивание по правому краю, символ "#", ширина 10, точность 4
    sprintf(expected_output, "Float: %#-10.4f", floatValue);
    s21_sprintf(buffer, "Float: %#-10.4f", floatValue);
    ck_assert_str_eq(buffer, expected_output);

    // Флаги: выравнивание по правому краю, ширина 20, точность 8
    sprintf(expected_output, "Int: %20.8d", intValue);
    s21_sprintf(buffer, "Int: %20.8d", intValue);
    ck_assert_str_eq(buffer, expected_output);
}
END_TEST


START_TEST(test_my_sprintf_random_power)
{
    srand((unsigned int)time(NULL));

    // Случайные значения
    double baseValue = ((double)rand() / RAND_MAX);  // Случайное число от 0 до 1
    int power =  rand() % 200 - 100;
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Флаги: ширина 10, точность 2
    sprintf(expected_output, "Power: %10.*e", 2, pow(baseValue, power));
    s21_sprintf(buffer, "Power: %10.*e", 2, pow(baseValue, power));
    ck_assert_str_eq(buffer, expected_output);

    // Флаги: выравнивание по левому краю, ширина 15, символ "#"
    sprintf(expected_output, "Power: %#15.*e", 0, pow(baseValue, power));
    s21_sprintf(buffer, "Power: %#15.*e", 0, pow(baseValue, power));
    ck_assert_str_eq(buffer, expected_output);

    // Флаги: ширина 20, точность 3
    sprintf(expected_output, "Power: %20.*e", 3, pow(baseValue, power));
    s21_sprintf(buffer, "Power: %20.*e", 3, pow(baseValue, power));
    ck_assert_str_eq(buffer, expected_output);

    // Флаги: выравнивание по правому краю, символ " "
    sprintf(expected_output, "Power: %+15.*e", 4, pow(baseValue, power));
    s21_sprintf(buffer, "Power: %+15.*e", 4, pow(baseValue, power));
    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_my_sprintf_flags_long)
{
    srand((unsigned int)time(NULL));

    // Случайные значения
    long longValue = rand() % 2000 - 1000;
    unsigned long ulongValue = rand() % 200000;
    double doubleValue = ((double)rand() / RAND_MAX) * 200.0 - 100.0;
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Флаг "l": целое число
    sprintf(expected_output, "Long Integer: %ld", longValue);
    s21_sprintf(buffer, "Long Integer: %ld", longValue);
    ck_assert_str_eq(buffer, expected_output);

    // Флаг "l": беззнаковое целое число
    sprintf(expected_output, "Unsigned Long Integer: %lu", ulongValue);
    s21_sprintf(buffer, "Unsigned Long Integer: %lu", ulongValue);
    ck_assert_str_eq(buffer, expected_output);

    // Флаг "l": число с плавающей точкой
    sprintf(expected_output, "Double Value: %lf", doubleValue);
    s21_sprintf(buffer, "Double Value: %lf", doubleValue);
    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_my_sprintf_flags_long_double)
{
    srand((unsigned int)time(NULL));

    // Случайные значения
    long double ldValue = ((long double)rand() / RAND_MAX) * 300.0 - 150.0;
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Флаг "L": число с плавающей точкой (long double)
    sprintf(expected_output, "Long Double Value: %Lf", ldValue);
    s21_sprintf(buffer, "Long Double Value: %Lf", ldValue);
    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_my_sprintf_flags_short)
{
    srand((unsigned int)time(NULL));

    // Случайные значения
    short shortValue = rand() % 200 - 100;
    unsigned short ushortValue = rand() % 200;
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Флаг "h": короткое целое число
    sprintf(expected_output, "Short Integer: %hd", shortValue);
    s21_sprintf(buffer, "Short Integer: %hd", shortValue);
    ck_assert_str_eq(buffer, expected_output);

    // Флаг "h": беззнаковое короткое целое число
    sprintf(expected_output, "Unsigned Short Integer: %hu", ushortValue);
    s21_sprintf(buffer, "Unsigned Short Integer: %hu", ushortValue);
    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_my_sprintf_ints_overflow)
{
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Переполнение максимального знакового целого на 1
    sprintf(expected_output, "Integer overflow: %d", (int)2147483648);
    s21_sprintf(buffer, "Integer overflow: %d", 2147483648);
    ck_assert_str_eq(buffer, expected_output);

    // Переполнение максимального знакового короткого целого на 1
    sprintf(expected_output, "Short overflow: %hd", 32768);
    s21_sprintf(buffer, "Short overflow: %hd", 32768);
    ck_assert_str_eq(buffer, expected_output);

    // Переполнение максимального знакового длинного целого на 1
    sprintf(expected_output, "Long overflow: %ld", 9223372036854775808);
    s21_sprintf(buffer, "Long overflow: %ld", 9223372036854775808);
    ck_assert_str_eq(buffer, expected_output);

    // Переполнение максимального беззнакового целого на 1
    sprintf(expected_output, "Unsigned overflow: %u", 4294967296);
    s21_sprintf(buffer, "Unsigned overflow: %u", 4294967296);
    ck_assert_str_eq(buffer, expected_output);

    // Переполнение максимального беззнакового короткого целого на 1
    sprintf(expected_output, "Unsigned short overflow: %hu", 65536);
    s21_sprintf(buffer, "Unsigned short overflow: %hu", 65536);
    ck_assert_str_eq(buffer, expected_output);

    // Переполнение максимального беззнакового длинного целого на 1
    sprintf(expected_output, "Unsigned long overflow: %lu", 18446744073709551616);
    s21_sprintf(buffer, "Unsigned long overflow: %lu", 18446744073709551616);
    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_my_sprintf_char_edge_cases)
{
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Спецификатор "c": символ 'A'
    sprintf(expected_output, "Char: %c", 'A');
    s21_sprintf(buffer, "Char: %c", 'A');
    ck_assert_str_eq(buffer, expected_output);

    // Спецификатор "c": символ конца строки
    sprintf(expected_output, "Char: %c", '\0');
    s21_sprintf(buffer, "Char: %c", '\0');
    ck_assert_str_eq(buffer, expected_output);

    // Спецификатор "c": символ новой строки
    sprintf(expected_output, "Char: %c", '\n');
    s21_sprintf(buffer, "Char: %c", '\n');
    ck_assert_str_eq(buffer, expected_output);

    // Спецификатор "c": символ табуляции
    sprintf(expected_output, "Char: %c", '\t');
    s21_sprintf(buffer, "Char: %c", '\t');
    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_my_sprintf_wchar)
{
    setlocale(LC_ALL, "");  // Устанавливаем локаль для корректной работы с широкими символами

    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Спецификатор "lc": символ 'A'
    wchar_t wcharValue = L'A';
    sprintf(expected_output, "Wide Char: %lc", wcharValue);
    s21_sprintf(buffer, "Wide Char: %lc", wcharValue);
    ck_assert_str_eq(buffer, expected_output);

    // Спецификатор "lc": символ новой строки
    wchar_t newLine = L'\n';
    sprintf(expected_output, "Wide Char: %lc", newLine);
    s21_sprintf(buffer, "Wide Char: %lc", newLine);
    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_my_sprintf_wstring)
{
    setlocale(LC_ALL, "");  // Устанавливаем локаль для корректной работы с широкими символами

    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Спецификатор "ls": широкая строка L"Hello"
    const wchar_t *wstringValue = L"Hello";
    sprintf(expected_output, "Wide String: %ls", wstringValue);
    s21_sprintf(buffer, "Wide String: %ls", wstringValue);
    ck_assert_str_eq(buffer, expected_output);

    // Спецификатор "ls": широкая строка L"Привет"
    const wchar_t *russianWString = L"Привет";
    sprintf(expected_output, "Wide String: %ls", russianWString);
    s21_sprintf(buffer, "Wide String: %ls", russianWString);
    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_my_sprintf_pointer)
{
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Спецификатор "p": нулевой указатель
    void *nullPointer = NULL;
    sprintf(expected_output, "Pointer: %.20p", nullPointer);
    s21_sprintf(buffer, "Pointer: %p", nullPointer);
    ck_assert_str_eq(buffer, expected_output);

    // Спецификатор "p": ненулевой указатель
    int value = 42;
    void *nonNullPointer = &value;
    sprintf(expected_output, "Pointer: %p", nonNullPointer);
    s21_sprintf(buffer, "Pointer: %p", nonNullPointer);
    ck_assert_str_eq(buffer, expected_output);

    // Спецификатор "p": другой ненулевой указатель
    char charArray[10];
    void *nonNullPointer2 = charArray;
    sprintf(expected_output, "Pointer: %p", nonNullPointer2);
    s21_sprintf(buffer, "Pointer: %p", nonNullPointer2);
    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_my_sprintf_wstring_flags)
{
    setlocale(LC_ALL, "");  // Устанавливаем локаль для корректной работы с широкими символами

    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Спецификатор "ls": широкая строка L"Hello"
    const wchar_t *wstringValue = L"Hello"; 
    sprintf(expected_output, "Wide String: %ls", wstringValue);
    s21_sprintf(buffer, "Wide String: %ls", wstringValue);
    ck_assert_str_eq(buffer, expected_output);

    // Спецификатор "ls": широкая строка L"Привет"
    const wchar_t *russianWString = L"Привет";
    sprintf(expected_output, "Wide String: %ls", russianWString);
    s21_sprintf(buffer, "Wide String: %ls", russianWString);
    ck_assert_str_eq(buffer, expected_output);

    // Спецификатор "ls" с флагом "-" и шириной 10: широкая строка L"Test"
    const wchar_t *testWString = L"Test";
    sprintf(expected_output, "Wide String: %-10ls", testWString);
    s21_sprintf(buffer, "Wide String: %-10ls", testWString);
    ck_assert_str_eq(buffer, expected_output);

    // Спецификатор "ls" с шириной 8: широкая строка L"Test"
    sprintf(expected_output, "Wide String: %8ls", testWString);
    s21_sprintf(buffer, "Wide String: %8ls", testWString);
    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

// Тестовый случай для s21_sprintf с использованием спецификатора "ls" и нулевой широкой строки
START_TEST(test_my_sprintf_wstring_empty)
{
    setlocale(LC_ALL, "");  // Устанавливаем локаль для корректной работы с широкими символами

    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Спецификатор "ls": нулевая широкая строка
    const wchar_t *emptyWString = L"";
    sprintf(expected_output, "Empty Wide String: %ls", emptyWString);
    s21_sprintf(buffer, "Empty Wide String: %ls", emptyWString);
    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_my_sprintf_f_edgecase)
{
    double inf = INFINITY;
    double nan = NAN;
    long double inf_l = powl(2, 16384);
    long double nan_l = nanl("");
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Бесконечность для чиcла двойной точности
    // sprintf(expected_output, "Inf double: %10f", inf);
    // s21_sprintf(buffer, "Inf double: %10f", inf);
    // ck_assert_str_eq(buffer, expected_output);

    // // Минус бесконечность для чиcла двойной точности
    // sprintf(expected_output, "Inf double: %.10f", -inf);
    // s21_sprintf(buffer, "Inf double: %.10f", -inf);
    // ck_assert_str_eq(buffer, expected_output);

    // // Нечисло двойной точности
    // sprintf(expected_output, "Nan double: %+f", nan);
    // s21_sprintf(buffer, "Nan double: %+f", nan);
    // ck_assert_str_eq(buffer, expected_output);

    // // // Минус нечисло двойной точности
    sprintf(expected_output, "Nan double: %f", -nan);
    s21_sprintf(buffer, "Nan double: %f", -nan);
    ck_assert_str_eq(buffer, expected_output);

    // Бесконечность для чиcла повышенной точности
    // sprintf(expected_output, "Inf double: % Lf", inf_l);
    // s21_sprintf(buffer, "Inf double: % Lf", inf_l);
    // ck_assert_str_eq(buffer, expected_output);

    // // Минус бесконечность для чиcла повышенной точности
    // sprintf(expected_output, "Inf double: %#Lf", -inf_l);
    // s21_sprintf(buffer, "Inf double: %#Lf", -inf_l);
    // ck_assert_str_eq(buffer, expected_output);

    // // Нечисло повышенной точности
    // sprintf(expected_output, "Nan double: %.Lf", nan_l);
    // s21_sprintf(buffer, "Nan double: %.Lf", nan_l);
    // ck_assert_str_eq(buffer, expected_output);

    // // Минус нечисло повышенной точности
    // sprintf(expected_output, "Nan double: %010Lf", -nan_l);
    // s21_sprintf(buffer, "Nan double: %010Lf", -nan_l);
    // ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_my_sprintf_e_edgecase)
{
    double inf = INFINITY;
    double nan = NAN;
    long double inf_l = powl(2, 16384);
    long double nan_l = nanl("");
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Бесконечность для чиcла двойной точности
    sprintf(expected_output, "Inf double: %+e", inf);
    s21_sprintf(buffer, "Inf double: %+e", inf);
    ck_assert_str_eq(buffer, expected_output);

    // Бесконечность в верхнем регистре для чиcла двойной точности
    sprintf(expected_output, "Inf double: % E", inf);
    s21_sprintf(buffer, "Inf double: % E", inf);
    ck_assert_str_eq(buffer, expected_output);

    // Минус бесконечность для чиcла двойной точности
    sprintf(expected_output, "Inf double: %10e", -inf);
    s21_sprintf(buffer, "Inf double: %10e", -inf);
    ck_assert_str_eq(buffer, expected_output);

    // Минус бесконечность в верхнем регистре для чиcла двойной точности
    sprintf(expected_output, "Inf double: %.10E", -inf);
    s21_sprintf(buffer, "Inf double: %.10E", -inf);
    ck_assert_str_eq(buffer, expected_output);

    // Нечисло двойной точности
    sprintf(expected_output, "Nan double: %-10e", nan);
    s21_sprintf(buffer, "Nan double: %-10e", nan);
    ck_assert_str_eq(buffer, expected_output);

    // Нечисло двойной точности в верхнем регистре
    sprintf(expected_output, "Nan double: %.E", nan);
    s21_sprintf(buffer, "Nan double: %.E", nan);
    ck_assert_str_eq(buffer, expected_output);

    // Минус нечисло двойной точности
    sprintf(expected_output, "Nan double: %#e", -nan);
    s21_sprintf(buffer, "Nan double: %#e", -nan);
    ck_assert_str_eq(buffer, expected_output);

    // Минус нечисло двойной точности в верхнем регистре
    sprintf(expected_output, "Nan double: % E", -nan);
    s21_sprintf(buffer, "Nan double: % E", -nan);
    ck_assert_str_eq(buffer, expected_output);

    // Бесконечность для чиcла повышенной точности
    sprintf(expected_output, "Inf double: %.20Le", inf_l);
    s21_sprintf(buffer, "Inf double: %.20Le", inf_l);
    ck_assert_str_eq(buffer, expected_output);

    // Бесконечность в верхнем регистре для чиcла повышенной точности
    sprintf(expected_output, "Inf double: %20.10LE", inf_l);
    s21_sprintf(buffer, "Inf double: %20.10LE", inf_l);
    ck_assert_str_eq(buffer, expected_output);

    // Минус бесконечность для чиcла повышенной точности
    sprintf(expected_output, "Inf double: %Le", -inf_l);
    s21_sprintf(buffer, "Inf double: %Le", -inf_l);
    ck_assert_str_eq(buffer, expected_output);

    // Минус бесконечность в верхнем регистре для чиcла повышенной точности
    sprintf(expected_output, "Inf double: %LE", -inf_l);
    s21_sprintf(buffer, "Inf double: %LE", -inf_l);
    ck_assert_str_eq(buffer, expected_output);

    // Нечисло повышенной точности
    sprintf(expected_output, "Nan double: %Le", nan_l);
    s21_sprintf(buffer, "Nan double: %Le", nan_l);
    ck_assert_str_eq(buffer, expected_output);

    // Нечисло повышенной точности в верхнем регистре
    sprintf(expected_output, "Nan double: %LE", nan_l);
    s21_sprintf(buffer, "Nan double: %LE", nan_l);
    ck_assert_str_eq(buffer, expected_output);

    // Минус нечисло повышенной точности
    sprintf(expected_output, "Nan double: %Le", -nan_l);
    s21_sprintf(buffer, "Nan double: %Le", -nan_l);
    ck_assert_str_eq(buffer, expected_output);

    // Минус нечисло повышенной точности в верхнем регистре
    sprintf(expected_output, "Nan double: %LE", -nan_l);
    s21_sprintf(buffer, "Nan double: %LE", -nan_l);
    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

START_TEST(test_my_sprintf_g_edgecase)
{
    double inf = INFINITY;
    double nan = NAN;
    long double inf_l = powl(2, 16384);
    long double nan_l = nanl("");
    char expected_output[MAX_BUFFER_SIZE];
    char buffer[MAX_BUFFER_SIZE];

    // Бесконечность для чиcла двойной точности
    sprintf(expected_output, "Inf double: %g", inf);
    s21_sprintf(buffer, "Inf double: %g", inf);
    ck_assert_str_eq(buffer, expected_output);

    // Бесконечность в верхнем регистре для чиcла двойной точности
    sprintf(expected_output, "Inf double: %G", inf);
    s21_sprintf(buffer, "Inf double: %G", inf);
    ck_assert_str_eq(buffer, expected_output);

    // Минус бесконечность для чиcла двойной точности
    sprintf(expected_output, "Inf double: %G", -inf);
    s21_sprintf(buffer, "Inf double: %G", -inf);
    ck_assert_str_eq(buffer, expected_output);

    // Минус бесконечность в верхнем регистре для чиcла двойной точности
    sprintf(expected_output, "Inf double: %G", -inf);
    s21_sprintf(buffer, "Inf double: %G", -inf);
    ck_assert_str_eq(buffer, expected_output);

    // Нечисло двойной точности
    sprintf(expected_output, "Nan double: %g", nan);
    s21_sprintf(buffer, "Nan double: %g", nan);
    ck_assert_str_eq(buffer, expected_output);

    // Нечисло двойной точности в верхнем регистре
    sprintf(expected_output, "Nan double: %G", nan);
    s21_sprintf(buffer, "Nan double: %G", nan);
    ck_assert_str_eq(buffer, expected_output);

    // Минус нечисло двойной точности
    sprintf(expected_output, "Nan double: %g", -nan);
    s21_sprintf(buffer, "Nan double: %g", -nan);
    ck_assert_str_eq(buffer, expected_output);

    // Минус нечисло двойной точности в верхнем регистре
    sprintf(expected_output, "Nan double: %G", -nan);
    s21_sprintf(buffer, "Nan double: %G", -nan);
    ck_assert_str_eq(buffer, expected_output);

    // Бесконечность для чиcла повышенной точности
    sprintf(expected_output, "Inf double: %Lg", inf_l);
    s21_sprintf(buffer, "Inf double: %Lg", inf_l);
    ck_assert_str_eq(buffer, expected_output);

    // Бесконечность в верхнем регистре для чиcла повышенной точности
    sprintf(expected_output, "Inf double: %LG", inf_l);
    s21_sprintf(buffer, "Inf double: %LG", inf_l);
    ck_assert_str_eq(buffer, expected_output);

    // Минус бесконечность для чиcла повышенной точности
    sprintf(expected_output, "Inf double: %Lg", -inf_l);
    s21_sprintf(buffer, "Inf double: %Lg", -inf_l);
    ck_assert_str_eq(buffer, expected_output);

    // Минус бесконечность в верхнем регистре для чиcла повышенной точности
    sprintf(expected_output, "Inf double: %LG", -inf_l);
    s21_sprintf(buffer, "Inf double: %LG", -inf_l);
    ck_assert_str_eq(buffer, expected_output);

    // Нечисло повышенной точности
    sprintf(expected_output, "Nan double: %Lg", nan_l);
    s21_sprintf(buffer, "Nan double: %Lg", nan_l);
    ck_assert_str_eq(buffer, expected_output);

    // Нечисло повышенной точности в верхнем регистре
    sprintf(expected_output, "Nan double: %LG", nan_l);
    s21_sprintf(buffer, "Nan double: %LG", nan_l);
    ck_assert_str_eq(buffer, expected_output);

    // Минус нечисло повышенной точности
    sprintf(expected_output, "Nan double: %Lg", -nan_l);
    s21_sprintf(buffer, "Nan double: %Lg", -nan_l);
    ck_assert_str_eq(buffer, expected_output);

    // Минус нечисло повышенной точности в верхнем регистре
    sprintf(expected_output, "Nan double: %LG", -nan_l);
    s21_sprintf(buffer, "Nan double: %LG", -nan_l);
    ck_assert_str_eq(buffer, expected_output);
}
END_TEST

Suite *s21_sprintf_suite() {
  Suite *suite;
  TCase *tc_core;
  suite = suite_create("s21_sprintf");
  tc_core = tcase_create("core");
//  tcase_add_test(tc_core, test_s21_sprintf_d);
//  tcase_add_test(tc_core, test_s21_sprintf_d2);
//  tcase_add_test(tc_core, test_s21_sprintf_f);
//  tcase_add_test(tc_core, test_s21_sprintf_f2);
//  tcase_add_test(tc_core, test_s21_sprintf_f3);
//  tcase_add_test(tc_core, test_s21_sprintf_E_precision);
//  tcase_add_test(tc_core, test_s21_sprintf_alignment);
//  tcase_add_test(tc_core, test_s21_sprintf_padding);
//  tcase_add_test(tc_core, test_s21_sprintf_complex);
//  tcase_add_test(tc_core, test_s21_sprintf_multiple_flags);
//  tcase_add_test(tc_core, test_s21_sprintf_float_flags);
//  tcase_add_test(tc_core, test_s21_sprintf_integer_flags);
//  tcase_add_test(tc_core, test_s21_sprintf_string);
//  tcase_add_test(tc_core, test_s21_sprintf_float);
//  tcase_add_test(tc_core, test_s21_sprintf_integer);
//  tcase_add_test(tc_core, test_my_sprintf_random_int);
//  tcase_add_test(tc_core, test_my_sprintf_random_float);
//  tcase_add_test(tc_core, test_my_sprintf_random_large_order);
//  tcase_add_test(tc_core, test_my_sprintf_complex_flags);
//  tcase_add_test(tc_core, test_my_sprintf_random_power);
//  tcase_add_test(tc_core, test_my_sprintf_flags_long);
//  tcase_add_test(tc_core, test_my_sprintf_flags_long_double);
//  tcase_add_test(tc_core, test_my_sprintf_flags_short);
//  tcase_add_test(tc_core, test_my_sprintf_ints_overflow);
//  tcase_add_test(tc_core, test_my_sprintf_char_edge_cases);
//  tcase_add_test(tc_core, test_my_sprintf_wstring);
//  tcase_add_test(tc_core, test_my_sprintf_wchar);
//  tcase_add_test(tc_core, test_my_sprintf_pointer);
//  tcase_add_test(tc_core, test_my_sprintf_wstring_empty);
//   tcase_add_test(tc_core, test_my_sprintf_wstring_flags);
  tcase_add_test(tc_core, test_my_sprintf_f_edgecase);
//   tcase_add_test(tc_core, test_my_sprintf_e_edgecase);
//   tcase_add_test(tc_core, test_my_sprintf_g_edgecase);
  
  suite_add_tcase(suite, tc_core);
  return suite;
}

