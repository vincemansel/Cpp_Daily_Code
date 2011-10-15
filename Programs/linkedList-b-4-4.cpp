//
//  linkedList-b-4-4.cpp
//  linkedList-b-4-4
//
//  Created by Vince Mansel on 10/14/11.
//  Copyright 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "simpio.h"
#include "vector.h"

struct CellT {
    CellT *next;
    int value;
};

CellT * ConvertToListR(Vector<int> &vector);
CellT * ConvertToListI(Vector<int> vector);
void PrintLinkedList(CellT * list);
void Deallocate(CellT *list);
int SumList(CellT *list);

int main () {
    
    Vector<int> vector;
    CellT * myLinkedList = NULL;
    
    while (true) {
        cout << "Give me a list of numbers (-1 to quit): " << endl;
        int number;
        while (true) {
            cout << "Enter a number (-1 to quit): ";
            number = GetInteger();
            if (number == -1) break;
            vector.add(number);
        }
        //myLinkedList = ConvertToListR(vector);
        myLinkedList = ConvertToListR(vector);
        PrintLinkedList(myLinkedList);
        cout << SumList(myLinkedList) << endl;
        //vector.clear();
        Deallocate(myLinkedList);
    }
    
    return 0;
}

int SumList(CellT *list) {
    if (list == NULL) return 0;
    return (list->next == NULL) ? list->value : list->value + SumList(list->next) ;
}

CellT * ConvertToListRec(Vector<int> &vector, int index) {
    CellT * list = new CellT;
    
    if (index == vector.size()) return NULL;
    
    list->value = vector[index];
    list->next = ConvertToListRec(vector,index+1);

    return list;
}

CellT * ConvertToListR(Vector<int> &vector) {
    
    if (vector.isEmpty()) { // First time only, better to check before calling first time.
        return NULL;
    }
    return ConvertToListRec(vector,0);
}

CellT * ConvertToListI(Vector<int> vector) {
    CellT * list = new CellT;
    CellT * tlist = list;
    
    Vector<int>::Iterator itr = vector.iterator();
    
    while (!vector.isEmpty()) {
        tlist->value = itr.next();
        if (itr.hasNext()) {
            tlist->next = new CellT;
            tlist = tlist->next;
        }
        else {
            tlist->next = NULL;
            break;
        }
    }
    if (vector.isEmpty()) list = NULL;
    
    return list;
}


void PrintLinkedList(CellT * list) {
    if (list == NULL) {
        return;
    }
    cout << list->value << endl;
    PrintLinkedList(list->next);
}


void Deallocate(CellT *list)
{
    if (list != NULL) {
        Deallocate(list->next);
        delete list;
    }
}


