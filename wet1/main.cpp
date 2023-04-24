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
    i(tree, 4);
    i(tree, 7);
    i(tree, 6);
    i(tree, 2);
    i(tree, 9);
    i(tree, 10);

    tree.printPreOrder();
    tree.printInOrder();
    tree.printPostOrder();

    tree.remove(9);
    tree.remove(7);
    tree.printPreOrder();
    tree.printInOrder();
    tree.printPostOrder();
}