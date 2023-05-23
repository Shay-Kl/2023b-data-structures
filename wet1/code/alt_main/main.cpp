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
void weirdTest();

int main()
{
    //treeTest();
    //dbTest();
    //removeTest();
    weirdTest();
    
    return 0;
}

void removeTest()
{
    AVLtree<int, int> tree;
    int a[10]  = {1,5,4,3,2,6,7,9,8,0};
    for (int i = 0; i < 10; i++)
    {
        tree.insert(a[i], 0);
        cout << tree;
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

void weirdTest()
{
streaming_database *db = new streaming_database();

int output[20];
db->remove_user(4531);
db->add_movie(3804, (Genre)1, 20, false);
db->get_all_movies((Genre)0, output);
db->get_all_movies((Genre)4, output);
db->add_group(2346);
db->add_user(8724, false);
db->get_all_movies((Genre)1, output);
db->get_all_movies_count((Genre)4);
db->add_user(126, true);
db->user_watch(126, 2422);
db->add_movie(3204, (Genre)0, 65, true);
db->add_user(4473, false);
db->add_user_to_group(8724, 2346);
db->add_user_to_group(4473, 2346);
db->add_movie(7684, (Genre)4, 48, true);
db->group_watch(2346, 7684);
db->add_user(145, true);
db->get_all_movies((Genre)4, output);
db->get_num_views(145, (Genre)1);
db->get_all_movies((Genre)4, output);
db->add_movie(2698, (Genre)2, 28, true);
db->get_all_movies((Genre)3, output);
db->add_user(499, true);
db->remove_movie(7684);
db->remove_group(2346);
db->rate_movie(4473, 3804, 87);
db->get_num_views(145, (Genre)0);
db->add_user(5037, true);
db->user_watch(8724, 3204);
db->get_all_movies((Genre)3, output);
db->remove_movie(266);
db->add_group(7173);
db->get_group_recommendation(7173);
db->add_movie(360, (Genre)3, 69, false);
db->add_user_to_group(8724, 7173);
db->remove_group(7173);
db->remove_user(5037);
db->add_group(7018);
db->remove_group(7018);
db->get_group_recommendation(7018);
db->add_movie(9752, (Genre)0, 12, false);
db->add_movie(7016, (Genre)3, 71, true);
db->add_group(147);
db->add_user(5316, true);
db->add_user_to_group(8724, 7018);
db->get_num_views(145, (Genre)0);
db->get_all_movies((Genre)3, output);
db->get_group_recommendation(4565);
db->add_movie(613, (Genre)2, 89, true);
db->get_group_recommendation(147);
db->get_all_movies((Genre)1, output);
db->get_all_movies((Genre)0, output);
db->group_watch(7018, 360);
db->add_user(9378, false);
db->group_watch(7018, 613);
db->add_user_to_group(5316, 147);
db->group_watch(7018, 2422);
db->add_group(7487);
db->remove_group(7487);
db->add_movie(2887, (Genre)4, 51, false);
db->get_all_movies_count((Genre)1);
db->get_all_movies((Genre)3, output);
db->add_user(6781, true);
db->add_movie(9844, (Genre)1, 87, false);
db->remove_movie(360);
db->user_watch(499, 7016);
db->add_movie(534, (Genre)0, -5, false);
db->add_user(1519, true);
db->get_all_movies_count((Genre)2);
db->group_watch(7018, 7016);
db->add_movie(9688, (Genre)0, 95, false);
db->get_all_movies((Genre)1, output);
db->user_watch(126, 9688);
db->user_watch(6781, 2422);
db->remove_movie(2698);
db->remove_group(7018);
db->remove_user(4473);
db->get_all_movies((Genre)1, output);
db->add_user(2070, true);
db->group_watch(147, 3804);
db->add_user(9946, false);
db->remove_movie(3201);
db->remove_movie(9844);
db->add_group(4946);
db->group_watch(4946, 7016);
db->add_user(5210, true);
db->add_user(3218, true);
db->group_watch(147, 613);
db->add_group(7936);
db->get_all_movies((Genre)1, output);
db->add_group(4166);
db->group_watch(4946, 3804);
db->add_group(2134);
db->get_all_movies((Genre)0, output);
db->remove_movie(613);
db->remove_movie(9688);
db->add_group(1857);
db->add_user_to_group(1519, 4946);
db->add_user(251, false);
db->remove_user(1519);
db->add_user_to_group(6781, 3298);
db->get_group_recommendation(4946);
db->add_group(3370);
db->add_movie(539, (Genre)0, 27, true);
db->get_all_movies((Genre)3, output);
db->get_num_views(9378, (Genre)0);
db->add_group(2061);
db->get_all_movies((Genre)4, output);
db->rate_movie(1519, 3204, 3);
db->get_all_movies((Genre)4, output);
db->get_group_recommendation(3370);
db->add_movie(6536, (Genre)1, 75, true);
db->add_user_to_group(126, 2061);
db->get_all_movies_count((Genre)1);
db->add_group(6005);
db->remove_user(5210);
db->add_movie(7160, (Genre)1, 79, false);
db->remove_movie(9844);
db->get_num_views(8724, (Genre)1);
db->add_group(1616);
db->get_group_recommendation(2134);
db->get_group_recommendation(2061);
db->add_group(9227);
db->get_all_movies_count((Genre)1);
db->add_movie(4262, (Genre)4, 20, false);
db->add_movie(561, (Genre)2, 70, false);
db->get_all_movies_count((Genre)0);
db->user_watch(9378, 7160);
db->user_watch(499, 534);
db->get_all_movies((Genre)0, output);
db->user_watch(9946, 3804);
db->add_user_to_group(8724, 6005);
db->user_watch(7158, 4262);
db->add_user(4022, false);
db->add_user(8509, true);
db->get_group_recommendation(2134);
db->user_watch(2070, 7016);
db->get_num_views(3218, (Genre)2);
db->remove_group(147);
db->get_all_movies((Genre)2, output);
db->add_group(8226);
db->remove_movie(2422);
db->add_user_to_group(5316, 8226);
db->remove_movie(561);
db->add_movie(1586, (Genre)2, 56, false);
db->get_group_recommendation(4946);
db->add_user_to_group(9946, 2629);
db->rate_movie(2070, 7160, 106);
db->get_num_views(2070, (Genre)1);
db->group_watch(4946, 534);
db->get_group_recommendation(3370);
db->remove_group(7936);
db->rate_movie(6781, 6536, 86);
db->remove_user(9946);
db->add_user(2002, true);
db->add_movie(8456, (Genre)4, 39, false);
db->get_all_movies((Genre)0, output);
db->get_all_movies((Genre)2, output);
db->get_num_views(8724, (Genre)4);
db->get_group_recommendation(4946);
db->add_movie(8941, (Genre)0, 76, true);
db->get_all_movies((Genre)1, output);
db->remove_movie(539);
db->get_all_movies((Genre)4, output);
db->add_user(9513, false);
db->add_user(145, true);
db->group_watch(4166, 9752);
db->add_user_to_group(1519, 2061);
db->remove_user(9378);
db->add_user(9357, false);
db->add_user(383, false);
db->group_watch(1616, 231);
db->add_user(7558, true);
db->get_all_movies_count((Genre)0);
db->remove_group(2134);
db->add_group(9351);
db->get_num_views(9513, (Genre)3);
db->group_watch(8226, 4262);
db->add_user(1639, true);
db->add_group(2617);
db->get_num_views(8724, (Genre)0);
db->remove_user(3218);
db->add_movie(7044, (Genre)1, 83, false);
db->add_movie(5437, (Genre)2, 44, false);
db->add_user(1834, true);
db->group_watch(2617, 2887);
db->get_all_movies((Genre)0, output);
db->add_movie(5438, (Genre)1, 64, true);
db->add_movie(7373, (Genre)2, 100, false);
db->add_group(5772);
db->rate_movie(126, 5437, 147);
db->get_all_movies((Genre)3, output);
db->add_user(1182, true);
db->add_movie(7830, (Genre)2, 9, true);
db->group_watch(2617, 3204);
db->user_watch(6781, 7830);
db->rate_movie(251, 2887, 59);
db->group_watch(1616, 5437);
db->remove_user(126);
db->get_all_movies_count((Genre)1);
db->get_group_recommendation(9351);
db->add_user(7680, true);
db->get_all_movies_count((Genre)2);
db->group_watch(3370, 5437);
db->remove_group(6076);
db->remove_movie(8941);
db->remove_group(6005);
db->add_group(7375);
db->add_user_to_group(7680, 9227);
db->add_movie(8360, (Genre)4, 92, false);
db->add_movie(4863, (Genre)4, 71, false);
db->get_all_movies_count((Genre)3);
db->add_user_to_group(1639, 1616);
db->remove_group(9227);
db->remove_movie(7016);
db->add_user_to_group(6781, 4946);
db->add_user_to_group(8509, 5772);
db->add_movie(534, (Genre)1, 7, true);
db->remove_user(8509);
db->get_all_movies((Genre)4, output);
db->get_num_views(7680, (Genre)2);
db->get_all_movies((Genre)0, output);
db->get_num_views(145, (Genre)2);
db->add_user_to_group(9513, 8226);
db->remove_group(4166);
db->add_user(7240, true);
db->add_user(9632, true);
db->add_user_to_group(9632, 4946);
db->get_num_views(9632, (Genre)2);
db->get_all_movies((Genre)2, output);
db->remove_user(4022);
db->get_all_movies((Genre)4, output);
db->add_movie(491, (Genre)3, 42, false);
db->add_user_to_group(1182, 7936);
db->get_num_views(499, (Genre)4);
db->add_user(4344, false);
db->remove_user(9513);
db->add_user(7064, true);
db->add_movie(5286, (Genre)0, 91, true);
db->group_watch(9351, 7830);
db->get_group_recommendation(3370);
db->add_movie(4984, (Genre)1, 23, false);
db->remove_user(499);
db->group_watch(2617, 4262);
db->get_group_recommendation(4946);
db->add_group(3392);
db->add_movie(941, (Genre)2, 11, true);
db->add_group(5453);
db->add_movie(7915, (Genre)3, 15, true);
db->user_watch(8724, 8941);
db->get_all_movies((Genre)0, output);
db->user_watch(8724, 6536);
db->remove_user(383);
db->get_all_movies_count((Genre)0);
db->remove_group(9351);
db->get_group_recommendation(7375);
db->add_movie(7949, (Genre)1, 9, false);
db->remove_group(6005);
db->get_num_views(4344, (Genre)3);
db->add_group(9205);
db->group_watch(8226, 4262);
db->add_group(9730);
db->add_user(8997, false);
db->add_group(1540);
db->group_watch(2617, 4984);
db->remove_movie(9752);
db->add_movie(2790, (Genre)4, 29, true);
db->add_movie(7339, (Genre)0, 37, true);
db->get_all_movies((Genre)1, output);
db->remove_group(2617);
db->remove_user(9632);
db->get_all_movies_count((Genre)2);
db->user_watch(4344, 2887);
db->add_movie(7116, (Genre)4, 84, true);
db->get_num_views(7064, (Genre)3);
db->remove_movie(4279);
db->add_user(2544, true);
db->remove_user(8724);
db->remove_user(1519);
db->add_user_to_group(1096, 5772);
db->group_watch(3392, 6536);
db->remove_group(8226);
db->add_user(6469, true);
db->get_all_movies((Genre)4, output);
db->add_movie(2607, (Genre)0, 86, true);
db->add_group(7235);
db->get_all_movies((Genre)0, output);
db->add_group(5198);
db->get_all_movies((Genre)1, output);
db->remove_group(6005);
db->group_watch(7936, 4262);
db->add_user(6758, true);
db->get_group_recommendation(9205);
db->remove_movie(7116);
db->remove_user(3295);
db->get_group_recommendation(5213);
db->add_group(6980);
db->add_movie(7126, (Genre)3, 10, true);
db->add_movie(5770, (Genre)4, 75, false);
db->add_user(7240, true);
db->add_movie(8939, (Genre)0, -2, true);
db->remove_group(1857);
db->add_movie(7631, (Genre)4, 89, true);
db->get_all_movies((Genre)0, output);
db->add_user(4197, true);
db->add_user_to_group(7558, 3392);
db->add_movie(1917, (Genre)1, 8, false);
db->add_user_to_group(6469, 9205);
db->get_all_movies((Genre)1, output);
db->add_movie(6099, (Genre)2, 21, true);
db->remove_user(2544);
db->get_num_views(7064, (Genre)0);
db->user_watch(8997, 6099);
db->add_user(8288, true);
db->add_group(118);
db->get_all_movies((Genre)2, output);
db->get_all_movies_count((Genre)3);
db->get_all_movies((Genre)2, output);
db->add_group(1117);
db->get_num_views(7558, (Genre)0);
db->rate_movie(7680, 534, 34);
db->get_all_movies_count((Genre)4);
db->add_user(7637, false);
db->rate_movie(7064, 3804, 150);
db->add_group(4796);
db->add_group(2076);
db->remove_user(6758);
db->get_all_movies((Genre)4, output);
db->group_watch(5453, 7373);
db->add_group(8264);
db->group_watch(7936, 4984);
db->user_watch(1182, 6536);
db->get_num_views(2002, (Genre)1);
db->rate_movie(2544, 7915, 91);
db->rate_movie(7680, 7830, 87);
db->add_user_to_group(7240, 9205);
db->get_all_movies((Genre)3, output);
db->add_group(8499);
db->add_group(6641);
db->add_user(397, true);
db->add_group(2799);
db->remove_movie(2887);
db->add_group(2921);
db->group_watch(8264, 1586);
db->add_user_to_group(7637, 6641);
db->remove_group(5772);
db->get_all_movies((Genre)3, output);
db->get_all_movies_count((Genre)1);
db->add_group(3495);
db->add_movie(1994, (Genre)0, 84, true);
db->rate_movie(6781, 7830, 88);
db->remove_group(2076);
db->remove_movie(8941);
db->add_group(4594);
db->rate_movie(8288, 7044, 125);
db->group_watch(3392, 7830);
db->add_group(1467);
db->add_group(7921);
db->add_movie(6347, (Genre)1, 99, false);
db->user_watch(7240, 7373);
db->add_movie(2514, (Genre)4, 36, false);
db->get_all_movies_count((Genre)0);
db->group_watch(9205, 5437);
db->add_user_to_group(7240, 118);
db->add_user_to_group(397, 8264);
db->add_user(7476, true);
db->group_watch(4946, 7044);
db->group_watch(118, 5770);
db->get_all_movies((Genre)1, output);
db->get_all_movies_count((Genre)2);
db->get_num_views(9357, (Genre)2);
db->get_all_movies((Genre)3, output);
db->remove_group(4946);
db->add_movie(187, (Genre)4, 83, false);
db->get_all_movies_count((Genre)4);
db->add_movie(398, (Genre)4, 98, false);
db->get_group_recommendation(9730);
db->rate_movie(251, 7949, 25);
db->get_all_movies((Genre)3, output);
db->get_group_recommendation(7375);
db->rate_movie(7637, 2607, 71);
db->remove_movie(5437);
db->add_movie(6386, (Genre)4, 79, true);
db->remove_group(1467);
db->get_all_movies((Genre)4, output);
cout << output[0] << output[1];

}