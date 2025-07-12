#pragma once
#include <complex>

#include "RB_Iterator.hpp"
#include "../IDataStruct.hpp"
#include "RB_Node.hpp"

template<typename K, typename V>
class RB_Tree: public IDataStruct<K, V>{
    RB_Node<K, V>* _root;
    RB_Node<K, V>* NIL;
    size_t _count_rotations;
    size_t _count_comparisons;

public:
    RB_Tree() {
        NIL = new RB_Node<K, V>(BLACK);
        NIL->left = NIL;
        NIL->right = NIL;
        NIL->parent = NIL;
        _root = NIL;
        _count_rotations = 0;
        _count_comparisons = 0;
    }

    ~RB_Tree() override {
        RB_Tree::clear();
        delete NIL;
    }

    void printTree() const {
        _printTree(_root, "", true);
    }

    void insert(pair<K, V> my_pair) override {
        _insert(my_pair);
    }

    void update(K key, V value) override {
        RB_Node<K, V>* node = _get(key);
        if (node != nullptr) {
            node->value = value;
        } else {
            throw runtime_error("Key not found");
        }
    }

    pair<K, V> get(K key) override {
        RB_Node<K, V>* node = _get(key);
        if (node != NIL) {
            return { node->key, node->value };
        }
        throw runtime_error("Key not found");
    }

    void remove(K key) override {
        _remove(key);
    }

    bool exists(K key) override {
        return _get(key) != NIL;
    }

    RB_Iterator<K, V> iterator() {
        return RB_Iterator(_root, NIL);
    }

    size_t size() override {
        return _size(_root);
    }

    void clear() override {
        _clear(_root);
        _root = NIL;
        _count_rotations = 0;
        _count_comparisons = 0;
    }

    size_t total_rotations() const {
        return _count_rotations;
    }

    size_t total_comparisons() const {
        return _count_comparisons;
    }

