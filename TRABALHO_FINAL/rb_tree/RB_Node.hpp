#pragma once

using namespace std;
#include <string>

#define RED true
#define BLACK false

struct RB_Node {
    bool color;
    string key;
    size_t count;

    RB_Node* parent;
    RB_Node* left;
    RB_Node* right;

    RB_Node(const string &key, bool color) {
        this->key = key;
        this->color = color;
        this->count = 1;

        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }

    RB_Node(const pair<string, size_t> &item_pair, bool color, const int height) {
        this->key = item_pair.first;
        this->count = item_pair.second;
        this->color = color;

        this->left = nullptr;
        this->right = nullptr;
    }
};
