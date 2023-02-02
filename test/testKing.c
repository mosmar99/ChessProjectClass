#include <stdio.h>
#include <makeMove.h>
#include <king.h>
#include <assert.h>

static void initBoard(char *board[8][8]);

void main (){
    char *board[8][8];
    bool validMove[8];
    initBoard(board);

    //d4 - d5
    move * m1 = createMove(createPoint(4,4), createPoint(5,4), "wK", "--");
    validMove[0] = checkKingMove(m1, board);

    //d4 - e5
    move * m2 = createMove(createPoint(4,4), createPoint(5,5), "wK", "--");
    validMove[1] = checkKingMove(m2, board);

    //d4 - e4
    move * m3 = createMove(createPoint(4,4), createPoint(4,5), "wK", "--");
    validMove[2] = checkKingMove(m3, board);

    //d4 - e3
    move * m4 = createMove(createPoint(4,4), createPoint(3,5), "wK", "--");
    validMove[3] = checkKingMove(m4, board);

    //d4 - d3
    move * m5 = createMove(createPoint(4,4), createPoint(3,4), "wK", "--");
    validMove[4] = checkKingMove(m5, board);

    //d4 - c3
    move * m6 = createMove(createPoint(4,4), createPoint(3,3), "wK", "bR");
    validMove[5] = checkKingMove(m6, board);

    //d4 - c4
    move * m7 = createMove(createPoint(4,4), createPoint(4,3), "wK", "--");
    validMove[6] = checkKingMove(m7, board);

    //d4 - c5
    move * m8 = createMove(createPoint(4,4), createPoint(5,3), "wK", "--");
    validMove[7] = checkKingMove(m8, board);

    assert(validMove[0] == false);
    assert(validMove[1] == false);
    assert(validMove[2] == false);
    assert(validMove[3] == false);
    assert(validMove[4] == true);
    assert(validMove[5] == true);
    assert(validMove[6] == false);
    assert(validMove[7] == true);


    destroyMove(m1);
    destroyMove(m2);
    destroyMove(m3);
    destroyMove(m4);
    destroyMove(m5);
    destroyMove(m6);
    destroyMove(m7);
    destroyMove(m8);

    printf("KING TEST PASSED\n");
    
    system("pause");
}

static void initBoard(char *board[8][8]) {
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            board[i][j] = "--";
        }
    }

    // white
    board[3][3] = "wK";
    board[1][3] = "wp";

    // black
    board[7][0] = "bQ";
    board[4][0] = "bN";
    board[2][5] = "bN";
    board[0][6] = "bB";
}
