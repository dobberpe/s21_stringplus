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
    if (format[i] >= '0' && format[i]) {
    }
    if (format[i] == 'c') {
    } else if (format[i] == 'd' || format[i] == 'i') {
        process_dox(va_arg(*params, int), 10, true);
    } else if (format[i] == 'e' || format[i] == 'E') {
        print_exp(str, j, va_arg(*params, float));
    } else if (format[i] == 'f') {
        print_float(str, j, va_arg(*params, float));
    } else if (format[i] == 'g' || format[i] == 'G') {
        char e[256];
        char f[256];
        int je = -1;
        int jf = -1;
        print_exp(e, je, va_arg(*params, float));
        print_float(f, jf, va_arg(*params, float));
        print_str(str, j, je < jf ? e : f);
    } else if (format[i] == 'o') {
        process_dox(va_arg(*params, int), 8, true);
    } else if (format[i] == 's') {
        print_str(str, j, va_arg(*params, char *));
    } else if (format[i] == 'u') {
        process_dox(va_arg(*params, unsigned int), 10, true);
    } else if (format[i] == 'x' || format[i] == 'X') {
        process_dox(va_arg(*params, int), 16, format[i] == 'X' ? true : false);
    } else if (format[i] == 'p') {
        print_address(str, j, va_arg(*params, void *));
    } else if (format[i] == 'n') {
        print_n(*j, va_arg(*params, int *));
    }
}

char* process_dox(int d, const int radix, const bool uppercase) {
    char *dox = doxtoa(d, radix, uppercase);
}

int doxlen(int d, const int radix) {
    int i = (d < 0 && radix == 10) ? 2 : 1;
    while (d / radix) {
        ++i;
        d /= radix;
    }
    return i;
}

char *doxtoa(int d, const int radix, const bool uppercase) {
    int i = doxlen(d, radix) + 1;
    char *str = (char *)malloc((i) * sizeof(char));
    str[--i] = '\0';
    
    while (abs(d / radix)) {
        str[--i] = abs(d % radix);
        str[i] += str[i] < 10 ? 48 : uppercase ? 55 : 87;
        d /= radix;
    }
    str[--i] = abs(d % radix);
    str[i] += str[i] < 10 ? 48 : uppercase ? 55 : 87;
    str[0] = (d < 0 && radix == 10) ? '-' : str[0];
    return str;
}

void print_exp(char *str, int *j, float e);

void ftoa(char *str, int *j, float f) {
    f_representation flt;
    flt.full = f;
    bool negative = flt.bits & 0x80000000;
    int e = extract_exp(flt.bits);
    unsigned mask = 1 << 22;
    int integer = 0;
    int fraction = 0;

    while (e >= 0) {
        integer += flt.bits & mask ? pow(2, e--) : 0;
        mask >>= 1;
    }
    e = 1;
    while (mask) {
        fraction += flt.bits & mask ? pow(5, e++) : 0;
        mask >>= 1;
    }

    char *int_str = doxtoa(integer, 10, true);
    char *int_str = doxtoa(integer, 10, true);
}

int extract_exp(unsigned bits) {
    unsigned mask = 1 << 30;
    int e = -127;
    int power = 7;
    while (mask > 0x400000) {
        e += bits & mask ? pow(2, power) : 0;
        mask >>= 1;
        --power;
    }
    return e;
}

void print_str(char *str, int *j, char *s) {
    while (*s) str[++(*j)] = *s++;
}

void print_address(char *str, int *j, void *p);

void print_n(int j, int *n) {
    *n = j;
}