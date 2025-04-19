#ifndef Q1_NODE_H
#define Q1_NODE_H

#include <iostream>

struct Node {
    int key;
    Node* left;
    Node* right;

    Node (int  key, Node* left, Node* right) {
        this->key = key;
        this->left = left;
        this->right = right;
    }
};

#endif
