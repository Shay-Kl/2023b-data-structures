#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>
#include <iostream>
#include "exceptions.h"
#include "AVLtree.h"
#include "Customer.h"

static const int EXPANSION_RATE = 2;
static const int INITIAL_SIZE = 3;


class HashTable
{
private:
    AVLtree<int, shared_ptr<Customer>>* m_array;
    int m_size;
    int m_counter;

    //ReHash helper: insert all values in src tree into dest tree
    void reHashTree(AVLtree<int, shared_ptr<Customer>>::Node* src_tree_root, AVLtree<int, shared_ptr<Customer>>* new_trees_array);

    //Apply the Table's hash function on a given Id
    unsigned int HashFunction(int id) const;


    

public:
    //C'tor
    HashTable(int size = INITIAL_SIZE)
        :m_array(new AVLtree<int, shared_ptr<Customer>>[size]), m_size(size), m_counter(0) {}

    //D'tor
    ~HashTable () {delete[] m_array;}

    //Not supported
    HashTable(const HashTable &other) = delete;
    HashTable &operator=(const HashTable &other) = delete;

    //Insert an element into the table with Id and Customer being copies of the parameters
    //If a Id already exists, throw a KeyAlreadyExists exception
    //If allocation fails, bad alloc is thrown and the table doesn't change
    void insert(int id, Customer customer);
    
    //Return a reference to the Customer for the given Id
    //If a Id doesn't exist, throw a KeyMissing exception instead
    Customer& get(int id);

    
    void printTable()
    {
        for (int i = 0; i < m_size; i++)
        {
            std::cout << "tree index: " << i << std::endl;
            std::cout << m_array[i]<< std::endl;
        }
    }
   
};

#endif //HASH_TABLE_H