#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
	va_list params;
	va_start(params, format);
	scan_modifiers format_modifiers;
	int i = -1;
	int j = -1;

	reset_scan_mods(&format_modifiers);

	while (format[++i]) {
		if (format[i] == '%') {
			i = process_scan_format(format, i, str, &j, &params, &format_modifiers);
		} else if (format[i] == ' ') {
            i += skip_spaces(format + i) - 1;
        }
	}
	va_end(params);

	return 0;
}

void reset_scan_mods(scan_modifiers* format_modifiers) {
	format_modifiers->assignment = true;
	format_modifiers->length = 0;
}

int process_scan_format(const char* format, int i, const char* str, int* j, va_list *params, scan_modifiers *format_modifiers) {
	int percent_position = i;

	if (format[i] == '*') {
		format_modifiers->assignment = false;
		++i;
	}
	if (format[i] == 'h' || format[i] == 'l' || format[i] == 'L') {
		format_modifiers->length = format[i];
		++i;
	}

	*j = process_scan_specifier(format[i], str, *j, params, format_modifiers);

	reset_scan_mods(&format_modifiers);
	
	return i;
}

int process_scan_specifier(char specifier, const char* str, int len, va_list *params, scan_modifiers *format_modifiers) {
    scan_result res;

	if (specifier == 'c') {
        res.c = str[len];
        ++len;
	} else if (specifier == 'd' || specifier == 'i') {
        len += skip_spaces(str + len);
        int end = skip_dox(str + len, specifier);
        res.d = specifier == 'd' ? atoi(str + len) : strtol(str + len, str + len + end, 0);
        len += end;
	} else if (specifier == 'e' || specifier == 'E' || specifier == 'f' || specifier == 'g' || specifier == 'G') {
        len += skip_spaces(str + len);
        res.f = atof(str + len);
        len += skip_feg(str + len);
	} else if (specifier == 'o' || specifier == 'u' || specifier == 'x' || specifier == 'X') {
        len += skip_spaces(str + len);
        // res.u = specifier == 'o' ? otoi(str + len) : specifier == 'u' ? atoi(str + len) : xtoi(str + len);
        int end = skip_dox(str + len, specifier);
        res.u = specifier == 'u' ? atoi(str + len) : strtoul(str + len, str + len + end, specifier == 'o' ? 8 : 16);
        len += end;
	} else if (specifier == 's') {
        len += skip_spaces(str + len);
        res.s = str + len;
        len += skip_s(str + len);
	} else if (specifier == 'p') {
        void* p = va_arg(*params, void*);
	} else if (specifier == 'n') {
		int *n = va_arg(*params, int*);
		*n = len;
	} else if (specifier == '%') {
		;
	}

    if (format_modifiers->assignment) assign(&res, params, specifier, format_modifiers->length);

	return len;
}

int skip_spaces(char* str) {
    int i = -1;

    while(str[++i] && str[i] == ' ');

    return i;
}

int skip_dox(char* str, char radix) {
    int i = -1;

    if ((radix == 'd' || radix == 'i' || radix == 'u') && (str[i + 1] == '+' || str[i + 1] == '-')) ++i;
    while ((radix == 'd' || radix == 'i' || radix == 'u') && str[++i] && str[i] >= '0' && str[i] <= '9');
    while (radix == 'o' && str[++i] && str[i] >= '0' && str[i] <= '7');
    while ((radix == 'x' || radix == 'X') && str[++i] && (str[i] >= '0' && str[i] <= '7' || str[i] >= 'a' && str[i] <= 'f' || str[i] >= 'A' && str[i] <= 'F'));

    return i;
}

int skip_feg(char* str) {
    int i = -1;

    if (str[i + 1] == '+' || str[i + 1] == '-') ++i;
    while (str[++i] && str[i] >= '0' && str[i] <= '9');
    if (str[i] != '.') --i;
    while (str[++i] && str[i] >= '0' && str[i] <= '9');
    if (str[i] == 'e' || str[i] == 'E') {
        ;
    }

    return i;
}

int skip_s(char* str) {
    int i = -1;

    while (str[++i] && str[i] != ' ');

    return i;
}

void assign(scan_result* res, va_list* params, char specifier, char length) {
    if ((specifier == 'c' || specifier == 's') && length != 'l') {
        char* c = va_arg(*params, char*);
        *c = specifier == 'c' ? res->c : s21_strncpy(c, res->s, skip_s(res->s));
	} else if ((specifier == 'c' || specifier == 's') && length == 'l') {
        wchar_t* c = va_arg(*params, wchar_t*);
        *c = specifier == 'c' ? res->lc : wcsncpy(c, res->ls, skip_ls(res->ls));
	} else if ((specifier == 'd' || specifier == 'i') && length != 'h' && length != 'l') {
		int* d = va_arg(*params, int*);
        *d = res->d;
    } else if ((specifier == 'd' || specifier == 'i') && length == 'h') {
		short* d = va_arg(*params, short*);
        *d = res->hd;
    } else if ((specifier == 'd' || specifier == 'i') && length == 'l') {
		long* d = va_arg(*params, long*);
        *d = res->ld;
	} else if ((specifier == 'e' || specifier == 'E' || specifier == 'f' || specifier == 'g' || specifier == 'G') && length != 'L') {
		double* f = va_arg(*params, double*);
        *f = res->f;
    } else if ((specifier == 'e' || specifier == 'E' || specifier == 'f' || specifier == 'g' || specifier == 'G') && length == 'L') {
		long double* f = va_arg(*params, long double*);
        *f = res->lf;
	} else if ((specifier == 'o' || specifier == 'u' || specifier == 'x' || specifier == 'X') && length != 'h' && length != 'l') {
		unsigned* u = va_arg(*params, unsigned*);
        *u = res->u;
    } else if ((specifier == 'o' || specifier == 'u' || specifier == 'x' || specifier == 'X') && length == 'h') {
		unsigned short* u = va_arg(*params, unsigned short*);
        *u = res->hu;
    } else if ((specifier == 'o' || specifier == 'u' || specifier == 'x' || specifier == 'X') && length == 'l') {
		unsigned long* u = va_arg(*params, unsigned long*);
        *u = res->lu;
	} else if (specifier == 'p') {
        void* p = va_arg(*params, void*);
	} else if (specifier == '%') {
		char* c = va_arg(*params, char*);
        *c = '%';
	}
}

// unsigned otoi(char* str) {
//     unsigned res = 0;
//     int i = -1;

//     while (str[++i] && str[i] >= '0' && str[i] <= '7');

//     int power = -1;

//     while (--i >= 0) {
//         res += (str[i] - 48) * (int)pow(8, ++power);
//     }

//     return res;
// }

// unsigned xtoi(char* str) {
//     unsigned res = 0;
//     int i = -1;

//     while (str[++i] && (str[i] >= '0' && str[i] <= '7' || str[i] >= 'a' && str[i] <= 'f' || str[i] >= 'A' && str[i] <= 'F'));

//     int power = -1;

//     while (--i >= 0) {
//         res += (str[i] <= '7' ? str[i] - 48 : str[i] <= 'F' ? str[i] - 55 : str[i] - 87) * (int)pow(8, ++power);
//     }

//     return res;
// }