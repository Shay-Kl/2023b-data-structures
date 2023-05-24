#include "Group.h"

Group::Group(int id): m_id(id), m_vipCount(0), m_userCount(0), m_isOpen(true), m_genreTotalViews(), m_genreGroupViews(){}

int Group::getId() const
{
    return m_id;
}

bool Group::isVip() const
{
    return m_vipCount;
}

bool Group::isClosed() const
{
    return !m_isOpen;
}

int Group::getUsersCount() const
{
    return m_userCount;
}

void Group::addUser(User* user)
{
    m_userCount++;
    if (user->isVip())
    {
        m_vipCount++;
    }
    m_genreGroupViews[(int)Genre::COMEDY]+=user->getEffectiveViews(Genre::COMEDY);
    m_genreGroupViews[(int)Genre::DRAMA]+=user->getEffectiveViews(Genre::DRAMA);
    m_genreGroupViews[(int)Genre::ACTION]+=user->getEffectiveViews(Genre::ACTION);
    m_genreGroupViews[(int)Genre::FANTASY]+=user->getEffectiveViews(Genre::FANTASY);

}


void Group::removeUser(User* user)
{
    m_userCount--;
    if (user->isVip())
    {
        m_vipCount--;
    }
    m_genreGroupViews[(int)Genre::COMEDY]-=user->getEffectiveViews(Genre::COMEDY);
    m_genreGroupViews[(int)Genre::DRAMA]-=user->getEffectiveViews(Genre::DRAMA);
    m_genreGroupViews[(int)Genre::ACTION]-=user->getEffectiveViews(Genre::ACTION);
    m_genreGroupViews[(int)Genre::FANTASY]-=user->getEffectiveViews(Genre::FANTASY);
}

void Group::closeGroup()
{
    m_isOpen = false;
}

int Group::getGenreViewCount(Genre genre) const
{
    return m_genreTotalViews[(int)genre];
}

int Group::getGroupViews(Genre genre) const
{
    return m_genreGroupViews[(int)genre];
}

void Group::groupWatch(Genre genre)
{
    m_genreGroupViews[(int)genre]++;
    m_genreTotalViews[(int)genre]+=m_userCount;
}

void Group::soloWatch(Genre genre)
{
    m_genreTotalViews[(int)genre]++;
}