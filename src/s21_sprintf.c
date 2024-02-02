#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
	va_list params;
	va_start(params, format);
	print_modifiers format_modifiers;
	int i = -1;
	int j = -1;

	init_str(str);
	reset_mods(&format_modifiers);

	while (format[++i]) {
		if (format[i] == '%') {
			i = process_format(format, i, str, j + 1, &params, &format_modifiers);
			j = s21_strlen(str) - 1;
		} else {
			str[++j] = format[i];
		}
	}
	va_end(params);

	return 0;
}

void init_str(char* str) {
	int i = -1;
	while (str[++i]) str[i] = '\0';
}

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

int process_format(const char *format, int i, char *str, const int j, va_list *params, print_modifiers *format_modifiers) {
	int percent_position = i;

	while (format[++i] && s21_strchr("-+ #0", format[i])) {
		if (format[i] == '-') format_modifiers->left_alignment = true;
		if (format[i] == '+') format_modifiers->positive_sign = true;
		if (format[i] == ' ') format_modifiers->space_instead_of_sign = true;
		if (format[i] == '#') format_modifiers->oct_hex_notation = true;
		if (format[i] == '0') format_modifiers->fill_with_nulls = true;
	}
	if (format[i] >= '1' && format[i] <= '9') {
		format_modifiers->width = atoi(format + i);
		while (format[++i] && format[i] >= '0' && format[i] <= '9');
	} else if (format[i] == '*') {
		format_modifiers->width = va_arg(*params, int);
		++i;
	}
	if (format[i] == '.') {
		if (format[++i] == '*') {
			format_modifiers->precision = va_arg(*params, int);
		} else if (format[i] >= '0' && format[i] <= '9') {
			format_modifiers->precision = atoi(format + i);
			while (format[++i] && format[i] >= '0' && format[i] <= '9');
		} else format_modifiers->precision = 0;
	}
	if (format[i] == 'h' || format[i] == 'l' || format[i] == 'L') {
		format_modifiers->length = format[i];
		++i;
	}

	char *res = process_specifier(format[i], s21_strlen(str), params, format_modifiers);
	if (res) {
		s21_strncat(str, res, s21_strlen(res));
		free(res);
	} else i = percent_position;

	reset_mods(&format_modifiers);
	
	return i;
}

char *process_specifier(char specifier, const int len, va_list *params, print_modifiers *format_modifiers) {
	char *res = NULL;
	if (specifier == 'c') {
		if (format_modifiers->length == 'l') {
			wchar_t c = va_arg(*params, wchar_t);
			res = (char*)malloc(sizeof(wchar_t) + sizeof(char));
			wcstombs(res, &c, sizeof(wchar_t));
		} else {
			res = (char *)malloc(2 * sizeof(char));
			res[0] = (char)va_arg(*params, int);;
			res[1] = '\0';
		}
	} else if (specifier == 'd' || specifier == 'i') {
		format_modifiers->precision = format_modifiers->precision == -1 ? 1 : format_modifiers->precision;
		res = doxtoa(format_modifiers->length == 'h' ? va_arg(*params, short) : format_modifiers->length == 'l' ? va_arg(*params, long) : va_arg(*params, int), 10, false);
	} else if (specifier == 'e' || specifier == 'E' || specifier == 'f' || specifier == 'g' || specifier == 'G') {
		format_modifiers->precision = format_modifiers->precision == -1 ? 6 : format_modifiers->precision;
		res = get_f(format_modifiers->length == 'L' ? va_arg(*params, long double) : va_arg(*params, double));
	} else if (specifier == 'o' || specifier == 'u' || specifier == 'x' || specifier == 'X') {
		format_modifiers->precision = format_modifiers->precision == -1 ? 1 : format_modifiers->precision;
		res = doxtoa(format_modifiers->length == 'h' ? va_arg(*params, unsigned short) : format_modifiers->length == 'l' ? va_arg(*params, unsigned long) : va_arg(*params, unsigned), specifier == 'o' ? 8 : specifier == 'u' ? 10 : 16, specifier == 'X');
	} else if (specifier == 's') {
		if (format_modifiers->length == 'l') {
			wchar_t* s = va_arg(*params, wchar_t*);
			res = (char*)malloc((wcslen(s) * sizeof(wchar_t) + 1) * sizeof(char));
			wcstombs(res, s, wcslen(s) * sizeof(wchar_t));
		} else {
			char* s = va_arg(*params, char*);
			res = (char*)malloc((s21_strlen(s) + 1) * sizeof(char));
			res = s21_strncpy(res, s, s21_strlen(s));
		}
	} else if (specifier == 'p') {
		format_modifiers->precision = format_modifiers->precision == -1 ? 1 : format_modifiers->precision;
		res = doxtoa(va_arg(*params, unsigned long), 16, false);
	} else if (specifier == 'n') {
		int *n = va_arg(*params, int *);
		*n = len;
		res = (char *)malloc(1 * sizeof(char));
		res[0] = '\0';
	} else if (specifier == '%') {
		res = (char *)malloc(2 * sizeof(char));
		res[0] = '%';
		res[1] = '\0';
	}

	return res && specifier != '%' && specifier != 'n' ? apply_format(res, *format_modifiers, specifier) : res;
}

