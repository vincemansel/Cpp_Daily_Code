//
//  soundexCoder.cpp
//  soundexCoder
//
//  Created by Vince Mansel on 9/27/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

/*
 * Convert a surname to its soundex code
 */

#include <iostream>
#include "simpio.h"
#include "vector.h"

void StoreSoundex(Vector<string> &codex);
string GetSoundexCode(string name, Vector<string> &codex);

const int MaxCodeLength = 4;

int main() {
    
    Vector<string> codex;
    StoreSoundex(codex);
        
    while (true) {
        cout << "Enter surname (RETURN to quit): ";
        string name = GetLine();
        if (name == "") {
            break;
        }
        
        string code = GetSoundexCode(name, codex);
        
        cout << "Soundex code for " << name << " is " << code << endl;
        
        
    }
    
    return 0;

}

void StoreSoundex(Vector<string> &codex) {
    codex.add("AEIOUHWY");
    codex.add("BFPV");
    codex.add("CGJKQSXZ");
    codex.add("DT");
    codex.add("MN");
    codex.add("L");
    codex.add("R");
}

string GetSoundexCode(string name, Vector<string> &codex) {
    
    string code = "";
    
    for (int i = 0; i < name.length(); i++) {
        name[i] = toupper(name[i]);
        if (i == 0) {
            code += name[i];
        }
        else {
            for (int j = 0; j < codex.size(); j++) {
                if (codex[j].find(name[i]) != -1) {
                    if (j != 0 ) { // Take out 0 only 
                        code += IntegerToString(j);
                    }
                }
            }
        }
    }
    
    string temp;
    for (int i = 1; i < code.length(); i++) {  // Check for consecutive numbers
        if (code[i] != code[i-1]) {
            temp += code[i];
        }
    }
    
    code = code[0] + temp;
    
    if (code.length() > MaxCodeLength) {        // Truncate to 4 characters
        code = code.substr(0,MaxCodeLength);
    }
    else if (code.length() < MaxCodeLength) {
        while (code.length() < MaxCodeLength) { // Pad with zeros up to 4 characters
            code += IntegerToString(0);
        }
    }
    
    //cout << name << endl;

    return code;
}