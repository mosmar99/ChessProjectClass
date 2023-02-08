#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "rook.h"


bool checkPieceColor(const move *const move, char *const board[8][8])
{
    //get the color of the moving piece
    char movingPieceColor = move->movingPiece[0];
    //get the color of the captured piece
    char capturedPieceColor = board[move->toPoint->row][move->toPoint->col][0];
    // check if the moving piece and captured piece are different color
    if(movingPieceColor != capturedPieceColor && capturedPieceColor != '\0')
    {
        return true;
    }
    else
     return false;
}

bool checkRookMove(const move *const move, char *const board[8][8])
{  
  // Check if the moving piece is a rook
    if (*(move->movingPiece) != 'R') 
    {
        return false;
    }
    // check is to see if the move is either horizontal or vertical.
    // It checks if the starting and ending positions have the same row or column value respectively.
    if (move->fromPoint->col == move->toPoint->col || move->fromPoint->row == move->toPoint->row)
    {
        //vertical move
        if (move->fromPoint->col == move->toPoint->col) 
        {
            //rowdiff calculates the difference in row values between the starting and ending positions of the move. 
            //This value will be positive if the move is going down and negative if the move is going up.
            int rowDiff = move->toPoint->row - move->fromPoint->row;
            int rowDirection = rowDiff / abs(rowDiff);
            for (int i = move->fromPoint->row + rowDirection; i != move->toPoint->row; i += rowDirection) 
            {
                if (board[i][move->fromPoint->col] != NULL) 
                {
                    checkPieceColor(move,board);
                }
                return true;
            }
        } else 
        {
            int colDiff = move->toPoint->col - move->fromPoint->col;
            int colDirection = colDiff / abs(colDiff);
            for (int i = move->fromPoint->col + colDirection; i != move->toPoint->col; i += colDirection)
            {
                if (board[move->fromPoint->row][i] != NULL) 
                {
                     checkPieceColor(move,board);
                }
                return true;
            }
        }
        return true;
    }
    return false;
}