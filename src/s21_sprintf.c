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
	format_modifiers->h = false;
	format_modifiers->l = false;
	format_modifiers->ld = false;
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
	if (format[i] == 'h') format_modifiers->h = true;
	else if (format[i] == 'l') format_modifiers->l = true;
	else if (format[i] == 'L') format_modifiers->ld = true;
	if (format[i] == 'h' || format[i] == 'l' || format[i] == 'L') ++i;

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
	e_str = s21_strlen(e_str) > 1 ? e_str : add_rank(e_str, 1, '0');
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
			addendum = prevnulls ? add_rank(addendum, prevnulls, '0') : addendum;
			int addlen = s21_strlen(addendum);
			int fraclen = s21_strlen(fraction);
			fraction = fraclen < addlen ? addnulles(fraction, fraclen - 1, addlen) : fraction;
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

char* add_rank(char *str, int num, char value) {
	int i = s21_strlen(str) + num + 1;
	str = (char *)realloc(str, i * sizeof(char));

	str[--i] = '\0';
	while(--i >= num) str[i] = str[i - num];
	++i;
	while (--i >= 0) str[i] = value;

	return str;
}

char *addnulles(char *str, int i, int j) {
	str = (char *)realloc(str, (j + 1) * sizeof(char));

	while (++i < j) str[i] = '0';
	str[j] = '\0';

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
	res = overflow ? add_rank(res, 1, '1') : res;

	return res;
}

char *apply_format(char *str, modifiers *format_modifiers, char specifier) {
	return str;
}