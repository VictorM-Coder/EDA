#pragma once
#include <vector>
#include <string>
#include <utility>

#include "Slot.hpp"
#include "../Iterator.hpp"

class OpenHashIterator: public Iterator {
    std::vector<Slot> _table;
    size_t index;

public:
    OpenHashIterator(std::vector<Slot> table) {
        this->_table = table;
        this->index = _find_next_active(0);
    }

    bool hasNext() const override {
        return index < _table.size();
    }

    std::pair<std::string, size_t> next() override {
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