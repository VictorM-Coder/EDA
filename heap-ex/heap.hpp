#ifndef HEAP_HPP
#define HEAP_HPP
#include "vector"
#include <iostream>

template<typename T>
class Heap {
private:
    int heapSize;
    std::vector<T> vector;
public:
    Heap() {
        heapSize = 0;
        vector.push_back(T());
    }

    Heap(const std::vector<T>& initVector) {
        heapSize = initVector.size();
        vector.push_back(T());

        for (const T element: initVector) {
            vector.push_back(element);
        }

        buildHeap(this);
    }

    void insert(const T& newElement) {
        vector.push_back(newElement);
        heapSize++;
        fixUp(heapSize);
    }

    int size() const {
        return heapSize;
    }

    bool isEmpty() const {
        return heapSize == 0;
    }

    const T& top() const {
        if (!isEmpty()) {
            return vector[1];
        }
        throw std::underflow_error("empty heap");
    }

    void pop() {
        if (!isEmpty()) {
            vector[1] = vector[heapSize];
            heapSize--;
            fixDown(1);
        }
    }

private:
    void fixDown(int index) {
        while (index*2 <= heapSize) {
            int left = index*2;
            int right = left+1;

            int max = index;

            if (vector[index] < vector[left]) {
                max = left;
            }
            if (right <= heapSize && vector[max] < vector[right]) {
                max = right;
            }

            if (max != index) {
                T aux = vector[index];
                vector[index] = vector[max];
                vector[max] = aux;
                index = max;
            } else {
                break;
            }
        }
    }

    void fixUp(int index) {
        while (index != 1) {
            int parent = index/2;
            if (vector[index] > vector[parent]) {
                T aux = vector[index];
                vector[index] = vector[parent];
                vector[parent] = aux;
                index = parent;
            }
        }
    }

    void buildHeap(const std::vector<T>& initVector) {
        for (int i = initVector.size(); i >= 1; i--) {
            fixDown(i);
        }
    }
};

#endif