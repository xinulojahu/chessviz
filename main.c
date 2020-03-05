#include <stdio.h>
void board_print_plain(char board[8][8])
{
    for (int i = 7; i >= 0; i--) {
        printf("%d ", i + 1);
        for (int j = 0; j < 8; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("  ");
    for (char i = 'a'; i <= 'h'; i++) {
        printf("%c ", i);
    }
    printf("\n");
}

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
void board_read(char board[8][8])
{
    char c, figure;
    signed char x1, y1, x2, y2, turn;
    do {
        //Тип фигуры, выполняющей ход;
        c = getchar();
        figure = ' ';
        if (ischessman(c)) {
            figure = c;
            c = getchar();
        }
        //Буква поля с которого сделан ход
        if ((c >= 'a') && (c <= 'h')) {
            x1 = c - 'a';
        }
        //Цифра поля с которого сделан ход
        c = getchar();
        if ((c >= '1') && (c <= '8')) {
            y1 = c - '1';
        }

        //Тип хода
        c = getchar();
        switch (c) {
        case '-':
            turn = 0;
            break;
        case 'x':
            turn = 1;
            break;
        }

        //Буква поля куда сделан ход
        c = getchar();
        if ((c >= 'a') && (c <= 'h')) {
            x2 = c - 'a';
        }

        //Цифра поля куда сделан ход
        c = getchar();
        if ((c >= '1') && (c <= '8')) {
            y2 = c - '1';
        }

        //Проверка после хода
        c = getchar();
        if (ischessman(c)) {
            board[y1][x1] = c;
        }

        //Перемещение фигуры
        board[y2][x2] = board[y1][x1];
        board[y1][x1] = ' ';
    } while (0 /*c != '\0'*/);
}

int main()
{
    char board[8][8];
    board_init(board);
    board_print_plain(board);
    board_read(board);
    board_print_plain(board);
    return 0;
}

