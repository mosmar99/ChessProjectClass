#include "bishop.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <makeMove.h>

static bool checkInput(char *input, char *const board[8][8]);
static char * getDirection(const move *const m);
static bool exploreDirection (char *dir, const move *const m, char *const board[8][8]);

bool checkBishopMove(const move *const m, char *const board[8][8]){

    char *dir = getDirection(m);
    //direction was invalid I.e we did not perform a diagonal move.
    if(dir == NULL){
        return false;
    }
    //explore direction
    bool validDir = exploreDirection(dir, m, board);
    return validDir;
}

char * getDirection(const move *const m){

    char *direction;
    int deltaX = abs(m->fromPoint->row - m->toPoint->row);
    int deltaY = abs(m->fromPoint->col - m->toPoint->col);
    //Bishop moves on the diagonal
    //we need to check that the absolute values of delta x and delta y are equal otherwise and illegal move has been made
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
    return direction = NULL;
}

bool exploreDirection (char *dir, const move *const m, char *const board[8][8]){
    //explore nw
    if(strcmp(dir, "nw") == 0){
        int i = m->fromPoint->row - 1 , j = m->fromPoint->col + 1;
        while(i >  m->toPoint->row && j < m->toPoint->col){
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
        while(i <  m->toPoint->row && j < m->toPoint->col){
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
        while(i <  m->toPoint->row && j > m->toPoint->col){
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
    //direction was valid now check landing square
    char * toSquare = board[m->toPoint->row][m->toPoint->col];
    char * fromSquare = board[m->fromPoint->row][m->fromPoint->col];
    if(fromSquare[0] == toSquare[0]){
        return false;
    }
    //all test passed it is a valid move.
    return true;
}