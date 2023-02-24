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
//      head: a linked list, with head pointing to the last made move.
// Returns: true if collision is detected, otherwise false.
static bool checkCollisions(const move *const move, char *const board[8][8],
                            short deltaX, short deltaY,
                            const history *const head);

// Handler for checking validity of en passant move
//      move: a move struct filled with neccessary information for the desired move.
//      board: the string matrix representation of the current board state.
//      head: a linked list, with head pointing to the last made move.
// Returns: true if en passant is allowed, otherwise false.
static bool checkEnPassant(const move *const move, char *const board[8][8], const history *const head);

// Checks the criteria: "The capturing pawn must have advanced exactly tree ranks to
//                       perform this move.".
//      move: a move struct filled with neccessary information for the desired move.
//      board: the string matrix representation of the current board state.
// Returns true if the criteria is fulfilled, otherwise false.
static bool checkEnPassantStep1(const move *const move, char *const board[8][8]);

// Checks the criterias: "The captured pawn must have moved two squares in one move,
//                        landing right next to the capturing pawn.",
//                        and
//                        "The en passant capture must be performed on the turn
//                        immediately after the pawn being captured moves.
//                        If the player does not capture en passant on that turn
//                        they no longer can do it later."
//      move: a move struct filled with neccessary information for the desired move.
//      board: the string matrix representation of the current board state.
//      head: a linked list, with head pointing to the last made move.
// Returns true if the criterias are fulfilled, otherwise false.
static bool checkEnPassantStep2And3(const move *const move, char *const board[8][8], const history *const head);

// Get the color of the player that tries to make the move.
//      piece: the string representation of a piece.
// Returns: the color of the selected piece.
static Color getColor(const char *const piece);

// Asserts that the move is properly filled with valid information.
//      move: a move struct filled with neccessary information for the desired move.
// Returns: true if OK, otherwise false.
static bool assertMove(const move *const move);

// Asserts that the board is properly properly configured.
//      board: the string matrix representation of the current board state.
// Returns: true if OK, otherwise false.
static bool assertBoard(char *const board[8][8]);

bool checkPawnMove(const move *const move, char *const board[8][8],
                   const history *const head, bool *wasEnPassant)
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
    if (checkCollisions(move, board, deltaX, deltaY, head))
        return false;

    return true;
}

static bool checkCollisions(const move *const move, char *const board[8][8],
                            const short deltaX, const short deltaY,
                            const history *const head)
{
    if (abs(deltaX) == 1) // desire to move diagonally 1 step, i.e. attack an enemy piece
    {
        if (abs(deltaY) != 1)
            return false;

        // check if the desired move is an en passant move
        if (checkEnPassant(move, board, head))
            return false;

        // a normal attack:
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

static bool checkEnPassant(const move *const move, char *const board[8][8], const history *const head)
{
    /* The following criterias must be fulfilled for valid en passant:
    1. The capturing pawn must have advanced exactly tree ranks to perform this move.
    2. The captured pawn must have moved two squares in one move, landing right next to the capturing pawn.
    3. The en passant capture must be performed on the turn immediately after the pawn being captured moves.
       If the player does not capture en passant on that turn, they no longer can do it later.

       The checking of 2. and 3. goes hand in hand, hence the joint check method.
    */

    // en passant is critically dependent on the last made move
    if (head == NULL || head->mx == NULL)
        return false;

    if (checkEnPassantStep1(move, board) &&
        checkEnPassantStep2And3(move, board, head))
        return true;

    return false;
}

static bool checkEnPassantStep1(const move *const move, char *const board[8][8])
{
    // The capturing pawn must have advanced exactly tree ranks to perform this move.

    if (*(move->movingPiece) == 'w' && move->fromPoint->row == 4)
        return true;
    if (*(move->movingPiece) == 'b' && move->fromPoint->row == 3)
        return true;

    return false;
}

static bool checkEnPassantStep2And3(const move *const m, char *const board[8][8], const history *const head)
{
    // The captured pawn must have moved two squares in one move, landing right next to the capturing pawn.
    // The en passant capture must be performed on the turn immediately after the pawn being captured moves.
    //      If the player does not capture en passant on that turn they no longer can do it later.

    /*
    1. check the last made move
    2. check that an enemy pawn moved 2 squares in that move
    3. check that the enemy pawn is directly adjacent to the capturing pawn
    */

    // 1.
    const move *const last = head->mx;

    // 2.
    if (abs(last->fromPoint->row - last->toPoint->row) != 2)
        return false;

    switch (*(m->movingPiece))
    {
    case 'w':
        if (strncmp(last->movingPiece, "bp", 2) != 0)
            return false;
        break;
    case 'b':
        if (strncmp(last->movingPiece, "wp", 2) != 0)
            return false;
        break;
    }

    // 3.
    if (last->toPoint->row != m->fromPoint->row || abs(last->toPoint->col - m->fromPoint->col) != 1)
        return false;

    return true;
}

static Color getColor(const char *const piece)
{
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
