#pragma once

#include <memory>
#include <string>
#include <vector>
using namespace std;

class IDataStruct {
public:
    IDataStruct() = default;
    virtual ~IDataStruct() = default;

    virtual void insert(string key) = 0;
    virtual void update(string key, size_t value) = 0;
    virtual pair<string, size_t> get(string) = 0;
    virtual void remove(string key) = 0;
    virtual bool exists(string key) = 0;
    // virtual Iterator iterador() = 0;
    virtual size_t size() = 0;
    virtual void clear() = 0;
};
