#include <policy.h>

#include <string>
#include <memory>
#include <cmath>

#include <expression.h>

using namespace std;

//                              Policy
Policy::Policy() {}

Policy::~Policy() {}

double Policy::evaluate() {
    return 0;
}
//                              Plus

Plus::Plus(shared_ptr<Expression> l, shared_ptr<Expression> r) {
    lhs = l;
    rhs = r;
}

Plus::~Plus() {}

double Plus::evaluate() {
    return lhs->evaluate() + rhs->evaluate();
}

//                              Minus

Minus::Minus(shared_ptr<Expression> l, shared_ptr<Expression> r) {
    lhs = l;
    rhs = r;
}

Minus::~Minus() {}

double Minus::evaluate() {
    return lhs->evaluate() - rhs->evaluate();
}

//                              Multiply

Multiply::Multiply(shared_ptr<Expression> l, shared_ptr<Expression> r) {
    lhs = l;
    rhs = r;
}

Multiply::~Multiply() {}

double Multiply::evaluate() {
    return lhs->evaluate() * rhs->evaluate();
}

//                              Divide

Divide::Divide(shared_ptr<Expression> l, shared_ptr<Expression> r) {
    lhs = l;
    rhs = r;
}

Divide::~Divide() {}

double Divide::evaluate() {
    return lhs->evaluate() / rhs->evaluate();
}

//                              Power

Power::Power(shared_ptr<Expression> l, shared_ptr<Expression> r) {
    lhs = l;
    rhs = r;
}

Power::~Power() {}

double Power::evaluate() {
    return pow(lhs->evaluate(), rhs->evaluate());
}

//                              UnaryMinus

UnaryMinus::UnaryMinus(shared_ptr<Expression> r) {
    rhs = r;
}

UnaryMinus::~UnaryMinus() {}

double UnaryMinus::evaluate() {
    return -1 * rhs->evaluate();
}

//                              Value

Value::Value(double v) {
    value = v;
}

Value::~Value() {}

double Value::evaluate() {
    return value;
}
