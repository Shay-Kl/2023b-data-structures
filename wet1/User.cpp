#include "User.h"

User::User(int id, bool isVip): m_id(id), m_isVip(isVip), m_groupId(0),
                        m_group(nullptr), m_genreViewCount() {}

Group& User::getGroup() const
{
    return *m_group;
}

int User::getId() const
{
    return m_id;
}

int User::getGroupId() const
{
    return m_groupId;
}

void User::addToGroup(shared_ptr<Group> group, int groupId)
{
    if (m_groupId != 0)
    {
        throw std::exception();
    }
    if(group == nullptr)
    {
        throw std::bad_alloc();
    }
    m_group = group;
    m_groupId = groupId;

    m_genreViewCount[0] -= group->getGroupViews(Genre::COMEDY);
    m_genreViewCount[1] -= group->getGroupViews(Genre::DRAMA);
    m_genreViewCount[2] -= group->getGroupViews(Genre::ACTION);
    m_genreViewCount[3] -= group->getGroupViews(Genre::FANTASY);
}

void User::removeFromGroup()
{
    m_genreViewCount[0] += m_group->getGroupViews(Genre::COMEDY);
    m_genreViewCount[1] += m_group->getGroupViews(Genre::DRAMA);
    m_genreViewCount[2] += m_group->getGroupViews(Genre::ACTION);
    m_genreViewCount[3] += m_group->getGroupViews(Genre::FANTASY);
    m_groupId = 0;
    m_group = nullptr;

    
}

void User::watch(Genre genre)
{
    m_genreViewCount[(int) genre]++;
    if (m_group)
    {
        m_group->updateViews(genre, 1);
    }
}

bool User::isVip() const
{
    return m_isVip;
}

void User::addToGenreViews(Genre genre, int num)
{
    m_genreViewCount[(int) genre] += num;
}

int User::getGenreViewCount(Genre genre) const
{
    if (genre==Genre::NONE)
    {
        return (m_genreViewCount[0] + m_genreViewCount[1] + m_genreViewCount[2]
                 + m_genreViewCount[3]);
    }
    
    return m_genreViewCount[(int) genre];
}

int User::getEffectiveViews(Genre genre) const
{
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