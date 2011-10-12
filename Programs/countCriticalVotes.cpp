//
//  countCriticalVotes.cpp
//  countCriticalVotes
//
//  Created by Vince Mansel on 10/11/11.
//  Copyright 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "simpio.h"
#include "vector.h"

int CountCriticalVotes(Vector<int> & blocks, int blockIndex);

int main() {
    
    while (true) {
        Vector<int> blocks;
        Vector<int> makers;
        cout << "Enter block index: ";
        int blockIndex = GetInteger();
        int elements;
        while (true) {
            cout << "Enter the number of voting blocks (>1): ";
            elements = GetInteger();
            if (elements > 1) break;
        }
        for (int i = 0; i < elements; i++) {
            cout << "Enter size on voting block " << i+1 << ": ";
            int number = GetInteger();
            blocks.add(number);
        }
        int criticalVotes = CountCriticalVotes(blocks, blockIndex);
        cout << "Critical Votes: " << criticalVotes << endl;
    }
    return 0;
}

void CriticalVote(int &theCount, Vector<int> & soFar, int targetDiff, int majorityVotes) {
    //cout << "Critical Vote: ";
    int sum = 0;
    for (int i = 0; i < soFar.size(); i++) {
        sum += soFar[i];
        //cout << soFar[i] << " ";
    }
    //cout << "diff:" << targetDiff << " sum:" << sum << " majority:" << majorityVotes;
    if (sum < majorityVotes && targetDiff + sum > majorityVotes) {
        theCount += 1;
        //cout << " Yes: " << theCount;
    }
    //cout << endl;
}

void RecCanMakeSum(int &theCount, Vector<int> & soFar, Vector<int> & rest, int targetDiff, int majorityVotes) {
    if (rest.size() == 0) {
        CriticalVote(theCount, soFar, targetDiff, majorityVotes);
        return;
    }
    Vector<int> soFar1 = soFar;
    soFar1.add(rest[0]);
    Vector<int> rest1 = rest;
    rest1.removeAt(0);
    RecCanMakeSum(theCount, soFar1, rest1, targetDiff, majorityVotes);
    RecCanMakeSum(theCount, soFar, rest1, targetDiff, majorityVotes);
}

int GetMajorityVotes(Vector<int> & blocks) {
    int votes = 0;
    for (int i = 0; i < blocks.size(); i++) {
        votes += blocks[i];
    }
    int majority = votes/2;
    if (votes % 2 != 0) majority += 1;
    cout << "Majority = " << majority << endl;
    return majority; 
}

int CountCriticalVotes(Vector<int> & blocks, int blockIndex) {
    Vector<int> soFar;
    int theCount = 0;
    int targetDiff = blocks[blockIndex];
    int majorityVotes = GetMajorityVotes(blocks);
    blocks.removeAt(blockIndex);
    RecCanMakeSum(theCount, soFar, blocks, targetDiff, majorityVotes);
    return theCount;
}