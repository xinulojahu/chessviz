#include "board_read.h"
#include "board.h"
#include "board_print_plain.h"
#include "board_validation.h"
#include <stdio.h>
#include <stdlib.h>

//Для ошибок
int line = 1, sym = 0;

//Проверка корректности введеного хода и конвертирование в структуру
int board_check_turn(
        char board[8][8], board_turn* turn, char* string, int color_type)
{
    char c;
    char* ptrstr = string;
    //Тип фигуры, выполняющей ход;
    NEXT(c);
    turn->figure = ' ';
    if (iswhite(c)) {
        turn->figure = c;
        NEXT(c);
    }

    //Буква поля с которого сделан ход
    if (isboardletter(c)) {
        turn->x1 = c - 'a';
    } else {
        ERROR(sym, "Некорректная буква поля.");
    }

    //Цифра поля с которого сделан ход
    NEXT(c);
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
    NEXT(c);
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
    NEXT(c);
    if (isboardletter(c)) {
        turn->x2 = c - 'a';
    } else {
        ERROR(sym, "Некорректная буква поля.");
    }

    //Цифра поля куда сделан ход
    NEXT(c);
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
        ERROR(sym, "На указаннам поле есть фигура");
    }

    //Проверка на взятие на проходе
    NEXT(c);
    turn->eg = 0;
    if (c == 'e') {
        NEXT(c);
        if (c != '.') {
            ERROR(sym, "Некорректно обозначено взятие на проходе.");
        }
        NEXT(c);
        if (c != 'p') {
            ERROR(sym, "Некорректно обозначено взятие на проходе.");
        }
        NEXT(c);
        if (c != '.') {
            ERROR(sym, "Некорректно обозначено взятие на проходе.");
        }
        NEXT(c);
        turn->eg = 1;
    }

    return 0;
}

//Модуль
unsigned int board_abs(int d)
{
    if (d < 0) {
        return -d;
    }
    return d;
}

//Изменение пололожения фигуры на доске
void board_chess_moving(char board[8][8], board_turn turn)
{
    board[turn.y2][turn.x2] = board[turn.y1][turn.x1];
    board[turn.y1][turn.x1] = ' ';
}

//Проверка наличия других фигур на пути
int board_on_way_check(char board[8][8], board_turn turn)
{
    int xstep = turn.x2 - turn.x1;
    int ystep = turn.y2 - turn.y1;
    int dif;
    if (xstep != 0) {
        dif = board_abs(xstep);
        xstep /= dif;
    }
    if (ystep != 0) {
        dif = board_abs(ystep);
        ystep /= dif;
    }

    for (int i = 1; i < dif; i++) {
        if (ischessman(board[turn.y1 + ystep * i][turn.x1 + xstep * i])) {
            return 0;
        }
    }
    return 1;
}

//Логика передвижения шахман
void board_chessman_logic(char board[8][8], board_turn turn, int color_type)
{
    unsigned int ydif = board_abs(turn.y2 - turn.y1);
    unsigned int xdif = board_abs(turn.x2 - turn.x1);
    //Если пешка
    if (turn.figure == 'P') {
        // если ход на сруб
        if (turn.turn_type == 1) {
            if ((ydif == 1) && (xdif == 1)) {
                board_chess_moving(board, turn);
                return;
            }
            //Если ход не на сруб, то пешка идет по прямой
        } else if (xdif == 0) {
            //Если ход белых
            if (color_type == 0) {
                if ((turn.y1 == 1) && (turn.y2 == 3)) {
                    board_chess_moving(board, turn);
                    return;
                }
                if (turn.y2 - turn.y1 == 1) {
                    board_chess_moving(board, turn);
                    return;
                }
                //Если ход черных
            } else {
                if ((turn.y1 == 6) && (turn.y2 == 4)) {
                    board_chess_moving(board, turn);
                    return;
                }
                if (turn.y2 - turn.y1 == -1) {
                    board_chess_moving(board, turn);
                    return;
                }
            }
        }
    }
    //Если король
    if (turn.figure == 'K') {
        if ((xdif <= 1) && (ydif <= 1)) {
            board_chess_moving(board, turn);
            return;
        }
    }
    //Если конь
    if (turn.figure == 'N') {
        if ((xdif == 1) || (xdif == 2)) {
            if (xdif + ydif == 3) {
                board_chess_moving(board, turn);
                return;
            }
        }
    }
    //Если слон
    if (turn.figure == 'B') {
        if (xdif == ydif) {
            if (board_on_way_check(board, turn)) {
                board_chess_moving(board, turn);
                return;
            } else {
                ERROR(sym, "Слон не может ходить через фигуры.");
            }
        }
    }
    //Если ладья
    if (turn.figure == 'R') {
        //Т.к. Фигура не может оставться на месте, оба условия не могут
        //выполниться
        if ((xdif == 0) || (ydif == 0)) {
            if (board_on_way_check(board, turn)) {
                board_chess_moving(board, turn);
                return;
            } else {
                ERROR(sym, "Ладья не может ходить через фигуры.");
            }
        }
    }
    //Если ферзь
    if (turn.figure == 'Q') {
        if ((xdif == 0) || (ydif == 0) || (xdif == ydif)) {
            if (board_on_way_check(board, turn)) {
                board_chess_moving(board, turn);
                return;
            } else {
                ERROR(sym, "Ферзь не может ходить через фигуры.");
            }
        }
    }

    //Если return не случился, значит некорректные данные
    ERROR(sym, "Некорректное конечное поле.");
}

//Ввод хода
int board_get_turn(char* string)
{
    int i = 0;
    do {
        string[i++] = getchar();
    } while ((string[i - 1] != ' ') && (string[i - 1] != '\n')
             && (string[i - 1] != '\0'));
    string[i] = '\0';
    return i;
}

//Функция ввода всех кодов в цикле
int board_read(char board[8][8])
{
    char string[12];
    int stringlen;
    board_turn turn;
    do {
        stringlen = board_get_turn(string);
        board_check_turn(board, &turn, string, 0);
        board_chessman_logic(board, turn, 0);
        if (string[stringlen - 2] == '#') {
            return 0;
        }
        if (string[stringlen - 1] == '\n') {
            ERROR(sym, "Символ новой строки в некорректном месте.");
        }
        stringlen = board_get_turn(string);
        board_check_turn(board, &turn, string, 1);
        board_chessman_logic(board, turn, 1);
        if (string[stringlen - 2] == '#') {
            return 0;
        }
        if (string[stringlen - 1] == '\n') {
            line++;
            sym = 0;
        } else {
            ERROR(sym, "Отсутствует символ новой строки после хода черных.");
        }
        board_print_plain(board);
    } while (1);
}
