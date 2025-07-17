#pragma once

#include <iostream>
#include <algorithm>

#include "IDataStruct.hpp"
#include "avl_tree/AVL_Tree.hpp"
#include "chained_hashtable/ChainedHashTable.hpp"
#include "open_hashtable/OpenHashTable.hpp"
#include "rb_tree/RB_Tree.hpp"

enum Type {
    RB_TREE,
    AVL_TREE,
    OPEN_HT,
    CHAINED_HT
};

class Dictionary {
    IDataStruct<string, size_t> *dictionary;
    Type type;


public:
    Dictionary(Type type) {
        this->type = type;

        if (type == RB_TREE) {
            dictionary = new RB_Tree<string, size_t>();
        } else if (type == AVL_TREE) {
            dictionary = new AVL_Tree<string, size_t>();
        } else if (type == OPEN_HT) {
            dictionary = new OpenHashTable<string, size_t>();
        } else if (type == CHAINED_HT) {
            dictionary = new ChainedHashTable<string, size_t>();
        }
    }

    ~Dictionary() {
        delete dictionary;
    }

    void insert(const string word) {
        switch (type) {
            case RB_TREE:
                ++(*dynamic_cast<RB_Tree<string, size_t>*>(dictionary))[word];
                break;
            case AVL_TREE:
                ++(*dynamic_cast<AVL_Tree<string, size_t>*>(dictionary))[word];
                break;
            case OPEN_HT:
                ++(*dynamic_cast<OpenHashTable<string, size_t>*>(dictionary))[word];
                break;
            case CHAINED_HT:
                ++(*dynamic_cast<ChainedHashTable<string, size_t>*>(dictionary))[word];
                break;
        }
    }


    std::unique_ptr<Iterator<string, size_t>> getIterator() {
        switch (type) {
            case RB_TREE:
                return std::make_unique<RB_Iterator<string, size_t>>(
                    dynamic_cast<RB_Tree<string, size_t>*>(dictionary)->iterator()
                );
            case AVL_TREE:
                return std::make_unique<AVL_Iterator<string, size_t>>(
                    dynamic_cast<AVL_Tree<string, size_t>*>(dictionary)->iterator()
                );
            case OPEN_HT:
                return std::make_unique<OpenHashIterator<string, size_t>>(
                    dynamic_cast<OpenHashTable<string, size_t>*>(dictionary)->iterator()
                );
            case CHAINED_HT:
                return std::make_unique<ChainedIterator<string, size_t>>(
                    dynamic_cast<ChainedHashTable<string, size_t>*>(dictionary)->iterator()
                );
        }
        return nullptr;
}
    void printStatistics() const {
        switch (type) {
            case RB_TREE: {
                cout << "- Estatísticas Arvore rubro-negra" << endl;
                auto rb_tree = dynamic_cast<RB_Tree<string, size_t> *>(dictionary);
                cout << "   Total de comparacoes: " << rb_tree->total_comparisons() << endl;
                cout << "   Total de rotacoes: " << rb_tree->total_rotations() << endl;
            }
                break;
            case AVL_TREE: {
                cout << "- Estatísticas Arvore AVL" << endl;
                auto avl_tree = dynamic_cast<AVL_Tree<string, size_t> *>(dictionary);
                cout << "   Total de comparacoes: " << avl_tree->total_comparisons() << endl;
                cout << "   Total de rotacoes: " << avl_tree->total_rotations() << endl;
            }
                break;
            case OPEN_HT: {
                cout << "- Estatísticas Tabela hash com enderecamento aberto" << endl;
                auto open_hash = dynamic_cast<OpenHashTable<string, size_t> *>(dictionary);
                cout << "   Total de comparacoes: " << open_hash->total_comparisons() << endl;
                cout << "   Total de colisoes: " << open_hash->total_colisions() << endl;
            }
                break;
            case CHAINED_HT: {
                cout << "- Estatísticas Tabela hash com encadeamento externo" << endl;
                auto chained_hash = dynamic_cast<ChainedHashTable<string, size_t> *>(dictionary);
                cout << "   Total de comparacoes: " << chained_hash->total_comparisons() << endl;
                cout << "   Total de colisoes: " << chained_hash->total_colisions() << endl;
            }
                break;
        }
    }

    void update(const string& key, size_t value) {
        dictionary->update(key, value);
    }

    pair<string, size_t> get(const string& key) {
        return dictionary->get(key);
    }

    void remove(const string& key) {
        dictionary->remove(key);
    }

    bool exists(const string& key) {
        return dictionary->exists(key);
    }

    size_t size() {
        return dictionary->size();
    }

    void clear() {
        dictionary->clear();
    }

    vector<pair<string, size_t>> get_ordered_vector() {
        vector<pair<string, size_t>> ordered;
        ordered.reserve(this->size());

        auto it_ptr = getIterator();
        if (!it_ptr) {
            std::cerr << "Iterator is null!" << std::endl;
            return {};
        }

        auto it = it_ptr.get();
        while (it->hasNext()) {
            ordered.push_back(it->next());
        }

        if (type == CHAINED_HT || type == OPEN_HT) {
            std::sort(ordered.begin(), ordered.end(),
                 [](const pair<string, size_t>& a, const pair<string, size_t>& b) {
                     return a.first < b.first;
                 });
        }

        return ordered;
    }
};
