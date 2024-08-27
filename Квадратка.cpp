#include <stdio.h>
#include <TXLib.h>
#include <math.h>

enum {INF_ROOTS = -1, NO_ROOTS, ONE_ROOT, TWO_ROOTS};
const double EPSILON = 1e-9;

struct Coeffs // отвечает за коэффициенты уравнения
{
    double a;
    double b;
    double c;
};

struct Roots // отвечает за корни уравнения
{
    double x1;
    double x2;
    int count_roots;
};

void InputCoeffs(double *a, double *b, double *c);
int SolveQuadratic(double a, double b, double c, double *x1, double *x2);
void PrintSolution(struct Roots roots);
int IsZero(double n);
int ClearBuf(void); // очистка буфера ввода

int main()
{
    struct Coeffs coeffs { 0, 0, 0 };

    InputCoeffs(&coeffs.a, &coeffs.b, &coeffs.c);

    struct Roots roots { 0, 0, NO_ROOTS };

    roots.count_roots = SolveQuadratic(coeffs.a, coeffs.b, coeffs.c, &roots.x1, &roots.x2);

    PrintSolution(roots);
}

void InputCoeffs(double *a, double *b, double *c) // пользовательский ввод
{
    int count_params = 0;
    int count_excess_ch = 0; // количество лишних символов (не пробелов) после ввода

    while (true)
    {
        count_params = scanf("%lg %lg %lg", a, b, c);
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

int SolveQuadratic(double a, double b, double c, double *x1, double *x2)
{
    if (IsZero(a)) // проверка на нулевые коэффициенты
    {
        if (IsZero(b))
        {
            if (IsZero(c))
                return INF_ROOTS;
            else
                return NO_ROOTS;
        }
        else
        {
            *x1 = -c / b;

            return ONE_ROOT;
        }
    }
    else
    {
        double d = b*b - 4*a*c; // решение через дискриминант
        if (d < 0)
        {
            return NO_ROOTS;
        }
        else if (IsZero(d))
        {
            *x1 = -b / (2 * a);

            return ONE_ROOT;
        }
        else
        {
            double sqrt_d = sqrt(d);
            *x1 = (-b - sqrt_d) / (2 * a);
            *x2 = (-b + sqrt_d) / (2 * a);

            return TWO_ROOTS;
        }
    }
}

void PrintSolution(struct Roots roots)
{
    switch (roots.count_roots)
    {
        case NO_ROOTS: printf("Нет корней");
                break;
        case ONE_ROOT: printf("x = %lg", roots.x1);
                break;
        case TWO_ROOTS: printf("x1 = %lg, x2 = %lg", roots.x1, roots.x2);
                break;
        case INF_ROOTS: printf("x - любое число");
                break;
        default: printf("ОШИБКА: невозможное количество корней - %d", roots.count_roots);
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
