#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
	va_list params;
	va_start(params, format);
	print_modifiers format_modifiers;
	int i = -1;
	int j = -1;
	bool fail = false;

	str[0] = '\0';
	reset_mods(&format_modifiers);

	while (format[++i] && !fail) {
		if (format[i] == '%') {
			fail = process_format(format, &i, str, &params, &format_modifiers);
			j = s21_strlen(str) - 1;
		} else {
			str[++j] = format[i];
            str[j + 1] = '\0';
		}
	}
	va_end(params);

	return fail ? -1 : j + 1;
}

//void init_str(char* str) {
//	int i = -1;
//	while (str[++i]) str[i] = '\0';
//}

void reset_mods(print_modifiers* format_modifiers) {
	format_modifiers->left_alignment = false;
	format_modifiers->positive_sign = false;
	format_modifiers->space_instead_of_sign = false;
	format_modifiers->oct_hex_notation = false;
	format_modifiers->fill_with_nulls = false;
	format_modifiers->width = 0;
	format_modifiers->precision = -1;
	format_modifiers->length = 0;
}

int process_format(const char *format, int* i, char *str, va_list *params, print_modifiers *format_modifiers) {
	int percent_position = i;

	while (format[++(*i)] && s21_strchr("-+ #0", format[*i])) {
		if (format[*i] == '-') format_modifiers->left_alignment = true;
		if (format[*i] == '+') format_modifiers->positive_sign = true;
		if (format[*i] == ' ') format_modifiers->space_instead_of_sign = true;
		if (format[*i] == '#') format_modifiers->oct_hex_notation = true;
		if (format[*i] == '0') format_modifiers->fill_with_nulls = true;
	}
	if (format[*i] >= '1' && format[*i] <= '9') {
		format_modifiers->width = atoi(format + *i);
		while (format[++(*i)] && format[*i] >= '0' && format[*i] <= '9');
	} else if (format[*i] == '*') {
		format_modifiers->width = va_arg(*params, int);
		++(*i);
	}
	if (format[*i] == '.') {
		if (format[++(*i)] == '*') {
			format_modifiers->precision = va_arg(*params, int);
            ++(*i);
		} else if (format[*i] >= '0' && format[*i] <= '9') {
			format_modifiers->precision = atoi(format + *i);
			while (format[++(*i)] && format[*i] >= '0' && format[*i] <= '9');
		} else format_modifiers->precision = 0;
	}
	if (format[*i] == 'h' || format[*i] == 'l' || format[*i] == 'L') {
		format_modifiers->length = format[*i];
		++(*i);
	}

	bool fail = false;
	char *res = process_specifier(format[*i], s21_strlen(str), params, format_modifiers, &fail);
	if (res) {
		s21_strncat(str, res, s21_strlen(res));
		free(res);
	} else *i = percent_position;

	reset_mods(format_modifiers);
	
	return fail;
}

char *process_specifier(char specifier, const int len, va_list *params, print_modifiers *format_modifiers, bool* fail) {
	char *res = NULL;
	if (specifier == 'c') {
		res = get_c(params, format_modifiers->length, fail);
	} else if (specifier == 'd' || specifier == 'i') {
		format_modifiers->precision = format_modifiers->precision == -1 ? 1 : format_modifiers->precision;
		res = ditoa(format_modifiers->length == 'h' ? (short)va_arg(*params, int) : format_modifiers->length == 'l' ? va_arg(*params, long) : va_arg(*params, int));
	} else if (specifier == 'e' || specifier == 'E' || specifier == 'f' || specifier == 'g' || specifier == 'G') {
		format_modifiers->precision = format_modifiers->precision == -1 ? 6 : format_modifiers->precision;
		res = get_f(params, format_modifiers->length);
	} else if (specifier == 'o' || specifier == 'u' || specifier == 'x' || specifier == 'X') {
		format_modifiers->precision = format_modifiers->precision == -1 ? 1 : format_modifiers->precision;
		res = uoxtoa(format_modifiers->length == 'h' ? (unsigned short)va_arg(*params, unsigned int) : format_modifiers->length == 'l' ? va_arg(*params, unsigned long) : va_arg(*params, unsigned), specifier == 'o' ? 8 : specifier == 'u' ? 10 : 16, specifier == 'X');
	} else if (specifier == 's') {
		res = get_s(params, format_modifiers->length, fail);
	} else if (specifier == 'p') {
		format_modifiers->precision = format_modifiers->precision == -1 ? 1 : format_modifiers->precision;
		res = get_p(va_arg(*params, unsigned long));
	} else if (specifier == 'n') {
		int *n = va_arg(*params, int *);
		*n = len;
		res = (char *)calloc(1, sizeof(char));
	} else if (specifier == '%') {
		res = (char *)calloc(2, sizeof(char));
		res[0] = '%';
	}

	return res && specifier != '%' && specifier != 'n' ? apply_format(res, *format_modifiers, specifier) : res;
}

