#pragma once
#include <stack>

#include "RB_Node.hpp"
#include "../Iterator.hpp"

class RB_Iterator: public Iterator {
    stack<RB_Node*> _stack;
    RB_Node* _current;

public:
    RB_Iterator(RB_Node* root) {
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
        RB_Node* node = _stack.top();
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
