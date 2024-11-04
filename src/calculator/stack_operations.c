#include "../s21_SmartCalc.h"

void s21_insert(s21_stack *stack, s21_node *node, int position) {
  int i = get_stack_size(stack);
  for (; i >= position; i--) {
    stack->stack_array[i + 1] = stack->stack_array[i];
  }
  stack->stack_array[position] = *node;
}

void s21_delete(s21_stack *stack, int position) {
  int size = get_stack_size(stack);
  stack->stack_array[position].priority = 0;
  stack->stack_array[position].value = 0;
  stack->stack_array[position].type = 0;
  for (int i = position; i <= size; i++) {
    stack->stack_array[i] = stack->stack_array[i + 1];
  }
}

void s21_push(s21_stack *stack, s21_node *node) {
  int size = get_stack_size(stack);
  s21_insert(stack, node, size);
}

void s21_pop(s21_stack *stack, s21_node *node) {
  int size = get_stack_size(stack);
  *node = stack->stack_array[size - 1];
  s21_delete(stack, size - 1);
}