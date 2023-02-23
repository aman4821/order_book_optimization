/*
Program to test the "order.h" module.

We create a vector of order structures and convert them to a minHeap.
*/

#include <iostream>
#include <vector>
#include "order.h"

int main() {
    std::vector<order> currentOrders;

    currentOrders.push_back(order(1, 100, 10, 3, true)); // orderID, orderLimitPrice, orderShares, orderEntryTime, isOrderAsk
    currentOrders.push_back(order(2, 100, 20, 0, true));
    currentOrders.push_back(order(3, 100, 5, 4, true));
    currentOrders.push_back(order(4, 100, 30, 1, true));
    currentOrders.push_back(order(5, 100, 50, 2, true));

    std::make_heap(currentOrders.begin(), currentOrders.end(), order_entry_time_comparison());

    assert(currentOrders.front().orderEntryTime == 0);
    assert(currentOrders.front().orderShares == 20);

    return 0;
}