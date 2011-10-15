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

Vector<int> GetVector(string message);
CellT * ConvertToListR(Vector<int> &vector);
CellT * ConvertToListI(Vector<int> vector);
void PrintLinkedList(CellT * list);
void Deallocate(CellT *list);
int SumList(CellT *list);
void AppendList(CellT * &list1, CellT * &list2);
void Append(CellT *& first, CellT* second);

int main () {
    
    while (true) {
        CellT * list1 = NULL;
        CellT * list2 = NULL;
        
        Vector<int> vector1 = GetVector("Give me a 1st list of numbers (-1 to quit)");
        list1 = ConvertToListR(vector1);
        PrintLinkedList(list1);
        cout << SumList(list1) << endl;
        
        Vector<int> vector2 = GetVector("Give me a 2nd list of numbers (-1 to quit)");
        list2 = ConvertToListR(vector2);
        PrintLinkedList(list2);
        cout << SumList(list2) << endl;
        
        cout << "Appending the list now..." << endl;
        //AppendList(list1, list2);
        Append(list1, list2);
        PrintLinkedList(list1);
        cout << SumList(list1) << endl;
        
        vector1.clear();
        vector2.clear();
        Deallocate(list1);
        //Deallocate(list2);
        
        cout << "******************** OK WE ARE DONE **********************" << endl;
    }
    
    return 0;
}

Vector<int> GetVector(string message) {
    Vector<int> vector;
    cout << message << endl;
    int number;
    while (true) {
        cout << "Enter a number (-1 to quit): ";
        number = GetInteger();
        if (number == -1) break;
        vector.add(number);
    } 
    
    return vector;
}

void Append(CellT *& first, CellT * second)
{
    if (first == NULL)
    {
        first = second;
    }
    else
    {
        Append(first->next, second);
    }
}

void AppendListRec(CellT * &list1, CellT * &list2) {
    
    if (list1->next == NULL) {
        list1->next = list2;
    }
    else {
        list1 = list1->next;
        AppendListRec(list1, list2);
    }
}

void AppendList(CellT * &list1, CellT * &list2) {
    
    if (list1 == NULL) {
        list1 = list2;
        return;
    }

    CellT * listHead = list1;
    AppendListRec(listHead, list2);
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


