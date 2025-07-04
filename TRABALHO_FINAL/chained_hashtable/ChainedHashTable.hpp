#pragma once
#include <list>
#include <stdexcept>
#include <cmath>

#include "Chained_Iterator.hpp"
#include "../IDataStruct.hpp"

template<typename K, typename V>
class ChainedHashTable :  public IDataStruct<K, V> {
    size_t _number_of_elements;
    size_t _table_size;
    float _max_load_factor;

    vector<list<pair<K, V>>> _table;
    hash<K> _hashing;

    size_t _count_comparisons;
    size_t _count_colisions;

public:
    /**
     * @brief Construtor: cria uma tabela hash com um numero primo de slots.
     *
     * @param tableSize := o numero de slots da tabela.
     */
    ChainedHashTable(size_t tableSize = 19, float load_factor = 1.0) {
        _count_comparisons = 0;
        _count_colisions = 0;
        _number_of_elements = 0;
        _table_size = _get_next_prime(tableSize);
        _table.resize(_table_size);

        if(load_factor <= 0) {
            _max_load_factor = 1.0;
        } else {
            _max_load_factor = load_factor;
        }
    }

    /**
     * @brief Construtor: cria uma tabela hash com um numero primo de slots a partir de um vector de pares.
     */
    ChainedHashTable(const vector<pair<K, V>> &pairs, float load_factor = 1.0) {
        _number_of_elements = 0;
        _count_comparisons = 0;
        _count_colisions = 0;
        _table_size = _get_next_prime(pairs.size());
        _table.resize(_table_size);

        if(load_factor <= 0) {
            _max_load_factor = 1.0;
        } else {
            _max_load_factor = load_factor;
        }

        for (const auto & pair : pairs) {
            _insert(pair.first, pair.second);
        }
    }

    void insert(pair<K, V> my_pair) override {
        _insert(my_pair);
    }

    void update(K key, V value) override {
        pair<K, V>& my_pair = _get(key);
        my_pair.second = value;
    }

    pair<K, V> get(K key) override {
        pair<K, V> my_pair = _get(key);
        return my_pair;
    }

    void remove(K key) override {
        _remove(key);
    }

    bool exists(K key) override {
        try {
            _get(key);
            return true;
        } catch (const std::exception& e) {
            return false;
        }
    }

    ChainedIterator<K, V> iterator() {
        return ChainedIterator(_table);
    }

    size_t size() override {
        return _number_of_elements;
    }

    void clear() override {
        for(size_t i = 0; i < _table_size; ++i) {
            _table[i].clear();
        }
        _number_of_elements = 0;
        _count_comparisons = 0;
        _count_colisions = 0;
    }

    size_t total_comparisons() {
        return _count_comparisons;
    }

    size_t total_colisions() {
        return _count_colisions;
    }


private:
    /**
     * @brief Busca o próximo número primo a partir do valor passado. Caso o valor passado seja par, soma-se mais um, para torná-lo impar antes de prosseguir.
     * @param actual Número atual
     * @return Pŕoximo número primo
     */
    size_t _get_next_prime(size_t actual) {
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

    size_t _calc_hash_code(const K& key) const {
        return _hashing(key) % _table_size;
    }

    pair<K, V>& _get(const K& key) {
        size_t slot = _calc_hash_code(key);

        for (auto& actual_pair : _table[slot]) {
            if (actual_pair.first == key) {
                return actual_pair;
            }
        }

        throw std::runtime_error("Key is not in the table");
    }

    float _calc_load_factor() const {
        return static_cast<float>(_number_of_elements) / _table_size;
    }


    /**
     * @brief Recebe um inteiro nao negativo m e faz com que o tamanho
     * da tabela seja um numero primo maior ou igual a m.
     * Se m for maior que o tamanho atual da tabela, um rehashing eh realizado.
     * Se m for menor que o tamanho atual da tabela, a funcao nao tem nenhum efeito.
     * Um rehashing eh uma operacao de reconstrucao da tabela:
     * Todos os elementos no container sao rearranjados de acordo
     * com o seu valor de hashing dentro na nova tabela.
     * Isto pode alterar a ordem de iteracao dos elementos dentro do container.
     * Operacoes de rehashing sao realizadas automaticamente pelo container
     * sempre que load_factor() ultrapassa o m_max_load_factor.
     *
     * @param new_size := o novo tamanho da tabela hash
     */
    void _rehash(size_t new_size) {
        size_t new_table_size = _get_next_prime(new_size);
        if(new_table_size > _table_size) {
            vector<list<pair<K, V>>> old_vec = _table; // copia as chaves para uma nova tabela
            _table.clear(); // apaga todas as chaves da tabela atual e deixa ela vazia
            _table.resize(new_table_size); // tabela redimensionada com novo primo

            //Atualizar valores antigos
            _number_of_elements = 0;
            _table_size = new_table_size;
            for(auto & i : old_vec) {
                for(auto& par : i) {
                    _insert({par.first, par.second});
                }
                i.clear(); // opcional
            }
        }
    }

    /**
     * @brief Insere um novo elemento com chave e valor na tabela. caso o elemento já exista, apenas ignora
     */
    void _insert(pair<K, V> my_pair) {
        if (_calc_load_factor() >= _max_load_factor) {
            _rehash(2*_table_size);
        }

        size_t slot = _calc_hash_code(my_pair.first);
        for(auto &p : _table[slot]) {
            if(_equal(p.first, my_pair.first)) {
                return;
            }
        }

        if (!_table[slot].empty()) {
            _count_colisions++;
        }

        _table[slot].push_back(my_pair);
        _number_of_elements++;
    }

    /**
     * @brief Se o elemento com a chave existe, remove da tabela hash o elemento, do contrário, não faz nada.
     *
     * @param key := chave a ser removida
     */
    void _remove(const K& key) {
        size_t slot = _calc_hash_code(key);
        for(auto it = _table[slot].begin(); it != _table[slot].end(); ++it) {
            if(it->first == key) {
                _table[slot].erase(it);
                _number_of_elements--;
                return;
            }
        }
    }

    bool _equal(const K& a, const K& b) {
        _count_comparisons++;
        return a == b;
    }
};