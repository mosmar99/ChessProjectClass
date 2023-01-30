#ifndef _ROOK_H
#define _ROOK_H

#include <stdbool.h>
#include "makemove.h"


bool checkRookMove(const move *const move, char *const board[8][8]);
#endif