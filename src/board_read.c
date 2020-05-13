#include "board_validation.h"
#include <stdio.h>
#include <stdlib.h>

char board_read_turn(char board[8][8], int color_type)
{
    char c, figure;
    signed char x1, y1, x2, y2, turn_type;
    //Тип фигуры, выполняющей ход;
    c = getchar();
    figure = ' ';
    if (ischessman(c)) {
        figure = c;
        c = getchar();
    }

    //Буква поля с которого сделан ход
    if ((c >= 'a') && (c <= 'h')) {
        x1 = c - 'a';
    }
    //Цифра поля с которого сделан ход
    c = getchar();
    if ((c >= '1') && (c <= '8')) {
        y1 = c - '1';
    }

    //Тип хода
    c = getchar();
    switch (c) {
    case '-':
        turn_type = 0;
        break;
    case 'x':
        turn_type = 1;
        break;
    }

    //Буква поля куда сделан ход
    c = getchar();
    if ((c >= 'a') && (c <= 'h')) {
        x2 = c - 'a';
    }

    //Цифра поля куда сделан ход
    c = getchar();
    if ((c >= '1') && (c <= '8')) {
        y2 = c - '1';
    }

    //Проверка на взятие на проходе
    c = getchar();
    if (c == 'e') {
        c = getchar();
        if (c != '.') {
            printf("Неизвестный символ: %c\n", c);
            exit(-1);
        }
        c = getchar();
        if (c != 'p') {
            printf("Неизвестный символ: %c\n", c);
            exit(-1);
        }
        c = getchar();
        if (c != '.') {
            printf("Неизвестный символ: %c\n", c);
            exit(-1);
        }
        c = getchar();
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
