#include "Group.h"

Group::Group(int id): m_id(id), m_isVip(false), m_vipCount(0),
                    m_usersCount(0), m_genreTotalViews(), m_genreGroupViews() {}

int Group::getId() const
{
    return m_id;
}

bool Group::isVip() const
{
    return m_isVip;
}

int Group::getUsersCount() const
{
    return m_usersCount;
}

void Group::addUser(User* user)
{
    if (user->getGroup())
    {
        throw std::exception();
    }
    m_usersCount++;
    if (user->isVip())
    {
        m_isVip = true;
        m_vipCount++;
    }
    this->updateViews(Genre::COMEDY, user->getEffectiveViews(Genre::COMEDY));
    this->updateViews(Genre::DRAMA, user->getEffectiveViews(Genre::DRAMA));
    this->updateViews(Genre::ACTION, user->getEffectiveViews(Genre::ACTION));
    this->updateViews(Genre::FANTASY, user->getEffectiveViews(Genre::FANTASY));
    //(tree->get(this->getId())).insert(user->getId(), user);

}

void Group::removeUser(User* user)
{
    m_usersCount--;
    if (user->isVip())
    {
        m_vipCount--;
        if (m_vipCount == 0)
        {
            m_isVip = false;
        }
    }
    this->updateViews(Genre::COMEDY, -(user->getEffectiveViews(Genre::COMEDY)));
    this->updateViews(Genre::DRAMA, -(user->getEffectiveViews(Genre::DRAMA)));
    this->updateViews(Genre::ACTION, -(user->getEffectiveViews(Genre::ACTION)));
    this->updateViews(Genre::FANTASY, -(user->getEffectiveViews(Genre::FANTASY)));
    //(tree->get(this->getId())).remove(user->getId());
}

void Group::updateViews(Genre genre, int views)
{
    m_genreTotalViews[(int)genre] += views;
}

int Group::getGenreViewCount(Genre genre) const
{
    return m_genreTotalViews[(int)genre];
}

int Group::getGroupViews(Genre genre) const
{
    return m_genreGroupViews[(int)genre];
}

void Group::incGroupWatch(Genre genre)
{
    m_genreGroupViews[(int)genre]++;
}

AVLtree<int,User*>* Group::getUsers(){
    return m_users;
}