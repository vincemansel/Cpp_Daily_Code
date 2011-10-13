//
//  recursiveCutStock.cpp
//  recursiveCutStock
//
//  Created by Vince Mansel on 10/12/11.
//  Copyright 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "simpio.h"
#include "vector.h"

int CutStock(Vector<int> & requests, int stockLength);

void PrintInt(int piece) {
    cout << piece << " ";
}

int main() {
    
    while (true) {
        Vector<int> requests;
        cout << "Enter Stock Length (0 to quit): ";
        int stockLength = GetInteger();
        if (stockLength == 0) break;
        if (stockLength < 0) {
            cout << "Try Again... ";
            continue;
        }
        while (true) {
            cout << "Enter lenghth of cut (0 to quit): ";
            int piece = GetInteger();
            if (piece == 0) break;
            if (piece < 0 || piece > stockLength) {
                cout << "Try Again... ";
                continue;
            }
            requests.add(piece);
        }
        
        cout << "There are " << requests.size() << " pieces in this request:" << endl;
        requests.mapAll(PrintInt); cout << endl;
        
        int pipes = CutStock(requests, stockLength);
        
        cout << "This request requires " << pipes << " stock pieces." << endl;
        
    }
    
    return 0;
}

struct finalCutT {
    int stockPiece;
    int remains;
};

void RecursiveCutStock(Vector<int> & soFar,
                      Vector<int> & rest,
                      int stockLength,
                      Vector<finalCutT> &stockUsed);

finalCutT MakeCuts(Vector<int> & soFar, int stockLength);
int FindOptimalCut(Vector<finalCutT> &stockUsed, int max);

int CutStock(Vector<int> & requests, int stockLength) {
    Vector<int> soFar;
    Vector<finalCutT> stockUsed;
    
    RecursiveCutStock(soFar, requests, stockLength, stockUsed);
    return FindOptimalCut(stockUsed, requests.size());
}

void RecursiveCutStock(Vector<int> & soFar,
                  Vector<int> & rest,
                  int stockLength,
                  Vector<finalCutT> &stockUsed) {
       
    
    if (rest.size() == 0) { // BASE CASE
        //cout << "BASE CASE: "; 
        //soFar.mapAll(PrintInt); cout << endl;
        finalCutT pieces = MakeCuts(soFar, stockLength);
        stockUsed.add(pieces);
        return;
    }
    
    for (int i = 0; i < rest.size(); i++) { // Check all permutations
        
        Vector<int> soFar1 = soFar;
        soFar1.add(rest[i]);
        Vector<int> rest1 = rest;
        rest1.removeAt(i);
        
        RecursiveCutStock(soFar1, rest1, stockLength,  stockUsed);
    }
}

finalCutT MakeCuts(Vector<int> & soFar, int stockLength) {
    finalCutT pieces;
    
    // Take cuts
    int currentLength = 0;
    int stockPiece = 0;
    int remains = 0;
    
    for (int i = 0; i < soFar.size(); i++) {
        
        int currentPiece = soFar[i];
        //cout << "Before CUT: length:pieces:remains = " << currentLength << ":" << stockPiece << ":" << remains << endl;
        //cout << " R1: currentPiece: " << currentPiece << ", currentLength: " << currentLength << endl;
        if (currentPiece < currentLength) {
            currentLength -= currentPiece;
            remains -= currentPiece;
        }
        else if (currentPiece == currentLength) { // Even Cut, No Remains from this pipe.
            remains -= currentPiece;
            currentLength = 0;
        }
        else {
            stockPiece += 1;
            remains += stockLength;
            currentLength = stockLength - currentPiece;
            remains -= currentPiece;
            //cout << "  R4: New stock piece: " << stockPiece << endl;
        }
        
        //cout << "After CUT: length:pieces:remains = " << currentLength << ":" << stockPiece << ":" << remains << endl;
        
    }
    pieces.stockPiece = stockPiece;
    pieces.remains = remains;
    return pieces;
}

int FindOptimalCut(Vector<finalCutT> &stockUsed, int max) {
    
    finalCutT pieces;
    pieces.stockPiece = max;
    pieces.remains = max;
    
    for (int i = 0; i < stockUsed.size(); i++) {
        //cout << "i:" << i << " Pieces: " << stockUsed[i].stockPiece << ", Remains: " << stockUsed[i].remains << endl;
        if (stockUsed[i].stockPiece < pieces.stockPiece) {
            pieces.stockPiece = stockUsed[i].stockPiece;
            pieces.remains = stockUsed[i].remains;
        } else if (stockUsed[i].stockPiece == pieces.stockPiece && stockUsed[i].remains < pieces.remains) {
            pieces.remains = stockUsed[i].remains;
        }
    }
    return pieces.stockPiece;
    
}
