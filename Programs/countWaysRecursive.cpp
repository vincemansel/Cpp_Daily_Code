//
//  countWaysRecursive.cpp
//  countWaysRecursive
//
//  Created by Vince Mansel on 10/11/11.
//  Copyright 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "simpio.h"

int CountWays(int numStairs);

int main() {
    
    for (int i = 1; i < 22; i++) {
        cout << i << " stairs can be climbed " << CountWays(i) << " ways." << endl;
    }
    return 0;
}

void RecCountWays(int &counter, int numStairs);

int CountWays(int numStairs) {
    int counter = 0;
    RecCountWays(counter, numStairs);
    return counter;
}

void RecCountWays(int &counter, int numStairs) {
    
    if (numStairs == 0) { // SUCCESS BASE CASE
        counter += 1;
    }
    else if (numStairs < 0) { // FAILURE BASE CASE
        counter += 0;
    }
    else {
        RecCountWays(counter, numStairs-1);
        RecCountWays(counter, numStairs-2);
    }
}