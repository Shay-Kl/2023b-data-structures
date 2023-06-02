#ifndef __tree2_h__
#define __tree2_h__
#include <memory>
#include <iostream>
#include "exceptions.h"
#include "Customer.h"

using namespace std;

class MemberTree
{

public:
    class Node;

    //Default C'tor
    MemberTree(): m_root(nullptr) {}
    
    //Insert a pointer to a given customer into the tree
    //If a customer with the id already exists, throw a KeyAlreadyExists exception instead
    //If allocation fails, bad alloc is thrown and the tree doesn't change
    //O(log n)
    void insert(Customer* Customer);

    //Return a reference to a customer associated with a given id
    //If a customer with that id doesn't exist, throw a KeyMissing exception instead
    //O(log n)
    Customer& get(int id) const;

    //Gives out a discount prize of amount to all members with ids greater or equal to lowerLimit and lesser than upperLimit
    //O(log n)
    void addPrize(int lowerLimit, int upperLimit, int amount);

    //Resets the expenses of all members
    //O(n)
    void resetExpenses();

    //Prints out ids and expenses of all customers in order
    //O(n)
    friend ostream& operator<<(ostream& os, MemberTree& tree);


private:
    unique_ptr<Node> m_root;

    //Recursion helper functions
    void insertAux(unique_ptr<Node>& curNode, Node* newNode);
    Customer& getAux(const unique_ptr<Node>& curNode, int id) const;
    void addPrizeAux(unique_ptr<Node>&, int lowerLimit, int upperLimit, int amount);
    void resetExpensesAux(unique_ptr<Node>& curNode);
    void inOrder(unique_ptr<Node>& curNode, ostream& os);

    //AVL balancing functions
    void balance(unique_ptr<Node>& node);
    void rightRotate(unique_ptr<Node>& y);
    void leftRotate(unique_ptr<Node>& y);
};


class MemberTree::Node
{
public:
    Customer* customer;
    unique_ptr<Node> left = nullptr, right = nullptr;
    
    Node(Customer* customer): customer(customer), minId(customer->getId()), maxId(customer->getId()) {}

    //Getter functions
    int getMinId();
    int getMaxId();
    int getBalanceFactor();
    int getHeight();


    //Propogate the node's discount (make it trickle down)
    void propogate();

    //Update the node's unique members (height,minId, maxId) based on the node's children
    void update();
    
    //Increase a node's lazy discount counter
    void lazyDiscount(int amount);

private:
    //Increase the node's lazy discount by a given amount
    int minId; //Mainimum id in node's subtree
    int maxId; //Maximum id in node's subtree
    int height = 0; //Node's height
    int discount = 0; //Discount applied to all nodes in node's subtree
};

#endif