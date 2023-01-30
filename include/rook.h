#ifndef _ROOK_H
#define _ROOK_H

#include <stdbool.h>
#include "makeMove.h"


bool checkRookMove(const move *const move, char *const board[8][8]);
#endif