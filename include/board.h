#ifndef BOARD_H
#define BOARD_H

//Board as array of enums?

const char STANDARDBOARD[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

int getBoard(int col, int row);

enum PIECE_NUMERIC{
    // White
    P = 'A', //'P' = 80
    N = 'N', //'K' = 78
    B = 'B', //'B' = 66
    R = 'R', //'R' = 82
    Q = 'Q', //'Q' = 81
    K = 'K', //'K' = 75

    //Black
    p = 'a', //'P' = 112
    n = 'n', //'K' = 110
    b = 'b', //'B' = 66
    r = 'r', //'R' = 82
    q = 'q', //'Q' = 81
    k = 'k', //'K' = 75
};


#endif
