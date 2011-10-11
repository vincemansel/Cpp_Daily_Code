//
//  isMeasurableRecursive.cpp
//  isMeasurableRecursive
//
//  Created by Vince Mansel on 10/10/11.
//  Copyright 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "simpio.h"
#include "vector.h"

bool IsMeasurable(int target, Vector<int> & weights);

int main() {
    
    
    while (true) {
        
        Vector<int> sampleWeights;
        cout << "Enter Weight 1 (or -1 to quit): ";
        int w1 = GetInteger();
        if (w1 == -1) break;
        sampleWeights.add(w1);
        cout << "Enter Weight 1 (or -1 to quit): ";
        int w2 = GetInteger();
        if (w2 == -1) break;
        sampleWeights.add(w2);
        
        while (true) {
            cout << "Enter Weight of object (or -1 for new weights): ";
            int w3 = GetInteger();
            if (w3 == -1) break;
            string str;
            if (!IsMeasurable(w3, sampleWeights)) str = "not ";
            cout << "An object with weight " << w3 << " is " <<  str << "measurable with " << w1 << " and " << w2 << "." << endl;
        }
        
    }
    
    return 0;
}

bool MeasureObject(int target, Vector<int> balance, Vector<int> weights) {
    bool result = false;
    
    int left = 0;
    int right = 0;
    
    for (int i = 0; i < balance.size(); i++)
        left += balance[i];
    
    for (int i = 0; i < weights.size(); i++)
        right += weights[i];
    
    if ((target + left) == right)
        result = true;
    
    return result;
}

void AddWeightToObject(Vector<int> & soFar, Vector<int> & rest, int i) {
    soFar.add(rest[i]);
    rest.removeAt(i);
}

void DropWeight(Vector<int> & rest, int i) {
    rest.removeAt(i);
}

bool IsMeasurableR(int target, Vector<int> balance, Vector<int> weights) {
    
    if (weights.size() == 0) {
        return MeasureObject(target, balance, weights);
    }
    else {
        if (MeasureObject(target, balance, weights))
            return true;
        for (int i = 0; i < weights.size(); i++) {
            Vector<int> soFar = balance;
            Vector<int> rest = weights;
            AddWeightToObject(soFar,rest,i);
            if (IsMeasurableR(target, soFar, rest))
                return true;
            soFar = balance;
            rest = weights;
            DropWeight(rest,i);
            if (IsMeasurableR(target, soFar, rest))
                return true;
        }
    }
    return false;
}

bool IsMeasurable(int target, Vector<int> & weights)
{
    Vector<int> balance;
    return IsMeasurableR(target, balance, weights);
}


bool RecIsMeasurable(int target, Vector<int> & weights, int index)
{
    if (target == 0)
    {
        return true;
    }
    if (index >= weights.size())
    {
        return false;
    }
    return (RecIsMeasurable(target + weights[index], weights, index + 1)
            || RecIsMeasurable(target, weights, index + 1)
            || RecIsMeasurable(target - weights[index], weights,
                               index + 1));
}
bool IsMeasurable2(int target, Vector<int> & weights)
{
    return RecIsMeasurable(target, weights, 0);
}