    V& operator[](const K key) override {
        return _insert_at(key);
    }

private:
    /**
     *
     * @param key
     * @return the Node with contains the key or NIL case key not exists
     */
    RB_Node<K, V>* _get(const K& key) const {
        RB_Node<K, V>* node = _root;
        //FIND NODE
        while (node != NIL && node->key != key) {
            if (key < node->key) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return node;
    }

   void _insert(pair<K, V> my_pair) {
       RB_Node<K, V>* x = _root;
       RB_Node<K, V>* y = NIL;

       while (x != NIL) {
           y = x;
           if (_less(my_pair.first, x->key)) {
               x = x->left;
           } else if (_greater(my_pair.first, x->key)) {
               x = x->right;
           } else {
               return;
           }
       }

       auto* z = new RB_Node<K, V>(my_pair, RED);
       z->parent = y;
       if (y == NIL) {
           _root = z;
       } else if (z->key < y->key) {
           y->left = z;
       } else {
           y->right = z;
       }
       z->right = NIL;
       z->left = NIL;
       z->color = RED;
       _insert_fixup(z);
   }

    void _right_rotation(RB_Node<K, V>* node) {
       RB_Node<K, V>* u = node->left;
       node->left =  u->right;

       if (u->right != NIL) {
           u->right->parent = node;
       }

       u->parent = node->parent;
       if (node->parent == NIL) {
           _root = u;
       } else if (node == node->parent->right) {
           node->parent->right = u;
       } else {
           node->parent->left = u;
       }
       u->right = node;
       node->parent = u;
        _increment_count_rotations();
   }

    void _left_rotation(RB_Node<K, V>* node) {
       RB_Node<K, V>* u = node->right;
       node->right =  u->left;

       if (u->left != NIL) {
           u->left->parent = node;
       }

       u->parent = node->parent;
       if (node->parent == NIL) {
           _root = u;
       } else if (node == node->parent->left) {
           node->parent->left = u;
       } else {
           node->parent->right = u;
       }
       u->left = node;
       node->parent = u;
        _increment_count_rotations();
   }

    void _insert_fixup(RB_Node<K, V>* node) {
       while (node->parent->color == RED) {
           if (node->parent == node->parent->parent->left) {
               RB_Node<K, V>* aux = node->parent->parent->right;
               // CASE 1
               if (aux->color == RED) {
                   node->parent->color = BLACK;
                   aux->color = BLACK;
                   node->parent->parent->color = RED;
                   node = node->parent->parent;

               } else {
                   if (node == node->parent->right) { //CASE 2a
                       node = node->parent;
                       _left_rotation(node);
                   }
                   // CASE 3a
                   node->parent->color = BLACK;
                   node->parent->parent->color = RED;
                   _right_rotation(node->parent->parent);
               }
           } else if (node->parent == node->parent->parent->right) {
               RB_Node<K, V>* aux = node->parent->parent->left;
               // CASE 1
               if (aux->color == RED) {
                   node->parent->color = BLACK;
                   aux->color = BLACK;
                   node->parent->parent->color = RED;
                   node = node->parent->parent;
               } else  {
                   if (node == node->parent->left) { //CASE 2b
                       node = node->parent;
                       _right_rotation(node);
                   }
                   // CASE 3b
                   node->parent->color = BLACK;
                   node->parent->parent->color = RED;
                   _left_rotation(node->parent->parent);
               }
           }
       }
       _root->color = BLACK;
   }

    void _remove(const K& key) {
       RB_Node<K, V>* node = _get(key);

       if (node != NIL) {
           _delete(node);
       }
   }

    void _delete(RB_Node<K, V>* node) {
       RB_Node<K, V>* y;
       RB_Node<K, V>* x;

       if (node->left == NIL || node->right == NIL) {
           y = node;
       } else {
           y = _find_min(node->right);
       }

       if (y->left != NIL) {
           x = y->left;
       } else {
           x = y->right;
       }

       x->parent = y->parent;
       if (y->parent == NIL) {
           _root = x;
       } else {
           if (y == y->parent->left) {
               y->parent->left = x;
           } else {
               y->parent->right = x;
           }
       }

       if (y != node) {
           node->key = y->key;
           node->value = y->value;
       }

       if (y->color == BLACK) {
           _delete_fixup(x);
       }
       delete y;
   }

    void _delete_fixup(RB_Node<K, V>* node) {
       while (node != _root && node->color == BLACK) {
           RB_Node<K, V>* w;
           if (node == node->parent->left) { // Node is a left child
               w = node->parent->right;
               if (w->color == RED) { // CASE 1
                   w->color = BLACK;
                   node->parent->color = RED;
                   _left_rotation(node->parent);
                   w = node->parent->right;
               }

               if (w->left->color == BLACK && w->right->color == BLACK) { //CASE 2
                   w->color = RED;
                   node = node->parent;
               } else {
                   if (w->right->color == BLACK) { // CASE 3
                       w->left->color = BLACK;
                       w->color = RED;
                       _right_rotation(w);
                       w = node->parent->right;
                   }
                   // CASE 4
                   w->color = node->parent->color;
                   node->parent->color = BLACK;
                   w->right->color = BLACK;
                   _left_rotation(node->parent);
                   node = _root;
               }
           } else if (node == node->parent->right) { // Node is a right child
               w = node->parent->left;
               if (w->color == RED) { // CASE 1
                   w->color = BLACK;
                   node->parent->color = RED;
                   _right_rotation(node->parent);
                   w = node->parent->left;
               }

               if (w->left->color == BLACK && w->right->color == BLACK) { //CASE 2
                   w->color = RED;
                   node = node->parent;
               } else {
                   if (w->left->color == BLACK) { // CASE 3
                       w->right->color = BLACK;
                       w->color = RED;
                       _left_rotation(w);
                       w = node->parent->left;
                   }
                   // CASE 4
                   w->color = node->parent->color;
                   node->parent->color = BLACK;
                   w->left->color = BLACK;
                   _right_rotation(node->parent);
                   node = _root;
               }
           }
       }
       node->color = BLACK;
   }

    RB_Node<K, V>* _find_min(RB_Node<K, V>* node) const {
       while (node->left != NIL) {
           node = node->left;
       }
       return node;
   }

    size_t _size(const RB_Node<K, V>* node) const {
        if (node != NIL) {
            return 1 + _size(node->left) + _size(node->right);
        }
        return 0;
    }

    void _clear(RB_Node<K, V>* node) {
        if (node == NIL) {
            return;
        }
        _clear(node->left);
        _clear(node->right);
        delete node;
    }

    /**
     * @brief Método criado para fins de debug
     * @param node
     * @param prefix
     * @param isLeft
     */
    void _printTree(RB_Node<K, V>* node, const string& prefix, bool isLeft) const {
        if (node == NIL) return;

        cout << prefix;
        cout << (isLeft ? "├──" : "└──");

        // Mostra chave, cor e contagem
        cout << node->key << " (" << (node->color == RED ? "R" : "B") << ", count=" << node->count << ")" << endl;

        _printTree(node->left, prefix + (isLeft ? "│   " : "    "), true);
        _printTree(node->right, prefix + (isLeft ? "│   " : "    "), false);
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

    V& _insert_at(const K key) {
        RB_Node<K, V>* existing = _get(key);

        if (existing != NIL) {
            return existing->value;
        }

        _insert({key, 0});

        RB_Node<K, V>* node = _get(key);
        if (node == NIL) {
            throw runtime_error("Error trying to insert a node in the rb");
        }

        return node->value;
    }

};
