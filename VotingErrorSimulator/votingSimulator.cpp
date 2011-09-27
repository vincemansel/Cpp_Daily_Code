//
//  votingSimulator.cpp
//  perfectNumber
//
//  Created by Vince Mansel on 9/26/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

#include <iostream>
#include "vector.h"

//#include <vector>

#include "genlib.h"
#include "simpio.h"
#include "random.h"

const int MaxTrials = 500;

struct scoreStatsT {
    double min;
    double max;
    double avg;
    int num;
};

double RunElectionTrial(int voters, double spread, double votingError);
scoreStatsT calculateStatistics(Vector<int> elections);

int main() {
    
    bool endSim = false;
    
    Randomize();
    
    while (true) {
        double invalidElectResult = 0;
        int voters;
        double spread;
        double votingError;
        int trialRuns;
        
        Vector<int> elections;
        
        while (true) {
            cout << "Enter number of voters (or 0 to end simulation): ";
            voters = GetInteger();
            if (voters == 0) {
                endSim = true;
                break;
            }
            else if (voters < 0)
                cout << "Enter a positive integer." << endl;
            else
                break;
        }
        
        if (endSim) break;
        
        while (true) {
            cout << "Enter percentage spread between candidates (0 - 1.0): ";
            spread = GetReal();
            if (spread >=0 && spread <= 1.0)
                break;
            else
                cout << "Spread must be between 0 and 1.0" << endl;
        }
        while (true) {
            cout << "Enter voting error percentage: (0 - 1.0): ";
            votingError = GetReal();
            if (votingError >=0 && votingError <= 1.0)
                break;
            else
                cout << "Voting error must be between 0 and 1.0" << endl;
        }
        while (true) {
            cout << "Enter number of times to run the trial: ";
            trialRuns = GetInteger();
            if (trialRuns >= 1)
                break;
            else
                cout << "Enter a positive integer" << endl;
        }
        
        for (int i = 0; i < trialRuns; i++) {
            invalidElectResult = RunElectionTrial(voters, spread, votingError);
            cout << "Trial " << i + 1 << ": ";
            cout <<  "Chance of an invalid election result after 500 trials = " << invalidElectResult << "%" << endl;
            elections.add(invalidElectResult);
        }
        
        scoreStatsT scores = calculateStatistics(elections);
        
        cout << "Scores: MIN = " << scores.min << endl;
        cout << "Scores: MAX = " << scores.max << endl;
        cout << "Scores: AVG = " << scores.avg << endl;
        cout << "Scores: NUM = " << scores.num << endl;

        cout << "********************************************************" << endl << endl;
        
    }
    
    
    return 0;
}

scoreStatsT calculateStatistics(Vector<int> elections) {
    
    scoreStatsT scores;
    scores.min = 100;
    scores.max = 0;
    scores.avg = 0;
    
    int numScores = 0;


    
    for (int i = 0; i < elections.size(); i++ ) {
        double score = elections[i];
        if (score < scores.min)
            scores.min = score;
        if (score > scores.max)
            scores.max = score;
        scores.avg += score;
        numScores++;
    }
    
    scores.avg /= numScores;
    scores.num = numScores;
    
    //cout << "Scores: MIN = " << scores.min << endl;
    //cout << "Scores: MAX = " << scores.max << endl;
    //cout << "Scores: AVG = " << scores.avg << endl;
    //cout << "Scores: NUM = " << scores.num << endl;
    
    return scores;
}

double RunElectionTrial(int voters, double spread, double votingError) {
    int invalid = 0;
    
    for (int i = 0; i < MaxTrials; i++) {
        int votesForA = voters/2  + (voters * spread)/2;
        int votesForB = voters/2  - (voters * spread)/2;
        
        //cout << "Trial " << i << ": Before: A = " << votesForA << " : B = " << votesForB << " : A+B= " << votesForA + votesForB << " . " << endl;
        int errorA = 0;
        int errorB = 0;
        
        for (int j = 0; j < votesForA; j++)
            if (RandomChance(votingError)) {
                errorA++;
                votesForA--;
                votesForB++;
            }
        for (int j = 0; j < votesForB; j++)
            if (RandomChance(votingError)) {
                errorB++;
                votesForA++;
                votesForB--;
            }
        //cout << "Error against A # " << errorA << endl;
        //cout << "Error against B # " << errorB << endl;
        
        if (votesForA <= votesForB)
            invalid++;
        
        //cout << "Trial " << i << ": After: A = " << votesForA << " : B = " << votesForB << " : A+B= " << votesForA + votesForB << " Invalid = " << invalid << endl;
    }
    
    return 100.0 * (double)invalid/(double)MaxTrials;
}