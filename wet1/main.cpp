#include "BinaryTree.h"
#include "wet1util.h"
#include <iostream>
using namespace std;

shared_ptr<int> p(int p)
{
    return shared_ptr<int>(new int(p));
}

void ps(StatusType s)
{
    switch (s)
    {
    case StatusType::SUCCESS:
        cout << "success";
        break;
    case StatusType::FAILURE:
        cout << "failiure";
        break;
    case StatusType::ALLOCATION_ERROR:
        cout << "error";
        break;
    
    default:
        break;
    }
}
void i(BinaryTree &tree, int i){
    tree.insert(i, p(i));
}

int main()
{
    BinaryTree tree = BinaryTree();
    i(tree, 330);
    i(tree, 30);
    i(tree, 19);
    i(tree, 200);
    i(tree, 8700);
    i(tree, 1300);
    i(tree, 42000);

    tree.printPreOrder();
    tree.printInOrder();
    tree.printPostOrder();

    tree.remove(30);
    tree.remove(8700);
    tree.printPreOrder();
    tree.printInOrder();
    tree.printPostOrder();
}