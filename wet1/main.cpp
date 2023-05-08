#include "AVL_tree.h"
#include "wet1util.h"
#include <iostream>
using namespace std;

int main()
{
    AVLtree<int, int> tree = AVLtree<int, int>();
    tree.insert(5, 50);
    tree.insert(2, 20);
    tree.insert(1, 10);
    tree.insert(3, 30);
    tree.insert(8, 80);
    tree.insert(7, 70);
    tree.insert(9, 90);
    //          5
    //    2            8
    // 1     3      7     9
    cout << tree;



    tree.remove(2);
    //          5
    //    3            8
    // 1            7     9
    cout << tree;



    tree.remove(5);
    //          7
    //    3            8
    // 1                  9
    cout << tree;



    tree.remove(1);
    tree.remove(3);
    //          8
    //    7            9
    //                    
    cout << tree;


    tree.insert(15, 150);
    tree.insert(25, 250);
    tree.insert(35, 350);
    tree.insert(40, 400);
    //          8
    //    7            9
    //                     15
    //                          25
    //                               35

    //    
    cout<< tree;

    
}