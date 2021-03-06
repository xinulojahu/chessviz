#ifndef board_validation_h
#define board_validetion_h

#include "board_read.h"

int board_check_turn(
        char board[8][8], board_turn* turn, char* string, int color_type);
int board_chessman_logic(char board[8][8], board_turn turn, int color_type);

int board_on_way_check(char board[8][8], board_turn turn);

int isboardletter(char c);

int isboarddigit(char c);

int iswhite(char c);

int isblack(char c);

int ischessman(char c);
#endif
