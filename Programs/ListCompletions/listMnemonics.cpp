//
//  listMnemonics.cpp
//  listMnemonics
//
//  Created by Vince Mansel on 10/10/11.
//  Copyright 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "simpio.h"
#include "listMnemonics.h"

//void ListMnemonics(string str);

int main1 () {
    
    while (true) {
        cout << "Enter a 3-digit combo (2 through 9) (0 to quit): ";
        string str = GetLine();
        if (str == "0") break;
        ListMnemonics(str);
    }
    
    return 0;
}

/* Snagged from Section17S-SectionSolutions3.pdf */
void RecursiveMnemonics(string prefix, string rest, Vector<string> &prefixes);

/*
 * Function: ListMnemonics
 * Usage: ListMnemonics(str);
 * --------------------------
 * This function lists all of the mnemonics for the string of digits
 * stored in the string str. The correspondence between digits and
 * letters is the same as that on the standard telephone dial. The
 * implementation at this level is a simple wrapper function that
 * provides the arguments necessary for the recursive call.
 */
Vector<string> ListMnemonics(string str)
{
    Vector<string> prefixes;
    RecursiveMnemonics("", str, prefixes);
    return prefixes;
}

string DigitLetters(char ch);

/*
 * Function: RecursiveMnemonics
 * Usage: RecursiveMnemonics(prefix, rest);
 * ----------------------------------------
 * This function does all of the real work for ListMnemonics and
 * implements a more general problem with a recursive solution
 * that is easier to see. The call to RecursiveMnemonics generates
 * all mnemonics for the digits in the string rest prefixed by the
 * mnemonic string in prefix. As the recursion proceeds, the rest
 * string gets shorter and the prefix string gets longer.
 */

void RecursiveMnemonics(string prefix, string rest, Vector<string> &prefixes)
{
    if (rest.length() == 0)
    {
        //cout << prefix << " "; // << endl;
        prefixes.add(prefix);
    }
    else
    {
        string options = DigitLetters(rest[0]);
        for (int i = 0; i < options.length(); i++)
        {
            // Permutations
            RecursiveMnemonics(prefix + options[i], rest.substr(1), prefixes);
        }
        //cout << endl;
    }
}

/*
 * Function: DigitLetters
 * Usage: digits = DigitLetters(ch);
 * ---------------------------------
 * This function returns a string consisting of the legal
 * substitutions for a given digit character. Note that 0 and
 * 1 are handled just by leaving that digit in its position.
 */

string DigitLetters(char ch)
{
    switch (ch) {
        case '0': return ("0");
        case '1': return ("1");
        case '2': return ("ABC");
        case '3': return ("DEF");
        case '4': return ("GHI");
        case '5': return ("JKL");
        case '6': return ("MNO");
        case '7': return ("QPRS");
        case '8': return ("TUV");
        case '9': return ("WXYZ");
        default: Error("Illegal digit");
    }
    return ("0");
}