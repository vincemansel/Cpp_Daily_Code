//
//  countLetters.cpp
//  countLetters
//
//  Created by Vince Mansel on 9/26/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "genlib.h"
#include "simpio.h"
#include "strUtils.h"

void CountLetters(string filename);

int main() {
    
    string filename = "sample.rtf";
    CountLetters(filename);
    
    return 0;

}

void CountLetters(string filename) {
    
    vector<int> count(26,0);
    
    ifstream in;
    in.open(filename.c_str());
    if (in.fail()) Error("Can't open file: " + filename);
    
    while (true) {
        string line;
        getline(in, line);
        if (in.fail()) break; // no more lines to read
        for (int i = 0; i < line.length(); i++) {
            line = ConvertToLowerCase(line);
            char ch = line[i];
            if (isalpha(ch))
                count[ch - 'a']++;
        }
    }
    
    in.close();
    
    // Experiment with vector iterator
    
    vector<int>::iterator it;
    int i = 0;
    for (it=count.begin(); it < count.end(); it++) {
        char ch = 'a' + i;
        cout << ch << ": " << *it << endl;
        i++;
    }
}

