//
//  balancedTrees.cpp
//  balancedTrees
//
//  Created by Vince Mansel on 10/26/11.
//  Copyright (c) 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "simpio.h"
#include "queue.h"

#include "vector.h"

struct nodeT
{
    string key;
    nodeT * left;
    nodeT * right;
};

int TreeHeight(nodeT *t);
bool IsBalanced(nodeT *t);
void PrintTreePreOrder(nodeT * & root);
void TreeAdd(nodeT * &node, string key);

int main() {
    
    nodeT * root = NULL;
//  Height = 7, IsBalanced = false    
//    Vector<string> names;
//    names.add("Bashful");
//    names.add("Doc");
//    names.add("Dopey");
//    names.add("Grumpy");
//    names.add("Happy");
//    names.add("Sleepy");
//    names.add("Sneezy");

//  Height = 4, IsBalanced = false
//    Vector<string> names;
//    names.add("Grumpy");
//    names.add("Dopey");
//    names.add("Doc");
//    names.add("Bashful");
//    names.add("Happy");
//    names.add("Sleepy");
//    names.add("Sneezy");
    
//  Height = 4, IsBalanced = false;
//    Vector<string> names;
//    names.add("Grumpy");
//    names.add("Doc");
//    //names.add("Dopey");
//    //names.add("Bashful");
//    names.add("Sleepy");
//    names.add("Happy");
//    names.add("Sneezy");
//    names.add("Zoe");

//  Height = 3, IsBalanced = true;
    Vector<string> names;
    names.add("Grumpy");
    names.add("Doc");
    names.add("Dopey");
    names.add("Bashful");    
    names.add("Sleepy");
    names.add("Happy");
    names.add("Sneezy");

    
    Vector<string>::Iterator itr = names.iterator();
    
    while (itr.hasNext())
        TreeAdd(root, itr.next());
    
    cout << "Tree:" << endl;
    PrintTreePreOrder(root);
    
    cout << "Length = " << TreeHeight(root) << endl;
    cout << "IsBalanced = " << IsBalanced(root) << endl;
    
    return 0;
}

int RecTreeHeight(nodeT *t, int len) {
    if (t) {
        int lenLeft = RecTreeHeight(t->left,len+1);
        int lenRight = RecTreeHeight(t->right,len+1);
        if (lenLeft > lenRight)
            len = lenLeft;
        else
            len = lenRight;
    }
    return len;
}

int TreeHeight(nodeT *t) {
    return RecTreeHeight(t,0);
}

bool RecIsBalanced(nodeT *t, int &len) {
    if (t) {
        int lenLeft = len+1;
        int lenRight = len+1;
        bool balancedLeft = RecIsBalanced(t->left,lenLeft);
        bool balancedRight = RecIsBalanced(t->right,lenRight);
        if (lenLeft > lenRight)
            len = lenLeft;
        else
            len = lenRight;
        if (abs(lenLeft - lenRight) <= 1 && balancedLeft && balancedRight)
            return true;
        else
            return false;
    }
    return true;
}

bool IsBalanced(nodeT *t) {
    int len = 0;
    bool balanced = RecIsBalanced(t,len);
    cout << " IsBalanced:len=" << len << endl;
    return balanced;
}

void TreeAdd(nodeT * &node, string key) {
    if (node == NULL) {
        node = new nodeT;
        node->key = key;
        node->left = NULL;
        node->right = NULL;
    }
    else {
        if (key == node->key) {
            ;
        }
        else if (key < node->key) {
            TreeAdd(node->left, key);
        }
        else {
            TreeAdd(node->right, key); 
        }
    }
}



//
// Prints tree in pre-order fashion.
// Also, represents a breadth-first traversal of the tree
//

void PrintTreePreOrder(nodeT * & root) {
    Queue<nodeT *> queue;
    queue.enqueue(root);
    while (!queue.isEmpty()) {   
        nodeT * tree = queue.dequeue();
        if (tree != NULL) {
            cout << tree->key << endl;
            queue.enqueue(tree->left);
            queue.enqueue(tree->right);
            
        }
    }
}


