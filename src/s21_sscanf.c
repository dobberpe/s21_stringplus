#include "s21_string.h"

int s21_sscanf(const char *str, const char *format, ...) {
	va_list params;
	va_start(params, format);
	scan_modifiers format_modifiers;
    bool fail = false;
    char* str_p = (char*)str;
    int counter = 0;
	int i = -1;

	reset_scan_mods(&format_modifiers);

	while (format[++i] && !fail) {
		if (format[i] == '%') {
			fail = process_scan(format, &i, &str_p, str - str_p, &counter, &params, &format_modifiers);
		}
	}
	va_end(params);

	return counter;
}

void reset_scan_mods(scan_modifiers* format_modifiers) {
	format_modifiers->assignment = true;
    format_modifiers->width = 0;
	format_modifiers->length = 0;
}

bool process_scan(const char* format, int* i, char** str, const int read, int* counter, va_list *params, scan_modifiers *format_modifiers) {
    bool before_percent = s21_strchr(" \n\t\r\x0B\f", *i ? format[*i - 1] : 'a');

    if (format[++(*i)] >= '1' && format[*i] <= '9') {
        format_modifiers->width = atoi(format + *i);
        while (format[++(*i)] && format[*i] >= '0' && format[*i] <= '9');
    } else if (format[*i] == '*') {
		format_modifiers->assignment = false;
		++(*i);
	}
	if (format[*i] == 'h' || format[*i] == 'l' || format[*i] == 'L') {
		format_modifiers->length = format[*i];
		++(*i);
	}

    char specifier = format[*i];
    bool fail = false;
    if (specifier == 'c') {
        fail = set_c(str, counter, params, format_modifiers, before_percent);
    } else if (specifier == 'd' || specifier == 'i') {
        fail = set_di(specifier, str, counter, params, format_modifiers);
    } else if (specifier == 'e' || specifier == 'E' || specifier == 'f' || specifier == 'g' || specifier == 'G') {
        fail = set_feg(str, counter,params, format_modifiers);
    } else if (specifier == 'o' || specifier == 'u' || specifier == 'x' || specifier == 'X') {
        fail = set_uox(specifier, str, counter, params, format_modifiers);
    } else if (specifier == 's') {
        fail = set_s(str, counter, params, format_modifiers);
    } else if (specifier == 'p') {
        fail = set_p(str, counter, params, format_modifiers);
    } else if (specifier == 'n') {
        *(int*)va_arg(*params, void*) = read;
    } else if (specifier == '%') {
        if (**str != '%') fail = true;
        else ++(*str);
    } else fail = true;

	reset_scan_mods(format_modifiers);
	
	return fail;
}

bool set_c(char** str, int* counter, va_list *params, scan_modifiers* format_modifiers, bool before_percent) {
    bool fail = false;

    if (before_percent) {
        char *str_p;
        while ((str_p = s21_strchr(" \n\t\r\x0B\f", **str)) && *str_p) ++(*str);
    }
    if (!(**str)) fail = true;
    else if (format_modifiers->length == 'l') {
        if (format_modifiers->assignment) {
            int res = mbtowc(va_arg(*params, wchar_t*), *str, 2);
            if (res == -1 || !res) fail = true;
            ++(*counter);
        }
        *str += 2;
    } else {
        if (format_modifiers->assignment) *va_arg(*params, char*) = **str;
        ++(*str);
        ++(*counter);
    }

    return fail;
}

