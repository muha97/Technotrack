#include <cstdio>
#include <cmath>

void scan_parameters (double *a, double *b, double *c)
{
    scanf("%lf", a);
    scanf("%lf", b);
    scanf("%lf", c);
}

void solve_eq (double *x1, double *x2, const double a, const double b, const double c, int *status)
{
    if (a == 0.0 && b == 0.0 && c == 0.0)
        *status = -1;
    else if (a == 0.0 && b == 0.0)
        *status = 0;
    else if (a == 0.0)
    {
        *status = 1;
        *x2 = *x1 = - c / b;
    }
    else
    {
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
            *status = 0;
        else if (discriminant == 0)
        {
            *status = 1;
            *x2 = *x1 = - b / a / 2;
        }
        else
        {
            *status = 2;

            *x1 = (- b - sqrt(discriminant)) / a / 2;
            *x2 = (- b + sqrt(discriminant)) / a / 2;
        }
    }
}

void print_roots(double *x1, double *x2, int *status)
{
    switch (*status)
    {
        case -1:
        {
            printf ("Infinite roots\n");
            break;
        }
        case 0:
        {
            printf ("No roots\n");
            break;
        }
        case 1:
        {
            printf ("x = %lf\n", *x1);
            break;
        }
        case 2:
        {
            printf ("x1 = %lf, x2 = %lf\n", *x1, *x2);
        }
    }
}