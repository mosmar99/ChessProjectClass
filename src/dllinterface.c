#include "dllinterface.h"
#include "makeBoard.h"
#include "makeMove.h"

char *board[8][8];

void initGame(){ 
    initBoard(board);
}

void readBoard(char *rboard[8][8]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
        rboard[i][j] = board[i][j];
        }
    }
}

int turn(){

}

bool proposeMove(){

}