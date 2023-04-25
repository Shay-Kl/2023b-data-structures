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

    tree.printPreOrder();
    tree.printInOrder();
    tree.printPostOrder();
    cout << endl;

    tree.remove(2);

    tree.printPreOrder();
    tree.printInOrder();
    tree.printPostOrder();
    cout << endl;

    tree.remove(5);
    
    tree.printPreOrder();
    tree.printInOrder();
    tree.printPostOrder();
    cout << endl;
}