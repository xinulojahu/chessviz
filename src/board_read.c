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

