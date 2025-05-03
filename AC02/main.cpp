#include <iostream>
#include <vector>
#include <sstream>
#include "Set.h"

using namespace std;

void mostrar_menu(const vector<Set*>& conjuntos, int indice_atual) {
    cout << "\n==== MENU ====\n";
    cout << "Conjuntos existentes: " << conjuntos.size();
    if (indice_atual != -1) cout << " | Atual: " << indice_atual;
    cout << "\n\n";

    cout << " 1. Criar novo conjunto\n";
    cout << " 2. Selecionar conjunto atual\n";
    cout << " 3. Inserir elemento\n";
    cout << " 4. Remover elemento\n";
    cout << " 5. Verificar se contem elemento\n";
    cout << " 6. Mostrar minimo\n";
    cout << " 7. Mostrar maximo\n";
    cout << " 8. Mostrar sucessor\n";
    cout << " 9. Mostrar predecessor\n";
    cout << "10. Mostrar altura\n";
    cout << "11. Verificar se esta vazio\n";
    cout << "12. Limpar conjunto\n";
    cout << "13. Trocar dados entre dois conjuntos\n";
    cout << "14. Inserir lista de elementos\n";
    cout << "15. Mostrar conjunto atual\n";
    cout << "16. Unir dois conjuntos\n";
    cout << "17. Intersecao entre dois conjuntos\n";
    cout << "18. Diferenca entre dois conjuntos\n";
    cout << " 0. Sair\n";
    cout << "Opcao: ";
}

