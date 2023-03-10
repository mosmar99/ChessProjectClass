#include <stdio.h>
#include <checkmate.h>
#include <makeMove.h>
#include <assert.h>

static void baseBoard(char * board[8][8]);

history * hs = NULL;

static void addMoves(move *mx);

void main (void){
    char * board[8][8];
    char * flag = malloc(sizeof(char[50]));

    move *m1 = createMove(createPoint(7,7), createPoint(7,7), "wK", "wK");
    addMoves(m1);

    move *m2 = createMove(createPoint(7,0), createPoint(7,0), "bQ", "bQ");
    addMoves(m2);

    history *check = hs;

    flag = "reset";
    baseBoard(board);

    board[7][7] = "wK";
    board[0][7] = "bQ";
    checkmate(board, hs, &flag);
    assert(strcmp(flag, "CHECK") == 0);

    flag = "reset";
    baseBoard(board);

    board[7][7] = "wK";
    board[5][6] = "bN";
    checkmate(board, hs, &flag);
    assert(strcmp(flag, "CHECK") == 0);

    baseBoard(board);
    flag = "reset";

    board[0][7] = "wK";
    board[1][7] = "wp";
    board[1][6] = "wp";
    board[7][7] = "wB"; //bishop can attack queen diagonally h8-a1
    board[0][0] = "bQ";
    checkmate(board, hs, &flag);
    assert(strcmp(flag, "CHECK") == 0);

    baseBoard(board);
    flag = "reset";

    board[7][7] = "wK";
    board[6][7] = "wp";
    board[6][6] = "wp"; //this pawn can move up one
    board[7][0] = "bQ";
    checkmate(board, hs, &flag);
    assert(strcmp(flag, "CHECK") == 0);


    baseBoard(board);
    flag = "reset";

    board[0][7] = "wK"; //same position as the bishop one above but this time no bishop to save the king.
    board[1][7] = "wp";
    board[1][6] = "wp";
    board[0][0] = "bQ";
    checkmate(board, hs, &flag);
    assert(strcmp(flag, "CHECKMATE") == 0);

    baseBoard(board);
    flag = "reset";

    board[0][7] = "wK";
    board[1][7] = "wp";
    board[1][6] = "wp";
    board[7][7] = "wN"; //add random knight that cant save the king
    board[0][0] = "bQ";
    checkmate(board, hs, &flag);
    assert(strcmp(flag, "CHECKMATE") == 0);

    baseBoard(board);
    flag = "reset";

    board[0][7] = "wK";
    board[1][0] = "bQ";
    board[0][0] = "bQ";
    checkmate(board, hs, &flag);
    assert(strcmp(flag, "CHECKMATE") == 0);

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

static void addMoves(move *mx)
{
    history *curr = calloc(1, sizeof(history));
    if (hs == NULL)
    {
        curr->mx = mx;
        hs = curr;
    }
    else
    {
        curr->mx = mx;
        curr->next = hs;
        hs = curr;
    }
}