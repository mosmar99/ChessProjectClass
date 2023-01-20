#ifndef BOARDLOGIC_H
#define BOARDLOGIC_H

#define BOARDRC 8
#define COLOFFSET 97 //int 97 unicode = 'a'
#define ROWOFFSET 49 //int 49 unicode = '0'
#define LOWERCASEOFFSET 32


//indecies for allowed characters
#define PINDEX 0
#define COLINDEX 5
#define ROWINDEX 13
#define NUMALLOWEDCHARS 21

const char ALLOWEDCHARS[NUMALLOWEDCHARS] = {'K','Q','R','B','N','a','b','c','d','e','f','g','h','1','2','3','4','5','6','7','8'}

#endif