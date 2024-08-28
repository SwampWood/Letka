#include <stdio.h>
#include <TXLib.h>
#include <math.h>

enum N_ROOTS {
    INF_ROOTS = -1,
    NO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS
};
enum RETURN_CODES_FOR_QUIT {
    SUCCESSFUL_QUIT = -1,
    CHARACTER_NOT_FOUND = 0,
    CHARACTER_FOUND = 1,

};
enum RETURN_CODES_FOR_PRINT {
    SUCCESSFUL_PRINT = 0,
    UNEXPECTED_N_ROOTS = 1

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

int InputCoeffs (struct Equation *eq);

void SolveQuadratic (struct Equation *eq);
int IsZero (double n);
enum N_ROOTS SolveForLinear (struct Equation *eq);
enum N_ROOTS SolveForNegativeD (void);
enum N_ROOTS SolveForZeroD (struct Equation *eq);
enum N_ROOTS SolveForPositiveD (double d, struct Equation *eq);

enum RETURN_CODES_FOR_PRINT PrintSolution (struct Equation eq);
int ClearBuf (void); // очистка буфера ввода
enum RETURN_CODES_FOR_QUIT SearchForQuit (void);

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

int InputCoeffs(struct Equation *eq) // пользовательский ввод
{
    assert(eq != NULL);

    assert(isfinite(eq->a));
    assert(isfinite(eq->b));
    assert(isfinite(eq->c));

    assert(&(eq->a) != NULL);
    assert(&(eq->b) != NULL);
    assert(&(eq->c) != NULL);

    int count_params = 0; // количество полученных на вводе чисел
    int count_excess_ch = 0; // количество лишних символов (не пробелов) после ввода
    enum RETURN_CODES_FOR_QUIT is_quit = CHARACTER_NOT_FOUND; // флаг для выхода при вводе
    printf("Введите коэффициенты квадратного уравнения\n"
           "Чтобы выйти из программы, введите QUIT\n");

    while (true)
    {
        count_params = scanf("%lg %lg %lg", &(eq->a), &(eq->b), &(eq->c));
        if (count_params == 0)
        {
            is_quit = SearchForQuit();
        }
        count_excess_ch = ClearBuf(); // если SearchForQuit() не нашел символов, то буфер уже пуст
        if (is_quit == SUCCESSFUL_QUIT and count_excess_ch == 0)
        {
            return 1; // досрочное завершение программы
        }
        else if (count_params == 3 && is_quit == CHARACTER_NOT_FOUND && count_excess_ch == 0)
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
    return 0; // нормальное продолжение программы

}

void SolveQuadratic(struct Equation *eq)
{
    assert(&eq != NULL);

    assert(isfinite(eq->a));
    assert(isfinite(eq->b));
    assert(isfinite(eq->c));
    assert(isfinite(eq->x1));
    assert(isfinite(eq->x2));

    assert(&(eq->x1) != NULL);
    assert(&(eq->x2) != NULL);
    assert(&(eq->x1) != &(eq->x2));

    if (IsZero(eq->a)) // проверка на нулевой старший коэффициент
    {
        eq->count_roots = SolveForLinear(eq);
    }
    else
    {
        double d = (eq->b)*(eq->b) - 4*(eq->a)*(eq->c); // решение через дискриминант

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

enum RETURN_CODES_FOR_QUIT SearchForQuit(void)
{
    char check_string[] = "empty";

    int result = scanf("%s", check_string); // строка из пробелов - 0, иначе - 1
    if (strcmp(check_string, "QUIT"))
    {
        return result ? CHARACTER_FOUND : CHARACTER_NOT_FOUND;
    }
    return SUCCESSFUL_QUIT;
}

int IsZero(double n)
{
    return (-EPSILON < n && n < EPSILON);
}

enum N_ROOTS SolveForLinear (struct Equation *eq)
{
    assert(eq != NULL);

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
    return NO_ROOTS;
}

enum N_ROOTS SolveForZeroD (struct Equation *eq)
{
    assert(eq != NULL);

    assert(isfinite(eq->a));
    assert(isfinite(eq->b));

    eq->x1 = -(eq->b) / (2 * (eq->a));

    return ONE_ROOT;
}

enum N_ROOTS SolveForPositiveD (double d, struct Equation *eq)
{
    assert(eq != NULL);

    assert(&(eq->x1) != NULL);
    assert(&(eq->x2) != NULL);
    assert(&(eq->x1) != &(eq->x2));

    double sqrt_d = sqrt(d);
    eq->x1 = (-(eq->b) - sqrt_d) / (2 * (eq->a));
    eq->x2 = (-(eq->b) + sqrt_d) / (2 * (eq->a));

    return TWO_ROOTS;
}
