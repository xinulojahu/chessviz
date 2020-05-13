
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
