#include "AVL_tree.h"
#include "wet1util.h"
#include "Movie.h"
#include "StreamingDBa1.h"
#include <iostream>
using namespace std;

void st(StatusType s)
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

int main()
{

    streaming_database db = streaming_database();

    st(db.add_movie(123, Genre::ACTION, 20, false));
    st(db.add_movie(234, Genre::COMEDY, 30, true));
    st(db.add_movie(234, Genre::COMEDY, 30, true)); // Movie already exists, prints 2
    st(db.add_movie(-2, Genre::ACTION, 20, false)); //Invalid id, prints 3
    st(db.remove_movie(123));
    st(db.remove_movie(12)); // No such movie exists, prints 2
    st(db.add_user(101, false));
    st(db.add_user(101, false)); //User already exists, prints 2
    st(db.remove_user(101));
    st(db.remove_user(101)); // No such user exists, prints 2
    st(db.user_watch(101, 123)); // prints 2
    st(db.add_user(101, false));
    st(db.user_watch(101, 234)); //User isn't vip, prints 2

    db = streaming_database();
    cout << endl << endl;
    return 0;
}

