//
//  main.cpp
//  treeEqual
//
//  Created by Vince Mansel on 10/26/11.
//  Copyright (c) 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>
#include "simpio.h"
#include "queue.h"
#include "bst.h"

#include "vector.h"

struct nodeT
{
    string key;
    nodeT * left;
    nodeT * right;
};

bool IsTreeEqual(nodeT * root1, nodeT * root2);
void TreeAdd(nodeT * &node, string key);

int main() {
    
    nodeT * root1 = NULL;
    nodeT * root2 = NULL;
    
    Vector<string> names;
    names.add("Greene");
    names.add("Carter");
    names.add("Benton");
    //names.add("ZooBaby");
    names.add("Morgenstern");
    names.add("Hathaway");
    names.add("Ross");
    names.add("Weaver");
    
    Vector<string>::Iterator itr = names.iterator();
    
    while (itr.hasNext())
        TreeAdd(root1, itr.next());
    
    names.clear();
    names.add("Greene");
    names.add("Carter");
    names.add("Benton");
    names.add("Morgenstern");
    names.add("Hathaway");
    names.add("Ross");
    names.add("Weaver");
    //names.add("ZooBaby");
    
    itr = names.iterator();
    
    while (itr.hasNext())
        TreeAdd(root2, itr.next());
    
    cout << "Tree Equals?: " << IsTreeEqual(root1, root2) << endl;
    
    
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

bool IsTreeEqual(nodeT * root1, nodeT *  root2) {
    
    Queue<nodeT * > queue1;
    Queue<nodeT * > queue2;
    queue1.enqueue(root1);
    queue2.enqueue(root2);
    while (!queue1.isEmpty() && !queue2.isEmpty()) {   
        nodeT * tree1 = queue1.dequeue();
        nodeT * tree2 = queue2.dequeue();
        if (tree1 != NULL && tree2 != NULL) {
            //cout << tree1->key << ":" << tree2->key << endl;
            if (tree1->key == tree2->key) {
                queue1.enqueue(tree1->left);
                queue1.enqueue(tree1->right);
                queue2.enqueue(tree2->left);
                queue2.enqueue(tree2->right);
            }
            else {
                return false;
            }
        }
        else if (tree1 != NULL || tree2 != NULL) {
            //cout << "Discrepency found: t1/t2=" << tree1 << "/" << tree2 << endl;
            return false;
        }
    }
    
    if (queue1.isEmpty() == queue2.isEmpty())
        return true;
    
    return false;
}