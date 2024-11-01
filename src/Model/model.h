#ifndef MODEL_H
#define MODEL_H

#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

namespace s21 {

class Model {
 public:
  enum NodeType {
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
  };

  struct Node {
    Model::NodeType type;
    int priority;
    double value;

    Node(Model::NodeType t = Model::FIRST_SYM, int p = 0, double v = 0.0)
        : type(t), priority(p + 22), value(v) {}
  };

  struct Stack {
    unsigned int check_brt;
    NodeType last_index;
    std::stack<Node> stack_data;
  };
  int SmartCalc(const std::string str, std::string& result);
  double ProcessDigit(const char** str);
  double StrToDouble(const char* string);
  int MinorChanges(Model::Stack& string);
  void Transform(Model::Stack& string, std::deque<Model::Node>& queue);
  int ToPostfix(const char* str, std::deque<Model::Node>& queue);
  int ParseSymbols(const char** str, Model::Stack& string);
  int ParseUnOp(const char** str, Model::Stack& string);
  int ParseBinOp(const char** str, Model::Stack& string);
  int ParseTrigFunc(const char** str, Model::Stack& string);
  int CheckForOper(NodeType type);
  void ProcPriority(Model::Stack& stack, std::deque<Model::Node>& queue,
                    Node cur_node);
  void ProcBracket(Model::Stack& stack, std::deque<Model::Node>& queue);
  double CalcExp(std::deque<Model::Node> expr, int& err);
  int BinOpCalc(std::stack<Model::Node>& stack, Model::NodeType oper);
  int UnOpCalc(std::stack<Model::Node>& stack, Model::NodeType oper);

  int DiffCreditCalc(const std::string& sum, const std::string& time,
                     const std::string& rate, std::string& output);
  int AnnCreditCalc(const std::string& sum, const std::string& time,
                    const std::string& rate, std::string& output);
};

}  // namespace s21

#endif  // MODEL_H