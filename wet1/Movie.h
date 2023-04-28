#ifndef __MOVIE_H__
#define __MOVIE_H__

#include "wet1util.h"

class Movie
{
    public:
        Movie(Genre genre, int views, bool vipOnly);

        //Returns the movie's genre
        Genre getGenre() const;

        //Returns the movie's view count
        int getViews() const;

        //Return true if movie is only for vip users
        bool isVipOnly() const;

        //Returns the movie's average rating    
        int getRating() const;

        //Increment the movie's view count
        void view();

        //Rate the movie with a given rating 0-100
        //Updates the average rating accordingly
        void rate(int rating);



    private:
        Genre m_genre;
        bool m_vipOnly;
        int m_views;
        double m_ratingAverage = 0; //TODO: Not sure if movie with no rating is considered to have average of 0
        int m_ratingCount = 0;
};
#endif // __MOVIE_H__