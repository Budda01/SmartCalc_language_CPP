#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdexcept>

#include "../Model/model.h"

namespace s21 {

class Controller {
 public:
  Controller(Model* model) : model_(model) {}
  std::string Executor(const std::string input);
  std::string CreditExecutor(int mode, const std::string sum,
                             const std::string time, const std::string rate);

 private:
  Model* model_;
};

}  // namespace s21

#endif  // CONTROLLER_H