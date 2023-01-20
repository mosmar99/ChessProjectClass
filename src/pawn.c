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

// Count the number of occurrenses of a specific character in a given string.
//      str: the string to search
//      c: the character to count
// Returns: The number of occurrenses found.
static int countCharInString(const char const *str, const unsigned char c);

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

bool *checkPawnMove(const char *const input, char *board[8][8])
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
}

static int countCharInString(const char const *str, const unsigned char c)
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
