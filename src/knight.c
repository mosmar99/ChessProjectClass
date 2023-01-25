#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "makemove.h"
#include "knight.h"

static bool isSameColour(const char *piece1, const char *piece2);

bool checkKnightMove(move *move, const char *board[8][8]){

    const int pattern[8] = {1,2,2,1,-1,-2,-2,-1};
    int i = 0;

    while (i < 8 && move->fromPoint && move->toPoint){
        if (!isSameColour(board[move->fromPoint->row][move->fromPoint->col], board[move->fromPoint->row][move->toPoint->col])
            && move->toPoint->col - move->fromPoint->row == pattern[i % 8]
            && move->toPoint->col - move->fromPoint->row == pattern[(i+2) % 8]){
            return true;
        }
        i++;
    }

    return false; 
}

static bool isSameColour(const char *piece1, const char *piece2){

    if (piece1[0] != piece2[0]){
        return false;
    } else {
        return true;
    }

    return false;
}