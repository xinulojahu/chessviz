#include "board_validation.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROR(SYM, TEXT)                   \
    printf("%d:%d %s\n", line, SYM, TEXT); \
    exit(-1);

#define GET(C)     \
    c = getchar(); \
    sym++;

int line = 1, sym = 0;

char board_toupper(char c)
{
    if ((c >= 'a') && (c <= 'z')) {
        c += 'A' - 'a';
    }
    return c;
}
char board_read_turn(char board[8][8], int color_type)
{
    char c, figure;
    signed char x1, y1, x2, y2, turn_type;
    //Тип фигуры, выполняющей ход;
    GET(c);
    figure = ' ';
    if (iswhite(c)) {
        figure = c;
        GET(c);
    }

    //Буква поля с которого сделан ход
    if (isboardletter(c)) {
        x1 = c - 'a';
    } else {
        ERROR(sym, "Некорректная буква поля.");
    }

    //Цифра поля с которого сделан ход
    GET(c);
    if (isboarddigit(c)) {
        y1 = c - '1';
    } else {
        ERROR(sym, "Некорректная цифра поля.");
    }

    //Существет ли фигура на поле
    if (!ischessman(board[y1][x1])) {
        ERROR(sym, "На указанном поле нет фигур.");
    }

    if (color_type == 0) {
        if (isblack(board[y1][x1])) {
            ERROR(sym,
                  "На указанном поле черная фигура пока идет ход "
                  "белых.");
        }
    } else {
        if (iswhite(board[y1][x1])) {
            ERROR(sym,
                  "На указанном поле белая фигура пока идет ход "
                  "черных.");
        }
    }
    //Соответсвуют ли указанная фигура и фигура на указанном поле
    if (figure != ' ') {
        if (figure != board_toupper(board[y1][x1])) {
            ERROR(sym - 2, "Указанная и существующая фигуры отличаются.")
        }
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
    defoult:
        ERROR(sym, "Некорректный тип хода.");
    }

    //Буква поля куда сделан ход
    GET(c);
    if (isboardletter(c)) {
        x2 = c - 'a';
    } else {
        ERROR(sym, "Некорректная буква поля.");
    }

    //Цифра поля куда сделан ход
    GET(c);
    if (isboarddigit(c)) {
        y2 = c - '1';
    } else {
        ERROR(sym, "Некорректная цифра поля.");
    }

    //Проверка на взятие на проходе
    GET(c);
    if (c == 'e') {
        GET(c);
        if (c != '.') {
            ERROR(sym, "Некорректно обозначено взятие на проходе.");
        }
        GET(c);
        if (c != 'p') {
            ERROR(sym, "Некорректно обозначено взятие на проходе.");
        }
        GET(c);
        if (c != '.') {
            ERROR(sym, "Некорректно обозначено взятие на проходе.");
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
    char c;
    do {
        c = board_read_turn(board, 0);
        if (c == '\n') {
            ERROR(sym, "Символ новой строки в некорректном месте.");
        }
        if (c == '#') {
            return;
        }
        c = board_read_turn(board, 1);
        if (c == '\n') {
            line++;
            sym = 0;
        }
        if (c == '#') {
            return;
        }
    } while (c != '\0');
}
