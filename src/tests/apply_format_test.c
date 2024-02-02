#include "s21_string_test.h"

// c
START_TEST(test_apply_format_c_basic) {
	modifiers mod = {0};
    mod.precision = 1;
    test_all_falgs_d(mod, "0", '0', 'c');
    test_all_falgs_d(mod, "z", 'z', 'c');
    test_all_falgs_d(mod, "", '\0', 'c');
}
END_TEST

START_TEST(test_apply_format_c_width) {
	modifiers mod = {0};
	mod.width = 6;
    test_all_falgs_d(mod, "0", '0', 'c');
    test_all_falgs_d(mod, "z", 'z', 'c');
}
END_TEST


// d
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
    test_all_falgs_d(mod, "0", 0, 'd');
    test_all_falgs_d(mod, "5", 5, 'd');
    test_all_falgs_d(mod, "-47", -47, 'd');
}
END_TEST

START_TEST(test_apply_format_d_width_and_precision) {
	modifiers mod = {0};
	mod.width = 8;
    mod.precision = 4;
    test_all_falgs_d(mod, "0", 0, 'd');
    test_all_falgs_d(mod, "5", 5, 'd');
    test_all_falgs_d(mod, "-47", -47, 'd');
}
END_TEST

// i
START_TEST(test_apply_format_i_basic) {
	modifiers mod = {0};
    mod.precision = 1;
    test_all_falgs_d(mod, "0", 0, 'i');
    test_all_falgs_d(mod, "346", 346, 'i');
    test_all_falgs_d(mod, "-3", -3, 'i');
}
END_TEST

START_TEST(test_apply_format_i_precision) {
	modifiers mod = {0};
	mod.precision = 6;
    test_all_falgs_d(mod, "0", 0, 'i');
    test_all_falgs_d(mod, "346", 346, 'i');
    test_all_falgs_d(mod, "-3", -3, 'i');
}
END_TEST

START_TEST(test_apply_format_i_width) {
	modifiers mod = {0};
	mod.width = 6;
    mod.precision = 1;
    test_all_falgs_d(mod, "0", 0, 'i');
    test_all_falgs_d(mod, "346", 346, 'i');
    test_all_falgs_d(mod, "-3", -3, 'i');
}
END_TEST

START_TEST(test_apply_format_i_width_and_precision) {
	modifiers mod = {0};
	mod.width = 8;
    mod.precision = 4;
    test_all_falgs_d(mod, "0", 0, 'i');
    test_all_falgs_d(mod, "346", 346, 'i');
    test_all_falgs_d(mod, "-3", -3, 'i');
}
END_TEST


// o
START_TEST(test_apply_format_o_basic) {
	modifiers mod = {0};
    mod.precision = 1;
    test_all_falgs_d(mod, "0", 00, 'o');
    test_all_falgs_d(mod, "47", 047, 'o');
    test_all_falgs_d(mod, "1", 01, 'o');
}
END_TEST

START_TEST(test_apply_format_o_precision) {
	modifiers mod = {0};
	mod.precision = 6;
    test_all_falgs_d(mod, "0", 00, 'o');
    test_all_falgs_d(mod, "47", 047, 'o');
    test_all_falgs_d(mod, "1", 01, 'o');
}
END_TEST

START_TEST(test_apply_format_o_width) {
	modifiers mod = {0};
	mod.width = 6;
    mod.precision = 1;
    test_all_falgs_d(mod, "0", 00, 'o');
    test_all_falgs_d(mod, "47", 047, 'o');
    test_all_falgs_d(mod, "1", 01, 'o');
}
END_TEST

START_TEST(test_apply_format_o_width_and_precision) {
	modifiers mod = {0};
	mod.width = 8;
    mod.precision = 4;
    test_all_falgs_d(mod, "0", 00, 'o');
    test_all_falgs_d(mod, "47", 047, 'o');
    test_all_falgs_d(mod, "1", 01, 'o');
}
END_TEST

// u
START_TEST(test_apply_format_u_basic) {
	modifiers mod = {0};
    mod.precision = 1;
    test_all_falgs_d(mod, "0", 0, 'u');
    test_all_falgs_d(mod, "47", 47, 'u');
    test_all_falgs_d(mod, "1", 1, 'u');
}
END_TEST

