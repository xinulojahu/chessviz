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

CTEST(P_movement, twospace)
{
    int expected = 0;
    board_check_turn(board, &turn, "e2-e4", 0);
    int result = board_chessman_logic(board, turn, 0);
    ASSERT_EQUAL(expected, result);
}

CTEST(P_movement, onespace)
{
    int expected = 0;
    board_check_turn(board, &turn, "e2-e3", 0);
    int result = board_chessman_logic(board, turn, 0);
    ASSERT_EQUAL(expected, result);
}

CTEST(P_movement, incorrect)
{
    int expected = -1;
    board_check_turn(board, &turn, "e2-d3", 0);
    int result = board_chessman_logic(board, turn, 0);
    ASSERT_EQUAL(expected, result);
}

CTEST(P_movement, taking)
{
    int expected = 0;
    board_check_turn(board, &turn, "e2-e6", 0);
    board_chess_moving(board, turn);
    board_check_turn(board, &turn, "e6xd7", 0);
    int result = board_chessman_logic(board, turn, 0);
    ASSERT_EQUAL(expected, result);
}

CTEST(K_movement, correct)
{
    int expected = 0;
    board_check_turn(board, &turn, "e1-e2", 0);
    int result = board_chessman_logic(board, turn, 0);
    board_chess_moving(board, turn);
    ASSERT_EQUAL(expected, result);
}

CTEST(K_movement, correct_diag)
{
    int expected = 0;
    board_check_turn(board, &turn, "e2-d3", 0);
    int result = board_chessman_logic(board, turn, 0);
    ASSERT_EQUAL(expected, result);
}

CTEST(K_movement, incorrect)
{
    int expected = -1;
    board_check_turn(board, &turn, "e2-e4", 0);
    int result = board_chessman_logic(board, turn, 0);
    board_check_turn(board, &turn, "e2-e1", 0);
    board_chess_moving(board, turn);
    ASSERT_EQUAL(expected, result);
}

CTEST(Q_movement, correct_diag)
{
    int expected = 0;
    board_check_turn(board, &turn, "d1-f3", 0);
    int result = board_chessman_logic(board, turn, 0);
    board_chess_moving(board, turn);
    ASSERT_EQUAL(expected, result);
}

CTEST(Q_movement, correct)
{
    int expected = 0;
    board_check_turn(board, &turn, "f3-a3", 0);
    int result = board_chessman_logic(board, turn, 0);
    board_chess_moving(board, turn);
    ASSERT_EQUAL(expected, result);
}

CTEST(Q_movement, incorrect)
{
    int expected = -1;
    board_check_turn(board, &turn, "a3xa1", 0);
    int result = board_chessman_logic(board, turn, 0);
    ASSERT_EQUAL(expected, result);
}

CTEST(B_movement, correct1)
{
    int expected = 0;
    board_check_turn(board, &turn, "f1-b5", 0);
    int result = board_chessman_logic(board, turn, 0);
    board_chess_moving(board, turn);
    ASSERT_EQUAL(expected, result);
}

CTEST(B_movement, correct2)
{
    int expected = 0;
    board_check_turn(board, &turn, "b5-a4", 0);
    int result = board_chessman_logic(board, turn, 0);
    board_chess_moving(board, turn);
    ASSERT_EQUAL(expected, result);
}

CTEST(B_movement, incorrect)
{
    int expected = -1;
    board_check_turn(board, &turn, "a4-a8", 0);
    int result = board_chessman_logic(board, turn, 0);
    ASSERT_EQUAL(expected, result);
}

CTEST(N_movement, correct1)
{
    int expected = 0;
    board_check_turn(board, &turn, "g1-f3", 0);
    int result = board_chessman_logic(board, turn, 0);
    board_chess_moving(board, turn);
    ASSERT_EQUAL(expected, result);
}

CTEST(N_movement, correct2)
{
    int expected = 0;
    board_check_turn(board, &turn, "f3-h4", 0);
    int result = board_chessman_logic(board, turn, 0);
    board_chess_moving(board, turn);
    ASSERT_EQUAL(expected, result);
}

CTEST(N_movement, incorrect)
{
    int expected = -1;
    board_check_turn(board, &turn, "h4-f4", 0);
    int result = board_chessman_logic(board, turn, 0);
    ASSERT_EQUAL(expected, result);
}

