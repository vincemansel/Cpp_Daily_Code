//
//  mazeSolve.h
//  mazeGenSolve
//
//  Created by Vince Mansel on 10/5/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

#ifndef mazeGenSolve_mazeSolve_h
#define mazeGenSolve_mazeSolve_h

#include "maze.h"
#include "genlib.h"
#include "grid.h"

struct cellT {
    bool isFilled;
    bool isExcluded;
};

typedef Grid<cellT> GridOfCells;

void PrintPoint(pointT current);

void Solve(Maze &maze, GridOfCells &cells);

#endif

