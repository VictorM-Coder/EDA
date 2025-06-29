#pragma once
#include <stack>
#include <string>
#include <utility>

#include "RB_Node.hpp"
#include "../Iterator.hpp"
class RB_Iterator: public Iterator {
    stack<RB_Node*> _stack;
    RB_Node* _current;
    RB_Node* NIL;

public:
    RB_Iterator(RB_Node* root, RB_Node* nil): NIL(nil) {
        _current = root;
        while (_current != NIL) {
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

        pair<string, size_t> val(node->key, node->count);
        node = node->right;
        while (node != NIL) {
            _stack.push(node);
            node = node->left;
        }
        return val;
    }
};
