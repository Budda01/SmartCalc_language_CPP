#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 511

typedef enum {
  PLUS = 1,
  MINUS = 2,
  DIV = 3,
  MUL = 4,
  POW = 5,
  MOD = 6,
  UNAR_M = 7,
  UNAR_P = 8,
  SQRT = 9,
  LN = 10,
  LOG = 11,
  SIN = 12,
  COS = 13,
  TAN = 14,
  ACOS = 15,
  ASIN = 16,
  ATAN = 17,
  OP_BRACKET = 18,
  CL_BRACKET = 19,
  X = 20,
  DIGIT = 21,
  FIRST_SYM = 22
} node_type;

typedef struct {
  node_type type;
  int priority;
  double value;
} s21_node;

typedef struct {
  unsigned int check_brt;
  node_type last_index;
  s21_node stack_array[STACK_SIZE];
} s21_stack;

void s21_insert(s21_stack *stack, s21_node *res, int position);
void s21_delete(s21_stack *stack, int position);
void s21_push(s21_stack *stack, s21_node *node);
void s21_pop(s21_stack *stack, s21_node *node);

double process_digit(const char **str);
int is_bin_operator(node_type node);
int parse_bin_op(const char **str, s21_stack *stack, int *i);
int parse_un_op(const char **str, s21_stack *stack, int *i);
int parse_symols(const char **str, s21_stack *stack, int *i);
int parse_trig_func(const char **str, s21_stack *stack, int *i);
int to_postfix(const char *str, s21_stack *queue);
int get_stack_size(s21_stack *stack);
int minor_changes(s21_stack *string);
void proc_priority(s21_stack *stack, s21_stack *queue, s21_node node);
void proc_bracket(s21_stack *stack, s21_stack *queue);
void set_node(node_type type, int priority, double value, s21_node *res);
void transform(s21_stack *string, s21_stack *queue, s21_stack *stack);
double str_to_double(const char *string);

int s21_smart_calc(const char *str, char *result);
double calc_exp(s21_stack *expression, int *err);
void un_op_calc(s21_stack *stack, node_type oper);
int bin_op_calc(s21_stack *stack, node_type oper);
double get_value(s21_stack *stack);

int ann_credit_calc(const char *sum, const char *time, const char *rate,
                    char *output);
int diff_credit_calc(const char *sum, const char *time, const char *rate,
                     char *output);