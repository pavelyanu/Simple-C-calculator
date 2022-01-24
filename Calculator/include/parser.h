#if !defined(PARSER)
#define PARSER
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <deque>

#include "expression.h"
#include "token.h"
#include "tokenizer.h"

using namespace std;

class Parser {

public:
    Parser();
    shared_ptr<Expression> parse(vector<Token>& tokens);
    shared_ptr<Expression> linear_parse(int start, int finish);
    void parenthesize();
    vector<Token>& get_tokens();
    void substitute();
    bool correct_assignment(Token& t);
    void push_tokens(const string& append, vector<Token>& result, Tokenizer tokenizer);
    vector<Token> test_parenthesization(vector<Token>& t);
    string print_tokens(int s, int f);
    string print_tokens();
    int find_operator(int s, int f, int diff);
private:
    shared_ptr<Expression> root;
    vector<Token> tokens;
    unordered_map<string, double> vars;
};

#endif // PARSER
