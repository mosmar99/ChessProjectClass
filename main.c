#include "include/makeMove.h"

int main(void) {
    printf(BCYN "\n%s\n\n", "### New Game ###  " reset);
    printf(UYEL "%s\n", "Move Format:" reset);
    printf("%s%s%s\n", YEL "--> Pawns: " reset, "<From Column><From Row>--<Space>--<To Column><To Row>", GRN " e2 e4" reset);
    printf("%s%s%s\n", YEL "--> Minor or Major Pieces: " reset, "<Piece Letter><From Column><From Row>--<Space>--<Piece latter><To Column><To Row>", GRN " Nb1 Nc3" reset);
    char *board[8][8];
    initBoard(board);
    printBoard(board);
    play(board);
    return 0;
}
