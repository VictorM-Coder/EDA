#pragma once
#include <stack>
#include <utility>

#include "AVLNode.hpp"
#include "../Iterator.hpp"

template<typename K, typename V>
class AVL_Iterator: public Iterator<K, V>{
    stack<AVL_Node*> _stack;
    AVL_Node<K, V>* _current;

public:
    AVL_Iterator(AVL_Node<K, V>* root) {
        _current = root;
        while (_current) {
            _stack.push(_current);
            _current = _current->left;
        }
    }

    bool hasNext() const override {
        return !_stack.empty();
    }

    std::pair<K, V> next() override {
        AVL_Node<K, V>* node = _stack.top();
        _stack.pop();

        pair val(node->key, node->value);
        node = node->right;
        while (node) {
            _stack.push(node);
            node = node->left;
        }
        return val;
    }
};
