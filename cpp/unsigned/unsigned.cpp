#include <iostream>

using std::cout;
using std::endl;

int main()
{
    // this simple code snippet below checks for unsigned propagation
    // in arithmetic operations. Correct answer can be deduced from
    // section 7.4 [expr.arith.conv], item (1.5.5)
    signed int a = -1;
    unsigned int b = 1;

    if (a < b)
        cout << "a is less than b" << endl;
    else
        cout << "a is NOT less than b" << endl;

    return 0;
}
