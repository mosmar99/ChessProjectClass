#ifndef BISHOP_H
#define BISHOP_H

#include <stdbool.h>
/*
    Function to decide whether the requested bishop move is allowed
    Criteria:
        We only move on diagonals
        We do not "jump" colors.
        Nothing is in our path
        The "landing square" does not contain a piece of the same colour.
    Input: 
        The input move I.E. "F6 C3"
        The gameboard.
    Output:
        Boolean value, true if move is valid.

*/
bool checkBishopMove(char *input, char *board[8][8]);

#endif