#if !defined(TOKEN)
#define TOKEN

#include <string>

using namespace std;

class Token {
public:
    bool is_var;
    bool is_assign;
    bool is_op;
    bool is_num;
    bool valid;
    bool open_p;
    bool close_p;
    bool unary;
    int priority;
    double value;
    string var_name;
    string str;
    Token(string type, const string& s) {
        str = s;
        is_var = false;
        is_assign = false;
        is_op = false;
        is_num = false;
        valid = false;
        open_p = false;
        close_p = false;
        unary = false;
        value = 0;
        var_name = "";
        if (type == "v") {
            is_var = true;
            valid = true;
            var_name = s.substr(1, s.size() - 1);
        } else if (type == "a") {
            is_assign = true;
            valid = true;
            var_name = s.substr(0, s.size() - 1);
        } else if (type == "o") {
            is_op = true;
            valid = true;
            if (s == "-") {
                priority = 2;
            } else if (s == "+") {
                priority = 2;
            } else if (s == "*") {
                priority = 3;
            } else if (s == "/") {
                priority = 3;
            } else if (s == "^") {
                priority = 4;
            } else if (s == "~") {
                priority = 2;
                unary = true;
            } else if (s == "(") {
                is_op = false;
                open_p = true;
            } else  if (s == ")") {
                is_op = false;
                close_p = true;
            }
        } else if (type == "n") {
            is_num = true;
            valid = true;
            value = stod(s);
        } else {
            valid = false;
        }
    }

    Token(double v) {
        is_var = false;
        is_assign = false;
        is_op = false;
        open_p = false;
        close_p = false;
        unary = false;
        var_name = "";
        is_num = true;
        valid = true;
        value = v;
        str = to_string(v);
    }

    Token(const Token& t) {
    is_var = t.is_var;
    is_assign = t.is_assign;
    is_op = t.is_op;
    is_num = t.is_num;
    valid = t.valid;
    open_p = t.open_p;
    close_p = t.close_p;
    unary = t.unary;
    priority = t.priority;
    value = t.value;
    var_name = t.var_name;
    str = t.str;
    }

    inline bool operator==(const Token& rhs) const {
        return rhs.str == str;
    }
};


#endif // TOKEN
