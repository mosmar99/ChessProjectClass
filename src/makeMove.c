#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "makeMove.h"
#include "knight.h"
#include "pawn.h"

void play(char *board[size][size]) {
    bool play = true;
    while (play)
    {
        char *input = requestMove();
        move *mx = setupMoveData(input, board);
        //applyMove(mx, board);
        action(mx, board);
        printBoard(board);
    }

}

move *setupMoveData(char *input, char *board[size][size]) {
    move *mx = malloc(sizeof(move));
    mx->fromPoint = malloc(sizeof(point));
    mx->toPoint = malloc(sizeof(point));
    mx->capturedPiece = malloc(sizeof(char)*3);
    mx->movingPiece = malloc(sizeof(char)*3);
    char oldChessCoord[3];
    char newChessCoord[3];
    unsigned int oldArrCoord[2];
    unsigned int newArrCoord[2];
    if (mx == NULL)
    {
        puts("Error: failed to allocate memory for move.");
        return NULL;
    }

    if (*input == 'R' || *input == 'N' || *input == 'B' || *input == 'Q' || *input == 'K')
    {
        // get non-pawn coordinates
        extractChessCoord(oldChessCoord, input, 1, 2);
        extractChessCoord(newChessCoord, input, 5, 6);

    } else if (*input == 'a' || *input == 'b' || *input == 'c' || *input =='d' || *input == 'e' || *input == 'f' || *input == 'g')
    {
        // get pawn coordinates  
        extractChessCoord(oldChessCoord, input, 0, 1);
        extractChessCoord(newChessCoord, input, 3, 4);
    } else {
        puts("Invalid input");
        exit(0);
    }

    // put "--" in old position
    // example: "e, 2" -> "{1, 4} and "e, 4" -> {3, 4}
    getTransform(oldArrCoord, oldChessCoord);
    getTransform(newArrCoord, newChessCoord);

    // store data in struct move
    mx->fromPoint->col = oldArrCoord[1];
    mx->fromPoint->row = oldArrCoord[0];
    mx->toPoint->col = newArrCoord[1];
    mx->toPoint->row = newArrCoord[0];
   
    mx->movingPiece = board[oldArrCoord[0]][oldArrCoord[1]];
    mx->capturedPiece = board[newArrCoord[0]][newArrCoord[1]];

    return mx;
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

char *requestMove() {
    char *input = malloc( sizeof(char) * size );

    // prompt user for move
    printf("Enter white's move [Piece][Square]-->[Piece][Square]: ");
    fflush(stdout);

    // collect all input until eol
    readInput(input);

    return input;
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

void action(move *mx, char *board[size][size]) {
    // todo manipulate board according to move: "e2 e4"
    // put "--" in old position
    // put correctly coloured pawn in to-move-to-tile

    // put piece in its correct new position
    board[mx->toPoint->row][mx->toPoint->col] = board[mx->fromPoint->row][mx->fromPoint->col];

    // put "--"" in old position
    board[mx->fromPoint->row][mx->fromPoint->col] = "--";
}

void applyMove(move *mx, char *board[size][size]) {
    bool validMove;
    switch (mx->movingPiece[1])
    {
    case 'R':
        // validMove = checkRockMove(move, board);
        break;
    case 'N':
        validMove = checkKnightMove(mx, board);
        if (validMove)
            action(mx, board);        
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
        validMove = checkPawnMove(mx, board);
        if (validMove)
            action(mx, board);        
        break;    
    
    default:
        puts("---> Error: Not a valid move");
        return;
    }
}