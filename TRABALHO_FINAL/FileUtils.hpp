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

    static void write_file(Iterator<std::string, size_t> & it, const std::string& name) {
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

        bool hasAlnum = false;

        for (int32_t i = 0; i < ustr.length(); ++i) {
            UChar32 c = ustr.char32At(i);

            // Ignorar pontuação, exceto hífen
            if (u_ispunct(c) && c != 0x2D) {
                continue;
            }

            // Verifica se é alfanumérico
            if (u_isalnum(c)) {
                hasAlnum = true;
            }

            UChar32 lower = u_tolower(c);
            result.append(lower);

            // Se for caractere fora do BMP, pular índice extra
            if (c > 0xFFFF) {
                ++i;
            }
        }

        // Verifica se sobrou algo além de hífens
        if (!hasAlnum) {
            return ""; // descarta palavras como "--", "---", etc.
        }

        // Remove hífens iniciais e finais, se ainda existirem
        while (result.length() > 0 && result.char32At(0) == 0x2D) {
            result.remove(0, 1);
        }
        while (result.length() > 0 && result.char32At(result.length() - 1) == 0x2D) {
            int32_t lastIndex = result.length() - 1;
            if (result.char32At(lastIndex) > 0xFFFF) {
                result.removeBetween(lastIndex - 1, lastIndex + 1); // caractere fora BMP
            } else {
                result.remove(lastIndex, 1);
            }
        }

        std::string cleaned;
        result.toUTF8String(cleaned);
        return cleaned;
    }



};
