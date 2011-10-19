//
//  bingoSort.cpp
//  template
//
//  Created by Vince Mansel on 10/18/11.
//  Copyright (c) 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "vector.h"
#include "simpio.h"
#include "random.h"
#include <ctime>

void BingoSort(Vector<int> &v, double = -1);

void RunExperiment(Vector<int> &data, int sortCount, int runs, int expNum, string dataCondition);
void RunTest(Vector<int> &data, void (fn)(Vector<int> &, double), int runs, string name);


int main() {
    
    Randomize();
    int startSize = 10;
    int sortMax = 4000;
    int runs = 500;
    int experiment = 0;
    
    Vector<int> data;
    string dataCondition = "Pre-sorted";
    
    for (int size = startSize; size <= sortMax; size *= 2) {
        data.clear();
        for (int i = size; i > 0; i--) {
            data.add(i);
        }
        RunExperiment(data, size, runs, experiment++, dataCondition);
    }
    
    cout << endl;

    dataCondition = "Reverse Pre-sorted";
    
    for (int size = startSize; size <= sortMax; size *= 2) {
        data.clear();
        for (int i = 0; i < size; i++) {
            data.add(i);
        }
        RunExperiment(data, size, runs, experiment++, dataCondition);
    }
    
    cout << endl;
    
    dataCondition = "Random";
    
    for (int size = startSize; size <= sortMax; size *= 2) {
        data.clear();
        for (int i = 0; i < size; i++) {
            data.add(RandomInteger(0,sortMax-1));
        }

        RunExperiment(data, size, runs, experiment++, dataCondition);

    }

    
    for (int i = 0; i < data.size(); i++) {
        cout << data[i] << " ";
    }
    
    
    
    return 0;
}

/* 
 * Code adapted from http://en.wikipedia.org/wiki/Bingo_sort
 */

void Swap(int & one, int & two);

void BingoSort(Vector<int> &v1, double d) {
    // This procedure sorts in ascending order.
    
    int max = v1.size()-1;
    
    // The first iteration is written to look very similar to the subsequent ones, but without swaps.
    int nextValue = v1[max];
    
    for (int i = max - 1; i >= 0; i--) {
        if (v1[i] > nextValue) { 
            nextValue = v1[i];
        }
    }
    while ((max > 0) && (v1[max] == nextValue)) {
        max -= 1;
    }
    
    while (max > 0) {
        int value = nextValue;
        nextValue = v1[max];
        for (int i = max - 1; i >= 0; i--) {
            if (v1[i] == value) {
                Swap(v1[i], v1[max]);
                max -= 1;
            }
            else if (v1[i] > nextValue) {
                nextValue = v1[i];
            }
        }
        while ((max > 0) && (v1[max] == nextValue)) {
            max -= 1;
        }
    }
}

void Swap(int & one, int & two) {
    int temp = one;
    one = two;
    two = temp;
}

void RunExperiment(Vector<int> &data, int size, int runs, int expNum, string dataCondition) {
    
    cout << "Experiment " << expNum << ": Sorting " << size << " elements " << runs << " times." << endl;
    
    Vector<int> v1;
    Vector<int> v2;
    Vector<int> v3;
    Vector<int> v4;
    Vector<int> v5;
    
    v1 = v2 = v3 = v4 = v5 = data;
    
    RunTest(v1, BingoSort, runs, "V1 " + dataCondition + ":");
    
    int foo = 0;
    foo++;
    
    data = v1;
}

void RunTest(Vector<int> &data, void (fn)(Vector<int> &, double), int runs, string name) {
    
    Vector<int> testData;
    double start = double(clock()) / CLOCKS_PER_SEC;    
    
    for (int i = 0; i < runs; i++) {
        testData = data;
        //fn(data, .000001);
        fn(testData, 1.0);
    }
    
    double finish = double(clock()) / CLOCKS_PER_SEC;
    double elapsed = finish - start;
    
    cout << name << " Elapsed Time = " << elapsed/runs << endl;
    
    data = testData;
}

