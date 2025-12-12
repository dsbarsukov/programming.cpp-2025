#include <gtest/gtest.h>

#include "RPNCalculator.h"

using namespace std;

// ==================== Тесты для isNumber() ====================
TEST(RPNCalculatorTest, IsNumber_PositiveInteger) {
  EXPECT_TRUE(isNumber("0"));
  EXPECT_TRUE(isNumber("5"));
  EXPECT_TRUE(isNumber("123"));
  EXPECT_TRUE(isNumber("999999"));
}

TEST(RPNCalculatorTest, IsNumber_NegativeInteger) {
  EXPECT_TRUE(isNumber("-5"));
  EXPECT_TRUE(isNumber("-123"));
  EXPECT_FALSE(isNumber("-"));
  EXPECT_FALSE(isNumber(""));
}

TEST(RPNCalculatorTest, IsNumber_Decimal) {
  EXPECT_TRUE(isNumber("3.14"));
  EXPECT_TRUE(isNumber("0.5"));
  EXPECT_TRUE(isNumber("-2.71"));
  EXPECT_TRUE(isNumber("100.0"));
}

TEST(RPNCalculatorTest, IsNumber_Invalid) {
  EXPECT_FALSE(isNumber("abc"));
  EXPECT_FALSE(isNumber("12a3"));
  EXPECT_FALSE(isNumber("12.3.4"));
  EXPECT_FALSE(isNumber("."));
}

// ==================== Тесты для isOperator() ====================
TEST(RPNCalculatorTest, IsOperator_Valid) {
  EXPECT_TRUE(isOperator("+"));
  EXPECT_TRUE(isOperator("-"));
  EXPECT_TRUE(isOperator("*"));
  EXPECT_TRUE(isOperator("/"));
}

TEST(RPNCalculatorTest, IsOperator_Invalid) {
  EXPECT_FALSE(isOperator("++"));
  EXPECT_FALSE(isOperator("a"));
  EXPECT_FALSE(isOperator("1"));
  EXPECT_FALSE(isOperator(""));
  EXPECT_FALSE(isOperator("^"));
}

// ==================== Тесты для applyOperator() ====================
TEST(RPNCalculatorTest, ApplyOperator_Addition) {
  EXPECT_DOUBLE_EQ(applyOperator("+", 3.0, 4.0), 7.0);
  EXPECT_DOUBLE_EQ(applyOperator("+", -2.0, 5.0), 3.0);
  EXPECT_DOUBLE_EQ(applyOperator("+", 0.0, 0.0), 0.0);
}

TEST(RPNCalculatorTest, ApplyOperator_Subtraction) {
  EXPECT_DOUBLE_EQ(applyOperator("-", 10.0, 4.0), 6.0);
  EXPECT_DOUBLE_EQ(applyOperator("-", 5.0, 10.0), -5.0);
  EXPECT_DOUBLE_EQ(applyOperator("-", 0.0, 3.0), -3.0);
}

TEST(RPNCalculatorTest, ApplyOperator_Multiplication) {
  EXPECT_DOUBLE_EQ(applyOperator("*", 3.0, 4.0), 12.0);
  EXPECT_DOUBLE_EQ(applyOperator("*", -2.0, 5.0), -10.0);
  EXPECT_DOUBLE_EQ(applyOperator("*", 0.0, 100.0), 0.0);
}

TEST(RPNCalculatorTest, ApplyOperator_Division) {
  EXPECT_DOUBLE_EQ(applyOperator("/", 10.0, 2.0), 5.0);
  EXPECT_DOUBLE_EQ(applyOperator("/", 5.0, 2.0), 2.5);
  EXPECT_DOUBLE_EQ(applyOperator("/", 0.0, 5.0), 0.0);
}

TEST(RPNCalculatorTest, ApplyOperator_DivisionByZero) {
  EXPECT_THROW(applyOperator("/", 10.0, 0.0), runtime_error);
  EXPECT_THROW(applyOperator("/", 0.0, 0.0), runtime_error);
}

