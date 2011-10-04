//
//  mostFrequentCharacterMap.cpp
//  mostFrequentCharacterMap
//
//  Created by Vince Mansel on 10/3/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "simpio.h"
#include "map.h"
#include "strutils.h"

void GetFile(ifstream &if1);
char MostFrequentCharacter(ifstream &if1, int &numOccurrences);

int main() {
    int numOccurrences = 0;
    ifstream if1;
    
    GetFile(if1);
    
    char ch = MostFrequentCharacter(if1, numOccurrences);
    
    cout << "The character " << ch << " occurs " << numOccurrences << " times.";
    
    return 0;
}

char MostFrequentCharacter(ifstream &if1, int &num) {
    
    char winner;
    Map<int> map;
    
    while (true) {
        char ch = if1.get();
        if (if1.fail()) {
            break;
        }
        if ( ch == ' ' ) {
            continue;
        }
        if (!map.containsKey(IntegerToString(ch - '0'))) {
            map.add(IntegerToString(ch - '0'),1);
        }
        else {
            map.put(IntegerToString(ch - '0'),map.get(IntegerToString(ch - '0'))+1);
        }
    }
    
    Map<int>::Iterator iter = map.iterator();
    num = 0;
    
    while (iter.hasNext()) {
        string sch = iter.next();
        if (map[sch] > num) {
            num = map[sch];
            winner = StringToInteger(sch) + '0';
        }
    }
    
    return winner;
}


void GetFile(ifstream &if1) {
    ifstream input;
    
    while (true) {
        cout << "Input file: ";
        string filename = GetLine();
        //string filename = "cppref.html";
        if1.open(filename.c_str());
        if (if1.fail()) {
            cout << "Error: can not open " << filename << ". Try again..." << endl;
            if1.clear();
        }
        else {
            break;
        }
    }
}
