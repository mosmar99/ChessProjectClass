#include "makeMove.h"
#include <assert.h>

int main() {
    enum player turn = BLANCO; // whites turn

    // a piece should not be able to capture another allied piece, if error, returns false
    move *m1 = createMove(createPoint(0,0), createPoint(1,0), "wR", "wp");
    assert(!(catchGeneralErrors(m1, turn)) == true);

    move *m2 = createMove(createPoint(5,2), createPoint(1,1), "wR", "--");
    assert(catchGeneralErrors(m2, turn) == false);

    move *m3 = createMove(createPoint(2,3), createPoint(1,7), "wR", "wp");
    assert(!catchGeneralErrors(m3, turn) == true);

    turn = NEGRO;
    move *m4 = createMove(createPoint(3,0), createPoint(1,2), "bR", "--");
    assert(catchGeneralErrors(m4, turn) == false);

    move *m5 = createMove(createPoint(2,3), createPoint(1,3), "bR", "bQ");
    assert(!catchGeneralErrors(m5, turn) == true);
    
    move *m6 = createMove(createPoint(1,5), createPoint(5,0), "bp", "bp");
    assert(!catchGeneralErrors(m6, turn) == true);
    
    puts("TEST PASSED");
}