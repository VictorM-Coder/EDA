#pragma once
#include <cmath>

#include "OpenHash_Iterator.hpp"
#include "Slot.hpp"
#include "../IDataStruct.hpp"

template<typename K, typename V>
class OpenHashTable : public IDataStruct<K, V> {
    size_t _number_of_elements;
    size_t _table_size;
    float _max_load_factor;

    vector<Slot<K, V>> _table;

    hash<K> _hashing;

    size_t _count_comparisons;
    size_t _count_colisions;

public:
    OpenHashTable(size_t tableSize = 19, float load_factor = 1.0) {
        _number_of_elements = 0;
        _count_colisions = 0;
        _count_comparisons = 0;

        _table_size = _get_next_prime(tableSize);
        _table.resize(_table_size);

        if(load_factor <= 0) {
            _max_load_factor = 1.0;
        } else {
            _max_load_factor = load_factor;
        }
    }

    OpenHashTable(const vector<pair<K, V>> &pairs, float load_factor = 1.0) {
        _number_of_elements = 0;
        _count_colisions = 0;
        _count_comparisons = 0;
        _table_size = _get_next_prime(pairs.size());
        _table.resize(_table_size);

        if(load_factor <= 0) {
            _max_load_factor = 1.0;
        } else {
            _max_load_factor = load_factor;
        }

        for (int i = 0; i < pairs.size(); i++) {
            _insert(pairs[i].first, pairs[i].second);
        }
    }

    void insert(pair<K, V> my_pair) override {
        _insert(my_pair);
    }

    void update(K key, V value) override {
        int slot = _find_slot(key);
        if (slot == -1) {
            throw std::runtime_error("Key not found");
        }
        _table[slot].value = value;
    }

    pair<K, V> get(K key) override {
        int slot = _find_slot(key);
        if (slot == -1) {
            throw std::runtime_error("Key not found");
        }

        return {_table[slot].key, _table[slot].value};
    }

    void remove(K key) override {
        _remove(key);
    }

    bool exists(K key) override {
        int slot = _find_slot(key);
        return slot > -1;
    }

     OpenHashIterator<K, V> iterator() {
         return OpenHashIterator(_table);
     }

    size_t size() override {
        return _number_of_elements;
    }

    void clear() override {
        _table.assign(_table_size, Slot<K, V>{});
        _number_of_elements = 0;
        _count_colisions = 0;
        _count_comparisons = 0;
    }

    size_t total_comparisons() const {
        return _count_comparisons;
    }

    size_t total_colisions() const {
        return _count_colisions;
    }

private:
    size_t _get(const K &key) {
        int slot = _find_slot(key);
        if (slot == -1) {
            throw "key not found";
        }
        return _table[slot].value;
    }

    bool _insert(const K &key, V value) {
        if (_calc_load_factor() >= _max_load_factor) {
            _rehash(2 * _table_size);
        }

        int slot = _find_slot(key);

        if (slot != -1) {
            return true;
        }

        for (size_t i = 0; i < _table_size; ++i) {
            size_t possible_slot = _calc_hash_code(key, i);
            //Adiciona uma nova chave na tabela
            if (_table[possible_slot].status != ACTIVE) {
                _table[possible_slot] = Slot<K, V>(key, ACTIVE, value);
                _number_of_elements++;
                return true;
            } else {
                if ((_table[possible_slot].key != key)) {
                    _count_colisions++;
                }
            }
        }
        return false;
    }

    bool _remove(const K &key) {
        int slot = _find_slot(key);
        if (slot == -1) {
            return false;
        }
        _table[slot].status = DELETED;
        _number_of_elements--;
        return true;
    }

    int _find_slot(const K& key) {
        int index = 0;
        while (index < _table_size) {
            size_t slot = _calc_hash_code(key, index);
            if (_table[slot].status == EMPTY) return -1;
            if (_table[slot].status == ACTIVE && _equal(_table[slot].key, key)) return slot;
            ++index;
        }
        return -1;
    }

    size_t _calc_hash_code(const K& key, size_t index) const {
        return (_hashing(key) + index) % _table_size;
    }

    /**
     * @brief Busca o próximo número primo a partir do valor passado. Caso o valor passado seja par, soma-se mais um, para torná-lo impar antes de prosseguir.
     * @param actual Número atual
     * @return Pŕoximo número primo
     */
    static size_t _get_next_prime(size_t actual) {
        if (actual <= 2) return 3;

        actual += (actual % 2 == 0);

        while (true) {
            bool is_prime = true;
            int limit = sqrt(actual);

            for (int i = 3; i <= limit; i+=2) {
                if (actual % i == 0) {
                    is_prime = false;
                    break;
                }
            }
            if (is_prime) {
                return actual;
            }
            actual += 2;
        }
    }

    float _calc_load_factor() const {
        return static_cast<float>(_number_of_elements) / _table_size;
    }

    void _rehash(const size_t new_size) {
        size_t new_table_size = _get_next_prime(new_size);
        if(new_table_size > _table_size) {
            vector<Slot<K, V>> old_vec = _table; // copia as chaves para uma nova tabela
            _table.clear(); // apaga todas as chaves da tabela atual e deixa ela vazia
            _table.resize(new_table_size); // tabela redimensionada com novo primo

            //Atualizar valores antigos
            _number_of_elements = 0;
            _table_size = new_table_size;
            for(size_t i = 0; i < old_vec.size(); ++i) {
                _insert(old_vec[i].key, old_vec[i].value);
            }
        }
    }

    bool _equal(const K& a, const K& b) {
        _count_comparisons++;
        return a == b;
    }
};