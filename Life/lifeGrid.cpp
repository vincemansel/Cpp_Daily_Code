//
//  lifeGrid.cpp
//  life
//
//  Created by Vince Mansel on 9/29/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//


#include <iostream>

#include "genlib.h"
#include "extgraph.h"
#include "simpio.h"
#include "strutils.h"
//#include "random.h"
#include "grid.h"

#include "lifeGrid.h"
#include "lifeGraphics.h"

/*
 * Simulation Update Speed Note:
 *  SimSpeed of 1 calls pause with 0    seconds
 *              2                  0.1
 *              3                  0.5    
 */
const double FrameRateMuliplier = 0.1; // Fast Simulation
//Nullifies the fast sim when turtle mode (3 - 1 = 2) selected. 2 * 0.25 = 0.5 second updates.
const double FrameRateAdjustment = (1 / FrameRateMuliplier) * 0.25;

int CountNeighbors(gridLifeT &gridLife, int row, int col, int simMode);
void ShowGrid(gridLifeT &gridLife);
void PopulateHood(Grid<bool>& hood, gridLifeT &gridLife, int row, int col, int simMode);
bool IsDirectionOccupied(gridLifeT &gridLife, int row, int col, int dRow, int dCol);
int CountNeighborsInHood(Grid<bool>& hood);

void DrawGrid(gridLifeT &gridLife) {
    InitLifeGraphics(gridLife.size.row, gridLife.size.col);
    for (int i = 0; i < gridLife.size.row; i++)
        for (int j = 0; j < gridLife.size.col; j++)
            DrawCellAt(i, j, gridLife.lifeGrid.getAt(i,j));
    UpdateDisplay();
    //ShowGrid(gridLife);
}

void RunLifeSim(int simSpeed, int simMode, gridLifeT &gridLife) {
    //cout << "Stub for RunLifeSim(" << simSpeed << ", " << simMode << ", GRID= " << gridLife.size.row << ":" << gridLife.size.col << ")" << endl;
    cout << endl;
    
    if (simSpeed == 4) {
        while (true) {
            cout << "RETURN to continue (or \"quit\" to end simulation): "; 
            string line = ConvertToLowerCase(GetLine());
            if (line[0] == 'q') {
                break;
            }
            UpdateGrid(gridLife, simMode);
            DrawGrid(gridLife);
            
        }
    }
    else {
        double frameRate = (simSpeed - 1) * FrameRateMuliplier * ((simSpeed == 3) ? FrameRateAdjustment : 1);
        cout << "Click and hold the mouse button on the graphics window to end the simulation." << endl;
        while (true) {
            if (MouseButtonIsDown()) {
                break;
            }
            //cout << "Checking frame rate adjustment" << endl;
            UpdateGrid(gridLife, simMode);
            DrawGrid(gridLife);
            Pause(frameRate);
        }
    }
}

void PrintCell(int point) {
    cout << " " << point;
}

void ShowGrid(gridLifeT &gridLife) {
    //gridLife.lifeGrid.mapAll(PrintCell);
    cout << endl;
    for (int i = 0; i < gridLife.size.row; i++) {
        cout << " ";
        for (int j = 0; j < gridLife.size.col; j++) {
            cout << gridLife.lifeGrid[i][j];
            string spacer = ((gridLife.lifeGrid[i][j]) > 9) ? " " : "  ";
            cout << spacer;
        }
        cout << endl;
    }
}

void UpdateGrid(gridLifeT &gridLife, int simMode) {
    gridLifeT gridLife2 = gridLife;
    for (int i = 0; i < gridLife.size.row; i++) {
        for (int j = 0; j < gridLife.size.col; j++) {
            int neighbors = CountNeighbors(gridLife2, i, j, simMode);
            switch (neighbors) {
                case 2:
                    if (gridLife.lifeGrid[i][j] < MaxAge) {
                        gridLife.lifeGrid[i][j] += ((gridLife.lifeGrid[i][j]) != 0) ? 1 : 0;
                    }
                    break;
                case 3:
                    if (gridLife.lifeGrid[i][j] < MaxAge) {
                        gridLife.lifeGrid[i][j] += 1;
                    }
                    break;
                default:
                    gridLife.lifeGrid[i][j] = 0;
                    break;
            }
        }
    }
}

