#ifndef BTREE
#define BTREE

struct Node {
    int key;
    Node *left;
    Node *right;

    Node(int key) {
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class BTree {
private:
    Node *root;

public:
    BTree() {
       root = nullptr;
    }

    void insert(int key) {
        root = _insert(root, key);
    }

    void show() {
        bshow(root, "");
    }

    int size() {
        return _size(root);
    }

    int qnt_folhas() {
        return _qnt_folhas(root);
    }

    void excluir_folhas() {
        root = _excluir_folhas(root);
    }

    int qnt_nos_internos() {
        return _qnt_nos_internos(root);
    }

    int maior() {
        return _maior(root);
    }

    Node* find(int key) {
        return _find(root, key);
    }

    bool contains(int key) {
        return find(key) != nullptr;
    }

    void excluir(int key) {
        root = _excluir(root, key);
    }
private:
    Node *_insert(Node *node, int key) {
        if (node == nullptr)
            return new Node(key);

        if (node->key > key)
            node->left = _insert(node->left, key);

        if (node->key < key)
            node->right = _insert(node->right, key);

        return node;
    }

    int _size(Node* node) {
        if (node == nullptr)
            return 0;

        return 1 +_size(node->left) + _size(node->right);
    }

    int _qnt_folhas(Node* node) {
        if (node == nullptr)
            return 0;

        if (node->left == nullptr && node->right == nullptr)
            return 1;

        return _qnt_folhas(node->left) + _qnt_folhas(node->right);
    }

    Node*   _excluir_folhas(Node* node) {
        if (node == nullptr)
            return nullptr;

        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }

        node->left = _excluir_folhas(node->left);
        node->right = _excluir_folhas(node->right);
        return node;
    }

    int _qnt_nos_internos(Node* node) {
        if (node == nullptr)
            return 0;

        if (node->left == nullptr && node->right == nullptr)
            return 0;

        return 1 + _qnt_nos_internos(node->left) + _qnt_nos_internos(node->right);
    }

    int _maior(Node* node) {
        if (node == nullptr)
            throw "arvore vazia";

        if (node->right == nullptr)
            return node->key;

        return _maior(node->right);
    }

    Node* _maior_node(Node* node) {
        if (node->right == nullptr)
            return node;

        return _maior_node(node->right);
    }

    Node* _find(Node* node, int key) {
        if (node == nullptr)
            return nullptr;

        if (node->key == key)
            return node;

        if (node->key > key)
            return _find(node->left, key);

        if (node->key < key)
            return _find(node->right, key);
    }

    Node* _excluir(Node* node, int key) {
        if (node == nullptr)
            return nullptr;

        if (key < node->key) {
            node->left = _excluir(node->left, key);
        } else if (key > node->key) {
            node->right = _excluir(node->right, key);
        } else {
            // Folha (sem filhos)
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            // Sem filho direito
            if (node->right == nullptr) {
                Node* aux = node->left;
                delete node;
                return aux;
            }

            // Sem filho esquerdo
            if (node->left == nullptr) {
                Node* aux = node->right;
                delete node;
                return aux;
            }

            Node* aux = _maior_node(node->left);
            node->key = aux->key;
            node->left = _excluir(node->left, aux->key);
        }

        return node;
    }


    void bshow(Node *node, std::string heranca) {
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->right , heranca + "r");
        for(int i = 0; i < (int) heranca.size() - 1; i++)
            std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
        if(heranca != "")
            std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
        if(node == nullptr){
            std::cout << "#" << std::endl;
            return;
        }
        std::cout << node->key << std::endl;
        if(node != nullptr && (node->left != nullptr || node->right != nullptr))
            bshow(node->left, heranca + "l");
    }
};

#endif BTREE