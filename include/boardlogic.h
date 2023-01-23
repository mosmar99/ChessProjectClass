#ifndef BOARDLOGIC_H
#define BOARDLOGIC_H
#include <stdbool.h>

#define BOARDRC 8
#define COLOFFSET 97 //int 97 unicode = 'a'
#define ROWOFFSET 49 //int 49 unicode = '0'
#define LOWERCASEOFFSET 32


//indecies for allowed characters
#define PINDEX 0
#define COLINDEX 5
#define ROWINDEX 13
#define NUMALLOWEDCHARS 21

typedef struct point{
    unsigned int col;
    unsigned int row;
}point;

typedef struct move{
    char *movingPiece;
    point *fromPoint;

    char *capturedPiece;
    point *toPoint;
}move;

move *parseMove(char *board[8][8], char *string);
void printMove(move *m);

#endif