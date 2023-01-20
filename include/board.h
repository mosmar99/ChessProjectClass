#ifndef BOARD_H
#define BOARD_H

//Board as array of enums characters?

const char STANDARDBOARD[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"; // maybe load board from FEN

char getPiece(int col, int row);

#endif
