#include <calculator.h>

#include <string>
#include <iostream>
#include <memory>
#include <algorithm>
#include <cctype>

#include <expression.h>

using namespace std;

void Calculator::start(istream &in, ostream &out)
{
    string input;
    string output;
    int n;

    getline(in, input);
    n = stoi(input);
    for (int i = 0; i < n; i++)
    {
        getline(in, input);
        output = process(input);
        out << output << std::endl;
    }
}

string &Calculator::process(const string &s)
{
    string str = s;
    transform(str.begin(), str.end(), str.begin(),
              [](unsigned char c)
              { return std::tolower(c); });
    auto e = lexer.parse(str);
    expression.swap(e);
    if (expression->valid())
    {
        result = to_string(expression->evaluate());
        result = trimString(result);
    }
    else
    {
        result = error;
    }
    return result;
}

string &Calculator::process(const string &s, Lexer &l)
{
    string str = s;
    transform(str.begin(), str.end(), str.begin(),
              [](unsigned char c)
              { return std::tolower(c); });
    auto e = l.parse(str);
    expression.swap(e);
    if (expression->valid())
    {
        result = to_string(expression->evaluate());
        result = trimString(result);
    }
    else
    {
        result = error;
    }
    return result;
}

string &Calculator::trimString(string &str)
{
    for (string::size_type s = str.length() - 1; s > 0; --s)
    {
        if (str[s] == '0')
            str.erase(s, 1);
        else if (str[s] == '.')
        {
            str.erase(s, 1);
            break;
        }
        else
            break;
    }
    return str;
}