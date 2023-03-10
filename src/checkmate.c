#include <stdio.h>
#include <stdbool.h>
#include <checkmate.h>

//pieces used for validity of moves check.
#include <king.h>
#include <queen.h>
#include <rook.h>
#include <bishop.h>
#include <knight.h>
#include <pawn.h>

typedef struct POI{
    point **line;
    unsigned int dangerousLines;
    unsigned int noPoints;
}POI;

//EXPORTED FUNCTIONS
bool check(const move * const move, char * const board[8][8]);
bool checkmate(char * const board[8][8], history * const hs, char **flag);

// static char getColor(const move * const move);
static bool checkDiagonals(const move * const move, char * const board[8][8], char oppositeColor);
static bool checkStraights(const move * const move, char * const board[8][8], char pieceColor);
static bool isOnBoard(int row, int col);
static bool exploreDiagonal(int rowOffset, int colOffset, char pieceColor, char * const board[8][8], const move * const move);
static bool exploreStraight(int rowOffset, int colOffset, char pieceColor, char * const board[8][8], const move * const move);
static bool checkKnight(char * const board[8][8], const move * const move, char pieceColor);
static POI * createStruct();
static point * getPosition(char * const board[8][8], char piece[2], int index);
static bool valid(char * const board[8][8], history * const hs, char piece[2], point *p);
static move * generateMoves(point *p, char * const board[8][8]);
static bool attemptMove(char * const board[8][8], const history * const hs, const move * const m, char *piece);
static void populateArray(int rowOffset, int colOffset, const move *const m, char * const board[8][8]);
static char getColor(const move * const m);
static bool moveKing(char * const board[8][8], point * p);
static bool loopPieces(char * const board[8][8], history * const hs, char piece[2]);


POI *poi = NULL;

bool checkmate(char * const board[8][8], history * const hs, char **flag){
    if(hs != NULL){
        poi = createStruct(); //mem for struct
        if(poi != NULL && hs->next != NULL){
            char color = getColor(hs->next->mx);
            char piece[2];
            piece[0] = color;
            piece[1] = 'K';
            point * p = getPosition(board, piece, 0);
            move * m = createMove(p, p, board[p->row][p->col], board[p->row][p->col]);
            if(check(m, board)){ //check if king moving from the square it is standing on to the square it is standing on, will result in a check.
                if(!valid(board, hs, piece, p)){
                    *(flag) = "CHECKMATE";
                    free(poi);
                    return true;
                }
                *(flag) = "CHECK";
                free(poi);
                return true;
            }
        }
    }
    free(poi);
    *(flag) = "IDLE";
    return false;
}

static POI * createStruct(){
    poi = malloc(sizeof(POI));
    if(poi != NULL){
        poi->line = (point **)malloc(sizeof(point *) * 8);
        poi->dangerousLines = 0;
        poi->noPoints = 0;
        return poi;
    }
    return NULL;
}

static void populateArray(int rowOffset, int colOffset, const move *const m, char * const board[8][8]){
    if(poi->dangerousLines == 0){
        int i = m->toPoint->row + rowOffset , j = m->toPoint->col + colOffset;
        int index = 0;
        //check if it was a knight because populating the array of points will not be the same. since we will only be looking for a singular point
        if(abs(rowOffset) > 1 || abs(colOffset) > 1){
            poi->line[0] = createPoint(j,i);
        }
        else{
            while(isOnBoard(i,j)){
                poi->line[index] = createPoint(j,i);
                index++;
                i = i + rowOffset;
                j = j + colOffset;
            }
            //while loop ends when the dangerous piece is encountered, but capturing the piece may be possible therefore we add the point of the piece aswell.
            poi->line[index] = createPoint(j, i);
            poi->noPoints = index;
        }
        poi->dangerousLines++;
    }
    else{
        poi->dangerousLines++;
    }
}

static bool valid(char * const board[8][8], history * const hs, char piece[2], point *p){
    bool valid = false;
    if(poi->dangerousLines > 1){ //if two lines are considered dangerous the only valid move is for the king to move.
        valid = moveKing(board, p);
    }
    else{ //dangerous lines is less than two which means the attack can be blocked by a friendly piece or the attacker can be captured. king may also move.
        if(loopPieces(board, hs, piece) || moveKing(board, p)){
            valid = true;
        }
    }
    return valid;
}

