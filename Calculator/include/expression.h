#if !defined(EXPRESSION)
#define EXPRESSION

#include <memory>
#include <string>

#include <policy.h>

using namespace std;

class Expression{

public:
    Expression();
    Expression(shared_ptr<Expression> l, shared_ptr<Expression> r, std::string op);
    Expression(shared_ptr<Expression> r, const std::string& op);
    Expression(double v);
    virtual ~Expression() {};
    virtual bool valid();
    virtual double evaluate();
    shared_ptr<Policy> policy;
private:
    

};

class ValidExpression: public Expression {
public:
    bool valid() override {
        return true;
    }
    double evaluate() override {
        return 0;
    }
};

class InvalidExpression: public Expression {
public:
    bool valid() override {
        return false;
    }
    double evaluate() override{
        return 0;
    }
};
#endif