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

    //Default C'tor
    AVLtree(): m_root(nullptr), m_count(0) {}
    
    //Insert a node into the tree with key and val being copies of the parameters
    //If a node with key already exists, throw a KeyAlreadyExists exception instead
    //If allocation fails, bad alloc is thrown and the tree doesn't change
    //O(log n)
    void insert(Key key, Val val);

    //Insert the given node into the tree without copying its data
    //Allocation can't fail because the funciton doesn't allocate the memory
    //O(log n)
    void insertNode(Node* node);

    //Return a reference to the value for the given key
    //If a node with key doesn't exist, throw a KeyMissing exception instead
    //O(log n)
    Val& get(const Key& key) const;

    //Remove the node with the given key from the tree
    //If a node with key doesn't exist, throw a KeyMissing exception instead
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

    //Recursion helper functions
    void insertAux(unique_ptr<Node>& curNode, Node* newNode);
    Val& getAux(const unique_ptr<Node>& curNode, const Key& key) const;
    Node* removeAux(unique_ptr<Node>& curNode, const Key& key);
    void removeNode(unique_ptr<Node>& curNode);
    void preOrder(unique_ptr<Node>& curNode, ostream& os);
    void inOrder(unique_ptr<Node>& curNode, ostream& os);

    //Returns the leftmost node from a given node
    unique_ptr<Node>& getLeftmost(unique_ptr<Node>& curNode);

    //AVL balancing functions
    void balance(unique_ptr<Node>& node);
    void rightRotate(unique_ptr<Node>& y);
    void leftRotate(unique_ptr<Node>& y);
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
    balance(curNode);
    
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
        throw KeyMissing();
    }
    else if (curNode->key < key) 
    {
        Node* node =  removeAux(curNode->right, key);
        balance(curNode);
        return node;
    }
    else if(key < curNode->key)
    {
        Node* node =  removeAux(curNode->left, key);
        balance(curNode);
        return node;
    }
    else if(curNode->right && curNode->left)
    {
        unique_ptr<Node>& next = getLeftmost(curNode->right);
        unique_ptr<Node> temp = move(next);
        if (curNode->right == next)
        {
            curNode->right = move(temp->right);
            temp->left = move(curNode->left);
            temp->right = move(curNode);
            curNode = move(temp); 
            Node* removed = removeAux(curNode->right, key);
            balance(curNode);
            return removed;
        }
        else
        {
            unique_ptr<Node> right = move(curNode->right);
            unique_ptr<Node> left = move(curNode->left);

            curNode->right = move(temp->right);
            temp->right = move(right);
            temp->left = move(left);
            next = move(curNode);
            curNode = move(temp);
            Node* removed = removeAux(curNode->right, key);
            balance(curNode);
            return removed;
        }
        
    }
    else if(curNode->right)
    {
        Node* temp = curNode->right.release();
        Node* removed = curNode.release();
        curNode.reset(temp);
        return removed;
    }
    else if(curNode->left)
    {
        Node* temp = curNode->left.release();
        Node* removed = curNode.release();
        curNode.reset(temp);
        return removed;
    }
    else
    {
        Node* removed = curNode.release();
        return removed;
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

template <class Key, class Val>
void AVLtree<Key,Val>::rightRotate(unique_ptr<typename AVLtree<Key,Val>::Node>& B)
{
    unique_ptr<AVLtree<Key,Val>::Node> A = move(B->left);
    unique_ptr<AVLtree<Key,Val>::Node> Ar = move(A->right);
    A->right = move(B);
    A->right->left = move(Ar);
    A->right->updateHeight();
    A->updateHeight();
    B = move(A);
}
template <class Key, class Val>
void AVLtree<Key,Val>::leftRotate(unique_ptr<AVLtree<Key,Val>::Node>& A)
{
    unique_ptr<AVLtree<Key,Val>::Node> B = move(A->right);
    unique_ptr<AVLtree<Key,Val>::Node> Bl = move(B->left);
    B->left = move(A);
    B->left->right = move(Bl);
    B->left->updateHeight();
    B->updateHeight();
    A = move(B);
}
template <class Key, class Val>
void AVLtree<Key,Val>::balance(unique_ptr<AVLtree<Key,Val>::Node>& node)
{
    node->updateHeight();
    int balance = node->getBalanceFactor();
    int leftBalance = (node->left) ? node->left->getBalanceFactor() : 0;
    int rightBalance = (node->right) ? node->right->getBalanceFactor() : 0;
    
    if (balance == 2 && leftBalance >= 0) //LL
    {
        return rightRotate(node);
    }
    else if (balance == 2 && leftBalance < 0) //LR
    {
        leftRotate(node->left);
        rightRotate(node);
    }
    else if (balance == -2 && rightBalance <= 0) //RR
    {
        leftRotate(node);
    }
    else if (balance == -2 && rightBalance > 0) //RL
    {
        rightRotate(node->right);
        leftRotate(node);
    }
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
    os << curNode->key << ",";
    inOrder(curNode->right, os);
}
template <class Key, class Val>
void AVLtree<Key,Val>::preOrder(unique_ptr<Node>& curNode, ostream& os)
{
    if (!curNode)
    {
        return;
    }
    
    os << curNode->key << ",";
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
    unique_ptr<Node> left, right;
    int height;
    friend AVLtree;
    
    int getBalanceFactor()
    {
        int leftHeight = (left) ? left->height : -1;
        int rightHeight = (right) ? right->height : -1;
        return leftHeight - rightHeight;
    }    
    void updateHeight()
    {
        int leftHeight = (left) ? left->height : -1;
        int rightHeight = (right) ? right->height : -1;
        height = (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
    }
};

#endif