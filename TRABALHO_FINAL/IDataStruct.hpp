#pragma once

#include <string>
#include <vector>
using namespace std;

class IDataStruct {
public:
    IDataStruct();
    IDataStruct(vector<pair<string, size_t>> pairs);
    virtual ~IDataStruct() = default;

    virtual void insert(string key);
    virtual void update(string key, size_t value);
    virtual pair<string, size_t> get(string);
    virtual void remove(string key);
    virtual bool exists(string key);
    //TODO iterador
    virtual size_t size();
    virtual void clear();
};
