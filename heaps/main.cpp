#include <iostream>
#include "min_heap.hpp"

int main() {
    min_heap* minHeap = new min_heap();

    minHeap->push(1);
    minHeap->push(2);
    minHeap->push(3);
    minHeap->push(4);
    minHeap->push(5);
    minHeap->push(6);
    minHeap->push(-1);
    minHeap->show();
    minHeap->pop();
    minHeap->show();
    minHeap->push(-2);
    minHeap->push(-4);
    minHeap->push(20);
    minHeap->push(30);
    minHeap->show();
    return 0;
}
