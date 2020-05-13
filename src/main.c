int main()
{
    char board[8][8];
    board_init(board);
    board_print_plain(board);
    board_read(board);
    board_print_plain(board);
    return 0;
}

