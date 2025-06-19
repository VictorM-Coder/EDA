//
// Created by marti on 05/06/2025.
//

#ifndef HEAPS_MIN_HEAP_HPP
#define HEAPS_MIN_HEAP_HPP
#include "vector"
#include "iostream"

class min_heap {
private:
    std::vector<int> _vector;

public:
    int size() {
        return _vector.size()-1;
    }

    min_heap() {
        _vector.push_back(int());
    }

    int getMin() {
        if (size() > 0) {
            return _vector[1];
        }
        throw "underflow error";
    }

    void push(int key) {
        minHeap_insert(_vector, key);
    }

    void pop() {
        minHeap_extractMin(_vector);
    }

    void show() {
        std::cout << "[";
        for (int i = 1; i <= size(); i++) {
            std::cout << _vector[i];
            if (i != size()) {
                std::cout << ", ";
            }
        }
        std::cout << "]\n";
    }

private:
    void minFixUp(std::vector<int>& A, int i) {
        int p = i/2;

        while (p >= 1 && A[i] < A[p]) {
            int aux = A[i];
            A[i] = A[p];
            A[p] = aux;

            i = p;
            p = i/2;
        }
    }

    void minHeap_decreaseKey(std::vector<int>& A, int i, int newKey) {
        if (newKey > A[i]) {
            throw "invalid key";
        }
        A[i] = newKey;
        minFixUp(A, i);
    }

    void minFixDown(std::vector<int>& A, int i) {
        while (2*i <= size()) {
            int i_left = 2*i;
            int i_right = i_left+1;
            int i_min = i;

            if (i_left <= size() && A[i_left] < A[i_min]) {
                i_min = i_left;
            }

            if (i_right <= size() && A[i_right] < A[i_min]) {
                i_min = i_right;
            }

            if (i != i_min) {
                int aux = A[i];
                A[i] = A[i_min];
                A[i_min] = aux;

                i = i_min;
            } else {
                break;
            }
        }
    }

    void minHeap_increaseKey(std::vector<int>& A, int i, int newKey) {
        if (newKey < A[i]) {
            throw "invalid key";
        }
        A[i] = newKey;
        minFixDown(A, i);
    }

    void minHeap_insert(std::vector<int>& A, int key) {
        A.push_back(key);
        minFixUp(A, size());
    }

    void minHeap_extractMin(std::vector<int>& A) {
        A[1] = A[size()];
        minFixDown(A, 1);
    }
};


#endif //HEAPS_MIN_HEAP_HPP
