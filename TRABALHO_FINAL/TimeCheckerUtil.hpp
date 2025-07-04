#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <numeric>

#include "Dictionary.hpp"
#include "FileUtils.hpp"


using namespace std;
using namespace std::chrono;

/**
 * @brief Classe auxiliar para rodar múltiplos testes de leitura de arquivos
 */
class TimeCheckerUtil {
public:
    void runPipeline() {
        const int total_tests = 1000;

        checkInsertionTime("The Secret Garden", FileUtils::readFile("/home/victor/Documentos/faculdade/EDA/TRABALHO_FINAL/entrada-livros/the-secret-garden.txt"), total_tests);
        checkInsertionTime("Sherlock Holmes", FileUtils::readFile("/home/victor/Documentos/faculdade/EDA/TRABALHO_FINAL/entrada-livros/sherlock_holmes.txt"), total_tests);
        checkInsertionTime("Manifesto Comunista", FileUtils::readFile("/home/victor/Documentos/faculdade/EDA/TRABALHO_FINAL/entrada-livros/o_manifesto_comunista_english.txt"), total_tests);
        checkInsertionTime("Bíblia", FileUtils::readFile("/home/victor/Documentos/faculdade/EDA/TRABALHO_FINAL/entrada-livros/kjv-bible.txt"), total_tests);
        checkInsertionTime("Dom Casmurro", FileUtils::readFile("/home/victor/Documentos/faculdade/EDA/TRABALHO_FINAL/entrada-livros/dom-casmurro.txt"), total_tests);
        checkInsertionTime("A Riqueza das Nações", FileUtils::readFile("/home/victor/Documentos/faculdade/EDA/TRABALHO_FINAL/entrada-livros/a_riqueza_das nacoes_english.txt"), total_tests);
    }

private:
    static void checkInsertionTime(const std::string& book, const std::vector<std::string>& words, int total_tests) {
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


};