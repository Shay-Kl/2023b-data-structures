#include "Movie.h"

Movie::Movie(Genre genre, int views, bool vipOnly, int id):
        m_views(views),m_vipOnly(vipOnly),
        m_id(id), m_ratingAverage(0), m_ratingCount(0), m_genre(genre) {}

Genre Movie::getGenre() const
{
    return m_genre;
}

int Movie::getViews() const
{
    return m_views;
}

int Movie::getId() const
{
    return m_id;
}

bool Movie::isVipOnly() const
{
    return m_vipOnly;
}

int Movie::getRating() const
{
    return m_ratingAverage;
}

void Movie::view(int views)
{
    m_views += views;
} 

void Movie::rate(int rating)
{
    if (rating >= 0 && rating <= 100)
    {
        double sum = ((m_ratingAverage * m_ratingCount) + rating);
        ++m_ratingCount;
        m_ratingAverage = sum /m_ratingCount;
        
    }
    
}

bool operator<(const Movie& movie1, const Movie& movie2)
{
    if (movie1.getRating() > movie2.getRating())
    {
        return true;
    }
    else if (movie1.getRating() >= movie2.getRating())
    {
        if (movie1.getViews() > movie2.getViews())
        {
            return true;
        }
        else if(movie1.getViews() == movie2.getViews())
        {
            if (movie1.getId() < movie2.getId())
            {
                return true;
            }
        }
    }
    return false;
    
}
bool operator!=(const Movie& movie1, const Movie& movie2)
{
    return movie1.getId() != movie2.getId();
}

bool operator==(const Movie& movie1, const Movie& movie2)
{
    return movie1.getId() == movie2.getId();
}

std::ostream& operator<<(std::ostream& os, const Movie& movie)
{
    os << movie.getId();
    return os;
}