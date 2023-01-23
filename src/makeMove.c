#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define size (7+1)

void requestMove(char *move);
void applyMove(char *move, char *board[8][8]);
void action(char *move, char *board[8][8]);
void printBoard(char *board[8][8]);

// bool *checkRockMove(const char *const input, char *board[8][8];
// bool *checkKnightMove(const char *const input, char *board[8][8]);
// bool *checkBishopMove(const char *const input, char *board[8][8]);
// bool *checkQueenMove(const char *const input, char *board[8][8]);
// bool *checkKingMove(const char *const input, char *board[8][8]);
bool *checkPawnMove(const char *const input, char *board[8][8]);

void play(char *board[8][8]) {
    bool play = true;
    while (play)
    {
        //get next move
        char *move = malloc( sizeof(char) * size );
        requestMove(move);
        // applyMove(move, board);
        action(move, board);
        printBoard(board);
    }

}

void readInput(char *move) {
    char c;
    for (size_t i = 0; i < size; i++)
    {
        c = getchar();
        if (c == '\n'||c == '\0') 
        {
            *(move+i) = c;
            return;
        } 
        else 
        {
            *(move+i) = c;
        }
    }
}

void requestMove(char *move) {
    // prompt user for move
    printf("Enter white's move [Piece][Square]-->[Piece][Square]: ");
    fflush(stdout);

    // collect all input until eol
    readInput(move);
}

// input para: dest and src are given
// cpyFrom start at char you want to cpy 
// cpyTo end at char you want to cpy to
void extractChessCoord(char *dest, char *src, int cpyFrom, int cpyTo) {
    size_t i = cpyFrom;
    size_t j = 0;
    for (; i <= cpyTo; i++, j++)
    {
        *(dest+j) = *(src+i);
    }
    *(dest+j) = '\n';
}

// only gets input like "e2" and makes it into {1, 4}
void getTransform(int *dest, char *src) {
    switch (*(src+0))
    {
    case 'a':
        *(dest+1) = 0;
        break;
    case 'b':
        *(dest+1) = 1;
        break;
    case 'c':
        *(dest+1) = 2;
        break;
    case 'd':
        *(dest+1) = 3;
        break;
    case 'e':
        *(dest+1) = 4;
        break;
    case 'f':
        *(dest+1) = 5;
        break;
    case 'g':
        *(dest+1) = 6;
        break;
    case 'h':
        *(dest+1) = 7;
        break;

    default:
        puts("Could not extract valid coordinates");
        break;
    }    

    switch (*(src+1))
    {
    case '1':
        *(dest+0) = 0;
        break;
    case '2':
        *(dest+0) = 1;
        break;
    case '3':
        *(dest+0) = 2;
        break;
    case '4':
        *(dest+0) = 3;
        break;
    case '5':
        *(dest+0) = 4;
        break;
    case '6':
        *(dest+0) = 5;
        break;
    case '7':
        *(dest+0) = 6;
        break;
    case '8':
        *(dest+0) = 7;
        break;

    default:
        puts("Could not extract valid coordinates");
        break;
    }    
}

void action(char *move, char *board[8][8]) {
    // todo manipulate board according to move: "e2 e4"
    // put -- in old position
    // put correctly coloured pawn in to-move-to-tile
    
    char oldChessCoord[3];
    char newChessCoord[3];
    int oldArrCoord[2];
    int newArrCoord[2];
    if (*move == 'R' || *move == 'N' || *move == 'B' || *move == 'Q' || *move == 'K')
    {
        // get non-pawn coordinates
        extractChessCoord(oldChessCoord, move, 1, 2);
        extractChessCoord(newChessCoord, move, 5, 6);

    } else if (*move == 'a' || *move == 'b' || *move == 'c' || *move =='d' || *move == 'e' || *move == 'f' || *move == 'g')
    {
        // get pawn coordinates  
        extractChessCoord(oldChessCoord, move, 0, 1);
        extractChessCoord(newChessCoord, move, 3, 4);
    } else {
        puts("Invalid input");
        exit(0);
    }

    // put "--" in old position
    // example: "e, 2" -> "{1, 4} and "e, 4" -> {3, 4}
    getTransform(oldArrCoord, oldChessCoord);
    getTransform(newArrCoord, newChessCoord);

    // put piece in its correct new position
    board[newArrCoord[0]][newArrCoord[1]] = board[oldArrCoord[0]][oldArrCoord[1]];

    // put "--"" in old position
    board[oldArrCoord[0]][oldArrCoord[1]] = "--";
}

void applyMove(char *move, char *board[8][8]) {
    bool *validMove;
    switch (*(move))
    {
    case 'R':
        // validMove = checkRockMove(move, board);
        break;
    case 'N':
        // validMove = checkKnightMove(move, board);
        break;
    case 'B':
        // validMove = checkBishopkMove(move, board);
        break;
    case 'Q':
        // validMove = checkQueenMove(move, board);
        break;
    case 'K':
        // validMove = checkKingMove(move, board);
        break;
    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
        validMove = checkPawnMove(move, board);
        if (*validMove)
            action(move, board);        
        break;    
    
    default:
        puts("Not a valid move");
        return;
    }
}