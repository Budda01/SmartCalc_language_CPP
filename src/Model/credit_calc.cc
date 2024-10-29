#include "model.h"

namespace s21 {

int Model::AnnCreditCalc(const std::string& sum, const std::string& time,
                         const std::string& rate, std::string& output) {
  int err = 0;
  long double d_sum = std::stold(sum);
  int d_time = std::stoi(time);
  long double d_rate = std::stold(rate) / 100;
  if (d_time > 0 && d_sum > 0 && d_rate > 0) {
    long double month_pay =
        (d_sum * d_rate / 12) / (1 - std::pow(1 + d_rate / 12, -d_time));
    long double total_pay = month_pay * d_time;
    long double over_pay = total_pay - d_sum;
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << "Ежемесячный платеж: " << month_pay << "\n";
    oss << "Переплата: " << over_pay << "\n";
    oss << "Общая выплата: " << total_pay;
    output = oss.str();
  } else {
    err = 1;
  }
  return err;
}

int Model::DiffCreditCalc(const std::string& sum, const std::string& time,
                          const std::string& rate, std::string& output) {
  int err = 0;
  long double d_sum = std::stold(sum);
  long double copy_sum = d_sum;
  int d_time = std::stoi(time);
  long double d_rate = std::stold(rate);
  long double month_rate = d_rate / 12 / 100;
  long double month_pay = d_sum / d_time + d_sum * month_rate;
  long double prin_pay = 0;
  long double total_rate = 0;
  if (d_time > 0 && d_sum > 0 && d_rate > 0) {
    for (int i = 0; i < d_time; ++i) {
      long double intr_pay = d_sum * month_rate;
      prin_pay = month_pay - intr_pay;
      total_rate += intr_pay;
      d_sum -= prin_pay;
    }
    long double res_sum = copy_sum + total_rate;
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(3);
    oss << "Ежемесячный платеж: " << prin_pay << "\n";
    oss << "Начисленные проценты: " << total_rate << "\n";
    oss << "Долг + проценты: " << res_sum;
    output = oss.str();
  } else {
    err = 1;
  }
  return err;
}

}  // namespace s21