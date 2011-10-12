//
//  listCompletions.cpp
//  listCompletions
//
//  Created by Vince Mansel on 10/12/11.
//  Copyright 2011 Wave Ocean Software. All rights reserved.
//

/*
 * This program prints all words from the lexicon that can be formed
 * by extending the given digit sequence.
 */ 

#include <iostream>
#include "simpio.h"
#include "genlib.h"
#include "listMnemonics.h"
#include "lexicon.h"

const string Alphabet = "abcdefghijklnmopqrstuvwxyz";

void ListCompletions(string digits, Lexicon & lex);
void RecursiveListCompletions(Lexicon & lex, string prefix, string rest);

int main() {
    
    Lexicon lex("lexicon.dat");
        
    while (true) {
        cout << "Enter a string of digits (2 through 9) (0 to quit): ";
        string digits = GetLine();
        if (digits == "0") break;
        ListCompletions(digits, lex);
    }
        
    return 0;
}

/*
 * Function: ListCompletions
 * Usage: ListCompletions(digits, lexicon);
 * --------------------------
 * This function prints all words from the lexicon that can be formed
 * by extending the given digit sequence.
 */ 

void ListCompletions(string digits, Lexicon & lex) {
    
    cout << lex.size() << endl;
    Vector<string> prefixes;
    prefixes = ListMnemonics(digits);
    
    Vector<string>::Iterator itr = prefixes.iterator();
    
    while (itr.hasNext()) {
        string prefix = itr.next();
        if (lex.containsPrefix(prefix)) {
            RecursiveListCompletions(lex, prefix, Alphabet);
        }
    }
}

void RecursiveListCompletions(Lexicon & lex, string prefix, string rest) {
    if (lex.containsWord(prefix))
    {
        cout << prefix << endl;
    }
    
    for (int i = 0; i < rest.length(); i++)
    {
        // Permutations
        if (lex.containsPrefix(prefix + rest[i])) {
            RecursiveListCompletions(lex, prefix + rest[i], Alphabet);
        }
    }
}
