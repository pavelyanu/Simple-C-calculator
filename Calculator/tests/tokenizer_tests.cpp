#include <string>
#include <vector>
#include <stdexcept>

#include <gtest/gtest.h>

#include "tokenizer.h"
#include "token.h"

using namespace std;

// Demonstrate some basic assertions.
TEST(tokenizer_tests, valid1)
{
  Tokenizer tokenizer;
  vector<string> inputs{"1 + 2", "4+5/7^2", "2.5*9"};
  vector<string> first{"1", "+", "2"};
  vector<string> second{"4", "+", "5", "/", "7", "^", "2"};
  vector<string> third{"2.5", "*", "9"};
  vector<vector<string>> exp{first, second, third};
  for (int i = 0; i < exp.size(); i++)
  {
    vector<Token> output = tokenizer.tokenize(inputs[i]);
    EXPECT_EQ(exp[i].size(), output.size());
    if (exp[i].size() == output.size())
    {
      for (int j = 0; j < exp[i].size(); j++)
      {
        EXPECT_EQ(exp[i][j], output[j].str);
      }
    }
  }
}

TEST(tokenizer_tests, valid2)
{
  Tokenizer tokenizer;
  string in_str = "xyz=         -(1 + 2 - ((-3) * (2)))";
  string out_str = "xyz=-(1+2-((-3)*(2)))";
  auto out =  tokenizer.tokenize(in_str);
  auto exp_out =  tokenizer.tokenize(out_str);
  if (exp_out.size() == out.size())
  {
    for (int j = 0; j < exp_out.size(); j++)
    {
      EXPECT_EQ(exp_out[j], out[j]);
    }
  }
}

TEST(tokenizer_tests, invalid1)
{
  Tokenizer tokenizer;
  vector<string> inputs{"1 + 2,2", "4+5/7^2.", "2.5*%9"};
  for (int i = 0; i < inputs.size(); i++)
  {
    EXPECT_THROW(tokenizer.tokenize(inputs[i]), invalid_argument);
  }
}

TEST(tokenizer_tests, invalid_do_not_throw)
{
  Tokenizer tokenizer;
  vector<string> inputs{"x="};
  for (int i = 0; i < inputs.size(); i++)
  {
    EXPECT_NO_THROW(tokenizer.tokenize(inputs[i]));
  }
}

TEST(tokenizer_tests, replace_unary1)
{
  Tokenizer tokenizer;
  string s = "2- 2 +  -3";
  vector<string> exp_out{"2", "-", "2", "+", "~", "3"};
  auto in = tokenizer.tokenize(s);
  tokenizer.replace_unary(in);
  auto out = tokenizer.get_tokens();
  EXPECT_EQ(exp_out.size(), out.size());
  if (exp_out.size() == out.size())
  {
    for (int i = 0; i < exp_out.size(); i++)
    {
      EXPECT_EQ(exp_out[i], out[i].str);
    }
  }
}

TEST(tokenizer_tests, replace_unary2)
{
  Tokenizer tokenizer;
  string in_str = "-(1 + 2)";
  vector<string> exp_out{"~", "(", "1", "+", "2", ")"};
  auto in = tokenizer.tokenize(in_str);
  tokenizer.replace_unary(in);
  auto out = tokenizer.get_tokens();
  EXPECT_EQ(exp_out.size(), out.size());
  if (exp_out.size() == out.size())
  {
    for (int i = 0; i < exp_out.size(); i++)
    {
      EXPECT_EQ(exp_out[i], out[i].str);
    }
  }
}

TEST(tokenizer_tests, replace_unary3)
{
  Tokenizer tokenizer;
  string in_str = "xyz=         -(1 + 2)";
  vector<string> exp_out{"xyz=", "~", "(", "1", "+", "2", ")"};
  auto in = tokenizer.tokenize(in_str);
  tokenizer.replace_unary(in);
  auto out = tokenizer.get_tokens();
  EXPECT_EQ(exp_out.size(), out.size());
  if (exp_out.size() == out.size())
  {
    for (int i = 0; i < exp_out.size(); i++)
    {
      EXPECT_EQ(exp_out[i], out[i].str);
    }
  }
}

TEST(tokenizer_tests, replace_unary4)
{
  Tokenizer tokenizer;
  string in_str = "2 - ((-3) + 2)";
  vector<string> exp_out{"2", "-", "(", "(", "~", "3", ")", "+", "2", ")"};
  auto in = tokenizer.tokenize(in_str);
  tokenizer.replace_unary(in);
  auto out = tokenizer.get_tokens();
  EXPECT_EQ(exp_out.size(), out.size());
  if (exp_out.size() == out.size())
  {
    for (int i = 0; i < exp_out.size(); i++)
    {
      EXPECT_EQ(exp_out[i], out[i].str);
    }
  }
}