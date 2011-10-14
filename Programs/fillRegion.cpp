//
//  fillRegion.cpp
//  fillRegion
//
//  Created by Vince Mansel on 10/13/11.
//  Copyright 2011 Wave Ocean Software. All rights reserved.
//

/*
 * This program draws a simple house and waits for the user to click the mouse.
 * The program then fills the region inclose by the house with a color.
 */

#include <iostream>
#include "simpio.h"
#include "graphics.h"
#include "extgraph.h"
#include "grid.h"

enum pixelStateT { White, Black };

struct pointT {
    int row, col;
};

const int MM = 1;
const int HouseWidthC = 60*MM;
const int HouseHeightC = 60*MM;
const int RoofHeightC = 30*MM;
const int WindowWidth = 10*MM;
const int WindowHeight = 10*MM;
const int DoorWidth = 20*MM;
const int DoorHeight = 35*MM;

void InitializeGrid(Grid<pixelStateT> &screen);
void DrawHouse(Grid<pixelStateT> &screen);
pointT GetMousePosition();
void FillRegion(pointT pt, Grid<pixelStateT> &screen, int &counter);

int main() {
    double screenWidth = GetFullScreenWidth();
    double screenHeight = GetFullScreenHeight();
    SetWindowSize(screenWidth, screenHeight);
    SetWindowTitle("Fill Region Demo");
    InitGraphics();
    SetPenColor("Black");
    
    double xRes = GetXResolution(); 
	double yRes = GetYResolution();
    double xWin = GetWindowWidth();
    double yWin = GetWindowHeight();
    int xPix = xRes * xWin;
    int yPix = yRes * yWin;

    cout << "Resolution is " << xRes << "x" << yRes << " pixels per square inch." << endl;
    cout << "Window dimensions are " << xWin << "x" << yWin << " inches." << endl;
    cout << "Screen is " << screenWidth << "x" << screenHeight << "." << endl;
    cout << "Pixel dimensions are " << xPix << "x" << yPix << " pixels." << endl;
    cout << "Coordinate System: " << GetCoordinateSystem() << endl;
    
    Grid<pixelStateT> screen (xPix, yPix);
    InitializeGrid(screen);

    cout << "Grid is " << screen.numRows() << "x" << screen.numCols() << "." << endl;
    
    DrawHouse(screen);
    pointT point = GetMousePosition();
    SetPenColor("Green");
    
    int counter = 0;
    FillRegion(point, screen, counter);
    
    cout << "Recursive calls to FilledRegion = " << counter << endl;
    
    return 0;
}

void InitPixelState(pixelStateT px) {
    px = White;
}

void InitializeGrid(Grid<pixelStateT> &screen) {
    screen.mapAll(InitPixelState);
}


void DrawPointG(pointT pt, Grid<pixelStateT> &screen) {
    double xRes = GetXResolution(); 
	double yRes = GetYResolution();
    screen[pt.row][pt.col] = Black;
    MovePen(pt.row/xRes, pt.col/yRes);
    DrawLine(0,0);
}

bool OnGrid(pointT pt, Grid<pixelStateT> &screen) {
    if (pt.row >= screen.numRows() || pt.col >= screen.numCols())
        return false; // BASE CASE
    if (pt.row < 0 || pt.col < 0)
        return false; // BASE CASE
    return true;
}

bool isWhite(pointT pt, Grid<pixelStateT> &screen) {
    if (screen[pt.row][pt.col] == White)
        return true;
    return false;
}
    
void FillRegion(pointT pt, Grid<pixelStateT> &screen, int &counter) {
    
    counter++;
    if (!OnGrid(pt,screen))
        return;
    if (screen[pt.row][pt.col] == Black)
        return; // BASE CASE
    
    DrawPointG(pt,screen);
    
    // Recursively fill neighbor pixels in four directions
    
    pointT np;
    np.row = pt.row + 1;
    np.col = pt.col;
    if (OnGrid(np,screen) && isWhite(np,screen))
        FillRegion(np, screen, counter);
    
    np.row = pt.row - 1;
    if (OnGrid(np,screen) && isWhite(np,screen))
        FillRegion(np, screen, counter);
    
    np.row = pt.row;
    np.col = pt.col + 1;
    if (OnGrid(np,screen) && isWhite(np,screen))
        FillRegion(np, screen, counter);
    
    np.col = pt.col - 1;
    if (OnGrid(np,screen) && isWhite(np,screen))
        FillRegion(np, screen, counter);
}

