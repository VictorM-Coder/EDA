#include <iostream>
#include <sstream>
#include <vector>
#include "Tree.hpp"

using namespace std;

Tree* readTree() {
    Tree* tree = new Tree();
    int totalNodes;
    cin >> totalNodes;
    cin.ignore();

    string keysString;
    getline(cin, keysString);

    istringstream iss(keysString);
    int key;
    while (iss >> key) {
        tree->insert(key);
    }

    return tree;
}

int main() {
    int totalArvores;
    cin >> totalArvores;
    cin.ignore();

    for (int i = 0; i < totalArvores; i++) {
        Tree* tree = readTree();

        cout << "Case " << i+1 << ":" << "\n";
        tree->pre();
        tree->in();
        tree->pos();
        cout << "\n";
    }

    return 0;
}