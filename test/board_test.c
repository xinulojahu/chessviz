#include "board_test.h"
#include "board.h"
#include "board_read.h"
#include "board_validation.h"
#include "ctest.h"

char board[8][8];
board_turn turn;

CTEST(syntax, correct_turn)
{
    int expected = 0;
    int result = board_check_turn(board, &turn, "e2-e4", 0);
    ASSERT_EQUAL(expected, result);
}

CTEST(syntax, incorrect_turn)
{
    int expected = -1;
    int result = board_check_turn(board, &turn, "e0-e4", 0);
    ASSERT_EQUAL(expected, result);
}

CTEST(syntax, correct_figure_type)
{
    int expected = 0;
    int result = board_check_turn(board, &turn, "Pe2-e4", 0);
    ASSERT_EQUAL(expected, result);
}

CTEST(syntax, incorrect_figure_type)
{
    int expected = -1;
    int result = board_check_turn(board, &turn, "Oe2-e4", 0);
    ASSERT_EQUAL(expected, result);
}

CTEST(syntax, correct_taking)
{
    int expected = 0;
    int result = board_check_turn(board, &turn, "e2xe7", 0);
    ASSERT_EQUAL(expected, result);
}

CTEST(syntax, incorrect_taking)
{
    int expected = -1;
    int result = board_check_turn(board, &turn, "e2xe4", 0);
    ASSERT_EQUAL(expected, result);
}

CTEST(syntax, correct_non_taking)
{
    int expected = -1;
    int result = board_check_turn(board, &turn, "e2-e7", 0);
    ASSERT_EQUAL(expected, result);
}

CTEST(syntax, mate)
{
    int expected = 0;
    int result = board_check_turn(board, &turn, "e2-e4#", 0);
    ASSERT_EQUAL(expected, result);
}

CTEST(syntax, check)
{
    int expected = 0;
    int result = board_check_turn(board, &turn, "e2-e4+", 0);
    ASSERT_EQUAL(expected, result);
}

CTEST(syntax, ep)
{
    int expected = 0;
    int result = board_check_turn(board, &turn, "e2-e4e.p.", 0);
    ASSERT_EQUAL(expected, result);
}

CTEST(syntax, all)
{
    int expected = 0;
    int result = board_check_turn(board, &turn, "Pe2xe7e.p.#", 0);
    ASSERT_EQUAL(expected, result);
}
