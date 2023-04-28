#include "Movie.h"

Movie::Movie(Genre genre, int views, bool vipOnly):
    m_genre(genre),m_views(views),m_vipOnly(vipOnly) {}

Genre Movie::getGenre() const
{
    return m_genre;
}

int Movie::getViews() const
{
    return m_views;
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
    m_ratingAverage = ((m_ratingAverage * m_ratingCount) + rating) / ++m_ratingCount;
}
