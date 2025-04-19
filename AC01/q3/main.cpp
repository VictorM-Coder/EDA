#include <iostream>
#include <string>
#include <sstream>
#include "Tree.hpp"
using namespace std;

int main()
{
    int key;
	string line;
    Tree tree;

    getline(cin, line);
    stringstream ss (line);

    while(ss >> key) {
        tree.insert(key);
    }

    cout << tree.height() << " " << tree.size() << endl;
    return 0;
}