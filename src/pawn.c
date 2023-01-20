#include "pawn.h"

#include <assert.h>
#include <string.h>

#define NULL ((void *)0)

struct Point
{
    unsigned char x, y;
};

// Decides whether or not the desired move is allowed or not.
//      input: a string representation of the desired move, e.g. "PA2 A4"
//      board: the string matrix representation of the current board state
// Returns: true if allowed, false if disallowed, NULL if invalid parameter(s)
bool *checkPawnMove(const char *const input, char *board[8][8])
{
    if (input == NULL || board == NULL)
        return NULL;
    if (strlen(input) < 6 || (input[0] != 'P' && input[0] != 'p'))
        return NULL;

    // extract coordinates from input, ex. "PA2 A4"
}