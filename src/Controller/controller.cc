#include "controller.h"

namespace s21 {
std::string Controller::Executor(const std::string input) {
  if (model_ == nullptr) throw std::runtime_error("Model not initialized");
  std::string output;
  int err = model_->SmartCalc(input, output);
  if (err == 1)
    throw std::invalid_argument("INCORRECT INPUT");
  else if (err == 2)
    throw std::domain_error("INCORRECT OPERATION");
  else
    return output;
}

std::string Controller::CreditExecutor(int mode, const std::string sum,
                                       const std::string time,
                                       const std::string rate) {
  if (model_ == nullptr) throw std::runtime_error("Model not initialized");
  int err = 0;
  std::string output;
  if (mode == 1)
    err = model_->AnnCreditCalc(sum, time, rate, output);
  else if (mode == 2)
    err = model_->DiffCreditCalc(sum, time, rate, output);
  if (err) throw std::invalid_argument("INCORRECT INPUT");
  return output;
}

}  // namespace s21