#include <assert.h>

#include "makeMove.h"
#include "pawn.h"

static void printBoard(char *board[8][8]);

int main()
{
    char *board[8][8] = {
        {"bp", "wp", "--", "--", "--", "--", "--", "wp"}, // 0
        {"wp", "--", "--", "--", "bp", "--", "--", "--"}, // 1
        {"--", "--", "--", "--", "bp", "--", "--", "--"}, // 2
        {"--", "--", "wp", "wp", "--", "--", "--", "wp"}, // 3
        {"--", "--", "bp", "--", "bp", "--", "--", "--"}, // 4
        {"--", "--", "--", "--", "--", "bp", "bp", "--"}, // 5
        {"--", "--", "--", "bp", "--", "--", "--", "--"}, // 6
        {"wp", "--", "--", "--", "--", "--", "--", "bp"}  // 7
    };
    //    0     1     2     3     4     5     6     7

    // printBoard(board);

#pragma region ***Out of bounds ***
    move *SW00 = createMove(createPoint(0, 0), createPoint(-1, -1), "bp", "--");
    assert(!checkPawnMove(SW00, board));
    destroyMove(SW00);

    move *NW70 = createMove(createPoint(7, 0), createPoint(8, -1), "wp", "--");
    assert(!checkPawnMove(NW70, board));
    destroyMove(NW70);

    move *NE77 = createMove(createPoint(7, 7), createPoint(8, 8), "bp", "--");
    assert(!checkPawnMove(NE77, board));
    destroyMove(NE77);

    move *SW07 = createMove(createPoint(0, 7), createPoint(-1, 8), "wp", "--");
    assert(!checkPawnMove(SW07, board));
    destroyMove(SW07);
#pragma endregion

#pragma region ***Two step FAIL ***
    move *w37 = createMove(createPoint(7, 3), createPoint(7, 5), "wp", "--");
    assert(!checkPawnMove(w37, board));
    destroyMove(w37);

    move *w01 = createMove(createPoint(1, 0), createPoint(1, 2), "wp", "--");
    assert(!checkPawnMove(w01, board));
    destroyMove(w01);

    move *b44 = createMove(createPoint(4, 4), createPoint(4, 2), "bp", "--");
    assert(!checkPawnMove(b44, board));
    destroyMove(b44);

    move *b42 = createMove(createPoint(2, 4), createPoint(2, 2), "bp", "--");
    assert(!checkPawnMove(b42, board));
    destroyMove(b42);
#pragma endregion

#pragma region ***Two step SUCC ***
    move *w10 = createMove(createPoint(0, 1), createPoint(0, 3), "wp", "--");
    assert(checkPawnMove(w10, board));
    destroyMove(w10);

    move *b63 = createMove(createPoint(3, 6), createPoint(3, 4), "bp", "--");
    assert(checkPawnMove(b63, board));
    destroyMove(b63);
#pragma endregion

#pragma region ***One step FAIL ***
    move *w32 = createMove(createPoint(2, 3), createPoint(2, 4), "wp", "bp");
    assert(!checkPawnMove(w32, board));
    destroyMove(w32);

    move *b24 = createMove(createPoint(4, 2), createPoint(4, 1), "bp", "bp");
    assert(!checkPawnMove(b24, board));
    destroyMove(b24);
#pragma endregion

#pragma region ***One step SUCC ***
    move *b55 = createMove(createPoint(5, 5), createPoint(5, 4), "bp", "--");
    assert(checkPawnMove(b55, board));
    destroyMove(b55);

    move *w33 = createMove(createPoint(3, 3), createPoint(3, 4), "wp", "--");
    assert(checkPawnMove(w33, board));
    destroyMove(w33);
#pragma endregion

#pragma region ***Direction FAIL ***
    move *b56 = createMove(createPoint(6, 5), createPoint(6, 6), "bp", "--");
    assert(!checkPawnMove(b56, board));
    destroyMove(b56);

    w32 = createMove(createPoint(2, 3), createPoint(2, 2), "wp", "--");
    assert(!checkPawnMove(w32, board));
    destroyMove(w32);
#pragma endregion

#pragma region ***Attack SUCC ***
    w33 = createMove(createPoint(3, 3), createPoint(4, 4), "wp", "bp");
    assert(checkPawnMove(w33, board));
    destroyMove(w33);

    b44 = createMove(createPoint(4, 4), createPoint(3, 3), "bp", "wp");
    assert(checkPawnMove(b44, board));
    destroyMove(b44);
#pragma endregion

#pragma region ***Attack FAIL ***
    move *b14 = createMove(createPoint(4, 1), createPoint(3, 0), "bp", "--");
    assert(!checkPawnMove(b14, board));
    destroyMove(b14);

    b56 = createMove(createPoint(6, 5), createPoint(7, 5), "bp", "--");
    assert(!checkPawnMove(b56, board));
    destroyMove(b56);

    w32 = createMove(createPoint(2, 3), createPoint(1, 4), "wp", "--");
    assert(!checkPawnMove(w32, board));
    destroyMove(w32);

    w32 = createMove(createPoint(2, 3), createPoint(3, 4), "wp", "--");
    assert(!checkPawnMove(w32, board));
    destroyMove(w32);
#pragma endregion

    printf("%s\n", "PAWN TEST PASSED");
    system("pause");
}

static void printBoard(char *board[8][8])
{
    char numbers[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    char letters[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    printf("\n");
    for (size_t i = 0; i < 8; i++)
    {
        printf("%c   ", *(numbers + (7 - i)));
        for (size_t j = 0; j < 8; j++)
        {
            printf("%s  ", board[7 - i][j]);
        }
        printf("\n");
    }

    printf("\n    ");
    fflush(stdout);

    for (size_t i = 0; i < 8; i++)
    {
        printf("%c   ", *(letters + i));
    }

    printf("\n\n");
}