START_TEST(test_apply_format_u_precision) {
	modifiers mod = {0};
	mod.precision = 6;
    test_all_falgs_d(mod, "0", 0, 'u');
    test_all_falgs_d(mod, "47", 47, 'u');
    test_all_falgs_d(mod, "1", 1, 'u');
}
END_TEST

START_TEST(test_apply_format_u_width) {
	modifiers mod = {0};
	mod.width = 6;
    mod.precision = 1;
    test_all_falgs_d(mod, "0", 0, 'u');
    test_all_falgs_d(mod, "47", 47, 'u');
    test_all_falgs_d(mod, "1", 1, 'u');
}
END_TEST

START_TEST(test_apply_format_u_width_and_precision) {
	modifiers mod = {0};
	mod.width = 8;
    mod.precision = 4;
    test_all_falgs_d(mod, "0", 0, 'u');
    test_all_falgs_d(mod, "47", 47, 'u');
    test_all_falgs_d(mod, "1", 1, 'u');
}
END_TEST

// x
START_TEST(test_apply_format_x_basic) {
	modifiers mod = {0};
    mod.precision = 1;
    test_all_falgs_d(mod, "0", 0x0, 'x');
    test_all_falgs_d(mod, "4c2", 0x4c2, 'x');
    test_all_falgs_d(mod, "fe", 0xfe, 'x');
}
END_TEST

START_TEST(test_apply_format_x_precision) {
	modifiers mod = {0};
	mod.precision = 6;
    test_all_falgs_d(mod, "0", 0x0, 'x');
    test_all_falgs_d(mod, "4c2", 0x4c2, 'x');
    test_all_falgs_d(mod, "fe", 0xfe, 'x');
}
END_TEST

START_TEST(test_apply_format_x_width) {
	modifiers mod = {0};
	mod.width = 6;
    mod.precision = 1;
    test_all_falgs_d(mod, "0", 0x0, 'x');
    test_all_falgs_d(mod, "4c2", 0x4c2, 'x');
    test_all_falgs_d(mod, "fe", 0xfe, 'x');
}
END_TEST

START_TEST(test_apply_format_x_width_and_precision) {
	modifiers mod = {0};
	mod.width = 9;
    mod.precision = 5;
    test_all_falgs_d(mod, "0", 0x0, 'x');
    test_all_falgs_d(mod, "4c2", 0x4c2, 'x');
    test_all_falgs_d(mod, "fe", 0xfe, 'x');
}
END_TEST

// X
START_TEST(test_apply_format_X_basic) {
	modifiers mod = {0};
    mod.precision = 1;
    test_all_falgs_d(mod, "0", 0x0, 'X');
    test_all_falgs_d(mod, "1A", 0x1A, 'X');
    test_all_falgs_d(mod, "EE", 0xEE, 'X');
}
END_TEST

START_TEST(test_apply_format_X_precision) {
	modifiers mod = {0};
	mod.precision = 6;
    test_all_falgs_d(mod, "0", 0x0, 'X');
    test_all_falgs_d(mod, "1A", 0x1A, 'X');
    test_all_falgs_d(mod, "EE", 0xEE, 'X');
}
END_TEST

START_TEST(test_apply_format_X_width) {
	modifiers mod = {0};
	mod.width = 6;
    mod.precision = 1;
    test_all_falgs_d(mod, "0", 0x0, 'X');
    test_all_falgs_d(mod, "1A", 0x1A, 'X');
    test_all_falgs_d(mod, "EE", 0xEE, 'X');
}
END_TEST

START_TEST(test_apply_format_X_width_and_precision) {
	modifiers mod = {0};
	mod.width = 9;
    mod.precision = 5;
    test_all_falgs_d(mod, "0", 0x0, 'X');
    test_all_falgs_d(mod, "1A", 0x1A, 'X');
    test_all_falgs_d(mod, "EE", 0xEE, 'X');
}
END_TEST

