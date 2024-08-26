#include <stdio.h>
#include <TXLib.h>
#include <math.h>

const int INF = -1;
int roots = 0;

void SolveQuadratic(double a, double b, double c, double *x1, double *x2)
{
    if (a == 0) // Проверка на нулевые коэффициенты
    {
        if (b == 0)
        {
            if (c == 0)
                roots = INF;
            else
                roots = 0;
        }
        else
        {
            *x1 = -c / b;
            roots = 1;
        }
    }
    else
    {
        double d = b*b - 4*a*c; // Решение через дискриминант
        if (d < 0)
            roots = 0;
        else if (d == 0)
        {
            *x1 = -b / (2 * a);
            roots = 1;
        }
        else
        {
            *x1 = (-b - sqrt(d)) / (2 * a);
            *x2 = (-b + sqrt(d)) / (2 * a);
            roots = 2;
        }
    }
}

int main()
{
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;
    scanf("%lg %lg %lg", &a, &b, &c); // Пользовательский ввод
    SolveQuadratic(a, b, c, &x1, &x2);
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
    }
}