static bool moveKing(char * const board[8][8], point * p){
    int offset[8][2] = {
        {1, -1},
        {1, 1},
        {-1, 1},
        {-1, -1},
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1}
    };
    int validMoves = 0;
    for(int k = 0; k < 8; k++){
        int col = p->col + offset[k][1];
        int row = p->row + offset[k][0];
        if(isOnBoard(row,col)){
            move * toCheck = createMove(p, createPoint(col,row), board[p->row][p->col], board[row][col]);
            if(checkKingMove(toCheck, board)){
                validMoves++;
            }
        }
    }
    return validMoves > 0;
}

static move * generateMoves(point *p, char * const board[8][8]){
    poi->noPoints--;
    int col = poi->line[poi->noPoints]->col;
    int row = poi->line[poi->noPoints]->row;
    point *newPoint = createPoint(col,row);
    move * new = createMove(p, newPoint, board[p->row][p->col], board[row][col]);
    return new;
}

static bool loopPieces(char * const board[8][8], history * const hs, char piece[2]){
    bool blocked = false;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(strrchr(board[i][j], piece[0]) && !strrchr(board[i][j], 'K')){
                point * p = createPoint(j,i);
                int temp = poi->noPoints;
                for(int k = 0; k <= temp; k++){
                    if(poi->noPoints > 0){
                        move * m = generateMoves(p, board);
                        if(attemptMove(board, hs, m, board[i][j])){
                            blocked = true;
                        }
                    }
                }
                poi->noPoints = temp;
            }
        }
    }
    return blocked;
}

static bool attemptMove(char * const board[8][8], const history * const hs, const move * const m, char *piece){
    bool passant = false;
    if(strrchr(piece, 'p')){
        return checkPawnMove(m, board, hs, &passant);
    }
    if(strrchr(piece, 'Q')){
        return checkQueenMove(m, board);
    }
    if(strrchr(piece, 'B')){
        return checkBishopMove(m, board);
    }
    if(strrchr(piece, 'N')){
        return checkKnightMove(m, board);
    }
    if(strrchr(piece, 'R')){
        return checkRookMove(m, board);
    }
    return false;
}


static point * getPosition(char * const board[8][8], char piece[2], int index){
    int counter = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(strrchr(board[i][j], piece[0]) && strrchr(board[i][j], piece[1])){
                if(counter == index){
                    point *new = createPoint(j,i);
                    return new;
                }
                else{
                    counter++;
                }
            }
        }
    }
    return NULL;
}

static char getColor(const move * const m){
    if(strrchr(m->movingPiece, 'w')){
        return 'w';
    }
    return 'b';
}

bool check(const move * const m, char * const board[8][8]){
    //If any of these return true the king is checked.
    bool diagonals = checkDiagonals(m, board, getColor(m));
    bool straights = checkStraights(m, board, getColor(m));
    bool knights = checkKnight(board, m, getColor(m));
    if(!diagonals || !straights || !knights){
        return true;
    }
    return false;
}

static bool checkDiagonals(const move * const m, char * const board[8][8], char pieceColor){

    bool nw = exploreDiagonal(1, -1, pieceColor, board, m);
    bool ne = exploreDiagonal(1, 1, pieceColor, board, m);
    bool se = exploreDiagonal(-1, 1, pieceColor, board, m);
    bool sw = exploreDiagonal(-1, -1, pieceColor, board, m);
    
    if(nw && ne && se && sw){
        return true;
    }
    return false;
}

static bool checkStraights(const move * const m, char * const board[8][8], char pieceColor){

    bool north = exploreStraight(1, 0, pieceColor, board, m);
    bool east = exploreStraight(0, 1, pieceColor, board, m);
    bool south = exploreStraight(-1, 0, pieceColor, board, m);
    bool west = exploreStraight(0, -1, pieceColor, board, m);

    if(north && east && south && west){
        return true;
    }
    return false;
}

