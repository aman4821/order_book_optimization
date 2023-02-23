This repository implements an optimized version of a HFT Limit Order Book (LOB)

The key idea in this implementation is to use a combination of AVL Tree along with a Priority Queue (for FIFO functionality) as opposed to using a double ended linked list in the original implementation for the limit order book.

We model the order book as an AVL Tree where each node of the tree represents a limit price and is modelled as a priority queue of orders for that particular limit price. We use two separate AVL trees for the ask and the bid side (The trees for ask and bid side would be mirror image of one another in a sense since the prices increase in different orders in the ask and bid side).

Each order is a C++ structure that has the following attributes: 

    1. orderID 
    2. orderLimitPrice 
    3. orderShares 
    4. orderEntryTime 
    5. isOrderAsk 
    
    
The AVL Tree in turn consists of each node represnting a limit price and consisting of a priority queue of this order structure based on the orderEntryTime.




