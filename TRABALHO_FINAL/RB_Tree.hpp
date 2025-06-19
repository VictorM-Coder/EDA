#pragma once
#include "IDataStruct.hpp"
#include "RB_Node.hpp"

class RB_Tree: public IDataStruct{
private:
    RB_Node* _root;
    RB_Node* NIL;

public:
    RB_Tree() {
        NIL = new RB_Node("", BLACK);
        _root = NIL;
        _root->left = NIL;
        _root->right = NIL;
        _root->parent = NIL;
    }

    void insert(string key) {

    }

    void update(string key, size_t value);
    pair<string, size_t> get(string);
    void remove(string key);
    bool exists(string key);
    //TODO iterador
    size_t size();
    void clear();
};
