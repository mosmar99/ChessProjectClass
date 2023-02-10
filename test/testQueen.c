#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <queen.h>
#include <makeMove.h>

static void initQueenBoard(char *board[8][8]);

int main(){
    char *board[8][8];
    bool validMove[8];
    initQueenBoard(board);

    //move north direction from d5 to d8
    move * m1 = createMove(createPoint(5,4), createPoint(8,4), "wQ", "--");
    validMove[0] = checkQueenMove(m1, board);

    //move north east direction from d5 to g8 will be false since we are trying to "jump" a pawn
    move * m2 = createMove(createPoint(5,4), createPoint(8,7), "wQ", "--");
    validMove[1] = checkQueenMove(m2, board);

    //move east direction from d5 to h5 landing on a pawn of the opposite color.
    move * m3 = createMove(createPoint(5,4), createPoint(5,8), "wQ", "bp");
    validMove[2] = checkQueenMove(m3, board);

    //move south east direction from d5 to h1
    move * m4 = createMove(createPoint(5,4), createPoint(1,8), "wQ", "--");
    validMove[3] = checkQueenMove(m4, board);

    //move south direction attempting to land on a pawn of the same color will thus be false
    move * m5 = createMove(createPoint(5,4), createPoint(2,4), "wQ", "wp");
    validMove[4] = checkQueenMove(m5, board);

    //move south west direction from d5 to a2
    move * m6 = createMove(createPoint(5,4), createPoint(2,1), "wQ", "--");
    validMove[5] = checkQueenMove(m6, board);

    //move west direction from d5 to a5
    move * m7 = createMove(createPoint(5,4), createPoint(5,1), "wQ", "--");
    validMove[6] = checkQueenMove(m7, board);

    //move north west direction from d5 to a8
    move * m8 = createMove(createPoint(5,4), createPoint(8,1), "wQ", "--");
    validMove[7] = checkQueenMove(m8, board);

    //pattern should look like this:
    //true  false   true    true    false   true    true    true
    assert(validMove[0] == true);
    assert(validMove[1] == false);
    assert(validMove[2] == true);
    assert(validMove[3] == true);
    assert(validMove[4] == false);
    assert(validMove[5] == true);
    assert(validMove[6] == true);
    assert(validMove[7] == true);


    destroyMove(m1);
    destroyMove(m2);
    destroyMove(m3);
    destroyMove(m4);
    destroyMove(m5);
    destroyMove(m6);
    destroyMove(m7);
    destroyMove(m8);

    printf("QUEEN TEST PASSED\n");
    
    system("pause");
}

static void initQueenBoard(char *board[8][8]) {
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
