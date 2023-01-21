#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define size (7+1)

void requestMove(char *move);
void applyMove(char *move, char *board[8][8]);

// bool *checkRockMove(const char *const input, char *board[8][8];
// bool *checkKnightMove(const char *const input, char *board[8][8]);
// bool *checkBishopMove(const char *const input, char *board[8][8]);
// bool *checkQueenMove(const char *const input, char *board[8][8]);
// bool *checkKingMove(const char *const input, char *board[8][8]);
bool *checkPawnMove(const char *const input, char *board[8][8]);

void play(char *board[8][8]) {
    bool play = true;
    while (play)
    {
        //get next move
        char *move = malloc( sizeof(char) * size );
        requestMove(move);
        // applyMove(move, board);
        action(move, board);
    }

}

void readInput(char *move) {
    char c;
    for (size_t i = 0; i < size; i++)
    {
        c = getchar();
        if (c == '\n'||c == '\0') 
        {
            *(move+i) = c;
            return;
        } 
        else 
        {
            *(move+i) = c;
        }
    }
}

void requestMove(char *move) {
    // prompt user for move
    printf("Enter white's move [Piece][Square]-->[Piece][Square]: ");
    fflush(stdout);

    // collect all input until eol
    readInput(move);
}

void actionPawn(char *move, char *board[8][8]) {
    // todo manipulate board according to move
    // put -- in old position
    // put correctly coloured pawn in to-move-to-tile
}

void applyMove(char *move, char *board[8][8]) {
    bool *validMove;
    switch (*(move))
    {
    case 'R':
        // validMove = checkRockMove(move, board);
        break;
    case 'N':
        // validMove = checkKnightMove(move, board);
        break;
    case 'B':
        // validMove = checkBishopkMove(move, board);
        break;
    case 'Q':
        // validMove = checkQueenMove(move, board);
        break;
    case 'K':
        // validMove = checkKingMove(move, board);
        break;
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
        validMove = checkPawnMove(move, board);
        if (*validMove)
            actionPawn(move, board);        
        break;    
    
    default:
        puts("Not a valid move");
        return;
    }


    
}