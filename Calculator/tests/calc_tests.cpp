#include <iostream>
#include <sstream>

#include <gtest/gtest.h>

#include <calculator.h>
#include <lexer.h>
#include <expression.h>

using namespace std;

TEST(calc_tests, valid) {
    Calculator calc{};
    ValidLexer lexer;
    string res = calc.process("", lexer);
    EXPECT_EQ("0", res);
}

TEST(calc_tests, invalid) {
    Calculator calc{};
    InvalidLexer lexer;
    string res = calc.process("", lexer);
    EXPECT_EQ(calc.get_error(), res);
}

TEST(calc_tests, normal_valid_1) {
    Calculator calc{};
    string res = calc.process("4*5");
    EXPECT_EQ("20", res);
}

TEST(calc_tests, normal_valid_2) {
    Calculator calc{};
    string res = calc.process("2 + 2");
    EXPECT_EQ("4", res);
}

TEST(calc_tests, normal_valid_3) {
    Calculator calc{};
    string res = calc.process("2 + 2 + (2 + 2)");
    EXPECT_EQ("8", res);
}

TEST(calc_tests, normal_valid_4) {
    Calculator calc{};
    string res = calc.process("2 * 2 / 2 * 2");
    EXPECT_EQ("4", res);
}

TEST(calc_tests, normal_valid_5) {
    Calculator calc{};
    string res = calc.process("-(3) + 2");
    EXPECT_EQ("-1", res);
}

TEST(calc_tests, normal_valid_6) {
    Calculator calc{};
    string res = calc.process("-(-(-1))");
    EXPECT_EQ("-1", res);
}

TEST(calc_tests, normal_valid_7) {
    Calculator calc{};
    string res = calc.process("--1");
    EXPECT_EQ("1", res);
}

TEST(calc_tests, normal_valid_8) {
    Calculator calc{};
    string res = calc.process("x= 2");
    EXPECT_EQ("2", res);
    res = calc.process("y= $X");
    EXPECT_EQ("2", res);
    res = calc.process("$Y + $x");
    EXPECT_EQ("4", res);
    res = calc.process("nonesence= 101");
    EXPECT_EQ("101", res);
}

TEST(calc_tests, normal_invalid_1) {
    Calculator calc{};
    string res = calc.process("2 + 2. * 2");
    EXPECT_EQ(calc.get_error(), res);
}

TEST(calc_tests, normal_invalid_2) {
    Calculator calc{};
    string res = calc.process("2 + * 2");
    EXPECT_EQ(calc.get_error(), res);
}

TEST(calc_tests, normal_invalid_3) {
    Calculator calc{};
    string res = calc.process("2 +");
    EXPECT_EQ(calc.get_error(), res);
}

TEST(calc_tests, normal_invalid_4) {
    Calculator calc{};
    string res = calc.process("error");
    EXPECT_EQ(calc.get_error(), res);
}

TEST(calc_tests, normal_invalid_5) {
    Calculator calc{};
    string res = calc.process("tricky test=5");
    EXPECT_EQ(calc.get_error(), res);
}