#include <stdlib.h>
#include <iostream>
#include "HashTable.h"
#include "Customer.h"
using namespace std;


int main()
{
    /*dynamicArray<int> arr;
    int size = arr.getSize();
    cout << "size: "<< size << endl;
    arr[0] = 0;
    arr[1] = 1;
    arr[2] = 2;
    printArray(arr, size);
    arr.expand();
    size = arr.getSize();
    cout << "size: "<< size << endl;
    arr[3] = 3;
    arr[4] = 4;
    arr[5] = 5;
    printArray(arr, size);
    */

    HashTable hash1;
    for(int i = 0; i < 10000; ++i)
    {
        if (!(i%10))
        {
            Customer temp(i, i);
            hash1.insert(i, temp);
        }

    }
    bool testSucceeded = true;
    int problemValue = -1;
    for(int i = 0; i < 5000; ++i)
    {
        if(!(i%10) && (i < 5000) && !hash1.isExists(i))
        {   
            testSucceeded = false;
            problemValue = i;
            cout << "fucked here: " << i << endl;
        }
        if((i >= 5000) && hash1.isExists(i))
        {
            testSucceeded = false;
            problemValue = i;
            cout << "REALLY fucked here: " << i << endl;
        }
    }
    if(testSucceeded)
    {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "TEST PASSED!" << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    else
    {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "TEST FAILED." << endl;
        cout << "PROBLEM VALUE IS: " << problemValue << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }


    /*HashTable table1;

    //cout << "array size: " << table1.getSize()<<endl << "counter: " << table1.getCounter()<<endl; 

    table1.insert(1, Customer(1,1));
    table1.insert(2, Customer(2,2));

    cout << "array size: " << table1.getSize()<<endl << "counter: " << table1.getCounter()<<endl; 
    table1.printTable();
    cout << endl << endl;
    
    table1.insert(3, Customer(3,3));
    cout << "array size: " << table1.getSize()<<endl << "counter: " << table1.getCounter()<<endl; 
    table1.printTable();
    cout << endl << endl;
    
    table1.insert(30, Customer(30,30));
    table1.insert(5, Customer(5,5));


    cout << "array size: " << table1.getSize()<<endl << "counter: " << table1.getCounter()<<endl; 
    table1.printTable();
    cout << endl << endl;*/


    return 0;

}