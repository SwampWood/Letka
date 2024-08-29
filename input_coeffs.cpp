#include <stdio.h>
#include <TXLib.h>
#include "input_coeffs.h"
#include "solve_quadratic.h"

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
