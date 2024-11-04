#include "../s21_SmartCalc.h"

double get_value(s21_stack *stack) {
  s21_node result;
  s21_pop(stack, &result);
  return result.value;
}

int bin_op_calc(s21_stack *stack, node_type oper) {
  double value_1 = get_value(stack);
  double value_2 = get_value(stack);
  double val = 0;
  int err = 0;
  switch (oper) {
    case PLUS:
      val = value_1 + value_2;
      break;
    case MINUS:
      val = value_2 - value_1;
      break;
    case DIV:
      if (value_1 != 0)
        val = value_2 / value_1;
      else
        err = 2;

      break;
    case MUL:
      val = value_1 * value_2;
      break;
    case POW:
      val = pow(value_2, value_1);
      break;
    case MOD:
      val = fmod(value_2, value_1);
      break;
    default:
      break;
  }
  s21_node res;
  set_node(DIGIT, 0, val, &res);
  s21_push(stack, &res);
  return err;
}

void un_op_calc(s21_stack *stack, node_type oper) {
  double value = get_value(stack);
  double val = 0;
  switch (oper) {
    case UNAR_M:
      val = (-1) * value;
      break;
    case UNAR_P:
      val = value;
      break;
    case SQRT:
      val = sqrt(value);
      break;
    case LN:
      val = log(value);
      break;
    case LOG:
      val = log10(value);
      break;
    case SIN:
      val = sin(value);
      break;
    case COS:
      val = cos(value);
      break;
    case TAN:
      val = tan(value);
      break;
    case ACOS:
      val = acos(value);
      break;
    case ASIN:
      val = asin(value);
      break;
    case ATAN:
      val = atan(value);
      break;
    default:
      break;
  }
  s21_node res;
  set_node(DIGIT, 0, val, &res);
  s21_push(stack, &res);
}

double calc_exp(s21_stack *expression, int *err) {
  int size = get_stack_size(expression);
  s21_stack stack = {0};
  for (int i = 0; i < size; i++) {
    if (expression->stack_array[i].type == DIGIT) {
      s21_push(&stack, &expression->stack_array[i]);
    } else if (expression->stack_array[i].type <= 6) {
      *err = bin_op_calc(&stack, expression->stack_array[i].type);
    } else if (expression->stack_array[i].type >= 6 &&
               expression->stack_array[i].type <= 17) {
      un_op_calc(&stack, expression->stack_array[i].type);
    }
  }
  return stack.stack_array[0].value;
}

int s21_smart_calc(const char *str, char *result) {
  double res = 0;
  s21_stack queue = {0};
  int err = to_postfix(str, &queue);
  if (err == 0) {
    res = calc_exp(&queue, &err);
  }
  sprintf(result, "%f", res);
  return err;
}
