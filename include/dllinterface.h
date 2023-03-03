#ifndef DLLINTERFACE_H
#define DLLINTERFACE_H
#include <stdbool.h>

//  __declspec(dllexport)  used to declare export from dll
//  use "dumpbind /exports <dll filepath>" in cmd to show exports

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

void EXPORT initGame();
void EXPORT readBoard(char *rboard[8][8]);
bool EXPORT proposeMove();

#endif