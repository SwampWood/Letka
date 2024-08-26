#include <stdio.h>
#include <TXLib.h>
#include <math.h>

const int INF = -1;
const double EPSILON = 1e-9;

void input(double *a, double *b, double *c);
int SolveQuadratic(double a, double b, double c, double *x1, double *x2);
void print(int roots, double x1, double x2);

int main()
{
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;

    input(&a, &b, &c);

    int roots = SolveQuadratic(a, b, c, &x1, &x2);

    print(roots, x1, x2);
}

void input(double *a, double *b, double *c) // Пользовательский ввод
{
    int count_params = scanf("%lg %lg %lg", a, b, c);
    getchar();

    while (count_params != 3)
    {
        printf("Неверное число аргументов: %d\n", count_params);
        printf("Попробуйте снова\n");

        count_params = scanf("\n%lg %lg %lg", a, b, c);
        getchar();
    }

}

int SolveQuadratic(double a, double b, double c, double *x1, double *x2)
{
    if (-EPSILON < a && a < EPSILON) // Проверка на нулевые коэффициенты
    {
        if (-EPSILON < b && b < EPSILON)
        {
            if (-EPSILON < c && c < EPSILON)
                return INF;
            else
                return 0;
        }
        else
        {
            *x1 = -c / b;
            return 1;
        }
    }
    else
    {
        double d = b*b - 4*a*c; // Решение через дискриминант
        if (d < 0)
        {
            return 0;
        }
        else if (-EPSILON < d && d < EPSILON)
        {
            *x1 = -b / (2 * a);
            return 1;
        }
        else
        {
            *x1 = (-b - sqrt(d)) / (2 * a);
            *x2 = (-b + sqrt(d)) / (2 * a);
            return 2;
        }
    }
}

void print(int roots, double x1, double x2)
{
    switch (roots)
    {
        case 0: printf("Нет корней");
                break;
        case 1: printf("x = %lg", x1);
                break;
        case 2: printf("x1 = %lg, x2 = %lg", x1, x2);
                break;
        case INF: printf("x - любое число");
                break;
        default: printf("ОШИБКА: невозможное количество корней - %d", roots);
                break;
    }
}
