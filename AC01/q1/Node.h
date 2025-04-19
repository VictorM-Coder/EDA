#ifndef Q1_NODE_H
#define Q1_NODE_H

#include <iostream>

struct Node {
    int key;
    Node* left;
    Node* right;

    Node (int  key) {
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
    }

    ~Node() {
        std::cout << "Nodo " << key << " removido\n";
    }
};

#endif
