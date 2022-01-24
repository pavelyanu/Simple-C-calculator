#if !defined(CALCULATOR)
#define CALCULATOR
#include <string>
#include <memory>

#include "lexer.h"

using namespace std;

class Calculator
{

public:
    Calculator() = default;
    void start(istream &in, ostream &out);
    string& trimString(string& str);
    string& process(const string &str);
    string& process(const string &str, Lexer& l);
    const string& get_error() {return error;}
private:
    string result;
    const string error = "Error";
    Lexer lexer;
    shared_ptr<Expression> expression;
};
#endif