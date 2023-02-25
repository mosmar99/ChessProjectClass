#include <assert.h>

#include "pawn.h"

int main()
{
    char *board[8][8] = {
        {"bp", "wp", "--", "--", "--", "--", "--", "wp"}, // 0  1
        {"wp", "--", "--", "--", "bp", "--", "--", "--"}, // 1  2
        {"--", "--", "--", "--", "bp", "--", "--", "--"}, // 2  3
        {"--", "--", "wp", "wp", "--", "--", "--", "wp"}, // 3  4
        {"wp", "bp", "bp", "--", "bp", "--", "--", "--"}, // 4  5
        {"--", "--", "--", "--", "--", "bp", "bp", "--"}, // 5  6
        {"--", "--", "--", "bp", "--", "--", "--", "--"}, // 6  7
        {"wp", "--", "--", "--", "--", "--", "--", "bp"}  // 7  8
    };
    //    0     1     2     3     4     5     6     7
    //    a     b     c     d     e     f     g     h

    history *head = NULL;
    bool wasEnPassant = false;

#pragma region ***Out of bounds ***
    move *SW00 = createMove(createPoint(0, 0), createPoint(-1, -1), "bp", "--");
    assert(!checkPawnMove(SW00, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(SW00);

    move *NW70 = createMove(createPoint(7, 0), createPoint(8, -1), "wp", "--");
    assert(!checkPawnMove(NW70, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(NW70);

    move *NE77 = createMove(createPoint(7, 7), createPoint(8, 8), "bp", "--");
    assert(!checkPawnMove(NE77, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(NE77);

    move *SW07 = createMove(createPoint(0, 7), createPoint(-1, 8), "wp", "--");
    assert(!checkPawnMove(SW07, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(SW07);
#pragma endregion

#pragma region ***Two step FAIL ***
    move *w37 = createMove(createPoint(7, 3), createPoint(7, 5), "wp", "--");
    assert(!checkPawnMove(w37, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(w37);

    move *w01 = createMove(createPoint(1, 0), createPoint(1, 2), "wp", "--");
    assert(!checkPawnMove(w01, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(w01);

    move *b44 = createMove(createPoint(4, 4), createPoint(4, 2), "bp", "--");
    assert(!checkPawnMove(b44, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(b44);

    move *b42 = createMove(createPoint(2, 4), createPoint(2, 2), "bp", "--");
    assert(!checkPawnMove(b42, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(b42);
#pragma endregion

#pragma region ***Two step SUCC ***
    move *w10 = createMove(createPoint(0, 1), createPoint(0, 3), "wp", "--");
    assert(checkPawnMove(w10, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(w10);

    move *b63 = createMove(createPoint(3, 6), createPoint(3, 4), "bp", "--");
    assert(checkPawnMove(b63, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(b63);
#pragma endregion

#pragma region ***One step FAIL ***
    move *w32 = createMove(createPoint(2, 3), createPoint(2, 4), "wp", "bp");
    assert(!checkPawnMove(w32, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(w32);

    move *b24 = createMove(createPoint(4, 2), createPoint(4, 1), "bp", "bp");
    assert(!checkPawnMove(b24, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(b24);
#pragma endregion

#pragma region ***One step SUCC ***
    move *b55 = createMove(createPoint(5, 5), createPoint(5, 4), "bp", "--");
    assert(checkPawnMove(b55, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(b55);

    move *w33 = createMove(createPoint(3, 3), createPoint(3, 4), "wp", "--");
    assert(checkPawnMove(w33, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(w33);
#pragma endregion

#pragma region ***Direction FAIL ***
    move *b56 = createMove(createPoint(6, 5), createPoint(6, 6), "bp", "--");
    assert(!checkPawnMove(b56, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(b56);

    w32 = createMove(createPoint(2, 3), createPoint(2, 2), "wp", "--");
    assert(!checkPawnMove(w32, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(w32);
#pragma endregion

#pragma region ***Attack SUCC ***
    w33 = createMove(createPoint(3, 3), createPoint(4, 4), "wp", "bp");
    assert(checkPawnMove(w33, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(w33);

    b44 = createMove(createPoint(4, 4), createPoint(3, 3), "bp", "wp");
    assert(checkPawnMove(b44, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(b44);

    w32 = createMove(createPoint(2, 3), createPoint(1, 4), "wp", "--");
    assert(checkPawnMove(w32, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(w32);
#pragma endregion

#pragma region ***Attack FAIL ***
    move *b14 = createMove(createPoint(4, 1), createPoint(3, 0), "bp", "--");
    assert(!checkPawnMove(b14, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(b14);

    b56 = createMove(createPoint(6, 5), createPoint(7, 5), "bp", "--");
    assert(!checkPawnMove(b56, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(b56);

    w32 = createMove(createPoint(2, 3), createPoint(3, 4), "wp", "--");
    assert(!checkPawnMove(w32, board, head, &wasEnPassant));
    assert(!wasEnPassant);
    destroyMove(w32);
#pragma endregion

#pragma region ***En passant SUCC ***
    head = calloc(1, sizeof(history));
    assert(head != NULL);
    move *last = createMove(createPoint(1, 6), createPoint(1, 4), "bp", "--");
    head->mx = last;

    move *w14 = createMove(createPoint(0, 4), createPoint(1, 5), "wp", "--");
    assert(checkPawnMove(w14, board, head, &wasEnPassant));
    assert(wasEnPassant);
    wasEnPassant = false;

    destroyMove(last);
    free(head);
#pragma endregion

#pragma region ***En passant FAIL ***
    head = calloc(1, sizeof(history));
    assert(head != NULL);
    last = createMove(createPoint(1, 5), createPoint(1, 4), "bp", "--");
    head->mx = last;

    w14 = createMove(createPoint(0, 4), createPoint(1, 5), "wp", "--");
    wasEnPassant = false;
    assert(!checkPawnMove(w14, board, head, &wasEnPassant));
    assert(!wasEnPassant);

    destroyMove(last);
    free(head);
#pragma endregion

    printf("\n%s\n\n", "PAWN TEST PASSED");
}
