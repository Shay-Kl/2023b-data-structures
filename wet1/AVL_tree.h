#ifndef AVL_H
#define AVL_H
#include <stdlib.h>
#include <iostream>

#include "exceptions.h"

namespace Webflix
{

//===================================================================
//                              Node
//===================================================================
template <class Key, class Value>
class Node //NTM:change to class?
{
public:
    Key m_key;
    Value m_value;
    Node *m_left, *m_right, *m_parent;
    int m_height;

    int getHeight(const Node* node)
    {
        if (node == nullptr){
            return -1;
        }
        else{
            return node->m_height;
        }
    }

    int BalanceFactor(){
        return (getHeight(m_left) - getHeight(m_right));
    }

    // tbd : more constructors
    Node(const Key &key,const Value &value, Node *parent = nullptr)
                    : m_key(key), m_value(value), m_left(nullptr),
                        m_right(nullptr), m_parent(parent), m_height(0){};
    Node(const Node& node) = default;
    virtual ~Node() = default;

    Node &operator=(const Node &node) = default;

    void setCurrHeight(){
        int l_height = getHeight(m_left);
        int r_height = getHeight(m_right);
        if (l_height > r_height){
            m_height = l_height + 1;
        }
        else{
            m_height = r_height + 1;
        }
    }

    /// TBD we assumed T has assign operator , to check later with new structs
    void swapNodes(Node* node1, Node* node2)
    {
        const Key temp_k = node1->m_key;
        const Value temp_v = node1->m_value;
        node1->m_key = node2->m_key;
        node1->m_value = node2->m_value;
        node2->m_key = temp_k;
        node2->m_value = temp_v;
    }
};


template <class Key, class Value>
std::ostream &operator<<(std::ostream &os, const Node<Key,Value> &node)
{

    os << "("<<node.m_key<<")";

    return os;
}
//===================================================================



//===================================================================
//                              AVL tree
//===================================================================

template <class Key, class Value>
class AVLtree
{
    typedef Node<Key, Value> Node;

private:

    Node* m_root;
    Node* m_min_node;
    void rotate(Node* root, Node* new_root, Node** new_root_son, Node** root_son);
    void rotateLeft(Node* root);
    void rotateRight(Node* root);
    Node* iterate_to_next(Node* root) const;
    void correctTreeUp(Node* it, const bool is_insert = true);
    void destroy_tree(Node* root);
    void printTreeAux(Node* root) const;

public:
    int m_num_of_nodes;

    AVLtree() : m_root(nullptr) ,m_min_node(nullptr), m_num_of_nodes(0){};
    ~AVLtree() { destroy_tree(this->m_root); }

        //interface//

