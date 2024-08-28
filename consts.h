#ifndef CONSTS_H_INCLUDED
#define CONSTS_H_INCLUDED

enum N_ROOTS {
    INF_ROOTS = -1,
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS
};

enum RESPONSE_CODES_FOR_PRINT {
    SUCCESSFUL_PRINT = 0,
    UNEXPECTED_N_ROOTS = 1

};

const double EPSILON = 1e-9;

struct Equation // отвечает за коэффициенты уравнения
{
    double a;
    double b;
    double c;
    double x1;
    double x2;
    enum N_ROOTS count_roots;
};

#endif // CONSTS_H_INCLUDED
