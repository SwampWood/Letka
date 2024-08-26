#include <stdio.h>
#include <TXLib.h>
#include <math.h>

const int INF = -1;
const double EPSILON = 1e-9;

void input(double *a, double *b, double *c);
int SolveQuadratic(double a, double b, double c, double *x1, double *x2);
void print(int roots, double x1, double x2);
bool eqzero(double n);
void clearbuf(void); // ������� ������ �����

int main()
{
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;

    input(&a, &b, &c);

    int roots = SolveQuadratic(a, b, c, &x1, &x2);

    print(roots, x1, x2);
}

void input(double *a, double *b, double *c) // ���������������� ����
{
    int count_params;
    int next_ch;

    while (true)
    {
        count_params = scanf("%lg %lg %lg", a, b, c);
        next_ch = getchar();
        if (count_params == 3 && next_ch == '\n')
        {
            break;
        }
        else if (count_params != 3)
        {
            printf("�������� ����� ���������� ����������: %d\n", count_params);
        }
        else
        {
            printf("������� ����� ����������\n");
            clearbuf();
        }

        printf("���������� �����\n");
    }

}

int SolveQuadratic(double a, double b, double c, double *x1, double *x2)
{
    if (eqzero(a)) // �������� �� ������� ������������
    {
        if (eqzero(b))
        {
            if (eqzero(c))
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
        double d = b*b - 4*a*c; // ������� ����� ������������
        if (d < 0)
        {
            return 0;
        }
        else if (eqzero(d))
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
        case 0: printf("��� ������");
                break;
        case 1: printf("x = %lg", x1);
                break;
        case 2: printf("x1 = %lg, x2 = %lg", x1, x2);
                break;
        case INF: printf("x - ����� �����");
                break;
        default: printf("������: ����������� ���������� ������ - %d", roots);
                break;
    }
}

void clearbuf(void)
{
    while (getchar() != '\n')
        ;
}

bool eqzero(double n)
{
    return (-EPSILON < n && n < EPSILON);
}
