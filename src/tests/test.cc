#include <gtest/gtest.h>

#include "../Model/model.h"

class ModelTests : public ::testing::Test {
 protected:
  s21::Model model;
};

TEST_F(ModelTests, SmartCalc) {
  std::string res;
  model.SmartCalc("31(3-2)", res);
  EXPECT_EQ(res, "31.0000000");
  model.SmartCalc("+3 - 2", res);
  EXPECT_EQ(res, "1.0000000");
  model.SmartCalc("2^2^3", res);
  EXPECT_EQ(res, "256.0000000");
  model.SmartCalc("12.123455 + 15432.4", res);
  EXPECT_EQ(res, "15444.5234550");
  model.SmartCalc("5 / 2", res);
  EXPECT_EQ(res, "2.5000000");
  model.SmartCalc("sqrt(9)", res);
  EXPECT_EQ(res, "3.0000000");
  model.SmartCalc("(-(121 + 3454) * 12) * 12^2", res);
  EXPECT_EQ(res, "-6177600.0000000");
  model.SmartCalc("12.333", res);
  EXPECT_EQ(res, "12.3330000");
  model.SmartCalc("2.5+2*(2+cos(0.1))", res);
  EXPECT_EQ(res, "8.4900083");
  model.SmartCalc("10 + 5", res);
  EXPECT_EQ(res, "15.0000000");
  model.SmartCalc("20 - 3", res);
  EXPECT_EQ(res, "17.0000000");
  model.SmartCalc("4 * 7.25", res);
  EXPECT_EQ(res, "29.0000000");
  model.SmartCalc("100 / 8", res);
  EXPECT_EQ(res, "12.5000000");
  model.SmartCalc("5 mod 3", res);
  EXPECT_EQ(res, "2.0000000");
  model.SmartCalc("3^4", res);
  EXPECT_EQ(res, "81.0000000");
  model.SmartCalc("-8 + 4", res);
  EXPECT_EQ(res, "-4.0000000");
  model.SmartCalc("-2 * (-3)", res);
  EXPECT_EQ(res, "6.0000000");
  model.SmartCalc("cos(0)", res);
  EXPECT_EQ(res, "1.0000000");
  model.SmartCalc("sin(3.14159265 / 2)", res);
  EXPECT_EQ(res, "1.0000000");
  model.SmartCalc("tan(0)", res);
  EXPECT_EQ(res, "0.0000000");
  model.SmartCalc("acos(1)", res);
  EXPECT_EQ(res, "0.0000000");
  model.SmartCalc("asin(1)", res);
  EXPECT_EQ(res, "1.5707963");  // π/2 radians
  model.SmartCalc("atan(1)", res);
  EXPECT_EQ(res, "0.7853982");  // π/4 radians
  model.SmartCalc("sqrt(16)", res);
  EXPECT_EQ(res, "4.0000000");
  model.SmartCalc("ln(2.7182818)", res);
  EXPECT_EQ(res, "1.0000000");
  model.SmartCalc("log(100)", res);
  EXPECT_EQ(res, "2.0000000");
  model.SmartCalc("5 + 3 * (10 - 6) / 2", res);
  EXPECT_EQ(res, "11.0000000");
  model.SmartCalc("10 + sin(0.5) * cos(0.5)", res);
  EXPECT_EQ(res, "10.4207355");
  model.SmartCalc("5^2 + sqrt(49) - ln(1)", res);
  EXPECT_EQ(res, "32.0000000");
  model.SmartCalc("7 * atan(1)", res);
  EXPECT_EQ(res, "5.4977871");
}

