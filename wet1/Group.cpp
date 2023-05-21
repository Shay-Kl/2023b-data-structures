#include "Group.h"

Group::Group(int id): m_id(id),m_vipCount(0), m_genreTotalViews(), m_genreGroupViews() {}

Group::Group() {}

int Group::getId() const
{
    return m_id;
}

bool Group::isVip() const
{
    return m_vipCount;
}

int Group::getUsersCount() const
{
    return users.getNodeCount();
}

void Group::addUser(User& user)
{
    if (user.getGroup())
    {
        throw std::exception();
    }
    if (user.isVip())
    {
        m_vipCount++;
    }
    this->updateViews(Genre::COMEDY, user.getEffectiveViews(Genre::COMEDY));
    this->updateViews(Genre::DRAMA, user.getEffectiveViews(Genre::DRAMA));
    this->updateViews(Genre::ACTION, user.getEffectiveViews(Genre::ACTION));
    this->updateViews(Genre::FANTASY, user.getEffectiveViews(Genre::FANTASY));
    users.insert(user.getId(), &user);

}

void Group::removeUser(User& user)
{
    if (user.isVip())
    {
        m_vipCount--;
    }
    this->updateViews(Genre::COMEDY, -(user.getEffectiveViews(Genre::COMEDY)));
    this->updateViews(Genre::DRAMA, -(user.getEffectiveViews(Genre::DRAMA)));
    this->updateViews(Genre::ACTION, -(user.getEffectiveViews(Genre::ACTION)));
    this->updateViews(Genre::FANTASY, -(user.getEffectiveViews(Genre::FANTASY)));
    users.remove(user.getId());
}

void Group::closeGroup()
{
    
}

void Group::closeGroupAux(unique_ptr<AVLtree<int,User>::Node>& curNode)
{
    if (!curNode)
    {
        return;
    }
    User& user = curNode->val;
	user.removeFromGroup();
    closeGroupAux(curNode->left);
    closeGroupAux(curNode->right);
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

AVLtree<int, User*>& Group::getUsers()
{
    return users;
}