#include "board.h"

//Изменение пололожения фигуры на доске
void board_chess_moving(char board[8][8], board_turn turn)
{
    board[turn.y2][turn.x2] = board[turn.y1][turn.x1];
    board[turn.y1][turn.x1] = ' ';
}

//Модуль
unsigned int board_abs(int d)
{
    if (d < 0) {
        return -d;
    }
    return d;
}

//Сделать из маленькой буквы заглавную
char board_toupper(char c)
{
    if ((c >= 'a') && (c <= 'z')) {
        c += 'A' - 'a';
    }
    return c;
}

//Инициализировать доску
void board_init(char board[8][8])
{
    for (int j = 0; j <= 1; j++) {
        board[7 * j][0] = board[7 * j][7] = 'R' - ('A' - 'a') * j;
        board[7 * j][1] = board[7 * j][6] = 'N' - ('A' - 'a') * j;
        board[7 * j][2] = board[7 * j][5] = 'B' - ('A' - 'a') * j;
        board[7 * j][3] = 'Q' - ('A' - 'a') * j;
        board[7 * j][4] = 'K' - ('A' - 'a') * j;
        for (int i = 0; i < 8; i++) {
            board[1 + 5 * j][i] = 'P' - ('A' - 'a') * j;
            board[2 + 2 * j][i] = ' ';
            board[3 + 2 * j][i] = ' ';
        }
    }
}
