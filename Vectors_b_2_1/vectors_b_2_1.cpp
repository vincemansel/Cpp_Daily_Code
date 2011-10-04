//
//  vectors_b_2_1.cpp
//  vectors_b_2_1
//
//  Created by Vince Mansel on 10/2/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

#include <iostream>
#include "simpio.h"
#include "vector.h"
#include "strutils.h"

struct eMailMsg {
    Vector <string> to; // i.e. "professor@stanford.edu"
    string from; // i.e. "student@stanford.edu"
    string message; // body of message
    string subject; // i.e. "CS106 Rocks!"
    int date; // date email was sent
    int time; // time email was sent
};


void GetEmail(int i, Vector<eMailMsg> &emailStore);
void RemoveSpam(Vector<eMailMsg> &emailStore);
void PrintEmail(eMailMsg email);

int main() {
    
    Vector<eMailMsg> emailStore;
    
    eMailMsg m1, m2, m3;
    
    cout << "Enter number of messages: ";
    int num = GetInteger();
    
    for (int i = 0; i < num; i++) {
        GetEmail(i, emailStore);
    }
    
    cout << endl << endl;
    emailStore.mapAll(PrintEmail);
    
    RemoveSpam(emailStore);
    
    cout << endl << endl;
    emailStore.mapAll(PrintEmail);
    
    cout << "We are done!" << endl;
    
    return 0;
}

void GetEmail(int i, Vector<eMailMsg> &emailStore) {
    eMailMsg email;
    cout << "Email subject: ";
    email.subject = GetLine();
    email.to.add ("prof" + IntegerToString(i) + "@stanford.edu");
    email.to.add ("admin" + IntegerToString(i * 100) + "@stanford.edu");
    email.from = "stud" + IntegerToString(i) + "@stanford.edu";
    email.message = "blah blah";
    email.date = i;
    email.time = 10 * i;
    emailStore.add(email);
}

void RemoveSpam(Vector<eMailMsg> &emailStore) {
    
    cout << "RemoveSpam: IN" << endl;
    
    int size = emailStore.size();
    for (int i = size - 1; i >= 0; i--) {
        PrintEmail(emailStore.getAt(i));
        if (emailStore.getAt(i).subject.compare("SPAM") == 0) {
            cout << "Removing " << i << endl;
            emailStore.removeAt(i);
        }
    }
    
    cout << "RemoveSpam: OUT" << endl;

}

void PrintTo(string to) {
    
    cout << to << " || " ;
    
}
void PrintEmail(eMailMsg email) { 
    cout << email.subject << " : ";
    email.to.mapAll(PrintTo);
    cout << " : " << email.from << " : " <<  email.message   << " : " <<   email.date  << " : " <<  email.time   << endl;
}