char* get_c(va_list* params, char length, bool* fail) {
	char* res;

	if (length == 'l') {
		wchar_t c = va_arg(*params, wchar_t);
        res = (char*)calloc(1, sizeof(wchar_t) + sizeof(char));
		wcstombs(res, &c,   sizeof(wchar_t));
		if (!s21_strlen(res)) *fail = true;
	} else {
		res = (char *)calloc(2, sizeof(char));
		res[0] = (char)va_arg(*params, int);
		if (!s21_strlen(res)) *fail = true;
	}

	return res;
}

char *ditoa(long d) {
	int i = dilen(d);
	char *str = (char *)calloc(i + 1, sizeof(char));

	while (abs((int)(d / 10))) {
		str[--i] = abs((int)(d % 10));
		str[i] += 48;
		d /= 10;
	}
	str[--i] = abs((int)(d % 10));
	str[i] += 48;
	str[0] = d < 0 ? '-' : str[0];

	return str;
}

int dilen(long d) {
	int i = d < 0 ? 2 : 1;
	while (d / 10) {
		++i;
		d /= 10;
	}
	return i;
}

char *uoxtoa(unsigned long d, const int radix, const bool uppercase) {
	int i = uoxlen(d, radix);
	char *str = (char *)calloc(i + 1, sizeof(char));

	while (abs((int)(d / radix))) {
		str[--i] = abs((int)(d % radix));
		str[i] += str[i] < 10 ? 48 : uppercase ? 55 : 87;
		d /= radix;
	}
	str[--i] = abs((int)(d % radix));
	str[i] += str[i] < 10 ? 48 : uppercase ? 55 : 87;
	str[0] = (d < 0 && radix == 10) ? '-' : str[0];

	return str;
}

int uoxlen(unsigned long d, const int radix) {
	int i = (d < 0 && radix == 10) ? 2 : 1;
	while (d / radix) {
		++i;
		d /= radix;
	}
	return i;
}

char* get_f(va_list* params, char length) {
	char* res;

	if (length == 'L') {
        fl_representation f;
		f.full = va_arg(*params, long double);
		if (isinfl(f.full) || isnanl(f.full)) res = edge_case(isinfl(f.full), f.bits[4] & 0x8000);
		else res = lftoa(&f);
	} else {
        f_representation f;
		f.full = va_arg(*params, double);
		if (isinf(f.full) || isnan(f.full)) res = edge_case(isinf(f.full), f.bits & 0x8000000000000000);
		else res = ftoa(&f);
	}

	return res;
}

char* edge_case(bool inf, bool negative) {
	char* res = (char*)calloc(4 + negative, sizeof(char));
	res = negative ? s21_strncat(res, "-", 1) : res;
	res = s21_strncat(res, inf ? "inf" : "nan", 3);

    return res;
}

char *ftoa(const f_representation* f) {
	bool negative = f->bits & 0x8000000000000000;
	int e = extract_exp(f->bits);
	unsigned long long mask = (unsigned long long)1 << 51;
	char *integer = ditoa(0);
	char *fraction = ditoa(0);

	if (f->full) {
		integer = e >= 0 ? calculate_int_part(integer, e, f->bits, e > 52 ? 1 : mask >> (e - 1)) : integer;
    	mask = e > 0 ? mask >> e : mask;
		fraction = mask ? calculate_frac_part(fraction, e, f->bits, mask) : fraction;
	}

	char* res = join_frac_to_int(integer, fraction, negative);

	return res;
}