// e
START_TEST(test_apply_format_e_basic) {
	modifiers mod = {0};
    mod.precision = 6;
    test_all_falgs_double(mod, "0.02", 0.02, 'e');
    test_all_falgs_double(mod, "42141.957", 42141.957, 'e');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'e');
    test_all_falgs_double(mod, "1.3121257", 1.3121257, 'e');
    test_all_falgs_double(mod, "0.0", 0.0, 'e');
    test_all_falgs_double(mod, "-1.999999232", -1.999999232, 'e');
}
END_TEST

START_TEST(test_apply_format_e_precision) {
	modifiers mod = {0};
	mod.precision = 0;
    test_all_falgs_double(mod, "0.02", 0.02, 'e');
    test_all_falgs_double(mod, "45141.957", 45141.957, 'e');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'e');
    test_all_falgs_double(mod, "1.3121257", 1.3121257, 'e');
    test_all_falgs_double(mod, "0.0", 0.0, 'e');
    test_all_falgs_double(mod, "-1.999999232", -1.999999232, 'e');
}
END_TEST

START_TEST(test_apply_format_e_width) {
	modifiers mod = {0};
	mod.width = 9;
    mod.precision = 4;
    test_all_falgs_double(mod, "0.02", 0.02, 'e');
    test_all_falgs_double(mod, "42141.957", 42141.957, 'e');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'e');
    test_all_falgs_double(mod, "1.3121257", 1.3121257, 'e');
    test_all_falgs_double(mod, "0.0", 0.0, 'e');
    test_all_falgs_double(mod, "-1.999999232", -1.999999232, 'e');
}
END_TEST

START_TEST(test_apply_format_e_width_and_precision) {
	modifiers mod = {0};
	mod.width = 9;
    mod.precision = 3;
    test_all_falgs_double(mod, "0.02", 0.02, 'e');
    test_all_falgs_double(mod, "42141.957", 42141.957, 'e');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'e');
    test_all_falgs_double(mod, "1.3121257", 1.3121257, 'e');
    test_all_falgs_double(mod, "0.0", 0.0, 'e');
    test_all_falgs_double(mod, "-1.999999232", -1.999999232, 'e');
}
END_TEST

// E
START_TEST(test_apply_format_E_basic) {
	modifiers mod = {0};
    mod.precision = 6;
    test_all_falgs_double(mod, "1.000009", 1.000009, 'E');
    test_all_falgs_double(mod, "-99999.057", -99999.057, 'E');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'E');
    test_all_falgs_double(mod, "1.1795464", 1.1795464, 'E');
    test_all_falgs_double(mod, "0.00000000", 0.00000000, 'E');
    test_all_falgs_double(mod, "-1.999999232", -1.999999232, 'E');
}
END_TEST

START_TEST(test_apply_format_E_precision) {
	modifiers mod = {0};
	mod.precision = 0;
    test_all_falgs_double(mod, "1.000009", 1.000009, 'E');
    test_all_falgs_double(mod, "-99999.057", -99999.057, 'E');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'E');
    test_all_falgs_double(mod, "1.1795464", 1.1795464, 'E');
    test_all_falgs_double(mod, "0.00000000", 0.00000000, 'E');
    test_all_falgs_double(mod, "-1.999999232", -1.999999232, 'E');
}
END_TEST

START_TEST(test_apply_format_E_width) {
	modifiers mod = {0};
	mod.width = 9;
    mod.precision = 5;
    test_all_falgs_double(mod, "1.000009", 1.000009, 'E');
    test_all_falgs_double(mod, "-99999.057", -99999.057, 'E');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'E');
    test_all_falgs_double(mod, "1.1795464", 1.1795464, 'E');
    test_all_falgs_double(mod, "0.00000000", 0.00000000, 'E');
    test_all_falgs_double(mod, "-1.999999232", -1.999999232, 'E');
}
END_TEST

START_TEST(test_apply_format_E_width_and_precision) {
	modifiers mod = {0};
	mod.width = 9;
    mod.precision = 3;
    test_all_falgs_double(mod, "1.000009", 1.000009, 'E');
    test_all_falgs_double(mod, "-99999.057", -99999.057, 'E');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'E');
    test_all_falgs_double(mod, "1.1795464", 1.1795464, 'E');
    test_all_falgs_double(mod, "0.00000000", 0.00000000, 'E');
    test_all_falgs_double(mod, "-1.999999232", -1.999999232, 'E');
}
END_TEST

