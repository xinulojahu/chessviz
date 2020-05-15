#include "board_read.h"
#include "board.h"
#include "board_print_plain.h"
#include "board_validation.h"
#include <stdlib.h>

//Для ошибок
int line = 1, sym = 0;

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
        if (board_check_turn(board, &turn, string, 0) == -1) {
            return -1;
        }

        if (board_chessman_logic(board, turn, 0) == -1) {
            return -1;
        }
        if (string[stringlen - 2] == '#') {
            return 0;
        }
        if (string[stringlen - 1] == '\n') {
            ERROR(sym, "Символ новой строки в некорректном месте.");
        }
        stringlen = board_get_turn(string);
        if (board_check_turn(board, &turn, string, 1) == -1) {
            return -1;
        }
        if (board_chessman_logic(board, turn, 1) == -1) {
            return -1;
        }
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
