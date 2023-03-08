#ifndef MAKEMOVE_H
#define MAKEMOVE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include "makeBoard.h"

#define size (7+1)

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
bool noSpecificErrors(move *mx, bool isValidMove); 
enum player switchTurn(enum player turn);
bool noGeneralErrors(move *mx, enum player turn);
bool applyMove(move *mx, char *board[size][size]);
void action(move *mx, char *board[size][size], const bool *const wasEnPassant);
bool isWrongInput(char *input);

point *createPoint(unsigned int x, unsigned int y);
move *createMove(point *fromPoint, point *toPoint, char *movingPiece, char *CapturedPiece);
void destroyMove(move *move);

#endif