void UpdateScreen(Grid<pixelStateT> &screen, int x1, int y1, int x2, int y2) {
    
    if (y1 == y2) { // Assumes Left to Right
        for (int i = x1; i <= x2; i++) {
            screen[i][y1] = Black;
            //cout << "US1:" << i << ":" << y1 << endl;
        }
    }
    else if (x1 == x2) { // Assumes Bottom to Top
        for (int j = y1; j <= y2; j++) {
            screen[x1][j] = Black;
            //cout << "US2:" << x1 << ":" << j << endl;
        }
    }
    else if (abs(x2-x1) >= abs(y2-y1)) {
        int xSlope = abs((x2-x1)/(y2-y1));
        if ((x2 > x1) && (y2 > y1)) {
            int j = y1;
            for (int i = x1; i <= x2; i++) {
                //cout << "US3:" << i << ":" << j << endl;
                screen[i][j] = Black;
                if (i % xSlope == 0) j++;
            }
        }
        
        if ((x2 < x1) && (y2 < y1)) {
            int j = y2;
            for (int i = x2; i <= x1; i++) {
                //cout << "US4:" << i << ":" << j << endl;
                screen[i][j] = Black;
                if (i % xSlope == 0) j++;
            }
        }
        
        if ((x2 > x1) && (y2 < y1)) {
            int j = y1;
            for (int i = x1; i <= x2; i++) {
                //cout << "US5:" << i << ":" << j << endl;
                screen[i][j] = Black;
                if (i % xSlope == 0) j--;
            }
        }
        
        if ((x2 < x1) && (y2 > y1)) {
            int j = y2;
            for (int i = x2; i <= x1; i++) {
                //cout << "US6:" << i << ":" << j << endl;
                screen[i][j] = Black;
                if (i % xSlope == 0) j--;
            }
        }
    }
    else if (abs(y2-y1) > abs(x2-x1)) {
        int ySlope = abs((y2-y1)/(x2-x1));
        if ((y2 > y1) && (x2 > x1)) {
            int i = x1;
            for (int j = y1; j <= y2; j++) {
                //cout << "US7:" << i << ":" << j << endl;
                screen[i][j] = Black;
                if (i % ySlope == 0) i++;
            }
        }
        
        if ((y2 < y1) && (x2 < x1)) {
            int i = x2;
            for (int j = y2; j <= y1; j++) {
                //cout << "US8:" << i << ":" << j << endl;
                screen[i][j] = Black;
                if (i % ySlope == 0) i++;
            }
        }
        
        if ((y2 > y1) && (x2 < x1)) {
            int i = x2;
            for (int j = y1; j <= y2; j++) {
                //cout << "US9:" << i << ":" << j << endl;
                screen[i][j] = Black;
                if (i % ySlope == 0) i--;
            }
        }
        
        if ((y2 < y1) && (x2 > x1)) {
            int i = x1;
            for (int j = y2; j <= y1; j++) {
                //cout << "US10:" << i << ":" << j << endl;
                screen[i][j] = Black;
                if (i % ySlope == 0) i--;
            }
        }
    }
}

void DrawLineG(Grid<pixelStateT> &screen, int x1, int y1, int x2, int y2) {
    double xRes = GetXResolution(); 
	double yRes = GetYResolution();
    MovePen(x1/xRes, y1/yRes);
    DrawLine((x2-x1)/xRes, (y2-y1)/yRes);
    UpdateScreen(screen, x1, y1, x2, y2);
}

void DrawBox(Grid<pixelStateT> &screen, int x1, int y1, int width, int height) {
    DrawLineG(screen, x1, y1, x1+width, y1);
    DrawLineG(screen, x1, y1, x1, y1+height);
    DrawLineG(screen, x1+width, y1, x1+width, y1+height);
    DrawLineG(screen, x1, y1+height, x1+width, y1+height);
}


void DrawHouse(Grid<pixelStateT> &screen) {
    int rows = screen.numRows();
    int cols = screen.numCols();
    //double xRes = GetXResolution(); 
	//double yRes = GetYResolution();
    
    // Lower Left
    int startX = rows/2 - HouseWidthC/2;
    int startY = cols/2 - (HouseHeightC + RoofHeightC)/2;
    
    cout << "Start point is " << startX << ":" << startY << endl;
    
    // Draw Foundation
    DrawLineG(screen, startX, startY, startX+HouseWidthC, startY);
    // Draw Left Wall
    DrawLineG(screen, startX, startY, startX, startY+HouseHeightC);
    // Draw Right Wall
    DrawLineG(screen, startX+HouseWidthC, startY, startX+HouseWidthC, startY+HouseHeightC);
    // Draw Roof
    DrawLineG(screen, startX, startY+HouseHeightC, startX+HouseWidthC/2, startY+HouseHeightC+RoofHeightC);
    DrawLineG(screen, startX+HouseWidthC, startY+HouseHeightC, startX+HouseWidthC/2, startY+HouseHeightC+RoofHeightC);
    // Draw Left Window
    DrawBox(screen, startX+WindowWidth, startY+4*WindowWidth, WindowWidth, WindowHeight);
    // Draw Right Window
    DrawBox(screen, startX+4*WindowWidth, startY+4*WindowWidth, WindowWidth, WindowHeight);
    // Draw Door
    DrawBox(screen, startX+2*WindowWidth, startY, DoorWidth, DoorHeight);
    
    UpdateDisplay();
}

pointT GetMousePosition() {
    pointT point;
    cout << "Click the mouse inside the house." << endl;
    WaitForMouseUp();
    point.row = GetMouseX() * GetXResolution();
    point.col = GetMouseY() * GetYResolution();
    cout << "Point is " << point.row << ":" << point.col << endl;
    cout << "Thank you!" << endl;
    return point;
}