// f
START_TEST(test_apply_format_f_basic) {
	modifiers mod = {0};
    mod.precision = 6;
    test_all_falgs_double(mod, "0.02", 0.02, 'f');
    test_all_falgs_double(mod, "42141.957", 42141.957, 'f');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'f');
    test_all_falgs_double(mod, "1.3121257", 1.3121257, 'f');
    test_all_falgs_double(mod, "0.0", 0.0, 'f');
    test_all_falgs_double(mod, "-1.1259232", -1.1259232, 'f');
}
END_TEST

START_TEST(test_apply_format_f_precision) {
	modifiers mod = {0};
	mod.precision = 0;
    test_all_falgs_double(mod, "0.02", 0.02, 'f');
    test_all_falgs_double(mod, "42141.957", 42141.957, 'f');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'f');
    test_all_falgs_double(mod, "1.3121257", 1.3121257, 'f');
    test_all_falgs_double(mod, "0.0", 0.0, 'f');
    test_all_falgs_double(mod, "-1.1259232", -1.1259232, 'f');
}
END_TEST

START_TEST(test_apply_format_f_width) {
	modifiers mod = {0};
	mod.width = 9;
    mod.precision = 6;
    test_all_falgs_double(mod, "0.02", 0.02, 'f');
    test_all_falgs_double(mod, "42141.957", 42141.957, 'f');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'f');
    test_all_falgs_double(mod, "1.3121257", 1.3121257, 'f');
    test_all_falgs_double(mod, "0.0", 0.0, 'f');
    test_all_falgs_double(mod, "-1.1259232", -1.1259232, 'f');
}
END_TEST

START_TEST(test_apply_format_f_width_and_precision) {
	modifiers mod = {0};
	mod.width = 9;
    mod.precision = 3;
    test_all_falgs_double(mod, "0.02", 0.02, 'f');
    test_all_falgs_double(mod, "42141.957", 42141.957, 'f');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'f');
    test_all_falgs_double(mod, "1.3121257", 1.3121257, 'f');
    test_all_falgs_double(mod, "0.0", 0.0, 'f');
    test_all_falgs_double(mod, "-1.1259232", -1.1259232, 'f');
}
END_TEST

// g
START_TEST(test_apply_format_g_basic) {
	modifiers mod = {0};
    mod.precision = 6;
    test_all_falgs_double(mod, "0.02", 0.02, 'g');
    test_all_falgs_double(mod, "42141.957", 42141.957, 'g');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'g');
    test_all_falgs_double(mod, "1.3121257", 1.3121257, 'g');
    test_all_falgs_double(mod, "0.0", 0.0, 'g');
    test_all_falgs_double(mod, "-1.999999232", -1.999999232, 'g');
}
END_TEST

START_TEST(test_apply_format_g_precision) {
	modifiers mod = {0};
	mod.precision = 0;
    test_all_falgs_double(mod, "0.02", 0.02, 'g');
    test_all_falgs_double(mod, "42141.957", 42141.957, 'g');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'g');
    test_all_falgs_double(mod, "1.3121257", 1.3121257, 'g');
    test_all_falgs_double(mod, "0.0", 0.0, 'g');
    test_all_falgs_double(mod, "-1.999999232", -1.999999232, 'g');
}
END_TEST

START_TEST(test_apply_format_g_width) {
	modifiers mod = {0};
	mod.width = 9;
    mod.precision = 4;
    test_all_falgs_double(mod, "0.02", 0.02, 'g');
    test_all_falgs_double(mod, "42141.957", 42141.957, 'g');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'g');
    test_all_falgs_double(mod, "1.3121257", 1.3121257, 'g');
    test_all_falgs_double(mod, "0.0", 0.0, 'g');
    test_all_falgs_double(mod, "-1.999999232", -1.999999232, 'g');
}
END_TEST

