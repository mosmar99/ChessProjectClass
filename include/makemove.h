#ifndef MAKEMOVE_H
#define MAKEMOVE_H

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

#endif