#include "makeMove.h"
#include "knight.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"

point *createPoint(unsigned int x, unsigned int y);
static void destroyPoint(point *p);
move *createMove(point *fromPoint, point *toPoint, char *movingPiece, char *CapturedPiece);
void destroyMove(move *move);
static void printMoves(history *head, int *iter);
static enum player switchTurn(enum player turn);
static void printHistory();
void printBoard(char *board[8][8]);

history *head = NULL;

void play(char *board[size][size])
{
    bool play = true;
    enum player turn = BLANCO;
    while (play)
    {
        char *input = requestMove(turn);

        if (strcmp(input, "exit\n") == 0)
        {
            play = false;
            continue;
        }

        if (strcmp(input, "history\n") == 0)
        {
            printHistory();
            continue;
        }

        move *mx = constructMove(input, board);

        if (mx == NULL)
            continue;

        if (catchGeneralErrors(mx, turn))
        {
            // move is never applied if there are general piece errors
            if (catchSpecificErrors(mx, applyMove(mx, board)))
            {
                // board is printed, with the desired valid move if its passed both general and specific piece errors
                printBoard(board);

                // move is added to move history
                moveHistory(mx);

                // switch turn
                turn = switchTurn(turn);
                continue;
            }
        }
    }
}

void printHistory()
{
    if (head == NULL)
    {
        puts("");
        puts("No moves have been made");
    }
    else
    {
        puts("");
        int *iter = malloc(sizeof(int));
        *iter = 1;
        printMoves(head, iter);
        puts("");
    }
}

enum player switchTurn(enum player turn)
{
    if (turn == BLANCO)
    {
        return turn = NEGRO;
    }
    else
    {
        return turn = BLANCO;
    }
}

/* Function to reverse the linked list */
void printMoves(history *curr, int *iter)
{
    // Base case
    if (curr == NULL)
    {
        return;
    }

    // print the list after head node
    printMoves(curr->next, iter);

    char letter = (curr->mx->toPoint->col + 49) + '0';
    int digit = curr->mx->toPoint->row + 1;

    if (*iter % 2 != 0) // whites turn
    {

        if (curr->mx->movingPiece[1] == 'p')
        {
            printf("%2d.%4c%d", *iter, letter, digit);
        }
        else
        {
            printf("%2d.%4c%c%d", *iter, curr->mx->movingPiece[1], letter, digit);
        }
    }
    else // black turn
    {
        if (curr->mx->movingPiece[1] == 'p')
        {
            printf("%4c%d\n", letter, digit);
        }
        else
        {
            printf("%3c%c%d\n", curr->mx->movingPiece[1], letter, digit);
        }
    }

    (*iter)++;
    
}

void moveHistory(move *mx)
{
    history *curr = malloc(sizeof(history));
    if (head == NULL)
    {
        curr->mx = mx;
        head = curr;
    }
    else
    {
        curr->mx = mx;
        curr->next = head;
        head = curr;
    }
}

bool catchGeneralErrors(move *mx, enum player turn)
{
    // general conditions that hold for all pieces
    // Ex: No piece can capture another ally piece

    // check that destination move already doesn't contain an allied piece
    if (*(mx->movingPiece) == *(mx->capturedPiece))
    {
        puts("---> Error: Not a valid move");
        puts("---> Reason: Can not capture same colored piece");
        return false;
    }

    // if it is whites turn, they can not move blacks pieces and vice versa
    if (turn == BLANCO && *(mx->movingPiece) == 'b' || turn == NEGRO && *(mx->movingPiece) == 'w')
    {
        puts("---> Error: Not a valid move");
        puts("---> Reason: Can not move opponents pieces");
        return false;
    }

    return false;
}

