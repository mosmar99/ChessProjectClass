#ifndef _PAWN_H
#define _PAWN_H

#include <stdbool.h>
#include "makemove.h"

// Decides whether or not the desired move is allowed or not.
//      move: a move struct filled with neccessary information for the desired move.
//      board: the string matrix representation of the current board state.
// Returns: true if allowed, false if disallowed.
bool checkPawnMove(const move *const move, char *const board[8][8]);

#endif