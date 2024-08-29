#include <stdio.h>
#include <TXLib.h>
#include "solve_quadratic.h"
#include "equation.h"


void SolveQuadratic(struct Equation *eq)
{
    assert(&eq != NULL);

    assert(isfinite(eq->a));
    assert(isfinite(eq->b));
    assert(isfinite(eq->c));
    assert(isfinite(eq->x1));
    assert(isfinite(eq->x2));

    assert(&(eq->x1) != NULL);
    assert(&(eq->x2) != NULL);
    assert(&(eq->x1) != &(eq->x2));

    if (IsZero(eq->a)) // проверка на нулевой старший коэффициент
    {
        eq->count_roots = SolveForLinear(eq);
    }
    else
    {
        double d = (eq->b)*(eq->b) - 4*(eq->a)*(eq->c); // решение через дискриминант

        if (d < 0)
        {
            eq->count_roots = SolveForNegativeD();
        }
        else if (IsZero(d))
        {
            eq->count_roots = SolveForZeroD (eq);
        }
        else
        {
            eq->count_roots = SolveForPositiveD (d, eq);
        }
    }
}

int IsZero(double n)
{
    return (-EPSILON < n && n < EPSILON);
}

enum N_ROOTS SolveForLinear (struct Equation *eq)
{
    assert(eq != NULL);

    if (IsZero(eq->b))
    {
        if (IsZero(eq->c))
            return INF_ROOTS;
        else
            return NO_ROOTS;
    }
    else
    {
        eq->x1 = -eq->c / eq->b;

        return ONE_ROOT;
    }

}

enum N_ROOTS SolveForNegativeD (void)
{
    return NO_ROOTS;
}

enum N_ROOTS SolveForZeroD (struct Equation *eq)
{
    assert(eq != NULL);

    assert(isfinite(eq->a));
    assert(isfinite(eq->b));

    eq->x1 = -(eq->b) / (2 * (eq->a));

    return ONE_ROOT;
}

enum N_ROOTS SolveForPositiveD (double d, struct Equation *eq)
{
    assert(eq != NULL);

    assert(&(eq->x1) != NULL);
    assert(&(eq->x2) != NULL);
    assert(&(eq->x1) != &(eq->x2));

    double sqrt_d = sqrt(d);
    eq->x1 = (-(eq->b) - sqrt_d) / (2 * (eq->a));
    eq->x2 = (-(eq->b) + sqrt_d) / (2 * (eq->a));

    return TWO_ROOTS;
}
