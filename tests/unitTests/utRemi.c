#include "stdio.h"
#include "remi.h"
#include "makeMove.h"
#include <assert.h>

static void baseBoard(char * board[8][8]);
static void baseHistory (int no);
static void utPrintBoard(char * board[8][8]);

struct history *hs = NULL;

void main (void){

    char *board[8][8];
    char *flag = "whatever";
    history *temp;
    
    #pragma region ***Sufficient Material***
        baseBoard(board);
        //king v king + atleast one pawn = not draw
        board[5][5] = "wK";
        board[5][6] = "wp";
        board[3][3] = "bK";
        assert(remi(board, hs, &flag) == false);
        baseBoard(board);
        //king v king + 2 bishops = not draw
        board[5][5] = "wK";
        board[3][3] = "bK";
        board[4][4] = "bB";
        board[4][5] = "bB";
        assert(remi(board, hs, &flag) == false);
        baseBoard(board);
        //king v king + any material other than horse or bishop = not draw
        board[5][5] = "wK";
        board[3][3] = "bK";
        board[4][5] = "bQ";
        assert(remi(board, hs, &flag) == false);
        baseBoard(board);
        //king + material v. king + 2 horses = not draw
        board[5][5] = "wK";
        board[3][3] = "bK";
        board[4][4] = "bB";
        board[4][5] = "wN";
        board[4][6] = "wN";
        assert(remi(board, hs, &flag) == false);

    #pragma endregion

    #pragma region ***Insufficient Material***
        baseBoard(board);
        //king v. king is draw
        board[4][4] = "wK";
        board[5][7] = "bK";
        assert(remi(board, hs, &flag) == true);
        baseBoard(board);
        //king v. king + 1 knight = draw
        board[4][4] = "wK";
        board[4][4] = "wN";
        board[5][7] = "bK";
        assert(remi(board, hs, &flag) == true);
        baseBoard(board);
        //king v. king + 2 knights = draw
        board[4][4] = "wK";
        board[4][6] = "wN";
        board[0][0] = "wN";
        board[5][7] = "bK";
        assert(remi(board, hs, &flag) == true);
        baseBoard(board);
        //king v. king + 1 bishop = draw
        board[4][4] = "wK";
        board[4][4] = "wB";
        board[5][7] = "bK";
        assert(remi(board, hs, &flag) == true);

    #pragma endregion

    #pragma region ***Great number of moves with and without captures captures***
        baseBoard(board); //board needs some material to get past the sufficient material check.
        board[5][5] = "wK";
        board[5][6] = "wp";
        board[3][3] = "bK";

        baseHistory(50); //50 moves no captures = draw
        assert(remi(board, hs, &flag) == true);

        baseHistory(49); //49 moves no captures = not draw
        assert(remi(board,hs, &flag) == false);

        //put random move in middle that isnt empty
        baseHistory(50);
        temp = hs;
        for(int i = 0; i < 10; i++){
            temp = temp->next;
        }
        temp->mx->capturedPiece = "bp";
        assert(remi(board, hs, &flag) == false); //random capture move making not draw;

    #pragma endregion

    #pragma region ***Three fold repetition***
        baseBoard(board);
        baseHistory(6);

        board[5][5] = "wK"; //add material so we get past the sufficient material check
        board[5][6] = "wp";
        board[3][3] = "bK";

        temp = hs;
        for(int i = 0; i < 6; i++){
            if((i % 2) == 0){
                temp->mx->movingPiece = "wR";
            }
            else{
                temp->mx->movingPiece = "bR";
            }
            temp = temp->next;
        }
        assert(remi(board,hs, &flag) == true); // 3 fold repetition same position is repeted 3 times = draw

        baseHistory(6);
        temp = hs;
        for(int i = 0; i < 6; i++){
            if((i % 2) == 0){
                temp->mx->movingPiece = "wR";
            }
            else{
                temp->mx->movingPiece = "bR";
            }
            if(i == 4){ //change random move in the middle
                temp->mx->toPoint->col = 5;
            }
            temp = temp->next;
        }
        assert(remi(board,hs, &flag) == false);
    #pragma endregion


    #pragma region ***No valid moves left***
        baseBoard(board);
        baseHistory(3); //random move history to get past 3 fold repetition


        board[7][5] = "wK";
        board[6][5] = "wR";
        board[2][1] = "wp";


        board[7][7] = "bK";
        board[3][1] = "bp";

        assert(remi(board, hs, &flag) == true);


    #pragma endregion

    printf("REMI TEST PASSED\n");
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
    move *m = createMove(createPoint(1,1),createPoint(1,1), "--", "--");
    hs->mx = malloc(sizeof(move));
    hs->mx = m;
    hs->next = NULL;

    history * temp, *head;
    temp = hs;
    for(int i = 0; i < no-1; i++){
        move *m = createMove(createPoint(1,1),createPoint(1,1), "--", "--");
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