TEST(RPNCalculatorTest, ApplyOperator_UnknownOperator) {
  EXPECT_THROW(applyOperator("%", 10.0, 2.0), runtime_error);
  EXPECT_THROW(applyOperator("^", 2.0, 3.0), runtime_error);
}

// ==================== Тесты для evaluateRPN() ====================
TEST(RPNCalculatorTest, EvaluateRPN_SimpleOperations) {
  EXPECT_DOUBLE_EQ(evaluateRPN("3 4 +"), 7.0);
  EXPECT_DOUBLE_EQ(evaluateRPN("10 4 -"), 6.0);
  EXPECT_DOUBLE_EQ(evaluateRPN("3 5 *"), 15.0);
  EXPECT_DOUBLE_EQ(evaluateRPN("10 2 /"), 5.0);
}

TEST(RPNCalculatorTest, EvaluateRPN_ComplexExpressions) {
  // 5 1 2 + 4 * + 3 - = (5 + ((1 + 2) * 4)) - 3 = 14
  EXPECT_DOUBLE_EQ(evaluateRPN("5 1 2 + 4 * + 3 -"), 14.0);

  // 2 3 * 4 5 * + = (2 * 3) + (4 * 5) = 26
  EXPECT_DOUBLE_EQ(evaluateRPN("2 3 * 4 5 * +"), 26.0);

  // 7 2 - 3 * = (7 - 2) * 3 = 15
  EXPECT_DOUBLE_EQ(evaluateRPN("7 2 - 3 *"), 15.0);
}

TEST(RPNCalculatorTest, EvaluateRPN_DecimalNumbers) {
  EXPECT_DOUBLE_EQ(evaluateRPN("3.5 2.5 +"), 6.0);
  EXPECT_DOUBLE_EQ(evaluateRPN("10 3 /"), 10.0 / 3.0);
  EXPECT_DOUBLE_EQ(evaluateRPN("2.5 4 *"), 10.0);
}

TEST(RPNCalculatorTest, EvaluateRPN_NegativeNumbers) {
  EXPECT_DOUBLE_EQ(evaluateRPN("-3 5 +"), 2.0);
  EXPECT_DOUBLE_EQ(evaluateRPN("5 -3 +"), 2.0);
  EXPECT_DOUBLE_EQ(evaluateRPN("-3 -5 *"), 15.0);
}

TEST(RPNCalculatorTest, EvaluateRPN_DivisionByZero_InExpression) {
  EXPECT_THROW(evaluateRPN("10 0 /"), runtime_error);
  EXPECT_THROW(evaluateRPN("5 2 0 * /"), runtime_error);
}

TEST(RPNCalculatorTest, EvaluateRPN_NotEnoughOperands) {
  EXPECT_THROW(evaluateRPN("3 +"), runtime_error);
  EXPECT_THROW(evaluateRPN("+"), runtime_error);
  EXPECT_THROW(evaluateRPN("3 4 + -"), runtime_error);
}

TEST(RPNCalculatorTest, EvaluateRPN_TooManyNumbers) {
  EXPECT_THROW(evaluateRPN("3 4 5"), runtime_error);
  EXPECT_THROW(evaluateRPN("3 4 + 5"), runtime_error);
}

TEST(RPNCalculatorTest, EvaluateRPN_InvalidTokens) {
  EXPECT_THROW(evaluateRPN("3 abc +"), runtime_error);
  EXPECT_THROW(evaluateRPN("3 4 &"), runtime_error);
  EXPECT_THROW(evaluateRPN(""), runtime_error);
}

TEST(RPNCalculatorTest, EvaluateRPN_ComplexDivision) {
  // 2 12 6 / - = 2 - (12 / 6) = 0
  EXPECT_DOUBLE_EQ(evaluateRPN("2 12 6 / -"), 0.0);

  // 10 4 3 + 2 * - = 10 - ((4 + 3) * 2) = -4
  EXPECT_DOUBLE_EQ(evaluateRPN("10 4 3 + 2 * -"), -4.0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}