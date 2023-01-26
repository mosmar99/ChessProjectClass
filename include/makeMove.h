#ifndef MAKEMOVE_H
#define MAKEMOVE_H

#include <stdbool.h>

#define size (7+1)

typedef struct point{
    unsigned int col;
    unsigned int row;
} point;

typedef struct move{
    char *movingPiece;
    char *capturedPiece;

    point *fromPoint;
    point *toPoint;
} move;

void play(char *board[size][size]);
char *requestMove();
move *setupMoveData(char *input, char *board[size][size]);
void extractChessCoord(char *dest, char *src, int cpyFrom, int cpyTo);
void getTransform(int *dest, char *src); 
void applyMove(move *mx, char *board[size][size]);
void action(move *mx, char *board[size][size]);
void printBoard(char *board[size][size]);

#endif