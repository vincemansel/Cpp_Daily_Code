//
//  histogram.cpp
//  histogram
//
//  Created by Vince Mansel on 9/27/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

/* 
 *  Produces a 10 bucket histogram for a list of scores from 0 to 99
 */

#include <fstream>
#include <iostream>
#include "simpio.h"
#include "genlib.h"
#include "vector.h"

void GetScores(Vector<int> &scores);
void ReadScores(ifstream &in1, Vector<int> &scores);
void ReadScores1(ifstream &in1, Vector<int> &scores);
void DrawHistogram(Vector<int> &scores);

int main() {
    Vector<int> scores;
    for (int i = 0; i < 10; i++) {
        scores.add(0);
    }
    GetScores(scores);
    DrawHistogram(scores);
    
    return 0;
}
                      
void GetScores(Vector<int> &scores) {
    ifstream in1;
    
    while (true) {
        cout << "Data file ?: ";
        string fileName = GetLine();
        
        in1.open(fileName.c_str());
        if (in1.fail()) {
            in1.clear();
            cout << "Try again... " << endl;
        }
        else {
            break;
        }
    }
    ReadScores(in1,scores);
    in1.close();
}

void ReadScores(ifstream &in1, Vector<int> &scores) {
    while (true) {
        int x;
        in1 >> x;
        if (in1.fail()) {
            break; // no more lines to read
        }
        cout << x << endl;
        //Input can haveletters, punctuation or whitespace, but only integers between 0 and 99 are accepted.
        
        if (x >= 0 && x <= 99) {
            scores[x / 10] += 1;
        }
        
    } 
}

void ReadScores1(ifstream &in1, Vector<int> &scores) {
    while (true) {
        string line;
        getline(in1, line);
    
        if (in1.fail()) {
            break; // no more lines to read
        }
        cout << line << endl;
        //Input line must be well form. Only digits. No letters, punctuation or whitespace.
        int x = StringToInteger(line);
        
        if (x >= 0 && x <= 99) {
            scores[x / 10] += 1;
        }
        
    } 
}


void DrawHistogram(Vector<int> &scores) {
    
    for (int i = 0; i < scores.size(); i++) {
        cout << i * 10 << "-" << (i * 10)+9 << ": ";
        for (int j = 0; j < scores[i]; j++) {
            cout << "X";
        }
        cout << endl;
    }
}