START_TEST(test_apply_format_g_width_and_precision) {
	modifiers mod = {0};
	mod.width = 9;
    mod.precision = 3;
    test_all_falgs_double(mod, "0.02", 0.02, 'g');
    test_all_falgs_double(mod, "42141.957", 42141.957, 'g');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'g');
    test_all_falgs_double(mod, "1.3121257", 1.3121257, 'g');
    test_all_falgs_double(mod, "0.0", 0.0, 'g');
    test_all_falgs_double(mod, "-1.999999232", -1.999999232, 'g');
}
END_TEST


// G
START_TEST(test_apply_format_G_basic) {
	modifiers mod = {0};
    mod.precision = 6;
    test_all_falgs_double(mod, "-0.00059999999", -0.00059999999, 'G');
    test_all_falgs_double(mod, "-0.0005", -0.0005, 'G');
    test_all_falgs_double(mod, "99999.957", 99999.957, 'G');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'G');
    test_all_falgs_double(mod, "1.54120400002123", 1.54120400002123, 'G');
    test_all_falgs_double(mod, "0.0", 0.0, 'G');
    test_all_falgs_double(mod, "-321.5569232", -321.5569232, 'G');
}
END_TEST

START_TEST(test_apply_format_G_precision) {
	modifiers mod = {0};
	mod.precision = 0;
    test_all_falgs_double(mod, "-0.0005", -0.0005, 'G');
    test_all_falgs_double(mod, "99999.957", 99999.957, 'G');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'G');
    test_all_falgs_double(mod, "1.54120400002123", 1.54120400002123, 'G');
    test_all_falgs_double(mod, "0.0", 0.0, 'G');
    test_all_falgs_double(mod, "-321.5569232", -321.5569232, 'G');
}
END_TEST

START_TEST(test_apply_format_G_width) {
	modifiers mod = {0};
	mod.width = 9;
    mod.precision = 2;
    test_all_falgs_double(mod, "-0.0005", -0.0005, 'G');
    test_all_falgs_double(mod, "99999.957", 99999.957, 'G');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'G');
    test_all_falgs_double(mod, "1.54120400002123", 1.54120400002123, 'G');
    test_all_falgs_double(mod, "0.0", 0.0, 'G');
    test_all_falgs_double(mod, "-321.5569232", -321.5569232, 'G');
}
END_TEST

START_TEST(test_apply_format_G_width_and_precision) {
	modifiers mod = {0};
	mod.width = 9;
    mod.precision = 7;
    test_all_falgs_double(mod, "-0.0005", -0.0005, 'G');
    test_all_falgs_double(mod, "99999.957", 99999.957, 'G');
    test_all_falgs_double(mod, "-9.9999999", -9.9999999, 'G');
    test_all_falgs_double(mod, "1.54120400002123", 1.54120400002123, 'G');
    test_all_falgs_double(mod, "0.0", 0.0, 'G');
    test_all_falgs_double(mod, "-321.5569232", -321.5569232, 'G');
}
END_TEST



// s
START_TEST(test_apply_format_s_basic) {
	modifiers mod = {0};
    mod.precision = -1;
    test_all_falgs_string(mod, "qwe", "qwe", 's');
    test_all_falgs_string(mod, "", "", 's');
    test_all_falgs_string(mod, "-99999.957", "-99999.957", 's');
    test_all_falgs_string(mod, "-^&%!^#&YH%T!O#H!#HG!*&(Y)(&$!@T$)", "-^&%!^#&YH%T!O#H!#HG!*&(Y)(&$!@T$)", 's');
}
END_TEST

START_TEST(test_apply_format_s_precision) {
	modifiers mod = {0};
	mod.precision = 0;
    test_all_falgs_string(mod, "qwe", "qwe", 's');
    test_all_falgs_string(mod, "", "", 's');
    test_all_falgs_string(mod, "-99999.957", "-99999.957", 's');
    test_all_falgs_string(mod, "-^&%!^#&YH%T!O#H!#HG!*&(Y)(&$!@T$)", "-^&%!^#&YH%T!O#H!#HG!*&(Y)(&$!@T$)", 's');
}
END_TEST

