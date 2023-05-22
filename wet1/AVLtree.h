#ifndef __tree_h__
#define __tree_h__
#include <memory>
#include <iostream>
#include "exceptions.h"

using namespace std;

template <class Key, class Val>
class AVLtree
{

public:
    class Node;
    AVLtree(): m_root(nullptr), m_count(0) {}
    
    //Insert a node into the tree with key and val being copies of the parameters
    //If key exists in the tree throw a KeyAlreadyExists exception instead
    //If allocation fails, bad alloc is throw and the tree doesn't change
    // O(log n)
    void insert(Key key, Val val);

    //Insert the given node into the tree without copying its data
    //Allocation can't fail because the funciton doesn't allocate the memory
    //O(log n)
    void insertNode(Node* node);

    //Return a reference of the value for the given key
    //O(log n)
    Val& get(const Key& key) const;

    //Remove the node with the given key from the tree
    //If node doesn't exist, throw a runtime error
    //O(log n)
    void remove(const Key& key);

    //Returns the number of nodes in the tree;
    //O(1)
    int getNodeCount() const {  return m_count; }

    //Returns the tree's root node
    //O(1)
    Node* getRoot() { return m_root.get(); }

    //Returns the tree's minimum node
    //O(1)
    Node* getMin() { return m_min; }

    //Print out the tree's keys using both inorder and preorder
    //O(n)
    template <class K,class V>
    friend ostream& operator<<(ostream& os, AVLtree<K, V>& tree);


private:
    unique_ptr<Node> m_root;
    Node* m_min;
    int m_count;

    //Helper function for inserting
    void insertAux(unique_ptr<Node>& curNode, Node* newNode);

    //Helper function for getting
    Val& getAux(const unique_ptr<Node>& curNode, const Key& key) const;

    //Helper functions for removing
    Node* removeAux(unique_ptr<Node>& curNode, const Key& key);
    void removeNode(unique_ptr<Node>& toDelete);

    //Returns the leftmost node from a given node
    unique_ptr<Node>& getLeftmost(unique_ptr<Node>& curNode);

    //Helper functions for printing
    void preOrder(unique_ptr<Node>& curNode, ostream& os);
    void inOrder(unique_ptr<Node>& curNode, ostream& os);
};


template <class Key, class Val>
void AVLtree<Key,Val>::insert(Key key, Val val)
{
    insertAux(m_root, new Node(key, val));
    m_count++;
    m_min = getLeftmost(m_root).get();
}
template <class Key, class Val>
void AVLtree<Key,Val>::insertNode(Node* node)
{
    insertAux(m_root, node);
    m_count++;
    m_min = getLeftmost(m_root).get();
}
template <class Key, class Val>
void AVLtree<Key,Val>::insertAux(unique_ptr<Node>& curNode, Node* newNode)
{
    if(!curNode)
    {
        curNode.reset(newNode);
    }
    else if (curNode->key < newNode->key) 
    {
        insertAux(curNode->right, newNode);
    }
    else if(newNode->key < curNode->key)
    {
        insertAux(curNode->left, newNode);
    }
    else
    {
        delete newNode;
        throw KeyAlreadyExists();
    }
    
}

template <class Key, class Val>
Val& AVLtree<Key,Val>::get(const Key& key) const
{
    return getAux(m_root, key);
}
template <class Key, class Val>
Val& AVLtree<Key,Val>::getAux(const unique_ptr<Node>& curNode, const Key& key) const
{
    if (!curNode)
    {
        throw KeyMissing();
    }
    else if (curNode->key < key) 
    {
        return getAux(curNode->right, key);
    }
    else if(key < curNode->key)
    {
        return getAux(curNode->left, key);
    }
    else
    {
        return curNode->val;
    }
    
}

template <class Key, class Val>
void AVLtree<Key,Val>::remove(const Key& key)
{
    delete removeAux(m_root, key);
    m_count--;
    if (m_root)
    {
        m_min = getLeftmost(m_root).get();
    }
    else
    {
        m_min = nullptr;
    }
    
}

