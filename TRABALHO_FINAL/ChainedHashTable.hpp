#pragma once
#include <list>
#include <stdexcept>
#include <bits/valarray_after.h>

#include "IDataStruct.hpp"


class ChainedHashTable :  public IDataStruct {
private:
    size_t _number_of_elements;
    size_t _table_size;
    float _max_load_factor;

    vector<list<pair<string,size_t>>> _table;
    hash<string> _hashing;

public:
    /**
     * @brief Construtor: cria uma tabela hash com um numero primo de slots.
     *
     * @param tableSize := o numero de slots da tabela.
     */
    ChainedHashTable(size_t tableSize = 19, float load_factor = 1.0) {
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
    ChainedHashTable(const vector<pair<string, size_t>> &pairs, float load_factor = 1.0) {
        _number_of_elements = 0;
        _table_size = _get_next_prime(pairs.size());
        _table.resize(_table_size);

        for (int i = 0; i < pairs.size(); i++) {
            _insert(pairs[i].first, pairs[i].second);
        }

        if(load_factor <= 0) {
            _max_load_factor = 1.0;
        } else {
            _max_load_factor = load_factor;
        }
    }

    void insert(string key) override {
        _insert(key);
    }

    void update(string key, size_t value) override {
        pair<string, size_t>& my_pair = _get(key);
        my_pair.second = value;
    }

    pair<string, size_t> get(string key) override {
        pair<string, size_t> my_pair = _get(key);
        return my_pair;
    }

    void remove(string key) override {
        _remove(key);
    }

    bool exists(string key) override {
        try {
            _get(key);
            return true;
        } catch (const std::exception& e) {
            return false;
        }
    }

    //TODO iterador
    size_t size() override {
        return _number_of_elements;
    }

    void clear() override {
        for(size_t i = 0; i < _table_size; ++i) {
            _table[i].clear();
        }
        _number_of_elements = 0;
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

    size_t _calc_hash_code(const string& key) const {
        return _hashing(key) % _table_size;
    }

    pair<string, size_t>& _get(const string& key) {
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
            vector<list<pair<string,size_t>>> old_vec = _table; // copia as chaves para uma nova tabela
            _table.clear(); // apaga todas as chaves da tabela atual e deixa ela vazia
            _table.resize(new_table_size); // tabela redimensionada com novo primo

            //Atualizar valores antigos
            _number_of_elements = 0;
            _table_size = new_table_size;
            for(size_t i = 0; i < old_vec.size(); ++i) {
                for(auto& par : old_vec[i]) {
                    _insert(par.first, par.second);
                }
                old_vec[i].clear(); // opcional
            }
        }
    }

    /**
     * @brief Insert para inserir e contar os elementos
     * @param key chave a ser inserida
     */
    void _insert(const string& key) {
        if (_calc_load_factor() >= _max_load_factor) {
            _rehash(2*_table_size);
        }

        size_t slot = _calc_hash_code(key);
        for(auto& p : _table[slot]) {
            if(p.first == key) {
                p.second++;
                return;
            }
        }

        _table[slot].push_back(make_pair(key, 0));
        _number_of_elements++;
    }

    /**
     * @brief Insere um novo elemento com chave e valor na tabela. caso o elemento já exista, apenas ignora
     * @param key
     * @param value
     */
    void _insert(const string& key, const size_t& value) {
        if (_calc_load_factor() >= _max_load_factor) {
            _rehash(2*_table_size);
        }

        size_t slot = _calc_hash_code(key);
        for(auto p& : _table[slot]) {
            if(p.first == key) {
                return;
            }
        }

        _table[slot].push_back(make_pair(key, value));
        _number_of_elements++;
    }

    /**
     * @brief Se o elemento com a chave existe, remove da tabela hash o elemento, do contrário, não faz nada.
     *
     * @param key := chave a ser removida
     */
    void _remove(const string& key) {
        size_t slot = _calc_hash_code(key);
        for(auto it = _table[slot].begin(); it != _table[slot].end(); ++it) {
            if(it->first == key) {
                _table[slot].erase(it);
                _number_of_elements--;
                return;
            }
        }
    }
};