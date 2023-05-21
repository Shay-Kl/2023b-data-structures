#ifndef __MOVIE_H__
#define __MOVIE_H__

#include "wet1util.h"

class Movie
{
public:
    //C'tor
    Movie(Genre genre, int views, bool vipOnly, int id);

    //Returns the movie's genre
    Genre getGenre() const;

    //Returns the movie's view count
    int getViews() const;

    //Return true if movie is only for vip users
    bool isVipOnly() const;

    //Returns the movie's average rating    
    int getRating() const;

    //Returns the movie's id
    int getId() const;

    //Increment the movie's view count
    void view(int views = 1);

    //Rate the movie with a given rating 0-100
    //Updates the average rating accordingly
    void rate(int rating);

    //Compares 2 movies, with the "lower" one being whichever is
    // higher rated/higher viewed/lower id in that order
    friend bool operator!=(const Movie& movie1, const Movie& movie2);
    friend bool operator<(const Movie& movie1, const Movie& movie2);
    friend bool operator==(const Movie& movie1, const Movie& movie2);
    friend std::ostream& operator<<(std::ostream& os, const Movie& movie)
    {
        std::cout << (movie.m_id);
        return os;
    }

private:
    int m_views;
    bool m_vipOnly;
    int m_id;
    double m_ratingAverage;
    int m_ratingCount;
    Genre m_genre;
};
#endif //__MOVIE_H__