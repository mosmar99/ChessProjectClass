#ifndef _ROOK_H
#define _ROOK_H

#include <stdbool.h>

/*This function checks if a move for a rook piece in a chess game is valid.
 It takes in three parameters: the starting position of the piece,
 the ending position of the piece, and the current state of the chess board*/
bool is_valid_rook_move(char* startPos, char* endPos, char* board[8][8]);
#endif