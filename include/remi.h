#ifndef REMI_H
#define REMI_H

//empty
#include <stdbool.h>
#include <makeMove.h>

//FUNCTION RETURNS TRUE IF DRAW, IF NOT IT WILL RETURN FALSE
bool remi (char * const board[8][8], history *const hs, char **flag);

#endif