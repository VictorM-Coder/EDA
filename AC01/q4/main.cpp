#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "bst.h"
using namespace std;
#define MAX 70

// Funcao recursiva 'construirBST_balanceada'
// Essa funcao recebe como entrada:
// (1) Um ponteiro para uma BST vazia;
// (2) Um vetor de inteiros A[p..q] em ordem crescente com q-p+1 elementos:
// o numero p eh o indice inicial do vetor e o numero q eh o indice final do vetor
// Ao final da execucao dessa funcao, a BST deve ser uma arvore completa.
// Uma arvore completa com n nos tem altura igual ao piso( log_2(n) ) + 1.
void construirBST_balanceada(BST& tree, int array[], int start, int end) {
    if (start > end) {
        return;
    }

    int index =  (end+start)/2;
    tree.add(array[index]);
    construirBST_balanceada(tree, array, index+1, end);
    construirBST_balanceada(tree, array, start, index-1);
}

int main()
{
	string skeys;
	vector<int> vec;
	int value;

	getline(cin, skeys); // read a string containing all keys separated by spaces

	stringstream ss { skeys };

	while(ss >> value)
		vec.push_back(value);

	int n = vec.size();
	int A[MAX];

	for(int i = 0; i < n; i++)
		A[i] = vec[i];

	BST tree; // cria bst vazia
	construirBST_balanceada(tree, A, 0, n-1);

	cout << "height: " << tree.height() << endl;
	tree.bshow();

	return 0;
}