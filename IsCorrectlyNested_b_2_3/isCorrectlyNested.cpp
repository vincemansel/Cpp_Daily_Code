//
//  isCorrectlyNested.cpp
//  isCorrectlyNested
//
//  Created by Vince Mansel on 10/2/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "scanner.h"
#include "stack.h"
#include "simpio.h"

bool IsCorrectlyNested(string htmlStr);
bool IsBeginToken(string token);
bool IsEndToken(string token);
bool IsMateOnStack(string stackToken, string token);

int main() {
    
    
    string test = "<html><b><i>CS106 rules!</i></b></html>";
    //string test2 = "<html><b><i></i></b></html>";
    //string test = "<html><b><i>CS106 rules!</b></html>";
    
    //cout << test << endl;
    
    //string test = GetHtml();
    
    cout << test << endl;
    
    cout << "FINISHED FILE. NOW PARSING" << endl;
    
    if (IsCorrectlyNested(test)) {
        cout << "CORRECTLY NESTED." << endl;
    }
    else {
        cout << "TRY AGAIN DUDE!" << endl;
        
    }
    
    return 0;
}


bool IsCorrectlyNested(string htmlStr) {
    bool result = true;
    
    Scanner scanner;
    Stack<string> stack;
    
    scanner.setSpaceOption(Scanner::IgnoreSpaces);
    scanner.setBracketOption(Scanner::ScanBracketsAsTag);
    
    scanner.setInput(htmlStr);
    
    while(scanner.hasMoreTokens()) {
        string token = scanner.nextToken();
        if (IsBeginToken(token)) {
            stack.push(token);
        }
        else if (IsEndToken(token)) {
            if (!(!stack.isEmpty() && IsMateOnStack(stack.pop(),token))) {
                result = false;
            }
        }
    }
    
    if (!stack.isEmpty()) {
        result = false;
    }
    
    return result;
}

bool IsBeginToken(string token) {
    bool result = false;
    if (token.find('<',0) != -1 && token.find('/',1) == -1 && token.find('>',token.size()-1) != 1) {
        result = true;
    }
                
    return result;
}

bool IsEndToken(string token) {
    bool result = false;
    
    if (token.find('<',0) != -1 && token.find('/',1) != -1 && token.find('>',token.size()-1) != 1) {
        result = true;
    }
    
    return result;
}

bool IsMateOnStack(string stackToken, string token) {
    bool result = false;
    
    token.replace(1,1,"");
    
    if (stackToken == token) {
        result = true;
    }
    return result;
}
