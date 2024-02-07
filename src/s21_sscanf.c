#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
	va_list params;
	va_start(params, format);
	scan_modifiers format_modifiers;
    bool fail = false;
    char* str_p = (char*)str;
	int i = -1;

	reset_scan_mods(&format_modifiers);

	while (format[++i] && !fail) {
		if (format[i] == '%') {
			fail = process_scan_format(format, &i, &str_p, str - str_p, &params, &format_modifiers);
		}
	}
	va_end(params);

	return 0;
}

void reset_scan_mods(scan_modifiers* format_modifiers) {
	format_modifiers->assignment = true;
	format_modifiers->length = 0;
}

bool process_scan(const char* format, int* i, char** str, const int printed, va_list *params, scan_modifiers *format_modifiers) {
    char before_percent = *i ? format[*i - 1] : '\0';

	if (format[++(*i)] == '*') {
		format_modifiers->assignment = false;
		++(*i);
	}
	if (format[*i] == 'h' || format[*i] == 'l' || format[*i] == 'L') {
		format_modifiers->length = format[*i];
		++(*i);
	}

    if (specifier == 'c') {
        fail = set_c(str, params, format_modifiers, before_percent);
    } else if (specifier == 'd' || specifier == 'i') {
        fail = set_di(specifier, str, params, format_modifiers);
    } else if (specifier == 'e' || specifier == 'E' || specifier == 'f' || specifier == 'g' || specifier == 'G') {
        fail = set_feg(str, params, format_modifiers);
    } else if (specifier == 'o' || specifier == 'u' || specifier == 'x' || specifier == 'X') {
        fail = set_uox(specifier, str, params, format_modifiers);
    } else if (specifier == 's') {
        fail = set_s(str, params, format_modifiers);
    } else if (specifier == 'p') {
        fail = set_p(str, params, format_modifiers);
    } else if (specifier == 'n') {
        *va_arg(*params, int*) = printed;
    } else if (specifier == '%') {
        if (**str != '%') fail = true;
        else ++(*str);
    }

	reset_scan_mods(format_modifiers);
	
	return fail;
}

bool set_c(char** str, va_list *params, scan_modifiers* format_modifiers, bool before_percent) {
    bool fail = false;

    if (before_percent)
        while (s21_strchr(" \n\t\r\x0B\f", **str)) ++(*str);
    if (!(**str)) fail = true;
    else if (format_modifiers->length == 'l') {
        if (format_modifiers->assignment) {
            int res = mbtowc(va_arg(*params, wchar_t*), *str, 2);
            if (res == -1 || !res) fail = true;
        }
        *str += 2;
    } else {
        if (format_modifiers->assignment) {
            *va_arg(args, char *) = **src;
        }
        ++(*str);
    }

    return fail;
}

bool set_di(const char specifier, char** str, va_list *params, scan_modifiers* format_modifiers) {
    bool fail = false;

    char* end;
    long res = strtol(*str, &end, specifier == 'd' ? 10 : 0);
    if (end == *str) fail = true;
    else if (format_modifiers->assignment) {
        if (format_modifiers->length == 'h') *va_arg(*params, short*) = (short)res;
        else if (format_modifiers->length == 'l') *va_arg(*params, long*) = res;
        else *va_arg(*params, int*) = (int)res;
    }
    *str = end;

    return fail;
}

bool set_feg(char** str, va_list *params, scan_modifiers* format_modifiers) {
    bool fail = false;

    char* end;
    if (format_modifiers->length == 'L') {
        long double res = strtold(*str, &end);
        if (end == *str) fail = true;
        else if (format_modifiers->assignment) *va_arg(*params, long double*) = res;
    } else if (format_modifiers->length == 'l') {
        double res = strtod(*str, &end);
        if (end == *str) fail = true;
        else if (format_modifiers->assignment) *va_arg(*params, double*) = res;
    } else {
        float res = strtof(*str, &end);
        if (end == *str) fail = true;
        else if (format_modifiers->assignment) *va_arg(*params, float*) = res;
    }
    *str = end;

    return fail;
}

bool set_uox(const char specifier, char** str, va_list *params, scan_modifiers* format_modifiers) {
    bool fail = false;

    char* end;
    unsigned long res = strtoul(*str, &end, specifier == 'u' ? 10 : specifier == 'o' ? 8 : 16);
    if (end == *str) fail = true;
    else if (format_modifiers->assignment) {
        if (format_modifiers->length == 'h') *va_arg(*params, unsigned short*) = (unsigned short)res;
        else if (format_modifiers->length == 'l') *va_arg(*params, unsigned long*) = res;
        else *va_arg(*params, unsigned int*) = (unsigned int)res;
    }
    *str = end;

    return fail;
}

bool set_s(char** str, va_list *params, scan_modifiers* format_modifiers) {
    bool fail = false;

    if (before_percent)
        while (s21_strchr(" \n\t\r\x0B\f", **str)) ++(*str);
    if (!(**str)) fail = true;
    else {
        char* end = s21_strpbrk(*str, " \n\t\r\x0B\f");
        end = !end ? *str + s21_strlen(*str) : end;
        if (format_modifiers->assignment) {
            if (format_modifiers->length == 'l') {
                int res = mbstowcs(va_arg(*params, wchar_t*), *str, end - *str);
                if (res == -1 || !res) fail = true;
            } else {
                char* res = va_arg(*params, char*);
                res[0] = '\0';
                s21_strncat(res, *str, end - *str);
            }
        }
        *str = end;
    }

    return fail;
}

bool set_p(char** str, va_list *params, scan_modifiers* format_modifiers) {
    bool fail = false;

    char* end;
    unsigned long res = strtoul(*str, &end, 16);
    if (end == *str) fail = true;
    else if (format_modifiers->assignment) {
        *va_arg(*params, void**) = (void*)res;
    }
    *str = end;

    return fail;
}