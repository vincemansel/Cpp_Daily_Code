//
//  listMnemonics.h
//  listCompletions
//
//  Created by Vince Mansel on 10/12/11.
//  Copyright 2011 Wave Ocean Software. All rights reserved.
//

#ifndef listCompletions_listMnemonics_h
#define listCompletions_listMnemonics_h

#include "vector.h"

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

Vector<string> ListMnemonics(string str);

#endif
