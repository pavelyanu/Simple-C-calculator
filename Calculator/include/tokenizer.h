#if !defined(TOKENIZER)
#define TOKENIZER
#include <string>
#include <vector>

#include <token.h>

using namespace std;


class Tokenizer {

public:

    vector<Token>& tokenize(const string& str);
    vector<Token>& get_tokens();
    Token make_token(const string& str);
    void replace_unary(vector<Token> &t);
    void replace_unary();

private:
    vector<Token> tokens;

};


#endif // TOKENIZER
