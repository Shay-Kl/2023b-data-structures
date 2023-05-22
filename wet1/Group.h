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
    explicit Group(int id);

    //Returns the group's ID
    int getId() const;

    Group(const Group&) = delete;

    //Returns the number of users in the group
    int getUsersCount() const;

    AVLtree<int, User*>& getGroupUsers();

    //Returns true if the group has VIP member in it
    bool isVip() const;

    //Add new user to the group
    void addUser(User* user);
    //Remove user from group
    void removeUser(User* user);

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
    bool m_isVip;
    int m_vipCount;
    int m_usersCount;
    int m_genreTotalViews[4] = {0};
    int m_genreGroupViews[4] = {0};
    AVLtree<int, User*> m_members;

};

#endif // __GROUP_H__