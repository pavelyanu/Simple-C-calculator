#include <lexer.h>

#include <string>
#include <memory>
#include <vector>
#include <iostream>

#include <expression.h>
#include <parser.h>
#include <tokenizer.h>

using namespace std;

//                          Lexer

Lexer::Lexer(){};
Lexer::~Lexer(){};

shared_ptr<Expression> Lexer::parse(const string &str)
{
    try
    {
        tokens = tokenizer.tokenize(str);
    }
    catch(const std::exception& e)
    {
        // cout << e.what();
        return make_shared<InvalidExpression>(InvalidExpression());
    }
    
    try
    {
        result = parser.parse(tokens);
    }
    catch(const std::exception& e)
    {
        // cout << e.what();
        return make_shared<InvalidExpression>(InvalidExpression());
    }
    return result;
}

//                          ValidLexer

ValidLexer::ValidLexer()
{
    valid_result = make_shared<ValidExpression>(ValidExpression());
};

ValidLexer::~ValidLexer(){};


shared_ptr<Expression> ValidLexer::parse(const string &str)
{
    return valid_result;
}

//                          InvalidLexer

InvalidLexer::InvalidLexer()
{
    invalid_result = make_shared<InvalidExpression>(InvalidExpression());
};

InvalidLexer::~InvalidLexer(){};

shared_ptr<Expression> InvalidLexer::parse(const string &str)
{
    return invalid_result;
}