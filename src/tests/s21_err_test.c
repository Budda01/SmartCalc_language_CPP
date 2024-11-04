#include "s21_test.h"

START_TEST(err_test_1) {
  const char str[] = ") (";
  char output[256];
  int res = s21_smart_calc(str, output);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(err_test_2) {
  const char str[] = "2.2.3 +2";
  char output[256];
  int res = s21_smart_calc(str, output);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(err_test_3) {
  const char str[] = "(2.2)) (+2";
  char output[256];
  int res = s21_smart_calc(str, output);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(err_test_4) {
  const char str[] = "2/(5-5)";
  char output[256];
  int res = s21_smart_calc(str, output);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(err_test_5) {
  const char str[] = "1adfdg";
  char output[256];
  int res = s21_smart_calc(str, output);
  ;
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(err_test_6) {
  const char str[] = "2 / 1";
  char output[256];
  int res = s21_smart_calc(str, output);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(err_test_7) {
  const char str[] = "2 / 0";
  char output[256];
  int res = s21_smart_calc(str, output);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(err_test_8) {
  const char str[] = "2 -- 2";
  char output[256];
  int res = s21_smart_calc(str, output);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(err_test_9) {
  const char str[] =
      "2+234+45*41+2+234+45*41+2+234+45*41+2+234+45*41+2+234+45*41+2+234+45*41+"
      "2+234+45*41+2+234+45*41+2+234+45*41+2+234+45*41+2+234+45*41+2+234+45*41+"
      "2+234+45*41+2+234+45*41+2+234+45*41+2+234+45*41+2+234+45*41+2+234+45*41+"
      "2+234+45*41+2+234+45*41+2+234+45*41+2+234+45*41+2+234+45*41+2+234+45*41+"
      "2+234+45*41";
  char output[256];
  int res = s21_smart_calc(str, output);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(err_test_10) {
  const char str[] = "2+2*";
  char output[256];
  int res = s21_smart_calc(str, output);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(err_test_11) {
  const char str[] = "+";
  char output[256];
  int res = s21_smart_calc(str, output);
  ck_assert_int_eq(res, 1);
}
END_TEST

Suite* s21_err_test(void) {
  Suite* s;
  s = suite_create("\033[33ms21_err\033[0m");
  TCase* tc_core;
  tc_core = tcase_create("s21_err_core");
  tcase_add_test(tc_core, err_test_1);
  tcase_add_test(tc_core, err_test_2);
  tcase_add_test(tc_core, err_test_3);
  tcase_add_test(tc_core, err_test_4);
  tcase_add_test(tc_core, err_test_5);
  tcase_add_test(tc_core, err_test_6);
  tcase_add_test(tc_core, err_test_7);
  tcase_add_test(tc_core, err_test_8);
  tcase_add_test(tc_core, err_test_9);
  tcase_add_test(tc_core, err_test_10);
  tcase_add_test(tc_core, err_test_11);
  suite_add_tcase(s, tc_core);

  return s;
}
