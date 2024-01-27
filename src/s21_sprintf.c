#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
	va_list params;
	va_start(params, format);
	modifiers format_modifiers;
	int i = -1;
	int j = -1;

	init_str_n_mods(str, &format_modifiers);

	while (format[++i]) {
		if (format[i] == '%') {
			i = process_format(format, i, str, j + 1, &params, &format_modifiers);
			j = s21_strlen(str) - 1;
		} else {
			str[++j] = format[i];
		}
	}
}

void init_str_n_mods(char *str, modifiers *format_modifiers) {
	int i = -1;
	while (str[++i]) str[i] = '\0';

	format_modifiers->left_alignment = false;
	format_modifiers->positive_sign = false;
	format_modifiers->space_instead_of_sign = false;
	format_modifiers->oct_hex_notation = false;
	format_modifiers->fill_with_nulls = false;
	format_modifiers->width = 0;
	format_modifiers->precision = 6;
	format_modifiers->length = 0;
}

int process_format(const char *format, int i, char *str, const int j, va_list *params, modifiers *format_modifiers) {
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
	}
	if (format[i] == '.') {
		format_modifiers->precision = atoi(format + i + 1);
		while (format[++i] && format[i] >= '0' && format[i] <= '9');
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
	
	return i;
}

char *process_specifier(char specifier, const int len, va_list *params, modifiers *format_modifiers) {
	char *res = NULL;
	if (specifier == 'c') {
		res = (char *)malloc(2 * sizeof(char));
		res[0] = (char)va_arg(*params, int);;
		res[1] = '\0';
	} else if (specifier == 'd' || specifier == 'i') {
		res = doxtoa(va_arg(*params, int), 10, false);
	} else if (specifier == 'e' || specifier == 'E') {
		res = etoa(ftoa(va_arg(*params, double)));
	} else if (specifier == 'f') {
		res = ftoa(va_arg(*params, double));
	} else if (specifier == 'g' || specifier == 'G') {
	} else if (specifier == 'o' || specifier == 'u' || specifier == 'x' || specifier == 'X') {
		res = doxtoa(va_arg(*params, unsigned), specifier == 'o' ? 8 : specifier == 'u' ? 10 : 16, specifier == 'X' ? true : false);
	} else if (specifier == 's') {
		res = va_arg(*params, char *);
	} else if (specifier == 'p') {
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

	return res && specifier != '%' && specifier != 'n' ? apply_format(res, format_modifiers, specifier) : res;
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

char *etoa(char* f_str) {
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

	int flen = s21_strlen(f_str);
	char *e_str = doxtoa(abs(exp), 10, false);
	e_str = s21_strlen(e_str) > 1 ? e_str : add_width(e_str, 1, '0', true);
	int elen = s21_strlen(e_str);
	f_str = (char *)realloc(f_str, (flen + elen + 3) * sizeof(char));
	s21_strncat(f_str, "e", 1);
	s21_strncat(f_str, exp < 0 ? "-" : "+", 1);
	s21_strncat(f_str, e_str, elen);

	return f_str;
}

char *ftoa(double f) {
	f_representation flt;
	flt.full = f;
	bool negative = flt.bits & 0x8000000000000000;
	int e = extract_exp(flt.bits);
	unsigned long long mask = (long long)1 << 51;
	char *integer = doxtoa(e >= 0 ? pow(2, e) : 0, 10, true);
	char *fraction = doxtoa(e < 0 ? pow(5, -e) : 0, 10, true);

	while (--e >= 0) {
		if (flt.bits & mask) {
			char *tmp = integer;
			char *addendum = doxtoa(pow(2, e), 10, true);
			integer = stradd(integer, addendum, false);
			free(tmp);
			free(addendum);
		}
		mask >>= 1;
	}
	e = abs(e);
	while (mask) {
		if (flt.bits & mask) {
			char *addendum = doxtoa(pow(5, e), 10, true);
			int prevnulls = (int)round(0.30103 * (float)e - 0.49732);
			addendum = prevnulls ? add_width(addendum, prevnulls, '0', true) : addendum;
			int addlen = s21_strlen(addendum);
			int fraclen = s21_strlen(fraction);
			fraction = fraclen < addlen ? add_width(fraction, addlen - fraclen, '0', false) : fraction;
			char *tmp = fraction;
			fraction = stradd(fraction, addendum, true);
			free(tmp);
			free(addendum);
		}
		mask >>= 1;
		++e;
	}

	int i = s21_strlen(integer);
	char* res_str = (char *)malloc((i + s21_strlen(fraction) + 2 + negative) * sizeof(char));
	res_str[0] = negative ? '-' : res_str[0];
	strcpy(res_str + negative, integer);
	res_str[i + negative] = '.';
	strcpy(res_str + negative + i + 1, fraction);
	res_str[i + negative + 1 + s21_strlen(fraction)] = '\0';
	free(integer);
	free(fraction);

	return res_str;
}

int extract_exp(unsigned long long bits) {
	unsigned long long mask = (long long)1 << 62;
	int e = -1023;
	int power = 11;

	while (--power >= 0) {
		e += bits & mask ? pow(2, power) : 0;
		mask >>= 1;
	}

	return e;
}

char* add_width(char *str, int num, char value, bool right_alignment) {
    int j = strlen(str);
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

char* stradd(char *l_str, char *r_str, bool fraction) {
	int i = s21_strlen(l_str);
	int j = s21_strlen(r_str);
	int k = (i > j ? i : j) + 1;
	char *res = (char *)malloc(k * sizeof(char));
	bool overflow = false;

	res[--k] = '\0';
	while (--k >= 0) {
		res[k] = (i && j ? -48 : 0) + (i ? l_str[--i] : 0) + (j ? r_str[--j] : 0) + overflow;
		overflow = res[k] > 57 ? true : false;
		res[k] -= res[k] > 57 ? 10 : 0;
	}
	res = overflow ? add_width(res, 1, '1', true) : res;

	return res;
}

char *apply_format(char *str, modifiers *format_modifiers, char specifier) {

	// точность

	size_t str_len = s21_strlen(str);
	// printf("len = %ld\n", str_len);
	if (specifier == 's' && str_len > format_modifiers->precision) {
		str[format_modifiers->precision] = '\0';
	}
	if (s21_strchr("diouxX", specifier) && str_len < format_modifiers->precision) {
		str = add_width(str, format_modifiers->precision - str_len, '0', true);
	}
	if (s21_strchr("diouxX", specifier) && *str == '0' && format_modifiers->precision == 0) {
		*str = '\0';
	}
	if (s21_strchr("eEfgG", specifier)) {
		char *tmp = s21_strchr(str, '.') + 1;
		if (s21_strchr("gG", specifier)) format_modifiers->precision -= tmp - 1 - str;
		int i = 0;
		while (*tmp >= '0' && *tmp <= '9') {
			i++;
			tmp++;
		}
		if (i < format_modifiers->precision) {
			size_t offset = format_modifiers->precision - i;
			if (!s21_strchr(str, 'e') && !s21_strchr(str, 'E')) {
				str = add_width(str, offset, '0', false);
			} else {
				str = (char *)realloc(str, (str_len + 1 + offset) * sizeof(char));
				tmp = s21_strchr(str, 'e');
				if (tmp == NULL) tmp = s21_strchr(str, 'E');
				for (int j = str_len; j >= tmp - str; j--) str[j + offset] = str[j];
				for (int j = 0; j < offset; j++) str[(tmp - str) + j] = '0';
			}
		} else if (i > format_modifiers->precision) {
			tmp = s21_strchr(str, '.') + 1 + format_modifiers->precision;
			char val = *tmp;
			*tmp = '\0';
			if (val > '4') {
				char *tail = s21_strchr(tmp + 1, 'e');
				if (tail == NULL) tail = s21_strchr(tmp + 1, 'E');
				char *str2 = malloc((3 + format_modifiers->precision) * sizeof(char));
				s21_memset(str2, '0', format_modifiers->precision + 1);
				str2[1] = '.';
				str2[format_modifiers->precision + 1] = '1';
				str2[format_modifiers->precision + 2] = '\0';
				tmp = stradd(str, str2, true);
				if (s21_strchr(tail, 'e') || s21_strchr(tail, 'E')) {
					tmp = (char *)realloc(tmp, (s21_strlen(tmp) + s21_strlen(tail) + 1) * sizeof(char));
					s21_strncat(tmp, tail, s21_strlen(tail) + 1);
				}
				free(str);
				free(str2);
				str = tmp;
			}
		}
	}
	if (s21_strchr("gG", specifier)) {
		char *tail = NULL;
		char *tmp = s21_strchr(str, 'e');
		if (tmp == NULL) tmp = s21_strchr(str, 'E');
		if (tmp != NULL) tail = tmp;
		else tmp = &str[s21_strlen(str)];
		tmp--;
		while (*tmp == '0') {
			*tmp = '\0';
			tmp--;
		}
		if (*tmp == ',') *tmp = '\0';
		if (tail) s21_strncat(str, tail, s21_strlen(tail) + 1);
	}
	

	// знак

	if (format_modifiers->positive_sign && s21_strchr("dieEfgG", specifier) && *str != '-') {
		str = add_width(str, 1, '+', true);
	}

	if (format_modifiers->space_instead_of_sign && !format_modifiers->positive_sign && s21_strchr("dieEfgG", specifier) && *str != '-') {
		str = add_width(str, 1, ' ', true);
	}


	// префикс и точка

	str_len = s21_strlen(str);
	if (format_modifiers->oct_hex_notation && s21_strchr("oxXeEfgG", specifier)) {
		if (specifier == 'o' && *str != 0 && *str != '0') {
			str = add_width(str, 1, '0', true);
		}
		if (specifier == 'x' && *str != 0 && *str != '0') {
			str = add_width(str, 1, 'x', true);
			str = add_width(str, 1, '0', true);
		}
		if (specifier == 'X' && *str != 0 && *str != '0') {
			str = add_width(str, 1, 'X', true);
			str = add_width(str, 1, '0', true);
		}
		if (specifier == 'f' && !s21_strchr(str, '.')) {
			str = add_width(str, 1, '.', false);
		}
		if (s21_strchr("eEgG", specifier) && !s21_strchr(str, '.')) {
			str = (char *)realloc(str, (str_len + 2) * sizeof(char));
			char *tmp = s21_strchr(str, 'e');
			if (tmp == NULL) tmp = s21_strchr(str, 'E');
			for (int i = str_len; i >= tmp - str; i--) str[i + 1] = str[i];
			str[tmp - str] = '.';
		}
	}


	// ширина
	str_len = s21_strlen(str);
	if (format_modifiers->width > str_len && !format_modifiers->fill_with_nulls) {
		str = add_width(str, format_modifiers->width - str_len, ' ', !format_modifiers->left_alignment);
	}
	else if (format_modifiers->width > str_len && format_modifiers->fill_with_nulls) {
		if (*str >= '0' && *str <= '9') {
			str = add_width(str, format_modifiers->width - str_len, '0', true);
		} else {
			char *tmp = str;
			while (*tmp < '0' || *tmp > '9') tmp++;
			size_t offset = format_modifiers->width - str_len;
			str = (char *)realloc(str, (str_len + 1 + offset) * sizeof(char));
			for (int j = str_len; j >= tmp - str; j--) str[j + offset] = str[j];
			for (int j = 0; j < offset; j++) str[(tmp - str) + j] = '0';

		}
	}

	// str_len = s21_strlen(str);
	// printf("len = %ld\n", str_len);
	return str;
}


int main() {
	modifiers mod = {0};
	mod.left_alignment = false;
	mod.positive_sign = false;
	mod.space_instead_of_sign = false;
	mod.oct_hex_notation = true;
	mod.fill_with_nulls = true;
	mod.width = 5;
	mod.precision = 1;
	mod.length = 0;

	char *src = "1d";
	char *val = malloc(100);
	s21_strncpy(val, src, 100);

	printf("%#05x\n", 29);
	// printf("%.17f\n", 412.2127);
	printf("%s\n", val = apply_format(val, &mod, 'x'));

	free(val);
	return 0;
}