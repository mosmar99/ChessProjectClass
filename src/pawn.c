#include "pawn.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define NULL ((void *)0)

typedef struct Point
{
    unsigned short x, y;
} Point;

typedef struct PointPair
{
    Point *to, *from;
} PointPair;

typedef enum Color
{
    EMPTY,
    BLACK,
    WHITE
} Color;

typedef enum AllowedDirection
{
    UP,  // black may only move up
    DOWN // white may only move down
} AllowedDirection;

// Count the number of occurrenses of a specific character in a given string.
//      str: the string to search
//      c: the character to count
// Returns: The number of occurrenses found.
static unsigned int countCharInString(const char const *str, const unsigned char c);

// Get a copy of a string.
//      str: the string to copy
// Returns: a string.
static char *getCopyOfString(const char *const str);

// Get the color of the player that tries to make the move.
//      board: the board
//      startPos: the position of the selected piece that tries
//                to move, i.e. the the piece on "from" coordinate
// Returns: the color of the selected piece.
static Color getColor(const char *const board[8][8], const char *const movingPiece);

bool checkPawnMove(move *move, const char *const board[8][8])
{
    // check for basic validity of parameters
    assert(move != NULL && board != NULL);

    // get color of the player and the allowed direction for that color
    Color player = getColor(board, move->movingPiece);
    if (player == EMPTY)
        return NULL;
    AllowedDirection dir = player == BLACK ? UP : DOWN;

    // check vertical direction constraint, i.e. a player may only advance a pawn
    AllowedDirection tryDir = move->fromPoint->row > move->toPoint->row ? UP : DOWN;
    if (tryDir != dir)
        return false;

    unsigned short deltaX = abs(move->fromPoint->col - move->toPoint->col);
    unsigned short deltaY = abs(move->fromPoint->row - move->toPoint->row);

    // can at most move 1 horizontally and must always move 1 or 2 vertically
    if (deltaX > 1 || deltaY < 1 || deltaY > 2)
        return false;

    // check special 2 vertical move
    if ((deltaY == 2 && player == BLACK && move->fromPoint->row != 6) || (player == WHITE && move->fromPoint->row != 1))
        return false;
}

static unsigned int countCharInString(const char const *str, const unsigned char c)
{
    assert(str != NULL);

    int counter = 0;
    for (const char *ptr = str; *ptr != 0; ptr++)
        if (*ptr == c)
            counter++;

    return counter;
}

static char *getCopyOfString(const char *const str)
{
    assert(str != NULL);

    // +1 for null termimator
    char *newStr = calloc(strlen(str) + 1, sizeof(char));
    assert(newStr != NULL);

    strncpy(newStr, str, strlen(str));

    return newStr;
}

static Color getColor(const char *const board[8][8], const char *const movingPiece)
{
    assert(board != NULL && movingPiece != NULL);
}
