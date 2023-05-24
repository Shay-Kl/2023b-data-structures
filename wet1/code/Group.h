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

    //Returns the group's ID
    int getId() const;

    Group(const Group&) = delete;

    //Returns true if the group has VIP member in it
    bool isVip() const;

    //Returns true if the group is closed
    bool isClosed() const ;

    //Returns the number of users in the group
    int getUsersCount() const;

    //Add new user to the group
    void addUser(User* user);

    //Remove user from group
    void removeUser(User* user);

    //Makes group officially closed.
    void closeGroup();

    //Returns the total genre views count of the group
    int getGenreViewCount(Genre genre) const;

    //Returns the number of times the group watched together in a genre
    int getGroupViews(Genre genre) const;

    //Watch a movie as a group
    void groupWatch(Genre genre);

    //Watch a movie solo
    void soloWatch(Genre genre);



private:
    int m_id;
    int m_vipCount;
    int m_userCount;
    bool m_isOpen;
    int m_genreTotalViews[4] = {0};
    int m_genreGroupViews[4] = {0};

};

#endif // __GROUP_H__