int main() {
    vector<Set*> conjuntos;
    int indice_atual = -1;

    int opcao, valor, indice1, indice2;

    do {
        mostrar_menu(conjuntos, indice_atual);
        cin >> opcao;

        switch(opcao) {
            case 1:
                conjuntos.push_back(new Set());
                indice_atual = conjuntos.size() - 1;
                cout << "Novo conjunto criado com indice " << indice_atual << ".\n";
                break;

            case 2:
                cout << "Digite o indice do conjunto: ";
                cin >> indice1;
                if (indice1 >= 0 && indice1 < (int)conjuntos.size()) {
                    indice_atual = indice1;
                    cout << "Conjunto " << indice_atual << " selecionado.\n";
                } else {
                    cout << "Indice invalido.\n";
                }
                break;

            case 3:
                if (indice_atual == -1) {
                    cout << "Nenhum conjunto selecionado.\n";
                    break;
                }
                cout << "Valor a inserir: ";
                cin >> valor;
                conjuntos[indice_atual]->insert(valor);
                cout << "Inserido.\n";
                break;

            case 4:
                if (indice_atual == -1) {
                    cout << "Nenhum conjunto selecionado.\n";
                    break;
                }
                cout << "Valor a remover: ";
                cin >> valor;
                conjuntos[indice_atual]->erase(valor);
                cout << "Removido.\n";
                break;

            case 5:
                if (indice_atual == -1) {
                    cout << "Nenhum conjunto selecionado.\n";
                    break;
                }
                cout << "Valor a verificar: ";
                cin >> valor;
                cout << (conjuntos[indice_atual]->contains(valor) ? "Contem.\n" : "Nao contem.\n");
                break;

            case 6:
                if (indice_atual == -1) {
                    cout << "Nenhum conjunto selecionado.\n";
                    break;
                }
                try {
                    cout << "Minimo: " << conjuntos[indice_atual]->minimum() << "\n";
                } catch (...) {
                    cout << "Erro ao obter minimo.\n";
                }
                break;

            case 7:
                if (indice_atual == -1) {
                    cout << "Nenhum conjunto selecionado.\n";
                    break;
                }
                try {
                    cout << "Maximo: " << conjuntos[indice_atual]->maximum() << "\n";
                } catch (...) {
                    cout << "Erro ao obter maximo.\n";
                }
                break;

            case 8:
                if (indice_atual == -1) {
                    cout << "Nenhum conjunto selecionado.\n";
                    break;
                }
                cout << "Valor para encontrar sucessor: ";
                cin >> valor;
                try {
                    cout << "Sucessor: " << conjuntos[indice_atual]->successor(valor) << "\n";
                } catch (...) {
                    cout << "Erro ao obter sucessor.\n";
                }
                break;

            case 9:
                if (indice_atual == -1) {
                    cout << "Nenhum conjunto selecionado.\n";
                    break;
                }
                cout << "Valor para encontrar predecessor: ";
                cin >> valor;
                try {
                    cout << "Predecessor: " << conjuntos[indice_atual]->predecessor(valor) << "\n";
                } catch (...) {
                    cout << "Erro ao obter predecessor.\n";
                }
                break;

            case 10:
                if (indice_atual == -1) {
                    cout << "Nenhum conjunto selecionado.\n";
                    break;
                }
                cout << "Altura: " << conjuntos[indice_atual]->height() << "\n";
                break;

            case 11:
                if (indice_atual == -1) {
                    cout << "Nenhum conjunto selecionado.\n";
                    break;
                }
                cout << (conjuntos[indice_atual]->empty() ? "Esta vazio.\n" : "Nao esta vazio.\n");
                break;

            case 12:
                if (indice_atual == -1) {
                    cout << "Nenhum conjunto selecionado.\n";
                    break;
                }
                conjuntos[indice_atual]->clear();
                cout << "Conjunto limpo.\n";
                break;

            case 13:
                cout << "Digite os indices dos conjuntos para trocar (i1 i2): ";
                cin >> indice1 >> indice2;
                if (indice1 >= 0 && indice1 < (int)conjuntos.size() &&
                    indice2 >= 0 && indice2 < (int)conjuntos.size()) {
                    conjuntos[indice1]->swap(conjuntos[indice2]);
                    cout << "Conjuntos trocados.\n";
                } else {
                    cout << "Indices invalidos.\n";
                }
                break;

            case 14:
                if (indice_atual == -1) {
                    cout << "Nenhum conjunto selecionado.\n";
                    break;
                }
                cin.ignore();
                cout << "Digite os elementos separados por espaco: ";
                {
                    string linha;
                    getline(cin, linha);
                    istringstream iss(linha);
                    while (iss >> valor) {
                        conjuntos[indice_atual]->insert(valor);
                    }
                    cout << "Lista inserida.\n";
                }
                break;

            case 15:
                if (indice_atual == -1) {
                    cout << "Nenhum conjunto selecionado.\n";
                    break;
                }
                cout << "Conjunto " << indice_atual << ": \n";
                conjuntos[indice_atual]->show();
                break;

            case 16:
                cout << "Digite os indices dos conjuntos a serem unidos (i1 i2): ";
                cin >> indice1 >> indice2;
                if (indice1 >= 0 && indice1 < (int)conjuntos.size() &&
                    indice2 >= 0 && indice2 < (int)conjuntos.size()) {
                    Set* novo = conjuntos[indice1]->set_union(conjuntos[indice2]);
                    conjuntos.push_back(novo);
                    indice_atual = conjuntos.size() - 1;
                    cout << "Conjunto unido criado com indice " << indice_atual << ".\n";
                    } else {
                        cout << "Indices invalidos.\n";
                    }
                break;

            case 17:
                cout << "Digite os indices dos conjuntos a serem interseccionado (i1 i2): ";
                cin >> indice1 >> indice2;
                if (indice1 >= 0 && indice1 < (int)conjuntos.size() &&
                    indice2 >= 0 && indice2 < (int)conjuntos.size()) {
                    Set* novo = conjuntos[indice1]->intersection(conjuntos[indice2]);
                    conjuntos.push_back(novo);
                    indice_atual = conjuntos.size() - 1;
                    cout << "Conjunto interseção criado com indice " << indice_atual << ".\n";
                    } else {
                        cout << "Indices invalidos.\n";
                    }
                break;

            case 18:
                cout << "Digite os indices dos conjuntos a ser calculada a diferenca (i1 i2): ";
                cin >> indice1 >> indice2;
                if (indice1 >= 0 && indice1 < (int)conjuntos.size() &&
                    indice2 >= 0 && indice2 < (int)conjuntos.size()) {
                    Set* novo = conjuntos[indice1]->difference(conjuntos[indice2]);
                    conjuntos.push_back(novo);
                    indice_atual = conjuntos.size() - 1;
                    cout << "Conjunto diferenca criado com indice " << indice_atual << ".\n";
                    } else {
                        cout << "Indices invalidos.\n";
                    }
                break;

            case 0:
                cout << "Encerrando...\n";
                break;

            default:
                cout << "Opcao invalida.\n";
                break;
        }

    } while(opcao != 0);

    for (Set* s : conjuntos) {
        delete s;
    }

    return 0;
}
