//
//  examStatistics.cpp
//  examStatistics
//
//  Created by Vince Mansel on 9/26/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "genlib.h"
#include "simpio.h"
#include "strUtils.h"

struct scoreStats {
    double min;
    double max;
    double avg;
};

int main() {
    
    scoreStats scores;
    scores.min = 100;
    scores.max = 0;
    scores.avg = 0;
    
    ifstream in;
    in.open("scores.txt");
    
    int numScores = 0;
    
    if (in.fail()) Error("Can't open files.");
    
    string line;
    while (true) {
        getline(in, line);
        if (in.fail()) break; // no more lines to read
        double score = StringToReal(line);
        if (score < scores.min)
            scores.min = score;
        if (score > scores.max)
            scores.max = score;
        scores.avg += score;
        numScores++;
    }
    
    scores.avg /= numScores;
    
    cout << "Scores: MIN = " << scores.min << endl;
    cout << "Scores: MAX = " << scores.max << endl;
    cout << "Scores: AVG = " << scores.avg << endl;
    cout << "Scores: NUM = " << numScores << endl;
    
    return 0;
}
