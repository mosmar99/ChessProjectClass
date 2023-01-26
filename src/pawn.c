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

typedef enum VerticalDirection
{
    UP,  // white may only move up
    DOWN // black may only move down
} VerticalDirection;

// Check for collisions given the desired move.
//      move: a move struct filled with neccessary information for the desired move.
//      board: the string matrix representation of the current board state.
//      deltaX: the delta in horizontal movement.
//      deltaY: the delta in vertical movement.
// Returns: true if collision is detected, false otherwise.
static bool checkCollisions(const move *const move, char *const board[8][8], short deltaX, short deltaY);

// Get the color of the player that tries to make the move.
//      piece: the string representation of a piece.
// Returns: the color of the selected piece.
static Color getColor(const char *const piece);

// Asserts that the move is properly filled with valid information.
//      move: a move struct filled with neccessary information for the desired move.
static void assertMove(const move *const move);

// Asserts that the board is properly properly configured.
//      board: the string matrix representation of the current board state.
static void assertBoard(char *const board[8][8]);

// Count the number of occurrenses of a specific character in a given string.
//      str: the string to search.
//      c: the character to count.
// Returns: The number of occurrenses found.
static unsigned int countCharInString(const char const *str, const unsigned char c);

// Get a copy of a string.
//      str: the string to copy
// Returns: a string.
static char *getCopyOfString(const char *const str);

bool checkPawnMove(const move *const move, char *const board[8][8])
{
    assertMove(move);
    assertBoard(board);

    // get color of the player and the allowed direction for that color
    Color player = getColor(move->movingPiece);
    assert(player == WHITE || player == BLACK);
    VerticalDirection dir = player == WHITE ? UP : DOWN;

    short deltaX = move->toPoint->col - move->fromPoint->col;
    short deltaY = move->toPoint->row - move->fromPoint->row;

    // check simple distance constraints:
    // 2 vertically and 0 horizontally
    // 1 vertically and either 0 or 1 horizontally
    if (!((deltaY == 2 && deltaX == 0) || (deltaY == 1 && (deltaX == 0 || deltaX == 1))))
        return false;

    // check vertical direction constraint, i.e. a player may only advance a pawn
    VerticalDirection tryDir = deltaY >= 0 ? UP : DOWN;
    if (tryDir != dir)
        return false;

    // simple check for special 2 vertical move from starting position
    if (deltaY == 2)
        if (player == WHITE && move->fromPoint->row != 1)
            return false;
        else if (player == BLACK && move->fromPoint->row != 6)
            return false;

    // at this point the desired move is plausible from the given 'to' and 'from' coordinates
    // check collisions
    if (checkCollisions(move, board, deltaX, deltaY))
        return false;
    return true;
}

static bool checkCollisions(const move *const move, char *const board[8][8], short deltaX, short deltaY)
{
    assert(move != NULL && board != NULL);

    unsigned short checkRow = move->fromPoint->row;
    unsigned short checkCol = move->fromPoint->col;

    if (abs(deltaX) == 1) // desire to move diagonally 1 step
    {
        assert(abs(deltaY) == 1);

        // check border
        if (checkRow + deltaY > 7 || checkRow + deltaY < 0 || checkCol + deltaX > 7 || checkCol + deltaX < 0)
            return true;

        if (strcmp(board[checkRow + deltaY][checkCol + deltaX], "--") != 0)
            return true;
        return false;
    }

    assert(deltaX == 0 && abs(deltaY) <= 2);

    while (deltaY != 0)
    {
        // advance 1 step
        checkRow += deltaY > 0 ? 1 : -1;

        // check border
        if (checkRow > 7 || checkRow < 0)
            return true;

        // check if there is a piece
        if (strcmp(board[checkRow][checkCol], "--") != 0)
            return true;

        // increment/decrement
        deltaY += deltaY > 0 ? -1 : 1;
    }

    return false;
}

static Color getColor(const char *const piece)
{
    assert(piece != NULL);

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

static void assertMove(const move *const move)
{
    assert(move != NULL);
    assert(move->movingPiece != NULL);
    assert(move->fromPoint != NULL);
    assert(move->capturedPiece != NULL);
    assert(move->toPoint != NULL);

    assert(strlen(move->movingPiece) == 2);
    assert(strlen(move->capturedPiece) == 2);
    assert(move->movingPiece[0] == 'b' || move->movingPiece[0] == 'w');
    assert(move->movingPiece[1] == 'p');
    assert(strlen(move->capturedPiece) == 2);

    assert(move->fromPoint->col >= 0 && move->fromPoint->col <= 7);
    assert(move->fromPoint->row >= 0 && move->fromPoint->row <= 7);
    assert(move->toPoint->col >= 0 && move->toPoint->col <= 7);
    assert(move->toPoint->row >= 0 && move->toPoint->row <= 7);
}

static void assertBoard(char *const board[8][8])
{
    assert(board != NULL);

    for (unsigned short row = 0; row < 8; row++)
    {
        assert(board[row] != NULL);
        for (unsigned short col = 0; col < 8; col++)
            assert(strlen(board[row][col]) == 2);
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
