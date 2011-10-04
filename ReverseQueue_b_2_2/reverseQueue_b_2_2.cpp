//
//  reverseQueue_b_2_2.cpp
//  reverseQueue_b_2_2
//
//  Created by Vince Mansel on 10/2/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

#include <iostream>
#include "queue.h"
#include "stack.h"
#include "simpio.h"

const int Sentinal = -1;

void PrintQ(Queue<int> myQ);
void ReverseQueue(Queue<int> &myQ);

int main() {
    
    Queue<int> myQ;
    
    cout << "Enter ints to queue up (-1 to end): ";
    int num;
    while ((num = GetInteger()) != Sentinal) {
        myQ.enqueue(num);
        cout << "Next? ";
    }
    
    PrintQ(myQ);
    
    cout << "Now Reverse it" << endl;
    
    ReverseQueue(myQ);
    
    PrintQ(myQ);
    
    cout << "END" << endl;
    
    return 0;
}

void PrintQ(Queue<int> myQ) {
     
    while (!myQ.isEmpty()) {
        cout << myQ.dequeue() << endl;
    }
}

void ReverseQueue(Queue<int> &q) {
    Stack<int> s;
    while (!q.isEmpty()) {
        s.push(q.dequeue());
    }
    while (!s.isEmpty()) {
        q.enqueue(s.pop());
    }
}
