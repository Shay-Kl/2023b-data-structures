#include "AVL_tree.h"
#include "wet1util.h"
#include <iostream>
using namespace std;

int main()
{
    AVLtree<int, int> tree = AVLtree<int, int>();
    int a = 5, b = 2, c = 1, d = 3, e = 8, f = 7, g = 9;
    tree.insert(a, a);
    tree.insert(b, b);
    tree.insert(c, c);
    tree.insert(d, d);
    tree.insert(e, e);
    tree.insert(f, f);
    tree.insert(g, g);

    //          5
    //    2            8
    // 1     3      7     9
    tree.printTree();
    //cout << tree;

    tree.remove(2);

    //          5
    //    3            8
    // 1            7     9

    tree.printTree();
    //cout << tree;

    tree.remove(5);
    
    //          7
    //    3            8
    // 1                  9
    tree.printTree();
    //cout << tree;
}