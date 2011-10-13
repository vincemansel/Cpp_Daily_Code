//
//  recursivePuzzleSolver.cpp
//  RecursivePuzzleSolver
//
//  Created by Vince Mansel on 10/12/11.
//  Copyright 2011 Wave Ocean Software. All rights reserved.
//

/* 
 * This program attemps to solve a puzzle consisting of a random set of integers
 * between 1 and 1/2 the length of the array that holds the integers.
 * Starting from index 0, the solver jumps to the next index indicated by the value
 * contained in the current index. From there, the solver can either jump forward
 * or backwards in the array. The goal is to reach the last index with value of zero.
 * 
 * The program is currently in test mode.
 */

#include <iostream>
#include "simpio.h"
#include "vector.h"
#include "map.h"
#include "random.h"

const bool TEST = true;
const int TestRuns = 100;
const int MinIndex = 40;
const int MaxIndex = 48;

bool Solvable(int start, Vector<int> & squares);

void TestSetup(Vector<int> & squares) {
//    squares.add(3);
//    squares.add(1);
//    squares.add(2);
//    squares.add(3);
//    squares.add(4);
//    squares.add(1);
//    squares.add(2);
//    squares.add(5);
//    squares.add(1);
//    squares.add(0);
    
    int length = RandomInteger(MinIndex, MaxIndex);
    cout << "(" << length << ") ";
    
    for (int i = 0; i < length; i++) {
        squares.add(RandomInteger(1,length/2));
    }
    squares.add(0);
    for (int i = 0; i < squares.size(); i++) {
        cout << squares[i] << " ";
    }
    cout << endl;
    
}

int main() {
    
    Randomize();
    
    int runs = TestRuns;
    int solvable = runs;
    
    while (true) {
        Vector<int> squares;
        if (TEST) {
            cout << "TestRun: " << runs-- << ": ";
            TestSetup(squares);
        }
        else {
            while (true) {
                cout << "Enter a number between 1 and 9 to seed puzzle (0 to end): ";
                int number = GetInteger();
                if (number >= 0 && number <= 9)
                    squares.add(number);
                else {
                    cout << "Try again..." << endl;
                }
                if (number == 0) {
                    break;
                };
            }
        }
        
        if (!Solvable(0, squares)) {
            cout << "NOT ";
            solvable--;
        }
        cout << "SOLVABLE" << endl;
        
        if (TEST) {
            if (runs == 0) {
                cout << "End of Tests: " << solvable << " of " << TestRuns << " SOLVABLE." << endl;
                cout << "Continue? (y or n): ";
                string line = GetLine();
                if (line[0] == 'n') break;
                runs = TestRuns;
                solvable = runs;
            }
        }
        else {
            cout << "Continue? (y or n): ";
            string line = GetLine();
            if (line[0] == 'n') break;
        }
    }

    return 0;
}

/* 
 * Function: Solvable(int start, Vector<int> & squares)
 * Usage: Solvable(0,square);
 *
 * This function takes a starting
 * position of the marker along with the vector of squares. The function returns true if it is
 * possible to solve the puzzle from the starting configuration and false if it is impossible.
 */

bool RecursiveSolvable(int start, int last, Map<bool> visited, Vector<int> & squares) {
    if (squares[start] == 0) // SUCCESS BASE CASE
        return true;
    
    visited.put(IntegerToString(last),true);
    
    //cout << "R1:" << start << endl;
    
    if (visited.get(IntegerToString(start))) // LOOP: FAILURE BASE CASE
        return false;
    
    if (!((start + squares[start]) >= squares.size())) { // STEP RIGHT IS OUT OF BOUND: FAILURE BASE CASE
        //cout << "R2:" << start + squares[start] << endl;
        return RecursiveSolvable(start + squares[start], start, visited, squares);
    }
    
    if (!((start - squares[start]) < 0)) { // STEP LEFT IS OUT OF BOUND: FAILURE BASE CASE
        //cout << "R3:" << start - squares[start] << endl;
        return RecursiveSolvable(start - squares[start], start, visited, squares);
    }

    return false;
}

bool Solvable(int start, Vector<int> & squares) {
    Map<bool> visited;
    for (int i = 0; i < squares.size(); i++) {
        visited.put(IntegerToString(i),false);
    }
    return RecursiveSolvable(start, squares.size()-1, visited, squares);
}

