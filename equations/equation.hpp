#ifndef EQUATION_HPP
#define EQUATION_HPP
#endif

#ifdef EQUATION_HPP

void scan_parameters (double *a, double *b, double *c);

void solve_eq (double *x1, double *x2, const double a, const double b, const double c, int *status);

void print_roots (double *x1, double *x2, int *status);

#endif