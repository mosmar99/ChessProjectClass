#ifndef CHECKMATE_H
#define CHECKMATE_H

#include <makeMove.h>
#include <stdbool.h>


//CHECKMATE
bool checkmate(char * const board[8][8], history *hs, char **flag);

bool check(const move * const m, char * const board[8][8]);

#endif