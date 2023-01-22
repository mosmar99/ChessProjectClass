#include "queen.h"
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

static PointArray * getCoordinates(char *input);
static Point * translateCoordiantes (char *coordinate);
static bool checkInput(char *input, char *board[8][8]);
static char * getDirection(Point *from, Point *to);
static bool * exploreDirection (char *dir, Point *from, Point *to, char *board[8][8]);

bool * checkQueenMove(char *input, char *board[8][8]){
    if(!checkInput){
        return NULL;
    }
    Point *from, *to;
    PointArray *pA;
    pA = getCoordinates(input);
    from = pA[1].p;
    to = pA[0].p;
    char *dir = getDirection(from, to);
    if(dir == NULL){
        return false;
    }
    //explore direction
    bool * validDir = exploreDirection(dir, from, to, board);
    free(from);
    free(to);
    return validDir;

}

bool checkInput(char *input, char *board[8][8]){
    if(input == NULL || board == NULL || strlen(input) != 7){
        return false;
    }
    for(int i = 0; i < 2; i++){
        if(!isalpha(input[i]) && !isalpha(input[i+1]) && !isdigit(input[i+2])){
            return false;
        }
    }
    return true;
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
    free(cordsToSplit);
    return pA;
}

Point * translateCoordiantes (char *coordinate){
    Point *p = malloc(sizeof(Point));
    p->x = coordinate[2] - '0' - 1;
    p->y = coordinate[1] - 'A';
    p->y = 8 - p->y - 1;
    return p;
}

char * getDirection(Point *from, Point *to){
    char *direction;
    int deltaX = abs(from->x - to->x);
    int deltaY = abs(from->y - to->y);
    //diagonal move
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
    //move was not diagonal
    //may or may not still be valid since queen has the combined moveset of the bishop and rook.
    //either delta y or delta x must equal 0
    if(deltaY == 0){
        if(from->x > to->x){
            return direction = "n";
        }
        else{
            return direction = "s";
        }
    }
    if(deltaX == 0){
        if(from->y > to->y){
            return direction = "w";
        }
        else{
            return direction = "e";
        }
    }
    return direction = NULL;
}

bool * exploreDirection (char *dir, Point *from, Point *to, char *board[8][8]){
    bool * invalidMove = false;
    //explore nw
    if(strcmp(dir, "nw") == 0){
        int i = from->x - 1 , j = from->y + 1;
        while(i > to->x && j < to->y){
            if(strcmp(board[i][j], "--") != 0){
                return invalidMove;
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
                return invalidMove;
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
                return invalidMove;
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
                return invalidMove;
            }
            i--;
            j--;
        }
    }
    //explore n
    if(strcmp(dir, "n") == 0){
        int i = from->x - 1 , j = from->y;
        while(i > to->x){
            if(strcmp(board[i][j], "--") != 0){
                return invalidMove;
            }
            i--;
        }
    }
    //explore e
    if(strcmp(dir, "e") == 0){
        int i = from->x, j = from->y + 1;
        while(j < to->y){
            if(strcmp(board[i][j], "--") != 0){
                return invalidMove;
            }
            j++;
        }
    }
    //explore s
    if(strcmp(dir, "s") == 0){
        int i = from->x + 1 , j = from->y;
        while(i > to->x){
            if(strcmp(board[i][j], "--") != 0){
                return invalidMove;
            }
            i++;
        }
    }
    //explore w
    if(strcmp(dir, "w") == 0){
        int i = from->x, j = from->y - 1;
        while(j > to->y){
            if(strcmp(board[i][j], "--") != 0){
                return invalidMove;
            }
            j--;
        }
    }
    //direction was valid now check landing square
    char * toSquare = board[to->x][to->y];
    char * fromSquare = board[from->x][from->y];
    if(fromSquare[0] == toSquare[0]){
        return invalidMove;
    }
    //all test passed it is a valid move.
    return (bool *)true;
}