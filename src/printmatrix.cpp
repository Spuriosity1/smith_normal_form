#include <iostream>
#include <vector>
#include <math.h>
#include <string.h>
#include <string>

#include "printmatrix.hpp"

int DigitLength (int a) { // returns number of digits of a.
    if (a < 0){
        a = -a;}
    if (a == 0){
        return 1;
    }
    else {
        return 1 + floor(log10(a));}
}


