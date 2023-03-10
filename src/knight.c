#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "knight.h"

static bool isSameColour(const char *piece1, const char *piece2);

bool checkKnightMove(const move *const move, char *const board[8][8]) {

    const int pattern[8] = {1,2,2,1,-1,-2,-2,-1};
    int i = 0;

    while (i < 8 && move->fromPoint && move->toPoint){
        if (move->toPoint->col - move->fromPoint->col == pattern[i % 8]
            && move->toPoint->row - move->fromPoint->row == pattern[(i+2) % 8]){
            return true;
        }
        i++;
    }

    return false; 
}
