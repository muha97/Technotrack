#include <iostream>
#include "equation.hpp"

using std::cin;
using std::cout;
using std::endl;

int main()
{
    double a, b, c;
    cin >> a >> b >> c;
    double discriminant = b*b - 4*a*c;

    if (a == 0 && b == 0 && c == 0)
        cout << "Infinite roots" << endl;
    else if (a == 0 && b == 0 && c != 0)
        cout << "No roots" << endl;
    else if (a == 0 && b != 0)
    {
        double x = 0;
        LineEq(b, c, x);
        cout << "x = " << x;
    }
    else if (a != 0 && discriminant == 0)
    {
        double x = QuadEq(a, b, c);
        cout << "x = " << x << endl;
    }
    else if (a != 0 && discriminant != 0)
    {
        double x1 = 0, x2 = 0;
        QuadEq(a, b, c, x1, x2);
        cout << "x1 = " << x1 << ", x2 = " << x2 << endl;
    }

    return 0;
}