//
//  recursiveRulerMaker.cpp
//  recursiveRulerMaker
//
//  Created by Vince Mansel on 10/11/11.
//  Copyright 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "simpio.h"
#include "graphics.h"
#include "extgraph.h"

void DrawRuler(double x, double y, double w, double h);
void DrawOneLine(double x1, double y1, double x2, double y2);

int main() {
    
    SetWindowSize(GetFullScreenWidth(), GetFullScreenHeight());
    SetWindowTitle("Ruler Maker");
    InitGraphics();
    SetPenColor("Black");
    
    while (true) {
        double w;
        double h;
        while (true) {
            cout << "Enter width of ruler in inches: ";
            w = GetReal();
            if (w > 0.0) break;
        }
        while (true) {
            cout << "Enter height of ruler in inches: " ;
            h = GetReal();
            if (h > 0.0) break;
        }
        InitGraphics();
        DrawRuler(1, GetFullScreenHeight()/2, w, h);
        UpdateDisplay();
    }
    
    return 0;
}

void RecDrawRuler(double x, double y, double w, double h) {
    if (h < 0.0625) return; // BASE CASE
    
    double x2 = x + w/2;
    DrawOneLine(x2,y,x2,y+h); // Draw the ticks
    RecDrawRuler(x, y, w/2, h/2);
    RecDrawRuler(x2, y, w/2, h/2);
}

void DrawRuler(double x, double y, double w, double h) {
    DrawOneLine(x, y, x+w, y); // Draw the bottom edge:
                               // x+w compensates for any initial offset
    RecDrawRuler(x, y, w, h);
}

void DrawOneLine(double x1, double y1, double x2, double y2) {
    MovePen(x1, y1);
    DrawLine(x2-x1, y2-y1);
}
