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
        this->height = 1;
    }
};

#endif //AC02_NODE_HPP
