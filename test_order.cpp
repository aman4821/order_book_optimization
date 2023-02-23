/*
Program to test the "order.h" module.

We create a vector of order structures and convert them to a Min Heap and Max Heap.
*/

#include <iostream>
#include <vector>
#include "order.h"

int main() {
    std::vector<order> currentOrdersMinHeap;
    std::vector<order> currentOrdersMaxHeap;

    currentOrdersMinHeap.push_back(order(1, 100, 10, 3, true)); // orderID, orderLimitPrice, orderShares, orderEntryTime, isOrderAsk
    currentOrdersMinHeap.push_back(order(2, 200, 20, 0, true));
    currentOrdersMinHeap.push_back(order(3, 100, 5, 4, true));
    currentOrdersMinHeap.push_back(order(4, 400, 30, 1, true));
    currentOrdersMinHeap.push_back(order(5, 300, 50, 2, true));

    std::make_heap(currentOrdersMinHeap.begin(), currentOrdersMinHeap.end(), min_heap_limit_price_comparator());

    assert(currentOrdersMinHeap.front().orderEntryTime == 4);
    assert(currentOrdersMinHeap.front().orderShares == 5);

    currentOrdersMaxHeap.push_back(order(1, 100, 10, 3, true)); // orderID, orderLimitPrice, orderShares, orderEntryTime, isOrderAsk
    currentOrdersMaxHeap.push_back(order(2, 200, 20, 0, true));
    currentOrdersMaxHeap.push_back(order(3, 100, 5, 4, true));
    currentOrdersMaxHeap.push_back(order(4, 400, 30, 1, true));
    currentOrdersMaxHeap.push_back(order(5, 300, 50, 2, true));

    std::make_heap(currentOrdersMaxHeap.begin(), currentOrdersMaxHeap.end(), max_heap_limit_price_comparator());

    assert(currentOrdersMaxHeap.front().orderEntryTime == 1);
    assert(currentOrdersMaxHeap.front().orderShares == 30);

    return 0;
}