void getPieceString(move *mx, char *piece)
{
    switch (*(mx->movingPiece + 1))
    {
    case 'R':
        *(piece + 0) = 'R';
        *(piece + 1) = 'o';
        *(piece + 2) = 'o';
        *(piece + 3) = 'k';
        break;
    case 'N':
        *(piece + 0) = 'K';
        *(piece + 1) = 'n';
        *(piece + 2) = 'i';
        *(piece + 3) = 'g';
        *(piece + 4) = 'h';
        *(piece + 5) = 't';
        break;
    case 'B':
        *(piece + 0) = 'B';
        *(piece + 1) = 'i';
        *(piece + 2) = 's';
        *(piece + 3) = 'h';
        *(piece + 4) = 'o';
        *(piece + 5) = 'p';
        break;
    case 'Q':
        *(piece + 0) = 'Q';
        *(piece + 1) = 'u';
        *(piece + 2) = 'e';
        *(piece + 3) = 'e';
        *(piece + 4) = 'n';
        break;
    case 'K':
        *(piece + 0) = 'K';
        *(piece + 1) = 'i';
        *(piece + 2) = 'n';
        *(piece + 3) = 'g';
        break;
    case 'p':
        *(piece + 0) = 'P';
        *(piece + 1) = 'a';
        *(piece + 2) = 'w';
        *(piece + 3) = 'n';
        break;
    }
}

bool catchSpecificErrors(move *mx, bool isValidMove)
{
    // if the desired move isn't a valid piece specific move, an error message will be printed
    if (!isValidMove)
    {
        char *piece;
        piece = malloc(sizeof(char) * size);
        getPieceString(mx, piece);
        printf("---> Error: The %s does not move in that way\n", piece);
        return false;
    }

    return true;
}

move *constructMove(char *input, char *board[size][size])
{

    char oldChessCoord[3];
    char newChessCoord[3];

    if (*input == 'R' || *input == 'N' || *input == 'B' || *input == 'Q' || *input == 'K')
    {
        // get non-pawn coordinates
        extractChessCoord(oldChessCoord, input, 1, 2);
        extractChessCoord(newChessCoord, input, 5, 6);
    }
    else if (*input == 'a' || *input == 'b' || *input == 'c' || *input == 'd' || *input == 'e' || *input == 'f' || *input == 'g' || *input == 'h')
    {
        // get pawn coordinates
        extractChessCoord(oldChessCoord, input, 0, 1);
        extractChessCoord(newChessCoord, input, 3, 4);
    }
    else
    {
        puts("Invalid input");
        return NULL;
    }

    // put "--" in old position
    // example: "e, 2" -> "{1, 4} and "e, 4" -> {3, 4}
    unsigned int oldArrCoord[2];
    unsigned int newArrCoord[2];
    getTransform(oldArrCoord, oldChessCoord);
    getTransform(newArrCoord, newChessCoord);

    // put in substructs
    point *from = createPoint(oldArrCoord[1], oldArrCoord[0]);
    point *to = createPoint(newArrCoord[1], newArrCoord[0]);
    char *movingPiece = board[oldArrCoord[0]][oldArrCoord[1]];
    char *capturingPiece = board[newArrCoord[0]][newArrCoord[1]];

    return createMove(from, to, movingPiece, capturingPiece);
}

void readInput(char *move)
{
    char c;
    fflush(stdin);
    for (size_t i = 0; i < size; i++)
    {
        c = getchar();
        if (c == '\n' || c == '\0')
        {
            *(move + i) = c;
            return;
        }
        else
        {
            *(move + i) = c;
        }
    }
}

char *requestMove(enum player turn)
{
    char *input = malloc(sizeof(char) * size);

    // prompt user for move
    if (turn == BLANCO)
    {
        printf("Enter white's move [Piece][Square]-->[Piece][Square]: ");
        fflush(stdout);
    }
    else
    {
        printf("Enter black's move [Piece][Square]-->[Piece][Square]: ");
        fflush(stdout);
    }

    // collect all input until eol
    readInput(input);

    return input;
}