static const int hNumRows = 3;
static const int hNumColumns = 3;

void InitHood(Grid<bool>& hood){
    for (int row = 0; row < hNumRows; row++) {
        for (int col = 0; col < hNumColumns; col++) {
            hood[row][col] = false;
        }
    }
}

void ShowHood(Grid<bool>& hood, int row, int col) {
    cout << endl;
    cout << "  r:c=" << row << ":" << col << endl;
    for (int i = 0; i < hood.numRows(); i++) {
        cout << "    ";
        for (int j = 0; j < hood.numCols(); j++) {
            cout << hood[i][j];
            cout << " ";
        }
        cout << endl;
    }
}

int CountNeighbors(gridLifeT &gridLife, int row, int col, int simMode) {
    int count;
    
    Grid<bool> hood (hNumRows, hNumColumns);
    //InitHood(hood);
    PopulateHood(hood, gridLife, row, col, simMode);
    //ShowHood(hood, row, col);
    count = CountNeighborsInHood(hood);

    return count;
}

void PopulateHood(Grid<bool>& hood, gridLifeT &gridLife, int row, int col, int simMode) {
    
    //cout << endl << " PopulateHood: r:c=" << row << ":" << col << endl;
    
    for (int dRow = -1; dRow <= 1; dRow++) {
        for (int dCol = -1; dCol <= 1; dCol++) {
            hood[dRow+1][dCol+1] = IsDirectionOccupied(gridLife, row, col, dRow, dCol);
            //cout << "  hood[" << dRow+1 << "][" << dCol+1 << "]"  <<  hood[dRow+1][dCol+1] << endl;
        }
    }
}

int CountNeighborsInHood(Grid<bool>& hood) {
    int count = 0;
    for (int row = 0; row < hNumRows; row++) {
        for (int col = 0; col < hNumColumns; col++) {
            if (hood[row][col] > 0 && !(row == 1 && col == 1)) { // Do not count the middle cell, only neighbors.
                count += 1;
                //cout << " CountNeighborsInHood: r:c:count=" << row << ":" << col << ":" << count << endl;
            }
        }
    }
    return count;
}


/**
 * Function: OnBoard
 * (modified from: 08-Velociraptor-Safety.pdf, Stanford Univerity)
 * -----------------
 * OnBoard is a predicate function that returns true if and only if the
 * specified coordinate indexes a legal entry of the lifeGrid.
 */


bool OnBoard(int row, int col, gridSizeT size) {
    return (row >= 0 && row < size.row &&
            col >= 0 && col < size.col);
}

/**
 * Function: IsDirectionOccupied
 * (modified from: 08-Velociraptor-Safety.pdf, Stanford Univerity)
 * -------------------------
 * IsDirectionOccupied decides whether or not a neighbor can be seen
 * by looking from the specified (row, col) coordinate in a particular
 * direction--specified by arguments four and five in the form of exactly
 * what values should be added to (row, col) to look in a specified
 * direction.
 *
 * Assuming that the origin (0,0) coincides with the lower left corner of
 * then board, IsDirectionOccupied must examine the coordinates * (row + dRow, col + dCol), (row + 2 * dRow, col + 2 * dCol)
 * to see if neighbors are adjacent.
 */


bool IsDirectionOccupied(gridLifeT &gridLife, int row, int col, int dRow, int dCol) {
    gridSizeT size = gridLife.size;
    if ((dRow == 0) && (dCol == 0)) return false; // protect against bad call
    row += dRow;
    col += dCol;
    //if (OnBoard(row, col, size)) {
    //    int check = gridLife.lifeGrid[row][col];
        //cout << "   IsDirectionOccupied: gridLife.lifeGrid [" << row << "][" << col << "]" << check;
    //}
    return (OnBoard(row, col, size) && gridLife.lifeGrid[row][col] > 0);
}





