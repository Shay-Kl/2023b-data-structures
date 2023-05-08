#include "Movie.h"

Movie::Movie(Genre genre, int views, bool vipOnly, int id):
    m_genre(genre),m_views(views),m_vipOnly(vipOnly), m_id(id) {}

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

void Movie::view()
{
    m_views++;
}

void Movie::rate(int rating)
{
    if (rating >= 0 && rating <= 100)
    {
        m_ratingAverage = ((m_ratingAverage * m_ratingCount) + rating) / ++m_ratingCount;
    }
    
}

bool operator<(const Movie& movie1, const Movie& movie2)
{
    if (movie1.getRating() > movie2.getRating())
    {
        return true;
    }
    else if (movie1.getRating() == movie2.getRating())
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