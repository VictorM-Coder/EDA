#pragma once

using namespace std;
#include <string>

template<typename K, typename V>
struct AVL_Node {
    K key;
    size_t value;
    size_t height;

    AVL_Node* left;
    AVL_Node* right;

    AVL_Node(const K &key, const int height, const V value) {
        this->key = key;
        this->height = height;
        this->value = value;

        this->left = nullptr;
        this->right = nullptr;
    }

    AVL_Node(const pair<K, V> &item_pair, const int height) {
        this->key = item_pair.first;
        this->height = height;
        this->value = item_pair.second;

        this->left = nullptr;
        this->right = nullptr;
    }
};
