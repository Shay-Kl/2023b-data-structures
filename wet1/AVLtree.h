#ifndef __tree_h__
#define __tree_h__
#include <memory>
#include <iostream>

using namespace std;

template <class Key, class Val>
class AVLtree
{

public:
    AVLtree(): m_root(nullptr), m_min(nullptr), m_count(0) {}
    AVLtree(const AVLtree<Key, Val>& other) : m_root(nullptr), m_min(nullptr), m_count(other.m_count)
    {
        m_root = unique_ptr<Node>(copyNodes(other.m_root.get(), nullptr));
        if(m_root)
        {
            m_min = m_root.get();
            while(m_min->left)
            {
                m_min = m_min->left.get();
            }
        }
    }
    AVLtree& operator=(const AVLtree& other)
    {
        if (this != &other) 
        {
            m_root = nullptr;
            m_min = nullptr;
            m_count = other.m_count; 
            this->m_root = unique_ptr<Node>(copyNodes(other.m_root.get(), nullptr));
            if(m_root)
            {
                m_min = m_root.get();
                while(m_min->left)
                {
                    m_min = m_min->left.get();
                }
            }
        }
        return *this;
    }
    void insert(const Key& key, const Val& val);
    void remove(const Key& key);
    Val& get(Key& key);
    int getNodeCount() const {  return m_count; }
    class Node
    {
    public:
        Key key;
        Val val;
        unique_ptr<Node> left, right;
        Node* parent;
        int height;
        
    private:
        friend AVLtree;
        Node(): key(Key()), val(Val()), left(nullptr), right(nullptr), parent(nullptr), height(0) {}
        Node(Key key, Val val): key(key), val(val), left(nullptr), right(nullptr), parent(nullptr), height(0) {}
        
        void updateHeight()
        {
            int leftHeight = -1, rightHeight = -1;
            if (left)
            {
                leftHeight = left->height;
            }
            if (right)
            {
                rightHeight = right->height;
            }
            height = (leftHeight > rightHeight) ? leftHeight+1 : rightHeight+1;
            if (parent)
            {
                parent->updateHeight();
            }
            
        }
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

        bool operator!=(const Iterator& other) const
        {
            return node != other.node;
        }
        const Node& operator*() const
        {
            return *node;
        }
    private:
        Node* node;
        Iterator(Node* node): node(node) {}
        Iterator(): node(nullptr) {}
        friend AVLtree;
    };
    Iterator begin() { return m_min; }
    Iterator end() { return nullptr; }

    template <class K,class V>
    friend ostream& operator<<(ostream& os, AVLtree<K, V>& tree);

private:
    unique_ptr<Node> m_root;
    Node* m_min;
    int m_count;

    Node* find(const Key& key);
    void removeNode(AVLtree::Node* node);
    void removeRoot();
    void preOrder(Node* node);
    unique_ptr<Node> copyNodes(Node* other_node, Node* parent);

    int getBalanceFactor(Node* node);
};
template <class Key, class Val>
void AVLtree<Key,Val>::insert(const Key& key, const Val& value)
{
    if(!m_root)
    {
        m_root = unique_ptr<Node>(new Node(key,value));
        m_min = m_root.get();
    }
    else
    {
        Node* parent = nullptr, *node = m_root.get();
        while (node)
        {
            parent = node;
            if (!(node->key != key))
            {
                throw runtime_error("Insert existing");
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
        unique_ptr<Node> newNode(new Node(key,value));

        if (parent->key < key)
        {
            parent->right = move(newNode);
            parent->right->parent = parent;
        }
        else
        {
            parent->left = move(newNode);
            parent->left->parent = parent;
        }

        if(key < m_min->key)
        {
            m_min = parent->left.get();
        }
    }
    m_count++;

}
template <class Key, class Val>
typename AVLtree<Key,Val>::Node* AVLtree<Key,Val>::find(const Key& key)
{
    AVLtree::Node* node = m_root.get();
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
        throw runtime_error("Get non existing");
    }
    return node->val;
}
template <class Key, class Val>
void AVLtree<Key,Val>::remove(const Key& key)
{
    Node* node = find(key);
    if (!node)
    {
        throw runtime_error("Remove non existing");
    }

    m_count--;
    if(node == m_root.get())
    {
        removeRoot();
    }
    else
    {
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
}
template <class Key, class Val>
void AVLtree<Key,Val>::removeNode(AVLtree<Key,Val>::Node* node)
{
    Node* parent = node->parent;
    if(!node->right && !node->left)
    {
        if (parent->right.get() == node)
        {
            parent->right = nullptr;

        }
        else
        {
            parent->left = nullptr;
        }
    }
    else if(!node->right)
    {
        if (parent->right.get() == node)
        {
            node->left->parent = parent;
            parent->right = move(node->left);
            node->left = nullptr;
        }
        else
        {
            node->left->parent = parent;
            parent->left = move(node->left);
            node->left = nullptr;
        }
    }
    else if(!node->left)
    {
        if (parent->right.get() == node)
        {
            node->right->parent = parent;
            parent->right = move(node->right);
            node->right = nullptr;
        }
        else
        {
            node->right->parent = parent;
            parent->left = move(node->right);
            node->right = nullptr;
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
void AVLtree<Key,Val>::removeRoot()
{
    if(!m_root->right && !m_root->left)
    {
        m_root = nullptr;
        m_min = nullptr;
    }
    else if(!m_root->right)
    {
        unique_ptr<Node> temp = move(m_root);
        m_root = move(temp->left);
        m_root->parent = nullptr;
    }
    else if(!m_root->left)
    {
        unique_ptr<Node> temp = move(m_root);
        m_root = move(temp->right);
        m_root->parent = nullptr;
        m_min = m_root.get();
    }
    else
    {
        Node* next = m_root->right.get();
        if(!next->left)
        {
            m_root->key = next->key;
            m_root->val = next->val;
            m_root->right = move(m_root->right->right);
            if(m_root->right)
            {
                m_root->right->parent = m_root.get();
            }
        }
        else
        {
            while(next->left)
            {
                next = next->left.get();
            }

            unique_ptr<Node> temp = move(m_root);
            m_root = move(next->parent->left);
            m_root->parent = nullptr;
            m_root->left = move(temp->left);
            m_root->right = move(temp->right);
            removeNode(next);
        }
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
    
    for (const typename AVLtree<Key,Val>::Node& node: tree)
    {
        cout << node.key << ", ";
    }
    cout << endl << "Preorder: ";
    tree.preOrder(tree.m_root.get());
    cout << endl;
    return os;
}

template <class Key, class Val>
unique_ptr<typename AVLtree<Key, Val>::Node> AVLtree<Key, Val>::copyNodes(Node* other_node, Node* parent)
{
    if (other_node == nullptr)
    {
        return nullptr;
    }
    
    // Use unique_ptr for new_node
    std::unique_ptr<Node> new_node = unique_ptr<Node>(new Node(other_node->key, other_node->val));
    new_node->parent = parent;
    new_node->height = other_node->height;
    new_node->left = copyNodes(other_node->left.get(), new_node.get());
    new_node->right = copyNodes(other_node->right.get(), new_node.get());

    // Return unique_ptr to ensure memory management
    return new_node;
}



#endif