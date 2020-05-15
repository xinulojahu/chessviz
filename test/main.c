#define CTEST_MAIN
//#define CTEST_SEGFAULT
#include "board.h"
#include "board_test.h"
#include "ctest.h"
#include <stdio.h>

int main(int argc, const char* argv[])
{
    board_init(board);
    int result = ctest_main(argc, argv);
    printf("End of tests!\n");
    return result;
}
