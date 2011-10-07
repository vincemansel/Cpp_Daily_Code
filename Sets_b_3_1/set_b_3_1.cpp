//
//  set_b_3_1.cpp
//  sets_b_3_1
//
//  Created by Vince Mansel on 10/6/11.
//  Copyright 2011 Wave Ocean Networks. All rights reserved.
//

#include <iostream>
#include "simpio.h"
#include "set.h"

struct entryT {
    string firstName;
    string lastName;
    string phoneNumber;
};

int OperatorCmp(entryT one, entryT two) {
	if (one.lastName == two.lastName) {
        if (one.firstName == two.firstName) {
            if (one.phoneNumber == two.phoneNumber) {
                return 0;
            }
            if (one.phoneNumber < two.phoneNumber) return -1;
            return 1;
        }
        if (one.firstName < two.firstName) return -1;
        return 1;
    }
	if (one.lastName < two.lastName) return -1;
	return 1;
}

void PrintFriend(entryT myFriend) {
    cout << myFriend.firstName << " " << myFriend.lastName << " " << myFriend.phoneNumber << endl;
}

int main() {
    
    Set<entryT> friends(OperatorCmp);
    
    entryT myFriend;
    myFriend.firstName = "Bill";
    myFriend.lastName = "Jones";
    myFriend.phoneNumber = "4567";
    friends.add(myFriend);
    
    myFriend.firstName = "Bob";
    myFriend.lastName = "Jones";
    myFriend.phoneNumber = "1234";
    friends.add(myFriend);
    
    myFriend.firstName = "Sally";
    myFriend.lastName = "Jane";
    myFriend.phoneNumber = "3568";
    friends.add(myFriend);
    
    myFriend.firstName = "Bill";
    myFriend.lastName = "Jones";
    myFriend.phoneNumber = "6789";
    friends.add(myFriend);
    
    myFriend.firstName = "Sally";
    myFriend.lastName = "Jane";
    myFriend.phoneNumber = "3568";
    friends.add(myFriend);

    
    friends.mapAll(PrintFriend);
    

    
    return 0;
}