char *doxtoa(long long d, const int radix, const bool uppercase) {
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

int doxlen(long long d, const int radix) {
	int i = (d < 0 && radix == 10) ? 2 : 1;
	while (d / radix) {
		++i;
		d /= radix;
	}
	return i;
}

char* get_f(long double f) {
	char* res;
	if (isinfl(f) || isnanl(f)) {
		res = (char*)calloc((4 + (f < 0)), sizeof(char));
		res = f < 0 ? s21_strncat(res, "-", 1) : res;
		res = isinfl(f) ? s21_strncat(res, "inf", 3) : s21_strncat(res, "nan", 3);
	} else res = ftoa(f);

	return res;
}

char *ftoa(long double f) {
	f_representation flt;
	flt.full = f;
	bool negative = flt.bits[4] & 0x8000;
	int e = extract_exp(flt.bits[4]);
	char* res;
	char *integer = doxtoa(0, 10, false);
	char *fraction = doxtoa(0, 10, false);

	integer = e >= 0 ? calculate_int_part(integer, e, flt.bits, e > 62 ? 1 : 0x8000 >> (e % 16)) : integer;
	unsigned short mask = 0x8000 >> (e % 16 + 1);
	fraction = e < 63 ? calculate_frac_part(fraction, e, flt.bits, mask ? mask : 0x8000) : fraction;

	int i = s21_strlen(integer);
	res = negative ? add_width(integer, 1, '-', true) : integer;
	res = add_width(res, 1, '.', false);
	res = (char*)realloc(res, (s21_strlen(res) + s21_strlen(fraction) + 1) * sizeof(char));
	s21_strncat(res, fraction, s21_strlen(fraction));
	free(fraction);

	return res;
}

int extract_exp(const unsigned short bits) {
    unsigned short mask = 1 << 14;
    int e = -16383;
    int power = 15;

    while (--power >= 0) {
        e += bits & mask ? pow(2, power) : 0;
        mask >>= 1;
    }

    return e;
}

char *calculate_int_part(char *integer, const int e, const unsigned short *bits, unsigned short mask) {
	int p = e > 64 ? e - 63 : 0;
	char* power_of_2 = doxtoa(1, 10, false);
	int prev_p = 0;
	int i = 2 - e / 16;
	i = i < -1 ? -1 : i;
	while (++i < 4) {
		while (mask) {
			if (bits[i] & mask) {
				char *tmp = integer;
				char *addendum = raise_power_of_2(power_of_2, p - prev_p + 1);
				int addlen = s21_strlen(addendum);
				power_of_2 = (char *)malloc((addlen + 1) * sizeof(char));
				power_of_2 = s21_strncpy(power_of_2, addendum, addlen);
				power_of_2[addlen] = '\0';
				prev_p = p;
				integer = stradd(integer, addendum);
				free(tmp);
			}
			mask <<= 1;
			++p;
		}
		mask = 1;
	}
	free(power_of_2);

	return integer;
}

char* raise_power_of_2(char *str, int n) {
	while (--n) {
		char *tmp = str;
		str = stradd(str, str);
		free(tmp);
	}
	return str;
}

char *calculate_frac_part(char *fraction, int e, const unsigned short *bits, unsigned short mask) {
	int i = 3 - e / 16 + 1;
	i = i > 4 ? 4 : i;
	e = e >= 0 ? 1 : abs(e);
	char* power_of_5 = doxtoa(5, 10, false);
	int prev_p = 1;
	while (--i >= 0) {
		while (mask) {
			if (bits[i] & mask) {
				char *addendum = raise_power_of_5(power_of_5, e - prev_p + 1);
				int addlen = s21_strlen(addendum);
				power_of_5 = (char *)malloc((addlen + 1) * sizeof(char));
				power_of_5 = s21_strncpy(power_of_5, addendum, addlen);
				power_of_5[addlen] = '\0';
				prev_p = e;
				// int prevnulls = (int)round(0.30103 * (float)(e) - 0.49732);
				int prevnulls = e - addlen;
				addendum = prevnulls ? add_width(addendum, prevnulls, '0', true) : addendum;
				addlen = s21_strlen(addendum);
				int fraclen = s21_strlen(fraction);
				fraction = fraclen < addlen ? add_width(fraction, addlen - fraclen, '0', false) : fraction;
				char *tmp = fraction;
				fraction = stradd(fraction, addendum);
				free(tmp);
			}
			mask >>= 1;
			++e;
		}
		mask = 1 << 15;
	}
	free(power_of_5);

	return fraction;
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
	int k = max(l_len, r_len) + 1;
	if (point_position(l_str)) {
	    int l_frac = l_len - point_position(l_str);
	    int r_frac = r_len - point_position(r_str);
	    i = l_frac < r_frac ? i + r_frac - l_frac: i;
	    j = r_frac < l_frac ? j + l_frac - r_frac : j;
	}
	char *res = (char *)malloc(k * sizeof(char));
	bool overflow = false;

	res[--k] = '\0';
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

	if (!s21_strchr(f_str, '.')) f_str = add_width(f_str, 1, '.', false);
	if (f_str[s21_strlen(f_str) - 1] == '.') f_str = add_width(f_str, 1, '0', false);
    f_str = clear_nulls(f_str);
	if (*f_str == '0') exp = 0;
	char k = *f_str;
	f_str = double_round(f_str, format_modifiers, specifier);

	if (f_str[1] == '0' || (k == '9' && *f_str == '1')) {
		if (format_modifiers.precision && f_str[2] != '\0') {
			f_str[1] = '.';
			f_str[2] = '0';
			f_str[s21_strlen(f_str) - 1] = '\0';
		} else if (!format_modifiers.oct_hex_notation || !format_modifiers.precision) {
			f_str[1] = '\0';
		} else {
			f_str[1] = '.';
			f_str = add_width(f_str, 1, '0', false);
		}
		exp += 1;
	}
	if (s21_strchr("gG", specifier) && !format_modifiers.oct_hex_notation)
		f_str = clear_last_nulls(f_str);

    int flen = s21_strlen(f_str);
    char *e_str = doxtoa(abs(exp), 10, false);
    e_str = s21_strlen(e_str) > 1 ? e_str : add_width(e_str, 1, '0', true);
    int elen = s21_strlen(e_str);
    f_str = (char *)realloc(f_str, (flen + elen + 3) * sizeof(char));
	if (specifier == 'g') specifier = 'e';
	if (specifier == "G") specifier = 'E';

	char *o = "e";
	if (s21_strchr("EG", specifier)) o = "E";

    s21_strncat(f_str, o, 1);
    s21_strncat(f_str, exp < 0 ? "-" : "+", 1);
    s21_strncat(f_str, e_str, elen);
	free(e_str);
    return f_str;
}

char *double_round(char *str, print_modifiers format_modifiers, char specifier) {
	int i = 0;
	char *tmp;
	if (s21_strchr("gG", specifier)) {
		tmp = str;
		bool dot_find = false;
		while (*tmp < '1' && *tmp != '\0') {
			if (*tmp == '.') dot_find = true;
			tmp++;
		}
		if (*tmp == '\0') {
			format_modifiers.precision -= 1;
		} else {
			if (dot_find) {
				if (format_modifiers.precision == 0) format_modifiers.precision += 1;
				format_modifiers.precision += tmp - s21_strchr(str, '.') - format_modifiers.oct_hex_notation;
			} else {
				size_t offset = s21_strchr(str, '.') - tmp;
				format_modifiers.precision = format_modifiers.precision - offset;
				if (format_modifiers.precision < 0) format_modifiers.precision = 0;
			}
		}
	}

	tmp = s21_strchr(str, '.') + 1;
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
	size_t str_len = s21_strlen(str);
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
	}
	return str;
}

