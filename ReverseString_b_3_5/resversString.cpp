//
//  resversString.cpp
//  reverseString
//
//  Created by Vince Mansel on 10/10/11.
//  Copyright 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "simpio.h"

string ReverseStringI(string str);

string ReverseStringR(string str);

int main () {
    
    while (true) {
        cout << "Enter a short string to Reverse (0 to quit): ";
        string str = GetLine();
        if (str == "0") break;
        cout << "Itertive: " << ReverseStringI(str) << endl;
        cout << "Recursive: " << ReverseStringR(str) << endl;
    }
    
    return 0;
}

string ReverseStringI(string str) {
    string result;
    for (int i = str.length() - 1; i >= 0; i--)
        result += str[i];
    return result;
}

string ReverseStringR(string str) {
    string result;
    int len = str.length();
    if (len == 0)
        return "";
    return str[len-1] + ReverseStringR(str.substr(0,len-1));
}
