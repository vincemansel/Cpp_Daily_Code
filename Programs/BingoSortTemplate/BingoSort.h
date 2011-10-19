//
//  BingoSort.h
//  bingoSortTemplateTest
//
//  Created by Vince Mansel on 10/18/11.
//  Copyright (c) 2011 Wave Ocean Software. All rights reserved.
//

#ifndef bingoSortTemplateTest_BingoSort_h
#define bingoSortTemplateTest_BingoSort_h

#include "cmpfn.h"
#include "vector.h"

template <typename Type>
void BingoSort(Vector<Type> &v, double d, int (cmpFn)(Type, Type) = OperatorCmp);

#include "BingoSort.cpp"

#endif
