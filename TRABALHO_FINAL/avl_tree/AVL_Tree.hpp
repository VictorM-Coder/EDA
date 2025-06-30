#pragma once
#include "AVLNode.hpp"
#include "AVL_Iterator.hpp"
#include "../IDataStruct.hpp"

class AVL_Tree : public IDataStruct {
    AVL_Node* _root;
    size_t _count_rotations;
    size_t _count_comparisons;

public:
    AVL_Tree() {
        _count_rotations = 0;
        _count_comparisons = 0;
        _root = nullptr;
    }

    AVL_Tree(vector<pair<string, size_t>> pairs) {
        _root = nullptr;
        _count_rotations = 0;
        _count_comparisons = 0;
        for (int i = 0; i < pairs.size(); i++) {
            _root = _insert_pair(pairs[i], _root);
        }
    }

    ~AVL_Tree() {
        AVL_Tree::clear();
    }
    void insert(string key){
        _root = _insert(key, _root);
    }

    void update(string key, size_t value) {
        AVL_Node* node = _get(key, _root);
        if (node != nullptr) {
            node->count = value;
        } else {
            throw "key not found";
        }
    }

    pair<string, size_t> get(string key) {
        AVL_Node* node = _get(key, _root);
        if (node != nullptr) {
            pair<string, size_t> iten;
            iten.first = node->key;
            iten.second = node->count;
            return iten;
        }
        throw "key not found";
    }

    void remove(string key) {
        _root = _remove(key, _root);
    }

    bool exists(string key) {
        return _get(key, _root) != nullptr;
    }

    AVL_Iterator iterator() const {
        return {_root};
    }

    size_t size() {
        return _size(_root);
    }

    void clear() {
        _clear(_root);
        _root = nullptr;
        _count_rotations = 0;
        _count_comparisons = 0;
    }

    size_t total_rotations() {
        return _count_rotations;
    }

    size_t total_comparisons() {
        return _count_comparisons;
    }

private:
    AVL_Node* _insert_pair(pair<string, size_t> item_pair, AVL_Node* node) {
        if (node == nullptr) {
            return new AVL_Node(item_pair, 1);
        }

        if (node->key == item_pair.first) {
            node->count += item_pair.second;
            return node;
        }

        if (item_pair.first > node->key) {
            node->right = _insert_pair(item_pair, node->right);
        }

        if (item_pair.first < node->key) {
            node->left = _insert_pair(item_pair, node->left);
        }

        node = _fixup_insert(node, item_pair.first);
        return node;
    }


    AVL_Node* _insert(string key, AVL_Node* node) {
        if (node == nullptr) {
            return new AVL_Node(key, 1);
        }

        if (_equal(node->key, key)) {
            node->count++;
            return node;
        }

        if (_greater(key, node->key)) {
            node->right = _insert(key, node->right);
        } else {
            node->left = _insert(key, node->left);
        }

        node = _fixup_insert(node, key);
        return node;
    }

    AVL_Node* _remove(string key, AVL_Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = _remove(key, node->left);
        } else if (key > node->key) {
            node->right = _remove(key, node->right);
        } else if (node->right == nullptr) {
            AVL_Node* child = node->left;
            delete node;
            return child;
        } else {
            node->right = _remove_sucessor(node, node->right);
        }

        node = _fixup_remove(node);
        return node;
    }
    AVL_Node* _remove_sucessor(AVL_Node* root, AVL_Node* node) {
        if (node->left != nullptr) {
            node->left = _remove_sucessor(root, node->left);
        } else {
            root->key = node->key;
            AVL_Node* aux = node->right;
            delete node;
            return aux;
        }

        node = _fixup_remove(node);
        return node;
    }

    int _height(AVL_Node* node) {
        return (node != nullptr) ? node->height : 0;
    }

    int _calc_height(AVL_Node* node) {
        return 1 + max(_height(node->left), _height(node->right));
    }

    int _balance(AVL_Node* node) {
        return _height(node->right) - _height(node->left);
    }

    AVL_Node* _right_rotation(AVL_Node* node) {
        AVL_Node* u = node->left;
        node->left = u->right;
        u->right = node;

        node->height = _calc_height(node);
        u->height = _calc_height(u);

        _increment_count_rotations();
        return u;
    }

    AVL_Node* _left_rotation(AVL_Node* node) {
        AVL_Node* u = node->right;
        node->right =  u->left;
        u->left = node;

        node->height = _calc_height(node);
        u->height = _calc_height(u);

        _increment_count_rotations();
        return u;
    }

    AVL_Node* _double_right_rotation(AVL_Node* node) {
        node->left = _left_rotation(node->left);
        return _right_rotation(node);
    }

    AVL_Node* _double_left_rotation(AVL_Node* node) {
        node->right = _right_rotation(node->right);
        return _left_rotation(node);
    }

    AVL_Node* _fixup_insert(AVL_Node* node, string key) {
        int balance = _balance(node);

        // CASE 1 (a)
        if (balance < -1 && key < node->left->key) {
            return _right_rotation(node);
        }

        // CASE 1 (b)
        if (balance < -1 && key > node->left->key) {
            return _double_right_rotation(node);
        }

        // CASE 2 (a)
        if (balance > 1 && key > node->right->key) {
            return _left_rotation(node);
        }

        // CASE 2 (b)
        if (balance > 1 && key < node->right->key) {
            return _double_left_rotation(node);
        }

        node->height = _calc_height(node);
        return node;
    }

    AVL_Node* _fixup_remove(AVL_Node* node) {
        int balance = _balance(node);

        if (balance > 1 && _balance(node->right) >= 0) {
            return _left_rotation(node);
        }

        if (balance > 1 && _balance(node->right) < 0) {
            return _double_left_rotation(node);
        }

        if (balance < -1 && _balance(node->left) <= 0) {
            return _right_rotation(node);
        }

        if (balance < -1 && _balance(node->left) > 0) {
            return _double_right_rotation(node);
        }

        node->height = _calc_height(node);
        return node;
    }

    void _clear(AVL_Node* node) {
        if (node != nullptr) {
            _clear(node->left);
            _clear(node->right);
            delete node;
        }
    }

    size_t _size(AVL_Node *node) const {
        if (node != nullptr) {
            return 1 + _size(node->left) + _size(node->right);
        }
        return 0;
    }

    AVL_Node* _get(string key, AVL_Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->key == key) {
            return node;
        }

        if (key > node->key) {
            return _get(key, node->right);
        }

        if (key < node->key) {
            return _get(key, node->left);
        }

        return nullptr;
    }

    void _increment_count_rotations() {
        _count_rotations++;
    }

    bool _greater(const string& a, const string& b) {
        _count_comparisons++;
        return a > b;
    }

    bool _less(const string& a, const string& b) {
        _count_comparisons++;
        return a < b;
    }

    bool _equal(const string& a, const string& b) {
        _count_comparisons++;
        return a == b;
    }
};
