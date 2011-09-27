//
//  perfectNumber.cpp
//  perfectNumber
//
//  Created by Vince Mansel on 9/26/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

#include <iostream>
#include "genlib.h"
#include "simpio.h"

const int MaxNum = 10000;

bool IsPerfect(int num);

int main() {
    
    for (int i = 1; i <= MaxNum; i++) {
        if (IsPerfect(i))
            cout << i << " is a perfect number!" << endl;
    }
    return 0;
}

bool IsPerfect(int num) {
    bool result = false;
    int divisorSum = 0;
    
    for (int i = 1; i <= num/2; i++)
        if (num % i == 0)
            divisorSum += i;
    
    if (divisorSum == num) {
        result = true;
    }
    
    return result;
}