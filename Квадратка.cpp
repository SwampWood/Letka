#include <stdio.h>
#include <TXLib.h>
#include <math.h>

const int INF_ROOTS = -1;

int main()
{
    double a, b, c, d, x1 = 0, x2 = 0;
    int roots = 0;
    scanf("%lg %lg %lg", &a, &b, &c); // Пользовательский ввод
    if (a == 0) // Проверка на нулевые коэффициенты
    {
        if (b == 0)
        {
            if (c == 0)
                roots = INF_ROOTS;
            else
                roots = 0;
        }
        else
        {
            roots = 1;
            x1 = c / b;
        }
    }
    else // Решение через дискриминант
    {
        d = b*b - 4*a*c;
        if (d < 0)
            roots = 0;
        else if (d == 0)
        {
            roots = 1;
            x1 = -b / (2 * a);
        }
        else
        {
            roots = 2;
            x1 = (-b - sqrt(d)) / (2 * a);
            x2 = (-b + sqrt(d)) / (2 * a);
        }
    }
    switch (roots)
    {
        case 0: printf("Нет корней");
                break;
        case 1: printf("x = %lg", x1);
                break;
        case 2: printf("x1 = %lg, x2 = %lg", x1, x2);
                break;
        case INF_ROOTS: printf("x - любое число");
                break;
    }
}
