#ifndef _PAWN_H
#define _PAWN_H

#include <stdbool.h>

// Decides whether or not the desired move is allowed or not.
//      input: a string representation of the desired move, e.g. "A2 A4"
//      board: the string matrix representation of the current board state
// Returns: true if allowed, false if disallowed, NULL if invalid parameter(s)
bool *checkPawnMove(const char *const input, char *board[8][8]);

#endif