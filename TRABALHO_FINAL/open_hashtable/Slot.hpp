#pragma once
#include <string>

enum Status {
    EMPTY,
    ACTIVE,
    DELETED
};

struct Slot {
    std::string key;
    size_t value;
    Status status;

    Slot() : key(""), value(0), status(EMPTY) {}

    Slot(std::string key, Status status) {
        this->key = key;
        this->status = status;
        this->value = 1;
    }

    Slot(std::string key, Status status, size_t value) {
        this->key = key;
        this->status = status;
        this->value = value;
    }
};