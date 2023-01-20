#include "bishop.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Point{
    unsigned int x, y;
}Point;

typedef struct PointArray{
    Point *p;
} PointArray;

PointArray * getCoordinates(char *input);
Point * translateCoordiantes (char *coordinate);
bool checkInput(char *input, char *board[8][8]);
char * getDirection(Point *from, Point *to);
bool exploreDirection (char *dir, Point *from, Point *to, char *board[8][8]);

bool checkBishopMove(char *input, char *board[8][8]){
    if(!checkInput){
        return NULL;
    }
    Point *from, *to;
    PointArray *pA;
    pA = getCoordinates(input);
    from = pA[1].p;
    to = pA[0].p;
    char *dir = getDirection(from, to);
    //direction was invalid I.e we did not perform a diagonal move.
    if(dir == NULL){
        return false;
    }
    //explore direction
    bool validDir = exploreDirection(dir, from, to, board);
    return validDir;
}

bool checkInput(char *input, char *board[8][8]){
    if(input == NULL || board == NULL || strlen(input) != 5){
        return false;
    }
    if(!isalpha(input[0]) || !isalpha(input[3]) || isdigit(input[1]) || isdigit(input[4])){
        return false;
    }
}

PointArray * getCoordinates(char *input){
    char *cordsToSplit, *fromCord, *toCord;
    Point *from, *to;

    cordsToSplit = calloc(strlen(input) + 1, sizeof(char));

    strncpy(cordsToSplit, input, strlen(input)+1);

    fromCord = strtok(cordsToSplit, " ");
    toCord = strtok(NULL, " ");

    //translate the coordinates from alphabetical to numerical
    from = translateCoordiantes(fromCord);
    to = translateCoordiantes(toCord);

    //a point array is used to return the two points.
    PointArray * pA = malloc(sizeof(PointArray));
    for(int i = 0; i < 2; i++){
        pA[i].p = (Point *)malloc(sizeof(Point));
    }
    pA[1].p = from;
    pA[0].p = to;
    return pA;
}

Point * translateCoordiantes (char *coordinate){
    toupper(coordinate[0]);
    Point *p = malloc(sizeof(Point));
    p->x = coordinate[1] - '0' - 1;
    p->y = coordinate[0] - 'A';
    p->y = 8 - p->y - 1;
    return p;
}

char * getDirection(Point *from, Point *to){
    char *direction;
    int deltaX = abs(from->x - to->x);
    int deltaY = abs(from->y - to->y);
    //Bishop moves on the diagonal
    //we need to check that the absolute values of delta x and delta y are equal otherwise and illegal move has been made
    if(deltaX == deltaY){
        if(from->x > to->x && from->y < to->y){
            return direction = "nw";
        }
        if(from->x < to->x && from->y < to->y){
            return direction = "ne";
        }
        if(from->x < to->x && from->y > to->y){
            return direction = "se";
        }
        if(from->x > to->x && from->y > to->y){
            return direction = "sw";
        }
    }
    return direction = NULL;
}

bool exploreDirection (char *dir, Point *from, Point *to, char *board[8][8]){
    //explore nw
    if(strcmp(dir, "nw") == 0){
        int i = from->x - 1 , j = from->y + 1;
        while(i > to->x && j < to->y){
            if(strcmp(board[i][j], "--") != 0){
                return false;
            }
            i--;
            j++;
        }
    }
    //explore ne
    if(strcmp(dir, "ne") == 0){
        int i = from->x + 1 , j = from->y + 1;
        while(i < to->x && j < to->y){
            if(strcmp(board[i][j], "--") != 0){
                return false;
            }
            i++;
            j++;
        }
    }
    //explore se
    if(strcmp(dir, "se") == 0){
        int i = from->x + 1 , j = from->y - 1;
        while(i < to->x && j > to->y){
            if(strcmp(board[i][j], "--") != 0){
                return false;
            }
            i++;
            j--;
        }
    }
    //explore sw
    if(strcmp(dir, "sw") == 0){
        int i = from->x - 1 , j = from->y - 1;
        while(i > to->x && j > to->y){
            if(strcmp(board[i][j], "--") != 0){
                return false;
            }
            i--;
            j--;
        }
    }
    //direction was valid now check landing square
    char * toSquare = board[to->x][to->y];
    char * fromSquare = board[from->x][from->y];
    if(fromSquare[0] == toSquare[0]){
        return false;
    }
    //all test passed it is a valid move.
    return true;
}