#include <stdio.h>
#include <TXLib.h>
#include <math.h>

enum N_ROOTS {
    INF_ROOTS = -1,
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS
};
enum RESPONSE_CODES_FOR_QUIT {
    SUCCESSFUL_QUIT = -1,
    CHARACTER_NOT_FOUND = 0,
    CHARACTER_FOUND = 1,
    UNEXPECTED_CHARACTER = -2,
    UNEXPECTED_SPACE = -3

};
enum RESPONSE_CODES_FOR_PRINT {
    SUCCESSFUL_PRINT = 0,
    UNEXPECTED_N_ROOTS = 1

};

const double EPSILON = 1e-9;

struct Equation // �������� �� ������������ ���������
{
    double a;
    double b;
    double c;
    double x1;
    double x2;
    enum N_ROOTS count_roots;
};

void InputCoeffs (struct Equation *eq);

void SolveQuadratic (struct Equation *eq);
int IsZero (double n);
enum N_ROOTS SolveForLinear (struct Equation *eq);
enum N_ROOTS SolveForNegativeD (void);
enum N_ROOTS SolveForZeroD (struct Equation *eq);
enum N_ROOTS SolveForPositiveD (double d, struct Equation *eq);

enum RESPONSE_CODES_FOR_PRINT PrintSolution (struct Equation eq);
int ClearBuf (void); // ������� ������ �����
enum RESPONSE_CODES_FOR_QUIT SearchForQuit (void);

int main()
{
    struct Equation eq = { NAN, 0, 0, 0, 0, NO_ROOTS };

    InputCoeffs(&eq);

    SolveQuadratic(&eq);

    PrintSolution(eq);

    return 0;
}

void InputCoeffs(struct Equation *eq) // ���������������� ����
{
    assert(&(eq->a) != NULL);
    assert(&(eq->b) != NULL);
    assert(&(eq->c) != NULL);

    int count_params = 0; // ���������� ���������� �� ����� �����
    int count_excess_ch = 0; // ���������� ������ �������� (�� ��������) ����� �����
    int is_quit = 0; // ���� ��� ������ ��� �����
    printf("������� ������������ ����������� ���������\n"
           "����� ����� �� ���������, ������� QUIT\n");

    while (true)
    {
        count_params = scanf("%lg %lg %lg", &(eq->a), &(eq->b), &(eq->c));
        is_quit = SearchForQuit();
        count_excess_ch = (is_quit == CHARACTER_NOT_FOUND) ? 0 : ClearBuf(); // ���� SearchForQuit() �� ����� ��������, �� ����� ��� ����
        if (count_params == 0 && is_quit == SUCCESSFUL_QUIT && count_excess_ch == 0)
        {
            exit(0);
        }
        else if (count_params == 3 && is_quit == 0 && count_excess_ch == 0)
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
        }

        printf("���������� �����\n");
    }

}

void SolveQuadratic(struct Equation *eq)
{
    assert(isfinite(eq->a));
    assert(isfinite(eq->b));
    assert(isfinite(eq->c));

    assert(&(eq->x1) != NULL);
    assert(&(eq->x2) != NULL);
    assert(&(eq->x1) != &(eq->x2));

    if (IsZero(eq->a)) // �������� �� ������� ������� �����������
    {
        eq->count_roots = SolveForLinear(eq);
    }
    else
    {
        double d = (eq->b)*(eq->b) - 4*(eq->a)*(eq->c); // ������� ����� ������������

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
        case NO_ROOTS: printf("��� ������");
                break;
        case ONE_ROOT: printf("x = %lg", eq.x1);
                break;
        case TWO_ROOTS: printf("x1 = %lg, x2 = %lg", eq.x1, eq.x2);
                break;
        case INF_ROOTS: printf("x - ����� �����");
                break;
        default: printf("������: ����������� ���������� ������ - %d", eq.count_roots);
                return UNEXPECTED_N_ROOTS;
    }
    return SUCCESSFUL_PRINT;
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

enum RESPONSE_CODES_FOR_QUIT SearchForQuit(void)
{
    int next_ch = '\0', count_not_spaces = 0;

    int cur_quit_index = 0; // ������� ������ �������
    char quit_string[4] = { 'Q', 'U', 'I', 'T' };

    while ((next_ch = getchar()) != '\n' && next_ch != EOF)
    {
        if (!isspace(next_ch))
        {
            ++count_not_spaces;

            // ���������, �� ������ �� ������������ "QUIT"
            if (cur_quit_index < 4 && next_ch == quit_string[cur_quit_index])
            {
                ++cur_quit_index;
                if (cur_quit_index == 4)
                {
                    return SUCCESSFUL_QUIT;
                }
            }
            else
            {
                return UNEXPECTED_CHARACTER;
            }
        }
        else if (cur_quit_index)
        {
            return UNEXPECTED_SPACE;
        }
    }
    if (count_not_spaces)
    {
        return CHARACTER_FOUND;
    }
    else
    {
        return CHARACTER_NOT_FOUND;
    }
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
