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
			j = strlen(str) - 1;
		} else {
			str[++j] = format[i];
		}
	}
	va_end(params);

	return 0;
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

	while (format[++i] && strchr("-+ #0", format[i])) {
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

	char *res = process_specifier(format[i], strlen(str), params, format_modifiers);
	if (res) {
		strncat(str, res, strlen(res));
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
		res = doxtoa(format_modifiers->length == 'h' ? va_arg(*params, short) : format_modifiers->length == 'l' ? va_arg(*params, long) : va_arg(*params, int), 10, false);
	} else if (specifier == 'e' || specifier == 'E') {
		res = etoa(ftoa(va_arg(*params, double)));
	} else if (specifier == 'f') {
		res = ftoa(va_arg(*params, double));
	} else if (specifier == 'g' || specifier == 'G') {
	} else if (specifier == 'o' || specifier == 'u' || specifier == 'x' || specifier == 'X') {
		res = doxtoa(format_modifiers->length == 'h' ? va_arg(*params, unsigned short) : format_modifiers->length == 'l' ? va_arg(*params, unsigned long) : va_arg(*params, unsigned), specifier == 'o' ? 8 : specifier == 'u' ? 10 : 16, specifier == 'X' ? true : false);
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
	int point = strchr(f_str, '.') - f_str;
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

	int flen = strlen(f_str);
	char *e_str = doxtoa(abs(exp), 10, false);
	e_str = strlen(e_str) > 1 ? e_str : add_width(e_str, 1, '0', true);
	int elen = strlen(e_str);
	f_str = (char *)realloc(f_str, (flen + elen + 3) * sizeof(char));
	strncat(f_str, "e", 1);
	strncat(f_str, exp < 0 ? "-" : "+", 1);
	strncat(f_str, e_str, elen);

	return f_str;
}

char *ftoa(long double f) {
	f_representation flt;
	flt.full = f;
	bool negative = flt.bits[0] & 0x8000;
	int e = extract_exp(flt.bits[0]);
	unsigned long long mask = (unsigned long long)1 << 63;
	char *integer = doxtoa(0, 10, false);
	char *fraction = doxtoa(0, 10, false);

	integer = e > 0 ? calculate_int_part(integer, e, flt.bits, e > 64 ? 1 : mask >> (e - 1)) : integer;
	mask >>= e;
	fraction = mask ? calculate_frac_part(fraction, e, flt.bits, mask) : fraction;

	int i = strlen(integer);
	char* res_str = (char *)malloc((i + strlen(fraction) + 2 + negative) * sizeof(char));
	res_str[0] = negative ? '-' : res_str[0];
	strcpy(res_str + negative, integer);
	res_str[i + negative] = '.';
	strcpy(res_str + negative + i + 1, fraction);
	res_str[i + negative + 1 + strlen(fraction)] = '\0';
	free(integer);
	free(fraction);

	return res_str;
}

int extract_exp(short bits) {
	unsigned long long mask = 0x4000;
	int e = -16384;
	int power = 15;

	while (--power >= 0) {
		e += bits & mask ? pow(2, power) : 0;
		mask >>= 1;
	}

	return e;
}

char *calculate_int_part(char *integer, const int e, const short *bits, unsigned long long mask) {
	int p = e > 52 ? e - 52 - 1 : -1;
	char* power_of_2 = doxtoa(2, 10, false);
	int prev_p = 1;
	while (++p <= e) {
		if (bits[(e - p) / 16 + ((e - p) % 16 ? 1 : 0)] & mask || p == e) {
			char *tmp = integer;
			char *addendum = raise_power_of_2(power_of_2, p - prev_p + 1);
			int addlen = strlen(addendum);
			power_of_2 = (char *)malloc((addlen + 1) * sizeof(char));
			power_of_2 = strncpy(power_of_2, addendum, addlen);
			power_of_2[addlen] = '\0';
			prev_p = e;

			integer = stradd(integer, addendum);
			free(tmp);
			if (p <= 63) free(addendum);
		}
		mask <<= 1;
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

char *calculate_frac_part(char *fraction, int e, const short *bits, unsigned long long mask) {
	int senior_degree = e;
	e = e >= 0 ? 1 : abs(e);
	char* power_of_5 = doxtoa(5, 10, false);
	int prev_p = 1;
	while (mask) {
		if (bits[(senior_degree + e) / 16 + ((senior_degree + e) % 16 ? 1 : 0)] & mask) {
			char *addendum = raise_power_of_5(power_of_5, e - prev_p + 1);
			int addlen = strlen(addendum);
			power_of_5 = (char *)malloc((addlen + 1) * sizeof(char));
			power_of_5 = strncpy(power_of_5, addendum, addlen);
			power_of_5[addlen] = '\0';
			prev_p = e;
			// int prevnulls = (int)round(0.30103 * (float)(e) - 0.49732);
			int prevnulls = e - addlen;
			addendum = prevnulls ? add_width(addendum, prevnulls, '0', true) : addendum;
			addlen = strlen(addendum);
			int fraclen = strlen(fraction);
			fraction = fraclen < addlen ? add_width(fraction, addlen - fraclen, '0', false) : fraction;
			char *tmp = fraction;
			fraction = stradd(fraction, addendum);
			free(tmp);
		}
		mask >>= 1;
		++e;
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

char* stradd(char *l_str, char *r_str) {
	int i = strlen(l_str);
	int j = strlen(r_str);
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
	// if (format_modifiers->width > strlen(str));
	return str;
}