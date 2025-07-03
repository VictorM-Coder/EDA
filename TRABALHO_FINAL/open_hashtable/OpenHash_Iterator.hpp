#pragma once
#include <vector>
#include <string>
#include <utility>

#include "Slot.hpp"
#include "../Iterator.hpp"

template<typename K, typename V>
class OpenHashIterator: public Iterator<K, V> {
    std::vector<Slot<K, V>> _table;
    size_t index;

public:
    OpenHashIterator(std::vector<Slot<K, V>> table) {
        this->_table = table;
        this->index = _find_next_active(0);
    }

    bool hasNext() const override {
        return index < _table.size();
    }

    std::pair<K, V> next() override {
        auto actual = _table[index];
        index = _find_next_active(index + 1);
        return { actual.key, actual.value };
    }

private:
    size_t _find_next_active(size_t actual) {
        while (_table[actual].status != ACTIVE && actual < _table.size()) {
            actual++;
        }
        return actual;
    }
};