int extract_exp(unsigned long long bits) {
	unsigned long long mask = (long long)1 << 62;
	int e = -1023;
	int power = 11;

	while (--power >= 0) {
		e += (bits & mask) ? pow(2, power) : 0;
		mask >>= 1;
	}

	return e;
}

char *calculate_int_part(char *integer, const int e, const unsigned long long bits, unsigned long long mask) {
	int p = e > 52 ? e - 53 : -1;
	char* power_of_2 = ditoa(1);
	int prev_p = 0;
	while (++p <= e) {
		if (bits & mask || p == e) {
			integer = augment_int(integer, p, &power_of_2, &prev_p);
		}
		mask <<= 1;
	}
	free(power_of_2);

	return integer;
}

char* augment_int(char* integer, int p, char** power_of_2, int* prev_p) {
    char *tmp = integer;
    char *addendum = raise_power_of_2(*power_of_2, p - *prev_p + 1);
    *power_of_2 = addendum;
    *prev_p = p;
    integer = stradd(integer, addendum);
    free(tmp);

    return  integer;
}

char *calculate_frac_part(char *fraction, int e, const unsigned long long bits, unsigned long long mask) {
	char* power_of_5 = ditoa(5);
	int prev_p = 1;
    if (e < 0) {
        e = abs(e);
        fraction = augment_frac(fraction, e++, &power_of_5, &prev_p);
    } else e = 1;
	while (mask) {
		if (bits & mask) {
			fraction = augment_frac(fraction, e, &power_of_5, &prev_p);
		}
		mask >>= 1;
		++e;
	}
	free(power_of_5);

	return fraction;
}

char* augment_frac(char* fraction, int e, char** power_of_5, int* prev_p) {
    char *addendum = raise_power_of_5(*power_of_5, e - *prev_p + 1);
    int addlen = s21_strlen(addendum);
    *power_of_5 = (char *)calloc(addlen + 1, sizeof(char));
    *power_of_5 = s21_strncat(*power_of_5, addendum, addlen);
    *prev_p = e;
    int prevnulls = e - addlen;
    addendum = prevnulls ? add_width(addendum, prevnulls, '0', true) : addendum;
    addlen = s21_strlen(addendum);
    int fraclen = s21_strlen(fraction);
    fraction = fraclen < addlen ? add_width(fraction, addlen - fraclen, '0', false) : fraction;
    char *tmp = fraction;
    fraction = stradd(fraction, addendum);
    free(tmp);
    free(addendum);

    return fraction;
}

char* join_frac_to_int(char* integer, char* fraction, bool negative) {
    char* res = negative ? add_width(integer, 1, '-', true) : integer;
    res = add_width(res, 1, '.', false);
    char* tmp = res;
    res = (char*)realloc(res, (s21_strlen(res) + s21_strlen(fraction) + 1) * sizeof(char));
    if (!res) free(tmp);
    else s21_strncat(res, fraction, s21_strlen(fraction));
    free(fraction);

    return res;
}

char *lftoa(const fl_representation* f) {
	bool negative = f->bits[4] & 0x8000;
	int e = extract_exp_long(f->bits[4]);
	char *integer = ditoa(0);
	char *fraction = ditoa(0);

	if (f->full) {
		integer = e >= 0 ? calculate_int_part_long(integer, e, f->bits, e > 62 ? 1 : 0x8000 >> (e % 16)) : integer;
		unsigned short mask = 0x8000 >> (e % 16 + 1);
		fraction = e < 63 ? calculate_frac_part_long(fraction, e, f->bits, mask ? mask : 0x8000) : fraction;
	}

	char* res = join_frac_to_int(integer, fraction, negative);

	return res;
}

int extract_exp_long(const unsigned short bits) {
    unsigned short mask = 1 << 14;
    int e = -16383;
    int power = 15;

    while (--power >= 0) {
        e += (bits & mask) ? pow(2, power) : 0;
        mask >>= 1;
    }

    return e;
}

