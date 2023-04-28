#ifndef __USER_H__
#define __USER_H__

#include "Group.h"
#include "Movie.h"
#include "wet1util.h"
class User
{
    public:
        User(bool isVip);

        //Returns reference to group
        Group* getGroup();

        //Adds user to group, if user is already in a group, returns FailureException
        void addToGroup(Group* group);

        //Remove user's reference to group, should only be called by the group when it gets destroyed
        void removeFromGroup();

        //Watch a movie, increasing its viewCount and the user's viewcount of that genre
        //Returns FailiureException if the user isn't vip and can't watch it
        void watch(Movie& movie);

        //Returns the number of views by the user of movies in the genre
        int getGenreViewCount(Genre genre);


    private:
        bool m_isVip;
        Group* m_group;
        int m_genreViewCount[4];
};
#endif // __USER_H__