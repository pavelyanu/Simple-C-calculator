#include <iostream>
#include <sstream>

#include "calculator.h"
#include "expression.h"

using namespace std;

int main(int argc, char const *argv[])
{
    Calculator calculator{};
    calculator.start(cin, cout);
    return 0;
}
