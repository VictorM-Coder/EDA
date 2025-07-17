#include <iostream>
#include <string>
#include <vector>

#include "FileUtils.hpp"
#include "Dictionary.hpp"
#include "TestUtils.hpp"

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Uso: " << argv[0] << " <estrutura> <arquivo_entrada> <arquivo_saida>" << std::endl;
        return 1;
    }

    std::string dataStruct = argv[1];
    std::string pathToRead = argv[2];
    std::string nameToWrite = argv[3];

    std::vector<std::string> all_words = FileUtils::readFile(pathToRead);

    Type chosenType;
    if (dataStruct == "dictionary_avl") {
        chosenType = AVL_TREE;
    } else if (dataStruct == "dictionary_rb") {
        chosenType = RB_TREE;
    } else if (dataStruct == "dictionary_cht") {
        chosenType = CHAINED_HT;
    } else if (dataStruct == "dictionary_oht") {
        chosenType = OPEN_HT;
    } else {
        std::cerr << "Erro: estrutura de dados \"" << dataStruct << "\" não reconhecida." << std::endl;
        return 1;
    }

    Dictionary dict(chosenType);

    for (const auto& word : all_words) {
        dict.insert(word);
    }

    FileUtils::write_file(dict.get_ordered_vector(), nameToWrite);

    return 0;
}
