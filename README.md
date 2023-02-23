## This repository implements an optimized version of a HFT Limit Order Book (LOB)

The key idea in this implementation is to use a combination of AVL Tree along with a Priority Queue (for FIFO functionality) as opposed to using a double ended linked list in the original implementation for the limit order book.

We model the order book as an AVL Tree where each node of the tree represents a limit price and is modelled as a priority queue of orders for that particular limit price. We use two separate AVL trees for the ask and the bid side (The trees for ask and bid side would be mirror image of one another in a sense since the prices increase in different orders in the ask and bid side).

Each order is a C++ structure that has the following attributes: 

    1. orderID 
    2. orderLimitPrice 
    3. orderShares 
    4. orderEntryTime 
    5. isOrderAsk 
    
    
The AVL Tree in turn consists of each node represnting a limit price and consisting of a priority queue of this order structure.


The intuition behind choosing a priority queue is extremely fast access, caching and retreival. Searching in a priority queue is of logarithmic order as opposed to asymptomatic linear ordering in a linked list. Another benefit of using a priority queue is that it provides a nice ordering based on how we want to structure the data. For instance, we can order the priority queue based on any of the attributes of the order (such as orderEntryTime, orderShares etc). Accessing the min/max element in priority queue is extremely fast and is of the order of O(1).

Source : https://news.ycombinator.com/item?id=333814



