#ifndef board_h
#define board_h
#include "board_read.h"
void board_init(char board[8][8]);

void board_chess_moving(char board[8][8], board_turn turn);

unsigned int board_abs(int d);

char board_toupper(char c);
#endif
