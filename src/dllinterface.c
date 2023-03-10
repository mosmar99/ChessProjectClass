#include "dllinterface.h"
#include "makeBoard.h"
#include "makeMove.h"
#include "remi.h"

char *board[8][8];

void init(){
    initBoard(board);
    initGame(false);
}

void readBoard(char *rboard[8][8]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
        rboard[i][j] = board[i][j];
        }
    }
}

int tryTurn(int fx, int fy, int tx, int ty, char* mp, char* cp){

    point* fp = createPoint(fx, fy);
    point* tp = createPoint(tx, ty);

    move* mx = createMove(fp, tp, mp, cp);

    gameTurn(mx, board);
}
