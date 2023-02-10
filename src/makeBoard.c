#include "stdio.h"
#include "stdlib.h"

void printBoardBlack(char *board[8][8]) {
    char numbers[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    char letters[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    printf("\n");
    for (size_t i = 0; i < 8; i++)
    {
        printf("%c   ", *(numbers+(i)));
        for (size_t j = 0; j < 8; j++)
        {
            printf("%s  ", board[i][7-j]);
        }
        printf("\n");
    }

    printf("\n    ");
    fflush(stdout);

    for (size_t i = 0; i < 8; i++)
    {
        printf("%c   ", *(letters+7-i));
    }
    

    printf("\n\n");    
}

void printBoard(char *board[8][8]) {
    char numbers[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    char letters[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

    printf("\n");
    for (size_t i = 0; i < 8; i++)
    {
        printf("%c   ", *(numbers+(7-i)));
        for (size_t j = 0; j < 8; j++)
        {
            printf("%s  ", board[7-i][j]);
        }
        printf("\n");
    }

    printf("\n    ");
    fflush(stdout);

    for (size_t i = 0; i < 8; i++)
    {
        printf("%c   ", *(letters+i));
    }
    

    printf("\n\n");
}

void initBoard(char *board[8][8]) {
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            board[i][j] = "--";
        }
    }

    // white
    board[0][0] = "wR";
    board[0][1] = "wN";
    board[0][2] = "wB";
    board[0][3] = "wQ";
    board[0][4] = "wK";
    board[0][5] = "wB";
    board[0][6] = "wN";
    board[0][7] = "wR";
    board[1][0] = "wp";
    board[1][1] = "wp";
    board[1][2] = "wp";
    board[1][3] = "wp";
    board[1][4] = "wp";
    board[1][5] = "wp";
    board[1][6] = "wp";
    board[1][7] = "wp";

    // black
    board[7][0] = "bR";
    board[7][1] = "bN";
    board[7][2] = "bB";
    board[7][3] = "bQ";
    board[7][4] = "bK";
    board[7][5] = "bB";
    board[7][6] = "bN";
    board[7][7] = "bR";
    board[6][0] = "bp";
    board[6][1] = "bp";
    board[6][2] = "bp";
    board[6][3] = "bp";
    board[6][4] = "bp";
    board[6][5] = "bp";
    board[6][6] = "bp";
    board[6][7] = "bp";
}
