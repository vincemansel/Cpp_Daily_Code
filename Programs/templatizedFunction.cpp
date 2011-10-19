//
//  templatizedFunction.cpp
//  templatizedFunction
//
//  Created by Vince Mansel on 10/19/11.
//  Copyright (c) 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "simpio.h"
#include "queue.h"

struct recordingT {
    string title;
    string genre;
    int rating;
};

template <typename Type>
void Filter(Queue<Type> &q, bool (cmpFn)(Type one));

// Test Code:
//
//template <typename Type>
//bool AlwaysTrue(Type t) {
//    return false;
//}
//
//bool IsTwo(int t) {
//    if (t == 2) return true;
//    return false;
//}
//
//bool IsNotTwo(int t) {
//    if (t == 2) return false;
//    return true;
//}

bool IsBadAnimation(recordingT show)
{
    return (show.genre == "animation" && show.rating < 8);
}

int main() {
    
//    Queue<int> qq;
//    qq.enqueue(1);
//    qq.enqueue(2);
//    qq.enqueue(3);
//    qq.enqueue(2);
//    qq.enqueue(2);
//    qq.enqueue(5);
//    
//    Filter(qq, IsNotTwo);
    
    Queue<recordingT> * myDVRrecordings = new Queue<recordingT> ;
    
    recordingT * movie = new recordingT;
    movie->title = "Ben Hur";
    movie->genre = "drama";
    movie->rating = 7;
    myDVRrecordings->enqueue(*movie);
    
    movie->title = "Silly Cartoon";
    movie->genre = "animation";
    movie->rating = 7;
    myDVRrecordings->enqueue(*movie);
    
    movie->title = "OK Cartoon";
    movie->genre = "animation";
    movie->rating = 8;
    myDVRrecordings->enqueue(*movie);
    
    movie->title = "Meet the Fockers";
    movie->genre = "comedy";
    movie->rating = 7;
    myDVRrecordings->enqueue(*movie);
    
    movie->title = "007";
    movie->genre = "action";
    movie->rating = 9;
    myDVRrecordings->enqueue(*movie);

    
    Queue<recordingT> test = *myDVRrecordings;
    
    movie->title = "007 returns";
    movie->genre = "action";
    movie->rating = 6;
    test.enqueue(*movie);
    
    while (!test.isEmpty()) {
        cout << test.dequeue().title << ", ";
    }
    
    movie->title = "007 returns";
    movie->genre = "action";
    movie->rating = 6;
    test.enqueue(*movie);
    
    cout << endl;
    
    Filter(*myDVRrecordings, IsBadAnimation);
    
    while (!myDVRrecordings->isEmpty()) {
        cout << myDVRrecordings->dequeue().title << ", ";
    }

    
    return 0;
}

template <typename Type>
void Filter(Queue<Type> &q, bool (cmpFn)(Type one)) {
    
    Queue<Type> q2;
    
    int size = q.size();
    
    while (size-- > 0) {
        Type t = q.dequeue();
        if (!cmpFn(t))
            q.enqueue(t);
    }
}
