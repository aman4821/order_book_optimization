/*
This header file implements the limits data structure for the bid side.

In this implementation, limit is modelled as an AVL Tree. Each node of limit corresponds to the current limitPrice and each node of limit
constitutes of a set of orders for that particular price modelled as a Max Heap.

Each limit entity consists of the following attributes:
    1. limitPrice
    2. std::vector<order> currentLimitOrders 
*/

#include <iostream>
#include "order.h"

const int HEIGHT_DIFF_SUBTREES = 2;

using namespace std;

class AVLBidTree
{
    struct node
    {
        int limitPrice;
        int height;
        std::vector<order> currentLimitOrders;

        node* left;
        node* right;
    };

    node* root;

    void createEmptyTree(node* root)
    {
        if(root == NULL)
            return;

        createEmptyTree(root->left);
        createEmptyTree(root->right);

        delete root;
    }

    node* insertNode(int orderID, int orderLimitPrice, int orderShares, int orderEntryTime, int isOrderAsk, node* root)
    {
       order currOrder = order(orderID, orderLimitPrice, orderShares, orderEntryTime, isOrderAsk);

       if(root == NULL)
        {
            root = new node;
            root->limitPrice = orderLimitPrice;
            root->height = 0;
            root->left = root->right = NULL;
            root->currentLimitOrders.push_back(currOrder);
        }

        else if(orderLimitPrice > root->limitPrice)
        {
            root->left = insertNode(orderID, orderLimitPrice, orderShares, orderEntryTime, isOrderAsk, root->left);
            if(getTreeHeight(root->left) - getTreeHeight(root->right) == HEIGHT_DIFF_SUBTREES)
            {
                if(orderLimitPrice > root->left->limitPrice)
                    root = rotateRightOnce(root);
                else
                    root = rotateRightTwice(root);
            }
        }

        else if(orderLimitPrice < root->limitPrice)
        {
            root->right = insertNode(orderID, orderLimitPrice, orderShares, orderEntryTime, isOrderAsk, root->right);
            if(getTreeHeight(root->right) - getTreeHeight(root->left) == HEIGHT_DIFF_SUBTREES)
            {
                if(orderLimitPrice < root->right->limitPrice)
                    root = rotateLeftOnce(root);
                else
                    root = rotateLeftTwice(root);
            }
        }

        else {
            root->currentLimitOrders.push_back(currOrder);
            std::make_heap(root->currentLimitOrders.begin(), root->currentLimitOrders.end(), max_heap_limit_price_comparator());
        }

        root->height = max(getTreeHeight(root->left), getTreeHeight(root->right))+1;
        return root;
    }

    node* rotateRightOnce(node* &root)
    {
        node* tempNodeNode = root->left;
        root->left = tempNodeNode->right;
        tempNodeNode->right = root;
        root->height = max(getTreeHeight(root->left), getTreeHeight(root->right))+1;
        tempNodeNode->height = max(getTreeHeight(tempNodeNode->left), root->height)+1;
        return tempNodeNode;
    }

    node* rotateLeftOnce(node* &root)
    {
        node* tempNodeNode = root->right;
        root->right = tempNodeNode->left;
        tempNodeNode->left = root;
        root->height = max(getTreeHeight(root->left), getTreeHeight(root->right))+1;
        tempNodeNode->height = max(getTreeHeight(root->right), root->height)+1 ;
        return tempNodeNode;
    }

    node* rotateLeftTwice(node* &root)
    {
        root->right = rotateRightOnce(root->right);
        return rotateLeftOnce(root);
    }

    node* rotateRightTwice(node* &root)
    {
        root->left = rotateLeftOnce(root->left);
        return rotateRightOnce(root);
    }

    node* getSmallestElement(node* root)
    {
        if(root == NULL)
            return NULL;

        else if(root->left == NULL)
            return root;

        else
            return getSmallestElement(root->left);
    }

    node* getMaxElement(node* root)
    {
        if(root == NULL)
            return NULL;

        else if(root->right == NULL)
            return root;

        else
            return getMaxElement(root->right);
    }

    node* removeNode(order* currOrder, node* root)
    {
        int currOrderID = currOrder->orderID;
        int currOrderLimitPrice = currOrder->orderLimitPrice;

        node* tempNode;

        // Element not found
        if(root == NULL)
            return NULL;

        // Searching for element
        else if(currOrderLimitPrice > root->limitPrice)
            root->left = removeNode(currOrder, root->left);

        else if(currOrderLimitPrice < root->limitPrice)
            root->right = removeNode(currOrder, root->right);

        // Case 1 : Two Children
        else if(root->left && root->right)
        {
            tempNode = getSmallestElement(root->right);
            root->limitPrice = tempNode->limitPrice;
            root->right = removeNode(currOrder, root->right);
        }
        
        // Case 2 : At most one child
        else
        {
            tempNode = root;
            if(root->left == NULL)
                root = root->right;

            else if(root->right == NULL)
                root = root->left;

            delete tempNode;
        }

        if(root == NULL)
            return root;

        root->height = max(getTreeHeight(root->left), getTreeHeight(root->right))+1;

        if(getTreeHeight(root->left) - getTreeHeight(root->right) == HEIGHT_DIFF_SUBTREES)
        {
            // right right case
            if(getTreeHeight(root->left->left) - getTreeHeight(root->left->right) == 1)
                return rotateLeftOnce(root);

            // right left case
            else
                return rotateLeftTwice(root);
        }
        
        else if(getTreeHeight(root->right) - getTreeHeight(root->left) == HEIGHT_DIFF_SUBTREES)
        {
            // left left case
            if(getTreeHeight(root->right->right) - getTreeHeight(root->right->left) == 1)
                return rotateRightOnce(root);

            // left right case
            else
                return rotateRightTwice(root);
        }
        return root;
    }

    int getTreeHeight(node* root)
    {
        return (root == NULL ? -1 : root->height);
    }

    int getBalanceFactor(node* root)
    {
        if(root == NULL)
            return 0;
        else
            return getTreeHeight(root->left) - getTreeHeight(root->right);
    }

    void printInOrderTraversal(node* root)
    {
        if(root == NULL)
            return;

        printInOrderTraversal(root->left);

        for(auto& itr : root->currentLimitOrders) {
            std::cout << "\n orderEntryTime" << " " << itr.orderEntryTime;
            std::cout << "\n orderID" << " " << itr.orderID;
            std::cout << "\n orderLimitPrice" << " " << itr.orderLimitPrice;
            std::cout << "\n orderShares" << " " << itr.orderShares;
            std::cout << "\n----------------";
        }

        printInOrderTraversal(root->right);
    }

public:
    AVLBidTree()
    {
        root = NULL;
    }

    void insertNode(int orderID, int orderLimitPrice, int orderShares, int orderEntryTime, int isOrderAsk)
    {
        root = insertNode(orderID, orderLimitPrice, orderShares, orderEntryTime, isOrderAsk, root);
    }

    void removeNode(order* currOrder)
    {
        root = removeNode(currOrder, root);
    }

    void display()
    {
        printInOrderTraversal(root);
        cout << endl;
    }
};