char *set_hex_notation(char *str, print_modifiers format_modifiers, char specifier, char is_zero) {
	size_t str_len = s21_strlen(str);
	if (format_modifiers.oct_hex_notation && s21_strchr("oxXeEfgG", specifier)) {
		if (specifier == 'o' && *str != 0 && *str != '0') {
			str = add_width(str, 1, '0', true);
		} else if (specifier == 'x' && *str != 0 && is_zero != '0') {
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
	size_t str_len = s21_strlen(str);
	if (*str == '\0' && format_modifiers.width && specifier != 's') format_modifiers.width--; 
	if (format_modifiers.width > str_len && !format_modifiers.fill_with_nulls) {
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
			size_t diff = tmp - str;
			size_t offset = format_modifiers.width - str_len;
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

	// точность
	str = set_precision(str, format_modifiers, specifier);
	
	// префикс и точка
	str = set_hex_notation(str, format_modifiers, specifier, is_zero);

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
	str = set_width(str, format_modifiers, specifier);

	return str;
}


// int main() {
// 	modifiers mod = {0};
// 	mod.left_alignment = false;
// 	mod.positive_sign = false;
// 	mod.space_instead_of_sign = false;
// 	mod.oct_hex_notation = true;
// 	mod.fill_with_nulls = false;
// 	mod.width = 9;
// 	mod.precision = 2;
// 	mod.length = 0;


// 	char *src = "99999.957";
// 	char *val = malloc(100);
// 	s21_strncpy(val, src, 100);

// 	printf("%s\n", val = apply_format(val, mod, 'g'));
// 	// printf("%s\n", val = etoa(val));
// 	printf("%#9.2g\n", 99999.957);

// 	free(val);
// 	return 0;
// }