char *calculate_int_part_long(char *integer, const int e, const unsigned short *bits, unsigned short mask) {
	int p = e > 64 ? e - 63 : 0;
	char* power_of_2 = ditoa(1);
	int prev_p = 0;
	int i = 2 - e / 16;
	i = i < -1 ? -1 : i;
	while (++i < 4) {
		while (mask) {
			if (bits[i] & mask) {
				integer = augment_int(integer, p, &power_of_2, &prev_p);
			}
			mask <<= 1;
			++p;
		}
		mask = 1;
	}
	free(power_of_2);

	return integer;
}

char *calculate_frac_part_long(char *fraction, int e, const unsigned short *bits, unsigned short mask) {
	int i = 3 - e / 16 + 1;
	i = i > 4 ? 4 : i;
	e = e >= 0 ? 1 : abs(e);
	char* power_of_5 = ditoa(5);
	int prev_p = 1;
	while (--i >= 0) {
		while (mask) {
			if (bits[i] & mask) {
                fraction = augment_frac(fraction, e, &power_of_5, &prev_p);
			}
			mask >>= 1;
			++e;
		}
		mask = 1 << 15;
	}
	free(power_of_5);

	return fraction;
}

char* raise_power_of_2(char *str, int n) {
	while (--n) {
		char *tmp = str;
		str = stradd(str, str);
		free(tmp);
	}
	return str;
}

char* raise_power_of_5(char *str, int n) {
	while (--n) {
		char *tmp = str;
		char *tmp_times_2 = stradd(str, str);
		char *tmp_times_4 = stradd(tmp_times_2, tmp_times_2);
		free(tmp_times_2);
		str = stradd(tmp_times_4, tmp);
		free(tmp_times_4);
		free(tmp);
	}
	return str;
}

char* add_width(char *str, int num, char value, bool right_alignment) {
    int j = s21_strlen(str);
	int i = j + num + 1;
	str = (char *)realloc(str, i * sizeof(char));

	str[--i] = '\0';
	if (right_alignment) {
		while(--i >= num) str[i] = str[i - num];
		++i;
		while (--i >= 0) str[i] = value;
	} else {
	    --j;
		while (++j < i) str[j] = value;
	}

	return str;
}

char* stradd(char *l_str, char *r_str) {
    int l_len = s21_strlen(l_str);
    int r_len = s21_strlen(r_str);
	int i = l_len - 1;
	int j = r_len - 1;
	int k = max(l_len, r_len);
	if (point_position(l_str)) {
	    int l_frac = l_len - point_position(l_str);
	    int r_frac = r_len - point_position(r_str);
	    i = l_frac < r_frac ? i + r_frac - l_frac: i;
	    j = r_frac < l_frac ? j + l_frac - r_frac : j;
	}
	char *res = (char *)calloc(k + 1, sizeof(char));
	bool overflow = false;

	while (--k >= 0) {
	    if (i >= 0 && i < l_len && l_str[i] == '.') {
		    res[k] = '.';
	    } else {
	        res[k] = (i >= 0 && i < l_len && j >= 0 && j < r_len ? -48 : 0) + (i >= 0 && i < l_len ? l_str[i] : 0) + (j >= 0 && j < r_len ? r_str[j] : 0) + overflow;
		    overflow = res[k] > 57;
		    res[k] -= res[k] > 57 ? 10 : 0;
	    }
	    --i;
	    --j;
	}
	res = overflow ? add_width(res, 1, '1', true) : res;

	return res;
}

int point_position(char *str) {
    int i = -1;
    while (str[++i] && str[i] != '.');
    
    return str[i] ? i : 0;
}

char* get_s(va_list* params, char length, bool* fail) {
	char* res;

	if (length == 'l') {
		wchar_t* s = va_arg(*params, wchar_t*);
		res = (char*)calloc(1, wcslen(s) * sizeof(wchar_t) + sizeof(char));
		wcstombs(res, s, wcslen(s) * sizeof(wchar_t));
		if (!s21_strlen(res)) *fail = true;
	} else {
		char* s = va_arg(*params, char*);
		res = (char*)calloc(s21_strlen(s) + 1, sizeof(char));
		res = s21_strncat(res, s, s21_strlen(s));
	}
	
	return res;
}

