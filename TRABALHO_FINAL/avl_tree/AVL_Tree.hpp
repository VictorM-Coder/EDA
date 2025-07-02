#pragma once
#include "AVLNode.hpp"
#include "AVL_Iterator.hpp"
#include "../IDataStruct.hpp"

template<typename K, typename V>
class AVL_Tree : public IDataStruct<K, V> {
    AVL_Node<K, V> * _root;
    size_t _count_rotations;
    size_t _count_comparisons;

public:
    AVL_Tree() {
        _count_rotations = 0;
        _count_comparisons = 0;
        _root = nullptr;
    }

    AVL_Tree(vector<pair<K, V>> pairs) {
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
    void insert(K key) override {
        _root = _insert(key, _root);
    }

    void update(K key, V value) override {
        AVL_Node<K, V>* node = _get(key, _root);
        if (node != nullptr) {
            node->count = value;
        } else {
            throw runtime_error("Key not found");
        }
    }

    pair<K, V> get(K key) override {
        AVL_Node<K, V>* node = _get(key, _root);
        if (node != nullptr) {
            return { node->key, node->count };
        }
        throw runtime_error("Key not found");
    }

    void remove(K key) override {
        _root = _remove(key, _root);
    }

    bool exists(K key) override {
        return _get(key, _root) != nullptr;
    }

    AVL_Iterator<K, V> iterator() const {
        return {_root};
    }

    size_t size() override {
        return _size(_root);
    }

    void clear() override {
        _clear(_root);
        _root = nullptr;
        _count_rotations = 0;
        _count_comparisons = 0;
    }

    size_t total_rotations() const {
        return _count_rotations;
    }

    size_t total_comparisons() const {
        return _count_comparisons;
    }

private:
    AVL_Node<K, V>* _insert_pair(pair<K, V> item_pair, AVL_Node<K, V>* node) {
        if (node == nullptr) {
            return new AVL_Node(item_pair, 1);
        }

        if (_equal(node->key, item_pair.first)) {
            return node;
        }

        if (_greater(item_pair.first, node->key)) {
            node->right = _insert_pair(item_pair, node->right);
        } else {
            node->left = _insert_pair(item_pair, node->left);
        }

        return _fixup_insert(node, item_pair.first);
    }

    AVL_Node<K, V>* _remove(K key, AVL_Node<K, V>* node) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = _remove(key, node->left);
        } else if (key > node->key) {
            node->right = _remove(key, node->right);
        } else if (node->right == nullptr) {
            AVL_Node<K, V>* child = node->left;
            delete node;
            return child;
        } else {
            node->right = _remove_sucessor(node, node->right);
        }

        return _fixup_remove(node);
    }

    AVL_Node<K, V>* _remove_sucessor(AVL_Node<K, V>* root, AVL_Node<K, V>* node) {
        if (node->left != nullptr) {
            node->left = _remove_sucessor(root, node->left);
        } else {
            root->key = node->key;
            AVL_Node<K, V>* aux = node->right;
            delete node;
            return aux;
        }

        node = _fixup_remove(node);
        return node;
    }

    int _height(AVL_Node<K, V>* node) {
        return (node != nullptr) ? node->height : 0;
    }

    int _calc_height(AVL_Node<K, V>* node) {
        return 1 + max(_height(node->left), _height(node->right));
    }

    int _balance(AVL_Node<K, V>* node) {
        return _height(node->right) - _height(node->left);
    }

    AVL_Node<K, V>* _right_rotation(AVL_Node<K, V>* node) {
        AVL_Node<K, V>* u = node->left;
        node->left = u->right;
        u->right = node;

        node->height = _calc_height(node);
        u->height = _calc_height(u);

        _increment_count_rotations();
        return u;
    }

    AVL_Node<K, V>* _left_rotation(AVL_Node<K, V>* node) {
        AVL_Node<K, V>* u = node->right;
        node->right =  u->left;
        u->left = node;

        node->height = _calc_height(node);
        u->height = _calc_height(u);

        _increment_count_rotations();
        return u;
    }

    AVL_Node<K, V>* _double_right_rotation(AVL_Node<K, V>* node) {
        node->left = _left_rotation(node->left);
        return _right_rotation(node);
    }

    AVL_Node<K, V>* _double_left_rotation(AVL_Node<K, V>* node) {
        node->right = _right_rotation(node->right);
        return _left_rotation(node);
    }

    AVL_Node<K, V>* _fixup_insert(AVL_Node<K, V>* node, K key) {
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

    AVL_Node<K, V>* _fixup_remove(AVL_Node<K, V>* node) {
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

    void _clear(AVL_Node<K, V>* node) {
        if (node != nullptr) {
            _clear(node->left);
            _clear(node->right);
            delete node;
        }
    }

    size_t _size(AVL_Node<K, V>* node) const {
        if (node != nullptr) {
            return 1 + _size(node->left) + _size(node->right);
        }
        return 0;
    }

    AVL_Node<K, V>* _get(K key, AVL_Node<K, V>* node) {
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

    bool _greater(const K& a, const K& b) {
        _count_comparisons++;
        return a > b;
    }

    bool _less(const K& a, const K& b) {
        _count_comparisons++;
        return a < b;
    }

    bool _equal(const K& a, const K& b) {
        _count_comparisons++;
        return a == b;
    }
};
