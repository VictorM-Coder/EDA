#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unicode/unistr.h>
#include <unicode/uchar.h>

#include "Iterator.hpp"


class FileUtils {
    static constexpr size_t INIT_SIZE = 10000;
public:
    static std::vector<std::string> readFile(const std::string& file_url) {
        std::vector<std::string> words;
        words.reserve(INIT_SIZE);

        std::ifstream my_file(file_url);
        std::string word;

        if (!my_file) {
            std::cerr << "An error occurred while trying to read the file.\n";
        }

        while (my_file >> word) {
            words.push_back(_clean_word(word));
        }

        return words;
    }

    static void write_file(Iterator<string, size_t> & it, const std::string& name) {
        std::ofstream my_file(name + ".txt");

        if (!my_file) {
            std::cerr << "An error occurred while trying to write the file." << std::endl;
            return;
        }

        while (it.hasNext()) {
            std::pair<std::string, size_t> word = it.next();
            my_file << word.first << " " <<  word.second << std::endl;
        }

        my_file.close();
    }

private:
    static std::string _clean_word(const std::string& input) {
        // Converter UTF-8 para UnicodeString (UTF-16 interno)
        icu::UnicodeString ustr = icu::UnicodeString::fromUTF8(input);

        icu::UnicodeString result;

        for (int32_t i = 0; i < ustr.length(); ++i) {
            UChar32 c = ustr.char32At(i);

            // pular se for pontuação
            if (u_ispunct(c) && c != 0x2D) { // 0x2D é o '-'
                continue;
            }

            UChar32 lower = u_tolower(c);
            result.append(lower);

            // Se for um caractere composto (como emoji, ou letra fora BMP), pular índice extra
            if (c > 0xFFFF) {
                ++i;
            }
        }

        // converter resultado UTF-16 de volta para UTF-8 std::string
        std::string cleaned;
        result.toUTF8String(cleaned);
        return cleaned;
    }


};
