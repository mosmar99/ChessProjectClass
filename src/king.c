#include "king.h"
#include <stdio.h>
#include "queen.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <makeMove.h>

static bool checkMovingDistance(const move * const move);
static bool checkLandingSquare(const move * const move);
static char getColor(const move * const move);
static bool check(const move * const move, char * const board[8][8]);
static bool checkDiagonals(const move * const move, char * const board[8][8], char oppositeColor);
static bool checkStraights(const move * const move, char * const board[8][8], char pieceColor);
static bool isOnBoard(int row, int col);
static bool exploreDiagonal(int rowOffset, int colOffset, char pieceColor, char * const board[8][8], const move * const move);
static bool exploreStraight(int rowOffset, int colOffset, char pieceColor, char * const board[8][8], const move * const move);
static bool checkKnight(char * const board[8][8], const move * const move, char pieceColor);

bool checkKingMove(const move * const move, char * const board[8][8]){

    if(!checkMovingDistance(move) || !checkLandingSquare(move)){
        return false;
    }
    //if check returns true, the king will put itself in check, function will therefore return false.

    bool checked = check(move, board);
    // free(temp);
    return checked == true ? false : true;

    // return check(temp, board) == true ? false : true;
}

static bool checkMovingDistance(const move * const m){
    int deltaRow = abs(m->fromPoint->row - m->toPoint->row);
    int deltaCol = abs(m->fromPoint->col - m->toPoint->col);
    if(deltaRow >= 2 || deltaCol >= 2){
        return false;
    }
    return true;
}

static bool checkLandingSquare(const move * const m){
    if(strrchr(m->movingPiece, 'w') && strrchr(m->capturedPiece, 'w')){
        return false;
    }
    if(strrchr(m->movingPiece, 'b') && strrchr(m->capturedPiece, 'b')){
        return false;
    }
    return true;
}

static char getColor(const move * const m){
    if(strrchr(m->movingPiece, 'w')){
        return 'w';
    }
    return 'b';
}

static bool check(const move * const m, char * const board[8][8]){

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

    bool onBoard = true;
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
        king = (strrchr(board[i][j],'K') && (deltaRow < 2 && deltaCol < 2));
        friendlyPiece = (strrchr(board[i][j], pieceColor));
    
        lineBlocked =   (friendlyPiece || rook || knight || (strrchr(board[i][j], 'p') && !pawn) || 
                         (strrchr(board[i][j], 'K') && !king));

        if((queen || bishop || pawn || king) && !lineBlocked){
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

    bool onBoard = true;
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
        king = (strrchr(board[i][j],'K') && (deltaRow <= 2 || deltaCol <= 2));
        friendlyPiece = (strrchr(board[i][j], pieceColor));

        //FIX THIS 
        lineBlocked = (friendlyPiece || knight || bishop  || pawn);

        if((queen || rook || king) && !lineBlocked){
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