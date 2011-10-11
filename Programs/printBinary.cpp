//
//  printBinary.cpp
//  printBinary
//
//  Created by Vince Mansel on 10/11/11.
//  Copyright 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "simpio.h"

void PrintInBinary(int number);

int main() {
    
    while (true) {
        cout << "Enter number in decimal (-1 to quit): ";
        int number = GetInteger();
        if (number == -1) break;
        PrintInBinary(number);
        cout << endl;
    }
    return 0;
}

void PrintInBinary(int number) {
    if (number == 0 || number == 1) {
        cout << number;
        return;
    }
    int current = number % 2;
    PrintInBinary(number / 2);
    cout << current;
}