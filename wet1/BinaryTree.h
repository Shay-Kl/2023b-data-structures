#ifndef __BINARYTREE_H__
#define __BINARYTREE_H__
#include <memory>
#include <iostream>
#include "wet1util.h"
using namespace std;

class BinaryTree{
    public:
        //Initializes a new empty tree
        //Tree is initalized with an empty node, the rest of the tree is to the right of this node
        //This is to simplify what happens when you remove the first node inserted into the tree
        BinaryTree();

        //Inserts a new node into the tree with the given id and val
        //Returns StatusType:Success if such a node doesn't exist and StatusType:Failiure otherwise
        StatusType insert(int id, shared_ptr<int> val);

        //Returns the val for the node with the given id
        //If no such node exists, returns nullptr
        shared_ptr<int> get(int id) const;

        //Remove the node with the given id
        //Returns StatusType:Success if such a node exists and StatusType:Failiure otherwise
        StatusType remove(int id);

        //Print the tree's values using all 3 ordering methods
        friend ostream& operator<<(ostream& os, const BinaryTree& tree);
        
    private:
        class Node;

        void printInOrder(shared_ptr<Node> node) const;
        void printPreOrder(shared_ptr<Node> node) const;
        void printPostOrder(shared_ptr<Node> node) const;
        void removeNode(shared_ptr<Node> node, shared_ptr<Node> parent);

        shared_ptr<Node> m_root;
};

class BinaryTree::Node{
    public:
        Node(int id, shared_ptr<int> val, shared_ptr<Node> parent):
            m_id(id), m_val(val) {}
        shared_ptr<Node> getLeft() const
        {
            return m_left;
        }
        shared_ptr<Node> getRight() const
        { 
            return m_right;
        }
        void setLeft(shared_ptr<Node> left)
        {
            m_left = left;
        }
        void setRight(shared_ptr<Node> right)
        {
            m_right = right;
        }
        shared_ptr<int> getVal() const
        {
            return m_val;
        }
        int getId() const
        {
            return m_id;
        }

        //Replaces a child with the same id as son with newSon
        void replaceSon(shared_ptr<Node> son, shared_ptr<Node> newSon)
        {
            if (son->m_id == m_left->m_id)
            {
                setLeft(newSon);
            }
            else if(son->m_id == m_right->m_id)
            {
                setRight(newSon);
            }
        }

        //Swap out the values and ids of this node and the other node
        //Essentialy swaps the 2 node's locations in the tree
        void swap(shared_ptr<Node> other)
        {
            int temp = m_id;
            m_id = other->m_id;
            other->m_id = temp;
            other->m_val.swap(m_val);
        }

    private:
        int m_id;
        shared_ptr<int> m_val;
        shared_ptr<Node> m_left, m_right;
};

BinaryTree::BinaryTree(): m_root(new Node(-1, shared_ptr<int>(), shared_ptr<Node>())) { }

StatusType BinaryTree::insert(int id, shared_ptr<int> val)
{
    shared_ptr<Node> node = m_root->getRight(), parent = m_root;
    while(node)
    {
        parent = node;
        int curId = node->getId();
        if (curId == id)
        {
            return StatusType::FAILURE;
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
    try
    {
        Node* newNode = new Node(id, val, parent);
        if (parent->getId() > id)
        {
            parent->setLeft(shared_ptr<Node>(new Node(id, val, parent)));
        }
        else
        {
            parent->setRight(shared_ptr<Node>(new Node(id, val, parent)));
        }
    }
    catch(exception)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

shared_ptr<int> BinaryTree::get(int id) const
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
    return nullptr;
    
}

StatusType BinaryTree::remove(int id)
{
    shared_ptr<Node> node = m_root->getRight(), parent = m_root;
    while(node)
    {
        int curId = node->getId();
        if (curId == id)
        {
            try
            {
                removeNode(node, parent);
            }
            catch(exception)
            {
                return StatusType::ALLOCATION_ERROR;
            }
            return StatusType::SUCCESS;
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
    return StatusType::FAILURE;

}

//Removes a node you have a pointer to from the tree
void BinaryTree::removeNode(shared_ptr<Node> node, shared_ptr<Node> parent)
{
    shared_ptr<Node> left = node->getLeft(), right = node->getRight();

    if (!left && !right)
    {
        parent->replaceSon(node, nullptr);
    }
    else if (!left)
    {
        parent->replaceSon(node, right);
    }
    else if(!right){
        parent->replaceSon(node, left);
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
    cout << *node->getVal() << ", ";
    printInOrder(node->getRight());
}

void BinaryTree::printPreOrder(shared_ptr<Node> node) const
{
    if (node == nullptr)
    {
        return;
    }
    cout << *node->getVal() << ", ";
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
    cout << *node->getVal() << ", ";
}
#endif // __BINARYTREE_H__