// input para: dest and src are given
// cpyFrom start at char you want to cpy
// cpyTo end at char you want to cpy to
void extractChessCoord(char *dest, char *src, int cpyFrom, int cpyTo)
{
    size_t i = cpyFrom;
    size_t j = 0;
    for (; i <= cpyTo; i++, j++)
    {
        *(dest + j) = *(src + i);
    }
    *(dest + j) = '\n';
}

// only gets input like "e2" and makes it into {1, 4}
void getTransform(int *dest, char *src)
{
    switch (*(src + 0))
    {
    case 'a':
        *(dest + 1) = 0;
        break;
    case 'b':
        *(dest + 1) = 1;
        break;
    case 'c':
        *(dest + 1) = 2;
        break;
    case 'd':
        *(dest + 1) = 3;
        break;
    case 'e':
        *(dest + 1) = 4;
        break;
    case 'f':
        *(dest + 1) = 5;
        break;
    case 'g':
        *(dest + 1) = 6;
        break;
    case 'h':
        *(dest + 1) = 7;
        break;

    default:
        puts("---> Could not extract valid coordinates");
        return;
    }

    switch (*(src + 1))
    {
    case '1':
        *(dest + 0) = 0;
        break;
    case '2':
        *(dest + 0) = 1;
        break;
    case '3':
        *(dest + 0) = 2;
        break;
    case '4':
        *(dest + 0) = 3;
        break;
    case '5':
        *(dest + 0) = 4;
        break;
    case '6':
        *(dest + 0) = 5;
        break;
    case '7':
        *(dest + 0) = 6;
        break;
    case '8':
        *(dest + 0) = 7;
        break;

    default:
        puts("---> Could not extract valid coordinates");
        return;
    }
}

void action(move *mx, char *board[size][size])
{
    // todo manipulate board according to move: "e2 e4"
    // put "--" in old position
    // put correctly coloured pawn in to-move-to-tile

    // put piece in its correct new position
    board[mx->toPoint->row][mx->toPoint->col] = board[mx->fromPoint->row][mx->fromPoint->col];

    // put "--"" in old position
    board[mx->fromPoint->row][mx->fromPoint->col] = "--";
}

bool applyMove(move *mx, char *board[size][size])
{
    bool validMove;
    switch (mx->movingPiece[1])
    {
    case 'R':
        validMove = checkRookMove(mx, board);
        if (validMove)
            action(mx, board);
        return validMove;
    case 'N':
        validMove = checkKnightMove(mx, board);
        if (validMove)
            action(mx, board);
        return validMove;
    case 'B':
        // validMove = checkBishopkMove(move, board);
        break;
    case 'Q':
        // validMove = checkQueenMove(move, board);
        break;
    case 'K':
        // validMove = checkKingMove(move, board);
        break;
    case 'p':
        validMove = checkPawnMove(mx, board);
        if (validMove)
            action(mx, board);
        return validMove;

    default:
        return false;
    }
}

point *createPoint(unsigned int col, unsigned int row)
{

    point *p = malloc(sizeof(point));

    if (p)
    {
        p->col = col;
        p->row = row;
        return p;
    }
    else
    {
        return NULL;
    }
}

static void destroyPoint(point *p)
{
    if (p)
    {
        free(p);
    }
}

move *createMove(point *fromPoint, point *toPoint, char *movingPiece, char *CapturedPiece)
{
    move *newMove = malloc(sizeof(move));

    if (newMove)
    {
        newMove->movingPiece = malloc(sizeof(char[3]));
        newMove->capturedPiece = malloc(sizeof(char[3]));
        strcpy(newMove->movingPiece, movingPiece);
        strcpy(newMove->capturedPiece, CapturedPiece);

        newMove->fromPoint = fromPoint;
        newMove->toPoint = toPoint;
    }
    return newMove;
}

void destroyMove(move *move)
{

    if (move)
    {
        destroyPoint(move->fromPoint);
        destroyPoint(move->toPoint);

        free(move->movingPiece);
        free(move->capturedPiece);

        free(move);
    }
}