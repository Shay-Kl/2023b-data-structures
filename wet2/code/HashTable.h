#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>
#include <iostream>
#include "exceptions.h"
#include "AVLtree.h"
#include "Customer.h"

const unsigned int SHRINKAGE_RATE = 2;
const unsigned int EXPANSION_RATE = 2;
const unsigned int INITIAL_SIZE = 3;


//===================================================================
//                              Dynamic Array
//===================================================================
/*
template <class T>
class DynamicArray
{

private:
    T* m_array;
    int m_size;
    //int m_counter;

public:
    explicit DynamicArray(int size = INITIAL_SIZE)
        : m_array(new T[size]), m_size(INITIAL_SIZE), m_counter(0) {};

    ~DynamicArray () {delete[] m_array;}

    DynamicArray(const DynamicArray &other) = delete;

    DynamicArray &operator=(const DynamicArray &other) = delete;

    T& operator[](int index)
    {
        if (index < 0 || index >= m_size)
        {
            throw IndexOutOfRange();
        }
        return m_array[index];
    }
    void insert(const t& data, int index)
    {
        if (m_counter == size) // need to expand
        {
            try // for bad alloc
            {
                T* new_arr = new T[size*EXPANSION_RATE]; 
            }

            for(int i = 0; i < size; ++i)
            {
                new_arr[i] = m_array[i];
            }
            delete[] m_array;
            m_array = new_arr;
            m_size = size*EXPANSION_RATE;
        }
        m_arr
    }

    int getSize() {return m_size;}
    
    //T* getFirst() {return m_array;}

    void reSize(int rate = EXPANSION_RATE)
    {
        try // for bad alloc
        {
            T* new_arr = new T[m_size*rate];
            for(int i = 0; i < m_size; i++)
            {
                new_arr[i] = m_array[i];
            }
            delete[] m_array;
            m_array = new_arr;
            m_size *= rate;
        }
        catch (const std::bad_alloc &e)
        {
            throw e;
        }
    }
};

*/



//===================================================================
//                              Hash Table
//===================================================================

class HashTable
{
private:
    AVLtree<int, Customer>* m_array;
    int m_size;
    int m_counter;

    //ReHash helper: insert all values in src tree into dest tree
    void reHashTree(AVLtree<int, Customer>::Node* src_tree_root, AVLtree<int, Customer>* new_trees_array);

public:
    //C'tor
    HashTable(int size = INITIAL_SIZE)
        :m_array(new AVLtree<int, Customer>[size]), m_size(size), m_counter(0) {}

    //D'tor
    ~HashTable () {delete[] m_array;}

    //Not supported
    HashTable(const HashTable &other) = delete;
    HashTable &operator=(const HashTable &other) = delete;

    //Insert an element into the table with Id and Customer being copies of the parameters
    //If a Id already exists, throw a KeyAlreadyExists exception
    //If allocation fails, bad alloc is thrown and the table doesn't change
    void insert(int id, Customer customer);

    //Remove an element with given Id from the table
    //If a Id with key doesn't exist, throw a KeyMissing exception
    void Remove(int id);
    
    //Return a reference to the Customer for the given Id
    //If a Id doesn't exist, throw a KeyMissing exception instead
    Customer& find(int id);

    //Returns whether the element is exists in the table
    bool isExists(int id);

    //Apply the Table's hash function on a given Id
    unsigned int HashFunction(int id) const;


    //////////////////DEBUG/////////////////(delete later)
    int getSize() {return m_size;}
    int getCounter() {return m_counter;}

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