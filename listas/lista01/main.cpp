#include <iostream>

#include "BTree.hpp"

int main() {
    BTree* b_tree = new BTree();
    b_tree->insert(3);
    b_tree->insert(1);
    b_tree->insert(5);
    b_tree->insert(2);
    b_tree->insert(4);
    b_tree->insert(6);
    b_tree->insert(7);

    b_tree->show();
    b_tree->find(4);
    b_tree->excluir(1);
    b_tree->show();
    // std::cout << b_tree->qnt_nos_internos() << std::endl;
    // std::cout << b_tree->maior() << std::endl;
    // b_tree->excluir_folhas();
    // b_tree->show();
    // std::cout << b_tree->qnt_nos_internos() << std::endl;
    return 0;
}
