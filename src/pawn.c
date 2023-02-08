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
// Returns: true if OK, false otherwise.
static bool assertMove(const move *const move);

// Asserts that the board is properly properly configured.
//      board: the string matrix representation of the current board state.
// Returns: true if OK, false otherwise.
static bool assertBoard(char *const board[8][8]);

bool checkPawnMove(const move *const move, char *const board[8][8])
{
    if (!assertMove(move) || !assertBoard(board))
        return false;

    // get color of the player
    Color player = getColor(move->movingPiece);
    if (player != WHITE && player != BLACK)
        return false;

    const short deltaX = move->toPoint->col - move->fromPoint->col;
    const short deltaY = move->toPoint->row - move->fromPoint->row;

    // check vertical direction constraint, i.e. a player may only advance a pawn
    if ((deltaY >= 0 ? UP : DOWN) != (player == WHITE ? UP : DOWN))
        return false;

    // check simple distance constraints:
    // 2 vertically and 0 horizontally
    // 1 vertically and either 0 or 1 horizontally
    if (!((abs(deltaY) == 2 && deltaX == 0) || (abs(deltaY) == 1 && (deltaX == 0 || abs(deltaX) == 1))))
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

static bool checkCollisions(const move *const move, char *const board[8][8], const short deltaX, const short deltaY)
{
    if (move == NULL || board == NULL)
        return false;

    if (abs(deltaX) == 1) // desire to move diagonally 1 step, i.e. attack an enemy piece
    {
        if (abs(deltaY) != 1)
            return false;

        // the piece the pawn is moving to must be an enemy
        if (strcmp(board[move->toPoint->row][move->toPoint->col], *(move->movingPiece) == 'w' ? "bp" : "wp") != 0)
            return true;

        return false;
    }

    if (deltaX != 0 || abs(deltaY) > 2)
        return false;

    // start at fromPoint and explore direction to toPoint, checks for any obstacle
    // fromPoint and toPoint have already been checked for invalid indices

    const short offset = deltaY > 0 ? 1 : -1;
    for (unsigned short row = move->fromPoint->row; row != move->toPoint->row && row >= 0; row += offset)
        if (row + offset > 7 || strcmp(board[row + offset][move->fromPoint->col], "--") != 0)
            return true;

    return false;
}

static Color getColor(const char *const piece)
{
    if (piece == NULL)
        return EMPTY;

    switch (*piece)
    {
    case 'b':
        return BLACK;
    case 'w':
        return WHITE;
    default:
        return EMPTY;
    }
}

static bool assertMove(const move *const move)
{
    if (move == NULL)
        return false;
    if (move->movingPiece == NULL || move->fromPoint == NULL)
        return false;
    if (move->capturedPiece == NULL || move->toPoint == NULL)
        return false;

    if (strlen(move->movingPiece) != 2 || strlen(move->capturedPiece) != 2)
        return false;
    if (!(move->movingPiece[0] == 'b' || move->movingPiece[0] == 'w'))
        return false;
    if (move->movingPiece[1] != 'p' || strlen(move->capturedPiece) != 2)
        return false;

    // 'col' and 'row' are unsigned
    if (move->fromPoint->col > 7 || move->fromPoint->row > 7)
        return false;
    if (move->toPoint->col > 7 || move->toPoint->row > 7)
        return false;

    return true;
}

static bool assertBoard(char *const board[8][8])
{
    if (board == NULL)
        return false;

    for (unsigned short row = 0; row < 8; row++)
    {
        if (board[row] == NULL)
            return false;
        for (unsigned short col = 0; col < 8; col++)
            if (strlen(board[row][col]) != 2)
                return false;
    }

    return true;
}
