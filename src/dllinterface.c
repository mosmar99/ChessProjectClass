#include "dllinterface.h"
#include "makeMove.h"

void initGame(){
    char *board[8][8];
    initBoard(board);
    printBoard(board);
    play(board);
}

void readBoard(char *board[8][8]){


}

bool proposeMove(){

}