TEST_F(ModelTests, ErrSmartCalc) {
  std::string res;
  EXPECT_TRUE(model.SmartCalc("2^", res));
  EXPECT_TRUE(model.SmartCalc("sqrt(-5)", res));
  EXPECT_TRUE(model.SmartCalc(")1+2(", res));
  EXPECT_TRUE(model.SmartCalc("(1+2))", res));
  EXPECT_TRUE(model.SmartCalc("12334+", res));
  EXPECT_TRUE(model.SmartCalc("5 /", res));
  EXPECT_TRUE(model.SmartCalc("-(", res));
  EXPECT_TRUE(model.SmartCalc("sqrt()", res));
  EXPECT_TRUE(model.SmartCalc("ln(,)", res));
  EXPECT_TRUE(model.SmartCalc("cos(90", res));
  EXPECT_TRUE(model.SmartCalc("log(5", res));
  EXPECT_TRUE(model.SmartCalc("log(-5)", res));
  EXPECT_TRUE(model.SmartCalc("ln(-5)", res));
  EXPECT_TRUE(model.SmartCalc("-2^(0.5)", res));
  EXPECT_TRUE(model.SmartCalc("atan()", res));
  EXPECT_TRUE(model.SmartCalc("5 *** 2", res));
  EXPECT_TRUE(model.SmartCalc("4 ++ 3", res));
  EXPECT_TRUE(model.SmartCalc("3 mod mod 2", res));
  EXPECT_TRUE(model.SmartCalc("mod mod mod", res));
  EXPECT_TRUE(model.SmartCalc("455/0", res));
  EXPECT_TRUE(model.SmartCalc("455.012.31", res));
}

TEST_F(ModelTests, CheckForOperTest) {
  s21::Model::Node node(s21::Model::MUL, 2, 0);
  EXPECT_TRUE(model.CheckForOper(node.type));
  s21::Model::Node node2(s21::Model::PLUS, 2, 0);
  EXPECT_TRUE(model.CheckForOper(node2.type));
  s21::Model::Node node3(s21::Model::OP_BRACKET, 2, 0);
  EXPECT_FALSE(model.CheckForOper(node3.type));
}


TEST_F(ModelTests, ErrDiffCreditCalc1) {
  const std::string sum = "-2";
  const std::string time = "12";
  const std::string rate = "5";
  std::string output;
  EXPECT_TRUE(model.DiffCreditCalc(sum,time, rate, output));
}

TEST_F(ModelTests, ErrDiffCreditCalc2) {
  const std::string sum = "1000";
  const std::string time = "-12";
  const std::string rate = "5";
  std::string output;
  EXPECT_TRUE(model.DiffCreditCalc(sum,time, rate, output));
}

TEST_F(ModelTests, ErrDiffCreditCalc3) {
  const std::string sum = "3312542";
  const std::string time = "12";
  const std::string rate = "-15";
  std::string output;
  EXPECT_TRUE(model.DiffCreditCalc(sum,time, rate, output));
}

TEST_F(ModelTests, DiffCreditCalc) {
  const std::string sum = "3312542";
  const std::string time = "12";
  const std::string rate = "15";
  std::string output;
  EXPECT_FALSE(model.DiffCreditCalc(sum,time, rate, output));
}

TEST_F(ModelTests, ErrAnnCreditCalc1) {
  const std::string sum = "-2";
  const std::string time = "12";
  const std::string rate = "5";
  std::string output;
  EXPECT_TRUE(model.AnnCreditCalc(sum,time, rate, output));
}

TEST_F(ModelTests, ErrAnnCreditCalc2) {
  const std::string sum = "1000";
  const std::string time = "-12";
  const std::string rate = "5";
  std::string output;
  EXPECT_TRUE(model.AnnCreditCalc(sum,time, rate, output));
}

TEST_F(ModelTests, ErrAnnCreditCalc3) {
  const std::string sum = "3312542";
  const std::string time = "12";
  const std::string rate = "-15";
  std::string output;
  EXPECT_TRUE(model.AnnCreditCalc(sum,time, rate, output));
}

TEST_F(ModelTests, AnnCreditCalc) {
  const std::string sum = "3312542";
  const std::string time = "12";
  const std::string rate = "15";
  std::string output;
  EXPECT_FALSE(model.AnnCreditCalc(sum,time, rate, output));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}