START_TEST(test_apply_format_s_width) {
	modifiers mod = {0};
	mod.width = 9;
    mod.precision = -1;
    test_all_falgs_string(mod, "qwe", "qwe", 's');
    test_all_falgs_string(mod, "", "", 's');
    test_all_falgs_string(mod, "-99999.957", "-99999.957", 's');
    test_all_falgs_string(mod, "-^&%!^#&YH%T!O#H!#HG!*&(Y)(&$!@T$)", "-^&%!^#&YH%T!O#H!#HG!*&(Y)(&$!@T$)", 's');
}
END_TEST

START_TEST(test_apply_format_s_width_and_precision) {
	modifiers mod = {0};
	mod.width = 9;
    mod.precision = 7;
    test_all_falgs_string(mod, "qwe", "qwe", 's');
    test_all_falgs_string(mod, "", "", 's');
    test_all_falgs_string(mod, "-99999.957", "-99999.957", 's');
    test_all_falgs_string(mod, "-^&%!^#&YH%T!O#H!#HG!*&(Y)(&$!@T$)", "-^&%!^#&YH%T!O#H!#HG!*&(Y)(&$!@T$)", 's');
}
END_TEST

Suite *s21_apply_format_suite() {
  Suite *suite;
  TCase *tc_core;
  suite = suite_create("s21_apply_format");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_apply_format_c_basic);
  tcase_add_test(tc_core, test_apply_format_c_width);
  tcase_add_test(tc_core, test_apply_format_d_basic);
  tcase_add_test(tc_core, test_apply_format_d_precision);
  tcase_add_test(tc_core, test_apply_format_d_width);
  tcase_add_test(tc_core, test_apply_format_d_width_and_precision);
  tcase_add_test(tc_core, test_apply_format_i_basic);
  tcase_add_test(tc_core, test_apply_format_i_precision);
  tcase_add_test(tc_core, test_apply_format_i_width);
  tcase_add_test(tc_core, test_apply_format_i_width_and_precision);
  tcase_add_test(tc_core, test_apply_format_o_basic);
  tcase_add_test(tc_core, test_apply_format_o_precision);
  tcase_add_test(tc_core, test_apply_format_o_width);
  tcase_add_test(tc_core, test_apply_format_o_width_and_precision);
  tcase_add_test(tc_core, test_apply_format_u_basic);
  tcase_add_test(tc_core, test_apply_format_u_precision);
  tcase_add_test(tc_core, test_apply_format_u_width);
  tcase_add_test(tc_core, test_apply_format_u_width_and_precision);
  tcase_add_test(tc_core, test_apply_format_x_basic);
  tcase_add_test(tc_core, test_apply_format_x_precision);
  tcase_add_test(tc_core, test_apply_format_x_width);
  tcase_add_test(tc_core, test_apply_format_x_width_and_precision);
  tcase_add_test(tc_core, test_apply_format_X_basic);
  tcase_add_test(tc_core, test_apply_format_X_precision);
  tcase_add_test(tc_core, test_apply_format_X_width);
  tcase_add_test(tc_core, test_apply_format_X_width_and_precision);
  tcase_add_test(tc_core, test_apply_format_e_basic);
  tcase_add_test(tc_core, test_apply_format_e_precision);
  tcase_add_test(tc_core, test_apply_format_e_width);
  tcase_add_test(tc_core, test_apply_format_e_width_and_precision);
  tcase_add_test(tc_core, test_apply_format_E_basic);
  tcase_add_test(tc_core, test_apply_format_E_precision);
  tcase_add_test(tc_core, test_apply_format_E_width);
  tcase_add_test(tc_core, test_apply_format_E_width_and_precision);
  tcase_add_test(tc_core, test_apply_format_f_basic);
  tcase_add_test(tc_core, test_apply_format_f_precision);
  tcase_add_test(tc_core, test_apply_format_f_width);
  tcase_add_test(tc_core, test_apply_format_f_width_and_precision);
  tcase_add_test(tc_core, test_apply_format_g_basic);
  tcase_add_test(tc_core, test_apply_format_g_precision);
  tcase_add_test(tc_core, test_apply_format_g_width);
  tcase_add_test(tc_core, test_apply_format_g_width_and_precision);
  tcase_add_test(tc_core, test_apply_format_G_basic);
  tcase_add_test(tc_core, test_apply_format_G_precision);
  tcase_add_test(tc_core, test_apply_format_G_width);
  tcase_add_test(tc_core, test_apply_format_G_width_and_precision);
  tcase_add_test(tc_core, test_apply_format_s_basic);
  tcase_add_test(tc_core, test_apply_format_s_precision);
  tcase_add_test(tc_core, test_apply_format_s_width);
  tcase_add_test(tc_core, test_apply_format_s_width_and_precision);
  
  suite_add_tcase(suite, tc_core);
  return suite;
}



