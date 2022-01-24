#include <expression.h>

#include <memory>
#include <string>

#include <policy.h>

using namespace std;

Expression::Expression() {
}

Expression::Expression(shared_ptr<Expression> l,
                       shared_ptr<Expression> r,
                       std::string op)
{
    if (op == "+") {
        policy = make_shared<Plus>(Plus(l, r));
    } else 
    if (op == "-") {
        policy = make_shared<Minus>(Minus(l, r));
    } else 
    if (op == "*") {
        policy = make_shared<Multiply>(Multiply(l, r));
    } else 
    if (op == "/") {
        policy = make_shared<Divide>(Divide(l, r));
    } else 
    if (op == "^") {
        policy = make_shared<Power>(Power(l, r));
    }
}

Expression::Expression(shared_ptr<Expression> r, const std::string& op) {
    if (op == "~") {
        policy = make_shared<UnaryMinus>(UnaryMinus(r));
    }
}

Expression::Expression(double v) {
    policy = make_shared<Value>(Value(v));
}

bool Expression::valid()
{
    return true;
}

double Expression::evaluate()
{
    return policy->evaluate();
}