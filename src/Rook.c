// #include <stdio.h>
// #include <stdbool.h>
// #include <stdlib.h>
// #include <string.h>
// //#include "rook.h"

// bool is_valid_rook_move(char* startPos, char* endPos, char* board[8][8]) 
// {
//     int start_x = startPos[0] - 'a';
//     int start_y = startPos[1] - '1';
//     int end_x = endPos[0] - 'a';
//     int end_y = endPos[1] - '1';
//     // check if starting and end positions are on the board. If it is not return NULL
//     if(start_x < 0 || start_x > 7 || start_y < 0 || start_y > 7 || end_x < 0 || end_x > 7 || end_y < 0 || end_y > 7)
//      return NULL;

//     if (start_x == end_x || start_y == end_y) 
//     {
//         //check if there is no piece blocking the path
//         if(start_x == end_x) //vertical move 
//         {
//             int min_y = start_y < end_y ? start_y : end_y;
//             int max_y = start_y > end_y ? start_y : end_y;
//             for(int i = min_y + 1; i < max_y; i++){
//                 if(board[start_x][i] != '.')
//                  return false;
//             }
//         }
//         else
//         { // start_y == end_y means horizontal move
//             int min_x = start_x < end_x ? start_x : end_x;
//             int max_x = start_x > end_x ? start_x : end_x;
//             for(int i = min_x + 1; i < max_x; i++)
//             {
//                 if(board[i][start_y] != '.') 
//                 return false;
//             }
//         }
//         return true;
//     }
//     else 
//     {
//         return false;
//     }
// }
