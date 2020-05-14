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
