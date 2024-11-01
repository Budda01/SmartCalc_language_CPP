#include "model.h"

namespace s21 {

double Model::ProcessDigit(const char** str) {
  double num = 0;
  num = StrToDouble(*str);
  int counter_dots = 0;
  while ((**str >= '0' && **str <= '9') || **str == '.') {
    if (**str == '.') counter_dots++;
    (*str)++;
  }
  return counter_dots > 1 ? -1 : num;
}

int Model::CheckForOper(NodeType type) {
  int res = 0;
  if (type <= 8) res = 1;
  return res;
}

int Model::MinorChanges(Model::Stack& string) {
  int err = 0;
  std::deque<Model::Node> buff;
  int size = string.stack_data.size();
  int count_digits = 0;
  int count_bin_op = 0;
  while (!string.stack_data.empty()) {
    buff.push_front(string.stack_data.top());
    string.stack_data.pop();
  }
  if (size == 1 && buff[0].type != DIGIT) err = 1;
  for (int i = 0; err == 0 && i < size - 1; i++) {
    if ((buff[i].type == DIGIT &&
         (buff[i + 1].type >= 9 && buff[i + 1].type <= 18)) ||
        (buff[i].type == CL_BRACKET && buff[i + 1].type == DIGIT) ||
        (buff[i].type == CL_BRACKET && buff[i + 1].type == OP_BRACKET)) {
      Model::Node mul(Model::MUL, 2, 0);
      buff.insert(buff.begin() + i + 1, mul);
      size++;
    }
  }
  int add_count = 1;
  for (int i = 0; i < size; i++) {
    if (buff[i].type == POW && i + 2 < size && buff[i + 2].type == POW) {
      buff[i + 2].priority += add_count;
      add_count++;
    }
    if (buff[i].type == DIGIT) count_digits++;
    if (buff[i].type < 7) count_bin_op++;
  }
  if ((count_digits - count_bin_op) != 1) err = 1;
  for (int i = size - 1; i >= 0; --i) {
    string.stack_data.push(buff[i]);
  }
  return err;
}

double Model::StrToDouble(const char* string) {
  double value = 0;
  int check_for_dot = 0;
  int dot_pos = 0;

  for (int i = 0; (string[i] < 58 && string[i] > 47) || string[i] == '.'; i++) {
    if (string[i] >= 48 && string[i] <= 57) {
      if (check_for_dot == 0) {
        value = (string[i] - 48) + value * 10;
      } else if (check_for_dot == 1) {
        value += ((string[i] - 48) * pow(10, dot_pos - i));
      }
    } else if (string[i] == '.') {
      check_for_dot = 1;
      dot_pos = i;
    }
  }
  return value;
}

int Model::ParseSymbols(const char** str, Model::Stack& string) {
  int err = 0;
  if (**str == ' ') {
    (*str)++;
  } else if (**str >= '0' && **str <= '9' && string.last_index != DIGIT) {
    string.last_index = DIGIT;
    double num = ProcessDigit(str);
    if (num == -1) {
      err = 1;
    } else {
      Model::Node node(Model::DIGIT, 0, num);
      string.stack_data.push(node);
    }
  } else if (**str == '(') {
    string.last_index = OP_BRACKET;
    Model::Node node(Model::OP_BRACKET, 0, 0);
    string.stack_data.push(node);
    string.check_brt += 1;
    (*str)++;
  } else if (**str == ')' && string.check_brt &&
             string.last_index != OP_BRACKET) {
    string.last_index = CL_BRACKET;
    Model::Node node(Model::CL_BRACKET, 0, 0);
    string.stack_data.push(node);
    string.check_brt -= 1;
    (*str)++;
  } else if (err == 0) {
    err = ParseUnOp(str, string);
  }
  return err;
}

int Model::ParseUnOp(const char** str, Model::Stack& string) {
  int err = 0;
  if (**str == '+' &&
      (string.last_index == FIRST_SYM || string.last_index == OP_BRACKET)) {
    string.last_index = UNAR_P;
    Model::Node node(Model::UNAR_P, 5, 0);
    string.stack_data.push(node);
    (*str)++;
  } else if (**str == '-' && (string.last_index == FIRST_SYM ||
                              string.last_index == OP_BRACKET)) {
    string.last_index = UNAR_M;
    Model::Node node(Model::UNAR_M, 5, 0);
    string.stack_data.push(node);
    (*str)++;
  } else if (strncmp(*str, "sqrt(", 5) == 0) {
    string.last_index = SQRT;
    Model::Node node(Model::SQRT, 5, 0);
    string.stack_data.push(node);
    (*str) += 4;
  } else if (strncmp(*str, "ln(", 3) == 0) {
    string.last_index = LN;
    Model::Node node(Model::LN, 5, 0);
    string.stack_data.push(node);
    (*str) += 2;
  } else if (strncmp(*str, "log(", 4) == 0) {
    string.last_index = LOG;
    Model::Node node(Model::LOG, 5, 0);
    string.stack_data.push(node);
    (*str) += 3;
  } else if (ParseBinOp(str, string))
    err = 1;
  return err;
}

int Model::ParseBinOp(const char** str, Model::Stack& string) {
  int err = 0;
  if (**str == '+' && !CheckForOper(string.last_index)) {
    string.last_index = PLUS;
    Model::Node node(Model::PLUS, 1, 0);
    string.stack_data.push(node);
    (*str)++;
  } else if (**str == '-' && !CheckForOper(string.last_index)) {
    string.last_index = MINUS;
    Model::Node node(Model::MINUS, 1, 0);
    string.stack_data.push(node);
    (*str)++;
  } else if (**str == '/' && !CheckForOper(string.last_index)) {
    string.last_index = DIV;
    Model::Node node(Model::DIV, 2, 0);
    string.stack_data.push(node);
    (*str)++;
  } else if (**str == '*' && !CheckForOper(string.last_index)) {
    string.last_index = MUL;
    Model::Node node(Model::MUL, 2, 0);
    string.stack_data.push(node);
    (*str)++;
  } else if (**str == '^' && !CheckForOper(string.last_index)) {
    string.last_index = POW;
    Model::Node node(Model::POW, 3, 0);
    string.stack_data.push(node);
    (*str)++;
  } else if (strncmp(*str, "mod", 3) == 0 && !CheckForOper(string.last_index)) {
    string.last_index = MOD;
    Model::Node node(Model::MOD, 2, 0);
    string.stack_data.push(node);
    (*str) += 3;
  } else if (ParseTrigFunc(str, string)) {
    err = 1;
  }
  return err;
}

int Model::ParseTrigFunc(const char** str, Model::Stack& string) {
  int err = 0;
  if (strncmp(*str, "sin(", 4) == 0) {
    string.last_index = SIN;
    Model::Node node(Model::SIN, 5, 0);
    string.stack_data.push(node);
    (*str) += 3;
  } else if (strncmp(*str, "cos(", 4) == 0) {
    string.last_index = COS;
    Model::Node node(Model::COS, 5, 0);
    string.stack_data.push(node);
    (*str) += 3;
  } else if (strncmp(*str, "tan(", 4) == 0) {
    string.last_index = SIN;
    Model::Node node(Model::TAN, 5, 0);
    string.stack_data.push(node);
    (*str) += 3;
  } else if (strncmp(*str, "asin(", 5) == 0) {
    string.last_index = ASIN;
    Model::Node node(Model::ASIN, 5, 0);
    string.stack_data.push(node);
    (*str) += 4;
  } else if (strncmp(*str, "acos(", 5) == 0) {
    string.last_index = ACOS;
    Model::Node node(Model::ACOS, 5, 0);
    string.stack_data.push(node);
    (*str) += 4;
  } else if (strncmp(*str, "atan(", 5) == 0) {
    string.last_index = ATAN;
    Model::Node node(Model::ATAN, 5, 0);
    string.stack_data.push(node);
    (*str) += 4;
  } else
    err = 1;
  return err;
}

void Model::Transform(Model::Stack& string, std::deque<Model::Node>& queue) {
  Model::Stack stack;
  while (!string.stack_data.empty()) {
    Node cur_node = string.stack_data.top();
    if (cur_node.type == DIGIT) {
      queue.push_back(cur_node);
    } else if (cur_node.type == OP_BRACKET) {
      stack.stack_data.push(cur_node);
    } else if (cur_node.type == CL_BRACKET) {
      ProcBracket(stack, queue);
    } else if (cur_node.priority <= stack.stack_data.top().priority) {
      ProcPriority(stack, queue, cur_node);
    } else if (stack.stack_data.empty() ||
               stack.stack_data.top().type == OP_BRACKET) {
      stack.stack_data.push(cur_node);
    } else if (string.stack_data.top().priority >
               stack.stack_data.top().priority) {
      stack.stack_data.push(cur_node);
    }
    string.stack_data.pop();
  }
  while (!stack.stack_data.empty()) {
    queue.push_back(stack.stack_data.top());
    stack.stack_data.pop();
  }
}

void Model::ProcPriority(Model::Stack& stack, std::deque<Model::Node>& queue,
                         Node cur_node) {
  while (!stack.stack_data.empty() &&
         stack.stack_data.top().type != OP_BRACKET &&
         stack.stack_data.top().priority >= cur_node.priority) {
    queue.push_back(stack.stack_data.top());
    stack.stack_data.pop();
  }
  stack.stack_data.push(cur_node);
}

void Model::ProcBracket(Model::Stack& stack, std::deque<Model::Node>& queue) {
  while (!stack.stack_data.empty() &&
         stack.stack_data.top().type != OP_BRACKET) {
    queue.push_back(stack.stack_data.top());
    stack.stack_data.pop();
  }
  stack.stack_data.pop();
}

int Model::ToPostfix(const char* str, std::deque<Model::Node>& queue) {
  int err = 0;
  if (strlen(str) != 0 && strlen(str) < 256) {
    Model::Stack string;
    string.last_index = FIRST_SYM;
    string.check_brt = 0;
    while (*str != '\0' && err != 1) {
      if (ParseSymbols(&str, string)) err = 1;
    }
    if (err == 0 && string.check_brt == 0) {
      err = MinorChanges(string);
      Transform(string, queue);
    } else
      err = 1;
  }
  return err;
}
}  // namespace s21
