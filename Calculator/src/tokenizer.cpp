#include <tokenizer.h>

#include <string>
#include <vector>
#include <regex>
#include <stdexcept>

#include <token.h>

using namespace std;

vector<Token>& Tokenizer::tokenize(const string& str) {
    int len = 0;
    for (auto &&c : str)
    {
        if (c != ' ') {
            len += 1;
        }
    }
    
    tokens.clear();
    int sum = 0;
    regex re("([a-zA-Z]+=)|(\\$[a-zA-Z]+)|([0-9]+(\\.[0-9]+)?)|([+\\-*/=^()])");
    sregex_iterator begin(str.begin(), str.end(), re);
    sregex_iterator end;
    string str_match;

    for (sregex_iterator i = begin; i != end; ++i) {
        smatch match = *i;
        str_match = match.str();
        sum += str_match.length();
        tokens.push_back(make_token(str_match));
    }
    if (sum != len) {
        throw invalid_argument("Invalid input string");
    }
    replace_unary();
    return tokens;
}

Token Tokenizer::make_token(const string& str) {
    regex assign("[a-zA-Z]+=");
    regex var("\\$[a-zA-Z]+");
    regex num("[0-9]+(\\.[0-9]+)?");
    regex op("[+\\-*/=^()]");
    if (regex_match(str, assign)) {
        return Token("a", str);
    } else if (regex_match(str, var)) {
        return Token("v", str);
    } else if (regex_match(str, num)) {
        return Token("n", str);
    } else if (regex_match(str, op)) {
        return Token("o", str);
    } else {
        throw invalid_argument("Invalid string to make token");
    }
}

void Tokenizer::replace_unary(vector<Token> &t)
{
    tokens = t;
    replace_unary();
}


void Tokenizer::replace_unary()
{
    bool unary = true;
    vector<Token> result;
    for (auto &&t : tokens)
    {
        if (t.str == "-" && unary)
        {
            result.push_back(Token("o", "~"));
        } else if (
            t.str == "+" ||
            t.str == "-" ||
            t.str == "*" ||
            t.str == "/" ||
            t.str == "^")
        {
            if (unary) {
                throw invalid_argument("Invalid unary operator");
            }
            unary = true;
            result.push_back(t);
        } else {
            if (!t.is_assign && !t.open_p) {
                unary = false;
            }
            result.push_back(t);
        }
    }
    tokens = result;
}

vector<Token>& Tokenizer::get_tokens() { 
    return tokens;
}
