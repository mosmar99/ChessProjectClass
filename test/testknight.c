#include <assert.h>
#include "makeMove.h"
#include "knight.h"
#include "boardlogic.h"

void testKnight(){
    char *board[8][8];
    initBoard(board);
    move * move1 = createMove(createPoint(0,0),createPoint(1,2),"wN", "bP");
    assert(checkKnightMove(move1, board) == true);

    move * move2 = createMove(createPoint(2,1),createPoint(1,2),"wN", "bP");
    assert(checkKnightMove(move1, board) == true);
    
    move * move3 = createMove(createPoint(8,8),createPoint(7,6),"wN", "bP");
    assert(checkKnightMove(move1, board) == true);

    move * move4 = createMove(createPoint(5,5),createPoint(8,8),"wN", "bP");
    assert(checkKnightMove(move1, board) == false);

    move * move5 = createMove(createPoint(0,0),createPoint(1,2),"wN", "wP");
    assert(checkKnightMove(move1, board) == false);

    destroyMove(move1);
    destroyMove(move2);
    destroyMove(move3);
    destroyMove(move4);
    destroyMove(move5);

}

void initBoard(char *board[8][8]) {
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            board[i][j] = "--";
        }
    }

    // white
    board[0][0] = "wR";
    board[0][1] = "wN";
    board[0][2] = "wB";
    board[0][3] = "wQ";
    board[0][4] = "wK";
    board[0][5] = "wB";
    board[0][6] = "wN";
    board[0][7] = "wR";
    board[1][0] = "wp";
    board[1][1] = "wp";
    board[1][2] = "wp";
    board[1][3] = "wp";
    board[1][4] = "wp";
    board[1][5] = "wp";
    board[1][6] = "wp";
    board[1][7] = "wp";

    // black
    board[7][0] = "bR";
    board[7][1] = "bN";
    board[7][2] = "bB";
    board[7][3] = "bQ";
    board[7][4] = "bK";
    board[7][5] = "bB";
    board[7][6] = "bN";
    board[7][7] = "bR";
    board[6][0] = "bp";
    board[6][1] = "bp";
    board[6][2] = "bp";
    board[6][3] = "bp";
    board[6][4] = "bp";
    board[6][5] = "bp";
    board[6][6] = "bp";
    board[6][7] = "bp";
}
