#include "dllinterface.h"
#include "makeBoard.h"
#include "makeMove.h"
#include "remi.h"

char *board[8][8];
history *head = NULL;
enum player turn = BLANCO;
char *remi_flag = NULL;
int remi_offer = 0;

void initGame(){
    initBoard(board);
    remi_flag = malloc(sizeof(char) * 50);
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

    if(!noGeneralErrors(mx, turn)){
        return 0;
    }

    if (noSpecificErrors(mx, applyMove(mx, board))){
        moveHistory(mx);

        if(remi(board, head, &remi_flag)){
            return 0;
        }
        
        turn = switchTurn(turn);
    } else {
        return 0;
    }

    return 1;
}

bool proposeMove(){

}