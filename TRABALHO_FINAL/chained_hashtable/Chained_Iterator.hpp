#pragma once
#include <list>
#include <vector>
#include <string>
#include <utility>

#include "../Iterator.hpp"

template<typename K, typename V>
class ChainedIterator : public Iterator<K, V> {
    std::vector<std::list<std::pair<K, V>>> _table;
    int index;
    std::list<std::pair<K, V>>::iterator _list_iterator;

public:
    ChainedIterator(std::vector<std::list<std::pair<K, V>>>& table) {
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

    std::pair<K, V> next() override {
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