#include <stdio.h>
#include <TXLib.h>
#include <math.h>
#include "input_coeffs.h"
#include "solve_quadratic.h"
#include "print_solution.h"

int main()
{
    struct Equation eq = { 0, 0, 0, 0, 0, NO_ROOTS };

    if (InputCoeffs(&eq))
    {
        printf("Вы завершили выполнение программы");
        return 0;
    }

    SolveQuadratic(&eq);

    PrintSolution(eq);

    return 0;
}