static bool exploreDiagonal(int rowOffset, int colOffset, char pieceColor, char * const board[8][8], const move * const m){

    int i = m->toPoint->row + rowOffset , j = m->toPoint->col + colOffset;

    int deltaRow, deltaCol;

    bool onBoard = isOnBoard(i,j);
    bool lineBlocked = false;

    bool friendlyPiece = false;
    bool king = false;
    bool queen = false;
    bool knight = false;
    bool bishop = false;
    bool rook = false;
    bool pawn = false;

    //while line isn't blocked and we are still on the board.
    while(!lineBlocked && onBoard){
        deltaRow = abs(i - m->fromPoint->row);
        deltaCol = abs(j - m->fromPoint->col);

        pawn = (strrchr(board[i][j],'p') && (deltaRow <= 2 && deltaCol <= 2));
        bishop = strrchr(board[i][j],'B');
        queen = strrchr(board[i][j],'Q');
        knight = strrchr(board[i][j], 'N');
        rook = strrchr(board[i][j], 'R');
        king = (strrchr(board[i][j],'K') && (deltaRow <= 2 && deltaCol <= 2));
        friendlyPiece = (strrchr(board[i][j], pieceColor));
    
        lineBlocked =   (friendlyPiece || rook || knight || (strrchr(board[i][j], 'p') && !pawn) || 
                         (strrchr(board[i][j], 'K') && !king));

        if((queen || bishop || pawn || king) && !lineBlocked){
            if(poi != NULL){
                populateArray(rowOffset, colOffset, m, board);
            }
            return false;
        }
        if(rowOffset > 0){
            i++;
        }
        else{
            i--;
        }
        if(colOffset > 0){
            j++;
        }
        else{
            j--;
        }
        onBoard = isOnBoard(i,j);
    }
    return true;
}

static bool exploreStraight(int rowOffset, int colOffset, char pieceColor, char * const board[8][8], const move * const m){
    
    int i = m->toPoint->row + rowOffset , j = m->toPoint->col + colOffset;

    int deltaRow, deltaCol;

    bool onBoard = isOnBoard(i,j);
    bool lineBlocked = false;

    bool friendlyPiece;
    bool king;
    bool queen;
    bool knight;
    bool bishop;
    bool rook;
    bool pawn;

    //while line isn't blocked and we are still on the board.
    while(!lineBlocked && onBoard){

        deltaRow = abs(i - m->fromPoint->row);
        deltaCol = abs(j - m->fromPoint->col);

        pawn = strrchr(board[i][j],'p');
        bishop = strrchr(board[i][j],'B');
        queen = strrchr(board[i][j],'Q');
        knight = strrchr(board[i][j], 'N');
        rook = strrchr(board[i][j], 'R');
        king = (strrchr(board[i][j],'K') && (deltaRow <= 2 && deltaCol <= 2));
        friendlyPiece = (strrchr(board[i][j], pieceColor));

        lineBlocked = (friendlyPiece || knight || bishop  || pawn);

        if((queen || rook || king) && !lineBlocked){
            if(poi != NULL){
                populateArray(rowOffset, colOffset, m, board);
            }
            return false;
        }
        if(rowOffset > 0){
            i++;
        }
        else if(rowOffset < 0){
            i--;
        }
        if(colOffset > 0){
            j++;
        }
        else if(colOffset < 0){
            j--;
        }
        onBoard = isOnBoard(i,j);
    }
    return true;
}

static bool checkKnight(char * const board[8][8], const move * const m, char pieceColor){

    int pattern[8][2] = {
        {2,-1},
        {2,1},
        {1,2},
        {-1,2},
        {-2,1},
        {-2,-1},
        {-1,-2},
        {1,-2},

    };

    bool danger = false;
    bool knight;
    bool onBoard;

    int n = 0;

    while(n < 8){
        int i = m->toPoint->row + pattern[n][0] , j = m->toPoint->col + pattern[n][1];
        onBoard = isOnBoard(i,j);
        if(onBoard){
            knight = (strrchr(board[i][j], 'N') && !strrchr(board[i][j], pieceColor));
            if(knight){
                if(poi != NULL){
                    populateArray(pattern[n][0], pattern[n][1], m, board);
                }
                danger = true;
            }
        }
        n++;
    }

    return !danger;
}

static bool isOnBoard(int row, int col){
    int check1 = (row - 0)*(row - 7);
    int check2 = (col - 0)*(col - 7);
    if((check1 <= 0) && (check2 <= 0)){
        return true;
    }
    return false;
}
