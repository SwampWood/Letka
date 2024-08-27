#include <stdio.h>
#include <TXLib.h>
#include <math.h>

enum N_ROOTS {
    INF_ROOTS = -1,
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS
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

void InputCoeffs(struct Equation *eq);
void SolveQuadratic(struct Equation *eq);
void PrintSolution(struct Equation eq);
int IsZero(double n);
int ClearBuf(void); // очистка буфера ввода

int main()
{
    struct Equation eq = { 0, 0, 0, 0, 0, NO_ROOTS };

    InputCoeffs(&eq);

    SolveQuadratic(&eq);

    PrintSolution(eq);

    return 0;
}

void InputCoeffs(struct Equation *eq) // пользовательский ввод
{
    int count_params = 0;
    int count_excess_ch = 0; // количество лишних символов (не пробелов) после ввода

    while (true)
    {
        count_params = scanf("%lg %lg %lg", &(eq->a), &(eq->b), &(eq->c));
        count_excess_ch = ClearBuf();
        if (count_params == 3 && count_excess_ch == 0)
        {
            break;
        }
        else if (count_params != 3)
        {
            printf("Неверное число допустимых аргументов: %d\n", count_params);
        }
        else
        {
            printf("Слишком много аргументов\n");
        }

        printf("Попробуйте снова\n");
    }

}

void SolveQuadratic(struct Equation *eq)
{
    if (IsZero(eq->a)) // проверка на нулевые коэффициенты
    {
        if (IsZero(eq->b))
        {
            if (IsZero(eq->c))
                eq->count_roots = INF_ROOTS;
            else
                eq->count_roots = NO_ROOTS;
        }
        else
        {
            eq->x1 = -eq->c / eq->b;

            eq->count_roots = ONE_ROOT;
        }
    }
    else
    {
        double d = (eq->b)*(eq->b) - 4*(eq->a)*(eq->c); // решение через дискриминант
        if (d < 0)
        {
            eq->count_roots = NO_ROOTS;
        }
        else if (IsZero(d))
        {
            eq->x1 = -(eq->b) / (2 * (eq->a));

            eq->count_roots = ONE_ROOT;
        }
        else
        {
            double sqrt_d = sqrt(d);
            eq->x1 = (-(eq->b) - sqrt_d) / (2 * (eq->a));
            eq->x2 = (-(eq->b) + sqrt_d) / (2 * (eq->a));

            eq->count_roots = TWO_ROOTS;
        }
    }
}

void PrintSolution(struct Equation eq)
{
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
                break;
    }
}

int ClearBuf(void)
{
    int next_ch = '\0', count_not_spaces = 0;
    while ((next_ch = getchar()) != '\n' && next_ch != EOF)
    {
        if (!isspace(next_ch))
        {
            ++count_not_spaces;
        }
    }
    return count_not_spaces;
}

int IsZero(double n)
{
    return (-EPSILON < n && n < EPSILON);
}
