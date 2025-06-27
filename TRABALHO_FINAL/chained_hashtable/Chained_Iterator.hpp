#pragma once
#include <list>
#include <vector>

#include "../Iterator.hpp"

class ChainedIterator : public Iterator {
    std::vector<std::list<std::pair<std::string,size_t>>> _table;
    int index;
    std::list<std::pair<std::string, size_t>>::iterator _list_iterator;

public:
    ChainedIterator(std::vector<std::list<std::pair<std::string,size_t>>>& table) {
        _table = table;
        index = 0;
        while (index < _table.size() && _table[index].empty()) {
            ++index;
        }
        if (index < _table.size()) {
            _list_iterator = _table[index].begin();
        }

    }

    bool hasNext() const override {
        return index < _table.size();
    }

    std::pair<std::string, size_t> next() override {
        auto value = *_list_iterator;
        ++_list_iterator;

        while (index < _table.size() && _list_iterator == _table[index].end()) {
            ++index;
            if (index < _table.size())
                _list_iterator = _table[index].begin();
        }

        return value;
    }
};