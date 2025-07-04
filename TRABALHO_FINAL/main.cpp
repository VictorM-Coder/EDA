// #include <iostream>
// #include <string>
// #include <vector>
//
// #include "FileUtils.hpp"
// #include "avl_tree/AVL_Tree.hpp"
// #include "rb_tree/RB_Tree.hpp"
// #include "chained_hashtable/ChainedHashTable.hpp"
// #include "open_hashtable/OpenHashTable.hpp"
// //
// int main(int argc, char* argv[]) {
//
//     if (argc != 4) {
//         std::cerr << "Uso: " << argv[0] << " <estrutura> <arquivo_entrada> <arquivo_saida>" << std::endl;
//         return 1;
//     }
//
//     std::string dataStruct = argv[1];
//     std::string pathToRead = argv[2];
//     std::string nameToWrite = argv[3];
//
//     std::vector<std::string> all_words = FileUtils::readFile(pathToRead);
//     cout << "size: " << all_words.size() << endl;
//
//     if (dataStruct == "dictionary_avl") {
//         AVL_Tree avl_tree;
//         for (auto& word : all_words) {
//             avl_tree.insert(word);
//         }
//         cout << "contagem: " << avl_tree.size() << endl;
//         auto it = avl_tree.iterator();
//         FileUtils::write_file(it, nameToWrite);
//
//     } else if (dataStruct == "dictionary_rb") {
//         RB_Tree rb_tree;
//         for (auto& word : all_words) {
//             rb_tree.insert(word);
//         }
//
//         cout << "contagem: " << rb_tree.size() << endl;
//         auto it = rb_tree.iterator();
//         FileUtils::write_file(it, nameToWrite);
//
//     } else if (dataStruct == "dictionary_cht") {
//         ChainedHashTable cht;
//         for (auto& word : all_words) {
//             cht.insert(word);
//         }
//
//         cout << "contagem: " << cht.size() << endl;
//         auto it = cht.iterator();
//         FileUtils::write_file(it, nameToWrite);
//
//     } else if (dataStruct == "dictionary_oht") {
//         OpenHashTable oht;
//         for (auto& word : all_words) {
//             oht.insert(word);
//         }
//
//         cout << "contagem: " << oht.size() << endl;
//         auto it = oht.iterator();
//         FileUtils::write_file(it, nameToWrite);
//
//     } else {
//         std::cerr << "Erro: estrutura de dados \"" << dataStruct << "\" não reconhecida." << std::endl;
//         return 1;
//     }
//
//     return 0;
// }

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <numeric> // Para std::accumulate

#include "Dictionary.hpp"
#include "FileUtils.hpp"
#include "avl_tree/AVL_Tree.hpp"
#include "rb_tree/RB_Tree.hpp"
#include "chained_hashtable/ChainedHashTable.hpp"
#include "open_hashtable/OpenHashTable.hpp"

using namespace std;
using namespace std::chrono;


void medirTempoInsercao(const std::string& book, const std::vector<std::string>& words, int total_tests) {
    cout << "\n===== Livro: " << book << " | Total de palavras: " << words.size() << " | Total de testes por estrutura: " << total_tests << " =====" << endl;

    vector<long long> temposAVL, temposRB, temposCHT, temposOHT;

    for (int i = 0; i < total_tests; ++i) {
        {
            Dictionary dict(AVL_TREE);
            auto start = high_resolution_clock::now();
            for (const auto& word : words) {
                dict.insert(word);
            }
            auto end = high_resolution_clock::now();
            temposAVL.push_back(duration_cast<milliseconds>(end - start).count());
        }

        {
            Dictionary dict(RB_TREE);
            auto start = high_resolution_clock::now();
            for (const auto& word : words) {
                dict.insert(word);
            }
            auto end = high_resolution_clock::now();
            temposRB.push_back(duration_cast<milliseconds>(end - start).count());
        }

        {
            Dictionary dict(CHAINED_HT);
            auto start = high_resolution_clock::now();
            for (const auto& word : words) {
                dict.insert(word);
            }
            auto end = high_resolution_clock::now();
            temposCHT.push_back(duration_cast<milliseconds>(end - start).count());
        }

        {
            Dictionary dict(OPEN_HT);
            auto start = high_resolution_clock::now();
            for (const auto& word : words) {
                dict.insert(word);
            }
            auto end = high_resolution_clock::now();
            temposOHT.push_back(duration_cast<milliseconds>(end - start).count());
        }
    }

    auto media = [](const vector<long long>& tempos) -> double {
        return accumulate(tempos.begin(), tempos.end(), 0.0) / tempos.size();
    };

    cout << "Média de tempo de inserção (ms):" << endl;
    cout << "  AVL_Tree: " << media(temposAVL) << " ms" << endl;
    cout << "  RB_Tree: " << media(temposRB) << " ms" << endl;
    cout << "  ChainedHashTable: " << media(temposCHT) << " ms" << endl;
    cout << "  OpenHashTable: " << media(temposOHT) << " ms" << endl;

    cout << "----------------------------------------" << endl;
}


int main() {
    const int total_tests = 10;

    medirTempoInsercao("The Secret Garden", FileUtils::readFile("/home/victor/Documentos/faculdade/EDA/TRABALHO_FINAL/entrada-livros/the-secret-garden.txt"), total_tests);
    medirTempoInsercao("Sherlock Holmes", FileUtils::readFile("/home/victor/Documentos/faculdade/EDA/TRABALHO_FINAL/entrada-livros/sherlock_holmes.txt"), total_tests);
    medirTempoInsercao("Manifesto Comunista", FileUtils::readFile("/home/victor/Documentos/faculdade/EDA/TRABALHO_FINAL/entrada-livros/o_manifesto_comunista_english.txt"), total_tests);
    medirTempoInsercao("Bíblia", FileUtils::readFile("/home/victor/Documentos/faculdade/EDA/TRABALHO_FINAL/entrada-livros/kjv-bible.txt"), total_tests);
    medirTempoInsercao("Dom Casmurro", FileUtils::readFile("/home/victor/Documentos/faculdade/EDA/TRABALHO_FINAL/entrada-livros/dom-casmurro.txt"), total_tests);
    medirTempoInsercao("A Riqueza das Nações", FileUtils::readFile("/home/victor/Documentos/faculdade/EDA/TRABALHO_FINAL/entrada-livros/a_riqueza_das nacoes_english.txt"), total_tests);

    return 0;
}