char* get_p(unsigned long address) {
    char* res;

    if (address) res = uoxtoa(address, 16, false);
    else {
        res = (char*) calloc(6, sizeof(char));
        res = s21_strncat(res, "(nil)", 5);
    }

    return res;
}

char* clear_nulls(char* str) {
    int i = -1;
    while (str[++i] == '0' && str[i + 1] != '.');
    int j = -1;
    --i;
    while (str[++i]) str[++j] = str[i];
    str[++j] = '\0';
    str = (char*)realloc(str, (s21_strlen(str) + 1) * sizeof(char));
    return str;
}

char *clear_last_nulls(char *str) {
	if (str != NULL && *str != '\0') {
		size_t str_len = s21_strlen(str) - 1;
		char *tmp = &str[str_len];
		while (*tmp == '0' && str_len--) {
			*tmp = '\0';
			tmp--;
		}
	}
	return str;
}

char *etoa(char* f_str, print_modifiers format_modifiers, char specifier) {
    int point = s21_strchr(f_str, '.') - f_str;
    int integer_part = -1;
    while (f_str[++integer_part] && f_str[integer_part] < '1');
    int exp = point > integer_part ? point - integer_part - 1 : point - integer_part;
    if (point > integer_part + 1) {
        ++point;
        while (--point > integer_part + 1) {
            f_str[point] = f_str[point - 1];
        }
    } else if (point < integer_part) {
        --point;
        while (++point < integer_part) {
            f_str[point] = f_str[point + 1];
        }
    }
    f_str[point] = '.';
	f_str = string_format(f_str, &exp, format_modifiers, specifier);
    int flen = s21_strlen(f_str);
    char *e_str = ditoa(abs(exp));
    e_str = s21_strlen(e_str) > 1 ? e_str : add_width(e_str, 1, '0', true);
    int elen = s21_strlen(e_str);
    f_str = (char *)realloc(f_str, (flen + elen + 3) * sizeof(char));
	if (specifier == 'g') specifier = 'e';
	if (specifier == 'G') specifier = 'E';
	char *o = "e";
	if (s21_strchr("EG", specifier)) o = "E";
    s21_strncat(f_str, o, 1);
    s21_strncat(f_str, exp < 0 ? "-" : "+", 1);
    s21_strncat(f_str, e_str, elen);
	free(e_str);
    return f_str;
}

char *string_format(char *str, int *exp, print_modifiers format_modifiers, char specifier) {
	if (!s21_strchr(str, '.')) str = add_width(str, 1, '.', false);
	if (str[s21_strlen(str) - 1] == '.') str = add_width(str, 1, '0', false);
    str = clear_nulls(str);
	if (*str == '0') *exp = 0;
	char k = *str;
	str = double_round(str, format_modifiers, specifier);
	if (str[1] == '0' || (k == '9' && *str == '1')) {
		if (format_modifiers.precision && str[2] != '\0') {
			str[1] = '.';
			str[2] = '0';
			str[s21_strlen(str) - 1] = '\0';
		} else if (!format_modifiers.oct_hex_notation || !format_modifiers.precision) {
			str[1] = '\0';
		} else {
			str[1] = '.';
			str = add_width(str, 1, '0', false);
		}
		*exp += 1;
	}
	if (s21_strchr("gG", specifier) && !format_modifiers.oct_hex_notation)
		str = clear_last_nulls(str);
	return str;
}

