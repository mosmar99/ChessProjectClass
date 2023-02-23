#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <makeMove.h>
#include <bishop.h>


static void initBishopBoard(char *board[8][8]);

int main(){
    char *board[8][8];
    bool validMove[8];
    initBishopBoard(board);

    //move north direction from d5 to d8
    move * m1 = createMove(createPoint(3,4), createPoint(3,7), "wB", "--");
    validMove[0] = checkBishopMove(m1, board);

    //move north east direction from d5 to g8 will be false since we are trying to "jump" a pawn
    move * m2 = createMove(createPoint(3,4), createPoint(6,7), "wB", "--");
    validMove[1] = checkBishopMove(m2, board);

    //move south east direction from d5 to h1
    move * m3 = createMove(createPoint(3,4), createPoint(7,0), "wB", "--");
    validMove[2] = checkBishopMove(m3, board);

    //move south west direction from d5 to a2
    move * m4 = createMove(createPoint(3,4), createPoint(0,1), "wB", "--");
    validMove[3] = checkBishopMove(m4, board);

    //move north west direction from d5 to a8
    move * m5 = createMove(createPoint(3,4), createPoint(0,7), "wB", "--");
    validMove[4] = checkBishopMove(m5, board);

    //pattern should look like this:
    //true  false   true    true    false   true    true    true
    assert(validMove[0] == false);
    assert(validMove[1] == false);
    assert(validMove[2] == true);
    assert(validMove[3] == true);
    assert(validMove[4] == true);


    destroyMove(m1);
    destroyMove(m2);
    destroyMove(m3);
    destroyMove(m4);
    destroyMove(m5);

    printf("BISHOP TEST PASSED\n");
    
    system("pause");
}

static void initBishopBoard(char *board[8][8]) {
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            board[i][j] = "--";
        }
    }

    // white
    board[4][3] = "wQ";
    board[1][3] = "wp";

    // black
    board[4][7] = "bp";
    board[6][5] = "bp";
}