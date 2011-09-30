//
//  lifeGrid.h
//  life
//
//  Created by Vince Mansel on 9/29/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

/*
 * Defines routines the interact directly with graphics window,
 * and runs the life simulation
 *
 */

#ifndef life_lifeGrid_h
#define life_lifeGrid_h



struct gridSizeT {
    int row;
    int col;
};

struct gridLifeT {
    gridSizeT size;
    Grid<int> lifeGrid;
};

/*
 * Draws a fresh grid unto the graphics window
 */

void DrawGrid(gridLifeT &gridLife);

/*
 * Calculates life for the next step and updates the Grid by reference based on the given simMode.
 */

void UpdateGrid(gridLifeT &gridLife, int simMode);

/* 
 * Handles the various modes of the game and kicks off the life simulation
 */

void RunLifeSim(int simSpeed, int simMode, gridLifeT &gridLife);

#endif
