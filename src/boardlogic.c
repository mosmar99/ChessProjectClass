#include <stdbool.h>
#include <string.h>
#include "boardlogic.h"
#include "board.h"



bool makeMove(/*pointer to board + move*/ ){

}

// move input string ex "Nf3 Nc6", "Nf3 c6"
bool parseMove(/*Board array ** to pass along to _CanMove() */char *string){

    int move[6]; //{moving piece, from row, from col, captured piece(0 for blank), to row, to col }?
    int i = 0;
    char *token = strtok(string, ' ');

    while(i < 6){

        if(strlen(token) == 2){
            move[i + 1] = token[0] - COLOFFSET;
            move[i + 2] = token[1] - ROWOFFSET;
        
            char boardPiece = getPiece(move[i + 1], move[i + 2]);

            if (getPiece(boardPiece == p || boardPiece == P)){
                move[i] = getPiece(move[i + 1], move[i + 2]);
                i = i + 3;
            } else {
                return false;
            }
        
        } else if(strlen(token) == 3) {
            move[i + 1] = token[1] - COLOFFSET;
            move[i + 2] = token[2] - ROWOFFSET;

            char boardPiece = getPiece(move[i + 1], move[i + 2]);

            if(boardPiece == token[0] || boardPiece - 32 == token[0]){
                move[i] = boardPiece;

                i = i + 3;
            } else {
                return false;
            }

        } else {
            return false;
        }

        strtok(NULL,' ');
    }
    

    // parse move

    //send to correct library/function

    //return if valid move
    return true;
}


// can move _CanMove() to separate libraries and include

// bool kingCanMove(/*pointer to board + move from parse*/){

//     return false;
// }

// bool queenCanMove(/*pointer to board + move from parse*/){
    
//     return false;
// }

bool rookCanMove(/*pointer to board + move from parse*/){
    return false;
}

bool knightCanMove(/*pointer to board + move from parse*/){
    return false;
}

bool bishopCanMove(/*pointer to board + move from parse*/){
    return false;
}

bool pawnCanMove(/*pointer to board + move from parse*/){
    return false;
}