#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <boardlogic.h>

const char ALLOWEDCHARS[NUMALLOWEDCHARS] = {'K','Q','R','B','N','a','b','c','d','e','f','g','h','1','2','3','4','5','6','7','8'};

static bool parseToken(char *board[8][8], char *token, bool first, struct point **p, char *piece);
static bool charIsValid(char c, int indexStart, int indexStop);
static point *createPoint(unsigned int x, unsigned int y);
static void destroyPoint(point *p);
static move *createMove(point *fromPoint, point *toPoint, char *movingPiece, char *CapturedPiece);
static void destroyMove(move *move);

// parse move input string ex "Nf3 Nc6", "Nf3 c6", "f3 c6"
// output pointer to move struct if successful
// NULL if fail
move *parseMove(char *board[8][8], char *string){

    char *token = strtok(string, " ");

    char movingPiece[3];
    point *fromPoint = NULL;
    char capturedPiece[3];
    point *toPoint = NULL;

    if (!parseToken(board, token, true, &fromPoint, movingPiece)){
        destroyPoint(fromPoint);
        destroyPoint(fromPoint);
        return NULL;
    }

    token = strtok(NULL, " ");

    if (!parseToken(board, token, false, &toPoint, capturedPiece)){
        return NULL;
    }

    return createMove(fromPoint, toPoint, movingPiece, capturedPiece);
}

void printMove(move *m){
    printf("Parsed move\n");
    printf(" \"%s\" is the moving piece\n", m->movingPiece);
    printf("the piece is moving from (%d,%d)\n", m->fromPoint->col, m->fromPoint->row);
    printf(" \"%s\" is the captured piece\n", m->capturedPiece);
    printf("the piece is captured at (%d,%d)\n", m->toPoint->col, m->toPoint->row);
}

static bool parseToken(char *board[8][8], char *token, bool first, struct point **p, char *piece){

    if(!token || strlen(token) < 2 || strlen(token) > 3){ 
        return false;
    }

    int tokenLength = strlen(token);

    // Check and assign rank and file (COL and ROW)
    if (charIsValid(token[tokenLength - 2], COLINDEX, ROWINDEX) && charIsValid(token[tokenLength - 1], ROWINDEX, NUMALLOWEDCHARS)){
        unsigned int col = token[tokenLength - 2] - COLOFFSET;
        unsigned int row = token[tokenLength - 1] - ROWOFFSET;
        *p = createPoint(col,row);
    } else {
        return false;
    }

    char pieceOnBoard[3];

    strcpy(pieceOnBoard, board[(*p)->row][(*p)->col]);

    // Check that the specified Piece is on the board location
    if(tokenLength == 2 && first && pieceOnBoard[1] == 'p'){
        strcpy(piece, pieceOnBoard);
        return true;

    } else if (tokenLength == 2 && !first && (pieceOnBoard[1] == 'p' || pieceOnBoard[0] == '-')){
        strcpy(piece, pieceOnBoard);
        return true;

    } else if (tokenLength == 3 && pieceOnBoard[1] == token[0]){
        strcpy(piece, pieceOnBoard);
        return true;

    } else {
        return false;
    }  
}

static bool charIsValid(char c, int indexStart, int indexStop){
    for (size_t i = indexStart; i < indexStop; i++)
    {
        if (c == ALLOWEDCHARS[i]){
            return true;
        }           
    }

    return false;  
}

static point *createPoint(unsigned int col, unsigned int row){

    point *p = malloc(sizeof(point));

    if (p){
        p->col = col;
        p->row = row;
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

static move *createMove(point *fromPoint, point *toPoint, char *movingPiece, char *CapturedPiece){
    move *newMove = malloc(sizeof(move));

    if (newMove){
        newMove->movingPiece = malloc(sizeof(char[3]));
        newMove->capturedPiece = malloc(sizeof(char[3]));
        strcpy(newMove->movingPiece, movingPiece);
        strcpy(newMove->capturedPiece, CapturedPiece);

        newMove->fromPoint = fromPoint;
        newMove->toPoint = toPoint;
    }
    return newMove;
}

static void destroyMove(move *move){

    if(move){
        destroyPoint(move->fromPoint);
        destroyPoint(move->toPoint);

        free(move->movingPiece);
        free(move->capturedPiece);

        free(move);
    }
}