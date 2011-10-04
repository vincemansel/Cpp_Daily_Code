//
//  minesweepGrid.cpp
//  minesweeperGrid
//
//  Created by Vince Mansel on 10/3/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "grid.h"
#include "scanner.h"
#include "simpio.h"

void InitializeGrid(Grid<bool> & bGrid);
Grid<bool> LoadGrid(ifstream &if1);
void ResizeGrid(Grid<bool> &bGrid, int numRows, int numCols);
void GetFile(ifstream &if1);
void PrintBGrid(Grid<bool> & eGrid);
void PrintCGrid(Grid<int> & eGrid);
Grid<int> MakeGridOfCounts(Grid<bool> & bombLocations);
int CheckForNeighbors(Grid<bool> bGrid, int row, int col);
int IsDirectionOccupied(Grid<bool> bGrid, int row, int col, int dRow, int dCol);

int main() {
    
    cout << "Minesweeper: Make Grid of Counts" << endl << endl;
    
    //cout << "Main: IN" << endl;
    
    Grid<bool> bGrid;
    InitializeGrid(bGrid);
    PrintBGrid(bGrid);
    cout << endl;
    Grid<int> countGrid = MakeGridOfCounts(bGrid);
    PrintCGrid(countGrid);
    
    //cout << "Main: OUT" << endl;
    
    return 0;
}

void InitializeGrid(Grid<bool> & bGrid) {
    //cout << " InitializeGrid: IN" << endl;
    ifstream input;
    GetFile(input);
    bGrid = LoadGrid(input);
    //cout << " InitializeGrid: OUT" << endl;
}

/*
 * LoadGrid streams in a file formated with i rows and j columns.
 * Each "cell" is formatted with a "T" or "F".
 * The boolean grid is started as 1x1, is resized for each new column and is adjusted back after first time.
 * After that, only rows are re-sized. The alternative is to but the # of row and colunms at the beginning
 * of the initialization file, an easier implementation.
 */

Grid<bool> LoadGrid(ifstream &if1) {
    //cout << "  LoadGrid: IN" << endl;
    Scanner scanner;
    scanner.setSpaceOption(Scanner::IgnoreSpaces);
    Grid<bool> bGrid(1,1); // Kluggy, but needed to start with something for first row only resize.
    bool firstTime = true;
    
    while (true) {
        string line;
        getline(if1, line);
        if (if1.fail()) {
            break;
        }
        scanner.setInput(line);
        //cout << "Before Re-sizing ..." << endl;
        //PrintBGrid(bGrid);
        ResizeGrid(bGrid,bGrid.numRows()+1,bGrid.numCols());
        //cout << "After Re-sizing ..." << endl;
        //PrintBGrid(bGrid);
        int nCols = 0;
        while (scanner.hasMoreTokens()) {
            if (firstTime) {
                ResizeGrid(bGrid,bGrid.numRows(),bGrid.numCols()+1);
                bool cell = true;
                if (scanner.nextToken() == "F") {
                    cell = false;
                }
                bGrid[bGrid.numRows()-2][bGrid.numCols()-2] = cell; // special case: extra row and colunm tack on earlier (1,1) safety.
                //cout << "FT:" << bGrid.numRows()-2 << ":" << bGrid.numCols()-2 << "=" << cell << endl;
                //PrintBGrid(bGrid);
                
            }
            else {
                bool cell = true;
                if (scanner.nextToken() == "F") {
                    cell = false;
                }
                //cout << "NT:" << bGrid.numRows()-1 << ":" << nCols << "=" << cell << endl;
                bGrid[bGrid.numRows()-1][nCols++] = cell;
                //PrintBGrid(bGrid);
            }
        }
        if (firstTime) {
            ResizeGrid(bGrid,bGrid.numRows()-1,bGrid.numCols()-1);
            firstTime = false;
        }
        
    }
    //cout << "Leaving ..." << endl;
    //PrintBGrid(bGrid);
    //cout << "  LoadGrid: OUT" << endl;
    return bGrid;
}

