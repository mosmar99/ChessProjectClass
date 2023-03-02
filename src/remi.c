#include <stdio.h>
#include <stdbool.h>
#include <makeMove.h>
#include <remi.h>

//pieces used for validity of moves check.
#include <king.h>
#include <queen.h>
#include <rook.h>
#include <bishop.h>
#include <knight.h>
#include <pawn.h>

bool checkMaterial(char * const board[8][8], char **flag);
bool checkMoves(history *const hs, char **flag);
bool checkRepetition(history *const hs, char **flag);
bool compareMoves(move *m1, move *m2);
bool checkValidMoves(char * const board[8][8], history * const hs, char **flag);

static bool isOnBoard(int row, int col);

bool remi (char * const board[8][8], history *const hs, char **flag){
    bool sufficientMaterial;
    bool manyMovesNoCaptures = false;
    bool repetition = false;
    bool ValidMoves = true;

    sufficientMaterial = checkMaterial(board, flag); //returns true if material is sufficient
    if(hs != NULL){
        ValidMoves = checkValidMoves(board, hs, flag); //returns true if valid moves exist.
        manyMovesNoCaptures = checkMoves(hs, flag); //returns true if we have many moves (50) with no captures
        repetition = checkRepetition(hs, flag); //returns true if we have repetition
    }
    if(!sufficientMaterial || manyMovesNoCaptures || repetition || !ValidMoves){ 
        return true; //we have draw
    }
    return false; //not draw

    //((win by time but no material))
}

bool checkMaterial(char * const board[8][8], char **flag){
    //king v king
    //king v king + bishop / horse

    //can win with two bishops and no enemy material
    //cannot win with two horses if enemy has no material.

    int whiteHorses = 0;
    int whiteBishops = 0;
    int otherWhitePieces = -1;
    

    int blackHorses = 0;
    int blackBishops = 0;
    int otherBlackPieces = -1;

    bool emptySquare;
    bool white;
    bool horse;
    bool bishop;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            emptySquare = strrchr(board[i][j], '-');
            if(!emptySquare){
                white = strrchr(board[i][j], 'w');
                bishop = strrchr(board[i][j], 'B');
                horse = strrchr(board[i][j], 'N');
                if(white){
                    if(horse){
                        whiteHorses++;
                    }
                    else if(bishop){
                        whiteBishops++;
                    }
                    else{   
                        otherWhitePieces++;
                    }
                }
                else{
                    if(horse){
                        blackHorses++;
                    }
                    else if(bishop){
                        blackBishops++;
                    }
                    else{
                        otherBlackPieces++;
                    }
                }
            }
        }
    }

    //check if other pieces > 0;
    //check that atleast one player has sufficient material

    if(otherBlackPieces > 0 || otherWhitePieces > 0){
        return true;
    }
    //white has more than one horse and black has another pieces besides the king.
    otherWhitePieces = otherWhitePieces + whiteHorses + whiteBishops;
    otherBlackPieces = otherBlackPieces + blackHorses + blackBishops;
    if(whiteHorses > 1 && otherBlackPieces > 0){
        return true;
    }
    if(whiteBishops > 1){
        return true;
    }
    //same as above but reverse.
    if(blackHorses > 1 && otherWhitePieces > 0){
        return true;
    }
    if(blackBishops > 1){
        return true;
    }

    if(((whiteHorses-1 + whiteBishops) > 1) || ((blackHorses-1 + blackBishops) > 1)){
        return true;
    }

    //now neither player has sufficient material & special cases dont match.
    *(flag) = "Insufficient Material";
    return false;
}

bool checkMoves(history *const hs, char **flag){
    history *temp = hs;
    int moveCount = 0;
    while(temp != NULL){
        //if blank move increase moveCount
        if(strcmp(temp->mx->capturedPiece, "--") == 0){
            moveCount++;
        }
        else{
            moveCount = 0;
        }
        temp = temp->next;
    }
    if(moveCount >= 50){
        *(flag) = "50 Moves Without Any Captures";
        return true;
    }
    return false;
}

bool checkRepetition(history *const hs, char **flag){
    //check last 6 moves (3 white) (3 black) if we have the same positions.

    //count # of moves
    int noMoves = 0;
    history *temp = hs;
    while(temp != NULL){
        temp = temp->next;
        noMoves++;
    }
    
    if(noMoves < 6){ //not enought moves.
        return false;
    }



    temp = hs;
    move *whiteMove = NULL;
    move *blackMove = NULL;

    int repetitions = 0;
    int index = 0;
    while(index < 6){
        if(whiteMove == NULL || blackMove == NULL){
            if(strrchr(temp->mx->movingPiece, 'w')){
                whiteMove = temp->mx;
            }
            else{
                blackMove = temp->mx;
            }
        }
        else{
            if(strrchr(temp->mx->movingPiece, 'w')){
                if(compareMoves(whiteMove, temp->mx)){
                    repetitions++;
                    whiteMove = temp->mx;
                }
            }
            else{
                if(compareMoves(blackMove, temp->mx)){
                    repetitions++;
                    blackMove = temp->mx;
                }
            }
        }
        temp = temp->next;
        index++;
    }

    if(repetitions > 3){
        *(flag) = "3 Fold Repetition";
        return true;
    }
    return false;
}

