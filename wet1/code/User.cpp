#include "User.h"

User::User(bool isVip): m_isVip(isVip), m_group(nullptr), m_genreViewCount() {}

void User::addToGroup(shared_ptr<Group> group, int groupId)
{
    updateGroup();
    if(group == nullptr)
    {
        throw std::bad_alloc();
    }
    m_group = group;

    m_genreViewCount[0] -= group->getGroupViews(Genre::COMEDY);
    m_genreViewCount[1] -= group->getGroupViews(Genre::DRAMA);
    m_genreViewCount[2] -= group->getGroupViews(Genre::ACTION);
    m_genreViewCount[3] -= group->getGroupViews(Genre::FANTASY);
}

void User::watch(Genre genre)
{
    updateGroup();
    m_genreViewCount[(int) genre]++;
    if (m_group)
    {
        m_group->soloWatch(genre);
    }
}

bool User::isVip() const
{
    return m_isVip;
}

int User::getGenreViewCount(Genre genre)
{
    updateGroup();
    if (genre==Genre::NONE)
    {
        return (m_genreViewCount[0] + m_genreViewCount[1] + m_genreViewCount[2]
                 + m_genreViewCount[3]);
    }
    
    return m_genreViewCount[(int) genre];
}

int User::getEffectiveViews(Genre genre)
{
    updateGroup();
    if (!m_group)
    {
        return (this->getGenreViewCount(genre));
    }
    else
    {
        if (genre == Genre::NONE)
        {
            int total = 0;
            for (int i = 0; i < 4; i++)
            {
                total += m_genreViewCount[i] + m_group->getGroupViews((Genre)i);
            }
            return total;
        }
        
        return (m_genreViewCount[(int)genre] + m_group->getGroupViews(genre));
    }
}

shared_ptr<Group> User::getGroup()
{
    updateGroup();
    return m_group;
}

void User::updateGroup()
{
    if (m_group && !m_group->isClosed())
    {
        m_genreViewCount[0] += m_group->getGroupViews(Genre::COMEDY);
        m_genreViewCount[1] += m_group->getGroupViews(Genre::DRAMA);
        m_genreViewCount[2] += m_group->getGroupViews(Genre::ACTION);
        m_genreViewCount[3] += m_group->getGroupViews(Genre::FANTASY);
        m_group = nullptr;
    }
}