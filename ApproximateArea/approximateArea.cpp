//
//  approximateArea.cpp
//  template
//
//  Created by Vince Mansel on 9/25/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include <cmath>

const int Num_rects = 100000;
const double PI = 3.14159;

int main() {
    
    cout << "Enter radius: ";
    double radius = GetReal();
    double area = 0;
    double x = radius / Num_rects;
    for (int i = 0; i < Num_rects; i++) {
        double xC = x * i;
        double h = sqrt(pow(radius,2) - pow(xC,2));
        area += h * x;
    }
    cout << "Approximate area of a quarter Arch of radius " << radius << " is " << area << "." << endl;
    cout << "Area of a quarter Arch from PI of radius " << radius << " is " <<  (PI * pow(radius,2))/4 << "." << endl;
    
    cout << "Approximate Circle is " <<  area * 4 << "." << endl;
    cout << "PI circle is " <<  (PI * pow(radius,2)) << "." << endl;
    
    return 0;
    
}
