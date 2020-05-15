#include "board_read.h"
#include "board.h"
#include "board_print_plain.h"
#include "board_validation.h"
#include <stdlib.h>

//Для ошибок
int line = 1, sym = 0;

//Логика передвижения шахман
int board_chessman_logic(char board[8][8], board_turn turn, int color_type)
{
    unsigned int ydif = board_abs(turn.y2 - turn.y1);
    unsigned int xdif = board_abs(turn.x2 - turn.x1);
    //Если пешка
    if (turn.figure == 'P') {
        // если ход на сруб
        if (turn.turn_type == 1) {
            if ((ydif == 1) && (xdif == 1)) {
                board_chess_moving(board, turn);
                return 0;
            }
            //Если ход не на сруб, то пешка идет по прямой
        } else if (xdif == 0) {
            //Если ход белых
            if (color_type == 0) {
                if ((turn.y1 == 1) && (turn.y2 == 3)) {
                    board_chess_moving(board, turn);
                    return 0;
                }
                if (turn.y2 - turn.y1 == 1) {
                    board_chess_moving(board, turn);
                    return 0;
                }
                //Если ход черных
            } else {
                if ((turn.y1 == 6) && (turn.y2 == 4)) {
                    board_chess_moving(board, turn);
                    return 0;
                }
                if (turn.y2 - turn.y1 == -1) {
                    board_chess_moving(board, turn);
                    return 0;
                }
            }
        }
    }
    //Если король
    if (turn.figure == 'K') {
        if ((xdif <= 1) && (ydif <= 1)) {
            board_chess_moving(board, turn);
            return 0;
        }
    }
    //Если конь
    if (turn.figure == 'N') {
        if ((xdif == 1) || (xdif == 2)) {
            if (xdif + ydif == 3) {
                board_chess_moving(board, turn);
                return 0;
            }
        }
    }
    //Если слон
    if (turn.figure == 'B') {
        if (xdif == ydif) {
            if (board_on_way_check(board, turn)) {
                board_chess_moving(board, turn);
                return 0;
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
                return 0;
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
                return 0;
            } else {
                ERROR(sym, "Ферзь не может ходить через фигуры.");
            }
        }
    }

    //Если return 0 не случился, значит некорректные данные
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
