#include <stdio.h>
#include "checkmate.h"
#include <makeMove.h>
#include <assert.h>

static void baseBoard(char * board[8][8]);
static void baseHistory (int no);

history * hs = NULL;

void main (void){
    char * board[8][8];
    char * flag = malloc(sizeof(char[50]));

    #pragma region ***non-checkmates, but checks***
        baseHistory(3);
        baseBoard(board);
        flag = "reset";

        board[7][7] = "wK";
        board[0][7] = "bQ";
        checkmate(board, hs, &flag);
        assert(strcmp(flag, "CHECK") == 0);

        flag = "reset";
        baseHistory(2);
        baseBoard(board);

        board[7][7] = "wK";
        board[5][6] = "bN";
        checkmate(board, hs, &flag);
        assert(strcmp(flag, "CHECK") == 0);
    #pragma endregion

    #pragma region ***non-checkmates, but checks where the king is unable to move, but a friendly piece can save the king***
        baseHistory(2);
        baseBoard(board);
        flag = "reset";

        board[0][7] = "wK";
        board[1][7] = "wp";
        board[1][6] = "wp";
        board[7][7] = "wB"; //bishop can attack queen diagonally h8-a1
        board[0][0] = "bQ";
        checkmate(board, hs, &flag);
        assert(strcmp(flag, "CHECK") == 0);

        baseHistory(2);
        baseBoard(board);
        flag = "reset";

        board[7][7] = "wK";
        board[6][7] = "wp";
        board[6][6] = "wp"; //this pawn can move up one
        board[7][0] = "bQ";
        checkmate(board, hs, &flag);
        assert(strcmp(flag, "CHECK") == 0);
    #pragma endregion

    #pragma region ***checkmates***
        baseHistory(2);
        baseBoard(board);
        flag = "reset";

        board[0][7] = "wK"; //same position as the bishop one above but this time no bishop to save the king.
        board[1][7] = "wp";
        board[1][6] = "wp";
        board[0][0] = "bQ";
        checkmate(board, hs, &flag);
        assert(strcmp(flag, "CHECKMATE") == 0);

        baseHistory(2);
        baseBoard(board);
        flag = "reset";

        board[0][7] = "wK";
        board[1][7] = "wp";
        board[1][6] = "wp";
        board[7][7] = "wN"; //add random knight that cant save the king
        board[0][0] = "bQ";
        checkmate(board, hs, &flag);
        assert(strcmp(flag, "CHECKMATE") == 0);

        baseHistory(2);
        baseBoard(board);
        flag = "reset";

        board[0][7] = "wK";
        board[1][0] = "bQ";
        board[0][0] = "bQ";
        checkmate(board, hs, &flag);
        assert(strcmp(flag, "CHECKMATE") == 0);
    #pragma endregion

    printf("\nCHECKMATE TEST PASSED\n");
    system("pause");
}

static void baseBoard(char * board[8][8]){
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            board[i][j] = "--";
        }
    }
}

static void baseHistory (int no){

    free(hs);
    hs = malloc(sizeof(history));
    move *m = createMove(createPoint(1,1),createPoint(1,1), "bp", "--");
    hs->mx = malloc(sizeof(move));
    hs->mx = m;
    hs->next = NULL;

    history * temp, *head;
    temp = hs;
    for(int i = 0; i < no-1; i++){
        move *m = createMove(createPoint(1,1),createPoint(1,1), "wp", "--");
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = malloc(sizeof(history));
        temp = temp->next;
        temp->mx = malloc(sizeof(move));
        temp->mx = m;
        temp->next = NULL;

    }
}