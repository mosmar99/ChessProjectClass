#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "makeMove.h"

void printBoard(char *board[8][8]);
void initBoard(char *board[8][8]);
void play(char *board[size][size]);

int main(void) {

    printf("%s\n", "    ### New Game ###  ");
    char *board[8][8];
    initBoard(board);
    printBoard(board);
    play(board);
    exit(0);
}

