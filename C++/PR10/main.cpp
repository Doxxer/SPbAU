#include <iostream>
#include "rational.hpp"

using std::cout;
using std::endl;

int main()
{
    Rational a(1, 2);
    Rational b(3, 6);
    
    cout << a << endl << b << endl;
    a == b ? cout << "equal" : cout << "fail", cout << endl;
    return 0;
}
