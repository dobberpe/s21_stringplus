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
        str[++(*j)] = va_arg(*params, char);
    } else if (format[i] == 'd' || format[i] == 'i') {
        char *di_str = doxtoa(va_arg(*params, int), 10, true);
        strcpy(str + i + 1, di_str);
    } else if (format[i] == 'e' || format[i] == 'E') {
        char *e_str = etoa(va_arg(*params, float));
        strcpy(str + i + 1, e_str);
    } else if (format[i] == 'f') {
        char *f_str = ftoa(va_arg(*params, float));
        strcpy(str + i + 1, f_str);
    } else if (format[i] == 'g' || format[i] == 'G') {
    } else if (format[i] == 'o') {
        char *o_str = doxtoa(va_arg(*params, unsigned), 8, true);
        strcpy(str + i + 1, o_str);
    } else if (format[i] == 's') {
        print_str(str, j, va_arg(*params, char *));
    } else if (format[i] == 'u') {
        char *u_str = doxtoa(va_arg(*params, unsigned), 10, true);
        strcpy(str + i + 1, u_str);
    } else if (format[i] == 'x' || format[i] == 'X') {
        char *x_str = doxtoa(va_arg(*params, unsigned), 16, format[i] == 'X' ? true : false);
        strcpy(str + i + 1, x_str);
    } else if (format[i] == 'p') {
        void *p = va_arg(*params, void *);
        char *p_str = doxtoa(p, 10, true);
        strcpy(str + i + 1, p_str);
    } else if (format[i] == 'n') {
        get_num_of_printed(*j, va_arg(*params, int *));
    }
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

char *etoa(const float e) {
    char* f_str = ftoa(e);
    int i = f_str[0] == '-' ? 0 : -1;

    while (f_str[++i] != '.');
    ++i;
    int point_place = f_str[0] == '-' ? 2 : 1;
    while (--i > point_place && f_str[i] != '-') {
        f_str[i] = f_str[i - 1];
    }
    f_str[point_place] = '.';

    return f_str;
}

char *ftoa(const float f) {
    f_representation flt;
    flt.full = f;
    bool negative = flt.bits & 0x80000000;
    int e = extract_exp(flt.bits);
    unsigned mask = 1 << 22;
    char *integer = doxtoa(e >= 0 ? pow(2, e) : 0, 10, true);
    char *fraction = doxtoa(e < 0 ? pow(5, -e): 0, 10, true);

    while (--e >= 0) {
        if (flt.bits & mask) {
            char *tmp = integer;
            char *addendum = doxtoa(pow(2, e), 10, true);
            integer = stradd(integer, addendum);
            free(tmp);
            free(addendum);
        }
        mask >>= 1;
    }
    e = abs(e);
    while (mask) {
        if (flt.bits & mask) {
            char *tmp = fraction;
            char *addendum = doxtoa(pow(5, e), 10, true);
            fraction = stradd(fraction, addendum);
            free(tmp);
            free(addendum);
        }
        mask >>= 1;
        ++e;
    }

    int i = strlen(integer);
    char* res_str = (char *)malloc((i + strlen(fraction) + 2 + negative) * sizeof(char));
    res_str[0] = negative ? '-' : res_str[0];
    strcpy(res_str + negative, integer);
    res_str[i + negative] = '.';
    strcpy(res_str + negative + i + 1, fraction);
    // strcpy конец строки ставит?
    free(integer);
    free(fraction);

    return res_str;
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

char* stradd(char *l_str, char *r_str) {
    int i = strlen(l_str);
    int j = strlen(r_str);
    int k = max(i, j) + 1;
    char *res = (char *)malloc(k * sizeof(char));
    bool overflow = false;

    res[--k] = '\0';
    while (--k >= 0) {
        res[k] = (i && j ? -48 : 0) + (i ? l_str[--i] : 0) + (j ? r_str[--j] : 0) + overflow;
        overflow = res[k] > 57 ? true : false;
        res[k] -= res[k] > 57 ? 10 : 0;
    }

    res = overflow ? increase_rank(res) : res;
    
    return res;
}

char* increase_rank(char *str) {
    int i = strlen(str) + 2;
    str = (char *)realloc(str, i * sizeof(char));

    str[--i] = '\0';
    while(--i) str[i] = str[i - 1];
    str[i] = '1';
    return str;
}

void get_num_of_printed(int j, int *n) {
    *n = j;
}