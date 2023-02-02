#include "queen.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <makeMove.h>

static char * getDirection(move *m);
static bool exploreDirection (char *dir, move *m, char *board[8][8]);

bool checkQueenMove(move *m, char *board[8][8]){

    int tempRow;
    int tempCol;

    tempRow = m->fromPoint->row - 1;
    tempCol = m->fromPoint->col - 1;
    
    m->fromPoint->row = tempCol;
    m->fromPoint->col = tempRow;

    tempRow = m->toPoint->row - 1;
    tempCol = m->toPoint->col - 1;
    
    m->toPoint->row = tempCol;
    m->toPoint->col = tempRow;


    char *dir = getDirection(m);
    if(dir == NULL){
        return false;
    }
    //explore direction
    bool validDir = exploreDirection(dir, m, board);
    return validDir;

}

char * getDirection(move *m){
    char *direction;
    int deltaX = abs(m->fromPoint->row - m->toPoint->row);
    int deltaY = abs(m->fromPoint->col - m->toPoint->col);
    //diagonal move
    if(deltaX == deltaY){
        if(m->fromPoint->row <  m->toPoint->row && m->fromPoint->col > m->toPoint->col){
            return direction = "nw";
        }
        if(m->fromPoint->row <  m->toPoint->row && m->fromPoint->col < m->toPoint->col){
            return direction = "ne";
        }
        if(m->fromPoint->row >  m->toPoint->row && m->fromPoint->col < m->toPoint->col){
            return direction = "se";
        }
        if(m->fromPoint->row >  m->toPoint->row && m->fromPoint->col > m->toPoint->col){
            return direction = "sw";
        } 
    }
    //move was not diagonal
    //may or may not still be valid since queen has the combined moveset of the bishop and rook.
    //either delta y or delta x must equal 0
    if(deltaY == 0){
        if(m->fromPoint->row < m->toPoint->row){
            return direction = "n";
        }
        else{
            return direction = "s";
        }
    }
    if(deltaX == 0){
        if(m->fromPoint->col < m->toPoint->col){
            return direction = "w";
        }
        else{
            return direction = "e";
        }
    }
    return direction = NULL;
}

bool exploreDirection (char *dir, move *m, char *board[8][8]){
    //explore nw
    if(strcmp(dir, "nw") == 0){
        int i = m->fromPoint->row - 1 , j = m->fromPoint->col + 1;
        while(i > m->toPoint->row && j < m->toPoint->col){
            if(strcmp(board[i][j], "--") != 0){
                return false;
            }
            i--;
            j++;
        }
    }
    //explore ne
    if(strcmp(dir, "ne") == 0){
        int i = m->fromPoint->row + 1 , j = m->fromPoint->col + 1;
        while(i < m->toPoint->row && j < m->toPoint->col){
            if(strcmp(board[i][j], "--") != 0){
                return false;
            }
            i++;
            j++;
        }
    }
    //explore se
    if(strcmp(dir, "se") == 0){
        int i = m->fromPoint->row + 1 , j = m->fromPoint->col - 1;
        while(i < m->toPoint->row && j > m->toPoint->col){
            if(strcmp(board[i][j], "--") != 0){
                return false;
            }
            i++;
            j--;
        }
    }
    //explore sw
    if(strcmp(dir, "sw") == 0){
        int i = m->fromPoint->row - 1 , j = m->fromPoint->col - 1;
        while(i > m->toPoint->row && j > m->toPoint->col){
            if(strcmp(board[i][j], "--") != 0){
                return false;
            }
            i--;
            j--;
        }
    }
    //explore n
    if(strcmp(dir, "n") == 0){
        int i = m->fromPoint->row + 1 , j = m->fromPoint->col;
        while(i > m->toPoint->row){
            if(strcmp(board[i][j], "--") != 0){
                return false;
            }
            i++;
        }
    }
    //explore e
    if(strcmp(dir, "e") == 0){
        int i = m->fromPoint->row, j = m->fromPoint->col - 1;
        while(j < m->toPoint->col){
            if(strcmp(board[i][j], "--") != 0){
                return false;
            }
            j--;
        }
    }
    //explore s
    if(strcmp(dir, "s") == 0){
        int i = m->fromPoint->row - 1 , j = m->fromPoint->col;
        while(i > m->toPoint->row){
            if(strcmp(board[i][j], "--") != 0){
                return false;
            }
            i--;
        }
    }
    //explore w
    if(strcmp(dir, "w") == 0){
        int i = m->fromPoint->row, j = m->fromPoint->col + 1;
        while(j > m->toPoint->col){
            if(strcmp(board[i][j], "--") != 0){
                return false;
            }
            j++;
        }
    }
    //direction was valid now check landing square
    char * toSquare = board[m->toPoint->row][m->toPoint->col];
    char * fromSquare = board[m->fromPoint->row][m->fromPoint->col];
    if(fromSquare[0] == toSquare[0]){
        return false;
    }
    //all test passed it is a valid move.
    return true;
}