void g_precision_calc(char *str, print_modifiers *format_modifiers) {
	char *tmp = str;
	bool dot_find = false;
	while (*tmp < '1' && *tmp != '\0') {
		if (*tmp == '.') dot_find = true;
		tmp++;
	}
	if (*tmp == '\0') {
		format_modifiers->precision -= 1;
	} else {
		if (dot_find) {
			size_t offset = tmp - s21_strchr(str, '.');
			if (format_modifiers->precision == 0 && offset != 1) format_modifiers->precision += 1;
			format_modifiers->precision += offset - format_modifiers->oct_hex_notation;
		} else {
			size_t offset = s21_strchr(str, '.') - tmp;
			format_modifiers->precision = format_modifiers->precision - offset;
			if (format_modifiers->precision < 0) format_modifiers->precision = 0;
		}
	}

}

char *double_round(char *str, print_modifiers format_modifiers, char specifier) {
	if (s21_strchr("gG", specifier)) g_precision_calc(str, &format_modifiers);
	char *tmp = s21_strchr(str, '.') + 1;
	int i = 0;
	while (*tmp >= '0' && *tmp <= '9') {
		i++;
		tmp++;
	}
	if (i < format_modifiers.precision) {
		size_t offset = format_modifiers.precision - i;
		str = add_width(str, offset, '0', false);
	} else if (i > format_modifiers.precision) {
		tmp = s21_strchr(str, '.') + 1 + format_modifiers.precision;
		char val = *tmp;
		*tmp = '\0';
		if (format_modifiers.precision == 0) *(tmp - 1) = '\0';
		if (val > '4' && val <= '9') {
			if (format_modifiers.precision == 0) {
				tmp = stradd(str, "1");
			} else {
				char *str2 = (char *)malloc((3 + format_modifiers.precision) * sizeof(char));
				s21_memset(str2, '0', format_modifiers.precision + 1);
				str2[1] = '.';
				str2[format_modifiers.precision + 1] = '1';
				str2[format_modifiers.precision + 2] = '\0';
				tmp = stradd(str, str2);
				free(str2);
			}
			if (s21_strchr("gG", specifier) && s21_strlen(tmp) > s21_strlen(str)) tmp[s21_strlen(tmp) - 1] = '\0';
			free(str);
			str = tmp;
		}
	}
	if (s21_strchr("gG", specifier) && !format_modifiers.oct_hex_notation)
		str = clear_last_nulls(str);
	if (s21_strchr(str, '.') == &str[s21_strlen(str) - 1])
		str[s21_strlen(str) - 1] = '\0';
	return str;
}

char *set_precision(char *str, print_modifiers format_modifiers, char specifier) {
	int str_len = (int)s21_strlen(str);
	if (specifier == 's' && format_modifiers.precision >= 0 && str_len > format_modifiers.precision) {
		str[format_modifiers.precision] = '\0';
	} else if (s21_strchr("diouxX", specifier) && str_len < format_modifiers.precision) {
		str = add_width(str, format_modifiers.precision - str_len, '0', true);
	} else if (s21_strchr("diouxX", specifier) && *str == '0' && format_modifiers.precision == 0) {
		*str = '\0';
	} else if (s21_strchr("f", specifier)) {
		str = double_round(str, format_modifiers, specifier);
	} else if (s21_strchr("Ee", specifier)) {
		str = etoa(str, format_modifiers, specifier);
	} else if (s21_strchr("Gg", specifier)) {
		int point = s21_strchr(str, '.') - str;
		int integer_part = -1;
		
		while (str[++integer_part] && str[integer_part] < '1');
		int exp = point > integer_part ? point - integer_part - 1 : point - integer_part;
		if ((exp < -4 || exp >= format_modifiers.precision) && !(!exp && !format_modifiers.precision && !(str[0] == '9' && str[2] > '4'))) {
			str = etoa(str, format_modifiers, specifier);
		} else {
			str = double_round(str, format_modifiers, specifier);
		}
	} else if (specifier == 'p' && *str != '(') {
		int zeros_no = format_modifiers.precision - str_len;
		if (zeros_no > 0) str = add_width(str, zeros_no, '0', true);
	}
	return str;
}

