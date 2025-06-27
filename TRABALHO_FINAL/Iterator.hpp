#pragma once
#include <string>
#include <utility>

class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() const = 0;
    virtual pair<string, size_t> next() = 0;
};
