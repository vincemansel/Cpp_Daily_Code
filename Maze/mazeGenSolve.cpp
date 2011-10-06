//
//  mazeGenSolve.cpp
//  mazeGenSolve
//
//  Created by Vince Mansel on 10/4/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

#include <iostream>
#include "maze.h"

#include "grid.h"
#include "simpio.h"
#include "random.h"
#include "mazeSolve.h"

static int GetMazeDimension(string prompt, 
							int minDimension = 10, 
							int maxDimension = 50);
void InitializeCells(GridOfCells &cells);
void PrintCells(GridOfCells &cells);

pointT GetRandomPoint(int numRows, int numCols);
pointT ChooseRandomNeighbor(pointT current, int numRows, int numCols);
int IncludeNeighbor(Maze &maze, GridOfCells &cells, pointT current, pointT neighbor);

int main() {
    Randomize();

    while (true) {
		int numRows = GetMazeDimension("What should the X dimension of your maze be [0 to exit]? ");
		if (numRows == 0) break;
        int numCols = GetMazeDimension("What should the Y dimension of your maze be [0 to exit]? ");
		if (numCols == 0) break;
		cout << "Here's where we'll generate a maze before your very eyes." << endl;
        
        Maze maze = Maze(numRows, numCols, true);
        maze.draw();
        
        GridOfCells cells(numRows, numCols);
        InitializeCells(cells);
        
        pointT current = GetRandomPoint(numRows,numCols);
        
        int includeCount = 0;
        while (includeCount < numRows * numCols) {
            pointT neighbor = ChooseRandomNeighbor(current,numRows,numCols);
            includeCount += IncludeNeighbor(maze,cells, current, neighbor);
            current = neighbor;
            
        }
        maze.draw();
        //PrintCells(cells);
        Solve(maze,cells);
    }
    
    return 0;
}

/**
 * Provided by and  Last modified: jcain on 9/26/09.
 *
 * Prompts the user so that he or she will supply an
 * integer in the range [minDimension, maxDimension].
 *
 * @param string prompt the text that should be printed to make it
 *        clear to the user that an integer should be entered.
 * @param int minDimension the lowest number the GetMazeDimension
 *        function will accept as in range.
 * @param int maxDimension the highest number the GetMazeDimension
 *        will accept as in range.
 * @return an integer in the range [minDimension, maxDimension].
 */
static int GetMazeDimension(string prompt, 
							int minDimension, 
							int maxDimension)
{
	while (true) {
		cout << prompt;
		int response = GetInteger();
		if (response == 0 || (response >= minDimension && response <= maxDimension))
			return response;
		cout << "Please enter a number between "
        << minDimension << " and " 
        << maxDimension << ", inclusive." << endl;
	}
}


void InitOneCell(cellT &cell) {
    cell.isFilled = false;
    cell.isExcluded = true;
}

void InitializeCells(GridOfCells &cells) {
    for (int i = 0; i < cells.numRows(); i++) {
        for (int j = 0; j < cells.numCols(); j++) {
            cells[i][j].isFilled = false;
            cells[i][j].isExcluded = true;
        }
    }
}

void PrintOneCell(cellT cell) {
    cout << cell.isFilled << ":" << cell.isExcluded << endl;
}

void PrintCells(GridOfCells &cells) {
    cells.mapAll(PrintOneCell);
}



pointT GetRandomPoint(int numRows, int numCols) {
    pointT p;
    p.row = RandomInteger(0, numRows);
    p.col = RandomInteger(0, numCols);
    return p;
}

bool IsValid(int row, int col, int nRows, int nCols) {
    return (row >= 0 && row < nRows &&
            col >= 0 && col < nCols);
}

pointT GetNewPoint(pointT current) {
    int choice = RandomInteger(0, 3);
    switch (choice) {
        case 0:
            current.col -= 1;
            break;
        case 1:
            current.col += 1;
            break;
        case 2:
            current.row -= 1;
            break;
        case 3:
            current.row += 1;
            break;
            
        default:
            break;
    }
    return current;
}

pointT ChooseRandomNeighbor(pointT current, int numRows, int numCols) {
    pointT neighbor;
    while (true) {
        neighbor = GetNewPoint(current);
        if (IsValid(neighbor.row, neighbor.col, numRows, numCols)) {
            break;
        }
    }
    return neighbor;
}

int IncludeNeighbor(Maze &maze, GridOfCells &cells, pointT current, pointT neighbor) {
    int counter = 0;
    if (cells[neighbor.row][neighbor.col].isExcluded) {
        maze.setWall(current, neighbor, false);
        cells[neighbor.row][neighbor.col].isExcluded = false;
        counter += 1;
    }
    return counter;
}
