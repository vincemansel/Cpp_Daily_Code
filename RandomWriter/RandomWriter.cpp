//
//  RandomWriter.cpp
//  RandomWriter
//
//  Created by Vince Mansel on 10/4/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

/*
 * RandomWriter generates random prose by analyzing a text with a given Markov
 * length which defines the number of characters in key string. For each key, the
 * following character is tracked. The longest key becomes the starting seed of the
 * prose. The next character is determined by its frequency of occurence after the
 * seed. The next seed is therefore the seed (minus its first char) + nextChar.
 * 
 * MaxChars (2000) characters are printed for the prose.
 *
 * See http://en.wikipedia.org/wiki/Markov_chain for more information.
 */

#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "vector.h"
#include "map.h"
#include <iostream>
#include <fstream>

typedef Map<Vector<string> > MapVectorT;

const int MaxChars = 2000;

int GetMarkov();
void GetFile(ifstream &if1);
string AnalyzeText(ifstream &if1, MapVectorT &model, int markov);
void ShowModel(MapVectorT &model);
void GenerateProse(MapVectorT &model, string longest);

int main() {
    
    Randomize();
    MapVectorT model;
    
    ifstream if1;
    int markov = GetMarkov();

    GetFile(if1);
    
    string longest = AnalyzeText(if1, model, markov);
    //ShowModel(model); // For testing
    GenerateProse(model, longest);
    
	return 0;
}

void GetFile(ifstream &if1) {
    ifstream input;
    
    while (true) {
        cout << "Input file: ";
        string filename = GetLine();
        //string filename = "sample.txt";
        //string filename = "TomSawyer.txt";
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

int GetMarkov() {
    int markov;
    while (true) {
        cout << "Enter the length of the Markov chain to use (1 - 10): ";
        markov = GetInteger();
        if (markov > 0 && markov <= 10) break;
    }
    return markov;
}

/*
 * Analyzes the text, creates the Markov model and returns one most frequent key
 */

string AnalyzeText(ifstream &if1, MapVectorT &model, int markov) {
    cout << " AnalyzeText: IN" << endl;
    string key;
    
    while (key.length() < markov) {
        char ch = if1.get();
        key += ch;
    }
    
    string longest = key;
    
    while (true) {
        //cout << " key: " << key;
        char nextCh = if1.get();
        //cout << " >> nextCh: " << nextCh;
        
        if (if1.fail()) {
            break;
        }
        
        string nextStr;
        nextStr += nextCh;

        if (!model.containsKey(key)) {
            //cout << " newVect created for key >>";
            Vector<string> newVect;
            newVect.add(nextStr);
            model[key] = newVect;
        }
        else {
            //cout << " Adding to previous key >>";
            model[key].add(nextStr);
        }
        
        if (model[key].size() > model[longest].size()) { // First time, same key
            longest = key;
        }
        
        key = key.substr(1) + nextCh;
        //cout << endl;
    }
 
    cout << " AnalyzeText: OUT" << endl;
    
    return longest;
}

void ShowModel(MapVectorT &model) {
    MapVectorT::Iterator iter = model.iterator();
    
    while (iter.hasNext()) {
        string key = iter.next();
        cout << key << ":";
        for (int i = 0; i < model[key].size(); i++) {
            cout << model[key].getAt(i) << " ";
        }
        cout << endl;
    }
}

string GetNextChar(MapVectorT &model, string seed) {
    int length = model[seed].size();
    string nextChar;
    if (length != 0) {
        int next = RandomInteger(0, length - 1);
        nextChar = model[seed][next];
    }
    return nextChar;
}

void GenerateProse(MapVectorT &model, string seed) {
    cout << seed;
    for (int i = 0; i < MaxChars; i++) {
        string nextChar = GetNextChar(model, seed);
        if (nextChar == "") break;
        cout << nextChar;
        seed = (seed + nextChar).substr(1);
    }
}
