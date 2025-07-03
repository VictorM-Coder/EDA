#pragma once
#include <string>

enum Status {
    EMPTY,
    ACTIVE,
    DELETED
};

template<typename K, typename V>
struct Slot {
    K key;
    V value;
    Status status;

    Slot() : status(EMPTY) {}

    Slot(pair<K, V> my_pair, Status status) {
        this->key = my_pair.first;
        this->value = my_pair.second;
        this->status = status;
    }
};