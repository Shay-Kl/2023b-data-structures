#include "AVL_tree.h"
#include "wet1util.h"
#include "Movie.h"
#include "StreamingDBa1.h"
#include <iostream>
using namespace std;

void st(StatusType s);
void treeTest();
void dbTest();

int main()
{
    //treeTest();
    dbTest();
}

void dbTest()
{

    streaming_database db = streaming_database();

    //Line 1 - Printing StatusType for various basic functions, every other command is an intended error of some kind

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
    st(db.user_watch(101, 123));
    st(db.user_watch(101, 234)); //User isn't vip, prints 2

    cout << endl;

    //Line 2 - printing number of movies in each genre
    db = streaming_database();
    db.add_movie(1, Genre::COMEDY, 5, false);
    db.add_movie(2, Genre::COMEDY, 5, false);
    db.add_movie(3, Genre::COMEDY, 10, false);
    db.add_movie(4, Genre::ACTION, 5, false);
    db.add_movie(5, Genre::DRAMA, 5, false);
    cout << "Comedy: " << db.get_all_movies_count(Genre::COMEDY).ans();
    cout << ", Drama: " << db.get_all_movies_count(Genre::DRAMA).ans();
    cout << ", Action: " << db.get_all_movies_count(Genre::ACTION).ans();
    cout << ", Fantasy: " << db.get_all_movies_count(Genre::FANTASY).ans();
    cout << ", Total: " << db.get_all_movies_count(Genre::NONE).ans();

    cout << endl;

    //line 3 - user view count
    db.add_user(10, true);
    db.user_watch(10, 1);
    db.user_watch(10, 2);
    db.user_watch(10, 5);
    cout << "User 10 - Comedy: " << db.get_num_views(10, Genre::COMEDY).ans();
    cout << ", Drama: " << db.get_num_views(10, Genre::DRAMA).ans();
    cout << ", Total: " << db.get_num_views(10, Genre::NONE).ans();

    cout << endl;

    //line 4 - rating and then printing all movies in a genre, sorted

    db.rate_movie(10, 3, 80);
    db.rate_movie(10, 3, 100); // Movie 3 - average rating of 90, high view count
    db.rate_movie(10, 2, 90); // Movie 2 - average rating of 90
    db.rate_movie(10, 5, 100); // Movie 5 - average rating of 100
    
    //Order is thus 5,3,2, then the rest are ordered by id (1,4)

    int count = db.get_all_movies_count(Genre::NONE).ans();
    int* output = new int[count];
    db.get_all_movies(Genre::NONE, output);
    cout << "All: ";
    for(int i = 0; i < count; i++)
    {
        cout << output[i] << ", ";
    }
    count = db.get_all_movies_count(Genre::COMEDY).ans();
    output = new int[count];
    db.get_all_movies(Genre::COMEDY, output);
    cout << "  Comedy: ";
    for(int i = 0; i < count; i++)
    {
        cout << output[i] << ",";
    }
    

}


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