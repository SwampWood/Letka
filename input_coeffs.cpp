#include "input_coeffs.h"

void InputCoeffs(struct Equation *eq) // пользовательский ввод
{
    assert(&(eq->a) != NULL);
    assert(&(eq->b) != NULL);
    assert(&(eq->c) != NULL);

    int count_params = 0; // количество полученных на вводе чисел
    int count_excess_ch = 0; // количество лишних символов (не пробелов) после ввода
    int is_quit = 0; // флаг для выхода при вводе
    printf("Введите коэффициенты квадратного уравнения\n"
           "Чтобы выйти из программы, введите QUIT\n");

    while (true)
    {
        count_params = scanf("%lg %lg %lg", &(eq->a), &(eq->b), &(eq->c));
        is_quit = SearchForQuit();
        count_excess_ch = (is_quit == CHARACTER_NOT_FOUND) ? 0 : ClearBuf(); // если SearchForQuit() не нашел символов, то буфер уже пуст
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
            printf("Неверное число допустимых аргументов: %d\n", count_params);
        }
        else
        {
            printf("Слишком много аргументов\n");
        }

        printf("Попробуйте снова\n");
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

enum RESPONSE_CODES_FOR_QUIT SearchForQuit(void)
{
    int next_ch = '\0', count_not_spaces = 0;

    int cur_quit_index = 0; // текущий символ массива
    char quit_string[4] = { 'Q', 'U', 'I', 'T' };

    while ((next_ch = getchar()) != '\n' && next_ch != EOF)
    {
        if (!isspace(next_ch))
        {
            ++count_not_spaces;

            // проверяем, не вводит ли пользователь "QUIT"
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
