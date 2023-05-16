#ifndef __USER_H__
#define __USER_H__

#include "Group.h"
#include "Movie.h"
#include "wet1util.h"

class Group;

class User
{
public:
    User(int id, bool isVip);

    //Returns pointer to group
    Group* getGroup() const;

    //Returns the user's ID
    int getId() const;

    //Returns the user's group ID
    int getGroupId() const;

    //Returns the number of views by the user of movies in a genre
    int getEffectiveViews(Genre genre) const;

    //Returns m_genreViewCount[genre];
    int getGenreViewCount(Genre genre) const;

    //Adds user to group, if user is already in a group, returns FailureException
    void addToGroup(Group* group, int groupId);

    //Remove user's reference to group, should only be called by the group when it gets destroyed
    void removeFromGroup();

    //Watch a movie and increase the user's viewcount of that genre
    void watch(Genre genre);

    //Add num of views to the user's genre ViewsCount
    void addToGenreViews(Genre genre, int num);

    //Returns true if the user is a vip
    bool isVip() const;

private:
    int m_id;
    bool m_isVip;
    int m_groupId;
    Group* m_group;
    int m_genreViewCount[4];
};
#endif // __USER_H__