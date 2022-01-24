#include <iostream>
#include <stdexcept>

#include <gtest/gtest.h>

#include <expression.h>
#include <tokenizer.h>
#include <parser.h>

TEST(parser_tests, invalid1)
{
    Parser parser;
    Tokenizer tokenizer;
    string s = "2 +";
    auto in = tokenizer.tokenize(s);
    EXPECT_THROW(parser.parse(in)->valid(), invalid_argument);
}

TEST(parser_tests, valid1)
{
    Parser parser;
    Tokenizer tokenizer;
    string s = "2 + 2 *2";
    auto in = tokenizer.tokenize(s);
    EXPECT_EQ(parser.parse(in)->evaluate(), (double)6);
}

TEST(parser_tests, valid2)
{
    Parser parser;
    Tokenizer tokenizer;
    string s = "(2 + 2) * 2";
    auto in = tokenizer.tokenize(s);
    EXPECT_EQ(parser.parse(in)->evaluate(), (double)8);
}

TEST(parser_tests, valid3)
{
    Parser parser;
    Tokenizer tokenizer;
    string s = "2 * -1";
    auto in = tokenizer.tokenize(s);
    EXPECT_EQ(parser.parse(in)->evaluate(), (double)-2);
}

TEST(parser_tests, valid4)
{
    Parser parser;
    Tokenizer tokenizer;
    string s = "xyz=         -(1 + 2 - ((-3) * (2)))";
    auto in = tokenizer.tokenize(s);
    EXPECT_EQ(parser.parse(in)->evaluate(), (double)-9);
}

TEST(parser_tests, assignment_valid1)
{
    Parser parser;
    Tokenizer tokenizer;
    string s = "x= 2+ 2";
    auto in = tokenizer.tokenize(s);
    EXPECT_EQ(parser.parse(in)->evaluate(), (double)4);
}

TEST(parser_tests, assignment_valid2)
{
    Parser parser;
    Tokenizer tokenizer;
    string s1 = "x= 2+ 2";
    auto in1 = tokenizer.tokenize(s1);
    EXPECT_EQ(parser.parse(in1)->evaluate(), (double)4);
    string s2 = "$x + 4";
    auto in2 = tokenizer.tokenize(s2);
    EXPECT_EQ(parser.parse(in2)->evaluate(), (double)8);
    string s3 = "y=$x + 4";
    auto in3 = tokenizer.tokenize(s3);
    EXPECT_EQ(parser.parse(in3)->evaluate(), (double)8);
    string s4 = "$y + $x + 4";
    auto in4 = tokenizer.tokenize(s4);
    EXPECT_EQ(parser.parse(in4)->evaluate(), (double)16);
}

TEST(parser_tests, parenthesize)
{
    Parser parser;
    Tokenizer tokenizer;
    string in_str = "2 + 2 * 2";
    string out_str = "((((2)))+(((2))*((2))))";
    auto in = tokenizer.tokenize(in_str);
    auto exp_out = tokenizer.tokenize(out_str);
    auto out = parser.test_parenthesization(in);
    EXPECT_EQ(exp_out.size(), out.size());
    if (exp_out.size() == out.size())
    {
        for (int i = 0; i < exp_out.size(); i++)
        {
            EXPECT_EQ(exp_out[i], out[i]);
        }
    }

}
