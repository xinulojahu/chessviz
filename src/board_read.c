#include "board_print_plain.h"
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

typedef struct board_turn {
    signed char x1;
    signed char y1;
    signed char x2;
    signed char y2;
    signed char turn_type;
    signed char eg;
    char figure;
} board_turn;

//Сделать из маленькой буквы заглавную
char board_toupper(char c)
{
    if ((c >= 'a') && (c <= 'z')) {
        c += 'A' - 'a';
    }
    return c;
}
char board_read_turn(char board[8][8], board_turn* turn, int color_type)
{
    char c;
    //Тип фигуры, выполняющей ход;
    GET(c);
    turn->figure = ' ';
    if (iswhite(c)) {
        turn->figure = c;
        GET(c);
    }

    //Буква поля с которого сделан ход
    if (isboardletter(c)) {
        turn->x1 = c - 'a';
    } else {
        ERROR(sym, "Некорректная буква поля.");
    }

    //Цифра поля с которого сделан ход
    GET(c);
    if (isboarddigit(c)) {
        turn->y1 = c - '1';
    } else {
        ERROR(sym, "Некорректная цифра поля.");
    }

    //Существет ли фигура на поле
    if (!ischessman(board[turn->y1][turn->x1])) {
        ERROR(sym, "На указанном поле нет фигур.");
    } else if (color_type == 0) {
        if (isblack(board[turn->y1][turn->x1])) {
            ERROR(sym,
                  "На указанном поле черная фигура пока идет ход "
                  "белых.");
        }
    } else if (iswhite(board[turn->y1][turn->x1])) {
        ERROR(sym,
              "На указанном поле белая фигура пока идет ход "
              "черных.");
    }

    //Соответсвуют ли указанная фигура и фигура на указанном поле
    if (turn->figure != ' ') {
        if (turn->figure != board_toupper(board[turn->y1][turn->x1])) {
            ERROR(sym - 2, "Указанная и существующая фигуры отличаются.")
        }
    } else {
        turn->figure = board_toupper(board[turn->y1][turn->x1]);
    }

    //Тип хода
    GET(c);
    switch (c) {
    case '-':
        turn->turn_type = 0;
        break;
    case 'x':
        turn->turn_type = 1;
        break;
    default:
        ERROR(sym, "Некорректный тип хода.");
    }

    //Буква поля куда сделан ход
    GET(c);
    if (isboardletter(c)) {
        turn->x2 = c - 'a';
    } else {
        ERROR(sym, "Некорректная буква поля.");
    }

    //Цифра поля куда сделан ход
    GET(c);
    if (isboarddigit(c)) {
        turn->y2 = c - '1';
    } else {
        ERROR(sym, "Некорректная цифра поля.");
    }

    //Проверка верности указанного типа хода хода
    if (turn->turn_type == 1) {
        if (color_type == 0) {
            if (!isblack(board[turn->y2][turn->x2])) {
                ERROR(sym, "На указанном поле нет фигур соперника");
            }
        } else if (!iswhite(board[turn->y2][turn->x2])) {
            ERROR(sym, "На указанном поле нет фигур соперника");
        }
    } else if (ischessman(board[turn->y2][turn->x2])) {
        ERROR(sym, "На указаннам поле есть фигура соперника");
    }

    //Проверка на взятие на проходе
    GET(c);
    turn->eg = 0;
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
        turn->eg = 1;
    }

    return c;
}

unsigned int board_abs(int d)
{
    if (d < 0) {
        return -d;
    }
    return d;
}

void board_chess_moving(char board[8][8], board_turn turn)
{
    board[turn.y2][turn.x2] = board[turn.y1][turn.x1];
    board[turn.y1][turn.x1] = ' ';
}

void board_chessman_logic(char board[8][8], board_turn turn, int color_type)
{
    //Если пешка
    if (turn.figure == 'P') {
        // если ход на сруб
        if (turn.turn_type == 1) {
            if ((board_abs(turn.y2 - turn.y1) == 1)
                && (board_abs(turn.x2 - turn.x1) == 1)) {
                board_chess_moving(board, turn);
                return;
            }
            //Если ход не на сруб, то пешка идет по прямой
        } else if (turn.x1 == turn.x2) {
            //Если ход белых
            if (color_type == 0) {
                if (turn.y1 == 1) {
                    if (turn.y2 == 3) {
                        board_chess_moving(board, turn);
                        return;
                    }
                }
                if (turn.y2 - turn.y1 == 1) {
                    board_chess_moving(board, turn);
                    return;
                }
                //Если ход черных
            } else {
                if (turn.y1 == 6) {
                    if (turn.y2 == 4) {
                        board_chess_moving(board, turn);
                        return;
                    }
                }
                if (turn.y2 - turn.y1 == -1) {
                    board_chess_moving(board, turn);
                    return;
                }
            }
        }
        //Если return не случился, значит некорректные данные
        ERROR(sym, "Некорректное конечное поле");
    }
    if (turn.figure == 'K') {
        if (board_abs(turn.x1 - turn.x2) <= 1) {
            if (board_abs(turn.y1 - turn.y2) <= 1) {
                board_chess_moving(board, turn);
                return;
            }
        }
        ERROR(sym, "Некорректное конечное поле");
    }
}
void board_read(char board[8][8])
{
    char c;
    board_turn turn;
    do {
        c = board_read_turn(board, &turn, 0);
        board_chessman_logic(board, turn, 0);
        if (c == '\n') {
            ERROR(sym, "Символ новой строки в некорректном месте.");
        }
        if (c == '#') {
            return;
        }
        c = board_read_turn(board, &turn, 1);
        board_chessman_logic(board, turn, 1);
        if (c == '\n') {
            line++;
            sym = 0;
        }
        if (c == '#') {
            return;
        }
        board_print_plain(board);
    } while (c != '\0');
}
