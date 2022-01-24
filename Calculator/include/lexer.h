#if !defined(LEXER)
#define LEXER

#include <string>
#include <memory>

#include "expression.h"
#include "parser.h"
#include "tokenizer.h"
#include "token.h"

using namespace std;

class Lexer {
public:
    virtual shared_ptr<Expression> parse(const string& str);
    Lexer();
    virtual ~Lexer();
private:
    Tokenizer tokenizer;
    Parser parser;
    shared_ptr<Expression> result;
    vector<Token> tokens;
};

class InvalidLexer: public Lexer {
public:
    InvalidLexer();
    ~InvalidLexer();
    shared_ptr<Expression> parse(const string& str) override;
private:
    shared_ptr<InvalidExpression> invalid_result;
};

class ValidLexer: public Lexer {
public:
    ValidLexer();
    ~ValidLexer();
    shared_ptr<Expression> parse(const string& str) override;
private:
    shared_ptr<ValidExpression> valid_result;
};

#endif