/*
 * ReSizeGrid is a utility function that insures that the intended contents
 * of the grid to be resized is properly saved. In case of a negative resize,
 * the affected rows or column are intentionally lost.
 *
 * Resizing can happen +/- rows and/or +/-
 */

void ResizeGrid(Grid<bool> &bGrid, int numRows, int numCols) {
    //cout << "Resize: IN" << endl;
    Grid<bool> tGrid = bGrid;
    bGrid.resize(numRows ,numCols);
    
    //cout << "tgrid" << endl;
    //PrintBGrid(tGrid);
    //cout << "bgrid" << endl;
    //PrintBGrid(bGrid);
    
    if (bGrid.numCols() < tGrid.numCols())
        numCols = bGrid.numCols();
    else
        numCols = tGrid.numCols();
    
    if (bGrid.numRows() < tGrid.numRows())
        numRows = bGrid.numRows();
    else
        numRows = tGrid.numRows();
    
    
    for (int i = 0; i < numRows; i++)
        for (int j = 0; j < numCols; j++) {
            //cout << "RS:" << i << ":" << j << "=";
            bGrid[i][j] = tGrid[i][j];
            //cout << tGrid[i][j] << endl;
        }
    //cout << "Resize: OUT" << endl;
}

void GetFile(ifstream &if1) {
    //cout << "  GetFile: IN" << endl;
    ifstream input;
    
    while (true) {
        cout << "Input file: ";
        string filename = GetLine();
        //string filename = "13x12";
        if1.open(filename.c_str());
        if (if1.fail()) {
            cout << "Error: can not open " << filename << ". Try again..." << endl;
            if1.clear();
        }
        else {
            break;
        }
    }
    //cout << "  GetFile: OUT" << endl;
}

void PrintBGrid(Grid<bool> & eGrid) {
    for (int i = 0; i < eGrid.numRows(); i++) {
        for (int j = 0; j < eGrid.numCols(); j++) {
            bool cell = eGrid[i][j];
            if (cell) {
                cout << "T" << " ";
            }
            else {
                cout << "F" << " ";
            }
                
        }
        cout << endl;
    }
}
    
void PrintCGrid(Grid<int> & eGrid) {
    for (int i = 0; i < eGrid.numRows(); i++) {
        for (int j = 0; j < eGrid.numCols(); j++) {
            cout << eGrid[i][j] << " ";
        }
        cout << endl;
    }
}
    
Grid<int> MakeGridOfCounts(Grid<bool> & bGrid) {
    Grid<int> cGrid (bGrid.numRows(),bGrid.numCols());
    for (int i = 0; i < cGrid.numRows(); i++)
        for (int j = 0; j < cGrid.numCols(); j++)
            cGrid[i][j] = CheckForNeighbors(bGrid, i, j);
    return cGrid;
}

int CheckForNeighbors(Grid<bool> bGrid, int row, int col) {
    int count = 0;
    
    for (int dRow = -1; dRow <= 1; dRow++) {
        for (int dCol = -1; dCol <= 1; dCol++) {
            count += IsDirectionOccupied(bGrid, row, col, dRow, dCol);
        }
    }
    return count + ((int) bGrid[row][col]) % 2;
}

/*
 * Function: OnBoard
 * (modified from: 08-Velociraptor-Safety.pdf, Stanford Univerity)
 * -----------------
 * OnBoard is a predicate function that returns true if and only if the
 * specified coordinate indexes a legal entry of the Grid.
 */

bool OnBoard(int row, int col, int nRows, int nCols) {
    return (row >= 0 && row < nRows &&
            col >= 0 && col < nCols);
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

int IsDirectionOccupied(Grid<bool> bGrid, int row, int col, int dRow, int dCol) {
    if ((dRow == 0) && (dCol == 0)) return false; // protect against bad call
    row += dRow;
    col += dCol;
    return (OnBoard(row, col,bGrid.numRows(), bGrid.numCols()) && bGrid[row][col]);

}