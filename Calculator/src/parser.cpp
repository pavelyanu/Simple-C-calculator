#include <vector>
#include <string>
#include <stdexcept>
#include <memory>
#include <stack>

#include "parser.h"
#include "token.h"
#include "expression.h"
#include "tokenizer.h"

Parser::Parser()
{
    root = make_shared<Expression>(ValidExpression());
}

shared_ptr<Expression> Parser::parse(vector<Token> &t)
{
    bool assignment = false;
    tokens = t;
    substitute();

    if (t[0].is_assign)
    {
        if (!correct_assignment(t[0]))
        {
            throw invalid_argument("Invalid assignment");
        }
        assignment = true;
        tokens.erase(tokens.begin());
    }

    parenthesize();

    shared_ptr<Expression> result;
    result = linear_parse(0, tokens.size() - 1);

    if (assignment)
    {
        vars[t[0].var_name] = result->evaluate();
    }

    return result;
}

void Parser::parenthesize()
{
    vector<Token> result;
    Tokenizer tokenizer;
    string string_to_append;
    vector<Token> append;
    push_tokens("((((", result, tokenizer);
    for (auto &&t : tokens)
    {
        if (t.str == "(")
        {
            string_to_append = "((((";
        }
        else if (t.str == ")")
        {
            string_to_append = "))))";
        }
        else if (t.str == "^")
        {
            string_to_append = ")^(";
        }
        else if (t.str == "*")
        {
            string_to_append = "))*((";
        }
        else if (t.str == "/")
        {
            string_to_append = "))/((";
        }
        else if (t.str == "+")
        {
            string_to_append = ")))+(((";
        }
        else if (t.str == "-")
        {
            string_to_append = ")))-(((";
        }
        else if (t.str == "~")
        {
            result.push_back(t);
            continue;
        }
        else
        {
            result.push_back(t);
            continue;
        }
        push_tokens(string_to_append, result, tokenizer);
    }
    push_tokens("))))", result, tokenizer);
    tokens = result;
}

shared_ptr<Expression> Parser::linear_parse(int start, int finish)
{
    Token token = tokens[start];
    if (token.open_p)
    {
        if (!tokens[finish].close_p)
        {
            throw invalid_argument("No closing parenthesis in the end");
        }
        int operator_position = find_operator(start, finish, 1);
        if (operator_position != -1)
        {
            auto left = linear_parse(start + 1, operator_position - 1);
            auto right = linear_parse(operator_position + 1, finish - 1);
            string op = tokens[operator_position].str;
            return make_shared<Expression>(Expression(left, right, op));
        }
        operator_position = find_operator(start, finish, 0);
        if (operator_position != -1) {
            auto left = linear_parse(start, operator_position - 1);
            auto right = linear_parse(operator_position + 1, finish);
            string op = tokens[operator_position].str;
            return make_shared<Expression>(Expression(left, right, op));
        } else
        {
            auto remainder = linear_parse(start + 1, finish - 1);
            return remainder;
        }
    }
    else
    {
        if (token.unary)
        {
            if (tokens[start + 1].open_p)
            {
                if (tokens[finish].close_p)
                {
                    string op = token.str;
                    auto right = linear_parse(start + 1, finish);
                    return make_shared<Expression>(Expression(right, op));
                }
                else
                {
                    throw invalid_argument("Trailing parenthesis in unary minus expression");
                }
            }
            string op = token.str;
            auto right = linear_parse(start + 1, finish);
            return make_shared<Expression>(Expression(right, op));
        }
        else if (token.is_num)
        {
            if (tokens[finish].close_p)
            {
                throw invalid_argument("Trailing parenthesis in the end");
            }
            return make_shared<Expression>(Expression(token.value));
        }
        else
        {
            throw invalid_argument("Invalid first token");
        }
    }
}

int Parser::find_operator(int start, int finish, int diff)
{
    Token token = tokens[start];
    int i = finish;
    int open_closed_diff = 0;
    int operation_position = -1;
    bool operation_found = false;
    while (!operation_found && i >= start)
    {
        token = tokens[i];
        if (token.open_p)
        {
            open_closed_diff++;
        }
        else if (token.close_p)
        {
            open_closed_diff--;
        }
        if (open_closed_diff == diff && token.is_op && !token.unary)
        {
            return i;
        }
        i--;
    }
    return -1;
}

vector<Token> Parser::test_parenthesization(vector<Token> &t)
{
    tokens = t;
    parenthesize();
    return tokens;
}

void Parser::push_tokens(const string &append, vector<Token> &result, Tokenizer tokenizer)
{
    auto t = tokenizer.tokenize(append);
    for (auto &&a : t)
    {
        result.push_back(a);
    }
}

bool Parser::correct_assignment(Token &t)
{
    if (vars.find(t.var_name) != vars.end())
    {
        return false;
    }
    if (tokens.size() < 2)
    {
        return false;
    }
    for (int i = 1; i < tokens.size(); i++)
    {
        if (tokens[i].var_name == t.var_name)
        {
            return false;
        }
    }
    return true;
}

void Parser::substitute()
{
    vector<Token> result;
    for (auto &&t : tokens)
    {
        if (t.is_var)
        {
            if (vars.find(t.var_name) == vars.end())
            {
                throw invalid_argument("Unknown variable");
            }
            result.push_back(Token(vars[t.var_name]));
        }
        else
        {
            result.push_back(t);
        }
    }
    tokens = result;
}

string Parser::print_tokens(int s, int f)
{
    string res = "";
    while (s <= f)
    {
        res += tokens[s].str;
        s++;
    }
    return res;
}

string Parser::print_tokens()
{
    string res = "";
    for (auto &&t : tokens)
    {
        res += t.str;
    }
    return res;
}