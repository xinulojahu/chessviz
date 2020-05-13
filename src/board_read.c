#include "board_validation.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROR(TEXT)                               \
    printf("%d:%d %s: %c\n", line, sym, TEXT, c); \
    exit(-1);

#define GET(C)     \
    c = getchar(); \
    sym++;

int line = 0, sym = 0;

char board_read_turn(char board[8][8], int color_type)
{
    char c, figure;
    signed char x1, y1, x2, y2, turn_type;
    //Тип фигуры, выполняющей ход;
    GET(c);
    figure = ' ';
    if (ischessman(c)) {
        figure = c;
        GET(c);
    }

    //Буква поля с которого сделан ход
    if (isboardletter(c)) {
        x1 = c - 'a';
    }
    //Цифра поля с которого сделан ход
    GET(c);
    if (isboarddigit(c)) {
        y1 = c - '1';
    }

    //Тип хода
    GET(c);
    switch (c) {
    case '-':
        turn_type = 0;
        break;
    case 'x':
        turn_type = 1;
        break;
    }

    //Буква поля куда сделан ход
    GET(c);
    if (isboardletter(c)) {
        x2 = c - 'a';
    }

    //Цифра поля куда сделан ход
    GET(c);
    if (isboarddigit(c)) {
        y2 = c - '1';
    }

    //Проверка на взятие на проходе
    GET(c);
    if (c == 'e') {
        GET(c);
        if (c != '.') {
            printf("Неизвестный символ: %c\n", c);
            exit(-1);
        }
        GET(c);
        if (c != 'p') {
            printf("Неизвестный символ: %c\n", c);
            exit(-1);
        }
        GET(c);
        if (c != '.') {
            printf("Неизвестный символ: %c\n", c);
            exit(-1);
        }
        GET(c);
    }

    //Перемещение фигуры
    board[y2][x2] = board[y1][x1];
    board[y1][x1] = ' ';

    return c;
}

void board_read(char board[8][8])
{
    board_read_turn(board, 0);
}
