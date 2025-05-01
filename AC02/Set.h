#ifndef BST_H
#define BST_H
#include "Node.hpp"
#include <algorithm>
using namespace std;

class Set {

public:
    Set() {
        root = nullptr;
    }

    ~Set(){
        clear();
    }

    void insert(int x) {
        root = _insert(root, x);
    }

    void erase(int x) {
        root = _remove(root, x);
    }

    //TODO testar
    bool contains(int x) {
        return _contains(x, root);
    }

    //Todo testar
    void clear() {
        _clear(root);
        root = nullptr;
    }

    //Todo testar
    void swap(Set* t) {
        Node* myRoot = root;
        root = t->root;
        t->root = myRoot;
    }

    //Todo testar
    int minimum() {
        return _minimum(root);
    }

    //Todo  testar
    int maximum() {
        return _maximum(root);
    }

    bool empty() {
        return root == nullptr;
    }

    int successor(int x) {
        return _sucessor(root, x);
    }

    int height() {
        return _height(root);
    }

    void show() {
        _show(root, "");
    }
private:
    Node* root;

    Node* _insert(Node* node, int x) {
        if (node == nullptr) {
            return new Node(x);
        }

        if (node->key == x) {
            return node;
        } else if (x > node->key) {
            node->right = _insert(node->right, x);
        } else if (x < node->key) {
            node->left = _insert(node->left, x);
        }

        node = _fixup_node(node, x);
        return node;
    }

    bool _contains(int x, Node* node) {
        if (node == nullptr) {
            return false;
        }

        if (node->key == x) {
            return true;
        }

        if (x > node->key) {
            return _contains(x, node->right);
        } else if (x < node->key) {
            return _contains(x, node->left);
        }

        return false;
    }

    void _clear(Node* node) {
        if (node != nullptr) {
            _clear(node->left);
            _clear(node->right);
            delete node;
        }
    }

    int _minimum(Node* node) {
        if (node->left == nullptr){
            return node->key;
        }

        return _minimum(node->left);
    }

    int _maximum(Node* node) {
        if (node->right == nullptr){
            return node->key;
        }

        return _maximum(node->right);
    }

    int _sucessor(Node* node, int x) {
        Node* sucessor = nullptr;

        while (node != nullptr) {
            if (x < node->key) {
                sucessor = node;
                node = node->left;
            } else if (x > node->key) {
                node = node->right;
            } else { // x == node->key
                if (node->right != nullptr) {
                    return _minimum(node->right);
                } else if (sucessor != nullptr) {
                    return sucessor->key;
                } else {
                    throw "No successor found";
                }
            }
        }

        throw "Number not found";
    }

    int _predecessor(Node* node, int x) {
        Node* sucessor = nullptr;

        while (node != nullptr) {
            if (x > node->key) {
                sucessor = node;
                node = node->right;
            } else if (x < node->key) {
                node = node->left;
            } else { // x == node->key
                if (node->left != nullptr) {
                    return _maximum(node->left);
                } else if (sucessor != nullptr) {
                    return sucessor->key;
                } else {
                    throw "No successor found";
                }
            }
        }

        throw "Number not found";
    }

    int _height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int _balance(Node* node) {
        return _height(node->right) - _height(node->left);
    }

    Node* _right_rotation(Node* node) {
        Node* u = node->left;
        node->left = u->right;
        u->right = node;

        node->height = 1 + max(_height(node->left), _height(node->right));
        u->height = 1 + max(_height(u->left), _height(u->right));

        return u;
    }

    Node* _left_rotation(Node* node) {
        Node* u = node->right;
        node->right = u->left;
        u->left = node;

        node->height = 1 + max(_height(node->left), _height(node->right));
        u->height = 1 + max(_height(u->left), _height(u->right));

        return u;
    }

    Node* _fixup_node(Node* node, int key) {
        int balance = _balance(node);

        if (balance < -1 && key < node->left->key) {
            return _right_rotation(node);
        } else if (balance < -1 && key > node->left->key) {
            node->left = _left_rotation(node->left);
            return _right_rotation(node);
        } else if (balance > 1 && key > node->right->key) {
            return _left_rotation(node);
        } else if (balance > 1 && key < node->right->key) {
            node->right = _right_rotation(node);
            return _left_rotation(node);
        }

        node->height = 1 + max(_height(node->left), _height(node->right));
        return node;
    }

    Node* fixup_deletion(Node* node) {
        int balance = _balance(node);

        if (balance > 1 && _balance(node->right) > 0) {
            return _left_rotation(node);
        } else if (balance > 1 && _balance(node->right) < 0) {
            node->right = _right_rotation(node->right);
            return _left_rotation(node);
        } else if (balance < -1 && _balance(node->left) > 0) {
            return _right_rotation(node);
        } else if (balance < -1 && _balance(node->left) < 0) {
            node->left = _left_rotation(node->left);
            return _right_rotation(node);
        }

        node->height = 1 + max(_height(node->left), _height(node->right));
        return node;
    }

    Node* _remove(Node* node, int x) {
        if (node == nullptr) {
            return nullptr;
        }

        if (x > node->key) {
            node->right = _remove(node->right, x);
        } else if (x < node->key) {
            node->left = _remove(node->left, x);
        } else if (node->right == nullptr) {
            Node* child = node->left;
            delete node;
            return child;
        } else {
            node->right = _remove_sucessor(node, node->right);
        }

        node = fixup_deletion(node);
        return node;
    }

    Node* _remove_sucessor(Node* root,Node* node) {
        if (node->left != nullptr) {
            node->left = _remove_sucessor(root, node->left);
        } else {
            root->key = node->key;
            Node* aux = node->right;
            delete node;
            return aux;
        }

        node = fixup_deletion(node);
        return node;
    }

    void _show(Node *node, std::string heranca) {
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            _show(node->right , heranca + "r");
        for(int i = 0; i < (int) heranca.size() - 1; i++)
            std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
        if(heranca != "")
            std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
        if(node == nullptr){
            std::cout << "#" << std::endl;
            return;
        }
        std::cout << node->key << std::endl;
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            _show(node->left, heranca + "l");
    }
};

#endif