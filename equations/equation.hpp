#include <cmath>


/*
    * Если ты начал где-то отделать пробелами бинарные операции, это нужно
    * продолжать делать дальше.
*/

//! Ссылки - синтаксический сахар из C++. Используй указатели.
void LineEq (const double b, const double c, double& x)
{
    x = - b/c;
}

void QuadEq (const double a, const double b, const double c, double& x1, double& x2)
{
    double discriminant = sqrt(b*b - 4*a*c);
    x1 = (- b - discriminant)/a/2;
    x2 = (- b + discriminant)/a/2;
}

double QuadEq (const double a, const double b, const double c)
{
    return (-b/a/2);
}
