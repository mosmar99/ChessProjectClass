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

// Get the two imbedded coordinates inside input as a pair of Points.
//      input: the string input
// Returns: A PointPair containing the extracted pair of coordinates.
static PointPair *getCoordinates(const char const *input);

// Extract x and y coordinates from a string input.
//      coord: the string input
// Returns: A Point struct containing x and y coordinates.
static Point *extractCoord(const char *const coord);

// Get the color of the player that tries to make the move.
//      board: the board
//      startPos: the position of the selected piece that tries
//                to move, i.e. the the piece on "from" coordinate
// Returns: the color of the selected piece.
static Color getColor(char *const board[8][8], const Point *const startPos);

bool *checkPawnMove(const char *const input, char *const board[8][8])
{
    // check for basic validity of parameters
    assert(input != NULL && board != NULL);
    if (countCharInString(input, ' ') != 1 || strlen(input) != 5)
        return NULL;

    PointPair *pair = getCoordinates(input);
    assert(pair != NULL);
    if (pair->from == NULL || pair->to == NULL)
        return NULL;

    // at this point the desired move is correctly formatted and converted to workable data
    // begin check if the desired move is valid

    // get color of the player and the allowed direction for that color
    Color player = getColor(board, pair->from);
    if (player == EMPTY)
        return NULL;
    AllowedDirection dir = player == BLACK ? UP : DOWN;

    // check vertical direction constraint, i.e. a player may only advance a pawn
    AllowedDirection tryDir = pair->from->y > pair->to->y ? UP : DOWN;
    if (tryDir != dir)
        return false;

    unsigned short deltaX = abs(pair->from->x - pair->to->x);
    unsigned short deltaY = abs(pair->from->y - pair->to->y);

    // can at most move 1 horizontally and must always move 1 or 2 vertically
    if (deltaX > 1 || deltaY < 1 || deltaY > 2)
        return false;

    // check special 2 vertical move
    if ((deltaY == 2 && player == BLACK && pair->from->y != 6) || (player == WHITE && pair->from->y != 1))
        return false;
    
    //test
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

static PointPair *getCoordinates(const char const *input)
{
    assert(input != NULL);

    // make a copy of input
    char *inputCopy = getCopyOfString(input);

    // split input into two sub strings
    const char const *firstCoord = strtok(inputCopy, " ");
    const char const *secondCoord = strtok(NULL, " ");
    assert(firstCoord != NULL && secondCoord != NULL);

    // extract x and y coordinates from the sub strings
    Point *from = extractCoord(firstCoord);
    Point *to = extractCoord(secondCoord);

    // release memory
    free(inputCopy);

    // put the twin points together
    PointPair *pair = calloc(1, sizeof(PointPair));
    assert(pair != NULL);
    pair->from = from;
    pair->to = to;

    return pair;
}

static Point *extractCoord(const char *const coord)
{
    // check validity of parameter
    if (coord == NULL || strlen(coord) != 2)
        return NULL;
    if (!isalpha(coord[0]) || !isdigit(coord[1]))
        return NULL;

    Point *p = calloc(1, sizeof(Point));
    assert(p != NULL);

    // convert char to int
    if (isupper(coord[0]))
        p->x = coord[0] - 'A';
    else
        p->x = coord[0] - 'a';
    p->y = coord[1] - '0';

    // flip y coord
    p->y = 8 - p->y;

    return p;
}

static Color getColor(char *const board[8][8], const Point *const startPos)
{
    assert(startPos != NULL);

    switch (*board[startPos->y][startPos->x])
    {
    case 'b':
    case 'B':
        return BLACK;
    case 'w':
    case 'W':
        return WHITE;
    default: // empty spot
        return EMPTY;
    }
}
