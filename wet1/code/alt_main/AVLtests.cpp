#include "AVLtree.h"
#include "wet1util.h"
#include "Movie.h"
#include <iostream>
using namespace std;


//================ First Test ==================

    // a tree that looks like this:

    /*                             15
                                /     \
                               /       \
                              /         \
                             /           \
                            10            20
                          /   \         /    \
                         8     12      18     30
                                      /  \ 
                                     16  19
                                                                   
    */// with preorder: 15, 10, 8, 12, 20, 18, 16, 19, 30.
   
   // it should look like this:
  
    /*                             15
                                /     \
                               /       \
                              /         \
                             /           \
                            10            19
                          /   \         /    \
                         8     12      18     30
                                      /   
                                     16  
                                                                   
    */// with preorder: 15, 10, 8, 12, 19, 18, 16,30.



void Test1()
{
  AVLtree<int, int> tree;
  tree.insert(15,-15);
  tree.insert(10,-10);
  tree.insert(20,-20);
  tree.insert(8,-8);
  tree.insert(12,-12);
  tree.insert(18,-18);
  tree.insert(30,-30);
  tree.insert(16,-16);
  tree.insert(19,-19);

  cout << tree << endl;

  tree.remove(20);

  cout << tree << endl;
}
//============================================

//================ 2nd Test ==================
    // removal of first leaf from the left, from a Fibonacci tree like in lecture 4 (AVL Trees) slide 36 (shel erez):
    // insert keys in this order: 5, 2, 8, 1, 4, 6, 10, 3, 7, 9 ,12, 11
    // you are supposed to get something like this:
    /*                              5
                                /       \
                             /            \
                            2              8
                         /     \       /      \
                        1       4      6       10
                               /        \     /   \
                              3         7    9     12
                                                   /
                                                  11
    */ // with preorder: 5, 2, 1, 4, 3, 8, 6, 7, 10, 9, 12, 11.
    // now remove key 1. you are supposed to get something like this:
    /*                             8
                               /       \
                              /         \
                            5             10
                          /   \        /    \
                         3     6      9      12
                        / \      \          /   
                       2   4      7       11     
                                                   
                                                  
    */// with preorder: 8, 5, 3, 2, 4, 6, 7, 10, 9, 12, 11.
    // this triggers an RL rotation on key 2 and then RR rotation on key 5.
void Test2()
{
  AVLtree<int, int> tree;
  tree.insert(5,-5);
  tree.insert(2,-2);
  tree.insert(8,-8);
  tree.insert(1,-1);
  tree.insert(4,-4);
  tree.insert(6,-6);
  tree.insert(10,-10);
  tree.insert(3,-3);
  tree.insert(7,-7);
  tree.insert(9,-9);
  tree.insert(12,-12);
  tree.insert(11,-11);
  cout << tree << endl;
  tree.remove(1);
  cout << tree << endl;
}
//============================================


//================ 3rd Test ================== 
//Valgrind tests
void Test3()
{
  AVLtree<int, int> tree;
  try
  {
    cout << "-----------Valgrind 1-------------" << endl;
    AVLtree<int, int> tree;
    for(int i = 1; i <= 10000; ++i)
    {
      tree.insert(i,i);
    }
    for(int i = 1; i <= 10000; ++i)
    {
      cout << "tree contains " << i << ": ";
      if (tree.get(i) == i)
      {
        cout << "True" << endl;
      }
    }
    for(int i = 1; i <= 10000; ++i)
    {
      tree.remove(i);
    }
    cout << "-----------------------------------" << endl;
    cout << "-----------Valgrind 2-------------" << endl;

    AVLtree<int, int> tree2;
    for(int i = 1; i <= 100000; i*=2)
    {
      tree2.insert(i,-i);
    }
    for(int i = 1; i <= 100000; i*=2)
    {
      cout << "tree contains " << i << ": ";
      if (tree2.get(i) == i)
      {
        cout << "True" << endl;
      }
    }
    for(int i = 1; i <= 10000; i*=2)
    {
      tree2.remove(i);
    }
    cout << "-----------------------------------" << endl;

  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
}
//============================================

int main()
{
  //Test1();
  //Test2();
  Test3();

  return 0;
}