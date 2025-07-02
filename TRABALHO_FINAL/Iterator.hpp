#pragma once
#include <string>
#include <utility>

template<typename K, typename V>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() const = 0;
    virtual std::pair<K, V> next() = 0;
};
