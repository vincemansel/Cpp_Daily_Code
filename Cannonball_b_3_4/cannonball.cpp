//
//  cannonball.cpp
//  cannonball
//
//  Created by Vince Mansel on 10/10/11.
//  Copyright 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "simpio.h"

int Cannonball(int height);

int main() {
    while (true) {
        cout << "Enter height: ";
        int height = GetInteger();
        if (height == 0) break;
        
        int balls = Cannonball(height);
        
        cout << balls << " cannonballs for height " << height << "." << endl;
    }
    return 0;
}

int Cannonball(int height) {
    if (height == 1) {
        return 1;
    }
    return height * height + Cannonball(height - 1);
}
