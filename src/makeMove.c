#include "makeMove.h"
#include "knight.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "remi.h"
#include "checkmate.h"

point *createPoint(unsigned int x, unsigned int y);
static void destroyPoint(point *p);
move *createMove(point *fromPoint, point *toPoint, char *movingPiece, char *CapturedPiece);
void destroyMove(move *move);
static void printMoves(history *head, int *iter);
static void printHistory();
bool isWrongInput(char *input);
void printBoard(char *board[8][8]);
void printBoardBlack(char *board[8][8]);
static void undoMove(move *mx, char *board[size][size]);

// Prompts the user for what piece they desire during a Pawn Promotion.
// Returns: 'Q' (queen), 'R' (rook), 'B' (bishop), or 'N' (knight).
static char promptPiece();

// Checks if the move is eligle for pawn promotion.
//      mx: a move struct filled with neccessary information for the played move.
// Returns true if a promotion is possible, otherwise false.
static bool checkPromotion(const move *const mx);

// Handler for pawn specific rules. (keep actions() clean)
//      mx: a move struct filled with neccessary information for the played move.
//      board: the string matrix representation of the current board state.
//      wasEnPassant: boolean flag which is true ONLY if the move was En Passant.
static void checkPawnStuff(const move *const mx, char *board[size][size], const bool *const wasEnPassant);

static history *head = NULL;
static enum player turn = BLANCO;
static char *gameEventFlag = NULL;
static bool isCli = true;

void clrscr()
{
    system("@cls||clear");
}

void initGame(bool enableCli){
    gameEventFlag = malloc(sizeof(char[50]));
    gameEventFlag = "IDLE";
    isCli = enableCli;
}

void play(char *board[size][size])
{
    initGame(true);
    bool play = true;
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

        if (isWrongInput(input))
        {
            puts("---> Invalid input, please re-enter a valid move");
            continue;
        }
        
        move *mx = constructMove(input, board);
        gameTurn(mx, board);
    }
}

int gameTurn(move* mx, char *board[size][size]){

    if (mx == NULL)
        return 0;

    if (noGeneralErrors(mx, turn))
    {
        // move is never applied if there are general piece errors
        if (noSpecificErrors(mx, applyMove(mx, board)))
        {
            // board is printed, with the desired valid move if its passed both general and specific piece errors
            if(strcmp(gameEventFlag, "BADMOVE") == 0){
                puts("---> BAD MOVE");
                checkmate(board,head,&gameEventFlag);
                return 0;
            }

            if (isCli){
                if (turn == NEGRO)
                {
                    printBoardBlack(board);
                    sleep(1);
                    //clrscr();
                    printBoard(board);
                }
                else
                {
                    printBoard(board);
                    sleep(1);
                    //clrscr();
                    printBoardBlack(board);
                }
            }
            // move is added to move history
            moveHistory(mx);

            // check for draw before continuing with game
            checkmate(board,head,&gameEventFlag);

            if(strcmp(gameEventFlag, "IDLE") == 0){
                if(remi(board, head, &gameEventFlag)){
                    printf("\n--->" BCYN "DRAW: %s\n" reset, gameEventFlag);
                    return 5;
                }
            }
            if(strcmp(gameEventFlag, "CHECK") == 0){
                printf("\n--->" BCYN "%s\n " reset, gameEventFlag);
            }
            if(strcmp(gameEventFlag, "CHECKMATE") == 0){
                printf("\n--->" BCYN "%s: " reset, gameEventFlag);
                if(turn == 0){
                    printf(BCYN "WHITE WINS\n");
                }
                else{
                    printf(BCYN "BLACK WINS\n");
                }
                //play = false;
            }

            turn = switchTurn(turn);
            return 1;
        }
    }
}

