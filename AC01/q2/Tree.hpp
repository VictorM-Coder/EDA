#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include "Node.h"
#include <queue>

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

    ~Tree() {
        _clear(root);
        root = nullptr;
    }

    void bfs() {
        queue<Node*> nodos;
        nodos.push(root);

        bool first = true;

        while (!nodos.empty()) {
            Node* front = nodos.front();

            if (!first) cout << " ";
            cout << front->key;
            first = false;

            nodos.pop();
            if (front->left != nullptr) {
                nodos.push(front->left);
            }

            if (front->right != nullptr) {
                nodos.push(front->right);
            }
        }
        cout << "\n";
    }


private:
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