    Node* getMinNode() const;
    Node* getRoot() const;
    Node* find(const Key& key) const;
    void insert(const Key& key,const Value& value);
    void remove(const Key& key);
    void printTree() const;

};


template <class Key ,class Value>
void AVLtree<Key,Value>::rotateLeft(Node* root)
{
    rotate(root, (root->m_right), &((root->m_right)->m_left), &(root->m_right));
}


template <class Key, class Value>
void AVLtree <Key, Value>::rotate(Node* root, Node* new_root, Node** new_root_son, Node** root_son)
{
    Node* temp = root->m_parent;

    *root_son = *new_root_son;
    if (*new_root_son != nullptr)
    {
        (*new_root_son)->m_parent = root;
    }
    root->setCurrHeight();
    root->m_parent = new_root;
    *new_root_son = root;
    new_root->setCurrHeight();


    if (temp == nullptr)
    {
        this->m_root = new_root;
    }
    else
    {
        Node** switched = nullptr;
        if (temp->m_right == root){
            switched = &(temp->m_right);
        }
        else{
            switched = &(temp->m_left);
        }

        *switched = new_root;
    }
    new_root->m_parent = temp;

}


template <class Key ,class Value>
Node<Key, Value>* AVLtree<Key,Value>::iterate_to_next(Node* root) const
{
    Node* it = root->m_right;
    while (it->m_left != nullptr)
    {
        it = it->m_left;
    }
    return it;
}

template <class Key ,class Value>
void AVLtree<Key,Value>::rotateRight(Node* root)
{
    rotate(root,(root->m_left), &((root->m_left)->m_right), &(root->m_left));
}


template <class Key ,class Value>
void AVLtree<Key,Value>::correctTreeUp(Node* it, const bool is_insert)
{
    bool valid_node = false;
    while ((it != nullptr) && ((is_insert == false) || (valid_node = false)))
    {
        it->setCurrHeight();
        int balance_factor = it->BalanceFactor();
        if (balance_factor > 1)
        {
            valid_node = true;
            if (it->m_left->BalanceFactor() < 0)
            {
                rotateLeft(it->m_left);
            }
            rotateRight(it);
        }
        else if (balance_factor < -1)
        {
            valid_node = true;
            if (it->m_right->BalanceFactor() > 0){
                rotateRight(it->m_right);
            }
            rotateLeft(it);
        }
        it = it->m_parent;
    }
}


template <class Key ,class Value>
void AVLtree<Key,Value>::destroy_tree(Node* root)
{
    if (root == nullptr){
        return;
    }
    destroy_tree(root->m_left);
    destroy_tree(root->m_right);
    delete(root);
}


template <class Key ,class Value>
Node<Key,Value>* AVLtree<Key,Value>::getMinNode() const
{
    return this->m_min_node;
}


template <class Key ,class Value>
Node<Key,Value>* AVLtree<Key,Value>::find(const Key &key) const
{
    Node* it = this->m_root;
    while (it  && (it->m_key != key))
    {
        if (it->m_key < key){
            it = it->m_right;
        }
        else{
            it = it->m_left;
        }
    }
    return it;
}


template <class Key ,class Value>
void AVLtree<Key,Value>::insert(const Key &key,const Value &value)
{

    if (find(key) != nullptr)
    {
        throw nodeExists();
    }

    Node* it = this->m_root;         // this node can be added because we checked above
    Node** new_ptr = &(this->m_root);
    Node* parent = nullptr;         // no root?, parent will be null

    while (it != nullptr) // find the node for insertion
    {
        parent = it;
        if (it->m_key < key)
        {
            new_ptr = &(it->m_right);
            it = it->m_right;
        }
        else if (it->m_key > key)
        {
            new_ptr = &(it->m_left);
            it = it->m_left;
        }
    }
    *new_ptr = new Node(key, value, parent);

    // ASSUMES the Type hase < operator
    if((this->m_min_node == nullptr) || key < this->m_min_node->m_key){
        this->m_min_node = *new_ptr;
    }
    this->m_num_of_nodes++;
    correctTreeUp(parent); //////paste here the func

}


template <class Key ,class Value>
void AVLtree<Key,Value>::remove(const Key &key)
{
    Node* removed_node = find(key);
    if (removed_node == nullptr){
        throw nodeNotExists();
    }

    if(removed_node == this->m_min_node)
    {
        if ((this->m_min_node)->m_right != nullptr){
            this->m_min_node = (this->m_min_node)->m_right;
        }
        else{
            this->m_min_node = (this->m_min_node)->m_parent;
        }
    }


    if ((removed_node->m_left != nullptr) && (removed_node->m_right != nullptr))
    {
        Node* next = iterate_to_next(removed_node);
        next->swapNodes(removed_node, next); // we need to swap nodes?
        removed_node = next;
    }
    Node* parent = removed_node->m_parent;
    bool is_root = false;
    if (parent == nullptr){
        is_root = true;
    }
    Node** change_parent_to_removed_node = nullptr;
    if (is_root == true){
        change_parent_to_removed_node = nullptr;
    }
    else{
        if (parent->m_left == removed_node){
            change_parent_to_removed_node = &(parent->m_left);
        }
        else{
            change_parent_to_removed_node = &(parent->m_right);
        }
    }
    if(removed_node->m_left == nullptr && removed_node->m_right == nullptr){
        if(is_root == true){
            this->m_root = nullptr;
        }
        else{
            *change_parent_to_removed_node = nullptr;
        }
    }
    else{
        // removed_node has has only one son
        Node** only_one_son = nullptr;
        if (removed_node->m_right != nullptr){
            only_one_son = &(removed_node->m_right);
        }
        else{
            only_one_son = &(removed_node->m_left);
        }

        if (is_root == true){
            this->m_root = *only_one_son;
        }
        else {
            *change_parent_to_removed_node = *only_one_son;
        }

        (*only_one_son)->m_parent = parent;
    }
    delete removed_node;
    this->m_num_of_nodes--;

    Node* it = parent;
    while (it)
    {
        it->setCurrHeight();
        it = it->m_parent;
    }
    correctTreeUp(parent, false);

}


template <class Key ,class Value>
void AVLtree<Key,Value>::printTreeAux(Node* root) const
{
    if (root == nullptr)
    {
        return;
    }
    printTreeAux(root->m_left);
    std::cout << root->m_key;
    printTreeAux(root->m_right);
}


template <class Key ,class Value>
void AVLtree<Key,Value>::printTree() const
{
    printTreeAux(this->m_root);
}


template <class Key ,class Value>
Node<Key,Value>* AVLtree<Key,Value>::getRoot() const
{
    return this->m_root;
}
//===================================================================

}
#endif