bool isWrongInput(char *input)
{

    char c;
    bool leftBound;
    bool rightBound;
    for (int iter = 0; iter < 8; iter++)
    { // "Nb1 Nc3\n" "e9 f8\n"
        c = *(input + iter);

        switch (iter)
        {
        case 0:
            if (!((c == 'R') || (c == 'N') || (c == 'B') || (c == 'Q') || (c == 'K') || (c == 'a') || (c == 'b') || (c == 'c') || (c == 'd') || (c == 'e') || (c == 'f') || (c == 'g') || (c == 'h')))
            {
                return true;
            }
            break;
        case 1:
            if (!(((c == 'a') || (c == 'b') || (c == 'c') || (c == 'd') || (c == 'e') || (c == 'f') || (c == 'g') || (c == 'h')) || (isdigit(c))))
            {
                return true;
            }

            if (isdigit(c))
            {
                leftBound = (0 >= (int)(c)-48);
                rightBound = ((int)(c)-48 >= 9);
                if ((leftBound || rightBound))
                {
                    return true;
                }
            }
            break;
        case 2:
            if (!(isdigit(c) || isspace((c))))
            {
                return true;
            }

            if (isdigit(c))
            {
                leftBound = (0 >= (int)(c)-48);
                rightBound = ((int)(c)-48 >= 9);
                if ((leftBound || rightBound))
                {
                    return true;
                }
            }
            break;
        case 3:
            if (!(isspace((c)) || (c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'g' || c == 'h')))
            {
                return true;
            }
            break;
        case 4:
            if (!((c == 'R' || c == 'N' || c == 'B' || c == 'Q' || c == 'K') || isdigit(c)))
            {
                return true;
            }

            if (isdigit(c))
            {
                leftBound = (0 >= (int)(c)-48);
                rightBound = ((int)(c)-48 >= 9);
                if ((leftBound || rightBound))
                {
                    return true;
                }
            }
            break;
        case 5:
            if (!((c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'g' || c == 'h') || c == '\n'))
            {
                return true;
            }
            if (c == '\n')
            {
                return false;
            }
            break;
        case 6:
            if (!(isdigit(c)))
            {
                return true;
            }

            leftBound = (0 >= (int)(c)-48);
            rightBound = ((int)(c)-48 >= 9);
            if ((leftBound || rightBound))
            {
                return true;
            }
            break;
        case 7:
            if (!(c == '\n'))
            {
                return true;
            }
            break;
        }
    }
    return false;
}

void printHistory()
{
    if (head == NULL)
    {
        puts("---> No moves have been made\n");
    }
    else
    {
        int *iter = malloc(sizeof(int));
        *iter = 3;
        printMoves(head, iter);
        puts("");
    }
}

// takes current player and gives turn to other
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
    int historyIter = 1;

    if (*iter % 2 != 0) // whites turn
    {

        if (curr->mx->movingPiece[1] == 'p')
        {
            printf(WHT "%2d." reset BLU "%4c%d" reset, (*iter) / 2, letter, digit);
        }
        else
        {
            printf(WHT "%2d." reset RED "%4c%c%d" reset, (*iter) / 2, curr->mx->movingPiece[1], letter, digit);
        }
    }
    else // black turn
    {
        if (curr->mx->movingPiece[1] == 'p')
        {
            printf(RED "%4c%d" reset "\n", letter, digit);
        }
        else
        {
            printf(RED "%3c%c%d" reset "\n", curr->mx->movingPiece[1], letter, digit);
        }
    }

    (*iter)++;
}

