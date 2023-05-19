#include <map>
#include <stdexcept>

template <class Key, class Value>
class AVLtree: public std::map<Key,Value>
{
    public:
    int count = 0;

    void insert(const Key& key, const Value& value)
    {
        if (this->find(key) != this->end())
        {
            throw exception();
        }
        count++;
        this->emplace(key, value);
    }

    Value& get(const Key& key)
    {
        auto it = this->find(key);
        if (it == this->end())
        {
            throw exception()
        }
        return it->second;
    }

    void remove(const Key& key)
    {
        if (this->find(key) == this->end())
        {
            throw exception()
        }
        count--;
        this->erase(key);
    }

    int getNodeCount() const { return count; }
};
