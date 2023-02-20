#ifndef QUEEN_H
#define QUEEN_H

#include <stdbool.h>
#include <makeMove.h>
/*
    Function to decide whether the requested Queen move is allowed
    Input: 
        The input move I.E. "QF6 QC3"
        The gameboard.
    Output:
        Boolean value, true if move is valid.
*/

bool checkQueenMove(const move *const m, char *const board[8][8]);

#endif