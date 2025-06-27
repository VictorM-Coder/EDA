#pragma once
#include <stack>
#include <string>
#include <utility>

#include "AVLNode.hpp"
#include "../Iterator.hpp"

class AVL_Iterator: public Iterator{
    stack<AVL_Node*> _stack;
    AVL_Node* _current;

public:
    AVL_Iterator(AVL_Node* root) {
        _current = root;
        while (_current) {
            _stack.push(_current);
            _current = _current->left;
        }
    }

    bool hasNext() const override {
        return !_stack.empty();
    }

    pair<string, size_t> next() override {
        AVL_Node* node = _stack.top();
        _stack.pop();

        pair val(node->key, node->count);
        node = node->right;
        while (node) {
            _stack.push(node);
            node = node->left;
        }
        return val;
    }
};
