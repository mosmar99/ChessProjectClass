#include <assert.h>

#include "makeMove.h"
#include "pawn.h"

void setupBoard(char *board[8][8]);

int main()
{
    char *board[8][8];
    setupBoard(board);

    move *adv1succ = createMove(createPoint(0, 1), createPoint(0, 2), "wp", "--");
    assert(checkPawnMove(adv1succ, board));
    destroyMove(adv1succ);

    move *adv2succ = createMove(createPoint(0, 1), createPoint(0, 3), "wp", "--");
    assert(checkPawnMove(adv2succ, board));
    destroyMove(adv2succ);

    move *adv2fail = createMove(createPoint(1, 0), createPoint(1, 2), "wp", "--");
    assert(!checkPawnMove(adv2fail, board));
    destroyMove(adv2fail);

    move *side = createMove(createPoint(1, 0), createPoint(0, 0), "wp", "--");
    assert(!checkPawnMove(side, board));
    destroyMove(side);

    move *attackfail = createMove(createPoint(0, 1), createPoint(1, 2), "wp", "--");
    assert(!checkPawnMove(attackfail, board));
    destroyMove(attackfail);

    move *wretreat = createMove(createPoint(2, 3), createPoint(2, 2), "wp", "--");
    assert(!checkPawnMove(wretreat, board));
    destroyMove(wretreat);

    move *bretreat = createMove(createPoint(5, 5), createPoint(5, 6), "bp", "--");
    assert(!checkPawnMove(bretreat, board));
    destroyMove(bretreat);

    move *wattack1succ = createMove(createPoint(2, 3), createPoint(1, 4), "wp", "--");
    assert(checkPawnMove(wattack1succ, board));
    destroyMove(wattack1succ);

    move *wattack2succ = createMove(createPoint(2, 3), createPoint(3, 4), "wp", "--");
    assert(checkPawnMove(wattack2succ, board));
    destroyMove(wattack2succ);

    move *battack1succ = createMove(createPoint(2, 4), createPoint(1, 3), "bp", "--");
    assert(checkPawnMove(battack1succ, board));
    destroyMove(battack1succ);

    move *battack2succ = createMove(createPoint(2, 4), createPoint(3, 3), "bp", "--");
    assert(checkPawnMove(battack2succ, board));
    destroyMove(battack2succ);

    move *wblock = createMove(createPoint(2, 3), createPoint(2, 4), "wp", "bp");
    assert(!checkPawnMove(wblock, board));
    destroyMove(wblock);

    move *bblock = createMove(createPoint(2, 4), createPoint(2, 3), "bp", "wp");
    assert(!checkPawnMove(bblock, board));
    destroyMove(bblock);

    printf("%s\n", "PAWN TEST PASSED");
    system("pause");
}

void setupBoard(char *board[8][8])
{
    for (int row = 0; row < 8; row++)
        for (int col = 0; col < 8; col++)
            board[row][col] = "--";

    board[1][0] = "wp";
    board[0][1] = "wp";
    board[3][2] = "wp";

    board[4][2] = "bp";
    board[2][4] = "bp";
    board[5][5] = "bp";
}
