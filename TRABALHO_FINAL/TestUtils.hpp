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
class TestUtils {
public:
    static void runPipeline() {
        const int total_tests = 1000;

        cout << "CALCULO DO TEMPO" << endl;
        auto book_secret_garden = FileUtils::readFile("/home/victor/Documentos/faculdade/EDA/TRABALHO_FINAL/entrada-livros/the-secret-garden.txt");
        auto book_shelock = FileUtils::readFile("/home/victor/Documentos/faculdade/EDA/TRABALHO_FINAL/entrada-livros/sherlock_holmes.txt");
        auto book_manifesto = FileUtils::readFile("/home/victor/Documentos/faculdade/EDA/TRABALHO_FINAL/entrada-livros/o_manifesto_comunista_english.txt");
        auto book_bible = FileUtils::readFile("/home/victor/Documentos/faculdade/EDA/TRABALHO_FINAL/entrada-livros/kjv-bible.txt");
        auto book_dom = FileUtils::readFile("/home/victor/Documentos/faculdade/EDA/TRABALHO_FINAL/entrada-livros/dom-casmurro.txt");
        auto book_nations = FileUtils::readFile("/home/victor/Documentos/faculdade/EDA/TRABALHO_FINAL/entrada-livros/a_riqueza_das nacoes_english.txt");

        checkInsertionTime("The Secret Garden", book_secret_garden, total_tests);
        checkInsertionTime("Sherlock Holmes", book_shelock, total_tests);
        checkInsertionTime("Manifesto Comunista", book_manifesto, total_tests);
        checkInsertionTime("Bíblia", book_bible, total_tests);
        checkInsertionTime("Dom Casmurro", book_dom, total_tests);
        checkInsertionTime("A Riqueza das Nações", book_nations, total_tests);

        cout << "======================================================================" << endl;
        cout << "ESTATÍSTICAS" << endl;

        runPipelineStatistics("The Secret Garden", book_secret_garden);
        runPipelineStatistics("Sherlock Holmes", book_shelock);
        runPipelineStatistics("Manifesto Comunista", book_manifesto);
        runPipelineStatistics("Bíblia", book_bible);
        runPipelineStatistics("Dom Casmurro", book_dom);
        runPipelineStatistics("A Riqueza das Nações", book_nations);
    }

private:
    static void checkTime(const std::vector<std::string> &words, vector<long long>& time_vector, Type type) {
        Dictionary dict(type);
        auto start = high_resolution_clock::now();
        for (const auto& word : words) {
            dict.insert(word);
        }
        auto end = high_resolution_clock::now();
        time_vector.push_back(duration_cast<milliseconds>(end - start).count());
    }

    static void checkInsertionTime(const std::string& book, const std::vector<std::string>& words, int total_tests) {
        cout << "\n===== Livro: " << book << " | Total de palavras: " << words.size()
             << " | Total de testes por estrutura: " << total_tests << " =====" << endl;

        vector<long long> temposAVL, temposRB, temposCHT, temposOHT;

        for (int i = 0; i < total_tests; ++i) {
            checkTime(words, temposAVL, AVL_TREE);
            checkTime(words, temposRB, RB_TREE);
            checkTime(words, temposCHT, CHAINED_HT);
            checkTime(words, temposOHT, OPEN_HT);
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

    static void runPipelineStatistics(const std::string& book, const std::vector<std::string>& words) {
        cout << "\n== Estatísticas do livro: " << book << " ==" << endl;
        checkStatistics(words, AVL_TREE);
        checkStatistics(words, RB_TREE);
        checkStatistics(words, CHAINED_HT);
        checkStatistics(words, OPEN_HT);
        cout << "----------------------------------------" << endl;
    }

    static void checkStatistics(const std::vector<std::string> &words, Type type) {
        Dictionary dict(type);
        for (const auto& word : words) {
            dict.insert(word);
        }
        dict.printStatistics();
    }
};
