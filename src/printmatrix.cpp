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

int EntryFatness (const SmithNormalFormCalculator::Matrix<int>& M) {
    int currentMax = 1;
    for (unsigned long rowIndex = 0; rowIndex < M.GetHeight(); rowIndex++ ) {
        const std::vector<int>& row = M[rowIndex];
        for (int x: row) {
            int t = DigitLength(x);
            if (currentMax < t) {
                currentMax = t;}
            }
        }
    return currentMax;
}


