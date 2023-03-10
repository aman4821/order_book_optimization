# This repository implements an optimized version of an HFT Limit Order Book

The key idea in this implementation is to use a combination of AVL Tree along with a Priority Queue (for FIFO functionality) as opposed to using a double-ended linked list in the original implementation for the limit order book.

I would recommend going through the files in the following sequence to understand the underlying code

```
order.h 

test_order.cpp 

limit_avl_ask.h 

test_limit_avl_ask.cpp 

limit_avl_bid.h 

test_limit_avl_bid.cpp
```

We model the order book as an AVL Tree where each node of the tree represents a limit price and is modeled as a priority queue of orders for that particular limit price. We use two separate AVL trees for the ask and the bid side (The trees for the ask and bid side would be a mirror image of one another in a sense since the prices increase in opposite orders on the ask and bid side).

Each order is a C++ structure that has the following attributes: 

    1. orderID -> The ID associated with each ask/bid order
    
    2. orderLimitPrice -> The limit price at which the order exists
    
    3. orderShares -> Number of shares for a particular order
    
    4. orderEntryTime -> Time at which the order was triggered
    
    5. isOrderAsk -> Whether the order is from ask or bid side
    
    
The AVL Tree in turn consists of each node representing a limit price and consisting of a priority queue of this order structure.


The intuition behind choosing a priority queue is extremely fast access, caching, and retrieval. Searching in a priority queue is of logarithmic order as opposed to asymptomatic linear ordering in a linked list. Another benefit of using a priority queue is that it provides a nice ordering based on how we want to structure the data. For instance, we can order the priority queue based on any of the attributes of the order (such as orderEntryTime, orderShares, etc). Accessing the min/max element in the priority queue is extremely fast and is of the order of O(1).

Source: https://news.ycombinator.com/item?id=333814

## *** Alternate Methods to Optimize the Performace ***

### 1. Parallelization

We can use CUDA and Multi-Threading to further boost the performance at run time on the GPU/Compiler level. The key idea here is to understand what operations, threads, or processes to optimize. In particular, we would like to keep a history/log of transactions and store transactions in separate threads to parallelize the process of the bid/ask and capitalize on the run time. With a priority queue structure implemented over here, we can parallelize the performance per thread/block using shared memory access. 

Source: https://forums.developer.nvidia.com/t/priority-queues/14667

### 2. Alternate Data Structures

Another way to further optimize the performance would be to replace AVL trees with B Trees. In a B Tree, each node contains a large number of children (as opposed to at max two children in AVL Tree) leading to sparsity and reducing the depth of the tree.

Source: https://www.javatpoint.com/binary-search-tree-vs-avl-tree


### 3. Reinforcement Learning

Although this is not related to improving the performance on a Data Structure or Compiler level, I found this to be an interesting read nonetheless and thought it would be worthwhile to mention how RL and Deep RL can be used to model multi-agent simulation behavior in Limit Order Book Transactions.

Source: https://arxiv.org/pdf/2006.05574.pdf \
Source: https://stanford.edu/~ashlearn/RLForFinanceBook/chapter9.pdf

## *** Coding Style - Design Practices ***

While coding up this implementation, I kept in mind the following features for an ideal coding style

```
1. Readability

2. Refactorability

3. Ease of modifying the code to suit future needs
```
With these ideas in mind, the following coding practices have been used 

```
1. Descriptive Variable Names

All the variable names used in the code are descriptive and self-explanatory.

2. Descriptive Function Names

All the function names used in the code are descriptive and self-explanatory. 
Each function name exactly specifies what the function intends to do along with the function return type.

3. Avoiding Magic Numbers

I've used const variables to avoid the use of magic numbers in the code. This ensures better readability and efficient 
refactoring along with ease of error handling.

```




