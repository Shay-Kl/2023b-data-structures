#include "AVL_tree.h"
#include "wet1util.h"
#include "Movie.h"
#include "StreamingDBa1.h"
#include <iostream>
using namespace std;
int st(StatusType s)
{
    switch (s)
    {
    case StatusType::SUCCESS:
        cout << "1,";
        break;
    case StatusType::FAILURE:
        cout << "2,";
        break;
    case StatusType::INVALID_INPUT:
        cout << "3,";
        break;
    case StatusType::ALLOCATION_ERROR:
        cout << "4,";
        break;
    }
}
void treeTest()
{
    AVLtree<int, int> tree = AVLtree<int, int>();
    tree.insert(5, 0);
    tree.insert(3, 0);
    tree.insert(1, 0);
    tree.insert(0, 0);
    tree.insert(20, 0);
    tree.insert(15, 0);
    tree.insert(40, 0);
    tree.insert(35, 0);
    tree.remove(1);
    tree.remove(0);
    tree.remove(20);
    tree.remove(3);
    tree.remove(5);
    tree.insert(50, 0);
    tree.insert(5, 0);
    tree.insert(-1, 0);
    tree.insert(70, 0);
    tree.insert(47, 0);
    tree.insert(23, 0);

    cout << tree;
}
void dbTest()
{

    streaming_database db = streaming_database();

    //Testing various scenarios, every other command is an intended error of some kind

    st(db.add_movie(234, Genre::COMEDY, 30, true));
    st(db.add_movie(234, Genre::COMEDY, 30, true)); // Movie already exists, prints 2
    st(db.add_movie(123, Genre::ACTION, 20, false));
    st(db.add_movie(-2, Genre::ACTION, 20, false)); //Invalid id, prints 3
    st(db.remove_movie(123));
    st(db.remove_movie(12)); // No such movie exists, prints 2
    st(db.add_user(101, false));
    st(db.add_user(101, false)); //User already exists, prints 2
    st(db.remove_user(101));
    st(db.remove_user(101)); // No such user exists, prints 2
}


int main()
{
    treeTest();
    //dbTest();
}