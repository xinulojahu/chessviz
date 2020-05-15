#ifndef board_read_h
#define board_read_h
#include <stdio.h>
//Ошибка
int line, sym;
#define ERROR(SYM, TEXT)                   \
    printf("%d:%d %s\n", line, SYM, TEXT); \
    return -1;

//Следующий символ строки
#define NEXT(C)  \
    C = *ptrstr; \
    ptrstr++;    \
    sym++;
int board_get_turn(char* string);

int board_read(char board[8][8]);

//структура для хранения хода в цифрах
typedef struct board_turn {
    signed char x1;
    signed char y1;
    signed char x2;
    signed char y2;
    signed char turn_type;
    signed char eg;
    char figure;
} board_turn;
#endif
