#pragma once

#include <memory>
#include <string>
#include <vector>
using namespace std;

template<typename K, typename V>
class IDataStruct {
public:
    IDataStruct() = default;
    virtual ~IDataStruct() = default;

    virtual void insert(pair<K, V> my_pair) = 0;
    virtual void update(K key, V value) = 0;
    virtual pair<K, V> get(K key) = 0;
    virtual void remove(K key) = 0;
    virtual bool exists(K key) = 0;
    virtual size_t size() = 0;
    virtual void clear() = 0;
};
