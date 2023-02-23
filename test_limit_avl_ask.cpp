/*
Program to test the "limit_avl_ask.h" module.
*/

#include <iostream>
#include <vector>
#include "limit_avl_ask.h"

int main()
{
    AVLAskTree tree;
    
    std::vector<order> currentOrders;

    currentOrders.push_back(order(1, 500, 10, 3, true)); // orderID, orderLimitPrice, orderShares, orderEntryTime, isOrderAsk
    currentOrders.push_back(order(2, 500, 20, 0, true));
    
    currentOrders.push_back(order(3, 100, 5, 4, true));
    currentOrders.push_back(order(4, 100, 30, 1, true));
    currentOrders.push_back(order(5, 100, 50, 2, true));

    currentOrders.push_back(order(6, 200, 20, 5, true));
    currentOrders.push_back(order(7, 200, 100, 6, true));

    currentOrders.push_back(order(8, 300, 50, 8, true));

    currentOrders.push_back(order(9, 400, 80, 9, true));
    currentOrders.push_back(order(10, 400, 45, 7, true));


    std::make_heap(currentOrders.begin(), currentOrders.end(), min_heap_limit_price_comparator());

    for(auto& order : currentOrders) {
        tree.insertNode(order.orderID, order.orderLimitPrice, order.orderShares, order.orderEntryTime, order.isOrderAsk);
    }

    tree.display();

    return 0;
}