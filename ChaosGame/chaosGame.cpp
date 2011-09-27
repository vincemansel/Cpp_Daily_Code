//
//  chaosGame.cpp
//  chaosGame
//
//  Created by Vince Mansel on 9/26/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

#include <iostream>
#include "graphics.h"
#include "extgraph.h"
#include "random.h"
#include "vector.h"

const double SmallRadius = 0.01; // inches
const double LargeRadius = 0.2;
const double FrameRate = 0.000001;   // seconds

struct pointT {
    double x;
    double y;
};

enum colorT {Black, DarkGray, Gray, LightGray, Red, Yellow, Green, Cyan, Blue, Magenta, White};



pointT waitAndGetPoint();
void getAllPoints(pointT &aPoint,pointT &bPoint,pointT &cPoint);
void drawTriangle(pointT aPoint, pointT bPoint, pointT cPoint);
pointT selectRandomVertex(pointT aPoint, pointT bPoint, pointT cPoint);
void drawSmallFilledCircle();
void movePenHalfDistance(pointT currentPoint, pointT selectedPoint);
pointT getCurrentPoint();
void setRandomColor();


int main() {
    
    SetWindowSize(GetFullScreenWidth(), GetFullScreenHeight());
    SetWindowTitle("Chaos Game");
    InitGraphics();
    
    Randomize();
    
    pointT aPoint;
    pointT bPoint;
    pointT cPoint;
    pointT selectedPoint;
    pointT currentPoint;
    
    cout << "Click 3 points (A, B, C) in the graphics window" << endl;
    
    //double GetMouseX() 
    //double GetMouseY()
    //void MovePen(double x,double y)
    //DrawArc(r, 0, 360) 	Draws a circle to the left of the current point.
    
    SetPenColor("Blue");
    getAllPoints(aPoint,bPoint,cPoint);
    drawTriangle(aPoint,bPoint,cPoint);
    selectRandomVertex(aPoint,bPoint,cPoint);
    drawSmallFilledCircle();
    Pause(1.0);
    UpdateDisplay();
    while (!MouseButtonIsDown()) {
        currentPoint = getCurrentPoint();
        selectedPoint = selectRandomVertex(aPoint,bPoint,cPoint);
        movePenHalfDistance(currentPoint,selectedPoint);
        setRandomColor();
        drawSmallFilledCircle();
        //Pause(FrameRate);
        UpdateDisplay();
    }
    
    SetPointSize(48);
    SetPenColor("Red");
    DrawTextString("Bye");
    UpdateDisplay();
    Pause(1.0);
    
    WaitForMouseUp();
    
    ExitGraphics();
    return 0;
}

void getAllPoints(pointT &aPoint,pointT &bPoint,pointT &cPoint) {
    aPoint = waitAndGetPoint();
    bPoint = waitAndGetPoint();
    cPoint = waitAndGetPoint();
}

pointT waitAndGetPoint() {
    
    pointT clickPoint;
    
    WaitForMouseDown();
    
    clickPoint.x = GetMouseX();
    clickPoint.y = GetMouseY();
    
    return clickPoint;
}

void drawTriangle(pointT aPoint, pointT bPoint, pointT cPoint) {
    MovePen(aPoint.x, aPoint.y);
    DrawLine(bPoint.x - aPoint.x, bPoint. y - aPoint.y);
    DrawLine(cPoint.x - bPoint.x, cPoint. y - bPoint.y);
    DrawLine(aPoint.x - cPoint.x, aPoint. y - cPoint.y);
}

pointT selectRandomVertex(pointT aPoint, pointT bPoint, pointT cPoint) {
    int startPoint = RandomInteger(1,3);
    
    switch (startPoint) {
        case 1:
            MovePen(aPoint.x, aPoint.y);
            return aPoint;
        case 2:
            MovePen(bPoint.x, bPoint.y);
            return bPoint;
        case 3:
            MovePen(cPoint.x, cPoint.y);
            return cPoint;
        default:
            Error("Bad switch expression");
            break;
    }
    return aPoint;
}

void drawSmallFilledCircle() {
    StartFilledRegion(1);
    DrawArc(SmallRadius, 0, 360);
    EndFilledRegion();
}

pointT getCurrentPoint() {
    pointT current;
    current.x = GetCurrentX();
    current.y = GetCurrentY();
    //cout << "getCurrentPoint() >> X = " << current.x << " : Y = " << current.y << endl;
    return current;
}

void movePenHalfDistance(pointT currentPoint, pointT selectedPoint) {
    MovePen((currentPoint.x + selectedPoint.x)/2, (currentPoint.y + selectedPoint.y)/2);
}

void setRandomColor() {
    //enum colorT {Black, DarkGray, Gray, LightGray, Red, Yellow, Green, Cyan, Blue, Magenta, White};
    
    colorT color = (colorT) RandomInteger(Black,Magenta);
    switch (color) {
        case Black:
            SetPenColor("Black");
            break;
        case DarkGray:
            SetPenColor("Dark Gray");
            break;
        case Gray:
            SetPenColor("Gray");
            break;
        case LightGray:
            SetPenColor("Light Gray");
            break;
        case Red:
            SetPenColor("Red");
            break;
        case Yellow:
            SetPenColor("Yellow");
            break;
        case Green:
            SetPenColor("Green");
            break;
        case Cyan:
            SetPenColor("Cyan");
            break;
        case Blue:
            SetPenColor("Blue");
            break;
        case Magenta:
            SetPenColor("Magenta");
            break;
            
        default:
            Error("Bad Color choice");
            break;
    }
}
