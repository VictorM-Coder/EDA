#include <iostream>
#include <string>
#include <vector>

#include "FileUtils.hpp"
#include "avl_tree/AVL_Tree.hpp"
#include "rb_tree/RB_Tree.hpp"
#include "chained_hashtable/ChainedHashTable.hpp"
#include "open_hashtable/OpenHashTable.hpp"

int main(int argc, char* argv[]) {

    if (argc != 4) {
        std::cerr << "Uso: " << argv[0] << " <estrutura> <arquivo_entrada> <arquivo_saida>" << std::endl;
        return 1;
    }

    std::string dataStruct = argv[1];
    std::string pathToRead = argv[2];
    std::string nameToWrite = argv[3];

    std::vector<std::string> all_words = FileUtils::readFile(pathToRead);

    if (dataStruct == "dictionary_avl") {
        AVL_Tree avl_tree;
        for (auto& word : all_words) {
            avl_tree.insert(word);
        }
        auto it = avl_tree.iterator();
        FileUtils::write_file(it, nameToWrite);

    } else if (dataStruct == "dictionary_rb") {
        RB_Tree rb_tree;
        for (auto& word : all_words) {
            rb_tree.insert(word);
        }
        auto it = rb_tree.iterator();
        FileUtils::write_file(it, nameToWrite);

    } else if (dataStruct == "dictionary_cht") {
        ChainedHashTable cht;
        for (auto& word : all_words) {
            cht.insert(word);
        }

        auto it = cht.iterator();
        FileUtils::write_file(it, nameToWrite);

    } else if (dataStruct == "dictionary_oht") {
        OpenHashTable oht;
        for (auto& word : all_words) {
            oht.insert(word);
        }

        auto it = oht.iterator();
        FileUtils::write_file(it, nameToWrite);

    } else {
        std::cerr << "Erro: estrutura de dados \"" << dataStruct << "\" não reconhecida." << std::endl;
        return 1;
    }

    return 0;
}
