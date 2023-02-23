#include "makeMove.h"
#include <assert.h>

bool noGeneralErrors2(move *mx, enum player turn)
{
    // general conditions that hold for all pieces
    // Ex: No piece can capture another ally piece

    // check that destination move already doesn't contain an allied piece
    if (*(mx->movingPiece) == *(mx->capturedPiece))
    {
        return false;
    }

    // if it is whites turn, they can not move blacks pieces and vice versa
    if (turn == BLANCO && *(mx->movingPiece) == 'b' || turn == NEGRO && *(mx->movingPiece) == 'w')
    {
        return false;
    }

    return true;
}

int main() {
    enum player turn = BLANCO; // whites turn

    // a piece should not be able to capture another allied piece, if error, returns false
    move *m1 = createMove(createPoint(0,0), createPoint(1,0), "wR", "wp");
    assert((noGeneralErrors2(m1, turn)) == false);

    move *m2 = createMove(createPoint(5,2), createPoint(1,1), "wR", "--");
    assert(noGeneralErrors2(m2, turn) == true);

    move *m3 = createMove(createPoint(2,3), createPoint(1,7), "wR", "wp");
    assert(noGeneralErrors2(m3, turn) == false);

    turn = NEGRO;
    move *m4 = createMove(createPoint(3,0), createPoint(1,2), "bR", "--");
    assert(noGeneralErrors2(m4, turn) == true);

    move *m5 = createMove(createPoint(2,3), createPoint(1,3), "bR", "bQ");
    assert(noGeneralErrors2(m5, turn) == false);
    
    move *m6 = createMove(createPoint(1,5), createPoint(5,0), "bp", "bp");
    assert(noGeneralErrors2(m6, turn) == false);

    destroyMove(m1);
    destroyMove(m2);
    destroyMove(m3);
    destroyMove(m4);
    destroyMove(m5);
    destroyMove(m6);
    
    puts("SELF-CAPTURE TEST PASSED");
}