#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
    va_list params;
    va_start(params, format);
    int i = -1;
    int j = -1;

    while (format[++i]) {
        if (format[i] == '%') {
            specifier(format, ++i, str, &j, &params);
        } else {
            str[++j] = format[i];
        }
    }
}

void specifier(const char *format, int i, char *str, int *j, va_list *params) {
    if (format[i] == 'c') {
    } else if (format[i] == 'd' || format[i] == 'i') {
        print_dox(str, j, va_arg(params, int), 10, true);
    } else if (format[i] == 'e' || format[i] == 'E') {
        print_exp(str, j, va_arg(params, float));
    } else if (format[i] == 'f') {
        print_float(str, j, va_arg(params, float));
    } else if (format[i] == 'g' || format[i] == 'G') {
        char e[256];
        char f[256];
        int je = -1;
        int jf = -1;
        print_exp(e, je, va_arg(params, float));
        print_float(f, jf, va_arg(params, float));
        print_str(str, j, je < jf ? e : f);
    } else if (format[i] == 'o') {
        print_dox(str, j, va_arg(params, int), 8, true);
    } else if (format[i] == 's') {
        print_str(str, j, va_arg(params, char *));
    } else if (format[i] == 'u') {
        print_dox(str, j, va_arg(params, unsigned int), 10, true);
    } else if (format[i] == 'x' || format[i] == 'X') {
        print_dox(str, j, va_arg(params, int), 16, format[i] == 'X' ? true : false);
    } else if (format[i] == 'p') {
        print_address(str, j, &va_arg(params, void *));
    } else if (format[i] == 'n') {
        print_n(*j, va_arg(params, int *));
    }
}

void print_dox(char *str, int *j, int d, const int radix, const bool uppercase) {
    if (d / radix) {
        print_dox(str, j, d / radix, radix, uppercase);
        str[++(*j)] = d % radix < 0 ? -(d % radix) : d % radix;
        str[*j] += str[*j] < 10 ? 48 : uppercase ? 55 : 87;
    } else {
        if (d < 0) str[++(*j)] = '-';
        str[++(*j)] = d < 0 ? -d : d;
        str[*j] += str[*j] < 10 ? 48 : uppercase ? 55 : 87;
    }
}

void print_exp(char *str, int *j, float e);

void print_float(char *str, int *j, float f) {
    f_representation flt;
    flt.full = f;
    bool negative = flt.bits & 0x80000000;
    int e = extract_exp(flt.bits);

}

int extract_exp(unsigned bits) {
    unsigned mask = 1 << 30;
    int e = -127;
    int power = 7;
    while (mask > 0x400000) {
        e += bits & mask ? s21_pow(2, power) : 0;
        mask >>= 1;
        --power;
    }
    return e;
}

int s21_pow(int a, int b) {
    int n = a;
    while (--b) a *= n;
    return a;
}

void print_str(char *str, int *j, char *s) {
    while (*s) str[++(*j)] = *s++;
}

void print_address(char *str, int *j, void **p);

void print_n(int j, int *n) {
    *n = j;
}