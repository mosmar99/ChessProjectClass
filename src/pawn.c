#include "pawn.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

typedef enum Color
{
    EMPTY,
    BLACK, // black initially at row 6, 7
    WHITE  // white initially at row 0, 1
} Color;

typedef enum AllowedDirection
{
    UP,  // white may only move up
    DOWN // black may only move down
} AllowedDirection;

// Get the color of the player that tries to make the move.
//      board: the board
//      piece: the string representation of a piece
// Returns: the color of the selected piece.
static Color getColor(char *const board[8][8], const char *const piece);

// Count the number of occurrenses of a specific character in a given string.
//      str: the string to search
//      c: the character to count
// Returns: The number of occurrenses found.
static unsigned int countCharInString(const char const *str, const unsigned char c);

// Get a copy of a string.
//      str: the string to copy
// Returns: a string.
static char *getCopyOfString(const char *const str);

bool checkPawnMove(const move *const move, char *const board[8][8])
{
    assert(move != NULL && board != NULL);

    // get color of the player and the allowed direction for that color
    Color player = getColor(board, move->movingPiece);
    assert(player == WHITE || player == BLACK);
    AllowedDirection dir = player == WHITE ? UP : DOWN;

    // check vertical direction constraint, i.e. a player may only advance a pawn
    AllowedDirection tryDir = move->fromPoint->row > move->toPoint->row ? UP : DOWN;
    if (tryDir != dir)
        return false;

    unsigned short deltaX = abs(move->fromPoint->col - move->toPoint->col);
    unsigned short deltaY = abs(move->fromPoint->row - move->toPoint->row);

    // check simple distance constraints
    // either 1 or 2 vertically, 0 or 1 horizontally
    if (!(deltaY == 1 || deltaY == 2) || !(deltaX == 0 || deltaX == 1))
        return false;
}

static Color getColor(char *const board[8][8], const char *const piece)
{
    assert(board != NULL && piece != NULL);

    switch (*piece)
    {
    case 'b':
        return BLACK;
    case 'w':
        return WHITE;
    case '-': // intentionally not a "default:", used to discover bugs
        return EMPTY;
    }
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
