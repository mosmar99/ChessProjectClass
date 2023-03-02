#ifndef DLLINTERFACE_H
#define DLLINTERFACE_H
#include <stdbool.h>

//  __declspec(dllexport)  used to declare export from dll
//  use "dumpbind /exports <dll filepath>" in cmd to show exports

void __declspec(dllexport) initGame();
void __declspec(dllexport) readBoard(char *rboard[8][8]);
bool __declspec(dllexport) proposeMove();

#endif