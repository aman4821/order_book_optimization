/*
This header file implements the order data structure.

Each order entity consists of the following attributes
    1. orderID
    2. orderLimitPrice
    3. orderShares
    4. orderEntryTime
    5. isOrderAsk

The set of orders for a given orderLimitPrice is implemented as a heap (minHeap). This minHeap (or conversely the set of orders for a given
orderLimitPrice) are the nodes of the AVL Tree which constitutes the Limit Order Book (for both bid and ask)

The intuition behind chosing a minHeap is that the orders are time indexed and we need to implement a FIFO functionality.
With a minHeap, the first order is always at the root of the heap thus making caching and retreival extremely fast.
*/

#include <algorithm>

struct order {
    int orderID;
    int orderLimitPrice;
    int orderShares;
    int orderEntryTime;
    bool isOrderAsk;

    explicit order(int orderID_, int orderLimitPrice_, int orderShares_, int orderEntryTime_, bool isOrderAsk_) {
        orderID = orderID_;
        orderLimitPrice = orderLimitPrice_;
        orderShares = orderShares_;
        orderEntryTime = orderEntryTime_;
        isOrderAsk = isOrderAsk_;
    }
};

// Comparator function to implement a minHeap based on orderEntryTime
struct order_entry_time_comparison {
    bool operator() (order const& firstOrder, order const& secondOrder) const {
        return firstOrder.orderEntryTime > secondOrder.orderEntryTime;
    }
};