#include "makeMove.h"

void printBoard(char *board[8][8]);
void initBoard(char *board[8][8]);

int main(void) {

    printf("%s\n", "    ### New Game ###  ");
    char *board[8][8];
    initBoard(board);
    printBoard(board);
    play(board);
    exit(0);
}

