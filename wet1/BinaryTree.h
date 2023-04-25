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

        //Remove the node with the given id
        //Returns StatusType:Success if such a node exists and StatusType:Failiure otherwise
        StatusType remove(int id);

        //Returns the val for the node with the given id
        //If no such node exists, returns nullptr
        shared_ptr<int> get(int id);

        //Prints the values of all nodes using inorder (left,parent,right)
        void printInOrder();

        //Prints the values of all nodes using postorder (parent,left,right)
        void printPreOrder();

        //Prints the values of all nodes using postorder (left,right,parent)
        void printPostOrder();
        
    private:
        class Node;

        void printInOrder(shared_ptr<Node> node);
        void printPreOrder(shared_ptr<Node> node);
        void printPostOrder(shared_ptr<Node> node);
        void removeNode(shared_ptr<Node> node, shared_ptr<Node> parent);

        shared_ptr<Node> root;
};

class BinaryTree::Node{
    public:
        Node(int id, shared_ptr<int> val, shared_ptr<Node> parent): id(id), val(val) {}
        shared_ptr<Node> getLeft()
        {
            return left;
        }
        shared_ptr<Node> getRight()
        { 
            return right;
        }
        void setLeft(shared_ptr<Node> left)
        {
            this->left = left;
        }
        void setRight(shared_ptr<Node> right)
        {
            this->right = right;
        }
        void replaceSon(shared_ptr<Node> son, shared_ptr<Node> newSon)
        {
            if (son == left)
            {
                setLeft(newSon);
            }
            else
            {
                setRight(newSon);
            }
            
        }
        void swapVal(shared_ptr<Node> other)
        {
            other->val.swap(val);
        }
        shared_ptr<int> getVal()
        {
            return val;
        }
        int getId()
        {
            return id;
        }

    private:
        int id;
        shared_ptr<int> val;
        shared_ptr<Node> left, right;
};

BinaryTree::BinaryTree(): root(new Node(-1, shared_ptr<int>(), shared_ptr<Node>())) { }

StatusType BinaryTree::insert(int id, shared_ptr<int> val)
{
    shared_ptr<Node> node = root->getRight(), parent = root;
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


StatusType BinaryTree::remove(int id)
{
    shared_ptr<Node> node = root->getRight(), parent = root;
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

shared_ptr<int> BinaryTree::get(int id)
{
    shared_ptr<Node> node = root;
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
        node->swapVal(next);
        removeNode(next, nextParent);
    }
            
}

void BinaryTree::printInOrder()
{
    cout << endl << "In:  ";
    printInOrder(root->getRight());   
}

void BinaryTree::printInOrder(shared_ptr<Node> node)
{
    if (node == nullptr)
    {
        return;
    }
    printInOrder(node->getLeft());
    cout << *node->getVal() << ", ";
    printInOrder(node->getRight());
}

void BinaryTree::printPreOrder()
{
    cout << endl << "Pre: ";
    printPreOrder(root->getRight());
}

void BinaryTree::printPreOrder(shared_ptr<Node> node)
{
    if (node == nullptr)
    {
        return;
    }
    cout << *node->getVal() << ", ";
    printPreOrder(node->getLeft());
    printPreOrder(node->getRight());
}

void BinaryTree::printPostOrder()
{
    cout << endl << "Post: ";
    printPostOrder(root->getRight());
}

void BinaryTree::printPostOrder(shared_ptr<Node> node)
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