/*
Program to test the "limit_avl_bid.h" module.
*/

#include <iostream>
#include <vector>
#include "limit_avl_bid.h"

const int MAIN_METHOD_RETURN_VALUE = 0;

int main()
{
    AVLBidTree tree;
    
    std::vector<order> currentOrders;

    currentOrders.push_back(order(1, 500, 10, 3, false)); // orderID, orderLimitPrice, orderShares, orderEntryTime, isOrderAsk
    currentOrders.push_back(order(2, 500, 20, 0, false));
    
    currentOrders.push_back(order(3, 100, 5, 4, false));
    currentOrders.push_back(order(4, 100, 30, 1, false));
    currentOrders.push_back(order(5, 100, 50, 2, false));

    currentOrders.push_back(order(6, 200, 20, 5, false));
    currentOrders.push_back(order(7, 200, 100, 6, false));

    currentOrders.push_back(order(8, 300, 50, 8, false));

    currentOrders.push_back(order(9, 400, 80, 9, false));
    currentOrders.push_back(order(10, 400, 45, 7, false));


    std::make_heap(currentOrders.begin(), currentOrders.end(), max_heap_limit_price_comparator());

    for(auto& order : currentOrders) {
        tree.insertNode(order.orderID, order.orderLimitPrice, order.orderShares, order.orderEntryTime, order.isOrderAsk);
    }


    tree.display();

    return MAIN_METHOD_RETURN_VALUE;
}