void test_all_falgs_d(modifiers mod, char *src, int src2, char spec) {
    char *str2 = (char *)malloc(2000);
    char *format;
    for (int i = 0; i < 32; i++) {
        char *str = (char *)malloc((strlen(src) + 1) * sizeof(char));
        mod.left_alignment = i & 1;
        mod.positive_sign = (i >> 1) & 1;
        mod.space_instead_of_sign = (i >> 2) & 1;
        mod.oct_hex_notation = (i >> 3) & 1;
        mod.fill_with_nulls = (i >> 4) & 1;
        format = format_maker(&mod, spec);
        s21_memcpy(str, src, strlen(src) + 1);
        str = apply_format(str, mod, spec);
        sprintf(str2, format, src2);

        // DEBUG
        // str = strcat(str, format);
        // str2 = strcat(str2, format);
        // END DEBUG

        ck_assert_str_eq(str, str2);
        free(str);
        free(format);
    }
    free(str2);
}

void test_all_falgs_double(modifiers mod, char *src, double src2, char spec) {
    char *str2 = (char *)malloc(2000);
    char *format;
    for (int i = 0; i < 32; i++) {
        char *str = (char *)malloc((strlen(src) + 1) * sizeof(char));
        mod.left_alignment = i & 1;
        mod.positive_sign = (i >> 1) & 1;
        mod.space_instead_of_sign = (i >> 2) & 1;
        mod.oct_hex_notation = (i >> 3) & 1;
        mod.fill_with_nulls = (i >> 4) & 1;
        format = format_maker(&mod, spec);
        s21_memcpy(str, src, strlen(src) + 1);
        str = apply_format(str, mod, spec);
        sprintf(str2, format, src2);

        // DEBUG
        // str = strcat(str, format);
        // str2 = strcat(str2, format);
        // END DEBUG

        ck_assert_str_eq(str, str2);
        free(str);
        free(format);
    }
    free(str2);
}


void test_all_falgs_string(modifiers mod, char *src, char *src2, char spec) {
    char *str2 = (char *)malloc(2000);
    char *format;
    for (int i = 0; i < 32; i++) {
        char *str = (char *)malloc((strlen(src) + 1) * sizeof(char));
        mod.left_alignment = i & 1;
        mod.positive_sign = (i >> 1) & 1;
        mod.space_instead_of_sign = (i >> 2) & 1;
        mod.oct_hex_notation = (i >> 3) & 1;
        mod.fill_with_nulls = (i >> 4) & 1;
        format = format_maker(&mod, spec);
        s21_memcpy(str, src, strlen(src) + 1);
        str = apply_format(str, mod, spec);
        sprintf(str2, format, src2);

        // DEBUG
        // str = strcat(str, format);
        // str2 = strcat(str2, format);
        // END DEBUG

        ck_assert_str_eq(str, str2);
        free(str);
        free(format);
    }
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
        if (mod->width != 0) {
            res[i++] = '-';
            mod->fill_with_nulls = false;
        } else {
            mod->left_alignment = false;
        }
    } else if (mod->fill_with_nulls && s21_strchr("dieEfgGouxX", ch) && !(s21_strchr("idouxX", ch) && mod->precision != 1)) {
        res[i++] = '0';
    } else {
        mod->fill_with_nulls = false;
    }
    if (mod->width != 0) res[i++] = mod->width + '0';
    if (s21_strchr("diouxXeEfgGs", ch) && ((s21_strchr("eEfgG", ch) && mod->precision != 6) || (s21_strchr("diouxX", ch) && mod->precision != 1) || (ch == 's' && mod->precision != -1))) {
        res[i++] = '.';
        res[i++] = mod->precision + '0';
    }
    res[i++] = ch;
    res[i] = '\0';
    return res;
}

