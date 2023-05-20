#ifndef __GROUP_H__
#define __GROUP_H__

#include "StreamingDBa1.h"
#include "User.h"
#include "AVLtree.h"

class User;

class Group
{
public:
    //C'tor
    Group(int id);

    //Dummy element for tree
    Group();

    //Returns the group's ID
    int getId() const;

    //Returns the number of users in the group
    int getUsersCount() const;

    //Returns the tree that holds all group's users
    AVLtree<int, User*>& getUsers();

    //Returns true if the group has VIP member in it
    bool isVip() const;

    //Add new user to the group
    void addUser(User& user);

    //Remove user from group
    void removeUser(User& user);

    void closeGroup();

    //Add num of views to the total genre views count
    void updateViews(Genre genre, int views);

    //Returns the total genre views count of the group
    int getGenreViewCount(Genre genre) const;

    //Returns the number of times the group watched together in a genre
    int getGroupViews(Genre genre) const;

    //Add one group watch to the groupWatchCounter
    void incGroupWatch(Genre genre);



private:
    int m_id;
    int m_vipCount;
    int m_genreTotalViews[4] = {0};
    int m_genreGroupViews[4] = {0};
    AVLtree<int, User*> users;
};

#endif // __GROUP_H__