#ifndef __USER_H__
#define __USER_H__

#include "Group.h"
#include "Movie.h"
#include "wet1util.h"
#include <memory>

using namespace std;
class Group;

class User
{
public:
    User(bool isVip);

    //Returns the number of views by the user of movies in a genre
    int getEffectiveViews(Genre genre);

    //Returns m_genreViewCount[genre];
    int getGenreViewCount(Genre genre);

    //Returns the user's group
    shared_ptr<Group> getGroup();

    //Adds user to group, if user is already in a group, returns FailureException
    void addToGroup(shared_ptr<Group> group, int groupId);

    //Watch a movie and increase the user's viewcount of that genre
    void watch(Genre genre);

    //Returns true if the user is a vip
    bool isVip() const;

private:

    //Checks to see if user is in group, if user left group, updates his status
    void updateGroup();

    bool m_isVip;
    shared_ptr<Group> m_group;
    int m_genreViewCount[4];
};
#endif // __USER_H__