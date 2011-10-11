//
//  canMakeSum.cpp
//  canMakeSum
//
//  Created by Vince Mansel on 10/11/11.
//  Copyright 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "simpio.h"
#include "vector.h"

bool CanMakeSum(int &theCount, Vector<int> & nums, int targetSum, Vector<int> & makers);

int main() {
    
    while (true) {
        Vector<int> nums;
        Vector<int> makers;
        int theCount = 0;
        cout << "Enter target sum: ";
        int targetSum = GetInteger();
        int elements;
        while (true) {
            cout << "Enter the number of elements in set (>1): ";
            elements = GetInteger();
            if (elements > 1) break;
        }
        for (int i = 0; i < elements; i++) {
            cout << "Enter element " << i+1 << ": ";
            int number = GetInteger();
            nums.add(number);
        }
        if (CanMakeSum(theCount, nums, targetSum, makers)) {
            cout << "Outer: ";
            for (int i = 0; i < makers.size(); i++) {
                cout << makers[i] << " ";
            }
            cout << endl;
//            cout << "YES" << endl;
            cout << "YES, there are/is " << theCount << " subset(s) that sum." << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
    return 0;
}

bool CanTheseSum(int &theCount, Vector<int> & soFar, int targetSum, Vector<int> & makers) {
    int sum = 0;
    for (int i = 0; i < soFar.size(); i++) {
        sum += soFar[i];
    }
    if (targetSum == sum) {
        cout << "Inner: ";
        for (int i = 0; i < soFar.size(); i++) {
            cout << soFar[i] << " ";
        }
        cout << endl;
        makers = soFar;
        theCount += 1;
        return true;
    }
    return false;
}

bool RecCanMakeSum(int &theCount, Vector<int> & soFar, Vector<int> & rest, int targetSum, Vector<int> & makers) {
    if (rest.size() == 0) {
        return CanTheseSum(theCount, soFar, targetSum, makers);
    }
    Vector<int> soFar1 = soFar;
    soFar1.add(rest[0]);
    Vector<int> rest1 = rest;
    rest1.removeAt(0);
//    if (RecCanMakeSum(theCount, soFar1, rest1, targetSum, makers)) return true;
    RecCanMakeSum(theCount, soFar1, rest1, targetSum, makers);
//    if (RecCanMakeSum(theCount, soFar, rest1, targetSum, makers)) return true;
    RecCanMakeSum(theCount, soFar, rest1, targetSum, makers);
    
    if (theCount > 0) return true;
    return false;
}

bool CanMakeSum(int &theCount, Vector<int> & nums, int targetSum, Vector<int> & makers) {
    Vector<int> soFar;
    return RecCanMakeSum(theCount, soFar, nums, targetSum, makers);
}