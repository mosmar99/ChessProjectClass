#include "makeMove.h"
#include <assert.h>

int main() {
    enum player turn = BLANCO; // whites turn

    // a piece should not be able to capture another allied piece, if error, returns false
    move *m1 = createMove(createPoint(0,0), createPoint(1,0), "wR", "wp");
    assert(catchGeneralErrors(m1, turn) == false);

    move *m2 = createMove(createPoint(0,0), createPoint(1,0), "wR", "--");
    assert(catchGeneralErrors(m2, turn) == true);
    
    puts("TEST PASSED");
}