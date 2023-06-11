#include <stdlib.h>
#include <iostream>
#include "HashTable.h"


unsigned int HashTable::HashFunction(int id) const
{
    return id % m_size;
}

void HashTable::reHashTree(AVLtree<int, shared_ptr<Customer>>::Node* src_tree_root, AVLtree<int, shared_ptr<Customer>>* new_trees_array)
{
    if (src_tree_root)
    {
        reHashTree(src_tree_root->getLeft(), new_trees_array);
        new_trees_array[HashFunction(src_tree_root->key)].insert(src_tree_root->key, src_tree_root->val);
        reHashTree(src_tree_root->getRight(), new_trees_array);
    }
}

void HashTable::insert(int id, Customer customer)
{
    m_array[HashFunction(id)].insert(id, shared_ptr<Customer>(new Customer(customer)));
    m_counter++;
    if (m_counter == m_size) //needs a ReHash
    {
        AVLtree<int, shared_ptr<Customer>>* new_arr = new AVLtree<int, shared_ptr<Customer>>[m_size*EXPANSION_RATE];
        for (int i = 0; i < m_size; i++)
        {
            reHashTree(m_array[i].getRoot(), new_arr);
        }
        delete[] m_array;
        m_array = new_arr;
        
    }
}

Customer& HashTable::get(int id)
{
    Customer& customer = *m_array[HashFunction(id)].get(id);
    return customer;
}