void moveHistory(move *mx)
{
    history *curr = calloc(1, sizeof(history));
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

bool noGeneralErrors(move *mx, enum player turn)
{
    // general conditions that hold for all pieces
    // Ex: No piece can capture another ally piece

    // check that destination move already doesn't contain an allied piece
    if (*(mx->movingPiece) == *(mx->capturedPiece))
    {
        puts("---> Error: Not a valid move");
        return false;
    }

    // if it is whites turn, they can not move blacks pieces and vice versa
    if (turn == BLANCO && *(mx->movingPiece) == 'b' || turn == NEGRO && *(mx->movingPiece) == 'w')
    {
        puts("---> Error: Not a valid move");
        return false;
    }

    return true;
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

bool noSpecificErrors(move *mx, bool isValidMove)
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

void readInput(char *move, int S)
{
    char c;
    fflush(stdin);
    for (size_t i = 0; i < S; i++)
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
    char *input = calloc((size + 1), sizeof(char));

    // prompt user for move
    if (turn == BLANCO)
    {
        printf("Enter " BLU "white's" reset " move: ");
        fflush(stdout);
    }
    else
    {
        printf("Enter " RED "black's" reset " move: ");
        fflush(stdout);
    }

    // collect all input until eol
    readInput(input, size);

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

static char promptPiece()
{
    char *piece = calloc(2, sizeof(char));
    while (true)
    {
        printf("Which piece do you want? (Q, R, B, N): ");
        fflush(stdout);

        readInput(piece, 2);

        switch (*piece)
        {
        case 'Q':
            return 'Q';
        case 'R':
            return 'R';
        case 'B':
            return 'B';
        case 'N':
            return 'N';
        }
    }
}

static bool checkPromotion(const move *const mx)
{
    if (mx == NULL)
        return false;

    // ONLY pawn may be promoted
    if (*(mx->movingPiece + 1) != 'p')
        return false;

    // check if the pawn reached the end
    if (*(mx->movingPiece) == 'w' && mx->toPoint->row == 7)
        return true;
    if (*(mx->movingPiece) == 'b' && mx->toPoint->row == 0)
        return true;

    return false;
}

static void checkPawnStuff(const move *const mx, char *board[size][size], const bool *const wasEnPassant)
{
    // if move was en passant
    //    put "--" behind the moved pawn
    //    --> if you don't, opponents pawn is still on the board
    //        (because the capturing pawn doesn't land on the captured piece in En Passant)
    if (*wasEnPassant && *(mx->movingPiece) == 'w')
        board[mx->toPoint->row - 1][mx->toPoint->col] = "--";
    if (*wasEnPassant && *(mx->movingPiece) == 'b')
        board[mx->toPoint->row + 1][mx->toPoint->col] = "--";

    if (checkPromotion(mx)) // check if a pawn can be promoted
    {
        char c = promptPiece();

        // this switch is absolutely horrendous, but was forced to do
        // it like this since any kind of strncpy yielded seg faults :(
        switch (*(mx->movingPiece))
        {
        case 'w':
            if (c == 'Q')
                board[mx->toPoint->row][mx->toPoint->col] = "wQ";
            else if (c == 'R')
                board[mx->toPoint->row][mx->toPoint->col] = "wR";
            else if (c == 'B')
                board[mx->toPoint->row][mx->toPoint->col] = "wB";
            else if (c == 'N')
                board[mx->toPoint->row][mx->toPoint->col] = "wN";
            break;
        case 'b':
            if (c == 'Q')
                board[mx->toPoint->row][mx->toPoint->col] = "bQ";
            else if (c == 'R')
                board[mx->toPoint->row][mx->toPoint->col] = "bR";
            else if (c == 'B')
                board[mx->toPoint->row][mx->toPoint->col] = "bB";
            else if (c == 'N')
                board[mx->toPoint->row][mx->toPoint->col] = "bN";
            break;
        }
    }
}

void action(move *mx, char *board[size][size], const bool *const wasEnPassant)
{
    // todo manipulate board according to move: "e2 e4"
    // put "--" in old position
    // put correctly coloured pawn in to-move-to-tile

    // put piece in its correct new position
    board[mx->toPoint->row][mx->toPoint->col] = board[mx->fromPoint->row][mx->fromPoint->col];

    // put "--"" in old position
    board[mx->fromPoint->row][mx->fromPoint->col] = "--";

    //Was the player checked?
    if(strcmp(gameEventFlag, "CHECK") == 0){
        checkmate(board, head, &gameEventFlag); //Did the move fix the check?
        if(strcmp(gameEventFlag, "CHECK") == 0 || strcmp(gameEventFlag, "CHECKMATE") == 0){ //If not then undo the move.
            undoMove(mx, board);
        }
    }

    //Now that the move has been made, check so that the player didnt put themselves in check.
    if(strcmp(gameEventFlag, "IDLE") == 0){
        checkmate(board, head, &gameEventFlag);
        if(strcmp(gameEventFlag, "CHECK") == 0 || strcmp(gameEventFlag, "CHECKMATE") == 0){ //If the player did put themselfs in check undo the move.
            undoMove(mx, board);
        }
    }

    checkPawnStuff(mx, board, wasEnPassant);

}

static void undoMove(move *mx, char *board[size][size]){
    board[mx->fromPoint->row][mx->fromPoint->col] = board[mx->toPoint->row][mx->toPoint->col];
    board[mx->toPoint->row][mx->toPoint->col] = "--";
    gameEventFlag = "BADMOVE";
}

bool applyMove(move *mx, char *board[size][size])
{
    bool validMove, enPassant = false;
    switch (mx->movingPiece[1])
    {
    case 'R':
        validMove = checkRookMove(mx, board);
        if (validMove)
            action(mx, board, &enPassant);
        return validMove;
    case 'N':
        validMove = checkKnightMove(mx, board);
        if (validMove)
            action(mx, board, &enPassant);
        return validMove;
    case 'B':
        validMove = checkBishopMove(mx, board); // segfault
        if (validMove)
            action(mx, board, &enPassant);
        return validMove;
    case 'Q':
        validMove = checkQueenMove(mx, board); // segfault
        if (validMove)
            action(mx, board, &enPassant);
        return validMove;
    case 'K':
        validMove = checkKingMove(mx, board);
        if (validMove)
            action(mx, board, &enPassant);
        return validMove;
        break;
    case 'p':
        validMove = checkPawnMove(mx, board, head, &enPassant);
        if (validMove)
            action(mx, board, &enPassant);
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