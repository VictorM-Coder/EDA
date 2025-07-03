#pragma once
#include <stack>
#include <string>
#include <utility>

#include "RB_Node.hpp"
#include "../Iterator.hpp"
template<typename K, typename V>
class RB_Iterator: public Iterator<K, V> {
    stack<RB_Node*> _stack;
    RB_Node<K, V>* _current;
    RB_Node<K, V>* NIL;

public:
    RB_Iterator(RB_Node<K, V>* root, RB_Node<K, V>* nil): NIL(nil) {
        _current = root;
        while (_current != NIL) {
            _stack.push(_current);
            _current = _current->left;
        }
    }

    bool hasNext() const override {
        return !_stack.empty();
    }

    pair<K, V> next() override {
        RB_Node<K, V>* node = _stack.top();
        _stack.pop();

        pair<K, V> val(node->key, node->value);
        node = node->right;
        while (node != NIL) {
            _stack.push(node);
            node = node->left;
        }
        return val;
    }
};
