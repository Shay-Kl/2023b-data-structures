#include "BinaryTree.h"
#include "wet1util.h"
#include <iostream>
using namespace std;

void i(BinaryTree &tree, int i){
    tree.insert(i, shared_ptr<int>(new int(i)));
}

int main()
{
    BinaryTree tree = BinaryTree();
    i(tree, 5);
    i(tree, 2);
    i(tree, 1);
    i(tree, 3);
    i(tree, 8);
    i(tree, 7);
    i(tree, 9);

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
}