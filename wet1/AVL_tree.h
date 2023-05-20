#ifndef __AVL_tree_H__
#define __AVL_tree_H__
#include <stdlib.h>
#include <iostream>

#include "exceptions.h"
#include <memory>
using namespace std;


//===================================================================
//                              Node
//===================================================================
template <class Key, class Value>
class Node
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

    Node(const Key &key,const Value &value, Node *parent = nullptr)
                    : m_key(key), m_value(value), m_left(nullptr),
                        m_right(nullptr), m_parent(parent), m_height(0){}
    Node(const Node& other) = default;
    /*: m_key(other.m_key),
        m_value(other.m_value),
        m_left(nullptr),
        m_right(nullptr),
        m_parent(nullptr),
        m_height(other.m_height)
    {
        if (other.m_left)
        {
            m_left = new Node(*other.m_left);
            m_left->m_parent = this;
        }

        if (other.m_right)
        {
            m_right = new Node(*other.m_right);
            m_right->m_parent = this;
        }
    }
*/

    virtual ~Node() = default;

    Node &operator=(const Node &node) = default;

    void setCurrHeight(){
        int l_height = getHeight(m_left);
        int r_height = getHeight(m_right);
        if (l_height > r_height){
            this->m_height = l_height + 1;
        }
        else{
            this->m_height = r_height + 1;
        }
    }

    /// TBD we assumed T has assign operator , to check later with new structs
    void swapNodes(Node* node1, Node* node2)
    {
        Node* tempRight = node1->m_right;
        Node* tempLeft = node1->m_left;
        Node* tempParent = node1->m_parent;
        node1->m_left = node2->m_left;
        node1->m_right = node2->m_right;
        node1->m_parent = node2->m_parent;
        node2->m_left = tempLeft;
        node2->m_right = tempRight;
        node2->m_parent = tempParent;

        if (node1->m_right)
        {
            node1->m_right->m_parent = node1;
        }
        if (node1->m_left)
        {
            node1->m_left->m_parent = node1;
        }
        if (node2->m_right)
        {
            node2->m_right->m_parent = node2;
        }
        if (node2->m_left)
        {
            node2->m_left->m_parent = node2;
        }
        if (node1->m_parent)
        {
            if (node1->m_parent->m_right && node1->m_parent->m_right == node2)
            {
                node1->m_parent->m_right = node1;
            }
            else
            {
                node1->m_parent->m_left = node1;
            }
        }
        if (node2->m_parent)
        {
            if (node2->m_parent->m_right && node2->m_parent->m_right == node1)
            {
                node2->m_parent->m_right = node2;
            }
            else
            {
                node2->m_parent->m_left = node2;
            }
        }
        
        
        
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

public:
    

    AVLtree() : m_num_of_nodes(0), m_root(nullptr) ,m_min_node(nullptr) {}
    AVLtree& operator=(const AVLtree& tree) = default;
    /*{
            if (this == &tree) {
            return *this;
        }
        this->m_root = tree.getRoot();
        this->m_num_of_nodes = tree.getNodeCount();
        this->m_min_node = tree.getMinNode();

        return *this;
	}*/


    AVLtree(const AVLtree& other)
        : m_num_of_nodes(other.m_num_of_nodes),
          m_root(nullptr),
          m_min_node(nullptr)
    {
        if (other.m_root)
        {
            m_root = new Node<Key, Value>(*other.m_root);

            // Find the corresponding minimum node in the new tree
            Node<Key, Value>* minNode = other.getMinNode();
            Node<Key, Value>* newNode = m_root;

            while (minNode && newNode)
            {
                if (minNode == other.m_min_node)
                {
                    m_min_node = newNode;
                    break;
                }

                if (minNode->m_left && newNode->m_left)
                {
                    minNode = minNode->m_left;
                    newNode = newNode->m_left;
                }
                else if (minNode->m_right && newNode->m_right)
                {
                    minNode = minNode->m_right;
                    newNode = newNode->m_right;
                }
                else
                {
                    break;
                }
            }
        }
    }






    ~AVLtree() { destroy_tree(this->m_root); }

        //interface//

    void insert(const Key& key,const Value& value);
    Value& get(const Key& key);
    void remove(const Key& key);
    int getNodeCount() const {return m_num_of_nodes;}
    Node<Key, Value>* getMinNode() const;
    Node<Key, Value>* getRoot() const;
    Node<Key, Value>* find(const Key& key);

    template <class k,class v>
    friend ostream& operator<< (ostream& os, AVLtree<k,v>& tree);
    


private:
    int m_num_of_nodes;
    Node<Key, Value>* m_root = nullptr;
    Node<Key, Value>* m_min_node = nullptr;
    
    
    void rotate(Node<Key, Value>* root, Node<Key, Value>* new_root, Node<Key, Value>** new_root_son, Node<Key, Value>** root_son);
    void rotateLeft(Node<Key, Value>* root);
    void rotateRight(Node<Key, Value>* root);
    Node<Key, Value>* iterate_to_next(Node<Key, Value>* root) const;
    void correctTreeUp(Node<Key, Value>* it, const bool is_insert = true);
    void destroy_tree(Node<Key, Value>* root);
    
    //void printInOrder(Node<Key,Value>* node);


};


