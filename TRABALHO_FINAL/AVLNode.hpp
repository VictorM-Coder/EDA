#pragma once

using namespace std;
#include <string>

struct AVL_Node {
    string key;
    size_t count;
    size_t height;

    AVL_Node* left;
    AVL_Node* right;

    AVL_Node(const string &key, const int height) {
        this->key = key;
        this->height = height;
        this->count = 1;

        this->left = nullptr;
        this->right = nullptr;
    }

    AVL_Node(const pair<string, size_t> &item_pair, const int height) {
        this->key = item_pair.first;
        this->height = height;
        this->count = item_pair.second;

        this->left = nullptr;
        this->right = nullptr;
    }
};
