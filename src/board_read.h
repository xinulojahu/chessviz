#ifndef board_read_h
#define board_read_h
int board_read(char board[8][8]);

//структура для хранения хода в цифрах
typedef struct board_turn {
    signed char x1;
    signed char y1;
    signed char x2;
    signed char y2;
    signed char turn_type;
    signed char eg;
    char figure;
} board_turn;
#endif
