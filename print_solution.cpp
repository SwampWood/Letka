#include <stdio.h>
#include <TXLib.h>
#include <math.h>
#include "solve_quadratic.h"
#include "print_solution.h"


enum RETURN_CODES_FOR_PRINT PrintSolution (struct Equation eq)
{
    assert(&eq != NULL);

    assert(isfinite(eq.x1));
    assert(isfinite(eq.x2));

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
