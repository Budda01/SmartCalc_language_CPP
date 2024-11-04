#include "../s21_SmartCalc.h"

int ann_credit_calc(const char *sum, const char *time, const char *rate,
                    char *output) {
  int err = 0;
  char *endptr;
  long double d_sum = strtold(sum, &endptr);
  int d_time = str_to_double(time);
  long double d_rate = strtold(rate, &endptr) / 100;

  if (d_time > 0 && d_sum > 0 && d_rate > 0) {
    long double month_pay;
    month_pay = (d_sum * d_rate / 12) / (1 - pow(1 + d_rate / 12, -d_time));
    long double total_pay = month_pay * d_time;
    long double over_pay = total_pay - d_sum;
    sprintf(output,
            "Ежемесячный платеж: %.3Lf\nПереплата: %.3Lf\nОбщая выплата: %.3Lf",
            month_pay, over_pay, total_pay);
  } else {
    err = 1;
  }
  return err;
}
int diff_credit_calc(const char *sum, const char *time, const char *rate,
                     char *output) {
  int err = 0;
  char *endptr;
  long double d_sum = strtold(sum, &endptr);
  long double copy_sum = d_sum;
  int d_time = str_to_double(time);
  long double d_rate = strtold(rate, &endptr);
  long double month_rate = d_rate / 12 / 100;
  long double month_pay = d_sum / d_time + d_sum * month_rate;
  long double prin_pay = 0;
  long double total_rate = 0;
  if (d_time > 0 && d_sum > 0 && d_rate > 0) {
    for (int i = 0; i < d_time; ++i) {
      double intr_pay = d_sum * d_rate / 12 / 100;
      prin_pay = month_pay - intr_pay;
      total_rate += intr_pay;
      d_sum -= prin_pay;
    }
    long double res_sum = copy_sum + total_rate;
    sprintf(output,
            "Ежемесячный платеж: %.3Lf\nНачисленные проценты: %.3Lf\nДолг + "
            "проценты: %.3Lf",
            prin_pay, total_rate, res_sum);
  } else {
    err = 1;
  }
  return err;
}