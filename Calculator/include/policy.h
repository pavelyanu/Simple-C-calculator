#if !defined(EVALUATE)
#define EVALUATE

#include <memory>

using namespace std;

class Expression;

class Policy {
public:
    Policy();
    virtual ~Policy();
    virtual double evaluate();
    shared_ptr<Expression> lhs;
    shared_ptr<Expression> rhs;
    double value;
private:
};

class Plus : public Policy {
public:
    Plus(shared_ptr<Expression> lhs, shared_ptr<Expression> rhs);
    ~Plus();
    double evaluate() override;
};

class Minus : public Policy {
public:
    Minus(shared_ptr<Expression> lhs, shared_ptr<Expression> rhs);
    ~Minus();
    double evaluate() override;
};

class Multiply : public Policy {
public:
    Multiply(shared_ptr<Expression> lhs, shared_ptr<Expression> rhs);
    ~Multiply();
    double evaluate() override;
};

class Divide : public Policy {
public:
    Divide(shared_ptr<Expression> lhs, shared_ptr<Expression> rhs);
    ~Divide();
    double evaluate() override;
};

class Power : public Policy {
public:
    Power(shared_ptr<Expression> lhs, shared_ptr<Expression> rhs);
    ~Power();
    double evaluate() override;
};

class UnaryMinus : public Policy {
public:
    UnaryMinus(shared_ptr<Expression> rhs);
    ~UnaryMinus();
    double evaluate() override;
};

class Value : public Policy {
public:
    Value(double v);
    ~Value();
    double evaluate() override;
};


#endif // EVALUATE
