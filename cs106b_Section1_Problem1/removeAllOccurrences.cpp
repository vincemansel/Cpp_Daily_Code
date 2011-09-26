//
//  removeAllOccurrences.cpp
//  removeAllOccurences
//
//  Created by Vince Mansel on 9/25/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

#include <iostream>
#include "simpio.h"

string CensorString1(string text, string remove)
{
    for (int i = 0; i < remove.length(); i++) {
        int found = 0;
        while ((found = text.find(remove[i],found)) != string::npos) {
            text.erase(found,1);
        }
    }
    return text;
}

void CensorString2(string &text, string remove)
{
    for (int i = 0; i < remove.length(); i++) {
        int found = 0;
        while ((found = text.find(remove[i],found)) != string::npos) {
            text.erase(found,1);
        }
    }
}


int main() {
    //cout << "Enter a long string: ";
    //string text = GetLine();
    //cout << "Enter a shorter string with characters to remove: ";
    //string remove = GetLine();
    
    string text = "This is a very long sentence and will need to be truncated by a good smittly boo. Ugly as it, all the vowels will be lost.";
    string remove = "aeiou";
    
    string outString = CensorString1(text, remove);
    CensorString2(text, remove);
    cout << "Text: " << text << endl;
    cout << "Censor: " << remove << endl;
    cout << "From 1: " << outString << endl;
    cout << "From 2: " << text << endl;
    
    return 0;
    
}
