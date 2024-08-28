#ifndef INPUT_COEFFS_H_INCLUDED
#define INPUT_COEFFS_H_INCLUDED

enum RESPONSE_CODES_FOR_QUIT {
    SUCCESSFUL_QUIT = -1,
    CHARACTER_NOT_FOUND = 0,
    CHARACTER_FOUND = 1,
    UNEXPECTED_CHARACTER = -2,
    UNEXPECTED_SPACE = -3
};

void InputCoeffs (struct Equation *eq);

int ClearBuf (void); // очистка буфера ввода
enum RESPONSE_CODES_FOR_QUIT SearchForQuit (void);

#endif // INPUT_COEFFS_H_INCLUDED
