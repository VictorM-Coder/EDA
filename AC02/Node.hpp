#ifndef AC02_NODE_HPP
#define AC02_NODE_HPP

struct Node {
    int key;
    int height;
    Node *left;
    Node *right;

    Node(int k) {
        this->key = k;
        this->left = nullptr;
        this->right = nullptr;
    }
//    Node(int k, int height) {
//        this->key = k;
//        this->height = height;
//        this->left = nullptr;
//        this->right = nullptr;
//    }
};

#endif //AC02_NODE_HPP
