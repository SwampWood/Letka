#ifndef SOLVE_QUADRATIC_H_INCLUDED
#define SOLVE_QUADRATIC_H_INCLUDED

enum N_ROOTS {
    INF_ROOTS = -1,
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS
};

struct Equation // отвечает за коэффициенты уравнения
{
    double a;
    double b;
    double c;
    double x1;
    double x2;
    enum N_ROOTS count_roots;
};


const double EPSILON = 1e-9;

void SolveQuadratic (struct Equation *eq);
int IsZero (double n);
enum N_ROOTS SolveForLinear (struct Equation *eq);
enum N_ROOTS SolveForNegativeD (void);
enum N_ROOTS SolveForZeroD (struct Equation *eq);
enum N_ROOTS SolveForPositiveD (double d, struct Equation *eq);

#endif // SOLVE_QUADRATIC_H_INCLUDED
