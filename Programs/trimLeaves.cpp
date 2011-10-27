//
//  main.cpp
//  trimLeaves
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

void TrimLeaves(nodeT * & root);
void PrintTreePreOrder(nodeT * & root);
void TreeAdd(nodeT * &node, string key);

int main() {
    
    nodeT * root = NULL;
    
    Vector<string> names;
    names.add("Jan");
    names.add("Cindy");
    names.add("Bobby");
    names.add("Greg");
    names.add("Marsha");
    names.add("Peter");
    names.add("Tiger");
    
    Vector<string>::Iterator itr = names.iterator();
    
    while (itr.hasNext())
        TreeAdd(root, itr.next());
    
    cout << "Before Trim" << endl;
    PrintTreePreOrder(root);
    TrimLeaves(root);
    cout << "After Trim" << endl;
    PrintTreePreOrder(root);
    
    return 0;
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

void TrimLeaves(nodeT * & root) {
    Queue<nodeT * > queue;
    queue.enqueue(root);
    while (!queue.isEmpty()) {   
        nodeT * tree = queue.dequeue();
        if (tree != NULL) {
            if (tree->left != NULL && (tree->left->left == NULL && tree->left->right == NULL)) {
                delete tree->left;
                tree->left = NULL;
            }
            else {
                queue.enqueue(tree->left);
            }
            if (tree->right != NULL && (tree->right->left == NULL && tree->right->right == NULL)) {
                delete tree->right;
                tree->right = NULL;
            }
            else {
                queue.enqueue(tree->right);
            }
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


