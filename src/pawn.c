#include "pawn.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define NULL ((void *)0)

typedef struct Point
{
    unsigned int x, y;
} Point;

// Count the number of occurrenses of a specific character in a given string.
//      str: the string to search
//      c: the character to count
// Returns: The number of occurrenses found, or -1 if invalid parameter(s).
static int countCharInString(const char const *str, const char c);

// Get a copy of a string.
//      str: the string to copy
// Returns: a string.
static char *getCopyOfString(const char *const str);

// Extract x and y coordinates from a string input.
//      coord: the string input
// Returns: A Point struct containing x and y coordinates.
static Point *extractCoord(const char *const coord);

bool *checkPawnMove(const char *const input, char *board[8][8])
{
    // check for basic validity of parameters
    if (input == NULL || board == NULL || strlen(input) != 5)
        return NULL;
    if (countCharInString(input, ' ') != 1)
        return NULL;

    // make a copy of input
    char *inputCopy = getCopyOfString(input);

    // split input into two sub strings
    const char const *firstCoord = strtok(inputCopy, " ");
    const char const *secondCoord = strtok(NULL, " ");
    assert(firstCoord != NULL && secondCoord != NULL);

    // extract x and y coordinates from the sub strings
    Point *from = extractCoord(firstCoord);
    Point *to = extractCoord(secondCoord);

    // check for correct format on desired move
    if (from == NULL || to == NULL)
        return NULL;

    // at this point the desired move is correctly formatted and converted to usable data
    // begin check if the move is valid to make

    // release memory
    free(inputCopy);
}

static int countCharInString(const char const *str, const char c)
{
    if (str == NULL)
        return -1;

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
