// #include <stdbool.h>
// #include <string.h>
// #include <ctype.h>
// #include "boardlogic.h"
// #include "board.h"

// struct point{
//     unsigned int x;
//     unsigned int y;
// };

// struct move{
//     char movingPiece;
//     struct point *fromPoint;

//     char capturedPiece;
//     struct point *toPoint;
// };

// bool makeMove(/*pointer to board + move*/ ){

// }

// // move input string ex "Nf3 Nc6", "Nf3 c6"
// bool parseMove(/*Board array ** to pass along to _CanMove() */char *string, struct move *move){

//     char *token = strtok(string, ' ');

//     parseToken(token, true, move->fromPoint, (*move).movingPiece);

//     strtok(NULL, ' ');

//     parseToken(token, false, move->toPoint, (*move).capturedPiece);

//     //send to correct library/function

//     //return if move was performed
//     return true;
// }

// bool parseToken(char *token, bool first, struct point *p, char *c){

//     if(!token || strlen(token) < 2 || strlen(token) > 3){ 
//         return false;
//     }

//     int tokenLength = strlen(token);

//     // Check and assign rank and file (COL and ROW)
//     if (charIsValid(token[0], COLINDEX, ROWINDEX) && charIsValid(token[1], ROWINDEX, NUMALLOWEDCHARS)){
//         p->x = token[tokenLength - 2] - COLOFFSET;
//         p->y = token[tokenLength - 1] - ROWOFFSET;
//     } else {
//         return false;
//     }

//     // Check that the correct Piece is on the board location
//     char piece = getPiece(p->x, p->y);
//     if(tokenLength == 2 && first && (piece == 'p' || piece == 'P')){
//         *c = piece;
//         return true;

//     } else if (tokenLength == 2 && !first && (piece == 'p' || piece == 'P' || piece == '-')){
//         *c = piece;
//         return true;

//     } else if (tokenLength == 3 && (piece == token[0] || piece == token[0] - LOWERCASEOFFSET)){
//         *c = piece;
//         return true;

//     } else {
//         return false;
//     }  
// }

// bool charIsValid(char *c, int indexStart, int indexStop){
//     for (size_t i = indexStart; i < indexStop; i++)
//     {
//         if (c == ALLOWEDCHARS[i]){
//             return true;
//         }           
//     }

//     return false;  
// }