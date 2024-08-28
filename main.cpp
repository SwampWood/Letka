#include <stdio.h>
#include <TXLib.h>
#include <math.h>
#include "input_coeffs.h"
#include "consts.h"

void SolveQuadratic (struct Equation *eq);
int IsZero (double n);
enum N_ROOTS SolveForLinear (struct Equation *eq);
enum N_ROOTS SolveForNegativeD (void);
enum N_ROOTS SolveForZeroD (struct Equation *eq);
enum N_ROOTS SolveForPositiveD (double d, struct Equation *eq);

enum RESPONSE_CODES_FOR_PRINT PrintSolution (struct Equation eq);


int main()
{
    struct Equation eq = { NAN, 0, 0, 0, 0, NO_ROOTS };

    InputCoeffs(&eq);

    SolveQuadratic(&eq);

    PrintSolution(eq);

    return 0;
}

void SolveQuadratic(struct Equation *eq)
{
    assert(isfinite(eq->a));
    assert(isfinite(eq->b));
    assert(isfinite(eq->c));

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

enum RESPONSE_CODES_FOR_PRINT PrintSolution (struct Equation eq)
{
    assert(&(eq.x1) != NULL);
    assert(&(eq.x2) != NULL);
    assert(&(eq.count_roots) != NULL);
    assert(&(eq.x1) != &(eq.x2));

    switch (eq.count_roots)
    {
        case NO_ROOTS: printf("Нет корней");
                break;
        case ONE_ROOT: printf("x = %lg", eq.x1);
                break;
        case TWO_ROOTS: printf("x1 = %lg, x2 = %lg", eq.x1, eq.x2);
                break;
        case INF_ROOTS: printf("x - любое число");
                break;
        default: printf("ОШИБКА: невозможное количество корней - %d", eq.count_roots);
                return UNEXPECTED_N_ROOTS;
    }
    return SUCCESSFUL_PRINT;
}

int IsZero(double n)
{
    return (-EPSILON < n && n < EPSILON);
}

enum N_ROOTS SolveForLinear (struct Equation *eq)
{
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
    return  NO_ROOTS;
}

enum N_ROOTS SolveForZeroD (struct Equation *eq)
{
    eq->x1 = -(eq->b) / (2 * (eq->a));

    return ONE_ROOT;
}

enum N_ROOTS SolveForPositiveD (double d, struct Equation *eq)
{

    assert(&(eq->x1) != NULL);
    assert(&(eq->x2) != NULL);
    assert(&(eq->x1) != &(eq->x2));

    double sqrt_d = sqrt(d);
    eq->x1 = (-(eq->b) - sqrt_d) / (2 * (eq->a));
    eq->x2 = (-(eq->b) + sqrt_d) / (2 * (eq->a));

    return TWO_ROOTS;
}
