#ifndef _PAWN_H
#define _PAWN_H

#include "makeMove.h"

// Decides whether or not the desired move is allowed or not.
//      move: a move struct filled with neccessary information for the desired move.
//      board: the string matrix representation of the current board state.
//      head: a linked list, with head pointing to the last made move.
//      wasEnPassant: boolean flag which is true ONLY if the move was En Passant.
// Returns: true if allowed, false if disallowed.
bool checkPawnMove(const move *const move, char *const board[8][8],
                   const history *const head, bool *wasEnPassant);

#endif