#include "s21_string.h"
#include <stdio.h>

int main() {
	char str[100];
	float a = 3.14;
//    sprintf(str, "%f", a);
	s21_sprintf(str, "%f", a);
	printf("%s\n", str);
	printf("%.22f", a);
	return 0;
}

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
	str[++j] = '\0';
}

void specifier(const char *format, int i, char *str, int *j, va_list *params) {
	if (format[i] == 'c') {
		str[++(*j)] = (char)va_arg(*params, int);
	} else if (format[i] == 'd' || format[i] == 'i') {
		char *di_str = doxtoa(va_arg(*params, int), 10, true);
		strcpy(str + (++(*j)), di_str);
		*j += strlen(di_str) - 1;
		free(di_str);
	} else if (format[i] == 'e' || format[i] == 'E') {
		char *e_str = ftoa(va_arg(*params, double));
		char *e_num = doxtoa(etoa(e_str), 10, true);
		if (strlen(e_num) < 2) add_rank(e_num, 1, '0');
		strcpy(str + (++(*j)), e_str);
		int shift = strlen(e_str);
		strcpy(str + *j + shift, "+");
		strcpy(str + *j + shift + 1, e_num);
		*j += shift + strlen(e_num);
		free(e_str);
		free(e_num);
	} else if (format[i] == 'f') {
		char *f_str = ftoa(va_arg(*params, double));
		strcpy(str + (++(*j)), f_str);
		*j += strlen(f_str) - 1;
		free(f_str);
	} else if (format[i] == 'g' || format[i] == 'G') {
	} else if (format[i] == 'o') {
		char *o_str = doxtoa(va_arg(*params, unsigned), 8, true);
		strcpy(str + (++(*j)), o_str);
		*j += strlen(o_str) - 1;
		free(o_str);
	} else if (format[i] == 's') {
		char *s_str = va_arg(*params, char *);
		strcpy(str + (++(*j)), s_str);
		*j += strlen(s_str) - 1;
	} else if (format[i] == 'u') {
		char *u_str = doxtoa(va_arg(*params, unsigned), 10, true);
		strcpy(str + (++(*j)), u_str);
		*j += strlen(u_str) - 1;
		free(u_str);
	} else if (format[i] == 'x' || format[i] == 'X') {
		char *x_str = doxtoa(va_arg(*params, unsigned), 16, format[i] == 'X' ? true : false);
		strcpy(str + (++(*j)), x_str);
		*j += strlen(x_str) - 1;
		free(x_str);
	} else if (format[i] == 'p') {
		unsigned long p = va_arg(*params, unsigned long);
		char *p_str = doxtoa(p, 16, false);
		strcpy(str + (++(*j)), "0x");
		strcpy(str + *j + 2, p_str);
		*j += strlen(p_str) + 1;
		free(p_str);
	} else if (format[i] == 'n') {
		get_num_of_printed(*j, va_arg(*params, int *));
	}
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

int etoa(char* f_str) {
	int i = f_str[0] == '-' ? 0 : -1;

	while (f_str[++i] != '.');
	int exp_num = i;
	++i;
	int point_place = f_str[0] == '-' ? 2 : 1;
	while (--i > point_place && f_str[i] != '-') {
		f_str[i] = f_str[i - 1];
	}
	f_str[point_place] = '.';

	return exp_num;
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
			int addlen = strlen(addendum);
			int fraclen = strlen(fraction);
			fraction = fraclen < addlen ? addnulles(fraction, fraclen - 1, addlen) : fraction;
			char *tmp = fraction;
			fraction = stradd(fraction, addendum, true);
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
	res_str[i + negative + 1 + strlen(fraction)] = '\0';
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
	int i = strlen(str) + num + 1;
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
	res = overflow ? add_rank(res, 1, '1') : res;

	return res;
}

void get_num_of_printed(int j, int *n) {
	*n = j;
}