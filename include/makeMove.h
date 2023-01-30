#ifndef MAKEMOVE_H
#define MAKEMOVE_H

#include <stdbool.h>

#define size (7+1)
#define NULL ((void *)0)

typedef struct point {
    unsigned int col;
    unsigned int row;
} point;

typedef struct move {
    char *movingPiece;
    char *capturedPiece;

    point *fromPoint;
    point *toPoint;
} move;

enum player {
    BLANCO, // white in spanish
    NEGRO   // black in spanish
};

typedef struct history {
    move *mx;
    struct history *next;
} history;

void play(char *board[size][size]);
char *requestMove(enum player turn);
move *constructMove(char *input, char *board[size][size]);
void extractChessCoord(char *dest, char *src, int cpyFrom, int cpyTo);
void getTransform(int *dest, char *src);
void moveHistory(move *mx);
bool catchSpecificErrors(move *mx, bool isValidMove); 
bool catchGeneralErrors(move *mx, enum player turn);
bool applyMove(move *mx, char *board[size][size]);
void action(move *mx, char *board[size][size]);
void printBoard(char *board[size][size]);

#endif