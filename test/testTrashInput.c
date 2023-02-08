#include "makeMove.h"
#include <assert.h>

bool isWrongInput2(char *input) {

    char c;
    bool leftBound;
    bool rightBound;
    for(int iter = 0; iter < 8; iter++) { // "Nb1 Nc3\n" "e9 f8\n"
        c = *(input+iter);

        switch (iter)
        {
        case 0:
            if (!((c == 'R') || (c == 'N') || (c == 'B') || (c == 'Q') || (c == 'K') || (c == 'a') || (c == 'b') || (c == 'c') || (c == 'd') || (c == 'e') || (c == 'f') || (c == 'g') ||  (c == 'h')))
            {
                return true;
            }                        
            break;
        case 1:
            if (!(((c == 'a') || (c == 'b') || (c == 'c') || (c == 'd') || (c == 'e') || (c == 'f') || (c == 'g') ||  (c == 'h')) || (isdigit(c))))
            {
                return true;   
            }

            if (isdigit(c))
            {
                leftBound = (0 >= (int)(c)-48);
                rightBound = ((int)(c)-48 >= 9);  
                if ((leftBound || rightBound))
                {
                    return true;
                }
            }            
            break;
        case 2:
            if (!(isdigit(c) || isspace((c))))
            {
                return true;
            }

            if (isdigit(c))
            {
                leftBound = (0 >= (int)(c)-48);
                rightBound = ((int)(c)-48 >= 9);  
                if ((leftBound || rightBound))
                {
                    return true;
                }
            }            
            break;
        case 3:
            if (!(isspace((c)) || (c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'g' || c == 'h')))
            {
                return true;
            }            
            break;
        case 4:
            if (!((c == 'R' || c == 'N' || c == 'B' || c == 'Q' || c == 'K') || isdigit(c)))
            {
                return true;
            }

            if (isdigit(c))
            {
                leftBound = (0 >= (int)(c)-48);
                rightBound = ((int)(c)-48 >= 9);  
                if ((leftBound || rightBound))
                {
                    return true;
                }
            }            
            break;
        case 5:
            if (!((c == 'a' || c == 'b' || c == 'c' || c == 'd' || c == 'e' || c == 'f' || c == 'g' || c == 'h') || c == '\n'))
            {
                return true;                
            }
            if (c == '\n')
            {
                return false;
            }            
            break;
        case 6:
            if (!(isdigit(c)))
            {
                return true;
            } 

            leftBound = (0 >= (int)(c)-48);
            rightBound = ((int)(c)-48 >= 9);  
            if ((leftBound || rightBound))
            {
                return true;
            }            
            break;
        case 7:
            if (!(c == '\n'))
            {
                return true;
            }            
            break;            
        }
    } 
    return false;
}

int main() {

    char input1[8] = {'a', '9', ' ', 'a', '4', '\n'};
    assert(isWrongInput(input1) == true);
    char input2[8] = {'a', '4', ' ', 'a', '9', '\n'};
    assert(isWrongInput(input2) == true);
    char input3[8] = {'a', 'a', ' ', 'a', 'a', '\n'};
    assert(isWrongInput(input3) == true);
    char input4[8] = {'4', '4', ' ', '4', '4', '\n'};
    assert(isWrongInput(input4) == true);
    char input5[8] = {'0', '0', ' ', '0', '0', '\n'};
    assert(isWrongInput(input5) == true);
    char input6[8] = {'-', '-', ' ', '-', '-', '\n'};
    assert(isWrongInput(input6) == true);
    char input7[8] = {'3', '2', ' ', '2', '3', '\n'};
    assert(isWrongInput(input7) == true);
    char input8[12] = {'a', 'a', 's', 'd', 'a', 'a', 's', 'a', 's', 'd', '\n'};
    assert(isWrongInput(input8) == true);
    char input9[10] = {'a', 'm', '8', 'a', 's', 'd', 'n', '\n'};
    assert(isWrongInput(input9) == true);
    char input10[8] = {'a', 'm', 'n', '\n'};
    assert(isWrongInput(input10) == true);
    char input11[8] = {'\n'};
    assert(isWrongInput("\n") == true);
    char input21[8] = {'N', 'b', '1', '3', 'N', 'c', '3', '\n'};
    assert(isWrongInput("Nb1 Nc3") == true);

    char input12[8] = {'e', '2', ' ', 'e', '3', '\n'};
    assert(isWrongInput(input12) == false);
    char input13[8] = {'e', '2', ' ', 'e', '4', '\n'};
    assert(isWrongInput(input13) == false);
    char input14[8] = {'a', '2', ' ', 'a', '4', '\n'};
    assert(isWrongInput(input14) == false);
    char input15[8] = {'h', '2', ' ', 'h', '4', '\n'};
    assert(isWrongInput(input15) == false);
    char input16[8] = {'N', 'b', '1', ' ', 'N', 'c', '3', '\n'};
    assert(isWrongInput(input16) == false);
    char input17[8] = {'Q', 'f', '3', ' ', 'Q', 'b', '3', '\n'};
    assert(isWrongInput(input17) == false);
    char input18[8] = {'K', 'd', '3', ' ', 'K', 'b', '8', '\n'};
    assert(isWrongInput(input18) == false);
    char input19[8] = {'R', 'h', '1', ' ', 'R', 'h', '8', '\n'};
    assert(isWrongInput(input19) == false);
    char input20[8] = {'B', 'h', '1', ' ', 'B', 'a', '8', '\n'};
    assert(isWrongInput(input20) == false);

    puts("TRASH-INPUT TEST PASSED");
    exit(0);
}