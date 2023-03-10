#include "king.h"
#include <stdio.h>
#include "queen.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <makeMove.h>
#include "checkmate.h"

static bool checkMovingDistance(const move * const move);
static bool checkLandingSquare(const move * const move);

bool checkKingMove(const move * const move, char * const board[8][8]){

    if(!checkMovingDistance(move) || !checkLandingSquare(move)){
        return false;
    }
    //if check returns true, the king will put itself in check, function will therefore return false.
    bool checked = check(move, board);
    return checked == true ? false : true;
}

static bool checkMovingDistance(const move * const m){
    int deltaRow = abs(m->fromPoint->row - m->toPoint->row);
    int deltaCol = abs(m->fromPoint->col - m->toPoint->col);
    if(deltaRow >= 2 || deltaCol >= 2){
        return false;
    }
    return true;
}

static bool checkLandingSquare(const move * const m){
    if(strrchr(m->movingPiece, 'w') && strrchr(m->capturedPiece, 'w')){
        return false;
    }
    if(strrchr(m->movingPiece, 'b') && strrchr(m->capturedPiece, 'b')){
        return false;
    }
    return true;
}