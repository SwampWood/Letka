#include <stdio.h>
#include <TXLib.h>
#include <math.h>

int main()
{
    double a, b, c, d, x1 = 0, x2 = 0;
    scanf("%lg %lg %lg", &a, &b, &c); // Пользовательский ввод
    if (a == 0) // Проверка на нулевые коэффициенты
    {
        if (b == 0)
        {
            if (c == 0)
                printf("x - любое число");
            else
                printf("Нет корней");
        }
        else
        {
            x1 = c / b;
            printf("x = %lg", x1);
        }
    }
    else // Решение через дискриминант
    {
        d = b*b - 4*a*c;
        if (d < 0)
            printf("Нет корней");
        else if (d == 0)
        {
            x1 = -b / (2 * a);
            printf("x = %lg", x1);
        }
        else
        {
            x1 = (-b - sqrt(d)) / (2 * a);
            x2 = (-b + sqrt(d)) / (2 * a);
            printf("x1 = %lg, x2 = %lg", x1, x2);
        }
    }
}
