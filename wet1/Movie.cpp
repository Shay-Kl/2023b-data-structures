#include "Movie.h"

Movie::Movie(Genre genre, int views, bool vipOnly):
    genre(genre),views(views),vipOnly(vipOnly) {}

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

void Movie::view(int viewers)
{
    m_views+=viewers;
}

void Movie::rate(int rating)
{
    m_ratingAverage = ((m_ratingAverage * m_ratingCount) + m_rating) / ++m_ratingCount;
}
