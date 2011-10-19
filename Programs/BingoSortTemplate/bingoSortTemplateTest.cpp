//
//  bingoSortTemplateTest.cpp
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
#include "BingoSort.h"
#include "strutils.h"
#include "set.h"

template <typename Type>
void RunExperiment(Vector<Type> &data, int sortCount, int runs, int expNum, string dataCondition);

template <typename Type>
void RunTest1(Vector<Type> &data, int runs, string name);

void RunTest(Vector<int> &data, void (fn)(Vector<int> &, double), int runs, string name);

int CmpSets(Set<int> one, Set<int> two) { // Callback
    
    int sum1 = 0;
    Set<int>::Iterator itr = one.iterator();
    while (itr.hasNext()) {
        sum1 += itr.next();
    }
    
    int sum2 = 0;
    itr = two.iterator();
    while (itr.hasNext()) {
        sum2 += itr.next();
    }
    
	if (sum1 == sum2) return 0;
	if (sum1 < sum2) return -1;
	return 1;
}

int main() {
    
//    Randomize();
//    int startSize = 10;
//    int sortMax = 499;
//    int runs = 50;
//    int experiment = 0;
//    
//    Vector<string> data;
//    string dataCondition = "Pre-sorted";
//    
//    for (int size = startSize; size <= sortMax; size *= 2) {
//        data.clear();
//        for (int i = size; i > 0; i--) {
//            data.add(IntegerToString(i));
//        }
//        data.add("Wolf");
//        RunExperiment(data, size, runs, experiment++, dataCondition);
//    }
//    
//    cout << endl;
//
//    dataCondition = "Reverse Pre-sorted";
//    
//    for (int size = startSize; size <= sortMax; size *= 2) {
//        data.clear();
//        for (int i = 0; i < size; i++) {
//            data.add(IntegerToString(i));
//        }
//        data.add("Wolf");
//        RunExperiment(data, size, runs, experiment++, dataCondition);
//    }
//    
//    cout << endl;
//    
//    dataCondition = "Random";
//    
//    for (int size = startSize; size <= sortMax; size *= 2) {
//        data.clear();
//        data.add("Wolf");
//        data.add("Wiff");
//        for (int i = 0; i < size; i++) {
//            data.add(IntegerToString(RandomInteger(0,sortMax-1)));
//        }
//        data.add("Ableton");
//        data.add("Abletan");
//        RunExperiment(data, size, runs, experiment++, dataCondition);
//
//    }
//
//    for (int i = 0; i < data.size(); i++) {
//        cout << data[i] << " ";
//    }
    
    Vector<Set<int> > vs;
    Set<int> s1;
    s1.add(2);
    s1.add(8);
    
    vs.add(s1);
    
    Set<int> s2;
    s2.add(1);
    s2.add(2);
    s2.add(3);
    
    vs.add(s2);
    
    for (int i = 0; i < vs.size(); i++) {
        cout << vs[i].size() << " ";
    }
    
    cout << endl;
    BingoSort(vs, 1.0, CmpSets);
    
    for (int i = 0; i < vs.size(); i++) {
        cout << vs[i].size() << " ";
    }

    return 0;
}

template <typename Type>
void RunExperiment(Vector<Type> &data, int size, int runs, int expNum, string dataCondition) {
    
    cout << "Experiment " << expNum << ": Sorting " << size << " elements " << runs << " times." << endl;
    
    Vector<Type> v1;
    Vector<Type> v2;
    Vector<Type> v3;
    Vector<Type> v4;
    Vector<Type> v5;
    
    v1 = v2 = v3 = v4 = v5 = data;
    
    //RunTest(v1, BingoSort, runs, "V1 " + dataCondition + ":");
    
    RunTest1(v1, runs, "V1 " + dataCondition + ":");
    
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

int BigStringsFirst(string one, string two) {
	if (one.size() == two.size()) {
        if (one == two) return 0;
        if (one < two) return -1;
        return 1;
    }
	if (one.size() < two.size()) return -1;
	return 1;
}

template <typename Type>
void RunTest1(Vector<Type> &data, int runs, string name) {
    
    Vector<Type> testData;
    double start = double(clock()) / CLOCKS_PER_SEC;    
    
    for (int i = 0; i < runs; i++) {
        testData = data;
        BingoSort(testData, 1.0, BigStringsFirst);
    }
    
    double finish = double(clock()) / CLOCKS_PER_SEC;
    double elapsed = finish - start;
    
    cout << name << " Elapsed Time = " << elapsed/runs << endl;
    
    data = testData;
}

