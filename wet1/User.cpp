#include "User.h"
#include "BinaryTree.h"

User::User(bool isVip): m_isVip(isVip) { }

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

void User::watch(Movie& movie)
{
    if(movie.isVipOnly() && !m_isVip)
    {
        throw BinaryTree::FailureException();
    }
    movie.view();
    m_genreViewCount[(int) movie.getGenre()]++;
}

int User::getGenreViewCount(Genre genre)
{
    return m_genreViewCount[(int) genre];
}