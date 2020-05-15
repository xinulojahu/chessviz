#include "board_test.h"
#include "board_read.h"
#include "board_validation.h"
#include "ctest.h"

char board[8][8];
board_turn turn;

CTEST(syntax, correct)
{
    int expected = 0;
    int result = board_check_turn(board, &turn, "e2-e4 ", 0);
    ASSERT_EQUAL(expected, result);
}

