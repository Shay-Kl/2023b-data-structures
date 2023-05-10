#include "User.h"
#include "BinaryTree.h"

User::User(bool isVip): m_isVip(isVip), m_genreViewCount() {}

Group* User::getGroup()
{
    return m_group;
}

void User::addToGroup(Group* group)
{
    if(m_group)
    {
        throw BinaryTree::FailureException();
    }
    m_group = group;

}

void User::removeFromGroup()
{
    m_group = nullptr;
}

void User::watch(Genre genre)
{
    m_genreViewCount[(int) genre]++;
}

int User::getGenreViewCount(Genre genre)
{
    if (genre==Genre::NONE)
    {
        return m_genreViewCount[0]+m_genreViewCount[1]+m_genreViewCount[2]+m_genreViewCount[3];
    }
    
    return m_genreViewCount[(int) genre];
}

bool User::isVip()
{
    return m_isVip;
}