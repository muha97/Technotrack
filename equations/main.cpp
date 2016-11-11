#include "equation.hpp"

int main()
{
    double a, b, c;
    double x1 = 0, x2 = 0;
    int status; // определяет количество корней

    scan_parameters(&a, &b, &c);

    solve_eq(&x1, &x2, a, b, c, &status);

    print_roots(&x1, &x2, &status);

    return 0;
}