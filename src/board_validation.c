#include "board_validation.h"
#include "board.h"
#include "board_read.h"

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

int isboardletter(char c)
{
    if ((c >= 'a') && (c <= 'h')) {
        return 1;
    }
    return 0;
}

int isboarddigit(char c)
{
    if ((c >= '1') && (c <= '8')) {
        return 1;
    }
    return 0;
}

int iswhite(char c)
{
    switch (c) {
    case 'P':
    case 'Q':
    case 'K':
    case 'R':
    case 'B':
    case 'N':
        return 1;
    default:
        return 0;
    }
}

int isblack(char c)
{
    return iswhite(c + 'A' - 'a');
}

int ischessman(char c)
{
    return iswhite(c) || isblack(c);
}
