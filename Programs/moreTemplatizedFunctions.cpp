//
//  moreTemplatizedFunctions.cpp
//  moreTemplatizedFunctions
//
//  Created by Vince Mansel on 10/19/11.
//  Copyright (c) 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "simpio.h"
#include "vector.h"
#include "cmpFn.h"

template <typename Type>
void RemoveDuplicates(Vector<Type> &v, int (cmpFn)(Type, Type) = OperatorCmp);

int AbsoluteCompare(int one, int two) {
    one = abs(one);
    two = abs(two);
	if (one == two) return 0;
	if (one < two) return -1;
	return 1;
}


int main() {
    
    Vector<int> v;
    v.add(1);
    v.add(1);
    v.add(2);
    v.add(3);
    v.add(4);
    v.add(2);
    v.add(-2);
    v.add(3);
    v.add(4);
    
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << ",";
    }
    cout << endl;
    
    RemoveDuplicates(v,AbsoluteCompare);
    
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << ",";
    }
    
    return 0;
}

template <typename Type>
void RemoveDuplicates(Vector<Type> &v, int (cmpFn)(Type, Type)) {
    
    for (int i = 0; i < v.size()-1; i++) {
        for (int j = v.size() - 1; j > i; j--) {
            if (cmpFn(v[i],v[j]) == 0)
                v.removeAt(j);
        }
    }
}