bool compareMoves(move *m1, move *m2){
    bool t1 = strcmp(m1->movingPiece, m2->movingPiece) == 0;
    bool t2 = strcmp(m1->capturedPiece, m2->capturedPiece) == 0;
    bool t3 = m1->fromPoint->row == m2->toPoint->row;
    bool t4 = m1->fromPoint->col == m2->toPoint->col;
    bool t5 = m1->toPoint->row == m2->fromPoint->row;
    bool t6 = m1->toPoint->col == m2->fromPoint->col;

    if(t1 && t2 && t3 && t4 && t5 && t6){
            return true;
        }
    return false;
}

bool checkValidMoves(char * const board[8][8], history * const hs, char **flag){
    //FIND ALL PIECES AND CHECK IF THEM MOVING ATLEST ONE SQUARE IS VALID.
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

    int knightOffset[8][2] = {
        {2,-1},
        {2,1},
        {1,2},
        {-1,2},
        {-2,1},
        {-2,-1},
        {-1,-2},
        {1,-2},

    };

    
    bool whiteMove = false;
    bool blackMove = false;

    bool passant = false;

    int validMove = 0;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(!strrchr(board[i][j], '-')){
                if(strrchr(board[i][j], 'p')){
                    for(int k = 0; k < 8; k++){

                        int rowOffset = i + offset[k][0];
                        int colOffset = j + offset[k][1];

                        if(isOnBoard(rowOffset, colOffset)){
                            point *from = createPoint(j,i);
                            point *to = createPoint(colOffset, rowOffset);

                            move *m = createMove(from, to, board[i][j], board[rowOffset][colOffset]);

                            if(checkPawnMove(m, board, hs, &passant)){
                                validMove++;
                            }
                        }

                    }
                }

                if(strrchr(board[i][j], 'R')){
                    for(int k = 0; k < 8; k++){

                        int rowOffset = i + offset[k][0];
                        int colOffset = j + offset[k][1];

                        if(isOnBoard(rowOffset, colOffset)){
                            point *from = createPoint(j,i);
                            point *to = createPoint(colOffset, rowOffset);

                            move *m = createMove(from, to, board[i][j], board[rowOffset][colOffset]);

                            if(checkRookMove(m, board)){
                                validMove++;
                            }
                        }

                    }
                }

                if(strrchr(board[i][j], 'N')){
                    for(int k = 0; k < 8; k++){

                        int rowOffset = i + knightOffset[k][0];
                        int colOffset = j + knightOffset[k][1];

                        if(isOnBoard(rowOffset, colOffset)){
                            point *from = createPoint(j,i);
                            point *to = createPoint(colOffset, rowOffset);

                            move *m = createMove(from, to, board[i][j], board[rowOffset][colOffset]);

                            if(checkKnightMove(m, board)){
                                validMove++;
                            }
                        }

                    }
                }

                if(strrchr(board[i][j], 'B')){
                    for(int k = 0; k < 8; k++){

                        int rowOffset = i + offset[k][0];
                        int colOffset = j + offset[k][1];


                        if(isOnBoard(rowOffset, colOffset)){
                            point *from = createPoint(j,i);
                            point *to = createPoint(colOffset, rowOffset);

                            move *m = createMove(from, to, board[i][j], board[rowOffset][colOffset]);

                            if(checkBishopMove(m, board)){
                                validMove++;
                            }
                        }

                    }
                }

                if(strrchr(board[i][j], 'Q')){
                    for(int k = 0; k < 8; k++){

                        int rowOffset = i + offset[k][0];
                        int colOffset = j + offset[k][1];
                        
                        if(isOnBoard(rowOffset, colOffset)){
                            point *from = createPoint(j,i);
                            point *to = createPoint(colOffset, rowOffset);

                            move *m = createMove(from, to, board[i][j], board[rowOffset][colOffset]);

                            if(checkQueenMove(m, board)){
                                validMove++;
                            }
                        }

                    }
                }

                if(strrchr(board[i][j], 'K')){
                    for(int k = 0; k < 8; k++){

                        int rowOffset = i + offset[k][0];
                        int colOffset = j + offset[k][1];
                        
                        if(isOnBoard(rowOffset, colOffset)){
                            point *from = createPoint(j,i);
                            point *to = createPoint(colOffset, rowOffset);

                            move *m = createMove(from, to, board[i][j], board[rowOffset][colOffset]);

                            if(checkKingMove(m, board)){
                                validMove++;
                            }
                        }

                    }
                }
            }
                if(validMove > 0){
                    if(strrchr(board[i][j], 'w')){
                        whiteMove = true;
                    }
                    if(strrchr(board[i][j], 'b')){
                        blackMove = true;
                    }
                }
                validMove = 0;
            }
    }

    if(whiteMove && blackMove){
        return true;
    }
    *(flag) = "No Valid Moves Left";
    return false;
}

static bool isOnBoard(int row, int col){
    int check1 = (row - 0)*(row - 7);
    int check2 = (col - 0)*(col - 7);
    if((check1 <= 0) && (check2 <= 0)){
        return true;
    }
    return false;
}