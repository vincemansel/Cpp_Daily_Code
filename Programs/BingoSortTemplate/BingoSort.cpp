//
//  BingoSort.cpp
//  bingoSortTemplateTest
//
//  Created by Vince Mansel on 10/18/11.
//  Copyright (c) 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "BingoSort.h"
/* 
 * Code adapted from http://en.wikipedia.org/wiki/Bingo_sort
 */

template <typename Type>
void Swap(Type & one, Type & two) {
    Type temp = one;
    one = two;
    two = temp;
}

template <typename Type>
void BingoSort(Vector<Type> &v1, double d, int (cmpFn)(Type, Type)) {
    // This procedure sorts in ascending order.
    
    int max = v1.size()-1;
    
    // The first iteration is written to look very similar to the subsequent ones, but without swaps.
    Type nextValue = v1[max];
    
    for (int i = max - 1; i >= 0; i--) {
        if (cmpFn(v1[i],nextValue) == 1) { 
            nextValue = v1[i];
        }
    }
    while ((max > 0) && (cmpFn(v1[max],nextValue) == 0)) {
        max -= 1;
    }
    
    while (max > 0) {
        Type value = nextValue;
        nextValue = v1[max];
        for (int i = max - 1; i >= 0; i--) {
            if (cmpFn(v1[i],value) == 0) {
                Swap(v1[i], v1[max]);
                max -= 1;
            }
            else if (cmpFn(v1[i],nextValue) == 1) {
                nextValue = v1[i];
            }
        }
        while ((max > 0) && (cmpFn(v1[max],nextValue) == 0)) {
            max -= 1;
        }
    }
}

