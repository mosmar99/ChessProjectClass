#include <assert.h>
#include "rook.h"
#include "makeMove.h"
#include <stdio.h>




static void initBoard(char *board[8][8]) {
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            board[i][j] = "--";
        }
    }

    // white
    board[2][1] = "wR";
    board[5][1] = "Wp";
    board[0][4] = "bp";

    // black
    board[0][4] = "bp";
    board[2][4] = "bp";
    board[5][5] = "bp";
}

int main() {
    char *board[8][8];
    initBoard(board);
    
    
    
    move *move1 = createMove(createPoint(0, 0), createPoint(0, 4), "wR", "bp");
    assert(checkRookMove(move1, board) == true);

    move *move2 = createMove(createPoint(0, 0), createPoint(4, 4), "wR", "bp");
    assert(checkRookMove(move2, board) == false);

    move *move3 = createMove(createPoint(0, 0), createPoint(1, 0), "wR", "bp");
    assert(checkRookMove(move3, board) == true);

    move *move4 = createMove(createPoint(0, 0), createPoint(1, 2), "wR", "bp");
    assert(checkRookMove(move4, board) == false);

    move *move5 = createMove(createPoint(0, 0), createPoint(0, 7), "wR", "wp");
    assert(checkRookMove(move5, board) == true);
    
    //(testing if it jump)
    board[0][2] = "bp"; 
    move *move6 = createMove(createPoint(0, 0), createPoint(3, 0), "wR", "bp");
    assert(checkRookMove(move6, board) == false); 

    destroyMove(move1);
    destroyMove(move2);
    destroyMove(move3);
    destroyMove(move4);
    destroyMove(move5);
    destroyMove(move6);
    
    printf("ROOK TEST PASSED\n");

    system("pause");
    return 0;
   
}