template <class Key ,class Value>
void printInOrder(Node<Key,Value>* node)
{
    if (node)
    {
        printInOrder(node->m_left);
        cout << node->m_key << ", ";
        printInOrder(node->m_right);
    }
    
}


template <class Key ,class Value>
void printPreOrder(Node<Key,Value>* node)
{
    if (node)
    {
        cout << node->m_key << ", ";
        printPreOrder(node->m_left);
        printPreOrder(node->m_right);
    }
    
}

template <class Key ,class Value>
ostream& operator<<(ostream& os, AVLtree<Key, Value>& tree)
{
    cout<< "Inorder: ";
    printInOrder(tree.m_root);
    
    cout << endl << "Preorder: ";
    printPreOrder(tree.m_root);
    cout << endl << endl;
    return os;
}



template <class Key, class Value>
Value& AVLtree<Key,Value>::get(const Key& key)
{
    Node<Key, Value>* node = find(key);
    if(!node)
    {
        throw nodeNotExists();
    }
    return node->m_value;
}


template <class Key ,class Value>
void AVLtree<Key,Value>::rotateLeft(Node<Key, Value>* root)
{
    rotate(root, (root->m_right), &((root->m_right)->m_left), &(root->m_right));
}


template <class Key, class Value>
void AVLtree <Key, Value>::rotate(Node<Key, Value>* root, Node<Key, Value>* new_root, Node<Key, Value>** new_root_son, Node<Key, Value>** root_son)
{
    Node<Key, Value>* temp = root->m_parent;

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
        Node<Key, Value>** switched = nullptr;
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
Node<Key, Value>* AVLtree<Key,Value>::iterate_to_next(Node<Key, Value>* root) const
{
    Node<Key, Value>* it = root->m_right;
    while (it->m_left != nullptr)
    {
        it = it->m_left;
    }
    return it;
}

template <class Key ,class Value>
void AVLtree<Key,Value>::rotateRight(Node<Key, Value>* root)
{
    rotate(root,(root->m_left), &((root->m_left)->m_right), &(root->m_left));
}


template <class Key ,class Value>
void AVLtree<Key,Value>::correctTreeUp(Node<Key, Value>* it, const bool is_insert)
{
    bool valid_node = false;
    while ((it != nullptr) && ((is_insert == false) || (!valid_node)))
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
void AVLtree<Key,Value>::destroy_tree(Node<Key, Value>* root)
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
Node<Key,Value>* AVLtree<Key,Value>::find(const Key &key)
{
    Node<Key, Value>* it = this->m_root;
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

    Node<Key, Value>* it = this->m_root;         // this node can be added because we checked above
    Node<Key, Value>** new_ptr = &(this->m_root);
    Node<Key, Value>* parent = nullptr;         // no root?, parent will be null

    while (it != nullptr) // find the node for insertion
    {
        parent = it;
        if (it->m_key < key)
        {
            new_ptr = &(it->m_right);
            it = it->m_right;
        }
        else if (key < it->m_key)
        {
            new_ptr = &(it->m_left);
            it = it->m_left;
        }
    }
    *new_ptr = new Node<Key, Value>(key, value, parent);

    // ASSUMES the Type has < operator
    if((this->m_min_node == nullptr) || key < (this->m_min_node)->m_key){
        this->m_min_node = *new_ptr;
    }
    (this->m_num_of_nodes)++;
    correctTreeUp(parent); //////paste here the func

}


template <class Key ,class Value>
void AVLtree<Key,Value>::remove(const Key &key)
{
    Node<Key, Value>* removed_node = find(key);
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
        Node<Key, Value>* next = iterate_to_next(removed_node);
        cout << endl << "removed: left:" << removed_node->m_left << ", right: " << removed_node->m_right << ", parent: " << removed_node->m_parent;
        cout << endl << "next   : left:" << next->m_left << ", right: " << next->m_right << ", parent: " << next->m_parent << endl << endl;
        if(next!=removed_node->m_right)
        {
            next->swapNodes(removed_node, next); // we need to swap nodes?
        }
        else
        {
            next->m_left = removed_node->m_left;
            next->m_parent = removed_node->m_parent;
            removed_node->m_left = nullptr;
            removed_node->m_parent = next;

            removed_node->m_right =  next->m_right;
            next->m_right = removed_node;
            if (removed_node->m_right)
            {
                removed_node->m_right->m_parent = removed_node;
            }
            if (next->m_parent && next->m_parent->m_right == removed_node)
            {
                next->m_parent->m_right = next;
            }
            if (next->m_parent && next->m_parent->m_left == removed_node)
            {
                next->m_parent->m_left = next;
            }
            if(next->m_left)
            {
                next->m_left->m_parent = next;
            }
            
            

        }
        removed_node = next;
    }
    Node<Key, Value>* parent = removed_node->m_parent;
    bool is_root = false;
    if (parent == nullptr){
        is_root = true;
    }
    Node<Key, Value>** change_parent_to_removed_node = nullptr;
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
        // removed_node has only one son
        Node<Key, Value>** only_one_son = nullptr;
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

    Node<Key, Value>* it = parent;
    while (it)
    {
        it->setCurrHeight();
        it = it->m_parent;
    }
    correctTreeUp(parent, false);

}

template <class Key ,class Value>
Node<Key,Value>* AVLtree<Key,Value>::getRoot() const
{
    return this->m_root;
}
//===================================================================

#endif