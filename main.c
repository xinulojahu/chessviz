#include <stdio.h>

int main()
{
    char chess[8][8];
    for (int j = 0; j <= 1; j++) {
        chess[7 * j][0] = chess[7 * j][7] = 'r' + ('A' - 'a') * j;
        chess[7 * j][1] = chess[7 * j][6] = 'n' + ('A' - 'a') * j;
        chess[7 * j][2] = chess[7 * j][5] = 'b' + ('A' - 'a') * j;
        chess[7 * j][3] = 'q' + ('A' - 'a') * j;
        chess[7 * j][4] = 'k' + ('A' - 'a') * j;

        for (int i = 0; i < 8; i++) {
            chess[1 + 5 * j][i] = 'p' + ('A' - 'a') * j;
            chess[2 + 2 * j][i] = '\0';
            chess[3 + 2 * j][i] = '\0';
        }
    }
    return 0;
}

