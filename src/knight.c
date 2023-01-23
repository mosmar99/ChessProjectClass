#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "knight.h"

typedef struct point{
    unsigned int x;
    unsigned int y;
}point;

static bool isSameColour(const char *piece1, const char *piece2);
static bool getCoords(char *input, point ** p1, point ** p2);
static bool parseToken(char *token, point **p);
static point *createPoint(unsigned int x, unsigned int y);
static void destroyPoint(point *p);

bool checkKnightMove(char *input, const char *board[8][8]){

    const int pattern[8] = {1,2,2,1,-1,-2,-2,-1};
    int i = 0;

    point *fromPoint = NULL;
    point *toPoint = NULL;

    if (!getCoords(input, &fromPoint, &toPoint)){
        destroyPoint(fromPoint);
        destroyPoint(toPoint);
        return false;
    }

    while (i < 8 && fromPoint && toPoint){
        if (!isSameColour(board[fromPoint->x][fromPoint->y], board[toPoint->x][toPoint->y])
            && toPoint->x - fromPoint->x == pattern[i % 8]
            && toPoint->y - fromPoint->y == pattern[(i+2) % 8]){
            return true;
        }
        i++;
    }

    return false; 
}

static bool isSameColour(const char *piece1, const char *piece2){

    if (piece1[0] != piece2[0]){
        return false;
    } else {
        return true;
    }

    return false;
}

static bool getCoords(char *input, point ** p1, point ** p2){

    if (!input || strlen(input) != 5){
        return false;
    }

    char *token = strtok(input," ");
    if (!parseToken(token, p1)){
        return false;
    }

    token = strtok(NULL," ");

    if (!parseToken(token, p2)){
        return false;
    }

    return true;
}

static bool parseToken(char *token, point ** p){

    if (!token || strlen(token) != 2)
    {
        return false;
    }

    int x = token[0] - 'a';
    int y = token[1] - '1';
    if (y < 8 && x < 8){
        *p = createPoint(x, y);
        return true;
    } else {
        return false;
    }
}

static point *createPoint(unsigned int x, unsigned int y){

    point *p = malloc(sizeof(point));

    if (p){
        p->x = x;
        p->y = y;
        return p;
    } else {
        return NULL;
    }
}

static void destroyPoint(point *p){
    if (p){
        free(p);
    } 
}