char *set_hex_notation(char *str, print_modifiers format_modifiers, char specifier, char is_zero) {
	size_t str_len = s21_strlen(str);
	if ((format_modifiers.oct_hex_notation && s21_strchr("oxXeEfgG", specifier)) || specifier == 'p') {
		if (specifier == 'o' && *str != 0 && *str != '0') {
			str = add_width(str, 1, '0', true);
		} else if ((specifier == 'x' && *str != 0 && is_zero != '0') || (specifier == 'p' && *str != '(')) {
			str = add_width(str, 1, 'x', true);
			str = add_width(str, 1, '0', true);
		} else if (specifier == 'X' && *str != 0 && is_zero != '0') {
			str = add_width(str, 1, 'X', true);
			str = add_width(str, 1, '0', true);
		} else if (s21_strchr("fgG", specifier) && !s21_strpbrk(str, "eE") && !s21_strpbrk(str, ",.")) {
			str = add_width(str, 1, '.', false);
		} else if (s21_strchr("gGeE", specifier) && s21_strpbrk(str, "eE") && !s21_strpbrk(str, ",.")) {
			str = (char *)realloc(str, (str_len + 2) * sizeof(char));
			char *tmp = s21_strchr(str, 'e');
			if (tmp == NULL) tmp = s21_strchr(str, 'E');
			for (int i = str_len; i >= tmp - str; i--) str[i + 1] = str[i];
			str[tmp - str] = '.';
		}
	}
	return str;
}

char *set_width(char *str, print_modifiers format_modifiers, char specifier) {
	int str_len = (int)s21_strlen(str);
	if (*str == '\0' && format_modifiers.width && specifier != 's') format_modifiers.width--; 
	if (format_modifiers.width > str_len && (!format_modifiers.fill_with_nulls || s21_strchr("(in", *str) || (*str != '\0' && str[1] != '\0' && s21_strchr("(in", str[1])))) {
		str = add_width(str, format_modifiers.width - str_len, ' ', !format_modifiers.left_alignment);
	}
	else if (format_modifiers.width > str_len && format_modifiers.fill_with_nulls) {
		if (s21_strchr("0123456789abcdefABCDEF", *str) && !s21_strpbrk(str, "xX")) {
			str = add_width(str, format_modifiers.width - str_len, '0', true);
		} else {
			char *tmp = str;
			if (!(s21_strpbrk(str, "xX"))) {
				while (*tmp < '0' || *tmp > '9') tmp++;
			} else {
				tmp = s21_strpbrk(str, "xX") + 1;
			}
			int diff = tmp - str;
			int offset = format_modifiers.width - str_len;
			str = (char *)realloc(str, (str_len + 1 + offset) * sizeof(char));
			for (int j = str_len; j >= diff; j--) str[j + offset] = str[j];
			for (int j = 0; j < offset; j++) str[(diff) + j] = '0';
		}
	}
	return str;
}

char *apply_format(char *str, print_modifiers format_modifiers, char specifier) {
	char is_zero = *str;
	size_t str_len = s21_strlen(str);

	// убираем минус
	bool negative = false;
	if (s21_strchr("dieEfgG", specifier)) {
		negative = *str == '-' ? true : false;
		if (negative) {
			memmove(str, str + 1, str_len);
			str = (char *)realloc(str, str_len);
		}
	}
	
	if (*str != 'n' && *str != 'i') {
		str = set_precision(str, format_modifiers, specifier);
		str = set_hex_notation(str, format_modifiers, specifier, is_zero);
	} else if (s21_strchr("EG", specifier) && s21_strchr("in", *str)) {
		char *tmp = s21_to_upper(str);
		free(str);
		str = tmp;
	}

	// знак
	str_len = s21_strlen(str);
	if (negative) {
		str = add_width(str, 1, '-', true);
	} else if (format_modifiers.positive_sign && s21_strchr("dieEfgG", specifier)) {
		str = add_width(str, 1, '+', true);
	} else if (format_modifiers.space_instead_of_sign && !format_modifiers.positive_sign && s21_strchr("dieEfgG", specifier)) {
		str = add_width(str, 1, ' ', true);
	}

	// ширина
	if (!(*str == 0 && ((specifier == 'c' && format_modifiers.left_alignment) || (specifier == 's' && format_modifiers.length == 'l')))) {
		str = set_width(str, format_modifiers, specifier);
	}
	return str;
}
