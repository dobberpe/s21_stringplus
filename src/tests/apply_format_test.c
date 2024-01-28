#include "s21_string_test.h"

START_TEST(test_apply_format_d_basic) {
	modifiers mod = {0};
    mod.precision = 1;
    test_all_falgs_d(mod, "0", 0, 'd');
    test_all_falgs_d(mod, "5", 5, 'd');
    test_all_falgs_d(mod, "-47", -47, 'd');
}
END_TEST

START_TEST(test_apply_format_d_precision) {
	modifiers mod = {0};
	mod.precision = 6;
    test_all_falgs_d(mod, "0", 0, 'd');
    test_all_falgs_d(mod, "5", 5, 'd');
    test_all_falgs_d(mod, "-47", -47, 'd');
}
END_TEST

START_TEST(test_apply_format_d_width) {
	modifiers mod = {0};
	mod.width = 6;
    mod.precision = 1;
    // test_all_falgs_d(mod, "0", 0, 'd');
    test_all_falgs_d(mod, "5", 5, 'd');
    test_all_falgs_d(mod, "-47", -47, 'd');
}
END_TEST

START_TEST(test_apply_format_d_width_and_precision) {
	modifiers mod = {0};
	mod.width = 8;
    mod.precision = 4;
    // test_all_falgs_d(mod, "0", 0, 'd');
    test_all_falgs_d(mod, "5", 5, 'd');
    test_all_falgs_d(mod, "-47", -47, 'd');
}
END_TEST

Suite *s21_apply_format_suite() {
  Suite *suite;
  TCase *tc_core;
  suite = suite_create("s21_apply_format");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_apply_format_d_basic);
  tcase_add_test(tc_core, test_apply_format_d_precision);
  tcase_add_test(tc_core, test_apply_format_d_width);
  tcase_add_test(tc_core, test_apply_format_d_width_and_precision);
  suite_add_tcase(suite, tc_core);
  return suite;
}


void test_all_falgs_d(modifiers mod, char *src, int src2, char spec) {
    char *str = malloc(100);
    char *str2 = malloc(100);
    char *format;
    for (int i = 0; i < 32; i++) {
        mod.left_alignment = i & 1;
        mod.positive_sign = (i >> 1) & 1;
        mod.space_instead_of_sign = (i >> 2) & 1;
        mod.oct_hex_notation = (i >> 3) & 1;
        mod.fill_with_nulls = (i >> 4) & 1;

        format = format_maker(&mod, spec);

        strcpy(str, src);
        str = apply_format(str, &mod, spec);
        sprintf(str2, format, src2);

        // DEBUG
        str = strcat(str, format);
        str2 = strcat(str2, format);
        // END DEBUG

        ck_assert_str_eq(str, str2);
        free(format);
    }

    free(str);
    free(str2);
}



char *format_maker(modifiers *mod, char ch) {
    char *res = (char *)malloc(40);
    res[0] = '%';
    int i = 1;
    if (s21_strchr("dieEfgG", ch)) {
        if (mod->positive_sign) {
            res[i++] = '+';
            mod->space_instead_of_sign = false;
        } else if (mod->space_instead_of_sign) {
            res[i++] = ' ';
        }
    }
    if (s21_strchr("xXoeEfgG", ch)) {
        if (mod->oct_hex_notation) res[i++] = '#';
    }
    if (mod->left_alignment) {
        res[i++] = '-';
        mod->fill_with_nulls = false;
    } else if (mod->fill_with_nulls && s21_strchr("dieEfgGouxX", ch) && !(s21_strchr("idouxX", ch) && mod->precision != 1)) {
        res[i++] = '0';
    } else {
        mod->fill_with_nulls = false;
    }
    if (mod->width != 0) res[i++] = mod->width + '0';
    if (s21_strchr("diouxXeEfgGs", ch) && ((s21_strchr("eEfgG", ch) && mod->precision != 6) || (!s21_strchr("eEfgG", ch) && mod->precision != 1))) {
        res[i++] = '.';
        res[i++] = mod->precision + '0';
    }
    res[i++] = ch;
    res[i] = '\0';
    return res;
}

