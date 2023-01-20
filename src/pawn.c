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

// Extract x and y coordinates from a string input.
//      coord: the string input
// Returns: A Point struct containing x and y coordinates.
static Point *extractCoord(const char *const coord);

// Get the two coordinates from input
//      from: assigned to extracted from coordinate
//      to: assigned to extracted to coordinate
static void getCoordinates(const char *const input, Point *const from, Point *const to);

bool *checkPawnMove(const char *const input, char *board[8][8])
{
    // check basic validity of parameters
    if (input == NULL || board == NULL || strlen(input) != 5)
        return NULL;
    if (countCharInString(input, ' ') != 1)
        return NULL;

    Point *fromCoord, *toCoord;
    getCoordinates(input, fromCoord, toCoord);
    assert(fromCoord != NULL && toCoord != NULL);
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

    // match coordinates to match chess grid
    p->x++;
    p->y++;

    return p;
}

static void getCoordinates(const char *const input, Point *from, Point *to)
{
    // make a copy of input
    char *inputCopy = calloc(strlen(input) + 1, sizeof(char));
    assert(inputCopy != NULL);
    strncpy(inputCopy, input, strlen(input) + 1);

    // split input into two sub strings
    char *firstCoord = strtok(inputCopy, " ");
    char *secondCoord = strtok(NULL, " ");
    assert(firstCoord != NULL && secondCoord != NULL);

    // extract x and y coordinates from the sub strings
    Point *fromCoord = extractCoord(firstCoord);
    Point *toCoord = extractCoord(secondCoord);

    from = fromCoord;
    to = toCoord;
}
