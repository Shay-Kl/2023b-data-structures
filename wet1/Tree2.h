#ifndef __tree_h__
#define __tree_h__
#include <memory>
#include <iostream>

using namespace std;

template <class Key, class Val>
class AVLtree
{

public:
    AVLtree() {}
    void insert(const Key& key, const Val& val);
    void remove(const Key& key);
    Val& get(Key& key);
    int getNodeCount() { cout << m_count; return m_count; }
    struct Node
    {
    public:
        Key key;
        Val val;
        friend AVLtree;
    private:
        Node(): key(Key()), val(Val()), parent(nullptr), left(nullptr), right(nullptr) {}
        Node(Key key, Val val): key(key), val(val), parent(nullptr), left(nullptr), right(nullptr) {}
        unique_ptr<Node> left, right;
        Node* parent;
        int height;
    };
    class Iterator
    {
    public:
        Iterator& operator++()
        {
            if (node->right)
            {
                node = node->right.get();
                while(node->left)
                {
                    node = node->left.get();
                }
            }
            else
            {
                while(node->parent && node->parent->right.get() == node)
                {
                    node = node->parent;
                }
                node = node->parent;
            }
            return *this;
        }

        bool operator!=(Iterator& other) const
        {
            return node != other.node;
        }
        Node& operator*()
        {
            return *node;
        }
    private:
        Node* node;
        Iterator(Node* node): node(node) {}
        friend AVLtree;
    };
    Iterator begin() { return m_min; }
    Iterator end() { return nullptr; }

    template <class K,class V>
    friend ostream& operator<<(ostream& os, AVLtree<Key, Val>& tree);

private:
    unique_ptr<Node> m_root = unique_ptr<Node>(new Node);
    Node* m_min = nullptr;
    int m_count = 0;

    Node* find(const Key& key);
    Node* top() { return m_root->right.get(); }
    void removeNode(AVLtree::Node* node);

    void preOrder(Node* node);

};
template <class Key, class Val>
void AVLtree<Key,Val>::insert(const Key& key, const Val& value)
{
    Node* parent = m_root.get(), *node = parent->right.get();
    while (node)
    {
        parent = node;
        if (!(node->key != key))
        {
            throw exception();
        }
        if (node->key < key)
        {
            node = node->right.get();
        }
        else
        {
            node = node->left.get();
        }
    }
    if (parent->key < key)
    {
        parent->right = unique_ptr<Node>(new Node(key, value));
        parent->right->parent = parent;
    }
    else
    {
        parent->left = unique_ptr<Node>(new Node(key, value));
        parent->left->parent = parent;
    }
    if(!m_min)
    {
        m_min = parent->right.get();
    }
    else if (key < m_min->key)
    {
        m_min = parent->left.get();
    }
    
    m_count++;
}
template <class Key, class Val>
typename AVLtree<Key,Val>::Node* AVLtree<Key,Val>::find(const Key& key)
{
    AVLtree::Node* node = top();
    while (node && node->key != key)
    {
        if (node->key < key)
        {
            node = node->right.get();
        }
        else
        {
            node = node->left.get();
        }
    }
    return node;
}
template <class Key, class Val>
Val& AVLtree<Key,Val>::get(Key& key)
{
    Node* node = find(key);
    if (!node)
    {
        throw exception();
    }
    return node->val;
}
template <class Key, class Val>
void AVLtree<Key,Val>::remove(const Key& key)
{
    Node* node = find(key);
    if (!node)
    {
        throw exception();
    }

    m_count--;
    if(m_min == node)
    {
        if(node->right)
        {
            m_min = node->right.get();
        }
        else if(m_count)
        {
            m_min = node->parent;
        }
        else
        {
            m_min = nullptr;
        }
    }
    removeNode(node);
}
template <class Key, class Val>
void AVLtree<Key,Val>::removeNode(AVLtree<Key,Val>::Node* node)
{
    
    if(!node->right && !node->left)
    {
        if (!(node->key != node->parent->right->key))
        {
            node->parent->right = nullptr;
        }
        else
        {
            node->parent->left = nullptr;
        }
    }
    else if(!node->right)
    {
        if (!(node->key != node->parent->right->key))
        {
            node->left->parent = node->parent;
            node->parent->right = move(node->left);
        }
        else
        {
            node->left->parent = node->parent;
            node->parent->left = move(node->left);
        }
    }
    else if(!node->left)
    {
        if (!(node->key != node->parent->right->key))
        {
            node->right->parent = node->parent;
            node->parent->right = move(node->right);
        }
        else
        {
            node->right->parent = node->parent;
            node->parent->left = move(node->right);
        }
    }
    else
    {
        Node* next = node->right.get();
        while(next->left)
        {
            next = next->left.get();
        }
        node->key = next->key;
        node->val = next->val;
        removeNode(next);
    }
}
template <class Key, class Val>
void AVLtree<Key,Val>::preOrder(AVLtree::Node* node)
{
    if(node)
    {
        cout << node->key << ", ";
        preOrder(node->left.get());
        preOrder(node->right.get());
    }
}

template <class Key,class Val>
ostream& operator<<(ostream& os, AVLtree<Key, Val>& tree)
{
    cout << endl << "Inorder: ";
    
    for (typename AVLtree<Key,Val>::Node& node: tree)
    {
        cout << node.key << ", ";
    }
    return os;
}
#endif