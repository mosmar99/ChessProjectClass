#ifndef DLLINTERFACE_H
#define DLLINTERFACE_H
//  __declspec(dllexport)  used to declare export from dll

void __declspec(dllexport) initGame();
void __declspec(dllexport) readBoard(char *board[8][8]);
bool __declspec(dllexport) proposeMove();

#endif