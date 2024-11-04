#include "../s21_SmartCalc.h"

void set_node(node_type type, int priority, double value, s21_node *res) {
  res->type = type;
  res->priority = priority + 22;
  res->value = value;
}

double str_to_double(const char *string) {
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

double process_digit(const char **str) {
  double num = 0;
  num = str_to_double(*str);
  int counter_dots = 0;
  while ((**str >= '0' && **str <= '9') || **str == '.') {
    if (**str == '.') counter_dots++;
    (*str)++;
  }
  return counter_dots > 1 ? -1 : num;
}

int check_for_operation(node_type type) {
  int res = 0;
  if (type <= 8) res = 1;
  return res;
}

int get_stack_size(s21_stack *stack) {
  int count = 0;
  while (stack->stack_array[count].type != 0) {
    count++;
  }
  return count;
}

int minor_changes(s21_stack *string) {
  s21_node mul;
  int err = 0;
  int size = get_stack_size(string);
  int count_digits = 0;
  int count_bin_op = 0;
  if (size == 1 && string->stack_array[0].type != DIGIT) {
    err = 1;
  }
  for (int i = 0; err == 0 && i < size; i++) {
    if ((string->stack_array[i].type == DIGIT &&
         (string->stack_array[i + 1].type >= 9 &&
          string->stack_array[i + 1].type <= 18)) ||
        (string->stack_array[i].type == CL_BRACKET &&
         string->stack_array[i + 1].type == DIGIT) ||
        (string->stack_array[i].type == CL_BRACKET &&
         string->stack_array[i + 1].type == OP_BRACKET)) {
      set_node(MUL, 2, 0, &mul);
      s21_insert(string, &mul, i + 1);
      size++;
    }
  }
  int add_count = 1;
  for (int i = 0; i < size; i++) {
    if (string->stack_array[i].type == POW &&
        string->stack_array[i + 2].type == POW) {
      string->stack_array[i + 2].priority += add_count;
      add_count++;
    }
    if (string->stack_array[i].type == DIGIT) count_digits++;
    if (string->stack_array[i].type <= 6) count_bin_op++;
  }
  if ((count_digits - count_bin_op) != 1) err = 1;

  return err;
}

void proc_priority(s21_stack *stack, s21_stack *queue, s21_node node) {
  int i = get_stack_size(stack) - 1;
  s21_node buffer;
  while (stack->stack_array[i].type != OP_BRACKET &&
         stack->stack_array[i].priority >= node.priority) {
    s21_pop(stack, &buffer);
    s21_push(queue, &buffer);
    i--;
  }
}

void proc_bracket(s21_stack *stack, s21_stack *queue) {
  int i = get_stack_size(stack) - 1;
  s21_node buffer;
  while (stack->stack_array[i].type != OP_BRACKET) {
    s21_pop(stack, &buffer);
    s21_push(queue, &buffer);
    i--;
  }
  s21_delete(stack, i);
}

int parse_bin_op(const char **str, s21_stack *string, int *i) {
  int err = 0;
  if (**str == '+' && check_for_operation(string->last_index) == 0) {
    string->last_index = PLUS;
    set_node(PLUS, 1, 0, &(string->stack_array[*i]));
    (*i)++;
    (*str)++;
  } else if (**str == '-' && check_for_operation(string->last_index) == 0) {
    string->last_index = MINUS;
    set_node(MINUS, 1, 0, &(string->stack_array[*i]));
    (*i)++;
    (*str)++;
  } else if (**str == '/' && check_for_operation(string->last_index) == 0) {
    string->last_index = DIV;
    set_node(DIV, 2, 0, &(string->stack_array[*i]));
    (*i)++;
    (*str)++;
  } else if (**str == '*' && check_for_operation(string->last_index) == 0) {
    string->last_index = MUL;
    set_node(MUL, 2, 0, &(string->stack_array[*i]));
    (*i)++;
    (*str)++;
  } else if (**str == '^' && check_for_operation(string->last_index) == 0) {
    string->last_index = POW;
    set_node(POW, 3, 0, &(string->stack_array[*i]));
    (*i)++;
    (*str)++;
  } else if (strncmp(*str, "mod", 3) == 0) {
    string->last_index = MOD;
    set_node(MOD, 2, 0, &(string->stack_array[*i]));
    (*i)++;
    (*str) += 3;
  } else if (parse_trig_func(str, string, i))
    err = 1;
  return err;
}

int parse_un_op(const char **str, s21_stack *string, int *i) {
  int err = 0;
  if (**str == '+' &&
      (string->last_index == FIRST_SYM || string->last_index == OP_BRACKET)) {
    string->last_index = UNAR_P;
    set_node(UNAR_P, 5, 0, &(string->stack_array[*i]));
    (*i)++;
    (*str)++;
  } else if (**str == '-' && (string->last_index == FIRST_SYM ||
                              string->last_index == OP_BRACKET)) {
    string->last_index = UNAR_M;
    set_node(UNAR_M, 5, 0, &(string->stack_array[*i]));
    (*i)++;
    (*str)++;
  } else if (strncmp(*str, "sqrt(", 5) == 0) {
    string->last_index = SQRT;
    set_node(SQRT, 5, 0, &(string->stack_array[*i]));
    (*i)++;
    (*str) += 4;
  } else if (strncmp(*str, "ln(", 3) == 0) {
    string->last_index = LN;
    set_node(LN, 5, 0, &(string->stack_array[*i]));
    (*i)++;
    (*str) += 2;
  } else if (strncmp(*str, "log(", 4) == 0) {
    string->last_index = LOG;
    set_node(LOG, 5, 0, &(string->stack_array[*i]));
    (*i)++;
    (*str) += 3;
  } else if (parse_bin_op(str, string, i))
    err = 1;
  return err;
}

int parse_symols(const char **str, s21_stack *string, int *i) {
  int err = 0;
  if (**str == ' ')
    (*str)++;
  else if (**str >= '0' && **str <= '9' && string->last_index != DIGIT) {
    string->last_index = DIGIT;
    double num = process_digit(str);
    if (num == -1) {
      err = 1;
    }
    set_node(DIGIT, 0, num, &(string->stack_array[*i]));
    (*i)++;
  } else if (**str == '(') {
    string->last_index = OP_BRACKET;
    set_node(OP_BRACKET, 0, 0, &(string->stack_array[*i]));
    string->check_brt += 1;
    (*i)++;
    (*str)++;
  } else if (**str == ')' && string->check_brt &&
             string->last_index != OP_BRACKET) {
    string->last_index = CL_BRACKET;
    set_node(CL_BRACKET, 0, 0, &(string->stack_array[*i]));
    string->check_brt -= 1;
    (*i)++;
    (*str)++;
  } else if (err == 0)
    err = parse_un_op(str, string, i);
  return err;
}

int parse_trig_func(const char **str, s21_stack *string, int *i) {
  int err = 0;
  if (strncmp(*str, "sin(", 4) == 0) {
    string->last_index = SIN;
    set_node(SIN, 5, 0, &(string->stack_array[*i]));
    (*i)++;
    (*str) += 3;
  } else if (strncmp(*str, "cos(", 4) == 0) {
    string->last_index = COS;
    set_node(COS, 5, 0, &(string->stack_array[*i]));
    (*i)++;
    (*str) += 3;
  } else if (strncmp(*str, "tan(", 4) == 0) {
    string->last_index = TAN;
    set_node(TAN, 5, 0, &(string->stack_array[*i]));
    (*i)++;
    (*str) += 3;
  } else if (strncmp(*str, "asin(", 5) == 0) {
    string->last_index = ASIN;
    set_node(ASIN, 5, 0, &(string->stack_array[*i]));
    (*i)++;
    (*str) += 4;
  } else if (strncmp(*str, "acos(", 5) == 0) {
    string->last_index = ACOS;
    set_node(ACOS, 5, 0, &(string->stack_array[*i]));
    (*i)++;
    (*str) += 4;
  } else if (strncmp(*str, "atan(", 5) == 0) {
    string->last_index = ATAN;
    set_node(ATAN, 5, 0, &(string->stack_array[*i]));
    (*i)++;
    (*str) += 4;
  } else
    err = 1;
  return err;
}

void transform(s21_stack *string, s21_stack *queue, s21_stack *stack) {
  for (int i = 0; i < get_stack_size(string); i++) {
    int size = get_stack_size(stack);
    if (string->stack_array[i].type == DIGIT) {
      s21_push(queue, &string->stack_array[i]);
    } else if (string->stack_array[i].type == OP_BRACKET) {
      s21_push(stack, &string->stack_array[i]);
    } else if (string->stack_array[i].type == CL_BRACKET) {
      proc_bracket(stack, queue);
    } else if (string->stack_array[i].priority <=
               stack->stack_array[size - 1].priority) {
      proc_priority(stack, queue, string->stack_array[i]);
      s21_push(stack, &string->stack_array[i]);
    } else if (size == 0 || stack->stack_array[size - 1].type == OP_BRACKET) {
      s21_push(stack, &string->stack_array[i]);
    } else if (string->stack_array[i].priority >
               stack->stack_array[size - 1].priority) {
      s21_push(stack, &string->stack_array[i]);
    }
  }
  int size_stack = get_stack_size(stack);
  if (size_stack != 0) {
    s21_node last_element;
    while (size_stack > 0) {
      s21_pop(stack, &last_element);
      s21_push(queue, &last_element);
      size_stack = get_stack_size(stack);
    }
  }
}

int to_postfix(const char *str, s21_stack *queue) {
  int err = 0;
  if (strlen(str) != 0 && strlen(str) < 256) {
    s21_stack string = {0};
    string.last_index = FIRST_SYM;
    int i = 0;
    while (*str != '\0' && err != 1) {
      if (parse_symols(&str, &string, &i)) err = 1;
    }
    if (string.check_brt == 0 && err == 0) {
      err = minor_changes(&string);
      s21_stack stack = {0};
      transform(&string, queue, &stack);
    } else
      err = 1;
  } else
    err = 1;
  return err;
}
