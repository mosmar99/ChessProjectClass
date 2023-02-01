#include "makeMove.h"
#include <assert.h>

int main() {
    enum player turn = BLANCO; // whites turn

    // a piece should not be able to capture another allied piece, if error, returns false
    move *m1 = createMove(createPoint(0,0), createPoint(1,0), "wR", "wp");
    assert((noGeneralErrors(m1, turn)) == false);

    move *m2 = createMove(createPoint(5,2), createPoint(1,1), "wR", "--");
    assert(noGeneralErrors(m2, turn) == true);

    move *m3 = createMove(createPoint(2,3), createPoint(1,7), "wR", "wp");
    assert(noGeneralErrors(m3, turn) == false);

    turn = NEGRO;
    move *m4 = createMove(createPoint(3,0), createPoint(1,2), "bR", "--");
    assert(noGeneralErrors(m4, turn) == true);

    move *m5 = createMove(createPoint(2,3), createPoint(1,3), "bR", "bQ");
    assert(noGeneralErrors(m5, turn) == false);
    
    move *m6 = createMove(createPoint(1,5), createPoint(5,0), "bp", "bp");
    assert(noGeneralErrors(m6, turn) == false);

    destroyMove(m1);
    destroyMove(m2);
    destroyMove(m3);
    destroyMove(m4);
    destroyMove(m5);
    destroyMove(m6);
    
    puts("SELF-CAPTURE TEST PASSED");
}