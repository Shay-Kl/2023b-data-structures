#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__
#include <memory>
#include <iostream>
#include "wet1util.h"
using namespace std;

class BinaryTree
{
    public:
        //Initializes a new empty tree
        //Tree is initalized with an empty node, the rest of the tree is to the right of this node
        //This is to simplify what happens when you remove the first node inserted into the tree
        BinaryTree();

        //Inserts a new node into the tree with the given id and val
        //Throws FailiureException if the given id already exists
        void insert(int id, int& val);

        //Returns the val for the node with the given id
        //Throw FailiureException if the given id doesn't exist
        int& get(int id);

        //Remove the node with the given id
        //Throws FailiureException if the given id doesn't exist
        void remove(int id);

        //Returns the number of elements in the tree
        int getSize();

        //Print the tree's values using all 3 ordering methods
        friend ostream& operator<<(ostream& os, const BinaryTree& tree);
        
        class FailureException{};
    private:
        class Node;

        void printInOrder(shared_ptr<Node> node) const;
        void printPreOrder(shared_ptr<Node> node) const;
        void printPostOrder(shared_ptr<Node> node) const;
        void removeNode(shared_ptr<Node> node, shared_ptr<Node> parent);

        shared_ptr<Node> m_root;
        int m_size = 0;
};

class BinaryTree::Node
{
    public:
        //Standard constructor 
        Node(int id, shared_ptr<int> val, Node* parent):
            m_id(id), m_val(val), m_parent(parent) {}

        //Default constructor for root
        Node():
            m_id(-1), m_val() {}
        shared_ptr<Node> getLeft()
        {
            return m_left;
        }
        shared_ptr<Node> getRight()
        { 
            return m_right;
        }
        Node* getParent()
        { 
            return m_parent;
        }
        int& getVal()
        {
            return *m_val;
        }
        int getId() const
        {
            return m_id;
        }

        //Sets one of the node's children as newSon
        //Choice of which son to replace is based on the id of newSon relative to the node
        void setSon(shared_ptr<Node> newSon)
        {
            if(newSon->m_id > m_id)
            {
                m_right = newSon;
            }
            else{
                m_left = newSon;
            }
            newSon->m_parent = this;
        }

        //Removes a node's given son
        void removeSon(shared_ptr<Node> son)
        {
            if(m_left->m_id == son->m_id)
            {
                m_left = nullptr;
            }
            else if(m_right->m_id = son->m_id)
            {
                m_right = nullptr;
            }
        }

        //Swap out the values and ids of this node and the other node
        //Essentialy swaps the 2 node's locations in the tree
        void swap(shared_ptr<Node> other)
        {
            int idTemp = m_id;
            m_id = other->m_id;
            other->m_id = idTemp;

            other->m_val.swap(m_val);
        }

    private:
        int m_id;
        shared_ptr<int> m_val;
        shared_ptr<Node> m_left, m_right;
        Node* m_parent;
};


BinaryTree::BinaryTree(): m_root(new Node()) { }

void BinaryTree::insert(int id, int& val)
{
    shared_ptr<Node> node = m_root->getRight(), parent = m_root;
    while(node)
    {
        parent = node;
        int curId = node->getId();
        if (curId == id)
        {
            throw BinaryTree::FailureException();
        }
        else if (curId > id)
        {
            node = node->getLeft();
        }
        else
        {
            node = node->getRight();
        }
    }
    parent->setSon(shared_ptr<Node>(new Node(id, shared_ptr<int>(new int(val)), parent.get())));
    m_size++;
}

int& BinaryTree::get(int id)
{
    shared_ptr<Node> node = m_root->getRight();
    while (node)
    {
        int curId = node->getId();
        if (curId == id)
        {
            return node->getVal();
        }
        else if (curId > id)
        {
            node = node->getLeft();
        }
        else{
            node = node->getRight();
        }
    }
    throw BinaryTree::FailureException();
    
}

void BinaryTree::remove(int id)
{
    shared_ptr<Node> node = m_root->getRight(), parent = m_root;
    while(node)
    {
        int curId = node->getId();
        if (curId == id)
        {
            removeNode(node, parent);
            return;
        }
        parent = node;
        if (curId > id)
        {
            node = node->getLeft();
        }
        else
        {
            node = node->getRight();
        }
    }
    throw BinaryTree::FailureException();
    m_size--;
}

//Removes a node you have a pointer to from the tree
void BinaryTree::removeNode(shared_ptr<Node> node, shared_ptr<Node> parent)
{
    shared_ptr<Node> left = node->getLeft(), right = node->getRight();

    if (!left && !right)
    {
        parent->removeSon(node);
    }
    else if (!left)
    {
        parent->setSon(right);
    }
    else if(!right){
        parent->setSon(left);
    }
    else{
        shared_ptr<Node> next = node->getRight(), nextParent = node;
        while(next->getLeft()!=nullptr)
        {
            nextParent = next;
            next=next->getLeft();
        }
        node->swap(next);
        removeNode(next, nextParent);
    }
            
}

int BinaryTree::getSize()
{
    return m_size;
}

ostream& operator<<(ostream& os, const BinaryTree& tree){
    os << endl << "Pre:  ";
    tree.printPreOrder((tree.m_root)->getRight());
    os << endl << "In:   ";
    tree.printInOrder((tree.m_root)->getRight());
    os << endl << "Post: ";
    tree.printPostOrder((tree.m_root)->getRight());
    os << endl;
    return os;
}


void BinaryTree::printInOrder(shared_ptr<Node> node) const
{
    if (node == nullptr)
    {
        return;
    }
    printInOrder(node->getLeft());
    cout << node->getVal() << ", ";
    printInOrder(node->getRight());
}

void BinaryTree::printPreOrder(shared_ptr<Node> node) const
{
    if (node == nullptr)
    {
        return;
    }
    cout << node->getVal() << ", ";
    printPreOrder(node->getLeft());
    printPreOrder(node->getRight());
}

void BinaryTree::printPostOrder(shared_ptr<Node> node) const
{
    if (node == nullptr)
    {
        return;
    }
    printPostOrder(node->getLeft());
    printPostOrder(node->getRight());
    cout << node->getVal() << ", ";
}
#endif // __BINARYTREE_H__