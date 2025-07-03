#pragma once

using namespace std;
#include <string>

#define RED true
#define BLACK false

template<typename K, typename V>
struct RB_Node {
    bool color;
    K key;
    V value;

    RB_Node* parent;
    RB_Node* left;
    RB_Node* right;

    RB_Node(bool color) {
        this->color = color;

        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }

    RB_Node(const pair<string, size_t> &item_pair, bool color, const int height) {
        this->key = item_pair.first;
        this->value = item_pair.second;
        this->color = color;

        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
    }
};
