//
//  sortDetective.cpp
//  sortDetective
//
//  Created by Vince Mansel on 10/18/11.
//  Copyright (c) 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "simpio.h"
#include "vector.h"
#include "random.h"

#include "mysterysort.h"
#include <ctime>

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

    
    
//    Vector<int>::Iterator itr = v1.iterator();
//    while (itr.hasNext()) {
//        cout << itr.next() << " ";
//    }
    
    
    return 0;
}

void RunExperiment(Vector<int> &data, int size, int runs, int expNum, string dataCondition) {
    
    cout << "Experiment " << expNum << ": Sorting " << size << " elements " << runs << " times." << endl;
    
    Vector<int> v1;
    Vector<int> v2;
    Vector<int> v3;
    Vector<int> v4;
    Vector<int> v5;
    
    v1 = v2 = v3 = v4 = v5 = data;
    
    RunTest(v1, MysterySort1, runs, "V1 " + dataCondition + ":");
    RunTest(v2, MysterySort2, runs, "V2 " + dataCondition + ":");
    RunTest(v3, MysterySort3, runs, "V3 " + dataCondition + ":");
    RunTest(v4, MysterySort4, runs, "V4 " + dataCondition + ":");
    RunTest(v5, MysterySort5, runs, "V5 " + dataCondition + ":");
    int foo = 0;
    foo++;
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
