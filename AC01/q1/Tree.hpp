#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include "Node.h"

using namespace std;

class Tree {
private:
    Node* root;

public:
    Tree() {
        root = nullptr;
    }

    void insert(int key) {
        root = _insert(root, key);
    }

    void pre() {
        cout << "Pre.:";
        _pre(root);
        cout << "\n";
    }

    void in() {
        cout << "In..:";
        _in(root);
        cout << "\n";
    }

    void pos() {
        cout << "Post:";
        _pos(root);
        cout << "\n";
    }

    ~Tree() {
        _clear(root);
        root = nullptr;
    }

private:
    void _pre(Node* node) {
        if (node != nullptr) {
            cout << " " << node->key;
            _pre(node->left);
            _pre(node->right);
        }
    }

    void _in(Node* node) {
        if (node != nullptr) {
            _in(node->left);
            cout << " " << node->key;
            _in(node->right);
        }
    }

    void _pos(Node* node) {
        if (node != nullptr) {
            _pos(node->left);
            _pos(node->right);
            cout << " " << node->key;
        }
    }

    Node* _insert(Node* node, int key) {
        if (node == nullptr) {
            return new Node(key);
        }

        if (key > node->key) {
            node->right = _insert(node->right, key);
        } else if (key < node->key) {
            node->left = _insert(node->left, key);
        }
        return node;
    }

    void _clear(Node* node) {
        if(node != nullptr) {
            _clear(node->left);
            _clear(node->right);
            delete node;
        }
    }
};

#endif