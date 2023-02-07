#include <assert.h>
#include "rook.h"
#include "makeMove.h"
#include <stdio.h>





void printBoard(char *board[8][8]) {
    char numbers[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    char letters[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    printf("\n");
    for (size_t i = 0; i < 8; i++)
    {
        printf("%c   ", *(numbers+(7-i)));
        for (size_t j = 0; j < 8; j++)
        {
            printf("%s  ", board[7-i][j]);
        }
        printf("\n");
    }

    printf("\n    ");
    fflush(stdout);

    for (size_t i = 0; i < 8; i++)
    {
        printf("%c   ", *(letters+i));
    }
    

    printf("\n\n");
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

    destroyMove(move1);
    destroyMove(move2);
    destroyMove(move3);
    destroyMove(move4);
    destroyMove(move5);
    
    printf("ROOK TEST PASSED\n");

    system("pause");
    return 0;
   
}