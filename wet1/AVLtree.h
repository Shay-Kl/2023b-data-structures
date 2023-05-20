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
    void update(const Key& oldKey, const Key& newKey);
    void remove(const Key& key);
    Val& get(const Key& key) const;
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
        Node(Key key, Val val, Node* parent): key(key), val(val), left(nullptr), right(nullptr), parent(parent), height(0) {}
        
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

    void removeNode(Node* node);
    void preOrder(Node* node);
    void swapNodes(unique_ptr<Node>& a, unique_ptr<Node>& b);
    unique_ptr<Node> copyNodes(Node* other_node, Node* parent);

    unique_ptr<Node>& unique(Node* node);

    int getBalanceFactor(Node* node);
};
template <class Key, class Val>
void AVLtree<Key,Val>::insert(const Key& key, const Val& value)
{
    if (!m_root)
    {
        m_root = unique_ptr<Node>(new Node(key,value,nullptr));
        m_min = m_root.get();
        return;
    }
    
    Node* node = m_root.get(), *parent = nullptr;
    while (node && node->key != key)
    {
        parent = node;
        if (node->key < key)
        {
            node = node->right.get();
        }
        else
        {
            node = node->left.get();
        }
    }
    if (node)
    {
        throw runtime_error("Insert existing");
    }
    unique_ptr<Node>& uniNode = (parent->key < key) ? parent->right : parent->left;
    uniNode.reset(new Node(key, value, parent));

    if(key < m_min->key)
    {
        m_min = uniNode.get();
    }
    m_count++;
}

template <class Key, class Val>
void AVLtree<Key,Val>::update(const Key& oldKey, const Key& newKey)
{
    const Val& val = get(oldKey);
    remove(oldKey);
    insert(newKey, val);
}
template <class Key, class Val>
Val& AVLtree<Key,Val>::get(const Key& key) const
{
    Node* node = m_root.get();
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
    if (!node)
    {
        throw runtime_error("Get non existing");
    }
    return node->val;
}
template <class Key, class Val>
void AVLtree<Key,Val>::remove(const Key& key)
{
    Node* node = m_root.get();
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
    if (!node)
    {
        throw runtime_error("Remove non existing");
    }
    m_count--;
    if (!(m_min->key != key))
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
void AVLtree<Key,Val>::swapNodes(unique_ptr<Node>& a, unique_ptr<Node>& b)
{
    Node* temp = a->parent;
    a->parent = b->parent;
    b->parent = temp;
    a->left.swap(b->left);
    a->right.swap(b->right);
}
template <class Key, class Val>
void AVLtree<Key,Val>::removeNode(Node* node)
{
    unique_ptr<Node>& uniNode = unique(node);
    if (node->right && node->left)
    {
        if(!node->right->left)
        {
            unique_ptr<Node> temp = move(node->right);
            // Move the left child of the node to be the left child of temp
            temp->left = move(node->left);
            temp->left->parent = temp.get();
            temp->parent = node->parent;
            uniNode = move(temp);
        }
        else 
        {
            Node* next = node->right.get();
            while(next->left) {
                next = next->left.get();
            }
            unique_ptr<Node>& inorder_successor = unique(next);
            unique_ptr<Node> temp = move(inorder_successor);
            
            // Fix the tree structure after removing the in-order successor
            if (next->right) {
                inorder_successor = move(next->right);
            }

            // Replace the node with the in-order successor
            temp->left = move(node->left);
            temp->right = move(node->right);

            if(temp->left) {
                temp->left->parent = temp.get();
            }
            if(temp->right) {
                temp->right->parent = temp.get();
            }

            temp->parent = node->parent;
            uniNode = move(temp);
        }

    }
    else if(node->right)
    {
        node->right->parent = node->parent;
        unique_ptr<Node> temp = move(node->right);
        uniNode = move(temp);
    }
    else if(node->left)
    {
        node->left->parent = node->parent;
        unique_ptr<Node> temp = move(node->left);
        uniNode = move(temp);
    }
    else
    {
        uniNode.release();
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
    std::unique_ptr<Node> new_node = unique_ptr<Node>(new Node(other_node->key, other_node->val, parent));
    new_node->height = other_node->height;
    new_node->left = copyNodes(other_node->left.get(), new_node.get());
    new_node->right = copyNodes(other_node->right.get(), new_node.get());

    // Return unique_ptr to ensure memory management
    return new_node;
}

template <class Key, class Val>
unique_ptr<typename AVLtree<Key, Val>::Node>& AVLtree<Key, Val>::unique(Node* node)
{
    if(!node->parent)
    {
        return m_root;
    }
    else if(node->parent->left.get() == node)
    {
        return node->parent->left;
    }
    else
    {
        return node->parent->right;
    }

}


#endif