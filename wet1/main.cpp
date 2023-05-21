#include "AVLtree.h"
#include "wet1util.h"
#include "Movie.h"
#include <iostream>
#include "StreamingDBa1.h"
using namespace std;

void st(StatusType s);
void treeTest();
void dbTest();
void removeTest();

int main()
{
    //treeTest();
    dbTest();
    //removeTest();
    return 0;
}

void removeTest()
{
    AVLtree<int, int> tree;
    int a[10]  = {1,5,4,3,2,6,7,9,8,0};
    for (int i = 0; i < 10; i++)
    {
        tree.insert(a[i], 0);
    }
    cout << tree;
    int b[10]  = {1,7,9,8,0,2,3,4,6,5};
    for (int i = 0; i < 10; i++)
    {
        cout << "Removed " << b[i] << endl;
        tree.remove(b[i]);
        cout << tree;
    }

    int c[10]  = {7, 5,4,3,2,6,1,9,8,0};
    for (int i = 0; i < 10; i++)
    {
        tree.insert(c[i], 0);
    }
    cout << tree;
    int d[10]  = {1, 7, 9,8,0,2,3,4,6,5};
    for (int i = 0; i < 10; i++)
    {
        cout << "Removed " << b[i] << endl;
        tree.remove(d[i]);
        cout << tree;
    }
}
void dbTest()
{

    streaming_database db;

    //Line 1 - Printing StatusType for various basic functions, every other command is an intended error of some kind

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

    cout << endl << endl;
    //Line 2 - printing number of movies in each genre
    db.add_movie(1, Genre::COMEDY, 5, false);
    db.add_movie(2, Genre::COMEDY, 5, false);
    db.add_movie(3, Genre::COMEDY, 10, false);
    db.add_movie(4, Genre::ACTION, 5, false);
    db.add_movie(5, Genre::DRAMA, 5, true);
    cout << "Comedy: " << db.get_all_movies_count(Genre::COMEDY).ans();
    cout << ", Drama: " << db.get_all_movies_count(Genre::DRAMA).ans();
    cout << ", Action: " << db.get_all_movies_count(Genre::ACTION).ans();
    cout << ", Fantasy: " << db.get_all_movies_count(Genre::FANTASY).ans();
    cout << ", Total: " << db.get_all_movies_count(Genre::NONE).ans();

    cout << endl << endl;
    
    
    //line 3 - user view count
    st(db.add_user(10, true));//
    st(db.add_user(100, false));//
    st(db.user_watch(10, 1));//
    st(db.user_watch(10, 1));//
    st(db.user_watch(10, 5));//
    st(db.user_watch(100, 5));// user not VIP print 2
    cout << "User 10 - Comedy: " << db.get_num_views(10, Genre::COMEDY).ans();
    cout << ", Drama: " << db.get_num_views(10, Genre::DRAMA).ans();
    cout << ", Total: " << db.get_num_views(10, Genre::NONE).ans();

    cout << endl << endl;

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
    delete[] output;
    count = db.get_all_movies_count(Genre::COMEDY).ans();
    int* output2 = new int[count];
    db.get_all_movies(Genre::COMEDY, output2);
    cout << "  Comedy: ";
    for(int i = 0; i < count; i++)
    {
        cout << output2[i] << ",";
    }
    delete[] output2;
    cout << endl << endl;
 
    //------------------------

    db.add_movie(1, Genre::COMEDY, 0, false);
    db.add_movie(2, Genre::COMEDY, 0, false);
    db.add_movie(3, Genre::COMEDY, 0, false);
    db.add_movie(4, Genre::ACTION, 0, false);
    db.add_movie(5, Genre::DRAMA, 0, true);

    db.add_user(1, false);
    db.add_user(2, false);
    db.add_user(3, true);
    db.add_user(4, true);


    //line 5 - add groups
    st(db.add_group(1));//
    st(db.add_group(1)); //already exists, print 2
    st(db.add_group(-1)); // print 3
    st(db.add_group(2));//
    st(db.add_group(3));//
    st(db.add_group(4));//
    
    cout << endl << endl;

    //line 6 - add users to groups
    st(db.add_user_to_group(-1,1)); // print 3
    st(db.add_user_to_group(1,-1)); // print 3
    st(db.add_user_to_group(1,1)); //
    st(db.add_user_to_group(1,1)); //already exists, print 2
    st(db.add_user_to_group(1,2)); //user already has a group, print 2
    st(db.add_user_to_group(2,2));//
    st(db.add_user_to_group(3,3));//

    cout << endl << endl;

    //line 7 - group watches
    st(db.group_watch(1,-1)); //print 3
    st(db.group_watch(-1,1)); //print 3
    st(db.group_watch(1,1));
    st(db.group_watch(4,5)); // empty group, print 2
    st(db.group_watch(2,5)); // VIP movie not VIP group, print 2
    st(db.group_watch(3,5));
    st(db.group_watch(3,5));
    st(db.group_watch(3,5));

    db.user_watch(3,5);

    cout << " num views: " << db.get_num_views(3,Genre::DRAMA).ans(); // num views: 4

    cout << endl << endl;

    //line 8 - get_group_recommendation
    cout << "recommended movie (or Satus): " << db.get_group_recommendation(3).ans();//should print 5
    cout << " ,";
    st(db.get_group_recommendation(100).status()); //no such group, print 2
    cout << " ,";
    st(db.get_group_recommendation(4).status()); //empty group, print 2
    cout << endl;

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