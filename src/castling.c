#include <stdio.h>
#include <stdbool.h>
#include <makeMove.h>
#include <king.h>
#include <rook.h>
#include <string.h>

void castle(char *board[size][size], enum player turn, char *move) 
{
    // check if castling is legal
    if (strcmp(move, "O-O\n") == 0 || strcmp(move, "O-O-O\n") == 0) 
    {
        int row = (turn == BLANCO) ? 7 : 0;
        int king_col = 4;
        int rook_col, new_king_col, new_rook_col;
        if (strcmp(move, "O-O\n") == 0) 
        { // kingside castling
            rook_col = 7;
            new_king_col = 6;
            new_rook_col = 5;
        } else 
        { // queenside castling
            rook_col = 0;
            new_king_col = 2;
            new_rook_col = 3;
        }

        // check if the pieces are in the right position for castling
        if (strcmp(board[row][king_col], turn == BLANCO ? "K" : "k") != 0 ||
            strcmp(board[row][rook_col], turn == BLANCO ? "R" : "r") != 0 ||
            strcmp(board[row][new_king_col], " ") != 0 ||
            strcmp(board[row][new_rook_col], " ") != 0) 
        {
            puts("---> Castling is not legal");
            return;
        }
        
        // check if the squares between the king and rook are not under attack
        //int col_step = (new_king_col > king_col) ? 1 : -1;
        //for (int col = king_col + col_step; col != rook_col; col += col_step) 
        //{
        //    if (isAttacked(board, row, col, turn)) 
        //    {
        //        puts("---> Castling is not legal");
        //       return;
        //    }
        //}
        

        // execute the castling move
        board[row][new_king_col] = turn == BLANCO ? "K" : "k";
        board[row][new_rook_col] = turn == BLANCO ? "R" : "r";
        board[row][king_col] = " ";
        board[row][rook_col] = " ";
       // update the move string based on which type of castling was performed
        if (strcmp(move, "O-O\n") == 0) 
        { // kingside castling
            strcpy(move, "O-O");
        } else 
        { // queenside castling
            strcpy(move, "O-O-O");
        }
        
        printf("---> Castling move: %s\n", move);
        return;
    }
}
