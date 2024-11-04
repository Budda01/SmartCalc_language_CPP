#ifndef S21_TEST_H
#define S21_TEST_H

#include <check.h>

#include "../s21_SmartCalc.h"
#define EPS 0.0000001

Suite *s21_calculation_test(void);
Suite *s21_err_test(void);

#endif