template <class Key, class Val>
typename AVLtree<Key,Val>::Node* AVLtree<Key,Val>::removeAux(unique_ptr<Node>& curNode, const Key& key)
{
    if (!curNode)
    {
        throw KeyAlreadyExists();
    }
    else if (curNode->key < key) 
    {
        return removeAux(curNode->right, key);
    }
    else if(key < curNode->key)
    {
        return removeAux(curNode->left, key);
    }
    else
    {
        Node* node = curNode.get();
        removeNode(curNode);
        return node;
    }
}

template <class Key, class Val>
void AVLtree<Key,Val>::removeNode(unique_ptr<Node>& toDelete)
{
    if (toDelete->right && toDelete->left)
    {
        
        unique_ptr<Node>& next = getLeftmost(toDelete->right);
        unique_ptr<Node> temp = move(next);
        if (toDelete->right == next)
        {
            toDelete->right = std::move(temp->right);
            temp->left = std::move(toDelete->left);
            temp->right = move(toDelete);
            toDelete = std::move(temp); 
            removeNode(toDelete->right);
        }
        else
        {
            unique_ptr<Node> right = move(toDelete->right);
            unique_ptr<Node> left = move(toDelete->left);

            toDelete->right = move(temp->right);
            temp->right = move(right);
            temp->left = move(left);
            next = move(toDelete);
            toDelete = move(temp);
            removeNode(next);
        }
        
    }
    else if(toDelete->right)
    {
        
        Node* temp = toDelete->right.release();
        toDelete.release();
        toDelete.reset(temp);
    }
    else if(toDelete->left)
    {
        Node* temp = toDelete->left.release();
        toDelete.release();
        toDelete.reset(temp);
    }
    else
    {
        toDelete.release();
        toDelete.reset();
    }
    
}

template <class Key, class Val>
unique_ptr<typename AVLtree<Key,Val>::Node>& AVLtree<Key,Val>::getLeftmost(unique_ptr<Node>& curNode)
{
    if (curNode->left)
    {
        return getLeftmost(curNode->left);
    }
    return curNode;
    
}

template <class Key,class Val>
std::ostream& operator<<(std::ostream& os, AVLtree<Key, Val>& tree)
{
    os << "Inorder: ";
    tree.inOrder(tree.m_root, os);
    os << endl << "Preorder: ";
    tree.preOrder(tree.m_root, os);
    os << endl;
    return os;
}
template <class Key, class Val>
void AVLtree<Key,Val>::inOrder(unique_ptr<Node>& curNode, ostream& os)
{
    if (!curNode)
    {
        return;
    }
    
    inOrder(curNode->left, os);
    os << curNode->key << ", ";
    inOrder(curNode->right, os);
}
template <class Key, class Val>
void AVLtree<Key,Val>::preOrder(unique_ptr<Node>& curNode, ostream& os)
{
    if (!curNode)
    {
        return;
    }
    
    os << curNode->key << ", ";
    preOrder(curNode->left, os);
    preOrder(curNode->right, os);
}

template <class Key, class Val>
class AVLtree<Key,Val>::Node
{
public:
    Key key;
    Val val;

    Node* getRight(){ return right.get();}
    Node* getLeft(){ return left.get(); }
    
    Node(Key key, Val val): key(key), val(val), left(nullptr), right(nullptr), height(0) {}
    
private:
    int height;
    unique_ptr<Node> left, right;
    friend AVLtree;
    
    int getHeight()
    {
        if (!this)
        {
            return -1;
        }
        return height;
    }
    int getBalanceFactor()
    {
        if(!this)
        {
            return 0;
        }
        return getHeight(getLeft()) - getHeight(getRight());
    }
    void updateHeight()
    {
        int leftHeight = getHeight(getLeft());
        int rightHeight = getHeight(getLeft());
        height = (leftHeight > rightHeight) ? leftHeight+1 : rightHeight+1;
    }
};

#endif