bool set_di(const char specifier, char** str, int* counter, va_list *params, scan_modifiers* format_modifiers) {
    bool fail = false;
    char* str_p;

    while ((str_p = s21_strchr(" \n\t\r\x0B\f", **str)) && *str_p) ++(*str);
    if (!(**str)) fail = true;
    else {
        str_p = *str;
        if (format_modifiers->width && format_modifiers->width < s21_strlen(str_p)) {
            str_p = (char*)calloc(format_modifiers->width + 1, sizeof(char));
            str_p = s21_strncat(str_p, *str, format_modifiers->width);
        }

        char* end;
        long res = strtol(str_p, &end, specifier == 'd' ? 10 : 0);
        if (end == str_p) fail = true;
        else if (format_modifiers->assignment) {
            if (format_modifiers->length == 'h') *(short*)va_arg(*params, void*) = (short)res;
            else if (format_modifiers->length == 'l') *(long*)va_arg(*params, void*) = res;
            else *(int*)va_arg(*params, void*) = (int)res;
            ++(*counter);
        }
        *str += end - str_p;
        if (format_modifiers->width && format_modifiers->width < s21_strlen(str_p)) free(str_p);
    }

    return fail;
}

bool set_feg(char** str, int* counter, va_list *params, scan_modifiers* format_modifiers) {
    bool fail = false;

    char* end;
    if (format_modifiers->length == 'L') {
        long double res = strtold(*str, &end);
        if (end == *str) fail = true;
        else if (format_modifiers->assignment) {
            *(long double*)va_arg(*params, void*) = res;
            ++(*counter);
        }
    } else if (format_modifiers->length == 'l') {
        double res = strtod(*str, &end);
        if (end == *str) fail = true;
        else if (format_modifiers->assignment) {
            *(double*)va_arg(*params, void*) = res;
            ++(*counter);
        }
    } else {
        float res = strtof(*str, &end);
        if (end == *str) fail = true;
        else if (format_modifiers->assignment) {
            *(float*)va_arg(*params, void*) = res;
            ++(*counter);
        }
    }
    *str = end;

    return fail;
}

bool set_uox(const char specifier, char** str, int* counter, va_list *params, scan_modifiers* format_modifiers) {
    bool fail = false;

    char* end;
    unsigned long res = strtoul(*str, &end, specifier == 'u' ? 10 : specifier == 'o' ? 8 : 16);
    if (end == *str) fail = true;
    else if (format_modifiers->assignment) {
        if (format_modifiers->length == 'h') *(unsigned short*)va_arg(*params, void*) = (unsigned short)res;
        else if (format_modifiers->length == 'l') *(unsigned long*)va_arg(*params, void*) = res;
        else *(unsigned int*)va_arg(*params, void*) = (unsigned int)res;
        ++(*counter);
    }
    *str = end;

    return fail;
}

bool set_s(char** str, int* counter, va_list *params, scan_modifiers* format_modifiers) {
    bool fail = false;
    char* str_p;

    while ((str_p = s21_strchr(" \n\t\r\x0B\f", **str)) && *str_p) ++(*str);
    if (!(**str)) fail = true;
    else {
        str_p = *str;
        if (format_modifiers->width && format_modifiers->width < s21_strlen(str_p)) {
            str_p = (char*)calloc(format_modifiers->width + 1, sizeof(char));
            str_p = s21_strncat(str_p, *str, format_modifiers->width);
        }

        char* end = s21_strpbrk(str_p, " \n\t\r\x0B\f");
        end = !end ? str_p + s21_strlen(str_p) : end;
        if (format_modifiers->assignment) {
            if (format_modifiers->length == 'l') {
                int res = mbstowcs(va_arg(*params, wchar_t*), str_p, end - *str);
                if (res == -1 || !res) fail = true;
                ++(*counter);
            } else {
                char* res = va_arg(*params, char*);
                res[0] = '\0';
                s21_strncat(res, str_p, end - *str);
                ++(*counter);
            }
        }
        *str += end - str_p;
        if (format_modifiers->width && format_modifiers->width < s21_strlen(str_p)) free(str_p);
    }

    return fail;
}

bool set_p(char** str, int* counter, va_list *params, scan_modifiers* format_modifiers) {
    bool fail = false;

    char* end;
    unsigned long res = strtoul(*str, &end, 16);
    if (end == *str) fail = true;
    else if (format_modifiers->assignment) {
        *va_arg(*params, void**) = (void*)res;
        ++(*counter);
    }
    *str = end;

    return fail;
}